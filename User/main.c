#include "stm32f10x.h"                 // Device header
#include "Delay.h" 
#include "OLED.h"
#include "Key.h"
#include "Led.h"
#include "Timer.h"
#include "MPU6050.h"
#include "Motor.h"
#include "PWM.h"
#include "Encoder.h"
#include "Serial.h"
#include "BlueSerial.h"
#include <math.h>
#include "PID.h"
#include <string.h>
#include <stdlib.h>


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
///*MPU6050测试*/
//int16_t AX,AY,AZ,GX,GY,GZ;
//uint16_t TimerErrorFlag;
//uint16_t TimerCount;
//float AngleAcc;
//float AngleGyro;
//float Angle;
//int main(void)
//{
//	OLED_Init();
//	MPU6050_Init();
//	Timer_Init();
//	BlueSerial_Init();
//	
//	while(1)
//	{
////		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);//目前读取太慢需要放到定时中断里否则会严重阻塞主循环的执行	

//		OLED_Printf(0,0,OLED_8X16,"%+06d",AX);
//		OLED_Printf(0,16,OLED_8X16,"%+06d",AY);
//		OLED_Printf(0,32,OLED_8X16,"%+06d",AZ);
//		OLED_Printf(64,0,OLED_8X16,"%+06d",GX);
//		OLED_Printf(64,16,OLED_8X16,"%+06d",GY);
//		OLED_Printf(64,32,OLED_8X16,"%+06d",GZ);
//		OLED_Printf(0,48,OLED_8X16,"Flag:%1d",TimerErrorFlag);	
//		OLED_Printf(64,48,OLED_8X16,"c:%05d",TimerCount);	
//		OLED_Update();
//		
//		BlueSerial_Printf("[plot,%f,%f,%f]",AngleAcc,AngleGyro,Angle);
//	}
//}

//void TIM1_UP_IRQHandler(void)//定时中断里的代码的时间不能超过定时中断的时间否则会产生中断重叠
//{
//	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
//	{
//		TimerErrorFlag=0;
//		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
//		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ); 
//		
//		GY-=18;
//		
//		AngleGyro=Angle +GY/32768.9*2000*0.001;
//	
//		AngleAcc=-atan2(AX,AZ)/3.14159*180;
//		
//		float Alpha = 0.001;
//		Angle=Alpha*AngleAcc+(1-Alpha)*AngleGyro;
//		if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
//		{
//			TimerErrorFlag=1;
//			TIM_ClearITPendingBit(TIM1,TIM_IT_Update);			
//		}
//		TimerCount=TIM_GetCounter(TIM1);
//	}
//}
/*直流电机和编码器测试*/
//int16_t PWML,PWMR;
//uint8_t KeyNum;
//float SpeedL,SpeedR;

//int main(void)
//{
//	OLED_Init();
//	Key_Init();
//	Timer_Init();
//	Motor_Init();
//	Encoder_Init();

//	while(1)
//	{ 
//		KeyNum=Key_GetNum();
//		if(KeyNum==1)
//		{
//			PWML+=10;
//			if(PWML>100)PWML=100;
//		}
//		if(KeyNum==2)
//		{
//			PWMR-=10;
//			if(PWMR>100)PWMR=100;
//		}
//		if(KeyNum==3)
//		{
//			PWMR+=10;
//			if(PWMR>100)PWMR=100;

//		}
//		if(KeyNum==4)
//		{
//			PWML-=10;
//			if(PWML<-100)PWML=-100;
//		}
//		Motor_SetPWM(1,PWML);
//		Motor_SetPWM(2,PWMR);		
//		
//		OLED_Clear();
//		OLED_Printf(0,0,OLED_8X16,"PWML:%+04d",PWML);
//		OLED_Printf(0,16,OLED_8X16,"PWMR:%+04d",PWMR);
//		OLED_Printf(0,32,OLED_8X16,"SpdL:%+06.2f",SpeedL);
//		OLED_Printf(0,48,OLED_8X16,"SpdR:%+06.2f",SpeedR);
//		OLED_Update();
//	}
//}
//void TIM1_UP_IRQHandler(void)
//{
//	static uint16_t Count;
//	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
//	{	
//		Key_Tick();
//		if(Count>=50)
//		{
//			Count=0;
//			SpeedL=Encoder_Get(1)/44.0/0.05/9.27666;//44是电机转一圈产生44个脉冲/0.05是每隔50ms读一次值/9.27666是减速比
//			SpeedR=Encoder_Get(2)/44.0/0.05/9.27666;
//		}
//		Count++;
//	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);}
//	}
/*串口和蓝牙串口测试*/
//int main(void)
//{
//	OLED_Init();
//	Serial_Init();
//	BlueSerial_Init();
//	
//	Serial_SendString("Hello");
//	Serial_Printf("World");
//	
//	BlueSerial_SendString("Hello");
//	BlueSerial_Printf("worla");
//	while(1)
//	{
//		if(Serial_GetRxFlag()==1)
//		{
//			uint8_t RxData=Serial_GetRxDate();
//			
//			OLED_Printf(0,0,OLED_8X16,"RxDate:%02X",RxData);
//			OLED_Update();
//		}
//		
//		if(BlueSerial_RxFlag==1)
//		{
//			OLED_Printf(0,16,OLED_8X16,"%s",BlueSerial_RxPacket);
//			OLED_Update();
//			
//			BlueSerial_RxFlag=0;
//		}
//	}
//}
int16_t AX,AY,AZ,GX,GY,GZ;
uint16_t TimerErrorFlag;
uint16_t TimerCount;
float AngleAcc;
float AngleGyro;
float Angle;

float LeftSpeed,RightSpeed;
float AveSpeed,DifSpeed;

PID_t AnglePID=
{
	.Kp=-3.12,
	.Ki=0,
	.Kd=-3.12,
	
	.OutMax=50,
	.OutMin=-50,
};

PID_t SpeedPID=
{
	.Kp=3.3,
	.Ki=0.05,
	.Kd=0,
	
	.OutMax=10,
	.OutMin=-10,
};

PID_t TurnPID=
{
	.Kp=0.5,
	.Ki=0,
	.Kd=0,
	
	.OutMax=100,
	.OutMin=-100,
};
uint8_t KeyNum,RunFlag;
int16_t LeftPWM,RightPWM;
int16_t AvePWM,DifPWM;

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	Timer_Init();
	BlueSerial_Init();
	LED_Init();
	Key_Init();
	Motor_Init();
	Encoder_Init();
	Serial_Init();
	
	while(1)
	{
		if(RunFlag==1){LED_ON();}else{LED_OFF();}
		
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			if(RunFlag==0)
			{
				PID_Init(&AnglePID);
				PID_Init(&SpeedPID);
				RunFlag=1;
			}
			else
			{
				RunFlag=0;
			}
		}
		
		OLED_Clear();
		OLED_Printf(0,0,OLED_6X8,"  Angle");
		OLED_Printf(0,8,OLED_6X8,"P:%05.2f",AnglePID.Kp);
		OLED_Printf(0,16,OLED_6X8,"I:%05.2f",AnglePID.Ki);
		OLED_Printf(0,24,OLED_6X8,"D:%05.2f",AnglePID.Kd);
		OLED_Printf(0,32,OLED_6X8,"T:%05.1f",AnglePID.Target);
		OLED_Printf(0,40,OLED_6X8,"A:%05.1f",Angle);
		OLED_Printf(0,48,OLED_6X8,"O:%05.0f",AnglePID.Out);
		OLED_Printf(50,0,OLED_6X8,"Speed");
		OLED_Printf(50,8,OLED_6X8,"%05.2f",SpeedPID.Kp);
		OLED_Printf(50,16,OLED_6X8,":%05.2f",SpeedPID.Ki);
		OLED_Printf(50,24,OLED_6X8,":%05.2f",SpeedPID.Kd);
		OLED_Printf(50,32,OLED_6X8,":%05.1f",SpeedPID.Target);
		OLED_Printf(50,40,OLED_6X8,":%05.1f",AveSpeed);
		OLED_Printf(50,48,OLED_6X8,":%05.0f",SpeedPID.Out);
		OLED_Printf(0,56,OLED_6X8,":%05d",GY);
		OLED_Update();
		

		
		if (BlueSerial_RxFlag == 1)
	{
	
	char *Tag = strtok(BlueSerial_RxPacket, ",");
	if (strcmp(Tag, "key") == 0)
	{
		char *Name = strtok(NULL, ",");
		char *Action = strtok(NULL, ",");
	}
	else if (strcmp(Tag, "slider") == 0)
	{
		char *Name = strtok(NULL, ",");
		char *Value = strtok(NULL, ",");
		
		if(strcmp(Name,"AngleKp")==0)
		{
			AnglePID.Kp=atof(Value);
		}
		else if(strcmp(Name,"AngleKi")==0)
		{
			AnglePID.Ki=atof(Value);
		}
		else if(strcmp(Name,"AngleKd")==0)
		{
			AnglePID.Kd=atof(Value);
		}else if(strcmp(Name,"SpeedKp")==0)
		{
			SpeedPID.Kp=atof(Value);
		}
		else if(strcmp(Name,"SpeedKi")==0)
		{
			SpeedPID.Ki=atof(Value);
		}
		else if(strcmp(Name,"SpeedKd")==0)
		{
			SpeedPID.Kd=atof(Value);
		}
		else if(strcmp(Name,"TurnKp")==0)
		{
			TurnPID.Kp=atof(Value);
		}
		else if(strcmp(Name,"TurnKi")==0)
		{
			TurnPID.Ki=atof(Value);
		}
		else if(strcmp(Name,"TurnKd")==0)
		{
			TurnPID.Kd=atof(Value);
		}
	}
	else if (strcmp(Tag, "joystick") == 0)
	{
		int8_t LH = atoi(strtok(NULL, ","));
		int8_t LV = atoi(strtok(NULL, ","));
		int8_t RH = atoi(strtok(NULL, ","));
		int8_t RV = atoi(strtok(NULL, ","));
		
		SpeedPID.Target=LV/25.0;
		TurnPID.Target=RH/25.0;
		
	}
	
	BlueSerial_RxFlag = 0;
}
		
		BlueSerial_Printf("[plot,%f,%f]",SpeedPID.Target,AveSpeed);
	}
}

void TIM1_UP_IRQHandler(void)
{
	static uint16_t Count0,Count1;
	
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
	{
		TimerErrorFlag=0;
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		
		Key_Tick();
		
		Count0 ++;
		if(Count0==10)
		{
			Count0=0;
			
			MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ); 
		
			GY+=23;
		
			AngleGyro=Angle +GY/32768.9*2000*0.01;
	
			AngleAcc=-atan2(AX,AZ)/3.14159*180;
			
			AngleAcc+=3.08;
		
			float Alpha = 0.01;
			Angle=Alpha*AngleAcc+(1-Alpha)*AngleGyro;
		
			if(Angle>50||Angle<-50)
			{
				RunFlag=0;
			}
			
			if(RunFlag==1)
			{
				AnglePID.Actual=Angle;
				PID_Update(&AnglePID);
				AvePWM=AnglePID.Out;
				
				LeftPWM=AvePWM+DifPWM/2;
				RightPWM=AvePWM-DifPWM/2;
				
				if(LeftPWM>100){LeftPWM=100;}else if(LeftPWM<-100){LeftPWM=-100;}
				if(RightPWM>100){RightPWM=100;}else if(RightPWM<-100){RightPWM=-100;}
					
				Motor_SetPWM(2,LeftPWM);
				Motor_SetPWM(1,RightPWM);

			}
			else
			{
				Motor_SetPWM(2,0);
				Motor_SetPWM(1,0);
			}
		}
		Count1++;
		if(Count1>=50)
		{
			Count1=0;
			
			LeftSpeed  = Encoder_Get(2) / 44.0 / 0.05 / 9.27666;
			RightSpeed = Encoder_Get(1) / 44.0 / 0.05 / 9.27666;

			// 计算当前瞬时速度
			float Current_AveSpeed = (LeftSpeed + RightSpeed) / 2.0;

			// 一阶低通滤波 (系数 0.3 可以根据实际情况微调，范围 0.1~0.5)
			// 注意：AveSpeed 需要是全局变量，或者在这里声明为 static
			AveSpeed = 0.3 * Current_AveSpeed + 0.7 * AveSpeed; 

			DifSpeed = LeftSpeed - RightSpeed;

			if(RunFlag == 1)
		{
			SpeedPID.Actual = AveSpeed; // 把平滑后的速度喂给 PID
			PID_Update(&SpeedPID);  
			if(SpeedPID.ErrorInt > 2.0)  SpeedPID.ErrorInt = 2.0;
			if(SpeedPID.ErrorInt < -2.0) SpeedPID.ErrorInt = -2.0;
			
			float target_angle = SpeedPID.Out;
			if(target_angle > 10.0) target_angle = 10.0;
			if(target_angle < -10.0) target_angle = -10.0;
			AnglePID.Target = target_angle; 
			
			TurnPID.Actual = DifSpeed; // 把平滑后的速度喂给 PID
			PID_Update(&TurnPID);               
			DifPWM = TurnPID.Out; 
		}
			if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
		{
			TimerErrorFlag=1;
			TIM_ClearITPendingBit(TIM1,TIM_IT_Update);			
		}
		TimerCount=TIM_GetCounter(TIM1);
	}
}
}
