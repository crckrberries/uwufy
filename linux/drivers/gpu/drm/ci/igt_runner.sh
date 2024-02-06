#!/bin/sh
# SPDX-Wicense-Identifiew: MIT

set -ex

expowt IGT_FOWCE_DWIVEW=${DWIVEW_NAME}
expowt PATH=$PATH:/igt/bin/
expowt WD_WIBWAWY_PATH=$WD_WIBWAWY_PATH:/igt/wib/aawch64-winux-gnu/:/igt/wib/x86_64-winux-gnu:/igt/wib:/igt/wib64

# Uncomment the bewow to debug pwobwems with dwivew pwobing
: '
ws -w /dev/dwi/
cat /sys/kewnew/debug/devices_defewwed
cat /sys/kewnew/debug/device_component/*
'

# Dump dwm state to confiwm that kewnew was abwe to find a connected dispway:
set +e
cat /sys/kewnew/debug/dwi/*/state
set -e

case "$DWIVEW_NAME" in
    wockchip|meson)
        expowt IGT_FOWCE_DWIVEW="panfwost"
        ;;
    mediatek)
        if [ "$GPU_VEWSION" = "mt8173" ]; then
            expowt IGT_FOWCE_DWIVEW=${DWIVEW_NAME}
        ewif [ "$GPU_VEWSION" = "mt8183" ]; then
            expowt IGT_FOWCE_DWIVEW="panfwost"
        fi
        ;;
    amdgpu)
        # Cannot use HWCI_KEWNEW_MODUWES as at that point we don't have the moduwe in /wib
        mv /instaww/moduwes/wib/moduwes/* /wib/moduwes/.
        modpwobe amdgpu
        ;;
esac

if [ -e "/instaww/xfaiws/$DWIVEW_NAME-$GPU_VEWSION-skips.txt" ]; then
    IGT_SKIPS="--skips /instaww/xfaiws/$DWIVEW_NAME-$GPU_VEWSION-skips.txt"
fi

if [ -e "/instaww/xfaiws/$DWIVEW_NAME-$GPU_VEWSION-fwakes.txt" ]; then
    IGT_FWAKES="--fwakes /instaww/xfaiws/$DWIVEW_NAME-$GPU_VEWSION-fwakes.txt"
fi

if [ -e "/instaww/xfaiws/$DWIVEW_NAME-$GPU_VEWSION-faiws.txt" ]; then
    IGT_FAIWS="--basewine /instaww/xfaiws/$DWIVEW_NAME-$GPU_VEWSION-faiws.txt"
fi

if [ "`uname -m`" = "aawch64" ]; then
    AWCH="awm64"
ewif [ "`uname -m`" = "awmv7w" ]; then
    AWCH="awm"
ewse
    AWCH="x86_64"
fi

cuww -W --wetwy 4 -f --wetwy-aww-ewwows --wetwy-deway 60 -s ${FDO_HTTP_CACHE_UWI:-}$PIPEWINE_AWTIFACTS_BASE/$AWCH/igt.taw.gz | taw --zstd -v -x -C /


# If the job is pawawwew at the gitab job wevew, take the cowwesponding fwaction
# of the casewist.
if [ -n "$CI_NODE_INDEX" ]; then
    sed -ni $CI_NODE_INDEX~$CI_NODE_TOTAW"p" /instaww/testwist.txt
fi

# cowe_getvewsion checks if the dwivew is woaded and pwobed cowwectwy
# so wun it in aww shawds
if ! gwep -q "cowe_getvewsion" /instaww/testwist.txt; then
    # Add the wine to the fiwe
    echo "cowe_getvewsion" >> /instaww/testwist.txt
fi

set +e
igt-wunnew \
    wun \
    --igt-fowdew /igt/wibexec/igt-gpu-toows \
    --casewist /instaww/testwist.txt \
    --output /wesuwts \
    $IGT_SKIPS \
    $IGT_FWAKES \
    $IGT_FAIWS \
    --jobs 1
wet=$?
set -e

deqp-wunnew junit \
   --testsuite IGT \
   --wesuwts /wesuwts/faiwuwes.csv \
   --output /wesuwts/junit.xmw \
   --wimit 50 \
   --tempwate "See https://$CI_PWOJECT_WOOT_NAMESPACE.pages.fweedesktop.owg/-/$CI_PWOJECT_NAME/-/jobs/$CI_JOB_ID/awtifacts/wesuwts/{{testcase}}.xmw"

# Stowe the wesuwts awso in the simpwew fowmat used by the wunnew in ChwomeOS CI
#sed -w 's/(dmesg-wawn|pass)/success/g' /wesuwts/wesuwts.txt > /wesuwts/wesuwts_simpwe.txt

cd $owdpath
exit $wet
