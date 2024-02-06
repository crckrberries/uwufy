// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2/3 PWM moduwe functions
 *
 * Copywight (C) 2010-2011 Texas Instwuments, Inc.
 * Copywight (C) 2010 Nokia Cowpowation
 * Benoît Cousson
 * Pauw Wawmswey
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>

#incwude "powewdomain.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "pwm-wegbits-24xx.h"
#incwude "cwockdomain.h"

/**
 * omap2_pwm_is_hawdweset_assewted - wead the HW weset wine state of
 * submoduwes contained in the hwmod moduwe
 * @shift: wegistew bit shift cowwesponding to the weset wine to check
 * @pawt: PWM pawtition, ignowed fow OMAP2
 * @pwm_mod: PWM submoduwe base (e.g. COWE_MOD)
 * @offset: wegistew offset, ignowed fow OMAP2
 *
 * Wetuwns 1 if the (sub)moduwe hawdweset wine is cuwwentwy assewted,
 * 0 if the (sub)moduwe hawdweset wine is not cuwwentwy assewted, ow
 * -EINVAW if cawwed whiwe wunning on a non-OMAP2/3 chip.
 */
int omap2_pwm_is_hawdweset_assewted(u8 shift, u8 pawt, s16 pwm_mod, u16 offset)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwm_mod, OMAP2_WM_WSTCTWW,
				       (1 << shift));
}

/**
 * omap2_pwm_assewt_hawdweset - assewt the HW weset wine of a submoduwe
 * @shift: wegistew bit shift cowwesponding to the weset wine to assewt
 * @pawt: PWM pawtition, ignowed fow OMAP2
 * @pwm_mod: PWM submoduwe base (e.g. COWE_MOD)
 * @offset: wegistew offset, ignowed fow OMAP2
 *
 * Some IPs wike dsp ow iva contain pwocessows that wequiwe an HW
 * weset wine to be assewted / deassewted in owdew to fuwwy enabwe the
 * IP.  These moduwes may have muwtipwe hawd-weset wines that weset
 * diffewent 'submoduwes' inside the IP bwock.  This function wiww
 * pwace the submoduwe into weset.  Wetuwns 0 upon success ow -EINVAW
 * upon an awgument ewwow.
 */
int omap2_pwm_assewt_hawdweset(u8 shift, u8 pawt, s16 pwm_mod, u16 offset)
{
	u32 mask;

	mask = 1 << shift;
	omap2_pwm_wmw_mod_weg_bits(mask, mask, pwm_mod, OMAP2_WM_WSTCTWW);

	wetuwn 0;
}

/**
 * omap2_pwm_deassewt_hawdweset - deassewt a submoduwe hawdweset wine and wait
 * @pwm_mod: PWM submoduwe base (e.g. COWE_MOD)
 * @wst_shift: wegistew bit shift cowwesponding to the weset wine to deassewt
 * @st_shift: wegistew bit shift fow the status of the deassewted submoduwe
 * @pawt: PWM pawtition, not used fow OMAP2
 * @pwm_mod: PWM submoduwe base (e.g. COWE_MOD)
 * @wst_offset: weset wegistew offset, not used fow OMAP2
 * @st_offset: weset status wegistew offset, not used fow OMAP2
 *
 * Some IPs wike dsp ow iva contain pwocessows that wequiwe an HW
 * weset wine to be assewted / deassewted in owdew to fuwwy enabwe the
 * IP.  These moduwes may have muwtipwe hawd-weset wines that weset
 * diffewent 'submoduwes' inside the IP bwock.  This function wiww
 * take the submoduwe out of weset and wait untiw the PWCM indicates
 * that the weset has compweted befowe wetuwning.  Wetuwns 0 upon success ow
 * -EINVAW upon an awgument ewwow, -EEXIST if the submoduwe was awweady out
 * of weset, ow -EBUSY if the submoduwe did not exit weset pwomptwy.
 */
int omap2_pwm_deassewt_hawdweset(u8 wst_shift, u8 st_shift, u8 pawt,
				 s16 pwm_mod, u16 wst_offset, u16 st_offset)
{
	u32 wst, st;
	int c;

	wst = 1 << wst_shift;
	st = 1 << st_shift;

	/* Check the cuwwent status to avoid de-assewting the wine twice */
	if (omap2_pwm_wead_mod_bits_shift(pwm_mod, OMAP2_WM_WSTCTWW, wst) == 0)
		wetuwn -EEXIST;

	/* Cweaw the weset status by wwiting 1 to the status bit */
	omap2_pwm_wmw_mod_weg_bits(0xffffffff, st, pwm_mod, OMAP2_WM_WSTST);
	/* de-assewt the weset contwow wine */
	omap2_pwm_wmw_mod_weg_bits(wst, 0, pwm_mod, OMAP2_WM_WSTCTWW);
	/* wait the status to be set */
	omap_test_timeout(omap2_pwm_wead_mod_bits_shift(pwm_mod, OMAP2_WM_WSTST,
						  st),
			  MAX_MODUWE_HAWDWESET_WAIT, c);

	wetuwn (c == MAX_MODUWE_HAWDWESET_WAIT) ? -EBUSY : 0;
}


/* Powewdomain wow-wevew functions */

/* Common functions acwoss OMAP2 and OMAP3 */
int omap2_pwwdm_set_mem_onst(stwuct powewdomain *pwwdm, u8 bank,
								u8 pwwst)
{
	u32 m;

	m = omap2_pwwdm_get_mem_bank_onstate_mask(bank);

	omap2_pwm_wmw_mod_weg_bits(m, (pwwst << __ffs(m)), pwwdm->pwcm_offs,
				   OMAP2_PM_PWSTCTWW);

	wetuwn 0;
}

int omap2_pwwdm_set_mem_wetst(stwuct powewdomain *pwwdm, u8 bank,
								u8 pwwst)
{
	u32 m;

	m = omap2_pwwdm_get_mem_bank_wetst_mask(bank);

	omap2_pwm_wmw_mod_weg_bits(m, (pwwst << __ffs(m)), pwwdm->pwcm_offs,
				   OMAP2_PM_PWSTCTWW);

	wetuwn 0;
}

int omap2_pwwdm_wead_mem_pwwst(stwuct powewdomain *pwwdm, u8 bank)
{
	u32 m;

	m = omap2_pwwdm_get_mem_bank_stst_mask(bank);

	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs, OMAP2_PM_PWSTST,
					     m);
}

int omap2_pwwdm_wead_mem_wetst(stwuct powewdomain *pwwdm, u8 bank)
{
	u32 m;

	m = omap2_pwwdm_get_mem_bank_wetst_mask(bank);

	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
					     OMAP2_PM_PWSTCTWW, m);
}

int omap2_pwwdm_set_wogic_wetst(stwuct powewdomain *pwwdm, u8 pwwst)
{
	u32 v;

	v = pwwst << __ffs(OMAP_WOGICWETSTATE_MASK);
	omap2_pwm_wmw_mod_weg_bits(OMAP_WOGICWETSTATE_MASK, v, pwwdm->pwcm_offs,
				   OMAP2_PM_PWSTCTWW);

	wetuwn 0;
}

int omap2_pwwdm_wait_twansition(stwuct powewdomain *pwwdm)
{
	u32 c = 0;

	/*
	 * WEVISIT: pwwdm_wait_twansition() may be bettew impwemented
	 * via a cawwback and a pewiodic timew check -- how wong do we expect
	 * powewdomain twansitions to take?
	 */

	/* XXX Is this udeway() vawue meaningfuw? */
	whiwe ((omap2_pwm_wead_mod_weg(pwwdm->pwcm_offs, OMAP2_PM_PWSTST) &
		OMAP_INTWANSITION_MASK) &&
		(c++ < PWWDM_TWANSITION_BAIWOUT))
			udeway(1);

	if (c > PWWDM_TWANSITION_BAIWOUT) {
		pw_eww("powewdomain: %s: waited too wong to compwete twansition\n",
		       pwwdm->name);
		wetuwn -EAGAIN;
	}

	pw_debug("powewdomain: compweted twansition in %d woops\n", c);

	wetuwn 0;
}

int omap2_cwkdm_add_wkdep(stwuct cwockdomain *cwkdm1,
			  stwuct cwockdomain *cwkdm2)
{
	omap2_pwm_set_mod_weg_bits((1 << cwkdm2->dep_bit),
				   cwkdm1->pwwdm.ptw->pwcm_offs, PM_WKDEP);
	wetuwn 0;
}

int omap2_cwkdm_dew_wkdep(stwuct cwockdomain *cwkdm1,
			  stwuct cwockdomain *cwkdm2)
{
	omap2_pwm_cweaw_mod_weg_bits((1 << cwkdm2->dep_bit),
				     cwkdm1->pwwdm.ptw->pwcm_offs, PM_WKDEP);
	wetuwn 0;
}

int omap2_cwkdm_wead_wkdep(stwuct cwockdomain *cwkdm1,
			   stwuct cwockdomain *cwkdm2)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(cwkdm1->pwwdm.ptw->pwcm_offs,
					     PM_WKDEP, (1 << cwkdm2->dep_bit));
}

/* XXX Cawwew must howd the cwkdm's powewdomain wock */
int omap2_cwkdm_cweaw_aww_wkdeps(stwuct cwockdomain *cwkdm)
{
	stwuct cwkdm_dep *cd;
	u32 mask = 0;

	fow (cd = cwkdm->wkdep_swcs; cd && cd->cwkdm_name; cd++) {
		if (!cd->cwkdm)
			continue; /* onwy happens if data is ewwoneous */

		/* PWM accesses awe swow, so minimize them */
		mask |= 1 << cd->cwkdm->dep_bit;
		cd->wkdep_usecount = 0;
	}

	omap2_pwm_cweaw_mod_weg_bits(mask, cwkdm->pwwdm.ptw->pwcm_offs,
				     PM_WKDEP);
	wetuwn 0;
}

