#!/usr/bin/env bash

if command -v acpi_listen &> /dev/null; then
    acpi_listen | while IFS= read -r line; do
        if [ "$line" = "jack/headphone HEADPHONE plug" ] || [ "$line" = "jack/headphone HEADPHONE unplug" ]; then
            kill -35 $(pidof dwmblocks)
        fi
        sleep 1
    done &
fi

volume=$(wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{ print($2 * 100) }')

case ${BLOCK_BUTTON} in
    1) pamixer -t
       ;;
    3) pavucontrol
       ;;
esac

if [[ ${volume} -ge 66 ]]; then
    volume_icon=""
    notify_icon="audio-volume-high"
elif [[ ${volume} -ge 33 ]] && [[ ${volume} -lt 66 ]]; then
    volume_icon=""
    notify_icon="audio-volume-medium"
elif [[ ${volume} -lt 33 ]]; then
    volume_icon=""
    notify_icon="audio-volume-low"
fi

if [[ -n $(wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{ print $3 }') ]]; then
    volume_icon=""
    volume="M"
    notify_icon="audio-volume-muted"
fi

if command -v notify-send &> /dev/null; then
    notify-send -i "${notify_icon}" "${volume}%"
fi

echo ^b#ff5189^^c#080808^" ${volume_icon} "^d^^c#ff5189^" ${volume}% "^d^
