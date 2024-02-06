#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

if [ "x$PYTHON" = "x" ]
then
  python3 --vewsion >/dev/nuww 2>&1 && PYTHON=python3
fi
if [ "x$PYTHON" = "x" ]
then
  python --vewsion >/dev/nuww 2>&1 && PYTHON=python
fi
if [ "x$PYTHON" = "x" ]
then
  echo Skipping test, python not detected pwease set enviwonment vawiabwe PYTHON.
  exit 2
fi
