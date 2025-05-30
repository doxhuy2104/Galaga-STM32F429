#include <gui/screen2_screen/Screen2View.hpp>
#include <cmsis_os.h>
#include <Game.hpp>
extern osMessageQueueId_t Queue1Handle;
osThreadId_t gameTaskHandle;
Screen2View::Screen2View()
{bg0Y = -320;
bg1Y = 0;
changeBg = 0;
galagaImage.setBitmap(touchgfx::Bitmap(BITMAP_GALAGA_ID));
galagaImage.setXY(112,280);
	add(galagaImage);

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();

    const osThreadAttr_t update_attributes = {
    	  .name = "update",
    	  .stack_size = 8192 * 2,
    	  .priority = (osPriority_t) osPriorityNormal,
    	};

    	gameTaskHandle = osThreadNew(GameThread, NULL, &update_attributes);
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}
void Screen2View::handleTickEvent(){
	Screen2ViewBase::handleTickEvent();

		tickCount++;
		if (tickCount % 10==0) {
			changeBg = !changeBg;
		}
		bg0Y += 2;
		bg1Y += 2;
		if (bg0Y == 0) {
			bg0Y = -320;
		}
		if (bg1Y == 320) {
			bg1Y = 0;
		}
		bg0.setY(bg0Y);
		bg1.setY(bg1Y);
		bg2.setY(bg0Y);
		bg3.setY(bg1Y);
		switch (changeBg) {
		case 0:
			bg0.setAlpha(255);
			bg1.setAlpha(255);
			bg2.setAlpha(96);
			bg3.setAlpha(96);

			break;
		case 1:
			bg2.setAlpha(255);
			bg3.setAlpha(255);
			bg0.setAlpha(96);
			bg1.setAlpha(96);
			break;
		default:
			break;
		}


		uint8_t res;
		if(osMessageQueueGetCount(Queue1Handle)>0){
			osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
			if(res == 'R'){
				galagaImage.moveTo(game.galaga.x, 0);
			}
		}
//		galagaImage.moveTo(game.galaga.x, game.galaga.y);
		invalidate();
}
