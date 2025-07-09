/**
* @par Copyright (C): 2016-2026, Shenzhen Yahboom Tech
* @file         // main.c
* @author       // lly
* @version      // V1.0
* @date         // 230228
* @brief        // �������
* @details      
* @par History  // �޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸��߼�
*               // �޸����ݼ���  
*/
#include "AllHeader.h"
#include "pic.h"//ͼƬ

u8 stop_flag = 0;  //0:С����δֹͣ 1:����k210��Ϣ
u32 n_stime = 0;   //�ָ�����Ѳ�ߵ�ʱ��
u16 wait_k210 = 700;//�ȴ�k210������ʱ��


#define speed_go 50 //�������ٶ�
#define de_time  200  //�ӳ�ʱ��
void Leave_Stop(void)
{
	Motion_Set_Pwm(speed_go,speed_go,speed_go,speed_go);
	delay_ms(de_time);
}

//		Motion_Set_Pwm(50,50,50,50);//����,����,����,����

int main(void)
{	
	u8 id_num = MAX_id;
	u8 id_num_back = MAX_id;
	
	//Ӳ����ʼ��
	BSP_init();
	
	//������ʱ����ʼ��
	TIM6_Init();//10MS
	TIM7_Init();//1MS
	
	//����һ���ȴ�k210����������ʱ��
	while(wait_k210);
	
	while(1)
	{
		
#if k210_AI_SWITCH == 1
		
		id_num = get_dataid();//��ȡ���µ�id
	
		if(id_num != id_num_back)//״̬�����ı�
		{
				id_num_back = id_num;
				
				//���µı�־���������
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
						Motion_Set_Pwm(50,0,50,0);//��������߼�鲻���ߵ�״̬
						break;
						
					//ֻ��һ��
					case one:
							Reverse_parking_no1();//��1��
					break;
				
					case two:
							Reverse_parking_no2();//��2��
					break;
					
//					case horn :
//					 Leave_Stop();n_stime = 100;Motion_Set_Pwm(50,0,50,0);//��������߼�鲻���ߵ�״̬
//							Road_sign_speedlimit();//�л�����Ѳ��
//						break;//��������
					
					case chuku_track_line: break; //�����κβ���
				
					default:Motion_Set_Pwm(50,0,50,0);//��������߼�鲻���ߵ�״̬
				}
			
		}
		
		switch(id_num_back)
		{
			case red_light: 
				Motion_Set_Pwm(0,0,0,0);//С��ֹͣ
				set_dataid(MAX_id);//�ص�����Ѳ��
			break;
			
			case green_light:
				set_dataid(MAX_id);//�ص�����Ѳ��
			break;
			
			case school:
			case walk:
				set_dataid(MAX_id);//�ص�����Ѳ��
				break;
		
			case right:
				Road_sign_right();//��ת����Ѳ��
			break;
			
			case left:
				Road_sign_left();//��ת����Ѳ��
				break;
			
			case freeSpeed:
				set_dataid(MAX_id);//�ص�����Ѳ��
				break;
			
			case limitSpeed:
				Road_sign_speedlimit();//����Ѳ��
			break;
			
			case chuku_track_line://������Ѳ��
					car_outbound_track();
					break;
			
			//�����κδ���
			case one:
			case two:
			case horn:
				break;
			
			default: Track_line();//��������Ѳ�ߺ���
		}
		
# else
//		Motion_Set_Pwm(500,500,500,500);
		
		//������û�е�pid���ƣ������Ҫpid�ذѶ�ʱ��6���ж�ע�͵Ĵ��뿪��
		//Ȼ����tbdetails.c��Ѳ�ߴ����Motion_Set_Pwm��Щ��������Mecanum_State�ú���
		//		Mecanum_State(MOTION_RUN,100,0);//����PID
#endif
		//		Encoder_Update_Count();
		//		Motion_Handle();
		
	}
}


