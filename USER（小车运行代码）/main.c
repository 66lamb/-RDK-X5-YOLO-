/**
* @par Copyright (C): 2016-2026, Shenzhen Yahboom Tech
* @file         // main.c
* @author       // lly
* @version      // V1.0
* @date         // 230228
* @brief        // 程序入口
* @details      
* @par History  // 修改历史记录列表，每条修改记录应包括修改日期、修改者及
*               // 修改内容简述  
*/
#include "AllHeader.h"
#include "pic.h"//图片

u8 stop_flag = 0;  //0:小车并未停止 1:接收k210信息
u32 n_stime = 0;   //恢复正常巡线的时间
u16 wait_k210 = 700;//等待k210启动的时间


#define speed_go 50 //出黑线速度
#define de_time  200  //延迟时间
void Leave_Stop(void)
{
	Motion_Set_Pwm(speed_go,speed_go,speed_go,speed_go);
	delay_ms(de_time);
}

//		Motion_Set_Pwm(50,50,50,50);//右上,右下,左上,左下

int main(void)
{	
	u8 id_num = MAX_id;
	u8 id_num_back = MAX_id;
	
	//硬件初始化
	BSP_init();
	
	//基本定时器初始化
	TIM6_Init();//10MS
	TIM7_Init();//1MS
	
	//设置一个等待k210正常开启的时间
	while(wait_k210);
	
	while(1)
	{
		
#if k210_AI_SWITCH == 1
		
		id_num = get_dataid();//获取最新的id
	
		if(id_num != id_num_back)//状态发生改变
		{
				id_num_back = id_num;
				
				//以下的标志都逃离黑线
				switch(id_num)
				{
					case green_light:
					case school:
					case walk:
					case right:
					case left:
					case freeSpeed:
					case limitSpeed: 
					case horn :
						Leave_Stop();
						Motion_Set_Pwm(50,0,50,0);//处理出黑线检查不到线的状态
						break;
						
					//只做一次
					case one:
							Reverse_parking_no1();//倒1库
					break;
				
					case two:
							Reverse_parking_no2();//倒2库
					break;
					
//					case horn :
//					 Leave_Stop();n_stime = 100;Motion_Set_Pwm(50,0,50,0);//处理出黑线检查不到线的状态
//							Road_sign_speedlimit();//切换低速巡线
//						break;//不处理了
					
					case chuku_track_line: break; //不做任何操作
				
					default:Motion_Set_Pwm(50,0,50,0);//处理出黑线检查不到线的状态
				}
			
		}
		
		switch(id_num_back)
		{
			case red_light: 
				Motion_Set_Pwm(0,0,0,0);//小车停止
				set_dataid(MAX_id);//回到正常巡线
			break;
			
			case green_light:
				set_dataid(MAX_id);//回到正常巡线
			break;
			
			case school:
			case walk:
				set_dataid(MAX_id);//回到正常巡线
				break;
		
			case right:
				Road_sign_right();//右转优先巡线
			break;
			
			case left:
				Road_sign_left();//左转优先巡线
				break;
			
			case freeSpeed:
				set_dataid(MAX_id);//回到正常巡线
				break;
			
			case limitSpeed:
				Road_sign_speedlimit();//低速巡线
			break;
			
			case chuku_track_line://出库后的巡线
					car_outbound_track();
					break;
			
			//不做任何处理
			case one:
			case two:
			case horn:
				break;
			
			default: Track_line();//调用正常巡线函数
		}
		
# else
//		Motion_Set_Pwm(500,500,500,500);
		
		//本工程没有到pid控制，如果想要pid控把定时器6的中断注释的代码开启
		//然后在tbdetails.c的巡线代码把Motion_Set_Pwm这些函数换成Mecanum_State该函数
		//		Mecanum_State(MOTION_RUN,100,0);//用了PID
#endif
		//		Encoder_Update_Count();
		//		Motion_Handle();
		
	}
}


