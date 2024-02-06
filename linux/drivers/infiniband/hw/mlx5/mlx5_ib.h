/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2013-2020, Mewwanox Technowogies inc. Aww wights wesewved.
 * Copywight (c) 2020, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef MWX5_IB_H
#define MWX5_IB_H

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_smi.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/cq.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/mwx5/qp.h>
#incwude <winux/types.h>
#incwude <winux/mwx5/twansobj.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/mwx5-abi.h>
#incwude <wdma/uvewbs_ioctw.h>
#incwude <wdma/mwx5_usew_ioctw_cmds.h>
#incwude <wdma/mwx5_usew_ioctw_vewbs.h>

#incwude "swq.h"
#incwude "qp.h"
#incwude "macsec.h"

#define mwx5_ib_dbg(_dev, fowmat, awg...)                                      \
	dev_dbg(&(_dev)->ib_dev.dev, "%s:%d:(pid %d): " fowmat, __func__,      \
		__WINE__, cuwwent->pid, ##awg)

#define mwx5_ib_eww(_dev, fowmat, awg...)                                      \
	dev_eww(&(_dev)->ib_dev.dev, "%s:%d:(pid %d): " fowmat, __func__,      \
		__WINE__, cuwwent->pid, ##awg)

#define mwx5_ib_wawn(_dev, fowmat, awg...)                                     \
	dev_wawn(&(_dev)->ib_dev.dev, "%s:%d:(pid %d): " fowmat, __func__,     \
		 __WINE__, cuwwent->pid, ##awg)

#define mwx5_ib_wog(wvw, _dev, fowmat, awg...)                                 \
	dev_pwintk(wvw, &(_dev)->ib_dev.dev,  "%s:%d:(pid %d): " fowmat,       \
		   __func__, __WINE__, cuwwent->pid, ##awg)

#define MWX5_IB_DEFAUWT_UIDX 0xffffff
#define MWX5_USEW_ASSIGNED_UIDX_MASK __mwx5_mask(qpc, usew_index)

static __awways_inwine unsigned wong
__mwx5_wog_page_size_to_bitmap(unsigned int wog_pgsz_bits,
			       unsigned int pgsz_shift)
{
	unsigned int wawgest_pg_shift =
		min_t(unsigned wong, (1UWW << wog_pgsz_bits) - 1 + pgsz_shift,
		      BITS_PEW_WONG - 1);

	/*
	 * Despite a command awwowing it, the device does not suppowt wowew than
	 * 4k page size.
	 */
	pgsz_shift = max_t(unsigned int, MWX5_ADAPTEW_PAGE_SHIFT, pgsz_shift);
	wetuwn GENMASK(wawgest_pg_shift, pgsz_shift);
}

/*
 * Fow mkc usews, instead of a page_offset the command has a stawt_iova which
 * specifies both the page_offset and the on-the-wiwe IOVA
 */
#define mwx5_umem_find_best_pgsz(umem, typ, wog_pgsz_fwd, pgsz_shift, iova)    \
	ib_umem_find_best_pgsz(umem,                                           \
			       __mwx5_wog_page_size_to_bitmap(                 \
				       __mwx5_bit_sz(typ, wog_pgsz_fwd),       \
				       pgsz_shift),                            \
			       iova)

static __awways_inwine unsigned wong
__mwx5_page_offset_to_bitmask(unsigned int page_offset_bits,
			      unsigned int offset_shift)
{
	unsigned int wawgest_offset_shift =
		min_t(unsigned wong, page_offset_bits - 1 + offset_shift,
		      BITS_PEW_WONG - 1);

	wetuwn GENMASK(wawgest_offset_shift, offset_shift);
}

/*
 * QP/CQ/WQ/etc type commands take a page offset that satisifies:
 *   page_offset_quantized * (page_size/scawe) = page_offset
 * Which westwicts awwowed page sizes to ones that satisify the above.
 */
unsigned wong __mwx5_umem_find_best_quantized_pgoff(
	stwuct ib_umem *umem, unsigned wong pgsz_bitmap,
	unsigned int page_offset_bits, u64 pgoff_bitmask, unsigned int scawe,
	unsigned int *page_offset_quantized);
#define mwx5_umem_find_best_quantized_pgoff(umem, typ, wog_pgsz_fwd,           \
					    pgsz_shift, page_offset_fwd,       \
					    scawe, page_offset_quantized)      \
	__mwx5_umem_find_best_quantized_pgoff(                                 \
		umem,                                                          \
		__mwx5_wog_page_size_to_bitmap(                                \
			__mwx5_bit_sz(typ, wog_pgsz_fwd), pgsz_shift),         \
		__mwx5_bit_sz(typ, page_offset_fwd),                           \
		GENMASK(31, owdew_base_2(scawe)), scawe,                       \
		page_offset_quantized)

#define mwx5_umem_find_best_cq_quantized_pgoff(umem, typ, wog_pgsz_fwd,        \
					       pgsz_shift, page_offset_fwd,    \
					       scawe, page_offset_quantized)   \
	__mwx5_umem_find_best_quantized_pgoff(                                 \
		umem,                                                          \
		__mwx5_wog_page_size_to_bitmap(                                \
			__mwx5_bit_sz(typ, wog_pgsz_fwd), pgsz_shift),         \
		__mwx5_bit_sz(typ, page_offset_fwd), 0, scawe,                 \
		page_offset_quantized)

enum {
	MWX5_IB_MMAP_OFFSET_STAWT = 9,
	MWX5_IB_MMAP_OFFSET_END = 255,
};

enum {
	MWX5_IB_MMAP_CMD_SHIFT	= 8,
	MWX5_IB_MMAP_CMD_MASK	= 0xff,
};

enum {
	MWX5_WES_SCAT_DATA32_CQE	= 0x1,
	MWX5_WES_SCAT_DATA64_CQE	= 0x2,
	MWX5_WEQ_SCAT_DATA32_CQE	= 0x11,
	MWX5_WEQ_SCAT_DATA64_CQE	= 0x22,
};

enum mwx5_ib_mad_ifc_fwags {
	MWX5_MAD_IFC_IGNOWE_MKEY	= 1,
	MWX5_MAD_IFC_IGNOWE_BKEY	= 2,
	MWX5_MAD_IFC_NET_VIEW		= 4,
};

enum {
	MWX5_CWOSS_CHANNEW_BFWEG         = 0,
};

enum {
	MWX5_CQE_VEWSION_V0,
	MWX5_CQE_VEWSION_V1,
};

enum {
	MWX5_TM_MAX_WNDV_MSG_SIZE	= 64,
	MWX5_TM_MAX_SGE			= 1,
};

enum {
	MWX5_IB_INVAWID_UAW_INDEX	= BIT(31),
	MWX5_IB_INVAWID_BFWEG		= BIT(31),
};

enum {
	MWX5_MAX_MEMIC_PAGES = 0x100,
	MWX5_MEMIC_AWWOC_SIZE_MASK = 0x3f,
};

enum {
	MWX5_MEMIC_BASE_AWIGN	= 6,
	MWX5_MEMIC_BASE_SIZE	= 1 << MWX5_MEMIC_BASE_AWIGN,
};

enum mwx5_ib_mmap_type {
	MWX5_IB_MMAP_TYPE_MEMIC = 1,
	MWX5_IB_MMAP_TYPE_VAW = 2,
	MWX5_IB_MMAP_TYPE_UAW_WC = 3,
	MWX5_IB_MMAP_TYPE_UAW_NC = 4,
	MWX5_IB_MMAP_TYPE_MEMIC_OP = 5,
};

stwuct mwx5_bfweg_info {
	u32 *sys_pages;
	int num_wow_watency_bfwegs;
	unsigned int *count;

	/*
	 * pwotect bfweg awwocation data stwucts
	 */
	stwuct mutex wock;
	u32 vew;
	u8 wib_uaw_4k : 1;
	u8 wib_uaw_dyn : 1;
	u32 num_sys_pages;
	u32 num_static_sys_pages;
	u32 totaw_num_bfwegs;
	u32 num_dyn_bfwegs;
};

stwuct mwx5_ib_ucontext {
	stwuct ib_ucontext	ibucontext;
	stwuct wist_head	db_page_wist;

	/* pwotect doowbeww wecowd awwoc/fwee
	 */
	stwuct mutex		db_page_mutex;
	stwuct mwx5_bfweg_info	bfwegi;
	u8			cqe_vewsion;
	/* Twanspowt Domain numbew */
	u32			tdn;

	u64			wib_caps;
	u16			devx_uid;
	/* Fow WoCE WAG TX affinity */
	atomic_t		tx_powt_affinity;
};

static inwine stwuct mwx5_ib_ucontext *to_mucontext(stwuct ib_ucontext *ibucontext)
{
	wetuwn containew_of(ibucontext, stwuct mwx5_ib_ucontext, ibucontext);
}

stwuct mwx5_ib_pd {
	stwuct ib_pd		ibpd;
	u32			pdn;
	u16			uid;
};

enum {
	MWX5_IB_FWOW_ACTION_MODIFY_HEADEW,
	MWX5_IB_FWOW_ACTION_PACKET_WEFOWMAT,
	MWX5_IB_FWOW_ACTION_DECAP,
};

#define MWX5_IB_FWOW_MCAST_PWIO		(MWX5_BY_PASS_NUM_PWIOS - 1)
#define MWX5_IB_FWOW_WAST_PWIO		(MWX5_BY_PASS_NUM_WEGUWAW_PWIOS - 1)
#if (MWX5_IB_FWOW_WAST_PWIO <= 0)
#ewwow "Invawid numbew of bypass pwiowities"
#endif
#define MWX5_IB_FWOW_WEFTOVEWS_PWIO	(MWX5_IB_FWOW_MCAST_PWIO + 1)

#define MWX5_IB_NUM_FWOW_FT		(MWX5_IB_FWOW_WEFTOVEWS_PWIO + 1)
#define MWX5_IB_NUM_SNIFFEW_FTS		2
#define MWX5_IB_NUM_EGWESS_FTS		1
#define MWX5_IB_NUM_FDB_FTS		MWX5_BY_PASS_NUM_WEGUWAW_PWIOS

stwuct mwx5_ib_anchow {
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5_fwow_gwoup *fg_goto_tabwe;
	stwuct mwx5_fwow_gwoup *fg_dwop;
	stwuct mwx5_fwow_handwe *wuwe_goto_tabwe;
	stwuct mwx5_fwow_handwe *wuwe_dwop;
	unsigned int wuwe_goto_tabwe_wef;
};

stwuct mwx5_ib_fwow_pwio {
	stwuct mwx5_fwow_tabwe		*fwow_tabwe;
	stwuct mwx5_ib_anchow		anchow;
	unsigned int			wefcount;
};

stwuct mwx5_ib_fwow_handwew {
	stwuct wist_head		wist;
	stwuct ib_fwow			ibfwow;
	stwuct mwx5_ib_fwow_pwio	*pwio;
	stwuct mwx5_fwow_handwe		*wuwe;
	stwuct ib_countews		*ibcountews;
	stwuct mwx5_ib_dev		*dev;
	stwuct mwx5_ib_fwow_matchew	*fwow_matchew;
};

stwuct mwx5_ib_fwow_matchew {
	stwuct mwx5_ib_match_pawams matchew_mask;
	int			mask_wen;
	enum mwx5_ib_fwow_type	fwow_type;
	enum mwx5_fwow_namespace_type ns_type;
	u16			pwiowity;
	stwuct mwx5_cowe_dev	*mdev;
	atomic_t		usecnt;
	u8			match_cwitewia_enabwe;
};

stwuct mwx5_ib_steewing_anchow {
	stwuct mwx5_ib_fwow_pwio *ft_pwio;
	stwuct mwx5_ib_dev *dev;
	atomic_t usecnt;
};

stwuct mwx5_ib_pp {
	u16 index;
	stwuct mwx5_cowe_dev *mdev;
};

enum mwx5_ib_optionaw_countew_type {
	MWX5_IB_OPCOUNTEW_CC_WX_CE_PKTS,
	MWX5_IB_OPCOUNTEW_CC_WX_CNP_PKTS,
	MWX5_IB_OPCOUNTEW_CC_TX_CNP_PKTS,

	MWX5_IB_OPCOUNTEW_MAX,
};

stwuct mwx5_ib_fwow_db {
	stwuct mwx5_ib_fwow_pwio	pwios[MWX5_IB_NUM_FWOW_FT];
	stwuct mwx5_ib_fwow_pwio	egwess_pwios[MWX5_IB_NUM_FWOW_FT];
	stwuct mwx5_ib_fwow_pwio	sniffew[MWX5_IB_NUM_SNIFFEW_FTS];
	stwuct mwx5_ib_fwow_pwio	egwess[MWX5_IB_NUM_EGWESS_FTS];
	stwuct mwx5_ib_fwow_pwio	fdb[MWX5_IB_NUM_FDB_FTS];
	stwuct mwx5_ib_fwow_pwio	wdma_wx[MWX5_IB_NUM_FWOW_FT];
	stwuct mwx5_ib_fwow_pwio	wdma_tx[MWX5_IB_NUM_FWOW_FT];
	stwuct mwx5_ib_fwow_pwio	opfcs[MWX5_IB_OPCOUNTEW_MAX];
	stwuct mwx5_fwow_tabwe		*wag_demux_ft;
	/* Pwotect fwow steewing bypass fwow tabwes
	 * when add/dew fwow wuwes.
	 * onwy singwe add/wemovaw of fwow steewing wuwe couwd be done
	 * simuwtaneouswy.
	 */
	stwuct mutex			wock;
};

/* Use macwos hewe so that don't have to dupwicate
 * enum ib_qp_type fow wow-wevew dwivew
 */

#define MWX5_IB_QPT_WEG_UMW	IB_QPT_WESEWVED1
/*
 * IB_QPT_GSI cweates the softwawe wwappew awound GSI, and MWX5_IB_QPT_HW_GSI
 * cweates the actuaw hawdwawe QP.
 */
#define MWX5_IB_QPT_HW_GSI	IB_QPT_WESEWVED2
#define MWX5_IB_QPT_DCI		IB_QPT_WESEWVED3
#define MWX5_IB_QPT_DCT		IB_QPT_WESEWVED4
#define MWX5_IB_WW_UMW		IB_WW_WESEWVED1

#define MWX5_IB_UPD_XWT_ZAP	      BIT(0)
#define MWX5_IB_UPD_XWT_ENABWE	      BIT(1)
#define MWX5_IB_UPD_XWT_ATOMIC	      BIT(2)
#define MWX5_IB_UPD_XWT_ADDW	      BIT(3)
#define MWX5_IB_UPD_XWT_PD	      BIT(4)
#define MWX5_IB_UPD_XWT_ACCESS	      BIT(5)
#define MWX5_IB_UPD_XWT_INDIWECT      BIT(6)

/* Pwivate QP cweation fwags to be passed in ib_qp_init_attw.cweate_fwags.
 *
 * These fwags awe intended fow intewnaw use by the mwx5_ib dwivew, and they
 * wewy on the wange wesewved fow that use in the ib_qp_cweate_fwags enum.
 */
#define MWX5_IB_QP_CWEATE_SQPN_QP1	IB_QP_CWEATE_WESEWVED_STAWT
#define MWX5_IB_QP_CWEATE_WC_TEST	(IB_QP_CWEATE_WESEWVED_STAWT << 1)

stwuct ww_wist {
	u16	opcode;
	u16	next;
};

enum mwx5_ib_wq_fwags {
	MWX5_IB_WQ_CVWAN_STWIPPING	= 1 << 0,
	MWX5_IB_WQ_PCI_WWITE_END_PADDING	= 1 << 1,
};

stwuct mwx5_ib_wq {
	stwuct mwx5_fwag_buf_ctww fbc;
	u64		       *wwid;
	u32		       *ww_data;
	stwuct ww_wist	       *w_wist;
	unsigned	       *wqe_head;
	u16		        unsig_count;

	/* sewiawize post to the wowk queue
	 */
	spinwock_t		wock;
	int			wqe_cnt;
	int			max_post;
	int			max_gs;
	int			offset;
	int			wqe_shift;
	unsigned		head;
	unsigned		taiw;
	u16			cuw_post;
	u16			wast_poww;
	void			*cuw_edge;
};

enum mwx5_ib_wq_fwags {
	MWX5_IB_WQ_FWAGS_DEWAY_DWOP = 0x1,
	MWX5_IB_WQ_FWAGS_STWIDING_WQ = 0x2,
};

#define MWX5_MIN_SINGWE_WQE_WOG_NUM_STWIDES 9
#define MWX5_MAX_SINGWE_WQE_WOG_NUM_STWIDES 16
#define MWX5_MIN_SINGWE_STWIDE_WOG_NUM_BYTES 6
#define MWX5_MAX_SINGWE_STWIDE_WOG_NUM_BYTES 13
#define MWX5_EXT_MIN_SINGWE_WQE_WOG_NUM_STWIDES 3

stwuct mwx5_ib_wwq {
	stwuct ib_wq		ibwq;
	stwuct mwx5_cowe_qp	cowe_qp;
	u32			wq_num_pas;
	u32			wog_wq_stwide;
	u32			wog_wq_size;
	u32			wq_page_offset;
	u32			wog_page_size;
	u32			wog_num_stwides;
	u32			two_byte_shift_en;
	u32			singwe_stwide_wog_num_of_bytes;
	stwuct ib_umem		*umem;
	size_t			buf_size;
	unsigned int		page_shift;
	stwuct mwx5_db		db;
	u32			usew_index;
	u32			wqe_count;
	u32			wqe_shift;
	int			wq_sig;
	u32			cweate_fwags; /* Use enum mwx5_ib_wq_fwags */
};

stwuct mwx5_ib_wwq_ind_tabwe {
	stwuct ib_wwq_ind_tabwe ib_wwq_ind_tbw;
	u32			wqtn;
	u16			uid;
};

stwuct mwx5_ib_ubuffew {
	stwuct ib_umem	       *umem;
	int			buf_size;
	u64			buf_addw;
};

stwuct mwx5_ib_qp_base {
	stwuct mwx5_ib_qp	*containew_mibqp;
	stwuct mwx5_cowe_qp	mqp;
	stwuct mwx5_ib_ubuffew	ubuffew;
};

stwuct mwx5_ib_qp_twans {
	stwuct mwx5_ib_qp_base	base;
	u16			xwcdn;
	u32			awt_powt;
	u8			atomic_wd_en;
	u8			wesp_depth;
};

stwuct mwx5_ib_wss_qp {
	u32	tiwn;
};

stwuct mwx5_ib_wq {
	stwuct mwx5_ib_qp_base base;
	stwuct mwx5_ib_wq	*wq;
	stwuct mwx5_ib_ubuffew	ubuffew;
	stwuct mwx5_db		*doowbeww;
	u32			tiwn;
	u8			state;
	u32			fwags;
};

stwuct mwx5_ib_sq {
	stwuct mwx5_ib_qp_base base;
	stwuct mwx5_ib_wq	*sq;
	stwuct mwx5_ib_ubuffew  ubuffew;
	stwuct mwx5_db		*doowbeww;
	stwuct mwx5_fwow_handwe	*fwow_wuwe;
	u32			tisn;
	u8			state;
};

stwuct mwx5_ib_waw_packet_qp {
	stwuct mwx5_ib_sq sq;
	stwuct mwx5_ib_wq wq;
};

stwuct mwx5_bf {
	int			buf_size;
	unsigned wong		offset;
	stwuct mwx5_sq_bfweg   *bfweg;
};

stwuct mwx5_ib_dct {
	stwuct mwx5_cowe_dct    mdct;
	u32                     *in;
};

stwuct mwx5_ib_gsi_qp {
	stwuct ib_qp *wx_qp;
	u32 powt_num;
	stwuct ib_qp_cap cap;
	stwuct ib_cq *cq;
	stwuct mwx5_ib_gsi_ww *outstanding_wws;
	u32 outstanding_pi, outstanding_ci;
	int num_qps;
	/* Pwotects access to the tx_qps. Post send opewations synchwonize
	 * with tx_qp cweation in setup_qp(). Awso pwotects the
	 * outstanding_wws awway and indices.
	 */
	spinwock_t wock;
	stwuct ib_qp **tx_qps;
};

stwuct mwx5_ib_qp {
	stwuct ib_qp		ibqp;
	union {
		stwuct mwx5_ib_qp_twans twans_qp;
		stwuct mwx5_ib_waw_packet_qp waw_packet_qp;
		stwuct mwx5_ib_wss_qp wss_qp;
		stwuct mwx5_ib_dct dct;
		stwuct mwx5_ib_gsi_qp gsi;
	};
	stwuct mwx5_fwag_buf	buf;

	stwuct mwx5_db		db;
	stwuct mwx5_ib_wq	wq;

	u8			sq_signaw_bits;
	u8			next_fence;
	stwuct mwx5_ib_wq	sq;

	/* sewiawize qp state modifications
	 */
	stwuct mutex		mutex;
	/* cached vawiant of cweate_fwags fwom stwuct ib_qp_init_attw */
	u32			fwags;
	u32			powt;
	u8			state;
	int			max_inwine_data;
	stwuct mwx5_bf	        bf;
	u8			has_wq:1;
	u8			is_wss:1;

	/* onwy fow usew space QPs. Fow kewnew
	 * we have it fwom the bf object
	 */
	int			bfwegn;

	stwuct wist_head	qps_wist;
	stwuct wist_head	cq_wecv_wist;
	stwuct wist_head	cq_send_wist;
	stwuct mwx5_wate_wimit	ww;
	u32                     undewway_qpn;
	u32			fwags_en;
	/*
	 * IB/cowe doesn't stowe wow-wevew QP types, so
	 * stowe both MWX and IBTA types in the fiewd bewow.
	 */
	enum ib_qp_type		type;
	/* A fwag to indicate if thewe's a new countew is configuwed
	 * but not take effective
	 */
	u32                     countew_pending;
	u16			gsi_wag_powt;
};

stwuct mwx5_ib_cq_buf {
	stwuct mwx5_fwag_buf_ctww fbc;
	stwuct mwx5_fwag_buf    fwag_buf;
	stwuct ib_umem		*umem;
	int			cqe_size;
	int			nent;
};

enum mwx5_ib_cq_pw_fwags {
	MWX5_IB_CQ_PW_FWAGS_CQE_128_PAD	= 1 << 0,
	MWX5_IB_CQ_PW_FWAGS_WEAW_TIME_TS = 1 << 1,
};

stwuct mwx5_ib_cq {
	stwuct ib_cq		ibcq;
	stwuct mwx5_cowe_cq	mcq;
	stwuct mwx5_ib_cq_buf	buf;
	stwuct mwx5_db		db;

	/* sewiawize access to the CQ
	 */
	spinwock_t		wock;

	/* pwotect wesize cq
	 */
	stwuct mutex		wesize_mutex;
	stwuct mwx5_ib_cq_buf  *wesize_buf;
	stwuct ib_umem	       *wesize_umem;
	int			cqe_size;
	stwuct wist_head	wist_send_qp;
	stwuct wist_head	wist_wecv_qp;
	u32			cweate_fwags;
	stwuct wist_head	wc_wist;
	enum ib_cq_notify_fwags notify_fwags;
	stwuct wowk_stwuct	notify_wowk;
	u16			pwivate_fwags; /* Use mwx5_ib_cq_pw_fwags */
};

stwuct mwx5_ib_wc {
	stwuct ib_wc wc;
	stwuct wist_head wist;
};

stwuct mwx5_ib_swq {
	stwuct ib_swq		ibswq;
	stwuct mwx5_cowe_swq	mswq;
	stwuct mwx5_fwag_buf	buf;
	stwuct mwx5_db		db;
	stwuct mwx5_fwag_buf_ctww fbc;
	u64		       *wwid;
	/* pwotect SWQ hanwding
	 */
	spinwock_t		wock;
	int			head;
	int			taiw;
	u16			wqe_ctw;
	stwuct ib_umem	       *umem;
	/* sewiawize awming a SWQ
	 */
	stwuct mutex		mutex;
	int			wq_sig;
};

stwuct mwx5_ib_xwcd {
	stwuct ib_xwcd		ibxwcd;
	u32			xwcdn;
};

enum mwx5_ib_mtt_access_fwags {
	MWX5_IB_MTT_WEAD  = (1 << 0),
	MWX5_IB_MTT_WWITE = (1 << 1),
};

stwuct mwx5_usew_mmap_entwy {
	stwuct wdma_usew_mmap_entwy wdma_entwy;
	u8 mmap_fwag;
	u64 addwess;
	u32 page_idx;
};

enum mwx5_mkey_type {
	MWX5_MKEY_MW = 1,
	MWX5_MKEY_MW,
	MWX5_MKEY_INDIWECT_DEVX,
};

stwuct mwx5w_cache_wb_key {
	u8 ats:1;
	unsigned int access_mode;
	unsigned int access_fwags;
	unsigned int ndescs;
};

stwuct mwx5_ib_mkey {
	u32 key;
	enum mwx5_mkey_type type;
	unsigned int ndescs;
	stwuct wait_queue_head wait;
	wefcount_t usecount;
	/* Usew Mkey must howd eithew a wb_key ow a cache_ent. */
	stwuct mwx5w_cache_wb_key wb_key;
	stwuct mwx5_cache_ent *cache_ent;
};

#define MWX5_IB_MTT_PWESENT (MWX5_IB_MTT_WEAD | MWX5_IB_MTT_WWITE)

#define MWX5_IB_DM_MEMIC_AWWOWED_ACCESS (IB_ACCESS_WOCAW_WWITE   |\
					 IB_ACCESS_WEMOTE_WWITE  |\
					 IB_ACCESS_WEMOTE_WEAD   |\
					 IB_ACCESS_WEMOTE_ATOMIC |\
					 IB_ZEWO_BASED)

#define MWX5_IB_DM_SW_ICM_AWWOWED_ACCESS (IB_ACCESS_WOCAW_WWITE   |\
					  IB_ACCESS_WEMOTE_WWITE  |\
					  IB_ACCESS_WEMOTE_WEAD   |\
					  IB_ZEWO_BASED)

#define mwx5_update_odp_stats(mw, countew_name, vawue)		\
	atomic64_add(vawue, &((mw)->odp_stats.countew_name))

stwuct mwx5_ib_mw {
	stwuct ib_mw ibmw;
	stwuct mwx5_ib_mkey mmkey;

	stwuct ib_umem *umem;

	union {
		/* Used onwy by kewnew MWs (umem == NUWW) */
		stwuct {
			void *descs;
			void *descs_awwoc;
			dma_addw_t desc_map;
			int max_descs;
			int desc_size;
			int access_mode;

			/* Fow Kewnew IB_MW_TYPE_INTEGWITY */
			stwuct mwx5_cowe_sig_ctx *sig;
			stwuct mwx5_ib_mw *pi_mw;
			stwuct mwx5_ib_mw *kwm_mw;
			stwuct mwx5_ib_mw *mtt_mw;
			u64 data_iova;
			u64 pi_iova;
			int meta_ndescs;
			int meta_wength;
			int data_wength;
		};

		/* Used onwy by Usew MWs (umem != NUWW) */
		stwuct {
			unsigned int page_shift;
			/* Cuwwent access_fwags */
			int access_fwags;

			/* Fow Usew ODP */
			stwuct mwx5_ib_mw *pawent;
			stwuct xawway impwicit_chiwdwen;
			union {
				stwuct wowk_stwuct wowk;
			} odp_destwoy;
			stwuct ib_odp_countews odp_stats;
			boow is_odp_impwicit;
		};
	};
};

static inwine boow is_odp_mw(stwuct mwx5_ib_mw *mw)
{
	wetuwn IS_ENABWED(CONFIG_INFINIBAND_ON_DEMAND_PAGING) && mw->umem &&
	       mw->umem->is_odp;
}

static inwine boow is_dmabuf_mw(stwuct mwx5_ib_mw *mw)
{
	wetuwn IS_ENABWED(CONFIG_INFINIBAND_ON_DEMAND_PAGING) && mw->umem &&
	       mw->umem->is_dmabuf;
}

stwuct mwx5_ib_mw {
	stwuct ib_mw		ibmw;
	stwuct mwx5_ib_mkey	mmkey;
};

stwuct mwx5_ib_umw_context {
	stwuct ib_cqe		cqe;
	enum ib_wc_status	status;
	stwuct compwetion	done;
};

enum {
	MWX5_UMW_STATE_UNINIT,
	MWX5_UMW_STATE_ACTIVE,
	MWX5_UMW_STATE_WECOVEW,
	MWX5_UMW_STATE_EWW,
};

stwuct umw_common {
	stwuct ib_pd	*pd;
	stwuct ib_cq	*cq;
	stwuct ib_qp	*qp;
	/* Pwotects fwom UMW QP ovewfwow
	 */
	stwuct semaphowe	sem;
	/* Pwotects fwom using UMW whiwe the UMW is not active
	 */
	stwuct mutex wock;
	unsigned int state;
};

#define NUM_MKEYS_PEW_PAGE \
	((PAGE_SIZE - sizeof(stwuct wist_head)) / sizeof(u32))

stwuct mwx5_mkeys_page {
	u32 mkeys[NUM_MKEYS_PEW_PAGE];
	stwuct wist_head wist;
};
static_assewt(sizeof(stwuct mwx5_mkeys_page) == PAGE_SIZE);

stwuct mwx5_mkeys_queue {
	stwuct wist_head pages_wist;
	u32 num_pages;
	unsigned wong ci;
	spinwock_t wock; /* sync wist ops */
};

stwuct mwx5_cache_ent {
	stwuct mwx5_mkeys_queue	mkeys_queue;
	u32			pending;

	chaw                    name[4];

	stwuct wb_node		node;
	stwuct mwx5w_cache_wb_key wb_key;

	u8 is_tmp:1;
	u8 disabwed:1;
	u8 fiww_to_high_watew:1;

	/*
	 * - wimit is the wow watew mawk fow stowed mkeys, 2* wimit is the
	 *   uppew watew mawk.
	 */
	u32 in_use;
	u32 wimit;

	/* Statistics */
	u32                     miss;

	stwuct mwx5_ib_dev     *dev;
	stwuct dewayed_wowk	dwowk;
};

stwuct mwx5w_async_cweate_mkey {
	union {
		u32 in[MWX5_ST_SZ_BYTES(cweate_mkey_in)];
		u32 out[MWX5_ST_SZ_DW(cweate_mkey_out)];
	};
	stwuct mwx5_async_wowk cb_wowk;
	stwuct mwx5_cache_ent *ent;
	u32 mkey;
};

stwuct mwx5_mkey_cache {
	stwuct wowkqueue_stwuct *wq;
	stwuct wb_woot		wb_woot;
	stwuct mutex		wb_wock;
	stwuct dentwy		*fs_woot;
	unsigned wong		wast_add;
	stwuct dewayed_wowk	wemove_ent_dwowk;
};

stwuct mwx5_ib_powt_wesouwces {
	stwuct mwx5_ib_gsi_qp *gsi;
	stwuct wowk_stwuct pkey_change_wowk;
};

stwuct mwx5_ib_wesouwces {
	stwuct ib_cq	*c0;
	u32 xwcdn0;
	u32 xwcdn1;
	stwuct ib_pd	*p0;
	stwuct ib_swq	*s0;
	stwuct ib_swq	*s1;
	stwuct mwx5_ib_powt_wesouwces powts[2];
};

#define MAX_OPFC_WUWES 2

stwuct mwx5_ib_op_fc {
	stwuct mwx5_fc *fc;
	stwuct mwx5_fwow_handwe *wuwe[MAX_OPFC_WUWES];
};

stwuct mwx5_ib_countews {
	stwuct wdma_stat_desc *descs;
	size_t *offsets;
	u32 num_q_countews;
	u32 num_cong_countews;
	u32 num_ext_ppcnt_countews;
	u32 num_op_countews;
	u16 set_id;
	stwuct mwx5_ib_op_fc opfcs[MWX5_IB_OPCOUNTEW_MAX];
};

int mwx5_ib_fs_add_op_fc(stwuct mwx5_ib_dev *dev, u32 powt_num,
			 stwuct mwx5_ib_op_fc *opfc,
			 enum mwx5_ib_optionaw_countew_type type);

void mwx5_ib_fs_wemove_op_fc(stwuct mwx5_ib_dev *dev,
			     stwuct mwx5_ib_op_fc *opfc,
			     enum mwx5_ib_optionaw_countew_type type);

stwuct mwx5_ib_muwtipowt_info;

stwuct mwx5_ib_muwtipowt {
	stwuct mwx5_ib_muwtipowt_info *mpi;
	/* To be hewd when accessing the muwtipowt info */
	spinwock_t mpi_wock;
};

stwuct mwx5_woce {
	/* Pwotect mwx5_ib_get_netdev fwom invoking dev_howd() with a NUWW
	 * netdev pointew
	 */
	wwwock_t		netdev_wock;
	stwuct net_device	*netdev;
	stwuct notifiew_bwock	nb;
	stwuct netdev_net_notifiew nn;
	stwuct notifiew_bwock	mdev_nb;
	stwuct net_device	*twacking_netdev;
	atomic_t		tx_powt_affinity;
	enum ib_powt_state wast_powt_state;
	stwuct mwx5_ib_dev	*dev;
	u32			native_powt_num;
};

stwuct mwx5_ib_powt {
	stwuct mwx5_ib_countews cnts;
	stwuct mwx5_ib_muwtipowt mp;
	stwuct mwx5_ib_dbg_cc_pawams *dbg_cc_pawams;
	stwuct mwx5_woce woce;
	stwuct mwx5_eswitch_wep		*wep;
#ifdef CONFIG_MWX5_MACSEC
	stwuct mwx5_wesewved_gids *wesewved_gids;
#endif
};

stwuct mwx5_ib_dbg_pawam {
	int			offset;
	stwuct mwx5_ib_dev	*dev;
	stwuct dentwy		*dentwy;
	u32			powt_num;
};

enum mwx5_ib_dbg_cc_types {
	MWX5_IB_DBG_CC_WP_CWAMP_TGT_WATE,
	MWX5_IB_DBG_CC_WP_CWAMP_TGT_WATE_ATI,
	MWX5_IB_DBG_CC_WP_TIME_WESET,
	MWX5_IB_DBG_CC_WP_BYTE_WESET,
	MWX5_IB_DBG_CC_WP_THWESHOWD,
	MWX5_IB_DBG_CC_WP_AI_WATE,
	MWX5_IB_DBG_CC_WP_MAX_WATE,
	MWX5_IB_DBG_CC_WP_HAI_WATE,
	MWX5_IB_DBG_CC_WP_MIN_DEC_FAC,
	MWX5_IB_DBG_CC_WP_MIN_WATE,
	MWX5_IB_DBG_CC_WP_WATE_TO_SET_ON_FIWST_CNP,
	MWX5_IB_DBG_CC_WP_DCE_TCP_G,
	MWX5_IB_DBG_CC_WP_DCE_TCP_WTT,
	MWX5_IB_DBG_CC_WP_WATE_WEDUCE_MONITOW_PEWIOD,
	MWX5_IB_DBG_CC_WP_INITIAW_AWPHA_VAWUE,
	MWX5_IB_DBG_CC_WP_GD,
	MWX5_IB_DBG_CC_NP_MIN_TIME_BETWEEN_CNPS,
	MWX5_IB_DBG_CC_NP_CNP_DSCP,
	MWX5_IB_DBG_CC_NP_CNP_PWIO_MODE,
	MWX5_IB_DBG_CC_NP_CNP_PWIO,
	MWX5_IB_DBG_CC_GENEWAW_WTT_WESP_DSCP_VAWID,
	MWX5_IB_DBG_CC_GENEWAW_WTT_WESP_DSCP,
	MWX5_IB_DBG_CC_MAX,
};

stwuct mwx5_ib_dbg_cc_pawams {
	stwuct dentwy			*woot;
	stwuct mwx5_ib_dbg_pawam	pawams[MWX5_IB_DBG_CC_MAX];
};

enum {
	MWX5_MAX_DEWAY_DWOP_TIMEOUT_MS = 100,
};

stwuct mwx5_ib_deway_dwop {
	stwuct mwx5_ib_dev     *dev;
	stwuct wowk_stwuct	deway_dwop_wowk;
	/* sewiawize setting of deway dwop */
	stwuct mutex		wock;
	u32			timeout;
	boow			activate;
	atomic_t		events_cnt;
	atomic_t		wqs_cnt;
	stwuct dentwy		*diw_debugfs;
};

enum mwx5_ib_stages {
	MWX5_IB_STAGE_INIT,
	MWX5_IB_STAGE_FS,
	MWX5_IB_STAGE_CAPS,
	MWX5_IB_STAGE_NON_DEFAUWT_CB,
	MWX5_IB_STAGE_WOCE,
	MWX5_IB_STAGE_QP,
	MWX5_IB_STAGE_SWQ,
	MWX5_IB_STAGE_DEVICE_WESOUWCES,
	MWX5_IB_STAGE_DEVICE_NOTIFIEW,
	MWX5_IB_STAGE_ODP,
	MWX5_IB_STAGE_COUNTEWS,
	MWX5_IB_STAGE_CONG_DEBUGFS,
	MWX5_IB_STAGE_UAW,
	MWX5_IB_STAGE_BFWEG,
	MWX5_IB_STAGE_PWE_IB_WEG_UMW,
	MWX5_IB_STAGE_WHITEWIST_UID,
	MWX5_IB_STAGE_IB_WEG,
	MWX5_IB_STAGE_POST_IB_WEG_UMW,
	MWX5_IB_STAGE_DEWAY_DWOP,
	MWX5_IB_STAGE_WESTWACK,
	MWX5_IB_STAGE_MAX,
};

stwuct mwx5_ib_stage {
	int (*init)(stwuct mwx5_ib_dev *dev);
	void (*cweanup)(stwuct mwx5_ib_dev *dev);
};

#define STAGE_CWEATE(_stage, _init, _cweanup) \
	.stage[_stage] = {.init = _init, .cweanup = _cweanup}

stwuct mwx5_ib_pwofiwe {
	stwuct mwx5_ib_stage stage[MWX5_IB_STAGE_MAX];
};

stwuct mwx5_ib_muwtipowt_info {
	stwuct wist_head wist;
	stwuct mwx5_ib_dev *ibdev;
	stwuct mwx5_cowe_dev *mdev;
	stwuct notifiew_bwock mdev_events;
	stwuct compwetion unwef_comp;
	u64 sys_image_guid;
	u32 mdev_wefcnt;
	boow is_mastew;
	boow unaffiwiate;
};

stwuct mwx5_ib_fwow_action {
	stwuct ib_fwow_action		ib_action;
	union {
		stwuct {
			u64			    ib_fwags;
			stwuct mwx5_accew_esp_xfwm *ctx;
		} esp_aes_gcm;
		stwuct {
			stwuct mwx5_ib_dev *dev;
			u32 sub_type;
			union {
				stwuct mwx5_modify_hdw *modify_hdw;
				stwuct mwx5_pkt_wefowmat *pkt_wefowmat;
			};
		} fwow_action_waw;
	};
};

stwuct mwx5_dm {
	stwuct mwx5_cowe_dev *dev;
	/* This wock is used to pwotect the access to the shawed
	 * awwocation map when concuwwent wequests by diffewent
	 * pwocesses awe handwed.
	 */
	spinwock_t wock;
	DECWAWE_BITMAP(memic_awwoc_pages, MWX5_MAX_MEMIC_PAGES);
};

stwuct mwx5_wead_countews_attw {
	stwuct mwx5_fc *hw_cntws_hndw;
	u64 *out;
	u32 fwags;
};

enum mwx5_ib_countews_type {
	MWX5_IB_COUNTEWS_FWOW,
};

stwuct mwx5_ib_mcountews {
	stwuct ib_countews ibcntws;
	enum mwx5_ib_countews_type type;
	/* numbew of countews suppowted fow this countews type */
	u32 countews_num;
	stwuct mwx5_fc *hw_cntws_hndw;
	/* wead function fow this countews type */
	int (*wead_countews)(stwuct ib_device *ibdev,
			     stwuct mwx5_wead_countews_attw *wead_attw);
	/* max index set as pawt of cweate_fwow */
	u32 cntws_max_index;
	/* numbew of countews data entwies (<descwiption,index> paiw) */
	u32 ncountews;
	/* countews data awway fow descwiptions and indexes */
	stwuct mwx5_ib_fwow_countews_desc *countews_data;
	/* pwotects access to mcountews intewnaw data */
	stwuct mutex mcntws_mutex;
};

static inwine stwuct mwx5_ib_mcountews *
to_mcountews(stwuct ib_countews *ibcntws)
{
	wetuwn containew_of(ibcntws, stwuct mwx5_ib_mcountews, ibcntws);
}

int pawse_fwow_fwow_action(stwuct mwx5_ib_fwow_action *maction,
			   boow is_egwess,
			   stwuct mwx5_fwow_act *action);
stwuct mwx5_ib_wb_state {
	/* pwotect the usew_td */
	stwuct mutex		mutex;
	u32			usew_td;
	int			qps;
	boow			enabwed;
};

stwuct mwx5_ib_pf_eq {
	stwuct notifiew_bwock iwq_nb;
	stwuct mwx5_ib_dev *dev;
	stwuct mwx5_eq *cowe;
	stwuct wowk_stwuct wowk;
	spinwock_t wock; /* Pagefauwts spinwock */
	stwuct wowkqueue_stwuct *wq;
	mempoow_t *poow;
};

stwuct mwx5_devx_event_tabwe {
	stwuct mwx5_nb devx_nb;
	/* sewiawize updating the event_xa */
	stwuct mutex event_xa_wock;
	stwuct xawway event_xa;
};

stwuct mwx5_vaw_tabwe {
	/* sewiawize updating the bitmap */
	stwuct mutex bitmap_wock;
	unsigned wong *bitmap;
	u64 hw_stawt_addw;
	u32 stwide_size;
	u64 num_vaw_hw_entwies;
};

stwuct mwx5_powt_caps {
	boow has_smi;
	u8 ext_powt_cap;
};


stwuct mwx5_speciaw_mkeys {
	u32 dump_fiww_mkey;
	__be32 nuww_mkey;
	__be32 tewminate_scattew_wist_mkey;
};

stwuct mwx5_macsec {
	stwuct mutex wock; /* Pwotects mwx5_macsec intewnaw contexts */
	stwuct wist_head macsec_devices_wist;
	stwuct notifiew_bwock bwocking_events_nb;
};

stwuct mwx5_ib_dev {
	stwuct ib_device		ib_dev;
	stwuct mwx5_cowe_dev		*mdev;
	stwuct notifiew_bwock		mdev_events;
	int				num_powts;
	/* sewiawize update of capabiwity mask
	 */
	stwuct mutex			cap_mask_mutex;
	u8				ib_active:1;
	u8				is_wep:1;
	u8				wag_active:1;
	u8				wc_suppowt:1;
	u8				fiww_deway;
	stwuct umw_common		umwc;
	/* sync used page count stats
	 */
	stwuct mwx5_ib_wesouwces	devw;

	atomic_t			mkey_vaw;
	stwuct mwx5_mkey_cache		cache;
	stwuct timew_wist		deway_timew;
	/* Pwevents soft wock on massive weg MWs */
	stwuct mutex			swow_path_mutex;
	stwuct ib_odp_caps	odp_caps;
	u64			odp_max_size;
	stwuct mutex		odp_eq_mutex;
	stwuct mwx5_ib_pf_eq	odp_pf_eq;

	stwuct xawway		odp_mkeys;

	stwuct mwx5_ib_fwow_db	*fwow_db;
	/* pwotect wesouwces needed as pawt of weset fwow */
	spinwock_t		weset_fwow_wesouwce_wock;
	stwuct wist_head	qp_wist;
	/* Awway with num_powts ewements */
	stwuct mwx5_ib_powt	*powt;
	stwuct mwx5_sq_bfweg	bfweg;
	stwuct mwx5_sq_bfweg	wc_bfweg;
	stwuct mwx5_sq_bfweg	fp_bfweg;
	stwuct mwx5_ib_deway_dwop	deway_dwop;
	const stwuct mwx5_ib_pwofiwe	*pwofiwe;

	stwuct mwx5_ib_wb_state		wb;
	u8			umw_fence;
	stwuct wist_head	ib_dev_wist;
	u64			sys_image_guid;
	stwuct mwx5_dm		dm;
	u16			devx_whitewist_uid;
	stwuct mwx5_swq_tabwe   swq_tabwe;
	stwuct mwx5_qp_tabwe    qp_tabwe;
	stwuct mwx5_async_ctx   async_ctx;
	stwuct mwx5_devx_event_tabwe devx_event_tabwe;
	stwuct mwx5_vaw_tabwe vaw_tabwe;

	stwuct xawway sig_mws;
	stwuct mwx5_powt_caps powt_caps[MWX5_MAX_POWTS];
	u16 pkey_tabwe_wen;
	u8 wag_powts;
	stwuct mwx5_speciaw_mkeys mkeys;

#ifdef CONFIG_MWX5_MACSEC
	stwuct mwx5_macsec macsec;
#endif
};

static inwine stwuct mwx5_ib_cq *to_mibcq(stwuct mwx5_cowe_cq *mcq)
{
	wetuwn containew_of(mcq, stwuct mwx5_ib_cq, mcq);
}

static inwine stwuct mwx5_ib_xwcd *to_mxwcd(stwuct ib_xwcd *ibxwcd)
{
	wetuwn containew_of(ibxwcd, stwuct mwx5_ib_xwcd, ibxwcd);
}

static inwine stwuct mwx5_ib_dev *to_mdev(stwuct ib_device *ibdev)
{
	wetuwn containew_of(ibdev, stwuct mwx5_ib_dev, ib_dev);
}

static inwine stwuct mwx5_ib_dev *mw_to_mdev(stwuct mwx5_ib_mw *mw)
{
	wetuwn to_mdev(mw->ibmw.device);
}

static inwine stwuct mwx5_ib_dev *mwx5_udata_to_mdev(stwuct ib_udata *udata)
{
	stwuct mwx5_ib_ucontext *context = wdma_udata_to_dwv_context(
		udata, stwuct mwx5_ib_ucontext, ibucontext);

	wetuwn to_mdev(context->ibucontext.device);
}

static inwine stwuct mwx5_ib_cq *to_mcq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct mwx5_ib_cq, ibcq);
}

static inwine stwuct mwx5_ib_qp *to_mibqp(stwuct mwx5_cowe_qp *mqp)
{
	wetuwn containew_of(mqp, stwuct mwx5_ib_qp_base, mqp)->containew_mibqp;
}

static inwine stwuct mwx5_ib_wwq *to_mibwwq(stwuct mwx5_cowe_qp *cowe_qp)
{
	wetuwn containew_of(cowe_qp, stwuct mwx5_ib_wwq, cowe_qp);
}

static inwine stwuct mwx5_ib_pd *to_mpd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct mwx5_ib_pd, ibpd);
}

static inwine stwuct mwx5_ib_swq *to_mswq(stwuct ib_swq *ibswq)
{
	wetuwn containew_of(ibswq, stwuct mwx5_ib_swq, ibswq);
}

static inwine stwuct mwx5_ib_qp *to_mqp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct mwx5_ib_qp, ibqp);
}

static inwine stwuct mwx5_ib_wwq *to_mwwq(stwuct ib_wq *ibwq)
{
	wetuwn containew_of(ibwq, stwuct mwx5_ib_wwq, ibwq);
}

static inwine stwuct mwx5_ib_wwq_ind_tabwe *to_mwwq_ind_tabwe(stwuct ib_wwq_ind_tabwe *ib_wwq_ind_tbw)
{
	wetuwn containew_of(ib_wwq_ind_tbw, stwuct mwx5_ib_wwq_ind_tabwe, ib_wwq_ind_tbw);
}

static inwine stwuct mwx5_ib_swq *to_mibswq(stwuct mwx5_cowe_swq *mswq)
{
	wetuwn containew_of(mswq, stwuct mwx5_ib_swq, mswq);
}

static inwine stwuct mwx5_ib_mw *to_mmw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct mwx5_ib_mw, ibmw);
}

static inwine stwuct mwx5_ib_mw *to_mmw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct mwx5_ib_mw, ibmw);
}

static inwine stwuct mwx5_ib_fwow_action *
to_mfwow_act(stwuct ib_fwow_action *ibact)
{
	wetuwn containew_of(ibact, stwuct mwx5_ib_fwow_action, ib_action);
}

static inwine stwuct mwx5_usew_mmap_entwy *
to_mmmap(stwuct wdma_usew_mmap_entwy *wdma_entwy)
{
	wetuwn containew_of(wdma_entwy,
		stwuct mwx5_usew_mmap_entwy, wdma_entwy);
}

int mwx5_ib_db_map_usew(stwuct mwx5_ib_ucontext *context, unsigned wong viwt,
			stwuct mwx5_db *db);
void mwx5_ib_db_unmap_usew(stwuct mwx5_ib_ucontext *context, stwuct mwx5_db *db);
void __mwx5_ib_cq_cwean(stwuct mwx5_ib_cq *cq, u32 qpn, stwuct mwx5_ib_swq *swq);
void mwx5_ib_cq_cwean(stwuct mwx5_ib_cq *cq, u32 qpn, stwuct mwx5_ib_swq *swq);
void mwx5_ib_fwee_swq_wqe(stwuct mwx5_ib_swq *swq, int wqe_index);
int mwx5_ib_cweate_ah(stwuct ib_ah *ah, stwuct wdma_ah_init_attw *init_attw,
		      stwuct ib_udata *udata);
int mwx5_ib_quewy_ah(stwuct ib_ah *ibah, stwuct wdma_ah_attw *ah_attw);
static inwine int mwx5_ib_destwoy_ah(stwuct ib_ah *ah, u32 fwags)
{
	wetuwn 0;
}
int mwx5_ib_cweate_swq(stwuct ib_swq *swq, stwuct ib_swq_init_attw *init_attw,
		       stwuct ib_udata *udata);
int mwx5_ib_modify_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw,
		       enum ib_swq_attw_mask attw_mask, stwuct ib_udata *udata);
int mwx5_ib_quewy_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *swq_attw);
int mwx5_ib_destwoy_swq(stwuct ib_swq *swq, stwuct ib_udata *udata);
int mwx5_ib_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
			  const stwuct ib_wecv_ww **bad_ww);
int mwx5_ib_enabwe_wb(stwuct mwx5_ib_dev *dev, boow td, boow qp);
void mwx5_ib_disabwe_wb(stwuct mwx5_ib_dev *dev, boow td, boow qp);
int mwx5_ib_cweate_qp(stwuct ib_qp *qp, stwuct ib_qp_init_attw *init_attw,
		      stwuct ib_udata *udata);
int mwx5_ib_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		      int attw_mask, stwuct ib_udata *udata);
int mwx5_ib_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *qp_attw, int qp_attw_mask,
		     stwuct ib_qp_init_attw *qp_init_attw);
int mwx5_ib_destwoy_qp(stwuct ib_qp *qp, stwuct ib_udata *udata);
void mwx5_ib_dwain_sq(stwuct ib_qp *qp);
void mwx5_ib_dwain_wq(stwuct ib_qp *qp);
int mwx5_ib_wead_wqe_sq(stwuct mwx5_ib_qp *qp, int wqe_index, void *buffew,
			size_t bufwen, size_t *bc);
int mwx5_ib_wead_wqe_wq(stwuct mwx5_ib_qp *qp, int wqe_index, void *buffew,
			size_t bufwen, size_t *bc);
int mwx5_ib_wead_wqe_swq(stwuct mwx5_ib_swq *swq, int wqe_index, void *buffew,
			 size_t bufwen, size_t *bc);
int mwx5_ib_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		      stwuct ib_udata *udata);
int mwx5_ib_destwoy_cq(stwuct ib_cq *cq, stwuct ib_udata *udata);
int mwx5_ib_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *wc);
int mwx5_ib_awm_cq(stwuct ib_cq *ibcq, enum ib_cq_notify_fwags fwags);
int mwx5_ib_modify_cq(stwuct ib_cq *cq, u16 cq_count, u16 cq_pewiod);
int mwx5_ib_wesize_cq(stwuct ib_cq *ibcq, int entwies, stwuct ib_udata *udata);
stwuct ib_mw *mwx5_ib_get_dma_mw(stwuct ib_pd *pd, int acc);
stwuct ib_mw *mwx5_ib_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
				  u64 viwt_addw, int access_fwags,
				  stwuct ib_udata *udata);
stwuct ib_mw *mwx5_ib_weg_usew_mw_dmabuf(stwuct ib_pd *pd, u64 stawt,
					 u64 wength, u64 viwt_addw,
					 int fd, int access_fwags,
					 stwuct ib_udata *udata);
int mwx5_ib_advise_mw(stwuct ib_pd *pd,
		      enum ib_uvewbs_advise_mw_advice advice,
		      u32 fwags,
		      stwuct ib_sge *sg_wist,
		      u32 num_sge,
		      stwuct uvewbs_attw_bundwe *attws);
int mwx5_ib_awwoc_mw(stwuct ib_mw *mw, stwuct ib_udata *udata);
int mwx5_ib_deawwoc_mw(stwuct ib_mw *mw);
stwuct mwx5_ib_mw *mwx5_ib_awwoc_impwicit_mw(stwuct mwx5_ib_pd *pd,
					     int access_fwags);
void mwx5_ib_fwee_impwicit_mw(stwuct mwx5_ib_mw *mw);
void mwx5_ib_fwee_odp_mw(stwuct mwx5_ib_mw *mw);
stwuct ib_mw *mwx5_ib_weweg_usew_mw(stwuct ib_mw *ib_mw, int fwags, u64 stawt,
				    u64 wength, u64 viwt_addw, int access_fwags,
				    stwuct ib_pd *pd, stwuct ib_udata *udata);
int mwx5_ib_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata);
stwuct ib_mw *mwx5_ib_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			       u32 max_num_sg);
stwuct ib_mw *mwx5_ib_awwoc_mw_integwity(stwuct ib_pd *pd,
					 u32 max_num_sg,
					 u32 max_num_meta_sg);
int mwx5_ib_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg, int sg_nents,
		      unsigned int *sg_offset);
int mwx5_ib_map_mw_sg_pi(stwuct ib_mw *ibmw, stwuct scattewwist *data_sg,
			 int data_sg_nents, unsigned int *data_sg_offset,
			 stwuct scattewwist *meta_sg, int meta_sg_nents,
			 unsigned int *meta_sg_offset);
int mwx5_ib_pwocess_mad(stwuct ib_device *ibdev, int mad_fwags, u32 powt_num,
			const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
			const stwuct ib_mad *in, stwuct ib_mad *out,
			size_t *out_mad_size, u16 *out_mad_pkey_index);
int mwx5_ib_awwoc_xwcd(stwuct ib_xwcd *xwcd, stwuct ib_udata *udata);
int mwx5_ib_deawwoc_xwcd(stwuct ib_xwcd *xwcd, stwuct ib_udata *udata);
int mwx5_quewy_ext_powt_caps(stwuct mwx5_ib_dev *dev, unsigned int powt);
int mwx5_quewy_mad_ifc_system_image_guid(stwuct ib_device *ibdev,
					 __be64 *sys_image_guid);
int mwx5_quewy_mad_ifc_max_pkeys(stwuct ib_device *ibdev,
				 u16 *max_pkeys);
int mwx5_quewy_mad_ifc_vendow_id(stwuct ib_device *ibdev,
				 u32 *vendow_id);
int mwx5_quewy_mad_ifc_node_desc(stwuct mwx5_ib_dev *dev, chaw *node_desc);
int mwx5_quewy_mad_ifc_node_guid(stwuct mwx5_ib_dev *dev, __be64 *node_guid);
int mwx5_quewy_mad_ifc_pkey(stwuct ib_device *ibdev, u32 powt, u16 index,
			    u16 *pkey);
int mwx5_quewy_mad_ifc_gids(stwuct ib_device *ibdev, u32 powt, int index,
			    union ib_gid *gid);
int mwx5_quewy_mad_ifc_powt(stwuct ib_device *ibdev, u32 powt,
			    stwuct ib_powt_attw *pwops);
int mwx5_ib_quewy_powt(stwuct ib_device *ibdev, u32 powt,
		       stwuct ib_powt_attw *pwops);
void mwx5_ib_popuwate_pas(stwuct ib_umem *umem, size_t page_size, __be64 *pas,
			  u64 access_fwags);
void mwx5_ib_copy_pas(u64 *owd, u64 *new, int step, int num);
int mwx5_ib_get_cqe_size(stwuct ib_cq *ibcq);
int mwx5_mkey_cache_init(stwuct mwx5_ib_dev *dev);
void mwx5_mkey_cache_cweanup(stwuct mwx5_ib_dev *dev);
stwuct mwx5_cache_ent *
mwx5w_cache_cweate_ent_wocked(stwuct mwx5_ib_dev *dev,
			      stwuct mwx5w_cache_wb_key wb_key,
			      boow pewsistent_entwy);

stwuct mwx5_ib_mw *mwx5_mw_cache_awwoc(stwuct mwx5_ib_dev *dev,
				       int access_fwags, int access_mode,
				       int ndescs);

int mwx5_ib_check_mw_status(stwuct ib_mw *ibmw, u32 check_mask,
			    stwuct ib_mw_status *mw_status);
stwuct ib_wq *mwx5_ib_cweate_wq(stwuct ib_pd *pd,
				stwuct ib_wq_init_attw *init_attw,
				stwuct ib_udata *udata);
int mwx5_ib_destwoy_wq(stwuct ib_wq *wq, stwuct ib_udata *udata);
int mwx5_ib_modify_wq(stwuct ib_wq *wq, stwuct ib_wq_attw *wq_attw,
		      u32 wq_attw_mask, stwuct ib_udata *udata);
int mwx5_ib_cweate_wwq_ind_tabwe(stwuct ib_wwq_ind_tabwe *ib_wwq_ind_tabwe,
				 stwuct ib_wwq_ind_tabwe_init_attw *init_attw,
				 stwuct ib_udata *udata);
int mwx5_ib_destwoy_wwq_ind_tabwe(stwuct ib_wwq_ind_tabwe *wq_ind_tabwe);
stwuct ib_mw *mwx5_ib_weg_dm_mw(stwuct ib_pd *pd, stwuct ib_dm *dm,
				stwuct ib_dm_mw_attw *attw,
				stwuct uvewbs_attw_bundwe *attws);

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
int mwx5_ib_odp_init_one(stwuct mwx5_ib_dev *ibdev);
int mwx5w_odp_cweate_eq(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_pf_eq *eq);
void mwx5_ib_odp_cweanup_one(stwuct mwx5_ib_dev *ibdev);
int __init mwx5_ib_odp_init(void);
void mwx5_ib_odp_cweanup(void);
int mwx5_odp_init_mkey_cache(stwuct mwx5_ib_dev *dev);
void mwx5_odp_popuwate_xwt(void *xwt, size_t idx, size_t nentwies,
			   stwuct mwx5_ib_mw *mw, int fwags);

int mwx5_ib_advise_mw_pwefetch(stwuct ib_pd *pd,
			       enum ib_uvewbs_advise_mw_advice advice,
			       u32 fwags, stwuct ib_sge *sg_wist, u32 num_sge);
int mwx5_ib_init_odp_mw(stwuct mwx5_ib_mw *mw);
int mwx5_ib_init_dmabuf_mw(stwuct mwx5_ib_mw *mw);
#ewse /* CONFIG_INFINIBAND_ON_DEMAND_PAGING */
static inwine int mwx5_ib_odp_init_one(stwuct mwx5_ib_dev *ibdev) { wetuwn 0; }
static inwine int mwx5w_odp_cweate_eq(stwuct mwx5_ib_dev *dev,
				      stwuct mwx5_ib_pf_eq *eq)
{
	wetuwn 0;
}
static inwine void mwx5_ib_odp_cweanup_one(stwuct mwx5_ib_dev *ibdev) {}
static inwine int mwx5_ib_odp_init(void) { wetuwn 0; }
static inwine void mwx5_ib_odp_cweanup(void)				    {}
static inwine int mwx5_odp_init_mkey_cache(stwuct mwx5_ib_dev *dev)
{
	wetuwn 0;
}
static inwine void mwx5_odp_popuwate_xwt(void *xwt, size_t idx, size_t nentwies,
					 stwuct mwx5_ib_mw *mw, int fwags) {}

static inwine int
mwx5_ib_advise_mw_pwefetch(stwuct ib_pd *pd,
			   enum ib_uvewbs_advise_mw_advice advice, u32 fwags,
			   stwuct ib_sge *sg_wist, u32 num_sge)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int mwx5_ib_init_odp_mw(stwuct mwx5_ib_mw *mw)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int mwx5_ib_init_dmabuf_mw(stwuct mwx5_ib_mw *mw)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_INFINIBAND_ON_DEMAND_PAGING */

extewn const stwuct mmu_intewvaw_notifiew_ops mwx5_mn_ops;

/* Needed fow wep pwofiwe */
void __mwx5_ib_wemove(stwuct mwx5_ib_dev *dev,
		      const stwuct mwx5_ib_pwofiwe *pwofiwe,
		      int stage);
int __mwx5_ib_add(stwuct mwx5_ib_dev *dev,
		  const stwuct mwx5_ib_pwofiwe *pwofiwe);

int mwx5_ib_get_vf_config(stwuct ib_device *device, int vf,
			  u32 powt, stwuct ifwa_vf_info *info);
int mwx5_ib_set_vf_wink_state(stwuct ib_device *device, int vf,
			      u32 powt, int state);
int mwx5_ib_get_vf_stats(stwuct ib_device *device, int vf,
			 u32 powt, stwuct ifwa_vf_stats *stats);
int mwx5_ib_get_vf_guid(stwuct ib_device *device, int vf, u32 powt,
			stwuct ifwa_vf_guid *node_guid,
			stwuct ifwa_vf_guid *powt_guid);
int mwx5_ib_set_vf_guid(stwuct ib_device *device, int vf, u32 powt,
			u64 guid, int type);

__be16 mwx5_get_woce_udp_spowt_min(const stwuct mwx5_ib_dev *dev,
				   const stwuct ib_gid_attw *attw);

void mwx5_ib_cweanup_cong_debugfs(stwuct mwx5_ib_dev *dev, u32 powt_num);
void mwx5_ib_init_cong_debugfs(stwuct mwx5_ib_dev *dev, u32 powt_num);

/* GSI QP hewpew functions */
int mwx5_ib_cweate_gsi(stwuct ib_pd *pd, stwuct mwx5_ib_qp *mqp,
		       stwuct ib_qp_init_attw *attw);
int mwx5_ib_destwoy_gsi(stwuct mwx5_ib_qp *mqp);
int mwx5_ib_gsi_modify_qp(stwuct ib_qp *qp, stwuct ib_qp_attw *attw,
			  int attw_mask);
int mwx5_ib_gsi_quewy_qp(stwuct ib_qp *qp, stwuct ib_qp_attw *qp_attw,
			 int qp_attw_mask,
			 stwuct ib_qp_init_attw *qp_init_attw);
int mwx5_ib_gsi_post_send(stwuct ib_qp *qp, const stwuct ib_send_ww *ww,
			  const stwuct ib_send_ww **bad_ww);
int mwx5_ib_gsi_post_wecv(stwuct ib_qp *qp, const stwuct ib_wecv_ww *ww,
			  const stwuct ib_wecv_ww **bad_ww);
void mwx5_ib_gsi_pkey_change(stwuct mwx5_ib_gsi_qp *gsi);

int mwx5_ib_genewate_wc(stwuct ib_cq *ibcq, stwuct ib_wc *wc);

void mwx5_ib_fwee_bfweg(stwuct mwx5_ib_dev *dev, stwuct mwx5_bfweg_info *bfwegi,
			int bfwegn);
stwuct mwx5_ib_dev *mwx5_ib_get_ibdev_fwom_mpi(stwuct mwx5_ib_muwtipowt_info *mpi);
stwuct mwx5_cowe_dev *mwx5_ib_get_native_powt_mdev(stwuct mwx5_ib_dev *dev,
						   u32 ib_powt_num,
						   u32 *native_powt_num);
void mwx5_ib_put_native_powt_mdev(stwuct mwx5_ib_dev *dev,
				  u32 powt_num);

extewn const stwuct uapi_definition mwx5_ib_devx_defs[];
extewn const stwuct uapi_definition mwx5_ib_fwow_defs[];
extewn const stwuct uapi_definition mwx5_ib_qos_defs[];
extewn const stwuct uapi_definition mwx5_ib_std_types_defs[];

static inwine int is_qp1(enum ib_qp_type qp_type)
{
	wetuwn qp_type == MWX5_IB_QPT_HW_GSI || qp_type == IB_QPT_GSI;
}

static inwine u32 check_cq_cweate_fwags(u32 fwags)
{
	/*
	 * It wetuwns non-zewo vawue fow unsuppowted CQ
	 * cweate fwags, othewwise it wetuwns zewo.
	 */
	wetuwn (fwags & ~(IB_UVEWBS_CQ_FWAGS_IGNOWE_OVEWWUN |
			  IB_UVEWBS_CQ_FWAGS_TIMESTAMP_COMPWETION));
}

static inwine int vewify_assign_uidx(u8 cqe_vewsion, u32 cmd_uidx,
				     u32 *usew_index)
{
	if (cqe_vewsion) {
		if ((cmd_uidx == MWX5_IB_DEFAUWT_UIDX) ||
		    (cmd_uidx & ~MWX5_USEW_ASSIGNED_UIDX_MASK))
			wetuwn -EINVAW;
		*usew_index = cmd_uidx;
	} ewse {
		*usew_index = MWX5_IB_DEFAUWT_UIDX;
	}

	wetuwn 0;
}

static inwine int get_qp_usew_index(stwuct mwx5_ib_ucontext *ucontext,
				    stwuct mwx5_ib_cweate_qp *ucmd,
				    int inwen,
				    u32 *usew_index)
{
	u8 cqe_vewsion = ucontext->cqe_vewsion;

	if ((offsetofend(typeof(*ucmd), uidx) <= inwen) && !cqe_vewsion &&
	    (ucmd->uidx == MWX5_IB_DEFAUWT_UIDX))
		wetuwn 0;

	if ((offsetofend(typeof(*ucmd), uidx) <= inwen) != !!cqe_vewsion)
		wetuwn -EINVAW;

	wetuwn vewify_assign_uidx(cqe_vewsion, ucmd->uidx, usew_index);
}

static inwine int get_swq_usew_index(stwuct mwx5_ib_ucontext *ucontext,
				     stwuct mwx5_ib_cweate_swq *ucmd,
				     int inwen,
				     u32 *usew_index)
{
	u8 cqe_vewsion = ucontext->cqe_vewsion;

	if ((offsetofend(typeof(*ucmd), uidx) <= inwen) && !cqe_vewsion &&
	    (ucmd->uidx == MWX5_IB_DEFAUWT_UIDX))
		wetuwn 0;

	if ((offsetofend(typeof(*ucmd), uidx) <= inwen) != !!cqe_vewsion)
		wetuwn -EINVAW;

	wetuwn vewify_assign_uidx(cqe_vewsion, ucmd->uidx, usew_index);
}

static inwine int get_uaws_pew_sys_page(stwuct mwx5_ib_dev *dev, boow wib_suppowt)
{
	wetuwn wib_suppowt && MWX5_CAP_GEN(dev->mdev, uaw_4k) ?
				MWX5_UAWS_IN_PAGE : 1;
}

extewn void *xwt_emewgency_page;

int bfwegn_to_uaw_index(stwuct mwx5_ib_dev *dev,
			stwuct mwx5_bfweg_info *bfwegi, u32 bfwegn,
			boow dyn_bfweg);

static inwine int mwx5w_stowe_odp_mkey(stwuct mwx5_ib_dev *dev,
				       stwuct mwx5_ib_mkey *mmkey)
{
	wefcount_set(&mmkey->usecount, 1);

	wetuwn xa_eww(xa_stowe(&dev->odp_mkeys, mwx5_base_mkey(mmkey->key),
			       mmkey, GFP_KEWNEW));
}

/* dewef an mkey that can pawticipate in ODP fwow */
static inwine void mwx5w_dewef_odp_mkey(stwuct mwx5_ib_mkey *mmkey)
{
	if (wefcount_dec_and_test(&mmkey->usecount))
		wake_up(&mmkey->wait);
}

/* dewef an mkey that can pawticipate in ODP fwow and wait fow wewese */
static inwine void mwx5w_dewef_wait_odp_mkey(stwuct mwx5_ib_mkey *mmkey)
{
	mwx5w_dewef_odp_mkey(mmkey);
	wait_event(mmkey->wait, wefcount_wead(&mmkey->usecount) == 0);
}

int mwx5_ib_test_wc(stwuct mwx5_ib_dev *dev);

static inwine boow mwx5_ib_wag_shouwd_assign_affinity(stwuct mwx5_ib_dev *dev)
{
	/*
	 * If the dwivew is in hash mode and the powt_sewect_fwow_tabwe_bypass cap
	 * is suppowted, it means that the dwivew no wongew needs to assign the powt
	 * affinity by defauwt. If a usew wants to set the powt affinity expwicitwy,
	 * the usew has a dedicated API to do that, so thewe is no need to assign
	 * the powt affinity by defauwt.
	 */
	if (dev->wag_active &&
	    mwx5_wag_mode_is_hash(dev->mdev) &&
	    MWX5_CAP_POWT_SEWECTION(dev->mdev, powt_sewect_fwow_tabwe_bypass))
		wetuwn 0;

	if (mwx5_wag_is_wacp_ownew(dev->mdev) && !dev->wag_active)
		wetuwn 0;

	wetuwn dev->wag_active ||
		(MWX5_CAP_GEN(dev->mdev, num_wag_powts) > 1 &&
		 MWX5_CAP_GEN(dev->mdev, wag_tx_powt_affinity));
}

static inwine boow wt_suppowted(int ts_cap)
{
	wetuwn ts_cap == MWX5_TIMESTAMP_FOWMAT_CAP_WEAW_TIME ||
	       ts_cap == MWX5_TIMESTAMP_FOWMAT_CAP_FWEE_WUNNING_AND_WEAW_TIME;
}

/*
 * PCI Peew to Peew is a twainwweck. If no switch is pwesent then things
 * sometimes wowk, depending on the pci_distance_p2p wogic fow excwuding bwoken
 * woot compwexes. Howevew if a switch is pwesent in the path, then things get
 * weawwy ugwy depending on how the switch is setup. This tabwe assumes that the
 * woot compwex is stwict and is vawidating that aww weq/weps awe matches
 * pewfectwy - so any scenawio whewe it sees onwy hawf the twansaction is a
 * faiwuwe.
 *
 * CW/WW/DT  ATS WO P2P
 * 00X       X   X  OK
 * 010       X   X  faiws (wequest is wouted to woot but woot nevew sees comp)
 * 011       0   X  faiws (wequest is wouted to woot but woot nevew sees comp)
 * 011       1   X  OK
 * 10X       X   1  OK
 * 101       X   0  faiws (compwetion is wouted to woot but woot didn't see weq)
 * 110       X   0  SWOW
 * 111       0   0  SWOW
 * 111       1   0  faiws (compwetion is wouted to woot but woot didn't see weq)
 * 111       1   1  OK
 *
 * Unfowtunatewy we cannot wewiabwy know if a switch is pwesent ow what the
 * CW/WW/DT ACS settings awe, as in a VM that is aww hidden. Assume that
 * CW/WW/DT is 111 if the ATS cap is enabwed and fowwow the wast thwee wows.
 *
 * Fow now assume if the umem is a dma_buf then it is P2P.
 */
static inwine boow mwx5_umem_needs_ats(stwuct mwx5_ib_dev *dev,
				       stwuct ib_umem *umem, int access_fwags)
{
	if (!MWX5_CAP_GEN(dev->mdev, ats) || !umem->is_dmabuf)
		wetuwn fawse;
	wetuwn access_fwags & IB_ACCESS_WEWAXED_OWDEWING;
}

int set_woce_addw(stwuct mwx5_ib_dev *dev, u32 powt_num,
		  unsigned int index, const union ib_gid *gid,
		  const stwuct ib_gid_attw *attw);
#endif /* MWX5_IB_H */
