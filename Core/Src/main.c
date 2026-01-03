#include <init.h>

int B1;
int B1_prev;
int B2;
int B2_prev;

int count_B1 = 1; // число светодиодов, горящих одновременно
int LED_group = 0; //позиция группы светодиодов
int LED_index; // индекс текущего светодиода
const int LED_num = 6; // всего светодиодов

int main(void){

    GPIO_Init();
    off_all_led();
    GPIO |= GPIOEN0;      // Включаем 1 светодиод

    while(1){
        // Считывание первой кнопки
        if ((GPIO_READ1 == 0)) { B1 = 0;}
        if ((GPIO_READ1 != 0)) { B1 = 1;}  

        if (B1_prev == 0 && B1 == 1) {

            count_B1++; // count_B1 по сути число светодиодов, которые включаются
            if (count_B1 > LED_num) {count_B1 = 1;} // сдвиг от 1 до 6
                LED_group = 0;
                off_all_led(); // все выключаем

                for (int i = 0; i < count_B1; i++) // выбираем число светодиодов
                {
                     LED_index = i;
                    GPIO |= (0x01 << LED_index);
                }
        }
        B1_prev = B1;

// Считывание второй кнопки
if ((GPIO_READ2 == 0)) { B2 = 0;}
if ((GPIO_READ2 != 0)) { B2 = 1;}

// Обработка нажатия второй кнопки
if (B2_prev == 0 && B2 == 1)
{
    // Увеличиваем позицию группы на количество светодиодов
    LED_group += count_B1;
    
    // Проверяем, не вышла ли группа за пределы
    if (LED_group >= LED_num)
    {
        // Если вышли за пределы - ВЫКЛЮЧАЕМ ВСЕ светодиоды
        GPIO |= 0x10000;   // Выкл LED0
        GPIO |= 0x20000;   // Выкл LED1  
        GPIO |= 0x40000;   // Выкл LED2
        GPIO |= 0x80000;   // Выкл LED3
        GPIO |= 0x100000;  // Выкл LED4
        GPIO |= 0x200000;  // Выкл LED5
        
        // Сбрасываем позицию группы
        LED_group = 0;
        
        // И ВКЛЮЧАЕМ первую группу снова
        for (int i = 0; i < count_B1; i++)
        {
            LED_index = (LED_group + i) % LED_num;
            GPIO |= (0x01 << LED_index);
        }
    }
    else
    {
        // Если еще в пределах - НЕ выключаем старые, 
        // а только ДОБАВЛЯЕМ новую группу светодиодов
        for (int i = 0; i < count_B1; i++)
        {
            LED_index = (LED_group + i) % LED_num;
            GPIO |= (0x01 << LED_index);
        }
    }
}
B2_prev = B2;
    }
}
