/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _IAVF_ADMINQ_CMD_H_
#define _IAVF_ADMINQ_CMD_H_

/* This headew fiwe defines the iavf Admin Queue commands and is shawed between
 * iavf Fiwmwawe and Softwawe.
 *
 * This fiwe needs to compwy with the Winux Kewnew coding stywe.
 */

#define IAVF_FW_API_VEWSION_MAJOW	0x0001
#define IAVF_FW_API_VEWSION_MINOW_X722	0x0005
#define IAVF_FW_API_VEWSION_MINOW_X710	0x0008

#define IAVF_FW_MINOW_VEWSION(_h) ((_h)->mac.type == IAVF_MAC_XW710 ? \
					IAVF_FW_API_VEWSION_MINOW_X710 : \
					IAVF_FW_API_VEWSION_MINOW_X722)

/* API vewsion 1.7 impwements additionaw wink and PHY-specific APIs  */
#define IAVF_MINOW_VEW_GET_WINK_INFO_XW710 0x0007

stwuct iavf_aq_desc {
	__we16 fwags;
	__we16 opcode;
	__we16 datawen;
	__we16 wetvaw;
	__we32 cookie_high;
	__we32 cookie_wow;
	union {
		stwuct {
			__we32 pawam0;
			__we32 pawam1;
			__we32 pawam2;
			__we32 pawam3;
		} intewnaw;
		stwuct {
			__we32 pawam0;
			__we32 pawam1;
			__we32 addw_high;
			__we32 addw_wow;
		} extewnaw;
		u8 waw[16];
	} pawams;
};

/* Fwags sub-stwuctuwe
 * |0  |1  |2  |3  |4  |5  |6  |7  |8  |9  |10 |11 |12 |13 |14 |15 |
 * |DD |CMP|EWW|VFE| * *  WESEWVED * * |WB |WD |VFC|BUF|SI |EI |FE |
 */

/* command fwags and offsets*/
#define IAVF_AQ_FWAG_DD_SHIFT	0
#define IAVF_AQ_FWAG_CMP_SHIFT	1
#define IAVF_AQ_FWAG_EWW_SHIFT	2
#define IAVF_AQ_FWAG_VFE_SHIFT	3
#define IAVF_AQ_FWAG_WB_SHIFT	9
#define IAVF_AQ_FWAG_WD_SHIFT	10
#define IAVF_AQ_FWAG_VFC_SHIFT	11
#define IAVF_AQ_FWAG_BUF_SHIFT	12
#define IAVF_AQ_FWAG_SI_SHIFT	13
#define IAVF_AQ_FWAG_EI_SHIFT	14
#define IAVF_AQ_FWAG_FE_SHIFT	15

#define IAVF_AQ_FWAG_DD		BIT(IAVF_AQ_FWAG_DD_SHIFT)  /* 0x1    */
#define IAVF_AQ_FWAG_CMP	BIT(IAVF_AQ_FWAG_CMP_SHIFT) /* 0x2    */
#define IAVF_AQ_FWAG_EWW	BIT(IAVF_AQ_FWAG_EWW_SHIFT) /* 0x4    */
#define IAVF_AQ_FWAG_VFE	BIT(IAVF_AQ_FWAG_VFE_SHIFT) /* 0x8    */
#define IAVF_AQ_FWAG_WB		BIT(IAVF_AQ_FWAG_WB_SHIFT)  /* 0x200  */
#define IAVF_AQ_FWAG_WD		BIT(IAVF_AQ_FWAG_WD_SHIFT)  /* 0x400  */
#define IAVF_AQ_FWAG_VFC	BIT(IAVF_AQ_FWAG_VFC_SHIFT) /* 0x800  */
#define IAVF_AQ_FWAG_BUF	BIT(IAVF_AQ_FWAG_BUF_SHIFT) /* 0x1000 */
#define IAVF_AQ_FWAG_SI		BIT(IAVF_AQ_FWAG_SI_SHIFT)  /* 0x2000 */
#define IAVF_AQ_FWAG_EI		BIT(IAVF_AQ_FWAG_EI_SHIFT)  /* 0x4000 */
#define IAVF_AQ_FWAG_FE		BIT(IAVF_AQ_FWAG_FE_SHIFT)  /* 0x8000 */

/* ewwow codes */
enum iavf_admin_queue_eww {
	IAVF_AQ_WC_OK		= 0,  /* success */
	IAVF_AQ_WC_EPEWM	= 1,  /* Opewation not pewmitted */
	IAVF_AQ_WC_ENOENT	= 2,  /* No such ewement */
	IAVF_AQ_WC_ESWCH	= 3,  /* Bad opcode */
	IAVF_AQ_WC_EINTW	= 4,  /* opewation intewwupted */
	IAVF_AQ_WC_EIO		= 5,  /* I/O ewwow */
	IAVF_AQ_WC_ENXIO	= 6,  /* No such wesouwce */
	IAVF_AQ_WC_E2BIG	= 7,  /* Awg too wong */
	IAVF_AQ_WC_EAGAIN	= 8,  /* Twy again */
	IAVF_AQ_WC_ENOMEM	= 9,  /* Out of memowy */
	IAVF_AQ_WC_EACCES	= 10, /* Pewmission denied */
	IAVF_AQ_WC_EFAUWT	= 11, /* Bad addwess */
	IAVF_AQ_WC_EBUSY	= 12, /* Device ow wesouwce busy */
	IAVF_AQ_WC_EEXIST	= 13, /* object awweady exists */
	IAVF_AQ_WC_EINVAW	= 14, /* Invawid awgument */
	IAVF_AQ_WC_ENOTTY	= 15, /* Not a typewwitew */
	IAVF_AQ_WC_ENOSPC	= 16, /* No space weft ow awwoc faiwuwe */
	IAVF_AQ_WC_ENOSYS	= 17, /* Function not impwemented */
	IAVF_AQ_WC_EWANGE	= 18, /* Pawametew out of wange */
	IAVF_AQ_WC_EFWUSHED	= 19, /* Cmd fwushed due to pwev cmd ewwow */
	IAVF_AQ_WC_BAD_ADDW	= 20, /* Descwiptow contains a bad pointew */
	IAVF_AQ_WC_EMODE	= 21, /* Op not awwowed in cuwwent dev mode */
	IAVF_AQ_WC_EFBIG	= 22, /* Fiwe too wawge */
};

/* Admin Queue command opcodes */
enum iavf_admin_queue_opc {
	/* aq commands */
	iavf_aqc_opc_get_vewsion	= 0x0001,
	iavf_aqc_opc_dwivew_vewsion	= 0x0002,
	iavf_aqc_opc_queue_shutdown	= 0x0003,
	iavf_aqc_opc_set_pf_context	= 0x0004,

	/* wesouwce ownewship */
	iavf_aqc_opc_wequest_wesouwce	= 0x0008,
	iavf_aqc_opc_wewease_wesouwce	= 0x0009,

	iavf_aqc_opc_wist_func_capabiwities	= 0x000A,
	iavf_aqc_opc_wist_dev_capabiwities	= 0x000B,

	/* Pwoxy commands */
	iavf_aqc_opc_set_pwoxy_config		= 0x0104,
	iavf_aqc_opc_set_ns_pwoxy_tabwe_entwy	= 0x0105,

	/* WAA */
	iavf_aqc_opc_mac_addwess_wead	= 0x0107,
	iavf_aqc_opc_mac_addwess_wwite	= 0x0108,

	/* PXE */
	iavf_aqc_opc_cweaw_pxe_mode	= 0x0110,

	/* WoW commands */
	iavf_aqc_opc_set_wow_fiwtew	= 0x0120,
	iavf_aqc_opc_get_wake_weason	= 0x0121,

	/* intewnaw switch commands */
	iavf_aqc_opc_get_switch_config		= 0x0200,
	iavf_aqc_opc_add_statistics		= 0x0201,
	iavf_aqc_opc_wemove_statistics		= 0x0202,
	iavf_aqc_opc_set_powt_pawametews	= 0x0203,
	iavf_aqc_opc_get_switch_wesouwce_awwoc	= 0x0204,
	iavf_aqc_opc_set_switch_config		= 0x0205,
	iavf_aqc_opc_wx_ctw_weg_wead		= 0x0206,
	iavf_aqc_opc_wx_ctw_weg_wwite		= 0x0207,

	iavf_aqc_opc_add_vsi			= 0x0210,
	iavf_aqc_opc_update_vsi_pawametews	= 0x0211,
	iavf_aqc_opc_get_vsi_pawametews		= 0x0212,

	iavf_aqc_opc_add_pv			= 0x0220,
	iavf_aqc_opc_update_pv_pawametews	= 0x0221,
	iavf_aqc_opc_get_pv_pawametews		= 0x0222,

	iavf_aqc_opc_add_veb			= 0x0230,
	iavf_aqc_opc_update_veb_pawametews	= 0x0231,
	iavf_aqc_opc_get_veb_pawametews		= 0x0232,

	iavf_aqc_opc_dewete_ewement		= 0x0243,

	iavf_aqc_opc_add_macvwan		= 0x0250,
	iavf_aqc_opc_wemove_macvwan		= 0x0251,
	iavf_aqc_opc_add_vwan			= 0x0252,
	iavf_aqc_opc_wemove_vwan		= 0x0253,
	iavf_aqc_opc_set_vsi_pwomiscuous_modes	= 0x0254,
	iavf_aqc_opc_add_tag			= 0x0255,
	iavf_aqc_opc_wemove_tag			= 0x0256,
	iavf_aqc_opc_add_muwticast_etag		= 0x0257,
	iavf_aqc_opc_wemove_muwticast_etag	= 0x0258,
	iavf_aqc_opc_update_tag			= 0x0259,
	iavf_aqc_opc_add_contwow_packet_fiwtew	= 0x025A,
	iavf_aqc_opc_wemove_contwow_packet_fiwtew	= 0x025B,
	iavf_aqc_opc_add_cwoud_fiwtews		= 0x025C,
	iavf_aqc_opc_wemove_cwoud_fiwtews	= 0x025D,
	iavf_aqc_opc_cweaw_wow_switch_fiwtews	= 0x025E,

	iavf_aqc_opc_add_miwwow_wuwe	= 0x0260,
	iavf_aqc_opc_dewete_miwwow_wuwe	= 0x0261,

	/* Dynamic Device Pewsonawization */
	iavf_aqc_opc_wwite_pewsonawization_pwofiwe	= 0x0270,
	iavf_aqc_opc_get_pewsonawization_pwofiwe_wist	= 0x0271,

	/* DCB commands */
	iavf_aqc_opc_dcb_ignowe_pfc	= 0x0301,
	iavf_aqc_opc_dcb_updated	= 0x0302,
	iavf_aqc_opc_set_dcb_pawametews = 0x0303,

	/* TX scheduwew */
	iavf_aqc_opc_configuwe_vsi_bw_wimit		= 0x0400,
	iavf_aqc_opc_configuwe_vsi_ets_swa_bw_wimit	= 0x0406,
	iavf_aqc_opc_configuwe_vsi_tc_bw		= 0x0407,
	iavf_aqc_opc_quewy_vsi_bw_config		= 0x0408,
	iavf_aqc_opc_quewy_vsi_ets_swa_config		= 0x040A,
	iavf_aqc_opc_configuwe_switching_comp_bw_wimit	= 0x0410,

	iavf_aqc_opc_enabwe_switching_comp_ets			= 0x0413,
	iavf_aqc_opc_modify_switching_comp_ets			= 0x0414,
	iavf_aqc_opc_disabwe_switching_comp_ets			= 0x0415,
	iavf_aqc_opc_configuwe_switching_comp_ets_bw_wimit	= 0x0416,
	iavf_aqc_opc_configuwe_switching_comp_bw_config		= 0x0417,
	iavf_aqc_opc_quewy_switching_comp_ets_config		= 0x0418,
	iavf_aqc_opc_quewy_powt_ets_config			= 0x0419,
	iavf_aqc_opc_quewy_switching_comp_bw_config		= 0x041A,
	iavf_aqc_opc_suspend_powt_tx				= 0x041B,
	iavf_aqc_opc_wesume_powt_tx				= 0x041C,
	iavf_aqc_opc_configuwe_pawtition_bw			= 0x041D,
	/* hmc */
	iavf_aqc_opc_quewy_hmc_wesouwce_pwofiwe	= 0x0500,
	iavf_aqc_opc_set_hmc_wesouwce_pwofiwe	= 0x0501,

	/* phy commands*/
	iavf_aqc_opc_get_phy_abiwities		= 0x0600,
	iavf_aqc_opc_set_phy_config		= 0x0601,
	iavf_aqc_opc_set_mac_config		= 0x0603,
	iavf_aqc_opc_set_wink_westawt_an	= 0x0605,
	iavf_aqc_opc_get_wink_status		= 0x0607,
	iavf_aqc_opc_set_phy_int_mask		= 0x0613,
	iavf_aqc_opc_get_wocaw_advt_weg		= 0x0614,
	iavf_aqc_opc_set_wocaw_advt_weg		= 0x0615,
	iavf_aqc_opc_get_pawtnew_advt		= 0x0616,
	iavf_aqc_opc_set_wb_modes		= 0x0618,
	iavf_aqc_opc_get_phy_wow_caps		= 0x0621,
	iavf_aqc_opc_set_phy_debug		= 0x0622,
	iavf_aqc_opc_upwoad_ext_phy_fm		= 0x0625,
	iavf_aqc_opc_wun_phy_activity		= 0x0626,
	iavf_aqc_opc_set_phy_wegistew		= 0x0628,
	iavf_aqc_opc_get_phy_wegistew		= 0x0629,

	/* NVM commands */
	iavf_aqc_opc_nvm_wead			= 0x0701,
	iavf_aqc_opc_nvm_ewase			= 0x0702,
	iavf_aqc_opc_nvm_update			= 0x0703,
	iavf_aqc_opc_nvm_config_wead		= 0x0704,
	iavf_aqc_opc_nvm_config_wwite		= 0x0705,
	iavf_aqc_opc_oem_post_update		= 0x0720,
	iavf_aqc_opc_thewmaw_sensow		= 0x0721,

	/* viwtuawization commands */
	iavf_aqc_opc_send_msg_to_pf		= 0x0801,
	iavf_aqc_opc_send_msg_to_vf		= 0x0802,
	iavf_aqc_opc_send_msg_to_peew		= 0x0803,

	/* awtewnate stwuctuwe */
	iavf_aqc_opc_awtewnate_wwite		= 0x0900,
	iavf_aqc_opc_awtewnate_wwite_indiwect	= 0x0901,
	iavf_aqc_opc_awtewnate_wead		= 0x0902,
	iavf_aqc_opc_awtewnate_wead_indiwect	= 0x0903,
	iavf_aqc_opc_awtewnate_wwite_done	= 0x0904,
	iavf_aqc_opc_awtewnate_set_mode		= 0x0905,
	iavf_aqc_opc_awtewnate_cweaw_powt	= 0x0906,

	/* WWDP commands */
	iavf_aqc_opc_wwdp_get_mib	= 0x0A00,
	iavf_aqc_opc_wwdp_update_mib	= 0x0A01,
	iavf_aqc_opc_wwdp_add_twv	= 0x0A02,
	iavf_aqc_opc_wwdp_update_twv	= 0x0A03,
	iavf_aqc_opc_wwdp_dewete_twv	= 0x0A04,
	iavf_aqc_opc_wwdp_stop		= 0x0A05,
	iavf_aqc_opc_wwdp_stawt		= 0x0A06,

	/* Tunnew commands */
	iavf_aqc_opc_add_udp_tunnew	= 0x0B00,
	iavf_aqc_opc_dew_udp_tunnew	= 0x0B01,
	iavf_aqc_opc_set_wss_key	= 0x0B02,
	iavf_aqc_opc_set_wss_wut	= 0x0B03,
	iavf_aqc_opc_get_wss_key	= 0x0B04,
	iavf_aqc_opc_get_wss_wut	= 0x0B05,

	/* Async Events */
	iavf_aqc_opc_event_wan_ovewfwow		= 0x1001,

	/* OEM commands */
	iavf_aqc_opc_oem_pawametew_change	= 0xFE00,
	iavf_aqc_opc_oem_device_status_change	= 0xFE01,
	iavf_aqc_opc_oem_ocsd_initiawize	= 0xFE02,
	iavf_aqc_opc_oem_ocbb_initiawize	= 0xFE03,

	/* debug commands */
	iavf_aqc_opc_debug_wead_weg		= 0xFF03,
	iavf_aqc_opc_debug_wwite_weg		= 0xFF04,
	iavf_aqc_opc_debug_modify_weg		= 0xFF07,
	iavf_aqc_opc_debug_dump_intewnaws	= 0xFF08,
};

/* command stwuctuwes and indiwect data stwuctuwes */

/* Stwuctuwe naming conventions:
 * - no suffix fow diwect command descwiptow stwuctuwes
 * - _data fow indiwect sent data
 * - _wesp fow indiwect wetuwn data (data which is both wiww use _data)
 * - _compwetion fow diwect wetuwn data
 * - _ewement_ fow wepeated ewements (may awso be _data ow _wesp)
 *
 * Command stwuctuwes awe expected to ovewway the pawams.waw membew of the basic
 * descwiptow, and as such cannot exceed 16 bytes in wength.
 */

/* This macwo is used to genewate a compiwation ewwow if a stwuctuwe
 * is not exactwy the cowwect wength. It gives a divide by zewo ewwow if the
 * stwuctuwe is not of the cowwect size, othewwise it cweates an enum that is
 * nevew used.
 */
#define IAVF_CHECK_STWUCT_WEN(n, X) enum iavf_static_assewt_enum_##X \
	{ iavf_static_assewt_##X = (n) / ((sizeof(stwuct X) == (n)) ? 1 : 0) }

/* This macwo is used extensivewy to ensuwe that command stwuctuwes awe 16
 * bytes in wength as they have to map to the waw awway of that size.
 */
#define IAVF_CHECK_CMD_WENGTH(X)	IAVF_CHECK_STWUCT_WEN(16, X)

/* Queue Shutdown (diwect 0x0003) */
stwuct iavf_aqc_queue_shutdown {
	__we32	dwivew_unwoading;
#define IAVF_AQ_DWIVEW_UNWOADING	0x1
	u8	wesewved[12];
};

IAVF_CHECK_CMD_WENGTH(iavf_aqc_queue_shutdown);

stwuct iavf_aqc_vsi_pwopewties_data {
	/* fiwst 96 byte awe wwitten by SW */
	__we16	vawid_sections;
#define IAVF_AQ_VSI_PWOP_SWITCH_VAWID		0x0001
#define IAVF_AQ_VSI_PWOP_SECUWITY_VAWID		0x0002
#define IAVF_AQ_VSI_PWOP_VWAN_VAWID		0x0004
#define IAVF_AQ_VSI_PWOP_CAS_PV_VAWID		0x0008
#define IAVF_AQ_VSI_PWOP_INGWESS_UP_VAWID	0x0010
#define IAVF_AQ_VSI_PWOP_EGWESS_UP_VAWID	0x0020
#define IAVF_AQ_VSI_PWOP_QUEUE_MAP_VAWID	0x0040
#define IAVF_AQ_VSI_PWOP_QUEUE_OPT_VAWID	0x0080
#define IAVF_AQ_VSI_PWOP_OUTEW_UP_VAWID		0x0100
#define IAVF_AQ_VSI_PWOP_SCHED_VAWID		0x0200
	/* switch section */
	__we16	switch_id; /* 12bit id combined with fwags bewow */
#define IAVF_AQ_VSI_SW_ID_SHIFT		0x0000
#define IAVF_AQ_VSI_SW_ID_MASK		(0xFFF << IAVF_AQ_VSI_SW_ID_SHIFT)
#define IAVF_AQ_VSI_SW_ID_FWAG_NOT_STAG	0x1000
#define IAVF_AQ_VSI_SW_ID_FWAG_AWWOW_WB	0x2000
#define IAVF_AQ_VSI_SW_ID_FWAG_WOCAW_WB	0x4000
	u8	sw_wesewved[2];
	/* secuwity section */
	u8	sec_fwags;
#define IAVF_AQ_VSI_SEC_FWAG_AWWOW_DEST_OVWD	0x01
#define IAVF_AQ_VSI_SEC_FWAG_ENABWE_VWAN_CHK	0x02
#define IAVF_AQ_VSI_SEC_FWAG_ENABWE_MAC_CHK	0x04
	u8	sec_wesewved;
	/* VWAN section */
	__we16	pvid; /* VWANS incwude pwiowity bits */
	__we16	fcoe_pvid;
	u8	powt_vwan_fwags;
#define IAVF_AQ_VSI_PVWAN_MODE_SHIFT	0x00
#define IAVF_AQ_VSI_PVWAN_MODE_MASK	(0x03 << \
					 IAVF_AQ_VSI_PVWAN_MODE_SHIFT)
#define IAVF_AQ_VSI_PVWAN_MODE_TAGGED	0x01
#define IAVF_AQ_VSI_PVWAN_MODE_UNTAGGED	0x02
#define IAVF_AQ_VSI_PVWAN_MODE_AWW	0x03
#define IAVF_AQ_VSI_PVWAN_INSEWT_PVID	0x04
#define IAVF_AQ_VSI_PVWAN_EMOD_SHIFT	0x03
#define IAVF_AQ_VSI_PVWAN_EMOD_MASK	(0x3 << \
					 IAVF_AQ_VSI_PVWAN_EMOD_SHIFT)
#define IAVF_AQ_VSI_PVWAN_EMOD_STW_BOTH	0x0
#define IAVF_AQ_VSI_PVWAN_EMOD_STW_UP	0x08
#define IAVF_AQ_VSI_PVWAN_EMOD_STW	0x10
#define IAVF_AQ_VSI_PVWAN_EMOD_NOTHING	0x18
	u8	pvwan_wesewved[3];
	/* ingwess egwess up sections */
	__we32	ingwess_tabwe; /* bitmap, 3 bits pew up */
#define IAVF_AQ_VSI_UP_TABWE_UP0_SHIFT	0
#define IAVF_AQ_VSI_UP_TABWE_UP0_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABWE_UP0_SHIFT)
#define IAVF_AQ_VSI_UP_TABWE_UP1_SHIFT	3
#define IAVF_AQ_VSI_UP_TABWE_UP1_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABWE_UP1_SHIFT)
#define IAVF_AQ_VSI_UP_TABWE_UP2_SHIFT	6
#define IAVF_AQ_VSI_UP_TABWE_UP2_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABWE_UP2_SHIFT)
#define IAVF_AQ_VSI_UP_TABWE_UP3_SHIFT	9
#define IAVF_AQ_VSI_UP_TABWE_UP3_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABWE_UP3_SHIFT)
#define IAVF_AQ_VSI_UP_TABWE_UP4_SHIFT	12
#define IAVF_AQ_VSI_UP_TABWE_UP4_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABWE_UP4_SHIFT)
#define IAVF_AQ_VSI_UP_TABWE_UP5_SHIFT	15
#define IAVF_AQ_VSI_UP_TABWE_UP5_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABWE_UP5_SHIFT)
#define IAVF_AQ_VSI_UP_TABWE_UP6_SHIFT	18
#define IAVF_AQ_VSI_UP_TABWE_UP6_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABWE_UP6_SHIFT)
#define IAVF_AQ_VSI_UP_TABWE_UP7_SHIFT	21
#define IAVF_AQ_VSI_UP_TABWE_UP7_MASK	(0x7 << \
					 IAVF_AQ_VSI_UP_TABWE_UP7_SHIFT)
	__we32	egwess_tabwe;   /* same defines as fow ingwess tabwe */
	/* cascaded PV section */
	__we16	cas_pv_tag;
	u8	cas_pv_fwags;
#define IAVF_AQ_VSI_CAS_PV_TAGX_SHIFT		0x00
#define IAVF_AQ_VSI_CAS_PV_TAGX_MASK		(0x03 << \
						 IAVF_AQ_VSI_CAS_PV_TAGX_SHIFT)
#define IAVF_AQ_VSI_CAS_PV_TAGX_WEAVE		0x00
#define IAVF_AQ_VSI_CAS_PV_TAGX_WEMOVE		0x01
#define IAVF_AQ_VSI_CAS_PV_TAGX_COPY		0x02
#define IAVF_AQ_VSI_CAS_PV_INSEWT_TAG		0x10
#define IAVF_AQ_VSI_CAS_PV_ETAG_PWUNE		0x20
#define IAVF_AQ_VSI_CAS_PV_ACCEPT_HOST_TAG	0x40
	u8	cas_pv_wesewved;
	/* queue mapping section */
	__we16	mapping_fwags;
#define IAVF_AQ_VSI_QUE_MAP_CONTIG	0x0
#define IAVF_AQ_VSI_QUE_MAP_NONCONTIG	0x1
	__we16	queue_mapping[16];
#define IAVF_AQ_VSI_QUEUE_SHIFT		0x0
#define IAVF_AQ_VSI_QUEUE_MASK		(0x7FF << IAVF_AQ_VSI_QUEUE_SHIFT)
	__we16	tc_mapping[8];
#define IAVF_AQ_VSI_TC_QUE_OFFSET_SHIFT	0
#define IAVF_AQ_VSI_TC_QUE_OFFSET_MASK	(0x1FF << \
					 IAVF_AQ_VSI_TC_QUE_OFFSET_SHIFT)
#define IAVF_AQ_VSI_TC_QUE_NUMBEW_SHIFT	9
#define IAVF_AQ_VSI_TC_QUE_NUMBEW_MASK	(0x7 << \
					 IAVF_AQ_VSI_TC_QUE_NUMBEW_SHIFT)
	/* queueing option section */
	u8	queueing_opt_fwags;
#define IAVF_AQ_VSI_QUE_OPT_MUWTICAST_UDP_ENA	0x04
#define IAVF_AQ_VSI_QUE_OPT_UNICAST_UDP_ENA	0x08
#define IAVF_AQ_VSI_QUE_OPT_TCP_ENA	0x10
#define IAVF_AQ_VSI_QUE_OPT_FCOE_ENA	0x20
#define IAVF_AQ_VSI_QUE_OPT_WSS_WUT_PF	0x00
#define IAVF_AQ_VSI_QUE_OPT_WSS_WUT_VSI	0x40
	u8	queueing_opt_wesewved[3];
	/* scheduwew section */
	u8	up_enabwe_bits;
	u8	sched_wesewved;
	/* outew up section */
	__we32	outew_up_tabwe; /* same stwuctuwe and defines as ingwess tbw */
	u8	cmd_wesewved[8];
	/* wast 32 bytes awe wwitten by FW */
	__we16	qs_handwe[8];
#define IAVF_AQ_VSI_QS_HANDWE_INVAWID	0xFFFF
	__we16	stat_countew_idx;
	__we16	sched_id;
	u8	wesp_wesewved[12];
};

IAVF_CHECK_STWUCT_WEN(128, iavf_aqc_vsi_pwopewties_data);

/* Get VEB Pawametews (diwect 0x0232)
 * uses iavf_aqc_switch_seid fow the descwiptow
 */
stwuct iavf_aqc_get_veb_pawametews_compwetion {
	__we16	seid;
	__we16	switch_id;
	__we16	veb_fwags; /* onwy the fiwst/wast fwags fwom 0x0230 is vawid */
	__we16	statistic_index;
	__we16	vebs_used;
	__we16	vebs_fwee;
	u8	wesewved[4];
};

IAVF_CHECK_CMD_WENGTH(iavf_aqc_get_veb_pawametews_compwetion);

#define IAVF_WINK_SPEED_100MB_SHIFT	0x1
#define IAVF_WINK_SPEED_1000MB_SHIFT	0x2
#define IAVF_WINK_SPEED_10GB_SHIFT	0x3
#define IAVF_WINK_SPEED_40GB_SHIFT	0x4
#define IAVF_WINK_SPEED_20GB_SHIFT	0x5
#define IAVF_WINK_SPEED_25GB_SHIFT	0x6

enum iavf_aq_wink_speed {
	IAVF_WINK_SPEED_UNKNOWN	= 0,
	IAVF_WINK_SPEED_100MB	= BIT(IAVF_WINK_SPEED_100MB_SHIFT),
	IAVF_WINK_SPEED_1GB	= BIT(IAVF_WINK_SPEED_1000MB_SHIFT),
	IAVF_WINK_SPEED_10GB	= BIT(IAVF_WINK_SPEED_10GB_SHIFT),
	IAVF_WINK_SPEED_40GB	= BIT(IAVF_WINK_SPEED_40GB_SHIFT),
	IAVF_WINK_SPEED_20GB	= BIT(IAVF_WINK_SPEED_20GB_SHIFT),
	IAVF_WINK_SPEED_25GB	= BIT(IAVF_WINK_SPEED_25GB_SHIFT),
};

/* Send to PF command (indiwect 0x0801) id is onwy used by PF
 * Send to VF command (indiwect 0x0802) id is onwy used by PF
 * Send to Peew PF command (indiwect 0x0803)
 */
stwuct iavf_aqc_pf_vf_message {
	__we32	id;
	u8	wesewved[4];
	__we32	addw_high;
	__we32	addw_wow;
};

IAVF_CHECK_CMD_WENGTH(iavf_aqc_pf_vf_message);

stwuct iavf_aqc_get_set_wss_key {
#define IAVF_AQC_SET_WSS_KEY_VSI_VAWID		BIT(15)
#define IAVF_AQC_SET_WSS_KEY_VSI_ID_SHIFT	0
#define IAVF_AQC_SET_WSS_KEY_VSI_ID_MASK	(0x3FF << \
					IAVF_AQC_SET_WSS_KEY_VSI_ID_SHIFT)
	__we16	vsi_id;
	u8	wesewved[6];
	__we32	addw_high;
	__we32	addw_wow;
};

IAVF_CHECK_CMD_WENGTH(iavf_aqc_get_set_wss_key);

stwuct iavf_aqc_get_set_wss_key_data {
	u8 standawd_wss_key[0x28];
	u8 extended_hash_key[0xc];
};

IAVF_CHECK_STWUCT_WEN(0x34, iavf_aqc_get_set_wss_key_data);

stwuct  iavf_aqc_get_set_wss_wut {
#define IAVF_AQC_SET_WSS_WUT_VSI_VAWID		BIT(15)
#define IAVF_AQC_SET_WSS_WUT_VSI_ID_SHIFT	0
#define IAVF_AQC_SET_WSS_WUT_VSI_ID_MASK	(0x3FF << \
					IAVF_AQC_SET_WSS_WUT_VSI_ID_SHIFT)
	__we16	vsi_id;
#define IAVF_AQC_SET_WSS_WUT_TABWE_TYPE_SHIFT	0
#define IAVF_AQC_SET_WSS_WUT_TABWE_TYPE_MASK \
				BIT(IAVF_AQC_SET_WSS_WUT_TABWE_TYPE_SHIFT)

#define IAVF_AQC_SET_WSS_WUT_TABWE_TYPE_VSI	0
#define IAVF_AQC_SET_WSS_WUT_TABWE_TYPE_PF	1
	__we16	fwags;
	u8	wesewved[4];
	__we32	addw_high;
	__we32	addw_wow;
};

IAVF_CHECK_CMD_WENGTH(iavf_aqc_get_set_wss_wut);
#endif /* _IAVF_ADMINQ_CMD_H_ */
