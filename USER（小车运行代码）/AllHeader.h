/**
* @par Copyright (C): 2016-2026, Shenzhen Yahboom Tech
* @file         // ALLHeader.h
* @author       // lly
* @version      // V1.0
* @date         // 230228
* @brief        // 相关所有的头文件
* @details      
* @par History  //
*               
*/


#ifndef __AllHeader_H
#define __AllHeader_H

#define DEBUG_USARTx USART1


/*
C8T6:
STM:20036410
GD: 13030410

RCT6:
APM:000A0414
STM:10036414
*/


//功能开关  1:打开 0:关闭
#define LCD_SWITCH    	0
#define IMU_SWITCH 			0 
#define FLASH_SWITCH  	0 
#define RGB_SWITCH			0

#define MOTOR_SWITCH  	1

#define k210_AI_SWITCH  1

//从1开始
enum k210_msg 
{
	red_light = 1,
	green_light,
	school,
	walk,
	one,
	right,
	two,
	freeSpeed,
	left,
	limitSpeed,
	horn,
	chuku_track_line,
	MAX_id
};


#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "stdint.h"
#include "stm32f10x.h"

#include "bsp.h"
#include "bsp_common.h"
#include "delay.h"

#include "bsp_key.h"
#include "bsp_timer.h"

#include "bsp_icm20607.h"
#include "IOI2C.h"

#include "lcd.h"
#include "lcd_init.h"

#include "bsp_spi.h"
#include "bsp_w25q64.h"

#include "bsp_RGB.h"
#include "bsp_usart.h"

#include "bsp_encoder.h"
#include "bsp_motor.h"
#include "app_motion.h"
#include "bsp_pid.h"
#include "app_mecanum.h"
#include "app_math.h"

#include "bsp_timer.h"

#include "tbdetails.h"
#include "k210_AI_deal.h"



//APP文件下的函数
/********外部flash相关*********/
u8 detcet_flash(void);
void flash_test(void);
void show_flash(void);

/**********IMU相关************/
void imu_test(void);


extern u8 stop_flag; //0:小车并未停止 1:碰到停止线，等待接收k210信息
extern u32 n_stime ;
extern u16 wait_k210;//等待k210启动的时间
extern u32 dao_time;
extern u8 bound_num;

extern unsigned char ICM_ADDRESS; //IMU



#endif


