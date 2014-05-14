
#include <ezarm/clock.h>
#include <ezarm/gpio.h>
#include <ezarm/delay.h>

#define LED PB2

main () 
{
  eza_clock_init (EZA_CLK_MAX);
  eza_gpio_set_pinmode (LED, EZA_GPIO_OUTPUT);
  while (1) {
    eza_gpio_toggle (LED);
    eza_delay_ms (300);
  }
}

