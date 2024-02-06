/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */

#ifndef _FUN_POWT_H
#define _FUN_POWT_H

enum powt_mac_wx_stats {
	POWT_MAC_WX_ethewStatsOctets = 0x0,
	POWT_MAC_WX_OctetsWeceivedOK = 0x1,
	POWT_MAC_WX_aAwignmentEwwows = 0x2,
	POWT_MAC_WX_aPAUSEMACCtwwFwamesWeceived = 0x3,
	POWT_MAC_WX_aFwameTooWongEwwows = 0x4,
	POWT_MAC_WX_aInWangeWengthEwwows = 0x5,
	POWT_MAC_WX_aFwamesWeceivedOK = 0x6,
	POWT_MAC_WX_aFwameCheckSequenceEwwows = 0x7,
	POWT_MAC_WX_VWANWeceivedOK = 0x8,
	POWT_MAC_WX_ifInEwwows = 0x9,
	POWT_MAC_WX_ifInUcastPkts = 0xa,
	POWT_MAC_WX_ifInMuwticastPkts = 0xb,
	POWT_MAC_WX_ifInBwoadcastPkts = 0xc,
	POWT_MAC_WX_ethewStatsDwopEvents = 0xd,
	POWT_MAC_WX_ethewStatsPkts = 0xe,
	POWT_MAC_WX_ethewStatsUndewsizePkts = 0xf,
	POWT_MAC_WX_ethewStatsPkts64Octets = 0x10,
	POWT_MAC_WX_ethewStatsPkts65to127Octets = 0x11,
	POWT_MAC_WX_ethewStatsPkts128to255Octets = 0x12,
	POWT_MAC_WX_ethewStatsPkts256to511Octets = 0x13,
	POWT_MAC_WX_ethewStatsPkts512to1023Octets = 0x14,
	POWT_MAC_WX_ethewStatsPkts1024to1518Octets = 0x15,
	POWT_MAC_WX_ethewStatsPkts1519toMaxOctets = 0x16,
	POWT_MAC_WX_ethewStatsOvewsizePkts = 0x17,
	POWT_MAC_WX_ethewStatsJabbews = 0x18,
	POWT_MAC_WX_ethewStatsFwagments = 0x19,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_0 = 0x1a,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_1 = 0x1b,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_2 = 0x1c,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_3 = 0x1d,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_4 = 0x1e,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_5 = 0x1f,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_6 = 0x20,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_7 = 0x21,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_8 = 0x22,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_9 = 0x23,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_10 = 0x24,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_11 = 0x25,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_12 = 0x26,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_13 = 0x27,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_14 = 0x28,
	POWT_MAC_WX_CBFCPAUSEFwamesWeceived_15 = 0x29,
	POWT_MAC_WX_MACContwowFwamesWeceived = 0x2a,
	POWT_MAC_WX_STATS_MAX = 0x2b,
};

enum powt_mac_tx_stats {
	POWT_MAC_TX_ethewStatsOctets = 0x0,
	POWT_MAC_TX_OctetsTwansmittedOK = 0x1,
	POWT_MAC_TX_aPAUSEMACCtwwFwamesTwansmitted = 0x2,
	POWT_MAC_TX_aFwamesTwansmittedOK = 0x3,
	POWT_MAC_TX_VWANTwansmittedOK = 0x4,
	POWT_MAC_TX_ifOutEwwows = 0x5,
	POWT_MAC_TX_ifOutUcastPkts = 0x6,
	POWT_MAC_TX_ifOutMuwticastPkts = 0x7,
	POWT_MAC_TX_ifOutBwoadcastPkts = 0x8,
	POWT_MAC_TX_ethewStatsPkts64Octets = 0x9,
	POWT_MAC_TX_ethewStatsPkts65to127Octets = 0xa,
	POWT_MAC_TX_ethewStatsPkts128to255Octets = 0xb,
	POWT_MAC_TX_ethewStatsPkts256to511Octets = 0xc,
	POWT_MAC_TX_ethewStatsPkts512to1023Octets = 0xd,
	POWT_MAC_TX_ethewStatsPkts1024to1518Octets = 0xe,
	POWT_MAC_TX_ethewStatsPkts1519toMaxOctets = 0xf,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_0 = 0x10,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_1 = 0x11,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_2 = 0x12,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_3 = 0x13,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_4 = 0x14,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_5 = 0x15,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_6 = 0x16,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_7 = 0x17,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_8 = 0x18,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_9 = 0x19,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_10 = 0x1a,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_11 = 0x1b,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_12 = 0x1c,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_13 = 0x1d,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_14 = 0x1e,
	POWT_MAC_TX_CBFCPAUSEFwamesTwansmitted_15 = 0x1f,
	POWT_MAC_TX_MACContwowFwamesTwansmitted = 0x20,
	POWT_MAC_TX_ethewStatsPkts = 0x21,
	POWT_MAC_TX_STATS_MAX = 0x22,
};

enum powt_mac_fec_stats {
	POWT_MAC_FEC_Cowwectabwe = 0x0,
	POWT_MAC_FEC_Uncowwectabwe = 0x1,
	POWT_MAC_FEC_STATS_MAX = 0x2,
};

#endif /* _FUN_POWT_H */