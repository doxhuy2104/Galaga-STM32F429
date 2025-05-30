#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <images/BitmapDatabase.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
protected:
    uint32_t tickCount;
        int16_t bg0Y;
        int16_t bg1Y;
        uint8_t changeBg;
private:
    touchgfx::Image galagaImage;
};

#endif // SCREEN2VIEW_HPP
