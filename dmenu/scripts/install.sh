#!/usr/bin/env bash

install_script()
{
	echo "Installing $1..."
	sudo cp ./"$1" /usr/local/bin/

	echo "Adding execute permissions to $1..."
	sudo chmod +x /usr/local/bin/"$1"
}

echo "Installing scripts..."

install_script powermenu
