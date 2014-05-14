ezarm
=====

Library for ARM processors

I have a PCB that fits at least 6 different STM32 processors. ST has
good compatibility across the different processors. So I wrote a 
"blinky" program that blinks the led connected to PB2 on the board. 
After "porting" this program to all 6 boards/cpus, I now have a 74 
line program with 8 #if statements to do things differently for
each CPU. This is the situation I want to move away from. 

The blinky program should be as simple as: 
```
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
```
This should compile into a working program on all six boards. 

Now, some processors have advanced features that others don't have. 
The goal is to have the "simpler" programs that would work on all 
CPUs just work. It should also be possible to access the "advanced"
features of processors. 

So, some processors may have a "2MHz max" and a "50MHz max" GPIO 
output mode. The EZA_GPIO_OUTPUT define is the "i don't want to know"
version of EZA_GPIO_OUTPUT_2MHZ or EZA_GPIO_OUTPUT_50MHZ. Which
one we'll have to decide eventually. Specifying say the 50MHz version
without the feature being available for that processor, could 
result in a compile-time error, or just the "OUTPUT". We'll have
to think about that. I think I'll prefer for it to just work. 

Similarly, when using modules like "i2c", ADC or "USART" there are
differences between processors. But when you request to initialize
say the I2C module in slave mode, the library should chose defaults
to make more advanced processors do the same as the simpler ones. 

Looking in libopencm3-examples, you'll find that it takes on the 
order of 10-20 lines of code to initialize an I2C or SPI module. 
And they are different for various processors.
Providing defaults, the library should just initialize the module, 
into a usable state. 

Goals
=====

* little code to start working with a CPU, and its peripherals. 
* First for STM32, later maybe for other processors as well. 
* Portability across CPUs for simple things like blinky. (and
  a couple of steps more complicated)

Plan
====

The plan is to FIRST write the programs that are supposed to work,
and then implement the library parts that suport those programs. 
The blinky above was written here in the README, and will be
copied into the "examples" directory to provide a guideline to
implement the first lines of the library. 

So if you feel like helping with a module, feel free to submit
an example program first, and then help with implementing
the support for a module.


