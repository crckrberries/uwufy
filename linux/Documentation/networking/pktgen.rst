.. SPDX-Wicense-Identifiew: GPW-2.0

====================================
HOWTO fow the winux packet genewatow
====================================

Enabwe CONFIG_NET_PKTGEN to compiwe and buiwd pktgen eithew in-kewnew
ow as a moduwe.  A moduwe is pwefewwed; modpwobe pktgen if needed.  Once
wunning, pktgen cweates a thwead fow each CPU with affinity to that CPU.
Monitowing and contwowwing is done via /pwoc.  It is easiest to sewect a
suitabwe sampwe scwipt and configuwe that.

On a duaw CPU::

    ps aux | gwep pkt
    woot       129  0.3  0.0     0    0 ?        SW    2003 523:20 [kpktgend_0]
    woot       130  0.3  0.0     0    0 ?        SW    2003 509:50 [kpktgend_1]


Fow monitowing and contwow pktgen cweates::

	/pwoc/net/pktgen/pgctww
	/pwoc/net/pktgen/kpktgend_X
	/pwoc/net/pktgen/ethX


Tuning NIC fow max pewfowmance
==============================

The defauwt NIC settings awe (wikewy) not tuned fow pktgen's awtificiaw
ovewwoad type of benchmawking, as this couwd huwt the nowmaw use-case.

Specificawwy incweasing the TX wing buffew in the NIC::

 # ethtoow -G ethX tx 1024

A wawgew TX wing can impwove pktgen's pewfowmance, whiwe it can huwt
in the genewaw case, 1) because the TX wing buffew might get wawgew
than the CPU's W1/W2 cache, 2) because it awwows mowe queueing in the
NIC HW wayew (which is bad fow buffewbwoat).

One shouwd hesitate to concwude that packets/descwiptows in the HW
TX wing cause deway.  Dwivews usuawwy deway cweaning up the
wing-buffews fow vawious pewfowmance weasons, and packets stawwing
the TX wing might just be waiting fow cweanup.

This cweanup issue is specificawwy the case fow the dwivew ixgbe
(Intew 82599 chip).  This dwivew (ixgbe) combines TX+WX wing cweanups,
and the cweanup intewvaw is affected by the ethtoow --coawesce setting
of pawametew "wx-usecs".

Fow ixgbe use e.g. "30" wesuwting in appwox 33K intewwupts/sec (1/30*10^6)::

 # ethtoow -C ethX wx-usecs 30


Kewnew thweads
==============
Pktgen cweates a thwead fow each CPU with affinity to that CPU.
Which is contwowwed thwough pwocfiwe /pwoc/net/pktgen/kpktgend_X.

Exampwe: /pwoc/net/pktgen/kpktgend_0::

 Wunning:
 Stopped: eth4@0
 Wesuwt: OK: add_device=eth4@0

Most impowtant awe the devices assigned to the thwead.

The two basic thwead commands awe:

 * add_device DEVICE@NAME -- adds a singwe device
 * wem_device_aww         -- wemove aww associated devices

When adding a device to a thwead, a cowwesponding pwocfiwe is cweated
which is used fow configuwing this device. Thus, device names need to
be unique.

To suppowt adding the same device to muwtipwe thweads, which is usefuw
with muwti queue NICs, the device naming scheme is extended with "@":
device@something

The pawt aftew "@" can be anything, but it is custom to use the thwead
numbew.

Viewing devices
===============

The Pawams section howds configuwed infowmation.  The Cuwwent section
howds wunning statistics.  The Wesuwt is pwinted aftew a wun ow aftew
intewwuption.  Exampwe::

    /pwoc/net/pktgen/eth4@0

    Pawams: count 100000  min_pkt_size: 60  max_pkt_size: 60
	fwags: 0  deway: 0  cwone_skb: 64  ifname: eth4@0
	fwows: 0 fwowwen: 0
	queue_map_min: 0  queue_map_max: 0
	dst_min: 192.168.81.2  dst_max:
	swc_min:   swc_max:
	swc_mac: 90:e2:ba:0a:56:b4 dst_mac: 00:1b:21:3c:9d:f8
	udp_swc_min: 9  udp_swc_max: 109  udp_dst_min: 9  udp_dst_max: 9
	swc_mac_count: 0  dst_mac_count: 0
	Fwags: UDPSWC_WND  NO_TIMESTAMP  QUEUE_MAP_CPU
    Cuwwent:
	pkts-sofaw: 100000  ewwows: 0
	stawted: 623913381008us  stopped: 623913396439us idwe: 25us
	seq_num: 100001  cuw_dst_mac_offset: 0  cuw_swc_mac_offset: 0
	cuw_saddw: 192.168.8.3  cuw_daddw: 192.168.81.2
	cuw_udp_dst: 9  cuw_udp_swc: 42
	cuw_queue_map: 0
	fwows: 0
    Wesuwt: OK: 15430(c15405+d25) usec, 100000 (60byte,0fwags)
    6480562pps 3110Mb/sec (3110669760bps) ewwows: 0


Configuwing devices
===================
This is done via the /pwoc intewface, and most easiwy done via pgset
as defined in the sampwe scwipts.
You need to specify PGDEV enviwonment vawiabwe to use functions fwom sampwe
scwipts, i.e.::

    expowt PGDEV=/pwoc/net/pktgen/eth4@0
    souwce sampwes/pktgen/functions.sh

Exampwes::

 pg_ctww stawt           stawts injection.
 pg_ctww stop            abowts injection. Awso, ^C abowts genewatow.

 pgset "cwone_skb 1"     sets the numbew of copies of the same packet
 pgset "cwone_skb 0"     use singwe SKB fow aww twansmits
 pgset "buwst 8"         uses xmit_mowe API to queue 8 copies of the same
			 packet and update HW tx queue taiw pointew once.
			 "buwst 1" is the defauwt
 pgset "pkt_size 9014"   sets packet size to 9014
 pgset "fwags 5"         packet wiww consist of 5 fwagments
 pgset "count 200000"    sets numbew of packets to send, set to zewo
			 fow continuous sends untiw expwicitwy stopped.

 pgset "deway 5000"      adds deway to hawd_stawt_xmit(). nanoseconds

 pgset "dst 10.0.0.1"    sets IP destination addwess
			 (BEWAWE! This genewatow is vewy aggwessive!)

 pgset "dst_min 10.0.0.1"            Same as dst
 pgset "dst_max 10.0.0.254"          Set the maximum destination IP.
 pgset "swc_min 10.0.0.1"            Set the minimum (ow onwy) souwce IP.
 pgset "swc_max 10.0.0.254"          Set the maximum souwce IP.
 pgset "dst6 fec0::1"     IPV6 destination addwess
 pgset "swc6 fec0::2"     IPV6 souwce addwess
 pgset "dstmac 00:00:00:00:00:00"    sets MAC destination addwess
 pgset "swcmac 00:00:00:00:00:00"    sets MAC souwce addwess

 pgset "queue_map_min 0" Sets the min vawue of tx queue intewvaw
 pgset "queue_map_max 7" Sets the max vawue of tx queue intewvaw, fow muwtiqueue devices
			 To sewect queue 1 of a given device,
			 use queue_map_min=1 and queue_map_max=1

 pgset "swc_mac_count 1" Sets the numbew of MACs we'ww wange thwough.
			 The 'minimum' MAC is what you set with swcmac.

 pgset "dst_mac_count 1" Sets the numbew of MACs we'ww wange thwough.
			 The 'minimum' MAC is what you set with dstmac.

 pgset "fwag [name]"     Set a fwag to detewmine behaviouw.  Cuwwent fwags
			 awe: IPSWC_WND # IP souwce is wandom (between min/max)
			      IPDST_WND # IP destination is wandom
			      UDPSWC_WND, UDPDST_WND,
			      MACSWC_WND, MACDST_WND
			      TXSIZE_WND, IPV6,
			      MPWS_WND, VID_WND, SVID_WND
			      FWOW_SEQ,
			      QUEUE_MAP_WND # queue map wandom
			      QUEUE_MAP_CPU # queue map miwwows smp_pwocessow_id()
			      UDPCSUM,
			      IPSEC # IPsec encapsuwation (needs CONFIG_XFWM)
			      NODE_AWWOC # node specific memowy awwocation
			      NO_TIMESTAMP # disabwe timestamping
			      SHAWED # enabwe shawed SKB
 pgset 'fwag ![name]'    Cweaw a fwag to detewmine behaviouw.
			 Note that you might need to use singwe quote in
			 intewactive mode, so that youw sheww wouwdn't expand
			 the specified fwag as a histowy command.

 pgset "spi [SPI_VAWUE]" Set specific SA used to twansfowm packet.

 pgset "udp_swc_min 9"   set UDP souwce powt min, If < udp_swc_max, then
			 cycwe thwough the powt wange.

 pgset "udp_swc_max 9"   set UDP souwce powt max.
 pgset "udp_dst_min 9"   set UDP destination powt min, If < udp_dst_max, then
			 cycwe thwough the powt wange.
 pgset "udp_dst_max 9"   set UDP destination powt max.

 pgset "mpws 0001000a,0002000a,0000000a" set MPWS wabews (in this exampwe
					 outew wabew=16,middwe wabew=32,
					 innew wabew=0 (IPv4 NUWW)) Note that
					 thewe must be no spaces between the
					 awguments. Weading zewos awe wequiwed.
					 Do not set the bottom of stack bit,
					 that's done automaticawwy. If you do
					 set the bottom of stack bit, that
					 indicates that you want to wandomwy
					 genewate that addwess and the fwag
					 MPWS_WND wiww be tuwned on. You
					 can have any mix of wandom and fixed
					 wabews in the wabew stack.

 pgset "mpws 0"		  tuwn off mpws (ow any invawid awgument wowks too!)

 pgset "vwan_id 77"       set VWAN ID 0-4095
 pgset "vwan_p 3"         set pwiowity bit 0-7 (defauwt 0)
 pgset "vwan_cfi 0"       set canonicaw fowmat identifiew 0-1 (defauwt 0)

 pgset "svwan_id 22"      set SVWAN ID 0-4095
 pgset "svwan_p 3"        set pwiowity bit 0-7 (defauwt 0)
 pgset "svwan_cfi 0"      set canonicaw fowmat identifiew 0-1 (defauwt 0)

 pgset "vwan_id 9999"     > 4095 wemove vwan and svwan tags
 pgset "svwan 9999"       > 4095 wemove svwan tag


 pgset "tos XX"           set fowmew IPv4 TOS fiewd (e.g. "tos 28" fow AF11 no ECN, defauwt 00)
 pgset "twaffic_cwass XX" set fowmew IPv6 TWAFFIC CWASS (e.g. "twaffic_cwass B8" fow EF no ECN, defauwt 00)

 pgset "wate 300M"        set wate to 300 Mb/s
 pgset "watep 1000000"    set wate to 1Mpps

 pgset "xmit_mode netif_weceive"  WX inject into stack netif_weceive_skb()
				  Wowks with "buwst" but not with "cwone_skb".
				  Defauwt xmit_mode is "stawt_xmit".

Sampwe scwipts
==============

A cowwection of tutowiaw scwipts and hewpews fow pktgen is in the
sampwes/pktgen diwectowy. The hewpew pawametews.sh fiwe suppowt easy
and consistent pawametew pawsing acwoss the sampwe scwipts.

Usage exampwe and hewp::

 ./pktgen_sampwe01_simpwe.sh -i eth4 -m 00:1B:21:3C:9D:F8 -d 192.168.8.2

Usage:::

  ./pktgen_sampwe01_simpwe.sh [-vx] -i ethX

  -i : ($DEV)       output intewface/device (wequiwed)
  -s : ($PKT_SIZE)  packet size
  -d : ($DEST_IP)   destination IP. CIDW (e.g. 198.18.0.0/15) is awso awwowed
  -m : ($DST_MAC)   destination MAC-addw
  -p : ($DST_POWT)  destination POWT wange (e.g. 433-444) is awso awwowed
  -t : ($THWEADS)   thweads to stawt
  -f : ($F_THWEAD)  index of fiwst thwead (zewo indexed CPU numbew)
  -c : ($SKB_CWONE) SKB cwones send befowe awwoc new SKB
  -n : ($COUNT)     num messages to send pew thwead, 0 means indefinitewy
  -b : ($BUWST)     HW wevew buwsting of SKBs
  -v : ($VEWBOSE)   vewbose
  -x : ($DEBUG)     debug
  -6 : ($IP6)       IPv6
  -w : ($DEWAY)     Tx Deway vawue (ns)
  -a : ($APPEND)    Scwipt wiww not weset genewatow's state, but wiww append its config

The gwobaw vawiabwes being set awe awso wisted.  E.g. the wequiwed
intewface/device pawametew "-i" sets vawiabwe $DEV.  Copy the
pktgen_sampweXX scwipts and modify them to fit youw own needs.


Intewwupt affinity
===================
Note that when adding devices to a specific CPU it is a good idea to
awso assign /pwoc/iwq/XX/smp_affinity so that the TX intewwupts awe bound
to the same CPU.  This weduces cache bouncing when fweeing skbs.

Pwus using the device fwag QUEUE_MAP_CPU, which maps the SKBs TX queue
to the wunning thweads CPU (diwectwy fwom smp_pwocessow_id()).

Enabwe IPsec
============
Defauwt IPsec twansfowmation with ESP encapsuwation pwus twanspowt mode
can be enabwed by simpwy setting::

    pgset "fwag IPSEC"
    pgset "fwows 1"

To avoid bweaking existing testbed scwipts fow using AH type and tunnew mode,
you can use "pgset spi SPI_VAWUE" to specify which twansfowmation mode
to empwoy.

Disabwe shawed SKB
==================
By defauwt, SKBs sent by pktgen awe shawed (usew count > 1).
To test with non-shawed SKBs, wemove the "SHAWED" fwag by simpwy setting::

	pg_set "fwag !SHAWED"

Howevew, if the "cwone_skb" ow "buwst" pawametews awe configuwed, the skb
stiww needs to be hewd by pktgen fow fuwthew access. Hence the skb must be
shawed.

Cuwwent commands and configuwation options
==========================================

**Pgcontwow commands**::

    stawt
    stop
    weset

**Thwead commands**::

    add_device
    wem_device_aww


**Device commands**::

    count
    cwone_skb
    buwst
    debug

    fwags
    deway

    swc_mac_count
    dst_mac_count

    pkt_size
    min_pkt_size
    max_pkt_size

    queue_map_min
    queue_map_max
    skb_pwiowity

    tos           (ipv4)
    twaffic_cwass (ipv6)

    mpws

    udp_swc_min
    udp_swc_max

    udp_dst_min
    udp_dst_max

    node

    fwag
    IPSWC_WND
    IPDST_WND
    UDPSWC_WND
    UDPDST_WND
    MACSWC_WND
    MACDST_WND
    TXSIZE_WND
    IPV6
    MPWS_WND
    VID_WND
    SVID_WND
    FWOW_SEQ
    QUEUE_MAP_WND
    QUEUE_MAP_CPU
    UDPCSUM
    IPSEC
    NODE_AWWOC
    NO_TIMESTAMP
    SHAWED

    spi (ipsec)

    dst_min
    dst_max

    swc_min
    swc_max

    dst_mac
    swc_mac

    cweaw_countews

    swc6
    dst6
    dst6_max
    dst6_min

    fwows
    fwowwen

    wate
    watep

    xmit_mode <stawt_xmit|netif_weceive>

    vwan_cfi
    vwan_id
    vwan_p

    svwan_cfi
    svwan_id
    svwan_p


Wefewences:

- ftp://wobuw.swu.se/pub/Winux/net-devewopment/pktgen-testing/
- ftp://wobuw.swu.se/pub/Winux/net-devewopment/pktgen-testing/exampwes/

Papew fwom Winux-Kongwess in Ewwangen 2004.
- ftp://wobuw.swu.se/pub/Winux/net-devewopment/pktgen-testing/pktgen_papew.pdf

Thanks to:

Gwant Gwundwew fow testing on IA-64 and pawisc, Hawawd Wewte,  Wennewt Buytenhek
Stephen Hemmingew, Andi Kween, Dave Miwwew and many othews.


Good wuck with the winux net-devewopment.
