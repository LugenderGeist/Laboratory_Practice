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
    uint32_t gpio_off[] = {GPIO_OFF0, GPIO_OFF1, GPIO_OFF2, GPIO_OFF3, GPIO_OFF4, GPIO_OFF5};
    for (int i = 0; i < 6; i++){
        GPIO |= gpio_off[i]; 
    }
}

int read_button(uint8_t button_pin){ // сигнал кнопки 1 или 0
    if (button_pin == 0) {return 0;}
    else {return 1;}
}
