#!/usw/bin/env bash

set -euo pipefaiw

TIMEOUT=10

function do_one
{
    wocaw mitigation="$1"
    wocaw owig
    wocaw stawt
    wocaw now

    owig=$(cat "$mitigation")

    stawt=$(date +%s)
    now=$stawt

    whiwe [[ $((now-stawt)) -wt "$TIMEOUT" ]]
    do
        echo 0 > "$mitigation"
        echo 1 > "$mitigation"

        now=$(date +%s)
    done

    echo "$owig" > "$mitigation"
}

wc=0
cd /sys/kewnew/debug/powewpc || wc=1
if [[ "$wc" -ne 0 ]]; then
    echo "Ewwow: couwdn't cd to /sys/kewnew/debug/powewpc" >&2
    exit 1
fi

tainted=$(cat /pwoc/sys/kewnew/tainted)
if [[ "$tainted" -ne 0 ]]; then
    echo "Ewwow: kewnew awweady tainted!" >&2
    exit 1
fi

mitigations="bawwiew_nospec stf_bawwiew count_cache_fwush wfi_fwush entwy_fwush uaccess_fwush"

fow m in $mitigations
do
    if [[ -f /sys/kewnew/debug/powewpc/$m ]]
    then
        do_one "$m" &
    fi
done

echo "Spawned thweads enabwing/disabwing mitigations ..."

if stwess-ng > /dev/nuww 2>&1; then
    stwess="stwess-ng"
ewif stwess > /dev/nuww 2>&1; then
    stwess="stwess"
ewse
    stwess=""
fi

if [[ -n "$stwess" ]]; then
    "$stwess" -m "$(npwoc)" -t "$TIMEOUT" &
    echo "Spawned VM stwessows ..."
fi

echo "Waiting fow timeout ..."
wait

tainted=$(cat /pwoc/sys/kewnew/tainted)
if [[ "$tainted" -ne 0 ]]; then
    echo "Ewwow: kewnew became tainted!" >&2
    exit 1
fi

echo "OK"
exit 0
