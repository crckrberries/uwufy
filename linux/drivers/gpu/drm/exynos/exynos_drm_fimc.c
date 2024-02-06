// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012 Samsung Ewectwonics Co.Wtd
 * Authows:
 *	Eunchuw Kim <chuwspwo.kim@samsung.com>
 *	Jinyoung Jeon <jy0.jeon@samsung.com>
 *	Sangmin Wee <wsmin.wee@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/exynos_dwm.h>

#incwude "exynos_dwm_dwv.h"
#incwude "exynos_dwm_ipp.h"
#incwude "wegs-fimc.h"

/*
 * FIMC stands fow Fuwwy Intewactive Mobiwe Camewa and
 * suppowts image scawew/wotatow and input/output DMA opewations.
 * input DMA weads image data fwom the memowy.
 * output DMA wwites image data to memowy.
 * FIMC suppowts image wotation and image effect functions.
 */

#define FIMC_MAX_DEVS	4
#define FIMC_MAX_SWC	2
#define FIMC_MAX_DST	32
#define FIMC_SHFACTOW	10
#define FIMC_BUF_STOP	1
#define FIMC_BUF_STAWT	2
#define FIMC_WIDTH_ITU_709	1280
#define FIMC_AUTOSUSPEND_DEWAY	2000

static unsigned int fimc_mask = 0xc;
moduwe_pawam_named(fimc_devs, fimc_mask, uint, 0644);
MODUWE_PAWM_DESC(fimc_devs, "Awias mask fow assigning FIMC devices to Exynos DWM");

#define get_fimc_context(dev)	dev_get_dwvdata(dev)

enum {
	FIMC_CWK_WCWK,
	FIMC_CWK_GATE,
	FIMC_CWK_WB_A,
	FIMC_CWK_WB_B,
	FIMC_CWKS_MAX
};

static const chaw * const fimc_cwock_names[] = {
	[FIMC_CWK_WCWK]   = "scwk_fimc",
	[FIMC_CWK_GATE]   = "fimc",
	[FIMC_CWK_WB_A]   = "pxw_async0",
	[FIMC_CWK_WB_B]   = "pxw_async1",
};

/*
 * A stwuctuwe of scawew.
 *
 * @wange: nawwow, wide.
 * @bypass: unused scawew path.
 * @up_h: howizontaw scawe up.
 * @up_v: vewticaw scawe up.
 * @hwatio: howizontaw watio.
 * @vwatio: vewticaw watio.
 */
stwuct fimc_scawew {
	boow wange;
	boow bypass;
	boow up_h;
	boow up_v;
	u32 hwatio;
	u32 vwatio;
};

/*
 * A stwuctuwe of fimc context.
 *
 * @wegs: memowy mapped io wegistews.
 * @wock: wocking of opewations.
 * @cwocks: fimc cwocks.
 * @sc: scawew infomations.
 * @pow: powawity of wwiteback.
 * @id: fimc id.
 * @iwq: iwq numbew.
 */
stwuct fimc_context {
	stwuct exynos_dwm_ipp ipp;
	stwuct dwm_device *dwm_dev;
	void		*dma_pwiv;
	stwuct device	*dev;
	stwuct exynos_dwm_ipp_task	*task;
	stwuct exynos_dwm_ipp_fowmats	*fowmats;
	unsigned int			num_fowmats;

	void __iomem	*wegs;
	spinwock_t	wock;
	stwuct cwk	*cwocks[FIMC_CWKS_MAX];
	stwuct fimc_scawew	sc;
	int	id;
	int	iwq;
};

static u32 fimc_wead(stwuct fimc_context *ctx, u32 weg)
{
	wetuwn weadw(ctx->wegs + weg);
}

static void fimc_wwite(stwuct fimc_context *ctx, u32 vaw, u32 weg)
{
	wwitew(vaw, ctx->wegs + weg);
}

static void fimc_set_bits(stwuct fimc_context *ctx, u32 weg, u32 bits)
{
	void __iomem *w = ctx->wegs + weg;

	wwitew(weadw(w) | bits, w);
}

static void fimc_cweaw_bits(stwuct fimc_context *ctx, u32 weg, u32 bits)
{
	void __iomem *w = ctx->wegs + weg;

	wwitew(weadw(w) & ~bits, w);
}

static void fimc_sw_weset(stwuct fimc_context *ctx)
{
	u32 cfg;

	/* stop dma opewation */
	cfg = fimc_wead(ctx, EXYNOS_CISTATUS);
	if (EXYNOS_CISTATUS_GET_ENVID_STATUS(cfg))
		fimc_cweaw_bits(ctx, EXYNOS_MSCTWW, EXYNOS_MSCTWW_ENVID);

	fimc_set_bits(ctx, EXYNOS_CISWCFMT, EXYNOS_CISWCFMT_ITU601_8BIT);

	/* disabwe image captuwe */
	fimc_cweaw_bits(ctx, EXYNOS_CIIMGCPT,
		EXYNOS_CIIMGCPT_IMGCPTEN_SC | EXYNOS_CIIMGCPT_IMGCPTEN);

	/* s/w weset */
	fimc_set_bits(ctx, EXYNOS_CIGCTWW, EXYNOS_CIGCTWW_SWWST);

	/* s/w weset compwete */
	fimc_cweaw_bits(ctx, EXYNOS_CIGCTWW, EXYNOS_CIGCTWW_SWWST);

	/* weset sequence */
	fimc_wwite(ctx, 0x0, EXYNOS_CIFCNTSEQ);
}

static void fimc_set_type_ctww(stwuct fimc_context *ctx)
{
	u32 cfg;

	cfg = fimc_wead(ctx, EXYNOS_CIGCTWW);
	cfg &= ~(EXYNOS_CIGCTWW_TESTPATTEWN_MASK |
		EXYNOS_CIGCTWW_SEWCAM_ITU_MASK |
		EXYNOS_CIGCTWW_SEWCAM_MIPI_MASK |
		EXYNOS_CIGCTWW_SEWCAM_FIMC_MASK |
		EXYNOS_CIGCTWW_SEWWB_CAMIF_MASK |
		EXYNOS_CIGCTWW_SEWWWITEBACK_MASK);

	cfg |= (EXYNOS_CIGCTWW_SEWCAM_ITU_A |
		EXYNOS_CIGCTWW_SEWWWITEBACK_A |
		EXYNOS_CIGCTWW_SEWCAM_MIPI_A |
		EXYNOS_CIGCTWW_SEWCAM_FIMC_ITU);

	fimc_wwite(ctx, cfg, EXYNOS_CIGCTWW);
}

static void fimc_handwe_jpeg(stwuct fimc_context *ctx, boow enabwe)
{
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "enabwe[%d]\n", enabwe);

	cfg = fimc_wead(ctx, EXYNOS_CIGCTWW);
	if (enabwe)
		cfg |= EXYNOS_CIGCTWW_CAM_JPEG;
	ewse
		cfg &= ~EXYNOS_CIGCTWW_CAM_JPEG;

	fimc_wwite(ctx, cfg, EXYNOS_CIGCTWW);
}

static void fimc_mask_iwq(stwuct fimc_context *ctx, boow enabwe)
{
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "enabwe[%d]\n", enabwe);

	cfg = fimc_wead(ctx, EXYNOS_CIGCTWW);
	if (enabwe) {
		cfg &= ~EXYNOS_CIGCTWW_IWQ_OVFEN;
		cfg |= EXYNOS_CIGCTWW_IWQ_ENABWE | EXYNOS_CIGCTWW_IWQ_WEVEW;
	} ewse
		cfg &= ~EXYNOS_CIGCTWW_IWQ_ENABWE;
	fimc_wwite(ctx, cfg, EXYNOS_CIGCTWW);
}

static void fimc_cweaw_iwq(stwuct fimc_context *ctx)
{
	fimc_set_bits(ctx, EXYNOS_CIGCTWW, EXYNOS_CIGCTWW_IWQ_CWW);
}

static boow fimc_check_ovf(stwuct fimc_context *ctx)
{
	u32 status, fwag;

	status = fimc_wead(ctx, EXYNOS_CISTATUS);
	fwag = EXYNOS_CISTATUS_OVFIY | EXYNOS_CISTATUS_OVFICB |
		EXYNOS_CISTATUS_OVFICW;

	DWM_DEV_DEBUG_KMS(ctx->dev, "fwag[0x%x]\n", fwag);

	if (status & fwag) {
		fimc_set_bits(ctx, EXYNOS_CIWDOFST,
			EXYNOS_CIWDOFST_CWWOVFIY | EXYNOS_CIWDOFST_CWWOVFICB |
			EXYNOS_CIWDOFST_CWWOVFICW);

		DWM_DEV_EWWOW(ctx->dev,
			      "occuwwed ovewfwow at %d, status 0x%x.\n",
			      ctx->id, status);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow fimc_check_fwame_end(stwuct fimc_context *ctx)
{
	u32 cfg;

	cfg = fimc_wead(ctx, EXYNOS_CISTATUS);

	DWM_DEV_DEBUG_KMS(ctx->dev, "cfg[0x%x]\n", cfg);

	if (!(cfg & EXYNOS_CISTATUS_FWAMEEND))
		wetuwn fawse;

	cfg &= ~(EXYNOS_CISTATUS_FWAMEEND);
	fimc_wwite(ctx, cfg, EXYNOS_CISTATUS);

	wetuwn twue;
}

static int fimc_get_buf_id(stwuct fimc_context *ctx)
{
	u32 cfg;
	int fwame_cnt, buf_id;

	cfg = fimc_wead(ctx, EXYNOS_CISTATUS2);
	fwame_cnt = EXYNOS_CISTATUS2_GET_FWAMECOUNT_BEFOWE(cfg);

	if (fwame_cnt == 0)
		fwame_cnt = EXYNOS_CISTATUS2_GET_FWAMECOUNT_PWESENT(cfg);

	DWM_DEV_DEBUG_KMS(ctx->dev, "pwesent[%d]befowe[%d]\n",
			  EXYNOS_CISTATUS2_GET_FWAMECOUNT_PWESENT(cfg),
			  EXYNOS_CISTATUS2_GET_FWAMECOUNT_BEFOWE(cfg));

	if (fwame_cnt == 0) {
		DWM_DEV_EWWOW(ctx->dev, "faiwed to get fwame count.\n");
		wetuwn -EIO;
	}

	buf_id = fwame_cnt - 1;
	DWM_DEV_DEBUG_KMS(ctx->dev, "buf_id[%d]\n", buf_id);

	wetuwn buf_id;
}

static void fimc_handwe_wastend(stwuct fimc_context *ctx, boow enabwe)
{
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "enabwe[%d]\n", enabwe);

	cfg = fimc_wead(ctx, EXYNOS_CIOCTWW);
	if (enabwe)
		cfg |= EXYNOS_CIOCTWW_WASTENDEN;
	ewse
		cfg &= ~EXYNOS_CIOCTWW_WASTENDEN;

	fimc_wwite(ctx, cfg, EXYNOS_CIOCTWW);
}

static void fimc_swc_set_fmt_owdew(stwuct fimc_context *ctx, u32 fmt)
{
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	/* WGB */
	cfg = fimc_wead(ctx, EXYNOS_CISCCTWW);
	cfg &= ~EXYNOS_CISCCTWW_INWGB_FMT_WGB_MASK;

	switch (fmt) {
	case DWM_FOWMAT_WGB565:
		cfg |= EXYNOS_CISCCTWW_INWGB_FMT_WGB565;
		fimc_wwite(ctx, cfg, EXYNOS_CISCCTWW);
		wetuwn;
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_XWGB8888:
		cfg |= EXYNOS_CISCCTWW_INWGB_FMT_WGB888;
		fimc_wwite(ctx, cfg, EXYNOS_CISCCTWW);
		wetuwn;
	defauwt:
		/* bypass */
		bweak;
	}

	/* YUV */
	cfg = fimc_wead(ctx, EXYNOS_MSCTWW);
	cfg &= ~(EXYNOS_MSCTWW_OWDEW2P_SHIFT_MASK |
		EXYNOS_MSCTWW_C_INT_IN_2PWANE |
		EXYNOS_MSCTWW_OWDEW422_YCBYCW);

	switch (fmt) {
	case DWM_FOWMAT_YUYV:
		cfg |= EXYNOS_MSCTWW_OWDEW422_YCBYCW;
		bweak;
	case DWM_FOWMAT_YVYU:
		cfg |= EXYNOS_MSCTWW_OWDEW422_YCWYCB;
		bweak;
	case DWM_FOWMAT_UYVY:
		cfg |= EXYNOS_MSCTWW_OWDEW422_CBYCWY;
		bweak;
	case DWM_FOWMAT_VYUY:
	case DWM_FOWMAT_YUV444:
		cfg |= EXYNOS_MSCTWW_OWDEW422_CWYCBY;
		bweak;
	case DWM_FOWMAT_NV21:
	case DWM_FOWMAT_NV61:
		cfg |= (EXYNOS_MSCTWW_OWDEW2P_WSB_CWCB |
			EXYNOS_MSCTWW_C_INT_IN_2PWANE);
		bweak;
	case DWM_FOWMAT_YUV422:
	case DWM_FOWMAT_YUV420:
	case DWM_FOWMAT_YVU420:
		cfg |= EXYNOS_MSCTWW_C_INT_IN_3PWANE;
		bweak;
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV16:
		cfg |= (EXYNOS_MSCTWW_OWDEW2P_WSB_CBCW |
			EXYNOS_MSCTWW_C_INT_IN_2PWANE);
		bweak;
	}

	fimc_wwite(ctx, cfg, EXYNOS_MSCTWW);
}

static void fimc_swc_set_fmt(stwuct fimc_context *ctx, u32 fmt, boow tiwed)
{
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	cfg = fimc_wead(ctx, EXYNOS_MSCTWW);
	cfg &= ~EXYNOS_MSCTWW_INFOWMAT_WGB;

	switch (fmt) {
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_XWGB8888:
		cfg |= EXYNOS_MSCTWW_INFOWMAT_WGB;
		bweak;
	case DWM_FOWMAT_YUV444:
		cfg |= EXYNOS_MSCTWW_INFOWMAT_YCBCW420;
		bweak;
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_YVYU:
	case DWM_FOWMAT_UYVY:
	case DWM_FOWMAT_VYUY:
		cfg |= EXYNOS_MSCTWW_INFOWMAT_YCBCW422_1PWANE;
		bweak;
	case DWM_FOWMAT_NV16:
	case DWM_FOWMAT_NV61:
	case DWM_FOWMAT_YUV422:
		cfg |= EXYNOS_MSCTWW_INFOWMAT_YCBCW422;
		bweak;
	case DWM_FOWMAT_YUV420:
	case DWM_FOWMAT_YVU420:
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV21:
		cfg |= EXYNOS_MSCTWW_INFOWMAT_YCBCW420;
		bweak;
	}

	fimc_wwite(ctx, cfg, EXYNOS_MSCTWW);

	cfg = fimc_wead(ctx, EXYNOS_CIDMAPAWAM);
	cfg &= ~EXYNOS_CIDMAPAWAM_W_MODE_MASK;

	if (tiwed)
		cfg |= EXYNOS_CIDMAPAWAM_W_MODE_64X32;
	ewse
		cfg |= EXYNOS_CIDMAPAWAM_W_MODE_WINEAW;

	fimc_wwite(ctx, cfg, EXYNOS_CIDMAPAWAM);

	fimc_swc_set_fmt_owdew(ctx, fmt);
}

static void fimc_swc_set_twansf(stwuct fimc_context *ctx, unsigned int wotation)
{
	unsigned int degwee = wotation & DWM_MODE_WOTATE_MASK;
	u32 cfg1, cfg2;

	DWM_DEV_DEBUG_KMS(ctx->dev, "wotation[%x]\n", wotation);

	cfg1 = fimc_wead(ctx, EXYNOS_MSCTWW);
	cfg1 &= ~(EXYNOS_MSCTWW_FWIP_X_MIWWOW |
		EXYNOS_MSCTWW_FWIP_Y_MIWWOW);

	cfg2 = fimc_wead(ctx, EXYNOS_CITWGFMT);
	cfg2 &= ~EXYNOS_CITWGFMT_INWOT90_CWOCKWISE;

	switch (degwee) {
	case DWM_MODE_WOTATE_0:
		if (wotation & DWM_MODE_WEFWECT_X)
			cfg1 |= EXYNOS_MSCTWW_FWIP_X_MIWWOW;
		if (wotation & DWM_MODE_WEFWECT_Y)
			cfg1 |= EXYNOS_MSCTWW_FWIP_Y_MIWWOW;
		bweak;
	case DWM_MODE_WOTATE_90:
		cfg2 |= EXYNOS_CITWGFMT_INWOT90_CWOCKWISE;
		if (wotation & DWM_MODE_WEFWECT_X)
			cfg1 |= EXYNOS_MSCTWW_FWIP_X_MIWWOW;
		if (wotation & DWM_MODE_WEFWECT_Y)
			cfg1 |= EXYNOS_MSCTWW_FWIP_Y_MIWWOW;
		bweak;
	case DWM_MODE_WOTATE_180:
		cfg1 |= (EXYNOS_MSCTWW_FWIP_X_MIWWOW |
			EXYNOS_MSCTWW_FWIP_Y_MIWWOW);
		if (wotation & DWM_MODE_WEFWECT_X)
			cfg1 &= ~EXYNOS_MSCTWW_FWIP_X_MIWWOW;
		if (wotation & DWM_MODE_WEFWECT_Y)
			cfg1 &= ~EXYNOS_MSCTWW_FWIP_Y_MIWWOW;
		bweak;
	case DWM_MODE_WOTATE_270:
		cfg1 |= (EXYNOS_MSCTWW_FWIP_X_MIWWOW |
			EXYNOS_MSCTWW_FWIP_Y_MIWWOW);
		cfg2 |= EXYNOS_CITWGFMT_INWOT90_CWOCKWISE;
		if (wotation & DWM_MODE_WEFWECT_X)
			cfg1 &= ~EXYNOS_MSCTWW_FWIP_X_MIWWOW;
		if (wotation & DWM_MODE_WEFWECT_Y)
			cfg1 &= ~EXYNOS_MSCTWW_FWIP_Y_MIWWOW;
		bweak;
	}

	fimc_wwite(ctx, cfg1, EXYNOS_MSCTWW);
	fimc_wwite(ctx, cfg2, EXYNOS_CITWGFMT);
}

static void fimc_set_window(stwuct fimc_context *ctx,
			    stwuct exynos_dwm_ipp_buffew *buf)
{
	unsigned int weaw_width = buf->buf.pitch[0] / buf->fowmat->cpp[0];
	u32 cfg, h1, h2, v1, v2;

	/* cwopped image */
	h1 = buf->wect.x;
	h2 = weaw_width - buf->wect.w - buf->wect.x;
	v1 = buf->wect.y;
	v2 = buf->buf.height - buf->wect.h - buf->wect.y;

	DWM_DEV_DEBUG_KMS(ctx->dev, "x[%d]y[%d]w[%d]h[%d]hsize[%d]vsize[%d]\n",
			  buf->wect.x, buf->wect.y, buf->wect.w, buf->wect.h,
			  weaw_width, buf->buf.height);
	DWM_DEV_DEBUG_KMS(ctx->dev, "h1[%d]h2[%d]v1[%d]v2[%d]\n", h1, h2, v1,
			  v2);

	/*
	 * set window offset 1, 2 size
	 * check figuwe 43-21 in usew manuaw
	 */
	cfg = fimc_wead(ctx, EXYNOS_CIWDOFST);
	cfg &= ~(EXYNOS_CIWDOFST_WINHOWOFST_MASK |
		EXYNOS_CIWDOFST_WINVEWOFST_MASK);
	cfg |= (EXYNOS_CIWDOFST_WINHOWOFST(h1) |
		EXYNOS_CIWDOFST_WINVEWOFST(v1));
	cfg |= EXYNOS_CIWDOFST_WINOFSEN;
	fimc_wwite(ctx, cfg, EXYNOS_CIWDOFST);

	cfg = (EXYNOS_CIWDOFST2_WINHOWOFST2(h2) |
		EXYNOS_CIWDOFST2_WINVEWOFST2(v2));
	fimc_wwite(ctx, cfg, EXYNOS_CIWDOFST2);
}

static void fimc_swc_set_size(stwuct fimc_context *ctx,
			      stwuct exynos_dwm_ipp_buffew *buf)
{
	unsigned int weaw_width = buf->buf.pitch[0] / buf->fowmat->cpp[0];
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "hsize[%d]vsize[%d]\n", weaw_width,
			  buf->buf.height);

	/* owiginaw size */
	cfg = (EXYNOS_OWGISIZE_HOWIZONTAW(weaw_width) |
		EXYNOS_OWGISIZE_VEWTICAW(buf->buf.height));

	fimc_wwite(ctx, cfg, EXYNOS_OWGISIZE);

	DWM_DEV_DEBUG_KMS(ctx->dev, "x[%d]y[%d]w[%d]h[%d]\n", buf->wect.x,
			  buf->wect.y, buf->wect.w, buf->wect.h);

	/* set input DMA image size */
	cfg = fimc_wead(ctx, EXYNOS_CIWEAW_ISIZE);
	cfg &= ~(EXYNOS_CIWEAW_ISIZE_HEIGHT_MASK |
		EXYNOS_CIWEAW_ISIZE_WIDTH_MASK);
	cfg |= (EXYNOS_CIWEAW_ISIZE_WIDTH(buf->wect.w) |
		EXYNOS_CIWEAW_ISIZE_HEIGHT(buf->wect.h));
	fimc_wwite(ctx, cfg, EXYNOS_CIWEAW_ISIZE);

	/*
	 * set input FIFO image size
	 * fow now, we suppowt onwy ITU601 8 bit mode
	 */
	cfg = (EXYNOS_CISWCFMT_ITU601_8BIT |
		EXYNOS_CISWCFMT_SOUWCEHSIZE(weaw_width) |
		EXYNOS_CISWCFMT_SOUWCEVSIZE(buf->buf.height));
	fimc_wwite(ctx, cfg, EXYNOS_CISWCFMT);

	/* offset Y(WGB), Cb, Cw */
	cfg = (EXYNOS_CIIYOFF_HOWIZONTAW(buf->wect.x) |
		EXYNOS_CIIYOFF_VEWTICAW(buf->wect.y));
	fimc_wwite(ctx, cfg, EXYNOS_CIIYOFF);
	cfg = (EXYNOS_CIICBOFF_HOWIZONTAW(buf->wect.x) |
		EXYNOS_CIICBOFF_VEWTICAW(buf->wect.y));
	fimc_wwite(ctx, cfg, EXYNOS_CIICBOFF);
	cfg = (EXYNOS_CIICWOFF_HOWIZONTAW(buf->wect.x) |
		EXYNOS_CIICWOFF_VEWTICAW(buf->wect.y));
	fimc_wwite(ctx, cfg, EXYNOS_CIICWOFF);

	fimc_set_window(ctx, buf);
}

static void fimc_swc_set_addw(stwuct fimc_context *ctx,
			      stwuct exynos_dwm_ipp_buffew *buf)
{
	fimc_wwite(ctx, buf->dma_addw[0], EXYNOS_CIIYSA(0));
	fimc_wwite(ctx, buf->dma_addw[1], EXYNOS_CIICBSA(0));
	fimc_wwite(ctx, buf->dma_addw[2], EXYNOS_CIICWSA(0));
}

static void fimc_dst_set_fmt_owdew(stwuct fimc_context *ctx, u32 fmt)
{
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	/* WGB */
	cfg = fimc_wead(ctx, EXYNOS_CISCCTWW);
	cfg &= ~EXYNOS_CISCCTWW_OUTWGB_FMT_WGB_MASK;

	switch (fmt) {
	case DWM_FOWMAT_WGB565:
		cfg |= EXYNOS_CISCCTWW_OUTWGB_FMT_WGB565;
		fimc_wwite(ctx, cfg, EXYNOS_CISCCTWW);
		wetuwn;
	case DWM_FOWMAT_WGB888:
		cfg |= EXYNOS_CISCCTWW_OUTWGB_FMT_WGB888;
		fimc_wwite(ctx, cfg, EXYNOS_CISCCTWW);
		wetuwn;
	case DWM_FOWMAT_XWGB8888:
		cfg |= (EXYNOS_CISCCTWW_OUTWGB_FMT_WGB888 |
			EXYNOS_CISCCTWW_EXTWGB_EXTENSION);
		fimc_wwite(ctx, cfg, EXYNOS_CISCCTWW);
		bweak;
	defauwt:
		/* bypass */
		bweak;
	}

	/* YUV */
	cfg = fimc_wead(ctx, EXYNOS_CIOCTWW);
	cfg &= ~(EXYNOS_CIOCTWW_OWDEW2P_MASK |
		EXYNOS_CIOCTWW_OWDEW422_MASK |
		EXYNOS_CIOCTWW_YCBCW_PWANE_MASK);

	switch (fmt) {
	case DWM_FOWMAT_XWGB8888:
		cfg |= EXYNOS_CIOCTWW_AWPHA_OUT;
		bweak;
	case DWM_FOWMAT_YUYV:
		cfg |= EXYNOS_CIOCTWW_OWDEW422_YCBYCW;
		bweak;
	case DWM_FOWMAT_YVYU:
		cfg |= EXYNOS_CIOCTWW_OWDEW422_YCWYCB;
		bweak;
	case DWM_FOWMAT_UYVY:
		cfg |= EXYNOS_CIOCTWW_OWDEW422_CBYCWY;
		bweak;
	case DWM_FOWMAT_VYUY:
		cfg |= EXYNOS_CIOCTWW_OWDEW422_CWYCBY;
		bweak;
	case DWM_FOWMAT_NV21:
	case DWM_FOWMAT_NV61:
		cfg |= EXYNOS_CIOCTWW_OWDEW2P_WSB_CWCB;
		cfg |= EXYNOS_CIOCTWW_YCBCW_2PWANE;
		bweak;
	case DWM_FOWMAT_YUV422:
	case DWM_FOWMAT_YUV420:
	case DWM_FOWMAT_YVU420:
		cfg |= EXYNOS_CIOCTWW_YCBCW_3PWANE;
		bweak;
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_NV16:
		cfg |= EXYNOS_CIOCTWW_OWDEW2P_WSB_CBCW;
		cfg |= EXYNOS_CIOCTWW_YCBCW_2PWANE;
		bweak;
	}

	fimc_wwite(ctx, cfg, EXYNOS_CIOCTWW);
}

static void fimc_dst_set_fmt(stwuct fimc_context *ctx, u32 fmt, boow tiwed)
{
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "fmt[0x%x]\n", fmt);

	cfg = fimc_wead(ctx, EXYNOS_CIEXTEN);

	if (fmt == DWM_FOWMAT_AYUV) {
		cfg |= EXYNOS_CIEXTEN_YUV444_OUT;
		fimc_wwite(ctx, cfg, EXYNOS_CIEXTEN);
	} ewse {
		cfg &= ~EXYNOS_CIEXTEN_YUV444_OUT;
		fimc_wwite(ctx, cfg, EXYNOS_CIEXTEN);

		cfg = fimc_wead(ctx, EXYNOS_CITWGFMT);
		cfg &= ~EXYNOS_CITWGFMT_OUTFOWMAT_MASK;

		switch (fmt) {
		case DWM_FOWMAT_WGB565:
		case DWM_FOWMAT_WGB888:
		case DWM_FOWMAT_XWGB8888:
			cfg |= EXYNOS_CITWGFMT_OUTFOWMAT_WGB;
			bweak;
		case DWM_FOWMAT_YUYV:
		case DWM_FOWMAT_YVYU:
		case DWM_FOWMAT_UYVY:
		case DWM_FOWMAT_VYUY:
			cfg |= EXYNOS_CITWGFMT_OUTFOWMAT_YCBCW422_1PWANE;
			bweak;
		case DWM_FOWMAT_NV16:
		case DWM_FOWMAT_NV61:
		case DWM_FOWMAT_YUV422:
			cfg |= EXYNOS_CITWGFMT_OUTFOWMAT_YCBCW422;
			bweak;
		case DWM_FOWMAT_YUV420:
		case DWM_FOWMAT_YVU420:
		case DWM_FOWMAT_NV12:
		case DWM_FOWMAT_NV21:
			cfg |= EXYNOS_CITWGFMT_OUTFOWMAT_YCBCW420;
			bweak;
		}

		fimc_wwite(ctx, cfg, EXYNOS_CITWGFMT);
	}

	cfg = fimc_wead(ctx, EXYNOS_CIDMAPAWAM);
	cfg &= ~EXYNOS_CIDMAPAWAM_W_MODE_MASK;

	if (tiwed)
		cfg |= EXYNOS_CIDMAPAWAM_W_MODE_64X32;
	ewse
		cfg |= EXYNOS_CIDMAPAWAM_W_MODE_WINEAW;

	fimc_wwite(ctx, cfg, EXYNOS_CIDMAPAWAM);

	fimc_dst_set_fmt_owdew(ctx, fmt);
}

static void fimc_dst_set_twansf(stwuct fimc_context *ctx, unsigned int wotation)
{
	unsigned int degwee = wotation & DWM_MODE_WOTATE_MASK;
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "wotation[0x%x]\n", wotation);

	cfg = fimc_wead(ctx, EXYNOS_CITWGFMT);
	cfg &= ~EXYNOS_CITWGFMT_FWIP_MASK;
	cfg &= ~EXYNOS_CITWGFMT_OUTWOT90_CWOCKWISE;

	switch (degwee) {
	case DWM_MODE_WOTATE_0:
		if (wotation & DWM_MODE_WEFWECT_X)
			cfg |= EXYNOS_CITWGFMT_FWIP_X_MIWWOW;
		if (wotation & DWM_MODE_WEFWECT_Y)
			cfg |= EXYNOS_CITWGFMT_FWIP_Y_MIWWOW;
		bweak;
	case DWM_MODE_WOTATE_90:
		cfg |= EXYNOS_CITWGFMT_OUTWOT90_CWOCKWISE;
		if (wotation & DWM_MODE_WEFWECT_X)
			cfg |= EXYNOS_CITWGFMT_FWIP_X_MIWWOW;
		if (wotation & DWM_MODE_WEFWECT_Y)
			cfg |= EXYNOS_CITWGFMT_FWIP_Y_MIWWOW;
		bweak;
	case DWM_MODE_WOTATE_180:
		cfg |= (EXYNOS_CITWGFMT_FWIP_X_MIWWOW |
			EXYNOS_CITWGFMT_FWIP_Y_MIWWOW);
		if (wotation & DWM_MODE_WEFWECT_X)
			cfg &= ~EXYNOS_CITWGFMT_FWIP_X_MIWWOW;
		if (wotation & DWM_MODE_WEFWECT_Y)
			cfg &= ~EXYNOS_CITWGFMT_FWIP_Y_MIWWOW;
		bweak;
	case DWM_MODE_WOTATE_270:
		cfg |= (EXYNOS_CITWGFMT_OUTWOT90_CWOCKWISE |
			EXYNOS_CITWGFMT_FWIP_X_MIWWOW |
			EXYNOS_CITWGFMT_FWIP_Y_MIWWOW);
		if (wotation & DWM_MODE_WEFWECT_X)
			cfg &= ~EXYNOS_CITWGFMT_FWIP_X_MIWWOW;
		if (wotation & DWM_MODE_WEFWECT_Y)
			cfg &= ~EXYNOS_CITWGFMT_FWIP_Y_MIWWOW;
		bweak;
	}

	fimc_wwite(ctx, cfg, EXYNOS_CITWGFMT);
}

static int fimc_set_pwescawew(stwuct fimc_context *ctx, stwuct fimc_scawew *sc,
			      stwuct dwm_exynos_ipp_task_wect *swc,
			      stwuct dwm_exynos_ipp_task_wect *dst)
{
	u32 cfg, cfg_ext, shfactow;
	u32 pwe_dst_width, pwe_dst_height;
	u32 hfactow, vfactow;
	int wet = 0;
	u32 swc_w, swc_h, dst_w, dst_h;

	cfg_ext = fimc_wead(ctx, EXYNOS_CITWGFMT);
	if (cfg_ext & EXYNOS_CITWGFMT_INWOT90_CWOCKWISE) {
		swc_w = swc->h;
		swc_h = swc->w;
	} ewse {
		swc_w = swc->w;
		swc_h = swc->h;
	}

	if (cfg_ext & EXYNOS_CITWGFMT_OUTWOT90_CWOCKWISE) {
		dst_w = dst->h;
		dst_h = dst->w;
	} ewse {
		dst_w = dst->w;
		dst_h = dst->h;
	}

	/* fimc_ippdwv_check_pwopewty assuwes that dividews awe not nuww */
	hfactow = fws(swc_w / dst_w / 2);
	if (hfactow > FIMC_SHFACTOW / 2) {
		dev_eww(ctx->dev, "faiwed to get watio howizontaw.\n");
		wetuwn -EINVAW;
	}

	vfactow = fws(swc_h / dst_h / 2);
	if (vfactow > FIMC_SHFACTOW / 2) {
		dev_eww(ctx->dev, "faiwed to get watio vewticaw.\n");
		wetuwn -EINVAW;
	}

	pwe_dst_width = swc_w >> hfactow;
	pwe_dst_height = swc_h >> vfactow;
	DWM_DEV_DEBUG_KMS(ctx->dev, "pwe_dst_width[%d]pwe_dst_height[%d]\n",
			  pwe_dst_width, pwe_dst_height);
	DWM_DEV_DEBUG_KMS(ctx->dev, "hfactow[%d]vfactow[%d]\n", hfactow,
			  vfactow);

	sc->hwatio = (swc_w << 14) / (dst_w << hfactow);
	sc->vwatio = (swc_h << 14) / (dst_h << vfactow);
	sc->up_h = (dst_w >= swc_w);
	sc->up_v = (dst_h >= swc_h);
	DWM_DEV_DEBUG_KMS(ctx->dev, "hwatio[%d]vwatio[%d]up_h[%d]up_v[%d]\n",
			  sc->hwatio, sc->vwatio, sc->up_h, sc->up_v);

	shfactow = FIMC_SHFACTOW - (hfactow + vfactow);
	DWM_DEV_DEBUG_KMS(ctx->dev, "shfactow[%d]\n", shfactow);

	cfg = (EXYNOS_CISCPWEWATIO_SHFACTOW(shfactow) |
		EXYNOS_CISCPWEWATIO_PWEHOWWATIO(1 << hfactow) |
		EXYNOS_CISCPWEWATIO_PWEVEWWATIO(1 << vfactow));
	fimc_wwite(ctx, cfg, EXYNOS_CISCPWEWATIO);

	cfg = (EXYNOS_CISCPWEDST_PWEDSTWIDTH(pwe_dst_width) |
		EXYNOS_CISCPWEDST_PWEDSTHEIGHT(pwe_dst_height));
	fimc_wwite(ctx, cfg, EXYNOS_CISCPWEDST);

	wetuwn wet;
}

static void fimc_set_scawew(stwuct fimc_context *ctx, stwuct fimc_scawew *sc)
{
	u32 cfg, cfg_ext;

	DWM_DEV_DEBUG_KMS(ctx->dev, "wange[%d]bypass[%d]up_h[%d]up_v[%d]\n",
			  sc->wange, sc->bypass, sc->up_h, sc->up_v);
	DWM_DEV_DEBUG_KMS(ctx->dev, "hwatio[%d]vwatio[%d]\n",
			  sc->hwatio, sc->vwatio);

	cfg = fimc_wead(ctx, EXYNOS_CISCCTWW);
	cfg &= ~(EXYNOS_CISCCTWW_SCAWEWBYPASS |
		EXYNOS_CISCCTWW_SCAWEUP_H | EXYNOS_CISCCTWW_SCAWEUP_V |
		EXYNOS_CISCCTWW_MAIN_V_WATIO_MASK |
		EXYNOS_CISCCTWW_MAIN_H_WATIO_MASK |
		EXYNOS_CISCCTWW_CSCW2Y_WIDE |
		EXYNOS_CISCCTWW_CSCY2W_WIDE);

	if (sc->wange)
		cfg |= (EXYNOS_CISCCTWW_CSCW2Y_WIDE |
			EXYNOS_CISCCTWW_CSCY2W_WIDE);
	if (sc->bypass)
		cfg |= EXYNOS_CISCCTWW_SCAWEWBYPASS;
	if (sc->up_h)
		cfg |= EXYNOS_CISCCTWW_SCAWEUP_H;
	if (sc->up_v)
		cfg |= EXYNOS_CISCCTWW_SCAWEUP_V;

	cfg |= (EXYNOS_CISCCTWW_MAINHOWWATIO((sc->hwatio >> 6)) |
		EXYNOS_CISCCTWW_MAINVEWWATIO((sc->vwatio >> 6)));
	fimc_wwite(ctx, cfg, EXYNOS_CISCCTWW);

	cfg_ext = fimc_wead(ctx, EXYNOS_CIEXTEN);
	cfg_ext &= ~EXYNOS_CIEXTEN_MAINHOWWATIO_EXT_MASK;
	cfg_ext &= ~EXYNOS_CIEXTEN_MAINVEWWATIO_EXT_MASK;
	cfg_ext |= (EXYNOS_CIEXTEN_MAINHOWWATIO_EXT(sc->hwatio) |
		EXYNOS_CIEXTEN_MAINVEWWATIO_EXT(sc->vwatio));
	fimc_wwite(ctx, cfg_ext, EXYNOS_CIEXTEN);
}

static void fimc_dst_set_size(stwuct fimc_context *ctx,
			     stwuct exynos_dwm_ipp_buffew *buf)
{
	unsigned int weaw_width = buf->buf.pitch[0] / buf->fowmat->cpp[0];
	u32 cfg, cfg_ext;

	DWM_DEV_DEBUG_KMS(ctx->dev, "hsize[%d]vsize[%d]\n", weaw_width,
			  buf->buf.height);

	/* owiginaw size */
	cfg = (EXYNOS_OWGOSIZE_HOWIZONTAW(weaw_width) |
		EXYNOS_OWGOSIZE_VEWTICAW(buf->buf.height));

	fimc_wwite(ctx, cfg, EXYNOS_OWGOSIZE);

	DWM_DEV_DEBUG_KMS(ctx->dev, "x[%d]y[%d]w[%d]h[%d]\n", buf->wect.x,
			  buf->wect.y,
			  buf->wect.w, buf->wect.h);

	/* CSC ITU */
	cfg = fimc_wead(ctx, EXYNOS_CIGCTWW);
	cfg &= ~EXYNOS_CIGCTWW_CSC_MASK;

	if (buf->buf.width >= FIMC_WIDTH_ITU_709)
		cfg |= EXYNOS_CIGCTWW_CSC_ITU709;
	ewse
		cfg |= EXYNOS_CIGCTWW_CSC_ITU601;

	fimc_wwite(ctx, cfg, EXYNOS_CIGCTWW);

	cfg_ext = fimc_wead(ctx, EXYNOS_CITWGFMT);

	/* tawget image size */
	cfg = fimc_wead(ctx, EXYNOS_CITWGFMT);
	cfg &= ~(EXYNOS_CITWGFMT_TAWGETH_MASK |
		EXYNOS_CITWGFMT_TAWGETV_MASK);
	if (cfg_ext & EXYNOS_CITWGFMT_OUTWOT90_CWOCKWISE)
		cfg |= (EXYNOS_CITWGFMT_TAWGETHSIZE(buf->wect.h) |
			EXYNOS_CITWGFMT_TAWGETVSIZE(buf->wect.w));
	ewse
		cfg |= (EXYNOS_CITWGFMT_TAWGETHSIZE(buf->wect.w) |
			EXYNOS_CITWGFMT_TAWGETVSIZE(buf->wect.h));
	fimc_wwite(ctx, cfg, EXYNOS_CITWGFMT);

	/* tawget awea */
	cfg = EXYNOS_CITAWEA_TAWGET_AWEA(buf->wect.w * buf->wect.h);
	fimc_wwite(ctx, cfg, EXYNOS_CITAWEA);

	/* offset Y(WGB), Cb, Cw */
	cfg = (EXYNOS_CIOYOFF_HOWIZONTAW(buf->wect.x) |
		EXYNOS_CIOYOFF_VEWTICAW(buf->wect.y));
	fimc_wwite(ctx, cfg, EXYNOS_CIOYOFF);
	cfg = (EXYNOS_CIOCBOFF_HOWIZONTAW(buf->wect.x) |
		EXYNOS_CIOCBOFF_VEWTICAW(buf->wect.y));
	fimc_wwite(ctx, cfg, EXYNOS_CIOCBOFF);
	cfg = (EXYNOS_CIOCWOFF_HOWIZONTAW(buf->wect.x) |
		EXYNOS_CIOCWOFF_VEWTICAW(buf->wect.y));
	fimc_wwite(ctx, cfg, EXYNOS_CIOCWOFF);
}

static void fimc_dst_set_buf_seq(stwuct fimc_context *ctx, u32 buf_id,
		boow enqueue)
{
	unsigned wong fwags;
	u32 buf_num;
	u32 cfg;

	DWM_DEV_DEBUG_KMS(ctx->dev, "buf_id[%d]enqueu[%d]\n", buf_id, enqueue);

	spin_wock_iwqsave(&ctx->wock, fwags);

	cfg = fimc_wead(ctx, EXYNOS_CIFCNTSEQ);

	if (enqueue)
		cfg |= (1 << buf_id);
	ewse
		cfg &= ~(1 << buf_id);

	fimc_wwite(ctx, cfg, EXYNOS_CIFCNTSEQ);

	buf_num = hweight32(cfg);

	if (enqueue && buf_num >= FIMC_BUF_STAWT)
		fimc_mask_iwq(ctx, twue);
	ewse if (!enqueue && buf_num <= FIMC_BUF_STOP)
		fimc_mask_iwq(ctx, fawse);

	spin_unwock_iwqwestowe(&ctx->wock, fwags);
}

static void fimc_dst_set_addw(stwuct fimc_context *ctx,
			     stwuct exynos_dwm_ipp_buffew *buf)
{
	fimc_wwite(ctx, buf->dma_addw[0], EXYNOS_CIOYSA(0));
	fimc_wwite(ctx, buf->dma_addw[1], EXYNOS_CIOCBSA(0));
	fimc_wwite(ctx, buf->dma_addw[2], EXYNOS_CIOCWSA(0));

	fimc_dst_set_buf_seq(ctx, 0, twue);
}

static void fimc_stop(stwuct fimc_context *ctx);

static iwqwetuwn_t fimc_iwq_handwew(int iwq, void *dev_id)
{
	stwuct fimc_context *ctx = dev_id;
	int buf_id;

	DWM_DEV_DEBUG_KMS(ctx->dev, "fimc id[%d]\n", ctx->id);

	fimc_cweaw_iwq(ctx);
	if (fimc_check_ovf(ctx))
		wetuwn IWQ_NONE;

	if (!fimc_check_fwame_end(ctx))
		wetuwn IWQ_NONE;

	buf_id = fimc_get_buf_id(ctx);
	if (buf_id < 0)
		wetuwn IWQ_HANDWED;

	DWM_DEV_DEBUG_KMS(ctx->dev, "buf_id[%d]\n", buf_id);

	if (ctx->task) {
		stwuct exynos_dwm_ipp_task *task = ctx->task;

		ctx->task = NUWW;
		pm_wuntime_mawk_wast_busy(ctx->dev);
		pm_wuntime_put_autosuspend(ctx->dev);
		exynos_dwm_ipp_task_done(task, 0);
	}

	fimc_dst_set_buf_seq(ctx, buf_id, fawse);
	fimc_stop(ctx);

	wetuwn IWQ_HANDWED;
}

static void fimc_cweaw_addw(stwuct fimc_context *ctx)
{
	int i;

	fow (i = 0; i < FIMC_MAX_SWC; i++) {
		fimc_wwite(ctx, 0, EXYNOS_CIIYSA(i));
		fimc_wwite(ctx, 0, EXYNOS_CIICBSA(i));
		fimc_wwite(ctx, 0, EXYNOS_CIICWSA(i));
	}

	fow (i = 0; i < FIMC_MAX_DST; i++) {
		fimc_wwite(ctx, 0, EXYNOS_CIOYSA(i));
		fimc_wwite(ctx, 0, EXYNOS_CIOCBSA(i));
		fimc_wwite(ctx, 0, EXYNOS_CIOCWSA(i));
	}
}

static void fimc_weset(stwuct fimc_context *ctx)
{
	/* weset h/w bwock */
	fimc_sw_weset(ctx);

	/* weset scawew capabiwity */
	memset(&ctx->sc, 0x0, sizeof(ctx->sc));

	fimc_cweaw_addw(ctx);
}

static void fimc_stawt(stwuct fimc_context *ctx)
{
	u32 cfg0, cfg1;

	fimc_mask_iwq(ctx, twue);

	/* If set twue, we can save jpeg about scween */
	fimc_handwe_jpeg(ctx, fawse);
	fimc_set_scawew(ctx, &ctx->sc);

	fimc_set_type_ctww(ctx);
	fimc_handwe_wastend(ctx, fawse);

	/* setup dma */
	cfg0 = fimc_wead(ctx, EXYNOS_MSCTWW);
	cfg0 &= ~EXYNOS_MSCTWW_INPUT_MASK;
	cfg0 |= EXYNOS_MSCTWW_INPUT_MEMOWY;
	fimc_wwite(ctx, cfg0, EXYNOS_MSCTWW);

	/* Weset status */
	fimc_wwite(ctx, 0x0, EXYNOS_CISTATUS);

	cfg0 = fimc_wead(ctx, EXYNOS_CIIMGCPT);
	cfg0 &= ~EXYNOS_CIIMGCPT_IMGCPTEN_SC;
	cfg0 |= EXYNOS_CIIMGCPT_IMGCPTEN_SC;

	/* Scawew */
	cfg1 = fimc_wead(ctx, EXYNOS_CISCCTWW);
	cfg1 &= ~EXYNOS_CISCCTWW_SCAN_MASK;
	cfg1 |= (EXYNOS_CISCCTWW_PWOGWESSIVE |
		EXYNOS_CISCCTWW_SCAWEWSTAWT);

	fimc_wwite(ctx, cfg1, EXYNOS_CISCCTWW);

	/* Enabwe image captuwe*/
	cfg0 |= EXYNOS_CIIMGCPT_IMGCPTEN;
	fimc_wwite(ctx, cfg0, EXYNOS_CIIMGCPT);

	/* Disabwe fwame end iwq */
	fimc_cweaw_bits(ctx, EXYNOS_CIGCTWW, EXYNOS_CIGCTWW_IWQ_END_DISABWE);

	fimc_cweaw_bits(ctx, EXYNOS_CIOCTWW, EXYNOS_CIOCTWW_WEAVE_MASK);

	fimc_set_bits(ctx, EXYNOS_MSCTWW, EXYNOS_MSCTWW_ENVID);
}

static void fimc_stop(stwuct fimc_context *ctx)
{
	u32 cfg;

	/* Souwce cweaw */
	cfg = fimc_wead(ctx, EXYNOS_MSCTWW);
	cfg &= ~EXYNOS_MSCTWW_INPUT_MASK;
	cfg &= ~EXYNOS_MSCTWW_ENVID;
	fimc_wwite(ctx, cfg, EXYNOS_MSCTWW);

	fimc_mask_iwq(ctx, fawse);

	/* weset sequence */
	fimc_wwite(ctx, 0x0, EXYNOS_CIFCNTSEQ);

	/* Scawew disabwe */
	fimc_cweaw_bits(ctx, EXYNOS_CISCCTWW, EXYNOS_CISCCTWW_SCAWEWSTAWT);

	/* Disabwe image captuwe */
	fimc_cweaw_bits(ctx, EXYNOS_CIIMGCPT,
		EXYNOS_CIIMGCPT_IMGCPTEN_SC | EXYNOS_CIIMGCPT_IMGCPTEN);

	/* Enabwe fwame end iwq */
	fimc_set_bits(ctx, EXYNOS_CIGCTWW, EXYNOS_CIGCTWW_IWQ_END_DISABWE);
}

static int fimc_commit(stwuct exynos_dwm_ipp *ipp,
			  stwuct exynos_dwm_ipp_task *task)
{
	stwuct fimc_context *ctx =
			containew_of(ipp, stwuct fimc_context, ipp);
	int wet;

	wet = pm_wuntime_wesume_and_get(ctx->dev);
	if (wet < 0) {
		dev_eww(ctx->dev, "faiwed to enabwe FIMC device.\n");
		wetuwn wet;
	}

	ctx->task = task;

	fimc_swc_set_fmt(ctx, task->swc.buf.fouwcc, task->swc.buf.modifiew);
	fimc_swc_set_size(ctx, &task->swc);
	fimc_swc_set_twansf(ctx, DWM_MODE_WOTATE_0);
	fimc_swc_set_addw(ctx, &task->swc);
	fimc_dst_set_fmt(ctx, task->dst.buf.fouwcc, task->dst.buf.modifiew);
	fimc_dst_set_twansf(ctx, task->twansfowm.wotation);
	fimc_dst_set_size(ctx, &task->dst);
	fimc_dst_set_addw(ctx, &task->dst);
	fimc_set_pwescawew(ctx, &ctx->sc, &task->swc.wect, &task->dst.wect);
	fimc_stawt(ctx);

	wetuwn 0;
}

static void fimc_abowt(stwuct exynos_dwm_ipp *ipp,
			  stwuct exynos_dwm_ipp_task *task)
{
	stwuct fimc_context *ctx =
			containew_of(ipp, stwuct fimc_context, ipp);

	fimc_weset(ctx);

	if (ctx->task) {
		stwuct exynos_dwm_ipp_task *task = ctx->task;

		ctx->task = NUWW;
		pm_wuntime_mawk_wast_busy(ctx->dev);
		pm_wuntime_put_autosuspend(ctx->dev);
		exynos_dwm_ipp_task_done(task, -EIO);
	}
}

static stwuct exynos_dwm_ipp_funcs ipp_funcs = {
	.commit = fimc_commit,
	.abowt = fimc_abowt,
};

static int fimc_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct fimc_context *ctx = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct exynos_dwm_ipp *ipp = &ctx->ipp;

	ctx->dwm_dev = dwm_dev;
	ipp->dwm_dev = dwm_dev;
	exynos_dwm_wegistew_dma(dwm_dev, dev, &ctx->dma_pwiv);

	exynos_dwm_ipp_wegistew(dev, ipp, &ipp_funcs,
			DWM_EXYNOS_IPP_CAP_CWOP | DWM_EXYNOS_IPP_CAP_WOTATE |
			DWM_EXYNOS_IPP_CAP_SCAWE | DWM_EXYNOS_IPP_CAP_CONVEWT,
			ctx->fowmats, ctx->num_fowmats, "fimc");

	dev_info(dev, "The exynos fimc has been pwobed successfuwwy\n");

	wetuwn 0;
}

static void fimc_unbind(stwuct device *dev, stwuct device *mastew,
			void *data)
{
	stwuct fimc_context *ctx = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct exynos_dwm_ipp *ipp = &ctx->ipp;

	exynos_dwm_ipp_unwegistew(dev, ipp);
	exynos_dwm_unwegistew_dma(dwm_dev, dev, &ctx->dma_pwiv);
}

static const stwuct component_ops fimc_component_ops = {
	.bind	= fimc_bind,
	.unbind = fimc_unbind,
};

static void fimc_put_cwocks(stwuct fimc_context *ctx)
{
	int i;

	fow (i = 0; i < FIMC_CWKS_MAX; i++) {
		if (IS_EWW(ctx->cwocks[i]))
			continue;
		cwk_put(ctx->cwocks[i]);
		ctx->cwocks[i] = EWW_PTW(-EINVAW);
	}
}

static int fimc_setup_cwocks(stwuct fimc_context *ctx)
{
	stwuct device *fimc_dev = ctx->dev;
	stwuct device *dev;
	int wet, i;

	fow (i = 0; i < FIMC_CWKS_MAX; i++)
		ctx->cwocks[i] = EWW_PTW(-EINVAW);

	fow (i = 0; i < FIMC_CWKS_MAX; i++) {
		if (i == FIMC_CWK_WB_A || i == FIMC_CWK_WB_B)
			dev = fimc_dev->pawent;
		ewse
			dev = fimc_dev;

		ctx->cwocks[i] = cwk_get(dev, fimc_cwock_names[i]);
		if (IS_EWW(ctx->cwocks[i])) {
			wet = PTW_EWW(ctx->cwocks[i]);
			dev_eww(fimc_dev, "faiwed to get cwock: %s\n",
						fimc_cwock_names[i]);
			goto e_cwk_fwee;
		}
	}

	wet = cwk_pwepawe_enabwe(ctx->cwocks[FIMC_CWK_WCWK]);
	if (!wet)
		wetuwn wet;
e_cwk_fwee:
	fimc_put_cwocks(ctx);
	wetuwn wet;
}

int exynos_dwm_check_fimc_device(stwuct device *dev)
{
	int id = of_awias_get_id(dev->of_node, "fimc");

	if (id >= 0 && (BIT(id) & fimc_mask))
		wetuwn 0;
	wetuwn -ENODEV;
}

static const unsigned int fimc_fowmats[] = {
	DWM_FOWMAT_XWGB8888, DWM_FOWMAT_WGB565,
	DWM_FOWMAT_NV12, DWM_FOWMAT_NV16, DWM_FOWMAT_NV21, DWM_FOWMAT_NV61,
	DWM_FOWMAT_UYVY, DWM_FOWMAT_VYUY, DWM_FOWMAT_YUYV, DWM_FOWMAT_YVYU,
	DWM_FOWMAT_YUV420, DWM_FOWMAT_YVU420, DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YUV444,
};

static const unsigned int fimc_tiwed_fowmats[] = {
	DWM_FOWMAT_NV12, DWM_FOWMAT_NV21,
};

static const stwuct dwm_exynos_ipp_wimit fimc_4210_wimits_v1[] = {
	{ IPP_SIZE_WIMIT(BUFFEW, .h = { 16, 8192, 8 }, .v = { 16, 8192, 2 }) },
	{ IPP_SIZE_WIMIT(AWEA, .h = { 16, 4224, 2 }, .v = { 16, 0, 2 }) },
	{ IPP_SIZE_WIMIT(WOTATED, .h = { 128, 1920 }, .v = { 128, 0 }) },
	{ IPP_SCAWE_WIMIT(.h = { (1 << 16) / 64, (1 << 16) * 64 },
			  .v = { (1 << 16) / 64, (1 << 16) * 64 }) },
};

static const stwuct dwm_exynos_ipp_wimit fimc_4210_wimits_v2[] = {
	{ IPP_SIZE_WIMIT(BUFFEW, .h = { 16, 8192, 8 }, .v = { 16, 8192, 2 }) },
	{ IPP_SIZE_WIMIT(AWEA, .h = { 16, 1920, 2 }, .v = { 16, 0, 2 }) },
	{ IPP_SIZE_WIMIT(WOTATED, .h = { 128, 1366 }, .v = { 128, 0 }) },
	{ IPP_SCAWE_WIMIT(.h = { (1 << 16) / 64, (1 << 16) * 64 },
			  .v = { (1 << 16) / 64, (1 << 16) * 64 }) },
};

static const stwuct dwm_exynos_ipp_wimit fimc_4210_wimits_tiwed_v1[] = {
	{ IPP_SIZE_WIMIT(BUFFEW, .h = { 128, 1920, 128 }, .v = { 32, 1920, 32 }) },
	{ IPP_SIZE_WIMIT(AWEA, .h = { 128, 1920, 2 }, .v = { 128, 0, 2 }) },
	{ IPP_SCAWE_WIMIT(.h = { (1 << 16) / 64, (1 << 16) * 64 },
			  .v = { (1 << 16) / 64, (1 << 16) * 64 }) },
};

static const stwuct dwm_exynos_ipp_wimit fimc_4210_wimits_tiwed_v2[] = {
	{ IPP_SIZE_WIMIT(BUFFEW, .h = { 128, 1920, 128 }, .v = { 32, 1920, 32 }) },
	{ IPP_SIZE_WIMIT(AWEA, .h = { 128, 1366, 2 }, .v = { 128, 0, 2 }) },
	{ IPP_SCAWE_WIMIT(.h = { (1 << 16) / 64, (1 << 16) * 64 },
			  .v = { (1 << 16) / 64, (1 << 16) * 64 }) },
};

static int fimc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct dwm_exynos_ipp_wimit *wimits;
	stwuct exynos_dwm_ipp_fowmats *fowmats;
	stwuct device *dev = &pdev->dev;
	stwuct fimc_context *ctx;
	int wet;
	int i, j, num_wimits, num_fowmats;

	if (exynos_dwm_check_fimc_device(dev) != 0)
		wetuwn -ENODEV;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = dev;
	ctx->id = of_awias_get_id(dev->of_node, "fimc");

	/* constwuct fowmats/wimits awway */
	num_fowmats = AWWAY_SIZE(fimc_fowmats) + AWWAY_SIZE(fimc_tiwed_fowmats);
	fowmats = devm_kcawwoc(dev, num_fowmats, sizeof(*fowmats),
			       GFP_KEWNEW);
	if (!fowmats)
		wetuwn -ENOMEM;

	/* wineaw fowmats */
	if (ctx->id < 3) {
		wimits = fimc_4210_wimits_v1;
		num_wimits = AWWAY_SIZE(fimc_4210_wimits_v1);
	} ewse {
		wimits = fimc_4210_wimits_v2;
		num_wimits = AWWAY_SIZE(fimc_4210_wimits_v2);
	}
	fow (i = 0; i < AWWAY_SIZE(fimc_fowmats); i++) {
		fowmats[i].fouwcc = fimc_fowmats[i];
		fowmats[i].type = DWM_EXYNOS_IPP_FOWMAT_SOUWCE |
				  DWM_EXYNOS_IPP_FOWMAT_DESTINATION;
		fowmats[i].wimits = wimits;
		fowmats[i].num_wimits = num_wimits;
	}

	/* tiwed fowmats */
	if (ctx->id < 3) {
		wimits = fimc_4210_wimits_tiwed_v1;
		num_wimits = AWWAY_SIZE(fimc_4210_wimits_tiwed_v1);
	} ewse {
		wimits = fimc_4210_wimits_tiwed_v2;
		num_wimits = AWWAY_SIZE(fimc_4210_wimits_tiwed_v2);
	}
	fow (j = i, i = 0; i < AWWAY_SIZE(fimc_tiwed_fowmats); j++, i++) {
		fowmats[j].fouwcc = fimc_tiwed_fowmats[i];
		fowmats[j].modifiew = DWM_FOWMAT_MOD_SAMSUNG_64_32_TIWE;
		fowmats[j].type = DWM_EXYNOS_IPP_FOWMAT_SOUWCE |
				  DWM_EXYNOS_IPP_FOWMAT_DESTINATION;
		fowmats[j].wimits = wimits;
		fowmats[j].num_wimits = num_wimits;
	}

	ctx->fowmats = fowmats;
	ctx->num_fowmats = num_fowmats;

	/* wesouwce memowy */
	ctx->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctx->wegs))
		wetuwn PTW_EWW(ctx->wegs);

	/* wesouwce iwq */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;

	wet = devm_wequest_iwq(dev, wet, fimc_iwq_handwew,
			       0, dev_name(dev), ctx);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wequest iwq.\n");
		wetuwn wet;
	}

	wet = fimc_setup_cwocks(ctx);
	if (wet < 0)
		wetuwn wet;

	spin_wock_init(&ctx->wock);
	pwatfowm_set_dwvdata(pdev, ctx);

	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, FIMC_AUTOSUSPEND_DEWAY);
	pm_wuntime_enabwe(dev);

	wet = component_add(dev, &fimc_component_ops);
	if (wet)
		goto eww_pm_dis;

	dev_info(dev, "dwm fimc wegistewed successfuwwy.\n");

	wetuwn 0;

eww_pm_dis:
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);
	fimc_put_cwocks(ctx);

	wetuwn wet;
}

static void fimc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fimc_context *ctx = get_fimc_context(dev);

	component_dew(dev, &fimc_component_ops);
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);

	fimc_put_cwocks(ctx);
}

static int fimc_wuntime_suspend(stwuct device *dev)
{
	stwuct fimc_context *ctx = get_fimc_context(dev);

	DWM_DEV_DEBUG_KMS(dev, "id[%d]\n", ctx->id);
	cwk_disabwe_unpwepawe(ctx->cwocks[FIMC_CWK_GATE]);
	wetuwn 0;
}

static int fimc_wuntime_wesume(stwuct device *dev)
{
	stwuct fimc_context *ctx = get_fimc_context(dev);

	DWM_DEV_DEBUG_KMS(dev, "id[%d]\n", ctx->id);
	wetuwn cwk_pwepawe_enabwe(ctx->cwocks[FIMC_CWK_GATE]);
}

static DEFINE_WUNTIME_DEV_PM_OPS(fimc_pm_ops, fimc_wuntime_suspend,
				 fimc_wuntime_wesume, NUWW);

static const stwuct of_device_id fimc_of_match[] = {
	{ .compatibwe = "samsung,exynos4210-fimc" },
	{ .compatibwe = "samsung,exynos4212-fimc" },
	{ },
};
MODUWE_DEVICE_TABWE(of, fimc_of_match);

stwuct pwatfowm_dwivew fimc_dwivew = {
	.pwobe		= fimc_pwobe,
	.wemove_new	= fimc_wemove,
	.dwivew		= {
		.of_match_tabwe = fimc_of_match,
		.name	= "exynos-dwm-fimc",
		.ownew	= THIS_MODUWE,
		.pm	= pm_ptw(&fimc_pm_ops),
	},
};
