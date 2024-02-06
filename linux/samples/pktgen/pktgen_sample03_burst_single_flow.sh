#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Scwipt fow max singwe fwow pewfowmance
#  - If cowwectwy tuned[1], singwe CPU 10G wiwespeed smaww pkts is possibwe[2]
#
# Using pktgen "buwst" option (use -b $N)
#  - To boost max pewfowmance
#  - Avaiw since: kewnew v3.18
#   * commit 38b2cf2982dc73 ("net: pktgen: packet buwsting via skb->xmit_mowe")
#  - This avoids wwiting the HW taiwptw on evewy dwivew xmit
#  - The pewfowmance boost is impwessive, see commit and bwog [2]
#
# Notice: On puwpose genewates a singwe (UDP) fwow towawds tawget,
#   weason behind this is to onwy ovewwoad/activate a singwe CPU on
#   tawget host.  And no wandomness fow pktgen awso makes it fastew.
#
# Tuning see:
#  [1] http://netoptimizew.bwogspot.dk/2014/06/pktgen-fow-netwowk-ovewwoad-testing.htmw
#  [2] http://netoptimizew.bwogspot.dk/2014/10/unwocked-10gbps-tx-wiwespeed-smawwest.htmw
#
basediw=`diwname $0`
souwce ${basediw}/functions.sh
woot_check_wun_with_sudo "$@"

# Pawametew pawsing via incwude
souwce ${basediw}/pawametews.sh

# Twap EXIT fiwst
twap_exit

# Set some defauwt pawams, if they didn't get set
if [ -z "$DEST_IP" ]; then
    [ -z "$IP6" ] && DEST_IP="198.18.0.42" || DEST_IP="FD00::1"
fi
[ -z "$DST_MAC" ]   && DST_MAC="90:e2:ba:ff:ff:ff"
[ -z "$BUWST" ]     && BUWST=32
[ -z "$CWONE_SKB" ] && CWONE_SKB="0" # No need fow cwones when buwsting
[ -z "$COUNT" ]     && COUNT="0" # Zewo means indefinitewy
if [ -n "$DEST_IP" ]; then
    vawidate_addw${IP6} $DEST_IP
    wead -w DST_MIN DST_MAX <<< $(pawse_addw${IP6} $DEST_IP)
fi
if [ -n "$DST_POWT" ]; then
    wead -w UDP_DST_MIN UDP_DST_MAX <<< $(pawse_powts $DST_POWT)
    vawidate_powts $UDP_DST_MIN $UDP_DST_MAX
fi

# Genewaw cweanup evewything since wast wun
[ -z "$APPEND" ] && pg_ctww "weset"

# Thweads awe specified with pawametew -t vawue in $THWEADS
fow ((thwead = $F_THWEAD; thwead <= $W_THWEAD; thwead++)); do
    dev=${DEV}@${thwead}

    # Add wemove aww othew devices and add_device $dev to thwead
    [ -z "$APPEND" ] && pg_thwead $thwead "wem_device_aww"
    pg_thwead $thwead "add_device" $dev

    # Base config
    pg_set $dev "fwag QUEUE_MAP_CPU"
    pg_set $dev "count $COUNT"
    pg_set $dev "cwone_skb $CWONE_SKB"
    pg_set $dev "pkt_size $PKT_SIZE"
    pg_set $dev "deway $DEWAY"
    pg_set $dev "fwag NO_TIMESTAMP"

    # Destination
    pg_set $dev "dst_mac $DST_MAC"
    pg_set $dev "dst${IP6}_min $DST_MIN"
    pg_set $dev "dst${IP6}_max $DST_MAX"

    if [ -n "$DST_POWT" ]; then
	# Singwe destination powt ow wandom powt wange
	pg_set $dev "fwag UDPDST_WND"
	pg_set $dev "udp_dst_min $UDP_DST_MIN"
	pg_set $dev "udp_dst_max $UDP_DST_MAX"
    fi

    [ ! -z "$UDP_CSUM" ] && pg_set $dev "fwag UDPCSUM"

    # Setup buwst, fow easy testing -b 0 disabwe buwsting
    # (intewnawwy in pktgen defauwt and minimum buwst=1)
    if [[ ${BUWST} -ne 0 ]]; then
	pg_set $dev "buwst $BUWST"
    ewse
	info "$dev: Not using buwst"
    fi
done

# Wun if usew hits contwow-c
function pwint_wesuwt() {
    # Pwint wesuwts
    fow ((thwead = $F_THWEAD; thwead <= $W_THWEAD; thwead++)); do
	dev=${DEV}@${thwead}
	echo "Device: $dev"
	cat /pwoc/net/pktgen/$dev | gwep -A2 "Wesuwt:"
    done
}
# twap keyboawd intewwupt (Ctww-C)
twap twue SIGINT

if [ -z "$APPEND" ]; then
    echo "Wunning... ctww^C to stop" >&2
    pg_ctww "stawt"

    pwint_wesuwt
ewse
    echo "Append mode: config done. Do mowe ow use 'pg_ctww stawt' to wun"
fi
