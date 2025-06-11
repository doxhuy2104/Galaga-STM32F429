#include <gui/gamescreen_screen/GameScreenView.hpp>
#include <cmsis_os.h>
#include <Game.hpp>
extern osMessageQueueId_t Queue1Handle;
extern osMessageQueueId_t Queue2Handle;
extern osMessageQueueId_t Queue3Handle;

osThreadId_t gameTaskHandle;
const uint16_t DEATH_EFFECT_BITMAPS[] = { BITMAP_EDIE0_ID, BITMAP_EDIE1_ID,
		BITMAP_EDIE2_ID, BITMAP_EDIE3_ID, BITMAP_EDIE4_ID };
GameScreenView::GameScreenView() {
	bg0Y = -320;
	bg1Y = 0;
	changeBg = 0;
	iAlp = 0;
	dAlp = 255;
	galagaImage.setBitmap(touchgfx::Bitmap(BITMAP_GALAGA_ID));
	galagaImage.setXY(112, 280);
	add (galagaImage);

	for (int i = 0; i < MAX_BULLET; i++) {
		bulletImages[i].setBitmap(touchgfx::Bitmap(BITMAP_MBULLET_ID));
		bulletImages[i].setXY(0, 0);
		add (bulletImages[i]);
	}
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy0Images[i].setBitmap(touchgfx::Bitmap(BITMAP_ENEMY0_ID));
		enemy0Images[i].setXY(0, 0);
		add (enemy0Images[i]);
		enemy0Images[i].setVisible(false);
		enemy1Images[i].setBitmap(touchgfx::Bitmap(BITMAP_ENEMY1_ID));
		enemy1Images[i].setXY(game.enemies[i].x, game.enemies[i].y);
		add (enemy1Images[i]);
	}
	for (int i = 0; i < MAX_ENEMY; i++) {
		bee0Images[i].setBitmap(touchgfx::Bitmap(BITMAP_BEE0_ID));
		bee0Images[i].setXY(0, 0);
		add (bee0Images[i]);
		bee0Images[i].setVisible(false);
		bee1Images[i].setBitmap(touchgfx::Bitmap(BITMAP_BEE1_ID));
		bee1Images[i].setXY(game.bees[i].x, game.bees[i].y);
		add (bee1Images[i]);
	}
	for (int i = 0; i < 5; i++) {
		eDieImages[i].setBitmap(touchgfx::Bitmap(DEATH_EFFECT_BITMAPS[0]));
		eDieImages[i].setXY(0, 0);
		eDieImages[i].setVisible(false);
		add (eDieImages[i]);
		eDieCounter[i] = -1;
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
	if (tickCount % 5 == 0) {
		if (tickCount % 15 == 0)
			changeBg = !changeBg;
		if (iAlp == 0)
			iAlp = 31;
		else if (iAlp == 31) {
			iAlp = 255;
		} else {
			iAlp = 0;
		}
		if (dAlp == 255)
			dAlp = 31;
		else if (dAlp == 31) {
			dAlp = 0;
		} else {
			dAlp = 255;
		}
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
		bg0.setAlpha(iAlp);
		bg1.setAlpha(iAlp);
		bg2.setAlpha(dAlp);
		bg3.setAlpha(dAlp);
		break;
	case 1:
		bg2.setAlpha(iAlp);
		bg3.setAlpha(iAlp);
		bg0.setAlpha(dAlp);
		bg1.setAlpha(dAlp);
		break;
	default:
		break;
	}

	uint8_t res;
	if (osMessageQueueGetCount(Queue1Handle) > 0) {
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if (res == 'R') {
			game.ship.moveR();
		}
	}
	if (osMessageQueueGetCount(Queue2Handle) > 0) {
		osMessageQueueGet(Queue2Handle, &res, NULL, osWaitForever);
		if (res == 'L') {
			game.ship.moveL();
		}

	}
	if (osMessageQueueGetCount(Queue3Handle) > 0) {
		osMessageQueueGet(Queue3Handle, &res, NULL, osWaitForever);
		if (res == 'F') {
			game.ship.isFire = true;
		}
	} else {
		game.ship.isFire = false;
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		switch (game.ship.bullets[i].status) {
		case SPAWN:
			bulletImages[i].moveTo(game.ship.bullets[i].x,
					game.ship.bullets[i].y);
			bulletImages[i].setVisible(true);
			game.ship.bullets[i].updateStatus(ACTIVE);
			break;
		case ACTIVE:
			bulletImages[i].moveTo(game.ship.bullets[i].x,
					game.ship.bullets[i].y);
			break;
		case INACTIVE:
			bulletImages[i].setVisible(false);
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < MAX_ENEMY; i++) {
		switch (game.enemies[i].status) {
		case ALIVE:
			enemy1Images[i].moveTo(game.enemies[i].x, game.enemies[i].y);
			enemy0Images[i].moveTo(game.enemies[i].x, game.enemies[i].y);
			if (game.enemies[i].sprite) {
				enemy1Images[i].setVisible(true);
				enemy0Images[i].setVisible(false);
			} else {
				enemy0Images[i].setVisible(true);
				enemy1Images[i].setVisible(false);
			}
			break;

		case DIE:
			enemy1Images[i].setVisible(false);
			enemy0Images[i].setVisible(false);
			for (int j = 0; j < 5; j++) {
				if (eDieCounter[j] == -1) {
					eDieCounter[j] = 0;
					eDieImages[j].moveTo(game.enemies[i].x - 8,
							game.enemies[i].y - 8);
					eDieImages[j].setVisible(true);
					game.enemies[i].status = DEAD;
					break;
				}
			}
			break;

		case DEAD:
			enemy1Images[i].setVisible(false);
			enemy0Images[i].setVisible(false);
			break;

		default:
			break;
		}
	}
	for (int i = 0; i < MAX_ENEMY; i++) {
		switch (game.bees[i].status) {
		case ALIVE:
			bee1Images[i].moveTo(game.bees[i].x, game.bees[i].y);
			bee0Images[i].moveTo(game.bees[i].x, game.bees[i].y);
			if (game.bees[i].sprite) {
				bee1Images[i].setVisible(true);
				bee0Images[i].setVisible(false);
			} else {
				bee0Images[i].setVisible(true);
				bee1Images[i].setVisible(false);
			}
			break;

		case DIE:
			bee1Images[i].setVisible(false);
			bee0Images[i].setVisible(false);
			for (int j = 0; j < 5; j++) {
				if (eDieCounter[j] == -1) {
					eDieCounter[j] = 0;
					eDieImages[j].moveTo(game.bees[i].x - 8,
							game.bees[i].y - 8);
					eDieImages[j].setVisible(true);
					game.bees[i].status = DEAD;
					break;
				}
			}
			break;

		case DEAD:
			bee1Images[i].setVisible(false);
			bee0Images[i].setVisible(false);
			break;

		default:
			break;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (eDieCounter[i] != -1) {
			eDieCounter[i]++;
			if (eDieCounter[i] % 5 == 0) {
				eDieImages[i].setBitmap(
						DEATH_EFFECT_BITMAPS[eDieCounter[i] / 5]);
				if (eDieCounter[i] >= 25) {
					eDieCounter[i] = -1;
					eDieImages[i].setBitmap(DEATH_EFFECT_BITMAPS[0]);
					eDieImages[i].setVisible(false);
				}
			}
		}
	}
	galagaImage.moveTo(game.ship.x, game.ship.y);
	invalidate();
}
