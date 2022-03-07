#ifndef UART_H
#define UART_H

#define Turn_ON 0x01
#define Turn_off 0x02
#define Mode_potentiometer 0x03
#define Mode_curve 0x04

#define GET_INTERNAL_TEMP 0xC1 //Solicita Temperatura Interna
#define GET_POTENTIOMETER 0xC2 //Solicita Temperatura Potenciômetro
#define GET_KEY_VALUE 0xC3 //Le comandos do usuário
#define SEND_SIGNAL 0xD1 //Envia sinal de controle Int (4 bytes)
#define SEND_REFERENCE_SIGNAL 0xD2 //Envia sinal de Referência Float (4 bytes)
#define SEND_SYS_STATE 0xD3 //Envia Estado do Sistema (Ligado = 1 / Desligado = 0) (1 byte)
#define SEND_CONTROL_MODE 0xD4 //Modo de Controle (Potenciômetro = 0 / Curva = 1) (1 byte)

typedef struct number {
  int int_value;
  float float_value;
} number;

int connect_uart();
void write_uart_get(int filestream, unsigned char code);
void write_uart_send_CTR(int filestream, int value);
void write_uart_send_REF(int filestream, float reference_signal);
number read_uart(int filestream, unsigned char code);
void close_uart(int filestream);

#endif /* UART_H */
