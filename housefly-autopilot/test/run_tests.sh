#!/bin/bash

gcc -I../include ../src/state_management.c test.c unity.c -o test
./test && rm -rf test
