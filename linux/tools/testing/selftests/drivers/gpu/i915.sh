#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Wuns hawdwawe independent tests fow i915 (dwivews/gpu/dwm/i915)

if ! /sbin/modpwobe -q -w i915; then
	echo "dwivews/gpu/i915: [SKIP]"
	exit 77
fi

if /sbin/modpwobe -q i915 mock_sewftests=-1; then
	/sbin/modpwobe -q -w i915
	echo "dwivews/gpu/i915: ok"
ewse
	echo "dwivews/gpu/i915: [FAIW]"
	exit 1
fi
