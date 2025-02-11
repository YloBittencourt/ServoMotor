# Controle de Servo Motor com Raspberry Pi Pico W

Este programa em C utiliza a biblioteca SDK do Raspberry Pi Pico para controlar um servo motor por meio de um sinal PWM gerado na GPIO 22. Ele movimenta o servo entre 0°, 90° e 180°, além de realizar um movimento contínuo de oscilação entre esses ângulos.

## Vídeo 
Link: https://drive.google.com/file/d/1cbQ_sOgeDbpDZEe54Uk3H0Fcn-cgXkq_/view?usp=sharing

## Requisitos

- Raspberry Pi Pico W
- Servo motor compatível com PWM (ex: SG90, MG995)
- Fonte de alimentação apropriada para o servo motor
- Software para compilar e carregar o programa no Raspberry Pi Pico W
- Bibliotecas do SDK do Raspberry Pi Pico instaladas

## Configuração do PWM

- O sinal PWM é gerado na GPIO 22.
- O "wrap" do PWM é configurado para 20000 ciclos.
- O clock do PWM tem um divisor de 125.0.
- O ciclo de trabalho varia entre 500 (0°), 1470 (90°) e 2400 (180°) microsegundos.

## Como Compilar e Executar

1. Instale o SDK do Raspberry Pi Pico seguindo a [documentação oficial](https://www.raspberrypi.com/documentation/microcontrollers/).
2. Compile o programa utilizando o CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Conecte o Raspberry Pi Pico W ao computador no modo USB mass storage.

## Funcionamento

1. O programa inicializa o PWM na GPIO 22.
2. Move o servo motor para 180° e aguarda 5 segundos.
3. Move o servo motor para 90° e aguarda 5 segundos.
4. Move o servo motor para 0° e aguarda 5 segundos.
5. Em seguida, inicia um loop infinito que oscila o servo entre 0° e 180° de forma contínua.

## Personalização

- Para alterar os ângulos, ajuste os valores de `duty_cycle` nas funções `move_servo_to_X_degrees()`.
- Para modificar a velocidade de oscilação, altere o incremento e a duração do `sleep_ms()` dentro do loop infinito.

## Autor
Ylo Silva de Sá Bittencourt

