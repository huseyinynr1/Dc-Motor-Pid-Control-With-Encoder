	/*
	 * pid_control.c
	 *
	 *  Created on: Mar 9, 2025
	 *      Author: husey
	 */

	#include "pid_control.h"

	void pidInit(pid_param* controller, float kp, float ki, float kd, float ts, float iMaxLimit, float iMinLimit,
				 float dMaxLimit, float dMinLimit, float pidMaxLimit, float pidMinLimit)
	{
		controller->kp = kp;
		controller->ki = ki;
		controller->kd = kd;
		controller->ts = ts;

		controller->iMax = iMaxLimit;
		controller->iMin = iMinLimit;

		controller->dMax = dMaxLimit;
		controller->dMin = dMinLimit;

		controller->pidMax = pidMaxLimit;
		controller->pidMin = pidMinLimit;
	}

	void pidChangeCoefficient(pid_param* controller, float kp, float ki, float kd, float ts)
	{
		controller->kp = kp;
		controller->ki = ki;
		controller->kd = kd;
		controller->ts = ts;

	}


	void pidControl(pid_param* controller, float error)
	{
		controller->error = error;

		controller->partP = controller->error ;

		controller->partI += controller->error * controller->ts;

		controller->partD = (controller->error - controller->lastError) / controller->ts;


		if ( controller->partI > controller->iMax )
		{
			controller->partI = controller->iMax;
		}

		else if(controller->partI < controller->iMin)
		{
			controller->partI = controller->iMin;
		}

		else
		{

		}

		if(controller->partD > controller->dMax)
		{
			controller->partD = controller->dMax;
		}

		else if(controller->partD < controller->dMin)
		{
			controller->partD = controller->dMin;
		}

		else
		{

		}


		controller->pidOutput = (controller->partP * controller->kp) +
								(controller->partI * controller->ki) +
								(controller->partD * controller->kd);


		if(controller->pidOutput > controller->pidMax)
		{
			controller->pidOutput = controller->pidMax;
		}

		else if(controller->pidOutput < controller->pidMin)
		{
			controller->pidOutput = controller->pidMin;
		}

		else
		{

		}

		controller->lastError = controller->error;

	}


	float GetPidOutput(pid_param* controller)
	{
		return(controller->pidOutput);
	}
