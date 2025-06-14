#include <gui/gamescreen_screen/GameScreenView.hpp>
#include <cmsis_os.h>
#include <Game.hpp>
extern osMessageQueueId_t Queue1Handle;
extern osMessageQueueId_t Queue2Handle;
extern osMessageQueueId_t Queue3Handle;

osThreadId_t gameTaskHandle;
const uint16_t EDIE_BITMAPS[] = { BITMAP_EDIE0_ID, BITMAP_EDIE1_ID,
		BITMAP_EDIE2_ID, BITMAP_EDIE3_ID, BITMAP_EDIE4_ID };
const uint16_t MDIE_BITMAPS[] = { BITMAP_MDIE0_ID, BITMAP_MDIE1_ID,
		BITMAP_MDIE2_ID, BITMAP_MDIE3_ID };
const uint16_t DIGIT_BITMAPS[] = { BITMAP_N0_ID, BITMAP_N1_ID, BITMAP_N2_ID,
		BITMAP_N3_ID, BITMAP_N4_ID, BITMAP_N5_ID, BITMAP_N6_ID, BITMAP_N7_ID,
		BITMAP_N8_ID, BITMAP_N9_ID };
GameScreenView::GameScreenView() {
	bg0Y = -320;
	bg1Y = 0;
	changeBg = 0;
	iAlp = 0;
	dAlp = 255;
	galagaImage.setBitmap(touchgfx::Bitmap(BITMAP_GALAGA_ID));
	galagaImage.setXY(112, 280);
	add (galagaImage);
	mDieImage.setBitmap(touchgfx::Bitmap(BITMAP_MDIE0_ID));
	mDieImage.setXY(0, 0);
	add (mDieImage);
	mDieImage.setVisible(false);
	for (int i = 0; i < MAX_LIVE; i++) {
		liveImages[i].setBitmap(touchgfx::Bitmap(BITMAP_LIVE_ID));
		liveImages[i].setXY(16 * i, 300);
		add (liveImages[i]);
		liveImages[i].setVisible(true);
	}
	for (int i = 0; i < game.ship.live; i++) {

		liveImages[i].setVisible(true);
	}
	for (int i = 0; i < MAX_BULLET; i++) {
		bulletImages[i].setBitmap(touchgfx::Bitmap(BITMAP_MBULLET_ID));
		bulletImages[i].setXY(0, 0);
		add (bulletImages[i]);
	}
	for (int i = 0; i < MAX_EBULLET; i++) {
		eBulletImages[i].setBitmap(touchgfx::Bitmap(BITMAP_EBULLET_ID));
		eBulletImages[i].setXY(0, 0);
		add (eBulletImages[i]);
	}
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy0Images[i].setBitmap(touchgfx::Bitmap(BITMAP_ENEMY0_ID));
		enemy0Images[i].setXY(0, 0);
		add (enemy0Images[i]);
		enemy0Images[i].setVisible(false);
		enemy1Images[i].setBitmap(touchgfx::Bitmap(BITMAP_ENEMY1_ID));
		enemy1Images[i].setXY(game.bosses[i].x, game.bosses[i].y);
		add (enemy1Images[i]);
	}
	for (int i = 0; i < MAX_BEE; i++) {
		bee0Images[i].setBitmap(touchgfx::Bitmap(BITMAP_BEE0_ID));
		bee0Images[i].setXY(0, 0);
		add (bee0Images[i]);
		bee0Images[i].setVisible(false);
		bee1Images[i].setBitmap(touchgfx::Bitmap(BITMAP_BEE1_ID));
		bee1Images[i].setXY(game.bees[i].x, game.bees[i].y);
		add (bee1Images[i]);
	}
	for (int i = 0; i < MAX_BUTTERFLY; i++) {
		butterfly0Images[i].setBitmap(touchgfx::Bitmap(BITMAP_BUTTERFLY0_ID));
		butterfly0Images[i].setXY(0, 0);
		add (butterfly0Images[i]);
		butterfly0Images[i].setVisible(false);
		butterfly1Images[i].setBitmap(touchgfx::Bitmap(BITMAP_BUTTERFLY1_ID));
		butterfly1Images[i].setXY(game.butterflys[i].x, game.butterflys[i].y);
		add (butterfly1Images[i]);
	}
	for (int i = 0; i < 5; i++) {
		eDieImages[i].setBitmap(touchgfx::Bitmap(EDIE_BITMAPS[0]));
		eDieImages[i].setXY(0, 0);
		eDieImages[i].setVisible(false);
		add (eDieImages[i]);
		eDieCounter[i] = -1;
	}

	for (int i = 0; i < MAX_SCORE_LEN - 1; i++) {
		scoreImages[i].setBitmap(touchgfx::Bitmap(BITMAP_N0_ID));
		scoreImages[i].setXY(8 * i, 8);
		scoreImages[i].setVisible(false);
		add (scoreImages[i]);
	}
	scoreImages[5].setBitmap(touchgfx::Bitmap(BITMAP_N0_ID));
	scoreImages[5].setXY(40, 8);
	add (scoreImages[5]);
	oldScore = 0;
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

	//background
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

	//ship
	uint8_t res;

	if (osMessageQueueGetCount(Queue1Handle) > 0) {
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if (res == 'R') {
			if (game.ship.status == ALIVE)
				game.ship.moveR();
		}
	}
	if (osMessageQueueGetCount(Queue2Handle) > 0) {
		osMessageQueueGet(Queue2Handle, &res, NULL, osWaitForever);
		if (res == 'L') {
			if (game.ship.status == ALIVE)
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
	galagaImage.moveTo(game.ship.x, game.ship.y);
//	if (game.ship.live != oldLive) {
//		oldLive = game.ship.live;
//		for (int i = 0; i < game.ship.live; i++) {
//			liveImages[i].setVisible(true);
//		}
//		for (int i = game.ship.live; i < MAX_LIVE; i++) {
//			liveImages[i].setVisible(false);
//		}
//	}
	if (game.ship.status == DIE) {
		galagaImage.setVisible(false);
		if (mDieCounter == 0) {
			mDieImage.setVisible(true);
			mDieImage.moveTo(game.ship.x - 8, game.ship.y - 8);
		}
		mDieCounter++;
		if (mDieCounter % 10 == 0) {
			mDieImage.setBitmap(MDIE_BITMAPS[mDieCounter / 10]);
			if (mDieCounter >= 40) {
				galagaImage.setVisible(true);
				mDieCounter = 0;
				mDieImage.setBitmap(EDIE_BITMAPS[0]);
				mDieImage.setVisible(false);
				if (game.ship.live > 1)
					game.ship.live--;
				liveImages[game.ship.live].setVisible(false);
				game.ship.status = ALIVE;
			}
		}
	}

	//enemy
	for (int i = 0; i < MAX_ENEMY; i++) {
		switch (game.bosses[i].status) {
		case ALIVE:
			enemy1Images[i].moveTo(game.bosses[i].x, game.bosses[i].y);
			enemy0Images[i].moveTo(game.bosses[i].x, game.bosses[i].y);
			if (game.bosses[i].sprite) {
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
					eDieImages[j].moveTo(game.bosses[i].x - 8,
							game.bosses[i].y - 8);
					eDieImages[j].setVisible(true);
					game.bosses[i].status = DEAD;
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
	for (int i = 0; i < MAX_BEE; i++) {
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

	for (int i = 0; i < MAX_BUTTERFLY; i++) {
		switch (game.butterflys[i].status) {
		case ALIVE:
			butterfly1Images[i].moveTo(game.butterflys[i].x,
					game.butterflys[i].y);
			butterfly0Images[i].moveTo(game.butterflys[i].x,
					game.butterflys[i].y);
			if (game.butterflys[i].sprite) {
				butterfly1Images[i].setVisible(true);
				butterfly0Images[i].setVisible(false);
			} else {
				butterfly0Images[i].setVisible(true);
				butterfly1Images[i].setVisible(false);
			}
			break;

		case DIE:
			butterfly1Images[i].setVisible(false);
			butterfly0Images[i].setVisible(false);
			for (int j = 0; j < 5; j++) {
				if (eDieCounter[j] == -1) {
					eDieCounter[j] = 0;
					eDieImages[j].moveTo(game.butterflys[i].x - 8,
							game.butterflys[i].y - 8);
					eDieImages[j].setVisible(true);
					game.butterflys[i].status = DEAD;
					break;
				}
			}
			break;

		case DEAD:
			butterfly1Images[i].setVisible(false);
			butterfly0Images[i].setVisible(false);
			break;

		default:
			break;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (eDieCounter[i] != -1) {
			eDieCounter[i]++;
			if (eDieCounter[i] % 3 == 0) {
				eDieImages[i].setBitmap(EDIE_BITMAPS[eDieCounter[i] / 3]);
				if (eDieCounter[i] >= 15) {
					eDieCounter[i] = -1;
					eDieImages[i].setBitmap(EDIE_BITMAPS[0]);
					eDieImages[i].setVisible(false);
				}
			}
		}
	}
	for (int i = 0; i < MAX_EBULLET; i++) {
		switch (game.eBullets[i].status) {
		case SPAWN:
			eBulletImages[i].moveTo(game.eBullets[i].x, game.eBullets[i].y);
			eBulletImages[i].setVisible(true);
			game.eBullets[i].updateStatus(ACTIVE);
			break;
		case ACTIVE:
			eBulletImages[i].moveTo(game.eBullets[i].x, game.eBullets[i].y);
			break;
		case INACTIVE:
			eBulletImages[i].setVisible(false);
			break;
		default:
			break;
		}
	}

	//score
	if (game.score != oldScore) {
		oldScore = game.score;
		uint32_t score = game.score;
		for (int i = MAX_SCORE_LEN - 1; i >= 0; i--) {
			uint8_t digit = score % 10;
			score /= 10;
			scoreImages[i].setBitmap(touchgfx::Bitmap(DIGIT_BITMAPS[digit]));
			scoreImages[i].setVisible(true);
			if(score==0) break;
		}
	}
	invalidate();
}
