#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/utils.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    lastTempValue = 0;
    counter = presenter->getCounter();
    Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::buttonUpClick()
{
  touchgfx_printf("buttonUpClicked\n");
  counter++;
  saveSettings();//
  Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
  // Invalidate text area, which will result in it being redrawn in next tick.
  textCounter.invalidate();
}

void Screen1View::setJunctionTempValue(float value)
{
	//if (lastTempValue != value)
	//{
	//	lastTempValue = value;
		Unicode::snprintfFloat(textTempBuffer, TEXTTEMP_SIZE, "%6.4f", value);
		//Unicode::snprintf(textTempBuffer, TEXTTEMP_SIZE, "%d", value);
		  // Invalidate text area, which will result in it being redrawn in next tick.
		textTemp.invalidate();
//	}
}

void Screen1View::buttonDownClick()
{
  touchgfx_printf("buttonDownClicked\n");
  counter--;
  saveSettings();
  Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
  // Invalidate text area, which will result in it being redrawn in next tick.
  textCounter.invalidate();
}

void Screen1View::handleTickEvent()
{
//	if (tickCount == 60)
//	{
//		//counter++;
//		Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
//		textCounter.invalidate();
//		tickCount = 0;
//	}

}

void Screen1View::toggleSwLed()
{
	if (SwLedOn.isVisible())
	{
		SwLedOn.setVisible(false);
		SwLedOff.setVisible(true);
	}
	else
	{
		SwLedOn.setVisible(true);
		SwLedOff.setVisible(false);
	}
	SwLedOn.invalidate();
	SwLedOff.invalidate();

	counter--;
	  Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
	  // Invalidate text area, which will result in it being redrawn in next tick.
	  textCounter.invalidate();

	 // Unicode::snprintf(textTempBuffer, TEXTTEMP_SIZE, "%d", 35);
	  		  // Invalidate text area, which will result in it being redrawn in next tick.
	//  		textTemp.invalidate();
}
