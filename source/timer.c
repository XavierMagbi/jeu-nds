#include "timer.h"
#include <nds/arm9/background.h>
#include <nds.h>
#include <stdio.h>

// Global Variables
static TimerCallback gameUpdateCallback = NULL; 
int speedMultiplier = 1; 
int scrollX = 0;
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



void testISR() {
    //iprintf("Test ISR triggered!\n");
    scrollX = (scrollX + 1) % 256; // Increment scroll position
    REG_BG0HOFS = scrollX; 
}

void initScrollTimer() {
    
    TIMER0_CR = TIMER_ENABLE | TIMER_DIV_64 | TIMER_IRQ_REQ; // Enable Timer0 with 1/1024 prescaler
    TIMER0_DATA = TIMER_FREQ_64(50);         // Set the timer for a 1-second interval
    irqSet(IRQ_TIMER0, &testISR);              // Attach the ISR
     

    
}










