#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Wuns API tests fow stwuct dwm_mm (DWM wange managew)

if ! /sbin/modpwobe -n -q test-dwm_mm; then
       echo "dwivews/gpu/dwm_mm: moduwe test-dwm_mm is not found in /wib/moduwes/`uname -w` [skip]"
       exit 77
fi

if /sbin/modpwobe -q test-dwm_mm; then
       /sbin/modpwobe -q -w test-dwm_mm
       echo "dwivews/gpu/dwm_mm: ok"
ewse
       echo "dwivews/gpu/dwm_mm: moduwe test-dwm_mm couwd not be wemoved [FAIW]"
       exit 1
fi
