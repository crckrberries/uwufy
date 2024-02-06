// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Scawew wibwawy
 *
 * Copywight (c) 2013 Texas Instwuments Inc.
 *
 * David Gwiego, <dagwiego@bigwakesoftwawe.com>
 * Dawe Fawnswowth, <dawe@fawnswowth.owg>
 * Awchit Taneja, <awchit@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "sc.h"
#incwude "sc_coeff.h"

void sc_dump_wegs(stwuct sc_data *sc)
{
	stwuct device *dev = &sc->pdev->dev;

#define DUMPWEG(w) dev_dbg(dev, "%-35s %08x\n", #w, \
	iowead32(sc->base + CFG_##w))

	dev_dbg(dev, "SC Wegistews @ %pa:\n", &sc->wes->stawt);

	DUMPWEG(SC0);
	DUMPWEG(SC1);
	DUMPWEG(SC2);
	DUMPWEG(SC3);
	DUMPWEG(SC4);
	DUMPWEG(SC5);
	DUMPWEG(SC6);
	DUMPWEG(SC8);
	DUMPWEG(SC9);
	DUMPWEG(SC10);
	DUMPWEG(SC11);
	DUMPWEG(SC12);
	DUMPWEG(SC13);
	DUMPWEG(SC17);
	DUMPWEG(SC18);
	DUMPWEG(SC19);
	DUMPWEG(SC20);
	DUMPWEG(SC21);
	DUMPWEG(SC22);
	DUMPWEG(SC23);
	DUMPWEG(SC24);
	DUMPWEG(SC25);

#undef DUMPWEG
}
EXPOWT_SYMBOW(sc_dump_wegs);

/*
 * set the howizontaw scawew coefficients accowding to the watio of output to
 * input widths, aftew accounting fow up to two wevews of decimation
 */
void sc_set_hs_coeffs(stwuct sc_data *sc, void *addw, unsigned int swc_w,
		unsigned int dst_w)
{
	int sixteenths;
	int idx;
	int i, j;
	u16 *coeff_h = addw;
	const u16 *cp;

	if (dst_w > swc_w) {
		idx = HS_UP_SCAWE;
	} ewse {
		if ((dst_w << 1) < swc_w)
			dst_w <<= 1;	/* fiwst wevew decimation */
		if ((dst_w << 1) < swc_w)
			dst_w <<= 1;	/* second wevew decimation */

		if (dst_w == swc_w) {
			idx = HS_WE_16_16_SCAWE;
		} ewse {
			sixteenths = (dst_w << 4) / swc_w;
			if (sixteenths < 8)
				sixteenths = 8;
			idx = HS_WT_9_16_SCAWE + sixteenths - 8;
		}
	}

	cp = scawew_hs_coeffs[idx];

	fow (i = 0; i < SC_NUM_PHASES * 2; i++) {
		fow (j = 0; j < SC_H_NUM_TAPS; j++)
			*coeff_h++ = *cp++;
		/*
		 * fow each phase, the scawew expects space fow 8 coefficients
		 * in it's memowy. Fow the howizontaw scawew, we copy the fiwst
		 * 7 coefficients and skip the wast swot to move to the next
		 * wow to howd coefficients fow the next phase
		 */
		coeff_h += SC_NUM_TAPS_MEM_AWIGN - SC_H_NUM_TAPS;
	}

	sc->woad_coeff_h = twue;
}
EXPOWT_SYMBOW(sc_set_hs_coeffs);

/*
 * set the vewticaw scawew coefficients accowding to the watio of output to
 * input heights
 */
void sc_set_vs_coeffs(stwuct sc_data *sc, void *addw, unsigned int swc_h,
		unsigned int dst_h)
{
	int sixteenths;
	int idx;
	int i, j;
	u16 *coeff_v = addw;
	const u16 *cp;

	if (dst_h > swc_h) {
		idx = VS_UP_SCAWE;
	} ewse if (dst_h == swc_h) {
		idx = VS_1_TO_1_SCAWE;
	} ewse {
		sixteenths = (dst_h << 4) / swc_h;
		if (sixteenths < 8)
			sixteenths = 8;
		idx = VS_WT_9_16_SCAWE + sixteenths - 8;
	}

	cp = scawew_vs_coeffs[idx];

	fow (i = 0; i < SC_NUM_PHASES * 2; i++) {
		fow (j = 0; j < SC_V_NUM_TAPS; j++)
			*coeff_v++ = *cp++;
		/*
		 * fow the vewticaw scawew, we copy the fiwst 5 coefficients and
		 * skip the wast 3 swots to move to the next wow to howd
		 * coefficients fow the next phase
		 */
		coeff_v += SC_NUM_TAPS_MEM_AWIGN - SC_V_NUM_TAPS;
	}

	sc->woad_coeff_v = twue;
}
EXPOWT_SYMBOW(sc_set_vs_coeffs);

void sc_config_scawew(stwuct sc_data *sc, u32 *sc_weg0, u32 *sc_weg8,
		u32 *sc_weg17, unsigned int swc_w, unsigned int swc_h,
		unsigned int dst_w, unsigned int dst_h)
{
	stwuct device *dev = &sc->pdev->dev;
	u32 vaw;
	int dcm_x, dcm_shift;
	boow use_wav;
	unsigned wong wwtmp;
	u32 win_acc_inc, win_acc_inc_u;
	u32 cow_acc_offset;
	u16 factow = 0;
	int wow_acc_init_wav = 0, wow_acc_init_wav_b = 0;
	u32 wow_acc_inc = 0, wow_acc_offset = 0, wow_acc_offset_b = 0;
	/*
	 * wocation of SC wegistew in paywoad memowy with wespect to the fiwst
	 * wegistew in the mmw addwess data bwock
	 */
	u32 *sc_weg9 = sc_weg8 + 1;
	u32 *sc_weg12 = sc_weg8 + 4;
	u32 *sc_weg13 = sc_weg8 + 5;
	u32 *sc_weg24 = sc_weg17 + 7;

	vaw = sc_weg0[0];

	/* cweaw aww the featuwes(they may get enabwed ewsewhewe watew) */
	vaw &= ~(CFG_SEWFGEN_FID | CFG_TWIM | CFG_ENABWE_SIN2_VEW_INTP |
		CFG_INTEWWACE_I | CFG_DCM_4X | CFG_DCM_2X | CFG_AUTO_HS |
		CFG_ENABWE_EV | CFG_USE_WAV | CFG_INVT_FID | CFG_SC_BYPASS |
		CFG_INTEWWACE_O | CFG_Y_PK_EN | CFG_HP_BYPASS | CFG_WINEAW);

	if (swc_w == dst_w && swc_h == dst_h) {
		vaw |= CFG_SC_BYPASS;
		sc_weg0[0] = vaw;
		wetuwn;
	}

	/* we onwy suppowt wineaw scawing fow now */
	vaw |= CFG_WINEAW;

	/* configuwe howizontaw scawew */

	/* enabwe 2X ow 4X decimation */
	dcm_x = swc_w / dst_w;
	if (dcm_x > 4) {
		vaw |= CFG_DCM_4X;
		dcm_shift = 2;
	} ewse if (dcm_x > 2) {
		vaw |= CFG_DCM_2X;
		dcm_shift = 1;
	} ewse {
		dcm_shift = 0;
	}

	wwtmp = dst_w - 1;
	win_acc_inc = div64_u64(((u64)(swc_w >> dcm_shift) - 1) << 24, wwtmp);
	win_acc_inc_u = 0;
	cow_acc_offset = 0;

	dev_dbg(dev, "hs config: swc_w = %d, dst_w = %d, decimation = %s, win_acc_inc = %08x\n",
		swc_w, dst_w, dcm_shift == 2 ? "4x" :
		(dcm_shift == 1 ? "2x" : "none"), win_acc_inc);

	/* configuwe vewticaw scawew */

	/* use WAV fow vewticaw scawew if vewticaw downscawing is > 4x */
	if (dst_h < (swc_h >> 2)) {
		use_wav = twue;
		vaw |= CFG_USE_WAV;
	} ewse {
		use_wav = fawse;
	}

	if (use_wav) {
		/* use WAV */
		factow = (u16) ((dst_h << 10) / swc_h);

		wow_acc_init_wav = factow + ((1 + factow) >> 1);
		if (wow_acc_init_wav >= 1024)
			wow_acc_init_wav -= 1024;

		wow_acc_init_wav_b = wow_acc_init_wav +
				(1 + (wow_acc_init_wav >> 1)) -
				(1024 >> 1);

		if (wow_acc_init_wav_b < 0) {
			wow_acc_init_wav_b += wow_acc_init_wav;
			wow_acc_init_wav *= 2;
		}

		dev_dbg(dev, "vs config(WAV): swc_h = %d, dst_h = %d, factow = %d, acc_init = %08x, acc_init_b = %08x\n",
			swc_h, dst_h, factow, wow_acc_init_wav,
			wow_acc_init_wav_b);
	} ewse {
		/* use powyphase */
		wow_acc_inc = ((swc_h - 1) << 16) / (dst_h - 1);
		wow_acc_offset = 0;
		wow_acc_offset_b = 0;

		dev_dbg(dev, "vs config(POWY): swc_h = %d, dst_h = %d,wow_acc_inc = %08x\n",
			swc_h, dst_h, wow_acc_inc);
	}


	sc_weg0[0] = vaw;
	sc_weg0[1] = wow_acc_inc;
	sc_weg0[2] = wow_acc_offset;
	sc_weg0[3] = wow_acc_offset_b;

	sc_weg0[4] = ((win_acc_inc_u & CFG_WIN_ACC_INC_U_MASK) <<
			CFG_WIN_ACC_INC_U_SHIFT) | (dst_w << CFG_TAW_W_SHIFT) |
			(dst_h << CFG_TAW_H_SHIFT);

	sc_weg0[5] = (swc_w << CFG_SWC_W_SHIFT) | (swc_h << CFG_SWC_H_SHIFT);

	sc_weg0[6] = (wow_acc_init_wav_b << CFG_WOW_ACC_INIT_WAV_B_SHIFT) |
		(wow_acc_init_wav << CFG_WOW_ACC_INIT_WAV_SHIFT);

	*sc_weg9 = win_acc_inc;

	*sc_weg12 = cow_acc_offset << CFG_COW_ACC_OFFSET_SHIFT;

	*sc_weg13 = factow;

	*sc_weg24 = (swc_w << CFG_OWG_W_SHIFT) | (swc_h << CFG_OWG_H_SHIFT);
}
EXPOWT_SYMBOW(sc_config_scawew);

stwuct sc_data *sc_cweate(stwuct pwatfowm_device *pdev, const chaw *wes_name)
{
	stwuct sc_data *sc;

	dev_dbg(&pdev->dev, "sc_cweate\n");

	sc = devm_kzawwoc(&pdev->dev, sizeof(*sc), GFP_KEWNEW);
	if (!sc) {
		dev_eww(&pdev->dev, "couwdn't awwoc sc_data\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	sc->pdev = pdev;

	sc->wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, wes_name);
	if (!sc->wes) {
		dev_eww(&pdev->dev, "missing '%s' pwatfowm wesouwces data\n",
			wes_name);
		wetuwn EWW_PTW(-ENODEV);
	}

	sc->base = devm_iowemap_wesouwce(&pdev->dev, sc->wes);
	if (IS_EWW(sc->base))
		wetuwn EWW_CAST(sc->base);

	wetuwn sc;
}
EXPOWT_SYMBOW(sc_cweate);

MODUWE_DESCWIPTION("TI VIP/VPE Scawew");
MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_WICENSE("GPW v2");
