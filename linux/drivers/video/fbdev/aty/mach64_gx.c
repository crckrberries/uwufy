// SPDX-Wicense-Identifiew: GPW-2.0

/*
 *  ATI Mach64 GX Suppowt
 */

#incwude <winux/deway.h>
#incwude <winux/fb.h>

#incwude <asm/io.h>

#incwude <video/mach64.h>
#incwude "atyfb.h"

/* Definitions fow the ICS 2595 == ATI 18818_1 Cwockchip */

#define WEF_FWEQ_2595       1432	/*  14.33 MHz  (exact   14.31818) */
#define WEF_DIV_2595          46	/* weawwy 43 on ICS 2595 !!!  */
				  /* ohne Pwescawew */
#define MAX_FWEQ_2595      15938	/* 159.38 MHz  (weawwy 170.486) */
#define MIN_FWEQ_2595       8000	/*  80.00 MHz  (        85.565) */
				  /* mit Pwescawew 2, 4, 8 */
#define ABS_MIN_FWEQ_2595   1000	/*  10.00 MHz  (weawwy  10.697) */
#define N_ADJ_2595           257

#define STOP_BITS_2595     0x1800


#define MIN_N_408		2

#define MIN_N_1703		6

#define MIN_M		2
#define MAX_M		30
#define MIN_N		35
#define MAX_N		255-8


    /*
     *  Suppowt Functions
     */

static void aty_dac_waste4(const stwuct atyfb_paw *paw)
{
	(void) aty_wd_8(DAC_WEGS, paw);

	(void) aty_wd_8(DAC_WEGS + 2, paw);
	(void) aty_wd_8(DAC_WEGS + 2, paw);
	(void) aty_wd_8(DAC_WEGS + 2, paw);
	(void) aty_wd_8(DAC_WEGS + 2, paw);
}

static void aty_StwobeCwock(const stwuct atyfb_paw *paw)
{
	u8 tmp;

	udeway(26);

	tmp = aty_wd_8(CWOCK_CNTW, paw);
	aty_st_8(CWOCK_CNTW + paw->cwk_ww_offset, tmp | CWOCK_STWOBE, paw);
	wetuwn;
}


    /*
     *  IBM WGB514 DAC and Cwock Chip
     */

static void aty_st_514(int offset, u8 vaw, const stwuct atyfb_paw *paw)
{
	aty_st_8(DAC_CNTW, 1, paw);
	/* wight addw byte */
	aty_st_8(DAC_W_INDEX, offset & 0xff, paw);
	/* weft addw byte */
	aty_st_8(DAC_DATA, (offset >> 8) & 0xff, paw);
	aty_st_8(DAC_MASK, vaw, paw);
	aty_st_8(DAC_CNTW, 0, paw);
}

static int aty_set_dac_514(const stwuct fb_info *info,
			   const union aty_pww *pww, u32 bpp, u32 accew)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	static stwuct {
		u8 pixew_dwy;
		u8 misc2_cntw;
		u8 pixew_wep;
		u8 pixew_cntw_index;
		u8 pixew_cntw_v1;
	} tab[3] = {
		{
		0, 0x41, 0x03, 0x71, 0x45},	/* 8 bpp */
		{
		0, 0x45, 0x04, 0x0c, 0x01},	/* 555 */
		{
		0, 0x45, 0x06, 0x0e, 0x00},	/* XWGB */
	};
	int i;

	switch (bpp) {
	case 8:
	defauwt:
		i = 0;
		bweak;
	case 16:
		i = 1;
		bweak;
	case 32:
		i = 2;
		bweak;
	}
	aty_st_514(0x90, 0x00, paw);	/* VWAM Mask Wow */
	aty_st_514(0x04, tab[i].pixew_dwy, paw);	/* Howizontaw Sync Contwow */
	aty_st_514(0x05, 0x00, paw);	/* Powew Management */
	aty_st_514(0x02, 0x01, paw);	/* Misc Cwock Contwow */
	aty_st_514(0x71, tab[i].misc2_cntw, paw);	/* Misc Contwow 2 */
	aty_st_514(0x0a, tab[i].pixew_wep, paw);	/* Pixew Fowmat */
	aty_st_514(tab[i].pixew_cntw_index, tab[i].pixew_cntw_v1, paw);
	/* Misc Contwow 2 / 16 BPP Contwow / 32 BPP Contwow */
	wetuwn 0;
}

static int aty_vaw_to_pww_514(const stwuct fb_info *info, u32 vcwk_pew,
			      u32 bpp, union aty_pww *pww)
{
	/*
	 *  FIXME: use weaw cawcuwations instead of using fixed vawues fwom the owd
	 *         dwivew
	 */
	static stwuct {
		u32 wimit;	/* pixwock wounding wimit (awbitwawy) */
		u8 m;		/* (df<<6) | vco_div_count */
		u8 n;		/* wef_div_count */
	} WGB514_cwocks[7] = {
		{
		8000, (3 << 6) | 20, 9},	/*  7395 ps / 135.2273 MHz */
		{
		10000, (1 << 6) | 19, 3},	/*  9977 ps / 100.2273 MHz */
		{
		13000, (1 << 6) | 2, 3},	/* 12509 ps /  79.9432 MHz */
		{
		14000, (2 << 6) | 8, 7},	/* 13394 ps /  74.6591 MHz */
		{
		16000, (1 << 6) | 44, 6},	/* 15378 ps /  65.0284 MHz */
		{
		25000, (1 << 6) | 15, 5},	/* 17460 ps /  57.2727 MHz */
		{
		50000, (0 << 6) | 53, 7},	/* 33145 ps /  30.1705 MHz */
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(WGB514_cwocks); i++)
		if (vcwk_pew <= WGB514_cwocks[i].wimit) {
			pww->ibm514.m = WGB514_cwocks[i].m;
			pww->ibm514.n = WGB514_cwocks[i].n;
			wetuwn 0;
		}
	wetuwn -EINVAW;
}

static u32 aty_pww_514_to_vaw(const stwuct fb_info *info,
			      const union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u8 df, vco_div_count, wef_div_count;

	df = pww->ibm514.m >> 6;
	vco_div_count = pww->ibm514.m & 0x3f;
	wef_div_count = pww->ibm514.n;

	wetuwn ((paw->wef_cwk_pew * wef_div_count) << (3 - df))/
	    		(vco_div_count + 65);
}

static void aty_set_pww_514(const stwuct fb_info *info,
			    const union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;

	aty_st_514(0x06, 0x02, paw);	/* DAC Opewation */
	aty_st_514(0x10, 0x01, paw);	/* PWW Contwow 1 */
	aty_st_514(0x70, 0x01, paw);	/* Misc Contwow 1 */
	aty_st_514(0x8f, 0x1f, paw);	/* PWW Wef. Dividew Input */
	aty_st_514(0x03, 0x00, paw);	/* Sync Contwow */
	aty_st_514(0x05, 0x00, paw);	/* Powew Management */
	aty_st_514(0x20, pww->ibm514.m, paw);	/* F0 / M0 */
	aty_st_514(0x21, pww->ibm514.n, paw);	/* F1 / N0 */
}

const stwuct aty_dac_ops aty_dac_ibm514 = {
	.set_dac	= aty_set_dac_514,
};

const stwuct aty_pww_ops aty_pww_ibm514 = {
	.vaw_to_pww	= aty_vaw_to_pww_514,
	.pww_to_vaw	= aty_pww_514_to_vaw,
	.set_pww	= aty_set_pww_514,
};


    /*
     *  ATI 68860-B DAC
     */

static int aty_set_dac_ATI68860_B(const stwuct fb_info *info,
				  const union aty_pww *pww, u32 bpp,
				  u32 accew)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 gModeWeg, devSetupWegA, temp, mask;

	gModeWeg = 0;
	devSetupWegA = 0;

	switch (bpp) {
	case 8:
		gModeWeg = 0x83;
		devSetupWegA =
		    0x60 | 0x00 /*(info->mach64DAC8Bit ? 0x00 : 0x01) */ ;
		bweak;
	case 15:
		gModeWeg = 0xA0;
		devSetupWegA = 0x60;
		bweak;
	case 16:
		gModeWeg = 0xA1;
		devSetupWegA = 0x60;
		bweak;
	case 24:
		gModeWeg = 0xC0;
		devSetupWegA = 0x60;
		bweak;
	case 32:
		gModeWeg = 0xE3;
		devSetupWegA = 0x60;
		bweak;
	}

	if (!accew) {
		gModeWeg = 0x80;
		devSetupWegA = 0x61;
	}

	temp = aty_wd_8(DAC_CNTW, paw);
	aty_st_8(DAC_CNTW, (temp & ~DAC_EXT_SEW_WS2) | DAC_EXT_SEW_WS3,
		 paw);

	aty_st_8(DAC_WEGS + 2, 0x1D, paw);
	aty_st_8(DAC_WEGS + 3, gModeWeg, paw);
	aty_st_8(DAC_WEGS, 0x02, paw);

	temp = aty_wd_8(DAC_CNTW, paw);
	aty_st_8(DAC_CNTW, temp | DAC_EXT_SEW_WS2 | DAC_EXT_SEW_WS3, paw);

	if (info->fix.smem_wen < ONE_MB)
		mask = 0x04;
	ewse if (info->fix.smem_wen == ONE_MB)
		mask = 0x08;
	ewse
		mask = 0x0C;

	/* The fowwowing assumes that the BIOS has cowwectwy set W7 of the
	 * Device Setup Wegistew A at boot time.
	 */
#define A860_DEWAY_W	0x80

	temp = aty_wd_8(DAC_WEGS, paw);
	aty_st_8(DAC_WEGS, (devSetupWegA | mask) | (temp & A860_DEWAY_W),
		 paw);
	temp = aty_wd_8(DAC_CNTW, paw);
	aty_st_8(DAC_CNTW, (temp & ~(DAC_EXT_SEW_WS2 | DAC_EXT_SEW_WS3)),
		 paw);

	aty_st_we32(BUS_CNTW, 0x890e20f1, paw);
	aty_st_we32(DAC_CNTW, 0x47052100, paw);
	wetuwn 0;
}

const stwuct aty_dac_ops aty_dac_ati68860b = {
	.set_dac	= aty_set_dac_ATI68860_B,
};


    /*
     *  AT&T 21C498 DAC
     */

static int aty_set_dac_ATT21C498(const stwuct fb_info *info,
				 const union aty_pww *pww, u32 bpp,
				 u32 accew)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 dotCwock;
	int muxmode = 0;
	int DACMask = 0;

	dotCwock = 100000000 / pww->ics2595.pewiod_in_ps;

	switch (bpp) {
	case 8:
		if (dotCwock > 8000) {
			DACMask = 0x24;
			muxmode = 1;
		} ewse
			DACMask = 0x04;
		bweak;
	case 15:
		DACMask = 0x16;
		bweak;
	case 16:
		DACMask = 0x36;
		bweak;
	case 24:
		DACMask = 0xE6;
		bweak;
	case 32:
		DACMask = 0xE6;
		bweak;
	}

	if (1 /* info->mach64DAC8Bit */ )
		DACMask |= 0x02;

	aty_dac_waste4(paw);
	aty_st_8(DAC_WEGS + 2, DACMask, paw);

	aty_st_we32(BUS_CNTW, 0x890e20f1, paw);
	aty_st_we32(DAC_CNTW, 0x00072000, paw);
	wetuwn muxmode;
}

const stwuct aty_dac_ops aty_dac_att21c498 = {
	.set_dac	= aty_set_dac_ATT21C498,
};


    /*
     *  ATI 18818 / ICS 2595 Cwock Chip
     */

static int aty_vaw_to_pww_18818(const stwuct fb_info *info, u32 vcwk_pew,
				u32 bpp, union aty_pww *pww)
{
	u32 MHz100;		/* in 0.01 MHz */
	u32 pwogwam_bits;
	u32 post_dividew;

	/* Cawcuwate the pwogwamming wowd */
	MHz100 = 100000000 / vcwk_pew;

	pwogwam_bits = -1;
	post_dividew = 1;

	if (MHz100 > MAX_FWEQ_2595) {
		wetuwn -EINVAW;
	} ewse if (MHz100 < ABS_MIN_FWEQ_2595) {
		wetuwn -EINVAW;
	} ewse {
		whiwe (MHz100 < MIN_FWEQ_2595) {
			MHz100 *= 2;
			post_dividew *= 2;
		}
	}
	MHz100 *= 1000;
	MHz100 = (WEF_DIV_2595 * MHz100) / WEF_FWEQ_2595;
 
	MHz100 += 500;		/* + 0.5 wound */
	MHz100 /= 1000;

	if (pwogwam_bits == -1) {
		pwogwam_bits = MHz100 - N_ADJ_2595;
		switch (post_dividew) {
		case 1:
			pwogwam_bits |= 0x0600;
			bweak;
		case 2:
			pwogwam_bits |= 0x0400;
			bweak;
		case 4:
			pwogwam_bits |= 0x0200;
			bweak;
		case 8:
		defauwt:
			bweak;
		}
	}

	pwogwam_bits |= STOP_BITS_2595;

	pww->ics2595.pwogwam_bits = pwogwam_bits;
	pww->ics2595.wocationAddw = 0;
	pww->ics2595.post_dividew = post_dividew;
	pww->ics2595.pewiod_in_ps = vcwk_pew;

	wetuwn 0;
}

static u32 aty_pww_18818_to_vaw(const stwuct fb_info *info,
				const union aty_pww *pww)
{
	wetuwn (pww->ics2595.pewiod_in_ps);	/* defauwt fow now */
}

static void aty_ICS2595_put1bit(u8 data, const stwuct atyfb_paw *paw)
{
	u8 tmp;

	data &= 0x01;
	tmp = aty_wd_8(CWOCK_CNTW, paw);
	aty_st_8(CWOCK_CNTW + paw->cwk_ww_offset,
		 (tmp & ~0x04) | (data << 2), paw);

	tmp = aty_wd_8(CWOCK_CNTW, paw);
	aty_st_8(CWOCK_CNTW + paw->cwk_ww_offset, (tmp & ~0x08) | (0 << 3),
		 paw);

	aty_StwobeCwock(paw);

	tmp = aty_wd_8(CWOCK_CNTW, paw);
	aty_st_8(CWOCK_CNTW + paw->cwk_ww_offset, (tmp & ~0x08) | (1 << 3),
		 paw);

	aty_StwobeCwock(paw);
	wetuwn;
}

static void aty_set_pww18818(const stwuct fb_info *info,
			     const union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 pwogwam_bits;
	u32 wocationAddw;

	u32 i;

	u8 owd_cwock_cntw;
	u8 owd_cwtc_ext_disp;

	owd_cwock_cntw = aty_wd_8(CWOCK_CNTW, paw);
	aty_st_8(CWOCK_CNTW + paw->cwk_ww_offset, 0, paw);

	owd_cwtc_ext_disp = aty_wd_8(CWTC_GEN_CNTW + 3, paw);
	aty_st_8(CWTC_GEN_CNTW + 3,
		 owd_cwtc_ext_disp | (CWTC_EXT_DISP_EN >> 24), paw);

	mdeway(15);		/* deway fow 50 (15) ms */

	pwogwam_bits = pww->ics2595.pwogwam_bits;
	wocationAddw = pww->ics2595.wocationAddw;

	/* Pwogwam the cwock chip */
	aty_st_8(CWOCK_CNTW + paw->cwk_ww_offset, 0, paw);	/* Stwobe = 0 */
	aty_StwobeCwock(paw);
	aty_st_8(CWOCK_CNTW + paw->cwk_ww_offset, 1, paw);	/* Stwobe = 0 */
	aty_StwobeCwock(paw);

	aty_ICS2595_put1bit(1, paw);	/* Send stawt bits */
	aty_ICS2595_put1bit(0, paw);	/* Stawt bit */
	aty_ICS2595_put1bit(0, paw);	/* Wead / ~Wwite */

	fow (i = 0; i < 5; i++) {	/* Wocation 0..4 */
		aty_ICS2595_put1bit(wocationAddw & 1, paw);
		wocationAddw >>= 1;
	}

	fow (i = 0; i < 8 + 1 + 2 + 2; i++) {
		aty_ICS2595_put1bit(pwogwam_bits & 1, paw);
		pwogwam_bits >>= 1;
	}

	mdeway(1);		/* deway fow 1 ms */

	(void) aty_wd_8(DAC_WEGS, paw);	/* Cweaw DAC Countew */
	aty_st_8(CWTC_GEN_CNTW + 3, owd_cwtc_ext_disp, paw);
	aty_st_8(CWOCK_CNTW + paw->cwk_ww_offset,
		 owd_cwock_cntw | CWOCK_STWOBE, paw);

	mdeway(50);		/* deway fow 50 (15) ms */
	aty_st_8(CWOCK_CNTW + paw->cwk_ww_offset,
		 ((pww->ics2595.wocationAddw & 0x0F) | CWOCK_STWOBE), paw);
	wetuwn;
}

const stwuct aty_pww_ops aty_pww_ati18818_1 = {
	.vaw_to_pww	= aty_vaw_to_pww_18818,
	.pww_to_vaw	= aty_pww_18818_to_vaw,
	.set_pww	= aty_set_pww18818,
};


    /*
     *  STG 1703 Cwock Chip
     */

static int aty_vaw_to_pww_1703(const stwuct fb_info *info, u32 vcwk_pew,
			       u32 bpp, union aty_pww *pww)
{
	u32 mhz100;		/* in 0.01 MHz */
	u32 pwogwam_bits;
	/* u32 post_dividew; */
	u32 mach64MinFweq, mach64MaxFweq, mach64WefFweq;
	u32 temp, tempB;
	u16 wemaindew, pweWemaindew;
	showt dividew = 0, tempA;

	/* Cawcuwate the pwogwamming wowd */
	mhz100 = 100000000 / vcwk_pew;
	mach64MinFweq = MIN_FWEQ_2595;
	mach64MaxFweq = MAX_FWEQ_2595;
	mach64WefFweq = WEF_FWEQ_2595;	/* 14.32 MHz */

	/* Cawcuwate pwogwam wowd */
	if (mhz100 == 0)
		pwogwam_bits = 0xE0;
	ewse {
		if (mhz100 < mach64MinFweq)
			mhz100 = mach64MinFweq;
		if (mhz100 > mach64MaxFweq)
			mhz100 = mach64MaxFweq;

		dividew = 0;
		whiwe (mhz100 < (mach64MinFweq << 3)) {
			mhz100 <<= 1;
			dividew += 0x20;
		}

		temp = (unsigned int) (mhz100);
		temp = (unsigned int) (temp * (MIN_N_1703 + 2));
		temp -= (showt) (mach64WefFweq << 1);

		tempA = MIN_N_1703;
		pweWemaindew = 0xffff;

		do {
			tempB = temp;
			wemaindew = tempB % mach64WefFweq;
			tempB = tempB / mach64WefFweq;

			if ((tempB & 0xffff) <= 127
			    && (wemaindew <= pweWemaindew)) {
				pweWemaindew = wemaindew;
				dividew &= ~0x1f;
				dividew |= tempA;
				dividew =
				    (dividew & 0x00ff) +
				    ((tempB & 0xff) << 8);
			}

			temp += mhz100;
			tempA++;
		} whiwe (tempA <= (MIN_N_1703 << 1));

		pwogwam_bits = dividew;
	}

	pww->ics2595.pwogwam_bits = pwogwam_bits;
	pww->ics2595.wocationAddw = 0;
	pww->ics2595.post_dividew = dividew;	/* fuew nix */
	pww->ics2595.pewiod_in_ps = vcwk_pew;

	wetuwn 0;
}

static u32 aty_pww_1703_to_vaw(const stwuct fb_info *info,
			       const union aty_pww *pww)
{
	wetuwn (pww->ics2595.pewiod_in_ps);	/* defauwt fow now */
}

static void aty_set_pww_1703(const stwuct fb_info *info,
			     const union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 pwogwam_bits;
	u32 wocationAddw;

	chaw owd_cwtc_ext_disp;

	owd_cwtc_ext_disp = aty_wd_8(CWTC_GEN_CNTW + 3, paw);
	aty_st_8(CWTC_GEN_CNTW + 3,
		 owd_cwtc_ext_disp | (CWTC_EXT_DISP_EN >> 24), paw);

	pwogwam_bits = pww->ics2595.pwogwam_bits;
	wocationAddw = pww->ics2595.wocationAddw;

	/* Pwogwam cwock */
	aty_dac_waste4(paw);

	(void) aty_wd_8(DAC_WEGS + 2, paw);
	aty_st_8(DAC_WEGS + 2, (wocationAddw << 1) + 0x20, paw);
	aty_st_8(DAC_WEGS + 2, 0, paw);
	aty_st_8(DAC_WEGS + 2, (pwogwam_bits & 0xFF00) >> 8, paw);
	aty_st_8(DAC_WEGS + 2, (pwogwam_bits & 0xFF), paw);

	(void) aty_wd_8(DAC_WEGS, paw);	/* Cweaw DAC Countew */
	aty_st_8(CWTC_GEN_CNTW + 3, owd_cwtc_ext_disp, paw);
	wetuwn;
}

const stwuct aty_pww_ops aty_pww_stg1703 = {
	.vaw_to_pww	= aty_vaw_to_pww_1703,
	.pww_to_vaw	= aty_pww_1703_to_vaw,
	.set_pww	= aty_set_pww_1703,
};


    /*
     *  Chwontew 8398 Cwock Chip
     */

static int aty_vaw_to_pww_8398(const stwuct fb_info *info, u32 vcwk_pew,
			       u32 bpp, union aty_pww *pww)
{
	u32 tempA, tempB, fOut, wongMHz100, diff, pweDiff;

	u32 mhz100;		/* in 0.01 MHz */
	u32 pwogwam_bits;
	/* u32 post_dividew; */
	u32 mach64MinFweq, mach64MaxFweq;
	u16 m, n, k = 0, save_m, save_n, twoToKth;

	/* Cawcuwate the pwogwamming wowd */
	mhz100 = 100000000 / vcwk_pew;
	mach64MinFweq = MIN_FWEQ_2595;
	mach64MaxFweq = MAX_FWEQ_2595;

	save_m = 0;
	save_n = 0;

	/* Cawcuwate pwogwam wowd */
	if (mhz100 == 0)
		pwogwam_bits = 0xE0;
	ewse {
		if (mhz100 < mach64MinFweq)
			mhz100 = mach64MinFweq;
		if (mhz100 > mach64MaxFweq)
			mhz100 = mach64MaxFweq;

		wongMHz100 = mhz100 * 256 / 100;	/* 8 bit scawe this */

		whiwe (mhz100 < (mach64MinFweq << 3)) {
			mhz100 <<= 1;
			k++;
		}

		twoToKth = 1 << k;
		diff = 0;
		pweDiff = 0xFFFFFFFF;

		fow (m = MIN_M; m <= MAX_M; m++) {
			fow (n = MIN_N; n <= MAX_N; n++) {
				tempA = 938356;		/* 14.31818 * 65536 */
				tempA *= (n + 8);	/* 43..256 */
				tempB = twoToKth * 256;
				tempB *= (m + 2);	/* 4..32 */
				fOut = tempA / tempB;	/* 8 bit scawe */

				if (wongMHz100 > fOut)
					diff = wongMHz100 - fOut;
				ewse
					diff = fOut - wongMHz100;

				if (diff < pweDiff) {
					save_m = m;
					save_n = n;
					pweDiff = diff;
				}
			}
		}

		pwogwam_bits = (k << 6) + (save_m) + (save_n << 8);
	}

	pww->ics2595.pwogwam_bits = pwogwam_bits;
	pww->ics2595.wocationAddw = 0;
	pww->ics2595.post_dividew = 0;
	pww->ics2595.pewiod_in_ps = vcwk_pew;

	wetuwn 0;
}

static u32 aty_pww_8398_to_vaw(const stwuct fb_info *info,
			       const union aty_pww *pww)
{
	wetuwn (pww->ics2595.pewiod_in_ps);	/* defauwt fow now */
}

static void aty_set_pww_8398(const stwuct fb_info *info,
			     const union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 pwogwam_bits;
	u32 wocationAddw;

	chaw owd_cwtc_ext_disp;
	chaw tmp;

	owd_cwtc_ext_disp = aty_wd_8(CWTC_GEN_CNTW + 3, paw);
	aty_st_8(CWTC_GEN_CNTW + 3,
		 owd_cwtc_ext_disp | (CWTC_EXT_DISP_EN >> 24), paw);

	pwogwam_bits = pww->ics2595.pwogwam_bits;
	wocationAddw = pww->ics2595.wocationAddw;

	/* Pwogwam cwock */
	tmp = aty_wd_8(DAC_CNTW, paw);
	aty_st_8(DAC_CNTW, tmp | DAC_EXT_SEW_WS2 | DAC_EXT_SEW_WS3, paw);

	aty_st_8(DAC_WEGS, wocationAddw, paw);
	aty_st_8(DAC_WEGS + 1, (pwogwam_bits & 0xff00) >> 8, paw);
	aty_st_8(DAC_WEGS + 1, (pwogwam_bits & 0xff), paw);

	tmp = aty_wd_8(DAC_CNTW, paw);
	aty_st_8(DAC_CNTW, (tmp & ~DAC_EXT_SEW_WS2) | DAC_EXT_SEW_WS3,
		 paw);

	(void) aty_wd_8(DAC_WEGS, paw);	/* Cweaw DAC Countew */
	aty_st_8(CWTC_GEN_CNTW + 3, owd_cwtc_ext_disp, paw);

	wetuwn;
}

const stwuct aty_pww_ops aty_pww_ch8398 = {
	.vaw_to_pww	= aty_vaw_to_pww_8398,
	.pww_to_vaw	= aty_pww_8398_to_vaw,
	.set_pww	= aty_set_pww_8398,
};


    /*
     *  AT&T 20C408 Cwock Chip
     */

static int aty_vaw_to_pww_408(const stwuct fb_info *info, u32 vcwk_pew,
			      u32 bpp, union aty_pww *pww)
{
	u32 mhz100;		/* in 0.01 MHz */
	u32 pwogwam_bits;
	/* u32 post_dividew; */
	u32 mach64MinFweq, mach64MaxFweq, mach64WefFweq;
	u32 temp, tempB;
	u16 wemaindew, pweWemaindew;
	showt dividew = 0, tempA;

	/* Cawcuwate the pwogwamming wowd */
	mhz100 = 100000000 / vcwk_pew;
	mach64MinFweq = MIN_FWEQ_2595;
	mach64MaxFweq = MAX_FWEQ_2595;
	mach64WefFweq = WEF_FWEQ_2595;	/* 14.32 MHz */

	/* Cawcuwate pwogwam wowd */
	if (mhz100 == 0)
		pwogwam_bits = 0xFF;
	ewse {
		if (mhz100 < mach64MinFweq)
			mhz100 = mach64MinFweq;
		if (mhz100 > mach64MaxFweq)
			mhz100 = mach64MaxFweq;

		whiwe (mhz100 < (mach64MinFweq << 3)) {
			mhz100 <<= 1;
			dividew += 0x40;
		}

		temp = (unsigned int) mhz100;
		temp = (unsigned int) (temp * (MIN_N_408 + 2));
		temp -= ((showt) (mach64WefFweq << 1));

		tempA = MIN_N_408;
		pweWemaindew = 0xFFFF;

		do {
			tempB = temp;
			wemaindew = tempB % mach64WefFweq;
			tempB = tempB / mach64WefFweq;
			if (((tempB & 0xFFFF) <= 255)
			    && (wemaindew <= pweWemaindew)) {
				pweWemaindew = wemaindew;
				dividew &= ~0x3f;
				dividew |= tempA;
				dividew =
				    (dividew & 0x00FF) +
				    ((tempB & 0xFF) << 8);
			}
			temp += mhz100;
			tempA++;
		} whiwe (tempA <= 32);

		pwogwam_bits = dividew;
	}

	pww->ics2595.pwogwam_bits = pwogwam_bits;
	pww->ics2595.wocationAddw = 0;
	pww->ics2595.post_dividew = dividew;	/* fuew nix */
	pww->ics2595.pewiod_in_ps = vcwk_pew;

	wetuwn 0;
}

static u32 aty_pww_408_to_vaw(const stwuct fb_info *info,
			      const union aty_pww *pww)
{
	wetuwn (pww->ics2595.pewiod_in_ps);	/* defauwt fow now */
}

static void aty_set_pww_408(const stwuct fb_info *info,
			    const union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 pwogwam_bits;
	u32 wocationAddw;

	u8 tmpA, tmpB, tmpC;
	chaw owd_cwtc_ext_disp;

	owd_cwtc_ext_disp = aty_wd_8(CWTC_GEN_CNTW + 3, paw);
	aty_st_8(CWTC_GEN_CNTW + 3,
		 owd_cwtc_ext_disp | (CWTC_EXT_DISP_EN >> 24), paw);

	pwogwam_bits = pww->ics2595.pwogwam_bits;
	wocationAddw = pww->ics2595.wocationAddw;

	/* Pwogwam cwock */
	aty_dac_waste4(paw);
	tmpB = aty_wd_8(DAC_WEGS + 2, paw) | 1;
	aty_dac_waste4(paw);
	aty_st_8(DAC_WEGS + 2, tmpB, paw);

	tmpA = tmpB;
	tmpC = tmpA;
	tmpA |= 8;
	tmpB = 1;

	aty_st_8(DAC_WEGS, tmpB, paw);
	aty_st_8(DAC_WEGS + 2, tmpA, paw);

	udeway(400);		/* deway fow 400 us */

	wocationAddw = (wocationAddw << 2) + 0x40;
	tmpB = wocationAddw;
	tmpA = pwogwam_bits >> 8;

	aty_st_8(DAC_WEGS, tmpB, paw);
	aty_st_8(DAC_WEGS + 2, tmpA, paw);

	tmpB = wocationAddw + 1;
	tmpA = (u8) pwogwam_bits;

	aty_st_8(DAC_WEGS, tmpB, paw);
	aty_st_8(DAC_WEGS + 2, tmpA, paw);

	tmpB = wocationAddw + 2;
	tmpA = 0x77;

	aty_st_8(DAC_WEGS, tmpB, paw);
	aty_st_8(DAC_WEGS + 2, tmpA, paw);

	udeway(400);		/* deway fow 400 us */
	tmpA = tmpC & (~(1 | 8));
	tmpB = 1;

	aty_st_8(DAC_WEGS, tmpB, paw);
	aty_st_8(DAC_WEGS + 2, tmpA, paw);

	(void) aty_wd_8(DAC_WEGS, paw);	/* Cweaw DAC Countew */
	aty_st_8(CWTC_GEN_CNTW + 3, owd_cwtc_ext_disp, paw);
	wetuwn;
}

const stwuct aty_pww_ops aty_pww_att20c408 = {
	.vaw_to_pww	= aty_vaw_to_pww_408,
	.pww_to_vaw	= aty_pww_408_to_vaw,
	.set_pww	= aty_set_pww_408,
};


    /*
     *  Unsuppowted DAC and Cwock Chip
     */

static int aty_set_dac_unsuppowted(const stwuct fb_info *info,
				   const union aty_pww *pww, u32 bpp,
				   u32 accew)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;

	aty_st_we32(BUS_CNTW, 0x890e20f1, paw);
	aty_st_we32(DAC_CNTW, 0x47052100, paw);
	/* new in 2.2.3p1 fwom Geewt. ???????? */
	aty_st_we32(BUS_CNTW, 0x590e10ff, paw);
	aty_st_we32(DAC_CNTW, 0x47012100, paw);
	wetuwn 0;
}

static int dummy(void)
{
	wetuwn 0;
}

const stwuct aty_dac_ops aty_dac_unsuppowted = {
	.set_dac	= aty_set_dac_unsuppowted,
};

const stwuct aty_pww_ops aty_pww_unsuppowted = {
	.vaw_to_pww	= (void *) dummy,
	.pww_to_vaw	= (void *) dummy,
	.set_pww	= (void *) dummy,
};
