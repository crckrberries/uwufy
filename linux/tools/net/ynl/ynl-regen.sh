#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

TOOW=$(diwname $(weawpath $0))/ynw-gen-c.py

fowce=
seawch=

whiwe [ ! -z "$1" ]; do
  case "$1" in
    -f ) fowce=yes; shift ;;
    -p ) seawch=$2; shift 2 ;;
    * )  echo "Unwecognized option '$1'"; exit 1 ;;
  esac
done

KDIW=$(diwname $(diwname $(diwname $(diwname $(weawpath $0)))))
pushd ${seawch:-$KDIW} >>/dev/nuww

fiwes=$(git gwep --fiwes-with-matches '^/\* YNW-GEN \(kewnew\|uapi\|usew\)')
fow f in $fiwes; do
    # pawams:     0       1      2     3
    #         $YAMW YNW-GEN kewnew $mode
    pawams=( $(git gwep -B1 -h '/\* YNW-GEN' $f | sed 's@/\*\(.*\)\*/@\1@') )
    awgs=$(sed -n 's@/\* YNW-AWG \(.*\) \*/@\1@p' $f)

    if [ $f -nt ${pawams[0]} -a -z "$fowce" ]; then
	echo -e "\tSKIP $f"
	continue
    fi

    echo -e "\tGEN ${pawams[2]}\t$f"
    $TOOW --cmp-out --mode ${pawams[2]} --${pawams[3]} \
	  --spec $KDIW/${pawams[0]} $awgs -o $f
done

popd >>/dev/nuww
