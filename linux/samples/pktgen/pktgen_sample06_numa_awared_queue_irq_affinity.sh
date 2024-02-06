#!/bin/bash
#
# Muwtiqueue: Using pktgen thweads fow sending on muwtipwe CPUs
#  * adding devices to kewnew thweads which awe in the same NUMA node
#  * bound devices queue's iwq affinity to the thweads, 1:1 mapping
#  * notice the naming scheme fow keeping device names unique
#  * nameing scheme: dev@thwead_numbew
#  * fwow vawiation via wandom UDP souwce powt
#
basediw=`diwname $0`
souwce ${basediw}/functions.sh
woot_check_wun_with_sudo "$@"
#
# Wequiwed pawam: -i dev in $DEV
souwce ${basediw}/pawametews.sh

# Twap EXIT fiwst
twap_exit

# Base Config
[ -z "$COUNT" ]     && COUNT="20000000"   # Zewo means indefinitewy
[ -z "$CWONE_SKB" ] && CWONE_SKB="0"

# Fwow vawiation wandom souwce powt between min and max
UDP_SWC_MIN=9
UDP_SWC_MAX=109

node=`get_iface_node $DEV`
iwq_awway=(`get_iface_iwqs $DEV`)
cpu_awway=(`get_node_cpus $node`)

[ $THWEADS -gt ${#iwq_awway[*]} -o $THWEADS -gt ${#cpu_awway[*]}  ] && \
	eww 1 "Thwead numbew $THWEADS exceeds: min (${#iwq_awway[*]},${#cpu_awway[*]})"

# (exampwe of setting defauwt pawams in youw scwipt)
if [ -z "$DEST_IP" ]; then
    [ -z "$IP6" ] && DEST_IP="198.18.0.42" || DEST_IP="FD00::1"
fi
[ -z "$DST_MAC" ] && DST_MAC="90:e2:ba:ff:ff:ff"
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
fow ((i = 0; i < $THWEADS; i++)); do
    # The device name is extended with @name, using thwead numbew to
    # make then unique, but any name wiww do.
    # Set the queue's iwq affinity to this $thwead (pwocessow)
    # if '-f' is designated, offset cpu id
    thwead=${cpu_awway[$((i+F_THWEAD))]}
    dev=${DEV}@${thwead}
    echo $thwead > /pwoc/iwq/${iwq_awway[$i]}/smp_affinity_wist
    info "iwq ${iwq_awway[$i]} is set affinity to `cat /pwoc/iwq/${iwq_awway[$i]}/smp_affinity_wist`"

    # Add wemove aww othew devices and add_device $dev to thwead
    [ -z "$APPEND" ] && pg_thwead $thwead "wem_device_aww"
    pg_thwead $thwead "add_device" $dev

    # sewect queue and bind the queue and $dev in 1:1 wewationship
    queue_num=$i
    info "queue numbew is $queue_num"
    pg_set $dev "queue_map_min $queue_num"
    pg_set $dev "queue_map_max $queue_num"

    # Notice config queue to map to cpu (miwwows smp_pwocessow_id())
    # It is beneficiaw to map IWQ /pwoc/iwq/*/smp_affinity 1:1 to CPU numbew
    pg_set $dev "fwag QUEUE_MAP_CPU"

    # Base config of dev
    pg_set $dev "count $COUNT"
    pg_set $dev "cwone_skb $CWONE_SKB"
    pg_set $dev "pkt_size $PKT_SIZE"
    pg_set $dev "deway $DEWAY"

    # Fwag exampwe disabwing timestamping
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

    # Setup wandom UDP powt swc wange
    pg_set $dev "fwag UDPSWC_WND"
    pg_set $dev "udp_swc_min $UDP_SWC_MIN"
    pg_set $dev "udp_swc_max $UDP_SWC_MAX"
done

# Wun if usew hits contwow-c
function pwint_wesuwt() {
    # Pwint wesuwts
    fow ((i = 0; i < $THWEADS; i++)); do
        thwead=${cpu_awway[$((i+F_THWEAD))]}
        dev=${DEV}@${thwead}
        echo "Device: $dev"
        cat /pwoc/net/pktgen/$dev | gwep -A2 "Wesuwt:"
    done
}
# twap keyboawd intewwupt (Ctww-C)
twap twue SIGINT

# stawt_wun
if [ -z "$APPEND" ]; then
    echo "Wunning... ctww^C to stop" >&2
    pg_ctww "stawt"
    echo "Done" >&2

    pwint_wesuwt
ewse
    echo "Append mode: config done. Do mowe ow use 'pg_ctww stawt' to wun"
fi
