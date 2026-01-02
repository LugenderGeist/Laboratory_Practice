#include <stdint.h>
#define RCC_GPIO_EN (*(uint32_t *)(0x40023800 + 0x30)) //тактирование портов В и С
#define GPIOB_MODER (*(uint32_t *)(0x40020400 + 0x00)) // вход или выход портов В
#define GPIOB_OSPEED (*(uint32_t *)(0x40020400 + 0x08)) //скорость работы портов В

#define GPIOC_READ (*(uint32_t *)(0x40020800 + 0x10) & 0x2000) //считывание кнопки

void GPIO_Init(void);