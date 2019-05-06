/* 
 * File:   adcdrv.h
 * Author: ginst
 *
 * Created on March 21, 2019, 4:02 AM
 */

#ifndef  _ADC_ADS8344_
   #define _ADC_ADS8344_

   #define NUM_ADS8344_CHANNELS  8        // Max # of A/D Channels on an ADS8344 A/D

void select_adc_ads8344 (unsigned char channel_number, short value);
unsigned char get_adc_channel_ads8344(unsigned char channel_number);
void start_read_ads8344 (unsigned char channel_number);
signed long read_channel_ads8344 (unsigned char channel_number);

#endif

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
	//---------------------------------------------------------------------------
	// A/D Functions [ADS8344]
	//---------------------------------------------------------------------------
  // unsigned char get_adc_channel_ads8344(unsigned char channel_number);
   //void start_read_ads8344 (unsigned char channel_number);
   //unsigned int read_channel_ads8344 (unsigned char channel_number);