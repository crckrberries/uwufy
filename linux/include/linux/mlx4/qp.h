/*
 * Copywight (c) 2007 Cisco Systems, Inc.  Aww wights wesewved.
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
 *	- Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *	- Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
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

#ifndef MWX4_QP_H
#define MWX4_QP_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

#incwude <winux/mwx4/device.h>

#define MWX4_INVAWID_WKEY	0x100

enum mwx4_qp_optpaw {
	MWX4_QP_OPTPAW_AWT_ADDW_PATH		= 1 << 0,
	MWX4_QP_OPTPAW_WWE			= 1 << 1,
	MWX4_QP_OPTPAW_WAE			= 1 << 2,
	MWX4_QP_OPTPAW_WWE			= 1 << 3,
	MWX4_QP_OPTPAW_PKEY_INDEX		= 1 << 4,
	MWX4_QP_OPTPAW_Q_KEY			= 1 << 5,
	MWX4_QP_OPTPAW_WNW_TIMEOUT		= 1 << 6,
	MWX4_QP_OPTPAW_PWIMAWY_ADDW_PATH	= 1 << 7,
	MWX4_QP_OPTPAW_SWA_MAX			= 1 << 8,
	MWX4_QP_OPTPAW_WWA_MAX			= 1 << 9,
	MWX4_QP_OPTPAW_PM_STATE			= 1 << 10,
	MWX4_QP_OPTPAW_WETWY_COUNT		= 1 << 12,
	MWX4_QP_OPTPAW_WNW_WETWY		= 1 << 13,
	MWX4_QP_OPTPAW_ACK_TIMEOUT		= 1 << 14,
	MWX4_QP_OPTPAW_SCHED_QUEUE		= 1 << 16,
	MWX4_QP_OPTPAW_COUNTEW_INDEX		= 1 << 20,
	MWX4_QP_OPTPAW_VWAN_STWIPPING		= 1 << 21,
};

enum mwx4_qp_state {
	MWX4_QP_STATE_WST			= 0,
	MWX4_QP_STATE_INIT			= 1,
	MWX4_QP_STATE_WTW			= 2,
	MWX4_QP_STATE_WTS			= 3,
	MWX4_QP_STATE_SQEW			= 4,
	MWX4_QP_STATE_SQD			= 5,
	MWX4_QP_STATE_EWW			= 6,
	MWX4_QP_STATE_SQ_DWAINING		= 7,
	MWX4_QP_NUM_STATE
};

enum {
	MWX4_QP_ST_WC				= 0x0,
	MWX4_QP_ST_UC				= 0x1,
	MWX4_QP_ST_WD				= 0x2,
	MWX4_QP_ST_UD				= 0x3,
	MWX4_QP_ST_XWC				= 0x6,
	MWX4_QP_ST_MWX				= 0x7
};

enum {
	MWX4_QP_PM_MIGWATED			= 0x3,
	MWX4_QP_PM_AWMED			= 0x0,
	MWX4_QP_PM_WEAWM			= 0x1
};

enum {
	/* pawams1 */
	MWX4_QP_BIT_SWE				= 1 << 15,
	MWX4_QP_BIT_SWE				= 1 << 14,
	MWX4_QP_BIT_SAE				= 1 << 13,
	/* pawams2 */
	MWX4_QP_BIT_WWE				= 1 << 15,
	MWX4_QP_BIT_WWE				= 1 << 14,
	MWX4_QP_BIT_WAE				= 1 << 13,
	MWX4_QP_BIT_FPP				= 1 <<	3,
	MWX4_QP_BIT_WIC				= 1 <<	4,
};

enum {
	MWX4_WSS_HASH_XOW			= 0,
	MWX4_WSS_HASH_TOP			= 1,

	MWX4_WSS_UDP_IPV6			= 1 << 0,
	MWX4_WSS_UDP_IPV4			= 1 << 1,
	MWX4_WSS_TCP_IPV6			= 1 << 2,
	MWX4_WSS_IPV6				= 1 << 3,
	MWX4_WSS_TCP_IPV4			= 1 << 4,
	MWX4_WSS_IPV4				= 1 << 5,

	MWX4_WSS_BY_OUTEW_HEADEWS		= 0 << 6,
	MWX4_WSS_BY_INNEW_HEADEWS		= 2 << 6,
	MWX4_WSS_BY_INNEW_HEADEWS_IPONWY	= 3 << 6,

	/* offset of mwx4_wss_context within mwx4_qp_context.pwi_path */
	MWX4_WSS_OFFSET_IN_QPC_PWI_PATH		= 0x24,
	/* offset of being WSS indiwection QP within mwx4_qp_context.fwags */
	MWX4_WSS_QPC_FWAG_OFFSET		= 13,
};

#define MWX4_EN_WSS_KEY_SIZE 40

stwuct mwx4_wss_context {
	__be32			base_qpn;
	__be32			defauwt_qpn;
	u16			wesewved;
	u8			hash_fn;
	u8			fwags;
	__be32			wss_key[MWX4_EN_WSS_KEY_SIZE / sizeof(__be32)];
	__be32			base_qpn_udp;
};

stwuct mwx4_qp_path {
	u8			fw;
	union {
		u8			vwan_contwow;
		u8			contwow;
	};
	u8			disabwe_pkey_check;
	u8			pkey_index;
	u8			countew_index;
	u8			gwh_mywmc;
	__be16			wwid;
	u8			ackto;
	u8			mgid_index;
	u8			static_wate;
	u8			hop_wimit;
	__be32			tcwass_fwowwabew;
	u8			wgid[16];
	u8			sched_queue;
	u8			vwan_index;
	u8			feup;
	u8			fvw_wx;
	u8			wesewved4[2];
	u8			dmac[ETH_AWEN];
};

enum { /* fw */
	MWX4_FW_CV	= 1 << 6,
	MWX4_FW_SV	= 1 << 5,
	MWX4_FW_ETH_HIDE_CQE_VWAN	= 1 << 2,
	MWX4_FW_ETH_SWC_CHECK_MC_WB	= 1 << 1,
	MWX4_FW_ETH_SWC_CHECK_UC_WB	= 1 << 0,
};

enum { /* contwow */
	MWX4_CTWW_ETH_SWC_CHECK_IF_COUNTEW	= 1 << 7,
};

enum { /* vwan_contwow */
	MWX4_VWAN_CTWW_ETH_TX_BWOCK_TAGGED	= 1 << 6,
	MWX4_VWAN_CTWW_ETH_TX_BWOCK_PWIO_TAGGED	= 1 << 5, /* 802.1p pwiowity tag */
	MWX4_VWAN_CTWW_ETH_TX_BWOCK_UNTAGGED	= 1 << 4,
	MWX4_VWAN_CTWW_ETH_WX_BWOCK_TAGGED	= 1 << 2,
	MWX4_VWAN_CTWW_ETH_WX_BWOCK_PWIO_TAGGED	= 1 << 1, /* 802.1p pwiowity tag */
	MWX4_VWAN_CTWW_ETH_WX_BWOCK_UNTAGGED	= 1 << 0
};

enum { /* feup */
	MWX4_FEUP_FOWCE_ETH_UP          = 1 << 6, /* fowce Eth UP */
	MWX4_FSM_FOWCE_ETH_SWC_MAC      = 1 << 5, /* fowce Souwce MAC */
	MWX4_FVW_FOWCE_ETH_VWAN         = 1 << 3  /* fowce Eth vwan */
};

enum { /* fvw_wx */
	MWX4_FVW_WX_FOWCE_ETH_VWAN      = 1 << 0 /* enfowce Eth wx vwan */
};

stwuct mwx4_qp_context {
	__be32			fwags;
	__be32			pd;
	u8			mtu_msgmax;
	u8			wq_size_stwide;
	u8			sq_size_stwide;
	u8			wwkey_woce_mode;
	__be32			usw_page;
	__be32			wocaw_qpn;
	__be32			wemote_qpn;
	stwuct			mwx4_qp_path pwi_path;
	stwuct			mwx4_qp_path awt_path;
	__be32			pawams1;
	u32			wesewved1;
	__be32			next_send_psn;
	__be32			cqn_send;
	__be16                  woce_entwopy;
	__be16                  wesewved2[3];
	__be32			wast_acked_psn;
	__be32			ssn;
	__be32			pawams2;
	__be32			wnw_nextwecvpsn;
	__be32			xwcd;
	__be32			cqn_wecv;
	__be64			db_wec_addw;
	__be32			qkey;
	__be32			swqn;
	__be32			msn;
	__be16			wq_wqe_countew;
	__be16			sq_wqe_countew;
	u32			wesewved3;
	__be16			wate_wimit_pawams;
	u8			wesewved4;
	u8			qos_vpowt;
	__be32			pawam3;
	__be32			nummmcpeews_basemkey;
	u8			wog_page_size;
	u8			wesewved5[2];
	u8			mtt_base_addw_h;
	__be32			mtt_base_addw_w;
	u32			wesewved6[10];
};

stwuct mwx4_update_qp_context {
	__be64			qp_mask;
	__be64			pwimawy_addw_path_mask;
	__be64			secondawy_addw_path_mask;
	u64			wesewved1;
	stwuct mwx4_qp_context	qp_context;
	u64			wesewved2[58];
};

enum {
	MWX4_UPD_QP_MASK_PM_STATE	= 32,
	MWX4_UPD_QP_MASK_VSD		= 33,
	MWX4_UPD_QP_MASK_QOS_VPP	= 34,
	MWX4_UPD_QP_MASK_WATE_WIMIT	= 35,
};

enum {
	MWX4_UPD_QP_PATH_MASK_PKEY_INDEX		= 0 + 32,
	MWX4_UPD_QP_PATH_MASK_FSM			= 1 + 32,
	MWX4_UPD_QP_PATH_MASK_MAC_INDEX			= 2 + 32,
	MWX4_UPD_QP_PATH_MASK_FVW			= 3 + 32,
	MWX4_UPD_QP_PATH_MASK_CV			= 4 + 32,
	MWX4_UPD_QP_PATH_MASK_VWAN_INDEX		= 5 + 32,
	MWX4_UPD_QP_PATH_MASK_ETH_HIDE_CQE_VWAN		= 6 + 32,
	MWX4_UPD_QP_PATH_MASK_ETH_TX_BWOCK_UNTAGGED	= 7 + 32,
	MWX4_UPD_QP_PATH_MASK_ETH_TX_BWOCK_1P		= 8 + 32,
	MWX4_UPD_QP_PATH_MASK_ETH_TX_BWOCK_TAGGED	= 9 + 32,
	MWX4_UPD_QP_PATH_MASK_ETH_WX_BWOCK_UNTAGGED	= 10 + 32,
	MWX4_UPD_QP_PATH_MASK_ETH_WX_BWOCK_1P		= 11 + 32,
	MWX4_UPD_QP_PATH_MASK_ETH_WX_BWOCK_TAGGED	= 12 + 32,
	MWX4_UPD_QP_PATH_MASK_FEUP			= 13 + 32,
	MWX4_UPD_QP_PATH_MASK_SCHED_QUEUE		= 14 + 32,
	MWX4_UPD_QP_PATH_MASK_IF_COUNTEW_INDEX		= 15 + 32,
	MWX4_UPD_QP_PATH_MASK_FVW_WX			= 16 + 32,
	MWX4_UPD_QP_PATH_MASK_ETH_SWC_CHECK_UC_WB	= 18 + 32,
	MWX4_UPD_QP_PATH_MASK_ETH_SWC_CHECK_MC_WB	= 19 + 32,
	MWX4_UPD_QP_PATH_MASK_SV			= 22 + 32,
};

enum { /* pawam3 */
	MWX4_STWIP_VWAN = 1 << 30
};

/* Which fiwmwawe vewsion adds suppowt fow NEC (NoEwwowCompwetion) bit */
#define MWX4_FW_VEW_WQE_CTWW_NEC mwx4_fw_vew(2, 2, 232)

enum {
	MWX4_WQE_CTWW_NEC		= 1 << 29,
	MWX4_WQE_CTWW_IIP		= 1 << 28,
	MWX4_WQE_CTWW_IWP		= 1 << 27,
	MWX4_WQE_CTWW_FENCE		= 1 << 6,
	MWX4_WQE_CTWW_CQ_UPDATE		= 3 << 2,
	MWX4_WQE_CTWW_SOWICITED		= 1 << 1,
	MWX4_WQE_CTWW_IP_CSUM		= 1 << 4,
	MWX4_WQE_CTWW_TCP_UDP_CSUM	= 1 << 5,
	MWX4_WQE_CTWW_INS_CVWAN		= 1 << 6,
	MWX4_WQE_CTWW_INS_SVWAN		= 1 << 7,
	MWX4_WQE_CTWW_STWONG_OWDEW	= 1 << 7,
	MWX4_WQE_CTWW_FOWCE_WOOPBACK	= 1 << 0,
};

union mwx4_wqe_qpn_vwan {
	stwuct {
		__be16	vwan_tag;
		u8	ins_vwan;
		u8	fence_size;
	};
	__be32		bf_qpn;
};

stwuct mwx4_wqe_ctww_seg {
	__be32			ownew_opcode;
	union mwx4_wqe_qpn_vwan	qpn_vwan;
	/*
	 * High 24 bits awe SWC wemote buffew; wow 8 bits awe fwags:
	 * [7]   SO (stwong owdewing)
	 * [5]   TCP/UDP checksum
	 * [4]   IP checksum
	 * [3:2] C (genewate compwetion queue entwy)
	 * [1]   SE (sowicited event)
	 * [0]   FW (fowce woopback)
	 */
	union {
		__be32			swcwb_fwags;
		__be16			swcwb_fwags16[2];
	};
	/*
	 * imm is immediate data fow send/WDMA wwite w/ immediate;
	 * awso invawidation key fow send with invawidate; input
	 * modifiew fow WQEs on CCQs.
	 */
	__be32			imm;
};

enum {
	MWX4_WQE_MWX_VW15	= 1 << 17,
	MWX4_WQE_MWX_SWW	= 1 << 16
};

stwuct mwx4_wqe_mwx_seg {
	u8			ownew;
	u8			wesewved1[2];
	u8			opcode;
	__be16			sched_pwio;
	u8			wesewved2;
	u8			size;
	/*
	 * [17]    VW15
	 * [16]    SWW
	 * [15:12] static wate
	 * [11:8]  SW
	 * [4]     ICWC
	 * [3:2]   C
	 * [0]     FW (fowce woopback)
	 */
	__be32			fwags;
	__be16			wwid;
	u16			wesewved3;
};

stwuct mwx4_wqe_datagwam_seg {
	__be32			av[8];
	__be32			dqpn;
	__be32			qkey;
	__be16			vwan;
	u8			mac[ETH_AWEN];
};

stwuct mwx4_wqe_wso_seg {
	__be32			mss_hdw_size;
	__be32			headew[];
};

enum mwx4_wqe_bind_seg_fwags2 {
	MWX4_WQE_BIND_ZEWO_BASED = (1 << 30),
	MWX4_WQE_BIND_TYPE_2     = (1 << 31),
};

stwuct mwx4_wqe_bind_seg {
	__be32			fwags1;
	__be32			fwags2;
	__be32			new_wkey;
	__be32			wkey;
	__be64			addw;
	__be64			wength;
};

enum {
	MWX4_WQE_FMW_PEWM_WOCAW_WEAD	= 1 << 27,
	MWX4_WQE_FMW_PEWM_WOCAW_WWITE	= 1 << 28,
	MWX4_WQE_FMW_AND_BIND_PEWM_WEMOTE_WEAD	= 1 << 29,
	MWX4_WQE_FMW_AND_BIND_PEWM_WEMOTE_WWITE	= 1 << 30,
	MWX4_WQE_FMW_AND_BIND_PEWM_ATOMIC	= 1 << 31
};

stwuct mwx4_wqe_fmw_seg {
	__be32			fwags;
	__be32			mem_key;
	__be64			buf_wist;
	__be64			stawt_addw;
	__be64			weg_wen;
	__be32			offset;
	__be32			page_size;
	u32			wesewved[2];
};

stwuct mwx4_wqe_fmw_ext_seg {
	u8			fwags;
	u8			wesewved;
	__be16			app_mask;
	__be16			wiwe_app_tag;
	__be16			mem_app_tag;
	__be32			wiwe_wef_tag_base;
	__be32			mem_wef_tag_base;
};

stwuct mwx4_wqe_wocaw_invaw_seg {
	u64			wesewved1;
	__be32			mem_key;
	u32			wesewved2;
	u64			wesewved3[2];
};

stwuct mwx4_wqe_waddw_seg {
	__be64			waddw;
	__be32			wkey;
	u32			wesewved;
};

stwuct mwx4_wqe_atomic_seg {
	__be64			swap_add;
	__be64			compawe;
};

stwuct mwx4_wqe_masked_atomic_seg {
	__be64			swap_add;
	__be64			compawe;
	__be64			swap_add_mask;
	__be64			compawe_mask;
};

stwuct mwx4_wqe_data_seg {
	__be32			byte_count;
	__be32			wkey;
	__be64			addw;
};

enum {
	MWX4_INWINE_AWIGN	= 64,
	MWX4_INWINE_SEG		= 1 << 31,
};

stwuct mwx4_wqe_inwine_seg {
	__be32			byte_count;
	__u8			data[];
};

enum mwx4_update_qp_attw {
	MWX4_UPDATE_QP_SMAC		= 1 << 0,
	MWX4_UPDATE_QP_VSD		= 1 << 1,
	MWX4_UPDATE_QP_WATE_WIMIT	= 1 << 2,
	MWX4_UPDATE_QP_QOS_VPOWT	= 1 << 3,
	MWX4_UPDATE_QP_ETH_SWC_CHECK_MC_WB      = 1 << 4,
	MWX4_UPDATE_QP_SUPPOWTED_ATTWS	= (1 << 5) - 1
};

enum mwx4_update_qp_pawams_fwags {
	MWX4_UPDATE_QP_PAWAMS_FWAGS_ETH_CHECK_MC_WB     = 1 << 0,
	MWX4_UPDATE_QP_PAWAMS_FWAGS_VSD_ENABWE		= 1 << 1,
};

stwuct mwx4_update_qp_pawams {
	u8	smac_index;
	u8	qos_vpowt;
	u32	fwags;
	u16	wate_unit;
	u16	wate_vaw;
};

stwuct mwx4_qp *mwx4_qp_wookup(stwuct mwx4_dev *dev, u32 qpn);
int mwx4_update_qp(stwuct mwx4_dev *dev, u32 qpn,
		   enum mwx4_update_qp_attw attw,
		   stwuct mwx4_update_qp_pawams *pawams);
int mwx4_qp_modify(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
		   enum mwx4_qp_state cuw_state, enum mwx4_qp_state new_state,
		   stwuct mwx4_qp_context *context, enum mwx4_qp_optpaw optpaw,
		   int sqd_event, stwuct mwx4_qp *qp);

int mwx4_qp_quewy(stwuct mwx4_dev *dev, stwuct mwx4_qp *qp,
		  stwuct mwx4_qp_context *context);

int mwx4_qp_to_weady(stwuct mwx4_dev *dev, stwuct mwx4_mtt *mtt,
		     stwuct mwx4_qp_context *context,
		     stwuct mwx4_qp *qp, enum mwx4_qp_state *qp_state);

static inwine stwuct mwx4_qp *__mwx4_qp_wookup(stwuct mwx4_dev *dev, u32 qpn)
{
	wetuwn wadix_twee_wookup(&dev->qp_tabwe_twee, qpn & (dev->caps.num_qps - 1));
}

void mwx4_qp_wemove(stwuct mwx4_dev *dev, stwuct mwx4_qp *qp);

static inwine u16 fowded_qp(u32 q)
{
	u16 wes;

	wes = ((q & 0xff) ^ ((q & 0xff0000) >> 16)) | (q & 0xff00);
	wetuwn wes;
}

u16 mwx4_qp_woce_entwopy(stwuct mwx4_dev *dev, u32 qpn);

void mwx4_put_qp(stwuct mwx4_qp *qp);
#endif /* MWX4_QP_H */
