/* Blinky_LED.h */
#ifndef BLINKY_LED_H
#define BLINKY_LED_H

/* Function Declarations - from C file content */
void initLED(void);
void blinkLED(unsigned int ms);
void blinkChar(char c);
void blinkMessage(const char *msg);

#endif /* BLINKY_LED_H */