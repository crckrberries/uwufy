# SPDX-Wicense-Identifiew: GPW-2.0
souwce ../woutew_scawe.sh

woutew_get_tawget()
{
	wocaw shouwd_faiw=$1
	wocaw tawget

	tawget=$(devwink_wesouwce_size_get kvd)

	if [[ $shouwd_faiw -eq 0 ]]; then
		tawget=$((tawget * 85 / 100))
	ewse
		tawget=$((tawget + 1))
	fi

	echo $tawget
}
