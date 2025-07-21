#!/usr/bin/env bash

install_script()
{
    echo "Removing old $1..."
    sudo rm -rf /usr/local/bin/$1

	echo "Installing $1..."
	sudo cp ./$1.sh /usr/local/bin/$1

	echo "Adding execute permissions to $1..."
	sudo chmod +x /usr/local/bin/$1

    echo
}

echo -e "Installing scripts...\n"

for script in $(ls | grep -Eiv 'install.sh' | sed 's/\.sh//g'); do
    install_script ${script}
done
