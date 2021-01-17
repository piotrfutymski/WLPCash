--#################### RELACJE ####################
DROP TABLE WPLATY;
DROP TABLE OKRESY_SKLADKOWE;
DROP TABLE STANY_INSTRUKTOROW;
DROP TABLE STATUSY;
DROP TABLE DRUZYNY;
DROP TABLE TYPY_DRUZYN;
DROP TABLE HUFCOWI;
DROP TABLE INSTRUKTORZY;
DROP TABLE HUFCE;
DROP TABLE STOPNIE_INSTRUKTORSKIE;
DROP TABLE STOPNIE_HARCERSKIE;

CREATE TABLE STOPNIE_INSTRUKTORSKIE
(
	nazwa VARCHAR2(64) CONSTRAINT PK_STOPNIE_INSTRUKTORSKIE PRIMARY KEY
);
CREATE TABLE STOPNIE_HARCERSKIE
(
	nazwa VARCHAR2(64) CONSTRAINT PK_STOPNIE_HARCERSKIE PRIMARY KEY
);
CREATE TABLE HUFCE
(
	nazwa VARCHAR2(64) CONSTRAINT PK_HUFCE PRIMARY KEY
);
CREATE TABLE INSTRUKTORZY
(
	id_instr NUMBER(6) CONSTRAINT PK_INSTRUKTORZY PRIMARY KEY,
	imie VARCHAR2(64) NOT NULL,
	nazwisko VARCHAR2(64) NOT NULL,
	email VARCHAR2(64) NOT NULL,
	rozkaz_przyjecia VARCHAR2(64) NOT NULL,
	st_instr VARCHAR2(64) NOT NULL CONSTRAINT FK_INSTRUKTORZY_ST_INSTR REFERENCES STOPNIE_INSTRUKTORSKIE(nazwa),
	st_harc VARCHAR2(64) NOT NULL CONSTRAINT FK_INSTRUKTORZY_ST_HARC REFERENCES STOPNIE_HARCERSKIE(nazwa),
	hufiec VARCHAR2(64) CONSTRAINT FK_INSTR_HUFCE REFERENCES HUFCE(nazwa) ON DELETE SET NULL
);
CREATE TABLE HUFCOWI
(
	hufiec VARCHAR2(64) CONSTRAINT FK_HUFC_HUFCE REFERENCES HUFCE(nazwa) ON DELETE CASCADE,
	hufcowy NUMBER(6) NOT NULL CONSTRAINT FK_HUFC_INSTRUKTORZY REFERENCES INSTRUKTORZY(id_instr) ON DELETE CASCADE,
	CONSTRAINT PK_HUFCOWI PRIMARY KEY(hufiec),
  CONSTRAINT U_HUFCOWI UNIQUE(HUFCOWY)
);
CREATE TABLE TYPY_DRUZYN
(
  nazwa VARCHAR2(64) CONSTRAINT PK_TYPY_DRUZYN PRIMARY KEY
);
CREATE TABLE DRUZYNY
(
	nazwa VARCHAR2(64),
	numer NUMBER(6),
	probna VARCHAR2(3) NOT NULL,
	patron VARCHAR2(64),
	druzynowy NUMBER(6) NOT NULL CONSTRAINT FK_DR_INSTRUKTORZY REFERENCES INSTRUKTORZY(id_instr),
	hufiec VARCHAR2(64) NOT NULL CONSTRAINT FK_DR_HUFCE REFERENCES HUFCE(nazwa),
	typ_druzyny VARCHAR2(64) NOT NULL CONSTRAINT FK_DR_TYPY_DRUZYN REFERENCES TYPY_DRUZYN(nazwa),
	CONSTRAINT PK_DRUZYNY PRIMARY KEY(nazwa, numer),
  CONSTRAINT CHK_PROBNA CHECK(probna IN ('TAK', 'NIE')),
  CONSTRAINT U_DRUZYNY UNIQUE(druzynowy)
);
CREATE TABLE STATUSY
(
	nazwa VARCHAR2(64) CONSTRAINT PK_STATUSY PRIMARY KEY
);
CREATE TABLE STANY_INSTRUKTOROW
(
  poczatek DATE, 
  koniec DATE,
  status VARCHAR2(64) NOT NULL CONSTRAINT FK_ST_STATUS REFERENCES STATUSY(nazwa),
  instruktor NUMBER(6) CONSTRAINT FK_ST_INSTRUKTORZY REFERENCES INSTRUKTORZY(id_instr) ON DELETE CASCADE,
  CONSTRAINT PK_STANY_INSTRUKTOROW PRIMARY KEY(poczatek, instruktor),
  CONSTRAINT CHK_POCZ_KON_STANY_INSTRUKTOROW CHECK(poczatek < koniec)
);
CREATE TABLE OKRESY_SKLADKOWE
(
  poczatek DATE CONSTRAINT PK_OKRESY_SKLADKOWE PRIMARY KEY,
  kwota NUMBER(8,2) NOT NULL, 
  koniec DATE,
  CONSTRAINT CHK_POCZ_KON_OKRESY_SKLADKOWE CHECK(poczatek < koniec)
);
CREATE TABLE WPLATY
(
  id_wplaty NUMBER(6) CONSTRAINT PK_WPLATY PRIMARY KEY,
  kwota NUMBER(8,2) NOT NULL, 
  data DATE NOT NULL,
  instruktor NUMBER(6) NOT NULL CONSTRAINT FK_WPL_INSTRUKTORZY REFERENCES INSTRUKTORZY(id_instr) ON DELETE CASCADE
);

--#################### SEKWENCJE ####################

DROP SEQUENCE wplaty_id_seq;
DROP SEQUENCE instruktorzy_id_seq;

CREATE SEQUENCE wplaty_id_seq START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE instruktorzy_id_seq START WITH 1 INCREMENT BY 1;

--#################### TRIGGERY ####################
CREATE OR REPLACE TRIGGER HUFCE_UPD
BEFORE UPDATE OF nazwa ON HUFCE
 FOR EACH ROW
 WHEN (NEW.nazwa IS NOT NULL AND OLD.nazwa <> NEW.nazwa)
BEGIN
  UPDATE INSTRUKTORZY
  SET hufiec = :NEW.nazwa
  WHERE hufiec = :OLD.nazwa;

  UPDATE HUFCOWI
  SET hufiec = :NEW.nazwa
  WHERE hufiec = :OLD.nazwa;

  UPDATE druzyny
  SET hufiec = :NEW.nazwa
  WHERE hufiec = :OLD.nazwa;
END;

--#################### FUNKCJE ####################

CREATE OR REPLACE FUNCTION sumaSkladekInstruktoraWOkresie
(
  pID IN INSTRUKTORZY.ID_INSTR%TYPE,
  pPoczatek IN VARCHAR,
  pKoniec IN VARCHAR
) RETURN NUMBER IS
  vPoczatek DATE;
  vKoniec DATE;
  vSuma NUMBER;
BEGIN
  vPoczatek := to_date(pPoczatek,'DD-MM-YYYY');
  vKoniec := to_date(pKoniec,'DD-MM-YYYY');
  SELECT SUM(kwota) INTO vSuma FROM WPLATY
  WHERE data >= vPoczatek AND data <= vKoniec
  GROUP BY instruktor
  HAVING instruktor = pID;
  return vSuma;
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    return 0;
END;

CREATE OR REPLACE FUNCTION sumaSkladekHufcaWOkresie
(
  pNazwa IN HUFCE.NAZWA%TYPE,
  pPoczatek IN VARCHAR,
  pKoniec IN VARCHAR
)RETURN NUMBER IS
  vPoczatek DATE;
  vKoniec DATE;
  vSuma NUMBER;
BEGIN
  vPoczatek := to_date(pPoczatek,'DD-MM-YYYY');
  vKoniec := to_date(pKoniec,'DD-MM-YYYY');
  SELECT SUM(kwota) INTO vSuma FROM WPLATY INNER JOIN INSTRUKTORZY ON(instruktor = id_instr)
  WHERE data >= vPoczatek AND data <= vKoniec
  GROUP BY hufiec
  HAVING hufiec IS NOT NULL AND hufiec = pNazwa;
  return vSuma;
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    return 0;
END;

CREATE OR REPLACE FUNCTION naleznoscInstruktoraDo
(
  pID IN INSTRUKTORZY.ID_INSTR%TYPE,
  pBariera DATE
)RETURN NUMBER IS

  CURSOR cStany IS 
  SELECT * FROM STANY_INSTRUKTOROW
  WHERE instruktor = pID
  ORDER BY poczatek;
  
  vStan STANY_INSTRUKTOROW%ROWTYPE;
  vD DATE;
  vKoniec DATE;
  vKwota NUMBER;
  vSuma NUMBER DEFAULT 0;
BEGIN
  OPEN cStany;
  LOOP
    FETCH cStany INTO vStan;
    EXIT WHEN cStany%NOTFOUND;

    IF vStan.status IN ('CZYNNY', 'REZERWA') THEN
      vD := vStan.poczatek;
      IF vStan.koniec IS NULL OR pBariera <= vStan.koniec THEN
        vKoniec := pBariera;
      ELSE
        vKoniec := vStan.koniec;
      END IF;
      IF EXTRACT(DAY FROM vD) > 1 THEN
        vD := LAST_DAY(LAST_DAY(vD)+1);
      ELSE
        vD := LAST_DAY(vD);
      END IF;
      WHILE vD <= vKoniec LOOP
        SELECT kwota into vKwota FROM OKRESY_SKLADKOWE
        WHERE poczatek <= vd AND (koniec IS NULL OR koniec >= vd);
        vSuma := vSuma + vKwota;
        vD := LAST_DAY(vD+1);
      END LOOP;
    END IF;
  END LOOP;
  
  CLOSE cStany;
  return vSuma;
END;


CREATE OR REPLACE FUNCTION doKiedyUzupelniono
(
  pID IN INSTRUKTORZY.ID_INSTR%TYPE
) RETURN DATE IS
  vZaplaconed NUMBER;
  vWymaganed NUMBER;
  vRes DATE;
BEGIN
  SELECT MIN(poczatek) INTO vRes FROM STANY_INSTRUKTOROW
  WHERE instruktor = pID;
  vZaplaconed := sumaSkladekInstruktoraWOkresie(pID, '01-01-2000', TO_CHAR(CURRENT_DATE, 'dd-mm-yyyy'));

  LOOP
    vWymaganed := naleznoscInstruktoraDo(pID, LAST_DAY(vRes+1));
    EXIT WHEN vWymaganed > vZaplaconed;
    vRes := LAST_DAY(vRes+1);
    IF vRes > CURRENT_DATE THEN
      vRes := CURRENT_DATE;
      EXIT;
    END IF;
  END LOOP;

  return vRes;
END;

CREATE OR REPLACE FUNCTION czyUzupelnionoDo
(
  pID IN INSTRUKTORZY.ID_INSTR%TYPE,
  pKoniec IN VARCHAR
)RETURN VARCHAR IS
  vKoniec DATE;
BEGIN
  vKoniec := to_date(pKoniec, 'dd-mm-yyyy');
  IF vKoniec < doKiedyUzupelniono(pID) THEN
    return 'TAK';
  END IF;
  return 'NIE';
END;

create or replace FUNCTION ImieNazwiskoDoID
(
  pImieNazwisko IN HUFCE.NAZWA%TYPE
) 
RETURN INSTRUKTORZY.ID_INSTR%TYPE IS
  vID Instruktorzy.id_instr%TYPE;
BEGIN
	SELECT id_instr INTO vID FROM instruktorzy
  WHERE pImieNazwisko LIKE (imie || ' ' || nazwisko);
  return vID;
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    raise_application_error(-20001, 'NO OPERATION');
END;

--#################### PROCEDURY ####################

create or replace PROCEDURE ResetBazy IS
BEGIN
  DELETE FROM WPLATY;
  DELETE FROM OKRESY_SKLADKOWE;
  DELETE FROM STANY_INSTRUKTOROW;
  DELETE FROM STATUSY;
  DELETE FROM DRUZYNY;
  DELETE FROM TYPY_DRUZYN;
  DELETE FROM HUFCOWI;
  DELETE FROM INSTRUKTORZY;
  DELETE FROM HUFCE;
  DELETE FROM STOPNIE_INSTRUKTORSKIE;
  DELETE FROM STOPNIE_HARCERSKIE;
  
  INSERT INTO typy_druzyn(nazwa) VALUES('ZUCHOWA');
  INSERT INTO typy_druzyn(nazwa) VALUES('HARCERSKA');
  INSERT INTO typy_druzyn(nazwa) VALUES('WEDROWNICZA');
  
  INSERT INTO statusy(nazwa) VALUES('CZYNNY');
  INSERT INTO statusy(nazwa) VALUES('REZERWA');
  INSERT INTO statusy(nazwa) VALUES('URLOP');
  INSERT INTO statusy(nazwa) VALUES('SKRESLONY');
  
  INSERT INTO STOPNIE_INSTRUKTORSKIE(nazwa) VALUES('PWD');
  INSERT INTO STOPNIE_INSTRUKTORSKIE(nazwa) VALUES('PHM');
  INSERT INTO STOPNIE_INSTRUKTORSKIE(nazwa) VALUES('HM');
  
  INSERT INTO STOPNIE_HARCERSKIE(nazwa) VALUES('HO');
  INSERT INTO STOPNIE_HARCERSKIE(nazwa) VALUES('HR');
  
  INSERT INTO OKRESY_SKLADKOWE(poczatek, kwota, koniec) VALUES(TO_DATE('01-01-2000', 'dd-mm-yyyy'), 0, NULL);
END;

create or replace PROCEDURE ResetWplat IS
BEGIN
  DELETE FROM WPLATY;
  DELETE FROM OKRESY_SKLADKOWE;
  
  INSERT INTO OKRESY_SKLADKOWE(poczatek, kwota, koniec) VALUES(TO_DATE('01-01-2000', 'dd-mm-yyyy'), 0, NULL);
END;

create or replace PROCEDURE DodajHufiec
(
  pHufiec IN VARCHAR,
  pImieNazwisko IN VARCHAR
) IS
vID NUMBER;
BEGIN
  vID := IMIENAZWISKODOID(pImieNazwisko);
  INSERT INTO HUFCE(nazwa)
	VALUES (pHufiec);

  UPDATE INSTRUKTORZY
  SET hufiec = pHufiec
  WHERE id_instr=vID;

  DELETE FROM hufcowi
  WHERE hufiec = pHufiec;
  INSERT INTO hufcowi(hufiec, hufcowy)
  VALUES(pHufiec, vID);
END;

create or replace PROCEDURE usunHufiec
(
  pHufiec IN VARCHAR
) IS
BEGIN
  DELETE FROM HUFCE
	WHERE nazwa = pHufiec;
  IF SQL%NOTFOUND THEN
    raise_application_error(-20001, 'NO OPERATION');
  END IF;
END;

create or replace PROCEDURE modyfikujHufiec
(
  pStaraNazwa IN VARCHAR,
  pNowaNazwa IN VARCHAR,
  pImieNazwisko IN VARCHAR
)IS
  vID NUMBER;
BEGIN
  vID := IMIENAZWISKODOID(pImieNazwisko);

  DELETE FROM hufcowi
  WHERE hufiec = pStaraNazwa;

  UPDATE HUFCE
  SET nazwa = pNowaNazwa
  WHERE nazwa = pStaraNazwa;

  INSERT INTO hufcowi(hufiec, hufcowy)
  VALUES(pNowaNazwa, vID);
END;

CREATE OR REPLACE PROCEDURE DodajStan
(
  pStatus IN VARCHAR,
  pImieNazw IN VARCHAR,
  pData IN VARCHAR
) IS
BEGIN
  UPDATE STANY_INSTRUKTOROW
  SET koniec = to_date(pData, 'dd-mm-yyyy')
  WHERE instruktor = IMIENAZWISKODOID(pImieNazw) AND koniec IS NULL;

  INSERT INTO STANY_INSTRUKTOROW(poczatek, status, instruktor)
  VALUES(to_date(pData, 'dd-mm-yyyy'), pStatus, IMIENAZWISKODOID(pImieNazw));
END;

CREATE OR REPLACE PROCEDURE UsunStan
(
  pData IN VARCHAR,
  pImieNazw IN VARCHAR
) IS
  vNowyPocz DATE;
BEGIN
  SELECT poczatek INTO vNowyPocz FROM STANY_INSTRUKTOROW
  WHERE koniec = to_date(pData, 'dd-mm-yyyy') AND instruktor = IMIENAZWISKODOID(pImieNazw);

  DELETE FROM STANY_INSTRUKTOROW
  WHERE instruktor = IMIENAZWISKODOID(pImieNazw) AND poczatek = to_date(pData, 'dd-mm-yyyy') AND koniec IS NULL;

  IF SQL%NOTFOUND THEN
    raise_application_error(-20001, 'NO OPERATION');
  END IF;

  UPDATE STANY_INSTRUKTOROW
  SET koniec = NULL
  WHERE instruktor = IMIENAZWISKODOID(pImieNazw) AND poczatek = vNowyPocz;
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    raise_application_error(-20001, 'NO OPERATION');
END;

CREATE OR REPLACE PROCEDURE dodajInstruktora
(
  pImie IN VARCHAR,
  pNazwisko IN VARCHAR,
  pEmail IN VARCHAR,
  pRozkaz IN VARCHAR,
  pStInstr IN VARCHAR,
  pStHarc IN VARCHAR,
  pHufiec IN VARCHAR,
  pData IN VARCHAR
) IS
  vID INSTRUKTORZY.ID_INSTR%TYPE;
BEGIN
  vID := instruktorzy_id_seq.nextval;
  IF pHufiec = '' THEN
    INSERT INTO INSTRUKTORZY(id_instr, imie, nazwisko, email, rozkaz_przyjecia, st_instr, st_harc, hufiec)
    VALUES (vID, pImie, pNazwisko, pEmail, pRozkaz, pStInstr, pStHarc, pHufiec);
  ELSE
    INSERT INTO INSTRUKTORZY(id_instr, imie, nazwisko, email, rozkaz_przyjecia, st_instr, st_harc)
    VALUES (vID, pImie, pNazwisko, pEmail, pRozkaz, pStInstr, pStHarc);
  END IF;
  DodajStan('CZYNNY', pImie || ' ' || pNazwisko, pData);
END;

CREATE OR REPLACE PROCEDURE usunInstruktora
(
  pImie IN VARCHAR,
  pNazwisko IN VARCHAR
) IS
BEGIN
  DELETE FROM INSTRUKTORZY
  WHERE imie = pImie AND nazwisko = pNazwisko;

  IF SQL%NOTFOUND THEN
    raise_application_error(-20001, 'NO OPERATION');
  END IF;
END;

CREATE OR REPLACE PROCEDURE modyfikujInstruktora
(
  pStareImie IN VARCHAR,
  pStareNazwisko IN VARCHAR,
  pImie IN VARCHAR,
  pNazwisko IN VARCHAR,
  pEmail IN VARCHAR,
  pRozkaz IN VARCHAR,
  pStInstr IN VARCHAR,
  pStHarc IN VARCHAR,
  pHufiec IN VARCHAR
) IS
BEGIN
IF pHufiec = '' THEN
  UPDATE INSTRUKTORZY
  SET imie = pImie,
  nazwisko = pNazwisko,
  email = pEmail,
  rozkaz_przyjecia = pRozkaz,
  st_instr = pStInstr,
  st_harc = pStHarc,
  hufiec = NULL
  WHERE imie = pStareImie AND nazwisko = pStareNazwisko;
ELSE
UPDATE INSTRUKTORZY
  SET imie = pImie,
  nazwisko = pNazwisko,
  email = pEmail,
  rozkaz_przyjecia = pRozkaz,
  st_instr = pStInstr,
  st_harc = pStHarc,
  hufiec = pHufiec
  WHERE imie = pStareImie AND nazwisko = pStareNazwisko;
END IF;
  IF SQL%NOTFOUND THEN
    raise_application_error(-20001, 'NO OPERATION');
  END IF;
END;

CREATE OR REPLACE PROCEDURE dodajDruzyne
(
  pNazwa IN VARCHAR,
  pNumer IN VARCHAR,
  pProbna IN VARCHAR,
  pPatron IN VARCHAR,
  pImieNazwisko IN VARCHAR,
  pHufiec IN VARCHAR,
  pTyp IN VARCHAR
)IS
BEGIN
  IF pPatron = '' THEN
    INSERT INTO Druzyny(nazwa, numer, probna, druzynowy, hufiec, typ_druzyny)
    VALUES (pNazwa, TO_NUMBER(pNumer), pProbna, IMIENAZWISKODOID(pImieNazwisko), pHufiec, pTyp);
  ELSE
    INSERT INTO Druzyny(nazwa, numer, probna, patron, druzynowy, hufiec, typ_druzyny)
    VALUES (pNazwa, TO_NUMBER(pNumer), pProbna, pPatron, IMIENAZWISKODOID(pImieNazwisko), pHufiec, pTyp);
  END IF;
END;

CREATE OR REPLACE PROCEDURE usunDruzyne
(
  pNazwa IN VARCHAR,
  pNumer IN VARCHAR
)IS
BEGIN
  DELETE FROM DRUZYNY
  WHERE nazwa = pNazwa AND numer = TO_NUMBER(pNumer);

  IF SQL%NOTFOUND THEN
    raise_application_error(-20001, 'NO OPERATION');
  END IF;
END;

CREATE OR REPLACE PROCEDURE modyfikujDruzyne
(
  pStaraNazwa IN VARCHAR,
  pStaryNumer IN VARCHAR,
  pNazwa IN VARCHAR,
  pNumer IN VARCHAR,
  pProbna IN VARCHAR,
  pPatron IN VARCHAR,
  pImieNazwisko IN VARCHAR,
  pHufiec IN VARCHAR,
  pTyp IN VARCHAR
)IS
BEGIN
  IF pPatron = '' THEN
    UPDATE DRUZYNY
    SET nazwa = pNazwa,
    numer = TO_NUMBER(pNumer),
    probna = pProbna,
    patron = NULL,
    druzynowy = IMIENAZWISKODOID(pImieNazwisko),
    hufiec = pHufiec,
    typ_druzyny = pTyp
    WHERE nazwa = pStaraNazwa AND numer = TO_NUMBER(pStaryNumer);
  ELSE
    UPDATE DRUZYNY
    SET nazwa = pNazwa,
    numer = TO_NUMBER(pNumer),
    probna = pProbna,
    patron = pPatron,
    druzynowy = IMIENAZWISKODOID(pImieNazwisko),
    hufiec = pHufiec,
    typ_druzyny = pTyp
    WHERE nazwa = pStaraNazwa AND numer = TO_NUMBER(pStaryNumer);
  END IF;
  IF SQL%NOTFOUND THEN
    raise_application_error(-20001, 'NO OPERATION');
  END IF;
END;

CREATE OR REPLACE PROCEDURE dodajOkresSladkowy
(
  pKwota IN VARCHAR,
  pData IN VARCHAR
) IS
  vData DATE;
BEGIN
  vData := to_date(pData,'DD-MM-YYYY');
  UPDATE OKRESY_SKLADKOWE
  SET koniec = vData - EXTRACT(DAY FROM vData)
  WHERE koniec IS NULL;
  
  INSERT INTO OKRESY_SKLADKOWE(poczatek, kwota, koniec)
  VALUES(vData - EXTRACT(DAY FROM vData) + 1, TO_NUMBER(pKwota), NULL);
END;

CREATE OR REPLACE PROCEDURE usunOkresSladkowy IS
  vData DATE;
BEGIN
  SELECT poczatek INTO vData FROM OKRESY_SKLADKOWE WHERE koniec IS NULL;

  UPDATE OKRESY_SKLADKOWE SET koniec = NULL WHERE koniec = vData - EXTRACT(DAY FROM vData);
  IF SQL%NOTFOUND THEN
    raise_application_error(-20001, 'NO OPERATION');
  END IF;

  DELETE FROM OKRESY_SKLADKOWE WHERE poczatek = vData;
END;

CREATE OR REPLACE PROCEDURE dodajWplate
(
  pImieNazwisko IN VARCHAR,
  pKwota IN VARCHAR,
  pData IN VARCHAR
) IS
BEGIN
  INSERT INTO wplaty(id_wplaty, kwota, data, instruktor)
  VALUES(wplaty_id_seq.nextval, TO_NUMBER(pKwota), to_date(pData,'DD-MM-YYYY'), IMIENAZWISKODOID(pImieNazwisko));
END;

CREATE OR REPLACE PROCEDURE usunWplate
(
  pID IN VARCHAR
) IS
BEGIN
  DELETE FROM wplaty
  WHERE id_wplaty = TO_NUMBER(pID);
END;

CREATE OR REPLACE PROCEDURE modyfikujWplate
(
  pID IN VARCHAR,
  pImieNazwisko IN VARCHAR,
  pKwota IN VARCHAR,
  pData IN VARCHAR
) IS
BEGIN
  UPDATE wplaty
  SET kwota = TO_NUMBER(pKwota),
  data = to_date(pData,'DD-MM-YYYY'),
  instruktor = IMIENAZWISKODOID(pImieNazwisko)
  WHERE id_wplaty = TO_NUMBER(pID);
END;
--gdfgfdgdf

CREATE OR REPLACE PROCEDURE STOPNIE_INSTRUKTORSKIE_INS
(
	pNazwa IN STOPNIE_INSTRUKTORSKIE.NAZWA%TYPE
) IS
BEGIN
	INSERT INTO STOPNIE_INSTRUKTORSKIE(nazwa)
	VALUES (pNazwa);
END;

CREATE OR REPLACE PROCEDURE STOPNIE_HARCERSKIE_INS
(
	pNazwa IN STOPNIE_HARCERSKIE.NAZWA%TYPE
) IS
BEGIN
	INSERT INTO STOPNIE_HARCERSKIE(nazwa)
	VALUES (pNazwa);
END;

CREATE OR REPLACE PROCEDURE HUFIEC_INS
(
	pNazwa IN HUFCE.NAZWA%TYPE
) IS
BEGIN
	INSERT INTO HUFCE(nazwa)
	VALUES (pNazwa);
END;

CREATE OR REPLACE PROCEDURE TYPY_DRUZYN_INS
(
  pNazwa IN TYPY_DRUZYN.NAZWA%TYPE
) IS
BEGIN
	INSERT INTO TYPY_DRUZYN(nazwa)
	VALUES (pNazwa);
END;

CREATE OR REPLACE PROCEDURE INSTRUKTORZY_INS
(
    pImie IN INSTRUKTORZY.IMIE%TYPE,
    pNazwisko IN INSTRUKTORZY.NAZWISKO%TYPE,
    pRozkaz IN INSTRUKTORZY.ROZKAZ_PRZYJECIA%TYPE,
    pStInstr IN INSTRUKTORZY.ST_HARC%TYPE,
    pStHarc IN INSTRUKTORZY.ST_INSTR%TYPE,
    pHufiec IN INSTRUKTORZY.HUFIEC%TYPE
) IS 
vID INSTRUKTORZY.ID_INSTR%TYPE;
BEGIN
  	vID := instruktorzy_id_seq.nextval;
    INSERT INTO INSTRUKTORZY(id_instr, imie, nazwisko, rozkaz_przyjecia, st_instr, st_harc, hufiec)
    VALUES (vID, pImie, pNazwisko, pRozkaz, pStInstr, pStHarc, pHufiec);
END;
--#################### FUNKCJE #################### 

CREATE OR REPLACE PROCEDURE PrzypiszDoHufca
(
    pIdInstr IN instruktorzy.id_instr%TYPE,
    pHufiec IN instruktorzy.hufiec%TYPE
) IS
BEGIN
--SPRAWDZ CZY NIE JEST HUFCOWYM
    UPDATE INSTRUKTORZY
    SET hufiec = pHufiec
    WHERE id_instr=pIdInstr;
END;

CREATE OR REPLACE PROCEDURE MianujHufcowym
(
    pIdInstr IN instruktorzy.id_instr%TYPE,
    pHufiec IN instruktorzy.hufiec%TYPE
) IS
BEGIN
    PrzypiszDoHufca(pIdInstr, pHufiec);
    
    DELETE FROM hufcowi
    WHERE hufiec = pHufiec;
    INSERT INTO hufcowi(hufiec, hufcowy)
    VALUES(pHufiec, pIdInstr);
END;

CREATE OR REPLACE PROCEDURE DodajStatus
(
	pNazwa IN STATUSY.NAZWA%TYPE
) IS
BEGIN
	INSERT INTO STATUSY(nazwa)
	VALUES (pNazwa);
END;

CREATE OR REPLACE PROCEDURE StanPoczatkowyInstruktora
(
  pPoczatek IN STANY_INSTRUKTOROW.poczatek%TYPE,
  pidInstr IN STANY_INSTRUKTOROW.instruktor%TYPE
)IS
BEGIN
  INSERT INTO STANY_INSTRUKTOROW(poczatek,status,instruktor)
  VALUES (pPoczatek, 'Czynny', pidInstr);
END;

CREATE OR REPLACE PROCEDURE NowyInstruktor_PUB
(
  pPoczatek IN STANY_INSTRUKTOROW.poczatek%TYPE,
  pHufiec IN instruktorzy.hufiec%TYPE,
  pImie IN INSTRUKTORZY.IMIE%TYPE,
  pNazwisko IN INSTRUKTORZY.NAZWISKO%TYPE,
  pRozkaz IN INSTRUKTORZY.ROZKAZ_PRZYJECIA%TYPE,
  pStInstr IN INSTRUKTORZY.ST_HARC%TYPE,
  pStHarc IN INSTRUKTORZY.ST_INSTR%TYPE
) IS
vID INSTRUKTORZY.ID_INSTR%TYPE;
BEGIN
  vID:=NowyInstruktor(pImie,pNazwisko,pRozkaz,pStInstr,pStHarc);
  PrzypiszDoHufca(vID,pHufiec);
  StanPoczatkowyInstruktora(pPoczatek, viD);
END;

CREATE OR REPLACE PROCEDURE ZmianaStanu
(
  pData IN STANY_INSTRUKTOROW.poczatek%TYPE,
  pidInstr IN STANY_INSTRUKTOROW.instruktor%TYPE,
  pStan IN STANY_INSTRUKTOROW.status%TYPE
) IS
BEGIN
  UPDATE STANY_INSTRUKTOROW
  SET koniec = pData
  WHERE pidInstr = instruktor AND koniec is null;
  INSERT INTO STANY_INSTRUKTOROW(poczatek,status,instruktor)
  VALUES (pData, pStan, pidInstr);
END;

CREATE OR REPLACE PROCEDURE KolejnyOkresSkladkowy
(
  pStart IN OKRESY_SKLADKOWE.poczatek%TYPE,
  pKwota IN OKRESY_SKLADKOWE.kwota%TYPE
  --ZMIENIĆ ARGUMENT DATA NA MIESIĄC I ROK--
) IS
vIle NATURAL;
BEGIN
  SELECT COUNT(*)  INTO vILE FROM OKRESY_SKLADKOWE;
  if vILE > 0 then
    UPDATE OKRESY_SKLADKOWE
    SET koniec = pStart - interval '1' month
    WHERE koniec is null;
  end if;
  INSERT INTO OKRESY_SKLADKOWE(poczatek,kwota)
  VALUES (pStart, pKwota);
  
END;

CREATE OR REPLACE PROCEDURE NowaWplata
(
  pInstruktor IN WPLATY.instruktor%TYPE,
  pData IN WPLATY.data%TYPE,
  pKwota IN WPLATY.kwota%TYPE
) IS 
BEGIN
  INSERT INTO WPLATY(id_wplaty, kwota, data, instruktor)
  VALUES (wplaty_id_seq.nextval, pKwota, pData, pInstruktor);
END;

CREATE OR REPLACE FUNCTION DoKiedyOplacone
(
  pIDInstr IN INSTRUKTORZY.id_instr%TYPE
) RETURN DATE IS vData DATE;
vWplacone NATURAL;
BEGIN
  SELECT SUM(kwota) INTO vWplacone from wplaty where instruktor = pIDInstr;
  
  -- NAJWAŻNIEJSZA FUNKCJA--
  
END;

CREATE OR REPLACE PROCEDURE zmienDruzynowego
(
    pNazwa IN druzyny.nazwa%type,
    pNumer IN druzyny.numer%type,
    pIdInstr IN druzyny.druzynowy%type
) IS
    vNowyHufiec druzyny.hufiec%type;
BEGIN
    UPDATE druzyny
    SET druzynowy = pIdInstr
    WHERE druzyny.nazwa = pNazwa AND druzyny.numer = pNumer;
    
    SELECT hufiec
    INTO vNowyHufiec
    FROM druzyny
    WHERE druzyny.nazwa = pNazwa AND druzyny.numer = pNumer;
    
    PrzypiszDoHufca(pIdInstr, vNowyHufiec);
END;

CREATE OR REPLACE PROCEDURE ZmienHufiecDruzyny
(
    pNazwa IN druzyny.nazwa%type,
    pNumer IN druzyny.numer%type,
    pHufiec IN druzyny.hufiec%TYPE
) IS
    vDruzynowy druzyny.druzynowy%type;
BEGIN
    UPDATE druzyny
    SET hufiec = pHufiec
    WHERE druzyny.nazwa = pNazwa AND druzyny.numer = pNumer;
    
    SELECT druzynowy
    INTO vDruzynowy
    FROM druzyny
    WHERE druzyny.nazwa = pNazwa AND druzyny.numer = pNumer;
    
    PrzypiszDoHufca(vDruzynowy, pHufiec);
END;

CREATE OR REPLACE PROCEDURE NowaDruzyna
(
    pNazwa IN druzyny.nazwa%type,
    pNumer IN druzyny.numer%type,
    pProb IN druzyny.probna%type,
    pDruzynowy IN druzyny.druzynowy%type,
    pHufiec IN druzyny.hufiec%type,
    pTyp IN druzyny.typ_druzyny%type
) IS
BEGIN
    INSERT INTO Druzyny(nazwa, numer, probna, druzynowy, hufiec, typ_druzyny)
    VALUES (pNazwa, pNumer, pProb, pDruzynowy, pHufiec, pTyp);
    zmienDruzynowego(pNazwa, pNumer, pDruzynowy);
END;

--#################### INDEKSY #################### 

CREATE INDEX druz_nazw_idx ON druzyny(nazwa);
CREATE INDEX druz_num_idx ON druzyny(numer);
CREATE INDEX instr_nazw_idx ON instruktorzy(nazwisko);
CREATE INDEX instr_imie_idx ON instruktorzy(imie);
CREATE BITMAP INDEX instr_hufiec_bmp_idx ON instruktorzy(hufiec);
CREATE BITMAP INDEX instr_stT_bmp_idx ON instruktorzy(st_instr);
CREATE BITMAP INDEX instr_stH_bmp_idx ON instruktorzy(st_harc);
CREATE BITMAP INDEX stany_instr_bmp_idx ON stany_instruktorow(status);


