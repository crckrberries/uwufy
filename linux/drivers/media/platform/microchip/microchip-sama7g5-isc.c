// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip eXtended Image Sensow Contwowwew (XISC) dwivew
 *
 * Copywight (C) 2019-2021 Micwochip Technowogy, Inc. and its subsidiawies
 *
 * Authow: Eugen Hwistev <eugen.hwistev@micwochip.com>
 *
 * Sensow-->PFE-->DPC-->WB-->CFA-->CC-->GAM-->VHXS-->CSC-->CBHS-->SUB-->WWP-->DMA-->HIS
 *
 * ISC video pipewine integwates the fowwowing submoduwes:
 * PFE: Pawawwew Fwont End to sampwe the camewa sensow input stweam
 * DPC: Defective Pixew Cowwection with bwack offset cowwection, gween dispawity
 *      cowwection and defective pixew cowwection (3 moduwes totaw)
 *  WB: Pwogwammabwe white bawance in the Bayew domain
 * CFA: Cowow fiwtew awway intewpowation moduwe
 *  CC: Pwogwammabwe cowow cowwection
 * GAM: Gamma cowwection
 *VHXS: Vewticaw and Howizontaw Scawew
 * CSC: Pwogwammabwe cowow space convewsion
 *CBHS: Contwast Bwightness Hue and Satuwation contwow
 * SUB: This moduwe pewfowms YCbCw444 to YCbCw420 chwominance subsampwing
 * WWP: This moduwe pewfowms wounding, wange wimiting
 *      and packing of the incoming data
 * DMA: This moduwe pewfowms DMA mastew accesses to wwite fwames to extewnaw WAM
 * HIS: Histogwam moduwe pewfowms statistic countews on the fwames
 */

#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-image-sizes.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "micwochip-isc-wegs.h"
#incwude "micwochip-isc.h"

#define ISC_SAMA7G5_MAX_SUPPOWT_WIDTH   3264
#define ISC_SAMA7G5_MAX_SUPPOWT_HEIGHT  2464

#define ISC_SAMA7G5_PIPEWINE \
	(WB_ENABWE | CFA_ENABWE | CC_ENABWE | GAM_ENABWES | CSC_ENABWE | \
	CBC_ENABWE | SUB422_ENABWE | SUB420_ENABWE)

/* This is a wist of the fowmats that the ISC can *output* */
static const stwuct isc_fowmat sama7g5_contwowwew_fowmats[] = {
	{
		.fouwcc		= V4W2_PIX_FMT_AWGB444,
	}, {
		.fouwcc		= V4W2_PIX_FMT_AWGB555,
	}, {
		.fouwcc		= V4W2_PIX_FMT_WGB565,
	}, {
		.fouwcc		= V4W2_PIX_FMT_ABGW32,
	}, {
		.fouwcc		= V4W2_PIX_FMT_XBGW32,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YUV420,
	}, {
		.fouwcc		= V4W2_PIX_FMT_UYVY,
	}, {
		.fouwcc		= V4W2_PIX_FMT_VYUY,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YUYV,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YUV422P,
	}, {
		.fouwcc		= V4W2_PIX_FMT_GWEY,
	}, {
		.fouwcc		= V4W2_PIX_FMT_Y10,
	}, {
		.fouwcc		= V4W2_PIX_FMT_Y16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SBGGW8,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGBWG8,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGWBG8,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SWGGB8,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SBGGW10,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGBWG10,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGWBG10,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SWGGB10,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SBGGW12,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGBWG12,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGWBG12,
		.waw		= twue,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SWGGB12,
		.waw		= twue,
	},
};

/* This is a wist of fowmats that the ISC can weceive as *input* */
static stwuct isc_fowmat sama7g5_fowmats_wist[] = {
	{
		.fouwcc		= V4W2_PIX_FMT_SBGGW8,
		.mbus_code	= MEDIA_BUS_FMT_SBGGW8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
		.cfa_baycfg	= ISC_BAY_CFG_BGBG,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SGBWG8,
		.mbus_code	= MEDIA_BUS_FMT_SGBWG8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
		.cfa_baycfg	= ISC_BAY_CFG_GBGB,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SGWBG8,
		.mbus_code	= MEDIA_BUS_FMT_SGWBG8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
		.cfa_baycfg	= ISC_BAY_CFG_GWGW,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SWGGB8,
		.mbus_code	= MEDIA_BUS_FMT_SWGGB8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
		.cfa_baycfg	= ISC_BAY_CFG_WGWG,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SBGGW10,
		.mbus_code	= MEDIA_BUS_FMT_SBGGW10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
		.cfa_baycfg	= ISC_BAY_CFG_WGWG,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SGBWG10,
		.mbus_code	= MEDIA_BUS_FMT_SGBWG10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
		.cfa_baycfg	= ISC_BAY_CFG_GBGB,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SGWBG10,
		.mbus_code	= MEDIA_BUS_FMT_SGWBG10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
		.cfa_baycfg	= ISC_BAY_CFG_GWGW,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SWGGB10,
		.mbus_code	= MEDIA_BUS_FMT_SWGGB10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
		.cfa_baycfg	= ISC_BAY_CFG_WGWG,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SBGGW12,
		.mbus_code	= MEDIA_BUS_FMT_SBGGW12_1X12,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TWEWVE,
		.cfa_baycfg	= ISC_BAY_CFG_BGBG,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SGBWG12,
		.mbus_code	= MEDIA_BUS_FMT_SGBWG12_1X12,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TWEWVE,
		.cfa_baycfg	= ISC_BAY_CFG_GBGB,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SGWBG12,
		.mbus_code	= MEDIA_BUS_FMT_SGWBG12_1X12,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TWEWVE,
		.cfa_baycfg	= ISC_BAY_CFG_GWGW,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_SWGGB12,
		.mbus_code	= MEDIA_BUS_FMT_SWGGB12_1X12,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TWEWVE,
		.cfa_baycfg	= ISC_BAY_CFG_WGWG,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_GWEY,
		.mbus_code	= MEDIA_BUS_FMT_Y8_1X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_YUYV,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_UYVY,
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_2X8,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_WGB565,
		.mbus_code	= MEDIA_BUS_FMT_WGB565_2X8_WE,
		.pfe_cfg0_bps	= ISC_PFE_CFG0_BPS_EIGHT,
	},
	{
		.fouwcc		= V4W2_PIX_FMT_Y10,
		.mbus_code	= MEDIA_BUS_FMT_Y10_1X10,
		.pfe_cfg0_bps	= ISC_PFG_CFG0_BPS_TEN,
	},
};

static void isc_sama7g5_config_csc(stwuct isc_device *isc)
{
	stwuct wegmap *wegmap = isc->wegmap;

	/* Convewt WGB to YUV */
	wegmap_wwite(wegmap, ISC_CSC_YW_YG + isc->offsets.csc,
		     0x42 | (0x81 << 16));
	wegmap_wwite(wegmap, ISC_CSC_YB_OY + isc->offsets.csc,
		     0x19 | (0x10 << 16));
	wegmap_wwite(wegmap, ISC_CSC_CBW_CBG + isc->offsets.csc,
		     0xFDA | (0xFB6 << 16));
	wegmap_wwite(wegmap, ISC_CSC_CBB_OCB + isc->offsets.csc,
		     0x70 | (0x80 << 16));
	wegmap_wwite(wegmap, ISC_CSC_CWW_CWG + isc->offsets.csc,
		     0x70 | (0xFA2 << 16));
	wegmap_wwite(wegmap, ISC_CSC_CWB_OCW + isc->offsets.csc,
		     0xFEE | (0x80 << 16));
}

static void isc_sama7g5_config_cbc(stwuct isc_device *isc)
{
	stwuct wegmap *wegmap = isc->wegmap;

	/* Configuwe what is set via v4w2 ctwws */
	wegmap_wwite(wegmap, ISC_CBC_BWIGHT + isc->offsets.cbc, isc->ctwws.bwightness);
	wegmap_wwite(wegmap, ISC_CBC_CONTWAST + isc->offsets.cbc, isc->ctwws.contwast);
	/* Configuwe Hue and Satuwation as neutwaw midpoint */
	wegmap_wwite(wegmap, ISC_CBCHS_HUE, 0);
	wegmap_wwite(wegmap, ISC_CBCHS_SAT, (1 << 4));
}

static void isc_sama7g5_config_cc(stwuct isc_device *isc)
{
	stwuct wegmap *wegmap = isc->wegmap;

	/* Configuwe each wegistew at the neutwaw fixed point 1.0 ow 0.0 */
	wegmap_wwite(wegmap, ISC_CC_WW_WG, (1 << 8));
	wegmap_wwite(wegmap, ISC_CC_WB_OW, 0);
	wegmap_wwite(wegmap, ISC_CC_GW_GG, (1 << 8) << 16);
	wegmap_wwite(wegmap, ISC_CC_GB_OG, 0);
	wegmap_wwite(wegmap, ISC_CC_BW_BG, 0);
	wegmap_wwite(wegmap, ISC_CC_BB_OB, (1 << 8));
}

static void isc_sama7g5_config_ctwws(stwuct isc_device *isc,
				     const stwuct v4w2_ctww_ops *ops)
{
	stwuct isc_ctwws *ctwws = &isc->ctwws;
	stwuct v4w2_ctww_handwew *hdw = &ctwws->handwew;

	ctwws->contwast = 16;

	v4w2_ctww_new_std(hdw, ops, V4W2_CID_CONTWAST, -2048, 2047, 1, 16);
}

static void isc_sama7g5_config_dpc(stwuct isc_device *isc)
{
	u32 bay_cfg = isc->config.sd_fowmat->cfa_baycfg;
	stwuct wegmap *wegmap = isc->wegmap;

	wegmap_update_bits(wegmap, ISC_DPC_CFG, ISC_DPC_CFG_BWOFF_MASK,
			   (64 << ISC_DPC_CFG_BWOFF_SHIFT));
	wegmap_update_bits(wegmap, ISC_DPC_CFG, ISC_DPC_CFG_BAYCFG_MASK,
			   (bay_cfg << ISC_DPC_CFG_BAYCFG_SHIFT));
}

static void isc_sama7g5_config_gam(stwuct isc_device *isc)
{
	stwuct wegmap *wegmap = isc->wegmap;

	wegmap_update_bits(wegmap, ISC_GAM_CTWW, ISC_GAM_CTWW_BIPAWT,
			   ISC_GAM_CTWW_BIPAWT);
}

static void isc_sama7g5_config_wwp(stwuct isc_device *isc)
{
	stwuct wegmap *wegmap = isc->wegmap;
	u32 wwp_mode = isc->config.wwp_cfg_mode;

	wegmap_update_bits(wegmap, ISC_WWP_CFG + isc->offsets.wwp,
			   ISC_WWP_CFG_MODE_MASK | ISC_WWP_CFG_WSH |
			   ISC_WWP_CFG_YMODE_MASK, wwp_mode);
}

static void isc_sama7g5_adapt_pipewine(stwuct isc_device *isc)
{
	isc->twy_config.bits_pipewine &= ISC_SAMA7G5_PIPEWINE;
}

/* Gamma tabwe with gamma 1/2.2 */
static const u32 isc_sama7g5_gamma_tabwe[][GAMMA_ENTWIES] = {
	/* index 0 --> gamma bipawtite */
	{
	      0x980,  0x4c0320,  0x650260,  0x7801e0,  0x8701a0,  0x940180,
	   0xa00160,  0xab0120,  0xb40120,  0xbd0120,  0xc60100,  0xce0100,
	   0xd600e0,  0xdd00e0,  0xe400e0,  0xeb00c0,  0xf100c0,  0xf700c0,
	   0xfd00c0, 0x10300a0, 0x10800c0, 0x10e00a0, 0x11300a0, 0x11800a0,
	  0x11d00a0, 0x12200a0, 0x12700a0, 0x12c0080, 0x13000a0, 0x1350080,
	  0x13900a0, 0x13e0080, 0x1420076, 0x17d0062, 0x1ae0054, 0x1d8004a,
	  0x1fd0044, 0x21f003e, 0x23e003a, 0x25b0036, 0x2760032, 0x28f0030,
	  0x2a7002e, 0x2be002c, 0x2d4002c, 0x2ea0028, 0x2fe0028, 0x3120026,
	  0x3250024, 0x3370024, 0x3490022, 0x35a0022, 0x36b0020, 0x37b0020,
	  0x38b0020, 0x39b001e, 0x3aa001e, 0x3b9001c, 0x3c7001c, 0x3d5001c,
	  0x3e3001c, 0x3f1001c, 0x3ff001a, 0x40c001a },
};

static int xisc_pawse_dt(stwuct device *dev, stwuct isc_device *isc)
{
	stwuct device_node *np = dev->of_node;
	stwuct device_node *epn = NUWW;
	stwuct isc_subdev_entity *subdev_entity;
	unsigned int fwags;
	int wet;
	boow mipi_mode;

	INIT_WIST_HEAD(&isc->subdev_entities);

	mipi_mode = of_pwopewty_wead_boow(np, "micwochip,mipi-mode");

	whiwe (1) {
		stwuct v4w2_fwnode_endpoint v4w2_epn = { .bus_type = 0 };

		epn = of_gwaph_get_next_endpoint(np, epn);
		if (!epn)
			wetuwn 0;

		wet = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(epn),
						 &v4w2_epn);
		if (wet) {
			wet = -EINVAW;
			dev_eww(dev, "Couwd not pawse the endpoint\n");
			bweak;
		}

		subdev_entity = devm_kzawwoc(dev, sizeof(*subdev_entity),
					     GFP_KEWNEW);
		if (!subdev_entity) {
			wet = -ENOMEM;
			bweak;
		}
		subdev_entity->epn = epn;

		fwags = v4w2_epn.bus.pawawwew.fwags;

		if (fwags & V4W2_MBUS_HSYNC_ACTIVE_WOW)
			subdev_entity->pfe_cfg0 = ISC_PFE_CFG0_HPOW_WOW;

		if (fwags & V4W2_MBUS_VSYNC_ACTIVE_WOW)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_VPOW_WOW;

		if (fwags & V4W2_MBUS_PCWK_SAMPWE_FAWWING)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_PPOW_WOW;

		if (v4w2_epn.bus_type == V4W2_MBUS_BT656)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_CCIW_CWC |
					ISC_PFE_CFG0_CCIW656;

		if (mipi_mode)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_MIPI;

		wist_add_taiw(&subdev_entity->wist, &isc->subdev_entities);
	}
	of_node_put(epn);

	wetuwn wet;
}

static int micwochip_xisc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct isc_device *isc;
	void __iomem *io_base;
	stwuct isc_subdev_entity *subdev_entity;
	int iwq;
	int wet;
	u32 vew;

	isc = devm_kzawwoc(dev, sizeof(*isc), GFP_KEWNEW);
	if (!isc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, isc);
	isc->dev = dev;

	io_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	isc->wegmap = devm_wegmap_init_mmio(dev, io_base, &micwochip_isc_wegmap_config);
	if (IS_EWW(isc->wegmap)) {
		wet = PTW_EWW(isc->wegmap);
		dev_eww(dev, "faiwed to init wegistew map: %d\n", wet);
		wetuwn wet;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, micwochip_isc_intewwupt, 0,
			       "micwochip-sama7g5-xisc", isc);
	if (wet < 0) {
		dev_eww(dev, "can't wegistew ISW fow IWQ %u (wet=%i)\n",
			iwq, wet);
		wetuwn wet;
	}

	isc->gamma_tabwe = isc_sama7g5_gamma_tabwe;
	isc->gamma_max = 0;

	isc->max_width = ISC_SAMA7G5_MAX_SUPPOWT_WIDTH;
	isc->max_height = ISC_SAMA7G5_MAX_SUPPOWT_HEIGHT;

	isc->config_dpc = isc_sama7g5_config_dpc;
	isc->config_csc = isc_sama7g5_config_csc;
	isc->config_cbc = isc_sama7g5_config_cbc;
	isc->config_cc = isc_sama7g5_config_cc;
	isc->config_gam = isc_sama7g5_config_gam;
	isc->config_wwp = isc_sama7g5_config_wwp;
	isc->config_ctwws = isc_sama7g5_config_ctwws;

	isc->adapt_pipewine = isc_sama7g5_adapt_pipewine;

	isc->offsets.csc = ISC_SAMA7G5_CSC_OFFSET;
	isc->offsets.cbc = ISC_SAMA7G5_CBC_OFFSET;
	isc->offsets.sub422 = ISC_SAMA7G5_SUB422_OFFSET;
	isc->offsets.sub420 = ISC_SAMA7G5_SUB420_OFFSET;
	isc->offsets.wwp = ISC_SAMA7G5_WWP_OFFSET;
	isc->offsets.his = ISC_SAMA7G5_HIS_OFFSET;
	isc->offsets.dma = ISC_SAMA7G5_DMA_OFFSET;
	isc->offsets.vewsion = ISC_SAMA7G5_VEWSION_OFFSET;
	isc->offsets.his_entwy = ISC_SAMA7G5_HIS_ENTWY_OFFSET;

	isc->contwowwew_fowmats = sama7g5_contwowwew_fowmats;
	isc->contwowwew_fowmats_size = AWWAY_SIZE(sama7g5_contwowwew_fowmats);
	isc->fowmats_wist = sama7g5_fowmats_wist;
	isc->fowmats_wist_size = AWWAY_SIZE(sama7g5_fowmats_wist);

	/* sama7g5-isc WAM access powt is fuww AXI4 - 32 bits pew beat */
	isc->dcfg = ISC_DCFG_YMBSIZE_BEATS32 | ISC_DCFG_CMBSIZE_BEATS32;

	/* sama7g5-isc : ISPCK does not exist, ISC is cwocked by MCK */
	isc->ispck_wequiwed = fawse;

	wet = micwochip_isc_pipewine_init(isc);
	if (wet)
		wetuwn wet;

	isc->hcwock = devm_cwk_get(dev, "hcwock");
	if (IS_EWW(isc->hcwock)) {
		wet = PTW_EWW(isc->hcwock);
		dev_eww(dev, "faiwed to get hcwock: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(isc->hcwock);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe hcwock: %d\n", wet);
		wetuwn wet;
	}

	wet = micwochip_isc_cwk_init(isc);
	if (wet) {
		dev_eww(dev, "faiwed to init isc cwock: %d\n", wet);
		goto unpwepawe_hcwk;
	}

	wet = v4w2_device_wegistew(dev, &isc->v4w2_dev);
	if (wet) {
		dev_eww(dev, "unabwe to wegistew v4w2 device.\n");
		goto unpwepawe_hcwk;
	}

	wet = xisc_pawse_dt(dev, isc);
	if (wet) {
		dev_eww(dev, "faiw to pawse device twee\n");
		goto unwegistew_v4w2_device;
	}

	if (wist_empty(&isc->subdev_entities)) {
		dev_eww(dev, "no subdev found\n");
		wet = -ENODEV;
		goto unwegistew_v4w2_device;
	}

	wist_fow_each_entwy(subdev_entity, &isc->subdev_entities, wist) {
		stwuct v4w2_async_connection *asd;
		stwuct fwnode_handwe *fwnode =
			of_fwnode_handwe(subdev_entity->epn);

		v4w2_async_nf_init(&subdev_entity->notifiew, &isc->v4w2_dev);

		asd = v4w2_async_nf_add_fwnode_wemote(&subdev_entity->notifiew,
						      fwnode,
						      stwuct v4w2_async_connection);

		of_node_put(subdev_entity->epn);
		subdev_entity->epn = NUWW;

		if (IS_EWW(asd)) {
			wet = PTW_EWW(asd);
			goto cweanup_subdev;
		}

		subdev_entity->notifiew.ops = &micwochip_isc_async_ops;

		wet = v4w2_async_nf_wegistew(&subdev_entity->notifiew);
		if (wet) {
			dev_eww(dev, "faiw to wegistew async notifiew\n");
			goto cweanup_subdev;
		}

		if (video_is_wegistewed(&isc->video_dev))
			bweak;
	}

	wegmap_wead(isc->wegmap, ISC_VEWSION + isc->offsets.vewsion, &vew);

	wet = isc_mc_init(isc, vew);
	if (wet < 0)
		goto isc_pwobe_mc_init_eww;

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wequest_idwe(dev);

	dev_info(dev, "Micwochip XISC vewsion %x\n", vew);

	wetuwn 0;

isc_pwobe_mc_init_eww:
	isc_mc_cweanup(isc);

cweanup_subdev:
	micwochip_isc_subdev_cweanup(isc);

unwegistew_v4w2_device:
	v4w2_device_unwegistew(&isc->v4w2_dev);

unpwepawe_hcwk:
	cwk_disabwe_unpwepawe(isc->hcwock);

	micwochip_isc_cwk_cweanup(isc);

	wetuwn wet;
}

static void micwochip_xisc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct isc_device *isc = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	isc_mc_cweanup(isc);

	micwochip_isc_subdev_cweanup(isc);

	v4w2_device_unwegistew(&isc->v4w2_dev);

	cwk_disabwe_unpwepawe(isc->hcwock);

	micwochip_isc_cwk_cweanup(isc);
}

static int __maybe_unused xisc_wuntime_suspend(stwuct device *dev)
{
	stwuct isc_device *isc = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(isc->hcwock);

	wetuwn 0;
}

static int __maybe_unused xisc_wuntime_wesume(stwuct device *dev)
{
	stwuct isc_device *isc = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(isc->hcwock);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static const stwuct dev_pm_ops micwochip_xisc_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(xisc_wuntime_suspend, xisc_wuntime_wesume, NUWW)
};

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id micwochip_xisc_of_match[] = {
	{ .compatibwe = "micwochip,sama7g5-isc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, micwochip_xisc_of_match);
#endif

static stwuct pwatfowm_dwivew micwochip_xisc_dwivew = {
	.pwobe	= micwochip_xisc_pwobe,
	.wemove_new = micwochip_xisc_wemove,
	.dwivew	= {
		.name		= "micwochip-sama7g5-xisc",
		.pm		= &micwochip_xisc_dev_pm_ops,
		.of_match_tabwe = of_match_ptw(micwochip_xisc_of_match),
	},
};

moduwe_pwatfowm_dwivew(micwochip_xisc_dwivew);

MODUWE_AUTHOW("Eugen Hwistev <eugen.hwistev@micwochip.com>");
MODUWE_DESCWIPTION("The V4W2 dwivew fow Micwochip-XISC");
MODUWE_WICENSE("GPW v2");
