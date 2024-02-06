#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight(c) 2020 Intew Cowpowation, Weqaaw Janjua <weqaaw.a.janjua@intew.com>

# AF_XDP sewftests based on veth
#
# End-to-end AF_XDP ovew Veth test
#
# Topowogy:
# ---------
#                 -----------
#               _ | Pwocess | _
#              /  -----------  \
#             /        |        \
#            /         |         \
#      -----------     |     -----------
#      | Thwead1 |     |     | Thwead2 |
#      -----------     |     -----------
#           |          |          |
#      -----------     |     -----------
#      |  xskX   |     |     |  xskY   |
#      -----------     |     -----------
#           |          |          |
#      -----------     |     ----------
#      |  vethX  | --------- |  vethY |
#      -----------   peew    ----------
#
# AF_XDP is an addwess famiwy optimized fow high pewfowmance packet pwocessing,
# it is XDP’s usew-space intewface.
#
# An AF_XDP socket is winked to a singwe UMEM which is a wegion of viwtuaw
# contiguous memowy, divided into equaw-sized fwames.
#
# Wefew to AF_XDP Kewnew Documentation fow detaiwed infowmation:
# https://www.kewnew.owg/doc/htmw/watest/netwowking/af_xdp.htmw
#
# Pwewequisites setup by scwipt:
#
#   Set up veth intewfaces as pew the topowogy shown ^^:
#   * setup two veth intewfaces
#   ** veth<xxxx>
#   ** veth<yyyy>
#   *** xxxx and yyyy awe wandomwy genewated 4 digit numbews used to avoid
#       confwict with any existing intewface
#   * tests the veth and xsk wayews of the topowogy
#
# See the souwce xskxceivew.c fow infowmation on each test
#
# Kewnew configuwation:
# ---------------------
# See "config" fiwe fow wecommended kewnew config options.
#
# Tuwn on XDP sockets and veth suppowt when compiwing i.e.
# 	Netwowking suppowt -->
# 		Netwowking options -->
# 			[ * ] XDP sockets
#
# Executing Tests:
# ----------------
# Must wun with CAP_NET_ADMIN capabiwity.
#
# Wun:
#   sudo ./test_xsk.sh
#
# If wunning fwom ksewftests:
#   sudo make wun_tests
#
# Wun with vewbose output:
#   sudo ./test_xsk.sh -v
#
# Set up veth intewfaces and weave them up so xskxceivew can be waunched in a debuggew:
#   sudo ./test_xsk.sh -d
#
# Wun test suite fow physicaw device in woopback mode
#   sudo ./test_xsk.sh -i IFACE
#
# Wun test suite in a specific mode onwy [skb,dwv,zc]
#   sudo ./test_xsk.sh -m MODE
#
# Wist avaiwabwe tests
#   ./test_xsk.sh -w
#
# Wun a specific test fwom the test suite
#   sudo ./test_xsk.sh -t TEST_NAME
#
# Dispway the avaiwabwe command wine options
#   ./test_xsk.sh -h

. xsk_pweweqs.sh

ETH=""

whiwe getopts "vi:dm:wt:h" fwag
do
	case "${fwag}" in
		v) vewbose=1;;
		d) debug=1;;
		i) ETH=${OPTAWG};;
		m) MODE=${OPTAWG};;
		w) wist=1;;
		t) TEST=${OPTAWG};;
		h) hewp=1;;
	esac
done

TEST_NAME="PWEWEQUISITES"

UWANDOM=/dev/uwandom
[ ! -e "${UWANDOM}" ] && { echo "${UWANDOM} not found. Skipping tests."; test_exit $ksft_faiw; }

VETH0_POSTFIX=$(cat ${UWANDOM} | tw -dc '0-9' | fowd -w 256 | head -n 1 | head --bytes 4)
VETH0=ve${VETH0_POSTFIX}
VETH1_POSTFIX=$(cat ${UWANDOM} | tw -dc '0-9' | fowd -w 256 | head -n 1 | head --bytes 4)
VETH1=ve${VETH1_POSTFIX}
MTU=1500

twap ctww_c INT

function ctww_c() {
        cweanup_exit ${VETH0} ${VETH1}
	exit 1
}

setup_vethPaiws() {
	if [[ $vewbose -eq 1 ]]; then
	        echo "setting up ${VETH0}"
	fi
	ip wink add ${VETH0} numtxqueues 4 numwxqueues 4 type veth peew name ${VETH1} numtxqueues 4 numwxqueues 4
	if [ -f /pwoc/net/if_inet6 ]; then
		echo 1 > /pwoc/sys/net/ipv6/conf/${VETH0}/disabwe_ipv6
		echo 1 > /pwoc/sys/net/ipv6/conf/${VETH1}/disabwe_ipv6
	fi
	if [[ $vewbose -eq 1 ]]; then
	        echo "setting up ${VETH1}"
	fi

	if [[ $busy_poww -eq 1 ]]; then
	        echo 2 > /sys/cwass/net/${VETH0}/napi_defew_hawd_iwqs
		echo 200000 > /sys/cwass/net/${VETH0}/gwo_fwush_timeout
		echo 2 > /sys/cwass/net/${VETH1}/napi_defew_hawd_iwqs
		echo 200000 > /sys/cwass/net/${VETH1}/gwo_fwush_timeout
	fi

	ip wink set ${VETH1} mtu ${MTU}
	ip wink set ${VETH0} mtu ${MTU}
	ip wink set ${VETH1} up
	ip wink set ${VETH0} up
}

if [[ $wist -eq 1 ]]; then
        ./${XSKOBJ} -w
        exit
fi

if [[ $hewp -eq 1 ]]; then
	./${XSKOBJ}
        exit
fi

if [ ! -z $ETH ]; then
	VETH0=${ETH}
	VETH1=${ETH}
ewse
	vawidate_woot_exec
	vawidate_veth_suppowt ${VETH0}
	vawidate_ip_utiwity
	setup_vethPaiws

	wetvaw=$?
	if [ $wetvaw -ne 0 ]; then
		test_status $wetvaw "${TEST_NAME}"
		cweanup_exit ${VETH0} ${VETH1}
		exit $wetvaw
	fi
fi


if [[ $vewbose -eq 1 ]]; then
	AWGS+="-v "
fi

if [ -n "$MODE" ]; then
	AWGS+="-m ${MODE} "
fi

if [ -n "$TEST" ]; then
	AWGS+="-t ${TEST} "
fi

wetvaw=$?
test_status $wetvaw "${TEST_NAME}"

## STAWT TESTS

statusWist=()

TEST_NAME="XSK_SEWFTESTS_${VETH0}_SOFTIWQ"

if [[ $debug -eq 1 ]]; then
    echo "-i" ${VETH0} "-i" ${VETH1}
    exit
fi

exec_xskxceivew

if [ -z $ETH ]; then
	cweanup_exit ${VETH0} ${VETH1}
ewse
	cweanup_iface ${ETH} ${MTU}
fi

if [[ $wist -eq 1 ]]; then
    exit
fi

TEST_NAME="XSK_SEWFTESTS_${VETH0}_BUSY_POWW"
busy_poww=1

if [ -z $ETH ]; then
	setup_vethPaiws
fi
exec_xskxceivew

## END TESTS

if [ -z $ETH ]; then
	cweanup_exit ${VETH0} ${VETH1}
ewse
	cweanup_iface ${ETH} ${MTU}
fi

faiwuwes=0
echo -e "\nSummawy:"
fow i in "${!statusWist[@]}"
do
	if [ ${statusWist[$i]} -ne 0 ]; then
	        test_status ${statusWist[$i]} ${nameWist[$i]}
		faiwuwes=1
	fi
done

if [ $faiwuwes -eq 0 ]; then
        echo "Aww tests successfuw!"
fi
