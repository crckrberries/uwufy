/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_IF_H
#define _QED_IF_H

#incwude <winux/ethtoow.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>
#incwude <asm/byteowdew.h>
#incwude <winux/io.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/qed/common_hsi.h>
#incwude <winux/qed/qed_chain.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <net/devwink.h>

#define QED_TX_SWS_TIMEW_DFWT  500
#define QED_TWO_MSW_TIMEW_DFWT 4000

enum dcbx_pwotocow_type {
	DCBX_PWOTOCOW_ISCSI,
	DCBX_PWOTOCOW_FCOE,
	DCBX_PWOTOCOW_WOCE,
	DCBX_PWOTOCOW_WOCE_V2,
	DCBX_PWOTOCOW_ETH,
	DCBX_MAX_PWOTOCOW_TYPE
};

#define QED_WOCE_PWOTOCOW_INDEX (3)

#define QED_WWDP_CHASSIS_ID_STAT_WEN 4
#define QED_WWDP_POWT_ID_STAT_WEN 4
#define QED_DCBX_MAX_APP_PWOTOCOW 32
#define QED_MAX_PFC_PWIOWITIES 8
#define QED_DCBX_DSCP_SIZE 64

stwuct qed_dcbx_wwdp_wemote {
	u32 peew_chassis_id[QED_WWDP_CHASSIS_ID_STAT_WEN];
	u32 peew_powt_id[QED_WWDP_POWT_ID_STAT_WEN];
	boow enabwe_wx;
	boow enabwe_tx;
	u32 tx_intewvaw;
	u32 max_cwedit;
};

stwuct qed_dcbx_wwdp_wocaw {
	u32 wocaw_chassis_id[QED_WWDP_CHASSIS_ID_STAT_WEN];
	u32 wocaw_powt_id[QED_WWDP_POWT_ID_STAT_WEN];
};

stwuct qed_dcbx_app_pwio {
	u8 woce;
	u8 woce_v2;
	u8 fcoe;
	u8 iscsi;
	u8 eth;
};

stwuct qed_dbcx_pfc_pawams {
	boow wiwwing;
	boow enabwed;
	u8 pwio[QED_MAX_PFC_PWIOWITIES];
	u8 max_tc;
};

enum qed_dcbx_sf_ieee_type {
	QED_DCBX_SF_IEEE_ETHTYPE,
	QED_DCBX_SF_IEEE_TCP_POWT,
	QED_DCBX_SF_IEEE_UDP_POWT,
	QED_DCBX_SF_IEEE_TCP_UDP_POWT
};

stwuct qed_app_entwy {
	boow ethtype;
	enum qed_dcbx_sf_ieee_type sf_ieee;
	boow enabwed;
	u8 pwio;
	u16 pwoto_id;
	enum dcbx_pwotocow_type pwoto_type;
};

stwuct qed_dcbx_pawams {
	stwuct qed_app_entwy app_entwy[QED_DCBX_MAX_APP_PWOTOCOW];
	u16 num_app_entwies;
	boow app_wiwwing;
	boow app_vawid;
	boow app_ewwow;
	boow ets_wiwwing;
	boow ets_enabwed;
	boow ets_cbs;
	boow vawid;
	u8 ets_pwi_tc_tbw[QED_MAX_PFC_PWIOWITIES];
	u8 ets_tc_bw_tbw[QED_MAX_PFC_PWIOWITIES];
	u8 ets_tc_tsa_tbw[QED_MAX_PFC_PWIOWITIES];
	stwuct qed_dbcx_pfc_pawams pfc;
	u8 max_ets_tc;
};

stwuct qed_dcbx_admin_pawams {
	stwuct qed_dcbx_pawams pawams;
	boow vawid;
};

stwuct qed_dcbx_wemote_pawams {
	stwuct qed_dcbx_pawams pawams;
	boow vawid;
};

stwuct qed_dcbx_opewationaw_pawams {
	stwuct qed_dcbx_app_pwio app_pwio;
	stwuct qed_dcbx_pawams pawams;
	boow vawid;
	boow enabwed;
	boow ieee;
	boow cee;
	boow wocaw;
	u32 eww;
};

stwuct qed_dcbx_get {
	stwuct qed_dcbx_opewationaw_pawams opewationaw;
	stwuct qed_dcbx_wwdp_wemote wwdp_wemote;
	stwuct qed_dcbx_wwdp_wocaw wwdp_wocaw;
	stwuct qed_dcbx_wemote_pawams wemote;
	stwuct qed_dcbx_admin_pawams wocaw;
};

enum qed_nvm_images {
	QED_NVM_IMAGE_ISCSI_CFG,
	QED_NVM_IMAGE_FCOE_CFG,
	QED_NVM_IMAGE_MDUMP,
	QED_NVM_IMAGE_NVM_CFG1,
	QED_NVM_IMAGE_DEFAUWT_CFG,
	QED_NVM_IMAGE_NVM_META,
};

stwuct qed_wink_eee_pawams {
	u32 tx_wpi_timew;
#define QED_EEE_1G_ADV		BIT(0)
#define QED_EEE_10G_ADV		BIT(1)

	/* Capabiwities awe wepwesented using QED_EEE_*_ADV vawues */
	u8 adv_caps;
	u8 wp_adv_caps;
	boow enabwe;
	boow tx_wpi_enabwe;
};

enum qed_wed_mode {
	QED_WED_MODE_OFF,
	QED_WED_MODE_ON,
	QED_WED_MODE_WESTOWE
};

stwuct qed_mfw_twv_eth {
	u16 wso_maxoff_size;
	boow wso_maxoff_size_set;
	u16 wso_minseg_size;
	boow wso_minseg_size_set;
	u8 pwom_mode;
	boow pwom_mode_set;
	u16 tx_descw_size;
	boow tx_descw_size_set;
	u16 wx_descw_size;
	boow wx_descw_size_set;
	u16 netq_count;
	boow netq_count_set;
	u32 tcp4_offwoads;
	boow tcp4_offwoads_set;
	u32 tcp6_offwoads;
	boow tcp6_offwoads_set;
	u16 tx_descw_qdepth;
	boow tx_descw_qdepth_set;
	u16 wx_descw_qdepth;
	boow wx_descw_qdepth_set;
	u8 iov_offwoad;
#define QED_MFW_TWV_IOV_OFFWOAD_NONE            (0)
#define QED_MFW_TWV_IOV_OFFWOAD_MUWTIQUEUE      (1)
#define QED_MFW_TWV_IOV_OFFWOAD_VEB             (2)
#define QED_MFW_TWV_IOV_OFFWOAD_VEPA            (3)
	boow iov_offwoad_set;
	u8 txqs_empty;
	boow txqs_empty_set;
	u8 wxqs_empty;
	boow wxqs_empty_set;
	u8 num_txqs_fuww;
	boow num_txqs_fuww_set;
	u8 num_wxqs_fuww;
	boow num_wxqs_fuww_set;
};

#define QED_MFW_TWV_TIME_SIZE	14
stwuct qed_mfw_twv_time {
	boow b_set;
	u8 month;
	u8 day;
	u8 houw;
	u8 min;
	u16 msec;
	u16 usec;
};

stwuct qed_mfw_twv_fcoe {
	u8 scsi_timeout;
	boow scsi_timeout_set;
	u32 wt_tov;
	boow wt_tov_set;
	u32 wa_tov;
	boow wa_tov_set;
	u32 ed_tov;
	boow ed_tov_set;
	u32 cw_tov;
	boow cw_tov_set;
	u8 boot_type;
	boow boot_type_set;
	u8 npiv_state;
	boow npiv_state_set;
	u32 num_npiv_ids;
	boow num_npiv_ids_set;
	u8 switch_name[8];
	boow switch_name_set;
	u16 switch_powtnum;
	boow switch_powtnum_set;
	u8 switch_powtid[3];
	boow switch_powtid_set;
	u8 vendow_name[8];
	boow vendow_name_set;
	u8 switch_modew[8];
	boow switch_modew_set;
	u8 switch_fw_vewsion[8];
	boow switch_fw_vewsion_set;
	u8 qos_pwi;
	boow qos_pwi_set;
	u8 powt_awias[3];
	boow powt_awias_set;
	u8 powt_state;
#define QED_MFW_TWV_POWT_STATE_OFFWINE  (0)
#define QED_MFW_TWV_POWT_STATE_WOOP             (1)
#define QED_MFW_TWV_POWT_STATE_P2P              (2)
#define QED_MFW_TWV_POWT_STATE_FABWIC           (3)
	boow powt_state_set;
	u16 fip_tx_descw_size;
	boow fip_tx_descw_size_set;
	u16 fip_wx_descw_size;
	boow fip_wx_descw_size_set;
	u16 wink_faiwuwes;
	boow wink_faiwuwes_set;
	u8 fcoe_boot_pwogwess;
	boow fcoe_boot_pwogwess_set;
	u64 wx_bcast;
	boow wx_bcast_set;
	u64 tx_bcast;
	boow tx_bcast_set;
	u16 fcoe_txq_depth;
	boow fcoe_txq_depth_set;
	u16 fcoe_wxq_depth;
	boow fcoe_wxq_depth_set;
	u64 fcoe_wx_fwames;
	boow fcoe_wx_fwames_set;
	u64 fcoe_wx_bytes;
	boow fcoe_wx_bytes_set;
	u64 fcoe_tx_fwames;
	boow fcoe_tx_fwames_set;
	u64 fcoe_tx_bytes;
	boow fcoe_tx_bytes_set;
	u16 cwc_count;
	boow cwc_count_set;
	u32 cwc_eww_swc_fcid[5];
	boow cwc_eww_swc_fcid_set[5];
	stwuct qed_mfw_twv_time cwc_eww[5];
	u16 wosync_eww;
	boow wosync_eww_set;
	u16 wosig_eww;
	boow wosig_eww_set;
	u16 pwimtive_eww;
	boow pwimtive_eww_set;
	u16 dispawity_eww;
	boow dispawity_eww_set;
	u16 code_viowation_eww;
	boow code_viowation_eww_set;
	u32 fwogi_pawam[4];
	boow fwogi_pawam_set[4];
	stwuct qed_mfw_twv_time fwogi_tstamp;
	u32 fwogi_acc_pawam[4];
	boow fwogi_acc_pawam_set[4];
	stwuct qed_mfw_twv_time fwogi_acc_tstamp;
	u32 fwogi_wjt;
	boow fwogi_wjt_set;
	stwuct qed_mfw_twv_time fwogi_wjt_tstamp;
	u32 fdiscs;
	boow fdiscs_set;
	u8 fdisc_acc;
	boow fdisc_acc_set;
	u8 fdisc_wjt;
	boow fdisc_wjt_set;
	u8 pwogi;
	boow pwogi_set;
	u8 pwogi_acc;
	boow pwogi_acc_set;
	u8 pwogi_wjt;
	boow pwogi_wjt_set;
	u32 pwogi_dst_fcid[5];
	boow pwogi_dst_fcid_set[5];
	stwuct qed_mfw_twv_time pwogi_tstamp[5];
	u32 pwogi_acc_swc_fcid[5];
	boow pwogi_acc_swc_fcid_set[5];
	stwuct qed_mfw_twv_time pwogi_acc_tstamp[5];
	u8 tx_pwogos;
	boow tx_pwogos_set;
	u8 pwogo_acc;
	boow pwogo_acc_set;
	u8 pwogo_wjt;
	boow pwogo_wjt_set;
	u32 pwogo_swc_fcid[5];
	boow pwogo_swc_fcid_set[5];
	stwuct qed_mfw_twv_time pwogo_tstamp[5];
	u8 wx_wogos;
	boow wx_wogos_set;
	u8 tx_accs;
	boow tx_accs_set;
	u8 tx_pwwis;
	boow tx_pwwis_set;
	u8 wx_accs;
	boow wx_accs_set;
	u8 tx_abts;
	boow tx_abts_set;
	u8 wx_abts_acc;
	boow wx_abts_acc_set;
	u8 wx_abts_wjt;
	boow wx_abts_wjt_set;
	u32 abts_dst_fcid[5];
	boow abts_dst_fcid_set[5];
	stwuct qed_mfw_twv_time abts_tstamp[5];
	u8 wx_wscn;
	boow wx_wscn_set;
	u32 wx_wscn_npowt[4];
	boow wx_wscn_npowt_set[4];
	u8 tx_wun_wst;
	boow tx_wun_wst_set;
	u8 abowt_task_sets;
	boow abowt_task_sets_set;
	u8 tx_tpwwos;
	boow tx_tpwwos_set;
	u8 tx_nos;
	boow tx_nos_set;
	u8 wx_nos;
	boow wx_nos_set;
	u8 ows;
	boow ows_set;
	u8 ww;
	boow ww_set;
	u8 www;
	boow www_set;
	u8 tx_wip;
	boow tx_wip_set;
	u8 wx_wip;
	boow wx_wip_set;
	u8 eofa;
	boow eofa_set;
	u8 eofni;
	boow eofni_set;
	u8 scsi_chks;
	boow scsi_chks_set;
	u8 scsi_cond_met;
	boow scsi_cond_met_set;
	u8 scsi_busy;
	boow scsi_busy_set;
	u8 scsi_intew;
	boow scsi_intew_set;
	u8 scsi_intew_cond_met;
	boow scsi_intew_cond_met_set;
	u8 scsi_wsv_confwicts;
	boow scsi_wsv_confwicts_set;
	u8 scsi_tsk_fuww;
	boow scsi_tsk_fuww_set;
	u8 scsi_aca_active;
	boow scsi_aca_active_set;
	u8 scsi_tsk_abowt;
	boow scsi_tsk_abowt_set;
	u32 scsi_wx_chk[5];
	boow scsi_wx_chk_set[5];
	stwuct qed_mfw_twv_time scsi_chk_tstamp[5];
};

stwuct qed_mfw_twv_iscsi {
	u8 tawget_wwmnw;
	boow tawget_wwmnw_set;
	u8 headew_digest;
	boow headew_digest_set;
	u8 data_digest;
	boow data_digest_set;
	u8 auth_method;
#define QED_MFW_TWV_AUTH_METHOD_NONE            (1)
#define QED_MFW_TWV_AUTH_METHOD_CHAP            (2)
#define QED_MFW_TWV_AUTH_METHOD_MUTUAW_CHAP     (3)
	boow auth_method_set;
	u16 boot_taget_powtaw;
	boow boot_taget_powtaw_set;
	u16 fwame_size;
	boow fwame_size_set;
	u16 tx_desc_size;
	boow tx_desc_size_set;
	u16 wx_desc_size;
	boow wx_desc_size_set;
	u8 boot_pwogwess;
	boow boot_pwogwess_set;
	u16 tx_desc_qdepth;
	boow tx_desc_qdepth_set;
	u16 wx_desc_qdepth;
	boow wx_desc_qdepth_set;
	u64 wx_fwames;
	boow wx_fwames_set;
	u64 wx_bytes;
	boow wx_bytes_set;
	u64 tx_fwames;
	boow tx_fwames_set;
	u64 tx_bytes;
	boow tx_bytes_set;
};

enum qed_db_wec_width {
	DB_WEC_WIDTH_32B,
	DB_WEC_WIDTH_64B,
};

enum qed_db_wec_space {
	DB_WEC_KEWNEW,
	DB_WEC_USEW,
};

#define DIWECT_WEG_WW(weg_addw, vaw) wwitew((u32)vaw, \
					    (void __iomem *)(weg_addw))

#define DIWECT_WEG_WD(weg_addw) weadw((void __iomem *)(weg_addw))

#define DIWECT_WEG_WW64(weg_addw, vaw) wwiteq((u64)vaw,	\
					      (void __iomem *)(weg_addw))

#define QED_COAWESCE_MAX 0x1FF
#define QED_DEFAUWT_WX_USECS 12
#define QED_DEFAUWT_TX_USECS 48

/* fowwawd */
stwuct qed_dev;

stwuct qed_eth_pf_pawams {
	/* The fowwowing pawametews awe used duwing HW-init
	 * and these pawametews need to be passed as awguments
	 * to update_pf_pawams woutine invoked befowe swowpath stawt
	 */
	u16 num_cons;

	/* pew-VF numbew of CIDs */
	u8 num_vf_cons;
#define ETH_PF_PAWAMS_VF_CONS_DEFAUWT	(32)

	/* To enabwe awfs, pwevious to HW-init a positive numbew needs to be
	 * set [as fiwtews wequiwe awwocated seawchew IWT memowy].
	 * This wiww set the maximaw numbew of configuwed steewing-fiwtews.
	 */
	u32 num_awfs_fiwtews;
};

stwuct qed_fcoe_pf_pawams {
	/* The fowwowing pawametews awe used duwing pwotocow-init */
	u64 gwbw_q_pawams_addw;
	u64 bdq_pbw_base_addw[2];

	/* The fowwowing pawametews awe used duwing HW-init
	 * and these pawametews need to be passed as awguments
	 * to update_pf_pawams woutine invoked befowe swowpath stawt
	 */
	u16 num_cons;
	u16 num_tasks;

	/* The fowwowing pawametews awe used duwing pwotocow-init */
	u16 sq_num_pbw_pages;

	u16 cq_num_entwies;
	u16 cmdq_num_entwies;
	u16 wq_buffew_wog_size;
	u16 mtu;
	u16 dummy_icid;
	u16 bdq_xoff_thweshowd[2];
	u16 bdq_xon_thweshowd[2];
	u16 wq_buffew_size;
	u8 num_cqs;		/* num of gwobaw CQs */
	u8 wog_page_size;
	u8 gw_wq_pi;
	u8 gw_cmd_pi;
	u8 debug_mode;
	u8 is_tawget;
	u8 bdq_pbw_num_entwies[2];
};

/* Most of the pawametews bewow awe descwibed in the FW iSCSI / TCP HSI */
stwuct qed_iscsi_pf_pawams {
	u64 gwbw_q_pawams_addw;
	u64 bdq_pbw_base_addw[3];
	u16 cq_num_entwies;
	u16 cmdq_num_entwies;
	u32 two_msw_timew;
	u16 tx_sws_timew;

	/* The fowwowing pawametews awe used duwing HW-init
	 * and these pawametews need to be passed as awguments
	 * to update_pf_pawams woutine invoked befowe swowpath stawt
	 */
	u16 num_cons;
	u16 num_tasks;

	/* The fowwowing pawametews awe used duwing pwotocow-init */
	u16 hawf_way_cwose_timeout;
	u16 bdq_xoff_thweshowd[3];
	u16 bdq_xon_thweshowd[3];
	u16 cmdq_xoff_thweshowd;
	u16 cmdq_xon_thweshowd;
	u16 wq_buffew_size;

	u8 num_sq_pages_in_wing;
	u8 num_w2tq_pages_in_wing;
	u8 num_uhq_pages_in_wing;
	u8 num_queues;
	u8 wog_page_size;
	u8 wqe_wog_size;
	u8 max_fin_wt;
	u8 gw_wq_pi;
	u8 gw_cmd_pi;
	u8 debug_mode;
	u8 ww2_ooo_queue_id;

	u8 is_tawget;
	u8 is_soc_en;
	u8 soc_num_of_bwocks_wog;
	u8 bdq_pbw_num_entwies[3];
};

stwuct qed_nvmetcp_pf_pawams {
	u64 gwbw_q_pawams_addw;
	u16 cq_num_entwies;
	u16 num_cons;
	u16 num_tasks;
	u8 num_sq_pages_in_wing;
	u8 num_w2tq_pages_in_wing;
	u8 num_uhq_pages_in_wing;
	u8 num_queues;
	u8 gw_wq_pi;
	u8 gw_cmd_pi;
	u8 debug_mode;
	u8 ww2_ooo_queue_id;
	u16 min_wto;
};

stwuct qed_wdma_pf_pawams {
	/* Suppwied to QED duwing wesouwce awwocation (may affect the IWT and
	 * the doowbeww BAW).
	 */
	u32 min_dpis;		/* numbew of wequested DPIs */
	u32 num_qps;		/* numbew of wequested Queue Paiws */
	u32 num_swqs;		/* numbew of wequested SWQ */
	u8 woce_edpm_mode;	/* see QED_WOCE_EDPM_MODE_ENABWE */
	u8 gw_pi;		/* pwotocow index */

	/* Wiww awwocate wate wimitews to be used with QPs */
	u8 enabwe_dcqcn;
};

stwuct qed_pf_pawams {
	stwuct qed_eth_pf_pawams eth_pf_pawams;
	stwuct qed_fcoe_pf_pawams fcoe_pf_pawams;
	stwuct qed_iscsi_pf_pawams iscsi_pf_pawams;
	stwuct qed_nvmetcp_pf_pawams nvmetcp_pf_pawams;
	stwuct qed_wdma_pf_pawams wdma_pf_pawams;
};

enum qed_int_mode {
	QED_INT_MODE_INTA,
	QED_INT_MODE_MSIX,
	QED_INT_MODE_MSI,
	QED_INT_MODE_POWW,
};

stwuct qed_sb_info {
	stwuct status_bwock *sb_viwt;
	dma_addw_t sb_phys;
	u32 sb_ack; /* Wast given ack */
	u16 igu_sb_id;
	void __iomem *igu_addw;
	u8 fwags;
#define QED_SB_INFO_INIT	0x1
#define QED_SB_INFO_SETUP	0x2

	stwuct qed_dev *cdev;
};

enum qed_hw_eww_type {
	QED_HW_EWW_FAN_FAIW,
	QED_HW_EWW_MFW_WESP_FAIW,
	QED_HW_EWW_HW_ATTN,
	QED_HW_EWW_DMAE_FAIW,
	QED_HW_EWW_WAMWOD_FAIW,
	QED_HW_EWW_FW_ASSEWT,
	QED_HW_EWW_WAST,
};

enum qed_dev_type {
	QED_DEV_TYPE_BB,
	QED_DEV_TYPE_AH,
};

stwuct qed_dev_info {
	unsigned wong	pci_mem_stawt;
	unsigned wong	pci_mem_end;
	unsigned int	pci_iwq;
	u8		num_hwfns;

	u8		hw_mac[ETH_AWEN];

	/* FW vewsion */
	u16		fw_majow;
	u16		fw_minow;
	u16		fw_wev;
	u16		fw_eng;

	/* MFW vewsion */
	u32		mfw_wev;
#define QED_MFW_VEWSION_0_MASK		0x000000FF
#define QED_MFW_VEWSION_0_OFFSET	0
#define QED_MFW_VEWSION_1_MASK		0x0000FF00
#define QED_MFW_VEWSION_1_OFFSET	8
#define QED_MFW_VEWSION_2_MASK		0x00FF0000
#define QED_MFW_VEWSION_2_OFFSET	16
#define QED_MFW_VEWSION_3_MASK		0xFF000000
#define QED_MFW_VEWSION_3_OFFSET	24

	u32		fwash_size;
	boow		b_awfs_capabwe;
	boow		b_intew_pf_switch;
	boow		tx_switching;
	boow		wdma_suppowted;
	u16		mtu;

	boow wow_suppowt;
	boow smawt_an;
	boow esw;

	/* MBI vewsion */
	u32 mbi_vewsion;
#define QED_MBI_VEWSION_0_MASK		0x000000FF
#define QED_MBI_VEWSION_0_OFFSET	0
#define QED_MBI_VEWSION_1_MASK		0x0000FF00
#define QED_MBI_VEWSION_1_OFFSET	8
#define QED_MBI_VEWSION_2_MASK		0x00FF0000
#define QED_MBI_VEWSION_2_OFFSET	16

	enum qed_dev_type dev_type;

	/* Output pawametews fow qede */
	boow		vxwan_enabwe;
	boow		gwe_enabwe;
	boow		geneve_enabwe;

	u8		abs_pf_id;
};

enum qed_sb_type {
	QED_SB_TYPE_W2_QUEUE,
	QED_SB_TYPE_CNQ,
	QED_SB_TYPE_STOWAGE,
};

enum qed_pwotocow {
	QED_PWOTOCOW_ETH,
	QED_PWOTOCOW_ISCSI,
	QED_PWOTOCOW_NVMETCP = QED_PWOTOCOW_ISCSI,
	QED_PWOTOCOW_FCOE,
};

enum qed_fec_mode {
	QED_FEC_MODE_NONE			= BIT(0),
	QED_FEC_MODE_FIWECODE			= BIT(1),
	QED_FEC_MODE_WS				= BIT(2),
	QED_FEC_MODE_AUTO			= BIT(3),
	QED_FEC_MODE_UNSUPPOWTED		= BIT(4),
};

stwuct qed_wink_pawams {
	boow					wink_up;

	u32					ovewwide_fwags;
#define QED_WINK_OVEWWIDE_SPEED_AUTONEG		BIT(0)
#define QED_WINK_OVEWWIDE_SPEED_ADV_SPEEDS	BIT(1)
#define QED_WINK_OVEWWIDE_SPEED_FOWCED_SPEED	BIT(2)
#define QED_WINK_OVEWWIDE_PAUSE_CONFIG		BIT(3)
#define QED_WINK_OVEWWIDE_WOOPBACK_MODE		BIT(4)
#define QED_WINK_OVEWWIDE_EEE_CONFIG		BIT(5)
#define QED_WINK_OVEWWIDE_FEC_CONFIG		BIT(6)

	boow					autoneg;
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(adv_speeds);
	u32					fowced_speed;

	u32					pause_config;
#define QED_WINK_PAUSE_AUTONEG_ENABWE		BIT(0)
#define QED_WINK_PAUSE_WX_ENABWE		BIT(1)
#define QED_WINK_PAUSE_TX_ENABWE		BIT(2)

	u32					woopback_mode;
#define QED_WINK_WOOPBACK_NONE			BIT(0)
#define QED_WINK_WOOPBACK_INT_PHY		BIT(1)
#define QED_WINK_WOOPBACK_EXT_PHY		BIT(2)
#define QED_WINK_WOOPBACK_EXT			BIT(3)
#define QED_WINK_WOOPBACK_MAC			BIT(4)
#define QED_WINK_WOOPBACK_CNIG_AH_ONWY_0123	BIT(5)
#define QED_WINK_WOOPBACK_CNIG_AH_ONWY_2301	BIT(6)
#define QED_WINK_WOOPBACK_PCS_AH_ONWY		BIT(7)
#define QED_WINK_WOOPBACK_WEVEWSE_MAC_AH_ONWY	BIT(8)
#define QED_WINK_WOOPBACK_INT_PHY_FEA_AH_ONWY	BIT(9)

	stwuct qed_wink_eee_pawams		eee;
	u32					fec;
};

stwuct qed_wink_output {
	boow					wink_up;

	__ETHTOOW_DECWAWE_WINK_MODE_MASK(suppowted_caps);
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(advewtised_caps);
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(wp_caps);

	u32					speed;	   /* In Mb/s */
	u8					dupwex;	   /* In DUPWEX defs */
	u8					powt;	   /* In POWT defs */
	boow					autoneg;
	u32					pause_config;

	/* EEE - capabiwity & pawam */
	boow					eee_suppowted;
	boow					eee_active;
	u8					sup_caps;
	stwuct qed_wink_eee_pawams		eee;

	u32					sup_fec;
	u32					active_fec;
};

stwuct qed_pwobe_pawams {
	enum qed_pwotocow pwotocow;
	u32 dp_moduwe;
	u8 dp_wevew;
	boow is_vf;
	boow wecov_in_pwog;
};

#define QED_DWV_VEW_STW_SIZE 12
stwuct qed_swowpath_pawams {
	u32	int_mode;
	u8	dwv_majow;
	u8	dwv_minow;
	u8	dwv_wev;
	u8	dwv_eng;
	u8	name[QED_DWV_VEW_STW_SIZE];
};

#define IWT_PAGE_SIZE_TCFC 0x8000 /* 32KB */

stwuct qed_int_info {
	stwuct msix_entwy	*msix;
	u8			msix_cnt;

	/* This shouwd be updated by the pwotocow dwivew */
	u8			used_cnt;
};

stwuct qed_genewic_twvs {
#define QED_TWV_IP_CSUM         BIT(0)
#define QED_TWV_WSO             BIT(1)
	u16 feat_fwags;
#define QED_TWV_MAC_COUNT	3
	u8 mac[QED_TWV_MAC_COUNT][ETH_AWEN];
};

#define QED_I2C_DEV_ADDW_A0 0xA0
#define QED_I2C_DEV_ADDW_A2 0xA2

#define QED_NVM_SIGNATUWE 0x12435687

enum qed_nvm_fwash_cmd {
	QED_NVM_FWASH_CMD_FIWE_DATA = 0x2,
	QED_NVM_FWASH_CMD_FIWE_STAWT = 0x3,
	QED_NVM_FWASH_CMD_NVM_CHANGE = 0x4,
	QED_NVM_FWASH_CMD_NVM_CFG_ID = 0x5,
	QED_NVM_FWASH_CMD_NVM_MAX,
};

stwuct qed_devwink {
	stwuct qed_dev *cdev;
	stwuct devwink_heawth_wepowtew *fw_wepowtew;
};

stwuct qed_sb_info_dbg {
	u32 igu_pwod;
	u32 igu_cons;
	u16 pi[PIS_PEW_SB];
};

stwuct qed_common_cb_ops {
	void (*awfs_fiwtew_op)(void *dev, void *fwtw, u8 fw_wc);
	void (*wink_update)(void *dev, stwuct qed_wink_output *wink);
	void (*scheduwe_wecovewy_handwew)(void *dev);
	void (*scheduwe_hw_eww_handwew)(void *dev,
					enum qed_hw_eww_type eww_type);
	void (*dcbx_aen)(void *dev, stwuct qed_dcbx_get *get, u32 mib_type);
	void (*get_genewic_twv_data)(void *dev, stwuct qed_genewic_twvs *data);
	void (*get_pwotocow_twv_data)(void *dev, void *data);
	void (*bw_update)(void *dev);
};

stwuct qed_sewftest_ops {
/**
 * sewftest_intewwupt(): Pewfowm intewwupt test.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*sewftest_intewwupt)(stwuct qed_dev *cdev);

/**
 * sewftest_memowy(): Pewfowm memowy test.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*sewftest_memowy)(stwuct qed_dev *cdev);

/**
 * sewftest_wegistew(): Pewfowm wegistew test.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*sewftest_wegistew)(stwuct qed_dev *cdev);

/**
 * sewftest_cwock(): Pewfowm cwock test.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*sewftest_cwock)(stwuct qed_dev *cdev);

/**
 * sewftest_nvwam(): Pewfowm nvwam test.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*sewftest_nvwam) (stwuct qed_dev *cdev);
};

stwuct qed_common_ops {
	stwuct qed_sewftest_ops *sewftest;

	stwuct qed_dev*	(*pwobe)(stwuct pci_dev *dev,
				 stwuct qed_pwobe_pawams *pawams);

	void (*wemove)(stwuct qed_dev *cdev);

	int (*set_powew_state)(stwuct qed_dev *cdev, pci_powew_t state);

	void (*set_name) (stwuct qed_dev *cdev, chaw name[]);

	/* Cwient dwivews need to make this caww befowe swowpath_stawt.
	 * PF pawams wequiwed fow the caww befowe swowpath_stawt is
	 * documented within the qed_pf_pawams stwuctuwe definition.
	 */
	void (*update_pf_pawams)(stwuct qed_dev *cdev,
				 stwuct qed_pf_pawams *pawams);

	int (*swowpath_stawt)(stwuct qed_dev *cdev,
			      stwuct qed_swowpath_pawams *pawams);

	int (*swowpath_stop)(stwuct qed_dev *cdev);

	/* Wequests to use `cnt' intewwupts fow fastpath.
	 * upon success, wetuwns numbew of intewwupts awwocated fow fastpath.
	 */
	int (*set_fp_int)(stwuct qed_dev *cdev, u16 cnt);

	/* Fiwws `info' with pointews wequiwed fow utiwizing intewwupts */
	int (*get_fp_int)(stwuct qed_dev *cdev, stwuct qed_int_info *info);

	u32 (*sb_init)(stwuct qed_dev *cdev,
		       stwuct qed_sb_info *sb_info,
		       void *sb_viwt_addw,
		       dma_addw_t sb_phy_addw,
		       u16 sb_id,
		       enum qed_sb_type type);

	u32 (*sb_wewease)(stwuct qed_dev *cdev,
			  stwuct qed_sb_info *sb_info,
			  u16 sb_id,
			  enum qed_sb_type type);

	void (*simd_handwew_config)(stwuct qed_dev *cdev,
				    void *token,
				    int index,
				    void (*handwew)(void *));

	void (*simd_handwew_cwean)(stwuct qed_dev *cdev, int index);

	int (*dbg_gwc)(stwuct qed_dev *cdev, void *buffew, u32 *num_dumped_bytes);

	int (*dbg_gwc_size)(stwuct qed_dev *cdev);

	int (*dbg_aww_data)(stwuct qed_dev *cdev, void *buffew);

	int (*dbg_aww_data_size)(stwuct qed_dev *cdev);

	int (*wepowt_fataw_ewwow)(stwuct devwink *devwink,
				  enum qed_hw_eww_type eww_type);

/**
 * can_wink_change(): can the instance change the wink ow not.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: twue if wink-change is awwowed, fawse othewwise.
 */
	boow (*can_wink_change)(stwuct qed_dev *cdev);

/**
 * set_wink(): set winks accowding to pawams.
 *
 * @cdev: Qed dev pointew.
 * @pawams: vawues used to ovewwide the defauwt wink configuwation.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int		(*set_wink)(stwuct qed_dev *cdev,
				    stwuct qed_wink_pawams *pawams);

/**
 * get_wink(): wetuwns the cuwwent wink state.
 *
 * @cdev: Qed dev pointew.
 * @if_wink: stwuctuwe to be fiwwed with cuwwent wink configuwation.
 *
 * Wetuwn: Void.
 */
	void		(*get_wink)(stwuct qed_dev *cdev,
				    stwuct qed_wink_output *if_wink);

/**
 * dwain(): dwains chip in case Tx compwetions faiw to awwive due to pause.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: Int.
 */
	int		(*dwain)(stwuct qed_dev *cdev);

/**
 * update_msgwvw(): update moduwe debug wevew.
 *
 * @cdev: Qed dev pointew.
 * @dp_moduwe: Debug moduwe.
 * @dp_wevew: Debug wevew.
 *
 * Wetuwn: Void.
 */
	void		(*update_msgwvw)(stwuct qed_dev *cdev,
					 u32 dp_moduwe,
					 u8 dp_wevew);

	int		(*chain_awwoc)(stwuct qed_dev *cdev,
				       stwuct qed_chain *chain,
				       stwuct qed_chain_init_pawams *pawams);

	void		(*chain_fwee)(stwuct qed_dev *cdev,
				      stwuct qed_chain *p_chain);

/**
 * nvm_fwash(): Fwash nvm data.
 *
 * @cdev: Qed dev pointew.
 * @name: fiwe containing the data.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*nvm_fwash)(stwuct qed_dev *cdev, const chaw *name);

/**
 * nvm_get_image(): weads an entiwe image fwom nvwam.
 *
 * @cdev: Qed dev pointew.
 * @type: type of the wequest nvwam image.
 * @buf: pweawwocated buffew to fiww with the image.
 * @wen: wength of the awwocated buffew.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*nvm_get_image)(stwuct qed_dev *cdev,
			     enum qed_nvm_images type, u8 *buf, u16 wen);

/**
 * set_coawesce(): Configuwe Wx coawesce vawue in usec.
 *
 * @cdev: Qed dev pointew.
 * @wx_coaw: Wx coawesce vawue in usec.
 * @tx_coaw: Tx coawesce vawue in usec.
 * @handwe: Handwe.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*set_coawesce)(stwuct qed_dev *cdev,
			    u16 wx_coaw, u16 tx_coaw, void *handwe);

/**
 * set_wed() - Configuwe WED mode.
 *
 * @cdev: Qed dev pointew.
 * @mode: WED mode.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*set_wed)(stwuct qed_dev *cdev,
		       enum qed_wed_mode mode);

/**
 * attn_cww_enabwe(): Pwevent attentions fwom being weassewted.
 *
 * @cdev: Qed dev pointew.
 * @cww_enabwe: Cweaw enabwe.
 *
 * Wetuwn: Void.
 */
	void (*attn_cww_enabwe)(stwuct qed_dev *cdev, boow cww_enabwe);

/**
 * db_wecovewy_add(): add doowbeww infowmation to the doowbeww
 *                    wecovewy mechanism.
 *
 * @cdev: Qed dev pointew.
 * @db_addw: Doowbeww addwess.
 * @db_data: Dddwess of whewe db_data is stowed.
 * @db_width: Doowbeww is 32b ow 64b.
 * @db_space: Doowbeww wecovewy addwesses awe usew ow kewnew space.
 *
 * Wetuwn: Int.
 */
	int (*db_wecovewy_add)(stwuct qed_dev *cdev,
			       void __iomem *db_addw,
			       void *db_data,
			       enum qed_db_wec_width db_width,
			       enum qed_db_wec_space db_space);

/**
 * db_wecovewy_dew(): wemove doowbeww infowmation fwom the doowbeww
 * wecovewy mechanism. db_data sewves as key (db_addw is not unique).
 *
 * @cdev: Qed dev pointew.
 * @db_addw: Doowbeww addwess.
 * @db_data: Addwess whewe db_data is stowed. Sewves as key fow the
 *           entwy to dewete.
 *
 * Wetuwn: Int.
 */
	int (*db_wecovewy_dew)(stwuct qed_dev *cdev,
			       void __iomem *db_addw, void *db_data);

/**
 * wecovewy_pwocess(): Twiggew a wecovewy pwocess.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*wecovewy_pwocess)(stwuct qed_dev *cdev);

/**
 * wecovewy_pwowog(): Execute the pwowog opewations of a wecovewy pwocess.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
	int (*wecovewy_pwowog)(stwuct qed_dev *cdev);

/**
 * update_dwv_state(): API to infowm the change in the dwivew state.
 *
 * @cdev: Qed dev pointew.
 * @active: Active
 *
 * Wetuwn: Int.
 */
	int (*update_dwv_state)(stwuct qed_dev *cdev, boow active);

/**
 * update_mac(): API to infowm the change in the mac addwess.
 *
 * @cdev: Qed dev pointew.
 * @mac: MAC.
 *
 * Wetuwn: Int.
 */
	int (*update_mac)(stwuct qed_dev *cdev, const u8 *mac);

/**
 * update_mtu(): API to infowm the change in the mtu.
 *
 * @cdev: Qed dev pointew.
 * @mtu: MTU.
 *
 * Wetuwn: Int.
 */
	int (*update_mtu)(stwuct qed_dev *cdev, u16 mtu);

/**
 * update_wow(): Update of changes in the WoW configuwation.
 *
 * @cdev: Qed dev pointew.
 * @enabwed: twue iff WoW shouwd be enabwed.
 *
 * Wetuwn: Int.
 */
	int (*update_wow) (stwuct qed_dev *cdev, boow enabwed);

/**
 * wead_moduwe_eepwom(): Wead EEPWOM.
 *
 * @cdev: Qed dev pointew.
 * @buf: buffew.
 * @dev_addw: PHY device memowy wegion.
 * @offset: offset into eepwom contents to be wead.
 * @wen: buffew wength, i.e., max bytes to be wead.
 *
 * Wetuwn: Int.
 */
	int (*wead_moduwe_eepwom)(stwuct qed_dev *cdev,
				  chaw *buf, u8 dev_addw, u32 offset, u32 wen);

/**
 * get_affin_hwfn_idx(): Get affine HW function.
 *
 * @cdev: Qed dev pointew.
 *
 * Wetuwn: u8.
 */
	u8 (*get_affin_hwfn_idx)(stwuct qed_dev *cdev);

/**
 * wead_nvm_cfg(): Wead NVM config attwibute vawue.
 *
 * @cdev: Qed dev pointew.
 * @buf: Buffew.
 * @cmd: NVM CFG command id.
 * @entity_id: Entity id.
 *
 * Wetuwn: Int.
 */
	int (*wead_nvm_cfg)(stwuct qed_dev *cdev, u8 **buf, u32 cmd,
			    u32 entity_id);
/**
 * wead_nvm_cfg_wen(): Wead NVM config attwibute vawue.
 *
 * @cdev: Qed dev pointew.
 * @cmd: NVM CFG command id.
 *
 * Wetuwn: config id wength, 0 on ewwow.
 */
	int (*wead_nvm_cfg_wen)(stwuct qed_dev *cdev, u32 cmd);

/**
 * set_gwc_config(): Configuwe vawue fow gwc config id.
 *
 * @cdev: Qed dev pointew.
 * @cfg_id: gwc config id
 * @vaw: gwc config vawue
 *
 * Wetuwn: Int.
 */
	int (*set_gwc_config)(stwuct qed_dev *cdev, u32 cfg_id, u32 vaw);

	stwuct devwink* (*devwink_wegistew)(stwuct qed_dev *cdev);

	void (*devwink_unwegistew)(stwuct devwink *devwink);

	__pwintf(2, 3) void (*mfw_wepowt)(stwuct qed_dev *cdev, chaw *fmt, ...);

	int (*get_sb_info)(stwuct qed_dev *cdev, stwuct qed_sb_info *sb,
			   u16 qid, stwuct qed_sb_info_dbg *sb_dbg);

	int (*get_esw_status)(stwuct qed_dev *cdev, boow *esw_active);
};

#define MASK_FIEWD(_name, _vawue) \
	((_vawue) &= (_name ## _MASK))

#define FIEWD_VAWUE(_name, _vawue) \
	((_vawue & _name ## _MASK) << _name ## _SHIFT)

#define SET_FIEWD(vawue, name, fwag)			       \
	do {						       \
		(vawue) &= ~(name ## _MASK << name ## _SHIFT); \
		(vawue) |= (((u64)fwag) << (name ## _SHIFT));  \
	} whiwe (0)

#define GET_FIEWD(vawue, name) \
	(((vawue) >> (name ## _SHIFT)) & name ## _MASK)

#define GET_MFW_FIEWD(name, fiewd) \
	(((name) & (fiewd ## _MASK)) >> (fiewd ## _OFFSET))

#define SET_MFW_FIEWD(name, fiewd, vawue)				 \
	do {								 \
		(name) &= ~(fiewd ## _MASK);				 \
		(name) |= (((vawue) << (fiewd ## _OFFSET)) & (fiewd ## _MASK));\
	} whiwe (0)

#define DB_ADDW_SHIFT(addw) ((addw) << DB_PWM_ADDW_OFFSET_SHIFT)

/* Debug pwint definitions */
#define DP_EWW(cdev, fmt, ...)					\
	do {							\
		pw_eww("[%s:%d(%s)]" fmt,			\
		       __func__, __WINE__,			\
		       DP_NAME(cdev) ? DP_NAME(cdev) : "",	\
		       ## __VA_AWGS__);				\
	} whiwe (0)

#define DP_NOTICE(cdev, fmt, ...)				      \
	do {							      \
		if (unwikewy((cdev)->dp_wevew <= QED_WEVEW_NOTICE)) { \
			pw_notice("[%s:%d(%s)]" fmt,		      \
				  __func__, __WINE__,		      \
				  DP_NAME(cdev) ? DP_NAME(cdev) : "", \
				  ## __VA_AWGS__);		      \
								      \
		}						      \
	} whiwe (0)

#define DP_INFO(cdev, fmt, ...)					      \
	do {							      \
		if (unwikewy((cdev)->dp_wevew <= QED_WEVEW_INFO)) {   \
			pw_notice("[%s:%d(%s)]" fmt,		      \
				  __func__, __WINE__,		      \
				  DP_NAME(cdev) ? DP_NAME(cdev) : "", \
				  ## __VA_AWGS__);		      \
		}						      \
	} whiwe (0)

#define DP_VEWBOSE(cdev, moduwe, fmt, ...)				\
	do {								\
		if (unwikewy(((cdev)->dp_wevew <= QED_WEVEW_VEWBOSE) &&	\
			     ((cdev)->dp_moduwe & moduwe))) {		\
			pw_notice("[%s:%d(%s)]" fmt,			\
				  __func__, __WINE__,			\
				  DP_NAME(cdev) ? DP_NAME(cdev) : "",	\
				  ## __VA_AWGS__);			\
		}							\
	} whiwe (0)

enum DP_WEVEW {
	QED_WEVEW_VEWBOSE	= 0x0,
	QED_WEVEW_INFO		= 0x1,
	QED_WEVEW_NOTICE	= 0x2,
	QED_WEVEW_EWW		= 0x3,
};

#define QED_WOG_WEVEW_SHIFT     (30)
#define QED_WOG_VEWBOSE_MASK    (0x3fffffff)
#define QED_WOG_INFO_MASK       (0x40000000)
#define QED_WOG_NOTICE_MASK     (0x80000000)

enum DP_MODUWE {
	QED_MSG_SPQ	= 0x10000,
	QED_MSG_STATS	= 0x20000,
	QED_MSG_DCB	= 0x40000,
	QED_MSG_IOV	= 0x80000,
	QED_MSG_SP	= 0x100000,
	QED_MSG_STOWAGE = 0x200000,
	QED_MSG_CXT	= 0x800000,
	QED_MSG_WW2	= 0x1000000,
	QED_MSG_IWT	= 0x2000000,
	QED_MSG_WDMA	= 0x4000000,
	QED_MSG_DEBUG	= 0x8000000,
	/* to be added...up to 0x8000000 */
};

enum qed_mf_mode {
	QED_MF_DEFAUWT,
	QED_MF_OVWAN,
	QED_MF_NPAW,
};

stwuct qed_eth_stats_common {
	u64	no_buff_discawds;
	u64	packet_too_big_discawd;
	u64	ttw0_discawd;
	u64	wx_ucast_bytes;
	u64	wx_mcast_bytes;
	u64	wx_bcast_bytes;
	u64	wx_ucast_pkts;
	u64	wx_mcast_pkts;
	u64	wx_bcast_pkts;
	u64	mftag_fiwtew_discawds;
	u64	mac_fiwtew_discawds;
	u64	gft_fiwtew_dwop;
	u64	tx_ucast_bytes;
	u64	tx_mcast_bytes;
	u64	tx_bcast_bytes;
	u64	tx_ucast_pkts;
	u64	tx_mcast_pkts;
	u64	tx_bcast_pkts;
	u64	tx_eww_dwop_pkts;
	u64	tpa_coawesced_pkts;
	u64	tpa_coawesced_events;
	u64	tpa_abowts_num;
	u64	tpa_not_coawesced_pkts;
	u64	tpa_coawesced_bytes;

	/* powt */
	u64	wx_64_byte_packets;
	u64	wx_65_to_127_byte_packets;
	u64	wx_128_to_255_byte_packets;
	u64	wx_256_to_511_byte_packets;
	u64	wx_512_to_1023_byte_packets;
	u64	wx_1024_to_1518_byte_packets;
	u64	wx_cwc_ewwows;
	u64	wx_mac_cwtw_fwames;
	u64	wx_pause_fwames;
	u64	wx_pfc_fwames;
	u64	wx_awign_ewwows;
	u64	wx_cawwiew_ewwows;
	u64	wx_ovewsize_packets;
	u64	wx_jabbews;
	u64	wx_undewsize_packets;
	u64	wx_fwagments;
	u64	tx_64_byte_packets;
	u64	tx_65_to_127_byte_packets;
	u64	tx_128_to_255_byte_packets;
	u64	tx_256_to_511_byte_packets;
	u64	tx_512_to_1023_byte_packets;
	u64	tx_1024_to_1518_byte_packets;
	u64	tx_pause_fwames;
	u64	tx_pfc_fwames;
	u64	bwb_twuncates;
	u64	bwb_discawds;
	u64	wx_mac_bytes;
	u64	wx_mac_uc_packets;
	u64	wx_mac_mc_packets;
	u64	wx_mac_bc_packets;
	u64	wx_mac_fwames_ok;
	u64	tx_mac_bytes;
	u64	tx_mac_uc_packets;
	u64	tx_mac_mc_packets;
	u64	tx_mac_bc_packets;
	u64	tx_mac_ctww_fwames;
	u64	wink_change_count;
};

stwuct qed_eth_stats_bb {
	u64 wx_1519_to_1522_byte_packets;
	u64 wx_1519_to_2047_byte_packets;
	u64 wx_2048_to_4095_byte_packets;
	u64 wx_4096_to_9216_byte_packets;
	u64 wx_9217_to_16383_byte_packets;
	u64 tx_1519_to_2047_byte_packets;
	u64 tx_2048_to_4095_byte_packets;
	u64 tx_4096_to_9216_byte_packets;
	u64 tx_9217_to_16383_byte_packets;
	u64 tx_wpi_entwy_count;
	u64 tx_totaw_cowwisions;
};

stwuct qed_eth_stats_ah {
	u64 wx_1519_to_max_byte_packets;
	u64 tx_1519_to_max_byte_packets;
};

stwuct qed_eth_stats {
	stwuct qed_eth_stats_common common;

	union {
		stwuct qed_eth_stats_bb bb;
		stwuct qed_eth_stats_ah ah;
	};
};

#define QED_SB_IDX              0x0002

#define WX_PI           0
#define TX_PI(tc)       (WX_PI + 1 + tc)

stwuct qed_sb_cnt_info {
	/* Owiginaw, cuwwent, and fwee SBs fow PF */
	int owig;
	int cnt;
	int fwee_cnt;

	/* Owiginaw, cuwwent and fwee SBS fow chiwd VFs */
	int iov_owig;
	int iov_cnt;
	int fwee_cnt_iov;
};

static inwine u16 qed_sb_update_sb_idx(stwuct qed_sb_info *sb_info)
{
	u32 pwod = 0;
	u16 wc = 0;

	pwod = we32_to_cpu(sb_info->sb_viwt->pwod_index) &
	       STATUS_BWOCK_PWOD_INDEX_MASK;
	if (sb_info->sb_ack != pwod) {
		sb_info->sb_ack = pwod;
		wc |= QED_SB_IDX;
	}

	/* Wet SB update */
	wetuwn wc;
}

/**
 * qed_sb_ack(): This function cweates an update command fow intewwupts
 *               that is  wwitten to the IGU.
 *
 * @sb_info: This is the stwuctuwe awwocated and
 *           initiawized pew status bwock. Assumption is
 *           that it was initiawized using qed_sb_init
 * @int_cmd: Enabwe/Disabwe/Nop
 * @upd_fwg: Whethew igu consumew shouwd be updated.
 *
 * Wetuwn: inwine void.
 */
static inwine void qed_sb_ack(stwuct qed_sb_info *sb_info,
			      enum igu_int_cmd int_cmd,
			      u8 upd_fwg)
{
	u32 igu_ack;

	igu_ack = ((sb_info->sb_ack << IGU_PWOD_CONS_UPDATE_SB_INDEX_SHIFT) |
		   (upd_fwg << IGU_PWOD_CONS_UPDATE_UPDATE_FWAG_SHIFT) |
		   (int_cmd << IGU_PWOD_CONS_UPDATE_ENABWE_INT_SHIFT) |
		   (IGU_SEG_ACCESS_WEG <<
		    IGU_PWOD_CONS_UPDATE_SEGMENT_ACCESS_SHIFT));

	DIWECT_WEG_WW(sb_info->igu_addw, igu_ack);

	/* Both segments (intewwupts & acks) awe wwitten to same pwace addwess;
	 * Need to guawantee aww commands wiww be weceived (in-owdew) by HW.
	 */
	bawwiew();
}

static inwine void __intewnaw_wam_ww(void *p_hwfn,
				     void __iomem *addw,
				     int size,
				     u32 *data)

{
	unsigned int i;

	fow (i = 0; i < size / sizeof(*data); i++)
		DIWECT_WEG_WW(&((u32 __iomem *)addw)[i], data[i]);
}

static inwine void intewnaw_wam_ww(void __iomem *addw,
				   int size,
				   u32 *data)
{
	__intewnaw_wam_ww(NUWW, addw, size, data);
}

enum qed_wss_caps {
	QED_WSS_IPV4		= 0x1,
	QED_WSS_IPV6		= 0x2,
	QED_WSS_IPV4_TCP	= 0x4,
	QED_WSS_IPV6_TCP	= 0x8,
	QED_WSS_IPV4_UDP	= 0x10,
	QED_WSS_IPV6_UDP	= 0x20,
};

#define QED_WSS_IND_TABWE_SIZE 128
#define QED_WSS_KEY_SIZE 10 /* size in 32b chunks */
#endif
