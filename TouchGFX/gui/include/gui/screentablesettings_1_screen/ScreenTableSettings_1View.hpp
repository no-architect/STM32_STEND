#ifndef SCREENTABLESETTINGS_1VIEW_HPP
#define SCREENTABLESETTINGS_1VIEW_HPP

#include <gui_generated/screentablesettings_1_screen/ScreenTableSettings_1ViewBase.hpp>
#include <gui/screentablesettings_1_screen/ScreenTableSettings_1Presenter.hpp>

class ScreenTableSettings_1View : public ScreenTableSettings_1ViewBase
{
public:
    ScreenTableSettings_1View();
    virtual ~ScreenTableSettings_1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREENTABLESETTINGS_1VIEW_HPP
