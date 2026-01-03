#include <init.h>

int B1;
int B1_prev;
int B2;
int B2_prev;

int count_B1 = 1;      // число светодиодов, горящих одновременно
int LED_group = 0;     // позиция группы светодиодов
int LED_index;         // индекс текущего светодиода
const int LED_num = 6; // всего светодиодов

int main(void) {

    GPIO_Init();
    off_all_led();
    GPIO |= GPIO_SET0;

    while (1) {
        // Считывание первой кнопки
        B1 = read_button(GPIO_READ1);

        if (B1_prev == 0 && B1 == 1) {
            count_B1++;
            if (count_B1 > LED_num) {count_B1 = 1;} 
            LED_group = 0;
            off_all_led();

            for (int i = 0; i < count_B1; i++) { // выбираем число светодиодов 
                LED_index = i;
                GPIO |= (0x01 << LED_index);
            }
        }
        B1_prev = B1;

        // Считывание второй кнопки
        B2 = read_button(GPIO_READ2);

        if (B2_prev == 0 && B2 == 1) {
            LED_group += count_B1; // увеличиваем позицию группы на количество светодиодов

            if (LED_group >= LED_num) {
                off_all_led();
                LED_group = 0;
                for (int i = 0; i < count_B1; i++) {
                    LED_index = (LED_group + i) % LED_num;
                    GPIO |= (0x01 << LED_index);
                }
            }
            else
            {
                for (int i = 0; i < count_B1; i++) {
                    LED_index = (LED_group + i) % LED_num;
                    GPIO |= (0x01 << LED_index);
                }
            }
        }
        B2_prev = B2;
    }
}
