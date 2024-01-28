#ifndef _SYS_H
#define _SYS_H
#include "stm32f7xx.h"
#include "core_cm7.h"
#include "stm32f7xx_hal.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F7������
//ϵͳʱ�ӳ�ʼ��	
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/6/10
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//�޸�˵��
//��
//////////////////////////////////////////////////////////////////////////////////  

//0,��֧��os
//1,֧��os
#define SYSTEM_SUPPORT_OS		0		//����ϵͳ�ļ����Ƿ�֧��OS	
///////////////////////////////////////////////////////////////////////////////////
//����һЩ���õ��������Ͷ̹ؼ��� 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  

// ?? GPIO ???????
#define GPIOB_ODR (*((volatile unsigned int *)0x40020414))  // GPIOB Output Data Register
#define GPIOB_IDR (*((volatile unsigned int *)0x40020410))  // GPIOB Input Data Register

// ?? BIT_ADDR ?
#define BIT_ADDR(reg, bit) ((reg) | (1 << (bit)))

// ???? PBout ? PBin ?
#define PBout(n) BIT_ADDR(GPIOB_ODR, n)
#define PBin(n)  BIT_ADDR(GPIOB_IDR, n)

#define ON	1
#define OFF	0
#define Write_Through() (*(__IO uint32_t*)0XE000EF9C=1UL<<2) //Cache͸дģʽ

//GPIO����ר�ú궨��
#define GPIO_MODE_IN    	0		//��ͨ����ģʽ
#define GPIO_MODE_OUT		1		//��ͨ���ģʽ
#define GPIO_MODE_AF		2		//AF����ģʽ
#define GPIO_MODE_AIN		3		//ģ������ģʽ

#define GPIO_SPEED_2M		0		//GPIO�ٶ�2Mhz(����)
#define GPIO_SPEED_25M		1		//GPIO�ٶ�25Mhz(����)
#define GPIO_SPEED_50M		2		//GPIO�ٶ�50Mhz(����)
#define GPIO_SPEED_100M		3		//GPIO�ٶ�100Mhz(����)

#define GPIO_PUPD_NONE		0		//����������
#define GPIO_PUPD_PU		1		//����
#define GPIO_PUPD_PD		2		//����
#define GPIO_PUPD_RES		3		//���� 

#define GPIO_OTYPE_PP		0		//�������
#define GPIO_OTYPE_OD		1		//��©��� 

//GPIO���ű�Ŷ���
#define PIN0				1<<0
#define PIN1				1<<1
#define PIN2				1<<2
#define PIN3				1<<3
#define PIN4				1<<4
#define PIN5				1<<5
#define PIN6				1<<6
#define PIN7				1<<7
#define PIN8				1<<8
#define PIN9				1<<9
#define PIN10				1<<10
#define PIN11				1<<11
#define PIN12				1<<12
#define PIN13				1<<13
#define PIN14				1<<14
#define PIN15				1<<15 



void Cache_Enable(void);                                    //ʹ��STM32F7��L1-Cahce
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq); //����ϵͳʱ��
u8 Get_ICahceSta(void);//�ж�I_Cache�Ƿ��
u8 Get_DCahceSta(void);//�ж�I_Dache�Ƿ��
//����Ϊ��ຯ��
void WFI_SET(void);		//ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(u32 addr);	//���ö�ջ��ַ 
#endif

