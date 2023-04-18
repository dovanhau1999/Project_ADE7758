/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>
#define MAX_ID            8
#define MAX_485_USE       20
#define MAX_TEMPER_USE    9
#define MAX_ADE           6

#if MAX_ADE == 3
   #define MAX_DISPLAY_ALARM 14 
#elif MAX_ADE == 6
   #define MAX_DISPLAY_ALARM 19 
#elif MAX_ADE == 9
   #define MAX_DISPLAY_ALARM 22
#endif

#define         ADE_CS1       _LATF0  
#define         ADE_CS2       _LATF1
#define         ADE_CS3       _LATE0
#define         ADE_CS4       _LATB0              //LATBbits.LATB0
#define         ADE_CS5       _LATB1
#define         ADE_CS6       _LATE3
#define         ADE_CS7       _LATE2
#define         ADE_CS8       _LATE1
#define         ADE_CS9       _LATB12
#define         POWER_SIM     _LATD6
#define         exit          _RG2
#define         down          _RG3
#define         up            _RD9
#define         enter         _RC13
#define         ON_ADE        _LATB11
#define         LIGHT_LCD     _LATD7
#define         ONE_WIRE_PIN1 _LATE5   //chan nhiet do 1
#define         ONE_WIRE_PIN2 _LATE6   //chan nhiet do 2
#define         ONE_WIRE_PIN3 _LATE7   //chan nhiet do 3
#define         LCD_DB4       _LATB5
#define         LCD_DB5       _LATB4
#define         LCD_DB6       _LATB3
#define         LCD_DB7       _LATB2
#define         LCD_RS        _LATB13
#define         LCD_RW        _LATF3
#define         LCD_E         _LATD8
#define         LED_WARN      _LATC14
#define         RTC_SDA       _LATD11
#define         RTC_SCL       _LATD10
#define         IN_RTC_SDA    _RD11

#define     ADD_START_CONFIG        0
#define     ADD_PACKET_PERIOD       ADD_START_CONFIG
#define     ADD_LOCAL_IP            ADD_PACKET_PERIOD + 1
#define     ADD_PORT_SERVER         ADD_LOCAL_IP + 4
#define     ADD_PASSWORD_LOGIN      ADD_PORT_SERVER + 4
#define     ADD_ID_DEVICE           ADD_PASSWORD_LOGIN + 8
#define     ADD_MAX_TEMPER          ADD_ID_DEVICE + 10
#define     ADD_MAX_COS_PHI         ADD_MAX_TEMPER + 1
#define     ADD_MIN_COS_PHI         ADD_MAX_COS_PHI + 1
#define     ADD_TIME_COS_PHI        ADD_MIN_COS_PHI + 1
#define     ADD_TI_FACTOR           ADD_TIME_COS_PHI + 1
#define     ADD_SET_TI              ADD_TI_FACTOR + 2
#define     ADD_SET_WARNING         ADD_SET_TI + 28 // 9*3
#define     ADD_SELECT_FUNC         ADD_SET_WARNING + 10
#define     ADD_PHONE               ADD_SELECT_FUNC + 1
#define     ADD_BYTE_ALARM          ADD_PHONE + 12 
#define     ADD_TEMPER              ADD_BYTE_ALARM + 8
#define     ADD_DEBUG_DEVICE        ADD_TEMPER + 216 //27*8byte 27 diem nhiet do
#define     ADD_DOMAIN_NAME         ADD_DEBUG_DEVICE + 10
#define     ADD_DOMAIN_LENGTH       ADD_DOMAIN_NAME + 50

#define     ADD_START_MEASURE       1000
#define     ADD_KU                  ADD_START_MEASURE
#define     ADD_KI                  ADD_KU + 54       //9*2*2byte Ku[0] Ku[1] ... Ki[26]
#define     ADD_KP                  ADD_KI + 54       //9*3*2byte Ki[0] Ki[1] ... Ki[26]
#define     ADD_KQ                  ADD_KP + 54       //9*3*2byte Kp[0] Kp[1] ... Kp[26]
#define     ADD_THRESS_P            ADD_KQ + 54       //9*3*2byte Kq[0] Kq[1] ... Kq[26]
#define     ADD_THRESS_Q            ADD_THRESS_P + 108 //9*3*4byte Thress 9*3 Nhanh
#define     ADD_CUMULATIVE_P        ADD_THRESS_Q + 108 //9*3*4byte Thress 9*3 Nhanh
#define     ADD_CUMULATIVE_Q        ADD_CUMULATIVE_P + 36 //4byte*9=36byte Ptichluy 9 nhanh 
// TODO Insert C++ class definitions if appropriate
// TODO Insert declarations
typedef enum
{
    ENTER = 0,
    UP,
    DOWN,
    EXIT
}button_type;

void Init_ADE_Run(void);
void ADE_test(uint8_t Num);
//extern void Init_Buttons(void);
//extern void Test(void);
// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

