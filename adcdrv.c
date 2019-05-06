#include "adcdrv.h"
#include <xc.h>
#include <p33FJ128MC802.h>
#include "peripherals.h"
#include <stdio.h>
#include <SPI.h>
#define HIGH 1
#define LOW 0
#define  SAMP_BUFF_SIZE	 		8		// Size of the input buffer per analog input
#define  NUM_CHS2SCAN			4		// Number of channels enabled for channel scan
 
//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Routine:		select_adc_ads8344
//	Inputs:		channel #
//	Outputs:		none
//	Purpose:		Selects A/D (just one option for this so other cases in base code removed)
//-----------------------------------------------------------------------------
void select_adc_ads8344 (unsigned char channel_number, short value)
{
																						//-----------------------------------------
                                                                         // Since the A/D reads 8 channels we just need to 
         channel_number >>= 3;                                          // shift to the right 3 bits to get the bank # of the A/D
																						//-----------------------------------------
         AD1CON3bits.ADCS0 = LOW;   
      
        // break;                                                   //change to just set one ADC chanel
                                                             
  
       																			//-----------------------------------------

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
   unsigned int code; //changed to int

   																						//-----------------------------------------
   channel_number = get_adc_channel_ads8344(channel_number);         // Get A/D Channel
   code = channel_number & 0x07;                                     // Build the data value
   code <<= 4;                                                       //
   code |= 0x86;                                                     //
   code = ~code;                                                     //
   //RPINR20 is the SPI data input and clock input register for the dspic33
   //RPINR21 is the SPI slave select input
   
   select_adc_ads8344(channel_number, LOW);  //LOW changed to 0          // Select A/D
  // WriteSPI1(code);    // SpiChnPutC(2, code);                  // Send Data
   //putsSPI1(2, &code);
   //getsSPI1(2, &code, 2);
   WriteSPI1(code);
   ReadSPI1();
 //  ReadSPI1(code);                      //SpiChnGetC(2);                        // Get the received data
  select_adc_ads8344(channel_number, HIGH);                               // Deselect A/D
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
	signed long adcData = 0x00000000; //write put 0xFF , read for get 
    unsigned int code2 = 0xFF;
                                                                    //-----------------------------------------
   channel_number = get_adc_channel_ads8344(channel_number);         // Get A/D Channel
   select_adc_ads8344(channel_number, 0);                          // Select A/D, LOW changed to 0
   WriteSPI1(code2);                                           // Send Data
   adcData = ReadSPI1();                                           // Get the received data
   adcData <<= 8;                                                    // Shift by 8 bits
   WriteSPI1(code2);                                              // Send Data
   adcData |=ReadSPI1();                                          // Get the received data
   adcData <<= 8;                                                    // Shift by 8 bits
   WriteSPI1(code2);                                              // Send Data
   adcData |=ReadSPI1();                                          // Get the received data
   select_adc_ads8344(channel_number, HIGH);                         // Deselect A/D
																							//-----------------------------------------

   adcData &= 0x7FFFFF;
   adcData >>= 7;
   adcData -= 32768;

   return adcData;
}
