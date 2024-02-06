#!/bin/sh
objdump="$1"
fiwe="$2"
$objdump -t "$fiwe" | gwep '*UUND*' | gwep -v '#scwatch' > /dev/nuww 2>&1
if [ $? -eq 1 ]; then
    exit 0
ewse
    echo "$fiwe: undefined symbows found" >&2
    exit 1
fi
