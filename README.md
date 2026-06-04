# OS Configuration (Suckless Tools & Scripts)

This repository contains custom builds of various suckless tools and system utility scripts.

## Contents

- **[dwm](dwm/)**: Dynamic Window Manager
  - Upstream: `https://git.suckless.org/dwm`
  - Customizations: Tokyo Night theme, Iosevka Nerd Font, custom window handling rules.
- **[dmenu](dmenu/)**: Dynamic Menu
  - Upstream: `https://git.suckless.org/dmenu`
  - Customizations: Font sizes, Tokyo Night colors.
- **[dmenu-tuned](dmenu-tuned/)**: Custom power profiles switcher
  - Integrates `tuned-adm` power management profiles directly with a C-based `dmenu` interface.
- **[slstatus](slstatus/)**: Status Monitor for dwm
  - Upstream: `https://git.suckless.org/slstatus`
  - Customizations: CPU, RAM, Volume, and Date/Time formatting.
- **[slock](slock/)**: Screen Locker
  - Upstream: `https://git.suckless.org/slock`
  - Customizations: Tokyo Night colors, User/Group dropping, Ctrl-U password clearing.
- **[dmenu-powermenu](dmenu-powermenu/)**: Custom power menu script.
- **[dmenu-screenshot](dmenu-screenshot/)**: Custom screenshot manager
  - Integrates `maim`, `xclip`, and X11 APIs to capture screenshots (Fullscreen, active window, active monitor, or selection) via a `dmenu` interface.

## ⌨️ Keybindings

A complete reference of all shortcuts and mouse actions is available in [keybindings.md](keybindings.md).

## Setup and Installation

To compile and install any of these tools:

```bash
cd <tool-directory>
sudo make clean install
```
