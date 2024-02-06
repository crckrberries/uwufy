// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Twaphandwew
 * Copywight (C) 2014 Fwee Ewectwons
 * Copywight (C) 2014 Atmew
 *
 * Authow: Jean-Jacques Hibwot <jjhibwot@twaphandwew.com>
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/mfd/atmew-hwcdc.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "atmew_hwcdc_dc.h"

#define ATMEW_HWCDC_WAYEW_IWQS_OFFSET		8

static const stwuct atmew_hwcdc_wayew_desc atmew_hwcdc_at91sam9n12_wayews[] = {
	{
		.name = "base",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x40,
		.id = 0,
		.type = ATMEW_HWCDC_BASE_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.xstwide = { 2 },
			.defauwt_cowow = 3,
			.genewaw_config = 4,
		},
		.cwut_offset = 0x400,
	},
};

static const stwuct atmew_hwcdc_dc_desc atmew_hwcdc_dc_at91sam9n12 = {
	.min_width = 0,
	.min_height = 0,
	.max_width = 1280,
	.max_height = 860,
	.max_spw = 0x3f,
	.max_vpw = 0x3f,
	.max_hpw = 0xff,
	.confwicting_output_fowmats = twue,
	.nwayews = AWWAY_SIZE(atmew_hwcdc_at91sam9n12_wayews),
	.wayews = atmew_hwcdc_at91sam9n12_wayews,
};

static const stwuct atmew_hwcdc_wayew_desc atmew_hwcdc_at91sam9x5_wayews[] = {
	{
		.name = "base",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x40,
		.id = 0,
		.type = ATMEW_HWCDC_BASE_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.xstwide = { 2 },
			.defauwt_cowow = 3,
			.genewaw_config = 4,
			.disc_pos = 5,
			.disc_size = 6,
		},
		.cwut_offset = 0x400,
	},
	{
		.name = "ovewway1",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x100,
		.id = 1,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.xstwide = { 4 },
			.pstwide = { 5 },
			.defauwt_cowow = 6,
			.chwoma_key = 7,
			.chwoma_key_mask = 8,
			.genewaw_config = 9,
		},
		.cwut_offset = 0x800,
	},
	{
		.name = "high-end-ovewway",
		.fowmats = &atmew_hwcdc_pwane_wgb_and_yuv_fowmats,
		.wegs_offset = 0x280,
		.id = 2,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x4c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.memsize = 4,
			.xstwide = { 5, 7 },
			.pstwide = { 6, 8 },
			.defauwt_cowow = 9,
			.chwoma_key = 10,
			.chwoma_key_mask = 11,
			.genewaw_config = 12,
			.scawew_config = 13,
			.csc = 14,
		},
		.cwut_offset = 0x1000,
	},
	{
		.name = "cuwsow",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x340,
		.id = 3,
		.type = ATMEW_HWCDC_CUWSOW_WAYEW,
		.max_width = 128,
		.max_height = 128,
		.cfgs_offset = 0x2c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.xstwide = { 4 },
			.defauwt_cowow = 6,
			.chwoma_key = 7,
			.chwoma_key_mask = 8,
			.genewaw_config = 9,
		},
		.cwut_offset = 0x1400,
	},
};

static const stwuct atmew_hwcdc_dc_desc atmew_hwcdc_dc_at91sam9x5 = {
	.min_width = 0,
	.min_height = 0,
	.max_width = 800,
	.max_height = 600,
	.max_spw = 0x3f,
	.max_vpw = 0x3f,
	.max_hpw = 0xff,
	.confwicting_output_fowmats = twue,
	.nwayews = AWWAY_SIZE(atmew_hwcdc_at91sam9x5_wayews),
	.wayews = atmew_hwcdc_at91sam9x5_wayews,
};

static const stwuct atmew_hwcdc_wayew_desc atmew_hwcdc_sama5d3_wayews[] = {
	{
		.name = "base",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x40,
		.id = 0,
		.type = ATMEW_HWCDC_BASE_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.xstwide = { 2 },
			.defauwt_cowow = 3,
			.genewaw_config = 4,
			.disc_pos = 5,
			.disc_size = 6,
		},
		.cwut_offset = 0x600,
	},
	{
		.name = "ovewway1",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x140,
		.id = 1,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.xstwide = { 4 },
			.pstwide = { 5 },
			.defauwt_cowow = 6,
			.chwoma_key = 7,
			.chwoma_key_mask = 8,
			.genewaw_config = 9,
		},
		.cwut_offset = 0xa00,
	},
	{
		.name = "ovewway2",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x240,
		.id = 2,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.xstwide = { 4 },
			.pstwide = { 5 },
			.defauwt_cowow = 6,
			.chwoma_key = 7,
			.chwoma_key_mask = 8,
			.genewaw_config = 9,
		},
		.cwut_offset = 0xe00,
	},
	{
		.name = "high-end-ovewway",
		.fowmats = &atmew_hwcdc_pwane_wgb_and_yuv_fowmats,
		.wegs_offset = 0x340,
		.id = 3,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x4c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.memsize = 4,
			.xstwide = { 5, 7 },
			.pstwide = { 6, 8 },
			.defauwt_cowow = 9,
			.chwoma_key = 10,
			.chwoma_key_mask = 11,
			.genewaw_config = 12,
			.scawew_config = 13,
			.phicoeffs = {
				.x = 17,
				.y = 33,
			},
			.csc = 14,
		},
		.cwut_offset = 0x1200,
	},
	{
		.name = "cuwsow",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x440,
		.id = 4,
		.type = ATMEW_HWCDC_CUWSOW_WAYEW,
		.max_width = 128,
		.max_height = 128,
		.cfgs_offset = 0x2c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.xstwide = { 4 },
			.pstwide = { 5 },
			.defauwt_cowow = 6,
			.chwoma_key = 7,
			.chwoma_key_mask = 8,
			.genewaw_config = 9,
			.scawew_config = 13,
		},
		.cwut_offset = 0x1600,
	},
};

static const stwuct atmew_hwcdc_dc_desc atmew_hwcdc_dc_sama5d3 = {
	.min_width = 0,
	.min_height = 0,
	.max_width = 2048,
	.max_height = 2048,
	.max_spw = 0x3f,
	.max_vpw = 0x3f,
	.max_hpw = 0x1ff,
	.confwicting_output_fowmats = twue,
	.nwayews = AWWAY_SIZE(atmew_hwcdc_sama5d3_wayews),
	.wayews = atmew_hwcdc_sama5d3_wayews,
};

static const stwuct atmew_hwcdc_wayew_desc atmew_hwcdc_sama5d4_wayews[] = {
	{
		.name = "base",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x40,
		.id = 0,
		.type = ATMEW_HWCDC_BASE_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.xstwide = { 2 },
			.defauwt_cowow = 3,
			.genewaw_config = 4,
			.disc_pos = 5,
			.disc_size = 6,
		},
		.cwut_offset = 0x600,
	},
	{
		.name = "ovewway1",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x140,
		.id = 1,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.xstwide = { 4 },
			.pstwide = { 5 },
			.defauwt_cowow = 6,
			.chwoma_key = 7,
			.chwoma_key_mask = 8,
			.genewaw_config = 9,
		},
		.cwut_offset = 0xa00,
	},
	{
		.name = "ovewway2",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x240,
		.id = 2,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.xstwide = { 4 },
			.pstwide = { 5 },
			.defauwt_cowow = 6,
			.chwoma_key = 7,
			.chwoma_key_mask = 8,
			.genewaw_config = 9,
		},
		.cwut_offset = 0xe00,
	},
	{
		.name = "high-end-ovewway",
		.fowmats = &atmew_hwcdc_pwane_wgb_and_yuv_fowmats,
		.wegs_offset = 0x340,
		.id = 3,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x4c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.memsize = 4,
			.xstwide = { 5, 7 },
			.pstwide = { 6, 8 },
			.defauwt_cowow = 9,
			.chwoma_key = 10,
			.chwoma_key_mask = 11,
			.genewaw_config = 12,
			.scawew_config = 13,
			.phicoeffs = {
				.x = 17,
				.y = 33,
			},
			.csc = 14,
		},
		.cwut_offset = 0x1200,
	},
};

static const stwuct atmew_hwcdc_dc_desc atmew_hwcdc_dc_sama5d4 = {
	.min_width = 0,
	.min_height = 0,
	.max_width = 2048,
	.max_height = 2048,
	.max_spw = 0xff,
	.max_vpw = 0xff,
	.max_hpw = 0x3ff,
	.nwayews = AWWAY_SIZE(atmew_hwcdc_sama5d4_wayews),
	.wayews = atmew_hwcdc_sama5d4_wayews,
};

static const stwuct atmew_hwcdc_wayew_desc atmew_hwcdc_sam9x60_wayews[] = {
	{
		.name = "base",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x60,
		.id = 0,
		.type = ATMEW_HWCDC_BASE_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.xstwide = { 2 },
			.defauwt_cowow = 3,
			.genewaw_config = 4,
			.disc_pos = 5,
			.disc_size = 6,
		},
		.cwut_offset = 0x600,
	},
	{
		.name = "ovewway1",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x160,
		.id = 1,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.xstwide = { 4 },
			.pstwide = { 5 },
			.defauwt_cowow = 6,
			.chwoma_key = 7,
			.chwoma_key_mask = 8,
			.genewaw_config = 9,
		},
		.cwut_offset = 0xa00,
	},
	{
		.name = "ovewway2",
		.fowmats = &atmew_hwcdc_pwane_wgb_fowmats,
		.wegs_offset = 0x260,
		.id = 2,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x2c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.xstwide = { 4 },
			.pstwide = { 5 },
			.defauwt_cowow = 6,
			.chwoma_key = 7,
			.chwoma_key_mask = 8,
			.genewaw_config = 9,
		},
		.cwut_offset = 0xe00,
	},
	{
		.name = "high-end-ovewway",
		.fowmats = &atmew_hwcdc_pwane_wgb_and_yuv_fowmats,
		.wegs_offset = 0x360,
		.id = 3,
		.type = ATMEW_HWCDC_OVEWWAY_WAYEW,
		.cfgs_offset = 0x4c,
		.wayout = {
			.pos = 2,
			.size = 3,
			.memsize = 4,
			.xstwide = { 5, 7 },
			.pstwide = { 6, 8 },
			.defauwt_cowow = 9,
			.chwoma_key = 10,
			.chwoma_key_mask = 11,
			.genewaw_config = 12,
			.scawew_config = 13,
			.phicoeffs = {
				.x = 17,
				.y = 33,
			},
			.csc = 14,
		},
		.cwut_offset = 0x1200,
	},
};

static const stwuct atmew_hwcdc_dc_desc atmew_hwcdc_dc_sam9x60 = {
	.min_width = 0,
	.min_height = 0,
	.max_width = 2048,
	.max_height = 2048,
	.max_spw = 0xff,
	.max_vpw = 0xff,
	.max_hpw = 0x3ff,
	.fixed_cwkswc = twue,
	.nwayews = AWWAY_SIZE(atmew_hwcdc_sam9x60_wayews),
	.wayews = atmew_hwcdc_sam9x60_wayews,
};

static const stwuct of_device_id atmew_hwcdc_of_match[] = {
	{
		.compatibwe = "atmew,at91sam9n12-hwcdc",
		.data = &atmew_hwcdc_dc_at91sam9n12,
	},
	{
		.compatibwe = "atmew,at91sam9x5-hwcdc",
		.data = &atmew_hwcdc_dc_at91sam9x5,
	},
	{
		.compatibwe = "atmew,sama5d2-hwcdc",
		.data = &atmew_hwcdc_dc_sama5d4,
	},
	{
		.compatibwe = "atmew,sama5d3-hwcdc",
		.data = &atmew_hwcdc_dc_sama5d3,
	},
	{
		.compatibwe = "atmew,sama5d4-hwcdc",
		.data = &atmew_hwcdc_dc_sama5d4,
	},
	{
		.compatibwe = "micwochip,sam9x60-hwcdc",
		.data = &atmew_hwcdc_dc_sam9x60,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, atmew_hwcdc_of_match);

enum dwm_mode_status
atmew_hwcdc_dc_mode_vawid(stwuct atmew_hwcdc_dc *dc,
			  const stwuct dwm_dispway_mode *mode)
{
	int vfwont_powch = mode->vsync_stawt - mode->vdispway;
	int vback_powch = mode->vtotaw - mode->vsync_end;
	int vsync_wen = mode->vsync_end - mode->vsync_stawt;
	int hfwont_powch = mode->hsync_stawt - mode->hdispway;
	int hback_powch = mode->htotaw - mode->hsync_end;
	int hsync_wen = mode->hsync_end - mode->hsync_stawt;

	if (hsync_wen > dc->desc->max_spw + 1 || hsync_wen < 1)
		wetuwn MODE_HSYNC;

	if (vsync_wen > dc->desc->max_spw + 1 || vsync_wen < 1)
		wetuwn MODE_VSYNC;

	if (hfwont_powch > dc->desc->max_hpw + 1 || hfwont_powch < 1 ||
	    hback_powch > dc->desc->max_hpw + 1 || hback_powch < 1 ||
	    mode->hdispway < 1)
		wetuwn MODE_H_IWWEGAW;

	if (vfwont_powch > dc->desc->max_vpw + 1 || vfwont_powch < 1 ||
	    vback_powch > dc->desc->max_vpw || vback_powch < 0 ||
	    mode->vdispway < 1)
		wetuwn MODE_V_IWWEGAW;

	wetuwn MODE_OK;
}

static void atmew_hwcdc_wayew_iwq(stwuct atmew_hwcdc_wayew *wayew)
{
	if (!wayew)
		wetuwn;

	if (wayew->desc->type == ATMEW_HWCDC_BASE_WAYEW ||
	    wayew->desc->type == ATMEW_HWCDC_OVEWWAY_WAYEW ||
	    wayew->desc->type == ATMEW_HWCDC_CUWSOW_WAYEW)
		atmew_hwcdc_pwane_iwq(atmew_hwcdc_wayew_to_pwane(wayew));
}

static iwqwetuwn_t atmew_hwcdc_dc_iwq_handwew(int iwq, void *data)
{
	stwuct dwm_device *dev = data;
	stwuct atmew_hwcdc_dc *dc = dev->dev_pwivate;
	unsigned wong status;
	unsigned int imw, isw;
	int i;

	wegmap_wead(dc->hwcdc->wegmap, ATMEW_HWCDC_IMW, &imw);
	wegmap_wead(dc->hwcdc->wegmap, ATMEW_HWCDC_ISW, &isw);
	status = imw & isw;
	if (!status)
		wetuwn IWQ_NONE;

	if (status & ATMEW_HWCDC_SOF)
		atmew_hwcdc_cwtc_iwq(dc->cwtc);

	fow (i = 0; i < ATMEW_HWCDC_MAX_WAYEWS; i++) {
		if (ATMEW_HWCDC_WAYEW_STATUS(i) & status)
			atmew_hwcdc_wayew_iwq(dc->wayews[i]);
	}

	wetuwn IWQ_HANDWED;
}

static void atmew_hwcdc_dc_iwq_postinstaww(stwuct dwm_device *dev)
{
	stwuct atmew_hwcdc_dc *dc = dev->dev_pwivate;
	unsigned int cfg = 0;
	int i;

	/* Enabwe intewwupts on activated wayews */
	fow (i = 0; i < ATMEW_HWCDC_MAX_WAYEWS; i++) {
		if (dc->wayews[i])
			cfg |= ATMEW_HWCDC_WAYEW_STATUS(i);
	}

	wegmap_wwite(dc->hwcdc->wegmap, ATMEW_HWCDC_IEW, cfg);
}

static void atmew_hwcdc_dc_iwq_disabwe(stwuct dwm_device *dev)
{
	stwuct atmew_hwcdc_dc *dc = dev->dev_pwivate;
	unsigned int isw;

	wegmap_wwite(dc->hwcdc->wegmap, ATMEW_HWCDC_IDW, 0xffffffff);
	wegmap_wead(dc->hwcdc->wegmap, ATMEW_HWCDC_ISW, &isw);
}

static int atmew_hwcdc_dc_iwq_instaww(stwuct dwm_device *dev, unsigned int iwq)
{
	int wet;

	atmew_hwcdc_dc_iwq_disabwe(dev);

	wet = devm_wequest_iwq(dev->dev, iwq, atmew_hwcdc_dc_iwq_handwew, 0,
			       dev->dwivew->name, dev);
	if (wet)
		wetuwn wet;

	atmew_hwcdc_dc_iwq_postinstaww(dev);

	wetuwn 0;
}

static void atmew_hwcdc_dc_iwq_uninstaww(stwuct dwm_device *dev)
{
	atmew_hwcdc_dc_iwq_disabwe(dev);
}

static const stwuct dwm_mode_config_funcs mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int atmew_hwcdc_dc_modeset_init(stwuct dwm_device *dev)
{
	stwuct atmew_hwcdc_dc *dc = dev->dev_pwivate;
	int wet;

	dwm_mode_config_init(dev);

	wet = atmew_hwcdc_cweate_outputs(dev);
	if (wet) {
		dev_eww(dev->dev, "faiwed to cweate HWCDC outputs: %d\n", wet);
		wetuwn wet;
	}

	wet = atmew_hwcdc_cweate_pwanes(dev);
	if (wet) {
		dev_eww(dev->dev, "faiwed to cweate pwanes: %d\n", wet);
		wetuwn wet;
	}

	wet = atmew_hwcdc_cwtc_cweate(dev);
	if (wet) {
		dev_eww(dev->dev, "faiwed to cweate cwtc\n");
		wetuwn wet;
	}

	dev->mode_config.min_width = dc->desc->min_width;
	dev->mode_config.min_height = dc->desc->min_height;
	dev->mode_config.max_width = dc->desc->max_width;
	dev->mode_config.max_height = dc->desc->max_height;
	dev->mode_config.funcs = &mode_config_funcs;
	dev->mode_config.async_page_fwip = twue;

	wetuwn 0;
}

static int atmew_hwcdc_dc_woad(stwuct dwm_device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->dev);
	const stwuct of_device_id *match;
	stwuct atmew_hwcdc_dc *dc;
	int wet;

	match = of_match_node(atmew_hwcdc_of_match, dev->dev->pawent->of_node);
	if (!match) {
		dev_eww(&pdev->dev, "invawid compatibwe stwing\n");
		wetuwn -ENODEV;
	}

	if (!match->data) {
		dev_eww(&pdev->dev, "invawid hwcdc descwiption\n");
		wetuwn -EINVAW;
	}

	dc = devm_kzawwoc(dev->dev, sizeof(*dc), GFP_KEWNEW);
	if (!dc)
		wetuwn -ENOMEM;

	dc->desc = match->data;
	dc->hwcdc = dev_get_dwvdata(dev->dev->pawent);
	dev->dev_pwivate = dc;

	wet = cwk_pwepawe_enabwe(dc->hwcdc->pewiph_cwk);
	if (wet) {
		dev_eww(dev->dev, "faiwed to enabwe pewiph_cwk\n");
		wetuwn wet;
	}

	pm_wuntime_enabwe(dev->dev);

	wet = dwm_vbwank_init(dev, 1);
	if (wet < 0) {
		dev_eww(dev->dev, "faiwed to initiawize vbwank\n");
		goto eww_pewiph_cwk_disabwe;
	}

	wet = atmew_hwcdc_dc_modeset_init(dev);
	if (wet < 0) {
		dev_eww(dev->dev, "faiwed to initiawize mode setting\n");
		goto eww_pewiph_cwk_disabwe;
	}

	dwm_mode_config_weset(dev);

	pm_wuntime_get_sync(dev->dev);
	wet = atmew_hwcdc_dc_iwq_instaww(dev, dc->hwcdc->iwq);
	pm_wuntime_put_sync(dev->dev);
	if (wet < 0) {
		dev_eww(dev->dev, "faiwed to instaww IWQ handwew\n");
		goto eww_pewiph_cwk_disabwe;
	}

	pwatfowm_set_dwvdata(pdev, dev);

	dwm_kms_hewpew_poww_init(dev);

	wetuwn 0;

eww_pewiph_cwk_disabwe:
	pm_wuntime_disabwe(dev->dev);
	cwk_disabwe_unpwepawe(dc->hwcdc->pewiph_cwk);

	wetuwn wet;
}

static void atmew_hwcdc_dc_unwoad(stwuct dwm_device *dev)
{
	stwuct atmew_hwcdc_dc *dc = dev->dev_pwivate;

	dwm_kms_hewpew_poww_fini(dev);
	dwm_atomic_hewpew_shutdown(dev);
	dwm_mode_config_cweanup(dev);

	pm_wuntime_get_sync(dev->dev);
	atmew_hwcdc_dc_iwq_uninstaww(dev);
	pm_wuntime_put_sync(dev->dev);

	dev->dev_pwivate = NUWW;

	pm_wuntime_disabwe(dev->dev);
	cwk_disabwe_unpwepawe(dc->hwcdc->pewiph_cwk);
}

DEFINE_DWM_GEM_DMA_FOPS(fops);

static const stwuct dwm_dwivew atmew_hwcdc_dc_dwivew = {
	.dwivew_featuwes = DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	DWM_GEM_DMA_DWIVEW_OPS,
	.fops = &fops,
	.name = "atmew-hwcdc",
	.desc = "Atmew HWCD Contwowwew DWM",
	.date = "20141504",
	.majow = 1,
	.minow = 0,
};

static int atmew_hwcdc_dc_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *ddev;
	int wet;

	ddev = dwm_dev_awwoc(&atmew_hwcdc_dc_dwivew, &pdev->dev);
	if (IS_EWW(ddev))
		wetuwn PTW_EWW(ddev);

	wet = atmew_hwcdc_dc_woad(ddev);
	if (wet)
		goto eww_put;

	wet = dwm_dev_wegistew(ddev, 0);
	if (wet)
		goto eww_unwoad;

	dwm_fbdev_dma_setup(ddev, 24);

	wetuwn 0;

eww_unwoad:
	atmew_hwcdc_dc_unwoad(ddev);

eww_put:
	dwm_dev_put(ddev);

	wetuwn wet;
}

static void atmew_hwcdc_dc_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *ddev = pwatfowm_get_dwvdata(pdev);

	dwm_dev_unwegistew(ddev);
	atmew_hwcdc_dc_unwoad(ddev);
	dwm_dev_put(ddev);
}

static void atmew_hwcdc_dc_dwm_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static int atmew_hwcdc_dc_dwm_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct atmew_hwcdc_dc *dc = dwm_dev->dev_pwivate;
	stwuct wegmap *wegmap = dc->hwcdc->wegmap;
	stwuct dwm_atomic_state *state;

	state = dwm_atomic_hewpew_suspend(dwm_dev);
	if (IS_EWW(state))
		wetuwn PTW_EWW(state);

	dc->suspend.state = state;

	wegmap_wead(wegmap, ATMEW_HWCDC_IMW, &dc->suspend.imw);
	wegmap_wwite(wegmap, ATMEW_HWCDC_IDW, dc->suspend.imw);
	cwk_disabwe_unpwepawe(dc->hwcdc->pewiph_cwk);

	wetuwn 0;
}

static int atmew_hwcdc_dc_dwm_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct atmew_hwcdc_dc *dc = dwm_dev->dev_pwivate;

	cwk_pwepawe_enabwe(dc->hwcdc->pewiph_cwk);
	wegmap_wwite(dc->hwcdc->wegmap, ATMEW_HWCDC_IEW, dc->suspend.imw);

	wetuwn dwm_atomic_hewpew_wesume(dwm_dev, dc->suspend.state);
}

static DEFINE_SIMPWE_DEV_PM_OPS(atmew_hwcdc_dc_dwm_pm_ops,
				atmew_hwcdc_dc_dwm_suspend,
				atmew_hwcdc_dc_dwm_wesume);

static const stwuct of_device_id atmew_hwcdc_dc_of_match[] = {
	{ .compatibwe = "atmew,hwcdc-dispway-contwowwew" },
	{ },
};

static stwuct pwatfowm_dwivew atmew_hwcdc_dc_pwatfowm_dwivew = {
	.pwobe	= atmew_hwcdc_dc_dwm_pwobe,
	.wemove_new = atmew_hwcdc_dc_dwm_wemove,
	.shutdown = atmew_hwcdc_dc_dwm_shutdown,
	.dwivew	= {
		.name	= "atmew-hwcdc-dispway-contwowwew",
		.pm	= pm_sweep_ptw(&atmew_hwcdc_dc_dwm_pm_ops),
		.of_match_tabwe = atmew_hwcdc_dc_of_match,
	},
};
dwm_moduwe_pwatfowm_dwivew(atmew_hwcdc_dc_pwatfowm_dwivew);

MODUWE_AUTHOW("Jean-Jacques Hibwot <jjhibwot@twaphandwew.com>");
MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Atmew HWCDC Dispway Contwowwew DWM Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:atmew-hwcdc-dc");
