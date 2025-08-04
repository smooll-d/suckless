#!/usr/bin/env bash

if command -v acpi_listen &> /dev/null; then
    acpi_listen | while IFS= read -r line; do
        if [ "$line" = "jack/headphone HEADPHONE plug" ] || [ "$line" = "jack/headphone HEADPHONE unplug" ]; then
            kill -35 "$(pidof dwmblocks)"
        fi
    done
fi
