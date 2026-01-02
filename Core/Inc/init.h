#include <stdint.h>

// Первое число - литера GPIO
// Второе число - настройка (RCC, MODER и  т.д.)
// Число после равно - настройка для контретного бита или номер бита

#define RCC_GPIO_EN (*(uint32_t *)(0x40023800 + 0x30)|= 0x02) //тактирование для шины AHB1, для всех GPIO
#define GPIOB_MODER (*(uint32_t *)(0x40020400 + 0x00)) // вход или выход портов В
#define GPIOB_OSPEED (*(uint32_t *)(0x40020400 + 0x08)) //скорость работы портов В
#define GPIOB_PPUP (*(uint32_t *)(0x40020400 + 0x0C) |= 0x00); //нет подтяжки/стяжки на портах В
#define GPIO *(uint32_t *)(0x40020400 + 0x18) // вкл пина группы В

#define GPIO_SET0 0x01 //GPIOB0 01
#define GPIO_SET1 0x04 //GPIOB1 01
#define GPIO_SET2 0x10   //GPIOB2 01
#define GPIO_SET3 0x1000 //GPIOB6 01
#define GPIO_SET4 0x10000 //GPIOB8 01
#define GPIO_SET5 0x40000 //GPIOB9 01

#define GPIOEN0 0x01 //вкл GPIOB0
#define GPIOEN1 0x02 //вкл GPIOB1
#define GPIOEN2 0x04 //вкл GPIOB2
#define GPIOEN3 0x40 //вкл GPIOB6
#define GPIOEN4 0x100 //вкл GPIOB8 
#define GPIOEN5 0x200 //вкл GPIOB9

// #define GPIOC_READ (*(uint32_t *)(0x40020800 + 0x10) & 0x2000) считывание кнопки

void GPIO_Init(void);