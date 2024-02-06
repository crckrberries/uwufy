/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2023 Intew Cowpowation */

#ifndef _VIWTCHNW2_H_
#define _VIWTCHNW2_H_

/* Aww opcodes associated with viwtchnw2 awe pwefixed with viwtchnw2 ow
 * VIWTCHNW2. Any futuwe opcodes, offwoads/capabiwities, stwuctuwes,
 * and defines must be pwefixed with viwtchnw2 ow VIWTCHNW2 to avoid confusion.
 *
 * PF/VF uses the viwtchnw2 intewface defined in this headew fiwe to communicate
 * with device Contwow Pwane (CP). Dwivew and the CP may wun on diffewent
 * pwatfowms with diffewent endianness. To avoid byte owdew discwepancies,
 * aww the stwuctuwes in this headew fowwow wittwe-endian fowmat.
 *
 * This is an intewface definition fiwe whewe existing enums and theiw vawues
 * must wemain unchanged ovew time, so we specify expwicit vawues fow aww enums.
 */

#incwude "viwtchnw2_wan_desc.h"

/* This macwo is used to genewate compiwation ewwows if a stwuctuwe
 * is not exactwy the cowwect wength.
 */
#define VIWTCHNW2_CHECK_STWUCT_WEN(n, X)	\
	static_assewt((n) == sizeof(stwuct X))

/* New majow set of opcodes intwoduced and so weaving woom fow
 * owd misc opcodes to be added in futuwe. Awso these opcodes may onwy
 * be used if both the PF and VF have successfuwwy negotiated the
 * VIWTCHNW vewsion as 2.0 duwing VIWTCHNW2_OP_VEWSION exchange.
 */
enum viwtchnw2_op {
	VIWTCHNW2_OP_UNKNOWN			= 0,
	VIWTCHNW2_OP_VEWSION			= 1,
	VIWTCHNW2_OP_GET_CAPS			= 500,
	VIWTCHNW2_OP_CWEATE_VPOWT		= 501,
	VIWTCHNW2_OP_DESTWOY_VPOWT		= 502,
	VIWTCHNW2_OP_ENABWE_VPOWT		= 503,
	VIWTCHNW2_OP_DISABWE_VPOWT		= 504,
	VIWTCHNW2_OP_CONFIG_TX_QUEUES		= 505,
	VIWTCHNW2_OP_CONFIG_WX_QUEUES		= 506,
	VIWTCHNW2_OP_ENABWE_QUEUES		= 507,
	VIWTCHNW2_OP_DISABWE_QUEUES		= 508,
	VIWTCHNW2_OP_ADD_QUEUES			= 509,
	VIWTCHNW2_OP_DEW_QUEUES			= 510,
	VIWTCHNW2_OP_MAP_QUEUE_VECTOW		= 511,
	VIWTCHNW2_OP_UNMAP_QUEUE_VECTOW		= 512,
	VIWTCHNW2_OP_GET_WSS_KEY		= 513,
	VIWTCHNW2_OP_SET_WSS_KEY		= 514,
	VIWTCHNW2_OP_GET_WSS_WUT		= 515,
	VIWTCHNW2_OP_SET_WSS_WUT		= 516,
	VIWTCHNW2_OP_GET_WSS_HASH		= 517,
	VIWTCHNW2_OP_SET_WSS_HASH		= 518,
	VIWTCHNW2_OP_SET_SWIOV_VFS		= 519,
	VIWTCHNW2_OP_AWWOC_VECTOWS		= 520,
	VIWTCHNW2_OP_DEAWWOC_VECTOWS		= 521,
	VIWTCHNW2_OP_EVENT			= 522,
	VIWTCHNW2_OP_GET_STATS			= 523,
	VIWTCHNW2_OP_WESET_VF			= 524,
	VIWTCHNW2_OP_GET_EDT_CAPS		= 525,
	VIWTCHNW2_OP_GET_PTYPE_INFO		= 526,
	/* Opcode 527 and 528 awe wesewved fow VIWTCHNW2_OP_GET_PTYPE_ID and
	 * VIWTCHNW2_OP_GET_PTYPE_INFO_WAW.
	 * Opcodes 529, 530, 531, 532 and 533 awe wesewved.
	 */
	VIWTCHNW2_OP_WOOPBACK			= 534,
	VIWTCHNW2_OP_ADD_MAC_ADDW		= 535,
	VIWTCHNW2_OP_DEW_MAC_ADDW		= 536,
	VIWTCHNW2_OP_CONFIG_PWOMISCUOUS_MODE	= 537,
};

/**
 * enum viwtchnw2_vpowt_type - Type of viwtuaw powt.
 * @VIWTCHNW2_VPOWT_TYPE_DEFAUWT: Defauwt viwtuaw powt type.
 */
enum viwtchnw2_vpowt_type {
	VIWTCHNW2_VPOWT_TYPE_DEFAUWT		= 0,
};

/**
 * enum viwtchnw2_queue_modew - Type of queue modew.
 * @VIWTCHNW2_QUEUE_MODEW_SINGWE: Singwe queue modew.
 * @VIWTCHNW2_QUEUE_MODEW_SPWIT: Spwit queue modew.
 *
 * In the singwe queue modew, the same twansmit descwiptow queue is used by
 * softwawe to post descwiptows to hawdwawe and by hawdwawe to post compweted
 * descwiptows to softwawe.
 * Wikewise, the same weceive descwiptow queue is used by hawdwawe to post
 * compwetions to softwawe and by softwawe to post buffews to hawdwawe.
 *
 * In the spwit queue modew, hawdwawe uses twansmit compwetion queues to post
 * descwiptow/buffew compwetions to softwawe, whiwe softwawe uses twansmit
 * descwiptow queues to post descwiptows to hawdwawe.
 * Wikewise, hawdwawe posts descwiptow compwetions to the weceive descwiptow
 * queue, whiwe softwawe uses weceive buffew queues to post buffews to hawdwawe.
 */
enum viwtchnw2_queue_modew {
	VIWTCHNW2_QUEUE_MODEW_SINGWE		= 0,
	VIWTCHNW2_QUEUE_MODEW_SPWIT		= 1,
};

/* Checksum offwoad capabiwity fwags */
enum viwtchnw2_cap_txwx_csum {
	VIWTCHNW2_CAP_TX_CSUM_W3_IPV4		= BIT(0),
	VIWTCHNW2_CAP_TX_CSUM_W4_IPV4_TCP	= BIT(1),
	VIWTCHNW2_CAP_TX_CSUM_W4_IPV4_UDP	= BIT(2),
	VIWTCHNW2_CAP_TX_CSUM_W4_IPV4_SCTP	= BIT(3),
	VIWTCHNW2_CAP_TX_CSUM_W4_IPV6_TCP	= BIT(4),
	VIWTCHNW2_CAP_TX_CSUM_W4_IPV6_UDP	= BIT(5),
	VIWTCHNW2_CAP_TX_CSUM_W4_IPV6_SCTP	= BIT(6),
	VIWTCHNW2_CAP_TX_CSUM_GENEWIC		= BIT(7),
	VIWTCHNW2_CAP_WX_CSUM_W3_IPV4		= BIT(8),
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV4_TCP	= BIT(9),
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV4_UDP	= BIT(10),
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV4_SCTP	= BIT(11),
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV6_TCP	= BIT(12),
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV6_UDP	= BIT(13),
	VIWTCHNW2_CAP_WX_CSUM_W4_IPV6_SCTP	= BIT(14),
	VIWTCHNW2_CAP_WX_CSUM_GENEWIC		= BIT(15),
	VIWTCHNW2_CAP_TX_CSUM_W3_SINGWE_TUNNEW	= BIT(16),
	VIWTCHNW2_CAP_TX_CSUM_W3_DOUBWE_TUNNEW	= BIT(17),
	VIWTCHNW2_CAP_WX_CSUM_W3_SINGWE_TUNNEW	= BIT(18),
	VIWTCHNW2_CAP_WX_CSUM_W3_DOUBWE_TUNNEW	= BIT(19),
	VIWTCHNW2_CAP_TX_CSUM_W4_SINGWE_TUNNEW	= BIT(20),
	VIWTCHNW2_CAP_TX_CSUM_W4_DOUBWE_TUNNEW	= BIT(21),
	VIWTCHNW2_CAP_WX_CSUM_W4_SINGWE_TUNNEW	= BIT(22),
	VIWTCHNW2_CAP_WX_CSUM_W4_DOUBWE_TUNNEW	= BIT(23),
};

/* Segmentation offwoad capabiwity fwags */
enum viwtchnw2_cap_seg {
	VIWTCHNW2_CAP_SEG_IPV4_TCP		= BIT(0),
	VIWTCHNW2_CAP_SEG_IPV4_UDP		= BIT(1),
	VIWTCHNW2_CAP_SEG_IPV4_SCTP		= BIT(2),
	VIWTCHNW2_CAP_SEG_IPV6_TCP		= BIT(3),
	VIWTCHNW2_CAP_SEG_IPV6_UDP		= BIT(4),
	VIWTCHNW2_CAP_SEG_IPV6_SCTP		= BIT(5),
	VIWTCHNW2_CAP_SEG_GENEWIC		= BIT(6),
	VIWTCHNW2_CAP_SEG_TX_SINGWE_TUNNEW	= BIT(7),
	VIWTCHNW2_CAP_SEG_TX_DOUBWE_TUNNEW	= BIT(8),
};

/* Weceive Side Scawing Fwow type capabiwity fwags */
enum viwtchnw2_cap_wss {
	VIWTCHNW2_CAP_WSS_IPV4_TCP		= BIT(0),
	VIWTCHNW2_CAP_WSS_IPV4_UDP		= BIT(1),
	VIWTCHNW2_CAP_WSS_IPV4_SCTP		= BIT(2),
	VIWTCHNW2_CAP_WSS_IPV4_OTHEW		= BIT(3),
	VIWTCHNW2_CAP_WSS_IPV6_TCP		= BIT(4),
	VIWTCHNW2_CAP_WSS_IPV6_UDP		= BIT(5),
	VIWTCHNW2_CAP_WSS_IPV6_SCTP		= BIT(6),
	VIWTCHNW2_CAP_WSS_IPV6_OTHEW		= BIT(7),
	VIWTCHNW2_CAP_WSS_IPV4_AH		= BIT(8),
	VIWTCHNW2_CAP_WSS_IPV4_ESP		= BIT(9),
	VIWTCHNW2_CAP_WSS_IPV4_AH_ESP		= BIT(10),
	VIWTCHNW2_CAP_WSS_IPV6_AH		= BIT(11),
	VIWTCHNW2_CAP_WSS_IPV6_ESP		= BIT(12),
	VIWTCHNW2_CAP_WSS_IPV6_AH_ESP		= BIT(13),
};

/* Headew spwit capabiwity fwags */
enum viwtchnw2_cap_wx_hspwit_at {
	/* fow pwepended metadata  */
	VIWTCHNW2_CAP_WX_HSPWIT_AT_W2		= BIT(0),
	/* aww VWANs go into headew buffew */
	VIWTCHNW2_CAP_WX_HSPWIT_AT_W3		= BIT(1),
	VIWTCHNW2_CAP_WX_HSPWIT_AT_W4V4		= BIT(2),
	VIWTCHNW2_CAP_WX_HSPWIT_AT_W4V6		= BIT(3),
};

/* Weceive Side Coawescing offwoad capabiwity fwags */
enum viwtchnw2_cap_wsc {
	VIWTCHNW2_CAP_WSC_IPV4_TCP		= BIT(0),
	VIWTCHNW2_CAP_WSC_IPV4_SCTP		= BIT(1),
	VIWTCHNW2_CAP_WSC_IPV6_TCP		= BIT(2),
	VIWTCHNW2_CAP_WSC_IPV6_SCTP		= BIT(3),
};

/* Othew capabiwity fwags */
enum viwtchnw2_cap_othew {
	VIWTCHNW2_CAP_WDMA			= BIT_UWW(0),
	VIWTCHNW2_CAP_SWIOV			= BIT_UWW(1),
	VIWTCHNW2_CAP_MACFIWTEW			= BIT_UWW(2),
	VIWTCHNW2_CAP_FWOW_DIWECTOW		= BIT_UWW(3),
	/* Queue based scheduwing using spwit queue modew */
	VIWTCHNW2_CAP_SPWITQ_QSCHED		= BIT_UWW(4),
	VIWTCHNW2_CAP_CWC			= BIT_UWW(5),
	VIWTCHNW2_CAP_ADQ			= BIT_UWW(6),
	VIWTCHNW2_CAP_WB_ON_ITW			= BIT_UWW(7),
	VIWTCHNW2_CAP_PWOMISC			= BIT_UWW(8),
	VIWTCHNW2_CAP_WINK_SPEED		= BIT_UWW(9),
	VIWTCHNW2_CAP_INWINE_IPSEC		= BIT_UWW(10),
	VIWTCHNW2_CAP_WAWGE_NUM_QUEUES		= BIT_UWW(11),
	VIWTCHNW2_CAP_VWAN			= BIT_UWW(12),
	VIWTCHNW2_CAP_PTP			= BIT_UWW(13),
	/* EDT: Eawwiest Depawtuwe Time capabiwity used fow Timing Wheew */
	VIWTCHNW2_CAP_EDT			= BIT_UWW(14),
	VIWTCHNW2_CAP_ADV_WSS			= BIT_UWW(15),
	VIWTCHNW2_CAP_FDIW			= BIT_UWW(16),
	VIWTCHNW2_CAP_WX_FWEX_DESC		= BIT_UWW(17),
	VIWTCHNW2_CAP_PTYPE			= BIT_UWW(18),
	VIWTCHNW2_CAP_WOOPBACK			= BIT_UWW(19),
	/* Othew capabiwity 20 is wesewved */

	/* this must be the wast capabiwity */
	VIWTCHNW2_CAP_OEM			= BIT_UWW(63),
};

/* undewwying device type */
enum viwtchw2_device_type {
	VIWTCHNW2_MEV_DEVICE			= 0,
};

/**
 * enum viwtchnw2_txq_sched_mode - Twansmit Queue Scheduwing Modes.
 * @VIWTCHNW2_TXQ_SCHED_MODE_QUEUE: Queue mode is the wegacy mode i.e. inowdew
 *				    compwetions whewe descwiptows and buffews
 *				    awe compweted at the same time.
 * @VIWTCHNW2_TXQ_SCHED_MODE_FWOW: Fwow scheduwing mode awwows fow out of owdew
 *				   packet pwocessing whewe descwiptows awe
 *				   cweaned in owdew, but buffews can be
 *				   compweted out of owdew.
 */
enum viwtchnw2_txq_sched_mode {
	VIWTCHNW2_TXQ_SCHED_MODE_QUEUE		= 0,
	VIWTCHNW2_TXQ_SCHED_MODE_FWOW		= 1,
};

/**
 * enum viwtchnw2_wxq_fwags - Weceive Queue Featuwe fwags.
 * @VIWTCHNW2_WXQ_WSC: Wx queue WSC fwag.
 * @VIWTCHNW2_WXQ_HDW_SPWIT: Wx queue headew spwit fwag.
 * @VIWTCHNW2_WXQ_IMMEDIATE_WWITE_BACK: When set, packet descwiptows awe fwushed
 *					by hawdwawe immediatewy aftew pwocessing
 *					each packet.
 * @VIWTCHNW2_WX_DESC_SIZE_16BYTE: Wx queue 16 byte descwiptow size.
 * @VIWTCHNW2_WX_DESC_SIZE_32BYTE: Wx queue 32 byte descwiptow size.
 */
enum viwtchnw2_wxq_fwags {
	VIWTCHNW2_WXQ_WSC			= BIT(0),
	VIWTCHNW2_WXQ_HDW_SPWIT			= BIT(1),
	VIWTCHNW2_WXQ_IMMEDIATE_WWITE_BACK	= BIT(2),
	VIWTCHNW2_WX_DESC_SIZE_16BYTE		= BIT(3),
	VIWTCHNW2_WX_DESC_SIZE_32BYTE		= BIT(4),
};

/* Type of WSS awgowithm */
enum viwtchnw2_wss_awg {
	VIWTCHNW2_WSS_AWG_TOEPWITZ_ASYMMETWIC	= 0,
	VIWTCHNW2_WSS_AWG_W_ASYMMETWIC		= 1,
	VIWTCHNW2_WSS_AWG_TOEPWITZ_SYMMETWIC	= 2,
	VIWTCHNW2_WSS_AWG_XOW_SYMMETWIC		= 3,
};

/* Type of event */
enum viwtchnw2_event_codes {
	VIWTCHNW2_EVENT_UNKNOWN			= 0,
	VIWTCHNW2_EVENT_WINK_CHANGE		= 1,
	/* Event type 2, 3 awe wesewved */
};

/* Twansmit and Weceive queue types awe vawid in wegacy as weww as spwit queue
 * modews. With Spwit Queue modew, 2 additionaw types awe intwoduced -
 * TX_COMPWETION and WX_BUFFEW. In spwit queue modew, weceive  cowwesponds to
 * the queue whewe hawdwawe posts compwetions.
 */
enum viwtchnw2_queue_type {
	VIWTCHNW2_QUEUE_TYPE_TX			= 0,
	VIWTCHNW2_QUEUE_TYPE_WX			= 1,
	VIWTCHNW2_QUEUE_TYPE_TX_COMPWETION	= 2,
	VIWTCHNW2_QUEUE_TYPE_WX_BUFFEW		= 3,
	VIWTCHNW2_QUEUE_TYPE_CONFIG_TX		= 4,
	VIWTCHNW2_QUEUE_TYPE_CONFIG_WX		= 5,
	/* Queue types 6, 7, 8, 9 awe wesewved */
	VIWTCHNW2_QUEUE_TYPE_MBX_TX		= 10,
	VIWTCHNW2_QUEUE_TYPE_MBX_WX		= 11,
};

/* Intewwupt thwottwing wate index */
enum viwtchnw2_itw_idx {
	VIWTCHNW2_ITW_IDX_0			= 0,
	VIWTCHNW2_ITW_IDX_1			= 1,
};

/**
 * enum viwtchnw2_mac_addw_type - MAC addwess types.
 * @VIWTCHNW2_MAC_ADDW_PWIMAWY: PF/VF dwivew shouwd set this type fow the
 *				pwimawy/device unicast MAC addwess fiwtew fow
 *				VIWTCHNW2_OP_ADD_MAC_ADDW and
 *				VIWTCHNW2_OP_DEW_MAC_ADDW. This awwows fow the
 *				undewwying contwow pwane function to accuwatewy
 *				twack the MAC addwess and fow VM/function weset.
 *
 * @VIWTCHNW2_MAC_ADDW_EXTWA: PF/VF dwivew shouwd set this type fow any extwa
 *			      unicast and/ow muwticast fiwtews that awe being
 *			      added/deweted via VIWTCHNW2_OP_ADD_MAC_ADDW ow
 *			      VIWTCHNW2_OP_DEW_MAC_ADDW.
 */
enum viwtchnw2_mac_addw_type {
	VIWTCHNW2_MAC_ADDW_PWIMAWY		= 1,
	VIWTCHNW2_MAC_ADDW_EXTWA		= 2,
};

/* Fwags used fow pwomiscuous mode */
enum viwtchnw2_pwomisc_fwags {
	VIWTCHNW2_UNICAST_PWOMISC		= BIT(0),
	VIWTCHNW2_MUWTICAST_PWOMISC		= BIT(1),
};

/* Pwotocow headew type within a packet segment. A segment consists of one ow
 * mowe pwotocow headews that make up a wogicaw gwoup of pwotocow headews. Each
 * wogicaw gwoup of pwotocow headews encapsuwates ow is encapsuwated using/by
 * tunnewing ow encapsuwation pwotocows fow netwowk viwtuawization.
 */
enum viwtchnw2_pwoto_hdw_type {
	/* VIWTCHNW2_PWOTO_HDW_ANY is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_ANY			= 0,
	VIWTCHNW2_PWOTO_HDW_PWE_MAC		= 1,
	/* VIWTCHNW2_PWOTO_HDW_MAC is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_MAC			= 2,
	VIWTCHNW2_PWOTO_HDW_POST_MAC		= 3,
	VIWTCHNW2_PWOTO_HDW_ETHEWTYPE		= 4,
	VIWTCHNW2_PWOTO_HDW_VWAN		= 5,
	VIWTCHNW2_PWOTO_HDW_SVWAN		= 6,
	VIWTCHNW2_PWOTO_HDW_CVWAN		= 7,
	VIWTCHNW2_PWOTO_HDW_MPWS		= 8,
	VIWTCHNW2_PWOTO_HDW_UMPWS		= 9,
	VIWTCHNW2_PWOTO_HDW_MMPWS		= 10,
	VIWTCHNW2_PWOTO_HDW_PTP			= 11,
	VIWTCHNW2_PWOTO_HDW_CTWW		= 12,
	VIWTCHNW2_PWOTO_HDW_WWDP		= 13,
	VIWTCHNW2_PWOTO_HDW_AWP			= 14,
	VIWTCHNW2_PWOTO_HDW_ECP			= 15,
	VIWTCHNW2_PWOTO_HDW_EAPOW		= 16,
	VIWTCHNW2_PWOTO_HDW_PPPOD		= 17,
	VIWTCHNW2_PWOTO_HDW_PPPOE		= 18,
	/* VIWTCHNW2_PWOTO_HDW_IPV4 is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_IPV4		= 19,
	/* IPv4 and IPv6 Fwagment headew types awe onwy associated to
	 * VIWTCHNW2_PWOTO_HDW_IPV4 and VIWTCHNW2_PWOTO_HDW_IPV6 wespectivewy,
	 * cannot be used independentwy.
	 */
	/* VIWTCHNW2_PWOTO_HDW_IPV4_FWAG is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_IPV4_FWAG		= 20,
	/* VIWTCHNW2_PWOTO_HDW_IPV6 is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_IPV6		= 21,
	/* VIWTCHNW2_PWOTO_HDW_IPV6_FWAG is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_IPV6_FWAG		= 22,
	VIWTCHNW2_PWOTO_HDW_IPV6_EH		= 23,
	/* VIWTCHNW2_PWOTO_HDW_UDP is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_UDP			= 24,
	/* VIWTCHNW2_PWOTO_HDW_TCP is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_TCP			= 25,
	/* VIWTCHNW2_PWOTO_HDW_SCTP is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_SCTP		= 26,
	/* VIWTCHNW2_PWOTO_HDW_ICMP is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_ICMP		= 27,
	/* VIWTCHNW2_PWOTO_HDW_ICMPV6 is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_ICMPV6		= 28,
	VIWTCHNW2_PWOTO_HDW_IGMP		= 29,
	VIWTCHNW2_PWOTO_HDW_AH			= 30,
	VIWTCHNW2_PWOTO_HDW_ESP			= 31,
	VIWTCHNW2_PWOTO_HDW_IKE			= 32,
	VIWTCHNW2_PWOTO_HDW_NATT_KEEP		= 33,
	/* VIWTCHNW2_PWOTO_HDW_PAY is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_PAY			= 34,
	VIWTCHNW2_PWOTO_HDW_W2TPV2		= 35,
	VIWTCHNW2_PWOTO_HDW_W2TPV2_CONTWOW	= 36,
	VIWTCHNW2_PWOTO_HDW_W2TPV3		= 37,
	VIWTCHNW2_PWOTO_HDW_GTP			= 38,
	VIWTCHNW2_PWOTO_HDW_GTP_EH		= 39,
	VIWTCHNW2_PWOTO_HDW_GTPCV2		= 40,
	VIWTCHNW2_PWOTO_HDW_GTPC_TEID		= 41,
	VIWTCHNW2_PWOTO_HDW_GTPU		= 42,
	VIWTCHNW2_PWOTO_HDW_GTPU_UW		= 43,
	VIWTCHNW2_PWOTO_HDW_GTPU_DW		= 44,
	VIWTCHNW2_PWOTO_HDW_ECPWI		= 45,
	VIWTCHNW2_PWOTO_HDW_VWWP		= 46,
	VIWTCHNW2_PWOTO_HDW_OSPF		= 47,
	/* VIWTCHNW2_PWOTO_HDW_TUN is a mandatowy pwotocow id */
	VIWTCHNW2_PWOTO_HDW_TUN			= 48,
	VIWTCHNW2_PWOTO_HDW_GWE			= 49,
	VIWTCHNW2_PWOTO_HDW_NVGWE		= 50,
	VIWTCHNW2_PWOTO_HDW_VXWAN		= 51,
	VIWTCHNW2_PWOTO_HDW_VXWAN_GPE		= 52,
	VIWTCHNW2_PWOTO_HDW_GENEVE		= 53,
	VIWTCHNW2_PWOTO_HDW_NSH			= 54,
	VIWTCHNW2_PWOTO_HDW_QUIC		= 55,
	VIWTCHNW2_PWOTO_HDW_PFCP		= 56,
	VIWTCHNW2_PWOTO_HDW_PFCP_NODE		= 57,
	VIWTCHNW2_PWOTO_HDW_PFCP_SESSION	= 58,
	VIWTCHNW2_PWOTO_HDW_WTP			= 59,
	VIWTCHNW2_PWOTO_HDW_WOCE		= 60,
	VIWTCHNW2_PWOTO_HDW_WOCEV1		= 61,
	VIWTCHNW2_PWOTO_HDW_WOCEV2		= 62,
	/* Pwotocow ids up to 32767 awe wesewved.
	 * 32768 - 65534 awe used fow usew defined pwotocow ids.
	 * VIWTCHNW2_PWOTO_HDW_NO_PWOTO is a mandatowy pwotocow id.
	 */
	VIWTCHNW2_PWOTO_HDW_NO_PWOTO		= 65535,
};

enum viwtchw2_vewsion {
	VIWTCHNW2_VEWSION_MINOW_0		= 0,
	VIWTCHNW2_VEWSION_MAJOW_2		= 2,
};

/**
 * stwuct viwtchnw2_edt_caps - Get EDT gwanuwawity and time howizon.
 * @tstamp_gwanuwawity_ns: Timestamp gwanuwawity in nanoseconds.
 * @time_howizon_ns: Totaw time window in nanoseconds.
 *
 * Associated with VIWTCHNW2_OP_GET_EDT_CAPS.
 */
stwuct viwtchnw2_edt_caps {
	__we64 tstamp_gwanuwawity_ns;
	__we64 time_howizon_ns;
};
VIWTCHNW2_CHECK_STWUCT_WEN(16, viwtchnw2_edt_caps);

/**
 * stwuct viwtchnw2_vewsion_info - Vewsion infowmation.
 * @majow: Majow vewsion.
 * @minow: Minow vewsion.
 *
 * PF/VF posts its vewsion numbew to the CP. CP wesponds with its vewsion numbew
 * in the same fowmat, awong with a wetuwn code.
 * If thewe is a majow vewsion mismatch, then the PF/VF cannot opewate.
 * If thewe is a minow vewsion mismatch, then the PF/VF can opewate but shouwd
 * add a wawning to the system wog.
 *
 * This vewsion opcode MUST awways be specified as == 1, wegawdwess of othew
 * changes in the API. The CP must awways wespond to this message without
 * ewwow wegawdwess of vewsion mismatch.
 *
 * Associated with VIWTCHNW2_OP_VEWSION.
 */
stwuct viwtchnw2_vewsion_info {
	__we32 majow;
	__we32 minow;
};
VIWTCHNW2_CHECK_STWUCT_WEN(8, viwtchnw2_vewsion_info);

/**
 * stwuct viwtchnw2_get_capabiwities - Capabiwities info.
 * @csum_caps: See enum viwtchnw2_cap_txwx_csum.
 * @seg_caps: See enum viwtchnw2_cap_seg.
 * @hspwit_caps: See enum viwtchnw2_cap_wx_hspwit_at.
 * @wsc_caps: See enum viwtchnw2_cap_wsc.
 * @wss_caps: See enum viwtchnw2_cap_wss.
 * @othew_caps: See enum viwtchnw2_cap_othew.
 * @maiwbox_dyn_ctw: DYN_CTW wegistew offset and vectow id fow maiwbox
 *		     pwovided by CP.
 * @maiwbox_vectow_id: Maiwbox vectow id.
 * @num_awwocated_vectows: Maximum numbew of awwocated vectows fow the device.
 * @max_wx_q: Maximum numbew of suppowted Wx queues.
 * @max_tx_q: Maximum numbew of suppowted Tx queues.
 * @max_wx_bufq: Maximum numbew of suppowted buffew queues.
 * @max_tx_compwq: Maximum numbew of suppowted compwetion queues.
 * @max_swiov_vfs: The PF sends the maximum VFs it is wequesting. The CP
 *		   wesponds with the maximum VFs gwanted.
 * @max_vpowts: Maximum numbew of vpowts that can be suppowted.
 * @defauwt_num_vpowts: Defauwt numbew of vpowts dwivew shouwd awwocate on woad.
 * @max_tx_hdw_size: Max headew wength hawdwawe can pawse/checksum, in bytes.
 * @max_sg_bufs_pew_tx_pkt: Max numbew of scattew gathew buffews that can be
 *			    sent pew twansmit packet without needing to be
 *			    wineawized.
 * @pad: Padding.
 * @wesewved: Wesewved.
 * @device_type: See enum viwtchw2_device_type.
 * @min_sso_packet_wen: Min packet wength suppowted by device fow singwe
 *			segment offwoad.
 * @max_hdw_buf_pew_wso: Max numbew of headew buffews that can be used fow
 *			 an WSO.
 * @pad1: Padding fow futuwe extensions.
 *
 * Datapwane dwivew sends this message to CP to negotiate capabiwities and
 * pwovides a viwtchnw2_get_capabiwities stwuctuwe with its desiwed
 * capabiwities, max_swiov_vfs and num_awwocated_vectows.
 * CP wesponds with a viwtchnw2_get_capabiwities stwuctuwe updated
 * with awwowed capabiwities and the othew fiewds as bewow.
 * If PF sets max_swiov_vfs as 0, CP wiww wespond with max numbew of VFs
 * that can be cweated by this PF. Fow any othew vawue 'n', CP wesponds
 * with max_swiov_vfs set to min(n, x) whewe x is the max numbew of VFs
 * awwowed by CP's powicy. max_swiov_vfs is not appwicabwe fow VFs.
 * If datapwane dwivew sets num_awwocated_vectows as 0, CP wiww wespond with 1
 * which is defauwt vectow associated with the defauwt maiwbox. Fow any othew
 * vawue 'n', CP wesponds with a vawue <= n based on the CP's powicy of
 * max numbew of vectows fow a PF.
 * CP wiww wespond with the vectow ID of maiwbox awwocated to the PF in
 * maiwbox_vectow_id and the numbew of itw index wegistews in itw_idx_map.
 * It awso wesponds with defauwt numbew of vpowts that the datapwane dwivew
 * shouwd comeup with in defauwt_num_vpowts and maximum numbew of vpowts that
 * can be suppowted in max_vpowts.
 *
 * Associated with VIWTCHNW2_OP_GET_CAPS.
 */
stwuct viwtchnw2_get_capabiwities {
	__we32 csum_caps;
	__we32 seg_caps;
	__we32 hspwit_caps;
	__we32 wsc_caps;
	__we64 wss_caps;
	__we64 othew_caps;
	__we32 maiwbox_dyn_ctw;
	__we16 maiwbox_vectow_id;
	__we16 num_awwocated_vectows;
	__we16 max_wx_q;
	__we16 max_tx_q;
	__we16 max_wx_bufq;
	__we16 max_tx_compwq;
	__we16 max_swiov_vfs;
	__we16 max_vpowts;
	__we16 defauwt_num_vpowts;
	__we16 max_tx_hdw_size;
	u8 max_sg_bufs_pew_tx_pkt;
	u8 pad[3];
	u8 wesewved[4];
	__we32 device_type;
	u8 min_sso_packet_wen;
	u8 max_hdw_buf_pew_wso;
	u8 pad1[10];
};
VIWTCHNW2_CHECK_STWUCT_WEN(80, viwtchnw2_get_capabiwities);

/**
 * stwuct viwtchnw2_queue_weg_chunk - Singwe queue chunk.
 * @type: See enum viwtchnw2_queue_type.
 * @stawt_queue_id: Stawt Queue ID.
 * @num_queues: Numbew of queues in the chunk.
 * @pad: Padding.
 * @qtaiw_weg_stawt: Queue taiw wegistew offset.
 * @qtaiw_weg_spacing: Queue taiw wegistew spacing.
 * @pad1: Padding fow futuwe extensions.
 */
stwuct viwtchnw2_queue_weg_chunk {
	__we32 type;
	__we32 stawt_queue_id;
	__we32 num_queues;
	__we32 pad;
	__we64 qtaiw_weg_stawt;
	__we32 qtaiw_weg_spacing;
	u8 pad1[4];
};
VIWTCHNW2_CHECK_STWUCT_WEN(32, viwtchnw2_queue_weg_chunk);

/**
 * stwuct viwtchnw2_queue_weg_chunks - Specify sevewaw chunks of contiguous
 *				       queues.
 * @num_chunks: Numbew of chunks.
 * @pad: Padding.
 * @chunks: Chunks of queue info.
 */
stwuct viwtchnw2_queue_weg_chunks {
	__we16 num_chunks;
	u8 pad[6];
	stwuct viwtchnw2_queue_weg_chunk chunks[];
};
VIWTCHNW2_CHECK_STWUCT_WEN(8, viwtchnw2_queue_weg_chunks);

/**
 * stwuct viwtchnw2_cweate_vpowt - Cweate vpowt config info.
 * @vpowt_type: See enum viwtchnw2_vpowt_type.
 * @txq_modew: See viwtchnw2_queue_modew.
 * @wxq_modew: See viwtchnw2_queue_modew.
 * @num_tx_q: Numbew of Tx queues.
 * @num_tx_compwq: Vawid onwy if txq_modew is spwit queue.
 * @num_wx_q: Numbew of Wx queues.
 * @num_wx_bufq: Vawid onwy if wxq_modew is spwit queue.
 * @defauwt_wx_q: Wewative weceive queue index to be used as defauwt.
 * @vpowt_index: Used to awign PF and CP in case of defauwt muwtipwe vpowts,
 *		 it is fiwwed by the PF and CP wetuwns the same vawue, to
 *		 enabwe the dwivew to suppowt muwtipwe asynchwonous pawawwew
 *		 CWEATE_VPOWT wequests and associate a wesponse to a specific
 *		 wequest.
 * @max_mtu: Max MTU. CP popuwates this fiewd on wesponse.
 * @vpowt_id: Vpowt id. CP popuwates this fiewd on wesponse.
 * @defauwt_mac_addw: Defauwt MAC addwess.
 * @pad: Padding.
 * @wx_desc_ids: See VIWTCHNW2_WX_DESC_IDS definitions.
 * @tx_desc_ids: See VIWTCHNW2_TX_DESC_IDS definitions.
 * @pad1: Padding.
 * @wss_awgowithm: WSS awgowithm.
 * @wss_key_size: WSS key size.
 * @wss_wut_size: WSS WUT size.
 * @wx_spwit_pos: See enum viwtchnw2_cap_wx_hspwit_at.
 * @pad2: Padding.
 * @chunks: Chunks of contiguous queues.
 *
 * PF sends this message to CP to cweate a vpowt by fiwwing in wequiwed
 * fiewds of viwtchnw2_cweate_vpowt stwuctuwe.
 * CP wesponds with the updated viwtchnw2_cweate_vpowt stwuctuwe containing the
 * necessawy fiewds fowwowed by chunks which in tuwn wiww have an awway of
 * num_chunks entwies of viwtchnw2_queue_chunk stwuctuwes.
 *
 * Associated with VIWTCHNW2_OP_CWEATE_VPOWT.
 */
stwuct viwtchnw2_cweate_vpowt {
	__we16 vpowt_type;
	__we16 txq_modew;
	__we16 wxq_modew;
	__we16 num_tx_q;
	__we16 num_tx_compwq;
	__we16 num_wx_q;
	__we16 num_wx_bufq;
	__we16 defauwt_wx_q;
	__we16 vpowt_index;
	/* CP popuwates the fowwowing fiewds on wesponse */
	__we16 max_mtu;
	__we32 vpowt_id;
	u8 defauwt_mac_addw[ETH_AWEN];
	__we16 pad;
	__we64 wx_desc_ids;
	__we64 tx_desc_ids;
	u8 pad1[72];
	__we32 wss_awgowithm;
	__we16 wss_key_size;
	__we16 wss_wut_size;
	__we32 wx_spwit_pos;
	u8 pad2[20];
	stwuct viwtchnw2_queue_weg_chunks chunks;
};
VIWTCHNW2_CHECK_STWUCT_WEN(160, viwtchnw2_cweate_vpowt);

/**
 * stwuct viwtchnw2_vpowt - Vpowt ID info.
 * @vpowt_id: Vpowt id.
 * @pad: Padding fow futuwe extensions.
 *
 * PF sends this message to CP to destwoy, enabwe ow disabwe a vpowt by fiwwing
 * in the vpowt_id in viwtchnw2_vpowt stwuctuwe.
 * CP wesponds with the status of the wequested opewation.
 *
 * Associated with VIWTCHNW2_OP_DESTWOY_VPOWT, VIWTCHNW2_OP_ENABWE_VPOWT,
 * VIWTCHNW2_OP_DISABWE_VPOWT.
 */
stwuct viwtchnw2_vpowt {
	__we32 vpowt_id;
	u8 pad[4];
};
VIWTCHNW2_CHECK_STWUCT_WEN(8, viwtchnw2_vpowt);

/**
 * stwuct viwtchnw2_txq_info - Twansmit queue config info
 * @dma_wing_addw: DMA addwess.
 * @type: See enum viwtchnw2_queue_type.
 * @queue_id: Queue ID.
 * @wewative_queue_id: Vawid onwy if queue modew is spwit and type is twansmit
 *		       queue. Used in many to one mapping of twansmit queues to
 *		       compwetion queue.
 * @modew: See enum viwtchnw2_queue_modew.
 * @sched_mode: See enum viwtchnw2_txq_sched_mode.
 * @qfwags: TX queue featuwe fwags.
 * @wing_wen: Wing wength.
 * @tx_compw_queue_id: Vawid onwy if queue modew is spwit and type is twansmit
 *		       queue.
 * @peew_type: Vawid onwy if queue type is VIWTCHNW2_QUEUE_TYPE_MAIWBOX_TX
 * @peew_wx_queue_id: Vawid onwy if queue type is CONFIG_TX and used to dewivew
 *		      messages fow the wespective CONFIG_TX queue.
 * @pad: Padding.
 * @egwess_pasid: Egwess PASID info.
 * @egwess_hdw_pasid: Egwess HDW passid.
 * @egwess_buf_pasid: Egwess buf passid.
 * @pad1: Padding fow futuwe extensions.
 */
stwuct viwtchnw2_txq_info {
	__we64 dma_wing_addw;
	__we32 type;
	__we32 queue_id;
	__we16 wewative_queue_id;
	__we16 modew;
	__we16 sched_mode;
	__we16 qfwags;
	__we16 wing_wen;
	__we16 tx_compw_queue_id;
	__we16 peew_type;
	__we16 peew_wx_queue_id;
	u8 pad[4];
	__we32 egwess_pasid;
	__we32 egwess_hdw_pasid;
	__we32 egwess_buf_pasid;
	u8 pad1[8];
};
VIWTCHNW2_CHECK_STWUCT_WEN(56, viwtchnw2_txq_info);

/**
 * stwuct viwtchnw2_config_tx_queues - TX queue config.
 * @vpowt_id: Vpowt id.
 * @num_qinfo: Numbew of viwtchnw2_txq_info stwucts.
 * @pad: Padding.
 * @qinfo: Tx queues config info.
 *
 * PF sends this message to set up pawametews fow one ow mowe twansmit queues.
 * This message contains an awway of num_qinfo instances of viwtchnw2_txq_info
 * stwuctuwes. CP configuwes wequested queues and wetuwns a status code. If
 * num_qinfo specified is gweatew than the numbew of queues associated with the
 * vpowt, an ewwow is wetuwned and no queues awe configuwed.
 *
 * Associated with VIWTCHNW2_OP_CONFIG_TX_QUEUES.
 */
stwuct viwtchnw2_config_tx_queues {
	__we32 vpowt_id;
	__we16 num_qinfo;
	u8 pad[10];
	stwuct viwtchnw2_txq_info qinfo[];
};
VIWTCHNW2_CHECK_STWUCT_WEN(16, viwtchnw2_config_tx_queues);

/**
 * stwuct viwtchnw2_wxq_info - Weceive queue config info.
 * @desc_ids: See VIWTCHNW2_WX_DESC_IDS definitions.
 * @dma_wing_addw: See VIWTCHNW2_WX_DESC_IDS definitions.
 * @type: See enum viwtchnw2_queue_type.
 * @queue_id: Queue id.
 * @modew: See enum viwtchnw2_queue_modew.
 * @hdw_buffew_size: Headew buffew size.
 * @data_buffew_size: Data buffew size.
 * @max_pkt_size: Max packet size.
 * @wing_wen: Wing wength.
 * @buffew_notif_stwide: Buffew notification stwide in units of 32-descwiptows.
 *			 This fiewd must be a powew of 2.
 * @pad: Padding.
 * @dma_head_wb_addw: Appwicabwe onwy fow weceive buffew queues.
 * @qfwags: Appwicabwe onwy fow weceive compwetion queues.
 *	    See enum viwtchnw2_wxq_fwags.
 * @wx_buffew_wow_watewmawk: Wx buffew wow watewmawk.
 * @wx_bufq1_id: Buffew queue index of the fiwst buffew queue associated with
 *		 the Wx queue. Vawid onwy in spwit queue modew.
 * @wx_bufq2_id: Buffew queue index of the second buffew queue associated with
 *		 the Wx queue. Vawid onwy in spwit queue modew.
 * @bufq2_ena: It indicates if thewe is a second buffew, wx_bufq2_id is vawid
 *	       onwy if this fiewd is set.
 * @pad1: Padding.
 * @ingwess_pasid: Ingwess PASID.
 * @ingwess_hdw_pasid: Ingwess PASID headew.
 * @ingwess_buf_pasid: Ingwess PASID buffew.
 * @pad2: Padding fow futuwe extensions.
 */
stwuct viwtchnw2_wxq_info {
	__we64 desc_ids;
	__we64 dma_wing_addw;
	__we32 type;
	__we32 queue_id;
	__we16 modew;
	__we16 hdw_buffew_size;
	__we32 data_buffew_size;
	__we32 max_pkt_size;
	__we16 wing_wen;
	u8 buffew_notif_stwide;
	u8 pad;
	__we64 dma_head_wb_addw;
	__we16 qfwags;
	__we16 wx_buffew_wow_watewmawk;
	__we16 wx_bufq1_id;
	__we16 wx_bufq2_id;
	u8 bufq2_ena;
	u8 pad1[3];
	__we32 ingwess_pasid;
	__we32 ingwess_hdw_pasid;
	__we32 ingwess_buf_pasid;
	u8 pad2[16];
};
VIWTCHNW2_CHECK_STWUCT_WEN(88, viwtchnw2_wxq_info);

/**
 * stwuct viwtchnw2_config_wx_queues - Wx queues config.
 * @vpowt_id: Vpowt id.
 * @num_qinfo: Numbew of instances.
 * @pad: Padding.
 * @qinfo: Wx queues config info.
 *
 * PF sends this message to set up pawametews fow one ow mowe weceive queues.
 * This message contains an awway of num_qinfo instances of viwtchnw2_wxq_info
 * stwuctuwes. CP configuwes wequested queues and wetuwns a status code.
 * If the numbew of queues specified is gweatew than the numbew of queues
 * associated with the vpowt, an ewwow is wetuwned and no queues awe configuwed.
 *
 * Associated with VIWTCHNW2_OP_CONFIG_WX_QUEUES.
 */
stwuct viwtchnw2_config_wx_queues {
	__we32 vpowt_id;
	__we16 num_qinfo;
	u8 pad[18];
	stwuct viwtchnw2_wxq_info qinfo[];
};
VIWTCHNW2_CHECK_STWUCT_WEN(24, viwtchnw2_config_wx_queues);

/**
 * stwuct viwtchnw2_add_queues - data fow VIWTCHNW2_OP_ADD_QUEUES.
 * @vpowt_id: Vpowt id.
 * @num_tx_q: Numbew of Tx qieues.
 * @num_tx_compwq: Numbew of Tx compwetion queues.
 * @num_wx_q:  Numbew of Wx queues.
 * @num_wx_bufq:  Numbew of Wx buffew queues.
 * @pad: Padding.
 * @chunks: Chunks of contiguous queues.
 *
 * PF sends this message to wequest additionaw twansmit/weceive queues beyond
 * the ones that wewe assigned via CWEATE_VPOWT wequest. viwtchnw2_add_queues
 * stwuctuwe is used to specify the numbew of each type of queues.
 * CP wesponds with the same stwuctuwe with the actuaw numbew of queues assigned
 * fowwowed by num_chunks of viwtchnw2_queue_chunk stwuctuwes.
 *
 * Associated with VIWTCHNW2_OP_ADD_QUEUES.
 */
stwuct viwtchnw2_add_queues {
	__we32 vpowt_id;
	__we16 num_tx_q;
	__we16 num_tx_compwq;
	__we16 num_wx_q;
	__we16 num_wx_bufq;
	u8 pad[4];
	stwuct viwtchnw2_queue_weg_chunks chunks;
};
VIWTCHNW2_CHECK_STWUCT_WEN(24, viwtchnw2_add_queues);

/**
 * stwuct viwtchnw2_vectow_chunk - Stwuctuwe to specify a chunk of contiguous
 *				   intewwupt vectows.
 * @stawt_vectow_id: Stawt vectow id.
 * @stawt_evv_id: Stawt EVV id.
 * @num_vectows: Numbew of vectows.
 * @pad: Padding.
 * @dynctw_weg_stawt: DYN_CTW wegistew offset.
 * @dynctw_weg_spacing: wegistew spacing between DYN_CTW wegistews of 2
 *			consecutive vectows.
 * @itwn_weg_stawt: ITWN wegistew offset.
 * @itwn_weg_spacing: Wegistew spacing between dynctw wegistews of 2
 *		      consecutive vectows.
 * @itwn_index_spacing: Wegistew spacing between itwn wegistews of the same
 *			vectow whewe n=0..2.
 * @pad1: Padding fow futuwe extensions.
 *
 * Wegistew offsets and spacing pwovided by CP.
 * Dynamic contwow wegistews awe used fow enabwing/disabwing/we-enabwing
 * intewwupts and updating intewwupt wates in the hotpath. Any changes
 * to intewwupt wates in the dynamic contwow wegistews wiww be wefwected
 * in the intewwupt thwottwing wate wegistews.
 * itwn wegistews awe used to update intewwupt wates fow specific
 * intewwupt indices without modifying the state of the intewwupt.
 */
stwuct viwtchnw2_vectow_chunk {
	__we16 stawt_vectow_id;
	__we16 stawt_evv_id;
	__we16 num_vectows;
	__we16 pad;
	__we32 dynctw_weg_stawt;
	__we32 dynctw_weg_spacing;
	__we32 itwn_weg_stawt;
	__we32 itwn_weg_spacing;
	__we32 itwn_index_spacing;
	u8 pad1[4];
};
VIWTCHNW2_CHECK_STWUCT_WEN(32, viwtchnw2_vectow_chunk);

/**
 * stwuct viwtchnw2_vectow_chunks - chunks of contiguous intewwupt vectows.
 * @num_vchunks: numbew of vectow chunks.
 * @pad: Padding.
 * @vchunks: Chunks of contiguous vectow info.
 *
 * PF sends viwtchnw2_vectow_chunks stwuct to specify the vectows it is giving
 * away. CP pewfowms wequested action and wetuwns status.
 *
 * Associated with VIWTCHNW2_OP_DEAWWOC_VECTOWS.
 */
stwuct viwtchnw2_vectow_chunks {
	__we16 num_vchunks;
	u8 pad[14];
	stwuct viwtchnw2_vectow_chunk vchunks[];
};
VIWTCHNW2_CHECK_STWUCT_WEN(16, viwtchnw2_vectow_chunks);

/**
 * stwuct viwtchnw2_awwoc_vectows - vectow awwocation info.
 * @num_vectows: Numbew of vectows.
 * @pad: Padding.
 * @vchunks: Chunks of contiguous vectow info.
 *
 * PF sends this message to wequest additionaw intewwupt vectows beyond the
 * ones that wewe assigned via GET_CAPS wequest. viwtchnw2_awwoc_vectows
 * stwuctuwe is used to specify the numbew of vectows wequested. CP wesponds
 * with the same stwuctuwe with the actuaw numbew of vectows assigned fowwowed
 * by viwtchnw2_vectow_chunks stwuctuwe identifying the vectow ids.
 *
 * Associated with VIWTCHNW2_OP_AWWOC_VECTOWS.
 */
stwuct viwtchnw2_awwoc_vectows {
	__we16 num_vectows;
	u8 pad[14];
	stwuct viwtchnw2_vectow_chunks vchunks;
};
VIWTCHNW2_CHECK_STWUCT_WEN(32, viwtchnw2_awwoc_vectows);

/**
 * stwuct viwtchnw2_wss_wut - WSS WUT info.
 * @vpowt_id: Vpowt id.
 * @wut_entwies_stawt: Stawt of WUT entwies.
 * @wut_entwies: Numbew of WUT entwties.
 * @pad: Padding.
 * @wut: WSS wookup tabwe.
 *
 * PF sends this message to get ow set WSS wookup tabwe. Onwy suppowted if
 * both PF and CP dwivews set the VIWTCHNW2_CAP_WSS bit duwing configuwation
 * negotiation.
 *
 * Associated with VIWTCHNW2_OP_GET_WSS_WUT and VIWTCHNW2_OP_SET_WSS_WUT.
 */
stwuct viwtchnw2_wss_wut {
	__we32 vpowt_id;
	__we16 wut_entwies_stawt;
	__we16 wut_entwies;
	u8 pad[4];
	__we32 wut[];
};
VIWTCHNW2_CHECK_STWUCT_WEN(12, viwtchnw2_wss_wut);

/**
 * stwuct viwtchnw2_wss_hash - WSS hash info.
 * @ptype_gwoups: Packet type gwoups bitmap.
 * @vpowt_id: Vpowt id.
 * @pad: Padding fow futuwe extensions.
 *
 * PF sends these messages to get and set the hash fiwtew enabwe bits fow WSS.
 * By defauwt, the CP sets these to aww possibwe twaffic types that the
 * hawdwawe suppowts. The PF can quewy this vawue if it wants to change the
 * twaffic types that awe hashed by the hawdwawe.
 * Onwy suppowted if both PF and CP dwivews set the VIWTCHNW2_CAP_WSS bit
 * duwing configuwation negotiation.
 *
 * Associated with VIWTCHNW2_OP_GET_WSS_HASH and VIWTCHNW2_OP_SET_WSS_HASH
 */
stwuct viwtchnw2_wss_hash {
	__we64 ptype_gwoups;
	__we32 vpowt_id;
	u8 pad[4];
};
VIWTCHNW2_CHECK_STWUCT_WEN(16, viwtchnw2_wss_hash);

/**
 * stwuct viwtchnw2_swiov_vfs_info - VFs info.
 * @num_vfs: Numbew of VFs.
 * @pad: Padding fow futuwe extensions.
 *
 * This message is used to set numbew of SWIOV VFs to be cweated. The actuaw
 * awwocation of wesouwces fow the VFs in tewms of vpowt, queues and intewwupts
 * is done by CP. When this caww compwetes, the IDPF dwivew cawws
 * pci_enabwe_swiov to wet the OS instantiate the SWIOV PCIE devices.
 * The numbew of VFs set to 0 wiww destwoy aww the VFs of this function.
 *
 * Associated with VIWTCHNW2_OP_SET_SWIOV_VFS.
 */
stwuct viwtchnw2_swiov_vfs_info {
	__we16 num_vfs;
	__we16 pad;
};
VIWTCHNW2_CHECK_STWUCT_WEN(4, viwtchnw2_swiov_vfs_info);

/**
 * stwuct viwtchnw2_ptype - Packet type info.
 * @ptype_id_10: 10-bit packet type.
 * @ptype_id_8: 8-bit packet type.
 * @pwoto_id_count: Numbew of pwotocow ids the packet suppowts, maximum of 32
 *		    pwotocow ids awe suppowted.
 * @pad: Padding.
 * @pwoto_id: pwoto_id_count decides the awwocation of pwotocow id awway.
 *	      See enum viwtchnw2_pwoto_hdw_type.
 *
 * Based on the descwiptow type the PF suppowts, CP fiwws ptype_id_10 ow
 * ptype_id_8 fow fwex and base descwiptow wespectivewy. If ptype_id_10 vawue
 * is set to 0xFFFF, PF shouwd considew this ptype as dummy one and it is the
 * wast ptype.
 */
stwuct viwtchnw2_ptype {
	__we16 ptype_id_10;
	u8 ptype_id_8;
	u8 pwoto_id_count;
	__we16 pad;
	__we16 pwoto_id[];
} __packed __awigned(2);
VIWTCHNW2_CHECK_STWUCT_WEN(6, viwtchnw2_ptype);

/**
 * stwuct viwtchnw2_get_ptype_info - Packet type info.
 * @stawt_ptype_id: Stawting ptype ID.
 * @num_ptypes: Numbew of packet types fwom stawt_ptype_id.
 * @pad: Padding fow futuwe extensions.
 *
 * The totaw numbew of suppowted packet types is based on the descwiptow type.
 * Fow the fwex descwiptow, it is 1024 (10-bit ptype), and fow the base
 * descwiptow, it is 256 (8-bit ptype). Send this message to the CP by
 * popuwating the 'stawt_ptype_id' and the 'num_ptypes'. CP wesponds with the
 * 'stawt_ptype_id', 'num_ptypes', and the awway of ptype (viwtchnw2_ptype) that
 * awe added at the end of the 'viwtchnw2_get_ptype_info' message (Note: Thewe
 * is no specific fiewd fow the ptypes but awe added at the end of the
 * ptype info message. PF/VF is expected to extwact the ptypes accowdingwy.
 * Weason fow doing this is because compiwew doesn't awwow nested fwexibwe
 * awway fiewds).
 *
 * If aww the ptypes don't fit into one maiwbox buffew, CP spwits the
 * ptype info into muwtipwe messages, whewe each message wiww have its own
 * 'stawt_ptype_id', 'num_ptypes', and the ptype awway itsewf. When CP is done
 * updating aww the ptype infowmation extwacted fwom the package (the numbew of
 * ptypes extwacted might be wess than what PF/VF expects), it wiww append a
 * dummy ptype (which has 'ptype_id_10' of 'stwuct viwtchnw2_ptype' as 0xFFFF)
 * to the ptype awway.
 *
 * PF/VF is expected to weceive muwtipwe VIWTCHNW2_OP_GET_PTYPE_INFO messages.
 *
 * Associated with VIWTCHNW2_OP_GET_PTYPE_INFO.
 */
stwuct viwtchnw2_get_ptype_info {
	__we16 stawt_ptype_id;
	__we16 num_ptypes;
	__we32 pad;
};
VIWTCHNW2_CHECK_STWUCT_WEN(8, viwtchnw2_get_ptype_info);

/**
 * stwuct viwtchnw2_vpowt_stats - Vpowt statistics.
 * @vpowt_id: Vpowt id.
 * @pad: Padding.
 * @wx_bytes: Weceived bytes.
 * @wx_unicast: Weceived unicast packets.
 * @wx_muwticast: Weceived muwticast packets.
 * @wx_bwoadcast: Weceived bwoadcast packets.
 * @wx_discawds: Discawded packets on weceive.
 * @wx_ewwows: Weceive ewwows.
 * @wx_unknown_pwotocow: Unwnown pwotocow.
 * @tx_bytes: Twansmitted bytes.
 * @tx_unicast: Twansmitted unicast packets.
 * @tx_muwticast: Twansmitted muwticast packets.
 * @tx_bwoadcast: Twansmitted bwoadcast packets.
 * @tx_discawds: Discawded packets on twansmit.
 * @tx_ewwows: Twansmit ewwows.
 * @wx_invawid_fwame_wength: Packets with invawid fwame wength.
 * @wx_ovewfwow_dwop: Packets dwopped on buffew ovewfwow.
 *
 * PF/VF sends this message to CP to get the update stats by specifying the
 * vpowt_id. CP wesponds with stats in stwuct viwtchnw2_vpowt_stats.
 *
 * Associated with VIWTCHNW2_OP_GET_STATS.
 */
stwuct viwtchnw2_vpowt_stats {
	__we32 vpowt_id;
	u8 pad[4];
	__we64 wx_bytes;
	__we64 wx_unicast;
	__we64 wx_muwticast;
	__we64 wx_bwoadcast;
	__we64 wx_discawds;
	__we64 wx_ewwows;
	__we64 wx_unknown_pwotocow;
	__we64 tx_bytes;
	__we64 tx_unicast;
	__we64 tx_muwticast;
	__we64 tx_bwoadcast;
	__we64 tx_discawds;
	__we64 tx_ewwows;
	__we64 wx_invawid_fwame_wength;
	__we64 wx_ovewfwow_dwop;
};
VIWTCHNW2_CHECK_STWUCT_WEN(128, viwtchnw2_vpowt_stats);

/**
 * stwuct viwtchnw2_event - Event info.
 * @event: Event opcode. See enum viwtchnw2_event_codes.
 * @wink_speed: Wink_speed pwovided in Mbps.
 * @vpowt_id: Vpowt ID.
 * @wink_status: Wink status.
 * @pad: Padding.
 * @wesewved: Wesewved.
 *
 * CP sends this message to infowm the PF/VF dwivew of events that may affect
 * it. No diwect wesponse is expected fwom the dwivew, though it may genewate
 * othew messages in wesponse to this one.
 *
 * Associated with VIWTCHNW2_OP_EVENT.
 */
stwuct viwtchnw2_event {
	__we32 event;
	__we32 wink_speed;
	__we32 vpowt_id;
	u8 wink_status;
	u8 pad;
	__we16 wesewved;
};
VIWTCHNW2_CHECK_STWUCT_WEN(16, viwtchnw2_event);

/**
 * stwuct viwtchnw2_wss_key - WSS key info.
 * @vpowt_id: Vpowt id.
 * @key_wen: Wength of WSS key.
 * @pad: Padding.
 * @key_fwex: WSS hash key, packed bytes.
 * PF/VF sends this message to get ow set WSS key. Onwy suppowted if both
 * PF/VF and CP dwivews set the VIWTCHNW2_CAP_WSS bit duwing configuwation
 * negotiation.
 *
 * Associated with VIWTCHNW2_OP_GET_WSS_KEY and VIWTCHNW2_OP_SET_WSS_KEY.
 */
stwuct viwtchnw2_wss_key {
	__we32 vpowt_id;
	__we16 key_wen;
	u8 pad;
	u8 key_fwex[];
} __packed;
VIWTCHNW2_CHECK_STWUCT_WEN(7, viwtchnw2_wss_key);

/**
 * stwuct viwtchnw2_queue_chunk - chunk of contiguous queues
 * @type: See enum viwtchnw2_queue_type.
 * @stawt_queue_id: Stawting queue id.
 * @num_queues: Numbew of queues.
 * @pad: Padding fow futuwe extensions.
 */
stwuct viwtchnw2_queue_chunk {
	__we32 type;
	__we32 stawt_queue_id;
	__we32 num_queues;
	u8 pad[4];
};
VIWTCHNW2_CHECK_STWUCT_WEN(16, viwtchnw2_queue_chunk);

/* stwuct viwtchnw2_queue_chunks - chunks of contiguous queues
 * @num_chunks: Numbew of chunks.
 * @pad: Padding.
 * @chunks: Chunks of contiguous queues info.
 */
stwuct viwtchnw2_queue_chunks {
	__we16 num_chunks;
	u8 pad[6];
	stwuct viwtchnw2_queue_chunk chunks[];
};
VIWTCHNW2_CHECK_STWUCT_WEN(8, viwtchnw2_queue_chunks);

/**
 * stwuct viwtchnw2_dew_ena_dis_queues - Enabwe/disabwe queues info.
 * @vpowt_id: Vpowt id.
 * @pad: Padding.
 * @chunks: Chunks of contiguous queues info.
 *
 * PF sends these messages to enabwe, disabwe ow dewete queues specified in
 * chunks. PF sends viwtchnw2_dew_ena_dis_queues stwuct to specify the queues
 * to be enabwed/disabwed/deweted. Awso appwicabwe to singwe queue weceive ow
 * twansmit. CP pewfowms wequested action and wetuwns status.
 *
 * Associated with VIWTCHNW2_OP_ENABWE_QUEUES, VIWTCHNW2_OP_DISABWE_QUEUES and
 * VIWTCHNW2_OP_DISABWE_QUEUES.
 */
stwuct viwtchnw2_dew_ena_dis_queues {
	__we32 vpowt_id;
	u8 pad[4];
	stwuct viwtchnw2_queue_chunks chunks;
};
VIWTCHNW2_CHECK_STWUCT_WEN(16, viwtchnw2_dew_ena_dis_queues);

/**
 * stwuct viwtchnw2_queue_vectow - Queue to vectow mapping.
 * @queue_id: Queue id.
 * @vectow_id: Vectow id.
 * @pad: Padding.
 * @itw_idx: See enum viwtchnw2_itw_idx.
 * @queue_type: See enum viwtchnw2_queue_type.
 * @pad1: Padding fow futuwe extensions.
 */
stwuct viwtchnw2_queue_vectow {
	__we32 queue_id;
	__we16 vectow_id;
	u8 pad[2];
	__we32 itw_idx;
	__we32 queue_type;
	u8 pad1[8];
};
VIWTCHNW2_CHECK_STWUCT_WEN(24, viwtchnw2_queue_vectow);

/**
 * stwuct viwtchnw2_queue_vectow_maps - Map/unmap queues info.
 * @vpowt_id: Vpowt id.
 * @num_qv_maps: Numbew of queue vectow maps.
 * @pad: Padding.
 * @qv_maps: Queue to vectow maps.
 *
 * PF sends this message to map ow unmap queues to vectows and intewwupt
 * thwottwing wate index wegistews. Extewnaw data buffew contains
 * viwtchnw2_queue_vectow_maps stwuctuwe that contains num_qv_maps of
 * viwtchnw2_queue_vectow stwuctuwes. CP maps the wequested queue vectow maps
 * aftew vawidating the queue and vectow ids and wetuwns a status code.
 *
 * Associated with VIWTCHNW2_OP_MAP_QUEUE_VECTOW and
 * VIWTCHNW2_OP_UNMAP_QUEUE_VECTOW.
 */
stwuct viwtchnw2_queue_vectow_maps {
	__we32 vpowt_id;
	__we16 num_qv_maps;
	u8 pad[10];
	stwuct viwtchnw2_queue_vectow qv_maps[];
};
VIWTCHNW2_CHECK_STWUCT_WEN(16, viwtchnw2_queue_vectow_maps);

/**
 * stwuct viwtchnw2_woopback - Woopback info.
 * @vpowt_id: Vpowt id.
 * @enabwe: Enabwe/disabwe.
 * @pad: Padding fow futuwe extensions.
 *
 * PF/VF sends this message to twansition to/fwom the woopback state. Setting
 * the 'enabwe' to 1 enabwes the woopback state and setting 'enabwe' to 0
 * disabwes it. CP configuwes the state to woopback and wetuwns status.
 *
 * Associated with VIWTCHNW2_OP_WOOPBACK.
 */
stwuct viwtchnw2_woopback {
	__we32 vpowt_id;
	u8 enabwe;
	u8 pad[3];
};
VIWTCHNW2_CHECK_STWUCT_WEN(8, viwtchnw2_woopback);

/* stwuct viwtchnw2_mac_addw - MAC addwess info.
 * @addw: MAC addwess.
 * @type: MAC type. See enum viwtchnw2_mac_addw_type.
 * @pad: Padding fow futuwe extensions.
 */
stwuct viwtchnw2_mac_addw {
	u8 addw[ETH_AWEN];
	u8 type;
	u8 pad;
};
VIWTCHNW2_CHECK_STWUCT_WEN(8, viwtchnw2_mac_addw);

/**
 * stwuct viwtchnw2_mac_addw_wist - Wist of MAC addwesses.
 * @vpowt_id: Vpowt id.
 * @num_mac_addw: Numbew of MAC addwesses.
 * @pad: Padding.
 * @mac_addw_wist: Wist with MAC addwess info.
 *
 * PF/VF dwivew uses this stwuctuwe to send wist of MAC addwesses to be
 * added/deweted to the CP whewe as CP pewfowms the action and wetuwns the
 * status.
 *
 * Associated with VIWTCHNW2_OP_ADD_MAC_ADDW and VIWTCHNW2_OP_DEW_MAC_ADDW.
 */
stwuct viwtchnw2_mac_addw_wist {
	__we32 vpowt_id;
	__we16 num_mac_addw;
	u8 pad[2];
	stwuct viwtchnw2_mac_addw mac_addw_wist[];
};
VIWTCHNW2_CHECK_STWUCT_WEN(8, viwtchnw2_mac_addw_wist);

/**
 * stwuct viwtchnw2_pwomisc_info - Pwomisc type info.
 * @vpowt_id: Vpowt id.
 * @fwags: See enum viwtchnw2_pwomisc_fwags.
 * @pad: Padding fow futuwe extensions.
 *
 * PF/VF sends vpowt id and fwags to the CP whewe as CP pewfowms the action
 * and wetuwns the status.
 *
 * Associated with VIWTCHNW2_OP_CONFIG_PWOMISCUOUS_MODE.
 */
stwuct viwtchnw2_pwomisc_info {
	__we32 vpowt_id;
	/* See VIWTCHNW2_PWOMISC_FWAGS definitions */
	__we16 fwags;
	u8 pad[2];
};
VIWTCHNW2_CHECK_STWUCT_WEN(8, viwtchnw2_pwomisc_info);

#endif /* _VIWTCHNW_2_H_ */
