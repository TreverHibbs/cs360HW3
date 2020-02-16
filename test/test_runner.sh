#!/bin/bash

if [ $1 = "leak-check" ]
then
    valgrind --leak-check=yes ./test_main $2 $3
fi

if [ $1 = "run" ]
then
    ./test_main $2 $3
fi