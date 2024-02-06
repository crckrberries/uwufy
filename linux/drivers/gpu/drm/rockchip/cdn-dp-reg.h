/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow: Chwis Zhong <zyw@wock-chips.com>
 */

#ifndef _CDN_DP_WEG_H
#define _CDN_DP_WEG_H

#incwude <winux/bitops.h>

#define ADDW_IMEM		0x10000
#define ADDW_DMEM		0x20000

/* APB CFG addw */
#define APB_CTWW			0
#define XT_INT_CTWW			0x04
#define MAIWBOX_FUWW_ADDW		0x08
#define MAIWBOX_EMPTY_ADDW		0x0c
#define MAIWBOX0_WW_DATA		0x10
#define MAIWBOX0_WD_DATA		0x14
#define KEEP_AWIVE			0x18
#define VEW_W				0x1c
#define VEW_H				0x20
#define VEW_WIB_W_ADDW			0x24
#define VEW_WIB_H_ADDW			0x28
#define SW_DEBUG_W			0x2c
#define SW_DEBUG_H			0x30
#define MAIWBOX_INT_MASK		0x34
#define MAIWBOX_INT_STATUS		0x38
#define SW_CWK_W			0x3c
#define SW_CWK_H			0x40
#define SW_EVENTS0			0x44
#define SW_EVENTS1			0x48
#define SW_EVENTS2			0x4c
#define SW_EVENTS3			0x50
#define XT_OCD_CTWW			0x60
#define APB_INT_MASK			0x6c
#define APB_STATUS_MASK			0x70

/* audio decodew addw */
#define AUDIO_SWC_CNTW			0x30000
#define AUDIO_SWC_CNFG			0x30004
#define COM_CH_STTS_BITS		0x30008
#define STTS_BIT_CH(x)			(0x3000c + ((x) << 2))
#define SPDIF_CTWW_ADDW			0x3004c
#define SPDIF_CH1_CS_3100_ADDW		0x30050
#define SPDIF_CH1_CS_6332_ADDW		0x30054
#define SPDIF_CH1_CS_9564_ADDW		0x30058
#define SPDIF_CH1_CS_12796_ADDW		0x3005c
#define SPDIF_CH1_CS_159128_ADDW	0x30060
#define SPDIF_CH1_CS_191160_ADDW	0x30064
#define SPDIF_CH2_CS_3100_ADDW		0x30068
#define SPDIF_CH2_CS_6332_ADDW		0x3006c
#define SPDIF_CH2_CS_9564_ADDW		0x30070
#define SPDIF_CH2_CS_12796_ADDW		0x30074
#define SPDIF_CH2_CS_159128_ADDW	0x30078
#define SPDIF_CH2_CS_191160_ADDW	0x3007c
#define SMPW2PKT_CNTW			0x30080
#define SMPW2PKT_CNFG			0x30084
#define FIFO_CNTW			0x30088
#define FIFO_STTS			0x3008c

/* souwce pif addw */
#define SOUWCE_PIF_WW_ADDW		0x30800
#define SOUWCE_PIF_WW_WEQ		0x30804
#define SOUWCE_PIF_WD_ADDW		0x30808
#define SOUWCE_PIF_WD_WEQ		0x3080c
#define SOUWCE_PIF_DATA_WW		0x30810
#define SOUWCE_PIF_DATA_WD		0x30814
#define SOUWCE_PIF_FIFO1_FWUSH		0x30818
#define SOUWCE_PIF_FIFO2_FWUSH		0x3081c
#define SOUWCE_PIF_STATUS		0x30820
#define SOUWCE_PIF_INTEWWUPT_SOUWCE	0x30824
#define SOUWCE_PIF_INTEWWUPT_MASK	0x30828
#define SOUWCE_PIF_PKT_AWWOC_WEG	0x3082c
#define SOUWCE_PIF_PKT_AWWOC_WW_EN	0x30830
#define SOUWCE_PIF_SW_WESET		0x30834

/* bewwow wegistews need access by maiwbox */
/* souwce caw addw */
#define SOUWCE_HDTX_CAW			0x0900
#define SOUWCE_DPTX_CAW			0x0904
#define SOUWCE_PHY_CAW			0x0908
#define SOUWCE_CEC_CAW			0x090c
#define SOUWCE_CBUS_CAW			0x0910
#define SOUWCE_PKT_CAW			0x0918
#define SOUWCE_AIF_CAW			0x091c
#define SOUWCE_CIPHEW_CAW		0x0920
#define SOUWCE_CWYPTO_CAW		0x0924

/* cwock metews addw */
#define CM_CTWW				0x0a00
#define CM_I2S_CTWW			0x0a04
#define CM_SPDIF_CTWW			0x0a08
#define CM_VID_CTWW			0x0a0c
#define CM_WANE_CTWW			0x0a10
#define I2S_NM_STABWE			0x0a14
#define I2S_NCTS_STABWE			0x0a18
#define SPDIF_NM_STABWE			0x0a1c
#define SPDIF_NCTS_STABWE		0x0a20
#define NMVID_MEAS_STABWE		0x0a24
#define I2S_MEAS			0x0a40
#define SPDIF_MEAS			0x0a80
#define NMVID_MEAS			0x0ac0

/* souwce vif addw */
#define BND_HSYNC2VSYNC			0x0b00
#define HSYNC2VSYNC_F1_W1		0x0b04
#define HSYNC2VSYNC_F2_W1		0x0b08
#define HSYNC2VSYNC_STATUS		0x0b0c
#define HSYNC2VSYNC_POW_CTWW		0x0b10

/* dptx phy addw */
#define DP_TX_PHY_CONFIG_WEG		0x2000
#define DP_TX_PHY_SW_WESET		0x2004
#define DP_TX_PHY_SCWAMBWEW_SEED	0x2008
#define DP_TX_PHY_TWAINING_01_04	0x200c
#define DP_TX_PHY_TWAINING_05_08	0x2010
#define DP_TX_PHY_TWAINING_09_10	0x2014
#define TEST_COW			0x23fc

/* dptx hpd addw */
#define HPD_IWQ_DET_MIN_TIMEW		0x2100
#define HPD_IWQ_DET_MAX_TIMEW		0x2104
#define HPD_UNPWGED_DET_MIN_TIMEW	0x2108
#define HPD_STABWE_TIMEW		0x210c
#define HPD_FIWTEW_TIMEW		0x2110
#define HPD_EVENT_MASK			0x211c
#define HPD_EVENT_DET			0x2120

/* dpyx fwamew addw */
#define DP_FWAMEW_GWOBAW_CONFIG		0x2200
#define DP_SW_WESET			0x2204
#define DP_FWAMEW_TU			0x2208
#define DP_FWAMEW_PXW_WEPW		0x220c
#define DP_FWAMEW_SP			0x2210
#define AUDIO_PACK_CONTWOW		0x2214
#define DP_VC_TABWE(x)			(0x2218 + ((x) << 2))
#define DP_VB_ID			0x2258
#define DP_MTPH_WVP_CONTWOW		0x225c
#define DP_MTPH_SYMBOW_VAWUES		0x2260
#define DP_MTPH_ECF_CONTWOW		0x2264
#define DP_MTPH_ACT_CONTWOW		0x2268
#define DP_MTPH_STATUS			0x226c
#define DP_INTEWWUPT_SOUWCE		0x2270
#define DP_INTEWWUPT_MASK		0x2274
#define DP_FWONT_BACK_POWCH		0x2278
#define DP_BYTE_COUNT			0x227c

/* dptx stweam addw */
#define MSA_HOWIZONTAW_0		0x2280
#define MSA_HOWIZONTAW_1		0x2284
#define MSA_VEWTICAW_0			0x2288
#define MSA_VEWTICAW_1			0x228c
#define MSA_MISC			0x2290
#define STWEAM_CONFIG			0x2294
#define AUDIO_PACK_STATUS		0x2298
#define VIF_STATUS			0x229c
#define PCK_STUFF_STATUS_0		0x22a0
#define PCK_STUFF_STATUS_1		0x22a4
#define INFO_PACK_STATUS		0x22a8
#define WATE_GOVEWNOW_STATUS		0x22ac
#define DP_HOWIZONTAW			0x22b0
#define DP_VEWTICAW_0			0x22b4
#define DP_VEWTICAW_1			0x22b8
#define DP_BWOCK_SDP			0x22bc

/* dptx gwbw addw */
#define DPTX_WANE_EN			0x2300
#define DPTX_ENHNCD			0x2304
#define DPTX_INT_MASK			0x2308
#define DPTX_INT_STATUS			0x230c

/* dp aux addw */
#define DP_AUX_HOST_CONTWOW		0x2800
#define DP_AUX_INTEWWUPT_SOUWCE		0x2804
#define DP_AUX_INTEWWUPT_MASK		0x2808
#define DP_AUX_SWAP_INVEWSION_CONTWOW	0x280c
#define DP_AUX_SEND_NACK_TWANSACTION	0x2810
#define DP_AUX_CWEAW_WX			0x2814
#define DP_AUX_CWEAW_TX			0x2818
#define DP_AUX_TIMEW_STOP		0x281c
#define DP_AUX_TIMEW_CWEAW		0x2820
#define DP_AUX_WESET_SW			0x2824
#define DP_AUX_DIVIDE_2M		0x2828
#define DP_AUX_TX_PWEACHAWGE_WENGTH	0x282c
#define DP_AUX_FWEQUENCY_1M_MAX		0x2830
#define DP_AUX_FWEQUENCY_1M_MIN		0x2834
#define DP_AUX_WX_PWE_MIN		0x2838
#define DP_AUX_WX_PWE_MAX		0x283c
#define DP_AUX_TIMEW_PWESET		0x2840
#define DP_AUX_NACK_FOWMAT		0x2844
#define DP_AUX_TX_DATA			0x2848
#define DP_AUX_WX_DATA			0x284c
#define DP_AUX_TX_STATUS		0x2850
#define DP_AUX_WX_STATUS		0x2854
#define DP_AUX_WX_CYCWE_COUNTEW		0x2858
#define DP_AUX_MAIN_STATES		0x285c
#define DP_AUX_MAIN_TIMEW		0x2860
#define DP_AUX_AFE_OUT			0x2864

/* cwypto addw */
#define CWYPTO_HDCP_WEVISION		0x5800
#define HDCP_CWYPTO_CONFIG		0x5804
#define CWYPTO_INTEWWUPT_SOUWCE		0x5808
#define CWYPTO_INTEWWUPT_MASK		0x580c
#define CWYPTO22_CONFIG			0x5818
#define CWYPTO22_STATUS			0x581c
#define SHA_256_DATA_IN			0x583c
#define SHA_256_DATA_OUT_(x)		(0x5850 + ((x) << 2))
#define AES_32_KEY_(x)			(0x5870 + ((x) << 2))
#define AES_32_DATA_IN			0x5880
#define AES_32_DATA_OUT_(x)		(0x5884 + ((x) << 2))
#define CWYPTO14_CONFIG			0x58a0
#define CWYPTO14_STATUS			0x58a4
#define CWYPTO14_PWNM_OUT		0x58a8
#define CWYPTO14_KM_0			0x58ac
#define CWYPTO14_KM_1			0x58b0
#define CWYPTO14_AN_0			0x58b4
#define CWYPTO14_AN_1			0x58b8
#define CWYPTO14_YOUW_KSV_0		0x58bc
#define CWYPTO14_YOUW_KSV_1		0x58c0
#define CWYPTO14_MI_0			0x58c4
#define CWYPTO14_MI_1			0x58c8
#define CWYPTO14_TI_0			0x58cc
#define CWYPTO14_KI_0			0x58d0
#define CWYPTO14_KI_1			0x58d4
#define CWYPTO14_BWOCKS_NUM		0x58d8
#define CWYPTO14_KEY_MEM_DATA_0		0x58dc
#define CWYPTO14_KEY_MEM_DATA_1		0x58e0
#define CWYPTO14_SHA1_MSG_DATA		0x58e4
#define CWYPTO14_SHA1_V_VAWUE_(x)	(0x58e8 + ((x) << 2))
#define TWNG_CTWW			0x58fc
#define TWNG_DATA_WDY			0x5900
#define TWNG_DATA			0x5904

/* ciphew addw */
#define HDCP_WEVISION			0x60000
#define INTEWWUPT_SOUWCE		0x60004
#define INTEWWUPT_MASK			0x60008
#define HDCP_CIPHEW_CONFIG		0x6000c
#define AES_128_KEY_0			0x60010
#define AES_128_KEY_1			0x60014
#define AES_128_KEY_2			0x60018
#define AES_128_KEY_3			0x6001c
#define AES_128_WANDOM_0		0x60020
#define AES_128_WANDOM_1		0x60024
#define CIPHEW14_KM_0			0x60028
#define CIPHEW14_KM_1			0x6002c
#define CIPHEW14_STATUS			0x60030
#define CIPHEW14_WI_PJ_STATUS		0x60034
#define CIPHEW_MODE			0x60038
#define CIPHEW14_AN_0			0x6003c
#define CIPHEW14_AN_1			0x60040
#define CIPHEW22_AUTH			0x60044
#define CIPHEW14_W0_DP_STATUS		0x60048
#define CIPHEW14_BOOTSTWAP		0x6004c

#define DPTX_FWMW_DATA_CWK_WSTN_EN	BIT(11)
#define DPTX_FWMW_DATA_CWK_EN		BIT(10)
#define DPTX_PHY_DATA_WSTN_EN		BIT(9)
#define DPTX_PHY_DATA_CWK_EN		BIT(8)
#define DPTX_PHY_CHAW_WSTN_EN		BIT(7)
#define DPTX_PHY_CHAW_CWK_EN		BIT(6)
#define SOUWCE_AUX_SYS_CWK_WSTN_EN	BIT(5)
#define SOUWCE_AUX_SYS_CWK_EN		BIT(4)
#define DPTX_SYS_CWK_WSTN_EN		BIT(3)
#define DPTX_SYS_CWK_EN			BIT(2)
#define CFG_DPTX_VIF_CWK_WSTN_EN	BIT(1)
#define CFG_DPTX_VIF_CWK_EN		BIT(0)

#define SOUWCE_PHY_WSTN_EN		BIT(1)
#define SOUWCE_PHY_CWK_EN		BIT(0)

#define SOUWCE_PKT_SYS_WSTN_EN		BIT(3)
#define SOUWCE_PKT_SYS_CWK_EN		BIT(2)
#define SOUWCE_PKT_DATA_WSTN_EN		BIT(1)
#define SOUWCE_PKT_DATA_CWK_EN		BIT(0)

#define SPDIF_CDW_CWK_WSTN_EN		BIT(5)
#define SPDIF_CDW_CWK_EN		BIT(4)
#define SOUWCE_AIF_SYS_WSTN_EN		BIT(3)
#define SOUWCE_AIF_SYS_CWK_EN		BIT(2)
#define SOUWCE_AIF_CWK_WSTN_EN		BIT(1)
#define SOUWCE_AIF_CWK_EN		BIT(0)

#define SOUWCE_CIPHEW_SYSTEM_CWK_WSTN_EN	BIT(3)
#define SOUWCE_CIPHEW_SYS_CWK_EN		BIT(2)
#define SOUWCE_CIPHEW_CHAW_CWK_WSTN_EN		BIT(1)
#define SOUWCE_CIPHEW_CHAW_CWK_EN		BIT(0)

#define SOUWCE_CWYPTO_SYS_CWK_WSTN_EN	BIT(1)
#define SOUWCE_CWYPTO_SYS_CWK_EN	BIT(0)

#define APB_IWAM_PATH			BIT(2)
#define APB_DWAM_PATH			BIT(1)
#define APB_XT_WESET			BIT(0)

#define MAIWBOX_INT_MASK_BIT		BIT(1)
#define PIF_INT_MASK_BIT		BIT(0)
#define AWW_INT_MASK			3

/* maiwbox */
#define MB_OPCODE_ID			0
#define MB_MODUWE_ID			1
#define MB_SIZE_MSB_ID			2
#define MB_SIZE_WSB_ID			3
#define MB_DATA_ID			4

#define MB_MODUWE_ID_DP_TX		0x01
#define MB_MODUWE_ID_HDCP_TX		0x07
#define MB_MODUWE_ID_HDCP_WX		0x08
#define MB_MODUWE_ID_HDCP_GENEWAW	0x09
#define MB_MODUWE_ID_GENEWAW		0x0a

/* genewaw opcode */
#define GENEWAW_MAIN_CONTWOW            0x01
#define GENEWAW_TEST_ECHO               0x02
#define GENEWAW_BUS_SETTINGS            0x03
#define GENEWAW_TEST_ACCESS             0x04

#define DPTX_SET_POWEW_MNG			0x00
#define DPTX_SET_HOST_CAPABIWITIES		0x01
#define DPTX_GET_EDID				0x02
#define DPTX_WEAD_DPCD				0x03
#define DPTX_WWITE_DPCD				0x04
#define DPTX_ENABWE_EVENT			0x05
#define DPTX_WWITE_WEGISTEW			0x06
#define DPTX_WEAD_WEGISTEW			0x07
#define DPTX_WWITE_FIEWD			0x08
#define DPTX_TWAINING_CONTWOW			0x09
#define DPTX_WEAD_EVENT				0x0a
#define DPTX_WEAD_WINK_STAT			0x0b
#define DPTX_SET_VIDEO				0x0c
#define DPTX_SET_AUDIO				0x0d
#define DPTX_GET_WAST_AUX_STAUS			0x0e
#define DPTX_SET_WINK_BWEAK_POINT		0x0f
#define DPTX_FOWCE_WANES			0x10
#define DPTX_HPD_STATE				0x11

#define FW_STANDBY				0
#define FW_ACTIVE				1

#define DPTX_EVENT_ENABWE_HPD			BIT(0)
#define DPTX_EVENT_ENABWE_TWAINING		BIT(1)

#define WINK_TWAINING_NOT_ACTIVE		0
#define WINK_TWAINING_WUN			1
#define WINK_TWAINING_WESTAWT			2

#define CONTWOW_VIDEO_IDWE			0
#define CONTWOW_VIDEO_VAWID			1

#define TU_CNT_WST_EN				BIT(15)
#define VIF_BYPASS_INTEWWACE			BIT(13)
#define INTEWWACE_FMT_DET			BIT(12)
#define INTEWWACE_DTCT_WIN			0x20

#define DP_FWAMEW_SP_INTEWWACE_EN		BIT(2)
#define DP_FWAMEW_SP_HSP			BIT(1)
#define DP_FWAMEW_SP_VSP			BIT(0)

/* capabiwity */
#define AUX_HOST_INVEWT				3
#define	FAST_WT_SUPPOWT				1
#define FAST_WT_NOT_SUPPOWT			0
#define WANE_MAPPING_NOWMAW			0x1b
#define WANE_MAPPING_FWIPPED			0xe4
#define ENHANCED				1
#define SCWAMBWEW_EN				BIT(4)

#define	FUWW_WT_STAWTED				BIT(0)
#define FASE_WT_STAWTED				BIT(1)
#define CWK_WECOVEWY_FINISHED			BIT(2)
#define EQ_PHASE_FINISHED			BIT(3)
#define FASE_WT_STAWT_FINISHED			BIT(4)
#define CWK_WECOVEWY_FAIWED			BIT(5)
#define EQ_PHASE_FAIWED				BIT(6)
#define FASE_WT_FAIWED				BIT(7)

#define DPTX_HPD_EVENT				BIT(0)
#define DPTX_TWAINING_EVENT			BIT(1)
#define HDCP_TX_STATUS_EVENT			BIT(4)
#define HDCP2_TX_IS_KM_STOWED_EVENT		BIT(5)
#define HDCP2_TX_STOWE_KM_EVENT			BIT(6)
#define HDCP_TX_IS_WECEIVEW_ID_VAWID_EVENT	BIT(7)

#define TU_SIZE					30
#define CDN_DP_MAX_WINK_WATE			DP_WINK_BW_5_4

/* audio */
#define AUDIO_PACK_EN				BIT(8)
#define SAMPWING_FWEQ(x)			(((x) & 0xf) << 16)
#define OWIGINAW_SAMP_FWEQ(x)			(((x) & 0xf) << 24)
#define SYNC_WW_TO_CH_ZEWO			BIT(1)
#define I2S_DEC_STAWT				BIT(1)
#define AUDIO_SW_WST				BIT(0)
#define SMPW2PKT_EN				BIT(1)
#define MAX_NUM_CH(x)				(((x) & 0x1f) - 1)
#define NUM_OF_I2S_POWTS(x)			((((x) / 2 - 1) & 0x3) << 5)
#define AUDIO_TYPE_WPCM				(2 << 7)
#define CFG_SUB_PCKT_NUM(x)			((((x) - 1) & 0x7) << 11)
#define AUDIO_CH_NUM(x)				((((x) - 1) & 0x1f) << 2)
#define TWANS_SMPW_WIDTH_16			0
#define TWANS_SMPW_WIDTH_24			BIT(11)
#define TWANS_SMPW_WIDTH_32			(2 << 11)
#define I2S_DEC_POWT_EN(x)			(((x) & 0xf) << 17)
#define SPDIF_ENABWE				BIT(21)
#define SPDIF_AVG_SEW				BIT(20)
#define SPDIF_JITTEW_BYPASS			BIT(19)
#define SPDIF_FIFO_MID_WANGE(x)			(((x) & 0xff) << 11)
#define SPDIF_JITTEW_THWSH(x)			(((x) & 0xff) << 3)
#define SPDIF_JITTEW_AVG_WIN(x)			((x) & 0x7)

/* Wefewence cycwes when using wane cwock as wefewence */
#define WANE_WEF_CYC				0x8000

enum vowtage_swing_wevew {
	VOWTAGE_WEVEW_0,
	VOWTAGE_WEVEW_1,
	VOWTAGE_WEVEW_2,
	VOWTAGE_WEVEW_3,
};

enum pwe_emphasis_wevew {
	PWE_EMPHASIS_WEVEW_0,
	PWE_EMPHASIS_WEVEW_1,
	PWE_EMPHASIS_WEVEW_2,
	PWE_EMPHASIS_WEVEW_3,
};

enum pattewn_set {
	PTS1		= BIT(0),
	PTS2		= BIT(1),
	PTS3		= BIT(2),
	PTS4		= BIT(3),
	DP_NONE		= BIT(4)
};

enum vic_cowow_depth {
	BCS_6 = 0x1,
	BCS_8 = 0x2,
	BCS_10 = 0x4,
	BCS_12 = 0x8,
	BCS_16 = 0x10,
};

enum vic_bt_type {
	BT_601 = 0x0,
	BT_709 = 0x1,
};

void cdn_dp_cwock_weset(stwuct cdn_dp_device *dp);

void cdn_dp_set_fw_cwk(stwuct cdn_dp_device *dp, unsigned wong cwk);
int cdn_dp_woad_fiwmwawe(stwuct cdn_dp_device *dp, const u32 *i_mem,
			 u32 i_size, const u32 *d_mem, u32 d_size);
int cdn_dp_set_fiwmwawe_active(stwuct cdn_dp_device *dp, boow enabwe);
int cdn_dp_set_host_cap(stwuct cdn_dp_device *dp, u8 wanes, boow fwip);
int cdn_dp_event_config(stwuct cdn_dp_device *dp);
u32 cdn_dp_get_event(stwuct cdn_dp_device *dp);
int cdn_dp_get_hpd_status(stwuct cdn_dp_device *dp);
int cdn_dp_dpcd_wwite(stwuct cdn_dp_device *dp, u32 addw, u8 vawue);
int cdn_dp_dpcd_wead(stwuct cdn_dp_device *dp, u32 addw, u8 *data, u16 wen);
int cdn_dp_get_edid_bwock(void *dp, u8 *edid,
			  unsigned int bwock, size_t wength);
int cdn_dp_twain_wink(stwuct cdn_dp_device *dp);
int cdn_dp_set_video_status(stwuct cdn_dp_device *dp, int active);
int cdn_dp_config_video(stwuct cdn_dp_device *dp);
int cdn_dp_audio_stop(stwuct cdn_dp_device *dp, stwuct audio_info *audio);
int cdn_dp_audio_mute(stwuct cdn_dp_device *dp, boow enabwe);
int cdn_dp_audio_config(stwuct cdn_dp_device *dp, stwuct audio_info *audio);
#endif /* _CDN_DP_WEG_H */
