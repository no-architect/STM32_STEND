
#include <math.h>
#include "max31865.h"
#include "MCP23S17.h"

//#include "max31865Conf.h"
//#if (_MAX31865_USE_FREERTOS == 1)
//#include "cmsis_os.h"
//#endif

//#########################################################################################################################
#define MAX31856_CONFIG_REG             0x00
#define MAX31856_CONFIG_BIAS            0x80
#define MAX31856_CONFIG_MODEAUTO        0x40
#define MAX31856_CONFIG_MODEOFF         0x00
#define MAX31856_CONFIG_1SHOT           0x20
#define MAX31856_CONFIG_3WIRE           0x10
#define MAX31856_CONFIG_24WIRE          0x00
#define MAX31856_CONFIG_FAULTSTAT       0x02
#define MAX31856_CONFIG_FILT50HZ        0x01
#define MAX31856_CONFIG_FILT60HZ        0x00

#define MAX31856_RTDMSB_REG             0x01
#define MAX31856_RTDLSB_REG             0x02
#define MAX31856_HFAULTMSB_REG          0x03
#define MAX31856_HFAULTLSB_REG          0x04
#define MAX31856_LFAULTMSB_REG          0x05
#define MAX31856_LFAULTLSB_REG          0x06
#define MAX31856_FAULTSTAT_REG          0x07


#define MAX31865_FAULT_HIGHTHRESH       0x80
#define MAX31865_FAULT_LOWTHRESH        0x40
#define MAX31865_FAULT_REFINLOW         0x20
#define MAX31865_FAULT_REFINHIGH        0x10
#define MAX31865_FAULT_RTDINLOW         0x08
#define MAX31865_FAULT_OVUV             0x04


#define RTD_A 3.9083e-3
#define RTD_B -5.775e-7

#define MAX31865_RREF      430.0f
#define MAX31865_RNOMINAL  100.0f
//#########################################################################################################################
void  Max31865_delay(uint32_t delay_ms)
{
//  #if (_MAX31865_USE_FREERTOS == 1)
//  osDelay(delay_ms);
//  #else
  HAL_Delay(delay_ms);
//  #endif
}
//#########################################################################################################################
void Max31865_readRegisterN(Max31865_t *max31865,uint8_t addr, uint8_t *buffer, uint8_t n)
{
  uint8_t tmp = 0xFF;
	addr &= 0x7F;
	HAL_GPIO_WritePin(max31865->cs_gpio, max31865->cs_pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(max31865->spi,&addr, 1, 100);
	while (n--)
	{
    HAL_SPI_TransmitReceive(max31865->spi, &tmp, buffer, 1, 100);
		buffer++;
	}
	HAL_GPIO_WritePin(max31865->cs_gpio, max31865->cs_pin, GPIO_PIN_SET);
}
void Max31865_readRegisterN_index(Max31865_t *max31865,uint8_t addr, uint8_t *buffer, uint8_t n, uint8_t index)
{
  uint8_t tmp = 0xFF;
	addr &= 0x7F;
	// CS = 0 for MAX[index]
	MCP23x17_write_index(MAX[index].portX, MCP23x17_OLAT, MAX[index].OLAT, MAX[index].indexMCP, MCP_TEMP);

	HAL_SPI_Transmit(max31865->spi,&addr, 1, 100);

	while (n--)
	{
		HAL_SPI_TransmitReceive(max31865->spi, &tmp, buffer, 1, 100);
		buffer++;
	}

	// CS = 1 for MAX[index]
	MCP23x17_write_index(MAX[index].portX, MCP23x17_OLAT, 0xFF, MAX[index].indexMCP, MCP_TEMP);

}
//#########################################################################################################################
uint8_t Max31865_readRegister8(Max31865_t *max31865,uint8_t addr)
{
  uint8_t ret = 0;
	Max31865_readRegisterN(max31865, addr, &ret, 1);
	return ret;
}
uint8_t Max31865_readRegister8_portA(Max31865_t *max31865,uint8_t addr, MCP23x17_t *driver, uint8_t value)
{
  uint8_t ret = 0;
	Max31865_readRegisterN_portA(max31865, addr, &ret, 1, driver, value);
	return ret;
}
uint8_t Max31865_readRegister8_index(Max31865_t *max31865,uint8_t addr, uint8_t index)
{
	uint8_t ret = 0;
	Max31865_readRegisterN_index(max31865, addr, &ret, 1, index);
	return ret;
}
//#########################################################################################################################
uint16_t Max31865_readRegister16(Max31865_t *max31865,uint8_t addr)
{
	uint8_t buffer[2] = {0, 0};
	Max31865_readRegisterN(max31865, addr, buffer, 2);
	uint16_t ret = buffer[0];
	ret <<= 8;
	ret |=  buffer[1];
	return ret;
}
uint16_t Max31865_readRegister16_portA(Max31865_t *max31865,uint8_t addr, MCP23x17_t *driver, uint8_t value)
{
	uint8_t buffer[2] = {0, 0};
	Max31865_readRegisterN_portA(max31865, addr, buffer, 2, driver, value);
	uint16_t ret = buffer[0];
	ret <<= 8;
	ret |=  buffer[1];
	return ret;
}
uint16_t Max31865_readRegister16_index(Max31865_t *max31865,uint8_t addr, uint8_t index)
{
	uint8_t buffer[2] = {0, 0};
	Max31865_readRegisterN_index(max31865, addr, buffer, 2, index);
	uint16_t ret = buffer[0];
	ret <<= 8;
	ret |=  buffer[1];
	return ret;
}
//#########################################################################################################################
void Max31865_writeRegister8(Max31865_t *max31865,uint8_t addr, uint8_t data)
{
	HAL_GPIO_WritePin(max31865->cs_gpio, max31865->cs_pin, GPIO_PIN_RESET);
  addr |= 0x80;
	HAL_SPI_Transmit(max31865->spi,&addr, 1, 100);
	HAL_SPI_Transmit(max31865->spi,&data, 1, 100);
	HAL_GPIO_WritePin(max31865->cs_gpio, max31865->cs_pin, GPIO_PIN_SET);
}
void Max31865_writeRegister8_portA(Max31865_t *max31865,uint8_t addr, uint8_t data, MCP23x17_t *driver, uint8_t value)
{
	//HAL_GPIO_WritePin(max31865->cs_gpio, max31865->cs_pin, GPIO_PIN_RESET);
	MCP23x17_writeportA(driver, 0x00);
  addr |= 0x80;
	HAL_SPI_Transmit(max31865->spi,&addr, 1, 100);
	HAL_SPI_Transmit(max31865->spi,&data, 1, 100);
	//HAL_GPIO_WritePin(max31865->cs_gpio, max31865->cs_pin, GPIO_PIN_SET);
	MCP23x17_writeportA(driver, 0xFF);
}
void Max31865_writeRegister8_index(Max31865_t *max31865,uint8_t addr, uint8_t data, uint8_t index)
{
	// CS = 0 for MAX[index]
	MCP23x17_write_index(MAX[index].portX, MCP23x17_OLAT, MAX[index].OLAT, MAX[index].indexMCP, MCP_TEMP);

	addr |= 0x80;
	HAL_SPI_Transmit(max31865->spi,&addr, 1, 100);
	HAL_SPI_Transmit(max31865->spi,&data, 1, 100);

	// CS = 1 for MAX[index]
	MCP23x17_write_index(MAX[index].portX, MCP23x17_OLAT, 0xFF, MAX[index].indexMCP, MCP_TEMP);
}
//#########################################################################################################################
uint8_t Max31865_readFault(Max31865_t *max31865)
{
  return Max31865_readRegister8(max31865, MAX31856_FAULTSTAT_REG);
}
uint8_t Max31865_readFault_portA(Max31865_t *max31865, MCP23x17_t *driver, uint8_t value)
{
  return Max31865_readRegister8_portA(max31865, MAX31856_FAULTSTAT_REG, driver, value);
}
uint8_t Max31865_readFault_index(Max31865_t *max31865, uint8_t index)
{
  return Max31865_readRegister8_index(max31865, MAX31856_FAULTSTAT_REG, index);
}
//#########################################################################################################################
void Max31865_clearFault(Max31865_t *max31865)
{
	uint8_t t = Max31865_readRegister8(max31865, MAX31856_CONFIG_REG);
	t &= ~0x2C;
	t |= MAX31856_CONFIG_FAULTSTAT;
	Max31865_writeRegister8(max31865, MAX31856_CONFIG_REG, t);
}
void Max31865_clearFault_portA(Max31865_t *max31865,  MCP23x17_t *driver, uint8_t value)
{
	uint8_t t = Max31865_readRegister8_portA(max31865, MAX31856_CONFIG_REG, driver, value);
	t &= ~0x2C;
	t |= MAX31856_CONFIG_FAULTSTAT;
	Max31865_writeRegister8_portA(max31865, MAX31856_CONFIG_REG, t, driver, value);
}
void Max31865_clearFault_index(Max31865_t *max31865,  uint8_t index)
{
	uint8_t t = Max31865_readRegister8_index(max31865, MAX31856_CONFIG_REG, index);
	t &= ~0x2C;
	t |= MAX31856_CONFIG_FAULTSTAT;
	Max31865_writeRegister8_index(max31865, MAX31856_CONFIG_REG, t, index);
}
//#########################################################################################################################
void Max31865_enableBias(Max31865_t *max31865, uint8_t enable)
{
	uint8_t t = Max31865_readRegister8(max31865, MAX31856_CONFIG_REG);
	if (enable)
		t |= MAX31856_CONFIG_BIAS;
	else
		t &= ~MAX31856_CONFIG_BIAS;
	Max31865_writeRegister8(max31865, MAX31856_CONFIG_REG, t);
}
void Max31865_enableBias_portA(Max31865_t *max31865, uint8_t enable,  MCP23x17_t *driver, uint8_t value)
{
	uint8_t t = Max31865_readRegister8_portA(max31865, MAX31856_CONFIG_REG, driver, value);
	if (enable)
		t |= MAX31856_CONFIG_BIAS;
	else
		t &= ~MAX31856_CONFIG_BIAS;
	Max31865_writeRegister8_portA(max31865, MAX31856_CONFIG_REG, t, driver, value);
}
void Max31865_enableBias_index(Max31865_t *max31865, uint8_t enable, uint8_t index)
{
	uint8_t t = Max31865_readRegister8_index(max31865, MAX31856_CONFIG_REG, index);
	if (enable)
		t |= MAX31856_CONFIG_BIAS;
	else
		t &= ~MAX31856_CONFIG_BIAS;
	Max31865_writeRegister8_index(max31865, MAX31856_CONFIG_REG, t, index);
}
//#########################################################################################################################
void Max31865_autoConvert(Max31865_t *max31865, uint8_t enable)
{
	uint8_t t = Max31865_readRegister8(max31865, MAX31856_CONFIG_REG);
	if (enable)
		t |= MAX31856_CONFIG_MODEAUTO;
	else
		t &= ~MAX31856_CONFIG_MODEAUTO;
	Max31865_writeRegister8(max31865, MAX31856_CONFIG_REG, t);
}
void Max31865_autoConvert_portA(Max31865_t *max31865, uint8_t enable,  MCP23x17_t *driver, uint8_t value)
{
	uint8_t t = Max31865_readRegister8_portA(max31865, MAX31856_CONFIG_REG, driver, value);
	if (enable)
		t |= MAX31856_CONFIG_MODEAUTO;
	else
		t &= ~MAX31856_CONFIG_MODEAUTO;
	Max31865_writeRegister8_portA(max31865, MAX31856_CONFIG_REG, t, driver, value);
}
void Max31865_autoConvert_index(Max31865_t *max31865, uint8_t enable, uint8_t index)
{
	uint8_t t = Max31865_readRegister8_index(max31865, MAX31856_CONFIG_REG, index);
	if (enable)
		t |= MAX31856_CONFIG_MODEAUTO;
	else
		t &= ~MAX31856_CONFIG_MODEAUTO;
	Max31865_writeRegister8_index(max31865, MAX31856_CONFIG_REG, t, index);
}
//#########################################################################################################################
void Max31865_setWires(Max31865_t *max31865, uint8_t numWires)
{
	uint8_t t = Max31865_readRegister8(max31865, MAX31856_CONFIG_REG);
	if (numWires == 3)
		t |= MAX31856_CONFIG_3WIRE;
	else
		t &= ~MAX31856_CONFIG_3WIRE;
	Max31865_writeRegister8(max31865, MAX31856_CONFIG_REG, t);
}
void Max31865_setWires_portA(Max31865_t *max31865, uint8_t numWires,  MCP23x17_t *driver, uint8_t value)
{
	uint8_t t = Max31865_readRegister8_portA(max31865, MAX31856_CONFIG_REG, driver, value);
	if (numWires == 3)
		t |= MAX31856_CONFIG_3WIRE;
	else
		t &= ~MAX31856_CONFIG_3WIRE;
	Max31865_writeRegister8_portA(max31865, MAX31856_CONFIG_REG, t, driver, value);
}
void Max31865_setWires_index(Max31865_t *max31865, uint8_t numWires,  uint8_t index)
{
	uint8_t t = Max31865_readRegister8_index(max31865, MAX31856_CONFIG_REG, index);
	if (numWires == 3)
		t |= MAX31856_CONFIG_3WIRE;
	else
		t &= ~MAX31856_CONFIG_3WIRE;
	Max31865_writeRegister8_index(max31865, MAX31856_CONFIG_REG, t, index);
}
//#########################################################################################################################
void Max31865_setFilter(Max31865_t *max31865, uint8_t filterHz)
{
	uint8_t t = Max31865_readRegister8(max31865, MAX31856_CONFIG_REG);
	if (filterHz == 50)
		t |= MAX31856_CONFIG_FILT50HZ;
	else
		t &= ~MAX31856_CONFIG_FILT50HZ;
	Max31865_writeRegister8(max31865, MAX31856_CONFIG_REG, t);
}
void Max31865_setFilter_portA(Max31865_t *max31865, uint8_t filterHz,  MCP23x17_t *driver, uint8_t value)
{
	uint8_t t = Max31865_readRegister8_portA(max31865, MAX31856_CONFIG_REG, driver, value);
	if (filterHz == 50)
		t |= MAX31856_CONFIG_FILT50HZ;
	else
		t &= ~MAX31856_CONFIG_FILT50HZ;
	Max31865_writeRegister8_portA(max31865, MAX31856_CONFIG_REG, t, driver, value);
}
void Max31865_setFilter_index(Max31865_t *max31865, uint8_t filterHz, uint8_t index)
{
	uint8_t t = Max31865_readRegister8_index(max31865, MAX31856_CONFIG_REG, index);
	if (filterHz == 50)
		t |= MAX31856_CONFIG_FILT50HZ;
	else
		t &= ~MAX31856_CONFIG_FILT50HZ;
	Max31865_writeRegister8_index(max31865, MAX31856_CONFIG_REG, t, index);
}
//#########################################################################################################################
uint16_t Max31865_readRTD (Max31865_t *max31865)
{
	Max31865_clearFault(max31865);
	Max31865_enableBias(max31865, 1);
	Max31865_delay(10);
	uint8_t t = Max31865_readRegister8(max31865, MAX31856_CONFIG_REG);
	t |= MAX31856_CONFIG_1SHOT;
	Max31865_writeRegister8(max31865, MAX31856_CONFIG_REG, t);
	Max31865_delay(65);
	uint16_t rtd = Max31865_readRegister16(max31865, MAX31856_RTDMSB_REG);
	rtd >>= 1;
	return rtd;
}
uint16_t Max31865_readRTD_portA (Max31865_t *max31865,  MCP23x17_t *driver, uint8_t value)
{
	Max31865_clearFault_portA(max31865, driver, value);
	Max31865_enableBias_portA(max31865, 1, driver, value);
	Max31865_delay(10);
	uint8_t t = Max31865_readRegister8_portA(max31865, MAX31856_CONFIG_REG, driver, value);
	t |= MAX31856_CONFIG_1SHOT;
	Max31865_writeRegister8_portA(max31865, MAX31856_CONFIG_REG, t, driver, value);
	Max31865_delay(65);
	uint16_t rtd = Max31865_readRegister16_portA(max31865, MAX31856_RTDMSB_REG, driver, value);
	rtd >>= 1;
	return rtd;
}
uint16_t Max31865_readRTD_index (Max31865_t *max31865, uint8_t index)
{
	Max31865_clearFault_index(max31865, index);
	Max31865_enableBias_index(max31865, 1, index);
	Max31865_delay(10);
	uint8_t t = Max31865_readRegister8_index(max31865, MAX31856_CONFIG_REG, index);
	t |= MAX31856_CONFIG_1SHOT;
	Max31865_writeRegister8_index(max31865, MAX31856_CONFIG_REG, t, index);
	Max31865_delay(65);
	uint16_t rtd = Max31865_readRegister16_index(max31865, MAX31856_RTDMSB_REG, index);
	rtd >>= 1;
	return rtd;
}
//#########################################################################################################################
//#########################################################################################################################
//#########################################################################################################################
void  Max31865_init(Max31865_t *max31865,SPI_HandleTypeDef *spi,GPIO_TypeDef  *cs_gpio,uint16_t cs_pin,uint8_t  numwires, uint8_t filterHz)
{
  if(max31865->lock == 1)
    Max31865_delay(1);
  max31865->lock = 1;
  max31865->spi = spi;
  max31865->cs_gpio = cs_gpio;
  max31865->cs_pin = cs_pin;
  HAL_GPIO_WritePin(max31865->cs_gpio,max31865->cs_pin,GPIO_PIN_SET);
  Max31865_delay(100);
  Max31865_setWires(max31865, numwires);
	Max31865_enableBias(max31865, 0);
	Max31865_autoConvert(max31865, 0);
	Max31865_clearFault(max31865);
  Max31865_setFilter(max31865, filterHz);
}
void  Max31865_init_portA(Max31865_t *max31865,SPI_HandleTypeDef *spi,GPIO_TypeDef  *cs_gpio,uint16_t cs_pin,uint8_t  numwires, uint8_t filterHz, MCP23x17_t *driver, uint8_t value)
{
  if(max31865->lock == 1)
    Max31865_delay(1);
  max31865->lock = 1;
  max31865->spi = spi;
  max31865->cs_gpio = cs_gpio;
  max31865->cs_pin = cs_pin;
  //HAL_GPIO_WritePin(max31865->cs_gpio,max31865->cs_pin,GPIO_PIN_SET);
  MCP23x17_writeportA(driver, 0xFE);
  MCP23x17_writeportB(driver, 0xFF);
  Max31865_delay(100);

  Max31865_setWires_portA(max31865, numwires, driver, value);
	Max31865_enableBias_portA(max31865, 0, driver, value);
	Max31865_autoConvert_portA(max31865, 0, driver, value);
	Max31865_clearFault_portA(max31865, driver, value);
  Max31865_setFilter_portA(max31865, filterHz, driver, value);
}
void  Max31865_init_ALL(Max31865_t *max31865, SPI_HandleTypeDef *spi, GPIO_TypeDef  *cs_gpio, uint16_t cs_pin, uint8_t numwires, uint8_t filterHz)
{
  if(max31865->lock == 1)
    Max31865_delay(1);
  max31865->lock = 1;
  max31865->spi = spi;
  max31865->cs_gpio = cs_gpio;
  max31865->cs_pin = cs_pin;

  //HAL_GPIO_WritePin(max31865->cs_gpio,max31865->cs_pin,GPIO_PIN_SET);
  int i;
  i = MAX[0].indexMCP;
  for (i=0; i<MAX_COUNT; i++)
  {
	  //--- ALL CS = 1
	  MCP23x17_write_index(MAX[i].portX, MCP23x17_OLAT, 0xFF, MAX[i].indexMCP, MCP_TEMP);

	  Max31865_delay(100);

	  Max31865_setWires_index(max31865, numwires, i);
	  Max31865_enableBias_index(max31865, 0, i);
	  Max31865_autoConvert_index(max31865, 0, i);
	  Max31865_clearFault_index(max31865, i);
	  Max31865_setFilter_index(max31865, filterHz, i);
  }
}
void  Max31865_init_index(Max31865_t *max31865, SPI_HandleTypeDef *spi, GPIO_TypeDef  *cs_gpio, uint16_t cs_pin, uint8_t numwires, uint8_t filterHz, uint8_t index)
{
  if(max31865->lock == 1)
    Max31865_delay(1);
  max31865->lock = 1;
  max31865->spi = spi;
  max31865->cs_gpio = cs_gpio;
  max31865->cs_pin = cs_pin;

  //HAL_GPIO_WritePin(max31865->cs_gpio,max31865->cs_pin,GPIO_PIN_SET);
  int i;
  i = MAX[0].indexMCP;

  MCP23x17_write_index(MAX[index].portX, MCP23x17_OLAT, MAX[index].OLAT, MAX[index].indexMCP, MCP_TEMP);

  Max31865_delay(100);

  Max31865_setWires_index(max31865, numwires, index);
  Max31865_enableBias_index(max31865, 0, index);
  Max31865_autoConvert_index(max31865, 0, index);
  Max31865_clearFault_index(max31865, index);
  Max31865_setFilter_index(max31865, filterHz, index);

}
//#########################################################################################################################
bool Max31865_readTempC(Max31865_t *max31865,float *readTemp)
{
  if(max31865->lock == 1)
    Max31865_delay(1);
  max31865->lock = 1;
  bool isOk = false;
  float Z1, Z2, Z3, Z4, Rt, Rt1, temp;
	Rt1 = Max31865_readRTD(max31865);
	Rt = Rt1/32768;
	Rt *= MAX31865_RREF;
	Z1 = -RTD_A;
	Z2 = RTD_A * RTD_A - (4 * RTD_B);
	Z3 = (4 * RTD_B) / MAX31865_RNOMINAL;
	Z4 = 2 * RTD_B;
	temp = Z2 + (Z3 * Rt);
	temp = (sqrtf(temp) + Z1) / Z4;

	if (temp >= 0)
  {
    *readTemp = temp;
    if(Max31865_readFault(max31865) == 0)
      isOk = true;
    max31865->lock = 0;
    return isOk;
  }
	Rt /= MAX31865_RNOMINAL;
	Rt *= 100;
	float rpoly = Rt;
	temp = -242.02;
	temp += 2.2228 * rpoly;
	rpoly *= Rt;  // square
	temp += 2.5859e-3 * rpoly;
	rpoly *= Rt;  // ^3
	temp -= 4.8260e-6 * rpoly;
	rpoly *= Rt;  // ^4
	temp -= 2.8183e-8 * rpoly;
	rpoly *= Rt;  // ^5
	temp += 1.5243e-10 * rpoly;

  *readTemp = temp;
  if(Max31865_readFault(max31865) == 0)
    isOk = true;
  max31865->lock = 0;
  return isOk;
}
bool Max31865_readTempC_portA(Max31865_t *max31865,float *readTemp, MCP23x17_t *driver, uint8_t value)
{
  if(max31865->lock == 1)
    Max31865_delay(1);
  max31865->lock = 1;
  bool isOk = false;
  float Z1, Z2, Z3, Z4, Rt, Rt1, temp;
	Rt1 = Max31865_readRTD_portA(max31865, driver, value);
	Rt = Rt1/32768;
	Rt *= MAX31865_RREF;
	Z1 = -RTD_A;
	Z2 = RTD_A * RTD_A - (4 * RTD_B);
	Z3 = (4 * RTD_B) / MAX31865_RNOMINAL;
	Z4 = 2 * RTD_B;
	temp = Z2 + (Z3 * Rt);
	temp = (sqrtf(temp) + Z1) / Z4;

	if (temp >= 0)
  {
    *readTemp = temp;
    if(Max31865_readFault_portA(max31865, driver, value) == 0)
      isOk = true;
    max31865->lock = 0;
    return isOk;
  }
	Rt /= MAX31865_RNOMINAL;
	Rt *= 100;
	float rpoly = Rt;
	temp = -242.02;
	temp += 2.2228 * rpoly;
	rpoly *= Rt;  // square
	temp += 2.5859e-3 * rpoly;
	rpoly *= Rt;  // ^3
	temp -= 4.8260e-6 * rpoly;
	rpoly *= Rt;  // ^4
	temp -= 2.8183e-8 * rpoly;
	rpoly *= Rt;  // ^5
	temp += 1.5243e-10 * rpoly;

  *readTemp = temp;
  if(Max31865_readFault_portA(max31865, driver, value) == 0)
    isOk = true;
  max31865->lock = 0;
  return isOk;
}
bool Max31865_readTempC_index(Max31865_t *max31865,float *readTemp, uint8_t index)
{
  if(max31865->lock == 1)
    Max31865_delay(1);
  max31865->lock = 1;
  bool isOk = false;
  float Z1, Z2, Z3, Z4, Rt, Rt1, temp;
	Rt1 = Max31865_readRTD_index(max31865, index);
	Rt = Rt1/32768;
	Rt *= MAX31865_RREF;
	Z1 = -RTD_A;
	Z2 = RTD_A * RTD_A - (4 * RTD_B);
	Z3 = (4 * RTD_B) / MAX31865_RNOMINAL;
	Z4 = 2 * RTD_B;
	temp = Z2 + (Z3 * Rt);
	temp = (sqrtf(temp) + Z1) / Z4;

	if (temp >= 0)
  {
    *readTemp = temp;
    if(Max31865_readFault_index(max31865, index) == 0)
      isOk = true;
    max31865->lock = 0;
    return isOk;
  }
	Rt /= MAX31865_RNOMINAL;
	Rt *= 100;
	float rpoly = Rt;
	temp = -242.02;
	temp += 2.2228 * rpoly;
	rpoly *= Rt;  // square
	temp += 2.5859e-3 * rpoly;
	rpoly *= Rt;  // ^3
	temp -= 4.8260e-6 * rpoly;
	rpoly *= Rt;  // ^4
	temp -= 2.8183e-8 * rpoly;
	rpoly *= Rt;  // ^5
	temp += 1.5243e-10 * rpoly;

  *readTemp = temp;

  if(Max31865_readFault_index(max31865, index) == 0)
    isOk = true;
  max31865->lock = 0;
  return isOk;
}
//#########################################################################################################################
bool  Max31865_readTempF(Max31865_t *max31865,float *readTemp)
{
  bool isOk = Max31865_readTempC(max31865,readTemp);
  *readTemp = (*readTemp * 9.0f / 5.0f) + 32.0f;
  return isOk;
}
//#########################################################################################################################
float Max31865_Filter(float	newInput, float	lastOutput, float efectiveFactor)
{
	return ((float)lastOutput*(1.0f-efectiveFactor)) + ((float)newInput*efectiveFactor) ;
}
//#########################################################################################################################
