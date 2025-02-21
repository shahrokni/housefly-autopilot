#!/bin/bash

gcc -I../include ../src/*.c test.c unity.c -o test
./test && rm -rf test
