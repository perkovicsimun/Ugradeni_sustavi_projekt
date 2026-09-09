#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "vaga.h"
#include "temperatura.h"
#include "serial.h"
#include "zaslon.h"
#include "pumpa.h"

int main(void){

    vaga_init();
    pumpa_init();
    zaslon_init();
    temperatura_init();
    uart_init();
    vaga_tare();

    while(1){
        float masa_vage = vaga_read_grams();
        float temp_zraka = temperatura_read();
        int32_t postotak = (int32_t)((masa_vage * 100.0) / 180.0);

        if(postotak < 0){
            postotak = 0;
        }
        if(postotak >=100){
            postotak = 100;
        }

        zaslon_set_cursor(0, 0);
        zaslon_print("Voda: ");
        zaslon_printint(postotak);
        zaslon_print("%")

        zaslon_set_cursor(1, 0);
        zaslon_print("Temp: ");
        zaslon_printint((int32_t)temp_zraka);
        zaslon_print(" C   ");

        if(postotak<20){
            pumpa_on();
        }
        else if(postotak>=80){
            pumpa_off();
        }

        _delay_ms(100);

    }










    
    return 0;

}