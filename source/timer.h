#ifndef TIMER_H
#define TIMER_H

#include <nds.h>
#include <stdio.h>

// Function to make the background scrolling 
void ScrollISR();
void initScrollTimer();
void disableScrollTimer();

#endif

