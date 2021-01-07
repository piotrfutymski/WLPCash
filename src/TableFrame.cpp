#include "TableFrame.h"


TableFrame::TableFrame(const std::string & name, int len, int ID, const std::vector<std::pair<std::string, int>> & labelData, bool specialButton)
    : wxFrame(NULL, ID, name, wxDefaultPosition, wxSize(310+len, 510+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), _labelData(labelData)
{
    _panel = std::make_unique<wxPanel>(this, -1);
    wxFont smallFont(7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);

    _prevButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::PREV), wxT("poprzednie"), wxPoint(20,40), wxSize(60,20));
    _prevButton->SetFont(smallFont);

    _nextButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::NEXT), wxT("następne"), wxPoint(20,460), wxSize(60,20));
    _nextButton->SetFont(smallFont);

    _addButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::ADD), wxT("DODAJ"), wxPoint(100,460), wxSize(len,30));

    _pageInfo = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, "0-0", wxPoint(20,10), wxSize(60,20));

    int px = 100;

    for(auto & p : labelData)
    {
        _labels.emplace_back(std::make_unique<wxStaticText>(
            _panel.get(), wxWindowID(ID::LABELS), p.first, wxPoint(px, 40), wxSize(p.second, 20)
        ));
        px += p.second;
        (*(_labels.end()-1))->SetBackgroundColour(wxColor(180,180,180));
    }

    int py = 70;

    for(int i = 0; i < 10; i++)
    {
        _rows[i] = std::make_unique<wxTextCtrl>(_panel.get(), wxID_ANY, wxT(""), wxPoint(100, py+40*i), wxSize(len, 30), wxTE_READONLY);
        _deleteButton[i] =  std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::DELETE) + i, wxT("DEL"), wxPoint(100+len+80,py+40*i), wxSize(50,30));
        _modifyButton[i] =  std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::MODIFY) + i, wxT("MODIFY"), wxPoint(100+len+10,py+40*i), wxSize(60,30));
        if(specialButton)
            _specialButton[i] = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::SPECIAL) + i, wxT("STAN"), wxPoint(100+len+140,py+40*i), wxSize(50,30));
    }

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(TableFrame::close));

}

bool TableFrame::isOpened()const
{
    return _isOpened;
}

void TableFrame::fillData(const std::vector<std::vector<std::string>> & data)
{
    _data = data;
}

void TableFrame::reload()
{
    if(_data.size() < 10)
    {
        _pageInfo->SetLabel("1-" + std::to_string(_data.size()));
    }
    else
    {
        _pageInfo->SetLabel("1-10");
    }
    
    for(int i = 0; i < 10; i++)
    {
        if( i >= _data.size())
            break;
        _rows[i]->Clear();
        int px = 0;
        auto it = _data[i].begin();
        for(auto &p : _labelData)
        {
            px += p.second;
            _rows[i]->WriteText(*it++);
            int x, y;
            if(it == _data[i].end())
                break;
            do{
                _rows[i]->WriteText(" ");
                _rows[i]->GetTextExtent(_rows[i]->GetLineText(0), &x, &y);
                
            }while(x < px-10);      
            
        }
        
    }
}

bool TableFrame::Show()
{
    _isOpened = true;
    return wxFrame::Show();
}

void TableFrame::close(wxCommandEvent& WXUNUSED(event))
{
    _isOpened = false;
    wxFrame::Hide();
}