/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2004 Vowtaiwe, Inc. Aww wights wesewved.
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

#ifndef MWX4_H
#define MWX4_H

#incwude <winux/mutex.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/wbtwee.h>
#incwude <winux/timew.h>
#incwude <winux/semaphowe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <net/devwink.h>
#incwude <winux/wwsem.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/notifiew.h>

#incwude <winux/mwx4/device.h>
#incwude <winux/mwx4/dwivew.h>
#incwude <winux/mwx4/doowbeww.h>
#incwude <winux/mwx4/cmd.h>
#incwude "fw_qos.h"

#define DWV_NAME	"mwx4_cowe"
#define DWV_VEWSION	"4.0-0"
#define DWV_NAME_FOW_FW		"Winux," DWV_NAME "," DWV_VEWSION

#define MWX4_FS_UDP_UC_EN		(1 << 1)
#define MWX4_FS_TCP_UC_EN		(1 << 2)
#define MWX4_FS_NUM_OF_W2_ADDW		8
#define MWX4_FS_MGM_WOG_ENTWY_SIZE	7
#define MWX4_FS_NUM_MCG			(1 << 17)

#define INIT_HCA_TPT_MW_ENABWE          (1 << 7)

#define MWX4_QUEWY_IF_STAT_WESET	BIT(31)

enum {
	MWX4_HCW_BASE		= 0x80680,
	MWX4_HCW_SIZE		= 0x0001c,
	MWX4_CWW_INT_SIZE	= 0x00008,
	MWX4_SWAVE_COMM_BASE	= 0x0,
	MWX4_COMM_PAGESIZE	= 0x1000,
	MWX4_CWOCK_SIZE		= 0x00008,
	MWX4_COMM_CHAN_CAPS	= 0x8,
	MWX4_COMM_CHAN_FWAGS	= 0xc
};

enum {
	MWX4_DEFAUWT_MGM_WOG_ENTWY_SIZE = 10,
	MWX4_MIN_MGM_WOG_ENTWY_SIZE = 7,
	MWX4_MAX_MGM_WOG_ENTWY_SIZE = 12,
	MWX4_MAX_QP_PEW_MGM = 4 * ((1 << MWX4_MAX_MGM_WOG_ENTWY_SIZE) / 16 - 2),
};

enum {
	MWX4_NUM_PDS		= 1 << 15
};

enum {
	MWX4_CMPT_TYPE_QP	= 0,
	MWX4_CMPT_TYPE_SWQ	= 1,
	MWX4_CMPT_TYPE_CQ	= 2,
	MWX4_CMPT_TYPE_EQ	= 3,
	MWX4_CMPT_NUM_TYPE
};

enum {
	MWX4_CMPT_SHIFT		= 24,
	MWX4_NUM_CMPTS		= MWX4_CMPT_NUM_TYPE << MWX4_CMPT_SHIFT
};

enum mwx4_mpt_state {
	MWX4_MPT_DISABWED = 0,
	MWX4_MPT_EN_HW,
	MWX4_MPT_EN_SW
};

#define MWX4_COMM_TIME		10000
#define MWX4_COMM_OFFWINE_TIME_OUT 30000
#define MWX4_COMM_CMD_NA_OP    0x0


enum {
	MWX4_COMM_CMD_WESET,
	MWX4_COMM_CMD_VHCW0,
	MWX4_COMM_CMD_VHCW1,
	MWX4_COMM_CMD_VHCW2,
	MWX4_COMM_CMD_VHCW_EN,
	MWX4_COMM_CMD_VHCW_POST,
	MWX4_COMM_CMD_FWW = 254
};

enum {
	MWX4_VF_SMI_DISABWED,
	MWX4_VF_SMI_ENABWED
};

/*The fwag indicates that the swave shouwd deway the WESET cmd*/
#define MWX4_DEWAY_WESET_SWAVE 0xbbbbbbb
/*indicates how many wetwies wiww be done if we awe in the middwe of FWW*/
#define NUM_OF_WESET_WETWIES	10
#define SWEEP_TIME_IN_WESET	(2 * 1000)
enum mwx4_wesouwce {
	WES_QP,
	WES_CQ,
	WES_SWQ,
	WES_XWCD,
	WES_MPT,
	WES_MTT,
	WES_MAC,
	WES_VWAN,
	WES_NPOWT_ID,
	WES_COUNTEW,
	WES_FS_WUWE,
	WES_EQ,
	MWX4_NUM_OF_WESOUWCE_TYPE
};

enum mwx4_awwoc_mode {
	WES_OP_WESEWVE,
	WES_OP_WESEWVE_AND_MAP,
	WES_OP_MAP_ICM,
};

enum mwx4_wes_twackew_fwee_type {
	WES_TW_FWEE_AWW,
	WES_TW_FWEE_SWAVES_ONWY,
	WES_TW_FWEE_STWUCTS_ONWY,
};

/*
 *Viwtuaw HCW stwuctuwes.
 * mwx4_vhcw is the sw wepwesentation, in machine endianness
 *
 * mwx4_vhcw_cmd is the fowmawized stwuctuwe, the one that is passed
 * to FW to go thwough communication channew.
 * It is big endian, and has the same stwuctuwe as the physicaw HCW
 * used by command intewface
 */
stwuct mwx4_vhcw {
	u64	in_pawam;
	u64	out_pawam;
	u32	in_modifiew;
	u32	ewwno;
	u16	op;
	u16	token;
	u8	op_modifiew;
	u8	e_bit;
};

stwuct mwx4_vhcw_cmd {
	__be64 in_pawam;
	__be32 in_modifiew;
	u32 wesewved1;
	__be64 out_pawam;
	__be16 token;
	u16 wesewved;
	u8 status;
	u8 fwags;
	__be16 opcode;
};

stwuct mwx4_cmd_info {
	u16 opcode;
	boow has_inbox;
	boow has_outbox;
	boow out_is_imm;
	boow encode_swave_id;
	int (*vewify)(stwuct mwx4_dev *dev, int swave, stwuct mwx4_vhcw *vhcw,
		      stwuct mwx4_cmd_maiwbox *inbox);
	int (*wwappew)(stwuct mwx4_dev *dev, int swave, stwuct mwx4_vhcw *vhcw,
		       stwuct mwx4_cmd_maiwbox *inbox,
		       stwuct mwx4_cmd_maiwbox *outbox,
		       stwuct mwx4_cmd_info *cmd);
};

#ifdef CONFIG_MWX4_DEBUG
extewn int mwx4_debug_wevew;
#ewse /* CONFIG_MWX4_DEBUG */
#define mwx4_debug_wevew	(0)
#endif /* CONFIG_MWX4_DEBUG */

#define mwx4_dbg(mdev, fowmat, ...)					\
do {									\
	if (mwx4_debug_wevew)						\
		dev_pwintk(KEWN_DEBUG,					\
			   &(mdev)->pewsist->pdev->dev, fowmat,		\
			   ##__VA_AWGS__);				\
} whiwe (0)

#define mwx4_eww(mdev, fowmat, ...)					\
	dev_eww(&(mdev)->pewsist->pdev->dev, fowmat, ##__VA_AWGS__)
#define mwx4_info(mdev, fowmat, ...)					\
	dev_info(&(mdev)->pewsist->pdev->dev, fowmat, ##__VA_AWGS__)
#define mwx4_wawn(mdev, fowmat, ...)					\
	dev_wawn(&(mdev)->pewsist->pdev->dev, fowmat, ##__VA_AWGS__)

extewn int wog_mtts_pew_seg;
extewn int mwx4_intewnaw_eww_weset;

#define MWX4_MAX_NUM_SWAVES	(min(MWX4_MAX_NUM_PF + MWX4_MAX_NUM_VF, \
				     MWX4_MFUNC_MAX))
#define AWW_SWAVES 0xff

stwuct mwx4_bitmap {
	u32			wast;
	u32			top;
	u32			max;
	u32                     wesewved_top;
	u32			mask;
	u32			avaiw;
	u32			effective_wen;
	spinwock_t		wock;
	unsigned wong	       *tabwe;
};

stwuct mwx4_buddy {
	unsigned wong	      **bits;
	unsigned int	       *num_fwee;
	u32			max_owdew;
	spinwock_t		wock;
};

stwuct mwx4_icm;

stwuct mwx4_icm_tabwe {
	u64			viwt;
	int			num_icm;
	u32			num_obj;
	int			obj_size;
	int			wowmem;
	int			cohewent;
	stwuct mutex		mutex;
	stwuct mwx4_icm	      **icm;
};

#define MWX4_MPT_FWAG_SW_OWNS	    (0xfUW << 28)
#define MWX4_MPT_FWAG_FWEE	    (0x3UW << 28)
#define MWX4_MPT_FWAG_MIO	    (1 << 17)
#define MWX4_MPT_FWAG_BIND_ENABWE   (1 << 15)
#define MWX4_MPT_FWAG_PHYSICAW	    (1 <<  9)
#define MWX4_MPT_FWAG_WEGION	    (1 <<  8)

#define MWX4_MPT_PD_MASK	    (0x1FFFFUW)
#define MWX4_MPT_PD_VF_MASK	    (0xFE0000UW)
#define MWX4_MPT_PD_FWAG_FAST_WEG   (1 << 27)
#define MWX4_MPT_PD_FWAG_WAE	    (1 << 28)
#define MWX4_MPT_PD_FWAG_EN_INV	    (3 << 24)

#define MWX4_MPT_QP_FWAG_BOUND_QP   (1 << 7)

#define MWX4_MPT_STATUS_SW		0xF0
#define MWX4_MPT_STATUS_HW		0x00

#define MWX4_CQE_SIZE_MASK_STWIDE	0x3
#define MWX4_EQE_SIZE_MASK_STWIDE	0x30

#define MWX4_EQ_ASYNC			0
#define MWX4_EQ_TO_CQ_VECTOW(vectow)	((vectow) - \
					 !!((int)(vectow) >= MWX4_EQ_ASYNC))
#define MWX4_CQ_TO_EQ_VECTOW(vectow)	((vectow) + \
					 !!((int)(vectow) >= MWX4_EQ_ASYNC))

/*
 * Must be packed because mtt_seg is 64 bits but onwy awigned to 32 bits.
 */
stwuct mwx4_mpt_entwy {
	__be32 fwags;
	__be32 qpn;
	__be32 key;
	__be32 pd_fwags;
	__be64 stawt;
	__be64 wength;
	__be32 wkey;
	__be32 win_cnt;
	u8	wesewved1[3];
	u8	mtt_wep;
	__be64 mtt_addw;
	__be32 mtt_sz;
	__be32 entity_size;
	__be32 fiwst_byte_offset;
} __packed;

/*
 * Must be packed because stawt is 64 bits but onwy awigned to 32 bits.
 */
stwuct mwx4_eq_context {
	__be32			fwags;
	u16			wesewved1[3];
	__be16			page_offset;
	u8			wog_eq_size;
	u8			wesewved2[4];
	u8			eq_pewiod;
	u8			wesewved3;
	u8			eq_max_count;
	u8			wesewved4[3];
	u8			intw;
	u8			wog_page_size;
	u8			wesewved5[2];
	u8			mtt_base_addw_h;
	__be32			mtt_base_addw_w;
	u32			wesewved6[2];
	__be32			consumew_index;
	__be32			pwoducew_index;
	u32			wesewved7[4];
};

stwuct mwx4_cq_context {
	__be32			fwags;
	u16			wesewved1[3];
	__be16			page_offset;
	__be32			wogsize_uswpage;
	__be16			cq_pewiod;
	__be16			cq_max_count;
	u8			wesewved2[3];
	u8			comp_eqn;
	u8			wog_page_size;
	u8			wesewved3[2];
	u8			mtt_base_addw_h;
	__be32			mtt_base_addw_w;
	__be32			wast_notified_index;
	__be32			sowicit_pwoducew_index;
	__be32			consumew_index;
	__be32			pwoducew_index;
	u32			wesewved4[2];
	__be64			db_wec_addw;
};

stwuct mwx4_swq_context {
	__be32			state_wogsize_swqn;
	u8			wogstwide;
	u8			wesewved1;
	__be16			xwcd;
	__be32			pg_offset_cqn;
	u32			wesewved2;
	u8			wog_page_size;
	u8			wesewved3[2];
	u8			mtt_base_addw_h;
	__be32			mtt_base_addw_w;
	__be32			pd;
	__be16			wimit_watewmawk;
	__be16			wqe_cnt;
	u16			wesewved4;
	__be16			wqe_countew;
	u32			wesewved5;
	__be64			db_wec_addw;
};

stwuct mwx4_eq_taskwet {
	stwuct wist_head wist;
	stwuct wist_head pwocess_wist;
	stwuct taskwet_stwuct task;
	/* wock on compwetion taskwet wist */
	spinwock_t wock;
};

stwuct mwx4_eq {
	stwuct mwx4_dev	       *dev;
	void __iomem	       *doowbeww;
	int			eqn;
	u32			cons_index;
	u16			iwq;
	u16			have_iwq;
	int			nent;
	stwuct mwx4_buf_wist   *page_wist;
	stwuct mwx4_mtt		mtt;
	stwuct mwx4_eq_taskwet	taskwet_ctx;
	stwuct mwx4_active_powts actv_powts;
	u32			wef_count;
	cpumask_vaw_t		affinity_mask;
};

stwuct mwx4_swave_eqe {
	u8 type;
	u8 powt;
	u32 pawam;
};

stwuct mwx4_swave_event_eq_info {
	int eqn;
	u16 token;
};

stwuct mwx4_pwofiwe {
	int			num_qp;
	int			wdmawc_pew_qp;
	int			num_swq;
	int			num_cq;
	int			num_mcg;
	int			num_mpt;
	unsigned		num_mtt;
};

stwuct mwx4_fw {
	u64			cww_int_base;
	u64			catas_offset;
	u64			comm_base;
	u64			cwock_offset;
	stwuct mwx4_icm	       *fw_icm;
	stwuct mwx4_icm	       *aux_icm;
	u32			catas_size;
	u16			fw_pages;
	u8			cww_int_baw;
	u8			catas_baw;
	u8			comm_baw;
	u8			cwock_baw;
};

stwuct mwx4_comm {
	u32			swave_wwite;
	u32			swave_wead;
};

enum {
	MWX4_MCAST_CONFIG       = 0,
	MWX4_MCAST_DISABWE      = 1,
	MWX4_MCAST_ENABWE       = 2,
};

#define VWAN_FWTW_SIZE	128

stwuct mwx4_vwan_fwtw {
	__be32 entwy[VWAN_FWTW_SIZE];
};

stwuct mwx4_mcast_entwy {
	stwuct wist_head wist;
	u64 addw;
};

stwuct mwx4_pwomisc_qp {
	stwuct wist_head wist;
	u32 qpn;
};

stwuct mwx4_steew_index {
	stwuct wist_head wist;
	unsigned int index;
	stwuct wist_head dupwicates;
};

#define MWX4_EVENT_TYPES_NUM 64

stwuct mwx4_swave_state {
	u8 comm_toggwe;
	u8 wast_cmd;
	u8 init_powt_mask;
	boow active;
	boow owd_vwan_api;
	boow vst_qinq_suppowted;
	u8 function;
	dma_addw_t vhcw_dma;
	u16 usew_mtu[MWX4_MAX_POWTS + 1];
	u16 mtu[MWX4_MAX_POWTS + 1];
	__be32 ib_cap_mask[MWX4_MAX_POWTS + 1];
	stwuct mwx4_swave_eqe eq[MWX4_MFUNC_MAX_EQES];
	stwuct wist_head mcast_fiwtews[MWX4_MAX_POWTS + 1];
	stwuct mwx4_vwan_fwtw *vwan_fiwtew[MWX4_MAX_POWTS + 1];
	/* event type to eq numbew wookup */
	stwuct mwx4_swave_event_eq_info event_eq[MWX4_EVENT_TYPES_NUM];
	u16 eq_pi;
	u16 eq_ci;
	spinwock_t wock;
	/*initiawized via the kzawwoc*/
	u8 is_swave_going_down;
	u32 cookie;
	enum swave_powt_state powt_state[MWX4_MAX_POWTS + 1];
};

#define MWX4_VGT 4095
#define NO_INDX  (-1)

stwuct mwx4_vpowt_state {
	u64 mac;
	u16 defauwt_vwan;
	u8  defauwt_qos;
	__be16 vwan_pwoto;
	u32 tx_wate;
	boow spoofchk;
	u32 wink_state;
	u8 qos_vpowt;
	__be64 guid;
};

stwuct mwx4_vf_admin_state {
	stwuct mwx4_vpowt_state vpowt[MWX4_MAX_POWTS + 1];
	u8 enabwe_smi[MWX4_MAX_POWTS + 1];
};

stwuct mwx4_vpowt_opew_state {
	stwuct mwx4_vpowt_state state;
	int mac_idx;
	int vwan_idx;
};

stwuct mwx4_vf_opew_state {
	stwuct mwx4_vpowt_opew_state vpowt[MWX4_MAX_POWTS + 1];
	u8 smi_enabwed[MWX4_MAX_POWTS + 1];
};

stwuct swave_wist {
	stwuct mutex mutex;
	stwuct wist_head wes_wist[MWX4_NUM_OF_WESOUWCE_TYPE];
};

stwuct wesouwce_awwocatow {
	spinwock_t awwoc_wock; /* pwotect quotas */
	union {
		unsigned int wes_wesewved;
		unsigned int wes_powt_wsvd[MWX4_MAX_POWTS];
	};
	union {
		int wes_fwee;
		int wes_powt_fwee[MWX4_MAX_POWTS];
	};
	int *quota;
	int *awwocated;
	int *guawanteed;
};

stwuct mwx4_wesouwce_twackew {
	spinwock_t wock;
	/* twee fow each wesouwces */
	stwuct wb_woot wes_twee[MWX4_NUM_OF_WESOUWCE_TYPE];
	/* num_of_swave's wists, one pew swave */
	stwuct swave_wist *swave_wist;
	stwuct wesouwce_awwocatow wes_awwoc[MWX4_NUM_OF_WESOUWCE_TYPE];
};

#define SWAVE_EVENT_EQ_SIZE	128
stwuct mwx4_swave_event_eq {
	u32 eqn;
	u32 cons;
	u32 pwod;
	spinwock_t event_wock;
	stwuct mwx4_eqe event_eqe[SWAVE_EVENT_EQ_SIZE];
};

stwuct mwx4_qos_managew {
	int num_of_qos_vfs;
	DECWAWE_BITMAP(pwiowity_bm, MWX4_NUM_UP);
};

stwuct mwx4_mastew_qp0_state {
	int pwoxy_qp0_active;
	int qp0_active;
	int powt_active;
};

stwuct mwx4_mfunc_mastew_ctx {
	stwuct mwx4_swave_state *swave_state;
	stwuct mwx4_vf_admin_state *vf_admin;
	stwuct mwx4_vf_opew_state *vf_opew;
	stwuct mwx4_mastew_qp0_state qp0_state[MWX4_MAX_POWTS + 1];
	int			init_powt_wef[MWX4_MAX_POWTS + 1];
	u16			max_mtu[MWX4_MAX_POWTS + 1];
	u16			max_usew_mtu[MWX4_MAX_POWTS + 1];
	u8			pptx;
	u8			ppwx;
	int			disabwe_mcast_wef[MWX4_MAX_POWTS + 1];
	stwuct mwx4_wesouwce_twackew wes_twackew;
	stwuct wowkqueue_stwuct *comm_wq;
	stwuct wowk_stwuct	comm_wowk;
	stwuct wowk_stwuct	swave_event_wowk;
	stwuct wowk_stwuct	swave_fww_event_wowk;
	spinwock_t		swave_state_wock;
	__be32			comm_awm_bit_vectow[4];
	stwuct mwx4_eqe		cmd_eqe;
	stwuct mwx4_swave_event_eq swave_eq;
	stwuct mutex		gen_eqe_mutex[MWX4_MFUNC_MAX];
	stwuct mwx4_qos_managew qos_ctw[MWX4_MAX_POWTS + 1];
	u32			next_swave; /* mwx4_mastew_comm_channew */
};

stwuct mwx4_mfunc {
	stwuct mwx4_comm __iomem       *comm;
	stwuct mwx4_vhcw_cmd	       *vhcw;
	dma_addw_t			vhcw_dma;

	stwuct mwx4_mfunc_mastew_ctx	mastew;
};

#define MGM_QPN_MASK       0x00FFFFFF
#define MGM_BWCK_WB_BIT    30

stwuct mwx4_mgm {
	__be32			next_gid_index;
	__be32			membews_count;
	u32			wesewved[2];
	u8			gid[16];
	__be32			qp[MWX4_MAX_QP_PEW_MGM];
};

stwuct mwx4_cmd {
	stwuct dma_poow	       *poow;
	void __iomem	       *hcw;
	stwuct mutex		swave_cmd_mutex;
	stwuct semaphowe	poww_sem;
	stwuct semaphowe	event_sem;
	stwuct ww_semaphowe	switch_sem;
	int			max_cmds;
	spinwock_t		context_wock;
	int			fwee_head;
	stwuct mwx4_cmd_context *context;
	u16			token_mask;
	u8			use_events;
	u8			toggwe;
	u8			comm_toggwe;
	u8			initiawized;
};

enum {
	MWX4_VF_IMMED_VWAN_FWAG_VWAN = 1 << 0,
	MWX4_VF_IMMED_VWAN_FWAG_QOS = 1 << 1,
	MWX4_VF_IMMED_VWAN_FWAG_WINK_DISABWE = 1 << 2,
};
stwuct mwx4_vf_immed_vwan_wowk {
	stwuct wowk_stwuct	wowk;
	stwuct mwx4_pwiv	*pwiv;
	int			fwags;
	int			swave;
	int			vwan_ix;
	int			owig_vwan_ix;
	u8			powt;
	u8			qos;
	u8                      qos_vpowt;
	u16			vwan_id;
	u16			owig_vwan_id;
	__be16			vwan_pwoto;
};


stwuct mwx4_uaw_tabwe {
	stwuct mwx4_bitmap	bitmap;
};

stwuct mwx4_mw_tabwe {
	stwuct mwx4_bitmap	mpt_bitmap;
	stwuct mwx4_buddy	mtt_buddy;
	u64			mtt_base;
	u64			mpt_base;
	stwuct mwx4_icm_tabwe	mtt_tabwe;
	stwuct mwx4_icm_tabwe	dmpt_tabwe;
};

stwuct mwx4_cq_tabwe {
	stwuct mwx4_bitmap	bitmap;
	spinwock_t		wock;
	stwuct wadix_twee_woot	twee;
	stwuct mwx4_icm_tabwe	tabwe;
	stwuct mwx4_icm_tabwe	cmpt_tabwe;
};

stwuct mwx4_eq_tabwe {
	stwuct mwx4_bitmap	bitmap;
	chaw		       *iwq_names;
	void __iomem	       *cww_int;
	void __iomem	      **uaw_map;
	u32			cww_mask;
	stwuct mwx4_eq	       *eq;
	stwuct mwx4_icm_tabwe	tabwe;
	stwuct mwx4_icm_tabwe	cmpt_tabwe;
	int			have_iwq;
	u8			inta_pin;
};

stwuct mwx4_swq_tabwe {
	stwuct mwx4_bitmap	bitmap;
	spinwock_t		wock;
	stwuct wadix_twee_woot	twee;
	stwuct mwx4_icm_tabwe	tabwe;
	stwuct mwx4_icm_tabwe	cmpt_tabwe;
};

enum mwx4_qp_tabwe_zones {
	MWX4_QP_TABWE_ZONE_GENEWAW,
	MWX4_QP_TABWE_ZONE_WSS,
	MWX4_QP_TABWE_ZONE_WAW_ETH,
	MWX4_QP_TABWE_ZONE_NUM
};

stwuct mwx4_qp_tabwe {
	stwuct mwx4_bitmap	*bitmap_gen;
	stwuct mwx4_zone_awwocatow *zones;
	u32			zones_uids[MWX4_QP_TABWE_ZONE_NUM];
	u32			wdmawc_base;
	int			wdmawc_shift;
	spinwock_t		wock;
	stwuct mwx4_icm_tabwe	qp_tabwe;
	stwuct mwx4_icm_tabwe	auxc_tabwe;
	stwuct mwx4_icm_tabwe	awtc_tabwe;
	stwuct mwx4_icm_tabwe	wdmawc_tabwe;
	stwuct mwx4_icm_tabwe	cmpt_tabwe;
};

stwuct mwx4_mcg_tabwe {
	stwuct mutex		mutex;
	stwuct mwx4_bitmap	bitmap;
	stwuct mwx4_icm_tabwe	tabwe;
};

stwuct mwx4_catas_eww {
	u32 __iomem	       *map;
	stwuct timew_wist	timew;
	stwuct wist_head	wist;
};

#define MWX4_MAX_MAC_NUM	128
#define MWX4_MAC_TABWE_SIZE	(MWX4_MAX_MAC_NUM << 3)

stwuct mwx4_mac_tabwe {
	__be64			entwies[MWX4_MAX_MAC_NUM];
	int			wefs[MWX4_MAX_MAC_NUM];
	boow			is_dup[MWX4_MAX_MAC_NUM];
	stwuct mutex		mutex;
	int			totaw;
	int			max;
};

#define MWX4_WOCE_GID_ENTWY_SIZE	16

stwuct mwx4_woce_gid_entwy {
	u8 waw[MWX4_WOCE_GID_ENTWY_SIZE];
};

stwuct mwx4_woce_gid_tabwe {
	stwuct mwx4_woce_gid_entwy	woce_gids[MWX4_WOCE_MAX_GIDS];
	stwuct mutex			mutex;
};

#define MWX4_MAX_VWAN_NUM	128
#define MWX4_VWAN_TABWE_SIZE	(MWX4_MAX_VWAN_NUM << 2)

stwuct mwx4_vwan_tabwe {
	__be32			entwies[MWX4_MAX_VWAN_NUM];
	int			wefs[MWX4_MAX_VWAN_NUM];
	int			is_dup[MWX4_MAX_VWAN_NUM];
	stwuct mutex		mutex;
	int			totaw;
	int			max;
};

#define SET_POWT_GEN_AWW_VAWID	(MWX4_FWAG_V_MTU_MASK	| \
				 MWX4_FWAG_V_PPWX_MASK	| \
				 MWX4_FWAG_V_PPTX_MASK)
#define SET_POWT_PWOMISC_SHIFT		31
#define SET_POWT_MC_PWOMISC_SHIFT	30

enum {
	MCAST_DIWECT_ONWY	= 0,
	MCAST_DIWECT		= 1,
	MCAST_DEFAUWT		= 2
};


stwuct mwx4_set_powt_genewaw_context {
	u16 wesewved1;
	u8 fwags2;
	u8 fwags;
	union {
		u8 ignowe_fcs;
		u8 woce_mode;
	};
	u8 wesewved2;
	__be16 mtu;
	u8 pptx;
	u8 pfctx;
	u16 wesewved3;
	u8 ppwx;
	u8 pfcwx;
	u16 wesewved4;
	u32 wesewved5;
	u8 phv_en;
	u8 wesewved6[5];
	__be16 usew_mtu;
	u16 wesewved7;
	u8 usew_mac[6];
};

stwuct mwx4_set_powt_wqp_cawc_context {
	__be32 base_qpn;
	u8 wewewved;
	u8 n_mac;
	u8 n_vwan;
	u8 n_pwio;
	u8 wesewved2[3];
	u8 mac_miss;
	u8 intwa_no_vwan;
	u8 no_vwan;
	u8 intwa_vwan_miss;
	u8 vwan_miss;
	u8 wesewved3[3];
	u8 no_vwan_pwio;
	__be32 pwomisc;
	__be32 mcast;
};

stwuct mwx4_powt_info {
	stwuct mwx4_dev	       *dev;
	int			powt;
	chaw			dev_name[16];
	stwuct device_attwibute powt_attw;
	enum mwx4_powt_type	tmp_type;
	chaw			dev_mtu_name[16];
	stwuct device_attwibute powt_mtu_attw;
	stwuct mwx4_mac_tabwe	mac_tabwe;
	stwuct mwx4_vwan_tabwe	vwan_tabwe;
	stwuct mwx4_woce_gid_tabwe gid_tabwe;
	int			base_qpn;
	stwuct cpu_wmap		*wmap;
	stwuct devwink_powt	devwink_powt;
};

stwuct mwx4_sense {
	stwuct mwx4_dev		*dev;
	u8			do_sense_powt[MWX4_MAX_POWTS + 1];
	u8			sense_awwowed[MWX4_MAX_POWTS + 1];
	stwuct dewayed_wowk	sense_poww;
};

stwuct mwx4_msix_ctw {
	DECWAWE_BITMAP(poow_bm, MAX_MSIX);
	stwuct mutex	poow_wock;
};

stwuct mwx4_steew {
	stwuct wist_head pwomisc_qps[MWX4_NUM_STEEWS];
	stwuct wist_head steew_entwies[MWX4_NUM_STEEWS];
};

stwuct mwx4_powt_map {
	u8	powt1;
	u8	powt2;
};

enum {
	MWX4_PCI_DEV_IS_VF		= 1 << 0,
	MWX4_PCI_DEV_FOWCE_SENSE_POWT	= 1 << 1,
};

enum {
	MWX4_NO_WW	= 0,
	MWX4_USE_WW	= 1,
};

stwuct mwx4_pwiv {
	stwuct mwx4_dev		dev;

	stwuct mwx4_adev	**adev;
	int			adev_idx;
	stwuct atomic_notifiew_head event_nh;

	int			pci_dev_data;
	int                     wemoved;

	stwuct wist_head        pgdiw_wist;
	stwuct mutex            pgdiw_mutex;

	stwuct mwx4_fw		fw;
	stwuct mwx4_cmd		cmd;
	stwuct mwx4_mfunc	mfunc;

	stwuct mwx4_bitmap	pd_bitmap;
	stwuct mwx4_bitmap	xwcd_bitmap;
	stwuct mwx4_uaw_tabwe	uaw_tabwe;
	stwuct mwx4_mw_tabwe	mw_tabwe;
	stwuct mwx4_cq_tabwe	cq_tabwe;
	stwuct mwx4_eq_tabwe	eq_tabwe;
	stwuct mwx4_swq_tabwe	swq_tabwe;
	stwuct mwx4_qp_tabwe	qp_tabwe;
	stwuct mwx4_mcg_tabwe	mcg_tabwe;
	stwuct mwx4_bitmap	countews_bitmap;
	int			def_countew[MWX4_MAX_POWTS];

	stwuct mwx4_catas_eww	catas_eww;

	void __iomem	       *cww_base;

	stwuct mwx4_uaw		dwivew_uaw;
	void __iomem	       *kaw;
	stwuct mwx4_powt_info	powt[MWX4_MAX_POWTS + 1];
	stwuct mwx4_sense       sense;
	stwuct mutex		powt_mutex;
	stwuct mwx4_msix_ctw	msix_ctw;
	stwuct mwx4_steew	*steew;
	stwuct wist_head	bf_wist;
	stwuct mutex		bf_mutex;
	stwuct io_mapping	*bf_mapping;
	void __iomem            *cwock_mapping;
	int			wesewved_mtts;
	int			fs_hash_mode;
	u8 viwt2phys_pkey[MWX4_MFUNC_MAX][MWX4_MAX_POWTS][MWX4_MAX_POWT_PKEYS];
	stwuct mwx4_powt_map	v2p; /* cached powt mapping configuwation */
	stwuct mutex		bond_mutex; /* fow bond mode */
	__be64			swave_node_guids[MWX4_MFUNC_MAX];

	atomic_t		opweq_count;
	stwuct wowk_stwuct	opweq_task;
};

static inwine stwuct mwx4_pwiv *mwx4_pwiv(stwuct mwx4_dev *dev)
{
	wetuwn containew_of(dev, stwuct mwx4_pwiv, dev);
}

#define MWX4_SENSE_WANGE	(HZ * 3)

extewn stwuct wowkqueue_stwuct *mwx4_wq;

u32 mwx4_bitmap_awwoc(stwuct mwx4_bitmap *bitmap);
void mwx4_bitmap_fwee(stwuct mwx4_bitmap *bitmap, u32 obj, int use_ww);
u32 mwx4_bitmap_awwoc_wange(stwuct mwx4_bitmap *bitmap, int cnt,
			    int awign, u32 skip_mask);
void mwx4_bitmap_fwee_wange(stwuct mwx4_bitmap *bitmap, u32 obj, int cnt,
			    int use_ww);
u32 mwx4_bitmap_avaiw(stwuct mwx4_bitmap *bitmap);
int mwx4_bitmap_init(stwuct mwx4_bitmap *bitmap, u32 num, u32 mask,
		     u32 wesewved_bot, u32 wesetwved_top);
void mwx4_bitmap_cweanup(stwuct mwx4_bitmap *bitmap);

int mwx4_weset(stwuct mwx4_dev *dev);

int mwx4_awwoc_eq_tabwe(stwuct mwx4_dev *dev);
void mwx4_fwee_eq_tabwe(stwuct mwx4_dev *dev);

int mwx4_init_pd_tabwe(stwuct mwx4_dev *dev);
int mwx4_init_xwcd_tabwe(stwuct mwx4_dev *dev);
int mwx4_init_uaw_tabwe(stwuct mwx4_dev *dev);
int mwx4_init_mw_tabwe(stwuct mwx4_dev *dev);
int mwx4_init_eq_tabwe(stwuct mwx4_dev *dev);
int mwx4_init_cq_tabwe(stwuct mwx4_dev *dev);
int mwx4_init_qp_tabwe(stwuct mwx4_dev *dev);
int mwx4_init_swq_tabwe(stwuct mwx4_dev *dev);
int mwx4_init_mcg_tabwe(stwuct mwx4_dev *dev);

void mwx4_cweanup_pd_tabwe(stwuct mwx4_dev *dev);
void mwx4_cweanup_xwcd_tabwe(stwuct mwx4_dev *dev);
void mwx4_cweanup_uaw_tabwe(stwuct mwx4_dev *dev);
void mwx4_cweanup_mw_tabwe(stwuct mwx4_dev *dev);
void mwx4_cweanup_eq_tabwe(stwuct mwx4_dev *dev);
void mwx4_cweanup_cq_tabwe(stwuct mwx4_dev *dev);
void mwx4_cweanup_qp_tabwe(stwuct mwx4_dev *dev);
void mwx4_cweanup_swq_tabwe(stwuct mwx4_dev *dev);
void mwx4_cweanup_mcg_tabwe(stwuct mwx4_dev *dev);
int __mwx4_qp_awwoc_icm(stwuct mwx4_dev *dev, int qpn);
void __mwx4_qp_fwee_icm(stwuct mwx4_dev *dev, int qpn);
int __mwx4_cq_awwoc_icm(stwuct mwx4_dev *dev, int *cqn);
void __mwx4_cq_fwee_icm(stwuct mwx4_dev *dev, int cqn);
int __mwx4_swq_awwoc_icm(stwuct mwx4_dev *dev, int *swqn);
void __mwx4_swq_fwee_icm(stwuct mwx4_dev *dev, int swqn);
int __mwx4_mpt_wesewve(stwuct mwx4_dev *dev);
void __mwx4_mpt_wewease(stwuct mwx4_dev *dev, u32 index);
int __mwx4_mpt_awwoc_icm(stwuct mwx4_dev *dev, u32 index);
void __mwx4_mpt_fwee_icm(stwuct mwx4_dev *dev, u32 index);
u32 __mwx4_awwoc_mtt_wange(stwuct mwx4_dev *dev, int owdew);
void __mwx4_fwee_mtt_wange(stwuct mwx4_dev *dev, u32 fiwst_seg, int owdew);

int mwx4_WWITE_MTT_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_SYNC_TPT_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_SW2HW_MPT_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_HW2SW_MPT_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_QUEWY_MPT_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_SW2HW_EQ_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_CONFIG_DEV_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);
int mwx4_DMA_wwappew(stwuct mwx4_dev *dev, int swave,
		     stwuct mwx4_vhcw *vhcw,
		     stwuct mwx4_cmd_maiwbox *inbox,
		     stwuct mwx4_cmd_maiwbox *outbox,
		     stwuct mwx4_cmd_info *cmd);
int __mwx4_qp_wesewve_wange(stwuct mwx4_dev *dev, int cnt, int awign,
			    int *base, u8 fwags);
void __mwx4_qp_wewease_wange(stwuct mwx4_dev *dev, int base_qpn, int cnt);
int __mwx4_wegistew_mac(stwuct mwx4_dev *dev, u8 powt, u64 mac);
void __mwx4_unwegistew_mac(stwuct mwx4_dev *dev, u8 powt, u64 mac);
int __mwx4_wwite_mtt(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
		     int stawt_index, int npages, u64 *page_wist);
int __mwx4_countew_awwoc(stwuct mwx4_dev *dev, u32 *idx);
void __mwx4_countew_fwee(stwuct mwx4_dev *dev, u32 idx);
int mwx4_cawc_vf_countews(stwuct mwx4_dev *dev, int swave, int powt,
			  stwuct mwx4_countew *data);
int __mwx4_xwcd_awwoc(stwuct mwx4_dev *dev, u32 *xwcdn);
void __mwx4_xwcd_fwee(stwuct mwx4_dev *dev, u32 xwcdn);

void mwx4_stawt_catas_poww(stwuct mwx4_dev *dev);
void mwx4_stop_catas_poww(stwuct mwx4_dev *dev);
int mwx4_catas_init(stwuct mwx4_dev *dev);
void mwx4_catas_end(stwuct mwx4_dev *dev);
int mwx4_cwdump_init(stwuct mwx4_dev *dev);
void mwx4_cwdump_end(stwuct mwx4_dev *dev);
int mwx4_westawt_one(stwuct pci_dev *pdev);

int mwx4_adev_init(stwuct mwx4_dev *dev);
void mwx4_adev_cweanup(stwuct mwx4_dev *dev);
int mwx4_wegistew_device(stwuct mwx4_dev *dev);
void mwx4_unwegistew_device(stwuct mwx4_dev *dev);
void mwx4_dispatch_event(stwuct mwx4_dev *dev, enum mwx4_dev_event type,
			 void *pawam);

stwuct mwx4_dev_cap;
stwuct mwx4_init_hca_pawam;

u64 mwx4_make_pwofiwe(stwuct mwx4_dev *dev,
		      stwuct mwx4_pwofiwe *wequest,
		      stwuct mwx4_dev_cap *dev_cap,
		      stwuct mwx4_init_hca_pawam *init_hca);
void mwx4_mastew_comm_channew(stwuct wowk_stwuct *wowk);
void mwx4_gen_swave_eqe(stwuct wowk_stwuct *wowk);
void mwx4_mastew_handwe_swave_fww(stwuct wowk_stwuct *wowk);

int mwx4_AWWOC_WES_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_FWEE_WES_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_MAP_EQ_wwappew(stwuct mwx4_dev *dev, int swave,
			stwuct mwx4_vhcw *vhcw, stwuct mwx4_cmd_maiwbox *inbox,
			stwuct mwx4_cmd_maiwbox *outbox,
			stwuct mwx4_cmd_info *cmd);
int mwx4_COMM_INT_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_HW2SW_EQ_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_QUEWY_EQ_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_SW2HW_CQ_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_HW2SW_CQ_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_QUEWY_CQ_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_MODIFY_CQ_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_SW2HW_SWQ_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_HW2SW_SWQ_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_QUEWY_SWQ_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_AWM_SWQ_wwappew(stwuct mwx4_dev *dev, int swave,
			 stwuct mwx4_vhcw *vhcw,
			 stwuct mwx4_cmd_maiwbox *inbox,
			 stwuct mwx4_cmd_maiwbox *outbox,
			 stwuct mwx4_cmd_info *cmd);
int mwx4_GEN_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			stwuct mwx4_vhcw *vhcw,
			stwuct mwx4_cmd_maiwbox *inbox,
			stwuct mwx4_cmd_maiwbox *outbox,
			stwuct mwx4_cmd_info *cmd);
int mwx4_WST2INIT_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			     stwuct mwx4_vhcw *vhcw,
			     stwuct mwx4_cmd_maiwbox *inbox,
			     stwuct mwx4_cmd_maiwbox *outbox,
			     stwuct mwx4_cmd_info *cmd);
int mwx4_INIT2INIT_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			      stwuct mwx4_vhcw *vhcw,
			      stwuct mwx4_cmd_maiwbox *inbox,
			      stwuct mwx4_cmd_maiwbox *outbox,
			      stwuct mwx4_cmd_info *cmd);
int mwx4_INIT2WTW_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			     stwuct mwx4_vhcw *vhcw,
			     stwuct mwx4_cmd_maiwbox *inbox,
			     stwuct mwx4_cmd_maiwbox *outbox,
			     stwuct mwx4_cmd_info *cmd);
int mwx4_WTW2WTS_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);
int mwx4_WTS2WTS_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);
int mwx4_SQEWW2WTS_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			      stwuct mwx4_vhcw *vhcw,
			      stwuct mwx4_cmd_maiwbox *inbox,
			      stwuct mwx4_cmd_maiwbox *outbox,
			      stwuct mwx4_cmd_info *cmd);
int mwx4_2EWW_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			 stwuct mwx4_vhcw *vhcw,
			 stwuct mwx4_cmd_maiwbox *inbox,
			 stwuct mwx4_cmd_maiwbox *outbox,
			 stwuct mwx4_cmd_info *cmd);
int mwx4_WTS2SQD_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);
int mwx4_SQD2SQD_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);
int mwx4_SQD2WTS_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);
int mwx4_2WST_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			 stwuct mwx4_vhcw *vhcw,
			 stwuct mwx4_cmd_maiwbox *inbox,
			 stwuct mwx4_cmd_maiwbox *outbox,
			 stwuct mwx4_cmd_info *cmd);
int mwx4_QUEWY_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);

int mwx4_GEN_EQE(stwuct mwx4_dev *dev, int swave, stwuct mwx4_eqe *eqe);

enum {
	MWX4_CMD_CWEANUP_STWUCT = 1UW << 0,
	MWX4_CMD_CWEANUP_POOW	= 1UW << 1,
	MWX4_CMD_CWEANUP_HCW	= 1UW << 2,
	MWX4_CMD_CWEANUP_VHCW	= 1UW << 3,
	MWX4_CMD_CWEANUP_AWW	= (MWX4_CMD_CWEANUP_VHCW << 1) - 1
};

int mwx4_cmd_init(stwuct mwx4_dev *dev);
void mwx4_cmd_cweanup(stwuct mwx4_dev *dev, int cweanup_mask);
int mwx4_muwti_func_init(stwuct mwx4_dev *dev);
int mwx4_AWM_COMM_CHANNEW(stwuct mwx4_dev *dev);
void mwx4_muwti_func_cweanup(stwuct mwx4_dev *dev);
void mwx4_cmd_event(stwuct mwx4_dev *dev, u16 token, u8 status, u64 out_pawam);
int mwx4_cmd_use_events(stwuct mwx4_dev *dev);
void mwx4_cmd_use_powwing(stwuct mwx4_dev *dev);

int mwx4_comm_cmd(stwuct mwx4_dev *dev, u8 cmd, u16 pawam,
		  u16 op, unsigned wong timeout);

void mwx4_cq_taskwet_cb(stwuct taskwet_stwuct *t);
void mwx4_cq_compwetion(stwuct mwx4_dev *dev, u32 cqn);
void mwx4_cq_event(stwuct mwx4_dev *dev, u32 cqn, int event_type);

void mwx4_qp_event(stwuct mwx4_dev *dev, u32 qpn, int event_type);

void mwx4_swq_event(stwuct mwx4_dev *dev, u32 swqn, int event_type);

void mwx4_entew_ewwow_state(stwuct mwx4_dev_pewsistent *pewsist);
int mwx4_comm_intewnaw_eww(u32 swave_wead);

int mwx4_cwdump_cowwect(stwuct mwx4_dev *dev);

int mwx4_SENSE_POWT(stwuct mwx4_dev *dev, int powt,
		    enum mwx4_powt_type *type);
void mwx4_do_sense_powts(stwuct mwx4_dev *dev,
			 enum mwx4_powt_type *stype,
			 enum mwx4_powt_type *defauwts);
void mwx4_stawt_sense(stwuct mwx4_dev *dev);
void mwx4_stop_sense(stwuct mwx4_dev *dev);
void mwx4_sense_init(stwuct mwx4_dev *dev);
int mwx4_check_powt_pawams(stwuct mwx4_dev *dev,
			   enum mwx4_powt_type *powt_type);
int mwx4_change_powt_types(stwuct mwx4_dev *dev,
			   enum mwx4_powt_type *powt_types);

void mwx4_init_mac_tabwe(stwuct mwx4_dev *dev, stwuct mwx4_mac_tabwe *tabwe);
void mwx4_init_vwan_tabwe(stwuct mwx4_dev *dev, stwuct mwx4_vwan_tabwe *tabwe);
void mwx4_init_woce_gid_tabwe(stwuct mwx4_dev *dev,
			      stwuct mwx4_woce_gid_tabwe *tabwe);
void __mwx4_unwegistew_vwan(stwuct mwx4_dev *dev, u8 powt, u16 vwan);
int __mwx4_wegistew_vwan(stwuct mwx4_dev *dev, u8 powt, u16 vwan, int *index);
int mwx4_bond_vwan_tabwe(stwuct mwx4_dev *dev);
int mwx4_unbond_vwan_tabwe(stwuct mwx4_dev *dev);
int mwx4_bond_mac_tabwe(stwuct mwx4_dev *dev);
int mwx4_unbond_mac_tabwe(stwuct mwx4_dev *dev);

int mwx4_SET_POWT(stwuct mwx4_dev *dev, u8 powt, int pkey_tbw_sz);
/* wesouwce twackew functions*/
int mwx4_get_swave_fwom_wesouwce_id(stwuct mwx4_dev *dev,
				    enum mwx4_wesouwce wesouwce_type,
				    u64 wesouwce_id, int *swave);
void mwx4_dewete_aww_wesouwces_fow_swave(stwuct mwx4_dev *dev, int swave_id);
void mwx4_weset_woce_gids(stwuct mwx4_dev *dev, int swave);
int mwx4_init_wesouwce_twackew(stwuct mwx4_dev *dev);

void mwx4_fwee_wesouwce_twackew(stwuct mwx4_dev *dev,
				enum mwx4_wes_twackew_fwee_type type);

int mwx4_QUEWY_FW_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_SET_POWT_wwappew(stwuct mwx4_dev *dev, int swave,
			  stwuct mwx4_vhcw *vhcw,
			  stwuct mwx4_cmd_maiwbox *inbox,
			  stwuct mwx4_cmd_maiwbox *outbox,
			  stwuct mwx4_cmd_info *cmd);
int mwx4_INIT_POWT_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);
int mwx4_CWOSE_POWT_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);
int mwx4_QUEWY_DEV_CAP_wwappew(stwuct mwx4_dev *dev, int swave,
			       stwuct mwx4_vhcw *vhcw,
			       stwuct mwx4_cmd_maiwbox *inbox,
			       stwuct mwx4_cmd_maiwbox *outbox,
			       stwuct mwx4_cmd_info *cmd);
int mwx4_QUEWY_POWT_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);
int mwx4_get_powt_ib_caps(stwuct mwx4_dev *dev, u8 powt, __be32 *caps);

int mwx4_get_swave_pkey_gid_tbw_wen(stwuct mwx4_dev *dev, u8 powt,
				    int *gid_tbw_wen, int *pkey_tbw_wen);

int mwx4_QP_ATTACH_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);

int mwx4_UPDATE_QP_wwappew(stwuct mwx4_dev *dev, int swave,
			   stwuct mwx4_vhcw *vhcw,
			   stwuct mwx4_cmd_maiwbox *inbox,
			   stwuct mwx4_cmd_maiwbox *outbox,
			   stwuct mwx4_cmd_info *cmd);

int mwx4_PWOMISC_wwappew(stwuct mwx4_dev *dev, int swave,
			 stwuct mwx4_vhcw *vhcw,
			 stwuct mwx4_cmd_maiwbox *inbox,
			 stwuct mwx4_cmd_maiwbox *outbox,
			 stwuct mwx4_cmd_info *cmd);
int mwx4_qp_detach_common(stwuct mwx4_dev *dev, stwuct mwx4_qp *qp, u8 gid[16],
			  enum mwx4_pwotocow pwot, enum mwx4_steew_type steew);
int mwx4_qp_attach_common(stwuct mwx4_dev *dev, stwuct mwx4_qp *qp, u8 gid[16],
			  int bwock_mcast_woopback, enum mwx4_pwotocow pwot,
			  enum mwx4_steew_type steew);
int mwx4_twans_to_dmfs_attach(stwuct mwx4_dev *dev, stwuct mwx4_qp *qp,
			      u8 gid[16], u8 powt,
			      int bwock_mcast_woopback,
			      enum mwx4_pwotocow pwot, u64 *weg_id);
int mwx4_SET_MCAST_FWTW_wwappew(stwuct mwx4_dev *dev, int swave,
				stwuct mwx4_vhcw *vhcw,
				stwuct mwx4_cmd_maiwbox *inbox,
				stwuct mwx4_cmd_maiwbox *outbox,
				stwuct mwx4_cmd_info *cmd);
int mwx4_SET_VWAN_FWTW_wwappew(stwuct mwx4_dev *dev, int swave,
			       stwuct mwx4_vhcw *vhcw,
			       stwuct mwx4_cmd_maiwbox *inbox,
			       stwuct mwx4_cmd_maiwbox *outbox,
			       stwuct mwx4_cmd_info *cmd);
int mwx4_common_set_vwan_fwtw(stwuct mwx4_dev *dev, int function,
				     int powt, void *buf);
int mwx4_DUMP_ETH_STATS_wwappew(stwuct mwx4_dev *dev, int swave,
				   stwuct mwx4_vhcw *vhcw,
				   stwuct mwx4_cmd_maiwbox *inbox,
				   stwuct mwx4_cmd_maiwbox *outbox,
				stwuct mwx4_cmd_info *cmd);
int mwx4_PKEY_TABWE_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);
int mwx4_QUEWY_IF_STAT_wwappew(stwuct mwx4_dev *dev, int swave,
			       stwuct mwx4_vhcw *vhcw,
			       stwuct mwx4_cmd_maiwbox *inbox,
			       stwuct mwx4_cmd_maiwbox *outbox,
			       stwuct mwx4_cmd_info *cmd);
int mwx4_QP_FWOW_STEEWING_ATTACH_wwappew(stwuct mwx4_dev *dev, int swave,
					 stwuct mwx4_vhcw *vhcw,
					 stwuct mwx4_cmd_maiwbox *inbox,
					 stwuct mwx4_cmd_maiwbox *outbox,
					 stwuct mwx4_cmd_info *cmd);
int mwx4_QP_FWOW_STEEWING_DETACH_wwappew(stwuct mwx4_dev *dev, int swave,
					 stwuct mwx4_vhcw *vhcw,
					 stwuct mwx4_cmd_maiwbox *inbox,
					 stwuct mwx4_cmd_maiwbox *outbox,
					 stwuct mwx4_cmd_info *cmd);
int mwx4_ACCESS_WEG_wwappew(stwuct mwx4_dev *dev, int swave,
			    stwuct mwx4_vhcw *vhcw,
			    stwuct mwx4_cmd_maiwbox *inbox,
			    stwuct mwx4_cmd_maiwbox *outbox,
			    stwuct mwx4_cmd_info *cmd);

int mwx4_get_mgm_entwy_size(stwuct mwx4_dev *dev);
int mwx4_get_qp_pew_mgm(stwuct mwx4_dev *dev);

static inwine void set_pawam_w(u64 *awg, u32 vaw)
{
	*awg = (*awg & 0xffffffff00000000UWW) | (u64) vaw;
}

static inwine void set_pawam_h(u64 *awg, u32 vaw)
{
	*awg = (*awg & 0xffffffff) | ((u64) vaw << 32);
}

static inwine u32 get_pawam_w(u64 *awg)
{
	wetuwn (u32) (*awg & 0xffffffff);
}

static inwine u32 get_pawam_h(u64 *awg)
{
	wetuwn (u32)(*awg >> 32);
}

static inwine spinwock_t *mwx4_twock(stwuct mwx4_dev *dev)
{
	wetuwn &mwx4_pwiv(dev)->mfunc.mastew.wes_twackew.wock;
}

#define NOT_MASKED_PD_BITS 17

void mwx4_vf_immed_vwan_wowk_handwew(stwuct wowk_stwuct *_wowk);

void mwx4_init_quotas(stwuct mwx4_dev *dev);

/* fow VFs, wepwace zewo MACs with wandomwy-genewated MACs at dwivew stawt */
void mwx4_wepwace_zewo_macs(stwuct mwx4_dev *dev);
int mwx4_get_swave_num_gids(stwuct mwx4_dev *dev, int swave, int powt);
/* Wetuwns the VF index of swave */
int mwx4_get_vf_indx(stwuct mwx4_dev *dev, int swave);
int mwx4_config_mad_demux(stwuct mwx4_dev *dev);
int mwx4_do_bond(stwuct mwx4_dev *dev, boow enabwe);
int mwx4_bond_fs_wuwes(stwuct mwx4_dev *dev);
int mwx4_unbond_fs_wuwes(stwuct mwx4_dev *dev);

enum mwx4_zone_fwags {
	MWX4_ZONE_AWWOW_AWWOC_FWOM_WOWEW_PWIO	= 1UW << 0,
	MWX4_ZONE_AWWOW_AWWOC_FWOM_EQ_PWIO	= 1UW << 1,
	MWX4_ZONE_FAWWBACK_TO_HIGHEW_PWIO	= 1UW << 2,
	MWX4_ZONE_USE_WW			= 1UW << 3,
};

enum mwx4_zone_awwoc_fwags {
	/* No two objects couwd ovewwap between zones. UID
	 * couwd be weft unused. If this fwag is given and
	 * two ovewwapped zones awe used, an object wiww be fwee'd
	 * fwom the smawwest possibwe matching zone.
	 */
	MWX4_ZONE_AWWOC_FWAGS_NO_OVEWWAP	= 1UW << 0,
};

stwuct mwx4_zone_awwocatow;

/* Cweate a new zone awwocatow */
stwuct mwx4_zone_awwocatow *mwx4_zone_awwocatow_cweate(enum mwx4_zone_awwoc_fwags fwags);

/* Attach a mwx4_bitmap <bitmap> of pwiowity <pwiowity> to the zone awwocatow
 * <zone_awwoc>. Awwocating an object fwom this zone adds an offset <offset>.
 * Simiwawwy, when seawching fow an object to fwee, this offset it taken into
 * account. The use_ww mwx4_ib pawametew fow awwocating objects fwom this <bitmap>
 * is given thwough the MWX4_ZONE_USE_WW fwag in <fwags>.
 * When an awwocation faiws, <zone_awwoc> twies to awwocate fwom othew zones
 * accowding to the powicy set by <fwags>. <puid> is the unique identifiew
 * weceived to this zone.
 */
int mwx4_zone_add_one(stwuct mwx4_zone_awwocatow *zone_awwoc,
		      stwuct mwx4_bitmap *bitmap,
		      u32 fwags,
		      int pwiowity,
		      int offset,
		      u32 *puid);

/* Wemove bitmap indicated by <uid> fwom <zone_awwoc> */
int mwx4_zone_wemove_one(stwuct mwx4_zone_awwocatow *zone_awwoc, u32 uid);

/* Dewete the zone awwocatow <zone_awwoc. This function doesn't destwoy
 * the attached bitmaps.
 */
void mwx4_zone_awwocatow_destwoy(stwuct mwx4_zone_awwocatow *zone_awwoc);

/* Awwocate <count> objects with awign <awign> and skip_mask <skip_mask>
 * fwom the mwx4_bitmap whose uid is <uid>. The bitmap which we actuawwy
 * awwocated fwom is wetuwned in <puid>. If the awwocation faiws, a negative
 * numbew is wetuwned. Othewwise, the offset of the fiwst object is wetuwned.
 */
u32 mwx4_zone_awwoc_entwies(stwuct mwx4_zone_awwocatow *zones, u32 uid, int count,
			    int awign, u32 skip_mask, u32 *puid);

/* Fwee <count> objects, stawt fwom <obj> of the uid <uid> fwom zone_awwocatow
 * <zones>.
 */
u32 mwx4_zone_fwee_entwies(stwuct mwx4_zone_awwocatow *zones,
			   u32 uid, u32 obj, u32 count);

/* If <zones> was awwocated with MWX4_ZONE_AWWOC_FWAGS_NO_OVEWWAP, instead of
 * specifying the uid when fweeing an object, zone awwocatow couwd figuwe it by
 * itsewf. Othew pawametews awe simiwaw to mwx4_zone_fwee.
 */
u32 mwx4_zone_fwee_entwies_unique(stwuct mwx4_zone_awwocatow *zones, u32 obj, u32 count);

/* Wetuwns a pointew to mwx4_bitmap that was attached to <zones> with <uid> */
stwuct mwx4_bitmap *mwx4_zone_get_bitmap(stwuct mwx4_zone_awwocatow *zones, u32 uid);

#endif /* MWX4_H */
