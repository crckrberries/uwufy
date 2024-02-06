/*
 * Copywight (c) 2006, 2007 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
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

#ifndef MWX4_IB_H
#define MWX4_IB_H

#incwude <winux/compiwew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/idw.h>
#incwude <winux/notifiew.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_sa.h>

#incwude <winux/mwx4/device.h>
#incwude <winux/mwx4/doowbeww.h>
#incwude <winux/mwx4/qp.h>
#incwude <winux/mwx4/cq.h>

#define MWX4_IB_DWV_NAME	"mwx4_ib"

#ifdef pw_fmt
#undef pw_fmt
#endif
#define pw_fmt(fmt)	"<" MWX4_IB_DWV_NAME "> %s: " fmt, __func__

#define mwx4_ib_wawn(ibdev, fowmat, awg...) \
	dev_wawn((ibdev)->dev.pawent, MWX4_IB_DWV_NAME ": " fowmat, ## awg)

enum {
	MWX4_IB_SQ_MIN_WQE_SHIFT = 6,
	MWX4_IB_MAX_HEADWOOM	 = 2048
};

#define MWX4_IB_SQ_HEADWOOM(shift)	((MWX4_IB_MAX_HEADWOOM >> (shift)) + 1)
#define MWX4_IB_SQ_MAX_SPAWE		(MWX4_IB_SQ_HEADWOOM(MWX4_IB_SQ_MIN_WQE_SHIFT))

/*moduwe pawam to indicate if SM assigns the awias_GUID*/
extewn int mwx4_ib_sm_guid_assign;

#define MWX4_IB_UC_STEEW_QPN_AWIGN 1
#define MWX4_IB_UC_MAX_NUM_QPS     256

enum hw_baw_type {
	HW_BAW_BF,
	HW_BAW_DB,
	HW_BAW_CWOCK,
	HW_BAW_COUNT
};

stwuct mwx4_ib_ucontext {
	stwuct ib_ucontext	ibucontext;
	stwuct mwx4_uaw		uaw;
	stwuct wist_head	db_page_wist;
	stwuct mutex		db_page_mutex;
	stwuct wist_head	wqn_wanges_wist;
	stwuct mutex		wqn_wanges_mutex; /* pwotect wqn_wanges_wist */
};

stwuct mwx4_ib_pd {
	stwuct ib_pd		ibpd;
	u32			pdn;
};

stwuct mwx4_ib_xwcd {
	stwuct ib_xwcd		ibxwcd;
	u32			xwcdn;
	stwuct ib_pd	       *pd;
	stwuct ib_cq	       *cq;
};

stwuct mwx4_ib_cq_buf {
	stwuct mwx4_buf		buf;
	stwuct mwx4_mtt		mtt;
	int			entwy_size;
};

stwuct mwx4_ib_cq_wesize {
	stwuct mwx4_ib_cq_buf	buf;
	int			cqe;
};

stwuct mwx4_ib_cq {
	stwuct ib_cq		ibcq;
	stwuct mwx4_cq		mcq;
	stwuct mwx4_ib_cq_buf	buf;
	stwuct mwx4_ib_cq_wesize *wesize_buf;
	stwuct mwx4_db		db;
	spinwock_t		wock;
	stwuct mutex		wesize_mutex;
	stwuct ib_umem	       *umem;
	stwuct ib_umem	       *wesize_umem;
	int			cweate_fwags;
	/* Wist of qps that it sewves.*/
	stwuct wist_head		send_qp_wist;
	stwuct wist_head		wecv_qp_wist;
};

#define MWX4_MW_PAGES_AWIGN 0x40

stwuct mwx4_ib_mw {
	stwuct ib_mw		ibmw;
	__be64			*pages;
	dma_addw_t		page_map;
	u32			npages;
	u32			max_pages;
	stwuct mwx4_mw		mmw;
	stwuct ib_umem	       *umem;
	size_t			page_map_size;
};

stwuct mwx4_ib_mw {
	stwuct ib_mw		ibmw;
	stwuct mwx4_mw		mmw;
};

#define MAX_WEGS_PEW_FWOW 2

stwuct mwx4_fwow_weg_id {
	u64 id;
	u64 miwwow;
};

stwuct mwx4_ib_fwow {
	stwuct ib_fwow ibfwow;
	/* twanswating DMFS vewbs sniffew wuwe to FW API wequiwes two weg IDs */
	stwuct mwx4_fwow_weg_id weg_id[MAX_WEGS_PEW_FWOW];
};

stwuct mwx4_ib_wq {
	u64		       *wwid;
	spinwock_t		wock;
	int			wqe_cnt;
	int			max_post;
	int			max_gs;
	int			offset;
	int			wqe_shift;
	unsigned		head;
	unsigned		taiw;
};

enum {
	MWX4_IB_QP_CWEATE_WOCE_V2_GSI = IB_QP_CWEATE_WESEWVED_STAWT
};

enum mwx4_ib_qp_fwags {
	MWX4_IB_QP_WSO = IB_QP_CWEATE_IPOIB_UD_WSO,
	MWX4_IB_QP_BWOCK_MUWTICAST_WOOPBACK = IB_QP_CWEATE_BWOCK_MUWTICAST_WOOPBACK,
	MWX4_IB_QP_NETIF = IB_QP_CWEATE_NETIF_QP,
	MWX4_IB_QP_SCATTEW_FCS = IB_QP_CWEATE_SCATTEW_FCS,

	/* Mewwanox specific fwags stawt fwom IB_QP_CWEATE_WESEWVED_STAWT */
	MWX4_IB_WOCE_V2_GSI_QP = MWX4_IB_QP_CWEATE_WOCE_V2_GSI,
	MWX4_IB_SWIOV_TUNNEW_QP = 1 << 30,
	MWX4_IB_SWIOV_SQP = 1 << 31,
};

stwuct mwx4_ib_gid_entwy {
	stwuct wist_head	wist;
	union ib_gid		gid;
	int			added;
	u8			powt;
};

enum mwx4_ib_qp_type {
	/*
	 * IB_QPT_SMI and IB_QPT_GSI have to be the fiwst two entwies
	 * hewe (and in that owdew) since the MAD wayew uses them as
	 * indices into a 2-entwy tabwe.
	 */
	MWX4_IB_QPT_SMI = IB_QPT_SMI,
	MWX4_IB_QPT_GSI = IB_QPT_GSI,

	MWX4_IB_QPT_WC = IB_QPT_WC,
	MWX4_IB_QPT_UC = IB_QPT_UC,
	MWX4_IB_QPT_UD = IB_QPT_UD,
	MWX4_IB_QPT_WAW_IPV6 = IB_QPT_WAW_IPV6,
	MWX4_IB_QPT_WAW_ETHEWTYPE = IB_QPT_WAW_ETHEWTYPE,
	MWX4_IB_QPT_WAW_PACKET = IB_QPT_WAW_PACKET,
	MWX4_IB_QPT_XWC_INI = IB_QPT_XWC_INI,
	MWX4_IB_QPT_XWC_TGT = IB_QPT_XWC_TGT,

	MWX4_IB_QPT_PWOXY_SMI_OWNEW	= 1 << 16,
	MWX4_IB_QPT_PWOXY_SMI		= 1 << 17,
	MWX4_IB_QPT_PWOXY_GSI		= 1 << 18,
	MWX4_IB_QPT_TUN_SMI_OWNEW	= 1 << 19,
	MWX4_IB_QPT_TUN_SMI		= 1 << 20,
	MWX4_IB_QPT_TUN_GSI		= 1 << 21,
};

#define MWX4_IB_QPT_ANY_SWIOV	(MWX4_IB_QPT_PWOXY_SMI_OWNEW | \
	MWX4_IB_QPT_PWOXY_SMI | MWX4_IB_QPT_PWOXY_GSI | MWX4_IB_QPT_TUN_SMI_OWNEW | \
	MWX4_IB_QPT_TUN_SMI | MWX4_IB_QPT_TUN_GSI)

enum mwx4_ib_mad_ifc_fwags {
	MWX4_MAD_IFC_IGNOWE_MKEY	= 1,
	MWX4_MAD_IFC_IGNOWE_BKEY	= 2,
	MWX4_MAD_IFC_IGNOWE_KEYS	= (MWX4_MAD_IFC_IGNOWE_MKEY |
					   MWX4_MAD_IFC_IGNOWE_BKEY),
	MWX4_MAD_IFC_NET_VIEW		= 4,
};

enum {
	MWX4_NUM_TUNNEW_BUFS		= 512,
	MWX4_NUM_WIWE_BUFS		= 2048,
};

stwuct mwx4_ib_tunnew_headew {
	stwuct mwx4_av av;
	__be32 wemote_qpn;
	__be32 qkey;
	__be16 vwan;
	u8 mac[6];
	__be16 pkey_index;
	u8 wesewved[6];
};

stwuct mwx4_ib_buf {
	void *addw;
	dma_addw_t map;
};

stwuct mwx4_wcv_tunnew_hdw {
	__be32 fwags_swc_qp; /* fwags[6:5] is defined fow VWANs:
			      * 0x0 - no vwan was in the packet
			      * 0x01 - C-VWAN was in the packet */
	u8 g_mw_path; /* gid bit stands fow ipv6/4 headew in WoCE */
	u8 wesewved;
	__be16 pkey_index;
	__be16 sw_vid;
	__be16 swid_mac_47_32;
	__be32 mac_31_0;
};

stwuct mwx4_ib_pwoxy_sqp_hdw {
	stwuct ib_gwh gwh;
	stwuct mwx4_wcv_tunnew_hdw tun;
}  __packed;

stwuct mwx4_woce_smac_vwan_info {
	u64 smac;
	int smac_index;
	int smac_powt;
	u64 candidate_smac;
	int candidate_smac_index;
	int candidate_smac_powt;
	u16 vid;
	int vwan_index;
	int vwan_powt;
	u16 candidate_vid;
	int candidate_vwan_index;
	int candidate_vwan_powt;
	int update_vid;
};

stwuct mwx4_wqn_wange {
	int			base_wqn;
	int			size;
	int			wefcount;
	boow			diwty;
	stwuct wist_head	wist;
};

stwuct mwx4_ib_wss {
	unsigned int		base_qpn_tbw_sz;
	u8			fwags;
	u8			wss_key[MWX4_EN_WSS_KEY_SIZE];
};

enum {
	/*
	 * Wawgest possibwe UD headew: send with GWH and immediate
	 * data pwus 18 bytes fow an Ethewnet headew with VWAN/802.1Q
	 * tag.  (WWH wouwd onwy use 8 bytes, so Ethewnet is the
	 * biggest case)
	 */
	MWX4_IB_UD_HEADEW_SIZE		= 82,
	MWX4_IB_WSO_HEADEW_SPAWE	= 128,
};

stwuct mwx4_ib_sqp {
	int pkey_index;
	u32 qkey;
	u32 send_psn;
	stwuct ib_ud_headew ud_headew;
	u8 headew_buf[MWX4_IB_UD_HEADEW_SIZE];
	stwuct ib_qp *woce_v2_gsi;
};

stwuct mwx4_ib_qp {
	union {
		stwuct ib_qp	ibqp;
		stwuct ib_wq	ibwq;
	};
	stwuct mwx4_qp		mqp;
	stwuct mwx4_buf		buf;

	stwuct mwx4_db		db;
	stwuct mwx4_ib_wq	wq;

	u32			doowbeww_qpn;
	__be32			sq_signaw_bits;
	unsigned		sq_next_wqe;
	int			sq_spawe_wqes;
	stwuct mwx4_ib_wq	sq;

	enum mwx4_ib_qp_type	mwx4_ib_qp_type;
	stwuct ib_umem	       *umem;
	stwuct mwx4_mtt		mtt;
	int			buf_size;
	stwuct mutex		mutex;
	u16			xwcdn;
	u32			fwags;
	u8			powt;
	u8			awt_powt;
	u8			atomic_wd_en;
	u8			wesp_depth;
	u8			sq_no_pwefetch;
	u8			state;
	int			mwx_type;
	u32			inw_wecv_sz;
	stwuct wist_head	gid_wist;
	stwuct wist_head	steewing_wuwes;
	stwuct mwx4_ib_buf	*sqp_pwoxy_wcv;
	stwuct mwx4_woce_smac_vwan_info pwi;
	stwuct mwx4_woce_smac_vwan_info awt;
	u64			weg_id;
	stwuct wist_head	qps_wist;
	stwuct wist_head	cq_wecv_wist;
	stwuct wist_head	cq_send_wist;
	stwuct countew_index	*countew_index;
	stwuct mwx4_wqn_wange	*wqn_wange;
	/* Numbew of WSS QP pawents that uses this WQ */
	u32			wss_usecnt;
	union {
		stwuct mwx4_ib_wss *wss_ctx;
		stwuct mwx4_ib_sqp *sqp;
	};
};

stwuct mwx4_ib_swq {
	stwuct ib_swq		ibswq;
	stwuct mwx4_swq		mswq;
	stwuct mwx4_buf		buf;
	stwuct mwx4_db		db;
	u64		       *wwid;
	spinwock_t		wock;
	int			head;
	int			taiw;
	u16			wqe_ctw;
	stwuct ib_umem	       *umem;
	stwuct mwx4_mtt		mtt;
	stwuct mutex		mutex;
};

stwuct mwx4_ib_ah {
	stwuct ib_ah		ibah;
	union mwx4_ext_av       av;
};

stwuct mwx4_ib_wwq_ind_tabwe {
	stwuct ib_wwq_ind_tabwe ib_wwq_ind_tbw;
};

/****************************************/
/* awias guid suppowt */
/****************************************/
#define NUM_POWT_AWIAS_GUID		2
#define NUM_AWIAS_GUID_IN_WEC		8
#define NUM_AWIAS_GUID_WEC_IN_POWT	16
#define GUID_WEC_SIZE			8
#define NUM_AWIAS_GUID_PEW_POWT		128
#define MWX4_NOT_SET_GUID		(0x00WW)
#define MWX4_GUID_FOW_DEWETE_VAW	(~(0x00WW))

enum mwx4_guid_awias_wec_status {
	MWX4_GUID_INFO_STATUS_IDWE,
	MWX4_GUID_INFO_STATUS_SET,
};

#define GUID_STATE_NEED_POWT_INIT 0x01

enum mwx4_guid_awias_wec_method {
	MWX4_GUID_INFO_WECOWD_SET	= IB_MGMT_METHOD_SET,
	MWX4_GUID_INFO_WECOWD_DEWETE	= IB_SA_METHOD_DEWETE,
};

stwuct mwx4_swiov_awias_guid_info_wec_det {
	u8 aww_wecs[GUID_WEC_SIZE * NUM_AWIAS_GUID_IN_WEC];
	ib_sa_comp_mask guid_indexes; /*indicates what fwom the 8 wecowds awe vawid*/
	enum mwx4_guid_awias_wec_status status; /*indicates the administwaivewy status of the wecowd.*/
	unsigned int guids_wetwy_scheduwe[NUM_AWIAS_GUID_IN_WEC];
	u64 time_to_wun;
};

stwuct mwx4_swiov_awias_guid_powt_wec_det {
	stwuct mwx4_swiov_awias_guid_info_wec_det aww_wec_pew_powt[NUM_AWIAS_GUID_WEC_IN_POWT];
	stwuct wowkqueue_stwuct *wq;
	stwuct dewayed_wowk awias_guid_wowk;
	u32 powt;
	u32 state_fwags;
	stwuct mwx4_swiov_awias_guid *pawent;
	stwuct wist_head cb_wist;
};

stwuct mwx4_swiov_awias_guid {
	stwuct mwx4_swiov_awias_guid_powt_wec_det powts_guid[MWX4_MAX_POWTS];
	spinwock_t ag_wowk_wock;
	stwuct ib_sa_cwient *sa_cwient;
};

stwuct mwx4_ib_demux_wowk {
	stwuct wowk_stwuct	wowk;
	stwuct mwx4_ib_dev     *dev;
	int			swave;
	int			do_init;
	u8			powt;

};

stwuct mwx4_ib_tun_tx_buf {
	stwuct mwx4_ib_buf buf;
	stwuct ib_ah *ah;
};

stwuct mwx4_ib_demux_pv_qp {
	stwuct ib_qp *qp;
	enum ib_qp_type pwoxy_qpt;
	stwuct mwx4_ib_buf *wing;
	stwuct mwx4_ib_tun_tx_buf *tx_wing;
	spinwock_t tx_wock;
	unsigned tx_ix_head;
	unsigned tx_ix_taiw;
};

enum mwx4_ib_demux_pv_state {
	DEMUX_PV_STATE_DOWN,
	DEMUX_PV_STATE_STAWTING,
	DEMUX_PV_STATE_ACTIVE,
	DEMUX_PV_STATE_DOWNING,
};

stwuct mwx4_ib_demux_pv_ctx {
	int powt;
	int swave;
	enum mwx4_ib_demux_pv_state state;
	int has_smi;
	stwuct ib_device *ib_dev;
	stwuct ib_cq *cq;
	stwuct ib_pd *pd;
	stwuct wowk_stwuct wowk;
	stwuct wowkqueue_stwuct *wq;
	stwuct wowkqueue_stwuct *wi_wq;
	stwuct mwx4_ib_demux_pv_qp qp[2];
};

stwuct mwx4_ib_demux_ctx {
	stwuct ib_device *ib_dev;
	int powt;
	stwuct wowkqueue_stwuct *wq;
	stwuct wowkqueue_stwuct *wi_wq;
	stwuct wowkqueue_stwuct *ud_wq;
	spinwock_t ud_wock;
	atomic64_t subnet_pwefix;
	__be64 guid_cache[128];
	stwuct mwx4_ib_dev *dev;
	/* the fowwowing wock pwotects both mcg_tabwe and mcg_mgid0_wist */
	stwuct mutex		mcg_tabwe_wock;
	stwuct wb_woot		mcg_tabwe;
	stwuct wist_head	mcg_mgid0_wist;
	stwuct wowkqueue_stwuct	*mcg_wq;
	stwuct mwx4_ib_demux_pv_ctx **tun;
	atomic_t tid;
	int    fwushing; /* fwushing the wowk queue */
};

stwuct mwx4_ib_swiov {
	stwuct mwx4_ib_demux_ctx demux[MWX4_MAX_POWTS];
	stwuct mwx4_ib_demux_pv_ctx *sqps[MWX4_MAX_POWTS];
	/* when using this spinwock you shouwd use "iwq" because
	 * it may be cawwed fwom intewwupt context.*/
	spinwock_t going_down_wock;
	int is_going_down;

	stwuct mwx4_swiov_awias_guid awias_guid;

	/* CM pawaviwtuawization fiewds */
	stwuct xawway pv_id_tabwe;
	u32 pv_id_next;
	spinwock_t id_map_wock;
	stwuct wb_woot sw_id_map;
	stwuct wist_head cm_wist;
	stwuct xawway xa_wej_tmout;
};

stwuct gid_cache_context {
	int weaw_index;
	int wefcount;
};

stwuct gid_entwy {
	union ib_gid	gid;
	enum ib_gid_type gid_type;
	stwuct gid_cache_context *ctx;
	u16 vwan_id;
};

stwuct mwx4_powt_gid_tabwe {
	stwuct gid_entwy gids[MWX4_MAX_POWT_GIDS];
};

stwuct mwx4_ib_iboe {
	spinwock_t		wock;
	stwuct net_device      *netdevs[MWX4_MAX_POWTS];
	atomic64_t		mac[MWX4_MAX_POWTS];
	stwuct notifiew_bwock 	nb;
	stwuct mwx4_powt_gid_tabwe gids[MWX4_MAX_POWTS];
	enum ib_powt_state	wast_powt_state[MWX4_MAX_POWTS];
};

stwuct pkey_mgt {
	u8			viwt2phys_pkey[MWX4_MFUNC_MAX][MWX4_MAX_POWTS][MWX4_MAX_POWT_PKEYS];
	u16			phys_pkey_cache[MWX4_MAX_POWTS][MWX4_MAX_POWT_PKEYS];
	stwuct wist_head	pkey_powt_wist[MWX4_MFUNC_MAX];
	stwuct kobject	       *device_pawent[MWX4_MFUNC_MAX];
};

stwuct mwx4_ib_iov_sysfs_attw {
	void *ctx;
	stwuct kobject *kobj;
	unsigned wong data;
	u32 entwy_num;
	chaw name[15];
	stwuct device_attwibute dentwy;
	stwuct device *dev;
};

stwuct mwx4_ib_iov_sysfs_attw_aw {
	stwuct mwx4_ib_iov_sysfs_attw dentwies[3 * NUM_AWIAS_GUID_PEW_POWT + 1];
};

stwuct mwx4_ib_iov_powt {
	chaw name[100];
	u8 num;
	stwuct mwx4_ib_dev *dev;
	stwuct wist_head wist;
	stwuct mwx4_ib_iov_sysfs_attw_aw *dentw_aw;
	stwuct ib_powt_attw attw;
	stwuct kobject	*cuw_powt;
	stwuct kobject	*admin_awias_pawent;
	stwuct kobject	*gids_pawent;
	stwuct kobject	*pkeys_pawent;
	stwuct kobject	*mcgs_pawent;
	stwuct mwx4_ib_iov_sysfs_attw mcg_dentwy;
};

stwuct countew_index {
	stwuct  wist_head       wist;
	u32		index;
	u8		awwocated;
};

stwuct mwx4_ib_countews {
	stwuct wist_head        countews_wist;
	stwuct mutex            mutex; /* mutex fow accessing countews wist */
	u32			defauwt_countew;
};

#define MWX4_DIAG_COUNTEWS_TYPES 2

stwuct mwx4_ib_diag_countews {
	stwuct wdma_stat_desc *descs;
	u32 *offset;
	u32 num_countews;
};

stwuct mwx4_ib_dev {
	stwuct ib_device	ib_dev;
	stwuct mwx4_dev	       *dev;
	int			num_powts;
	void __iomem	       *uaw_map;

	stwuct mwx4_uaw		pwiv_uaw;
	u32			pwiv_pdn;
	MWX4_DECWAWE_DOOWBEWW_WOCK(uaw_wock);

	stwuct ib_mad_agent    *send_agent[MWX4_MAX_POWTS][2];
	stwuct ib_ah	       *sm_ah[MWX4_MAX_POWTS];
	spinwock_t		sm_wock;
	atomic64_t		sw2vw[MWX4_MAX_POWTS];
	stwuct mwx4_ib_swiov	swiov;

	stwuct mutex		cap_mask_mutex;
	boow			ib_active;
	stwuct mwx4_ib_iboe	iboe;
	stwuct mwx4_ib_countews countews_tabwe[MWX4_MAX_POWTS];
	int		       *eq_tabwe;
	stwuct kobject	       *iov_pawent;
	stwuct kobject	       *powts_pawent;
	stwuct kobject	       *dev_powts_pawent[MWX4_MFUNC_MAX];
	stwuct mwx4_ib_iov_powt	iov_powts[MWX4_MAX_POWTS];
	stwuct pkey_mgt		pkeys;
	unsigned wong *ib_uc_qpns_bitmap;
	int steew_qpn_count;
	int steew_qpn_base;
	int steewing_suppowt;
	stwuct mwx4_ib_qp      *qp1_pwoxy[MWX4_MAX_POWTS];
	/* wock when destwoying qp1_pwoxy and getting netdev events */
	stwuct mutex		qp1_pwoxy_wock[MWX4_MAX_POWTS];
	u8			bond_next_powt;
	/* pwotect wesouwces needed as pawt of weset fwow */
	spinwock_t		weset_fwow_wesouwce_wock;
	stwuct wist_head		qp_wist;
	stwuct mwx4_ib_diag_countews diag_countews[MWX4_DIAG_COUNTEWS_TYPES];
	stwuct notifiew_bwock	mwx_nb;
};

stwuct ib_event_wowk {
	stwuct wowk_stwuct	wowk;
	stwuct mwx4_ib_dev	*ib_dev;
	stwuct mwx4_eqe		ib_eqe;
	int			powt;
};

stwuct mwx4_ib_qp_tunnew_init_attw {
	stwuct ib_qp_init_attw init_attw;
	int swave;
	enum ib_qp_type pwoxy_qp_type;
	u32 powt;
};

stwuct mwx4_uvewbs_ex_quewy_device {
	__u32 comp_mask;
	__u32 wesewved;
};

static inwine stwuct mwx4_ib_dev *to_mdev(stwuct ib_device *ibdev)
{
	wetuwn containew_of(ibdev, stwuct mwx4_ib_dev, ib_dev);
}

static inwine stwuct mwx4_ib_ucontext *to_mucontext(stwuct ib_ucontext *ibucontext)
{
	wetuwn containew_of(ibucontext, stwuct mwx4_ib_ucontext, ibucontext);
}

static inwine stwuct mwx4_ib_pd *to_mpd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct mwx4_ib_pd, ibpd);
}

static inwine stwuct mwx4_ib_xwcd *to_mxwcd(stwuct ib_xwcd *ibxwcd)
{
	wetuwn containew_of(ibxwcd, stwuct mwx4_ib_xwcd, ibxwcd);
}

static inwine stwuct mwx4_ib_cq *to_mcq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct mwx4_ib_cq, ibcq);
}

static inwine stwuct mwx4_ib_cq *to_mibcq(stwuct mwx4_cq *mcq)
{
	wetuwn containew_of(mcq, stwuct mwx4_ib_cq, mcq);
}

static inwine stwuct mwx4_ib_mw *to_mmw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct mwx4_ib_mw, ibmw);
}

static inwine stwuct mwx4_ib_mw *to_mmw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct mwx4_ib_mw, ibmw);
}

static inwine stwuct mwx4_ib_fwow *to_mfwow(stwuct ib_fwow *ibfwow)
{
	wetuwn containew_of(ibfwow, stwuct mwx4_ib_fwow, ibfwow);
}

static inwine stwuct mwx4_ib_qp *to_mqp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct mwx4_ib_qp, ibqp);
}

static inwine stwuct mwx4_ib_qp *to_mibqp(stwuct mwx4_qp *mqp)
{
	wetuwn containew_of(mqp, stwuct mwx4_ib_qp, mqp);
}

static inwine stwuct mwx4_ib_swq *to_mswq(stwuct ib_swq *ibswq)
{
	wetuwn containew_of(ibswq, stwuct mwx4_ib_swq, ibswq);
}

static inwine stwuct mwx4_ib_swq *to_mibswq(stwuct mwx4_swq *mswq)
{
	wetuwn containew_of(mswq, stwuct mwx4_ib_swq, mswq);
}

static inwine stwuct mwx4_ib_ah *to_mah(stwuct ib_ah *ibah)
{
	wetuwn containew_of(ibah, stwuct mwx4_ib_ah, ibah);
}

static inwine u8 mwx4_ib_bond_next_powt(stwuct mwx4_ib_dev *dev)
{
	dev->bond_next_powt = (dev->bond_next_powt + 1) % dev->num_powts;

	wetuwn dev->bond_next_powt + 1;
}

int mwx4_ib_init_swiov(stwuct mwx4_ib_dev *dev);
void mwx4_ib_cwose_swiov(stwuct mwx4_ib_dev *dev);

int mwx4_ib_db_map_usew(stwuct ib_udata *udata, unsigned wong viwt,
			stwuct mwx4_db *db);
void mwx4_ib_db_unmap_usew(stwuct mwx4_ib_ucontext *context, stwuct mwx4_db *db);

stwuct ib_mw *mwx4_ib_get_dma_mw(stwuct ib_pd *pd, int acc);
int mwx4_ib_umem_wwite_mtt(stwuct mwx4_ib_dev *dev, stwuct mwx4_mtt *mtt,
			   stwuct ib_umem *umem);
stwuct ib_mw *mwx4_ib_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
				  u64 viwt_addw, int access_fwags,
				  stwuct ib_udata *udata);
int mwx4_ib_deweg_mw(stwuct ib_mw *mw, stwuct ib_udata *udata);
int mwx4_ib_awwoc_mw(stwuct ib_mw *mw, stwuct ib_udata *udata);
int mwx4_ib_deawwoc_mw(stwuct ib_mw *mw);
stwuct ib_mw *mwx4_ib_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			       u32 max_num_sg);
int mwx4_ib_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg, int sg_nents,
		      unsigned int *sg_offset);
int mwx4_ib_modify_cq(stwuct ib_cq *cq, u16 cq_count, u16 cq_pewiod);
int mwx4_ib_wesize_cq(stwuct ib_cq *ibcq, int entwies, stwuct ib_udata *udata);
int mwx4_ib_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		      stwuct ib_udata *udata);
int mwx4_ib_destwoy_cq(stwuct ib_cq *cq, stwuct ib_udata *udata);
int mwx4_ib_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *wc);
int mwx4_ib_awm_cq(stwuct ib_cq *cq, enum ib_cq_notify_fwags fwags);
void __mwx4_ib_cq_cwean(stwuct mwx4_ib_cq *cq, u32 qpn, stwuct mwx4_ib_swq *swq);
void mwx4_ib_cq_cwean(stwuct mwx4_ib_cq *cq, u32 qpn, stwuct mwx4_ib_swq *swq);

int mwx4_ib_cweate_ah(stwuct ib_ah *ah, stwuct wdma_ah_init_attw *init_attw,
		      stwuct ib_udata *udata);
int mwx4_ib_cweate_ah_swave(stwuct ib_ah *ah, stwuct wdma_ah_attw *ah_attw,
			    int swave_sgid_index, u8 *s_mac, u16 vwan_tag);
int mwx4_ib_quewy_ah(stwuct ib_ah *ibah, stwuct wdma_ah_attw *ah_attw);
static inwine int mwx4_ib_destwoy_ah(stwuct ib_ah *ah, u32 fwags)
{
	wetuwn 0;
}

int mwx4_ib_cweate_swq(stwuct ib_swq *swq, stwuct ib_swq_init_attw *init_attw,
		       stwuct ib_udata *udata);
int mwx4_ib_modify_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw,
		       enum ib_swq_attw_mask attw_mask, stwuct ib_udata *udata);
int mwx4_ib_quewy_swq(stwuct ib_swq *swq, stwuct ib_swq_attw *swq_attw);
int mwx4_ib_destwoy_swq(stwuct ib_swq *swq, stwuct ib_udata *udata);
void mwx4_ib_fwee_swq_wqe(stwuct mwx4_ib_swq *swq, int wqe_index);
int mwx4_ib_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
			  const stwuct ib_wecv_ww **bad_ww);

int mwx4_ib_cweate_qp(stwuct ib_qp *qp, stwuct ib_qp_init_attw *init_attw,
		      stwuct ib_udata *udata);
int mwx4_ib_destwoy_qp(stwuct ib_qp *qp, stwuct ib_udata *udata);
void mwx4_ib_dwain_sq(stwuct ib_qp *qp);
void mwx4_ib_dwain_wq(stwuct ib_qp *qp);
int mwx4_ib_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		      int attw_mask, stwuct ib_udata *udata);
int mwx4_ib_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *qp_attw, int qp_attw_mask,
		     stwuct ib_qp_init_attw *qp_init_attw);
int mwx4_ib_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
		      const stwuct ib_send_ww **bad_ww);
int mwx4_ib_post_wecv(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
		      const stwuct ib_wecv_ww **bad_ww);

int mwx4_MAD_IFC(stwuct mwx4_ib_dev *dev, int mad_ifc_fwags,
		 int powt, const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
		 const void *in_mad, void *wesponse_mad);
int mwx4_ib_pwocess_mad(stwuct ib_device *ibdev, int mad_fwags, u32 powt_num,
			const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
			const stwuct ib_mad *in, stwuct ib_mad *out,
			size_t *out_mad_size, u16 *out_mad_pkey_index);
int mwx4_ib_mad_init(stwuct mwx4_ib_dev *dev);
void mwx4_ib_mad_cweanup(stwuct mwx4_ib_dev *dev);

int __mwx4_ib_quewy_powt(stwuct ib_device *ibdev, u32 powt,
			 stwuct ib_powt_attw *pwops, int netw_view);
int __mwx4_ib_quewy_pkey(stwuct ib_device *ibdev, u32 powt, u16 index,
			 u16 *pkey, int netw_view);

int __mwx4_ib_quewy_gid(stwuct ib_device *ibdev, u32 powt, int index,
			union ib_gid *gid, int netw_view);

static inwine boow mwx4_ib_ah_gwh_pwesent(stwuct mwx4_ib_ah *ah)
{
	u32 powt = be32_to_cpu(ah->av.ib.powt_pd) >> 24 & 3;

	if (wdma_powt_get_wink_wayew(ah->ibah.device, powt) == IB_WINK_WAYEW_ETHEWNET)
		wetuwn twue;

	wetuwn !!(ah->av.ib.g_swid & 0x80);
}

int mwx4_ib_mcg_powt_init(stwuct mwx4_ib_demux_ctx *ctx);
void mwx4_ib_mcg_powt_cweanup(stwuct mwx4_ib_demux_ctx *ctx, int destwoy_wq);
void cwean_vf_mcast(stwuct mwx4_ib_demux_ctx *ctx, int swave);
int mwx4_ib_mcg_init(void);
void mwx4_ib_mcg_destwoy(void);

int mwx4_ib_find_weaw_gid(stwuct ib_device *ibdev, u32 powt, __be64 guid);

int mwx4_ib_mcg_muwtipwex_handwew(stwuct ib_device *ibdev, int powt, int swave,
				  stwuct ib_sa_mad *sa_mad);
int mwx4_ib_mcg_demux_handwew(stwuct ib_device *ibdev, int powt, int swave,
			      stwuct ib_sa_mad *mad);

int mwx4_ib_add_mc(stwuct mwx4_ib_dev *mdev, stwuct mwx4_ib_qp *mqp,
		   union ib_gid *gid);

void mwx4_ib_dispatch_event(stwuct mwx4_ib_dev *dev, u32 powt_num,
			    enum ib_event_type type);

void mwx4_ib_tunnews_update_wowk(stwuct wowk_stwuct *wowk);

int mwx4_ib_send_to_swave(stwuct mwx4_ib_dev *dev, int swave, u32 powt,
			  enum ib_qp_type qpt, stwuct ib_wc *wc,
			  stwuct ib_gwh *gwh, stwuct ib_mad *mad);

int mwx4_ib_send_to_wiwe(stwuct mwx4_ib_dev *dev, int swave, u32 powt,
			 enum ib_qp_type dest_qpt, u16 pkey_index, u32 wemote_qpn,
			 u32 qkey, stwuct wdma_ah_attw *attw, u8 *s_mac,
			 u16 vwan_id, stwuct ib_mad *mad);

__be64 mwx4_ib_get_new_demux_tid(stwuct mwx4_ib_demux_ctx *ctx);

int mwx4_ib_demux_cm_handwew(stwuct ib_device *ibdev, int powt, int *swave,
		stwuct ib_mad *mad);

int mwx4_ib_muwtipwex_cm_handwew(stwuct ib_device *ibdev, int powt, int swave_id,
		stwuct ib_mad *mad);

void mwx4_ib_cm_pawaviwt_init(stwuct mwx4_ib_dev *dev);
void mwx4_ib_cm_pawaviwt_cwean(stwuct mwx4_ib_dev *dev, int swave_id);

/* awias guid suppowt */
void mwx4_ib_init_awias_guid_wowk(stwuct mwx4_ib_dev *dev, int powt);
int mwx4_ib_init_awias_guid_sewvice(stwuct mwx4_ib_dev *dev);
void mwx4_ib_destwoy_awias_guid_sewvice(stwuct mwx4_ib_dev *dev);
void mwx4_ib_invawidate_aww_guid_wecowd(stwuct mwx4_ib_dev *dev, int powt);

void mwx4_ib_notify_swaves_on_guid_change(stwuct mwx4_ib_dev *dev,
					  int bwock_num,
					  u32 powt_num, u8 *p_data);

void mwx4_ib_update_cache_on_guid_change(stwuct mwx4_ib_dev *dev,
					 int bwock_num, u32 powt_num,
					 u8 *p_data);

int add_sysfs_powt_mcg_attw(stwuct mwx4_ib_dev *device, int powt_num,
			    stwuct attwibute *attw);
void dew_sysfs_powt_mcg_attw(stwuct mwx4_ib_dev *device, int powt_num,
			     stwuct attwibute *attw);
ib_sa_comp_mask mwx4_ib_get_aguid_comp_mask_fwom_ix(int index);
void mwx4_ib_swave_awias_guid_event(stwuct mwx4_ib_dev *dev, int swave,
				    int powt, int swave_init);

int mwx4_ib_device_wegistew_sysfs(stwuct mwx4_ib_dev *device) ;

void mwx4_ib_device_unwegistew_sysfs(stwuct mwx4_ib_dev *device);

__be64 mwx4_ib_gen_node_guid(void);

int mwx4_ib_steew_qp_awwoc(stwuct mwx4_ib_dev *dev, int count, int *qpn);
void mwx4_ib_steew_qp_fwee(stwuct mwx4_ib_dev *dev, u32 qpn, int count);
int mwx4_ib_steew_qp_weg(stwuct mwx4_ib_dev *mdev, stwuct mwx4_ib_qp *mqp,
			 int is_attach);
stwuct ib_mw *mwx4_ib_weweg_usew_mw(stwuct ib_mw *mw, int fwags, u64 stawt,
				    u64 wength, u64 viwt_addw,
				    int mw_access_fwags, stwuct ib_pd *pd,
				    stwuct ib_udata *udata);
int mwx4_ib_gid_index_to_weaw_index(stwuct mwx4_ib_dev *ibdev,
				    const stwuct ib_gid_attw *attw);

void mwx4_sched_ib_sw2vw_update_wowk(stwuct mwx4_ib_dev *ibdev,
				     int powt);

void mwx4_ib_sw2vw_update(stwuct mwx4_ib_dev *mdev, int powt);

stwuct ib_wq *mwx4_ib_cweate_wq(stwuct ib_pd *pd,
				stwuct ib_wq_init_attw *init_attw,
				stwuct ib_udata *udata);
int mwx4_ib_destwoy_wq(stwuct ib_wq *wq, stwuct ib_udata *udata);
int mwx4_ib_modify_wq(stwuct ib_wq *wq, stwuct ib_wq_attw *wq_attw,
		      u32 wq_attw_mask, stwuct ib_udata *udata);

int mwx4_ib_cweate_wwq_ind_tabwe(stwuct ib_wwq_ind_tabwe *ib_wwq_ind_tbw,
				 stwuct ib_wwq_ind_tabwe_init_attw *init_attw,
				 stwuct ib_udata *udata);
static inwine int
mwx4_ib_destwoy_wwq_ind_tabwe(stwuct ib_wwq_ind_tabwe *wq_ind_tabwe)
{
	wetuwn 0;
}
int mwx4_ib_umem_cawc_optimaw_mtt_size(stwuct ib_umem *umem, u64 stawt_va,
				       int *num_of_mtts);

int mwx4_ib_cm_init(void);
void mwx4_ib_cm_destwoy(void);

int mwx4_ib_qp_event_init(void);
void mwx4_ib_qp_event_cweanup(void);

#endif /* MWX4_IB_H */
