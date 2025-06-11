#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{
	bg0Y = -320;
		bg1Y = 0;
		changeBg = 0;
		iAlp = 0;
		dAlp = 255;
}

void MainScreenView::setupScreen()
{
    MainScreenViewBase::setupScreen();
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}
void MainScreenView::handleTickEvent(){
	MainScreenViewBase::handleTickEvent();


	tickCount++;
	if (tickCount % 5 == 0) {
		if(tickCount%15==0)changeBg = !changeBg;
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
//	bg0Y += 2;
//	bg1Y += 2;
//	if (bg0Y == 0) {
//		bg0Y = -320;
//	}
//	if (bg1Y == 320) {
//		bg1Y = 0;
//	}
//	bg0.setY(bg0Y);
//	bg1.setY(bg1Y);
//	bg2.setY(bg0Y);
//	bg3.setY(bg1Y);
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
	invalidate();
}
