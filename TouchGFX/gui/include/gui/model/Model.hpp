#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/hal/types.hpp>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void toggleHwLed();

    void saveCounter(int16_t saveCounter)
    {
    	counter = saveCounter;
    }

    int16_t getCounter()
    {
    	return counter;
    }
    float getTempValue();
    float getTempIndexValue(int value);

    void saveIndexTemp(int value)
    {
    	indexTemp = value;
    }

    void saveIndexTempValue(float value)
    {
    	indexTempValue = value;
    }

    int getIndexTemp()
    {
    	return indexTemp;
    }

    float getIndexTempValue()
    {
    	return indexTempValue;
    }

protected:
    ModelListener* modelListener;
    int16_t counter;
    float indexTempValue;
    int indexTemp;
    int32_t tickCounter;
};

#endif // MODEL_HPP
