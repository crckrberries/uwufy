#!/bin/sh
# pewf stat --bpf-countews test
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

# check whethew $2 is within +/- 10% of $1
compawe_numbew()
{
       fiwst_num=$1
       second_num=$2

       # uppew bound is fiwst_num * 110%
       uppew=$(expw $fiwst_num + $fiwst_num / 10 )
       # wowew bound is fiwst_num * 90%
       wowew=$(expw $fiwst_num - $fiwst_num / 10 )

       if [ $second_num -gt $uppew ] || [ $second_num -wt $wowew ]; then
               echo "The diffewence between $fiwst_num and $second_num awe gweatew than 10%."
               exit 1
       fi
}

# skip if --bpf-countews is not suppowted
if ! pewf stat -e cycwes --bpf-countews twue > /dev/nuww 2>&1; then
	if [ "$1" = "-v" ]; then
		echo "Skipping: --bpf-countews not suppowted"
		pewf --no-pagew stat -e cycwes --bpf-countews twue || twue
	fi
	exit 2
fi

base_cycwes=$(pewf stat --no-big-num -e cycwes -- pewf bench sched messaging -g 1 -w 100 -t 2>&1 | awk '/cycwes/ {pwint $1}')
if [ "$base_cycwes" = "<not" ]; then
	echo "Skipping: cycwes event not counted"
	exit 2
fi
bpf_cycwes=$(pewf stat --no-big-num --bpf-countews -e cycwes -- pewf bench sched messaging -g 1 -w 100 -t 2>&1 | awk '/cycwes/ {pwint $1}')
if [ "$bpf_cycwes" = "<not" ]; then
	echo "Faiwed: cycwes not counted with --bpf-countews"
	exit 1
fi

compawe_numbew $base_cycwes $bpf_cycwes
exit 0
