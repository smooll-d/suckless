#!/usr/bin/env bash

install_block()
{
    echo "Removing old $1..."
    sudo rm -rf /usr/local/bin/$1

	echo "Installing $1..."
	sudo cp ./$1.sh /usr/local/bin/$1

	echo "Adding execute permissions to $1..."
	sudo chmod +x /usr/local/bin/$1

    echo
}

echo -e "Installing blocks...\n"

for block in $(ls | grep -Eiv 'install.sh' | sed 's/\.sh//g'); do
    install_block ${block}
done
