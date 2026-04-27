#include "stm32f10x.h"                 // Device header
#include "Delay.h" 
#include "OLED.h"
#include "Key.h"
#include "Led.h"
#include "Timer.h"
#include "MPU6050.h"


/*OLED和LED测试*/
//int main(void){
//    OLED_Init();
//	LED_Init();
//	
//	OLED_Printf(0,0,OLED_8X16,"Hello,World!");
//	OLED_Printf(0,16,OLED_6X8,"Hello,World!");
//	OLED_Update();

//	 while(1)
//	{
//		LED_ON();
//		Delay_ms(500);
//		LED_OFF();
//		Delay_ms(500);
//		LED_Turn();
//		Delay_ms(500);
//		LED_Turn();
//		Delay_ms(500);
//	
//	}
//}
/*定时中断和非阻塞式按键测试程序*/
//uint16_t Count;
//uint8_t KeyNum,Num;
//int main(void)
//{
//	OLED_Init();
//	Key_Init();
//	Timer_Init();
//	
//	while(1)
//	{
//		KeyNum=Key_GetNum();
//		if(KeyNum==1)
//		{
//			Num++;
//		}
//		if(KeyNum==2)
//		{
//			Num--;
//		}
//		if(KeyNum==3)
//		{
//			Num+=10;
//		}
//		if(KeyNum==4)
//		{
//			Num-=10;
//		}
//		OLED_Printf(0,0,OLED_8X16,"Count:%05d",Count);
//		OLED_Printf(0,16,OLED_8X16,"Num:%03d",Num);
//		OLED_Update();
//	}
//}
//void TIM1_UP_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
//	{
//		Count++;
//		
//		Key_Tick();
//		
//		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
//	}
//}
/*MPU6050测试*/
int16_t AX,AY,AZ,GX,GY,GZ;
uint16_t TimerErrorFlag;
uint16_t TimerCount;
int main(void)
{
	OLED_Init();
	MPU6050_Init();
	Timer_Init();
	
	while(1)
	{
//		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);//目前读取太慢需要放到定时中断里否则会严重阻塞主循环的执行
		
		OLED_Printf(0,0,OLED_8X16,"%+06d",AX);
		OLED_Printf(0,16,OLED_8X16,"%+06d",AY);
		OLED_Printf(0,32,OLED_8X16,"%+06d",AZ);
		OLED_Printf(64,0,OLED_8X16,"%+06d",GX);
		OLED_Printf(64,16,OLED_8X16,"%+06d",GY);
		OLED_Printf(64,32,OLED_8X16,"%+06d",GZ);
		OLED_Printf(0,48,OLED_8X16,"Flag:%1d",TimerErrorFlag);	
		OLED_Printf(64,48,OLED_8X16,"c:%05d",TimerCount);	
		OLED_Update();
	}
}

void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
	{
		TimerErrorFlag=0;
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		
		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ); 
		
		if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
		{
			TimerErrorFlag=1;
			TIM_ClearITPendingBit(TIM1,TIM_IT_Update);			
		}
		TimerCount=TIM_GetCounter(TIM1);
	}
}
