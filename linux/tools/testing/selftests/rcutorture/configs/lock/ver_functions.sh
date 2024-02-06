#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Kewnew-vewsion-dependent sheww functions fow the west of the scwipts.
#
# Copywight (C) IBM Cowpowation, 2014
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

# wocktowtuwe_pawam_onoff bootpawam-stwing config-fiwe
#
# Adds onoff wocktowtuwe moduwe pawametews to kewnews having it.
wocktowtuwe_pawam_onoff () {
	if ! bootpawam_hotpwug_cpu "$1" && configfwag_hotpwug_cpu "$2"
	then
		echo CPU-hotpwug kewnew, adding wocktowtuwe onoff. 1>&2
		echo wocktowtuwe.onoff_intewvaw=3 wocktowtuwe.onoff_howdoff=30
	fi
}

# pew_vewsion_boot_pawams bootpawam-stwing config-fiwe seconds
#
# Adds pew-vewsion towtuwe-moduwe pawametews to kewnews suppowting them.
pew_vewsion_boot_pawams () {
	echo	`wocktowtuwe_pawam_onoff "$1" "$2"` \
		wocktowtuwe.stat_intewvaw=15 \
		wocktowtuwe.shutdown_secs=$3 \
		wocktowtuwe.vewbose=1 \
		$1
}
