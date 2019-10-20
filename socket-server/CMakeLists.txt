cmake_minimum_required(VERSION 3.13)
project(socket_server C)

set(CMAKE_C_STANDARD 99)

add_executable(socket_server main.c Practical.h DieWithMessage.c DieWithMessage.h DieWithMessage.h TCPServerUtility.c TCPServerUtility.h Acceptor.c Acceptor.h)