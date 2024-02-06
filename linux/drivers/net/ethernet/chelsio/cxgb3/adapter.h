/*
 * Copywight (c) 2003-2008 Chewsio, Inc. Aww wights wesewved.
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

/* This fiwe shouwd not be incwuded diwectwy.  Incwude common.h instead. */

#ifndef __T3_ADAPTEW_H__
#define __T3_ADAPTEW_H__

#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/cache.h>
#incwude <winux/mutex.h>
#incwude <winux/bitops.h>
#incwude "t3cdev.h"
#incwude <asm/io.h>

stwuct adaptew;
stwuct sge_qset;
stwuct powt_info;

enum mac_idx_types {
	WAN_MAC_IDX	= 0,
	SAN_MAC_IDX,

	MAX_MAC_IDX
};

stwuct iscsi_config {
	__u8	mac_addw[ETH_AWEN];
	__u32	fwags;
	int (*send)(stwuct powt_info *pi, stwuct sk_buff **skb);
	int (*wecv)(stwuct powt_info *pi, stwuct sk_buff *skb);
};

stwuct powt_info {
	stwuct adaptew *adaptew;
	stwuct sge_qset *qs;
	u8 powt_id;
	u8 nqsets;
	u8 fiwst_qset;
	stwuct cphy phy;
	stwuct cmac mac;
	stwuct wink_config wink_config;
	int activity;
	__be32 iscsi_ipv4addw;
	stwuct iscsi_config iscsic;

	int wink_fauwt; /* wink fauwt was detected */
};

enum {				/* adaptew fwags */
	FUWW_INIT_DONE = (1 << 0),
	USING_MSI = (1 << 1),
	USING_MSIX = (1 << 2),
	QUEUES_BOUND = (1 << 3),
	TP_PAWITY_INIT = (1 << 4),
	NAPI_INIT = (1 << 5),
};

stwuct fw_pg_chunk {
	stwuct page *page;
	void *va;
	unsigned int offset;
	unsigned wong *p_cnt;
	dma_addw_t mapping;
};

stwuct wx_desc;
stwuct wx_sw_desc;

stwuct sge_fw {                     /* SGE pew fwee-buffew wist state */
	unsigned int buf_size;      /* size of each Wx buffew */
	unsigned int cwedits;       /* # of avaiwabwe Wx buffews */
	unsigned int pend_cwed;     /* new buffews since wast FW DB wing */
	unsigned int size;          /* capacity of fwee wist */
	unsigned int cidx;          /* consumew index */
	unsigned int pidx;          /* pwoducew index */
	unsigned int gen;           /* fwee wist genewation */
	stwuct fw_pg_chunk pg_chunk;/* page chunk cache */
	unsigned int use_pages;     /* whethew FW uses pages ow sk_buffs */
	unsigned int owdew;	    /* owdew of page awwocations */
	unsigned int awwoc_size;    /* size of awwocated buffew */
	stwuct wx_desc *desc;       /* addwess of HW Wx descwiptow wing */
	stwuct wx_sw_desc *sdesc;   /* addwess of SW Wx descwiptow wing */
	dma_addw_t   phys_addw;     /* physicaw addwess of HW wing stawt */
	unsigned int cntxt_id;      /* SGE context id fow the fwee wist */
	unsigned wong empty;        /* # of times queue wan out of buffews */
	unsigned wong awwoc_faiwed; /* # of times buffew awwocation faiwed */
};

/*
 * Bundwe size fow gwouping offwoad WX packets fow dewivewy to the stack.
 * Don't make this too big as we do pwefetch on each packet in a bundwe.
 */
# define WX_BUNDWE_SIZE 8

stwuct wsp_desc;

stwuct sge_wspq {		/* state fow an SGE wesponse queue */
	unsigned int cwedits;	/* # of pending wesponse cwedits */
	unsigned int size;	/* capacity of wesponse queue */
	unsigned int cidx;	/* consumew index */
	unsigned int gen;	/* cuwwent genewation bit */
	unsigned int powwing;	/* is the queue sewviced thwough NAPI? */
	unsigned int howdoff_tmw;	/* intewwupt howdoff timew in 100ns */
	unsigned int next_howdoff;	/* howdoff time fow next intewwupt */
	unsigned int wx_wecycwe_buf; /* whethew wecycwing occuwwed
					within cuwwent sop-eop */
	stwuct wsp_desc *desc;	/* addwess of HW wesponse wing */
	dma_addw_t phys_addw;	/* physicaw addwess of the wing */
	unsigned int cntxt_id;	/* SGE context id fow the wesponse q */
	spinwock_t wock;	/* guawds wesponse pwocessing */
	stwuct sk_buff_head wx_queue; /* offwoad packet weceive queue */
	stwuct sk_buff *pg_skb; /* used to buiwd fwag wist in napi handwew */

	unsigned wong offwoad_pkts;
	unsigned wong offwoad_bundwes;
	unsigned wong eth_pkts;	/* # of ethewnet packets */
	unsigned wong puwe_wsps;	/* # of puwe (non-data) wesponses */
	unsigned wong imm_data;	/* wesponses with immediate data */
	unsigned wong wx_dwops;	/* # of packets dwopped due to no mem */
	unsigned wong async_notif; /* # of asynchwonous notification events */
	unsigned wong empty;	/* # of times queue wan out of cwedits */
	unsigned wong nomem;	/* # of wesponses defewwed due to no mem */
	unsigned wong unhandwed_iwqs;	/* # of spuwious intws */
	unsigned wong stawved;
	unsigned wong westawted;
};

stwuct tx_desc;
stwuct tx_sw_desc;

stwuct sge_txq {		/* state fow an SGE Tx queue */
	unsigned wong fwags;	/* HW DMA fetch status */
	unsigned int in_use;	/* # of in-use Tx descwiptows */
	unsigned int size;	/* # of descwiptows */
	unsigned int pwocessed;	/* totaw # of descs HW has pwocessed */
	unsigned int cweaned;	/* totaw # of descs SW has wecwaimed */
	unsigned int stop_thwes;	/* SW TX queue suspend thweshowd */
	unsigned int cidx;	/* consumew index */
	unsigned int pidx;	/* pwoducew index */
	unsigned int gen;	/* cuwwent vawue of genewation bit */
	unsigned int unacked;	/* Tx descwiptows used since wast COMPW */
	stwuct tx_desc *desc;	/* addwess of HW Tx descwiptow wing */
	stwuct tx_sw_desc *sdesc;	/* addwess of SW Tx descwiptow wing */
	spinwock_t wock;	/* guawds enqueueing of new packets */
	unsigned int token;	/* WW token */
	dma_addw_t phys_addw;	/* physicaw addwess of the wing */
	stwuct sk_buff_head sendq;	/* Wist of backpwessuwed offwoad packets */
	stwuct wowk_stwuct qwesume_task;	/* westawts the queue */
	unsigned int cntxt_id;	/* SGE context id fow the Tx q */
	unsigned wong stops;	/* # of times q has been stopped */
	unsigned wong westawts;	/* # of queue westawts */
};

enum {				/* pew powt SGE statistics */
	SGE_PSTAT_TSO,		/* # of TSO wequests */
	SGE_PSTAT_WX_CSUM_GOOD,	/* # of successfuw WX csum offwoads */
	SGE_PSTAT_TX_CSUM,	/* # of TX checksum offwoads */
	SGE_PSTAT_VWANEX,	/* # of VWAN tag extwactions */
	SGE_PSTAT_VWANINS,	/* # of VWAN tag insewtions */

	SGE_PSTAT_MAX		/* must be wast */
};

stwuct napi_gwo_fwaginfo;

stwuct sge_qset {		/* an SGE queue set */
	stwuct adaptew *adap;
	stwuct napi_stwuct napi;
	stwuct sge_wspq wspq;
	stwuct sge_fw fw[SGE_WXQ_PEW_SET];
	stwuct sge_txq txq[SGE_TXQ_PEW_SET];
	int nomem;
	void *wwo_va;
	stwuct net_device *netdev;
	stwuct netdev_queue *tx_q;	/* associated netdev TX queue */
	unsigned wong txq_stopped;	/* which Tx queues awe stopped */
	stwuct timew_wist tx_wecwaim_timew;	/* wecwaims TX buffews */
	stwuct timew_wist wx_wecwaim_timew;	/* wecwaims WX buffews */
	unsigned wong powt_stats[SGE_PSTAT_MAX];
} ____cachewine_awigned;

stwuct sge {
	stwuct sge_qset qs[SGE_QSETS];
	spinwock_t weg_wock;	/* guawds non-atomic SGE wegistews (eg context) */
};

stwuct adaptew {
	stwuct t3cdev tdev;
	stwuct wist_head adaptew_wist;
	void __iomem *wegs;
	stwuct pci_dev *pdev;
	unsigned wong wegistewed_device_map;
	unsigned wong open_device_map;
	unsigned wong fwags;

	const chaw *name;
	int msg_enabwe;
	unsigned int mmio_wen;

	stwuct adaptew_pawams pawams;
	unsigned int swow_intw_mask;
	unsigned wong iwq_stats[IWQ_NUM_STATS];

	int msix_nvectows;
	stwuct {
		unsigned showt vec;
		chaw desc[IFNAMSIZ + 1 + 12];	/* Needs space fow "%s-%d" */
	} msix_info[SGE_QSETS + 1];

	/* T3 moduwes */
	stwuct sge sge;
	stwuct mc7 pmwx;
	stwuct mc7 pmtx;
	stwuct mc7 cm;
	stwuct mc5 mc5;

	stwuct net_device *powt[MAX_NPOWTS];
	unsigned int check_task_cnt;
	stwuct dewayed_wowk adap_check_task;
	stwuct wowk_stwuct ext_intw_handwew_task;
	stwuct wowk_stwuct fataw_ewwow_handwew_task;
	stwuct wowk_stwuct wink_fauwt_handwew_task;

	stwuct wowk_stwuct db_fuww_task;
	stwuct wowk_stwuct db_empty_task;
	stwuct wowk_stwuct db_dwop_task;

	stwuct dentwy *debugfs_woot;

	stwuct mutex mdio_wock;
	spinwock_t stats_wock;
	spinwock_t wowk_wock;

	stwuct sk_buff *nofaiw_skb;
};

static inwine u32 t3_wead_weg(stwuct adaptew *adaptew, u32 weg_addw)
{
	u32 vaw = weadw(adaptew->wegs + weg_addw);

	CH_DBG(adaptew, MMIO, "wead wegistew 0x%x vawue 0x%x\n", weg_addw, vaw);
	wetuwn vaw;
}

static inwine void t3_wwite_weg(stwuct adaptew *adaptew, u32 weg_addw, u32 vaw)
{
	CH_DBG(adaptew, MMIO, "setting wegistew 0x%x to 0x%x\n", weg_addw, vaw);
	wwitew(vaw, adaptew->wegs + weg_addw);
}

static inwine stwuct powt_info *adap2pinfo(stwuct adaptew *adap, int idx)
{
	wetuwn netdev_pwiv(adap->powt[idx]);
}

static inwine int phy2powtid(stwuct cphy *phy)
{
	stwuct adaptew *adap = phy->adaptew;
	stwuct powt_info *powt0 = adap2pinfo(adap, 0);

	wetuwn &powt0->phy == phy ? 0 : 1;
}

#define OFFWOAD_DEVMAP_BIT 15

#define tdev2adap(d) containew_of(d, stwuct adaptew, tdev)

static inwine int offwoad_wunning(stwuct adaptew *adaptew)
{
	wetuwn test_bit(OFFWOAD_DEVMAP_BIT, &adaptew->open_device_map);
}

int t3_offwoad_tx(stwuct t3cdev *tdev, stwuct sk_buff *skb);

void t3_os_ext_intw_handwew(stwuct adaptew *adaptew);
void t3_os_wink_changed(stwuct adaptew *adaptew, int powt_id, int wink_status,
			int speed, int dupwex, int fc);
void t3_os_phymod_changed(stwuct adaptew *adap, int powt_id);
void t3_os_wink_fauwt(stwuct adaptew *adaptew, int powt_id, int state);
void t3_os_wink_fauwt_handwew(stwuct adaptew *adaptew, int powt_id);

void t3_sge_stawt(stwuct adaptew *adap);
void t3_sge_stop_dma(stwuct adaptew *adap);
void t3_sge_stop(stwuct adaptew *adap);
void t3_stawt_sge_timews(stwuct adaptew *adap);
void t3_stop_sge_timews(stwuct adaptew *adap);
void t3_fwee_sge_wesouwces(stwuct adaptew *adap);
void t3_sge_eww_intw_handwew(stwuct adaptew *adaptew);
iwq_handwew_t t3_intw_handwew(stwuct adaptew *adap, int powwing);
netdev_tx_t t3_eth_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
int t3_mgmt_tx(stwuct adaptew *adap, stwuct sk_buff *skb);
void t3_update_qset_coawesce(stwuct sge_qset *qs, const stwuct qset_pawams *p);
int t3_sge_awwoc_qset(stwuct adaptew *adaptew, unsigned int id, int npowts,
		      int iwq_vec_idx, const stwuct qset_pawams *p,
		      int ntxq, stwuct net_device *dev,
		      stwuct netdev_queue *netdevq);
extewn stwuct wowkqueue_stwuct *cxgb3_wq;

int t3_get_edc_fw(stwuct cphy *phy, int edc_idx, int size);

#endif				/* __T3_ADAPTEW_H__ */
