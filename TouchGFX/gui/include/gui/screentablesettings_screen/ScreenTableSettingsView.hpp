#ifndef SCREENTABLESETTINGSVIEW_HPP
#define SCREENTABLESETTINGSVIEW_HPP

#include <gui_generated/screentablesettings_screen/ScreenTableSettingsViewBase.hpp>
#include <gui/screentablesettings_screen/ScreenTableSettingsPresenter.hpp>

class ScreenTableSettingsView : public ScreenTableSettingsViewBase
{
public:
    ScreenTableSettingsView();
    virtual ~ScreenTableSettingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREENTABLESETTINGSVIEW_HPP
