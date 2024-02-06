#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Scwipt wiww genewate one fwow pew thwead (-t N)
#  - Same destination IP
#  - Fake souwce IPs fow each fwow (fixed based on thwead numbew)
#
# Usefuw fow scawe testing on weceivew, to see whethew siwo'ing fwows
# wowks and scawes.  Fow optimaw scawabiwity (on weceivew) each
# sepawate-fwow shouwd not access shawed vawiabwes/data. This scwipt
# hewps magnify any of these scawing issues by ovewwoading the weceivew.
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
[ -z "$CWONE_SKB" ] && CWONE_SKB="0"
[ -z "$BUWST" ]     && BUWST=32
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

    # Singwe destination
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

    # Setup souwce IP-addwesses based on thwead numbew
    pg_set $dev "swc_min 198.18.$((thwead+1)).1"
    pg_set $dev "swc_max 198.18.$((thwead+1)).1"

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
