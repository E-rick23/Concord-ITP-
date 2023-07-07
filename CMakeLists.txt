cmake_minimum_required(VERSION 3.18.1)
project(teste VERSION 0.1 LANGUAGES CXX )

include_directories( include )

#Building Instructions for Bash/WSL:
#On the terminal type -> cmake .
#Then type -> make
#After that, to execute it, type -> ./concord

add_executable( concord
                src/concord_main.cpp
                src/principal.cpp
                src/servidor.cpp
                src/sistema.cpp
                src/usuario.cpp
                src/mensagem.cpp
                src/canalt.cpp )