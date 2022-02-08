#include <gui/containers/CustomContainer0.hpp>

CustomContainer0::CustomContainer0()
{

}

void CustomContainer0::initialize()
{
    CustomContainer0Base::initialize();
}

int CustomContainer0::getListElementsCheck()
{
	int prom = 0;
	if (btnTempSelCont1.getState()) prom+=1;
	if (btnTempSelCont2.getState()) prom+=2;
	if (btnTempSelCont3.getState()) prom+=4;
	if (btnTempSelCont4.getState()) prom+=8;

	if (btnTempSelCont5.getState()) prom+=16;
	if (btnTempSelCont6.getState()) prom+=32;
	if (btnTempSelCont7.getState()) prom+=64;
	if (btnTempSelCont8.getState()) prom+=128;

	if (btnTempSelCont9.getState()) prom+=256;
	if (btnTempSelCont10.getState()) prom+=512;

	if (btnTempSelContALL.getState()) prom+=1024;

	return prom;
}

void CustomContainer0::setListElementsCheck(int item, bool check)
{
	btnTempSelCont1.forceState(check);
	btnTempSelCont1.invalidate();
	btnTempSelCont2.forceState(check);
	btnTempSelCont2.invalidate();
	btnTempSelCont3.forceState(check);
	btnTempSelCont3.invalidate();
	btnTempSelCont4.forceState(check);
	btnTempSelCont4.invalidate();
	btnTempSelCont5.forceState(check);
	btnTempSelCont5.invalidate();
	btnTempSelCont6.forceState(check);
	btnTempSelCont6.invalidate();
	btnTempSelCont7.forceState(check);
	btnTempSelCont7.invalidate();
	btnTempSelCont8.forceState(check);
	btnTempSelCont8.invalidate();
	btnTempSelCont9.forceState(check);
	btnTempSelCont9.invalidate();
	btnTempSelCont10.forceState(check);
	btnTempSelCont10.invalidate();

	if (check)
	{
	            textAreaLX.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea1X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea2X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea3X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea4X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea5X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea6X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea7X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea8X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea9X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textArea10X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	            textAreaLX.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	        }
	        else
	        {
	            textAreaLX.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea1X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea2X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea3X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea4X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea5X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea6X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea7X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea8X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea9X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textArea10X.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	            textAreaLX.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	  }
	        textArea1X.invalidate();
	        textArea2X.invalidate();
	        textArea3X.invalidate();
	        textArea4X.invalidate();
	        textArea5X.invalidate();
	        textArea6X.invalidate();
	        textArea7X.invalidate();
	        textArea8X.invalidate();
	        textArea9X.invalidate();
	        textArea10X.invalidate();
	        textAreaLX.invalidate();
}
void CustomContainer0::setListElements(int item)
{
	Unicode::snprintf(textArea1XBuffer, TEXTAREA1X_SIZE, "%d", 1 + item*10);
	Unicode::snprintf(textArea2XBuffer, TEXTAREA2X_SIZE, "%d", 2 + item*10);
	Unicode::snprintf(textArea3XBuffer, TEXTAREA3X_SIZE, "%d", 3 + item*10);
	Unicode::snprintf(textArea4XBuffer, TEXTAREA4X_SIZE, "%d", 4 + item*10);
	Unicode::snprintf(textArea5XBuffer, TEXTAREA5X_SIZE, "%d", 5 + item*10);
	Unicode::snprintf(textArea6XBuffer, TEXTAREA6X_SIZE, "%d", 6 + item*10);
	Unicode::snprintf(textArea7XBuffer, TEXTAREA7X_SIZE, "%d", 7 + item*10);
	Unicode::snprintf(textArea8XBuffer, TEXTAREA8X_SIZE, "%d", 8 + item*10);
	Unicode::snprintf(textArea9XBuffer, TEXTAREA9X_SIZE, "%d", 9 + item*10);
	Unicode::snprintf(textArea10XBuffer, TEXTAREA10X_SIZE, "%d", 10 + item*10);
	Unicode::snprintf(textAreaLXBuffer, TEXTAREALX_SIZE, "%d", item + 1);
	textArea1X.invalidate();
	textArea2X.invalidate();
	textArea3X.invalidate();
	textArea4X.invalidate();
	textArea5X.invalidate();
	textArea6X.invalidate();
	textArea7X.invalidate();
	textArea8X.invalidate();
	textArea9X.invalidate();
	textArea10X.invalidate();
	textAreaLX.invalidate();

}
