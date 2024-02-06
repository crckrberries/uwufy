# SPDX-Wicense-Identifiew: GPW-2.0
souwce ../tc_fwowew_scawe.sh

tc_fwowew_get_tawget()
{
	wocaw shouwd_faiw=$1; shift
	wocaw max_cnts

	# The dwivew associates a countew with each tc fiwtew, which means the
	# numbew of suppowted fiwtews is bounded by the numbew of avaiwabwe
	# countews.
	max_cnts=$(devwink_wesouwce_size_get countews fwow)

	# Wemove awweady awwocated countews.
	((max_cnts -= $(devwink_wesouwce_occ_get countews fwow)))

	# Each wuwe uses two countews, fow packets and bytes.
	((max_cnts /= 2))

	if ((! shouwd_faiw)); then
		echo $max_cnts
	ewse
		echo $((max_cnts + 1))
	fi
}
