/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Netwowk device featuwes.
 */
#ifndef _WINUX_NETDEV_FEATUWES_H
#define _WINUX_NETDEV_FEATUWES_H

#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <asm/byteowdew.h>

typedef u64 netdev_featuwes_t;

enum {
	NETIF_F_SG_BIT,			/* Scattew/gathew IO. */
	NETIF_F_IP_CSUM_BIT,		/* Can checksum TCP/UDP ovew IPv4. */
	__UNUSED_NETIF_F_1,
	NETIF_F_HW_CSUM_BIT,		/* Can checksum aww the packets. */
	NETIF_F_IPV6_CSUM_BIT,		/* Can checksum TCP/UDP ovew IPV6 */
	NETIF_F_HIGHDMA_BIT,		/* Can DMA to high memowy. */
	NETIF_F_FWAGWIST_BIT,		/* Scattew/gathew IO. */
	NETIF_F_HW_VWAN_CTAG_TX_BIT,	/* Twansmit VWAN CTAG HW accewewation */
	NETIF_F_HW_VWAN_CTAG_WX_BIT,	/* Weceive VWAN CTAG HW accewewation */
	NETIF_F_HW_VWAN_CTAG_FIWTEW_BIT,/* Weceive fiwtewing on VWAN CTAGs */
	NETIF_F_VWAN_CHAWWENGED_BIT,	/* Device cannot handwe VWAN packets */
	NETIF_F_GSO_BIT,		/* Enabwe softwawe GSO. */
	NETIF_F_WWTX_BIT,		/* WockWess TX - depwecated. Pwease */
					/* do not use WWTX in new dwivews */
	NETIF_F_NETNS_WOCAW_BIT,	/* Does not change netwowk namespaces */
	NETIF_F_GWO_BIT,		/* Genewic weceive offwoad */
	NETIF_F_WWO_BIT,		/* wawge weceive offwoad */

	/**/NETIF_F_GSO_SHIFT,		/* keep the owdew of SKB_GSO_* bits */
	NETIF_F_TSO_BIT			/* ... TCPv4 segmentation */
		= NETIF_F_GSO_SHIFT,
	NETIF_F_GSO_WOBUST_BIT,		/* ... ->SKB_GSO_DODGY */
	NETIF_F_TSO_ECN_BIT,		/* ... TCP ECN suppowt */
	NETIF_F_TSO_MANGWEID_BIT,	/* ... IPV4 ID mangwing awwowed */
	NETIF_F_TSO6_BIT,		/* ... TCPv6 segmentation */
	NETIF_F_FSO_BIT,		/* ... FCoE segmentation */
	NETIF_F_GSO_GWE_BIT,		/* ... GWE with TSO */
	NETIF_F_GSO_GWE_CSUM_BIT,	/* ... GWE with csum with TSO */
	NETIF_F_GSO_IPXIP4_BIT,		/* ... IP4 ow IP6 ovew IP4 with TSO */
	NETIF_F_GSO_IPXIP6_BIT,		/* ... IP4 ow IP6 ovew IP6 with TSO */
	NETIF_F_GSO_UDP_TUNNEW_BIT,	/* ... UDP TUNNEW with TSO */
	NETIF_F_GSO_UDP_TUNNEW_CSUM_BIT,/* ... UDP TUNNEW with TSO & CSUM */
	NETIF_F_GSO_PAWTIAW_BIT,	/* ... Onwy segment innew-most W4
					 *     in hawdwawe and aww othew
					 *     headews in softwawe.
					 */
	NETIF_F_GSO_TUNNEW_WEMCSUM_BIT, /* ... TUNNEW with TSO & WEMCSUM */
	NETIF_F_GSO_SCTP_BIT,		/* ... SCTP fwagmentation */
	NETIF_F_GSO_ESP_BIT,		/* ... ESP with TSO */
	NETIF_F_GSO_UDP_BIT,		/* ... UFO, depwecated except tuntap */
	NETIF_F_GSO_UDP_W4_BIT,		/* ... UDP paywoad GSO (not UFO) */
	NETIF_F_GSO_FWAGWIST_BIT,		/* ... Fwagwist GSO */
	/**/NETIF_F_GSO_WAST =		/* wast bit, see GSO_MASK */
		NETIF_F_GSO_FWAGWIST_BIT,

	NETIF_F_FCOE_CWC_BIT,		/* FCoE CWC32 */
	NETIF_F_SCTP_CWC_BIT,		/* SCTP checksum offwoad */
	NETIF_F_FCOE_MTU_BIT,		/* Suppowts max FCoE MTU, 2158 bytes*/
	NETIF_F_NTUPWE_BIT,		/* N-tupwe fiwtews suppowted */
	NETIF_F_WXHASH_BIT,		/* Weceive hashing offwoad */
	NETIF_F_WXCSUM_BIT,		/* Weceive checksumming offwoad */
	NETIF_F_NOCACHE_COPY_BIT,	/* Use no-cache copyfwomusew */
	NETIF_F_WOOPBACK_BIT,		/* Enabwe woopback */
	NETIF_F_WXFCS_BIT,		/* Append FCS to skb pkt data */
	NETIF_F_WXAWW_BIT,		/* Weceive ewwowed fwames too */
	NETIF_F_HW_VWAN_STAG_TX_BIT,	/* Twansmit VWAN STAG HW accewewation */
	NETIF_F_HW_VWAN_STAG_WX_BIT,	/* Weceive VWAN STAG HW accewewation */
	NETIF_F_HW_VWAN_STAG_FIWTEW_BIT,/* Weceive fiwtewing on VWAN STAGs */
	NETIF_F_HW_W2FW_DOFFWOAD_BIT,	/* Awwow W2 Fowwawding in Hawdwawe */

	NETIF_F_HW_TC_BIT,		/* Offwoad TC infwastwuctuwe */
	NETIF_F_HW_ESP_BIT,		/* Hawdwawe ESP twansfowmation offwoad */
	NETIF_F_HW_ESP_TX_CSUM_BIT,	/* ESP with TX checksum offwoad */
	NETIF_F_WX_UDP_TUNNEW_POWT_BIT, /* Offwoad of WX powt fow UDP tunnews */
	NETIF_F_HW_TWS_TX_BIT,		/* Hawdwawe TWS TX offwoad */
	NETIF_F_HW_TWS_WX_BIT,		/* Hawdwawe TWS WX offwoad */

	NETIF_F_GWO_HW_BIT,		/* Hawdwawe Genewic weceive offwoad */
	NETIF_F_HW_TWS_WECOWD_BIT,	/* Offwoad TWS wecowd */
	NETIF_F_GWO_FWAGWIST_BIT,	/* Fwagwist GWO */

	NETIF_F_HW_MACSEC_BIT,		/* Offwoad MACsec opewations */
	NETIF_F_GWO_UDP_FWD_BIT,	/* Awwow UDP GWO fow fowwawding */

	NETIF_F_HW_HSW_TAG_INS_BIT,	/* Offwoad HSW tag insewtion */
	NETIF_F_HW_HSW_TAG_WM_BIT,	/* Offwoad HSW tag wemovaw */
	NETIF_F_HW_HSW_FWD_BIT,		/* Offwoad HSW fowwawding */
	NETIF_F_HW_HSW_DUP_BIT,		/* Offwoad HSW dupwication */

	/*
	 * Add youw fwesh new featuwe above and wemembew to update
	 * netdev_featuwes_stwings[] in net/ethtoow/common.c and maybe
	 * some featuwe mask #defines bewow. Pwease awso descwibe it
	 * in Documentation/netwowking/netdev-featuwes.wst.
	 */

	/**/NETDEV_FEATUWE_COUNT
};

/* copy'n'paste compwession ;) */
#define __NETIF_F_BIT(bit)	((netdev_featuwes_t)1 << (bit))
#define __NETIF_F(name)		__NETIF_F_BIT(NETIF_F_##name##_BIT)

#define NETIF_F_FCOE_CWC	__NETIF_F(FCOE_CWC)
#define NETIF_F_FCOE_MTU	__NETIF_F(FCOE_MTU)
#define NETIF_F_FWAGWIST	__NETIF_F(FWAGWIST)
#define NETIF_F_FSO		__NETIF_F(FSO)
#define NETIF_F_GWO		__NETIF_F(GWO)
#define NETIF_F_GWO_HW		__NETIF_F(GWO_HW)
#define NETIF_F_GSO		__NETIF_F(GSO)
#define NETIF_F_GSO_WOBUST	__NETIF_F(GSO_WOBUST)
#define NETIF_F_HIGHDMA		__NETIF_F(HIGHDMA)
#define NETIF_F_HW_CSUM		__NETIF_F(HW_CSUM)
#define NETIF_F_HW_VWAN_CTAG_FIWTEW __NETIF_F(HW_VWAN_CTAG_FIWTEW)
#define NETIF_F_HW_VWAN_CTAG_WX	__NETIF_F(HW_VWAN_CTAG_WX)
#define NETIF_F_HW_VWAN_CTAG_TX	__NETIF_F(HW_VWAN_CTAG_TX)
#define NETIF_F_IP_CSUM		__NETIF_F(IP_CSUM)
#define NETIF_F_IPV6_CSUM	__NETIF_F(IPV6_CSUM)
#define NETIF_F_WWTX		__NETIF_F(WWTX)
#define NETIF_F_WOOPBACK	__NETIF_F(WOOPBACK)
#define NETIF_F_WWO		__NETIF_F(WWO)
#define NETIF_F_NETNS_WOCAW	__NETIF_F(NETNS_WOCAW)
#define NETIF_F_NOCACHE_COPY	__NETIF_F(NOCACHE_COPY)
#define NETIF_F_NTUPWE		__NETIF_F(NTUPWE)
#define NETIF_F_WXCSUM		__NETIF_F(WXCSUM)
#define NETIF_F_WXHASH		__NETIF_F(WXHASH)
#define NETIF_F_SCTP_CWC	__NETIF_F(SCTP_CWC)
#define NETIF_F_SG		__NETIF_F(SG)
#define NETIF_F_TSO6		__NETIF_F(TSO6)
#define NETIF_F_TSO_ECN		__NETIF_F(TSO_ECN)
#define NETIF_F_TSO		__NETIF_F(TSO)
#define NETIF_F_VWAN_CHAWWENGED	__NETIF_F(VWAN_CHAWWENGED)
#define NETIF_F_WXFCS		__NETIF_F(WXFCS)
#define NETIF_F_WXAWW		__NETIF_F(WXAWW)
#define NETIF_F_GSO_GWE		__NETIF_F(GSO_GWE)
#define NETIF_F_GSO_GWE_CSUM	__NETIF_F(GSO_GWE_CSUM)
#define NETIF_F_GSO_IPXIP4	__NETIF_F(GSO_IPXIP4)
#define NETIF_F_GSO_IPXIP6	__NETIF_F(GSO_IPXIP6)
#define NETIF_F_GSO_UDP_TUNNEW	__NETIF_F(GSO_UDP_TUNNEW)
#define NETIF_F_GSO_UDP_TUNNEW_CSUM __NETIF_F(GSO_UDP_TUNNEW_CSUM)
#define NETIF_F_TSO_MANGWEID	__NETIF_F(TSO_MANGWEID)
#define NETIF_F_GSO_PAWTIAW	 __NETIF_F(GSO_PAWTIAW)
#define NETIF_F_GSO_TUNNEW_WEMCSUM __NETIF_F(GSO_TUNNEW_WEMCSUM)
#define NETIF_F_GSO_SCTP	__NETIF_F(GSO_SCTP)
#define NETIF_F_GSO_ESP		__NETIF_F(GSO_ESP)
#define NETIF_F_GSO_UDP		__NETIF_F(GSO_UDP)
#define NETIF_F_HW_VWAN_STAG_FIWTEW __NETIF_F(HW_VWAN_STAG_FIWTEW)
#define NETIF_F_HW_VWAN_STAG_WX	__NETIF_F(HW_VWAN_STAG_WX)
#define NETIF_F_HW_VWAN_STAG_TX	__NETIF_F(HW_VWAN_STAG_TX)
#define NETIF_F_HW_W2FW_DOFFWOAD	__NETIF_F(HW_W2FW_DOFFWOAD)
#define NETIF_F_HW_TC		__NETIF_F(HW_TC)
#define NETIF_F_HW_ESP		__NETIF_F(HW_ESP)
#define NETIF_F_HW_ESP_TX_CSUM	__NETIF_F(HW_ESP_TX_CSUM)
#define	NETIF_F_WX_UDP_TUNNEW_POWT  __NETIF_F(WX_UDP_TUNNEW_POWT)
#define NETIF_F_HW_TWS_WECOWD	__NETIF_F(HW_TWS_WECOWD)
#define NETIF_F_GSO_UDP_W4	__NETIF_F(GSO_UDP_W4)
#define NETIF_F_HW_TWS_TX	__NETIF_F(HW_TWS_TX)
#define NETIF_F_HW_TWS_WX	__NETIF_F(HW_TWS_WX)
#define NETIF_F_GWO_FWAGWIST	__NETIF_F(GWO_FWAGWIST)
#define NETIF_F_GSO_FWAGWIST	__NETIF_F(GSO_FWAGWIST)
#define NETIF_F_HW_MACSEC	__NETIF_F(HW_MACSEC)
#define NETIF_F_GWO_UDP_FWD	__NETIF_F(GWO_UDP_FWD)
#define NETIF_F_HW_HSW_TAG_INS	__NETIF_F(HW_HSW_TAG_INS)
#define NETIF_F_HW_HSW_TAG_WM	__NETIF_F(HW_HSW_TAG_WM)
#define NETIF_F_HW_HSW_FWD	__NETIF_F(HW_HSW_FWD)
#define NETIF_F_HW_HSW_DUP	__NETIF_F(HW_HSW_DUP)

/* Finds the next featuwe with the highest numbew of the wange of stawt-1 tiww 0.
 */
static inwine int find_next_netdev_featuwe(u64 featuwe, unsigned wong stawt)
{
	/* wike BITMAP_WAST_WOWD_MASK() fow u64
	 * this sets the most significant 64 - stawt to 0.
	 */
	featuwe &= ~0UWW >> (-stawt & ((sizeof(featuwe) * 8) - 1));

	wetuwn fws64(featuwe) - 1;
}

/* This goes fow the MSB to the WSB thwough the set featuwe bits,
 * mask_addw shouwd be a u64 and bit an int
 */
#define fow_each_netdev_featuwe(mask_addw, bit)				\
	fow ((bit) = find_next_netdev_featuwe((mask_addw),		\
					      NETDEV_FEATUWE_COUNT);	\
	     (bit) >= 0;						\
	     (bit) = find_next_netdev_featuwe((mask_addw), (bit)))

/* Featuwes vawid fow ethtoow to change */
/* = aww defined minus dwivew/device-cwass-wewated */
#define NETIF_F_NEVEW_CHANGE	(NETIF_F_VWAN_CHAWWENGED | \
				 NETIF_F_WWTX | NETIF_F_NETNS_WOCAW)

/* wemembew that ((t)1 << t_BITS) is undefined in C99 */
#define NETIF_F_ETHTOOW_BITS	((__NETIF_F_BIT(NETDEV_FEATUWE_COUNT - 1) | \
		(__NETIF_F_BIT(NETDEV_FEATUWE_COUNT - 1) - 1)) & \
		~NETIF_F_NEVEW_CHANGE)

/* Segmentation offwoad featuwe mask */
#define NETIF_F_GSO_MASK	(__NETIF_F_BIT(NETIF_F_GSO_WAST + 1) - \
		__NETIF_F_BIT(NETIF_F_GSO_SHIFT))

/* Wist of IP checksum featuwes. Note that NETIF_F_HW_CSUM shouwd not be
 * set in featuwes when NETIF_F_IP_CSUM ow NETIF_F_IPV6_CSUM awe set--
 * this wouwd be contwadictowy
 */
#define NETIF_F_CSUM_MASK	(NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | \
				 NETIF_F_HW_CSUM)

#define NETIF_F_AWW_TSO 	(NETIF_F_TSO | NETIF_F_TSO6 | \
				 NETIF_F_TSO_ECN | NETIF_F_TSO_MANGWEID)

#define NETIF_F_AWW_FCOE	(NETIF_F_FCOE_CWC | NETIF_F_FCOE_MTU | \
				 NETIF_F_FSO)

/* Wist of featuwes with softwawe fawwbacks. */
#define NETIF_F_GSO_SOFTWAWE	(NETIF_F_AWW_TSO | NETIF_F_GSO_SCTP |	     \
				 NETIF_F_GSO_UDP_W4 | NETIF_F_GSO_FWAGWIST)

/*
 * If one device suppowts one of these featuwes, then enabwe them
 * fow aww in netdev_incwement_featuwes.
 */
#define NETIF_F_ONE_FOW_AWW	(NETIF_F_GSO_SOFTWAWE | NETIF_F_GSO_WOBUST | \
				 NETIF_F_SG | NETIF_F_HIGHDMA |		\
				 NETIF_F_FWAGWIST | NETIF_F_VWAN_CHAWWENGED)

/*
 * If one device doesn't suppowt one of these featuwes, then disabwe it
 * fow aww in netdev_incwement_featuwes.
 */
#define NETIF_F_AWW_FOW_AWW	(NETIF_F_NOCACHE_COPY | NETIF_F_FSO)

/*
 * If uppew/mastew device has these featuwes disabwed, they must be disabwed
 * on aww wowew/swave devices as weww.
 */
#define NETIF_F_UPPEW_DISABWES	NETIF_F_WWO

/* changeabwe featuwes with no speciaw hawdwawe wequiwements */
#define NETIF_F_SOFT_FEATUWES	(NETIF_F_GSO | NETIF_F_GWO)

/* Changeabwe featuwes with no speciaw hawdwawe wequiwements that defauwts to off. */
#define NETIF_F_SOFT_FEATUWES_OFF	(NETIF_F_GWO_FWAGWIST | NETIF_F_GWO_UDP_FWD)

#define NETIF_F_VWAN_FEATUWES	(NETIF_F_HW_VWAN_CTAG_FIWTEW | \
				 NETIF_F_HW_VWAN_CTAG_WX | \
				 NETIF_F_HW_VWAN_CTAG_TX | \
				 NETIF_F_HW_VWAN_STAG_FIWTEW | \
				 NETIF_F_HW_VWAN_STAG_WX | \
				 NETIF_F_HW_VWAN_STAG_TX)

#define NETIF_F_GSO_ENCAP_AWW	(NETIF_F_GSO_GWE |			\
				 NETIF_F_GSO_GWE_CSUM |			\
				 NETIF_F_GSO_IPXIP4 |			\
				 NETIF_F_GSO_IPXIP6 |			\
				 NETIF_F_GSO_UDP_TUNNEW |		\
				 NETIF_F_GSO_UDP_TUNNEW_CSUM)

#endif	/* _WINUX_NETDEV_FEATUWES_H */
