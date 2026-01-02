#include <init.h>

int main(void)
{

GPIO_Init();

    while(1){
        GPIO |= GPIOEN0;
        GPIO |= GPIOEN1;
        GPIO |= GPIOEN2; // включение светодиода B2
        GPIO |= GPIOEN3;
        GPIO |= GPIOEN4;
        GPIO |= GPIOEN5;
        
        
    }

}