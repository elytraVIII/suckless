# dmenu-powermenu

`dmenu-powermenu` is a suckless-style power menu wrapper written in C. It feeds a set of configured power action labels to `dmenu`, reads the selected option, prompts for confirmation using `dmenu` if configured, and executes the corresponding shell command using `/bin/sh`.

It requires no external dependencies (like X11 or Xft) of its own, because it relies on standard IPC pipes to invoke `dmenu`.

## Requirements

* `dmenu` (runtime dependency, configured in `config.h`)

## Installation

Edit `config.mk` if you need to match your system paths. Then run the following to build and install:

```bash
make
sudo make install
```

This installs the binary to `/usr/local/bin/dmenu-powermenu` (or your configured prefix).

## Configuration

Following the suckless philosophy, configuration is done at compile-time by modifying `config.h`. If you haven't compiled yet, copy `config.def.h` to `config.h` or let `make` copy it for you:

```bash
cp config.def.h config.h
```

Inside `config.h`, you can configure:

* `dmenu_cmd`: The execution array for launching the main menu.
* `confirm_cmd`: The execution array for launching the confirmation menu.
* `confirm_options`: Custom options for confirmation (e.g. `No`, `Yes`).
* `items`: The array of menu actions containing:
  * Label (displayed in dmenu)
  * Shell command (executed upon selection and confirmation)
  * Confirmation flag (set to `1` to prompt for confirmation, `0` to run immediately)

Example configuration item:

```c
static const PowermenuItem items[] = {
	/* label       command              confirm */
	{ "Lock",      "slock",             0 },
	{ "Suspend",   "systemctl suspend", 0 },
	{ "Logout",    "killall dwm",       1 },
	{ "Reboot",    "systemctl reboot",  1 },
	{ "Shutdown",  "systemctl poweroff",1 },
};
```

After modifying `config.h`, rebuild and reinstall:

```bash
make clean
make
sudo make install
```
