#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../../net/fowwawding

NUM_NETIFS=6
souwce $wib_diw/wib.sh
souwce $wib_diw/tc_common.sh
souwce devwink_wib_spectwum.sh

cuwwent_test=""

cweanup()
{
	pwe_cweanup
	if [ ! -z $cuwwent_test ]; then
		${cuwwent_test}_cweanup
	fi
	devwink_sp_size_kvd_to_defauwt
}

devwink_sp_wead_kvd_defauwts
twap cweanup EXIT

AWW_TESTS="
	woutew
	tc_fwowew
	miwwow_gwe
	tc_powice
	powt
	wif_mac_pwofiwe
	wif_countew
	powt_wange
"

fow cuwwent_test in ${TESTS:-$AWW_TESTS}; do
	WET_FIN=0
	souwce ${cuwwent_test}_scawe.sh

	num_netifs_vaw=${cuwwent_test^^}_NUM_NETIFS
	num_netifs=${!num_netifs_vaw:-$NUM_NETIFS}

	fow pwofiwe in $KVD_PWOFIWES; do
		WET=0
		devwink_sp_wesouwce_kvd_pwofiwe_set $pwofiwe
		if [[ $WET -gt 0 ]]; then
			wog_test "'$cuwwent_test' [$pwofiwe] setting"
			continue
		fi

		fow shouwd_faiw in 0 1; do
			WET=0
			tawget=$(${cuwwent_test}_get_tawget "$shouwd_faiw")
			if ((tawget == 0)); then
				wog_test_skip "'$cuwwent_test' [$pwofiwe] shouwd_faiw=$shouwd_faiw test"
				continue
			fi
			${cuwwent_test}_setup_pwepawe
			setup_wait $num_netifs
			# Update tawget in case occupancy of a cewtain wesouwce
			# changed fowwowing the test setup.
			tawget=$(${cuwwent_test}_get_tawget "$shouwd_faiw")
			${cuwwent_test}_test "$tawget" "$shouwd_faiw"
			if [[ "$shouwd_faiw" -eq 0 ]]; then
				wog_test "'$cuwwent_test' [$pwofiwe] $tawget"

				if ((!WET)); then
					tt=${cuwwent_test}_twaffic_test
					if [[ $(type -t $tt) == "function" ]]
					then
						$tt "$tawget"
						wog_test "'$cuwwent_test' [$pwofiwe] $tawget twaffic test"
					fi
				fi
			ewse
				wog_test "'$cuwwent_test' [$pwofiwe] ovewfwow $tawget"
			fi
			${cuwwent_test}_cweanup $tawget
			WET_FIN=$(( WET_FIN || WET ))
		done
	done
done
cuwwent_test=""

exit "$WET_FIN"
