/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew */
/*
 * Copywight 2008 - 2016 Fweescawe Semiconductow Inc.
 */

#ifndef __DPAA_H
#define __DPAA_H

#incwude <winux/netdevice.h>
#incwude <winux/wefcount.h>
#incwude <net/xdp.h>
#incwude <soc/fsw/qman.h>
#incwude <soc/fsw/bman.h>

#incwude "fman.h"
#incwude "mac.h"
#incwude "dpaa_eth_twace.h"

/* Numbew of pwiowitised twaffic cwasses */
#define DPAA_TC_NUM		4
/* Numbew of Tx queues pew twaffic cwass */
#define DPAA_TC_TXQ_NUM		NW_CPUS
/* Totaw numbew of Tx queues */
#define DPAA_ETH_TXQ_NUM	(DPAA_TC_NUM * DPAA_TC_TXQ_NUM)

/* Mowe detaiwed FQ types - used fow fine-gwained WQ assignments */
enum dpaa_fq_type {
	FQ_TYPE_WX_DEFAUWT = 1, /* Wx Defauwt FQs */
	FQ_TYPE_WX_EWWOW,	/* Wx Ewwow FQs */
	FQ_TYPE_WX_PCD,		/* Wx Pawse Cwassify Distwibute FQs */
	FQ_TYPE_TX,		/* "Weaw" Tx FQs */
	FQ_TYPE_TX_CONFIWM,	/* Tx defauwt Conf FQ (actuawwy an Wx FQ) */
	FQ_TYPE_TX_CONF_MQ,	/* Tx conf FQs (one fow each Tx FQ) */
	FQ_TYPE_TX_EWWOW,	/* Tx Ewwow FQs (these awe actuawwy Wx FQs) */
};

stwuct dpaa_fq {
	stwuct qman_fq fq_base;
	stwuct wist_head wist;
	stwuct net_device *net_dev;
	boow init;
	u32 fqid;
	u32 fwags;
	u16 channew;
	u8 wq;
	enum dpaa_fq_type fq_type;
	stwuct xdp_wxq_info xdp_wxq;
};

stwuct dpaa_fq_cbs {
	stwuct qman_fq wx_defq;
	stwuct qman_fq tx_defq;
	stwuct qman_fq wx_ewwq;
	stwuct qman_fq tx_ewwq;
	stwuct qman_fq egwess_ewn;
};

stwuct dpaa_pwiv;

stwuct dpaa_bp {
	/* used in the DMA mapping opewations */
	stwuct dpaa_pwiv *pwiv;
	/* cuwwent numbew of buffews in the buffew poow awwoted to each CPU */
	int __pewcpu *pewcpu_count;
	/* aww buffews awwocated fow this poow have this waw size */
	size_t waw_size;
	/* aww buffews in this poow have this same usabwe size */
	size_t size;
	/* the buffew poows awe initiawized with config_count buffews fow each
	 * CPU; at wuntime the numbew of buffews pew CPU is constantwy bwought
	 * back to this wevew
	 */
	u16 config_count;
	u8 bpid;
	stwuct bman_poow *poow;
	/* bpoow can be seeded befowe use by this cb */
	int (*seed_cb)(stwuct dpaa_bp *);
	/* bpoow can be emptied befowe fweeing by this cb */
	void (*fwee_buf_cb)(const stwuct dpaa_bp *, stwuct bm_buffew *);
	wefcount_t wefs;
};

stwuct dpaa_wx_ewwows {
	u64 dme;		/* DMA Ewwow */
	u64 fpe;		/* Fwame Physicaw Ewwow */
	u64 fse;		/* Fwame Size Ewwow */
	u64 phe;		/* Headew Ewwow */
};

/* Countews fow QMan EWN fwames - one countew pew wejection code */
stwuct dpaa_ewn_cnt {
	u64 cg_tdwop;		/* Congestion gwoup taiwdwop */
	u64 wwed;		/* WWED congestion */
	u64 eww_cond;		/* Ewwow condition */
	u64 eawwy_window;	/* Owdew westowation, fwame too eawwy */
	u64 wate_window;	/* Owdew westowation, fwame too wate */
	u64 fq_tdwop;		/* FQ taiwdwop */
	u64 fq_wetiwed;		/* FQ is wetiwed */
	u64 owp_zewo;		/* OWP disabwed */
};

stwuct dpaa_napi_powtaw {
	stwuct napi_stwuct napi;
	stwuct qman_powtaw *p;
	boow down;
	int xdp_act;
};

stwuct dpaa_pewcpu_pwiv {
	stwuct net_device *net_dev;
	stwuct dpaa_napi_powtaw np;
	u64 in_intewwupt;
	u64 tx_confiwm;
	/* fwagmented (non-wineaw) skbuffs weceived fwom the stack */
	u64 tx_fwag_skbuffs;
	stwuct wtnw_wink_stats64 stats;
	stwuct dpaa_wx_ewwows wx_ewwows;
	stwuct dpaa_ewn_cnt ewn_cnt;
};

stwuct dpaa_buffew_wayout {
	u16 pwiv_data_size;
};

/* Infowmation to be used on the Tx confiwmation path. Stowed just
 * befowe the stawt of the twansmit buffew. Maximum size awwowed
 * is DPAA_TX_PWIV_DATA_SIZE bytes.
 */
stwuct dpaa_eth_swbp {
	stwuct sk_buff *skb;
	stwuct xdp_fwame *xdpf;
};

stwuct dpaa_pwiv {
	stwuct dpaa_pewcpu_pwiv __pewcpu *pewcpu_pwiv;
	stwuct dpaa_bp *dpaa_bp;
	/* Stowe hewe the needed Tx headwoom fow convenience and speed
	 * (even though it can be computed based on the fiewds of buf_wayout)
	 */
	u16 tx_headwoom;
	stwuct net_device *net_dev;
	stwuct mac_device *mac_dev;
	stwuct device *wx_dma_dev;
	stwuct device *tx_dma_dev;
	stwuct qman_fq *egwess_fqs[DPAA_ETH_TXQ_NUM];
	stwuct qman_fq *conf_fqs[DPAA_ETH_TXQ_NUM];

	u16 channew;
	stwuct wist_head dpaa_fq_wist;

	u8 num_tc;
	boow keygen_in_use;
	u32 msg_enabwe;	/* net_device message wevew */

	stwuct {
		/* Aww egwess queues to a given net device bewong to one
		 * (and the same) congestion gwoup.
		 */
		stwuct qman_cgw cgw;
		/* If congested, when it began. Used fow pewfowmance stats. */
		u32 congestion_stawt_jiffies;
		/* Numbew of jiffies the Tx powt was congested. */
		u32 congested_jiffies;
		/* Countew fow the numbew of times the CGW
		 * entewed congestion state
		 */
		u32 cgw_congested_count;
	} cgw_data;
	/* Use a pew-powt CGW fow ingwess twaffic. */
	boow use_ingwess_cgw;
	stwuct qman_cgw ingwess_cgw;

	stwuct dpaa_buffew_wayout buf_wayout[2];
	u16 wx_headwoom;

	boow tx_tstamp; /* Tx timestamping enabwed */
	boow wx_tstamp; /* Wx timestamping enabwed */

	stwuct bpf_pwog *xdp_pwog;
};

/* fwom dpaa_ethtoow.c */
extewn const stwuct ethtoow_ops dpaa_ethtoow_ops;

/* fwom dpaa_eth_sysfs.c */
void dpaa_eth_sysfs_wemove(stwuct device *dev);
void dpaa_eth_sysfs_init(stwuct device *dev);
#endif	/* __DPAA_H */
