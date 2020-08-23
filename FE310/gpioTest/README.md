# gpioTest

Toggle FE310G pin 19 as fast as possible

We configured clock to 320MHz using PLL and tried two ways to toggle the output:
1- using atomic XOR instructions, resulting in a 13.33MHz
2- using a sequence of direct stores, resulting in a 20MHz output
