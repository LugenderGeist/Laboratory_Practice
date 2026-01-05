#include "init.h"

void GPIO_Init(void) { //настройка регистров для используемых пинов
    RCC_GPIO_ENF;
    RCC_GPIO_ENB;
    GPIOF_PPUP;
    GPIOB_PPUP;

    uint32_t gpio_sets[] = {GPIO_SET0, GPIO_SET1, GPIO_SET2, GPIO_SET3, GPIO_SET4, GPIO_SET5};
    for (int i = 0; i < 6; i++){
        GPIOF_MODER |= gpio_sets[i];
        GPIOF_OSPEED |= gpio_sets[i];
    }
}

void off_all_led(void){ //выключение всех пинов
    GPIO |= 0x10000;
    GPIO |= 0x20000;
    GPIO |= 0x40000;
    GPIO |= 0x80000;
    GPIO |= 0x100000;
    GPIO |= 0x200000;
}

int read_button(uint8_t button_pin){ // сигнал кнопки 1 или 0
    if (button_pin == 0) {return 0;}
    else {return 1;}
}
