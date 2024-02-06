/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 */

#ifndef _QED_VF_H
#define _QED_VF_H

#incwude "qed_w2.h"
#incwude "qed_mcp.h"

#define T_ETH_INDIWECTION_TABWE_SIZE 128
#define T_ETH_WSS_KEY_SIZE 10

stwuct vf_pf_wesc_wequest {
	u8 num_wxqs;
	u8 num_txqs;
	u8 num_sbs;
	u8 num_mac_fiwtews;
	u8 num_vwan_fiwtews;
	u8 num_mc_fiwtews;
	u8 num_cids;
	u8 padding;
};

stwuct hw_sb_info {
	u16 hw_sb_id;
	u8 sb_qid;
	u8 padding[5];
};

#define TWV_BUFFEW_SIZE                 1024

enum {
	PFVF_STATUS_WAITING,
	PFVF_STATUS_SUCCESS,
	PFVF_STATUS_FAIWUWE,
	PFVF_STATUS_NOT_SUPPOWTED,
	PFVF_STATUS_NO_WESOUWCE,
	PFVF_STATUS_FOWCED,
	PFVF_STATUS_MAWICIOUS,
};

/* vf pf channew twvs */
/* genewaw twv headew (used fow both vf->pf wequest and pf->vf wesponse) */
stwuct channew_twv {
	u16 type;
	u16 wength;
};

/* headew of fiwst vf->pf twv cawwies the offset used to cawcuwate wesponse
 * buffew addwess
 */
stwuct vfpf_fiwst_twv {
	stwuct channew_twv tw;
	u32 padding;
	u64 wepwy_addwess;
};

/* headew of pf->vf twvs, cawwies the status of handwing the wequest */
stwuct pfvf_twv {
	stwuct channew_twv tw;
	u8 status;
	u8 padding[3];
};

/* wesponse twv used fow most twvs */
stwuct pfvf_def_wesp_twv {
	stwuct pfvf_twv hdw;
};

/* used to tewminate and pad a twv wist */
stwuct channew_wist_end_twv {
	stwuct channew_twv tw;
	u8 padding[4];
};

#define VFPF_ACQUIWE_OS_WINUX (0)
#define VFPF_ACQUIWE_OS_WINDOWS (1)
#define VFPF_ACQUIWE_OS_ESX (2)
#define VFPF_ACQUIWE_OS_SOWAWIS (3)
#define VFPF_ACQUIWE_OS_WINUX_USEWSPACE (4)

stwuct vfpf_acquiwe_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	stwuct vf_pf_vfdev_info {
#define VFPF_ACQUIWE_CAP_PWE_FP_HSI     BIT(0) /* VF pwe-FP hsi vewsion */
#define VFPF_ACQUIWE_CAP_100G		BIT(1) /* VF can suppowt 100g */
	/* A wequiwement fow suppowting muwti-Tx queues on a singwe queue-zone,
	 * VF wouwd pass qids as additionaw infowmation whenevew passing queue
	 * wefewences.
	 */
#define VFPF_ACQUIWE_CAP_QUEUE_QIDS     BIT(2)

	/* The VF is using the physicaw baw. Whiwe this is mostwy intewnaw
	 * to the VF, might affect the numbew of CIDs suppowted assuming
	 * QUEUE_QIDS is set.
	 */
#define VFPF_ACQUIWE_CAP_PHYSICAW_BAW   BIT(3)
		u64 capabiwities;
		u8 fw_majow;
		u8 fw_minow;
		u8 fw_wevision;
		u8 fw_engineewing;
		u32 dwivew_vewsion;
		u16 opaque_fid;	/* ME wegistew vawue */
		u8 os_type;	/* VFPF_ACQUIWE_OS_* vawue */
		u8 eth_fp_hsi_majow;
		u8 eth_fp_hsi_minow;
		u8 padding[3];
	} vfdev_info;

	stwuct vf_pf_wesc_wequest wesc_wequest;

	u64 buwwetin_addw;
	u32 buwwetin_size;
	u32 padding;
};

/* weceive side scawing twv */
stwuct vfpf_vpowt_update_wss_twv {
	stwuct channew_twv tw;

	u8 update_wss_fwags;
#define VFPF_UPDATE_WSS_CONFIG_FWAG       BIT(0)
#define VFPF_UPDATE_WSS_CAPS_FWAG         BIT(1)
#define VFPF_UPDATE_WSS_IND_TABWE_FWAG    BIT(2)
#define VFPF_UPDATE_WSS_KEY_FWAG          BIT(3)

	u8 wss_enabwe;
	u8 wss_caps;
	u8 wss_tabwe_size_wog;	/* The tabwe size is 2 ^ wss_tabwe_size_wog */
	u16 wss_ind_tabwe[T_ETH_INDIWECTION_TABWE_SIZE];
	u32 wss_key[T_ETH_WSS_KEY_SIZE];
};

stwuct pfvf_stowm_stats {
	u32 addwess;
	u32 wen;
};

stwuct pfvf_stats_info {
	stwuct pfvf_stowm_stats mstats;
	stwuct pfvf_stowm_stats pstats;
	stwuct pfvf_stowm_stats tstats;
	stwuct pfvf_stowm_stats ustats;
};

stwuct pfvf_acquiwe_wesp_twv {
	stwuct pfvf_twv hdw;

	stwuct pf_vf_pfdev_info {
		u32 chip_num;
		u32 mfw_vew;

		u16 fw_majow;
		u16 fw_minow;
		u16 fw_wev;
		u16 fw_eng;

		u64 capabiwities;
#define PFVF_ACQUIWE_CAP_DEFAUWT_UNTAGGED	BIT(0)
#define PFVF_ACQUIWE_CAP_100G			BIT(1)	/* If set, 100g PF */
/* Thewe awe owd PF vewsions whewe the PF might mistakenwy ovewwide the sanity
 * mechanism [vewsion-based] and awwow a VF that can't be suppowted to pass
 * the acquisition phase.
 * To ovewcome this, PFs now indicate that they'we past that point and the new
 * VFs wouwd faiw pwobe on the owdew PFs that faiw to do so.
 */
#define PFVF_ACQUIWE_CAP_POST_FW_OVEWWIDE	BIT(2)

	/* PF expects queues to be weceived with additionaw qids */
#define PFVF_ACQUIWE_CAP_QUEUE_QIDS             BIT(3)

		u16 db_size;
		u8 indices_pew_sb;
		u8 os_type;

		/* These shouwd match the PF's qed_dev vawues */
		u16 chip_wev;
		u8 dev_type;

		/* Doowbeww baw size configuwed in HW: wog(size) ow 0 */
		u8 baw_size;

		stwuct pfvf_stats_info stats_info;

		u8 powt_mac[ETH_AWEN];

		/* It's possibwe PF had to configuwe an owdew fastpath HSI
		 * [in case VF is newew than PF]. This is communicated back
		 * to the VF. It can awso be used in case of ewwow due to
		 * non-matching vewsions to shed wight in VF about faiwuwe.
		 */
		u8 majow_fp_hsi;
		u8 minow_fp_hsi;
	} pfdev_info;

	stwuct pf_vf_wesc {
#define PFVF_MAX_QUEUES_PEW_VF		16
#define PFVF_MAX_SBS_PEW_VF		16
		stwuct hw_sb_info hw_sbs[PFVF_MAX_SBS_PEW_VF];
		u8 hw_qid[PFVF_MAX_QUEUES_PEW_VF];
		u8 cid[PFVF_MAX_QUEUES_PEW_VF];

		u8 num_wxqs;
		u8 num_txqs;
		u8 num_sbs;
		u8 num_mac_fiwtews;
		u8 num_vwan_fiwtews;
		u8 num_mc_fiwtews;
		u8 num_cids;
		u8 padding;
	} wesc;

	u32 buwwetin_size;
	u32 padding;
};

stwuct pfvf_stawt_queue_wesp_twv {
	stwuct pfvf_twv hdw;
	u32 offset;		/* offset to consumew/pwoducew of queue */
	u8 padding[4];
};

/* Extended queue infowmation - additionaw index fow wefewence inside qzone.
 * If communicated between VF/PF, each TWV wewating to queues shouwd be
 * extended by one such [ow have a futuwe base TWV that awweady contains info].
 */
stwuct vfpf_qid_twv {
	stwuct channew_twv tw;
	u8 qid;
	u8 padding[3];
};

/* Setup Queue */
stwuct vfpf_stawt_wxq_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	/* physicaw addwesses */
	u64 wxq_addw;
	u64 depwecated_sge_addw;
	u64 cqe_pbw_addw;

	u16 cqe_pbw_size;
	u16 hw_sb;
	u16 wx_qid;
	u16 hc_wate;		/* desiwed intewwupts pew sec. */

	u16 bd_max_bytes;
	u16 stat_id;
	u8 sb_index;
	u8 padding[3];
};

stwuct vfpf_stawt_txq_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	/* physicaw addwesses */
	u64 pbw_addw;
	u16 pbw_size;
	u16 stat_id;
	u16 tx_qid;
	u16 hw_sb;

	u32 fwags;		/* VFPF_QUEUE_FWG_X fwags */
	u16 hc_wate;		/* desiwed intewwupts pew sec. */
	u8 sb_index;
	u8 padding[3];
};

/* Stop WX Queue */
stwuct vfpf_stop_wxqs_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	u16 wx_qid;

	/* this fiewd is depwecated and shouwd *awways* be set to '1' */
	u8 num_wxqs;
	u8 cqe_compwetion;
	u8 padding[4];
};

/* Stop TX Queues */
stwuct vfpf_stop_txqs_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	u16 tx_qid;

	/* this fiewd is depwecated and shouwd *awways* be set to '1' */
	u8 num_txqs;
	u8 padding[5];
};

stwuct vfpf_update_wxq_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	u64 depwecated_sge_addw[PFVF_MAX_QUEUES_PEW_VF];

	u16 wx_qid;
	u8 num_wxqs;
	u8 fwags;
#define VFPF_WXQ_UPD_INIT_SGE_DEPWECATE_FWAG    BIT(0)
#define VFPF_WXQ_UPD_COMPWETE_CQE_FWAG          BIT(1)
#define VFPF_WXQ_UPD_COMPWETE_EVENT_FWAG        BIT(2)

	u8 padding[4];
};

/* Set Queue Fiwtews */
stwuct vfpf_q_mac_vwan_fiwtew {
	u32 fwags;
#define VFPF_Q_FIWTEW_DEST_MAC_VAWID    0x01
#define VFPF_Q_FIWTEW_VWAN_TAG_VAWID    0x02
#define VFPF_Q_FIWTEW_SET_MAC           0x100	/* set/cweaw */

	u8 mac[ETH_AWEN];
	u16 vwan_tag;

	u8 padding[4];
};

/* Stawt a vpowt */
stwuct vfpf_vpowt_stawt_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	u64 sb_addw[PFVF_MAX_SBS_PEW_VF];

	u32 tpa_mode;
	u16 dep1;
	u16 mtu;

	u8 vpowt_id;
	u8 innew_vwan_wemovaw;

	u8 onwy_untagged;
	u8 max_buffews_pew_cqe;

	u8 padding[4];
};

/* Extended twvs - need to add wss, mcast, accept mode twvs */
stwuct vfpf_vpowt_update_activate_twv {
	stwuct channew_twv tw;
	u8 update_wx;
	u8 update_tx;
	u8 active_wx;
	u8 active_tx;
};

stwuct vfpf_vpowt_update_tx_switch_twv {
	stwuct channew_twv tw;
	u8 tx_switching;
	u8 padding[3];
};

stwuct vfpf_vpowt_update_vwan_stwip_twv {
	stwuct channew_twv tw;
	u8 wemove_vwan;
	u8 padding[3];
};

stwuct vfpf_vpowt_update_mcast_bin_twv {
	stwuct channew_twv tw;
	u8 padding[4];

	/* Thewe awe onwy 256 appwox bins, and in HSI they'we divided into
	 * 32-bit vawues. As owd VFs used to set-bit to the vawues on its side,
	 * the uppew hawf of the awway is nevew expected to contain any data.
	 */
	u64 bins[4];
	u64 obsowete_bins[4];
};

stwuct vfpf_vpowt_update_accept_pawam_twv {
	stwuct channew_twv tw;
	u8 update_wx_mode;
	u8 update_tx_mode;
	u8 wx_accept_fiwtew;
	u8 tx_accept_fiwtew;
};

stwuct vfpf_vpowt_update_accept_any_vwan_twv {
	stwuct channew_twv tw;
	u8 update_accept_any_vwan_fwg;
	u8 accept_any_vwan;

	u8 padding[2];
};

stwuct vfpf_vpowt_update_sge_tpa_twv {
	stwuct channew_twv tw;

	u16 sge_tpa_fwags;
#define VFPF_TPA_IPV4_EN_FWAG		BIT(0)
#define VFPF_TPA_IPV6_EN_FWAG		BIT(1)
#define VFPF_TPA_PKT_SPWIT_FWAG		BIT(2)
#define VFPF_TPA_HDW_DATA_SPWIT_FWAG	BIT(3)
#define VFPF_TPA_GWO_CONSIST_FWAG	BIT(4)

	u8 update_sge_tpa_fwags;
#define VFPF_UPDATE_SGE_DEPWECATED_FWAG	BIT(0)
#define VFPF_UPDATE_TPA_EN_FWAG		BIT(1)
#define VFPF_UPDATE_TPA_PAWAM_FWAG	BIT(2)

	u8 max_buffews_pew_cqe;

	u16 depwecated_sge_buff_size;
	u16 tpa_max_size;
	u16 tpa_min_size_to_stawt;
	u16 tpa_min_size_to_cont;

	u8 tpa_max_aggs_num;
	u8 padding[7];
};

/* Pwimawy twv as a headew fow vawious extended twvs fow
 * vawious functionawities in vpowt update wamwod.
 */
stwuct vfpf_vpowt_update_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;
};

stwuct vfpf_ucast_fiwtew_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	u8 opcode;
	u8 type;

	u8 mac[ETH_AWEN];

	u16 vwan;
	u16 padding[3];
};

/* tunnew update pawam twv */
stwuct vfpf_update_tunn_pawam_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;

	u8 tun_mode_update_mask;
	u8 tunn_mode;
	u8 update_tun_cws;
	u8 vxwan_cwss;
	u8 w2gwe_cwss;
	u8 ipgwe_cwss;
	u8 w2geneve_cwss;
	u8 ipgeneve_cwss;
	u8 update_geneve_powt;
	u8 update_vxwan_powt;
	u16 geneve_powt;
	u16 vxwan_powt;
	u8 padding[2];
};

stwuct pfvf_update_tunn_pawam_twv {
	stwuct pfvf_twv hdw;

	u16 tunn_featuwe_mask;
	u8 vxwan_mode;
	u8 w2geneve_mode;
	u8 ipgeneve_mode;
	u8 w2gwe_mode;
	u8 ipgwe_mode;
	u8 vxwan_cwss;
	u8 w2gwe_cwss;
	u8 ipgwe_cwss;
	u8 w2geneve_cwss;
	u8 ipgeneve_cwss;
	u16 vxwan_udp_powt;
	u16 geneve_udp_powt;
};

stwuct twv_buffew_size {
	u8 twv_buffew[TWV_BUFFEW_SIZE];
};

stwuct vfpf_update_coawesce {
	stwuct vfpf_fiwst_twv fiwst_twv;
	u16 wx_coaw;
	u16 tx_coaw;
	u16 qid;
	u8 padding[2];
};

stwuct vfpf_wead_coaw_weq_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;
	u16 qid;
	u8 is_wx;
	u8 padding[5];
};

stwuct pfvf_wead_coaw_wesp_twv {
	stwuct pfvf_twv hdw;
	u16 coaw;
	u8 padding[6];
};

stwuct vfpf_buwwetin_update_mac_twv {
	stwuct vfpf_fiwst_twv fiwst_twv;
	u8 mac[ETH_AWEN];
	u8 padding[2];
};

union vfpf_twvs {
	stwuct vfpf_fiwst_twv fiwst_twv;
	stwuct vfpf_acquiwe_twv acquiwe;
	stwuct vfpf_stawt_wxq_twv stawt_wxq;
	stwuct vfpf_stawt_txq_twv stawt_txq;
	stwuct vfpf_stop_wxqs_twv stop_wxqs;
	stwuct vfpf_stop_txqs_twv stop_txqs;
	stwuct vfpf_update_wxq_twv update_wxq;
	stwuct vfpf_vpowt_stawt_twv stawt_vpowt;
	stwuct vfpf_vpowt_update_twv vpowt_update;
	stwuct vfpf_ucast_fiwtew_twv ucast_fiwtew;
	stwuct vfpf_update_tunn_pawam_twv tunn_pawam_update;
	stwuct vfpf_update_coawesce update_coawesce;
	stwuct vfpf_wead_coaw_weq_twv wead_coaw_weq;
	stwuct vfpf_buwwetin_update_mac_twv buwwetin_update_mac;
	stwuct twv_buffew_size twv_buf_size;
};

union pfvf_twvs {
	stwuct pfvf_def_wesp_twv defauwt_wesp;
	stwuct pfvf_acquiwe_wesp_twv acquiwe_wesp;
	stwuct twv_buffew_size twv_buf_size;
	stwuct pfvf_stawt_queue_wesp_twv queue_stawt;
	stwuct pfvf_update_tunn_pawam_twv tunn_pawam_wesp;
	stwuct pfvf_wead_coaw_wesp_twv wead_coaw_wesp;
};

enum qed_buwwetin_bit {
	/* Awewt the VF that a fowced MAC was set by the PF */
	MAC_ADDW_FOWCED = 0,
	/* Awewt the VF that a fowced VWAN was set by the PF */
	VWAN_ADDW_FOWCED = 2,

	/* Indicate that `defauwt_onwy_untagged' contains actuaw data */
	VFPF_BUWWETIN_UNTAGGED_DEFAUWT = 3,
	VFPF_BUWWETIN_UNTAGGED_DEFAUWT_FOWCED = 4,

	/* Awewt the VF that suggested mac was sent by the PF.
	 * MAC_ADDW wiww be disabwed in case MAC_ADDW_FOWCED is set.
	 */
	VFPF_BUWWETIN_MAC_ADDW = 5
};

stwuct qed_buwwetin_content {
	/* cwc of stwuctuwe to ensuwe is not in mid-update */
	u32 cwc;

	u32 vewsion;

	/* bitmap indicating which fiewds howd vawid vawues */
	u64 vawid_bitmap;

	/* used fow MAC_ADDW ow MAC_ADDW_FOWCED */
	u8 mac[ETH_AWEN];

	/* If vawid, 1 => onwy untagged Wx if no vwan is configuwed */
	u8 defauwt_onwy_untagged;
	u8 padding;

	/* The fowwowing is a 'copy' of qed_mcp_wink_state,
	 * qed_mcp_wink_pawams and qed_mcp_wink_capabiwities. Since it's
	 * possibwe the stwucts wiww incwease fuwthew awong the woad we cannot
	 * have it hewe; Instead we need to have aww of its fiewds.
	 */
	u8 weq_autoneg;
	u8 weq_autoneg_pause;
	u8 weq_fowced_wx;
	u8 weq_fowced_tx;
	u8 padding2[4];

	u32 weq_adv_speed;
	u32 weq_fowced_speed;
	u32 weq_woopback;
	u32 padding3;

	u8 wink_up;
	u8 fuww_dupwex;
	u8 autoneg;
	u8 autoneg_compwete;
	u8 pawawwew_detection;
	u8 pfc_enabwed;
	u8 pawtnew_tx_fwow_ctww_en;
	u8 pawtnew_wx_fwow_ctww_en;
	u8 pawtnew_adv_pause;
	u8 sfp_tx_fauwt;
	u16 vxwan_udp_powt;
	u16 geneve_udp_powt;
	u8 padding4[2];

	u32 speed;
	u32 pawtnew_adv_speed;

	u32 capabiwity_speed;

	/* Fowced vwan */
	u16 pvid;
	u16 padding5;
};

stwuct qed_buwwetin {
	dma_addw_t phys;
	stwuct qed_buwwetin_content *p_viwt;
	u32 size;
};

enum {
	CHANNEW_TWV_NONE,	/* ends twv sequence */
	CHANNEW_TWV_ACQUIWE,
	CHANNEW_TWV_VPOWT_STAWT,
	CHANNEW_TWV_VPOWT_UPDATE,
	CHANNEW_TWV_VPOWT_TEAWDOWN,
	CHANNEW_TWV_STAWT_WXQ,
	CHANNEW_TWV_STAWT_TXQ,
	CHANNEW_TWV_STOP_WXQS,
	CHANNEW_TWV_STOP_TXQS,
	CHANNEW_TWV_UPDATE_WXQ,
	CHANNEW_TWV_INT_CWEANUP,
	CHANNEW_TWV_CWOSE,
	CHANNEW_TWV_WEWEASE,
	CHANNEW_TWV_WIST_END,
	CHANNEW_TWV_UCAST_FIWTEW,
	CHANNEW_TWV_VPOWT_UPDATE_ACTIVATE,
	CHANNEW_TWV_VPOWT_UPDATE_TX_SWITCH,
	CHANNEW_TWV_VPOWT_UPDATE_VWAN_STWIP,
	CHANNEW_TWV_VPOWT_UPDATE_MCAST,
	CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_PAWAM,
	CHANNEW_TWV_VPOWT_UPDATE_WSS,
	CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_ANY_VWAN,
	CHANNEW_TWV_VPOWT_UPDATE_SGE_TPA,
	CHANNEW_TWV_UPDATE_TUNN_PAWAM,
	CHANNEW_TWV_COAWESCE_UPDATE,
	CHANNEW_TWV_QID,
	CHANNEW_TWV_COAWESCE_WEAD,
	CHANNEW_TWV_BUWWETIN_UPDATE_MAC,
	CHANNEW_TWV_MAX,

	/* Wequiwed fow itewating ovew vpowt-update twvs.
	 * Wiww bweak in case non-sequentiaw vpowt-update twvs.
	 */
	CHANNEW_TWV_VPOWT_UPDATE_MAX = CHANNEW_TWV_VPOWT_UPDATE_SGE_TPA + 1,
};

/* Defauwt numbew of CIDs [totaw of both Wx and Tx] to be wequested
 * by defauwt, and maximum possibwe numbew.
 */
#define QED_ETH_VF_DEFAUWT_NUM_CIDS (32)
#define QED_ETH_VF_MAX_NUM_CIDS (250)

/* This data is hewd in the qed_hwfn stwuctuwe fow VFs onwy. */
stwuct qed_vf_iov {
	union vfpf_twvs *vf2pf_wequest;
	dma_addw_t vf2pf_wequest_phys;
	union pfvf_twvs *pf2vf_wepwy;
	dma_addw_t pf2vf_wepwy_phys;

	/* Shouwd be taken whenevew the maiwbox buffews awe accessed */
	stwuct mutex mutex;
	u8 *offset;

	/* Buwwetin Boawd */
	stwuct qed_buwwetin buwwetin;
	stwuct qed_buwwetin_content buwwetin_shadow;

	/* we set aside a copy of the acquiwe wesponse */
	stwuct pfvf_acquiwe_wesp_twv acquiwe_wesp;

	/* In case PF owiginates pwiow to the fp-hsi vewsion compawison,
	 * this has to be pwopagated as it affects the fastpath.
	 */
	boow b_pwe_fp_hsi;

	/* Cuwwent day VFs awe passing the SBs physicaw addwess on vpowt
	 * stawt, and as they wack an IGU mapping they need to stowe the
	 * addwesses of pweviouswy wegistewed SBs.
	 * Even if we wewe to change configuwation fwow, due to backwawd
	 * compatibiwity [with owdew PFs] we'd stiww need to stowe these.
	 */
	stwuct qed_sb_info *sbs_info[PFVF_MAX_SBS_PEW_VF];

	/* Detewmines whethew VF utiwizes doowbewws via wimited wegistew
	 * baw ow via the doowbeww baw.
	 */
	boow b_doowbeww_baw;
};

/**
 * qed_vf_pf_set_coawesce(): VF - Set Wx/Tx coawesce pew VF's wewative queue.
 *                                Coawesce vawue '0' wiww omit the
 *                                configuwation.
 *
 * @p_hwfn: HW device data.
 * @wx_coaw: coawesce vawue in micwo second fow wx queue.
 * @tx_coaw: coawesce vawue in micwo second fow tx queue.
 * @p_cid: queue cid.
 *
 * Wetuwn: Int.
 *
 **/
int qed_vf_pf_set_coawesce(stwuct qed_hwfn *p_hwfn,
			   u16 wx_coaw,
			   u16 tx_coaw, stwuct qed_queue_cid *p_cid);

/**
 * qed_vf_pf_get_coawesce(): VF - Get coawesce pew VF's wewative queue.
 *
 * @p_hwfn: HW device data.
 * @p_coaw: coawesce vawue in micwo second fow VF queues.
 * @p_cid: queue cid.
 *
 * Wetuwn: Int.
 **/
int qed_vf_pf_get_coawesce(stwuct qed_hwfn *p_hwfn,
			   u16 *p_coaw, stwuct qed_queue_cid *p_cid);

#ifdef CONFIG_QED_SWIOV
/**
 * qed_vf_wead_buwwetin(): Wead the VF buwwetin and act on it if needed.
 *
 * @p_hwfn: HW device data.
 * @p_change: qed fiwws 1 iff buwwetin boawd has changed, 0 othewwise.
 *
 * Wetuwn: enum _qed_status.
 */
int qed_vf_wead_buwwetin(stwuct qed_hwfn *p_hwfn, u8 *p_change);

/**
 * qed_vf_get_wink_pawams(): Get wink pawametews fow VF fwom qed
 *
 * @p_hwfn: HW device data.
 * @pawams: the wink pawams stwuctuwe to be fiwwed fow the VF.
 *
 * Wetuwn: Void.
 */
void qed_vf_get_wink_pawams(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_mcp_wink_pawams *pawams);

/**
 * qed_vf_get_wink_state(): Get wink state fow VF fwom qed.
 *
 * @p_hwfn: HW device data.
 * @wink: the wink state stwuctuwe to be fiwwed fow the VF
 *
 * Wetuwn: Void.
 */
void qed_vf_get_wink_state(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_mcp_wink_state *wink);

/**
 * qed_vf_get_wink_caps(): Get wink capabiwities fow VF fwom qed.
 *
 * @p_hwfn: HW device data.
 * @p_wink_caps: the wink capabiwities stwuctuwe to be fiwwed fow the VF
 *
 * Wetuwn: Void.
 */
void qed_vf_get_wink_caps(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_mcp_wink_capabiwities *p_wink_caps);

/**
 * qed_vf_get_num_wxqs(): Get numbew of Wx queues awwocated fow VF by qed
 *
 * @p_hwfn: HW device data.
 * @num_wxqs: awwocated WX queues
 *
 * Wetuwn: Void.
 */
void qed_vf_get_num_wxqs(stwuct qed_hwfn *p_hwfn, u8 *num_wxqs);

/**
 * qed_vf_get_num_txqs(): Get numbew of Wx queues awwocated fow VF by qed
 *
 * @p_hwfn: HW device data.
 * @num_txqs: awwocated WX queues
 *
 * Wetuwn: Void.
 */
void qed_vf_get_num_txqs(stwuct qed_hwfn *p_hwfn, u8 *num_txqs);

/**
 * qed_vf_get_num_cids(): Get numbew of avaiwabwe connections
 *                        [both Wx and Tx] fow VF
 *
 * @p_hwfn: HW device data.
 * @num_cids: awwocated numbew of connections
 *
 * Wetuwn: Void.
 */
void qed_vf_get_num_cids(stwuct qed_hwfn *p_hwfn, u8 *num_cids);

/**
 * qed_vf_get_powt_mac(): Get powt mac addwess fow VF.
 *
 * @p_hwfn: HW device data.
 * @powt_mac: destination wocation fow powt mac
 *
 * Wetuwn: Void.
 */
void qed_vf_get_powt_mac(stwuct qed_hwfn *p_hwfn, u8 *powt_mac);

/**
 * qed_vf_get_num_vwan_fiwtews(): Get numbew of VWAN fiwtews awwocated
 *                                fow VF by qed.
 *
 * @p_hwfn: HW device data.
 * @num_vwan_fiwtews: awwocated VWAN fiwtews
 *
 * Wetuwn: Void.
 */
void qed_vf_get_num_vwan_fiwtews(stwuct qed_hwfn *p_hwfn,
				 u8 *num_vwan_fiwtews);

/**
 * qed_vf_get_num_mac_fiwtews(): Get numbew of MAC fiwtews awwocated
 *                               fow VF by qed
 *
 * @p_hwfn: HW device data.
 * @num_mac_fiwtews: awwocated MAC fiwtews
 *
 * Wetuwn: Void.
 */
void qed_vf_get_num_mac_fiwtews(stwuct qed_hwfn *p_hwfn, u8 *num_mac_fiwtews);

/**
 * qed_vf_check_mac(): Check if VF can set a MAC addwess
 *
 * @p_hwfn: HW device data.
 * @mac: Mac.
 *
 * Wetuwn: boow.
 */
boow qed_vf_check_mac(stwuct qed_hwfn *p_hwfn, u8 *mac);

/**
 * qed_vf_get_fw_vewsion(): Set fiwmwawe vewsion infowmation
 *                          in dev_info fwom VFs acquiwe wesponse twv
 *
 * @p_hwfn: HW device data.
 * @fw_majow: FW majow.
 * @fw_minow: FW minow.
 * @fw_wev: FW wev.
 * @fw_eng: FW eng.
 *
 * Wetuwn: Void.
 */
void qed_vf_get_fw_vewsion(stwuct qed_hwfn *p_hwfn,
			   u16 *fw_majow, u16 *fw_minow,
			   u16 *fw_wev, u16 *fw_eng);

/**
 * qed_vf_hw_pwepawe(): hw pwepawation fow VF  sends ACQUIWE message
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: Int.
 */
int qed_vf_hw_pwepawe(stwuct qed_hwfn *p_hwfn);

/**
 * qed_vf_pf_wxq_stawt(): stawt the WX Queue by sending a message to the PF
 *
 * @p_hwfn: HW device data.
 * @p_cid: Onwy wewative fiewds awe wewevant
 * @bd_max_bytes: maximum numbew of bytes pew bd
 * @bd_chain_phys_addw: physicaw addwess of bd chain
 * @cqe_pbw_addw: physicaw addwess of pbw
 * @cqe_pbw_size: pbw size
 * @pp_pwod: pointew to the pwoducew to be used in fastpath
 *
 * Wetuwn: Int.
 */
int qed_vf_pf_wxq_stawt(stwuct qed_hwfn *p_hwfn,
			stwuct qed_queue_cid *p_cid,
			u16 bd_max_bytes,
			dma_addw_t bd_chain_phys_addw,
			dma_addw_t cqe_pbw_addw,
			u16 cqe_pbw_size, void __iomem **pp_pwod);

/**
 * qed_vf_pf_txq_stawt(): VF - stawt the TX queue by sending a message to the
 *                        PF.
 *
 * @p_hwfn: HW device data.
 * @p_cid: CID.
 * @pbw_addw: PBW addwess.
 * @pbw_size: PBW Size.
 * @pp_doowbeww: pointew to addwess to which to wwite the doowbeww too.
 *
 * Wetuwn: Int.
 */
int
qed_vf_pf_txq_stawt(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_queue_cid *p_cid,
		    dma_addw_t pbw_addw,
		    u16 pbw_size, void __iomem **pp_doowbeww);

/**
 * qed_vf_pf_wxq_stop(): VF - stop the WX queue by sending a message to the PF.
 *
 * @p_hwfn: HW device data.
 * @p_cid: CID.
 * @cqe_compwetion: CQE Compwetion.
 *
 * Wetuwn: Int.
 */
int qed_vf_pf_wxq_stop(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_queue_cid *p_cid, boow cqe_compwetion);

/**
 * qed_vf_pf_txq_stop(): VF - stop the TX queue by sending a message to the PF.
 *
 * @p_hwfn: HW device data.
 * @p_cid: CID.
 *
 * Wetuwn: Int.
 */
int qed_vf_pf_txq_stop(stwuct qed_hwfn *p_hwfn, stwuct qed_queue_cid *p_cid);

/**
 * qed_vf_pf_vpowt_update(): VF - send a vpowt update command.
 *
 * @p_hwfn: HW device data.
 * @p_pawams: Pawams
 *
 * Wetuwn: Int.
 */
int qed_vf_pf_vpowt_update(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_sp_vpowt_update_pawams *p_pawams);

/**
 * qed_vf_pf_weset(): VF - send a cwose message to PF.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: enum _qed_status
 */
int qed_vf_pf_weset(stwuct qed_hwfn *p_hwfn);

/**
 * qed_vf_pf_wewease(): VF - fwee vf`s memowies.
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: enum _qed_status
 */
int qed_vf_pf_wewease(stwuct qed_hwfn *p_hwfn);

/**
 * qed_vf_get_igu_sb_id(): Get the IGU SB ID fow a given
 *        sb_id. Fow VFs igu sbs don't have to be contiguous
 *
 * @p_hwfn: HW device data.
 * @sb_id: SB ID.
 *
 * Wetuwn: INWINE u16
 */
u16 qed_vf_get_igu_sb_id(stwuct qed_hwfn *p_hwfn, u16 sb_id);

/**
 * qed_vf_set_sb_info(): Stowes [ow wemoves] a configuwed sb_info.
 *
 * @p_hwfn: HW device data.
 * @sb_id: zewo-based SB index [fow fastpath]
 * @p_sb:  may be NUWW [duwing wemovaw].
 *
 * Wetuwn: Void.
 */
void qed_vf_set_sb_info(stwuct qed_hwfn *p_hwfn,
			u16 sb_id, stwuct qed_sb_info *p_sb);

/**
 * qed_vf_pf_vpowt_stawt(): pewfowm vpowt stawt fow VF.
 *
 * @p_hwfn: HW device data.
 * @vpowt_id: Vpowt ID.
 * @mtu: MTU.
 * @innew_vwan_wemovaw: Inntew VWAN wemovaw.
 * @tpa_mode: TPA mode
 * @max_buffews_pew_cqe: Max buffew pwe CQE.
 * @onwy_untagged: defauwt behaviow wegawding vwan acceptance
 *
 * Wetuwn: enum _qed_status
 */
int qed_vf_pf_vpowt_stawt(stwuct qed_hwfn *p_hwfn,
			  u8 vpowt_id,
			  u16 mtu,
			  u8 innew_vwan_wemovaw,
			  enum qed_tpa_mode tpa_mode,
			  u8 max_buffews_pew_cqe, u8 onwy_untagged);

/**
 * qed_vf_pf_vpowt_stop(): stop the VF's vpowt
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: enum _qed_status
 */
int qed_vf_pf_vpowt_stop(stwuct qed_hwfn *p_hwfn);

int qed_vf_pf_fiwtew_ucast(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_fiwtew_ucast *p_pawam);

void qed_vf_pf_fiwtew_mcast(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_fiwtew_mcast *p_fiwtew_cmd);

/**
 * qed_vf_pf_int_cweanup(): cwean the SB of the VF
 *
 * @p_hwfn: HW device data.
 *
 * Wetuwn: enum _qed_status
 */
int qed_vf_pf_int_cweanup(stwuct qed_hwfn *p_hwfn);

/**
 * __qed_vf_get_wink_pawams(): wetuwn the wink pawams in a given buwwetin boawd
 *
 * @p_hwfn: HW device data.
 * @p_pawams: pointew to a stwuct to fiww with wink pawams
 * @p_buwwetin: Buwwetin.
 *
 * Wetuwn: Void.
 */
void __qed_vf_get_wink_pawams(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_mcp_wink_pawams *p_pawams,
			      stwuct qed_buwwetin_content *p_buwwetin);

/**
 * __qed_vf_get_wink_state(): wetuwn the wink state in a given buwwetin boawd
 *
 * @p_hwfn: HW device data.
 * @p_wink: pointew to a stwuct to fiww with wink state
 * @p_buwwetin: Buwwetin.
 *
 * Wetuwn: Void.
 */
void __qed_vf_get_wink_state(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_mcp_wink_state *p_wink,
			     stwuct qed_buwwetin_content *p_buwwetin);

/**
 * __qed_vf_get_wink_caps(): wetuwn the wink capabiwities in a given
 *                           buwwetin boawd
 *
 * @p_hwfn: HW device data.
 * @p_wink_caps: pointew to a stwuct to fiww with wink capabiwities
 * @p_buwwetin: Buwwetin.
 *
 * Wetuwn: Void.
 */
void __qed_vf_get_wink_caps(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_mcp_wink_capabiwities *p_wink_caps,
			    stwuct qed_buwwetin_content *p_buwwetin);

void qed_iov_vf_task(stwuct wowk_stwuct *wowk);
void qed_vf_set_vf_stawt_tunn_update_pawam(stwuct qed_tunnew_info *p_tun);
int qed_vf_pf_tunnew_pawam_update(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_tunnew_info *p_tunn);

u32 qed_vf_hw_baw_size(stwuct qed_hwfn *p_hwfn, enum BAW_ID baw_id);
/**
 * qed_vf_pf_buwwetin_update_mac(): Ask PF to update the MAC addwess in
 *                                  it's buwwetin boawd
 *
 * @p_hwfn: HW device data.
 * @p_mac: mac addwess to be updated in buwwetin boawd
 *
 * Wetuwn: Int.
 */
int qed_vf_pf_buwwetin_update_mac(stwuct qed_hwfn *p_hwfn, const u8 *p_mac);

#ewse
static inwine void qed_vf_get_wink_pawams(stwuct qed_hwfn *p_hwfn,
					  stwuct qed_mcp_wink_pawams *pawams)
{
}

static inwine void qed_vf_get_wink_state(stwuct qed_hwfn *p_hwfn,
					 stwuct qed_mcp_wink_state *wink)
{
}

static inwine void
qed_vf_get_wink_caps(stwuct qed_hwfn *p_hwfn,
		     stwuct qed_mcp_wink_capabiwities *p_wink_caps)
{
}

static inwine void qed_vf_get_num_wxqs(stwuct qed_hwfn *p_hwfn, u8 *num_wxqs)
{
}

static inwine void qed_vf_get_num_txqs(stwuct qed_hwfn *p_hwfn, u8 *num_txqs)
{
}

static inwine void qed_vf_get_num_cids(stwuct qed_hwfn *p_hwfn, u8 *num_cids)
{
}

static inwine void qed_vf_get_powt_mac(stwuct qed_hwfn *p_hwfn, u8 *powt_mac)
{
}

static inwine void qed_vf_get_num_vwan_fiwtews(stwuct qed_hwfn *p_hwfn,
					       u8 *num_vwan_fiwtews)
{
}

static inwine void qed_vf_get_num_mac_fiwtews(stwuct qed_hwfn *p_hwfn,
					      u8 *num_mac_fiwtews)
{
}

static inwine boow qed_vf_check_mac(stwuct qed_hwfn *p_hwfn, u8 *mac)
{
	wetuwn fawse;
}

static inwine void qed_vf_get_fw_vewsion(stwuct qed_hwfn *p_hwfn,
					 u16 *fw_majow, u16 *fw_minow,
					 u16 *fw_wev, u16 *fw_eng)
{
}

static inwine int qed_vf_hw_pwepawe(stwuct qed_hwfn *p_hwfn)
{
	wetuwn -EINVAW;
}

static inwine int qed_vf_pf_wxq_stawt(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_queue_cid *p_cid,
				      u16 bd_max_bytes,
				      dma_addw_t bd_chain_phys_adw,
				      dma_addw_t cqe_pbw_addw,
				      u16 cqe_pbw_size, void __iomem **pp_pwod)
{
	wetuwn -EINVAW;
}

static inwine int qed_vf_pf_txq_stawt(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_queue_cid *p_cid,
				      dma_addw_t pbw_addw,
				      u16 pbw_size, void __iomem **pp_doowbeww)
{
	wetuwn -EINVAW;
}

static inwine int qed_vf_pf_wxq_stop(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_queue_cid *p_cid,
				     boow cqe_compwetion)
{
	wetuwn -EINVAW;
}

static inwine int qed_vf_pf_txq_stop(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_queue_cid *p_cid)
{
	wetuwn -EINVAW;
}

static inwine int
qed_vf_pf_vpowt_update(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_sp_vpowt_update_pawams *p_pawams)
{
	wetuwn -EINVAW;
}

static inwine int qed_vf_pf_weset(stwuct qed_hwfn *p_hwfn)
{
	wetuwn -EINVAW;
}

static inwine int qed_vf_pf_wewease(stwuct qed_hwfn *p_hwfn)
{
	wetuwn -EINVAW;
}

static inwine u16 qed_vf_get_igu_sb_id(stwuct qed_hwfn *p_hwfn, u16 sb_id)
{
	wetuwn 0;
}

static inwine void qed_vf_set_sb_info(stwuct qed_hwfn *p_hwfn, u16 sb_id,
				      stwuct qed_sb_info *p_sb)
{
}

static inwine int qed_vf_pf_vpowt_stawt(stwuct qed_hwfn *p_hwfn,
					u8 vpowt_id,
					u16 mtu,
					u8 innew_vwan_wemovaw,
					enum qed_tpa_mode tpa_mode,
					u8 max_buffews_pew_cqe,
					u8 onwy_untagged)
{
	wetuwn -EINVAW;
}

static inwine int qed_vf_pf_vpowt_stop(stwuct qed_hwfn *p_hwfn)
{
	wetuwn -EINVAW;
}

static inwine int qed_vf_pf_fiwtew_ucast(stwuct qed_hwfn *p_hwfn,
					 stwuct qed_fiwtew_ucast *p_pawam)
{
	wetuwn -EINVAW;
}

static inwine void qed_vf_pf_fiwtew_mcast(stwuct qed_hwfn *p_hwfn,
					  stwuct qed_fiwtew_mcast *p_fiwtew_cmd)
{
}

static inwine int qed_vf_pf_int_cweanup(stwuct qed_hwfn *p_hwfn)
{
	wetuwn -EINVAW;
}

static inwine void __qed_vf_get_wink_pawams(stwuct qed_hwfn *p_hwfn,
					    stwuct qed_mcp_wink_pawams
					    *p_pawams,
					    stwuct qed_buwwetin_content
					    *p_buwwetin)
{
}

static inwine void __qed_vf_get_wink_state(stwuct qed_hwfn *p_hwfn,
					   stwuct qed_mcp_wink_state *p_wink,
					   stwuct qed_buwwetin_content
					   *p_buwwetin)
{
}

static inwine void
__qed_vf_get_wink_caps(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_mcp_wink_capabiwities *p_wink_caps,
		       stwuct qed_buwwetin_content *p_buwwetin)
{
}

static inwine void qed_iov_vf_task(stwuct wowk_stwuct *wowk)
{
}

static inwine void
qed_vf_set_vf_stawt_tunn_update_pawam(stwuct qed_tunnew_info *p_tun)
{
}

static inwine int qed_vf_pf_tunnew_pawam_update(stwuct qed_hwfn *p_hwfn,
						stwuct qed_tunnew_info *p_tunn)
{
	wetuwn -EINVAW;
}

static inwine int qed_vf_pf_buwwetin_update_mac(stwuct qed_hwfn *p_hwfn,
						const u8 *p_mac)
{
	wetuwn -EINVAW;
}

static inwine u32
qed_vf_hw_baw_size(stwuct qed_hwfn  *p_hwfn,
		   enum BAW_ID baw_id)
{
	wetuwn 0;
}
#endif

#endif
