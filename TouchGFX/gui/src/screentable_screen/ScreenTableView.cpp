#include <gui/screentable_screen/ScreenTableView.hpp>

ScreenTableView::ScreenTableView()
{

}

void ScreenTableView::setupScreen()
{
    ScreenTableViewBase::setupScreen();
    textNum1.setVisible(true);
    textNum1.invalidate();
    textNum2.setVisible(true);
    textNum2.invalidate();
    textNum3.setVisible(true);
    textNum3.invalidate();
    textNum4.setVisible(true);
    textNum4.invalidate();
    textTemp1.setVisible(false);
    textTemp1.invalidate();
}

void ScreenTableView::tearDownScreen()
{
    ScreenTableViewBase::tearDownScreen();
}

void ScreenTableView::virtChooseTemp()
{
    ScreenTableView s;
    if (!textNum1.isVisible())
    {
    	textNum1.setVisible(true);
    	textNum1.invalidate();
    	textNum2.setVisible(true);
    	textNum2.invalidate();
    	textNum3.setVisible(true);
    	textNum3.invalidate();
    	textNum4.setVisible(true);
    	textNum4.invalidate();
    	textTemp1.setVisible(false);
    	textTemp1.invalidate();
    	//toggleButton1.getPressedState()
    }
    else
    {
    	textNum1.setVisible(false);
    	textNum1.invalidate();
    	textNum2.setVisible(false);
    	textNum2.invalidate();
    	textNum3.setVisible(false);
    	textNum3.invalidate();
    	textNum4.setVisible(false);
    	textNum4.invalidate();
    	textTemp1.setVisible(true);
    	textTemp1.invalidate();
    }
}
