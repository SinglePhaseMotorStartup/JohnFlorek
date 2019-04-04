/*#include "adcdrv.h"
#include <xc.h>
*/
//#define  SAMP_BUFF_SIZE	 		8		// Size of the input buffer per analog input
//#define  NUM_CHS2SCAN			4		// Number of channels enabled for channel scan

/*=============================================================================
ADC INITIALIZATION FOR CHANNEL SCAN
=============================================================================*/
/*void initadc1(void)
{

		AD1CON1bits.FORM   = 3;		// Data Output Format: Signed Fraction (Q15 format)
		AD1CON1bits.SSRC   = 2;		// Sample Clock Source: GP Timer starts conversion
		AD1CON1bits.ASAM   = 1;		// ADC Sample Control: Sampling begins immediately after conversion
		AD1CON1bits.AD12B  = 0;		// 10-bit ADC operation

		AD1CON2bits.CSCNA = 1;		// Scan Input Selections for CH0+ during Sample A bit
		AD1CON2bits.CHPS  = 0;		// Converts CH0

		AD1CON3bits.ADRC = 0;		// ADC Clock is derived from Systems Clock
		AD1CON3bits.ADCS = 63;		// ADC Conversion Clock Tad=Tcy*(ADCS+1)= (1/40M)*64 = 1.6us (625Khz)
									// ADC Conversion Time for 10-bit Tc=12*Tab = 19.2us

		AD1CON2bits.SMPI    = (NUM_CHS2SCAN-1);	// 4 ADC Channel is scanned

}*/
//------------------------------------------------------------------------------
// A/D Functions [ADS8344]
//
// File Name: 		ADC (ADS8344).c
// Version:			1.0.0
// Date:				April 2, 2019
//	Description:	A/D Functions [ADS8344]
//
//------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//------------------------------------------------------------------------------
                         
//------------------------------------------------------------------------------
//	Project Header Files
//------------------------------------------------------------------------------
/*#include <p33FJ128MC802.h>                                               // Header file for the PIC33 MCU
#include "peripherals.h"                                                    // Header file for Peripheral Library Header File
#include <stdio.h>                                                   // Header file for Standard I/O Header File

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Routine:		select_adc_ads8344
//	Inputs:		channel #
//	Outputs:		none
//	Purpose:		Selects A/D based upon channel number
//-----------------------------------------------------------------------------
void select_adc_ads8344 (unsigned char channel_number, short value)
{
																						//-----------------------------------------
                                                                  // Since the A/D reads 8 channels we just need to 
   channel_number >>= 3;                                          // shift to the right 3 bits to get the bank # of the A/D
																						//-----------------------------------------

																						//-----------------------------------------
   switch (channel_number)                                        // Select the correct A/D based upon the bank #
   {                                                              //
      case 0x00:                                                  // Bank #0
         ADC_CS0 = value;                                         // Set CS to value
         break;                                                   //
                                                                  //
      case 0x01:                                                  // Bank #1
         ADC_CS1 = value;                                         // Set CS to value
         break;                                                   //
                                                                  //
      case 0x02:                                                  // Bank #2
         ADC_CS2 = value;                                         // Set CS to value
         break;                                                   //
                                                                  //
      case 0x03:                                                  // Bank #3
         ADC_CS3 = value;                                         // Set CS to value
         break;                                                   //
                                                                  //
      default:                                                    // do nothing...invalid bank #
         break;                                                   //
   }     																			//-----------------------------------------

}

//-----------------------------------------------------------------------------
// Routine:		get_adc_channel
//	Inputs:		channel #
//	Outputs:		ADC channel #
//	Purpose:		Converts channel number into actual A/D channel number
//-----------------------------------------------------------------------------
unsigned char get_adc_channel_ads8344(unsigned char channel_number)
{
																							//-----------------------------------------
   unsigned char adc_channel = channel_number & 0xF8;                // Keep the upper 5 bits of the channel (i.e. A/D Bank)
																							//-----------------------------------------

																							//-----------------------------------------
   switch (channel_number & 0x07)                                    // Switch on the A/D sub channel
   {                                                                 //
      case 0x00:                                                     // 0x00 = 0x00
         break;                                                      //
      case 0x01:                                                     // 0x01 = 0x04
         adc_channel |= 0x04;                                        //
         break;                                                      //
      case 0x02:                                                     // 0x02 = 0x01
         adc_channel |= 0x01;                                        //
         break;                                                      //
      case 0x03:                                                     // 0x03 = 0x05
         adc_channel |= 0x05;                                        //
         break;                                                      //
      case 0x04:                                                     // 0x04 = 0x02
         adc_channel |= 0x02;                                        //
         break;                                                      //
      case 0x05:                                                     // 0x05 = 0x06
         adc_channel |= 0x06;                                        //
         break;                                                      //
      case 0x06:                                                     // 0x06 = 0x03
         adc_channel |= 0x03;                                        //
         break;                                                      //
      case 0x07:                                                     // 0x07 = 0x07
         adc_channel |= 0x07;                                        //
         break;                                                      //
   }                                                                 //
																							//-----------------------------------------
   
																							//-----------------------------------------
   return adc_channel;                                               // Return the A/D channel
																							//-----------------------------------------
}

//-----------------------------------------------------------------------------
// Routine:		read_channel_ads8344
//	Inputs:		channel #
//	Outputs:		none
//	Purpose:		Read the channel for the ADS8344
//-----------------------------------------------------------------------------
void start_read_ads8344 (unsigned char channel_number)
{
   unsigned char code;

   																						//-----------------------------------------
   channel_number = get_adc_channel_ads8344(channel_number);         // Get A/D Channel
   code = channel_number & 0x07;                                     // Build the data value
   code <<= 4;                                                       //
   code |= 0x86;                                                     //
   code = ~code;                                                     //
   select_adc_ads8344(channel_number, LOW);                          // Select A/D
   SpiChnPutC(2, code);                                              // Send Data
   SpiChnGetC(2);                                                    // Get the received data
   select_adc_ads8344(channel_number, HIGH);                         // Deselect A/D
																							//-----------------------------------------

}

//-----------------------------------------------------------------------------
// Routine:		read_channel_ads8344
//	Inputs:		channel #
//	Outputs:		none
//	Purpose:		Read the channel for the ADS8344
//-----------------------------------------------------------------------------
signed long read_channel_ads8344 (unsigned char channel_number)
{
	signed long adcData = 0x00000000;

   																						//-----------------------------------------
   channel_number = get_adc_channel_ads8344(channel_number);         // Get A/D Channel
   select_adc_ads8344(channel_number, LOW);                          // Select A/D
   SpiChnPutC(2, 0xFF);                                              // Send Data
   adcData =SpiChnGetC(2);                                           // Get the received data
   adcData <<= 8;                                                    // Shift by 8 bits
   SpiChnPutC(2, 0xFF);                                              // Send Data
   adcData |=SpiChnGetC(2);                                          // Get the received data
   adcData <<= 8;                                                    // Shift by 8 bits
   SpiChnPutC(2, 0xFF);                                              // Send Data
   adcData |=SpiChnGetC(2);                                          // Get the received data
   select_adc_ads8344(channel_number, HIGH);                         // Deselect A/D
																							//-----------------------------------------

   adcData &= 0x7FFFFF;
   adcData >>= 7;
   adcData -= 32768;

   return adcData;
}
*/