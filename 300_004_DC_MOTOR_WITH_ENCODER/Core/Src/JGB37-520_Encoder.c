#include "JGB37-520_Encoder.h"                      // Header dosyası dahil edilir

static motor_param parameters;                      // Encoder verilerini tutan yapı (global)

motor_param* Encoder_GetParameters(void) {
    return &parameters;                             // Yapının adresini döndür
}

void Motor_Init(uint16_t dutyCycle, uint8_t directionInfo) {
    if(directionInfo == 1) {                        // İleri yön
        HAL_GPIO_WritePin(Motor_Forward_GPIO_Port, Motor_Forward_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(Motor_Backward_GPIO_Port, Motor_Backward_Pin, GPIO_PIN_RESET);
        for(int i = 0; i <= dutyCycle; i++) {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, i);  // PWM duty cycle arttır
            HAL_Delay(5);                                     // Yavaş yavaş başlat
        }
    } else if(directionInfo == 0) {                 // Geri yön
        HAL_GPIO_WritePin(Motor_Backward_GPIO_Port, Motor_Backward_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(Motor_Forward_GPIO_Port, Motor_Forward_Pin, GPIO_PIN_RESET);
        for(int i = 0; i <= dutyCycle; i++) {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, i);
            HAL_Delay(5);
        }
    } else {
        // Geçersiz yön bilgisi
    }
}

void Encoder_Update() {
    if(HAL_GPIO_ReadPin(GPIOA, Encoder_Phase_A_Pin) == GPIO_PIN_SET) {
        if(HAL_GPIO_ReadPin(GPIOA, Encoder_Phase_B_Pin) == GPIO_PIN_SET) {
            parameters.encoderPulse++;             // Saat yönü
        } else if(HAL_GPIO_ReadPin(GPIOA, Encoder_Phase_B_Pin) == GPIO_PIN_RESET) {
            parameters.encoderPulse--;             // Saat yönü tersi
        }
    }
}

int32_t Encoder_GetDeltaWithOverflow(int32_t current, int32_t previous) {
    if(current >= previous) {
        return current - previous;                 // Normal artış
    } else {
        return (INT32_MAX - previous + 1) + (current - INT32_MIN);  // Overflow düzeltmesi
    }
}

void Encoder_CalculateSpeedAndAcceleration() {
    parameters.deltaPulse = Encoder_GetDeltaWithOverflow(parameters.encoderPulse, parameters.previousEncoderPulse);
    parameters.previousEncoderPulse = parameters.encoderPulse;

    parameters.speed = ((float)parameters.deltaPulse / (float)ENCODER_PULSE_PER_REV)
                     * (SEC_TO_MINUTE / SPEED_CALC_PERIOD);       // Hız hesaplama

    parameters.acceleration = (parameters.speed - parameters.previousSpeed) / SPEED_CALC_PERIOD; // İvme
    parameters.previousSpeed = parameters.speed;
}

void Motor_SetPwmDutyCycle(uint16_t dutyCycle) {
	/*const uint16_t motorStartThresold = 550;

	if(dutyCycle > 0 && dutyCycle < motorStartThresold)
	{
		dutyCycle = motorStartThresold;
	}*/

	if(dutyCycle > 1000)
	{
		dutyCycle = 1000;
	}

	else if(dutyCycle < 0)
	{
		dutyCycle = 0;
	}
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, dutyCycle);      // PWM duty cycle ayarla
}

uint16_t Encoder_GetRPM(void) {
    parameters.rpm = parameters.encoderPulse / ENCODER_PULSE_PER_REV; // RPM hesapla
    return parameters.rpm;
}

float Encoder_GetSpeed(void) {
    if(parameters.speed < 0) {
        parameters.speed = -parameters.speed;      // Negatif hız varsa pozitife çevir
    }
    return parameters.speed;
}

float Encoder_GetAngle(void) {
    parameters.angle = (parameters.encoderPulse % ENCODER_PULSE_PER_REV)
                     * (360 / ENCODER_PULSE_PER_REV);             // 0-360 derece açı hesapla
    return parameters.angle;
}

float Encoder_GetAcceleration(void) {
    return parameters.acceleration;                // İvme değeri döndür
}

int16_t Encoder_GetEncoderPulse(void) {
    return parameters.encoderPulse;               // Enkoderden gelen pulse değerini döndör
}

int16_t Encoder_GetPreviousEncoderPulse(void) {
    return parameters.previousEncoderPulse;      // Son interruptaki pulse değerini döndür
}

int16_t Encoder_GetDeltaPulse(void) {
    return parameters.deltaPulse;                // Pulse değişim değerini döndür
}
