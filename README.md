# Console Racing System

A local two-player racing game made with C++17 and SFML 3. Race around the track, pass all four checkpoints in order, and complete three laps. Each player starts with three lives. Driving off the track costs a life and returns the car to its last safe position.

The game includes a main menu, car selection, saved race records, and a **Back to Menu** button during a race. The source code, headers, images, fonts, music, and score file are kept together in the project root. Start the game with this folder as the working directory so it can find its files.

## Requirements

- Windows 10 or 11, 64-bit
- Visual Studio with **Desktop development with C++** and a Windows SDK
- CMake 3.28 or newer
- Git for Windows
- vcpkg

The project uses SFML 3 Graphics and Audio. Its dependencies are listed in `vcpkg.json`.

## Build and run on Windows

Open **Developer PowerShell for Visual Studio**. Set the two paths below to your project folder and vcpkg installation, then run the commands:

```powershell
$repoFolder = "C:\path\to\Console-Racing_System"
$vcpkgRoot = "C:\path\to\vcpkg"

cmake -S $repoFolder -B "$repoFolder\build" `
  -DCMAKE_TOOLCHAIN_FILE="$vcpkgRoot\scripts\buildsystems\vcpkg.cmake" `
  -DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build "$repoFolder\build" --config Release
Set-Location $repoFolder
.\build\Release\game.exe
```

The first build may take a few minutes while vcpkg downloads and builds SFML. Race results are saved in `scores.txt`.

## Build and run on macOS

Install CMake and SFML 3 with Homebrew, then run these commands from the project folder:

```sh
brew install cmake sfml
cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix sfml)"
cmake --build build --config Release
./build/game
```

## Build and run on Linux

Install CMake 3.28 or newer, a C++17 compiler, and SFML 3 development libraries. From the project folder, run:

```sh
cmake -S . -B build
cmake --build build --config Release
./build/game
```

## Controls

| Action | Player 1 | Player 2 |
| --- | --- | --- |
| Accelerate | W | Up arrow |
| Brake | S | Down arrow |
| Steer left | A | Left arrow |
| Steer right | D | Right arrow |
| Return to menu during a race | Click **BACK TO MENU** | Click **BACK TO MENU** |
| Return to menu during a race | Escape | Escape |

## Project files

All project files are in this folder’s root; there are no `assets`, `data`, `include`, or `src` subfolders.

- `main.cpp` starts the game.
- `projectmenu.cpp` and `projectmenu.h` provide the main menu and records screen.
- `CarSelection.cpp` provides the car selection screen.
- `Car.cpp` and `Car.h` handle car controls and movement.
- `Game.cpp` and `Game.h` run the race, checkpoints, laps, timer, and HUD.
- `checkpoint.cpp` and `checkpoint.h` provide checkpoint detection.
- `Scores.h` and `scores.txt` handle saved race records.
- `CMakeLists.txt` and `vcpkg.json` configure the build and dependencies.
- Root-level PNG, JPG, TTF, and MP3 files provide the game’s images, fonts, and music.

Build output such as the `build` folder and `game.exe` is generated locally and does not need to be committed.
