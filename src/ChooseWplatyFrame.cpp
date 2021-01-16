#include "ChooseWplatyFrame.h"


ChooseWplatyFrame::ChooseWplatyFrame(int ID)
    : PopUpFrame(NULL, ID, wxT(""), wxDefaultPosition, wxSize(620, 250+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _chooseAllButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::ALL), wxT("Wszystkie wpłaty"), wxPoint(160,50), wxSize(300,50));

    _instruktorInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::INSTRUKTOR), wxPoint(40,120), wxSize(220,70));
    _chooseConcreteButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::CONCRETE), wxT("Wpłaty instruktora"), wxPoint(280,120), wxSize(300,50));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(ChooseWplatyFrame::close));
    Connect(wxWindowID(ID::ALL), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ChooseWplatyFrame::onAll));
    Connect(wxWindowID(ID::CONCRETE), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ChooseWplatyFrame::onConcrete));
}

void ChooseWplatyFrame::reload()
{
    _instruktorInput->Clear();
    for(auto & std: _instruktorData)
        _instruktorInput->Append(std);

    if(_instruktorData.size() != 0)
        _instruktorInput->SetSelection(0);
}

void ChooseWplatyFrame::fillInstruktorData(const std::vector<std::string> & hD)
{
    _instruktorData = hD;
}

void ChooseWplatyFrame::setOnAll(const std::function<void()> & f)
{
    _onAll = f;
}

void ChooseWplatyFrame::setOnConcrete(const std::function<void()> & f)
{
    _onConcrete = f;
}

std::string ChooseWplatyFrame::getInstruktor()
{

    if(_instruktorInput->GetSelection() == -1)
        return "";
    else
        return std::string(_instruktorInput->GetString(_instruktorInput->GetSelection()));
}


void ChooseWplatyFrame::onAll(wxCommandEvent & event)
{
    if(_onAll)
        _onAll();
}
void ChooseWplatyFrame::onConcrete(wxCommandEvent & event)
{
    if(_onConcrete)
        _onConcrete();
}