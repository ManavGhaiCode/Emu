cmake_minimum_required(VERSION "3.14")
project("emu")

add_executable("emu"
    "src/6502.cpp"

    "src/main.cpp"
    "src/log.cpp"
)

target_include_directories("emu" PUBLIC
    "src"
)