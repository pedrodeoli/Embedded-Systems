/* ========================================================================
   Programa em C para piscar LED a partir do uso de interrupções.
   O LED começar a piscar
   
   Autor: Pedro Couto
   Data: Fevereiro de 2025
   Atualizado em: Fevereiro de 2025

========================================================================== */

/* ========================================================================== */
/* Bibliotecas */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

/* ========================================================================== */
/* Constantes e defines */

#define BTN_A 5
#define BTN_B 6
#define LED_PIN 1

volatile uint8_t count_button = 0; // Contagem do n° de vezes que o botão foi pressionado
volatile bool is_blinking = false; // Informa se led esta piscado
volatile uint8_t led_frequency = 10; // Frequência inicial
uint64_t start_time = 0; // Armazena tempo de início da sequência para piscar
uint8_t time = 10; // Tempo que o led permanecerá piscando

/* ========================================================================== */
/* Protótipos */

void init_gpio();
static void button_callback(uint gpio, uint32_t events);
void blink_led();

/* ========================================================================== */
/* Função Principal */

int main()
{
    stdio_init_all();
    init_gpio();

    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    gpio_set_irq_enabled(BTN_B, GPIO_IRQ_EDGE_FALL, true);
    
    while (true) 
    {
      if (is_blinking) 
      {
        blink_led();     
      } /* end if */
    } /* end while */
  
    return 0;                                      /* Retorna 0 ao final da execução da função principal */

} /* end main */

/* ========================================================================== */
/* Funções secundárias */

// Inicializa GPIOs
void init_gpio() 
{ 
    // Inicializa botão A
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);
    // Inicializa botão B
    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);
    // Inicializa led
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);
}

// Função executada ao ocorrer a interrupção gerada pelo botão A e B
static void button_callback(uint gpio, uint32_t events) 
{ 
    if (gpio == BTN_A && !is_blinking) 
    { 
      count_button++;
      printf("Botão A pressionado: %d vezes\n", count_button);
      if (count_button >= 5) 
      {
        is_blinking = true;
        count_button = 0; // Reinicia a contagem
        printf("LED a piscar!\n");
        start_time = time_us_64();
      } /* end if */
    } /* end if */
    else if (gpio == BTN_B) 
    { 
        led_frequency = 1; // Muda a frequência para 1 Hz
        printf("Frequência do LED alterada para 1 Hz\n");
    } /* end else if */
}


void blink_led() 
{
    // Verifica se passaram 10 segundos
    if (time_us_64() - start_time >= time * 1000000) 
    {
      is_blinking = false;
      gpio_put(LED_PIN, 0); // Desliga o LED
      led_frequency = 10; // Reseta a frequência para 10 Hz
      printf("LED desligado!\n");
    } /* end if */
    else 
    {
        static uint64_t last_toggle_time = 0;
        static bool led_state = false;
        uint64_t current_time = time_us_64();
        uint64_t interval = 1000000 / led_frequency; // Intervalo em microssegundos
        
        if (current_time - last_toggle_time >= interval) 
        {
          last_toggle_time = current_time;
          led_state = !led_state;
          gpio_put(LED_PIN, led_state);
        } /* end if */
    } /* end else */
}

/* ========================================================================== */
/* Final do Programa */