#include "timer.h"

static TimerCallback gameUpdateCallback = NULL; // Callback function pointer
int speedMultiplier = 1; // Constant for the speed of bachground's scrolling 

void setTimerCallback(TimerCallback callback) {
    gameUpdateCallback = callback;
}

void initTimer() {
    TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024;
    TIMER0_DATA = TIMER_FREQ_1024(1); // 60 Hz

    irqSet(IRQ_TIMER0, timer_ISR);
    irqEnable(IRQ_TIMER0);
}

void timer_ISR() {
  int blinkCounter = 0;
  bool showMessage = true;

    blinkCounter++;

    if (blinkCounter >= 30) { // Toggle every 30 frames (~0.5 seconds at 60 FPS)
        showMessage = !showMessage;
        blinkCounter = 0;
    }
}


void initSpeedTimer() {
    TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024;
    TIMER1_DATA = TIMER_FREQ_1024(10); // Every 10 seconds

    irqSet(IRQ_TIMER1, speedTimerISR);
    irqEnable(IRQ_TIMER1);
}

void speedTimerISR() {
    int tick = 0;
    while(speedMultiplier < 5){
        tick++;
        if (tick>10){
            speedMultiplier++;
            tick = 0; 
        }
    }
}





