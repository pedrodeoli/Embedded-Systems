/* ========================================================================
   Programa em C para ilustrar o uso do módulo DS1307 
   com a placa Raspberry Pico W.
   
   Autor: Pedro Couto
   Data: Fevereiro de 2025
   Atualizado em: Fevereiro de 2025

========================================================================== */

/* ========================================================================== */
/* Bibliotecas */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

/* ========================================================================== */
/* Constantes */

// Definições do I2C
#define I2C_PORT i2c0
#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5
#define DS1307_ADDR 0x68 // endereço do RTC

// Datetime configurado
uint8_t set_day = 24;
uint8_t set_month = 9;
uint8_t set_year = 24;
uint8_t set_hour = 13;
uint8_t set_minute = 27;
uint8_t set_sec = 0;

/* ========================================================================== */
/* Protótipos */

void init_i2c();
uint8_t decimal_to_bcd(uint8_t decimal);
uint8_t bcd_to_decimal(uint8_t bcd);
void ds1307_set_datetime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
void ds1307_get_datetime(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second);


/* ========================================================================== */
/* Função Principal */
int main()
{
    stdio_init_all();
    init_i2c();

    printf("Inicializando o RTC\n");
    // Configura a data e hora no RTC
    ds1307_set_datetime(set_day, set_month, set_year, set_hour, set_minute, set_sec); // 24/09/2024 – 13:27:00
    printf("Data e hora configuradas: %02d/%02d/20%02d – %02d:%02d:%02d\n",set_day, set_month, set_year, set_hour, set_minute, set_sec);

    while (true)
    {
        uint8_t year, month, day, hour, minute, second;

        // Lê a data e hora do RTC
        ds1307_get_datetime(&year, &month, &day, &hour, &minute, &second);

        printf("Data e hora atuais: %02d/%02d/20%02d – %02d:%02d:%02d\n", day, month, year, hour, minute, second);
        sleep_ms(5000);
    } /* end while */
    
    return 0;

} /* end main */

/* ========================================================================== */
/* Funções Secundárias */

void init_i2c()
{
    // Inicializa a interface I2C
    i2c_init(I2C_PORT, 100 * 1000); // 100 kHz
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
}

// Função para converter decimal para BCD 
uint8_t decimal_to_bcd(uint8_t decimal) 
{
    return ((decimal / 10) << 4) | (decimal % 10);
}

// Função para converter BCD para decimal
uint8_t bcd_to_decimal(uint8_t bcd) 
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void ds1307_set_datetime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) 
{
    uint8_t data[8];

    data[0] = 0x00;
    data[1] = decimal_to_bcd(second); // Segundos
    data[2] = decimal_to_bcd(minute); // Minutos
    data[3] = decimal_to_bcd(hour);   // Horas (formato 24h)
    data[5] = decimal_to_bcd(day);    // Dia
    data[6] = decimal_to_bcd(month);  // Mês
    data[7] = decimal_to_bcd(year);   // Ano

    // Escreve os dados no RTC
    i2c_write_blocking(I2C_PORT, DS1307_ADDR, data, 8, false);
}

void ds1307_get_datetime(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second) 
{
    uint8_t data[7];
    uint8_t reg = 0x00;
    i2c_write_blocking(I2C_PORT, DS1307_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, DS1307_ADDR, data, 7, false);

    // Converte os valores de BCD para decimal
    *second = bcd_to_decimal(data[0] & 0x7F); // Ignora o bit de clock halt
    *minute = bcd_to_decimal(data[1]);
    *hour = bcd_to_decimal(data[2] & 0x3F);   // Ignora o bit de formato 12/24h
    *day = bcd_to_decimal(data[4]);
    *month = bcd_to_decimal(data[5]);
    *year = bcd_to_decimal(data[6]);
}

/* ========================================================================== */
/* Final do Programa */
