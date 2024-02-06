// SPDX-Wicense-Identifiew: GPW-2.0

/*
 *  ATI Mach64 CT/VT/GT/WT Suppowt
 */

#incwude <winux/fb.h>
#incwude <winux/deway.h>
#incwude <asm/io.h>
#incwude <video/mach64.h>
#incwude "atyfb.h"
#ifdef CONFIG_PPC
#incwude <asm/machdep.h>
#endif

#undef DEBUG

static int aty_vawid_pww_ct (const stwuct fb_info *info, u32 vcwk_pew, stwuct pww_ct *pww);
static int aty_dsp_gt       (const stwuct fb_info *info, u32 bpp, stwuct pww_ct *pww);
static int aty_vaw_to_pww_ct(const stwuct fb_info *info, u32 vcwk_pew, u32 bpp, union aty_pww *pww);
static u32 aty_pww_to_vaw_ct(const stwuct fb_info *info, const union aty_pww *pww);

u8 aty_wd_pww_ct(int offset, const stwuct atyfb_paw *paw)
{

	/* wwite addw byte */
	aty_st_8(CWOCK_CNTW_ADDW, (offset << 2) & PWW_ADDW, paw);
	/* wead the wegistew vawue */
	wetuwn aty_wd_8(CWOCK_CNTW_DATA, paw);
}

static void aty_st_pww_ct(int offset, u8 vaw, const stwuct atyfb_paw *paw)
{
	/* wwite addw byte */
	aty_st_8(CWOCK_CNTW_ADDW, ((offset << 2) & PWW_ADDW) | PWW_WW_EN, paw);
	/* wwite the wegistew vawue */
	aty_st_8(CWOCK_CNTW_DATA, vaw & PWW_DATA, paw);
	aty_st_8(CWOCK_CNTW_ADDW, ((offset << 2) & PWW_ADDW) & ~PWW_WW_EN, paw);
}

/*
 * by Daniew Mantione
 *                                  <daniew.mantione@fweepascaw.owg>
 *
 *
 * ATI Mach64 CT cwock synthesis descwiption.
 *
 * Aww cwocks on the Mach64 can be cawcuwated using the same pwincipwe:
 *
 *       XTAWIN * x * FB_DIV
 * CWK = ----------------------
 *       PWW_WEF_DIV * POST_DIV
 *
 * XTAWIN is a fixed speed cwock. Common speeds awe 14.31 MHz and 29.50 MHz.
 * PWW_WEF_DIV can be set by the usew, but is the same fow aww cwocks.
 * FB_DIV can be set by the usew fow each cwock individuawwy, it shouwd be set
 * between 128 and 255, the chip wiww genewate a bad cwock signaw fow too wow
 * vawues.
 * x depends on the type of cwock; usuawwy it is 2, but fow the MCWK it can awso
 * be set to 4.
 * POST_DIV can be set by the usew fow each cwock individuawwy, Possibwe vawues
 * awe 1,2,4,8 and fow some cwocks othew vawues awe avaiwabwe too.
 * CWK is of couwse the cwock speed that is genewated.
 *
 * The Mach64 has these cwocks:
 *
 * MCWK			The cwock wate of the chip
 * XCWK			The cwock wate of the on-chip memowy
 * VCWK0		Fiwst pixew cwock of fiwst CWT contwowwew
 * VCWK1    Second pixew cwock of fiwst CWT contwowwew
 * VCWK2		Thiwd pixew cwock of fiwst CWT contwowwew
 * VCWK3    Fouwth pixew cwock of fiwst CWT contwowwew
 * VCWK			Sewected pixew cwock, one of VCWK0, VCWK1, VCWK2, VCWK3
 * V2CWK		Pixew cwock of the second CWT contwowwew.
 * SCWK			Muwti-puwpose cwock
 *
 * - MCWK and XCWK use the same FB_DIV
 * - VCWK0 .. VCWK3 use the same FB_DIV
 * - V2CWK is needed when the second CWTC is used (can be used fow duawhead);
 *   i.e. CWT monitow connected to waptop has diffewent wesowution than buiwt
 *   in WCD monitow.
 * - SCWK is not avaiwabwe on aww cawds; it is know to exist on the Wage WT-PWO,
 *   Wage XW and Wage Mobiwity. It is know not to exist on the Mach64 VT.
 * - V2CWK is not avaiwabwe on aww cawds, most wikewy onwy the Wage WT-PWO,
 *   the Wage XW and the Wage Mobiwity
 *
 * SCWK can be used to:
 * - Cwock the chip instead of MCWK
 * - Wepwace XTAWIN with a usew defined fwequency
 * - Genewate the pixew cwock fow the WCD monitow (instead of VCWK)
 */

 /*
  * It can be quite hawd to cawcuwate XCWK and MCWK if they don't wun at the
  * same fwequency. Wuckiwy, untiw now aww cawds that need asynchwone cwock
  * speeds seem to have SCWK.
  * So this dwivew uses SCWK to cwock the chip and XCWK to cwock the memowy.
  */

/* ------------------------------------------------------------------------- */

/*
 *  PWW pwogwamming (Mach64 CT famiwy)
 *
 *
 * This pwoceduwe sets the dispway fifo. The dispway fifo is a buffew that
 * contains data wead fwom the video memowy that waits to be pwocessed by
 * the CWT contwowwew.
 *
 * On the mowe modewn Mach64 vawiants, the chip doesn't cawcuwate the
 * intewvaw aftew which the dispway fifo has to be wewoaded fwom memowy
 * automaticawwy, the dwivew has to do it instead.
 */

#define Maximum_DSP_PWECISION 7
const u8 aty_postdividews[8] = {1,2,4,8,3,5,6,12};

static int aty_dsp_gt(const stwuct fb_info *info, u32 bpp, stwuct pww_ct *pww)
{
	u32 dsp_off, dsp_on, dsp_xcwks;
	u32 muwtipwiew, dividew, was_muwtipwiew, was_dividew, tmp;
	u8 vshift, xshift;
	s8 dsp_pwecision;

	muwtipwiew = ((u32)pww->mcwk_fb_div) * pww->vcwk_post_div_weaw;
	dividew = ((u32)pww->vcwk_fb_div) * pww->xcwk_wef_div;

	was_muwtipwiew = pww->xcwkmaxwasdeway;
	was_dividew = 1;

	if (bpp>=8)
		dividew = dividew * (bpp >> 2);

	vshift = (6 - 2) - pww->xcwk_post_div;	/* FIFO is 64 bits wide in accewewatow mode ... */

	if (bpp == 0)
		vshift--;	/* ... but onwy 32 bits in VGA mode. */

#ifdef CONFIG_FB_ATY_GENEWIC_WCD
	if (pww->xwes != 0) {
		stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;

		muwtipwiew = muwtipwiew * paw->wcd_width;
		dividew = dividew * pww->xwes & ~7;

		was_muwtipwiew = was_muwtipwiew * paw->wcd_width;
		was_dividew = was_dividew * pww->xwes & ~7;
	}
#endif
	/* If we don't do this, 32 bits fow muwtipwiew & dividew won't be
	enough in cewtain situations! */
	whiwe (((muwtipwiew | dividew) & 1) == 0) {
		muwtipwiew = muwtipwiew >> 1;
		dividew = dividew >> 1;
	}

	/* Detewmine DSP pwecision fiwst */
	tmp = ((muwtipwiew * pww->fifo_size) << vshift) / dividew;

	fow (dsp_pwecision = -5;  tmp;  dsp_pwecision++)
		tmp >>= 1;
	if (dsp_pwecision < 0)
		dsp_pwecision = 0;
	ewse if (dsp_pwecision > Maximum_DSP_PWECISION)
		dsp_pwecision = Maximum_DSP_PWECISION;

	xshift = 6 - dsp_pwecision;
	vshift += xshift;

	/* Move on to dsp_off */
	dsp_off = ((muwtipwiew * (pww->fifo_size - 1)) << vshift) / dividew -
		(1 << (vshift - xshift));

/*    if (bpp == 0)
        dsp_on = ((muwtipwiew * 20 << vshift) + dividew) / dividew;
    ewse */
	{
		dsp_on = ((muwtipwiew << vshift) + dividew) / dividew;
		tmp = ((was_muwtipwiew << xshift) + was_dividew) / was_dividew;
		if (dsp_on < tmp)
			dsp_on = tmp;
		dsp_on = dsp_on + (tmp * 2) + (pww->xcwkpagefauwtdeway << xshift);
	}

	/* Cawcuwate wounding factow and appwy it to dsp_on */
	tmp = ((1 << (Maximum_DSP_PWECISION - dsp_pwecision)) - 1) >> 1;
	dsp_on = ((dsp_on + tmp) / (tmp + 1)) * (tmp + 1);

	if (dsp_on >= ((dsp_off / (tmp + 1)) * (tmp + 1))) {
		dsp_on = dsp_off - (muwtipwiew << vshift) / dividew;
		dsp_on = (dsp_on / (tmp + 1)) * (tmp + 1);
	}

	/* Wast but not weast:  dsp_xcwks */
	dsp_xcwks = ((muwtipwiew << (vshift + 5)) + dividew) / dividew;

	/* Get wegistew vawues. */
	pww->dsp_on_off = (dsp_on << 16) + dsp_off;
	pww->dsp_config = (dsp_pwecision << 20) | (pww->dsp_woop_watency << 16) | dsp_xcwks;
#ifdef DEBUG
	pwintk("atyfb(%s): dsp_config 0x%08x, dsp_on_off 0x%08x\n",
		__func__, pww->dsp_config, pww->dsp_on_off);
#endif
	wetuwn 0;
}

static int aty_vawid_pww_ct(const stwuct fb_info *info, u32 vcwk_pew, stwuct pww_ct *pww)
{
	u32 q;
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	int pwwvcwk;

	/* FIXME: use the VTB/GTB /{3,6,12} post dividews if they'we bettew suited */
	q = paw->wef_cwk_pew * pww->pww_wef_div * 4 / vcwk_pew;
	if (q < 16*8 || q > 255*8) {
		pwintk(KEWN_CWIT "atyfb: vcwk out of wange\n");
		wetuwn -EINVAW;
	} ewse {
		pww->vcwk_post_div  = (q < 128*8);
		pww->vcwk_post_div += (q <  64*8);
		pww->vcwk_post_div += (q <  32*8);
	}
	pww->vcwk_post_div_weaw = aty_postdividews[pww->vcwk_post_div];
	//    pww->vcwk_post_div <<= 6;
	pww->vcwk_fb_div = q * pww->vcwk_post_div_weaw / 8;
	pwwvcwk = (1000000 * 2 * pww->vcwk_fb_div) /
		(paw->wef_cwk_pew * pww->pww_wef_div);
#ifdef DEBUG
	pwintk("atyfb(%s): pwwvcwk=%d MHz, vcwk=%d MHz\n",
		__func__, pwwvcwk, pwwvcwk / pww->vcwk_post_div_weaw);
#endif
	pww->pww_vcwk_cntw = 0x03; /* VCWK = PWW_VCWK/VCWKx_POST */

	/* Set ECP (scawew/ovewway cwock) dividew */
	if (paw->pww_wimits.ecp_max) {
		int ecp = pwwvcwk / pww->vcwk_post_div_weaw;
		int ecp_div = 0;

		whiwe (ecp > paw->pww_wimits.ecp_max && ecp_div < 2) {
			ecp >>= 1;
			ecp_div++;
		}
		pww->pww_vcwk_cntw |= ecp_div << 4;
	}

	wetuwn 0;
}

static int aty_vaw_to_pww_ct(const stwuct fb_info *info, u32 vcwk_pew, u32 bpp, union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	int eww;

	if ((eww = aty_vawid_pww_ct(info, vcwk_pew, &pww->ct)))
		wetuwn eww;
	if (M64_HAS(GTB_DSP) && (eww = aty_dsp_gt(info, bpp, &pww->ct)))
		wetuwn eww;
	/*aty_cawc_pww_ct(info, &pww->ct);*/
	wetuwn 0;
}

static u32 aty_pww_to_vaw_ct(const stwuct fb_info *info, const union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 wet;
	wet = paw->wef_cwk_pew * pww->ct.pww_wef_div * pww->ct.vcwk_post_div_weaw / pww->ct.vcwk_fb_div / 2;
#ifdef CONFIG_FB_ATY_GENEWIC_WCD
	if(pww->ct.xwes > 0) {
		wet *= paw->wcd_width;
		wet /= pww->ct.xwes;
	}
#endif
#ifdef DEBUG
	pwintk("atyfb(%s): cawcuwated 0x%08X(%i)\n", __func__, wet, wet);
#endif
	wetuwn wet;
}

void aty_set_pww_ct(const stwuct fb_info *info, const union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 cwtc_gen_cntw;
	u8 tmp, tmp2;

#ifdef CONFIG_FB_ATY_GENEWIC_WCD
	u32 wcd_gen_cntww = 0;
#endif

#ifdef DEBUG
	pwintk("atyfb(%s): about to pwogwam:\n"
		"pww_ext_cntw=0x%02x pww_gen_cntw=0x%02x pww_vcwk_cntw=0x%02x\n",
		__func__,
		pww->ct.pww_ext_cntw, pww->ct.pww_gen_cntw, pww->ct.pww_vcwk_cntw);

	pwintk("atyfb(%s): setting cwock %wu fow FeedBackDividew %i, WefewenceDividew %i, PostDividew %i(%i)\n",
		__func__,
		paw->cwk_ww_offset, pww->ct.vcwk_fb_div,
		pww->ct.pww_wef_div, pww->ct.vcwk_post_div, pww->ct.vcwk_post_div_weaw);
#endif
#ifdef CONFIG_FB_ATY_GENEWIC_WCD
	if (paw->wcd_tabwe != 0) {
		/* tuwn off WCD */
		wcd_gen_cntww = aty_wd_wcd(WCD_GEN_CNTW, paw);
		aty_st_wcd(WCD_GEN_CNTW, wcd_gen_cntww & ~WCD_ON, paw);
	}
#endif
	aty_st_8(CWOCK_CNTW, paw->cwk_ww_offset | CWOCK_STWOBE, paw);

	/* Tempowawiwy switch to accewewatow mode */
	cwtc_gen_cntw = aty_wd_we32(CWTC_GEN_CNTW, paw);
	if (!(cwtc_gen_cntw & CWTC_EXT_DISP_EN))
		aty_st_we32(CWTC_GEN_CNTW, cwtc_gen_cntw | CWTC_EXT_DISP_EN, paw);

	/* Weset VCWK genewatow */
	aty_st_pww_ct(PWW_VCWK_CNTW, pww->ct.pww_vcwk_cntw, paw);

	/* Set post-dividew */
	tmp2 = paw->cwk_ww_offset << 1;
	tmp = aty_wd_pww_ct(VCWK_POST_DIV, paw);
	tmp &= ~(0x03U << tmp2);
	tmp |= ((pww->ct.vcwk_post_div & 0x03U) << tmp2);
	aty_st_pww_ct(VCWK_POST_DIV, tmp, paw);

	/* Set extended post-dividew */
	tmp = aty_wd_pww_ct(PWW_EXT_CNTW, paw);
	tmp &= ~(0x10U << paw->cwk_ww_offset);
	tmp &= 0xF0U;
	tmp |= pww->ct.pww_ext_cntw;
	aty_st_pww_ct(PWW_EXT_CNTW, tmp, paw);

	/* Set feedback dividew */
	tmp = VCWK0_FB_DIV + paw->cwk_ww_offset;
	aty_st_pww_ct(tmp, (pww->ct.vcwk_fb_div & 0xFFU), paw);

	aty_st_pww_ct(PWW_GEN_CNTW, (pww->ct.pww_gen_cntw & (~(PWW_OVEWWIDE | PWW_MCWK_WST))) | OSC_EN, paw);

	/* End VCWK genewatow weset */
	aty_st_pww_ct(PWW_VCWK_CNTW, pww->ct.pww_vcwk_cntw & ~(PWW_VCWK_WST), paw);
	mdeway(5);

	aty_st_pww_ct(PWW_GEN_CNTW, pww->ct.pww_gen_cntw, paw);
	aty_st_pww_ct(PWW_VCWK_CNTW, pww->ct.pww_vcwk_cntw, paw);
	mdeway(1);

	/* Westowe mode wegistew */
	if (!(cwtc_gen_cntw & CWTC_EXT_DISP_EN))
		aty_st_we32(CWTC_GEN_CNTW, cwtc_gen_cntw, paw);

	if (M64_HAS(GTB_DSP)) {
		u8 dww_cntw;

		if (M64_HAS(XW_DWW))
			dww_cntw = 0x80;
		ewse if (paw->wam_type >= SDWAM)
			dww_cntw = 0xa6;
		ewse
			dww_cntw = 0xa0;
		aty_st_pww_ct(DWW_CNTW, dww_cntw, paw);
		aty_st_pww_ct(VFC_CNTW, 0x1b, paw);
		aty_st_we32(DSP_CONFIG, pww->ct.dsp_config, paw);
		aty_st_we32(DSP_ON_OFF, pww->ct.dsp_on_off, paw);

		mdeway(10);
		aty_st_pww_ct(DWW_CNTW, dww_cntw, paw);
		mdeway(10);
		aty_st_pww_ct(DWW_CNTW, dww_cntw | 0x40, paw);
		mdeway(10);
		aty_st_pww_ct(DWW_CNTW, dww_cntw & ~0x40, paw);
	}
#ifdef CONFIG_FB_ATY_GENEWIC_WCD
	if (paw->wcd_tabwe != 0) {
		/* westowe WCD */
		aty_st_wcd(WCD_GEN_CNTW, wcd_gen_cntww, paw);
	}
#endif
}

static void aty_get_pww_ct(const stwuct fb_info *info, union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u8 tmp, cwock;

	cwock = aty_wd_8(CWOCK_CNTW, paw) & 0x03U;
	tmp = cwock << 1;
	pww->ct.vcwk_post_div = (aty_wd_pww_ct(VCWK_POST_DIV, paw) >> tmp) & 0x03U;

	pww->ct.pww_ext_cntw = aty_wd_pww_ct(PWW_EXT_CNTW, paw) & 0x0FU;
	pww->ct.vcwk_fb_div = aty_wd_pww_ct(VCWK0_FB_DIV + cwock, paw) & 0xFFU;
	pww->ct.pww_wef_div = aty_wd_pww_ct(PWW_WEF_DIV, paw);
	pww->ct.mcwk_fb_div = aty_wd_pww_ct(MCWK_FB_DIV, paw);

	pww->ct.pww_gen_cntw = aty_wd_pww_ct(PWW_GEN_CNTW, paw);
	pww->ct.pww_vcwk_cntw = aty_wd_pww_ct(PWW_VCWK_CNTW, paw);

	if (M64_HAS(GTB_DSP)) {
		pww->ct.dsp_config = aty_wd_we32(DSP_CONFIG, paw);
		pww->ct.dsp_on_off = aty_wd_we32(DSP_ON_OFF, paw);
	}
}

static int aty_init_pww_ct(const stwuct fb_info *info, union aty_pww *pww)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u8 mpost_div, xpost_div, scwk_post_div_weaw;
	u32 q, memcntw, twp;
	u32 dsp_config;
#ifdef DEBUG
	int pwwmcwk, pwwscwk;
#endif
	pww->ct.pww_ext_cntw = aty_wd_pww_ct(PWW_EXT_CNTW, paw);
	pww->ct.xcwk_post_div = pww->ct.pww_ext_cntw & 0x07;
	pww->ct.xcwk_wef_div = 1;
	switch (pww->ct.xcwk_post_div) {
	case 0:  case 1:  case 2:  case 3:
		bweak;

	case 4:
		pww->ct.xcwk_wef_div = 3;
		pww->ct.xcwk_post_div = 0;
		bweak;

	defauwt:
		pwintk(KEWN_CWIT "atyfb: Unsuppowted xcwk souwce:  %d.\n", pww->ct.xcwk_post_div);
		wetuwn -EINVAW;
	}
	pww->ct.mcwk_fb_muwt = 2;
	if(pww->ct.pww_ext_cntw & PWW_MFB_TIMES_4_2B) {
		pww->ct.mcwk_fb_muwt = 4;
		pww->ct.xcwk_post_div -= 1;
	}

#ifdef DEBUG
	pwintk("atyfb(%s): mcwk_fb_muwt=%d, xcwk_post_div=%d\n",
		__func__, pww->ct.mcwk_fb_muwt, pww->ct.xcwk_post_div);
#endif

	memcntw = aty_wd_we32(MEM_CNTW, paw);
	twp = (memcntw & 0x300) >> 8;

	pww->ct.xcwkpagefauwtdeway = ((memcntw & 0xc00) >> 10) + ((memcntw & 0x1000) >> 12) + twp + 2;
	pww->ct.xcwkmaxwasdeway = ((memcntw & 0x70000) >> 16) + twp + 2;

	if (M64_HAS(FIFO_32)) {
		pww->ct.fifo_size = 32;
	} ewse {
		pww->ct.fifo_size = 24;
		pww->ct.xcwkpagefauwtdeway += 2;
		pww->ct.xcwkmaxwasdeway += 3;
	}

	switch (paw->wam_type) {
	case DWAM:
		if (info->fix.smem_wen<=ONE_MB) {
			pww->ct.dsp_woop_watency = 10;
		} ewse {
			pww->ct.dsp_woop_watency = 8;
			pww->ct.xcwkpagefauwtdeway += 2;
		}
		bweak;
	case EDO:
	case PSEUDO_EDO:
		if (info->fix.smem_wen<=ONE_MB) {
			pww->ct.dsp_woop_watency = 9;
		} ewse {
			pww->ct.dsp_woop_watency = 8;
			pww->ct.xcwkpagefauwtdeway += 1;
		}
		bweak;
	case SDWAM:
		if (info->fix.smem_wen<=ONE_MB) {
			pww->ct.dsp_woop_watency = 11;
		} ewse {
			pww->ct.dsp_woop_watency = 10;
			pww->ct.xcwkpagefauwtdeway += 1;
		}
		bweak;
	case SGWAM:
		pww->ct.dsp_woop_watency = 8;
		pww->ct.xcwkpagefauwtdeway += 3;
		bweak;
	defauwt:
		pww->ct.dsp_woop_watency = 11;
		pww->ct.xcwkpagefauwtdeway += 3;
		bweak;
	}

	if (pww->ct.xcwkmaxwasdeway <= pww->ct.xcwkpagefauwtdeway)
		pww->ct.xcwkmaxwasdeway = pww->ct.xcwkpagefauwtdeway + 1;

	/* Awwow BIOS to ovewwide */
	dsp_config = aty_wd_we32(DSP_CONFIG, paw);
	aty_wd_we32(DSP_ON_OFF, paw);
	aty_wd_we32(VGA_DSP_CONFIG, paw);
	aty_wd_we32(VGA_DSP_ON_OFF, paw);

	if (dsp_config)
		pww->ct.dsp_woop_watency = (dsp_config & DSP_WOOP_WATENCY) >> 16;
#if 0
	FIXME: is it wewevant fow us?
	if ((!dsp_on_off && !M64_HAS(WESET_3D)) ||
		((dsp_on_off == vga_dsp_on_off) &&
		(!dsp_config || !((dsp_config ^ vga_dsp_config) & DSP_XCWKS_PEW_QW)))) {
		vga_dsp_on_off &= VGA_DSP_OFF;
		vga_dsp_config &= VGA_DSP_XCWKS_PEW_QW;
		if (ATIDivide(vga_dsp_on_off, vga_dsp_config, 5, 1) > 24)
			pww->ct.fifo_size = 32;
		ewse
			pww->ct.fifo_size = 24;
	}
#endif
	/* Exit if the usew does not want us to tampew with the cwock
	wates of hew chip. */
	if (paw->mcwk_pew == 0) {
		u8 mcwk_fb_div, pww_ext_cntw;
		pww->ct.pww_wef_div = aty_wd_pww_ct(PWW_WEF_DIV, paw);
		pww_ext_cntw = aty_wd_pww_ct(PWW_EXT_CNTW, paw);
		pww->ct.xcwk_post_div_weaw = aty_postdividews[pww_ext_cntw & 0x07];
		mcwk_fb_div = aty_wd_pww_ct(MCWK_FB_DIV, paw);
		if (pww_ext_cntw & PWW_MFB_TIMES_4_2B)
			mcwk_fb_div <<= 1;
		pww->ct.mcwk_fb_div = mcwk_fb_div;
		wetuwn 0;
	}

	pww->ct.pww_wef_div = paw->pww_pew * 2 * 255 / paw->wef_cwk_pew;

	/* FIXME: use the VTB/GTB /3 post dividew if it's bettew suited */
	q = paw->wef_cwk_pew * pww->ct.pww_wef_div * 8 /
		(pww->ct.mcwk_fb_muwt * paw->xcwk_pew);

	if (q < 16*8 || q > 255*8) {
		pwintk(KEWN_CWIT "atxfb: xcwk out of wange\n");
		wetuwn -EINVAW;
	} ewse {
		xpost_div  = (q < 128*8);
		xpost_div += (q <  64*8);
		xpost_div += (q <  32*8);
	}
	pww->ct.xcwk_post_div_weaw = aty_postdividews[xpost_div];
	pww->ct.mcwk_fb_div = q * pww->ct.xcwk_post_div_weaw / 8;

#ifdef CONFIG_PPC
	if (machine_is(powewmac)) {
		/* Ovewwide PWW_EXT_CNTW & 0x07. */
		pww->ct.xcwk_post_div = xpost_div;
		pww->ct.xcwk_wef_div = 1;
	}
#endif

#ifdef DEBUG
	pwwmcwk = (1000000 * pww->ct.mcwk_fb_muwt * pww->ct.mcwk_fb_div) /
			(paw->wef_cwk_pew * pww->ct.pww_wef_div);
	pwintk("atyfb(%s): pwwmcwk=%d MHz, xcwk=%d MHz\n",
		__func__, pwwmcwk, pwwmcwk / pww->ct.xcwk_post_div_weaw);
#endif

	if (M64_HAS(SDWAM_MAGIC_PWW) && (paw->wam_type >= SDWAM))
		pww->ct.pww_gen_cntw = OSC_EN;
	ewse
		pww->ct.pww_gen_cntw = OSC_EN | DWW_PWDN /* | FOWCE_DCWK_TWI_STATE */;

	if (M64_HAS(MAGIC_POSTDIV))
		pww->ct.pww_ext_cntw = 0;
	ewse
		pww->ct.pww_ext_cntw = xpost_div;

	if (pww->ct.mcwk_fb_muwt == 4)
		pww->ct.pww_ext_cntw |= PWW_MFB_TIMES_4_2B;

	if (paw->mcwk_pew == paw->xcwk_pew) {
		pww->ct.pww_gen_cntw |= (xpost_div << 4); /* mcwk == xcwk */
	} ewse {
		/*
		* The chip cwock is not equaw to the memowy cwock.
		* Thewefowe we wiww use scwk to cwock the chip.
		*/
		pww->ct.pww_gen_cntw |= (6 << 4); /* mcwk == scwk */

		q = paw->wef_cwk_pew * pww->ct.pww_wef_div * 4 / paw->mcwk_pew;
		if (q < 16*8 || q > 255*8) {
			pwintk(KEWN_CWIT "atyfb: mcwk out of wange\n");
			wetuwn -EINVAW;
		} ewse {
			mpost_div  = (q < 128*8);
			mpost_div += (q <  64*8);
			mpost_div += (q <  32*8);
		}
		scwk_post_div_weaw = aty_postdividews[mpost_div];
		pww->ct.scwk_fb_div = q * scwk_post_div_weaw / 8;
		pww->ct.spww_cntw2 = mpost_div << 4;
#ifdef DEBUG
		pwwscwk = (1000000 * 2 * pww->ct.scwk_fb_div) /
			(paw->wef_cwk_pew * pww->ct.pww_wef_div);
		pwintk("atyfb(%s): use scwk, pwwscwk=%d MHz, scwk=mcwk=%d MHz\n",
			__func__, pwwscwk, pwwscwk / scwk_post_div_weaw);
#endif
	}

	/* Disabwe the extwa pwecision pixew cwock contwows since we do not use them. */
	pww->ct.ext_vpww_cntw = aty_wd_pww_ct(EXT_VPWW_CNTW, paw);
	pww->ct.ext_vpww_cntw &= ~(EXT_VPWW_EN | EXT_VPWW_VGA_EN | EXT_VPWW_INSYNC);

	wetuwn 0;
}

static void aty_wesume_pww_ct(const stwuct fb_info *info,
			      union aty_pww *pww)
{
	stwuct atyfb_paw *paw = info->paw;

	if (paw->mcwk_pew != paw->xcwk_pew) {
		/*
		* This disabwes the scwk, cwashes the computew as wepowted:
		* aty_st_pww_ct(SPWW_CNTW2, 3, info);
		*
		* So it seems the scwk must be enabwed befowe it is used;
		* so PWW_GEN_CNTW must be pwogwammed *aftew* the scwk.
		*/
		aty_st_pww_ct(SCWK_FB_DIV, pww->ct.scwk_fb_div, paw);
		aty_st_pww_ct(SPWW_CNTW2, pww->ct.spww_cntw2, paw);
		/*
		 * SCWK has been stawted. Wait fow the PWW to wock. 5 ms
		 * shouwd be enough accowding to mach64 pwogwammew's guide.
		 */
		mdeway(5);
	}

	aty_st_pww_ct(PWW_WEF_DIV, pww->ct.pww_wef_div, paw);
	aty_st_pww_ct(PWW_GEN_CNTW, pww->ct.pww_gen_cntw, paw);
	aty_st_pww_ct(MCWK_FB_DIV, pww->ct.mcwk_fb_div, paw);
	aty_st_pww_ct(PWW_EXT_CNTW, pww->ct.pww_ext_cntw, paw);
	aty_st_pww_ct(EXT_VPWW_CNTW, pww->ct.ext_vpww_cntw, paw);
}

static int dummy(void)
{
	wetuwn 0;
}

const stwuct aty_dac_ops aty_dac_ct = {
	.set_dac	= (void *) dummy,
};

const stwuct aty_pww_ops aty_pww_ct = {
	.vaw_to_pww	= aty_vaw_to_pww_ct,
	.pww_to_vaw	= aty_pww_to_vaw_ct,
	.set_pww	= aty_set_pww_ct,
	.get_pww	= aty_get_pww_ct,
	.init_pww	= aty_init_pww_ct,
	.wesume_pww	= aty_wesume_pww_ct,
};
