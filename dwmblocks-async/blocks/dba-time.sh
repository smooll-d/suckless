#!/bin/bash

change_display()
{
    case ${display_mode} in
        0) time=$(date +'%H:%M')
           ;;
        1) time=$(date +'%I:%M %p')
           ;;
        2|*) display_mode=0
           echo ${display_mode} > "${display_mode_file}"
           change_display
           ;;
    esac
}

print_date()
{
    echo ^b#85dc85^^c#080808^" $1 "^d^^c#85dc85^ "${time}" ^d^
}

main()
{
    dba_directory="${HOME}/.local/state/dba/time"

    display_mode_file="${dba_directory}/display_mode"

    hour=$(date +'%H')

    if [[ ! -d "${dba_directory}" ]]; then
        mkdir -p "${dba_directory}"
    fi

    if [[ -f ${display_mode_file} ]]; then
        declare -i display_mode=$(< "${display_mode_file}")
    else
        declare -i display_mode=0
    fi

    case $BLOCK_BUTTON in
        1) display_mode+=1
           echo ${display_mode} > "${display_mode_file}"
           ;;
        2|3) display_mode=0
           echo ${display_mode} > "${display_mode_file}"
           ;;
    esac

    change_display

    case "$hour" in
        00|12) print_date 󱑊
        ;;
        01|13) print_date 󱐿
        ;;
        02|14) print_date 󱑀
        ;;
        03|15) print_date 󱑁
        ;;
        04|16) print_date 󱑂
        ;;
        05|17) print_date 󱑃
        ;;
        06|18) print_date 󱑄
        ;;
        07|19) print_date 󱑅
        ;;
        08|20) print_date 󱑆
        ;;
        09|21) print_date 󱑇
        ;;
        10|22) print_date 󱑈
        ;;
        11|23) print_date 󱑉
        ;;
        *) echo "err"
    esac
}

main
