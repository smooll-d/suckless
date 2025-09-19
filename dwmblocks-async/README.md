# [dwmblocks-async](https://github.com/UtkarshVerma/dwmblocks-async)
<p align="center">
    <img src="../assets/dwmblocks_current_configuration.png" alt="dwmblocks Showcase">
</p>

## Dependencies
- checkupdates (displaying how many updates on pacman)
- duf (for displaying disk stuff)
- date (date and time)
- a battery (optional)

## Building and Installation
First, clone the repository:

```bash
$ git clone --depth=1 https://github.com/smooll-d/suckless.git
```

Enter `dwmblocks-async/`:

```bash
$ cd suckless/dwmblocks-async
```

Build and install:

```bash
$ sudo make clean install
```

Enter `modules/`:

```bash
$ cd modules
```

>[!TIP]
>If you can't run `install.sh`, change its permissions:
>```bash
>$ chmod +x ./install.sh
>```

Install the modules:
```bash
$ sudo ./install.sh
```

## Modules
This is a list of all modules inside `modules/`:

- [dba-battery](blocks/dba-battery.sh) - Displays battery percentage and an icon that changes based on it.
- [dba-date](blocks/dba-date.sh) - Displays the date.
    Left click changes display modes between: full date, day and month, day
    Right click changes date format between:
        day/month/year, month/day/year and year/month/day for full date
        day/month and month/day for day and month display
- [dba-time](blocks/dba-time.sh) - Displays the time with an icon that updates based on the hour.
    Left click changes hour formats between: 24-hour and 12-hour
>[!CAUTION]
>For 12-hour format, you need the appropriate locale enabled, otherwise it will display
>just the hour and minute without `AM/PM`
- [dba-disksize](blocks/dba-disksize.sh) - Displays the `used/total (free)` disk space (disabled by default).
- [dba-updates](blocks/dba-updates.sh) - Displays the amount of current updates (disabled by default, it's been disabled for so long, I don't even know if it works anymore).
- [dba-volume](blocks/dba-volume.sh) - Displays the volume of the default audio device (the icon also changes based on it).
- [dba-volume-listener](blocks/dba-volume-listener.sh) - Uses `acpi_listen` to update the block on headphone plug/unplug events
- [dba-volume-bluetooth-listener](blocks/dba-volume-bluetooth-listener.sh) - Checks for bluetooth headphone connect/disconnect events
>[!CAUTION]
>Listener scripts are not blocks and shouldn't be added to dwmblocks-async's `config.h` file.
>These scripts are run as part of the autostart sequence in dwm.

The modules `dwmblocks-async` displays can be changed inside of `config.h`.
