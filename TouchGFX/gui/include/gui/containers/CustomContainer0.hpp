#ifndef CUSTOMCONTAINER0_HPP
#define CUSTOMCONTAINER0_HPP

#include <gui_generated/containers/CustomContainer0Base.hpp>

class CustomContainer0 : public CustomContainer0Base
{
public:
    CustomContainer0();
    virtual ~CustomContainer0() {}

    virtual void initialize();

    void setListElements(int item);
    void setListElementsCheck(int item, bool check);
    void setCheckElement1(int item, float temp);
    void setCheckElement2(int item, float temp);
    void setCheckElement3(int item, float temp);
    void setTempCheckElement(int index, float temp, float minTemp, float maxTemp);
    void setTempUnCheckElement(int index);
    int getListElementsCheck();
protected:
};

#endif // CUSTOMCONTAINER0_HPP
