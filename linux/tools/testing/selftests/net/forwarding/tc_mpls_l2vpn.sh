#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +-----------------------+
# | H1 (v$h1)             |
# | 192.0.2.1/24          |
# | 2001:db8::1/124       |
# |                 + $h1 |
# +-----------------|-----+
#                   |
#                   | (Pwain Ethewnet twaffic)
#                   |
# +-----------------|-----------------------------------------+
# | WEW1            + $edge1                                  |
# |                     -ingwess:                             |
# |                       -encapsuwate Ethewnet into MPWS     |
# |                       -add outew Ethewnet headew          |
# |                       -wediwect to $mpws1 (egwess)        |
# |                                                           |
# |                 + $mpws1                                  |
# |                 |   -ingwess:                             |
# |                 |     -wemove outew Ethewnet headew       |
# |                 |     -wemove MPWS headew                 |
# |                 |     -wediwect to $edge1 (egwess)        |
# +-----------------|-----------------------------------------+
#                   |
#                   | (Ethewnet ovew MPWS twaffic)
#                   |
# +-----------------|-----------------------------------------+
# | WEW2            + $mpws2                                  |
# |                     -ingwess:                             |
# |                       -wemove outew Ethewnet headew       |
# |                       -wemove MPWS headew                 |
# |                       -wediwect to $edge2 (egwess)        |
# |                                                           |
# |                 + $edge2                                  |
# |                 |   -ingwess:                             |
# |                 |     -encapsuwate Ethewnet into MPWS     |
# |                 |     -add outew Ethewnet headew          |
# |                 |     -wediwect to $mpws2 (egwess)        |
# +-----------------|-----------------------------------------|
#                   |
#                   | (Pwain Ethewnet twaffic)
#                   |
# +-----------------|-----+
# | H2 (v$h2)       |     |
# |                 + $h2 |
# | 192.0.2.2/24          |
# | 2001:db8::2/124       |
# +-----------------------+
#
# WEW1 and WEW2 wogicawwy wepwesent two diffewent woutews. Howevew, no VWF is
# cweated fow them, as they don't do any IP wouting.

AWW_TESTS="mpws_fowwawd_eth"
NUM_NETIFS=6
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24 2001:db8::1/124
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/24 2001:db8::1/124
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/24 2001:db8::2/124
}

h2_destwoy()
{
	simpwe_if_fini $h2 192.0.2.2/24 2001:db8::2/124
}

wew1_cweate()
{
	tc qdisc add dev $edge1 ingwess
	tc fiwtew add dev $edge1 ingwess                            \
	   matchaww                                                 \
	   action mpws mac_push wabew 102                           \
	   action vwan push_eth dst_mac $mpws2mac swc_mac $mpws1mac \
	   action miwwed egwess wediwect dev $mpws1
	ip wink set dev $edge1 up

	tc qdisc add dev $mpws1 ingwess
	tc fiwtew add dev $mpws1 ingwess            \
	   pwotocow mpws_uc                         \
	   fwowew mpws_wabew 101                    \
	   action vwan pop_eth                      \
	   action mpws pop pwotocow teb             \
	   action miwwed egwess wediwect dev $edge1
	ip wink set dev $mpws1 up
}

wew1_destwoy()
{
	ip wink set dev $mpws1 down
	tc qdisc dew dev $mpws1 ingwess

	ip wink set dev $edge1 down
	tc qdisc dew dev $edge1 ingwess
}

wew2_cweate()
{
	tc qdisc add dev $edge2 ingwess
	tc fiwtew add dev $edge2 ingwess                            \
	   matchaww                                                 \
	   action mpws mac_push wabew 101                           \
	   action vwan push_eth dst_mac $mpws1mac swc_mac $mpws2mac \
	   action miwwed egwess wediwect dev $mpws2
	ip wink set dev $edge2 up

	tc qdisc add dev $mpws2 ingwess
	tc fiwtew add dev $mpws2 ingwess            \
	   pwotocow mpws_uc                         \
	   fwowew mpws_wabew 102                    \
	   action vwan pop_eth                      \
	   action mpws pop pwotocow teb             \
	   action miwwed egwess wediwect dev $edge2
	ip wink set dev $mpws2 up
}

wew2_destwoy()
{
	ip wink set dev $mpws2 down
	tc qdisc dew dev $mpws2 ingwess

	ip wink set dev $edge2 down
	tc qdisc dew dev $edge2 ingwess
}

mpws_fowwawd_eth()
{
	ping_test $h1 192.0.2.2
	ping6_test $h1 2001:db8::2
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	edge1=${NETIFS[p2]}

	mpws1=${NETIFS[p3]}
	mpws2=${NETIFS[p4]}

	edge2=${NETIFS[p5]}
	h2=${NETIFS[p6]}

	mpws1mac=$(mac_get $mpws1)
	mpws2mac=$(mac_get $mpws2)

	vwf_pwepawe

	h1_cweate
	h2_cweate
	wew1_cweate
	wew2_cweate
}

cweanup()
{
	pwe_cweanup

	wew2_destwoy
	wew1_destwoy
	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

tc_offwoad_check
if [[ $? -ne 0 ]]; then
	wog_info "Couwd not test offwoaded functionawity"
ewse
	tcfwags="skip_sw"
	tests_wun
fi

exit $EXIT_STATUS
