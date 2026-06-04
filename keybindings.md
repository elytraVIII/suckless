# DWM Keybindings Reference

This document lists the configured keybindings for the custom **dwm (Dynamic Window Manager)** build in this repository.

*   **Modifier Key (`MODKEY`):** `Super` (Windows / Command key)

---

## 🚀 Applications & Launchers

| Keybinding | Action | Description |
| :--- | :--- | :--- |
| `Super + Return` | Launch Terminal | Opens `alacritty` |
| `Super + r` | Run Launcher | Opens `dmenu` for launching commands |
| `Super + b` | Open Browser | Launches `zen-browser` |
| `Super + n` | Open Text Editor | Launches `neovim` inside `alacritty` |
| `Super + y` | File Manager | Launches `yazi` inside `alacritty` |
| `Super + v` | Vacuum Script | Runs `startvacuumtube` |
| `Super + Ctrl + b` | Bluetooth Manager | Launches `bluetui` inside `alacritty` |
| `Super + p` | Power Profile Switcher | Launches `dmenu-tuned` |
| `Super + Shift + Escape` | Power Menu | Launches `dmenu-powermenu` |

---

## 🪟 Window Management & Stack Navigation

| Keybinding | Action | Description |
| :--- | :--- | :--- |
| `Super + j` | Focus Next | Move focus to the next window in the stack |
| `Super + k` | Focus Previous | Move focus to the previous window in the stack |
| `Super + Return` | Zoom / Master | Cycle the focused window to become the master (or swap back) |
| `Super + q` | Close Window | Terminate/kill the currently active window |
| `Super + Tab` | Previous Tag | Toggle view to the previously active tag/workspace |

---

## 📐 Layout & Workspace Adjustments

| Keybinding | Action | Description |
| :--- | :--- | :--- |
| `Super + h` | Shrink Master | Decrease the width of the master window area |
| `Super + l` | Expand Master | Increase the width of the master window area |
| `Super + i` | Inc Master | Increase the number of windows allowed in the master area |
| `Super + d` | Dec Master | Decrease the number of windows allowed in the master area |
| `Super + Shift + Space` | Toggle Float | Toggle the active window between tiled and floating states |
| `Super + Shift + b` | Toggle Bar | Toggle the visibility of the top status bar |

### Layout Modes
*   `Super + t`: Set layout to **Tiled** (`|| Mode: []= ||`)
*   `Super + f`: Set layout to **Floating** (`|| Mode: ><> ||`)
*   `Super + m`: Set layout to **Monocle** (`|| Mode: [M] ||`)
*   `Super + Space`: Cycle layout back to the previous layout state

---

## 📁 Workspaces (Tags)

There are 9 tags (`I` through `IX`).

| Keybinding | Action | Description |
| :--- | :--- | :--- |
| `Super + [1-9]` | View Tag | Switch view to workspace `[1-9]` |
| `Super + Shift + [1-9]` | Move to Tag | Move the focused window to workspace `[1-9]` |
| `Super + Ctrl + [1-9]` | Toggle Tag View | Toggle view of workspace `[1-9]` overlay |
| `Super + Ctrl + Shift + [1-9]` | Toggle Window Tag | Toggle workspace `[1-9]` assignment on focused window |
| `Super + 0` | View All | View all windows on all tags simultaneously |
| `Super + Shift + 0` | Pin to All | Show focused window on all tags (pin) |

---

## 🔊 Audio & Media Controls

| Keybinding | Action | Command |
| :--- | :--- | :--- |
| `Super + F12` | Raise Volume | `wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+` |
| `Super + F11` | Lower Volume | `wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-` |
| `Super + F10` | Toggle Mute | `wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle` |

---

## 📸 Screenshots

Takes screenshots, saves them to `~/Pictures/Screenshots/`, and copies them to the system clipboard. (Requires `maim`, `slop`, and `xclip` to be installed).

| Keybinding | Action | Description |
| :--- | :--- | :--- |
| `Print` | Full Screenshot | Captures the entire screen |
| `Shift + Print` | Region Screenshot | Interactively select a region or window to capture |

---

## 💻 Monitor Management

For multi-monitor setups:

| Keybinding | Action | Description |
| :--- | :--- | :--- |
| `Super + ,` (Comma) | Focus Prev Monitor | Shift focus to the previous monitor |
| `Super + .` (Period) | Focus Next Monitor | Shift focus to the next monitor |
| `Super + Shift + ,` | Move Prev Monitor | Move the active window to the previous monitor |
| `Super + Shift + .` | Move Next Monitor | Move the active window to the next monitor |

---

## 🔒 Session & DWM Control

| Keybinding | Action | Description |
| :--- | :--- | :--- |
| `Super + Shift + c` | Exit DWM | Exit the window manager session cleanly |
| `Super + Shift + Escape` | Power Menu | Shutdown, Reboot, Lock screen options |
| `Super + p` | Power Profiles | Select system performance profile (tuned) |

---

## 🖱️ Mouse Bindings

With the cursor over the window:
*   `Super + Left Click`: Drag to move a floating window.
*   `Super + Middle Click`: Toggle floating/tiled state on the window.
*   `Super + Right Click`: Drag to resize a floating window.

With the cursor over the status bar/tags:
*   `Left Click` on Tag: Switch to that tag.
*   `Right Click` on Tag: Toggle view of that tag.
*   `Left Click` on Layout indicator: Toggle layout modes.
*   `Right Click` on Layout indicator: Set monocle layout.
*   `Middle Click` on Status Text: Spawn terminal.
