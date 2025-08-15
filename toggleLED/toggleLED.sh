#!/bin/bash

echo "Toggling LED"

LED_GPIO_PIN=16
count=${count:-5}

echo "Enter toggle count: "
read  count

for ((i=0; i<count; i++))
do 
	gpioset gpiochip0 $LED_GPIO_PIN=1
	echo "LED ${LED_GPIO_PIN} is on!!!"
	sleep 1
	gpioset gpiochip0 $LED_GPIO_PIN=0
	echo "LED ${LED_GPIO_PIN} is off!"
	sleep 1
done

