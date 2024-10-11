#include "gpio.h"

typedef struct{
  // Step 3:
  // Add register definitions here
  uint32_t unused_A[(0x504)/4];
  uint32_t OUT; //0x504
  uint32_t OUTSET; //0x508
  uint32_t OUTCLR; //0x50C
  uint32_t IN; //0x510
  uint32_t DIR; //0x514
  uint32_t DIRSET; //0x518
  uint32_t DIRCLR; //0x51C
  uint32_t LATCH; //0x520
  uint32_t DETECTMODE; //0x524
  uint32_t unused_B[(0x700 - 0x524)/4 -1];
  uint32_t PIN_CNF[32]; //0x528-0x77C
} gpio_reg_t;

volatile gpio_reg_t* GPIO_REG_P0 = (gpio_reg_t*)(0x50000000);
volatile gpio_reg_t* GPIO_REG_P1 = (gpio_reg_t*)(0x50000300);

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // Implement me
  // This function should configure the pin as an input/output
  // Hint: Use proper PIN_CNF instead of DIR
  int new_gpio_num = gpio_num;
  if (gpio_num >= 32) {
    new_gpio_num = gpio_num - 32;

    if (dir == GPIO_INPUT) {
      GPIO_REG_P1->PIN_CNF[new_gpio_num] = GPIO_REG_P1->PIN_CNF[new_gpio_num] & 0xFFFFFFFC;
    }
    else {
      GPIO_REG_P1->PIN_CNF[new_gpio_num] = GPIO_REG_P1->PIN_CNF[new_gpio_num] | 0x00000003;
    }
  }

  else {
    if (dir == GPIO_INPUT) {
    GPIO_REG_P0->PIN_CNF[new_gpio_num] = GPIO_REG_P0->PIN_CNF[new_gpio_num] & 0xFFFFFFFC;
    }
    else {
      GPIO_REG_P0->PIN_CNF[new_gpio_num] = GPIO_REG_P0->PIN_CNF[new_gpio_num] | 0x00000003;
    }
  }

  
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin high
  // It can assume that the pin has already been configured

  if (gpio_num >= 32) {
    int new_gpio_num = gpio_num - 32;
    GPIO_REG_P1->OUTSET = (1 << new_gpio_num);
  }

  else {
    GPIO_REG_P0->OUTSET = (1 << gpio_num);
  }

}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin low
  // It can assume that the pin has already been configured

  int new_gpio_num = gpio_num;
  if (gpio_num >= 32) {
    new_gpio_num = gpio_num - 32;

    GPIO_REG_P1->OUTCLR = (1 << new_gpio_num);
  }
  else {
    GPIO_REG_P0->OUTCLR = (1 << new_gpio_num);
  }
 
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // Implement me
  // This function should read the value from the pin
  // It can assume that the pin has already been configured


  if (gpio_num < 32) {
    //use port 0
    int bit_mask = (1 << gpio_num);
    // printf("%ld\n", GPIO_REG_P0->OUT);
    // printf("bit_mask = %i\n", bit_mask);

    if ((GPIO_REG_P0->IN & bit_mask) != 0) {
      return true;
    }
    else {
      return false;
    }

  }
  else {
    //use port 1
    int new_gpio_num = gpio_num - 32;
    int bit_mask = (1 << new_gpio_num);

    if ((GPIO_REG_P1->IN & bit_mask) != 0) {
      return true;
    }
    else {
      return false;
    }


  }

  
}

// prints out some information about the GPIO driver. Can be called from main()
void gpio_print(void) {
  // Use this function for debugging purposes
  // For example, you could print out struct field addresses
  // You don't otherwise have to write anything here
  printf("%p\n", &(GPIO_REG_P0->OUT));
  printf("%p\n", &(GPIO_REG_P0->DIR));
  printf("%p\n", &(GPIO_REG_P0->LATCH));
  printf("%p\n", &(GPIO_REG_P0->PIN_CNF[0]));
}

