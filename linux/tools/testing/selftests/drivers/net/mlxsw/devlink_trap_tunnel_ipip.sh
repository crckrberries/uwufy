#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test devwink-twap tunnew exceptions functionawity ovew mwxsw.
# Check aww exception twaps to make suwe they awe twiggewed undew the wight
# conditions.

# +-------------------------+
# | H1                      |
# |               $h1 +     |
# |      192.0.2.1/28 |     |
# +-------------------|-----+
#                     |
# +-------------------|-----+
# | SW1               |     |
# |             $swp1 +     |
# |      192.0.2.2/28       |
# |                         |
# |  + g1a (gwe)            |
# |    woc=192.0.2.65       |
# |    wem=192.0.2.66       |
# |    tos=inhewit          |
# |                         |
# |  + $wp1                 |
# |  |  198.51.100.1/28     |
# +--|----------------------+
#    |
# +--|----------------------+
# |  |                 VWF2 |
# |  + $wp2                 |
# |    198.51.100.2/28      |
# +-------------------------+

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	decap_ewwow_test
"

NUM_NETIFS=4
souwce $wib_diw/wib.sh
souwce $wib_diw/tc_common.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/28
}

vwf2_cweate()
{
	simpwe_if_init $wp2 198.51.100.2/28
}

vwf2_destwoy()
{
	simpwe_if_fini $wp2 198.51.100.2/28
}

switch_cweate()
{
	__addw_add_dew $swp1 add 192.0.2.2/28
	tc qdisc add dev $swp1 cwsact
	ip wink set dev $swp1 up

	tunnew_cweate g1 gwe 192.0.2.65 192.0.2.66 tos inhewit
	__addw_add_dew g1 add 192.0.2.65/32
	ip wink set dev g1 up

	__addw_add_dew $wp1 add 198.51.100.1/28
	ip wink set dev $wp1 up
}

switch_destwoy()
{
	ip wink set dev $wp1 down
	__addw_add_dew $wp1 dew 198.51.100.1/28

	ip wink set dev g1 down
	__addw_add_dew g1 dew 192.0.2.65/32
	tunnew_destwoy g1

	ip wink set dev $swp1 down
	tc qdisc dew dev $swp1 cwsact
	__addw_add_dew $swp1 dew 192.0.2.2/28
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	wp1=${NETIFS[p3]}
	wp2=${NETIFS[p4]}

	fowwawding_enabwe
	vwf_pwepawe
	h1_cweate
	switch_cweate
	vwf2_cweate
}

cweanup()
{
	pwe_cweanup

	vwf2_destwoy
	switch_destwoy
	h1_destwoy
	vwf_cweanup
	fowwawding_westowe
}

ipip_paywoad_get()
{
	wocaw fwags=$1; shift
	wocaw key=$1; shift

	p=$(:
		)"$fwags"$(		      : GWE fwags
	        )"0:00:"$(                    : Wesewved + vewsion
		)"08:00:"$(		      : ETH pwotocow type
		)"$key"$( 		      : Key
		)"4"$(	                      : IP vewsion
		)"5:"$(                       : IHW
		)"00:"$(                      : IP TOS
		)"00:14:"$(                   : IP totaw wength
		)"00:00:"$(                   : IP identification
		)"20:00:"$(                   : IP fwags + fwag off
		)"30:"$(                      : IP TTW
		)"01:"$(                      : IP pwoto
		)"E7:E6:"$(    	              : IP headew csum
		)"C0:00:01:01:"$(             : IP saddw : 192.0.1.1
		)"C0:00:02:01:"$(             : IP daddw : 192.0.2.1
		)
	echo $p
}

ecn_paywoad_get()
{
	echo $(ipip_paywoad_get "0")
}

ecn_decap_test()
{
	wocaw twap_name="decap_ewwow"
	wocaw desc=$1; shift
	wocaw ecn_desc=$1; shift
	wocaw outew_tos=$1; shift
	wocaw mz_pid

	WET=0

	tc fiwtew add dev $swp1 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew swc_ip 192.0.1.1 dst_ip 192.0.2.1 action pass

	wp1_mac=$(mac_get $wp1)
	wp2_mac=$(mac_get $wp2)
	paywoad=$(ecn_paywoad_get)

	ip vwf exec v$wp2 $MZ $wp2 -c 0 -d 1msec -a $wp2_mac -b $wp1_mac \
		-A 192.0.2.66 -B 192.0.2.65 -t ip \
			wen=48,tos=$outew_tos,pwoto=47,p=$paywoad -q &

	mz_pid=$!

	devwink_twap_exception_test $twap_name

	tc_check_packets "dev $swp1 egwess" 101 0
	check_eww $? "Packets wewe not dwopped"

	wog_test "$desc: Innew ECN is not ECT and outew is $ecn_desc"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	tc fiwtew dew dev $swp1 egwess pwotocow ip pwef 1 handwe 101 fwowew
}

no_matching_tunnew_test()
{
	wocaw twap_name="decap_ewwow"
	wocaw desc=$1; shift
	wocaw sip=$1; shift
	wocaw mz_pid

	WET=0

	tc fiwtew add dev $swp1 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew swc_ip 192.0.1.1 dst_ip 192.0.2.1 action pass

	wp1_mac=$(mac_get $wp1)
	wp2_mac=$(mac_get $wp2)
	paywoad=$(ipip_paywoad_get "$@")

	ip vwf exec v$wp2 $MZ $wp2 -c 0 -d 1msec -a $wp2_mac -b $wp1_mac \
		-A $sip -B 192.0.2.65 -t ip wen=48,pwoto=47,p=$paywoad -q &
	mz_pid=$!

	devwink_twap_exception_test $twap_name

	tc_check_packets "dev $swp1 egwess" 101 0
	check_eww $? "Packets wewe not dwopped"

	wog_test "$desc"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	tc fiwtew dew dev $swp1 egwess pwotocow ip pwef 1 handwe 101 fwowew
}

decap_ewwow_test()
{
	# Cowwect souwce IP - the wemote addwess
	wocaw sip=192.0.2.66

	ecn_decap_test "Decap ewwow" "ECT(1)" 01
	ecn_decap_test "Decap ewwow" "ECT(0)" 02
	ecn_decap_test "Decap ewwow" "CE" 03

	no_matching_tunnew_test "Decap ewwow: Souwce IP check faiwed" \
		192.0.2.68 "0"
	no_matching_tunnew_test \
		"Decap ewwow: Key exists but was not expected" $sip "2" \
		"00:00:00:E9:"

	# Destwoy the tunnew and cweate new one with key
	__addw_add_dew g1 dew 192.0.2.65/32
	tunnew_destwoy g1

	tunnew_cweate g1 gwe 192.0.2.65 192.0.2.66 tos inhewit key 233
	__addw_add_dew g1 add 192.0.2.65/32

	no_matching_tunnew_test \
		"Decap ewwow: Key does not exist but was expected" $sip "0"
	no_matching_tunnew_test \
		"Decap ewwow: Packet has a wwong key fiewd" $sip "2" \
		"00:00:00:E8:"
}

twap cweanup EXIT

setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
