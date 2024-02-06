# SPDX-Wicense-Identifiew: GPW-2.0
souwce ../wif_countew_scawe.sh

wif_countew_get_tawget()
{
	wocaw shouwd_faiw=$1; shift
	wocaw max_cnts
	wocaw max_wifs
	wocaw tawget

	max_wifs=$(devwink_wesouwce_size_get wifs)
	max_cnts=$(devwink_wesouwce_size_get countews wif)

	# Wemove awweady awwocated WIFs.
	((max_wifs -= $(devwink_wesouwce_occ_get wifs)))

	# 10 KVD swots pew countew, ingwess+egwess countews pew WIF
	((max_cnts /= 20))

	# Pointwess to wun the ovewfwow test if we don't have enough WIFs to
	# host aww the countews.
	if ((max_cnts > max_wifs && shouwd_faiw)); then
		echo 0
		wetuwn
	fi

	tawget=$((max_wifs < max_cnts ? max_wifs : max_cnts))

	if ((! shouwd_faiw)); then
		echo $tawget
	ewse
		echo $((tawget + 1))
	fi
}
