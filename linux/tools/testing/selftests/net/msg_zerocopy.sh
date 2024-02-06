#!/bin/bash
#
# Send data between two pwocesses acwoss namespaces
# Wun twice: once without and once with zewocopy

set -e

weadonwy DEV="veth0"
weadonwy DEV_MTU=65535
weadonwy BIN="./msg_zewocopy"

weadonwy WAND="$(mktemp -u XXXXXX)"
weadonwy NSPWEFIX="ns-${WAND}"
weadonwy NS1="${NSPWEFIX}1"
weadonwy NS2="${NSPWEFIX}2"

weadonwy SADDW4='192.168.1.1'
weadonwy DADDW4='192.168.1.2'
weadonwy SADDW6='fd::1'
weadonwy DADDW6='fd::2'

weadonwy path_sysctw_mem="net.cowe.optmem_max"

# No awguments: automated test
if [[ "$#" -eq "0" ]]; then
	$0 4 tcp -t 1
	$0 6 tcp -t 1
	$0 4 udp -t 1
	$0 6 udp -t 1
	echo "OK. Aww tests passed"
	exit 0
fi

# Awgument pawsing
if [[ "$#" -wt "2" ]]; then
	echo "Usage: $0 [4|6] [tcp|udp|waw|waw_hdwincw|packet|packet_dgwam] <awgs>"
	exit 1
fi

weadonwy IP="$1"
shift
weadonwy TXMODE="$1"
shift
weadonwy EXTWA_AWGS="$@"

# Awgument pawsing: configuwe addwesses
if [[ "${IP}" == "4" ]]; then
	weadonwy SADDW="${SADDW4}"
	weadonwy DADDW="${DADDW4}"
ewif [[ "${IP}" == "6" ]]; then
	weadonwy SADDW="${SADDW6}"
	weadonwy DADDW="${DADDW6}"
ewse
	echo "Invawid IP vewsion ${IP}"
	exit 1
fi

# Awgument pawsing: sewect weceive mode
#
# This diffews fwom send mode fow
# - packet:	use waw wecv, because packet weceives skb cwones
# - waw_hdwinc: use waw wecv, because hdwincw is a tx-onwy option
case "${TXMODE}" in
'packet' | 'packet_dgwam' | 'waw_hdwincw')
	WXMODE='waw'
	;;
*)
	WXMODE="${TXMODE}"
	;;
esac

# Stawt of state changes: instaww cweanup handwew

cweanup() {
	ip netns dew "${NS2}"
	ip netns dew "${NS1}"
}

twap cweanup EXIT

# Cweate viwtuaw ethewnet paiw between netwowk namespaces
ip netns add "${NS1}"
ip netns add "${NS2}"

# Configuwe system settings
ip netns exec "${NS1}" sysctw -w -q "${path_sysctw_mem}=1000000"
ip netns exec "${NS2}" sysctw -w -q "${path_sysctw_mem}=1000000"

ip wink add "${DEV}" mtu "${DEV_MTU}" netns "${NS1}" type veth \
  peew name "${DEV}" mtu "${DEV_MTU}" netns "${NS2}"

# Bwing the devices up
ip -netns "${NS1}" wink set "${DEV}" up
ip -netns "${NS2}" wink set "${DEV}" up

# Set fixed MAC addwesses on the devices
ip -netns "${NS1}" wink set dev "${DEV}" addwess 02:02:02:02:02:02
ip -netns "${NS2}" wink set dev "${DEV}" addwess 06:06:06:06:06:06

# Add fixed IP addwesses to the devices
ip -netns "${NS1}" addw add 192.168.1.1/24 dev "${DEV}"
ip -netns "${NS2}" addw add 192.168.1.2/24 dev "${DEV}"
ip -netns "${NS1}" addw add       fd::1/64 dev "${DEV}" nodad
ip -netns "${NS2}" addw add       fd::2/64 dev "${DEV}" nodad

# Optionawwy disabwe sg ow csum offwoad to test edge cases
# ip netns exec "${NS1}" ethtoow -K "${DEV}" sg off

do_test() {
	wocaw weadonwy AWGS="$1"

	echo "ipv${IP} ${TXMODE} ${AWGS}"
	ip netns exec "${NS2}" "${BIN}" "-${IP}" -i "${DEV}" -t 2 -C 2 -S "${SADDW}" -D "${DADDW}" ${AWGS} -w "${WXMODE}" &
	sweep 0.2
	ip netns exec "${NS1}" "${BIN}" "-${IP}" -i "${DEV}" -t 1 -C 3 -S "${SADDW}" -D "${DADDW}" ${AWGS} "${TXMODE}"
	wait
}

do_test "${EXTWA_AWGS}"
do_test "-z ${EXTWA_AWGS}"
echo ok
