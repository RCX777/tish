#!/bin/bash

# build shell
make

# move executable to /usr/bin
printf "\e[1;32m==>\e[0m"
printf "\e[1;34m Installing to /usr/bin ...\e[0m\n"
printf "\e[1;34m  ->\e[0m "
printf "sudo mv ./bin/run /usr/bin/tish\n\n"
sudo mv ./bin/run /usr/bin/tish

# clean the intermediary files
make clean

# Done!
printf "\e[1;32m==>\e[0m \e[1;36mDone!\e[0m\n\n"
