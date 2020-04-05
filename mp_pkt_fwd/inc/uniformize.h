/*--------------------------------------------------------------------
  This file is part of the mp_pktfwd uniformize EU868<>US915 library.

  This code is free software:
  you can redistribute it and/or modify it under the terms of a Creative
  Commons Attribution-NonCommercial 4.0 International License
  (http://creativecommons.org/licenses/by-nc/4.0/) by
  Remko Welling (http://rfsee.nl) E-mail: remko@rfsee.nl

  The program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  --------------------------------------------------------------------*/

/*!
 * \file uniformize.h
 * \brief Uniformize functions EU868 <> US915 frequencies for the Helium network.
 * \author R. Welling (remko@rfsee.nl)
 * \date See version history
 * \version See version history
 *
 * Version|Date        |Note
 * -------|------------|----
 * 0      | 4-4-2020   | Initial version 
 * 
 */

 /*
# TTN frequency plans
The following documentation is collected from various sources as refrence for the uniformization functions.

Thi sinformation is from: https://www.thethingsnetwork.org/docs/lorawan/frequency-plans.html

## TTN EU863-870

 # |Uplink (MHz)|SFBW                              |Downlink (MHz)|SFBW                              |RX
 --|------------|----------------------------------|--------------|----------------------------------|---
  1|868.1       |SF7BW125 to SF12BW125             |868.1         |SF7BW125 to SF12BW125             | 1
  2|868.3       |SF7BW125 to SF12BW125 and SF7BW250|868.3         |SF7BW125 to SF12BW125 and SF7BW250| 1
  3|868.5       |SF7BW125 to SF12BW125             |868.5         |SF7BW125 to SF12BW125             | 1
  4|867.1       |SF7BW125 to SF12BW125             |867.1         |SF7BW125 to SF12BW125             | 1
  5|867.3       |SF7BW125 to SF12BW125             |867.3         |SF7BW125 to SF12BW125             | 1
  6|867.5       |SF7BW125 to SF12BW125             |867.5         |SF7BW125 to SF12BW125             | 1
  7|867.7       |SF7BW125 to SF12BW125             |867.7         |SF7BW125 to SF12BW125             | 1
  8|867.9       |SF7BW125 to SF12BW125             |867.9         |SF7BW125 to SF12BW125             | 1
  9|868.8       |FSK                               |868.8         |FSK                               | 1
 10|            |                                  |869.525       |SF9BW125 (DR3)                    | 2

## US902-928 used by TTN

Used in USA, Canada and South America

  # |Uplink (MHz) | Uplink SFBW           |# |Downlink (MHz) | Downlink SFBW        |RX
  --|-------------|-----------------------|--|---------------|----------------------|--
   8|903.9        | SF7BW125 to SF10BW125 |1 |923.3          | SF7BW500 to SF12BW500| 1
   9|904.1        | SF7BW125 to SF10BW125 |2 |923.9          | SF7BW500 to SF12BW500| 1
  10|904.3        | SF7BW125 to SF10BW125 |3 |924.5          | SF7BW500 to SF12BW500| 1
  11|904.5        | SF7BW125 to SF10BW125 |4 |925.1          | SF7BW500 to SF12BW500| 1
  12|904.7        | SF7BW125 to SF10BW125 |5 |925.7          | SF7BW500 to SF12BW500| 1
  13|904.9        | SF7BW125 to SF10BW125 |6 |926.3          | SF7BW500 to SF12BW500| 1
  14|905.1        | SF7BW125 to SF10BW125 |7 |926.9          | SF7BW500 to SF12BW500| 1
  15|905.3        | SF7BW125 to SF10BW125 |8 |927.5          | SF7BW500 to SF12BW500| 1
    |904.6        | SF8BW500              |  |               |                      | 1
                                          |  |923.3          | SF12BW500 (DR8)      | 2

# The Helium network frequency plan

https://www.disk91.com/2019/technology/lora/lorawan-in-us915-zone/

The RX1 channel is not the same as TX but determined from the TX channel. The rules applied is RX1 channel = TX channel % 8. As a consequence, if your have consecutive TX channels, all the RX channels will be used. The gateway needs to be able to manage this.
The RX2 channel is fixed : 923.3Mhz / DR8

https://net868.ru/assets/pdf/LoRaWAN-Regional-Parameters-v1.1rA.PDF

/verbatim
2.2.2 US902-928 Channel Frequencies382

The 915MHz ISM Band shall be divided into the following channel plans.
- Upstream –64 channelsnumbered 0 to 63 utilizing LoRa 125kHz BW varying from DR0toDR3, 
  using coding rate 4/5,starting at 902.3 MHz and incrementing linearly by 200 kHz to 914.9MHz
- Upstream –8 channels numbered 64 to 71 utilizing LoRa 500 kHz BW at DR4 starting at 903.0 MHz
  and incrementing linearly by 1.6MHz to 914.2 MHz
- Downstream –8 channels numbered 0 to 7 utilizing LoRa 500kHz BW at DR8 to DR13, starting at 
  923.3 MHz and incrementing linearly by 600 kHz to 927.5 MHz
/verbatimend

## LoRaWAN US915 Uplink Channels (125KHz,4/5,Unit:MHz,CHS=0)

https://developer.helium.com/devices/migrating-devices-to-helium/device-migration-the-things-network#lorawan-us915-uplink-channels-125-khz-4-5-unit-mhz-chs-0

  # | Uplink (MHz)| SFBW                  |# |Downlink (MHz) | Downlink SFBW         |RX
  --|-------------|-----------------------|--|---------------|-----------------------|--
  48| 911.9       | SF7BW125 to SF10BW125 |1 |923.3          | SF7BW500 to SF12BW500 | 1
  49| 912.1       | SF7BW125 to SF10BW125 |2 |923.9          | SF7BW500 to SF12BW500 | 1
  50| 912.3       | SF7BW125 to SF10BW125 |3 |924.5          | SF7BW500 to SF12BW500 | 1
  51| 912.5       | SF7BW125 to SF10BW125 |4 |925.1          | SF7BW500 to SF12BW500 | 1
  52| 912.7       | SF7BW125 to SF10BW125 |5 |925.7          | SF7BW500 to SF12BW500 | 1
  53| 912.9       | SF7BW125 to SF10BW125 |6 |926.3          | SF7BW500 to SF12BW500 | 1
  54| 913.1       | SF7BW125 to SF10BW125 |7 |926.9          | SF7BW500 to SF12BW500 | 1
  55| 913.3       | SF7BW125 to SF10BW125 |8 |927.5          | SF7BW500 to SF12BW500 | 1
    | 912.6       | SF8BW500              |  |               |                       | 1
    |             |                       |  |923.3          | SF12BW500 (DR8)       | 2

# Uniformization table TTN EU868 <> Helium

## Uplink uniformization from EU868 (TTN) to US915 (Helium)

Notes: 
- EU868 Uplink SF7BW125 to SF12BW125 are mapped to their equivalnet counterparts.
- Although US912 does not have SF11BW125 and SF12BW125 these are published to the  Heleium broker
- 868.8 FSK is static mapped to 912.6 SF8BW500. FSK as rarely used in EU
- Uplink RX2-channel is static mapped for both frequency and datarate.

  TTN                                               |Helium
  --------------------------------------------------|---------------------------------------
  # |Uplink (MHz)|SFBW                              |# |Uplink (MHz)| SFBW                  
  --|------------|----------------------------------|--|------------|-----------------------
   1| 868.1      |SF7BW125 to SF12BW125             |48| 911.9      | SF7BW125 to SF10BW125 
   2| 868.3      |SF7BW125 to SF12BW125 and SF7BW250|49| 912.1      | SF7BW125 to SF10BW125 
   3| 868.5      |SF7BW125 to SF12BW125             |50| 912.3      | SF7BW125 to SF10BW125 
   4| 867.1      |SF7BW125 to SF12BW125             |51| 912.5      | SF7BW125 to SF10BW125 
   5| 867.3      |SF7BW125 to SF12BW125             |52| 912.7      | SF7BW125 to SF10BW125 
   6| 867.5      |SF7BW125 to SF12BW125             |53| 912.9      | SF7BW125 to SF10BW125 
   7| 867.7      |SF7BW125 to SF12BW125             |54| 913.1      | SF7BW125 to SF10BW125 
   8| 867.9      |SF7BW125 to SF12BW125             |55| 913.3      | SF7BW125 to SF10BW125 
   9| 868.8      |FSK                               |  | 912.6      | SF8BW500              
    | 869.525    |SF9BW125                          |  | 923.3      | SF12BW500

## Downlink uniformization from US915 (Helium) to EU868 (TTN) 

Notes: 
- Downlink RX1 frequency uniformization is static according to the table below
- SF is unchanged
- BW is altered from 500 kHz to 125 kHz
- Channel 2 datarate SF7BW250 is not mapped because no static relation is availabale
- Downlink RX2 is static mapped for both frequency and datarate. 

  Helium                                       |TTN
  ---------------------------------------------|----------------------------------------------------
  # |Downlink (MHz) | Downlink SFBW         |RX|Downlink (MHz)|SFBW                              |RX
  --|---------------|-----------------------|--|--------------|----------------------------------|--
   1| 923.3         | SF7BW500 to SF12BW500 | 1| 868.1        |SF7BW125 to SF12BW125             | 1
   2| 923.9         | SF7BW500 to SF12BW500 | 1| 868.3        |SF7BW125 to SF12BW125 and SF7BW250| 1
   3| 924.5         | SF7BW500 to SF12BW500 | 1| 868.5        |SF7BW125 to SF12BW125             | 1
   4| 925.1         | SF7BW500 to SF12BW500 | 1| 867.1        |SF7BW125 to SF12BW125             | 1
   5| 925.7         | SF7BW500 to SF12BW500 | 1| 867.3        |SF7BW125 to SF12BW125             | 1
   6| 926.3         | SF7BW500 to SF12BW500 | 1| 867.5        |SF7BW125 to SF12BW125             | 1
   7| 926.9         | SF7BW500 to SF12BW500 | 1| 867.7        |SF7BW125 to SF12BW125             | 1
   8| 927.5         | SF7BW500 to SF12BW500 | 1| 867.9        |SF7BW125 to SF12BW125             | 1
    | 912.6         | SF8BW500              | 1| 868.8        |FSK                               | 1
    | 923.3         | SF12BW500             | 2| 869.525      |SF9BW125                          | 2



*/
#ifndef _UNIFOMIZE_EU_US_H_
#define _UNIFOMIZE_EU_US_H_


#endif /* _UNIFOMIZE_EU_US_H_ */
