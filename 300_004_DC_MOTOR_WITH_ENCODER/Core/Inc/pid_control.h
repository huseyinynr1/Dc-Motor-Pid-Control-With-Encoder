/*
 * pid_control.h
 *
 *  Created on: Mar 9, 2025
 *      Author: husey
 */
typedef struct{
	float kp;
	float ki;
	float kd;

	float ts;

	float error;
	float lastError;

	float iMax;
	float iMin;

	float dMax;
	float dMin;

	float partP;
	float partI;
	float partD;

	float pidMax;
	float pidMin;

	float pidOutput;
}pid_param;


void pidInit(pid_param* controller, float kp, float ki, float kd, float ts, float iMaxLimit, float iMinLimit,
		     float dMaxLimit, float dMinLimit, float pidMaxLimit, float pidMinLimit);
void pidChangeCoefficient(pid_param* controller, float kp, float ki, float kd, float ts);
void pidControl(pid_param* controller, float error);
float GetPidOutput(pid_param* controller);
