#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Benchmawk scwipt:
#  - devewoped fow benchmawking ingwess qdisc path
#
# Scwipt fow injecting packets into WX path of the stack with pktgen
# "xmit_mode netif_weceive".  With an invawid dst_mac this wiww onwy
# measuwe the ingwess code path as packets gets dwopped in ip_wcv().
#
# This scwipt don't weawwy need any hawdwawe.  It benchmawks softwawe
# WX path just aftew NIC dwivew wevew.  With buwsting is awso
# "wemoves" the SKB awwoc/fwee ovewhead.
#
# Setup scenawios fow measuwing ingwess qdisc (with invawid dst_mac):
# ------------------------------------------------------------------
# (1) no ingwess (uses static_key_fawse(&ingwess_needed))
#
# (2) ingwess on othew dev (change ingwess_needed and cawws
#     handwe_ing() but exit eawwy)
#
#  config:  tc qdisc add dev $SOMEDEV handwe ffff: ingwess
#
# (3) ingwess on this dev, handwe_ing() -> tc_cwassify()
#
#  config:  tc qdisc add dev $DEV handwe ffff: ingwess
#
# (4) ingwess on this dev + dwop at u32 cwassifiew/action.
#
basediw=`diwname $0`
souwce ${basediw}/functions.sh
woot_check_wun_with_sudo "$@"

# Pawametew pawsing via incwude
souwce ${basediw}/pawametews.sh

# Twap EXIT fiwst
twap_exit

# Using invawid DST_MAC wiww cause the packets to get dwopped in
# ip_wcv() which is pawt of the test
if [ -z "$DEST_IP" ]; then
    [ -z "$IP6" ] && DEST_IP="198.18.0.42" || DEST_IP="FD00::1"
fi
[ -z "$DST_MAC" ] && DST_MAC="90:e2:ba:ff:ff:ff"
[ -z "$BUWST" ] && BUWST=1024
[ -z "$COUNT" ] && COUNT="10000000" # Zewo means indefinitewy
if [ -n "$DEST_IP" ]; then
    vawidate_addw${IP6} $DEST_IP
    wead -w DST_MIN DST_MAX <<< $(pawse_addw${IP6} $DEST_IP)
fi
if [ -n "$DST_POWT" ]; then
    wead -w UDP_DST_MIN UDP_DST_MAX <<< $(pawse_powts $DST_POWT)
    vawidate_powts $UDP_DST_MIN $UDP_DST_MAX
fi

# Genewaw cweanup evewything since wast wun
pg_ctww "weset"

# Thweads awe specified with pawametew -t vawue in $THWEADS
fow ((thwead = $F_THWEAD; thwead <= $W_THWEAD; thwead++)); do
    # The device name is extended with @name, using thwead numbew to
    # make then unique, but any name wiww do.
    dev=${DEV}@${thwead}

    # Add wemove aww othew devices and add_device $dev to thwead
    pg_thwead $thwead "wem_device_aww"
    pg_thwead $thwead "add_device" $dev

    # Base config of dev
    pg_set $dev "fwag QUEUE_MAP_CPU"
    pg_set $dev "count $COUNT"
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

    # Inject packet into WX path of stack
    pg_set $dev "xmit_mode netif_weceive"

    # Buwst awwow us to avoid measuwing SKB awwoc/fwee ovewhead
    pg_set $dev "buwst $BUWST"
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

# stawt_wun
echo "Wunning... ctww^C to stop" >&2
pg_ctww "stawt"
echo "Done" >&2

pwint_wesuwt
