#ifndef GAMESCREENVIEW_HPP
#define GAMESCREENVIEW_HPP

#include <gui_generated/gamescreen_screen/GameScreenViewBase.hpp>
#include <gui/gamescreen_screen/GameScreenPresenter.hpp>
#include <images/BitmapDatabase.hpp>
#include <Game.hpp>
#include <vector>
class GameScreenView: public GameScreenViewBase {
public:
	GameScreenView();
	virtual ~GameScreenView() {
	}
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
private:
	touchgfx::Image galagaImage;
	touchgfx::Image liveImages[MAX_LIVE];
	touchgfx::Image bulletImages[MAX_BULLET];
	touchgfx::Image eBulletImages[MAX_BULLET];
	touchgfx::Image enemy0Images[MAX_ENEMY];
	touchgfx::Image enemy1Images[MAX_ENEMY];
	touchgfx::Image bee0Images[MAX_BEE];
	touchgfx::Image bee1Images[MAX_BEE];
	touchgfx::Image butterfly0Images[MAX_BEE];
	touchgfx::Image butterfly1Images[MAX_BEE];
	touchgfx::Image eDieImages[5];
	int8_t eDieCounter[5];
	uint8_t oldLive;
};

#endif // GAMESCREENVIEW_HPP
