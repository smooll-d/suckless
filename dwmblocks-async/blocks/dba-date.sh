#!/usr/bin/env bash

#TODO: Add date format change on right click

change_display()
{
    case $display_mode in
        0) date=$(date +'%d/%m/%Y')
           ;;
        1) date=$(date +'%d/%m')
           ;;
        2) date=$(date +'%d')
           ;;
        3|*) display_mode=0
           echo ${display_mode} > ${display_mode_file}
           change_display
           ;;
    esac
}

display_mode_file="${HOME}/.local/state/dba_date_display_mode"

if [[ -f ${display_mode_file} ]]; then
    declare -i display_mode=$(< "${display_mode_file}")
else
    declare -i display_mode=0
fi

case $BLOCK_BUTTON in
    1) display_mode+=1
       echo ${display_mode} > ${display_mode_file}
       ;;
    2|3) display_mode=0
       echo ${display_mode} > ${display_mode_file}
       ;;
esac

change_display

echo ^b#ff5d5d^^c#080808^"  "^d^^c#ff5d5d^ ${date} ^d^
