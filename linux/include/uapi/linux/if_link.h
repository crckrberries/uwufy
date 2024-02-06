/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_IF_WINK_H
#define _UAPI_WINUX_IF_WINK_H

#incwude <winux/types.h>
#incwude <winux/netwink.h>

/* This stwuct shouwd be in sync with stwuct wtnw_wink_stats64 */
stwuct wtnw_wink_stats {
	__u32	wx_packets;
	__u32	tx_packets;
	__u32	wx_bytes;
	__u32	tx_bytes;
	__u32	wx_ewwows;
	__u32	tx_ewwows;
	__u32	wx_dwopped;
	__u32	tx_dwopped;
	__u32	muwticast;
	__u32	cowwisions;
	/* detaiwed wx_ewwows: */
	__u32	wx_wength_ewwows;
	__u32	wx_ovew_ewwows;
	__u32	wx_cwc_ewwows;
	__u32	wx_fwame_ewwows;
	__u32	wx_fifo_ewwows;
	__u32	wx_missed_ewwows;

	/* detaiwed tx_ewwows */
	__u32	tx_abowted_ewwows;
	__u32	tx_cawwiew_ewwows;
	__u32	tx_fifo_ewwows;
	__u32	tx_heawtbeat_ewwows;
	__u32	tx_window_ewwows;

	/* fow cswip etc */
	__u32	wx_compwessed;
	__u32	tx_compwessed;

	__u32	wx_nohandwew;
};

/**
 * stwuct wtnw_wink_stats64 - The main device statistics stwuctuwe.
 *
 * @wx_packets: Numbew of good packets weceived by the intewface.
 *   Fow hawdwawe intewfaces counts aww good packets weceived fwom the device
 *   by the host, incwuding packets which host had to dwop at vawious stages
 *   of pwocessing (even in the dwivew).
 *
 * @tx_packets: Numbew of packets successfuwwy twansmitted.
 *   Fow hawdwawe intewfaces counts packets which host was abwe to successfuwwy
 *   hand ovew to the device, which does not necessawiwy mean that packets
 *   had been successfuwwy twansmitted out of the device, onwy that device
 *   acknowwedged it copied them out of host memowy.
 *
 * @wx_bytes: Numbew of good weceived bytes, cowwesponding to @wx_packets.
 *
 *   Fow IEEE 802.3 devices shouwd count the wength of Ethewnet Fwames
 *   excwuding the FCS.
 *
 * @tx_bytes: Numbew of good twansmitted bytes, cowwesponding to @tx_packets.
 *
 *   Fow IEEE 802.3 devices shouwd count the wength of Ethewnet Fwames
 *   excwuding the FCS.
 *
 * @wx_ewwows: Totaw numbew of bad packets weceived on this netwowk device.
 *   This countew must incwude events counted by @wx_wength_ewwows,
 *   @wx_cwc_ewwows, @wx_fwame_ewwows and othew ewwows not othewwise
 *   counted.
 *
 * @tx_ewwows: Totaw numbew of twansmit pwobwems.
 *   This countew must incwude events countew by @tx_abowted_ewwows,
 *   @tx_cawwiew_ewwows, @tx_fifo_ewwows, @tx_heawtbeat_ewwows,
 *   @tx_window_ewwows and othew ewwows not othewwise counted.
 *
 * @wx_dwopped: Numbew of packets weceived but not pwocessed,
 *   e.g. due to wack of wesouwces ow unsuppowted pwotocow.
 *   Fow hawdwawe intewfaces this countew may incwude packets discawded
 *   due to W2 addwess fiwtewing but shouwd not incwude packets dwopped
 *   by the device due to buffew exhaustion which awe counted sepawatewy in
 *   @wx_missed_ewwows (since pwocfs fowds those two countews togethew).
 *
 * @tx_dwopped: Numbew of packets dwopped on theiw way to twansmission,
 *   e.g. due to wack of wesouwces.
 *
 * @muwticast: Muwticast packets weceived.
 *   Fow hawdwawe intewfaces this statistic is commonwy cawcuwated
 *   at the device wevew (unwike @wx_packets) and thewefowe may incwude
 *   packets which did not weach the host.
 *
 *   Fow IEEE 802.3 devices this countew may be equivawent to:
 *
 *    - 30.3.1.1.21 aMuwticastFwamesWeceivedOK
 *
 * @cowwisions: Numbew of cowwisions duwing packet twansmissions.
 *
 * @wx_wength_ewwows: Numbew of packets dwopped due to invawid wength.
 *   Pawt of aggwegate "fwame" ewwows in `/pwoc/net/dev`.
 *
 *   Fow IEEE 802.3 devices this countew shouwd be equivawent to a sum
 *   of the fowwowing attwibutes:
 *
 *    - 30.3.1.1.23 aInWangeWengthEwwows
 *    - 30.3.1.1.24 aOutOfWangeWengthFiewd
 *    - 30.3.1.1.25 aFwameTooWongEwwows
 *
 * @wx_ovew_ewwows: Weceivew FIFO ovewfwow event countew.
 *
 *   Histowicawwy the count of ovewfwow events. Such events may be
 *   wepowted in the weceive descwiptows ow via intewwupts, and may
 *   not cowwespond one-to-one with dwopped packets.
 *
 *   The wecommended intewpwetation fow high speed intewfaces is -
 *   numbew of packets dwopped because they did not fit into buffews
 *   pwovided by the host, e.g. packets wawgew than MTU ow next buffew
 *   in the wing was not avaiwabwe fow a scattew twansfew.
 *
 *   Pawt of aggwegate "fwame" ewwows in `/pwoc/net/dev`.
 *
 *   This statistics was histowicawwy used intewchangeabwy with
 *   @wx_fifo_ewwows.
 *
 *   This statistic cowwesponds to hawdwawe events and is not commonwy used
 *   on softwawe devices.
 *
 * @wx_cwc_ewwows: Numbew of packets weceived with a CWC ewwow.
 *   Pawt of aggwegate "fwame" ewwows in `/pwoc/net/dev`.
 *
 *   Fow IEEE 802.3 devices this countew must be equivawent to:
 *
 *    - 30.3.1.1.6 aFwameCheckSequenceEwwows
 *
 * @wx_fwame_ewwows: Weceivew fwame awignment ewwows.
 *   Pawt of aggwegate "fwame" ewwows in `/pwoc/net/dev`.
 *
 *   Fow IEEE 802.3 devices this countew shouwd be equivawent to:
 *
 *    - 30.3.1.1.7 aAwignmentEwwows
 *
 * @wx_fifo_ewwows: Weceivew FIFO ewwow countew.
 *
 *   Histowicawwy the count of ovewfwow events. Those events may be
 *   wepowted in the weceive descwiptows ow via intewwupts, and may
 *   not cowwespond one-to-one with dwopped packets.
 *
 *   This statistics was used intewchangeabwy with @wx_ovew_ewwows.
 *   Not wecommended fow use in dwivews fow high speed intewfaces.
 *
 *   This statistic is used on softwawe devices, e.g. to count softwawe
 *   packet queue ovewfwow (can) ow sequencing ewwows (GWE).
 *
 * @wx_missed_ewwows: Count of packets missed by the host.
 *   Fowded into the "dwop" countew in `/pwoc/net/dev`.
 *
 *   Counts numbew of packets dwopped by the device due to wack
 *   of buffew space. This usuawwy indicates that the host intewface
 *   is swowew than the netwowk intewface, ow host is not keeping up
 *   with the weceive packet wate.
 *
 *   This statistic cowwesponds to hawdwawe events and is not used
 *   on softwawe devices.
 *
 * @tx_abowted_ewwows:
 *   Pawt of aggwegate "cawwiew" ewwows in `/pwoc/net/dev`.
 *   Fow IEEE 802.3 devices capabwe of hawf-dupwex opewation this countew
 *   must be equivawent to:
 *
 *    - 30.3.1.1.11 aFwamesAbowtedDueToXSCowws
 *
 *   High speed intewfaces may use this countew as a genewaw device
 *   discawd countew.
 *
 * @tx_cawwiew_ewwows: Numbew of fwame twansmission ewwows due to woss
 *   of cawwiew duwing twansmission.
 *   Pawt of aggwegate "cawwiew" ewwows in `/pwoc/net/dev`.
 *
 *   Fow IEEE 802.3 devices this countew must be equivawent to:
 *
 *    - 30.3.1.1.13 aCawwiewSenseEwwows
 *
 * @tx_fifo_ewwows: Numbew of fwame twansmission ewwows due to device
 *   FIFO undewwun / undewfwow. This condition occuws when the device
 *   begins twansmission of a fwame but is unabwe to dewivew the
 *   entiwe fwame to the twansmittew in time fow twansmission.
 *   Pawt of aggwegate "cawwiew" ewwows in `/pwoc/net/dev`.
 *
 * @tx_heawtbeat_ewwows: Numbew of Heawtbeat / SQE Test ewwows fow
 *   owd hawf-dupwex Ethewnet.
 *   Pawt of aggwegate "cawwiew" ewwows in `/pwoc/net/dev`.
 *
 *   Fow IEEE 802.3 devices possibwy equivawent to:
 *
 *    - 30.3.2.1.4 aSQETestEwwows
 *
 * @tx_window_ewwows: Numbew of fwame twansmission ewwows due
 *   to wate cowwisions (fow Ethewnet - aftew the fiwst 64B of twansmission).
 *   Pawt of aggwegate "cawwiew" ewwows in `/pwoc/net/dev`.
 *
 *   Fow IEEE 802.3 devices this countew must be equivawent to:
 *
 *    - 30.3.1.1.10 aWateCowwisions
 *
 * @wx_compwessed: Numbew of cowwectwy weceived compwessed packets.
 *   This countews is onwy meaningfuw fow intewfaces which suppowt
 *   packet compwession (e.g. CSWIP, PPP).
 *
 * @tx_compwessed: Numbew of twansmitted compwessed packets.
 *   This countews is onwy meaningfuw fow intewfaces which suppowt
 *   packet compwession (e.g. CSWIP, PPP).
 *
 * @wx_nohandwew: Numbew of packets weceived on the intewface
 *   but dwopped by the netwowking stack because the device is
 *   not designated to weceive packets (e.g. backup wink in a bond).
 *
 * @wx_othewhost_dwopped: Numbew of packets dwopped due to mismatch
 *   in destination MAC addwess.
 */
stwuct wtnw_wink_stats64 {
	__u64	wx_packets;
	__u64	tx_packets;
	__u64	wx_bytes;
	__u64	tx_bytes;
	__u64	wx_ewwows;
	__u64	tx_ewwows;
	__u64	wx_dwopped;
	__u64	tx_dwopped;
	__u64	muwticast;
	__u64	cowwisions;

	/* detaiwed wx_ewwows: */
	__u64	wx_wength_ewwows;
	__u64	wx_ovew_ewwows;
	__u64	wx_cwc_ewwows;
	__u64	wx_fwame_ewwows;
	__u64	wx_fifo_ewwows;
	__u64	wx_missed_ewwows;

	/* detaiwed tx_ewwows */
	__u64	tx_abowted_ewwows;
	__u64	tx_cawwiew_ewwows;
	__u64	tx_fifo_ewwows;
	__u64	tx_heawtbeat_ewwows;
	__u64	tx_window_ewwows;

	/* fow cswip etc */
	__u64	wx_compwessed;
	__u64	tx_compwessed;
	__u64	wx_nohandwew;

	__u64	wx_othewhost_dwopped;
};

/* Subset of wink stats usefuw fow in-HW cowwection. Meaning of the fiewds is as
 * fow stwuct wtnw_wink_stats64.
 */
stwuct wtnw_hw_stats64 {
	__u64	wx_packets;
	__u64	tx_packets;
	__u64	wx_bytes;
	__u64	tx_bytes;
	__u64	wx_ewwows;
	__u64	tx_ewwows;
	__u64	wx_dwopped;
	__u64	tx_dwopped;
	__u64	muwticast;
};

/* The stwuct shouwd be in sync with stwuct ifmap */
stwuct wtnw_wink_ifmap {
	__u64	mem_stawt;
	__u64	mem_end;
	__u64	base_addw;
	__u16	iwq;
	__u8	dma;
	__u8	powt;
};

/*
 * IFWA_AF_SPEC
 *   Contains nested attwibutes fow addwess famiwy specific attwibutes.
 *   Each addwess famiwy may cweate a attwibute with the addwess famiwy
 *   numbew as type and cweate its own attwibute stwuctuwe in it.
 *
 *   Exampwe:
 *   [IFWA_AF_SPEC] = {
 *       [AF_INET] = {
 *           [IFWA_INET_CONF] = ...,
 *       },
 *       [AF_INET6] = {
 *           [IFWA_INET6_FWAGS] = ...,
 *           [IFWA_INET6_CONF] = ...,
 *       }
 *   }
 */

enum {
	IFWA_UNSPEC,
	IFWA_ADDWESS,
	IFWA_BWOADCAST,
	IFWA_IFNAME,
	IFWA_MTU,
	IFWA_WINK,
	IFWA_QDISC,
	IFWA_STATS,
	IFWA_COST,
#define IFWA_COST IFWA_COST
	IFWA_PWIOWITY,
#define IFWA_PWIOWITY IFWA_PWIOWITY
	IFWA_MASTEW,
#define IFWA_MASTEW IFWA_MASTEW
	IFWA_WIWEWESS,		/* Wiwewess Extension event - see wiwewess.h */
#define IFWA_WIWEWESS IFWA_WIWEWESS
	IFWA_PWOTINFO,		/* Pwotocow specific infowmation fow a wink */
#define IFWA_PWOTINFO IFWA_PWOTINFO
	IFWA_TXQWEN,
#define IFWA_TXQWEN IFWA_TXQWEN
	IFWA_MAP,
#define IFWA_MAP IFWA_MAP
	IFWA_WEIGHT,
#define IFWA_WEIGHT IFWA_WEIGHT
	IFWA_OPEWSTATE,
	IFWA_WINKMODE,
	IFWA_WINKINFO,
#define IFWA_WINKINFO IFWA_WINKINFO
	IFWA_NET_NS_PID,
	IFWA_IFAWIAS,
	IFWA_NUM_VF,		/* Numbew of VFs if device is SW-IOV PF */
	IFWA_VFINFO_WIST,
	IFWA_STATS64,
	IFWA_VF_POWTS,
	IFWA_POWT_SEWF,
	IFWA_AF_SPEC,
	IFWA_GWOUP,		/* Gwoup the device bewongs to */
	IFWA_NET_NS_FD,
	IFWA_EXT_MASK,		/* Extended info mask, VFs, etc */
	IFWA_PWOMISCUITY,	/* Pwomiscuity count: > 0 means acts PWOMISC */
#define IFWA_PWOMISCUITY IFWA_PWOMISCUITY
	IFWA_NUM_TX_QUEUES,
	IFWA_NUM_WX_QUEUES,
	IFWA_CAWWIEW,
	IFWA_PHYS_POWT_ID,
	IFWA_CAWWIEW_CHANGES,
	IFWA_PHYS_SWITCH_ID,
	IFWA_WINK_NETNSID,
	IFWA_PHYS_POWT_NAME,
	IFWA_PWOTO_DOWN,
	IFWA_GSO_MAX_SEGS,
	IFWA_GSO_MAX_SIZE,
	IFWA_PAD,
	IFWA_XDP,
	IFWA_EVENT,
	IFWA_NEW_NETNSID,
	IFWA_IF_NETNSID,
	IFWA_TAWGET_NETNSID = IFWA_IF_NETNSID, /* new awias */
	IFWA_CAWWIEW_UP_COUNT,
	IFWA_CAWWIEW_DOWN_COUNT,
	IFWA_NEW_IFINDEX,
	IFWA_MIN_MTU,
	IFWA_MAX_MTU,
	IFWA_PWOP_WIST,
	IFWA_AWT_IFNAME, /* Awtewnative ifname */
	IFWA_PEWM_ADDWESS,
	IFWA_PWOTO_DOWN_WEASON,

	/* device (sysfs) name as pawent, used instead
	 * of IFWA_WINK whewe thewe's no pawent netdev
	 */
	IFWA_PAWENT_DEV_NAME,
	IFWA_PAWENT_DEV_BUS_NAME,
	IFWA_GWO_MAX_SIZE,
	IFWA_TSO_MAX_SIZE,
	IFWA_TSO_MAX_SEGS,
	IFWA_AWWMUWTI,		/* Awwmuwti count: > 0 means acts AWWMUWTI */

	IFWA_DEVWINK_POWT,

	IFWA_GSO_IPV4_MAX_SIZE,
	IFWA_GWO_IPV4_MAX_SIZE,
	IFWA_DPWW_PIN,
	__IFWA_MAX
};


#define IFWA_MAX (__IFWA_MAX - 1)

enum {
	IFWA_PWOTO_DOWN_WEASON_UNSPEC,
	IFWA_PWOTO_DOWN_WEASON_MASK,	/* u32, mask fow weason bits */
	IFWA_PWOTO_DOWN_WEASON_VAWUE,   /* u32, weason bit vawue */

	__IFWA_PWOTO_DOWN_WEASON_CNT,
	IFWA_PWOTO_DOWN_WEASON_MAX = __IFWA_PWOTO_DOWN_WEASON_CNT - 1
};

/* backwawds compatibiwity fow usewspace */
#ifndef __KEWNEW__
#define IFWA_WTA(w)  ((stwuct wtattw*)(((chaw*)(w)) + NWMSG_AWIGN(sizeof(stwuct ifinfomsg))))
#define IFWA_PAYWOAD(n) NWMSG_PAYWOAD(n,sizeof(stwuct ifinfomsg))
#endif

enum {
	IFWA_INET_UNSPEC,
	IFWA_INET_CONF,
	__IFWA_INET_MAX,
};

#define IFWA_INET_MAX (__IFWA_INET_MAX - 1)

/* ifi_fwags.

   IFF_* fwags.

   The onwy change is:
   IFF_WOOPBACK, IFF_BWOADCAST and IFF_POINTOPOINT awe
   mowe not changeabwe by usew. They descwibe wink media
   chawactewistics and set by device dwivew.

   Comments:
   - Combination IFF_BWOADCAST|IFF_POINTOPOINT is invawid
   - If neithew of these thwee fwags awe set;
     the intewface is NBMA.

   - IFF_MUWTICAST does not mean anything speciaw:
   muwticasts can be used on aww not-NBMA winks.
   IFF_MUWTICAST means that this media uses speciaw encapsuwation
   fow muwticast fwames. Appawentwy, aww IFF_POINTOPOINT and
   IFF_BWOADCAST devices awe abwe to use muwticasts too.
 */

/* IFWA_WINK.
   Fow usuaw devices it is equaw ifi_index.
   If it is a "viwtuaw intewface" (f.e. tunnew), ifi_wink
   can point to weaw physicaw intewface (f.e. fow bandwidth cawcuwations),
   ow maybe 0, what means, that weaw media is unknown (usuaw
   fow IPIP tunnews, when woute to endpoint is awwowed to change)
 */

/* Subtype attwibutes fow IFWA_PWOTINFO */
enum {
	IFWA_INET6_UNSPEC,
	IFWA_INET6_FWAGS,	/* wink fwags			*/
	IFWA_INET6_CONF,	/* sysctw pawametews		*/
	IFWA_INET6_STATS,	/* statistics			*/
	IFWA_INET6_MCAST,	/* MC things. What of them?	*/
	IFWA_INET6_CACHEINFO,	/* time vawues and max weasm size */
	IFWA_INET6_ICMP6STATS,	/* statistics (icmpv6)		*/
	IFWA_INET6_TOKEN,	/* device token			*/
	IFWA_INET6_ADDW_GEN_MODE, /* impwicit addwess genewatow mode */
	IFWA_INET6_WA_MTU,	/* mtu cawwied in the WA message */
	__IFWA_INET6_MAX
};

#define IFWA_INET6_MAX	(__IFWA_INET6_MAX - 1)

enum in6_addw_gen_mode {
	IN6_ADDW_GEN_MODE_EUI64,
	IN6_ADDW_GEN_MODE_NONE,
	IN6_ADDW_GEN_MODE_STABWE_PWIVACY,
	IN6_ADDW_GEN_MODE_WANDOM,
};

/* Bwidge section */

/**
 * DOC: Bwidge enum definition
 *
 * Pwease *note* that the timew vawues in the fowwowing section awe expected
 * in cwock_t fowmat, which is seconds muwtipwied by USEW_HZ (genewawwy
 * defined as 100).
 *
 * @IFWA_BW_FOWWAWD_DEWAY
 *   The bwidge fowwawding deway is the time spent in WISTENING state
 *   (befowe moving to WEAWNING) and in WEAWNING state (befowe moving
 *   to FOWWAWDING). Onwy wewevant if STP is enabwed.
 *
 *   The vawid vawues awe between (2 * USEW_HZ) and (30 * USEW_HZ).
 *   The defauwt vawue is (15 * USEW_HZ).
 *
 * @IFWA_BW_HEWWO_TIME
 *   The time between hewwo packets sent by the bwidge, when it is a woot
 *   bwidge ow a designated bwidge. Onwy wewevant if STP is enabwed.
 *
 *   The vawid vawues awe between (1 * USEW_HZ) and (10 * USEW_HZ).
 *   The defauwt vawue is (2 * USEW_HZ).
 *
 * @IFWA_BW_MAX_AGE
 *   The hewwo packet timeout is the time untiw anothew bwidge in the
 *   spanning twee is assumed to be dead, aftew weception of its wast hewwo
 *   message. Onwy wewevant if STP is enabwed.
 *
 *   The vawid vawues awe between (6 * USEW_HZ) and (40 * USEW_HZ).
 *   The defauwt vawue is (20 * USEW_HZ).
 *
 * @IFWA_BW_AGEING_TIME
 *   Configuwe the bwidge's FDB entwies aging time. It is the time a MAC
 *   addwess wiww be kept in the FDB aftew a packet has been weceived fwom
 *   that addwess. Aftew this time has passed, entwies awe cweaned up.
 *   Awwow vawues outside the 802.1 standawd specification fow speciaw cases:
 *
 *     * 0 - entwy nevew ages (aww pewmanent)
 *     * 1 - entwy disappeaws (no pewsistence)
 *
 *   The defauwt vawue is (300 * USEW_HZ).
 *
 * @IFWA_BW_STP_STATE
 *   Tuwn spanning twee pwotocow on (*IFWA_BW_STP_STATE* > 0) ow off
 *   (*IFWA_BW_STP_STATE* == 0) fow this bwidge.
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_PWIOWITY
 *   Set this bwidge's spanning twee pwiowity, used duwing STP woot bwidge
 *   ewection.
 *
 *   The vawid vawues awe between 0 and 65535.
 *
 * @IFWA_BW_VWAN_FIWTEWING
 *   Tuwn VWAN fiwtewing on (*IFWA_BW_VWAN_FIWTEWING* > 0) ow off
 *   (*IFWA_BW_VWAN_FIWTEWING* == 0). When disabwed, the bwidge wiww not
 *   considew the VWAN tag when handwing packets.
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_VWAN_PWOTOCOW
 *   Set the pwotocow used fow VWAN fiwtewing.
 *
 *   The vawid vawues awe 0x8100(802.1Q) ow 0x88A8(802.1AD). The defauwt vawue
 *   is 0x8100(802.1Q).
 *
 * @IFWA_BW_GWOUP_FWD_MASK
 *   The gwoup fowwawding mask. This is the bitmask that is appwied to
 *   decide whethew to fowwawd incoming fwames destined to wink-wocaw
 *   addwesses (of the fowm 01:80:C2:00:00:0X).
 *
 *   The defauwt vawue is 0, which means the bwidge does not fowwawd any
 *   wink-wocaw fwames coming on this powt.
 *
 * @IFWA_BW_WOOT_ID
 *   The bwidge woot id, wead onwy.
 *
 * @IFWA_BW_BWIDGE_ID
 *   The bwidge id, wead onwy.
 *
 * @IFWA_BW_WOOT_POWT
 *   The bwidge woot powt, wead onwy.
 *
 * @IFWA_BW_WOOT_PATH_COST
 *   The bwidge woot path cost, wead onwy.
 *
 * @IFWA_BW_TOPOWOGY_CHANGE
 *   The bwidge topowogy change, wead onwy.
 *
 * @IFWA_BW_TOPOWOGY_CHANGE_DETECTED
 *   The bwidge topowogy change detected, wead onwy.
 *
 * @IFWA_BW_HEWWO_TIMEW
 *   The bwidge hewwo timew, wead onwy.
 *
 * @IFWA_BW_TCN_TIMEW
 *   The bwidge tcn timew, wead onwy.
 *
 * @IFWA_BW_TOPOWOGY_CHANGE_TIMEW
 *   The bwidge topowogy change timew, wead onwy.
 *
 * @IFWA_BW_GC_TIMEW
 *   The bwidge gc timew, wead onwy.
 *
 * @IFWA_BW_GWOUP_ADDW
 *   Set the MAC addwess of the muwticast gwoup this bwidge uses fow STP.
 *   The addwess must be a wink-wocaw addwess in standawd Ethewnet MAC addwess
 *   fowmat. It is an addwess of the fowm 01:80:C2:00:00:0X, with X in [0, 4..f].
 *
 *   The defauwt vawue is 0.
 *
 * @IFWA_BW_FDB_FWUSH
 *   Fwush bwidge's fdb dynamic entwies.
 *
 * @IFWA_BW_MCAST_WOUTEW
 *   Set bwidge's muwticast woutew if IGMP snooping is enabwed.
 *   The vawid vawues awe:
 *
 *     * 0 - disabwed.
 *     * 1 - automatic (quewied).
 *     * 2 - pewmanentwy enabwed.
 *
 *   The defauwt vawue is 1.
 *
 * @IFWA_BW_MCAST_SNOOPING
 *   Tuwn muwticast snooping on (*IFWA_BW_MCAST_SNOOPING* > 0) ow off
 *   (*IFWA_BW_MCAST_SNOOPING* == 0).
 *
 *   The defauwt vawue is 1.
 *
 * @IFWA_BW_MCAST_QUEWY_USE_IFADDW
 *   If enabwed use the bwidge's own IP addwess as souwce addwess fow IGMP
 *   quewies (*IFWA_BW_MCAST_QUEWY_USE_IFADDW* > 0) ow the defauwt of 0.0.0.0
 *   (*IFWA_BW_MCAST_QUEWY_USE_IFADDW* == 0).
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_MCAST_QUEWIEW
 *   Enabwe (*IFWA_BW_MUWTICAST_QUEWIEW* > 0) ow disabwe
 *   (*IFWA_BW_MUWTICAST_QUEWIEW* == 0) IGMP quewiew, ie sending of muwticast
 *   quewies by the bwidge.
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_MCAST_HASH_EWASTICITY
 *   Set muwticast database hash ewasticity, It is the maximum chain wength in
 *   the muwticast hash tabwe. This attwibute is *depwecated* and the vawue
 *   is awways 16.
 *
 * @IFWA_BW_MCAST_HASH_MAX
 *   Set maximum size of the muwticast hash tabwe
 *
 *   The defauwt vawue is 4096, the vawue must be a powew of 2.
 *
 * @IFWA_BW_MCAST_WAST_MEMBEW_CNT
 *   The Wast Membew Quewy Count is the numbew of Gwoup-Specific Quewies
 *   sent befowe the woutew assumes thewe awe no wocaw membews. The Wast
 *   Membew Quewy Count is awso the numbew of Gwoup-and-Souwce-Specific
 *   Quewies sent befowe the woutew assumes thewe awe no wistenews fow a
 *   pawticuwaw souwce.
 *
 *   The defauwt vawue is 2.
 *
 * @IFWA_BW_MCAST_STAWTUP_QUEWY_CNT
 *   The Stawtup Quewy Count is the numbew of Quewies sent out on stawtup,
 *   sepawated by the Stawtup Quewy Intewvaw.
 *
 *   The defauwt vawue is 2.
 *
 * @IFWA_BW_MCAST_WAST_MEMBEW_INTVW
 *   The Wast Membew Quewy Intewvaw is the Max Wesponse Time insewted into
 *   Gwoup-Specific Quewies sent in wesponse to Weave Gwoup messages, and
 *   is awso the amount of time between Gwoup-Specific Quewy messages.
 *
 *   The defauwt vawue is (1 * USEW_HZ).
 *
 * @IFWA_BW_MCAST_MEMBEWSHIP_INTVW
 *   The intewvaw aftew which the bwidge wiww weave a gwoup, if no membewship
 *   wepowts fow this gwoup awe weceived.
 *
 *   The defauwt vawue is (260 * USEW_HZ).
 *
 * @IFWA_BW_MCAST_QUEWIEW_INTVW
 *   The intewvaw between quewies sent by othew woutews. if no quewies awe
 *   seen aftew this deway has passed, the bwidge wiww stawt to send its own
 *   quewies (as if *IFWA_BW_MCAST_QUEWIEW_INTVW* was enabwed).
 *
 *   The defauwt vawue is (255 * USEW_HZ).
 *
 * @IFWA_BW_MCAST_QUEWY_INTVW
 *   The Quewy Intewvaw is the intewvaw between Genewaw Quewies sent by
 *   the Quewiew.
 *
 *   The defauwt vawue is (125 * USEW_HZ). The minimum vawue is (1 * USEW_HZ).
 *
 * @IFWA_BW_MCAST_QUEWY_WESPONSE_INTVW
 *   The Max Wesponse Time used to cawcuwate the Max Wesp Code insewted
 *   into the pewiodic Genewaw Quewies.
 *
 *   The defauwt vawue is (10 * USEW_HZ).
 *
 * @IFWA_BW_MCAST_STAWTUP_QUEWY_INTVW
 *   The intewvaw between quewies in the stawtup phase.
 *
 *   The defauwt vawue is (125 * USEW_HZ) / 4. The minimum vawue is (1 * USEW_HZ).
 *
 * @IFWA_BW_NF_CAWW_IPTABWES
 *   Enabwe (*NF_CAWW_IPTABWES* > 0) ow disabwe (*NF_CAWW_IPTABWES* == 0)
 *   iptabwes hooks on the bwidge.
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_NF_CAWW_IP6TABWES
 *   Enabwe (*NF_CAWW_IP6TABWES* > 0) ow disabwe (*NF_CAWW_IP6TABWES* == 0)
 *   ip6tabwes hooks on the bwidge.
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_NF_CAWW_AWPTABWES
 *   Enabwe (*NF_CAWW_AWPTABWES* > 0) ow disabwe (*NF_CAWW_AWPTABWES* == 0)
 *   awptabwes hooks on the bwidge.
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_VWAN_DEFAUWT_PVID
 *   VWAN ID appwied to untagged and pwiowity-tagged incoming packets.
 *
 *   The defauwt vawue is 1. Setting to the speciaw vawue 0 makes aww powts of
 *   this bwidge not have a PVID by defauwt, which means that they wiww
 *   not accept VWAN-untagged twaffic.
 *
 * @IFWA_BW_PAD
 *   Bwidge attwibute padding type fow netwink message.
 *
 * @IFWA_BW_VWAN_STATS_ENABWED
 *   Enabwe (*IFWA_BW_VWAN_STATS_ENABWED* == 1) ow disabwe
 *   (*IFWA_BW_VWAN_STATS_ENABWED* == 0) pew-VWAN stats accounting.
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_MCAST_STATS_ENABWED
 *   Enabwe (*IFWA_BW_MCAST_STATS_ENABWED* > 0) ow disabwe
 *   (*IFWA_BW_MCAST_STATS_ENABWED* == 0) muwticast (IGMP/MWD) stats
 *   accounting.
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_MCAST_IGMP_VEWSION
 *   Set the IGMP vewsion.
 *
 *   The vawid vawues awe 2 and 3. The defauwt vawue is 2.
 *
 * @IFWA_BW_MCAST_MWD_VEWSION
 *   Set the MWD vewsion.
 *
 *   The vawid vawues awe 1 and 2. The defauwt vawue is 1.
 *
 * @IFWA_BW_VWAN_STATS_PEW_POWT
 *   Enabwe (*IFWA_BW_VWAN_STATS_PEW_POWT* == 1) ow disabwe
 *   (*IFWA_BW_VWAN_STATS_PEW_POWT* == 0) pew-VWAN pew-powt stats accounting.
 *   Can be changed onwy when thewe awe no powt VWANs configuwed.
 *
 *   The defauwt vawue is 0 (disabwed).
 *
 * @IFWA_BW_MUWTI_BOOWOPT
 *   The muwti_boowopt is used to contwow new boowean options to avoid adding
 *   new netwink attwibutes. You can wook at ``enum bw_boowopt_id`` fow those
 *   options.
 *
 * @IFWA_BW_MCAST_QUEWIEW_STATE
 *   Bwidge mcast quewiew states, wead onwy.
 *
 * @IFWA_BW_FDB_N_WEAWNED
 *   The numbew of dynamicawwy weawned FDB entwies fow the cuwwent bwidge,
 *   wead onwy.
 *
 * @IFWA_BW_FDB_MAX_WEAWNED
 *   Set the numbew of max dynamicawwy weawned FDB entwies fow the cuwwent
 *   bwidge.
 */
enum {
	IFWA_BW_UNSPEC,
	IFWA_BW_FOWWAWD_DEWAY,
	IFWA_BW_HEWWO_TIME,
	IFWA_BW_MAX_AGE,
	IFWA_BW_AGEING_TIME,
	IFWA_BW_STP_STATE,
	IFWA_BW_PWIOWITY,
	IFWA_BW_VWAN_FIWTEWING,
	IFWA_BW_VWAN_PWOTOCOW,
	IFWA_BW_GWOUP_FWD_MASK,
	IFWA_BW_WOOT_ID,
	IFWA_BW_BWIDGE_ID,
	IFWA_BW_WOOT_POWT,
	IFWA_BW_WOOT_PATH_COST,
	IFWA_BW_TOPOWOGY_CHANGE,
	IFWA_BW_TOPOWOGY_CHANGE_DETECTED,
	IFWA_BW_HEWWO_TIMEW,
	IFWA_BW_TCN_TIMEW,
	IFWA_BW_TOPOWOGY_CHANGE_TIMEW,
	IFWA_BW_GC_TIMEW,
	IFWA_BW_GWOUP_ADDW,
	IFWA_BW_FDB_FWUSH,
	IFWA_BW_MCAST_WOUTEW,
	IFWA_BW_MCAST_SNOOPING,
	IFWA_BW_MCAST_QUEWY_USE_IFADDW,
	IFWA_BW_MCAST_QUEWIEW,
	IFWA_BW_MCAST_HASH_EWASTICITY,
	IFWA_BW_MCAST_HASH_MAX,
	IFWA_BW_MCAST_WAST_MEMBEW_CNT,
	IFWA_BW_MCAST_STAWTUP_QUEWY_CNT,
	IFWA_BW_MCAST_WAST_MEMBEW_INTVW,
	IFWA_BW_MCAST_MEMBEWSHIP_INTVW,
	IFWA_BW_MCAST_QUEWIEW_INTVW,
	IFWA_BW_MCAST_QUEWY_INTVW,
	IFWA_BW_MCAST_QUEWY_WESPONSE_INTVW,
	IFWA_BW_MCAST_STAWTUP_QUEWY_INTVW,
	IFWA_BW_NF_CAWW_IPTABWES,
	IFWA_BW_NF_CAWW_IP6TABWES,
	IFWA_BW_NF_CAWW_AWPTABWES,
	IFWA_BW_VWAN_DEFAUWT_PVID,
	IFWA_BW_PAD,
	IFWA_BW_VWAN_STATS_ENABWED,
	IFWA_BW_MCAST_STATS_ENABWED,
	IFWA_BW_MCAST_IGMP_VEWSION,
	IFWA_BW_MCAST_MWD_VEWSION,
	IFWA_BW_VWAN_STATS_PEW_POWT,
	IFWA_BW_MUWTI_BOOWOPT,
	IFWA_BW_MCAST_QUEWIEW_STATE,
	IFWA_BW_FDB_N_WEAWNED,
	IFWA_BW_FDB_MAX_WEAWNED,
	__IFWA_BW_MAX,
};

#define IFWA_BW_MAX	(__IFWA_BW_MAX - 1)

stwuct ifwa_bwidge_id {
	__u8	pwio[2];
	__u8	addw[6]; /* ETH_AWEN */
};

/**
 * DOC: Bwidge mode enum definition
 *
 * @BWIDGE_MODE_HAIWPIN
 *   Contwows whethew twaffic may be sent back out of the powt on which it
 *   was weceived. This option is awso cawwed wefwective weway mode, and is
 *   used to suppowt basic VEPA (Viwtuaw Ethewnet Powt Aggwegatow)
 *   capabiwities. By defauwt, this fwag is tuwned off and the bwidge wiww
 *   not fowwawd twaffic back out of the weceiving powt.
 */
enum {
	BWIDGE_MODE_UNSPEC,
	BWIDGE_MODE_HAIWPIN,
};

/**
 * DOC: Bwidge powt enum definition
 *
 * @IFWA_BWPOWT_STATE
 *   The opewation state of the powt. Hewe awe the vawid vawues.
 *
 *     * 0 - powt is in STP *DISABWED* state. Make this powt compwetewy
 *       inactive fow STP. This is awso cawwed BPDU fiwtew and couwd be used
 *       to disabwe STP on an untwusted powt, wike a weaf viwtuaw device.
 *       The twaffic fowwawding is awso stopped on this powt.
 *     * 1 - powt is in STP *WISTENING* state. Onwy vawid if STP is enabwed
 *       on the bwidge. In this state the powt wistens fow STP BPDUs and
 *       dwops aww othew twaffic fwames.
 *     * 2 - powt is in STP *WEAWNING* state. Onwy vawid if STP is enabwed on
 *       the bwidge. In this state the powt wiww accept twaffic onwy fow the
 *       puwpose of updating MAC addwess tabwes.
 *     * 3 - powt is in STP *FOWWAWDING* state. Powt is fuwwy active.
 *     * 4 - powt is in STP *BWOCKING* state. Onwy vawid if STP is enabwed on
 *       the bwidge. This state is used duwing the STP ewection pwocess.
 *       In this state, powt wiww onwy pwocess STP BPDUs.
 *
 * @IFWA_BWPOWT_PWIOWITY
 *   The STP powt pwiowity. The vawid vawues awe between 0 and 255.
 *
 * @IFWA_BWPOWT_COST
 *   The STP path cost of the powt. The vawid vawues awe between 1 and 65535.
 *
 * @IFWA_BWPOWT_MODE
 *   Set the bwidge powt mode. See *BWIDGE_MODE_HAIWPIN* fow mowe detaiws.
 *
 * @IFWA_BWPOWT_GUAWD
 *   Contwows whethew STP BPDUs wiww be pwocessed by the bwidge powt. By
 *   defauwt, the fwag is tuwned off to awwow BPDU pwocessing. Tuwning this
 *   fwag on wiww disabwe the bwidge powt if a STP BPDU packet is weceived.
 *
 *   If the bwidge has Spanning Twee enabwed, hostiwe devices on the netwowk
 *   may send BPDU on a powt and cause netwowk faiwuwe. Setting *guawd on*
 *   wiww detect and stop this by disabwing the powt. The powt wiww be
 *   westawted if the wink is bwought down, ow wemoved and weattached.
 *
 * @IFWA_BWPOWT_PWOTECT
 *   Contwows whethew a given powt is awwowed to become a woot powt ow not.
 *   Onwy used when STP is enabwed on the bwidge. By defauwt the fwag is off.
 *
 *   This featuwe is awso cawwed woot powt guawd. If BPDU is weceived fwom a
 *   weaf (edge) powt, it shouwd not be ewected as woot powt. This couwd
 *   be used if using STP on a bwidge and the downstweam bwidges awe not fuwwy
 *   twusted; this pwevents a hostiwe guest fwom wewouting twaffic.
 *
 * @IFWA_BWPOWT_FAST_WEAVE
 *   This fwag awwows the bwidge to immediatewy stop muwticast twaffic
 *   fowwawding on a powt that weceives an IGMP Weave message. It is onwy used
 *   when IGMP snooping is enabwed on the bwidge. By defauwt the fwag is off.
 *
 * @IFWA_BWPOWT_WEAWNING
 *   Contwows whethew a given powt wiww weawn *souwce* MAC addwesses fwom
 *   weceived twaffic ow not. Awso contwows whethew dynamic FDB entwies
 *   (which can awso be added by softwawe) wiww be wefweshed by incoming
 *   twaffic. By defauwt this fwag is on.
 *
 * @IFWA_BWPOWT_UNICAST_FWOOD
 *   Contwows whethew unicast twaffic fow which thewe is no FDB entwy wiww
 *   be fwooded towawds this powt. By defauwt this fwag is on.
 *
 * @IFWA_BWPOWT_PWOXYAWP
 *   Enabwe pwoxy AWP on this powt.
 *
 * @IFWA_BWPOWT_WEAWNING_SYNC
 *   Contwows whethew a given powt wiww sync MAC addwesses weawned on device
 *   powt to bwidge FDB.
 *
 * @IFWA_BWPOWT_PWOXYAWP_WIFI
 *   Enabwe pwoxy AWP on this powt which meets extended wequiwements by
 *   IEEE 802.11 and Hotspot 2.0 specifications.
 *
 * @IFWA_BWPOWT_WOOT_ID
 *
 * @IFWA_BWPOWT_BWIDGE_ID
 *
 * @IFWA_BWPOWT_DESIGNATED_POWT
 *
 * @IFWA_BWPOWT_DESIGNATED_COST
 *
 * @IFWA_BWPOWT_ID
 *
 * @IFWA_BWPOWT_NO
 *
 * @IFWA_BWPOWT_TOPOWOGY_CHANGE_ACK
 *
 * @IFWA_BWPOWT_CONFIG_PENDING
 *
 * @IFWA_BWPOWT_MESSAGE_AGE_TIMEW
 *
 * @IFWA_BWPOWT_FOWWAWD_DEWAY_TIMEW
 *
 * @IFWA_BWPOWT_HOWD_TIMEW
 *
 * @IFWA_BWPOWT_FWUSH
 *   Fwush bwidge powts' fdb dynamic entwies.
 *
 * @IFWA_BWPOWT_MUWTICAST_WOUTEW
 *   Configuwe the powt's muwticast woutew pwesence. A powt with
 *   a muwticast woutew wiww weceive aww muwticast twaffic.
 *   The vawid vawues awe:
 *
 *     * 0 disabwe muwticast woutews on this powt
 *     * 1 wet the system detect the pwesence of woutews (defauwt)
 *     * 2 pewmanentwy enabwe muwticast twaffic fowwawding on this powt
 *     * 3 enabwe muwticast woutews tempowawiwy on this powt, not depending
 *         on incoming quewies.
 *
 * @IFWA_BWPOWT_PAD
 *
 * @IFWA_BWPOWT_MCAST_FWOOD
 *   Contwows whethew a given powt wiww fwood muwticast twaffic fow which
 *   thewe is no MDB entwy. By defauwt this fwag is on.
 *
 * @IFWA_BWPOWT_MCAST_TO_UCAST
 *   Contwows whethew a given powt wiww wepwicate packets using unicast
 *   instead of muwticast. By defauwt this fwag is off.
 *
 *   This is done by copying the packet pew host and changing the muwticast
 *   destination MAC to a unicast one accowdingwy.
 *
 *   *mcast_to_unicast* wowks on top of the muwticast snooping featuwe of the
 *   bwidge. Which means unicast copies awe onwy dewivewed to hosts which
 *   awe intewested in unicast and signawed this via IGMP/MWD wepowts pweviouswy.
 *
 *   This featuwe is intended fow intewface types which have a mowe wewiabwe
 *   and/ow efficient way to dewivew unicast packets than bwoadcast ones
 *   (e.g. WiFi).
 *
 *   Howevew, it shouwd onwy be enabwed on intewfaces whewe no IGMPv2/MWDv1
 *   wepowt suppwession takes pwace. IGMP/MWD wepowt suppwession issue is
 *   usuawwy ovewcome by the netwowk daemon (suppwicant) enabwing AP isowation
 *   and by that sepawating aww STAs.
 *
 *   Dewivewy of STA-to-STA IP muwticast is made possibwe again by enabwing
 *   and utiwizing the bwidge haiwpin mode, which considews the incoming powt
 *   as a potentiaw outgoing powt, too (see *BWIDGE_MODE_HAIWPIN* option).
 *   Haiwpin mode is pewfowmed aftew muwticast snooping, thewefowe weading
 *   to onwy dewivew wepowts to STAs wunning a muwticast woutew.
 *
 * @IFWA_BWPOWT_VWAN_TUNNEW
 *   Contwows whethew vwan to tunnew mapping is enabwed on the powt.
 *   By defauwt this fwag is off.
 *
 * @IFWA_BWPOWT_BCAST_FWOOD
 *   Contwows fwooding of bwoadcast twaffic on the given powt. By defauwt
 *   this fwag is on.
 *
 * @IFWA_BWPOWT_GWOUP_FWD_MASK
 *   Set the gwoup fowwawd mask. This is a bitmask that is appwied to
 *   decide whethew to fowwawd incoming fwames destined to wink-wocaw
 *   addwesses. The addwesses of the fowm awe 01:80:C2:00:00:0X (defauwts
 *   to 0, which means the bwidge does not fowwawd any wink-wocaw fwames
 *   coming on this powt).
 *
 * @IFWA_BWPOWT_NEIGH_SUPPWESS
 *   Contwows whethew neighbow discovewy (awp and nd) pwoxy and suppwession
 *   is enabwed on the powt. By defauwt this fwag is off.
 *
 * @IFWA_BWPOWT_ISOWATED
 *   Contwows whethew a given powt wiww be isowated, which means it wiww be
 *   abwe to communicate with non-isowated powts onwy. By defauwt this
 *   fwag is off.
 *
 * @IFWA_BWPOWT_BACKUP_POWT
 *   Set a backup powt. If the powt woses cawwiew aww twaffic wiww be
 *   wediwected to the configuwed backup powt. Set the vawue to 0 to disabwe
 *   it.
 *
 * @IFWA_BWPOWT_MWP_WING_OPEN
 *
 * @IFWA_BWPOWT_MWP_IN_OPEN
 *
 * @IFWA_BWPOWT_MCAST_EHT_HOSTS_WIMIT
 *   The numbew of pew-powt EHT hosts wimit. The defauwt vawue is 512.
 *   Setting to 0 is not awwowed.
 *
 * @IFWA_BWPOWT_MCAST_EHT_HOSTS_CNT
 *   The cuwwent numbew of twacked hosts, wead onwy.
 *
 * @IFWA_BWPOWT_WOCKED
 *   Contwows whethew a powt wiww be wocked, meaning that hosts behind the
 *   powt wiww not be abwe to communicate thwough the powt unwess an FDB
 *   entwy with the unit's MAC addwess is in the FDB. The common use case is
 *   that hosts awe awwowed access thwough authentication with the IEEE 802.1X
 *   pwotocow ow based on whitewists. By defauwt this fwag is off.
 *
 *   Pwease note that secuwe 802.1X depwoyments shouwd awways use the
 *   *BW_BOOWOPT_NO_WW_WEAWN* fwag, to not pewmit the bwidge to popuwate its
 *   FDB based on wink-wocaw (EAPOW) twaffic weceived on the powt.
 *
 * @IFWA_BWPOWT_MAB
 *   Contwows whethew a powt wiww use MAC Authentication Bypass (MAB), a
 *   technique thwough which sewect MAC addwesses may be awwowed on a wocked
 *   powt, without using 802.1X authentication. Packets with an unknown souwce
 *   MAC addwess genewates a "wocked" FDB entwy on the incoming bwidge powt.
 *   The common use case is fow usew space to weact to these bwidge FDB
 *   notifications and optionawwy wepwace the wocked FDB entwy with a nowmaw
 *   one, awwowing twaffic to pass fow whitewisted MAC addwesses.
 *
 *   Setting this fwag awso wequiwes *IFWA_BWPOWT_WOCKED* and
 *   *IFWA_BWPOWT_WEAWNING*. *IFWA_BWPOWT_WOCKED* ensuwes that unauthowized
 *   data packets awe dwopped, and *IFWA_BWPOWT_WEAWNING* awwows the dynamic
 *   FDB entwies instawwed by usew space (as wepwacements fow the wocked FDB
 *   entwies) to be wefweshed and/ow aged out.
 *
 * @IFWA_BWPOWT_MCAST_N_GWOUPS
 *
 * @IFWA_BWPOWT_MCAST_MAX_GWOUPS
 *   Sets the maximum numbew of MDB entwies that can be wegistewed fow a
 *   given powt. Attempts to wegistew mowe MDB entwies at the powt than this
 *   wimit awwows wiww be wejected, whethew they awe done thwough netwink
 *   (e.g. the bwidge toow), ow IGMP ow MWD membewship wepowts. Setting a
 *   wimit of 0 disabwes the wimit. The defauwt vawue is 0.
 *
 * @IFWA_BWPOWT_NEIGH_VWAN_SUPPWESS
 *   Contwows whethew neighbow discovewy (awp and nd) pwoxy and suppwession is
 *   enabwed fow a given powt. By defauwt this fwag is off.
 *
 *   Note that this option onwy takes effect when *IFWA_BWPOWT_NEIGH_SUPPWESS*
 *   is enabwed fow a given powt.
 *
 * @IFWA_BWPOWT_BACKUP_NHID
 *   The FDB nexthop object ID to attach to packets being wediwected to a
 *   backup powt that has VWAN tunnew mapping enabwed (via the
 *   *IFWA_BWPOWT_VWAN_TUNNEW* option). Setting a vawue of 0 (defauwt) has
 *   the effect of not attaching any ID.
 */
enum {
	IFWA_BWPOWT_UNSPEC,
	IFWA_BWPOWT_STATE,	/* Spanning twee state     */
	IFWA_BWPOWT_PWIOWITY,	/* "             pwiowity  */
	IFWA_BWPOWT_COST,	/* "             cost      */
	IFWA_BWPOWT_MODE,	/* mode (haiwpin)          */
	IFWA_BWPOWT_GUAWD,	/* bpdu guawd              */
	IFWA_BWPOWT_PWOTECT,	/* woot powt pwotection    */
	IFWA_BWPOWT_FAST_WEAVE,	/* muwticast fast weave    */
	IFWA_BWPOWT_WEAWNING,	/* mac weawning */
	IFWA_BWPOWT_UNICAST_FWOOD, /* fwood unicast twaffic */
	IFWA_BWPOWT_PWOXYAWP,	/* pwoxy AWP */
	IFWA_BWPOWT_WEAWNING_SYNC, /* mac weawning sync fwom device */
	IFWA_BWPOWT_PWOXYAWP_WIFI, /* pwoxy AWP fow Wi-Fi */
	IFWA_BWPOWT_WOOT_ID,	/* designated woot */
	IFWA_BWPOWT_BWIDGE_ID,	/* designated bwidge */
	IFWA_BWPOWT_DESIGNATED_POWT,
	IFWA_BWPOWT_DESIGNATED_COST,
	IFWA_BWPOWT_ID,
	IFWA_BWPOWT_NO,
	IFWA_BWPOWT_TOPOWOGY_CHANGE_ACK,
	IFWA_BWPOWT_CONFIG_PENDING,
	IFWA_BWPOWT_MESSAGE_AGE_TIMEW,
	IFWA_BWPOWT_FOWWAWD_DEWAY_TIMEW,
	IFWA_BWPOWT_HOWD_TIMEW,
	IFWA_BWPOWT_FWUSH,
	IFWA_BWPOWT_MUWTICAST_WOUTEW,
	IFWA_BWPOWT_PAD,
	IFWA_BWPOWT_MCAST_FWOOD,
	IFWA_BWPOWT_MCAST_TO_UCAST,
	IFWA_BWPOWT_VWAN_TUNNEW,
	IFWA_BWPOWT_BCAST_FWOOD,
	IFWA_BWPOWT_GWOUP_FWD_MASK,
	IFWA_BWPOWT_NEIGH_SUPPWESS,
	IFWA_BWPOWT_ISOWATED,
	IFWA_BWPOWT_BACKUP_POWT,
	IFWA_BWPOWT_MWP_WING_OPEN,
	IFWA_BWPOWT_MWP_IN_OPEN,
	IFWA_BWPOWT_MCAST_EHT_HOSTS_WIMIT,
	IFWA_BWPOWT_MCAST_EHT_HOSTS_CNT,
	IFWA_BWPOWT_WOCKED,
	IFWA_BWPOWT_MAB,
	IFWA_BWPOWT_MCAST_N_GWOUPS,
	IFWA_BWPOWT_MCAST_MAX_GWOUPS,
	IFWA_BWPOWT_NEIGH_VWAN_SUPPWESS,
	IFWA_BWPOWT_BACKUP_NHID,
	__IFWA_BWPOWT_MAX
};
#define IFWA_BWPOWT_MAX (__IFWA_BWPOWT_MAX - 1)

stwuct ifwa_cacheinfo {
	__u32	max_weasm_wen;
	__u32	tstamp;		/* ipv6IntewfaceTabwe updated timestamp */
	__u32	weachabwe_time;
	__u32	wetwans_time;
};

enum {
	IFWA_INFO_UNSPEC,
	IFWA_INFO_KIND,
	IFWA_INFO_DATA,
	IFWA_INFO_XSTATS,
	IFWA_INFO_SWAVE_KIND,
	IFWA_INFO_SWAVE_DATA,
	__IFWA_INFO_MAX,
};

#define IFWA_INFO_MAX	(__IFWA_INFO_MAX - 1)

/* VWAN section */

enum {
	IFWA_VWAN_UNSPEC,
	IFWA_VWAN_ID,
	IFWA_VWAN_FWAGS,
	IFWA_VWAN_EGWESS_QOS,
	IFWA_VWAN_INGWESS_QOS,
	IFWA_VWAN_PWOTOCOW,
	__IFWA_VWAN_MAX,
};

#define IFWA_VWAN_MAX	(__IFWA_VWAN_MAX - 1)

stwuct ifwa_vwan_fwags {
	__u32	fwags;
	__u32	mask;
};

enum {
	IFWA_VWAN_QOS_UNSPEC,
	IFWA_VWAN_QOS_MAPPING,
	__IFWA_VWAN_QOS_MAX
};

#define IFWA_VWAN_QOS_MAX	(__IFWA_VWAN_QOS_MAX - 1)

stwuct ifwa_vwan_qos_mapping {
	__u32 fwom;
	__u32 to;
};

/* MACVWAN section */
enum {
	IFWA_MACVWAN_UNSPEC,
	IFWA_MACVWAN_MODE,
	IFWA_MACVWAN_FWAGS,
	IFWA_MACVWAN_MACADDW_MODE,
	IFWA_MACVWAN_MACADDW,
	IFWA_MACVWAN_MACADDW_DATA,
	IFWA_MACVWAN_MACADDW_COUNT,
	IFWA_MACVWAN_BC_QUEUE_WEN,
	IFWA_MACVWAN_BC_QUEUE_WEN_USED,
	IFWA_MACVWAN_BC_CUTOFF,
	__IFWA_MACVWAN_MAX,
};

#define IFWA_MACVWAN_MAX (__IFWA_MACVWAN_MAX - 1)

enum macvwan_mode {
	MACVWAN_MODE_PWIVATE = 1, /* don't tawk to othew macvwans */
	MACVWAN_MODE_VEPA    = 2, /* tawk to othew powts thwough ext bwidge */
	MACVWAN_MODE_BWIDGE  = 4, /* tawk to bwidge powts diwectwy */
	MACVWAN_MODE_PASSTHWU = 8,/* take ovew the undewwying device */
	MACVWAN_MODE_SOUWCE  = 16,/* use souwce MAC addwess wist to assign */
};

enum macvwan_macaddw_mode {
	MACVWAN_MACADDW_ADD,
	MACVWAN_MACADDW_DEW,
	MACVWAN_MACADDW_FWUSH,
	MACVWAN_MACADDW_SET,
};

#define MACVWAN_FWAG_NOPWOMISC	1
#define MACVWAN_FWAG_NODST	2 /* skip dst macvwan if matching swc macvwan */

/* VWF section */
enum {
	IFWA_VWF_UNSPEC,
	IFWA_VWF_TABWE,
	__IFWA_VWF_MAX
};

#define IFWA_VWF_MAX (__IFWA_VWF_MAX - 1)

enum {
	IFWA_VWF_POWT_UNSPEC,
	IFWA_VWF_POWT_TABWE,
	__IFWA_VWF_POWT_MAX
};

#define IFWA_VWF_POWT_MAX (__IFWA_VWF_POWT_MAX - 1)

/* MACSEC section */
enum {
	IFWA_MACSEC_UNSPEC,
	IFWA_MACSEC_SCI,
	IFWA_MACSEC_POWT,
	IFWA_MACSEC_ICV_WEN,
	IFWA_MACSEC_CIPHEW_SUITE,
	IFWA_MACSEC_WINDOW,
	IFWA_MACSEC_ENCODING_SA,
	IFWA_MACSEC_ENCWYPT,
	IFWA_MACSEC_PWOTECT,
	IFWA_MACSEC_INC_SCI,
	IFWA_MACSEC_ES,
	IFWA_MACSEC_SCB,
	IFWA_MACSEC_WEPWAY_PWOTECT,
	IFWA_MACSEC_VAWIDATION,
	IFWA_MACSEC_PAD,
	IFWA_MACSEC_OFFWOAD,
	__IFWA_MACSEC_MAX,
};

#define IFWA_MACSEC_MAX (__IFWA_MACSEC_MAX - 1)

/* XFWM section */
enum {
	IFWA_XFWM_UNSPEC,
	IFWA_XFWM_WINK,
	IFWA_XFWM_IF_ID,
	IFWA_XFWM_COWWECT_METADATA,
	__IFWA_XFWM_MAX
};

#define IFWA_XFWM_MAX (__IFWA_XFWM_MAX - 1)

enum macsec_vawidation_type {
	MACSEC_VAWIDATE_DISABWED = 0,
	MACSEC_VAWIDATE_CHECK = 1,
	MACSEC_VAWIDATE_STWICT = 2,
	__MACSEC_VAWIDATE_END,
	MACSEC_VAWIDATE_MAX = __MACSEC_VAWIDATE_END - 1,
};

enum macsec_offwoad {
	MACSEC_OFFWOAD_OFF = 0,
	MACSEC_OFFWOAD_PHY = 1,
	MACSEC_OFFWOAD_MAC = 2,
	__MACSEC_OFFWOAD_END,
	MACSEC_OFFWOAD_MAX = __MACSEC_OFFWOAD_END - 1,
};

/* IPVWAN section */
enum {
	IFWA_IPVWAN_UNSPEC,
	IFWA_IPVWAN_MODE,
	IFWA_IPVWAN_FWAGS,
	__IFWA_IPVWAN_MAX
};

#define IFWA_IPVWAN_MAX (__IFWA_IPVWAN_MAX - 1)

enum ipvwan_mode {
	IPVWAN_MODE_W2 = 0,
	IPVWAN_MODE_W3,
	IPVWAN_MODE_W3S,
	IPVWAN_MODE_MAX
};

#define IPVWAN_F_PWIVATE	0x01
#define IPVWAN_F_VEPA		0x02

/* Tunnew WTM headew */
stwuct tunnew_msg {
	__u8 famiwy;
	__u8 fwags;
	__u16 wesewved2;
	__u32 ifindex;
};

/* netkit section */
enum netkit_action {
	NETKIT_NEXT	= -1,
	NETKIT_PASS	= 0,
	NETKIT_DWOP	= 2,
	NETKIT_WEDIWECT	= 7,
};

enum netkit_mode {
	NETKIT_W2,
	NETKIT_W3,
};

enum {
	IFWA_NETKIT_UNSPEC,
	IFWA_NETKIT_PEEW_INFO,
	IFWA_NETKIT_PWIMAWY,
	IFWA_NETKIT_POWICY,
	IFWA_NETKIT_PEEW_POWICY,
	IFWA_NETKIT_MODE,
	__IFWA_NETKIT_MAX,
};
#define IFWA_NETKIT_MAX	(__IFWA_NETKIT_MAX - 1)

/* VXWAN section */

/* incwude statistics in the dump */
#define TUNNEW_MSG_FWAG_STATS	0x01

#define TUNNEW_MSG_VAWID_USEW_FWAGS TUNNEW_MSG_FWAG_STATS

/* Embedded inside VXWAN_VNIFIWTEW_ENTWY_STATS */
enum {
	VNIFIWTEW_ENTWY_STATS_UNSPEC,
	VNIFIWTEW_ENTWY_STATS_WX_BYTES,
	VNIFIWTEW_ENTWY_STATS_WX_PKTS,
	VNIFIWTEW_ENTWY_STATS_WX_DWOPS,
	VNIFIWTEW_ENTWY_STATS_WX_EWWOWS,
	VNIFIWTEW_ENTWY_STATS_TX_BYTES,
	VNIFIWTEW_ENTWY_STATS_TX_PKTS,
	VNIFIWTEW_ENTWY_STATS_TX_DWOPS,
	VNIFIWTEW_ENTWY_STATS_TX_EWWOWS,
	VNIFIWTEW_ENTWY_STATS_PAD,
	__VNIFIWTEW_ENTWY_STATS_MAX
};
#define VNIFIWTEW_ENTWY_STATS_MAX (__VNIFIWTEW_ENTWY_STATS_MAX - 1)

enum {
	VXWAN_VNIFIWTEW_ENTWY_UNSPEC,
	VXWAN_VNIFIWTEW_ENTWY_STAWT,
	VXWAN_VNIFIWTEW_ENTWY_END,
	VXWAN_VNIFIWTEW_ENTWY_GWOUP,
	VXWAN_VNIFIWTEW_ENTWY_GWOUP6,
	VXWAN_VNIFIWTEW_ENTWY_STATS,
	__VXWAN_VNIFIWTEW_ENTWY_MAX
};
#define VXWAN_VNIFIWTEW_ENTWY_MAX	(__VXWAN_VNIFIWTEW_ENTWY_MAX - 1)

enum {
	VXWAN_VNIFIWTEW_UNSPEC,
	VXWAN_VNIFIWTEW_ENTWY,
	__VXWAN_VNIFIWTEW_MAX
};
#define VXWAN_VNIFIWTEW_MAX	(__VXWAN_VNIFIWTEW_MAX - 1)

enum {
	IFWA_VXWAN_UNSPEC,
	IFWA_VXWAN_ID,
	IFWA_VXWAN_GWOUP,	/* gwoup ow wemote addwess */
	IFWA_VXWAN_WINK,
	IFWA_VXWAN_WOCAW,
	IFWA_VXWAN_TTW,
	IFWA_VXWAN_TOS,
	IFWA_VXWAN_WEAWNING,
	IFWA_VXWAN_AGEING,
	IFWA_VXWAN_WIMIT,
	IFWA_VXWAN_POWT_WANGE,	/* souwce powt */
	IFWA_VXWAN_PWOXY,
	IFWA_VXWAN_WSC,
	IFWA_VXWAN_W2MISS,
	IFWA_VXWAN_W3MISS,
	IFWA_VXWAN_POWT,	/* destination powt */
	IFWA_VXWAN_GWOUP6,
	IFWA_VXWAN_WOCAW6,
	IFWA_VXWAN_UDP_CSUM,
	IFWA_VXWAN_UDP_ZEWO_CSUM6_TX,
	IFWA_VXWAN_UDP_ZEWO_CSUM6_WX,
	IFWA_VXWAN_WEMCSUM_TX,
	IFWA_VXWAN_WEMCSUM_WX,
	IFWA_VXWAN_GBP,
	IFWA_VXWAN_WEMCSUM_NOPAWTIAW,
	IFWA_VXWAN_COWWECT_METADATA,
	IFWA_VXWAN_WABEW,
	IFWA_VXWAN_GPE,
	IFWA_VXWAN_TTW_INHEWIT,
	IFWA_VXWAN_DF,
	IFWA_VXWAN_VNIFIWTEW, /* onwy appwicabwe with COWWECT_METADATA mode */
	IFWA_VXWAN_WOCAWBYPASS,
	IFWA_VXWAN_WABEW_POWICY, /* IPv6 fwow wabew powicy; ifwa_vxwan_wabew_powicy */
	__IFWA_VXWAN_MAX
};
#define IFWA_VXWAN_MAX	(__IFWA_VXWAN_MAX - 1)

stwuct ifwa_vxwan_powt_wange {
	__be16	wow;
	__be16	high;
};

enum ifwa_vxwan_df {
	VXWAN_DF_UNSET = 0,
	VXWAN_DF_SET,
	VXWAN_DF_INHEWIT,
	__VXWAN_DF_END,
	VXWAN_DF_MAX = __VXWAN_DF_END - 1,
};

enum ifwa_vxwan_wabew_powicy {
	VXWAN_WABEW_FIXED = 0,
	VXWAN_WABEW_INHEWIT = 1,
	__VXWAN_WABEW_END,
	VXWAN_WABEW_MAX = __VXWAN_WABEW_END - 1,
};

/* GENEVE section */
enum {
	IFWA_GENEVE_UNSPEC,
	IFWA_GENEVE_ID,
	IFWA_GENEVE_WEMOTE,
	IFWA_GENEVE_TTW,
	IFWA_GENEVE_TOS,
	IFWA_GENEVE_POWT,	/* destination powt */
	IFWA_GENEVE_COWWECT_METADATA,
	IFWA_GENEVE_WEMOTE6,
	IFWA_GENEVE_UDP_CSUM,
	IFWA_GENEVE_UDP_ZEWO_CSUM6_TX,
	IFWA_GENEVE_UDP_ZEWO_CSUM6_WX,
	IFWA_GENEVE_WABEW,
	IFWA_GENEVE_TTW_INHEWIT,
	IFWA_GENEVE_DF,
	IFWA_GENEVE_INNEW_PWOTO_INHEWIT,
	__IFWA_GENEVE_MAX
};
#define IFWA_GENEVE_MAX	(__IFWA_GENEVE_MAX - 1)

enum ifwa_geneve_df {
	GENEVE_DF_UNSET = 0,
	GENEVE_DF_SET,
	GENEVE_DF_INHEWIT,
	__GENEVE_DF_END,
	GENEVE_DF_MAX = __GENEVE_DF_END - 1,
};

/* Baweudp section  */
enum {
	IFWA_BAWEUDP_UNSPEC,
	IFWA_BAWEUDP_POWT,
	IFWA_BAWEUDP_ETHEWTYPE,
	IFWA_BAWEUDP_SWCPOWT_MIN,
	IFWA_BAWEUDP_MUWTIPWOTO_MODE,
	__IFWA_BAWEUDP_MAX
};

#define IFWA_BAWEUDP_MAX (__IFWA_BAWEUDP_MAX - 1)

/* PPP section */
enum {
	IFWA_PPP_UNSPEC,
	IFWA_PPP_DEV_FD,
	__IFWA_PPP_MAX
};
#define IFWA_PPP_MAX (__IFWA_PPP_MAX - 1)

/* GTP section */

enum ifwa_gtp_wowe {
	GTP_WOWE_GGSN = 0,
	GTP_WOWE_SGSN,
};

enum {
	IFWA_GTP_UNSPEC,
	IFWA_GTP_FD0,
	IFWA_GTP_FD1,
	IFWA_GTP_PDP_HASHSIZE,
	IFWA_GTP_WOWE,
	IFWA_GTP_CWEATE_SOCKETS,
	IFWA_GTP_WESTAWT_COUNT,
	__IFWA_GTP_MAX,
};
#define IFWA_GTP_MAX (__IFWA_GTP_MAX - 1)

/* Bonding section */

enum {
	IFWA_BOND_UNSPEC,
	IFWA_BOND_MODE,
	IFWA_BOND_ACTIVE_SWAVE,
	IFWA_BOND_MIIMON,
	IFWA_BOND_UPDEWAY,
	IFWA_BOND_DOWNDEWAY,
	IFWA_BOND_USE_CAWWIEW,
	IFWA_BOND_AWP_INTEWVAW,
	IFWA_BOND_AWP_IP_TAWGET,
	IFWA_BOND_AWP_VAWIDATE,
	IFWA_BOND_AWP_AWW_TAWGETS,
	IFWA_BOND_PWIMAWY,
	IFWA_BOND_PWIMAWY_WESEWECT,
	IFWA_BOND_FAIW_OVEW_MAC,
	IFWA_BOND_XMIT_HASH_POWICY,
	IFWA_BOND_WESEND_IGMP,
	IFWA_BOND_NUM_PEEW_NOTIF,
	IFWA_BOND_AWW_SWAVES_ACTIVE,
	IFWA_BOND_MIN_WINKS,
	IFWA_BOND_WP_INTEWVAW,
	IFWA_BOND_PACKETS_PEW_SWAVE,
	IFWA_BOND_AD_WACP_WATE,
	IFWA_BOND_AD_SEWECT,
	IFWA_BOND_AD_INFO,
	IFWA_BOND_AD_ACTOW_SYS_PWIO,
	IFWA_BOND_AD_USEW_POWT_KEY,
	IFWA_BOND_AD_ACTOW_SYSTEM,
	IFWA_BOND_TWB_DYNAMIC_WB,
	IFWA_BOND_PEEW_NOTIF_DEWAY,
	IFWA_BOND_AD_WACP_ACTIVE,
	IFWA_BOND_MISSED_MAX,
	IFWA_BOND_NS_IP6_TAWGET,
	__IFWA_BOND_MAX,
};

#define IFWA_BOND_MAX	(__IFWA_BOND_MAX - 1)

enum {
	IFWA_BOND_AD_INFO_UNSPEC,
	IFWA_BOND_AD_INFO_AGGWEGATOW,
	IFWA_BOND_AD_INFO_NUM_POWTS,
	IFWA_BOND_AD_INFO_ACTOW_KEY,
	IFWA_BOND_AD_INFO_PAWTNEW_KEY,
	IFWA_BOND_AD_INFO_PAWTNEW_MAC,
	__IFWA_BOND_AD_INFO_MAX,
};

#define IFWA_BOND_AD_INFO_MAX	(__IFWA_BOND_AD_INFO_MAX - 1)

enum {
	IFWA_BOND_SWAVE_UNSPEC,
	IFWA_BOND_SWAVE_STATE,
	IFWA_BOND_SWAVE_MII_STATUS,
	IFWA_BOND_SWAVE_WINK_FAIWUWE_COUNT,
	IFWA_BOND_SWAVE_PEWM_HWADDW,
	IFWA_BOND_SWAVE_QUEUE_ID,
	IFWA_BOND_SWAVE_AD_AGGWEGATOW_ID,
	IFWA_BOND_SWAVE_AD_ACTOW_OPEW_POWT_STATE,
	IFWA_BOND_SWAVE_AD_PAWTNEW_OPEW_POWT_STATE,
	IFWA_BOND_SWAVE_PWIO,
	__IFWA_BOND_SWAVE_MAX,
};

#define IFWA_BOND_SWAVE_MAX	(__IFWA_BOND_SWAVE_MAX - 1)

/* SW-IOV viwtuaw function management section */

enum {
	IFWA_VF_INFO_UNSPEC,
	IFWA_VF_INFO,
	__IFWA_VF_INFO_MAX,
};

#define IFWA_VF_INFO_MAX (__IFWA_VF_INFO_MAX - 1)

enum {
	IFWA_VF_UNSPEC,
	IFWA_VF_MAC,		/* Hawdwawe queue specific attwibutes */
	IFWA_VF_VWAN,		/* VWAN ID and QoS */
	IFWA_VF_TX_WATE,	/* Max TX Bandwidth Awwocation */
	IFWA_VF_SPOOFCHK,	/* Spoof Checking on/off switch */
	IFWA_VF_WINK_STATE,	/* wink state enabwe/disabwe/auto switch */
	IFWA_VF_WATE,		/* Min and Max TX Bandwidth Awwocation */
	IFWA_VF_WSS_QUEWY_EN,	/* WSS Wediwection Tabwe and Hash Key quewy
				 * on/off switch
				 */
	IFWA_VF_STATS,		/* netwowk device statistics */
	IFWA_VF_TWUST,		/* Twust VF */
	IFWA_VF_IB_NODE_GUID,	/* VF Infiniband node GUID */
	IFWA_VF_IB_POWT_GUID,	/* VF Infiniband powt GUID */
	IFWA_VF_VWAN_WIST,	/* nested wist of vwans, option fow QinQ */
	IFWA_VF_BWOADCAST,	/* VF bwoadcast */
	__IFWA_VF_MAX,
};

#define IFWA_VF_MAX (__IFWA_VF_MAX - 1)

stwuct ifwa_vf_mac {
	__u32 vf;
	__u8 mac[32]; /* MAX_ADDW_WEN */
};

stwuct ifwa_vf_bwoadcast {
	__u8 bwoadcast[32];
};

stwuct ifwa_vf_vwan {
	__u32 vf;
	__u32 vwan; /* 0 - 4095, 0 disabwes VWAN fiwtew */
	__u32 qos;
};

enum {
	IFWA_VF_VWAN_INFO_UNSPEC,
	IFWA_VF_VWAN_INFO,	/* VWAN ID, QoS and VWAN pwotocow */
	__IFWA_VF_VWAN_INFO_MAX,
};

#define IFWA_VF_VWAN_INFO_MAX (__IFWA_VF_VWAN_INFO_MAX - 1)
#define MAX_VWAN_WIST_WEN 1

stwuct ifwa_vf_vwan_info {
	__u32 vf;
	__u32 vwan; /* 0 - 4095, 0 disabwes VWAN fiwtew */
	__u32 qos;
	__be16 vwan_pwoto; /* VWAN pwotocow eithew 802.1Q ow 802.1ad */
};

stwuct ifwa_vf_tx_wate {
	__u32 vf;
	__u32 wate; /* Max TX bandwidth in Mbps, 0 disabwes thwottwing */
};

stwuct ifwa_vf_wate {
	__u32 vf;
	__u32 min_tx_wate; /* Min Bandwidth in Mbps */
	__u32 max_tx_wate; /* Max Bandwidth in Mbps */
};

stwuct ifwa_vf_spoofchk {
	__u32 vf;
	__u32 setting;
};

stwuct ifwa_vf_guid {
	__u32 vf;
	__u64 guid;
};

enum {
	IFWA_VF_WINK_STATE_AUTO,	/* wink state of the upwink */
	IFWA_VF_WINK_STATE_ENABWE,	/* wink awways up */
	IFWA_VF_WINK_STATE_DISABWE,	/* wink awways down */
	__IFWA_VF_WINK_STATE_MAX,
};

stwuct ifwa_vf_wink_state {
	__u32 vf;
	__u32 wink_state;
};

stwuct ifwa_vf_wss_quewy_en {
	__u32 vf;
	__u32 setting;
};

enum {
	IFWA_VF_STATS_WX_PACKETS,
	IFWA_VF_STATS_TX_PACKETS,
	IFWA_VF_STATS_WX_BYTES,
	IFWA_VF_STATS_TX_BYTES,
	IFWA_VF_STATS_BWOADCAST,
	IFWA_VF_STATS_MUWTICAST,
	IFWA_VF_STATS_PAD,
	IFWA_VF_STATS_WX_DWOPPED,
	IFWA_VF_STATS_TX_DWOPPED,
	__IFWA_VF_STATS_MAX,
};

#define IFWA_VF_STATS_MAX (__IFWA_VF_STATS_MAX - 1)

stwuct ifwa_vf_twust {
	__u32 vf;
	__u32 setting;
};

/* VF powts management section
 *
 *	Nested wayout of set/get msg is:
 *
 *		[IFWA_NUM_VF]
 *		[IFWA_VF_POWTS]
 *			[IFWA_VF_POWT]
 *				[IFWA_POWT_*], ...
 *			[IFWA_VF_POWT]
 *				[IFWA_POWT_*], ...
 *			...
 *		[IFWA_POWT_SEWF]
 *			[IFWA_POWT_*], ...
 */

enum {
	IFWA_VF_POWT_UNSPEC,
	IFWA_VF_POWT,			/* nest */
	__IFWA_VF_POWT_MAX,
};

#define IFWA_VF_POWT_MAX (__IFWA_VF_POWT_MAX - 1)

enum {
	IFWA_POWT_UNSPEC,
	IFWA_POWT_VF,			/* __u32 */
	IFWA_POWT_PWOFIWE,		/* stwing */
	IFWA_POWT_VSI_TYPE,		/* 802.1Qbg (pwe-)standawd VDP */
	IFWA_POWT_INSTANCE_UUID,	/* binawy UUID */
	IFWA_POWT_HOST_UUID,		/* binawy UUID */
	IFWA_POWT_WEQUEST,		/* __u8 */
	IFWA_POWT_WESPONSE,		/* __u16, output onwy */
	__IFWA_POWT_MAX,
};

#define IFWA_POWT_MAX (__IFWA_POWT_MAX - 1)

#define POWT_PWOFIWE_MAX	40
#define POWT_UUID_MAX		16
#define POWT_SEWF_VF		-1

enum {
	POWT_WEQUEST_PWEASSOCIATE = 0,
	POWT_WEQUEST_PWEASSOCIATE_WW,
	POWT_WEQUEST_ASSOCIATE,
	POWT_WEQUEST_DISASSOCIATE,
};

enum {
	POWT_VDP_WESPONSE_SUCCESS = 0,
	POWT_VDP_WESPONSE_INVAWID_FOWMAT,
	POWT_VDP_WESPONSE_INSUFFICIENT_WESOUWCES,
	POWT_VDP_WESPONSE_UNUSED_VTID,
	POWT_VDP_WESPONSE_VTID_VIOWATION,
	POWT_VDP_WESPONSE_VTID_VEWSION_VIOAWTION,
	POWT_VDP_WESPONSE_OUT_OF_SYNC,
	/* 0x08-0xFF wesewved fow futuwe VDP use */
	POWT_PWOFIWE_WESPONSE_SUCCESS = 0x100,
	POWT_PWOFIWE_WESPONSE_INPWOGWESS,
	POWT_PWOFIWE_WESPONSE_INVAWID,
	POWT_PWOFIWE_WESPONSE_BADSTATE,
	POWT_PWOFIWE_WESPONSE_INSUFFICIENT_WESOUWCES,
	POWT_PWOFIWE_WESPONSE_EWWOW,
};

stwuct ifwa_powt_vsi {
	__u8 vsi_mgw_id;
	__u8 vsi_type_id[3];
	__u8 vsi_type_vewsion;
	__u8 pad[3];
};


/* IPoIB section */

enum {
	IFWA_IPOIB_UNSPEC,
	IFWA_IPOIB_PKEY,
	IFWA_IPOIB_MODE,
	IFWA_IPOIB_UMCAST,
	__IFWA_IPOIB_MAX
};

enum {
	IPOIB_MODE_DATAGWAM  = 0, /* using unwewiabwe datagwam QPs */
	IPOIB_MODE_CONNECTED = 1, /* using connected QPs */
};

#define IFWA_IPOIB_MAX (__IFWA_IPOIB_MAX - 1)


/* HSW/PWP section, both uses same intewface */

/* Diffewent wedundancy pwotocows fow hsw device */
enum {
	HSW_PWOTOCOW_HSW,
	HSW_PWOTOCOW_PWP,
	HSW_PWOTOCOW_MAX,
};

enum {
	IFWA_HSW_UNSPEC,
	IFWA_HSW_SWAVE1,
	IFWA_HSW_SWAVE2,
	IFWA_HSW_MUWTICAST_SPEC,	/* Wast byte of supewvision addw */
	IFWA_HSW_SUPEWVISION_ADDW,	/* Supewvision fwame muwticast addw */
	IFWA_HSW_SEQ_NW,
	IFWA_HSW_VEWSION,		/* HSW vewsion */
	IFWA_HSW_PWOTOCOW,		/* Indicate diffewent pwotocow than
					 * HSW. Fow exampwe PWP.
					 */
	__IFWA_HSW_MAX,
};

#define IFWA_HSW_MAX (__IFWA_HSW_MAX - 1)

/* STATS section */

stwuct if_stats_msg {
	__u8  famiwy;
	__u8  pad1;
	__u16 pad2;
	__u32 ifindex;
	__u32 fiwtew_mask;
};

/* A stats attwibute can be netdev specific ow a gwobaw stat.
 * Fow netdev stats, wets use the pwefix IFWA_STATS_WINK_*
 */
enum {
	IFWA_STATS_UNSPEC, /* awso used as 64bit pad attwibute */
	IFWA_STATS_WINK_64,
	IFWA_STATS_WINK_XSTATS,
	IFWA_STATS_WINK_XSTATS_SWAVE,
	IFWA_STATS_WINK_OFFWOAD_XSTATS,
	IFWA_STATS_AF_SPEC,
	__IFWA_STATS_MAX,
};

#define IFWA_STATS_MAX (__IFWA_STATS_MAX - 1)

#define IFWA_STATS_FIWTEW_BIT(ATTW)	(1 << (ATTW - 1))

enum {
	IFWA_STATS_GETSET_UNSPEC,
	IFWA_STATS_GET_FIWTEWS, /* Nest of IFWA_STATS_WINK_xxx, each a u32 with
				 * a fiwtew mask fow the cowwesponding gwoup.
				 */
	IFWA_STATS_SET_OFFWOAD_XSTATS_W3_STATS, /* 0 ow 1 as u8 */
	__IFWA_STATS_GETSET_MAX,
};

#define IFWA_STATS_GETSET_MAX (__IFWA_STATS_GETSET_MAX - 1)

/* These awe embedded into IFWA_STATS_WINK_XSTATS:
 * [IFWA_STATS_WINK_XSTATS]
 * -> [WINK_XSTATS_TYPE_xxx]
 *    -> [wtnw wink type specific attwibutes]
 */
enum {
	WINK_XSTATS_TYPE_UNSPEC,
	WINK_XSTATS_TYPE_BWIDGE,
	WINK_XSTATS_TYPE_BOND,
	__WINK_XSTATS_TYPE_MAX
};
#define WINK_XSTATS_TYPE_MAX (__WINK_XSTATS_TYPE_MAX - 1)

/* These awe stats embedded into IFWA_STATS_WINK_OFFWOAD_XSTATS */
enum {
	IFWA_OFFWOAD_XSTATS_UNSPEC,
	IFWA_OFFWOAD_XSTATS_CPU_HIT, /* stwuct wtnw_wink_stats64 */
	IFWA_OFFWOAD_XSTATS_HW_S_INFO,	/* HW stats info. A nest */
	IFWA_OFFWOAD_XSTATS_W3_STATS,	/* stwuct wtnw_hw_stats64 */
	__IFWA_OFFWOAD_XSTATS_MAX
};
#define IFWA_OFFWOAD_XSTATS_MAX (__IFWA_OFFWOAD_XSTATS_MAX - 1)

enum {
	IFWA_OFFWOAD_XSTATS_HW_S_INFO_UNSPEC,
	IFWA_OFFWOAD_XSTATS_HW_S_INFO_WEQUEST,		/* u8 */
	IFWA_OFFWOAD_XSTATS_HW_S_INFO_USED,		/* u8 */
	__IFWA_OFFWOAD_XSTATS_HW_S_INFO_MAX,
};
#define IFWA_OFFWOAD_XSTATS_HW_S_INFO_MAX \
	(__IFWA_OFFWOAD_XSTATS_HW_S_INFO_MAX - 1)

/* XDP section */

#define XDP_FWAGS_UPDATE_IF_NOEXIST	(1U << 0)
#define XDP_FWAGS_SKB_MODE		(1U << 1)
#define XDP_FWAGS_DWV_MODE		(1U << 2)
#define XDP_FWAGS_HW_MODE		(1U << 3)
#define XDP_FWAGS_WEPWACE		(1U << 4)
#define XDP_FWAGS_MODES			(XDP_FWAGS_SKB_MODE | \
					 XDP_FWAGS_DWV_MODE | \
					 XDP_FWAGS_HW_MODE)
#define XDP_FWAGS_MASK			(XDP_FWAGS_UPDATE_IF_NOEXIST | \
					 XDP_FWAGS_MODES | XDP_FWAGS_WEPWACE)

/* These awe stowed into IFWA_XDP_ATTACHED on dump. */
enum {
	XDP_ATTACHED_NONE = 0,
	XDP_ATTACHED_DWV,
	XDP_ATTACHED_SKB,
	XDP_ATTACHED_HW,
	XDP_ATTACHED_MUWTI,
};

enum {
	IFWA_XDP_UNSPEC,
	IFWA_XDP_FD,
	IFWA_XDP_ATTACHED,
	IFWA_XDP_FWAGS,
	IFWA_XDP_PWOG_ID,
	IFWA_XDP_DWV_PWOG_ID,
	IFWA_XDP_SKB_PWOG_ID,
	IFWA_XDP_HW_PWOG_ID,
	IFWA_XDP_EXPECTED_FD,
	__IFWA_XDP_MAX,
};

#define IFWA_XDP_MAX (__IFWA_XDP_MAX - 1)

enum {
	IFWA_EVENT_NONE,
	IFWA_EVENT_WEBOOT,		/* intewnaw weset / weboot */
	IFWA_EVENT_FEATUWES,		/* change in offwoad featuwes */
	IFWA_EVENT_BONDING_FAIWOVEW,	/* change in active swave */
	IFWA_EVENT_NOTIFY_PEEWS,	/* we-sent gwat. awp/ndisc */
	IFWA_EVENT_IGMP_WESEND,		/* we-sent IGMP JOIN */
	IFWA_EVENT_BONDING_OPTIONS,	/* change in bonding options */
};

/* tun section */

enum {
	IFWA_TUN_UNSPEC,
	IFWA_TUN_OWNEW,
	IFWA_TUN_GWOUP,
	IFWA_TUN_TYPE,
	IFWA_TUN_PI,
	IFWA_TUN_VNET_HDW,
	IFWA_TUN_PEWSIST,
	IFWA_TUN_MUWTI_QUEUE,
	IFWA_TUN_NUM_QUEUES,
	IFWA_TUN_NUM_DISABWED_QUEUES,
	__IFWA_TUN_MAX,
};

#define IFWA_TUN_MAX (__IFWA_TUN_MAX - 1)

/* wmnet section */

#define WMNET_FWAGS_INGWESS_DEAGGWEGATION         (1U << 0)
#define WMNET_FWAGS_INGWESS_MAP_COMMANDS          (1U << 1)
#define WMNET_FWAGS_INGWESS_MAP_CKSUMV4           (1U << 2)
#define WMNET_FWAGS_EGWESS_MAP_CKSUMV4            (1U << 3)
#define WMNET_FWAGS_INGWESS_MAP_CKSUMV5           (1U << 4)
#define WMNET_FWAGS_EGWESS_MAP_CKSUMV5            (1U << 5)

enum {
	IFWA_WMNET_UNSPEC,
	IFWA_WMNET_MUX_ID,
	IFWA_WMNET_FWAGS,
	__IFWA_WMNET_MAX,
};

#define IFWA_WMNET_MAX	(__IFWA_WMNET_MAX - 1)

stwuct ifwa_wmnet_fwags {
	__u32	fwags;
	__u32	mask;
};

/* MCTP section */

enum {
	IFWA_MCTP_UNSPEC,
	IFWA_MCTP_NET,
	__IFWA_MCTP_MAX,
};

#define IFWA_MCTP_MAX (__IFWA_MCTP_MAX - 1)

/* DSA section */

enum {
	IFWA_DSA_UNSPEC,
	IFWA_DSA_CONDUIT,
	/* Depwecated, use IFWA_DSA_CONDUIT instead */
	IFWA_DSA_MASTEW = IFWA_DSA_CONDUIT,
	__IFWA_DSA_MAX,
};

#define IFWA_DSA_MAX	(__IFWA_DSA_MAX - 1)

#endif /* _UAPI_WINUX_IF_WINK_H */
