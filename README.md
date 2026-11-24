# Console Racing Game

A local two-player racing game made with C++17 and SFML 3. Race around the track, pass all four checkpoints in order, and complete three laps. Each player starts with three lives. Driving off the track costs a life and returns the car to its last safe position.

The game includes a main menu, car selection, saved race records, and a **Back to Menu** button during a race. PNG images and fonts are in `assets/`. The garage background and music are in the project root. Run the game with the project root as the working directory so it can find these files.

## Requirements

- Windows 10 or 11, 64-bit
- Visual Studio with **Desktop development with C++** and a Windows SDK
- CMake 3.28 or newer
- Git for Windows
- vcpkg

The project uses SFML 3 Graphics and Audio. The dependencies are listed in `vcpkg.json`; CMake installs them through vcpkg when you configure the project.

## Build and run on Windows

### 1. Install vcpkg

If vcpkg is not already installed, open **Developer PowerShell for Visual Studio** and run these commands once:

```powershell
$vcpkgRoot = "$env:USERPROFILE\source\vcpkg"
git clone https://github.com/microsoft/vcpkg.git "$vcpkgRoot"
& "$vcpkgRoot\bootstrap-vcpkg.bat"
```

If vcpkg is already installed, set `$vcpkgRoot` below to its existing folder.

### 2. Configure and build the game

Open Developer PowerShell for Visual Studio in the repository folder, then run:

```powershell
$repoFolder = (Get-Location).Path
$vcpkgRoot = "$env:USERPROFILE\source\vcpkg"

cmake -S "$repoFolder" -B "$repoFolder\build" `
  -DCMAKE_TOOLCHAIN_FILE="$vcpkgRoot\scripts\buildsystems\vcpkg.cmake" `
  -DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build "$repoFolder\build" --config Release
```

If vcpkg is installed in another location, change `$vcpkgRoot` to that folder.

### 3. Run the game

Run it from the repository folder so the relative image, font, and music paths work:

```powershell
Set-Location -LiteralPath $repoFolder
& ".\build\Release\game.exe"
```

The first configuration may take a few minutes while vcpkg installs SFML and its dependencies. Race results are saved in `scores.txt`.

## Build and run on macOS

Install CMake and SFML 3 with Homebrew. From the project folder, run:

```sh
brew install cmake sfml
cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix sfml)"
cmake --build build --config Release
./build/game
```

## Build and run on Linux

Install CMake 3.28 or newer, a C++17 compiler, and the SFML 3 Graphics and Audio development libraries. From the project folder, run:

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

- `main.cpp` starts the game.
- `projectmenu.cpp` and `projectmenu.h` provide the main menu and records screen.
- `CarSelection.cpp` provides the car selection screen.
- `Car.cpp` and `Car.h` handle car controls and movement.
- `Game.cpp` and `Game.h` run the race, checkpoints, laps, timer, and HUD.
- `checkpoint.cpp` and `checkpoint.h` provide checkpoint detection.
- `Scores.h` and `scores.txt` handle saved race records.
- `CMakeLists.txt` and `vcpkg.json` configure the build and dependencies.
- `assets/` contains the PNG images and TTF fonts.
- `car-selection-garage.jpg` is the garage background.
- `menu_sound.mp3` is the menu music.

Build output such as the `build` folder and `game.exe` is generated locally and does not need to be committed.
