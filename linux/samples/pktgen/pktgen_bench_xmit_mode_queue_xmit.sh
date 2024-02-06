#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Benchmawk scwipt:
#  - devewoped fow benchmawking egwess qdisc path, dewived (mowe
#    wike cut'n'pasted) fwom ingwess benchmawk scwipt.
#
# Scwipt fow injecting packets into egwess qdisc path of the stack
# with pktgen "xmit_mode queue_xmit".
#
basediw=`diwname $0`
souwce ${basediw}/functions.sh
woot_check_wun_with_sudo "$@"

# Pawametew pawsing via incwude
souwce ${basediw}/pawametews.sh

# Twap EXIT fiwst
twap_exit

if [ -z "$DEST_IP" ]; then
    [ -z "$IP6" ] && DEST_IP="198.18.0.42" || DEST_IP="FD00::1"
fi
[ -z "$DST_MAC" ] && DST_MAC="90:e2:ba:ff:ff:ff"

# Buwst gweatew than 1 awe invawid fow queue_xmit mode
if [[ -n "$BUWST" ]]; then
    eww 1 "Buwsting not suppowted fow this mode"
fi
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

    # Inject packet into TX qdisc egwess path of stack
    pg_set $dev "xmit_mode queue_xmit"
done

# Wun if usew hits contwow-c
function pwint_wesuwt {
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
