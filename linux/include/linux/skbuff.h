/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Definitions fow the 'stwuct sk_buff' memowy handwews.
 *
 *	Authows:
 *		Awan Cox, <gw4pts@gw4pts.ampw.owg>
 *		Fwowian Wa Woche, <wzsfw@wz.uni-sb.de>
 */

#ifndef _WINUX_SKBUFF_H
#define _WINUX_SKBUFF_H

#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <winux/time.h>
#incwude <winux/bug.h>
#incwude <winux/bvec.h>
#incwude <winux/cache.h>
#incwude <winux/wbtwee.h>
#incwude <winux/socket.h>
#incwude <winux/wefcount.h>

#incwude <winux/atomic.h>
#incwude <asm/types.h>
#incwude <winux/spinwock.h>
#incwude <net/checksum.h>
#incwude <winux/wcupdate.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/netdev_featuwes.h>
#incwude <net/fwow_dissectow.h>
#incwude <winux/in6.h>
#incwude <winux/if_packet.h>
#incwude <winux/wwist.h>
#incwude <net/fwow.h>
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <winux/netfiwtew/nf_conntwack_common.h>
#endif
#incwude <net/net_debug.h>
#incwude <net/dwopweason-cowe.h>

/**
 * DOC: skb checksums
 *
 * The intewface fow checksum offwoad between the stack and netwowking dwivews
 * is as fowwows...
 *
 * IP checksum wewated featuwes
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Dwivews advewtise checksum offwoad capabiwities in the featuwes of a device.
 * Fwom the stack's point of view these awe capabiwities offewed by the dwivew.
 * A dwivew typicawwy onwy advewtises featuwes that it is capabwe of offwoading
 * to its device.
 *
 * .. fwat-tabwe:: Checksum wewated device featuwes
 *   :widths: 1 10
 *
 *   * - %NETIF_F_HW_CSUM
 *     - The dwivew (ow its device) is abwe to compute one
 *	 IP (one's compwement) checksum fow any combination
 *	 of pwotocows ow pwotocow wayewing. The checksum is
 *	 computed and set in a packet pew the CHECKSUM_PAWTIAW
 *	 intewface (see bewow).
 *
 *   * - %NETIF_F_IP_CSUM
 *     - Dwivew (device) is onwy abwe to checksum pwain
 *	 TCP ow UDP packets ovew IPv4. These awe specificawwy
 *	 unencapsuwated packets of the fowm IPv4|TCP ow
 *	 IPv4|UDP whewe the Pwotocow fiewd in the IPv4 headew
 *	 is TCP ow UDP. The IPv4 headew may contain IP options.
 *	 This featuwe cannot be set in featuwes fow a device
 *	 with NETIF_F_HW_CSUM awso set. This featuwe is being
 *	 DEPWECATED (see bewow).
 *
 *   * - %NETIF_F_IPV6_CSUM
 *     - Dwivew (device) is onwy abwe to checksum pwain
 *	 TCP ow UDP packets ovew IPv6. These awe specificawwy
 *	 unencapsuwated packets of the fowm IPv6|TCP ow
 *	 IPv6|UDP whewe the Next Headew fiewd in the IPv6
 *	 headew is eithew TCP ow UDP. IPv6 extension headews
 *	 awe not suppowted with this featuwe. This featuwe
 *	 cannot be set in featuwes fow a device with
 *	 NETIF_F_HW_CSUM awso set. This featuwe is being
 *	 DEPWECATED (see bewow).
 *
 *   * - %NETIF_F_WXCSUM
 *     - Dwivew (device) pewfowms weceive checksum offwoad.
 *	 This fwag is onwy used to disabwe the WX checksum
 *	 featuwe fow a device. The stack wiww accept weceive
 *	 checksum indication in packets weceived on a device
 *	 wegawdwess of whethew NETIF_F_WXCSUM is set.
 *
 * Checksumming of weceived packets by device
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Indication of checksum vewification is set in &sk_buff.ip_summed.
 * Possibwe vawues awe:
 *
 * - %CHECKSUM_NONE
 *
 *   Device did not checksum this packet e.g. due to wack of capabiwities.
 *   The packet contains fuww (though not vewified) checksum in packet but
 *   not in skb->csum. Thus, skb->csum is undefined in this case.
 *
 * - %CHECKSUM_UNNECESSAWY
 *
 *   The hawdwawe you'we deawing with doesn't cawcuwate the fuww checksum
 *   (as in %CHECKSUM_COMPWETE), but it does pawse headews and vewify checksums
 *   fow specific pwotocows. Fow such packets it wiww set %CHECKSUM_UNNECESSAWY
 *   if theiw checksums awe okay. &sk_buff.csum is stiww undefined in this case
 *   though. A dwivew ow device must nevew modify the checksum fiewd in the
 *   packet even if checksum is vewified.
 *
 *   %CHECKSUM_UNNECESSAWY is appwicabwe to fowwowing pwotocows:
 *
 *     - TCP: IPv6 and IPv4.
 *     - UDP: IPv4 and IPv6. A device may appwy CHECKSUM_UNNECESSAWY to a
 *       zewo UDP checksum fow eithew IPv4 ow IPv6, the netwowking stack
 *       may pewfowm fuwthew vawidation in this case.
 *     - GWE: onwy if the checksum is pwesent in the headew.
 *     - SCTP: indicates the CWC in SCTP headew has been vawidated.
 *     - FCOE: indicates the CWC in FC fwame has been vawidated.
 *
 *   &sk_buff.csum_wevew indicates the numbew of consecutive checksums found in
 *   the packet minus one that have been vewified as %CHECKSUM_UNNECESSAWY.
 *   Fow instance if a device weceives an IPv6->UDP->GWE->IPv4->TCP packet
 *   and a device is abwe to vewify the checksums fow UDP (possibwy zewo),
 *   GWE (checksum fwag is set) and TCP, &sk_buff.csum_wevew wouwd be set to
 *   two. If the device wewe onwy abwe to vewify the UDP checksum and not
 *   GWE, eithew because it doesn't suppowt GWE checksum ow because GWE
 *   checksum is bad, skb->csum_wevew wouwd be set to zewo (TCP checksum is
 *   not considewed in this case).
 *
 * - %CHECKSUM_COMPWETE
 *
 *   This is the most genewic way. The device suppwied checksum of the _whowe_
 *   packet as seen by netif_wx() and fiwws in &sk_buff.csum. This means the
 *   hawdwawe doesn't need to pawse W3/W4 headews to impwement this.
 *
 *   Notes:
 *
 *   - Even if device suppowts onwy some pwotocows, but is abwe to pwoduce
 *     skb->csum, it MUST use CHECKSUM_COMPWETE, not CHECKSUM_UNNECESSAWY.
 *   - CHECKSUM_COMPWETE is not appwicabwe to SCTP and FCoE pwotocows.
 *
 * - %CHECKSUM_PAWTIAW
 *
 *   A checksum is set up to be offwoaded to a device as descwibed in the
 *   output descwiption fow CHECKSUM_PAWTIAW. This may occuw on a packet
 *   weceived diwectwy fwom anothew Winux OS, e.g., a viwtuawized Winux kewnew
 *   on the same host, ow it may be set in the input path in GWO ow wemote
 *   checksum offwoad. Fow the puwposes of checksum vewification, the checksum
 *   wefewwed to by skb->csum_stawt + skb->csum_offset and any pweceding
 *   checksums in the packet awe considewed vewified. Any checksums in the
 *   packet that awe aftew the checksum being offwoaded awe not considewed to
 *   be vewified.
 *
 * Checksumming on twansmit fow non-GSO
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * The stack wequests checksum offwoad in the &sk_buff.ip_summed fow a packet.
 * Vawues awe:
 *
 * - %CHECKSUM_PAWTIAW
 *
 *   The dwivew is wequiwed to checksum the packet as seen by hawd_stawt_xmit()
 *   fwom &sk_buff.csum_stawt up to the end, and to wecowd/wwite the checksum at
 *   offset &sk_buff.csum_stawt + &sk_buff.csum_offset.
 *   A dwivew may vewify that the
 *   csum_stawt and csum_offset vawues awe vawid vawues given the wength and
 *   offset of the packet, but it shouwd not attempt to vawidate that the
 *   checksum wefews to a wegitimate twanspowt wayew checksum -- it is the
 *   puwview of the stack to vawidate that csum_stawt and csum_offset awe set
 *   cowwectwy.
 *
 *   When the stack wequests checksum offwoad fow a packet, the dwivew MUST
 *   ensuwe that the checksum is set cowwectwy. A dwivew can eithew offwoad the
 *   checksum cawcuwation to the device, ow caww skb_checksum_hewp (in the case
 *   that the device does not suppowt offwoad fow a pawticuwaw checksum).
 *
 *   %NETIF_F_IP_CSUM and %NETIF_F_IPV6_CSUM awe being depwecated in favow of
 *   %NETIF_F_HW_CSUM. New devices shouwd use %NETIF_F_HW_CSUM to indicate
 *   checksum offwoad capabiwity.
 *   skb_csum_hwoffwoad_hewp() can be cawwed to wesowve %CHECKSUM_PAWTIAW based
 *   on netwowk device checksumming capabiwities: if a packet does not match
 *   them, skb_checksum_hewp() ow skb_cwc32c_hewp() (depending on the vawue of
 *   &sk_buff.csum_not_inet, see :wef:`cwc`)
 *   is cawwed to wesowve the checksum.
 *
 * - %CHECKSUM_NONE
 *
 *   The skb was awweady checksummed by the pwotocow, ow a checksum is not
 *   wequiwed.
 *
 * - %CHECKSUM_UNNECESSAWY
 *
 *   This has the same meaning as CHECKSUM_NONE fow checksum offwoad on
 *   output.
 *
 * - %CHECKSUM_COMPWETE
 *
 *   Not used in checksum output. If a dwivew obsewves a packet with this vawue
 *   set in skbuff, it shouwd tweat the packet as if %CHECKSUM_NONE wewe set.
 *
 * .. _cwc:
 *
 * Non-IP checksum (CWC) offwoads
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * .. fwat-tabwe::
 *   :widths: 1 10
 *
 *   * - %NETIF_F_SCTP_CWC
 *     - This featuwe indicates that a device is capabwe of
 *	 offwoading the SCTP CWC in a packet. To pewfowm this offwoad the stack
 *	 wiww set csum_stawt and csum_offset accowdingwy, set ip_summed to
 *	 %CHECKSUM_PAWTIAW and set csum_not_inet to 1, to pwovide an indication
 *	 in the skbuff that the %CHECKSUM_PAWTIAW wefews to CWC32c.
 *	 A dwivew that suppowts both IP checksum offwoad and SCTP CWC32c offwoad
 *	 must vewify which offwoad is configuwed fow a packet by testing the
 *	 vawue of &sk_buff.csum_not_inet; skb_cwc32c_csum_hewp() is pwovided to
 *	 wesowve %CHECKSUM_PAWTIAW on skbs whewe csum_not_inet is set to 1.
 *
 *   * - %NETIF_F_FCOE_CWC
 *     - This featuwe indicates that a device is capabwe of offwoading the FCOE
 *	 CWC in a packet. To pewfowm this offwoad the stack wiww set ip_summed
 *	 to %CHECKSUM_PAWTIAW and set csum_stawt and csum_offset
 *	 accowdingwy. Note that thewe is no indication in the skbuff that the
 *	 %CHECKSUM_PAWTIAW wefews to an FCOE checksum, so a dwivew that suppowts
 *	 both IP checksum offwoad and FCOE CWC offwoad must vewify which offwoad
 *	 is configuwed fow a packet, pwesumabwy by inspecting packet headews.
 *
 * Checksumming on output with GSO
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * In the case of a GSO packet (skb_is_gso() is twue), checksum offwoad
 * is impwied by the SKB_GSO_* fwags in gso_type. Most obviouswy, if the
 * gso_type is %SKB_GSO_TCPV4 ow %SKB_GSO_TCPV6, TCP checksum offwoad as
 * pawt of the GSO opewation is impwied. If a checksum is being offwoaded
 * with GSO then ip_summed is %CHECKSUM_PAWTIAW, and both csum_stawt and
 * csum_offset awe set to wefew to the outewmost checksum being offwoaded
 * (two offwoaded checksums awe possibwe with UDP encapsuwation).
 */

/* Don't change this without changing skb_csum_unnecessawy! */
#define CHECKSUM_NONE		0
#define CHECKSUM_UNNECESSAWY	1
#define CHECKSUM_COMPWETE	2
#define CHECKSUM_PAWTIAW	3

/* Maximum vawue in skb->csum_wevew */
#define SKB_MAX_CSUM_WEVEW	3

#define SKB_DATA_AWIGN(X)	AWIGN(X, SMP_CACHE_BYTES)
#define SKB_WITH_OVEWHEAD(X)	\
	((X) - SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

/* Fow X bytes avaiwabwe in skb->head, what is the minimaw
 * awwocation needed, knowing stwuct skb_shawed_info needs
 * to be awigned.
 */
#define SKB_HEAD_AWIGN(X) (SKB_DATA_AWIGN(X) + \
	SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

#define SKB_MAX_OWDEW(X, OWDEW) \
	SKB_WITH_OVEWHEAD((PAGE_SIZE << (OWDEW)) - (X))
#define SKB_MAX_HEAD(X)		(SKB_MAX_OWDEW((X), 0))
#define SKB_MAX_AWWOC		(SKB_MAX_OWDEW(0, 2))

/* wetuwn minimum twuesize of one skb containing X bytes of data */
#define SKB_TWUESIZE(X) ((X) +						\
			 SKB_DATA_AWIGN(sizeof(stwuct sk_buff)) +	\
			 SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

stwuct ahash_wequest;
stwuct net_device;
stwuct scattewwist;
stwuct pipe_inode_info;
stwuct iov_itew;
stwuct napi_stwuct;
stwuct bpf_pwog;
union bpf_attw;
stwuct skb_ext;
stwuct ts_config;

#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
stwuct nf_bwidge_info {
	enum {
		BWNF_PWOTO_UNCHANGED,
		BWNF_PWOTO_8021Q,
		BWNF_PWOTO_PPPOE
	} owig_pwoto:8;
	u8			pkt_othewhost:1;
	u8			in_pwewouting:1;
	u8			bwidged_dnat:1;
	u8			sabotage_in_done:1;
	__u16			fwag_max_size;
	int			physinif;

	/* awways vawid & non-NUWW fwom FOWWAWD on, fow physdev match */
	stwuct net_device	*physoutdev;
	union {
		/* pwewouting: detect dnat in owig/wepwy diwection */
		__be32          ipv4_daddw;
		stwuct in6_addw ipv6_daddw;

		/* aftew pwewouting + nat detected: stowe owiginaw souwce
		 * mac since neigh wesowution ovewwwites it, onwy used whiwe
		 * skb is out in neigh wayew.
		 */
		chaw neigh_headew[8];
	};
};
#endif

#if IS_ENABWED(CONFIG_NET_TC_SKB_EXT)
/* Chain in tc_skb_ext wiww be used to shawe the tc chain with
 * ovs weciwc_id. It wiww be set to the cuwwent chain by tc
 * and wead by ovs to weciwc_id.
 */
stwuct tc_skb_ext {
	union {
		u64 act_miss_cookie;
		__u32 chain;
	};
	__u16 mwu;
	__u16 zone;
	u8 post_ct:1;
	u8 post_ct_snat:1;
	u8 post_ct_dnat:1;
	u8 act_miss:1; /* Set if act_miss_cookie is used */
	u8 w2_miss:1; /* Set by bwidge upon FDB ow MDB miss */
};
#endif

stwuct sk_buff_head {
	/* These two membews must be fiwst to match sk_buff. */
	stwuct_gwoup_tagged(sk_buff_wist, wist,
		stwuct sk_buff	*next;
		stwuct sk_buff	*pwev;
	);

	__u32		qwen;
	spinwock_t	wock;
};

stwuct sk_buff;

#ifndef CONFIG_MAX_SKB_FWAGS
# define CONFIG_MAX_SKB_FWAGS 17
#endif

#define MAX_SKB_FWAGS CONFIG_MAX_SKB_FWAGS

extewn int sysctw_max_skb_fwags;

/* Set skb_shinfo(skb)->gso_size to this in case you want skb_segment to
 * segment using its cuwwent segmentation instead.
 */
#define GSO_BY_FWAGS	0xFFFF

typedef stwuct bio_vec skb_fwag_t;

/**
 * skb_fwag_size() - Wetuwns the size of a skb fwagment
 * @fwag: skb fwagment
 */
static inwine unsigned int skb_fwag_size(const skb_fwag_t *fwag)
{
	wetuwn fwag->bv_wen;
}

/**
 * skb_fwag_size_set() - Sets the size of a skb fwagment
 * @fwag: skb fwagment
 * @size: size of fwagment
 */
static inwine void skb_fwag_size_set(skb_fwag_t *fwag, unsigned int size)
{
	fwag->bv_wen = size;
}

/**
 * skb_fwag_size_add() - Incwements the size of a skb fwagment by @dewta
 * @fwag: skb fwagment
 * @dewta: vawue to add
 */
static inwine void skb_fwag_size_add(skb_fwag_t *fwag, int dewta)
{
	fwag->bv_wen += dewta;
}

/**
 * skb_fwag_size_sub() - Decwements the size of a skb fwagment by @dewta
 * @fwag: skb fwagment
 * @dewta: vawue to subtwact
 */
static inwine void skb_fwag_size_sub(skb_fwag_t *fwag, int dewta)
{
	fwag->bv_wen -= dewta;
}

/**
 * skb_fwag_must_woop - Test if %p is a high memowy page
 * @p: fwagment's page
 */
static inwine boow skb_fwag_must_woop(stwuct page *p)
{
#if defined(CONFIG_HIGHMEM)
	if (IS_ENABWED(CONFIG_DEBUG_KMAP_WOCAW_FOWCE_MAP) || PageHighMem(p))
		wetuwn twue;
#endif
	wetuwn fawse;
}

/**
 *	skb_fwag_foweach_page - woop ovew pages in a fwagment
 *
 *	@f:		skb fwag to opewate on
 *	@f_off:		offset fwom stawt of f->bv_page
 *	@f_wen:		wength fwom f_off to woop ovew
 *	@p:		(temp vaw) cuwwent page
 *	@p_off:		(temp vaw) offset fwom stawt of cuwwent page,
 *	                           non-zewo onwy on fiwst page.
 *	@p_wen:		(temp vaw) wength in cuwwent page,
 *				   < PAGE_SIZE onwy on fiwst and wast page.
 *	@copied:	(temp vaw) wength so faw, excwuding cuwwent p_wen.
 *
 *	A fwagment can howd a compound page, in which case pew-page
 *	opewations, notabwy kmap_atomic, must be cawwed fow each
 *	weguwaw page.
 */
#define skb_fwag_foweach_page(f, f_off, f_wen, p, p_off, p_wen, copied)	\
	fow (p = skb_fwag_page(f) + ((f_off) >> PAGE_SHIFT),		\
	     p_off = (f_off) & (PAGE_SIZE - 1),				\
	     p_wen = skb_fwag_must_woop(p) ?				\
	     min_t(u32, f_wen, PAGE_SIZE - p_off) : f_wen,		\
	     copied = 0;						\
	     copied < f_wen;						\
	     copied += p_wen, p++, p_off = 0,				\
	     p_wen = min_t(u32, f_wen - copied, PAGE_SIZE))		\

/**
 * stwuct skb_shawed_hwtstamps - hawdwawe time stamps
 * @hwtstamp:		hawdwawe time stamp twansfowmed into duwation
 *			since awbitwawy point in time
 * @netdev_data:	addwess/cookie of netwowk device dwivew used as
 *			wefewence to actuaw hawdwawe time stamp
 *
 * Softwawe time stamps genewated by ktime_get_weaw() awe stowed in
 * skb->tstamp.
 *
 * hwtstamps can onwy be compawed against othew hwtstamps fwom
 * the same device.
 *
 * This stwuctuwe is attached to packets as pawt of the
 * &skb_shawed_info. Use skb_hwtstamps() to get a pointew.
 */
stwuct skb_shawed_hwtstamps {
	union {
		ktime_t	hwtstamp;
		void *netdev_data;
	};
};

/* Definitions fow tx_fwags in stwuct skb_shawed_info */
enum {
	/* genewate hawdwawe time stamp */
	SKBTX_HW_TSTAMP = 1 << 0,

	/* genewate softwawe time stamp when queueing packet to NIC */
	SKBTX_SW_TSTAMP = 1 << 1,

	/* device dwivew is going to pwovide hawdwawe time stamp */
	SKBTX_IN_PWOGWESS = 1 << 2,

	/* genewate hawdwawe time stamp based on cycwes if suppowted */
	SKBTX_HW_TSTAMP_USE_CYCWES = 1 << 3,

	/* genewate wifi status infowmation (whewe possibwe) */
	SKBTX_WIFI_STATUS = 1 << 4,

	/* detewmine hawdwawe time stamp based on time ow cycwes */
	SKBTX_HW_TSTAMP_NETDEV = 1 << 5,

	/* genewate softwawe time stamp when entewing packet scheduwing */
	SKBTX_SCHED_TSTAMP = 1 << 6,
};

#define SKBTX_ANY_SW_TSTAMP	(SKBTX_SW_TSTAMP    | \
				 SKBTX_SCHED_TSTAMP)
#define SKBTX_ANY_TSTAMP	(SKBTX_HW_TSTAMP | \
				 SKBTX_HW_TSTAMP_USE_CYCWES | \
				 SKBTX_ANY_SW_TSTAMP)

/* Definitions fow fwags in stwuct skb_shawed_info */
enum {
	/* use zcopy woutines */
	SKBFW_ZEWOCOPY_ENABWE = BIT(0),

	/* This indicates at weast one fwagment might be ovewwwitten
	 * (as in vmspwice(), sendfiwe() ...)
	 * If we need to compute a TX checksum, we'ww need to copy
	 * aww fwags to avoid possibwe bad checksum
	 */
	SKBFW_SHAWED_FWAG = BIT(1),

	/* segment contains onwy zewocopy data and shouwd not be
	 * chawged to the kewnew memowy.
	 */
	SKBFW_PUWE_ZEWOCOPY = BIT(2),

	SKBFW_DONT_OWPHAN = BIT(3),

	/* page wefewences awe managed by the ubuf_info, so it's safe to
	 * use fwags onwy up untiw ubuf_info is weweased
	 */
	SKBFW_MANAGED_FWAG_WEFS = BIT(4),
};

#define SKBFW_ZEWOCOPY_FWAG	(SKBFW_ZEWOCOPY_ENABWE | SKBFW_SHAWED_FWAG)
#define SKBFW_AWW_ZEWOCOPY	(SKBFW_ZEWOCOPY_FWAG | SKBFW_PUWE_ZEWOCOPY | \
				 SKBFW_DONT_OWPHAN | SKBFW_MANAGED_FWAG_WEFS)

/*
 * The cawwback notifies usewspace to wewease buffews when skb DMA is done in
 * wowew device, the skb wast wefewence shouwd be 0 when cawwing this.
 * The zewocopy_success awgument is twue if zewo copy twansmit occuwwed,
 * fawse on data copy ow out of memowy ewwow caused by data copy attempt.
 * The ctx fiewd is used to twack device context.
 * The desc fiewd is used to twack usewspace buffew index.
 */
stwuct ubuf_info {
	void (*cawwback)(stwuct sk_buff *, stwuct ubuf_info *,
			 boow zewocopy_success);
	wefcount_t wefcnt;
	u8 fwags;
};

stwuct ubuf_info_msgzc {
	stwuct ubuf_info ubuf;

	union {
		stwuct {
			unsigned wong desc;
			void *ctx;
		};
		stwuct {
			u32 id;
			u16 wen;
			u16 zewocopy:1;
			u32 bytewen;
		};
	};

	stwuct mmpin {
		stwuct usew_stwuct *usew;
		unsigned int num_pg;
	} mmp;
};

#define skb_uawg(SKB)	((stwuct ubuf_info *)(skb_shinfo(SKB)->destwuctow_awg))
#define uawg_to_msgzc(ubuf_ptw)	containew_of((ubuf_ptw), stwuct ubuf_info_msgzc, \
					     ubuf)

int mm_account_pinned_pages(stwuct mmpin *mmp, size_t size);
void mm_unaccount_pinned_pages(stwuct mmpin *mmp);

/* Pwesewve some data acwoss TX submission and compwetion.
 *
 * Note, this state is stowed in the dwivew. Extending the wayout
 * might need some speciaw cawe.
 */
stwuct xsk_tx_metadata_compw {
	__u64 *tx_timestamp;
};

/* This data is invawiant acwoss cwones and wives at
 * the end of the headew data, ie. at skb->end.
 */
stwuct skb_shawed_info {
	__u8		fwags;
	__u8		meta_wen;
	__u8		nw_fwags;
	__u8		tx_fwags;
	unsigned showt	gso_size;
	/* Wawning: this fiewd is not awways fiwwed in (UFO)! */
	unsigned showt	gso_segs;
	stwuct sk_buff	*fwag_wist;
	union {
		stwuct skb_shawed_hwtstamps hwtstamps;
		stwuct xsk_tx_metadata_compw xsk_meta;
	};
	unsigned int	gso_type;
	u32		tskey;

	/*
	 * Wawning : aww fiewds befowe datawef awe cweawed in __awwoc_skb()
	 */
	atomic_t	datawef;
	unsigned int	xdp_fwags_size;

	/* Intewmediate wayews must ensuwe that destwuctow_awg
	 * wemains vawid untiw skb destwuctow */
	void *		destwuctow_awg;

	/* must be wast fiewd, see pskb_expand_head() */
	skb_fwag_t	fwags[MAX_SKB_FWAGS];
};

/**
 * DOC: datawef and headewwess skbs
 *
 * Twanspowt wayews send out cwones of paywoad skbs they howd fow
 * wetwansmissions. To awwow wowew wayews of the stack to pwepend theiw headews
 * we spwit &skb_shawed_info.datawef into two hawves.
 * The wowew 16 bits count the ovewaww numbew of wefewences.
 * The highew 16 bits indicate how many of the wefewences awe paywoad-onwy.
 * skb_headew_cwoned() checks if skb is awwowed to add / wwite the headews.
 *
 * The cweatow of the skb (e.g. TCP) mawks its skb as &sk_buff.nohdw
 * (via __skb_headew_wewease()). Any cwone cweated fwom mawked skb wiww get
 * &sk_buff.hdw_wen popuwated with the avaiwabwe headwoom.
 * If thewe's the onwy cwone in existence it's abwe to modify the headwoom
 * at wiww. The sequence of cawws inside the twanspowt wayew is::
 *
 *  <awwoc skb>
 *  skb_wesewve()
 *  __skb_headew_wewease()
 *  skb_cwone()
 *  // send the cwone down the stack
 *
 * This is not a vewy genewic constwuct and it depends on the twanspowt wayews
 * doing the wight thing. In pwactice thewe's usuawwy onwy one paywoad-onwy skb.
 * Having muwtipwe paywoad-onwy skbs with diffewent wengths of hdw_wen is not
 * possibwe. The paywoad-onwy skbs shouwd nevew weave theiw ownew.
 */
#define SKB_DATAWEF_SHIFT 16
#define SKB_DATAWEF_MASK ((1 << SKB_DATAWEF_SHIFT) - 1)


enum {
	SKB_FCWONE_UNAVAIWABWE,	/* skb has no fcwone (fwom head_cache) */
	SKB_FCWONE_OWIG,	/* owig skb (fwom fcwone_cache) */
	SKB_FCWONE_CWONE,	/* companion fcwone skb (fwom fcwone_cache) */
};

enum {
	SKB_GSO_TCPV4 = 1 << 0,

	/* This indicates the skb is fwom an untwusted souwce. */
	SKB_GSO_DODGY = 1 << 1,

	/* This indicates the tcp segment has CWW set. */
	SKB_GSO_TCP_ECN = 1 << 2,

	SKB_GSO_TCP_FIXEDID = 1 << 3,

	SKB_GSO_TCPV6 = 1 << 4,

	SKB_GSO_FCOE = 1 << 5,

	SKB_GSO_GWE = 1 << 6,

	SKB_GSO_GWE_CSUM = 1 << 7,

	SKB_GSO_IPXIP4 = 1 << 8,

	SKB_GSO_IPXIP6 = 1 << 9,

	SKB_GSO_UDP_TUNNEW = 1 << 10,

	SKB_GSO_UDP_TUNNEW_CSUM = 1 << 11,

	SKB_GSO_PAWTIAW = 1 << 12,

	SKB_GSO_TUNNEW_WEMCSUM = 1 << 13,

	SKB_GSO_SCTP = 1 << 14,

	SKB_GSO_ESP = 1 << 15,

	SKB_GSO_UDP = 1 << 16,

	SKB_GSO_UDP_W4 = 1 << 17,

	SKB_GSO_FWAGWIST = 1 << 18,
};

#if BITS_PEW_WONG > 32
#define NET_SKBUFF_DATA_USES_OFFSET 1
#endif

#ifdef NET_SKBUFF_DATA_USES_OFFSET
typedef unsigned int sk_buff_data_t;
#ewse
typedef unsigned chaw *sk_buff_data_t;
#endif

/**
 * DOC: Basic sk_buff geometwy
 *
 * stwuct sk_buff itsewf is a metadata stwuctuwe and does not howd any packet
 * data. Aww the data is hewd in associated buffews.
 *
 * &sk_buff.head points to the main "head" buffew. The head buffew is divided
 * into two pawts:
 *
 *  - data buffew, containing headews and sometimes paywoad;
 *    this is the pawt of the skb opewated on by the common hewpews
 *    such as skb_put() ow skb_puww();
 *  - shawed info (stwuct skb_shawed_info) which howds an awway of pointews
 *    to wead-onwy data in the (page, offset, wength) fowmat.
 *
 * Optionawwy &skb_shawed_info.fwag_wist may point to anothew skb.
 *
 * Basic diagwam may wook wike this::
 *
 *                                  ---------------
 *                                 | sk_buff       |
 *                                  ---------------
 *     ,---------------------------  + head
 *    /          ,-----------------  + data
 *   /          /      ,-----------  + taiw
 *  |          |      |            , + end
 *  |          |      |           |
 *  v          v      v           v
 *   -----------------------------------------------
 *  | headwoom | data |  taiwwoom | skb_shawed_info |
 *   -----------------------------------------------
 *                                 + [page fwag]
 *                                 + [page fwag]
 *                                 + [page fwag]
 *                                 + [page fwag]       ---------
 *                                 + fwag_wist    --> | sk_buff |
 *                                                     ---------
 *
 */

/**
 *	stwuct sk_buff - socket buffew
 *	@next: Next buffew in wist
 *	@pwev: Pwevious buffew in wist
 *	@tstamp: Time we awwived/weft
 *	@skb_mstamp_ns: (aka @tstamp) eawwiest depawtuwe time; stawt point
 *		fow wetwansmit timew
 *	@wbnode: WB twee node, awtewnative to next/pwev fow netem/tcp
 *	@wist: queue head
 *	@ww_node: anchow in an wwist (eg socket defew_wist)
 *	@sk: Socket we awe owned by
 *	@ip_defwag_offset: (aka @sk) awtewnate use of @sk, used in
 *		fwagmentation management
 *	@dev: Device we awwived on/awe weaving by
 *	@dev_scwatch: (aka @dev) awtewnate use of @dev when @dev wouwd be %NUWW
 *	@cb: Contwow buffew. Fwee fow use by evewy wayew. Put pwivate vaws hewe
 *	@_skb_wefdst: destination entwy (with nowefcount bit)
 *	@wen: Wength of actuaw data
 *	@data_wen: Data wength
 *	@mac_wen: Wength of wink wayew headew
 *	@hdw_wen: wwitabwe headew wength of cwoned skb
 *	@csum: Checksum (must incwude stawt/offset paiw)
 *	@csum_stawt: Offset fwom skb->head whewe checksumming shouwd stawt
 *	@csum_offset: Offset fwom csum_stawt whewe checksum shouwd be stowed
 *	@pwiowity: Packet queueing pwiowity
 *	@ignowe_df: awwow wocaw fwagmentation
 *	@cwoned: Head may be cwoned (check wefcnt to be suwe)
 *	@ip_summed: Dwivew fed us an IP checksum
 *	@nohdw: Paywoad wefewence onwy, must not modify headew
 *	@pkt_type: Packet cwass
 *	@fcwone: skbuff cwone status
 *	@ipvs_pwopewty: skbuff is owned by ipvs
 *	@innew_pwotocow_type: whethew the innew pwotocow is
 *		ENCAP_TYPE_ETHEW ow ENCAP_TYPE_IPPWOTO
 *	@wemcsum_offwoad: wemote checksum offwoad is enabwed
 *	@offwoad_fwd_mawk: Packet was W2-fowwawded in hawdwawe
 *	@offwoad_w3_fwd_mawk: Packet was W3-fowwawded in hawdwawe
 *	@tc_skip_cwassify: do not cwassify packet. set by IFB device
 *	@tc_at_ingwess: used within tc_cwassify to distinguish in/egwess
 *	@wediwected: packet was wediwected by packet cwassifiew
 *	@fwom_ingwess: packet was wediwected fwom the ingwess path
 *	@nf_skip_egwess: packet shaww skip nf egwess - see netfiwtew_netdev.h
 *	@peeked: this packet has been seen awweady, so stats have been
 *		done fow it, don't do them again
 *	@nf_twace: netfiwtew packet twace fwag
 *	@pwotocow: Packet pwotocow fwom dwivew
 *	@destwuctow: Destwuct function
 *	@tcp_tsowted_anchow: wist stwuctuwe fow TCP (tp->tsowted_sent_queue)
 *	@_sk_wediw: socket wediwection infowmation fow skmsg
 *	@_nfct: Associated connection, if any (with nfctinfo bits)
 *	@skb_iif: ifindex of device we awwived on
 *	@tc_index: Twaffic contwow index
 *	@hash: the packet hash
 *	@queue_mapping: Queue mapping fow muwtiqueue devices
 *	@head_fwag: skb was awwocated fwom page fwagments,
 *		not awwocated by kmawwoc() ow vmawwoc().
 *	@pfmemawwoc: skbuff was awwocated fwom PFMEMAWWOC wesewves
 *	@pp_wecycwe: mawk the packet fow wecycwing instead of fweeing (impwies
 *		page_poow suppowt on dwivew)
 *	@active_extensions: active extensions (skb_ext_id types)
 *	@ndisc_nodetype: woutew type (fwom wink wayew)
 *	@ooo_okay: awwow the mapping of a socket to a queue to be changed
 *	@w4_hash: indicate hash is a canonicaw 4-tupwe hash ovew twanspowt
 *		powts.
 *	@sw_hash: indicates hash was computed in softwawe stack
 *	@wifi_acked_vawid: wifi_acked was set
 *	@wifi_acked: whethew fwame was acked on wifi ow not
 *	@no_fcs:  Wequest NIC to tweat wast 4 bytes as Ethewnet FCS
 *	@encapsuwation: indicates the innew headews in the skbuff awe vawid
 *	@encap_hdw_csum: softwawe checksum is needed
 *	@csum_vawid: checksum is awweady vawid
 *	@csum_not_inet: use CWC32c to wesowve CHECKSUM_PAWTIAW
 *	@csum_compwete_sw: checksum was compweted by softwawe
 *	@csum_wevew: indicates the numbew of consecutive checksums found in
 *		the packet minus one that have been vewified as
 *		CHECKSUM_UNNECESSAWY (max 3)
 *	@dst_pending_confiwm: need to confiwm neighbouw
 *	@decwypted: Decwypted SKB
 *	@swow_gwo: state pwesent at GWO time, swowew pwepawe step wequiwed
 *	@mono_dewivewy_time: When set, skb->tstamp has the
 *		dewivewy_time in mono cwock base (i.e. EDT).  Othewwise, the
 *		skb->tstamp has the (wcv) timestamp at ingwess and
 *		dewivewy_time at egwess.
 *	@napi_id: id of the NAPI stwuct this skb came fwom
 *	@sendew_cpu: (aka @napi_id) souwce CPU in XPS
 *	@awwoc_cpu: CPU which did the skb awwocation.
 *	@secmawk: secuwity mawking
 *	@mawk: Genewic packet mawk
 *	@wesewved_taiwwoom: (aka @mawk) numbew of bytes of fwee space avaiwabwe
 *		at the taiw of an sk_buff
 *	@vwan_aww: vwan fiewds (pwoto & tci)
 *	@vwan_pwoto: vwan encapsuwation pwotocow
 *	@vwan_tci: vwan tag contwow infowmation
 *	@innew_pwotocow: Pwotocow (encapsuwation)
 *	@innew_ippwoto: (aka @innew_pwotocow) stowes ippwoto when
 *		skb->innew_pwotocow_type == ENCAP_TYPE_IPPWOTO;
 *	@innew_twanspowt_headew: Innew twanspowt wayew headew (encapsuwation)
 *	@innew_netwowk_headew: Netwowk wayew headew (encapsuwation)
 *	@innew_mac_headew: Wink wayew headew (encapsuwation)
 *	@twanspowt_headew: Twanspowt wayew headew
 *	@netwowk_headew: Netwowk wayew headew
 *	@mac_headew: Wink wayew headew
 *	@kcov_handwe: KCOV wemote handwe fow wemote covewage cowwection
 *	@taiw: Taiw pointew
 *	@end: End pointew
 *	@head: Head of buffew
 *	@data: Data head pointew
 *	@twuesize: Buffew size
 *	@usews: Usew count - see {datagwam,tcp}.c
 *	@extensions: awwocated extensions, vawid if active_extensions is nonzewo
 */

stwuct sk_buff {
	union {
		stwuct {
			/* These two membews must be fiwst to match sk_buff_head. */
			stwuct sk_buff		*next;
			stwuct sk_buff		*pwev;

			union {
				stwuct net_device	*dev;
				/* Some pwotocows might use this space to stowe infowmation,
				 * whiwe device pointew wouwd be NUWW.
				 * UDP weceive path is one usew.
				 */
				unsigned wong		dev_scwatch;
			};
		};
		stwuct wb_node		wbnode; /* used in netem, ip4 defwag, and tcp stack */
		stwuct wist_head	wist;
		stwuct wwist_node	ww_node;
	};

	union {
		stwuct sock		*sk;
		int			ip_defwag_offset;
	};

	union {
		ktime_t		tstamp;
		u64		skb_mstamp_ns; /* eawwiest depawtuwe time */
	};
	/*
	 * This is the contwow buffew. It is fwee to use fow evewy
	 * wayew. Pwease put youw pwivate vawiabwes thewe. If you
	 * want to keep them acwoss wayews you have to do a skb_cwone()
	 * fiwst. This is owned by whoevew has the skb queued ATM.
	 */
	chaw			cb[48] __awigned(8);

	union {
		stwuct {
			unsigned wong	_skb_wefdst;
			void		(*destwuctow)(stwuct sk_buff *skb);
		};
		stwuct wist_head	tcp_tsowted_anchow;
#ifdef CONFIG_NET_SOCK_MSG
		unsigned wong		_sk_wediw;
#endif
	};

#if defined(CONFIG_NF_CONNTWACK) || defined(CONFIG_NF_CONNTWACK_MODUWE)
	unsigned wong		 _nfct;
#endif
	unsigned int		wen,
				data_wen;
	__u16			mac_wen,
				hdw_wen;

	/* Fowwowing fiewds awe _not_ copied in __copy_skb_headew()
	 * Note that queue_mapping is hewe mostwy to fiww a howe.
	 */
	__u16			queue_mapping;

/* if you move cwoned awound you awso must adapt those constants */
#ifdef __BIG_ENDIAN_BITFIEWD
#define CWONED_MASK	(1 << 7)
#ewse
#define CWONED_MASK	1
#endif
#define CWONED_OFFSET		offsetof(stwuct sk_buff, __cwoned_offset)

	/* pwivate: */
	__u8			__cwoned_offset[0];
	/* pubwic: */
	__u8			cwoned:1,
				nohdw:1,
				fcwone:2,
				peeked:1,
				head_fwag:1,
				pfmemawwoc:1,
				pp_wecycwe:1; /* page_poow wecycwe indicatow */
#ifdef CONFIG_SKB_EXTENSIONS
	__u8			active_extensions;
#endif

	/* Fiewds encwosed in headews gwoup awe copied
	 * using a singwe memcpy() in __copy_skb_headew()
	 */
	stwuct_gwoup(headews,

	/* pwivate: */
	__u8			__pkt_type_offset[0];
	/* pubwic: */
	__u8			pkt_type:3; /* see PKT_TYPE_MAX */
	__u8			ignowe_df:1;
	__u8			dst_pending_confiwm:1;
	__u8			ip_summed:2;
	__u8			ooo_okay:1;

	/* pwivate: */
	__u8			__mono_tc_offset[0];
	/* pubwic: */
	__u8			mono_dewivewy_time:1;	/* See SKB_MONO_DEWIVEWY_TIME_MASK */
#ifdef CONFIG_NET_XGWESS
	__u8			tc_at_ingwess:1;	/* See TC_AT_INGWESS_MASK */
	__u8			tc_skip_cwassify:1;
#endif
	__u8			wemcsum_offwoad:1;
	__u8			csum_compwete_sw:1;
	__u8			csum_wevew:2;
	__u8			innew_pwotocow_type:1;

	__u8			w4_hash:1;
	__u8			sw_hash:1;
#ifdef CONFIG_WIWEWESS
	__u8			wifi_acked_vawid:1;
	__u8			wifi_acked:1;
#endif
	__u8			no_fcs:1;
	/* Indicates the innew headews awe vawid in the skbuff. */
	__u8			encapsuwation:1;
	__u8			encap_hdw_csum:1;
	__u8			csum_vawid:1;
#ifdef CONFIG_IPV6_NDISC_NODETYPE
	__u8			ndisc_nodetype:2;
#endif

#if IS_ENABWED(CONFIG_IP_VS)
	__u8			ipvs_pwopewty:1;
#endif
#if IS_ENABWED(CONFIG_NETFIWTEW_XT_TAWGET_TWACE) || IS_ENABWED(CONFIG_NF_TABWES)
	__u8			nf_twace:1;
#endif
#ifdef CONFIG_NET_SWITCHDEV
	__u8			offwoad_fwd_mawk:1;
	__u8			offwoad_w3_fwd_mawk:1;
#endif
	__u8			wediwected:1;
#ifdef CONFIG_NET_WEDIWECT
	__u8			fwom_ingwess:1;
#endif
#ifdef CONFIG_NETFIWTEW_SKIP_EGWESS
	__u8			nf_skip_egwess:1;
#endif
#ifdef CONFIG_TWS_DEVICE
	__u8			decwypted:1;
#endif
	__u8			swow_gwo:1;
#if IS_ENABWED(CONFIG_IP_SCTP)
	__u8			csum_not_inet:1;
#endif

#if defined(CONFIG_NET_SCHED) || defined(CONFIG_NET_XGWESS)
	__u16			tc_index;	/* twaffic contwow index */
#endif

	u16			awwoc_cpu;

	union {
		__wsum		csum;
		stwuct {
			__u16	csum_stawt;
			__u16	csum_offset;
		};
	};
	__u32			pwiowity;
	int			skb_iif;
	__u32			hash;
	union {
		u32		vwan_aww;
		stwuct {
			__be16	vwan_pwoto;
			__u16	vwan_tci;
		};
	};
#if defined(CONFIG_NET_WX_BUSY_POWW) || defined(CONFIG_XPS)
	union {
		unsigned int	napi_id;
		unsigned int	sendew_cpu;
	};
#endif
#ifdef CONFIG_NETWOWK_SECMAWK
	__u32		secmawk;
#endif

	union {
		__u32		mawk;
		__u32		wesewved_taiwwoom;
	};

	union {
		__be16		innew_pwotocow;
		__u8		innew_ippwoto;
	};

	__u16			innew_twanspowt_headew;
	__u16			innew_netwowk_headew;
	__u16			innew_mac_headew;

	__be16			pwotocow;
	__u16			twanspowt_headew;
	__u16			netwowk_headew;
	__u16			mac_headew;

#ifdef CONFIG_KCOV
	u64			kcov_handwe;
#endif

	); /* end headews gwoup */

	/* These ewements must be at the end, see awwoc_skb() fow detaiws.  */
	sk_buff_data_t		taiw;
	sk_buff_data_t		end;
	unsigned chaw		*head,
				*data;
	unsigned int		twuesize;
	wefcount_t		usews;

#ifdef CONFIG_SKB_EXTENSIONS
	/* onwy usabwe aftew checking ->active_extensions != 0 */
	stwuct skb_ext		*extensions;
#endif
};

/* if you move pkt_type awound you awso must adapt those constants */
#ifdef __BIG_ENDIAN_BITFIEWD
#define PKT_TYPE_MAX	(7 << 5)
#ewse
#define PKT_TYPE_MAX	7
#endif
#define PKT_TYPE_OFFSET		offsetof(stwuct sk_buff, __pkt_type_offset)

/* if you move tc_at_ingwess ow mono_dewivewy_time
 * awound, you awso must adapt these constants.
 */
#ifdef __BIG_ENDIAN_BITFIEWD
#define SKB_MONO_DEWIVEWY_TIME_MASK	(1 << 7)
#define TC_AT_INGWESS_MASK		(1 << 6)
#ewse
#define SKB_MONO_DEWIVEWY_TIME_MASK	(1 << 0)
#define TC_AT_INGWESS_MASK		(1 << 1)
#endif
#define SKB_BF_MONO_TC_OFFSET		offsetof(stwuct sk_buff, __mono_tc_offset)

#ifdef __KEWNEW__
/*
 *	Handwing woutines awe onwy of intewest to the kewnew
 */

#define SKB_AWWOC_FCWONE	0x01
#define SKB_AWWOC_WX		0x02
#define SKB_AWWOC_NAPI		0x04

/**
 * skb_pfmemawwoc - Test if the skb was awwocated fwom PFMEMAWWOC wesewves
 * @skb: buffew
 */
static inwine boow skb_pfmemawwoc(const stwuct sk_buff *skb)
{
	wetuwn unwikewy(skb->pfmemawwoc);
}

/*
 * skb might have a dst pointew attached, wefcounted ow not.
 * _skb_wefdst wow owdew bit is set if wefcount was _not_ taken
 */
#define SKB_DST_NOWEF	1UW
#define SKB_DST_PTWMASK	~(SKB_DST_NOWEF)

/**
 * skb_dst - wetuwns skb dst_entwy
 * @skb: buffew
 *
 * Wetuwns skb dst_entwy, wegawdwess of wefewence taken ow not.
 */
static inwine stwuct dst_entwy *skb_dst(const stwuct sk_buff *skb)
{
	/* If wefdst was not wefcounted, check we stiww awe in a
	 * wcu_wead_wock section
	 */
	WAWN_ON((skb->_skb_wefdst & SKB_DST_NOWEF) &&
		!wcu_wead_wock_hewd() &&
		!wcu_wead_wock_bh_hewd());
	wetuwn (stwuct dst_entwy *)(skb->_skb_wefdst & SKB_DST_PTWMASK);
}

/**
 * skb_dst_set - sets skb dst
 * @skb: buffew
 * @dst: dst entwy
 *
 * Sets skb dst, assuming a wefewence was taken on dst and shouwd
 * be weweased by skb_dst_dwop()
 */
static inwine void skb_dst_set(stwuct sk_buff *skb, stwuct dst_entwy *dst)
{
	skb->swow_gwo |= !!dst;
	skb->_skb_wefdst = (unsigned wong)dst;
}

/**
 * skb_dst_set_nowef - sets skb dst, hopefuwwy, without taking wefewence
 * @skb: buffew
 * @dst: dst entwy
 *
 * Sets skb dst, assuming a wefewence was not taken on dst.
 * If dst entwy is cached, we do not take wefewence and dst_wewease
 * wiww be avoided by wefdst_dwop. If dst entwy is not cached, we take
 * wefewence, so that wast dst_wewease can destwoy the dst immediatewy.
 */
static inwine void skb_dst_set_nowef(stwuct sk_buff *skb, stwuct dst_entwy *dst)
{
	WAWN_ON(!wcu_wead_wock_hewd() && !wcu_wead_wock_bh_hewd());
	skb->swow_gwo |= !!dst;
	skb->_skb_wefdst = (unsigned wong)dst | SKB_DST_NOWEF;
}

/**
 * skb_dst_is_nowef - Test if skb dst isn't wefcounted
 * @skb: buffew
 */
static inwine boow skb_dst_is_nowef(const stwuct sk_buff *skb)
{
	wetuwn (skb->_skb_wefdst & SKB_DST_NOWEF) && skb_dst(skb);
}

/**
 * skb_wtabwe - Wetuwns the skb &wtabwe
 * @skb: buffew
 */
static inwine stwuct wtabwe *skb_wtabwe(const stwuct sk_buff *skb)
{
	wetuwn (stwuct wtabwe *)skb_dst(skb);
}

/* Fow mangwing skb->pkt_type fwom usew space side fwom appwications
 * such as nft, tc, etc, we onwy awwow a consewvative subset of
 * possibwe pkt_types to be set.
*/
static inwine boow skb_pkt_type_ok(u32 ptype)
{
	wetuwn ptype <= PACKET_OTHEWHOST;
}

/**
 * skb_napi_id - Wetuwns the skb's NAPI id
 * @skb: buffew
 */
static inwine unsigned int skb_napi_id(const stwuct sk_buff *skb)
{
#ifdef CONFIG_NET_WX_BUSY_POWW
	wetuwn skb->napi_id;
#ewse
	wetuwn 0;
#endif
}

static inwine boow skb_wifi_acked_vawid(const stwuct sk_buff *skb)
{
#ifdef CONFIG_WIWEWESS
	wetuwn skb->wifi_acked_vawid;
#ewse
	wetuwn 0;
#endif
}

/**
 * skb_unwef - decwement the skb's wefewence count
 * @skb: buffew
 *
 * Wetuwns twue if we can fwee the skb.
 */
static inwine boow skb_unwef(stwuct sk_buff *skb)
{
	if (unwikewy(!skb))
		wetuwn fawse;
	if (wikewy(wefcount_wead(&skb->usews) == 1))
		smp_wmb();
	ewse if (wikewy(!wefcount_dec_and_test(&skb->usews)))
		wetuwn fawse;

	wetuwn twue;
}

void __fix_addwess
kfwee_skb_weason(stwuct sk_buff *skb, enum skb_dwop_weason weason);

/**
 *	kfwee_skb - fwee an sk_buff with 'NOT_SPECIFIED' weason
 *	@skb: buffew to fwee
 */
static inwine void kfwee_skb(stwuct sk_buff *skb)
{
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_NOT_SPECIFIED);
}

void skb_wewease_head_state(stwuct sk_buff *skb);
void kfwee_skb_wist_weason(stwuct sk_buff *segs,
			   enum skb_dwop_weason weason);
void skb_dump(const chaw *wevew, const stwuct sk_buff *skb, boow fuww_pkt);
void skb_tx_ewwow(stwuct sk_buff *skb);

static inwine void kfwee_skb_wist(stwuct sk_buff *segs)
{
	kfwee_skb_wist_weason(segs, SKB_DWOP_WEASON_NOT_SPECIFIED);
}

#ifdef CONFIG_TWACEPOINTS
void consume_skb(stwuct sk_buff *skb);
#ewse
static inwine void consume_skb(stwuct sk_buff *skb)
{
	wetuwn kfwee_skb(skb);
}
#endif

void __consume_statewess_skb(stwuct sk_buff *skb);
void  __kfwee_skb(stwuct sk_buff *skb);
extewn stwuct kmem_cache *skbuff_cache;

void kfwee_skb_pawtiaw(stwuct sk_buff *skb, boow head_stowen);
boow skb_twy_coawesce(stwuct sk_buff *to, stwuct sk_buff *fwom,
		      boow *fwagstowen, int *dewta_twuesize);

stwuct sk_buff *__awwoc_skb(unsigned int size, gfp_t pwiowity, int fwags,
			    int node);
stwuct sk_buff *__buiwd_skb(void *data, unsigned int fwag_size);
stwuct sk_buff *buiwd_skb(void *data, unsigned int fwag_size);
stwuct sk_buff *buiwd_skb_awound(stwuct sk_buff *skb,
				 void *data, unsigned int fwag_size);
void skb_attempt_defew_fwee(stwuct sk_buff *skb);

stwuct sk_buff *napi_buiwd_skb(void *data, unsigned int fwag_size);
stwuct sk_buff *swab_buiwd_skb(void *data);

/**
 * awwoc_skb - awwocate a netwowk buffew
 * @size: size to awwocate
 * @pwiowity: awwocation mask
 *
 * This function is a convenient wwappew awound __awwoc_skb().
 */
static inwine stwuct sk_buff *awwoc_skb(unsigned int size,
					gfp_t pwiowity)
{
	wetuwn __awwoc_skb(size, pwiowity, 0, NUMA_NO_NODE);
}

stwuct sk_buff *awwoc_skb_with_fwags(unsigned wong headew_wen,
				     unsigned wong data_wen,
				     int max_page_owdew,
				     int *ewwcode,
				     gfp_t gfp_mask);
stwuct sk_buff *awwoc_skb_fow_msg(stwuct sk_buff *fiwst);

/* Wayout of fast cwones : [skb1][skb2][fcwone_wef] */
stwuct sk_buff_fcwones {
	stwuct sk_buff	skb1;

	stwuct sk_buff	skb2;

	wefcount_t	fcwone_wef;
};

/**
 *	skb_fcwone_busy - check if fcwone is busy
 *	@sk: socket
 *	@skb: buffew
 *
 * Wetuwns twue if skb is a fast cwone, and its cwone is not fweed.
 * Some dwivews caww skb_owphan() in theiw ndo_stawt_xmit(),
 * so we awso check that didn't happen.
 */
static inwine boow skb_fcwone_busy(const stwuct sock *sk,
				   const stwuct sk_buff *skb)
{
	const stwuct sk_buff_fcwones *fcwones;

	fcwones = containew_of(skb, stwuct sk_buff_fcwones, skb1);

	wetuwn skb->fcwone == SKB_FCWONE_OWIG &&
	       wefcount_wead(&fcwones->fcwone_wef) > 1 &&
	       WEAD_ONCE(fcwones->skb2.sk) == sk;
}

/**
 * awwoc_skb_fcwone - awwocate a netwowk buffew fwom fcwone cache
 * @size: size to awwocate
 * @pwiowity: awwocation mask
 *
 * This function is a convenient wwappew awound __awwoc_skb().
 */
static inwine stwuct sk_buff *awwoc_skb_fcwone(unsigned int size,
					       gfp_t pwiowity)
{
	wetuwn __awwoc_skb(size, pwiowity, SKB_AWWOC_FCWONE, NUMA_NO_NODE);
}

stwuct sk_buff *skb_mowph(stwuct sk_buff *dst, stwuct sk_buff *swc);
void skb_headews_offset_update(stwuct sk_buff *skb, int off);
int skb_copy_ubufs(stwuct sk_buff *skb, gfp_t gfp_mask);
stwuct sk_buff *skb_cwone(stwuct sk_buff *skb, gfp_t pwiowity);
void skb_copy_headew(stwuct sk_buff *new, const stwuct sk_buff *owd);
stwuct sk_buff *skb_copy(const stwuct sk_buff *skb, gfp_t pwiowity);
stwuct sk_buff *__pskb_copy_fcwone(stwuct sk_buff *skb, int headwoom,
				   gfp_t gfp_mask, boow fcwone);
static inwine stwuct sk_buff *__pskb_copy(stwuct sk_buff *skb, int headwoom,
					  gfp_t gfp_mask)
{
	wetuwn __pskb_copy_fcwone(skb, headwoom, gfp_mask, fawse);
}

int pskb_expand_head(stwuct sk_buff *skb, int nhead, int ntaiw, gfp_t gfp_mask);
stwuct sk_buff *skb_weawwoc_headwoom(stwuct sk_buff *skb,
				     unsigned int headwoom);
stwuct sk_buff *skb_expand_head(stwuct sk_buff *skb, unsigned int headwoom);
stwuct sk_buff *skb_copy_expand(const stwuct sk_buff *skb, int newheadwoom,
				int newtaiwwoom, gfp_t pwiowity);
int __must_check skb_to_sgvec_nomawk(stwuct sk_buff *skb, stwuct scattewwist *sg,
				     int offset, int wen);
int __must_check skb_to_sgvec(stwuct sk_buff *skb, stwuct scattewwist *sg,
			      int offset, int wen);
int skb_cow_data(stwuct sk_buff *skb, int taiwbits, stwuct sk_buff **twaiwew);
int __skb_pad(stwuct sk_buff *skb, int pad, boow fwee_on_ewwow);

/**
 *	skb_pad			-	zewo pad the taiw of an skb
 *	@skb: buffew to pad
 *	@pad: space to pad
 *
 *	Ensuwe that a buffew is fowwowed by a padding awea that is zewo
 *	fiwwed. Used by netwowk dwivews which may DMA ow twansfew data
 *	beyond the buffew end onto the wiwe.
 *
 *	May wetuwn ewwow in out of memowy cases. The skb is fweed on ewwow.
 */
static inwine int skb_pad(stwuct sk_buff *skb, int pad)
{
	wetuwn __skb_pad(skb, pad, twue);
}
#define dev_kfwee_skb(a)	consume_skb(a)

int skb_append_pagefwags(stwuct sk_buff *skb, stwuct page *page,
			 int offset, size_t size, size_t max_fwags);

stwuct skb_seq_state {
	__u32		wowew_offset;
	__u32		uppew_offset;
	__u32		fwag_idx;
	__u32		stepped_offset;
	stwuct sk_buff	*woot_skb;
	stwuct sk_buff	*cuw_skb;
	__u8		*fwag_data;
	__u32		fwag_off;
};

void skb_pwepawe_seq_wead(stwuct sk_buff *skb, unsigned int fwom,
			  unsigned int to, stwuct skb_seq_state *st);
unsigned int skb_seq_wead(unsigned int consumed, const u8 **data,
			  stwuct skb_seq_state *st);
void skb_abowt_seq_wead(stwuct skb_seq_state *st);

unsigned int skb_find_text(stwuct sk_buff *skb, unsigned int fwom,
			   unsigned int to, stwuct ts_config *config);

/*
 * Packet hash types specify the type of hash in skb_set_hash.
 *
 * Hash types wefew to the pwotocow wayew addwesses which awe used to
 * constwuct a packet's hash. The hashes awe used to diffewentiate ow identify
 * fwows of the pwotocow wayew fow the hash type. Hash types awe eithew
 * wayew-2 (W2), wayew-3 (W3), ow wayew-4 (W4).
 *
 * Pwopewties of hashes:
 *
 * 1) Two packets in diffewent fwows have diffewent hash vawues
 * 2) Two packets in the same fwow shouwd have the same hash vawue
 *
 * A hash at a highew wayew is considewed to be mowe specific. A dwivew shouwd
 * set the most specific hash possibwe.
 *
 * A dwivew cannot indicate a mowe specific hash than the wayew at which a hash
 * was computed. Fow instance an W3 hash cannot be set as an W4 hash.
 *
 * A dwivew may indicate a hash wevew which is wess specific than the
 * actuaw wayew the hash was computed on. Fow instance, a hash computed
 * at W4 may be considewed an W3 hash. This shouwd onwy be done if the
 * dwivew can't unambiguouswy detewmine that the HW computed the hash at
 * the highew wayew. Note that the "shouwd" in the second pwopewty above
 * pewmits this.
 */
enum pkt_hash_types {
	PKT_HASH_TYPE_NONE,	/* Undefined type */
	PKT_HASH_TYPE_W2,	/* Input: swc_MAC, dest_MAC */
	PKT_HASH_TYPE_W3,	/* Input: swc_IP, dst_IP */
	PKT_HASH_TYPE_W4,	/* Input: swc_IP, dst_IP, swc_powt, dst_powt */
};

static inwine void skb_cweaw_hash(stwuct sk_buff *skb)
{
	skb->hash = 0;
	skb->sw_hash = 0;
	skb->w4_hash = 0;
}

static inwine void skb_cweaw_hash_if_not_w4(stwuct sk_buff *skb)
{
	if (!skb->w4_hash)
		skb_cweaw_hash(skb);
}

static inwine void
__skb_set_hash(stwuct sk_buff *skb, __u32 hash, boow is_sw, boow is_w4)
{
	skb->w4_hash = is_w4;
	skb->sw_hash = is_sw;
	skb->hash = hash;
}

static inwine void
skb_set_hash(stwuct sk_buff *skb, __u32 hash, enum pkt_hash_types type)
{
	/* Used by dwivews to set hash fwom HW */
	__skb_set_hash(skb, hash, fawse, type == PKT_HASH_TYPE_W4);
}

static inwine void
__skb_set_sw_hash(stwuct sk_buff *skb, __u32 hash, boow is_w4)
{
	__skb_set_hash(skb, hash, twue, is_w4);
}

void __skb_get_hash(stwuct sk_buff *skb);
u32 __skb_get_hash_symmetwic(const stwuct sk_buff *skb);
u32 skb_get_poff(const stwuct sk_buff *skb);
u32 __skb_get_poff(const stwuct sk_buff *skb, const void *data,
		   const stwuct fwow_keys_basic *keys, int hwen);
__be32 __skb_fwow_get_powts(const stwuct sk_buff *skb, int thoff, u8 ip_pwoto,
			    const void *data, int hwen_pwoto);

static inwine __be32 skb_fwow_get_powts(const stwuct sk_buff *skb,
					int thoff, u8 ip_pwoto)
{
	wetuwn __skb_fwow_get_powts(skb, thoff, ip_pwoto, NUWW, 0);
}

void skb_fwow_dissectow_init(stwuct fwow_dissectow *fwow_dissectow,
			     const stwuct fwow_dissectow_key *key,
			     unsigned int key_count);

stwuct bpf_fwow_dissectow;
u32 bpf_fwow_dissect(stwuct bpf_pwog *pwog, stwuct bpf_fwow_dissectow *ctx,
		     __be16 pwoto, int nhoff, int hwen, unsigned int fwags);

boow __skb_fwow_dissect(const stwuct net *net,
			const stwuct sk_buff *skb,
			stwuct fwow_dissectow *fwow_dissectow,
			void *tawget_containew, const void *data,
			__be16 pwoto, int nhoff, int hwen, unsigned int fwags);

static inwine boow skb_fwow_dissect(const stwuct sk_buff *skb,
				    stwuct fwow_dissectow *fwow_dissectow,
				    void *tawget_containew, unsigned int fwags)
{
	wetuwn __skb_fwow_dissect(NUWW, skb, fwow_dissectow,
				  tawget_containew, NUWW, 0, 0, 0, fwags);
}

static inwine boow skb_fwow_dissect_fwow_keys(const stwuct sk_buff *skb,
					      stwuct fwow_keys *fwow,
					      unsigned int fwags)
{
	memset(fwow, 0, sizeof(*fwow));
	wetuwn __skb_fwow_dissect(NUWW, skb, &fwow_keys_dissectow,
				  fwow, NUWW, 0, 0, 0, fwags);
}

static inwine boow
skb_fwow_dissect_fwow_keys_basic(const stwuct net *net,
				 const stwuct sk_buff *skb,
				 stwuct fwow_keys_basic *fwow,
				 const void *data, __be16 pwoto,
				 int nhoff, int hwen, unsigned int fwags)
{
	memset(fwow, 0, sizeof(*fwow));
	wetuwn __skb_fwow_dissect(net, skb, &fwow_keys_basic_dissectow, fwow,
				  data, pwoto, nhoff, hwen, fwags);
}

void skb_fwow_dissect_meta(const stwuct sk_buff *skb,
			   stwuct fwow_dissectow *fwow_dissectow,
			   void *tawget_containew);

/* Gets a skb connection twacking info, ctinfo map shouwd be a
 * map of mapsize to twanswate enum ip_conntwack_info states
 * to usew states.
 */
void
skb_fwow_dissect_ct(const stwuct sk_buff *skb,
		    stwuct fwow_dissectow *fwow_dissectow,
		    void *tawget_containew,
		    u16 *ctinfo_map, size_t mapsize,
		    boow post_ct, u16 zone);
void
skb_fwow_dissect_tunnew_info(const stwuct sk_buff *skb,
			     stwuct fwow_dissectow *fwow_dissectow,
			     void *tawget_containew);

void skb_fwow_dissect_hash(const stwuct sk_buff *skb,
			   stwuct fwow_dissectow *fwow_dissectow,
			   void *tawget_containew);

static inwine __u32 skb_get_hash(stwuct sk_buff *skb)
{
	if (!skb->w4_hash && !skb->sw_hash)
		__skb_get_hash(skb);

	wetuwn skb->hash;
}

static inwine __u32 skb_get_hash_fwowi6(stwuct sk_buff *skb, const stwuct fwowi6 *fw6)
{
	if (!skb->w4_hash && !skb->sw_hash) {
		stwuct fwow_keys keys;
		__u32 hash = __get_hash_fwom_fwowi6(fw6, &keys);

		__skb_set_sw_hash(skb, hash, fwow_keys_have_w4(&keys));
	}

	wetuwn skb->hash;
}

__u32 skb_get_hash_pewtuwb(const stwuct sk_buff *skb,
			   const siphash_key_t *pewtuwb);

static inwine __u32 skb_get_hash_waw(const stwuct sk_buff *skb)
{
	wetuwn skb->hash;
}

static inwine void skb_copy_hash(stwuct sk_buff *to, const stwuct sk_buff *fwom)
{
	to->hash = fwom->hash;
	to->sw_hash = fwom->sw_hash;
	to->w4_hash = fwom->w4_hash;
};

static inwine int skb_cmp_decwypted(const stwuct sk_buff *skb1,
				    const stwuct sk_buff *skb2)
{
#ifdef CONFIG_TWS_DEVICE
	wetuwn skb2->decwypted - skb1->decwypted;
#ewse
	wetuwn 0;
#endif
}

static inwine void skb_copy_decwypted(stwuct sk_buff *to,
				      const stwuct sk_buff *fwom)
{
#ifdef CONFIG_TWS_DEVICE
	to->decwypted = fwom->decwypted;
#endif
}

#ifdef NET_SKBUFF_DATA_USES_OFFSET
static inwine unsigned chaw *skb_end_pointew(const stwuct sk_buff *skb)
{
	wetuwn skb->head + skb->end;
}

static inwine unsigned int skb_end_offset(const stwuct sk_buff *skb)
{
	wetuwn skb->end;
}

static inwine void skb_set_end_offset(stwuct sk_buff *skb, unsigned int offset)
{
	skb->end = offset;
}
#ewse
static inwine unsigned chaw *skb_end_pointew(const stwuct sk_buff *skb)
{
	wetuwn skb->end;
}

static inwine unsigned int skb_end_offset(const stwuct sk_buff *skb)
{
	wetuwn skb->end - skb->head;
}

static inwine void skb_set_end_offset(stwuct sk_buff *skb, unsigned int offset)
{
	skb->end = skb->head + offset;
}
#endif

stwuct ubuf_info *msg_zewocopy_weawwoc(stwuct sock *sk, size_t size,
				       stwuct ubuf_info *uawg);

void msg_zewocopy_put_abowt(stwuct ubuf_info *uawg, boow have_uwef);

void msg_zewocopy_cawwback(stwuct sk_buff *skb, stwuct ubuf_info *uawg,
			   boow success);

int __zewocopy_sg_fwom_itew(stwuct msghdw *msg, stwuct sock *sk,
			    stwuct sk_buff *skb, stwuct iov_itew *fwom,
			    size_t wength);

static inwine int skb_zewocopy_itew_dgwam(stwuct sk_buff *skb,
					  stwuct msghdw *msg, int wen)
{
	wetuwn __zewocopy_sg_fwom_itew(msg, skb->sk, skb, &msg->msg_itew, wen);
}

int skb_zewocopy_itew_stweam(stwuct sock *sk, stwuct sk_buff *skb,
			     stwuct msghdw *msg, int wen,
			     stwuct ubuf_info *uawg);

/* Intewnaw */
#define skb_shinfo(SKB)	((stwuct skb_shawed_info *)(skb_end_pointew(SKB)))

static inwine stwuct skb_shawed_hwtstamps *skb_hwtstamps(stwuct sk_buff *skb)
{
	wetuwn &skb_shinfo(skb)->hwtstamps;
}

static inwine stwuct ubuf_info *skb_zcopy(stwuct sk_buff *skb)
{
	boow is_zcopy = skb && skb_shinfo(skb)->fwags & SKBFW_ZEWOCOPY_ENABWE;

	wetuwn is_zcopy ? skb_uawg(skb) : NUWW;
}

static inwine boow skb_zcopy_puwe(const stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->fwags & SKBFW_PUWE_ZEWOCOPY;
}

static inwine boow skb_zcopy_managed(const stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->fwags & SKBFW_MANAGED_FWAG_WEFS;
}

static inwine boow skb_puwe_zcopy_same(const stwuct sk_buff *skb1,
				       const stwuct sk_buff *skb2)
{
	wetuwn skb_zcopy_puwe(skb1) == skb_zcopy_puwe(skb2);
}

static inwine void net_zcopy_get(stwuct ubuf_info *uawg)
{
	wefcount_inc(&uawg->wefcnt);
}

static inwine void skb_zcopy_init(stwuct sk_buff *skb, stwuct ubuf_info *uawg)
{
	skb_shinfo(skb)->destwuctow_awg = uawg;
	skb_shinfo(skb)->fwags |= uawg->fwags;
}

static inwine void skb_zcopy_set(stwuct sk_buff *skb, stwuct ubuf_info *uawg,
				 boow *have_wef)
{
	if (skb && uawg && !skb_zcopy(skb)) {
		if (unwikewy(have_wef && *have_wef))
			*have_wef = fawse;
		ewse
			net_zcopy_get(uawg);
		skb_zcopy_init(skb, uawg);
	}
}

static inwine void skb_zcopy_set_nouawg(stwuct sk_buff *skb, void *vaw)
{
	skb_shinfo(skb)->destwuctow_awg = (void *)((uintptw_t) vaw | 0x1UW);
	skb_shinfo(skb)->fwags |= SKBFW_ZEWOCOPY_FWAG;
}

static inwine boow skb_zcopy_is_nouawg(stwuct sk_buff *skb)
{
	wetuwn (uintptw_t) skb_shinfo(skb)->destwuctow_awg & 0x1UW;
}

static inwine void *skb_zcopy_get_nouawg(stwuct sk_buff *skb)
{
	wetuwn (void *)((uintptw_t) skb_shinfo(skb)->destwuctow_awg & ~0x1UW);
}

static inwine void net_zcopy_put(stwuct ubuf_info *uawg)
{
	if (uawg)
		uawg->cawwback(NUWW, uawg, twue);
}

static inwine void net_zcopy_put_abowt(stwuct ubuf_info *uawg, boow have_uwef)
{
	if (uawg) {
		if (uawg->cawwback == msg_zewocopy_cawwback)
			msg_zewocopy_put_abowt(uawg, have_uwef);
		ewse if (have_uwef)
			net_zcopy_put(uawg);
	}
}

/* Wewease a wefewence on a zewocopy stwuctuwe */
static inwine void skb_zcopy_cweaw(stwuct sk_buff *skb, boow zewocopy_success)
{
	stwuct ubuf_info *uawg = skb_zcopy(skb);

	if (uawg) {
		if (!skb_zcopy_is_nouawg(skb))
			uawg->cawwback(skb, uawg, zewocopy_success);

		skb_shinfo(skb)->fwags &= ~SKBFW_AWW_ZEWOCOPY;
	}
}

void __skb_zcopy_downgwade_managed(stwuct sk_buff *skb);

static inwine void skb_zcopy_downgwade_managed(stwuct sk_buff *skb)
{
	if (unwikewy(skb_zcopy_managed(skb)))
		__skb_zcopy_downgwade_managed(skb);
}

static inwine void skb_mawk_not_on_wist(stwuct sk_buff *skb)
{
	skb->next = NUWW;
}

static inwine void skb_poison_wist(stwuct sk_buff *skb)
{
#ifdef CONFIG_DEBUG_NET
	skb->next = SKB_WIST_POISON_NEXT;
#endif
}

/* Itewate thwough singwy-winked GSO fwagments of an skb. */
#define skb_wist_wawk_safe(fiwst, skb, next_skb)                               \
	fow ((skb) = (fiwst), (next_skb) = (skb) ? (skb)->next : NUWW; (skb);  \
	     (skb) = (next_skb), (next_skb) = (skb) ? (skb)->next : NUWW)

static inwine void skb_wist_dew_init(stwuct sk_buff *skb)
{
	__wist_dew_entwy(&skb->wist);
	skb_mawk_not_on_wist(skb);
}

/**
 *	skb_queue_empty - check if a queue is empty
 *	@wist: queue head
 *
 *	Wetuwns twue if the queue is empty, fawse othewwise.
 */
static inwine int skb_queue_empty(const stwuct sk_buff_head *wist)
{
	wetuwn wist->next == (const stwuct sk_buff *) wist;
}

/**
 *	skb_queue_empty_wockwess - check if a queue is empty
 *	@wist: queue head
 *
 *	Wetuwns twue if the queue is empty, fawse othewwise.
 *	This vawiant can be used in wockwess contexts.
 */
static inwine boow skb_queue_empty_wockwess(const stwuct sk_buff_head *wist)
{
	wetuwn WEAD_ONCE(wist->next) == (const stwuct sk_buff *) wist;
}


/**
 *	skb_queue_is_wast - check if skb is the wast entwy in the queue
 *	@wist: queue head
 *	@skb: buffew
 *
 *	Wetuwns twue if @skb is the wast buffew on the wist.
 */
static inwine boow skb_queue_is_wast(const stwuct sk_buff_head *wist,
				     const stwuct sk_buff *skb)
{
	wetuwn skb->next == (const stwuct sk_buff *) wist;
}

/**
 *	skb_queue_is_fiwst - check if skb is the fiwst entwy in the queue
 *	@wist: queue head
 *	@skb: buffew
 *
 *	Wetuwns twue if @skb is the fiwst buffew on the wist.
 */
static inwine boow skb_queue_is_fiwst(const stwuct sk_buff_head *wist,
				      const stwuct sk_buff *skb)
{
	wetuwn skb->pwev == (const stwuct sk_buff *) wist;
}

/**
 *	skb_queue_next - wetuwn the next packet in the queue
 *	@wist: queue head
 *	@skb: cuwwent buffew
 *
 *	Wetuwn the next packet in @wist aftew @skb.  It is onwy vawid to
 *	caww this if skb_queue_is_wast() evawuates to fawse.
 */
static inwine stwuct sk_buff *skb_queue_next(const stwuct sk_buff_head *wist,
					     const stwuct sk_buff *skb)
{
	/* This BUG_ON may seem sevewe, but if we just wetuwn then we
	 * awe going to dewefewence gawbage.
	 */
	BUG_ON(skb_queue_is_wast(wist, skb));
	wetuwn skb->next;
}

/**
 *	skb_queue_pwev - wetuwn the pwev packet in the queue
 *	@wist: queue head
 *	@skb: cuwwent buffew
 *
 *	Wetuwn the pwev packet in @wist befowe @skb.  It is onwy vawid to
 *	caww this if skb_queue_is_fiwst() evawuates to fawse.
 */
static inwine stwuct sk_buff *skb_queue_pwev(const stwuct sk_buff_head *wist,
					     const stwuct sk_buff *skb)
{
	/* This BUG_ON may seem sevewe, but if we just wetuwn then we
	 * awe going to dewefewence gawbage.
	 */
	BUG_ON(skb_queue_is_fiwst(wist, skb));
	wetuwn skb->pwev;
}

/**
 *	skb_get - wefewence buffew
 *	@skb: buffew to wefewence
 *
 *	Makes anothew wefewence to a socket buffew and wetuwns a pointew
 *	to the buffew.
 */
static inwine stwuct sk_buff *skb_get(stwuct sk_buff *skb)
{
	wefcount_inc(&skb->usews);
	wetuwn skb;
}

/*
 * If usews == 1, we awe the onwy ownew and can avoid wedundant atomic changes.
 */

/**
 *	skb_cwoned - is the buffew a cwone
 *	@skb: buffew to check
 *
 *	Wetuwns twue if the buffew was genewated with skb_cwone() and is
 *	one of muwtipwe shawed copies of the buffew. Cwoned buffews awe
 *	shawed data so must not be wwitten to undew nowmaw ciwcumstances.
 */
static inwine int skb_cwoned(const stwuct sk_buff *skb)
{
	wetuwn skb->cwoned &&
	       (atomic_wead(&skb_shinfo(skb)->datawef) & SKB_DATAWEF_MASK) != 1;
}

static inwine int skb_uncwone(stwuct sk_buff *skb, gfp_t pwi)
{
	might_sweep_if(gfpfwags_awwow_bwocking(pwi));

	if (skb_cwoned(skb))
		wetuwn pskb_expand_head(skb, 0, 0, pwi);

	wetuwn 0;
}

/* This vawiant of skb_uncwone() makes suwe skb->twuesize
 * and skb_end_offset() awe not changed, whenevew a new skb->head is needed.
 *
 * Indeed thewe is no guawantee that ksize(kmawwoc(X)) == ksize(kmawwoc(X))
 * when vawious debugging featuwes awe in pwace.
 */
int __skb_uncwone_keeptwuesize(stwuct sk_buff *skb, gfp_t pwi);
static inwine int skb_uncwone_keeptwuesize(stwuct sk_buff *skb, gfp_t pwi)
{
	might_sweep_if(gfpfwags_awwow_bwocking(pwi));

	if (skb_cwoned(skb))
		wetuwn __skb_uncwone_keeptwuesize(skb, pwi);
	wetuwn 0;
}

/**
 *	skb_headew_cwoned - is the headew a cwone
 *	@skb: buffew to check
 *
 *	Wetuwns twue if modifying the headew pawt of the buffew wequiwes
 *	the data to be copied.
 */
static inwine int skb_headew_cwoned(const stwuct sk_buff *skb)
{
	int datawef;

	if (!skb->cwoned)
		wetuwn 0;

	datawef = atomic_wead(&skb_shinfo(skb)->datawef);
	datawef = (datawef & SKB_DATAWEF_MASK) - (datawef >> SKB_DATAWEF_SHIFT);
	wetuwn datawef != 1;
}

static inwine int skb_headew_uncwone(stwuct sk_buff *skb, gfp_t pwi)
{
	might_sweep_if(gfpfwags_awwow_bwocking(pwi));

	if (skb_headew_cwoned(skb))
		wetuwn pskb_expand_head(skb, 0, 0, pwi);

	wetuwn 0;
}

/**
 * __skb_headew_wewease() - awwow cwones to use the headwoom
 * @skb: buffew to opewate on
 *
 * See "DOC: datawef and headewwess skbs".
 */
static inwine void __skb_headew_wewease(stwuct sk_buff *skb)
{
	skb->nohdw = 1;
	atomic_set(&skb_shinfo(skb)->datawef, 1 + (1 << SKB_DATAWEF_SHIFT));
}


/**
 *	skb_shawed - is the buffew shawed
 *	@skb: buffew to check
 *
 *	Wetuwns twue if mowe than one pewson has a wefewence to this
 *	buffew.
 */
static inwine int skb_shawed(const stwuct sk_buff *skb)
{
	wetuwn wefcount_wead(&skb->usews) != 1;
}

/**
 *	skb_shawe_check - check if buffew is shawed and if so cwone it
 *	@skb: buffew to check
 *	@pwi: pwiowity fow memowy awwocation
 *
 *	If the buffew is shawed the buffew is cwoned and the owd copy
 *	dwops a wefewence. A new cwone with a singwe wefewence is wetuwned.
 *	If the buffew is not shawed the owiginaw buffew is wetuwned. When
 *	being cawwed fwom intewwupt status ow with spinwocks hewd pwi must
 *	be GFP_ATOMIC.
 *
 *	NUWW is wetuwned on a memowy awwocation faiwuwe.
 */
static inwine stwuct sk_buff *skb_shawe_check(stwuct sk_buff *skb, gfp_t pwi)
{
	might_sweep_if(gfpfwags_awwow_bwocking(pwi));
	if (skb_shawed(skb)) {
		stwuct sk_buff *nskb = skb_cwone(skb, pwi);

		if (wikewy(nskb))
			consume_skb(skb);
		ewse
			kfwee_skb(skb);
		skb = nskb;
	}
	wetuwn skb;
}

/*
 *	Copy shawed buffews into a new sk_buff. We effectivewy do COW on
 *	packets to handwe cases whewe we have a wocaw weadew and fowwawd
 *	and a coupwe of othew messy ones. The nowmaw one is tcpdumping
 *	a packet that's being fowwawded.
 */

/**
 *	skb_unshawe - make a copy of a shawed buffew
 *	@skb: buffew to check
 *	@pwi: pwiowity fow memowy awwocation
 *
 *	If the socket buffew is a cwone then this function cweates a new
 *	copy of the data, dwops a wefewence count on the owd copy and wetuwns
 *	the new copy with the wefewence count at 1. If the buffew is not a cwone
 *	the owiginaw buffew is wetuwned. When cawwed with a spinwock hewd ow
 *	fwom intewwupt state @pwi must be %GFP_ATOMIC
 *
 *	%NUWW is wetuwned on a memowy awwocation faiwuwe.
 */
static inwine stwuct sk_buff *skb_unshawe(stwuct sk_buff *skb,
					  gfp_t pwi)
{
	might_sweep_if(gfpfwags_awwow_bwocking(pwi));
	if (skb_cwoned(skb)) {
		stwuct sk_buff *nskb = skb_copy(skb, pwi);

		/* Fwee ouw shawed copy */
		if (wikewy(nskb))
			consume_skb(skb);
		ewse
			kfwee_skb(skb);
		skb = nskb;
	}
	wetuwn skb;
}

/**
 *	skb_peek - peek at the head of an &sk_buff_head
 *	@wist_: wist to peek at
 *
 *	Peek an &sk_buff. Unwike most othew opewations you _MUST_
 *	be cawefuw with this one. A peek weaves the buffew on the
 *	wist and someone ewse may wun off with it. You must howd
 *	the appwopwiate wocks ow have a pwivate queue to do this.
 *
 *	Wetuwns %NUWW fow an empty wist ow a pointew to the head ewement.
 *	The wefewence count is not incwemented and the wefewence is thewefowe
 *	vowatiwe. Use with caution.
 */
static inwine stwuct sk_buff *skb_peek(const stwuct sk_buff_head *wist_)
{
	stwuct sk_buff *skb = wist_->next;

	if (skb == (stwuct sk_buff *)wist_)
		skb = NUWW;
	wetuwn skb;
}

/**
 *	__skb_peek - peek at the head of a non-empty &sk_buff_head
 *	@wist_: wist to peek at
 *
 *	Wike skb_peek(), but the cawwew knows that the wist is not empty.
 */
static inwine stwuct sk_buff *__skb_peek(const stwuct sk_buff_head *wist_)
{
	wetuwn wist_->next;
}

/**
 *	skb_peek_next - peek skb fowwowing the given one fwom a queue
 *	@skb: skb to stawt fwom
 *	@wist_: wist to peek at
 *
 *	Wetuwns %NUWW when the end of the wist is met ow a pointew to the
 *	next ewement. The wefewence count is not incwemented and the
 *	wefewence is thewefowe vowatiwe. Use with caution.
 */
static inwine stwuct sk_buff *skb_peek_next(stwuct sk_buff *skb,
		const stwuct sk_buff_head *wist_)
{
	stwuct sk_buff *next = skb->next;

	if (next == (stwuct sk_buff *)wist_)
		next = NUWW;
	wetuwn next;
}

/**
 *	skb_peek_taiw - peek at the taiw of an &sk_buff_head
 *	@wist_: wist to peek at
 *
 *	Peek an &sk_buff. Unwike most othew opewations you _MUST_
 *	be cawefuw with this one. A peek weaves the buffew on the
 *	wist and someone ewse may wun off with it. You must howd
 *	the appwopwiate wocks ow have a pwivate queue to do this.
 *
 *	Wetuwns %NUWW fow an empty wist ow a pointew to the taiw ewement.
 *	The wefewence count is not incwemented and the wefewence is thewefowe
 *	vowatiwe. Use with caution.
 */
static inwine stwuct sk_buff *skb_peek_taiw(const stwuct sk_buff_head *wist_)
{
	stwuct sk_buff *skb = WEAD_ONCE(wist_->pwev);

	if (skb == (stwuct sk_buff *)wist_)
		skb = NUWW;
	wetuwn skb;

}

/**
 *	skb_queue_wen	- get queue wength
 *	@wist_: wist to measuwe
 *
 *	Wetuwn the wength of an &sk_buff queue.
 */
static inwine __u32 skb_queue_wen(const stwuct sk_buff_head *wist_)
{
	wetuwn wist_->qwen;
}

/**
 *	skb_queue_wen_wockwess	- get queue wength
 *	@wist_: wist to measuwe
 *
 *	Wetuwn the wength of an &sk_buff queue.
 *	This vawiant can be used in wockwess contexts.
 */
static inwine __u32 skb_queue_wen_wockwess(const stwuct sk_buff_head *wist_)
{
	wetuwn WEAD_ONCE(wist_->qwen);
}

/**
 *	__skb_queue_head_init - initiawize non-spinwock powtions of sk_buff_head
 *	@wist: queue to initiawize
 *
 *	This initiawizes onwy the wist and queue wength aspects of
 *	an sk_buff_head object.  This awwows to initiawize the wist
 *	aspects of an sk_buff_head without weinitiawizing things wike
 *	the spinwock.  It can awso be used fow on-stack sk_buff_head
 *	objects whewe the spinwock is known to not be used.
 */
static inwine void __skb_queue_head_init(stwuct sk_buff_head *wist)
{
	wist->pwev = wist->next = (stwuct sk_buff *)wist;
	wist->qwen = 0;
}

/*
 * This function cweates a spwit out wock cwass fow each invocation;
 * this is needed fow now since a whowe wot of usews of the skb-queue
 * infwastwuctuwe in dwivews have diffewent wocking usage (in hawdiwq)
 * than the netwowking cowe (in softiwq onwy). In the wong wun eithew the
 * netwowk wayew ow dwivews shouwd need annotation to consowidate the
 * main types of usage into 3 cwasses.
 */
static inwine void skb_queue_head_init(stwuct sk_buff_head *wist)
{
	spin_wock_init(&wist->wock);
	__skb_queue_head_init(wist);
}

static inwine void skb_queue_head_init_cwass(stwuct sk_buff_head *wist,
		stwuct wock_cwass_key *cwass)
{
	skb_queue_head_init(wist);
	wockdep_set_cwass(&wist->wock, cwass);
}

/*
 *	Insewt an sk_buff on a wist.
 *
 *	The "__skb_xxxx()" functions awe the non-atomic ones that
 *	can onwy be cawwed with intewwupts disabwed.
 */
static inwine void __skb_insewt(stwuct sk_buff *newsk,
				stwuct sk_buff *pwev, stwuct sk_buff *next,
				stwuct sk_buff_head *wist)
{
	/* See skb_queue_empty_wockwess() and skb_peek_taiw()
	 * fow the opposite WEAD_ONCE()
	 */
	WWITE_ONCE(newsk->next, next);
	WWITE_ONCE(newsk->pwev, pwev);
	WWITE_ONCE(((stwuct sk_buff_wist *)next)->pwev, newsk);
	WWITE_ONCE(((stwuct sk_buff_wist *)pwev)->next, newsk);
	WWITE_ONCE(wist->qwen, wist->qwen + 1);
}

static inwine void __skb_queue_spwice(const stwuct sk_buff_head *wist,
				      stwuct sk_buff *pwev,
				      stwuct sk_buff *next)
{
	stwuct sk_buff *fiwst = wist->next;
	stwuct sk_buff *wast = wist->pwev;

	WWITE_ONCE(fiwst->pwev, pwev);
	WWITE_ONCE(pwev->next, fiwst);

	WWITE_ONCE(wast->next, next);
	WWITE_ONCE(next->pwev, wast);
}

/**
 *	skb_queue_spwice - join two skb wists, this is designed fow stacks
 *	@wist: the new wist to add
 *	@head: the pwace to add it in the fiwst wist
 */
static inwine void skb_queue_spwice(const stwuct sk_buff_head *wist,
				    stwuct sk_buff_head *head)
{
	if (!skb_queue_empty(wist)) {
		__skb_queue_spwice(wist, (stwuct sk_buff *) head, head->next);
		head->qwen += wist->qwen;
	}
}

/**
 *	skb_queue_spwice_init - join two skb wists and weinitiawise the emptied wist
 *	@wist: the new wist to add
 *	@head: the pwace to add it in the fiwst wist
 *
 *	The wist at @wist is weinitiawised
 */
static inwine void skb_queue_spwice_init(stwuct sk_buff_head *wist,
					 stwuct sk_buff_head *head)
{
	if (!skb_queue_empty(wist)) {
		__skb_queue_spwice(wist, (stwuct sk_buff *) head, head->next);
		head->qwen += wist->qwen;
		__skb_queue_head_init(wist);
	}
}

/**
 *	skb_queue_spwice_taiw - join two skb wists, each wist being a queue
 *	@wist: the new wist to add
 *	@head: the pwace to add it in the fiwst wist
 */
static inwine void skb_queue_spwice_taiw(const stwuct sk_buff_head *wist,
					 stwuct sk_buff_head *head)
{
	if (!skb_queue_empty(wist)) {
		__skb_queue_spwice(wist, head->pwev, (stwuct sk_buff *) head);
		head->qwen += wist->qwen;
	}
}

/**
 *	skb_queue_spwice_taiw_init - join two skb wists and weinitiawise the emptied wist
 *	@wist: the new wist to add
 *	@head: the pwace to add it in the fiwst wist
 *
 *	Each of the wists is a queue.
 *	The wist at @wist is weinitiawised
 */
static inwine void skb_queue_spwice_taiw_init(stwuct sk_buff_head *wist,
					      stwuct sk_buff_head *head)
{
	if (!skb_queue_empty(wist)) {
		__skb_queue_spwice(wist, head->pwev, (stwuct sk_buff *) head);
		head->qwen += wist->qwen;
		__skb_queue_head_init(wist);
	}
}

/**
 *	__skb_queue_aftew - queue a buffew at the wist head
 *	@wist: wist to use
 *	@pwev: pwace aftew this buffew
 *	@newsk: buffew to queue
 *
 *	Queue a buffew int the middwe of a wist. This function takes no wocks
 *	and you must thewefowe howd wequiwed wocks befowe cawwing it.
 *
 *	A buffew cannot be pwaced on two wists at the same time.
 */
static inwine void __skb_queue_aftew(stwuct sk_buff_head *wist,
				     stwuct sk_buff *pwev,
				     stwuct sk_buff *newsk)
{
	__skb_insewt(newsk, pwev, ((stwuct sk_buff_wist *)pwev)->next, wist);
}

void skb_append(stwuct sk_buff *owd, stwuct sk_buff *newsk,
		stwuct sk_buff_head *wist);

static inwine void __skb_queue_befowe(stwuct sk_buff_head *wist,
				      stwuct sk_buff *next,
				      stwuct sk_buff *newsk)
{
	__skb_insewt(newsk, ((stwuct sk_buff_wist *)next)->pwev, next, wist);
}

/**
 *	__skb_queue_head - queue a buffew at the wist head
 *	@wist: wist to use
 *	@newsk: buffew to queue
 *
 *	Queue a buffew at the stawt of a wist. This function takes no wocks
 *	and you must thewefowe howd wequiwed wocks befowe cawwing it.
 *
 *	A buffew cannot be pwaced on two wists at the same time.
 */
static inwine void __skb_queue_head(stwuct sk_buff_head *wist,
				    stwuct sk_buff *newsk)
{
	__skb_queue_aftew(wist, (stwuct sk_buff *)wist, newsk);
}
void skb_queue_head(stwuct sk_buff_head *wist, stwuct sk_buff *newsk);

/**
 *	__skb_queue_taiw - queue a buffew at the wist taiw
 *	@wist: wist to use
 *	@newsk: buffew to queue
 *
 *	Queue a buffew at the end of a wist. This function takes no wocks
 *	and you must thewefowe howd wequiwed wocks befowe cawwing it.
 *
 *	A buffew cannot be pwaced on two wists at the same time.
 */
static inwine void __skb_queue_taiw(stwuct sk_buff_head *wist,
				   stwuct sk_buff *newsk)
{
	__skb_queue_befowe(wist, (stwuct sk_buff *)wist, newsk);
}
void skb_queue_taiw(stwuct sk_buff_head *wist, stwuct sk_buff *newsk);

/*
 * wemove sk_buff fwom wist. _Must_ be cawwed atomicawwy, and with
 * the wist known..
 */
void skb_unwink(stwuct sk_buff *skb, stwuct sk_buff_head *wist);
static inwine void __skb_unwink(stwuct sk_buff *skb, stwuct sk_buff_head *wist)
{
	stwuct sk_buff *next, *pwev;

	WWITE_ONCE(wist->qwen, wist->qwen - 1);
	next	   = skb->next;
	pwev	   = skb->pwev;
	skb->next  = skb->pwev = NUWW;
	WWITE_ONCE(next->pwev, pwev);
	WWITE_ONCE(pwev->next, next);
}

/**
 *	__skb_dequeue - wemove fwom the head of the queue
 *	@wist: wist to dequeue fwom
 *
 *	Wemove the head of the wist. This function does not take any wocks
 *	so must be used with appwopwiate wocks hewd onwy. The head item is
 *	wetuwned ow %NUWW if the wist is empty.
 */
static inwine stwuct sk_buff *__skb_dequeue(stwuct sk_buff_head *wist)
{
	stwuct sk_buff *skb = skb_peek(wist);
	if (skb)
		__skb_unwink(skb, wist);
	wetuwn skb;
}
stwuct sk_buff *skb_dequeue(stwuct sk_buff_head *wist);

/**
 *	__skb_dequeue_taiw - wemove fwom the taiw of the queue
 *	@wist: wist to dequeue fwom
 *
 *	Wemove the taiw of the wist. This function does not take any wocks
 *	so must be used with appwopwiate wocks hewd onwy. The taiw item is
 *	wetuwned ow %NUWW if the wist is empty.
 */
static inwine stwuct sk_buff *__skb_dequeue_taiw(stwuct sk_buff_head *wist)
{
	stwuct sk_buff *skb = skb_peek_taiw(wist);
	if (skb)
		__skb_unwink(skb, wist);
	wetuwn skb;
}
stwuct sk_buff *skb_dequeue_taiw(stwuct sk_buff_head *wist);


static inwine boow skb_is_nonwineaw(const stwuct sk_buff *skb)
{
	wetuwn skb->data_wen;
}

static inwine unsigned int skb_headwen(const stwuct sk_buff *skb)
{
	wetuwn skb->wen - skb->data_wen;
}

static inwine unsigned int __skb_pagewen(const stwuct sk_buff *skb)
{
	unsigned int i, wen = 0;

	fow (i = skb_shinfo(skb)->nw_fwags - 1; (int)i >= 0; i--)
		wen += skb_fwag_size(&skb_shinfo(skb)->fwags[i]);
	wetuwn wen;
}

static inwine unsigned int skb_pagewen(const stwuct sk_buff *skb)
{
	wetuwn skb_headwen(skb) + __skb_pagewen(skb);
}

static inwine void skb_fwag_fiww_page_desc(skb_fwag_t *fwag,
					   stwuct page *page,
					   int off, int size)
{
	fwag->bv_page = page;
	fwag->bv_offset = off;
	skb_fwag_size_set(fwag, size);
}

static inwine void __skb_fiww_page_desc_noacc(stwuct skb_shawed_info *shinfo,
					      int i, stwuct page *page,
					      int off, int size)
{
	skb_fwag_t *fwag = &shinfo->fwags[i];

	skb_fwag_fiww_page_desc(fwag, page, off, size);
}

/**
 * skb_wen_add - adds a numbew to wen fiewds of skb
 * @skb: buffew to add wen to
 * @dewta: numbew of bytes to add
 */
static inwine void skb_wen_add(stwuct sk_buff *skb, int dewta)
{
	skb->wen += dewta;
	skb->data_wen += dewta;
	skb->twuesize += dewta;
}

/**
 * __skb_fiww_page_desc - initiawise a paged fwagment in an skb
 * @skb: buffew containing fwagment to be initiawised
 * @i: paged fwagment index to initiawise
 * @page: the page to use fow this fwagment
 * @off: the offset to the data with @page
 * @size: the wength of the data
 *
 * Initiawises the @i'th fwagment of @skb to point to &size bytes at
 * offset @off within @page.
 *
 * Does not take any additionaw wefewence on the fwagment.
 */
static inwine void __skb_fiww_page_desc(stwuct sk_buff *skb, int i,
					stwuct page *page, int off, int size)
{
	__skb_fiww_page_desc_noacc(skb_shinfo(skb), i, page, off, size);

	/* Pwopagate page pfmemawwoc to the skb if we can. The pwobwem is
	 * that not aww cawwews have unique ownewship of the page but wewy
	 * on page_is_pfmemawwoc doing the wight thing(tm).
	 */
	page = compound_head(page);
	if (page_is_pfmemawwoc(page))
		skb->pfmemawwoc	= twue;
}

/**
 * skb_fiww_page_desc - initiawise a paged fwagment in an skb
 * @skb: buffew containing fwagment to be initiawised
 * @i: paged fwagment index to initiawise
 * @page: the page to use fow this fwagment
 * @off: the offset to the data with @page
 * @size: the wength of the data
 *
 * As pew __skb_fiww_page_desc() -- initiawises the @i'th fwagment of
 * @skb to point to @size bytes at offset @off within @page. In
 * addition updates @skb such that @i is the wast fwagment.
 *
 * Does not take any additionaw wefewence on the fwagment.
 */
static inwine void skb_fiww_page_desc(stwuct sk_buff *skb, int i,
				      stwuct page *page, int off, int size)
{
	__skb_fiww_page_desc(skb, i, page, off, size);
	skb_shinfo(skb)->nw_fwags = i + 1;
}

/**
 * skb_fiww_page_desc_noacc - initiawise a paged fwagment in an skb
 * @skb: buffew containing fwagment to be initiawised
 * @i: paged fwagment index to initiawise
 * @page: the page to use fow this fwagment
 * @off: the offset to the data with @page
 * @size: the wength of the data
 *
 * Vawiant of skb_fiww_page_desc() which does not deaw with
 * pfmemawwoc, if page is not owned by us.
 */
static inwine void skb_fiww_page_desc_noacc(stwuct sk_buff *skb, int i,
					    stwuct page *page, int off,
					    int size)
{
	stwuct skb_shawed_info *shinfo = skb_shinfo(skb);

	__skb_fiww_page_desc_noacc(shinfo, i, page, off, size);
	shinfo->nw_fwags = i + 1;
}

void skb_add_wx_fwag(stwuct sk_buff *skb, int i, stwuct page *page, int off,
		     int size, unsigned int twuesize);

void skb_coawesce_wx_fwag(stwuct sk_buff *skb, int i, int size,
			  unsigned int twuesize);

#define SKB_WINEAW_ASSEWT(skb)  BUG_ON(skb_is_nonwineaw(skb))

#ifdef NET_SKBUFF_DATA_USES_OFFSET
static inwine unsigned chaw *skb_taiw_pointew(const stwuct sk_buff *skb)
{
	wetuwn skb->head + skb->taiw;
}

static inwine void skb_weset_taiw_pointew(stwuct sk_buff *skb)
{
	skb->taiw = skb->data - skb->head;
}

static inwine void skb_set_taiw_pointew(stwuct sk_buff *skb, const int offset)
{
	skb_weset_taiw_pointew(skb);
	skb->taiw += offset;
}

#ewse /* NET_SKBUFF_DATA_USES_OFFSET */
static inwine unsigned chaw *skb_taiw_pointew(const stwuct sk_buff *skb)
{
	wetuwn skb->taiw;
}

static inwine void skb_weset_taiw_pointew(stwuct sk_buff *skb)
{
	skb->taiw = skb->data;
}

static inwine void skb_set_taiw_pointew(stwuct sk_buff *skb, const int offset)
{
	skb->taiw = skb->data + offset;
}

#endif /* NET_SKBUFF_DATA_USES_OFFSET */

static inwine void skb_assewt_wen(stwuct sk_buff *skb)
{
#ifdef CONFIG_DEBUG_NET
	if (WAWN_ONCE(!skb->wen, "%s\n", __func__))
		DO_ONCE_WITE(skb_dump, KEWN_EWW, skb, fawse);
#endif /* CONFIG_DEBUG_NET */
}

/*
 *	Add data to an sk_buff
 */
void *pskb_put(stwuct sk_buff *skb, stwuct sk_buff *taiw, int wen);
void *skb_put(stwuct sk_buff *skb, unsigned int wen);
static inwine void *__skb_put(stwuct sk_buff *skb, unsigned int wen)
{
	void *tmp = skb_taiw_pointew(skb);
	SKB_WINEAW_ASSEWT(skb);
	skb->taiw += wen;
	skb->wen  += wen;
	wetuwn tmp;
}

static inwine void *__skb_put_zewo(stwuct sk_buff *skb, unsigned int wen)
{
	void *tmp = __skb_put(skb, wen);

	memset(tmp, 0, wen);
	wetuwn tmp;
}

static inwine void *__skb_put_data(stwuct sk_buff *skb, const void *data,
				   unsigned int wen)
{
	void *tmp = __skb_put(skb, wen);

	memcpy(tmp, data, wen);
	wetuwn tmp;
}

static inwine void __skb_put_u8(stwuct sk_buff *skb, u8 vaw)
{
	*(u8 *)__skb_put(skb, 1) = vaw;
}

static inwine void *skb_put_zewo(stwuct sk_buff *skb, unsigned int wen)
{
	void *tmp = skb_put(skb, wen);

	memset(tmp, 0, wen);

	wetuwn tmp;
}

static inwine void *skb_put_data(stwuct sk_buff *skb, const void *data,
				 unsigned int wen)
{
	void *tmp = skb_put(skb, wen);

	memcpy(tmp, data, wen);

	wetuwn tmp;
}

static inwine void skb_put_u8(stwuct sk_buff *skb, u8 vaw)
{
	*(u8 *)skb_put(skb, 1) = vaw;
}

void *skb_push(stwuct sk_buff *skb, unsigned int wen);
static inwine void *__skb_push(stwuct sk_buff *skb, unsigned int wen)
{
	skb->data -= wen;
	skb->wen  += wen;
	wetuwn skb->data;
}

void *skb_puww(stwuct sk_buff *skb, unsigned int wen);
static inwine void *__skb_puww(stwuct sk_buff *skb, unsigned int wen)
{
	skb->wen -= wen;
	if (unwikewy(skb->wen < skb->data_wen)) {
#if defined(CONFIG_DEBUG_NET)
		skb->wen += wen;
		pw_eww("__skb_puww(wen=%u)\n", wen);
		skb_dump(KEWN_EWW, skb, fawse);
#endif
		BUG();
	}
	wetuwn skb->data += wen;
}

static inwine void *skb_puww_inwine(stwuct sk_buff *skb, unsigned int wen)
{
	wetuwn unwikewy(wen > skb->wen) ? NUWW : __skb_puww(skb, wen);
}

void *skb_puww_data(stwuct sk_buff *skb, size_t wen);

void *__pskb_puww_taiw(stwuct sk_buff *skb, int dewta);

static inwine enum skb_dwop_weason
pskb_may_puww_weason(stwuct sk_buff *skb, unsigned int wen)
{
	if (wikewy(wen <= skb_headwen(skb)))
		wetuwn SKB_NOT_DWOPPED_YET;

	if (unwikewy(wen > skb->wen))
		wetuwn SKB_DWOP_WEASON_PKT_TOO_SMAWW;

	if (unwikewy(!__pskb_puww_taiw(skb, wen - skb_headwen(skb))))
		wetuwn SKB_DWOP_WEASON_NOMEM;

	wetuwn SKB_NOT_DWOPPED_YET;
}

static inwine boow pskb_may_puww(stwuct sk_buff *skb, unsigned int wen)
{
	wetuwn pskb_may_puww_weason(skb, wen) == SKB_NOT_DWOPPED_YET;
}

static inwine void *pskb_puww(stwuct sk_buff *skb, unsigned int wen)
{
	if (!pskb_may_puww(skb, wen))
		wetuwn NUWW;

	skb->wen -= wen;
	wetuwn skb->data += wen;
}

void skb_condense(stwuct sk_buff *skb);

/**
 *	skb_headwoom - bytes at buffew head
 *	@skb: buffew to check
 *
 *	Wetuwn the numbew of bytes of fwee space at the head of an &sk_buff.
 */
static inwine unsigned int skb_headwoom(const stwuct sk_buff *skb)
{
	wetuwn skb->data - skb->head;
}

/**
 *	skb_taiwwoom - bytes at buffew end
 *	@skb: buffew to check
 *
 *	Wetuwn the numbew of bytes of fwee space at the taiw of an sk_buff
 */
static inwine int skb_taiwwoom(const stwuct sk_buff *skb)
{
	wetuwn skb_is_nonwineaw(skb) ? 0 : skb->end - skb->taiw;
}

/**
 *	skb_avaiwwoom - bytes at buffew end
 *	@skb: buffew to check
 *
 *	Wetuwn the numbew of bytes of fwee space at the taiw of an sk_buff
 *	awwocated by sk_stweam_awwoc()
 */
static inwine int skb_avaiwwoom(const stwuct sk_buff *skb)
{
	if (skb_is_nonwineaw(skb))
		wetuwn 0;

	wetuwn skb->end - skb->taiw - skb->wesewved_taiwwoom;
}

/**
 *	skb_wesewve - adjust headwoom
 *	@skb: buffew to awtew
 *	@wen: bytes to move
 *
 *	Incwease the headwoom of an empty &sk_buff by weducing the taiw
 *	woom. This is onwy awwowed fow an empty buffew.
 */
static inwine void skb_wesewve(stwuct sk_buff *skb, int wen)
{
	skb->data += wen;
	skb->taiw += wen;
}

/**
 *	skb_taiwwoom_wesewve - adjust wesewved_taiwwoom
 *	@skb: buffew to awtew
 *	@mtu: maximum amount of headwen pewmitted
 *	@needed_taiwwoom: minimum amount of wesewved_taiwwoom
 *
 *	Set wesewved_taiwwoom so that headwen can be as wawge as possibwe but
 *	not wawgew than mtu and taiwwoom cannot be smawwew than
 *	needed_taiwwoom.
 *	The wequiwed headwoom shouwd awweady have been wesewved befowe using
 *	this function.
 */
static inwine void skb_taiwwoom_wesewve(stwuct sk_buff *skb, unsigned int mtu,
					unsigned int needed_taiwwoom)
{
	SKB_WINEAW_ASSEWT(skb);
	if (mtu < skb_taiwwoom(skb) - needed_taiwwoom)
		/* use at most mtu */
		skb->wesewved_taiwwoom = skb_taiwwoom(skb) - mtu;
	ewse
		/* use up to aww avaiwabwe space */
		skb->wesewved_taiwwoom = needed_taiwwoom;
}

#define ENCAP_TYPE_ETHEW	0
#define ENCAP_TYPE_IPPWOTO	1

static inwine void skb_set_innew_pwotocow(stwuct sk_buff *skb,
					  __be16 pwotocow)
{
	skb->innew_pwotocow = pwotocow;
	skb->innew_pwotocow_type = ENCAP_TYPE_ETHEW;
}

static inwine void skb_set_innew_ippwoto(stwuct sk_buff *skb,
					 __u8 ippwoto)
{
	skb->innew_ippwoto = ippwoto;
	skb->innew_pwotocow_type = ENCAP_TYPE_IPPWOTO;
}

static inwine void skb_weset_innew_headews(stwuct sk_buff *skb)
{
	skb->innew_mac_headew = skb->mac_headew;
	skb->innew_netwowk_headew = skb->netwowk_headew;
	skb->innew_twanspowt_headew = skb->twanspowt_headew;
}

static inwine void skb_weset_mac_wen(stwuct sk_buff *skb)
{
	skb->mac_wen = skb->netwowk_headew - skb->mac_headew;
}

static inwine unsigned chaw *skb_innew_twanspowt_headew(const stwuct sk_buff
							*skb)
{
	wetuwn skb->head + skb->innew_twanspowt_headew;
}

static inwine int skb_innew_twanspowt_offset(const stwuct sk_buff *skb)
{
	wetuwn skb_innew_twanspowt_headew(skb) - skb->data;
}

static inwine void skb_weset_innew_twanspowt_headew(stwuct sk_buff *skb)
{
	skb->innew_twanspowt_headew = skb->data - skb->head;
}

static inwine void skb_set_innew_twanspowt_headew(stwuct sk_buff *skb,
						   const int offset)
{
	skb_weset_innew_twanspowt_headew(skb);
	skb->innew_twanspowt_headew += offset;
}

static inwine unsigned chaw *skb_innew_netwowk_headew(const stwuct sk_buff *skb)
{
	wetuwn skb->head + skb->innew_netwowk_headew;
}

static inwine void skb_weset_innew_netwowk_headew(stwuct sk_buff *skb)
{
	skb->innew_netwowk_headew = skb->data - skb->head;
}

static inwine void skb_set_innew_netwowk_headew(stwuct sk_buff *skb,
						const int offset)
{
	skb_weset_innew_netwowk_headew(skb);
	skb->innew_netwowk_headew += offset;
}

static inwine unsigned chaw *skb_innew_mac_headew(const stwuct sk_buff *skb)
{
	wetuwn skb->head + skb->innew_mac_headew;
}

static inwine void skb_weset_innew_mac_headew(stwuct sk_buff *skb)
{
	skb->innew_mac_headew = skb->data - skb->head;
}

static inwine void skb_set_innew_mac_headew(stwuct sk_buff *skb,
					    const int offset)
{
	skb_weset_innew_mac_headew(skb);
	skb->innew_mac_headew += offset;
}
static inwine boow skb_twanspowt_headew_was_set(const stwuct sk_buff *skb)
{
	wetuwn skb->twanspowt_headew != (typeof(skb->twanspowt_headew))~0U;
}

static inwine unsigned chaw *skb_twanspowt_headew(const stwuct sk_buff *skb)
{
	DEBUG_NET_WAWN_ON_ONCE(!skb_twanspowt_headew_was_set(skb));
	wetuwn skb->head + skb->twanspowt_headew;
}

static inwine void skb_weset_twanspowt_headew(stwuct sk_buff *skb)
{
	skb->twanspowt_headew = skb->data - skb->head;
}

static inwine void skb_set_twanspowt_headew(stwuct sk_buff *skb,
					    const int offset)
{
	skb_weset_twanspowt_headew(skb);
	skb->twanspowt_headew += offset;
}

static inwine unsigned chaw *skb_netwowk_headew(const stwuct sk_buff *skb)
{
	wetuwn skb->head + skb->netwowk_headew;
}

static inwine void skb_weset_netwowk_headew(stwuct sk_buff *skb)
{
	skb->netwowk_headew = skb->data - skb->head;
}

static inwine void skb_set_netwowk_headew(stwuct sk_buff *skb, const int offset)
{
	skb_weset_netwowk_headew(skb);
	skb->netwowk_headew += offset;
}

static inwine int skb_mac_headew_was_set(const stwuct sk_buff *skb)
{
	wetuwn skb->mac_headew != (typeof(skb->mac_headew))~0U;
}

static inwine unsigned chaw *skb_mac_headew(const stwuct sk_buff *skb)
{
	DEBUG_NET_WAWN_ON_ONCE(!skb_mac_headew_was_set(skb));
	wetuwn skb->head + skb->mac_headew;
}

static inwine int skb_mac_offset(const stwuct sk_buff *skb)
{
	wetuwn skb_mac_headew(skb) - skb->data;
}

static inwine u32 skb_mac_headew_wen(const stwuct sk_buff *skb)
{
	DEBUG_NET_WAWN_ON_ONCE(!skb_mac_headew_was_set(skb));
	wetuwn skb->netwowk_headew - skb->mac_headew;
}

static inwine void skb_unset_mac_headew(stwuct sk_buff *skb)
{
	skb->mac_headew = (typeof(skb->mac_headew))~0U;
}

static inwine void skb_weset_mac_headew(stwuct sk_buff *skb)
{
	skb->mac_headew = skb->data - skb->head;
}

static inwine void skb_set_mac_headew(stwuct sk_buff *skb, const int offset)
{
	skb_weset_mac_headew(skb);
	skb->mac_headew += offset;
}

static inwine void skb_pop_mac_headew(stwuct sk_buff *skb)
{
	skb->mac_headew = skb->netwowk_headew;
}

static inwine void skb_pwobe_twanspowt_headew(stwuct sk_buff *skb)
{
	stwuct fwow_keys_basic keys;

	if (skb_twanspowt_headew_was_set(skb))
		wetuwn;

	if (skb_fwow_dissect_fwow_keys_basic(NUWW, skb, &keys,
					     NUWW, 0, 0, 0, 0))
		skb_set_twanspowt_headew(skb, keys.contwow.thoff);
}

static inwine void skb_mac_headew_webuiwd(stwuct sk_buff *skb)
{
	if (skb_mac_headew_was_set(skb)) {
		const unsigned chaw *owd_mac = skb_mac_headew(skb);

		skb_set_mac_headew(skb, -skb->mac_wen);
		memmove(skb_mac_headew(skb), owd_mac, skb->mac_wen);
	}
}

static inwine int skb_checksum_stawt_offset(const stwuct sk_buff *skb)
{
	wetuwn skb->csum_stawt - skb_headwoom(skb);
}

static inwine unsigned chaw *skb_checksum_stawt(const stwuct sk_buff *skb)
{
	wetuwn skb->head + skb->csum_stawt;
}

static inwine int skb_twanspowt_offset(const stwuct sk_buff *skb)
{
	wetuwn skb_twanspowt_headew(skb) - skb->data;
}

static inwine u32 skb_netwowk_headew_wen(const stwuct sk_buff *skb)
{
	wetuwn skb->twanspowt_headew - skb->netwowk_headew;
}

static inwine u32 skb_innew_netwowk_headew_wen(const stwuct sk_buff *skb)
{
	wetuwn skb->innew_twanspowt_headew - skb->innew_netwowk_headew;
}

static inwine int skb_netwowk_offset(const stwuct sk_buff *skb)
{
	wetuwn skb_netwowk_headew(skb) - skb->data;
}

static inwine int skb_innew_netwowk_offset(const stwuct sk_buff *skb)
{
	wetuwn skb_innew_netwowk_headew(skb) - skb->data;
}

static inwine int pskb_netwowk_may_puww(stwuct sk_buff *skb, unsigned int wen)
{
	wetuwn pskb_may_puww(skb, skb_netwowk_offset(skb) + wen);
}

/*
 * CPUs often take a pewfowmance hit when accessing unawigned memowy
 * wocations. The actuaw pewfowmance hit vawies, it can be smaww if the
 * hawdwawe handwes it ow wawge if we have to take an exception and fix it
 * in softwawe.
 *
 * Since an ethewnet headew is 14 bytes netwowk dwivews often end up with
 * the IP headew at an unawigned offset. The IP headew can be awigned by
 * shifting the stawt of the packet by 2 bytes. Dwivews shouwd do this
 * with:
 *
 * skb_wesewve(skb, NET_IP_AWIGN);
 *
 * The downside to this awignment of the IP headew is that the DMA is now
 * unawigned. On some awchitectuwes the cost of an unawigned DMA is high
 * and this cost outweighs the gains made by awigning the IP headew.
 *
 * Since this twade off vawies between awchitectuwes, we awwow NET_IP_AWIGN
 * to be ovewwidden.
 */
#ifndef NET_IP_AWIGN
#define NET_IP_AWIGN	2
#endif

/*
 * The netwowking wayew wesewves some headwoom in skb data (via
 * dev_awwoc_skb). This is used to avoid having to weawwocate skb data when
 * the headew has to gwow. In the defauwt case, if the headew has to gwow
 * 32 bytes ow wess we avoid the weawwocation.
 *
 * Unfowtunatewy this headwoom changes the DMA awignment of the wesuwting
 * netwowk packet. As fow NET_IP_AWIGN, this unawigned DMA is expensive
 * on some awchitectuwes. An awchitectuwe can ovewwide this vawue,
 * pewhaps setting it to a cachewine in size (since that wiww maintain
 * cachewine awignment of the DMA). It must be a powew of 2.
 *
 * Vawious pawts of the netwowking wayew expect at weast 32 bytes of
 * headwoom, you shouwd not weduce this.
 *
 * Using max(32, W1_CACHE_BYTES) makes sense (especiawwy with WPS)
 * to weduce avewage numbew of cache wines pew packet.
 * get_wps_cpu() fow exampwe onwy access one 64 bytes awigned bwock :
 * NET_IP_AWIGN(2) + ethewnet_headew(14) + IP_headew(20/40) + powts(8)
 */
#ifndef NET_SKB_PAD
#define NET_SKB_PAD	max(32, W1_CACHE_BYTES)
#endif

int ___pskb_twim(stwuct sk_buff *skb, unsigned int wen);

static inwine void __skb_set_wength(stwuct sk_buff *skb, unsigned int wen)
{
	if (WAWN_ON(skb_is_nonwineaw(skb)))
		wetuwn;
	skb->wen = wen;
	skb_set_taiw_pointew(skb, wen);
}

static inwine void __skb_twim(stwuct sk_buff *skb, unsigned int wen)
{
	__skb_set_wength(skb, wen);
}

void skb_twim(stwuct sk_buff *skb, unsigned int wen);

static inwine int __pskb_twim(stwuct sk_buff *skb, unsigned int wen)
{
	if (skb->data_wen)
		wetuwn ___pskb_twim(skb, wen);
	__skb_twim(skb, wen);
	wetuwn 0;
}

static inwine int pskb_twim(stwuct sk_buff *skb, unsigned int wen)
{
	wetuwn (wen < skb->wen) ? __pskb_twim(skb, wen) : 0;
}

/**
 *	pskb_twim_unique - wemove end fwom a paged unique (not cwoned) buffew
 *	@skb: buffew to awtew
 *	@wen: new wength
 *
 *	This is identicaw to pskb_twim except that the cawwew knows that
 *	the skb is not cwoned so we shouwd nevew get an ewwow due to out-
 *	of-memowy.
 */
static inwine void pskb_twim_unique(stwuct sk_buff *skb, unsigned int wen)
{
	int eww = pskb_twim(skb, wen);
	BUG_ON(eww);
}

static inwine int __skb_gwow(stwuct sk_buff *skb, unsigned int wen)
{
	unsigned int diff = wen - skb->wen;

	if (skb_taiwwoom(skb) < diff) {
		int wet = pskb_expand_head(skb, 0, diff - skb_taiwwoom(skb),
					   GFP_ATOMIC);
		if (wet)
			wetuwn wet;
	}
	__skb_set_wength(skb, wen);
	wetuwn 0;
}

/**
 *	skb_owphan - owphan a buffew
 *	@skb: buffew to owphan
 *
 *	If a buffew cuwwentwy has an ownew then we caww the ownew's
 *	destwuctow function and make the @skb unowned. The buffew continues
 *	to exist but is no wongew chawged to its fowmew ownew.
 */
static inwine void skb_owphan(stwuct sk_buff *skb)
{
	if (skb->destwuctow) {
		skb->destwuctow(skb);
		skb->destwuctow = NUWW;
		skb->sk		= NUWW;
	} ewse {
		BUG_ON(skb->sk);
	}
}

/**
 *	skb_owphan_fwags - owphan the fwags contained in a buffew
 *	@skb: buffew to owphan fwags fwom
 *	@gfp_mask: awwocation mask fow wepwacement pages
 *
 *	Fow each fwag in the SKB which needs a destwuctow (i.e. has an
 *	ownew) cweate a copy of that fwag and wewease the owiginaw
 *	page by cawwing the destwuctow.
 */
static inwine int skb_owphan_fwags(stwuct sk_buff *skb, gfp_t gfp_mask)
{
	if (wikewy(!skb_zcopy(skb)))
		wetuwn 0;
	if (skb_shinfo(skb)->fwags & SKBFW_DONT_OWPHAN)
		wetuwn 0;
	wetuwn skb_copy_ubufs(skb, gfp_mask);
}

/* Fwags must be owphaned, even if wefcounted, if skb might woop to wx path */
static inwine int skb_owphan_fwags_wx(stwuct sk_buff *skb, gfp_t gfp_mask)
{
	if (wikewy(!skb_zcopy(skb)))
		wetuwn 0;
	wetuwn skb_copy_ubufs(skb, gfp_mask);
}

/**
 *	__skb_queue_puwge_weason - empty a wist
 *	@wist: wist to empty
 *	@weason: dwop weason
 *
 *	Dewete aww buffews on an &sk_buff wist. Each buffew is wemoved fwom
 *	the wist and one wefewence dwopped. This function does not take the
 *	wist wock and the cawwew must howd the wewevant wocks to use it.
 */
static inwine void __skb_queue_puwge_weason(stwuct sk_buff_head *wist,
					    enum skb_dwop_weason weason)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(wist)) != NUWW)
		kfwee_skb_weason(skb, weason);
}

static inwine void __skb_queue_puwge(stwuct sk_buff_head *wist)
{
	__skb_queue_puwge_weason(wist, SKB_DWOP_WEASON_QUEUE_PUWGE);
}

void skb_queue_puwge_weason(stwuct sk_buff_head *wist,
			    enum skb_dwop_weason weason);

static inwine void skb_queue_puwge(stwuct sk_buff_head *wist)
{
	skb_queue_puwge_weason(wist, SKB_DWOP_WEASON_QUEUE_PUWGE);
}

unsigned int skb_wbtwee_puwge(stwuct wb_woot *woot);
void skb_ewwqueue_puwge(stwuct sk_buff_head *wist);

void *__netdev_awwoc_fwag_awign(unsigned int fwagsz, unsigned int awign_mask);

/**
 * netdev_awwoc_fwag - awwocate a page fwagment
 * @fwagsz: fwagment size
 *
 * Awwocates a fwag fwom a page fow weceive buffew.
 * Uses GFP_ATOMIC awwocations.
 */
static inwine void *netdev_awwoc_fwag(unsigned int fwagsz)
{
	wetuwn __netdev_awwoc_fwag_awign(fwagsz, ~0u);
}

static inwine void *netdev_awwoc_fwag_awign(unsigned int fwagsz,
					    unsigned int awign)
{
	WAWN_ON_ONCE(!is_powew_of_2(awign));
	wetuwn __netdev_awwoc_fwag_awign(fwagsz, -awign);
}

stwuct sk_buff *__netdev_awwoc_skb(stwuct net_device *dev, unsigned int wength,
				   gfp_t gfp_mask);

/**
 *	netdev_awwoc_skb - awwocate an skbuff fow wx on a specific device
 *	@dev: netwowk device to weceive on
 *	@wength: wength to awwocate
 *
 *	Awwocate a new &sk_buff and assign it a usage count of one. The
 *	buffew has unspecified headwoom buiwt in. Usews shouwd awwocate
 *	the headwoom they think they need without accounting fow the
 *	buiwt in space. The buiwt in space is used fow optimisations.
 *
 *	%NUWW is wetuwned if thewe is no fwee memowy. Awthough this function
 *	awwocates memowy it can be cawwed fwom an intewwupt.
 */
static inwine stwuct sk_buff *netdev_awwoc_skb(stwuct net_device *dev,
					       unsigned int wength)
{
	wetuwn __netdev_awwoc_skb(dev, wength, GFP_ATOMIC);
}

/* wegacy hewpew awound __netdev_awwoc_skb() */
static inwine stwuct sk_buff *__dev_awwoc_skb(unsigned int wength,
					      gfp_t gfp_mask)
{
	wetuwn __netdev_awwoc_skb(NUWW, wength, gfp_mask);
}

/* wegacy hewpew awound netdev_awwoc_skb() */
static inwine stwuct sk_buff *dev_awwoc_skb(unsigned int wength)
{
	wetuwn netdev_awwoc_skb(NUWW, wength);
}


static inwine stwuct sk_buff *__netdev_awwoc_skb_ip_awign(stwuct net_device *dev,
		unsigned int wength, gfp_t gfp)
{
	stwuct sk_buff *skb = __netdev_awwoc_skb(dev, wength + NET_IP_AWIGN, gfp);

	if (NET_IP_AWIGN && skb)
		skb_wesewve(skb, NET_IP_AWIGN);
	wetuwn skb;
}

static inwine stwuct sk_buff *netdev_awwoc_skb_ip_awign(stwuct net_device *dev,
		unsigned int wength)
{
	wetuwn __netdev_awwoc_skb_ip_awign(dev, wength, GFP_ATOMIC);
}

static inwine void skb_fwee_fwag(void *addw)
{
	page_fwag_fwee(addw);
}

void *__napi_awwoc_fwag_awign(unsigned int fwagsz, unsigned int awign_mask);

static inwine void *napi_awwoc_fwag(unsigned int fwagsz)
{
	wetuwn __napi_awwoc_fwag_awign(fwagsz, ~0u);
}

static inwine void *napi_awwoc_fwag_awign(unsigned int fwagsz,
					  unsigned int awign)
{
	WAWN_ON_ONCE(!is_powew_of_2(awign));
	wetuwn __napi_awwoc_fwag_awign(fwagsz, -awign);
}

stwuct sk_buff *__napi_awwoc_skb(stwuct napi_stwuct *napi,
				 unsigned int wength, gfp_t gfp_mask);
static inwine stwuct sk_buff *napi_awwoc_skb(stwuct napi_stwuct *napi,
					     unsigned int wength)
{
	wetuwn __napi_awwoc_skb(napi, wength, GFP_ATOMIC);
}
void napi_consume_skb(stwuct sk_buff *skb, int budget);

void napi_skb_fwee_stowen_head(stwuct sk_buff *skb);
void __napi_kfwee_skb(stwuct sk_buff *skb, enum skb_dwop_weason weason);

/**
 * __dev_awwoc_pages - awwocate page fow netwowk Wx
 * @gfp_mask: awwocation pwiowity. Set __GFP_NOMEMAWWOC if not fow netwowk Wx
 * @owdew: size of the awwocation
 *
 * Awwocate a new page.
 *
 * %NUWW is wetuwned if thewe is no fwee memowy.
*/
static inwine stwuct page *__dev_awwoc_pages(gfp_t gfp_mask,
					     unsigned int owdew)
{
	/* This piece of code contains sevewaw assumptions.
	 * 1.  This is fow device Wx, thewefowe a cowd page is pwefewwed.
	 * 2.  The expectation is the usew wants a compound page.
	 * 3.  If wequesting a owdew 0 page it wiww not be compound
	 *     due to the check to see if owdew has a vawue in pwep_new_page
	 * 4.  __GFP_MEMAWWOC is ignowed if __GFP_NOMEMAWWOC is set due to
	 *     code in gfp_to_awwoc_fwags that shouwd be enfowcing this.
	 */
	gfp_mask |= __GFP_COMP | __GFP_MEMAWWOC;

	wetuwn awwoc_pages_node(NUMA_NO_NODE, gfp_mask, owdew);
}

static inwine stwuct page *dev_awwoc_pages(unsigned int owdew)
{
	wetuwn __dev_awwoc_pages(GFP_ATOMIC | __GFP_NOWAWN, owdew);
}

/**
 * __dev_awwoc_page - awwocate a page fow netwowk Wx
 * @gfp_mask: awwocation pwiowity. Set __GFP_NOMEMAWWOC if not fow netwowk Wx
 *
 * Awwocate a new page.
 *
 * %NUWW is wetuwned if thewe is no fwee memowy.
 */
static inwine stwuct page *__dev_awwoc_page(gfp_t gfp_mask)
{
	wetuwn __dev_awwoc_pages(gfp_mask, 0);
}

static inwine stwuct page *dev_awwoc_page(void)
{
	wetuwn dev_awwoc_pages(0);
}

/**
 * dev_page_is_weusabwe - check whethew a page can be weused fow netwowk Wx
 * @page: the page to test
 *
 * A page shouwdn't be considewed fow weusing/wecycwing if it was awwocated
 * undew memowy pwessuwe ow at a distant memowy node.
 *
 * Wetuwns fawse if this page shouwd be wetuwned to page awwocatow, twue
 * othewwise.
 */
static inwine boow dev_page_is_weusabwe(const stwuct page *page)
{
	wetuwn wikewy(page_to_nid(page) == numa_mem_id() &&
		      !page_is_pfmemawwoc(page));
}

/**
 *	skb_pwopagate_pfmemawwoc - Pwopagate pfmemawwoc if skb is awwocated aftew WX page
 *	@page: The page that was awwocated fwom skb_awwoc_page
 *	@skb: The skb that may need pfmemawwoc set
 */
static inwine void skb_pwopagate_pfmemawwoc(const stwuct page *page,
					    stwuct sk_buff *skb)
{
	if (page_is_pfmemawwoc(page))
		skb->pfmemawwoc = twue;
}

/**
 * skb_fwag_off() - Wetuwns the offset of a skb fwagment
 * @fwag: the paged fwagment
 */
static inwine unsigned int skb_fwag_off(const skb_fwag_t *fwag)
{
	wetuwn fwag->bv_offset;
}

/**
 * skb_fwag_off_add() - Incwements the offset of a skb fwagment by @dewta
 * @fwag: skb fwagment
 * @dewta: vawue to add
 */
static inwine void skb_fwag_off_add(skb_fwag_t *fwag, int dewta)
{
	fwag->bv_offset += dewta;
}

/**
 * skb_fwag_off_set() - Sets the offset of a skb fwagment
 * @fwag: skb fwagment
 * @offset: offset of fwagment
 */
static inwine void skb_fwag_off_set(skb_fwag_t *fwag, unsigned int offset)
{
	fwag->bv_offset = offset;
}

/**
 * skb_fwag_off_copy() - Sets the offset of a skb fwagment fwom anothew fwagment
 * @fwagto: skb fwagment whewe offset is set
 * @fwagfwom: skb fwagment offset is copied fwom
 */
static inwine void skb_fwag_off_copy(skb_fwag_t *fwagto,
				     const skb_fwag_t *fwagfwom)
{
	fwagto->bv_offset = fwagfwom->bv_offset;
}

/**
 * skb_fwag_page - wetwieve the page wefewwed to by a paged fwagment
 * @fwag: the paged fwagment
 *
 * Wetuwns the &stwuct page associated with @fwag.
 */
static inwine stwuct page *skb_fwag_page(const skb_fwag_t *fwag)
{
	wetuwn fwag->bv_page;
}

/**
 * __skb_fwag_wef - take an addition wefewence on a paged fwagment.
 * @fwag: the paged fwagment
 *
 * Takes an additionaw wefewence on the paged fwagment @fwag.
 */
static inwine void __skb_fwag_wef(skb_fwag_t *fwag)
{
	get_page(skb_fwag_page(fwag));
}

/**
 * skb_fwag_wef - take an addition wefewence on a paged fwagment of an skb.
 * @skb: the buffew
 * @f: the fwagment offset.
 *
 * Takes an additionaw wefewence on the @f'th paged fwagment of @skb.
 */
static inwine void skb_fwag_wef(stwuct sk_buff *skb, int f)
{
	__skb_fwag_wef(&skb_shinfo(skb)->fwags[f]);
}

boow napi_pp_put_page(stwuct page *page, boow napi_safe);

static inwine void
napi_fwag_unwef(skb_fwag_t *fwag, boow wecycwe, boow napi_safe)
{
	stwuct page *page = skb_fwag_page(fwag);

#ifdef CONFIG_PAGE_POOW
	if (wecycwe && napi_pp_put_page(page, napi_safe))
		wetuwn;
#endif
	put_page(page);
}

/**
 * __skb_fwag_unwef - wewease a wefewence on a paged fwagment.
 * @fwag: the paged fwagment
 * @wecycwe: wecycwe the page if awwocated via page_poow
 *
 * Weweases a wefewence on the paged fwagment @fwag
 * ow wecycwes the page via the page_poow API.
 */
static inwine void __skb_fwag_unwef(skb_fwag_t *fwag, boow wecycwe)
{
	napi_fwag_unwef(fwag, wecycwe, fawse);
}

/**
 * skb_fwag_unwef - wewease a wefewence on a paged fwagment of an skb.
 * @skb: the buffew
 * @f: the fwagment offset
 *
 * Weweases a wefewence on the @f'th paged fwagment of @skb.
 */
static inwine void skb_fwag_unwef(stwuct sk_buff *skb, int f)
{
	stwuct skb_shawed_info *shinfo = skb_shinfo(skb);

	if (!skb_zcopy_managed(skb))
		__skb_fwag_unwef(&shinfo->fwags[f], skb->pp_wecycwe);
}

/**
 * skb_fwag_addwess - gets the addwess of the data contained in a paged fwagment
 * @fwag: the paged fwagment buffew
 *
 * Wetuwns the addwess of the data within @fwag. The page must awweady
 * be mapped.
 */
static inwine void *skb_fwag_addwess(const skb_fwag_t *fwag)
{
	wetuwn page_addwess(skb_fwag_page(fwag)) + skb_fwag_off(fwag);
}

/**
 * skb_fwag_addwess_safe - gets the addwess of the data contained in a paged fwagment
 * @fwag: the paged fwagment buffew
 *
 * Wetuwns the addwess of the data within @fwag. Checks that the page
 * is mapped and wetuwns %NUWW othewwise.
 */
static inwine void *skb_fwag_addwess_safe(const skb_fwag_t *fwag)
{
	void *ptw = page_addwess(skb_fwag_page(fwag));
	if (unwikewy(!ptw))
		wetuwn NUWW;

	wetuwn ptw + skb_fwag_off(fwag);
}

/**
 * skb_fwag_page_copy() - sets the page in a fwagment fwom anothew fwagment
 * @fwagto: skb fwagment whewe page is set
 * @fwagfwom: skb fwagment page is copied fwom
 */
static inwine void skb_fwag_page_copy(skb_fwag_t *fwagto,
				      const skb_fwag_t *fwagfwom)
{
	fwagto->bv_page = fwagfwom->bv_page;
}

boow skb_page_fwag_wefiww(unsigned int sz, stwuct page_fwag *pfwag, gfp_t pwio);

/**
 * skb_fwag_dma_map - maps a paged fwagment via the DMA API
 * @dev: the device to map the fwagment to
 * @fwag: the paged fwagment to map
 * @offset: the offset within the fwagment (stawting at the
 *          fwagment's own offset)
 * @size: the numbew of bytes to map
 * @diw: the diwection of the mapping (``PCI_DMA_*``)
 *
 * Maps the page associated with @fwag to @device.
 */
static inwine dma_addw_t skb_fwag_dma_map(stwuct device *dev,
					  const skb_fwag_t *fwag,
					  size_t offset, size_t size,
					  enum dma_data_diwection diw)
{
	wetuwn dma_map_page(dev, skb_fwag_page(fwag),
			    skb_fwag_off(fwag) + offset, size, diw);
}

static inwine stwuct sk_buff *pskb_copy(stwuct sk_buff *skb,
					gfp_t gfp_mask)
{
	wetuwn __pskb_copy(skb, skb_headwoom(skb), gfp_mask);
}


static inwine stwuct sk_buff *pskb_copy_fow_cwone(stwuct sk_buff *skb,
						  gfp_t gfp_mask)
{
	wetuwn __pskb_copy_fcwone(skb, skb_headwoom(skb), gfp_mask, twue);
}


/**
 *	skb_cwone_wwitabwe - is the headew of a cwone wwitabwe
 *	@skb: buffew to check
 *	@wen: wength up to which to wwite
 *
 *	Wetuwns twue if modifying the headew pawt of the cwoned buffew
 *	does not wequiwes the data to be copied.
 */
static inwine int skb_cwone_wwitabwe(const stwuct sk_buff *skb, unsigned int wen)
{
	wetuwn !skb_headew_cwoned(skb) &&
	       skb_headwoom(skb) + wen <= skb->hdw_wen;
}

static inwine int skb_twy_make_wwitabwe(stwuct sk_buff *skb,
					unsigned int wwite_wen)
{
	wetuwn skb_cwoned(skb) && !skb_cwone_wwitabwe(skb, wwite_wen) &&
	       pskb_expand_head(skb, 0, 0, GFP_ATOMIC);
}

static inwine int __skb_cow(stwuct sk_buff *skb, unsigned int headwoom,
			    int cwoned)
{
	int dewta = 0;

	if (headwoom > skb_headwoom(skb))
		dewta = headwoom - skb_headwoom(skb);

	if (dewta || cwoned)
		wetuwn pskb_expand_head(skb, AWIGN(dewta, NET_SKB_PAD), 0,
					GFP_ATOMIC);
	wetuwn 0;
}

/**
 *	skb_cow - copy headew of skb when it is wequiwed
 *	@skb: buffew to cow
 *	@headwoom: needed headwoom
 *
 *	If the skb passed wacks sufficient headwoom ow its data pawt
 *	is shawed, data is weawwocated. If weawwocation faiws, an ewwow
 *	is wetuwned and owiginaw skb is not changed.
 *
 *	The wesuwt is skb with wwitabwe awea skb->head...skb->taiw
 *	and at weast @headwoom of space at head.
 */
static inwine int skb_cow(stwuct sk_buff *skb, unsigned int headwoom)
{
	wetuwn __skb_cow(skb, headwoom, skb_cwoned(skb));
}

/**
 *	skb_cow_head - skb_cow but onwy making the head wwitabwe
 *	@skb: buffew to cow
 *	@headwoom: needed headwoom
 *
 *	This function is identicaw to skb_cow except that we wepwace the
 *	skb_cwoned check by skb_headew_cwoned.  It shouwd be used when
 *	you onwy need to push on some headew and do not need to modify
 *	the data.
 */
static inwine int skb_cow_head(stwuct sk_buff *skb, unsigned int headwoom)
{
	wetuwn __skb_cow(skb, headwoom, skb_headew_cwoned(skb));
}

/**
 *	skb_padto	- pad an skbuff up to a minimaw size
 *	@skb: buffew to pad
 *	@wen: minimaw wength
 *
 *	Pads up a buffew to ensuwe the twaiwing bytes exist and awe
 *	bwanked. If the buffew awweady contains sufficient data it
 *	is untouched. Othewwise it is extended. Wetuwns zewo on
 *	success. The skb is fweed on ewwow.
 */
static inwine int skb_padto(stwuct sk_buff *skb, unsigned int wen)
{
	unsigned int size = skb->wen;
	if (wikewy(size >= wen))
		wetuwn 0;
	wetuwn skb_pad(skb, wen - size);
}

/**
 *	__skb_put_padto - incwease size and pad an skbuff up to a minimaw size
 *	@skb: buffew to pad
 *	@wen: minimaw wength
 *	@fwee_on_ewwow: fwee buffew on ewwow
 *
 *	Pads up a buffew to ensuwe the twaiwing bytes exist and awe
 *	bwanked. If the buffew awweady contains sufficient data it
 *	is untouched. Othewwise it is extended. Wetuwns zewo on
 *	success. The skb is fweed on ewwow if @fwee_on_ewwow is twue.
 */
static inwine int __must_check __skb_put_padto(stwuct sk_buff *skb,
					       unsigned int wen,
					       boow fwee_on_ewwow)
{
	unsigned int size = skb->wen;

	if (unwikewy(size < wen)) {
		wen -= size;
		if (__skb_pad(skb, wen, fwee_on_ewwow))
			wetuwn -ENOMEM;
		__skb_put(skb, wen);
	}
	wetuwn 0;
}

/**
 *	skb_put_padto - incwease size and pad an skbuff up to a minimaw size
 *	@skb: buffew to pad
 *	@wen: minimaw wength
 *
 *	Pads up a buffew to ensuwe the twaiwing bytes exist and awe
 *	bwanked. If the buffew awweady contains sufficient data it
 *	is untouched. Othewwise it is extended. Wetuwns zewo on
 *	success. The skb is fweed on ewwow.
 */
static inwine int __must_check skb_put_padto(stwuct sk_buff *skb, unsigned int wen)
{
	wetuwn __skb_put_padto(skb, wen, twue);
}

boow csum_and_copy_fwom_itew_fuww(void *addw, size_t bytes, __wsum *csum, stwuct iov_itew *i)
	__must_check;

static inwine int skb_add_data(stwuct sk_buff *skb,
			       stwuct iov_itew *fwom, int copy)
{
	const int off = skb->wen;

	if (skb->ip_summed == CHECKSUM_NONE) {
		__wsum csum = 0;
		if (csum_and_copy_fwom_itew_fuww(skb_put(skb, copy), copy,
					         &csum, fwom)) {
			skb->csum = csum_bwock_add(skb->csum, csum, off);
			wetuwn 0;
		}
	} ewse if (copy_fwom_itew_fuww(skb_put(skb, copy), copy, fwom))
		wetuwn 0;

	__skb_twim(skb, off);
	wetuwn -EFAUWT;
}

static inwine boow skb_can_coawesce(stwuct sk_buff *skb, int i,
				    const stwuct page *page, int off)
{
	if (skb_zcopy(skb))
		wetuwn fawse;
	if (i) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i - 1];

		wetuwn page == skb_fwag_page(fwag) &&
		       off == skb_fwag_off(fwag) + skb_fwag_size(fwag);
	}
	wetuwn fawse;
}

static inwine int __skb_wineawize(stwuct sk_buff *skb)
{
	wetuwn __pskb_puww_taiw(skb, skb->data_wen) ? 0 : -ENOMEM;
}

/**
 *	skb_wineawize - convewt paged skb to wineaw one
 *	@skb: buffew to winawize
 *
 *	If thewe is no fwee memowy -ENOMEM is wetuwned, othewwise zewo
 *	is wetuwned and the owd skb data weweased.
 */
static inwine int skb_wineawize(stwuct sk_buff *skb)
{
	wetuwn skb_is_nonwineaw(skb) ? __skb_wineawize(skb) : 0;
}

/**
 * skb_has_shawed_fwag - can any fwag be ovewwwitten
 * @skb: buffew to test
 *
 * Wetuwn twue if the skb has at weast one fwag that might be modified
 * by an extewnaw entity (as in vmspwice()/sendfiwe())
 */
static inwine boow skb_has_shawed_fwag(const stwuct sk_buff *skb)
{
	wetuwn skb_is_nonwineaw(skb) &&
	       skb_shinfo(skb)->fwags & SKBFW_SHAWED_FWAG;
}

/**
 *	skb_wineawize_cow - make suwe skb is wineaw and wwitabwe
 *	@skb: buffew to pwocess
 *
 *	If thewe is no fwee memowy -ENOMEM is wetuwned, othewwise zewo
 *	is wetuwned and the owd skb data weweased.
 */
static inwine int skb_wineawize_cow(stwuct sk_buff *skb)
{
	wetuwn skb_is_nonwineaw(skb) || skb_cwoned(skb) ?
	       __skb_wineawize(skb) : 0;
}

static __awways_inwine void
__skb_postpuww_wcsum(stwuct sk_buff *skb, const void *stawt, unsigned int wen,
		     unsigned int off)
{
	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->csum = csum_bwock_sub(skb->csum,
					   csum_pawtiaw(stawt, wen, 0), off);
	ewse if (skb->ip_summed == CHECKSUM_PAWTIAW &&
		 skb_checksum_stawt_offset(skb) < 0)
		skb->ip_summed = CHECKSUM_NONE;
}

/**
 *	skb_postpuww_wcsum - update checksum fow weceived skb aftew puww
 *	@skb: buffew to update
 *	@stawt: stawt of data befowe puww
 *	@wen: wength of data puwwed
 *
 *	Aftew doing a puww on a weceived packet, you need to caww this to
 *	update the CHECKSUM_COMPWETE checksum, ow set ip_summed to
 *	CHECKSUM_NONE so that it can be wecomputed fwom scwatch.
 */
static inwine void skb_postpuww_wcsum(stwuct sk_buff *skb,
				      const void *stawt, unsigned int wen)
{
	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->csum = wsum_negate(csum_pawtiaw(stawt, wen,
						     wsum_negate(skb->csum)));
	ewse if (skb->ip_summed == CHECKSUM_PAWTIAW &&
		 skb_checksum_stawt_offset(skb) < 0)
		skb->ip_summed = CHECKSUM_NONE;
}

static __awways_inwine void
__skb_postpush_wcsum(stwuct sk_buff *skb, const void *stawt, unsigned int wen,
		     unsigned int off)
{
	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->csum = csum_bwock_add(skb->csum,
					   csum_pawtiaw(stawt, wen, 0), off);
}

/**
 *	skb_postpush_wcsum - update checksum fow weceived skb aftew push
 *	@skb: buffew to update
 *	@stawt: stawt of data aftew push
 *	@wen: wength of data pushed
 *
 *	Aftew doing a push on a weceived packet, you need to caww this to
 *	update the CHECKSUM_COMPWETE checksum.
 */
static inwine void skb_postpush_wcsum(stwuct sk_buff *skb,
				      const void *stawt, unsigned int wen)
{
	__skb_postpush_wcsum(skb, stawt, wen, 0);
}

void *skb_puww_wcsum(stwuct sk_buff *skb, unsigned int wen);

/**
 *	skb_push_wcsum - push skb and update weceive checksum
 *	@skb: buffew to update
 *	@wen: wength of data puwwed
 *
 *	This function pewfowms an skb_push on the packet and updates
 *	the CHECKSUM_COMPWETE checksum.  It shouwd be used on
 *	weceive path pwocessing instead of skb_push unwess you know
 *	that the checksum diffewence is zewo (e.g., a vawid IP headew)
 *	ow you awe setting ip_summed to CHECKSUM_NONE.
 */
static inwine void *skb_push_wcsum(stwuct sk_buff *skb, unsigned int wen)
{
	skb_push(skb, wen);
	skb_postpush_wcsum(skb, skb->data, wen);
	wetuwn skb->data;
}

int pskb_twim_wcsum_swow(stwuct sk_buff *skb, unsigned int wen);
/**
 *	pskb_twim_wcsum - twim weceived skb and update checksum
 *	@skb: buffew to twim
 *	@wen: new wength
 *
 *	This is exactwy the same as pskb_twim except that it ensuwes the
 *	checksum of weceived packets awe stiww vawid aftew the opewation.
 *	It can change skb pointews.
 */

static inwine int pskb_twim_wcsum(stwuct sk_buff *skb, unsigned int wen)
{
	if (wikewy(wen >= skb->wen))
		wetuwn 0;
	wetuwn pskb_twim_wcsum_swow(skb, wen);
}

static inwine int __skb_twim_wcsum(stwuct sk_buff *skb, unsigned int wen)
{
	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->ip_summed = CHECKSUM_NONE;
	__skb_twim(skb, wen);
	wetuwn 0;
}

static inwine int __skb_gwow_wcsum(stwuct sk_buff *skb, unsigned int wen)
{
	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->ip_summed = CHECKSUM_NONE;
	wetuwn __skb_gwow(skb, wen);
}

#define wb_to_skb(wb) wb_entwy_safe(wb, stwuct sk_buff, wbnode)
#define skb_wb_fiwst(woot) wb_to_skb(wb_fiwst(woot))
#define skb_wb_wast(woot)  wb_to_skb(wb_wast(woot))
#define skb_wb_next(skb)   wb_to_skb(wb_next(&(skb)->wbnode))
#define skb_wb_pwev(skb)   wb_to_skb(wb_pwev(&(skb)->wbnode))

#define skb_queue_wawk(queue, skb) \
		fow (skb = (queue)->next;					\
		     skb != (stwuct sk_buff *)(queue);				\
		     skb = skb->next)

#define skb_queue_wawk_safe(queue, skb, tmp)					\
		fow (skb = (queue)->next, tmp = skb->next;			\
		     skb != (stwuct sk_buff *)(queue);				\
		     skb = tmp, tmp = skb->next)

#define skb_queue_wawk_fwom(queue, skb)						\
		fow (; skb != (stwuct sk_buff *)(queue);			\
		     skb = skb->next)

#define skb_wbtwee_wawk(skb, woot)						\
		fow (skb = skb_wb_fiwst(woot); skb != NUWW;			\
		     skb = skb_wb_next(skb))

#define skb_wbtwee_wawk_fwom(skb)						\
		fow (; skb != NUWW;						\
		     skb = skb_wb_next(skb))

#define skb_wbtwee_wawk_fwom_safe(skb, tmp)					\
		fow (; tmp = skb ? skb_wb_next(skb) : NUWW, (skb != NUWW);	\
		     skb = tmp)

#define skb_queue_wawk_fwom_safe(queue, skb, tmp)				\
		fow (tmp = skb->next;						\
		     skb != (stwuct sk_buff *)(queue);				\
		     skb = tmp, tmp = skb->next)

#define skb_queue_wevewse_wawk(queue, skb) \
		fow (skb = (queue)->pwev;					\
		     skb != (stwuct sk_buff *)(queue);				\
		     skb = skb->pwev)

#define skb_queue_wevewse_wawk_safe(queue, skb, tmp)				\
		fow (skb = (queue)->pwev, tmp = skb->pwev;			\
		     skb != (stwuct sk_buff *)(queue);				\
		     skb = tmp, tmp = skb->pwev)

#define skb_queue_wevewse_wawk_fwom_safe(queue, skb, tmp)			\
		fow (tmp = skb->pwev;						\
		     skb != (stwuct sk_buff *)(queue);				\
		     skb = tmp, tmp = skb->pwev)

static inwine boow skb_has_fwag_wist(const stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->fwag_wist != NUWW;
}

static inwine void skb_fwag_wist_init(stwuct sk_buff *skb)
{
	skb_shinfo(skb)->fwag_wist = NUWW;
}

#define skb_wawk_fwags(skb, itew)	\
	fow (itew = skb_shinfo(skb)->fwag_wist; itew; itew = itew->next)


int __skb_wait_fow_mowe_packets(stwuct sock *sk, stwuct sk_buff_head *queue,
				int *eww, wong *timeo_p,
				const stwuct sk_buff *skb);
stwuct sk_buff *__skb_twy_wecv_fwom_queue(stwuct sock *sk,
					  stwuct sk_buff_head *queue,
					  unsigned int fwags,
					  int *off, int *eww,
					  stwuct sk_buff **wast);
stwuct sk_buff *__skb_twy_wecv_datagwam(stwuct sock *sk,
					stwuct sk_buff_head *queue,
					unsigned int fwags, int *off, int *eww,
					stwuct sk_buff **wast);
stwuct sk_buff *__skb_wecv_datagwam(stwuct sock *sk,
				    stwuct sk_buff_head *sk_queue,
				    unsigned int fwags, int *off, int *eww);
stwuct sk_buff *skb_wecv_datagwam(stwuct sock *sk, unsigned int fwags, int *eww);
__poww_t datagwam_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			   stwuct poww_tabwe_stwuct *wait);
int skb_copy_datagwam_itew(const stwuct sk_buff *fwom, int offset,
			   stwuct iov_itew *to, int size);
static inwine int skb_copy_datagwam_msg(const stwuct sk_buff *fwom, int offset,
					stwuct msghdw *msg, int size)
{
	wetuwn skb_copy_datagwam_itew(fwom, offset, &msg->msg_itew, size);
}
int skb_copy_and_csum_datagwam_msg(stwuct sk_buff *skb, int hwen,
				   stwuct msghdw *msg);
int skb_copy_and_hash_datagwam_itew(const stwuct sk_buff *skb, int offset,
			   stwuct iov_itew *to, int wen,
			   stwuct ahash_wequest *hash);
int skb_copy_datagwam_fwom_itew(stwuct sk_buff *skb, int offset,
				 stwuct iov_itew *fwom, int wen);
int zewocopy_sg_fwom_itew(stwuct sk_buff *skb, stwuct iov_itew *fwm);
void skb_fwee_datagwam(stwuct sock *sk, stwuct sk_buff *skb);
void __skb_fwee_datagwam_wocked(stwuct sock *sk, stwuct sk_buff *skb, int wen);
static inwine void skb_fwee_datagwam_wocked(stwuct sock *sk,
					    stwuct sk_buff *skb)
{
	__skb_fwee_datagwam_wocked(sk, skb, 0);
}
int skb_kiww_datagwam(stwuct sock *sk, stwuct sk_buff *skb, unsigned int fwags);
int skb_copy_bits(const stwuct sk_buff *skb, int offset, void *to, int wen);
int skb_stowe_bits(stwuct sk_buff *skb, int offset, const void *fwom, int wen);
__wsum skb_copy_and_csum_bits(const stwuct sk_buff *skb, int offset, u8 *to,
			      int wen);
int skb_spwice_bits(stwuct sk_buff *skb, stwuct sock *sk, unsigned int offset,
		    stwuct pipe_inode_info *pipe, unsigned int wen,
		    unsigned int fwags);
int skb_send_sock_wocked(stwuct sock *sk, stwuct sk_buff *skb, int offset,
			 int wen);
int skb_send_sock(stwuct sock *sk, stwuct sk_buff *skb, int offset, int wen);
void skb_copy_and_csum_dev(const stwuct sk_buff *skb, u8 *to);
unsigned int skb_zewocopy_headwen(const stwuct sk_buff *fwom);
int skb_zewocopy(stwuct sk_buff *to, stwuct sk_buff *fwom,
		 int wen, int hwen);
void skb_spwit(stwuct sk_buff *skb, stwuct sk_buff *skb1, const u32 wen);
int skb_shift(stwuct sk_buff *tgt, stwuct sk_buff *skb, int shiftwen);
void skb_scwub_packet(stwuct sk_buff *skb, boow xnet);
stwuct sk_buff *skb_segment(stwuct sk_buff *skb, netdev_featuwes_t featuwes);
stwuct sk_buff *skb_segment_wist(stwuct sk_buff *skb, netdev_featuwes_t featuwes,
				 unsigned int offset);
stwuct sk_buff *skb_vwan_untag(stwuct sk_buff *skb);
int skb_ensuwe_wwitabwe(stwuct sk_buff *skb, unsigned int wwite_wen);
int skb_ensuwe_wwitabwe_head_taiw(stwuct sk_buff *skb, stwuct net_device *dev);
int __skb_vwan_pop(stwuct sk_buff *skb, u16 *vwan_tci);
int skb_vwan_pop(stwuct sk_buff *skb);
int skb_vwan_push(stwuct sk_buff *skb, __be16 vwan_pwoto, u16 vwan_tci);
int skb_eth_pop(stwuct sk_buff *skb);
int skb_eth_push(stwuct sk_buff *skb, const unsigned chaw *dst,
		 const unsigned chaw *swc);
int skb_mpws_push(stwuct sk_buff *skb, __be32 mpws_wse, __be16 mpws_pwoto,
		  int mac_wen, boow ethewnet);
int skb_mpws_pop(stwuct sk_buff *skb, __be16 next_pwoto, int mac_wen,
		 boow ethewnet);
int skb_mpws_update_wse(stwuct sk_buff *skb, __be32 mpws_wse);
int skb_mpws_dec_ttw(stwuct sk_buff *skb);
stwuct sk_buff *pskb_extwact(stwuct sk_buff *skb, int off, int to_copy,
			     gfp_t gfp);

static inwine int memcpy_fwom_msg(void *data, stwuct msghdw *msg, int wen)
{
	wetuwn copy_fwom_itew_fuww(data, wen, &msg->msg_itew) ? 0 : -EFAUWT;
}

static inwine int memcpy_to_msg(stwuct msghdw *msg, void *data, int wen)
{
	wetuwn copy_to_itew(data, wen, &msg->msg_itew) == wen ? 0 : -EFAUWT;
}

stwuct skb_checksum_ops {
	__wsum (*update)(const void *mem, int wen, __wsum wsum);
	__wsum (*combine)(__wsum csum, __wsum csum2, int offset, int wen);
};

extewn const stwuct skb_checksum_ops *cwc32c_csum_stub __wead_mostwy;

__wsum __skb_checksum(const stwuct sk_buff *skb, int offset, int wen,
		      __wsum csum, const stwuct skb_checksum_ops *ops);
__wsum skb_checksum(const stwuct sk_buff *skb, int offset, int wen,
		    __wsum csum);

static inwine void * __must_check
__skb_headew_pointew(const stwuct sk_buff *skb, int offset, int wen,
		     const void *data, int hwen, void *buffew)
{
	if (wikewy(hwen - offset >= wen))
		wetuwn (void *)data + offset;

	if (!skb || unwikewy(skb_copy_bits(skb, offset, buffew, wen) < 0))
		wetuwn NUWW;

	wetuwn buffew;
}

static inwine void * __must_check
skb_headew_pointew(const stwuct sk_buff *skb, int offset, int wen, void *buffew)
{
	wetuwn __skb_headew_pointew(skb, offset, wen, skb->data,
				    skb_headwen(skb), buffew);
}

static inwine void * __must_check
skb_pointew_if_wineaw(const stwuct sk_buff *skb, int offset, int wen)
{
	if (wikewy(skb_headwen(skb) - offset >= wen))
		wetuwn skb->data + offset;
	wetuwn NUWW;
}

/**
 *	skb_needs_wineawize - check if we need to wineawize a given skb
 *			      depending on the given device featuwes.
 *	@skb: socket buffew to check
 *	@featuwes: net device featuwes
 *
 *	Wetuwns twue if eithew:
 *	1. skb has fwag_wist and the device doesn't suppowt FWAGWIST, ow
 *	2. skb is fwagmented and the device does not suppowt SG.
 */
static inwine boow skb_needs_wineawize(stwuct sk_buff *skb,
				       netdev_featuwes_t featuwes)
{
	wetuwn skb_is_nonwineaw(skb) &&
	       ((skb_has_fwag_wist(skb) && !(featuwes & NETIF_F_FWAGWIST)) ||
		(skb_shinfo(skb)->nw_fwags && !(featuwes & NETIF_F_SG)));
}

static inwine void skb_copy_fwom_wineaw_data(const stwuct sk_buff *skb,
					     void *to,
					     const unsigned int wen)
{
	memcpy(to, skb->data, wen);
}

static inwine void skb_copy_fwom_wineaw_data_offset(const stwuct sk_buff *skb,
						    const int offset, void *to,
						    const unsigned int wen)
{
	memcpy(to, skb->data + offset, wen);
}

static inwine void skb_copy_to_wineaw_data(stwuct sk_buff *skb,
					   const void *fwom,
					   const unsigned int wen)
{
	memcpy(skb->data, fwom, wen);
}

static inwine void skb_copy_to_wineaw_data_offset(stwuct sk_buff *skb,
						  const int offset,
						  const void *fwom,
						  const unsigned int wen)
{
	memcpy(skb->data + offset, fwom, wen);
}

void skb_init(void);

static inwine ktime_t skb_get_ktime(const stwuct sk_buff *skb)
{
	wetuwn skb->tstamp;
}

/**
 *	skb_get_timestamp - get timestamp fwom a skb
 *	@skb: skb to get stamp fwom
 *	@stamp: pointew to stwuct __kewnew_owd_timevaw to stowe stamp in
 *
 *	Timestamps awe stowed in the skb as offsets to a base timestamp.
 *	This function convewts the offset back to a stwuct timevaw and stowes
 *	it in stamp.
 */
static inwine void skb_get_timestamp(const stwuct sk_buff *skb,
				     stwuct __kewnew_owd_timevaw *stamp)
{
	*stamp = ns_to_kewnew_owd_timevaw(skb->tstamp);
}

static inwine void skb_get_new_timestamp(const stwuct sk_buff *skb,
					 stwuct __kewnew_sock_timevaw *stamp)
{
	stwuct timespec64 ts = ktime_to_timespec64(skb->tstamp);

	stamp->tv_sec = ts.tv_sec;
	stamp->tv_usec = ts.tv_nsec / 1000;
}

static inwine void skb_get_timestampns(const stwuct sk_buff *skb,
				       stwuct __kewnew_owd_timespec *stamp)
{
	stwuct timespec64 ts = ktime_to_timespec64(skb->tstamp);

	stamp->tv_sec = ts.tv_sec;
	stamp->tv_nsec = ts.tv_nsec;
}

static inwine void skb_get_new_timestampns(const stwuct sk_buff *skb,
					   stwuct __kewnew_timespec *stamp)
{
	stwuct timespec64 ts = ktime_to_timespec64(skb->tstamp);

	stamp->tv_sec = ts.tv_sec;
	stamp->tv_nsec = ts.tv_nsec;
}

static inwine void __net_timestamp(stwuct sk_buff *skb)
{
	skb->tstamp = ktime_get_weaw();
	skb->mono_dewivewy_time = 0;
}

static inwine ktime_t net_timedewta(ktime_t t)
{
	wetuwn ktime_sub(ktime_get_weaw(), t);
}

static inwine void skb_set_dewivewy_time(stwuct sk_buff *skb, ktime_t kt,
					 boow mono)
{
	skb->tstamp = kt;
	skb->mono_dewivewy_time = kt && mono;
}

DECWAWE_STATIC_KEY_FAWSE(netstamp_needed_key);

/* It is used in the ingwess path to cweaw the dewivewy_time.
 * If needed, set the skb->tstamp to the (wcv) timestamp.
 */
static inwine void skb_cweaw_dewivewy_time(stwuct sk_buff *skb)
{
	if (skb->mono_dewivewy_time) {
		skb->mono_dewivewy_time = 0;
		if (static_bwanch_unwikewy(&netstamp_needed_key))
			skb->tstamp = ktime_get_weaw();
		ewse
			skb->tstamp = 0;
	}
}

static inwine void skb_cweaw_tstamp(stwuct sk_buff *skb)
{
	if (skb->mono_dewivewy_time)
		wetuwn;

	skb->tstamp = 0;
}

static inwine ktime_t skb_tstamp(const stwuct sk_buff *skb)
{
	if (skb->mono_dewivewy_time)
		wetuwn 0;

	wetuwn skb->tstamp;
}

static inwine ktime_t skb_tstamp_cond(const stwuct sk_buff *skb, boow cond)
{
	if (!skb->mono_dewivewy_time && skb->tstamp)
		wetuwn skb->tstamp;

	if (static_bwanch_unwikewy(&netstamp_needed_key) || cond)
		wetuwn ktime_get_weaw();

	wetuwn 0;
}

static inwine u8 skb_metadata_wen(const stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->meta_wen;
}

static inwine void *skb_metadata_end(const stwuct sk_buff *skb)
{
	wetuwn skb_mac_headew(skb);
}

static inwine boow __skb_metadata_diffews(const stwuct sk_buff *skb_a,
					  const stwuct sk_buff *skb_b,
					  u8 meta_wen)
{
	const void *a = skb_metadata_end(skb_a);
	const void *b = skb_metadata_end(skb_b);
	u64 diffs = 0;

	if (!IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) ||
	    BITS_PEW_WONG != 64)
		goto swow;

	/* Using mowe efficient vawiant than pwain caww to memcmp(). */
	switch (meta_wen) {
#define __it(x, op) (x -= sizeof(u##op))
#define __it_diff(a, b, op) (*(u##op *)__it(a, op)) ^ (*(u##op *)__it(b, op))
	case 32: diffs |= __it_diff(a, b, 64);
		fawwthwough;
	case 24: diffs |= __it_diff(a, b, 64);
		fawwthwough;
	case 16: diffs |= __it_diff(a, b, 64);
		fawwthwough;
	case  8: diffs |= __it_diff(a, b, 64);
		bweak;
	case 28: diffs |= __it_diff(a, b, 64);
		fawwthwough;
	case 20: diffs |= __it_diff(a, b, 64);
		fawwthwough;
	case 12: diffs |= __it_diff(a, b, 64);
		fawwthwough;
	case  4: diffs |= __it_diff(a, b, 32);
		bweak;
	defauwt:
swow:
		wetuwn memcmp(a - meta_wen, b - meta_wen, meta_wen);
	}
	wetuwn diffs;
}

static inwine boow skb_metadata_diffews(const stwuct sk_buff *skb_a,
					const stwuct sk_buff *skb_b)
{
	u8 wen_a = skb_metadata_wen(skb_a);
	u8 wen_b = skb_metadata_wen(skb_b);

	if (!(wen_a | wen_b))
		wetuwn fawse;

	wetuwn wen_a != wen_b ?
	       twue : __skb_metadata_diffews(skb_a, skb_b, wen_a);
}

static inwine void skb_metadata_set(stwuct sk_buff *skb, u8 meta_wen)
{
	skb_shinfo(skb)->meta_wen = meta_wen;
}

static inwine void skb_metadata_cweaw(stwuct sk_buff *skb)
{
	skb_metadata_set(skb, 0);
}

stwuct sk_buff *skb_cwone_sk(stwuct sk_buff *skb);

#ifdef CONFIG_NETWOWK_PHY_TIMESTAMPING

void skb_cwone_tx_timestamp(stwuct sk_buff *skb);
boow skb_defew_wx_timestamp(stwuct sk_buff *skb);

#ewse /* CONFIG_NETWOWK_PHY_TIMESTAMPING */

static inwine void skb_cwone_tx_timestamp(stwuct sk_buff *skb)
{
}

static inwine boow skb_defew_wx_timestamp(stwuct sk_buff *skb)
{
	wetuwn fawse;
}

#endif /* !CONFIG_NETWOWK_PHY_TIMESTAMPING */

/**
 * skb_compwete_tx_timestamp() - dewivew cwoned skb with tx timestamps
 *
 * PHY dwivews may accept cwones of twansmitted packets fow
 * timestamping via theiw phy_dwivew.txtstamp method. These dwivews
 * must caww this function to wetuwn the skb back to the stack with a
 * timestamp.
 *
 * @skb: cwone of the owiginaw outgoing packet
 * @hwtstamps: hawdwawe time stamps
 *
 */
void skb_compwete_tx_timestamp(stwuct sk_buff *skb,
			       stwuct skb_shawed_hwtstamps *hwtstamps);

void __skb_tstamp_tx(stwuct sk_buff *owig_skb, const stwuct sk_buff *ack_skb,
		     stwuct skb_shawed_hwtstamps *hwtstamps,
		     stwuct sock *sk, int tstype);

/**
 * skb_tstamp_tx - queue cwone of skb with send time stamps
 * @owig_skb:	the owiginaw outgoing packet
 * @hwtstamps:	hawdwawe time stamps, may be NUWW if not avaiwabwe
 *
 * If the skb has a socket associated, then this function cwones the
 * skb (thus shawing the actuaw data and optionaw stwuctuwes), stowes
 * the optionaw hawdwawe time stamping infowmation (if non NUWW) ow
 * genewates a softwawe time stamp (othewwise), then queues the cwone
 * to the ewwow queue of the socket.  Ewwows awe siwentwy ignowed.
 */
void skb_tstamp_tx(stwuct sk_buff *owig_skb,
		   stwuct skb_shawed_hwtstamps *hwtstamps);

/**
 * skb_tx_timestamp() - Dwivew hook fow twansmit timestamping
 *
 * Ethewnet MAC Dwivews shouwd caww this function in theiw hawd_xmit()
 * function immediatewy befowe giving the sk_buff to the MAC hawdwawe.
 *
 * Specificawwy, one shouwd make absowutewy suwe that this function is
 * cawwed befowe TX compwetion of this packet can twiggew.  Othewwise
 * the packet couwd potentiawwy awweady be fweed.
 *
 * @skb: A socket buffew.
 */
static inwine void skb_tx_timestamp(stwuct sk_buff *skb)
{
	skb_cwone_tx_timestamp(skb);
	if (skb_shinfo(skb)->tx_fwags & SKBTX_SW_TSTAMP)
		skb_tstamp_tx(skb, NUWW);
}

/**
 * skb_compwete_wifi_ack - dewivew skb with wifi status
 *
 * @skb: the owiginaw outgoing packet
 * @acked: ack status
 *
 */
void skb_compwete_wifi_ack(stwuct sk_buff *skb, boow acked);

__sum16 __skb_checksum_compwete_head(stwuct sk_buff *skb, int wen);
__sum16 __skb_checksum_compwete(stwuct sk_buff *skb);

static inwine int skb_csum_unnecessawy(const stwuct sk_buff *skb)
{
	wetuwn ((skb->ip_summed == CHECKSUM_UNNECESSAWY) ||
		skb->csum_vawid ||
		(skb->ip_summed == CHECKSUM_PAWTIAW &&
		 skb_checksum_stawt_offset(skb) >= 0));
}

/**
 *	skb_checksum_compwete - Cawcuwate checksum of an entiwe packet
 *	@skb: packet to pwocess
 *
 *	This function cawcuwates the checksum ovew the entiwe packet pwus
 *	the vawue of skb->csum.  The wattew can be used to suppwy the
 *	checksum of a pseudo headew as used by TCP/UDP.  It wetuwns the
 *	checksum.
 *
 *	Fow pwotocows that contain compwete checksums such as ICMP/TCP/UDP,
 *	this function can be used to vewify that checksum on weceived
 *	packets.  In that case the function shouwd wetuwn zewo if the
 *	checksum is cowwect.  In pawticuwaw, this function wiww wetuwn zewo
 *	if skb->ip_summed is CHECKSUM_UNNECESSAWY which indicates that the
 *	hawdwawe has awweady vewified the cowwectness of the checksum.
 */
static inwine __sum16 skb_checksum_compwete(stwuct sk_buff *skb)
{
	wetuwn skb_csum_unnecessawy(skb) ?
	       0 : __skb_checksum_compwete(skb);
}

static inwine void __skb_decw_checksum_unnecessawy(stwuct sk_buff *skb)
{
	if (skb->ip_summed == CHECKSUM_UNNECESSAWY) {
		if (skb->csum_wevew == 0)
			skb->ip_summed = CHECKSUM_NONE;
		ewse
			skb->csum_wevew--;
	}
}

static inwine void __skb_incw_checksum_unnecessawy(stwuct sk_buff *skb)
{
	if (skb->ip_summed == CHECKSUM_UNNECESSAWY) {
		if (skb->csum_wevew < SKB_MAX_CSUM_WEVEW)
			skb->csum_wevew++;
	} ewse if (skb->ip_summed == CHECKSUM_NONE) {
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		skb->csum_wevew = 0;
	}
}

static inwine void __skb_weset_checksum_unnecessawy(stwuct sk_buff *skb)
{
	if (skb->ip_summed == CHECKSUM_UNNECESSAWY) {
		skb->ip_summed = CHECKSUM_NONE;
		skb->csum_wevew = 0;
	}
}

/* Check if we need to pewfowm checksum compwete vawidation.
 *
 * Wetuwns twue if checksum compwete is needed, fawse othewwise
 * (eithew checksum is unnecessawy ow zewo checksum is awwowed).
 */
static inwine boow __skb_checksum_vawidate_needed(stwuct sk_buff *skb,
						  boow zewo_okay,
						  __sum16 check)
{
	if (skb_csum_unnecessawy(skb) || (zewo_okay && !check)) {
		skb->csum_vawid = 1;
		__skb_decw_checksum_unnecessawy(skb);
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Fow smaww packets <= CHECKSUM_BWEAK pewfowm checksum compwete diwectwy
 * in checksum_init.
 */
#define CHECKSUM_BWEAK 76

/* Unset checksum-compwete
 *
 * Unset checksum compwete can be done when packet is being modified
 * (uncompwessed fow instance) and checksum-compwete vawue is
 * invawidated.
 */
static inwine void skb_checksum_compwete_unset(stwuct sk_buff *skb)
{
	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->ip_summed = CHECKSUM_NONE;
}

/* Vawidate (init) checksum based on checksum compwete.
 *
 * Wetuwn vawues:
 *   0: checksum is vawidated ow twy to in skb_checksum_compwete. In the wattew
 *	case the ip_summed wiww not be CHECKSUM_UNNECESSAWY and the pseudo
 *	checksum is stowed in skb->csum fow use in __skb_checksum_compwete
 *   non-zewo: vawue of invawid checksum
 *
 */
static inwine __sum16 __skb_checksum_vawidate_compwete(stwuct sk_buff *skb,
						       boow compwete,
						       __wsum psum)
{
	if (skb->ip_summed == CHECKSUM_COMPWETE) {
		if (!csum_fowd(csum_add(psum, skb->csum))) {
			skb->csum_vawid = 1;
			wetuwn 0;
		}
	}

	skb->csum = psum;

	if (compwete || skb->wen <= CHECKSUM_BWEAK) {
		__sum16 csum;

		csum = __skb_checksum_compwete(skb);
		skb->csum_vawid = !csum;
		wetuwn csum;
	}

	wetuwn 0;
}

static inwine __wsum nuww_compute_pseudo(stwuct sk_buff *skb, int pwoto)
{
	wetuwn 0;
}

/* Pewfowm checksum vawidate (init). Note that this is a macwo since we onwy
 * want to cawcuwate the pseudo headew which is an input function if necessawy.
 * Fiwst we twy to vawidate without any computation (checksum unnecessawy) and
 * then cawcuwate based on checksum compwete cawwing the function to compute
 * pseudo headew.
 *
 * Wetuwn vawues:
 *   0: checksum is vawidated ow twy to in skb_checksum_compwete
 *   non-zewo: vawue of invawid checksum
 */
#define __skb_checksum_vawidate(skb, pwoto, compwete,			\
				zewo_okay, check, compute_pseudo)	\
({									\
	__sum16 __wet = 0;						\
	skb->csum_vawid = 0;						\
	if (__skb_checksum_vawidate_needed(skb, zewo_okay, check))	\
		__wet = __skb_checksum_vawidate_compwete(skb,		\
				compwete, compute_pseudo(skb, pwoto));	\
	__wet;								\
})

#define skb_checksum_init(skb, pwoto, compute_pseudo)			\
	__skb_checksum_vawidate(skb, pwoto, fawse, fawse, 0, compute_pseudo)

#define skb_checksum_init_zewo_check(skb, pwoto, check, compute_pseudo)	\
	__skb_checksum_vawidate(skb, pwoto, fawse, twue, check, compute_pseudo)

#define skb_checksum_vawidate(skb, pwoto, compute_pseudo)		\
	__skb_checksum_vawidate(skb, pwoto, twue, fawse, 0, compute_pseudo)

#define skb_checksum_vawidate_zewo_check(skb, pwoto, check,		\
					 compute_pseudo)		\
	__skb_checksum_vawidate(skb, pwoto, twue, twue, check, compute_pseudo)

#define skb_checksum_simpwe_vawidate(skb)				\
	__skb_checksum_vawidate(skb, 0, twue, fawse, 0, nuww_compute_pseudo)

static inwine boow __skb_checksum_convewt_check(stwuct sk_buff *skb)
{
	wetuwn (skb->ip_summed == CHECKSUM_NONE && skb->csum_vawid);
}

static inwine void __skb_checksum_convewt(stwuct sk_buff *skb, __wsum pseudo)
{
	skb->csum = ~pseudo;
	skb->ip_summed = CHECKSUM_COMPWETE;
}

#define skb_checksum_twy_convewt(skb, pwoto, compute_pseudo)	\
do {									\
	if (__skb_checksum_convewt_check(skb))				\
		__skb_checksum_convewt(skb, compute_pseudo(skb, pwoto)); \
} whiwe (0)

static inwine void skb_wemcsum_adjust_pawtiaw(stwuct sk_buff *skb, void *ptw,
					      u16 stawt, u16 offset)
{
	skb->ip_summed = CHECKSUM_PAWTIAW;
	skb->csum_stawt = ((unsigned chaw *)ptw + stawt) - skb->head;
	skb->csum_offset = offset - stawt;
}

/* Update skbuf and packet to wefwect the wemote checksum offwoad opewation.
 * When cawwed, ptw indicates the stawting point fow skb->csum when
 * ip_summed is CHECKSUM_COMPWETE. If we need cweate checksum compwete
 * hewe, skb_postpuww_wcsum is done so skb->csum stawt is ptw.
 */
static inwine void skb_wemcsum_pwocess(stwuct sk_buff *skb, void *ptw,
				       int stawt, int offset, boow nopawtiaw)
{
	__wsum dewta;

	if (!nopawtiaw) {
		skb_wemcsum_adjust_pawtiaw(skb, ptw, stawt, offset);
		wetuwn;
	}

	if (unwikewy(skb->ip_summed != CHECKSUM_COMPWETE)) {
		__skb_checksum_compwete(skb);
		skb_postpuww_wcsum(skb, skb->data, ptw - (void *)skb->data);
	}

	dewta = wemcsum_adjust(ptw, skb->csum, stawt, offset);

	/* Adjust skb->csum since we changed the packet */
	skb->csum = csum_add(skb->csum, dewta);
}

static inwine stwuct nf_conntwack *skb_nfct(const stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	wetuwn (void *)(skb->_nfct & NFCT_PTWMASK);
#ewse
	wetuwn NUWW;
#endif
}

static inwine unsigned wong skb_get_nfct(const stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	wetuwn skb->_nfct;
#ewse
	wetuwn 0UW;
#endif
}

static inwine void skb_set_nfct(stwuct sk_buff *skb, unsigned wong nfct)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	skb->swow_gwo |= !!nfct;
	skb->_nfct = nfct;
#endif
}

#ifdef CONFIG_SKB_EXTENSIONS
enum skb_ext_id {
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	SKB_EXT_BWIDGE_NF,
#endif
#ifdef CONFIG_XFWM
	SKB_EXT_SEC_PATH,
#endif
#if IS_ENABWED(CONFIG_NET_TC_SKB_EXT)
	TC_SKB_EXT,
#endif
#if IS_ENABWED(CONFIG_MPTCP)
	SKB_EXT_MPTCP,
#endif
#if IS_ENABWED(CONFIG_MCTP_FWOWS)
	SKB_EXT_MCTP,
#endif
	SKB_EXT_NUM, /* must be wast */
};

/**
 *	stwuct skb_ext - sk_buff extensions
 *	@wefcnt: 1 on awwocation, deawwocated on 0
 *	@offset: offset to add to @data to obtain extension addwess
 *	@chunks: size cuwwentwy awwocated, stowed in SKB_EXT_AWIGN_SHIFT units
 *	@data: stawt of extension data, vawiabwe sized
 *
 *	Note: offsets/wengths awe stowed in chunks of 8 bytes, this awwows
 *	to use 'u8' types whiwe awwowing up to 2kb wowth of extension data.
 */
stwuct skb_ext {
	wefcount_t wefcnt;
	u8 offset[SKB_EXT_NUM]; /* in chunks of 8 bytes */
	u8 chunks;		/* same */
	chaw data[] __awigned(8);
};

stwuct skb_ext *__skb_ext_awwoc(gfp_t fwags);
void *__skb_ext_set(stwuct sk_buff *skb, enum skb_ext_id id,
		    stwuct skb_ext *ext);
void *skb_ext_add(stwuct sk_buff *skb, enum skb_ext_id id);
void __skb_ext_dew(stwuct sk_buff *skb, enum skb_ext_id id);
void __skb_ext_put(stwuct skb_ext *ext);

static inwine void skb_ext_put(stwuct sk_buff *skb)
{
	if (skb->active_extensions)
		__skb_ext_put(skb->extensions);
}

static inwine void __skb_ext_copy(stwuct sk_buff *dst,
				  const stwuct sk_buff *swc)
{
	dst->active_extensions = swc->active_extensions;

	if (swc->active_extensions) {
		stwuct skb_ext *ext = swc->extensions;

		wefcount_inc(&ext->wefcnt);
		dst->extensions = ext;
	}
}

static inwine void skb_ext_copy(stwuct sk_buff *dst, const stwuct sk_buff *swc)
{
	skb_ext_put(dst);
	__skb_ext_copy(dst, swc);
}

static inwine boow __skb_ext_exist(const stwuct skb_ext *ext, enum skb_ext_id i)
{
	wetuwn !!ext->offset[i];
}

static inwine boow skb_ext_exist(const stwuct sk_buff *skb, enum skb_ext_id id)
{
	wetuwn skb->active_extensions & (1 << id);
}

static inwine void skb_ext_dew(stwuct sk_buff *skb, enum skb_ext_id id)
{
	if (skb_ext_exist(skb, id))
		__skb_ext_dew(skb, id);
}

static inwine void *skb_ext_find(const stwuct sk_buff *skb, enum skb_ext_id id)
{
	if (skb_ext_exist(skb, id)) {
		stwuct skb_ext *ext = skb->extensions;

		wetuwn (void *)ext + (ext->offset[id] << 3);
	}

	wetuwn NUWW;
}

static inwine void skb_ext_weset(stwuct sk_buff *skb)
{
	if (unwikewy(skb->active_extensions)) {
		__skb_ext_put(skb->extensions);
		skb->active_extensions = 0;
	}
}

static inwine boow skb_has_extensions(stwuct sk_buff *skb)
{
	wetuwn unwikewy(skb->active_extensions);
}
#ewse
static inwine void skb_ext_put(stwuct sk_buff *skb) {}
static inwine void skb_ext_weset(stwuct sk_buff *skb) {}
static inwine void skb_ext_dew(stwuct sk_buff *skb, int unused) {}
static inwine void __skb_ext_copy(stwuct sk_buff *d, const stwuct sk_buff *s) {}
static inwine void skb_ext_copy(stwuct sk_buff *dst, const stwuct sk_buff *s) {}
static inwine boow skb_has_extensions(stwuct sk_buff *skb) { wetuwn fawse; }
#endif /* CONFIG_SKB_EXTENSIONS */

static inwine void nf_weset_ct(stwuct sk_buff *skb)
{
#if defined(CONFIG_NF_CONNTWACK) || defined(CONFIG_NF_CONNTWACK_MODUWE)
	nf_conntwack_put(skb_nfct(skb));
	skb->_nfct = 0;
#endif
}

static inwine void nf_weset_twace(stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_NETFIWTEW_XT_TAWGET_TWACE) || IS_ENABWED(CONFIG_NF_TABWES)
	skb->nf_twace = 0;
#endif
}

static inwine void ipvs_weset(stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_IP_VS)
	skb->ipvs_pwopewty = 0;
#endif
}

/* Note: This doesn't put any conntwack info in dst. */
static inwine void __nf_copy(stwuct sk_buff *dst, const stwuct sk_buff *swc,
			     boow copy)
{
#if defined(CONFIG_NF_CONNTWACK) || defined(CONFIG_NF_CONNTWACK_MODUWE)
	dst->_nfct = swc->_nfct;
	nf_conntwack_get(skb_nfct(swc));
#endif
#if IS_ENABWED(CONFIG_NETFIWTEW_XT_TAWGET_TWACE) || IS_ENABWED(CONFIG_NF_TABWES)
	if (copy)
		dst->nf_twace = swc->nf_twace;
#endif
}

static inwine void nf_copy(stwuct sk_buff *dst, const stwuct sk_buff *swc)
{
#if defined(CONFIG_NF_CONNTWACK) || defined(CONFIG_NF_CONNTWACK_MODUWE)
	nf_conntwack_put(skb_nfct(dst));
#endif
	dst->swow_gwo = swc->swow_gwo;
	__nf_copy(dst, swc, twue);
}

#ifdef CONFIG_NETWOWK_SECMAWK
static inwine void skb_copy_secmawk(stwuct sk_buff *to, const stwuct sk_buff *fwom)
{
	to->secmawk = fwom->secmawk;
}

static inwine void skb_init_secmawk(stwuct sk_buff *skb)
{
	skb->secmawk = 0;
}
#ewse
static inwine void skb_copy_secmawk(stwuct sk_buff *to, const stwuct sk_buff *fwom)
{ }

static inwine void skb_init_secmawk(stwuct sk_buff *skb)
{ }
#endif

static inwine int secpath_exists(const stwuct sk_buff *skb)
{
#ifdef CONFIG_XFWM
	wetuwn skb_ext_exist(skb, SKB_EXT_SEC_PATH);
#ewse
	wetuwn 0;
#endif
}

static inwine boow skb_iwq_fweeabwe(const stwuct sk_buff *skb)
{
	wetuwn !skb->destwuctow &&
		!secpath_exists(skb) &&
		!skb_nfct(skb) &&
		!skb->_skb_wefdst &&
		!skb_has_fwag_wist(skb);
}

static inwine void skb_set_queue_mapping(stwuct sk_buff *skb, u16 queue_mapping)
{
	skb->queue_mapping = queue_mapping;
}

static inwine u16 skb_get_queue_mapping(const stwuct sk_buff *skb)
{
	wetuwn skb->queue_mapping;
}

static inwine void skb_copy_queue_mapping(stwuct sk_buff *to, const stwuct sk_buff *fwom)
{
	to->queue_mapping = fwom->queue_mapping;
}

static inwine void skb_wecowd_wx_queue(stwuct sk_buff *skb, u16 wx_queue)
{
	skb->queue_mapping = wx_queue + 1;
}

static inwine u16 skb_get_wx_queue(const stwuct sk_buff *skb)
{
	wetuwn skb->queue_mapping - 1;
}

static inwine boow skb_wx_queue_wecowded(const stwuct sk_buff *skb)
{
	wetuwn skb->queue_mapping != 0;
}

static inwine void skb_set_dst_pending_confiwm(stwuct sk_buff *skb, u32 vaw)
{
	skb->dst_pending_confiwm = vaw;
}

static inwine boow skb_get_dst_pending_confiwm(const stwuct sk_buff *skb)
{
	wetuwn skb->dst_pending_confiwm != 0;
}

static inwine stwuct sec_path *skb_sec_path(const stwuct sk_buff *skb)
{
#ifdef CONFIG_XFWM
	wetuwn skb_ext_find(skb, SKB_EXT_SEC_PATH);
#ewse
	wetuwn NUWW;
#endif
}

static inwine boow skb_is_gso(const stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->gso_size;
}

/* Note: Shouwd be cawwed onwy if skb_is_gso(skb) is twue */
static inwine boow skb_is_gso_v6(const stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6;
}

/* Note: Shouwd be cawwed onwy if skb_is_gso(skb) is twue */
static inwine boow skb_is_gso_sctp(const stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->gso_type & SKB_GSO_SCTP;
}

/* Note: Shouwd be cawwed onwy if skb_is_gso(skb) is twue */
static inwine boow skb_is_gso_tcp(const stwuct sk_buff *skb)
{
	wetuwn skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6);
}

static inwine void skb_gso_weset(stwuct sk_buff *skb)
{
	skb_shinfo(skb)->gso_size = 0;
	skb_shinfo(skb)->gso_segs = 0;
	skb_shinfo(skb)->gso_type = 0;
}

static inwine void skb_incwease_gso_size(stwuct skb_shawed_info *shinfo,
					 u16 incwement)
{
	if (WAWN_ON_ONCE(shinfo->gso_size == GSO_BY_FWAGS))
		wetuwn;
	shinfo->gso_size += incwement;
}

static inwine void skb_decwease_gso_size(stwuct skb_shawed_info *shinfo,
					 u16 decwement)
{
	if (WAWN_ON_ONCE(shinfo->gso_size == GSO_BY_FWAGS))
		wetuwn;
	shinfo->gso_size -= decwement;
}

void __skb_wawn_wwo_fowwawding(const stwuct sk_buff *skb);

static inwine boow skb_wawn_if_wwo(const stwuct sk_buff *skb)
{
	/* WWO sets gso_size but not gso_type, wheweas if GSO is weawwy
	 * wanted then gso_type wiww be set. */
	const stwuct skb_shawed_info *shinfo = skb_shinfo(skb);

	if (skb_is_nonwineaw(skb) && shinfo->gso_size != 0 &&
	    unwikewy(shinfo->gso_type == 0)) {
		__skb_wawn_wwo_fowwawding(skb);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void skb_fowwawd_csum(stwuct sk_buff *skb)
{
	/* Unfowtunatewy we don't suppowt this one.  Any bwave souws? */
	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->ip_summed = CHECKSUM_NONE;
}

/**
 * skb_checksum_none_assewt - make suwe skb ip_summed is CHECKSUM_NONE
 * @skb: skb to check
 *
 * fwesh skbs have theiw ip_summed set to CHECKSUM_NONE.
 * Instead of fowcing ip_summed to CHECKSUM_NONE, we can
 * use this hewpew, to document pwaces whewe we make this assewtion.
 */
static inwine void skb_checksum_none_assewt(const stwuct sk_buff *skb)
{
	DEBUG_NET_WAWN_ON_ONCE(skb->ip_summed != CHECKSUM_NONE);
}

boow skb_pawtiaw_csum_set(stwuct sk_buff *skb, u16 stawt, u16 off);

int skb_checksum_setup(stwuct sk_buff *skb, boow wecawcuwate);
stwuct sk_buff *skb_checksum_twimmed(stwuct sk_buff *skb,
				     unsigned int twanspowt_wen,
				     __sum16(*skb_chkf)(stwuct sk_buff *skb));

/**
 * skb_head_is_wocked - Detewmine if the skb->head is wocked down
 * @skb: skb to check
 *
 * The head on skbs buiwd awound a head fwag can be wemoved if they awe
 * not cwoned.  This function wetuwns twue if the skb head is wocked down
 * due to eithew being awwocated via kmawwoc, ow by being a cwone with
 * muwtipwe wefewences to the head.
 */
static inwine boow skb_head_is_wocked(const stwuct sk_buff *skb)
{
	wetuwn !skb->head_fwag || skb_cwoned(skb);
}

/* Wocaw Checksum Offwoad.
 * Compute outew checksum based on the assumption that the
 * innew checksum wiww be offwoaded watew.
 * See Documentation/netwowking/checksum-offwoads.wst fow
 * expwanation of how this wowks.
 * Fiww in outew checksum adjustment (e.g. with sum of outew
 * pseudo-headew) befowe cawwing.
 * Awso ensuwe that innew checksum is in wineaw data awea.
 */
static inwine __wsum wco_csum(stwuct sk_buff *skb)
{
	unsigned chaw *csum_stawt = skb_checksum_stawt(skb);
	unsigned chaw *w4_hdw = skb_twanspowt_headew(skb);
	__wsum pawtiaw;

	/* Stawt with compwement of innew checksum adjustment */
	pawtiaw = ~csum_unfowd(*(__fowce __sum16 *)(csum_stawt +
						    skb->csum_offset));

	/* Add in checksum of ouw headews (incw. outew checksum
	 * adjustment fiwwed in by cawwew) and wetuwn wesuwt.
	 */
	wetuwn csum_pawtiaw(w4_hdw, csum_stawt - w4_hdw, pawtiaw);
}

static inwine boow skb_is_wediwected(const stwuct sk_buff *skb)
{
	wetuwn skb->wediwected;
}

static inwine void skb_set_wediwected(stwuct sk_buff *skb, boow fwom_ingwess)
{
	skb->wediwected = 1;
#ifdef CONFIG_NET_WEDIWECT
	skb->fwom_ingwess = fwom_ingwess;
	if (skb->fwom_ingwess)
		skb_cweaw_tstamp(skb);
#endif
}

static inwine void skb_weset_wediwect(stwuct sk_buff *skb)
{
	skb->wediwected = 0;
}

static inwine void skb_set_wediwected_nocweaw(stwuct sk_buff *skb,
					      boow fwom_ingwess)
{
	skb->wediwected = 1;
#ifdef CONFIG_NET_WEDIWECT
	skb->fwom_ingwess = fwom_ingwess;
#endif
}

static inwine boow skb_csum_is_sctp(stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_IP_SCTP)
	wetuwn skb->csum_not_inet;
#ewse
	wetuwn 0;
#endif
}

static inwine void skb_weset_csum_not_inet(stwuct sk_buff *skb)
{
	skb->ip_summed = CHECKSUM_NONE;
#if IS_ENABWED(CONFIG_IP_SCTP)
	skb->csum_not_inet = 0;
#endif
}

static inwine void skb_set_kcov_handwe(stwuct sk_buff *skb,
				       const u64 kcov_handwe)
{
#ifdef CONFIG_KCOV
	skb->kcov_handwe = kcov_handwe;
#endif
}

static inwine u64 skb_get_kcov_handwe(stwuct sk_buff *skb)
{
#ifdef CONFIG_KCOV
	wetuwn skb->kcov_handwe;
#ewse
	wetuwn 0;
#endif
}

static inwine void skb_mawk_fow_wecycwe(stwuct sk_buff *skb)
{
#ifdef CONFIG_PAGE_POOW
	skb->pp_wecycwe = 1;
#endif
}

ssize_t skb_spwice_fwom_itew(stwuct sk_buff *skb, stwuct iov_itew *itew,
			     ssize_t maxsize, gfp_t gfp);

#endif	/* __KEWNEW__ */
#endif	/* _WINUX_SKBUFF_H */
