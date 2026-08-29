# Finding Keys
A 2-player online co-op puzzle game built in Unreal Engine 5.5, built to explore what online multiplayer development actually looks like. Two players work together with pressure plates, movable boxes, and moving platforms to collect keys and reach the exit.

Playable over LAN and Steam.

## Features
- Pressure plate puzzles: plates must stay active - releasing one closes the linked door. Triggered by players or moveable boxes.
- Key collection & door logic: a 4-key main door, plus a secondary door requiring 3 plates to be active.
- Custom `GameInstanceSubsystem` in C++ handling session creation, discovery, joining and destruction for both LAN and Steam, with automatic LAN/Steam detection on startup.
- Single level built with [Stylized Egypt](https://www.fab.com/listings/c935ca3e-dbb1-4b7d-a080-65de129c60bd) assets from Fab.

## Multiplayer Architecture
Session Management is handled by a custom `GameInstanceSubsystem` written in C++ (`Source/FindingKeys/MultiplayerSubsystem.h/.cpp`). It is also maintained as a standalone, reusable component: [ue5.5-multiplayer-subsystem](https://github.com/yakshG/ue5.5-multiplayer-subsystem).

## Requirements
- Unreal Engine 5.5
- Visual Studio 2022 or later version (with "Game development with C++" workload) or Rider
- Steam Client (must be logged in and running in the background to use Spacewar App ID 480)
- Git LFS

## Setup
1. `git clone https://github.com/yakshG/finding-keys-ue5.git`
2. `cd finding-keys-ue5`
3. `git lfs pull`
4. Right-click `FindingKeys.uproject` and select **Generate Visual Studio project files**.
5. Open `FindingKeys.sln` in your IDE and build the solution (Development Editor configuration).
6. Launch the project from your IDE or double-click the `.uproject` file.

## Post Mortem
Steam session joining consistently failed silently in UE5.5 - sessions were found correctly, but the join call succeeded internally without the client ever travelling. Fixed by switching to the Steam Sockets plugin (`SteamSocketsNetDriver`) and adding the required session settings during discovery, which the client needs to resolve the connection string.

## Status
Release on [itch.io](https://billawatts.itch.io/finding-keys).

## License
This project is licensed under the MIT License - see the LICENSE file for details.
