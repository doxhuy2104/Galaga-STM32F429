#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
protected:
    uint32_t tickCount;
        int16_t bg0Y;
        int16_t bg1Y;
        uint8_t changeBg;
        uint8_t iAlp;
        uint8_t dAlp;
};

#endif // MAINSCREENVIEW_HPP
