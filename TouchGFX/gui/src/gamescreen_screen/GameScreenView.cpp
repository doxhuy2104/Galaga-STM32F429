#include <gui/gamescreen_screen/GameScreenView.hpp>
#include <cmsis_os.h>
#include <Game.hpp>
extern osMessageQueueId_t Queue1Handle;
extern osMessageQueueId_t Queue2Handle;
extern osMessageQueueId_t Queue3Handle;

osThreadId_t gameTaskHandle;
GameScreenView::GameScreenView() {
	bg0Y = -320;
	bg1Y = 0;
	changeBg = 0;
	galagaImage.setBitmap(touchgfx::Bitmap(BITMAP_GALAGA_ID));
	galagaImage.setXY(112, 280);
	add (galagaImage);

	for (int i = 0; i < MAX_BULLET; i++) {
		bulletImages[i].setBitmap(touchgfx::Bitmap(BITMAP_MBULLET_ID));
		bulletImages[i].setXY(0, 0);
		add(bulletImages[i]);
	}
}

void GameScreenView::setupScreen() {
	GameScreenViewBase::setupScreen();

	const osThreadAttr_t update_attributes = { .name = "update", .stack_size =
			8192 * 2, .priority = (osPriority_t) osPriorityNormal, };

	gameTaskHandle = osThreadNew(GameThread, NULL, &update_attributes);
}

void GameScreenView::tearDownScreen() {
	GameScreenViewBase::tearDownScreen();
}
void GameScreenView::handleTickEvent() {
	GameScreenViewBase::handleTickEvent();

	tickCount++;
	if (tickCount % 10 == 0) {
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
	if (osMessageQueueGetCount(Queue1Handle) > 0) {
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if (res == 'R') {
			game.galaga.moveR();
		}
	}
	if (osMessageQueueGetCount(Queue2Handle) > 0) {
		osMessageQueueGet(Queue2Handle, &res, NULL, osWaitForever);
		if (res == 'L') {
			game.galaga.moveL();
		}

	}
	if (osMessageQueueGetCount(Queue3Handle) > 0) {
			osMessageQueueGet(Queue3Handle, &res, NULL, osWaitForever);
			if (res == 'F') {
				game.galaga.isFire=true;
			}

		}else{
			game.galaga.isFire=false;

		}
	for (int i = 0; i < MAX_BULLET; i++) {
		switch (game.galaga.bullets[i].status) {
		case SPAWN:
			bulletImages[i].moveTo(game.galaga.bullets[i].x,
					game.galaga.bullets[i].y);
			bulletImages[i].setVisible(true);
			game.galaga.bullets[i].updateStatus(ACTIVE);
			break;
		case ACTIVE:
			bulletImages[i].moveTo(game.galaga.bullets[i].x,
					game.galaga.bullets[i].y);
			break;
		case INACTIVE:
			bulletImages[i].setVisible(false);
			break;
		default:
			break;
		}
	}
	galagaImage.moveTo(game.galaga.x, game.galaga.y);
	invalidate();
}
