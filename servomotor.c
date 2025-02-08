#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define PWM_GPIO 22
#define PWM_WRAP 20000

// Função para configurar o PWM
void setup_pwm() {
    gpio_set_function(PWM_GPIO, GPIO_FUNC_PWM); // Set GPIO 22 as PWM
    uint slice_num = pwm_gpio_to_slice_num(PWM_GPIO); // Pega o número do slice do PWM
    pwm_set_wrap(slice_num, PWM_WRAP); // Seta o valor de wrap do PWM
    pwm_set_clkdiv(slice_num, 125.0f); // Seta o divisor de clock do PWM
    pwm_set_enabled(slice_num, true); // Habilita o PWM
}

void set_pwm_duty_cycle(uint slice_num, uint16_t duty_cycle) {
    pwm_set_gpio_level(PWM_GPIO, duty_cycle);
}

void move_servo_to_180_degrees() {
    uint slice_num = pwm_gpio_to_slice_num(PWM_GPIO);
    uint16_t duty_cycle = 2400; // 2.400µs
    set_pwm_duty_cycle(slice_num, duty_cycle);
    sleep_ms(5000); // Aguarda 5 segundos
}

void move_servo_to_90_degrees() {
    uint slice_num = pwm_gpio_to_slice_num(PWM_GPIO);
    uint16_t duty_cycle = 1470; // 1.470µs
    set_pwm_duty_cycle(slice_num, duty_cycle);
    sleep_ms(5000); // Aguarda 5 segundos
}

void move_servo_to_0_degrees() {
    uint slice_num = pwm_gpio_to_slice_num(PWM_GPIO);
    uint16_t duty_cycle = 500; // 500µs
    set_pwm_duty_cycle(slice_num, duty_cycle);
    sleep_ms(5000); // Aguarda 5 segundos
}

int main() {

    stdio_init_all(); // Inicializa a comunicação serial
    setup_pwm(); // Chama a função para configurar o PWM

    // Chamar a função para mover o servo para 180 graus
    move_servo_to_180_degrees();
    // Chamar a função para mover o servo para 90 graus
    move_servo_to_90_degrees();
    // Chamar a função para mover o servo para 0 graus
    move_servo_to_0_degrees();

    // Loop infinito para fazer o servo motor se mover de 0 a 180 graus
    while (true) {
        for (uint16_t duty_cycle = 500; duty_cycle <= 2400; duty_cycle += 5) {
            set_pwm_duty_cycle(pwm_gpio_to_slice_num(PWM_GPIO), duty_cycle);
            sleep_ms(10);
        }
        for (uint16_t duty_cycle = 2400; duty_cycle >= 500; duty_cycle -= 5) {
            set_pwm_duty_cycle(pwm_gpio_to_slice_num(PWM_GPIO), duty_cycle);
            sleep_ms(10);
        }
    }
        
    return 0;
}