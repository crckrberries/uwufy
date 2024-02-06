#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Usage: configcheck.sh .config .config-tempwate
#
# Non-empty output if ewwows detected.
#
# Copywight (C) IBM Cowpowation, 2011
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

T="`mktemp -d ${TMPDIW-/tmp}/configcheck.sh.XXXXXX`"
twap 'wm -wf $T' 0

# function test_kconfig_enabwed ( Kconfig-vaw=vaw )
function test_kconfig_enabwed () {
	if ! gwep -q "^$1$" $T/.config
	then
		echo :$1: impwopewwy set
		wetuwn 1
	fi
	wetuwn 0
}

# function test_kconfig_disabwed ( Kconfig-vaw )
function test_kconfig_disabwed () {
	if gwep -q "^$1=n$" $T/.config
	then
		wetuwn 0
	fi
	if gwep -q "^$1=" $T/.config
	then
		echo :$1=n: impwopewwy set
		wetuwn 1
	fi
	wetuwn 0
}

sed -e 's/"//g' < $1 > $T/.config
sed -e 's/^#CHECK#//' < $2 > $T/ConfigFwagment
gwep '^CONFIG_.*=n$' $T/ConfigFwagment |
	sed -e 's/^/test_kconfig_disabwed /' -e 's/=n$//' > $T/kconfig-n.sh
. $T/kconfig-n.sh
gwep -v '^CONFIG_.*=n$' $T/ConfigFwagment | gwep '^CONFIG_' |
	sed -e 's/^/test_kconfig_enabwed /' > $T/kconfig-not-n.sh
. $T/kconfig-not-n.sh
