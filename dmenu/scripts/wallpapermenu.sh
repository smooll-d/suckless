#!/usr/bin/env bash

filter='\.(png|jpg)'

declare -A wallpapers

prettify()
{
    if [ -n "$1" ] && [ "$1" = "-r" ]; then
        echo "${@:2}" | sed 's/ /_/g' | sed 's/[^ -_]*/\l&/g' | sed 's/ /\n/g'
    else
        echo "${@:1}" | sed 's/ /\n/g' | sed 's/[^ -_]*/\u&/g' | sed 's/_/ /g'
    fi
}

for file in $(ls "$1" | grep -Ei ${filter} | awk 'NR > 0 { print }'); do
    formatted_name=("$(echo "${file}" | sed -E "s/${filter}//g")")
    filepath=("$1/${file}")

    wallpapers[${formatted_name}]=${filepath}
done

if command -v dmenu &> /dev/null; then
	response=$(prettify "${!wallpapers[@]}" | dmenu -noi -p "Select Wallpaper" -l 10)
elif command -v mew &> /dev/null; then
	response=$(prettify "${!wallpapers[@]}" | mew -p "Select Wallpaper" -l 10)
else
	echo "No launcher available."
fi

if [ -n "$(prettify -r "${response}")" ]; then
	# Change "feh --bg-max" if using a different wallpaper manager.
    feh --bg-max "${wallpapers[$(prettify -r "${response}")]}"
fi
