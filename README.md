# Multithreading Socket Server & Client using pthread
The program is compatible with macOS Mojave and Ubuntu 18.04 LTS. You may also be able to open the project directly with CLion since it was firstly created with CLion before migrating the Ubuntu.

## Link & Compile
Both for socket server and socket client, cd to their respective root directories. Then running the following command.
```bash
$ make
```
In case you already have the *.o and the executable programs in the directory and you want to remake the program. You can run the following command before make.
```bash
$ make clean
```

## Run the server
In the server directory,
```bash
$ ./socket_server
```
## Run the client
In the client directory
```bash
$ ./socket_client
```

## Caution
Do not force quit a client using Ctrl+C inside the terminal, since it will cause the server unable to remove the accidently quitted client form the client list.
