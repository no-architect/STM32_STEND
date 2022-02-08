#ifndef SCREENTABLEPRESENTER_HPP
#define SCREENTABLEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenTableView;

class ScreenTablePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenTablePresenter(ScreenTableView& v);

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

    virtual ~ScreenTablePresenter() {};

private:
    ScreenTablePresenter();

    ScreenTableView& view;
};

#endif // SCREENTABLEPRESENTER_HPP
