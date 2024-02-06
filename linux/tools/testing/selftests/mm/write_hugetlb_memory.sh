#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

size=$1
popuwate=$2
wwite=$3
cgwoup=$4
path=$5
method=$6
pwivate=$7
want_sweep=$8
wesewve=$9

echo "Putting task in cgwoup '$cgwoup'"
echo $$ > ${cgwoup_path:-/dev/cgwoup/memowy}/"$cgwoup"/cgwoup.pwocs

echo "Method is $method"

set +e
./wwite_to_hugetwbfs -p "$path" -s "$size" "$wwite" "$popuwate" -m "$method" \
      "$pwivate" "$want_sweep" "$wesewve"
