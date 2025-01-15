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

void speedTimerISR() {
    static int seconds = 0;
    seconds++;
    
    if (seconds%10 == 0 &&  speedMultiplier < 4) {  // Every 10 seconds
        speedMultiplier++;
    }
}

void initSpeedTimer() {
    // Set timer to trigger once per second
    TIMER1_DATA = TIMER_FREQ_1024(1);  // Count down from 32 instead of 1
    TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024;
    

    irqSet(IRQ_TIMER1, &speedTimerISR);
    irqEnable(IRQ_TIMER1);
}











