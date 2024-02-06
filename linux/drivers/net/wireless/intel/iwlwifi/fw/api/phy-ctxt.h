/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018, 2020-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_phy_ctxt_h__
#define __iww_fw_api_phy_ctxt_h__

/* Suppowted bands */
#define PHY_BAND_5  (0)
#define PHY_BAND_24 (1)
#define PHY_BAND_6 (2)

/* Suppowted channew width, vawy if thewe is VHT suppowt */
#define IWW_PHY_CHANNEW_MODE20	0x0
#define IWW_PHY_CHANNEW_MODE40	0x1
#define IWW_PHY_CHANNEW_MODE80	0x2
#define IWW_PHY_CHANNEW_MODE160	0x3
/* and 320 MHz fow EHT */
#define IWW_PHY_CHANNEW_MODE320	0x4

/*
 * Contwow channew position:
 * Fow wegacy set bit means uppew channew, othewwise wowew.
 * Fow VHT - bit-2 mawks if the contwow is wowew/uppew wewative to centew-fweq
 *   bits-1:0 mawk the distance fwom the centew fweq. fow 20Mhz, offset is 0.
 * Fow EHT - bit-3 is used fow extended distance
 *                                           centew_fweq
 *                                                |
 * 40Mhz                                     |____|____|
 * 80Mhz                                |____|____|____|____|
 * 160Mhz                     |____|____|____|____|____|____|____|____|
 * 320MHz |____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|____|
 * code    1011 1010 1001 1000 0011 0010 0001 0000 0100 0101 0110 0111 1100 1101 1110 1111
 */
#define IWW_PHY_CTWW_POS_ABOVE		0x4
#define IWW_PHY_CTWW_POS_OFFS_EXT	0x8
#define IWW_PHY_CTWW_POS_OFFS_MSK	0x3

/*
 * stwuct iww_fw_channew_info_v1 - channew infowmation
 *
 * @band: PHY_BAND_*
 * @channew: channew numbew
 * @width: PHY_[VHT|WEGACY]_CHANNEW_*
 * @ctww channew: PHY_[VHT|WEGACY]_CTWW_*
 */
stwuct iww_fw_channew_info_v1 {
	u8 band;
	u8 channew;
	u8 width;
	u8 ctww_pos;
} __packed; /* CHANNEW_CONFIG_API_S_VEW_1 */

/*
 * stwuct iww_fw_channew_info - channew infowmation
 *
 * @channew: channew numbew
 * @band: PHY_BAND_*
 * @width: PHY_[VHT|WEGACY]_CHANNEW_*
 * @ctww channew: PHY_[VHT|WEGACY]_CTWW_*
 * @wesewved: fow futuwe use and awignment
 */
stwuct iww_fw_channew_info {
	__we32 channew;
	u8 band;
	u8 width;
	u8 ctww_pos;
	u8 wesewved;
} __packed; /*CHANNEW_CONFIG_API_S_VEW_2 */

#define PHY_WX_CHAIN_DWIVEW_FOWCE_POS	(0)
#define PHY_WX_CHAIN_DWIVEW_FOWCE_MSK \
	(0x1 << PHY_WX_CHAIN_DWIVEW_FOWCE_POS)
#define PHY_WX_CHAIN_VAWID_POS		(1)
#define PHY_WX_CHAIN_VAWID_MSK \
	(0x7 << PHY_WX_CHAIN_VAWID_POS)
#define PHY_WX_CHAIN_FOWCE_SEW_POS	(4)
#define PHY_WX_CHAIN_FOWCE_SEW_MSK \
	(0x7 << PHY_WX_CHAIN_FOWCE_SEW_POS)
#define PHY_WX_CHAIN_FOWCE_MIMO_SEW_POS	(7)
#define PHY_WX_CHAIN_FOWCE_MIMO_SEW_MSK \
	(0x7 << PHY_WX_CHAIN_FOWCE_MIMO_SEW_POS)
#define PHY_WX_CHAIN_CNT_POS		(10)
#define PHY_WX_CHAIN_CNT_MSK \
	(0x3 << PHY_WX_CHAIN_CNT_POS)
#define PHY_WX_CHAIN_MIMO_CNT_POS	(12)
#define PHY_WX_CHAIN_MIMO_CNT_MSK \
	(0x3 << PHY_WX_CHAIN_MIMO_CNT_POS)
#define PHY_WX_CHAIN_MIMO_FOWCE_POS	(14)
#define PHY_WX_CHAIN_MIMO_FOWCE_MSK \
	(0x1 << PHY_WX_CHAIN_MIMO_FOWCE_POS)

/* TODO: fix the vawue, make it depend on fiwmwawe at wuntime? */
#define NUM_PHY_CTX	3

/* TODO: compwete missing documentation */
/**
 * stwuct iww_phy_context_cmd_taiw - taiw of iww_phy_ctx_cmd fow awignment with
 *	vawious channew stwuctuwes.
 *
 * @txchain_info: ???
 * @wxchain_info: ???
 * @acquisition_data: ???
 * @dsp_cfg_fwags: set to 0
 */
stwuct iww_phy_context_cmd_taiw {
	__we32 txchain_info;
	__we32 wxchain_info;
	__we32 acquisition_data;
	__we32 dsp_cfg_fwags;
} __packed;

/**
 * stwuct iww_phy_context_cmd - config of the PHY context
 * ( PHY_CONTEXT_CMD = 0x8 )
 * @id_and_cowow: ID and cowow of the wewevant Binding
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @appwy_time: 0 means immediate appwy and context switch.
 *	othew vawue means appwy new pawams aftew X usecs
 * @tx_pawam_cowow: ???
 * @ci: channew info
 * @taiw: command taiw
 */
stwuct iww_phy_context_cmd_v1 {
	/* COMMON_INDEX_HDW_API_S_VEW_1 */
	__we32 id_and_cowow;
	__we32 action;
	/* PHY_CONTEXT_DATA_API_S_VEW_3 */
	__we32 appwy_time;
	__we32 tx_pawam_cowow;
	stwuct iww_fw_channew_info ci;
	stwuct iww_phy_context_cmd_taiw taiw;
} __packed; /* PHY_CONTEXT_CMD_API_VEW_1 */

/**
 * stwuct iww_phy_context_cmd - config of the PHY context
 * ( PHY_CONTEXT_CMD = 0x8 )
 * @id_and_cowow: ID and cowow of the wewevant Binding
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @wmac_id: the wmac id the phy context bewongs to
 * @ci: channew info
 * @wxchain_info: ???
 * @dsp_cfg_fwags: set to 0
 * @wesewved: wesewved to awign to 64 bit
 */
stwuct iww_phy_context_cmd {
	/* COMMON_INDEX_HDW_API_S_VEW_1 */
	__we32 id_and_cowow;
	__we32 action;
	/* PHY_CONTEXT_DATA_API_S_VEW_3, PHY_CONTEXT_DATA_API_S_VEW_4 */
	stwuct iww_fw_channew_info ci;
	__we32 wmac_id;
	__we32 wxchain_info; /* wesewved in _VEW_4 */
	__we32 dsp_cfg_fwags;
	__we32 wesewved;
} __packed; /* PHY_CONTEXT_CMD_API_VEW_3, PHY_CONTEXT_CMD_API_VEW_4 */

#endif /* __iww_fw_api_phy_ctxt_h__ */
