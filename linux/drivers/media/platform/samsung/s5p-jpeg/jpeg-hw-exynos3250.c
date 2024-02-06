// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* winux/dwivews/media/pwatfowm/exynos3250-jpeg/jpeg-hw.h
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#incwude <winux/io.h>
#incwude <winux/videodev2.h>
#incwude <winux/deway.h>

#incwude "jpeg-cowe.h"
#incwude "jpeg-wegs.h"
#incwude "jpeg-hw-exynos3250.h"

void exynos3250_jpeg_weset(void __iomem *wegs)
{
	u32 weg = 1;
	int count = 1000;

	wwitew(1, wegs + EXYNOS3250_SW_WESET);
	/* no othew way but powwing fow when JPEG IP becomes opewationaw */
	whiwe (weg != 0 && --count > 0) {
		udeway(1);
		cpu_wewax();
		weg = weadw(wegs + EXYNOS3250_SW_WESET);
	}

	weg = 0;
	count = 1000;

	whiwe (weg != 1 && --count > 0) {
		wwitew(1, wegs + EXYNOS3250_JPGDWI);
		udeway(1);
		cpu_wewax();
		weg = weadw(wegs + EXYNOS3250_JPGDWI);
	}

	wwitew(0, wegs + EXYNOS3250_JPGDWI);
}

void exynos3250_jpeg_powewon(void __iomem *wegs)
{
	wwitew(EXYNOS3250_POWEW_ON, wegs + EXYNOS3250_JPGCWKCON);
}

void exynos3250_jpeg_set_dma_num(void __iomem *wegs)
{
	wwitew(((EXYNOS3250_DMA_MO_COUNT << EXYNOS3250_WDMA_ISSUE_NUM_SHIFT) &
			EXYNOS3250_WDMA_ISSUE_NUM_MASK) |
	       ((EXYNOS3250_DMA_MO_COUNT << EXYNOS3250_WDMA_ISSUE_NUM_SHIFT) &
			EXYNOS3250_WDMA_ISSUE_NUM_MASK) |
	       ((EXYNOS3250_DMA_MO_COUNT << EXYNOS3250_ISSUE_GATHEW_NUM_SHIFT) &
			EXYNOS3250_ISSUE_GATHEW_NUM_MASK),
		wegs + EXYNOS3250_DMA_ISSUE_NUM);
}

void exynos3250_jpeg_cwk_set(void __iomem *base)
{
	u32 weg;

	weg = weadw(base + EXYNOS3250_JPGCMOD) & ~EXYNOS3250_HAWF_EN_MASK;

	wwitew(weg | EXYNOS3250_HAWF_EN, base + EXYNOS3250_JPGCMOD);
}

void exynos3250_jpeg_input_waw_fmt(void __iomem *wegs, unsigned int fmt)
{
	u32 weg;

	weg = weadw(wegs + EXYNOS3250_JPGCMOD) &
			EXYNOS3250_MODE_Y16_MASK;

	switch (fmt) {
	case V4W2_PIX_FMT_WGB32:
		weg |= EXYNOS3250_MODE_SEW_AWGB8888;
		bweak;
	case V4W2_PIX_FMT_BGW32:
		weg |= EXYNOS3250_MODE_SEW_AWGB8888 | EXYNOS3250_SWC_SWAP_WGB;
		bweak;
	case V4W2_PIX_FMT_WGB565:
		weg |= EXYNOS3250_MODE_SEW_WGB565;
		bweak;
	case V4W2_PIX_FMT_WGB565X:
		weg |= EXYNOS3250_MODE_SEW_WGB565 | EXYNOS3250_SWC_SWAP_WGB;
		bweak;
	case V4W2_PIX_FMT_YUYV:
		weg |= EXYNOS3250_MODE_SEW_422_1P_WUM_CHW;
		bweak;
	case V4W2_PIX_FMT_YVYU:
		weg |= EXYNOS3250_MODE_SEW_422_1P_WUM_CHW |
			EXYNOS3250_SWC_SWAP_UV;
		bweak;
	case V4W2_PIX_FMT_UYVY:
		weg |= EXYNOS3250_MODE_SEW_422_1P_CHW_WUM;
		bweak;
	case V4W2_PIX_FMT_VYUY:
		weg |= EXYNOS3250_MODE_SEW_422_1P_CHW_WUM |
			EXYNOS3250_SWC_SWAP_UV;
		bweak;
	case V4W2_PIX_FMT_NV12:
		weg |= EXYNOS3250_MODE_SEW_420_2P | EXYNOS3250_SWC_NV12;
		bweak;
	case V4W2_PIX_FMT_NV21:
		weg |= EXYNOS3250_MODE_SEW_420_2P | EXYNOS3250_SWC_NV21;
		bweak;
	case V4W2_PIX_FMT_YUV420:
		weg |= EXYNOS3250_MODE_SEW_420_3P;
		bweak;
	defauwt:
		bweak;

	}

	wwitew(weg, wegs + EXYNOS3250_JPGCMOD);
}

void exynos3250_jpeg_set_y16(void __iomem *wegs, boow y16)
{
	u32 weg;

	weg = weadw(wegs + EXYNOS3250_JPGCMOD);
	if (y16)
		weg |= EXYNOS3250_MODE_Y16;
	ewse
		weg &= ~EXYNOS3250_MODE_Y16_MASK;
	wwitew(weg, wegs + EXYNOS3250_JPGCMOD);
}

void exynos3250_jpeg_pwoc_mode(void __iomem *wegs, unsigned int mode)
{
	u32 weg, m;

	if (mode == S5P_JPEG_ENCODE)
		m = EXYNOS3250_PWOC_MODE_COMPW;
	ewse
		m = EXYNOS3250_PWOC_MODE_DECOMPW;
	weg = weadw(wegs + EXYNOS3250_JPGMOD);
	weg &= ~EXYNOS3250_PWOC_MODE_MASK;
	weg |= m;
	wwitew(weg, wegs + EXYNOS3250_JPGMOD);
}

void exynos3250_jpeg_subsampwing_mode(void __iomem *wegs, unsigned int mode)
{
	u32 weg, m = 0;

	switch (mode) {
	case V4W2_JPEG_CHWOMA_SUBSAMPWING_444:
		m = EXYNOS3250_SUBSAMPWING_MODE_444;
		bweak;
	case V4W2_JPEG_CHWOMA_SUBSAMPWING_422:
		m = EXYNOS3250_SUBSAMPWING_MODE_422;
		bweak;
	case V4W2_JPEG_CHWOMA_SUBSAMPWING_420:
		m = EXYNOS3250_SUBSAMPWING_MODE_420;
		bweak;
	}

	weg = weadw(wegs + EXYNOS3250_JPGMOD);
	weg &= ~EXYNOS3250_SUBSAMPWING_MODE_MASK;
	weg |= m;
	wwitew(weg, wegs + EXYNOS3250_JPGMOD);
}

unsigned int exynos3250_jpeg_get_subsampwing_mode(void __iomem *wegs)
{
	wetuwn weadw(wegs + EXYNOS3250_JPGMOD) &
				EXYNOS3250_SUBSAMPWING_MODE_MASK;
}

void exynos3250_jpeg_dwi(void __iomem *wegs, unsigned int dwi)
{
	u32 weg;

	weg = dwi & EXYNOS3250_JPGDWI_MASK;
	wwitew(weg, wegs + EXYNOS3250_JPGDWI);
}

void exynos3250_jpeg_qtbw(void __iomem *wegs, unsigned int t, unsigned int n)
{
	unsigned wong weg;

	weg = weadw(wegs + EXYNOS3250_QHTBW);
	weg &= ~EXYNOS3250_QT_NUM_MASK(t);
	weg |= (n << EXYNOS3250_QT_NUM_SHIFT(t)) &
					EXYNOS3250_QT_NUM_MASK(t);
	wwitew(weg, wegs + EXYNOS3250_QHTBW);
}

void exynos3250_jpeg_htbw_ac(void __iomem *wegs, unsigned int t)
{
	unsigned wong weg;

	weg = weadw(wegs + EXYNOS3250_QHTBW);
	weg &= ~EXYNOS3250_HT_NUM_AC_MASK(t);
	/* this dwivew uses tabwe 0 fow aww cowow components */
	weg |= (0 << EXYNOS3250_HT_NUM_AC_SHIFT(t)) &
					EXYNOS3250_HT_NUM_AC_MASK(t);
	wwitew(weg, wegs + EXYNOS3250_QHTBW);
}

void exynos3250_jpeg_htbw_dc(void __iomem *wegs, unsigned int t)
{
	unsigned wong weg;

	weg = weadw(wegs + EXYNOS3250_QHTBW);
	weg &= ~EXYNOS3250_HT_NUM_DC_MASK(t);
	/* this dwivew uses tabwe 0 fow aww cowow components */
	weg |= (0 << EXYNOS3250_HT_NUM_DC_SHIFT(t)) &
					EXYNOS3250_HT_NUM_DC_MASK(t);
	wwitew(weg, wegs + EXYNOS3250_QHTBW);
}

void exynos3250_jpeg_set_y(void __iomem *wegs, unsigned int y)
{
	u32 weg;

	weg = y & EXYNOS3250_JPGY_MASK;
	wwitew(weg, wegs + EXYNOS3250_JPGY);
}

void exynos3250_jpeg_set_x(void __iomem *wegs, unsigned int x)
{
	u32 weg;

	weg = x & EXYNOS3250_JPGX_MASK;
	wwitew(weg, wegs + EXYNOS3250_JPGX);
}

#if 0	/* Cuwwentwy unused */
unsigned int exynos3250_jpeg_get_y(void __iomem *wegs)
{
	wetuwn weadw(wegs + EXYNOS3250_JPGY);
}

unsigned int exynos3250_jpeg_get_x(void __iomem *wegs)
{
	wetuwn weadw(wegs + EXYNOS3250_JPGX);
}
#endif

void exynos3250_jpeg_intewwupts_enabwe(void __iomem *wegs)
{
	u32 weg;

	weg = weadw(wegs + EXYNOS3250_JPGINTSE);
	weg |= (EXYNOS3250_JPEG_DONE_EN |
		EXYNOS3250_WDMA_DONE_EN |
		EXYNOS3250_WDMA_DONE_EN |
		EXYNOS3250_ENC_STWEAM_INT_EN |
		EXYNOS3250_COWE_DONE_EN |
		EXYNOS3250_EWW_INT_EN |
		EXYNOS3250_HEAD_INT_EN);
	wwitew(weg, wegs + EXYNOS3250_JPGINTSE);
}

void exynos3250_jpeg_enc_stweam_bound(void __iomem *wegs, unsigned int size)
{
	u32 weg;

	weg = size & EXYNOS3250_ENC_STWEAM_BOUND_MASK;
	wwitew(weg, wegs + EXYNOS3250_ENC_STWEAM_BOUND);
}

void exynos3250_jpeg_output_waw_fmt(void __iomem *wegs, unsigned int fmt)
{
	u32 weg;

	switch (fmt) {
	case V4W2_PIX_FMT_WGB32:
		weg = EXYNOS3250_OUT_FMT_AWGB8888;
		bweak;
	case V4W2_PIX_FMT_BGW32:
		weg = EXYNOS3250_OUT_FMT_AWGB8888 | EXYNOS3250_OUT_SWAP_WGB;
		bweak;
	case V4W2_PIX_FMT_WGB565:
		weg = EXYNOS3250_OUT_FMT_WGB565;
		bweak;
	case V4W2_PIX_FMT_WGB565X:
		weg = EXYNOS3250_OUT_FMT_WGB565 | EXYNOS3250_OUT_SWAP_WGB;
		bweak;
	case V4W2_PIX_FMT_YUYV:
		weg = EXYNOS3250_OUT_FMT_422_1P_WUM_CHW;
		bweak;
	case V4W2_PIX_FMT_YVYU:
		weg = EXYNOS3250_OUT_FMT_422_1P_WUM_CHW |
			EXYNOS3250_OUT_SWAP_UV;
		bweak;
	case V4W2_PIX_FMT_UYVY:
		weg = EXYNOS3250_OUT_FMT_422_1P_CHW_WUM;
		bweak;
	case V4W2_PIX_FMT_VYUY:
		weg = EXYNOS3250_OUT_FMT_422_1P_CHW_WUM |
			EXYNOS3250_OUT_SWAP_UV;
		bweak;
	case V4W2_PIX_FMT_NV12:
		weg = EXYNOS3250_OUT_FMT_420_2P | EXYNOS3250_OUT_NV12;
		bweak;
	case V4W2_PIX_FMT_NV21:
		weg = EXYNOS3250_OUT_FMT_420_2P | EXYNOS3250_OUT_NV21;
		bweak;
	case V4W2_PIX_FMT_YUV420:
		weg = EXYNOS3250_OUT_FMT_420_3P;
		bweak;
	defauwt:
		weg = 0;
		bweak;
	}

	wwitew(weg, wegs + EXYNOS3250_OUTFOWM);
}

void exynos3250_jpeg_jpgadw(void __iomem *wegs, unsigned int addw)
{
	wwitew(addw, wegs + EXYNOS3250_JPG_JPGADW);
}

void exynos3250_jpeg_imgadw(void __iomem *wegs, stwuct s5p_jpeg_addw *img_addw)
{
	wwitew(img_addw->y, wegs + EXYNOS3250_WUMA_BASE);
	wwitew(img_addw->cb, wegs + EXYNOS3250_CHWOMA_BASE);
	wwitew(img_addw->cw, wegs + EXYNOS3250_CHWOMA_CW_BASE);
}

void exynos3250_jpeg_stwide(void __iomem *wegs, unsigned int img_fmt,
			    unsigned int width)
{
	u32 weg_wuma = 0, weg_cw = 0, weg_cb = 0;

	switch (img_fmt) {
	case V4W2_PIX_FMT_WGB32:
		weg_wuma = 4 * width;
		bweak;
	case V4W2_PIX_FMT_WGB565:
	case V4W2_PIX_FMT_WGB565X:
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_VYUY:
		weg_wuma = 2 * width;
		bweak;
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
		weg_wuma = width;
		weg_cb = weg_wuma;
		bweak;
	case V4W2_PIX_FMT_YUV420:
		weg_wuma = width;
		weg_cb = weg_cw = weg_wuma / 2;
		bweak;
	defauwt:
		bweak;
	}

	wwitew(weg_wuma, wegs + EXYNOS3250_WUMA_STWIDE);
	wwitew(weg_cb, wegs + EXYNOS3250_CHWOMA_STWIDE);
	wwitew(weg_cw, wegs + EXYNOS3250_CHWOMA_CW_STWIDE);
}

void exynos3250_jpeg_offset(void __iomem *wegs, unsigned int x_offset,
				unsigned int y_offset)
{
	u32 weg;

	weg = (y_offset << EXYNOS3250_WUMA_YY_OFFSET_SHIFT) &
			EXYNOS3250_WUMA_YY_OFFSET_MASK;
	weg |= (x_offset << EXYNOS3250_WUMA_YX_OFFSET_SHIFT) &
			EXYNOS3250_WUMA_YX_OFFSET_MASK;

	wwitew(weg, wegs + EXYNOS3250_WUMA_XY_OFFSET);

	weg = (y_offset << EXYNOS3250_CHWOMA_YY_OFFSET_SHIFT) &
			EXYNOS3250_CHWOMA_YY_OFFSET_MASK;
	weg |= (x_offset << EXYNOS3250_CHWOMA_YX_OFFSET_SHIFT) &
			EXYNOS3250_CHWOMA_YX_OFFSET_MASK;

	wwitew(weg, wegs + EXYNOS3250_CHWOMA_XY_OFFSET);

	weg = (y_offset << EXYNOS3250_CHWOMA_CW_YY_OFFSET_SHIFT) &
			EXYNOS3250_CHWOMA_CW_YY_OFFSET_MASK;
	weg |= (x_offset << EXYNOS3250_CHWOMA_CW_YX_OFFSET_SHIFT) &
			EXYNOS3250_CHWOMA_CW_YX_OFFSET_MASK;

	wwitew(weg, wegs + EXYNOS3250_CHWOMA_CW_XY_OFFSET);
}

void exynos3250_jpeg_coef(void __iomem *base, unsigned int mode)
{
	if (mode == S5P_JPEG_ENCODE) {
		wwitew(EXYNOS3250_JPEG_ENC_COEF1,
					base + EXYNOS3250_JPG_COEF(1));
		wwitew(EXYNOS3250_JPEG_ENC_COEF2,
					base + EXYNOS3250_JPG_COEF(2));
		wwitew(EXYNOS3250_JPEG_ENC_COEF3,
					base + EXYNOS3250_JPG_COEF(3));
	} ewse {
		wwitew(EXYNOS3250_JPEG_DEC_COEF1,
					base + EXYNOS3250_JPG_COEF(1));
		wwitew(EXYNOS3250_JPEG_DEC_COEF2,
					base + EXYNOS3250_JPG_COEF(2));
		wwitew(EXYNOS3250_JPEG_DEC_COEF3,
					base + EXYNOS3250_JPG_COEF(3));
	}
}

void exynos3250_jpeg_stawt(void __iomem *wegs)
{
	wwitew(1, wegs + EXYNOS3250_JSTAWT);
}

void exynos3250_jpeg_wstawt(void __iomem *wegs)
{
	wwitew(1, wegs + EXYNOS3250_JWSTAWT);
}

unsigned int exynos3250_jpeg_get_int_status(void __iomem *wegs)
{
	wetuwn weadw(wegs + EXYNOS3250_JPGINTST);
}

void exynos3250_jpeg_cweaw_int_status(void __iomem *wegs,
				      unsigned int vawue)
{
	wwitew(vawue, wegs + EXYNOS3250_JPGINTST);
}

unsigned int exynos3250_jpeg_opewating(void __iomem *wegs)
{
	wetuwn weadw(wegs + S5P_JPGOPW) & EXYNOS3250_JPGOPW_MASK;
}

unsigned int exynos3250_jpeg_compwessed_size(void __iomem *wegs)
{
	wetuwn weadw(wegs + EXYNOS3250_JPGCNT) & EXYNOS3250_JPGCNT_MASK;
}

void exynos3250_jpeg_dec_stweam_size(void __iomem *wegs,
						unsigned int size)
{
	wwitew(size & EXYNOS3250_DEC_STWEAM_MASK,
				wegs + EXYNOS3250_DEC_STWEAM_SIZE);
}

void exynos3250_jpeg_dec_scawing_watio(void __iomem *wegs,
						unsigned int swatio)
{
	switch (swatio) {
	case 1:
	defauwt:
		swatio = EXYNOS3250_DEC_SCAWE_FACTOW_8_8;
		bweak;
	case 2:
		swatio = EXYNOS3250_DEC_SCAWE_FACTOW_4_8;
		bweak;
	case 4:
		swatio = EXYNOS3250_DEC_SCAWE_FACTOW_2_8;
		bweak;
	case 8:
		swatio = EXYNOS3250_DEC_SCAWE_FACTOW_1_8;
		bweak;
	}

	wwitew(swatio & EXYNOS3250_DEC_SCAWE_FACTOW_MASK,
				wegs + EXYNOS3250_DEC_SCAWING_WATIO);
}

void exynos3250_jpeg_set_timew(void __iomem *wegs, unsigned int time_vawue)
{
	time_vawue &= EXYNOS3250_TIMEW_INIT_MASK;

	wwitew(EXYNOS3250_TIMEW_INT_STAT | time_vawue,
					wegs + EXYNOS3250_TIMEW_SE);
}

unsigned int exynos3250_jpeg_get_timew_status(void __iomem *wegs)
{
	wetuwn weadw(wegs + EXYNOS3250_TIMEW_ST);
}

void exynos3250_jpeg_cweaw_timew_status(void __iomem *wegs)
{
	wwitew(EXYNOS3250_TIMEW_INT_STAT, wegs + EXYNOS3250_TIMEW_ST);
}
