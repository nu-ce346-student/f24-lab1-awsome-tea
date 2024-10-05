// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"

int main(void) {
  printf("Board started!\n");

  // Turn on all LEDs on the back of the Microbit
  // Add code here
  gpio_print();

  //configure 10 GPIO pins as outputs
  gpio_config(21, GPIO_OUTPUT);
  gpio_config(22, GPIO_OUTPUT);
  gpio_config(15, GPIO_OUTPUT);
  gpio_config(24, GPIO_OUTPUT);
  gpio_config(19, GPIO_OUTPUT);
  gpio_config(28, GPIO_OUTPUT);
  gpio_config(11, GPIO_OUTPUT);
  gpio_config(31, GPIO_OUTPUT);
  gpio_config(37, GPIO_OUTPUT);
  gpio_config(30, GPIO_OUTPUT);

  //configure the output value
  //set high all the rows
  gpio_set(21);
  gpio_set(22);
  gpio_set(15);
  gpio_set(24);
  gpio_set(19);

  //clear all the columns
  gpio_clear(28);
  gpio_clear(11);
  gpio_clear(31);
  gpio_clear(37);
  gpio_clear(30);

  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code here


  //CHECK OFF #11 : -------------------------
  //write DIR register
  *(uint32_t*)(0x50000514) = 0x100000;
  //write OUT register
  *(uint32_t*)(0x50000504) = 0x100000;
  // ----------------------------------------

  // loop forever
  // printf("Looping\n");

  // printf("Test 1: \n");
  // gpio_config(20, GPIO_OUTPUT);
  // gpio_clear(20);
  // printf("gpio 20 read: %s\n", gpio_read(20) ? "true" : "false");
  // gpio_set(20);
  // printf("gpio 20 read: %s\n", gpio_read(20) ? "true" : "false");
  // gpio_clear(20);
  // printf("gpio 20 read: %s\n", gpio_read(20) ? "true" : "false");
  // gpio_set(20);
  // printf("gpio 20 read: %s\n", gpio_read(20) ? "true" : "false");


  // printf("Test 1 complete.\n");

  // printf("Test 2: \n");
  // gpio_config(31, GPIO_OUTPUT);
  // printf("gpio 31 read: %s\n", gpio_read(31) ? "true" : "false");
  // gpio_set(31);
  // printf("gpio 31 read: %s\n", gpio_read(31) ? "true" : "false");
  // gpio_clear(31);
  // printf("gpio 31 read: %s\n", gpio_read(31) ? "true" : "false");


  // printf("Test 1 complete.\n");

  //CHECKOFF 13: ------------------
  //initialize buttons
  gpio_config(14, GPIO_INPUT); //button A
  gpio_config(23, GPIO_INPUT); //button B
  gpio_config(20, GPIO_OUTPUT); //microphone LED

  printf("Looping\n");
  while (1) {

    // printf("Looping\n");
    printf("GPIO 14 (A): %s\n", gpio_read(14) ? "true" : "false");
    printf("GPIO 23 (B): %s\n", gpio_read(23) ? "true" : "false");

    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here

    if (gpio_read(14) == false) {
      gpio_set(20);
    }
    if (gpio_read(23) == false) {
      gpio_clear(20);
    }
    // nrf_delay_ms(10);
}
}

