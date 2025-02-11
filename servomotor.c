#include <stdio.h> //biblioteca padrão da linguagem C
#include "pico/stdlib.h" //subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

#define LED_BLUE 12  // GPIO utilizada para controle do Led Azul

// Função para configurar o PWM na frequência desejada (50 Hz)
uint pwm_setup() {
    gpio_set_function(LED_BLUE, GPIO_FUNC_PWM);         // Configura o pino como saída PWM
    uint slice = pwm_gpio_to_slice_num(LED_BLUE);         // Obtém o slice correspondente

    // Configura o divisor de clock:
    pwm_set_clkdiv(slice, 125.0);
    
    // Para obter um período de 20 ms (20.000 µs) no PWM:
    // wrap + 1 = 20000  =>  wrap = 19999
    pwm_set_wrap(slice, 19999);

    pwm_set_enabled(slice, true);  // Habilita o slice PWM

    return slice;
}

int main() {
    stdio_init_all();  // Inicializa o sistema de I/O
    pwm_setup();  // Configura o PWM

    // 1) Posição para 180° (pulso de 2400 µs)
    pwm_set_gpio_level(LED_BLUE, 2400);
    printf("Posicao: 180 graus\n");
    sleep_ms(5000);  // Aguarda 5 segundos

    // 2) Posição para 90° (pulso de 1470 µs)
    pwm_set_gpio_level(LED_BLUE, 1470);
    printf("Posicao: 90 graus\n");
    sleep_ms(5000);  // Aguarda 5 segundos

    // 3) Posição para 0° (pulso de 500 µs)
    pwm_set_gpio_level(LED_BLUE, 500);
    printf("Posicao: 0 graus\n");
    sleep_ms(5000);  // Aguarda 5 segundos

    // 4) Movimentação suave entre 0° e 180°:
    // Incrementa o pulso de 500 µs até 2400 µs com passos de 5 µs e depois decrementa.
    while (true) {
        // Movimento de 0° para 180°
        for (int level = 500; level <= 2400; level += 5) {
            pwm_set_gpio_level(LED_BLUE, level);
            sleep_ms(10);  // Atraso de 10 ms entre os incrementos
        }
        // Movimento de 180° para 0°
        for (int level = 2400; level >= 500; level -= 5) {
            pwm_set_gpio_level(LED_BLUE, level);
            sleep_ms(10);  // Atraso de 10 ms entre os decrementos
        }
    }

    return 0;
}
