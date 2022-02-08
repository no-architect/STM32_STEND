#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void buttonUpClick();
    virtual void buttonDownClick();
    virtual void handleTickEvent();

    void toggleSwLed();
    void setJunctionTempValue(float value);

    virtual void saveSettings()
    {
    	presenter->saveCounter(counter);
    }
protected:
    int16_t counter;
    int16_t tickCount;
    int lastTempValue;
};

#endif // SCREEN1VIEW_HPP
