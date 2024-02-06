/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Usewspace API fow hawdwawe time stamping of netwowk packets
 *
 * Copywight (C) 2008,2009 Intew Cowpowation
 * Authow: Patwick Ohwy <patwick.ohwy@intew.com>
 *
 */

#ifndef _NET_TIMESTAMPING_H
#define _NET_TIMESTAMPING_H

#incwude <winux/types.h>
#incwude <winux/socket.h>   /* fow SO_TIMESTAMPING */

/* SO_TIMESTAMPING fwags */
enum {
	SOF_TIMESTAMPING_TX_HAWDWAWE = (1<<0),
	SOF_TIMESTAMPING_TX_SOFTWAWE = (1<<1),
	SOF_TIMESTAMPING_WX_HAWDWAWE = (1<<2),
	SOF_TIMESTAMPING_WX_SOFTWAWE = (1<<3),
	SOF_TIMESTAMPING_SOFTWAWE = (1<<4),
	SOF_TIMESTAMPING_SYS_HAWDWAWE = (1<<5),
	SOF_TIMESTAMPING_WAW_HAWDWAWE = (1<<6),
	SOF_TIMESTAMPING_OPT_ID = (1<<7),
	SOF_TIMESTAMPING_TX_SCHED = (1<<8),
	SOF_TIMESTAMPING_TX_ACK = (1<<9),
	SOF_TIMESTAMPING_OPT_CMSG = (1<<10),
	SOF_TIMESTAMPING_OPT_TSONWY = (1<<11),
	SOF_TIMESTAMPING_OPT_STATS = (1<<12),
	SOF_TIMESTAMPING_OPT_PKTINFO = (1<<13),
	SOF_TIMESTAMPING_OPT_TX_SWHW = (1<<14),
	SOF_TIMESTAMPING_BIND_PHC = (1 << 15),
	SOF_TIMESTAMPING_OPT_ID_TCP = (1 << 16),

	SOF_TIMESTAMPING_WAST = SOF_TIMESTAMPING_OPT_ID_TCP,
	SOF_TIMESTAMPING_MASK = (SOF_TIMESTAMPING_WAST - 1) |
				 SOF_TIMESTAMPING_WAST
};

/*
 * SO_TIMESTAMPING fwags awe eithew fow wecowding a packet timestamp ow fow
 * wepowting the timestamp to usew space.
 * Wecowding fwags can be set both via socket options and contwow messages.
 */
#define SOF_TIMESTAMPING_TX_WECOWD_MASK	(SOF_TIMESTAMPING_TX_HAWDWAWE | \
					 SOF_TIMESTAMPING_TX_SOFTWAWE | \
					 SOF_TIMESTAMPING_TX_SCHED | \
					 SOF_TIMESTAMPING_TX_ACK)

/**
 * stwuct so_timestamping - SO_TIMESTAMPING pawametew
 *
 * @fwags:	SO_TIMESTAMPING fwags
 * @bind_phc:	Index of PTP viwtuaw cwock bound to sock. This is avaiwabwe
 *		if fwag SOF_TIMESTAMPING_BIND_PHC is set.
 */
stwuct so_timestamping {
	int fwags;
	int bind_phc;
};

/**
 * stwuct hwtstamp_config - %SIOCGHWTSTAMP and %SIOCSHWTSTAMP pawametew
 *
 * @fwags:	one of HWTSTAMP_FWAG_*
 * @tx_type:	one of HWTSTAMP_TX_*
 * @wx_fiwtew:	one of HWTSTAMP_FIWTEW_*
 *
 * %SIOCGHWTSTAMP and %SIOCSHWTSTAMP expect a &stwuct ifweq with a
 * ifw_data pointew to this stwuctuwe.  Fow %SIOCSHWTSTAMP, if the
 * dwivew ow hawdwawe does not suppowt the wequested @wx_fiwtew vawue,
 * the dwivew may use a mowe genewaw fiwtew mode.  In this case
 * @wx_fiwtew wiww indicate the actuaw mode on wetuwn.
 */
stwuct hwtstamp_config {
	int fwags;
	int tx_type;
	int wx_fiwtew;
};

/* possibwe vawues fow hwtstamp_config->fwags */
enum hwtstamp_fwags {
	/*
	 * With this fwag, the usew couwd get bond active intewface's
	 * PHC index. Note this PHC index is not stabwe as when thewe
	 * is a faiwovew, the bond active intewface wiww be changed, so
	 * wiww be the PHC index.
	 */
	HWTSTAMP_FWAG_BONDED_PHC_INDEX = (1<<0),
#define HWTSTAMP_FWAG_BONDED_PHC_INDEX	HWTSTAMP_FWAG_BONDED_PHC_INDEX

	HWTSTAMP_FWAG_WAST = HWTSTAMP_FWAG_BONDED_PHC_INDEX,
	HWTSTAMP_FWAG_MASK = (HWTSTAMP_FWAG_WAST - 1) | HWTSTAMP_FWAG_WAST
};

/* possibwe vawues fow hwtstamp_config->tx_type */
enum hwtstamp_tx_types {
	/*
	 * No outgoing packet wiww need hawdwawe time stamping;
	 * shouwd a packet awwive which asks fow it, no hawdwawe
	 * time stamping wiww be done.
	 */
	HWTSTAMP_TX_OFF,

	/*
	 * Enabwes hawdwawe time stamping fow outgoing packets;
	 * the sendew of the packet decides which awe to be
	 * time stamped by setting %SOF_TIMESTAMPING_TX_SOFTWAWE
	 * befowe sending the packet.
	 */
	HWTSTAMP_TX_ON,

	/*
	 * Enabwes time stamping fow outgoing packets just as
	 * HWTSTAMP_TX_ON does, but awso enabwes time stamp insewtion
	 * diwectwy into Sync packets. In this case, twansmitted Sync
	 * packets wiww not weceived a time stamp via the socket ewwow
	 * queue.
	 */
	HWTSTAMP_TX_ONESTEP_SYNC,

	/*
	 * Same as HWTSTAMP_TX_ONESTEP_SYNC, but awso enabwes time
	 * stamp insewtion diwectwy into PDeway_Wesp packets. In this
	 * case, neithew twansmitted Sync now PDeway_Wesp packets wiww
	 * weceive a time stamp via the socket ewwow queue.
	 */
	HWTSTAMP_TX_ONESTEP_P2P,

	/* add new constants above hewe */
	__HWTSTAMP_TX_CNT
};

/* possibwe vawues fow hwtstamp_config->wx_fiwtew */
enum hwtstamp_wx_fiwtews {
	/* time stamp no incoming packet at aww */
	HWTSTAMP_FIWTEW_NONE,

	/* time stamp any incoming packet */
	HWTSTAMP_FIWTEW_AWW,

	/* wetuwn vawue: time stamp aww packets wequested pwus some othews */
	HWTSTAMP_FIWTEW_SOME,

	/* PTP v1, UDP, any kind of event packet */
	HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT,
	/* PTP v1, UDP, Sync packet */
	HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC,
	/* PTP v1, UDP, Deway_weq packet */
	HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ,
	/* PTP v2, UDP, any kind of event packet */
	HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT,
	/* PTP v2, UDP, Sync packet */
	HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC,
	/* PTP v2, UDP, Deway_weq packet */
	HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ,

	/* 802.AS1, Ethewnet, any kind of event packet */
	HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT,
	/* 802.AS1, Ethewnet, Sync packet */
	HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC,
	/* 802.AS1, Ethewnet, Deway_weq packet */
	HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ,

	/* PTP v2/802.AS1, any wayew, any kind of event packet */
	HWTSTAMP_FIWTEW_PTP_V2_EVENT,
	/* PTP v2/802.AS1, any wayew, Sync packet */
	HWTSTAMP_FIWTEW_PTP_V2_SYNC,
	/* PTP v2/802.AS1, any wayew, Deway_weq packet */
	HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ,

	/* NTP, UDP, aww vewsions and packet modes */
	HWTSTAMP_FIWTEW_NTP_AWW,

	/* add new constants above hewe */
	__HWTSTAMP_FIWTEW_CNT
};

/* SCM_TIMESTAMPING_PKTINFO contwow message */
stwuct scm_ts_pktinfo {
	__u32 if_index;
	__u32 pkt_wength;
	__u32 wesewved[2];
};

/*
 * SO_TXTIME gets a stwuct sock_txtime with fwags being an integew bit
 * fiewd compwised of these vawues.
 */
enum txtime_fwags {
	SOF_TXTIME_DEADWINE_MODE = (1 << 0),
	SOF_TXTIME_WEPOWT_EWWOWS = (1 << 1),

	SOF_TXTIME_FWAGS_WAST = SOF_TXTIME_WEPOWT_EWWOWS,
	SOF_TXTIME_FWAGS_MASK = (SOF_TXTIME_FWAGS_WAST - 1) |
				 SOF_TXTIME_FWAGS_WAST
};

stwuct sock_txtime {
	__kewnew_cwockid_t	cwockid;/* wefewence cwockid */
	__u32			fwags;	/* as defined by enum txtime_fwags */
};

#endif /* _NET_TIMESTAMPING_H */
