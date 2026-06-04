# OS Configuration (Suckless Tools & Scripts)

This repository contains custom builds of various suckless tools and system utility scripts.

## Contents

- **[dwm](dwm/)**: Dynamic Window Manager
  - Upstream: `https://git.suckless.org/dwm`
  - Customizations: Tokyo Night theme, Iosevka Nerd Font, custom window handling rules.
- **[dmenu](dmenu/)**: Dynamic Menu
  - Upstream: `https://git.suckless.org/dmenu`
  - Customizations: Font sizes, Tokyo Night colors.
- **[slstatus](slstatus/)**: Status Monitor for dwm
  - Upstream: `https://git.suckless.org/slstatus`
  - Customizations: CPU, RAM, Volume, and Date/Time formatting.
- **[slock](slock/)**: Screen Locker
  - Upstream: `https://git.suckless.org/slock`
  - Customizations: Tokyo Night colors, User/Group dropping, Ctrl-U password clearing.
- **[dmenu-powermenu](dmenu-powermenu/)**: Custom power menu script.

## Setup and Installation

To compile and install any of these tools:

```bash
cd <tool-directory>
sudo make clean install
```
