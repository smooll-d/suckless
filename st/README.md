# st
<p align="center">
    <img src="../assets/cut st showcase.png" alt="st Showcase">
</p>

## Dependencies
>[!CAUTION]
>Every package name is the same as on Arch Linux so, you'll have to find your distro's equivalent. It's what I use personally, so deal with it.

- base-devel
- libx11
- libxft
- fontconfig
- ncurses
- ttf-jetbrains-mono-nerd

## Installation
>[!CAUTION]
>These installation guides assume you're in the same directory as the `README.md` file you're reading right now.

```bash
$ cd st/
$ sudo make clean install
```

There shouldn't be any errors, unless you don't have some st dependency.

## Patches
Here's a list of patches that reside in the `patches/` directory and an excerpt from st's patches website describing what they do (I don't remember if all of them are applied):

>[!NOTE]
>`glyph wide support` is not on the list because I implemented it myself. I didn't know it existed as a patch when trying to fix cutoff icons.

- anysize - This patch allows st to resize to any pixel size, makes the inner border size dynamic, and centers the content of the terminal so that the left/right and top/bottom borders are balanced. With this patch, st on a tiling WM will always fill the entire space allocated to it.
- blinking_cursor - This patch allows the use of a blinking cursor. When drawing is triggered, the cursor does not blink.
- bold-is-not-bright - In st, bold text is rendered with a bold font in the bright variant of the current color. This patch makes bold text rendered simply as bold, leaving the color unaffected.
- boxdraw - Custom rendering of lines/blocks/braille characters for gapless alignment.
- clipboard - This trivial patch sets CLIPBOARD on selection, the same as your browser.
- colorschemes - This patch adds multiple color schemes and lets you change them without having to restart st (plus a custom tokyo-night colorscheme).
- desktopentry - Creates a desktop-entry for st. This enables to find st in a graphical menu and to display it with a nice icon.
- dynamic-cursor-color - Swaps the colors of your cursor and the character you're currently on (much like alacritty). Some say the effect is very appealing:) (it is:)
- expected-anysize - This variant will only add the border paddings to the bottom and the right of the window, which is usually expected as english is left to right and the terminal output comes from the top.
- hidecursor - Hide the X cursor whenever a key is pressed and show it back when the mouse is moved in the terminal window.
- scrollback-mouse - Allows scrolling using Shift+MouseWheel.
- scrollback-mouse-altscreen - Allows scrollback using mouse wheel only when not in MODE_ALTSCREEN. For example the content is being scrolled instead of the scrollback buffer in less. Consequently the Shift modifier for scrolling is not needed anymore.
- scrollback-mouse-increment - Allows changing how fast the mouse scrolls.
- scrollback-ringbuffer - Scroll back through terminal output using Shift+{PageUp, PageDown}. Uses a ring buffer for more efficient scrolling.
- title_parsing_fix - This patch "fixes" window titles getting truncated after the first ';' character.
- undercurl - This patch adds support for special underlines.
- workingdir - This patch allows user to specify the initial path st should use as WD (working directory).
