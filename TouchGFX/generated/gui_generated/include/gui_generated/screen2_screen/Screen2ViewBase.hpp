/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN2VIEWBASE_HPP
#define SCREEN2VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/scrollers/ScrollList.hpp>
#include <gui/containers/CustomContainer0.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class Screen2ViewBase : public touchgfx::View<Screen2Presenter>
{
public:
    Screen2ViewBase();
    virtual ~Screen2ViewBase() {}
    virtual void setupScreen();

    virtual void scrollList1UpdateItem(CustomContainer0& item, int16_t itemIndex)
    {
        // Override and implement this function in Screen2
    }

    /*
     * Virtual Action Handlers
     */
    virtual void checkALL()
    {
        // Override and implement this function in Screen2
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::ScrollList scrollList1;
    touchgfx::DrawableListItems<CustomContainer0, 9> scrollList1ListItems;
    touchgfx::ToggleButton btnTempSelectALL;
    touchgfx::Button button1;
    touchgfx::TextAreaWithOneWildcard textArea1;
    touchgfx::TextAreaWithOneWildcard textArea2;
    touchgfx::TextAreaWithOneWildcard textArea3;
    touchgfx::TextAreaWithOneWildcard textArea4;
    touchgfx::TextAreaWithOneWildcard textArea5;
    touchgfx::TextAreaWithOneWildcard textArea6;
    touchgfx::TextAreaWithOneWildcard textArea7;
    touchgfx::TextAreaWithOneWildcard textArea8;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea1Buffer[TEXTAREA1_SIZE];
    static const uint16_t TEXTAREA2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea2Buffer[TEXTAREA2_SIZE];
    static const uint16_t TEXTAREA3_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea3Buffer[TEXTAREA3_SIZE];
    static const uint16_t TEXTAREA4_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea4Buffer[TEXTAREA4_SIZE];
    static const uint16_t TEXTAREA5_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea5Buffer[TEXTAREA5_SIZE];
    static const uint16_t TEXTAREA6_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea6Buffer[TEXTAREA6_SIZE];
    static const uint16_t TEXTAREA7_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea7Buffer[TEXTAREA7_SIZE];
    static const uint16_t TEXTAREA8_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea8Buffer[TEXTAREA8_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen2ViewBase, const touchgfx::AbstractButton&> buttonCallback;
    touchgfx::Callback<Screen2ViewBase, touchgfx::DrawableListItemsInterface*, int16_t, int16_t> updateItemCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // SCREEN2VIEWBASE_HPP
