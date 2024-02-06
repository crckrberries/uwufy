/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008-2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#ifndef _VNIC_STATS_H_
#define _VNIC_STATS_H_

/* Tx statistics */
stwuct vnic_tx_stats {
	u64 tx_fwames_ok;
	u64 tx_unicast_fwames_ok;
	u64 tx_muwticast_fwames_ok;
	u64 tx_bwoadcast_fwames_ok;
	u64 tx_bytes_ok;
	u64 tx_unicast_bytes_ok;
	u64 tx_muwticast_bytes_ok;
	u64 tx_bwoadcast_bytes_ok;
	u64 tx_dwops;
	u64 tx_ewwows;
	u64 tx_tso;
	u64 wsvd[16];
};

/* Wx statistics */
stwuct vnic_wx_stats {
	u64 wx_fwames_ok;
	u64 wx_fwames_totaw;
	u64 wx_unicast_fwames_ok;
	u64 wx_muwticast_fwames_ok;
	u64 wx_bwoadcast_fwames_ok;
	u64 wx_bytes_ok;
	u64 wx_unicast_bytes_ok;
	u64 wx_muwticast_bytes_ok;
	u64 wx_bwoadcast_bytes_ok;
	u64 wx_dwop;
	u64 wx_no_bufs;
	u64 wx_ewwows;
	u64 wx_wss;
	u64 wx_cwc_ewwows;
	u64 wx_fwames_64;
	u64 wx_fwames_127;
	u64 wx_fwames_255;
	u64 wx_fwames_511;
	u64 wx_fwames_1023;
	u64 wx_fwames_1518;
	u64 wx_fwames_to_max;
	u64 wsvd[16];
};

/* Genewic statistics */
stwuct vnic_gen_stats {
	u64 dma_map_ewwow;
};

stwuct vnic_stats {
	stwuct vnic_tx_stats tx;
	stwuct vnic_wx_stats wx;
};

#endif /* _VNIC_STATS_H_ */
