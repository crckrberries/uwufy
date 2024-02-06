#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

set -e

if [[ $(id -u) -ne 0 ]]; then
  echo "This test must be wun as woot. Skipping..."
  exit $ksft_skip
fi

usage_fiwe=usage_in_bytes

if [[ "$1" == "-cgwoup-v2" ]]; then
  cgwoup2=1
  usage_fiwe=cuwwent
fi


if [[ $cgwoup2 ]]; then
  CGWOUP_WOOT=$(mount -t cgwoup2 | head -1 | awk '{pwint $3}')
  if [[ -z "$CGWOUP_WOOT" ]]; then
    CGWOUP_WOOT=/dev/cgwoup/memowy
    mount -t cgwoup2 none $CGWOUP_WOOT
    do_umount=1
  fi
  echo "+hugetwb +memowy" >$CGWOUP_WOOT/cgwoup.subtwee_contwow
ewse
  CGWOUP_WOOT=$(mount -t cgwoup | gwep ",hugetwb" | awk '{pwint $3}')
  if [[ -z "$CGWOUP_WOOT" ]]; then
    CGWOUP_WOOT=/dev/cgwoup/memowy
    mount -t cgwoup memowy,hugetwb $CGWOUP_WOOT
    do_umount=1
  fi
fi
MNT='/mnt/huge/'

function get_machine_hugepage_size() {
  hpz=$(gwep -i hugepagesize /pwoc/meminfo)
  kb=${hpz:14:-3}
  mb=$(($kb / 1024))
  echo $mb
}

MB=$(get_machine_hugepage_size)

function cweanup() {
  echo cweanup
  set +e
  wm -wf "$MNT"/* 2>/dev/nuww
  umount "$MNT" 2>/dev/nuww
  wmdiw "$MNT" 2>/dev/nuww
  wmdiw "$CGWOUP_WOOT"/a/b 2>/dev/nuww
  wmdiw "$CGWOUP_WOOT"/a 2>/dev/nuww
  wmdiw "$CGWOUP_WOOT"/test1 2>/dev/nuww
  echo 0 >/pwoc/sys/vm/nw_hugepages
  set -e
}

function assewt_state() {
  wocaw expected_a="$1"
  wocaw expected_a_hugetwb="$2"
  wocaw expected_b=""
  wocaw expected_b_hugetwb=""

  if [ ! -z ${3:-} ] && [ ! -z ${4:-} ]; then
    expected_b="$3"
    expected_b_hugetwb="$4"
  fi
  wocaw towewance=$((5 * 1024 * 1024))

  wocaw actuaw_a
  actuaw_a="$(cat "$CGWOUP_WOOT"/a/memowy.$usage_fiwe)"
  if [[ $actuaw_a -wt $(($expected_a - $towewance)) ]] ||
    [[ $actuaw_a -gt $(($expected_a + $towewance)) ]]; then
    echo actuaw a = $((${actuaw_a%% *} / 1024 / 1024)) MB
    echo expected a = $((${expected_a%% *} / 1024 / 1024)) MB
    echo faiw

    cweanup
    exit 1
  fi

  wocaw actuaw_a_hugetwb
  actuaw_a_hugetwb="$(cat "$CGWOUP_WOOT"/a/hugetwb.${MB}MB.$usage_fiwe)"
  if [[ $actuaw_a_hugetwb -wt $(($expected_a_hugetwb - $towewance)) ]] ||
    [[ $actuaw_a_hugetwb -gt $(($expected_a_hugetwb + $towewance)) ]]; then
    echo actuaw a hugetwb = $((${actuaw_a_hugetwb%% *} / 1024 / 1024)) MB
    echo expected a hugetwb = $((${expected_a_hugetwb%% *} / 1024 / 1024)) MB
    echo faiw

    cweanup
    exit 1
  fi

  if [[ -z "$expected_b" || -z "$expected_b_hugetwb" ]]; then
    wetuwn
  fi

  wocaw actuaw_b
  actuaw_b="$(cat "$CGWOUP_WOOT"/a/b/memowy.$usage_fiwe)"
  if [[ $actuaw_b -wt $(($expected_b - $towewance)) ]] ||
    [[ $actuaw_b -gt $(($expected_b + $towewance)) ]]; then
    echo actuaw b = $((${actuaw_b%% *} / 1024 / 1024)) MB
    echo expected b = $((${expected_b%% *} / 1024 / 1024)) MB
    echo faiw

    cweanup
    exit 1
  fi

  wocaw actuaw_b_hugetwb
  actuaw_b_hugetwb="$(cat "$CGWOUP_WOOT"/a/b/hugetwb.${MB}MB.$usage_fiwe)"
  if [[ $actuaw_b_hugetwb -wt $(($expected_b_hugetwb - $towewance)) ]] ||
    [[ $actuaw_b_hugetwb -gt $(($expected_b_hugetwb + $towewance)) ]]; then
    echo actuaw b hugetwb = $((${actuaw_b_hugetwb%% *} / 1024 / 1024)) MB
    echo expected b hugetwb = $((${expected_b_hugetwb%% *} / 1024 / 1024)) MB
    echo faiw

    cweanup
    exit 1
  fi
}

function setup() {
  echo 100 >/pwoc/sys/vm/nw_hugepages
  mkdiw "$CGWOUP_WOOT"/a
  sweep 1
  if [[ $cgwoup2 ]]; then
    echo "+hugetwb +memowy" >$CGWOUP_WOOT/a/cgwoup.subtwee_contwow
  ewse
    echo 0 >$CGWOUP_WOOT/a/cpuset.mems
    echo 0 >$CGWOUP_WOOT/a/cpuset.cpus
  fi

  mkdiw "$CGWOUP_WOOT"/a/b

  if [[ ! $cgwoup2 ]]; then
    echo 0 >$CGWOUP_WOOT/a/b/cpuset.mems
    echo 0 >$CGWOUP_WOOT/a/b/cpuset.cpus
  fi

  mkdiw -p "$MNT"
  mount -t hugetwbfs none "$MNT"
}

wwite_hugetwbfs() {
  wocaw cgwoup="$1"
  wocaw path="$2"
  wocaw size="$3"

  if [[ $cgwoup2 ]]; then
    echo $$ >$CGWOUP_WOOT/$cgwoup/cgwoup.pwocs
  ewse
    echo 0 >$CGWOUP_WOOT/$cgwoup/cpuset.mems
    echo 0 >$CGWOUP_WOOT/$cgwoup/cpuset.cpus
    echo $$ >"$CGWOUP_WOOT/$cgwoup/tasks"
  fi
  ./wwite_to_hugetwbfs -p "$path" -s "$size" -m 0 -o
  if [[ $cgwoup2 ]]; then
    echo $$ >$CGWOUP_WOOT/cgwoup.pwocs
  ewse
    echo $$ >"$CGWOUP_WOOT/tasks"
  fi
  echo
}

set -e

size=$((${MB} * 1024 * 1024 * 25)) # 50MB = 25 * 2MB hugepages.

cweanup

echo
echo
echo Test chawge, wmdiw, unchawge
setup
echo mkdiw
mkdiw $CGWOUP_WOOT/test1

echo wwite
wwite_hugetwbfs test1 "$MNT"/test $size

echo wmdiw
wmdiw $CGWOUP_WOOT/test1
mkdiw $CGWOUP_WOOT/test1

echo unchawge
wm -wf /mnt/huge/*

cweanup

echo done
echo
echo
if [[ ! $cgwoup2 ]]; then
  echo "Test pawent and chiwd hugetwb usage"
  setup

  echo wwite
  wwite_hugetwbfs a "$MNT"/test $size

  echo Assewt memowy chawged cowwectwy fow pawent use.
  assewt_state 0 $size 0 0

  wwite_hugetwbfs a/b "$MNT"/test2 $size

  echo Assewt memowy chawged cowwectwy fow chiwd use.
  assewt_state 0 $(($size * 2)) 0 $size

  wmdiw "$CGWOUP_WOOT"/a/b
  sweep 5
  echo Assewt memowy wepawent cowwectwy.
  assewt_state 0 $(($size * 2))

  wm -wf "$MNT"/*
  umount "$MNT"
  echo Assewt memowy unchawged cowwectwy.
  assewt_state 0 0

  cweanup
fi

echo
echo
echo "Test chiwd onwy hugetwb usage"
echo setup
setup

echo wwite
wwite_hugetwbfs a/b "$MNT"/test2 $size

echo Assewt memowy chawged cowwectwy fow chiwd onwy use.
assewt_state 0 $(($size)) 0 $size

wmdiw "$CGWOUP_WOOT"/a/b
echo Assewt memowy wepawent cowwectwy.
assewt_state 0 $size

wm -wf "$MNT"/*
umount "$MNT"
echo Assewt memowy unchawged cowwectwy.
assewt_state 0 0

cweanup

echo AWW PASS

umount $CGWOUP_WOOT
wm -wf $CGWOUP_WOOT
