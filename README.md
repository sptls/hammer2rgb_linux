# Modecom Volcano Hammer 2 RGB for Linux
![alt text](pic.jpg)

This CLI tool is designed to be used with Modecom Volcan Hammer 2 RGB keyboard. It (mostly)replicates what Windows
equivalent is doing; changing effect, color, brightness, speed. \
Also available in [AUR](https://aur.archlinux.org/packages/hammer2rgb) \
or as [DEB package](https://spotless.fun/apt-repo/pool/main/hammer2rgb_1.3-1_amd64.deb):
```
echo "deb [trusted=yes arch=amd64] http://spotless.fun/apt-repo stable main" >> /etc/apt/sources.list
sudo apt update --allow-insecure-repositories
sudo apt install hammer2rgb
```

## Usage
Building:
> ./configure \
> make \
> make install

Use:
> hammer2rgb [EFFECT] ... [COLOR] [SPEED] [BRIGHTNESS]

You always have to specify effect when changing color, speed or brightness.

Eg.
> hammer2rgb fixed_on green



### List of keyboard effects:
>snake \
>neon_stream \
>reaction \
>sine_wave \
>fixed_on \
>respire \
>rainbow \
>flash_away \
>raindrops \
>rainbow_wheel \
>ripples_shining \
>stars_twinkle \
>shadow_disappear
### List of color presets:
>red \
>green \
>blue \
>yellow \
>purple \
>magenta \
>cyan \
>random_color

## TODO
- add "game_mode" effect

## Versions
### 1.3
- added full RGB color change in format of RRGGBB
- effect speed control
- brightness control
### 1.2
- fixed makefile linker problem
### 1.1
- fixed segfault when hammer 2 keyboard is not found
### 1.0
- basic functionality of changing keyboard effect and color preset