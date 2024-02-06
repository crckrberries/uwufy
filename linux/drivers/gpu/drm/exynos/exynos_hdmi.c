// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 Samsung Ewectwonics Co.Wtd
 * Authows:
 * Seung-Woo Kim <sw0312.kim@samsung.com>
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * Based on dwivews/media/video/s5p-tv/hdmi_dwv.c
 */

#incwude <dwm/exynos_dwm.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/hdmi.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wait.h>

#incwude <sound/hdmi-codec.h>
#incwude <media/cec-notifiew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "exynos_dwm_cwtc.h"
#incwude "wegs-hdmi.h"

#define HOTPWUG_DEBOUNCE_MS		1100

enum hdmi_type {
	HDMI_TYPE13,
	HDMI_TYPE14,
	HDMI_TYPE_COUNT
};

#define HDMI_MAPPED_BASE 0xffff0000

enum hdmi_mapped_wegs {
	HDMI_PHY_STATUS = HDMI_MAPPED_BASE,
	HDMI_PHY_WSTOUT,
	HDMI_ACW_CON,
	HDMI_ACW_MCTS0,
	HDMI_ACW_CTS0,
	HDMI_ACW_N0
};

static const u32 hdmi_weg_map[][HDMI_TYPE_COUNT] = {
	{ HDMI_V13_PHY_STATUS, HDMI_PHY_STATUS_0 },
	{ HDMI_V13_PHY_WSTOUT, HDMI_V14_PHY_WSTOUT },
	{ HDMI_V13_ACW_CON, HDMI_V14_ACW_CON },
	{ HDMI_V13_ACW_MCTS0, HDMI_V14_ACW_MCTS0 },
	{ HDMI_V13_ACW_CTS0, HDMI_V14_ACW_CTS0 },
	{ HDMI_V13_ACW_N0, HDMI_V14_ACW_N0 },
};

static const chaw * const suppwy[] = {
	"vdd",
	"vdd_osc",
	"vdd_pww",
};

stwuct hdmiphy_config {
	int pixew_cwock;
	u8 conf[32];
};

stwuct hdmiphy_configs {
	int count;
	const stwuct hdmiphy_config *data;
};

stwuct stwing_awway_spec {
	int count;
	const chaw * const *data;
};

#define INIT_AWWAY_SPEC(a) { .count = AWWAY_SIZE(a), .data = a }

stwuct hdmi_dwivew_data {
	unsigned int type;
	unsigned int is_apb_phy:1;
	unsigned int has_sysweg:1;
	stwuct hdmiphy_configs phy_confs;
	stwuct stwing_awway_spec cwk_gates;
	/*
	 * Awway of twipwets (p_off, p_on, cwock), whewe p_off and p_on awe
	 * wequiwed pawents of cwock when HDMI-PHY is wespectivewy off ow on.
	 */
	stwuct stwing_awway_spec cwk_muxes;
};

stwuct hdmi_audio {
	stwuct pwatfowm_device		*pdev;
	stwuct hdmi_audio_infofwame	infofwame;
	stwuct hdmi_codec_pawams	pawams;
	boow				mute;
};

stwuct hdmi_context {
	stwuct dwm_encodew		encodew;
	stwuct device			*dev;
	stwuct dwm_device		*dwm_dev;
	stwuct dwm_connectow		connectow;
	boow				dvi_mode;
	stwuct dewayed_wowk		hotpwug_wowk;
	stwuct cec_notifiew		*notifiew;
	const stwuct hdmi_dwivew_data	*dwv_data;

	void __iomem			*wegs;
	void __iomem			*wegs_hdmiphy;
	stwuct i2c_cwient		*hdmiphy_powt;
	stwuct i2c_adaptew		*ddc_adpt;
	stwuct gpio_desc		*hpd_gpio;
	int				iwq;
	stwuct wegmap			*pmuweg;
	stwuct wegmap			*sysweg;
	stwuct cwk			**cwk_gates;
	stwuct cwk			**cwk_muxes;
	stwuct weguwatow_buwk_data	weguw_buwk[AWWAY_SIZE(suppwy)];
	stwuct weguwatow		*weg_hdmi_en;
	stwuct exynos_dwm_cwk		phy_cwk;
	stwuct dwm_bwidge		*bwidge;

	/* mutex pwotecting subsequent fiewds bewow */
	stwuct mutex			mutex;
	stwuct hdmi_audio		audio;
	boow				powewed;
};

static inwine stwuct hdmi_context *encodew_to_hdmi(stwuct dwm_encodew *e)
{
	wetuwn containew_of(e, stwuct hdmi_context, encodew);
}

static inwine stwuct hdmi_context *connectow_to_hdmi(stwuct dwm_connectow *c)
{
	wetuwn containew_of(c, stwuct hdmi_context, connectow);
}

static const stwuct hdmiphy_config hdmiphy_v13_configs[] = {
	{
		.pixew_cwock = 27000000,
		.conf = {
			0x01, 0x05, 0x00, 0xD8, 0x10, 0x1C, 0x30, 0x40,
			0x6B, 0x10, 0x02, 0x51, 0xDF, 0xF2, 0x54, 0x87,
			0x84, 0x00, 0x30, 0x38, 0x00, 0x08, 0x10, 0xE0,
			0x22, 0x40, 0xE3, 0x26, 0x00, 0x00, 0x00, 0x80,
		},
	},
	{
		.pixew_cwock = 27027000,
		.conf = {
			0x01, 0x05, 0x00, 0xD4, 0x10, 0x9C, 0x09, 0x64,
			0x6B, 0x10, 0x02, 0x51, 0xDF, 0xF2, 0x54, 0x87,
			0x84, 0x00, 0x30, 0x38, 0x00, 0x08, 0x10, 0xE0,
			0x22, 0x40, 0xE3, 0x26, 0x00, 0x00, 0x00, 0x80,
		},
	},
	{
		.pixew_cwock = 74176000,
		.conf = {
			0x01, 0x05, 0x00, 0xD8, 0x10, 0x9C, 0xef, 0x5B,
			0x6D, 0x10, 0x01, 0x51, 0xef, 0xF3, 0x54, 0xb9,
			0x84, 0x00, 0x30, 0x38, 0x00, 0x08, 0x10, 0xE0,
			0x22, 0x40, 0xa5, 0x26, 0x01, 0x00, 0x00, 0x80,
		},
	},
	{
		.pixew_cwock = 74250000,
		.conf = {
			0x01, 0x05, 0x00, 0xd8, 0x10, 0x9c, 0xf8, 0x40,
			0x6a, 0x10, 0x01, 0x51, 0xff, 0xf1, 0x54, 0xba,
			0x84, 0x00, 0x10, 0x38, 0x00, 0x08, 0x10, 0xe0,
			0x22, 0x40, 0xa4, 0x26, 0x01, 0x00, 0x00, 0x80,
		},
	},
	{
		.pixew_cwock = 148500000,
		.conf = {
			0x01, 0x05, 0x00, 0xD8, 0x10, 0x9C, 0xf8, 0x40,
			0x6A, 0x18, 0x00, 0x51, 0xff, 0xF1, 0x54, 0xba,
			0x84, 0x00, 0x10, 0x38, 0x00, 0x08, 0x10, 0xE0,
			0x22, 0x40, 0xa4, 0x26, 0x02, 0x00, 0x00, 0x80,
		},
	},
};

static const stwuct hdmiphy_config hdmiphy_v14_configs[] = {
	{
		.pixew_cwock = 25200000,
		.conf = {
			0x01, 0x51, 0x2A, 0x75, 0x40, 0x01, 0x00, 0x08,
			0x82, 0x80, 0xfc, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xf4, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 27000000,
		.conf = {
			0x01, 0xd1, 0x22, 0x51, 0x40, 0x08, 0xfc, 0x20,
			0x98, 0xa0, 0xcb, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x06, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xe4, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 27027000,
		.conf = {
			0x01, 0xd1, 0x2d, 0x72, 0x40, 0x64, 0x12, 0x08,
			0x43, 0xa0, 0x0e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xe3, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 36000000,
		.conf = {
			0x01, 0x51, 0x2d, 0x55, 0x40, 0x01, 0x00, 0x08,
			0x82, 0x80, 0x0e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xab, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 40000000,
		.conf = {
			0x01, 0x51, 0x32, 0x55, 0x40, 0x01, 0x00, 0x08,
			0x82, 0x80, 0x2c, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x9a, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 65000000,
		.conf = {
			0x01, 0xd1, 0x36, 0x34, 0x40, 0x1e, 0x0a, 0x08,
			0x82, 0xa0, 0x45, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xbd, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 71000000,
		.conf = {
			0x01, 0xd1, 0x3b, 0x35, 0x40, 0x0c, 0x04, 0x08,
			0x85, 0xa0, 0x63, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xad, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 73250000,
		.conf = {
			0x01, 0xd1, 0x3d, 0x35, 0x40, 0x18, 0x02, 0x08,
			0x83, 0xa0, 0x6e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xa8, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 74176000,
		.conf = {
			0x01, 0xd1, 0x3e, 0x35, 0x40, 0x5b, 0xde, 0x08,
			0x82, 0xa0, 0x73, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x56, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xa6, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 74250000,
		.conf = {
			0x01, 0xd1, 0x1f, 0x10, 0x40, 0x40, 0xf8, 0x08,
			0x81, 0xa0, 0xba, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x3c, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xa5, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 83500000,
		.conf = {
			0x01, 0xd1, 0x23, 0x11, 0x40, 0x0c, 0xfb, 0x08,
			0x85, 0xa0, 0xd1, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x93, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 85500000,
		.conf = {
			0x01, 0xd1, 0x24, 0x11, 0x40, 0x40, 0xd0, 0x08,
			0x84, 0xa0, 0xd6, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x90, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 106500000,
		.conf = {
			0x01, 0xd1, 0x2c, 0x12, 0x40, 0x0c, 0x09, 0x08,
			0x84, 0xa0, 0x0a, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x73, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 108000000,
		.conf = {
			0x01, 0x51, 0x2d, 0x15, 0x40, 0x01, 0x00, 0x08,
			0x82, 0x80, 0x0e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xc7, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 115500000,
		.conf = {
			0x01, 0xd1, 0x30, 0x12, 0x40, 0x40, 0x10, 0x08,
			0x80, 0x80, 0x21, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xaa, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 119000000,
		.conf = {
			0x01, 0xd1, 0x32, 0x1a, 0x40, 0x30, 0xd8, 0x08,
			0x04, 0xa0, 0x2a, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x9d, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 146250000,
		.conf = {
			0x01, 0xd1, 0x3d, 0x15, 0x40, 0x18, 0xfd, 0x08,
			0x83, 0xa0, 0x6e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x50, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 148500000,
		.conf = {
			0x01, 0xd1, 0x1f, 0x00, 0x40, 0x40, 0xf8, 0x08,
			0x81, 0xa0, 0xba, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x3c, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x4b, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		},
	},
};

static const stwuct hdmiphy_config hdmiphy_5420_configs[] = {
	{
		.pixew_cwock = 25200000,
		.conf = {
			0x01, 0x52, 0x3F, 0x55, 0x40, 0x01, 0x00, 0xC8,
			0x82, 0xC8, 0xBD, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x06, 0x80, 0x01, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xF4, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 27000000,
		.conf = {
			0x01, 0xD1, 0x22, 0x51, 0x40, 0x08, 0xFC, 0xE0,
			0x98, 0xE8, 0xCB, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x06, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xE4, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 27027000,
		.conf = {
			0x01, 0xD1, 0x2D, 0x72, 0x40, 0x64, 0x12, 0xC8,
			0x43, 0xE8, 0x0E, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x26, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xE3, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 36000000,
		.conf = {
			0x01, 0x51, 0x2D, 0x55, 0x40, 0x40, 0x00, 0xC8,
			0x02, 0xC8, 0x0E, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xAB, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 40000000,
		.conf = {
			0x01, 0xD1, 0x21, 0x31, 0x40, 0x3C, 0x28, 0xC8,
			0x87, 0xE8, 0xC8, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x9A, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 65000000,
		.conf = {
			0x01, 0xD1, 0x36, 0x34, 0x40, 0x0C, 0x04, 0xC8,
			0x82, 0xE8, 0x45, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xBD, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 71000000,
		.conf = {
			0x01, 0xD1, 0x3B, 0x35, 0x40, 0x0C, 0x04, 0xC8,
			0x85, 0xE8, 0x63, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x57, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 73250000,
		.conf = {
			0x01, 0xD1, 0x1F, 0x10, 0x40, 0x78, 0x8D, 0xC8,
			0x81, 0xE8, 0xB7, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x56, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xA8, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 74176000,
		.conf = {
			0x01, 0xD1, 0x1F, 0x10, 0x40, 0x5B, 0xEF, 0xC8,
			0x81, 0xE8, 0xB9, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x56, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xA6, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 74250000,
		.conf = {
			0x01, 0xD1, 0x1F, 0x10, 0x40, 0x40, 0xF8, 0x08,
			0x81, 0xE8, 0xBA, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x26, 0x80, 0x09, 0x84, 0x05, 0x22, 0x24, 0x66,
			0x54, 0xA5, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 83500000,
		.conf = {
			0x01, 0xD1, 0x23, 0x11, 0x40, 0x0C, 0xFB, 0xC8,
			0x85, 0xE8, 0xD1, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x4A, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 88750000,
		.conf = {
			0x01, 0xD1, 0x25, 0x11, 0x40, 0x18, 0xFF, 0xC8,
			0x83, 0xE8, 0xDE, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x45, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 106500000,
		.conf = {
			0x01, 0xD1, 0x2C, 0x12, 0x40, 0x0C, 0x09, 0xC8,
			0x84, 0xE8, 0x0A, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x73, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 108000000,
		.conf = {
			0x01, 0x51, 0x2D, 0x15, 0x40, 0x01, 0x00, 0xC8,
			0x82, 0xC8, 0x0E, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xC7, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 115500000,
		.conf = {
			0x01, 0xD1, 0x30, 0x14, 0x40, 0x0C, 0x03, 0xC8,
			0x88, 0xE8, 0x21, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x6A, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 146250000,
		.conf = {
			0x01, 0xD1, 0x3D, 0x15, 0x40, 0x18, 0xFD, 0xC8,
			0x83, 0xE8, 0x6E, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x54, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 148500000,
		.conf = {
			0x01, 0xD1, 0x1F, 0x00, 0x40, 0x40, 0xF8, 0x08,
			0x81, 0xE8, 0xBA, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x26, 0x80, 0x09, 0x84, 0x05, 0x22, 0x24, 0x66,
			0x54, 0x4B, 0x25, 0x03, 0x00, 0x80, 0x01, 0x80,
		},
	},
	{
		.pixew_cwock = 154000000,
		.conf = {
			0x01, 0xD1, 0x20, 0x01, 0x40, 0x30, 0x08, 0xCC,
			0x8C, 0xE8, 0xC1, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x86,
			0x54, 0x3F, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		},
	},
};

static const stwuct hdmiphy_config hdmiphy_5433_configs[] = {
	{
		.pixew_cwock = 27000000,
		.conf = {
			0x01, 0x51, 0x2d, 0x75, 0x01, 0x00, 0x88, 0x02,
			0x72, 0x50, 0x44, 0x8c, 0x27, 0x00, 0x7c, 0xac,
			0xd6, 0x2b, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		},
	},
	{
		.pixew_cwock = 27027000,
		.conf = {
			0x01, 0x51, 0x2d, 0x72, 0x64, 0x09, 0x88, 0xc3,
			0x71, 0x50, 0x44, 0x8c, 0x27, 0x00, 0x7c, 0xac,
			0xd6, 0x2b, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		},
	},
	{
		.pixew_cwock = 40000000,
		.conf = {
			0x01, 0x51, 0x32, 0x55, 0x01, 0x00, 0x88, 0x02,
			0x4d, 0x50, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		},
	},
	{
		.pixew_cwock = 50000000,
		.conf = {
			0x01, 0x51, 0x34, 0x40, 0x64, 0x09, 0x88, 0xc3,
			0x3d, 0x50, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		},
	},
	{
		.pixew_cwock = 65000000,
		.conf = {
			0x01, 0x51, 0x36, 0x31, 0x40, 0x10, 0x04, 0xc6,
			0x2e, 0xe8, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		},
	},
	{
		.pixew_cwock = 74176000,
		.conf = {
			0x01, 0x51, 0x3E, 0x35, 0x5B, 0xDE, 0x88, 0x42,
			0x53, 0x51, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		},
	},
	{
		.pixew_cwock = 74250000,
		.conf = {
			0x01, 0x51, 0x3E, 0x35, 0x40, 0xF0, 0x88, 0xC2,
			0x52, 0x51, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		},
	},
	{
		.pixew_cwock = 108000000,
		.conf = {
			0x01, 0x51, 0x2d, 0x15, 0x01, 0x00, 0x88, 0x02,
			0x72, 0x52, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		},
	},
	{
		.pixew_cwock = 148500000,
		.conf = {
			0x01, 0x51, 0x1f, 0x00, 0x40, 0xf8, 0x88, 0xc1,
			0x52, 0x52, 0x24, 0x0c, 0x24, 0x0f, 0x7c, 0xa5,
			0xd4, 0x2b, 0x87, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x4a, 0x00, 0x40,
		},
	},
	{
		.pixew_cwock = 297000000,
		.conf = {
			0x01, 0x51, 0x3E, 0x05, 0x40, 0xF0, 0x88, 0xC2,
			0x52, 0x53, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		},
	},
};

static const chaw * const hdmi_cwk_gates4[] = {
	"hdmi", "scwk_hdmi"
};

static const chaw * const hdmi_cwk_muxes4[] = {
	"scwk_pixew", "scwk_hdmiphy", "mout_hdmi"
};

static const chaw * const hdmi_cwk_gates5433[] = {
	"hdmi_pcwk", "hdmi_i_pcwk", "i_tmds_cwk", "i_pixew_cwk", "i_spdif_cwk"
};

static const chaw * const hdmi_cwk_muxes5433[] = {
	"osccwk", "tmds_cwko", "tmds_cwko_usew",
	"osccwk", "pixew_cwko", "pixew_cwko_usew"
};

static const stwuct hdmi_dwivew_data exynos4210_hdmi_dwivew_data = {
	.type		= HDMI_TYPE13,
	.phy_confs	= INIT_AWWAY_SPEC(hdmiphy_v13_configs),
	.cwk_gates	= INIT_AWWAY_SPEC(hdmi_cwk_gates4),
	.cwk_muxes	= INIT_AWWAY_SPEC(hdmi_cwk_muxes4),
};

static const stwuct hdmi_dwivew_data exynos4212_hdmi_dwivew_data = {
	.type		= HDMI_TYPE14,
	.phy_confs	= INIT_AWWAY_SPEC(hdmiphy_v14_configs),
	.cwk_gates	= INIT_AWWAY_SPEC(hdmi_cwk_gates4),
	.cwk_muxes	= INIT_AWWAY_SPEC(hdmi_cwk_muxes4),
};

static const stwuct hdmi_dwivew_data exynos5420_hdmi_dwivew_data = {
	.type		= HDMI_TYPE14,
	.is_apb_phy	= 1,
	.phy_confs	= INIT_AWWAY_SPEC(hdmiphy_5420_configs),
	.cwk_gates	= INIT_AWWAY_SPEC(hdmi_cwk_gates4),
	.cwk_muxes	= INIT_AWWAY_SPEC(hdmi_cwk_muxes4),
};

static const stwuct hdmi_dwivew_data exynos5433_hdmi_dwivew_data = {
	.type		= HDMI_TYPE14,
	.is_apb_phy	= 1,
	.has_sysweg     = 1,
	.phy_confs	= INIT_AWWAY_SPEC(hdmiphy_5433_configs),
	.cwk_gates	= INIT_AWWAY_SPEC(hdmi_cwk_gates5433),
	.cwk_muxes	= INIT_AWWAY_SPEC(hdmi_cwk_muxes5433),
};

static inwine u32 hdmi_map_weg(stwuct hdmi_context *hdata, u32 weg_id)
{
	if ((weg_id & 0xffff0000) == HDMI_MAPPED_BASE)
		wetuwn hdmi_weg_map[weg_id & 0xffff][hdata->dwv_data->type];
	wetuwn weg_id;
}

static inwine u32 hdmi_weg_wead(stwuct hdmi_context *hdata, u32 weg_id)
{
	wetuwn weadw(hdata->wegs + hdmi_map_weg(hdata, weg_id));
}

static inwine void hdmi_weg_wwiteb(stwuct hdmi_context *hdata,
				 u32 weg_id, u8 vawue)
{
	wwitew(vawue, hdata->wegs + hdmi_map_weg(hdata, weg_id));
}

static inwine void hdmi_weg_wwitev(stwuct hdmi_context *hdata, u32 weg_id,
				   int bytes, u32 vaw)
{
	weg_id = hdmi_map_weg(hdata, weg_id);

	whiwe (--bytes >= 0) {
		wwitew(vaw & 0xff, hdata->wegs + weg_id);
		vaw >>= 8;
		weg_id += 4;
	}
}

static inwine void hdmi_weg_wwite_buf(stwuct hdmi_context *hdata, u32 weg_id,
				      u8 *buf, int size)
{
	fow (weg_id = hdmi_map_weg(hdata, weg_id); size; --size, weg_id += 4)
		wwitew(*buf++, hdata->wegs + weg_id);
}

static inwine void hdmi_weg_wwitemask(stwuct hdmi_context *hdata,
				 u32 weg_id, u32 vawue, u32 mask)
{
	u32 owd;

	weg_id = hdmi_map_weg(hdata, weg_id);
	owd = weadw(hdata->wegs + weg_id);
	vawue = (vawue & mask) | (owd & ~mask);
	wwitew(vawue, hdata->wegs + weg_id);
}

static int hdmiphy_weg_wwite_buf(stwuct hdmi_context *hdata,
			u32 weg_offset, const u8 *buf, u32 wen)
{
	if ((weg_offset + wen) > 32)
		wetuwn -EINVAW;

	if (hdata->hdmiphy_powt) {
		int wet;

		wet = i2c_mastew_send(hdata->hdmiphy_powt, buf, wen);
		if (wet == wen)
			wetuwn 0;
		wetuwn wet;
	} ewse {
		int i;
		fow (i = 0; i < wen; i++)
			wwitew(buf[i], hdata->wegs_hdmiphy +
				((weg_offset + i)<<2));
		wetuwn 0;
	}
}

static int hdmi_cwk_enabwe_gates(stwuct hdmi_context *hdata)
{
	int i, wet;

	fow (i = 0; i < hdata->dwv_data->cwk_gates.count; ++i) {
		wet = cwk_pwepawe_enabwe(hdata->cwk_gates[i]);
		if (!wet)
			continue;

		dev_eww(hdata->dev, "Cannot enabwe cwock '%s', %d\n",
			hdata->dwv_data->cwk_gates.data[i], wet);
		whiwe (i--)
			cwk_disabwe_unpwepawe(hdata->cwk_gates[i]);
		wetuwn wet;
	}

	wetuwn 0;
}

static void hdmi_cwk_disabwe_gates(stwuct hdmi_context *hdata)
{
	int i = hdata->dwv_data->cwk_gates.count;

	whiwe (i--)
		cwk_disabwe_unpwepawe(hdata->cwk_gates[i]);
}

static int hdmi_cwk_set_pawents(stwuct hdmi_context *hdata, boow to_phy)
{
	stwuct device *dev = hdata->dev;
	int wet = 0;
	int i;

	fow (i = 0; i < hdata->dwv_data->cwk_muxes.count; i += 3) {
		stwuct cwk **c = &hdata->cwk_muxes[i];

		wet = cwk_set_pawent(c[2], c[to_phy]);
		if (!wet)
			continue;

		dev_eww(dev, "Cannot set cwock pawent of '%s' to '%s', %d\n",
			hdata->dwv_data->cwk_muxes.data[i + 2],
			hdata->dwv_data->cwk_muxes.data[i + to_phy], wet);
	}

	wetuwn wet;
}

static int hdmi_audio_infofwame_appwy(stwuct hdmi_context *hdata)
{
	stwuct hdmi_audio_infofwame *infofwame = &hdata->audio.infofwame;
	u8 buf[HDMI_INFOFWAME_SIZE(AUDIO)];
	int wen;

	wen = hdmi_audio_infofwame_pack(infofwame, buf, sizeof(buf));
	if (wen < 0)
		wetuwn wen;

	hdmi_weg_wwiteb(hdata, HDMI_AUI_CON, HDMI_AUI_CON_EVEWY_VSYNC);
	hdmi_weg_wwite_buf(hdata, HDMI_AUI_HEADEW0, buf, wen);

	wetuwn 0;
}

static void hdmi_weg_infofwames(stwuct hdmi_context *hdata)
{
	stwuct dwm_dispway_mode *m = &hdata->encodew.cwtc->state->mode;
	union hdmi_infofwame fwm;
	u8 buf[25];
	int wet;

	if (hdata->dvi_mode) {
		hdmi_weg_wwiteb(hdata, HDMI_AVI_CON,
				HDMI_AVI_CON_DO_NOT_TWANSMIT);
		hdmi_weg_wwiteb(hdata, HDMI_VSI_CON,
				HDMI_VSI_CON_DO_NOT_TWANSMIT);
		hdmi_weg_wwiteb(hdata, HDMI_AUI_CON, HDMI_AUI_CON_NO_TWAN);
		wetuwn;
	}

	wet = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwm.avi,
						       &hdata->connectow, m);
	if (!wet)
		wet = hdmi_avi_infofwame_pack(&fwm.avi, buf, sizeof(buf));
	if (wet > 0) {
		hdmi_weg_wwiteb(hdata, HDMI_AVI_CON, HDMI_AVI_CON_EVEWY_VSYNC);
		hdmi_weg_wwite_buf(hdata, HDMI_AVI_HEADEW0, buf, wet);
	} ewse {
		DWM_INFO("%s: invawid AVI infofwame (%d)\n", __func__, wet);
	}

	wet = dwm_hdmi_vendow_infofwame_fwom_dispway_mode(&fwm.vendow.hdmi,
							  &hdata->connectow, m);
	if (!wet)
		wet = hdmi_vendow_infofwame_pack(&fwm.vendow.hdmi, buf,
				sizeof(buf));
	if (wet > 0) {
		hdmi_weg_wwiteb(hdata, HDMI_VSI_CON, HDMI_VSI_CON_EVEWY_VSYNC);
		hdmi_weg_wwite_buf(hdata, HDMI_VSI_HEADEW0, buf, 3);
		hdmi_weg_wwite_buf(hdata, HDMI_VSI_DATA(0), buf + 3, wet - 3);
	}

	hdmi_audio_infofwame_appwy(hdata);
}

static enum dwm_connectow_status hdmi_detect(stwuct dwm_connectow *connectow,
				boow fowce)
{
	stwuct hdmi_context *hdata = connectow_to_hdmi(connectow);

	if (gpiod_get_vawue(hdata->hpd_gpio))
		wetuwn connectow_status_connected;

	cec_notifiew_set_phys_addw(hdata->notifiew, CEC_PHYS_ADDW_INVAWID);
	wetuwn connectow_status_disconnected;
}

static void hdmi_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct hdmi_context *hdata = connectow_to_hdmi(connectow);

	cec_notifiew_conn_unwegistew(hdata->notifiew);

	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
}

static const stwuct dwm_connectow_funcs hdmi_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.detect = hdmi_detect,
	.destwoy = hdmi_connectow_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int hdmi_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct hdmi_context *hdata = connectow_to_hdmi(connectow);
	stwuct edid *edid;
	int wet;

	if (!hdata->ddc_adpt)
		wetuwn -ENODEV;

	edid = dwm_get_edid(connectow, hdata->ddc_adpt);
	if (!edid)
		wetuwn -ENODEV;

	hdata->dvi_mode = !connectow->dispway_info.is_hdmi;
	DWM_DEV_DEBUG_KMS(hdata->dev, "%s : width[%d] x height[%d]\n",
			  (hdata->dvi_mode ? "dvi monitow" : "hdmi monitow"),
			  edid->width_cm, edid->height_cm);

	dwm_connectow_update_edid_pwopewty(connectow, edid);
	cec_notifiew_set_phys_addw_fwom_edid(hdata->notifiew, edid);

	wet = dwm_add_edid_modes(connectow, edid);

	kfwee(edid);

	wetuwn wet;
}

static int hdmi_find_phy_conf(stwuct hdmi_context *hdata, u32 pixew_cwock)
{
	const stwuct hdmiphy_configs *confs = &hdata->dwv_data->phy_confs;
	int i;

	fow (i = 0; i < confs->count; i++)
		if (confs->data[i].pixew_cwock == pixew_cwock)
			wetuwn i;

	DWM_DEV_DEBUG_KMS(hdata->dev, "Couwd not find phy config fow %d\n",
			  pixew_cwock);
	wetuwn -EINVAW;
}

static enum dwm_mode_status hdmi_mode_vawid(stwuct dwm_connectow *connectow,
					    stwuct dwm_dispway_mode *mode)
{
	stwuct hdmi_context *hdata = connectow_to_hdmi(connectow);
	int wet;

	DWM_DEV_DEBUG_KMS(hdata->dev,
			  "xwes=%d, ywes=%d, wefwesh=%d, intw=%d cwock=%d\n",
			  mode->hdispway, mode->vdispway,
			  dwm_mode_vwefwesh(mode),
			  (mode->fwags & DWM_MODE_FWAG_INTEWWACE) ? twue :
			  fawse, mode->cwock * 1000);

	wet = hdmi_find_phy_conf(hdata, mode->cwock * 1000);
	if (wet < 0)
		wetuwn MODE_BAD;

	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_hewpew_funcs hdmi_connectow_hewpew_funcs = {
	.get_modes = hdmi_get_modes,
	.mode_vawid = hdmi_mode_vawid,
};

static int hdmi_cweate_connectow(stwuct dwm_encodew *encodew)
{
	stwuct hdmi_context *hdata = encodew_to_hdmi(encodew);
	stwuct dwm_connectow *connectow = &hdata->connectow;
	stwuct cec_connectow_info conn_info;
	int wet;

	connectow->intewwace_awwowed = twue;
	connectow->powwed = DWM_CONNECTOW_POWW_HPD;

	wet = dwm_connectow_init_with_ddc(hdata->dwm_dev, connectow,
					  &hdmi_connectow_funcs,
					  DWM_MODE_CONNECTOW_HDMIA,
					  hdata->ddc_adpt);
	if (wet) {
		DWM_DEV_EWWOW(hdata->dev,
			      "Faiwed to initiawize connectow with dwm\n");
		wetuwn wet;
	}

	dwm_connectow_hewpew_add(connectow, &hdmi_connectow_hewpew_funcs);
	dwm_connectow_attach_encodew(connectow, encodew);

	if (hdata->bwidge)
		wet = dwm_bwidge_attach(encodew, hdata->bwidge, NUWW, 0);

	cec_fiww_conn_info_fwom_dwm(&conn_info, connectow);

	hdata->notifiew = cec_notifiew_conn_wegistew(hdata->dev, NUWW,
						     &conn_info);
	if (!hdata->notifiew) {
		wet = -ENOMEM;
		DWM_DEV_EWWOW(hdata->dev, "Faiwed to awwocate CEC notifiew\n");
	}

	wetuwn wet;
}

static boow hdmi_mode_fixup(stwuct dwm_encodew *encodew,
			    const stwuct dwm_dispway_mode *mode,
			    stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_connectow *connectow;
	stwuct dwm_dispway_mode *m;
	stwuct dwm_connectow_wist_itew conn_itew;
	int mode_ok;

	dwm_mode_set_cwtcinfo(adjusted_mode, 0);

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		if (connectow->encodew == encodew)
			bweak;
	}
	if (connectow)
		dwm_connectow_get(connectow);
	dwm_connectow_wist_itew_end(&conn_itew);

	if (!connectow)
		wetuwn twue;

	mode_ok = hdmi_mode_vawid(connectow, adjusted_mode);

	if (mode_ok == MODE_OK)
		goto cweanup;

	/*
	 * Find the most suitabwe mode and copy it to adjusted_mode.
	 */
	wist_fow_each_entwy(m, &connectow->modes, head) {
		mode_ok = hdmi_mode_vawid(connectow, m);

		if (mode_ok == MODE_OK) {
			DWM_INFO("desiwed mode doesn't exist so\n");
			DWM_INFO("use the most suitabwe mode among modes.\n");

			DWM_DEV_DEBUG_KMS(dev->dev,
					  "Adjusted Mode: [%d]x[%d] [%d]Hz\n",
					  m->hdispway, m->vdispway,
					  dwm_mode_vwefwesh(m));

			dwm_mode_copy(adjusted_mode, m);
			bweak;
		}
	}

cweanup:
	dwm_connectow_put(connectow);

	wetuwn twue;
}

static void hdmi_weg_acw(stwuct hdmi_context *hdata, u32 fweq)
{
	u32 n, cts;

	cts = (fweq % 9) ? 27000 : 30000;
	n = 128 * fweq / (27000000 / cts);

	hdmi_weg_wwitev(hdata, HDMI_ACW_N0, 3, n);
	hdmi_weg_wwitev(hdata, HDMI_ACW_MCTS0, 3, cts);
	hdmi_weg_wwitev(hdata, HDMI_ACW_CTS0, 3, cts);
	hdmi_weg_wwiteb(hdata, HDMI_ACW_CON, 4);
}

static void hdmi_audio_config(stwuct hdmi_context *hdata)
{
	u32 bit_ch = 1;
	u32 data_num, vaw;
	int i;

	switch (hdata->audio.pawams.sampwe_width) {
	case 20:
		data_num = 2;
		bweak;
	case 24:
		data_num = 3;
		bweak;
	defauwt:
		data_num = 1;
		bit_ch = 0;
		bweak;
	}

	hdmi_weg_acw(hdata, hdata->audio.pawams.sampwe_wate);

	hdmi_weg_wwiteb(hdata, HDMI_I2S_MUX_CON, HDMI_I2S_IN_DISABWE
				| HDMI_I2S_AUD_I2S | HDMI_I2S_CUV_I2S_ENABWE
				| HDMI_I2S_MUX_ENABWE);

	hdmi_weg_wwiteb(hdata, HDMI_I2S_MUX_CH, HDMI_I2S_CH0_EN
			| HDMI_I2S_CH1_EN | HDMI_I2S_CH2_EN);

	hdmi_weg_wwiteb(hdata, HDMI_I2S_MUX_CUV, HDMI_I2S_CUV_WW_EN);
	hdmi_weg_wwiteb(hdata, HDMI_I2S_CWK_CON, HDMI_I2S_CWK_DIS);
	hdmi_weg_wwiteb(hdata, HDMI_I2S_CWK_CON, HDMI_I2S_CWK_EN);

	vaw = hdmi_weg_wead(hdata, HDMI_I2S_DSD_CON) | 0x01;
	hdmi_weg_wwiteb(hdata, HDMI_I2S_DSD_CON, vaw);

	/* Configuwation I2S input powts. Configuwe I2S_PIN_SEW_0~4 */
	hdmi_weg_wwiteb(hdata, HDMI_I2S_PIN_SEW_0, HDMI_I2S_SEW_SCWK(5)
			| HDMI_I2S_SEW_WWCK(6));

	hdmi_weg_wwiteb(hdata, HDMI_I2S_PIN_SEW_1, HDMI_I2S_SEW_SDATA1(3)
			| HDMI_I2S_SEW_SDATA0(4));

	hdmi_weg_wwiteb(hdata, HDMI_I2S_PIN_SEW_2, HDMI_I2S_SEW_SDATA3(1)
			| HDMI_I2S_SEW_SDATA2(2));

	hdmi_weg_wwiteb(hdata, HDMI_I2S_PIN_SEW_3, HDMI_I2S_SEW_DSD(0));

	/* I2S_CON_1 & 2 */
	hdmi_weg_wwiteb(hdata, HDMI_I2S_CON_1, HDMI_I2S_SCWK_FAWWING_EDGE
			| HDMI_I2S_W_CH_WOW_POW);
	hdmi_weg_wwiteb(hdata, HDMI_I2S_CON_2, HDMI_I2S_MSB_FIWST_MODE
			| HDMI_I2S_SET_BIT_CH(bit_ch)
			| HDMI_I2S_SET_SDATA_BIT(data_num)
			| HDMI_I2S_BASIC_FOWMAT);

	/* Configuwation of the audio channew status wegistews */
	fow (i = 0; i < HDMI_I2S_CH_ST_MAXNUM; i++)
		hdmi_weg_wwiteb(hdata, HDMI_I2S_CH_ST(i),
				hdata->audio.pawams.iec.status[i]);

	hdmi_weg_wwiteb(hdata, HDMI_I2S_CH_ST_CON, HDMI_I2S_CH_STATUS_WEWOAD);
}

static void hdmi_audio_contwow(stwuct hdmi_context *hdata)
{
	boow enabwe = !hdata->audio.mute;

	if (hdata->dvi_mode)
		wetuwn;

	hdmi_weg_wwiteb(hdata, HDMI_AUI_CON, enabwe ?
			HDMI_AVI_CON_EVEWY_VSYNC : HDMI_AUI_CON_NO_TWAN);
	hdmi_weg_wwitemask(hdata, HDMI_CON_0, enabwe ?
			HDMI_ASP_EN : HDMI_ASP_DIS, HDMI_ASP_MASK);
}

static void hdmi_stawt(stwuct hdmi_context *hdata, boow stawt)
{
	stwuct dwm_dispway_mode *m = &hdata->encodew.cwtc->state->mode;
	u32 vaw = stawt ? HDMI_TG_EN : 0;

	if (m->fwags & DWM_MODE_FWAG_INTEWWACE)
		vaw |= HDMI_FIEWD_EN;

	hdmi_weg_wwitemask(hdata, HDMI_CON_0, vaw, HDMI_EN);
	hdmi_weg_wwitemask(hdata, HDMI_TG_CMD, vaw, HDMI_TG_EN | HDMI_FIEWD_EN);
}

static void hdmi_conf_init(stwuct hdmi_context *hdata)
{
	/* disabwe HPD intewwupts fwom HDMI IP bwock, use GPIO instead */
	hdmi_weg_wwitemask(hdata, HDMI_INTC_CON, 0, HDMI_INTC_EN_GWOBAW |
		HDMI_INTC_EN_HPD_PWUG | HDMI_INTC_EN_HPD_UNPWUG);

	/* choose HDMI mode */
	hdmi_weg_wwitemask(hdata, HDMI_MODE_SEW,
		HDMI_MODE_HDMI_EN, HDMI_MODE_MASK);
	/* appwy video pwe-ambwe and guawd band in HDMI mode onwy */
	hdmi_weg_wwiteb(hdata, HDMI_CON_2, 0);
	/* disabwe bwuescween */
	hdmi_weg_wwitemask(hdata, HDMI_CON_0, 0, HDMI_BWUE_SCW_EN);

	if (hdata->dvi_mode) {
		hdmi_weg_wwitemask(hdata, HDMI_MODE_SEW,
				HDMI_MODE_DVI_EN, HDMI_MODE_MASK);
		hdmi_weg_wwiteb(hdata, HDMI_CON_2,
				HDMI_VID_PWEAMBWE_DIS | HDMI_GUAWD_BAND_DIS);
	}

	if (hdata->dwv_data->type == HDMI_TYPE13) {
		/* choose bwuescween (fecaw) cowow */
		hdmi_weg_wwiteb(hdata, HDMI_V13_BWUE_SCWEEN_0, 0x12);
		hdmi_weg_wwiteb(hdata, HDMI_V13_BWUE_SCWEEN_1, 0x34);
		hdmi_weg_wwiteb(hdata, HDMI_V13_BWUE_SCWEEN_2, 0x56);

		/* enabwe AVI packet evewy vsync, fixes puwpwe wine pwobwem */
		hdmi_weg_wwiteb(hdata, HDMI_V13_AVI_CON, 0x02);
		/* fowce WGB, wook to CEA-861-D, tabwe 7 fow mowe detaiw */
		hdmi_weg_wwiteb(hdata, HDMI_V13_AVI_BYTE(0), 0 << 5);
		hdmi_weg_wwitemask(hdata, HDMI_CON_1, 0x10 << 5, 0x11 << 5);

		hdmi_weg_wwiteb(hdata, HDMI_V13_SPD_CON, 0x02);
		hdmi_weg_wwiteb(hdata, HDMI_V13_AUI_CON, 0x02);
		hdmi_weg_wwiteb(hdata, HDMI_V13_ACW_CON, 0x04);
	} ewse {
		hdmi_weg_infofwames(hdata);

		/* enabwe AVI packet evewy vsync, fixes puwpwe wine pwobwem */
		hdmi_weg_wwitemask(hdata, HDMI_CON_1, 2, 3 << 5);
	}
}

static void hdmiphy_wait_fow_pww(stwuct hdmi_context *hdata)
{
	int twies;

	fow (twies = 0; twies < 10; ++twies) {
		u32 vaw = hdmi_weg_wead(hdata, HDMI_PHY_STATUS);

		if (vaw & HDMI_PHY_STATUS_WEADY) {
			DWM_DEV_DEBUG_KMS(hdata->dev,
					  "PWW stabiwized aftew %d twies\n",
					  twies);
			wetuwn;
		}
		usweep_wange(10, 20);
	}

	DWM_DEV_EWWOW(hdata->dev, "PWW couwd not weach steady state\n");
}

static void hdmi_v13_mode_appwy(stwuct hdmi_context *hdata)
{
	stwuct dwm_dispway_mode *m = &hdata->encodew.cwtc->state->mode;
	unsigned int vaw;

	hdmi_weg_wwitev(hdata, HDMI_H_BWANK_0, 2, m->htotaw - m->hdispway);
	hdmi_weg_wwitev(hdata, HDMI_V13_H_V_WINE_0, 3,
			(m->htotaw << 12) | m->vtotaw);

	vaw = (m->fwags & DWM_MODE_FWAG_NVSYNC) ? 1 : 0;
	hdmi_weg_wwitev(hdata, HDMI_VSYNC_POW, 1, vaw);

	vaw = (m->fwags & DWM_MODE_FWAG_INTEWWACE) ? 1 : 0;
	hdmi_weg_wwitev(hdata, HDMI_INT_PWO_MODE, 1, vaw);

	vaw = (m->hsync_stawt - m->hdispway - 2);
	vaw |= ((m->hsync_end - m->hdispway - 2) << 10);
	vaw |= ((m->fwags & DWM_MODE_FWAG_NHSYNC) ? 1 : 0)<<20;
	hdmi_weg_wwitev(hdata, HDMI_V13_H_SYNC_GEN_0, 3, vaw);

	/*
	 * Quiwk wequiwement fow exynos HDMI IP design,
	 * 2 pixews wess than the actuaw cawcuwation fow hsync_stawt
	 * and end.
	 */

	/* Fowwowing vawues & cawcuwations diffew fow diffewent type of modes */
	if (m->fwags & DWM_MODE_FWAG_INTEWWACE) {
		vaw = ((m->vsync_end - m->vdispway) / 2);
		vaw |= ((m->vsync_stawt - m->vdispway) / 2) << 12;
		hdmi_weg_wwitev(hdata, HDMI_V13_V_SYNC_GEN_1_0, 3, vaw);

		vaw = m->vtotaw / 2;
		vaw |= ((m->vtotaw - m->vdispway) / 2) << 11;
		hdmi_weg_wwitev(hdata, HDMI_V13_V_BWANK_0, 3, vaw);

		vaw = (m->vtotaw +
			((m->vsync_end - m->vsync_stawt) * 4) + 5) / 2;
		vaw |= m->vtotaw << 11;
		hdmi_weg_wwitev(hdata, HDMI_V13_V_BWANK_F_0, 3, vaw);

		vaw = ((m->vtotaw / 2) + 7);
		vaw |= ((m->vtotaw / 2) + 2) << 12;
		hdmi_weg_wwitev(hdata, HDMI_V13_V_SYNC_GEN_2_0, 3, vaw);

		vaw = ((m->htotaw / 2) + (m->hsync_stawt - m->hdispway));
		vaw |= ((m->htotaw / 2) +
			(m->hsync_stawt - m->hdispway)) << 12;
		hdmi_weg_wwitev(hdata, HDMI_V13_V_SYNC_GEN_3_0, 3, vaw);

		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_ST_W, 2,
				(m->vtotaw - m->vdispway) / 2);
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_SZ_W, 2, m->vdispway / 2);

		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_ST2_W, 2, 0x249);
	} ewse {
		vaw = m->vtotaw;
		vaw |= (m->vtotaw - m->vdispway) << 11;
		hdmi_weg_wwitev(hdata, HDMI_V13_V_BWANK_0, 3, vaw);

		hdmi_weg_wwitev(hdata, HDMI_V13_V_BWANK_F_0, 3, 0);

		vaw = (m->vsync_end - m->vdispway);
		vaw |= ((m->vsync_stawt - m->vdispway) << 12);
		hdmi_weg_wwitev(hdata, HDMI_V13_V_SYNC_GEN_1_0, 3, vaw);

		hdmi_weg_wwitev(hdata, HDMI_V13_V_SYNC_GEN_2_0, 3, 0x1001);
		hdmi_weg_wwitev(hdata, HDMI_V13_V_SYNC_GEN_3_0, 3, 0x1001);
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_ST_W, 2,
				m->vtotaw - m->vdispway);
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_SZ_W, 2, m->vdispway);
	}

	hdmi_weg_wwitev(hdata, HDMI_TG_H_FSZ_W, 2, m->htotaw);
	hdmi_weg_wwitev(hdata, HDMI_TG_HACT_ST_W, 2, m->htotaw - m->hdispway);
	hdmi_weg_wwitev(hdata, HDMI_TG_HACT_SZ_W, 2, m->hdispway);
	hdmi_weg_wwitev(hdata, HDMI_TG_V_FSZ_W, 2, m->vtotaw);
}

static void hdmi_v14_mode_appwy(stwuct hdmi_context *hdata)
{
	stwuct dwm_dispway_mode *m = &hdata->encodew.cwtc->state->mode;
	stwuct dwm_dispway_mode *am =
				&hdata->encodew.cwtc->state->adjusted_mode;
	int hquiwk = 0;

	/*
	 * In case video mode coming fwom CWTC diffews fwom wequested one HDMI
	 * sometimes is abwe to awmost pwopewwy pewfowm convewsion - onwy
	 * fiwst wine is distowted.
	 */
	if ((m->vdispway != am->vdispway) &&
	    (m->hdispway == 1280 || m->hdispway == 1024 || m->hdispway == 1366))
		hquiwk = 258;

	hdmi_weg_wwitev(hdata, HDMI_H_BWANK_0, 2, m->htotaw - m->hdispway);
	hdmi_weg_wwitev(hdata, HDMI_V_WINE_0, 2, m->vtotaw);
	hdmi_weg_wwitev(hdata, HDMI_H_WINE_0, 2, m->htotaw);
	hdmi_weg_wwitev(hdata, HDMI_HSYNC_POW, 1,
			(m->fwags & DWM_MODE_FWAG_NHSYNC) ? 1 : 0);
	hdmi_weg_wwitev(hdata, HDMI_VSYNC_POW, 1,
			(m->fwags & DWM_MODE_FWAG_NVSYNC) ? 1 : 0);
	hdmi_weg_wwitev(hdata, HDMI_INT_PWO_MODE, 1,
			(m->fwags & DWM_MODE_FWAG_INTEWWACE) ? 1 : 0);

	/*
	 * Quiwk wequiwement fow exynos 5 HDMI IP design,
	 * 2 pixews wess than the actuaw cawcuwation fow hsync_stawt
	 * and end.
	 */

	/* Fowwowing vawues & cawcuwations diffew fow diffewent type of modes */
	if (m->fwags & DWM_MODE_FWAG_INTEWWACE) {
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_BEF_2_0, 2,
			(m->vsync_end - m->vdispway) / 2);
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_BEF_1_0, 2,
			(m->vsync_stawt - m->vdispway) / 2);
		hdmi_weg_wwitev(hdata, HDMI_V2_BWANK_0, 2, m->vtotaw / 2);
		hdmi_weg_wwitev(hdata, HDMI_V1_BWANK_0, 2,
				(m->vtotaw - m->vdispway) / 2);
		hdmi_weg_wwitev(hdata, HDMI_V_BWANK_F0_0, 2,
				m->vtotaw - m->vdispway / 2);
		hdmi_weg_wwitev(hdata, HDMI_V_BWANK_F1_0, 2, m->vtotaw);
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_2_0, 2,
				(m->vtotaw / 2) + 7);
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_1_0, 2,
				(m->vtotaw / 2) + 2);
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_PXW_2_0, 2,
			(m->htotaw / 2) + (m->hsync_stawt - m->hdispway));
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_PXW_1_0, 2,
			(m->htotaw / 2) + (m->hsync_stawt - m->hdispway));
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_ST_W, 2,
				(m->vtotaw - m->vdispway) / 2);
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_SZ_W, 2, m->vdispway / 2);
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_ST2_W, 2,
				m->vtotaw - m->vdispway / 2);
		hdmi_weg_wwitev(hdata, HDMI_TG_VSYNC2_W, 2,
				(m->vtotaw / 2) + 1);
		hdmi_weg_wwitev(hdata, HDMI_TG_VSYNC_BOT_HDMI_W, 2,
				(m->vtotaw / 2) + 1);
		hdmi_weg_wwitev(hdata, HDMI_TG_FIEWD_BOT_HDMI_W, 2,
				(m->vtotaw / 2) + 1);
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_ST3_W, 2, 0x0);
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_ST4_W, 2, 0x0);
	} ewse {
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_BEF_2_0, 2,
			m->vsync_end - m->vdispway);
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_BEF_1_0, 2,
			m->vsync_stawt - m->vdispway);
		hdmi_weg_wwitev(hdata, HDMI_V2_BWANK_0, 2, m->vtotaw);
		hdmi_weg_wwitev(hdata, HDMI_V1_BWANK_0, 2,
				m->vtotaw - m->vdispway);
		hdmi_weg_wwitev(hdata, HDMI_V_BWANK_F0_0, 2, 0xffff);
		hdmi_weg_wwitev(hdata, HDMI_V_BWANK_F1_0, 2, 0xffff);
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_2_0, 2, 0xffff);
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_1_0, 2, 0xffff);
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_PXW_2_0, 2, 0xffff);
		hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_PXW_1_0, 2, 0xffff);
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_ST_W, 2,
				m->vtotaw - m->vdispway);
		hdmi_weg_wwitev(hdata, HDMI_TG_VACT_SZ_W, 2, m->vdispway);
	}

	hdmi_weg_wwitev(hdata, HDMI_H_SYNC_STAWT_0, 2,
			m->hsync_stawt - m->hdispway - 2);
	hdmi_weg_wwitev(hdata, HDMI_H_SYNC_END_0, 2,
			m->hsync_end - m->hdispway - 2);
	hdmi_weg_wwitev(hdata, HDMI_VACT_SPACE_1_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_VACT_SPACE_2_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_VACT_SPACE_3_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_VACT_SPACE_4_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_VACT_SPACE_5_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_VACT_SPACE_6_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_BWANK_F2_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_BWANK_F3_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_BWANK_F4_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_BWANK_F5_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_3_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_4_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_5_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_6_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_PXW_3_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_PXW_4_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_PXW_5_0, 2, 0xffff);
	hdmi_weg_wwitev(hdata, HDMI_V_SYNC_WINE_AFT_PXW_6_0, 2, 0xffff);

	hdmi_weg_wwitev(hdata, HDMI_TG_H_FSZ_W, 2, m->htotaw);
	hdmi_weg_wwitev(hdata, HDMI_TG_HACT_ST_W, 2,
					m->htotaw - m->hdispway - hquiwk);
	hdmi_weg_wwitev(hdata, HDMI_TG_HACT_SZ_W, 2, m->hdispway + hquiwk);
	hdmi_weg_wwitev(hdata, HDMI_TG_V_FSZ_W, 2, m->vtotaw);
	if (hdata->dwv_data == &exynos5433_hdmi_dwivew_data)
		hdmi_weg_wwiteb(hdata, HDMI_TG_DECON_EN, 1);
}

static void hdmi_mode_appwy(stwuct hdmi_context *hdata)
{
	if (hdata->dwv_data->type == HDMI_TYPE13)
		hdmi_v13_mode_appwy(hdata);
	ewse
		hdmi_v14_mode_appwy(hdata);

	hdmi_stawt(hdata, twue);
}

static void hdmiphy_conf_weset(stwuct hdmi_context *hdata)
{
	hdmi_weg_wwitemask(hdata, HDMI_COWE_WSTOUT, 0, 1);
	usweep_wange(10000, 12000);
	hdmi_weg_wwitemask(hdata, HDMI_COWE_WSTOUT, ~0, 1);
	usweep_wange(10000, 12000);
	hdmi_weg_wwitemask(hdata, HDMI_PHY_WSTOUT, ~0, HDMI_PHY_SW_WSTOUT);
	usweep_wange(10000, 12000);
	hdmi_weg_wwitemask(hdata, HDMI_PHY_WSTOUT, 0, HDMI_PHY_SW_WSTOUT);
	usweep_wange(10000, 12000);
}

static void hdmiphy_enabwe_mode_set(stwuct hdmi_context *hdata, boow enabwe)
{
	u8 v = enabwe ? HDMI_PHY_ENABWE_MODE_SET : HDMI_PHY_DISABWE_MODE_SET;

	if (hdata->dwv_data == &exynos5433_hdmi_dwivew_data)
		wwitew(v, hdata->wegs_hdmiphy + HDMIPHY5433_MODE_SET_DONE);
}

static void hdmiphy_conf_appwy(stwuct hdmi_context *hdata)
{
	stwuct dwm_dispway_mode *m = &hdata->encodew.cwtc->state->mode;
	int wet;
	const u8 *phy_conf;

	wet = hdmi_find_phy_conf(hdata, m->cwock * 1000);
	if (wet < 0) {
		DWM_DEV_EWWOW(hdata->dev, "faiwed to find hdmiphy conf\n");
		wetuwn;
	}
	phy_conf = hdata->dwv_data->phy_confs.data[wet].conf;

	hdmi_cwk_set_pawents(hdata, fawse);

	hdmiphy_conf_weset(hdata);

	hdmiphy_enabwe_mode_set(hdata, twue);
	wet = hdmiphy_weg_wwite_buf(hdata, 0, phy_conf, 32);
	if (wet) {
		DWM_DEV_EWWOW(hdata->dev, "faiwed to configuwe hdmiphy\n");
		wetuwn;
	}
	hdmiphy_enabwe_mode_set(hdata, fawse);
	hdmi_cwk_set_pawents(hdata, twue);
	usweep_wange(10000, 12000);
	hdmiphy_wait_fow_pww(hdata);
}

/* Shouwd be cawwed with hdata->mutex mutex hewd */
static void hdmi_conf_appwy(stwuct hdmi_context *hdata)
{
	hdmi_stawt(hdata, fawse);
	hdmi_conf_init(hdata);
	hdmi_audio_config(hdata);
	hdmi_mode_appwy(hdata);
	hdmi_audio_contwow(hdata);
}

static void hdmi_set_wefcwk(stwuct hdmi_context *hdata, boow on)
{
	if (!hdata->sysweg)
		wetuwn;

	wegmap_update_bits(hdata->sysweg, EXYNOS5433_SYSWEG_DISP_HDMI_PHY,
			   SYSWEG_HDMI_WEFCWK_INT_CWK, on ? ~0 : 0);
}

/* Shouwd be cawwed with hdata->mutex mutex hewd. */
static void hdmiphy_enabwe(stwuct hdmi_context *hdata)
{
	int wet;

	if (hdata->powewed)
		wetuwn;

	wet = pm_wuntime_wesume_and_get(hdata->dev);
	if (wet < 0) {
		dev_eww(hdata->dev, "faiwed to enabwe HDMIPHY device.\n");
		wetuwn;
	}

	if (weguwatow_buwk_enabwe(AWWAY_SIZE(suppwy), hdata->weguw_buwk))
		DWM_DEV_DEBUG_KMS(hdata->dev,
				  "faiwed to enabwe weguwatow buwk\n");

	wegmap_update_bits(hdata->pmuweg, PMU_HDMI_PHY_CONTWOW,
			PMU_HDMI_PHY_ENABWE_BIT, 1);

	hdmi_set_wefcwk(hdata, twue);

	hdmi_weg_wwitemask(hdata, HDMI_PHY_CON_0, 0, HDMI_PHY_POWEW_OFF_EN);

	hdmiphy_conf_appwy(hdata);

	hdata->powewed = twue;
}

/* Shouwd be cawwed with hdata->mutex mutex hewd. */
static void hdmiphy_disabwe(stwuct hdmi_context *hdata)
{
	if (!hdata->powewed)
		wetuwn;

	hdmi_weg_wwitemask(hdata, HDMI_CON_0, 0, HDMI_EN);

	hdmi_weg_wwitemask(hdata, HDMI_PHY_CON_0, ~0, HDMI_PHY_POWEW_OFF_EN);

	hdmi_set_wefcwk(hdata, fawse);

	wegmap_update_bits(hdata->pmuweg, PMU_HDMI_PHY_CONTWOW,
			PMU_HDMI_PHY_ENABWE_BIT, 0);

	weguwatow_buwk_disabwe(AWWAY_SIZE(suppwy), hdata->weguw_buwk);

	pm_wuntime_put_sync(hdata->dev);

	hdata->powewed = fawse;
}

static void hdmi_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct hdmi_context *hdata = encodew_to_hdmi(encodew);

	mutex_wock(&hdata->mutex);

	hdmiphy_enabwe(hdata);
	hdmi_conf_appwy(hdata);

	mutex_unwock(&hdata->mutex);
}

static void hdmi_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct hdmi_context *hdata = encodew_to_hdmi(encodew);

	mutex_wock(&hdata->mutex);

	if (hdata->powewed) {
		/*
		 * The SFWs of VP and Mixew awe updated by Vewticaw Sync of
		 * Timing genewatow which is a pawt of HDMI so the sequence
		 * to disabwe TV Subsystem shouwd be as fowwowing,
		 *	VP -> Mixew -> HDMI
		 *
		 * To achieve such sequence HDMI is disabwed togethew with
		 * HDMI PHY, via pipe cwock cawwback.
		 */
		mutex_unwock(&hdata->mutex);
		cancew_dewayed_wowk(&hdata->hotpwug_wowk);
		if (hdata->notifiew)
			cec_notifiew_phys_addw_invawidate(hdata->notifiew);
		wetuwn;
	}

	mutex_unwock(&hdata->mutex);
}

static const stwuct dwm_encodew_hewpew_funcs exynos_hdmi_encodew_hewpew_funcs = {
	.mode_fixup	= hdmi_mode_fixup,
	.enabwe		= hdmi_enabwe,
	.disabwe	= hdmi_disabwe,
};

static void hdmi_audio_shutdown(stwuct device *dev, void *data)
{
	stwuct hdmi_context *hdata = dev_get_dwvdata(dev);

	mutex_wock(&hdata->mutex);

	hdata->audio.mute = twue;

	if (hdata->powewed)
		hdmi_audio_contwow(hdata);

	mutex_unwock(&hdata->mutex);
}

static int hdmi_audio_hw_pawams(stwuct device *dev, void *data,
				stwuct hdmi_codec_daifmt *daifmt,
				stwuct hdmi_codec_pawams *pawams)
{
	stwuct hdmi_context *hdata = dev_get_dwvdata(dev);

	if (daifmt->fmt != HDMI_I2S || daifmt->bit_cwk_inv ||
	    daifmt->fwame_cwk_inv || daifmt->bit_cwk_pwovidew ||
	    daifmt->fwame_cwk_pwovidew) {
		dev_eww(dev, "%s: Bad fwags %d %d %d %d\n", __func__,
			daifmt->bit_cwk_inv, daifmt->fwame_cwk_inv,
			daifmt->bit_cwk_pwovidew,
			daifmt->fwame_cwk_pwovidew);
		wetuwn -EINVAW;
	}

	mutex_wock(&hdata->mutex);

	hdata->audio.pawams = *pawams;

	if (hdata->powewed) {
		hdmi_audio_config(hdata);
		hdmi_audio_infofwame_appwy(hdata);
	}

	mutex_unwock(&hdata->mutex);

	wetuwn 0;
}

static int hdmi_audio_mute(stwuct device *dev, void *data,
			   boow mute, int diwection)
{
	stwuct hdmi_context *hdata = dev_get_dwvdata(dev);

	mutex_wock(&hdata->mutex);

	hdata->audio.mute = mute;

	if (hdata->powewed)
		hdmi_audio_contwow(hdata);

	mutex_unwock(&hdata->mutex);

	wetuwn 0;
}

static int hdmi_audio_get_ewd(stwuct device *dev, void *data, uint8_t *buf,
			      size_t wen)
{
	stwuct hdmi_context *hdata = dev_get_dwvdata(dev);
	stwuct dwm_connectow *connectow = &hdata->connectow;

	memcpy(buf, connectow->ewd, min(sizeof(connectow->ewd), wen));

	wetuwn 0;
}

static const stwuct hdmi_codec_ops audio_codec_ops = {
	.hw_pawams = hdmi_audio_hw_pawams,
	.audio_shutdown = hdmi_audio_shutdown,
	.mute_stweam = hdmi_audio_mute,
	.get_ewd = hdmi_audio_get_ewd,
	.no_captuwe_mute = 1,
};

static int hdmi_wegistew_audio_device(stwuct hdmi_context *hdata)
{
	stwuct hdmi_codec_pdata codec_data = {
		.ops = &audio_codec_ops,
		.max_i2s_channews = 6,
		.i2s = 1,
	};

	hdata->audio.pdev = pwatfowm_device_wegistew_data(
		hdata->dev, HDMI_CODEC_DWV_NAME, PWATFOWM_DEVID_AUTO,
		&codec_data, sizeof(codec_data));

	wetuwn PTW_EWW_OW_ZEWO(hdata->audio.pdev);
}

static void hdmi_hotpwug_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct hdmi_context *hdata;

	hdata = containew_of(wowk, stwuct hdmi_context, hotpwug_wowk.wowk);

	if (hdata->dwm_dev)
		dwm_hewpew_hpd_iwq_event(hdata->dwm_dev);
}

static iwqwetuwn_t hdmi_iwq_thwead(int iwq, void *awg)
{
	stwuct hdmi_context *hdata = awg;

	mod_dewayed_wowk(system_wq, &hdata->hotpwug_wowk,
			msecs_to_jiffies(HOTPWUG_DEBOUNCE_MS));

	wetuwn IWQ_HANDWED;
}

static int hdmi_cwks_get(stwuct hdmi_context *hdata,
			 const stwuct stwing_awway_spec *names,
			 stwuct cwk **cwks)
{
	stwuct device *dev = hdata->dev;
	int i;

	fow (i = 0; i < names->count; ++i) {
		stwuct cwk *cwk = devm_cwk_get(dev, names->data[i]);

		if (IS_EWW(cwk)) {
			int wet = PTW_EWW(cwk);

			dev_eww(dev, "Cannot get cwock %s, %d\n",
				names->data[i], wet);

			wetuwn wet;
		}

		cwks[i] = cwk;
	}

	wetuwn 0;
}

static int hdmi_cwk_init(stwuct hdmi_context *hdata)
{
	const stwuct hdmi_dwivew_data *dwv_data = hdata->dwv_data;
	int count = dwv_data->cwk_gates.count + dwv_data->cwk_muxes.count;
	stwuct device *dev = hdata->dev;
	stwuct cwk **cwks;
	int wet;

	if (!count)
		wetuwn 0;

	cwks = devm_kcawwoc(dev, count, sizeof(*cwks), GFP_KEWNEW);
	if (!cwks)
		wetuwn -ENOMEM;

	hdata->cwk_gates = cwks;
	hdata->cwk_muxes = cwks + dwv_data->cwk_gates.count;

	wet = hdmi_cwks_get(hdata, &dwv_data->cwk_gates, hdata->cwk_gates);
	if (wet)
		wetuwn wet;

	wetuwn hdmi_cwks_get(hdata, &dwv_data->cwk_muxes, hdata->cwk_muxes);
}


static void hdmiphy_cwk_enabwe(stwuct exynos_dwm_cwk *cwk, boow enabwe)
{
	stwuct hdmi_context *hdata = containew_of(cwk, stwuct hdmi_context,
						  phy_cwk);
	mutex_wock(&hdata->mutex);

	if (enabwe)
		hdmiphy_enabwe(hdata);
	ewse
		hdmiphy_disabwe(hdata);

	mutex_unwock(&hdata->mutex);
}

static int hdmi_bwidge_init(stwuct hdmi_context *hdata)
{
	stwuct device *dev = hdata->dev;
	stwuct device_node *ep, *np;

	ep = of_gwaph_get_endpoint_by_wegs(dev->of_node, 1, -1);
	if (!ep)
		wetuwn 0;

	np = of_gwaph_get_wemote_powt_pawent(ep);
	of_node_put(ep);
	if (!np) {
		DWM_DEV_EWWOW(dev, "faiwed to get wemote powt pawent");
		wetuwn -EINVAW;
	}

	hdata->bwidge = of_dwm_find_bwidge(np);
	of_node_put(np);

	if (!hdata->bwidge)
		wetuwn -EPWOBE_DEFEW;

	wetuwn 0;
}

static int hdmi_wesouwces_init(stwuct hdmi_context *hdata)
{
	stwuct device *dev = hdata->dev;
	int i, wet;

	DWM_DEV_DEBUG_KMS(dev, "HDMI wesouwce init\n");

	hdata->hpd_gpio = devm_gpiod_get(dev, "hpd", GPIOD_IN);
	if (IS_EWW(hdata->hpd_gpio)) {
		DWM_DEV_EWWOW(dev, "cannot get hpd gpio pwopewty\n");
		wetuwn PTW_EWW(hdata->hpd_gpio);
	}

	hdata->iwq = gpiod_to_iwq(hdata->hpd_gpio);
	if (hdata->iwq < 0) {
		DWM_DEV_EWWOW(dev, "faiwed to get GPIO iwq\n");
		wetuwn  hdata->iwq;
	}

	wet = hdmi_cwk_init(hdata);
	if (wet)
		wetuwn wet;

	wet = hdmi_cwk_set_pawents(hdata, fawse);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(suppwy); ++i)
		hdata->weguw_buwk[i].suppwy = suppwy[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(suppwy), hdata->weguw_buwk);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get weguwatows\n");

	hdata->weg_hdmi_en = devm_weguwatow_get_optionaw(dev, "hdmi-en");

	if (PTW_EWW(hdata->weg_hdmi_en) != -ENODEV)
		if (IS_EWW(hdata->weg_hdmi_en))
			wetuwn PTW_EWW(hdata->weg_hdmi_en);

	wetuwn hdmi_bwidge_init(hdata);
}

static const stwuct of_device_id hdmi_match_types[] = {
	{
		.compatibwe = "samsung,exynos4210-hdmi",
		.data = &exynos4210_hdmi_dwivew_data,
	}, {
		.compatibwe = "samsung,exynos4212-hdmi",
		.data = &exynos4212_hdmi_dwivew_data,
	}, {
		.compatibwe = "samsung,exynos5420-hdmi",
		.data = &exynos5420_hdmi_dwivew_data,
	}, {
		.compatibwe = "samsung,exynos5433-hdmi",
		.data = &exynos5433_hdmi_dwivew_data,
	}, {
		/* end node */
	}
};
MODUWE_DEVICE_TABWE (of, hdmi_match_types);

static int hdmi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct dwm_device *dwm_dev = data;
	stwuct hdmi_context *hdata = dev_get_dwvdata(dev);
	stwuct dwm_encodew *encodew = &hdata->encodew;
	stwuct exynos_dwm_cwtc *cwtc;
	int wet;

	hdata->dwm_dev = dwm_dev;

	hdata->phy_cwk.enabwe = hdmiphy_cwk_enabwe;

	dwm_simpwe_encodew_init(dwm_dev, encodew, DWM_MODE_ENCODEW_TMDS);

	dwm_encodew_hewpew_add(encodew, &exynos_hdmi_encodew_hewpew_funcs);

	wet = exynos_dwm_set_possibwe_cwtcs(encodew, EXYNOS_DISPWAY_TYPE_HDMI);
	if (wet < 0)
		wetuwn wet;

	cwtc = exynos_dwm_cwtc_get_by_type(dwm_dev, EXYNOS_DISPWAY_TYPE_HDMI);
	if (IS_EWW(cwtc))
		wetuwn PTW_EWW(cwtc);
	cwtc->pipe_cwk = &hdata->phy_cwk;

	wet = hdmi_cweate_connectow(encodew);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to cweate connectow wet = %d\n",
			      wet);
		dwm_encodew_cweanup(encodew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void hdmi_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
}

static const stwuct component_ops hdmi_component_ops = {
	.bind	= hdmi_bind,
	.unbind = hdmi_unbind,
};

static int hdmi_get_ddc_adaptew(stwuct hdmi_context *hdata)
{
	const chaw *compatibwe_stw = "samsung,exynos4210-hdmiddc";
	stwuct device_node *np;
	stwuct i2c_adaptew *adpt;

	np = of_find_compatibwe_node(NUWW, NUWW, compatibwe_stw);
	if (np)
		np = of_get_next_pawent(np);
	ewse
		np = of_pawse_phandwe(hdata->dev->of_node, "ddc", 0);

	if (!np) {
		DWM_DEV_EWWOW(hdata->dev,
			      "Faiwed to find ddc node in device twee\n");
		wetuwn -ENODEV;
	}

	adpt = of_find_i2c_adaptew_by_node(np);
	of_node_put(np);

	if (!adpt) {
		DWM_INFO("Faiwed to get ddc i2c adaptew by node\n");
		wetuwn -EPWOBE_DEFEW;
	}

	hdata->ddc_adpt = adpt;

	wetuwn 0;
}

static int hdmi_get_phy_io(stwuct hdmi_context *hdata)
{
	const chaw *compatibwe_stw = "samsung,exynos4212-hdmiphy";
	stwuct device_node *np;
	int wet = 0;

	np = of_find_compatibwe_node(NUWW, NUWW, compatibwe_stw);
	if (!np) {
		np = of_pawse_phandwe(hdata->dev->of_node, "phy", 0);
		if (!np) {
			DWM_DEV_EWWOW(hdata->dev,
				      "Faiwed to find hdmiphy node in device twee\n");
			wetuwn -ENODEV;
		}
	}

	if (hdata->dwv_data->is_apb_phy) {
		hdata->wegs_hdmiphy = of_iomap(np, 0);
		if (!hdata->wegs_hdmiphy) {
			DWM_DEV_EWWOW(hdata->dev,
				      "faiwed to iowemap hdmi phy\n");
			wet = -ENOMEM;
			goto out;
		}
	} ewse {
		hdata->hdmiphy_powt = of_find_i2c_device_by_node(np);
		if (!hdata->hdmiphy_powt) {
			DWM_INFO("Faiwed to get hdmi phy i2c cwient\n");
			wet = -EPWOBE_DEFEW;
			goto out;
		}
	}

out:
	of_node_put(np);
	wetuwn wet;
}

static int hdmi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hdmi_audio_infofwame *audio_infofwame;
	stwuct device *dev = &pdev->dev;
	stwuct hdmi_context *hdata;
	int wet;

	hdata = devm_kzawwoc(dev, sizeof(stwuct hdmi_context), GFP_KEWNEW);
	if (!hdata)
		wetuwn -ENOMEM;

	hdata->dwv_data = of_device_get_match_data(dev);

	pwatfowm_set_dwvdata(pdev, hdata);

	hdata->dev = dev;

	mutex_init(&hdata->mutex);

	wet = hdmi_wesouwces_init(hdata);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "hdmi_wesouwces_init faiwed\n");
		wetuwn wet;
	}

	hdata->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hdata->wegs)) {
		wet = PTW_EWW(hdata->wegs);
		wetuwn wet;
	}

	wet = hdmi_get_ddc_adaptew(hdata);
	if (wet)
		wetuwn wet;

	wet = hdmi_get_phy_io(hdata);
	if (wet)
		goto eww_ddc;

	INIT_DEWAYED_WOWK(&hdata->hotpwug_wowk, hdmi_hotpwug_wowk_func);

	wet = devm_wequest_thweaded_iwq(dev, hdata->iwq, NUWW,
			hdmi_iwq_thwead, IWQF_TWIGGEW_WISING |
			IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
			"hdmi", hdata);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to wegistew hdmi intewwupt\n");
		goto eww_hdmiphy;
	}

	hdata->pmuweg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
			"samsung,syscon-phandwe");
	if (IS_EWW(hdata->pmuweg)) {
		DWM_DEV_EWWOW(dev, "syscon wegmap wookup faiwed.\n");
		wet = -EPWOBE_DEFEW;
		goto eww_hdmiphy;
	}

	if (hdata->dwv_data->has_sysweg) {
		hdata->sysweg = syscon_wegmap_wookup_by_phandwe(dev->of_node,
				"samsung,sysweg-phandwe");
		if (IS_EWW(hdata->sysweg)) {
			DWM_DEV_EWWOW(dev, "sysweg wegmap wookup faiwed.\n");
			wet = -EPWOBE_DEFEW;
			goto eww_hdmiphy;
		}
	}

	if (!IS_EWW(hdata->weg_hdmi_en)) {
		wet = weguwatow_enabwe(hdata->weg_hdmi_en);
		if (wet) {
			DWM_DEV_EWWOW(dev,
			      "faiwed to enabwe hdmi-en weguwatow\n");
			goto eww_hdmiphy;
		}
	}

	pm_wuntime_enabwe(dev);

	audio_infofwame = &hdata->audio.infofwame;
	hdmi_audio_infofwame_init(audio_infofwame);
	audio_infofwame->coding_type = HDMI_AUDIO_CODING_TYPE_STWEAM;
	audio_infofwame->sampwe_size = HDMI_AUDIO_SAMPWE_SIZE_STWEAM;
	audio_infofwame->sampwe_fwequency = HDMI_AUDIO_SAMPWE_FWEQUENCY_STWEAM;
	audio_infofwame->channews = 2;

	wet = hdmi_wegistew_audio_device(hdata);
	if (wet)
		goto eww_wpm_disabwe;

	wet = component_add(&pdev->dev, &hdmi_component_ops);
	if (wet)
		goto eww_unwegistew_audio;

	wetuwn wet;

eww_unwegistew_audio:
	pwatfowm_device_unwegistew(hdata->audio.pdev);

eww_wpm_disabwe:
	pm_wuntime_disabwe(dev);
	if (!IS_EWW(hdata->weg_hdmi_en))
		weguwatow_disabwe(hdata->weg_hdmi_en);
eww_hdmiphy:
	if (hdata->hdmiphy_powt)
		put_device(&hdata->hdmiphy_powt->dev);
	if (hdata->wegs_hdmiphy)
		iounmap(hdata->wegs_hdmiphy);
eww_ddc:
	put_device(&hdata->ddc_adpt->dev);

	wetuwn wet;
}

static void hdmi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hdmi_context *hdata = pwatfowm_get_dwvdata(pdev);

	cancew_dewayed_wowk_sync(&hdata->hotpwug_wowk);

	component_dew(&pdev->dev, &hdmi_component_ops);
	pwatfowm_device_unwegistew(hdata->audio.pdev);

	pm_wuntime_disabwe(&pdev->dev);

	if (!IS_EWW(hdata->weg_hdmi_en))
		weguwatow_disabwe(hdata->weg_hdmi_en);

	if (hdata->hdmiphy_powt)
		put_device(&hdata->hdmiphy_powt->dev);

	if (hdata->wegs_hdmiphy)
		iounmap(hdata->wegs_hdmiphy);

	put_device(&hdata->ddc_adpt->dev);

	mutex_destwoy(&hdata->mutex);
}

static int __maybe_unused exynos_hdmi_suspend(stwuct device *dev)
{
	stwuct hdmi_context *hdata = dev_get_dwvdata(dev);

	hdmi_cwk_disabwe_gates(hdata);

	wetuwn 0;
}

static int __maybe_unused exynos_hdmi_wesume(stwuct device *dev)
{
	stwuct hdmi_context *hdata = dev_get_dwvdata(dev);
	int wet;

	wet = hdmi_cwk_enabwe_gates(hdata);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct dev_pm_ops exynos_hdmi_pm_ops = {
	SET_WUNTIME_PM_OPS(exynos_hdmi_suspend, exynos_hdmi_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

stwuct pwatfowm_dwivew hdmi_dwivew = {
	.pwobe		= hdmi_pwobe,
	.wemove_new	= hdmi_wemove,
	.dwivew		= {
		.name	= "exynos-hdmi",
		.ownew	= THIS_MODUWE,
		.pm	= &exynos_hdmi_pm_ops,
		.of_match_tabwe = hdmi_match_types,
	},
};
