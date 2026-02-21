# Finding Keys
A 2-player co-op puzzle game built in Unreal Engine 5.5. Players coordinate on pressure plates and moving platforms to collect keys and reach the exit.<br>
Playable over LAN and Steam.

## About
Built on a UE5.2 multiplayer course, independently extended with LAN and Steam networking via a custom GameInstanceSubsystem with Steam Sockets integration.

## Multiplayer Architecture
Session Management is handled by a standalone GameInstanceSubsystem written in C++.<br>
See: [ue5.5-multiplayer-subsystem](https://github.com/yakshG/ue5.5-multiplayer-subsystem)

## Requirements
- Unreal Engine 5.5
- Visual Studio / Rider
- Steam (for Steam sessions)

## Status
In development. Not yet released.
