CREATE TABLE STOPNIE_INSTRUKTORSKIE(
    nazwa VARCHAR(64) PRIMARY KEY
); CREATE TABLE STOPNIE_HARCERSKIE(
    nazwa VARCHAR(64) PRIMARY KEY
); CREATE TABLE HUFCE(
    nazwa VARCHAR(64) PRIMARY KEY
); CREATE TABLE HUFCOWI(
    hufiec VARCHAR(64) REFERENCES HUFCE(nazwa),
    hufcowy NUMERIC(6) NOT NULL REFERENCES INSTRUKTORZY(id_instr),
    PRIMARY KEY(hufiec)
); CREATE TABLE INSTRUKTORZY(
    id_instr NUMERIC(6) PRIMARY KEY,
    imie VARCHAR(64) NOT NULL,
    nazwisko VARCHAR(64) NOT NULL,
    email VARCHAR(64) NOT NULL,
    rozkaz_przyjecia VARCHAR(64) NOT NULL,
    st_instr VARCHAR(64) NOT NULL REFERENCES STOPNIE_INSTRUKTORSKIE(nazwa),
    st_harc VARCHAR(64) NOT NULL REFERENCES STOPNIE_HARCERSKIE(nazwa),
    hufiec VARCHAR(64) REFERENCES HUFCE(nazwa)
); CREATE TABLE TYPY_DRUZYN(
    nazwa VARCHAR(64) PRIMARY KEY,
    min_wiek NUMERIC(3) NOT NULL,
    max_wiek NUMERIC(3) NOT NULL
); CREATE TABLE DRUZYNY(
    nazwa VARCHAR(64),
    numer NUMERIC(6),
    probna CHAR(1) NOT NULL,
    patron VARCHAR(64),
    druzynowy NUMERIC(6) NOT NULL REFERENCES INSTRUKTORZY(id_instr),
    hufiec VARCHAR(64) NOT NULL REFERENCES HUFCE(nazwa),
    typ_druzyny VARCHAR(64) NOT NULL REFERENCES TYPY_DRUZYN(nazwa),
    PRIMARY KEY(nazwa, numer)
); CREATE TABLE STATUSY(
    nazwa VARCHAR(64) PRIMARY KEY
); CREATE TABLE STANY_INSTRUKTOROW(
    poczatek DATE,
    koniec DATE,
    STATUS
        VARCHAR(64) NOT NULL REFERENCES STATUSY(nazwa),
        instruktor NUMERIC(6) REFERENCES INSTRUKTORZY(id_instr),
        PRIMARY KEY(poczatek, instruktor)
);
CREATE TABLE OKRESY_SKLADKOWE(
    poczatek DATE PRIMARY KEY,
    kwota NUMERIC(8, 2) NOT NULL,
    koniec DATE
); CREATE TABLE WPLATY(
    id_wplaty NUMERIC(6) PRIMARY KEY,
    kwota NUMERIC(8, 2) NOT NULL,
    DATA DATE NOT NULL,
    instruktor NUMERIC(6) NOT NULL REFERENCES INSTRUKTORZY(id_instr)
); 
-- ###################### SEKWENCJE ########################################
CREATE SEQUENCE wplaty_id_seq START WITH 1 INCREMENT BY 1; CREATE SEQUENCE instruktorzy_id_seq START WITH 1 INCREMENT BY 1;
-- ###################### PODPROGRAMY ######################################
CREATE OR REPLACE PROCEDURE DodajStopienInstruktorski(
    pNazwa IN STOPNIE_INSTRUKTORSKIE.NAZWA % TYPE
) IS
BEGIN
    INSERT INTO STOPNIE_INSTRUKTORSKIE(nazwa)
VALUES(pNazwa);
END;
CREATE OR REPLACE PROCEDURE DodajStopienHarcerski(
    pNazwa IN STOPNIE_HARCERSKIE.NAZWA % TYPE
) IS
BEGIN
    INSERT INTO STOPNIE_HARCERSKIE(nazwa)
VALUES(pNazwa);
END;
CREATE OR REPLACE PROCEDURE StworzHufiec(pNazwa IN HUFCE.NAZWA % TYPE) IS
BEGIN
    INSERT INTO HUFCE(nazwa)
VALUES(pNazwa);
END;
CREATE OR REPLACE FUNCTION NowyInstruktor(
    pImie IN INSTRUKTORZY.IMIE % TYPE,
    pNazwisko IN INSTRUKTORZY.NAZWISKO % TYPE,
    pRozkaz IN INSTRUKTORZY.ROZKAZ_PRZYJECIA % TYPE,
    pStInstr IN INSTRUKTORZY.ST_HARC % TYPE,
    pStHarc IN INSTRUKTORZY.ST_INSTR % TYPE
) RETURN INSTRUKTORZY.ID_INSTR % TYPE IS vID INSTRUKTORZY.ID_INSTR % TYPE; BEGIN
        vID : = instruktorzy_id_seq.nextval;
    INSERT INTO INSTRUKTORZY(
        id_instr,
        imie,
        nazwisko,
        rozkaz_przyjecia,
        st_instr,
        st_harc
    )
VALUES(
    vID,
    pImie,
    pNazwisko,
    pRozkaz,
    pStInstr,
    pStHarc
); RETURN vID;
    END;
CREATE OR REPLACE PROCEDURE PrzypiszDoHufca(
    pIdInstr IN instruktorzy.id_instr % TYPE,
    pHufiec IN instruktorzy.hufiec % TYPE
) IS
BEGIN
        - - SPRAWDZ CZY NIE JEST HUFCOWYM
    UPDATE
        INSTRUKTORZY
    SET
        hufiec = pHufiec
    WHERE
        id_instr = pIdInstr;
    END;
CREATE OR REPLACE PROCEDURE MianujHufcowym(
    pIdInstr IN instruktorzy.id_instr % TYPE,
    pHufiec IN instruktorzy.hufiec % TYPE
) IS
BEGIN
        PrzypiszDoHufca(pIdInstr, pHufiec);
    DELETE
FROM
    hufcowi
WHERE
    hufiec = pHufiec;
INSERT INTO hufcowi(hufiec, hufcowy)
VALUES(pHufiec, pIdInstr);
    END;
CREATE OR REPLACE PROCEDURE DodajStatus(pNazwa IN STATUSY.NAZWA % TYPE) IS
BEGIN
    INSERT INTO STATUSY(nazwa)
VALUES(pNazwa);
END;
CREATE OR REPLACE PROCEDURE StanPoczatkowyInstruktora(
    pPoczatek IN STANY_INSTRUKTOROW.poczatek % TYPE,
    pidInstr IN STANY_INSTRUKTOROW.instruktor % TYPE
) IS
BEGIN
    INSERT INTO STANY_INSTRUKTOROW(poczatek,
STATUS
    , instruktor)
VALUES(pPoczatek, 'Czynny', pidInstr);
END;
CREATE OR REPLACE PROCEDURE NowyInstruktor_PUB(
    pPoczatek IN STANY_INSTRUKTOROW.poczatek % TYPE,
    pHufiec IN instruktorzy.hufiec % TYPE,
    pImie IN INSTRUKTORZY.IMIE % TYPE,
    pNazwisko IN INSTRUKTORZY.NAZWISKO % TYPE,
    pRozkaz IN INSTRUKTORZY.ROZKAZ_PRZYJECIA % TYPE,
    pStInstr IN INSTRUKTORZY.ST_HARC % TYPE,
    pStHarc IN INSTRUKTORZY.ST_INSTR % TYPE
) IS vID INSTRUKTORZY.ID_INSTR % TYPE;
BEGIN
        vID: = NowyInstruktor(
            pImie,
            pNazwisko,
            pRozkaz,
            pStInstr,
            pStHarc
        ); PrzypiszDoHufca(vID, pHufiec); StanPoczatkowyInstruktora(pPoczatek, viD);
    END;
CREATE OR REPLACE PROCEDURE ZmianaStanu(
    pData IN STANY_INSTRUKTOROW.poczatek % TYPE,
    pidInstr IN STANY_INSTRUKTOROW.instruktor % TYPE,
    pStan IN STANY_INSTRUKTOROW.status % TYPE
) IS
BEGIN
    UPDATE
        STANY_INSTRUKTOROW
    SET
        koniec = pData
    WHERE
        pidInstr = instruktor AND koniec IS NULL;
    INSERT INTO STANY_INSTRUKTOROW(poczatek,
STATUS
    , instruktor)
VALUES(pData, pStan, pidInstr);
END;
CREATE OR REPLACE PROCEDURE KolejnyOkresSkladkowy(
    pStart IN OKRESY_SKLADKOWE.poczatek % TYPE,
    pKwota IN OKRESY_SKLADKOWE.kwota % TYPE - - ZMIENIĆ ARGUMENT DATA NA MIESIĄC I ROK --

) IS vIle NATURAL;
BEGIN
    SELECT
        COUNT(*)
    INTO vILE
FROM
    OKRESY_SKLADKOWE; IF vILE > 0 THEN
UPDATE
    OKRESY_SKLADKOWE
SET
    koniec = pStart - INTERVAL '1' MONTH
WHERE
    koniec IS NULL;
END IF;
INSERT INTO OKRESY_SKLADKOWE(poczatek, kwota)
VALUES(pStart, pKwota);
END;
CREATE OR REPLACE PROCEDURE NowaWplata(
    pInstruktor IN WPLATY.instruktor % TYPE,
    pData IN WPLATY.data % TYPE,
    pKwota IN WPLATY.kwota % TYPE
) IS
BEGIN
    INSERT INTO WPLATY(
        id_wplaty,
        kwota,
        DATA,
        instruktor
    )
VALUES(
    wplaty_id_seq.nextval,
    pKwota,
    pData,
    pInstruktor
);
END;
CREATE OR REPLACE FUNCTION DoKiedyOplacone(
    pIDInstr IN INSTRUKTORZY.id_instr % TYPE
) RETURN DATE IS vData DATE; vWplacone NATURAL; BEGIN
    SELECT
        SUM(kwota)
    INTO vWplacone
FROM
    wplaty
WHERE
    instruktor = pIDInstr;
    -- NAJWAŻNIEJSZA FUNKCJA--
END;
CREATE OR REPLACE PROCEDURE zmienDruzynowego(
    pNazwa IN druzyny.nazwa % TYPE,
    pNumer IN druzyny.numer % TYPE,
    pIdInstr IN druzyny.druzynowy % TYPE
) IS vNowyHufiec druzyny.hufiec % TYPE;
BEGIN
    UPDATE
        druzyny
    SET
        druzynowy = pIdInstr
    WHERE
        druzyny.nazwa = pNazwa AND druzyny.numer = pNumer;
    SELECT
        hufiec
    INTO vNowyHufiec
FROM
    druzyny
WHERE
    druzyny.nazwa = pNazwa AND druzyny.numer = pNumer; PrzypiszDoHufca(pIdInstr, vNowyHufiec);
END;
CREATE OR REPLACE PROCEDURE ZmienHufiecDruzyny(
    pNazwa IN druzyny.nazwa % TYPE,
    pNumer IN druzyny.numer % TYPE,
    pHufiec IN druzyny.hufiec % TYPE
) IS vDruzynowy druzyny.druzynowy % TYPE;
BEGIN
    UPDATE
        druzyny
    SET
        hufiec = pHufiec
    WHERE
        druzyny.nazwa = pNazwa AND druzyny.numer = pNumer;
    SELECT
        druzynowy
    INTO vDruzynowy
FROM
    druzyny
WHERE
    druzyny.nazwa = pNazwa AND druzyny.numer = pNumer; PrzypiszDoHufca(vDruzynowy, pHufiec);
END;
CREATE OR REPLACE PROCEDURE NowaDruzyna(
    pNazwa IN druzyny.nazwa % TYPE,
    pNumer IN druzyny.numer % TYPE,
    pProb IN druzyny.probna % TYPE,
    pDruzynowy IN druzyny.druzynowy % TYPE,
    pHufiec IN druzyny.hufiec % TYPE,
    pTyp IN druzyny.typ_druzyny % TYPE
) IS
BEGIN
    INSERT INTO Druzyny(
        nazwa,
        numer,
        probna,
        druzynowy,
        hufiec,
        typ_druzyny
    )
VALUES(
    pNazwa,
    pNumer,
    pProb,
    pDruzynowy,
    pHufiec,
    pTyp
); zmienDruzynowego(pNazwa, pNumer, pDruzynowy);
END; - - ################# INDEKSY ##########################################
CREATE INDEX druz_nazw_idx ON
    druzyny(nazwa);
CREATE INDEX druz_num_idx ON
    druzyny(numer);
CREATE INDEX instr_nazw_idx ON
    instruktorzy(nazwisko);
CREATE INDEX instr_imie_idx ON
    instruktorzy(imie);
CREATE BITMAP INDEX instr_hufiec_bmp_idx ON
    instruktorzy(hufiec);
CREATE BITMAP INDEX instr_stT_bmp_idx ON
    instruktorzy(st_instr);
CREATE BITMAP INDEX instr_stH_bmp_idx ON
    instruktorzy(st_harc);
CREATE BITMAP INDEX stany_instr_bmp_idx ON
    stany_instruktorow(
STATUS
);