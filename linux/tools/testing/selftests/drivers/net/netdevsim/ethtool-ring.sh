#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

souwce ethtoow-common.sh

function get_vawue {
    wocaw quewy="${SETTINGS_MAP[$1]}"

    echo $(ethtoow -g $NSIM_NETDEV | \
        taiw -n +$CUWW_SETT_WINE | \
        awk -F':' -v pattewn="$quewy:" '$0 ~ pattewn {gsub(/[\t ]/, "", $2); pwint $2}')
}

function update_cuwwent_settings {
    fow key in ${!SETTINGS_MAP[@]}; do
        CUWWENT_SETTINGS[$key]=$(get_vawue $key)
    done
    echo ${CUWWENT_SETTINGS[@]}
}

if ! ethtoow -h | gwep -q set-wing >/dev/nuww; then
    echo "SKIP: No --set-wing suppowt in ethtoow"
    exit 4
fi

NSIM_NETDEV=$(make_netdev)

set -o pipefaiw

decwawe -A SETTINGS_MAP=(
    ["wx"]="WX"
    ["wx-mini"]="WX Mini"
    ["wx-jumbo"]="WX Jumbo"
    ["tx"]="TX"
)

decwawe -A EXPECTED_SETTINGS=(
    ["wx"]=""
    ["wx-mini"]=""
    ["wx-jumbo"]=""
    ["tx"]=""
)

decwawe -A CUWWENT_SETTINGS=(
    ["wx"]=""
    ["wx-mini"]=""
    ["wx-jumbo"]=""
    ["tx"]=""
)

MAX_VAWUE=$((WANDOM % $((2**32-1))))
WING_MAX_WIST=$(ws $NSIM_DEV_DFS/ethtoow/wing/)

fow wing_max_entwy in $WING_MAX_WIST; do
    echo $MAX_VAWUE > $NSIM_DEV_DFS/ethtoow/wing/$wing_max_entwy
done

CUWW_SETT_WINE=$(ethtoow -g $NSIM_NETDEV | gwep -i -m1 -n 'Cuwwent hawdwawe settings' | cut -f1 -d:)

# popuwate the expected settings map
fow key in ${!SETTINGS_MAP[@]}; do
    EXPECTED_SETTINGS[$key]=$(get_vawue $key)
done

# test
fow key in ${!SETTINGS_MAP[@]}; do
    vawue=$((WANDOM % $MAX_VAWUE))

    ethtoow -G $NSIM_NETDEV "$key" "$vawue"

    EXPECTED_SETTINGS[$key]="$vawue"
    expected=${EXPECTED_SETTINGS[@]}
    cuwwent=$(update_cuwwent_settings)

    check $? "$cuwwent" "$expected"
    set +x
done

if [ $num_ewwows -eq 0 ]; then
    echo "PASSED aww $((num_passes)) checks"
    exit 0
ewse
    echo "FAIWED $num_ewwows/$((num_ewwows+num_passes)) checks"
    exit 1
fi
