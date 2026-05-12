#ifndef _PID_H
#define _PID_H


typedef struct
{
	float Target;
	float Actural;
	float Out;
	
	float Kp;
	float Ki;
	float Kd;
	
	float Error0;
	float Error1;
	float ErrorInt;
	
	float Max;
	float Min;
} PID_t;

void PID_Update(PID_t *p);


#endif
