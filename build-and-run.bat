@echo off
:: Step 1: Set up the Visual Studio environment (Example for VS 2022 Community)
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

:: Step 2: Build the project
msbuild raylib-template.sln /p:configuration=Release /p:platform=x64

:: Step 3: Run the program if the build succeeded
if %ERRORLEVEL% EQU 0 (
    echo.
    echo --- Running Program ---
    "x64\Release\node-editor.exe"
) else (
    echo Build failed.
)
pause