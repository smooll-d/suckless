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

- [dba-battery](modules/dba-battery) - Displays battery percentage and an icon that changes based on it.
- [dba-date](modules/dba-date) - Displays the date (in DD/MM/YYYY format).
- [dba-time](modules/dba-time) - Displays the time with an icon that updates based on the hour.
- [dba-disksize](modules/dba-disksize) - Displays the `used/total (free)` disk space (disabled by default).
- [dba-updates](modules/dba-updates) - Displays the amount of current updates (disabled by default, it's been disabled for so long, I don't even know if it works anymore).

The modules `dwmblocks-async` displays can be changed inside of `config.h`.
