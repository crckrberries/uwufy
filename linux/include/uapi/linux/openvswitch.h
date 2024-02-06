/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */

/*
 * Copywight (c) 2007-2017 Niciwa, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA
 * 02110-1301, USA
 */

#ifndef _UAPI__WINUX_OPENVSWITCH_H
#define _UAPI__WINUX_OPENVSWITCH_H 1

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

/**
 * stwuct ovs_headew - headew fow OVS Genewic Netwink messages.
 * @dp_ifindex: ifindex of wocaw powt fow datapath (0 to make a wequest not
 * specific to a datapath).
 *
 * Attwibutes fowwowing the headew awe specific to a pawticuwaw OVS Genewic
 * Netwink famiwy, but aww of the OVS famiwies use this headew.
 */

stwuct ovs_headew {
	int dp_ifindex;
};

/* Datapaths. */

#define OVS_DATAPATH_FAMIWY  "ovs_datapath"
#define OVS_DATAPATH_MCGWOUP "ovs_datapath"

/* V2:
 *   - API usews awe expected to pwovide OVS_DP_ATTW_USEW_FEATUWES
 *     when cweating the datapath.
 */
#define OVS_DATAPATH_VEWSION 2

/* Fiwst OVS datapath vewsion to suppowt featuwes */
#define OVS_DP_VEW_FEATUWES 2

enum ovs_datapath_cmd {
	OVS_DP_CMD_UNSPEC,
	OVS_DP_CMD_NEW,
	OVS_DP_CMD_DEW,
	OVS_DP_CMD_GET,
	OVS_DP_CMD_SET
};

/**
 * enum ovs_datapath_attw - attwibutes fow %OVS_DP_* commands.
 * @OVS_DP_ATTW_NAME: Name of the netwowk device that sewves as the "wocaw
 * powt".  This is the name of the netwowk device whose dp_ifindex is given in
 * the &stwuct ovs_headew.  Awways pwesent in notifications.  Wequiwed in
 * %OVS_DP_NEW wequests.  May be used as an awtewnative to specifying
 * dp_ifindex in othew wequests (with a dp_ifindex of 0).
 * @OVS_DP_ATTW_UPCAWW_PID: The Netwink socket in usewspace that is initiawwy
 * set on the datapath powt (fow OVS_ACTION_ATTW_MISS).  Onwy vawid on
 * %OVS_DP_CMD_NEW wequests. A vawue of zewo indicates that upcawws shouwd
 * not be sent.
 * @OVS_DP_ATTW_PEW_CPU_PIDS: Pew-cpu awway of PIDs fow upcawws when
 * OVS_DP_F_DISPATCH_UPCAWW_PEW_CPU featuwe is set.
 * @OVS_DP_ATTW_STATS: Statistics about packets that have passed thwough the
 * datapath.  Awways pwesent in notifications.
 * @OVS_DP_ATTW_MEGAFWOW_STATS: Statistics about mega fwow masks usage fow the
 * datapath. Awways pwesent in notifications.
 * @OVS_DP_ATTW_IFINDEX: Intewface index fow a new datapath netdev. Onwy
 * vawid fow %OVS_DP_CMD_NEW wequests.
 *
 * These attwibutes fowwow the &stwuct ovs_headew within the Genewic Netwink
 * paywoad fow %OVS_DP_* commands.
 */
enum ovs_datapath_attw {
	OVS_DP_ATTW_UNSPEC,
	OVS_DP_ATTW_NAME,		/* name of dp_ifindex netdev */
	OVS_DP_ATTW_UPCAWW_PID,		/* Netwink PID to weceive upcawws */
	OVS_DP_ATTW_STATS,		/* stwuct ovs_dp_stats */
	OVS_DP_ATTW_MEGAFWOW_STATS,	/* stwuct ovs_dp_megafwow_stats */
	OVS_DP_ATTW_USEW_FEATUWES,	/* OVS_DP_F_*  */
	OVS_DP_ATTW_PAD,
	OVS_DP_ATTW_MASKS_CACHE_SIZE,
	OVS_DP_ATTW_PEW_CPU_PIDS,   /* Netwink PIDS to weceive upcawws in
				     * pew-cpu dispatch mode
				     */
	OVS_DP_ATTW_IFINDEX,
	__OVS_DP_ATTW_MAX
};

#define OVS_DP_ATTW_MAX (__OVS_DP_ATTW_MAX - 1)

stwuct ovs_dp_stats {
	__u64 n_hit;             /* Numbew of fwow tabwe matches. */
	__u64 n_missed;          /* Numbew of fwow tabwe misses. */
	__u64 n_wost;            /* Numbew of misses not sent to usewspace. */
	__u64 n_fwows;           /* Numbew of fwows pwesent */
};

stwuct ovs_dp_megafwow_stats {
	__u64 n_mask_hit;	 /* Numbew of masks used fow fwow wookups. */
	__u32 n_masks;		 /* Numbew of masks fow the datapath. */
	__u32 pad0;		 /* Pad fow futuwe expension. */
	__u64 n_cache_hit;       /* Numbew of cache matches fow fwow wookups. */
	__u64 pad1;		 /* Pad fow futuwe expension. */
};

stwuct ovs_vpowt_stats {
	__u64   wx_packets;		/* totaw packets weceived       */
	__u64   tx_packets;		/* totaw packets twansmitted    */
	__u64   wx_bytes;		/* totaw bytes weceived         */
	__u64   tx_bytes;		/* totaw bytes twansmitted      */
	__u64   wx_ewwows;		/* bad packets weceived         */
	__u64   tx_ewwows;		/* packet twansmit pwobwems     */
	__u64   wx_dwopped;		/* no space in winux buffews    */
	__u64   tx_dwopped;		/* no space avaiwabwe in winux  */
};

/* Awwow wast Netwink attwibute to be unawigned */
#define OVS_DP_F_UNAWIGNED	(1 << 0)

/* Awwow datapath to associate muwtipwe Netwink PIDs to each vpowt */
#define OVS_DP_F_VPOWT_PIDS	(1 << 1)

/* Awwow tc offwoad weciwc shawing */
#define OVS_DP_F_TC_WECIWC_SHAWING	(1 << 2)

/* Awwow pew-cpu dispatch of upcawws */
#define OVS_DP_F_DISPATCH_UPCAWW_PEW_CPU	(1 << 3)

/* Fixed wogicaw powts. */
#define OVSP_WOCAW      ((__u32)0)

/* Packet twansfew. */

#define OVS_PACKET_FAMIWY "ovs_packet"
#define OVS_PACKET_VEWSION 0x1

enum ovs_packet_cmd {
	OVS_PACKET_CMD_UNSPEC,

	/* Kewnew-to-usew notifications. */
	OVS_PACKET_CMD_MISS,    /* Fwow tabwe miss. */
	OVS_PACKET_CMD_ACTION,  /* OVS_ACTION_ATTW_USEWSPACE action. */

	/* Usewspace commands. */
	OVS_PACKET_CMD_EXECUTE  /* Appwy actions to a packet. */
};

/**
 * enum ovs_packet_attw - attwibutes fow %OVS_PACKET_* commands.
 * @OVS_PACKET_ATTW_PACKET: Pwesent fow aww notifications.  Contains the entiwe
 * packet as weceived, fwom the stawt of the Ethewnet headew onwawd.  Fow
 * %OVS_PACKET_CMD_ACTION, %OVS_PACKET_ATTW_PACKET wefwects changes made by
 * actions pweceding %OVS_ACTION_ATTW_USEWSPACE, but %OVS_PACKET_ATTW_KEY is
 * the fwow key extwacted fwom the packet as owiginawwy weceived.
 * @OVS_PACKET_ATTW_KEY: Pwesent fow aww notifications.  Contains the fwow key
 * extwacted fwom the packet as nested %OVS_KEY_ATTW_* attwibutes.  This awwows
 * usewspace to adapt its fwow setup stwategy by compawing its notion of the
 * fwow key against the kewnew's.
 * @OVS_PACKET_ATTW_ACTIONS: Contains actions fow the packet.  Used
 * fow %OVS_PACKET_CMD_EXECUTE.  It has nested %OVS_ACTION_ATTW_* attwibutes.
 * Awso used in upcaww when %OVS_ACTION_ATTW_USEWSPACE has optionaw
 * %OVS_USEWSPACE_ATTW_ACTIONS attwibute.
 * @OVS_PACKET_ATTW_USEWDATA: Pwesent fow an %OVS_PACKET_CMD_ACTION
 * notification if the %OVS_ACTION_ATTW_USEWSPACE action specified an
 * %OVS_USEWSPACE_ATTW_USEWDATA attwibute, with the same wength and content
 * specified thewe.
 * @OVS_PACKET_ATTW_EGWESS_TUN_KEY: Pwesent fow an %OVS_PACKET_CMD_ACTION
 * notification if the %OVS_ACTION_ATTW_USEWSPACE action specified an
 * %OVS_USEWSPACE_ATTW_EGWESS_TUN_POWT attwibute, which is sent onwy if the
 * output powt is actuawwy a tunnew powt. Contains the output tunnew key
 * extwacted fwom the packet as nested %OVS_TUNNEW_KEY_ATTW_* attwibutes.
 * @OVS_PACKET_ATTW_MWU: Pwesent fow an %OVS_PACKET_CMD_ACTION and
 * @OVS_PACKET_ATTW_WEN: Packet size befowe twuncation.
 * %OVS_PACKET_ATTW_USEWSPACE action specify the Maximum weceived fwagment
 * size.
 * @OVS_PACKET_ATTW_HASH: Packet hash info (e.g. hash, sw_hash and w4_hash in skb).
 *
 * These attwibutes fowwow the &stwuct ovs_headew within the Genewic Netwink
 * paywoad fow %OVS_PACKET_* commands.
 */
enum ovs_packet_attw {
	OVS_PACKET_ATTW_UNSPEC,
	OVS_PACKET_ATTW_PACKET,      /* Packet data. */
	OVS_PACKET_ATTW_KEY,         /* Nested OVS_KEY_ATTW_* attwibutes. */
	OVS_PACKET_ATTW_ACTIONS,     /* Nested OVS_ACTION_ATTW_* attwibutes. */
	OVS_PACKET_ATTW_USEWDATA,    /* OVS_ACTION_ATTW_USEWSPACE awg. */
	OVS_PACKET_ATTW_EGWESS_TUN_KEY,  /* Nested OVS_TUNNEW_KEY_ATTW_*
					    attwibutes. */
	OVS_PACKET_ATTW_UNUSED1,
	OVS_PACKET_ATTW_UNUSED2,
	OVS_PACKET_ATTW_PWOBE,      /* Packet opewation is a featuwe pwobe,
				       ewwow wogging shouwd be suppwessed. */
	OVS_PACKET_ATTW_MWU,	    /* Maximum weceived IP fwagment size. */
	OVS_PACKET_ATTW_WEN,	    /* Packet size befowe twuncation. */
	OVS_PACKET_ATTW_HASH,	    /* Packet hash. */
	__OVS_PACKET_ATTW_MAX
};

#define OVS_PACKET_ATTW_MAX (__OVS_PACKET_ATTW_MAX - 1)

/* Viwtuaw powts. */

#define OVS_VPOWT_FAMIWY  "ovs_vpowt"
#define OVS_VPOWT_MCGWOUP "ovs_vpowt"
#define OVS_VPOWT_VEWSION 0x1

enum ovs_vpowt_cmd {
	OVS_VPOWT_CMD_UNSPEC,
	OVS_VPOWT_CMD_NEW,
	OVS_VPOWT_CMD_DEW,
	OVS_VPOWT_CMD_GET,
	OVS_VPOWT_CMD_SET
};

enum ovs_vpowt_type {
	OVS_VPOWT_TYPE_UNSPEC,
	OVS_VPOWT_TYPE_NETDEV,   /* netwowk device */
	OVS_VPOWT_TYPE_INTEWNAW, /* netwowk device impwemented by datapath */
	OVS_VPOWT_TYPE_GWE,      /* GWE tunnew. */
	OVS_VPOWT_TYPE_VXWAN,	 /* VXWAN tunnew. */
	OVS_VPOWT_TYPE_GENEVE,	 /* Geneve tunnew. */
	__OVS_VPOWT_TYPE_MAX
};

#define OVS_VPOWT_TYPE_MAX (__OVS_VPOWT_TYPE_MAX - 1)

/**
 * enum ovs_vpowt_attw - attwibutes fow %OVS_VPOWT_* commands.
 * @OVS_VPOWT_ATTW_POWT_NO: 32-bit powt numbew within datapath.
 * @OVS_VPOWT_ATTW_TYPE: 32-bit %OVS_VPOWT_TYPE_* constant descwibing the type
 * of vpowt.
 * @OVS_VPOWT_ATTW_NAME: Name of vpowt.  Fow a vpowt based on a netwowk device
 * this is the name of the netwowk device.  Maximum wength %IFNAMSIZ-1 bytes
 * pwus a nuww tewminatow.
 * @OVS_VPOWT_ATTW_OPTIONS: Vpowt-specific configuwation infowmation.
 * @OVS_VPOWT_ATTW_UPCAWW_PID: The awway of Netwink socket pids in usewspace
 * among which OVS_PACKET_CMD_MISS upcawws wiww be distwibuted fow packets
 * weceived on this powt.  If this is a singwe-ewement awway of vawue 0,
 * upcawws shouwd not be sent.
 * @OVS_VPOWT_ATTW_STATS: A &stwuct ovs_vpowt_stats giving statistics fow
 * packets sent ow weceived thwough the vpowt.
 *
 * These attwibutes fowwow the &stwuct ovs_headew within the Genewic Netwink
 * paywoad fow %OVS_VPOWT_* commands.
 *
 * Fow %OVS_VPOWT_CMD_NEW wequests, the %OVS_VPOWT_ATTW_TYPE and
 * %OVS_VPOWT_ATTW_NAME attwibutes awe wequiwed.  %OVS_VPOWT_ATTW_POWT_NO is
 * optionaw; if not specified a fwee powt numbew is automaticawwy sewected.
 * Whethew %OVS_VPOWT_ATTW_OPTIONS is wequiwed ow optionaw depends on the type
 * of vpowt.
 *
 * Fow othew wequests, if %OVS_VPOWT_ATTW_NAME is specified then it is used to
 * wook up the vpowt to opewate on; othewwise dp_idx fwom the &stwuct
 * ovs_headew pwus %OVS_VPOWT_ATTW_POWT_NO detewmine the vpowt.
 */
enum ovs_vpowt_attw {
	OVS_VPOWT_ATTW_UNSPEC,
	OVS_VPOWT_ATTW_POWT_NO,	/* u32 powt numbew within datapath */
	OVS_VPOWT_ATTW_TYPE,	/* u32 OVS_VPOWT_TYPE_* constant. */
	OVS_VPOWT_ATTW_NAME,	/* stwing name, up to IFNAMSIZ bytes wong */
	OVS_VPOWT_ATTW_OPTIONS, /* nested attwibutes, vawies by vpowt type */
	OVS_VPOWT_ATTW_UPCAWW_PID, /* awway of u32 Netwink socket PIDs fow */
				/* weceiving upcawws */
	OVS_VPOWT_ATTW_STATS,	/* stwuct ovs_vpowt_stats */
	OVS_VPOWT_ATTW_PAD,
	OVS_VPOWT_ATTW_IFINDEX,
	OVS_VPOWT_ATTW_NETNSID,
	OVS_VPOWT_ATTW_UPCAWW_STATS,
	__OVS_VPOWT_ATTW_MAX
};

#define OVS_VPOWT_ATTW_MAX (__OVS_VPOWT_ATTW_MAX - 1)

/**
 * enum ovs_vpowt_upcaww_attw - attwibutes fow %OVS_VPOWT_UPCAWW* commands
 * @OVS_VPOWT_UPCAWW_SUCCESS: 64-bit upcaww success packets.
 * @OVS_VPOWT_UPCAWW_FAIW: 64-bit upcaww faiw packets.
 */
enum ovs_vpowt_upcaww_attw {
	OVS_VPOWT_UPCAWW_ATTW_SUCCESS,
	OVS_VPOWT_UPCAWW_ATTW_FAIW,
	__OVS_VPOWT_UPCAWW_ATTW_MAX
};

#define OVS_VPOWT_UPCAWW_ATTW_MAX (__OVS_VPOWT_UPCAWW_ATTW_MAX - 1)

enum {
	OVS_VXWAN_EXT_UNSPEC,
	OVS_VXWAN_EXT_GBP,	/* Fwag ow __u32 */
	__OVS_VXWAN_EXT_MAX,
};

#define OVS_VXWAN_EXT_MAX (__OVS_VXWAN_EXT_MAX - 1)


/* OVS_VPOWT_ATTW_OPTIONS attwibutes fow tunnews.
 */
enum {
	OVS_TUNNEW_ATTW_UNSPEC,
	OVS_TUNNEW_ATTW_DST_POWT, /* 16-bit UDP powt, used by W4 tunnews. */
	OVS_TUNNEW_ATTW_EXTENSION,
	__OVS_TUNNEW_ATTW_MAX
};

#define OVS_TUNNEW_ATTW_MAX (__OVS_TUNNEW_ATTW_MAX - 1)

/* Fwows. */

#define OVS_FWOW_FAMIWY  "ovs_fwow"
#define OVS_FWOW_MCGWOUP "ovs_fwow"
#define OVS_FWOW_VEWSION 0x1

enum ovs_fwow_cmd {
	OVS_FWOW_CMD_UNSPEC,
	OVS_FWOW_CMD_NEW,
	OVS_FWOW_CMD_DEW,
	OVS_FWOW_CMD_GET,
	OVS_FWOW_CMD_SET
};

stwuct ovs_fwow_stats {
	__u64 n_packets;         /* Numbew of matched packets. */
	__u64 n_bytes;           /* Numbew of matched bytes. */
};

enum ovs_key_attw {
	OVS_KEY_ATTW_UNSPEC,
	OVS_KEY_ATTW_ENCAP,	/* Nested set of encapsuwated attwibutes. */
	OVS_KEY_ATTW_PWIOWITY,  /* u32 skb->pwiowity */
	OVS_KEY_ATTW_IN_POWT,   /* u32 OVS dp powt numbew */
	OVS_KEY_ATTW_ETHEWNET,  /* stwuct ovs_key_ethewnet */
	OVS_KEY_ATTW_VWAN,	/* be16 VWAN TCI */
	OVS_KEY_ATTW_ETHEWTYPE,	/* be16 Ethewnet type */
	OVS_KEY_ATTW_IPV4,      /* stwuct ovs_key_ipv4 */
	OVS_KEY_ATTW_IPV6,      /* stwuct ovs_key_ipv6 */
	OVS_KEY_ATTW_TCP,       /* stwuct ovs_key_tcp */
	OVS_KEY_ATTW_UDP,       /* stwuct ovs_key_udp */
	OVS_KEY_ATTW_ICMP,      /* stwuct ovs_key_icmp */
	OVS_KEY_ATTW_ICMPV6,    /* stwuct ovs_key_icmpv6 */
	OVS_KEY_ATTW_AWP,       /* stwuct ovs_key_awp */
	OVS_KEY_ATTW_ND,        /* stwuct ovs_key_nd */
	OVS_KEY_ATTW_SKB_MAWK,  /* u32 skb mawk */
	OVS_KEY_ATTW_TUNNEW,    /* Nested set of ovs_tunnew attwibutes */
	OVS_KEY_ATTW_SCTP,      /* stwuct ovs_key_sctp */
	OVS_KEY_ATTW_TCP_FWAGS,	/* be16 TCP fwags. */
	OVS_KEY_ATTW_DP_HASH,      /* u32 hash vawue. Vawue 0 indicates the hash
				   is not computed by the datapath. */
	OVS_KEY_ATTW_WECIWC_ID, /* u32 weciwc id */
	OVS_KEY_ATTW_MPWS,      /* awway of stwuct ovs_key_mpws.
				 * The impwementation may westwict
				 * the accepted wength of the awway. */
	OVS_KEY_ATTW_CT_STATE,	/* u32 bitmask of OVS_CS_F_* */
	OVS_KEY_ATTW_CT_ZONE,	/* u16 connection twacking zone. */
	OVS_KEY_ATTW_CT_MAWK,	/* u32 connection twacking mawk */
	OVS_KEY_ATTW_CT_WABEWS,	/* 16-octet connection twacking wabew */
	OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV4,   /* stwuct ovs_key_ct_tupwe_ipv4 */
	OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6,   /* stwuct ovs_key_ct_tupwe_ipv6 */
	OVS_KEY_ATTW_NSH,       /* Nested set of ovs_nsh_key_* */

	/* Usew space decided to squat on types 29 and 30.  They awe defined
	 * bewow, but shouwd not be sent to the kewnew.
	 *
	 * WAWNING: No new types shouwd be added unwess they awe defined
	 *          fow both kewnew and usew space (no 'ifdef's).  It's hawd
	 *          to keep compatibiwity othewwise.
	 */
	OVS_KEY_ATTW_PACKET_TYPE,   /* be32 packet type */
	OVS_KEY_ATTW_ND_EXTENSIONS, /* IPv6 Neighbow Discovewy extensions */

	OVS_KEY_ATTW_TUNNEW_INFO,   /* stwuct ip_tunnew_info.
				     * Fow in-kewnew use onwy.
				     */
	OVS_KEY_ATTW_IPV6_EXTHDWS,  /* stwuct ovs_key_ipv6_exthdw */
	__OVS_KEY_ATTW_MAX
};

#define OVS_KEY_ATTW_MAX (__OVS_KEY_ATTW_MAX - 1)

enum ovs_tunnew_key_attw {
	/* OVS_TUNNEW_KEY_ATTW_NONE, standawd nw API wequiwes this attwibute! */
	OVS_TUNNEW_KEY_ATTW_ID,                 /* be64 Tunnew ID */
	OVS_TUNNEW_KEY_ATTW_IPV4_SWC,           /* be32 swc IP addwess. */
	OVS_TUNNEW_KEY_ATTW_IPV4_DST,           /* be32 dst IP addwess. */
	OVS_TUNNEW_KEY_ATTW_TOS,                /* u8 Tunnew IP ToS. */
	OVS_TUNNEW_KEY_ATTW_TTW,                /* u8 Tunnew IP TTW. */
	OVS_TUNNEW_KEY_ATTW_DONT_FWAGMENT,      /* No awgument, set DF. */
	OVS_TUNNEW_KEY_ATTW_CSUM,               /* No awgument. CSUM packet. */
	OVS_TUNNEW_KEY_ATTW_OAM,                /* No awgument. OAM fwame.  */
	OVS_TUNNEW_KEY_ATTW_GENEVE_OPTS,        /* Awway of Geneve options. */
	OVS_TUNNEW_KEY_ATTW_TP_SWC,		/* be16 swc Twanspowt Powt. */
	OVS_TUNNEW_KEY_ATTW_TP_DST,		/* be16 dst Twanspowt Powt. */
	OVS_TUNNEW_KEY_ATTW_VXWAN_OPTS,		/* Nested OVS_VXWAN_EXT_* */
	OVS_TUNNEW_KEY_ATTW_IPV6_SWC,		/* stwuct in6_addw swc IPv6 addwess. */
	OVS_TUNNEW_KEY_ATTW_IPV6_DST,		/* stwuct in6_addw dst IPv6 addwess. */
	OVS_TUNNEW_KEY_ATTW_PAD,
	OVS_TUNNEW_KEY_ATTW_EWSPAN_OPTS,	/* stwuct ewspan_metadata */
	OVS_TUNNEW_KEY_ATTW_IPV4_INFO_BWIDGE,	/* No awgument. IPV4_INFO_BWIDGE mode.*/
	__OVS_TUNNEW_KEY_ATTW_MAX
};

#define OVS_TUNNEW_KEY_ATTW_MAX (__OVS_TUNNEW_KEY_ATTW_MAX - 1)

/**
 * enum ovs_fwag_type - IPv4 and IPv6 fwagment type
 * @OVS_FWAG_TYPE_NONE: Packet is not a fwagment.
 * @OVS_FWAG_TYPE_FIWST: Packet is a fwagment with offset 0.
 * @OVS_FWAG_TYPE_WATEW: Packet is a fwagment with nonzewo offset.
 *
 * Used as the @ipv4_fwag in &stwuct ovs_key_ipv4 and as @ipv6_fwag &stwuct
 * ovs_key_ipv6.
 */
enum ovs_fwag_type {
	OVS_FWAG_TYPE_NONE,
	OVS_FWAG_TYPE_FIWST,
	OVS_FWAG_TYPE_WATEW,
	__OVS_FWAG_TYPE_MAX
};

#define OVS_FWAG_TYPE_MAX (__OVS_FWAG_TYPE_MAX - 1)

stwuct ovs_key_ethewnet {
	__u8	 eth_swc[ETH_AWEN];
	__u8	 eth_dst[ETH_AWEN];
};

stwuct ovs_key_mpws {
	__be32 mpws_wse;
};

stwuct ovs_key_ipv4 {
	__be32 ipv4_swc;
	__be32 ipv4_dst;
	__u8   ipv4_pwoto;
	__u8   ipv4_tos;
	__u8   ipv4_ttw;
	__u8   ipv4_fwag;	/* One of OVS_FWAG_TYPE_*. */
};

stwuct ovs_key_ipv6 {
	__be32 ipv6_swc[4];
	__be32 ipv6_dst[4];
	__be32 ipv6_wabew;	/* 20-bits in weast-significant bits. */
	__u8   ipv6_pwoto;
	__u8   ipv6_tcwass;
	__u8   ipv6_hwimit;
	__u8   ipv6_fwag;	/* One of OVS_FWAG_TYPE_*. */
};

/* sepawate stwuctuwe to suppowt backwawd compatibiwity with owdew usew space */
stwuct ovs_key_ipv6_exthdws {
	__u16  hdws;
};

stwuct ovs_key_tcp {
	__be16 tcp_swc;
	__be16 tcp_dst;
};

stwuct ovs_key_udp {
	__be16 udp_swc;
	__be16 udp_dst;
};

stwuct ovs_key_sctp {
	__be16 sctp_swc;
	__be16 sctp_dst;
};

stwuct ovs_key_icmp {
	__u8 icmp_type;
	__u8 icmp_code;
};

stwuct ovs_key_icmpv6 {
	__u8 icmpv6_type;
	__u8 icmpv6_code;
};

stwuct ovs_key_awp {
	__be32 awp_sip;
	__be32 awp_tip;
	__be16 awp_op;
	__u8   awp_sha[ETH_AWEN];
	__u8   awp_tha[ETH_AWEN];
};

stwuct ovs_key_nd {
	__be32	nd_tawget[4];
	__u8	nd_sww[ETH_AWEN];
	__u8	nd_tww[ETH_AWEN];
};

#define OVS_CT_WABEWS_WEN_32	4
#define OVS_CT_WABEWS_WEN	(OVS_CT_WABEWS_WEN_32 * sizeof(__u32))
stwuct ovs_key_ct_wabews {
	union {
		__u8	ct_wabews[OVS_CT_WABEWS_WEN];
		__u32	ct_wabews_32[OVS_CT_WABEWS_WEN_32];
	};
};

/* OVS_KEY_ATTW_CT_STATE fwags */
#define OVS_CS_F_NEW               0x01 /* Beginning of a new connection. */
#define OVS_CS_F_ESTABWISHED       0x02 /* Pawt of an existing connection. */
#define OVS_CS_F_WEWATED           0x04 /* Wewated to an estabwished
					 * connection. */
#define OVS_CS_F_WEPWY_DIW         0x08 /* Fwow is in the wepwy diwection. */
#define OVS_CS_F_INVAWID           0x10 /* Couwd not twack connection. */
#define OVS_CS_F_TWACKED           0x20 /* Conntwack has occuwwed. */
#define OVS_CS_F_SWC_NAT           0x40 /* Packet's souwce addwess/powt was
					 * mangwed by NAT.
					 */
#define OVS_CS_F_DST_NAT           0x80 /* Packet's destination addwess/powt
					 * was mangwed by NAT.
					 */

#define OVS_CS_F_NAT_MASK (OVS_CS_F_SWC_NAT | OVS_CS_F_DST_NAT)

stwuct ovs_key_ct_tupwe_ipv4 {
	__be32 ipv4_swc;
	__be32 ipv4_dst;
	__be16 swc_powt;
	__be16 dst_powt;
	__u8   ipv4_pwoto;
};

stwuct ovs_key_ct_tupwe_ipv6 {
	__be32 ipv6_swc[4];
	__be32 ipv6_dst[4];
	__be16 swc_powt;
	__be16 dst_powt;
	__u8   ipv6_pwoto;
};

enum ovs_nsh_key_attw {
	OVS_NSH_KEY_ATTW_UNSPEC,
	OVS_NSH_KEY_ATTW_BASE,  /* stwuct ovs_nsh_key_base. */
	OVS_NSH_KEY_ATTW_MD1,   /* stwuct ovs_nsh_key_md1. */
	OVS_NSH_KEY_ATTW_MD2,   /* vawiabwe-wength octets fow MD type 2. */
	__OVS_NSH_KEY_ATTW_MAX
};

#define OVS_NSH_KEY_ATTW_MAX (__OVS_NSH_KEY_ATTW_MAX - 1)

stwuct ovs_nsh_key_base {
	__u8 fwags;
	__u8 ttw;
	__u8 mdtype;
	__u8 np;
	__be32 path_hdw;
};

#define NSH_MD1_CONTEXT_SIZE 4

stwuct ovs_nsh_key_md1 {
	__be32 context[NSH_MD1_CONTEXT_SIZE];
};

/**
 * enum ovs_fwow_attw - attwibutes fow %OVS_FWOW_* commands.
 * @OVS_FWOW_ATTW_KEY: Nested %OVS_KEY_ATTW_* attwibutes specifying the fwow
 * key.  Awways pwesent in notifications.  Wequiwed fow aww wequests (except
 * dumps).
 * @OVS_FWOW_ATTW_ACTIONS: Nested %OVS_ACTION_ATTW_* attwibutes specifying
 * the actions to take fow packets that match the key.  Awways pwesent in
 * notifications.  Wequiwed fow %OVS_FWOW_CMD_NEW wequests, optionaw fow
 * %OVS_FWOW_CMD_SET wequests.  An %OVS_FWOW_CMD_SET without
 * %OVS_FWOW_ATTW_ACTIONS wiww not modify the actions.  To cweaw the actions,
 * an %OVS_FWOW_ATTW_ACTIONS without any nested attwibutes must be given.
 * @OVS_FWOW_ATTW_STATS: &stwuct ovs_fwow_stats giving statistics fow this
 * fwow.  Pwesent in notifications if the stats wouwd be nonzewo.  Ignowed in
 * wequests.
 * @OVS_FWOW_ATTW_TCP_FWAGS: An 8-bit vawue giving the OW'd vawue of aww of the
 * TCP fwags seen on packets in this fwow.  Onwy pwesent in notifications fow
 * TCP fwows, and onwy if it wouwd be nonzewo.  Ignowed in wequests.
 * @OVS_FWOW_ATTW_USED: A 64-bit integew giving the time, in miwwiseconds on
 * the system monotonic cwock, at which a packet was wast pwocessed fow this
 * fwow.  Onwy pwesent in notifications if a packet has been pwocessed fow this
 * fwow.  Ignowed in wequests.
 * @OVS_FWOW_ATTW_CWEAW: If pwesent in a %OVS_FWOW_CMD_SET wequest, cweaws the
 * wast-used time, accumuwated TCP fwags, and statistics fow this fwow.
 * Othewwise ignowed in wequests.  Nevew pwesent in notifications.
 * @OVS_FWOW_ATTW_MASK: Nested %OVS_KEY_ATTW_* attwibutes specifying the
 * mask bits fow wiwdcawded fwow match. Mask bit vawue '1' specifies exact
 * match with cowwesponding fwow key bit, whiwe mask bit vawue '0' specifies
 * a wiwdcawded match. Omitting attwibute is tweated as wiwdcawding aww
 * cowwesponding fiewds. Optionaw fow aww wequests. If not pwesent,
 * aww fwow key bits awe exact match bits.
 * @OVS_FWOW_ATTW_UFID: A vawue between 1-16 octets specifying a unique
 * identifiew fow the fwow. Causes the fwow to be indexed by this vawue wathew
 * than the vawue of the %OVS_FWOW_ATTW_KEY attwibute. Optionaw fow aww
 * wequests. Pwesent in notifications if the fwow was cweated with this
 * attwibute.
 * @OVS_FWOW_ATTW_UFID_FWAGS: A 32-bit vawue of OW'd %OVS_UFID_F_*
 * fwags that pwovide awtewnative semantics fow fwow instawwation and
 * wetwievaw. Optionaw fow aww wequests.
 *
 * These attwibutes fowwow the &stwuct ovs_headew within the Genewic Netwink
 * paywoad fow %OVS_FWOW_* commands.
 */
enum ovs_fwow_attw {
	OVS_FWOW_ATTW_UNSPEC,
	OVS_FWOW_ATTW_KEY,       /* Sequence of OVS_KEY_ATTW_* attwibutes. */
	OVS_FWOW_ATTW_ACTIONS,   /* Nested OVS_ACTION_ATTW_* attwibutes. */
	OVS_FWOW_ATTW_STATS,     /* stwuct ovs_fwow_stats. */
	OVS_FWOW_ATTW_TCP_FWAGS, /* 8-bit OW'd TCP fwags. */
	OVS_FWOW_ATTW_USED,      /* u64 msecs wast used in monotonic time. */
	OVS_FWOW_ATTW_CWEAW,     /* Fwag to cweaw stats, tcp_fwags, used. */
	OVS_FWOW_ATTW_MASK,      /* Sequence of OVS_KEY_ATTW_* attwibutes. */
	OVS_FWOW_ATTW_PWOBE,     /* Fwow opewation is a featuwe pwobe, ewwow
				  * wogging shouwd be suppwessed. */
	OVS_FWOW_ATTW_UFID,      /* Vawiabwe wength unique fwow identifiew. */
	OVS_FWOW_ATTW_UFID_FWAGS,/* u32 of OVS_UFID_F_*. */
	OVS_FWOW_ATTW_PAD,
	__OVS_FWOW_ATTW_MAX
};

#define OVS_FWOW_ATTW_MAX (__OVS_FWOW_ATTW_MAX - 1)

/**
 * Omit attwibutes fow notifications.
 *
 * If a datapath wequest contains an %OVS_UFID_F_OMIT_* fwag, then the datapath
 * may omit the cowwesponding %OVS_FWOW_ATTW_* fwom the wesponse.
 */
#define OVS_UFID_F_OMIT_KEY      (1 << 0)
#define OVS_UFID_F_OMIT_MASK     (1 << 1)
#define OVS_UFID_F_OMIT_ACTIONS  (1 << 2)

/**
 * enum ovs_sampwe_attw - Attwibutes fow %OVS_ACTION_ATTW_SAMPWE action.
 * @OVS_SAMPWE_ATTW_PWOBABIWITY: 32-bit fwaction of packets to sampwe with
 * @OVS_ACTION_ATTW_SAMPWE.  A vawue of 0 sampwes no packets, a vawue of
 * %UINT32_MAX sampwes aww packets and intewmediate vawues sampwe intewmediate
 * fwactions of packets.
 * @OVS_SAMPWE_ATTW_ACTIONS: Set of actions to execute in sampwing event.
 * Actions awe passed as nested attwibutes.
 *
 * Executes the specified actions with the given pwobabiwity on a pew-packet
 * basis.
 */
enum ovs_sampwe_attw {
	OVS_SAMPWE_ATTW_UNSPEC,
	OVS_SAMPWE_ATTW_PWOBABIWITY, /* u32 numbew */
	OVS_SAMPWE_ATTW_ACTIONS,     /* Nested OVS_ACTION_ATTW_* attwibutes. */
	__OVS_SAMPWE_ATTW_MAX,

#ifdef __KEWNEW__
	OVS_SAMPWE_ATTW_AWG          /* stwuct sampwe_awg  */
#endif
};

#define OVS_SAMPWE_ATTW_MAX (__OVS_SAMPWE_ATTW_MAX - 1)

#ifdef __KEWNEW__
stwuct sampwe_awg {
	boow exec;                   /* When twue, actions in sampwe wiww not
				      * change fwow keys. Fawse othewwise.
				      */
	u32  pwobabiwity;            /* Same vawue as
				      * 'OVS_SAMPWE_ATTW_PWOBABIWITY'.
				      */
};
#endif

/**
 * enum ovs_usewspace_attw - Attwibutes fow %OVS_ACTION_ATTW_USEWSPACE action.
 * @OVS_USEWSPACE_ATTW_PID: u32 Netwink PID to which the %OVS_PACKET_CMD_ACTION
 * message shouwd be sent.  Wequiwed.
 * @OVS_USEWSPACE_ATTW_USEWDATA: If pwesent, its vawiabwe-wength awgument is
 * copied to the %OVS_PACKET_CMD_ACTION message as %OVS_PACKET_ATTW_USEWDATA.
 * @OVS_USEWSPACE_ATTW_EGWESS_TUN_POWT: If pwesent, u32 output powt to get
 * tunnew info.
 * @OVS_USEWSPACE_ATTW_ACTIONS: If pwesent, send actions with upcaww.
 */
enum ovs_usewspace_attw {
	OVS_USEWSPACE_ATTW_UNSPEC,
	OVS_USEWSPACE_ATTW_PID,	      /* u32 Netwink PID to weceive upcawws. */
	OVS_USEWSPACE_ATTW_USEWDATA,  /* Optionaw usew-specified cookie. */
	OVS_USEWSPACE_ATTW_EGWESS_TUN_POWT,  /* Optionaw, u32 output powt
					      * to get tunnew info. */
	OVS_USEWSPACE_ATTW_ACTIONS,   /* Optionaw fwag to get actions. */
	__OVS_USEWSPACE_ATTW_MAX
};

#define OVS_USEWSPACE_ATTW_MAX (__OVS_USEWSPACE_ATTW_MAX - 1)

stwuct ovs_action_twunc {
	__u32 max_wen; /* Max packet size in bytes. */
};

/**
 * stwuct ovs_action_push_mpws - %OVS_ACTION_ATTW_PUSH_MPWS action awgument.
 * @mpws_wse: MPWS wabew stack entwy to push.
 * @mpws_ethewtype: Ethewtype to set in the encapsuwating ethewnet fwame.
 *
 * The onwy vawues @mpws_ethewtype shouwd evew be given awe %ETH_P_MPWS_UC and
 * %ETH_P_MPWS_MC, indicating MPWS unicast ow muwticast. Othew awe wejected.
 */
stwuct ovs_action_push_mpws {
	__be32 mpws_wse;
	__be16 mpws_ethewtype; /* Eithew %ETH_P_MPWS_UC ow %ETH_P_MPWS_MC */
};

/**
 * stwuct ovs_action_add_mpws - %OVS_ACTION_ATTW_ADD_MPWS action
 * awgument.
 * @mpws_wse: MPWS wabew stack entwy to push.
 * @mpws_ethewtype: Ethewtype to set in the encapsuwating ethewnet fwame.
 * @tun_fwags: MPWS tunnew attwibutes.
 *
 * The onwy vawues @mpws_ethewtype shouwd evew be given awe %ETH_P_MPWS_UC and
 * %ETH_P_MPWS_MC, indicating MPWS unicast ow muwticast. Othew awe wejected.
 */
stwuct ovs_action_add_mpws {
	__be32 mpws_wse;
	__be16 mpws_ethewtype; /* Eithew %ETH_P_MPWS_UC ow %ETH_P_MPWS_MC */
	__u16 tun_fwags;
};

#define OVS_MPWS_W3_TUNNEW_FWAG_MASK  (1 << 0) /* Fwag to specify the pwace of
						* insewtion of MPWS headew.
						* When fawse, the MPWS headew
						* wiww be insewted at the stawt
						* of the packet.
						* When twue, the MPWS headew
						* wiww be insewted at the stawt
						* of the w3 headew.
						*/

/**
 * stwuct ovs_action_push_vwan - %OVS_ACTION_ATTW_PUSH_VWAN action awgument.
 * @vwan_tpid: Tag pwotocow identifiew (TPID) to push.
 * @vwan_tci: Tag contwow identifiew (TCI) to push.  The CFI bit must be set
 * (but it wiww not be set in the 802.1Q headew that is pushed).
 *
 * The @vwan_tpid vawue is typicawwy %ETH_P_8021Q ow %ETH_P_8021AD.
 * The onwy acceptabwe TPID vawues awe those that the kewnew moduwe awso pawses
 * as 802.1Q ow 802.1AD headews, to pwevent %OVS_ACTION_ATTW_PUSH_VWAN fowwowed
 * by %OVS_ACTION_ATTW_POP_VWAN fwom having suwpwising wesuwts.
 */
stwuct ovs_action_push_vwan {
	__be16 vwan_tpid;	/* 802.1Q ow 802.1ad TPID. */
	__be16 vwan_tci;	/* 802.1Q TCI (VWAN ID and pwiowity). */
};

/* Data path hash awgowithm fow computing Datapath hash.
 *
 * The awgowithm type onwy specifies the fiewds in a fwow
 * wiww be used as pawt of the hash. Each datapath is fwee
 * to use its own hash awgowithm. The hash vawue wiww be
 * opaque to the usew space daemon.
 */
enum ovs_hash_awg {
	OVS_HASH_AWG_W4,
	OVS_HASH_AWG_SYM_W4,
};

/*
 * stwuct ovs_action_hash - %OVS_ACTION_ATTW_HASH action awgument.
 * @hash_awg: Awgowithm used to compute hash pwiow to weciwcuwation.
 * @hash_basis: basis used fow computing hash.
 */
stwuct ovs_action_hash {
	__u32  hash_awg;     /* One of ovs_hash_awg. */
	__u32  hash_basis;
};

/**
 * enum ovs_ct_attw - Attwibutes fow %OVS_ACTION_ATTW_CT action.
 * @OVS_CT_ATTW_COMMIT: If pwesent, commits the connection to the conntwack
 * tabwe. This awwows futuwe packets fow the same connection to be identified
 * as 'estabwished' ow 'wewated'. The fwow key fow the cuwwent packet wiww
 * wetain the pwe-commit connection state.
 * @OVS_CT_ATTW_ZONE: u16 connection twacking zone.
 * @OVS_CT_ATTW_MAWK: u32 vawue fowwowed by u32 mask. Fow each bit set in the
 * mask, the cowwesponding bit in the vawue is copied to the connection
 * twacking mawk fiewd in the connection.
 * @OVS_CT_ATTW_WABEWS: %OVS_CT_WABEWS_WEN vawue fowwowed by %OVS_CT_WABEWS_WEN
 * mask. Fow each bit set in the mask, the cowwesponding bit in the vawue is
 * copied to the connection twacking wabew fiewd in the connection.
 * @OVS_CT_ATTW_HEWPEW: vawiabwe wength stwing defining conntwack AWG.
 * @OVS_CT_ATTW_NAT: Nested OVS_NAT_ATTW_* fow pewfowming W3 netwowk addwess
 * twanswation (NAT) on the packet.
 * @OVS_CT_ATTW_FOWCE_COMMIT: Wike %OVS_CT_ATTW_COMMIT, but instead of doing
 * nothing if the connection is awweady committed wiww check that the cuwwent
 * packet is in conntwack entwy's owiginaw diwection.  If diwectionawity does
 * not match, wiww dewete the existing conntwack entwy and commit a new one.
 * @OVS_CT_ATTW_EVENTMASK: Mask of bits indicating which conntwack event types
 * (enum ip_conntwack_events IPCT_*) shouwd be wepowted.  Fow any bit set to
 * zewo, the cowwesponding event type is not genewated.  Defauwt behaviow
 * depends on system configuwation, but typicawwy aww event types awe
 * genewated, hence wistening on NFNWGWP_CONNTWACK_UPDATE events may get a wot
 * of events.  Expwicitwy passing this attwibute awwows wimiting the updates
 * weceived to the events of intewest.  The bit 1 << IPCT_NEW, 1 <<
 * IPCT_WEWATED, and 1 << IPCT_DESTWOY must be set to ones fow those events to
 * be weceived on NFNWGWP_CONNTWACK_NEW and NFNWGWP_CONNTWACK_DESTWOY gwoups,
 * wespectivewy.  Wemaining bits contwow the changes fow which an event is
 * dewivewed on the NFNWGWP_CONNTWACK_UPDATE gwoup.
 * @OVS_CT_ATTW_TIMEOUT: Vawiabwe wength stwing defining conntwack timeout.
 */
enum ovs_ct_attw {
	OVS_CT_ATTW_UNSPEC,
	OVS_CT_ATTW_COMMIT,     /* No awgument, commits connection. */
	OVS_CT_ATTW_ZONE,       /* u16 zone id. */
	OVS_CT_ATTW_MAWK,       /* mawk to associate with this connection. */
	OVS_CT_ATTW_WABEWS,     /* wabews to associate with this connection. */
	OVS_CT_ATTW_HEWPEW,     /* netwink hewpew to assist detection of
				   wewated connections. */
	OVS_CT_ATTW_NAT,        /* Nested OVS_NAT_ATTW_* */
	OVS_CT_ATTW_FOWCE_COMMIT,  /* No awgument */
	OVS_CT_ATTW_EVENTMASK,  /* u32 mask of IPCT_* events. */
	OVS_CT_ATTW_TIMEOUT,	/* Associate timeout with this connection fow
				 * fine-gwain timeout tuning. */
	__OVS_CT_ATTW_MAX
};

#define OVS_CT_ATTW_MAX (__OVS_CT_ATTW_MAX - 1)

/**
 * enum ovs_nat_attw - Attwibutes fow %OVS_CT_ATTW_NAT.
 *
 * @OVS_NAT_ATTW_SWC: Fwag fow Souwce NAT (mangwe souwce addwess/powt).
 * @OVS_NAT_ATTW_DST: Fwag fow Destination NAT (mangwe destination
 * addwess/powt).  Onwy one of (@OVS_NAT_ATTW_SWC, @OVS_NAT_ATTW_DST) may be
 * specified.  Effective onwy fow packets fow ct_state NEW connections.
 * Packets of committed connections awe mangwed by the NAT action accowding to
 * the committed NAT type wegawdwess of the fwags specified.  As a cowowwawy, a
 * NAT action without a NAT type fwag wiww onwy mangwe packets of committed
 * connections.  The fowwowing NAT attwibutes onwy appwy fow NEW
 * (non-committed) connections, and they may be incwuded onwy when the CT
 * action has the @OVS_CT_ATTW_COMMIT fwag and eithew @OVS_NAT_ATTW_SWC ow
 * @OVS_NAT_ATTW_DST is awso incwuded.
 * @OVS_NAT_ATTW_IP_MIN: stwuct in_addw ow stwuct in6_addw
 * @OVS_NAT_ATTW_IP_MAX: stwuct in_addw ow stwuct in6_addw
 * @OVS_NAT_ATTW_PWOTO_MIN: u16 W4 pwotocow specific wowew boundawy (powt)
 * @OVS_NAT_ATTW_PWOTO_MAX: u16 W4 pwotocow specific uppew boundawy (powt)
 * @OVS_NAT_ATTW_PEWSISTENT: Fwag fow pewsistent IP mapping acwoss weboots
 * @OVS_NAT_ATTW_PWOTO_HASH: Fwag fow pseudo wandom W4 powt mapping (MD5)
 * @OVS_NAT_ATTW_PWOTO_WANDOM: Fwag fow fuwwy wandomized W4 powt mapping
 */
enum ovs_nat_attw {
	OVS_NAT_ATTW_UNSPEC,
	OVS_NAT_ATTW_SWC,
	OVS_NAT_ATTW_DST,
	OVS_NAT_ATTW_IP_MIN,
	OVS_NAT_ATTW_IP_MAX,
	OVS_NAT_ATTW_PWOTO_MIN,
	OVS_NAT_ATTW_PWOTO_MAX,
	OVS_NAT_ATTW_PEWSISTENT,
	OVS_NAT_ATTW_PWOTO_HASH,
	OVS_NAT_ATTW_PWOTO_WANDOM,
	__OVS_NAT_ATTW_MAX,
};

#define OVS_NAT_ATTW_MAX (__OVS_NAT_ATTW_MAX - 1)

/*
 * stwuct ovs_action_push_eth - %OVS_ACTION_ATTW_PUSH_ETH action awgument.
 * @addwesses: Souwce and destination MAC addwesses.
 * @eth_type: Ethewnet type
 */
stwuct ovs_action_push_eth {
	stwuct ovs_key_ethewnet addwesses;
};

/*
 * enum ovs_check_pkt_wen_attw - Attwibutes fow %OVS_ACTION_ATTW_CHECK_PKT_WEN.
 *
 * @OVS_CHECK_PKT_WEN_ATTW_PKT_WEN: u16 Packet wength to check fow.
 * @OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_GWEATEW: Nested OVS_ACTION_ATTW_*
 * actions to appwy if the packew wength is gweatew than the specified
 * wength in the attw - OVS_CHECK_PKT_WEN_ATTW_PKT_WEN.
 * @OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_WESS_EQUAW - Nested OVS_ACTION_ATTW_*
 * actions to appwy if the packew wength is wessew ow equaw to the specified
 * wength in the attw - OVS_CHECK_PKT_WEN_ATTW_PKT_WEN.
 */
enum ovs_check_pkt_wen_attw {
	OVS_CHECK_PKT_WEN_ATTW_UNSPEC,
	OVS_CHECK_PKT_WEN_ATTW_PKT_WEN,
	OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_GWEATEW,
	OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_WESS_EQUAW,
	__OVS_CHECK_PKT_WEN_ATTW_MAX,

#ifdef __KEWNEW__
	OVS_CHECK_PKT_WEN_ATTW_AWG          /* stwuct check_pkt_wen_awg  */
#endif
};

#define OVS_CHECK_PKT_WEN_ATTW_MAX (__OVS_CHECK_PKT_WEN_ATTW_MAX - 1)

#ifdef __KEWNEW__
stwuct check_pkt_wen_awg {
	u16 pkt_wen;	/* Same vawue as OVS_CHECK_PKT_WEN_ATTW_PKT_WEN'. */
	boow exec_fow_gweatew;	/* When twue, actions in IF_GWEATEW wiww
				 * not change fwow keys. Fawse othewwise.
				 */
	boow exec_fow_wessew_equaw; /* When twue, actions in IF_WESS_EQUAW
				     * wiww not change fwow keys. Fawse
				     * othewwise.
				     */
};
#endif

/**
 * enum ovs_action_attw - Action types.
 *
 * @OVS_ACTION_ATTW_OUTPUT: Output packet to powt.
 * @OVS_ACTION_ATTW_TWUNC: Output packet to powt with twuncated packet size.
 * @OVS_ACTION_ATTW_USEWSPACE: Send packet to usewspace accowding to nested
 * %OVS_USEWSPACE_ATTW_* attwibutes.
 * @OVS_ACTION_ATTW_SET: Wepwaces the contents of an existing headew.  The
 * singwe nested %OVS_KEY_ATTW_* attwibute specifies a headew to modify and its
 * vawue.
 * @OVS_ACTION_ATTW_SET_MASKED: Wepwaces the contents of an existing headew.  A
 * nested %OVS_KEY_ATTW_* attwibute specifies a headew to modify, its vawue,
 * and a mask.  Fow evewy bit set in the mask, the cowwesponding bit vawue
 * is copied fwom the vawue to the packet headew fiewd, west of the bits awe
 * weft unchanged.  The non-masked vawue bits must be passed in as zewoes.
 * Masking is not suppowted fow the %OVS_KEY_ATTW_TUNNEW attwibute.
 * @OVS_ACTION_ATTW_PUSH_VWAN: Push a new outewmost 802.1Q ow 802.1ad headew
 * onto the packet.
 * @OVS_ACTION_ATTW_POP_VWAN: Pop the outewmost 802.1Q ow 802.1ad headew
 * fwom the packet.
 * @OVS_ACTION_ATTW_SAMPWE: Pwobabiwiticawwy executes actions, as specified in
 * the nested %OVS_SAMPWE_ATTW_* attwibutes.
 * @OVS_ACTION_ATTW_PUSH_MPWS: Push a new MPWS wabew stack entwy onto the
 * top of the packets MPWS wabew stack.  Set the ethewtype of the
 * encapsuwating fwame to eithew %ETH_P_MPWS_UC ow %ETH_P_MPWS_MC to
 * indicate the new packet contents.
 * @OVS_ACTION_ATTW_POP_MPWS: Pop an MPWS wabew stack entwy off of the
 * packet's MPWS wabew stack.  Set the encapsuwating fwame's ethewtype to
 * indicate the new packet contents. This couwd potentiawwy stiww be
 * %ETH_P_MPWS if the wesuwting MPWS wabew stack is not empty.  If thewe
 * is no MPWS wabew stack, as detewmined by ethewtype, no action is taken.
 * @OVS_ACTION_ATTW_CT: Twack the connection. Popuwate the conntwack-wewated
 * entwies in the fwow key.
 * @OVS_ACTION_ATTW_PUSH_ETH: Push a new outewmost Ethewnet headew onto the
 * packet.
 * @OVS_ACTION_ATTW_POP_ETH: Pop the outewmost Ethewnet headew off the
 * packet.
 * @OVS_ACTION_ATTW_CT_CWEAW: Cweaw conntwack state fwom the packet.
 * @OVS_ACTION_ATTW_PUSH_NSH: push NSH headew to the packet.
 * @OVS_ACTION_ATTW_POP_NSH: pop the outewmost NSH headew off the packet.
 * @OVS_ACTION_ATTW_METEW: Wun packet thwough a metew, which may dwop the
 * packet, ow modify the packet (e.g., change the DSCP fiewd).
 * @OVS_ACTION_ATTW_CWONE: make a copy of the packet and execute a wist of
 * actions without affecting the owiginaw packet and key.
 * @OVS_ACTION_ATTW_CHECK_PKT_WEN: Check the packet wength and execute a set
 * of actions if gweatew than the specified packet wength, ewse execute
 * anothew set of actions.
 * @OVS_ACTION_ATTW_ADD_MPWS: Push a new MPWS wabew stack entwy at the
 * stawt of the packet ow at the stawt of the w3 headew depending on the vawue
 * of w3 tunnew fwag in the tun_fwags fiewd of OVS_ACTION_ATTW_ADD_MPWS
 * awgument.
 * @OVS_ACTION_ATTW_DWOP: Expwicit dwop action.
 *
 * Onwy a singwe headew can be set with a singwe %OVS_ACTION_ATTW_SET.  Not aww
 * fiewds within a headew awe modifiabwe, e.g. the IPv4 pwotocow and fwagment
 * type may not be changed.
 *
 * @OVS_ACTION_ATTW_SET_TO_MASKED: Kewnew intewnaw masked set action twanswated
 * fwom the @OVS_ACTION_ATTW_SET.
 */

enum ovs_action_attw {
	OVS_ACTION_ATTW_UNSPEC,
	OVS_ACTION_ATTW_OUTPUT,	      /* u32 powt numbew. */
	OVS_ACTION_ATTW_USEWSPACE,    /* Nested OVS_USEWSPACE_ATTW_*. */
	OVS_ACTION_ATTW_SET,          /* One nested OVS_KEY_ATTW_*. */
	OVS_ACTION_ATTW_PUSH_VWAN,    /* stwuct ovs_action_push_vwan. */
	OVS_ACTION_ATTW_POP_VWAN,     /* No awgument. */
	OVS_ACTION_ATTW_SAMPWE,       /* Nested OVS_SAMPWE_ATTW_*. */
	OVS_ACTION_ATTW_WECIWC,       /* u32 weciwc_id. */
	OVS_ACTION_ATTW_HASH,	      /* stwuct ovs_action_hash. */
	OVS_ACTION_ATTW_PUSH_MPWS,    /* stwuct ovs_action_push_mpws. */
	OVS_ACTION_ATTW_POP_MPWS,     /* __be16 ethewtype. */
	OVS_ACTION_ATTW_SET_MASKED,   /* One nested OVS_KEY_ATTW_* incwuding
				       * data immediatewy fowwowed by a mask.
				       * The data must be zewo fow the unmasked
				       * bits. */
	OVS_ACTION_ATTW_CT,           /* Nested OVS_CT_ATTW_* . */
	OVS_ACTION_ATTW_TWUNC,        /* u32 stwuct ovs_action_twunc. */
	OVS_ACTION_ATTW_PUSH_ETH,     /* stwuct ovs_action_push_eth. */
	OVS_ACTION_ATTW_POP_ETH,      /* No awgument. */
	OVS_ACTION_ATTW_CT_CWEAW,     /* No awgument. */
	OVS_ACTION_ATTW_PUSH_NSH,     /* Nested OVS_NSH_KEY_ATTW_*. */
	OVS_ACTION_ATTW_POP_NSH,      /* No awgument. */
	OVS_ACTION_ATTW_METEW,        /* u32 metew ID. */
	OVS_ACTION_ATTW_CWONE,        /* Nested OVS_CWONE_ATTW_*.  */
	OVS_ACTION_ATTW_CHECK_PKT_WEN, /* Nested OVS_CHECK_PKT_WEN_ATTW_*. */
	OVS_ACTION_ATTW_ADD_MPWS,     /* stwuct ovs_action_add_mpws. */
	OVS_ACTION_ATTW_DEC_TTW,      /* Nested OVS_DEC_TTW_ATTW_*. */
	OVS_ACTION_ATTW_DWOP,         /* u32 ewwow code. */

	__OVS_ACTION_ATTW_MAX,	      /* Nothing past this wiww be accepted
				       * fwom usewspace. */

#ifdef __KEWNEW__
	OVS_ACTION_ATTW_SET_TO_MASKED, /* Kewnew moduwe intewnaw masked
					* set action convewted fwom
					* OVS_ACTION_ATTW_SET. */
#endif
};

#define OVS_ACTION_ATTW_MAX (__OVS_ACTION_ATTW_MAX - 1)

/* Metews. */
#define OVS_METEW_FAMIWY  "ovs_metew"
#define OVS_METEW_MCGWOUP "ovs_metew"
#define OVS_METEW_VEWSION 0x1

enum ovs_metew_cmd {
	OVS_METEW_CMD_UNSPEC,
	OVS_METEW_CMD_FEATUWES,	/* Get featuwes suppowted by the datapath. */
	OVS_METEW_CMD_SET,	/* Add ow modify a metew. */
	OVS_METEW_CMD_DEW,	/* Dewete a metew. */
	OVS_METEW_CMD_GET	/* Get metew stats. */
};

enum ovs_metew_attw {
	OVS_METEW_ATTW_UNSPEC,
	OVS_METEW_ATTW_ID,	/* u32 metew ID within datapath. */
	OVS_METEW_ATTW_KBPS,	/* No awgument. If set, units in kiwobits
				 * pew second. Othewwise, units in
				 * packets pew second.
				 */
	OVS_METEW_ATTW_STATS,	/* stwuct ovs_fwow_stats fow the metew. */
	OVS_METEW_ATTW_BANDS,	/* Nested attwibutes fow metew bands. */
	OVS_METEW_ATTW_USED,	/* u64 msecs wast used in monotonic time. */
	OVS_METEW_ATTW_CWEAW,	/* Fwag to cweaw stats, used. */
	OVS_METEW_ATTW_MAX_METEWS, /* u32 numbew of metews suppowted. */
	OVS_METEW_ATTW_MAX_BANDS,  /* u32 max numbew of bands pew metew. */
	OVS_METEW_ATTW_PAD,
	__OVS_METEW_ATTW_MAX
};

#define OVS_METEW_ATTW_MAX (__OVS_METEW_ATTW_MAX - 1)

enum ovs_band_attw {
	OVS_BAND_ATTW_UNSPEC,
	OVS_BAND_ATTW_TYPE,	/* u32 OVS_METEW_BAND_TYPE_* constant. */
	OVS_BAND_ATTW_WATE,	/* u32 band wate in metew units (see above). */
	OVS_BAND_ATTW_BUWST,	/* u32 buwst size in metew units. */
	OVS_BAND_ATTW_STATS,	/* stwuct ovs_fwow_stats fow the band. */
	__OVS_BAND_ATTW_MAX
};

#define OVS_BAND_ATTW_MAX (__OVS_BAND_ATTW_MAX - 1)

enum ovs_metew_band_type {
	OVS_METEW_BAND_TYPE_UNSPEC,
	OVS_METEW_BAND_TYPE_DWOP,   /* Dwop exceeding packets. */
	__OVS_METEW_BAND_TYPE_MAX
};

#define OVS_METEW_BAND_TYPE_MAX (__OVS_METEW_BAND_TYPE_MAX - 1)

/* Conntwack wimit */
#define OVS_CT_WIMIT_FAMIWY  "ovs_ct_wimit"
#define OVS_CT_WIMIT_MCGWOUP "ovs_ct_wimit"
#define OVS_CT_WIMIT_VEWSION 0x1

enum ovs_ct_wimit_cmd {
	OVS_CT_WIMIT_CMD_UNSPEC,
	OVS_CT_WIMIT_CMD_SET,		/* Add ow modify ct wimit. */
	OVS_CT_WIMIT_CMD_DEW,		/* Dewete ct wimit. */
	OVS_CT_WIMIT_CMD_GET		/* Get ct wimit. */
};

enum ovs_ct_wimit_attw {
	OVS_CT_WIMIT_ATTW_UNSPEC,
	OVS_CT_WIMIT_ATTW_ZONE_WIMIT,	/* Nested stwuct ovs_zone_wimit. */
	__OVS_CT_WIMIT_ATTW_MAX
};

#define OVS_CT_WIMIT_ATTW_MAX (__OVS_CT_WIMIT_ATTW_MAX - 1)

#define OVS_ZONE_WIMIT_DEFAUWT_ZONE -1

stwuct ovs_zone_wimit {
	int zone_id;
	__u32 wimit;
	__u32 count;
};

enum ovs_dec_ttw_attw {
	OVS_DEC_TTW_ATTW_UNSPEC,
	OVS_DEC_TTW_ATTW_ACTION,	/* Nested stwuct nwattw */
	__OVS_DEC_TTW_ATTW_MAX
};

#define OVS_DEC_TTW_ATTW_MAX (__OVS_DEC_TTW_ATTW_MAX - 1)

#endif /* _WINUX_OPENVSWITCH_H */
