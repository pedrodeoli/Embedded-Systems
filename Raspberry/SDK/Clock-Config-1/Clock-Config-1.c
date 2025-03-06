/* ========================================================================
   Programa em que implementa ajuste no clock do sistema
   
   Autor: Pedro Couto
   Data: Março de 2025
   Atualizado em: Março de 2025

========================================================================== */

/* ========================================================================== */
/* Bibliotecas */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"

/* ========================================================================== */
/* Constantes */

/* ========================================================================== */
/* Protótipos */

void set_system_clock(uint32_t freq_mhz);

/* ========================================================================== */
/* Função Principal */

int main()
{
    stdio_init_all();

    /*
    clocks_init() inicializa clock com configuração padrão
    clk_sys = 125 MHz
    clk_usb = 48 MHz
    */
    //clocks_init();
    printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
    printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
    sleep_ms(1000);
    /*
    Altera clk_sys para 50 MHz
    */
    set_system_clock(50);
    printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
    printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
} /* end main */

/* ========================================================================== */
/* Funções secundárias */

void set_system_clock(uint32_t freq_mhz) 
{

    // Definimos o PLL_SYS para um valor adequado (precisa ser um múltiplo maior do que freq_mhz)
    // Aqui usamos 120 MHz, pois é um valor gerenciável pelo PLL
    uint32_t pll_freq_mhz = 120;

    if (freq_mhz > 120) 
    {
        pll_freq_mhz = 1500;  // Para frequências muito altas, usamos o PLL_SYS em 1500 MHz
    } else if (freq_mhz > 50) 
    {
        pll_freq_mhz = 120;  // Para frequências médias, usamos o PLL_SYS em 120 MHz
    } else 
    {
        pll_freq_mhz = 96;   // Para frequências mais baixas, usamos 96 MHz
    } /* end if */

    // Inicializa o PLL_SYS com a frequência determinada
    pll_init(pll_sys, 1, pll_freq_mhz * MHZ, 6 * MHZ, 1);

    // Configura o clock do sistema (CLK_SYS) para a frequência desejada
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX,
                    CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, 
                    freq_mhz * MHZ,   // Frequência desejada
                    pll_freq_mhz * MHZ);  // Frequência do PLL_SYS usada como referência

}

/* ========================================================================== */
/* Final do Programa */