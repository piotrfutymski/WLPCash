#pragma once
#include "PopUpFrame.h"

class RaportyFrame : public PopUpFrame
{
public:
    RaportyFrame(int ID);

    virtual void reload();

    void setOnGenerate(const std::function<void(const std::vector<std::wstring> &)> & f, int n);

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _labels[4];
    std::unique_ptr<wxTextCtrl> _dataDCtrl[5];
    std::unique_ptr<wxTextCtrl> _dataMCtrl[5];
    std::unique_ptr<wxTextCtrl> _dataRCtrl[5];

    std::unique_ptr<wxButton> _generateButton[4];

    //functions

    std::function<void(const std::vector<std::wstring> &)> _onGenerate[4];


private:

    enum class ID
    {
        DATA_D = 1, DATA_M=10, DATA_R=20, GEN=30
    };

private:

    void onGenerate(int n);

};
