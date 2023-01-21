#!/bin/sh

make ft
time ./ft_containers > test_ft.txt
# ./ft_containers > test_ft.txt

make std
time ./std_containers std > test_std.txt
# ./std_containers std > test_std.txt

diff -s test_ft.txt test_std.txt