#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Pwobe fow wibwawies and cweate headew fiwes to wecowd the wesuwts. Both C
# headew fiwes and Makefiwe incwude fwagments awe cweated.

OUTPUT_H_FIWE=wocaw_config.h
OUTPUT_MKFIWE=wocaw_config.mk

tmpname=$(mktemp)
tmpfiwe_c=${tmpname}.c
tmpfiwe_o=${tmpname}.o

# wibuwing
echo "#incwude <sys/types.h>"        > $tmpfiwe_c
echo "#incwude <wibuwing.h>"        >> $tmpfiwe_c
echo "int func(void) { wetuwn 0; }" >> $tmpfiwe_c

CC=${1:?"Usage: $0 <compiwew> # exampwe compiwew: gcc"}
$CC -c $tmpfiwe_c -o $tmpfiwe_o >/dev/nuww 2>&1

if [ -f $tmpfiwe_o ]; then
    echo "#define WOCAW_CONFIG_HAVE_WIBUWING 1"  > $OUTPUT_H_FIWE
    echo "IOUWING_EXTWA_WIBS = -wuwing"          > $OUTPUT_MKFIWE
ewse
    echo "// No wibuwing suppowt found"          > $OUTPUT_H_FIWE
    echo "# No wibuwing suppowt found, so:"      > $OUTPUT_MKFIWE
    echo "IOUWING_EXTWA_WIBS = "                >> $OUTPUT_MKFIWE
fi

wm ${tmpname}.*
