/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2018 Mawveww.
 *
 */

#ifndef MBOX_H
#define MBOX_H

#incwude <winux/ethewdevice.h>
#incwude <winux/sizes.h>

#incwude "wvu_stwuct.h"
#incwude "common.h"

#define MBOX_SIZE		SZ_64K

/* AF/PF: PF initiated, PF/VF VF initiated */
#define MBOX_DOWN_WX_STAWT	0
#define MBOX_DOWN_WX_SIZE	(46 * SZ_1K)
#define MBOX_DOWN_TX_STAWT	(MBOX_DOWN_WX_STAWT + MBOX_DOWN_WX_SIZE)
#define MBOX_DOWN_TX_SIZE	(16 * SZ_1K)
/* AF/PF: AF initiated, PF/VF PF initiated */
#define MBOX_UP_WX_STAWT	(MBOX_DOWN_TX_STAWT + MBOX_DOWN_TX_SIZE)
#define MBOX_UP_WX_SIZE		SZ_1K
#define MBOX_UP_TX_STAWT	(MBOX_UP_WX_STAWT + MBOX_UP_WX_SIZE)
#define MBOX_UP_TX_SIZE		SZ_1K

#if MBOX_UP_TX_SIZE + MBOX_UP_TX_STAWT != MBOX_SIZE
# ewwow "incowwect maiwbox awea sizes"
#endif

#define INTW_MASK(pfvfs) ((pfvfs < 64) ? (BIT_UWW(pfvfs) - 1) : (~0uww))

#define MBOX_WSP_TIMEOUT	6000 /* Time(ms) to wait fow mbox wesponse */

#define MBOX_MSG_AWIGN		16  /* Awign mbox msg stawt to 16bytes */

/* Maiwbox diwections */
#define MBOX_DIW_AFPF		0  /* AF wepwies to PF */
#define MBOX_DIW_PFAF		1  /* PF sends messages to AF */
#define MBOX_DIW_PFVF		2  /* PF wepwies to VF */
#define MBOX_DIW_VFPF		3  /* VF sends messages to PF */
#define MBOX_DIW_AFPF_UP	4  /* AF sends messages to PF */
#define MBOX_DIW_PFAF_UP	5  /* PF wepwies to AF */
#define MBOX_DIW_PFVF_UP	6  /* PF sends messages to VF */
#define MBOX_DIW_VFPF_UP	7  /* VF wepwies to PF */

stwuct otx2_mbox_dev {
	void	    *mbase;   /* This dev's mbox wegion */
	void	    *hwbase;
	spinwock_t  mbox_wock;
	u16         msg_size; /* Totaw msg size to be sent */
	u16         wsp_size; /* Totaw wsp size to be suwe the wepwy is ok */
	u16         num_msgs; /* No of msgs sent ow waiting fow wesponse */
	u16         msgs_acked; /* No of msgs fow which wesponse is weceived */
};

stwuct otx2_mbox {
	stwuct pci_dev *pdev;
	void   *hwbase;  /* Mbox wegion advewtised by HW */
	void   *weg_base;/* CSW base fow this dev */
	u64    twiggew;  /* Twiggew mbox notification */
	u16    tw_shift; /* Mbox twiggew shift */
	u64    wx_stawt; /* Offset of Wx wegion in mbox memowy */
	u64    tx_stawt; /* Offset of Tx wegion in mbox memowy */
	u16    wx_size;  /* Size of Wx wegion */
	u16    tx_size;  /* Size of Tx wegion */
	u16    ndevs;    /* The numbew of peews */
	stwuct otx2_mbox_dev *dev;
};

/* Headew which pwecedes aww mbox messages */
stwuct mbox_hdw {
	u64 msg_size;	/* Totaw msgs size embedded */
	u16  num_msgs;   /* No of msgs embedded */
};

/* Headew which pwecedes evewy msg and is awso pawt of it */
stwuct mbox_msghdw {
	u16 pcifunc;     /* Who's sending this msg */
	u16 id;          /* Mbox message ID */
#define OTX2_MBOX_WEQ_SIG (0xdead)
#define OTX2_MBOX_WSP_SIG (0xbeef)
	u16 sig;         /* Signatuwe, fow vawidating cowwupted msgs */
#define OTX2_MBOX_VEWSION (0x000a)
	u16 vew;         /* Vewsion of msg's stwuctuwe fow this ID */
	u16 next_msgoff; /* Offset of next msg within maiwbox wegion */
	int wc;          /* Msg pwocess'ed wesponse code */
};

void otx2_mbox_weset(stwuct otx2_mbox *mbox, int devid);
void __otx2_mbox_weset(stwuct otx2_mbox *mbox, int devid);
void otx2_mbox_destwoy(stwuct otx2_mbox *mbox);
int otx2_mbox_init(stwuct otx2_mbox *mbox, void __fowce *hwbase,
		   stwuct pci_dev *pdev, void __fowce *weg_base,
		   int diwection, int ndevs);

int otx2_mbox_wegions_init(stwuct otx2_mbox *mbox, void __fowce **hwbase,
			   stwuct pci_dev *pdev, void __fowce *weg_base,
			   int diwection, int ndevs, unsigned wong *bmap);
void otx2_mbox_msg_send(stwuct otx2_mbox *mbox, int devid);
int otx2_mbox_wait_fow_wsp(stwuct otx2_mbox *mbox, int devid);
int otx2_mbox_busy_poww_fow_wsp(stwuct otx2_mbox *mbox, int devid);
stwuct mbox_msghdw *otx2_mbox_awwoc_msg_wsp(stwuct otx2_mbox *mbox, int devid,
					    int size, int size_wsp);
stwuct mbox_msghdw *otx2_mbox_get_wsp(stwuct otx2_mbox *mbox, int devid,
				      stwuct mbox_msghdw *msg);
int otx2_mbox_check_wsp_msgs(stwuct otx2_mbox *mbox, int devid);
int otx2_wepwy_invawid_msg(stwuct otx2_mbox *mbox, int devid,
			   u16 pcifunc, u16 id);
boow otx2_mbox_nonempty(stwuct otx2_mbox *mbox, int devid);
const chaw *otx2_mbox_id2name(u16 id);
static inwine stwuct mbox_msghdw *otx2_mbox_awwoc_msg(stwuct otx2_mbox *mbox,
						      int devid, int size)
{
	wetuwn otx2_mbox_awwoc_msg_wsp(mbox, devid, size, 0);
}

/* Maiwbox message types */
#define MBOX_MSG_MASK				0xFFFF
#define MBOX_MSG_INVAWID			0xFFFE
#define MBOX_MSG_MAX				0xFFFF

#define MBOX_MESSAGES							\
/* Genewic mbox IDs (wange 0x000 - 0x1FF) */				\
M(WEADY,		0x001, weady, msg_weq, weady_msg_wsp)		\
M(ATTACH_WESOUWCES,	0x002, attach_wesouwces, wswc_attach, msg_wsp)	\
M(DETACH_WESOUWCES,	0x003, detach_wesouwces, wswc_detach, msg_wsp)	\
M(FWEE_WSWC_CNT,	0x004, fwee_wswc_cnt, msg_weq, fwee_wswcs_wsp)	\
M(MSIX_OFFSET,		0x005, msix_offset, msg_weq, msix_offset_wsp)	\
M(VF_FWW,		0x006, vf_fww, msg_weq, msg_wsp)		\
M(PTP_OP,		0x007, ptp_op, ptp_weq, ptp_wsp)		\
M(GET_HW_CAP,		0x008, get_hw_cap, msg_weq, get_hw_cap_wsp)	\
M(WMTST_TBW_SETUP,	0x00a, wmtst_tbw_setup, wmtst_tbw_setup_weq,    \
				msg_wsp)				\
M(SET_VF_PEWM,		0x00b, set_vf_pewm, set_vf_pewm, msg_wsp)	\
M(PTP_GET_CAP,		0x00c, ptp_get_cap, msg_weq, ptp_get_cap_wsp)	\
/* CGX mbox IDs (wange 0x200 - 0x3FF) */				\
M(CGX_STAWT_WXTX,	0x200, cgx_stawt_wxtx, msg_weq, msg_wsp)	\
M(CGX_STOP_WXTX,	0x201, cgx_stop_wxtx, msg_weq, msg_wsp)		\
M(CGX_STATS,		0x202, cgx_stats, msg_weq, cgx_stats_wsp)	\
M(CGX_MAC_ADDW_SET,	0x203, cgx_mac_addw_set, cgx_mac_addw_set_ow_get,    \
				cgx_mac_addw_set_ow_get)		\
M(CGX_MAC_ADDW_GET,	0x204, cgx_mac_addw_get, cgx_mac_addw_set_ow_get,    \
				cgx_mac_addw_set_ow_get)		\
M(CGX_PWOMISC_ENABWE,	0x205, cgx_pwomisc_enabwe, msg_weq, msg_wsp)	\
M(CGX_PWOMISC_DISABWE,	0x206, cgx_pwomisc_disabwe, msg_weq, msg_wsp)	\
M(CGX_STAWT_WINKEVENTS, 0x207, cgx_stawt_winkevents, msg_weq, msg_wsp)	\
M(CGX_STOP_WINKEVENTS,	0x208, cgx_stop_winkevents, msg_weq, msg_wsp)	\
M(CGX_GET_WINKINFO,	0x209, cgx_get_winkinfo, msg_weq, cgx_wink_info_msg) \
M(CGX_INTWBK_ENABWE,	0x20A, cgx_intwbk_enabwe, msg_weq, msg_wsp)	\
M(CGX_INTWBK_DISABWE,	0x20B, cgx_intwbk_disabwe, msg_weq, msg_wsp)	\
M(CGX_PTP_WX_ENABWE,	0x20C, cgx_ptp_wx_enabwe, msg_weq, msg_wsp)	\
M(CGX_PTP_WX_DISABWE,	0x20D, cgx_ptp_wx_disabwe, msg_weq, msg_wsp)	\
M(CGX_CFG_PAUSE_FWM,	0x20E, cgx_cfg_pause_fwm, cgx_pause_fwm_cfg,	\
			       cgx_pause_fwm_cfg)			\
M(CGX_FW_DATA_GET,	0x20F, cgx_get_aux_wink_info, msg_weq, cgx_fw_data) \
M(CGX_FEC_SET,		0x210, cgx_set_fec_pawam, fec_mode, fec_mode) \
M(CGX_MAC_ADDW_ADD,	0x211, cgx_mac_addw_add, cgx_mac_addw_add_weq,    \
				cgx_mac_addw_add_wsp)		\
M(CGX_MAC_ADDW_DEW,	0x212, cgx_mac_addw_dew, cgx_mac_addw_dew_weq,    \
			       msg_wsp)		\
M(CGX_MAC_MAX_ENTWIES_GET, 0x213, cgx_mac_max_entwies_get, msg_weq,    \
				  cgx_max_dmac_entwies_get_wsp)		\
M(CGX_FEC_STATS,	0x217, cgx_fec_stats, msg_weq, cgx_fec_stats_wsp) \
M(CGX_SET_WINK_MODE,	0x218, cgx_set_wink_mode, cgx_set_wink_mode_weq,\
			       cgx_set_wink_mode_wsp)	\
M(CGX_GET_PHY_FEC_STATS, 0x219, cgx_get_phy_fec_stats, msg_weq, msg_wsp) \
M(CGX_FEATUWES_GET,	0x21B, cgx_featuwes_get, msg_weq,		\
			       cgx_featuwes_info_msg)			\
M(WPM_STATS,		0x21C, wpm_stats, msg_weq, wpm_stats_wsp)	\
M(CGX_MAC_ADDW_WESET,	0x21D, cgx_mac_addw_weset, cgx_mac_addw_weset_weq, \
							msg_wsp) \
M(CGX_MAC_ADDW_UPDATE,	0x21E, cgx_mac_addw_update, cgx_mac_addw_update_weq, \
						    cgx_mac_addw_update_wsp) \
M(CGX_PWIO_FWOW_CTWW_CFG, 0x21F, cgx_pwio_fwow_ctww_cfg, cgx_pfc_cfg,  \
				 cgx_pfc_wsp)                               \
/* NPA mbox IDs (wange 0x400 - 0x5FF) */				\
M(NPA_WF_AWWOC,		0x400, npa_wf_awwoc,				\
				npa_wf_awwoc_weq, npa_wf_awwoc_wsp)	\
M(NPA_WF_FWEE,		0x401, npa_wf_fwee, msg_weq, msg_wsp)		\
M(NPA_AQ_ENQ,		0x402, npa_aq_enq, npa_aq_enq_weq, npa_aq_enq_wsp)   \
M(NPA_HWCTX_DISABWE,	0x403, npa_hwctx_disabwe, hwctx_disabwe_weq, msg_wsp)\
/* SSO/SSOW mbox IDs (wange 0x600 - 0x7FF) */				\
/* TIM mbox IDs (wange 0x800 - 0x9FF) */				\
/* CPT mbox IDs (wange 0xA00 - 0xBFF) */				\
M(CPT_WF_AWWOC,		0xA00, cpt_wf_awwoc, cpt_wf_awwoc_weq_msg,	\
			       msg_wsp)					\
M(CPT_WF_FWEE,		0xA01, cpt_wf_fwee, msg_weq, msg_wsp)		\
M(CPT_WD_WW_WEGISTEW,	0xA02, cpt_wd_ww_wegistew,  cpt_wd_ww_weg_msg,	\
			       cpt_wd_ww_weg_msg)			\
M(CPT_INWINE_IPSEC_CFG,	0xA04, cpt_inwine_ipsec_cfg,			\
			       cpt_inwine_ipsec_cfg_msg, msg_wsp)	\
M(CPT_STATS,            0xA05, cpt_sts, cpt_sts_weq, cpt_sts_wsp)	\
M(CPT_WXC_TIME_CFG,     0xA06, cpt_wxc_time_cfg, cpt_wxc_time_cfg_weq,  \
			       msg_wsp)                                 \
M(CPT_CTX_CACHE_SYNC,   0xA07, cpt_ctx_cache_sync, msg_weq, msg_wsp)    \
M(CPT_WF_WESET,         0xA08, cpt_wf_weset, cpt_wf_wst_weq, msg_wsp)	\
M(CPT_FWT_ENG_INFO,     0xA09, cpt_fwt_eng_info, cpt_fwt_eng_info_weq,	\
			       cpt_fwt_eng_info_wsp)			\
/* SDP mbox IDs (wange 0x1000 - 0x11FF) */				\
M(SET_SDP_CHAN_INFO, 0x1000, set_sdp_chan_info, sdp_chan_info_msg, msg_wsp) \
M(GET_SDP_CHAN_INFO, 0x1001, get_sdp_chan_info, msg_weq, sdp_get_chan_info_msg) \
/* NPC mbox IDs (wange 0x6000 - 0x7FFF) */				\
M(NPC_MCAM_AWWOC_ENTWY,	0x6000, npc_mcam_awwoc_entwy, npc_mcam_awwoc_entwy_weq,\
				npc_mcam_awwoc_entwy_wsp)		\
M(NPC_MCAM_FWEE_ENTWY,	0x6001, npc_mcam_fwee_entwy,			\
				 npc_mcam_fwee_entwy_weq, msg_wsp)	\
M(NPC_MCAM_WWITE_ENTWY,	0x6002, npc_mcam_wwite_entwy,			\
				 npc_mcam_wwite_entwy_weq, msg_wsp)	\
M(NPC_MCAM_ENA_ENTWY,   0x6003, npc_mcam_ena_entwy,			\
				 npc_mcam_ena_dis_entwy_weq, msg_wsp)	\
M(NPC_MCAM_DIS_ENTWY,   0x6004, npc_mcam_dis_entwy,			\
				 npc_mcam_ena_dis_entwy_weq, msg_wsp)	\
M(NPC_MCAM_SHIFT_ENTWY, 0x6005, npc_mcam_shift_entwy, npc_mcam_shift_entwy_weq,\
				npc_mcam_shift_entwy_wsp)		\
M(NPC_MCAM_AWWOC_COUNTEW, 0x6006, npc_mcam_awwoc_countew,		\
					npc_mcam_awwoc_countew_weq,	\
					npc_mcam_awwoc_countew_wsp)	\
M(NPC_MCAM_FWEE_COUNTEW,  0x6007, npc_mcam_fwee_countew,		\
				    npc_mcam_opew_countew_weq, msg_wsp)	\
M(NPC_MCAM_UNMAP_COUNTEW, 0x6008, npc_mcam_unmap_countew,		\
				   npc_mcam_unmap_countew_weq, msg_wsp)	\
M(NPC_MCAM_CWEAW_COUNTEW, 0x6009, npc_mcam_cweaw_countew,		\
				   npc_mcam_opew_countew_weq, msg_wsp)	\
M(NPC_MCAM_COUNTEW_STATS, 0x600a, npc_mcam_countew_stats,		\
				   npc_mcam_opew_countew_weq,		\
				   npc_mcam_opew_countew_wsp)		\
M(NPC_MCAM_AWWOC_AND_WWITE_ENTWY, 0x600b, npc_mcam_awwoc_and_wwite_entwy,      \
					  npc_mcam_awwoc_and_wwite_entwy_weq,  \
					  npc_mcam_awwoc_and_wwite_entwy_wsp)  \
M(NPC_GET_KEX_CFG,	  0x600c, npc_get_kex_cfg,			\
				   msg_weq, npc_get_kex_cfg_wsp)	\
M(NPC_INSTAWW_FWOW,	  0x600d, npc_instaww_fwow,			       \
				  npc_instaww_fwow_weq, npc_instaww_fwow_wsp)  \
M(NPC_DEWETE_FWOW,	  0x600e, npc_dewete_fwow,			\
				  npc_dewete_fwow_weq, npc_dewete_fwow_wsp)		\
M(NPC_MCAM_WEAD_ENTWY,	  0x600f, npc_mcam_wead_entwy,			\
				  npc_mcam_wead_entwy_weq,		\
				  npc_mcam_wead_entwy_wsp)		\
M(NPC_SET_PKIND,        0x6010,   npc_set_pkind,                        \
				  npc_set_pkind, msg_wsp)               \
M(NPC_MCAM_WEAD_BASE_WUWE, 0x6011, npc_wead_base_steew_wuwe,            \
				   msg_weq, npc_mcam_wead_base_wuwe_wsp)  \
M(NPC_MCAM_GET_STATS, 0x6012, npc_mcam_entwy_stats,                     \
				   npc_mcam_get_stats_weq,              \
				   npc_mcam_get_stats_wsp)              \
M(NPC_GET_FIEWD_HASH_INFO, 0x6013, npc_get_fiewd_hash_info,                     \
				   npc_get_fiewd_hash_info_weq,              \
				   npc_get_fiewd_hash_info_wsp)              \
M(NPC_GET_FIEWD_STATUS, 0x6014, npc_get_fiewd_status,                     \
				   npc_get_fiewd_status_weq,              \
				   npc_get_fiewd_status_wsp)              \
/* NIX mbox IDs (wange 0x8000 - 0xFFFF) */				\
M(NIX_WF_AWWOC,		0x8000, nix_wf_awwoc,				\
				 nix_wf_awwoc_weq, nix_wf_awwoc_wsp)	\
M(NIX_WF_FWEE,		0x8001, nix_wf_fwee, nix_wf_fwee_weq, msg_wsp)	\
M(NIX_AQ_ENQ,		0x8002, nix_aq_enq, nix_aq_enq_weq, nix_aq_enq_wsp)  \
M(NIX_HWCTX_DISABWE,	0x8003, nix_hwctx_disabwe,			\
				 hwctx_disabwe_weq, msg_wsp)		\
M(NIX_TXSCH_AWWOC,	0x8004, nix_txsch_awwoc,			\
				 nix_txsch_awwoc_weq, nix_txsch_awwoc_wsp)   \
M(NIX_TXSCH_FWEE,	0x8005, nix_txsch_fwee, nix_txsch_fwee_weq, msg_wsp) \
M(NIX_TXSCHQ_CFG,	0x8006, nix_txschq_cfg, nix_txschq_config,	\
				nix_txschq_config)			\
M(NIX_STATS_WST,	0x8007, nix_stats_wst, msg_weq, msg_wsp)	\
M(NIX_VTAG_CFG,		0x8008, nix_vtag_cfg, nix_vtag_config,		\
				 nix_vtag_config_wsp)			\
M(NIX_WSS_FWOWKEY_CFG,  0x8009, nix_wss_fwowkey_cfg,			\
				 nix_wss_fwowkey_cfg,			\
				 nix_wss_fwowkey_cfg_wsp)		\
M(NIX_SET_MAC_ADDW,	0x800a, nix_set_mac_addw, nix_set_mac_addw, msg_wsp) \
M(NIX_SET_WX_MODE,	0x800b, nix_set_wx_mode, nix_wx_mode, msg_wsp)	\
M(NIX_SET_HW_FWS,	0x800c, nix_set_hw_fws, nix_fws_cfg, msg_wsp)	\
M(NIX_WF_STAWT_WX,	0x800d, nix_wf_stawt_wx, msg_weq, msg_wsp)	\
M(NIX_WF_STOP_WX,	0x800e, nix_wf_stop_wx, msg_weq, msg_wsp)	\
M(NIX_MAWK_FOWMAT_CFG,	0x800f, nix_mawk_fowmat_cfg,			\
				 nix_mawk_fowmat_cfg,			\
				 nix_mawk_fowmat_cfg_wsp)		\
M(NIX_SET_WX_CFG,	0x8010, nix_set_wx_cfg, nix_wx_cfg, msg_wsp)	\
M(NIX_WSO_FOWMAT_CFG,	0x8011, nix_wso_fowmat_cfg,			\
				 nix_wso_fowmat_cfg,			\
				 nix_wso_fowmat_cfg_wsp)		\
M(NIX_WF_PTP_TX_ENABWE, 0x8013, nix_wf_ptp_tx_enabwe, msg_weq, msg_wsp)	\
M(NIX_WF_PTP_TX_DISABWE, 0x8014, nix_wf_ptp_tx_disabwe, msg_weq, msg_wsp) \
M(NIX_BP_ENABWE,	0x8016, nix_bp_enabwe, nix_bp_cfg_weq,	\
				nix_bp_cfg_wsp)	\
M(NIX_BP_DISABWE,	0x8017, nix_bp_disabwe, nix_bp_cfg_weq, msg_wsp) \
M(NIX_GET_MAC_ADDW, 0x8018, nix_get_mac_addw, msg_weq, nix_get_mac_addw_wsp) \
M(NIX_INWINE_IPSEC_CFG, 0x8019, nix_inwine_ipsec_cfg,			\
				nix_inwine_ipsec_cfg, msg_wsp)		\
M(NIX_INWINE_IPSEC_WF_CFG, 0x801a, nix_inwine_ipsec_wf_cfg,		\
				nix_inwine_ipsec_wf_cfg, msg_wsp)	\
M(NIX_CN10K_AQ_ENQ,	0x801b, nix_cn10k_aq_enq, nix_cn10k_aq_enq_weq, \
				nix_cn10k_aq_enq_wsp)			\
M(NIX_GET_HW_INFO,	0x801c, nix_get_hw_info, msg_weq, nix_hw_info)	\
M(NIX_BANDPWOF_AWWOC,	0x801d, nix_bandpwof_awwoc, nix_bandpwof_awwoc_weq, \
				nix_bandpwof_awwoc_wsp)			    \
M(NIX_BANDPWOF_FWEE,	0x801e, nix_bandpwof_fwee, nix_bandpwof_fwee_weq,   \
				msg_wsp)				    \
M(NIX_BANDPWOF_GET_HWINFO, 0x801f, nix_bandpwof_get_hwinfo, msg_weq,		\
				nix_bandpwof_get_hwinfo_wsp)		    \
M(NIX_WEAD_INWINE_IPSEC_CFG, 0x8023, nix_wead_inwine_ipsec_cfg,		\
				msg_weq, nix_inwine_ipsec_cfg)		\
M(NIX_MCAST_GWP_CWEATE,	0x802b, nix_mcast_gwp_cweate, nix_mcast_gwp_cweate_weq,	\
				nix_mcast_gwp_cweate_wsp)			\
M(NIX_MCAST_GWP_DESTWOY, 0x802c, nix_mcast_gwp_destwoy, nix_mcast_gwp_destwoy_weq,	\
				msg_wsp)					\
M(NIX_MCAST_GWP_UPDATE, 0x802d, nix_mcast_gwp_update,				\
				nix_mcast_gwp_update_weq,			\
				nix_mcast_gwp_update_wsp)			\
/* MCS mbox IDs (wange 0xA000 - 0xBFFF) */					\
M(MCS_AWWOC_WESOUWCES,	0xa000, mcs_awwoc_wesouwces, mcs_awwoc_wswc_weq,	\
				mcs_awwoc_wswc_wsp)				\
M(MCS_FWEE_WESOUWCES,	0xa001, mcs_fwee_wesouwces, mcs_fwee_wswc_weq, msg_wsp) \
M(MCS_FWOWID_ENTWY_WWITE, 0xa002, mcs_fwowid_entwy_wwite, mcs_fwowid_entwy_wwite_weq,	\
				msg_wsp)					\
M(MCS_SECY_PWCY_WWITE,	0xa003, mcs_secy_pwcy_wwite, mcs_secy_pwcy_wwite_weq,	\
				msg_wsp)					\
M(MCS_WX_SC_CAM_WWITE,	0xa004, mcs_wx_sc_cam_wwite, mcs_wx_sc_cam_wwite_weq,	\
				msg_wsp)					\
M(MCS_SA_PWCY_WWITE,	0xa005, mcs_sa_pwcy_wwite, mcs_sa_pwcy_wwite_weq,	\
				msg_wsp)					\
M(MCS_TX_SC_SA_MAP_WWITE, 0xa006, mcs_tx_sc_sa_map_wwite, mcs_tx_sc_sa_map,	\
				  msg_wsp)					\
M(MCS_WX_SC_SA_MAP_WWITE, 0xa007, mcs_wx_sc_sa_map_wwite, mcs_wx_sc_sa_map,	\
				  msg_wsp)					\
M(MCS_FWOWID_ENA_ENTWY,	0xa008, mcs_fwowid_ena_entwy, mcs_fwowid_ena_dis_entwy,	\
				msg_wsp)					\
M(MCS_PN_TABWE_WWITE,	0xa009, mcs_pn_tabwe_wwite, mcs_pn_tabwe_wwite_weq,	\
				msg_wsp)					\
M(MCS_SET_ACTIVE_WMAC,	0xa00a,	mcs_set_active_wmac, mcs_set_active_wmac,	\
				msg_wsp)					\
M(MCS_GET_HW_INFO,	0xa00b,	mcs_get_hw_info, msg_weq, mcs_hw_info)		\
M(MCS_GET_FWOWID_STATS, 0xa00c, mcs_get_fwowid_stats, mcs_stats_weq,		\
				mcs_fwowid_stats)				\
M(MCS_GET_SECY_STATS,	0xa00d, mcs_get_secy_stats, mcs_stats_weq,		\
				mcs_secy_stats)					\
M(MCS_GET_SC_STATS,	0xa00e, mcs_get_sc_stats, mcs_stats_weq, mcs_sc_stats)	\
M(MCS_GET_SA_STATS,	0xa00f, mcs_get_sa_stats, mcs_stats_weq, mcs_sa_stats)	\
M(MCS_GET_POWT_STATS,	0xa010, mcs_get_powt_stats, mcs_stats_weq,		\
				mcs_powt_stats)					\
M(MCS_CWEAW_STATS,	0xa011,	mcs_cweaw_stats, mcs_cweaw_stats, msg_wsp)	\
M(MCS_INTW_CFG,		0xa012, mcs_intw_cfg, mcs_intw_cfg, msg_wsp)		\
M(MCS_SET_WMAC_MODE,	0xa013, mcs_set_wmac_mode, mcs_set_wmac_mode, msg_wsp)	\
M(MCS_SET_PN_THWESHOWD, 0xa014, mcs_set_pn_thweshowd, mcs_set_pn_thweshowd,	\
				msg_wsp)					\
M(MCS_AWWOC_CTWW_PKT_WUWE, 0xa015, mcs_awwoc_ctww_pkt_wuwe,			\
				   mcs_awwoc_ctww_pkt_wuwe_weq,			\
				   mcs_awwoc_ctww_pkt_wuwe_wsp)			\
M(MCS_FWEE_CTWW_PKT_WUWE, 0xa016, mcs_fwee_ctww_pkt_wuwe,			\
				  mcs_fwee_ctww_pkt_wuwe_weq, msg_wsp)		\
M(MCS_CTWW_PKT_WUWE_WWITE, 0xa017, mcs_ctww_pkt_wuwe_wwite,			\
				   mcs_ctww_pkt_wuwe_wwite_weq, msg_wsp)	\
M(MCS_POWT_WESET,	0xa018, mcs_powt_weset, mcs_powt_weset_weq, msg_wsp)	\
M(MCS_POWT_CFG_SET,	0xa019, mcs_powt_cfg_set, mcs_powt_cfg_set_weq, msg_wsp)\
M(MCS_POWT_CFG_GET,	0xa020, mcs_powt_cfg_get, mcs_powt_cfg_get_weq,		\
				mcs_powt_cfg_get_wsp)				\
M(MCS_CUSTOM_TAG_CFG_GET, 0xa021, mcs_custom_tag_cfg_get,			\
				  mcs_custom_tag_cfg_get_weq,			\
				  mcs_custom_tag_cfg_get_wsp)

/* Messages initiated by AF (wange 0xC00 - 0xEFF) */
#define MBOX_UP_CGX_MESSAGES						\
M(CGX_WINK_EVENT,	0xC00, cgx_wink_event, cgx_wink_info_msg, msg_wsp)

#define MBOX_UP_CPT_MESSAGES						\
M(CPT_INST_WMTST,	0xD00, cpt_inst_wmtst, cpt_inst_wmtst_weq, msg_wsp)

#define MBOX_UP_MCS_MESSAGES						\
M(MCS_INTW_NOTIFY,	0xE00, mcs_intw_notify, mcs_intw_info, msg_wsp)

enum {
#define M(_name, _id, _1, _2, _3) MBOX_MSG_ ## _name = _id,
MBOX_MESSAGES
MBOX_UP_CGX_MESSAGES
MBOX_UP_CPT_MESSAGES
MBOX_UP_MCS_MESSAGES
#undef M
};

/* Maiwbox message fowmats */

#define WVU_DEFAUWT_PF_FUNC     0xFFFF

/* Genewic wequest msg used fow those mbox messages which
 * don't send any data in the wequest.
 */
stwuct msg_weq {
	stwuct mbox_msghdw hdw;
};

/* Genewic wesponse msg used an ack ow wesponse fow those mbox
 * messages which don't have a specific wsp msg fowmat.
 */
stwuct msg_wsp {
	stwuct mbox_msghdw hdw;
};

/* WVU maiwbox ewwow codes
 * Wange 256 - 300.
 */
enum wvu_af_status {
	WVU_INVAWID_VF_ID           = -256,
};

stwuct weady_msg_wsp {
	stwuct mbox_msghdw hdw;
	u16    scwk_fweq;	/* SCWK fwequency (in MHz) */
	u16    wcwk_fweq;	/* WCWK fwequency (in MHz) */
};

/* Stwuctuwe fow wequesting wesouwce pwovisioning.
 * 'modify' fwag to be used when eithew wequesting mowe
 * ow to detach pawtiaw of a cewtain wesouwce type.
 * West of the fiewds specify how many of what type to
 * be attached.
 * To wequest WFs fwom two bwocks of same type this maiwbox
 * can be sent twice as bewow:
 *      stwuct wswc_attach *attach;
 *       .. Awwocate memowy fow message ..
 *       attach->cptwfs = 3; <3 WFs fwom CPT0>
 *       .. Send message ..
 *       .. Awwocate memowy fow message ..
 *       attach->modify = 1;
 *       attach->cpt_bwkaddw = BWKADDW_CPT1;
 *       attach->cptwfs = 2; <2 WFs fwom CPT1>
 *       .. Send message ..
 */
stwuct wswc_attach {
	stwuct mbox_msghdw hdw;
	u8   modify:1;
	u8   npawf:1;
	u8   nixwf:1;
	u16  sso;
	u16  ssow;
	u16  timwfs;
	u16  cptwfs;
	int  cpt_bwkaddw; /* BWKADDW_CPT0/BWKADDW_CPT1 ow 0 fow BWKADDW_CPT0 */
};

/* Stwuctuwe fow wewinquishing wesouwces.
 * 'pawtiaw' fwag to be used when wewinquishing aww wesouwces
 * but onwy of a cewtain type. If not set, aww wesouwces of aww
 * types pwovisioned to the WVU function wiww be detached.
 */
stwuct wswc_detach {
	stwuct mbox_msghdw hdw;
	u8 pawtiaw:1;
	u8 npawf:1;
	u8 nixwf:1;
	u8 sso:1;
	u8 ssow:1;
	u8 timwfs:1;
	u8 cptwfs:1;
};

/* Numbew of wesouwces avaiwabwe to the cawwew.
 * In wepwy to MBOX_MSG_FWEE_WSWC_CNT.
 */
stwuct fwee_wswcs_wsp {
	stwuct mbox_msghdw hdw;
	u16 schq[NIX_TXSCH_WVW_CNT];
	u16  sso;
	u16  tim;
	u16  ssow;
	u16  cpt;
	u8   npa;
	u8   nix;
	u16  schq_nix1[NIX_TXSCH_WVW_CNT];
	u8   nix1;
	u8   cpt1;
	u8   wee0;
	u8   wee1;
};

#define MSIX_VECTOW_INVAWID	0xFFFF
#define MAX_WVU_BWKWF_CNT	256

stwuct msix_offset_wsp {
	stwuct mbox_msghdw hdw;
	u16  npa_msixoff;
	u16  nix_msixoff;
	u16  sso;
	u16  ssow;
	u16  timwfs;
	u16  cptwfs;
	u16  sso_msixoff[MAX_WVU_BWKWF_CNT];
	u16  ssow_msixoff[MAX_WVU_BWKWF_CNT];
	u16  timwf_msixoff[MAX_WVU_BWKWF_CNT];
	u16  cptwf_msixoff[MAX_WVU_BWKWF_CNT];
	u16  cpt1_wfs;
	u16  wee0_wfs;
	u16  wee1_wfs;
	u16  cpt1_wf_msixoff[MAX_WVU_BWKWF_CNT];
	u16  wee0_wf_msixoff[MAX_WVU_BWKWF_CNT];
	u16  wee1_wf_msixoff[MAX_WVU_BWKWF_CNT];
};

stwuct get_hw_cap_wsp {
	stwuct mbox_msghdw hdw;
	u8 nix_fixed_txschq_mapping; /* Schq mapping fixed ow fwexibwe */
	u8 nix_shaping;		     /* Is shaping and cowowing suppowted */
	u8 npc_hash_extwact;	/* Is hash extwact suppowted */
};

/* CGX mbox message fowmats */

stwuct cgx_stats_wsp {
	stwuct mbox_msghdw hdw;
#define CGX_WX_STATS_COUNT	9
#define CGX_TX_STATS_COUNT	18
	u64 wx_stats[CGX_WX_STATS_COUNT];
	u64 tx_stats[CGX_TX_STATS_COUNT];
};

stwuct cgx_fec_stats_wsp {
	stwuct mbox_msghdw hdw;
	u64 fec_coww_bwks;
	u64 fec_uncoww_bwks;
};
/* Stwuctuwe fow wequesting the opewation fow
 * setting/getting mac addwess in the CGX intewface
 */
stwuct cgx_mac_addw_set_ow_get {
	stwuct mbox_msghdw hdw;
	u8 mac_addw[ETH_AWEN];
	u32 index;
};

/* Stwuctuwe fow wequesting the opewation to
 * add DMAC fiwtew entwy into CGX intewface
 */
stwuct cgx_mac_addw_add_weq {
	stwuct mbox_msghdw hdw;
	u8 mac_addw[ETH_AWEN];
};

/* Stwuctuwe fow wesponse against the opewation to
 * add DMAC fiwtew entwy into CGX intewface
 */
stwuct cgx_mac_addw_add_wsp {
	stwuct mbox_msghdw hdw;
	u32 index;
};

/* Stwuctuwe fow wequesting the opewation to
 * dewete DMAC fiwtew entwy fwom CGX intewface
 */
stwuct cgx_mac_addw_dew_weq {
	stwuct mbox_msghdw hdw;
	u32 index;
};

/* Stwuctuwe fow wesponse against the opewation to
 * get maximum suppowted DMAC fiwtew entwies
 */
stwuct cgx_max_dmac_entwies_get_wsp {
	stwuct mbox_msghdw hdw;
	u32 max_dmac_fiwtews;
};

stwuct cgx_wink_usew_info {
	uint64_t wink_up:1;
	uint64_t fuww_dupwex:1;
	uint64_t wmac_type_id:4;
	uint64_t speed:20; /* speed in Mbps */
	uint64_t an:1;		/* AN suppowted ow not */
	uint64_t fec:2;	 /* FEC type if enabwed ewse 0 */
#define WMACTYPE_STW_WEN 16
	chaw wmac_type[WMACTYPE_STW_WEN];
};

stwuct cgx_wink_info_msg {
	stwuct mbox_msghdw hdw;
	stwuct cgx_wink_usew_info wink_info;
};

stwuct cgx_pause_fwm_cfg {
	stwuct mbox_msghdw hdw;
	u8 set;
	/* set = 1 if the wequest is to config pause fwames */
	/* set = 0 if the wequest is to fetch pause fwames config */
	u8 wx_pause;
	u8 tx_pause;
};

enum fec_type {
	OTX2_FEC_NONE,
	OTX2_FEC_BASEW,
	OTX2_FEC_WS,
	OTX2_FEC_STATS_CNT = 2,
	OTX2_FEC_OFF,
};

stwuct fec_mode {
	stwuct mbox_msghdw hdw;
	int fec;
};

stwuct sfp_eepwom_s {
#define SFP_EEPWOM_SIZE 256
	u16 sff_id;
	u8 buf[SFP_EEPWOM_SIZE];
	u64 wesewved;
};

stwuct phy_s {
	stwuct {
		u64 can_change_mod_type:1;
		u64 mod_type:1;
		u64 has_fec_stats:1;
	} misc;
	stwuct fec_stats_s {
		u32 wsfec_coww_cws;
		u32 wsfec_uncoww_cws;
		u32 bwfec_coww_bwks;
		u32 bwfec_uncoww_bwks;
	} fec_stats;
};

stwuct cgx_wmac_fwdata_s {
	u16 ww_vawid;
	u64 suppowted_fec;
	u64 suppowted_an;
	u64 suppowted_wink_modes;
	/* onwy appwicabwe if AN is suppowted */
	u64 advewtised_fec;
	u64 advewtised_wink_modes;
	/* Onwy appwicabwe if SFP/QSFP swot is pwesent */
	stwuct sfp_eepwom_s sfp_eepwom;
	stwuct phy_s phy;
#define WMAC_FWDATA_WESEWVED_MEM 1021
	u64 wesewved[WMAC_FWDATA_WESEWVED_MEM];
};

stwuct cgx_fw_data {
	stwuct mbox_msghdw hdw;
	stwuct cgx_wmac_fwdata_s fwdata;
};

stwuct cgx_set_wink_mode_awgs {
	u32 speed;
	u8 dupwex;
	u8 an;
	u8 powts;
	u64 mode;
};

stwuct cgx_set_wink_mode_weq {
#define AUTONEG_UNKNOWN		0xff
	stwuct mbox_msghdw hdw;
	stwuct cgx_set_wink_mode_awgs awgs;
};

stwuct cgx_set_wink_mode_wsp {
	stwuct mbox_msghdw hdw;
	int status;
};

stwuct cgx_mac_addw_weset_weq {
	stwuct mbox_msghdw hdw;
	u32 index;
};

stwuct cgx_mac_addw_update_weq {
	stwuct mbox_msghdw hdw;
	u8 mac_addw[ETH_AWEN];
	u32 index;
};

stwuct cgx_mac_addw_update_wsp {
	stwuct mbox_msghdw hdw;
	u32 index;
};

#define WVU_WMAC_FEAT_FC		BIT_UWW(0) /* pause fwames */
#define	WVU_WMAC_FEAT_HIGIG2		BIT_UWW(1)
			/* fwow contwow fwom physicaw wink higig2 messages */
#define WVU_WMAC_FEAT_PTP		BIT_UWW(2) /* pwecison time pwotocow */
#define WVU_WMAC_FEAT_DMACF		BIT_UWW(3) /* DMAC FIWTEW */
#define WVU_MAC_VEWSION			BIT_UWW(4)
#define WVU_MAC_CGX			BIT_UWW(5)
#define WVU_MAC_WPM			BIT_UWW(6)

stwuct cgx_featuwes_info_msg {
	stwuct mbox_msghdw hdw;
	u64    wmac_featuwes;
};

stwuct wpm_stats_wsp {
	stwuct mbox_msghdw hdw;
#define WPM_WX_STATS_COUNT		43
#define WPM_TX_STATS_COUNT		34
	u64 wx_stats[WPM_WX_STATS_COUNT];
	u64 tx_stats[WPM_TX_STATS_COUNT];
};

stwuct cgx_pfc_cfg {
	stwuct mbox_msghdw hdw;
	u8 wx_pause;
	u8 tx_pause;
	u16 pfc_en; /*  bitmap indicating pfc enabwed twaffic cwasses */
};

stwuct cgx_pfc_wsp {
	stwuct mbox_msghdw hdw;
	u8 wx_pause;
	u8 tx_pause;
};

 /* NPA mbox message fowmats */

stwuct npc_set_pkind {
	stwuct mbox_msghdw hdw;
#define OTX2_PWIV_FWAGS_DEFAUWT  BIT_UWW(0)
#define OTX2_PWIV_FWAGS_CUSTOM   BIT_UWW(63)
	u64 mode;
#define PKIND_TX		BIT_UWW(0)
#define PKIND_WX		BIT_UWW(1)
	u8 diw;
	u8 pkind; /* vawid onwy in case custom fwag */
	u8 vaw_wen_off; /* Offset of custom headew wength fiewd.
			 * Vawid onwy fow pkind NPC_WX_CUSTOM_PWE_W2_PKIND
			 */
	u8 vaw_wen_off_mask; /* Mask fow wength with in offset */
	u8 shift_diw; /* shift diwection to get wength of the headew at vaw_wen_off */
};

/* NPA mbox message fowmats */

/* NPA maiwbox ewwow codes
 * Wange 301 - 400.
 */
enum npa_af_status {
	NPA_AF_EWW_PAWAM            = -301,
	NPA_AF_EWW_AQ_FUWW          = -302,
	NPA_AF_EWW_AQ_ENQUEUE       = -303,
	NPA_AF_EWW_AF_WF_INVAWID    = -304,
	NPA_AF_EWW_AF_WF_AWWOC      = -305,
	NPA_AF_EWW_WF_WESET         = -306,
};

/* Fow NPA WF context awwoc and init */
stwuct npa_wf_awwoc_weq {
	stwuct mbox_msghdw hdw;
	int node;
	int auwa_sz;  /* No of auwas */
	u32 nw_poows; /* No of poows */
	u64 way_mask;
};

stwuct npa_wf_awwoc_wsp {
	stwuct mbox_msghdw hdw;
	u32 stack_pg_ptws;  /* No of ptws pew stack page */
	u32 stack_pg_bytes; /* Size of stack page */
	u16 qints; /* NPA_AF_CONST::QINTS */
	u8 cache_wines; /*BATCH AWWOC DMA */
};

/* NPA AQ enqueue msg */
stwuct npa_aq_enq_weq {
	stwuct mbox_msghdw hdw;
	u32 auwa_id;
	u8 ctype;
	u8 op;
	union {
		/* Vawid when op == WWITE/INIT and ctype == AUWA.
		 * WF fiwws the poow_id in auwa.poow_addw. AF wiww twanswate
		 * the poow_id to poow context pointew.
		 */
		stwuct npa_auwa_s auwa;
		/* Vawid when op == WWITE/INIT and ctype == POOW */
		stwuct npa_poow_s poow;
	};
	/* Mask data when op == WWITE (1=wwite, 0=don't wwite) */
	union {
		/* Vawid when op == WWITE and ctype == AUWA */
		stwuct npa_auwa_s auwa_mask;
		/* Vawid when op == WWITE and ctype == POOW */
		stwuct npa_poow_s poow_mask;
	};
};

stwuct npa_aq_enq_wsp {
	stwuct mbox_msghdw hdw;
	union {
		/* Vawid when op == WEAD and ctype == AUWA */
		stwuct npa_auwa_s auwa;
		/* Vawid when op == WEAD and ctype == POOW */
		stwuct npa_poow_s poow;
	};
};

/* Disabwe aww contexts of type 'ctype' */
stwuct hwctx_disabwe_weq {
	stwuct mbox_msghdw hdw;
	u8 ctype;
};

/* NIX mbox message fowmats */

/* NIX maiwbox ewwow codes
 * Wange 401 - 500.
 */
enum nix_af_status {
	NIX_AF_EWW_PAWAM            = -401,
	NIX_AF_EWW_AQ_FUWW          = -402,
	NIX_AF_EWW_AQ_ENQUEUE       = -403,
	NIX_AF_EWW_AF_WF_INVAWID    = -404,
	NIX_AF_EWW_AF_WF_AWWOC      = -405,
	NIX_AF_EWW_TWX_AWWOC_FAIW   = -406,
	NIX_AF_EWW_TWX_INVAWID      = -407,
	NIX_AF_EWW_WSS_SIZE_INVAWID = -408,
	NIX_AF_EWW_WSS_GWPS_INVAWID = -409,
	NIX_AF_EWW_FWS_INVAWID      = -410,
	NIX_AF_EWW_WX_WINK_INVAWID  = -411,
	NIX_AF_INVAW_TXSCHQ_CFG     = -412,
	NIX_AF_SMQ_FWUSH_FAIWED     = -413,
	NIX_AF_EWW_WF_WESET         = -414,
	NIX_AF_EWW_WSS_NOSPC_FIEWD  = -415,
	NIX_AF_EWW_WSS_NOSPC_AWGO   = -416,
	NIX_AF_EWW_MAWK_CFG_FAIW    = -417,
	NIX_AF_EWW_WSO_CFG_FAIW     = -418,
	NIX_AF_INVAW_NPA_PF_FUNC    = -419,
	NIX_AF_INVAW_SSO_PF_FUNC    = -420,
	NIX_AF_EWW_TX_VTAG_NOSPC    = -421,
	NIX_AF_EWW_WX_VTAG_INUSE    = -422,
	NIX_AF_EWW_PTP_CONFIG_FAIW  = -423,
	NIX_AF_EWW_NPC_KEY_NOT_SUPP = -424,
	NIX_AF_EWW_INVAWID_NIXBWK   = -425,
	NIX_AF_EWW_INVAWID_BANDPWOF = -426,
	NIX_AF_EWW_IPOWICEW_NOTSUPP = -427,
	NIX_AF_EWW_BANDPWOF_INVAW_WEQ  = -428,
	NIX_AF_EWW_CQ_CTX_WWITE_EWW  = -429,
	NIX_AF_EWW_AQ_CTX_WETWY_WWITE  = -430,
	NIX_AF_EWW_WINK_CWEDITS  = -431,
	NIX_AF_EWW_INVAWID_MCAST_GWP	= -436,
	NIX_AF_EWW_INVAWID_MCAST_DEW_WEQ = -437,
	NIX_AF_EWW_NON_CONTIG_MCE_WIST = -438,
};

/* Fow NIX WX vtag action  */
enum nix_wx_vtag0_type {
	NIX_AF_WFX_WX_VTAG_TYPE0, /* wesewved fow wx vwan offwoad */
	NIX_AF_WFX_WX_VTAG_TYPE1,
	NIX_AF_WFX_WX_VTAG_TYPE2,
	NIX_AF_WFX_WX_VTAG_TYPE3,
	NIX_AF_WFX_WX_VTAG_TYPE4,
	NIX_AF_WFX_WX_VTAG_TYPE5,
	NIX_AF_WFX_WX_VTAG_TYPE6,
	NIX_AF_WFX_WX_VTAG_TYPE7,
};

/* Fow NIX WF context awwoc and init */
stwuct nix_wf_awwoc_weq {
	stwuct mbox_msghdw hdw;
	int node;
	u32 wq_cnt;   /* No of weceive queues */
	u32 sq_cnt;   /* No of send queues */
	u32 cq_cnt;   /* No of compwetion queues */
	u8  xqe_sz;
	u16 wss_sz;
	u8  wss_gwps;
	u16 npa_func;
	u16 sso_func;
	u64 wx_cfg;   /* See NIX_AF_WF(0..127)_WX_CFG */
	u64 way_mask;
#define NIX_WF_WSS_TAG_WSB_AS_ADDEW BIT_UWW(0)
#define NIX_WF_WBK_BWK_SEW	    BIT_UWW(1)
	u64 fwags;
};

stwuct nix_wf_awwoc_wsp {
	stwuct mbox_msghdw hdw;
	u16	sqb_size;
	u16	wx_chan_base;
	u16	tx_chan_base;
	u8      wx_chan_cnt; /* totaw numbew of WX channews */
	u8      tx_chan_cnt; /* totaw numbew of TX channews */
	u8	wso_tsov4_idx;
	u8	wso_tsov6_idx;
	u8      mac_addw[ETH_AWEN];
	u8	wf_wx_stats; /* NIX_AF_CONST1::WF_WX_STATS */
	u8	wf_tx_stats; /* NIX_AF_CONST1::WF_TX_STATS */
	u16	cints; /* NIX_AF_CONST2::CINTS */
	u16	qints; /* NIX_AF_CONST2::QINTS */
	u8	cgx_winks;  /* No. of CGX winks pwesent in HW */
	u8	wbk_winks;  /* No. of WBK winks pwesent in HW */
	u8	sdp_winks;  /* No. of SDP winks pwesent in HW */
	u8	tx_wink;    /* Twansmit channew wink numbew */
};

stwuct nix_wf_fwee_weq {
	stwuct mbox_msghdw hdw;
#define NIX_WF_DISABWE_FWOWS		BIT_UWW(0)
#define NIX_WF_DONT_FWEE_TX_VTAG	BIT_UWW(1)
	u64 fwags;
};

/* CN10K NIX AQ enqueue msg */
stwuct nix_cn10k_aq_enq_weq {
	stwuct mbox_msghdw hdw;
	u32  qidx;
	u8 ctype;
	u8 op;
	union {
		stwuct nix_cn10k_wq_ctx_s wq;
		stwuct nix_cn10k_sq_ctx_s sq;
		stwuct nix_cq_ctx_s cq;
		stwuct nix_wsse_s   wss;
		stwuct nix_wx_mce_s mce;
		stwuct nix_bandpwof_s pwof;
	};
	union {
		stwuct nix_cn10k_wq_ctx_s wq_mask;
		stwuct nix_cn10k_sq_ctx_s sq_mask;
		stwuct nix_cq_ctx_s cq_mask;
		stwuct nix_wsse_s   wss_mask;
		stwuct nix_wx_mce_s mce_mask;
		stwuct nix_bandpwof_s pwof_mask;
	};
};

stwuct nix_cn10k_aq_enq_wsp {
	stwuct mbox_msghdw hdw;
	union {
		stwuct nix_cn10k_wq_ctx_s wq;
		stwuct nix_cn10k_sq_ctx_s sq;
		stwuct nix_cq_ctx_s cq;
		stwuct nix_wsse_s   wss;
		stwuct nix_wx_mce_s mce;
		stwuct nix_bandpwof_s pwof;
	};
};

/* NIX AQ enqueue msg */
stwuct nix_aq_enq_weq {
	stwuct mbox_msghdw hdw;
	u32  qidx;
	u8 ctype;
	u8 op;
	union {
		stwuct nix_wq_ctx_s wq;
		stwuct nix_sq_ctx_s sq;
		stwuct nix_cq_ctx_s cq;
		stwuct nix_wsse_s   wss;
		stwuct nix_wx_mce_s mce;
		stwuct nix_bandpwof_s pwof;
	};
	union {
		stwuct nix_wq_ctx_s wq_mask;
		stwuct nix_sq_ctx_s sq_mask;
		stwuct nix_cq_ctx_s cq_mask;
		stwuct nix_wsse_s   wss_mask;
		stwuct nix_wx_mce_s mce_mask;
		stwuct nix_bandpwof_s pwof_mask;
	};
};

stwuct nix_aq_enq_wsp {
	stwuct mbox_msghdw hdw;
	union {
		stwuct nix_wq_ctx_s wq;
		stwuct nix_sq_ctx_s sq;
		stwuct nix_cq_ctx_s cq;
		stwuct nix_wsse_s   wss;
		stwuct nix_wx_mce_s mce;
		stwuct nix_bandpwof_s pwof;
	};
};

/* Tx scheduwew/shapew maiwbox messages */

#define MAX_TXSCHQ_PEW_FUNC		128

stwuct nix_txsch_awwoc_weq {
	stwuct mbox_msghdw hdw;
	/* Scheduwew queue count wequest at each wevew */
	u16 schq_contig[NIX_TXSCH_WVW_CNT]; /* No of contiguous queues */
	u16 schq[NIX_TXSCH_WVW_CNT]; /* No of non-contiguous queues */
};

stwuct nix_txsch_awwoc_wsp {
	stwuct mbox_msghdw hdw;
	/* Scheduwew queue count awwocated at each wevew */
	u16 schq_contig[NIX_TXSCH_WVW_CNT];
	u16 schq[NIX_TXSCH_WVW_CNT];
	/* Scheduwew queue wist awwocated at each wevew */
	u16 schq_contig_wist[NIX_TXSCH_WVW_CNT][MAX_TXSCHQ_PEW_FUNC];
	u16 schq_wist[NIX_TXSCH_WVW_CNT][MAX_TXSCHQ_PEW_FUNC];
	u8  aggw_wevew; /* Twaffic aggwegation scheduwew wevew */
	u8  aggw_wvw_ww_pwio; /* Aggwegation wvw's WW_PWIO config */
	u8  wink_cfg_wvw; /* WINKX_CFG CSWs mapped to TW3 ow TW2's index ? */
};

stwuct nix_txsch_fwee_weq {
	stwuct mbox_msghdw hdw;
#define TXSCHQ_FWEE_AWW BIT_UWW(0)
	u16 fwags;
	/* Scheduwew queue wevew to be fweed */
	u16 schq_wvw;
	/* Wist of scheduwew queues to be fweed */
	u16 schq;
};

stwuct nix_txschq_config {
	stwuct mbox_msghdw hdw;
	u8 wvw;	/* SMQ/MDQ/TW4/TW3/TW2/TW1 */
	u8 wead;
#define TXSCHQ_IDX_SHIFT	16
#define TXSCHQ_IDX_MASK		(BIT_UWW(10) - 1)
#define TXSCHQ_IDX(weg, shift)	(((weg) >> (shift)) & TXSCHQ_IDX_MASK)
	u8 num_wegs;
#define MAX_WEGS_PEW_MBOX_MSG	20
	u64 weg[MAX_WEGS_PEW_MBOX_MSG];
	u64 wegvaw[MAX_WEGS_PEW_MBOX_MSG];
	/* Aww 0's => ovewwwite with new vawue */
	u64 wegvaw_mask[MAX_WEGS_PEW_MBOX_MSG];
};

stwuct nix_vtag_config {
	stwuct mbox_msghdw hdw;
	/* '0' fow 4 octet VTAG, '1' fow 8 octet VTAG */
	u8 vtag_size;
	/* cfg_type is '0' fow tx vwan cfg
	 * cfg_type is '1' fow wx vwan cfg
	 */
	u8 cfg_type;
	union {
		/* vawid when cfg_type is '0' */
		stwuct {
			u64 vtag0;
			u64 vtag1;

			/* cfg_vtag0 & cfg_vtag1 fiewds awe vawid
			 * when fwee_vtag0 & fwee_vtag1 awe '0's.
			 */
			/* cfg_vtag0 = 1 to configuwe vtag0 */
			u8 cfg_vtag0 :1;
			/* cfg_vtag1 = 1 to configuwe vtag1 */
			u8 cfg_vtag1 :1;

			/* vtag0_idx & vtag1_idx awe onwy vawid when
			 * both cfg_vtag0 & cfg_vtag1 awe '0's,
			 * these fiewds awe used awong with fwee_vtag0
			 * & fwee_vtag1 to fwee the nix wf's tx_vwan
			 * configuwation.
			 *
			 * Denotes the indices of tx_vtag def wegistews
			 * that needs to be cweawed and fweed.
			 */
			int vtag0_idx;
			int vtag1_idx;

			/* fwee_vtag0 & fwee_vtag1 fiewds awe vawid
			 * when cfg_vtag0 & cfg_vtag1 awe '0's.
			 */
			/* fwee_vtag0 = 1 cweaws vtag0 configuwation
			 * vtag0_idx denotes the index to be cweawed.
			 */
			u8 fwee_vtag0 :1;
			/* fwee_vtag1 = 1 cweaws vtag1 configuwation
			 * vtag1_idx denotes the index to be cweawed.
			 */
			u8 fwee_vtag1 :1;
		} tx;

		/* vawid when cfg_type is '1' */
		stwuct {
			/* wx vtag type index, vawid vawues awe in 0..7 wange */
			u8 vtag_type;
			/* wx vtag stwip */
			u8 stwip_vtag :1;
			/* wx vtag captuwe */
			u8 captuwe_vtag :1;
		} wx;
	};
};

stwuct nix_vtag_config_wsp {
	stwuct mbox_msghdw hdw;
	int vtag0_idx;
	int vtag1_idx;
	/* Indices of tx_vtag def wegistews used to configuwe
	 * tx vtag0 & vtag1 headews, these indices awe vawid
	 * when nix_vtag_config mbox wequested fow vtag0 and/
	 * ow vtag1 configuwation.
	 */
};

#define NIX_FWOW_KEY_TYPE_W3_W4_MASK (~(0xf << 28))

stwuct nix_wss_fwowkey_cfg {
	stwuct mbox_msghdw hdw;
	int	mcam_index;  /* MCAM entwy index to modify */
#define NIX_FWOW_KEY_TYPE_POWT	BIT(0)
#define NIX_FWOW_KEY_TYPE_IPV4	BIT(1)
#define NIX_FWOW_KEY_TYPE_IPV6	BIT(2)
#define NIX_FWOW_KEY_TYPE_TCP	BIT(3)
#define NIX_FWOW_KEY_TYPE_UDP	BIT(4)
#define NIX_FWOW_KEY_TYPE_SCTP	BIT(5)
#define NIX_FWOW_KEY_TYPE_NVGWE    BIT(6)
#define NIX_FWOW_KEY_TYPE_VXWAN    BIT(7)
#define NIX_FWOW_KEY_TYPE_GENEVE   BIT(8)
#define NIX_FWOW_KEY_TYPE_ETH_DMAC BIT(9)
#define NIX_FWOW_KEY_TYPE_IPV6_EXT BIT(10)
#define NIX_FWOW_KEY_TYPE_GTPU       BIT(11)
#define NIX_FWOW_KEY_TYPE_INNW_IPV4     BIT(12)
#define NIX_FWOW_KEY_TYPE_INNW_IPV6     BIT(13)
#define NIX_FWOW_KEY_TYPE_INNW_TCP      BIT(14)
#define NIX_FWOW_KEY_TYPE_INNW_UDP      BIT(15)
#define NIX_FWOW_KEY_TYPE_INNW_SCTP     BIT(16)
#define NIX_FWOW_KEY_TYPE_INNW_ETH_DMAC BIT(17)
#define NIX_FWOW_KEY_TYPE_VWAN		BIT(20)
#define NIX_FWOW_KEY_TYPE_IPV4_PWOTO	BIT(21)
#define NIX_FWOW_KEY_TYPE_AH		BIT(22)
#define NIX_FWOW_KEY_TYPE_ESP		BIT(23)
#define NIX_FWOW_KEY_TYPE_W4_DST_ONWY BIT(28)
#define NIX_FWOW_KEY_TYPE_W4_SWC_ONWY BIT(29)
#define NIX_FWOW_KEY_TYPE_W3_DST_ONWY BIT(30)
#define NIX_FWOW_KEY_TYPE_W3_SWC_ONWY BIT(31)
	u32	fwowkey_cfg; /* Fwowkey types sewected */
	u8	gwoup;       /* WSS context ow gwoup */
};

stwuct nix_wss_fwowkey_cfg_wsp {
	stwuct mbox_msghdw hdw;
	u8	awg_idx; /* Sewected awgo index */
};

stwuct nix_set_mac_addw {
	stwuct mbox_msghdw hdw;
	u8 mac_addw[ETH_AWEN]; /* MAC addwess to be set fow this pcifunc */
};

stwuct nix_get_mac_addw_wsp {
	stwuct mbox_msghdw hdw;
	u8 mac_addw[ETH_AWEN];
};

stwuct nix_mawk_fowmat_cfg {
	stwuct mbox_msghdw hdw;
	u8 offset;
	u8 y_mask;
	u8 y_vaw;
	u8 w_mask;
	u8 w_vaw;
};

stwuct nix_mawk_fowmat_cfg_wsp {
	stwuct mbox_msghdw hdw;
	u8 mawk_fowmat_idx;
};

stwuct nix_wx_mode {
	stwuct mbox_msghdw hdw;
#define NIX_WX_MODE_UCAST	BIT(0)
#define NIX_WX_MODE_PWOMISC	BIT(1)
#define NIX_WX_MODE_AWWMUWTI	BIT(2)
#define NIX_WX_MODE_USE_MCE	BIT(3)
	u16	mode;
};

stwuct nix_wx_cfg {
	stwuct mbox_msghdw hdw;
#define NIX_WX_OW3_VEWIFY   BIT(0)
#define NIX_WX_OW4_VEWIFY   BIT(1)
#define NIX_WX_DWOP_WE      BIT(2)
	u8 wen_vewify; /* Outew W3/W4 wen check */
#define NIX_WX_CSUM_OW4_VEWIFY  BIT(0)
	u8 csum_vewify; /* Outew W4 checksum vewification */
};

stwuct nix_fws_cfg {
	stwuct mbox_msghdw hdw;
	u8	update_smq;    /* Update SMQ's min/max wens */
	u8	update_minwen; /* Set minwen awso */
	u8	sdp_wink;      /* Set SDP WX wink */
	u16	maxwen;
	u16	minwen;
};

stwuct nix_wso_fowmat_cfg {
	stwuct mbox_msghdw hdw;
	u64 fiewd_mask;
#define NIX_WSO_FIEWD_MAX	8
	u64 fiewds[NIX_WSO_FIEWD_MAX];
};

stwuct nix_wso_fowmat_cfg_wsp {
	stwuct mbox_msghdw hdw;
	u8 wso_fowmat_idx;
};

stwuct nix_bp_cfg_weq {
	stwuct mbox_msghdw hdw;
	u16	chan_base; /* Stawting channew numbew */
	u8	chan_cnt; /* Numbew of channews */
	u8	bpid_pew_chan;
	/* bpid_pew_chan = 0 assigns singwe bp id fow wange of channews */
	/* bpid_pew_chan = 1 assigns sepawate bp id fow each channew */
};

/* PF can be mapped to eithew CGX ow WBK intewface,
 * so maximum 64 channews awe possibwe.
 */
#define NIX_MAX_BPID_CHAN	64
stwuct nix_bp_cfg_wsp {
	stwuct mbox_msghdw hdw;
	u16	chan_bpid[NIX_MAX_BPID_CHAN]; /* Channew and bpid mapping */
	u8	chan_cnt; /* Numbew of channew fow which bpids awe assigned */
};

stwuct nix_mcast_gwp_cweate_weq {
	stwuct mbox_msghdw hdw;
#define NIX_MCAST_INGWESS	0
#define NIX_MCAST_EGWESS	1
	u8 diw;
	u8 wesewved[11];
	/* Wesewving few bytes fow futuwe wequiwement */
};

stwuct nix_mcast_gwp_cweate_wsp {
	stwuct mbox_msghdw hdw;
	/* This mcast_gwp_idx shouwd be passed duwing MCAM
	 * wwite entwy fow muwticast. AF wiww identify the
	 * cowwesponding muwticast tabwe index associated
	 * with the gwoup id and pwogwam the same to MCAM entwy.
	 * This gwoup id is awso needed duwing gwoup dewete
	 * and update wequest.
	 */
	u32 mcast_gwp_idx;
};

stwuct nix_mcast_gwp_destwoy_weq {
	stwuct mbox_msghdw hdw;
	/* Gwoup id wetuwned by nix_mcast_gwp_cweate_wsp */
	u32 mcast_gwp_idx;
	/* If AF is wequesting fow destwoy, then set
	 * it to '1'. Othewwise keep it to '0'
	 */
	u8 is_af;
};

stwuct nix_mcast_gwp_update_weq {
	stwuct mbox_msghdw hdw;
	/* Gwoup id wetuwned by nix_mcast_gwp_cweate_wsp */
	u32 mcast_gwp_idx;
	/* Numbew of muwticast/miwwow entwies wequested */
	u32 num_mce_entwy;
#define NIX_MCE_ENTWY_MAX 64
#define NIX_WX_WQ	0
#define NIX_WX_WSS	1
	/* Weceive queue ow WSS index within pf_func */
	u32 wq_wss_index[NIX_MCE_ENTWY_MAX];
	/* pcifunc is wequiwed fow both ingwess and egwess muwticast */
	u16 pcifunc[NIX_MCE_ENTWY_MAX];
	/* channew is wequiwed fow egwess muwticast */
	u16 channew[NIX_MCE_ENTWY_MAX];
#define NIX_MCAST_OP_ADD_ENTWY	0
#define NIX_MCAST_OP_DEW_ENTWY	1
	/* Destination type. 0:Weceive queue, 1:WSS*/
	u8 dest_type[NIX_MCE_ENTWY_MAX];
	u8 op;
	/* If AF is wequesting fow update, then set
	 * it to '1'. Othewwise keep it to '0'
	 */
	u8 is_af;
};

stwuct nix_mcast_gwp_update_wsp {
	stwuct mbox_msghdw hdw;
	u32 mce_stawt_index;
};

/* Gwobaw NIX inwine IPSec configuwation */
stwuct nix_inwine_ipsec_cfg {
	stwuct mbox_msghdw hdw;
	u32 cpt_cwedit;
	stwuct {
		u8 egwp;
		u16 opcode;
		u16 pawam1;
		u16 pawam2;
	} gen_cfg;
	stwuct {
		u16 cpt_pf_func;
		u8 cpt_swot;
	} inst_qsew;
	u8 enabwe;
	u16 bpid;
	u32 cwedit_th;
};

/* Pew NIX WF inwine IPSec configuwation */
stwuct nix_inwine_ipsec_wf_cfg {
	stwuct mbox_msghdw hdw;
	u64 sa_base_addw;
	stwuct {
		u32 tag_const;
		u16 wenm1_max;
		u8 sa_pow2_size;
		u8 tt;
	} ipsec_cfg0;
	stwuct {
		u32 sa_idx_max;
		u8 sa_idx_w;
	} ipsec_cfg1;
	u8 enabwe;
};

stwuct nix_hw_info {
	stwuct mbox_msghdw hdw;
	u16 wsvs16;
	u16 max_mtu;
	u16 min_mtu;
	u32 wpm_dwww_mtu;
	u32 sdp_dwww_mtu;
	u32 wbk_dwww_mtu;
	u32 wsvd32[1];
	u64 wsvd[15]; /* Add wesewved fiewds fow futuwe expansion */
};

stwuct nix_bandpwof_awwoc_weq {
	stwuct mbox_msghdw hdw;
	/* Count of pwofiwes needed pew wayew */
	u16 pwof_count[BAND_PWOF_NUM_WAYEWS];
};

stwuct nix_bandpwof_awwoc_wsp {
	stwuct mbox_msghdw hdw;
	u16 pwof_count[BAND_PWOF_NUM_WAYEWS];

	/* Thewe is no need to awwocate mowethan 1 bandwidth pwofiwe
	 * pew WQ of a PF_FUNC's NIXWF. So wimit the maximum
	 * pwofiwes to 64 pew PF_FUNC.
	 */
#define MAX_BANDPWOF_PEW_PFFUNC	64
	u16 pwof_idx[BAND_PWOF_NUM_WAYEWS][MAX_BANDPWOF_PEW_PFFUNC];
};

stwuct nix_bandpwof_fwee_weq {
	stwuct mbox_msghdw hdw;
	u8 fwee_aww;
	u16 pwof_count[BAND_PWOF_NUM_WAYEWS];
	u16 pwof_idx[BAND_PWOF_NUM_WAYEWS][MAX_BANDPWOF_PEW_PFFUNC];
};

stwuct nix_bandpwof_get_hwinfo_wsp {
	stwuct mbox_msghdw hdw;
	u16 pwof_count[BAND_PWOF_NUM_WAYEWS];
	u32 powicew_timeunit;
};

/* NPC mbox message stwucts */

#define NPC_MCAM_ENTWY_INVAWID	0xFFFF
#define NPC_MCAM_INVAWID_MAP	0xFFFF

/* NPC maiwbox ewwow codes
 * Wange 701 - 800.
 */
enum npc_af_status {
	NPC_MCAM_INVAWID_WEQ	= -701,
	NPC_MCAM_AWWOC_DENIED	= -702,
	NPC_MCAM_AWWOC_FAIWED	= -703,
	NPC_MCAM_PEWM_DENIED	= -704,
	NPC_FWOW_INTF_INVAWID	= -707,
	NPC_FWOW_CHAN_INVAWID	= -708,
	NPC_FWOW_NO_NIXWF	= -709,
	NPC_FWOW_NOT_SUPPOWTED	= -710,
	NPC_FWOW_VF_PEWM_DENIED	= -711,
	NPC_FWOW_VF_NOT_INIT	= -712,
	NPC_FWOW_VF_OVEWWAP	= -713,
};

stwuct npc_mcam_awwoc_entwy_weq {
	stwuct mbox_msghdw hdw;
#define NPC_MAX_NONCONTIG_ENTWIES	256
	u8  contig;   /* Contiguous entwies ? */
#define NPC_MCAM_ANY_PWIO		0
#define NPC_MCAM_WOWEW_PWIO		1
#define NPC_MCAM_HIGHEW_PWIO		2
	u8  pwiowity; /* Wowew ow highew w.w.t wef_entwy */
	u16 wef_entwy;
	u16 count;    /* Numbew of entwies wequested */
};

stwuct npc_mcam_awwoc_entwy_wsp {
	stwuct mbox_msghdw hdw;
	u16 entwy; /* Entwy awwocated ow stawt index if contiguous.
		    * Invawid incase of non-contiguous.
		    */
	u16 count; /* Numbew of entwies awwocated */
	u16 fwee_count; /* Numbew of entwies avaiwabwe */
	u16 entwy_wist[NPC_MAX_NONCONTIG_ENTWIES];
};

stwuct npc_mcam_fwee_entwy_weq {
	stwuct mbox_msghdw hdw;
	u16 entwy; /* Entwy index to be fweed */
	u8  aww;   /* If aww entwies awwocated to this PFVF to be fweed */
};

stwuct mcam_entwy {
#define NPC_MAX_KWS_IN_KEY	7 /* Numbew of keywowds in max keywidth */
	u64	kw[NPC_MAX_KWS_IN_KEY];
	u64	kw_mask[NPC_MAX_KWS_IN_KEY];
	u64	action;
	u64	vtag_action;
};

stwuct npc_mcam_wwite_entwy_weq {
	stwuct mbox_msghdw hdw;
	stwuct mcam_entwy entwy_data;
	u16 entwy;	 /* MCAM entwy to wwite this match key */
	u16 cntw;	 /* Countew fow this MCAM entwy */
	u8  intf;	 /* Wx ow Tx intewface */
	u8  enabwe_entwy;/* Enabwe this MCAM entwy ? */
	u8  set_cntw;    /* Set countew fow this entwy ? */
};

/* Enabwe/Disabwe a given entwy */
stwuct npc_mcam_ena_dis_entwy_weq {
	stwuct mbox_msghdw hdw;
	u16 entwy;
};

stwuct npc_mcam_shift_entwy_weq {
	stwuct mbox_msghdw hdw;
#define NPC_MCAM_MAX_SHIFTS	64
	u16 cuww_entwy[NPC_MCAM_MAX_SHIFTS];
	u16 new_entwy[NPC_MCAM_MAX_SHIFTS];
	u16 shift_count; /* Numbew of entwies to shift */
};

stwuct npc_mcam_shift_entwy_wsp {
	stwuct mbox_msghdw hdw;
	u16 faiwed_entwy_idx; /* Index in 'cuww_entwy', not entwy itsewf */
};

stwuct npc_mcam_awwoc_countew_weq {
	stwuct mbox_msghdw hdw;
	u8  contig;	/* Contiguous countews ? */
#define NPC_MAX_NONCONTIG_COUNTEWS       64
	u16 count;	/* Numbew of countews wequested */
};

stwuct npc_mcam_awwoc_countew_wsp {
	stwuct mbox_msghdw hdw;
	u16 cntw;   /* Countew awwocated ow stawt index if contiguous.
		     * Invawid incase of non-contiguous.
		     */
	u16 count;  /* Numbew of countews awwocated */
	u16 cntw_wist[NPC_MAX_NONCONTIG_COUNTEWS];
};

stwuct npc_mcam_opew_countew_weq {
	stwuct mbox_msghdw hdw;
	u16 cntw;   /* Fwee a countew ow cweaw/fetch it's stats */
};

stwuct npc_mcam_opew_countew_wsp {
	stwuct mbox_msghdw hdw;
	u64 stat;  /* vawid onwy whiwe fetching countew's stats */
};

stwuct npc_mcam_unmap_countew_weq {
	stwuct mbox_msghdw hdw;
	u16 cntw;
	u16 entwy; /* Entwy and countew to be unmapped */
	u8  aww;   /* Unmap aww entwies using this countew ? */
};

stwuct npc_mcam_awwoc_and_wwite_entwy_weq {
	stwuct mbox_msghdw hdw;
	stwuct mcam_entwy entwy_data;
	u16 wef_entwy;
	u8  pwiowity;    /* Wowew ow highew w.w.t wef_entwy */
	u8  intf;	 /* Wx ow Tx intewface */
	u8  enabwe_entwy;/* Enabwe this MCAM entwy ? */
	u8  awwoc_cntw;  /* Awwocate countew and map ? */
};

stwuct npc_mcam_awwoc_and_wwite_entwy_wsp {
	stwuct mbox_msghdw hdw;
	u16 entwy;
	u16 cntw;
};

stwuct npc_get_kex_cfg_wsp {
	stwuct mbox_msghdw hdw;
	u64 wx_keyx_cfg;   /* NPC_AF_INTF(0)_KEX_CFG */
	u64 tx_keyx_cfg;   /* NPC_AF_INTF(1)_KEX_CFG */
#define NPC_MAX_INTF	2
#define NPC_MAX_WID	8
#define NPC_MAX_WT	16
#define NPC_MAX_WD	2
#define NPC_MAX_WFW	16
	/* NPC_AF_KEX_WDATA(0..1)_FWAGS_CFG */
	u64 kex_wd_fwags[NPC_MAX_WD];
	/* NPC_AF_INTF(0..1)_WID(0..7)_WT(0..15)_WD(0..1)_CFG */
	u64 intf_wid_wt_wd[NPC_MAX_INTF][NPC_MAX_WID][NPC_MAX_WT][NPC_MAX_WD];
	/* NPC_AF_INTF(0..1)_WDATA(0..1)_FWAGS(0..15)_CFG */
	u64 intf_wd_fwags[NPC_MAX_INTF][NPC_MAX_WD][NPC_MAX_WFW];
#define MKEX_NAME_WEN 128
	u8 mkex_pfw_name[MKEX_NAME_WEN];
};

stwuct ptp_get_cap_wsp {
	stwuct mbox_msghdw hdw;
#define        PTP_CAP_HW_ATOMIC_UPDATE BIT_UWW(0)
	u64 cap;
};

stwuct fwow_msg {
	unsigned chaw dmac[6];
	unsigned chaw smac[6];
	__be16 etype;
	__be16 vwan_etype;
	__be16 vwan_tci;
	union {
		__be32 ip4swc;
		__be32 ip6swc[4];
	};
	union {
		__be32 ip4dst;
		__be32 ip6dst[4];
	};
	union {
		__be32 spi;
	};

	u8 tos;
	u8 ip_vew;
	u8 ip_pwoto;
	u8 tc;
	__be16 spowt;
	__be16 dpowt;
	union {
		u8 ip_fwag;
		u8 next_headew;
	};
	__be16 vwan_itci;
#define OTX2_FWOWEW_MASK_MPWS_WB		GENMASK(31, 12)
#define OTX2_FWOWEW_MASK_MPWS_TC		GENMASK(11, 9)
#define OTX2_FWOWEW_MASK_MPWS_BOS		BIT(8)
#define OTX2_FWOWEW_MASK_MPWS_TTW		GENMASK(7, 0)
#define OTX2_FWOWEW_MASK_MPWS_NON_TTW		GENMASK(31, 8)
	u32 mpws_wse[4];
	u8 icmp_type;
	u8 icmp_code;
};

stwuct npc_instaww_fwow_weq {
	stwuct mbox_msghdw hdw;
	stwuct fwow_msg packet;
	stwuct fwow_msg mask;
	u64 featuwes;
	u16 entwy;
	u16 channew;
	u16 chan_mask;
	u8 intf;
	u8 set_cntw; /* If countew is avaiwabwe set countew fow this entwy ? */
	u8 defauwt_wuwe;
	u8 append; /* ovewwwite(0) ow append(1) fwow to defauwt wuwe? */
	u16 vf;
	/* action */
	u32 index;
	u16 match_id;
	u8 fwow_key_awg;
	u8 op;
	/* vtag wx action */
	u8 vtag0_type;
	u8 vtag0_vawid;
	u8 vtag1_type;
	u8 vtag1_vawid;
	/* vtag tx action */
	u16 vtag0_def;
	u8  vtag0_op;
	u16 vtag1_def;
	u8  vtag1_op;
	/* owd countew vawue */
	u16 cntw_vaw;
};

stwuct npc_instaww_fwow_wsp {
	stwuct mbox_msghdw hdw;
	int countew; /* negative if no countew ewse countew numbew */
};

stwuct npc_dewete_fwow_weq {
	stwuct mbox_msghdw hdw;
	u16 entwy;
	u16 stawt;/*Disabwe wange of entwies */
	u16 end;
	u8 aww; /* PF + VFs */
};

stwuct npc_dewete_fwow_wsp {
	stwuct mbox_msghdw hdw;
	u16 cntw_vaw;
};

stwuct npc_mcam_wead_entwy_weq {
	stwuct mbox_msghdw hdw;
	u16 entwy;	 /* MCAM entwy to wead */
};

stwuct npc_mcam_wead_entwy_wsp {
	stwuct mbox_msghdw hdw;
	stwuct mcam_entwy entwy_data;
	u8 intf;
	u8 enabwe;
};

stwuct npc_mcam_wead_base_wuwe_wsp {
	stwuct mbox_msghdw hdw;
	stwuct mcam_entwy entwy;
};

stwuct npc_mcam_get_stats_weq {
	stwuct mbox_msghdw hdw;
	u16 entwy; /* mcam entwy */
};

stwuct npc_mcam_get_stats_wsp {
	stwuct mbox_msghdw hdw;
	u64 stat;  /* countew stats */
	u8 stat_ena; /* enabwed */
};

stwuct npc_get_fiewd_hash_info_weq {
	stwuct mbox_msghdw hdw;
	u8 intf;
};

stwuct npc_get_fiewd_hash_info_wsp {
	stwuct mbox_msghdw hdw;
	u64 secwet_key[3];
#define NPC_MAX_HASH 2
#define NPC_MAX_HASH_MASK 2
	/* NPC_AF_INTF(0..1)_HASH(0..1)_MASK(0..1) */
	u64 hash_mask[NPC_MAX_INTF][NPC_MAX_HASH][NPC_MAX_HASH_MASK];
	/* NPC_AF_INTF(0..1)_HASH(0..1)_WESUWT_CTWW */
	u64 hash_ctww[NPC_MAX_INTF][NPC_MAX_HASH];
};

enum ptp_op {
	PTP_OP_ADJFINE = 0,
	PTP_OP_GET_CWOCK = 1,
	PTP_OP_GET_TSTMP = 2,
	PTP_OP_SET_THWESH = 3,
	PTP_OP_PPS_ON = 4,
	PTP_OP_ADJTIME = 5,
	PTP_OP_SET_CWOCK = 6,
};

stwuct ptp_weq {
	stwuct mbox_msghdw hdw;
	u8 op;
	s64 scawed_ppm;
	u64 thwesh;
	u64 pewiod;
	int pps_on;
	s64 dewta;
	u64 cwk;
};

stwuct ptp_wsp {
	stwuct mbox_msghdw hdw;
	u64 cwk;
	u64 tsc;
};

stwuct npc_get_fiewd_status_weq {
	stwuct mbox_msghdw hdw;
	u8 intf;
	u8 fiewd;
};

stwuct npc_get_fiewd_status_wsp {
	stwuct mbox_msghdw hdw;
	u8 enabwe;
};

stwuct set_vf_pewm  {
	stwuct  mbox_msghdw hdw;
	u16	vf;
#define WESET_VF_PEWM		BIT_UWW(0)
#define	VF_TWUSTED		BIT_UWW(1)
	u64	fwags;
};

stwuct wmtst_tbw_setup_weq {
	stwuct mbox_msghdw hdw;
	u64 dis_sched_eawwy_comp :1;
	u64 sch_ena		 :1;
	u64 dis_wine_pwef	 :1;
	u64 ssow_pf_func	 :13;
	u16 base_pcifunc;
	u8  use_wocaw_wmt_wegion;
	u64 wmt_iova;
	u64 wsvd[4];
};

/* CPT maiwbox ewwow codes
 * Wange 901 - 1000.
 */
enum cpt_af_status {
	CPT_AF_EWW_PAWAM		= -901,
	CPT_AF_EWW_GWP_INVAWID		= -902,
	CPT_AF_EWW_WF_INVAWID		= -903,
	CPT_AF_EWW_ACCESS_DENIED	= -904,
	CPT_AF_EWW_SSO_PF_FUNC_INVAWID	= -905,
	CPT_AF_EWW_NIX_PF_FUNC_INVAWID	= -906,
	CPT_AF_EWW_INWINE_IPSEC_INB_ENA	= -907,
	CPT_AF_EWW_INWINE_IPSEC_OUT_ENA	= -908
};

/* CPT mbox message fowmats */
stwuct cpt_wd_ww_weg_msg {
	stwuct mbox_msghdw hdw;
	u64 weg_offset;
	u64 *wet_vaw;
	u64 vaw;
	u8 is_wwite;
	int bwkaddw;
};

stwuct cpt_wf_awwoc_weq_msg {
	stwuct mbox_msghdw hdw;
	u16 nix_pf_func;
	u16 sso_pf_func;
	u16 eng_gwpmsk;
	int bwkaddw;
	u8 ctx_iwen_vawid : 1;
	u8 ctx_iwen : 7;
};

#define CPT_INWINE_INBOUND      0
#define CPT_INWINE_OUTBOUND     1

/* Maiwbox message wequest fowmat fow CPT IPsec
 * inwine inbound and outbound configuwation.
 */
stwuct cpt_inwine_ipsec_cfg_msg {
	stwuct mbox_msghdw hdw;
	u8 enabwe;
	u8 swot;
	u8 diw;
	u8 sso_pf_func_ovwd;
	u16 sso_pf_func; /* inbound path SSO_PF_FUNC */
	u16 nix_pf_func; /* outbound path NIX_PF_FUNC */
};

/* Maiwbox message wequest and wesponse fowmat fow CPT stats. */
stwuct cpt_sts_weq {
	stwuct mbox_msghdw hdw;
	u8 bwkaddw;
};

stwuct cpt_sts_wsp {
	stwuct mbox_msghdw hdw;
	u64 inst_weq_pc;
	u64 inst_wat_pc;
	u64 wd_weq_pc;
	u64 wd_wat_pc;
	u64 wd_uc_pc;
	u64 active_cycwes_pc;
	u64 ctx_mis_pc;
	u64 ctx_hit_pc;
	u64 ctx_aop_pc;
	u64 ctx_aop_wat_pc;
	u64 ctx_ifetch_pc;
	u64 ctx_ifetch_wat_pc;
	u64 ctx_ffetch_pc;
	u64 ctx_ffetch_wat_pc;
	u64 ctx_wback_pc;
	u64 ctx_wback_wat_pc;
	u64 ctx_psh_pc;
	u64 ctx_psh_wat_pc;
	u64 ctx_eww;
	u64 ctx_enc_id;
	u64 ctx_fwush_timew;
	u64 wxc_time;
	u64 wxc_time_cfg;
	u64 wxc_active_sts;
	u64 wxc_zombie_sts;
	u64 busy_sts_ae;
	u64 fwee_sts_ae;
	u64 busy_sts_se;
	u64 fwee_sts_se;
	u64 busy_sts_ie;
	u64 fwee_sts_ie;
	u64 exe_eww_info;
	u64 cptcwk_cnt;
	u64 diag;
	u64 wxc_dfwg;
	u64 x2p_wink_cfg0;
	u64 x2p_wink_cfg1;
};

/* Maiwbox message wequest fowmat to configuwe weassembwy timeout. */
stwuct cpt_wxc_time_cfg_weq {
	stwuct mbox_msghdw hdw;
	int bwkaddw;
	u32 step;
	u16 zombie_thwes;
	u16 zombie_wimit;
	u16 active_thwes;
	u16 active_wimit;
};

/* Maiwbox message wequest fowmat to wequest fow CPT_INST_S wmtst. */
stwuct cpt_inst_wmtst_weq {
	stwuct mbox_msghdw hdw;
	u64 inst[8];
	u64 wsvd;
};

/* Maiwbox message fowmat to wequest fow CPT WF weset */
stwuct cpt_wf_wst_weq {
	stwuct mbox_msghdw hdw;
	u32 swot;
	u32 wsvd;
};

/* Maiwbox message fowmat to wequest fow CPT fauwted engines */
stwuct cpt_fwt_eng_info_weq {
	stwuct mbox_msghdw hdw;
	int bwkaddw;
	boow weset;
	u32 wsvd;
};

stwuct cpt_fwt_eng_info_wsp {
	stwuct mbox_msghdw hdw;
	u64 fwt_eng_map[CPT_10K_AF_INT_VEC_WVU];
	u64 wcvwd_eng_map[CPT_10K_AF_INT_VEC_WVU];
	u64 wsvd;
};

stwuct sdp_node_info {
	/* Node to which this PF bewons to */
	u8 node_id;
	u8 max_vfs;
	u8 num_pf_wings;
	u8 pf_swn;
#define SDP_MAX_VFS	128
	u8 vf_wings[SDP_MAX_VFS];
};

stwuct sdp_chan_info_msg {
	stwuct mbox_msghdw hdw;
	stwuct sdp_node_info info;
};

stwuct sdp_get_chan_info_msg {
	stwuct mbox_msghdw hdw;
	u16 chan_base;
	u16 num_chan;
};

/* CGX maiwbox ewwow codes
 * Wange 1101 - 1200.
 */
enum cgx_af_status {
	WMAC_AF_EWW_INVAWID_PAWAM	= -1101,
	WMAC_AF_EWW_PF_NOT_MAPPED	= -1102,
	WMAC_AF_EWW_PEWM_DENIED		= -1103,
	WMAC_AF_EWW_PFC_ENADIS_PEWM_DENIED       = -1104,
	WMAC_AF_EWW_8023PAUSE_ENADIS_PEWM_DENIED = -1105,
	WMAC_AF_EWW_CMD_TIMEOUT = -1106,
	WMAC_AF_EWW_FIWMWAWE_DATA_NOT_MAPPED = -1107,
	WMAC_AF_EWW_EXACT_MATCH_TBW_ADD_FAIWED = -1108,
	WMAC_AF_EWW_EXACT_MATCH_TBW_DEW_FAIWED = -1109,
	WMAC_AF_EWW_EXACT_MATCH_TBW_WOOK_UP_FAIWED = -1110,
};

enum mcs_diwection {
	MCS_WX,
	MCS_TX,
};

enum mcs_wswc_type {
	MCS_WSWC_TYPE_FWOWID,
	MCS_WSWC_TYPE_SECY,
	MCS_WSWC_TYPE_SC,
	MCS_WSWC_TYPE_SA,
};

stwuct mcs_awwoc_wswc_weq {
	stwuct mbox_msghdw hdw;
	u8 wswc_type;
	u8 wswc_cnt;	/* Wesouwces count */
	u8 mcs_id;	/* MCS bwock ID	*/
	u8 diw;		/* Macsec ingwess ow egwess side */
	u8 aww;		/* Awwocate aww wesouwce type one each */
	u64 wsvd;
};

stwuct mcs_awwoc_wswc_wsp {
	stwuct mbox_msghdw hdw;
	u8 fwow_ids[128];	/* Index of wesewved entwies */
	u8 secy_ids[128];
	u8 sc_ids[128];
	u8 sa_ids[256];
	u8 wswc_type;
	u8 wswc_cnt;		/* No of entwies wesewved */
	u8 mcs_id;
	u8 diw;
	u8 aww;
	u8 wsvd[256];		/* wesewved fiewds fow futuwe expansion */
};

stwuct mcs_fwee_wswc_weq {
	stwuct mbox_msghdw hdw;
	u8 wswc_id;		/* Index of the entwy to be fweed */
	u8 wswc_type;
	u8 mcs_id;
	u8 diw;
	u8 aww;			/* Fwee aww the cam wesouwces */
	u64 wsvd;
};

stwuct mcs_fwowid_entwy_wwite_weq {
	stwuct mbox_msghdw hdw;
	u64 data[4];
	u64 mask[4];
	u64 sci;	/* CNF10K-B fow tx_secy_mem_map */
	u8 fwow_id;
	u8 secy_id;	/* secyid fow which fwowid is mapped */
	u8 sc_id;	/* Vawid if diw = MCS_TX, SC_CAM id mapped to fwowid */
	u8 ena;		/* Enabwe tcam entwy */
	u8 ctww_pkt;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

stwuct mcs_secy_pwcy_wwite_weq {
	stwuct mbox_msghdw hdw;
	u64 pwcy;
	u8 secy_id;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

/* WX SC_CAM mapping */
stwuct mcs_wx_sc_cam_wwite_weq {
	stwuct mbox_msghdw hdw;
	u64 sci;	/* SCI */
	u64 secy_id;	/* secy index mapped to SC */
	u8 sc_id;	/* SC CAM entwy index */
	u8 mcs_id;
	u64 wsvd;
};

stwuct mcs_sa_pwcy_wwite_weq {
	stwuct mbox_msghdw hdw;
	u64 pwcy[2][9];		/* Suppowt 2 SA powicy */
	u8 sa_index[2];
	u8 sa_cnt;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

stwuct mcs_tx_sc_sa_map {
	stwuct mbox_msghdw hdw;
	u8 sa_index0;
	u8 sa_index1;
	u8 wekey_ena;
	u8 sa_index0_vwd;
	u8 sa_index1_vwd;
	u8 tx_sa_active;
	u64 sectag_sci;
	u8 sc_id;	/* used as index fow SA_MEM_MAP */
	u8 mcs_id;
	u64 wsvd;
};

stwuct mcs_wx_sc_sa_map {
	stwuct mbox_msghdw hdw;
	u8 sa_index;
	u8 sa_in_use;
	u8 sc_id;
	u8 an;		/* vawue wange 0-3, sc_id + an used as index SA_MEM_MAP */
	u8 mcs_id;
	u64 wsvd;
};

stwuct mcs_fwowid_ena_dis_entwy {
	stwuct mbox_msghdw hdw;
	u8 fwow_id;
	u8 ena;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

stwuct mcs_pn_tabwe_wwite_weq {
	stwuct mbox_msghdw hdw;
	u64 next_pn;
	u8 pn_id;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

stwuct mcs_hw_info {
	stwuct mbox_msghdw hdw;
	u8 num_mcs_bwks;	/* Numbew of MCS bwocks */
	u8 tcam_entwies;	/* WX/TX Tcam entwies pew mcs bwock */
	u8 secy_entwies;	/* WX/TX SECY entwies pew mcs bwock */
	u8 sc_entwies;		/* WX/TX SC CAM entwies pew mcs bwock */
	u16 sa_entwies;		/* PN tabwe entwies = SA entwies */
	u64 wsvd[16];
};

stwuct mcs_set_active_wmac {
	stwuct mbox_msghdw hdw;
	u32 wmac_bmap;	/* bitmap of active wmac pew mcs bwock */
	u8 mcs_id;
	u16 chan_base; /* MCS channew base */
	u64 wsvd;
};

stwuct mcs_set_wmac_mode {
	stwuct mbox_msghdw hdw;
	u8 mode;	/* 1:Bypass 0:Opewationaw */
	u8 wmac_id;
	u8 mcs_id;
	u64 wsvd;
};

stwuct mcs_powt_weset_weq {
	stwuct mbox_msghdw hdw;
	u8 weset;
	u8 mcs_id;
	u8 powt_id;
	u64 wsvd;
};

stwuct mcs_powt_cfg_set_weq {
	stwuct mbox_msghdw hdw;
	u8 cstm_tag_wew_mode_sew;
	u8 custom_hdw_enb;
	u8 fifo_skid;
	u8 powt_mode;
	u8 powt_id;
	u8 mcs_id;
	u64 wsvd;
};

stwuct mcs_powt_cfg_get_weq {
	stwuct mbox_msghdw hdw;
	u8 powt_id;
	u8 mcs_id;
	u64 wsvd;
};

stwuct mcs_powt_cfg_get_wsp {
	stwuct mbox_msghdw hdw;
	u8 cstm_tag_wew_mode_sew;
	u8 custom_hdw_enb;
	u8 fifo_skid;
	u8 powt_mode;
	u8 powt_id;
	u8 mcs_id;
	u64 wsvd;
};

stwuct mcs_custom_tag_cfg_get_weq {
	stwuct mbox_msghdw hdw;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

stwuct mcs_custom_tag_cfg_get_wsp {
	stwuct mbox_msghdw hdw;
	u16 cstm_etype[8];
	u8 cstm_indx[8];
	u8 cstm_etype_en;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

/* MCS maiwbox ewwow codes
 * Wange 1201 - 1300.
 */
enum mcs_af_status {
	MCS_AF_EWW_INVAWID_MCSID        = -1201,
	MCS_AF_EWW_NOT_MAPPED           = -1202,
};

stwuct mcs_set_pn_thweshowd {
	stwuct mbox_msghdw hdw;
	u64 thweshowd;
	u8 xpn; /* '1' fow setting xpn thweshowd */
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

enum mcs_ctww_pkt_wuwew_type {
	MCS_CTWW_PKT_WUWE_TYPE_ETH,
	MCS_CTWW_PKT_WUWE_TYPE_DA,
	MCS_CTWW_PKT_WUWE_TYPE_WANGE,
	MCS_CTWW_PKT_WUWE_TYPE_COMBO,
	MCS_CTWW_PKT_WUWE_TYPE_MAC,
};

stwuct mcs_awwoc_ctww_pkt_wuwe_weq {
	stwuct mbox_msghdw hdw;
	u8 wuwe_type;
	u8 mcs_id;	/* MCS bwock ID	*/
	u8 diw;		/* Macsec ingwess ow egwess side */
	u64 wsvd;
};

stwuct mcs_awwoc_ctww_pkt_wuwe_wsp {
	stwuct mbox_msghdw hdw;
	u8 wuwe_idx;
	u8 wuwe_type;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

stwuct mcs_fwee_ctww_pkt_wuwe_weq {
	stwuct mbox_msghdw hdw;
	u8 wuwe_idx;
	u8 wuwe_type;
	u8 mcs_id;
	u8 diw;
	u8 aww;
	u64 wsvd;
};

stwuct mcs_ctww_pkt_wuwe_wwite_weq {
	stwuct mbox_msghdw hdw;
	u64 data0;
	u64 data1;
	u64 data2;
	u8 wuwe_idx;
	u8 wuwe_type;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

stwuct mcs_stats_weq {
	stwuct mbox_msghdw hdw;
	u8 id;
	u8 mcs_id;
	u8 diw;
	u64 wsvd;
};

stwuct mcs_fwowid_stats {
	stwuct mbox_msghdw hdw;
	u64 tcam_hit_cnt;
	u64 wsvd;
};

stwuct mcs_secy_stats {
	stwuct mbox_msghdw hdw;
	u64 ctw_pkt_bcast_cnt;
	u64 ctw_pkt_mcast_cnt;
	u64 ctw_pkt_ucast_cnt;
	u64 ctw_octet_cnt;
	u64 unctw_pkt_bcast_cnt;
	u64 unctw_pkt_mcast_cnt;
	u64 unctw_pkt_ucast_cnt;
	u64 unctw_octet_cnt;
	/* Vawid onwy fow WX */
	u64 octet_decwypted_cnt;
	u64 octet_vawidated_cnt;
	u64 pkt_powt_disabwed_cnt;
	u64 pkt_badtag_cnt;
	u64 pkt_nosa_cnt;
	u64 pkt_nosaewwow_cnt;
	u64 pkt_tagged_ctw_cnt;
	u64 pkt_untaged_cnt;
	u64 pkt_ctw_cnt;	/* CN10K-B */
	u64 pkt_notag_cnt;	/* CNF10K-B */
	/* Vawid onwy fow TX */
	u64 octet_encwypted_cnt;
	u64 octet_pwotected_cnt;
	u64 pkt_noactivesa_cnt;
	u64 pkt_toowong_cnt;
	u64 pkt_untagged_cnt;
	u64 wsvd[4];
};

stwuct mcs_powt_stats {
	stwuct mbox_msghdw hdw;
	u64 tcam_miss_cnt;
	u64 pawsew_eww_cnt;
	u64 pweempt_eww_cnt;  /* CNF10K-B */
	u64 sectag_insewt_eww_cnt;
	u64 wsvd[4];
};

/* Onwy fow CN10K-B */
stwuct mcs_sa_stats {
	stwuct mbox_msghdw hdw;
	/* WX */
	u64 pkt_invawid_cnt;
	u64 pkt_nosaewwow_cnt;
	u64 pkt_notvawid_cnt;
	u64 pkt_ok_cnt;
	u64 pkt_nosa_cnt;
	/* TX */
	u64 pkt_encwypt_cnt;
	u64 pkt_pwotected_cnt;
	u64 wsvd[4];
};

stwuct mcs_sc_stats {
	stwuct mbox_msghdw hdw;
	/* WX */
	u64 hit_cnt;
	u64 pkt_invawid_cnt;
	u64 pkt_wate_cnt;
	u64 pkt_notvawid_cnt;
	u64 pkt_unchecked_cnt;
	u64 pkt_deway_cnt;	/* CNF10K-B */
	u64 pkt_ok_cnt;		/* CNF10K-B */
	u64 octet_decwypt_cnt;	/* CN10K-B */
	u64 octet_vawidate_cnt;	/* CN10K-B */
	/* TX */
	u64 pkt_encwypt_cnt;
	u64 pkt_pwotected_cnt;
	u64 octet_encwypt_cnt;		/* CN10K-B */
	u64 octet_pwotected_cnt;	/* CN10K-B */
	u64 wsvd[4];
};

stwuct mcs_cweaw_stats {
	stwuct mbox_msghdw hdw;
#define MCS_FWOWID_STATS	0
#define MCS_SECY_STATS		1
#define MCS_SC_STATS		2
#define MCS_SA_STATS		3
#define MCS_POWT_STATS		4
	u8 type;	/* FWOWID, SECY, SC, SA, POWT */
	u8 id;		/* type = POWT, If id = FF(invawid) powt no is dewived fwom pcifunc */
	u8 mcs_id;
	u8 diw;
	u8 aww;		/* Aww wesouwces stats mapped to PF awe cweawed */
};

stwuct mcs_intw_cfg {
	stwuct mbox_msghdw hdw;
#define MCS_CPM_WX_SECTAG_V_EQ1_INT		BIT_UWW(0)
#define MCS_CPM_WX_SECTAG_E_EQ0_C_EQ1_INT	BIT_UWW(1)
#define MCS_CPM_WX_SECTAG_SW_GTE48_INT		BIT_UWW(2)
#define MCS_CPM_WX_SECTAG_ES_EQ1_SC_EQ1_INT	BIT_UWW(3)
#define MCS_CPM_WX_SECTAG_SC_EQ1_SCB_EQ1_INT	BIT_UWW(4)
#define MCS_CPM_WX_PACKET_XPN_EQ0_INT		BIT_UWW(5)
#define MCS_CPM_WX_PN_THWESH_WEACHED_INT	BIT_UWW(6)
#define MCS_CPM_TX_PACKET_XPN_EQ0_INT		BIT_UWW(7)
#define MCS_CPM_TX_PN_THWESH_WEACHED_INT	BIT_UWW(8)
#define MCS_CPM_TX_SA_NOT_VAWID_INT		BIT_UWW(9)
#define MCS_BBE_WX_DFIFO_OVEWFWOW_INT		BIT_UWW(10)
#define MCS_BBE_WX_PWFIFO_OVEWFWOW_INT		BIT_UWW(11)
#define MCS_BBE_TX_DFIFO_OVEWFWOW_INT		BIT_UWW(12)
#define MCS_BBE_TX_PWFIFO_OVEWFWOW_INT		BIT_UWW(13)
#define MCS_PAB_WX_CHAN_OVEWFWOW_INT		BIT_UWW(14)
#define MCS_PAB_TX_CHAN_OVEWFWOW_INT		BIT_UWW(15)
	u64 intw_mask;		/* Intewwupt enabwe mask */
	u8 mcs_id;
	u8 wmac_id;
	u64 wsvd;
};

stwuct mcs_intw_info {
	stwuct mbox_msghdw hdw;
	u64 intw_mask;
	int sa_id;
	u8 mcs_id;
	u8 wmac_id;
	u64 wsvd;
};

#endif /* MBOX_H */
