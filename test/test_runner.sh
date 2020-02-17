#!/bin/bash
input_flag=0

if [ $1 = "leak-check" ]
then
    input_flag=1
    valgrind --leak-check=yes ./test_main $2 $3
fi

if [ $1 = "run" ]
then
    input_flag=1
    ./test_main $2 $3
fi

if [ $1 = "help" ]
then 
    input_flag=1
    echo "possible arguments are: run and leak-check."
fi

if [ $input_flag = 0 ]
then 
    echo "possible arguments are: run and leak-check."
fi