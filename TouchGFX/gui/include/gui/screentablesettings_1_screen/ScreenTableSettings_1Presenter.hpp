#ifndef SCREENTABLESETTINGS_1PRESENTER_HPP
#define SCREENTABLESETTINGS_1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenTableSettings_1View;

class ScreenTableSettings_1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenTableSettings_1Presenter(ScreenTableSettings_1View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ScreenTableSettings_1Presenter() {};

private:
    ScreenTableSettings_1Presenter();

    ScreenTableSettings_1View& view;
};

#endif // SCREENTABLESETTINGS_1PRESENTER_HPP
