#include "timer.h"
#include <nds/arm9/background.h>
#include <nds.h>
#include <stdio.h>

// Global Variables 
int speedMultiplier = 1; 
int scrollX = 0;


void ScrollISR() {
    //iprintf("Test ISR triggered!\n");
    scrollX = (scrollX + 1*speedMultiplier) % 256; // Increment scroll position
    REG_BG0HOFS = scrollX; 
}

void initScrollTimer() {
    TIMER0_CR = TIMER_ENABLE | TIMER_DIV_64 | TIMER_IRQ_REQ; // Enable Timer0 with 1/1024 prescaler
    TIMER0_DATA = TIMER_FREQ_64(25);         // Set the timer for a 1-second interval
    irqSet(IRQ_TIMER0, &ScrollISR);              // Attach the ISR
}

void disableScrollTimer(){
    TIMER0_CR = 0;          // Disable the timer
    irqDisable(IRQ_TIMER0); // Disable its interrupt

    REG_BG0HOFS = 0;
}










