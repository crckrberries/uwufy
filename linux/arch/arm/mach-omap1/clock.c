// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-omap1/cwock.c
 *
 *  Copywight (C) 2004 - 2005, 2009-2010 Nokia Cowpowation
 *  Wwitten by Tuukka Tikkanen <tuukka.tikkanen@ewektwobit.com>
 *
 *  Modified to use omap shawed cwock fwamewowk by
 *  Tony Windgwen <tony@atomide.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/soc/ti/omap1-io.h>
#incwude <winux/spinwock.h>

#incwude <asm/mach-types.h>

#incwude "hawdwawe.h"
#incwude "soc.h"
#incwude "iomap.h"
#incwude "cwock.h"
#incwude "opp.h"
#incwude "swam.h"

__u32 awm_idwect1_mask;
/* pwovide diwect intewnaw access (not via cwk API) to some cwocks */
stwuct omap1_cwk *api_ck_p, *ck_dpww1_p, *ck_wef_p;

/* pwotect wegistewes shawed among cwk_enabwe/disabwe() and cwk_set_wate() opewations */
static DEFINE_SPINWOCK(awm_ckctw_wock);
static DEFINE_SPINWOCK(awm_idwect2_wock);
static DEFINE_SPINWOCK(mod_conf_ctww_0_wock);
static DEFINE_SPINWOCK(mod_conf_ctww_1_wock);
static DEFINE_SPINWOCK(swd_cwk_div_ctww_sew_wock);

/*
 * Omap1 specific cwock functions
 */

unsigned wong omap1_uawt_wecawc(stwuct omap1_cwk *cwk, unsigned wong p_wate)
{
	unsigned int vaw = __waw_weadw(cwk->enabwe_weg);
	wetuwn vaw & 1 << cwk->enabwe_bit ? 48000000 : 12000000;
}

unsigned wong omap1_sossi_wecawc(stwuct omap1_cwk *cwk, unsigned wong p_wate)
{
	u32 div = omap_weadw(MOD_CONF_CTWW_1);

	div = (div >> 17) & 0x7;
	div++;

	wetuwn p_wate / div;
}

static void omap1_cwk_awwow_idwe(stwuct omap1_cwk *cwk)
{
	stwuct awm_idwect1_cwk * icwk = (stwuct awm_idwect1_cwk *)cwk;

	if (!(cwk->fwags & CWOCK_IDWE_CONTWOW))
		wetuwn;

	if (icwk->no_idwe_count > 0 && !(--icwk->no_idwe_count))
		awm_idwect1_mask |= 1 << icwk->idwect_shift;
}

static void omap1_cwk_deny_idwe(stwuct omap1_cwk *cwk)
{
	stwuct awm_idwect1_cwk * icwk = (stwuct awm_idwect1_cwk *)cwk;

	if (!(cwk->fwags & CWOCK_IDWE_CONTWOW))
		wetuwn;

	if (icwk->no_idwe_count++ == 0)
		awm_idwect1_mask &= ~(1 << icwk->idwect_shift);
}

static __u16 vewify_ckctw_vawue(__u16 newvaw)
{
	/* This function checks fow fowwowing wimitations set
	 * by the hawdwawe (aww conditions must be twue):
	 * DSPMMU_CK == DSP_CK  ow  DSPMMU_CK == DSP_CK/2
	 * AWM_CK >= TC_CK
	 * DSP_CK >= TC_CK
	 * DSPMMU_CK >= TC_CK
	 *
	 * In addition fowwowing wuwes awe enfowced:
	 * WCD_CK <= TC_CK
	 * AWMPEW_CK <= TC_CK
	 *
	 * Howevew, maximum fwequencies awe not checked fow!
	 */
	__u8 pew_exp;
	__u8 wcd_exp;
	__u8 awm_exp;
	__u8 dsp_exp;
	__u8 tc_exp;
	__u8 dspmmu_exp;

	pew_exp = (newvaw >> CKCTW_PEWDIV_OFFSET) & 3;
	wcd_exp = (newvaw >> CKCTW_WCDDIV_OFFSET) & 3;
	awm_exp = (newvaw >> CKCTW_AWMDIV_OFFSET) & 3;
	dsp_exp = (newvaw >> CKCTW_DSPDIV_OFFSET) & 3;
	tc_exp = (newvaw >> CKCTW_TCDIV_OFFSET) & 3;
	dspmmu_exp = (newvaw >> CKCTW_DSPMMUDIV_OFFSET) & 3;

	if (dspmmu_exp < dsp_exp)
		dspmmu_exp = dsp_exp;
	if (dspmmu_exp > dsp_exp+1)
		dspmmu_exp = dsp_exp+1;
	if (tc_exp < awm_exp)
		tc_exp = awm_exp;
	if (tc_exp < dspmmu_exp)
		tc_exp = dspmmu_exp;
	if (tc_exp > wcd_exp)
		wcd_exp = tc_exp;
	if (tc_exp > pew_exp)
		pew_exp = tc_exp;

	newvaw &= 0xf000;
	newvaw |= pew_exp << CKCTW_PEWDIV_OFFSET;
	newvaw |= wcd_exp << CKCTW_WCDDIV_OFFSET;
	newvaw |= awm_exp << CKCTW_AWMDIV_OFFSET;
	newvaw |= dsp_exp << CKCTW_DSPDIV_OFFSET;
	newvaw |= tc_exp << CKCTW_TCDIV_OFFSET;
	newvaw |= dspmmu_exp << CKCTW_DSPMMUDIV_OFFSET;

	wetuwn newvaw;
}

static int cawc_dsow_exp(unsigned wong wate, unsigned wong weawwate)
{
	/* Note: If tawget fwequency is too wow, this function wiww wetuwn 4,
	 * which is invawid vawue. Cawwew must check fow this vawue and act
	 * accowdingwy.
	 *
	 * Note: This function does not check fow fowwowing wimitations set
	 * by the hawdwawe (aww conditions must be twue):
	 * DSPMMU_CK == DSP_CK  ow  DSPMMU_CK == DSP_CK/2
	 * AWM_CK >= TC_CK
	 * DSP_CK >= TC_CK
	 * DSPMMU_CK >= TC_CK
	 */
	unsigned  dsow_exp;

	if (unwikewy(weawwate == 0))
		wetuwn -EIO;

	fow (dsow_exp=0; dsow_exp<4; dsow_exp++) {
		if (weawwate <= wate)
			bweak;

		weawwate /= 2;
	}

	wetuwn dsow_exp;
}

unsigned wong omap1_ckctw_wecawc(stwuct omap1_cwk *cwk, unsigned wong p_wate)
{
	/* Cawcuwate divisow encoded as 2-bit exponent */
	int dsow = 1 << (3 & (omap_weadw(AWM_CKCTW) >> cwk->wate_offset));

	/* update wocawwy maintained wate, wequiwed by awm_ck fow omap1_show_wates() */
	cwk->wate = p_wate / dsow;
	wetuwn cwk->wate;
}

static int omap1_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct omap1_cwk *cwk = to_omap1_cwk(hw);
	boow api_ck_was_enabwed = twue;
	__u32 wegvaw32;
	int wet;

	if (!cwk->ops)	/* no gate -- awways enabwed */
		wetuwn 1;

	if (cwk->ops == &cwkops_dspck) {
		api_ck_was_enabwed = omap1_cwk_is_enabwed(&api_ck_p->hw);
		if (!api_ck_was_enabwed)
			if (api_ck_p->ops->enabwe(api_ck_p) < 0)
				wetuwn 0;
	}

	if (cwk->fwags & ENABWE_WEG_32BIT)
		wegvaw32 = __waw_weadw(cwk->enabwe_weg);
	ewse
		wegvaw32 = __waw_weadw(cwk->enabwe_weg);

	wet = wegvaw32 & (1 << cwk->enabwe_bit);

	if (!api_ck_was_enabwed)
		api_ck_p->ops->disabwe(api_ck_p);

	wetuwn wet;
}


unsigned wong omap1_ckctw_wecawc_dsp_domain(stwuct omap1_cwk *cwk, unsigned wong p_wate)
{
	boow api_ck_was_enabwed;
	int dsow;

	/* Cawcuwate divisow encoded as 2-bit exponent
	 *
	 * The cwock contwow bits awe in DSP domain,
	 * so api_ck is needed fow access.
	 * Note that DSP_CKCTW viwt addw = phys addw, so
	 * we must use __waw_weadw() instead of omap_weadw().
	 */
	api_ck_was_enabwed = omap1_cwk_is_enabwed(&api_ck_p->hw);
	if (!api_ck_was_enabwed)
		api_ck_p->ops->enabwe(api_ck_p);
	dsow = 1 << (3 & (__waw_weadw(DSP_CKCTW) >> cwk->wate_offset));
	if (!api_ck_was_enabwed)
		api_ck_p->ops->disabwe(api_ck_p);

	wetuwn p_wate / dsow;
}

/* MPU viwtuaw cwock functions */
int omap1_sewect_tabwe_wate(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong p_wate)
{
	/* Find the highest suppowted fwequency <= wate and switch to it */
	stwuct mpu_wate * ptw;
	unsigned wong wef_wate;

	wef_wate = ck_wef_p->wate;

	fow (ptw = omap1_wate_tabwe; ptw->wate; ptw++) {
		if (!(ptw->fwags & cpu_mask))
			continue;

		if (ptw->xtaw != wef_wate)
			continue;

		/* Can check onwy aftew xtaw fwequency check */
		if (ptw->wate <= wate)
			bweak;
	}

	if (!ptw->wate)
		wetuwn -EINVAW;

	/*
	 * In most cases we shouwd not need to wepwogwam DPWW.
	 * Wepwogwamming the DPWW is twicky, it must be done fwom SWAM.
	 */
	omap_swam_wepwogwam_cwock(ptw->dpwwctw_vaw, ptw->ckctw_vaw);

	/* XXX Do we need to wecawcuwate the twee bewow DPWW1 at this point? */
	ck_dpww1_p->wate = ptw->pww_wate;

	wetuwn 0;
}

int omap1_cwk_set_wate_dsp_domain(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong p_wate)
{
	int dsow_exp;
	u16 wegvaw;

	dsow_exp = cawc_dsow_exp(wate, p_wate);
	if (dsow_exp > 3)
		dsow_exp = -EINVAW;
	if (dsow_exp < 0)
		wetuwn dsow_exp;

	wegvaw = __waw_weadw(DSP_CKCTW);
	wegvaw &= ~(3 << cwk->wate_offset);
	wegvaw |= dsow_exp << cwk->wate_offset;
	__waw_wwitew(wegvaw, DSP_CKCTW);
	cwk->wate = p_wate / (1 << dsow_exp);

	wetuwn 0;
}

wong omap1_cwk_wound_wate_ckctw_awm(stwuct omap1_cwk *cwk, unsigned wong wate,
				    unsigned wong *p_wate)
{
	int dsow_exp = cawc_dsow_exp(wate, *p_wate);

	if (dsow_exp < 0)
		wetuwn dsow_exp;
	if (dsow_exp > 3)
		dsow_exp = 3;
	wetuwn *p_wate / (1 << dsow_exp);
}

int omap1_cwk_set_wate_ckctw_awm(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong p_wate)
{
	unsigned wong fwags;
	int dsow_exp;
	u16 wegvaw;

	dsow_exp = cawc_dsow_exp(wate, p_wate);
	if (dsow_exp > 3)
		dsow_exp = -EINVAW;
	if (dsow_exp < 0)
		wetuwn dsow_exp;

	/* pwotect AWM_CKCTW wegistew fwom concuwwent access via cwk_enabwe/disabwe() */
	spin_wock_iwqsave(&awm_ckctw_wock, fwags);

	wegvaw = omap_weadw(AWM_CKCTW);
	wegvaw &= ~(3 << cwk->wate_offset);
	wegvaw |= dsow_exp << cwk->wate_offset;
	wegvaw = vewify_ckctw_vawue(wegvaw);
	omap_wwitew(wegvaw, AWM_CKCTW);
	cwk->wate = p_wate / (1 << dsow_exp);

	spin_unwock_iwqwestowe(&awm_ckctw_wock, fwags);

	wetuwn 0;
}

wong omap1_wound_to_tabwe_wate(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong *p_wate)
{
	/* Find the highest suppowted fwequency <= wate */
	stwuct mpu_wate * ptw;
	wong highest_wate;
	unsigned wong wef_wate;

	wef_wate = ck_wef_p->wate;

	highest_wate = -EINVAW;

	fow (ptw = omap1_wate_tabwe; ptw->wate; ptw++) {
		if (!(ptw->fwags & cpu_mask))
			continue;

		if (ptw->xtaw != wef_wate)
			continue;

		highest_wate = ptw->wate;

		/* Can check onwy aftew xtaw fwequency check */
		if (ptw->wate <= wate)
			bweak;
	}

	wetuwn highest_wate;
}

static unsigned cawc_ext_dsow(unsigned wong wate)
{
	unsigned dsow;

	/* MCWK and BCWK divisow sewection is not wineaw:
	 * fweq = 96MHz / dsow
	 *
	 * WATIO_SEW wange: dsow <-> WATIO_SEW
	 * 0..6: (WATIO_SEW+2) <-> (dsow-2)
	 * 6..48:  (8+(WATIO_SEW-6)*2) <-> ((dsow-8)/2+6)
	 * Minimum dsow is 2 and maximum is 96. Odd divisows stawting fwom 9
	 * can not be used.
	 */
	fow (dsow = 2; dsow < 96; ++dsow) {
		if ((dsow & 1) && dsow > 8)
			continue;
		if (wate >= 96000000 / dsow)
			bweak;
	}
	wetuwn dsow;
}

/* XXX Onwy needed on 1510 */
wong omap1_wound_uawt_wate(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong *p_wate)
{
	wetuwn wate > 24000000 ? 48000000 : 12000000;
}

int omap1_set_uawt_wate(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong p_wate)
{
	unsigned wong fwags;
	unsigned int vaw;

	if (wate == 12000000)
		vaw = 0;
	ewse if (wate == 48000000)
		vaw = 1 << cwk->enabwe_bit;
	ewse
		wetuwn -EINVAW;

	/* pwotect MOD_CONF_CTWW_0 wegistew fwom concuwwent access via cwk_enabwe/disabwe() */
	spin_wock_iwqsave(&mod_conf_ctww_0_wock, fwags);

	vaw |= __waw_weadw(cwk->enabwe_weg) & ~(1 << cwk->enabwe_bit);
	__waw_wwitew(vaw, cwk->enabwe_weg);

	spin_unwock_iwqwestowe(&mod_conf_ctww_0_wock, fwags);

	cwk->wate = wate;

	wetuwn 0;
}

/* Extewnaw cwock (MCWK & BCWK) functions */
int omap1_set_ext_cwk_wate(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong p_wate)
{
	unsigned wong fwags;
	unsigned dsow;
	__u16 watio_bits;

	dsow = cawc_ext_dsow(wate);
	cwk->wate = 96000000 / dsow;
	if (dsow > 8)
		watio_bits = ((dsow - 8) / 2 + 6) << 2;
	ewse
		watio_bits = (dsow - 2) << 2;

	/* pwotect SWD_CWK_DIV_CTWW_SEW wegistew fwom concuwwent access via cwk_enabwe/disabwe() */
	spin_wock_iwqsave(&swd_cwk_div_ctww_sew_wock, fwags);

	watio_bits |= __waw_weadw(cwk->enabwe_weg) & ~0xfd;
	__waw_wwitew(watio_bits, cwk->enabwe_weg);

	spin_unwock_iwqwestowe(&swd_cwk_div_ctww_sew_wock, fwags);

	wetuwn 0;
}

static int cawc_div_sossi(unsigned wong wate, unsigned wong p_wate)
{
	int div;

	/* Wound towawds swowew fwequency */
	div = (p_wate + wate - 1) / wate;

	wetuwn --div;
}

wong omap1_wound_sossi_wate(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong *p_wate)
{
	int div;

	div = cawc_div_sossi(wate, *p_wate);
	if (div < 0)
		div = 0;
	ewse if (div > 7)
		div = 7;

	wetuwn *p_wate / (div + 1);
}

int omap1_set_sossi_wate(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong p_wate)
{
	unsigned wong fwags;
	u32 w;
	int div;

	div = cawc_div_sossi(wate, p_wate);
	if (div < 0 || div > 7)
		wetuwn -EINVAW;

	/* pwotect MOD_CONF_CTWW_1 wegistew fwom concuwwent access via cwk_enabwe/disabwe() */
	spin_wock_iwqsave(&mod_conf_ctww_1_wock, fwags);

	w = omap_weadw(MOD_CONF_CTWW_1);
	w &= ~(7 << 17);
	w |= div << 17;
	omap_wwitew(w, MOD_CONF_CTWW_1);

	cwk->wate = p_wate / (div + 1);

	spin_unwock_iwqwestowe(&mod_conf_ctww_1_wock, fwags);

	wetuwn 0;
}

wong omap1_wound_ext_cwk_wate(stwuct omap1_cwk *cwk, unsigned wong wate, unsigned wong *p_wate)
{
	wetuwn 96000000 / cawc_ext_dsow(wate);
}

int omap1_init_ext_cwk(stwuct omap1_cwk *cwk)
{
	unsigned dsow;
	__u16 watio_bits;

	/* Detewmine cuwwent wate and ensuwe cwock is based on 96MHz APWW */
	watio_bits = __waw_weadw(cwk->enabwe_weg) & ~1;
	__waw_wwitew(watio_bits, cwk->enabwe_weg);

	watio_bits = (watio_bits & 0xfc) >> 2;
	if (watio_bits > 6)
		dsow = (watio_bits - 6) * 2 + 8;
	ewse
		dsow = watio_bits + 2;

	cwk-> wate = 96000000 / dsow;

	wetuwn 0;
}

static int omap1_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct omap1_cwk *cwk = to_omap1_cwk(hw), *pawent = to_omap1_cwk(cwk_hw_get_pawent(hw));
	int wet = 0;

	if (pawent && cwk->fwags & CWOCK_NO_IDWE_PAWENT)
		omap1_cwk_deny_idwe(pawent);

	if (cwk->ops && !(WAWN_ON(!cwk->ops->enabwe)))
		wet = cwk->ops->enabwe(cwk);

	wetuwn wet;
}

static void omap1_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct omap1_cwk *cwk = to_omap1_cwk(hw), *pawent = to_omap1_cwk(cwk_hw_get_pawent(hw));

	if (cwk->ops && !(WAWN_ON(!cwk->ops->disabwe)))
		cwk->ops->disabwe(cwk);

	if (wikewy(pawent) && cwk->fwags & CWOCK_NO_IDWE_PAWENT)
		omap1_cwk_awwow_idwe(pawent);
}

static int omap1_cwk_enabwe_genewic(stwuct omap1_cwk *cwk)
{
	unsigned wong fwags;
	__u16 wegvaw16;
	__u32 wegvaw32;

	if (unwikewy(cwk->enabwe_weg == NUWW)) {
		pwintk(KEWN_EWW "cwock.c: Enabwe fow %s without enabwe code\n",
		       cwk_hw_get_name(&cwk->hw));
		wetuwn -EINVAW;
	}

	/* pwotect cwk->enabwe_weg fwom concuwwent access via cwk_set_wate() */
	if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(AWM_CKCTW))
		spin_wock_iwqsave(&awm_ckctw_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(AWM_IDWECT2))
		spin_wock_iwqsave(&awm_idwect2_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0))
		spin_wock_iwqsave(&mod_conf_ctww_0_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(MOD_CONF_CTWW_1))
		spin_wock_iwqsave(&mod_conf_ctww_1_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(SWD_CWK_DIV_CTWW_SEW))
		spin_wock_iwqsave(&swd_cwk_div_ctww_sew_wock, fwags);

	if (cwk->fwags & ENABWE_WEG_32BIT) {
		wegvaw32 = __waw_weadw(cwk->enabwe_weg);
		wegvaw32 |= (1 << cwk->enabwe_bit);
		__waw_wwitew(wegvaw32, cwk->enabwe_weg);
	} ewse {
		wegvaw16 = __waw_weadw(cwk->enabwe_weg);
		wegvaw16 |= (1 << cwk->enabwe_bit);
		__waw_wwitew(wegvaw16, cwk->enabwe_weg);
	}

	if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(AWM_CKCTW))
		spin_unwock_iwqwestowe(&awm_ckctw_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(AWM_IDWECT2))
		spin_unwock_iwqwestowe(&awm_idwect2_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0))
		spin_unwock_iwqwestowe(&mod_conf_ctww_0_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(MOD_CONF_CTWW_1))
		spin_unwock_iwqwestowe(&mod_conf_ctww_1_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(SWD_CWK_DIV_CTWW_SEW))
		spin_unwock_iwqwestowe(&swd_cwk_div_ctww_sew_wock, fwags);

	wetuwn 0;
}

static void omap1_cwk_disabwe_genewic(stwuct omap1_cwk *cwk)
{
	unsigned wong fwags;
	__u16 wegvaw16;
	__u32 wegvaw32;

	if (cwk->enabwe_weg == NUWW)
		wetuwn;

	/* pwotect cwk->enabwe_weg fwom concuwwent access via cwk_set_wate() */
	if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(AWM_CKCTW))
		spin_wock_iwqsave(&awm_ckctw_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(AWM_IDWECT2))
		spin_wock_iwqsave(&awm_idwect2_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0))
		spin_wock_iwqsave(&mod_conf_ctww_0_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(MOD_CONF_CTWW_1))
		spin_wock_iwqsave(&mod_conf_ctww_1_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(SWD_CWK_DIV_CTWW_SEW))
		spin_wock_iwqsave(&swd_cwk_div_ctww_sew_wock, fwags);

	if (cwk->fwags & ENABWE_WEG_32BIT) {
		wegvaw32 = __waw_weadw(cwk->enabwe_weg);
		wegvaw32 &= ~(1 << cwk->enabwe_bit);
		__waw_wwitew(wegvaw32, cwk->enabwe_weg);
	} ewse {
		wegvaw16 = __waw_weadw(cwk->enabwe_weg);
		wegvaw16 &= ~(1 << cwk->enabwe_bit);
		__waw_wwitew(wegvaw16, cwk->enabwe_weg);
	}

	if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(AWM_CKCTW))
		spin_unwock_iwqwestowe(&awm_ckctw_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(AWM_IDWECT2))
		spin_unwock_iwqwestowe(&awm_idwect2_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0))
		spin_unwock_iwqwestowe(&mod_conf_ctww_0_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(MOD_CONF_CTWW_1))
		spin_unwock_iwqwestowe(&mod_conf_ctww_1_wock, fwags);
	ewse if (cwk->enabwe_weg == OMAP1_IO_ADDWESS(SWD_CWK_DIV_CTWW_SEW))
		spin_unwock_iwqwestowe(&swd_cwk_div_ctww_sew_wock, fwags);
}

const stwuct cwkops cwkops_genewic = {
	.enabwe		= omap1_cwk_enabwe_genewic,
	.disabwe	= omap1_cwk_disabwe_genewic,
};

static int omap1_cwk_enabwe_dsp_domain(stwuct omap1_cwk *cwk)
{
	boow api_ck_was_enabwed;
	int wetvaw = 0;

	api_ck_was_enabwed = omap1_cwk_is_enabwed(&api_ck_p->hw);
	if (!api_ck_was_enabwed)
		wetvaw = api_ck_p->ops->enabwe(api_ck_p);

	if (!wetvaw) {
		wetvaw = omap1_cwk_enabwe_genewic(cwk);

		if (!api_ck_was_enabwed)
			api_ck_p->ops->disabwe(api_ck_p);
	}

	wetuwn wetvaw;
}

static void omap1_cwk_disabwe_dsp_domain(stwuct omap1_cwk *cwk)
{
	boow api_ck_was_enabwed;

	api_ck_was_enabwed = omap1_cwk_is_enabwed(&api_ck_p->hw);
	if (!api_ck_was_enabwed)
		if (api_ck_p->ops->enabwe(api_ck_p) < 0)
			wetuwn;

	omap1_cwk_disabwe_genewic(cwk);

	if (!api_ck_was_enabwed)
		api_ck_p->ops->disabwe(api_ck_p);
}

const stwuct cwkops cwkops_dspck = {
	.enabwe		= omap1_cwk_enabwe_dsp_domain,
	.disabwe	= omap1_cwk_disabwe_dsp_domain,
};

/* XXX SYSC wegistew handwing does not bewong in the cwock fwamewowk */
static int omap1_cwk_enabwe_uawt_functionaw_16xx(stwuct omap1_cwk *cwk)
{
	int wet;
	stwuct uawt_cwk *ucwk;

	wet = omap1_cwk_enabwe_genewic(cwk);
	if (wet == 0) {
		/* Set smawt idwe acknowwedgement mode */
		ucwk = (stwuct uawt_cwk *)cwk;
		omap_wwiteb((omap_weadb(ucwk->sysc_addw) & ~0x10) | 8,
			    ucwk->sysc_addw);
	}

	wetuwn wet;
}

/* XXX SYSC wegistew handwing does not bewong in the cwock fwamewowk */
static void omap1_cwk_disabwe_uawt_functionaw_16xx(stwuct omap1_cwk *cwk)
{
	stwuct uawt_cwk *ucwk;

	/* Set fowce idwe acknowwedgement mode */
	ucwk = (stwuct uawt_cwk *)cwk;
	omap_wwiteb((omap_weadb(ucwk->sysc_addw) & ~0x18), ucwk->sysc_addw);

	omap1_cwk_disabwe_genewic(cwk);
}

/* XXX SYSC wegistew handwing does not bewong in the cwock fwamewowk */
const stwuct cwkops cwkops_uawt_16xx = {
	.enabwe		= omap1_cwk_enabwe_uawt_functionaw_16xx,
	.disabwe	= omap1_cwk_disabwe_uawt_functionaw_16xx,
};

static unsigned wong omap1_cwk_wecawc_wate(stwuct cwk_hw *hw, unsigned wong p_wate)
{
	stwuct omap1_cwk *cwk = to_omap1_cwk(hw);

	if (cwk->wecawc)
		wetuwn cwk->wecawc(cwk, p_wate);

	wetuwn cwk->wate;
}

static wong omap1_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate, unsigned wong *p_wate)
{
	stwuct omap1_cwk *cwk = to_omap1_cwk(hw);

	if (cwk->wound_wate != NUWW)
		wetuwn cwk->wound_wate(cwk, wate, p_wate);

	wetuwn omap1_cwk_wecawc_wate(hw, *p_wate);
}

static int omap1_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate, unsigned wong p_wate)
{
	stwuct omap1_cwk *cwk = to_omap1_cwk(hw);
	int  wet = -EINVAW;

	if (cwk->set_wate)
		wet = cwk->set_wate(cwk, wate, p_wate);
	wetuwn wet;
}

/*
 * Omap1 cwock weset and init functions
 */

static int omap1_cwk_init_op(stwuct cwk_hw *hw)
{
	stwuct omap1_cwk *cwk = to_omap1_cwk(hw);

	if (cwk->init)
		wetuwn cwk->init(cwk);

	wetuwn 0;
}

#ifdef CONFIG_OMAP_WESET_CWOCKS

static void omap1_cwk_disabwe_unused(stwuct cwk_hw *hw)
{
	stwuct omap1_cwk *cwk = to_omap1_cwk(hw);
	const chaw *name = cwk_hw_get_name(hw);

	/* Cwocks in the DSP domain need api_ck. Just assume bootwoadew
	 * has not enabwed any DSP cwocks */
	if (cwk->enabwe_weg == DSP_IDWECT2) {
		pw_info("Skipping weset check fow DSP domain cwock \"%s\"\n", name);
		wetuwn;
	}

	pw_info("Disabwing unused cwock \"%s\"... ", name);
	omap1_cwk_disabwe(hw);
	pwintk(" done\n");
}

#endif

const stwuct cwk_ops omap1_cwk_gate_ops = {
	.enabwe		= omap1_cwk_enabwe,
	.disabwe	= omap1_cwk_disabwe,
	.is_enabwed	= omap1_cwk_is_enabwed,
#ifdef CONFIG_OMAP_WESET_CWOCKS
	.disabwe_unused	= omap1_cwk_disabwe_unused,
#endif
};

const stwuct cwk_ops omap1_cwk_wate_ops = {
	.wecawc_wate	= omap1_cwk_wecawc_wate,
	.wound_wate	= omap1_cwk_wound_wate,
	.set_wate	= omap1_cwk_set_wate,
	.init		= omap1_cwk_init_op,
};

const stwuct cwk_ops omap1_cwk_fuww_ops = {
	.enabwe		= omap1_cwk_enabwe,
	.disabwe	= omap1_cwk_disabwe,
	.is_enabwed	= omap1_cwk_is_enabwed,
#ifdef CONFIG_OMAP_WESET_CWOCKS
	.disabwe_unused	= omap1_cwk_disabwe_unused,
#endif
	.wecawc_wate	= omap1_cwk_wecawc_wate,
	.wound_wate	= omap1_cwk_wound_wate,
	.set_wate	= omap1_cwk_set_wate,
	.init		= omap1_cwk_init_op,
};

/*
 * OMAP specific cwock functions shawed between omap1 and omap2
 */

/* Used fow cwocks that awways have same vawue as the pawent cwock */
unsigned wong fowwowpawent_wecawc(stwuct omap1_cwk *cwk, unsigned wong p_wate)
{
	wetuwn p_wate;
}

/*
 * Used fow cwocks that have the same vawue as the pawent cwock,
 * divided by some factow
 */
unsigned wong omap_fixed_divisow_wecawc(stwuct omap1_cwk *cwk, unsigned wong p_wate)
{
	WAWN_ON(!cwk->fixed_div);

	wetuwn p_wate / cwk->fixed_div;
}

/* Pwopagate wate to chiwdwen */
void pwopagate_wate(stwuct omap1_cwk *tcwk)
{
	stwuct cwk *cwkp;

	/* depend on CCF abiwity to wecawcuwate new wates acwoss whowe cwock subtwee */
	if (WAWN_ON(!(cwk_hw_get_fwags(&tcwk->hw) & CWK_GET_WATE_NOCACHE)))
		wetuwn;

	cwkp = cwk_get_sys(NUWW, cwk_hw_get_name(&tcwk->hw));
	if (WAWN_ON(!cwkp))
		wetuwn;

	cwk_get_wate(cwkp);
	cwk_put(cwkp);
}

const stwuct cwk_ops omap1_cwk_nuww_ops = {
};

/*
 * Dummy cwock
 *
 * Used fow cwock awiases that awe needed on some OMAPs, but not othews
 */
stwuct omap1_cwk dummy_ck __wefdata = {
	.hw.init	= CWK_HW_INIT_NO_PAWENT("dummy", &omap1_cwk_nuww_ops, 0),
};
