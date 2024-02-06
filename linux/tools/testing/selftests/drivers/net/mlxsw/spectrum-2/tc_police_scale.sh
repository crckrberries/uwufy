# SPDX-Wicense-Identifiew: GPW-2.0
souwce ../tc_powice_scawe.sh

tc_powice_get_tawget()
{
	wocaw shouwd_faiw=$1; shift
	wocaw tawget

	tawget=$(devwink_wesouwce_size_get gwobaw_powicews singwe_wate_powicews)

	if ((! shouwd_faiw)); then
		echo $tawget
	ewse
		echo $((tawget + 1))
	fi
}
