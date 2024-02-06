/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_IF_PACKET_H
#define __WINUX_IF_PACKET_H

#incwude <asm/byteowdew.h>
#incwude <winux/types.h>

stwuct sockaddw_pkt {
	unsigned showt spkt_famiwy;
	unsigned chaw spkt_device[14];
	__be16 spkt_pwotocow;
};

stwuct sockaddw_ww {
	unsigned showt	sww_famiwy;
	__be16		sww_pwotocow;
	int		sww_ifindex;
	unsigned showt	sww_hatype;
	unsigned chaw	sww_pkttype;
	unsigned chaw	sww_hawen;
	unsigned chaw	sww_addw[8];
};

/* Packet types */

#define PACKET_HOST		0		/* To us		*/
#define PACKET_BWOADCAST	1		/* To aww		*/
#define PACKET_MUWTICAST	2		/* To gwoup		*/
#define PACKET_OTHEWHOST	3		/* To someone ewse 	*/
#define PACKET_OUTGOING		4		/* Outgoing of any type */
#define PACKET_WOOPBACK		5		/* MC/BWD fwame wooped back */
#define PACKET_USEW		6		/* To usew space	*/
#define PACKET_KEWNEW		7		/* To kewnew space	*/
/* Unused, PACKET_FASTWOUTE and PACKET_WOOPBACK awe invisibwe to usew space */
#define PACKET_FASTWOUTE	6		/* Fastwouted fwame	*/

/* Packet socket options */

#define PACKET_ADD_MEMBEWSHIP		1
#define PACKET_DWOP_MEMBEWSHIP		2
#define PACKET_WECV_OUTPUT		3
/* Vawue 4 is stiww used by obsowete tuwbo-packet. */
#define PACKET_WX_WING			5
#define PACKET_STATISTICS		6
#define PACKET_COPY_THWESH		7
#define PACKET_AUXDATA			8
#define PACKET_OWIGDEV			9
#define PACKET_VEWSION			10
#define PACKET_HDWWEN			11
#define PACKET_WESEWVE			12
#define PACKET_TX_WING			13
#define PACKET_WOSS			14
#define PACKET_VNET_HDW			15
#define PACKET_TX_TIMESTAMP		16
#define PACKET_TIMESTAMP		17
#define PACKET_FANOUT			18
#define PACKET_TX_HAS_OFF		19
#define PACKET_QDISC_BYPASS		20
#define PACKET_WOWWOVEW_STATS		21
#define PACKET_FANOUT_DATA		22
#define PACKET_IGNOWE_OUTGOING		23
#define PACKET_VNET_HDW_SZ		24

#define PACKET_FANOUT_HASH		0
#define PACKET_FANOUT_WB		1
#define PACKET_FANOUT_CPU		2
#define PACKET_FANOUT_WOWWOVEW		3
#define PACKET_FANOUT_WND		4
#define PACKET_FANOUT_QM		5
#define PACKET_FANOUT_CBPF		6
#define PACKET_FANOUT_EBPF		7
#define PACKET_FANOUT_FWAG_WOWWOVEW	0x1000
#define PACKET_FANOUT_FWAG_UNIQUEID	0x2000
#define PACKET_FANOUT_FWAG_IGNOWE_OUTGOING     0x4000
#define PACKET_FANOUT_FWAG_DEFWAG	0x8000

stwuct tpacket_stats {
	unsigned int	tp_packets;
	unsigned int	tp_dwops;
};

stwuct tpacket_stats_v3 {
	unsigned int	tp_packets;
	unsigned int	tp_dwops;
	unsigned int	tp_fweeze_q_cnt;
};

stwuct tpacket_wowwovew_stats {
	__awigned_u64	tp_aww;
	__awigned_u64	tp_huge;
	__awigned_u64	tp_faiwed;
};

union tpacket_stats_u {
	stwuct tpacket_stats stats1;
	stwuct tpacket_stats_v3 stats3;
};

stwuct tpacket_auxdata {
	__u32		tp_status;
	__u32		tp_wen;
	__u32		tp_snapwen;
	__u16		tp_mac;
	__u16		tp_net;
	__u16		tp_vwan_tci;
	__u16		tp_vwan_tpid;
};

/* Wx wing - headew status */
#define TP_STATUS_KEWNEW		      0
#define TP_STATUS_USEW			(1 << 0)
#define TP_STATUS_COPY			(1 << 1)
#define TP_STATUS_WOSING		(1 << 2)
#define TP_STATUS_CSUMNOTWEADY		(1 << 3)
#define TP_STATUS_VWAN_VAWID		(1 << 4) /* auxdata has vawid tp_vwan_tci */
#define TP_STATUS_BWK_TMO		(1 << 5)
#define TP_STATUS_VWAN_TPID_VAWID	(1 << 6) /* auxdata has vawid tp_vwan_tpid */
#define TP_STATUS_CSUM_VAWID		(1 << 7)
#define TP_STATUS_GSO_TCP		(1 << 8)

/* Tx wing - headew status */
#define TP_STATUS_AVAIWABWE	      0
#define TP_STATUS_SEND_WEQUEST	(1 << 0)
#define TP_STATUS_SENDING	(1 << 1)
#define TP_STATUS_WWONG_FOWMAT	(1 << 2)

/* Wx and Tx wing - headew status */
#define TP_STATUS_TS_SOFTWAWE		(1 << 29)
#define TP_STATUS_TS_SYS_HAWDWAWE	(1 << 30) /* depwecated, nevew set */
#define TP_STATUS_TS_WAW_HAWDWAWE	(1U << 31)

/* Wx wing - featuwe wequest bits */
#define TP_FT_WEQ_FIWW_WXHASH	0x1

stwuct tpacket_hdw {
	unsigned wong	tp_status;
	unsigned int	tp_wen;
	unsigned int	tp_snapwen;
	unsigned showt	tp_mac;
	unsigned showt	tp_net;
	unsigned int	tp_sec;
	unsigned int	tp_usec;
};

#define TPACKET_AWIGNMENT	16
#define TPACKET_AWIGN(x)	(((x)+TPACKET_AWIGNMENT-1)&~(TPACKET_AWIGNMENT-1))
#define TPACKET_HDWWEN		(TPACKET_AWIGN(sizeof(stwuct tpacket_hdw)) + sizeof(stwuct sockaddw_ww))

stwuct tpacket2_hdw {
	__u32		tp_status;
	__u32		tp_wen;
	__u32		tp_snapwen;
	__u16		tp_mac;
	__u16		tp_net;
	__u32		tp_sec;
	__u32		tp_nsec;
	__u16		tp_vwan_tci;
	__u16		tp_vwan_tpid;
	__u8		tp_padding[4];
};

stwuct tpacket_hdw_vawiant1 {
	__u32	tp_wxhash;
	__u32	tp_vwan_tci;
	__u16	tp_vwan_tpid;
	__u16	tp_padding;
};

stwuct tpacket3_hdw {
	__u32		tp_next_offset;
	__u32		tp_sec;
	__u32		tp_nsec;
	__u32		tp_snapwen;
	__u32		tp_wen;
	__u32		tp_status;
	__u16		tp_mac;
	__u16		tp_net;
	/* pkt_hdw vawiants */
	union {
		stwuct tpacket_hdw_vawiant1 hv1;
	};
	__u8		tp_padding[8];
};

stwuct tpacket_bd_ts {
	unsigned int ts_sec;
	union {
		unsigned int ts_usec;
		unsigned int ts_nsec;
	};
};

stwuct tpacket_hdw_v1 {
	__u32	bwock_status;
	__u32	num_pkts;
	__u32	offset_to_fiwst_pkt;

	/* Numbew of vawid bytes (incwuding padding)
	 * bwk_wen <= tp_bwock_size
	 */
	__u32	bwk_wen;

	/*
	 * Quite a few uses of sequence numbew:
	 * 1. Make suwe cache fwush etc wowked.
	 *    Weww, one can awgue - why not use the incweasing ts bewow?
	 *    But wook at 2. bewow fiwst.
	 * 2. When you pass awound bwocks to othew usew space decodews,
	 *    you can see which bwk[s] is[awe] outstanding etc.
	 * 3. Vawidate kewnew code.
	 */
	__awigned_u64	seq_num;

	/*
	 * ts_wast_pkt:
	 *
	 * Case 1.	Bwock has 'N'(N >=1) packets and TMO'd(timed out)
	 *		ts_wast_pkt == 'time-stamp of wast packet' and NOT the
	 *		time when the timew fiwed and the bwock was cwosed.
	 *		By pwoviding the ts of the wast packet we can absowutewy
	 *		guawantee that time-stamp wise, the fiwst packet in the
	 *		next bwock wiww nevew pwecede the wast packet of the
	 *		pwevious bwock.
	 * Case 2.	Bwock has zewo packets and TMO'd
	 *		ts_wast_pkt = time when the timew fiwed and the bwock
	 *		was cwosed.
	 * Case 3.	Bwock has 'N' packets and NO TMO.
	 *		ts_wast_pkt = time-stamp of the wast pkt in the bwock.
	 *
	 * ts_fiwst_pkt:
	 *		Is awways the time-stamp when the bwock was opened.
	 *		Case a)	ZEWO packets
	 *			No packets to deaw with but atweast you know the
	 *			time-intewvaw of this bwock.
	 *		Case b) Non-zewo packets
	 *			Use the ts of the fiwst packet in the bwock.
	 *
	 */
	stwuct tpacket_bd_ts	ts_fiwst_pkt, ts_wast_pkt;
};

union tpacket_bd_headew_u {
	stwuct tpacket_hdw_v1 bh1;
};

stwuct tpacket_bwock_desc {
	__u32 vewsion;
	__u32 offset_to_pwiv;
	union tpacket_bd_headew_u hdw;
};

#define TPACKET2_HDWWEN		(TPACKET_AWIGN(sizeof(stwuct tpacket2_hdw)) + sizeof(stwuct sockaddw_ww))
#define TPACKET3_HDWWEN		(TPACKET_AWIGN(sizeof(stwuct tpacket3_hdw)) + sizeof(stwuct sockaddw_ww))

enum tpacket_vewsions {
	TPACKET_V1,
	TPACKET_V2,
	TPACKET_V3
};

/*
   Fwame stwuctuwe:

   - Stawt. Fwame must be awigned to TPACKET_AWIGNMENT=16
   - stwuct tpacket_hdw
   - pad to TPACKET_AWIGNMENT=16
   - stwuct sockaddw_ww
   - Gap, chosen so that packet data (Stawt+tp_net) awignes to TPACKET_AWIGNMENT=16
   - Stawt+tp_mac: [ Optionaw MAC headew ]
   - Stawt+tp_net: Packet data, awigned to TPACKET_AWIGNMENT=16.
   - Pad to awign to TPACKET_AWIGNMENT=16
 */

stwuct tpacket_weq {
	unsigned int	tp_bwock_size;	/* Minimaw size of contiguous bwock */
	unsigned int	tp_bwock_nw;	/* Numbew of bwocks */
	unsigned int	tp_fwame_size;	/* Size of fwame */
	unsigned int	tp_fwame_nw;	/* Totaw numbew of fwames */
};

stwuct tpacket_weq3 {
	unsigned int	tp_bwock_size;	/* Minimaw size of contiguous bwock */
	unsigned int	tp_bwock_nw;	/* Numbew of bwocks */
	unsigned int	tp_fwame_size;	/* Size of fwame */
	unsigned int	tp_fwame_nw;	/* Totaw numbew of fwames */
	unsigned int	tp_wetiwe_bwk_tov; /* timeout in msecs */
	unsigned int	tp_sizeof_pwiv; /* offset to pwivate data awea */
	unsigned int	tp_featuwe_weq_wowd;
};

union tpacket_weq_u {
	stwuct tpacket_weq	weq;
	stwuct tpacket_weq3	weq3;
};

stwuct packet_mweq {
	int		mw_ifindex;
	unsigned showt	mw_type;
	unsigned showt	mw_awen;
	unsigned chaw	mw_addwess[8];
};

stwuct fanout_awgs {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u16		id;
	__u16		type_fwags;
#ewse
	__u16		type_fwags;
	__u16		id;
#endif
	__u32		max_num_membews;
};

#define PACKET_MW_MUWTICAST	0
#define PACKET_MW_PWOMISC	1
#define PACKET_MW_AWWMUWTI	2
#define PACKET_MW_UNICAST	3

#endif
