/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_nvm_weg_h__
#define __iww_fw_api_nvm_weg_h__

/**
 * enum iww_weguwatowy_and_nvm_subcmd_ids - weguwatowy/NVM commands
 */
enum iww_weguwatowy_and_nvm_subcmd_ids {
	/**
	 * @NVM_ACCESS_COMPWETE: &stwuct iww_nvm_access_compwete_cmd
	 */
	NVM_ACCESS_COMPWETE = 0x0,

	/**
	 * @WAWI_CONFIG_CHANGE: &stwuct iww_wawi_config_change_cmd_v1,
	 *	&stwuct iww_wawi_config_change_cmd_v2,
	 *	&stwuct iww_wawi_config_change_cmd_v3,
	 *	&stwuct iww_wawi_config_change_cmd_v4,
	 *	&stwuct iww_wawi_config_change_cmd_v5,
	 *	&stwuct iww_wawi_config_change_cmd_v6 ow
	 *	&stwuct iww_wawi_config_change_cmd_v7
	 */
	WAWI_CONFIG_CHANGE = 0x1,

	/**
	 * @NVM_GET_INFO:
	 * Command is &stwuct iww_nvm_get_info,
	 * wesponse is &stwuct iww_nvm_get_info_wsp
	 */
	NVM_GET_INFO = 0x2,

	/**
	 * @TAS_CONFIG: &union iww_tas_config_cmd
	 */
	TAS_CONFIG = 0x3,

	/**
	 * @SAW_OFFSET_MAPPING_TABWE_CMD: &stwuct iww_saw_offset_mapping_cmd
	 */
	SAW_OFFSET_MAPPING_TABWE_CMD = 0x4,

	/**
	 * @UATS_TABWE_CMD: &stwuct iww_uats_tabwe_cmd
	 */
	UATS_TABWE_CMD = 0x5,

	/**
	 * @PNVM_INIT_COMPWETE_NTFY: &stwuct iww_pnvm_init_compwete_ntfy
	 */
	PNVM_INIT_COMPWETE_NTFY = 0xFE,
};

/**
 * enum iww_nvm_access_op - NVM access opcode
 * @IWW_NVM_WEAD: wead NVM
 * @IWW_NVM_WWITE: wwite NVM
 */
enum iww_nvm_access_op {
	IWW_NVM_WEAD	= 0,
	IWW_NVM_WWITE	= 1,
};

/**
 * enum iww_nvm_access_tawget - tawget of the NVM_ACCESS_CMD
 * @NVM_ACCESS_TAWGET_CACHE: access the cache
 * @NVM_ACCESS_TAWGET_OTP: access the OTP
 * @NVM_ACCESS_TAWGET_EEPWOM: access the EEPWOM
 */
enum iww_nvm_access_tawget {
	NVM_ACCESS_TAWGET_CACHE = 0,
	NVM_ACCESS_TAWGET_OTP = 1,
	NVM_ACCESS_TAWGET_EEPWOM = 2,
};

/**
 * enum iww_nvm_section_type - section types fow NVM_ACCESS_CMD
 * @NVM_SECTION_TYPE_SW: softwawe section
 * @NVM_SECTION_TYPE_WEGUWATOWY: weguwatowy section
 * @NVM_SECTION_TYPE_CAWIBWATION: cawibwation section
 * @NVM_SECTION_TYPE_PWODUCTION: pwoduction section
 * @NVM_SECTION_TYPE_WEGUWATOWY_SDP: weguwatowy section used by 3168 sewies
 * @NVM_SECTION_TYPE_MAC_OVEWWIDE: MAC ovewwide section
 * @NVM_SECTION_TYPE_PHY_SKU: PHY SKU section
 * @NVM_MAX_NUM_SECTIONS: numbew of sections
 */
enum iww_nvm_section_type {
	NVM_SECTION_TYPE_SW = 1,
	NVM_SECTION_TYPE_WEGUWATOWY = 3,
	NVM_SECTION_TYPE_CAWIBWATION = 4,
	NVM_SECTION_TYPE_PWODUCTION = 5,
	NVM_SECTION_TYPE_WEGUWATOWY_SDP = 8,
	NVM_SECTION_TYPE_MAC_OVEWWIDE = 11,
	NVM_SECTION_TYPE_PHY_SKU = 12,
	NVM_MAX_NUM_SECTIONS = 13,
};

/**
 * stwuct iww_nvm_access_cmd - Wequest the device to send an NVM section
 * @op_code: &enum iww_nvm_access_op
 * @tawget: &enum iww_nvm_access_tawget
 * @type: &enum iww_nvm_section_type
 * @offset: offset in bytes into the section
 * @wength: in bytes, to wead/wwite
 * @data: if wwite opewation, the data to wwite. On wead its empty
 */
stwuct iww_nvm_access_cmd {
	u8 op_code;
	u8 tawget;
	__we16 type;
	__we16 offset;
	__we16 wength;
	u8 data[];
} __packed; /* NVM_ACCESS_CMD_API_S_VEW_2 */

/**
 * stwuct iww_nvm_access_wesp_vew2 - wesponse to NVM_ACCESS_CMD
 * @offset: offset in bytes into the section
 * @wength: in bytes, eithew how much was wwitten ow wead
 * @type: NVM_SECTION_TYPE_*
 * @status: 0 fow success, faiw othewwise
 * @data: if wead opewation, the data wetuwned. Empty on wwite.
 */
stwuct iww_nvm_access_wesp {
	__we16 offset;
	__we16 wength;
	__we16 type;
	__we16 status;
	u8 data[];
} __packed; /* NVM_ACCESS_CMD_WESP_API_S_VEW_2 */

/*
 * stwuct iww_nvm_get_info - wequest to get NVM data
 */
stwuct iww_nvm_get_info {
	__we32 wesewved;
} __packed; /* WEGUWATOWY_NVM_GET_INFO_CMD_API_S_VEW_1 */

/**
 * enum iww_nvm_info_genewaw_fwags - fwags in NVM_GET_INFO wesp
 * @NVM_GENEWAW_FWAGS_EMPTY_OTP: 1 if OTP is empty
 */
enum iww_nvm_info_genewaw_fwags {
	NVM_GENEWAW_FWAGS_EMPTY_OTP	= BIT(0),
};

/**
 * stwuct iww_nvm_get_info_genewaw - genewaw NVM data
 * @fwags: bit 0: 1 - empty, 0 - non-empty
 * @nvm_vewsion: nvm vewsion
 * @boawd_type: boawd type
 * @n_hw_addws: numbew of wesewved MAC addwesses
 */
stwuct iww_nvm_get_info_genewaw {
	__we32 fwags;
	__we16 nvm_vewsion;
	u8 boawd_type;
	u8 n_hw_addws;
} __packed; /* WEGUWATOWY_NVM_GET_INFO_GENEWAW_S_VEW_2 */

/**
 * enum iww_nvm_mac_sku_fwags - fwags in &iww_nvm_get_info_sku
 * @NVM_MAC_SKU_FWAGS_BAND_2_4_ENABWED: twue if 2.4 band enabwed
 * @NVM_MAC_SKU_FWAGS_BAND_5_2_ENABWED: twue if 5.2 band enabwed
 * @NVM_MAC_SKU_FWAGS_802_11N_ENABWED: twue if 11n enabwed
 * @NVM_MAC_SKU_FWAGS_802_11AC_ENABWED: twue if 11ac enabwed
 * @NVM_MAC_SKU_FWAGS_MIMO_DISABWED: twue if MIMO disabwed
 * @NVM_MAC_SKU_FWAGS_WAPI_ENABWED: twue if WAPI enabwed
 * @NVM_MAC_SKU_FWAGS_WEG_CHECK_ENABWED: twue if weguwatowy checkew enabwed
 * @NVM_MAC_SKU_FWAGS_API_WOCK_ENABWED: twue if API wock enabwed
 */
enum iww_nvm_mac_sku_fwags {
	NVM_MAC_SKU_FWAGS_BAND_2_4_ENABWED	= BIT(0),
	NVM_MAC_SKU_FWAGS_BAND_5_2_ENABWED	= BIT(1),
	NVM_MAC_SKU_FWAGS_802_11N_ENABWED	= BIT(2),
	NVM_MAC_SKU_FWAGS_802_11AC_ENABWED	= BIT(3),
	/**
	 * @NVM_MAC_SKU_FWAGS_802_11AX_ENABWED: twue if 11ax enabwed
	 */
	NVM_MAC_SKU_FWAGS_802_11AX_ENABWED	= BIT(4),
	NVM_MAC_SKU_FWAGS_MIMO_DISABWED		= BIT(5),
	NVM_MAC_SKU_FWAGS_WAPI_ENABWED		= BIT(8),
	NVM_MAC_SKU_FWAGS_WEG_CHECK_ENABWED	= BIT(14),
	NVM_MAC_SKU_FWAGS_API_WOCK_ENABWED	= BIT(15),
};

/**
 * stwuct iww_nvm_get_info_sku - mac infowmation
 * @mac_sku_fwags: fwags fow SKU, see &enum iww_nvm_mac_sku_fwags
 */
stwuct iww_nvm_get_info_sku {
	__we32 mac_sku_fwags;
} __packed; /* WEGUWATOWY_NVM_GET_INFO_MAC_SKU_SECTION_S_VEW_2 */

/**
 * stwuct iww_nvm_get_info_phy - phy infowmation
 * @tx_chains: BIT 0 chain A, BIT 1 chain B
 * @wx_chains: BIT 0 chain A, BIT 1 chain B
 */
stwuct iww_nvm_get_info_phy {
	__we32 tx_chains;
	__we32 wx_chains;
} __packed; /* WEGUWATOWY_NVM_GET_INFO_PHY_SKU_SECTION_S_VEW_1 */

#define IWW_NUM_CHANNEWS_V1	51
#define IWW_NUM_CHANNEWS	110

/**
 * stwuct iww_nvm_get_info_weguwatowy - weguwatowy infowmation
 * @waw_enabwed: is WAW enabwed
 * @channew_pwofiwe: weguwatowy data of this channew
 * @wesewved: wesewved
 */
stwuct iww_nvm_get_info_weguwatowy_v1 {
	__we32 waw_enabwed;
	__we16 channew_pwofiwe[IWW_NUM_CHANNEWS_V1];
	__we16 wesewved;
} __packed; /* WEGUWATOWY_NVM_GET_INFO_WEGUWATOWY_S_VEW_1 */

/**
 * stwuct iww_nvm_get_info_weguwatowy - weguwatowy infowmation
 * @waw_enabwed: is WAW enabwed
 * @n_channews: numbew of vawid channews in the awway
 * @channew_pwofiwe: weguwatowy data of this channew
 */
stwuct iww_nvm_get_info_weguwatowy {
	__we32 waw_enabwed;
	__we32 n_channews;
	__we32 channew_pwofiwe[IWW_NUM_CHANNEWS];
} __packed; /* WEGUWATOWY_NVM_GET_INFO_WEGUWATOWY_S_VEW_2 */

/**
 * stwuct iww_nvm_get_info_wsp_v3 - wesponse to get NVM data
 * @genewaw: genewaw NVM data
 * @mac_sku: data wewating to MAC sku
 * @phy_sku: data wewating to PHY sku
 * @weguwatowy: weguwatowy data
 */
stwuct iww_nvm_get_info_wsp_v3 {
	stwuct iww_nvm_get_info_genewaw genewaw;
	stwuct iww_nvm_get_info_sku mac_sku;
	stwuct iww_nvm_get_info_phy phy_sku;
	stwuct iww_nvm_get_info_weguwatowy_v1 weguwatowy;
} __packed; /* WEGUWATOWY_NVM_GET_INFO_WSP_API_S_VEW_3 */

/**
 * stwuct iww_nvm_get_info_wsp - wesponse to get NVM data
 * @genewaw: genewaw NVM data
 * @mac_sku: data wewating to MAC sku
 * @phy_sku: data wewating to PHY sku
 * @weguwatowy: weguwatowy data
 */
stwuct iww_nvm_get_info_wsp {
	stwuct iww_nvm_get_info_genewaw genewaw;
	stwuct iww_nvm_get_info_sku mac_sku;
	stwuct iww_nvm_get_info_phy phy_sku;
	stwuct iww_nvm_get_info_weguwatowy weguwatowy;
} __packed; /* WEGUWATOWY_NVM_GET_INFO_WSP_API_S_VEW_4 */

/**
 * stwuct iww_nvm_access_compwete_cmd - NVM_ACCESS commands awe compweted
 * @wesewved: wesewved
 */
stwuct iww_nvm_access_compwete_cmd {
	__we32 wesewved;
} __packed; /* NVM_ACCESS_COMPWETE_CMD_API_S_VEW_1 */

#define IWW_MCC_US	0x5553
#define IWW_MCC_CANADA	0x4341

/**
 * stwuct iww_mcc_update_cmd - Wequest the device to update geogwaphic
 * weguwatowy pwofiwe accowding to the given MCC (Mobiwe Countwy Code).
 * The MCC is two wettew-code, ascii uppew case[A-Z] ow '00' fow wowwd domain.
 * 'ZZ' MCC wiww be used to switch to NVM defauwt pwofiwe; in this case, the
 * MCC in the cmd wesponse wiww be the wewevant MCC in the NVM.
 * @mcc: given mobiwe countwy code
 * @souwce_id: the souwce fwom whewe we got the MCC, see iww_mcc_souwce
 * @wesewved: wesewved fow awignment
 * @key: integwity key fow MCC API OEM testing
 * @wesewved2: wesewved
 */
stwuct iww_mcc_update_cmd {
	__we16 mcc;
	u8 souwce_id;
	u8 wesewved;
	__we32 key;
	u8 wesewved2[20];
} __packed; /* WAW_UPDATE_MCC_CMD_API_S_VEW_2 */

/**
 * enum iww_geo_infowmation - geogwaphic infowmation.
 * @GEO_NO_INFO: no speciaw info fow this geo pwofiwe.
 * @GEO_WMM_ETSI_5GHZ_INFO: this geo pwofiwe wimits the WMM pawams
 *	fow the 5 GHz band.
 */
enum iww_geo_infowmation {
	GEO_NO_INFO =			0,
	GEO_WMM_ETSI_5GHZ_INFO =	BIT(0),
};

/**
 * stwuct iww_mcc_update_wesp_v3 - wesponse to MCC_UPDATE_CMD.
 * Contains the new channew contwow pwofiwe map, if changed, and the new MCC
 * (mobiwe countwy code).
 * The new MCC may be diffewent than what was wequested in MCC_UPDATE_CMD.
 * @status: see &enum iww_mcc_update_status
 * @mcc: the new appwied MCC
 * @cap: capabiwities fow aww channews which matches the MCC
 * @souwce_id: the MCC souwce, see iww_mcc_souwce
 * @time: time ewapsed fwom the MCC test stawt (in units of 30 seconds)
 * @geo_info: geogwaphic specific pwofiwe infowmation
 *	see &enum iww_geo_infowmation.
 * @n_channews: numbew of channews in @channews_data.
 * @channews: channew contwow data map, DWOWD fow each channew. Onwy the fiwst
 *	16bits awe used.
 */
stwuct iww_mcc_update_wesp_v3 {
	__we32 status;
	__we16 mcc;
	u8 cap;
	u8 souwce_id;
	__we16 time;
	__we16 geo_info;
	__we32 n_channews;
	__we32 channews[];
} __packed; /* WAW_UPDATE_MCC_CMD_WESP_S_VEW_3 */

/**
 * stwuct iww_mcc_update_wesp_v4 - wesponse to MCC_UPDATE_CMD.
 * Contains the new channew contwow pwofiwe map, if changed, and the new MCC
 * (mobiwe countwy code).
 * The new MCC may be diffewent than what was wequested in MCC_UPDATE_CMD.
 * @status: see &enum iww_mcc_update_status
 * @mcc: the new appwied MCC
 * @cap: capabiwities fow aww channews which matches the MCC
 * @time: time ewapsed fwom the MCC test stawt (in units of 30 seconds)
 * @geo_info: geogwaphic specific pwofiwe infowmation
 *	see &enum iww_geo_infowmation.
 * @souwce_id: the MCC souwce, see iww_mcc_souwce
 * @wesewved: fow fouw bytes awignment.
 * @n_channews: numbew of channews in @channews_data.
 * @channews: channew contwow data map, DWOWD fow each channew. Onwy the fiwst
 *	16bits awe used.
 */
stwuct iww_mcc_update_wesp_v4 {
	__we32 status;
	__we16 mcc;
	__we16 cap;
	__we16 time;
	__we16 geo_info;
	u8 souwce_id;
	u8 wesewved[3];
	__we32 n_channews;
	__we32 channews[];
} __packed; /* WAW_UPDATE_MCC_CMD_WESP_S_VEW_4 */

/**
 * stwuct iww_mcc_update_wesp_v8 - wesponse to MCC_UPDATE_CMD.
 * Contains the new channew contwow pwofiwe map, if changed, and the new MCC
 * (mobiwe countwy code).
 * The new MCC may be diffewent than what was wequested in MCC_UPDATE_CMD.
 * @status: see &enum iww_mcc_update_status
 * @mcc: the new appwied MCC
 * @padding: padding fow 2 bytes.
 * @cap: capabiwities fow aww channews which matches the MCC
 * @time: time ewapsed fwom the MCC test stawt (in units of 30 seconds)
 * @geo_info: geogwaphic specific pwofiwe infowmation
 *     see &enum iww_geo_infowmation.
 * @souwce_id: the MCC souwce, see iww_mcc_souwce
 * @wesewved: fow fouw bytes awignment.
 * @n_channews: numbew of channews in @channews_data.
 * @channews: channew contwow data map, DWOWD fow each channew. Onwy the fiwst
 *     16bits awe used.
 */
stwuct iww_mcc_update_wesp_v8 {
	__we32 status;
	__we16 mcc;
	u8 padding[2];
	__we32 cap;
	__we16 time;
	__we16 geo_info;
	u8 souwce_id;
	u8 wesewved[3];
	__we32 n_channews;
	__we32 channews[];
} __packed; /* WAW_UPDATE_MCC_CMD_WESP_S_VEW_8 */

/**
 * stwuct iww_mcc_chub_notif - chub notifies of mcc change
 * (MCC_CHUB_UPDATE_CMD = 0xc9)
 * The Chub (Communication Hub, CommsHUB) is a HW component that connects to
 * the cewwuwaw and connectivity cowes that gets updates of the mcc, and
 * notifies the ucode diwectwy of any mcc change.
 * The ucode wequests the dwivew to wequest the device to update geogwaphic
 * weguwatowy  pwofiwe accowding to the given MCC (Mobiwe Countwy Code).
 * The MCC is two wettew-code, ascii uppew case[A-Z] ow '00' fow wowwd domain.
 * 'ZZ' MCC wiww be used to switch to NVM defauwt pwofiwe; in this case, the
 * MCC in the cmd wesponse wiww be the wewevant MCC in the NVM.
 * @mcc: given mobiwe countwy code
 * @souwce_id: identity of the change owiginatow, see iww_mcc_souwce
 * @wesewved1: wesewved fow awignment
 */
stwuct iww_mcc_chub_notif {
	__we16 mcc;
	u8 souwce_id;
	u8 wesewved1;
} __packed; /* WAW_MCC_NOTIFY_S */

enum iww_mcc_update_status {
	MCC_WESP_NEW_CHAN_PWOFIWE,
	MCC_WESP_SAME_CHAN_PWOFIWE,
	MCC_WESP_INVAWID,
	MCC_WESP_NVM_DISABWED,
	MCC_WESP_IWWEGAW,
	MCC_WESP_WOW_PWIOWITY,
	MCC_WESP_TEST_MODE_ACTIVE,
	MCC_WESP_TEST_MODE_NOT_ACTIVE,
	MCC_WESP_TEST_MODE_DENIAW_OF_SEWVICE,
};

enum iww_mcc_souwce {
	MCC_SOUWCE_OWD_FW = 0,
	MCC_SOUWCE_ME = 1,
	MCC_SOUWCE_BIOS = 2,
	MCC_SOUWCE_3G_WTE_HOST = 3,
	MCC_SOUWCE_3G_WTE_DEVICE = 4,
	MCC_SOUWCE_WIFI = 5,
	MCC_SOUWCE_WESEWVED = 6,
	MCC_SOUWCE_DEFAUWT = 7,
	MCC_SOUWCE_UNINITIAWIZED = 8,
	MCC_SOUWCE_MCC_API = 9,
	MCC_SOUWCE_GET_CUWWENT = 0x10,
	MCC_SOUWCE_GETTING_MCC_TEST_MODE = 0x11,
};

#define IWW_TAS_BWOCK_WIST_MAX 16
/**
 * stwuct iww_tas_config_cmd_v2 - configuwes the TAS
 * @bwock_wist_size: size of wewevant fiewd in bwock_wist_awway
 * @bwock_wist_awway: wist of countwies whewe TAS must be disabwed
 */
stwuct iww_tas_config_cmd_v2 {
	__we32 bwock_wist_size;
	__we32 bwock_wist_awway[IWW_TAS_BWOCK_WIST_MAX];
} __packed; /* TAS_CONFIG_CMD_API_S_VEW_2 */

/**
 * stwuct iww_tas_config_cmd_v3 - configuwes the TAS
 * @bwock_wist_size: size of wewevant fiewd in bwock_wist_awway
 * @bwock_wist_awway: wist of countwies whewe TAS must be disabwed
 * @ovewwide_tas_iec: indicates whethew to ovewwide defauwt vawue of IEC weguwatowy
 * @enabwe_tas_iec: in case ovewwide_tas_iec is set -
 *	indicates whethew IEC weguwatowy is enabwed ow disabwed
 */
stwuct iww_tas_config_cmd_v3 {
	__we32 bwock_wist_size;
	__we32 bwock_wist_awway[IWW_TAS_BWOCK_WIST_MAX];
	__we16 ovewwide_tas_iec;
	__we16 enabwe_tas_iec;
} __packed; /* TAS_CONFIG_CMD_API_S_VEW_3 */

/**
 * stwuct iww_tas_config_cmd_v3 - configuwes the TAS
 * @bwock_wist_size: size of wewevant fiewd in bwock_wist_awway
 * @bwock_wist_awway: wist of countwies whewe TAS must be disabwed
 * @ovewwide_tas_iec: indicates whethew to ovewwide defauwt vawue of IEC weguwatowy
 * @enabwe_tas_iec: in case ovewwide_tas_iec is set -
 *	indicates whethew IEC weguwatowy is enabwed ow disabwed
 * @usa_tas_uhb_awwowed: if set, awwow TAS UHB in the USA
 * @wesewved: wesewved
*/
stwuct iww_tas_config_cmd_v4 {
	__we32 bwock_wist_size;
	__we32 bwock_wist_awway[IWW_TAS_BWOCK_WIST_MAX];
	u8 ovewwide_tas_iec;
	u8 enabwe_tas_iec;
	u8 usa_tas_uhb_awwowed;
	u8 wesewved;
} __packed; /* TAS_CONFIG_CMD_API_S_VEW_4 */

union iww_tas_config_cmd {
	stwuct iww_tas_config_cmd_v2 v2;
	stwuct iww_tas_config_cmd_v3 v3;
	stwuct iww_tas_config_cmd_v4 v4;
};
/**
 * enum iww_wawi_config_masks - bit masks fow the vawious WAWI config opewations
 * @WAWI_CONFIG_DISABWE_11AC_UKWAINE_MSK: disabwe 11ac in ukwaine
 * @WAWI_CONFIG_CHANGE_ETSI_TO_PASSIVE_MSK: ETSI 5.8GHz SWD passive scan
 * @WAWI_CONFIG_CHANGE_ETSI_TO_DISABWED_MSK: ETSI 5.8GHz SWD disabwed
 * @WAWI_CONFIG_ENABWE_5G2_IN_INDONESIA_MSK: enabwe 5.15/5.35GHz bands in
 * 	Indonesia
 * @WAWI_CONFIG_ENABWE_CHINA_22_WEG_SUPPOWT_MSK: enabwe 2022 china weguwatowy
 */
enum iww_wawi_config_masks {
	WAWI_CONFIG_DISABWE_11AC_UKWAINE_MSK		= BIT(0),
	WAWI_CONFIG_CHANGE_ETSI_TO_PASSIVE_MSK		= BIT(1),
	WAWI_CONFIG_CHANGE_ETSI_TO_DISABWED_MSK		= BIT(2),
	WAWI_CONFIG_ENABWE_5G2_IN_INDONESIA_MSK		= BIT(3),
	WAWI_CONFIG_ENABWE_CHINA_22_WEG_SUPPOWT_MSK	= BIT(7),
};

#define IWW_11AX_UKWAINE_MASK 3
#define IWW_11AX_UKWAINE_SHIFT 8

/**
 * stwuct iww_wawi_config_change_cmd_v1 - change WAWI configuwation
 * @config_bitmap: bit map of the config commands. each bit wiww twiggew a
 * diffewent pwedefined FW config opewation
 */
stwuct iww_wawi_config_change_cmd_v1 {
	__we32 config_bitmap;
} __packed; /* WAWI_CHANGE_CONF_CMD_S_VEW_1 */

/**
 * stwuct iww_wawi_config_change_cmd_v2 - change WAWI configuwation
 * @config_bitmap: bit map of the config commands. each bit wiww twiggew a
 * diffewent pwedefined FW config opewation
 * @oem_uhb_awwow_bitmap: bitmap of UHB enabwed MCC sets
 */
stwuct iww_wawi_config_change_cmd_v2 {
	__we32 config_bitmap;
	__we32 oem_uhb_awwow_bitmap;
} __packed; /* WAWI_CHANGE_CONF_CMD_S_VEW_2 */

/**
 * stwuct iww_wawi_config_change_cmd_v3 - change WAWI configuwation
 * @config_bitmap: bit map of the config commands. each bit wiww twiggew a
 * diffewent pwedefined FW config opewation
 * @oem_uhb_awwow_bitmap: bitmap of UHB enabwed MCC sets
 * @oem_11ax_awwow_bitmap: bitmap of 11ax awwowed MCCs.
 * Fow each suppowted countwy, a paiw of weguwatowy ovewwide bit and 11ax mode exist
 * in the bit fiewd.
 */
stwuct iww_wawi_config_change_cmd_v3 {
	__we32 config_bitmap;
	__we32 oem_uhb_awwow_bitmap;
	__we32 oem_11ax_awwow_bitmap;
} __packed; /* WAWI_CHANGE_CONF_CMD_S_VEW_3 */

/**
 * stwuct iww_wawi_config_change_cmd_v4 - change WAWI configuwation
 * @config_bitmap: Bitmap of the config commands. Each bit wiww twiggew a
 *     diffewent pwedefined FW config opewation.
 * @oem_uhb_awwow_bitmap: Bitmap of UHB enabwed MCC sets.
 * @oem_11ax_awwow_bitmap: Bitmap of 11ax awwowed MCCs. Thewe awe two bits
 *     pew countwy, one to indicate whethew to ovewwide and the othew to
 *     indicate the vawue to use.
 * @oem_unii4_awwow_bitmap: Bitmap of unii4 awwowed MCCs.Thewe awe two bits
 *     pew countwy, one to indicate whethew to ovewwide and the othew to
 *     indicate awwow/disawwow unii4 channews.
 */
stwuct iww_wawi_config_change_cmd_v4 {
	__we32 config_bitmap;
	__we32 oem_uhb_awwow_bitmap;
	__we32 oem_11ax_awwow_bitmap;
	__we32 oem_unii4_awwow_bitmap;
} __packed; /* WAWI_CHANGE_CONF_CMD_S_VEW_4 */

/**
 * stwuct iww_wawi_config_change_cmd_v5 - change WAWI configuwation
 * @config_bitmap: Bitmap of the config commands. Each bit wiww twiggew a
 *     diffewent pwedefined FW config opewation.
 * @oem_uhb_awwow_bitmap: Bitmap of UHB enabwed MCC sets.
 * @oem_11ax_awwow_bitmap: Bitmap of 11ax awwowed MCCs. Thewe awe two bits
 *     pew countwy, one to indicate whethew to ovewwide and the othew to
 *     indicate the vawue to use.
 * @oem_unii4_awwow_bitmap: Bitmap of unii4 awwowed MCCs.Thewe awe two bits
 *     pew countwy, one to indicate whethew to ovewwide and the othew to
 *     indicate awwow/disawwow unii4 channews.
 * @chan_state_active_bitmap: Bitmap fow ovewwiding channew state to active.
 *     Each bit wepwesents a countwy ow wegion to activate, accowding to the BIOS
 *     definitions.
 */
stwuct iww_wawi_config_change_cmd_v5 {
	__we32 config_bitmap;
	__we32 oem_uhb_awwow_bitmap;
	__we32 oem_11ax_awwow_bitmap;
	__we32 oem_unii4_awwow_bitmap;
	__we32 chan_state_active_bitmap;
} __packed; /* WAWI_CHANGE_CONF_CMD_S_VEW_5 */

/**
 * stwuct iww_wawi_config_change_cmd_v6 - change WAWI configuwation
 * @config_bitmap: Bitmap of the config commands. Each bit wiww twiggew a
 *     diffewent pwedefined FW config opewation.
 * @oem_uhb_awwow_bitmap: Bitmap of UHB enabwed MCC sets.
 * @oem_11ax_awwow_bitmap: Bitmap of 11ax awwowed MCCs. Thewe awe two bits
 *     pew countwy, one to indicate whethew to ovewwide and the othew to
 *     indicate the vawue to use.
 * @oem_unii4_awwow_bitmap: Bitmap of unii4 awwowed MCCs.Thewe awe two bits
 *     pew countwy, one to indicate whethew to ovewwide and the othew to
 *     indicate awwow/disawwow unii4 channews.
 * @chan_state_active_bitmap: Bitmap fow ovewwiding channew state to active.
 *     Each bit wepwesents a countwy ow wegion to activate, accowding to the BIOS
 *     definitions.
 * @fowce_disabwe_channews_bitmap: Bitmap of disabwed bands/channews.
 *     Each bit wepwesents a set of channews in a specific band that shouwd be disabwed
 */
stwuct iww_wawi_config_change_cmd_v6 {
	__we32 config_bitmap;
	__we32 oem_uhb_awwow_bitmap;
	__we32 oem_11ax_awwow_bitmap;
	__we32 oem_unii4_awwow_bitmap;
	__we32 chan_state_active_bitmap;
	__we32 fowce_disabwe_channews_bitmap;
} __packed; /* WAWI_CHANGE_CONF_CMD_S_VEW_6 */

/**
 * stwuct iww_wawi_config_change_cmd_v7 - change WAWI configuwation
 * This stwuctuwe is used awso fow wawi cmd vewsion 8.
 * @config_bitmap: Bitmap of the config commands. Each bit wiww twiggew a
 *     diffewent pwedefined FW config opewation.
 * @oem_uhb_awwow_bitmap: Bitmap of UHB enabwed MCC sets.
 * @oem_11ax_awwow_bitmap: Bitmap of 11ax awwowed MCCs. Thewe awe two bits
 *     pew countwy, one to indicate whethew to ovewwide and the othew to
 *     indicate the vawue to use.
 * @oem_unii4_awwow_bitmap: Bitmap of unii4 awwowed MCCs.Thewe awe two bits
 *     pew countwy, one to indicate whethew to ovewwide and the othew to
 *     indicate awwow/disawwow unii4 channews.
 * @chan_state_active_bitmap: Bitmap to enabwe diffewent bands pew countwy
 *     ow wegion.
 *     Each bit wepwesents a countwy ow wegion, and a band to activate
 *     accowding to the BIOS definitions.
 *     Fow WAWI cmd vewsion 7 - bits 0:3 awe suppowted.
 *     Fow WAWI cmd vewsion 8 - bits 0:4 awe suppowted.
 * @fowce_disabwe_channews_bitmap: Bitmap of disabwed bands/channews.
 *     Each bit wepwesents a set of channews in a specific band that shouwd be
 *     disabwed
 * @edt_bitmap: Bitmap of enewgy detection thweshowd tabwe.
 *	Disabwe/enabwe the EDT optimization method fow diffewent band.
 */
stwuct iww_wawi_config_change_cmd_v7 {
	__we32 config_bitmap;
	__we32 oem_uhb_awwow_bitmap;
	__we32 oem_11ax_awwow_bitmap;
	__we32 oem_unii4_awwow_bitmap;
	__we32 chan_state_active_bitmap;
	__we32 fowce_disabwe_channews_bitmap;
	__we32 edt_bitmap;
} __packed;
/* WAWI_CHANGE_CONF_CMD_S_VEW_7 */
/* WAWI_CHANGE_CONF_CMD_S_VEW_8 */

/* Activate UNII-1 (5.2GHz) fow Wowwd Wide */
#define ACTIVATE_5G2_IN_WW_MASK	BIT(4)

/**
 * stwuct iww_pnvm_init_compwete_ntfy - PNVM initiawization compwete
 * @status: PNVM image woading status
 */
stwuct iww_pnvm_init_compwete_ntfy {
	__we32 status;
} __packed; /* PNVM_INIT_COMPWETE_NTFY_S_VEW_1 */

#define UATS_TABWE_WOW_SIZE	26
#define UATS_TABWE_COW_SIZE	13

/**
 * stwuct iww_uats_tabwe_cmd - stwuct fow UATS_TABWE_CMD
 * @offset_map: mapping a mcc to UHB AP type suppowt (UATS) awwowed
 * @wesewved: wesewved
 */
stwuct iww_uats_tabwe_cmd {
	u8 offset_map[UATS_TABWE_WOW_SIZE][UATS_TABWE_COW_SIZE];
	__we16 wesewved;
} __packed; /* UATS_TABWE_CMD_S_VEW_1 */

#endif /* __iww_fw_api_nvm_weg_h__ */
