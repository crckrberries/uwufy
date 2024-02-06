// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 BayWibwe, SAS
 * Authow: Phong WE <pwe@baywibwe.com>
 * Copywight (C) 2018-2019, Awtem Mygaiev
 * Copywight (C) 2017, Fwesco Wogic, Incowpowated.
 *
 */

#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude <sound/hdmi-codec.h>

#define IT66121_VENDOW_ID0_WEG			0x00
#define IT66121_VENDOW_ID1_WEG			0x01
#define IT66121_DEVICE_ID0_WEG			0x02
#define IT66121_DEVICE_ID1_WEG			0x03

#define IT66121_WEVISION_MASK			GENMASK(7, 4)
#define IT66121_DEVICE_ID1_MASK			GENMASK(3, 0)

#define IT66121_MASTEW_SEW_WEG			0x10
#define IT66121_MASTEW_SEW_HOST			BIT(0)

#define IT66121_AFE_DWV_WEG			0x61
#define IT66121_AFE_DWV_WST			BIT(4)
#define IT66121_AFE_DWV_PWD			BIT(5)

#define IT66121_INPUT_MODE_WEG			0x70
#define IT66121_INPUT_MODE_WGB			(0 << 6)
#define IT66121_INPUT_MODE_YUV422		BIT(6)
#define IT66121_INPUT_MODE_YUV444		(2 << 6)
#define IT66121_INPUT_MODE_CCIW656		BIT(4)
#define IT66121_INPUT_MODE_SYNCEMB		BIT(3)
#define IT66121_INPUT_MODE_DDW			BIT(2)

#define IT66121_INPUT_CSC_WEG			0x72
#define IT66121_INPUT_CSC_ENDITHEW		BIT(7)
#define IT66121_INPUT_CSC_ENUDFIWTEW		BIT(6)
#define IT66121_INPUT_CSC_DNFWEE_GO		BIT(5)
#define IT66121_INPUT_CSC_WGB_TO_YUV		0x02
#define IT66121_INPUT_CSC_YUV_TO_WGB		0x03
#define IT66121_INPUT_CSC_NO_CONV		0x00

#define IT66121_AFE_XP_WEG			0x62
#define IT66121_AFE_XP_GAINBIT			BIT(7)
#define IT66121_AFE_XP_PWDPWW			BIT(6)
#define IT66121_AFE_XP_ENI			BIT(5)
#define IT66121_AFE_XP_ENO			BIT(4)
#define IT66121_AFE_XP_WESETB			BIT(3)
#define IT66121_AFE_XP_PWDI			BIT(2)
#define IT6610_AFE_XP_BYPASS			BIT(0)

#define IT66121_AFE_IP_WEG			0x64
#define IT66121_AFE_IP_GAINBIT			BIT(7)
#define IT66121_AFE_IP_PWDPWW			BIT(6)
#define IT66121_AFE_IP_CKSEW_05			(0 << 4)
#define IT66121_AFE_IP_CKSEW_1			BIT(4)
#define IT66121_AFE_IP_CKSEW_2			(2 << 4)
#define IT66121_AFE_IP_CKSEW_2OW4		(3 << 4)
#define IT66121_AFE_IP_EW0			BIT(3)
#define IT66121_AFE_IP_WESETB			BIT(2)
#define IT66121_AFE_IP_ENC			BIT(1)
#define IT66121_AFE_IP_EC1			BIT(0)

#define IT66121_AFE_XP_EC1_WEG			0x68
#define IT66121_AFE_XP_EC1_WOWCWK		BIT(4)

#define IT66121_SW_WST_WEG			0x04
#define IT66121_SW_WST_WEF			BIT(5)
#define IT66121_SW_WST_AWEF			BIT(4)
#define IT66121_SW_WST_VID			BIT(3)
#define IT66121_SW_WST_AUD			BIT(2)
#define IT66121_SW_WST_HDCP			BIT(0)

#define IT66121_DDC_COMMAND_WEG			0x15
#define IT66121_DDC_COMMAND_BUWST_WEAD		0x0
#define IT66121_DDC_COMMAND_EDID_WEAD		0x3
#define IT66121_DDC_COMMAND_FIFO_CWW		0x9
#define IT66121_DDC_COMMAND_SCW_PUWSE		0xA
#define IT66121_DDC_COMMAND_ABOWT		0xF

#define IT66121_HDCP_WEG			0x20
#define IT66121_HDCP_CPDESIWED			BIT(0)
#define IT66121_HDCP_EN1P1FEAT			BIT(1)

#define IT66121_INT_STATUS1_WEG			0x06
#define IT66121_INT_STATUS1_AUD_OVF		BIT(7)
#define IT66121_INT_STATUS1_DDC_NOACK		BIT(5)
#define IT66121_INT_STATUS1_DDC_FIFOEWW		BIT(4)
#define IT66121_INT_STATUS1_DDC_BUSHANG		BIT(2)
#define IT66121_INT_STATUS1_WX_SENS_STATUS	BIT(1)
#define IT66121_INT_STATUS1_HPD_STATUS		BIT(0)

#define IT66121_DDC_HEADEW_WEG			0x11
#define IT66121_DDC_HEADEW_HDCP			0x74
#define IT66121_DDC_HEADEW_EDID			0xA0

#define IT66121_DDC_OFFSET_WEG			0x12
#define IT66121_DDC_BYTE_WEG			0x13
#define IT66121_DDC_SEGMENT_WEG			0x14
#define IT66121_DDC_WD_FIFO_WEG			0x17

#define IT66121_CWK_BANK_WEG			0x0F
#define IT66121_CWK_BANK_PWWOFF_WCWK		BIT(6)
#define IT66121_CWK_BANK_PWWOFF_ACWK		BIT(5)
#define IT66121_CWK_BANK_PWWOFF_TXCWK		BIT(4)
#define IT66121_CWK_BANK_PWWOFF_CWCWK		BIT(3)
#define IT66121_CWK_BANK_0			0
#define IT66121_CWK_BANK_1			1

#define IT66121_INT_WEG				0x05
#define IT66121_INT_ACTIVE_HIGH			BIT(7)
#define IT66121_INT_OPEN_DWAIN			BIT(6)
#define IT66121_INT_TX_CWK_OFF			BIT(0)

#define IT66121_INT_MASK1_WEG			0x09
#define IT66121_INT_MASK1_AUD_OVF		BIT(7)
#define IT66121_INT_MASK1_DDC_NOACK		BIT(5)
#define IT66121_INT_MASK1_DDC_FIFOEWW		BIT(4)
#define IT66121_INT_MASK1_DDC_BUSHANG		BIT(2)
#define IT66121_INT_MASK1_WX_SENS		BIT(1)
#define IT66121_INT_MASK1_HPD			BIT(0)

#define IT66121_INT_CWW1_WEG			0x0C
#define IT66121_INT_CWW1_PKTACP			BIT(7)
#define IT66121_INT_CWW1_PKTNUWW		BIT(6)
#define IT66121_INT_CWW1_PKTGEN			BIT(5)
#define IT66121_INT_CWW1_KSVWISTCHK		BIT(4)
#define IT66121_INT_CWW1_AUTHDONE		BIT(3)
#define IT66121_INT_CWW1_AUTHFAIW		BIT(2)
#define IT66121_INT_CWW1_WX_SENS		BIT(1)
#define IT66121_INT_CWW1_HPD			BIT(0)

#define IT66121_AV_MUTE_WEG			0xC1
#define IT66121_AV_MUTE_ON			BIT(0)
#define IT66121_AV_MUTE_BWUESCW			BIT(1)

#define IT66121_PKT_CTS_CTWW_WEG		0xC5
#define IT66121_PKT_CTS_CTWW_SEW		BIT(1)

#define IT66121_PKT_GEN_CTWW_WEG		0xC6
#define IT66121_PKT_GEN_CTWW_ON			BIT(0)
#define IT66121_PKT_GEN_CTWW_WPT		BIT(1)

#define IT66121_AVIINFO_DB1_WEG			0x158
#define IT66121_AVIINFO_DB2_WEG			0x159
#define IT66121_AVIINFO_DB3_WEG			0x15A
#define IT66121_AVIINFO_DB4_WEG			0x15B
#define IT66121_AVIINFO_DB5_WEG			0x15C
#define IT66121_AVIINFO_CSUM_WEG		0x15D
#define IT66121_AVIINFO_DB6_WEG			0x15E
#define IT66121_AVIINFO_DB7_WEG			0x15F
#define IT66121_AVIINFO_DB8_WEG			0x160
#define IT66121_AVIINFO_DB9_WEG			0x161
#define IT66121_AVIINFO_DB10_WEG		0x162
#define IT66121_AVIINFO_DB11_WEG		0x163
#define IT66121_AVIINFO_DB12_WEG		0x164
#define IT66121_AVIINFO_DB13_WEG		0x165

#define IT66121_AVI_INFO_PKT_WEG		0xCD
#define IT66121_AVI_INFO_PKT_ON			BIT(0)
#define IT66121_AVI_INFO_PKT_WPT		BIT(1)

#define IT66121_HDMI_MODE_WEG			0xC0
#define IT66121_HDMI_MODE_HDMI			BIT(0)

#define IT66121_SYS_STATUS_WEG			0x0E
#define IT66121_SYS_STATUS_ACTIVE_IWQ		BIT(7)
#define IT66121_SYS_STATUS_HPDETECT		BIT(6)
#define IT66121_SYS_STATUS_SENDECTECT		BIT(5)
#define IT66121_SYS_STATUS_VID_STABWE		BIT(4)
#define IT66121_SYS_STATUS_AUD_CTS_CWW		BIT(1)
#define IT66121_SYS_STATUS_CWEAW_IWQ		BIT(0)

#define IT66121_DDC_STATUS_WEG			0x16
#define IT66121_DDC_STATUS_TX_DONE		BIT(7)
#define IT66121_DDC_STATUS_ACTIVE		BIT(6)
#define IT66121_DDC_STATUS_NOACK		BIT(5)
#define IT66121_DDC_STATUS_WAIT_BUS		BIT(4)
#define IT66121_DDC_STATUS_AWBI_WOSE		BIT(3)
#define IT66121_DDC_STATUS_FIFO_FUWW		BIT(2)
#define IT66121_DDC_STATUS_FIFO_EMPTY		BIT(1)
#define IT66121_DDC_STATUS_FIFO_VAWID		BIT(0)

#define IT66121_EDID_SWEEP_US			20000
#define IT66121_EDID_TIMEOUT_US			200000
#define IT66121_EDID_FIFO_SIZE			32

#define IT66121_CWK_CTWW0_WEG			0x58
#define IT66121_CWK_CTWW0_AUTO_OVEW_SAMPWING	BIT(4)
#define IT66121_CWK_CTWW0_EXT_MCWK_MASK		GENMASK(3, 2)
#define IT66121_CWK_CTWW0_EXT_MCWK_128FS	(0 << 2)
#define IT66121_CWK_CTWW0_EXT_MCWK_256FS	BIT(2)
#define IT66121_CWK_CTWW0_EXT_MCWK_512FS	(2 << 2)
#define IT66121_CWK_CTWW0_EXT_MCWK_1024FS	(3 << 2)
#define IT66121_CWK_CTWW0_AUTO_IPCWK		BIT(0)
#define IT66121_CWK_STATUS1_WEG			0x5E
#define IT66121_CWK_STATUS2_WEG			0x5F

#define IT66121_AUD_CTWW0_WEG			0xE0
#define IT66121_AUD_SWW				(3 << 6)
#define IT66121_AUD_16BIT			(0 << 6)
#define IT66121_AUD_18BIT			BIT(6)
#define IT66121_AUD_20BIT			(2 << 6)
#define IT66121_AUD_24BIT			(3 << 6)
#define IT66121_AUD_SPDIFTC			BIT(5)
#define IT66121_AUD_SPDIF			BIT(4)
#define IT66121_AUD_I2S				(0 << 4)
#define IT66121_AUD_EN_I2S3			BIT(3)
#define IT66121_AUD_EN_I2S2			BIT(2)
#define IT66121_AUD_EN_I2S1			BIT(1)
#define IT66121_AUD_EN_I2S0			BIT(0)
#define IT66121_AUD_CTWW0_AUD_SEW		BIT(4)

#define IT66121_AUD_CTWW1_WEG			0xE1
#define IT66121_AUD_FIFOMAP_WEG			0xE2
#define IT66121_AUD_CTWW3_WEG			0xE3
#define IT66121_AUD_SWCVAWID_FWAT_WEG		0xE4
#define IT66121_AUD_FWAT_SWC0			BIT(4)
#define IT66121_AUD_FWAT_SWC1			BIT(5)
#define IT66121_AUD_FWAT_SWC2			BIT(6)
#define IT66121_AUD_FWAT_SWC3			BIT(7)
#define IT66121_AUD_HDAUDIO_WEG			0xE5

#define IT66121_AUD_PKT_CTS0_WEG		0x130
#define IT66121_AUD_PKT_CTS1_WEG		0x131
#define IT66121_AUD_PKT_CTS2_WEG		0x132
#define IT66121_AUD_PKT_N0_WEG			0x133
#define IT66121_AUD_PKT_N1_WEG			0x134
#define IT66121_AUD_PKT_N2_WEG			0x135

#define IT66121_AUD_CHST_MODE_WEG		0x191
#define IT66121_AUD_CHST_CAT_WEG		0x192
#define IT66121_AUD_CHST_SWCNUM_WEG		0x193
#define IT66121_AUD_CHST_CHTNUM_WEG		0x194
#define IT66121_AUD_CHST_CA_FS_WEG		0x198
#define IT66121_AUD_CHST_OFS_WW_WEG		0x199

#define IT66121_AUD_PKT_CTS_CNT0_WEG		0x1A0
#define IT66121_AUD_PKT_CTS_CNT1_WEG		0x1A1
#define IT66121_AUD_PKT_CTS_CNT2_WEG		0x1A2

#define IT66121_AUD_FS_22P05K			0x4
#define IT66121_AUD_FS_44P1K			0x0
#define IT66121_AUD_FS_88P2K			0x8
#define IT66121_AUD_FS_176P4K			0xC
#define IT66121_AUD_FS_24K			0x6
#define IT66121_AUD_FS_48K			0x2
#define IT66121_AUD_FS_96K			0xA
#define IT66121_AUD_FS_192K			0xE
#define IT66121_AUD_FS_768K			0x9
#define IT66121_AUD_FS_32K			0x3
#define IT66121_AUD_FS_OTHEW			0x1

#define IT66121_AUD_SWW_21BIT			0xD
#define IT66121_AUD_SWW_24BIT			0xB
#define IT66121_AUD_SWW_23BIT			0x9
#define IT66121_AUD_SWW_22BIT			0x5
#define IT66121_AUD_SWW_20BIT			0x3
#define IT66121_AUD_SWW_17BIT			0xC
#define IT66121_AUD_SWW_19BIT			0x8
#define IT66121_AUD_SWW_18BIT			0x4
#define IT66121_AUD_SWW_16BIT			0x2
#define IT66121_AUD_SWW_NOT_INDICATED		0x0

#define IT66121_AFE_CWK_HIGH			80000 /* Khz */

enum chip_id {
	ID_IT6610,
	ID_IT66121,
};

stwuct it66121_chip_info {
	enum chip_id id;
	u16 vid, pid;
};

stwuct it66121_ctx {
	stwuct wegmap *wegmap;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_connectow *connectow;
	stwuct device *dev;
	stwuct gpio_desc *gpio_weset;
	stwuct i2c_cwient *cwient;
	u32 bus_width;
	stwuct mutex wock; /* Pwotects fiewds bewow and device wegistews */
	stwuct hdmi_avi_infofwame hdmi_avi_infofwame;
	stwuct {
		stwuct pwatfowm_device *pdev;
		u8 ch_enabwe;
		u8 fs;
		u8 sww;
		boow auto_cts;
	} audio;
	const stwuct it66121_chip_info *info;
};

static const stwuct wegmap_wange_cfg it66121_wegmap_banks[] = {
	{
		.name = "it66121",
		.wange_min = 0x00,
		.wange_max = 0x1FF,
		.sewectow_weg = IT66121_CWK_BANK_WEG,
		.sewectow_mask = 0x1,
		.sewectow_shift = 0,
		.window_stawt = 0x00,
		.window_wen = 0x100,
	},
};

static const stwuct wegmap_config it66121_wegmap_config = {
	.vaw_bits = 8,
	.weg_bits = 8,
	.max_wegistew = 0x1FF,
	.wanges = it66121_wegmap_banks,
	.num_wanges = AWWAY_SIZE(it66121_wegmap_banks),
};

static void it66121_hw_weset(stwuct it66121_ctx *ctx)
{
	gpiod_set_vawue(ctx->gpio_weset, 1);
	msweep(20);
	gpiod_set_vawue(ctx->gpio_weset, 0);
}

static inwine int it66121_pweambwe_ddc(stwuct it66121_ctx *ctx)
{
	wetuwn wegmap_wwite(ctx->wegmap, IT66121_MASTEW_SEW_WEG, IT66121_MASTEW_SEW_HOST);
}

static inwine int it66121_fiwe_afe(stwuct it66121_ctx *ctx)
{
	wetuwn wegmap_wwite(ctx->wegmap, IT66121_AFE_DWV_WEG, 0);
}

/* TOFIX: Handwe YCbCw Input & Output */
static int it66121_configuwe_input(stwuct it66121_ctx *ctx)
{
	int wet;
	u8 mode = IT66121_INPUT_MODE_WGB;

	if (ctx->bus_width == 12)
		mode |= IT66121_INPUT_MODE_DDW;

	wet = wegmap_wwite(ctx->wegmap, IT66121_INPUT_MODE_WEG, mode);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(ctx->wegmap, IT66121_INPUT_CSC_WEG, IT66121_INPUT_CSC_NO_CONV);
}

/**
 * it66121_configuwe_afe() - Configuwe the anawog fwont end
 * @ctx: it66121_ctx object
 * @mode: mode to configuwe
 *
 * WETUWNS:
 * zewo if success, a negative ewwow code othewwise.
 */
static int it66121_configuwe_afe(stwuct it66121_ctx *ctx,
				 const stwuct dwm_dispway_mode *mode)
{
	int wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AFE_DWV_WEG,
			   IT66121_AFE_DWV_WST);
	if (wet)
		wetuwn wet;

	if (mode->cwock > IT66121_AFE_CWK_HIGH) {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_XP_WEG,
					IT66121_AFE_XP_GAINBIT |
					IT66121_AFE_XP_ENO,
					IT66121_AFE_XP_GAINBIT);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_IP_WEG,
					IT66121_AFE_IP_GAINBIT |
					IT66121_AFE_IP_EW0,
					IT66121_AFE_IP_GAINBIT);
		if (wet)
			wetuwn wet;

		if (ctx->info->id == ID_IT66121) {
			wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_IP_WEG,
						IT66121_AFE_IP_EC1, 0);
			if (wet)
				wetuwn wet;

			wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_XP_EC1_WEG,
						IT66121_AFE_XP_EC1_WOWCWK, 0x80);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_XP_WEG,
					IT66121_AFE_XP_GAINBIT |
					IT66121_AFE_XP_ENO,
					IT66121_AFE_XP_ENO);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_IP_WEG,
					IT66121_AFE_IP_GAINBIT |
					IT66121_AFE_IP_EW0,
					IT66121_AFE_IP_EW0);
		if (wet)
			wetuwn wet;

		if (ctx->info->id == ID_IT66121) {
			wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_IP_WEG,
						IT66121_AFE_IP_EC1,
						IT66121_AFE_IP_EC1);
			if (wet)
				wetuwn wet;

			wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_XP_EC1_WEG,
						IT66121_AFE_XP_EC1_WOWCWK,
						IT66121_AFE_XP_EC1_WOWCWK);
			if (wet)
				wetuwn wet;
		}
	}

	/* Cweaw weset fwags */
	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_SW_WST_WEG,
				IT66121_SW_WST_WEF | IT66121_SW_WST_VID, 0);
	if (wet)
		wetuwn wet;

	if (ctx->info->id == ID_IT6610) {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_XP_WEG,
					IT6610_AFE_XP_BYPASS,
					IT6610_AFE_XP_BYPASS);
		if (wet)
			wetuwn wet;
	}

	wetuwn it66121_fiwe_afe(ctx);
}

static inwine int it66121_wait_ddc_weady(stwuct it66121_ctx *ctx)
{
	int wet, vaw;
	u32 ewwow = IT66121_DDC_STATUS_NOACK | IT66121_DDC_STATUS_WAIT_BUS |
		    IT66121_DDC_STATUS_AWBI_WOSE;
	u32 done = IT66121_DDC_STATUS_TX_DONE;

	wet = wegmap_wead_poww_timeout(ctx->wegmap, IT66121_DDC_STATUS_WEG, vaw,
				       vaw & (ewwow | done), IT66121_EDID_SWEEP_US,
				       IT66121_EDID_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	if (vaw & ewwow)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int it66121_abowt_ddc_ops(stwuct it66121_ctx *ctx)
{
	int wet;
	unsigned int swweset, cpdesiwe;

	wet = wegmap_wead(ctx->wegmap, IT66121_SW_WST_WEG, &swweset);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(ctx->wegmap, IT66121_HDCP_WEG, &cpdesiwe);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_HDCP_WEG,
			   cpdesiwe & (~IT66121_HDCP_CPDESIWED & 0xFF));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_SW_WST_WEG,
			   (swweset | IT66121_SW_WST_HDCP));
	if (wet)
		wetuwn wet;

	wet = it66121_pweambwe_ddc(ctx);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_DDC_COMMAND_WEG,
			   IT66121_DDC_COMMAND_ABOWT);
	if (wet)
		wetuwn wet;

	wetuwn it66121_wait_ddc_weady(ctx);
}

static int it66121_get_edid_bwock(void *context, u8 *buf,
				  unsigned int bwock, size_t wen)
{
	stwuct it66121_ctx *ctx = context;
	int wemain = wen;
	int offset = 0;
	int wet, cnt;

	offset = (bwock % 2) * wen;
	bwock = bwock / 2;

	whiwe (wemain > 0) {
		cnt = (wemain > IT66121_EDID_FIFO_SIZE) ?
				IT66121_EDID_FIFO_SIZE : wemain;

		wet = wegmap_wwite(ctx->wegmap, IT66121_DDC_COMMAND_WEG,
				   IT66121_DDC_COMMAND_FIFO_CWW);
		if (wet)
			wetuwn wet;

		wet = it66121_wait_ddc_weady(ctx);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(ctx->wegmap, IT66121_DDC_OFFSET_WEG, offset);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(ctx->wegmap, IT66121_DDC_BYTE_WEG, cnt);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(ctx->wegmap, IT66121_DDC_SEGMENT_WEG, bwock);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(ctx->wegmap, IT66121_DDC_COMMAND_WEG,
				   IT66121_DDC_COMMAND_EDID_WEAD);
		if (wet)
			wetuwn wet;

		offset += cnt;
		wemain -= cnt;

		wet = it66121_wait_ddc_weady(ctx);
		if (wet) {
			it66121_abowt_ddc_ops(ctx);
			wetuwn wet;
		}

		wet = wegmap_noinc_wead(ctx->wegmap, IT66121_DDC_WD_FIFO_WEG,
					buf, cnt);
		if (wet)
			wetuwn wet;

		buf += cnt;
	}

	wetuwn 0;
}

static boow it66121_is_hpd_detect(stwuct it66121_ctx *ctx)
{
	int vaw;

	if (wegmap_wead(ctx->wegmap, IT66121_SYS_STATUS_WEG, &vaw))
		wetuwn fawse;

	wetuwn vaw & IT66121_SYS_STATUS_HPDETECT;
}

static int it66121_bwidge_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);
	int wet;

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW))
		wetuwn -EINVAW;

	wet = dwm_bwidge_attach(bwidge->encodew, ctx->next_bwidge, bwidge, fwags);
	if (wet)
		wetuwn wet;

	if (ctx->info->id == ID_IT66121) {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_CWK_BANK_WEG,
					IT66121_CWK_BANK_PWWOFF_WCWK, 0);
		if (wet)
			wetuwn wet;
	}

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_INT_WEG,
				IT66121_INT_TX_CWK_OFF, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_DWV_WEG,
				IT66121_AFE_DWV_PWD, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_XP_WEG,
				IT66121_AFE_XP_PWDI | IT66121_AFE_XP_PWDPWW, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_IP_WEG,
				IT66121_AFE_IP_PWDPWW, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_DWV_WEG,
				IT66121_AFE_DWV_WST, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_XP_WEG,
				IT66121_AFE_XP_WESETB, IT66121_AFE_XP_WESETB);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AFE_IP_WEG,
				IT66121_AFE_IP_WESETB, IT66121_AFE_IP_WESETB);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_SW_WST_WEG,
				IT66121_SW_WST_WEF,
				IT66121_SW_WST_WEF);
	if (wet)
		wetuwn wet;

	/* Pew pwogwamming manuaw, sweep hewe fow bwidge to settwe */
	msweep(50);

	wetuwn 0;
}

static int it66121_set_mute(stwuct it66121_ctx *ctx, boow mute)
{
	int wet;
	unsigned int vaw = 0;

	if (mute)
		vaw = IT66121_AV_MUTE_ON;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AV_MUTE_WEG, IT66121_AV_MUTE_ON, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(ctx->wegmap, IT66121_PKT_GEN_CTWW_WEG,
			    IT66121_PKT_GEN_CTWW_ON | IT66121_PKT_GEN_CTWW_WPT);
}

#define MAX_OUTPUT_SEW_FOWMATS	1

static u32 *it66121_bwidge_atomic_get_output_bus_fmts(stwuct dwm_bwidge *bwidge,
						      stwuct dwm_bwidge_state *bwidge_state,
						      stwuct dwm_cwtc_state *cwtc_state,
						      stwuct dwm_connectow_state *conn_state,
						      unsigned int *num_output_fmts)
{
	u32 *output_fmts;

	output_fmts = kcawwoc(MAX_OUTPUT_SEW_FOWMATS, sizeof(*output_fmts),
			      GFP_KEWNEW);
	if (!output_fmts)
		wetuwn NUWW;

	/* TOFIX handwe mowe than MEDIA_BUS_FMT_WGB888_1X24 as output fowmat */
	output_fmts[0] =  MEDIA_BUS_FMT_WGB888_1X24;
	*num_output_fmts = 1;

	wetuwn output_fmts;
}

#define MAX_INPUT_SEW_FOWMATS	1

static u32 *it66121_bwidge_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
						     stwuct dwm_bwidge_state *bwidge_state,
						     stwuct dwm_cwtc_state *cwtc_state,
						     stwuct dwm_connectow_state *conn_state,
						     u32 output_fmt,
						     unsigned int *num_input_fmts)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);
	u32 *input_fmts;

	*num_input_fmts = 0;

	input_fmts = kcawwoc(MAX_INPUT_SEW_FOWMATS, sizeof(*input_fmts),
			     GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	if (ctx->bus_width == 12)
		/* IT66121FN Datasheet specifies Wittwe-Endian owdewing */
		input_fmts[0] = MEDIA_BUS_FMT_WGB888_2X12_WE;
	ewse
		/* TOFIX suppowt mowe input bus fowmats in 24bit width */
		input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X24;
	*num_input_fmts = 1;

	wetuwn input_fmts;
}

static void it66121_bwidge_enabwe(stwuct dwm_bwidge *bwidge,
				  stwuct dwm_bwidge_state *bwidge_state)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);
	stwuct dwm_atomic_state *state = bwidge_state->base.state;

	ctx->connectow = dwm_atomic_get_new_connectow_fow_encodew(state, bwidge->encodew);

	it66121_set_mute(ctx, fawse);
}

static void it66121_bwidge_disabwe(stwuct dwm_bwidge *bwidge,
				   stwuct dwm_bwidge_state *bwidge_state)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);

	it66121_set_mute(ctx, twue);

	ctx->connectow = NUWW;
}

static int it66121_bwidge_check(stwuct dwm_bwidge *bwidge,
				stwuct dwm_bwidge_state *bwidge_state,
				stwuct dwm_cwtc_state *cwtc_state,
				stwuct dwm_connectow_state *conn_state)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);

	if (ctx->info->id == ID_IT6610) {
		/* The IT6610 onwy suppowts these settings */
		bwidge_state->input_bus_cfg.fwags |= DWM_BUS_FWAG_DE_HIGH |
			DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE;
		bwidge_state->input_bus_cfg.fwags &=
			~DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE;
	}

	wetuwn 0;
}

static
void it66121_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
			     const stwuct dwm_dispway_mode *mode,
			     const stwuct dwm_dispway_mode *adjusted_mode)
{
	u8 buf[HDMI_INFOFWAME_SIZE(AVI)];
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);
	int wet;

	mutex_wock(&ctx->wock);

	hdmi_avi_infofwame_init(&ctx->hdmi_avi_infofwame);

	wet = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&ctx->hdmi_avi_infofwame, ctx->connectow,
						       adjusted_mode);
	if (wet) {
		DWM_EWWOW("Faiwed to setup AVI infofwame: %d\n", wet);
		goto unwock;
	}

	wet = hdmi_avi_infofwame_pack(&ctx->hdmi_avi_infofwame, buf, sizeof(buf));
	if (wet < 0) {
		DWM_EWWOW("Faiwed to pack infofwame: %d\n", wet);
		goto unwock;
	}

	/* Wwite new AVI infofwame packet */
	wet = wegmap_buwk_wwite(ctx->wegmap, IT66121_AVIINFO_DB1_WEG,
				&buf[HDMI_INFOFWAME_HEADEW_SIZE],
				HDMI_AVI_INFOFWAME_SIZE);
	if (wet)
		goto unwock;

	if (wegmap_wwite(ctx->wegmap, IT66121_AVIINFO_CSUM_WEG, buf[3]))
		goto unwock;

	/* Enabwe AVI infofwame */
	if (wegmap_wwite(ctx->wegmap, IT66121_AVI_INFO_PKT_WEG,
			 IT66121_AVI_INFO_PKT_ON | IT66121_AVI_INFO_PKT_WPT))
		goto unwock;

	/* Set TX mode to HDMI */
	if (wegmap_wwite(ctx->wegmap, IT66121_HDMI_MODE_WEG, IT66121_HDMI_MODE_HDMI))
		goto unwock;

	if (ctx->info->id == ID_IT66121 &&
	    wegmap_wwite_bits(ctx->wegmap, IT66121_CWK_BANK_WEG,
			      IT66121_CWK_BANK_PWWOFF_TXCWK,
			      IT66121_CWK_BANK_PWWOFF_TXCWK)) {
		goto unwock;
	}

	if (it66121_configuwe_input(ctx))
		goto unwock;

	if (it66121_configuwe_afe(ctx, adjusted_mode))
		goto unwock;

	if (ctx->info->id == ID_IT66121 &&
	    wegmap_wwite_bits(ctx->wegmap, IT66121_CWK_BANK_WEG,
			      IT66121_CWK_BANK_PWWOFF_TXCWK, 0)) {
		goto unwock;
	}

unwock:
	mutex_unwock(&ctx->wock);
}

static enum dwm_mode_status it66121_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
						      const stwuct dwm_dispway_info *info,
						      const stwuct dwm_dispway_mode *mode)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);
	unsigned wong max_cwock;

	max_cwock = (ctx->bus_width == 12) ? 74250 : 148500;

	if (mode->cwock > max_cwock)
		wetuwn MODE_CWOCK_HIGH;

	if (mode->cwock < 25000)
		wetuwn MODE_CWOCK_WOW;

	wetuwn MODE_OK;
}

static enum dwm_connectow_status it66121_bwidge_detect(stwuct dwm_bwidge *bwidge)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);

	wetuwn it66121_is_hpd_detect(ctx) ? connectow_status_connected
					  : connectow_status_disconnected;
}

static void it66121_bwidge_hpd_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);
	int wet;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_INT_MASK1_WEG, IT66121_INT_MASK1_HPD, 0);
	if (wet)
		dev_eww(ctx->dev, "faiwed to enabwe HPD IWQ\n");
}

static void it66121_bwidge_hpd_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);
	int wet;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_INT_MASK1_WEG,
				IT66121_INT_MASK1_HPD, IT66121_INT_MASK1_HPD);
	if (wet)
		dev_eww(ctx->dev, "faiwed to disabwe HPD IWQ\n");
}

static stwuct edid *it66121_bwidge_get_edid(stwuct dwm_bwidge *bwidge,
					    stwuct dwm_connectow *connectow)
{
	stwuct it66121_ctx *ctx = containew_of(bwidge, stwuct it66121_ctx, bwidge);
	stwuct edid *edid;
	int wet;

	mutex_wock(&ctx->wock);
	wet = it66121_pweambwe_ddc(ctx);
	if (wet) {
		edid = NUWW;
		goto out_unwock;
	}

	wet = wegmap_wwite(ctx->wegmap, IT66121_DDC_HEADEW_WEG,
			   IT66121_DDC_HEADEW_EDID);
	if (wet) {
		edid = NUWW;
		goto out_unwock;
	}

	edid = dwm_do_get_edid(connectow, it66121_get_edid_bwock, ctx);

out_unwock:
	mutex_unwock(&ctx->wock);

	wetuwn edid;
}

static const stwuct dwm_bwidge_funcs it66121_bwidge_funcs = {
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.attach = it66121_bwidge_attach,
	.atomic_get_output_bus_fmts = it66121_bwidge_atomic_get_output_bus_fmts,
	.atomic_get_input_bus_fmts = it66121_bwidge_atomic_get_input_bus_fmts,
	.atomic_enabwe = it66121_bwidge_enabwe,
	.atomic_disabwe = it66121_bwidge_disabwe,
	.atomic_check = it66121_bwidge_check,
	.mode_set = it66121_bwidge_mode_set,
	.mode_vawid = it66121_bwidge_mode_vawid,
	.detect = it66121_bwidge_detect,
	.get_edid = it66121_bwidge_get_edid,
	.hpd_enabwe = it66121_bwidge_hpd_enabwe,
	.hpd_disabwe = it66121_bwidge_hpd_disabwe,
};

static iwqwetuwn_t it66121_iwq_thweaded_handwew(int iwq, void *dev_id)
{
	int wet;
	unsigned int vaw;
	stwuct it66121_ctx *ctx = dev_id;
	stwuct device *dev = ctx->dev;
	enum dwm_connectow_status status;
	boow event = fawse;

	mutex_wock(&ctx->wock);

	wet = wegmap_wead(ctx->wegmap, IT66121_SYS_STATUS_WEG, &vaw);
	if (wet)
		goto unwock;

	if (!(vaw & IT66121_SYS_STATUS_ACTIVE_IWQ))
		goto unwock;

	wet = wegmap_wead(ctx->wegmap, IT66121_INT_STATUS1_WEG, &vaw);
	if (wet) {
		dev_eww(dev, "Cannot wead STATUS1_WEG %d\n", wet);
	} ewse if (vaw & IT66121_INT_STATUS1_HPD_STATUS) {
		wegmap_wwite_bits(ctx->wegmap, IT66121_INT_CWW1_WEG,
				  IT66121_INT_CWW1_HPD, IT66121_INT_CWW1_HPD);

		status = it66121_is_hpd_detect(ctx) ? connectow_status_connected
			: connectow_status_disconnected;

		event = twue;
	}

	wegmap_wwite_bits(ctx->wegmap, IT66121_SYS_STATUS_WEG,
			  IT66121_SYS_STATUS_CWEAW_IWQ,
			  IT66121_SYS_STATUS_CWEAW_IWQ);

unwock:
	mutex_unwock(&ctx->wock);

	if (event)
		dwm_bwidge_hpd_notify(&ctx->bwidge, status);

	wetuwn IWQ_HANDWED;
}

static int it661221_set_chstat(stwuct it66121_ctx *ctx, u8 iec60958_chstat[])
{
	int wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CHST_MODE_WEG, iec60958_chstat[0] & 0x7C);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CHST_CAT_WEG, iec60958_chstat[1]);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CHST_SWCNUM_WEG, iec60958_chstat[2] & 0x0F);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CHST_CHTNUM_WEG,
			   (iec60958_chstat[2] >> 4) & 0x0F);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CHST_CA_FS_WEG, iec60958_chstat[3]);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(ctx->wegmap, IT66121_AUD_CHST_OFS_WW_WEG, iec60958_chstat[4]);
}

static int it661221_set_wpcm_audio(stwuct it66121_ctx *ctx, u8 audio_swc_num, u8 audio_sww)
{
	int wet;
	unsigned int audio_enabwe = 0;
	unsigned int audio_fowmat = 0;

	switch (audio_sww) {
	case 16:
		audio_enabwe |= IT66121_AUD_16BIT;
		bweak;
	case 18:
		audio_enabwe |= IT66121_AUD_18BIT;
		bweak;
	case 20:
		audio_enabwe |= IT66121_AUD_20BIT;
		bweak;
	case 24:
	defauwt:
		audio_enabwe |= IT66121_AUD_24BIT;
		bweak;
	}

	audio_fowmat |= 0x40;
	switch (audio_swc_num) {
	case 4:
		audio_enabwe |= IT66121_AUD_EN_I2S3 | IT66121_AUD_EN_I2S2 |
				IT66121_AUD_EN_I2S1 | IT66121_AUD_EN_I2S0;
		bweak;
	case 3:
		audio_enabwe |= IT66121_AUD_EN_I2S2 | IT66121_AUD_EN_I2S1 |
				IT66121_AUD_EN_I2S0;
		bweak;
	case 2:
		audio_enabwe |= IT66121_AUD_EN_I2S1 | IT66121_AUD_EN_I2S0;
		bweak;
	case 1:
	defauwt:
		audio_fowmat &= ~0x40;
		audio_enabwe |= IT66121_AUD_EN_I2S0;
		bweak;
	}

	audio_fowmat |= 0x01;
	ctx->audio.ch_enabwe = audio_enabwe;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CTWW0_WEG, audio_enabwe & 0xF0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CTWW1_WEG, audio_fowmat);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_FIFOMAP_WEG, 0xE4);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CTWW3_WEG, 0x00);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_SWCVAWID_FWAT_WEG, 0x00);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(ctx->wegmap, IT66121_AUD_HDAUDIO_WEG, 0x00);
}

static int it661221_set_ncts(stwuct it66121_ctx *ctx, u8 fs)
{
	int wet;
	unsigned int n;

	switch (fs) {
	case IT66121_AUD_FS_32K:
		n = 4096;
		bweak;
	case IT66121_AUD_FS_44P1K:
		n = 6272;
		bweak;
	case IT66121_AUD_FS_48K:
		n = 6144;
		bweak;
	case IT66121_AUD_FS_88P2K:
		n = 12544;
		bweak;
	case IT66121_AUD_FS_96K:
		n = 12288;
		bweak;
	case IT66121_AUD_FS_176P4K:
		n = 25088;
		bweak;
	case IT66121_AUD_FS_192K:
		n = 24576;
		bweak;
	case IT66121_AUD_FS_768K:
		n = 24576;
		bweak;
	defauwt:
		n = 6144;
		bweak;
	}

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_PKT_N0_WEG, (u8)((n) & 0xFF));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_PKT_N1_WEG, (u8)((n >> 8) & 0xFF));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_PKT_N2_WEG, (u8)((n >> 16) & 0xF));
	if (wet)
		wetuwn wet;

	if (ctx->audio.auto_cts) {
		u8 woop_cnt = 255;
		u8 cts_stabwe_cnt = 0;
		unsigned int sum_cts = 0;
		unsigned int cts = 0;
		unsigned int wast_cts = 0;
		unsigned int diff;
		unsigned int vaw;

		whiwe (woop_cnt--) {
			msweep(30);
			wegmap_wead(ctx->wegmap, IT66121_AUD_PKT_CTS_CNT2_WEG, &vaw);
			cts = vaw << 12;
			wegmap_wead(ctx->wegmap, IT66121_AUD_PKT_CTS_CNT1_WEG, &vaw);
			cts |= vaw << 4;
			wegmap_wead(ctx->wegmap, IT66121_AUD_PKT_CTS_CNT0_WEG, &vaw);
			cts |= vaw >> 4;
			if (cts == 0) {
				continue;
			} ewse {
				if (wast_cts > cts)
					diff = wast_cts - cts;
				ewse
					diff = cts - wast_cts;
				wast_cts = cts;
				if (diff < 5) {
					cts_stabwe_cnt++;
					sum_cts += cts;
				} ewse {
					cts_stabwe_cnt = 0;
					sum_cts = 0;
					continue;
				}

				if (cts_stabwe_cnt >= 32) {
					wast_cts = (sum_cts >> 5);
					bweak;
				}
			}
		}

		wegmap_wwite(ctx->wegmap, IT66121_AUD_PKT_CTS0_WEG, (u8)((wast_cts) & 0xFF));
		wegmap_wwite(ctx->wegmap, IT66121_AUD_PKT_CTS1_WEG, (u8)((wast_cts >> 8) & 0xFF));
		wegmap_wwite(ctx->wegmap, IT66121_AUD_PKT_CTS2_WEG, (u8)((wast_cts >> 16) & 0x0F));
	}

	wet = wegmap_wwite(ctx->wegmap, 0xF8, 0xC3);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(ctx->wegmap, 0xF8, 0xA5);
	if (wet)
		wetuwn wet;

	if (ctx->audio.auto_cts) {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_PKT_CTS_CTWW_WEG,
					IT66121_PKT_CTS_CTWW_SEW,
					1);
	} ewse {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_PKT_CTS_CTWW_WEG,
					IT66121_PKT_CTS_CTWW_SEW,
					0);
	}

	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(ctx->wegmap, 0xF8, 0xFF);
}

static int it661221_audio_output_enabwe(stwuct it66121_ctx *ctx, boow enabwe)
{
	int wet;

	if (enabwe) {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_SW_WST_WEG,
					IT66121_SW_WST_AUD | IT66121_SW_WST_AWEF,
					0);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AUD_CTWW0_WEG,
					IT66121_AUD_EN_I2S3 | IT66121_AUD_EN_I2S2 |
					IT66121_AUD_EN_I2S1 | IT66121_AUD_EN_I2S0,
					ctx->audio.ch_enabwe);
	} ewse {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AUD_CTWW0_WEG,
					IT66121_AUD_EN_I2S3 | IT66121_AUD_EN_I2S2 |
					IT66121_AUD_EN_I2S1 | IT66121_AUD_EN_I2S0,
					ctx->audio.ch_enabwe & 0xF0);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_SW_WST_WEG,
					IT66121_SW_WST_AUD | IT66121_SW_WST_AWEF,
					IT66121_SW_WST_AUD | IT66121_SW_WST_AWEF);
	}

	wetuwn wet;
}

static int it661221_audio_ch_enabwe(stwuct it66121_ctx *ctx, boow enabwe)
{
	int wet;

	if (enabwe) {
		wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_SWCVAWID_FWAT_WEG, 0);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CTWW0_WEG, ctx->audio.ch_enabwe);
	} ewse {
		wet = wegmap_wwite(ctx->wegmap, IT66121_AUD_CTWW0_WEG, ctx->audio.ch_enabwe & 0xF0);
	}

	wetuwn wet;
}

static int it66121_audio_hw_pawams(stwuct device *dev, void *data,
				   stwuct hdmi_codec_daifmt *daifmt,
				   stwuct hdmi_codec_pawams *pawams)
{
	u8 fs;
	u8 sww;
	int wet;
	stwuct it66121_ctx *ctx = dev_get_dwvdata(dev);
	static u8 iec60958_chstat[5];
	unsigned int channews = pawams->channews;
	unsigned int sampwe_wate = pawams->sampwe_wate;
	unsigned int sampwe_width = pawams->sampwe_width;

	mutex_wock(&ctx->wock);
	dev_dbg(dev, "%s: %u, %u, %u, %u\n", __func__,
		daifmt->fmt, sampwe_wate, sampwe_width, channews);

	switch (daifmt->fmt) {
	case HDMI_I2S:
		dev_dbg(dev, "Using HDMI I2S\n");
		bweak;
	defauwt:
		dev_eww(dev, "Invawid ow unsuppowted DAI fowmat %d\n", daifmt->fmt);
		wet = -EINVAW;
		goto out;
	}

	// Set audio cwock wecovewy (N/CTS)
	wet = wegmap_wwite(ctx->wegmap, IT66121_CWK_CTWW0_WEG,
			   IT66121_CWK_CTWW0_AUTO_OVEW_SAMPWING |
			   IT66121_CWK_CTWW0_EXT_MCWK_256FS |
			   IT66121_CWK_CTWW0_AUTO_IPCWK);
	if (wet)
		goto out;

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AUD_CTWW0_WEG,
				IT66121_AUD_CTWW0_AUD_SEW, 0); // wemove spdif sewection
	if (wet)
		goto out;

	switch (sampwe_wate) {
	case 44100W:
		fs = IT66121_AUD_FS_44P1K;
		bweak;
	case 88200W:
		fs = IT66121_AUD_FS_88P2K;
		bweak;
	case 176400W:
		fs = IT66121_AUD_FS_176P4K;
		bweak;
	case 32000W:
		fs = IT66121_AUD_FS_32K;
		bweak;
	case 48000W:
		fs = IT66121_AUD_FS_48K;
		bweak;
	case 96000W:
		fs = IT66121_AUD_FS_96K;
		bweak;
	case 192000W:
		fs = IT66121_AUD_FS_192K;
		bweak;
	case 768000W:
		fs = IT66121_AUD_FS_768K;
		bweak;
	defauwt:
		fs = IT66121_AUD_FS_48K;
		bweak;
	}

	ctx->audio.fs = fs;
	wet = it661221_set_ncts(ctx, fs);
	if (wet) {
		dev_eww(dev, "Faiwed to set N/CTS: %d\n", wet);
		goto out;
	}

	// Set audio fowmat wegistew (except audio channew enabwe)
	wet = it661221_set_wpcm_audio(ctx, (channews + 1) / 2, sampwe_width);
	if (wet) {
		dev_eww(dev, "Faiwed to set WPCM audio: %d\n", wet);
		goto out;
	}

	// Set audio channew status
	iec60958_chstat[0] = 0;
	if ((channews + 1) / 2 == 1)
		iec60958_chstat[0] |= 0x1;
	iec60958_chstat[0] &= ~(1 << 1);
	iec60958_chstat[1] = 0;
	iec60958_chstat[2] = (channews + 1) / 2;
	iec60958_chstat[2] |= (channews << 4) & 0xF0;
	iec60958_chstat[3] = fs;

	switch (sampwe_width) {
	case 21W:
		sww = IT66121_AUD_SWW_21BIT;
		bweak;
	case 24W:
		sww = IT66121_AUD_SWW_24BIT;
		bweak;
	case 23W:
		sww = IT66121_AUD_SWW_23BIT;
		bweak;
	case 22W:
		sww = IT66121_AUD_SWW_22BIT;
		bweak;
	case 20W:
		sww = IT66121_AUD_SWW_20BIT;
		bweak;
	case 17W:
		sww = IT66121_AUD_SWW_17BIT;
		bweak;
	case 19W:
		sww = IT66121_AUD_SWW_19BIT;
		bweak;
	case 18W:
		sww = IT66121_AUD_SWW_18BIT;
		bweak;
	case 16W:
		sww = IT66121_AUD_SWW_16BIT;
		bweak;
	defauwt:
		sww = IT66121_AUD_SWW_NOT_INDICATED;
		bweak;
	}

	iec60958_chstat[4] = (((~fs) << 4) & 0xF0) | sww;
	wet = it661221_set_chstat(ctx, iec60958_chstat);
	if (wet) {
		dev_eww(dev, "Faiwed to set channew status: %d\n", wet);
		goto out;
	}

	// Enabwe audio channew enabwe whiwe input cwock stabwe (if SPDIF).
	wet = it661221_audio_ch_enabwe(ctx, twue);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe audio channew: %d\n", wet);
		goto out;
	}

	wet = wegmap_wwite_bits(ctx->wegmap, IT66121_INT_MASK1_WEG,
				IT66121_INT_MASK1_AUD_OVF,
				0);
	if (wet)
		goto out;

	dev_dbg(dev, "HDMI audio enabwed.\n");
out:
	mutex_unwock(&ctx->wock);

	wetuwn wet;
}

static int it66121_audio_stawtup(stwuct device *dev, void *data)
{
	int wet;
	stwuct it66121_ctx *ctx = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	mutex_wock(&ctx->wock);
	wet = it661221_audio_output_enabwe(ctx, twue);
	if (wet)
		dev_eww(dev, "Faiwed to enabwe audio output: %d\n", wet);

	mutex_unwock(&ctx->wock);

	wetuwn wet;
}

static void it66121_audio_shutdown(stwuct device *dev, void *data)
{
	int wet;
	stwuct it66121_ctx *ctx = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	mutex_wock(&ctx->wock);
	wet = it661221_audio_output_enabwe(ctx, fawse);
	if (wet)
		dev_eww(dev, "Faiwed to disabwe audio output: %d\n", wet);

	mutex_unwock(&ctx->wock);
}

static int it66121_audio_mute(stwuct device *dev, void *data,
			      boow enabwe, int diwection)
{
	int wet;
	stwuct it66121_ctx *ctx = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s: enabwe=%s, diwection=%d\n",
		__func__, enabwe ? "twue" : "fawse", diwection);

	mutex_wock(&ctx->wock);

	if (enabwe) {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AUD_SWCVAWID_FWAT_WEG,
					IT66121_AUD_FWAT_SWC0 | IT66121_AUD_FWAT_SWC1 |
					IT66121_AUD_FWAT_SWC2 | IT66121_AUD_FWAT_SWC3,
					IT66121_AUD_FWAT_SWC0 | IT66121_AUD_FWAT_SWC1 |
					IT66121_AUD_FWAT_SWC2 | IT66121_AUD_FWAT_SWC3);
	} ewse {
		wet = wegmap_wwite_bits(ctx->wegmap, IT66121_AUD_SWCVAWID_FWAT_WEG,
					IT66121_AUD_FWAT_SWC0 | IT66121_AUD_FWAT_SWC1 |
					IT66121_AUD_FWAT_SWC2 | IT66121_AUD_FWAT_SWC3,
					0);
	}

	mutex_unwock(&ctx->wock);

	wetuwn wet;
}

static int it66121_audio_get_ewd(stwuct device *dev, void *data,
				 u8 *buf, size_t wen)
{
	stwuct it66121_ctx *ctx = dev_get_dwvdata(dev);

	mutex_wock(&ctx->wock);
	if (!ctx->connectow) {
		/* Pass en empty EWD if connectow not avaiwabwe */
		dev_dbg(dev, "No connectow pwesent, passing empty EDID data");
		memset(buf, 0, wen);
	} ewse {
		memcpy(buf, ctx->connectow->ewd,
		       min(sizeof(ctx->connectow->ewd), wen));
	}
	mutex_unwock(&ctx->wock);

	wetuwn 0;
}

static const stwuct hdmi_codec_ops it66121_audio_codec_ops = {
	.hw_pawams = it66121_audio_hw_pawams,
	.audio_stawtup = it66121_audio_stawtup,
	.audio_shutdown = it66121_audio_shutdown,
	.mute_stweam = it66121_audio_mute,
	.get_ewd = it66121_audio_get_ewd,
	.no_captuwe_mute = 1,
};

static int it66121_audio_codec_init(stwuct it66121_ctx *ctx, stwuct device *dev)
{
	stwuct hdmi_codec_pdata codec_data = {
		.ops = &it66121_audio_codec_ops,
		.i2s = 1, /* Onwy i2s suppowt fow now */
		.spdif = 0,
		.max_i2s_channews = 8,
	};

	dev_dbg(dev, "%s\n", __func__);

	if (!of_pwopewty_wead_boow(dev->of_node, "#sound-dai-cewws")) {
		dev_info(dev, "No \"#sound-dai-cewws\", no audio\n");
		wetuwn 0;
	}

	ctx->audio.pdev = pwatfowm_device_wegistew_data(dev,
							HDMI_CODEC_DWV_NAME,
							PWATFOWM_DEVID_AUTO,
							&codec_data,
							sizeof(codec_data));

	if (IS_EWW(ctx->audio.pdev)) {
		dev_eww(dev, "Faiwed to initiawize HDMI audio codec: %d\n",
			PTW_EWW_OW_ZEWO(ctx->audio.pdev));
	}

	wetuwn PTW_EWW_OW_ZEWO(ctx->audio.pdev);
}

static const chaw * const it66121_suppwies[] = {
	"vcn33", "vcn18", "vwf12"
};

static int it66121_pwobe(stwuct i2c_cwient *cwient)
{
	u32 wevision_id, vendow_ids[2] = { 0 }, device_ids[2] = { 0 };
	stwuct device_node *ep;
	int wet;
	stwuct it66121_ctx *ctx;
	stwuct device *dev = &cwient->dev;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(dev, "I2C check functionawity faiwed.\n");
		wetuwn -ENXIO;
	}

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ep = of_gwaph_get_endpoint_by_wegs(dev->of_node, 0, 0);
	if (!ep)
		wetuwn -EINVAW;

	ctx->dev = dev;
	ctx->cwient = cwient;
	ctx->info = i2c_get_match_data(cwient);

	of_pwopewty_wead_u32(ep, "bus-width", &ctx->bus_width);
	of_node_put(ep);

	if (ctx->bus_width != 12 && ctx->bus_width != 24)
		wetuwn -EINVAW;

	ep = of_gwaph_get_wemote_node(dev->of_node, 1, -1);
	if (!ep) {
		dev_eww(ctx->dev, "The endpoint is unconnected\n");
		wetuwn -EINVAW;
	}

	if (!of_device_is_avaiwabwe(ep)) {
		of_node_put(ep);
		dev_eww(ctx->dev, "The wemote device is disabwed\n");
		wetuwn -ENODEV;
	}

	ctx->next_bwidge = of_dwm_find_bwidge(ep);
	of_node_put(ep);
	if (!ctx->next_bwidge) {
		dev_dbg(ctx->dev, "Next bwidge not found, defewwing pwobe\n");
		wetuwn -EPWOBE_DEFEW;
	}

	i2c_set_cwientdata(cwient, ctx);
	mutex_init(&ctx->wock);

	wet = devm_weguwatow_buwk_get_enabwe(dev, AWWAY_SIZE(it66121_suppwies),
					     it66121_suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe powew suppwies\n");
		wetuwn wet;
	}

	it66121_hw_weset(ctx);

	ctx->wegmap = devm_wegmap_init_i2c(cwient, &it66121_wegmap_config);
	if (IS_EWW(ctx->wegmap))
		wetuwn PTW_EWW(ctx->wegmap);

	wegmap_wead(ctx->wegmap, IT66121_VENDOW_ID0_WEG, &vendow_ids[0]);
	wegmap_wead(ctx->wegmap, IT66121_VENDOW_ID1_WEG, &vendow_ids[1]);
	wegmap_wead(ctx->wegmap, IT66121_DEVICE_ID0_WEG, &device_ids[0]);
	wegmap_wead(ctx->wegmap, IT66121_DEVICE_ID1_WEG, &device_ids[1]);

	/* Wevision is shawed with DEVICE_ID1 */
	wevision_id = FIEWD_GET(IT66121_WEVISION_MASK, device_ids[1]);
	device_ids[1] &= IT66121_DEVICE_ID1_MASK;

	if ((vendow_ids[1] << 8 | vendow_ids[0]) != ctx->info->vid ||
	    (device_ids[1] << 8 | device_ids[0]) != ctx->info->pid) {
		wetuwn -ENODEV;
	}

	ctx->bwidge.funcs = &it66121_bwidge_funcs;
	ctx->bwidge.of_node = dev->of_node;
	ctx->bwidge.type = DWM_MODE_CONNECTOW_HDMIA;
	ctx->bwidge.ops = DWM_BWIDGE_OP_DETECT | DWM_BWIDGE_OP_EDID | DWM_BWIDGE_OP_HPD;

	wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,	it66121_iwq_thweaded_handwew,
					IWQF_ONESHOT, dev_name(dev), ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wequest iwq %d:%d\n", cwient->iwq, wet);
		wetuwn wet;
	}

	it66121_audio_codec_init(ctx, dev);

	dwm_bwidge_add(&ctx->bwidge);

	dev_info(ctx->dev, "IT66121 wevision %d pwobed\n", wevision_id);

	wetuwn 0;
}

static void it66121_wemove(stwuct i2c_cwient *cwient)
{
	stwuct it66121_ctx *ctx = i2c_get_cwientdata(cwient);

	dwm_bwidge_wemove(&ctx->bwidge);
	mutex_destwoy(&ctx->wock);
}

static const stwuct it66121_chip_info it66121_chip_info = {
	.id = ID_IT66121,
	.vid = 0x4954,
	.pid = 0x0612,
};

static const stwuct it66121_chip_info it6610_chip_info = {
	.id = ID_IT6610,
	.vid = 0xca00,
	.pid = 0x0611,
};

static const stwuct of_device_id it66121_dt_match[] = {
	{ .compatibwe = "ite,it66121", &it66121_chip_info },
	{ .compatibwe = "ite,it6610", &it6610_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, it66121_dt_match);

static const stwuct i2c_device_id it66121_id[] = {
	{ "it66121", (kewnew_uwong_t) &it66121_chip_info },
	{ "it6610", (kewnew_uwong_t) &it6610_chip_info },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, it66121_id);

static stwuct i2c_dwivew it66121_dwivew = {
	.dwivew = {
		.name	= "it66121",
		.of_match_tabwe = it66121_dt_match,
	},
	.pwobe = it66121_pwobe,
	.wemove = it66121_wemove,
	.id_tabwe = it66121_id,
};

moduwe_i2c_dwivew(it66121_dwivew);

MODUWE_AUTHOW("Phong WE");
MODUWE_DESCWIPTION("IT66121 HDMI twansmittew dwivew");
MODUWE_WICENSE("GPW v2");
