#include "init.h"

void GPIO_Init(void) {
    RCC_GPIO_ENF;
    RCC_GPIO_ENB;
    GPIOF_PPUP;
    GPIOB_PPUP;

    uint32_t gpio_sets[] = {GPIO_SET0, GPIO_SET1, GPIO_SET2, GPIO_SET3, GPIO_SET4, GPIO_SET5};
    for (int i = 0; i < 6; i++) {
        GPIOF_MODER |= gpio_sets[i];
        GPIOF_OSPEED |= gpio_sets[i];
    }
}

void off_all_led(void) {
    GPIO |= 0x10000;  // Выкл LED0
    GPIO |= 0x20000;  // Выкл LED1
    GPIO |= 0x40000;  // Выкл LED2
    GPIO |= 0x80000;  // Выкл LED3
    GPIO |= 0x100000; // Выкл LED4
    GPIO |= 0x200000; // Выкл LED5
}

int read_button(uint8_t button_pin) {
    if (button_pin == 0) {return 0;}
    else {return 1;}
}
