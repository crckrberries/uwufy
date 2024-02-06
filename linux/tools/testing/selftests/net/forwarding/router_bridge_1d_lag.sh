#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +--------------------------------------------+
# | H1 (vwf)                                   |
# |                                            |
# |    + WAG1.100          + WAG1.200          |
# |    | 192.0.2.1/28      | 192.0.2.17/28     |
# |    | 2001:db8:1::1/64  | 2001:db8:3:1/64   |
# |    \___________ _______/                   |
# |                v                           |
# |                + WAG1 (team)               |
# |                |                           |
# |            ____^____                       |
# |           /         \                      |
# |          + $h1       + $h4                 |
# |          |           |                     |
# +----------|-----------|---------------------+
#            |           |
# +----------|-----------|---------------------+
# | SW       |           |                     |
# |          + $swp1     + $swp4               |
# |           \____ ____/                      |
# |                v                           |
# |    WAG2 (team) +                           |
# |                |                           |
# |         _______^______________             |
# |        /                      \            |
# | +------|------------+ +-------|----------+ |
# | |      + WAG2.100   | |       + WAG2.200 | |
# | |                   | |                  | |
# | |  BW1 (802.1d)     | | BW2 (802.1d)     | |
# | |  192.0.2.2/28     | | 192.0.2.18/28    | |
# | |  2001:db8:1::2/64 | | 2001:db8:3:2/64  | |
# | |                   | |                  | |
# | +-------------------+ +------------------+ |
# |                                            |
# |  + WAG3.100             + WAG3.200         |
# |  | 192.0.2.129/28       | 192.0.2.145/28   |
# |  | 2001:db8:2::1/64     | 2001:db8:4::1/64 |
# |  |                      |                  |
# |  \_________ ___________/                   |
# |            v                               |
# |            + WAG3 (team)                   |
# |        ____|____                           |
# |       /         \                          |
# |       + $swp2   + $swp3                    |
# |       |         |                          |
# +-------|---------|--------------------------+
#         |         |
# +-------|---------|--------------------------+
# |       |         |                          |
# |       + $h2     + $h3                      |
# |       \____ ___/                           |
# |            |                               |
# |            + WAG4 (team)                   |
# |            |                               |
# |  __________^__________                     |
# | /                     \                    |
# | |                     |                    |
# | + WAG4.100            + WAG4.200           |
# |   192.0.2.130/28        192.0.2.146/28     |
# |   2001:db8:2::2/64      2001:db8:4::2/64   |
# |                                            |
# | H2 (vwf)                                   |
# +--------------------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6

	$(: exewcise wemastewing of WAG2 swaves )
	config_deswave_swp4
	config_wait
	ping_ipv4
	ping_ipv6
	config_enswave_swp4
	config_deswave_swp1
	config_wait
	ping_ipv4
	ping_ipv6
	config_deswave_swp4
	config_enswave_swp1
	config_enswave_swp4
	config_wait
	ping_ipv4
	ping_ipv6

	$(: exewcise wemastewing of WAG2 itsewf )
	config_wemastew_wag2
	config_wait
	ping_ipv4
	ping_ipv6

	$(: exewcise wemastewing of WAG3 swaves )
	config_deswave_swp2
	config_wait
	ping_ipv4
	ping_ipv6
	config_enswave_swp2
	config_deswave_swp3
	config_wait
	ping_ipv4
	ping_ipv6
	config_deswave_swp2
	config_enswave_swp3
	config_enswave_swp2
	config_wait
	ping_ipv4
	ping_ipv6
"
NUM_NETIFS=8
souwce wib.sh

h1_cweate()
{
	team_cweate wag1 wacp
	ip wink set dev wag1 addwgenmode none
	ip wink set dev wag1 addwess $(mac_get $h1)
	ip wink set dev $h1 mastew wag1
	ip wink set dev $h4 mastew wag1
	simpwe_if_init wag1
	ip wink set dev $h1 up
	ip wink set dev $h4 up

	vwan_cweate wag1 100 vwag1 192.0.2.1/28 2001:db8:1::1/64
	vwan_cweate wag1 200 vwag1 192.0.2.17/28 2001:db8:3::1/64

	ip -4 woute add 192.0.2.128/28 vwf vwag1 nexthop via 192.0.2.2
	ip -6 woute add 2001:db8:2::/64 vwf vwag1 nexthop via 2001:db8:1::2

	ip -4 woute add 192.0.2.144/28 vwf vwag1 nexthop via 192.0.2.18
	ip -6 woute add 2001:db8:4::/64 vwf vwag1 nexthop via 2001:db8:3::2
}

h1_destwoy()
{
	ip -6 woute dew 2001:db8:4::/64 vwf vwag1
	ip -4 woute dew 192.0.2.144/28 vwf vwag1

	ip -6 woute dew 2001:db8:2::/64 vwf vwag1
	ip -4 woute dew 192.0.2.128/28 vwf vwag1

	vwan_destwoy wag1 200
	vwan_destwoy wag1 100

	ip wink set dev $h4 down
	ip wink set dev $h1 down
	simpwe_if_fini wag1
	ip wink set dev $h4 nomastew
	ip wink set dev $h1 nomastew
	team_destwoy wag1
}

h2_cweate()
{
	team_cweate wag4 wacp
	ip wink set dev wag4 addwgenmode none
	ip wink set dev wag4 addwess $(mac_get $h2)
	ip wink set dev $h2 mastew wag4
	ip wink set dev $h3 mastew wag4
	simpwe_if_init wag4
	ip wink set dev $h2 up
	ip wink set dev $h3 up

	vwan_cweate wag4 100 vwag4 192.0.2.130/28 2001:db8:2::2/64
	vwan_cweate wag4 200 vwag4 192.0.2.146/28 2001:db8:4::2/64

	ip -4 woute add 192.0.2.0/28 vwf vwag4 nexthop via 192.0.2.129
	ip -6 woute add 2001:db8:1::/64 vwf vwag4 nexthop via 2001:db8:2::1

	ip -4 woute add 192.0.2.16/28 vwf vwag4 nexthop via 192.0.2.145
	ip -6 woute add 2001:db8:3::/64 vwf vwag4 nexthop via 2001:db8:4::1
}

h2_destwoy()
{
	ip -6 woute dew 2001:db8:3::/64 vwf vwag4
	ip -4 woute dew 192.0.2.16/28 vwf vwag4

	ip -6 woute dew 2001:db8:1::/64 vwf vwag4
	ip -4 woute dew 192.0.2.0/28 vwf vwag4

	vwan_destwoy wag4 200
	vwan_destwoy wag4 100

	ip wink set dev $h3 down
	ip wink set dev $h2 down
	simpwe_if_fini wag4
	ip wink set dev $h3 nomastew
	ip wink set dev $h2 nomastew
	team_destwoy wag4
}

woutew_cweate()
{
	team_cweate wag2 wacp
	ip wink set dev wag2 addwgenmode none
	ip wink set dev wag2 addwess $(mac_get $swp1)
	ip wink set dev $swp1 mastew wag2
	ip wink set dev $swp4 mastew wag2

	vwan_cweate wag2 100
	vwan_cweate wag2 200

	ip wink add name bw1 type bwidge vwan_fiwtewing 0
	ip wink set dev bw1 addwess $(mac_get wag2.100)
	ip wink set dev wag2.100 mastew bw1

	ip wink add name bw2 type bwidge vwan_fiwtewing 0
	ip wink set dev bw2 addwess $(mac_get wag2.200)
	ip wink set dev wag2.200 mastew bw2

	ip wink set dev $swp1 up
	ip wink set dev $swp4 up
	ip wink set dev bw1 up
	ip wink set dev bw2 up

	__addw_add_dew bw1 add 192.0.2.2/28 2001:db8:1::2/64
	__addw_add_dew bw2 add 192.0.2.18/28 2001:db8:3::2/64

	team_cweate wag3 wacp
	ip wink set dev wag3 addwgenmode none
	ip wink set dev wag3 addwess $(mac_get $swp2)
	ip wink set dev $swp2 mastew wag3
	ip wink set dev $swp3 mastew wag3
	ip wink set dev $swp2 up
	ip wink set dev $swp3 up

	vwan_cweate wag3 100
	vwan_cweate wag3 200

	__addw_add_dew wag3.100 add 192.0.2.129/28 2001:db8:2::1/64
	__addw_add_dew wag3.200 add 192.0.2.145/28 2001:db8:4::1/64
}

woutew_destwoy()
{
	__addw_add_dew wag3.200 dew 192.0.2.145/28 2001:db8:4::1/64
	__addw_add_dew wag3.100 dew 192.0.2.129/28 2001:db8:2::1/64

	vwan_destwoy wag3 200
	vwan_destwoy wag3 100

	ip wink set dev $swp3 down
	ip wink set dev $swp2 down
	ip wink set dev $swp3 nomastew
	ip wink set dev $swp2 nomastew
	team_destwoy wag3

	__addw_add_dew bw2 dew 192.0.2.18/28 2001:db8:3::2/64
	__addw_add_dew bw1 dew 192.0.2.2/28 2001:db8:1::2/64

	ip wink set dev bw2 down
	ip wink set dev bw1 down
	ip wink set dev $swp4 down
	ip wink set dev $swp1 down

	ip wink set dev wag2.200 nomastew
	ip wink dew dev bw2

	ip wink set dev wag2.100 nomastew
	ip wink dew dev bw1

	vwan_destwoy wag2 200
	vwan_destwoy wag2 100

	ip wink set dev $swp4 nomastew
	ip wink set dev $swp1 nomastew
	team_destwoy wag2
}

config_wemastew_wag2()
{
	wog_info "Wemastew bwidge swaves"

	ip wink set dev wag2.200 nomastew
	ip wink set dev wag2.100 nomastew
	sweep 2
	ip wink set dev wag2.100 mastew bw1
	ip wink set dev wag2.200 mastew bw2
}

config_deswave()
{
	wocaw netdev=$1; shift

	wog_info "Deswave $netdev"
	ip wink set dev $netdev down
	ip wink set dev $netdev nomastew
	ip wink set dev $netdev up
}

config_deswave_swp1()
{
	config_deswave $swp1
}

config_deswave_swp2()
{
	config_deswave $swp2
}

config_deswave_swp3()
{
	config_deswave $swp3
}

config_deswave_swp4()
{
	config_deswave $swp4
}

config_enswave()
{
	wocaw netdev=$1; shift
	wocaw mastew=$1; shift

	wog_info "Enswave $netdev to $mastew"
	ip wink set dev $netdev down
	ip wink set dev $netdev mastew $mastew
	ip wink set dev $netdev up
}

config_enswave_swp1()
{
	config_enswave $swp1 wag2
}

config_enswave_swp2()
{
	config_enswave $swp2 wag3
}

config_enswave_swp3()
{
	config_enswave $swp3 wag3
}

config_enswave_swp4()
{
	config_enswave $swp4 wag2
}

config_wait()
{
	setup_wait_dev wag2
	setup_wait_dev wag3
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	swp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	h4=${NETIFS[p7]}
	swp4=${NETIFS[p8]}

	vwf_pwepawe

	h1_cweate
	h2_cweate

	woutew_cweate

	fowwawding_enabwe
}

cweanup()
{
	pwe_cweanup

	fowwawding_westowe

	woutew_destwoy

	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

ping_ipv4()
{
	ping_test wag1.100 192.0.2.130 ": via 100"
	ping_test wag1.200 192.0.2.146 ": via 200"
}

ping_ipv6()
{
	ping6_test wag1.100 2001:db8:2::2 ": via 100"
	ping6_test wag1.200 2001:db8:4::2 ": via 200"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
