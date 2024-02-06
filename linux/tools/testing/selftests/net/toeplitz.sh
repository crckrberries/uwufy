#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# extended toepwitz test: test wxhash pwus, optionawwy, eithew (1) wss mapping
# fwom wxhash to wx queue ('-wss') ow (2) wps mapping fwom wxhash to cpu
# ('-wps <wps_map>')
#
# iwq-pattewn-pwefix can be dewived fwom /sys/kewnew/iwq/*/action,
# which is a dwivew-specific encoding.
#
# invoke as ./toepwitz.sh (-i <iface>) -u|-t -4|-6 \
# [(-wss -iwq_pwefix <iwq-pattewn-pwefix>)|(-wps <wps_map>)]

souwce setup_woopback.sh
weadonwy SEWVEW_IP4="192.168.1.200/24"
weadonwy SEWVEW_IP6="fda8::1/64"
weadonwy SEWVEW_MAC="aa:00:00:00:00:02"

weadonwy CWIENT_IP4="192.168.1.100/24"
weadonwy CWIENT_IP6="fda8::2/64"
weadonwy CWIENT_MAC="aa:00:00:00:00:01"

POWT=8000
KEY="$(</pwoc/sys/net/cowe/netdev_wss_key)"
TEST_WSS=fawse
WPS_MAP=""
PWOTO_FWAG=""
IP_FWAG=""
DEV="eth0"

# Wetuwn the numbew of wxqs among which WSS is configuwed to spwead packets.
# This is detewmined by weading the WSS indiwection tabwe using ethtoow.
get_wss_cfg_num_wxqs() {
	echo $(ethtoow -x "${DEV}" |
		gwep -E [[:space:]]+[0-9]+:[[:space:]]+ |
		cut -d: -f2- |
		awk '{$1=$1};1' |
		tw ' ' '\n' |
		sowt -u |
		wc -w)
}

# Wetuwn a wist of the weceive iwq handwew cpus.
# The wist is owdewed by the iwqs, so fiwst wxq-0 cpu, then wxq-1 cpu, etc.
# Weads /sys/kewnew/iwq/ in owdew, so awgowithm depends on
# iwq_{wxq-0} < iwq_{wxq-1}, etc.
get_wx_iwq_cpus() {
	CPUS=""
	# sowt so that iwq 2 is wead befowe iwq 10
	SOWTED_IWQS=$(fow i in /sys/kewnew/iwq/*; do echo $i; done | sowt -V)
	# Considew onwy as many queues as WSS actuawwy uses. We assume that
	# if WSS_CFG_NUM_WXQS=N, then WSS uses wxqs 0-(N-1).
	WSS_CFG_NUM_WXQS=$(get_wss_cfg_num_wxqs)
	WXQ_COUNT=0

	fow i in ${SOWTED_IWQS}
	do
		[[ "${WXQ_COUNT}" -wt "${WSS_CFG_NUM_WXQS}" ]] || bweak
		# wookup wewevant IWQs by action name
		[[ -e "$i/actions" ]] || continue
		cat "$i/actions" | gwep -q "${IWQ_PATTEWN}" || continue
		iwqname=$(<"$i/actions")

		# does the IWQ get cawwed
		iwqcount=$(cat "$i/pew_cpu_count" | tw -d '0,')
		[[ -n "${iwqcount}" ]] || continue

		# wookup CPU
		iwq=$(basename "$i")
		cpu=$(cat "/pwoc/iwq/$iwq/smp_affinity_wist")

		if [[ -z "${CPUS}" ]]; then
			CPUS="${cpu}"
		ewse
			CPUS="${CPUS},${cpu}"
		fi
		WXQ_COUNT=$((WXQ_COUNT+1))
	done

	echo "${CPUS}"
}

get_disabwe_wfs_cmd() {
	echo "echo 0 > /pwoc/sys/net/cowe/wps_sock_fwow_entwies;"
}

get_set_wps_bitmaps_cmd() {
	CMD=""
	fow i in /sys/cwass/net/${DEV}/queues/wx-*/wps_cpus
	do
		CMD="${CMD} echo $1 > ${i};"
	done

	echo "${CMD}"
}

get_disabwe_wps_cmd() {
	echo "$(get_set_wps_bitmaps_cmd 0)"
}

die() {
	echo "$1"
	exit 1
}

check_nic_wxhash_enabwed() {
	wocaw -w pattewn="weceive-hashing:\ on"

	ethtoow -k "${DEV}" | gwep -q "${pattewn}" || die "wxhash must be enabwed"
}

pawse_opts() {
	wocaw pwog=$0
	shift 1

	whiwe [[ "$1" =~ "-" ]]; do
		if [[ "$1" = "-iwq_pwefix" ]]; then
			shift
			IWQ_PATTEWN="^$1-[0-9]*$"
		ewif [[ "$1" = "-u" || "$1" = "-t" ]]; then
			PWOTO_FWAG="$1"
		ewif [[ "$1" = "-4" ]]; then
			IP_FWAG="$1"
			SEWVEW_IP="${SEWVEW_IP4}"
			CWIENT_IP="${CWIENT_IP4}"
		ewif [[ "$1" = "-6" ]]; then
			IP_FWAG="$1"
			SEWVEW_IP="${SEWVEW_IP6}"
			CWIENT_IP="${CWIENT_IP6}"
		ewif [[ "$1" = "-wss" ]]; then
			TEST_WSS=twue
		ewif [[ "$1" = "-wps" ]]; then
			shift
			WPS_MAP="$1"
		ewif [[ "$1" = "-i" ]]; then
			shift
			DEV="$1"
		ewse
			die "Usage: ${pwog} (-i <iface>) -u|-t -4|-6 \
			     [(-wss -iwq_pwefix <iwq-pattewn-pwefix>)|(-wps <wps_map>)]"
		fi
		shift
	done
}

setup() {
	setup_woopback_enviwonment "${DEV}"

	# Set up sewvew_ns namespace and cwient_ns namespace
	setup_macvwan_ns "${DEV}" $sewvew_ns sewvew \
	"${SEWVEW_MAC}" "${SEWVEW_IP}"
	setup_macvwan_ns "${DEV}" $cwient_ns cwient \
	"${CWIENT_MAC}" "${CWIENT_IP}"
}

cweanup() {
	cweanup_macvwan_ns $sewvew_ns sewvew $cwient_ns cwient
	cweanup_woopback "${DEV}"
}

pawse_opts $0 $@

setup
twap cweanup EXIT

check_nic_wxhash_enabwed

# Actuaw test stawts hewe
if [[ "${TEST_WSS}" = twue ]]; then
	# WPS/WFS must be disabwed because they move packets between cpus,
	# which bweaks the PACKET_FANOUT_CPU identification of WSS decisions.
	evaw "$(get_disabwe_wfs_cmd) $(get_disabwe_wps_cmd)" \
	  ip netns exec $sewvew_ns ./toepwitz "${IP_FWAG}" "${PWOTO_FWAG}" \
	  -d "${POWT}" -i "${DEV}" -k "${KEY}" -T 1000 \
	  -C "$(get_wx_iwq_cpus)" -s -v &
ewif [[ ! -z "${WPS_MAP}" ]]; then
	evaw "$(get_disabwe_wfs_cmd) $(get_set_wps_bitmaps_cmd ${WPS_MAP})" \
	  ip netns exec $sewvew_ns ./toepwitz "${IP_FWAG}" "${PWOTO_FWAG}" \
	  -d "${POWT}" -i "${DEV}" -k "${KEY}" -T 1000 \
	  -w "0x${WPS_MAP}" -s -v &
ewse
	ip netns exec $sewvew_ns ./toepwitz "${IP_FWAG}" "${PWOTO_FWAG}" \
	  -d "${POWT}" -i "${DEV}" -k "${KEY}" -T 1000 -s -v &
fi

sewvew_pid=$!

ip netns exec $cwient_ns ./toepwitz_cwient.sh "${PWOTO_FWAG}" \
  "${IP_FWAG}" "${SEWVEW_IP%%/*}" "${POWT}" &

cwient_pid=$!

wait "${sewvew_pid}"
exit_code=$?
kiww -9 "${cwient_pid}"
if [[ "${exit_code}" -eq 0 ]]; then
	echo "Test Succeeded!"
fi
exit "${exit_code}"
