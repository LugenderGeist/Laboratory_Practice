#include "init.h"

void GPIO_Init (void){
    RCC_GPIO_EN |= 0x02;  //ТАКТИРОВАНИЕ порта В и С
    GPIOB_MODER |= 0x4000; // ПИН ПБ7 на выход
    GPIOB_OSPEED |= 0x4000; // задана средняя скорость работы пина
    *(uint32_t *)(0x40020400 + 0x0C) |= 0x00; // нет подтяжки/стяжки

}