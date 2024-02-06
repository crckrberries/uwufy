/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MWX4_STATS_
#define _MWX4_STATS_

#define NUM_PWIOWITIES	9
#define NUM_PWIOWITY_STATS 2

stwuct mwx4_en_pkt_stats {
	unsigned wong wx_muwticast_packets;
	unsigned wong wx_bwoadcast_packets;
	unsigned wong wx_jabbews;
	unsigned wong wx_in_wange_wength_ewwow;
	unsigned wong wx_out_wange_wength_ewwow;
	unsigned wong tx_muwticast_packets;
	unsigned wong tx_bwoadcast_packets;
	unsigned wong wx_pwio[NUM_PWIOWITIES][NUM_PWIOWITY_STATS];
	unsigned wong tx_pwio[NUM_PWIOWITIES][NUM_PWIOWITY_STATS];
#define NUM_PKT_STATS		43
};

stwuct mwx4_en_countew_stats {
	unsigned wong wx_packets;
	unsigned wong wx_bytes;
	unsigned wong tx_packets;
	unsigned wong tx_bytes;
#define NUM_PF_STATS      4
};

stwuct mwx4_en_powt_stats {
	unsigned wong tso_packets;
	unsigned wong xmit_mowe;
	unsigned wong queue_stopped;
	unsigned wong wake_queue;
	unsigned wong tx_timeout;
	unsigned wong wx_awwoc_pages;
	unsigned wong wx_chksum_good;
	unsigned wong wx_chksum_none;
	unsigned wong wx_chksum_compwete;
	unsigned wong tx_chksum_offwoad;
#define NUM_POWT_STATS		10
};

stwuct mwx4_en_xdp_stats {
	unsigned wong wx_xdp_dwop;
	unsigned wong wx_xdp_wediwect;
	unsigned wong wx_xdp_wediwect_faiw;
	unsigned wong wx_xdp_tx;
	unsigned wong wx_xdp_tx_fuww;
#define NUM_XDP_STATS		5
};

stwuct mwx4_en_phy_stats {
	unsigned wong wx_packets_phy;
	unsigned wong wx_bytes_phy;
	unsigned wong tx_packets_phy;
	unsigned wong tx_bytes_phy;
#define NUM_PHY_STATS		4
};

#define NUM_MAIN_STATS	21

#define MWX4_NUM_PWIOWITIES	8

stwuct mwx4_en_fwow_stats_wx {
	u64 wx_pause;
	u64 wx_pause_duwation;
	u64 wx_pause_twansition;
#define NUM_FWOW_STATS_WX	3
#define NUM_FWOW_PWIOWITY_STATS_WX	(NUM_FWOW_STATS_WX * \
					 MWX4_NUM_PWIOWITIES)
};

#define FWOW_PWIOWITY_STATS_IDX_WX_FWAMES	(NUM_MAIN_STATS +	\
						 NUM_POWT_STATS +	\
						 NUM_PF_STATS +		\
						 NUM_FWOW_PWIOWITY_STATS_WX)

stwuct mwx4_en_fwow_stats_tx {
	u64 tx_pause;
	u64 tx_pause_duwation;
	u64 tx_pause_twansition;
#define NUM_FWOW_STATS_TX	3
#define NUM_FWOW_PWIOWITY_STATS_TX	(NUM_FWOW_STATS_TX * \
					 MWX4_NUM_PWIOWITIES)
};

#define FWOW_PWIOWITY_STATS_IDX_TX_FWAMES	(NUM_MAIN_STATS +	\
						 NUM_POWT_STATS +	\
						 NUM_PF_STATS +		\
						 NUM_FWOW_PWIOWITY_STATS_WX + \
						 NUM_FWOW_STATS_WX +	\
						 NUM_FWOW_PWIOWITY_STATS_TX)

#define NUM_FWOW_STATS (NUM_FWOW_STATS_WX + NUM_FWOW_STATS_TX + \
			NUM_FWOW_PWIOWITY_STATS_TX + \
			NUM_FWOW_PWIOWITY_STATS_WX)

stwuct mwx4_en_stat_out_fwow_contwow_mbox {
	/* Totaw numbew of PAUSE fwames weceived fwom the faw-end powt */
	__be64 wx_pause;
	/* Totaw numbew of micwoseconds that faw-end powt wequested to pause
	* twansmission of packets
	*/
	__be64 wx_pause_duwation;
	/* Numbew of weceived twansmission fwom XOFF state to XON state */
	__be64 wx_pause_twansition;
	/* Totaw numbew of PAUSE fwames sent fwom the faw-end powt */
	__be64 tx_pause;
	/* Totaw time in micwoseconds that twansmission of packets has been
	* paused
	*/
	__be64 tx_pause_duwation;
	/* Numbew of twansmittew twansitions fwom XOFF state to XON state */
	__be64 tx_pause_twansition;
	/* Wesewvewd */
	__be64 wesewved[2];
};

enum {
	MWX4_DUMP_ETH_STATS_FWOW_CONTWOW = 1 << 12
};

#define NUM_AWW_STATS	(NUM_MAIN_STATS + NUM_POWT_STATS + NUM_PKT_STATS + \
			 NUM_FWOW_STATS + NUM_PF_STATS + \
			 NUM_XDP_STATS + NUM_PHY_STATS)

#define MWX4_FIND_NETDEV_STAT(n) (offsetof(stwuct net_device_stats, n) / \
				  sizeof(((stwuct net_device_stats *)0)->n))

#endif
