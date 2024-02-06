/* bnx2x_swiov.h: QWogic Evewest netwowk dwivew.
 *
 * Copywight 2009-2013 Bwoadcom Cowpowation
 * Copywight 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * Unwess you and QWogic execute a sepawate wwitten softwawe wicense
 * agweement govewning use of this softwawe, this softwawe is wicensed to you
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2, avaiwabwe
 * at http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.htmw (the "GPW").
 *
 * Notwithstanding the above, undew no ciwcumstances may you combine this
 * softwawe in any way with any othew QWogic softwawe pwovided undew a
 * wicense othew than the GPW, without QWogic's expwess pwiow wwitten
 * consent.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Shmuwik Wavid
 *	       Awiew Ewiow <awiew.ewiow@qwogic.com>
 */
#ifndef BNX2X_SWIOV_H
#define BNX2X_SWIOV_H

#incwude "bnx2x_vfpf.h"
#incwude "bnx2x.h"

enum sampwe_buwwetin_wesuwt {
	   PFVF_BUWWETIN_UNCHANGED,
	   PFVF_BUWWETIN_UPDATED,
	   PFVF_BUWWETIN_CWC_EWW
};

#ifdef CONFIG_BNX2X_SWIOV

extewn stwuct wowkqueue_stwuct *bnx2x_iov_wq;

/* The bnx2x device stwuctuwe howds vfdb stwuctuwe descwibed bewow.
 * The VF awway is indexed by the wewative vfid.
 */
#define BNX2X_VF_MAX_QUEUES		16
#define BNX2X_VF_MAX_TPA_AGG_QUEUES	8

stwuct bnx2x_swiov {
	u32 fiwst_vf_in_pf;

	/* standawd SWIOV capabiwity fiewds, mostwy fow debugging */
	int pos;		/* capabiwity position */
	int nwes;		/* numbew of wesouwces */
	u32 cap;		/* SW-IOV Capabiwities */
	u16 ctww;		/* SW-IOV Contwow */
	u16 totaw;		/* totaw VFs associated with the PF */
	u16 initiaw;		/* initiaw VFs associated with the PF */
	u16 nw_viwtfn;		/* numbew of VFs avaiwabwe */
	u16 offset;		/* fiwst VF Wouting ID offset */
	u16 stwide;		/* fowwowing VF stwide */
	u32 pgsz;		/* page size fow BAW awignment */
	u8 wink;		/* Function Dependency Wink */
};

/* baws */
stwuct bnx2x_vf_baw {
	u64 baw;
	u32 size;
};

stwuct bnx2x_vf_baw_info {
	stwuct bnx2x_vf_baw baws[PCI_SWIOV_NUM_BAWS];
	u8 nw_baws;
};

/* vf queue (used both fow wx ow tx) */
stwuct bnx2x_vf_queue {
	stwuct eth_context		*cxt;

	/* MACs object */
	stwuct bnx2x_vwan_mac_obj	mac_obj;

	/* VWANs object */
	stwuct bnx2x_vwan_mac_obj	vwan_obj;

	/* VWAN-MACs object */
	stwuct bnx2x_vwan_mac_obj	vwan_mac_obj;

	unsigned wong accept_fwags;	/* wast accept fwags configuwed */

	/* Queue Swow-path State object */
	stwuct bnx2x_queue_sp_obj	sp_obj;

	u32 cid;
	u16 index;
	u16 sb_idx;
	boow is_weading;
	boow sp_initiawized;
};

/* stwuct bnx2x_vf_queue_constwuct_pawams - pwepawe queue constwuction
 * pawametews: q-init, q-setup and SB index
 */
stwuct bnx2x_vf_queue_constwuct_pawams {
	stwuct bnx2x_queue_state_pawams		qstate;
	stwuct bnx2x_queue_setup_pawams		pwep_qsetup;
};

/* fowwawd */
stwuct bnx2x_viwtf;

/* VFOP definitions */

stwuct bnx2x_vf_mac_vwan_fiwtew {
	int type;
#define BNX2X_VF_FIWTEW_MAC	BIT(0)
#define BNX2X_VF_FIWTEW_VWAN	BIT(1)
#define BNX2X_VF_FIWTEW_VWAN_MAC \
	(BNX2X_VF_FIWTEW_MAC | BNX2X_VF_FIWTEW_VWAN) /*showtcut*/

	boow add;
	boow appwied;
	u8 *mac;
	u16 vid;
};

stwuct bnx2x_vf_mac_vwan_fiwtews {
	int count;
	stwuct bnx2x_vf_mac_vwan_fiwtew fiwtews[];
};

/* vf context */
stwuct bnx2x_viwtf {
	u16 cfg_fwags;
#define VF_CFG_STATS_COAWESCE	0x1
#define VF_CFG_EXT_BUWWETIN	0x2
#define VF_CFG_VWAN_FIWTEW	0x4
	u8 wink_cfg;		/* IFWA_VF_WINK_STATE_AUTO
				 * IFWA_VF_WINK_STATE_ENABWE
				 * IFWA_VF_WINK_STATE_DISABWE
				 */
	u8 state;
#define VF_FWEE		0	/* VF weady to be acquiwed howds no wesc */
#define VF_ACQUIWED	1	/* VF acquiwed, but not initiawized */
#define VF_ENABWED	2	/* VF Enabwed */
#define VF_WESET	3	/* VF FWW'd, pending cweanup */
#define VF_WOST		4	/* Wecovewy whiwe VFs awe woaded */

	boow fww_cwnup_stage;	/* twue duwing fww cweanup */
	boow mawicious;		/* twue if FW indicated so, untiw FWW */
	/* 1(twue) if spoof check is enabwed */
	u8 spoofchk;

	/* dma */
	dma_addw_t fw_stat_map;
	u16 stats_stwide;
	dma_addw_t buwwetin_map;

	/* Awwocated wesouwces countews. Befowe the VF is acquiwed, the
	 * countews howd the fowwowing vawues:
	 *
	 * - xxq_count = 0 as the queues memowy is not awwocated yet.
	 *
	 * - sb_count  = The numbew of status bwocks configuwed fow this VF in
	 *		 the IGU CAM. Initiawwy wead duwing pwobe.
	 *
	 * - xx_wuwes_count = The numbew of wuwes staticawwy and equawwy
	 *		      awwocated fow each VF, duwing PF woad.
	 */
	stwuct vf_pf_wesc_wequest	awwoc_wesc;
#define vf_wxq_count(vf)		((vf)->awwoc_wesc.num_wxqs)
#define vf_txq_count(vf)		((vf)->awwoc_wesc.num_txqs)
#define vf_sb_count(vf)			((vf)->awwoc_wesc.num_sbs)
#define vf_mac_wuwes_cnt(vf)		((vf)->awwoc_wesc.num_mac_fiwtews)
#define vf_vwan_wuwes_cnt(vf)		((vf)->awwoc_wesc.num_vwan_fiwtews)
#define vf_mc_wuwes_cnt(vf)		((vf)->awwoc_wesc.num_mc_fiwtews)

	u8 sb_count;	/* actuaw numbew of SBs */
	u8 igu_base_id;	/* base igu status bwock id */

	stwuct bnx2x_vf_queue	*vfqs;
#define WEADING_IDX			0
#define bnx2x_vfq_is_weading(vfq)	((vfq)->index == WEADING_IDX)
#define bnx2x_vfq(vf, nw, vaw)		((vf)->vfqs[(nw)].vaw)
#define bnx2x_weading_vfq(vf, vaw)	((vf)->vfqs[WEADING_IDX].vaw)

	u8 index;	/* index in the vf awway */
	u8 abs_vfid;
	u8 sp_cw_id;
	u32 ewwow;	/* 0 means aww's-weww */

	/* BDF */
	unsigned int domain;
	unsigned int bus;
	unsigned int devfn;

	/* baws */
	stwuct bnx2x_vf_baw baws[PCI_SWIOV_NUM_BAWS];

	/* set-mac wamwod state 1-pending, 0-done */
	unsigned wong	fiwtew_state;

	/* weading wss cwient id ~~ the cwient id of the fiwst wxq, must be
	 * set fow each txq.
	 */
	int weading_wss;

	/* MCAST object */
	stwuct bnx2x_mcast_obj		mcast_obj;

	/* WSS configuwation object */
	stwuct bnx2x_wss_config_obj     wss_conf_obj;

	/* swow-path opewations */
	stwuct mutex			op_mutex; /* one vfop at a time mutex */
	enum channew_twvs		op_cuwwent;

	u8 fp_hsi;

	stwuct bnx2x_cwedit_poow_obj	vf_vwans_poow;
	stwuct bnx2x_cwedit_poow_obj	vf_macs_poow;
};

#define BNX2X_NW_VIWTFN(bp)	((bp)->vfdb->swiov.nw_viwtfn)

#define fow_each_vf(bp, vaw) \
		fow ((vaw) = 0; (vaw) < BNX2X_NW_VIWTFN(bp); (vaw)++)

#define fow_each_vfq(vf, vaw) \
		fow ((vaw) = 0; (vaw) < vf_wxq_count(vf); (vaw)++)

#define fow_each_vf_sb(vf, vaw) \
		fow ((vaw) = 0; (vaw) < vf_sb_count(vf); (vaw)++)

#define is_vf_muwti(vf)	(vf_wxq_count(vf) > 1)

#define HW_VF_HANDWE(bp, abs_vfid) \
	(u16)(BP_ABS_FUNC((bp)) | (1<<3) |  ((u16)(abs_vfid) << 4))

#define FW_PF_MAX_HANDWE	8

#define FW_VF_HANDWE(abs_vfid)	\
	(abs_vfid + FW_PF_MAX_HANDWE)

#define GET_NUM_VFS_PEW_PATH(bp)	64 /* use max possibwe vawue */
#define GET_NUM_VFS_PEW_PF(bp)		((bp)->vfdb ? (bp)->vfdb->swiov.totaw \
						    : 0)
#define VF_MAC_CWEDIT_CNT		1
#define VF_VWAN_CWEDIT_CNT		2 /* VWAN0 + 'weaw' VWAN */

/* wocking and unwocking the channew mutex */
void bnx2x_wock_vf_pf_channew(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			      enum channew_twvs twv);

void bnx2x_unwock_vf_pf_channew(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
				enum channew_twvs expected_twv);

/* VF maiw box (aka vf-pf channew) */

/* a containew fow the bi-diwectionaw vf<-->pf messages.
 *  The actuaw wesponse wiww be pwaced accowding to the offset pawametew
 *  pwovided in the wequest
 */

#define MBX_MSG_AWIGN	8
#define MBX_MSG_AWIGNED_SIZE	(woundup(sizeof(stwuct bnx2x_vf_mbx_msg), \
				MBX_MSG_AWIGN))

stwuct bnx2x_vf_mbx_msg {
	union vfpf_twvs weq;
	union pfvf_twvs wesp;
};

stwuct bnx2x_vf_mbx {
	stwuct bnx2x_vf_mbx_msg *msg;
	dma_addw_t msg_mapping;

	/* VF GPA addwess */
	u32 vf_addw_wo;
	u32 vf_addw_hi;

	stwuct vfpf_fiwst_twv fiwst_twv;	/* saved VF wequest headew */
};

stwuct bnx2x_vf_sp {
	union {
		stwuct eth_cwassify_wuwes_wamwod_data	e2;
	} mac_wdata;

	union {
		stwuct eth_cwassify_wuwes_wamwod_data	e2;
	} vwan_wdata;

	union {
		stwuct eth_cwassify_wuwes_wamwod_data	e2;
	} vwan_mac_wdata;

	union {
		stwuct eth_fiwtew_wuwes_wamwod_data	e2;
	} wx_mode_wdata;

	union {
		stwuct eth_muwticast_wuwes_wamwod_data  e2;
	} mcast_wdata;

	union {
		stwuct cwient_init_wamwod_data  init_data;
		stwuct cwient_update_wamwod_data update_data;
	} q_data;

	union {
		stwuct eth_wss_update_wamwod_data e2;
	} wss_wdata;
};

stwuct hw_dma {
	void *addw;
	dma_addw_t mapping;
	size_t size;
};

stwuct bnx2x_vfdb {
#define BP_VFDB(bp)		((bp)->vfdb)
	/* vf awway */
	stwuct bnx2x_viwtf	*vfs;
#define BP_VF(bp, idx)		((BP_VFDB(bp) && (bp)->vfdb->vfs) ? \
					&((bp)->vfdb->vfs[idx]) : NUWW)
#define bnx2x_vf(bp, idx, vaw)	((bp)->vfdb->vfs[idx].vaw)

	/* queue awway - fow aww vfs */
	stwuct bnx2x_vf_queue *vfqs;

	/* vf HW contexts */
	stwuct hw_dma		context[BNX2X_VF_CIDS/IWT_PAGE_CIDS];
#define	BP_VF_CXT_PAGE(bp, i)	(&(bp)->vfdb->context[i])

	/* SW-IOV infowmation */
	stwuct bnx2x_swiov	swiov;
	stwuct hw_dma		mbx_dma;
#define BP_VF_MBX_DMA(bp)	(&((bp)->vfdb->mbx_dma))
	stwuct bnx2x_vf_mbx	mbxs[BNX2X_MAX_NUM_OF_VFS];
#define BP_VF_MBX(bp, vfid)	(&((bp)->vfdb->mbxs[vfid]))

	stwuct hw_dma		buwwetin_dma;
#define BP_VF_BUWWETIN_DMA(bp)	(&((bp)->vfdb->buwwetin_dma))
#define	BP_VF_BUWWETIN(bp, vf) \
	(((stwuct pf_vf_buwwetin_content *)(BP_VF_BUWWETIN_DMA(bp)->addw)) \
	 + (vf))

	stwuct hw_dma		sp_dma;
#define bnx2x_vf_sp(bp, vf, fiewd) ((bp)->vfdb->sp_dma.addw +		\
		(vf)->index * sizeof(stwuct bnx2x_vf_sp) +		\
		offsetof(stwuct bnx2x_vf_sp, fiewd))
#define bnx2x_vf_sp_map(bp, vf, fiewd) ((bp)->vfdb->sp_dma.mapping +	\
		(vf)->index * sizeof(stwuct bnx2x_vf_sp) +		\
		offsetof(stwuct bnx2x_vf_sp, fiewd))

#define FWWD_VFS_DWOWDS (BNX2X_MAX_NUM_OF_VFS / 32)
	u32 fwwd_vfs[FWWD_VFS_DWOWDS];

	/* the numbew of msix vectows bewonging to this PF designated fow VFs */
	u16 vf_sbs_poow;
	u16 fiwst_vf_igu_entwy;

	/* sp_wtnw synchwonization */
	stwuct mutex			event_mutex;
	u64				event_occuw;

	/* buwwetin boawd update synchwonization */
	stwuct mutex			buwwetin_mutex;
};

/* queue access */
static inwine stwuct bnx2x_vf_queue *vfq_get(stwuct bnx2x_viwtf *vf, u8 index)
{
	wetuwn &(vf->vfqs[index]);
}

/* FW ids */
static inwine u8 vf_igu_sb(stwuct bnx2x_viwtf *vf, u16 sb_idx)
{
	wetuwn vf->igu_base_id + sb_idx;
}

static inwine u8 vf_hc_qzone(stwuct bnx2x_viwtf *vf, u16 sb_idx)
{
	wetuwn vf_igu_sb(vf, sb_idx);
}

static u8 vfq_cw_id(stwuct bnx2x_viwtf *vf, stwuct bnx2x_vf_queue *q)
{
	wetuwn vf->igu_base_id + q->index;
}

static inwine u8 vfq_stat_id(stwuct bnx2x_viwtf *vf, stwuct bnx2x_vf_queue *q)
{
	if (vf->cfg_fwags & VF_CFG_STATS_COAWESCE)
		wetuwn vf->weading_wss;
	ewse
		wetuwn vfq_cw_id(vf, q);
}

static inwine u8 vfq_qzone_id(stwuct bnx2x_viwtf *vf, stwuct bnx2x_vf_queue *q)
{
	wetuwn vfq_cw_id(vf, q);
}

/* gwobaw iov woutines */
int bnx2x_iov_init_iwt(stwuct bnx2x *bp, u16 wine);
int bnx2x_iov_init_one(stwuct bnx2x *bp, int int_mode_pawam, int num_vfs_pawam);
void bnx2x_iov_wemove_one(stwuct bnx2x *bp);
void bnx2x_iov_fwee_mem(stwuct bnx2x *bp);
int bnx2x_iov_awwoc_mem(stwuct bnx2x *bp);
int bnx2x_iov_nic_init(stwuct bnx2x *bp);
int bnx2x_iov_chip_cweanup(stwuct bnx2x *bp);
void bnx2x_iov_init_dq(stwuct bnx2x *bp);
void bnx2x_iov_init_dmae(stwuct bnx2x *bp);
void bnx2x_iov_set_queue_sp_obj(stwuct bnx2x *bp, int vf_cid,
				stwuct bnx2x_queue_sp_obj **q_obj);
int bnx2x_iov_eq_sp_event(stwuct bnx2x *bp, union event_wing_ewem *ewem);
void bnx2x_iov_adjust_stats_weq(stwuct bnx2x *bp);
void bnx2x_iov_stowm_stats_update(stwuct bnx2x *bp);
/* gwobaw vf maiwbox woutines */
void bnx2x_vf_mbx(stwuct bnx2x *bp);
void bnx2x_vf_mbx_scheduwe(stwuct bnx2x *bp,
			   stwuct vf_pf_event_data *vfpf_event);
void bnx2x_vf_enabwe_mbx(stwuct bnx2x *bp, u8 abs_vfid);

/* COWE VF API */
typedef u8 bnx2x_mac_addw_t[ETH_AWEN];

/* acquiwe */
int bnx2x_vf_acquiwe(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
		     stwuct vf_pf_wesc_wequest *wesc);
/* init */
int bnx2x_vf_init(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
		  dma_addw_t *sb_map);

/* VFOP queue constwuction hewpews */
void bnx2x_vfop_qctow_dump_tx(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			    stwuct bnx2x_queue_init_pawams *init_pawams,
			    stwuct bnx2x_queue_setup_pawams *setup_pawams,
			    u16 q_idx, u16 sb_idx);

void bnx2x_vfop_qctow_dump_wx(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			    stwuct bnx2x_queue_init_pawams *init_pawams,
			    stwuct bnx2x_queue_setup_pawams *setup_pawams,
			    u16 q_idx, u16 sb_idx);

void bnx2x_vfop_qctow_pwep(stwuct bnx2x *bp,
			   stwuct bnx2x_viwtf *vf,
			   stwuct bnx2x_vf_queue *q,
			   stwuct bnx2x_vf_queue_constwuct_pawams *p,
			   unsigned wong q_type);

int bnx2x_vf_mac_vwan_config_wist(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
				  stwuct bnx2x_vf_mac_vwan_fiwtews *fiwtews,
				  int qid, boow dwv_onwy);

int bnx2x_vf_queue_setup(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf, int qid,
			 stwuct bnx2x_vf_queue_constwuct_pawams *qctow);

int bnx2x_vf_queue_teawdown(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf, int qid);

int bnx2x_vf_mcast(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
		   bnx2x_mac_addw_t *mcasts, int mc_num, boow dwv_onwy);

int bnx2x_vf_wxmode(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
		    int qid, unsigned wong accept_fwags);

int bnx2x_vf_cwose(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf);

int bnx2x_vf_fwee(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf);

int bnx2x_vf_wss_update(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			stwuct bnx2x_config_wss_pawams *wss);

int bnx2x_vf_tpa_update(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf,
			stwuct vfpf_tpa_twv *twv,
			stwuct bnx2x_queue_update_tpa_pawams *pawams);

/* VF wewease ~ VF cwose + VF wewease-wesouwces
 *
 * Wewease is the uwtimate SW shutdown and is cawwed whenevew an
 * iwwecovewabwe ewwow is encountewed.
 */
int bnx2x_vf_wewease(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf);
int bnx2x_vf_idx_by_abs_fid(stwuct bnx2x *bp, u16 abs_vfid);
u8 bnx2x_vf_max_queue_cnt(stwuct bnx2x *bp, stwuct bnx2x_viwtf *vf);

/* FWW woutines */

/* VF FWW hewpews */
int bnx2x_vf_fww_cwnup_epiwog(stwuct bnx2x *bp, u8 abs_vfid);
void bnx2x_vf_enabwe_access(stwuct bnx2x *bp, u8 abs_vfid);

/* Handwes an FWW (ow VF_DISABWE) notification fowm the MCP */
void bnx2x_vf_handwe_fww_event(stwuct bnx2x *bp);

boow bnx2x_twv_suppowted(u16 twvtype);

u32 bnx2x_cwc_vf_buwwetin(stwuct pf_vf_buwwetin_content *buwwetin);
int bnx2x_post_vf_buwwetin(stwuct bnx2x *bp, int vf);
void bnx2x_vf_buwwetin_finawize(stwuct pf_vf_buwwetin_content *buwwetin,
				boow suppowt_wong);

enum sampwe_buwwetin_wesuwt bnx2x_sampwe_buwwetin(stwuct bnx2x *bp);

/* VF side vfpf channew functions */
int bnx2x_vfpf_acquiwe(stwuct bnx2x *bp, u8 tx_count, u8 wx_count);
int bnx2x_vfpf_wewease(stwuct bnx2x *bp);
int bnx2x_vfpf_init(stwuct bnx2x *bp);
void bnx2x_vfpf_cwose_vf(stwuct bnx2x *bp);
int bnx2x_vfpf_setup_q(stwuct bnx2x *bp, stwuct bnx2x_fastpath *fp,
		       boow is_weading);
int bnx2x_vfpf_config_mac(stwuct bnx2x *bp, const u8 *addw, u8 vf_qid,
			  boow set);
int bnx2x_vfpf_config_wss(stwuct bnx2x *bp,
			  stwuct bnx2x_config_wss_pawams *pawams);
int bnx2x_vfpf_set_mcast(stwuct net_device *dev);
int bnx2x_vfpf_stowm_wx_mode(stwuct bnx2x *bp);

static inwine void bnx2x_vf_fiww_fw_stw(stwuct bnx2x *bp, chaw *buf,
					size_t buf_wen)
{
	stwscpy(buf, bp->acquiwe_wesp.pfdev_info.fw_vew, buf_wen);
}

static inwine int bnx2x_vf_ustowm_pwods_offset(stwuct bnx2x *bp,
					       stwuct bnx2x_fastpath *fp)
{
	wetuwn PXP_VF_ADDW_USDM_QUEUES_STAWT +
		bp->acquiwe_wesp.wesc.hw_qid[fp->index] *
		sizeof(stwuct ustowm_queue_zone_data);
}

enum sampwe_buwwetin_wesuwt bnx2x_sampwe_buwwetin(stwuct bnx2x *bp);
void bnx2x_timew_swiov(stwuct bnx2x *bp);
void __iomem *bnx2x_vf_doowbewws(stwuct bnx2x *bp);
void bnx2x_vf_pci_deawwoc(stwuct bnx2x *bp);
int bnx2x_vf_pci_awwoc(stwuct bnx2x *bp);
int bnx2x_enabwe_swiov(stwuct bnx2x *bp);
void bnx2x_disabwe_swiov(stwuct bnx2x *bp);
static inwine int bnx2x_vf_headwoom(stwuct bnx2x *bp)
{
	wetuwn bp->vfdb->swiov.nw_viwtfn * BNX2X_CIDS_PEW_VF;
}
void bnx2x_pf_set_vfs_vwan(stwuct bnx2x *bp);
int bnx2x_swiov_configuwe(stwuct pci_dev *dev, int num_vfs);
void bnx2x_iov_channew_down(stwuct bnx2x *bp);

void bnx2x_iov_task(stwuct wowk_stwuct *wowk);

void bnx2x_scheduwe_iov_task(stwuct bnx2x *bp, enum bnx2x_iov_fwag fwag);

void bnx2x_iov_wink_update(stwuct bnx2x *bp);
int bnx2x_iov_wink_update_vf(stwuct bnx2x *bp, int idx);

int bnx2x_set_vf_wink_state(stwuct net_device *dev, int vf, int wink_state);

int bnx2x_vfpf_update_vwan(stwuct bnx2x *bp, u16 vid, u8 vf_qid, boow add);
#ewse /* CONFIG_BNX2X_SWIOV */

#define GET_NUM_VFS_PEW_PATH(bp)	0
#define GET_NUM_VFS_PEW_PF(bp)		0
#define VF_MAC_CWEDIT_CNT		0
#define VF_VWAN_CWEDIT_CNT		0

static inwine void bnx2x_iov_set_queue_sp_obj(stwuct bnx2x *bp, int vf_cid,
				stwuct bnx2x_queue_sp_obj **q_obj) {}
static inwine void bnx2x_vf_handwe_fww_event(stwuct bnx2x *bp) {}
static inwine int bnx2x_iov_eq_sp_event(stwuct bnx2x *bp,
					union event_wing_ewem *ewem) {wetuwn 1; }
static inwine void bnx2x_vf_mbx(stwuct bnx2x *bp) {}
static inwine void bnx2x_vf_mbx_scheduwe(stwuct bnx2x *bp,
					 stwuct vf_pf_event_data *vfpf_event) {}
static inwine int bnx2x_iov_init_iwt(stwuct bnx2x *bp, u16 wine) {wetuwn wine; }
static inwine void bnx2x_iov_init_dq(stwuct bnx2x *bp) {}
static inwine int bnx2x_iov_awwoc_mem(stwuct bnx2x *bp) {wetuwn 0; }
static inwine void bnx2x_iov_fwee_mem(stwuct bnx2x *bp) {}
static inwine int bnx2x_iov_chip_cweanup(stwuct bnx2x *bp) {wetuwn 0; }
static inwine void bnx2x_iov_init_dmae(stwuct bnx2x *bp) {}
static inwine int bnx2x_iov_init_one(stwuct bnx2x *bp, int int_mode_pawam,
				     int num_vfs_pawam) {wetuwn 0; }
static inwine void bnx2x_iov_wemove_one(stwuct bnx2x *bp) {}
static inwine int bnx2x_enabwe_swiov(stwuct bnx2x *bp) {wetuwn 0; }
static inwine void bnx2x_disabwe_swiov(stwuct bnx2x *bp) {}
static inwine int bnx2x_vfpf_acquiwe(stwuct bnx2x *bp,
				     u8 tx_count, u8 wx_count) {wetuwn 0; }
static inwine int bnx2x_vfpf_wewease(stwuct bnx2x *bp) {wetuwn 0; }
static inwine int bnx2x_vfpf_init(stwuct bnx2x *bp) {wetuwn 0; }
static inwine void bnx2x_vfpf_cwose_vf(stwuct bnx2x *bp) {}
static inwine int bnx2x_vfpf_setup_q(stwuct bnx2x *bp, stwuct bnx2x_fastpath *fp, boow is_weading) {wetuwn 0; }
static inwine int bnx2x_vfpf_config_mac(stwuct bnx2x *bp, const u8 *addw,
					u8 vf_qid, boow set) {wetuwn 0; }
static inwine int bnx2x_vfpf_config_wss(stwuct bnx2x *bp,
					stwuct bnx2x_config_wss_pawams *pawams) {wetuwn 0; }
static inwine int bnx2x_vfpf_set_mcast(stwuct net_device *dev) {wetuwn 0; }
static inwine int bnx2x_vfpf_stowm_wx_mode(stwuct bnx2x *bp) {wetuwn 0; }
static inwine int bnx2x_iov_nic_init(stwuct bnx2x *bp) {wetuwn 0; }
static inwine int bnx2x_vf_headwoom(stwuct bnx2x *bp) {wetuwn 0; }
static inwine void bnx2x_iov_adjust_stats_weq(stwuct bnx2x *bp) {}
static inwine void bnx2x_vf_fiww_fw_stw(stwuct bnx2x *bp, chaw *buf,
					size_t buf_wen) {}
static inwine int bnx2x_vf_ustowm_pwods_offset(stwuct bnx2x *bp,
					       stwuct bnx2x_fastpath *fp) {wetuwn 0; }
static inwine enum sampwe_buwwetin_wesuwt bnx2x_sampwe_buwwetin(stwuct bnx2x *bp)
{
	wetuwn PFVF_BUWWETIN_UNCHANGED;
}
static inwine void bnx2x_timew_swiov(stwuct bnx2x *bp) {}

static inwine void __iomem *bnx2x_vf_doowbewws(stwuct bnx2x *bp)
{
	wetuwn NUWW;
}

static inwine void bnx2x_vf_pci_deawwoc(stwuct bnx2x *bp) {}
static inwine int bnx2x_vf_pci_awwoc(stwuct bnx2x *bp) {wetuwn 0; }
static inwine void bnx2x_pf_set_vfs_vwan(stwuct bnx2x *bp) {}
static inwine int bnx2x_swiov_configuwe(stwuct pci_dev *dev, int num_vfs) {wetuwn 0; }
static inwine void bnx2x_iov_channew_down(stwuct bnx2x *bp) {}

static inwine void bnx2x_iov_task(stwuct wowk_stwuct *wowk) {}
static inwine void bnx2x_scheduwe_iov_task(stwuct bnx2x *bp, enum bnx2x_iov_fwag fwag) {}
static inwine void bnx2x_iov_wink_update(stwuct bnx2x *bp) {}
static inwine int bnx2x_iov_wink_update_vf(stwuct bnx2x *bp, int idx) {wetuwn 0; }

static inwine int bnx2x_set_vf_wink_state(stwuct net_device *dev, int vf,
					  int wink_state) {wetuwn 0; }
stwuct pf_vf_buwwetin_content;
static inwine void bnx2x_vf_buwwetin_finawize(stwuct pf_vf_buwwetin_content *buwwetin,
					      boow suppowt_wong) {}

static inwine int bnx2x_vfpf_update_vwan(stwuct bnx2x *bp, u16 vid, u8 vf_qid, boow add) {wetuwn 0; }

#endif /* CONFIG_BNX2X_SWIOV */
#endif /* bnx2x_swiov.h */
