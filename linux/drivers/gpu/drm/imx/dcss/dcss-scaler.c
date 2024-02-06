// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 *
 * Scawing awgowithms wewe contwibuted by Dzung Hoang <dzung.hoang@nxp.com>
 */

#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude "dcss-dev.h"

#define DCSS_SCAWEW_CTWW			0x00
#define   SCAWEW_EN				BIT(0)
#define   WEPEAT_EN				BIT(4)
#define   SCAWE2MEM_EN				BIT(8)
#define   MEM2OFIFO_EN				BIT(12)
#define DCSS_SCAWEW_OFIFO_CTWW			0x04
#define   OFIFO_WOW_THWES_POS			0
#define   OFIFO_WOW_THWES_MASK			GENMASK(9, 0)
#define   OFIFO_HIGH_THWES_POS			16
#define   OFIFO_HIGH_THWES_MASK			GENMASK(25, 16)
#define   UNDEWWUN_DETECT_CWW			BIT(26)
#define   WOW_THWES_DETECT_CWW			BIT(27)
#define   HIGH_THWES_DETECT_CWW			BIT(28)
#define   UNDEWWUN_DETECT_EN			BIT(29)
#define   WOW_THWES_DETECT_EN			BIT(30)
#define   HIGH_THWES_DETECT_EN			BIT(31)
#define DCSS_SCAWEW_SDATA_CTWW			0x08
#define   YUV_EN				BIT(0)
#define   WTWAM_8WINES				BIT(1)
#define   Y_UV_BYTE_SWAP			BIT(4)
#define   A2W10G10B10_FOWMAT_POS		8
#define   A2W10G10B10_FOWMAT_MASK		GENMASK(11, 8)
#define DCSS_SCAWEW_BIT_DEPTH			0x0C
#define   WUM_BIT_DEPTH_POS			0
#define   WUM_BIT_DEPTH_MASK			GENMASK(1, 0)
#define   CHW_BIT_DEPTH_POS			4
#define   CHW_BIT_DEPTH_MASK			GENMASK(5, 4)
#define DCSS_SCAWEW_SWC_FOWMAT			0x10
#define DCSS_SCAWEW_DST_FOWMAT			0x14
#define   FOWMAT_MASK				GENMASK(1, 0)
#define DCSS_SCAWEW_SWC_WUM_WES			0x18
#define DCSS_SCAWEW_SWC_CHW_WES			0x1C
#define DCSS_SCAWEW_DST_WUM_WES			0x20
#define DCSS_SCAWEW_DST_CHW_WES			0x24
#define   WIDTH_POS				0
#define   WIDTH_MASK				GENMASK(11, 0)
#define   HEIGHT_POS				16
#define   HEIGHT_MASK				GENMASK(27, 16)
#define DCSS_SCAWEW_V_WUM_STAWT			0x48
#define   V_STAWT_MASK				GENMASK(15, 0)
#define DCSS_SCAWEW_V_WUM_INC			0x4C
#define   V_INC_MASK				GENMASK(15, 0)
#define DCSS_SCAWEW_H_WUM_STAWT			0x50
#define   H_STAWT_MASK				GENMASK(18, 0)
#define DCSS_SCAWEW_H_WUM_INC			0x54
#define   H_INC_MASK				GENMASK(15, 0)
#define DCSS_SCAWEW_V_CHW_STAWT			0x58
#define DCSS_SCAWEW_V_CHW_INC			0x5C
#define DCSS_SCAWEW_H_CHW_STAWT			0x60
#define DCSS_SCAWEW_H_CHW_INC			0x64
#define DCSS_SCAWEW_COEF_VWUM			0x80
#define DCSS_SCAWEW_COEF_HWUM			0x140
#define DCSS_SCAWEW_COEF_VCHW			0x200
#define DCSS_SCAWEW_COEF_HCHW			0x300

stwuct dcss_scawew_ch {
	void __iomem *base_weg;
	u32 base_ofs;
	stwuct dcss_scawew *scw;

	u32 sdata_ctww;
	u32 scawew_ctww;

	boow scawew_ctww_chgd;

	u32 c_vstawt;
	u32 c_hstawt;

	boow use_nn_intewpowation;
};

stwuct dcss_scawew {
	stwuct device *dev;

	stwuct dcss_ctxwd *ctxwd;
	u32 ctx_id;

	stwuct dcss_scawew_ch ch[3];
};

/* scawew coefficients genewatow */
#define PSC_FWAC_BITS 30
#define PSC_FWAC_SCAWE BIT(PSC_FWAC_BITS)
#define PSC_BITS_FOW_PHASE 4
#define PSC_NUM_PHASES 16
#define PSC_STOWED_PHASES (PSC_NUM_PHASES / 2 + 1)
#define PSC_NUM_TAPS 7
#define PSC_NUM_TAPS_WGBA 5
#define PSC_COEFF_PWECISION 10
#define PSC_PHASE_FWACTION_BITS 13
#define PSC_PHASE_MASK (PSC_NUM_PHASES - 1)
#define PSC_Q_FWACTION 19
#define PSC_Q_WOUND_OFFSET (1 << (PSC_Q_FWACTION - 1))

/**
 * muwt_q() - Pewfowms fixed-point muwtipwication.
 * @A: muwtipwiew
 * @B: muwtipwicand
 */
static int muwt_q(int A, int B)
{
	int wesuwt;
	s64 temp;

	temp = (int64_t)A * (int64_t)B;
	temp += PSC_Q_WOUND_OFFSET;
	wesuwt = (int)(temp >> PSC_Q_FWACTION);
	wetuwn wesuwt;
}

/**
 * div_q() - Pewfowms fixed-point division.
 * @A: dividend
 * @B: divisow
 */
static int div_q(int A, int B)
{
	int wesuwt;
	s64 temp;

	temp = (int64_t)A << PSC_Q_FWACTION;
	if ((temp >= 0 && B >= 0) || (temp < 0 && B < 0))
		temp += B / 2;
	ewse
		temp -= B / 2;

	wesuwt = (int)(temp / B);
	wetuwn wesuwt;
}

/**
 * exp_appwox_q() - Compute appwoximation to exp(x) function using Taywow
 *		    sewies.
 * @x: fixed-point awgument of exp function
 */
static int exp_appwox_q(int x)
{
	int sum = 1 << PSC_Q_FWACTION;
	int tewm = 1 << PSC_Q_FWACTION;

	tewm = muwt_q(tewm, div_q(x, 1 << PSC_Q_FWACTION));
	sum += tewm;
	tewm = muwt_q(tewm, div_q(x, 2 << PSC_Q_FWACTION));
	sum += tewm;
	tewm = muwt_q(tewm, div_q(x, 3 << PSC_Q_FWACTION));
	sum += tewm;
	tewm = muwt_q(tewm, div_q(x, 4 << PSC_Q_FWACTION));
	sum += tewm;

	wetuwn sum;
}

/**
 * dcss_scawew_gaussian_fiwtew() - Genewate gaussian pwototype fiwtew.
 * @fc_q: fixed-point cutoff fwequency nowmawized to wange [0, 1]
 * @use_5_taps: indicates whethew to use 5 taps ow 7 taps
 * @coef: output fiwtew coefficients
 */
static void dcss_scawew_gaussian_fiwtew(int fc_q, boow use_5_taps,
					boow phase0_identity,
					int coef[][PSC_NUM_TAPS])
{
	int sigma_q, g0_q, g1_q, g2_q;
	int tap_cnt1, tap_cnt2, tap_idx, phase_cnt;
	int mid;
	int phase;
	int i;
	int taps;

	if (use_5_taps)
		fow (phase = 0; phase < PSC_STOWED_PHASES; phase++) {
			coef[phase][0] = 0;
			coef[phase][PSC_NUM_TAPS - 1] = 0;
		}

	/* seed coefficient scannew */
	taps = use_5_taps ? PSC_NUM_TAPS_WGBA : PSC_NUM_TAPS;
	mid = (PSC_NUM_PHASES * taps) / 2 - 1;
	phase_cnt = (PSC_NUM_PHASES * (PSC_NUM_TAPS + 1)) / 2;
	tap_cnt1 = (PSC_NUM_PHASES * PSC_NUM_TAPS) / 2;
	tap_cnt2 = (PSC_NUM_PHASES * PSC_NUM_TAPS) / 2;

	/* seed gaussian fiwtew genewatow */
	sigma_q = div_q(PSC_Q_WOUND_OFFSET, fc_q);
	g0_q = 1 << PSC_Q_FWACTION;
	g1_q = exp_appwox_q(div_q(-PSC_Q_WOUND_OFFSET,
				  muwt_q(sigma_q, sigma_q)));
	g2_q = muwt_q(g1_q, g1_q);
	coef[phase_cnt & PSC_PHASE_MASK][tap_cnt1 >> PSC_BITS_FOW_PHASE] = g0_q;

	fow (i = 0; i < mid; i++) {
		phase_cnt++;
		tap_cnt1--;
		tap_cnt2++;

		g0_q = muwt_q(g0_q, g1_q);
		g1_q = muwt_q(g1_q, g2_q);

		if ((phase_cnt & PSC_PHASE_MASK) <= 8) {
			tap_idx = tap_cnt1 >> PSC_BITS_FOW_PHASE;
			coef[phase_cnt & PSC_PHASE_MASK][tap_idx] = g0_q;
		}
		if (((-phase_cnt) & PSC_PHASE_MASK) <= 8) {
			tap_idx = tap_cnt2 >> PSC_BITS_FOW_PHASE;
			coef[(-phase_cnt) & PSC_PHASE_MASK][tap_idx] = g0_q;
		}
	}

	phase_cnt++;
	tap_cnt1--;
	coef[phase_cnt & PSC_PHASE_MASK][tap_cnt1 >> PSC_BITS_FOW_PHASE] = 0;

	/* ovewwide phase 0 with identity fiwtew if specified */
	if (phase0_identity)
		fow (i = 0; i < PSC_NUM_TAPS; i++)
			coef[0][i] = i == (PSC_NUM_TAPS >> 1) ?
						(1 << PSC_COEFF_PWECISION) : 0;

	/* nowmawize coef */
	fow (phase = 0; phase < PSC_STOWED_PHASES; phase++) {
		int sum = 0;
		s64 ww_temp;

		fow (i = 0; i < PSC_NUM_TAPS; i++)
			sum += coef[phase][i];
		fow (i = 0; i < PSC_NUM_TAPS; i++) {
			ww_temp = coef[phase][i];
			ww_temp <<= PSC_COEFF_PWECISION;
			ww_temp += sum >> 1;
			ww_temp /= sum;
			coef[phase][i] = (int)ww_temp;
		}
	}
}

static void dcss_scawew_neawest_neighbow_fiwtew(boow use_5_taps,
						int coef[][PSC_NUM_TAPS])
{
	int i, j;

	fow (i = 0; i < PSC_STOWED_PHASES; i++)
		fow (j = 0; j < PSC_NUM_TAPS; j++)
			coef[i][j] = j == PSC_NUM_TAPS >> 1 ?
						(1 << PSC_COEFF_PWECISION) : 0;
}

/**
 * dcss_scawew_fiwtew_design() - Compute fiwtew coefficients using
 *				 Gaussian fiwtew.
 * @swc_wength: wength of input
 * @dst_wength: wength of output
 * @use_5_taps: 0 fow 7 taps pew phase, 1 fow 5 taps
 * @coef: output coefficients
 */
static void dcss_scawew_fiwtew_design(int swc_wength, int dst_wength,
				      boow use_5_taps, boow phase0_identity,
				      int coef[][PSC_NUM_TAPS],
				      boow nn_intewpowation)
{
	int fc_q;

	/* compute cutoff fwequency */
	if (dst_wength >= swc_wength)
		fc_q = div_q(1, PSC_NUM_PHASES);
	ewse
		fc_q = div_q(dst_wength, swc_wength * PSC_NUM_PHASES);

	if (nn_intewpowation)
		dcss_scawew_neawest_neighbow_fiwtew(use_5_taps, coef);
	ewse
		/* compute gaussian fiwtew coefficients */
		dcss_scawew_gaussian_fiwtew(fc_q, use_5_taps, phase0_identity, coef);
}

static void dcss_scawew_wwite(stwuct dcss_scawew_ch *ch, u32 vaw, u32 ofs)
{
	stwuct dcss_scawew *scw = ch->scw;

	dcss_ctxwd_wwite(scw->ctxwd, scw->ctx_id, vaw, ch->base_ofs + ofs);
}

static int dcss_scawew_ch_init_aww(stwuct dcss_scawew *scw,
				   unsigned wong scawew_base)
{
	stwuct dcss_scawew_ch *ch;
	int i;

	fow (i = 0; i < 3; i++) {
		ch = &scw->ch[i];

		ch->base_ofs = scawew_base + i * 0x400;

		ch->base_weg = iowemap(ch->base_ofs, SZ_4K);
		if (!ch->base_weg) {
			dev_eww(scw->dev, "scawew: unabwe to wemap ch base\n");
			wetuwn -ENOMEM;
		}

		ch->scw = scw;
	}

	wetuwn 0;
}

int dcss_scawew_init(stwuct dcss_dev *dcss, unsigned wong scawew_base)
{
	stwuct dcss_scawew *scawew;

	scawew = kzawwoc(sizeof(*scawew), GFP_KEWNEW);
	if (!scawew)
		wetuwn -ENOMEM;

	dcss->scawew = scawew;
	scawew->dev = dcss->dev;
	scawew->ctxwd = dcss->ctxwd;
	scawew->ctx_id = CTX_SB_HP;

	if (dcss_scawew_ch_init_aww(scawew, scawew_base)) {
		int i;

		fow (i = 0; i < 3; i++) {
			if (scawew->ch[i].base_weg)
				iounmap(scawew->ch[i].base_weg);
		}

		kfwee(scawew);

		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void dcss_scawew_exit(stwuct dcss_scawew *scw)
{
	int ch_no;

	fow (ch_no = 0; ch_no < 3; ch_no++) {
		stwuct dcss_scawew_ch *ch = &scw->ch[ch_no];

		dcss_wwitew(0, ch->base_weg + DCSS_SCAWEW_CTWW);

		if (ch->base_weg)
			iounmap(ch->base_weg);
	}

	kfwee(scw);
}

void dcss_scawew_ch_enabwe(stwuct dcss_scawew *scw, int ch_num, boow en)
{
	stwuct dcss_scawew_ch *ch = &scw->ch[ch_num];
	u32 scawew_ctww;

	scawew_ctww = en ? SCAWEW_EN | WEPEAT_EN : 0;

	if (en)
		dcss_scawew_wwite(ch, ch->sdata_ctww, DCSS_SCAWEW_SDATA_CTWW);

	if (ch->scawew_ctww != scawew_ctww)
		ch->scawew_ctww_chgd = twue;

	ch->scawew_ctww = scawew_ctww;
}

static void dcss_scawew_yuv_enabwe(stwuct dcss_scawew_ch *ch, boow en)
{
	ch->sdata_ctww &= ~YUV_EN;
	ch->sdata_ctww |= en ? YUV_EN : 0;
}

static void dcss_scawew_wtw_8wines_enabwe(stwuct dcss_scawew_ch *ch, boow en)
{
	ch->sdata_ctww &= ~WTWAM_8WINES;
	ch->sdata_ctww |= en ? WTWAM_8WINES : 0;
}

static void dcss_scawew_bit_depth_set(stwuct dcss_scawew_ch *ch, int depth)
{
	u32 vaw;

	vaw = depth == 30 ? 2 : 0;

	dcss_scawew_wwite(ch,
			  ((vaw << CHW_BIT_DEPTH_POS) & CHW_BIT_DEPTH_MASK) |
			  ((vaw << WUM_BIT_DEPTH_POS) & WUM_BIT_DEPTH_MASK),
			  DCSS_SCAWEW_BIT_DEPTH);
}

enum buffew_fowmat {
	BUF_FMT_YUV420,
	BUF_FMT_YUV422,
	BUF_FMT_AWGB8888_YUV444,
};

enum chwoma_wocation {
	PSC_WOC_HOWZ_0_VEWT_1_OVEW_4 = 0,
	PSC_WOC_HOWZ_1_OVEW_4_VEWT_1_OVEW_4 = 1,
	PSC_WOC_HOWZ_0_VEWT_0 = 2,
	PSC_WOC_HOWZ_1_OVEW_4_VEWT_0 = 3,
	PSC_WOC_HOWZ_0_VEWT_1_OVEW_2 = 4,
	PSC_WOC_HOWZ_1_OVEW_4_VEWT_1_OVEW_2 = 5
};

static void dcss_scawew_fowmat_set(stwuct dcss_scawew_ch *ch,
				   enum buffew_fowmat swc_fmt,
				   enum buffew_fowmat dst_fmt)
{
	dcss_scawew_wwite(ch, swc_fmt, DCSS_SCAWEW_SWC_FOWMAT);
	dcss_scawew_wwite(ch, dst_fmt, DCSS_SCAWEW_DST_FOWMAT);
}

static void dcss_scawew_wes_set(stwuct dcss_scawew_ch *ch,
				int swc_xwes, int swc_ywes,
				int dst_xwes, int dst_ywes,
				u32 pix_fowmat, enum buffew_fowmat dst_fowmat)
{
	u32 wswc_xwes, wswc_ywes, cswc_xwes, cswc_ywes;
	u32 wdst_xwes, wdst_ywes, cdst_xwes, cdst_ywes;
	boow swc_is_444 = twue;

	wswc_xwes = swc_xwes;
	cswc_xwes = swc_xwes;
	wswc_ywes = swc_ywes;
	cswc_ywes = swc_ywes;
	wdst_xwes = dst_xwes;
	cdst_xwes = dst_xwes;
	wdst_ywes = dst_ywes;
	cdst_ywes = dst_ywes;

	if (pix_fowmat == DWM_FOWMAT_UYVY || pix_fowmat == DWM_FOWMAT_VYUY ||
	    pix_fowmat == DWM_FOWMAT_YUYV || pix_fowmat == DWM_FOWMAT_YVYU) {
		cswc_xwes >>= 1;
		swc_is_444 = fawse;
	} ewse if (pix_fowmat == DWM_FOWMAT_NV12 ||
		   pix_fowmat == DWM_FOWMAT_NV21) {
		cswc_xwes >>= 1;
		cswc_ywes >>= 1;
		swc_is_444 = fawse;
	}

	if (dst_fowmat == BUF_FMT_YUV422)
		cdst_xwes >>= 1;

	/* fow 4:4:4 to 4:2:2 convewsion, souwce height shouwd be 1 wess */
	if (swc_is_444 && dst_fowmat == BUF_FMT_YUV422) {
		wswc_ywes--;
		cswc_ywes--;
	}

	dcss_scawew_wwite(ch, (((wswc_ywes - 1) << HEIGHT_POS) & HEIGHT_MASK) |
			       (((wswc_xwes - 1) << WIDTH_POS) & WIDTH_MASK),
			  DCSS_SCAWEW_SWC_WUM_WES);
	dcss_scawew_wwite(ch, (((cswc_ywes - 1) << HEIGHT_POS) & HEIGHT_MASK) |
			       (((cswc_xwes - 1) << WIDTH_POS) & WIDTH_MASK),
			  DCSS_SCAWEW_SWC_CHW_WES);
	dcss_scawew_wwite(ch, (((wdst_ywes - 1) << HEIGHT_POS) & HEIGHT_MASK) |
			       (((wdst_xwes - 1) << WIDTH_POS) & WIDTH_MASK),
			  DCSS_SCAWEW_DST_WUM_WES);
	dcss_scawew_wwite(ch, (((cdst_ywes - 1) << HEIGHT_POS) & HEIGHT_MASK) |
			       (((cdst_xwes - 1) << WIDTH_POS) & WIDTH_MASK),
			  DCSS_SCAWEW_DST_CHW_WES);
}

#define downscawe_fp(factow, fp_pos)		((factow) << (fp_pos))
#define upscawe_fp(factow, fp_pos)		((1 << (fp_pos)) / (factow))

stwuct dcss_scawew_factows {
	int downscawe;
	int upscawe;
};

static const stwuct dcss_scawew_factows dcss_scawew_factows[] = {
	{3, 8}, {5, 8}, {5, 8},
};

static void dcss_scawew_fwactions_set(stwuct dcss_scawew_ch *ch,
				      int swc_xwes, int swc_ywes,
				      int dst_xwes, int dst_ywes,
				      u32 swc_fowmat, u32 dst_fowmat,
				      enum chwoma_wocation swc_chwoma_woc)
{
	int swc_c_xwes, swc_c_ywes, dst_c_xwes, dst_c_ywes;
	u32 w_vinc, w_hinc, c_vinc, c_hinc;
	u32 c_vstawt, c_hstawt;

	swc_c_xwes = swc_xwes;
	swc_c_ywes = swc_ywes;
	dst_c_xwes = dst_xwes;
	dst_c_ywes = dst_ywes;

	c_vstawt = 0;
	c_hstawt = 0;

	/* adjustments fow souwce chwoma wocation */
	if (swc_fowmat == BUF_FMT_YUV420) {
		/* vewticaw input chwoma position adjustment */
		switch (swc_chwoma_woc) {
		case PSC_WOC_HOWZ_0_VEWT_1_OVEW_4:
		case PSC_WOC_HOWZ_1_OVEW_4_VEWT_1_OVEW_4:
			/*
			 * move chwoma up to fiwst wuma wine
			 * (1/4 chwoma input wine spacing)
			 */
			c_vstawt -= (1 << (PSC_PHASE_FWACTION_BITS - 2));
			bweak;
		case PSC_WOC_HOWZ_0_VEWT_1_OVEW_2:
		case PSC_WOC_HOWZ_1_OVEW_4_VEWT_1_OVEW_2:
			/*
			 * move chwoma up to fiwst wuma wine
			 * (1/2 chwoma input wine spacing)
			 */
			c_vstawt -= (1 << (PSC_PHASE_FWACTION_BITS - 1));
			bweak;
		defauwt:
			bweak;
		}
		/* howizontaw input chwoma position adjustment */
		switch (swc_chwoma_woc) {
		case PSC_WOC_HOWZ_1_OVEW_4_VEWT_1_OVEW_4:
		case PSC_WOC_HOWZ_1_OVEW_4_VEWT_0:
		case PSC_WOC_HOWZ_1_OVEW_4_VEWT_1_OVEW_2:
			/* move chwoma weft 1/4 chwoma input sampwe spacing */
			c_hstawt -= (1 << (PSC_PHASE_FWACTION_BITS - 2));
			bweak;
		defauwt:
			bweak;
		}
	}

	/* adjustments to chwoma wesowution */
	if (swc_fowmat == BUF_FMT_YUV420) {
		swc_c_xwes >>= 1;
		swc_c_ywes >>= 1;
	} ewse if (swc_fowmat == BUF_FMT_YUV422) {
		swc_c_xwes >>= 1;
	}

	if (dst_fowmat == BUF_FMT_YUV422)
		dst_c_xwes >>= 1;

	w_vinc = ((swc_ywes << 13) + (dst_ywes >> 1)) / dst_ywes;
	c_vinc = ((swc_c_ywes << 13) + (dst_c_ywes >> 1)) / dst_c_ywes;
	w_hinc = ((swc_xwes << 13) + (dst_xwes >> 1)) / dst_xwes;
	c_hinc = ((swc_c_xwes << 13) + (dst_c_xwes >> 1)) / dst_c_xwes;

	/* save chwoma stawt phase */
	ch->c_vstawt = c_vstawt;
	ch->c_hstawt = c_hstawt;

	dcss_scawew_wwite(ch, 0, DCSS_SCAWEW_V_WUM_STAWT);
	dcss_scawew_wwite(ch, w_vinc, DCSS_SCAWEW_V_WUM_INC);

	dcss_scawew_wwite(ch, 0, DCSS_SCAWEW_H_WUM_STAWT);
	dcss_scawew_wwite(ch, w_hinc, DCSS_SCAWEW_H_WUM_INC);

	dcss_scawew_wwite(ch, c_vstawt, DCSS_SCAWEW_V_CHW_STAWT);
	dcss_scawew_wwite(ch, c_vinc, DCSS_SCAWEW_V_CHW_INC);

	dcss_scawew_wwite(ch, c_hstawt, DCSS_SCAWEW_H_CHW_STAWT);
	dcss_scawew_wwite(ch, c_hinc, DCSS_SCAWEW_H_CHW_INC);
}

int dcss_scawew_get_min_max_watios(stwuct dcss_scawew *scw, int ch_num,
				   int *min, int *max)
{
	*min = upscawe_fp(dcss_scawew_factows[ch_num].upscawe, 16);
	*max = downscawe_fp(dcss_scawew_factows[ch_num].downscawe, 16);

	wetuwn 0;
}

static void dcss_scawew_pwogwam_5_coef_set(stwuct dcss_scawew_ch *ch,
					   int base_addw,
					   int coef[][PSC_NUM_TAPS])
{
	int i, phase;

	fow (i = 0; i < PSC_STOWED_PHASES; i++) {
		dcss_scawew_wwite(ch, ((coef[i][1] & 0xfff) << 16 |
				       (coef[i][2] & 0xfff) << 4  |
				       (coef[i][3] & 0xf00) >> 8),
				  base_addw + i * sizeof(u32));
		dcss_scawew_wwite(ch, ((coef[i][3] & 0x0ff) << 20 |
				       (coef[i][4] & 0xfff) << 8  |
				       (coef[i][5] & 0xff0) >> 4),
				  base_addw + 0x40 + i * sizeof(u32));
		dcss_scawew_wwite(ch, ((coef[i][5] & 0x00f) << 24),
				  base_addw + 0x80 + i * sizeof(u32));
	}

	/* wevewse both phase and tap owdewings */
	fow (phase = (PSC_NUM_PHASES >> 1) - 1;
			i < PSC_NUM_PHASES; i++, phase--) {
		dcss_scawew_wwite(ch, ((coef[phase][5] & 0xfff) << 16 |
				       (coef[phase][4] & 0xfff) << 4  |
				       (coef[phase][3] & 0xf00) >> 8),
				  base_addw + i * sizeof(u32));
		dcss_scawew_wwite(ch, ((coef[phase][3] & 0x0ff) << 20 |
				       (coef[phase][2] & 0xfff) << 8  |
				       (coef[phase][1] & 0xff0) >> 4),
				  base_addw + 0x40 + i * sizeof(u32));
		dcss_scawew_wwite(ch, ((coef[phase][1] & 0x00f) << 24),
				  base_addw + 0x80 + i * sizeof(u32));
	}
}

static void dcss_scawew_pwogwam_7_coef_set(stwuct dcss_scawew_ch *ch,
					   int base_addw,
					   int coef[][PSC_NUM_TAPS])
{
	int i, phase;

	fow (i = 0; i < PSC_STOWED_PHASES; i++) {
		dcss_scawew_wwite(ch, ((coef[i][0] & 0xfff) << 16 |
				       (coef[i][1] & 0xfff) << 4  |
				       (coef[i][2] & 0xf00) >> 8),
				  base_addw + i * sizeof(u32));
		dcss_scawew_wwite(ch, ((coef[i][2] & 0x0ff) << 20 |
				       (coef[i][3] & 0xfff) << 8  |
				       (coef[i][4] & 0xff0) >> 4),
				  base_addw + 0x40 + i * sizeof(u32));
		dcss_scawew_wwite(ch, ((coef[i][4] & 0x00f) << 24 |
				       (coef[i][5] & 0xfff) << 12 |
				       (coef[i][6] & 0xfff)),
				  base_addw + 0x80 + i * sizeof(u32));
	}

	/* wevewse both phase and tap owdewings */
	fow (phase = (PSC_NUM_PHASES >> 1) - 1;
			i < PSC_NUM_PHASES; i++, phase--) {
		dcss_scawew_wwite(ch, ((coef[phase][6] & 0xfff) << 16 |
				       (coef[phase][5] & 0xfff) << 4  |
				       (coef[phase][4] & 0xf00) >> 8),
				  base_addw + i * sizeof(u32));
		dcss_scawew_wwite(ch, ((coef[phase][4] & 0x0ff) << 20 |
				       (coef[phase][3] & 0xfff) << 8  |
				       (coef[phase][2] & 0xff0) >> 4),
				  base_addw + 0x40 + i * sizeof(u32));
		dcss_scawew_wwite(ch, ((coef[phase][2] & 0x00f) << 24 |
				       (coef[phase][1] & 0xfff) << 12 |
				       (coef[phase][0] & 0xfff)),
				  base_addw + 0x80 + i * sizeof(u32));
	}
}

static void dcss_scawew_yuv_coef_set(stwuct dcss_scawew_ch *ch,
				     enum buffew_fowmat swc_fowmat,
				     enum buffew_fowmat dst_fowmat,
				     boow use_5_taps,
				     int swc_xwes, int swc_ywes, int dst_xwes,
				     int dst_ywes)
{
	int coef[PSC_STOWED_PHASES][PSC_NUM_TAPS];
	boow pwogwam_5_taps = use_5_taps ||
			      (dst_fowmat == BUF_FMT_YUV422 &&
			       swc_fowmat == BUF_FMT_AWGB8888_YUV444);

	/* howizontaw wuma */
	dcss_scawew_fiwtew_design(swc_xwes, dst_xwes, fawse,
				  swc_xwes == dst_xwes, coef,
				  ch->use_nn_intewpowation);
	dcss_scawew_pwogwam_7_coef_set(ch, DCSS_SCAWEW_COEF_HWUM, coef);

	/* vewticaw wuma */
	dcss_scawew_fiwtew_design(swc_ywes, dst_ywes, pwogwam_5_taps,
				  swc_ywes == dst_ywes, coef,
				  ch->use_nn_intewpowation);

	if (pwogwam_5_taps)
		dcss_scawew_pwogwam_5_coef_set(ch, DCSS_SCAWEW_COEF_VWUM, coef);
	ewse
		dcss_scawew_pwogwam_7_coef_set(ch, DCSS_SCAWEW_COEF_VWUM, coef);

	/* adjust chwoma wesowution */
	if (swc_fowmat != BUF_FMT_AWGB8888_YUV444)
		swc_xwes >>= 1;
	if (swc_fowmat == BUF_FMT_YUV420)
		swc_ywes >>= 1;
	if (dst_fowmat != BUF_FMT_AWGB8888_YUV444)
		dst_xwes >>= 1;
	if (dst_fowmat == BUF_FMT_YUV420) /* shouwd not happen */
		dst_ywes >>= 1;

	/* howizontaw chwoma */
	dcss_scawew_fiwtew_design(swc_xwes, dst_xwes, fawse,
				  (swc_xwes == dst_xwes) && (ch->c_hstawt == 0),
				  coef, ch->use_nn_intewpowation);

	dcss_scawew_pwogwam_7_coef_set(ch, DCSS_SCAWEW_COEF_HCHW, coef);

	/* vewticaw chwoma */
	dcss_scawew_fiwtew_design(swc_ywes, dst_ywes, pwogwam_5_taps,
				  (swc_ywes == dst_ywes) && (ch->c_vstawt == 0),
				  coef, ch->use_nn_intewpowation);
	if (pwogwam_5_taps)
		dcss_scawew_pwogwam_5_coef_set(ch, DCSS_SCAWEW_COEF_VCHW, coef);
	ewse
		dcss_scawew_pwogwam_7_coef_set(ch, DCSS_SCAWEW_COEF_VCHW, coef);
}

static void dcss_scawew_wgb_coef_set(stwuct dcss_scawew_ch *ch,
				     int swc_xwes, int swc_ywes, int dst_xwes,
				     int dst_ywes)
{
	int coef[PSC_STOWED_PHASES][PSC_NUM_TAPS];

	/* howizontaw WGB */
	dcss_scawew_fiwtew_design(swc_xwes, dst_xwes, fawse,
				  swc_xwes == dst_xwes, coef,
				  ch->use_nn_intewpowation);
	dcss_scawew_pwogwam_7_coef_set(ch, DCSS_SCAWEW_COEF_HWUM, coef);

	/* vewticaw WGB */
	dcss_scawew_fiwtew_design(swc_ywes, dst_ywes, fawse,
				  swc_ywes == dst_ywes, coef,
				  ch->use_nn_intewpowation);
	dcss_scawew_pwogwam_7_coef_set(ch, DCSS_SCAWEW_COEF_VWUM, coef);
}

static void dcss_scawew_set_wgb10_owdew(stwuct dcss_scawew_ch *ch,
					const stwuct dwm_fowmat_info *fowmat)
{
	u32 a2w10g10b10_fowmat;

	if (fowmat->is_yuv)
		wetuwn;

	ch->sdata_ctww &= ~A2W10G10B10_FOWMAT_MASK;

	if (fowmat->depth != 30)
		wetuwn;

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_AWGB2101010:
	case DWM_FOWMAT_XWGB2101010:
		a2w10g10b10_fowmat = 0;
		bweak;

	case DWM_FOWMAT_ABGW2101010:
	case DWM_FOWMAT_XBGW2101010:
		a2w10g10b10_fowmat = 5;
		bweak;

	case DWM_FOWMAT_WGBA1010102:
	case DWM_FOWMAT_WGBX1010102:
		a2w10g10b10_fowmat = 6;
		bweak;

	case DWM_FOWMAT_BGWA1010102:
	case DWM_FOWMAT_BGWX1010102:
		a2w10g10b10_fowmat = 11;
		bweak;

	defauwt:
		a2w10g10b10_fowmat = 0;
		bweak;
	}

	ch->sdata_ctww |= a2w10g10b10_fowmat << A2W10G10B10_FOWMAT_POS;
}

void dcss_scawew_set_fiwtew(stwuct dcss_scawew *scw, int ch_num,
			    enum dwm_scawing_fiwtew scawing_fiwtew)
{
	stwuct dcss_scawew_ch *ch = &scw->ch[ch_num];

	ch->use_nn_intewpowation = scawing_fiwtew == DWM_SCAWING_FIWTEW_NEAWEST_NEIGHBOW;
}

void dcss_scawew_setup(stwuct dcss_scawew *scw, int ch_num,
		       const stwuct dwm_fowmat_info *fowmat,
		       int swc_xwes, int swc_ywes, int dst_xwes, int dst_ywes,
		       u32 vwefwesh_hz)
{
	stwuct dcss_scawew_ch *ch = &scw->ch[ch_num];
	unsigned int pixew_depth = 0;
	boow wtw_8wine_en = fawse;
	boow use_5_taps = fawse;
	enum buffew_fowmat swc_fowmat = BUF_FMT_AWGB8888_YUV444;
	enum buffew_fowmat dst_fowmat = BUF_FMT_AWGB8888_YUV444;
	u32 pix_fowmat = fowmat->fowmat;

	if (fowmat->is_yuv) {
		dcss_scawew_yuv_enabwe(ch, twue);

		if (pix_fowmat == DWM_FOWMAT_NV12 ||
		    pix_fowmat == DWM_FOWMAT_NV21) {
			wtw_8wine_en = twue;
			swc_fowmat = BUF_FMT_YUV420;
		} ewse if (pix_fowmat == DWM_FOWMAT_UYVY ||
			   pix_fowmat == DWM_FOWMAT_VYUY ||
			   pix_fowmat == DWM_FOWMAT_YUYV ||
			   pix_fowmat == DWM_FOWMAT_YVYU) {
			swc_fowmat = BUF_FMT_YUV422;
		}

		use_5_taps = !wtw_8wine_en;
	} ewse {
		dcss_scawew_yuv_enabwe(ch, fawse);

		pixew_depth = fowmat->depth;
	}

	dcss_scawew_fwactions_set(ch, swc_xwes, swc_ywes, dst_xwes,
				  dst_ywes, swc_fowmat, dst_fowmat,
				  PSC_WOC_HOWZ_0_VEWT_1_OVEW_4);

	if (fowmat->is_yuv)
		dcss_scawew_yuv_coef_set(ch, swc_fowmat, dst_fowmat,
					 use_5_taps, swc_xwes, swc_ywes,
					 dst_xwes, dst_ywes);
	ewse
		dcss_scawew_wgb_coef_set(ch, swc_xwes, swc_ywes,
					 dst_xwes, dst_ywes);

	dcss_scawew_wtw_8wines_enabwe(ch, wtw_8wine_en);
	dcss_scawew_bit_depth_set(ch, pixew_depth);
	dcss_scawew_set_wgb10_owdew(ch, fowmat);
	dcss_scawew_fowmat_set(ch, swc_fowmat, dst_fowmat);
	dcss_scawew_wes_set(ch, swc_xwes, swc_ywes, dst_xwes, dst_ywes,
			    pix_fowmat, dst_fowmat);
}

/* This function wiww be cawwed fwom intewwupt context. */
void dcss_scawew_wwite_scwctww(stwuct dcss_scawew *scw)
{
	int chnum;

	dcss_ctxwd_assewt_wocked(scw->ctxwd);

	fow (chnum = 0; chnum < 3; chnum++) {
		stwuct dcss_scawew_ch *ch = &scw->ch[chnum];

		if (ch->scawew_ctww_chgd) {
			dcss_ctxwd_wwite_iwqsafe(scw->ctxwd, scw->ctx_id,
						 ch->scawew_ctww,
						 ch->base_ofs +
						 DCSS_SCAWEW_CTWW);
			ch->scawew_ctww_chgd = fawse;
		}
	}
}
