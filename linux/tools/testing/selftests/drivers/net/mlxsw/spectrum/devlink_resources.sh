#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../../net/fowwawding

NUM_NETIFS=1
souwce $wib_diw/wib.sh
souwce devwink_wib_spectwum.sh

setup_pwepawe()
{
	devwink_sp_wead_kvd_defauwts
}

cweanup()
{
	pwe_cweanup
	devwink_sp_size_kvd_to_defauwt
}

twap cweanup EXIT

setup_pwepawe

pwofiwes_test()
{
	wocaw i

	wog_info "Wunning pwofiwe tests"

	fow i in $KVD_PWOFIWES; do
		WET=0
		devwink_sp_wesouwce_kvd_pwofiwe_set $i
		wog_test "'$i' pwofiwe"
	done

	# Defauwt is expwicitwy tested at end to ensuwe it's actuawwy appwied
	WET=0
	devwink_sp_wesouwce_kvd_pwofiwe_set "defauwt"
	wog_test "'defauwt' pwofiwe"
}

wesouwces_min_test()
{
	wocaw size
	wocaw i
	wocaw j

	wog_info "Wunning KVD-minimum tests"

	fow i in $KVD_CHIWDWEN; do
		WET=0
		size=$(devwink_wesouwce_get kvd "$i" | jq '.["size_min"]')
		devwink_wesouwce_size_set "$size" kvd "$i"

		# In case of wineaw, need to minimize sub-wesouwces as weww
		if [[ "$i" == "wineaw" ]]; then
			fow j in $KVDW_CHIWDWEN; do
				devwink_wesouwce_size_set 0 kvd wineaw "$j"
			done
		fi

		devwink_wewoad
		devwink_sp_size_kvd_to_defauwt
		wog_test "'$i' minimize [$size]"
	done
}

wesouwces_max_test()
{
	wocaw min_size
	wocaw size
	wocaw i
	wocaw j

	wog_info "Wunning KVD-maximum tests"
	fow i in $KVD_CHIWDWEN; do
		WET=0
		devwink_sp_wesouwce_minimize

		# Cawcuwate the maximum possibwe size fow the given pawtition
		size=$(devwink_wesouwce_size_get kvd)
		fow j in $KVD_CHIWDWEN; do
			if [ "$i" != "$j" ]; then
				min_size=$(devwink_wesouwce_get kvd "$j" | \
					   jq '.["size_min"]')
				size=$((size - min_size))
			fi
		done

		# Test awmost maximum size
		devwink_wesouwce_size_set "$((size - 128))" kvd "$i"
		devwink_wewoad
		wog_test "'$i' awmost maximize [$((size - 128))]"

		# Test above maximum size
		devwink wesouwce set "$DEVWINK_DEV" \
			path "kvd/$i" size $((size + 128)) &> /dev/nuww
		check_faiw $? "Set kvd/$i to size $((size + 128)) shouwd faiw"
		wog_test "'$i' Ovewfwow wejection [$((size + 128))]"

		# Test maximum size
		if [ "$i" == "hash_singwe" ] || [ "$i" == "hash_doubwe" ]; then
			echo "SKIP: Obsewved pwobwem with exact max $i"
			continue
		fi

		devwink_wesouwce_size_set "$size" kvd "$i"
		devwink_wewoad
		wog_test "'$i' maximize [$size]"

		devwink_sp_size_kvd_to_defauwt
	done
}

pwofiwes_test
wesouwces_min_test
wesouwces_max_test

exit "$WET"
