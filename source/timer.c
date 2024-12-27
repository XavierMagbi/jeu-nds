#include "timer.h"

// Callback function pointer
static TimerCallback gameUpdateCallback = NULL;

void setTimerCallback(TimerCallback callback) {
    gameUpdateCallback = callback;
}

void initTimer() {
    TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024;
    TIMER0_DATA = TIMER_FREQ_1024(60); // 60 Hz

    irqSet(IRQ_TIMER0, timer_ISR);
    irqEnable(IRQ_TIMER0);
}

void timer_ISR() {
    static int tickCounter = 0;

    tickCounter++;

    // Trigger callback every 2 ticks
    if (tickCounter % 2 == 0 && gameUpdateCallback != NULL) {
        gameUpdateCallback();
    }
}

