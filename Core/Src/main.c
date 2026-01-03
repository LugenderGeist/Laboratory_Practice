#include <init.h>

int main(void)
{

GPIO_Init();

    while(1){
        if ((GPIOC_READ1 != 0)) { 
        GPIO |= GPIOEN0;
        GPIO |= GPIOEN1;
        GPIO |= GPIOEN2; 
        GPIO |= GPIOOFF3;
        GPIO |= GPIOOFF4;
        GPIO |= GPIOOFF5;
        
        }
        else if ((GPIOC_READ2 != 0)) {
        GPIO |= GPIOOFF0;
        GPIO |= GPIOOFF1;
        GPIO |= GPIOOFF2; 
        GPIO |= GPIOEN3;
        GPIO |= GPIOEN4;
        GPIO |= GPIOEN5;
        }
        else{
        GPIO |= GPIOOFF0;
        GPIO |= GPIOOFF1;
        GPIO |= GPIOOFF2; 
        GPIO |= GPIOOFF3;
        GPIO |= GPIOOFF4;
        GPIO |= GPIOOFF5;
        }

    }

}