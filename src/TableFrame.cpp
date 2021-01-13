#include "TableFrame.h"


TableFrame::TableFrame(const std::string & name, int len, int ID, const std::vector<std::pair<std::string, int>> & labelData, const TableStyle & style)
    : PopUpFrame(NULL, ID, name, wxDefaultPosition, wxSize(310+len, 510+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), _labelData(labelData), _style(style)
{
    _panel = std::make_unique<wxPanel>(this, -1);
    wxFont smallFont(7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);

    _prevButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::PREV), wxT("poprzednie"), wxPoint(20,40), wxSize(60,20));
    _prevButton->SetFont(smallFont);

    _nextButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::NEXT), wxT("następne"), wxPoint(20,460), wxSize(60,20));
    _nextButton->SetFont(smallFont);

    if(_style == TableStyle::Special || _style == TableStyle::None || _style == TableStyle::OnlyLast)
        _addButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::ADD), wxT("DODAJ"), wxPoint(100,460), wxSize(len,30));

    _pageInfo = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, "0-0", wxPoint(20,10), wxSize(60,20));

    _raportButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::RAPORT), wxT("ZAPISZ"), wxPoint(100+len+100,470), wxSize(90,30));

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
        if(_style == TableStyle::Special || _style == TableStyle::None || _style == TableStyle::OnlyLast)
            _deleteButton[i] =  std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::DELETE) + i, wxT("DEL"), wxPoint(100+len+80,py+40*i), wxSize(50,30));
        if(_style == TableStyle::Special || _style == TableStyle::None)
            _modifyButton[i] =  std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::MODIFY) + i, wxT("MODIFY"), wxPoint(100+len+10,py+40*i), wxSize(60,30));
        if(_style == TableStyle::Special)
            _specialButton[i] = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::SPECIAL) + i, wxT("STAN"), wxPoint(100+len+140,py+40*i), wxSize(50,30));
    }

    //EVENTS

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(TableFrame::close));
    Connect(wxWindowID(ID::ADD), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TableFrame::onAdd));
    Connect(wxWindowID(ID::NEXT), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TableFrame::onNext));
    Connect(wxWindowID(ID::PREV), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TableFrame::onPrevious));
    Connect(wxWindowID(ID::RAPORT), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TableFrame::onRaport));



    for(int i = 0; i < 10; i++ )
    {
        Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this, i]( wxCommandEvent &){
            this->onSpecial(i);
        }, wxWindowID(ID::SPECIAL) + i);

        Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this, i]( wxCommandEvent &){
            this->onDelete(i);
        }, wxWindowID(ID::DELETE) + i);

        Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this, i]( wxCommandEvent &){
            this->onModify(i);
        }, wxWindowID(ID::MODIFY) + i);
    }

}

void TableFrame::fillData(const std::vector<std::vector<std::string>> & data)
{
    _data = data;
}

void TableFrame::reload()
{
    setPage(0);
}


void TableFrame::setOnAdd(const std::function<void()> & f)
{
    _onAdd = f;
}

void TableFrame::setOnModify(const std::function<void(const std::vector<std::string> &)> & f)
{
    _onModify = f;
}

void TableFrame::setOnDel(const std::function<void(const std::vector<std::string> &)> & f)
{
    _onDelete = f;
}

void TableFrame::setOnSpec(const std::function<void(const std::vector<std::string> &)> & f)
{
    _onSpecial = f;
}

void TableFrame::setValue(const std::string & v)
{
    _value = v;
}

std::string TableFrame::getValue()
{
    return _value;
}


void TableFrame::onAdd(wxCommandEvent& WXUNUSED(event))
{
    if(_onAdd)
        _onAdd();
}

void TableFrame::onSpecial(int n)
{
    if(_onSpecial && _data.size() > _page*10 + n)
        _onSpecial(_data[_page*10 + n]);

}

void TableFrame::onDelete(int n)
{
    if(_style == TableStyle::OnlyLast)
    {
        if(_onDelete && _data.size() - 1 == _page*10 + n)
        {
            _onDelete(_data[_page*10 + n]);          
        }
        return;
    }
       

    if(_onDelete && _data.size() > _page*10 + n)
        _onDelete(_data[_page*10 + n]);

}

void TableFrame::onModify(int n)
{
    if(_onModify && _data.size() > _page*10 + n)
        _onModify(_data[_page*10 + n]);
}


void TableFrame::onPrevious(wxCommandEvent& WXUNUSED(event))
{
    setPage(_page - 1);
}
void TableFrame::onNext(wxCommandEvent& WXUNUSED(event))
{
    setPage(_page + 1);
}

void TableFrame::setPage(int p)
{
    if(p < 0)
        return;

    if(p > (_data.size()-1)/10)
        return;

    _page = p;
    if(_data.size() == 0)
    {
        _pageInfo->SetLabel("0-0 /0");
    }
    else
    {
        int s = _page * 10 + 1;
        int e = (_page + 1)*10;
        if(e > _data.size())
            e = _data.size();
        _pageInfo->SetLabel(std::to_string(s)+"-"+std::to_string(e)+" /" + std::to_string(_data.size()));
    }
    for(int i = 0; i < 10; i++)
    {
        _rows[i]->Clear();
        if( i + _page * 10 >= _data.size())
            continue;
        
        int px = 0;
        auto it = _data[i + _page * 10].begin();
        for(auto &p : _labelData)
        {
            px += p.second;
            _rows[i]->WriteText(*it++);
            int x, y;
            if(it == _data[i + _page * 10].end())
                break;
            do{
                _rows[i]->WriteText(" ");
                _rows[i]->GetTextExtent(_rows[i]->GetLineText(0), &x, &y);
                
            }while(x < px-10);      
            
        }
        
    }
}


void TableFrame::onRaport(wxCommandEvent & event)
{

}