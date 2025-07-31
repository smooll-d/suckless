#!/usr/bin/env bash

change_format()
{
    if [[ "$1" = "full" ]]; then
        case $format_full in
            0) date=$(date +'%d/%m/%Y')
               ;;
            1) date=$(date +'%m/%d/%Y')
               ;;
            2) date=$(date +'%Y/%m/%d')
               ;;
            3|*) format_full=0
               echo "${format_full}" > "${format_full_file}"
               change_format "full"
               ;;
        esac
    elif [[ "$1" = "month" ]]; then
        case $format_month in
            0) date=$(date +'%d/%m')
               ;;
            1) date=$(date +'%m/%d')
               ;;
            2|*) format_month=0
               echo "${format_month}" > "${format_month_file}"
               change_format "month"
               ;;
        esac
    fi
}

change_display()
{
    case $display_mode in
        0) change_format "full"
           ;;
        1) change_format "month"
           ;;
        2) date=$(date +'%d')
           ;;
        3|*) display_mode=0
           echo "${display_mode}" > "${display_mode_file}"
           change_display
           ;;
    esac
}

main()
{
    dba_directory="${HOME}/.local/state/dba/date"

    display_mode_file="${dba_directory}/display_mode"
    format_full_file="${dba_directory}/format_full"
    format_month_file="${dba_directory}/format_month"

    if [[ ! -d "${dba_directory}" ]]; then
        mkdir -p "${dba_directory}"
    fi

    if [[ -f "${display_mode_file}" ]]; then
        declare -i display_mode=$(< "${display_mode_file}")
    else
        declare -i display_mode=0
    fi

    if [[ -f "${format_full_file}" ]]; then
        declare -i format_full=$(< "${format_full_file}")
    else
        declare -i format_full=0
    fi

    if [[ -f "${format_month_file}" ]]; then
        declare -i format_month=$(< "${format_month_file}")
    else
        declare -i format_month=0
    fi

    case $BLOCK_BUTTON in
        1) display_mode+=1
           echo "${display_mode}" > "${display_mode_file}"
           ;;
        3) format_full+=1
           format_month+=1
           echo "${format_full}" > "${format_full_file}"
           echo "${format_month}" > "${format_month_file}"
           ;;
        2) display_mode=0
           format_full=0
           format_month=0
           echo "${display_mode}" > "${display_mode_file}"
           echo "${format_full}" > "${format_full_file}"
           echo "${format_month}" > "${format_month_file}"
           ;;
    esac

    change_display

    echo ^b#ff5d5d^^c#080808^"  "^d^^c#ff5d5d^ "${date}" ^d^
}

main
