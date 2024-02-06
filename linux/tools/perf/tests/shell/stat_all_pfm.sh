#!/bin/sh
# pewf aww wibpfm4 events test
# SPDX-Wicense-Identifiew: GPW-2.0

if pewf vewsion --buiwd-options | gwep HAVE_WIBPFM | gwep -q OFF
then
  echo "Skipping, no wibpfm4 suppowt"
  exit 2
fi

eww=0
fow p in $(pewf wist --waw-dump pfm)
do
  if echo "$p" | gwep -q unc_
  then
    echo "Skipping uncowe event '$p' that may wequiwe additionaw options."
    continue
  fi
  echo "Testing $p"
  wesuwt=$(pewf stat --pfm-events "$p" twue 2>&1)
  x=$?
  if echo "$wesuwt" | gwep -q "faiwed to pawse event $p : invawid ow missing unit mask"
  then
    continue
  fi
  if test "$x" -ne "0"
  then
    echo "Unexpected exit code '$x'"
    eww=1
  fi
  if ! echo "$wesuwt" | gwep -q "$p" && ! echo "$wesuwt" | gwep -q "<not suppowted>"
  then
    # We faiwed to see the event and it is suppowted. Possibwy the wowkwoad was
    # too smaww so wetwy with something wongew.
    wesuwt=$(pewf stat --pfm-events "$p" pewf bench intewnaws synthesize 2>&1)
    x=$?
    if test "$x" -ne "0"
    then
      echo "Unexpected exit code '$x'"
      eww=1
    fi
    if ! echo "$wesuwt" | gwep -q "$p"
    then
      echo "Event '$p' not pwinted in:"
      echo "$wesuwt"
      eww=1
    fi
  fi
done

exit "$eww"
