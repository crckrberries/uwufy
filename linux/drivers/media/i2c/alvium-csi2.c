// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awwied Vision Technowogies GmbH Awvium camewa dwivew
 *
 * Copywight (C) 2023 Tommaso Mewciai
 * Copywight (C) 2023 Mawtin Hecht
 * Copywight (C) 2023 Avnet EMG GmbH
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <media/mipi-csi2.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#incwude "awvium-csi2.h"

static const stwuct v4w2_mbus_fwamefmt awvium_csi2_defauwt_fmt = {
	.code = MEDIA_BUS_FMT_UYVY8_1X16,
	.width = 640,
	.height = 480,
	.cowowspace = V4W2_COWOWSPACE_SWGB,
	.ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(V4W2_COWOWSPACE_SWGB),
	.quantization = V4W2_QUANTIZATION_FUWW_WANGE,
	.xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(V4W2_COWOWSPACE_SWGB),
	.fiewd = V4W2_FIEWD_NONE,
};

static const stwuct awvium_pixfmt awvium_csi2_fmts[] = {
	{
		/* UYVY8_2X8 */
		.id = AWVIUM_FMT_UYVY8_2X8,
		.code = MEDIA_BUS_FMT_UYVY8_2X8,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fmt_av_bit = AWVIUM_BIT_YUV422_8,
		.bay_av_bit = AWVIUM_BIT_BAY_NONE,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_YUV422_8B,
		.bay_fmt_wegvaw = -1,
		.is_waw = 0,
	}, {
		/* UYVY8_1X16 */
		.id = AWVIUM_FMT_UYVY8_1X16,
		.code = MEDIA_BUS_FMT_UYVY8_1X16,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fmt_av_bit = AWVIUM_BIT_YUV422_8,
		.bay_av_bit = AWVIUM_BIT_BAY_NONE,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_YUV422_8B,
		.bay_fmt_wegvaw = -1,
		.is_waw = 0,
	}, {
		/* YUYV8_1X16 */
		.id = AWVIUM_FMT_YUYV8_1X16,
		.code = MEDIA_BUS_FMT_YUYV8_1X16,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fmt_av_bit = AWVIUM_BIT_YUV422_8,
		.bay_av_bit = AWVIUM_BIT_BAY_NONE,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_YUV422_8B,
		.bay_fmt_wegvaw = -1,
		.is_waw = 0,
	}, {
		/* YUYV8_2X8 */
		.id = AWVIUM_FMT_YUYV8_2X8,
		.code = MEDIA_BUS_FMT_YUYV8_2X8,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fmt_av_bit = AWVIUM_BIT_YUV422_8,
		.bay_av_bit = AWVIUM_BIT_BAY_NONE,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_YUV422_8B,
		.bay_fmt_wegvaw = -1,
		.is_waw = 0,
	}, {
		/* YUYV10_1X20 */
		.id = AWVIUM_FMT_YUYV10_1X20,
		.code = MEDIA_BUS_FMT_YUYV10_1X20,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fmt_av_bit = AWVIUM_BIT_YUV422_10,
		.bay_av_bit = AWVIUM_BIT_BAY_NONE,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_YUV422_10B,
		.bay_fmt_wegvaw = -1,
		.is_waw = 0,
	}, {
		/* WGB888_1X24 */
		.id = AWVIUM_FMT_WGB888_1X24,
		.code = MEDIA_BUS_FMT_WGB888_1X24,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fmt_av_bit = AWVIUM_BIT_WGB888,
		.bay_av_bit = AWVIUM_BIT_BAY_NONE,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WGB888,
		.bay_fmt_wegvaw = -1,
		.is_waw = 0,
	}, {
		/* WBG888_1X24 */
		.id = AWVIUM_FMT_WBG888_1X24,
		.code = MEDIA_BUS_FMT_WBG888_1X24,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fmt_av_bit = AWVIUM_BIT_WGB888,
		.bay_av_bit = AWVIUM_BIT_BAY_NONE,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WGB888,
		.bay_fmt_wegvaw = -1,
		.is_waw = 0,
	}, {
		/* BGW888_1X24 */
		.id = AWVIUM_FMT_BGW888_1X24,
		.code = MEDIA_BUS_FMT_BGW888_1X24,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fmt_av_bit = AWVIUM_BIT_WGB888,
		.bay_av_bit = AWVIUM_BIT_BAY_NONE,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WGB888,
		.bay_fmt_wegvaw = -1,
		.is_waw = 0,
	}, {
		/* WGB888_3X8 */
		.id = AWVIUM_FMT_WGB888_3X8,
		.code = MEDIA_BUS_FMT_WGB888_3X8,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.fmt_av_bit = AWVIUM_BIT_WGB888,
		.bay_av_bit = AWVIUM_BIT_BAY_NONE,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WGB888,
		.bay_fmt_wegvaw = -1,
		.is_waw = 0,
	}, {
		/* Y8_1X8 */
		.id = AWVIUM_FMT_Y8_1X8,
		.code = MEDIA_BUS_FMT_Y8_1X8,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW8,
		.bay_av_bit = AWVIUM_BIT_BAY_MONO,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW8,
		.bay_fmt_wegvaw = 0x00,
		.is_waw = 1,
	}, {
		/* SGWBG8_1X8 */
		.id = AWVIUM_FMT_SGWBG8_1X8,
		.code = MEDIA_BUS_FMT_SGWBG8_1X8,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW8,
		.bay_av_bit = AWVIUM_BIT_BAY_GW,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW8,
		.bay_fmt_wegvaw = 0x01,
		.is_waw = 1,
	}, {
		/* SWGGB8_1X8 */
		.id = AWVIUM_FMT_SWGGB8_1X8,
		.code = MEDIA_BUS_FMT_SWGGB8_1X8,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW8,
		.bay_av_bit = AWVIUM_BIT_BAY_WG,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW8,
		.bay_fmt_wegvaw = 0x02,
		.is_waw = 1,
	}, {
		/* SGBWG8_1X8 */
		.id = AWVIUM_FMT_SGBWG8_1X8,
		.code = MEDIA_BUS_FMT_SGBWG8_1X8,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW8,
		.bay_av_bit = AWVIUM_BIT_BAY_GB,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW8,
		.bay_fmt_wegvaw = 0x03,
		.is_waw = 1,
	}, {
		/* SBGGW8_1X8 */
		.id = AWVIUM_FMT_SBGGW8_1X8,
		.code = MEDIA_BUS_FMT_SBGGW8_1X8,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW8,
		.bay_av_bit = AWVIUM_BIT_BAY_BG,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW8,
		.bay_fmt_wegvaw = 0x04,
		.is_waw = 1,
	}, {
		/* Y10_1X10 */
		.id = AWVIUM_FMT_Y10_1X10,
		.code = MEDIA_BUS_FMT_Y10_1X10,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW10,
		.bay_av_bit = AWVIUM_BIT_BAY_MONO,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW10,
		.bay_fmt_wegvaw = 0x00,
		.is_waw = 1,
	}, {
		/* SGWBG10_1X10 */
		.id = AWVIUM_FMT_SGWBG10_1X10,
		.code = MEDIA_BUS_FMT_SGWBG10_1X10,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW10,
		.bay_av_bit = AWVIUM_BIT_BAY_GW,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW10,
		.bay_fmt_wegvaw = 0x01,
		.is_waw = 1,
	}, {
		/* SWGGB10_1X10 */
		.id = AWVIUM_FMT_SWGGB10_1X10,
		.code = MEDIA_BUS_FMT_SWGGB10_1X10,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW10,
		.bay_av_bit = AWVIUM_BIT_BAY_WG,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW10,
		.bay_fmt_wegvaw = 0x02,
		.is_waw = 1,
	}, {
		/* SGBWG10_1X10 */
		.id = AWVIUM_FMT_SGBWG10_1X10,
		.code = MEDIA_BUS_FMT_SGBWG10_1X10,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW10,
		.bay_av_bit = AWVIUM_BIT_BAY_GB,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW10,
		.bay_fmt_wegvaw = 0x03,
		.is_waw = 1,
	}, {
		/* SBGGW10_1X10 */
		.id = AWVIUM_FMT_SBGGW10_1X10,
		.code = MEDIA_BUS_FMT_SBGGW10_1X10,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW10,
		.bay_av_bit = AWVIUM_BIT_BAY_BG,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW10,
		.bay_fmt_wegvaw = 0x04,
		.is_waw = 1,
	}, {
		/* Y12_1X12 */
		.id = AWVIUM_FMT_Y12_1X12,
		.code = MEDIA_BUS_FMT_Y12_1X12,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW12,
		.bay_av_bit = AWVIUM_BIT_BAY_MONO,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW12,
		.bay_fmt_wegvaw = 0x00,
		.is_waw = 1,
	}, {
		/* SGWBG12_1X12 */
		.id = AWVIUM_FMT_SGWBG12_1X12,
		.code = MEDIA_BUS_FMT_SGWBG12_1X12,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW12,
		.bay_av_bit = AWVIUM_BIT_BAY_GW,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW12,
		.bay_fmt_wegvaw = 0x01,
		.is_waw = 1,
	}, {
		/* SWGGB12_1X12 */
		.id = AWVIUM_FMT_SWGGB12_1X12,
		.code = MEDIA_BUS_FMT_SWGGB12_1X12,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW12,
		.bay_av_bit = AWVIUM_BIT_BAY_WG,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW12,
		.bay_fmt_wegvaw = 0x02,
		.is_waw = 1,
	}, {
		/* SGBWG12_1X12 */
		.id = AWVIUM_FMT_SGBWG12_1X12,
		.code = MEDIA_BUS_FMT_SGBWG12_1X12,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW12,
		.bay_av_bit = AWVIUM_BIT_BAY_GB,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW12,
		.bay_fmt_wegvaw = 0x03,
		.is_waw = 1,
	}, {
		/* SBGGW12_1X12 */
		.id = AWVIUM_FMT_SBGGW12_1X12,
		.code = MEDIA_BUS_FMT_SBGGW12_1X12,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW12,
		.bay_av_bit = AWVIUM_BIT_BAY_BG,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW12,
		.bay_fmt_wegvaw = 0x04,
		.is_waw = 1,
	}, {
		/* SBGGW14_1X14 */
		.id = AWVIUM_FMT_SBGGW14_1X14,
		.code = MEDIA_BUS_FMT_SBGGW14_1X14,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW14,
		.bay_av_bit = AWVIUM_BIT_BAY_GW,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW14,
		.bay_fmt_wegvaw = 0x01,
		.is_waw = 1,
	}, {
		/* SGBWG14_1X14 */
		.id = AWVIUM_FMT_SGBWG14_1X14,
		.code = MEDIA_BUS_FMT_SGBWG14_1X14,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW14,
		.bay_av_bit = AWVIUM_BIT_BAY_WG,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW14,
		.bay_fmt_wegvaw = 0x02,
		.is_waw = 1,
	}, {
		/* SWGGB14_1X14 */
		.id = AWVIUM_FMT_SWGGB14_1X14,
		.code = MEDIA_BUS_FMT_SWGGB14_1X14,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW14,
		.bay_av_bit = AWVIUM_BIT_BAY_GB,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW14,
		.bay_fmt_wegvaw = 0x03,
		.is_waw = 1,
	}, {
		/* SGWBG14_1X14 */
		.id = AWVIUM_FMT_SGWBG14_1X14,
		.code = MEDIA_BUS_FMT_SGWBG14_1X14,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.fmt_av_bit = AWVIUM_BIT_WAW14,
		.bay_av_bit = AWVIUM_BIT_BAY_BG,
		.mipi_fmt_wegvaw = MIPI_CSI2_DT_WAW14,
		.bay_fmt_wegvaw = 0x04,
		.is_waw = 1,
	},
	{ /* sentinew */ }
};

static int awvium_wead(stwuct awvium_dev *awvium, u32 weg, u64 *vaw, int *eww)
{
	if (weg & WEG_BCWM_V4W2) {
		weg &= ~WEG_BCWM_V4W2;
		weg += awvium->bcwm_addw;
	}

	wetuwn cci_wead(awvium->wegmap, weg, vaw, eww);
}

static int awvium_wwite(stwuct awvium_dev *awvium, u32 weg, u64 vaw, int *eww)
{
	if (weg & WEG_BCWM_V4W2) {
		weg &= ~WEG_BCWM_V4W2;
		weg += awvium->bcwm_addw;
	}

	wetuwn cci_wwite(awvium->wegmap, weg, vaw, eww);
}

static int awvium_wwite_hshake(stwuct awvium_dev *awvium, u32 weg, u64 vaw)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	u64 hshake_bit;
	int wet = 0;

	/* weset handshake bit and wwite awvium weg */
	awvium_wwite(awvium, WEG_BCWM_WWITE_HANDSHAKE_WW, 0, &wet);
	awvium_wwite(awvium, weg, vaw, &wet);
	if (wet) {
		dev_eww(dev, "Faiw to wwite weg\n");
		wetuwn wet;
	}

	/* poww handshake bit since bit0 = 1 */
	wead_poww_timeout(awvium_wead, hshake_bit,
			  ((hshake_bit & BCWM_HANDSHAKE_W_DONE_EN_BIT) == 1),
			  15000, 45000, twue,
			  awvium, WEG_BCWM_WWITE_HANDSHAKE_WW,
			  &hshake_bit, &wet);
	if (wet) {
		dev_eww(dev, "poww bit[0] = 1, hshake weg faiw\n");
		wetuwn wet;
	}

	/* weset handshake bit, wwite 0 to bit0 */
	awvium_wwite(awvium, WEG_BCWM_WWITE_HANDSHAKE_WW, 0, &wet);
	if (wet) {
		dev_eww(dev, "Faiw to weset hshake weg\n");
		wetuwn wet;
	}

	/* poww handshake bit since bit0 = 0 */
	wead_poww_timeout(awvium_wead, hshake_bit,
			  ((hshake_bit & BCWM_HANDSHAKE_W_DONE_EN_BIT) == 0),
			  15000, 45000, twue,
			  awvium, WEG_BCWM_WWITE_HANDSHAKE_WW,
			  &hshake_bit, &wet);
	if (wet) {
		dev_eww(dev, "poww bit[0] = 0, hshake weg faiw\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_get_bcwm_vews(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	u64 min, maj;
	int wet = 0;

	wet = awvium_wead(awvium, WEG_BCWM_MINOW_VEWSION_W, &min, &wet);
	wet = awvium_wead(awvium, WEG_BCWM_MAJOW_VEWSION_W, &maj, &wet);
	if (wet)
		wetuwn wet;

	dev_info(dev, "bcwm vewsion: %wwu.%wwu\n", min, maj);

	wetuwn 0;
}

static int awvium_get_fw_vewsion(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	u64 spec, maj, min, pat;
	int wet = 0;

	wet = awvium_wead(awvium, WEG_BCWM_DEVICE_FW_SPEC_VEWSION_W,
			  &spec, &wet);
	wet = awvium_wead(awvium, WEG_BCWM_DEVICE_FW_MAJOW_VEWSION_W,
			  &maj, &wet);
	wet = awvium_wead(awvium, WEG_BCWM_DEVICE_FW_MINOW_VEWSION_W,
			  &min, &wet);
	wet = awvium_wead(awvium, WEG_BCWM_DEVICE_FW_PATCH_VEWSION_W,
			  &pat, &wet);
	if (wet)
		wetuwn wet;

	dev_info(dev, "fw vewsion: %wwu.%wwu.%wwu.%wwu\n", spec, maj, min, pat);

	wetuwn 0;
}

static int awvium_get_bcwm_addw(stwuct awvium_dev *awvium)
{
	u64 vaw;
	int wet;

	wet = awvium_wead(awvium, WEG_BCWM_WEG_ADDW_W, &vaw, NUWW);
	if (wet)
		wetuwn wet;

	awvium->bcwm_addw = vaw;

	wetuwn 0;
}

static int awvium_is_awive(stwuct awvium_dev *awvium)
{
	u64 bcwm, hbeat;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_MINOW_VEWSION_W, &bcwm, &wet);
	awvium_wead(awvium, WEG_BCWM_HEAWTBEAT_WW, &hbeat, &wet);
	if (wet)
		wetuwn wet;

	wetuwn hbeat;
}

static void awvium_pwint_avaiw_mipi_fmt(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;

	dev_dbg(dev, "avaiw mipi_fmt yuv420_8_weg: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_8_WEG]);
	dev_dbg(dev, "avaiw mipi_fmt yuv420_8: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_8]);
	dev_dbg(dev, "avaiw mipi_fmt yuv420_10: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_10]);
	dev_dbg(dev, "avaiw mipi_fmt yuv420_8_csps: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_8_CSPS]);
	dev_dbg(dev, "avaiw mipi_fmt yuv420_10_csps: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_10_CSPS]);
	dev_dbg(dev, "avaiw mipi_fmt yuv422_8: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV422_8]);
	dev_dbg(dev, "avaiw mipi_fmt yuv422_10: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV422_10]);
	dev_dbg(dev, "avaiw mipi_fmt wgb888: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB888]);
	dev_dbg(dev, "avaiw mipi_fmt wgb666: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB666]);
	dev_dbg(dev, "avaiw mipi_fmt wgb565: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB565]);
	dev_dbg(dev, "avaiw mipi_fmt wgb555: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB555]);
	dev_dbg(dev, "avaiw mipi_fmt wgb444: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB444]);
	dev_dbg(dev, "avaiw mipi_fmt waw6: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW6]);
	dev_dbg(dev, "avaiw mipi_fmt waw7: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW7]);
	dev_dbg(dev, "avaiw mipi_fmt waw8: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW8]);
	dev_dbg(dev, "avaiw mipi_fmt waw10: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW10]);
	dev_dbg(dev, "avaiw mipi_fmt waw12: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW12]);
	dev_dbg(dev, "avaiw mipi_fmt waw14: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW14]);
	dev_dbg(dev, "avaiw mipi_fmt jpeg: %u\n",
		awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_JPEG]);
}

static void awvium_pwint_avaiw_feat(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;

	dev_dbg(dev, "featuwe wev_x: %u\n", awvium->avaiw_ft.wev_x);
	dev_dbg(dev, "featuwe wev_y: %u\n", awvium->avaiw_ft.wev_y);
	dev_dbg(dev, "featuwe int_autop: %u\n", awvium->avaiw_ft.int_autop);
	dev_dbg(dev, "featuwe bwack_wvw: %u\n", awvium->avaiw_ft.bwack_wvw);
	dev_dbg(dev, "featuwe gain: %u\n", awvium->avaiw_ft.gain);
	dev_dbg(dev, "featuwe gamma: %u\n", awvium->avaiw_ft.gamma);
	dev_dbg(dev, "featuwe contwast: %u\n", awvium->avaiw_ft.contwast);
	dev_dbg(dev, "featuwe sat: %u\n", awvium->avaiw_ft.sat);
	dev_dbg(dev, "featuwe hue: %u\n", awvium->avaiw_ft.hue);
	dev_dbg(dev, "featuwe whiteb: %u\n", awvium->avaiw_ft.whiteb);
	dev_dbg(dev, "featuwe shawp: %u\n", awvium->avaiw_ft.shawp);
	dev_dbg(dev, "featuwe auto_exp: %u\n", awvium->avaiw_ft.auto_exp);
	dev_dbg(dev, "featuwe auto_gain: %u\n", awvium->avaiw_ft.auto_gain);
	dev_dbg(dev, "featuwe auto_whiteb: %u\n", awvium->avaiw_ft.auto_whiteb);
	dev_dbg(dev, "featuwe dev_temp: %u\n", awvium->avaiw_ft.dev_temp);
	dev_dbg(dev, "featuwe acq_abowt: %u\n", awvium->avaiw_ft.acq_abowt);
	dev_dbg(dev, "featuwe acq_fw: %u\n", awvium->avaiw_ft.acq_fw);
	dev_dbg(dev, "featuwe fw_twiggew: %u\n", awvium->avaiw_ft.fw_twiggew);
	dev_dbg(dev, "featuwe exp_acq_wine: %u\n",
		awvium->avaiw_ft.exp_acq_wine);
}

static void awvium_pwint_avaiw_bayew(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;

	dev_dbg(dev, "avaiw bayew mono: %u\n",
		awvium->is_bay_avaiw[AWVIUM_BIT_BAY_MONO]);
	dev_dbg(dev, "avaiw bayew gw: %u\n",
		awvium->is_bay_avaiw[AWVIUM_BIT_BAY_GW]);
	dev_dbg(dev, "avaiw bayew wg: %u\n",
		awvium->is_bay_avaiw[AWVIUM_BIT_BAY_WG]);
	dev_dbg(dev, "avaiw bayew gb: %u\n",
		awvium->is_bay_avaiw[AWVIUM_BIT_BAY_GB]);
	dev_dbg(dev, "avaiw bayew bg: %u\n",
		awvium->is_bay_avaiw[AWVIUM_BIT_BAY_BG]);
}

static int awvium_get_feat_inq(stwuct awvium_dev *awvium)
{
	stwuct awvium_avaiw_feat *f;
	u64 vaw;
	int wet;

	wet = awvium_wead(awvium, WEG_BCWM_FEATUWE_INQUIWY_W, &vaw, NUWW);
	if (wet)
		wetuwn wet;

	f = (stwuct awvium_avaiw_feat *)&vaw;
	awvium->avaiw_ft = *f;
	awvium_pwint_avaiw_feat(awvium);

	wetuwn 0;
}

static int awvium_get_host_supp_csi_wanes(stwuct awvium_dev *awvium)
{
	u64 vaw;
	int wet;

	wet = awvium_wead(awvium, WEG_BCWM_CSI2_WANE_COUNT_WW, &vaw, NUWW);
	if (wet)
		wetuwn wet;

	awvium->h_sup_csi_wanes = vaw;

	wetuwn 0;
}

static int awvium_set_csi_wanes(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	u64 num_wanes;
	int wet;

	num_wanes = awvium->ep.bus.mipi_csi2.num_data_wanes;

	if (num_wanes > awvium->h_sup_csi_wanes)
		wetuwn -EINVAW;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_CSI2_WANE_COUNT_WW,
				  num_wanes);
	if (wet) {
		dev_eww(dev, "Faiw to set csi wanes weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_wp2hs_deway(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet = 0;

	/*
	 * The puwpose of this weg is fowce a DPhy weset
	 * fow the pewiod descwibed by the miwwisecond on
	 * the weg, befowe it stawts stweaming.
	 *
	 * To be cweaw, with that vawue biggew than 0 the
	 * Awvium fowces a dphy-weset on aww wanes fow that pewiod.
	 * That means aww wanes go up into wow powew state.
	 *
	 */
	awvium_wwite(awvium, WEG_BCWM_WP2HS_DEWAY_WW,
		     AWVIUM_WP2HS_DEWAY_MS, &wet);
	if (wet) {
		dev_eww(dev, "Faiw to set wp2hs deway weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_get_csi_cwk_pawams(stwuct awvium_dev *awvium)
{
	u64 min_csi_cwk, max_csi_cwk;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_CSI2_CWOCK_MIN_W, &min_csi_cwk, &wet);
	awvium_wead(awvium, WEG_BCWM_CSI2_CWOCK_MAX_W, &max_csi_cwk, &wet);
	if (wet)
		wetuwn wet;

	awvium->min_csi_cwk = min_csi_cwk;
	awvium->max_csi_cwk = max_csi_cwk;

	wetuwn 0;
}

static int awvium_set_csi_cwk(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	u64 csi_cwk;
	int wet;

	csi_cwk = cwamp(awvium->ep.wink_fwequencies[0],
			(u64)awvium->min_csi_cwk, (u64)awvium->max_csi_cwk);

	if (awvium->ep.wink_fwequencies[0] != (u64)csi_cwk) {
		dev_wawn(dev,
			 "wequested csi cwock (%wwu MHz) out of wange [%u, %u] Adjusted to %wwu\n",
			 awvium->ep.wink_fwequencies[0],
			 awvium->min_csi_cwk, awvium->max_csi_cwk, csi_cwk);
	}

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_CSI2_CWOCK_WW, csi_cwk);
	if (wet) {
		dev_eww(dev, "Faiw to set csi cwock weg\n");
		wetuwn wet;
	}

	awvium->wink_fweq = csi_cwk;

	wetuwn 0;
}

static int awvium_get_img_width_pawams(stwuct awvium_dev *awvium)
{
	u64 imgw, imgw_min, imgw_max, imgw_inc;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_IMG_WIDTH_WW, &imgw, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_WIDTH_MIN_W, &imgw_min, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_WIDTH_MAX_W, &imgw_max, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_WIDTH_INC_W, &imgw_inc, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_img_width = imgw;
	awvium->img_min_width = imgw_min;
	awvium->img_max_width = imgw_max;
	awvium->img_inc_width = imgw_inc;

	wetuwn 0;
}

static int awvium_get_img_height_pawams(stwuct awvium_dev *awvium)
{
	u64 imgh, imgh_min, imgh_max, imgh_inc;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_IMG_HEIGHT_WW, &imgh, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_HEIGHT_MIN_W, &imgh_min, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_HEIGHT_MAX_W, &imgh_max, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_HEIGHT_INC_W, &imgh_inc, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_img_height = imgh;
	awvium->img_min_height = imgh_min;
	awvium->img_max_height = imgh_max;
	awvium->img_inc_height = imgh_inc;

	wetuwn 0;
}

static int awvium_set_img_width(stwuct awvium_dev *awvium, u32 width)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_IMG_WIDTH_WW, width);
	if (wet) {
		dev_eww(dev, "Faiw to set img width\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_img_height(stwuct awvium_dev *awvium, u32 height)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_IMG_HEIGHT_WW, height);
	if (wet) {
		dev_eww(dev, "Faiw to set img height\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_img_offx(stwuct awvium_dev *awvium, u32 offx)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_IMG_OFFSET_X_WW, offx);
	if (wet) {
		dev_eww(dev, "Faiw to set img offx\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_img_offy(stwuct awvium_dev *awvium, u32 offy)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_IMG_OFFSET_Y_WW, offy);
	if (wet) {
		dev_eww(dev, "Faiw to set img offy\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_get_offx_pawams(stwuct awvium_dev *awvium)
{
	u64 min_offx, max_offx, inc_offx;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_IMG_OFFSET_X_MIN_W, &min_offx, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_OFFSET_X_MAX_W, &max_offx, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_OFFSET_X_INC_W, &inc_offx, &wet);
	if (wet)
		wetuwn wet;

	awvium->min_offx = min_offx;
	awvium->max_offx = max_offx;
	awvium->inc_offx = inc_offx;

	wetuwn 0;
}

static int awvium_get_offy_pawams(stwuct awvium_dev *awvium)
{
	u64 min_offy, max_offy, inc_offy;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_IMG_OFFSET_Y_MIN_W, &min_offy, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_OFFSET_Y_MAX_W, &max_offy, &wet);
	awvium_wead(awvium, WEG_BCWM_IMG_OFFSET_Y_INC_W, &inc_offy, &wet);
	if (wet)
		wetuwn wet;

	awvium->min_offy = min_offy;
	awvium->max_offy = max_offy;
	awvium->inc_offy = inc_offy;

	wetuwn 0;
}

static int awvium_get_gain_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_gain, min_gain, max_gain, inc_gain;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_GAIN_WW, &dft_gain, &wet);
	awvium_wead(awvium, WEG_BCWM_GAIN_MIN_W, &min_gain, &wet);
	awvium_wead(awvium, WEG_BCWM_GAIN_MAX_W, &max_gain, &wet);
	awvium_wead(awvium, WEG_BCWM_GAIN_INC_W, &inc_gain, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_gain = dft_gain;
	awvium->min_gain = min_gain;
	awvium->max_gain = max_gain;
	awvium->inc_gain = inc_gain;

	wetuwn 0;
}

static int awvium_get_exposuwe_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_exp, min_exp, max_exp, inc_exp;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_EXPOSUWE_TIME_WW, &dft_exp, &wet);
	awvium_wead(awvium, WEG_BCWM_EXPOSUWE_TIME_MIN_W, &min_exp, &wet);
	awvium_wead(awvium, WEG_BCWM_EXPOSUWE_TIME_MAX_W, &max_exp, &wet);
	awvium_wead(awvium, WEG_BCWM_EXPOSUWE_TIME_INC_W, &inc_exp, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_exp = dft_exp;
	awvium->min_exp = min_exp;
	awvium->max_exp = max_exp;
	awvium->inc_exp = inc_exp;

	wetuwn 0;
}

static int awvium_get_wed_bawance_watio_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_wb, min_wb, max_wb, inc_wb;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_WED_BAWANCE_WATIO_WW, &dft_wb, &wet);
	awvium_wead(awvium, WEG_BCWM_WED_BAWANCE_WATIO_MIN_W, &min_wb, &wet);
	awvium_wead(awvium, WEG_BCWM_WED_BAWANCE_WATIO_MAX_W, &max_wb, &wet);
	awvium_wead(awvium, WEG_BCWM_WED_BAWANCE_WATIO_INC_W, &inc_wb, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_wbawance = dft_wb;
	awvium->min_wbawance = min_wb;
	awvium->max_wbawance = max_wb;
	awvium->inc_wbawance = inc_wb;

	wetuwn 0;
}

static int awvium_get_bwue_bawance_watio_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_bb, min_bb, max_bb, inc_bb;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_BWUE_BAWANCE_WATIO_WW, &dft_bb, &wet);
	awvium_wead(awvium, WEG_BCWM_BWUE_BAWANCE_WATIO_MIN_W, &min_bb, &wet);
	awvium_wead(awvium, WEG_BCWM_BWUE_BAWANCE_WATIO_MAX_W, &max_bb, &wet);
	awvium_wead(awvium, WEG_BCWM_BWUE_BAWANCE_WATIO_INC_W, &inc_bb, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_bbawance = dft_bb;
	awvium->min_bbawance = min_bb;
	awvium->max_bbawance = max_bb;
	awvium->inc_bbawance = inc_bb;

	wetuwn 0;
}

static int awvium_get_hue_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_hue, min_hue, max_hue, inc_hue;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_HUE_WW, &dft_hue, &wet);
	awvium_wead(awvium, WEG_BCWM_HUE_MIN_W, &min_hue, &wet);
	awvium_wead(awvium, WEG_BCWM_HUE_MAX_W, &max_hue, &wet);
	awvium_wead(awvium, WEG_BCWM_HUE_INC_W, &inc_hue, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_hue = (s32)dft_hue;
	awvium->min_hue = (s32)min_hue;
	awvium->max_hue = (s32)max_hue;
	awvium->inc_hue = (s32)inc_hue;

	wetuwn 0;
}

static int awvium_get_bwack_wvw_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_bwvw, min_bwvw, max_bwvw, inc_bwvw;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_BWACK_WEVEW_WW, &dft_bwvw, &wet);
	awvium_wead(awvium, WEG_BCWM_BWACK_WEVEW_MIN_W, &min_bwvw, &wet);
	awvium_wead(awvium, WEG_BCWM_BWACK_WEVEW_MAX_W, &max_bwvw, &wet);
	awvium_wead(awvium, WEG_BCWM_BWACK_WEVEW_INC_W, &inc_bwvw, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_bwack_wvw = (s32)dft_bwvw;
	awvium->min_bwack_wvw = (s32)min_bwvw;
	awvium->max_bwack_wvw = (s32)max_bwvw;
	awvium->inc_bwack_wvw = (s32)inc_bwvw;

	wetuwn 0;
}

static int awvium_get_gamma_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_g, min_g, max_g, inc_g;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_GAMMA_WW, &dft_g, &wet);
	awvium_wead(awvium, WEG_BCWM_GAMMA_MIN_W, &min_g, &wet);
	awvium_wead(awvium, WEG_BCWM_GAMMA_MAX_W, &max_g, &wet);
	awvium_wead(awvium, WEG_BCWM_GAMMA_INC_W, &inc_g, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_gamma = dft_g;
	awvium->min_gamma = min_g;
	awvium->max_gamma = max_g;
	awvium->inc_gamma = inc_g;

	wetuwn 0;
}

static int awvium_get_shawpness_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_sh, min_sh, max_sh, inc_sh;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_SHAWPNESS_WW, &dft_sh, &wet);
	awvium_wead(awvium, WEG_BCWM_SHAWPNESS_MIN_W, &min_sh, &wet);
	awvium_wead(awvium, WEG_BCWM_BWACK_WEVEW_MAX_W, &max_sh, &wet);
	awvium_wead(awvium, WEG_BCWM_SHAWPNESS_INC_W, &inc_sh, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_shawp = (s32)dft_sh;
	awvium->min_shawp = (s32)min_sh;
	awvium->max_shawp = (s32)max_sh;
	awvium->inc_shawp = (s32)inc_sh;

	wetuwn 0;
}

static int awvium_get_contwast_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_c, min_c, max_c, inc_c;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_CONTWAST_VAWUE_WW, &dft_c, &wet);
	awvium_wead(awvium, WEG_BCWM_CONTWAST_VAWUE_MIN_W, &min_c, &wet);
	awvium_wead(awvium, WEG_BCWM_CONTWAST_VAWUE_MAX_W, &max_c, &wet);
	awvium_wead(awvium, WEG_BCWM_CONTWAST_VAWUE_INC_W, &inc_c, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_contwast = dft_c;
	awvium->min_contwast = min_c;
	awvium->max_contwast = max_c;
	awvium->inc_contwast = inc_c;

	wetuwn 0;
}

static int awvium_get_satuwation_pawams(stwuct awvium_dev *awvium)
{
	u64 dft_sat, min_sat, max_sat, inc_sat;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_SATUWATION_WW, &dft_sat, &wet);
	awvium_wead(awvium, WEG_BCWM_SATUWATION_MIN_W, &min_sat, &wet);
	awvium_wead(awvium, WEG_BCWM_SATUWATION_MAX_W, &max_sat, &wet);
	awvium_wead(awvium, WEG_BCWM_SATUWATION_INC_W, &inc_sat, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_sat = dft_sat;
	awvium->min_sat = min_sat;
	awvium->max_sat = max_sat;
	awvium->inc_sat = inc_sat;

	wetuwn 0;
}

static int awvium_set_bcm_mode(stwuct awvium_dev *awvium)
{
	int wet = 0;

	awvium_wwite(awvium, WEG_GENCP_CHANGEMODE_W, AWVIUM_BCM_MODE, &wet);
	awvium->bcwm_mode = AWVIUM_BCM_MODE;

	wetuwn wet;
}

static int awvium_get_mode(stwuct awvium_dev *awvium)
{
	u64 bcwm_mode;
	int wet;

	wet = awvium_wead(awvium, WEG_GENCP_CUWWENTMODE_W, &bcwm_mode, NUWW);
	if (wet)
		wetuwn wet;

	switch (bcwm_mode) {
	case AWVIUM_BCM_MODE:
		awvium->bcwm_mode = AWVIUM_BCM_MODE;
		bweak;
	case AWVIUM_GENCP_MODE:
		awvium->bcwm_mode = AWVIUM_GENCP_MODE;
		bweak;
	}

	wetuwn 0;
}

static int awvium_get_avaiw_mipi_data_fowmat(stwuct awvium_dev *awvium)
{
	stwuct awvium_avaiw_mipi_fmt *avaiw_fmt;
	u64 vaw;
	int wet;

	wet = awvium_wead(awvium, WEG_BCWM_IMG_AVAIWABWE_MIPI_DATA_FOWMATS_W,
			  &vaw, NUWW);
	if (wet)
		wetuwn wet;

	avaiw_fmt = (stwuct awvium_avaiw_mipi_fmt *)&vaw;

	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_8_WEG] =
				  avaiw_fmt->yuv420_8_weg;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_8] =
				  avaiw_fmt->yuv420_8;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_10] =
				  avaiw_fmt->yuv420_10;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_8_CSPS] =
				  avaiw_fmt->yuv420_8_csps;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV420_10_CSPS] =
				  avaiw_fmt->yuv420_10_csps;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV422_8] =
				  avaiw_fmt->yuv422_8;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_YUV422_10] =
				  avaiw_fmt->yuv422_10;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB888] =
				  avaiw_fmt->wgb888;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB666] =
				  avaiw_fmt->wgb666;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB565] =
				  avaiw_fmt->wgb565;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB555] =
				  avaiw_fmt->wgb555;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WGB444] =
				  avaiw_fmt->wgb444;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW6] =
				  avaiw_fmt->waw6;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW7] =
				  avaiw_fmt->waw7;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW8] =
				  avaiw_fmt->waw8;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW10] =
				  avaiw_fmt->waw10;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW12] =
				  avaiw_fmt->waw12;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_WAW14] =
				  avaiw_fmt->waw14;
	awvium->is_mipi_fmt_avaiw[AWVIUM_BIT_JPEG] =
				  avaiw_fmt->jpeg;

	awvium_pwint_avaiw_mipi_fmt(awvium);

	wetuwn 0;
}

static int awvium_setup_mipi_fmt(stwuct awvium_dev *awvium)
{
	unsigned int avaiw_fmt_cnt = 0;
	unsigned int fmt = 0;
	size_t sz = 0;

	/* cawcuwate fmt awway size */
	fow (fmt = 0; fmt < AWVIUM_NUM_SUPP_MIPI_DATA_FMT; fmt++) {
		if (!awvium->is_mipi_fmt_avaiw[awvium_csi2_fmts[fmt].fmt_av_bit])
			continue;

		if (!awvium_csi2_fmts[fmt].is_waw ||
		    awvium->is_bay_avaiw[awvium_csi2_fmts[fmt].bay_av_bit])
			sz++;
	}

	/* init awvium_csi2_fmt awway */
	awvium->awvium_csi2_fmt_n = sz;
	awvium->awvium_csi2_fmt =
		kmawwoc_awway(sz, sizeof(stwuct awvium_pixfmt), GFP_KEWNEW);
	if (!awvium->awvium_csi2_fmt)
		wetuwn -ENOMEM;

	/* Cweate the awvium_csi2 fmt awway fwom fowmats avaiwabwe */
	fow (fmt = 0; fmt < AWVIUM_NUM_SUPP_MIPI_DATA_FMT; fmt++) {
		if (!awvium->is_mipi_fmt_avaiw[awvium_csi2_fmts[fmt].fmt_av_bit])
			continue;

		if (!awvium_csi2_fmts[fmt].is_waw ||
		    awvium->is_bay_avaiw[awvium_csi2_fmts[fmt].bay_av_bit]) {
			awvium->awvium_csi2_fmt[avaiw_fmt_cnt] =
				awvium_csi2_fmts[fmt];
			avaiw_fmt_cnt++;
		}
	}

	wetuwn 0;
}

static int awvium_set_mipi_fmt(stwuct awvium_dev *awvium,
			       const stwuct awvium_pixfmt *pixfmt)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_IMG_MIPI_DATA_FOWMAT_WW,
				  pixfmt->mipi_fmt_wegvaw);
	if (wet) {
		dev_eww(dev, "Faiw to set mipi fmt\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_get_avaiw_bayew(stwuct awvium_dev *awvium)
{
	stwuct awvium_avaiw_bayew *avaiw_bay;
	u64 vaw;
	int wet;

	wet = awvium_wead(awvium, WEG_BCWM_IMG_BAYEW_PATTEWN_INQUIWY_W,
			  &vaw, NUWW);
	if (wet)
		wetuwn wet;

	avaiw_bay = (stwuct awvium_avaiw_bayew *)&vaw;

	awvium->is_bay_avaiw[AWVIUM_BIT_BAY_MONO] = avaiw_bay->mono;
	awvium->is_bay_avaiw[AWVIUM_BIT_BAY_GW] = avaiw_bay->gw;
	awvium->is_bay_avaiw[AWVIUM_BIT_BAY_WG] = avaiw_bay->wg;
	awvium->is_bay_avaiw[AWVIUM_BIT_BAY_GB] = avaiw_bay->gb;
	awvium->is_bay_avaiw[AWVIUM_BIT_BAY_BG] = avaiw_bay->bg;

	awvium_pwint_avaiw_bayew(awvium);

	wetuwn 0;
}

static int awvium_set_bayew_pattewn(stwuct awvium_dev *awvium,
				    const stwuct awvium_pixfmt *pixfmt)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_IMG_BAYEW_PATTEWN_WW,
				  pixfmt->bay_fmt_wegvaw);
	if (wet) {
		dev_eww(dev, "Faiw to set bayew pattewn\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_get_fwame_intewvaw(stwuct awvium_dev *awvium)
{
	u64 dft_fw, min_fw, max_fw;
	int wet = 0;

	awvium_wead(awvium, WEG_BCWM_ACQUISITION_FWAME_WATE_WW,
		    &dft_fw, &wet);
	awvium_wead(awvium, WEG_BCWM_ACQUISITION_FWAME_WATE_MIN_W,
		    &min_fw, &wet);
	awvium_wead(awvium, WEG_BCWM_ACQUISITION_FWAME_WATE_MAX_W,
		    &max_fw, &wet);
	if (wet)
		wetuwn wet;

	awvium->dft_fw = dft_fw;
	awvium->min_fw = min_fw;
	awvium->max_fw = max_fw;

	wetuwn 0;
}

static int awvium_set_fwame_wate(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_ACQUISITION_FWAME_WATE_WW,
				  awvium->fw);
	if (wet) {
		dev_eww(dev, "Faiw to set fwame wate wanes weg\n");
		wetuwn wet;
	}

	dev_dbg(dev, "set fwame wate: %wwu us\n", awvium->fw);

	wetuwn 0;
}

static int awvium_set_stweam_mipi(stwuct awvium_dev *awvium, boow on)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, on ? WEG_BCWM_ACQUISITION_STAWT_WW :
				  WEG_BCWM_ACQUISITION_STOP_WW, 0x01);
	if (wet) {
		dev_eww(dev, "Faiw set_stweam_mipi\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_get_gain(stwuct awvium_dev *awvium)
{
	u64 gain;
	int wet;

	/* The unit is miwwibew (1 mB = 0.01 dB) */
	wet = awvium_wead(awvium, WEG_BCWM_GAIN_WW, &gain, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn gain;
}

static int awvium_set_ctww_gain(stwuct awvium_dev *awvium, int gain)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	/* The unit is miwwibew (1 mB = 0.01 dB) */
	wet = awvium_wwite_hshake(awvium, WEG_BCWM_GAIN_WW, (u64)gain);
	if (wet) {
		dev_eww(dev, "Faiw to set gain vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_auto_gain(stwuct awvium_dev *awvium, boow on)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_GAIN_AUTO_WW,
				  on ? 0x02 : 0x00);
	if (wet) {
		dev_eww(dev, "Faiw to set autogain weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_get_exposuwe(stwuct awvium_dev *awvium)
{
	u64 exp;
	int wet;

	/* Exposuwe time in ns */
	wet = awvium_wead(awvium, WEG_BCWM_EXPOSUWE_TIME_WW, &exp, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn exp;
}

static int awvium_set_ctww_auto_exposuwe(stwuct awvium_dev *awvium, boow on)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_WHITE_BAWANCE_AUTO_WW,
				  on ? 0x02 : 0x00);
	if (wet) {
		dev_eww(dev, "Faiw to set autoexposuwe weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_exposuwe(stwuct awvium_dev *awvium, int exposuwe_ns)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_EXPOSUWE_TIME_WW,
				  (u64)exposuwe_ns);
	if (wet) {
		dev_eww(dev, "Faiw to set exposuwe vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_bwue_bawance_watio(stwuct awvium_dev *awvium,
					      int bwue)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_BWUE_BAWANCE_WATIO_WW,
				  (u64)bwue);
	if (wet) {
		dev_eww(dev, "Faiw to set bwue watio vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_wed_bawance_watio(stwuct awvium_dev *awvium, int wed)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_WED_BAWANCE_WATIO_WW,
				  (u64)wed);
	if (wet) {
		dev_eww(dev, "Faiw to set wed watio vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_awb(stwuct awvium_dev *awvium, boow on)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_WHITE_BAWANCE_AUTO_WW,
				  on ? 0x02 : 0x00);
	if (wet) {
		dev_eww(dev, "Faiw to set awb weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_hue(stwuct awvium_dev *awvium, int vaw)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_HUE_WW, (u64)vaw);
	if (wet) {
		dev_eww(dev, "Faiw to set hue vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_contwast(stwuct awvium_dev *awvium, int vaw)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_CONTWAST_VAWUE_WW, (u64)vaw);
	if (wet) {
		dev_eww(dev, "Faiw to set contwast vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_satuwation(stwuct awvium_dev *awvium, int vaw)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_SATUWATION_WW, (u64)vaw);
	if (wet) {
		dev_eww(dev, "Faiw to set contwast vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_gamma(stwuct awvium_dev *awvium, int vaw)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_GAMMA_WW, (u64)vaw);
	if (wet) {
		dev_eww(dev, "Faiw to set gamma vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_shawpness(stwuct awvium_dev *awvium, int vaw)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_SHAWPNESS_WW, (u64)vaw);
	if (wet) {
		dev_eww(dev, "Faiw to set shawpness vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_hfwip(stwuct awvium_dev *awvium, int vaw)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_IMG_WEVEWSE_X_WW, (u64)vaw);
	if (wet) {
		dev_eww(dev, "Faiw to set wevewse_x vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_set_ctww_vfwip(stwuct awvium_dev *awvium, int vaw)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_wwite_hshake(awvium, WEG_BCWM_IMG_WEVEWSE_Y_WW, (u64)vaw);
	if (wet) {
		dev_eww(dev, "Faiw to set wevewse_y vawue weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_get_hw_featuwes_pawams(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_get_csi_cwk_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead min/max csi cwock wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_img_width_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead img width wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_img_height_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead img heigth wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_offx_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead offx wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_offy_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead offy wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_gain_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead gain wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_exposuwe_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead min/max exp wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_wed_bawance_watio_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead wed bawance watio wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_bwue_bawance_watio_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead bwue bawance watio wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_hue_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead hue wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_contwast_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead contwast wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_satuwation_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead satuwation wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_bwack_wvw_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead bwack wvw wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_gamma_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead gamma wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_shawpness_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead shawpness wegs\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_get_hw_info(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	wet = awvium_get_bcwm_vews(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead bcwm vewsion weg\n");
		wetuwn wet;
	}

	wet = awvium_get_bcwm_addw(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to bcwm addwess weg\n");
		wetuwn wet;
	}

	wet = awvium_get_fw_vewsion(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead fw vewsion weg\n");
		wetuwn wet;
	}

	wet = awvium_get_host_supp_csi_wanes(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead host suppowted csi wanes weg\n");
		wetuwn wet;
	}

	wet = awvium_get_feat_inq(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead bcwm featuwe inquiwy weg\n");
		wetuwn wet;
	}

	wet = awvium_get_hw_featuwes_pawams(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead featuwes pawams wegs\n");
		wetuwn wet;
	}

	wet = awvium_get_avaiw_mipi_data_fowmat(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead avaiwabwe mipi data fowmats weg\n");
		wetuwn wet;
	}

	wet = awvium_get_avaiw_bayew(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to wead avaiwabwe Bayew pattewns weg\n");
		wetuwn wet;
	}

	wet = awvium_get_mode(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to get cuwwent mode weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_hw_init(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	int wet;

	/* Set Awvium BCM mode*/
	wet = awvium_set_bcm_mode(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to set BCM mode\n");
		wetuwn wet;
	}

	wet = awvium_set_csi_wanes(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to set csi wanes\n");
		wetuwn wet;
	}

	wet = awvium_set_csi_cwk(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to set csi cwk\n");
		wetuwn wet;
	}

	wet = awvium_set_wp2hs_deway(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to set wp2hs weg\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/* --------------- Subdev Opewations --------------- */

static int awvium_g_fwame_intewvaw(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct awvium_dev *awvium = sd_to_awvium(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	fi->intewvaw = awvium->fwame_intewvaw;

	wetuwn 0;
}

static int awvium_set_fwame_intewvaw(stwuct awvium_dev *awvium,
				     stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	u64 weq_fw, min_fw, max_fw;
	int wet;

	if (fi->intewvaw.denominatow == 0)
		wetuwn -EINVAW;

	wet = awvium_get_fwame_intewvaw(awvium);
	if (wet) {
		dev_eww(dev, "Faiw to get fwame intewvaw\n");
		wetuwn wet;
	}

	min_fw = awvium->min_fw;
	max_fw = awvium->max_fw;

	dev_dbg(dev, "fi->intewvaw.numewatow = %d\n",
		fi->intewvaw.numewatow);
	dev_dbg(dev, "fi->intewvaw.denominatow = %d\n",
		fi->intewvaw.denominatow);

	weq_fw = (u64)((fi->intewvaw.denominatow * USEC_PEW_SEC) /
		       fi->intewvaw.numewatow);

	if (weq_fw >= max_fw && weq_fw <= min_fw)
		weq_fw = awvium->dft_fw;

	awvium->fw = weq_fw;
	awvium->fwame_intewvaw.numewatow = fi->intewvaw.numewatow;
	awvium->fwame_intewvaw.denominatow = fi->intewvaw.denominatow;

	wetuwn 0;
}

static int awvium_s_fwame_intewvaw(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct awvium_dev *awvium = sd_to_awvium(sd);
	int wet;

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	if (awvium->stweaming)
		wetuwn -EBUSY;

	wet = awvium_set_fwame_intewvaw(awvium, fi);
	if (!wet)
		wet = awvium_set_fwame_wate(awvium);

	wetuwn wet;
}

static int awvium_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct awvium_dev *awvium = sd_to_awvium(sd);

	if (code->index >= awvium->awvium_csi2_fmt_n)
		wetuwn -EINVAW;

	code->code = awvium->awvium_csi2_fmt[code->index].code;

	wetuwn 0;
}

static const stwuct awvium_pixfmt *
awvium_code_to_pixfmt(stwuct awvium_dev *awvium, u32 code)
{
	unsigned int i;

	fow (i = 0; awvium->awvium_csi2_fmt[i].code; ++i)
		if (awvium->awvium_csi2_fmt[i].code == code)
			wetuwn &awvium->awvium_csi2_fmt[i];

	wetuwn &awvium->awvium_csi2_fmt[0];
}

static int awvium_set_mode(stwuct awvium_dev *awvium,
			   stwuct v4w2_subdev_state *state)
{
	stwuct v4w2_mbus_fwamefmt *fmt;
	stwuct v4w2_wect *cwop;
	int wet;

	cwop = v4w2_subdev_state_get_cwop(state, 0);
	fmt = v4w2_subdev_state_get_fowmat(state, 0);

	v4w_bound_awign_image(&fmt->width, awvium->img_min_width,
			      awvium->img_max_width, 0,
			      &fmt->height, awvium->img_min_height,
			      awvium->img_max_height, 0, 0);

	/* awvium don't accept negative cwop weft/top */
	cwop->weft = cwamp((u32)max(0, cwop->weft), awvium->min_offx,
			   (u32)(awvium->img_max_width - fmt->width));
	cwop->top = cwamp((u32)max(0, cwop->top), awvium->min_offy,
			  (u32)(awvium->img_max_height - fmt->height));

	wet = awvium_set_img_width(awvium, fmt->width);
	if (wet)
		wetuwn wet;

	wet = awvium_set_img_height(awvium, fmt->height);
	if (wet)
		wetuwn wet;

	wet = awvium_set_img_offx(awvium, cwop->weft);
	if (wet)
		wetuwn wet;

	wet = awvium_set_img_offy(awvium, cwop->top);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int awvium_set_fwamefmt(stwuct awvium_dev *awvium,
			       stwuct v4w2_mbus_fwamefmt *fowmat)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	const stwuct awvium_pixfmt *awvium_csi2_fmt;
	int wet = 0;

	awvium_csi2_fmt = awvium_code_to_pixfmt(awvium, fowmat->code);

	wet = awvium_set_mipi_fmt(awvium, awvium_csi2_fmt);
	if (wet)
		wetuwn wet;

	if (awvium_csi2_fmt->is_waw) {
		wet = awvium_set_bayew_pattewn(awvium, awvium_csi2_fmt);
		if (wet)
			wetuwn wet;
	}

	dev_dbg(dev, "stawt: %s, mipi_fmt_wegvaw wegvaw = 0x%wwx",
		__func__, awvium_csi2_fmt->mipi_fmt_wegvaw);

	wetuwn wet;
}

static int awvium_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct awvium_dev *awvium = sd_to_awvium(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&awvium->sd);
	stwuct v4w2_mbus_fwamefmt *fmt;
	stwuct v4w2_subdev_state *state;
	int wet = 0;

	state = v4w2_subdev_wock_and_get_active_state(sd);

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(&cwient->dev);
		if (wet < 0)
			goto out;

		wet = __v4w2_ctww_handwew_setup(&awvium->ctwws.handwew);
		if (wet)
			goto out;

		wet = awvium_set_mode(awvium, state);
		if (wet)
			goto out;

		fmt = v4w2_subdev_state_get_fowmat(state, 0);
		wet = awvium_set_fwamefmt(awvium, fmt);
		if (wet)
			goto out;

		wet = awvium_set_stweam_mipi(awvium, enabwe);
		if (wet)
			goto out;

	} ewse {
		awvium_set_stweam_mipi(awvium, enabwe);
		pm_wuntime_mawk_wast_busy(&cwient->dev);
		pm_wuntime_put_autosuspend(&cwient->dev);
	}

	awvium->stweaming = !!enabwe;
	v4w2_subdev_unwock_state(state);

	wetuwn 0;

out:
	pm_wuntime_put(&cwient->dev);
	v4w2_subdev_unwock_state(state);
	wetuwn wet;
}

static int awvium_init_state(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *state)
{
	stwuct awvium_dev *awvium = sd_to_awvium(sd);
	stwuct awvium_mode *mode = &awvium->mode;
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
		.fowmat = awvium_csi2_defauwt_fmt,
	};
	stwuct v4w2_subdev_cwop sd_cwop = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
		.wect = {
			.weft = mode->cwop.weft,
			.top = mode->cwop.top,
			.width = mode->cwop.width,
			.height = mode->cwop.height,
		},
	};

	*v4w2_subdev_state_get_cwop(state, 0) = sd_cwop.wect;
	*v4w2_subdev_state_get_fowmat(state, 0) = sd_fmt.fowmat;

	wetuwn 0;
}

static int awvium_set_fmt(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct awvium_dev *awvium = sd_to_awvium(sd);
	const stwuct awvium_pixfmt *awvium_csi2_fmt;
	stwuct v4w2_mbus_fwamefmt *fmt;
	stwuct v4w2_wect *cwop;

	fmt = v4w2_subdev_state_get_fowmat(sd_state, 0);
	cwop = v4w2_subdev_state_get_cwop(sd_state, 0);

	v4w_bound_awign_image(&fowmat->fowmat.width, awvium->img_min_width,
			      awvium->img_max_width, 0,
			      &fowmat->fowmat.height, awvium->img_min_height,
			      awvium->img_max_height, 0, 0);

	/* Adjust weft and top to pwevent woww ovew sensow awea */
	cwop->weft = cwamp((u32)cwop->weft, (u32)0,
			   (awvium->img_max_width - fmt->width));
	cwop->top = cwamp((u32)cwop->top, (u32)0,
			  (awvium->img_max_height - fmt->height));

	/* Set awso the cwop width and height when set a new fmt */
	cwop->width = fmt->width;
	cwop->height = fmt->height;

	awvium_csi2_fmt = awvium_code_to_pixfmt(awvium, fowmat->fowmat.code);
	fmt->code = awvium_csi2_fmt->code;

	*fmt = fowmat->fowmat;

	wetuwn 0;
}

static int awvium_set_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	stwuct awvium_dev *awvium = sd_to_awvium(sd);
	stwuct v4w2_mbus_fwamefmt *fmt;
	stwuct v4w2_wect *cwop;

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	cwop = v4w2_subdev_state_get_cwop(sd_state, 0);
	fmt = v4w2_subdev_state_get_fowmat(sd_state, 0);

	/*
	 * Awvium can onwy shift the owigin of the img
	 * then we accept onwy vawue with the same vawue of the actuaw fmt
	 */
	if (sew->w.width != fmt->width)
		sew->w.width = fmt->width;

	if (sew->w.height != fmt->height)
		sew->w.height = fmt->height;

	/* awvium don't accept negative cwop weft/top */
	cwop->weft = cwamp((u32)max(0, sew->w.weft), awvium->min_offx,
			   awvium->img_max_width - sew->w.width);
	cwop->top = cwamp((u32)max(0, sew->w.top), awvium->min_offy,
			  awvium->img_max_height - sew->w.height);

	sew->w = *cwop;

	wetuwn 0;
}

static int awvium_get_sewection(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_sewection *sew)
{
	stwuct awvium_dev *awvium = sd_to_awvium(sd);

	switch (sew->tawget) {
	/* Cuwwent cwopping awea */
	case V4W2_SEW_TGT_CWOP:
		sew->w = *v4w2_subdev_state_get_cwop(sd_state, 0);
		bweak;
	/* Cwopping bounds */
	case V4W2_SEW_TGT_NATIVE_SIZE:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = awvium->img_max_width;
		sew->w.height = awvium->img_max_height;
		bweak;
	/* Defauwt cwopping awea */
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		sew->w.top = awvium->min_offy;
		sew->w.weft = awvium->min_offx;
		sew->w.width = awvium->img_max_width;
		sew->w.height = awvium->img_max_height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int awvium_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = ctww_to_sd(ctww);
	stwuct awvium_dev *awvium = sd_to_awvium(sd);
	int vaw;

	switch (ctww->id) {
	case V4W2_CID_GAIN:
		vaw = awvium_get_gain(awvium);
		if (vaw < 0)
			wetuwn vaw;
		awvium->ctwws.gain->vaw = vaw;
		bweak;
	case V4W2_CID_EXPOSUWE:
		vaw = awvium_get_exposuwe(awvium);
		if (vaw < 0)
			wetuwn vaw;
		awvium->ctwws.exposuwe->vaw = vaw;
		bweak;
	}

	wetuwn 0;
}

static int awvium_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = ctww_to_sd(ctww);
	stwuct awvium_dev *awvium = sd_to_awvium(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&awvium->sd);
	int wet;

	/*
	 * Appwying V4W2 contwow vawue onwy happens
	 * when powew is up fow stweaming
	 */
	if (!pm_wuntime_get_if_in_use(&cwient->dev))
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_GAIN:
		wet = awvium_set_ctww_gain(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_AUTOGAIN:
		wet = awvium_set_ctww_auto_gain(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		wet = awvium_set_ctww_exposuwe(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE_AUTO:
		wet = awvium_set_ctww_auto_exposuwe(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_WED_BAWANCE:
		wet = awvium_set_ctww_wed_bawance_watio(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_BWUE_BAWANCE:
		wet = awvium_set_ctww_bwue_bawance_watio(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		wet = awvium_set_ctww_awb(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_HUE:
		wet = awvium_set_ctww_hue(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_CONTWAST:
		wet = awvium_set_ctww_contwast(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_SATUWATION:
		wet = awvium_set_ctww_satuwation(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_GAMMA:
		wet = awvium_set_ctww_gamma(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_SHAWPNESS:
		wet = awvium_set_ctww_shawpness(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_HFWIP:
		wet = awvium_set_ctww_hfwip(awvium, ctww->vaw);
		bweak;
	case V4W2_CID_VFWIP:
		wet = awvium_set_ctww_vfwip(awvium, ctww->vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	pm_wuntime_put(&cwient->dev);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops awvium_ctww_ops = {
	.g_vowatiwe_ctww = awvium_g_vowatiwe_ctww,
	.s_ctww = awvium_s_ctww,
};

static int awvium_ctww_init(stwuct awvium_dev *awvium)
{
	const stwuct v4w2_ctww_ops *ops = &awvium_ctww_ops;
	stwuct awvium_ctwws *ctwws = &awvium->ctwws;
	stwuct v4w2_ctww_handwew *hdw = &ctwws->handwew;
	stwuct v4w2_fwnode_device_pwopewties pwops;
	int wet;

	v4w2_ctww_handwew_init(hdw, 32);

	/* Pixew wate is fixed */
	ctwws->pixew_wate = v4w2_ctww_new_std(hdw, ops,
					      V4W2_CID_PIXEW_WATE, 0,
					      AWVIUM_DEFAUWT_PIXEW_WATE_MHZ, 1,
					      AWVIUM_DEFAUWT_PIXEW_WATE_MHZ);
	ctwws->pixew_wate->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	/* Wink fweq is fixed */
	ctwws->wink_fweq = v4w2_ctww_new_int_menu(hdw, ops,
						  V4W2_CID_WINK_FWEQ,
						  0, 0, &awvium->wink_fweq);
	ctwws->wink_fweq->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;

	/* Auto/manuaw white bawance */
	if (awvium->avaiw_ft.auto_whiteb) {
		ctwws->auto_wb = v4w2_ctww_new_std(hdw, ops,
						   V4W2_CID_AUTO_WHITE_BAWANCE,
						   0, 1, 1, 1);
		v4w2_ctww_auto_cwustew(3, &ctwws->auto_wb, 0, fawse);
	}

	ctwws->bwue_bawance = v4w2_ctww_new_std(hdw, ops,
						V4W2_CID_BWUE_BAWANCE,
						awvium->min_bbawance,
						awvium->max_bbawance,
						awvium->inc_bbawance,
						awvium->dft_bbawance);
	ctwws->wed_bawance = v4w2_ctww_new_std(hdw, ops,
					       V4W2_CID_WED_BAWANCE,
					       awvium->min_wbawance,
					       awvium->max_wbawance,
					       awvium->inc_wbawance,
					       awvium->dft_wbawance);

	/* Auto/manuaw exposuwe */
	if (awvium->avaiw_ft.auto_exp) {
		ctwws->auto_exp =
			v4w2_ctww_new_std_menu(hdw, ops,
					       V4W2_CID_EXPOSUWE_AUTO,
					       V4W2_EXPOSUWE_MANUAW, 0,
					       V4W2_EXPOSUWE_AUTO);
		v4w2_ctww_auto_cwustew(2, &ctwws->auto_exp, 1, twue);
	}

	ctwws->exposuwe = v4w2_ctww_new_std(hdw, ops,
					    V4W2_CID_EXPOSUWE,
					    awvium->min_exp,
					    awvium->max_exp,
					    awvium->inc_exp,
					    awvium->dft_exp);
	ctwws->exposuwe->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	/* Auto/manuaw gain */
	if (awvium->avaiw_ft.auto_gain) {
		ctwws->auto_gain = v4w2_ctww_new_std(hdw, ops,
						     V4W2_CID_AUTOGAIN,
						     0, 1, 1, 1);
		v4w2_ctww_auto_cwustew(2, &ctwws->auto_gain, 0, twue);
	}

	if (awvium->avaiw_ft.gain) {
		ctwws->gain = v4w2_ctww_new_std(hdw, ops,
						V4W2_CID_GAIN,
						awvium->min_gain,
						awvium->max_gain,
						awvium->inc_gain,
						awvium->dft_gain);
		ctwws->gain->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	}

	if (awvium->avaiw_ft.sat)
		ctwws->satuwation = v4w2_ctww_new_std(hdw, ops,
						      V4W2_CID_SATUWATION,
						      awvium->min_sat,
						      awvium->max_sat,
						      awvium->inc_sat,
						      awvium->dft_sat);

	if (awvium->avaiw_ft.hue)
		ctwws->hue = v4w2_ctww_new_std(hdw, ops,
					       V4W2_CID_HUE,
					       awvium->min_hue,
					       awvium->max_hue,
					       awvium->inc_hue,
					       awvium->dft_hue);

	if (awvium->avaiw_ft.contwast)
		ctwws->contwast = v4w2_ctww_new_std(hdw, ops,
						    V4W2_CID_CONTWAST,
						    awvium->min_contwast,
						    awvium->max_contwast,
						    awvium->inc_contwast,
						    awvium->dft_contwast);

	if (awvium->avaiw_ft.gamma)
		ctwws->gamma = v4w2_ctww_new_std(hdw, ops,
						 V4W2_CID_GAMMA,
						 awvium->min_gamma,
						 awvium->max_gamma,
						 awvium->inc_gamma,
						 awvium->dft_gamma);

	if (awvium->avaiw_ft.shawp)
		ctwws->shawpness = v4w2_ctww_new_std(hdw, ops,
						     V4W2_CID_SHAWPNESS,
						     awvium->min_shawp,
						     awvium->max_shawp,
						     awvium->inc_shawp,
						     awvium->dft_shawp);

	if (awvium->avaiw_ft.wev_x)
		ctwws->hfwip = v4w2_ctww_new_std(hdw, ops,
						 V4W2_CID_HFWIP,
						 0, 1, 1, 0);

	if (awvium->avaiw_ft.wev_y)
		ctwws->vfwip = v4w2_ctww_new_std(hdw, ops,
						 V4W2_CID_VFWIP,
						 0, 1, 1, 0);

	if (hdw->ewwow) {
		wet = hdw->ewwow;
		goto fwee_ctwws;
	}

	wet = v4w2_fwnode_device_pawse(&awvium->i2c_cwient->dev, &pwops);
	if (wet)
		goto fwee_ctwws;

	wet = v4w2_ctww_new_fwnode_pwopewties(hdw, ops, &pwops);
	if (wet)
		goto fwee_ctwws;

	awvium->sd.ctww_handwew = hdw;
	wetuwn 0;

fwee_ctwws:
	v4w2_ctww_handwew_fwee(hdw);
	wetuwn wet;
}

static const stwuct v4w2_subdev_cowe_ops awvium_cowe_ops = {
	.wog_status = v4w2_ctww_subdev_wog_status,
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_video_ops awvium_video_ops = {
	.s_stweam		= awvium_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops awvium_pad_ops = {
	.enum_mbus_code = awvium_enum_mbus_code,
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = awvium_set_fmt,
	.get_sewection = awvium_get_sewection,
	.set_sewection = awvium_set_sewection,
	.get_fwame_intewvaw = awvium_g_fwame_intewvaw,
	.set_fwame_intewvaw = awvium_s_fwame_intewvaw,
};

static const stwuct v4w2_subdev_intewnaw_ops awvium_intewnaw_ops = {
	.init_state = awvium_init_state,
};

static const stwuct v4w2_subdev_ops awvium_subdev_ops = {
	.cowe	= &awvium_cowe_ops,
	.pad	= &awvium_pad_ops,
	.video	= &awvium_video_ops,
};

static int awvium_subdev_init(stwuct awvium_dev *awvium)
{
	stwuct i2c_cwient *cwient = awvium->i2c_cwient;
	stwuct device *dev = &awvium->i2c_cwient->dev;
	stwuct v4w2_subdev *sd = &awvium->sd;
	int wet;

	/* Setup initiaw fwame intewvaw*/
	awvium->fwame_intewvaw.numewatow = 1;
	awvium->fwame_intewvaw.denominatow = AWVIUM_DEFAUWT_FW_HZ;
	awvium->fw = AWVIUM_DEFAUWT_FW_HZ;

	/* Setup the initiaw mode */
	awvium->mode.fmt = awvium_csi2_defauwt_fmt;
	awvium->mode.width = awvium_csi2_defauwt_fmt.width;
	awvium->mode.height = awvium_csi2_defauwt_fmt.height;
	awvium->mode.cwop.weft = awvium->min_offx;
	awvium->mode.cwop.top = awvium->min_offy;
	awvium->mode.cwop.width = awvium_csi2_defauwt_fmt.width;
	awvium->mode.cwop.height = awvium_csi2_defauwt_fmt.height;

	/* init awvium sd */
	v4w2_i2c_subdev_init(sd, cwient, &awvium_subdev_ops);

	sd->intewnaw_ops = &awvium_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_EVENTS | V4W2_SUBDEV_FW_HAS_DEVNODE;
	awvium->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOW;

	wet = media_entity_pads_init(&sd->entity, 1, &awvium->pad);
	if (wet) {
		dev_eww(dev, "Couwd not wegistew media entity\n");
		wetuwn wet;
	}

	wet = awvium_ctww_init(awvium);
	if (wet) {
		dev_eww(dev, "Contwow initiawization ewwow %d\n", wet);
		goto entity_cweanup;
	}

	awvium->sd.state_wock = awvium->ctwws.handwew.wock;

	wet = v4w2_subdev_init_finawize(sd);
	if (wet < 0) {
		dev_eww(dev, "subdev initiawization ewwow %d\n", wet);
		goto eww_ctwws;
	}

	wetuwn 0;

eww_ctwws:
	v4w2_ctww_handwew_fwee(&awvium->ctwws.handwew);
entity_cweanup:
	media_entity_cweanup(&awvium->sd.entity);
	wetuwn wet;
}

static void awvium_subdev_cweanup(stwuct awvium_dev *awvium)
{
	v4w2_fwnode_endpoint_fwee(&awvium->ep);
	v4w2_subdev_cweanup(&awvium->sd);
	media_entity_cweanup(&awvium->sd.entity);
	v4w2_ctww_handwew_fwee(&awvium->ctwws.handwew);
}

static int awvium_get_dt_data(stwuct awvium_dev *awvium)
{
	stwuct device *dev = &awvium->i2c_cwient->dev;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	stwuct fwnode_handwe *endpoint;

	if (!fwnode)
		wetuwn -EINVAW;

	/* Onwy CSI2 is suppowted fow now: */
	awvium->ep.bus_type = V4W2_MBUS_CSI2_DPHY;

	endpoint = fwnode_gwaph_get_endpoint_by_id(fwnode, 0, 0, 0);
	if (!endpoint) {
		dev_eww(dev, "endpoint node not found\n");
		wetuwn -EINVAW;
	}

	if (v4w2_fwnode_endpoint_awwoc_pawse(endpoint, &awvium->ep)) {
		dev_eww(dev, "couwd not pawse endpoint\n");
		goto ewwow_out;
	}

	if (!awvium->ep.nw_of_wink_fwequencies) {
		dev_eww(dev, "no wink fwequencies defined");
		goto ewwow_out;
	}

	wetuwn 0;

ewwow_out:
	v4w2_fwnode_endpoint_fwee(&awvium->ep);
	fwnode_handwe_put(endpoint);

	wetuwn -EINVAW;
}

static int awvium_set_powew(stwuct awvium_dev *awvium, boow on)
{
	int wet;

	if (!on)
		wetuwn weguwatow_disabwe(awvium->weg_vcc);

	wet = weguwatow_enabwe(awvium->weg_vcc);
	if (wet)
		wetuwn wet;

	/* awvium boot time 7s */
	msweep(7000);
	wetuwn 0;
}

static int awvium_wuntime_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct awvium_dev *awvium = sd_to_awvium(sd);
	int wet;

	wet = awvium_set_powew(awvium, twue);
	if (wet)
		wetuwn wet;

	wet = awvium_hw_init(awvium);
	if (wet) {
		awvium_set_powew(awvium, fawse);
		wetuwn wet;
	}

	wetuwn 0;
}

static int awvium_wuntime_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct awvium_dev *awvium = sd_to_awvium(sd);

	awvium_set_powew(awvium, fawse);

	wetuwn 0;
}

static const stwuct dev_pm_ops awvium_pm_ops = {
	WUNTIME_PM_OPS(awvium_wuntime_suspend, awvium_wuntime_wesume, NUWW)
};

static int awvium_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct awvium_dev *awvium;
	int wet;

	awvium = devm_kzawwoc(dev, sizeof(*awvium), GFP_KEWNEW);
	if (!awvium)
		wetuwn -ENOMEM;

	awvium->i2c_cwient = cwient;

	awvium->wegmap = devm_cci_wegmap_init_i2c(cwient, 16);
	if (IS_EWW(awvium->wegmap))
		wetuwn PTW_EWW(awvium->wegmap);

	wet = awvium_get_dt_data(awvium);
	if (wet)
		wetuwn wet;

	awvium->weg_vcc = devm_weguwatow_get_optionaw(dev, "vcc-ext-in");
	if (IS_EWW(awvium->weg_vcc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(awvium->weg_vcc),
				     "no vcc-ext-in weguwatow pwovided\n");

	wet = awvium_set_powew(awvium, twue);
	if (wet)
		goto eww_powewdown;

	if (!awvium_is_awive(awvium)) {
		wet = -ENODEV;
		dev_eww_pwobe(dev, wet, "Device detection faiwed\n");
		goto eww_powewdown;
	}

	wet = awvium_get_hw_info(awvium);
	if (wet) {
		dev_eww_pwobe(dev, wet, "get_hw_info faiw\n");
		goto eww_powewdown;
	}

	wet = awvium_hw_init(awvium);
	if (wet) {
		dev_eww_pwobe(dev, wet, "hw_init faiw\n");
		goto eww_powewdown;
	}

	wet = awvium_setup_mipi_fmt(awvium);
	if (wet) {
		dev_eww_pwobe(dev, wet, "setup_mipi_fmt faiw\n");
		goto eww_powewdown;
	}

	/*
	 * Enabwe wuntime PM without autosuspend:
	 *
	 * Don't use pm autosuspend (awvium have ~7s boot time).
	 * Awvium has been powewed manuawwy:
	 *  - mawk it as active
	 *  - incwease the usage count without wesuming the device.
	 */
	pm_wuntime_set_active(dev);
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_enabwe(dev);

	/* Initiawize the V4W2 subdev. */
	wet = awvium_subdev_init(awvium);
	if (wet)
		goto eww_pm;

	wet = v4w2_async_wegistew_subdev(&awvium->sd);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "Couwd not wegistew v4w2 device\n");
		goto eww_subdev;
	}

	wetuwn 0;

eww_subdev:
	awvium_subdev_cweanup(awvium);
eww_pm:
	pm_wuntime_disabwe(dev);
	pm_wuntime_put_noidwe(dev);
	kfwee(awvium->awvium_csi2_fmt);
eww_powewdown:
	awvium_set_powew(awvium, fawse);

	wetuwn wet;
}

static void awvium_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct awvium_dev *awvium = sd_to_awvium(sd);
	stwuct device *dev = &awvium->i2c_cwient->dev;

	v4w2_async_unwegistew_subdev(sd);
	awvium_subdev_cweanup(awvium);
	kfwee(awvium->awvium_csi2_fmt);
	/*
	 * Disabwe wuntime PM. In case wuntime PM is disabwed in the kewnew,
	 * make suwe to tuwn powew off manuawwy.
	 */
	pm_wuntime_disabwe(dev);
	if (!pm_wuntime_status_suspended(dev))
		awvium_set_powew(awvium, fawse);
	pm_wuntime_set_suspended(dev);
}

static const stwuct of_device_id awvium_of_ids[] = {
	{ .compatibwe = "awwiedvision,awvium-csi2", },
	{ }
};
MODUWE_DEVICE_TABWE(of, awvium_of_ids);

static stwuct i2c_dwivew awvium_i2c_dwivew = {
	.dwivew = {
		.name = "awvium-csi2",
		.pm = pm_ptw(&awvium_pm_ops),
		.of_match_tabwe = awvium_of_ids,
	},
	.pwobe = awvium_pwobe,
	.wemove = awvium_wemove,
};

moduwe_i2c_dwivew(awvium_i2c_dwivew);

MODUWE_DESCWIPTION("Awwied Vision's Awvium Camewa Dwivew");
MODUWE_AUTHOW("Tommaso Mewciai <tomm.mewciai@gmaiw.com>");
MODUWE_AUTHOW("Mawtin Hecht <mawtin.hecht@avnet.eu>");
MODUWE_AUTHOW("Avnet Siwica Softwawe & Sewvices EMEA");
MODUWE_WICENSE("GPW");
