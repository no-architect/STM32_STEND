/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1VIEWBASE_HPP
#define SCREEN1VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Image.hpp>

class Screen1ViewBase : public touchgfx::View<Screen1Presenter>
{
public:
    Screen1ViewBase();
    virtual ~Screen1ViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void buttonUpClick()
    {
        // Override and implement this function in Screen1
    }

    virtual void buttonDownClick()
    {
        // Override and implement this function in Screen1
    }

    virtual void saveSettings()
    {
        // Override and implement this function in Screen1
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
    touchgfx::ButtonWithLabel buttonWithLabelSettings;
    touchgfx::ButtonWithLabel buttonUp;
    touchgfx::ButtonWithLabel buttonDown;
    touchgfx::TextAreaWithOneWildcard textCounter;
    touchgfx::ButtonWithLabel SWButtonHWLED;
    touchgfx::ButtonWithLabel SWButtonSWLED;
    touchgfx::Image SwLedOff;
    touchgfx::Image SwLedOn;
    touchgfx::TextAreaWithOneWildcard textTemp;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTCOUNTER_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textCounterBuffer[TEXTCOUNTER_SIZE];
    static const uint16_t TEXTTEMP_SIZE = 20;
    touchgfx::Unicode::UnicodeChar textTempBuffer[TEXTTEMP_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen1ViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SCREEN1VIEWBASE_HPP