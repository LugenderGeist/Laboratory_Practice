#include <init.h>
volatile int B1;
volatile int B1_prev;
volatile int B2;
volatile int B2_prev;

int LED_index;          // индекс текущего светодиода
int count_B1 = 1;       // число светодиодов, горящих одновременно
int LED_group = 0;      // позиция группы светодиодов
const int LED_num = 6;  // всего светодиодов в системе

int main(void){
    GPIO_Init();
    off_all_led();
    *(uint32_t *)(0x40021400 + 0x18) |= 0x01; // включение первого светодиода

    while (1){

       // Считывание первой кнопки
       B1 = read_button(GPIO_READ1);
        if (B1_prev == 0 && B1 == 1){
            count_B1++;
            if (count_B1 > LED_num){
                count_B1 = 1;
            }
            LED_group = 0;
            off_all_led();
            for (int i = 0; i < count_B1; i++){
                LED_index = i;
                GPIO |= (0x01 << LED_index);
            }
        }
        B1_prev = B1;

        // Считывание второй кнопки
        B2 = read_button(GPIO_READ2);
        if (B2_prev == 0 && B2 == 1){
            if (count_B1 == LED_num){
                static int all_leds_on = 0; //добавляем флаг, включились ли все светодиоды
                if (all_leds_on == 0){
                    off_all_led();
                    for (int i = 0; i < LED_num; i++){
                        GPIO |= (0x01 << i);
                    }
                    all_leds_on = 1;
                    LED_group = 0;
                }
                else{
                    off_all_led();
                    all_leds_on = 0;
                    LED_group = 0;
                }
            }
            else{
                LED_group += count_B1;

                if (LED_group >= LED_num){
                    off_all_led();
                    LED_group = 0;
                    for (int i = 0; i < count_B1; i++){
                        LED_index = i;
                        GPIO |= (0x01 << LED_index);
                    }
                }
                else{
                    for (int i = 0; i < count_B1; i++){
                        LED_index = (LED_group + i) % LED_num;
                        GPIO |= (0x01 << LED_index);
                    }
                }
            }
        }
        B2_prev = B2;
    }
}