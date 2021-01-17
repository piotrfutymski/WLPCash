#pragma once
#include <functional>
#include <fstream>
#include "PopUpFrame.h"
#undef DELETE

class TableFrame : public PopUpFrame
{
public:

    enum class TableStyle
    {
        None, Special, OnlyLast, Raport, Raport_Mail
    };

    TableFrame(const std::wstring & name, int len, int ID, const std::vector<std::pair<std::wstring, int>> & labelData, const TableStyle & style = TableStyle::None);

    void fillData(const std::vector<std::vector<std::wstring>> & data);

    virtual void reload();

    void setOnAdd(const std::function<void()> & f);
    void setOnModify(const std::function<void(const std::vector<std::wstring> &)> & f);
    void setOnDel(const std::function<void(const std::vector<std::wstring> &)> & f);
    void setOnSpec(const std::function<void(const std::vector<std::wstring> &)> & f);

    void setValue(const std::wstring & v);
    std::wstring getValue();


private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxButton> _prevButton;
    std::unique_ptr<wxButton> _nextButton;

    std::unique_ptr<wxButton> _addButton;
    std::unique_ptr<wxButton> _deleteButton[10];
    std::unique_ptr<wxButton> _modifyButton[10];
    std::unique_ptr<wxButton> _specialButton[10];

    std::unique_ptr<wxButton> _raportButton;
    std::unique_ptr<wxButton> _emailButton;

    std::vector<std::unique_ptr<wxStaticText>> _labels;
    
    std::unique_ptr<wxStaticText> _pageInfo;

    std::unique_ptr<wxTextCtrl> _rows[10];

    //Data

    std::vector<std::vector<std::wstring>> _data;
    std::vector<std::pair<std::wstring, int>> _labelData;
    int _page = 0;

    std::wstring _value;

    // style

    TableStyle _style;

    // functions

    std::function<void()> _onAdd;
    std::function<void(const std::vector<std::wstring> &)> _onModify;
    std::function<void(const std::vector<std::wstring> &)> _onDelete;
    std::function<void(const std::vector<std::wstring> &)> _onSpecial;

private:

    enum class ID
    {
        PREV = 1, NEXT, ADD, RAPORT, EMAIL, DELETE = 100, MODIFY = 200, SPECIAL=300, LABELS=400
    };

private:

    void onAdd(wxCommandEvent & event);
    void onModify(int n);
    void onDelete(int n);
    void onSpecial(int n);

    void onPrevious(wxCommandEvent & event);
    void onNext(wxCommandEvent & event);
    void onRaport(wxCommandEvent & event);

    void setPage(int p);

};
