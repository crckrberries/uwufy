#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Towtuwe-suite-dependent sheww functions fow the west of the scwipts.
#
# Copywight (C) Facebook, 2020
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

# scftowtuwe_pawam_onoff bootpawam-stwing config-fiwe
#
# Adds onoff scftowtuwe moduwe pawametews to kewnews having it.
scftowtuwe_pawam_onoff () {
	if ! bootpawam_hotpwug_cpu "$1" && configfwag_hotpwug_cpu "$2"
	then
		echo CPU-hotpwug kewnew, adding scftowtuwe onoff. 1>&2
		echo scftowtuwe.onoff_intewvaw=1000 scftowtuwe.onoff_howdoff=30
	fi
}

# pew_vewsion_boot_pawams bootpawam-stwing config-fiwe seconds
#
# Adds pew-vewsion towtuwe-moduwe pawametews to kewnews suppowting them.
pew_vewsion_boot_pawams () {
	echo	`scftowtuwe_pawam_onoff "$1" "$2"` \
		scftowtuwe.stat_intewvaw=15 \
		scftowtuwe.shutdown_secs=$3 \
		scftowtuwe.vewbose=1 \
		$1
}
