#include <stdint.h>

// Первое число - литера GPIO
// Второе число - настройка (RCC, MODER и  т.д.)
// Число после равно - настройка для контретного бита или номер бита

#define RCC_GPIO_ENF (*(uint32_t *)(0x40023800 + 0x30) |= 0x20) // тактирование для шины AHB1, для GPIOF
#define RCC_GPIO_ENB (*(uint32_t *)(0x40023800 + 0x30) |= 0x02) // тактирование для шины AHB1, для GPIOB
#define GPIOF_MODER (*(uint32_t *)(0x40021400 + 0x00))          // вход или выход портов F
#define GPIOF_OSPEED (*(uint32_t *)(0x40021400 + 0x08))         // скорость работы портов F
#define GPIOF_PPUP (*(uint32_t *)(0x40021400 + 0x0C) |= 0x00)   // нет подтяжки/стяжки на портах F
#define GPIOB_PPUP (*(uint32_t *)(0x40020400 + 0x0C) |= 0x00)   // Стяжка для кнопок
#define GPIO *(uint32_t *)(0x40021400 + 0x18)                   // вкл пина группы F

#define GPIO_READ1 (*(uint32_t *)(0x40020400 + 0x10) & 0x400) // B10
#define GPIO_READ2 (*(uint32_t *)(0x40020400 + 0x10) & 0x800) // B11

#define GPIO_SET0 0x01  // GPIO F0 01
#define GPIO_SET1 0x04  // GPIO F1 01
#define GPIO_SET2 0x10  // GPIO F2 01
#define GPIO_SET3 0x40  // GPIO F3 01
#define GPIO_SET4 0x100 // GPIO F4 01
#define GPIO_SET5 0x400 // GPIO F5 01

void GPIO_Init(void);