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

    int getListElementsCheck();
protected:
};

#endif // CUSTOMCONTAINER0_HPP
