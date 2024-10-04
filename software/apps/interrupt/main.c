// Interrupt app
//
// Trigger GPIO and Software interrupts

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"

// Initialize software interrupts
void software_interrupt_init(void) {
  NRF_EGU1->INTENSET = 0x1;
  NVIC_EnableIRQ(SWI1_EGU1_IRQn);
}

// Trigger a software interrupt
void software_interrupt_trigger(void) {
  NRF_EGU1->TASKS_TRIGGER[0] = 1;
}

void SWI1_EGU1_IRQHandler(void) {
  printf("Software interrupt started!\n");
  // Clear interrupt event
  NRF_EGU1->EVENTS_TRIGGERED[0] = 0;
  nrf_delay_ms(1000);
  printf("Count: 1\n");
  nrf_delay_ms(1000);
  printf("Count: 2\n");
  nrf_delay_ms(1000);
  printf("Count: 3\n");
  nrf_delay_ms(1000);
  printf("Count: 4\n");
  nrf_delay_ms(1000);
  printf("Count: 5\n");


  // Implement me
  printf("Software interrupt complete!\n");
}

void GPIOTE_IRQHandler(void) {
  printf("GPIOTE Interrupt triggered!\n");
  // Clear interrupt event
  NRF_GPIOTE->EVENTS_IN[0] = 0;

  // Implement me
  printf("GPIOTE Interrupt cleared!\n");
}

int main(void) {
  printf("Board started!\n");

  // First task. Trigger a GPIOTE interrupt
  // You can access the GPIOTE register map as NRF_GPIOTE->
  //    where the register name in all caps goes after the arrow.
  //    For example, NRF_GPIOTE->CONFIG[0]
  // Add code here
  NRF_GPIOTE->CONFIG[0] = 0x20E01;
  NRF_GPIOTE->INTENSET = 0x1;
  NVIC_EnableIRQ(GPIOTE_IRQn);
  NVIC_SetPriority(GPIOTE_IRQn,0);

  // Second task. Trigger a software interrupt
  // Use the software_interupt_* functions defined above
  // Add code here
  software_interrupt_init();
  NVIC_EnableIRQ(SWI1_EGU1_IRQn);
  NVIC_SetPriority(SWI1_EGU1_IRQn,3);
  software_interrupt_trigger();



  // loop forever
  while (1) {
    printf("Looping\n");
    nrf_delay_ms(1000);
  }
}

