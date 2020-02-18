#!/bin/bash
input_flag=0

if [ $1 = "leak-check" ]
then
    input_flag=1
    valgrind --leak-check=yes ./test_main $2 $3
fi

if [ $1 = "leak-check-no-path" ]
then
    input_flag=1
    valgrind --leak-check=yes ./test_main $2
fi

if [ $1 = "run" ]
then
    input_flag=1
    ./test_main $2 $3
fi

if [ $1 = "run-gdb" ]
then
    input_flag=1
    gdb ./test_main
fi

if [ $1 = "help" ]
then 
    input_flag=1
    echo "possible arguments are: ru, leak-check, leak-check-no-path, run-gdb."
fi

if [ $input_flag = 0 ]
then 
    echo "possible arguments are: run, leak-check-no-path and leak-check."
fi