#include <init.h>
int B1;
int B1_prev;
int B2;
int B2_prev;

int count_B1 = 1; // число светодиодов, горящих одновременно
int LED_group = 0; //позиция группы светодиодов
int LED_index; // индекс текущего светодиода
const int LED_num = 6; // всего светодиодов


int main(void)
{

GPIO_Init();

    // В начале выключаем все светодиоды
    GPIO |= 0x10000;   // Выкл LED0
    GPIO |= 0x20000;   // Выкл LED1
    GPIO |= 0x40000;   // Выкл LED2
    GPIO |= 0x80000;   // Выкл LED3
    GPIO |= 0x100000;  // Выкл LED4
    GPIO |= 0x200000;  // Выкл LED5
    
    // И включаем начальное количество (1 светодиод)
    GPIO |= 0x01;      // Вкл LED0

    while(1){
        
        // Считывание первой кнопки
        if ((GPIO_READ1 == 0)) { B1 = 0;}
        if ((GPIO_READ1 != 0)) { B1 = 1;}   
        if (B1_prev == 0 && B1 == 1) {
            
            count_B1++; // count_B1 по сути число светодиодов, которые включаются
            if (count_B1 > LED_num) {count_B1 = 1;} 
            LED_group = 0;
        
            GPIO |= 0x10000;   // Выкл LED0
            GPIO |= 0x20000;   // Выкл LED1
            GPIO |= 0x40000;   // Выкл LED2
            GPIO |= 0x80000;   // Выкл LED3
            GPIO |= 0x100000;  // Выкл LED4
            GPIO |= 0x200000;  // Выкл LED5

            for (int i = 0; i < count_B1; i++)
            {
                LED_index = i;  // Начинаем всегда с 0 при изменении количества
                GPIO |= (0x01 << LED_index);
            }
        }
        B1_prev = B1;
         

        

        // Считывание второй кнопки
        if ((GPIO_READ2 == 0)) { B2 = 0;}
        if ((GPIO_READ2 != 0)) { B2 = 1;}

        LED_group = count_B1; // отдельно выписываем сколько светодиодов за раз должно включаться

        if (B2_prev == 0 && B2 == 1){
              LED_group += count_B1;
            
            // Обеспечиваем циклический сдвиг (0..5)
            if (LED_group >= LED_num) { LED_group -= LED_num;} 
        
        // 1. Выключаем ВСЕ светодиоды
            GPIO |= 0x10000;   // Выкл LED0
            GPIO |= 0x20000;   // Выкл LED1
            GPIO |= 0x40000;   // Выкл LED2
            GPIO |= 0x80000;   // Выкл LED3
            GPIO |= 0x100000;  // Выкл LED4
            GPIO |= 0x200000;  // Выкл LED5
            
            // 2. Включаем группу светодиодов
            for (int i = 0; i < count_B1; i++)
            {
                // Вычисляем индекс светодиода с циклическим сдвигом
                LED_index = (LED_group + i) % LED_num;
                // Включаем светодиод
                GPIO |= (0x01 << LED_index);
            }
        }
        B2_prev = B2;

    }
}