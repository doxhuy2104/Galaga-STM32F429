#ifndef GAMESCREENVIEW_HPP
#define GAMESCREENVIEW_HPP

#include <gui_generated/gamescreen_screen/GameScreenViewBase.hpp>
#include <gui/gamescreen_screen/GameScreenPresenter.hpp>
#include <images/BitmapDatabase.hpp>
#include <Game.hpp>
class GameScreenView : public GameScreenViewBase
{
public:
    GameScreenView();
    virtual ~GameScreenView() {}
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
      touchgfx::Image bulletImages[MAX_BULLET];
};

#endif // GAMESCREENVIEW_HPP
