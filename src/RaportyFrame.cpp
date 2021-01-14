#include "RaportyFrame.h"

RaportyFrame::RaportyFrame(int ID)
    : PopUpFrame(NULL, ID, wxT("Wybór raportu"), wxDefaultPosition, wxSize(880, 280+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _labels[0] = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Wpłaty indywidualne od - do (dd-mm-rrrr):"), wxPoint(20,50), wxSize(300,30));
    _labels[1] = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Wpłaty na hufiec od - do (dd-mm-rrrr):"), wxPoint(20,100), wxSize(300,30));
    _labels[2] = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Do kiedy uzupełnione wpłaty:"), wxPoint(20,150), wxSize(300,30));
    _labels[3] = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Opuźnienia we wpłatach sprzed (dd-mm-rrrr):"), wxPoint(20,200), wxSize(300,50));

    _dataDCtrl[0] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_D), wxT(""), wxPoint(360,50), wxSize(40,30));
    _dataDCtrl[1] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_D)+1, wxT(""), wxPoint(560,50), wxSize(40,30));
    _dataDCtrl[2] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_D)+2, wxT(""), wxPoint(360,100), wxSize(40,30));
    _dataDCtrl[3] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_D)+3, wxT(""), wxPoint(560,100), wxSize(40,30));
    _dataDCtrl[4] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_D)+4, wxT(""), wxPoint(360,200), wxSize(40,30));

    _dataMCtrl[0] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M), wxT(""), wxPoint(410,50), wxSize(40,30));
    _dataMCtrl[1] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M)+1, wxT(""), wxPoint(610,50), wxSize(40,30));
    _dataMCtrl[2] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M)+2, wxT(""), wxPoint(410,100), wxSize(40,30));
    _dataMCtrl[3] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M)+3, wxT(""), wxPoint(610,100), wxSize(40,30));
    _dataMCtrl[4] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M)+4, wxT(""), wxPoint(410,200), wxSize(40,30));

    _dataRCtrl[0] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R), wxT(""), wxPoint(460,50), wxSize(80,30));
    _dataRCtrl[1] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R)+1, wxT(""), wxPoint(660,50), wxSize(80,30));
    _dataRCtrl[2] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R)+2, wxT(""), wxPoint(460,100), wxSize(80,30));
    _dataRCtrl[3] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R)+3, wxT(""), wxPoint(660,100), wxSize(80,30));
    _dataRCtrl[4] = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R)+4, wxT(""), wxPoint(460,200), wxSize(80,30));

    _generateButton[0] = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::GEN), wxT("GENERUJ"), wxPoint(760, 50), wxSize(90,30));
    _generateButton[1] = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::GEN)+1, wxT("GENERUJ"), wxPoint(760, 100), wxSize(90,30));
    _generateButton[2] = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::GEN)+2, wxT("GENERUJ"), wxPoint(760, 150), wxSize(90,30));
    _generateButton[3] = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::GEN)+3, wxT("GENERUJ"), wxPoint(760, 200), wxSize(90,30));

    for(int i = 0; i < 4; i++)
    {
        Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this, i]( wxCommandEvent &){
            this->onGenerate(i);
        }, wxWindowID(ID::GEN) + i);
    }

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(RaportyFrame::close));
}

void RaportyFrame::reload()
{

}

void RaportyFrame::setOnGenerate(const std::function<void(const std::vector<std::string> &)> & f, int n)
{
    _onGenerate[n] = f;
}

void RaportyFrame::onGenerate(int n)
{
    if(_onGenerate[n])
    {
        if(n == 0)
            _onGenerate[n]({std::string(_dataDCtrl[0]->GetValue()), std::string(_dataMCtrl[0]->GetValue()),std::string(_dataRCtrl[0]->GetValue()),
            std::string(_dataDCtrl[1]->GetValue()), std::string(_dataMCtrl[1]->GetValue()),std::string(_dataRCtrl[1]->GetValue())});
        if(n == 1)
            _onGenerate[n]({std::string(_dataDCtrl[2]->GetValue()), std::string(_dataMCtrl[2]->GetValue()),std::string(_dataRCtrl[2]->GetValue()),
            std::string(_dataDCtrl[3]->GetValue()), std::string(_dataMCtrl[3]->GetValue()),std::string(_dataRCtrl[3]->GetValue())});
        if(n == 2)
            _onGenerate[n]({});
        if(n == 3)
            _onGenerate[n]({std::string(_dataDCtrl[4]->GetValue()), std::string(_dataMCtrl[4]->GetValue()),std::string(_dataRCtrl[4]->GetValue())});
    }
        
}