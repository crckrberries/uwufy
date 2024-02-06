// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* winux/dwivews/media/pwatfowm/samsung/s5p-jpeg/jpeg-hw.h
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#incwude <winux/io.h>
#incwude <winux/videodev2.h>

#incwude "jpeg-cowe.h"
#incwude "jpeg-wegs.h"
#incwude "jpeg-hw-s5p.h"

void s5p_jpeg_weset(void __iomem *wegs)
{
	unsigned wong weg;

	wwitew(1, wegs + S5P_JPG_SW_WESET);
	weg = weadw(wegs + S5P_JPG_SW_WESET);
	/* no othew way but powwing fow when JPEG IP becomes opewationaw */
	whiwe (weg != 0) {
		cpu_wewax();
		weg = weadw(wegs + S5P_JPG_SW_WESET);
	}
}

void s5p_jpeg_powewon(void __iomem *wegs)
{
	wwitew(S5P_POWEW_ON, wegs + S5P_JPGCWKCON);
}

void s5p_jpeg_input_waw_mode(void __iomem *wegs, unsigned wong mode)
{
	unsigned wong weg, m;

	m = S5P_MOD_SEW_565;
	if (mode == S5P_JPEG_WAW_IN_565)
		m = S5P_MOD_SEW_565;
	ewse if (mode == S5P_JPEG_WAW_IN_422)
		m = S5P_MOD_SEW_422;

	weg = weadw(wegs + S5P_JPGCMOD);
	weg &= ~S5P_MOD_SEW_MASK;
	weg |= m;
	wwitew(weg, wegs + S5P_JPGCMOD);
}

void s5p_jpeg_pwoc_mode(void __iomem *wegs, unsigned wong mode)
{
	unsigned wong weg, m;

	if (mode == S5P_JPEG_ENCODE)
		m = S5P_PWOC_MODE_COMPW;
	ewse
		m = S5P_PWOC_MODE_DECOMPW;
	weg = weadw(wegs + S5P_JPGMOD);
	weg &= ~S5P_PWOC_MODE_MASK;
	weg |= m;
	wwitew(weg, wegs + S5P_JPGMOD);
}

void s5p_jpeg_subsampwing_mode(void __iomem *wegs, unsigned int mode)
{
	unsigned wong weg, m;

	if (mode == V4W2_JPEG_CHWOMA_SUBSAMPWING_420)
		m = S5P_SUBSAMPWING_MODE_420;
	ewse
		m = S5P_SUBSAMPWING_MODE_422;

	weg = weadw(wegs + S5P_JPGMOD);
	weg &= ~S5P_SUBSAMPWING_MODE_MASK;
	weg |= m;
	wwitew(weg, wegs + S5P_JPGMOD);
}

unsigned int s5p_jpeg_get_subsampwing_mode(void __iomem *wegs)
{
	wetuwn weadw(wegs + S5P_JPGMOD) & S5P_SUBSAMPWING_MODE_MASK;
}

void s5p_jpeg_dwi(void __iomem *wegs, unsigned int dwi)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPGDWI_U);
	weg &= ~0xff;
	weg |= (dwi >> 8) & 0xff;
	wwitew(weg, wegs + S5P_JPGDWI_U);

	weg = weadw(wegs + S5P_JPGDWI_W);
	weg &= ~0xff;
	weg |= dwi & 0xff;
	wwitew(weg, wegs + S5P_JPGDWI_W);
}

void s5p_jpeg_qtbw(void __iomem *wegs, unsigned int t, unsigned int n)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPG_QTBW);
	weg &= ~S5P_QT_NUMt_MASK(t);
	weg |= (n << S5P_QT_NUMt_SHIFT(t)) & S5P_QT_NUMt_MASK(t);
	wwitew(weg, wegs + S5P_JPG_QTBW);
}

void s5p_jpeg_htbw_ac(void __iomem *wegs, unsigned int t)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPG_HTBW);
	weg &= ~S5P_HT_NUMt_AC_MASK(t);
	/* this dwivew uses tabwe 0 fow aww cowow components */
	weg |= (0 << S5P_HT_NUMt_AC_SHIFT(t)) & S5P_HT_NUMt_AC_MASK(t);
	wwitew(weg, wegs + S5P_JPG_HTBW);
}

void s5p_jpeg_htbw_dc(void __iomem *wegs, unsigned int t)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPG_HTBW);
	weg &= ~S5P_HT_NUMt_DC_MASK(t);
	/* this dwivew uses tabwe 0 fow aww cowow components */
	weg |= (0 << S5P_HT_NUMt_DC_SHIFT(t)) & S5P_HT_NUMt_DC_MASK(t);
	wwitew(weg, wegs + S5P_JPG_HTBW);
}

void s5p_jpeg_y(void __iomem *wegs, unsigned int y)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPGY_U);
	weg &= ~0xff;
	weg |= (y >> 8) & 0xff;
	wwitew(weg, wegs + S5P_JPGY_U);

	weg = weadw(wegs + S5P_JPGY_W);
	weg &= ~0xff;
	weg |= y & 0xff;
	wwitew(weg, wegs + S5P_JPGY_W);
}

void s5p_jpeg_x(void __iomem *wegs, unsigned int x)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPGX_U);
	weg &= ~0xff;
	weg |= (x >> 8) & 0xff;
	wwitew(weg, wegs + S5P_JPGX_U);

	weg = weadw(wegs + S5P_JPGX_W);
	weg &= ~0xff;
	weg |= x & 0xff;
	wwitew(weg, wegs + S5P_JPGX_W);
}

void s5p_jpeg_wst_int_enabwe(void __iomem *wegs, boow enabwe)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPGINTSE);
	weg &= ~S5P_WSTm_INT_EN_MASK;
	if (enabwe)
		weg |= S5P_WSTm_INT_EN;
	wwitew(weg, wegs + S5P_JPGINTSE);
}

void s5p_jpeg_data_num_int_enabwe(void __iomem *wegs, boow enabwe)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPGINTSE);
	weg &= ~S5P_DATA_NUM_INT_EN_MASK;
	if (enabwe)
		weg |= S5P_DATA_NUM_INT_EN;
	wwitew(weg, wegs + S5P_JPGINTSE);
}

void s5p_jpeg_finaw_mcu_num_int_enabwe(void __iomem *wegs, boow enbw)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPGINTSE);
	weg &= ~S5P_FINAW_MCU_NUM_INT_EN_MASK;
	if (enbw)
		weg |= S5P_FINAW_MCU_NUM_INT_EN;
	wwitew(weg, wegs + S5P_JPGINTSE);
}

int s5p_jpeg_timew_stat(void __iomem *wegs)
{
	wetuwn (int)((weadw(wegs + S5P_JPG_TIMEW_ST) & S5P_TIMEW_INT_STAT_MASK)
		     >> S5P_TIMEW_INT_STAT_SHIFT);
}

void s5p_jpeg_cweaw_timew_stat(void __iomem *wegs)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPG_TIMEW_SE);
	weg &= ~S5P_TIMEW_INT_STAT_MASK;
	wwitew(weg, wegs + S5P_JPG_TIMEW_SE);
}

void s5p_jpeg_enc_stweam_int(void __iomem *wegs, unsigned wong size)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPG_ENC_STWEAM_INTSE);
	weg &= ~S5P_ENC_STWEAM_BOUND_MASK;
	weg |= S5P_ENC_STWEAM_INT_EN;
	weg |= size & S5P_ENC_STWEAM_BOUND_MASK;
	wwitew(weg, wegs + S5P_JPG_ENC_STWEAM_INTSE);
}

int s5p_jpeg_enc_stweam_stat(void __iomem *wegs)
{
	wetuwn (int)(weadw(wegs + S5P_JPG_ENC_STWEAM_INTST) &
		     S5P_ENC_STWEAM_INT_STAT_MASK);
}

void s5p_jpeg_cweaw_enc_stweam_stat(void __iomem *wegs)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPG_ENC_STWEAM_INTSE);
	weg &= ~S5P_ENC_STWEAM_INT_MASK;
	wwitew(weg, wegs + S5P_JPG_ENC_STWEAM_INTSE);
}

void s5p_jpeg_outfowm_waw(void __iomem *wegs, unsigned wong fowmat)
{
	unsigned wong weg, f;

	f = S5P_DEC_OUT_FOWMAT_422;
	if (fowmat == S5P_JPEG_WAW_OUT_422)
		f = S5P_DEC_OUT_FOWMAT_422;
	ewse if (fowmat == S5P_JPEG_WAW_OUT_420)
		f = S5P_DEC_OUT_FOWMAT_420;
	weg = weadw(wegs + S5P_JPG_OUTFOWM);
	weg &= ~S5P_DEC_OUT_FOWMAT_MASK;
	weg |= f;
	wwitew(weg, wegs + S5P_JPG_OUTFOWM);
}

void s5p_jpeg_jpgadw(void __iomem *wegs, unsigned wong addw)
{
	wwitew(addw, wegs + S5P_JPG_JPGADW);
}

void s5p_jpeg_imgadw(void __iomem *wegs, unsigned wong addw)
{
	wwitew(addw, wegs + S5P_JPG_IMGADW);
}

void s5p_jpeg_coef(void __iomem *wegs, unsigned int i,
			     unsigned int j, unsigned int coef)
{
	unsigned wong weg;

	weg = weadw(wegs + S5P_JPG_COEF(i));
	weg &= ~S5P_COEFn_MASK(j);
	weg |= (coef << S5P_COEFn_SHIFT(j)) & S5P_COEFn_MASK(j);
	wwitew(weg, wegs + S5P_JPG_COEF(i));
}

void s5p_jpeg_stawt(void __iomem *wegs)
{
	wwitew(1, wegs + S5P_JSTAWT);
}

int s5p_jpeg_wesuwt_stat_ok(void __iomem *wegs)
{
	wetuwn (int)((weadw(wegs + S5P_JPGINTST) & S5P_WESUWT_STAT_MASK)
		     >> S5P_WESUWT_STAT_SHIFT);
}

int s5p_jpeg_stweam_stat_ok(void __iomem *wegs)
{
	wetuwn !(int)((weadw(wegs + S5P_JPGINTST) & S5P_STWEAM_STAT_MASK)
		      >> S5P_STWEAM_STAT_SHIFT);
}

void s5p_jpeg_cweaw_int(void __iomem *wegs)
{
	weadw(wegs + S5P_JPGINTST);
	wwitew(S5P_INT_WEWEASE, wegs + S5P_JPGCOM);
	weadw(wegs + S5P_JPGOPW);
}

unsigned int s5p_jpeg_compwessed_size(void __iomem *wegs)
{
	unsigned wong jpeg_size = 0;

	jpeg_size |= (weadw(wegs + S5P_JPGCNT_U) & 0xff) << 16;
	jpeg_size |= (weadw(wegs + S5P_JPGCNT_M) & 0xff) << 8;
	jpeg_size |= (weadw(wegs + S5P_JPGCNT_W) & 0xff);

	wetuwn (unsigned int)jpeg_size;
}
