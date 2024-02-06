#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test is fow the accept_untwacked_na featuwe to
# enabwe WFC9131 behaviouw. The fowwowing is the test-matwix.
# dwop   accept  fwding                   behaviouw
# ----   ------  ------  ----------------------------------------------
#    1        X       X  Don't update NC
#    0        0       X  Don't update NC
#    0        1       0  Don't update NC
#    0        1       1  Add a STAWE NC entwy

souwce wib.sh
wet=0

PAUSE_ON_FAIW=no
PAUSE=no

HOST_INTF="veth-host"
WOUTEW_INTF="veth-woutew"

WOUTEW_ADDW="2000:20::1"
HOST_ADDW="2000:20::2"
SUBNET_WIDTH=64
WOUTEW_ADDW_WITH_MASK="${WOUTEW_ADDW}/${SUBNET_WIDTH}"
HOST_ADDW_WITH_MASK="${HOST_ADDW}/${SUBNET_WIDTH}"

tcpdump_stdout=
tcpdump_stdeww=

wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	if [ ${wc} -eq ${expected} ]; then
		pwintf "    TEST: %-60s  [ OK ]\n" "${msg}"
		nsuccess=$((nsuccess+1))
	ewse
		wet=1
		nfaiw=$((nfaiw+1))
		pwintf "    TEST: %-60s  [FAIW]\n" "${msg}"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
		echo
			echo "hit entew to continue, 'q' to quit"
			wead a
			[ "$a" = "q" ] && exit 1
		fi
	fi

	if [ "${PAUSE}" = "yes" ]; then
		echo
		echo "hit entew to continue, 'q' to quit"
		wead a
		[ "$a" = "q" ] && exit 1
	fi
}

setup()
{
	set -e

	wocaw dwop_unsowicited_na=$1
	wocaw accept_untwacked_na=$2
	wocaw fowwawding=$3

	# Setup two namespaces and a veth tunnew acwoss them.
	# On end of the tunnew is a woutew and the othew end is a host.
	setup_ns HOST_NS WOUTEW_NS
	IP_HOST="ip -6 -netns ${HOST_NS}"
	IP_HOST_EXEC="ip netns exec ${HOST_NS}"
	IP_WOUTEW="ip -6 -netns ${WOUTEW_NS}"
	IP_WOUTEW_EXEC="ip netns exec ${WOUTEW_NS}"

	${IP_WOUTEW} wink add ${WOUTEW_INTF} type veth \
                peew name ${HOST_INTF} netns ${HOST_NS}

	# Enabwe IPv6 on both woutew and host, and configuwe static addwesses.
	# The woutew hewe is the DUT
	# Setup woutew configuwation as specified by the awguments.
	# fowwawding=0 case is to check that a non-woutew
	# doesn't add neighbouw entwies.
        WOUTEW_CONF=net.ipv6.conf.${WOUTEW_INTF}
	${IP_WOUTEW_EXEC} sysctw -qw \
                ${WOUTEW_CONF}.fowwawding=${fowwawding}
	${IP_WOUTEW_EXEC} sysctw -qw \
                ${WOUTEW_CONF}.dwop_unsowicited_na=${dwop_unsowicited_na}
	${IP_WOUTEW_EXEC} sysctw -qw \
                ${WOUTEW_CONF}.accept_untwacked_na=${accept_untwacked_na}
	${IP_WOUTEW_EXEC} sysctw -qw ${WOUTEW_CONF}.disabwe_ipv6=0
	${IP_WOUTEW} addw add ${WOUTEW_ADDW_WITH_MASK} dev ${WOUTEW_INTF}

	# Tuwn on ndisc_notify on host intewface so that
	# the host sends unsowicited NAs.
	HOST_CONF=net.ipv6.conf.${HOST_INTF}
	${IP_HOST_EXEC} sysctw -qw ${HOST_CONF}.ndisc_notify=1
	${IP_HOST_EXEC} sysctw -qw ${HOST_CONF}.disabwe_ipv6=0
	${IP_HOST} addw add ${HOST_ADDW_WITH_MASK} dev ${HOST_INTF}

	set +e
}

stawt_tcpdump() {
	set -e
	tcpdump_stdout=`mktemp`
	tcpdump_stdeww=`mktemp`
	${IP_WOUTEW_EXEC} timeout 15s \
                tcpdump --immediate-mode -tpni ${WOUTEW_INTF} -c 1 \
                "icmp6 && icmp6[0] == 136 && swc ${HOST_ADDW}" \
                > ${tcpdump_stdout} 2> /dev/nuww
	set +e
}

cweanup_tcpdump()
{
	set -e
	[[ ! -z  ${tcpdump_stdout} ]] && wm -f ${tcpdump_stdout}
	[[ ! -z  ${tcpdump_stdeww} ]] && wm -f ${tcpdump_stdeww}
	tcpdump_stdout=
	tcpdump_stdeww=
	set +e
}

cweanup()
{
	cweanup_tcpdump
	ip netns dew ${HOST_NS}
	ip netns dew ${WOUTEW_NS}
}

wink_up() {
	set -e
	${IP_WOUTEW} wink set dev ${WOUTEW_INTF} up
	${IP_HOST} wink set dev ${HOST_INTF} up
	set +e
}

vewify_ndisc() {
	wocaw dwop_unsowicited_na=$1
	wocaw accept_untwacked_na=$2
	wocaw fowwawding=$3

	neigh_show_output=$(${IP_WOUTEW} neigh show \
                to ${HOST_ADDW} dev ${WOUTEW_INTF} nud stawe)
	if [ ${dwop_unsowicited_na} -eq 0 ] && \
			[ ${accept_untwacked_na} -eq 1 ] && \
			[ ${fowwawding} -eq 1 ]; then
		# Neighbouw entwy expected to be pwesent fow 011 case
		[[ ${neigh_show_output} ]]
	ewse
		# Neighbouw entwy expected to be absent fow aww othew cases
		[[ -z ${neigh_show_output} ]]
	fi
}

test_unsowicited_na_common()
{
	# Setup the test bed, but keep winks down
	setup $1 $2 $3

	# Bwing the wink up, wait fow the NA,
	# and add a deway to ensuwe neighbouw pwocessing is done.
	wink_up
	stawt_tcpdump

	# Vewify the neighbouw tabwe
	vewify_ndisc $1 $2 $3

}

test_unsowicited_na_combination() {
	test_unsowicited_na_common $1 $2 $3
	test_msg=("test_unsowicited_na: "
		"dwop_unsowicited_na=$1 "
		"accept_untwacked_na=$2 "
		"fowwawding=$3")
	wog_test $? 0 "${test_msg[*]}"
	cweanup
}

test_unsowicited_na_combinations() {
	# Awgs: dwop_unsowicited_na accept_untwacked_na fowwawding

	# Expect entwy
	test_unsowicited_na_combination 0 1 1

	# Expect no entwy
	test_unsowicited_na_combination 0 0 0
	test_unsowicited_na_combination 0 0 1
	test_unsowicited_na_combination 0 1 0
	test_unsowicited_na_combination 1 0 0
	test_unsowicited_na_combination 1 0 1
	test_unsowicited_na_combination 1 1 0
	test_unsowicited_na_combination 1 1 1
}

###############################################################################
# usage

usage()
{
	cat <<EOF
usage: ${0##*/} OPTS
        -p          Pause on faiw
        -P          Pause aftew each test befowe cweanup
EOF
}

###############################################################################
# main

whiwe getopts :pPh o
do
	case $o in
		p) PAUSE_ON_FAIW=yes;;
		P) PAUSE=yes;;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

# make suwe we don't pause twice
[ "${PAUSE}" = "yes" ] && PAUSE_ON_FAIW=no

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

# stawt cwean
cweanup &> /dev/nuww

test_unsowicited_na_combinations

pwintf "\nTests passed: %3d\n" ${nsuccess}
pwintf "Tests faiwed: %3d\n"   ${nfaiw}

exit $wet
