#!/bin/bash

make clean
make 
./tictactoe > output.txt
less output.txt
