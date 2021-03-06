#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern "C" {
	extern void SET_TIM1_PWM_PULSE(int setPWM);
	extern uint32_t userButtonPressed;
	extern float TEMP_SENSOR_GetValue(void);
	extern float TEMP_SENSOR_INDEX_GetValue(int valval);
}
int prom;

Model::Model() : modelListener(0), counter(), indexTemp(0), indexTempValue(0)
{

}

void Model::tick()
{
	tickCounter++;
	if (prom != counter)
	{
		prom = counter;
		SET_TIM1_PWM_PULSE(counter);
	}

	if(tickCounter%5000)
	{
		tickCounter = 0;


		//indexTempValue = getTempIndexValue(indexTemp);
		//modelListener->newJunctionTempValue(getTempValue());
		//if (modelListener != 0)
		//{
		//	modelListener->newJunctionTempValue(35);
		//}
	}

//#ifdef SIMULATOR
	if(userButtonPressed == 1)
	{
		userButtonPressed = 0;
		//modelListener->userButtonPress();
		modelListener->newJunctionTempValue(getTempIndexValue(counter));
		//modelListener->newJunctionTempValue(getTempValue());
		//modelListener->btnBtn1(getTempIndexValue(counter));
	}
	//modelListener->btnBtn1(getTempIndexValue(int valval3));
//#endif
}



void Model::toggleHwLed()
{
#ifdef SIMULATOR
	//userButtonPressed = 1;
	SET_TIM1_PWM_PULSE(counter);
#endif
}

float Model::getTempValue()
{
#ifndef SIMULATOR
	//return 36;
	return TEMP_SENSOR_GetValue();
#else
	return 25f;
#endif
}

float Model::getTempIndexValue(int valval2)
{
#ifndef SIMULATOR
	//return 36;
	return TEMP_SENSOR_INDEX_GetValue(valval2);
#else
	return 99f;
#endif
}
