#ifndef SCREENTABLEVIEW_HPP
#define SCREENTABLEVIEW_HPP

#include <gui_generated/screentable_screen/ScreenTableViewBase.hpp>
#include <gui/screentable_screen/ScreenTablePresenter.hpp>

class ScreenTableView : public ScreenTableViewBase
{
public:
    ScreenTableView();
    virtual ~ScreenTableView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void virtChooseTemp();
protected:
};

#endif // SCREENTABLEVIEW_HPP
