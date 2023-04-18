#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Config.h"
//#include "eepromI2C.h"
#include "mcc_generated_files/mcc.h"
#include "delay.h"
//#include "LCDD.h"
//#include "mcc_generated_files/ext_int.h"

#define Display_VoltCurr  0
//#define Display_Voltage   1
//#define Display_Currrent  2
#define Display_Power     3
#define Display_RPower    4
//#define Tempt_Ti1         120 // he so ban thu o goc tuong// 
#define Tempt_Ti1         80
//#define Tempt_Ti2         80 // he so ban thu gan cua ra vao//
//#define Tempt_Ti3         160
#define Utest             220
#define Itest             400
#define Ptest             44000
#define Pthress           68000
#define Ptl               40000
#define Qtest             44000
#define Qthress           56000
#define Qtl               40000

#define Awatt             0x01   //  2 byte
#define Bwatt             0x02   //  2 byte
#define Cwatt             0x03   //  2 byte
#define Avar              0x04   //  2 byte
#define Bvar              0x05   //  2 byte
#define Cvar              0x06   //  2 byte
#define Ava               0x07   //  2 byte
#define Bva               0x08   //  2 byte
#define Cva               0x09   //  2 byte
#define Ia                0x0A   //  3 byte
#define Ib                0x0B   //  3 byte
#define Ic                0x0C   //  3 byte
#define Va                0x0D   //  3 byte
#define Vb                0x0E   //  3 byte
#define Vc                0x0F   //  3 byte
#define Freq              0x10   // 
#define Temps             0x11   // 
#define Wform             0x12   // 
#define Opmode            0x13   // 
#define Mmode             0x14   // 
#define Wavmode           0x15   // 
#define Compmode          0x16   // 
#define Lcycmode          0x17   // 
#define Mask              0x18   // 
#define Status            0x19   // 
#define Rstatus           0x1A   // 
#define Zxtout            0x1B   // 
#define Linecyc           0x1C   // 
#define Sagcyc            0x1D   // 
#define Saglvl            0x1E   // 
#define Vpintlvl          0x1F   // 
#define Ipintlvl          0x20   // 
#define Vpeak             0x21   // 
#define Ipeak             0x22   // 
#define Gain              0x23   // 
#define Vagain            0x24   // 
#define Vbgain            0x25   // 
#define Vcgain            0x26   // 
#define Iagain            0x27   // 
#define Ibgain            0x28   // 
#define Icgain            0x29   // 
#define Wagain            0x2A   // 
#define Wbgain            0x2B   // 
#define Wcgain            0x2C   // 
#define VARagain          0x2D   // 
#define VARbgain          0x2E   // 
#define VARcgain          0x2F   // 
#define VAagain           0x30   // 
#define VAbgain           0x31   // 
#define VAcgain           0x32   // 
#define Varmsos           0x33   // 
#define Vbrmsos           0x34   // 
#define Vcrmsos           0x35   // 
#define Iarmsos           0x36   // 
#define Ibrmsos           0x37   // 
#define Icrmsos           0x38   // 
#define Waos              0x39   // 
#define Wbos              0x3A   // 
#define Wcos              0x3B   // 
#define VARaos            0x3C   // 
#define VARbos            0x3D   // 
#define VARcos            0x3E   // 
#define Aphcal            0x3F
#define Bphcal            0x40
#define Cphcal            0x41


static void ADE_Write(uint8_t ADE_Select, int32_t value, uint8_t address, uint8_t length);
static int32_t ADE_Read(uint8_t ADE_Select, uint8_t address, uint8_t length);
static int32_t Make32(uint8_t data);
static int32_t Make322(uint8_t data,uint8_t data1);
static int32_t Make323(uint8_t data,uint8_t data1,uint8_t data2);
static int8_t make8(uint32_t value, uint8_t c);


void Init_ADE_Run(void) {
    uint8_t i = 0;
    ADE_Write(0,0x05, Sagcyc,1);
    ADE_Write(0,0x30,Saglvl,1);
    ADE_Write(0,0x1C0,Mask,3);
    ADE_Write(0,0x00,Opmode,1);
    ADE_Write(0,0x40,Lcycmode,1);
    ADE_Write(0,0x9C,Compmode,1); 
    ADE_Write(0,0x00, Mmode,1);

    ADE_Write(0,-8,Varmsos,2);
    ADE_Write(0,-44,Vbrmsos,2);
    ADE_Write(0,-268,Vbrmsos,2);
    ADE_Write(0,25,Iarmsos,2);
    ADE_Write(0,25,Ibrmsos,2);
    ADE_Write(0,25,Icrmsos,2);
    ADE_Write(0,4,Wagain,2);
    ADE_Write(0,4,Wbgain,2);
    ADE_Write(0,4,Wcgain,2);
    ADE_Write(0,4,VAagain,2);
    ADE_Write(0,4,VAbgain,2);
    ADE_Write(0,4,VAcgain,2);
    ADE_Write(0,0,VARagain,2);
    ADE_Write(0,0,VARbgain,2);
    ADE_Write(0,0,VARcgain,2);
    ADE_Write(0,-10,Aphcal,2);
    ADE_Write(0,-10,Bphcal,2);
    ADE_Write(0,-10,Cphcal,2);
    ADE_Write(0,82,Waos,2);
    ADE_Write(0,82,Wbos,2);
    ADE_Write(0,82,Wcos,2);
    ADE_Write(0,-1590,VARaos,2);
    ADE_Write(0,-1590,VARbos,2);
    ADE_Write(0,-1590,VARcos,2);
    
    for (i = 1; i < MAX_ADE; i++) {
      __delay_ms(100);
      ADE_Write(i,0x05, Sagcyc,1);
      ADE_Write(i,0x30,Saglvl,1);
      ADE_Write(i,0x1C0,Mask,3);
      ADE_Write(i,0x00,Opmode,1);
      ADE_Write(i,0x40,Lcycmode,1);
      ADE_Write(i,0x9C,Compmode,1); 
      ADE_Write(i,0x00, Mmode,1);
      
      ADE_Write(i,65521,Varmsos,2);
      ADE_Write(i,65521,Vbrmsos,2);
      ADE_Write(i,65521,Vbrmsos,2);
      ADE_Write(i,249,Iarmsos,2);
      ADE_Write(i,249,Ibrmsos,2);
      ADE_Write(i,249,Icrmsos,2);
      ADE_Write(i,39,Wagain,2);
      ADE_Write(i,39,Wbgain,2);
      ADE_Write(i,39,Wcgain,2);
      ADE_Write(i,38,VAagain,2);
      ADE_Write(i,38,VAbgain,2);
      ADE_Write(i,38,VAcgain,2);
      ADE_Write(i,39,VARagain,2);
      ADE_Write(i,39,VARbgain,2);
      ADE_Write(i,39,VARcgain,2);
      ADE_Write(i,157,Waos,2);
      ADE_Write(i,157,Wbos,2);
      ADE_Write(i,157,Wcos,2);
      ADE_Write(i,473,VARaos,2);
      ADE_Write(i,473,VARbos,2);
      ADE_Write(i,473,VARcos,2);
    }
}

static int32_t Make32(uint8_t data){
    int32_t result=0;
    result=data;
    return (result);
}

static int32_t Make322(uint8_t data,uint8_t data1){
    int32_t result=0;
    result=data;
    result = result<<8;
    result = result| data1;
    return (result);
}

static int32_t Make323(uint8_t data,uint8_t data1,uint8_t data2){
    int32_t result=0;   
    result=data;
    result = result<<8 | data1;
    result = result<<8 | data2;
    return (result);
}

static int8_t make8(uint32_t value, uint8_t c){
    int8_t result=0;
    c=c*8;
    result = ((value >> c) & 0xFF);
    return result;
}
//-------------------------------------------------------------------------------------------------------//
static void ADE_Write(uint8_t ADE_Select, int32_t value, uint8_t address, uint8_t length){
    uint8_t response=0;
    switch(ADE_Select){
        case 1:{
            ADE_CS1=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }
        case 2:{
            ADE_CS2=0;
            ADE_CS1=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;

            break;
        }
        case 3:{
            ADE_CS3=0;
            ADE_CS2=1;
            ADE_CS1=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;

            break;
        }
        case 4:{
            ADE_CS4=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS1=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }   
        case 5:{
            ADE_CS5=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS1=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }
        case 6:{
            ADE_CS6=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS1=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }
        case 7:{
            ADE_CS7=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS1=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }
        case 8:{
            ADE_CS8=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS1=1;
            ADE_CS9=1;
            break;
        }
        case 9:{
            ADE_CS9=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS1=1;
            break;
        }   
    } 
    address=address|0x80;
    response = SPI2_Exchange8bit(address);
    Delay10us(20);
    
    switch(length){
        case 1: {
            response = SPI2_Exchange8bit(make8(value,0)); // truy?n ?i byte 0 trong value//
            break;
        }
        case 2: {
            response = SPI2_Exchange8bit(make8(value,1)); // truy?n ?i byte 1 trong value//
            Delay10us(20);
            response = SPI2_Exchange8bit(make8(value,0));
            break;
        }
        case 3: {
            response = SPI2_Exchange8bit(make8(value,2));
            Delay10us(20);
            response = SPI2_Exchange8bit(make8(value,1));
            Delay10us(20);
            response = SPI2_Exchange8bit(make8(value,0));
            break;
        }
    }
    ADE_CS1=1; ADE_CS2=1; ADE_CS3=1; ADE_CS4=1; ADE_CS5=1; ADE_CS6=1; ADE_CS7=1; ADE_CS8=1; ADE_CS9=1;
    DelayMs(1);
}

static int32_t ADE_Read(uint8_t ADE_Select, uint8_t address, uint8_t length){
    int32_t result=0;
    uint8_t temp,result_0=0,result_1=0,result_2=0;
    switch(ADE_Select){
        case 1:{
            ADE_CS1=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }
        case 2:{
            ADE_CS2=0;
            ADE_CS1=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;

            break;
        }
        case 3:{
            ADE_CS3=0;
            ADE_CS2=1;
            ADE_CS1=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;

            break;
        }
        case 4:{
            ADE_CS4=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS1=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }   
        case 5:{
            ADE_CS5=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS1=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }
        case 6:{
            ADE_CS6=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS1=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }
        case 7:{
            ADE_CS7=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS1=1;
            ADE_CS8=1;
            ADE_CS9=1;
            break;
        }
        case 8:{
            ADE_CS8=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS1=1;
            ADE_CS9=1;
            break;
        }
        case 9:{
            ADE_CS9=0;
            ADE_CS2=1;
            ADE_CS3=1;
            ADE_CS4=1;
            ADE_CS5=1;
            ADE_CS6=1;
            ADE_CS7=1;
            ADE_CS8=1;
            ADE_CS1=1;
            break;
        }             
    }
    address=address&0x7F;
    temp = SPI2_Exchange8bit(address);
    Delay10us(5);
    
    switch (length){
        case 1:{
            result_0 = SPI2_Exchange8bit(0);
            result = Make32(result_0);
            break;
        }   
        case 2:{
            result_0 = SPI2_Exchange8bit(0);
            Delay10us(5);
            result_1=SPI2_Exchange8bit(0);
            result = Make322(result_0,result_1);
            break;
        }  
        case 3:{
            result_0 = SPI2_Exchange8bit(0);
            Delay10us(5);
            result_1=SPI2_Exchange8bit(0);
            Delay10us(5);
            result_2=SPI2_Exchange8bit(0);
            result = Make323(result_0,result_1,result_2);
            break;
        }         
    }
    ADE_CS1=1; ADE_CS2=1; ADE_CS3=1; ADE_CS4=1; ADE_CS5=1; ADE_CS6=1; ADE_CS7=1; ADE_CS8=1; ADE_CS9=1;
    Delay10us(5);
    return result;
}



void ADE_test(uint8_t Num)
{
    uint8_t index;
    int32_t CurrValue[3], VoltValue[3], PowerValue[3], ReActiveValue[3];
    uint64_t ValueCos[3];
    switch (Num)
    {
        case 1:
        {
            for (index =0; index < 3; index++ )
            {
                CurrValue[index] = ADE_Read(6, Ia + index, 3);
                printf("Gia tri dong dien pha %d la: %li \n\r", (index + 1), CurrValue[index]);
            }
            break;
        }
        case 2:
        {
            for ( index =0; index < 3; index++ )
            {
                VoltValue[index] = ADE_Read(6, Va + index, 3);
                printf("Gia tri dien ap pha %d la: %li \n\r", (index + 1), VoltValue[index]);
            }
            break;
        }
        case 3:
        {
            int16_t ValueTest;
            for ( index =0; index < 3; index++ )
            {
                ValueTest = (int16_t)ADE_Read(6, Awatt + index, 2);
                PowerValue[index] = (int32_t) ValueTest;
                printf("Gia tri cong suat pha %d la: %li \n\r", (index + 1), PowerValue[index]);
            }
            
            for ( index =0; index < 3; index++ )
            {
                ValueTest = (int16_t)ADE_Read(6, Avar + index, 2);
                ReActiveValue[index] = (int32_t) ValueTest;
                printf("Gia tri cong suat phan khang pha %d la: %li \n\r", (index + 1), ReActiveValue[index]);
            }
            
            for ( index =0; index < 3; index++ )
            {
                ValueCos[index] = (uint64_t) sqrt(pow(PowerValue[index],2) + pow(ReActiveValue[index], 2));
                printf("Gia tri Cos Phi pha %d la: %li \n\r", (index + 1), ValueCos[index]);
            }
            
            break;
        }
                
    }

}

