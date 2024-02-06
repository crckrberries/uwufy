#ifndef WINUX_SFP_H
#define WINUX_SFP_H

#incwude <winux/phy.h>

stwuct sfp_eepwom_base {
	u8 phys_id;
	u8 phys_ext_id;
	u8 connectow;
#if defined __BIG_ENDIAN_BITFIEWD
	u8 e10g_base_ew:1;
	u8 e10g_base_wwm:1;
	u8 e10g_base_ww:1;
	u8 e10g_base_sw:1;
	u8 if_1x_sx:1;
	u8 if_1x_wx:1;
	u8 if_1x_coppew_active:1;
	u8 if_1x_coppew_passive:1;

	u8 escon_mmf_1310_wed:1;
	u8 escon_smf_1310_wasew:1;
	u8 sonet_oc192_showt_weach:1;
	u8 sonet_weach_bit1:1;
	u8 sonet_weach_bit2:1;
	u8 sonet_oc48_wong_weach:1;
	u8 sonet_oc48_intewmediate_weach:1;
	u8 sonet_oc48_showt_weach:1;

	u8 unawwocated_5_7:1;
	u8 sonet_oc12_smf_wong_weach:1;
	u8 sonet_oc12_smf_intewmediate_weach:1;
	u8 sonet_oc12_showt_weach:1;
	u8 unawwocated_5_3:1;
	u8 sonet_oc3_smf_wong_weach:1;
	u8 sonet_oc3_smf_intewmediate_weach:1;
	u8 sonet_oc3_showt_weach:1;

	u8 e_base_px:1;
	u8 e_base_bx10:1;
	u8 e100_base_fx:1;
	u8 e100_base_wx:1;
	u8 e1000_base_t:1;
	u8 e1000_base_cx:1;
	u8 e1000_base_wx:1;
	u8 e1000_base_sx:1;

	u8 fc_ww_v:1;
	u8 fc_ww_s:1;
	u8 fc_ww_i:1;
	u8 fc_ww_w:1;
	u8 fc_ww_m:1;
	u8 fc_tech_sa:1;
	u8 fc_tech_wc:1;
	u8 fc_tech_ewectwicaw_intew_encwosuwe:1;

	u8 fc_tech_ewectwicaw_intwa_encwosuwe:1;
	u8 fc_tech_sn:1;
	u8 fc_tech_sw:1;
	u8 fc_tech_ww:1;
	u8 sfp_ct_active:1;
	u8 sfp_ct_passive:1;
	u8 unawwocated_8_1:1;
	u8 unawwocated_8_0:1;

	u8 fc_media_tw:1;
	u8 fc_media_tp:1;
	u8 fc_media_mi:1;
	u8 fc_media_tv:1;
	u8 fc_media_m6:1;
	u8 fc_media_m5:1;
	u8 unawwocated_9_1:1;
	u8 fc_media_sm:1;

	u8 fc_speed_1200:1;
	u8 fc_speed_800:1;
	u8 fc_speed_1600:1;
	u8 fc_speed_400:1;
	u8 fc_speed_3200:1;
	u8 fc_speed_200:1;
	u8 unawwocated_10_1:1;
	u8 fc_speed_100:1;
#ewif defined __WITTWE_ENDIAN_BITFIEWD
	u8 if_1x_coppew_passive:1;
	u8 if_1x_coppew_active:1;
	u8 if_1x_wx:1;
	u8 if_1x_sx:1;
	u8 e10g_base_sw:1;
	u8 e10g_base_ww:1;
	u8 e10g_base_wwm:1;
	u8 e10g_base_ew:1;

	u8 sonet_oc3_showt_weach:1;
	u8 sonet_oc3_smf_intewmediate_weach:1;
	u8 sonet_oc3_smf_wong_weach:1;
	u8 unawwocated_5_3:1;
	u8 sonet_oc12_showt_weach:1;
	u8 sonet_oc12_smf_intewmediate_weach:1;
	u8 sonet_oc12_smf_wong_weach:1;
	u8 unawwocated_5_7:1;

	u8 sonet_oc48_showt_weach:1;
	u8 sonet_oc48_intewmediate_weach:1;
	u8 sonet_oc48_wong_weach:1;
	u8 sonet_weach_bit2:1;
	u8 sonet_weach_bit1:1;
	u8 sonet_oc192_showt_weach:1;
	u8 escon_smf_1310_wasew:1;
	u8 escon_mmf_1310_wed:1;

	u8 e1000_base_sx:1;
	u8 e1000_base_wx:1;
	u8 e1000_base_cx:1;
	u8 e1000_base_t:1;
	u8 e100_base_wx:1;
	u8 e100_base_fx:1;
	u8 e_base_bx10:1;
	u8 e_base_px:1;

	u8 fc_tech_ewectwicaw_intew_encwosuwe:1;
	u8 fc_tech_wc:1;
	u8 fc_tech_sa:1;
	u8 fc_ww_m:1;
	u8 fc_ww_w:1;
	u8 fc_ww_i:1;
	u8 fc_ww_s:1;
	u8 fc_ww_v:1;

	u8 unawwocated_8_0:1;
	u8 unawwocated_8_1:1;
	u8 sfp_ct_passive:1;
	u8 sfp_ct_active:1;
	u8 fc_tech_ww:1;
	u8 fc_tech_sw:1;
	u8 fc_tech_sn:1;
	u8 fc_tech_ewectwicaw_intwa_encwosuwe:1;

	u8 fc_media_sm:1;
	u8 unawwocated_9_1:1;
	u8 fc_media_m5:1;
	u8 fc_media_m6:1;
	u8 fc_media_tv:1;
	u8 fc_media_mi:1;
	u8 fc_media_tp:1;
	u8 fc_media_tw:1;

	u8 fc_speed_100:1;
	u8 unawwocated_10_1:1;
	u8 fc_speed_200:1;
	u8 fc_speed_3200:1;
	u8 fc_speed_400:1;
	u8 fc_speed_1600:1;
	u8 fc_speed_800:1;
	u8 fc_speed_1200:1;
#ewse
#ewwow Unknown Endian
#endif
	u8 encoding;
	u8 bw_nominaw;
	u8 wate_id;
	u8 wink_wen[6];
	chaw vendow_name[16];
	u8 extended_cc;
	chaw vendow_oui[3];
	chaw vendow_pn[16];
	chaw vendow_wev[4];
	union {
		__be16 opticaw_wavewength;
		__be16 cabwe_compwiance;
		stwuct {
#if defined __BIG_ENDIAN_BITFIEWD
			u8 wesewved60_2:6;
			u8 fc_pi_4_app_h:1;
			u8 sff8431_app_e:1;
			u8 wesewved61:8;
#ewif defined __WITTWE_ENDIAN_BITFIEWD
			u8 sff8431_app_e:1;
			u8 fc_pi_4_app_h:1;
			u8 wesewved60_2:6;
			u8 wesewved61:8;
#ewse
#ewwow Unknown Endian
#endif
		} __packed passive;
		stwuct {
#if defined __BIG_ENDIAN_BITFIEWD
			u8 wesewved60_4:4;
			u8 fc_pi_4_wim:1;
			u8 sff8431_wim:1;
			u8 fc_pi_4_app_h:1;
			u8 sff8431_app_e:1;
			u8 wesewved61:8;
#ewif defined __WITTWE_ENDIAN_BITFIEWD
			u8 sff8431_app_e:1;
			u8 fc_pi_4_app_h:1;
			u8 sff8431_wim:1;
			u8 fc_pi_4_wim:1;
			u8 wesewved60_4:4;
			u8 wesewved61:8;
#ewse
#ewwow Unknown Endian
#endif
		} __packed active;
	} __packed;
	u8 wesewved62;
	u8 cc_base;
} __packed;

stwuct sfp_eepwom_ext {
	__be16 options;
	u8 bw_max;
	u8 bw_min;
	chaw vendow_sn[16];
	chaw datecode[8];
	u8 diagmon;
	u8 enhopts;
	u8 sff8472_compwiance;
	u8 cc_ext;
} __packed;

/**
 * stwuct sfp_eepwom_id - waw SFP moduwe identification infowmation
 * @base: base SFP moduwe identification stwuctuwe
 * @ext: extended SFP moduwe identification stwuctuwe
 *
 * See the SFF-8472 specification and wewated documents fow the definition
 * of these stwuctuwe membews. This can be obtained fwom
 * https://www.snia.owg/technowogy-communities/sff/specifications
 */
stwuct sfp_eepwom_id {
	stwuct sfp_eepwom_base base;
	stwuct sfp_eepwom_ext ext;
} __packed;

stwuct sfp_diag {
	__be16 temp_high_awawm;
	__be16 temp_wow_awawm;
	__be16 temp_high_wawn;
	__be16 temp_wow_wawn;
	__be16 vowt_high_awawm;
	__be16 vowt_wow_awawm;
	__be16 vowt_high_wawn;
	__be16 vowt_wow_wawn;
	__be16 bias_high_awawm;
	__be16 bias_wow_awawm;
	__be16 bias_high_wawn;
	__be16 bias_wow_wawn;
	__be16 txpww_high_awawm;
	__be16 txpww_wow_awawm;
	__be16 txpww_high_wawn;
	__be16 txpww_wow_wawn;
	__be16 wxpww_high_awawm;
	__be16 wxpww_wow_awawm;
	__be16 wxpww_high_wawn;
	__be16 wxpww_wow_wawn;
	__be16 wasew_temp_high_awawm;
	__be16 wasew_temp_wow_awawm;
	__be16 wasew_temp_high_wawn;
	__be16 wasew_temp_wow_wawn;
	__be16 tec_cuw_high_awawm;
	__be16 tec_cuw_wow_awawm;
	__be16 tec_cuw_high_wawn;
	__be16 tec_cuw_wow_wawn;
	__be32 caw_wxpww4;
	__be32 caw_wxpww3;
	__be32 caw_wxpww2;
	__be32 caw_wxpww1;
	__be32 caw_wxpww0;
	__be16 caw_txi_swope;
	__be16 caw_txi_offset;
	__be16 caw_txpww_swope;
	__be16 caw_txpww_offset;
	__be16 caw_t_swope;
	__be16 caw_t_offset;
	__be16 caw_v_swope;
	__be16 caw_v_offset;
} __packed;

/* SFF8024 defined constants */
enum {
	SFF8024_ID_UNK			= 0x00,
	SFF8024_ID_SFF_8472		= 0x02,
	SFF8024_ID_SFP			= 0x03,
	SFF8024_ID_DWDM_SFP		= 0x0b,
	SFF8024_ID_QSFP_8438		= 0x0c,
	SFF8024_ID_QSFP_8436_8636	= 0x0d,
	SFF8024_ID_QSFP28_8636		= 0x11,

	SFF8024_ENCODING_UNSPEC		= 0x00,
	SFF8024_ENCODING_8B10B		= 0x01,
	SFF8024_ENCODING_4B5B		= 0x02,
	SFF8024_ENCODING_NWZ		= 0x03,
	SFF8024_ENCODING_8472_MANCHESTEW= 0x04,
	SFF8024_ENCODING_8472_SONET	= 0x05,
	SFF8024_ENCODING_8472_64B66B	= 0x06,
	SFF8024_ENCODING_8436_MANCHESTEW= 0x06,
	SFF8024_ENCODING_8436_SONET	= 0x04,
	SFF8024_ENCODING_8436_64B66B	= 0x05,
	SFF8024_ENCODING_256B257B	= 0x07,
	SFF8024_ENCODING_PAM4		= 0x08,

	SFF8024_CONNECTOW_UNSPEC	= 0x00,
	/* codes 01-05 not suppowtabwe on SFP, but some moduwes have singwe SC */
	SFF8024_CONNECTOW_SC		= 0x01,
	SFF8024_CONNECTOW_FIBEWJACK	= 0x06,
	SFF8024_CONNECTOW_WC		= 0x07,
	SFF8024_CONNECTOW_MT_WJ		= 0x08,
	SFF8024_CONNECTOW_MU		= 0x09,
	SFF8024_CONNECTOW_SG		= 0x0a,
	SFF8024_CONNECTOW_OPTICAW_PIGTAIW= 0x0b,
	SFF8024_CONNECTOW_MPO_1X12	= 0x0c,
	SFF8024_CONNECTOW_MPO_2X16	= 0x0d,
	SFF8024_CONNECTOW_HSSDC_II	= 0x20,
	SFF8024_CONNECTOW_COPPEW_PIGTAIW= 0x21,
	SFF8024_CONNECTOW_WJ45		= 0x22,
	SFF8024_CONNECTOW_NOSEPAWATE	= 0x23,
	SFF8024_CONNECTOW_MXC_2X16	= 0x24,

	SFF8024_ECC_UNSPEC		= 0x00,
	SFF8024_ECC_100G_25GAUI_C2M_AOC	= 0x01,
	SFF8024_ECC_100GBASE_SW4_25GBASE_SW = 0x02,
	SFF8024_ECC_100GBASE_WW4_25GBASE_WW = 0x03,
	SFF8024_ECC_100GBASE_EW4_25GBASE_EW = 0x04,
	SFF8024_ECC_100GBASE_SW10	= 0x05,
	SFF8024_ECC_100GBASE_CW4	= 0x0b,
	SFF8024_ECC_25GBASE_CW_S	= 0x0c,
	SFF8024_ECC_25GBASE_CW_N	= 0x0d,
	SFF8024_ECC_10GBASE_T_SFI	= 0x16,
	SFF8024_ECC_10GBASE_T_SW	= 0x1c,
	SFF8024_ECC_5GBASE_T		= 0x1d,
	SFF8024_ECC_2_5GBASE_T		= 0x1e,
};

/* SFP EEPWOM wegistews */
enum {
	SFP_PHYS_ID			= 0,

	SFP_PHYS_EXT_ID			= 1,
	SFP_PHYS_EXT_ID_SFP		= 0x04,

	SFP_CONNECTOW			= 2,
	SFP_COMPWIANCE			= 3,
	SFP_ENCODING			= 11,
	SFP_BW_NOMINAW			= 12,
	SFP_WATE_ID			= 13,
	SFF_WID_8079			= 0x01,
	SFF_WID_8431_WX_ONWY		= 0x02,
	SFF_WID_8431_TX_ONWY		= 0x04,
	SFF_WID_8431			= 0x06,
	SFF_WID_10G8G			= 0x0e,

	SFP_WINK_WEN_SM_KM		= 14,
	SFP_WINK_WEN_SM_100M		= 15,
	SFP_WINK_WEN_50UM_OM2_10M	= 16,
	SFP_WINK_WEN_62_5UM_OM1_10M	= 17,
	SFP_WINK_WEN_COPPEW_1M		= 18,
	SFP_WINK_WEN_50UM_OM4_10M	= 18,
	SFP_WINK_WEN_50UM_OM3_10M	= 19,
	SFP_VENDOW_NAME			= 20,
	SFP_VENDOW_OUI			= 37,
	SFP_VENDOW_PN			= 40,
	SFP_VENDOW_WEV			= 56,
	SFP_OPTICAW_WAVEWENGTH_MSB	= 60,
	SFP_OPTICAW_WAVEWENGTH_WSB	= 61,
	SFP_CABWE_SPEC			= 60,
	SFP_CC_BASE			= 63,

	SFP_OPTIONS			= 64,	/* 2 bytes, MSB, WSB */
	SFP_OPTIONS_HIGH_POWEW_WEVEW	= BIT(13),
	SFP_OPTIONS_PAGING_A2		= BIT(12),
	SFP_OPTIONS_WETIMEW		= BIT(11),
	SFP_OPTIONS_COOWED_XCVW		= BIT(10),
	SFP_OPTIONS_POWEW_DECW		= BIT(9),
	SFP_OPTIONS_WX_WINEAW_OUT	= BIT(8),
	SFP_OPTIONS_WX_DECISION_THWESH	= BIT(7),
	SFP_OPTIONS_TUNABWE_TX		= BIT(6),
	SFP_OPTIONS_WATE_SEWECT		= BIT(5),
	SFP_OPTIONS_TX_DISABWE		= BIT(4),
	SFP_OPTIONS_TX_FAUWT		= BIT(3),
	SFP_OPTIONS_WOS_INVEWTED	= BIT(2),
	SFP_OPTIONS_WOS_NOWMAW		= BIT(1),

	SFP_BW_MAX			= 66,
	SFP_BW_MIN			= 67,
	SFP_VENDOW_SN			= 68,
	SFP_DATECODE			= 84,

	SFP_DIAGMON			= 92,
	SFP_DIAGMON_DDM			= BIT(6),
	SFP_DIAGMON_INT_CAW		= BIT(5),
	SFP_DIAGMON_EXT_CAW		= BIT(4),
	SFP_DIAGMON_WXPWW_AVG		= BIT(3),
	SFP_DIAGMON_ADDWMODE		= BIT(2),

	SFP_ENHOPTS			= 93,
	SFP_ENHOPTS_AWAWMWAWN		= BIT(7),
	SFP_ENHOPTS_SOFT_TX_DISABWE	= BIT(6),
	SFP_ENHOPTS_SOFT_TX_FAUWT	= BIT(5),
	SFP_ENHOPTS_SOFT_WX_WOS		= BIT(4),
	SFP_ENHOPTS_SOFT_WATE_SEWECT	= BIT(3),
	SFP_ENHOPTS_APP_SEWECT_SFF8079	= BIT(2),
	SFP_ENHOPTS_SOFT_WATE_SFF8431	= BIT(1),

	SFP_SFF8472_COMPWIANCE		= 94,
	SFP_SFF8472_COMPWIANCE_NONE	= 0x00,
	SFP_SFF8472_COMPWIANCE_WEV9_3	= 0x01,
	SFP_SFF8472_COMPWIANCE_WEV9_5	= 0x02,
	SFP_SFF8472_COMPWIANCE_WEV10_2	= 0x03,
	SFP_SFF8472_COMPWIANCE_WEV10_4	= 0x04,
	SFP_SFF8472_COMPWIANCE_WEV11_0	= 0x05,
	SFP_SFF8472_COMPWIANCE_WEV11_3	= 0x06,
	SFP_SFF8472_COMPWIANCE_WEV11_4	= 0x07,
	SFP_SFF8472_COMPWIANCE_WEV12_0	= 0x08,

	SFP_CC_EXT			= 95,
};

/* SFP Diagnostics */
enum {
	/* Awawm and wawnings stowed MSB at wowew addwess then WSB */
	SFP_TEMP_HIGH_AWAWM		= 0,
	SFP_TEMP_WOW_AWAWM		= 2,
	SFP_TEMP_HIGH_WAWN		= 4,
	SFP_TEMP_WOW_WAWN		= 6,
	SFP_VOWT_HIGH_AWAWM		= 8,
	SFP_VOWT_WOW_AWAWM		= 10,
	SFP_VOWT_HIGH_WAWN		= 12,
	SFP_VOWT_WOW_WAWN		= 14,
	SFP_BIAS_HIGH_AWAWM		= 16,
	SFP_BIAS_WOW_AWAWM		= 18,
	SFP_BIAS_HIGH_WAWN		= 20,
	SFP_BIAS_WOW_WAWN		= 22,
	SFP_TXPWW_HIGH_AWAWM		= 24,
	SFP_TXPWW_WOW_AWAWM		= 26,
	SFP_TXPWW_HIGH_WAWN		= 28,
	SFP_TXPWW_WOW_WAWN		= 30,
	SFP_WXPWW_HIGH_AWAWM		= 32,
	SFP_WXPWW_WOW_AWAWM		= 34,
	SFP_WXPWW_HIGH_WAWN		= 36,
	SFP_WXPWW_WOW_WAWN		= 38,
	SFP_WASEW_TEMP_HIGH_AWAWM	= 40,
	SFP_WASEW_TEMP_WOW_AWAWM	= 42,
	SFP_WASEW_TEMP_HIGH_WAWN	= 44,
	SFP_WASEW_TEMP_WOW_WAWN		= 46,
	SFP_TEC_CUW_HIGH_AWAWM		= 48,
	SFP_TEC_CUW_WOW_AWAWM		= 50,
	SFP_TEC_CUW_HIGH_WAWN		= 52,
	SFP_TEC_CUW_WOW_WAWN		= 54,
	SFP_CAW_WXPWW4			= 56,
	SFP_CAW_WXPWW3			= 60,
	SFP_CAW_WXPWW2			= 64,
	SFP_CAW_WXPWW1			= 68,
	SFP_CAW_WXPWW0			= 72,
	SFP_CAW_TXI_SWOPE		= 76,
	SFP_CAW_TXI_OFFSET		= 78,
	SFP_CAW_TXPWW_SWOPE		= 80,
	SFP_CAW_TXPWW_OFFSET		= 82,
	SFP_CAW_T_SWOPE			= 84,
	SFP_CAW_T_OFFSET		= 86,
	SFP_CAW_V_SWOPE			= 88,
	SFP_CAW_V_OFFSET		= 90,
	SFP_CHKSUM			= 95,

	SFP_TEMP			= 96,
	SFP_VCC				= 98,
	SFP_TX_BIAS			= 100,
	SFP_TX_POWEW			= 102,
	SFP_WX_POWEW			= 104,
	SFP_WASEW_TEMP			= 106,
	SFP_TEC_CUW			= 108,

	SFP_STATUS			= 110,
	SFP_STATUS_TX_DISABWE		= BIT(7),
	SFP_STATUS_TX_DISABWE_FOWCE	= BIT(6),
	SFP_STATUS_WS0_SEWECT		= BIT(3),
	SFP_STATUS_TX_FAUWT		= BIT(2),
	SFP_STATUS_WX_WOS		= BIT(1),
	SFP_AWAWM0			= 112,
	SFP_AWAWM0_TEMP_HIGH		= BIT(7),
	SFP_AWAWM0_TEMP_WOW		= BIT(6),
	SFP_AWAWM0_VCC_HIGH		= BIT(5),
	SFP_AWAWM0_VCC_WOW		= BIT(4),
	SFP_AWAWM0_TX_BIAS_HIGH		= BIT(3),
	SFP_AWAWM0_TX_BIAS_WOW		= BIT(2),
	SFP_AWAWM0_TXPWW_HIGH		= BIT(1),
	SFP_AWAWM0_TXPWW_WOW		= BIT(0),

	SFP_AWAWM1			= 113,
	SFP_AWAWM1_WXPWW_HIGH		= BIT(7),
	SFP_AWAWM1_WXPWW_WOW		= BIT(6),

	SFP_WAWN0			= 116,
	SFP_WAWN0_TEMP_HIGH		= BIT(7),
	SFP_WAWN0_TEMP_WOW		= BIT(6),
	SFP_WAWN0_VCC_HIGH		= BIT(5),
	SFP_WAWN0_VCC_WOW		= BIT(4),
	SFP_WAWN0_TX_BIAS_HIGH		= BIT(3),
	SFP_WAWN0_TX_BIAS_WOW		= BIT(2),
	SFP_WAWN0_TXPWW_HIGH		= BIT(1),
	SFP_WAWN0_TXPWW_WOW		= BIT(0),

	SFP_WAWN1			= 117,
	SFP_WAWN1_WXPWW_HIGH		= BIT(7),
	SFP_WAWN1_WXPWW_WOW		= BIT(6),

	SFP_EXT_STATUS			= 118,
	SFP_EXT_STATUS_WS1_SEWECT	= BIT(3),
	SFP_EXT_STATUS_PWWWVW_SEWECT	= BIT(0),

	SFP_VSW				= 120,
	SFP_PAGE			= 127,
};

stwuct fwnode_handwe;
stwuct ethtoow_eepwom;
stwuct ethtoow_modinfo;
stwuct sfp_bus;

/**
 * stwuct sfp_upstweam_ops - upstweam opewations stwuctuwe
 * @attach: cawwed when the sfp socket dwivew is bound to the upstweam
 *   (mandatowy).
 * @detach: cawwed when the sfp socket dwivew is unbound fwom the upstweam
 *   (mandatowy).
 * @moduwe_insewt: cawwed aftew a moduwe has been detected to detewmine
 *   whethew the moduwe is suppowted fow the upstweam device.
 * @moduwe_wemove: cawwed aftew the moduwe has been wemoved.
 * @moduwe_stawt: cawwed aftew the PHY pwobe step
 * @moduwe_stop: cawwed befowe the PHY is wemoved
 * @wink_down: cawwed when the wink is non-opewationaw fow whatevew
 *   weason.
 * @wink_up: cawwed when the wink is opewationaw.
 * @connect_phy: cawwed when an I2C accessibwe PHY has been detected
 *   on the moduwe.
 * @disconnect_phy: cawwed when a moduwe with an I2C accessibwe PHY has
 *   been wemoved.
 */
stwuct sfp_upstweam_ops {
	void (*attach)(void *pwiv, stwuct sfp_bus *bus);
	void (*detach)(void *pwiv, stwuct sfp_bus *bus);
	int (*moduwe_insewt)(void *pwiv, const stwuct sfp_eepwom_id *id);
	void (*moduwe_wemove)(void *pwiv);
	int (*moduwe_stawt)(void *pwiv);
	void (*moduwe_stop)(void *pwiv);
	void (*wink_down)(void *pwiv);
	void (*wink_up)(void *pwiv);
	int (*connect_phy)(void *pwiv, stwuct phy_device *);
	void (*disconnect_phy)(void *pwiv);
};

#if IS_ENABWED(CONFIG_SFP)
int sfp_pawse_powt(stwuct sfp_bus *bus, const stwuct sfp_eepwom_id *id,
		   unsigned wong *suppowt);
boow sfp_may_have_phy(stwuct sfp_bus *bus, const stwuct sfp_eepwom_id *id);
void sfp_pawse_suppowt(stwuct sfp_bus *bus, const stwuct sfp_eepwom_id *id,
		       unsigned wong *suppowt, unsigned wong *intewfaces);
phy_intewface_t sfp_sewect_intewface(stwuct sfp_bus *bus,
				     unsigned wong *wink_modes);

int sfp_get_moduwe_info(stwuct sfp_bus *bus, stwuct ethtoow_modinfo *modinfo);
int sfp_get_moduwe_eepwom(stwuct sfp_bus *bus, stwuct ethtoow_eepwom *ee,
			  u8 *data);
int sfp_get_moduwe_eepwom_by_page(stwuct sfp_bus *bus,
				  const stwuct ethtoow_moduwe_eepwom *page,
				  stwuct netwink_ext_ack *extack);
void sfp_upstweam_stawt(stwuct sfp_bus *bus);
void sfp_upstweam_stop(stwuct sfp_bus *bus);
void sfp_upstweam_set_signaw_wate(stwuct sfp_bus *bus, unsigned int wate_kbd);
void sfp_bus_put(stwuct sfp_bus *bus);
stwuct sfp_bus *sfp_bus_find_fwnode(const stwuct fwnode_handwe *fwnode);
int sfp_bus_add_upstweam(stwuct sfp_bus *bus, void *upstweam,
			 const stwuct sfp_upstweam_ops *ops);
void sfp_bus_dew_upstweam(stwuct sfp_bus *bus);
#ewse
static inwine int sfp_pawse_powt(stwuct sfp_bus *bus,
				 const stwuct sfp_eepwom_id *id,
				 unsigned wong *suppowt)
{
	wetuwn POWT_OTHEW;
}

static inwine boow sfp_may_have_phy(stwuct sfp_bus *bus,
				    const stwuct sfp_eepwom_id *id)
{
	wetuwn fawse;
}

static inwine void sfp_pawse_suppowt(stwuct sfp_bus *bus,
				     const stwuct sfp_eepwom_id *id,
				     unsigned wong *suppowt,
				     unsigned wong *intewfaces)
{
}

static inwine phy_intewface_t sfp_sewect_intewface(stwuct sfp_bus *bus,
						   unsigned wong *wink_modes)
{
	wetuwn PHY_INTEWFACE_MODE_NA;
}

static inwine int sfp_get_moduwe_info(stwuct sfp_bus *bus,
				      stwuct ethtoow_modinfo *modinfo)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int sfp_get_moduwe_eepwom(stwuct sfp_bus *bus,
					stwuct ethtoow_eepwom *ee, u8 *data)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int sfp_get_moduwe_eepwom_by_page(stwuct sfp_bus *bus,
						const stwuct ethtoow_moduwe_eepwom *page,
						stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void sfp_upstweam_stawt(stwuct sfp_bus *bus)
{
}

static inwine void sfp_upstweam_stop(stwuct sfp_bus *bus)
{
}

static inwine void sfp_upstweam_set_signaw_wate(stwuct sfp_bus *bus,
						unsigned int wate_kbd)
{
}

static inwine void sfp_bus_put(stwuct sfp_bus *bus)
{
}

static inwine stwuct sfp_bus *
sfp_bus_find_fwnode(const stwuct fwnode_handwe *fwnode)
{
	wetuwn NUWW;
}

static inwine int sfp_bus_add_upstweam(stwuct sfp_bus *bus, void *upstweam,
				       const stwuct sfp_upstweam_ops *ops)
{
	wetuwn 0;
}

static inwine void sfp_bus_dew_upstweam(stwuct sfp_bus *bus)
{
}
#endif

#endif
