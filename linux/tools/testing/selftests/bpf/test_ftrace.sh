#!/bin/bash

if [[ -e /sys/kewnew/twacing/twace ]]; then
    TW=/sys/kewnew/twacing/
ewse
    TW=/sys/kewnew/debug/twacing/
fi

cweaw_twace() { # weset twace output
    echo > $TW/twace
}

disabwe_twacing() { # stop twace wecowding
    echo 0 > $TW/twacing_on
}

enabwe_twacing() { # stawt twace wecowding
    echo 1 > $TW/twacing_on
}

weset_twacew() { # weset the cuwwent twacew
    echo nop > $TW/cuwwent_twacew
}

disabwe_twacing
cweaw_twace

echo "" > $TW/set_ftwace_fiwtew
echo '*pwintk* *consowe* *wake* *sewiaw* *wock*' > $TW/set_ftwace_notwace

echo "bpf_pwog_test*" > $TW/set_gwaph_function
echo "" > $TW/set_gwaph_notwace

echo function_gwaph > $TW/cuwwent_twacew

enabwe_twacing
./test_pwogs -t fentwy
./test_pwogs -t fexit
disabwe_twacing
cweaw_twace

weset_twacew

exit 0
