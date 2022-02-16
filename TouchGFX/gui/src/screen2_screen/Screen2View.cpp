#include <gui/screen2_screen/Screen2View.hpp>

#include <texts/TextKeysAndLanguages.hpp>

Screen2View::Screen2View() :
scrollList1_ItemSelectedCallback(this, &Screen2View::scrollList1_ItemSelectedHandler)
{

}

void Screen2View::setupScreen()
{
	scrollList1.setItemSelectedCallback(scrollList1_ItemSelectedCallback);
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::scrollList1UpdateItem(CustomContainer0& item, int16_t itemIndex)
{
	item.setListElements(itemIndex);
}

void Screen2View::checkALL()
{
	float primer;

	primer = 24.5;
	int prom = scrollList1ListItems[0].getListElementsCheck();
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", prom);
	textArea1.invalidate();

	if (prom > 1024)
	{
		prom -= 1024;
	}
	int i;
	int j;
	int maska = 512;

	for (j=0; j<7; j++)
	{
		for (i=0; i<10;i++)
		{
			if (prom & maska)		//- если ячейка выбрана для замера температуры
			{
				primer = presenter->getIndexTempValue(9-i);
				scrollList1ListItems[j].setTempCheckElement(9-i, primer, 20.1, 30.1);
			}
			else 					//- если ячейка НЕ выбрана для замера температуры
			{
				scrollList1ListItems[j].setTempUnCheckElement(9-i);
			}
			maska>>=1;
		}
	}
/*
	if (prom%2 == 1)
	{
		primer = presenter->getIndexTempValue(0x00);
		scrollList1ListItems[0].setCheckElement1(0, primer);
	}

	if (prom%4 > 1)
	{
		primer = presenter->getIndexTempValue(0x01);
		scrollList1ListItems[0].setCheckElement2(0, primer);
	}

	prom = scrollList1ListItems[1].getListElementsCheck();
	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", prom);
	textArea2.invalidate();

	prom = scrollList1ListItems[2].getListElementsCheck();
	Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%d", prom);
	textArea3.invalidate();

	prom = scrollList1ListItems[3].getListElementsCheck();
	Unicode::snprintf(textArea4Buffer, TEXTAREA4_SIZE, "%d", prom);
	textArea4.invalidate();

	prom = scrollList1ListItems[4].getListElementsCheck();
	Unicode::snprintf(textArea5Buffer, TEXTAREA5_SIZE, "%d", prom);
	textArea5.invalidate();

	prom = scrollList1ListItems[5].getListElementsCheck();
	Unicode::snprintf(textArea6Buffer, TEXTAREA6_SIZE, "%d", prom);
	textArea6.invalidate();

	prom = scrollList1ListItems[6].getListElementsCheck();
	Unicode::snprintf(textArea7Buffer, TEXTAREA7_SIZE, "%d", prom);
	textArea7.invalidate();

	presenter->saveIndexTemp(0x00);

	primer = presenter->getIndexTempValue(0x00);
	Unicode::snprintfFloat(textArea8Buffer, TEXTAREA8_SIZE, "%6.4f", primer);
	textArea8.invalidate();
	//float value = getTempIndexValue(1);
*/

}

void Screen2View::setBtn1(float value)
{
	//Unicode::snprintf(textArea8Buffer, TEXTAREA8_SIZE, "%d", value);
	Unicode::snprintfFloat(textArea8Buffer, TEXTAREA8_SIZE, "%6.4f", value);
	textArea8.invalidate();
}
void Screen2View::scrollList1_ItemSelectedHandler(int16_t itemSelected)
{
/*

	textArea1.invalidate();

	switch (itemSelected)
	{
	case 0:
		textArea1.setTypedText(TypedText(T_RESOURCEID01));
		break;
	case 1:
			textArea1.setTypedText(TypedText(T_RESOURCEID11));
			break;
	case 2:
			textArea1.setTypedText(TypedText(T_RESOURCEID21));
			break;
	case 3:
			textArea1.setTypedText(TypedText(T_RESOURCEID31));
			break;
	case 4:
			textArea1.setTypedText(TypedText(T_RESOURCEID41));
			break;
	case 5:
			textArea1.setTypedText(TypedText(T_RESOURCEID51));
			break;
	case 6:
			textArea1.setTypedText(TypedText(T_RESOURCEID61));
			break;
	default:
		textArea1.setTypedText(TypedText(T_RESOURCEID11));
		break;
	}

	textArea1.invalidate();
*/
}
