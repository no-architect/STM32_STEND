#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void scrollList1UpdateItem(CustomContainer0& item, int16_t itemIndex);
    virtual void checkALL();
    void setBtn1(float value);
protected:
    Callback<Screen2View, int16_t> scrollList1_ItemSelectedCallback;
    void scrollList1_ItemSelectedHandler(int16_t itemSelected);
};

#endif // SCREEN2VIEW_HPP
