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
	btnTempSelContALL.forceState(check);
	btnTempSelContALL.invalidate();

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

void CustomContainer0::setCheckElement1(int item, float temp)
{
	Unicode::snprintfFloat(textArea1XBuffer, 10, "%3.1f", temp);
	textArea1X.invalidate();
	if (temp < 20 || temp > 30)
	{
		if (temp < 0 || temp > 99)
		{
			Unicode::snprintfFloat(textArea1XBuffer, 10, "%3.1f", 0.0);
		}
		textArea1X.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		textArea1X.invalidate();
		btnTempSelCont1.forceState(false);
		btnTempSelCont1.invalidate();
	}
}
void CustomContainer0::setCheckElement2(int item, float temp)
{
	Unicode::snprintfFloat(textArea2XBuffer, 10, "%3.1f", temp);
	textArea2X.invalidate();
	if (temp < 20 || temp > 30)
	{
		if (temp < 0 || temp > 99)
		{
			Unicode::snprintfFloat(textArea2XBuffer, 10, "%3.1f", 0.0);
		}
		textArea2X.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		textArea2X.invalidate();
		btnTempSelCont2.forceState(false);
		btnTempSelCont2.invalidate();
	}
}
void CustomContainer0::setCheckElement3(int item, float temp)
{
	Unicode::snprintfFloat(textArea3XBuffer, TEXTAREA3X_SIZE, "%3.1f", temp);
	textArea3X.invalidate();
	if (temp < 20 || temp > 30)
	{
		if (temp < 0 || temp > 99)
		{
			Unicode::snprintfFloat(textArea3XBuffer, TEXTAREA1X_SIZE, "%3.1f", 0.0);
		}
		textArea3X.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
		textArea3X.invalidate();
		btnTempSelCont3.forceState(false);
		btnTempSelCont3.invalidate();
	}
}
void CustomContainer0::setTempCheckElement(int index, float temp, float minTemp, float maxTemp)
{
	float prom;
	if (temp < 0)				//- если измеренная температура слишком маленькая, чтобы быть правдой
	{
		prom = -0.0;			//- устанавливаем текущее зачение в -0.0
	}
	else if (temp > 99.9)		//- если измеренная температура слишком большая, чтобы быть правдой
	{
		prom = 99.9;			//- устанавливаем текущее значение в 99.9
	}
	else						//- если измеренная температура корректна
	{
		prom = temp;			//- устанавливаем текущее значение в измеренное
	}

	colortype color;			//- определяем цвет корректно измеренного значения

	if ((temp < minTemp) || (temp > maxTemp))					//- если не попали в ворота
	{
		color = touchgfx::Color::getColorFromRGB(255, 0, 0);	//- цвет = красный
	}
	else														//- если в норме
	{
		color = touchgfx::Color::getColorFromRGB(0, 255, 0);	//- цвет = зеленый
	}

	switch (index)
	{
		case 0:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont1.forceState(false);
				btnTempSelCont1.invalidate();
			}
			textArea1X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea1X.invalidate();										//- обновить надпись
			break;
		case 1:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont2.forceState(false);
				btnTempSelCont2.invalidate();
			}
			textArea2X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea2X.invalidate();										//- обновить надпись
			break;
		case 2:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont3.forceState(false);
				btnTempSelCont3.invalidate();
			}
			textArea3X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea3X.invalidate();										//- обновить надпись
			break;
		case 3:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont4.forceState(false);
				btnTempSelCont4.invalidate();
			}
			textArea4X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea4X.invalidate();										//- обновить надпись
			break;
		case 4:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont5.forceState(false);
				btnTempSelCont5.invalidate();
			}
			textArea5X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea5X.invalidate();										//- обновить надпись
			break;
		case 5:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont6.forceState(false);
				btnTempSelCont6.invalidate();
			}
			textArea6X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea6X.invalidate();										//- обновить надпись
			break;
		case 6:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont7.forceState(false);
				btnTempSelCont7.invalidate();
			}
			textArea7X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea7X.invalidate();										//- обновить надпись
			break;
		case 7:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont8.forceState(false);
				btnTempSelCont8.invalidate();
			}
			textArea8X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea8X.invalidate();										//- обновить надпись
			break;
		case 8:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont9.forceState(false);
				btnTempSelCont9.invalidate();
			}
			textArea9X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea9X.invalidate();										//- обновить надпись
			break;
		default:
			if (color == touchgfx::Color::getColorFromRGB(255, 0, 0))
			{
				btnTempSelCont10.forceState(false);
				btnTempSelCont10.invalidate();
			}
			textArea10X.setColor(color);										//- надпись соответствующим цветом
			Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
			textArea10X.invalidate();										//- обновить надпись
			break;
	}

	//textArray[index].setColor(color);
	//Unicode::snprintfFloat(bufferArray[index], 10, "%3.1f", prom);	//- отрисовать соответствующую температуру
	//textArray[index].invalidate();

	/*
	textArea2X.invalidate();
	textArea3X.invalidate();
	textArea4X.invalidate();
	textArea5X.invalidate();
	textArea6X.invalidate();
	textArea7X.invalidate();
	textArea8X.invalidate();
	textArea9X.invalidate();
	textArea10X.invalidate();
	*/
}

void CustomContainer0::setTempUnCheckElement(int index)
{
	switch (index)
		{
			case 0:
				textArea1X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea1X.invalidate();												//- обновить надпись
				break;
			case 1:
				textArea2X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea2X.invalidate();												//- обновить надпись
				break;
			case 2:
				textArea3X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea3X.invalidate();												//- обновить надпись
				break;
			case 3:
				textArea4X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea4X.invalidate();												//- обновить надпись
				break;
			case 4:
				textArea5X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea5X.invalidate();												//- обновить надпись
				break;
			case 5:
				textArea6X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea6X.invalidate();												//- обновить надпись
				break;
			case 6:
				textArea7X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea7X.invalidate();												//- обновить надпись
				break;
			case 7:
				textArea8X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea8X.invalidate();												//- обновить надпись
				break;
			case 8:
				textArea9X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea9X.invalidate();												//- обновить надпись
				break;
			default:
				textArea10X.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));	//- надпись соответствующим цветом
				Unicode::snprintf(bufferArray[index], 10, "%s", "-");					//- отрисовать соответствующую температуру
				textArea10X.invalidate();												//- обновить надпись
				break;
		}

}

