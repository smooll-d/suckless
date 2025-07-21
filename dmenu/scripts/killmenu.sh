#!/usr/bin/env bash

main()
{
	# Take PID, CPU usage, RAM usage and the command name out of "ps aux"
	awk_query='NR > 1 {
		cmd = ""

		for (i = 11; i <= NF; i++) {
			cmd = cmd $i (i < NF ? OFS : "")
		}

		if (length(cmd) > 50) {
			cmd = substr(cmd, 1, 47) "..."
		}

		printf "%-6s %5s%% %5s%% %s\n", $2, $3, $4, cmd
	}'

	# Sort the output by CPU usage from highest to lowest, remove the
	# first two results -- "dmenu" and "ps aux" and pass it off to dmenu
	if command -v dmenu &> /dev/null; then
		response=$(ps aux | awk "${awk_query}" | sort -k2 -nr | dmenu -p "Kill:" -z 50 -l 10 -S)
	elif command -v mew &> /dev/null; then
		response=$(ps aux | awk "${awk_query}" | sort -k2 -nr | mew -p "Kill:" -l 10)
	else
		echo "No launcher available!"
	fi

	# Get the PID of process selected in dmenu
	pid=$(echo "${response}" | awk '{ print int($1) }')

	# Kill the selected process if its PID is greater than 0. We do
	# this check because dmenu outputs 0 if you press escape.
	if [ "${pid}" -gt 0 ]; then
		kill -9 "${pid}"
	fi
}

main
