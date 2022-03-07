#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bme280.h"
#include "uart.h"

#define true 1
#define false 0

int use_terminal = false;
struct bme280_dev bme_connection;
int uart_filesystem, key_gpio = 1;

void turnoff_program() {
  system("clear");
  printf("Programa encerrado\n");
  turn_resistance_off();
  turn_fan_off();
  close_uart(uart_filesystem);
  exit(0);
}

void pid_routine(int key) {
  system("clear");
  float TI, TR, TE;
  int value_to_send = 0;
  printf("\n================== Iniciada rotina PID ==================\n");
  pid_configura_constantes(20, 0.1, 100);
  do {
    write_uart_get(uart_filesystem, GET_INTERNAL_TEMP);
    TI = read_uart(uart_filesystem, GET_INTERNAL_TEMP).float_value;

    double value_to_send = pid_controle(TI);

    pwm_control(value_to_send);

    write_uart_get(uart_filesystem, GET_POTENTIOMETER);
    TR = read_uart(uart_filesystem, GET_POTENTIOMETER).float_value;

    pid_atualiza_referencia(TR);

    TE = get_current_temperature(&bme_connection);
    printf("\tUART TI: %.2f⁰C - TR: %.2f⁰C - TE: %.2f⁰C\n", TI, TR, TE);
    print_display("UART ", TI, TR, TE);

    if (!use_terminal) {
      write_uart_get(uart_filesystem, GET_KEY_VALUE);
      key_gpio = read_uart(uart_filesystem, GET_KEY_VALUE).int_value;
    }

    write_uart_send(uart_filesystem, value_to_send);
  } while (key_gpio == key);
  printf("============================================================\n");
}

void terminal_routine(float TR, int key) {
  system("clear");
  float TI, TE;
  int value_to_send = 0;
  printf("\n================== Iniciada rotina PID ==================\n");
  pid_configura_constantes(20, 0.1, 100);
  do {
    write_uart_get(uart_filesystem, GET_INTERNAL_TEMP);
    TI = read_uart(uart_filesystem, GET_INTERNAL_TEMP).float_value;

    double value_to_send = pid_controle(TI);

    pwm_control(value_to_send);

    write_uart_get(uart_filesystem, GET_POTENTIOMETER);
    // TR = read_uart(uart_filesystem, GET_POTENTIOMETER).float_value;

    pid_atualiza_referencia(TR);

    TE = get_current_temperature(&bme_connection);
    printf("\tTERMINAL TI: %.2f⁰C - TR: %.2f⁰C - TE: %.2f⁰C\n", TI, TR, TE);
    print_display("Terminal ", TI, TR, TE);

    if (!use_terminal) {
      write_uart_get(uart_filesystem, GET_KEY_VALUE);
      key_gpio = read_uart(uart_filesystem, GET_KEY_VALUE).int_value;
    }

    write_uart_send_REF(uart_filesystem, TR);
  } while (key_gpio == key);
  printf("============================================================\n");
  // on_off_routine(key_gpio);
}

void init() {
  wiringPiSetup();
  turn_resistance_off();
  turn_fan_off();
  connect_display();
  bme_connection = connect_bme();
  uart_filesystem = connect_uart();
  system("clear");
}

void menu () {
  int option;
  float INPUT_TR;
  printf("Como deseja controlar o programa?\n\t1) Terminal\n\t2) Potenciometro\n\t 3)Curva Reflow(Nao funciona)\n");
  scanf("%d", &option);
  switch (option) {
    case 1:
      system("clear");
      printf("Digite o valor que deseja para a Temperatura Referencial\n");
      scanf("%f", &INPUT_TR);
      use_terminal = true;
      terminal_routine(INPUT_TR, 1);
    case 2:
      use_terminal = true;
      pid_routine(1);

    case 3:
     turn_off_system(1);
    default:
      system("clear");
      printf("Opção invalida\n");
      menu();
      break;
  }
}

int main() {
  init();
  signal(SIGINT, turnoff_program);
  // signal(SIGQUIT, toggle_routine);
  menu();
  return 0;
}
