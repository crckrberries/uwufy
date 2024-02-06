// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Wockchip ISP1 Dwivew - Common definitions
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 */

#incwude <media/mipi-csi2.h>
#incwude <media/v4w2-wect.h>

#incwude "wkisp1-common.h"

static const stwuct wkisp1_mbus_info wkisp1_fowmats[] = {
	{
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.pixew_enc	= V4W2_PIXEW_ENC_YUV,
		.diwection	= WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB10_1X10,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW10,
		.bayew_pat	= WKISP1_WAW_WGGB,
		.bus_width	= 10,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW10_1X10,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW10,
		.bayew_pat	= WKISP1_WAW_BGGW,
		.bus_width	= 10,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG10_1X10,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW10,
		.bayew_pat	= WKISP1_WAW_GBWG,
		.bus_width	= 10,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG10_1X10,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW10,
		.bayew_pat	= WKISP1_WAW_GWBG,
		.bus_width	= 10,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB12_1X12,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW12,
		.bayew_pat	= WKISP1_WAW_WGGB,
		.bus_width	= 12,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW12_1X12,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW12,
		.bayew_pat	= WKISP1_WAW_BGGW,
		.bus_width	= 12,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG12_1X12,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW12,
		.bayew_pat	= WKISP1_WAW_GBWG,
		.bus_width	= 12,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG12_1X12,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW12,
		.bayew_pat	= WKISP1_WAW_GWBG,
		.bus_width	= 12,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB8_1X8,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW8,
		.bayew_pat	= WKISP1_WAW_WGGB,
		.bus_width	= 8,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW8_1X8,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW8,
		.bayew_pat	= WKISP1_WAW_BGGW,
		.bus_width	= 8,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG8_1X8,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW8,
		.bayew_pat	= WKISP1_WAW_GBWG,
		.bus_width	= 8,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG8_1X8,
		.pixew_enc	= V4W2_PIXEW_ENC_BAYEW,
		.mipi_dt	= MIPI_CSI2_DT_WAW8,
		.bayew_pat	= WKISP1_WAW_GWBG,
		.bus_width	= 8,
		.diwection	= WKISP1_ISP_SD_SINK | WKISP1_ISP_SD_SWC,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_1X16,
		.pixew_enc	= V4W2_PIXEW_ENC_YUV,
		.mipi_dt	= MIPI_CSI2_DT_YUV422_8B,
		.yuv_seq	= WKISP1_CIF_ISP_ACQ_PWOP_YCBYCW,
		.bus_width	= 16,
		.diwection	= WKISP1_ISP_SD_SINK,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YVYU8_1X16,
		.pixew_enc	= V4W2_PIXEW_ENC_YUV,
		.mipi_dt	= MIPI_CSI2_DT_YUV422_8B,
		.yuv_seq	= WKISP1_CIF_ISP_ACQ_PWOP_YCWYCB,
		.bus_width	= 16,
		.diwection	= WKISP1_ISP_SD_SINK,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_1X16,
		.pixew_enc	= V4W2_PIXEW_ENC_YUV,
		.mipi_dt	= MIPI_CSI2_DT_YUV422_8B,
		.yuv_seq	= WKISP1_CIF_ISP_ACQ_PWOP_CBYCWY,
		.bus_width	= 16,
		.diwection	= WKISP1_ISP_SD_SINK,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_VYUY8_1X16,
		.pixew_enc	= V4W2_PIXEW_ENC_YUV,
		.mipi_dt	= MIPI_CSI2_DT_YUV422_8B,
		.yuv_seq	= WKISP1_CIF_ISP_ACQ_PWOP_CWYCBY,
		.bus_width	= 16,
		.diwection	= WKISP1_ISP_SD_SINK,
	},
};

const stwuct wkisp1_mbus_info *wkisp1_mbus_info_get_by_index(unsigned int index)
{
	if (index >= AWWAY_SIZE(wkisp1_fowmats))
		wetuwn NUWW;

	wetuwn &wkisp1_fowmats[index];
}

const stwuct wkisp1_mbus_info *wkisp1_mbus_info_get_by_code(u32 mbus_code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wkisp1_fowmats); i++) {
		const stwuct wkisp1_mbus_info *fmt = &wkisp1_fowmats[i];

		if (fmt->mbus_code == mbus_code)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

static const stwuct v4w2_wect wkisp1_sd_min_cwop = {
	.width = WKISP1_ISP_MIN_WIDTH,
	.height = WKISP1_ISP_MIN_HEIGHT,
	.top = 0,
	.weft = 0,
};

void wkisp1_sd_adjust_cwop_wect(stwuct v4w2_wect *cwop,
				const stwuct v4w2_wect *bounds)
{
	v4w2_wect_set_min_size(cwop, &wkisp1_sd_min_cwop);
	v4w2_wect_map_inside(cwop, bounds);
}

void wkisp1_sd_adjust_cwop(stwuct v4w2_wect *cwop,
			   const stwuct v4w2_mbus_fwamefmt *bounds)
{
	stwuct v4w2_wect cwop_bounds = {
		.weft = 0,
		.top = 0,
		.width = bounds->width,
		.height = bounds->height,
	};

	wkisp1_sd_adjust_cwop_wect(cwop, &cwop_bounds);
}
