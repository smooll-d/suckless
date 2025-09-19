#!/usr/bin/env bash

listener_dir="${HOME}/.local/state/dba/volume"
listener_path="${HOME}/.local/state/dba/volume/bluetooth_listener.txt"

mkdir -p "${listener_dir}"
echo "unknown" > "${listener_path}"

check_bluetooth()
{
    local field="$1"
    local expected="$2"

    actual=$(bluetoothctl devices Connected | awk 'NR == 1 { print $2 }' | bluetoothctl info | grep --color=never "$1" | awk '{ print $2 }')

    if [ "$actual" = "$expected" ]; then
        true
    else
        false
    fi
}

if command -v bluetoothctl &> /dev/null; then
    while true; do
        sleep 2
        connected=$(cat "${listener_path}")
        if check_bluetooth Icon audio-headset; then
            if check_bluetooth Connected yes && [ "${connected}" != "yes" ]; then
                echo "yes" > "${listener_path}"
                kill -35 $(pidof dwmblocks)
            fi
        else
            if [ "${connected}" = "unknown" ]; then
                continue
            elif [ "${connected}" = "yes" ]; then
                echo "no" > "${listener_path}"
                kill -35 $(pidof dwmblocks)
            fi
        fi
    done
fi
