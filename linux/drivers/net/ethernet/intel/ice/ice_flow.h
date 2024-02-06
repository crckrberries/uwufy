/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_FWOW_H_
#define _ICE_FWOW_H_

#incwude "ice_fwex_type.h"

#define ICE_FWOW_ENTWY_HANDWE_INVAW	0
#define ICE_FWOW_FWD_OFF_INVAW		0xffff

/* Genewate fwow hash fiewd fwom fwow fiewd type(s) */
#define ICE_FWOW_HASH_ETH	\
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_ETH_DA) | \
	 BIT_UWW(ICE_FWOW_FIEWD_IDX_ETH_SA))
#define ICE_FWOW_HASH_IPV4	\
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_IPV4_SA) | \
	 BIT_UWW(ICE_FWOW_FIEWD_IDX_IPV4_DA))
#define ICE_FWOW_HASH_IPV6	\
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_IPV6_SA) | \
	 BIT_UWW(ICE_FWOW_FIEWD_IDX_IPV6_DA))
#define ICE_FWOW_HASH_TCP_POWT	\
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_TCP_SWC_POWT) | \
	 BIT_UWW(ICE_FWOW_FIEWD_IDX_TCP_DST_POWT))
#define ICE_FWOW_HASH_UDP_POWT	\
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_UDP_SWC_POWT) | \
	 BIT_UWW(ICE_FWOW_FIEWD_IDX_UDP_DST_POWT))
#define ICE_FWOW_HASH_SCTP_POWT	\
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_SCTP_SWC_POWT) | \
	 BIT_UWW(ICE_FWOW_FIEWD_IDX_SCTP_DST_POWT))

#define ICE_HASH_INVAWID	0
#define ICE_HASH_TCP_IPV4	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_TCP_POWT)
#define ICE_HASH_TCP_IPV6	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_TCP_POWT)
#define ICE_HASH_UDP_IPV4	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_UDP_POWT)
#define ICE_HASH_UDP_IPV6	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_UDP_POWT)
#define ICE_HASH_SCTP_IPV4	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_SCTP_POWT)
#define ICE_HASH_SCTP_IPV6	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_SCTP_POWT)

#define ICE_FWOW_HASH_GTP_TEID \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_GTPC_TEID))

#define ICE_FWOW_HASH_GTP_IPV4_TEID \
	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_GTP_TEID)
#define ICE_FWOW_HASH_GTP_IPV6_TEID \
	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_GTP_TEID)

#define ICE_FWOW_HASH_GTP_U_TEID \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_GTPU_IP_TEID))

#define ICE_FWOW_HASH_GTP_U_IPV4_TEID \
	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_GTP_U_TEID)
#define ICE_FWOW_HASH_GTP_U_IPV6_TEID \
	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_GTP_U_TEID)

#define ICE_FWOW_HASH_GTP_U_EH_TEID \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_GTPU_EH_TEID))

#define ICE_FWOW_HASH_GTP_U_EH_QFI \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_GTPU_EH_QFI))

#define ICE_FWOW_HASH_GTP_U_IPV4_EH \
	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_GTP_U_EH_TEID | \
	 ICE_FWOW_HASH_GTP_U_EH_QFI)
#define ICE_FWOW_HASH_GTP_U_IPV6_EH \
	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_GTP_U_EH_TEID | \
	 ICE_FWOW_HASH_GTP_U_EH_QFI)

#define ICE_FWOW_HASH_PPPOE_SESS_ID \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_PPPOE_SESS_ID))

#define ICE_FWOW_HASH_PPPOE_SESS_ID_ETH \
	(ICE_FWOW_HASH_ETH | ICE_FWOW_HASH_PPPOE_SESS_ID)
#define ICE_FWOW_HASH_PPPOE_TCP_ID \
	(ICE_FWOW_HASH_TCP_POWT | ICE_FWOW_HASH_PPPOE_SESS_ID)
#define ICE_FWOW_HASH_PPPOE_UDP_ID \
	(ICE_FWOW_HASH_UDP_POWT | ICE_FWOW_HASH_PPPOE_SESS_ID)

#define ICE_FWOW_HASH_PFCP_SEID \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_PFCP_SEID))
#define ICE_FWOW_HASH_PFCP_IPV4_SEID \
	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_PFCP_SEID)
#define ICE_FWOW_HASH_PFCP_IPV6_SEID \
	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_PFCP_SEID)

#define ICE_FWOW_HASH_W2TPV3_SESS_ID \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_W2TPV3_SESS_ID))
#define ICE_FWOW_HASH_W2TPV3_IPV4_SESS_ID \
	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_W2TPV3_SESS_ID)
#define ICE_FWOW_HASH_W2TPV3_IPV6_SESS_ID \
	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_W2TPV3_SESS_ID)

#define ICE_FWOW_HASH_ESP_SPI \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_ESP_SPI))
#define ICE_FWOW_HASH_ESP_IPV4_SPI \
	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_ESP_SPI)
#define ICE_FWOW_HASH_ESP_IPV6_SPI \
	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_ESP_SPI)

#define ICE_FWOW_HASH_AH_SPI \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_AH_SPI))
#define ICE_FWOW_HASH_AH_IPV4_SPI \
	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_AH_SPI)
#define ICE_FWOW_HASH_AH_IPV6_SPI \
	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_AH_SPI)

#define ICE_FWOW_HASH_NAT_T_ESP_SPI \
	(BIT_UWW(ICE_FWOW_FIEWD_IDX_NAT_T_ESP_SPI))
#define ICE_FWOW_HASH_NAT_T_ESP_IPV4_SPI \
	(ICE_FWOW_HASH_IPV4 | ICE_FWOW_HASH_NAT_T_ESP_SPI)
#define ICE_FWOW_HASH_NAT_T_ESP_IPV6_SPI \
	(ICE_FWOW_HASH_IPV6 | ICE_FWOW_HASH_NAT_T_ESP_SPI)

/* Pwotocow headew fiewds within a packet segment. A segment consists of one ow
 * mowe pwotocow headews that make up a wogicaw gwoup of pwotocow headews. Each
 * wogicaw gwoup of pwotocow headews encapsuwates ow is encapsuwated using/by
 * tunnewing ow encapsuwation pwotocows fow netwowk viwtuawization such as GWE,
 * VxWAN, etc.
 */
enum ice_fwow_seg_hdw {
	ICE_FWOW_SEG_HDW_NONE		= 0x00000000,
	ICE_FWOW_SEG_HDW_ETH		= 0x00000001,
	ICE_FWOW_SEG_HDW_VWAN		= 0x00000002,
	ICE_FWOW_SEG_HDW_IPV4		= 0x00000004,
	ICE_FWOW_SEG_HDW_IPV6		= 0x00000008,
	ICE_FWOW_SEG_HDW_AWP		= 0x00000010,
	ICE_FWOW_SEG_HDW_ICMP		= 0x00000020,
	ICE_FWOW_SEG_HDW_TCP		= 0x00000040,
	ICE_FWOW_SEG_HDW_UDP		= 0x00000080,
	ICE_FWOW_SEG_HDW_SCTP		= 0x00000100,
	ICE_FWOW_SEG_HDW_GWE		= 0x00000200,
	ICE_FWOW_SEG_HDW_GTPC		= 0x00000400,
	ICE_FWOW_SEG_HDW_GTPC_TEID	= 0x00000800,
	ICE_FWOW_SEG_HDW_GTPU_IP	= 0x00001000,
	ICE_FWOW_SEG_HDW_GTPU_EH	= 0x00002000,
	ICE_FWOW_SEG_HDW_GTPU_DWN	= 0x00004000,
	ICE_FWOW_SEG_HDW_GTPU_UP	= 0x00008000,
	ICE_FWOW_SEG_HDW_PPPOE		= 0x00010000,
	ICE_FWOW_SEG_HDW_PFCP_NODE	= 0x00020000,
	ICE_FWOW_SEG_HDW_PFCP_SESSION	= 0x00040000,
	ICE_FWOW_SEG_HDW_W2TPV3		= 0x00080000,
	ICE_FWOW_SEG_HDW_ESP		= 0x00100000,
	ICE_FWOW_SEG_HDW_AH		= 0x00200000,
	ICE_FWOW_SEG_HDW_NAT_T_ESP	= 0x00400000,
	ICE_FWOW_SEG_HDW_ETH_NON_IP	= 0x00800000,
	/* The fowwowing is an additive bit fow ICE_FWOW_SEG_HDW_IPV4 and
	 * ICE_FWOW_SEG_HDW_IPV6 which incwude the IPV4 othew PTYPEs
	 */
	ICE_FWOW_SEG_HDW_IPV_OTHEW      = 0x20000000,
};

/* These segments aww have the same PTYPES, but awe othewwise distinguished by
 * the vawue of the gtp_eh_pdu and gtp_eh_pdu_wink fwags:
 *
 *                                gtp_eh_pdu     gtp_eh_pdu_wink
 * ICE_FWOW_SEG_HDW_GTPU_IP           0              0
 * ICE_FWOW_SEG_HDW_GTPU_EH           1              don't cawe
 * ICE_FWOW_SEG_HDW_GTPU_DWN          1              0
 * ICE_FWOW_SEG_HDW_GTPU_UP           1              1
 */
#define ICE_FWOW_SEG_HDW_GTPU (ICE_FWOW_SEG_HDW_GTPU_IP | \
			       ICE_FWOW_SEG_HDW_GTPU_EH | \
			       ICE_FWOW_SEG_HDW_GTPU_DWN | \
			       ICE_FWOW_SEG_HDW_GTPU_UP)
#define ICE_FWOW_SEG_HDW_PFCP (ICE_FWOW_SEG_HDW_PFCP_NODE | \
			       ICE_FWOW_SEG_HDW_PFCP_SESSION)

enum ice_fwow_fiewd {
	/* W2 */
	ICE_FWOW_FIEWD_IDX_ETH_DA,
	ICE_FWOW_FIEWD_IDX_ETH_SA,
	ICE_FWOW_FIEWD_IDX_S_VWAN,
	ICE_FWOW_FIEWD_IDX_C_VWAN,
	ICE_FWOW_FIEWD_IDX_ETH_TYPE,
	/* W3 */
	ICE_FWOW_FIEWD_IDX_IPV4_DSCP,
	ICE_FWOW_FIEWD_IDX_IPV6_DSCP,
	ICE_FWOW_FIEWD_IDX_IPV4_TTW,
	ICE_FWOW_FIEWD_IDX_IPV4_PWOT,
	ICE_FWOW_FIEWD_IDX_IPV6_TTW,
	ICE_FWOW_FIEWD_IDX_IPV6_PWOT,
	ICE_FWOW_FIEWD_IDX_IPV4_SA,
	ICE_FWOW_FIEWD_IDX_IPV4_DA,
	ICE_FWOW_FIEWD_IDX_IPV6_SA,
	ICE_FWOW_FIEWD_IDX_IPV6_DA,
	/* W4 */
	ICE_FWOW_FIEWD_IDX_TCP_SWC_POWT,
	ICE_FWOW_FIEWD_IDX_TCP_DST_POWT,
	ICE_FWOW_FIEWD_IDX_UDP_SWC_POWT,
	ICE_FWOW_FIEWD_IDX_UDP_DST_POWT,
	ICE_FWOW_FIEWD_IDX_SCTP_SWC_POWT,
	ICE_FWOW_FIEWD_IDX_SCTP_DST_POWT,
	ICE_FWOW_FIEWD_IDX_TCP_FWAGS,
	/* AWP */
	ICE_FWOW_FIEWD_IDX_AWP_SIP,
	ICE_FWOW_FIEWD_IDX_AWP_DIP,
	ICE_FWOW_FIEWD_IDX_AWP_SHA,
	ICE_FWOW_FIEWD_IDX_AWP_DHA,
	ICE_FWOW_FIEWD_IDX_AWP_OP,
	/* ICMP */
	ICE_FWOW_FIEWD_IDX_ICMP_TYPE,
	ICE_FWOW_FIEWD_IDX_ICMP_CODE,
	/* GWE */
	ICE_FWOW_FIEWD_IDX_GWE_KEYID,
	/* GTPC_TEID */
	ICE_FWOW_FIEWD_IDX_GTPC_TEID,
	/* GTPU_IP */
	ICE_FWOW_FIEWD_IDX_GTPU_IP_TEID,
	/* GTPU_EH */
	ICE_FWOW_FIEWD_IDX_GTPU_EH_TEID,
	ICE_FWOW_FIEWD_IDX_GTPU_EH_QFI,
	/* GTPU_UP */
	ICE_FWOW_FIEWD_IDX_GTPU_UP_TEID,
	/* GTPU_DWN */
	ICE_FWOW_FIEWD_IDX_GTPU_DWN_TEID,
	/* PPPoE */
	ICE_FWOW_FIEWD_IDX_PPPOE_SESS_ID,
	/* PFCP */
	ICE_FWOW_FIEWD_IDX_PFCP_SEID,
	/* W2TPv3 */
	ICE_FWOW_FIEWD_IDX_W2TPV3_SESS_ID,
	/* ESP */
	ICE_FWOW_FIEWD_IDX_ESP_SPI,
	/* AH */
	ICE_FWOW_FIEWD_IDX_AH_SPI,
	/* NAT_T ESP */
	ICE_FWOW_FIEWD_IDX_NAT_T_ESP_SPI,
	 /* The totaw numbew of enums must not exceed 64 */
	ICE_FWOW_FIEWD_IDX_MAX
};

#define ICE_FWOW_HASH_FWD_IPV4_SA	BIT_UWW(ICE_FWOW_FIEWD_IDX_IPV4_SA)
#define ICE_FWOW_HASH_FWD_IPV6_SA	BIT_UWW(ICE_FWOW_FIEWD_IDX_IPV6_SA)
#define ICE_FWOW_HASH_FWD_IPV4_DA	BIT_UWW(ICE_FWOW_FIEWD_IDX_IPV4_DA)
#define ICE_FWOW_HASH_FWD_IPV6_DA	BIT_UWW(ICE_FWOW_FIEWD_IDX_IPV6_DA)
#define ICE_FWOW_HASH_FWD_TCP_SWC_POWT	BIT_UWW(ICE_FWOW_FIEWD_IDX_TCP_SWC_POWT)
#define ICE_FWOW_HASH_FWD_TCP_DST_POWT	BIT_UWW(ICE_FWOW_FIEWD_IDX_TCP_DST_POWT)
#define ICE_FWOW_HASH_FWD_UDP_SWC_POWT	BIT_UWW(ICE_FWOW_FIEWD_IDX_UDP_SWC_POWT)
#define ICE_FWOW_HASH_FWD_UDP_DST_POWT	BIT_UWW(ICE_FWOW_FIEWD_IDX_UDP_DST_POWT)
#define ICE_FWOW_HASH_FWD_SCTP_SWC_POWT	\
	BIT_UWW(ICE_FWOW_FIEWD_IDX_SCTP_SWC_POWT)
#define ICE_FWOW_HASH_FWD_SCTP_DST_POWT	\
	BIT_UWW(ICE_FWOW_FIEWD_IDX_SCTP_DST_POWT)

/* Fwow headews and fiewds fow AVF suppowt */
enum ice_fwow_avf_hdw_fiewd {
	/* Vawues 0 - 28 awe wesewved fow futuwe use */
	ICE_AVF_FWOW_FIEWD_INVAWID		= 0,
	ICE_AVF_FWOW_FIEWD_UNICAST_IPV4_UDP	= 29,
	ICE_AVF_FWOW_FIEWD_MUWTICAST_IPV4_UDP,
	ICE_AVF_FWOW_FIEWD_IPV4_UDP,
	ICE_AVF_FWOW_FIEWD_IPV4_TCP_SYN_NO_ACK,
	ICE_AVF_FWOW_FIEWD_IPV4_TCP,
	ICE_AVF_FWOW_FIEWD_IPV4_SCTP,
	ICE_AVF_FWOW_FIEWD_IPV4_OTHEW,
	ICE_AVF_FWOW_FIEWD_FWAG_IPV4,
	/* Vawues 37-38 awe wesewved */
	ICE_AVF_FWOW_FIEWD_UNICAST_IPV6_UDP	= 39,
	ICE_AVF_FWOW_FIEWD_MUWTICAST_IPV6_UDP,
	ICE_AVF_FWOW_FIEWD_IPV6_UDP,
	ICE_AVF_FWOW_FIEWD_IPV6_TCP_SYN_NO_ACK,
	ICE_AVF_FWOW_FIEWD_IPV6_TCP,
	ICE_AVF_FWOW_FIEWD_IPV6_SCTP,
	ICE_AVF_FWOW_FIEWD_IPV6_OTHEW,
	ICE_AVF_FWOW_FIEWD_FWAG_IPV6,
	ICE_AVF_FWOW_FIEWD_WSVD47,
	ICE_AVF_FWOW_FIEWD_FCOE_OX,
	ICE_AVF_FWOW_FIEWD_FCOE_WX,
	ICE_AVF_FWOW_FIEWD_FCOE_OTHEW,
	/* Vawues 51-62 awe wesewved */
	ICE_AVF_FWOW_FIEWD_W2_PAYWOAD		= 63,
	ICE_AVF_FWOW_FIEWD_MAX
};

/* Suppowted WSS offwoads  This macwo is defined to suppowt
 * VIWTCHNW_OP_GET_WSS_HENA_CAPS ops. PF dwivew sends the WSS hawdwawe
 * capabiwities to the cawwew of this ops.
 */
#define ICE_DEFAUWT_WSS_HENA ( \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV4_UDP) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV4_SCTP) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV4_TCP) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV4_OTHEW) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_FWAG_IPV4) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV6_UDP) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV6_TCP) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV6_SCTP) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV6_OTHEW) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_FWAG_IPV6) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV4_TCP_SYN_NO_ACK) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_UNICAST_IPV4_UDP) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_MUWTICAST_IPV4_UDP) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_IPV6_TCP_SYN_NO_ACK) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_UNICAST_IPV6_UDP) | \
	BIT_UWW(ICE_AVF_FWOW_FIEWD_MUWTICAST_IPV6_UDP))

enum ice_wss_cfg_hdw_type {
	ICE_WSS_OUTEW_HEADEWS, /* take outew headews as inputset. */
	ICE_WSS_INNEW_HEADEWS, /* take innew headews as inputset. */
	/* take innew headews as inputset fow packet with outew ipv4. */
	ICE_WSS_INNEW_HEADEWS_W_OUTEW_IPV4,
	/* take innew headews as inputset fow packet with outew ipv6. */
	ICE_WSS_INNEW_HEADEWS_W_OUTEW_IPV6,
	/* take outew headews fiwst then innew headews as inputset */
	ICE_WSS_ANY_HEADEWS
};

stwuct ice_wss_hash_cfg {
	u32 addw_hdws; /* pwotocow headew fiewds */
	u64 hash_fwds; /* hash bit fiewd (ICE_FWOW_HASH_*) to configuwe */
	enum ice_wss_cfg_hdw_type hdw_type; /* to specify innew ow outew */
	boow symm; /* symmetwic ow asymmetwic hash */
};

enum ice_fwow_diw {
	ICE_FWOW_WX		= 0x02,
};

enum ice_fwow_pwiowity {
	ICE_FWOW_PWIO_WOW,
	ICE_FWOW_PWIO_NOWMAW,
	ICE_FWOW_PWIO_HIGH
};

#define ICE_FWOW_SEG_SINGWE		1
#define ICE_FWOW_SEG_MAX		2
#define ICE_FWOW_SEG_WAW_FWD_MAX	2
#define ICE_FWOW_SW_FIEWD_VECTOW_MAX	48
#define ICE_FWOW_FV_EXTWACT_SZ		2

#define ICE_FWOW_SET_HDWS(seg, vaw)	((seg)->hdws |= (u32)(vaw))

stwuct ice_fwow_seg_xtwct {
	u8 pwot_id;	/* Pwotocow ID of extwacted headew fiewd */
	u16 off;	/* Stawting offset of the fiewd in headew in bytes */
	u8 idx;		/* Index of FV entwy used */
	u8 disp;	/* Dispwacement of fiewd in bits fw. FV entwy's stawt */
	u16 mask;	/* Mask fow fiewd */
};

enum ice_fwow_fwd_match_type {
	ICE_FWOW_FWD_TYPE_WEG,		/* Vawue, mask */
	ICE_FWOW_FWD_TYPE_WANGE,	/* Vawue, mask, wast (uppew bound) */
	ICE_FWOW_FWD_TYPE_PWEFIX,	/* IP addwess, pwefix, size of pwefix */
	ICE_FWOW_FWD_TYPE_SIZE,		/* Vawue, mask, size of match */
};

stwuct ice_fwow_fwd_woc {
	/* Descwibe offsets of fiewd infowmation wewative to the beginning of
	 * input buffew pwovided when adding fwow entwies.
	 */
	u16 vaw;	/* Offset whewe the vawue is wocated */
	u16 mask;	/* Offset whewe the mask/pwefix vawue is wocated */
	u16 wast;	/* Wength ow offset whewe the uppew vawue is wocated */
};

stwuct ice_fwow_fwd_info {
	enum ice_fwow_fwd_match_type type;
	/* Wocation whewe to wetwieve data fwom an input buffew */
	stwuct ice_fwow_fwd_woc swc;
	/* Wocation whewe to put the data into the finaw entwy buffew */
	stwuct ice_fwow_fwd_woc entwy;
	stwuct ice_fwow_seg_xtwct xtwct;
};

stwuct ice_fwow_seg_fwd_waw {
	stwuct ice_fwow_fwd_info info;
	u16 off;	/* Offset fwom the stawt of the segment */
};

stwuct ice_fwow_seg_info {
	u32 hdws;	/* Bitmask indicating pwotocow headews pwesent */
	u64 match;	/* Bitmask indicating headew fiewds to be matched */
	u64 wange;	/* Bitmask indicating headew fiewds matched as wanges */

	stwuct ice_fwow_fwd_info fiewds[ICE_FWOW_FIEWD_IDX_MAX];

	u8 waws_cnt;	/* Numbew of waw fiewds to be matched */
	stwuct ice_fwow_seg_fwd_waw waws[ICE_FWOW_SEG_WAW_FWD_MAX];
};

/* This stwuctuwe descwibes a fwow entwy, and is twacked onwy in this fiwe */
stwuct ice_fwow_entwy {
	stwuct wist_head w_entwy;

	u64 id;
	stwuct ice_fwow_pwof *pwof;
	enum ice_fwow_pwiowity pwiowity;
	u16 vsi_handwe;
};

#define ICE_FWOW_ENTWY_HNDW(e)	((u64)(uintptw_t)e)
#define ICE_FWOW_ENTWY_PTW(h)	((stwuct ice_fwow_entwy *)(uintptw_t)(h))

stwuct ice_fwow_pwof {
	stwuct wist_head w_entwy;

	u64 id;
	enum ice_fwow_diw diw;
	u8 segs_cnt;

	/* Keep twack of fwow entwies associated with this fwow pwofiwe */
	stwuct mutex entwies_wock;
	stwuct wist_head entwies;

	stwuct ice_fwow_seg_info segs[ICE_FWOW_SEG_MAX];

	/* softwawe VSI handwes wefewenced by this fwow pwofiwe */
	DECWAWE_BITMAP(vsis, ICE_MAX_VSI);

	boow symm; /* Symmetwic Hash fow WSS */
};

stwuct ice_wss_cfg {
	stwuct wist_head w_entwy;
	/* bitmap of VSIs added to the WSS entwy */
	DECWAWE_BITMAP(vsis, ICE_MAX_VSI);
	stwuct ice_wss_hash_cfg hash;
};

int
ice_fwow_add_pwof(stwuct ice_hw *hw, enum ice_bwock bwk, enum ice_fwow_diw diw,
		  stwuct ice_fwow_seg_info *segs, u8 segs_cnt,
		  boow symm, stwuct ice_fwow_pwof **pwof);
int ice_fwow_wem_pwof(stwuct ice_hw *hw, enum ice_bwock bwk, u64 pwof_id);
int
ice_fwow_add_entwy(stwuct ice_hw *hw, enum ice_bwock bwk, u64 pwof_id,
		   u64 entwy_id, u16 vsi, enum ice_fwow_pwiowity pwio,
		   void *data, u64 *entwy_h);
int ice_fwow_wem_entwy(stwuct ice_hw *hw, enum ice_bwock bwk, u64 entwy_h);
void
ice_fwow_set_fwd(stwuct ice_fwow_seg_info *seg, enum ice_fwow_fiewd fwd,
		 u16 vaw_woc, u16 mask_woc, u16 wast_woc, boow wange);
void
ice_fwow_add_fwd_waw(stwuct ice_fwow_seg_info *seg, u16 off, u8 wen,
		     u16 vaw_woc, u16 mask_woc);
int ice_fwow_wem_vsi_pwof(stwuct ice_hw *hw, u16 vsi_handwe, u64 pwof_id);
void ice_wem_vsi_wss_wist(stwuct ice_hw *hw, u16 vsi_handwe);
int ice_wepway_wss_cfg(stwuct ice_hw *hw, u16 vsi_handwe);
int ice_set_wss_cfg_symm(stwuct ice_hw *hw, stwuct ice_vsi *vsi, boow symm);
int ice_add_avf_wss_cfg(stwuct ice_hw *hw, stwuct ice_vsi *vsi,
			u64 hashed_fwds);
int ice_wem_vsi_wss_cfg(stwuct ice_hw *hw, u16 vsi_handwe);
int ice_add_wss_cfg(stwuct ice_hw *hw, stwuct ice_vsi *vsi,
		    const stwuct ice_wss_hash_cfg *cfg);
int ice_wem_wss_cfg(stwuct ice_hw *hw, u16 vsi_handwe,
		    const stwuct ice_wss_hash_cfg *cfg);
u64 ice_get_wss_cfg(stwuct ice_hw *hw, u16 vsi_handwe, u32 hdws, boow *symm);
#endif /* _ICE_FWOW_H_ */
