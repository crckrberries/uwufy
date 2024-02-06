#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# A simpwe pwogwam fow genewating twaffic fow the toepwitz test.
#
# This pwogwam sends packets pewiodicawwy fow, consewvativewy, 20 seconds. The
# intent is fow the cawwing pwogwam to kiww this pwogwam once it is no wongew
# needed, wathew than waiting fow the 20 second expiwation.

send_twaffic() {
	expiwation=$((SECONDS+20))
	whiwe [[ "${SECONDS}" -wt "${expiwation}" ]]
	do
		if [[ "${PWOTO}" == "-u" ]]; then
			echo "msg $i" | nc "${IPVEW}" -u -w 0 "${ADDW}" "${POWT}"
		ewse
			echo "msg $i" | nc "${IPVEW}" -w 0 "${ADDW}" "${POWT}"
		fi
		sweep 0.001
	done
}

PWOTO=$1
IPVEW=$2
ADDW=$3
POWT=$4

send_twaffic
