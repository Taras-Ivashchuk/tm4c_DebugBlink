# DebugBlink — TM4C123GH6PM

A simple program that demonstrates functional debugging.

The led constantly blinks on and off with the 0.1 sec delay.

## Environment
Project is build with Code Compose Studio(Theia) using GNU Arm Toolchain and CMSIS.

## Requirements
- Code Composer Studio (CCS) installed
- GNU Arm Toolchain installed and added to the CCS

## Usage
1. Open the DebugBlink project in CCS.
2. Flash the code to the board.
3. Run -> Debug Project (F5) to start the debug session.
4. Go to the Debug menu and add the time array to the Watch view.
5. Inspect time[1], time[2], time[n] values and verify the delay:
    time[n] * 62.5 / 1000000000 ~ 0.1 s.

## How the timing works
- The MCU runs at 16MHz, so one SysTick period is 1/16MHz = 62.5 ns.
- Time[n] stores the number of ticks between two consecutive LED toggles.
- Total time elapsed in seconds: 
  seconds =  62.5 ns * ticks / 1.000.000.000 ns/sec.
- Time[0] is very small because it captures the execution of the very first
  LED toggle before any delay applied.
