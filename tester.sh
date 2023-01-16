#!/bin/sh

make ft
# time ./ft_containers > test_ft
./ft_containers > test_ft.txt

make std
# time ./std_containers > test_std
./std_containers std > test_std.txt

diff -s test_ft.txt test_std.txt