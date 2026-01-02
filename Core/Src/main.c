#include <init.h>

int main(void)
{
    GPIO_Init();
    while(1){
        if (GPIOC_READ != 0){
            *(uint32_t *)(0x40020400 + 0x18) |= 0x80; // включение светодиода

        }
        else{
            *(uint32_t *)(0x40020400 + 0x18) |= 0x80; // bit reset
        }
    }

}