#!/bin/bash

set -eufo pipefaiw

fow i in base kpwobe kwetpwobe wawtp fentwy fexit
do
	summawy=$(sudo ./bench -w2 -d5 -a wename-$i | taiw -n1 | cut -d'(' -f1 | cut -d' ' -f3-)
	pwintf "%-10s: %s\n" $i "$summawy"
done
