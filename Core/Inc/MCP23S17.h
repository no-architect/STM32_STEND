
#ifndef _MCP23x17_H_
#define _MCP23x17_H_

#include <stdint.h>
#include "stm32f7xx_hal.h"

extern SPI_HandleTypeDef hspi2;

#define MCP23x17_READ_CONTROLE_BYTE 	0x41u
#define MCP23x17_WRITE_CONTROLE_BYTE 	0x40u

#define ADD_0 0b000
#define ADD_1 0b001
#define ADD_2 0b010
#define ADD_3 0b011
#define ADD_4 0b100
#define ADD_5 0b101
#define ADD_6 0b110
#define ADD_7 0b111

#define BIT_0 ~0b00000001
#define BIT_1 ~0b00000010
#define BIT_2 ~0b00000100
#define BIT_3 ~0b00001000
#define BIT_4 ~0b00010000
#define BIT_5 ~0b00100000
#define BIT_6 ~0b01000000
#define BIT_7 ~0b10000000


/*
------------------------------------------------------------
 BANK 0 Registers Addresses
------------------------------------------------------------
BANK0_IODIRA  	= 0
BANK0_IODIRB	= 1
BANK0_IPOLA	    = 2
BANK0_IPOLB	    = 3
BANK0_GPINTENA  = 4
BANK0_GPINTENB  = 5
BANK0_DEFVALA	= 6
BANK0_DEFVALB	= 7
BANK0_INTCONA	= 8
BANK0_INTCONB	= 9
BANK0_IOCONA	= 10
BANK0_IOCONB	= 11
BANK0_GPPUA	    = 12
BANK0_GPPUB	    = 13
BANK0_INTFA	    = 14
BANK0_INTFB	    = 15
BANK0_INTCAPA	= 16
BANK0_INTCAPB	= 17
BANK0_GPIOA	    = 18
BANK0_GPIOB 	= 19
BANK0_OLATA	    = 20
BANK0_OLATB	    = 21
------------------------------------------------------------
BANK 1 Registers Addresses
------------------------------------------------------------
BANK1_IODIRA 	= 0
BANK1_IPOLA  	= 1
BANK1_GPINTENA  = 2
BANK1_DEFVALA 	= 3
BANK1_INTCONA   = 4
BANK1_IOCONA	= 5
BANK1_GPPUA	    = 6
BANK1_INTFA	    = 7
BANK1_INTCAPA	= 8
BANK1_GPIOA	    = 9
BANK1_OLATA	    = 10
BANK1_IODIRB 	= 16
BANK1_IPOLB	    = 17
BANK1_GPINTENB	= 18
BANK1_DEFVALB	= 19
BANK1_INTCONB	= 20
BANK1_IOCONB	= 21
BANK1_GPPUB	    = 22
BANK1_INTFB	    = 23
BANK1_INTCAPB	= 24
BANK1_GPIOB	    = 25
BANK1_OLATB	    = 26
*/

typedef enum MCP23x17_register_e {
	MCP23x17_IODIR,				/* IODIR: I/O DIRECTION REGISTER */
	MCP23x17_IPOL,				/* IPOL: INPUT POLARITY PORT REGISTER If a bit is set, the corresponding GPIO register bit will reflect the inverted value on the pin */
	MCP23x17_GPINTEN,			/* INTERRUPT-ON-CHANGE CONTROL REGISTER */
	MCP23x17_DEFVAL,			/* DEFAULT COMPARE REGISTER FOR INTERRUPT-ON-CHANGE */
	MCP23x17_INTCON,			/* INTERRUPT CONTROL REGISTER */
	MCP23x17_IOCON,				/* I/OEXPANDER CONFIGURATION REGISTER */
	MCP23x17_GPPU,				/* GPPU: GPIO PULL-UP RESISTOR REGISTER */
	MCP23x17_INTF,				/* READ ONLY : INTF: INTERRUPT FLAG REGISTER (ADDR 0x07) */
	MCP23x17_INTCAP,			/* READ ONLY : INTCAP: INTERRUPT CAPTURED VALUE FOR PORT REGISTER */
	MCP23x17_GPIO,				/* Port adress */
	MCP23x17_OLAT,				/* OUTPUT LATCH REGISTER */
} MCP23x17_register_t;

typedef enum MCP23x17_version_e {
	MCP23x17_UNDEFINED,
	MCP23S17_SPI,
	MCP23017_I2C,
} MCP23x17_version_t;

typedef enum MCP23x17_BANK_e {
	MCP23x17_BANK0,
	MCP23x17_BANK1,
} MCP23x17_BANK_t;

typedef enum MCP23x17_port_e {
	MCP23x17_portA,
	MCP23x17_portB,
} MCP23x17_port_t;

typedef enum MCP_TEMP_POWER_e {
	MCP_TEMP,
	MCP_POWER,
} MCP_TEMP_POWER_t;

typedef struct MCP23x17_port_config_s {
	uint8_t IODIR;
	uint8_t IPOL;
	uint8_t GPINTEN;
	uint8_t DEFVAL;
	uint8_t INTCON;
	uint8_t IOCON;
	uint8_t GPPU;
	uint8_t default_GPIO;
	uint8_t OLAT;
} MCP23x17_port_config_t;

typedef struct MCP23x17_config_s {
	MCP23x17_BANK_t 		BANK;
	MCP23x17_port_config_t 	portA;
	MCP23x17_port_config_t 	portB;
} MCP23x17_config_t;

typedef struct MCP23x17_com_s{
	MCP23x17_version_t 		protocole;
	SPI_HandleTypeDef		hspix;
	uint8_t 				Opcode:3;
} MCP23x17_com_t;

typedef struct MCP23x17_s {
	MCP23x17_com_t			com;
	MCP23x17_config_t 		config;
} MCP23x17_t;

typedef struct MCP_CSforMAX_s {
	uint8_t indexMCP;
	MCP23x17_port_t portX;
	uint8_t OLAT;
} MCP_CSforMAX_t;

static const int8_t MAX_COUNT = 70;
static const MCP_CSforMAX_t MAX[70] = { { ADD_0, MCP23x17_portB, BIT_2}, { ADD_0, MCP23x17_portA, BIT_1}, { ADD_0, MCP23x17_portA, BIT_2}, //1-3
								  	  /*4*/ { ADD_0, MCP23x17_portA, BIT_3}, { ADD_0, MCP23x17_portA, BIT_4}, { ADD_0, MCP23x17_portA, BIT_5}, //4-6
									  /*7*/ { ADD_0, MCP23x17_portA, BIT_6},   /*8*/ { ADD_0, MCP23x17_portA, BIT_7}, { ADD_0, MCP23x17_portB, BIT_0}, //9
									 /*10*/ { ADD_0, MCP23x17_portB, BIT_1},  /*11*/ { ADD_0, MCP23x17_portA, BIT_1},  /*12*/ { ADD_0, MCP23x17_portA, BIT_2},
									 /*13*/ { ADD_0, MCP23x17_portA, BIT_3},  /*14*/ { ADD_0, MCP23x17_portA, BIT_4},  /*15*/ { ADD_0, MCP23x17_portA, BIT_5},
									 /*16*/ { ADD_0, MCP23x17_portA, BIT_6},  /*17*/ { ADD_0, MCP23x17_portA, BIT_7},  /*18*/ { ADD_0, MCP23x17_portB, BIT_0},
									 /*19*/ { ADD_0, MCP23x17_portB, BIT_2},  /*20*/ { ADD_0, MCP23x17_portA, BIT_1},  /*21*/ { ADD_0, MCP23x17_portA, BIT_2},
									 /*22*/ { ADD_0, MCP23x17_portA, BIT_3},  /*23*/ { ADD_0, MCP23x17_portA, BIT_4},  /*24*/ { ADD_0, MCP23x17_portA, BIT_5},
									 /*25*/ { ADD_0, MCP23x17_portA, BIT_6},  /*26*/ { ADD_0, MCP23x17_portA, BIT_7},  /*27*/ { ADD_0, MCP23x17_portB, BIT_0},
									 /*28*/	{ ADD_0, MCP23x17_portB, BIT_1},  /*29*/ { ADD_0, MCP23x17_portA, BIT_1},  /*30*/ { ADD_0, MCP23x17_portA, BIT_2},
									 /*31*/	{ ADD_0, MCP23x17_portA, BIT_3},  /*32*/ { ADD_0, MCP23x17_portA, BIT_4},  /*33*/ { ADD_0, MCP23x17_portA, BIT_5},
									 /*34*/	{ ADD_0, MCP23x17_portA, BIT_6},  /*35*/ { ADD_0, MCP23x17_portA, BIT_7},  /*36*/ { ADD_0, MCP23x17_portB, BIT_0},
									 /*37*/	{ ADD_0, MCP23x17_portB, BIT_2},  /*38*/ { ADD_0, MCP23x17_portA, BIT_1},  /*39*/ { ADD_0, MCP23x17_portA, BIT_2},
									 /*40*/	{ ADD_0, MCP23x17_portA, BIT_3},  /*41*/ { ADD_0, MCP23x17_portA, BIT_4},  /*42*/ { ADD_0, MCP23x17_portA, BIT_5},
									 /*43*/	{ ADD_0, MCP23x17_portA, BIT_6},  /*44*/ { ADD_0, MCP23x17_portA, BIT_7},  /*45*/ { ADD_0, MCP23x17_portB, BIT_0},
									 /*46*/	{ ADD_0, MCP23x17_portB, BIT_1},  /*47*/ { ADD_0, MCP23x17_portA, BIT_1},  /*48*/ { ADD_0, MCP23x17_portA, BIT_2},
									 /*49*/	{ ADD_0, MCP23x17_portA, BIT_3},  /*50*/ { ADD_0, MCP23x17_portA, BIT_4},  /*51*/ { ADD_0, MCP23x17_portA, BIT_5},
									 /*52*/	{ ADD_0, MCP23x17_portA, BIT_6},  /*53*/ { ADD_0, MCP23x17_portA, BIT_7},  /*54*/ { ADD_0, MCP23x17_portB, BIT_0},
									 /*55*/	{ ADD_0, MCP23x17_portB, BIT_2},  /*56*/ { ADD_0, MCP23x17_portA, BIT_1},  /*57*/ { ADD_0, MCP23x17_portA, BIT_2},
									 /*58*/	{ ADD_0, MCP23x17_portA, BIT_3},  /*59*/ { ADD_0, MCP23x17_portA, BIT_4},  /*60*/ { ADD_0, MCP23x17_portA, BIT_5},
									 /*61*/	{ ADD_0, MCP23x17_portA, BIT_6},  /*62*/ { ADD_0, MCP23x17_portA, BIT_7},  /*63*/ { ADD_0, MCP23x17_portB, BIT_0},
									 /*64*/	{ ADD_0, MCP23x17_portB, BIT_1},  /*65*/ { ADD_0, MCP23x17_portA, BIT_1},  /*66*/ { ADD_0, MCP23x17_portA, BIT_2},
									 /*67*/	{ ADD_0, MCP23x17_portA, BIT_3},  /*68*/ { ADD_0, MCP23x17_portA, BIT_4},  /*69*/ { ADD_0, MCP23x17_portA, BIT_5},
									 /*70*/	{ ADD_0, MCP23x17_portA, BIT_6} };


uint8_t MCP23x17_init(MCP23x17_t *driver);
uint8_t MCP23x17_read(MCP23x17_t *driver, MCP23x17_port_t port, MCP23x17_register_t reg);
uint8_t MCP23x17_read_index(MCP23x17_port_t port, MCP23x17_register_t reg, uint8_t index, MCP_TEMP_POWER_t MCP_TP);
uint8_t MCP23x17_readportA(MCP23x17_t *driver);
uint8_t MCP23x17_readportB(MCP23x17_t *driver);

void MCP23x17_write(MCP23x17_t *driver, MCP23x17_port_t port, MCP23x17_register_t reg, uint8_t value);
void MCP23x17_write_index(MCP23x17_port_t port, MCP23x17_register_t reg, uint8_t value, uint8_t index, MCP_TEMP_POWER_t MCP_TP);
void MCP23x17_writeportA(MCP23x17_t *driver, uint8_t value);
void MCP23x17_writeportB(MCP23x17_t *driver, uint8_t value);

#endif /* _MCP23x17_H_ */
