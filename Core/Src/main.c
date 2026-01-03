#include <init.h>
int B;

int main(void)
{

GPIO_Init();

    while(1){
        
        
        if ((GPIO_READ1 == 0)) 
        { 
        GPIO |= GPIOEN0;
        GPIO |= GPIOOFF1;
        B = 0;
        }
        if ((GPIO_READ1 != 0)) 
        {
        GPIO |= GPIOOFF0;
        GPIO |= GPIOEN1;
        B = 1;
        }
        if ((GPIO_READ2 == 0)) 
        { 
        GPIO |= GPIOEN2;
        GPIO |= GPIOOFF3;
        B = 0;
        }
        if ((GPIO_READ2 != 0)) 
        {
        GPIO |= GPIOOFF2;
        GPIO |= GPIOEN3;
        B = 1;
        }

        //if ((GPIO_READ2 == 0)) 
        //{ 
       // GPIO |= GPIOEN1;
       // }
       // else
       // {
       // GPIO |= GPIOEN3;
        //}

    }

}