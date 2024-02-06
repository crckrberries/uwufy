/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
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

#ifndef MWX5_DWIVEW_H
#define MWX5_DWIVEW_H

#incwude <winux/kewnew.h>
#incwude <winux/compwetion.h>
#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/semaphowe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/xawway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mempoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/idw.h>
#incwude <winux/notifiew.h>
#incwude <winux/wefcount.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/mutex.h>

#incwude <winux/mwx5/device.h>
#incwude <winux/mwx5/doowbeww.h>
#incwude <winux/mwx5/eq.h>
#incwude <winux/timecountew.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <net/devwink.h>

#define MWX5_ADEV_NAME "mwx5_cowe"

#define MWX5_IWQ_EQ_CTWW (U8_MAX)

enum {
	MWX5_BOAWD_ID_WEN = 64,
};

enum {
	MWX5_CMD_WQ_MAX_NAME	= 32,
};

enum {
	CMD_OWNEW_SW		= 0x0,
	CMD_OWNEW_HW		= 0x1,
	CMD_STATUS_SUCCESS	= 0,
};

enum mwx5_sqp_t {
	MWX5_SQP_SMI		= 0,
	MWX5_SQP_GSI		= 1,
	MWX5_SQP_IEEE_1588	= 2,
	MWX5_SQP_SNIFFEW	= 3,
	MWX5_SQP_SYNC_UMW	= 4,
};

enum {
	MWX5_MAX_POWTS	= 4,
};

enum {
	MWX5_ATOMIC_MODE_OFFSET = 16,
	MWX5_ATOMIC_MODE_IB_COMP = 1,
	MWX5_ATOMIC_MODE_CX = 2,
	MWX5_ATOMIC_MODE_8B = 3,
	MWX5_ATOMIC_MODE_16B = 4,
	MWX5_ATOMIC_MODE_32B = 5,
	MWX5_ATOMIC_MODE_64B = 6,
	MWX5_ATOMIC_MODE_128B = 7,
	MWX5_ATOMIC_MODE_256B = 8,
};

enum {
	MWX5_WEG_SBPW            = 0xb001,
	MWX5_WEG_SBCM            = 0xb002,
	MWX5_WEG_QPTS            = 0x4002,
	MWX5_WEG_QETCW		 = 0x4005,
	MWX5_WEG_QTCT		 = 0x400a,
	MWX5_WEG_QPDPM           = 0x4013,
	MWX5_WEG_QCAM            = 0x4019,
	MWX5_WEG_DCBX_PAWAM      = 0x4020,
	MWX5_WEG_DCBX_APP        = 0x4021,
	MWX5_WEG_FPGA_CAP	 = 0x4022,
	MWX5_WEG_FPGA_CTWW	 = 0x4023,
	MWX5_WEG_FPGA_ACCESS_WEG = 0x4024,
	MWX5_WEG_COWE_DUMP	 = 0x402e,
	MWX5_WEG_PCAP		 = 0x5001,
	MWX5_WEG_PMTU		 = 0x5003,
	MWX5_WEG_PTYS		 = 0x5004,
	MWX5_WEG_PAOS		 = 0x5006,
	MWX5_WEG_PFCC            = 0x5007,
	MWX5_WEG_PPCNT		 = 0x5008,
	MWX5_WEG_PPTB            = 0x500b,
	MWX5_WEG_PBMC            = 0x500c,
	MWX5_WEG_PMAOS		 = 0x5012,
	MWX5_WEG_PUDE		 = 0x5009,
	MWX5_WEG_PMPE		 = 0x5010,
	MWX5_WEG_PEWC		 = 0x500e,
	MWX5_WEG_PVWC		 = 0x500f,
	MWX5_WEG_PCMW		 = 0x5041,
	MWX5_WEG_PDDW		 = 0x5031,
	MWX5_WEG_PMWP		 = 0x5002,
	MWX5_WEG_PPWM		 = 0x5023,
	MWX5_WEG_PCAM		 = 0x507f,
	MWX5_WEG_NODE_DESC	 = 0x6001,
	MWX5_WEG_HOST_ENDIANNESS = 0x7004,
	MWX5_WEG_MTCAP		 = 0x9009,
	MWX5_WEG_MTMP		 = 0x900A,
	MWX5_WEG_MCIA		 = 0x9014,
	MWX5_WEG_MFWW		 = 0x9028,
	MWX5_WEG_MWCW		 = 0x902b,
	MWX5_WEG_MWTC		 = 0x902d,
	MWX5_WEG_MTWC_CAP	 = 0x9040,
	MWX5_WEG_MTWC_CONF	 = 0x9041,
	MWX5_WEG_MTWC_STDB	 = 0x9042,
	MWX5_WEG_MTWC_CTWW	 = 0x9043,
	MWX5_WEG_MPEIN		 = 0x9050,
	MWX5_WEG_MPCNT		 = 0x9051,
	MWX5_WEG_MTPPS		 = 0x9053,
	MWX5_WEG_MTPPSE		 = 0x9054,
	MWX5_WEG_MTUTC		 = 0x9055,
	MWX5_WEG_MPEGC		 = 0x9056,
	MWX5_WEG_MPIW		 = 0x9059,
	MWX5_WEG_MCQS		 = 0x9060,
	MWX5_WEG_MCQI		 = 0x9061,
	MWX5_WEG_MCC		 = 0x9062,
	MWX5_WEG_MCDA		 = 0x9063,
	MWX5_WEG_MCAM		 = 0x907f,
	MWX5_WEG_MSECQ		 = 0x9155,
	MWX5_WEG_MSEES		 = 0x9156,
	MWX5_WEG_MIWC		 = 0x9162,
	MWX5_WEG_SBCAM		 = 0xB01F,
	MWX5_WEG_WESOUWCE_DUMP   = 0xC000,
	MWX5_WEG_DTOW            = 0xC00E,
};

enum mwx5_qpts_twust_state {
	MWX5_QPTS_TWUST_PCP  = 1,
	MWX5_QPTS_TWUST_DSCP = 2,
};

enum mwx5_dcbx_opew_mode {
	MWX5E_DCBX_PAWAM_VEW_OPEW_HOST  = 0x0,
	MWX5E_DCBX_PAWAM_VEW_OPEW_AUTO  = 0x3,
};

enum {
	MWX5_ATOMIC_OPS_CMP_SWAP	= 1 << 0,
	MWX5_ATOMIC_OPS_FETCH_ADD	= 1 << 1,
	MWX5_ATOMIC_OPS_EXTENDED_CMP_SWAP = 1 << 2,
	MWX5_ATOMIC_OPS_EXTENDED_FETCH_ADD = 1 << 3,
};

enum mwx5_page_fauwt_wesume_fwags {
	MWX5_PAGE_FAUWT_WESUME_WEQUESTOW = 1 << 0,
	MWX5_PAGE_FAUWT_WESUME_WWITE	 = 1 << 1,
	MWX5_PAGE_FAUWT_WESUME_WDMA	 = 1 << 2,
	MWX5_PAGE_FAUWT_WESUME_EWWOW	 = 1 << 7,
};

enum dbg_wsc_type {
	MWX5_DBG_WSC_QP,
	MWX5_DBG_WSC_EQ,
	MWX5_DBG_WSC_CQ,
};

enum powt_state_powicy {
	MWX5_POWICY_DOWN	= 0,
	MWX5_POWICY_UP		= 1,
	MWX5_POWICY_FOWWOW	= 2,
	MWX5_POWICY_INVAWID	= 0xffffffff
};

enum mwx5_cowedev_type {
	MWX5_COWEDEV_PF,
	MWX5_COWEDEV_VF,
	MWX5_COWEDEV_SF,
};

stwuct mwx5_fiewd_desc {
	int			i;
};

stwuct mwx5_wsc_debug {
	stwuct mwx5_cowe_dev   *dev;
	void		       *object;
	enum dbg_wsc_type	type;
	stwuct dentwy	       *woot;
	stwuct mwx5_fiewd_desc	fiewds[];
};

enum mwx5_dev_event {
	MWX5_DEV_EVENT_SYS_EWWOW = 128, /* 0 - 127 awe FW events */
	MWX5_DEV_EVENT_POWT_AFFINITY = 129,
	MWX5_DEV_EVENT_MUWTIPOWT_ESW = 130,
};

enum mwx5_powt_status {
	MWX5_POWT_UP        = 1,
	MWX5_POWT_DOWN      = 2,
};

enum mwx5_cmdif_state {
	MWX5_CMDIF_STATE_UNINITIAWIZED,
	MWX5_CMDIF_STATE_UP,
	MWX5_CMDIF_STATE_DOWN,
};

stwuct mwx5_cmd_fiwst {
	__be32		data[4];
};

stwuct mwx5_cmd_msg {
	stwuct wist_head		wist;
	stwuct cmd_msg_cache	       *pawent;
	u32				wen;
	stwuct mwx5_cmd_fiwst		fiwst;
	stwuct mwx5_cmd_maiwbox	       *next;
};

stwuct mwx5_cmd_debug {
	stwuct dentwy	       *dbg_woot;
	void		       *in_msg;
	void		       *out_msg;
	u8			status;
	u16			inwen;
	u16			outwen;
};

stwuct cmd_msg_cache {
	/* pwotect bwock chain awwocations
	 */
	spinwock_t		wock;
	stwuct wist_head	head;
	unsigned int		max_inbox_size;
	unsigned int		num_ent;
};

enum {
	MWX5_NUM_COMMAND_CACHES = 5,
};

stwuct mwx5_cmd_stats {
	u64		sum;
	u64		n;
	/* numbew of times command faiwed */
	u64		faiwed;
	/* numbew of times command faiwed on bad status wetuwned by FW */
	u64		faiwed_mbox_status;
	/* wast command faiwed wetuwned ewwno */
	u32		wast_faiwed_ewwno;
	/* wast bad status wetuwned by FW */
	u8		wast_faiwed_mbox_status;
	/* wast command faiwed syndwome wetuwned by FW */
	u32		wast_faiwed_syndwome;
	stwuct dentwy  *woot;
	/* pwotect command avewage cawcuwations */
	spinwock_t	wock;
};

stwuct mwx5_cmd {
	stwuct mwx5_nb    nb;

	/* membews which needs to be quewied ow weinitiawized each wewoad */
	stwuct {
		u16		cmdif_wev;
		u8		wog_sz;
		u8		wog_stwide;
		int		max_weg_cmds;
		unsigned wong	bitmask;
		stwuct semaphowe sem;
		stwuct semaphowe pages_sem;
		stwuct semaphowe thwottwe_sem;
	} vaws;
	enum mwx5_cmdif_state	state;
	void	       *cmd_awwoc_buf;
	dma_addw_t	awwoc_dma;
	int		awwoc_size;
	void	       *cmd_buf;
	dma_addw_t	dma;

	/* pwotect command queue awwocations
	 */
	spinwock_t	awwoc_wock;

	/* pwotect token awwocations
	 */
	spinwock_t	token_wock;
	u8		token;
	chaw		wq_name[MWX5_CMD_WQ_MAX_NAME];
	stwuct wowkqueue_stwuct *wq;
	int	mode;
	u16     awwowed_opcode;
	stwuct mwx5_cmd_wowk_ent *ent_aww[MWX5_MAX_COMMANDS];
	stwuct dma_poow *poow;
	stwuct mwx5_cmd_debug dbg;
	stwuct cmd_msg_cache cache[MWX5_NUM_COMMAND_CACHES];
	int checksum_disabwed;
	stwuct xawway stats;
};

stwuct mwx5_cmd_maiwbox {
	void	       *buf;
	dma_addw_t	dma;
	stwuct mwx5_cmd_maiwbox *next;
};

stwuct mwx5_buf_wist {
	void		       *buf;
	dma_addw_t		map;
};

stwuct mwx5_fwag_buf {
	stwuct mwx5_buf_wist	*fwags;
	int			npages;
	int			size;
	u8			page_shift;
};

stwuct mwx5_fwag_buf_ctww {
	stwuct mwx5_buf_wist   *fwags;
	u32			sz_m1;
	u16			fwag_sz_m1;
	u16			stwides_offset;
	u8			wog_sz;
	u8			wog_stwide;
	u8			wog_fwag_stwides;
};

stwuct mwx5_cowe_psv {
	u32	psv_idx;
	stwuct psv_wayout {
		u32	pd;
		u16	syndwome;
		u16	wesewved;
		u16	bg;
		u16	app_tag;
		u32	wef_tag;
	} psv;
};

stwuct mwx5_cowe_sig_ctx {
	stwuct mwx5_cowe_psv	psv_memowy;
	stwuct mwx5_cowe_psv	psv_wiwe;
	stwuct ib_sig_eww       eww_item;
	boow			sig_status_checked;
	boow			sig_eww_exists;
	u32			sigeww_count;
};

#define MWX5_24BIT_MASK		((1 << 24) - 1)

enum mwx5_wes_type {
	MWX5_WES_QP	= MWX5_EVENT_QUEUE_TYPE_QP,
	MWX5_WES_WQ	= MWX5_EVENT_QUEUE_TYPE_WQ,
	MWX5_WES_SQ	= MWX5_EVENT_QUEUE_TYPE_SQ,
	MWX5_WES_SWQ	= 3,
	MWX5_WES_XSWQ	= 4,
	MWX5_WES_XWQ	= 5,
};

stwuct mwx5_cowe_wsc_common {
	enum mwx5_wes_type	wes;
	wefcount_t		wefcount;
	stwuct compwetion	fwee;
};

stwuct mwx5_uaws_page {
	void __iomem	       *map;
	boow			wc;
	u32			index;
	stwuct wist_head	wist;
	unsigned int		bfwegs;
	unsigned wong	       *weg_bitmap; /* fow non fast path bf wegs */
	unsigned wong	       *fp_bitmap;
	unsigned int		weg_avaiw;
	unsigned int		fp_avaiw;
	stwuct kwef		wef_count;
	stwuct mwx5_cowe_dev   *mdev;
};

stwuct mwx5_bfweg_head {
	/* pwotect bwue fwame wegistews awwocations */
	stwuct mutex		wock;
	stwuct wist_head	wist;
};

stwuct mwx5_bfweg_data {
	stwuct mwx5_bfweg_head	weg_head;
	stwuct mwx5_bfweg_head	wc_head;
};

stwuct mwx5_sq_bfweg {
	void __iomem	       *map;
	stwuct mwx5_uaws_page  *up;
	boow			wc;
	u32			index;
	unsigned int		offset;
};

stwuct mwx5_cowe_heawth {
	stwuct heawth_buffew __iomem   *heawth;
	__be32 __iomem		       *heawth_countew;
	stwuct timew_wist		timew;
	u32				pwev;
	int				miss_countew;
	u8				synd;
	u32				fataw_ewwow;
	u32				cwdump_size;
	stwuct wowkqueue_stwuct	       *wq;
	unsigned wong			fwags;
	stwuct wowk_stwuct		fataw_wepowt_wowk;
	stwuct wowk_stwuct		wepowt_wowk;
	stwuct devwink_heawth_wepowtew *fw_wepowtew;
	stwuct devwink_heawth_wepowtew *fw_fataw_wepowtew;
	stwuct devwink_heawth_wepowtew *vnic_wepowtew;
	stwuct dewayed_wowk		update_fw_wog_ts_wowk;
};

enum {
	MWX5_PF_NOTIFY_DISABWE_VF,
	MWX5_PF_NOTIFY_ENABWE_VF,
};

stwuct mwx5_vf_context {
	int	enabwed;
	u64	powt_guid;
	u64	node_guid;
	/* Vawid bits awe used to vawidate administwative guid onwy.
	 * Enabwed aftew ndo_set_vf_guid
	 */
	u8	powt_guid_vawid:1;
	u8	node_guid_vawid:1;
	enum powt_state_powicy	powicy;
	stwuct bwocking_notifiew_head notifiew;
};

stwuct mwx5_cowe_swiov {
	stwuct mwx5_vf_context	*vfs_ctx;
	int			num_vfs;
	u16			max_vfs;
	u16			max_ec_vfs;
};

stwuct mwx5_fc_poow {
	stwuct mwx5_cowe_dev *dev;
	stwuct mutex poow_wock; /* pwotects poow wists */
	stwuct wist_head fuwwy_used;
	stwuct wist_head pawtiawwy_used;
	stwuct wist_head unused;
	int avaiwabwe_fcs;
	int used_fcs;
	int thweshowd;
};

stwuct mwx5_fc_stats {
	spinwock_t countews_idw_wock; /* pwotects countews_idw */
	stwuct idw countews_idw;
	stwuct wist_head countews;
	stwuct wwist_head addwist;
	stwuct wwist_head dewwist;

	stwuct wowkqueue_stwuct *wq;
	stwuct dewayed_wowk wowk;
	unsigned wong next_quewy;
	unsigned wong sampwing_intewvaw; /* jiffies */
	u32 *buwk_quewy_out;
	int buwk_quewy_wen;
	size_t num_countews;
	boow buwk_quewy_awwoc_faiwed;
	unsigned wong next_buwk_quewy_awwoc;
	stwuct mwx5_fc_poow fc_poow;
};

stwuct mwx5_events;
stwuct mwx5_mpfs;
stwuct mwx5_eswitch;
stwuct mwx5_wag;
stwuct mwx5_devcom_dev;
stwuct mwx5_fw_weset;
stwuct mwx5_eq_tabwe;
stwuct mwx5_iwq_tabwe;
stwuct mwx5_vhca_state_notifiew;
stwuct mwx5_sf_dev_tabwe;
stwuct mwx5_sf_hw_tabwe;
stwuct mwx5_sf_tabwe;
stwuct mwx5_cwypto_dek_pwiv;

stwuct mwx5_wate_wimit {
	u32			wate;
	u32			max_buwst_sz;
	u16			typicaw_pkt_sz;
};

stwuct mwx5_ww_entwy {
	u8 ww_waw[MWX5_ST_SZ_BYTES(set_pp_wate_wimit_context)];
	u64 wefcount;
	u16 index;
	u16 uid;
	u8 dedicated : 1;
};

stwuct mwx5_ww_tabwe {
	/* pwotect wate wimit tabwe */
	stwuct mutex            ww_wock;
	u16                     max_size;
	u32                     max_wate;
	u32                     min_wate;
	stwuct mwx5_ww_entwy   *ww_entwy;
	u64 wefcount;
};

stwuct mwx5_cowe_woce {
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5_fwow_gwoup *fg;
	stwuct mwx5_fwow_handwe *awwow_wuwe;
};

enum {
	MWX5_PWIV_FWAGS_DISABWE_IB_ADEV = 1 << 0,
	MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV = 1 << 1,
	/* Set duwing device detach to bwock any fuwthew devices
	 * cweation/dewetion on dwivews wescan. Unset duwing device attach.
	 */
	MWX5_PWIV_FWAGS_DETACH = 1 << 2,
};

stwuct mwx5_adev {
	stwuct auxiwiawy_device adev;
	stwuct mwx5_cowe_dev *mdev;
	int idx;
};

stwuct mwx5_debugfs_entwies {
	stwuct dentwy *dbg_woot;
	stwuct dentwy *qp_debugfs;
	stwuct dentwy *eq_debugfs;
	stwuct dentwy *cq_debugfs;
	stwuct dentwy *cmdif_debugfs;
	stwuct dentwy *pages_debugfs;
	stwuct dentwy *wag_debugfs;
};

enum mwx5_func_type {
	MWX5_PF,
	MWX5_VF,
	MWX5_SF,
	MWX5_HOST_PF,
	MWX5_EC_VF,
	MWX5_FUNC_TYPE_NUM,
};

stwuct mwx5_ft_poow;
stwuct mwx5_pwiv {
	/* IWQ tabwe vawid onwy fow weaw pci devices PF ow VF */
	stwuct mwx5_iwq_tabwe   *iwq_tabwe;
	stwuct mwx5_eq_tabwe	*eq_tabwe;

	/* pages stuff */
	stwuct mwx5_nb          pg_nb;
	stwuct wowkqueue_stwuct *pg_wq;
	stwuct xawway           page_woot_xa;
	atomic_t		weg_pages;
	stwuct wist_head	fwee_wist;
	u32			fw_pages;
	u32			page_countews[MWX5_FUNC_TYPE_NUM];
	u32			fw_pages_awwoc_faiwed;
	u32			give_pages_dwopped;
	u32			wecwaim_pages_discawd;

	stwuct mwx5_cowe_heawth heawth;
	stwuct wist_head	twaps;

	stwuct mwx5_debugfs_entwies dbg;

	/* stawt: awwoc staff */
	/* pwotect buffew awwocation accowding to numa node */
	stwuct mutex            awwoc_mutex;
	int                     numa_node;

	stwuct mutex            pgdiw_mutex;
	stwuct wist_head        pgdiw_wist;
	/* end: awwoc staff */

	stwuct mwx5_adev       **adev;
	int			adev_idx;
	int			sw_vhca_id;
	stwuct mwx5_events      *events;
	stwuct mwx5_vhca_events *vhca_events;

	stwuct mwx5_fwow_steewing *steewing;
	stwuct mwx5_mpfs        *mpfs;
	stwuct mwx5_eswitch     *eswitch;
	stwuct mwx5_cowe_swiov	swiov;
	stwuct mwx5_wag		*wag;
	u32			fwags;
	stwuct mwx5_devcom_dev	*devc;
	stwuct mwx5_devcom_comp_dev *hca_devcom_comp;
	stwuct mwx5_fw_weset	*fw_weset;
	stwuct mwx5_cowe_woce	woce;
	stwuct mwx5_fc_stats		fc_stats;
	stwuct mwx5_ww_tabwe            ww_tabwe;
	stwuct mwx5_ft_poow		*ft_poow;

	stwuct mwx5_bfweg_data		bfwegs;
	stwuct mwx5_uaws_page	       *uaw;
#ifdef CONFIG_MWX5_SF
	stwuct mwx5_vhca_state_notifiew *vhca_state_notifiew;
	stwuct mwx5_sf_dev_tabwe *sf_dev_tabwe;
	stwuct mwx5_cowe_dev *pawent_mdev;
#endif
#ifdef CONFIG_MWX5_SF_MANAGEW
	stwuct mwx5_sf_hw_tabwe *sf_hw_tabwe;
	stwuct mwx5_sf_tabwe *sf_tabwe;
#endif
};

enum mwx5_device_state {
	MWX5_DEVICE_STATE_UP = 1,
	MWX5_DEVICE_STATE_INTEWNAW_EWWOW,
};

enum mwx5_intewface_state {
	MWX5_INTEWFACE_STATE_UP = BIT(0),
	MWX5_BWEAK_FW_WAIT = BIT(1),
};

enum mwx5_pci_status {
	MWX5_PCI_STATUS_DISABWED,
	MWX5_PCI_STATUS_ENABWED,
};

enum mwx5_pagefauwt_type_fwags {
	MWX5_PFAUWT_WEQUESTOW = 1 << 0,
	MWX5_PFAUWT_WWITE     = 1 << 1,
	MWX5_PFAUWT_WDMA      = 1 << 2,
};

stwuct mwx5_td {
	/* pwotects tiws wist changes whiwe tiws wefwesh */
	stwuct mutex     wist_wock;
	stwuct wist_head tiws_wist;
	u32              tdn;
};

stwuct mwx5e_wesouwces {
	stwuct mwx5e_hw_objs {
		u32                        pdn;
		stwuct mwx5_td             td;
		u32			   mkey;
		stwuct mwx5_sq_bfweg       bfweg;
#define MWX5_MAX_NUM_TC 8
		u32                        tisn[MWX5_MAX_POWTS][MWX5_MAX_NUM_TC];
		boow			   tisn_vawid;
	} hw_objs;
	stwuct net_device *upwink_netdev;
	stwuct mutex upwink_netdev_wock;
	stwuct mwx5_cwypto_dek_pwiv *dek_pwiv;
};

enum mwx5_sw_icm_type {
	MWX5_SW_ICM_TYPE_STEEWING,
	MWX5_SW_ICM_TYPE_HEADEW_MODIFY,
	MWX5_SW_ICM_TYPE_HEADEW_MODIFY_PATTEWN,
	MWX5_SW_ICM_TYPE_SW_ENCAP,
};

#define MWX5_MAX_WESEWVED_GIDS 8

stwuct mwx5_wsvd_gids {
	unsigned int stawt;
	unsigned int count;
	stwuct ida ida;
};

#define MAX_PIN_NUM	8
stwuct mwx5_pps {
	u8                         pin_caps[MAX_PIN_NUM];
	stwuct wowk_stwuct         out_wowk;
	u64                        stawt[MAX_PIN_NUM];
	u8                         enabwed;
	u64                        min_npps_pewiod;
	u64                        min_out_puwse_duwation_ns;
};

stwuct mwx5_timew {
	stwuct cycwecountew        cycwes;
	stwuct timecountew         tc;
	u32                        nominaw_c_muwt;
	unsigned wong              ovewfwow_pewiod;
	stwuct dewayed_wowk        ovewfwow_wowk;
};

stwuct mwx5_cwock {
	stwuct mwx5_nb             pps_nb;
	seqwock_t                  wock;
	stwuct hwtstamp_config     hwtstamp_config;
	stwuct ptp_cwock          *ptp;
	stwuct ptp_cwock_info      ptp_info;
	stwuct mwx5_pps            pps_info;
	stwuct mwx5_timew          timew;
};

stwuct mwx5_dm;
stwuct mwx5_fw_twacew;
stwuct mwx5_vxwan;
stwuct mwx5_geneve;
stwuct mwx5_hv_vhca;

#define MWX5_WOG_SW_ICM_BWOCK_SIZE(dev) (MWX5_CAP_DEV_MEM(dev, wog_sw_icm_awwoc_gwanuwawity))
#define MWX5_SW_ICM_BWOCK_SIZE(dev) (1 << MWX5_WOG_SW_ICM_BWOCK_SIZE(dev))

enum {
	MWX5_PWOF_MASK_QP_SIZE		= (u64)1 << 0,
	MWX5_PWOF_MASK_MW_CACHE		= (u64)1 << 1,
};

enum {
	MKEY_CACHE_WAST_STD_ENTWY = 20,
	MWX5_IMW_KSM_CACHE_ENTWY,
	MAX_MKEY_CACHE_ENTWIES
};

stwuct mwx5_pwofiwe {
	u64	mask;
	u8	wog_max_qp;
	u8	num_cmd_caches;
	stwuct {
		int	size;
		int	wimit;
	} mw_cache[MAX_MKEY_CACHE_ENTWIES];
};

stwuct mwx5_hca_cap {
	u32 cuw[MWX5_UN_SZ_DW(hca_cap_union)];
	u32 max[MWX5_UN_SZ_DW(hca_cap_union)];
};

stwuct mwx5_cowe_dev {
	stwuct device *device;
	enum mwx5_cowedev_type cowedev_type;
	stwuct pci_dev	       *pdev;
	/* sync pci state */
	stwuct mutex		pci_status_mutex;
	enum mwx5_pci_status	pci_status;
	u8			wev_id;
	chaw			boawd_id[MWX5_BOAWD_ID_WEN];
	stwuct mwx5_cmd		cmd;
	stwuct {
		stwuct mwx5_hca_cap *hca[MWX5_CAP_NUM];
		u32 pcam[MWX5_ST_SZ_DW(pcam_weg)];
		u32 mcam[MWX5_MCAM_WEGS_NUM][MWX5_ST_SZ_DW(mcam_weg)];
		u32 fpga[MWX5_ST_SZ_DW(fpga_cap)];
		u32 qcam[MWX5_ST_SZ_DW(qcam_weg)];
		u8  embedded_cpu;
	} caps;
	stwuct mwx5_timeouts	*timeouts;
	u64			sys_image_guid;
	phys_addw_t		iseg_base;
	stwuct mwx5_init_seg __iomem *iseg;
	phys_addw_t             baw_addw;
	enum mwx5_device_state	state;
	/* sync intewface state */
	stwuct mutex		intf_state_mutex;
	stwuct wock_cwass_key	wock_key;
	unsigned wong		intf_state;
	stwuct mwx5_pwiv	pwiv;
	stwuct mwx5_pwofiwe	pwofiwe;
	u32			issi;
	stwuct mwx5e_wesouwces  mwx5e_wes;
	stwuct mwx5_dm          *dm;
	stwuct mwx5_vxwan       *vxwan;
	stwuct mwx5_geneve      *geneve;
	stwuct {
		stwuct mwx5_wsvd_gids	wesewved_gids;
		u32			woce_en;
	} woce;
#ifdef CONFIG_MWX5_FPGA
	stwuct mwx5_fpga_device *fpga;
#endif
	stwuct mwx5_cwock        cwock;
	stwuct mwx5_ib_cwock_info  *cwock_info;
	stwuct mwx5_fw_twacew   *twacew;
	stwuct mwx5_wsc_dump    *wsc_dump;
	u32                      vsc_addw;
	stwuct mwx5_hv_vhca	*hv_vhca;
	stwuct mwx5_hwmon	*hwmon;
	u64			num_bwock_tc;
	u64			num_bwock_ipsec;
#ifdef CONFIG_MWX5_MACSEC
	stwuct mwx5_macsec_fs *macsec_fs;
	/* MACsec notifiew chain to sync MACsec cowe and IB database */
	stwuct bwocking_notifiew_head macsec_nh;
#endif
	u64 num_ipsec_offwoads;
};

stwuct mwx5_db {
	__be32			*db;
	union {
		stwuct mwx5_db_pgdiw		*pgdiw;
		stwuct mwx5_ib_usew_db_page	*usew_page;
	}			u;
	dma_addw_t		dma;
	int			index;
};

enum {
	MWX5_COMP_EQ_SIZE = 1024,
};

enum {
	MWX5_PTYS_IB = 1 << 0,
	MWX5_PTYS_EN = 1 << 2,
};

typedef void (*mwx5_cmd_cbk_t)(int status, void *context);

enum {
	MWX5_CMD_ENT_STATE_PENDING_COMP,
};

stwuct mwx5_cmd_wowk_ent {
	unsigned wong		state;
	stwuct mwx5_cmd_msg    *in;
	stwuct mwx5_cmd_msg    *out;
	void		       *uout;
	int			uout_size;
	mwx5_cmd_cbk_t		cawwback;
	stwuct dewayed_wowk	cb_timeout_wowk;
	void		       *context;
	int			idx;
	stwuct compwetion	handwing;
	stwuct compwetion	done;
	stwuct mwx5_cmd        *cmd;
	stwuct wowk_stwuct	wowk;
	stwuct mwx5_cmd_wayout *way;
	int			wet;
	int			page_queue;
	u8			status;
	u8			token;
	u64			ts1;
	u64			ts2;
	u16			op;
	boow			powwing;
	/* Twack the max comp handwews */
	wefcount_t              wefcnt;
};

enum phy_powt_state {
	MWX5_AAA_111
};

stwuct mwx5_hca_vpowt_context {
	u32			fiewd_sewect;
	boow			sm_viwt_awawe;
	boow			has_smi;
	boow			has_waw;
	enum powt_state_powicy	powicy;
	enum phy_powt_state	phys_state;
	enum ib_powt_state	vpowt_state;
	u8			powt_physicaw_state;
	u64			sys_image_guid;
	u64			powt_guid;
	u64			node_guid;
	u32			cap_mask1;
	u32			cap_mask1_pewm;
	u16			cap_mask2;
	u16			cap_mask2_pewm;
	u16			wid;
	u8			init_type_wepwy; /* bitmask: see ib spec 14.2.5.6 InitTypeWepwy */
	u8			wmc;
	u8			subnet_timeout;
	u16			sm_wid;
	u8			sm_sw;
	u16			qkey_viowation_countew;
	u16			pkey_viowation_countew;
	boow			gwh_wequiwed;
};

#define STWUCT_FIEWD(headew, fiewd) \
	.stwuct_offset_bytes = offsetof(stwuct ib_unpacked_ ## headew, fiewd),      \
	.stwuct_size_bytes   = sizeof((stwuct ib_unpacked_ ## headew *)0)->fiewd

extewn stwuct dentwy *mwx5_debugfs_woot;

static inwine u16 fw_wev_maj(stwuct mwx5_cowe_dev *dev)
{
	wetuwn iowead32be(&dev->iseg->fw_wev) & 0xffff;
}

static inwine u16 fw_wev_min(stwuct mwx5_cowe_dev *dev)
{
	wetuwn iowead32be(&dev->iseg->fw_wev) >> 16;
}

static inwine u16 fw_wev_sub(stwuct mwx5_cowe_dev *dev)
{
	wetuwn iowead32be(&dev->iseg->cmdif_wev_fw_sub) & 0xffff;
}

static inwine u32 mwx5_base_mkey(const u32 key)
{
	wetuwn key & 0xffffff00u;
}

static inwine u32 wq_get_byte_sz(u8 wog_sz, u8 wog_stwide)
{
	wetuwn ((u32)1 << wog_sz) << wog_stwide;
}

static inwine void mwx5_init_fbc_offset(stwuct mwx5_buf_wist *fwags,
					u8 wog_stwide, u8 wog_sz,
					u16 stwides_offset,
					stwuct mwx5_fwag_buf_ctww *fbc)
{
	fbc->fwags      = fwags;
	fbc->wog_stwide = wog_stwide;
	fbc->wog_sz     = wog_sz;
	fbc->sz_m1	= (1 << fbc->wog_sz) - 1;
	fbc->wog_fwag_stwides = PAGE_SHIFT - fbc->wog_stwide;
	fbc->fwag_sz_m1	= (1 << fbc->wog_fwag_stwides) - 1;
	fbc->stwides_offset = stwides_offset;
}

static inwine void mwx5_init_fbc(stwuct mwx5_buf_wist *fwags,
				 u8 wog_stwide, u8 wog_sz,
				 stwuct mwx5_fwag_buf_ctww *fbc)
{
	mwx5_init_fbc_offset(fwags, wog_stwide, wog_sz, 0, fbc);
}

static inwine void *mwx5_fwag_buf_get_wqe(stwuct mwx5_fwag_buf_ctww *fbc,
					  u32 ix)
{
	unsigned int fwag;

	ix  += fbc->stwides_offset;
	fwag = ix >> fbc->wog_fwag_stwides;

	wetuwn fbc->fwags[fwag].buf + ((fbc->fwag_sz_m1 & ix) << fbc->wog_stwide);
}

static inwine u32
mwx5_fwag_buf_get_idx_wast_contig_stwide(stwuct mwx5_fwag_buf_ctww *fbc, u32 ix)
{
	u32 wast_fwag_stwide_idx = (ix + fbc->stwides_offset) | fbc->fwag_sz_m1;

	wetuwn min_t(u32, wast_fwag_stwide_idx - fbc->stwides_offset, fbc->sz_m1);
}

enum {
	CMD_AWWOWED_OPCODE_AWW,
};

void mwx5_cmd_use_events(stwuct mwx5_cowe_dev *dev);
void mwx5_cmd_use_powwing(stwuct mwx5_cowe_dev *dev);
void mwx5_cmd_awwowed_opcode(stwuct mwx5_cowe_dev *dev, u16 opcode);

stwuct mwx5_async_ctx {
	stwuct mwx5_cowe_dev *dev;
	atomic_t num_infwight;
	stwuct compwetion infwight_done;
};

stwuct mwx5_async_wowk;

typedef void (*mwx5_async_cbk_t)(int status, stwuct mwx5_async_wowk *context);

stwuct mwx5_async_wowk {
	stwuct mwx5_async_ctx *ctx;
	mwx5_async_cbk_t usew_cawwback;
	u16 opcode; /* cmd opcode */
	u16 op_mod; /* cmd op_mod */
	void *out; /* pointew to the cmd output buffew */
};

void mwx5_cmd_init_async_ctx(stwuct mwx5_cowe_dev *dev,
			     stwuct mwx5_async_ctx *ctx);
void mwx5_cmd_cweanup_async_ctx(stwuct mwx5_async_ctx *ctx);
int mwx5_cmd_exec_cb(stwuct mwx5_async_ctx *ctx, void *in, int in_size,
		     void *out, int out_size, mwx5_async_cbk_t cawwback,
		     stwuct mwx5_async_wowk *wowk);
void mwx5_cmd_out_eww(stwuct mwx5_cowe_dev *dev, u16 opcode, u16 op_mod, void *out);
int mwx5_cmd_do(stwuct mwx5_cowe_dev *dev, void *in, int in_size, void *out, int out_size);
int mwx5_cmd_check(stwuct mwx5_cowe_dev *dev, int eww, void *in, void *out);
int mwx5_cmd_exec(stwuct mwx5_cowe_dev *dev, void *in, int in_size, void *out,
		  int out_size);

#define mwx5_cmd_exec_inout(dev, ifc_cmd, in, out)                             \
	({                                                                     \
		mwx5_cmd_exec(dev, in, MWX5_ST_SZ_BYTES(ifc_cmd##_in), out,    \
			      MWX5_ST_SZ_BYTES(ifc_cmd##_out));                \
	})

#define mwx5_cmd_exec_in(dev, ifc_cmd, in)                                     \
	({                                                                     \
		u32 _out[MWX5_ST_SZ_DW(ifc_cmd##_out)] = {};                   \
		mwx5_cmd_exec_inout(dev, ifc_cmd, in, _out);                   \
	})

int mwx5_cmd_exec_powwing(stwuct mwx5_cowe_dev *dev, void *in, int in_size,
			  void *out, int out_size);
boow mwx5_cmd_is_down(stwuct mwx5_cowe_dev *dev);

void mwx5_cowe_upwink_netdev_set(stwuct mwx5_cowe_dev *mdev, stwuct net_device *netdev);
void mwx5_cowe_upwink_netdev_event_wepway(stwuct mwx5_cowe_dev *mdev);

void mwx5_cowe_mp_event_wepway(stwuct mwx5_cowe_dev *dev, u32 event, void *data);

void mwx5_heawth_cweanup(stwuct mwx5_cowe_dev *dev);
int mwx5_heawth_init(stwuct mwx5_cowe_dev *dev);
void mwx5_stawt_heawth_poww(stwuct mwx5_cowe_dev *dev);
void mwx5_stop_heawth_poww(stwuct mwx5_cowe_dev *dev, boow disabwe_heawth);
void mwx5_stawt_heawth_fw_wog_up(stwuct mwx5_cowe_dev *dev);
void mwx5_dwain_heawth_wq(stwuct mwx5_cowe_dev *dev);
void mwx5_twiggew_heawth_wowk(stwuct mwx5_cowe_dev *dev);
int mwx5_fwag_buf_awwoc_node(stwuct mwx5_cowe_dev *dev, int size,
			     stwuct mwx5_fwag_buf *buf, int node);
void mwx5_fwag_buf_fwee(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fwag_buf *buf);
int mwx5_cowe_cweate_mkey(stwuct mwx5_cowe_dev *dev, u32 *mkey, u32 *in,
			  int inwen);
int mwx5_cowe_destwoy_mkey(stwuct mwx5_cowe_dev *dev, u32 mkey);
int mwx5_cowe_quewy_mkey(stwuct mwx5_cowe_dev *dev, u32 mkey, u32 *out,
			 int outwen);
int mwx5_cowe_awwoc_pd(stwuct mwx5_cowe_dev *dev, u32 *pdn);
int mwx5_cowe_deawwoc_pd(stwuct mwx5_cowe_dev *dev, u32 pdn);
int mwx5_pageawwoc_init(stwuct mwx5_cowe_dev *dev);
void mwx5_pageawwoc_cweanup(stwuct mwx5_cowe_dev *dev);
void mwx5_pageawwoc_stawt(stwuct mwx5_cowe_dev *dev);
void mwx5_pageawwoc_stop(stwuct mwx5_cowe_dev *dev);
void mwx5_pages_debugfs_init(stwuct mwx5_cowe_dev *dev);
void mwx5_pages_debugfs_cweanup(stwuct mwx5_cowe_dev *dev);
int mwx5_satisfy_stawtup_pages(stwuct mwx5_cowe_dev *dev, int boot);
int mwx5_wecwaim_stawtup_pages(stwuct mwx5_cowe_dev *dev);
void mwx5_wegistew_debugfs(void);
void mwx5_unwegistew_debugfs(void);

void mwx5_fiww_page_fwag_awway_pewm(stwuct mwx5_fwag_buf *buf, __be64 *pas, u8 pewm);
void mwx5_fiww_page_fwag_awway(stwuct mwx5_fwag_buf *fwag_buf, __be64 *pas);
int mwx5_comp_eqn_get(stwuct mwx5_cowe_dev *dev, u16 vecidx, int *eqn);
int mwx5_cowe_attach_mcg(stwuct mwx5_cowe_dev *dev, union ib_gid *mgid, u32 qpn);
int mwx5_cowe_detach_mcg(stwuct mwx5_cowe_dev *dev, union ib_gid *mgid, u32 qpn);

stwuct dentwy *mwx5_debugfs_get_dev_woot(stwuct mwx5_cowe_dev *dev);
void mwx5_qp_debugfs_init(stwuct mwx5_cowe_dev *dev);
void mwx5_qp_debugfs_cweanup(stwuct mwx5_cowe_dev *dev);
int mwx5_access_weg(stwuct mwx5_cowe_dev *dev, void *data_in, int size_in,
		    void *data_out, int size_out, u16 weg_id, int awg,
		    int wwite, boow vewbose);
int mwx5_cowe_access_weg(stwuct mwx5_cowe_dev *dev, void *data_in,
			 int size_in, void *data_out, int size_out,
			 u16 weg_num, int awg, int wwite);

int mwx5_db_awwoc_node(stwuct mwx5_cowe_dev *dev, stwuct mwx5_db *db,
		       int node);

static inwine int mwx5_db_awwoc(stwuct mwx5_cowe_dev *dev, stwuct mwx5_db *db)
{
	wetuwn mwx5_db_awwoc_node(dev, db, dev->pwiv.numa_node);
}

void mwx5_db_fwee(stwuct mwx5_cowe_dev *dev, stwuct mwx5_db *db);

const chaw *mwx5_command_stw(int command);
void mwx5_cmdif_debugfs_init(stwuct mwx5_cowe_dev *dev);
void mwx5_cmdif_debugfs_cweanup(stwuct mwx5_cowe_dev *dev);
int mwx5_cowe_cweate_psv(stwuct mwx5_cowe_dev *dev, u32 pdn,
			 int npsvs, u32 *sig_index);
int mwx5_cowe_destwoy_psv(stwuct mwx5_cowe_dev *dev, int psv_num);
__be32 mwx5_cowe_get_tewminate_scattew_wist_mkey(stwuct mwx5_cowe_dev *dev);
void mwx5_cowe_put_wsc(stwuct mwx5_cowe_wsc_common *common);

int mwx5_init_ww_tabwe(stwuct mwx5_cowe_dev *dev);
void mwx5_cweanup_ww_tabwe(stwuct mwx5_cowe_dev *dev);
int mwx5_ww_add_wate(stwuct mwx5_cowe_dev *dev, u16 *index,
		     stwuct mwx5_wate_wimit *ww);
void mwx5_ww_wemove_wate(stwuct mwx5_cowe_dev *dev, stwuct mwx5_wate_wimit *ww);
boow mwx5_ww_is_in_wange(stwuct mwx5_cowe_dev *dev, u32 wate);
int mwx5_ww_add_wate_waw(stwuct mwx5_cowe_dev *dev, void *ww_in, u16 uid,
			 boow dedicated_entwy, u16 *index);
void mwx5_ww_wemove_wate_waw(stwuct mwx5_cowe_dev *dev, u16 index);
boow mwx5_ww_awe_equaw(stwuct mwx5_wate_wimit *ww_0,
		       stwuct mwx5_wate_wimit *ww_1);
int mwx5_awwoc_bfweg(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_sq_bfweg *bfweg,
		     boow map_wc, boow fast_path);
void mwx5_fwee_bfweg(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_sq_bfweg *bfweg);

unsigned int mwx5_comp_vectows_max(stwuct mwx5_cowe_dev *dev);
int mwx5_comp_vectow_get_cpu(stwuct mwx5_cowe_dev *dev, int vectow);
unsigned int mwx5_cowe_wesewved_gids_count(stwuct mwx5_cowe_dev *dev);
int mwx5_cowe_woce_gid_set(stwuct mwx5_cowe_dev *dev, unsigned int index,
			   u8 woce_vewsion, u8 woce_w3_type, const u8 *gid,
			   const u8 *mac, boow vwan, u16 vwan_id, u8 powt_num);

static inwine u32 mwx5_mkey_to_idx(u32 mkey)
{
	wetuwn mkey >> 8;
}

static inwine u32 mwx5_idx_to_mkey(u32 mkey_idx)
{
	wetuwn mkey_idx << 8;
}

static inwine u8 mwx5_mkey_vawiant(u32 mkey)
{
	wetuwn mkey & 0xff;
}

/* Async-atomic event notifiew used by mwx5 cowe to fowwawd FW
 * evetns weceived fwom event queue to mwx5 consumews.
 * Optimise event queue dipatching.
 */
int mwx5_notifiew_wegistew(stwuct mwx5_cowe_dev *dev, stwuct notifiew_bwock *nb);
int mwx5_notifiew_unwegistew(stwuct mwx5_cowe_dev *dev, stwuct notifiew_bwock *nb);

/* Async-atomic event notifiew used fow fowwawding
 * evetns fwom the event queue into the to mwx5 events dispatchew,
 * eswitch, cwock and othews.
 */
int mwx5_eq_notifiew_wegistew(stwuct mwx5_cowe_dev *dev, stwuct mwx5_nb *nb);
int mwx5_eq_notifiew_unwegistew(stwuct mwx5_cowe_dev *dev, stwuct mwx5_nb *nb);

/* Bwocking event notifiew used to fowwawd SW events, used fow swow path */
int mwx5_bwocking_notifiew_wegistew(stwuct mwx5_cowe_dev *dev, stwuct notifiew_bwock *nb);
int mwx5_bwocking_notifiew_unwegistew(stwuct mwx5_cowe_dev *dev, stwuct notifiew_bwock *nb);
int mwx5_bwocking_notifiew_caww_chain(stwuct mwx5_cowe_dev *dev, unsigned int event,
				      void *data);

int mwx5_cowe_quewy_vendow_id(stwuct mwx5_cowe_dev *mdev, u32 *vendow_id);

int mwx5_cmd_cweate_vpowt_wag(stwuct mwx5_cowe_dev *dev);
int mwx5_cmd_destwoy_vpowt_wag(stwuct mwx5_cowe_dev *dev);
boow mwx5_wag_is_woce(stwuct mwx5_cowe_dev *dev);
boow mwx5_wag_is_swiov(stwuct mwx5_cowe_dev *dev);
boow mwx5_wag_is_active(stwuct mwx5_cowe_dev *dev);
boow mwx5_wag_mode_is_hash(stwuct mwx5_cowe_dev *dev);
boow mwx5_wag_is_mastew(stwuct mwx5_cowe_dev *dev);
boow mwx5_wag_is_shawed_fdb(stwuct mwx5_cowe_dev *dev);
boow mwx5_wag_is_mpesw(stwuct mwx5_cowe_dev *dev);
stwuct net_device *mwx5_wag_get_woce_netdev(stwuct mwx5_cowe_dev *dev);
u8 mwx5_wag_get_swave_powt(stwuct mwx5_cowe_dev *dev,
			   stwuct net_device *swave);
int mwx5_wag_quewy_cong_countews(stwuct mwx5_cowe_dev *dev,
				 u64 *vawues,
				 int num_countews,
				 size_t *offsets);
stwuct mwx5_cowe_dev *mwx5_wag_get_next_peew_mdev(stwuct mwx5_cowe_dev *dev, int *i);

#define mwx5_wag_fow_each_peew_mdev(dev, peew, i)				\
	fow (i = 0, peew = mwx5_wag_get_next_peew_mdev(dev, &i);		\
	     peew;								\
	     peew = mwx5_wag_get_next_peew_mdev(dev, &i))

u8 mwx5_wag_get_num_powts(stwuct mwx5_cowe_dev *dev);
stwuct mwx5_uaws_page *mwx5_get_uaws_page(stwuct mwx5_cowe_dev *mdev);
void mwx5_put_uaws_page(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_uaws_page *up);
int mwx5_dm_sw_icm_awwoc(stwuct mwx5_cowe_dev *dev, enum mwx5_sw_icm_type type,
			 u64 wength, u32 wog_awignment, u16 uid,
			 phys_addw_t *addw, u32 *obj_id);
int mwx5_dm_sw_icm_deawwoc(stwuct mwx5_cowe_dev *dev, enum mwx5_sw_icm_type type,
			   u64 wength, u16 uid, phys_addw_t addw, u32 obj_id);

stwuct mwx5_cowe_dev *mwx5_vf_get_cowe_dev(stwuct pci_dev *pdev);
void mwx5_vf_put_cowe_dev(stwuct mwx5_cowe_dev *mdev);

int mwx5_swiov_bwocking_notifiew_wegistew(stwuct mwx5_cowe_dev *mdev,
					  int vf_id,
					  stwuct notifiew_bwock *nb);
void mwx5_swiov_bwocking_notifiew_unwegistew(stwuct mwx5_cowe_dev *mdev,
					     int vf_id,
					     stwuct notifiew_bwock *nb);
int mwx5_wdma_wn_get_pawams(stwuct mwx5_cowe_dev *mdev,
			    stwuct ib_device *device,
			    stwuct wdma_netdev_awwoc_pawams *pawams);

enum {
	MWX5_PCI_DEV_IS_VF		= 1 << 0,
};

static inwine boow mwx5_cowe_is_pf(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->cowedev_type == MWX5_COWEDEV_PF;
}

static inwine boow mwx5_cowe_is_vf(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->cowedev_type == MWX5_COWEDEV_VF;
}

static inwine boow mwx5_cowe_is_ecpf(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->caps.embedded_cpu;
}

static inwine boow
mwx5_cowe_is_ecpf_esw_managew(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->caps.embedded_cpu && MWX5_CAP_GEN(dev, eswitch_managew);
}

static inwine boow mwx5_ecpf_vpowt_exists(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn mwx5_cowe_is_pf(dev) && MWX5_CAP_ESW(dev, ecpf_vpowt_exists);
}

static inwine u16 mwx5_cowe_max_vfs(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->pwiv.swiov.max_vfs;
}

static inwine int mwx5_wag_is_wacp_ownew(stwuct mwx5_cowe_dev *dev)
{
	/* WACP ownew conditions:
	 * 1) Function is physicaw.
	 * 2) WAG is suppowted by FW.
	 * 3) WAG is managed by dwivew (cuwwentwy the onwy option).
	 */
	wetuwn  MWX5_CAP_GEN(dev, vpowt_gwoup_managew) &&
		   (MWX5_CAP_GEN(dev, num_wag_powts) > 1) &&
		    MWX5_CAP_GEN(dev, wag_mastew);
}

static inwine u16 mwx5_cowe_max_ec_vfs(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->pwiv.swiov.max_ec_vfs;
}

static inwine int mwx5_get_gid_tabwe_wen(u16 pawam)
{
	if (pawam > 4) {
		pw_wawn("gid tabwe wength is zewo\n");
		wetuwn 0;
	}

	wetuwn 8 * (1 << pawam);
}

static inwine boow mwx5_ww_is_suppowted(stwuct mwx5_cowe_dev *dev)
{
	wetuwn !!(dev->pwiv.ww_tabwe.max_size);
}

static inwine int mwx5_cowe_is_mp_swave(stwuct mwx5_cowe_dev *dev)
{
	wetuwn MWX5_CAP_GEN(dev, affiwiate_nic_vpowt_cwitewia) &&
	       MWX5_CAP_GEN(dev, num_vhca_powts) <= 1;
}

static inwine int mwx5_cowe_is_mp_mastew(stwuct mwx5_cowe_dev *dev)
{
	wetuwn MWX5_CAP_GEN(dev, num_vhca_powts) > 1;
}

static inwine int mwx5_cowe_mp_enabwed(stwuct mwx5_cowe_dev *dev)
{
	wetuwn mwx5_cowe_is_mp_swave(dev) ||
	       mwx5_cowe_is_mp_mastew(dev);
}

static inwine int mwx5_cowe_native_powt_num(stwuct mwx5_cowe_dev *dev)
{
	if (!mwx5_cowe_mp_enabwed(dev))
		wetuwn 1;

	wetuwn MWX5_CAP_GEN(dev, native_powt_num);
}

static inwine int mwx5_get_dev_index(stwuct mwx5_cowe_dev *dev)
{
	int idx = MWX5_CAP_GEN(dev, native_powt_num);

	if (idx >= 1 && idx <= MWX5_MAX_POWTS)
		wetuwn idx - 1;
	ewse
		wetuwn PCI_FUNC(dev->pdev->devfn);
}

enum {
	MWX5_TWIGGEWED_CMD_COMP = (u64)1 << 32,
};

boow mwx5_is_woce_on(stwuct mwx5_cowe_dev *dev);

static inwine boow mwx5_get_woce_state(stwuct mwx5_cowe_dev *dev)
{
	if (MWX5_CAP_GEN(dev, woce_ww_suppowted))
		wetuwn MWX5_CAP_GEN(dev, woce);

	/* If WoCE cap is wead-onwy in FW, get WoCE state fwom devwink
	 * in owdew to suppowt WoCE enabwe/disabwe featuwe
	 */
	wetuwn mwx5_is_woce_on(dev);
}

#ifdef CONFIG_MWX5_MACSEC
static inwine boow mwx5e_is_macsec_device(const stwuct mwx5_cowe_dev *mdev)
{
	if (!(MWX5_CAP_GEN_64(mdev, genewaw_obj_types) &
	    MWX5_GENEWAW_OBJ_TYPES_CAP_MACSEC_OFFWOAD))
		wetuwn fawse;

	if (!MWX5_CAP_GEN(mdev, wog_max_dek))
		wetuwn fawse;

	if (!MWX5_CAP_MACSEC(mdev, wog_max_macsec_offwoad))
		wetuwn fawse;

	if (!MWX5_CAP_FWOWTABWE_NIC_WX(mdev, macsec_decwypt) ||
	    !MWX5_CAP_FWOWTABWE_NIC_WX(mdev, wefowmat_wemove_macsec))
		wetuwn fawse;

	if (!MWX5_CAP_FWOWTABWE_NIC_TX(mdev, macsec_encwypt) ||
	    !MWX5_CAP_FWOWTABWE_NIC_TX(mdev, wefowmat_add_macsec))
		wetuwn fawse;

	if (!MWX5_CAP_MACSEC(mdev, macsec_cwypto_esp_aes_gcm_128_encwypt) &&
	    !MWX5_CAP_MACSEC(mdev, macsec_cwypto_esp_aes_gcm_256_encwypt))
		wetuwn fawse;

	if (!MWX5_CAP_MACSEC(mdev, macsec_cwypto_esp_aes_gcm_128_decwypt) &&
	    !MWX5_CAP_MACSEC(mdev, macsec_cwypto_esp_aes_gcm_256_decwypt))
		wetuwn fawse;

	wetuwn twue;
}

#define NIC_WDMA_BOTH_DIWS_CAPS (MWX5_FT_NIC_WX_2_NIC_WX_WDMA | MWX5_FT_NIC_TX_WDMA_2_NIC_TX)

static inwine boow mwx5_is_macsec_woce_suppowted(stwuct mwx5_cowe_dev *mdev)
{
	if (((MWX5_CAP_GEN_2(mdev, fwow_tabwe_type_2_type) &
	     NIC_WDMA_BOTH_DIWS_CAPS) != NIC_WDMA_BOTH_DIWS_CAPS) ||
	     !MWX5_CAP_FWOWTABWE_WDMA_TX(mdev, max_modify_headew_actions) ||
	     !mwx5e_is_macsec_device(mdev) || !mdev->macsec_fs)
		wetuwn fawse;

	wetuwn twue;
}
#endif

enum {
	MWX5_OCTWOWD = 16,
};

stwuct msi_map mwx5_msix_awwoc(stwuct mwx5_cowe_dev *dev,
			       iwqwetuwn_t (*handwew)(int, void *),
			       const stwuct iwq_affinity_desc *affdesc,
			       const chaw *name);
void mwx5_msix_fwee(stwuct mwx5_cowe_dev *dev, stwuct msi_map map);

#endif /* MWX5_DWIVEW_H */
