# Timber
The Timberman 2D game clone, which is based on ideas and concepts from [*"Beginning C++ Game Programming" by John Horton*](https://www.packtpub.com/product/beginning-c-game-programming-second-edition/9781838648572).

## Requirements
- C++14
- SFML (x32 version)

## Install Game
- Open Terminal and change the current working directory to the location where you want the cloned directory to be made.
- Download the repository using the [instruction](https://help.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository).

### How to build in Visual Studio
Before this project will work you'll need to install the [SFML graphics library](https://www.sfml-dev.org/). 

Steps can be found [here](https://www.sfml-dev.org/tutorials/2.5/#getting-started).

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
- `Esc` for exit from the game
- `Enter` for start the game
- `Right arrow` / `Left arrow` for making a cut of a tree from an appropriate side

## Screenshots

<div style="display: flex; align-items: flex-start;">
  <img src="./screenshots/screenshot1.png" height="200">
  <img src="./screenshots/screenshot2.png" height="200">
  <img src="./screenshots/screenshot3.png" height="200">
</div>

## Demo for Windows
Once downloaded find and just run the included **Timber.exe** file to play. Enjoy!

## Things to do

-   [x] Add more trees to background
-   [ ] Improve the visability of the HUD text
-   [ ] Make the cloud code more efficient
