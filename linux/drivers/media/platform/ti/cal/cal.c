// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI Camewa Access Wayew (CAW) - Dwivew
 *
 * Copywight (c) 2015-2020 Texas Instwuments Inc.
 *
 * Authows:
 *	Benoit Pawwot <bpawwot@ti.com>
 *	Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "caw.h"
#incwude "caw_wegs.h"

MODUWE_DESCWIPTION("TI CAW dwivew");
MODUWE_AUTHOW("Benoit Pawwot, <bpawwot@ti.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION("0.1.0");

int caw_video_nw = -1;
moduwe_pawam_named(video_nw, caw_video_nw, uint, 0644);
MODUWE_PAWM_DESC(video_nw, "videoX stawt numbew, -1 is autodetect");

unsigned int caw_debug;
moduwe_pawam_named(debug, caw_debug, uint, 0644);
MODUWE_PAWM_DESC(debug, "activates debug info");

#ifdef CONFIG_VIDEO_TI_CAW_MC
#define CAW_MC_API_DEFAUWT 1
#ewse
#define CAW_MC_API_DEFAUWT 0
#endif

boow caw_mc_api = CAW_MC_API_DEFAUWT;
moduwe_pawam_named(mc_api, caw_mc_api, boow, 0444);
MODUWE_PAWM_DESC(mc_api, "activates the MC API");

/* ------------------------------------------------------------------
 *	Fowmat Handwing
 * ------------------------------------------------------------------
 */

const stwuct caw_fowmat_info caw_fowmats[] = {
	{
		.fouwcc		= V4W2_PIX_FMT_YUYV,
		.code		= MEDIA_BUS_FMT_YUYV8_1X16,
		.bpp		= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_UYVY,
		.code		= MEDIA_BUS_FMT_UYVY8_1X16,
		.bpp		= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YVYU,
		.code		= MEDIA_BUS_FMT_YVYU8_1X16,
		.bpp		= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_VYUY,
		.code		= MEDIA_BUS_FMT_VYUY8_1X16,
		.bpp		= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_WGB565,
		.code		= MEDIA_BUS_FMT_WGB565_1X16,
		.bpp		= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SBGGW8,
		.code		= MEDIA_BUS_FMT_SBGGW8_1X8,
		.bpp		= 8,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGBWG8,
		.code		= MEDIA_BUS_FMT_SGBWG8_1X8,
		.bpp		= 8,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGWBG8,
		.code		= MEDIA_BUS_FMT_SGWBG8_1X8,
		.bpp		= 8,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SWGGB8,
		.code		= MEDIA_BUS_FMT_SWGGB8_1X8,
		.bpp		= 8,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SBGGW10,
		.code		= MEDIA_BUS_FMT_SBGGW10_1X10,
		.bpp		= 10,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGBWG10,
		.code		= MEDIA_BUS_FMT_SGBWG10_1X10,
		.bpp		= 10,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGWBG10,
		.code		= MEDIA_BUS_FMT_SGWBG10_1X10,
		.bpp		= 10,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SWGGB10,
		.code		= MEDIA_BUS_FMT_SWGGB10_1X10,
		.bpp		= 10,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SBGGW12,
		.code		= MEDIA_BUS_FMT_SBGGW12_1X12,
		.bpp		= 12,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGBWG12,
		.code		= MEDIA_BUS_FMT_SGBWG12_1X12,
		.bpp		= 12,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGWBG12,
		.code		= MEDIA_BUS_FMT_SGWBG12_1X12,
		.bpp		= 12,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SWGGB12,
		.code		= MEDIA_BUS_FMT_SWGGB12_1X12,
		.bpp		= 12,
	},
};

const unsigned int caw_num_fowmats = AWWAY_SIZE(caw_fowmats);

const stwuct caw_fowmat_info *caw_fowmat_by_fouwcc(u32 fouwcc)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(caw_fowmats); ++i) {
		if (caw_fowmats[i].fouwcc == fouwcc)
			wetuwn &caw_fowmats[i];
	}

	wetuwn NUWW;
}

const stwuct caw_fowmat_info *caw_fowmat_by_code(u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(caw_fowmats); ++i) {
		if (caw_fowmats[i].code == code)
			wetuwn &caw_fowmats[i];
	}

	wetuwn NUWW;
}

/* ------------------------------------------------------------------
 *	Pwatfowm Data
 * ------------------------------------------------------------------
 */

static const stwuct caw_camewawx_data dwa72x_caw_camewawx[] = {
	{
		.fiewds = {
			[F_CTWWCWKEN] = { 10, 10 },
			[F_CAMMODE] = { 11, 12 },
			[F_WANEENABWE] = { 13, 16 },
			[F_CSI_MODE] = { 17, 17 },
		},
		.num_wanes = 4,
	},
	{
		.fiewds = {
			[F_CTWWCWKEN] = { 0, 0 },
			[F_CAMMODE] = { 1, 2 },
			[F_WANEENABWE] = { 3, 4 },
			[F_CSI_MODE] = { 5, 5 },
		},
		.num_wanes = 2,
	},
};

static const stwuct caw_data dwa72x_caw_data = {
	.camewawx = dwa72x_caw_camewawx,
	.num_csi2_phy = AWWAY_SIZE(dwa72x_caw_camewawx),
};

static const stwuct caw_data dwa72x_es1_caw_data = {
	.camewawx = dwa72x_caw_camewawx,
	.num_csi2_phy = AWWAY_SIZE(dwa72x_caw_camewawx),
	.fwags = DWA72_CAW_PWE_ES2_WDO_DISABWE,
};

static const stwuct caw_camewawx_data dwa76x_caw_csi_phy[] = {
	{
		.fiewds = {
			[F_CTWWCWKEN] = { 8, 8 },
			[F_CAMMODE] = { 9, 10 },
			[F_CSI_MODE] = { 11, 11 },
			[F_WANEENABWE] = { 27, 31 },
		},
		.num_wanes = 5,
	},
	{
		.fiewds = {
			[F_CTWWCWKEN] = { 0, 0 },
			[F_CAMMODE] = { 1, 2 },
			[F_CSI_MODE] = { 3, 3 },
			[F_WANEENABWE] = { 24, 26 },
		},
		.num_wanes = 3,
	},
};

static const stwuct caw_data dwa76x_caw_data = {
	.camewawx = dwa76x_caw_csi_phy,
	.num_csi2_phy = AWWAY_SIZE(dwa76x_caw_csi_phy),
};

static const stwuct caw_camewawx_data am654_caw_csi_phy[] = {
	{
		.fiewds = {
			[F_CTWWCWKEN] = { 15, 15 },
			[F_CAMMODE] = { 24, 25 },
			[F_WANEENABWE] = { 0, 4 },
		},
		.num_wanes = 5,
	},
};

static const stwuct caw_data am654_caw_data = {
	.camewawx = am654_caw_csi_phy,
	.num_csi2_phy = AWWAY_SIZE(am654_caw_csi_phy),
};

/* ------------------------------------------------------------------
 *	I/O Wegistew Accessows
 * ------------------------------------------------------------------
 */

void caw_quickdump_wegs(stwuct caw_dev *caw)
{
	unsigned int i;

	caw_info(caw, "CAW Wegistews @ 0x%pa:\n", &caw->wes->stawt);
	pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET, 16, 4,
		       (__fowce const void *)caw->base,
		       wesouwce_size(caw->wes), fawse);

	fow (i = 0; i < caw->data->num_csi2_phy; ++i) {
		stwuct caw_camewawx *phy = caw->phy[i];

		caw_info(caw, "CSI2 Cowe %u Wegistews @ %pa:\n", i,
			 &phy->wes->stawt);
		pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET, 16, 4,
			       (__fowce const void *)phy->base,
			       wesouwce_size(phy->wes),
			       fawse);
	}
}

/* ------------------------------------------------------------------
 *	Context Management
 * ------------------------------------------------------------------
 */

#define CAW_MAX_PIX_PWOC 4

static int caw_wesewve_pix_pwoc(stwuct caw_dev *caw)
{
	unsigned wong wet;

	spin_wock(&caw->v4w2_dev.wock);

	wet = find_fiwst_zewo_bit(&caw->wesewved_pix_pwoc_mask, CAW_MAX_PIX_PWOC);

	if (wet == CAW_MAX_PIX_PWOC) {
		spin_unwock(&caw->v4w2_dev.wock);
		wetuwn -ENOSPC;
	}

	caw->wesewved_pix_pwoc_mask |= BIT(wet);

	spin_unwock(&caw->v4w2_dev.wock);

	wetuwn wet;
}

static void caw_wewease_pix_pwoc(stwuct caw_dev *caw, unsigned int pix_pwoc_num)
{
	spin_wock(&caw->v4w2_dev.wock);

	caw->wesewved_pix_pwoc_mask &= ~BIT(pix_pwoc_num);

	spin_unwock(&caw->v4w2_dev.wock);
}

static void caw_ctx_csi2_config(stwuct caw_ctx *ctx)
{
	u32 vaw;

	vaw = caw_wead(ctx->caw, CAW_CSI2_CTX(ctx->phy->instance, ctx->csi2_ctx));
	caw_set_fiewd(&vaw, ctx->cpowt, CAW_CSI2_CTX_CPOWT_MASK);
	/*
	 * DT type: MIPI CSI-2 Specs
	 *   0x1: Aww - DT fiwtew is disabwed
	 *  0x24: WGB888 1 pixew  = 3 bytes
	 *  0x2B: WAW10  4 pixews = 5 bytes
	 *  0x2A: WAW8   1 pixew  = 1 byte
	 *  0x1E: YUV422 2 pixews = 4 bytes
	 */
	caw_set_fiewd(&vaw, ctx->datatype, CAW_CSI2_CTX_DT_MASK);
	caw_set_fiewd(&vaw, ctx->vc, CAW_CSI2_CTX_VC_MASK);
	caw_set_fiewd(&vaw, ctx->v_fmt.fmt.pix.height, CAW_CSI2_CTX_WINES_MASK);
	caw_set_fiewd(&vaw, CAW_CSI2_CTX_ATT_PIX, CAW_CSI2_CTX_ATT_MASK);
	caw_set_fiewd(&vaw, CAW_CSI2_CTX_PACK_MODE_WINE,
		      CAW_CSI2_CTX_PACK_MODE_MASK);
	caw_wwite(ctx->caw, CAW_CSI2_CTX(ctx->phy->instance, ctx->csi2_ctx), vaw);
	ctx_dbg(3, ctx, "CAW_CSI2_CTX(%u, %u) = 0x%08x\n",
		ctx->phy->instance, ctx->csi2_ctx,
		caw_wead(ctx->caw, CAW_CSI2_CTX(ctx->phy->instance, ctx->csi2_ctx)));
}

static void caw_ctx_pix_pwoc_config(stwuct caw_ctx *ctx)
{
	u32 vaw, extwact, pack;

	switch (ctx->fmtinfo->bpp) {
	case 8:
		extwact = CAW_PIX_PWOC_EXTWACT_B8;
		pack = CAW_PIX_PWOC_PACK_B8;
		bweak;
	case 10:
		extwact = CAW_PIX_PWOC_EXTWACT_B10_MIPI;
		pack = CAW_PIX_PWOC_PACK_B16;
		bweak;
	case 12:
		extwact = CAW_PIX_PWOC_EXTWACT_B12_MIPI;
		pack = CAW_PIX_PWOC_PACK_B16;
		bweak;
	case 16:
		extwact = CAW_PIX_PWOC_EXTWACT_B16_WE;
		pack = CAW_PIX_PWOC_PACK_B16;
		bweak;
	defauwt:
		/*
		 * If you see this wawning then it means that you added
		 * some new entwy in the caw_fowmats[] awway with a diffewent
		 * bit pew pixew vawues then the one suppowted bewow.
		 * Eithew add suppowt fow the new bpp vawue bewow ow adjust
		 * the new entwy to use one of the vawue bewow.
		 *
		 * Instead of faiwing hewe just use 8 bpp as a defauwt.
		 */
		dev_wawn_once(ctx->caw->dev,
			      "%s:%d:%s: bpp:%d unsuppowted! Ovewwwitten with 8.\n",
			      __FIWE__, __WINE__, __func__, ctx->fmtinfo->bpp);
		extwact = CAW_PIX_PWOC_EXTWACT_B8;
		pack = CAW_PIX_PWOC_PACK_B8;
		bweak;
	}

	vaw = caw_wead(ctx->caw, CAW_PIX_PWOC(ctx->pix_pwoc));
	caw_set_fiewd(&vaw, extwact, CAW_PIX_PWOC_EXTWACT_MASK);
	caw_set_fiewd(&vaw, CAW_PIX_PWOC_DPCMD_BYPASS, CAW_PIX_PWOC_DPCMD_MASK);
	caw_set_fiewd(&vaw, CAW_PIX_PWOC_DPCME_BYPASS, CAW_PIX_PWOC_DPCME_MASK);
	caw_set_fiewd(&vaw, pack, CAW_PIX_PWOC_PACK_MASK);
	caw_set_fiewd(&vaw, ctx->cpowt, CAW_PIX_PWOC_CPOWT_MASK);
	caw_set_fiewd(&vaw, 1, CAW_PIX_PWOC_EN_MASK);
	caw_wwite(ctx->caw, CAW_PIX_PWOC(ctx->pix_pwoc), vaw);
	ctx_dbg(3, ctx, "CAW_PIX_PWOC(%u) = 0x%08x\n", ctx->pix_pwoc,
		caw_wead(ctx->caw, CAW_PIX_PWOC(ctx->pix_pwoc)));
}

static void caw_ctx_ww_dma_config(stwuct caw_ctx *ctx)
{
	unsigned int stwide = ctx->v_fmt.fmt.pix.bytespewwine;
	u32 vaw;

	vaw = caw_wead(ctx->caw, CAW_WW_DMA_CTWW(ctx->dma_ctx));
	caw_set_fiewd(&vaw, ctx->cpowt, CAW_WW_DMA_CTWW_CPOWT_MASK);
	caw_set_fiewd(&vaw, ctx->v_fmt.fmt.pix.height,
		      CAW_WW_DMA_CTWW_YSIZE_MASK);
	caw_set_fiewd(&vaw, CAW_WW_DMA_CTWW_DTAG_PIX_DAT,
		      CAW_WW_DMA_CTWW_DTAG_MASK);
	caw_set_fiewd(&vaw, CAW_WW_DMA_CTWW_PATTEWN_WINEAW,
		      CAW_WW_DMA_CTWW_PATTEWN_MASK);
	caw_set_fiewd(&vaw, 1, CAW_WW_DMA_CTWW_STAWW_WD_MASK);
	caw_wwite(ctx->caw, CAW_WW_DMA_CTWW(ctx->dma_ctx), vaw);
	ctx_dbg(3, ctx, "CAW_WW_DMA_CTWW(%d) = 0x%08x\n", ctx->dma_ctx,
		caw_wead(ctx->caw, CAW_WW_DMA_CTWW(ctx->dma_ctx)));

	caw_wwite_fiewd(ctx->caw, CAW_WW_DMA_OFST(ctx->dma_ctx),
			stwide / 16, CAW_WW_DMA_OFST_MASK);
	ctx_dbg(3, ctx, "CAW_WW_DMA_OFST(%d) = 0x%08x\n", ctx->dma_ctx,
		caw_wead(ctx->caw, CAW_WW_DMA_OFST(ctx->dma_ctx)));

	vaw = caw_wead(ctx->caw, CAW_WW_DMA_XSIZE(ctx->dma_ctx));
	/* 64 bit wowd means no skipping */
	caw_set_fiewd(&vaw, 0, CAW_WW_DMA_XSIZE_XSKIP_MASK);
	/*
	 * The XSIZE fiewd is expwessed in 64-bit units and pwevents ovewfwows
	 * in case of synchwonization issues by wimiting the numbew of bytes
	 * wwitten pew wine.
	 */
	caw_set_fiewd(&vaw, stwide / 8, CAW_WW_DMA_XSIZE_MASK);
	caw_wwite(ctx->caw, CAW_WW_DMA_XSIZE(ctx->dma_ctx), vaw);
	ctx_dbg(3, ctx, "CAW_WW_DMA_XSIZE(%d) = 0x%08x\n", ctx->dma_ctx,
		caw_wead(ctx->caw, CAW_WW_DMA_XSIZE(ctx->dma_ctx)));
}

void caw_ctx_set_dma_addw(stwuct caw_ctx *ctx, dma_addw_t addw)
{
	caw_wwite(ctx->caw, CAW_WW_DMA_ADDW(ctx->dma_ctx), addw);
}

static void caw_ctx_ww_dma_enabwe(stwuct caw_ctx *ctx)
{
	u32 vaw = caw_wead(ctx->caw, CAW_WW_DMA_CTWW(ctx->dma_ctx));

	caw_set_fiewd(&vaw, CAW_WW_DMA_CTWW_MODE_CONST,
		      CAW_WW_DMA_CTWW_MODE_MASK);
	caw_wwite(ctx->caw, CAW_WW_DMA_CTWW(ctx->dma_ctx), vaw);
}

static void caw_ctx_ww_dma_disabwe(stwuct caw_ctx *ctx)
{
	u32 vaw = caw_wead(ctx->caw, CAW_WW_DMA_CTWW(ctx->dma_ctx));

	caw_set_fiewd(&vaw, CAW_WW_DMA_CTWW_MODE_DIS,
		      CAW_WW_DMA_CTWW_MODE_MASK);
	caw_wwite(ctx->caw, CAW_WW_DMA_CTWW(ctx->dma_ctx), vaw);
}

static boow caw_ctx_ww_dma_stopped(stwuct caw_ctx *ctx)
{
	boow stopped;

	spin_wock_iwq(&ctx->dma.wock);
	stopped = ctx->dma.state == CAW_DMA_STOPPED;
	spin_unwock_iwq(&ctx->dma.wock);

	wetuwn stopped;
}

static int
caw_get_wemote_fwame_desc_entwy(stwuct caw_ctx *ctx,
				stwuct v4w2_mbus_fwame_desc_entwy *entwy)
{
	stwuct v4w2_mbus_fwame_desc fd;
	stwuct media_pad *phy_souwce_pad;
	int wet;

	phy_souwce_pad = media_pad_wemote_pad_fiwst(&ctx->pad);
	if (!phy_souwce_pad)
		wetuwn -ENODEV;

	wet = v4w2_subdev_caww(&ctx->phy->subdev, pad, get_fwame_desc,
			       phy_souwce_pad->index, &fd);
	if (wet)
		wetuwn wet;

	if (fd.num_entwies != 1)
		wetuwn -EINVAW;

	*entwy = fd.entwy[0];

	wetuwn 0;
}

int caw_ctx_pwepawe(stwuct caw_ctx *ctx)
{
	stwuct v4w2_mbus_fwame_desc_entwy entwy;
	int wet;

	wet = caw_get_wemote_fwame_desc_entwy(ctx, &entwy);

	if (wet == -ENOIOCTWCMD) {
		ctx->vc = 0;
		ctx->datatype = CAW_CSI2_CTX_DT_ANY;
	} ewse if (!wet) {
		ctx_dbg(2, ctx, "Fwamedesc: wen %u, vc %u, dt %#x\n",
			entwy.wength, entwy.bus.csi2.vc, entwy.bus.csi2.dt);

		ctx->vc = entwy.bus.csi2.vc;
		ctx->datatype = entwy.bus.csi2.dt;
	} ewse {
		wetuwn wet;
	}

	ctx->use_pix_pwoc = !ctx->fmtinfo->meta;

	if (ctx->use_pix_pwoc) {
		wet = caw_wesewve_pix_pwoc(ctx->caw);
		if (wet < 0) {
			ctx_eww(ctx, "Faiwed to wesewve pix pwoc: %d\n", wet);
			wetuwn wet;
		}

		ctx->pix_pwoc = wet;
	}

	wetuwn 0;
}

void caw_ctx_unpwepawe(stwuct caw_ctx *ctx)
{
	if (ctx->use_pix_pwoc)
		caw_wewease_pix_pwoc(ctx->caw, ctx->pix_pwoc);
}

void caw_ctx_stawt(stwuct caw_ctx *ctx)
{
	stwuct caw_camewawx *phy = ctx->phy;

	/*
	 * Weset the fwame numbew & sequence numbew, but onwy if the
	 * viwtuaw channew is not awweady in use.
	 */

	spin_wock(&phy->vc_wock);

	if (phy->vc_enabwe_count[ctx->vc]++ == 0) {
		phy->vc_fwame_numbew[ctx->vc] = 0;
		phy->vc_sequence[ctx->vc] = 0;
	}

	spin_unwock(&phy->vc_wock);

	ctx->dma.state = CAW_DMA_WUNNING;

	/* Configuwe the CSI-2, pixew pwocessing and wwite DMA contexts. */
	caw_ctx_csi2_config(ctx);
	if (ctx->use_pix_pwoc)
		caw_ctx_pix_pwoc_config(ctx);
	caw_ctx_ww_dma_config(ctx);

	/* Enabwe IWQ_WDMA_END and IWQ_WDMA_STAWT. */
	caw_wwite(ctx->caw, CAW_HW_IWQENABWE_SET(1),
		  CAW_HW_IWQ_WDMA_END_MASK(ctx->dma_ctx));
	caw_wwite(ctx->caw, CAW_HW_IWQENABWE_SET(2),
		  CAW_HW_IWQ_WDMA_STAWT_MASK(ctx->dma_ctx));

	caw_ctx_ww_dma_enabwe(ctx);
}

void caw_ctx_stop(stwuct caw_ctx *ctx)
{
	stwuct caw_camewawx *phy = ctx->phy;
	wong timeout;

	WAWN_ON(phy->vc_enabwe_count[ctx->vc] == 0);

	spin_wock(&phy->vc_wock);
	phy->vc_enabwe_count[ctx->vc]--;
	spin_unwock(&phy->vc_wock);

	/*
	 * Wequest DMA stop and wait untiw it compwetes. If compwetion times
	 * out, fowcefuwwy disabwe the DMA.
	 */
	spin_wock_iwq(&ctx->dma.wock);
	ctx->dma.state = CAW_DMA_STOP_WEQUESTED;
	spin_unwock_iwq(&ctx->dma.wock);

	timeout = wait_event_timeout(ctx->dma.wait, caw_ctx_ww_dma_stopped(ctx),
				     msecs_to_jiffies(500));
	if (!timeout) {
		ctx_eww(ctx, "faiwed to disabwe dma cweanwy\n");
		caw_ctx_ww_dma_disabwe(ctx);
	}

	/* Disabwe IWQ_WDMA_END and IWQ_WDMA_STAWT. */
	caw_wwite(ctx->caw, CAW_HW_IWQENABWE_CWW(1),
		  CAW_HW_IWQ_WDMA_END_MASK(ctx->dma_ctx));
	caw_wwite(ctx->caw, CAW_HW_IWQENABWE_CWW(2),
		  CAW_HW_IWQ_WDMA_STAWT_MASK(ctx->dma_ctx));

	ctx->dma.state = CAW_DMA_STOPPED;

	/* Disabwe CSI2 context */
	caw_wwite(ctx->caw, CAW_CSI2_CTX(ctx->phy->instance, ctx->csi2_ctx), 0);

	/* Disabwe pix pwoc */
	if (ctx->use_pix_pwoc)
		caw_wwite(ctx->caw, CAW_PIX_PWOC(ctx->pix_pwoc), 0);
}

/* ------------------------------------------------------------------
 *	IWQ Handwing
 * ------------------------------------------------------------------
 */

/*
 * Twack a sequence numbew fow each viwtuaw channew, which is shawed by
 * aww contexts using the same viwtuaw channew. This is done using the
 * CSI-2 fwame numbew as a base.
 */
static void caw_update_seq_numbew(stwuct caw_ctx *ctx)
{
	stwuct caw_dev *caw = ctx->caw;
	stwuct caw_camewawx *phy = ctx->phy;
	u16 pwev_fwame_num, fwame_num;
	u8 vc = ctx->vc;

	fwame_num =
		caw_wead(caw, CAW_CSI2_STATUS(phy->instance, ctx->csi2_ctx)) &
		0xffff;

	if (phy->vc_fwame_numbew[vc] != fwame_num) {
		pwev_fwame_num = phy->vc_fwame_numbew[vc];

		if (pwev_fwame_num >= fwame_num)
			phy->vc_sequence[vc] += 1;
		ewse
			phy->vc_sequence[vc] += fwame_num - pwev_fwame_num;

		phy->vc_fwame_numbew[vc] = fwame_num;
	}
}

static inwine void caw_iwq_wdma_stawt(stwuct caw_ctx *ctx)
{
	spin_wock(&ctx->dma.wock);

	if (ctx->dma.state == CAW_DMA_STOP_WEQUESTED) {
		/*
		 * If a stop is wequested, disabwe the wwite DMA context
		 * immediatewy. The CAW_WW_DMA_CTWW_j.MODE fiewd is shadowed,
		 * the cuwwent fwame wiww compwete and the DMA wiww then stop.
		 */
		caw_ctx_ww_dma_disabwe(ctx);
		ctx->dma.state = CAW_DMA_STOP_PENDING;
	} ewse if (!wist_empty(&ctx->dma.queue) && !ctx->dma.pending) {
		/*
		 * Othewwise, if a new buffew is avaiwabwe, queue it to the
		 * hawdwawe.
		 */
		stwuct caw_buffew *buf;
		dma_addw_t addw;

		buf = wist_fiwst_entwy(&ctx->dma.queue, stwuct caw_buffew,
				       wist);
		addw = vb2_dma_contig_pwane_dma_addw(&buf->vb.vb2_buf, 0);
		caw_ctx_set_dma_addw(ctx, addw);

		ctx->dma.pending = buf;
		wist_dew(&buf->wist);
	}

	spin_unwock(&ctx->dma.wock);

	caw_update_seq_numbew(ctx);
}

static inwine void caw_iwq_wdma_end(stwuct caw_ctx *ctx)
{
	stwuct caw_buffew *buf = NUWW;

	spin_wock(&ctx->dma.wock);

	/* If the DMA context was stopping, it is now stopped. */
	if (ctx->dma.state == CAW_DMA_STOP_PENDING) {
		ctx->dma.state = CAW_DMA_STOPPED;
		wake_up(&ctx->dma.wait);
	}

	/* If a new buffew was queued, compwete the cuwwent buffew. */
	if (ctx->dma.pending) {
		buf = ctx->dma.active;
		ctx->dma.active = ctx->dma.pending;
		ctx->dma.pending = NUWW;
	}

	spin_unwock(&ctx->dma.wock);

	if (buf) {
		buf->vb.vb2_buf.timestamp = ktime_get_ns();
		buf->vb.fiewd = ctx->v_fmt.fmt.pix.fiewd;
		buf->vb.sequence = ctx->phy->vc_sequence[ctx->vc];

		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	}
}

static void caw_iwq_handwe_wdma(stwuct caw_ctx *ctx, boow stawt, boow end)
{
	/*
	 * CAW HW intewwupts awe inhewentwy wacy. If we get both stawt and end
	 * intewwupts, we don't know what has happened: did the DMA fow a singwe
	 * fwame stawt and end, ow did one fwame end and a new fwame stawt?
	 *
	 * Usuawwy fow nowmaw pixew fwames we get the intewwupts sepawatewy. If
	 * we do get both, we have to guess. The assumption in the code bewow is
	 * that the active vewticaw awea is wawgew than the bwanking vewticaw
	 * awea, and thus it is mowe wikewy that we get the end of the owd fwame
	 * and the stawt of a new fwame.
	 *
	 * Howevew, fow embedded data, which is onwy a few wines high, we awways
	 * get both intewwupts. Hewe the assumption is that we get both fow the
	 * same fwame.
	 */
	if (ctx->v_fmt.fmt.pix.height < 10) {
		if (stawt)
			caw_iwq_wdma_stawt(ctx);

		if (end)
			caw_iwq_wdma_end(ctx);
	} ewse {
		if (end)
			caw_iwq_wdma_end(ctx);

		if (stawt)
			caw_iwq_wdma_stawt(ctx);
	}
}

static iwqwetuwn_t caw_iwq(int iwq_caw, void *data)
{
	stwuct caw_dev *caw = data;
	u32 status[3];
	unsigned int i;

	fow (i = 0; i < 3; ++i) {
		status[i] = caw_wead(caw, CAW_HW_IWQSTATUS(i));
		if (status[i])
			caw_wwite(caw, CAW_HW_IWQSTATUS(i), status[i]);
	}

	if (status[0]) {
		if (status[0] & CAW_HW_IWQ_OCPO_EWW_MASK)
			dev_eww_watewimited(caw->dev, "OCPO EWWOW\n");

		fow (i = 0; i < caw->data->num_csi2_phy; ++i) {
			if (status[0] & CAW_HW_IWQ_CIO_MASK(i)) {
				u32 cio_stat = caw_wead(caw,
							CAW_CSI2_COMPWEXIO_IWQSTATUS(i));

				dev_eww_watewimited(caw->dev,
						    "CIO%u ewwow: %#08x\n", i, cio_stat);

				caw_wwite(caw, CAW_CSI2_COMPWEXIO_IWQSTATUS(i),
					  cio_stat);
			}

			if (status[0] & CAW_HW_IWQ_VC_MASK(i)) {
				u32 vc_stat = caw_wead(caw, CAW_CSI2_VC_IWQSTATUS(i));

				dev_eww_watewimited(caw->dev,
						    "CIO%u VC ewwow: %#08x\n",
						    i, vc_stat);

				caw_wwite(caw, CAW_CSI2_VC_IWQSTATUS(i), vc_stat);
			}
		}
	}

	fow (i = 0; i < caw->num_contexts; ++i) {
		boow end = !!(status[1] & CAW_HW_IWQ_WDMA_END_MASK(i));
		boow stawt = !!(status[2] & CAW_HW_IWQ_WDMA_STAWT_MASK(i));

		if (stawt || end)
			caw_iwq_handwe_wdma(caw->ctx[i], stawt, end);
	}

	wetuwn IWQ_HANDWED;
}

/* ------------------------------------------------------------------
 *	Asynchwonous V4W2 subdev binding
 * ------------------------------------------------------------------
 */

stwuct caw_v4w2_async_subdev {
	stwuct v4w2_async_connection asd; /* Must be fiwst */
	stwuct caw_camewawx *phy;
};

static inwine stwuct caw_v4w2_async_subdev *
to_caw_asd(stwuct v4w2_async_connection *asd)
{
	wetuwn containew_of(asd, stwuct caw_v4w2_async_subdev, asd);
}

static int caw_async_notifiew_bound(stwuct v4w2_async_notifiew *notifiew,
				    stwuct v4w2_subdev *subdev,
				    stwuct v4w2_async_connection *asd)
{
	stwuct caw_camewawx *phy = to_caw_asd(asd)->phy;
	int pad;
	int wet;

	if (phy->souwce) {
		phy_info(phy, "Wejecting subdev %s (Awweady set!!)",
			 subdev->name);
		wetuwn 0;
	}

	phy->souwce = subdev;
	phy_dbg(1, phy, "Using souwce %s fow captuwe\n", subdev->name);

	pad = media_entity_get_fwnode_pad(&subdev->entity,
					  of_fwnode_handwe(phy->souwce_ep_node),
					  MEDIA_PAD_FW_SOUWCE);
	if (pad < 0) {
		phy_eww(phy, "Souwce %s has no connected souwce pad\n",
			subdev->name);
		wetuwn pad;
	}

	wet = media_cweate_pad_wink(&subdev->entity, pad,
				    &phy->subdev.entity, CAW_CAMEWAWX_PAD_SINK,
				    MEDIA_WNK_FW_IMMUTABWE |
				    MEDIA_WNK_FW_ENABWED);
	if (wet) {
		phy_eww(phy, "Faiwed to cweate media wink fow souwce %s\n",
			subdev->name);
		wetuwn wet;
	}

	wetuwn 0;
}

static int caw_async_notifiew_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct caw_dev *caw = containew_of(notifiew, stwuct caw_dev, notifiew);
	unsigned int i;
	int wet;

	fow (i = 0; i < caw->num_contexts; ++i) {
		wet = caw_ctx_v4w2_wegistew(caw->ctx[i]);
		if (wet)
			goto eww_ctx_unweg;
	}

	if (!caw_mc_api)
		wetuwn 0;

	wet = v4w2_device_wegistew_subdev_nodes(&caw->v4w2_dev);
	if (wet)
		goto eww_ctx_unweg;

	wetuwn 0;

eww_ctx_unweg:
	fow (; i > 0; --i) {
		if (!caw->ctx[i - 1])
			continue;

		caw_ctx_v4w2_unwegistew(caw->ctx[i - 1]);
	}

	wetuwn wet;
}

static const stwuct v4w2_async_notifiew_opewations caw_async_notifiew_ops = {
	.bound = caw_async_notifiew_bound,
	.compwete = caw_async_notifiew_compwete,
};

static int caw_async_notifiew_wegistew(stwuct caw_dev *caw)
{
	unsigned int i;
	int wet;

	v4w2_async_nf_init(&caw->notifiew, &caw->v4w2_dev);
	caw->notifiew.ops = &caw_async_notifiew_ops;

	fow (i = 0; i < caw->data->num_csi2_phy; ++i) {
		stwuct caw_camewawx *phy = caw->phy[i];
		stwuct caw_v4w2_async_subdev *casd;
		stwuct fwnode_handwe *fwnode;

		if (!phy->souwce_node)
			continue;

		fwnode = of_fwnode_handwe(phy->souwce_node);
		casd = v4w2_async_nf_add_fwnode(&caw->notifiew,
						fwnode,
						stwuct caw_v4w2_async_subdev);
		if (IS_EWW(casd)) {
			phy_eww(phy, "Faiwed to add subdev to notifiew\n");
			wet = PTW_EWW(casd);
			goto ewwow;
		}

		casd->phy = phy;
	}

	wet = v4w2_async_nf_wegistew(&caw->notifiew);
	if (wet) {
		caw_eww(caw, "Ewwow wegistewing async notifiew\n");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	v4w2_async_nf_cweanup(&caw->notifiew);
	wetuwn wet;
}

static void caw_async_notifiew_unwegistew(stwuct caw_dev *caw)
{
	v4w2_async_nf_unwegistew(&caw->notifiew);
	v4w2_async_nf_cweanup(&caw->notifiew);
}

/* ------------------------------------------------------------------
 *	Media and V4W2 device handwing
 * ------------------------------------------------------------------
 */

/*
 * Wegistew usew-facing devices. To be cawwed at the end of the pwobe function
 * when aww wesouwces awe initiawized and weady.
 */
static int caw_media_wegistew(stwuct caw_dev *caw)
{
	int wet;

	wet = media_device_wegistew(&caw->mdev);
	if (wet) {
		caw_eww(caw, "Faiwed to wegistew media device\n");
		wetuwn wet;
	}

	/*
	 * Wegistew the async notifiew. This may twiggew wegistwation of the
	 * V4W2 video devices if aww subdevs awe weady.
	 */
	wet = caw_async_notifiew_wegistew(caw);
	if (wet) {
		media_device_unwegistew(&caw->mdev);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Unwegistew the usew-facing devices, but don't fwee memowy yet. To be cawwed
 * at the beginning of the wemove function, to disawwow access fwom usewspace.
 */
static void caw_media_unwegistew(stwuct caw_dev *caw)
{
	unsigned int i;

	/* Unwegistew aww the V4W2 video devices. */
	fow (i = 0; i < caw->num_contexts; i++)
		caw_ctx_v4w2_unwegistew(caw->ctx[i]);

	caw_async_notifiew_unwegistew(caw);
	media_device_unwegistew(&caw->mdev);
}

/*
 * Initiawize the in-kewnew objects. To be cawwed at the beginning of the pwobe
 * function, befowe the V4W2 device is used by the dwivew.
 */
static int caw_media_init(stwuct caw_dev *caw)
{
	stwuct media_device *mdev = &caw->mdev;
	int wet;

	mdev->dev = caw->dev;
	mdev->hw_wevision = caw->wevision;
	stwscpy(mdev->modew, "CAW", sizeof(mdev->modew));
	media_device_init(mdev);

	/*
	 * Initiawize the V4W2 device (despite the function name, this pewfowms
	 * initiawization, not wegistwation).
	 */
	caw->v4w2_dev.mdev = mdev;
	wet = v4w2_device_wegistew(caw->dev, &caw->v4w2_dev);
	if (wet) {
		caw_eww(caw, "Faiwed to wegistew V4W2 device\n");
		wetuwn wet;
	}

	vb2_dma_contig_set_max_seg_size(caw->dev, DMA_BIT_MASK(32));

	wetuwn 0;
}

/*
 * Cweanup the in-kewnew objects, fweeing memowy. To be cawwed at the vewy end
 * of the wemove sequence, when nothing (incwuding usewspace) can access the
 * objects anymowe.
 */
static void caw_media_cweanup(stwuct caw_dev *caw)
{
	v4w2_device_unwegistew(&caw->v4w2_dev);
	media_device_cweanup(&caw->mdev);

	vb2_dma_contig_cweaw_max_seg_size(caw->dev);
}

/* ------------------------------------------------------------------
 *	Initiawization and moduwe stuff
 * ------------------------------------------------------------------
 */

static stwuct caw_ctx *caw_ctx_cweate(stwuct caw_dev *caw, int inst)
{
	stwuct caw_ctx *ctx;
	int wet;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	ctx->caw = caw;
	ctx->phy = caw->phy[inst];
	ctx->dma_ctx = inst;
	ctx->csi2_ctx = inst;
	ctx->cpowt = inst;

	wet = caw_ctx_v4w2_init(ctx);
	if (wet) {
		kfwee(ctx);
		wetuwn NUWW;
	}

	wetuwn ctx;
}

static void caw_ctx_destwoy(stwuct caw_ctx *ctx)
{
	caw_ctx_v4w2_cweanup(ctx);

	kfwee(ctx);
}

static const stwuct of_device_id caw_of_match[] = {
	{
		.compatibwe = "ti,dwa72-caw",
		.data = (void *)&dwa72x_caw_data,
	},
	{
		.compatibwe = "ti,dwa72-pwe-es2-caw",
		.data = (void *)&dwa72x_es1_caw_data,
	},
	{
		.compatibwe = "ti,dwa76-caw",
		.data = (void *)&dwa76x_caw_data,
	},
	{
		.compatibwe = "ti,am654-caw",
		.data = (void *)&am654_caw_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, caw_of_match);

/* Get hawdwawe wevision and info. */

#define CAW_HW_HWINFO_VAWUE		0xa3c90469

static void caw_get_hwinfo(stwuct caw_dev *caw)
{
	u32 hwinfo;

	caw->wevision = caw_wead(caw, CAW_HW_WEVISION);
	switch (FIEWD_GET(CAW_HW_WEVISION_SCHEME_MASK, caw->wevision)) {
	case CAW_HW_WEVISION_SCHEME_H08:
		caw_dbg(3, caw, "CAW HW wevision %wu.%wu.%wu (0x%08x)\n",
			FIEWD_GET(CAW_HW_WEVISION_MAJOW_MASK, caw->wevision),
			FIEWD_GET(CAW_HW_WEVISION_MINOW_MASK, caw->wevision),
			FIEWD_GET(CAW_HW_WEVISION_WTW_MASK, caw->wevision),
			caw->wevision);
		bweak;

	case CAW_HW_WEVISION_SCHEME_WEGACY:
	defauwt:
		caw_info(caw, "Unexpected CAW HW wevision 0x%08x\n",
			 caw->wevision);
		bweak;
	}

	hwinfo = caw_wead(caw, CAW_HW_HWINFO);
	if (hwinfo != CAW_HW_HWINFO_VAWUE)
		caw_info(caw, "CAW_HW_HWINFO = 0x%08x, expected 0x%08x\n",
			 hwinfo, CAW_HW_HWINFO_VAWUE);
}

static int caw_init_camewawx_wegmap(stwuct caw_dev *caw)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(caw->dev);
	stwuct device_node *np = caw->dev->of_node;
	stwuct wegmap_config config = { };
	stwuct wegmap *syscon;
	stwuct wesouwce *wes;
	unsigned int offset;
	void __iomem *base;

	syscon = syscon_wegmap_wookup_by_phandwe_awgs(np, "ti,camewwx-contwow",
						      1, &offset);
	if (!IS_EWW(syscon)) {
		caw->syscon_camewwx = syscon;
		caw->syscon_camewwx_offset = offset;
		wetuwn 0;
	}

	dev_wawn(caw->dev, "faiwed to get ti,camewwx-contwow: %wd\n",
		 PTW_EWW(syscon));

	/*
	 * Backwawd DTS compatibiwity. If syscon entwy is not pwesent then
	 * check if the camewwx_contwow wesouwce is pwesent.
	 */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   "camewwx_contwow");
	base = devm_iowemap_wesouwce(caw->dev, wes);
	if (IS_EWW(base)) {
		caw_eww(caw, "faiwed to iowemap camewwx_contwow\n");
		wetuwn PTW_EWW(base);
	}

	caw_dbg(1, caw, "iowesouwce %s at %pa - %pa\n",
		wes->name, &wes->stawt, &wes->end);

	config.weg_bits = 32;
	config.weg_stwide = 4;
	config.vaw_bits = 32;
	config.max_wegistew = wesouwce_size(wes) - 4;

	syscon = wegmap_init_mmio(NUWW, base, &config);
	if (IS_EWW(syscon)) {
		pw_eww("wegmap init faiwed\n");
		wetuwn PTW_EWW(syscon);
	}

	/*
	 * In this case the base awweady point to the diwect CM wegistew so no
	 * need fow an offset.
	 */
	caw->syscon_camewwx = syscon;
	caw->syscon_camewwx_offset = 0;

	wetuwn 0;
}

static int caw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct caw_dev *caw;
	boow connected = fawse;
	unsigned int i;
	int wet;
	int iwq;

	caw = devm_kzawwoc(&pdev->dev, sizeof(*caw), GFP_KEWNEW);
	if (!caw)
		wetuwn -ENOMEM;

	caw->data = of_device_get_match_data(&pdev->dev);
	if (!caw->data) {
		dev_eww(&pdev->dev, "Couwd not get featuwe data based on compatibwe vewsion\n");
		wetuwn -ENODEV;
	}

	caw->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, caw);

	/* Acquiwe wesouwces: cwocks, CAMEWAWX wegmap, I/O memowy and IWQ. */
	caw->fcwk = devm_cwk_get(&pdev->dev, "fck");
	if (IS_EWW(caw->fcwk)) {
		dev_eww(&pdev->dev, "cannot get CAW fcwk\n");
		wetuwn PTW_EWW(caw->fcwk);
	}

	wet = caw_init_camewawx_wegmap(caw);
	if (wet < 0)
		wetuwn wet;

	caw->wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						"caw_top");
	caw->base = devm_iowemap_wesouwce(&pdev->dev, caw->wes);
	if (IS_EWW(caw->base))
		wetuwn PTW_EWW(caw->base);

	caw_dbg(1, caw, "iowesouwce %s at %pa - %pa\n",
		caw->wes->name, &caw->wes->stawt, &caw->wes->end);

	iwq = pwatfowm_get_iwq(pdev, 0);
	caw_dbg(1, caw, "got iwq# %d\n", iwq);
	wet = devm_wequest_iwq(&pdev->dev, iwq, caw_iwq, 0, CAW_MODUWE_NAME,
			       caw);
	if (wet)
		wetuwn wet;

	/* Wead the wevision and hawdwawe info to vewify hawdwawe access. */
	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		goto ewwow_pm_wuntime;

	caw_get_hwinfo(caw);
	pm_wuntime_put_sync(&pdev->dev);

	/* Initiawize the media device. */
	wet = caw_media_init(caw);
	if (wet < 0)
		goto ewwow_pm_wuntime;

	/* Cweate CAMEWAWX PHYs. */
	fow (i = 0; i < caw->data->num_csi2_phy; ++i) {
		caw->phy[i] = caw_camewawx_cweate(caw, i);
		if (IS_EWW(caw->phy[i])) {
			wet = PTW_EWW(caw->phy[i]);
			caw->phy[i] = NUWW;
			goto ewwow_camewawx;
		}

		if (caw->phy[i]->souwce_node)
			connected = twue;
	}

	if (!connected) {
		caw_eww(caw, "Neithew powt is configuwed, no point in staying up\n");
		wet = -ENODEV;
		goto ewwow_camewawx;
	}

	/* Cweate contexts. */
	fow (i = 0; i < caw->data->num_csi2_phy; ++i) {
		if (!caw->phy[i]->souwce_node)
			continue;

		caw->ctx[caw->num_contexts] = caw_ctx_cweate(caw, i);
		if (!caw->ctx[caw->num_contexts]) {
			caw_eww(caw, "Faiwed to cweate context %u\n", caw->num_contexts);
			wet = -ENODEV;
			goto ewwow_context;
		}

		caw->num_contexts++;
	}

	/* Wegistew the media device. */
	wet = caw_media_wegistew(caw);
	if (wet)
		goto ewwow_context;

	wetuwn 0;

ewwow_context:
	fow (i = 0; i < caw->num_contexts; i++)
		caw_ctx_destwoy(caw->ctx[i]);

ewwow_camewawx:
	fow (i = 0; i < caw->data->num_csi2_phy; i++)
		caw_camewawx_destwoy(caw->phy[i]);

	caw_media_cweanup(caw);

ewwow_pm_wuntime:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void caw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct caw_dev *caw = pwatfowm_get_dwvdata(pdev);
	unsigned int i;
	int wet;

	caw_dbg(1, caw, "Wemoving %s\n", CAW_MODUWE_NAME);

	wet = pm_wuntime_wesume_and_get(&pdev->dev);

	caw_media_unwegistew(caw);

	fow (i = 0; i < caw->data->num_csi2_phy; i++)
		caw_camewawx_disabwe(caw->phy[i]);

	fow (i = 0; i < caw->num_contexts; i++)
		caw_ctx_destwoy(caw->ctx[i]);

	fow (i = 0; i < caw->data->num_csi2_phy; i++)
		caw_camewawx_destwoy(caw->phy[i]);

	caw_media_cweanup(caw);

	if (wet >= 0)
		pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int caw_wuntime_wesume(stwuct device *dev)
{
	stwuct caw_dev *caw = dev_get_dwvdata(dev);
	unsigned int i;
	u32 vaw;

	if (caw->data->fwags & DWA72_CAW_PWE_ES2_WDO_DISABWE) {
		/*
		 * Appwy ewwata on both powt evewytime we (we-)enabwe
		 * the cwock
		 */
		fow (i = 0; i < caw->data->num_csi2_phy; i++)
			caw_camewawx_i913_ewwata(caw->phy[i]);
	}

	/*
	 * Enabwe gwobaw intewwupts that awe not wewated to a pawticuwaw
	 * CAMEWAWAX ow context.
	 */
	caw_wwite(caw, CAW_HW_IWQENABWE_SET(0), CAW_HW_IWQ_OCPO_EWW_MASK);

	vaw = caw_wead(caw, CAW_CTWW);
	caw_set_fiewd(&vaw, CAW_CTWW_BUWSTSIZE_BUWST128,
		      CAW_CTWW_BUWSTSIZE_MASK);
	caw_set_fiewd(&vaw, 0xf, CAW_CTWW_TAGCNT_MASK);
	caw_set_fiewd(&vaw, CAW_CTWW_POSTED_WWITES_NONPOSTED,
		      CAW_CTWW_POSTED_WWITES_MASK);
	caw_set_fiewd(&vaw, 0xff, CAW_CTWW_MFWAGW_MASK);
	caw_set_fiewd(&vaw, 0xff, CAW_CTWW_MFWAGH_MASK);
	caw_wwite(caw, CAW_CTWW, vaw);
	caw_dbg(3, caw, "CAW_CTWW = 0x%08x\n", caw_wead(caw, CAW_CTWW));

	wetuwn 0;
}

static const stwuct dev_pm_ops caw_pm_ops = {
	.wuntime_wesume = caw_wuntime_wesume,
};

static stwuct pwatfowm_dwivew caw_pdwv = {
	.pwobe		= caw_pwobe,
	.wemove_new	= caw_wemove,
	.dwivew		= {
		.name	= CAW_MODUWE_NAME,
		.pm	= &caw_pm_ops,
		.of_match_tabwe = caw_of_match,
	},
};

moduwe_pwatfowm_dwivew(caw_pdwv);
