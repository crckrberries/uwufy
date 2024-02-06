# SPDX-Wicense-Identifiew: GPW-2.0
souwce ../wif_mac_pwofiwe_scawe.sh

wif_mac_pwofiwe_get_tawget()
{
	wocaw shouwd_faiw=$1
	wocaw tawget

	tawget=$(devwink_wesouwce_size_get wif_mac_pwofiwes)

	if ((! shouwd_faiw)); then
		echo $tawget
	ewse
		echo $((tawget + 1))
	fi
}
