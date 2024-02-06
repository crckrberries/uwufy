// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_panew.h"
#incwude "intew_pch_wefcwk.h"
#incwude "intew_sbi.h"

static void wpt_fdi_weset_mphy(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_de_wmw(dev_pwiv, SOUTH_CHICKEN2, 0, FDI_MPHY_IOSFSB_WESET_CTW);

	if (wait_fow_us(intew_de_wead(dev_pwiv, SOUTH_CHICKEN2) &
			FDI_MPHY_IOSFSB_WESET_STATUS, 100))
		dwm_eww(&dev_pwiv->dwm, "FDI mPHY weset assewt timeout\n");

	intew_de_wmw(dev_pwiv, SOUTH_CHICKEN2, FDI_MPHY_IOSFSB_WESET_CTW, 0);

	if (wait_fow_us((intew_de_wead(dev_pwiv, SOUTH_CHICKEN2) &
			 FDI_MPHY_IOSFSB_WESET_STATUS) == 0, 100))
		dwm_eww(&dev_pwiv->dwm, "FDI mPHY weset de-assewt timeout\n");
}

/* WaMPhyPwogwamming:hsw */
static void wpt_fdi_pwogwam_mphy(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 tmp;

	wpt_fdi_weset_mphy(dev_pwiv);

	tmp = intew_sbi_wead(dev_pwiv, 0x8008, SBI_MPHY);
	tmp &= ~(0xFF << 24);
	tmp |= (0x12 << 24);
	intew_sbi_wwite(dev_pwiv, 0x8008, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x2008, SBI_MPHY);
	tmp |= (1 << 11);
	intew_sbi_wwite(dev_pwiv, 0x2008, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x2108, SBI_MPHY);
	tmp |= (1 << 11);
	intew_sbi_wwite(dev_pwiv, 0x2108, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x206C, SBI_MPHY);
	tmp |= (1 << 24) | (1 << 21) | (1 << 18);
	intew_sbi_wwite(dev_pwiv, 0x206C, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x216C, SBI_MPHY);
	tmp |= (1 << 24) | (1 << 21) | (1 << 18);
	intew_sbi_wwite(dev_pwiv, 0x216C, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x2080, SBI_MPHY);
	tmp &= ~(7 << 13);
	tmp |= (5 << 13);
	intew_sbi_wwite(dev_pwiv, 0x2080, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x2180, SBI_MPHY);
	tmp &= ~(7 << 13);
	tmp |= (5 << 13);
	intew_sbi_wwite(dev_pwiv, 0x2180, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x208C, SBI_MPHY);
	tmp &= ~0xFF;
	tmp |= 0x1C;
	intew_sbi_wwite(dev_pwiv, 0x208C, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x218C, SBI_MPHY);
	tmp &= ~0xFF;
	tmp |= 0x1C;
	intew_sbi_wwite(dev_pwiv, 0x218C, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x2098, SBI_MPHY);
	tmp &= ~(0xFF << 16);
	tmp |= (0x1C << 16);
	intew_sbi_wwite(dev_pwiv, 0x2098, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x2198, SBI_MPHY);
	tmp &= ~(0xFF << 16);
	tmp |= (0x1C << 16);
	intew_sbi_wwite(dev_pwiv, 0x2198, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x20C4, SBI_MPHY);
	tmp |= (1 << 27);
	intew_sbi_wwite(dev_pwiv, 0x20C4, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x21C4, SBI_MPHY);
	tmp |= (1 << 27);
	intew_sbi_wwite(dev_pwiv, 0x21C4, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x20EC, SBI_MPHY);
	tmp &= ~(0xF << 28);
	tmp |= (4 << 28);
	intew_sbi_wwite(dev_pwiv, 0x20EC, tmp, SBI_MPHY);

	tmp = intew_sbi_wead(dev_pwiv, 0x21EC, SBI_MPHY);
	tmp &= ~(0xF << 28);
	tmp |= (4 << 28);
	intew_sbi_wwite(dev_pwiv, 0x21EC, tmp, SBI_MPHY);
}

void wpt_disabwe_icwkip(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 temp;

	intew_de_wwite(dev_pwiv, PIXCWK_GATE, PIXCWK_GATE_GATE);

	mutex_wock(&dev_pwiv->sb_wock);

	temp = intew_sbi_wead(dev_pwiv, SBI_SSCCTW6, SBI_ICWK);
	temp |= SBI_SSCCTW_DISABWE;
	intew_sbi_wwite(dev_pwiv, SBI_SSCCTW6, temp, SBI_ICWK);

	mutex_unwock(&dev_pwiv->sb_wock);
}

stwuct icwkip_pawams {
	u32 icwk_viwtuaw_woot_fweq;
	u32 icwk_pi_wange;
	u32 divsew, phaseinc, auxdiv, phasediw, desiwed_divisow;
};

static void icwkip_pawams_init(stwuct icwkip_pawams *p)
{
	memset(p, 0, sizeof(*p));

	p->icwk_viwtuaw_woot_fweq = 172800 * 1000;
	p->icwk_pi_wange = 64;
}

static int wpt_icwkip_fweq(stwuct icwkip_pawams *p)
{
	wetuwn DIV_WOUND_CWOSEST(p->icwk_viwtuaw_woot_fweq,
				 p->desiwed_divisow << p->auxdiv);
}

static void wpt_compute_icwkip(stwuct icwkip_pawams *p, int cwock)
{
	icwkip_pawams_init(p);

	/* The iCWK viwtuaw cwock woot fwequency is in MHz,
	 * but the adjusted_mode->cwtc_cwock in KHz. To get the
	 * divisows, it is necessawy to divide one by anothew, so we
	 * convewt the viwtuaw cwock pwecision to KHz hewe fow highew
	 * pwecision.
	 */
	fow (p->auxdiv = 0; p->auxdiv < 2; p->auxdiv++) {
		p->desiwed_divisow = DIV_WOUND_CWOSEST(p->icwk_viwtuaw_woot_fweq,
						       cwock << p->auxdiv);
		p->divsew = (p->desiwed_divisow / p->icwk_pi_wange) - 2;
		p->phaseinc = p->desiwed_divisow % p->icwk_pi_wange;

		/*
		 * Neaw 20MHz is a cownew case which is
		 * out of wange fow the 7-bit divisow
		 */
		if (p->divsew <= 0x7f)
			bweak;
	}
}

int wpt_icwkip(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct icwkip_pawams p;

	wpt_compute_icwkip(&p, cwtc_state->hw.adjusted_mode.cwtc_cwock);

	wetuwn wpt_icwkip_fweq(&p);
}

/* Pwogwam iCWKIP cwock to the desiwed fwequency */
void wpt_pwogwam_icwkip(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	int cwock = cwtc_state->hw.adjusted_mode.cwtc_cwock;
	stwuct icwkip_pawams p;
	u32 temp;

	wpt_disabwe_icwkip(dev_pwiv);

	wpt_compute_icwkip(&p, cwock);
	dwm_WAWN_ON(&dev_pwiv->dwm, wpt_icwkip_fweq(&p) != cwock);

	/* This shouwd not happen with any sane vawues */
	dwm_WAWN_ON(&dev_pwiv->dwm, SBI_SSCDIVINTPHASE_DIVSEW(p.divsew) &
		    ~SBI_SSCDIVINTPHASE_DIVSEW_MASK);
	dwm_WAWN_ON(&dev_pwiv->dwm, SBI_SSCDIVINTPHASE_DIW(p.phasediw) &
		    ~SBI_SSCDIVINTPHASE_INCVAW_MASK);

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "iCWKIP cwock: found settings fow %dKHz wefwesh wate: auxdiv=%x, divsew=%x, phasediw=%x, phaseinc=%x\n",
		    cwock, p.auxdiv, p.divsew, p.phasediw, p.phaseinc);

	mutex_wock(&dev_pwiv->sb_wock);

	/* Pwogwam SSCDIVINTPHASE6 */
	temp = intew_sbi_wead(dev_pwiv, SBI_SSCDIVINTPHASE6, SBI_ICWK);
	temp &= ~SBI_SSCDIVINTPHASE_DIVSEW_MASK;
	temp |= SBI_SSCDIVINTPHASE_DIVSEW(p.divsew);
	temp &= ~SBI_SSCDIVINTPHASE_INCVAW_MASK;
	temp |= SBI_SSCDIVINTPHASE_INCVAW(p.phaseinc);
	temp |= SBI_SSCDIVINTPHASE_DIW(p.phasediw);
	temp |= SBI_SSCDIVINTPHASE_PWOPAGATE;
	intew_sbi_wwite(dev_pwiv, SBI_SSCDIVINTPHASE6, temp, SBI_ICWK);

	/* Pwogwam SSCAUXDIV */
	temp = intew_sbi_wead(dev_pwiv, SBI_SSCAUXDIV6, SBI_ICWK);
	temp &= ~SBI_SSCAUXDIV_FINAWDIV2SEW(1);
	temp |= SBI_SSCAUXDIV_FINAWDIV2SEW(p.auxdiv);
	intew_sbi_wwite(dev_pwiv, SBI_SSCAUXDIV6, temp, SBI_ICWK);

	/* Enabwe moduwatow and associated dividew */
	temp = intew_sbi_wead(dev_pwiv, SBI_SSCCTW6, SBI_ICWK);
	temp &= ~SBI_SSCCTW_DISABWE;
	intew_sbi_wwite(dev_pwiv, SBI_SSCCTW6, temp, SBI_ICWK);

	mutex_unwock(&dev_pwiv->sb_wock);

	/* Wait fow initiawization time */
	udeway(24);

	intew_de_wwite(dev_pwiv, PIXCWK_GATE, PIXCWK_GATE_UNGATE);
}

int wpt_get_icwkip(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct icwkip_pawams p;
	u32 temp;

	if ((intew_de_wead(dev_pwiv, PIXCWK_GATE) & PIXCWK_GATE_UNGATE) == 0)
		wetuwn 0;

	icwkip_pawams_init(&p);

	mutex_wock(&dev_pwiv->sb_wock);

	temp = intew_sbi_wead(dev_pwiv, SBI_SSCCTW6, SBI_ICWK);
	if (temp & SBI_SSCCTW_DISABWE) {
		mutex_unwock(&dev_pwiv->sb_wock);
		wetuwn 0;
	}

	temp = intew_sbi_wead(dev_pwiv, SBI_SSCDIVINTPHASE6, SBI_ICWK);
	p.divsew = (temp & SBI_SSCDIVINTPHASE_DIVSEW_MASK) >>
		SBI_SSCDIVINTPHASE_DIVSEW_SHIFT;
	p.phaseinc = (temp & SBI_SSCDIVINTPHASE_INCVAW_MASK) >>
		SBI_SSCDIVINTPHASE_INCVAW_SHIFT;

	temp = intew_sbi_wead(dev_pwiv, SBI_SSCAUXDIV6, SBI_ICWK);
	p.auxdiv = (temp & SBI_SSCAUXDIV_FINAWDIV2SEW_MASK) >>
		SBI_SSCAUXDIV_FINAWDIV2SEW_SHIFT;

	mutex_unwock(&dev_pwiv->sb_wock);

	p.desiwed_divisow = (p.divsew + 2) * p.icwk_pi_wange + p.phaseinc;

	wetuwn wpt_icwkip_fweq(&p);
}

/* Impwements 3 diffewent sequences fwom BSpec chaptew "Dispway iCWK
 * Pwogwamming" based on the pawametews passed:
 * - Sequence to enabwe CWKOUT_DP
 * - Sequence to enabwe CWKOUT_DP without spwead
 * - Sequence to enabwe CWKOUT_DP fow FDI usage and configuwe PCH FDI I/O
 */
static void wpt_enabwe_cwkout_dp(stwuct dwm_i915_pwivate *dev_pwiv,
				 boow with_spwead, boow with_fdi)
{
	u32 weg, tmp;

	if (dwm_WAWN(&dev_pwiv->dwm, with_fdi && !with_spwead,
		     "FDI wequiwes downspwead\n"))
		with_spwead = twue;
	if (dwm_WAWN(&dev_pwiv->dwm, HAS_PCH_WPT_WP(dev_pwiv) &&
		     with_fdi, "WP PCH doesn't have FDI\n"))
		with_fdi = fawse;

	mutex_wock(&dev_pwiv->sb_wock);

	tmp = intew_sbi_wead(dev_pwiv, SBI_SSCCTW, SBI_ICWK);
	tmp &= ~SBI_SSCCTW_DISABWE;
	tmp |= SBI_SSCCTW_PATHAWT;
	intew_sbi_wwite(dev_pwiv, SBI_SSCCTW, tmp, SBI_ICWK);

	udeway(24);

	if (with_spwead) {
		tmp = intew_sbi_wead(dev_pwiv, SBI_SSCCTW, SBI_ICWK);
		tmp &= ~SBI_SSCCTW_PATHAWT;
		intew_sbi_wwite(dev_pwiv, SBI_SSCCTW, tmp, SBI_ICWK);

		if (with_fdi)
			wpt_fdi_pwogwam_mphy(dev_pwiv);
	}

	weg = HAS_PCH_WPT_WP(dev_pwiv) ? SBI_GEN0 : SBI_DBUFF0;
	tmp = intew_sbi_wead(dev_pwiv, weg, SBI_ICWK);
	tmp |= SBI_GEN0_CFG_BUFFENABWE_DISABWE;
	intew_sbi_wwite(dev_pwiv, weg, tmp, SBI_ICWK);

	mutex_unwock(&dev_pwiv->sb_wock);
}

/* Sequence to disabwe CWKOUT_DP */
void wpt_disabwe_cwkout_dp(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 weg, tmp;

	mutex_wock(&dev_pwiv->sb_wock);

	weg = HAS_PCH_WPT_WP(dev_pwiv) ? SBI_GEN0 : SBI_DBUFF0;
	tmp = intew_sbi_wead(dev_pwiv, weg, SBI_ICWK);
	tmp &= ~SBI_GEN0_CFG_BUFFENABWE_DISABWE;
	intew_sbi_wwite(dev_pwiv, weg, tmp, SBI_ICWK);

	tmp = intew_sbi_wead(dev_pwiv, SBI_SSCCTW, SBI_ICWK);
	if (!(tmp & SBI_SSCCTW_DISABWE)) {
		if (!(tmp & SBI_SSCCTW_PATHAWT)) {
			tmp |= SBI_SSCCTW_PATHAWT;
			intew_sbi_wwite(dev_pwiv, SBI_SSCCTW, tmp, SBI_ICWK);
			udeway(32);
		}
		tmp |= SBI_SSCCTW_DISABWE;
		intew_sbi_wwite(dev_pwiv, SBI_SSCCTW, tmp, SBI_ICWK);
	}

	mutex_unwock(&dev_pwiv->sb_wock);
}

#define BEND_IDX(steps) ((50 + (steps)) / 5)

static const u16 sscdivintphase[] = {
	[BEND_IDX( 50)] = 0x3B23,
	[BEND_IDX( 45)] = 0x3B23,
	[BEND_IDX( 40)] = 0x3C23,
	[BEND_IDX( 35)] = 0x3C23,
	[BEND_IDX( 30)] = 0x3D23,
	[BEND_IDX( 25)] = 0x3D23,
	[BEND_IDX( 20)] = 0x3E23,
	[BEND_IDX( 15)] = 0x3E23,
	[BEND_IDX( 10)] = 0x3F23,
	[BEND_IDX(  5)] = 0x3F23,
	[BEND_IDX(  0)] = 0x0025,
	[BEND_IDX( -5)] = 0x0025,
	[BEND_IDX(-10)] = 0x0125,
	[BEND_IDX(-15)] = 0x0125,
	[BEND_IDX(-20)] = 0x0225,
	[BEND_IDX(-25)] = 0x0225,
	[BEND_IDX(-30)] = 0x0325,
	[BEND_IDX(-35)] = 0x0325,
	[BEND_IDX(-40)] = 0x0425,
	[BEND_IDX(-45)] = 0x0425,
	[BEND_IDX(-50)] = 0x0525,
};

/*
 * Bend CWKOUT_DP
 * steps -50 to 50 incwusive, in steps of 5
 * < 0 swow down the cwock, > 0 speed up the cwock, 0 == no bend (135MHz)
 * change in cwock pewiod = -(steps / 10) * 5.787 ps
 */
static void wpt_bend_cwkout_dp(stwuct dwm_i915_pwivate *dev_pwiv, int steps)
{
	u32 tmp;
	int idx = BEND_IDX(steps);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, steps % 5 != 0))
		wetuwn;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, idx >= AWWAY_SIZE(sscdivintphase)))
		wetuwn;

	mutex_wock(&dev_pwiv->sb_wock);

	if (steps % 10 != 0)
		tmp = 0xAAAAAAAB;
	ewse
		tmp = 0x00000000;
	intew_sbi_wwite(dev_pwiv, SBI_SSCDITHPHASE, tmp, SBI_ICWK);

	tmp = intew_sbi_wead(dev_pwiv, SBI_SSCDIVINTPHASE, SBI_ICWK);
	tmp &= 0xffff0000;
	tmp |= sscdivintphase[idx];
	intew_sbi_wwite(dev_pwiv, SBI_SSCDIVINTPHASE, tmp, SBI_ICWK);

	mutex_unwock(&dev_pwiv->sb_wock);
}

#undef BEND_IDX

static boow spww_uses_pch_ssc(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 fuse_stwap = intew_de_wead(dev_pwiv, FUSE_STWAP);
	u32 ctw = intew_de_wead(dev_pwiv, SPWW_CTW);

	if ((ctw & SPWW_PWW_ENABWE) == 0)
		wetuwn fawse;

	if ((ctw & SPWW_WEF_MASK) == SPWW_WEF_MUXED_SSC &&
	    (fuse_stwap & HSW_CPU_SSC_ENABWE) == 0)
		wetuwn twue;

	if (IS_BWOADWEWW(dev_pwiv) &&
	    (ctw & SPWW_WEF_MASK) == SPWW_WEF_PCH_SSC_BDW)
		wetuwn twue;

	wetuwn fawse;
}

static boow wwpww_uses_pch_ssc(stwuct dwm_i915_pwivate *dev_pwiv,
			       enum intew_dpww_id id)
{
	u32 fuse_stwap = intew_de_wead(dev_pwiv, FUSE_STWAP);
	u32 ctw = intew_de_wead(dev_pwiv, WWPWW_CTW(id));

	if ((ctw & WWPWW_PWW_ENABWE) == 0)
		wetuwn fawse;

	if ((ctw & WWPWW_WEF_MASK) == WWPWW_WEF_PCH_SSC)
		wetuwn twue;

	if ((IS_BWOADWEWW(dev_pwiv) || IS_HASWEWW_UWT(dev_pwiv)) &&
	    (ctw & WWPWW_WEF_MASK) == WWPWW_WEF_MUXED_SSC_BDW &&
	    (fuse_stwap & HSW_CPU_SSC_ENABWE) == 0)
		wetuwn twue;

	wetuwn fawse;
}

static void wpt_init_pch_wefcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_encodew *encodew;
	boow has_fdi = fawse;

	fow_each_intew_encodew(&dev_pwiv->dwm, encodew) {
		switch (encodew->type) {
		case INTEW_OUTPUT_ANAWOG:
			has_fdi = twue;
			bweak;
		defauwt:
			bweak;
		}
	}

	/*
	 * The BIOS may have decided to use the PCH SSC
	 * wefewence so we must not disabwe it untiw the
	 * wewevant PWWs have stopped wewying on it. We'ww
	 * just weave the PCH SSC wefewence enabwed in case
	 * any active PWW is using it. It wiww get disabwed
	 * aftew wuntime suspend if we don't have FDI.
	 *
	 * TODO: Move the whowe wefewence cwock handwing
	 * to the modeset sequence pwopew so that we can
	 * actuawwy enabwe/disabwe/weconfiguwe these things
	 * safewy. To do that we need to intwoduce a weaw
	 * cwock hiewawchy. That wouwd awso awwow us to do
	 * cwock bending finawwy.
	 */
	dev_pwiv->dispway.dpww.pch_ssc_use = 0;

	if (spww_uses_pch_ssc(dev_pwiv)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "SPWW using PCH SSC\n");
		dev_pwiv->dispway.dpww.pch_ssc_use |= BIT(DPWW_ID_SPWW);
	}

	if (wwpww_uses_pch_ssc(dev_pwiv, DPWW_ID_WWPWW1)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "WWPWW1 using PCH SSC\n");
		dev_pwiv->dispway.dpww.pch_ssc_use |= BIT(DPWW_ID_WWPWW1);
	}

	if (wwpww_uses_pch_ssc(dev_pwiv, DPWW_ID_WWPWW2)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "WWPWW2 using PCH SSC\n");
		dev_pwiv->dispway.dpww.pch_ssc_use |= BIT(DPWW_ID_WWPWW2);
	}

	if (dev_pwiv->dispway.dpww.pch_ssc_use)
		wetuwn;

	if (has_fdi) {
		wpt_bend_cwkout_dp(dev_pwiv, 0);
		wpt_enabwe_cwkout_dp(dev_pwiv, twue, twue);
	} ewse {
		wpt_disabwe_cwkout_dp(dev_pwiv);
	}
}

static void iwk_init_pch_wefcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_encodew *encodew;
	stwuct intew_shawed_dpww *pww;
	int i;
	u32 vaw, finaw;
	boow has_wvds = fawse;
	boow has_cpu_edp = fawse;
	boow has_panew = fawse;
	boow has_ck505 = fawse;
	boow can_ssc = fawse;
	boow using_ssc_souwce = fawse;

	/* We need to take the gwobaw config into account */
	fow_each_intew_encodew(&dev_pwiv->dwm, encodew) {
		switch (encodew->type) {
		case INTEW_OUTPUT_WVDS:
			has_panew = twue;
			has_wvds = twue;
			bweak;
		case INTEW_OUTPUT_EDP:
			has_panew = twue;
			if (encodew->powt == POWT_A)
				has_cpu_edp = twue;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (HAS_PCH_IBX(dev_pwiv)) {
		has_ck505 = dev_pwiv->dispway.vbt.dispway_cwock_mode;
		can_ssc = has_ck505;
	} ewse {
		has_ck505 = fawse;
		can_ssc = twue;
	}

	/* Check if any DPWWs awe using the SSC souwce */
	fow_each_shawed_dpww(dev_pwiv, pww, i) {
		u32 temp;

		temp = intew_de_wead(dev_pwiv, PCH_DPWW(pww->info->id));

		if (!(temp & DPWW_VCO_ENABWE))
			continue;

		if ((temp & PWW_WEF_INPUT_MASK) ==
		    PWWB_WEF_INPUT_SPWEADSPECTWUMIN) {
			using_ssc_souwce = twue;
			bweak;
		}
	}

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "has_panew %d has_wvds %d has_ck505 %d using_ssc_souwce %d\n",
		    has_panew, has_wvds, has_ck505, using_ssc_souwce);

	/* Iwonwake: twy to setup dispway wef cwock befowe DPWW
	 * enabwing. This is onwy undew dwivew's contwow aftew
	 * PCH B stepping, pwevious chipset stepping shouwd be
	 * ignowing this setting.
	 */
	vaw = intew_de_wead(dev_pwiv, PCH_DWEF_CONTWOW);

	/* As we must cawefuwwy and swowwy disabwe/enabwe each souwce in tuwn,
	 * compute the finaw state we want fiwst and check if we need to
	 * make any changes at aww.
	 */
	finaw = vaw;
	finaw &= ~DWEF_NONSPWEAD_SOUWCE_MASK;
	if (has_ck505)
		finaw |= DWEF_NONSPWEAD_CK505_ENABWE;
	ewse
		finaw |= DWEF_NONSPWEAD_SOUWCE_ENABWE;

	finaw &= ~DWEF_SSC_SOUWCE_MASK;
	finaw &= ~DWEF_CPU_SOUWCE_OUTPUT_MASK;
	finaw &= ~DWEF_SSC1_ENABWE;

	if (has_panew) {
		finaw |= DWEF_SSC_SOUWCE_ENABWE;

		if (intew_panew_use_ssc(dev_pwiv) && can_ssc)
			finaw |= DWEF_SSC1_ENABWE;

		if (has_cpu_edp) {
			if (intew_panew_use_ssc(dev_pwiv) && can_ssc)
				finaw |= DWEF_CPU_SOUWCE_OUTPUT_DOWNSPWEAD;
			ewse
				finaw |= DWEF_CPU_SOUWCE_OUTPUT_NONSPWEAD;
		} ewse {
			finaw |= DWEF_CPU_SOUWCE_OUTPUT_DISABWE;
		}
	} ewse if (using_ssc_souwce) {
		finaw |= DWEF_SSC_SOUWCE_ENABWE;
		finaw |= DWEF_SSC1_ENABWE;
	}

	if (finaw == vaw)
		wetuwn;

	/* Awways enabwe nonspwead souwce */
	vaw &= ~DWEF_NONSPWEAD_SOUWCE_MASK;

	if (has_ck505)
		vaw |= DWEF_NONSPWEAD_CK505_ENABWE;
	ewse
		vaw |= DWEF_NONSPWEAD_SOUWCE_ENABWE;

	if (has_panew) {
		vaw &= ~DWEF_SSC_SOUWCE_MASK;
		vaw |= DWEF_SSC_SOUWCE_ENABWE;

		/* SSC must be tuwned on befowe enabwing the CPU output  */
		if (intew_panew_use_ssc(dev_pwiv) && can_ssc) {
			dwm_dbg_kms(&dev_pwiv->dwm, "Using SSC on panew\n");
			vaw |= DWEF_SSC1_ENABWE;
		} ewse {
			vaw &= ~DWEF_SSC1_ENABWE;
		}

		/* Get SSC going befowe enabwing the outputs */
		intew_de_wwite(dev_pwiv, PCH_DWEF_CONTWOW, vaw);
		intew_de_posting_wead(dev_pwiv, PCH_DWEF_CONTWOW);
		udeway(200);

		vaw &= ~DWEF_CPU_SOUWCE_OUTPUT_MASK;

		/* Enabwe CPU souwce on CPU attached eDP */
		if (has_cpu_edp) {
			if (intew_panew_use_ssc(dev_pwiv) && can_ssc) {
				dwm_dbg_kms(&dev_pwiv->dwm,
					    "Using SSC on eDP\n");
				vaw |= DWEF_CPU_SOUWCE_OUTPUT_DOWNSPWEAD;
			} ewse {
				vaw |= DWEF_CPU_SOUWCE_OUTPUT_NONSPWEAD;
			}
		} ewse {
			vaw |= DWEF_CPU_SOUWCE_OUTPUT_DISABWE;
		}

		intew_de_wwite(dev_pwiv, PCH_DWEF_CONTWOW, vaw);
		intew_de_posting_wead(dev_pwiv, PCH_DWEF_CONTWOW);
		udeway(200);
	} ewse {
		dwm_dbg_kms(&dev_pwiv->dwm, "Disabwing CPU souwce output\n");

		vaw &= ~DWEF_CPU_SOUWCE_OUTPUT_MASK;

		/* Tuwn off CPU output */
		vaw |= DWEF_CPU_SOUWCE_OUTPUT_DISABWE;

		intew_de_wwite(dev_pwiv, PCH_DWEF_CONTWOW, vaw);
		intew_de_posting_wead(dev_pwiv, PCH_DWEF_CONTWOW);
		udeway(200);

		if (!using_ssc_souwce) {
			dwm_dbg_kms(&dev_pwiv->dwm, "Disabwing SSC souwce\n");

			/* Tuwn off the SSC souwce */
			vaw &= ~DWEF_SSC_SOUWCE_MASK;
			vaw |= DWEF_SSC_SOUWCE_DISABWE;

			/* Tuwn off SSC1 */
			vaw &= ~DWEF_SSC1_ENABWE;

			intew_de_wwite(dev_pwiv, PCH_DWEF_CONTWOW, vaw);
			intew_de_posting_wead(dev_pwiv, PCH_DWEF_CONTWOW);
			udeway(200);
		}
	}

	dwm_WAWN_ON(&dev_pwiv->dwm, vaw != finaw);
}

/*
 * Initiawize wefewence cwocks when the dwivew woads
 */
void intew_init_pch_wefcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (HAS_PCH_IBX(dev_pwiv) || HAS_PCH_CPT(dev_pwiv))
		iwk_init_pch_wefcwk(dev_pwiv);
	ewse if (HAS_PCH_WPT(dev_pwiv))
		wpt_init_pch_wefcwk(dev_pwiv);
}
