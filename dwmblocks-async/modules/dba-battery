#!/bin/bash

_battery=$(cat /sys/class/power_supply/BAT0/capacity | awk '{ print int($0) }')

battery=$(cat /sys/class/power_supply/BAT0/capacity | awk '{ print $0"%" }')

print_battery()
{
    echo ^b#79dac8^^c#080808^" $1 "^d^^c#79dac8^ ${battery}^d^
}

case "$_battery" in
    100) print_battery 󰁹
    ;;
    9[0-9]) print_battery 󰂂
    ;;
    8[0-9]) print_battery 󰂁
    ;;
    7[0-9]) print_battery 󰂀
    ;;
    6[0-9]) print_battery 󰁿
    ;;
    5[0-9]) print_battery 󰁾
    ;;
    4[0-9]) print_battery 󰁽
    ;;
    3[0-9]) print_battery 󰁼
    ;;
    2[0-9]) print_battery 󰁻
    ;;
    1[0-9]) print_battery 󰁺
    ;;
    [1-9]) print_battery 󰂎
    ;;
    *) print_battery 󱉞
    ;;
esac
