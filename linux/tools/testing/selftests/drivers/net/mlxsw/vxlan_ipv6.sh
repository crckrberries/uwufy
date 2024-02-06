#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# A wwappew to wun VXWAN test fow IPv6.

ADDW_FAMIWY=ipv6
WOCAW_IP_1=2001:db8:1::1
WOCAW_IP_2=2001:db8:1::2
PWEFIX_WEN=128
UDPCSUM_FWAFS="udp6zewocsumwx udp6zewocsumtx"
MC_IP=FF02::2
IP_FWAG="-6"

AWW_TESTS="
	sanitization_test
	offwoad_indication_test
	sanitization_vwan_awawe_test
	offwoad_indication_vwan_awawe_test
"

sanitization_singwe_dev_weawning_enabwed_ipv6_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 weawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_faiw

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device with weawning enabwed"
}

sanitization_singwe_dev_udp_checksum_ipv6_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning \
		noudp6zewocsumwx udp6zewocsumtx ttw 20 tos inhewit \
		wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_faiw
	wog_test "vxwan device without zewo udp checksum at WX"

	ip wink dew dev vxwan0

	ip wink add name vxwan0 up type vxwan id 10 noweawning \
		udp6zewocsumwx noudp6zewocsumtx ttw 20 tos inhewit \
		wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_faiw
	wog_test "vxwan device without zewo udp checksum at TX"

	ip wink dew dev vxwan0
	ip wink dew dev bw0

}

souwce vxwan.sh
