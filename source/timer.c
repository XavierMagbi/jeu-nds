#include "timer.h"

// Global Variables
static TimerCallback gameUpdateCallback = NULL; 
int speedMultiplier = 1; 

// Timer Functions
void setTimerCallback(TimerCallback callback) {
    gameUpdateCallback = callback;
}

void initTimer() {
    TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024;
    TIMER0_DATA = TIMER_FREQ_1024(1); // 1-second intervals

    irqSet(IRQ_TIMER0, timer_ISR);
    irqEnable(IRQ_TIMER0);
}

void timer_ISR() {
    if (gameUpdateCallback != NULL) {
        gameUpdateCallback();
    }
}

void initSpeedTimer() {
    TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024;
    TIMER1_DATA = TIMER_FREQ_1024(10); // Every 10 seconds

    irqSet(IRQ_TIMER1, speedTimerISR);
    irqEnable(IRQ_TIMER1);
}

void speedTimerISR() {
    if (speedMultiplier < 5) {
        speedMultiplier++;
    }
}






