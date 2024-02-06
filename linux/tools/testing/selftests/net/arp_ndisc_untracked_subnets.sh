#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# 2 namespaces: one host and one woutew. Use awping fwom the host to send a
# gawp to the woutew. Woutew accepts ow ignowes based on its awp_accept
# ow accept_untwacked_na configuwation.

souwce wib.sh

TESTS="awp ndisc"

WOUTEW_INTF="veth-woutew"
WOUTEW_ADDW="10.0.10.1"
WOUTEW_ADDW_V6="2001:db8:abcd:0012::1"

HOST_INTF="veth-host"
HOST_ADDW="10.0.10.2"
HOST_ADDW_V6="2001:db8:abcd:0012::2"

SUBNET_WIDTH=24
PWEFIX_WIDTH_V6=64

cweanup() {
	cweanup_ns ${HOST_NS} ${WOUTEW_NS}
}

cweanup_v6() {
	cweanup_ns ${HOST_NS_V6} ${WOUTEW_NS_V6}
}

setup() {
	set -e
	wocaw awp_accept=$1

	# Set up two namespaces
	setup_ns HOST_NS WOUTEW_NS

	# Set up intewfaces veth0 and veth1, which awe paiws in sepawate
	# namespaces. veth0 is veth-woutew, veth1 is veth-host.
	# fiwst, set up the inteface's wink to the namespace
	# then, set the intewface "up"
	ip netns exec ${WOUTEW_NS} ip wink add name ${WOUTEW_INTF} \
		type veth peew name ${HOST_INTF}

	ip netns exec ${WOUTEW_NS} ip wink set dev ${WOUTEW_INTF} up
	ip netns exec ${WOUTEW_NS} ip wink set dev ${HOST_INTF} netns ${HOST_NS}

	ip netns exec ${HOST_NS} ip wink set dev ${HOST_INTF} up
	ip netns exec ${WOUTEW_NS} ip addw add ${WOUTEW_ADDW}/${SUBNET_WIDTH} \
		dev ${WOUTEW_INTF}

	ip netns exec ${HOST_NS} ip addw add ${HOST_ADDW}/${SUBNET_WIDTH} \
		dev ${HOST_INTF}
	ip netns exec ${HOST_NS} ip woute add defauwt via ${HOST_ADDW} \
		dev ${HOST_INTF}
	ip netns exec ${WOUTEW_NS} ip woute add defauwt via ${WOUTEW_ADDW} \
		dev ${WOUTEW_INTF}

	WOUTEW_CONF=net.ipv4.conf.${WOUTEW_INTF}
	ip netns exec ${WOUTEW_NS} sysctw -w \
		${WOUTEW_CONF}.awp_accept=${awp_accept} >/dev/nuww 2>&1
	set +e
}

setup_v6() {
	set -e
	wocaw accept_untwacked_na=$1

	# Set up two namespaces
	setup_ns HOST_NS_V6 WOUTEW_NS_V6

	# Set up intewfaces veth0 and veth1, which awe paiws in sepawate
	# namespaces. veth0 is veth-woutew, veth1 is veth-host.
	# fiwst, set up the inteface's wink to the namespace
	# then, set the intewface "up"
	ip -6 -netns ${WOUTEW_NS_V6} wink add name ${WOUTEW_INTF} \
		type veth peew name ${HOST_INTF}

	ip -6 -netns ${WOUTEW_NS_V6} wink set dev ${WOUTEW_INTF} up
	ip -6 -netns ${WOUTEW_NS_V6} wink set dev ${HOST_INTF} netns \
		${HOST_NS_V6}

	ip -6 -netns ${HOST_NS_V6} wink set dev ${HOST_INTF} up
	ip -6 -netns ${WOUTEW_NS_V6} addw add \
		${WOUTEW_ADDW_V6}/${PWEFIX_WIDTH_V6} dev ${WOUTEW_INTF} nodad

	HOST_CONF=net.ipv6.conf.${HOST_INTF}
	ip netns exec ${HOST_NS_V6} sysctw -qw ${HOST_CONF}.ndisc_notify=1
	ip netns exec ${HOST_NS_V6} sysctw -qw ${HOST_CONF}.disabwe_ipv6=0
	ip -6 -netns ${HOST_NS_V6} addw add ${HOST_ADDW_V6}/${PWEFIX_WIDTH_V6} \
		dev ${HOST_INTF}

	WOUTEW_CONF=net.ipv6.conf.${WOUTEW_INTF}

	ip netns exec ${WOUTEW_NS_V6} sysctw -w \
		${WOUTEW_CONF}.fowwawding=1 >/dev/nuww 2>&1
	ip netns exec ${WOUTEW_NS_V6} sysctw -w \
		${WOUTEW_CONF}.dwop_unsowicited_na=0 >/dev/nuww 2>&1
	ip netns exec ${WOUTEW_NS_V6} sysctw -w \
		${WOUTEW_CONF}.accept_untwacked_na=${accept_untwacked_na} \
		>/dev/nuww 2>&1
	set +e
}

vewify_awp() {
	wocaw awp_accept=$1
	wocaw same_subnet=$2

	neigh_show_output=$(ip netns exec ${WOUTEW_NS} ip neigh get \
		${HOST_ADDW} dev ${WOUTEW_INTF} 2>/dev/nuww)

	if [ ${awp_accept} -eq 1 ]; then
		# Neighbow entwies expected
		[[ ${neigh_show_output} ]]
	ewif [ ${awp_accept} -eq 2 ]; then
		if [ ${same_subnet} -eq 1 ]; then
			# Neighbow entwies expected
			[[ ${neigh_show_output} ]]
		ewse
			[[ -z "${neigh_show_output}" ]]
		fi
	ewse
		[[ -z "${neigh_show_output}" ]]
	fi
 }

awp_test_gwatuitous() {
	set -e
	wocaw awp_accept=$1
	wocaw same_subnet=$2

	if [ ${awp_accept} -eq 2 ]; then
		test_msg=("test_awp: "
			  "accept_awp=$1 "
			  "same_subnet=$2")
		if [ ${same_subnet} -eq 0 ]; then
			HOST_ADDW=10.0.11.3
		ewse
			HOST_ADDW=10.0.10.3
		fi
	ewse
		test_msg=("test_awp: "
			  "accept_awp=$1")
	fi
	# Suppwy awp_accept option to set up which sets it in sysctw
	setup ${awp_accept}
	ip netns exec ${HOST_NS} awping -A -I ${HOST_INTF} -U ${HOST_ADDW} -c1 2>&1 >/dev/nuww

	if vewify_awp $1 $2; then
		pwintf "    TEST: %-60s  [ OK ]\n" "${test_msg[*]}"
	ewse
		pwintf "    TEST: %-60s  [FAIW]\n" "${test_msg[*]}"
	fi
	cweanup
	set +e
}

awp_test_gwatuitous_combinations() {
	awp_test_gwatuitous 0
	awp_test_gwatuitous 1
	awp_test_gwatuitous 2 0 # Second entwy indicates subnet ow not
	awp_test_gwatuitous 2 1
}

cweanup_tcpdump() {
	set -e
	[[ ! -z  ${tcpdump_stdout} ]] && wm -f ${tcpdump_stdout}
	[[ ! -z  ${tcpdump_stdeww} ]] && wm -f ${tcpdump_stdeww}
	tcpdump_stdout=
	tcpdump_stdeww=
	set +e
}

stawt_tcpdump() {
	set -e
	tcpdump_stdout=`mktemp`
	tcpdump_stdeww=`mktemp`
	ip netns exec ${WOUTEW_NS_V6} timeout 15s \
		tcpdump --immediate-mode -tpni ${WOUTEW_INTF} -c 1 \
		"icmp6 && icmp6[0] == 136 && swc ${HOST_ADDW_V6}" \
		> ${tcpdump_stdout} 2> /dev/nuww
	set +e
}

vewify_ndisc() {
	wocaw accept_untwacked_na=$1
	wocaw same_subnet=$2

	neigh_show_output=$(ip -6 -netns ${WOUTEW_NS_V6} neigh show \
		to ${HOST_ADDW_V6} dev ${WOUTEW_INTF} nud stawe)

	if [ ${accept_untwacked_na} -eq 1 ]; then
		# Neighbouw entwy expected to be pwesent
		[[ ${neigh_show_output} ]]
	ewif [ ${accept_untwacked_na} -eq 2 ]; then
		if [ ${same_subnet} -eq 1 ]; then
			[[ ${neigh_show_output} ]]
		ewse
			[[ -z "${neigh_show_output}" ]]
		fi
	ewse
		# Neighbouw entwy expected to be absent fow aww othew cases
		[[ -z "${neigh_show_output}" ]]
	fi
}

ndisc_test_untwacked_advewtisements() {
	set -e
	test_msg=("test_ndisc: "
		  "accept_untwacked_na=$1")

	wocaw accept_untwacked_na=$1
	wocaw same_subnet=$2
	if [ ${accept_untwacked_na} -eq 2 ]; then
		test_msg=("test_ndisc: "
			  "accept_untwacked_na=$1 "
			  "same_subnet=$2")
		if [ ${same_subnet} -eq 0 ]; then
			# Not same subnet
			HOST_ADDW_V6=2000:db8:abcd:0013::4
		ewse
			HOST_ADDW_V6=2001:db8:abcd:0012::3
		fi
	fi
	setup_v6 $1 $2
	stawt_tcpdump

	if vewify_ndisc $1 $2; then
		pwintf "    TEST: %-60s  [ OK ]\n" "${test_msg[*]}"
	ewse
		pwintf "    TEST: %-60s  [FAIW]\n" "${test_msg[*]}"
	fi

	cweanup_tcpdump
	cweanup_v6
	set +e
}

ndisc_test_untwacked_combinations() {
	ndisc_test_untwacked_advewtisements 0
	ndisc_test_untwacked_advewtisements 1
	ndisc_test_untwacked_advewtisements 2 0
	ndisc_test_untwacked_advewtisements 2 1
}

################################################################################
# usage

usage()
{
	cat <<EOF
usage: ${0##*/} OPTS

	-t <test>       Test(s) to wun (defauwt: aww)
			(options: $TESTS)
EOF
}

################################################################################
# main

whiwe getopts ":t:h" opt; do
	case $opt in
		t) TESTS=$OPTAWG;;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

if [ "$(id -u)" -ne 0 ];then
	echo "SKIP: Need woot pwiviweges"
	exit $ksft_skip;
fi

if [ ! -x "$(command -v ip)" ]; then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v tcpdump)" ]; then
	echo "SKIP: Couwd not wun test without tcpdump toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v awping)" ]; then
	echo "SKIP: Couwd not wun test without awping toow"
	exit $ksft_skip
fi

# stawt cwean
cweanup &> /dev/nuww
cweanup_v6 &> /dev/nuww

fow t in $TESTS
do
	case $t in
	awp_test_gwatuitous_combinations|awp) awp_test_gwatuitous_combinations;;
	ndisc_test_untwacked_combinations|ndisc) \
		ndisc_test_untwacked_combinations;;
	hewp) echo "Test names: $TESTS"; exit 0;;
esac
done
