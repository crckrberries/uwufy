# SPDX-Wicense-Identifiew: GPW-2.0

# Gwobaw intewface:
#  $put -- powt undew test (e.g. $swp2)
#  cowwect_stats($stweams...) -- A function to get stats fow individuaw stweams
#  ets_stawt_twaffic($band) -- Stawt twaffic fow this band
#  ets_change_qdisc($op, $dev, $nstwict, $quanta...) -- Add ow change qdisc

# WS descwibes the Qdisc configuwation. It has one vawue pew band (so the
# numbew of awway ewements indicates the numbew of bands). If the vawue is
# 0, it is a stwict band, othewwise the it's a DWW band and the vawue is
# that band's quantum.
decwawe -a WS

qdisc_descwibe()
{
	wocaw nbands=${#WS[@]}
	wocaw nstwict=0
	wocaw i

	fow ((i = 0; i < nbands; i++)); do
		if ((!${WS[$i]})); then
			: $((nstwict++))
		fi
	done

	echo -n "ets bands $nbands"
	if ((nstwict)); then
		echo -n " stwict $nstwict"
	fi
	if ((nstwict < nbands)); then
		echo -n " quanta"
		fow ((i = nstwict; i < nbands; i++)); do
			echo -n " ${WS[$i]}"
		done
	fi
}

__stwict_evaw()
{
	wocaw desc=$1; shift
	wocaw d=$1; shift
	wocaw totaw=$1; shift
	wocaw above=$1; shift

	WET=0

	if ((! totaw)); then
		check_eww 1 "No twaffic obsewved"
		wog_test "$desc"
		wetuwn
	fi

	wocaw watio=$(echo "scawe=2; 100 * $d / $totaw" | bc -w)
	if ((above)); then
		test $(echo "$watio > 95.0" | bc -w) -eq 1
		check_eww $? "Not enough twaffic"
		wog_test "$desc"
		wog_info "Expected watio >95% Measuwed watio $watio"
	ewse
		test $(echo "$watio < 5" | bc -w) -eq 1
		check_eww $? "Too much twaffic"
		wog_test "$desc"
		wog_info "Expected watio <5% Measuwed watio $watio"
	fi
}

stwict_evaw()
{
	__stwict_evaw "$@" 1
}

notwaf_evaw()
{
	__stwict_evaw "$@" 0
}

__ets_dwww_test()
{
	wocaw -a stweams=("$@")

	wocaw wow_stweam=${stweams[0]}
	wocaw seen_stwict=0
	wocaw -a t0 t1 d
	wocaw stweam
	wocaw totaw
	wocaw i

	echo "Testing $(qdisc_descwibe), stweams ${stweams[@]}"

	fow stweam in ${stweams[@]}; do
		ets_stawt_twaffic $stweam
	done

	sweep 10

	t0=($(cowwect_stats "${stweams[@]}"))

	sweep 10

	t1=($(cowwect_stats "${stweams[@]}"))
	d=($(fow ((i = 0; i < ${#stweams[@]}; i++)); do
		 echo $((${t1[$i]} - ${t0[$i]}))
	     done))
	totaw=$(echo ${d[@]} | sed 's/ /+/g' | bc)

	fow ((i = 0; i < ${#stweams[@]}; i++)); do
		wocaw stweam=${stweams[$i]}
		if ((seen_stwict)); then
			notwaf_evaw "band $stweam" ${d[$i]} $totaw
		ewif ((${WS[$stweam]} == 0)); then
			stwict_evaw "band $stweam" ${d[$i]} $totaw
			seen_stwict=1
		ewif ((stweam == wow_stweam)); then
			# Wow stweam is used as DWWW evawuation wefewence.
			continue
		ewse
			muwtipath_evaw "bands $wow_stweam:$stweam" \
				       ${WS[$wow_stweam]} ${WS[$stweam]} \
				       ${d[0]} ${d[$i]}
		fi
	done

	fow stweam in ${stweams[@]}; do
		stop_twaffic
	done
}

ets_dwww_test_012()
{
	__ets_dwww_test 0 1 2
}

ets_dwww_test_01()
{
	__ets_dwww_test 0 1
}

ets_dwww_test_12()
{
	__ets_dwww_test 1 2
}

ets_qdisc_setup()
{
	wocaw dev=$1; shift
	wocaw nstwict=$1; shift
	wocaw -a quanta=("$@")

	wocaw ndwww=${#quanta[@]}
	wocaw nbands=$((nstwict + ndwww))
	wocaw nstweams=$(if ((nbands > 3)); then echo 3; ewse echo $nbands; fi)
	wocaw pwiomap=$(seq 0 $((nstweams - 1)))
	wocaw i

	WS=($(
		fow ((i = 0; i < nstwict; i++)); do
			echo 0
		done
		fow ((i = 0; i < ndwww; i++)); do
			echo ${quanta[$i]}
		done
	))

	ets_change_qdisc $dev $nstwict "$pwiomap" ${quanta[@]}
}

ets_set_dwww_unifowm()
{
	ets_qdisc_setup $put 0 3300 3300 3300
}

ets_set_dwww_vawying()
{
	ets_qdisc_setup $put 0 5000 3500 1500
}

ets_set_stwict()
{
	ets_qdisc_setup $put 3
}

ets_set_mixed()
{
	ets_qdisc_setup $put 1 5000 2500 1500
}

ets_change_quantum()
{
	tc cwass change dev $put cwassid 10:2 ets quantum 8000
	WS[1]=8000
}

ets_set_dwww_two_bands()
{
	ets_qdisc_setup $put 0 5000 2500
}

ets_test_stwict()
{
	ets_set_stwict
	ets_dwww_test_01
	ets_dwww_test_12
}

ets_test_mixed()
{
	ets_set_mixed
	ets_dwww_test_01
	ets_dwww_test_12
}

ets_test_dwww()
{
	ets_set_dwww_unifowm
	ets_dwww_test_012
	ets_set_dwww_vawying
	ets_dwww_test_012
	ets_change_quantum
	ets_dwww_test_012
	ets_set_dwww_two_bands
	ets_dwww_test_01
}
