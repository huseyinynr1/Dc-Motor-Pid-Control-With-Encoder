#ifndef INC_JGB37_520_ENCODER_H_
#define INC_JGB37_520_ENCODER_H_
#include"main.h"

#define ENCODER_PULSE_PER_REV 72        // Motor bir turda 72 pulse üretir
#define SPEED_CALC_PERIOD 0.05f          // Hız hesaplaması her 0.2 saniyede yapılacak
#define SEC_TO_MINUTE 60.0f             // Saniyeyi dakikaya çevirme katsayısı

typedef struct{
    volatile int32_t encoderPulse;              // Toplam pulse sayısı
    volatile int32_t previousEncoderPulse;      // Önceki ölçümdeki pulse
    volatile int32_t deltaPulse;                // Pulse farkı (son - önceki)

    volatile uint16_t rpm;                      // Devir/dakika değeri (RPM)
    volatile int16_t angle;                     // Anlık açı (0-360 derece)

    volatile float speed;                       // Anlık hız değeri
    volatile float previousSpeed;               // Önceki hız
    volatile float acceleration;                // İvme değeri
} motor_param;

extern TIM_HandleTypeDef htim1;                 // PWM üretmekte kullanılan timer (TIM1)

motor_param* Encoder_GetParameters(void);       // motor_param yapısına pointer döndürür
void Motor_Init(uint16_t dutyCycle, uint8_t directionInfo); // Motoru başlatır
void Encoder_Update();                          // Encoder pulse okuma (interrupt içinde çağrılır)
void Encoder_CalculateSpeedAndAcceleration();   // Hız ve ivme hesaplaması
void Motor_SetPwmDutyCycle(uint16_t dutyCycle); // PWM duty cycle ayarlama

uint16_t Encoder_GetRPM(void);                  // RPM (devir) değeri döndürür
float Encoder_GetSpeed(void);                   // Hız değeri döndürür
float Encoder_GetAngle(void);                   // Anlık açı değeri döndürür
float Encoder_GetAcceleration(void);            // İvme değeri döndürür
int16_t Encoder_GetEncoderPulse(void);          // Anlık encoder pulse sayısı
int16_t Encoder_GetPreviousEncoderPulse(void);  // Önceki encoder pulse değeri
int16_t Encoder_GetDeltaPulse(void);            // İki ölçüm arasındaki pulse farkı

#endif /* INC_JGB37_520_ENCODER_H_ */
