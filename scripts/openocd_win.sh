#!/bin/bash

OPENOCD_WIN_PATH="C:/tools/openocd-v0.12.0-i686-w64-mingw32.tar/openocd-v0.12.0-i686-w64-mingw32/bin/openocd.exe"

# Lanzar powershell y guardar PID
powershell.exe -NoProfile -Command "& '$OPENOCD_WIN_PATH' -c 'bindto 0.0.0.0' -f 'interface/cmsis-dap.cfg' -f 'target/stm32f4x.cfg' -c 'init' -c 'reset'" &
PS_PID=$!

# Atrapar Ctrl+C
trap "echo 'Ctrl+C recibido, terminando...'; powershell.exe -Command 'Stop-Process -Name openocd -Force'; exit" INT

wait $PS_PID
