#!/usr/bin/env bash

uptime="$(uptime -p | sed -e 's/up //g')"

goodbye_prompt="Goodbye $(whoami) | Uptime: ${uptime}"
confirmation_prompt="Are you sure?"

# Powermenu Options
shutdown=" Shutdown"
reboot=" Reboot"
lock=" Lock"
suspend=" Suspend"
logout=" Logout"
yes=" Yes"
no=" No"

confirmation()
{
	if command -v dmenu &> /dev/null; then
		confirmation_response=$(echo -e "${yes}\n${no}" | dmenu -S -noi -p "${confirmation_prompt}" -z ${#confirmation_prompt})
	elif command -v mew &> /dev/null; then
		confirmation_response=$(echo -e "${yes}\n${no}" | mew -p "${confirmation_prompt}")
	else
		echo "No launcher available."
	fi

	case "${confirmation_response}" in
		"${yes}")
			return 0
			;;
		"${no}"|*)
			return 1
			;;
	esac
}

if command -v dmenu; then
	goodbye_response=$(echo -e "${shutdown}\n${reboot}\n${lock}\n${suspend}\n${logout}" | dmenu -S -noi -p "${goodbye_prompt}" -z ${#goodbye_prompt})
elif command -v mew; then
	goodbye_response=$(echo -e "${shutdown}\n${reboot}\n${lock}\n${suspend}\n${logout}" | mew -p "${goodbye_prompt}")
else
	echo "No launcher available."
fi

# If any of the commands below doesn't work, change them to the ones that work for you.
# For example with logging out, if you're not using dmenu, set the appropriate command for logging out.
case "${goodbye_response}" in
	"${shutdown}")
		if confirmation; then
			systemctl poweroff
		fi
		;;
	"${reboot}")
		if confirmation; then
			systemctl reboot
		fi
		;;
	"${lock}")
		if confirmation; then
			betterlockscreen -l blur 0.5 &
		fi
		;;
	"${suspend}")
		if confirmation; then
			betterlockscreen -l blur 0.5 &
			sleep 1
			systemctl suspend
		fi
		;;
	"${logout}")
		if confirmation; then
			killall dwm
		fi
		;;
	*)
		exit 0
		;;
esac
