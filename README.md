
# STM32 DC Motor PID Control with Encoder

## 🇹🇷 Türkçe Açıklama

Bu proje, **STM32F407** mikrodenetleyicisi ile PID kontrol algoritması kullanarak bir DC motorun hızının kontrol edilmesini amaçlamaktadır. Motor hız geri beslemesi için **JGB37-520 enkoderli DC motor** kullanılmıştır. PID algoritması ile hedef hıza yumuşak ve kararlı bir şekilde ulaşılması hedeflenmiştir.

### 🔧 Özellikler

- Enkoder sinyallerinden hız ve ivme hesaplama
- PID kontrol algoritması ile motor hız kontrolü
- PWM sinyali ile motor sürme
- STM32 HAL kütüphanesi ile yapılandırılmış modüler C kodları

### 📂 Dosya Yapısı

- `main.c`: Ana uygulama kodları
- `JGB37-520_Encoder.c/h`: Enkoder okuma ve hız hesaplama
- `pid_control.c/h`: PID kontrol algoritması

## 🇬🇧 English Description

This project demonstrates how to control the speed of a DC motor using a **PID controller** on the **STM32F407** microcontroller. A **JGB37-520 DC motor with encoder** is used for real-time feedback. The PID loop ensures the motor gradually and stably reaches the target speed.

### 🔧 Features

- Encoder-based speed and acceleration calculation
- Speed control with PID algorithm
- Motor driving with PWM signal
- Modular C code using STM32 HAL library

### 📂 Folder Structure

- `main.c`: Main control logic
- `JGB37-520_Encoder.c/h`: Encoder interface and speed calculation
- `pid_control.c/h`: PID algorithm implementation

---

🛠️ Geliştirici / Developed by: Hüseyin Yanar  
