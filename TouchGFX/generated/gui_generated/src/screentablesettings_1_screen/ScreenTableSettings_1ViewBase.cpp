/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screentablesettings_1_screen/ScreenTableSettings_1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


ScreenTableSettings_1ViewBase::ScreenTableSettings_1ViewBase() :
    buttonCallback(this, &ScreenTableSettings_1ViewBase::buttonCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box1.setPosition(0, 0, 480, 272);
    box1.setColor(touchgfx::Color::getColorFromRGB(135, 135, 135));

    line1.setPosition(0, 0, 2, 272);
    line1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1.setPainter(line1Painter);
    line1.setStart(0, 0);
    line1.setEnd(0, 272);
    line1.setLineWidth(2);
    line1.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);

    line22.setPosition(376, 0, 4, 272);
    line22Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line22.setPainter(line22Painter);
    line22.setStart(0, 0);
    line22.setEnd(0, 272);
    line22.setLineWidth(4);
    line22.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);

    gor1.setPosition(0, 0, 480, 2);
    gor1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    gor1.setPainter(gor1Painter);
    gor1.setStart(0, 0);
    gor1.setEnd(480, 0);
    gor1.setLineWidth(2);
    gor1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);

    button1.setXY(398, 22);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID));

    toggleButton1.setXY(440, 121);
    toggleButton1.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_30X30_BLUE_ID), touchgfx::Bitmap(BITMAP_BTN_30X30_GREY_ID));
    toggleButton1.forceState(true);
    toggleButton1.setAction(buttonCallback);

    button2.setXY(380, 155);
    button2.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID));

    textArea1.setXY(382, 86);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_0FNE));

    scrollableContainer1.setPosition(0, 0, 378, 272);
    scrollableContainer1.setVisible(false);
    scrollableContainer1.enableHorizontalScroll(false);
    scrollableContainer1.setScrollbarsColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    container2.setPosition(0, 0, 376, 272);

    container1_6.setPosition(2, 58, 374, 156);

    btnTempSelect1_6.setXY(10, 10);
    btnTempSelect1_6.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_6.add(btnTempSelect1_6);

    btnTempSelect2_6.setXY(86, 10);
    btnTempSelect2_6.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_6.add(btnTempSelect2_6);

    btnTempSelect3_6.setXY(156, 10);
    btnTempSelect3_6.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_6.add(btnTempSelect3_6);

    btnTempSelect4_6.setXY(226, 10);
    btnTempSelect4_6.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_6.add(btnTempSelect4_6);

    btnTempSelect5_6.setXY(296, 10);
    btnTempSelect5_6.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_6.add(btnTempSelect5_6);

    btnTempSelect6_6.setXY(10, 86);
    btnTempSelect6_6.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_6.add(btnTempSelect6_6);

    textArea2_6.setPosition(86, 28, 60, 25);
    textArea2_6.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2_6.setLinespacing(0);
    textArea2_6.setTypedText(touchgfx::TypedText(T___SINGLEUSE_K1R1));
    container1_6.add(textArea2_6);
    container2.add(container1_6);

    container1_5.setPosition(2, 58, 374, 156);

    btnTempSelect1_5.setXY(10, 10);
    btnTempSelect1_5.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_5.add(btnTempSelect1_5);

    btnTempSelect2_5.setXY(86, 10);
    btnTempSelect2_5.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_5.add(btnTempSelect2_5);

    btnTempSelect3_5.setXY(156, 10);
    btnTempSelect3_5.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_5.add(btnTempSelect3_5);

    btnTempSelect4_5.setXY(226, 10);
    btnTempSelect4_5.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_5.add(btnTempSelect4_5);

    btnTempSelect5_5.setXY(296, 10);
    btnTempSelect5_5.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_5.add(btnTempSelect5_5);

    btnTempSelect6_5.setXY(10, 86);
    btnTempSelect6_5.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_5.add(btnTempSelect6_5);

    textArea2_5.setPosition(86, 28, 60, 25);
    textArea2_5.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2_5.setLinespacing(0);
    textArea2_5.setTypedText(touchgfx::TypedText(T___SINGLEUSE_RQFU));
    container1_5.add(textArea2_5);
    container2.add(container1_5);

    container1_4.setPosition(2, 58, 374, 156);

    btnTempSelect1_4.setXY(10, 10);
    btnTempSelect1_4.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_4.add(btnTempSelect1_4);

    btnTempSelect2_4.setXY(86, 10);
    btnTempSelect2_4.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_4.add(btnTempSelect2_4);

    btnTempSelect3_4.setXY(156, 10);
    btnTempSelect3_4.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_4.add(btnTempSelect3_4);

    btnTempSelect4_4.setXY(226, 10);
    btnTempSelect4_4.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_4.add(btnTempSelect4_4);

    btnTempSelect5_4.setXY(296, 10);
    btnTempSelect5_4.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_4.add(btnTempSelect5_4);

    btnTempSelect6_4.setXY(10, 86);
    btnTempSelect6_4.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_4.add(btnTempSelect6_4);

    textArea2_4.setPosition(86, 28, 60, 25);
    textArea2_4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2_4.setLinespacing(0);
    textArea2_4.setTypedText(touchgfx::TypedText(T___SINGLEUSE_ZU78));
    container1_4.add(textArea2_4);
    container2.add(container1_4);

    container1_3.setPosition(2, 58, 374, 156);

    btnTempSelect1_3.setXY(10, 10);
    btnTempSelect1_3.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_3.add(btnTempSelect1_3);

    btnTempSelect2_3.setXY(86, 10);
    btnTempSelect2_3.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_3.add(btnTempSelect2_3);

    btnTempSelect3_3.setXY(156, 10);
    btnTempSelect3_3.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_3.add(btnTempSelect3_3);

    btnTempSelect4_3.setXY(226, 10);
    btnTempSelect4_3.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_3.add(btnTempSelect4_3);

    btnTempSelect5_3.setXY(296, 10);
    btnTempSelect5_3.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_3.add(btnTempSelect5_3);

    btnTempSelect6_3.setXY(10, 86);
    btnTempSelect6_3.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_3.add(btnTempSelect6_3);

    textArea2_3.setPosition(86, 28, 60, 25);
    textArea2_3.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2_3.setLinespacing(0);
    textArea2_3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_D8IW));
    container1_3.add(textArea2_3);
    container2.add(container1_3);

    container1_2.setPosition(2, 58, 374, 156);

    btnTempSelect1_2.setXY(10, 10);
    btnTempSelect1_2.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_2.add(btnTempSelect1_2);

    btnTempSelect2_2.setXY(86, 10);
    btnTempSelect2_2.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_2.add(btnTempSelect2_2);

    btnTempSelect3_2.setXY(156, 10);
    btnTempSelect3_2.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_2.add(btnTempSelect3_2);

    btnTempSelect4_2.setXY(226, 10);
    btnTempSelect4_2.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_2.add(btnTempSelect4_2);

    btnTempSelect5_2.setXY(296, 10);
    btnTempSelect5_2.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_2.add(btnTempSelect5_2);

    btnTempSelect6_2.setXY(10, 86);
    btnTempSelect6_2.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_2.add(btnTempSelect6_2);

    textArea2_2.setPosition(86, 28, 60, 25);
    textArea2_2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2_2.setLinespacing(0);
    textArea2_2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_OW12));
    container1_2.add(textArea2_2);
    container2.add(container1_2);

    container1_1.setPosition(2, 58, 374, 156);

    btnTempSelect1_1.setXY(10, 10);
    btnTempSelect1_1.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_1.add(btnTempSelect1_1);

    btnTempSelect2_1.setXY(86, 10);
    btnTempSelect2_1.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_1.add(btnTempSelect2_1);

    btnTempSelect3_1.setXY(156, 10);
    btnTempSelect3_1.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_1.add(btnTempSelect3_1);

    btnTempSelect4_1.setXY(226, 10);
    btnTempSelect4_1.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_1.add(btnTempSelect4_1);

    btnTempSelect5_1.setXY(296, 10);
    btnTempSelect5_1.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_1.add(btnTempSelect5_1);

    btnTempSelect6_1.setXY(10, 86);
    btnTempSelect6_1.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    container1_1.add(btnTempSelect6_1);

    textArea2_1.setPosition(86, 28, 60, 25);
    textArea2_1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2_1.setLinespacing(0);
    textArea2_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8LTS));
    container1_1.add(textArea2_1);
    container2.add(container1_1);

    container1.setPosition(2, 58, 374, 156);
    container2.add(container1);
    scrollableContainer1.add(container2);
    scrollableContainer1.setScrollbarsPermanentlyVisible();

    swipeContainer1.setXY(0, 0);
    swipeContainer1.setSwipeCutoff(50);
    swipeContainer1.setEndSwipeElasticWidth(50);

    swipeContainer1Page1.setWidth(378);
    swipeContainer1Page1.setHeight(272);

    btnTempSelect1.setXY(12, 68);
    btnTempSelect1.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1.add(btnTempSelect1);

    btnTempSelect2.setXY(88, 68);
    btnTempSelect2.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1.add(btnTempSelect2);

    btnTempSelect3.setXY(158, 68);
    btnTempSelect3.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1.add(btnTempSelect3);

    btnTempSelect4.setXY(228, 68);
    btnTempSelect4.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1.add(btnTempSelect4);

    btnTempSelect5.setXY(298, 68);
    btnTempSelect5.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1.add(btnTempSelect5);

    btnTempSelect6.setXY(12, 144);
    btnTempSelect6.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1.add(btnTempSelect6);

    textArea2.setPosition(88, 86, 60, 25);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_M90T));
    swipeContainer1Page1.add(textArea2);

    image1_1.setXY(164, 8);
    image1_1.setBitmap(touchgfx::Bitmap(BITMAP_DARK_ICONS_UP_ARROW_48_ID));
    swipeContainer1Page1.add(image1_1);
    swipeContainer1.add(swipeContainer1Page1);

    swipeContainer1Page1_1.setWidth(378);
    swipeContainer1Page1_1.setHeight(272);

    btnTempSelect1_7.setXY(12, 68);
    btnTempSelect1_7.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1_1.add(btnTempSelect1_7);

    btnTempSelect2_7.setXY(88, 68);
    btnTempSelect2_7.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1_1.add(btnTempSelect2_7);

    btnTempSelect3_7.setXY(158, 68);
    btnTempSelect3_7.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1_1.add(btnTempSelect3_7);

    btnTempSelect4_7.setXY(228, 68);
    btnTempSelect4_7.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1_1.add(btnTempSelect4_7);

    btnTempSelect5_7.setXY(298, 68);
    btnTempSelect5_7.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1_1.add(btnTempSelect5_7);

    btnTempSelect6_7.setXY(12, 144);
    btnTempSelect6_7.setBitmaps(touchgfx::Bitmap(BITMAP_BTN_60X60_GREY_ID), touchgfx::Bitmap(BITMAP_BTN_60X60_BLUE_ID));
    swipeContainer1Page1_1.add(btnTempSelect6_7);

    textArea2_7.setPosition(88, 86, 60, 25);
    textArea2_7.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2_7.setLinespacing(0);
    textArea2_7.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8HRC));
    swipeContainer1Page1_1.add(textArea2_7);

    image1_2.setXY(164, 235);
    image1_2.setBitmap(touchgfx::Bitmap(BITMAP_DARK_ICONS_DOWN_ARROW_48_ID));
    swipeContainer1Page1_1.add(image1_2);
    swipeContainer1.add(swipeContainer1Page1_1);
    swipeContainer1.setSelectedPage(1);

    add(__background);
    add(box1);
    add(line1);
    add(line22);
    add(gor1);
    add(button1);
    add(toggleButton1);
    add(button2);
    add(textArea1);
    add(scrollableContainer1);
    add(swipeContainer1);
}

void ScreenTableSettings_1ViewBase::setupScreen()
{

}

void ScreenTableSettings_1ViewBase::action1()
{

}

void ScreenTableSettings_1ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &toggleButton1)
    {
        //chooseTemp
        //When toggleButton1 clicked call virtual function
        //Call virtChooseTemp
        virtChooseTemp();

        //Interaction1
        //When toggleButton1 clicked execute C++ code
        //Execute C++ code
        if (textArea1.isVisible())
        {
            
            textArea1.setVisible(false);
            textArea1.invalidate();
        }
        else
        {
            textArea1.setVisible(true);
            textArea1.invalidate();
        }
    }
}
