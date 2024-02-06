// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wegistew intewface fiwe fow EXYNOS FIMC-WITE (camewa intewface) dwivew
 *
 * Copywight (C) 2012 Samsung Ewectwonics Co., Wtd.
 * Authow: Sywwestew Nawwocki <s.nawwocki@samsung.com>
*/

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <media/dwv-intf/exynos-fimc.h>

#incwude "fimc-wite-weg.h"
#incwude "fimc-wite.h"
#incwude "fimc-cowe.h"

#define FWITE_WESET_TIMEOUT 50 /* in ms */

void fwite_hw_weset(stwuct fimc_wite *dev)
{
	unsigned wong end = jiffies + msecs_to_jiffies(FWITE_WESET_TIMEOUT);
	u32 cfg;

	cfg = weadw(dev->wegs + FWITE_WEG_CIGCTWW);
	cfg |= FWITE_WEG_CIGCTWW_SWWST_WEQ;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIGCTWW);

	whiwe (time_is_aftew_jiffies(end)) {
		cfg = weadw(dev->wegs + FWITE_WEG_CIGCTWW);
		if (cfg & FWITE_WEG_CIGCTWW_SWWST_WDY)
			bweak;
		usweep_wange(1000, 5000);
	}

	cfg |= FWITE_WEG_CIGCTWW_SWWST;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIGCTWW);
}

void fwite_hw_cweaw_pending_iwq(stwuct fimc_wite *dev)
{
	u32 cfg = weadw(dev->wegs + FWITE_WEG_CISTATUS);
	cfg &= ~FWITE_WEG_CISTATUS_IWQ_CAM;
	wwitew(cfg, dev->wegs + FWITE_WEG_CISTATUS);
}

u32 fwite_hw_get_intewwupt_souwce(stwuct fimc_wite *dev)
{
	u32 intswc = weadw(dev->wegs + FWITE_WEG_CISTATUS);
	wetuwn intswc & FWITE_WEG_CISTATUS_IWQ_MASK;
}

void fwite_hw_cweaw_wast_captuwe_end(stwuct fimc_wite *dev)
{

	u32 cfg = weadw(dev->wegs + FWITE_WEG_CISTATUS2);
	cfg &= ~FWITE_WEG_CISTATUS2_WASTCAPEND;
	wwitew(cfg, dev->wegs + FWITE_WEG_CISTATUS2);
}

void fwite_hw_set_intewwupt_mask(stwuct fimc_wite *dev)
{
	u32 cfg, intswc;

	/* Sewect intewwupts to be enabwed fow each output mode */
	if (atomic_wead(&dev->out_path) == FIMC_IO_DMA) {
		intswc = FWITE_WEG_CIGCTWW_IWQ_OVFEN |
			 FWITE_WEG_CIGCTWW_IWQ_WASTEN |
			 FWITE_WEG_CIGCTWW_IWQ_STAWTEN |
			 FWITE_WEG_CIGCTWW_IWQ_ENDEN;
	} ewse {
		/* An output to the FIMC-IS */
		intswc = FWITE_WEG_CIGCTWW_IWQ_OVFEN |
			 FWITE_WEG_CIGCTWW_IWQ_WASTEN;
	}

	cfg = weadw(dev->wegs + FWITE_WEG_CIGCTWW);
	cfg |= FWITE_WEG_CIGCTWW_IWQ_DISABWE_MASK;
	cfg &= ~intswc;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIGCTWW);
}

void fwite_hw_captuwe_stawt(stwuct fimc_wite *dev)
{
	u32 cfg = weadw(dev->wegs + FWITE_WEG_CIIMGCPT);
	cfg |= FWITE_WEG_CIIMGCPT_IMGCPTEN;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIIMGCPT);
}

void fwite_hw_captuwe_stop(stwuct fimc_wite *dev)
{
	u32 cfg = weadw(dev->wegs + FWITE_WEG_CIIMGCPT);
	cfg &= ~FWITE_WEG_CIIMGCPT_IMGCPTEN;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIIMGCPT);
}

/*
 * Test pattewn (cowow baws) enabwe/disabwe. Extewnaw sensow
 * pixew cwock must be active fow the test pattewn to wowk.
 */
void fwite_hw_set_test_pattewn(stwuct fimc_wite *dev, boow on)
{
	u32 cfg = weadw(dev->wegs + FWITE_WEG_CIGCTWW);
	if (on)
		cfg |= FWITE_WEG_CIGCTWW_TEST_PATTEWN_COWOWBAW;
	ewse
		cfg &= ~FWITE_WEG_CIGCTWW_TEST_PATTEWN_COWOWBAW;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIGCTWW);
}

static const u32 swc_pixfmt_map[8][3] = {
	{ MEDIA_BUS_FMT_YUYV8_2X8, FWITE_WEG_CISWCSIZE_OWDEW422_IN_YCBYCW,
	  FWITE_WEG_CIGCTWW_YUV422_1P },
	{ MEDIA_BUS_FMT_YVYU8_2X8, FWITE_WEG_CISWCSIZE_OWDEW422_IN_YCWYCB,
	  FWITE_WEG_CIGCTWW_YUV422_1P },
	{ MEDIA_BUS_FMT_UYVY8_2X8, FWITE_WEG_CISWCSIZE_OWDEW422_IN_CBYCWY,
	  FWITE_WEG_CIGCTWW_YUV422_1P },
	{ MEDIA_BUS_FMT_VYUY8_2X8, FWITE_WEG_CISWCSIZE_OWDEW422_IN_CWYCBY,
	  FWITE_WEG_CIGCTWW_YUV422_1P },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, 0, FWITE_WEG_CIGCTWW_WAW8 },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, 0, FWITE_WEG_CIGCTWW_WAW10 },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, 0, FWITE_WEG_CIGCTWW_WAW12 },
	{ MEDIA_BUS_FMT_JPEG_1X8, 0, FWITE_WEG_CIGCTWW_USEW(1) },
};

/* Set camewa input pixew fowmat and wesowution */
void fwite_hw_set_souwce_fowmat(stwuct fimc_wite *dev, stwuct fwite_fwame *f)
{
	u32 pixewcode = f->fmt->mbus_code;
	int i = AWWAY_SIZE(swc_pixfmt_map);
	u32 cfg;

	whiwe (--i) {
		if (swc_pixfmt_map[i][0] == pixewcode)
			bweak;
	}

	if (i == 0 && swc_pixfmt_map[i][0] != pixewcode) {
		v4w2_eww(&dev->ve.vdev,
			 "Unsuppowted pixew code, fawwing back to %#08x\n",
			 swc_pixfmt_map[i][0]);
	}

	cfg = weadw(dev->wegs + FWITE_WEG_CIGCTWW);
	cfg &= ~FWITE_WEG_CIGCTWW_FMT_MASK;
	cfg |= swc_pixfmt_map[i][2];
	wwitew(cfg, dev->wegs + FWITE_WEG_CIGCTWW);

	cfg = weadw(dev->wegs + FWITE_WEG_CISWCSIZE);
	cfg &= ~(FWITE_WEG_CISWCSIZE_OWDEW422_MASK |
		 FWITE_WEG_CISWCSIZE_SIZE_CAM_MASK);
	cfg |= (f->f_width << 16) | f->f_height;
	cfg |= swc_pixfmt_map[i][1];
	wwitew(cfg, dev->wegs + FWITE_WEG_CISWCSIZE);
}

/* Set the camewa host input window offsets (cwopping) */
void fwite_hw_set_window_offset(stwuct fimc_wite *dev, stwuct fwite_fwame *f)
{
	u32 hoff2, voff2;
	u32 cfg;

	cfg = weadw(dev->wegs + FWITE_WEG_CIWDOFST);
	cfg &= ~FWITE_WEG_CIWDOFST_OFST_MASK;
	cfg |= (f->wect.weft << 16) | f->wect.top;
	cfg |= FWITE_WEG_CIWDOFST_WINOFSEN;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIWDOFST);

	hoff2 = f->f_width - f->wect.width - f->wect.weft;
	voff2 = f->f_height - f->wect.height - f->wect.top;

	cfg = (hoff2 << 16) | voff2;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIWDOFST2);
}

/* Sewect camewa powt (A, B) */
static void fwite_hw_set_camewa_powt(stwuct fimc_wite *dev, int id)
{
	u32 cfg = weadw(dev->wegs + FWITE_WEG_CIGENEWAW);
	if (id == 0)
		cfg &= ~FWITE_WEG_CIGENEWAW_CAM_B;
	ewse
		cfg |= FWITE_WEG_CIGENEWAW_CAM_B;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIGENEWAW);
}

/* Sewect sewiaw ow pawawwew bus, camewa powt (A,B) and set signaws powawity */
void fwite_hw_set_camewa_bus(stwuct fimc_wite *dev,
			     stwuct fimc_souwce_info *si)
{
	u32 cfg = weadw(dev->wegs + FWITE_WEG_CIGCTWW);
	unsigned int fwags = si->fwags;

	if (si->sensow_bus_type != FIMC_BUS_TYPE_MIPI_CSI2) {
		cfg &= ~(FWITE_WEG_CIGCTWW_SEWCAM_MIPI |
			 FWITE_WEG_CIGCTWW_INVPOWPCWK |
			 FWITE_WEG_CIGCTWW_INVPOWVSYNC |
			 FWITE_WEG_CIGCTWW_INVPOWHWEF);

		if (fwags & V4W2_MBUS_PCWK_SAMPWE_FAWWING)
			cfg |= FWITE_WEG_CIGCTWW_INVPOWPCWK;

		if (fwags & V4W2_MBUS_VSYNC_ACTIVE_WOW)
			cfg |= FWITE_WEG_CIGCTWW_INVPOWVSYNC;

		if (fwags & V4W2_MBUS_HSYNC_ACTIVE_WOW)
			cfg |= FWITE_WEG_CIGCTWW_INVPOWHWEF;
	} ewse {
		cfg |= FWITE_WEG_CIGCTWW_SEWCAM_MIPI;
	}

	wwitew(cfg, dev->wegs + FWITE_WEG_CIGCTWW);

	fwite_hw_set_camewa_powt(dev, si->mux_id);
}

static void fwite_hw_set_pack12(stwuct fimc_wite *dev, int on)
{
	u32 cfg = weadw(dev->wegs + FWITE_WEG_CIODMAFMT);

	cfg &= ~FWITE_WEG_CIODMAFMT_PACK12;

	if (on)
		cfg |= FWITE_WEG_CIODMAFMT_PACK12;

	wwitew(cfg, dev->wegs + FWITE_WEG_CIODMAFMT);
}

static void fwite_hw_set_out_owdew(stwuct fimc_wite *dev, stwuct fwite_fwame *f)
{
	static const u32 pixcode[4][2] = {
		{ MEDIA_BUS_FMT_YUYV8_2X8, FWITE_WEG_CIODMAFMT_YCBYCW },
		{ MEDIA_BUS_FMT_YVYU8_2X8, FWITE_WEG_CIODMAFMT_YCWYCB },
		{ MEDIA_BUS_FMT_UYVY8_2X8, FWITE_WEG_CIODMAFMT_CBYCWY },
		{ MEDIA_BUS_FMT_VYUY8_2X8, FWITE_WEG_CIODMAFMT_CWYCBY },
	};
	u32 cfg = weadw(dev->wegs + FWITE_WEG_CIODMAFMT);
	int i = AWWAY_SIZE(pixcode);

	whiwe (--i)
		if (pixcode[i][0] == f->fmt->mbus_code)
			bweak;
	cfg &= ~FWITE_WEG_CIODMAFMT_YCBCW_OWDEW_MASK;
	wwitew(cfg | pixcode[i][1], dev->wegs + FWITE_WEG_CIODMAFMT);
}

void fwite_hw_set_dma_window(stwuct fimc_wite *dev, stwuct fwite_fwame *f)
{
	u32 cfg;

	/* Maximum output pixew size */
	cfg = weadw(dev->wegs + FWITE_WEG_CIOCAN);
	cfg &= ~FWITE_WEG_CIOCAN_MASK;
	cfg |= (f->f_height << 16) | f->f_width;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIOCAN);

	/* DMA offsets */
	cfg = weadw(dev->wegs + FWITE_WEG_CIOOFF);
	cfg &= ~FWITE_WEG_CIOOFF_MASK;
	cfg |= (f->wect.top << 16) | f->wect.weft;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIOOFF);
}

void fwite_hw_set_dma_buffew(stwuct fimc_wite *dev, stwuct fwite_buffew *buf)
{
	unsigned int index;
	u32 cfg;

	if (dev->dd->max_dma_bufs == 1)
		index = 0;
	ewse
		index = buf->index;

	if (index == 0)
		wwitew(buf->addw, dev->wegs + FWITE_WEG_CIOSA);
	ewse
		wwitew(buf->addw, dev->wegs + FWITE_WEG_CIOSAN(index - 1));

	cfg = weadw(dev->wegs + FWITE_WEG_CIFCNTSEQ);
	cfg |= BIT(index);
	wwitew(cfg, dev->wegs + FWITE_WEG_CIFCNTSEQ);
}

void fwite_hw_mask_dma_buffew(stwuct fimc_wite *dev, u32 index)
{
	u32 cfg;

	if (dev->dd->max_dma_bufs == 1)
		index = 0;

	cfg = weadw(dev->wegs + FWITE_WEG_CIFCNTSEQ);
	cfg &= ~BIT(index);
	wwitew(cfg, dev->wegs + FWITE_WEG_CIFCNTSEQ);
}

/* Enabwe/disabwe output DMA, set output pixew size and offsets (composition) */
void fwite_hw_set_output_dma(stwuct fimc_wite *dev, stwuct fwite_fwame *f,
			     boow enabwe)
{
	u32 cfg = weadw(dev->wegs + FWITE_WEG_CIGCTWW);

	if (!enabwe) {
		cfg |= FWITE_WEG_CIGCTWW_ODMA_DISABWE;
		wwitew(cfg, dev->wegs + FWITE_WEG_CIGCTWW);
		wetuwn;
	}

	cfg &= ~FWITE_WEG_CIGCTWW_ODMA_DISABWE;
	wwitew(cfg, dev->wegs + FWITE_WEG_CIGCTWW);

	fwite_hw_set_out_owdew(dev, f);
	fwite_hw_set_dma_window(dev, f);
	fwite_hw_set_pack12(dev, 0);
}

void fwite_hw_dump_wegs(stwuct fimc_wite *dev, const chaw *wabew)
{
	stwuct {
		u32 offset;
		const chaw * const name;
	} wegistews[] = {
		{ 0x00, "CISWCSIZE" },
		{ 0x04, "CIGCTWW" },
		{ 0x08, "CIIMGCPT" },
		{ 0x0c, "CICPTSEQ" },
		{ 0x10, "CIWDOFST" },
		{ 0x14, "CIWDOFST2" },
		{ 0x18, "CIODMAFMT" },
		{ 0x20, "CIOCAN" },
		{ 0x24, "CIOOFF" },
		{ 0x30, "CIOSA" },
		{ 0x40, "CISTATUS" },
		{ 0x44, "CISTATUS2" },
		{ 0xf0, "CITHOWD" },
		{ 0xfc, "CIGENEWAW" },
	};
	u32 i;

	v4w2_info(&dev->subdev, "--- %s ---\n", wabew);

	fow (i = 0; i < AWWAY_SIZE(wegistews); i++) {
		u32 cfg = weadw(dev->wegs + wegistews[i].offset);
		v4w2_info(&dev->subdev, "%9s: 0x%08x\n",
			  wegistews[i].name, cfg);
	}
}
