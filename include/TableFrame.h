#pragma once
#include <functional>
#include "PopUpFrame.h"
#undef DELETE

class TableFrame : public PopUpFrame
{
public:

    enum class TableStyle
    {
        None, Special, OnlyLast, Raport, Raport_Mail
    };

    TableFrame(const std::string & name, int len, int ID, const std::vector<std::pair<std::string, int>> & labelData, const TableStyle & style = TableStyle::None);

    void fillData(const std::vector<std::vector<std::string>> & data);

    virtual void reload();

    void setOnAdd(const std::function<void()> & f);
    void setOnModify(const std::function<void(int)> & f);
    void setOnDel(const std::function<void(int)> & f);
    void setOnSpec(const std::function<void(int)> & f);
    void setOnGetRaport(const std::function<void()> & f);
    void setOnGetEmail(const std::function<void()> & f);


private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxButton> _prevButton;
    std::unique_ptr<wxButton> _nextButton;

    std::unique_ptr<wxButton> _addButton;
    std::unique_ptr<wxButton> _deleteButton[10];
    std::unique_ptr<wxButton> _modifyButton[10];
    std::unique_ptr<wxButton> _specialButton[10];

    std::vector<std::unique_ptr<wxStaticText>> _labels;
    
    std::unique_ptr<wxStaticText> _pageInfo;

    std::unique_ptr<wxTextCtrl> _rows[10];

    //Data

    std::vector<std::vector<std::string>> _data;
    std::vector<std::pair<std::string, int>> _labelData;
    int _page = 0;

    // style

    TableStyle _style;

    // functions

    std::function<void()> _onAdd;
    std::function<void(int)> _onModify;
    std::function<void(int)> _onDelete;
    std::function<void(int)> _onSpecial;
    std::function<void()> _onGetRaport;
    std::function<void()> _onGetEmail;

private:

    enum class ID
    {
        PREV = 1, NEXT, ADD, DELETE = 100, MODIFY = 200, SPECIAL=300, LABELS=400
    };

private:

    void onAdd(wxCommandEvent & event);
    void onModify(wxCommandEvent & event);
    void onDelete(wxCommandEvent & event);
    void onSpecial(wxCommandEvent & event);
    void onGetReport(wxCommandEvent & event);
    void onGetEmail(wxCommandEvent & event);

};