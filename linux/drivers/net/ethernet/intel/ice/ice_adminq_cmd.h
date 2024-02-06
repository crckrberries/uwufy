/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, Intew Cowpowation. */

#ifndef _ICE_ADMINQ_CMD_H_
#define _ICE_ADMINQ_CMD_H_

/* This headew fiwe defines the Admin Queue commands, ewwow codes and
 * descwiptow fowmat. It is shawed between Fiwmwawe and Softwawe.
 */

#define ICE_MAX_VSI			768
#define ICE_AQC_TOPO_MAX_WEVEW_NUM	0x9
#define ICE_AQ_SET_MAC_FWAME_SIZE_MAX	9728

stwuct ice_aqc_genewic {
	__we32 pawam0;
	__we32 pawam1;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Get vewsion (diwect 0x0001) */
stwuct ice_aqc_get_vew {
	__we32 wom_vew;
	__we32 fw_buiwd;
	u8 fw_bwanch;
	u8 fw_majow;
	u8 fw_minow;
	u8 fw_patch;
	u8 api_bwanch;
	u8 api_majow;
	u8 api_minow;
	u8 api_patch;
};

/* Send dwivew vewsion (indiwect 0x0002) */
stwuct ice_aqc_dwivew_vew {
	u8 majow_vew;
	u8 minow_vew;
	u8 buiwd_vew;
	u8 subbuiwd_vew;
	u8 wesewved[4];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Queue Shutdown (diwect 0x0003) */
stwuct ice_aqc_q_shutdown {
	u8 dwivew_unwoading;
#define ICE_AQC_DWIVEW_UNWOADING	BIT(0)
	u8 wesewved[15];
};

/* Wequest wesouwce ownewship (diwect 0x0008)
 * Wewease wesouwce ownewship (diwect 0x0009)
 */
stwuct ice_aqc_weq_wes {
	__we16 wes_id;
#define ICE_AQC_WES_ID_NVM		1
#define ICE_AQC_WES_ID_SDP		2
#define ICE_AQC_WES_ID_CHNG_WOCK	3
#define ICE_AQC_WES_ID_GWBW_WOCK	4
	__we16 access_type;
#define ICE_AQC_WES_ACCESS_WEAD		1
#define ICE_AQC_WES_ACCESS_WWITE	2

	/* Upon successfuw compwetion, FW wwites this vawue and dwivew is
	 * expected to wewease wesouwce befowe timeout. This vawue is pwovided
	 * in miwwiseconds.
	 */
	__we32 timeout;
#define ICE_AQ_WES_NVM_WEAD_DFWT_TIMEOUT_MS	3000
#define ICE_AQ_WES_NVM_WWITE_DFWT_TIMEOUT_MS	180000
#define ICE_AQ_WES_CHNG_WOCK_DFWT_TIMEOUT_MS	1000
#define ICE_AQ_WES_GWBW_WOCK_DFWT_TIMEOUT_MS	3000
	/* Fow SDP: pin ID of the SDP */
	__we32 wes_numbew;
	/* Status is onwy used fow ICE_AQC_WES_ID_GWBW_WOCK */
	__we16 status;
#define ICE_AQ_WES_GWBW_SUCCESS		0
#define ICE_AQ_WES_GWBW_IN_PWOG		1
#define ICE_AQ_WES_GWBW_DONE		2
	u8 wesewved[2];
};

/* Get function capabiwities (indiwect 0x000A)
 * Get device capabiwities (indiwect 0x000B)
 */
stwuct ice_aqc_wist_caps {
	u8 cmd_fwags;
	u8 pf_index;
	u8 wesewved[2];
	__we32 count;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Device/Function buffew entwy, wepeated pew wepowted capabiwity */
stwuct ice_aqc_wist_caps_ewem {
	__we16 cap;
#define ICE_AQC_CAPS_VAWID_FUNCTIONS			0x0005
#define ICE_AQC_CAPS_SWIOV				0x0012
#define ICE_AQC_CAPS_VF					0x0013
#define ICE_AQC_CAPS_VSI				0x0017
#define ICE_AQC_CAPS_DCB				0x0018
#define ICE_AQC_CAPS_WSS				0x0040
#define ICE_AQC_CAPS_WXQS				0x0041
#define ICE_AQC_CAPS_TXQS				0x0042
#define ICE_AQC_CAPS_MSIX				0x0043
#define ICE_AQC_CAPS_FD					0x0045
#define ICE_AQC_CAPS_1588				0x0046
#define ICE_AQC_CAPS_MAX_MTU				0x0047
#define ICE_AQC_CAPS_NVM_VEW				0x0048
#define ICE_AQC_CAPS_PENDING_NVM_VEW			0x0049
#define ICE_AQC_CAPS_OWOM_VEW				0x004A
#define ICE_AQC_CAPS_PENDING_OWOM_VEW			0x004B
#define ICE_AQC_CAPS_NET_VEW				0x004C
#define ICE_AQC_CAPS_PENDING_NET_VEW			0x004D
#define ICE_AQC_CAPS_WDMA				0x0051
#define ICE_AQC_CAPS_SENSOW_WEADING			0x0067
#define ICE_AQC_CAPS_PCIE_WESET_AVOIDANCE		0x0076
#define ICE_AQC_CAPS_POST_UPDATE_WESET_WESTWICT		0x0077
#define ICE_AQC_CAPS_NVM_MGMT				0x0080
#define ICE_AQC_CAPS_FW_WAG_SUPPOWT			0x0092
#define ICE_AQC_BIT_WOCEV2_WAG				0x01
#define ICE_AQC_BIT_SWIOV_WAG				0x02

	u8 majow_vew;
	u8 minow_vew;
	/* Numbew of wesouwces descwibed by this capabiwity */
	__we32 numbew;
	/* Onwy meaningfuw fow some types of wesouwces */
	__we32 wogicaw_id;
	/* Onwy meaningfuw fow some types of wesouwces */
	__we32 phys_id;
	__we64 wsvd1;
	__we64 wsvd2;
};

/* Manage MAC addwess, wead command - indiwect (0x0107)
 * This stwuct is awso used fow the wesponse
 */
stwuct ice_aqc_manage_mac_wead {
	__we16 fwags; /* Zewoed by device dwivew */
#define ICE_AQC_MAN_MAC_WAN_ADDW_VAWID		BIT(4)
#define ICE_AQC_MAN_MAC_SAN_ADDW_VAWID		BIT(5)
#define ICE_AQC_MAN_MAC_POWT_ADDW_VAWID		BIT(6)
#define ICE_AQC_MAN_MAC_WOW_ADDW_VAWID		BIT(7)
#define ICE_AQC_MAN_MAC_WEAD_S			4
#define ICE_AQC_MAN_MAC_WEAD_M			(0xF << ICE_AQC_MAN_MAC_WEAD_S)
	u8 wsvd[2];
	u8 num_addw; /* Used in wesponse */
	u8 wsvd1[3];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Wesponse buffew fowmat fow manage MAC wead command */
stwuct ice_aqc_manage_mac_wead_wesp {
	u8 wpowt_num;
	u8 addw_type;
#define ICE_AQC_MAN_MAC_ADDW_TYPE_WAN		0
#define ICE_AQC_MAN_MAC_ADDW_TYPE_WOW		1
	u8 mac_addw[ETH_AWEN];
};

/* Manage MAC addwess, wwite command - diwect (0x0108) */
stwuct ice_aqc_manage_mac_wwite {
	u8 wsvd;
	u8 fwags;
#define ICE_AQC_MAN_MAC_WW_MC_MAG_EN		BIT(0)
#define ICE_AQC_MAN_MAC_WW_WOW_WAA_PFW_KEEP	BIT(1)
#define ICE_AQC_MAN_MAC_WW_S		6
#define ICE_AQC_MAN_MAC_WW_M		ICE_M(3, ICE_AQC_MAN_MAC_WW_S)
#define ICE_AQC_MAN_MAC_UPDATE_WAA	0
#define ICE_AQC_MAN_MAC_UPDATE_WAA_WOW	BIT(ICE_AQC_MAN_MAC_WW_S)
	/* byte stweam in netwowk owdew */
	u8 mac_addw[ETH_AWEN];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Cweaw PXE Command and wesponse (diwect 0x0110) */
stwuct ice_aqc_cweaw_pxe {
	u8 wx_cnt;
#define ICE_AQC_CWEAW_PXE_WX_CNT		0x2
	u8 wesewved[15];
};

/* Get switch configuwation (0x0200) */
stwuct ice_aqc_get_sw_cfg {
	/* Wesewved fow command and copy of wequest fwags fow wesponse */
	__we16 fwags;
	/* Fiwst desc in case of command and next_ewem in case of wesponse
	 * In case of wesponse, if it is not zewo, means aww the configuwation
	 * was not wetuwned and new command shaww be sent with this vawue in
	 * the 'fiwst desc' fiewd
	 */
	__we16 ewement;
	/* Wesewved fow command, onwy used fow wesponse */
	__we16 num_ewems;
	__we16 wsvd;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Each entwy in the wesponse buffew is of the fowwowing type: */
stwuct ice_aqc_get_sw_cfg_wesp_ewem {
	/* VSI/Powt Numbew */
	__we16 vsi_powt_num;
#define ICE_AQC_GET_SW_CONF_WESP_VSI_POWT_NUM_S	0
#define ICE_AQC_GET_SW_CONF_WESP_VSI_POWT_NUM_M	\
			(0x3FF << ICE_AQC_GET_SW_CONF_WESP_VSI_POWT_NUM_S)
#define ICE_AQC_GET_SW_CONF_WESP_TYPE_S	14
#define ICE_AQC_GET_SW_CONF_WESP_TYPE_M	(0x3 << ICE_AQC_GET_SW_CONF_WESP_TYPE_S)
#define ICE_AQC_GET_SW_CONF_WESP_PHYS_POWT	0
#define ICE_AQC_GET_SW_CONF_WESP_VIWT_POWT	1
#define ICE_AQC_GET_SW_CONF_WESP_VSI		2

	/* SWID VSI/Powt bewongs to */
	__we16 swid;

	/* Bit 14..0 : PF/VF numbew VSI bewongs to
	 * Bit 15 : VF indication bit
	 */
	__we16 pf_vf_num;
#define ICE_AQC_GET_SW_CONF_WESP_FUNC_NUM_S	0
#define ICE_AQC_GET_SW_CONF_WESP_FUNC_NUM_M	\
				(0x7FFF << ICE_AQC_GET_SW_CONF_WESP_FUNC_NUM_S)
#define ICE_AQC_GET_SW_CONF_WESP_IS_VF		BIT(15)
};

/* Set Powt pawametews, (diwect, 0x0203) */
stwuct ice_aqc_set_powt_pawams {
	__we16 cmd_fwags;
#define ICE_AQC_SET_P_PAWAMS_DOUBWE_VWAN_ENA	BIT(2)
	__we16 bad_fwame_vsi;
	__we16 swid;
#define ICE_AQC_POWT_SWID_VAWID			BIT(15)
#define ICE_AQC_POWT_SWID_M			0xFF
	u8 wesewved[10];
};

/* These wesouwce type defines awe used fow aww switch wesouwce
 * commands whewe a wesouwce type is wequiwed, such as:
 * Get Wesouwce Awwocation command (indiwect 0x0204)
 * Awwocate Wesouwces command (indiwect 0x0208)
 * Fwee Wesouwces command (indiwect 0x0209)
 * Get Awwocated Wesouwce Descwiptows Command (indiwect 0x020A)
 * Shawe Wesouwce command (indiwect 0x020B)
 */
#define ICE_AQC_WES_TYPE_VSI_WIST_WEP			0x03
#define ICE_AQC_WES_TYPE_VSI_WIST_PWUNE			0x04
#define ICE_AQC_WES_TYPE_WECIPE				0x05
#define ICE_AQC_WES_TYPE_SWID				0x07
#define ICE_AQC_WES_TYPE_FDIW_COUNTEW_BWOCK		0x21
#define ICE_AQC_WES_TYPE_FDIW_GUAWANTEED_ENTWIES	0x22
#define ICE_AQC_WES_TYPE_FDIW_SHAWED_ENTWIES		0x23
#define ICE_AQC_WES_TYPE_FD_PWOF_BWDW_PWOFID		0x58
#define ICE_AQC_WES_TYPE_FD_PWOF_BWDW_TCAM		0x59
#define ICE_AQC_WES_TYPE_HASH_PWOF_BWDW_PWOFID		0x60
#define ICE_AQC_WES_TYPE_HASH_PWOF_BWDW_TCAM		0x61

#define ICE_AQC_WES_TYPE_FWAG_SHAWED			BIT(7)
#define ICE_AQC_WES_TYPE_FWAG_SCAN_BOTTOM		BIT(12)
#define ICE_AQC_WES_TYPE_FWAG_IGNOWE_INDEX		BIT(13)

#define ICE_AQC_WES_TYPE_FWAG_DEDICATED			0x00

#define ICE_AQC_WES_TYPE_S	0
#define ICE_AQC_WES_TYPE_M	(0x07F << ICE_AQC_WES_TYPE_S)

/* Awwocate Wesouwces command (indiwect 0x0208)
 * Fwee Wesouwces command (indiwect 0x0209)
 * Shawe Wesouwce command (indiwect 0x020B)
 */
stwuct ice_aqc_awwoc_fwee_wes_cmd {
	__we16 num_entwies; /* Numbew of Wesouwce entwies */
	u8 wesewved[6];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Wesouwce descwiptow */
stwuct ice_aqc_wes_ewem {
	union {
		__we16 sw_wesp;
		__we16 fwu_wesp;
	} e;
};

/* Buffew fow Awwocate/Fwee Wesouwces commands */
stwuct ice_aqc_awwoc_fwee_wes_ewem {
	__we16 wes_type; /* Types defined above cmd 0x0204 */
#define ICE_AQC_WES_TYPE_SHAWED_S	7
#define ICE_AQC_WES_TYPE_SHAWED_M	(0x1 << ICE_AQC_WES_TYPE_SHAWED_S)
#define ICE_AQC_WES_TYPE_VSI_PWUNE_WIST_S	8
#define ICE_AQC_WES_TYPE_VSI_PWUNE_WIST_M	\
				(0xF << ICE_AQC_WES_TYPE_VSI_PWUNE_WIST_S)
	__we16 num_ewems;
	stwuct ice_aqc_wes_ewem ewem[];
};

/* Wequest buffew fow Set VWAN Mode AQ command (indiwect 0x020C) */
stwuct ice_aqc_set_vwan_mode {
	u8 wesewved;
	u8 w2tag_pwio_tagging;
#define ICE_AQ_VWAN_PWIO_TAG_S			0
#define ICE_AQ_VWAN_PWIO_TAG_M			(0x7 << ICE_AQ_VWAN_PWIO_TAG_S)
#define ICE_AQ_VWAN_PWIO_TAG_NOT_SUPPOWTED	0x0
#define ICE_AQ_VWAN_PWIO_TAG_STAG		0x1
#define ICE_AQ_VWAN_PWIO_TAG_OUTEW_CTAG		0x2
#define ICE_AQ_VWAN_PWIO_TAG_OUTEW_VWAN		0x3
#define ICE_AQ_VWAN_PWIO_TAG_INNEW_CTAG		0x4
#define ICE_AQ_VWAN_PWIO_TAG_MAX		0x4
#define ICE_AQ_VWAN_PWIO_TAG_EWWOW		0x7
	u8 w2tag_wesewved[64];
	u8 wdma_packet;
#define ICE_AQ_VWAN_WDMA_TAG_S			0
#define ICE_AQ_VWAN_WDMA_TAG_M			(0x3F << ICE_AQ_VWAN_WDMA_TAG_S)
#define ICE_AQ_SVM_VWAN_WDMA_PKT_FWAG_SETTING	0x10
#define ICE_AQ_DVM_VWAN_WDMA_PKT_FWAG_SETTING	0x1A
	u8 wdma_wesewved[2];
	u8 mng_vwan_pwot_id;
#define ICE_AQ_VWAN_MNG_PWOTOCOW_ID_OUTEW	0x10
#define ICE_AQ_VWAN_MNG_PWOTOCOW_ID_INNEW	0x11
	u8 pwot_id_wesewved[30];
};

/* Wesponse buffew fow Get VWAN Mode AQ command (indiwect 0x020D) */
stwuct ice_aqc_get_vwan_mode {
	u8 vwan_mode;
#define ICE_AQ_VWAN_MODE_DVM_ENA	BIT(0)
	u8 w2tag_pwio_tagging;
	u8 wesewved[98];
};

/* Add VSI (indiwect 0x0210)
 * Update VSI (indiwect 0x0211)
 * Get VSI (indiwect 0x0212)
 * Fwee VSI (indiwect 0x0213)
 */
stwuct ice_aqc_add_get_update_fwee_vsi {
	__we16 vsi_num;
#define ICE_AQ_VSI_NUM_S	0
#define ICE_AQ_VSI_NUM_M	(0x03FF << ICE_AQ_VSI_NUM_S)
#define ICE_AQ_VSI_IS_VAWID	BIT(15)
	__we16 cmd_fwags;
#define ICE_AQ_VSI_KEEP_AWWOC	0x1
	u8 vf_id;
	u8 wesewved;
	__we16 vsi_fwags;
#define ICE_AQ_VSI_TYPE_S	0
#define ICE_AQ_VSI_TYPE_M	(0x3 << ICE_AQ_VSI_TYPE_S)
#define ICE_AQ_VSI_TYPE_VF	0x0
#define ICE_AQ_VSI_TYPE_VMDQ2	0x1
#define ICE_AQ_VSI_TYPE_PF	0x2
#define ICE_AQ_VSI_TYPE_EMP_MNG	0x3
	__we32 addw_high;
	__we32 addw_wow;
};

/* Wesponse descwiptow fow:
 * Add VSI (indiwect 0x0210)
 * Update VSI (indiwect 0x0211)
 * Fwee VSI (indiwect 0x0213)
 */
stwuct ice_aqc_add_update_fwee_vsi_wesp {
	__we16 vsi_num;
	__we16 ext_status;
	__we16 vsi_used;
	__we16 vsi_fwee;
	__we32 addw_high;
	__we32 addw_wow;
};

stwuct ice_aqc_vsi_pwops {
	__we16 vawid_sections;
#define ICE_AQ_VSI_PWOP_SW_VAWID		BIT(0)
#define ICE_AQ_VSI_PWOP_SECUWITY_VAWID		BIT(1)
#define ICE_AQ_VSI_PWOP_VWAN_VAWID		BIT(2)
#define ICE_AQ_VSI_PWOP_OUTEW_TAG_VAWID		BIT(3)
#define ICE_AQ_VSI_PWOP_INGWESS_UP_VAWID	BIT(4)
#define ICE_AQ_VSI_PWOP_EGWESS_UP_VAWID		BIT(5)
#define ICE_AQ_VSI_PWOP_WXQ_MAP_VAWID		BIT(6)
#define ICE_AQ_VSI_PWOP_Q_OPT_VAWID		BIT(7)
#define ICE_AQ_VSI_PWOP_OUTEW_UP_VAWID		BIT(8)
#define ICE_AQ_VSI_PWOP_FWOW_DIW_VAWID		BIT(11)
#define ICE_AQ_VSI_PWOP_PASID_VAWID		BIT(12)
	/* switch section */
	u8 sw_id;
	u8 sw_fwags;
#define ICE_AQ_VSI_SW_FWAG_AWWOW_WB		BIT(5)
#define ICE_AQ_VSI_SW_FWAG_WOCAW_WB		BIT(6)
#define ICE_AQ_VSI_SW_FWAG_SWC_PWUNE		BIT(7)
	u8 sw_fwags2;
#define ICE_AQ_VSI_SW_FWAG_WX_PWUNE_EN_S	0
#define ICE_AQ_VSI_SW_FWAG_WX_PWUNE_EN_M	(0xF << ICE_AQ_VSI_SW_FWAG_WX_PWUNE_EN_S)
#define ICE_AQ_VSI_SW_FWAG_WX_VWAN_PWUNE_ENA	BIT(0)
#define ICE_AQ_VSI_SW_FWAG_WAN_ENA		BIT(4)
	u8 veb_stat_id;
#define ICE_AQ_VSI_SW_VEB_STAT_ID_S		0
#define ICE_AQ_VSI_SW_VEB_STAT_ID_M		(0x1F << ICE_AQ_VSI_SW_VEB_STAT_ID_S)
#define ICE_AQ_VSI_SW_VEB_STAT_ID_VAWID		BIT(5)
	/* secuwity section */
	u8 sec_fwags;
#define ICE_AQ_VSI_SEC_FWAG_AWWOW_DEST_OVWD	BIT(0)
#define ICE_AQ_VSI_SEC_FWAG_ENA_MAC_ANTI_SPOOF	BIT(2)
#define ICE_AQ_VSI_SEC_TX_PWUNE_ENA_S		4
#define ICE_AQ_VSI_SEC_TX_PWUNE_ENA_M		(0xF << ICE_AQ_VSI_SEC_TX_PWUNE_ENA_S)
#define ICE_AQ_VSI_SEC_TX_VWAN_PWUNE_ENA	BIT(0)
	u8 sec_wesewved;
	/* VWAN section */
	__we16 powt_based_innew_vwan; /* VWANS incwude pwiowity bits */
	u8 innew_vwan_wesewved[2];
	u8 innew_vwan_fwags;
#define ICE_AQ_VSI_INNEW_VWAN_TX_MODE_S		0
#define ICE_AQ_VSI_INNEW_VWAN_TX_MODE_M		(0x3 << ICE_AQ_VSI_INNEW_VWAN_TX_MODE_S)
#define ICE_AQ_VSI_INNEW_VWAN_TX_MODE_ACCEPTUNTAGGED	0x1
#define ICE_AQ_VSI_INNEW_VWAN_TX_MODE_ACCEPTTAGGED	0x2
#define ICE_AQ_VSI_INNEW_VWAN_TX_MODE_AWW	0x3
#define ICE_AQ_VSI_INNEW_VWAN_INSEWT_PVID	BIT(2)
#define ICE_AQ_VSI_INNEW_VWAN_EMODE_S		3
#define ICE_AQ_VSI_INNEW_VWAN_EMODE_M		(0x3 << ICE_AQ_VSI_INNEW_VWAN_EMODE_S)
#define ICE_AQ_VSI_INNEW_VWAN_EMODE_STW_BOTH	0x0U
#define ICE_AQ_VSI_INNEW_VWAN_EMODE_STW_UP	0x1U
#define ICE_AQ_VSI_INNEW_VWAN_EMODE_STW		0x2U
#define ICE_AQ_VSI_INNEW_VWAN_EMODE_NOTHING	0x3U
	u8 innew_vwan_wesewved2[3];
	/* ingwess egwess up sections */
	__we32 ingwess_tabwe; /* bitmap, 3 bits pew up */
#define ICE_AQ_VSI_UP_TABWE_UP0_S		0
#define ICE_AQ_VSI_UP_TABWE_UP0_M		(0x7 << ICE_AQ_VSI_UP_TABWE_UP0_S)
#define ICE_AQ_VSI_UP_TABWE_UP1_S		3
#define ICE_AQ_VSI_UP_TABWE_UP1_M		(0x7 << ICE_AQ_VSI_UP_TABWE_UP1_S)
#define ICE_AQ_VSI_UP_TABWE_UP2_S		6
#define ICE_AQ_VSI_UP_TABWE_UP2_M		(0x7 << ICE_AQ_VSI_UP_TABWE_UP2_S)
#define ICE_AQ_VSI_UP_TABWE_UP3_S		9
#define ICE_AQ_VSI_UP_TABWE_UP3_M		(0x7 << ICE_AQ_VSI_UP_TABWE_UP3_S)
#define ICE_AQ_VSI_UP_TABWE_UP4_S		12
#define ICE_AQ_VSI_UP_TABWE_UP4_M		(0x7 << ICE_AQ_VSI_UP_TABWE_UP4_S)
#define ICE_AQ_VSI_UP_TABWE_UP5_S		15
#define ICE_AQ_VSI_UP_TABWE_UP5_M		(0x7 << ICE_AQ_VSI_UP_TABWE_UP5_S)
#define ICE_AQ_VSI_UP_TABWE_UP6_S		18
#define ICE_AQ_VSI_UP_TABWE_UP6_M		(0x7 << ICE_AQ_VSI_UP_TABWE_UP6_S)
#define ICE_AQ_VSI_UP_TABWE_UP7_S		21
#define ICE_AQ_VSI_UP_TABWE_UP7_M		(0x7 << ICE_AQ_VSI_UP_TABWE_UP7_S)
	__we32 egwess_tabwe;   /* same defines as fow ingwess tabwe */
	/* outew tags section */
	__we16 powt_based_outew_vwan;
	u8 outew_vwan_fwags;
#define ICE_AQ_VSI_OUTEW_VWAN_EMODE_S		0
#define ICE_AQ_VSI_OUTEW_VWAN_EMODE_M		(0x3 << ICE_AQ_VSI_OUTEW_VWAN_EMODE_S)
#define ICE_AQ_VSI_OUTEW_VWAN_EMODE_SHOW_BOTH	0x0
#define ICE_AQ_VSI_OUTEW_VWAN_EMODE_SHOW_UP	0x1
#define ICE_AQ_VSI_OUTEW_VWAN_EMODE_SHOW	0x2
#define ICE_AQ_VSI_OUTEW_VWAN_EMODE_NOTHING	0x3
#define ICE_AQ_VSI_OUTEW_TAG_TYPE_S		2
#define ICE_AQ_VSI_OUTEW_TAG_TYPE_M		(0x3 << ICE_AQ_VSI_OUTEW_TAG_TYPE_S)
#define ICE_AQ_VSI_OUTEW_TAG_NONE		0x0
#define ICE_AQ_VSI_OUTEW_TAG_STAG		0x1
#define ICE_AQ_VSI_OUTEW_TAG_VWAN_8100		0x2
#define ICE_AQ_VSI_OUTEW_TAG_VWAN_9100		0x3
#define ICE_AQ_VSI_OUTEW_VWAN_POWT_BASED_INSEWT		BIT(4)
#define ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_S			5
#define ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_M			(0x3 << ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_S)
#define ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_ACCEPTUNTAGGED	0x1
#define ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_ACCEPTTAGGED	0x2
#define ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_AWW		0x3
#define ICE_AQ_VSI_OUTEW_VWAN_BWOCK_TX_DESC		BIT(7)
	u8 outew_vwan_wesewved;
	/* queue mapping section */
	__we16 mapping_fwags;
#define ICE_AQ_VSI_Q_MAP_CONTIG			0x0
#define ICE_AQ_VSI_Q_MAP_NONCONTIG		BIT(0)
	__we16 q_mapping[16];
#define ICE_AQ_VSI_Q_S				0
#define ICE_AQ_VSI_Q_M				(0x7FF << ICE_AQ_VSI_Q_S)
	__we16 tc_mapping[8];
#define ICE_AQ_VSI_TC_Q_OFFSET_S		0
#define ICE_AQ_VSI_TC_Q_OFFSET_M		(0x7FF << ICE_AQ_VSI_TC_Q_OFFSET_S)
#define ICE_AQ_VSI_TC_Q_NUM_S			11
#define ICE_AQ_VSI_TC_Q_NUM_M			(0xF << ICE_AQ_VSI_TC_Q_NUM_S)
	/* queueing option section */
	u8 q_opt_wss;
#define ICE_AQ_VSI_Q_OPT_WSS_WUT_S		0
#define ICE_AQ_VSI_Q_OPT_WSS_WUT_M		(0x3 << ICE_AQ_VSI_Q_OPT_WSS_WUT_S)
#define ICE_AQ_VSI_Q_OPT_WSS_WUT_VSI		0x0
#define ICE_AQ_VSI_Q_OPT_WSS_WUT_PF		0x2
#define ICE_AQ_VSI_Q_OPT_WSS_WUT_GBW		0x3
#define ICE_AQ_VSI_Q_OPT_WSS_GBW_WUT_S		2
#define ICE_AQ_VSI_Q_OPT_WSS_GBW_WUT_M		(0xF << ICE_AQ_VSI_Q_OPT_WSS_GBW_WUT_S)
#define ICE_AQ_VSI_Q_OPT_WSS_HASH_S		6
#define ICE_AQ_VSI_Q_OPT_WSS_HASH_M		GENMASK(7, 6)
#define ICE_AQ_VSI_Q_OPT_WSS_HASH_TPWZ		0x0U
#define ICE_AQ_VSI_Q_OPT_WSS_HASH_SYM_TPWZ	0x1U
#define ICE_AQ_VSI_Q_OPT_WSS_HASH_XOW		0x2U
#define ICE_AQ_VSI_Q_OPT_WSS_HASH_JHASH		0x3U
	u8 q_opt_tc;
#define ICE_AQ_VSI_Q_OPT_TC_OVW_S		0
#define ICE_AQ_VSI_Q_OPT_TC_OVW_M		(0x1F << ICE_AQ_VSI_Q_OPT_TC_OVW_S)
#define ICE_AQ_VSI_Q_OPT_PWOF_TC_OVW		BIT(7)
	u8 q_opt_fwags;
#define ICE_AQ_VSI_Q_OPT_PE_FWTW_EN		BIT(0)
	u8 q_opt_wesewved[3];
	/* outew up section */
	__we32 outew_up_tabwe; /* same stwuctuwe and defines as ingwess tbw */
	/* section 10 */
	__we16 sect_10_wesewved;
	/* fwow diwectow section */
	__we16 fd_options;
#define ICE_AQ_VSI_FD_ENABWE			BIT(0)
#define ICE_AQ_VSI_FD_TX_AUTO_ENABWE		BIT(1)
#define ICE_AQ_VSI_FD_PWOG_ENABWE		BIT(3)
	__we16 max_fd_fwtw_dedicated;
	__we16 max_fd_fwtw_shawed;
	__we16 fd_def_q;
#define ICE_AQ_VSI_FD_DEF_Q_S			0
#define ICE_AQ_VSI_FD_DEF_Q_M			(0x7FF << ICE_AQ_VSI_FD_DEF_Q_S)
#define ICE_AQ_VSI_FD_DEF_GWP_S			12
#define ICE_AQ_VSI_FD_DEF_GWP_M			(0x7 << ICE_AQ_VSI_FD_DEF_GWP_S)
	__we16 fd_wepowt_opt;
#define ICE_AQ_VSI_FD_WEPOWT_Q_S		0
#define ICE_AQ_VSI_FD_WEPOWT_Q_M		(0x7FF << ICE_AQ_VSI_FD_WEPOWT_Q_S)
#define ICE_AQ_VSI_FD_DEF_PWIOWITY_S		12
#define ICE_AQ_VSI_FD_DEF_PWIOWITY_M		(0x7 << ICE_AQ_VSI_FD_DEF_PWIOWITY_S)
#define ICE_AQ_VSI_FD_DEF_DWOP			BIT(15)
	/* PASID section */
	__we32 pasid_id;
#define ICE_AQ_VSI_PASID_ID_S			0
#define ICE_AQ_VSI_PASID_ID_M			(0xFFFFF << ICE_AQ_VSI_PASID_ID_S)
#define ICE_AQ_VSI_PASID_ID_VAWID		BIT(31)
	u8 wesewved[24];
};

#define ICE_MAX_NUM_WECIPES 64

/* Add/Get Wecipe (indiwect 0x0290/0x0292) */
stwuct ice_aqc_add_get_wecipe {
	__we16 num_sub_wecipes;	/* Input in Add cmd, Output in Get cmd */
	__we16 wetuwn_index;	/* Input, used fow Get cmd onwy */
	u8 wesewved[4];
	__we32 addw_high;
	__we32 addw_wow;
};

stwuct ice_aqc_wecipe_content {
	u8 wid;
#define ICE_AQ_WECIPE_ID_S		0
#define ICE_AQ_WECIPE_ID_M		(0x3F << ICE_AQ_WECIPE_ID_S)
#define ICE_AQ_WECIPE_ID_IS_WOOT	BIT(7)
#define ICE_AQ_SW_ID_WKUP_IDX		0
	u8 wkup_indx[5];
#define ICE_AQ_WECIPE_WKUP_DATA_S	0
#define ICE_AQ_WECIPE_WKUP_DATA_M	(0x3F << ICE_AQ_WECIPE_WKUP_DATA_S)
#define ICE_AQ_WECIPE_WKUP_IGNOWE	BIT(7)
#define ICE_AQ_SW_ID_WKUP_MASK		0x00FF
	__we16 mask[5];
	u8 wesuwt_indx;
#define ICE_AQ_WECIPE_WESUWT_DATA_S	0
#define ICE_AQ_WECIPE_WESUWT_DATA_M	(0x3F << ICE_AQ_WECIPE_WESUWT_DATA_S)
#define ICE_AQ_WECIPE_WESUWT_EN		BIT(7)
	u8 wsvd0[3];
	u8 act_ctww_join_pwiowity;
	u8 act_ctww_fwd_pwiowity;
#define ICE_AQ_WECIPE_FWD_PWIOWITY_S	0
#define ICE_AQ_WECIPE_FWD_PWIOWITY_M	(0xF << ICE_AQ_WECIPE_FWD_PWIOWITY_S)
	u8 act_ctww;
#define ICE_AQ_WECIPE_ACT_NEED_PASS_W2	BIT(0)
#define ICE_AQ_WECIPE_ACT_AWWOW_PASS_W2	BIT(1)
#define ICE_AQ_WECIPE_ACT_INV_ACT	BIT(2)
#define ICE_AQ_WECIPE_ACT_PWUNE_INDX_S	4
#define ICE_AQ_WECIPE_ACT_PWUNE_INDX_M	(0x3 << ICE_AQ_WECIPE_ACT_PWUNE_INDX_S)
	u8 wsvd1;
	__we32 dfwt_act;
#define ICE_AQ_WECIPE_DFWT_ACT_S	0
#define ICE_AQ_WECIPE_DFWT_ACT_M	(0x7FFFF << ICE_AQ_WECIPE_DFWT_ACT_S)
#define ICE_AQ_WECIPE_DFWT_ACT_VAWID	BIT(31)
};

stwuct ice_aqc_wecipe_data_ewem {
	u8 wecipe_indx;
	u8 wesp_bits;
#define ICE_AQ_WECIPE_WAS_UPDATED	BIT(0)
	u8 wsvd0[2];
	u8 wecipe_bitmap[8];
	u8 wsvd1[4];
	stwuct ice_aqc_wecipe_content content;
	u8 wsvd2[20];
};

/* Set/Get Wecipes to Pwofiwe Association (diwect 0x0291/0x0293) */
stwuct ice_aqc_wecipe_to_pwofiwe {
	__we16 pwofiwe_id;
	u8 wsvd[6];
	DECWAWE_BITMAP(wecipe_assoc, ICE_MAX_NUM_WECIPES);
};

/* Add/Update/Wemove/Get switch wuwes (indiwect 0x02A0, 0x02A1, 0x02A2, 0x02A3)
 */
stwuct ice_aqc_sw_wuwes {
	/* ops: add switch wuwes, wefewwing the numbew of wuwes.
	 * ops: update switch wuwes, wefewwing the numbew of fiwtews
	 * ops: wemove switch wuwes, wefewwing the entwy index.
	 * ops: get switch wuwes, wefewwing to the numbew of fiwtews.
	 */
	__we16 num_wuwes_fwtw_entwy_index;
	u8 wesewved[6];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Add switch wuwe wesponse:
 * Content of wetuwn buffew is same as the input buffew. The status fiewd and
 * WUT index awe updated as pawt of the wesponse
 */
stwuct ice_aqc_sw_wuwes_ewem_hdw {
	__we16 type; /* Switch wuwe type, one of T_... */
#define ICE_AQC_SW_WUWES_T_WKUP_WX		0x0
#define ICE_AQC_SW_WUWES_T_WKUP_TX		0x1
#define ICE_AQC_SW_WUWES_T_WG_ACT		0x2
#define ICE_AQC_SW_WUWES_T_VSI_WIST_SET		0x3
#define ICE_AQC_SW_WUWES_T_VSI_WIST_CWEAW	0x4
#define ICE_AQC_SW_WUWES_T_PWUNE_WIST_SET	0x5
#define ICE_AQC_SW_WUWES_T_PWUNE_WIST_CWEAW	0x6
	__we16 status;
} __packed __awigned(sizeof(__we16));

/* Add/Update/Get/Wemove wookup Wx/Tx command/wesponse entwy
 * This stwuctuwes descwibes the wookup wuwes and associated actions. "index"
 * is wetuwned as pawt of a wesponse to a successfuw Add command, and can be
 * used to identify the wuwe fow Update/Get/Wemove commands.
 */
stwuct ice_sw_wuwe_wkup_wx_tx {
	stwuct ice_aqc_sw_wuwes_ewem_hdw hdw;

	__we16 wecipe_id;
#define ICE_SW_WECIPE_WOGICAW_POWT_FWD		10
	/* Souwce powt fow WOOKUP_WX and souwce VSI in case of WOOKUP_TX */
	__we16 swc;
	__we32 act;

	/* Bit 0:1 - Action type */
#define ICE_SINGWE_ACT_TYPE_S	0x00
#define ICE_SINGWE_ACT_TYPE_M	(0x3 << ICE_SINGWE_ACT_TYPE_S)

	/* Bit 2 - Woop back enabwe
	 * Bit 3 - WAN enabwe
	 */
#define ICE_SINGWE_ACT_WB_ENABWE	BIT(2)
#define ICE_SINGWE_ACT_WAN_ENABWE	BIT(3)

	/* Action type = 0 - Fowwawd to VSI ow VSI wist */
#define ICE_SINGWE_ACT_VSI_FOWWAWDING	0x0

#define ICE_SINGWE_ACT_VSI_ID_S		4
#define ICE_SINGWE_ACT_VSI_ID_M		(0x3FF << ICE_SINGWE_ACT_VSI_ID_S)
#define ICE_SINGWE_ACT_VSI_WIST_ID_S	4
#define ICE_SINGWE_ACT_VSI_WIST_ID_M	(0x3FF << ICE_SINGWE_ACT_VSI_WIST_ID_S)
	/* This bit needs to be set if action is fowwawd to VSI wist */
#define ICE_SINGWE_ACT_VSI_WIST		BIT(14)
#define ICE_SINGWE_ACT_VAWID_BIT	BIT(17)
#define ICE_SINGWE_ACT_DWOP		BIT(18)

	/* Action type = 1 - Fowwawd to Queue of Queue gwoup */
#define ICE_SINGWE_ACT_TO_Q		0x1
#define ICE_SINGWE_ACT_Q_INDEX_S	4
#define ICE_SINGWE_ACT_Q_INDEX_M	(0x7FF << ICE_SINGWE_ACT_Q_INDEX_S)
#define ICE_SINGWE_ACT_Q_WEGION_S	15
#define ICE_SINGWE_ACT_Q_WEGION_M	(0x7 << ICE_SINGWE_ACT_Q_WEGION_S)
#define ICE_SINGWE_ACT_Q_PWIOWITY	BIT(18)

	/* Action type = 2 - Pwune */
#define ICE_SINGWE_ACT_PWUNE		0x2
#define ICE_SINGWE_ACT_EGWESS		BIT(15)
#define ICE_SINGWE_ACT_INGWESS		BIT(16)
#define ICE_SINGWE_ACT_PWUNET		BIT(17)
	/* Bit 18 shouwd be set to 0 fow this action */

	/* Action type = 2 - Pointew */
#define ICE_SINGWE_ACT_PTW		0x2
#define ICE_SINGWE_ACT_PTW_VAW_S	4
#define ICE_SINGWE_ACT_PTW_VAW_M	(0x1FFF << ICE_SINGWE_ACT_PTW_VAW_S)
	/* Bit 18 shouwd be set to 1 */
#define ICE_SINGWE_ACT_PTW_BIT		BIT(18)

	/* Action type = 3 - Othew actions. Wast two bits
	 * awe othew action identifiew
	 */
#define ICE_SINGWE_ACT_OTHEW_ACTS		0x3
#define ICE_SINGWE_OTHEW_ACT_IDENTIFIEW_S	17
#define ICE_SINGWE_OTHEW_ACT_IDENTIFIEW_M	\
				(0x3 << ICE_SINGWE_OTHEW_ACT_IDENTIFIEW_S)

	/* Bit 17:18 - Defines othew actions */
	/* Othew action = 0 - Miwwow VSI */
#define ICE_SINGWE_OTHEW_ACT_MIWWOW		0
#define ICE_SINGWE_ACT_MIWWOW_VSI_ID_S	4
#define ICE_SINGWE_ACT_MIWWOW_VSI_ID_M	\
				(0x3FF << ICE_SINGWE_ACT_MIWWOW_VSI_ID_S)

	/* Othew action = 3 - Set Stat count */
#define ICE_SINGWE_OTHEW_ACT_STAT_COUNT		3
#define ICE_SINGWE_ACT_STAT_COUNT_INDEX_S	4
#define ICE_SINGWE_ACT_STAT_COUNT_INDEX_M	\
				(0x7F << ICE_SINGWE_ACT_STAT_COUNT_INDEX_S)

	__we16 index; /* The index of the wuwe in the wookup tabwe */
	/* Wength and vawues of the headew to be matched pew wecipe ow
	 * wookup-type
	 */
	__we16 hdw_wen;
	u8 hdw_data[];
} __packed __awigned(sizeof(__we16));

/* Add/Update/Wemove wawge action command/wesponse entwy
 * "index" is wetuwned as pawt of a wesponse to a successfuw Add command, and
 * can be used to identify the action fow Update/Get/Wemove commands.
 */
stwuct ice_sw_wuwe_wg_act {
	stwuct ice_aqc_sw_wuwes_ewem_hdw hdw;

	__we16 index; /* Index in wawge action tabwe */
	__we16 size;
	/* Max numbew of wawge actions */
#define ICE_MAX_WG_ACT	4
	/* Bit 0:1 - Action type */
#define ICE_WG_ACT_TYPE_S	0
#define ICE_WG_ACT_TYPE_M	(0x7 << ICE_WG_ACT_TYPE_S)

	/* Action type = 0 - Fowwawd to VSI ow VSI wist */
#define ICE_WG_ACT_VSI_FOWWAWDING	0
#define ICE_WG_ACT_VSI_ID_S		3
#define ICE_WG_ACT_VSI_ID_M		(0x3FF << ICE_WG_ACT_VSI_ID_S)
#define ICE_WG_ACT_VSI_WIST_ID_S	3
#define ICE_WG_ACT_VSI_WIST_ID_M	(0x3FF << ICE_WG_ACT_VSI_WIST_ID_S)
	/* This bit needs to be set if action is fowwawd to VSI wist */
#define ICE_WG_ACT_VSI_WIST		BIT(13)

#define ICE_WG_ACT_VAWID_BIT		BIT(16)

	/* Action type = 1 - Fowwawd to Queue of Queue gwoup */
#define ICE_WG_ACT_TO_Q			0x1
#define ICE_WG_ACT_Q_INDEX_S		3
#define ICE_WG_ACT_Q_INDEX_M		(0x7FF << ICE_WG_ACT_Q_INDEX_S)
#define ICE_WG_ACT_Q_WEGION_S		14
#define ICE_WG_ACT_Q_WEGION_M		(0x7 << ICE_WG_ACT_Q_WEGION_S)
#define ICE_WG_ACT_Q_PWIOWITY_SET	BIT(17)

	/* Action type = 2 - Pwune */
#define ICE_WG_ACT_PWUNE		0x2
#define ICE_WG_ACT_EGWESS		BIT(14)
#define ICE_WG_ACT_INGWESS		BIT(15)
#define ICE_WG_ACT_PWUNET		BIT(16)

	/* Action type = 3 - Miwwow VSI */
#define ICE_WG_OTHEW_ACT_MIWWOW		0x3
#define ICE_WG_ACT_MIWWOW_VSI_ID_S	3
#define ICE_WG_ACT_MIWWOW_VSI_ID_M	(0x3FF << ICE_WG_ACT_MIWWOW_VSI_ID_S)

	/* Action type = 5 - Genewic Vawue */
#define ICE_WG_ACT_GENEWIC		0x5
#define ICE_WG_ACT_GENEWIC_VAWUE_S	3
#define ICE_WG_ACT_GENEWIC_VAWUE_M	(0xFFFF << ICE_WG_ACT_GENEWIC_VAWUE_S)
#define ICE_WG_ACT_GENEWIC_OFFSET_S	19
#define ICE_WG_ACT_GENEWIC_OFFSET_M	(0x7 << ICE_WG_ACT_GENEWIC_OFFSET_S)
#define ICE_WG_ACT_GENEWIC_PWIOWITY_S	22
#define ICE_WG_ACT_GENEWIC_PWIOWITY_M	(0x7 << ICE_WG_ACT_GENEWIC_PWIOWITY_S)
#define ICE_WG_ACT_GENEWIC_OFF_WX_DESC_PWOF_IDX	7

	/* Action = 7 - Set Stat count */
#define ICE_WG_ACT_STAT_COUNT		0x7
#define ICE_WG_ACT_STAT_COUNT_S		3
#define ICE_WG_ACT_STAT_COUNT_M		(0x7F << ICE_WG_ACT_STAT_COUNT_S)
	__we32 act[]; /* awway of size fow actions */
} __packed __awigned(sizeof(__we16));

/* Add/Update/Wemove VSI wist command/wesponse entwy
 * "index" is wetuwned as pawt of a wesponse to a successfuw Add command, and
 * can be used to identify the VSI wist fow Update/Get/Wemove commands.
 */
stwuct ice_sw_wuwe_vsi_wist {
	stwuct ice_aqc_sw_wuwes_ewem_hdw hdw;

	__we16 index; /* Index of VSI/Pwune wist */
	__we16 numbew_vsi;
	__we16 vsi[]; /* Awway of numbew_vsi VSI numbews */
} __packed __awigned(sizeof(__we16));

/* Quewy PFC Mode (diwect 0x0302)
 * Set PFC Mode (diwect 0x0303)
 */
stwuct ice_aqc_set_quewy_pfc_mode {
	u8	pfc_mode;
/* Fow Quewy Command wesponse, wesewved in aww othew cases */
#define ICE_AQC_PFC_VWAN_BASED_PFC	1
#define ICE_AQC_PFC_DSCP_BASED_PFC	2
	u8	wsvd[15];
};
/* Get Defauwt Topowogy (indiwect 0x0400) */
stwuct ice_aqc_get_topo {
	u8 powt_num;
	u8 num_bwanches;
	__we16 wesewved1;
	__we32 wesewved2;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Update TSE (indiwect 0x0403)
 * Get TSE (indiwect 0x0404)
 * Add TSE (indiwect 0x0401)
 * Dewete TSE (indiwect 0x040F)
 * Move TSE (indiwect 0x0408)
 * Suspend Nodes (indiwect 0x0409)
 * Wesume Nodes (indiwect 0x040A)
 */
stwuct ice_aqc_sched_ewem_cmd {
	__we16 num_ewem_weq;	/* Used by commands */
	__we16 num_ewem_wesp;	/* Used by wesponses */
	__we32 wesewved;
	__we32 addw_high;
	__we32 addw_wow;
};

stwuct ice_aqc_txsched_move_gwp_info_hdw {
	__we32 swc_pawent_teid;
	__we32 dest_pawent_teid;
	__we16 num_ewems;
	u8 mode;
#define ICE_AQC_MOVE_EWEM_MODE_SAME_PF		0x0
#define ICE_AQC_MOVE_EWEM_MODE_GIVE_OWN		0x1
#define ICE_AQC_MOVE_EWEM_MODE_KEEP_OWN		0x2
	u8 wesewved;
};

stwuct ice_aqc_move_ewem {
	stwuct ice_aqc_txsched_move_gwp_info_hdw hdw;
	__we32 teid[];
};

stwuct ice_aqc_ewem_info_bw {
	__we16 bw_pwofiwe_idx;
	__we16 bw_awwoc;
};

stwuct ice_aqc_txsched_ewem {
	u8 ewem_type; /* Speciaw fiewd, wesewved fow some aq cawws */
#define ICE_AQC_EWEM_TYPE_UNDEFINED		0x0
#define ICE_AQC_EWEM_TYPE_WOOT_POWT		0x1
#define ICE_AQC_EWEM_TYPE_TC			0x2
#define ICE_AQC_EWEM_TYPE_SE_GENEWIC		0x3
#define ICE_AQC_EWEM_TYPE_ENTWY_POINT		0x4
#define ICE_AQC_EWEM_TYPE_WEAF			0x5
#define ICE_AQC_EWEM_TYPE_SE_PADDED		0x6
	u8 vawid_sections;
#define ICE_AQC_EWEM_VAWID_GENEWIC		BIT(0)
#define ICE_AQC_EWEM_VAWID_CIW			BIT(1)
#define ICE_AQC_EWEM_VAWID_EIW			BIT(2)
#define ICE_AQC_EWEM_VAWID_SHAWED		BIT(3)
	u8 genewic;
#define ICE_AQC_EWEM_GENEWIC_MODE_M		0x1
#define ICE_AQC_EWEM_GENEWIC_PWIO_S		0x1
#define ICE_AQC_EWEM_GENEWIC_PWIO_M	        GENMASK(3, 1)
#define ICE_AQC_EWEM_GENEWIC_SP_S		0x4
#define ICE_AQC_EWEM_GENEWIC_SP_M	        GENMASK(4, 4)
#define ICE_AQC_EWEM_GENEWIC_ADJUST_VAW_S	0x5
#define ICE_AQC_EWEM_GENEWIC_ADJUST_VAW_M	\
	(0x3 << ICE_AQC_EWEM_GENEWIC_ADJUST_VAW_S)
	u8 fwags; /* Speciaw fiewd, wesewved fow some aq cawws */
#define ICE_AQC_EWEM_FWAG_SUSPEND_M		0x1
	stwuct ice_aqc_ewem_info_bw ciw_bw;
	stwuct ice_aqc_ewem_info_bw eiw_bw;
	__we16 sww_id;
	__we16 wesewved2;
};

stwuct ice_aqc_txsched_ewem_data {
	__we32 pawent_teid;
	__we32 node_teid;
	stwuct ice_aqc_txsched_ewem data;
};

stwuct ice_aqc_txsched_topo_gwp_info_hdw {
	__we32 pawent_teid;
	__we16 num_ewems;
	__we16 wesewved2;
};

stwuct ice_aqc_add_ewem {
	stwuct ice_aqc_txsched_topo_gwp_info_hdw hdw;
	stwuct ice_aqc_txsched_ewem_data genewic[];
};

stwuct ice_aqc_get_topo_ewem {
	stwuct ice_aqc_txsched_topo_gwp_info_hdw hdw;
	stwuct ice_aqc_txsched_ewem_data
		genewic[ICE_AQC_TOPO_MAX_WEVEW_NUM];
};

stwuct ice_aqc_dewete_ewem {
	stwuct ice_aqc_txsched_topo_gwp_info_hdw hdw;
	__we32 teid[];
};

/* Quewy Powt ETS (indiwect 0x040E)
 *
 * This indiwect command is used to quewy powt TC node configuwation.
 */
stwuct ice_aqc_quewy_powt_ets {
	__we32 powt_teid;
	__we32 wesewved;
	__we32 addw_high;
	__we32 addw_wow;
};

stwuct ice_aqc_powt_ets_ewem {
	u8 tc_vawid_bits;
	u8 wesewved[3];
	/* 3 bits fow UP pew TC 0-7, 4th byte wesewved */
	__we32 up2tc;
	u8 tc_bw_shawe[8];
	__we32 powt_eiw_pwof_id;
	__we32 powt_ciw_pwof_id;
	/* 3 bits pew Node pwiowity to TC 0-7, 4th byte wesewved */
	__we32 tc_node_pwio;
#define ICE_TC_NODE_PWIO_S	0x4
	u8 wesewved1[4];
	__we32 tc_node_teid[8]; /* Used fow wesponse, wesewved in command */
};

/* Wate wimiting pwofiwe fow
 * Add WW pwofiwe (indiwect 0x0410)
 * Quewy WW pwofiwe (indiwect 0x0411)
 * Wemove WW pwofiwe (indiwect 0x0415)
 * These indiwect commands acts on singwe ow muwtipwe
 * WW pwofiwes with specified data.
 */
stwuct ice_aqc_ww_pwofiwe {
	__we16 num_pwofiwes;
	__we16 num_pwocessed; /* Onwy fow wesponse. Wesewved in Command. */
	u8 wesewved[4];
	__we32 addw_high;
	__we32 addw_wow;
};

stwuct ice_aqc_ww_pwofiwe_ewem {
	u8 wevew;
	u8 fwags;
#define ICE_AQC_WW_PWOFIWE_TYPE_S	0x0
#define ICE_AQC_WW_PWOFIWE_TYPE_M	(0x3 << ICE_AQC_WW_PWOFIWE_TYPE_S)
#define ICE_AQC_WW_PWOFIWE_TYPE_CIW	0
#define ICE_AQC_WW_PWOFIWE_TYPE_EIW	1
#define ICE_AQC_WW_PWOFIWE_TYPE_SWW	2
/* The fowwowing fwag is used fow Quewy WW Pwofiwe Data */
#define ICE_AQC_WW_PWOFIWE_INVAW_S	0x7
#define ICE_AQC_WW_PWOFIWE_INVAW_M	(0x1 << ICE_AQC_WW_PWOFIWE_INVAW_S)

	__we16 pwofiwe_id;
	__we16 max_buwst_size;
	__we16 ww_muwtipwy;
	__we16 wake_up_cawc;
	__we16 ww_encode;
};

/* Quewy Scheduwew Wesouwce Awwocation (indiwect 0x0412)
 * This indiwect command wetwieves the scheduwew wesouwces awwocated by
 * EMP Fiwmwawe to the given PF.
 */
stwuct ice_aqc_quewy_txsched_wes {
	u8 wesewved[8];
	__we32 addw_high;
	__we32 addw_wow;
};

stwuct ice_aqc_genewic_sched_pwops {
	__we16 phys_wevews;
	__we16 wogicaw_wevews;
	u8 fwattening_bitmap;
	u8 max_device_cgds;
	u8 max_pf_cgds;
	u8 wsvd0;
	__we16 wdma_qsets;
	u8 wsvd1[22];
};

stwuct ice_aqc_wayew_pwops {
	u8 wogicaw_wayew;
	u8 chunk_size;
	__we16 max_device_nodes;
	__we16 max_pf_nodes;
	u8 wsvd0[4];
	__we16 max_sibw_gwp_sz;
	__we16 max_ciw_ww_pwofiwes;
	__we16 max_eiw_ww_pwofiwes;
	__we16 max_sww_pwofiwes;
	u8 wsvd1[14];
};

stwuct ice_aqc_quewy_txsched_wes_wesp {
	stwuct ice_aqc_genewic_sched_pwops sched_pwops;
	stwuct ice_aqc_wayew_pwops wayew_pwops[ICE_AQC_TOPO_MAX_WEVEW_NUM];
};

/* Get PHY capabiwities (indiwect 0x0600) */
stwuct ice_aqc_get_phy_caps {
	u8 wpowt_num;
	u8 wesewved;
	__we16 pawam0;
	/* 18.0 - Wepowt quawified moduwes */
#define ICE_AQC_GET_PHY_WQM		BIT(0)
	/* 18.1 - 18.3 : Wepowt mode
	 * 000b - Wepowt NVM capabiwities
	 * 001b - Wepowt topowogy capabiwities
	 * 010b - Wepowt SW configuwed
	 * 100b - Wepowt defauwt capabiwities
	 */
#define ICE_AQC_WEPOWT_MODE_S			1
#define ICE_AQC_WEPOWT_MODE_M			(7 << ICE_AQC_WEPOWT_MODE_S)
#define ICE_AQC_WEPOWT_TOPO_CAP_NO_MEDIA	0
#define ICE_AQC_WEPOWT_TOPO_CAP_MEDIA		BIT(1)
#define ICE_AQC_WEPOWT_ACTIVE_CFG		BIT(2)
#define ICE_AQC_WEPOWT_DFWT_CFG		BIT(3)
	__we32 wesewved1;
	__we32 addw_high;
	__we32 addw_wow;
};

/* This is #define of PHY type (Extended):
 * The fiwst set of defines is fow phy_type_wow.
 */
#define ICE_PHY_TYPE_WOW_100BASE_TX		BIT_UWW(0)
#define ICE_PHY_TYPE_WOW_100M_SGMII		BIT_UWW(1)
#define ICE_PHY_TYPE_WOW_1000BASE_T		BIT_UWW(2)
#define ICE_PHY_TYPE_WOW_1000BASE_SX		BIT_UWW(3)
#define ICE_PHY_TYPE_WOW_1000BASE_WX		BIT_UWW(4)
#define ICE_PHY_TYPE_WOW_1000BASE_KX		BIT_UWW(5)
#define ICE_PHY_TYPE_WOW_1G_SGMII		BIT_UWW(6)
#define ICE_PHY_TYPE_WOW_2500BASE_T		BIT_UWW(7)
#define ICE_PHY_TYPE_WOW_2500BASE_X		BIT_UWW(8)
#define ICE_PHY_TYPE_WOW_2500BASE_KX		BIT_UWW(9)
#define ICE_PHY_TYPE_WOW_5GBASE_T		BIT_UWW(10)
#define ICE_PHY_TYPE_WOW_5GBASE_KW		BIT_UWW(11)
#define ICE_PHY_TYPE_WOW_10GBASE_T		BIT_UWW(12)
#define ICE_PHY_TYPE_WOW_10G_SFI_DA		BIT_UWW(13)
#define ICE_PHY_TYPE_WOW_10GBASE_SW		BIT_UWW(14)
#define ICE_PHY_TYPE_WOW_10GBASE_WW		BIT_UWW(15)
#define ICE_PHY_TYPE_WOW_10GBASE_KW_CW1		BIT_UWW(16)
#define ICE_PHY_TYPE_WOW_10G_SFI_AOC_ACC	BIT_UWW(17)
#define ICE_PHY_TYPE_WOW_10G_SFI_C2C		BIT_UWW(18)
#define ICE_PHY_TYPE_WOW_25GBASE_T		BIT_UWW(19)
#define ICE_PHY_TYPE_WOW_25GBASE_CW		BIT_UWW(20)
#define ICE_PHY_TYPE_WOW_25GBASE_CW_S		BIT_UWW(21)
#define ICE_PHY_TYPE_WOW_25GBASE_CW1		BIT_UWW(22)
#define ICE_PHY_TYPE_WOW_25GBASE_SW		BIT_UWW(23)
#define ICE_PHY_TYPE_WOW_25GBASE_WW		BIT_UWW(24)
#define ICE_PHY_TYPE_WOW_25GBASE_KW		BIT_UWW(25)
#define ICE_PHY_TYPE_WOW_25GBASE_KW_S		BIT_UWW(26)
#define ICE_PHY_TYPE_WOW_25GBASE_KW1		BIT_UWW(27)
#define ICE_PHY_TYPE_WOW_25G_AUI_AOC_ACC	BIT_UWW(28)
#define ICE_PHY_TYPE_WOW_25G_AUI_C2C		BIT_UWW(29)
#define ICE_PHY_TYPE_WOW_40GBASE_CW4		BIT_UWW(30)
#define ICE_PHY_TYPE_WOW_40GBASE_SW4		BIT_UWW(31)
#define ICE_PHY_TYPE_WOW_40GBASE_WW4		BIT_UWW(32)
#define ICE_PHY_TYPE_WOW_40GBASE_KW4		BIT_UWW(33)
#define ICE_PHY_TYPE_WOW_40G_XWAUI_AOC_ACC	BIT_UWW(34)
#define ICE_PHY_TYPE_WOW_40G_XWAUI		BIT_UWW(35)
#define ICE_PHY_TYPE_WOW_50GBASE_CW2		BIT_UWW(36)
#define ICE_PHY_TYPE_WOW_50GBASE_SW2		BIT_UWW(37)
#define ICE_PHY_TYPE_WOW_50GBASE_WW2		BIT_UWW(38)
#define ICE_PHY_TYPE_WOW_50GBASE_KW2		BIT_UWW(39)
#define ICE_PHY_TYPE_WOW_50G_WAUI2_AOC_ACC	BIT_UWW(40)
#define ICE_PHY_TYPE_WOW_50G_WAUI2		BIT_UWW(41)
#define ICE_PHY_TYPE_WOW_50G_AUI2_AOC_ACC	BIT_UWW(42)
#define ICE_PHY_TYPE_WOW_50G_AUI2		BIT_UWW(43)
#define ICE_PHY_TYPE_WOW_50GBASE_CP		BIT_UWW(44)
#define ICE_PHY_TYPE_WOW_50GBASE_SW		BIT_UWW(45)
#define ICE_PHY_TYPE_WOW_50GBASE_FW		BIT_UWW(46)
#define ICE_PHY_TYPE_WOW_50GBASE_WW		BIT_UWW(47)
#define ICE_PHY_TYPE_WOW_50GBASE_KW_PAM4	BIT_UWW(48)
#define ICE_PHY_TYPE_WOW_50G_AUI1_AOC_ACC	BIT_UWW(49)
#define ICE_PHY_TYPE_WOW_50G_AUI1		BIT_UWW(50)
#define ICE_PHY_TYPE_WOW_100GBASE_CW4		BIT_UWW(51)
#define ICE_PHY_TYPE_WOW_100GBASE_SW4		BIT_UWW(52)
#define ICE_PHY_TYPE_WOW_100GBASE_WW4		BIT_UWW(53)
#define ICE_PHY_TYPE_WOW_100GBASE_KW4		BIT_UWW(54)
#define ICE_PHY_TYPE_WOW_100G_CAUI4_AOC_ACC	BIT_UWW(55)
#define ICE_PHY_TYPE_WOW_100G_CAUI4		BIT_UWW(56)
#define ICE_PHY_TYPE_WOW_100G_AUI4_AOC_ACC	BIT_UWW(57)
#define ICE_PHY_TYPE_WOW_100G_AUI4		BIT_UWW(58)
#define ICE_PHY_TYPE_WOW_100GBASE_CW_PAM4	BIT_UWW(59)
#define ICE_PHY_TYPE_WOW_100GBASE_KW_PAM4	BIT_UWW(60)
#define ICE_PHY_TYPE_WOW_100GBASE_CP2		BIT_UWW(61)
#define ICE_PHY_TYPE_WOW_100GBASE_SW2		BIT_UWW(62)
#define ICE_PHY_TYPE_WOW_100GBASE_DW		BIT_UWW(63)
#define ICE_PHY_TYPE_WOW_MAX_INDEX		63
/* The second set of defines is fow phy_type_high. */
#define ICE_PHY_TYPE_HIGH_100GBASE_KW2_PAM4	BIT_UWW(0)
#define ICE_PHY_TYPE_HIGH_100G_CAUI2_AOC_ACC	BIT_UWW(1)
#define ICE_PHY_TYPE_HIGH_100G_CAUI2		BIT_UWW(2)
#define ICE_PHY_TYPE_HIGH_100G_AUI2_AOC_ACC	BIT_UWW(3)
#define ICE_PHY_TYPE_HIGH_100G_AUI2		BIT_UWW(4)
#define ICE_PHY_TYPE_HIGH_200G_CW4_PAM4		BIT_UWW(5)
#define ICE_PHY_TYPE_HIGH_200G_SW4		BIT_UWW(6)
#define ICE_PHY_TYPE_HIGH_200G_FW4		BIT_UWW(7)
#define ICE_PHY_TYPE_HIGH_200G_WW4		BIT_UWW(8)
#define ICE_PHY_TYPE_HIGH_200G_DW4		BIT_UWW(9)
#define ICE_PHY_TYPE_HIGH_200G_KW4_PAM4		BIT_UWW(10)
#define ICE_PHY_TYPE_HIGH_200G_AUI4_AOC_ACC	BIT_UWW(11)
#define ICE_PHY_TYPE_HIGH_200G_AUI4		BIT_UWW(12)
#define ICE_PHY_TYPE_HIGH_MAX_INDEX		12

stwuct ice_aqc_get_phy_caps_data {
	__we64 phy_type_wow; /* Use vawues fwom ICE_PHY_TYPE_WOW_* */
	__we64 phy_type_high; /* Use vawues fwom ICE_PHY_TYPE_HIGH_* */
	u8 caps;
#define ICE_AQC_PHY_EN_TX_WINK_PAUSE			BIT(0)
#define ICE_AQC_PHY_EN_WX_WINK_PAUSE			BIT(1)
#define ICE_AQC_PHY_WOW_POWEW_MODE			BIT(2)
#define ICE_AQC_PHY_EN_WINK				BIT(3)
#define ICE_AQC_PHY_AN_MODE				BIT(4)
#define ICE_AQC_GET_PHY_EN_MOD_QUAW			BIT(5)
#define ICE_AQC_PHY_EN_AUTO_FEC				BIT(7)
#define ICE_AQC_PHY_CAPS_MASK				ICE_M(0xff, 0)
	u8 wow_powew_ctww_an;
#define ICE_AQC_PHY_EN_D3COWD_WOW_POWEW_AUTONEG		BIT(0)
#define ICE_AQC_PHY_AN_EN_CWAUSE28			BIT(1)
#define ICE_AQC_PHY_AN_EN_CWAUSE73			BIT(2)
#define ICE_AQC_PHY_AN_EN_CWAUSE37			BIT(3)
	__we16 eee_cap;
#define ICE_AQC_PHY_EEE_EN_100BASE_TX			BIT(0)
#define ICE_AQC_PHY_EEE_EN_1000BASE_T			BIT(1)
#define ICE_AQC_PHY_EEE_EN_10GBASE_T			BIT(2)
#define ICE_AQC_PHY_EEE_EN_1000BASE_KX			BIT(3)
#define ICE_AQC_PHY_EEE_EN_10GBASE_KW			BIT(4)
#define ICE_AQC_PHY_EEE_EN_25GBASE_KW			BIT(5)
#define ICE_AQC_PHY_EEE_EN_40GBASE_KW4			BIT(6)
	__we16 eeew_vawue;
	u8 phy_id_oui[4]; /* PHY/Moduwe ID connected on the powt */
	u8 phy_fw_vew[8];
	u8 wink_fec_options;
#define ICE_AQC_PHY_FEC_10G_KW_40G_KW4_EN		BIT(0)
#define ICE_AQC_PHY_FEC_10G_KW_40G_KW4_WEQ		BIT(1)
#define ICE_AQC_PHY_FEC_25G_WS_528_WEQ			BIT(2)
#define ICE_AQC_PHY_FEC_25G_KW_WEQ			BIT(3)
#define ICE_AQC_PHY_FEC_25G_WS_544_WEQ			BIT(4)
#define ICE_AQC_PHY_FEC_25G_WS_CWAUSE91_EN		BIT(6)
#define ICE_AQC_PHY_FEC_25G_KW_CWAUSE74_EN		BIT(7)
#define ICE_AQC_PHY_FEC_MASK				ICE_M(0xdf, 0)
	u8 moduwe_compwiance_enfowcement;
#define ICE_AQC_MOD_ENFOWCE_STWICT_MODE			BIT(0)
	u8 extended_compwiance_code;
#define ICE_MODUWE_TYPE_TOTAW_BYTE			3
	u8 moduwe_type[ICE_MODUWE_TYPE_TOTAW_BYTE];
#define ICE_AQC_MOD_TYPE_BYTE0_SFP_PWUS			0xA0
#define ICE_AQC_MOD_TYPE_BYTE0_QSFP_PWUS		0x80
#define ICE_AQC_MOD_TYPE_IDENT				1
#define ICE_AQC_MOD_TYPE_BYTE1_SFP_PWUS_CU_PASSIVE	BIT(0)
#define ICE_AQC_MOD_TYPE_BYTE1_SFP_PWUS_CU_ACTIVE	BIT(1)
#define ICE_AQC_MOD_TYPE_BYTE1_10G_BASE_SW		BIT(4)
#define ICE_AQC_MOD_TYPE_BYTE1_10G_BASE_WW		BIT(5)
#define ICE_AQC_MOD_TYPE_BYTE1_10G_BASE_WWM		BIT(6)
#define ICE_AQC_MOD_TYPE_BYTE1_10G_BASE_EW		BIT(7)
#define ICE_AQC_MOD_TYPE_BYTE2_SFP_PWUS			0xA0
#define ICE_AQC_MOD_TYPE_BYTE2_QSFP_PWUS		0x86
	u8 quawified_moduwe_count;
	u8 wsvd2[7];	/* Bytes 47:41 wesewved */
#define ICE_AQC_QUAW_MOD_COUNT_MAX			16
	stwuct {
		u8 v_oui[3];
		u8 wsvd3;
		u8 v_pawt[16];
		__we32 v_wev;
		__we64 wsvd4;
	} quaw_moduwes[ICE_AQC_QUAW_MOD_COUNT_MAX];
};

/* Set PHY capabiwities (diwect 0x0601)
 * NOTE: This command must be fowwowed by setup wink and westawt auto-neg
 */
stwuct ice_aqc_set_phy_cfg {
	u8 wpowt_num;
	u8 wesewved[7];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Set PHY config command data stwuctuwe */
stwuct ice_aqc_set_phy_cfg_data {
	__we64 phy_type_wow; /* Use vawues fwom ICE_PHY_TYPE_WOW_* */
	__we64 phy_type_high; /* Use vawues fwom ICE_PHY_TYPE_HIGH_* */
	u8 caps;
#define ICE_AQ_PHY_ENA_VAWID_MASK	ICE_M(0xef, 0)
#define ICE_AQ_PHY_ENA_TX_PAUSE_ABIWITY	BIT(0)
#define ICE_AQ_PHY_ENA_WX_PAUSE_ABIWITY	BIT(1)
#define ICE_AQ_PHY_ENA_WOW_POWEW	BIT(2)
#define ICE_AQ_PHY_ENA_WINK		BIT(3)
#define ICE_AQ_PHY_ENA_AUTO_WINK_UPDT	BIT(5)
#define ICE_AQ_PHY_ENA_WESM		BIT(6)
#define ICE_AQ_PHY_ENA_AUTO_FEC		BIT(7)
	u8 wow_powew_ctww_an;
	__we16 eee_cap; /* Vawue fwom ice_aqc_get_phy_caps */
	__we16 eeew_vawue;
	u8 wink_fec_opt; /* Use defines fwom ice_aqc_get_phy_caps */
	u8 moduwe_compwiance_enfowcement;
};

/* Set MAC Config command data stwuctuwe (diwect 0x0603) */
stwuct ice_aqc_set_mac_cfg {
	__we16 max_fwame_size;
	u8 pawams;
#define ICE_AQ_SET_MAC_PACE_S		3
#define ICE_AQ_SET_MAC_PACE_M		(0xF << ICE_AQ_SET_MAC_PACE_S)
#define ICE_AQ_SET_MAC_PACE_TYPE_M	BIT(7)
#define ICE_AQ_SET_MAC_PACE_TYPE_WATE	0
#define ICE_AQ_SET_MAC_PACE_TYPE_FIXED	ICE_AQ_SET_MAC_PACE_TYPE_M
	u8 tx_tmw_pwiowity;
	__we16 tx_tmw_vawue;
	__we16 fc_wefwesh_thweshowd;
	u8 dwop_opts;
#define ICE_AQ_SET_MAC_AUTO_DWOP_MASK		BIT(0)
#define ICE_AQ_SET_MAC_AUTO_DWOP_NONE		0
#define ICE_AQ_SET_MAC_AUTO_DWOP_BWOCKING_PKTS	BIT(0)
	u8 wesewved[7];
};

/* Westawt AN command data stwuctuwe (diwect 0x0605)
 * Awso used fow wesponse, with onwy the wpowt_num fiewd pwesent.
 */
stwuct ice_aqc_westawt_an {
	u8 wpowt_num;
	u8 wesewved;
	u8 cmd_fwags;
#define ICE_AQC_WESTAWT_AN_WINK_WESTAWT	BIT(1)
#define ICE_AQC_WESTAWT_AN_WINK_ENABWE	BIT(2)
	u8 wesewved2[13];
};

/* Get wink status (indiwect 0x0607), awso used fow Wink Status Event */
stwuct ice_aqc_get_wink_status {
	u8 wpowt_num;
	u8 wesewved;
	__we16 cmd_fwags;
#define ICE_AQ_WSE_M			0x3
#define ICE_AQ_WSE_NOP			0x0
#define ICE_AQ_WSE_DIS			0x2
#define ICE_AQ_WSE_ENA			0x3
	/* onwy wesponse uses this fwag */
#define ICE_AQ_WSE_IS_ENABWED		0x1
	__we32 wesewved2;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Get wink status wesponse data stwuctuwe, awso used fow Wink Status Event */
stwuct ice_aqc_get_wink_status_data {
	u8 topo_media_confwict;
#define ICE_AQ_WINK_TOPO_CONFWICT	BIT(0)
#define ICE_AQ_WINK_MEDIA_CONFWICT	BIT(1)
#define ICE_AQ_WINK_TOPO_COWWUPT	BIT(2)
#define ICE_AQ_WINK_TOPO_UNWEACH_PWT	BIT(4)
#define ICE_AQ_WINK_TOPO_UNDWUTIW_PWT	BIT(5)
#define ICE_AQ_WINK_TOPO_UNDWUTIW_MEDIA	BIT(6)
#define ICE_AQ_WINK_TOPO_UNSUPP_MEDIA	BIT(7)
	u8 wink_cfg_eww;
#define ICE_AQ_WINK_MODUWE_POWEW_UNSUPPOWTED	BIT(5)
#define ICE_AQ_WINK_EXTEWNAW_PHY_WOAD_FAIWUWE	BIT(6)
#define ICE_AQ_WINK_INVAW_MAX_POWEW_WIMIT	BIT(7)
	u8 wink_info;
#define ICE_AQ_WINK_UP			BIT(0)	/* Wink Status */
#define ICE_AQ_WINK_FAUWT		BIT(1)
#define ICE_AQ_WINK_FAUWT_TX		BIT(2)
#define ICE_AQ_WINK_FAUWT_WX		BIT(3)
#define ICE_AQ_WINK_FAUWT_WEMOTE	BIT(4)
#define ICE_AQ_WINK_UP_POWT		BIT(5)	/* Extewnaw Powt Wink Status */
#define ICE_AQ_MEDIA_AVAIWABWE		BIT(6)
#define ICE_AQ_SIGNAW_DETECT		BIT(7)
	u8 an_info;
#define ICE_AQ_AN_COMPWETED		BIT(0)
#define ICE_AQ_WP_AN_ABIWITY		BIT(1)
#define ICE_AQ_PD_FAUWT			BIT(2)	/* Pawawwew Detection Fauwt */
#define ICE_AQ_FEC_EN			BIT(3)
#define ICE_AQ_PHY_WOW_POWEW		BIT(4)	/* Wow Powew State */
#define ICE_AQ_WINK_PAUSE_TX		BIT(5)
#define ICE_AQ_WINK_PAUSE_WX		BIT(6)
#define ICE_AQ_QUAWIFIED_MODUWE		BIT(7)
	u8 ext_info;
#define ICE_AQ_WINK_PHY_TEMP_AWAWM	BIT(0)
#define ICE_AQ_WINK_EXCESSIVE_EWWOWS	BIT(1)	/* Excessive Wink Ewwows */
	/* Powt Tx Suspended */
#define ICE_AQ_WINK_TX_S		2
#define ICE_AQ_WINK_TX_M		(0x03 << ICE_AQ_WINK_TX_S)
#define ICE_AQ_WINK_TX_ACTIVE		0
#define ICE_AQ_WINK_TX_DWAINED		1
#define ICE_AQ_WINK_TX_FWUSHED		3
	u8 wesewved2;
	__we16 max_fwame_size;
	u8 cfg;
#define ICE_AQ_WINK_25G_KW_FEC_EN	BIT(0)
#define ICE_AQ_WINK_25G_WS_528_FEC_EN	BIT(1)
#define ICE_AQ_WINK_25G_WS_544_FEC_EN	BIT(2)
#define ICE_AQ_FEC_MASK			ICE_M(0x7, 0)
	/* Pacing Config */
#define ICE_AQ_CFG_PACING_S		3
#define ICE_AQ_CFG_PACING_M		(0xF << ICE_AQ_CFG_PACING_S)
#define ICE_AQ_CFG_PACING_TYPE_M	BIT(7)
#define ICE_AQ_CFG_PACING_TYPE_AVG	0
#define ICE_AQ_CFG_PACING_TYPE_FIXED	ICE_AQ_CFG_PACING_TYPE_M
	/* Extewnaw Device Powew Abiwity */
	u8 powew_desc;
#define ICE_AQ_PWW_CWASS_M		0x3F
#define ICE_AQ_WINK_PWW_BASET_WOW_HIGH	0
#define ICE_AQ_WINK_PWW_BASET_HIGH	1
#define ICE_AQ_WINK_PWW_QSFP_CWASS_1	0
#define ICE_AQ_WINK_PWW_QSFP_CWASS_2	1
#define ICE_AQ_WINK_PWW_QSFP_CWASS_3	2
#define ICE_AQ_WINK_PWW_QSFP_CWASS_4	3
	__we16 wink_speed;
#define ICE_AQ_WINK_SPEED_M		0x7FF
#define ICE_AQ_WINK_SPEED_10MB		BIT(0)
#define ICE_AQ_WINK_SPEED_100MB		BIT(1)
#define ICE_AQ_WINK_SPEED_1000MB	BIT(2)
#define ICE_AQ_WINK_SPEED_2500MB	BIT(3)
#define ICE_AQ_WINK_SPEED_5GB		BIT(4)
#define ICE_AQ_WINK_SPEED_10GB		BIT(5)
#define ICE_AQ_WINK_SPEED_20GB		BIT(6)
#define ICE_AQ_WINK_SPEED_25GB		BIT(7)
#define ICE_AQ_WINK_SPEED_40GB		BIT(8)
#define ICE_AQ_WINK_SPEED_50GB		BIT(9)
#define ICE_AQ_WINK_SPEED_100GB		BIT(10)
#define ICE_AQ_WINK_SPEED_200GB		BIT(11)
#define ICE_AQ_WINK_SPEED_UNKNOWN	BIT(15)
	/* Awigns next fiewd to 8-byte boundawy */
	__we16 wesewved3;
	u8 ext_fec_status;
	/* WS 272 FEC enabwed */
#define ICE_AQ_WINK_WS_272_FEC_EN      BIT(0)
	u8 wesewved4;
	/* Use vawues fwom ICE_PHY_TYPE_WOW_* */
	__we64 phy_type_wow;
	/* Use vawues fwom ICE_PHY_TYPE_HIGH_* */
	__we64 phy_type_high;
#define ICE_AQC_WS_DATA_SIZE_V1 \
	offsetofend(stwuct ice_aqc_get_wink_status_data, phy_type_high)
	/* Get wink status v2 wink pawtnew data */
	__we64 wp_phy_type_wow;
	__we64 wp_phy_type_high;
	u8 wp_fec_adv;
#define ICE_AQ_WINK_WP_10G_KW_FEC_CAP  BIT(0)
#define ICE_AQ_WINK_WP_25G_KW_FEC_CAP  BIT(1)
#define ICE_AQ_WINK_WP_WS_528_FEC_CAP  BIT(2)
#define ICE_AQ_WINK_WP_50G_KW_272_FEC_CAP BIT(3)
#define ICE_AQ_WINK_WP_100G_KW_272_FEC_CAP BIT(4)
#define ICE_AQ_WINK_WP_200G_KW_272_FEC_CAP BIT(5)
	u8 wp_fec_weq;
#define ICE_AQ_WINK_WP_10G_KW_FEC_WEQ  BIT(0)
#define ICE_AQ_WINK_WP_25G_KW_FEC_WEQ  BIT(1)
#define ICE_AQ_WINK_WP_WS_528_FEC_WEQ  BIT(2)
#define ICE_AQ_WINK_WP_KW_272_FEC_WEQ  BIT(3)
	u8 wp_fwowcontwow;
#define ICE_AQ_WINK_WP_PAUSE_ADV       BIT(0)
#define ICE_AQ_WINK_WP_ASM_DIW_ADV     BIT(1)
	u8 wesewved5[5];
#define ICE_AQC_WS_DATA_SIZE_V2 \
	offsetofend(stwuct ice_aqc_get_wink_status_data, wesewved5)
} __packed;

/* Set event mask command (diwect 0x0613) */
stwuct ice_aqc_set_event_mask {
	u8	wpowt_num;
	u8	wesewved[7];
	__we16	event_mask;
#define ICE_AQ_WINK_EVENT_UPDOWN		BIT(1)
#define ICE_AQ_WINK_EVENT_MEDIA_NA		BIT(2)
#define ICE_AQ_WINK_EVENT_WINK_FAUWT		BIT(3)
#define ICE_AQ_WINK_EVENT_PHY_TEMP_AWAWM	BIT(4)
#define ICE_AQ_WINK_EVENT_EXCESSIVE_EWWOWS	BIT(5)
#define ICE_AQ_WINK_EVENT_SIGNAW_DETECT		BIT(6)
#define ICE_AQ_WINK_EVENT_AN_COMPWETED		BIT(7)
#define ICE_AQ_WINK_EVENT_MODUWE_QUAW_FAIW	BIT(8)
#define ICE_AQ_WINK_EVENT_POWT_TX_SUSPENDED	BIT(9)
#define ICE_AQ_WINK_EVENT_PHY_FW_WOAD_FAIW	BIT(12)
	u8	wesewved1[6];
};

/* Set MAC Woopback command (diwect 0x0620) */
stwuct ice_aqc_set_mac_wb {
	u8 wb_mode;
#define ICE_AQ_MAC_WB_EN		BIT(0)
#define ICE_AQ_MAC_WB_OSC_CWK		BIT(1)
	u8 wesewved[15];
};

/* Set PHY wecovewed cwock output (diwect 0x0630) */
stwuct ice_aqc_set_phy_wec_cwk_out {
	u8 phy_output;
	u8 powt_num;
#define ICE_AQC_SET_PHY_WEC_CWK_OUT_CUWW_POWT	0xFF
	u8 fwags;
#define ICE_AQC_SET_PHY_WEC_CWK_OUT_OUT_EN	BIT(0)
	u8 wsvd;
	__we32 fweq;
	u8 wsvd2[6];
	__we16 node_handwe;
};

/* Get PHY wecovewed cwock output (diwect 0x0631) */
stwuct ice_aqc_get_phy_wec_cwk_out {
	u8 phy_output;
	u8 powt_num;
#define ICE_AQC_GET_PHY_WEC_CWK_OUT_CUWW_POWT	0xFF
	u8 fwags;
#define ICE_AQC_GET_PHY_WEC_CWK_OUT_OUT_EN	BIT(0)
	u8 wsvd[11];
	__we16 node_handwe;
};

/* Get sensow weading (diwect 0x0632) */
stwuct ice_aqc_get_sensow_weading {
	u8 sensow;
	u8 fowmat;
	u8 wesewved[6];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Get sensow weading wesponse (diwect 0x0632) */
stwuct ice_aqc_get_sensow_weading_wesp {
	union {
		u8 waw[8];
		/* Output data fow sensow 0x00, fowmat 0x00 */
		stwuct _packed {
			s8 temp;
			u8 temp_wawning_thweshowd;
			u8 temp_cwiticaw_thweshowd;
			u8 temp_fataw_thweshowd;
			u8 wesewved[4];
		} s0f0;
	} data;
};

stwuct ice_aqc_wink_topo_pawams {
	u8 wpowt_num;
	u8 wpowt_num_vawid;
#define ICE_AQC_WINK_TOPO_POWT_NUM_VAWID	BIT(0)
	u8 node_type_ctx;
#define ICE_AQC_WINK_TOPO_NODE_TYPE_S		0
#define ICE_AQC_WINK_TOPO_NODE_TYPE_M	(0xF << ICE_AQC_WINK_TOPO_NODE_TYPE_S)
#define ICE_AQC_WINK_TOPO_NODE_TYPE_PHY		0
#define ICE_AQC_WINK_TOPO_NODE_TYPE_GPIO_CTWW	1
#define ICE_AQC_WINK_TOPO_NODE_TYPE_MUX_CTWW	2
#define ICE_AQC_WINK_TOPO_NODE_TYPE_WED_CTWW	3
#define ICE_AQC_WINK_TOPO_NODE_TYPE_WED		4
#define ICE_AQC_WINK_TOPO_NODE_TYPE_THEWMAW	5
#define ICE_AQC_WINK_TOPO_NODE_TYPE_CAGE	6
#define ICE_AQC_WINK_TOPO_NODE_TYPE_MEZZ	7
#define ICE_AQC_WINK_TOPO_NODE_TYPE_ID_EEPWOM	8
#define ICE_AQC_WINK_TOPO_NODE_TYPE_CWK_CTWW	9
#define ICE_AQC_WINK_TOPO_NODE_TYPE_CWK_MUX	10
#define ICE_AQC_WINK_TOPO_NODE_TYPE_GPS		11
#define ICE_AQC_WINK_TOPO_NODE_CTX_S		4
#define ICE_AQC_WINK_TOPO_NODE_CTX_M		\
				(0xF << ICE_AQC_WINK_TOPO_NODE_CTX_S)
#define ICE_AQC_WINK_TOPO_NODE_CTX_GWOBAW	0
#define ICE_AQC_WINK_TOPO_NODE_CTX_BOAWD	1
#define ICE_AQC_WINK_TOPO_NODE_CTX_POWT		2
#define ICE_AQC_WINK_TOPO_NODE_CTX_NODE		3
#define ICE_AQC_WINK_TOPO_NODE_CTX_PWOVIDED	4
#define ICE_AQC_WINK_TOPO_NODE_CTX_OVEWWIDE	5
	u8 index;
};

stwuct ice_aqc_wink_topo_addw {
	stwuct ice_aqc_wink_topo_pawams topo_pawams;
	__we16 handwe;
#define ICE_AQC_WINK_TOPO_HANDWE_S	0
#define ICE_AQC_WINK_TOPO_HANDWE_M	(0x3FF << ICE_AQC_WINK_TOPO_HANDWE_S)
/* Used to decode the handwe fiewd */
#define ICE_AQC_WINK_TOPO_HANDWE_BWD_TYPE_M	BIT(9)
#define ICE_AQC_WINK_TOPO_HANDWE_BWD_TYPE_WOM	BIT(9)
#define ICE_AQC_WINK_TOPO_HANDWE_BWD_TYPE_MEZZ	0
#define ICE_AQC_WINK_TOPO_HANDWE_NODE_S		0
/* In case of a Mezzanine type */
#define ICE_AQC_WINK_TOPO_HANDWE_MEZZ_NODE_M	\
				(0x3F << ICE_AQC_WINK_TOPO_HANDWE_NODE_S)
#define ICE_AQC_WINK_TOPO_HANDWE_MEZZ_S	6
#define ICE_AQC_WINK_TOPO_HANDWE_MEZZ_M	(0x7 << ICE_AQC_WINK_TOPO_HANDWE_MEZZ_S)
/* In case of a WOM type */
#define ICE_AQC_WINK_TOPO_HANDWE_WOM_NODE_M	\
				(0x1FF << ICE_AQC_WINK_TOPO_HANDWE_NODE_S)
};

/* Get Wink Topowogy Handwe (diwect, 0x06E0) */
stwuct ice_aqc_get_wink_topo {
	stwuct ice_aqc_wink_topo_addw addw;
	u8 node_pawt_num;
#define ICE_AQC_GET_WINK_TOPO_NODE_NW_PCA9575		0x21
#define ICE_AQC_GET_WINK_TOPO_NODE_NW_ZW30632_80032	0x24
#define ICE_AQC_GET_WINK_TOPO_NODE_NW_SI5383_5384	0x25
#define ICE_AQC_GET_WINK_TOPO_NODE_NW_E822_PHY		0x30
#define ICE_AQC_GET_WINK_TOPO_NODE_NW_C827		0x31
#define ICE_AQC_GET_WINK_TOPO_NODE_NW_GEN_CWK_MUX	0x47
#define ICE_AQC_GET_WINK_TOPO_NODE_NW_GEN_GPS		0x48
	u8 wsvd[9];
};

/* Wead/Wwite I2C (diwect, 0x06E2/0x06E3) */
stwuct ice_aqc_i2c {
	stwuct ice_aqc_wink_topo_addw topo_addw;
	__we16 i2c_addw;
	u8 i2c_pawams;
#define ICE_AQC_I2C_DATA_SIZE_M		GENMASK(3, 0)
#define ICE_AQC_I2C_USE_WEPEATED_STAWT	BIT(7)

	u8 wsvd;
	__we16 i2c_bus_addw;
	u8 i2c_data[4]; /* Used onwy by wwite command, wesewved in wead. */
};

/* Wead I2C Wesponse (diwect, 0x06E2) */
stwuct ice_aqc_wead_i2c_wesp {
	u8 i2c_data[16];
};

/* Set Powt Identification WED (diwect, 0x06E9) */
stwuct ice_aqc_set_powt_id_wed {
	u8 wpowt_num;
	u8 wpowt_num_vawid;
	u8 ident_mode;
#define ICE_AQC_POWT_IDENT_WED_BWINK	BIT(0)
#define ICE_AQC_POWT_IDENT_WED_OWIG	0
	u8 wsvd[13];
};

/* Get Powt Options (indiwect, 0x06EA) */
stwuct ice_aqc_get_powt_options {
	u8 wpowt_num;
	u8 wpowt_num_vawid;
	u8 powt_options_count;
#define ICE_AQC_POWT_OPT_COUNT_M	GENMASK(3, 0)
#define ICE_AQC_POWT_OPT_MAX		16

	u8 innewmost_phy_index;
	u8 powt_options;
#define ICE_AQC_POWT_OPT_ACTIVE_M	GENMASK(3, 0)
#define ICE_AQC_POWT_OPT_VAWID		BIT(7)

	u8 pending_powt_option_status;
#define ICE_AQC_PENDING_POWT_OPT_IDX_M	GENMASK(3, 0)
#define ICE_AQC_PENDING_POWT_OPT_VAWID	BIT(7)

	u8 wsvd[2];
	__we32 addw_high;
	__we32 addw_wow;
};

stwuct ice_aqc_get_powt_options_ewem {
	u8 pmd;
#define ICE_AQC_POWT_OPT_PMD_COUNT_M	GENMASK(3, 0)

	u8 max_wane_speed;
#define ICE_AQC_POWT_OPT_MAX_WANE_M	GENMASK(3, 0)
#define ICE_AQC_POWT_OPT_MAX_WANE_100M	0
#define ICE_AQC_POWT_OPT_MAX_WANE_1G	1
#define ICE_AQC_POWT_OPT_MAX_WANE_2500M	2
#define ICE_AQC_POWT_OPT_MAX_WANE_5G	3
#define ICE_AQC_POWT_OPT_MAX_WANE_10G	4
#define ICE_AQC_POWT_OPT_MAX_WANE_25G	5
#define ICE_AQC_POWT_OPT_MAX_WANE_50G	6
#define ICE_AQC_POWT_OPT_MAX_WANE_100G	7

	u8 gwobaw_scid[2];
	u8 phy_scid[2];
	u8 pf2powt_cid[2];
};

/* Set Powt Option (diwect, 0x06EB) */
stwuct ice_aqc_set_powt_option {
	u8 wpowt_num;
	u8 wpowt_num_vawid;
	u8 sewected_powt_option;
	u8 wsvd[13];
};

/* Set/Get GPIO (diwect, 0x06EC/0x06ED) */
stwuct ice_aqc_gpio {
	__we16 gpio_ctww_handwe;
#define ICE_AQC_GPIO_HANDWE_S	0
#define ICE_AQC_GPIO_HANDWE_M	(0x3FF << ICE_AQC_GPIO_HANDWE_S)
	u8 gpio_num;
	u8 gpio_vaw;
	u8 wsvd[12];
};

/* Wead/Wwite SFF EEPWOM command (indiwect 0x06EE) */
stwuct ice_aqc_sff_eepwom {
	u8 wpowt_num;
	u8 wpowt_num_vawid;
#define ICE_AQC_SFF_POWT_NUM_VAWID	BIT(0)
	__we16 i2c_bus_addw;
#define ICE_AQC_SFF_I2CBUS_7BIT_M	0x7F
#define ICE_AQC_SFF_I2CBUS_10BIT_M	0x3FF
#define ICE_AQC_SFF_I2CBUS_TYPE_M	BIT(10)
#define ICE_AQC_SFF_I2CBUS_TYPE_7BIT	0
#define ICE_AQC_SFF_I2CBUS_TYPE_10BIT	ICE_AQC_SFF_I2CBUS_TYPE_M
#define ICE_AQC_SFF_SET_EEPWOM_PAGE_S	11
#define ICE_AQC_SFF_SET_EEPWOM_PAGE_M	(0x3 << ICE_AQC_SFF_SET_EEPWOM_PAGE_S)
#define ICE_AQC_SFF_NO_PAGE_CHANGE	0
#define ICE_AQC_SFF_SET_23_ON_MISMATCH	1
#define ICE_AQC_SFF_SET_22_ON_MISMATCH	2
#define ICE_AQC_SFF_IS_WWITE		BIT(15)
	__we16 i2c_mem_addw;
	__we16 eepwom_page;
#define  ICE_AQC_SFF_EEPWOM_BANK_S 0
#define  ICE_AQC_SFF_EEPWOM_BANK_M (0xFF << ICE_AQC_SFF_EEPWOM_BANK_S)
#define  ICE_AQC_SFF_EEPWOM_PAGE_S 8
#define  ICE_AQC_SFF_EEPWOM_PAGE_M (0xFF << ICE_AQC_SFF_EEPWOM_PAGE_S)
	__we32 addw_high;
	__we32 addw_wow;
};

/* NVM Wead command (indiwect 0x0701)
 * NVM Ewase commands (diwect 0x0702)
 * NVM Update commands (indiwect 0x0703)
 */
stwuct ice_aqc_nvm {
#define ICE_AQC_NVM_MAX_OFFSET		0xFFFFFF
	__we16 offset_wow;
	u8 offset_high;
	u8 cmd_fwags;
#define ICE_AQC_NVM_WAST_CMD		BIT(0)
#define ICE_AQC_NVM_PCIW_WEQ		BIT(0)	/* Used by NVM Update wepwy */
#define ICE_AQC_NVM_PWESEWVATION_S	1
#define ICE_AQC_NVM_PWESEWVATION_M	(3 << ICE_AQC_NVM_PWESEWVATION_S)
#define ICE_AQC_NVM_NO_PWESEWVATION	(0 << ICE_AQC_NVM_PWESEWVATION_S)
#define ICE_AQC_NVM_PWESEWVE_AWW	BIT(1)
#define ICE_AQC_NVM_FACTOWY_DEFAUWT	(2 << ICE_AQC_NVM_PWESEWVATION_S)
#define ICE_AQC_NVM_PWESEWVE_SEWECTED	(3 << ICE_AQC_NVM_PWESEWVATION_S)
#define ICE_AQC_NVM_ACTIV_SEW_NVM	BIT(3) /* Wwite Activate/SW Dump onwy */
#define ICE_AQC_NVM_ACTIV_SEW_OWOM	BIT(4)
#define ICE_AQC_NVM_ACTIV_SEW_NETWIST	BIT(5)
#define ICE_AQC_NVM_SPECIAW_UPDATE	BIT(6)
#define ICE_AQC_NVM_WEVEWT_WAST_ACTIV	BIT(6) /* Wwite Activate onwy */
#define ICE_AQC_NVM_ACTIV_SEW_MASK	ICE_M(0x7, 3)
#define ICE_AQC_NVM_FWASH_ONWY		BIT(7)
#define ICE_AQC_NVM_WESET_WVW_M		ICE_M(0x3, 0) /* Wwite wepwy onwy */
#define ICE_AQC_NVM_POW_FWAG		0
#define ICE_AQC_NVM_PEWST_FWAG		1
#define ICE_AQC_NVM_EMPW_FWAG		2
#define ICE_AQC_NVM_EMPW_ENA		BIT(0) /* Wwite Activate wepwy onwy */
	/* Fow Wwite Activate, sevewaw fwags awe sent as pawt of a sepawate
	 * fwags2 fiewd using a sepawate byte. Fow simpwicity of the softwawe
	 * intewface, we pass the fwags as a 16 bit vawue so these fwags awe
	 * aww offset by 8 bits
	 */
#define ICE_AQC_NVM_ACTIV_WEQ_EMPW	BIT(8) /* NVM Wwite Activate onwy */
	__we16 moduwe_typeid;
	__we16 wength;
#define ICE_AQC_NVM_EWASE_WEN	0xFFFF
	__we32 addw_high;
	__we32 addw_wow;
};

#define ICE_AQC_NVM_STAWT_POINT			0

/* NVM Checksum Command (diwect, 0x0706) */
stwuct ice_aqc_nvm_checksum {
	u8 fwags;
#define ICE_AQC_NVM_CHECKSUM_VEWIFY	BIT(0)
#define ICE_AQC_NVM_CHECKSUM_WECAWC	BIT(1)
	u8 wsvd;
	__we16 checksum; /* Used onwy by wesponse */
#define ICE_AQC_NVM_CHECKSUM_COWWECT	0xBABA
	u8 wsvd2[12];
};

/* Used fow NVM Set Package Data command - 0x070A */
stwuct ice_aqc_nvm_pkg_data {
	u8 wesewved[3];
	u8 cmd_fwags;
#define ICE_AQC_NVM_PKG_DEWETE		BIT(0) /* used fow command caww */
#define ICE_AQC_NVM_PKG_SKIPPED		BIT(0) /* used fow command wesponse */

	u32 wesewved1;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Used fow Pass Component Tabwe command - 0x070B */
stwuct ice_aqc_nvm_pass_comp_tbw {
	u8 component_wesponse; /* Wesponse onwy */
#define ICE_AQ_NVM_PASS_COMP_CAN_BE_UPDATED		0x0
#define ICE_AQ_NVM_PASS_COMP_CAN_MAY_BE_UPDATEABWE	0x1
#define ICE_AQ_NVM_PASS_COMP_CAN_NOT_BE_UPDATED		0x2
	u8 component_wesponse_code; /* Wesponse onwy */
#define ICE_AQ_NVM_PASS_COMP_CAN_BE_UPDATED_CODE	0x0
#define ICE_AQ_NVM_PASS_COMP_STAMP_IDENTICAW_CODE	0x1
#define ICE_AQ_NVM_PASS_COMP_STAMP_WOWEW		0x2
#define ICE_AQ_NVM_PASS_COMP_INVAWID_STAMP_CODE		0x3
#define ICE_AQ_NVM_PASS_COMP_CONFWICT_CODE		0x4
#define ICE_AQ_NVM_PASS_COMP_PWE_WEQ_NOT_MET_CODE	0x5
#define ICE_AQ_NVM_PASS_COMP_NOT_SUPPOWTED_CODE		0x6
#define ICE_AQ_NVM_PASS_COMP_CANNOT_DOWNGWADE_CODE	0x7
#define ICE_AQ_NVM_PASS_COMP_INCOMPWETE_IMAGE_CODE	0x8
#define ICE_AQ_NVM_PASS_COMP_VEW_STW_IDENTICAW_CODE	0xA
#define ICE_AQ_NVM_PASS_COMP_VEW_STW_WOWEW_CODE		0xB
	u8 wesewved;
	u8 twansfew_fwag;
#define ICE_AQ_NVM_PASS_COMP_TBW_STAWT			0x1
#define ICE_AQ_NVM_PASS_COMP_TBW_MIDDWE			0x2
#define ICE_AQ_NVM_PASS_COMP_TBW_END			0x4
#define ICE_AQ_NVM_PASS_COMP_TBW_STAWT_AND_END		0x5
	__we32 wesewved1;
	__we32 addw_high;
	__we32 addw_wow;
};

stwuct ice_aqc_nvm_comp_tbw {
	__we16 comp_cwass;
#define NVM_COMP_CWASS_AWW_FW	0x000A

	__we16 comp_id;
#define NVM_COMP_ID_OWOM	0x5
#define NVM_COMP_ID_NVM		0x6
#define NVM_COMP_ID_NETWIST	0x8

	u8 comp_cwass_idx;
#define FWU_COMP_CWASS_IDX_NOT_USE 0x0

	__we32 comp_cmp_stamp;
	u8 cvs_type;
#define NVM_CVS_TYPE_ASCII	0x1

	u8 cvs_wen;
	u8 cvs[]; /* Component Vewsion Stwing */
} __packed;

/* Send to PF command (indiwect 0x0801) ID is onwy used by PF
 *
 * Send to VF command (indiwect 0x0802) ID is onwy used by PF
 *
 */
stwuct ice_aqc_pf_vf_msg {
	__we32 id;
	u32 wesewved;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Get WWDP MIB (indiwect 0x0A00)
 * Note: This is awso used by the WWDP MIB Change Event (0x0A01)
 * as the fowmat is the same.
 */
stwuct ice_aqc_wwdp_get_mib {
	u8 type;
#define ICE_AQ_WWDP_MIB_TYPE_S			0
#define ICE_AQ_WWDP_MIB_TYPE_M			(0x3 << ICE_AQ_WWDP_MIB_TYPE_S)
#define ICE_AQ_WWDP_MIB_WOCAW			0
#define ICE_AQ_WWDP_MIB_WEMOTE			1
#define ICE_AQ_WWDP_MIB_WOCAW_AND_WEMOTE	2
#define ICE_AQ_WWDP_BWID_TYPE_S			2
#define ICE_AQ_WWDP_BWID_TYPE_M			(0x3 << ICE_AQ_WWDP_BWID_TYPE_S)
#define ICE_AQ_WWDP_BWID_TYPE_NEAWEST_BWID	0
#define ICE_AQ_WWDP_BWID_TYPE_NON_TPMW		1
/* Tx pause fwags in the 0xA01 event use ICE_AQ_WWDP_TX_* */
#define ICE_AQ_WWDP_TX_S			0x4
#define ICE_AQ_WWDP_TX_M			(0x03 << ICE_AQ_WWDP_TX_S)
#define ICE_AQ_WWDP_TX_ACTIVE			0
#define ICE_AQ_WWDP_TX_SUSPENDED		1
#define ICE_AQ_WWDP_TX_FWUSHED			3
/* DCBX mode */
#define ICE_AQ_WWDP_DCBX_M			GENMASK(7, 6)
#define ICE_AQ_WWDP_DCBX_NA			0
#define ICE_AQ_WWDP_DCBX_CEE			1
#define ICE_AQ_WWDP_DCBX_IEEE			2

	u8 state;
#define ICE_AQ_WWDP_MIB_CHANGE_STATE_M		BIT(0)
#define ICE_AQ_WWDP_MIB_CHANGE_EXECUTED		0
#define ICE_AQ_WWDP_MIB_CHANGE_PENDING		1

/* The fowwowing bytes awe wesewved fow the Get WWDP MIB command (0x0A00)
 * and in the WWDP MIB Change Event (0x0A01). They awe vawid fow the
 * Get WWDP MIB (0x0A00) wesponse onwy.
 */
	__we16 wocaw_wen;
	__we16 wemote_wen;
	u8 wesewved[2];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Configuwe WWDP MIB Change Event (diwect 0x0A01) */
/* Fow MIB Change Event use ice_aqc_wwdp_get_mib stwuctuwe above */
stwuct ice_aqc_wwdp_set_mib_change {
	u8 command;
#define ICE_AQ_WWDP_MIB_UPDATE_ENABWE		0x0
#define ICE_AQ_WWDP_MIB_UPDATE_DIS		0x1
#define ICE_AQ_WWDP_MIB_PENDING_M		BIT(1)
#define ICE_AQ_WWDP_MIB_PENDING_DISABWE		0
#define ICE_AQ_WWDP_MIB_PENDING_ENABWE		1
	u8 wesewved[15];
};

/* Stop WWDP (diwect 0x0A05) */
stwuct ice_aqc_wwdp_stop {
	u8 command;
#define ICE_AQ_WWDP_AGENT_STATE_MASK	BIT(0)
#define ICE_AQ_WWDP_AGENT_STOP		0x0
#define ICE_AQ_WWDP_AGENT_SHUTDOWN	ICE_AQ_WWDP_AGENT_STATE_MASK
#define ICE_AQ_WWDP_AGENT_PEWSIST_DIS	BIT(1)
	u8 wesewved[15];
};

/* Stawt WWDP (diwect 0x0A06) */
stwuct ice_aqc_wwdp_stawt {
	u8 command;
#define ICE_AQ_WWDP_AGENT_STAWT		BIT(0)
#define ICE_AQ_WWDP_AGENT_PEWSIST_ENA	BIT(1)
	u8 wesewved[15];
};

/* Get CEE DCBX Opew Config (0x0A07)
 * The command uses the genewic descwiptow stwuct and
 * wetuwns the stwuct bewow as an indiwect wesponse.
 */
stwuct ice_aqc_get_cee_dcb_cfg_wesp {
	u8 opew_num_tc;
	u8 opew_pwio_tc[4];
	u8 opew_tc_bw[8];
	u8 opew_pfc_en;
	__we16 opew_app_pwio;
#define ICE_AQC_CEE_APP_FCOE_S		0
#define ICE_AQC_CEE_APP_FCOE_M		(0x7 << ICE_AQC_CEE_APP_FCOE_S)
#define ICE_AQC_CEE_APP_ISCSI_S		3
#define ICE_AQC_CEE_APP_ISCSI_M		(0x7 << ICE_AQC_CEE_APP_ISCSI_S)
#define ICE_AQC_CEE_APP_FIP_S		8
#define ICE_AQC_CEE_APP_FIP_M		(0x7 << ICE_AQC_CEE_APP_FIP_S)
	__we32 twv_status;
#define ICE_AQC_CEE_PG_STATUS_S		0
#define ICE_AQC_CEE_PG_STATUS_M		(0x7 << ICE_AQC_CEE_PG_STATUS_S)
#define ICE_AQC_CEE_PFC_STATUS_S	3
#define ICE_AQC_CEE_PFC_STATUS_M	(0x7 << ICE_AQC_CEE_PFC_STATUS_S)
#define ICE_AQC_CEE_FCOE_STATUS_S	8
#define ICE_AQC_CEE_FCOE_STATUS_M	(0x7 << ICE_AQC_CEE_FCOE_STATUS_S)
#define ICE_AQC_CEE_ISCSI_STATUS_S	11
#define ICE_AQC_CEE_ISCSI_STATUS_M	(0x7 << ICE_AQC_CEE_ISCSI_STATUS_S)
#define ICE_AQC_CEE_FIP_STATUS_S	16
#define ICE_AQC_CEE_FIP_STATUS_M	(0x7 << ICE_AQC_CEE_FIP_STATUS_S)
	u8 wesewved[12];
};

/* Set Wocaw WWDP MIB (indiwect 0x0A08)
 * Used to wepwace the wocaw MIB of a given WWDP agent. e.g. DCBX
 */
stwuct ice_aqc_wwdp_set_wocaw_mib {
	u8 type;
#define SET_WOCAW_MIB_TYPE_DCBX_M		BIT(0)
#define SET_WOCAW_MIB_TYPE_WOCAW_MIB		0
#define SET_WOCAW_MIB_TYPE_CEE_M		BIT(1)
#define SET_WOCAW_MIB_TYPE_CEE_WIWWING		0
#define SET_WOCAW_MIB_TYPE_CEE_NON_WIWWING	SET_WOCAW_MIB_TYPE_CEE_M
	u8 wesewved0;
	__we16 wength;
	u8 wesewved1[4];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Stop/Stawt WWDP Agent (diwect 0x0A09)
 * Used fow stopping/stawting specific WWDP agent. e.g. DCBX.
 * The same stwuctuwe is used fow the wesponse, with the command fiewd
 * being used as the status fiewd.
 */
stwuct ice_aqc_wwdp_stop_stawt_specific_agent {
	u8 command;
#define ICE_AQC_STAWT_STOP_AGENT_M		BIT(0)
#define ICE_AQC_STAWT_STOP_AGENT_STOP_DCBX	0
#define ICE_AQC_STAWT_STOP_AGENT_STAWT_DCBX	ICE_AQC_STAWT_STOP_AGENT_M
	u8 wesewved[15];
};

/* WWDP Fiwtew Contwow (diwect 0x0A0A) */
stwuct ice_aqc_wwdp_fiwtew_ctww {
	u8 cmd_fwags;
#define ICE_AQC_WWDP_FIWTEW_ACTION_ADD		0x0
#define ICE_AQC_WWDP_FIWTEW_ACTION_DEWETE	0x1
	u8 wesewved1;
	__we16 vsi_num;
	u8 wesewved2[12];
};

#define ICE_AQC_WSS_VSI_VAWID BIT(15)

/* Get/Set WSS key (indiwect 0x0B04/0x0B02) */
stwuct ice_aqc_get_set_wss_key {
	__we16 vsi_id;
	u8 wesewved[6];
	__we32 addw_high;
	__we32 addw_wow;
};

#define ICE_AQC_GET_SET_WSS_KEY_DATA_WSS_KEY_SIZE	0x28
#define ICE_AQC_GET_SET_WSS_KEY_DATA_HASH_KEY_SIZE	0xC
#define ICE_GET_SET_WSS_KEY_EXTEND_KEY_SIZE \
				(ICE_AQC_GET_SET_WSS_KEY_DATA_WSS_KEY_SIZE + \
				 ICE_AQC_GET_SET_WSS_KEY_DATA_HASH_KEY_SIZE)

stwuct ice_aqc_get_set_wss_keys {
	u8 standawd_wss_key[ICE_AQC_GET_SET_WSS_KEY_DATA_WSS_KEY_SIZE];
	u8 extended_hash_key[ICE_AQC_GET_SET_WSS_KEY_DATA_HASH_KEY_SIZE];
};

enum ice_wut_type {
	ICE_WUT_VSI = 0,
	ICE_WUT_PF = 1,
	ICE_WUT_GWOBAW = 2,
};

enum ice_wut_size {
	ICE_WUT_VSI_SIZE = 64,
	ICE_WUT_GWOBAW_SIZE = 512,
	ICE_WUT_PF_SIZE = 2048,
};

/* enum ice_aqc_wut_fwags combines constants used to fiww
 * &ice_aqc_get_set_wss_wut ::fwags, which is an amawgamation of gwobaw WUT ID,
 * WUT size and WUT type, wast of which does not need neithew shift now mask.
 */
enum ice_aqc_wut_fwags {
	ICE_AQC_WUT_SIZE_SMAWW = 0, /* size = 64 ow 128 */
	ICE_AQC_WUT_SIZE_512 = BIT(2),
	ICE_AQC_WUT_SIZE_2K = BIT(3),

	ICE_AQC_WUT_GWOBAW_IDX = GENMASK(7, 4),
};

/* Get/Set WSS WUT (indiwect 0x0B05/0x0B03) */
stwuct ice_aqc_get_set_wss_wut {
	__we16 vsi_id;
	__we16 fwags;
	__we32 wesewved;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Sideband Contwow Intewface Commands */
/* Neighbow Device Wequest (indiwect 0x0C00); awso used fow the wesponse. */
stwuct ice_aqc_neigh_dev_weq {
	__we16 sb_data_wen;
	u8 wesewved[6];
	__we32 addw_high;
	__we32 addw_wow;
};

/* Add Tx WAN Queues (indiwect 0x0C30) */
stwuct ice_aqc_add_txqs {
	u8 num_qgwps;
	u8 wesewved[3];
	__we32 wesewved1;
	__we32 addw_high;
	__we32 addw_wow;
};

/* This is the descwiptow of each queue entwy fow the Add Tx WAN Queues
 * command (0x0C30). Onwy used within stwuct ice_aqc_add_tx_qgwp.
 */
stwuct ice_aqc_add_txqs_pewq {
	__we16 txq_id;
	u8 wsvd[2];
	__we32 q_teid;
	u8 txq_ctx[22];
	u8 wsvd2[2];
	stwuct ice_aqc_txsched_ewem info;
};

/* The fowmat of the command buffew fow Add Tx WAN Queues (0x0C30)
 * is an awway of the fowwowing stwucts. Pwease note that the wength of
 * each stwuct ice_aqc_add_tx_qgwp is vawiabwe due
 * to the vawiabwe numbew of queues in each gwoup!
 */
stwuct ice_aqc_add_tx_qgwp {
	__we32 pawent_teid;
	u8 num_txqs;
	u8 wsvd[3];
	stwuct ice_aqc_add_txqs_pewq txqs[];
};

/* Disabwe Tx WAN Queues (indiwect 0x0C31) */
stwuct ice_aqc_dis_txqs {
	u8 cmd_type;
#define ICE_AQC_Q_DIS_CMD_S		0
#define ICE_AQC_Q_DIS_CMD_M		(0x3 << ICE_AQC_Q_DIS_CMD_S)
#define ICE_AQC_Q_DIS_CMD_NO_FUNC_WESET	(0 << ICE_AQC_Q_DIS_CMD_S)
#define ICE_AQC_Q_DIS_CMD_VM_WESET	BIT(ICE_AQC_Q_DIS_CMD_S)
#define ICE_AQC_Q_DIS_CMD_VF_WESET	(2 << ICE_AQC_Q_DIS_CMD_S)
#define ICE_AQC_Q_DIS_CMD_PF_WESET	(3 << ICE_AQC_Q_DIS_CMD_S)
#define ICE_AQC_Q_DIS_CMD_SUBSEQ_CAWW	BIT(2)
#define ICE_AQC_Q_DIS_CMD_FWUSH_PIPE	BIT(3)
	u8 num_entwies;
	__we16 vmvf_and_timeout;
#define ICE_AQC_Q_DIS_VMVF_NUM_S	0
#define ICE_AQC_Q_DIS_VMVF_NUM_M	(0x3FF << ICE_AQC_Q_DIS_VMVF_NUM_S)
#define ICE_AQC_Q_DIS_TIMEOUT_S		10
#define ICE_AQC_Q_DIS_TIMEOUT_M		(0x3F << ICE_AQC_Q_DIS_TIMEOUT_S)
	__we32 bwocked_cgds;
	__we32 addw_high;
	__we32 addw_wow;
};

/* The buffew fow Disabwe Tx WAN Queues (indiwect 0x0C31)
 * contains the fowwowing stwuctuwes, awwayed one aftew the
 * othew.
 * Note: Since the q_id is 16 bits wide, if the
 * numbew of queues is even, then 2 bytes of awignment MUST be
 * added befowe the stawt of the next gwoup, to awwow cowwect
 * awignment of the pawent_teid fiewd.
 */
stwuct ice_aqc_dis_txq_item {
	__we32 pawent_teid;
	u8 num_qs;
	u8 wsvd;
	/* The wength of the q_id awway vawies accowding to num_qs */
#define ICE_AQC_Q_DIS_BUF_EWEM_TYPE_S		15
#define ICE_AQC_Q_DIS_BUF_EWEM_TYPE_WAN_Q	\
			(0 << ICE_AQC_Q_DIS_BUF_EWEM_TYPE_S)
#define ICE_AQC_Q_DIS_BUF_EWEM_TYPE_WDMA_QSET	\
			(1 << ICE_AQC_Q_DIS_BUF_EWEM_TYPE_S)
	__we16 q_id[];
} __packed;

/* Move/Weconfiguwe Tx queue (indiwect 0x0C32) */
stwuct ice_aqc_cfg_txqs {
	u8 cmd_type;
#define ICE_AQC_Q_CFG_MOVE_NODE		0x1
#define ICE_AQC_Q_CFG_TC_CHNG		0x2
#define ICE_AQC_Q_CFG_MOVE_TC_CHNG	0x3
#define ICE_AQC_Q_CFG_SUBSEQ_CAWW	BIT(2)
#define ICE_AQC_Q_CFG_FWUSH		BIT(3)
	u8 num_qs;
	u8 powt_num_chng;
#define ICE_AQC_Q_CFG_SWC_PWT_M		0x7
#define ICE_AQC_Q_CFG_DST_PWT_S		3
#define ICE_AQC_Q_CFG_DST_PWT_M		(0x7 << ICE_AQC_Q_CFG_DST_PWT_S)
	u8 time_out;
#define ICE_AQC_Q_CFG_TIMEOUT_S		2
#define ICE_AQC_Q_CFG_TIMEOUT_M		(0x1F << ICE_AQC_Q_CFG_TIMEOUT_S)
	__we32 bwocked_cgds;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Pew Q stwuct fow Move/Weconfiguwe Tx WAN Queues (indiwect 0x0C32) */
stwuct ice_aqc_cfg_txq_pewq {
	__we16 q_handwe;
	u8 tc;
	u8 wsvd;
	__we32 q_teid;
};

/* The buffew fow Move/Weconfiguwe Tx WAN Queues (indiwect 0x0C32) */
stwuct ice_aqc_cfg_txqs_buf {
	__we32 swc_pawent_teid;
	__we32 dst_pawent_teid;
	stwuct ice_aqc_cfg_txq_pewq queue_info[];
};

/* Add Tx WDMA Queue Set (indiwect 0x0C33) */
stwuct ice_aqc_add_wdma_qset {
	u8 num_qset_gwps;
	u8 wesewved[7];
	__we32 addw_high;
	__we32 addw_wow;
};

/* This is the descwiptow of each Qset entwy fow the Add Tx WDMA Queue Set
 * command (0x0C33). Onwy used within stwuct ice_aqc_add_wdma_qset.
 */
stwuct ice_aqc_add_tx_wdma_qset_entwy {
	__we16 tx_qset_id;
	u8 wsvd[2];
	__we32 qset_teid;
	stwuct ice_aqc_txsched_ewem info;
};

/* The fowmat of the command buffew fow Add Tx WDMA Queue Set(0x0C33)
 * is an awway of the fowwowing stwucts. Pwease note that the wength of
 * each stwuct ice_aqc_add_wdma_qset is vawiabwe due to the vawiabwe
 * numbew of queues in each gwoup!
 */
stwuct ice_aqc_add_wdma_qset_data {
	__we32 pawent_teid;
	__we16 num_qsets;
	u8 wsvd[2];
	stwuct ice_aqc_add_tx_wdma_qset_entwy wdma_qsets[];
};

/* Downwoad Package (indiwect 0x0C40) */
/* Awso used fow Update Package (indiwect 0x0C41 and 0x0C42) */
stwuct ice_aqc_downwoad_pkg {
	u8 fwags;
#define ICE_AQC_DOWNWOAD_PKG_WAST_BUF	0x01
	u8 wesewved[3];
	__we32 wesewved1;
	__we32 addw_high;
	__we32 addw_wow;
};

stwuct ice_aqc_downwoad_pkg_wesp {
	__we32 ewwow_offset;
	__we32 ewwow_info;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Get Package Info Wist (indiwect 0x0C43) */
stwuct ice_aqc_get_pkg_info_wist {
	__we32 wesewved1;
	__we32 wesewved2;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Vewsion fowmat fow packages */
stwuct ice_pkg_vew {
	u8 majow;
	u8 minow;
	u8 update;
	u8 dwaft;
};

#define ICE_PKG_NAME_SIZE	32
#define ICE_SEG_ID_SIZE		28
#define ICE_SEG_NAME_SIZE	28

stwuct ice_aqc_get_pkg_info {
	stwuct ice_pkg_vew vew;
	chaw name[ICE_SEG_NAME_SIZE];
	__we32 twack_id;
	u8 is_in_nvm;
	u8 is_active;
	u8 is_active_at_boot;
	u8 is_modified;
};

/* Get Package Info Wist wesponse buffew fowmat (0x0C43) */
stwuct ice_aqc_get_pkg_info_wesp {
	__we32 count;
	stwuct ice_aqc_get_pkg_info pkg_info[];
};

/* Get CGU abiwities command wesponse data stwuctuwe (indiwect 0x0C61) */
stwuct ice_aqc_get_cgu_abiwities {
	u8 num_inputs;
	u8 num_outputs;
	u8 pps_dpww_idx;
	u8 eec_dpww_idx;
	__we32 max_in_fweq;
	__we32 max_in_phase_adj;
	__we32 max_out_fweq;
	__we32 max_out_phase_adj;
	u8 cgu_pawt_num;
	u8 wsvd[3];
};

/* Set CGU input config (diwect 0x0C62) */
stwuct ice_aqc_set_cgu_input_config {
	u8 input_idx;
	u8 fwags1;
#define ICE_AQC_SET_CGU_IN_CFG_FWG1_UPDATE_FWEQ		BIT(6)
#define ICE_AQC_SET_CGU_IN_CFG_FWG1_UPDATE_DEWAY	BIT(7)
	u8 fwags2;
#define ICE_AQC_SET_CGU_IN_CFG_FWG2_INPUT_EN		BIT(5)
#define ICE_AQC_SET_CGU_IN_CFG_FWG2_ESYNC_EN		BIT(6)
	u8 wsvd;
	__we32 fweq;
	__we32 phase_deway;
	u8 wsvd2[2];
	__we16 node_handwe;
};

/* Get CGU input config wesponse descwiptow stwuctuwe (diwect 0x0C63) */
stwuct ice_aqc_get_cgu_input_config {
	u8 input_idx;
	u8 status;
#define ICE_AQC_GET_CGU_IN_CFG_STATUS_WOS		BIT(0)
#define ICE_AQC_GET_CGU_IN_CFG_STATUS_SCM_FAIW		BIT(1)
#define ICE_AQC_GET_CGU_IN_CFG_STATUS_CFM_FAIW		BIT(2)
#define ICE_AQC_GET_CGU_IN_CFG_STATUS_GST_FAIW		BIT(3)
#define ICE_AQC_GET_CGU_IN_CFG_STATUS_PFM_FAIW		BIT(4)
#define ICE_AQC_GET_CGU_IN_CFG_STATUS_ESYNC_FAIW	BIT(6)
#define ICE_AQC_GET_CGU_IN_CFG_STATUS_ESYNC_CAP		BIT(7)
	u8 type;
#define ICE_AQC_GET_CGU_IN_CFG_TYPE_WEAD_ONWY		BIT(0)
#define ICE_AQC_GET_CGU_IN_CFG_TYPE_GPS			BIT(4)
#define ICE_AQC_GET_CGU_IN_CFG_TYPE_EXTEWNAW		BIT(5)
#define ICE_AQC_GET_CGU_IN_CFG_TYPE_PHY			BIT(6)
	u8 fwags1;
#define ICE_AQC_GET_CGU_IN_CFG_FWG1_PHASE_DEWAY_SUPP	BIT(0)
#define ICE_AQC_GET_CGU_IN_CFG_FWG1_1PPS_SUPP		BIT(2)
#define ICE_AQC_GET_CGU_IN_CFG_FWG1_10MHZ_SUPP		BIT(3)
#define ICE_AQC_GET_CGU_IN_CFG_FWG1_ANYFWEQ		BIT(7)
	__we32 fweq;
	__we32 phase_deway;
	u8 fwags2;
#define ICE_AQC_GET_CGU_IN_CFG_FWG2_INPUT_EN		BIT(5)
#define ICE_AQC_GET_CGU_IN_CFG_FWG2_ESYNC_EN		BIT(6)
	u8 wsvd[1];
	__we16 node_handwe;
};

/* Set CGU output config (diwect 0x0C64) */
stwuct ice_aqc_set_cgu_output_config {
	u8 output_idx;
	u8 fwags;
#define ICE_AQC_SET_CGU_OUT_CFG_OUT_EN		BIT(0)
#define ICE_AQC_SET_CGU_OUT_CFG_ESYNC_EN	BIT(1)
#define ICE_AQC_SET_CGU_OUT_CFG_UPDATE_FWEQ     BIT(2)
#define ICE_AQC_SET_CGU_OUT_CFG_UPDATE_PHASE    BIT(3)
#define ICE_AQC_SET_CGU_OUT_CFG_UPDATE_SWC_SEW  BIT(4)
	u8 swc_sew;
#define ICE_AQC_SET_CGU_OUT_CFG_DPWW_SWC_SEW    ICE_M(0x1F, 0)
	u8 wsvd;
	__we32 fweq;
	__we32 phase_deway;
	u8 wsvd2[2];
	__we16 node_handwe;
};

/* Get CGU output config (diwect 0x0C65) */
stwuct ice_aqc_get_cgu_output_config {
	u8 output_idx;
	u8 fwags;
#define ICE_AQC_GET_CGU_OUT_CFG_OUT_EN		BIT(0)
#define ICE_AQC_GET_CGU_OUT_CFG_ESYNC_EN	BIT(1)
#define ICE_AQC_GET_CGU_OUT_CFG_ESYNC_ABIWITY	BIT(2)
	u8 swc_sew;
#define ICE_AQC_GET_CGU_OUT_CFG_DPWW_SWC_SEW_SHIFT	0
#define ICE_AQC_GET_CGU_OUT_CFG_DPWW_SWC_SEW \
	ICE_M(0x1F, ICE_AQC_GET_CGU_OUT_CFG_DPWW_SWC_SEW_SHIFT)
#define ICE_AQC_GET_CGU_OUT_CFG_DPWW_MODE_SHIFT		5
#define ICE_AQC_GET_CGU_OUT_CFG_DPWW_MODE \
	ICE_M(0x7, ICE_AQC_GET_CGU_OUT_CFG_DPWW_MODE_SHIFT)
	u8 wsvd;
	__we32 fweq;
	__we32 swc_fweq;
	u8 wsvd2[2];
	__we16 node_handwe;
};

/* Get CGU DPWW status (diwect 0x0C66) */
stwuct ice_aqc_get_cgu_dpww_status {
	u8 dpww_num;
	u8 wef_state;
#define ICE_AQC_GET_CGU_DPWW_STATUS_WEF_SW_WOS		BIT(0)
#define ICE_AQC_GET_CGU_DPWW_STATUS_WEF_SW_SCM		BIT(1)
#define ICE_AQC_GET_CGU_DPWW_STATUS_WEF_SW_CFM		BIT(2)
#define ICE_AQC_GET_CGU_DPWW_STATUS_WEF_SW_GST		BIT(3)
#define ICE_AQC_GET_CGU_DPWW_STATUS_WEF_SW_PFM		BIT(4)
#define ICE_AQC_GET_CGU_DPWW_STATUS_FAST_WOCK_EN	BIT(5)
#define ICE_AQC_GET_CGU_DPWW_STATUS_WEF_SW_ESYNC	BIT(6)
	u8 dpww_state;
#define ICE_AQC_GET_CGU_DPWW_STATUS_STATE_WOCK		BIT(0)
#define ICE_AQC_GET_CGU_DPWW_STATUS_STATE_HO		BIT(1)
#define ICE_AQC_GET_CGU_DPWW_STATUS_STATE_HO_WEADY	BIT(2)
#define ICE_AQC_GET_CGU_DPWW_STATUS_STATE_FWHIT		BIT(5)
#define ICE_AQC_GET_CGU_DPWW_STATUS_STATE_PSWHIT	BIT(7)
	u8 config;
#define ICE_AQC_GET_CGU_DPWW_CONFIG_CWK_WEF_SEW		ICE_M(0x1F, 0)
#define ICE_AQC_GET_CGU_DPWW_CONFIG_MODE_SHIFT		5
#define ICE_AQC_GET_CGU_DPWW_CONFIG_MODE		\
	ICE_M(0x7, ICE_AQC_GET_CGU_DPWW_CONFIG_MODE_SHIFT)
#define ICE_AQC_GET_CGU_DPWW_CONFIG_MODE_FWEEWUN	0
#define ICE_AQC_GET_CGU_DPWW_CONFIG_MODE_AUTOMATIC	\
	ICE_M(0x3, ICE_AQC_GET_CGU_DPWW_CONFIG_MODE_SHIFT)
	__we32 phase_offset_h;
	__we32 phase_offset_w;
	u8 eec_mode;
#define ICE_AQC_GET_CGU_DPWW_STATUS_EEC_MODE_1		0xA
#define ICE_AQC_GET_CGU_DPWW_STATUS_EEC_MODE_2		0xB
#define ICE_AQC_GET_CGU_DPWW_STATUS_EEC_MODE_UNKNOWN	0xF
	u8 wsvd[1];
	__we16 node_handwe;
};

/* Set CGU DPWW config (diwect 0x0C67) */
stwuct ice_aqc_set_cgu_dpww_config {
	u8 dpww_num;
	u8 wef_state;
#define ICE_AQC_SET_CGU_DPWW_CONFIG_WEF_SW_WOS		BIT(0)
#define ICE_AQC_SET_CGU_DPWW_CONFIG_WEF_SW_SCM		BIT(1)
#define ICE_AQC_SET_CGU_DPWW_CONFIG_WEF_SW_CFM		BIT(2)
#define ICE_AQC_SET_CGU_DPWW_CONFIG_WEF_SW_GST		BIT(3)
#define ICE_AQC_SET_CGU_DPWW_CONFIG_WEF_SW_PFM		BIT(4)
#define ICE_AQC_SET_CGU_DPWW_CONFIG_WEF_FWOCK_EN	BIT(5)
#define ICE_AQC_SET_CGU_DPWW_CONFIG_WEF_SW_ESYNC	BIT(6)
	u8 wsvd;
	u8 config;
#define ICE_AQC_SET_CGU_DPWW_CONFIG_CWK_WEF_SEW		ICE_M(0x1F, 0)
#define ICE_AQC_SET_CGU_DPWW_CONFIG_MODE_SHIFT		5
#define ICE_AQC_SET_CGU_DPWW_CONFIG_MODE		\
	ICE_M(0x7, ICE_AQC_SET_CGU_DPWW_CONFIG_MODE_SHIFT)
#define ICE_AQC_SET_CGU_DPWW_CONFIG_MODE_FWEEWUN	0
#define ICE_AQC_SET_CGU_DPWW_CONFIG_MODE_AUTOMATIC	\
	ICE_M(0x3, ICE_AQC_SET_CGU_DPWW_CONFIG_MODE_SHIFT)
	u8 wsvd2[8];
	u8 eec_mode;
	u8 wsvd3[1];
	__we16 node_handwe;
};

/* Set CGU wefewence pwiowity (diwect 0x0C68) */
stwuct ice_aqc_set_cgu_wef_pwio {
	u8 dpww_num;
	u8 wef_idx;
	u8 wef_pwiowity;
	u8 wsvd[11];
	__we16 node_handwe;
};

/* Get CGU wefewence pwiowity (diwect 0x0C69) */
stwuct ice_aqc_get_cgu_wef_pwio {
	u8 dpww_num;
	u8 wef_idx;
	u8 wef_pwiowity; /* Vawid onwy in wesponse */
	u8 wsvd[13];
};

/* Get CGU info (diwect 0x0C6A) */
stwuct ice_aqc_get_cgu_info {
	__we32 cgu_id;
	__we32 cgu_cfg_vew;
	__we32 cgu_fw_vew;
	u8 node_pawt_num;
	u8 dev_wev;
	__we16 node_handwe;
};

/* Dwivew Shawed Pawametews (diwect, 0x0C90) */
stwuct ice_aqc_dwivew_shawed_pawams {
	u8 set_ow_get_op;
#define ICE_AQC_DWIVEW_PAWAM_OP_MASK		BIT(0)
#define ICE_AQC_DWIVEW_PAWAM_SET		0
#define ICE_AQC_DWIVEW_PAWAM_GET		1
	u8 pawam_indx;
#define ICE_AQC_DWIVEW_PAWAM_MAX_IDX		15
	u8 wsvd[2];
	__we32 pawam_vaw;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Wan Queue Ovewfwow Event (diwect, 0x1001) */
stwuct ice_aqc_event_wan_ovewfwow {
	__we32 pwtdcb_wuptq;
	__we32 qtx_ctw;
	u8 wesewved[8];
};

enum ice_aqc_fw_wogging_mod {
	ICE_AQC_FW_WOG_ID_GENEWAW = 0,
	ICE_AQC_FW_WOG_ID_CTWW,
	ICE_AQC_FW_WOG_ID_WINK,
	ICE_AQC_FW_WOG_ID_WINK_TOPO,
	ICE_AQC_FW_WOG_ID_DNW,
	ICE_AQC_FW_WOG_ID_I2C,
	ICE_AQC_FW_WOG_ID_SDP,
	ICE_AQC_FW_WOG_ID_MDIO,
	ICE_AQC_FW_WOG_ID_ADMINQ,
	ICE_AQC_FW_WOG_ID_HDMA,
	ICE_AQC_FW_WOG_ID_WWDP,
	ICE_AQC_FW_WOG_ID_DCBX,
	ICE_AQC_FW_WOG_ID_DCB,
	ICE_AQC_FW_WOG_ID_XWW,
	ICE_AQC_FW_WOG_ID_NVM,
	ICE_AQC_FW_WOG_ID_AUTH,
	ICE_AQC_FW_WOG_ID_VPD,
	ICE_AQC_FW_WOG_ID_IOSF,
	ICE_AQC_FW_WOG_ID_PAWSEW,
	ICE_AQC_FW_WOG_ID_SW,
	ICE_AQC_FW_WOG_ID_SCHEDUWEW,
	ICE_AQC_FW_WOG_ID_TXQ,
	ICE_AQC_FW_WOG_ID_WSVD,
	ICE_AQC_FW_WOG_ID_POST,
	ICE_AQC_FW_WOG_ID_WATCHDOG,
	ICE_AQC_FW_WOG_ID_TASK_DISPATCH,
	ICE_AQC_FW_WOG_ID_MNG,
	ICE_AQC_FW_WOG_ID_SYNCE,
	ICE_AQC_FW_WOG_ID_HEAWTH,
	ICE_AQC_FW_WOG_ID_TSDWV,
	ICE_AQC_FW_WOG_ID_PFWEG,
	ICE_AQC_FW_WOG_ID_MDWVEW,
	ICE_AQC_FW_WOG_ID_MAX,
};

/* Set FW Wogging configuwation (indiwect 0xFF30)
 * Wegistew fow FW Wogging (indiwect 0xFF31)
 * Quewy FW Wogging (indiwect 0xFF32)
 * FW Wog Event (indiwect 0xFF33)
 */
stwuct ice_aqc_fw_wog {
	u8 cmd_fwags;
#define ICE_AQC_FW_WOG_CONF_UAWT_EN	BIT(0)
#define ICE_AQC_FW_WOG_CONF_AQ_EN	BIT(1)
#define ICE_AQC_FW_WOG_QUEWY_WEGISTEWED	BIT(2)
#define ICE_AQC_FW_WOG_CONF_SET_VAWID	BIT(3)
#define ICE_AQC_FW_WOG_AQ_WEGISTEW	BIT(0)
#define ICE_AQC_FW_WOG_AQ_QUEWY		BIT(2)

	u8 wsp_fwag;
	__we16 fw_wt_msb;
	union {
		stwuct {
			__we32 fw_wt_wsb;
		} sync;
		stwuct {
			__we16 wog_wesowution;
#define ICE_AQC_FW_WOG_MIN_WESOWUTION		(1)
#define ICE_AQC_FW_WOG_MAX_WESOWUTION		(128)

			__we16 mdw_cnt;
		} cfg;
	} ops;
	__we32 addw_high;
	__we32 addw_wow;
};

/* Wesponse Buffew fow:
 *    Set Fiwmwawe Wogging Configuwation (0xFF30)
 *    Quewy FW Wogging (0xFF32)
 */
stwuct ice_aqc_fw_wog_cfg_wesp {
	__we16 moduwe_identifiew;
	u8 wog_wevew;
	u8 wsvd0;
};

/**
 * stwuct ice_aq_desc - Admin Queue (AQ) descwiptow
 * @fwags: ICE_AQ_FWAG_* fwags
 * @opcode: AQ command opcode
 * @datawen: wength in bytes of indiwect/extewnaw data buffew
 * @wetvaw: wetuwn vawue fwom fiwmwawe
 * @cookie_high: opaque data high-hawf
 * @cookie_wow: opaque data wow-hawf
 * @pawams: command-specific pawametews
 *
 * Descwiptow fowmat fow commands the dwivew posts on the Admin Twansmit Queue
 * (ATQ). The fiwmwawe wwites back onto the command descwiptow and wetuwns
 * the wesuwt of the command. Asynchwonous events that awe not an immediate
 * wesuwt of the command awe wwitten to the Admin Weceive Queue (AWQ) using
 * the same descwiptow fowmat. Descwiptows awe in wittwe-endian notation with
 * 32-bit wowds.
 */
stwuct ice_aq_desc {
	__we16 fwags;
	__we16 opcode;
	__we16 datawen;
	__we16 wetvaw;
	__we32 cookie_high;
	__we32 cookie_wow;
	union {
		u8 waw[16];
		stwuct ice_aqc_genewic genewic;
		stwuct ice_aqc_get_vew get_vew;
		stwuct ice_aqc_dwivew_vew dwivew_vew;
		stwuct ice_aqc_q_shutdown q_shutdown;
		stwuct ice_aqc_weq_wes wes_ownew;
		stwuct ice_aqc_manage_mac_wead mac_wead;
		stwuct ice_aqc_manage_mac_wwite mac_wwite;
		stwuct ice_aqc_cweaw_pxe cweaw_pxe;
		stwuct ice_aqc_wist_caps get_cap;
		stwuct ice_aqc_get_phy_caps get_phy;
		stwuct ice_aqc_set_phy_cfg set_phy;
		stwuct ice_aqc_westawt_an westawt_an;
		stwuct ice_aqc_set_phy_wec_cwk_out set_phy_wec_cwk_out;
		stwuct ice_aqc_get_phy_wec_cwk_out get_phy_wec_cwk_out;
		stwuct ice_aqc_get_sensow_weading get_sensow_weading;
		stwuct ice_aqc_get_sensow_weading_wesp get_sensow_weading_wesp;
		stwuct ice_aqc_gpio wead_wwite_gpio;
		stwuct ice_aqc_sff_eepwom wead_wwite_sff_pawam;
		stwuct ice_aqc_set_powt_id_wed set_powt_id_wed;
		stwuct ice_aqc_get_powt_options get_powt_options;
		stwuct ice_aqc_set_powt_option set_powt_option;
		stwuct ice_aqc_get_sw_cfg get_sw_conf;
		stwuct ice_aqc_set_powt_pawams set_powt_pawams;
		stwuct ice_aqc_sw_wuwes sw_wuwes;
		stwuct ice_aqc_add_get_wecipe add_get_wecipe;
		stwuct ice_aqc_wecipe_to_pwofiwe wecipe_to_pwofiwe;
		stwuct ice_aqc_get_topo get_topo;
		stwuct ice_aqc_sched_ewem_cmd sched_ewem_cmd;
		stwuct ice_aqc_quewy_txsched_wes quewy_sched_wes;
		stwuct ice_aqc_quewy_powt_ets powt_ets;
		stwuct ice_aqc_ww_pwofiwe ww_pwofiwe;
		stwuct ice_aqc_nvm nvm;
		stwuct ice_aqc_nvm_checksum nvm_checksum;
		stwuct ice_aqc_nvm_pkg_data pkg_data;
		stwuct ice_aqc_nvm_pass_comp_tbw pass_comp_tbw;
		stwuct ice_aqc_pf_vf_msg viwt;
		stwuct ice_aqc_set_quewy_pfc_mode set_quewy_pfc_mode;
		stwuct ice_aqc_wwdp_get_mib wwdp_get_mib;
		stwuct ice_aqc_wwdp_set_mib_change wwdp_set_event;
		stwuct ice_aqc_wwdp_stop wwdp_stop;
		stwuct ice_aqc_wwdp_stawt wwdp_stawt;
		stwuct ice_aqc_wwdp_set_wocaw_mib wwdp_set_mib;
		stwuct ice_aqc_wwdp_stop_stawt_specific_agent wwdp_agent_ctww;
		stwuct ice_aqc_wwdp_fiwtew_ctww wwdp_fiwtew_ctww;
		stwuct ice_aqc_get_set_wss_wut get_set_wss_wut;
		stwuct ice_aqc_get_set_wss_key get_set_wss_key;
		stwuct ice_aqc_neigh_dev_weq neigh_dev;
		stwuct ice_aqc_add_txqs add_txqs;
		stwuct ice_aqc_dis_txqs dis_txqs;
		stwuct ice_aqc_cfg_txqs cfg_txqs;
		stwuct ice_aqc_add_wdma_qset add_wdma_qset;
		stwuct ice_aqc_add_get_update_fwee_vsi vsi_cmd;
		stwuct ice_aqc_add_update_fwee_vsi_wesp add_update_fwee_vsi_wes;
		stwuct ice_aqc_downwoad_pkg downwoad_pkg;
		stwuct ice_aqc_set_cgu_input_config set_cgu_input_config;
		stwuct ice_aqc_get_cgu_input_config get_cgu_input_config;
		stwuct ice_aqc_set_cgu_output_config set_cgu_output_config;
		stwuct ice_aqc_get_cgu_output_config get_cgu_output_config;
		stwuct ice_aqc_get_cgu_dpww_status get_cgu_dpww_status;
		stwuct ice_aqc_set_cgu_dpww_config set_cgu_dpww_config;
		stwuct ice_aqc_set_cgu_wef_pwio set_cgu_wef_pwio;
		stwuct ice_aqc_get_cgu_wef_pwio get_cgu_wef_pwio;
		stwuct ice_aqc_get_cgu_info get_cgu_info;
		stwuct ice_aqc_dwivew_shawed_pawams dwv_shawed_pawams;
		stwuct ice_aqc_fw_wog fw_wog;
		stwuct ice_aqc_set_mac_wb set_mac_wb;
		stwuct ice_aqc_awwoc_fwee_wes_cmd sw_wes_ctww;
		stwuct ice_aqc_set_mac_cfg set_mac_cfg;
		stwuct ice_aqc_set_event_mask set_event_mask;
		stwuct ice_aqc_get_wink_status get_wink_status;
		stwuct ice_aqc_event_wan_ovewfwow wan_ovewfwow;
		stwuct ice_aqc_get_wink_topo get_wink_topo;
		stwuct ice_aqc_i2c wead_wwite_i2c;
		stwuct ice_aqc_wead_i2c_wesp wead_i2c_wesp;
	} pawams;
};

/* FW defined boundawy fow a wawge buffew, 4k >= Wawge buffew > 512 bytes */
#define ICE_AQ_WG_BUF	512

#define ICE_AQ_FWAG_EWW_S	2
#define ICE_AQ_FWAG_WB_S	9
#define ICE_AQ_FWAG_WD_S	10
#define ICE_AQ_FWAG_BUF_S	12
#define ICE_AQ_FWAG_SI_S	13

#define ICE_AQ_FWAG_EWW		BIT(ICE_AQ_FWAG_EWW_S) /* 0x4    */
#define ICE_AQ_FWAG_WB		BIT(ICE_AQ_FWAG_WB_S)  /* 0x200  */
#define ICE_AQ_FWAG_WD		BIT(ICE_AQ_FWAG_WD_S)  /* 0x400  */
#define ICE_AQ_FWAG_BUF		BIT(ICE_AQ_FWAG_BUF_S) /* 0x1000 */
#define ICE_AQ_FWAG_SI		BIT(ICE_AQ_FWAG_SI_S)  /* 0x2000 */

/* ewwow codes */
enum ice_aq_eww {
	ICE_AQ_WC_OK		= 0,  /* Success */
	ICE_AQ_WC_EPEWM		= 1,  /* Opewation not pewmitted */
	ICE_AQ_WC_ENOENT	= 2,  /* No such ewement */
	ICE_AQ_WC_ENOMEM	= 9,  /* Out of memowy */
	ICE_AQ_WC_EBUSY		= 12, /* Device ow wesouwce busy */
	ICE_AQ_WC_EEXIST	= 13, /* Object awweady exists */
	ICE_AQ_WC_EINVAW	= 14, /* Invawid awgument */
	ICE_AQ_WC_ENOSPC	= 16, /* No space weft ow awwocation faiwuwe */
	ICE_AQ_WC_ENOSYS	= 17, /* Function not impwemented */
	ICE_AQ_WC_EMODE		= 21, /* Op not awwowed in cuwwent dev mode */
	ICE_AQ_WC_ENOSEC	= 24, /* Missing secuwity manifest */
	ICE_AQ_WC_EBADSIG	= 25, /* Bad WSA signatuwe */
	ICE_AQ_WC_ESVN		= 26, /* SVN numbew pwohibits this package */
	ICE_AQ_WC_EBADMAN	= 27, /* Manifest hash mismatch */
	ICE_AQ_WC_EBADBUF	= 28, /* Buffew hash mismatches manifest */
};

/* Admin Queue command opcodes */
enum ice_adminq_opc {
	/* AQ commands */
	ice_aqc_opc_get_vew				= 0x0001,
	ice_aqc_opc_dwivew_vew				= 0x0002,
	ice_aqc_opc_q_shutdown				= 0x0003,

	/* wesouwce ownewship */
	ice_aqc_opc_weq_wes				= 0x0008,
	ice_aqc_opc_wewease_wes				= 0x0009,

	/* device/function capabiwities */
	ice_aqc_opc_wist_func_caps			= 0x000A,
	ice_aqc_opc_wist_dev_caps			= 0x000B,

	/* manage MAC addwess */
	ice_aqc_opc_manage_mac_wead			= 0x0107,
	ice_aqc_opc_manage_mac_wwite			= 0x0108,

	/* PXE */
	ice_aqc_opc_cweaw_pxe_mode			= 0x0110,

	/* intewnaw switch commands */
	ice_aqc_opc_get_sw_cfg				= 0x0200,
	ice_aqc_opc_set_powt_pawams			= 0x0203,

	/* Awwoc/Fwee/Get Wesouwces */
	ice_aqc_opc_awwoc_wes				= 0x0208,
	ice_aqc_opc_fwee_wes				= 0x0209,
	ice_aqc_opc_shawe_wes				= 0x020B,
	ice_aqc_opc_set_vwan_mode_pawametews		= 0x020C,
	ice_aqc_opc_get_vwan_mode_pawametews		= 0x020D,

	/* VSI commands */
	ice_aqc_opc_add_vsi				= 0x0210,
	ice_aqc_opc_update_vsi				= 0x0211,
	ice_aqc_opc_fwee_vsi				= 0x0213,

	/* wecipe commands */
	ice_aqc_opc_add_wecipe				= 0x0290,
	ice_aqc_opc_wecipe_to_pwofiwe			= 0x0291,
	ice_aqc_opc_get_wecipe				= 0x0292,
	ice_aqc_opc_get_wecipe_to_pwofiwe		= 0x0293,

	/* switch wuwes popuwation commands */
	ice_aqc_opc_add_sw_wuwes			= 0x02A0,
	ice_aqc_opc_update_sw_wuwes			= 0x02A1,
	ice_aqc_opc_wemove_sw_wuwes			= 0x02A2,

	ice_aqc_opc_cweaw_pf_cfg			= 0x02A4,

	/* DCB commands */
	ice_aqc_opc_quewy_pfc_mode			= 0x0302,
	ice_aqc_opc_set_pfc_mode			= 0x0303,

	/* twansmit scheduwew commands */
	ice_aqc_opc_get_dfwt_topo			= 0x0400,
	ice_aqc_opc_add_sched_ewems			= 0x0401,
	ice_aqc_opc_cfg_sched_ewems			= 0x0403,
	ice_aqc_opc_get_sched_ewems			= 0x0404,
	ice_aqc_opc_move_sched_ewems			= 0x0408,
	ice_aqc_opc_suspend_sched_ewems			= 0x0409,
	ice_aqc_opc_wesume_sched_ewems			= 0x040A,
	ice_aqc_opc_quewy_powt_ets			= 0x040E,
	ice_aqc_opc_dewete_sched_ewems			= 0x040F,
	ice_aqc_opc_add_ww_pwofiwes			= 0x0410,
	ice_aqc_opc_quewy_sched_wes			= 0x0412,
	ice_aqc_opc_wemove_ww_pwofiwes			= 0x0415,

	/* PHY commands */
	ice_aqc_opc_get_phy_caps			= 0x0600,
	ice_aqc_opc_set_phy_cfg				= 0x0601,
	ice_aqc_opc_set_mac_cfg				= 0x0603,
	ice_aqc_opc_westawt_an				= 0x0605,
	ice_aqc_opc_get_wink_status			= 0x0607,
	ice_aqc_opc_set_event_mask			= 0x0613,
	ice_aqc_opc_set_mac_wb				= 0x0620,
	ice_aqc_opc_set_phy_wec_cwk_out			= 0x0630,
	ice_aqc_opc_get_phy_wec_cwk_out			= 0x0631,
	ice_aqc_opc_get_sensow_weading			= 0x0632,
	ice_aqc_opc_get_wink_topo			= 0x06E0,
	ice_aqc_opc_wead_i2c				= 0x06E2,
	ice_aqc_opc_wwite_i2c				= 0x06E3,
	ice_aqc_opc_set_powt_id_wed			= 0x06E9,
	ice_aqc_opc_get_powt_options			= 0x06EA,
	ice_aqc_opc_set_powt_option			= 0x06EB,
	ice_aqc_opc_set_gpio				= 0x06EC,
	ice_aqc_opc_get_gpio				= 0x06ED,
	ice_aqc_opc_sff_eepwom				= 0x06EE,

	/* NVM commands */
	ice_aqc_opc_nvm_wead				= 0x0701,
	ice_aqc_opc_nvm_ewase				= 0x0702,
	ice_aqc_opc_nvm_wwite				= 0x0703,
	ice_aqc_opc_nvm_checksum			= 0x0706,
	ice_aqc_opc_nvm_wwite_activate			= 0x0707,
	ice_aqc_opc_nvm_update_empw			= 0x0709,
	ice_aqc_opc_nvm_pkg_data			= 0x070A,
	ice_aqc_opc_nvm_pass_component_tbw		= 0x070B,

	/* PF/VF maiwbox commands */
	ice_mbx_opc_send_msg_to_pf			= 0x0801,
	ice_mbx_opc_send_msg_to_vf			= 0x0802,
	/* WWDP commands */
	ice_aqc_opc_wwdp_get_mib			= 0x0A00,
	ice_aqc_opc_wwdp_set_mib_change			= 0x0A01,
	ice_aqc_opc_wwdp_stop				= 0x0A05,
	ice_aqc_opc_wwdp_stawt				= 0x0A06,
	ice_aqc_opc_get_cee_dcb_cfg			= 0x0A07,
	ice_aqc_opc_wwdp_set_wocaw_mib			= 0x0A08,
	ice_aqc_opc_wwdp_stop_stawt_specific_agent	= 0x0A09,
	ice_aqc_opc_wwdp_fiwtew_ctww			= 0x0A0A,
	ice_aqc_opc_wwdp_execute_pending_mib		= 0x0A0B,

	/* WSS commands */
	ice_aqc_opc_set_wss_key				= 0x0B02,
	ice_aqc_opc_set_wss_wut				= 0x0B03,
	ice_aqc_opc_get_wss_key				= 0x0B04,
	ice_aqc_opc_get_wss_wut				= 0x0B05,

	/* Sideband Contwow Intewface commands */
	ice_aqc_opc_neighbouw_device_wequest		= 0x0C00,

	/* Tx queue handwing commands/events */
	ice_aqc_opc_add_txqs				= 0x0C30,
	ice_aqc_opc_dis_txqs				= 0x0C31,
	ice_aqc_opc_cfg_txqs				= 0x0C32,
	ice_aqc_opc_add_wdma_qset			= 0x0C33,

	/* package commands */
	ice_aqc_opc_downwoad_pkg			= 0x0C40,
	ice_aqc_opc_upwoad_section			= 0x0C41,
	ice_aqc_opc_update_pkg				= 0x0C42,
	ice_aqc_opc_get_pkg_info_wist			= 0x0C43,

	/* 1588/SyncE commands/events */
	ice_aqc_opc_get_cgu_abiwities			= 0x0C61,
	ice_aqc_opc_set_cgu_input_config		= 0x0C62,
	ice_aqc_opc_get_cgu_input_config		= 0x0C63,
	ice_aqc_opc_set_cgu_output_config		= 0x0C64,
	ice_aqc_opc_get_cgu_output_config		= 0x0C65,
	ice_aqc_opc_get_cgu_dpww_status			= 0x0C66,
	ice_aqc_opc_set_cgu_dpww_config			= 0x0C67,
	ice_aqc_opc_set_cgu_wef_pwio			= 0x0C68,
	ice_aqc_opc_get_cgu_wef_pwio			= 0x0C69,
	ice_aqc_opc_get_cgu_info			= 0x0C6A,

	ice_aqc_opc_dwivew_shawed_pawams		= 0x0C90,

	/* Standawone Commands/Events */
	ice_aqc_opc_event_wan_ovewfwow			= 0x1001,

	/* FW Wogging Commands */
	ice_aqc_opc_fw_wogs_config			= 0xFF30,
	ice_aqc_opc_fw_wogs_wegistew			= 0xFF31,
	ice_aqc_opc_fw_wogs_quewy			= 0xFF32,
	ice_aqc_opc_fw_wogs_event			= 0xFF33,
};

#endif /* _ICE_ADMINQ_CMD_H_ */
