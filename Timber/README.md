# Timber
Chop wood as fast as you can, moving left and right avoiding branches, until the time runs out!!

## Requirements
- C++
- SFML (x32 version)

## Install Game
- Using the terminal, navigate to a local directory that you want to clone this game directory into.
- Clone the repository by following these instructions [instruction](https://help.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository).

### building in Visual Studio
First and foremost you have to install the [SFML graphics library](https://www.sfml-dev.org/). 

Detailed steps can be found [here](https://www.sfml-dev.org/tutorials/2.5/#getting-started).

After opening the project, go to **"Project -> Properties..."**:
- Select **"All configurations"** in **"Configuration"** section;
- In **"C/C++ -> General -> Additional include directories"** section append the "include" directory of SFML library;
- In **"Linker -> General -> Additional library directories"** section append the "lib" directory of SFML library;
- Select **Debug** in **Configuration** section;
- At the beginning of the **"Linker -> Input -> Additional dependencies"** section append the string:
```bash
sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-network-d.lib;sfml-audio-d.lib;
```

## Hotkeys
- `Esc` Exit the game
- `Enter` Start the game
- `Right arrow` / `Left arrow` Chop a piece of wood from the tree from the respective side

## Screenshots

<div style="display: flex; align-items: flex-start;">
  <img src="./Timber/Screenshots/screenshot1.png" height="200">
  <img src="./Screenshots/screenshot2.png" height="200">
  <img src="./Screenshots/screenshot3.png" height="200">
</div>

## Demo for Windows
You can find an executable for windows inside the Debug directory. Have fun!
