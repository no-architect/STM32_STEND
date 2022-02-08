#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::swButtonHwLedToggle()
{
	model->toggleHwLed();
}

void Screen1Presenter::swButtonSwLedToggle()
{
	view.toggleSwLed();
}

void Screen1Presenter::userButtonPress()
{
	view.toggleSwLed();
}

void Screen1Presenter::newJunctionTempValue(float value)
{
	view.setJunctionTempValue(value);
}
