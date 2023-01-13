#!/bin/sh

make ft
./ft_containers > test_ft
make std
./std_containers > test_std
diff test_ft test_std