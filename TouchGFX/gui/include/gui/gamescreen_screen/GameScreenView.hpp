#ifndef GAMESCREENVIEW_HPP
#define GAMESCREENVIEW_HPP

#include <gui_generated/gamescreen_screen/GameScreenViewBase.hpp>
#include <gui/gamescreen_screen/GameScreenPresenter.hpp>
#include <images/BitmapDatabase.hpp>
#include <Game.hpp>
#include <vector>

#define MAX_SCORE_LEN 6
#define MAX_STAGE_LEN 2

struct SoundPlayer {
    const uint32_t* tones;
    const uint16_t* durations;
    uint8_t count;
    uint8_t index;
    uint16_t tickCounter;
    bool isPlaying;
};

class GameScreenView: public GameScreenViewBase {
public:
	GameScreenView();
	virtual ~GameScreenView() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();
	virtual void handleTickEvent();
    void playToneSequence(const uint32_t* tones, const uint16_t* durations, uint8_t count);
    void playFireSound();
    void playEnemyDieSound();
    void playShipDieSound();
    void playEnemyFireSound();
    void playStageUpSound();
    void startTone(uint32_t freq);
    void stopTone();
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
	touchgfx::Image mDieImage;
	int8_t mDieCounter;
	touchgfx::Image scoreImages[MAX_SCORE_LEN];
	uint32_t oldScore;
	touchgfx::Image highScoreImages[MAX_SCORE_LEN];
	uint32_t highestScore;
	touchgfx::Image stageImages[MAX_STAGE_LEN];
	uint32_t oldStage;
	SoundPlayer soundPlayer;
};

#endif // GAMESCREENVIEW_HPP
