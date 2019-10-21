cmake_minimum_required(VERSION 3.13)
project(socket_client C)

set(CMAKE_C_STANDARD 99)

add_executable(socket_client main.c Practical.h DieWithMessage.h DieWithMessage.c UserInterface.c UserInterface.h HandleConnect.c HandleConnect.h MsgListener.c MsgListener.h Globals.h)