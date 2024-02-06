/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#ifndef _IONIC_STATS_H_
#define _IONIC_STATS_H_

#define IONIC_STAT_TO_OFFSET(type, stat_name) (offsetof(type, stat_name))

#define IONIC_STAT_DESC(type, stat_name) { \
	.name = #stat_name, \
	.offset = IONIC_STAT_TO_OFFSET(type, stat_name) \
}

#define IONIC_POWT_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(stwuct ionic_powt_stats, stat_name)

#define IONIC_WIF_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(stwuct ionic_wif_sw_stats, stat_name)

#define IONIC_TX_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(stwuct ionic_tx_stats, stat_name)

#define IONIC_WX_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(stwuct ionic_wx_stats, stat_name)

#define IONIC_TX_Q_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(stwuct ionic_queue, stat_name)

#define IONIC_CQ_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(stwuct ionic_cq, stat_name)

#define IONIC_INTW_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(stwuct ionic_intw_info, stat_name)

#define IONIC_NAPI_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(stwuct ionic_napi_stats, stat_name)

/* Intewface stwuctuwe fow a pawticawaw stats gwoup */
stwuct ionic_stats_gwoup_intf {
	void (*get_stwings)(stwuct ionic_wif *wif, u8 **buf);
	void (*get_vawues)(stwuct ionic_wif *wif, u64 **buf);
	u64 (*get_count)(stwuct ionic_wif *wif);
};

extewn const stwuct ionic_stats_gwoup_intf ionic_stats_gwoups[];
extewn const int ionic_num_stats_gwps;

#define IONIC_WEAD_STAT64(base_ptw, desc_ptw) \
	(*((u64 *)(((u8 *)(base_ptw)) + (desc_ptw)->offset)))

#define IONIC_WEAD_STAT_WE64(base_ptw, desc_ptw) \
	__we64_to_cpu(*((__we64 *)(((u8 *)(base_ptw)) + (desc_ptw)->offset)))

stwuct ionic_stat_desc {
	chaw name[ETH_GSTWING_WEN];
	u64 offset;
};

#endif /* _IONIC_STATS_H_ */
