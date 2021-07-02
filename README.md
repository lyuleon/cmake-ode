## Networked Physics tutorials 
#### Credits to [gafferongames](https://github.com/gafferongames). Sincere thanks to the networked preacher for his incredible contribution on detailed tutorials of designing TCP/UDP based network synchronization techniques.
1. Original project was organized by premake4, this project changes that to cmake
2. include all 3rd libraries as source
3. only available on Linux right now

## How to build
0. make sure you are on linux platform and have X11 and GLEW installed
1. download src or zip tp certain directory
2. mkdir build 
3. cd build;cmake..;cmake --build .


## How to use demo
1. ./build/bin/Client +load cubes 			-- run the cubes demo in single player.
2. ./build/bin/Client +load lockstep 		-- run the deterministic lockstep demo.
3. ./build/bin/Client +load snapshot 		-- run the snapshot interpolation demo.
4. ./build/bin/Client +load compression 	-- run the compression demo.
5. ./build/bin/Client +load delta 			-- run the delta compression demo.
6. ./build/bin/Client +load sync 			-- run the state synchronization demo.

## Contols
1. arrow keys -- strafe
2. space      -- jump/hover
3. z          -- katamari

## Within each demo you can pick different modes pressing the 1,2,3,4,5 keys:
### In the lockstep demo:
1. Deterministic mode (default)
2. Non-deterministic mode
3. TCP 100ms round-trip, 1% packet loss
4. TCP 200ms round-trip, 2% packet loss
5. TCP 250ms round-trip, 5% packet loss
6. UDP 250ms round-trip, 25% packet loss

### In the snapshot demo:
1. Snapshots at 60 packets per-second (default)
2. Snapshots at 60 packets per-second (with jitter)
3. Snapshots at 10 packets per-second
4. Linear interpolation at 10 packets per-second
5. Hermite interpolation at 10 packets per-second

### In the compression demo:
1. Uncompressed (default)
2. Compress orientation
3. Compress sinear velocity
4. At rest flag
5. Don't send velocity at all
6. Compress position
        
### In the delta demo:
1. Not changed bit (default)
2. Changed index
3. Relative index
4. Relative position
5. Relative orientation

### In the state synchronization sync demo:
1. Input and State (default)
2. Quantize
3. Smoothing


## TODO List
1. cmake editing to export Mac and Win32 platforms