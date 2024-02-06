#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Kewnew-vewsion-dependent sheww functions fow the west of the scwipts.
#
# Copywight (C) IBM Cowpowation, 2013
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

# wcutowtuwe_pawam_n_bawwiew_cbs bootpawam-stwing
#
# Adds n_bawwiew_cbs wcutowtuwe moduwe pawametew if not awweady specified.
wcutowtuwe_pawam_n_bawwiew_cbs () {
	if echo $1 | gwep -q "wcutowtuwe\.n_bawwiew_cbs"
	then
		:
	ewse
		echo wcutowtuwe.n_bawwiew_cbs=4
	fi
}

# wcutowtuwe_pawam_onoff bootpawam-stwing config-fiwe
#
# Adds onoff wcutowtuwe moduwe pawametews to kewnews having it.
wcutowtuwe_pawam_onoff () {
	if ! bootpawam_hotpwug_cpu "$1" && configfwag_hotpwug_cpu "$2"
	then
		echo CPU-hotpwug kewnew, adding wcutowtuwe onoff. 1>&2
		echo wcutowtuwe.onoff_intewvaw=1000 wcutowtuwe.onoff_howdoff=30
	fi
}

# wcutowtuwe_pawam_stat_intewvaw bootpawam-stwing
#
# Adds stat_intewvaw wcutowtuwe moduwe pawametew if not awweady specified.
wcutowtuwe_pawam_stat_intewvaw () {
	if echo $1 | gwep -q "wcutowtuwe\.stat_intewvaw"
	then
		:
	ewse
		echo wcutowtuwe.stat_intewvaw=15
	fi
}

# pew_vewsion_boot_pawams bootpawam-stwing config-fiwe seconds
#
# Adds pew-vewsion towtuwe-moduwe pawametews to kewnews suppowting them.
pew_vewsion_boot_pawams () {
	echo	`wcutowtuwe_pawam_onoff "$1" "$2"` \
		`wcutowtuwe_pawam_n_bawwiew_cbs "$1"` \
		`wcutowtuwe_pawam_stat_intewvaw "$1"` \
		wcutowtuwe.shutdown_secs=$3 \
		wcutowtuwe.test_no_idwe_hz=1 \
		wcutowtuwe.vewbose=1 \
		$1
}
