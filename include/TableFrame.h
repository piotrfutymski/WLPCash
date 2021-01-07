#include <memory>
#include <vector>
#include <wx/wx.h>

class TableFrame : public wxFrame
{
public:

    TableFrame(const std::string & name, int len, int ID, const std::vector<std::pair<std::string, int>> & labelData, bool specialButton = false);

    bool isOpened()const;

    void fillData(const std::vector<std::vector<std::string>> & data);

    void reload();

    bool Show();



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
    bool _isOpened = false;

private:

    enum class ID
    {
        PREV = 1, NEXT, ADD, DELETE = 100, MODIFY = 200, SPECIAL=300, LABELS=400
    };

private:

    void close(wxCommandEvent & event);

};