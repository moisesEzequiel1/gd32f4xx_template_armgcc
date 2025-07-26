# GD32F4xx ARM GCC Template Project

## Overview
This project is a template for developing firmware targeting the GD32F4xx series microcontrollers using the ARM GCC toolchain. It includes a modular and organized codebase for peripheral drivers, middleware, and application logic designed to accelerate embedded development.

## Project Structure

- **Build/**  
  Contains build artifacts such as ELF, HEX, map files, and object dependencies.

- **cmsis/**  
  CMSIS-Core and device-specific startup files and headers for GD32F4xx.

- **hal/**  
  Hardware Abstraction Layer source and header files for peripherals like ADC, CAN, GPIO, USART, Timer, etc.

- **Source/**  
  Main application source files and modules organized by functionality:  
  - MCU drivers (GPIO, PMU, RCU, etc.)  
  - Middleware components (event dispatcher, input/output managers)  
  - Core application files like `main.cpp`, scheduler, and task manager.

- **Makefile**  
  Build instructions for ARM GCC.

- **scripts/**  
  Utility scripts related to the project (e.g., OpenOCD scripts).

- **Documentation/**  
  (You may want to add this folder later for manuals and datasheets.)

## Features

- Modular peripheral drivers with clear separation between header and source files.
- CMSIS-compliant startup and system files.
- Middleware for event handling and input/output management.
- Build automation using GNU Make targeting ARM GCC.
- Ready-to-use OpenOCD debugging and flashing scripts.

## Getting Started

1. Ensure you have ARM GCC toolchain installed.
2. Build the project using `make`.
3. Flash the binary using OpenOCD and your preferred debugger.
4. Customize and extend the project based on your application needs.

## License

No license yet.

