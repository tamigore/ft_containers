#!/bin/sh

make ft
./containers > test_ft
make std
./containers > test_std
diff test_ft test_std