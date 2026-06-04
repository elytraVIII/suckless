# dmenu-screenshot

`dmenu-screenshot` is a suckless-style C wrapper for taking screenshots using `dmenu` and `maim` on X11. It provides a keyboard-driven dropdown menu to choose between capturing the full screen, the active window, the active monitor, or a selected region.

## 🛠️ Dependencies

To build and run `dmenu-screenshot`, ensure you have the following dependencies:

### Build Dependencies
- **gcc** or **clang** (C compiler)
- **make** (build automation tool)
- **libX11** development headers (e.g. `libx11-dev` or `libX11`)
- **libXinerama** development headers (e.g. `libxinerama-dev` or `libXinerama`)

### Runtime Dependencies
- **dmenu** (for displaying the menu selector)
- **maim** (the engine used to take screenshots)
- **xclip** (for copying the captured screenshot to the system clipboard)

## 🚀 Installation

To compile and install `dmenu-screenshot` to `/usr/local/bin`:

```bash
cd dmenu-screenshot
make
sudo make install
```

## 📂 Configuration

You can customize the prompt, font, colors, and options by editing `config.h` (which is copied from `config.def.h` on first build) and recompiling.

## 🖱️ Usage Options

Upon running, `dmenu-screenshot` prompts you to choose one of the following modes:
1. **Fullscreen**: Captures the entire desktop spanning all monitors.
2. **Active Window**: Dynamically detects and captures the currently active/focused window.
3. **Active Monitor**: Dynamically detects the monitor containing the mouse cursor and captures only that monitor.
4. **Selection**: Switches to interactive selection mode, letting you drag a box or click a window to capture.

All screenshots are saved automatically to `~/Pictures/Screenshots/` with a timestamp, and are simultaneously copied to your system clipboard.
