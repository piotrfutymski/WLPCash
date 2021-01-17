#pragma once
#include "PopUpFrame.h"

class ChooseWplatyFrame : public PopUpFrame
{
public:
    ChooseWplatyFrame(int ID);

    virtual void reload();

    void fillInstruktorData(const std::vector<std::wstring> & hD);

    void setOnAll(const std::function<void()> & f);
    void setOnConcrete(const std::function<void()> & f);

    std::wstring getInstruktor();

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;
    
    std::unique_ptr<wxListBox> _instruktorInput;

    std::unique_ptr<wxButton> _chooseAllButton;
    std::unique_ptr<wxButton> _chooseConcreteButton;

    //functions

    std::function<void()> _onAll;
    std::function<void()> _onConcrete;


    //DATA

    std::vector<std::wstring> _instruktorData;


private:

    enum class ID
    {
        INSTRUKTOR = 1, ALL, CONCRETE
    };

private:

    void onAll(wxCommandEvent & event);
    void onConcrete(wxCommandEvent & event);

};
