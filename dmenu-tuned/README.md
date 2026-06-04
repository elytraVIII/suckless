# dmenu-tuned

A suckless-style dynamic `dmenu` interface in C for managing and switching power profiles with the `tuned` daemon.

It queries active and available power profiles directly from `tuned-adm`, displays them using `dmenu` with their descriptions aligned neatly, and applies the selected profile.

## Features

- **Dynamic Profile Discovery (Default):** At runtime, queries `tuned-adm list` to discover all installed power profiles along with their official descriptions.
- **Active Profile Highlighting:** Automatically flags the current active profile with an asterisk (`*`) at the beginning of the list.
- **Static Profile List (Optional):** Can be configured in `config.h` to display a hardcoded list of profiles for speed/minimalism, while still dynamically flagging the active one.
- **Clean Selection Parsing:** Automatically parses the selection from dmenu and invokes `tuned-adm profile <name>`.
- **Aesthetic Customization:** Built to match the typography and colors of your DWM/Tokyo Night theme (easily customized via `config.h`).

## Requirements

- `tuned` (Dynamic System Tuning Daemon, providing the `tuned-adm` command)
- `dmenu` (Suckless dynamic menu)
- C compiler (e.g. `gcc`, `clang`, or `tcc`)
- GNU Make

## Installation

```bash
make
sudo make install
```

By default, `dmenu-tuned` will be installed to `/usr/local/bin`.

## Configuration

The configuration of `dmenu-tuned` is done by creating and customizing `config.h`. You can copy `config.def.h` to `config.h` or just run `make` which does it automatically if `config.h` is missing.

Key settings in `config.def.h`:

- `dmenu_cmd`: The array of arguments passed to launch `dmenu`. You can configure colors, fonts, prompt, positional arguments, etc.
- `dynamic_profiles`: Set to `1` (default) to dynamically fetch profiles and descriptions from `tuned-adm`. Set to `0` to use the static list defined in `static_profiles`.
- `static_profiles`: The list of fallback profiles if dynamic profile detection is disabled.
