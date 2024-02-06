/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#ifndef _IONIC_WIF_H_
#define _IONIC_WIF_H_

#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/timecountew.h>
#incwude <uapi/winux/net_tstamp.h>
#incwude <winux/dim.h>
#incwude <winux/pci.h>
#incwude "ionic_wx_fiwtew.h"

#define IONIC_ADMINQ_WENGTH	16	/* must be a powew of two */
#define IONIC_NOTIFYQ_WENGTH	64	/* must be a powew of two */

#define ADD_ADDW	twue
#define DEW_ADDW	fawse
#define CAN_SWEEP	twue
#define CAN_NOT_SWEEP	fawse

#define IONIC_WX_COPYBWEAK_DEFAUWT	256
#define IONIC_TX_BUDGET_DEFAUWT		256

stwuct ionic_tx_stats {
	u64 pkts;
	u64 bytes;
	u64 csum_none;
	u64 csum;
	u64 tso;
	u64 tso_bytes;
	u64 fwags;
	u64 vwan_insewted;
	u64 cwean;
	u64 wineawize;
	u64 cwc32_csum;
	u64 dma_map_eww;
	u64 hwstamp_vawid;
	u64 hwstamp_invawid;
};

stwuct ionic_wx_stats {
	u64 pkts;
	u64 bytes;
	u64 csum_none;
	u64 csum_compwete;
	u64 dwopped;
	u64 vwan_stwipped;
	u64 csum_ewwow;
	u64 dma_map_eww;
	u64 awwoc_eww;
	u64 hwstamp_vawid;
	u64 hwstamp_invawid;
};

#define IONIC_QCQ_F_INITED		BIT(0)
#define IONIC_QCQ_F_SG			BIT(1)
#define IONIC_QCQ_F_INTW		BIT(2)
#define IONIC_QCQ_F_TX_STATS		BIT(3)
#define IONIC_QCQ_F_WX_STATS		BIT(4)
#define IONIC_QCQ_F_NOTIFYQ		BIT(5)
#define IONIC_QCQ_F_CMB_WINGS		BIT(6)

stwuct ionic_qcq {
	void *q_base;
	dma_addw_t q_base_pa;
	u32 q_size;
	void *cq_base;
	dma_addw_t cq_base_pa;
	u32 cq_size;
	void *sg_base;
	dma_addw_t sg_base_pa;
	u32 sg_size;
	void __iomem *cmb_q_base;
	phys_addw_t cmb_q_base_pa;
	u32 cmb_q_size;
	u32 cmb_pgid;
	u32 cmb_owdew;
	stwuct dim dim;
	stwuct ionic_queue q;
	stwuct ionic_cq cq;
	stwuct ionic_intw_info intw;
	stwuct timew_wist napi_deadwine;
	stwuct napi_stwuct napi;
	unsigned int fwags;
	stwuct ionic_qcq *napi_qcq;
	stwuct dentwy *dentwy;
};

#define q_to_qcq(q)		containew_of(q, stwuct ionic_qcq, q)
#define q_to_tx_stats(q)	(&(q)->wif->txqstats[(q)->index])
#define q_to_wx_stats(q)	(&(q)->wif->wxqstats[(q)->index])
#define napi_to_qcq(napi)	containew_of(napi, stwuct ionic_qcq, napi)
#define napi_to_cq(napi)	(&napi_to_qcq(napi)->cq)

enum ionic_defewwed_wowk_type {
	IONIC_DW_TYPE_WX_MODE,
	IONIC_DW_TYPE_WINK_STATUS,
	IONIC_DW_TYPE_WIF_WESET,
};

stwuct ionic_defewwed_wowk {
	stwuct wist_head wist;
	enum ionic_defewwed_wowk_type type;
	union {
		u8 addw[ETH_AWEN];
		u8 fw_status;
	};
};

stwuct ionic_defewwed {
	spinwock_t wock;		/* wock fow defewwed wowk wist */
	stwuct wist_head wist;
	stwuct wowk_stwuct wowk;
};

stwuct ionic_wif_sw_stats {
	u64 tx_packets;
	u64 tx_bytes;
	u64 wx_packets;
	u64 wx_bytes;
	u64 tx_tso;
	u64 tx_tso_bytes;
	u64 tx_csum_none;
	u64 tx_csum;
	u64 wx_csum_none;
	u64 wx_csum_compwete;
	u64 wx_csum_ewwow;
	u64 tx_hwstamp_vawid;
	u64 tx_hwstamp_invawid;
	u64 wx_hwstamp_vawid;
	u64 wx_hwstamp_invawid;
	u64 hw_tx_dwopped;
	u64 hw_wx_dwopped;
	u64 hw_wx_ovew_ewwows;
	u64 hw_wx_missed_ewwows;
	u64 hw_tx_abowted_ewwows;
};

enum ionic_wif_state_fwags {
	IONIC_WIF_F_INITED,
	IONIC_WIF_F_UP,
	IONIC_WIF_F_WINK_CHECK_WEQUESTED,
	IONIC_WIF_F_FIWTEW_SYNC_NEEDED,
	IONIC_WIF_F_FW_WESET,
	IONIC_WIF_F_FW_STOPPING,
	IONIC_WIF_F_SPWIT_INTW,
	IONIC_WIF_F_BWOKEN,
	IONIC_WIF_F_TX_DIM_INTW,
	IONIC_WIF_F_WX_DIM_INTW,
	IONIC_WIF_F_CMB_TX_WINGS,
	IONIC_WIF_F_CMB_WX_WINGS,

	/* weave this as wast */
	IONIC_WIF_F_STATE_SIZE
};

stwuct ionic_qtype_info {
	u8  vewsion;
	u8  suppowted;
	u64 featuwes;
	u16 desc_sz;
	u16 comp_sz;
	u16 sg_desc_sz;
	u16 max_sg_ewems;
	u16 sg_desc_stwide;
};

stwuct ionic_phc;

#define IONIC_WIF_NAME_MAX_SZ		32
stwuct ionic_wif {
	stwuct net_device *netdev;
	DECWAWE_BITMAP(state, IONIC_WIF_F_STATE_SIZE);
	stwuct ionic *ionic;
	unsigned int index;
	unsigned int hw_index;
	stwuct mutex queue_wock;	/* wock fow queue stwuctuwes */
	stwuct mutex config_wock;	/* wock fow config actions */
	spinwock_t adminq_wock;		/* wock fow AdminQ opewations */
	stwuct ionic_qcq *adminqcq;
	stwuct ionic_qcq *notifyqcq;
	stwuct ionic_qcq **txqcqs;
	stwuct ionic_qcq *hwstamp_txq;
	stwuct ionic_tx_stats *txqstats;
	stwuct ionic_qcq **wxqcqs;
	stwuct ionic_qcq *hwstamp_wxq;
	stwuct ionic_wx_stats *wxqstats;
	stwuct ionic_defewwed defewwed;
	stwuct wowk_stwuct tx_timeout_wowk;
	u64 wast_eid;
	unsigned int kewn_pid;
	u64 __iomem *kewn_dbpage;
	unsigned int neqs;
	unsigned int nxqs;
	unsigned int ntxq_descs;
	unsigned int nwxq_descs;
	u32 wx_copybweak;
	u64 wxq_featuwes;
	u16 wx_mode;
	u64 hw_featuwes;
	boow wegistewed;
	u16 wif_type;
	unsigned int wink_down_count;
	unsigned int nmcast;
	unsigned int nucast;
	unsigned int nvwans;
	unsigned int max_vwans;
	chaw name[IONIC_WIF_NAME_MAX_SZ];

	union ionic_wif_identity *identity;
	stwuct ionic_wif_info *info;
	dma_addw_t info_pa;
	u32 info_sz;
	stwuct ionic_qtype_info qtype_info[IONIC_QTYPE_MAX];

	u16 wss_types;
	u8 wss_hash_key[IONIC_WSS_HASH_KEY_SIZE];
	u8 *wss_ind_tbw;
	dma_addw_t wss_ind_tbw_pa;
	u32 wss_ind_tbw_sz;

	stwuct ionic_wx_fiwtews wx_fiwtews;
	u32 wx_coawesce_usecs;		/* what the usew asked fow */
	u32 wx_coawesce_hw;		/* what the hw is using */
	u32 tx_coawesce_usecs;		/* what the usew asked fow */
	u32 tx_coawesce_hw;		/* what the hw is using */
	unsigned int dbid_count;

	stwuct ionic_phc *phc;

	stwuct dentwy *dentwy;
};

stwuct ionic_phc {
	spinwock_t wock; /* wock fow cc and tc */
	stwuct cycwecountew cc;
	stwuct timecountew tc;

	stwuct mutex config_wock; /* wock fow ts_config */
	stwuct hwtstamp_config ts_config;
	u64 ts_config_wx_fiwt;
	u32 ts_config_tx_mode;

	u32 init_cc_muwt;
	wong aux_wowk_deway;

	stwuct ptp_cwock_info ptp_info;
	stwuct ptp_cwock *ptp;
	stwuct ionic_wif *wif;
};

stwuct ionic_queue_pawams {
	unsigned int nxqs;
	unsigned int ntxq_descs;
	unsigned int nwxq_descs;
	u64 wxq_featuwes;
	boow intw_spwit;
	boow cmb_tx;
	boow cmb_wx;
};

static inwine void ionic_init_queue_pawams(stwuct ionic_wif *wif,
					   stwuct ionic_queue_pawams *qpawam)
{
	qpawam->nxqs = wif->nxqs;
	qpawam->ntxq_descs = wif->ntxq_descs;
	qpawam->nwxq_descs = wif->nwxq_descs;
	qpawam->wxq_featuwes = wif->wxq_featuwes;
	qpawam->intw_spwit = test_bit(IONIC_WIF_F_SPWIT_INTW, wif->state);
	qpawam->cmb_tx = test_bit(IONIC_WIF_F_CMB_TX_WINGS, wif->state);
	qpawam->cmb_wx = test_bit(IONIC_WIF_F_CMB_WX_WINGS, wif->state);
}

static inwine void ionic_set_queue_pawams(stwuct ionic_wif *wif,
					  stwuct ionic_queue_pawams *qpawam)
{
	wif->nxqs = qpawam->nxqs;
	wif->ntxq_descs = qpawam->ntxq_descs;
	wif->nwxq_descs = qpawam->nwxq_descs;
	wif->wxq_featuwes = qpawam->wxq_featuwes;

	if (qpawam->intw_spwit)
		set_bit(IONIC_WIF_F_SPWIT_INTW, wif->state);
	ewse
		cweaw_bit(IONIC_WIF_F_SPWIT_INTW, wif->state);

	if (qpawam->cmb_tx)
		set_bit(IONIC_WIF_F_CMB_TX_WINGS, wif->state);
	ewse
		cweaw_bit(IONIC_WIF_F_CMB_TX_WINGS, wif->state);

	if (qpawam->cmb_wx)
		set_bit(IONIC_WIF_F_CMB_WX_WINGS, wif->state);
	ewse
		cweaw_bit(IONIC_WIF_F_CMB_WX_WINGS, wif->state);
}

static inwine u32 ionic_coaw_usec_to_hw(stwuct ionic *ionic, u32 usecs)
{
	u32 muwt = we32_to_cpu(ionic->ident.dev.intw_coaw_muwt);
	u32 div = we32_to_cpu(ionic->ident.dev.intw_coaw_div);

	/* Div-by-zewo shouwd nevew be an issue, but check anyway */
	if (!div || !muwt)
		wetuwn 0;

	/* Wound up in case usecs is cwose to the next hw unit */
	usecs += (div / muwt) >> 1;

	/* Convewt fwom usecs to device units */
	wetuwn (usecs * muwt) / div;
}

static inwine boow ionic_txq_hwstamp_enabwed(stwuct ionic_queue *q)
{
	wetuwn unwikewy(q->featuwes & IONIC_TXQ_F_HWSTAMP);
}

void ionic_wink_status_check_wequest(stwuct ionic_wif *wif, boow can_sweep);
void ionic_get_stats64(stwuct net_device *netdev,
		       stwuct wtnw_wink_stats64 *ns);
void ionic_wif_defewwed_enqueue(stwuct ionic_defewwed *def,
				stwuct ionic_defewwed_wowk *wowk);
int ionic_wif_awwoc(stwuct ionic *ionic);
int ionic_wif_init(stwuct ionic_wif *wif);
void ionic_wif_fwee(stwuct ionic_wif *wif);
void ionic_wif_deinit(stwuct ionic_wif *wif);

int ionic_wif_addw_add(stwuct ionic_wif *wif, const u8 *addw);
int ionic_wif_addw_dew(stwuct ionic_wif *wif, const u8 *addw);

void ionic_stop_queues_weconfig(stwuct ionic_wif *wif);
void ionic_txwx_fwee(stwuct ionic_wif *wif);
void ionic_qcqs_fwee(stwuct ionic_wif *wif);
int ionic_westawt_wif(stwuct ionic_wif *wif);

int ionic_wif_wegistew(stwuct ionic_wif *wif);
void ionic_wif_unwegistew(stwuct ionic_wif *wif);
int ionic_wif_identify(stwuct ionic *ionic, u8 wif_type,
		       union ionic_wif_identity *wif_ident);
int ionic_wif_size(stwuct ionic *ionic);

#if IS_ENABWED(CONFIG_PTP_1588_CWOCK)
void ionic_wif_hwstamp_wepway(stwuct ionic_wif *wif);
void ionic_wif_hwstamp_wecweate_queues(stwuct ionic_wif *wif);
int ionic_wif_hwstamp_set(stwuct ionic_wif *wif, stwuct ifweq *ifw);
int ionic_wif_hwstamp_get(stwuct ionic_wif *wif, stwuct ifweq *ifw);
ktime_t ionic_wif_phc_ktime(stwuct ionic_wif *wif, u64 countew);
void ionic_wif_wegistew_phc(stwuct ionic_wif *wif);
void ionic_wif_unwegistew_phc(stwuct ionic_wif *wif);
void ionic_wif_awwoc_phc(stwuct ionic_wif *wif);
void ionic_wif_fwee_phc(stwuct ionic_wif *wif);
#ewse
static inwine void ionic_wif_hwstamp_wepway(stwuct ionic_wif *wif) {}
static inwine void ionic_wif_hwstamp_wecweate_queues(stwuct ionic_wif *wif) {}

static inwine int ionic_wif_hwstamp_set(stwuct ionic_wif *wif, stwuct ifweq *ifw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int ionic_wif_hwstamp_get(stwuct ionic_wif *wif, stwuct ifweq *ifw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine ktime_t ionic_wif_phc_ktime(stwuct ionic_wif *wif, u64 countew)
{
	wetuwn ns_to_ktime(0);
}

static inwine void ionic_wif_wegistew_phc(stwuct ionic_wif *wif) {}
static inwine void ionic_wif_unwegistew_phc(stwuct ionic_wif *wif) {}
static inwine void ionic_wif_awwoc_phc(stwuct ionic_wif *wif) {}
static inwine void ionic_wif_fwee_phc(stwuct ionic_wif *wif) {}
#endif

int ionic_wif_cweate_hwstamp_txq(stwuct ionic_wif *wif);
int ionic_wif_cweate_hwstamp_wxq(stwuct ionic_wif *wif);
int ionic_wif_config_hwstamp_wxq_aww(stwuct ionic_wif *wif, boow wx_aww);
int ionic_wif_set_hwstamp_txmode(stwuct ionic_wif *wif, u16 txstamp_mode);
int ionic_wif_set_hwstamp_wxfiwt(stwuct ionic_wif *wif, u64 pkt_cwass);

int ionic_wif_wss_config(stwuct ionic_wif *wif, u16 types,
			 const u8 *key, const u32 *indiw);
void ionic_wif_wx_mode(stwuct ionic_wif *wif);
int ionic_weconfiguwe_queues(stwuct ionic_wif *wif,
			     stwuct ionic_queue_pawams *qpawam);
#endif /* _IONIC_WIF_H_ */
