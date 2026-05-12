#include "stm32f10x.h"                  // Device header
#include "PID.h"

void PID_Update(PID_t *p)
{
	p->Error1 = p->Error0;
	p->Error0 = p->Target-p->Actural;
	
	if(p->Ki!=0)
	{
		p->ErrorInt += p->Error0;
	}
	else
	{
		p->ErrorInt=0;
	}
	
	p->Out=p->Kp * p->Error0
		  +p->Ki * p->ErrorInt
		  +p->Kd * (p->Error0-p->Error1);
	if (p->Out > p->Max){p->Out = p->Max;}
	if (p->Out < p->Min){p->Out = p->Min;}
	
}
