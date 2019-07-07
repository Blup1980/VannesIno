#ifndef CUSTOM_PDO_NAME_H
#define CUSTOM_PDO_NAME_H

//-------------------------------------------------------------------//
//                                                                   //
//     This file has been created by the Easy Configurator tool      //
//                                                                   //
//     Easy Configurator project EtherCarConfigurator.prj
//                                                                   //
//-------------------------------------------------------------------//


#define CUST_BYTE_NUM_OUT	1
#define CUST_BYTE_NUM_IN	11
#define TOT_BYTE_NUM_ROUND_OUT	4
#define TOT_BYTE_NUM_ROUND_IN	12


typedef union												//---- output buffer ----
{
	uint8_t  Byte [TOT_BYTE_NUM_ROUND_OUT];
	struct
	{
		uint8_t     PWM;
	}Cust;
} PROCBUFFER_OUT;


typedef union												//---- input buffer ----
{
	uint8_t  Byte [TOT_BYTE_NUM_ROUND_IN];
	struct
	{
		uint8_t     SW0;
		uint8_t     SW1;
		uint8_t     SW2;
		uint8_t     SW3;
		uint8_t     SW4;
		uint8_t     SW5;
		uint8_t     SW6;
		uint8_t     SW7;
		uint8_t     SW8;
		uint8_t     SW9;
		uint8_t     SW10;
	}Cust;
} PROCBUFFER_IN;

#endif