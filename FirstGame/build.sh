#!/bin/bash

warnings="-Wno-writable-strings -Wno-format-security -Wno-deprecated-declarations -Wno-switch"
includes="-I ../includes/"
# Find a fix 
libs="-L ../library/ ./src/Game.cpp"
smfl="-lsfml-graphics -lsfml-window -lsfml-system"

if [[ "$(uname)" == "Darwin" ]]; then
    echo "Running on Mac"
    outputFile=game

    rm -f game_*
    clang++ $includes $libs -g "FirstGame/src/main.cpp" -o $outputFile $warnings $smfl -std=c++17


else
    echo "Not yet implements for your OS"
fi

