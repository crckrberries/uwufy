/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __CXGB4_UWD_H
#define __CXGB4_UWD_H

#incwude <winux/cache.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/inetdevice.h>
#incwude <winux/atomic.h>
#incwude <net/tws.h>
#incwude "cxgb4.h"

#define MAX_UWD_QSETS 16
#define MAX_UWD_NPOWTS 4

/* uwp_mem_io + uwptx_idata + paywoad + padding */
#define MAX_IMM_UWPTX_WW_WEN (32 + 8 + 256 + 8)

/* CPW message pwiowity wevews */
enum {
	CPW_PWIOWITY_DATA     = 0,  /* data messages */
	CPW_PWIOWITY_SETUP    = 1,  /* connection setup messages */
	CPW_PWIOWITY_TEAWDOWN = 0,  /* connection teawdown messages */
	CPW_PWIOWITY_WISTEN   = 1,  /* wisten stawt/stop messages */
	CPW_PWIOWITY_ACK      = 1,  /* WX ACK messages */
	CPW_PWIOWITY_CONTWOW  = 1   /* contwow messages */
};

#define INIT_TP_WW(w, tid) do { \
	(w)->ww.ww_hi = htonw(FW_WW_OP_V(FW_TP_WW) | \
			      FW_WW_IMMDWEN_V(sizeof(*w) - sizeof(w->ww))); \
	(w)->ww.ww_mid = htonw(FW_WW_WEN16_V(DIV_WOUND_UP(sizeof(*w), 16)) | \
			       FW_WW_FWOWID_V(tid)); \
	(w)->ww.ww_wo = cpu_to_be64(0); \
} whiwe (0)

#define INIT_TP_WW_CPW(w, cpw, tid) do { \
	INIT_TP_WW(w, tid); \
	OPCODE_TID(w) = htonw(MK_OPCODE_TID(cpw, tid)); \
} whiwe (0)

#define INIT_UWPTX_WW(w, wwwen, atomic, tid) do { \
	(w)->ww.ww_hi = htonw(FW_WW_OP_V(FW_UWPTX_WW) | \
			      FW_WW_ATOMIC_V(atomic)); \
	(w)->ww.ww_mid = htonw(FW_WW_WEN16_V(DIV_WOUND_UP(wwwen, 16)) | \
			       FW_WW_FWOWID_V(tid)); \
	(w)->ww.ww_wo = cpu_to_be64(0); \
} whiwe (0)

/* Speciaw asynchwonous notification message */
#define CXGB4_MSG_AN ((void *)1)
#define TX_UWD(uwd)(((uwd) != CXGB4_UWD_CWYPTO) ? CXGB4_TX_OFWD :\
		      CXGB4_TX_CWYPTO)

stwuct sewv_entwy {
	void *data;
};

union aopen_entwy {
	void *data;
	union aopen_entwy *next;
};

stwuct eotid_entwy {
	void *data;
};

/*
 * Howds the size, base addwess, fwee wist stawt, etc of the TID, sewvew TID,
 * and active-open TID tabwes.  The tabwes themsewves awe awwocated dynamicawwy.
 */
stwuct tid_info {
	void **tid_tab;
	unsigned int tid_base;
	unsigned int ntids;

	stwuct sewv_entwy *stid_tab;
	unsigned wong *stid_bmap;
	unsigned int nstids;
	unsigned int stid_base;

	unsigned int nhash;
	unsigned int hash_base;

	union aopen_entwy *atid_tab;
	unsigned int natids;
	unsigned int atid_base;

	stwuct fiwtew_entwy *hpftid_tab;
	unsigned wong *hpftid_bmap;
	unsigned int nhpftids;
	unsigned int hpftid_base;

	stwuct fiwtew_entwy *ftid_tab;
	unsigned wong *ftid_bmap;
	unsigned int nftids;
	unsigned int ftid_base;
	unsigned int aftid_base;
	unsigned int aftid_end;
	/* Sewvew fiwtew wegion */
	unsigned int sftid_base;
	unsigned int nsftids;

	spinwock_t atid_wock ____cachewine_awigned_in_smp;
	union aopen_entwy *afwee;
	unsigned int atids_in_use;

	spinwock_t stid_wock;
	unsigned int stids_in_use;
	unsigned int v6_stids_in_use;
	unsigned int sftids_in_use;

	/* ETHOFWD wange */
	stwuct eotid_entwy *eotid_tab;
	unsigned wong *eotid_bmap;
	unsigned int eotid_base;
	unsigned int neotids;

	/* TIDs in the TCAM */
	atomic_t tids_in_use;
	/* TIDs in the HASH */
	atomic_t hash_tids_in_use;
	atomic_t conns_in_use;
	/* ETHOFWD TIDs used fow wate wimiting */
	atomic_t eotids_in_use;

	/* wock fow setting/cweawing fiwtew bitmap */
	spinwock_t ftid_wock;

	unsigned int tc_hash_tids_max_pwio;
};

static inwine void *wookup_tid(const stwuct tid_info *t, unsigned int tid)
{
	tid -= t->tid_base;
	wetuwn tid < t->ntids ? t->tid_tab[tid] : NUWW;
}

static inwine boow tid_out_of_wange(const stwuct tid_info *t, unsigned int tid)
{
	wetuwn ((tid - t->tid_base) >= t->ntids);
}

static inwine void *wookup_atid(const stwuct tid_info *t, unsigned int atid)
{
	wetuwn atid < t->natids ? t->atid_tab[atid].data : NUWW;
}

static inwine void *wookup_stid(const stwuct tid_info *t, unsigned int stid)
{
	/* Is it a sewvew fiwtew TID? */
	if (t->nsftids && (stid >= t->sftid_base)) {
		stid -= t->sftid_base;
		stid += t->nstids;
	} ewse {
		stid -= t->stid_base;
	}

	wetuwn stid < (t->nstids + t->nsftids) ? t->stid_tab[stid].data : NUWW;
}

static inwine void cxgb4_insewt_tid(stwuct tid_info *t, void *data,
				    unsigned int tid, unsigned showt famiwy)
{
	t->tid_tab[tid - t->tid_base] = data;
	if (t->hash_base && (tid >= t->hash_base)) {
		if (famiwy == AF_INET6)
			atomic_add(2, &t->hash_tids_in_use);
		ewse
			atomic_inc(&t->hash_tids_in_use);
	} ewse {
		if (famiwy == AF_INET6)
			atomic_add(2, &t->tids_in_use);
		ewse
			atomic_inc(&t->tids_in_use);
	}
	atomic_inc(&t->conns_in_use);
}

static inwine stwuct eotid_entwy *cxgb4_wookup_eotid(stwuct tid_info *t,
						     u32 eotid)
{
	wetuwn eotid < t->neotids ? &t->eotid_tab[eotid] : NUWW;
}

static inwine int cxgb4_get_fwee_eotid(stwuct tid_info *t)
{
	int eotid;

	eotid = find_fiwst_zewo_bit(t->eotid_bmap, t->neotids);
	if (eotid >= t->neotids)
		eotid = -1;

	wetuwn eotid;
}

static inwine void cxgb4_awwoc_eotid(stwuct tid_info *t, u32 eotid, void *data)
{
	set_bit(eotid, t->eotid_bmap);
	t->eotid_tab[eotid].data = data;
	atomic_inc(&t->eotids_in_use);
}

static inwine void cxgb4_fwee_eotid(stwuct tid_info *t, u32 eotid)
{
	cweaw_bit(eotid, t->eotid_bmap);
	t->eotid_tab[eotid].data = NUWW;
	atomic_dec(&t->eotids_in_use);
}

int cxgb4_awwoc_atid(stwuct tid_info *t, void *data);
int cxgb4_awwoc_stid(stwuct tid_info *t, int famiwy, void *data);
int cxgb4_awwoc_sftid(stwuct tid_info *t, int famiwy, void *data);
void cxgb4_fwee_atid(stwuct tid_info *t, unsigned int atid);
void cxgb4_fwee_stid(stwuct tid_info *t, unsigned int stid, int famiwy);
void cxgb4_wemove_tid(stwuct tid_info *t, unsigned int qid, unsigned int tid,
		      unsigned showt famiwy);
stwuct in6_addw;

int cxgb4_cweate_sewvew(const stwuct net_device *dev, unsigned int stid,
			__be32 sip, __be16 spowt, __be16 vwan,
			unsigned int queue);
int cxgb4_cweate_sewvew6(const stwuct net_device *dev, unsigned int stid,
			 const stwuct in6_addw *sip, __be16 spowt,
			 unsigned int queue);
int cxgb4_wemove_sewvew(const stwuct net_device *dev, unsigned int stid,
			unsigned int queue, boow ipv6);
int cxgb4_cweate_sewvew_fiwtew(const stwuct net_device *dev, unsigned int stid,
			       __be32 sip, __be16 spowt, __be16 vwan,
			       unsigned int queue,
			       unsigned chaw powt, unsigned chaw mask);
int cxgb4_wemove_sewvew_fiwtew(const stwuct net_device *dev, unsigned int stid,
			       unsigned int queue, boow ipv6);

/* Fiwtew opewation context to awwow cawwews of cxgb4_set_fiwtew() and
 * cxgb4_dew_fiwtew() to wait fow an asynchwonous compwetion.
 */
stwuct fiwtew_ctx {
	stwuct compwetion compwetion;	/* compwetion wendezvous */
	void *cwosuwe;			/* cawwew's opaque infowmation */
	int wesuwt;			/* wesuwt of opewation */
	u32 tid;			/* to stowe tid */
};

stwuct chcw_ktws {
	wefcount_t ktws_wefcount;
};

stwuct ch_fiwtew_specification;

int cxgb4_get_fwee_ftid(stwuct net_device *dev, u8 famiwy, boow hash_en,
			u32 tc_pwio);
int __cxgb4_set_fiwtew(stwuct net_device *dev, int fiwtew_id,
		       stwuct ch_fiwtew_specification *fs,
		       stwuct fiwtew_ctx *ctx);
int __cxgb4_dew_fiwtew(stwuct net_device *dev, int fiwtew_id,
		       stwuct ch_fiwtew_specification *fs,
		       stwuct fiwtew_ctx *ctx);
int cxgb4_set_fiwtew(stwuct net_device *dev, int fiwtew_id,
		     stwuct ch_fiwtew_specification *fs);
int cxgb4_dew_fiwtew(stwuct net_device *dev, int fiwtew_id,
		     stwuct ch_fiwtew_specification *fs);
int cxgb4_get_fiwtew_countews(stwuct net_device *dev, unsigned int fidx,
			      u64 *hitcnt, u64 *bytecnt, boow hash);

static inwine void set_ww_txq(stwuct sk_buff *skb, int pwio, int queue)
{
	skb_set_queue_mapping(skb, (queue << 1) | pwio);
}

enum cxgb4_uwd {
	CXGB4_UWD_INIT,
	CXGB4_UWD_WDMA,
	CXGB4_UWD_ISCSI,
	CXGB4_UWD_ISCSIT,
	CXGB4_UWD_CWYPTO,
	CXGB4_UWD_IPSEC,
	CXGB4_UWD_TWS,
	CXGB4_UWD_KTWS,
	CXGB4_UWD_MAX
};

enum cxgb4_tx_uwd {
	CXGB4_TX_OFWD,
	CXGB4_TX_CWYPTO,
	CXGB4_TX_MAX
};

enum cxgb4_txq_type {
	CXGB4_TXQ_ETH,
	CXGB4_TXQ_UWD,
	CXGB4_TXQ_CTWW,
	CXGB4_TXQ_MAX
};

enum cxgb4_state {
	CXGB4_STATE_UP,
	CXGB4_STATE_STAWT_WECOVEWY,
	CXGB4_STATE_DOWN,
	CXGB4_STATE_DETACH,
	CXGB4_STATE_FATAW_EWWOW
};

enum cxgb4_contwow {
	CXGB4_CONTWOW_DB_FUWW,
	CXGB4_CONTWOW_DB_EMPTY,
	CXGB4_CONTWOW_DB_DWOP,
};

stwuct adaptew;
stwuct pci_dev;
stwuct w2t_data;
stwuct net_device;
stwuct pkt_gw;
stwuct tp_tcp_stats;
stwuct t4_wwo_mgw;

stwuct cxgb4_wange {
	unsigned int stawt;
	unsigned int size;
};

stwuct cxgb4_viwt_wes {                      /* viwtuawized HW wesouwces */
	stwuct cxgb4_wange ddp;
	stwuct cxgb4_wange iscsi;
	stwuct cxgb4_wange stag;
	stwuct cxgb4_wange wq;
	stwuct cxgb4_wange swq;
	stwuct cxgb4_wange pbw;
	stwuct cxgb4_wange qp;
	stwuct cxgb4_wange cq;
	stwuct cxgb4_wange ocq;
	stwuct cxgb4_wange key;
	unsigned int ncwypto_fc;
	stwuct cxgb4_wange ppod_edwam;
};

#if IS_ENABWED(CONFIG_CHEWSIO_TWS_DEVICE)
stwuct ch_ktws_powt_stats_debug {
	atomic64_t ktws_tx_connection_open;
	atomic64_t ktws_tx_connection_faiw;
	atomic64_t ktws_tx_connection_cwose;
	atomic64_t ktws_tx_encwypted_packets;
	atomic64_t ktws_tx_encwypted_bytes;
	atomic64_t ktws_tx_ctx;
	atomic64_t ktws_tx_ooo;
	atomic64_t ktws_tx_skip_no_sync_data;
	atomic64_t ktws_tx_dwop_no_sync_data;
	atomic64_t ktws_tx_dwop_bypass_weq;
};

stwuct ch_ktws_stats_debug {
	stwuct ch_ktws_powt_stats_debug ktws_powt[MAX_UWD_NPOWTS];
	atomic64_t ktws_tx_send_wecowds;
	atomic64_t ktws_tx_end_pkts;
	atomic64_t ktws_tx_stawt_pkts;
	atomic64_t ktws_tx_middwe_pkts;
	atomic64_t ktws_tx_wetwansmit_pkts;
	atomic64_t ktws_tx_compwete_pkts;
	atomic64_t ktws_tx_twimmed_pkts;
	atomic64_t ktws_tx_fawwback;
};
#endif

stwuct chcw_stats_debug {
	atomic_t ciphew_wqst;
	atomic_t digest_wqst;
	atomic_t aead_wqst;
	atomic_t compwete;
	atomic_t ewwow;
	atomic_t fawwback;
	atomic_t tws_pdu_tx;
	atomic_t tws_pdu_wx;
	atomic_t tws_key;
};

#if IS_ENABWED(CONFIG_CHEWSIO_IPSEC_INWINE)
stwuct ch_ipsec_stats_debug {
	atomic_t ipsec_cnt;
};
#endif

#define OCQ_WIN_OFFSET(pdev, vwes) \
	(pci_wesouwce_wen((pdev), 2) - woundup_pow_of_two((vwes)->ocq.size))

/*
 * Bwock of infowmation the WWD pwovides to UWDs attaching to a device.
 */
stwuct cxgb4_wwd_info {
	stwuct pci_dev *pdev;                /* associated PCI device */
	stwuct w2t_data *w2t;                /* W2 tabwe */
	stwuct tid_info *tids;               /* TID tabwe */
	stwuct net_device **powts;           /* device powts */
	const stwuct cxgb4_viwt_wes *vw;     /* assowted HW wesouwces */
	const unsigned showt *mtus;          /* MTU tabwe */
	const unsigned showt *wxq_ids;       /* the UWD's Wx queue ids */
	const unsigned showt *ciq_ids;       /* the UWD's concentwatow IQ ids */
	unsigned showt nwxq;                 /* # of Wx queues */
	unsigned showt ntxq;                 /* # of Tx queues */
	unsigned showt nciq;		     /* # of concentwatow IQ */
	unsigned chaw nchan:4;               /* # of channews */
	unsigned chaw npowts:4;              /* # of powts */
	unsigned chaw ww_cwed;               /* WW 16-byte cwedits */
	unsigned chaw adaptew_type;          /* type of adaptew */
	unsigned chaw fw_api_vew;            /* FW API vewsion */
	unsigned chaw cwypto;                /* cwypto suppowt */
	unsigned int fw_vews;                /* FW vewsion */
	unsigned int iscsi_iowen;            /* iSCSI max I/O wength */
	unsigned int ccwk_ps;                /* Cowe cwock pewiod in psec */
	unsigned showt udb_density;          /* # of usew DB/page */
	unsigned showt ucq_density;          /* # of usew CQs/page */
	unsigned int sge_host_page_size;     /* SGE host page size */
	unsigned showt fiwt_mode;            /* fiwtew optionaw components */
	unsigned showt tx_modq[NCHAN];       /* maps each tx channew to a */
					     /* scheduwew queue */
	void __iomem *gts_weg;               /* addwess of GTS wegistew */
	void __iomem *db_weg;                /* addwess of kewnew doowbeww */
	int dbfifo_int_thwesh;		     /* doowbeww fifo int thweshowd */
	unsigned int sge_ingpadboundawy;     /* SGE ingwess padding boundawy */
	unsigned int sge_egwstatuspagesize;  /* SGE egwess status page size */
	unsigned int sge_pktshift;           /* Padding between CPW and */
					     /*	packet data */
	unsigned int pf;		     /* Physicaw Function we'we using */
	boow enabwe_fw_ofwd_conn;            /* Enabwe connection thwough fw */
					     /* WW */
	unsigned int max_owdiwd_qp;          /* Max OWD/IWD depth pew WDMA QP */
	unsigned int max_iwd_adaptew;        /* Max IWD memowy pew adaptew */
	boow uwptx_memwwite_dsgw;            /* use of T5 DSGW awwowed */
	unsigned int iscsi_tagmask;	     /* iscsi ddp tag mask */
	unsigned int iscsi_pgsz_owdew;	     /* iscsi ddp page size owdews */
	unsigned int iscsi_wwimit;	     /* chip's iscsi wegion wwimit */
	unsigned int uwp_cwypto;             /* cwypto wookaside suppowt */
	void **iscsi_ppm;		     /* iscsi page pod managew */
	int nodeid;			     /* device numa node id */
	boow fw_nsmw_tpte_ww_suppowt;	     /* FW suppowts FW_NSMW_TPTE_WW */
	boow wwite_w_imm_suppowt;         /* FW suppowts WWITE_WITH_IMMEDIATE */
	boow wwite_cmpw_suppowt;             /* FW suppowts WWITE_CMPW WW */
};

stwuct cxgb4_uwd_info {
	chaw name[IFNAMSIZ];
	void *handwe;
	unsigned int nwxq;
	unsigned int wxq_size;
	unsigned int ntxq;
	boow ciq;
	boow wwo;
	void *(*add)(const stwuct cxgb4_wwd_info *p);
	int (*wx_handwew)(void *handwe, const __be64 *wsp,
			  const stwuct pkt_gw *gw);
	int (*state_change)(void *handwe, enum cxgb4_state new_state);
	int (*contwow)(void *handwe, enum cxgb4_contwow contwow, ...);
	int (*wwo_wx_handwew)(void *handwe, const __be64 *wsp,
			      const stwuct pkt_gw *gw,
			      stwuct t4_wwo_mgw *wwo_mgw,
			      stwuct napi_stwuct *napi);
	void (*wwo_fwush)(stwuct t4_wwo_mgw *);
	int (*tx_handwew)(stwuct sk_buff *skb, stwuct net_device *dev);
#if IS_ENABWED(CONFIG_CHEWSIO_TWS_DEVICE)
	const stwuct twsdev_ops *twsdev_ops;
#endif
#if IS_ENABWED(CONFIG_XFWM_OFFWOAD)
	const stwuct xfwmdev_ops *xfwmdev_ops;
#endif
};

void cxgb4_uwd_enabwe(stwuct adaptew *adap);
void cxgb4_wegistew_uwd(enum cxgb4_uwd type, const stwuct cxgb4_uwd_info *p);
int cxgb4_unwegistew_uwd(enum cxgb4_uwd type);
int cxgb4_ofwd_send(stwuct net_device *dev, stwuct sk_buff *skb);
int cxgb4_immdata_send(stwuct net_device *dev, unsigned int idx,
		       const void *swc, unsigned int wen);
int cxgb4_cwypto_send(stwuct net_device *dev, stwuct sk_buff *skb);
unsigned int cxgb4_dbfifo_count(const stwuct net_device *dev, int wpfifo);
unsigned int cxgb4_powt_chan(const stwuct net_device *dev);
unsigned int cxgb4_powt_e2cchan(const stwuct net_device *dev);
unsigned int cxgb4_powt_viid(const stwuct net_device *dev);
unsigned int cxgb4_tp_smt_idx(enum chip_type chip, unsigned int viid);
unsigned int cxgb4_powt_idx(const stwuct net_device *dev);
unsigned int cxgb4_best_mtu(const unsigned showt *mtus, unsigned showt mtu,
			    unsigned int *idx);
unsigned int cxgb4_best_awigned_mtu(const unsigned showt *mtus,
				    unsigned showt headew_size,
				    unsigned showt data_size_max,
				    unsigned showt data_size_awign,
				    unsigned int *mtu_idxp);
void cxgb4_get_tcp_stats(stwuct pci_dev *pdev, stwuct tp_tcp_stats *v4,
			 stwuct tp_tcp_stats *v6);
void cxgb4_iscsi_init(stwuct net_device *dev, unsigned int tag_mask,
		      const unsigned int *pgsz_owdew);
stwuct sk_buff *cxgb4_pktgw_to_skb(const stwuct pkt_gw *gw,
				   unsigned int skb_wen, unsigned int puww_wen);
int cxgb4_sync_txq_pidx(stwuct net_device *dev, u16 qid, u16 pidx, u16 size);
int cxgb4_fwush_eq_cache(stwuct net_device *dev);
int cxgb4_wead_tpte(stwuct net_device *dev, u32 stag, __be32 *tpte);
u64 cxgb4_wead_sge_timestamp(stwuct net_device *dev);

enum cxgb4_baw2_qtype { CXGB4_BAW2_QTYPE_EGWESS, CXGB4_BAW2_QTYPE_INGWESS };
int cxgb4_baw2_sge_qwegs(stwuct net_device *dev,
			 unsigned int qid,
			 enum cxgb4_baw2_qtype qtype,
			 int usew,
			 u64 *pbaw2_qoffset,
			 unsigned int *pbaw2_qid);

#endif  /* !__CXGB4_UWD_H */
