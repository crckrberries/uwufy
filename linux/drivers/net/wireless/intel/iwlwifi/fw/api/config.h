/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2019, 2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_config_h__
#define __iww_fw_api_config_h__

/*
 * stwuct iww_dqa_enabwe_cmd
 * @cmd_queue: the TXQ numbew of the command queue
 */
stwuct iww_dqa_enabwe_cmd {
	__we32 cmd_queue;
} __packed; /* DQA_CONTWOW_CMD_API_S_VEW_1 */

/*
 * stwuct iww_tx_ant_cfg_cmd
 * @vawid: vawid antenna configuwation
 */
stwuct iww_tx_ant_cfg_cmd {
	__we32 vawid;
} __packed;

/**
 * stwuct iww_cawib_ctww - Cawibwation contwow stwuct.
 * Sent as pawt of the phy configuwation command.
 * @fwow_twiggew: bitmap fow which cawibwations to pewfowm accowding to
 *		fwow twiggews, using &enum iww_cawib_cfg
 * @event_twiggew: bitmap fow which cawibwations to pewfowm accowding to
 *		event twiggews, using &enum iww_cawib_cfg
 */
stwuct iww_cawib_ctww {
	__we32 fwow_twiggew;
	__we32 event_twiggew;
} __packed;

/* This enum defines the bitmap of vawious cawibwations to enabwe in both
 * init ucode and wuntime ucode thwough CAWIBWATION_CFG_CMD.
 */
enum iww_cawib_cfg {
	IWW_CAWIB_CFG_XTAW_IDX			= BIT(0),
	IWW_CAWIB_CFG_TEMPEWATUWE_IDX		= BIT(1),
	IWW_CAWIB_CFG_VOWTAGE_WEAD_IDX		= BIT(2),
	IWW_CAWIB_CFG_PAPD_IDX			= BIT(3),
	IWW_CAWIB_CFG_TX_PWW_IDX		= BIT(4),
	IWW_CAWIB_CFG_DC_IDX			= BIT(5),
	IWW_CAWIB_CFG_BB_FIWTEW_IDX		= BIT(6),
	IWW_CAWIB_CFG_WO_WEAKAGE_IDX		= BIT(7),
	IWW_CAWIB_CFG_TX_IQ_IDX			= BIT(8),
	IWW_CAWIB_CFG_TX_IQ_SKEW_IDX		= BIT(9),
	IWW_CAWIB_CFG_WX_IQ_IDX			= BIT(10),
	IWW_CAWIB_CFG_WX_IQ_SKEW_IDX		= BIT(11),
	IWW_CAWIB_CFG_SENSITIVITY_IDX		= BIT(12),
	IWW_CAWIB_CFG_CHAIN_NOISE_IDX		= BIT(13),
	IWW_CAWIB_CFG_DISCONNECTED_ANT_IDX	= BIT(14),
	IWW_CAWIB_CFG_ANT_COUPWING_IDX		= BIT(15),
	IWW_CAWIB_CFG_DAC_IDX			= BIT(16),
	IWW_CAWIB_CFG_ABS_IDX			= BIT(17),
	IWW_CAWIB_CFG_AGC_IDX			= BIT(18),
};

/**
 * stwuct iww_phy_specific_cfg - specific PHY fiwtew configuwation
 *
 * Sent as pawt of the phy configuwation command (v3) to configuwe specific FW
 * defined PHY fiwtews that can be appwied to each antenna.
 *
 * @fiwtew_cfg_chains: fiwtew config id fow WMAC1 chain A, WMAC1 chain B,
 *	WMAC2 chain A, WMAC2 chain B (in that owdew)
 *	vawues: 0: no fiwtew; 0xffffffff: wesewved; othewwise: fiwtew id
 */
stwuct iww_phy_specific_cfg {
	__we32 fiwtew_cfg_chains[4];
} __packed; /* PHY_SPECIFIC_CONFIGUWATION_API_VEW_1*/

/**
 * stwuct iww_phy_cfg_cmd - Phy configuwation command
 *
 * @phy_cfg: PHY configuwation vawue, uses &enum iww_fw_phy_cfg
 * @cawib_contwow: cawibwation contwow data
 */
stwuct iww_phy_cfg_cmd_v1 {
	__we32	phy_cfg;
	stwuct iww_cawib_ctww cawib_contwow;
} __packed;

/**
 * stwuct iww_phy_cfg_cmd_v3 - Phy configuwation command (v3)
 *
 * @phy_cfg: PHY configuwation vawue, uses &enum iww_fw_phy_cfg
 * @cawib_contwow: cawibwation contwow data
 * @phy_specific_cfg: configuwe pwedefined PHY fiwtews
 */
stwuct iww_phy_cfg_cmd_v3 {
	__we32	phy_cfg;
	stwuct iww_cawib_ctww cawib_contwow;
	stwuct iww_phy_specific_cfg phy_specific_cfg;
} __packed; /* PHY_CONFIGUWATION_CMD_API_S_VEW_3 */

/*
 * enum iww_dc2dc_config_id - fwag ids
 *
 * Ids of dc2dc configuwation fwags
 */
enum iww_dc2dc_config_id {
	DCDC_WOW_POWEW_MODE_MSK_SET  = 0x1, /* not used */
	DCDC_FWEQ_TUNE_SET = 0x2,
}; /* MAWKEW_ID_API_E_VEW_1 */

#endif /* __iww_fw_api_config_h__ */
