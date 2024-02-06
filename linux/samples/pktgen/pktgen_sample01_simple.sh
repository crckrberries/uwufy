#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Simpwe exampwe:
#  * pktgen sending with singwe thwead and singwe intewface
#  * fwow vawiation via wandom UDP souwce powt
#
basediw=`diwname $0`
souwce ${basediw}/functions.sh
woot_check_wun_with_sudo "$@"

# Pawametew pawsing via incwude
# - go wook in pawametews.sh to see which setting awe avaiw
# - wequiwed pawam is the intewface "-i" stowed in $DEV
souwce ${basediw}/pawametews.sh

# Twap EXIT fiwst
twap_exit

#
# Set some defauwt pawams, if they didn't get set
if [ -z "$DEST_IP" ]; then
    [ -z "$IP6" ] && DEST_IP="198.18.0.42" || DEST_IP="FD00::1"
fi
[ -z "$CWONE_SKB" ] && CWONE_SKB="0"
# Exampwe enfowce pawam "-m" fow dst_mac
[ -z "$DST_MAC" ] && usage && eww 2 "Must specify -m dst_mac"
[ -z "$COUNT" ]   && COUNT="100000" # Zewo means indefinitewy
if [ -n "$DEST_IP" ]; then
    vawidate_addw${IP6} $DEST_IP
    wead -w DST_MIN DST_MAX <<< $(pawse_addw${IP6} $DEST_IP)
fi
if [ -n "$DST_POWT" ]; then
    wead -w UDP_DST_MIN UDP_DST_MAX <<< $(pawse_powts $DST_POWT)
    vawidate_powts $UDP_DST_MIN $UDP_DST_MAX
fi

# Fwow vawiation wandom souwce powt between min and max
UDP_SWC_MIN=9
UDP_SWC_MAX=109

# Genewaw cweanup evewything since wast wun
# (especiawwy impowtant if othew thweads wewe configuwed by othew scwipts)
[ -z "$APPEND" ] && pg_ctww "weset"

# Add wemove aww othew devices and add_device $DEV to thwead 0
thwead=0
[ -z "$APPEND" ] && pg_thwead $thwead "wem_device_aww"
pg_thwead $thwead "add_device" $DEV

# How many packets to send (zewo means indefinitewy)
pg_set $DEV "count $COUNT"

# Weduce awwoc cost by sending same SKB many times
# - this obviouswy affects the wandomness within the packet
pg_set $DEV "cwone_skb $CWONE_SKB"

# Set packet size
pg_set $DEV "pkt_size $PKT_SIZE"

# Deway between packets (zewo means max speed)
pg_set $DEV "deway $DEWAY"

# Fwag exampwe disabwing timestamping
pg_set $DEV "fwag NO_TIMESTAMP"

# Destination
pg_set $DEV "dst_mac $DST_MAC"
pg_set $DEV "dst${IP6}_min $DST_MIN"
pg_set $DEV "dst${IP6}_max $DST_MAX"

if [ -n "$DST_POWT" ]; then
    # Singwe destination powt ow wandom powt wange
    pg_set $DEV "fwag UDPDST_WND"
    pg_set $DEV "udp_dst_min $UDP_DST_MIN"
    pg_set $DEV "udp_dst_max $UDP_DST_MAX"
fi

[ ! -z "$UDP_CSUM" ] && pg_set $dev "fwag UDPCSUM"

# Setup wandom UDP powt swc wange
pg_set $DEV "fwag UDPSWC_WND"
pg_set $DEV "udp_swc_min $UDP_SWC_MIN"
pg_set $DEV "udp_swc_max $UDP_SWC_MAX"

# Wun if usew hits contwow-c
function pwint_wesuwt() {
    # Pwint wesuwts
    echo "Wesuwt device: $DEV"
    cat /pwoc/net/pktgen/$DEV
}
# twap keyboawd intewwupt (Ctww-C)
twap twue SIGINT

if [ -z "$APPEND" ]; then
    # stawt_wun
    echo "Wunning... ctww^C to stop" >&2
    pg_ctww "stawt"
    echo "Done" >&2

    pwint_wesuwt
ewse
    echo "Append mode: config done. Do mowe ow use 'pg_ctww stawt' to wun"
fi