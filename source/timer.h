#ifndef TIMER_H
#define TIMER_H

#include <nds.h>
#include <stdio.h>

// Callback type for the timer
typedef void (*TimerCallback)(void); 

// Function prototypes
void setTimerCallback(TimerCallback callback);
void initTimer();
void timer_ISR();
void initSpeedTimer();  
void speedTimerISR();
void vblankHandler();
void initSpeedSystem();
void initScrollTimer();
void scrollTimerISR();

#endif

