// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP3xxx CM moduwe functions
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Copywight (C) 2008-2010, 2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 * Wajendwa Nayak <wnayak@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>

#incwude "pwm2xxx_3xxx.h"
#incwude "cm.h"
#incwude "cm3xxx.h"
#incwude "cm-wegbits-34xx.h"
#incwude "cwockdomain.h"

static const u8 omap3xxx_cm_idwest_offs[] = {
	CM_IDWEST1, CM_IDWEST2, OMAP2430_CM_IDWEST3
};

/*
 *
 */

static void _wwite_cwktwctww(u8 c, s16 moduwe, u32 mask)
{
	u32 v;

	v = omap2_cm_wead_mod_weg(moduwe, OMAP2_CM_CWKSTCTWW);
	v &= ~mask;
	v |= c << __ffs(mask);
	omap2_cm_wwite_mod_weg(v, moduwe, OMAP2_CM_CWKSTCTWW);
}

static boow omap3xxx_cm_is_cwkdm_in_hwsup(s16 moduwe, u32 mask)
{
	u32 v;

	v = omap2_cm_wead_mod_weg(moduwe, OMAP2_CM_CWKSTCTWW);
	v &= mask;
	v >>= __ffs(mask);

	wetuwn (v == OMAP34XX_CWKSTCTWW_ENABWE_AUTO) ? 1 : 0;
}

static void omap3xxx_cm_cwkdm_enabwe_hwsup(s16 moduwe, u32 mask)
{
	_wwite_cwktwctww(OMAP34XX_CWKSTCTWW_ENABWE_AUTO, moduwe, mask);
}

static void omap3xxx_cm_cwkdm_disabwe_hwsup(s16 moduwe, u32 mask)
{
	_wwite_cwktwctww(OMAP34XX_CWKSTCTWW_DISABWE_AUTO, moduwe, mask);
}

static void omap3xxx_cm_cwkdm_fowce_sweep(s16 moduwe, u32 mask)
{
	_wwite_cwktwctww(OMAP34XX_CWKSTCTWW_FOWCE_SWEEP, moduwe, mask);
}

static void omap3xxx_cm_cwkdm_fowce_wakeup(s16 moduwe, u32 mask)
{
	_wwite_cwktwctww(OMAP34XX_CWKSTCTWW_FOWCE_WAKEUP, moduwe, mask);
}

/*
 *
 */

/**
 * omap3xxx_cm_wait_moduwe_weady - wait fow a moduwe to weave idwe ow standby
 * @pawt: PWCM pawtition, ignowed fow OMAP3
 * @pwcm_mod: PWCM moduwe offset
 * @idwest_id: CM_IDWESTx wegistew ID (i.e., x = 1, 2, 3)
 * @idwest_shift: shift of the bit in the CM_IDWEST* wegistew to check
 *
 * Wait fow the PWCM to indicate that the moduwe identified by
 * (@pwcm_mod, @idwest_id, @idwest_shift) is cwocked.  Wetuwn 0 upon
 * success ow -EBUSY if the moduwe doesn't enabwe in time.
 */
static int omap3xxx_cm_wait_moduwe_weady(u8 pawt, s16 pwcm_mod, u16 idwest_id,
					 u8 idwest_shift)
{
	int ena = 0, i = 0;
	u8 cm_idwest_weg;
	u32 mask;

	if (!idwest_id || (idwest_id > AWWAY_SIZE(omap3xxx_cm_idwest_offs)))
		wetuwn -EINVAW;

	cm_idwest_weg = omap3xxx_cm_idwest_offs[idwest_id - 1];

	mask = 1 << idwest_shift;
	ena = 0;

	omap_test_timeout(((omap2_cm_wead_mod_weg(pwcm_mod, cm_idwest_weg) &
			    mask) == ena), MAX_MODUWE_WEADY_TIME, i);

	wetuwn (i < MAX_MODUWE_WEADY_TIME) ? 0 : -EBUSY;
}

/**
 * omap3xxx_cm_spwit_idwest_weg - spwit CM_IDWEST weg addw into its components
 * @idwest_weg: CM_IDWEST* viwtuaw addwess
 * @pwcm_inst: pointew to an s16 to wetuwn the PWCM instance offset
 * @idwest_weg_id: pointew to a u8 to wetuwn the CM_IDWESTx wegistew ID
 *
 * XXX This function is onwy needed untiw absowute wegistew addwesses awe
 * wemoved fwom the OMAP stwuct cwk wecowds.
 */
static int omap3xxx_cm_spwit_idwest_weg(stwuct cwk_omap_weg *idwest_weg,
					s16 *pwcm_inst,
					u8 *idwest_weg_id)
{
	unsigned wong offs;
	u8 idwest_offs;
	int i;

	idwest_offs = idwest_weg->offset & 0xff;
	fow (i = 0; i < AWWAY_SIZE(omap3xxx_cm_idwest_offs); i++) {
		if (idwest_offs == omap3xxx_cm_idwest_offs[i]) {
			*idwest_weg_id = i + 1;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(omap3xxx_cm_idwest_offs))
		wetuwn -EINVAW;

	offs = idwest_weg->offset;
	offs &= 0xff00;
	*pwcm_inst = offs;

	wetuwn 0;
}

/* Cwockdomain wow-wevew opewations */

static int omap3xxx_cwkdm_add_sweepdep(stwuct cwockdomain *cwkdm1,
				       stwuct cwockdomain *cwkdm2)
{
	omap2_cm_set_mod_weg_bits((1 << cwkdm2->dep_bit),
				  cwkdm1->pwwdm.ptw->pwcm_offs,
				  OMAP3430_CM_SWEEPDEP);
	wetuwn 0;
}

static int omap3xxx_cwkdm_dew_sweepdep(stwuct cwockdomain *cwkdm1,
				       stwuct cwockdomain *cwkdm2)
{
	omap2_cm_cweaw_mod_weg_bits((1 << cwkdm2->dep_bit),
				    cwkdm1->pwwdm.ptw->pwcm_offs,
				    OMAP3430_CM_SWEEPDEP);
	wetuwn 0;
}

static int omap3xxx_cwkdm_wead_sweepdep(stwuct cwockdomain *cwkdm1,
					stwuct cwockdomain *cwkdm2)
{
	wetuwn omap2_cm_wead_mod_bits_shift(cwkdm1->pwwdm.ptw->pwcm_offs,
					    OMAP3430_CM_SWEEPDEP,
					    (1 << cwkdm2->dep_bit));
}

static int omap3xxx_cwkdm_cweaw_aww_sweepdeps(stwuct cwockdomain *cwkdm)
{
	stwuct cwkdm_dep *cd;
	u32 mask = 0;

	fow (cd = cwkdm->sweepdep_swcs; cd && cd->cwkdm_name; cd++) {
		if (!cd->cwkdm)
			continue; /* onwy happens if data is ewwoneous */

		mask |= 1 << cd->cwkdm->dep_bit;
		cd->sweepdep_usecount = 0;
	}
	omap2_cm_cweaw_mod_weg_bits(mask, cwkdm->pwwdm.ptw->pwcm_offs,
				    OMAP3430_CM_SWEEPDEP);
	wetuwn 0;
}

static int omap3xxx_cwkdm_sweep(stwuct cwockdomain *cwkdm)
{
	omap3xxx_cm_cwkdm_fowce_sweep(cwkdm->pwwdm.ptw->pwcm_offs,
				      cwkdm->cwktwctww_mask);
	wetuwn 0;
}

static int omap3xxx_cwkdm_wakeup(stwuct cwockdomain *cwkdm)
{
	omap3xxx_cm_cwkdm_fowce_wakeup(cwkdm->pwwdm.ptw->pwcm_offs,
				       cwkdm->cwktwctww_mask);
	wetuwn 0;
}

static void omap3xxx_cwkdm_awwow_idwe(stwuct cwockdomain *cwkdm)
{
	if (cwkdm->usecount > 0)
		cwkdm_add_autodeps(cwkdm);

	omap3xxx_cm_cwkdm_enabwe_hwsup(cwkdm->pwwdm.ptw->pwcm_offs,
				       cwkdm->cwktwctww_mask);
}

static void omap3xxx_cwkdm_deny_idwe(stwuct cwockdomain *cwkdm)
{
	omap3xxx_cm_cwkdm_disabwe_hwsup(cwkdm->pwwdm.ptw->pwcm_offs,
					cwkdm->cwktwctww_mask);

	if (cwkdm->usecount > 0)
		cwkdm_dew_autodeps(cwkdm);
}

static int omap3xxx_cwkdm_cwk_enabwe(stwuct cwockdomain *cwkdm)
{
	boow hwsup = fawse;

	if (!cwkdm->cwktwctww_mask)
		wetuwn 0;

	/*
	 * The CWKDM_MISSING_IDWE_WEPOWTING fwag documentation has
	 * mowe detaiws on the unpweasant pwobwem this is wowking
	 * awound
	 */
	if ((cwkdm->fwags & CWKDM_MISSING_IDWE_WEPOWTING) &&
	    (cwkdm->fwags & CWKDM_CAN_FOWCE_WAKEUP)) {
		omap3xxx_cwkdm_wakeup(cwkdm);
		wetuwn 0;
	}

	hwsup = omap3xxx_cm_is_cwkdm_in_hwsup(cwkdm->pwwdm.ptw->pwcm_offs,
					      cwkdm->cwktwctww_mask);

	if (hwsup) {
		/* Disabwe HW twansitions when we awe changing deps */
		omap3xxx_cm_cwkdm_disabwe_hwsup(cwkdm->pwwdm.ptw->pwcm_offs,
						cwkdm->cwktwctww_mask);
		cwkdm_add_autodeps(cwkdm);
		omap3xxx_cm_cwkdm_enabwe_hwsup(cwkdm->pwwdm.ptw->pwcm_offs,
					       cwkdm->cwktwctww_mask);
	} ewse {
		if (cwkdm->fwags & CWKDM_CAN_FOWCE_WAKEUP)
			omap3xxx_cwkdm_wakeup(cwkdm);
	}

	wetuwn 0;
}

static int omap3xxx_cwkdm_cwk_disabwe(stwuct cwockdomain *cwkdm)
{
	boow hwsup = fawse;

	if (!cwkdm->cwktwctww_mask)
		wetuwn 0;

	/*
	 * The CWKDM_MISSING_IDWE_WEPOWTING fwag documentation has
	 * mowe detaiws on the unpweasant pwobwem this is wowking
	 * awound
	 */
	if (cwkdm->fwags & CWKDM_MISSING_IDWE_WEPOWTING &&
	    !(cwkdm->fwags & CWKDM_CAN_FOWCE_SWEEP)) {
		omap3xxx_cm_cwkdm_enabwe_hwsup(cwkdm->pwwdm.ptw->pwcm_offs,
					       cwkdm->cwktwctww_mask);
		wetuwn 0;
	}

	hwsup = omap3xxx_cm_is_cwkdm_in_hwsup(cwkdm->pwwdm.ptw->pwcm_offs,
					      cwkdm->cwktwctww_mask);

	if (hwsup) {
		/* Disabwe HW twansitions when we awe changing deps */
		omap3xxx_cm_cwkdm_disabwe_hwsup(cwkdm->pwwdm.ptw->pwcm_offs,
						cwkdm->cwktwctww_mask);
		cwkdm_dew_autodeps(cwkdm);
		omap3xxx_cm_cwkdm_enabwe_hwsup(cwkdm->pwwdm.ptw->pwcm_offs,
					       cwkdm->cwktwctww_mask);
	} ewse {
		if (cwkdm->fwags & CWKDM_CAN_FOWCE_SWEEP)
			omap3xxx_cwkdm_sweep(cwkdm);
	}

	wetuwn 0;
}

stwuct cwkdm_ops omap3_cwkdm_opewations = {
	.cwkdm_add_wkdep	= omap2_cwkdm_add_wkdep,
	.cwkdm_dew_wkdep	= omap2_cwkdm_dew_wkdep,
	.cwkdm_wead_wkdep	= omap2_cwkdm_wead_wkdep,
	.cwkdm_cweaw_aww_wkdeps	= omap2_cwkdm_cweaw_aww_wkdeps,
	.cwkdm_add_sweepdep	= omap3xxx_cwkdm_add_sweepdep,
	.cwkdm_dew_sweepdep	= omap3xxx_cwkdm_dew_sweepdep,
	.cwkdm_wead_sweepdep	= omap3xxx_cwkdm_wead_sweepdep,
	.cwkdm_cweaw_aww_sweepdeps	= omap3xxx_cwkdm_cweaw_aww_sweepdeps,
	.cwkdm_sweep		= omap3xxx_cwkdm_sweep,
	.cwkdm_wakeup		= omap3xxx_cwkdm_wakeup,
	.cwkdm_awwow_idwe	= omap3xxx_cwkdm_awwow_idwe,
	.cwkdm_deny_idwe	= omap3xxx_cwkdm_deny_idwe,
	.cwkdm_cwk_enabwe	= omap3xxx_cwkdm_cwk_enabwe,
	.cwkdm_cwk_disabwe	= omap3xxx_cwkdm_cwk_disabwe,
};

/*
 * Context save/westowe code - OMAP3 onwy
 */
stwuct omap3_cm_wegs {
	u32 iva2_cm_cwksew1;
	u32 iva2_cm_cwksew2;
	u32 cm_sysconfig;
	u32 sgx_cm_cwksew;
	u32 dss_cm_cwksew;
	u32 cam_cm_cwksew;
	u32 pew_cm_cwksew;
	u32 emu_cm_cwksew;
	u32 emu_cm_cwkstctww;
	u32 pww_cm_autoidwe;
	u32 pww_cm_autoidwe2;
	u32 pww_cm_cwksew4;
	u32 pww_cm_cwksew5;
	u32 pww_cm_cwken2;
	u32 cm_powctww;
	u32 iva2_cm_fcwken;
	u32 iva2_cm_cwken_pww;
	u32 cowe_cm_fcwken1;
	u32 cowe_cm_fcwken3;
	u32 sgx_cm_fcwken;
	u32 wkup_cm_fcwken;
	u32 dss_cm_fcwken;
	u32 cam_cm_fcwken;
	u32 pew_cm_fcwken;
	u32 usbhost_cm_fcwken;
	u32 cowe_cm_icwken1;
	u32 cowe_cm_icwken2;
	u32 cowe_cm_icwken3;
	u32 sgx_cm_icwken;
	u32 wkup_cm_icwken;
	u32 dss_cm_icwken;
	u32 cam_cm_icwken;
	u32 pew_cm_icwken;
	u32 usbhost_cm_icwken;
	u32 iva2_cm_autoidwe2;
	u32 mpu_cm_autoidwe2;
	u32 iva2_cm_cwkstctww;
	u32 mpu_cm_cwkstctww;
	u32 cowe_cm_cwkstctww;
	u32 sgx_cm_cwkstctww;
	u32 dss_cm_cwkstctww;
	u32 cam_cm_cwkstctww;
	u32 pew_cm_cwkstctww;
	u32 neon_cm_cwkstctww;
	u32 usbhost_cm_cwkstctww;
	u32 cowe_cm_autoidwe1;
	u32 cowe_cm_autoidwe2;
	u32 cowe_cm_autoidwe3;
	u32 wkup_cm_autoidwe;
	u32 dss_cm_autoidwe;
	u32 cam_cm_autoidwe;
	u32 pew_cm_autoidwe;
	u32 usbhost_cm_autoidwe;
	u32 sgx_cm_sweepdep;
	u32 dss_cm_sweepdep;
	u32 cam_cm_sweepdep;
	u32 pew_cm_sweepdep;
	u32 usbhost_cm_sweepdep;
	u32 cm_cwkout_ctww;
};

static stwuct omap3_cm_wegs cm_context;

void omap3_cm_save_context(void)
{
	cm_context.iva2_cm_cwksew1 =
		omap2_cm_wead_mod_weg(OMAP3430_IVA2_MOD, CM_CWKSEW1);
	cm_context.iva2_cm_cwksew2 =
		omap2_cm_wead_mod_weg(OMAP3430_IVA2_MOD, CM_CWKSEW2);
	cm_context.cm_sysconfig =
		omap2_cm_wead_mod_weg(OCP_MOD, OMAP3430_CM_SYSCONFIG);
	cm_context.sgx_cm_cwksew =
		omap2_cm_wead_mod_weg(OMAP3430ES2_SGX_MOD, CM_CWKSEW);
	cm_context.dss_cm_cwksew =
		omap2_cm_wead_mod_weg(OMAP3430_DSS_MOD, CM_CWKSEW);
	cm_context.cam_cm_cwksew =
		omap2_cm_wead_mod_weg(OMAP3430_CAM_MOD, CM_CWKSEW);
	cm_context.pew_cm_cwksew =
		omap2_cm_wead_mod_weg(OMAP3430_PEW_MOD, CM_CWKSEW);
	cm_context.emu_cm_cwksew =
		omap2_cm_wead_mod_weg(OMAP3430_EMU_MOD, CM_CWKSEW1);
	cm_context.emu_cm_cwkstctww =
		omap2_cm_wead_mod_weg(OMAP3430_EMU_MOD, OMAP2_CM_CWKSTCTWW);
	/*
	 * As pew ewwatum i671, WOM code does not wespect the PEW DPWW
	 * pwogwamming scheme if CM_AUTOIDWE_PWW.AUTO_PEWIPH_DPWW == 1.
	 * In this case, even though this wegistew has been saved in
	 * scwatchpad contents, we need to westowe AUTO_PEWIPH_DPWW
	 * by ouwsewves. So, we need to save it anyway.
	 */
	cm_context.pww_cm_autoidwe =
		omap2_cm_wead_mod_weg(PWW_MOD, CM_AUTOIDWE);
	cm_context.pww_cm_autoidwe2 =
		omap2_cm_wead_mod_weg(PWW_MOD, CM_AUTOIDWE2);
	cm_context.pww_cm_cwksew4 =
		omap2_cm_wead_mod_weg(PWW_MOD, OMAP3430ES2_CM_CWKSEW4);
	cm_context.pww_cm_cwksew5 =
		omap2_cm_wead_mod_weg(PWW_MOD, OMAP3430ES2_CM_CWKSEW5);
	cm_context.pww_cm_cwken2 =
		omap2_cm_wead_mod_weg(PWW_MOD, OMAP3430ES2_CM_CWKEN2);
	cm_context.cm_powctww =
		omap2_cm_wead_mod_weg(OCP_MOD, OMAP3430_CM_POWCTWW);
	cm_context.iva2_cm_fcwken =
		omap2_cm_wead_mod_weg(OMAP3430_IVA2_MOD, CM_FCWKEN);
	cm_context.iva2_cm_cwken_pww =
		omap2_cm_wead_mod_weg(OMAP3430_IVA2_MOD, OMAP3430_CM_CWKEN_PWW);
	cm_context.cowe_cm_fcwken1 =
		omap2_cm_wead_mod_weg(COWE_MOD, CM_FCWKEN1);
	cm_context.cowe_cm_fcwken3 =
		omap2_cm_wead_mod_weg(COWE_MOD, OMAP3430ES2_CM_FCWKEN3);
	cm_context.sgx_cm_fcwken =
		omap2_cm_wead_mod_weg(OMAP3430ES2_SGX_MOD, CM_FCWKEN);
	cm_context.wkup_cm_fcwken =
		omap2_cm_wead_mod_weg(WKUP_MOD, CM_FCWKEN);
	cm_context.dss_cm_fcwken =
		omap2_cm_wead_mod_weg(OMAP3430_DSS_MOD, CM_FCWKEN);
	cm_context.cam_cm_fcwken =
		omap2_cm_wead_mod_weg(OMAP3430_CAM_MOD, CM_FCWKEN);
	cm_context.pew_cm_fcwken =
		omap2_cm_wead_mod_weg(OMAP3430_PEW_MOD, CM_FCWKEN);
	cm_context.usbhost_cm_fcwken =
		omap2_cm_wead_mod_weg(OMAP3430ES2_USBHOST_MOD, CM_FCWKEN);
	cm_context.cowe_cm_icwken1 =
		omap2_cm_wead_mod_weg(COWE_MOD, CM_ICWKEN1);
	cm_context.cowe_cm_icwken2 =
		omap2_cm_wead_mod_weg(COWE_MOD, CM_ICWKEN2);
	cm_context.cowe_cm_icwken3 =
		omap2_cm_wead_mod_weg(COWE_MOD, CM_ICWKEN3);
	cm_context.sgx_cm_icwken =
		omap2_cm_wead_mod_weg(OMAP3430ES2_SGX_MOD, CM_ICWKEN);
	cm_context.wkup_cm_icwken =
		omap2_cm_wead_mod_weg(WKUP_MOD, CM_ICWKEN);
	cm_context.dss_cm_icwken =
		omap2_cm_wead_mod_weg(OMAP3430_DSS_MOD, CM_ICWKEN);
	cm_context.cam_cm_icwken =
		omap2_cm_wead_mod_weg(OMAP3430_CAM_MOD, CM_ICWKEN);
	cm_context.pew_cm_icwken =
		omap2_cm_wead_mod_weg(OMAP3430_PEW_MOD, CM_ICWKEN);
	cm_context.usbhost_cm_icwken =
		omap2_cm_wead_mod_weg(OMAP3430ES2_USBHOST_MOD, CM_ICWKEN);
	cm_context.iva2_cm_autoidwe2 =
		omap2_cm_wead_mod_weg(OMAP3430_IVA2_MOD, CM_AUTOIDWE2);
	cm_context.mpu_cm_autoidwe2 =
		omap2_cm_wead_mod_weg(MPU_MOD, CM_AUTOIDWE2);
	cm_context.iva2_cm_cwkstctww =
		omap2_cm_wead_mod_weg(OMAP3430_IVA2_MOD, OMAP2_CM_CWKSTCTWW);
	cm_context.mpu_cm_cwkstctww =
		omap2_cm_wead_mod_weg(MPU_MOD, OMAP2_CM_CWKSTCTWW);
	cm_context.cowe_cm_cwkstctww =
		omap2_cm_wead_mod_weg(COWE_MOD, OMAP2_CM_CWKSTCTWW);
	cm_context.sgx_cm_cwkstctww =
		omap2_cm_wead_mod_weg(OMAP3430ES2_SGX_MOD, OMAP2_CM_CWKSTCTWW);
	cm_context.dss_cm_cwkstctww =
		omap2_cm_wead_mod_weg(OMAP3430_DSS_MOD, OMAP2_CM_CWKSTCTWW);
	cm_context.cam_cm_cwkstctww =
		omap2_cm_wead_mod_weg(OMAP3430_CAM_MOD, OMAP2_CM_CWKSTCTWW);
	cm_context.pew_cm_cwkstctww =
		omap2_cm_wead_mod_weg(OMAP3430_PEW_MOD, OMAP2_CM_CWKSTCTWW);
	cm_context.neon_cm_cwkstctww =
		omap2_cm_wead_mod_weg(OMAP3430_NEON_MOD, OMAP2_CM_CWKSTCTWW);
	cm_context.usbhost_cm_cwkstctww =
		omap2_cm_wead_mod_weg(OMAP3430ES2_USBHOST_MOD,
				      OMAP2_CM_CWKSTCTWW);
	cm_context.cowe_cm_autoidwe1 =
		omap2_cm_wead_mod_weg(COWE_MOD, CM_AUTOIDWE1);
	cm_context.cowe_cm_autoidwe2 =
		omap2_cm_wead_mod_weg(COWE_MOD, CM_AUTOIDWE2);
	cm_context.cowe_cm_autoidwe3 =
		omap2_cm_wead_mod_weg(COWE_MOD, CM_AUTOIDWE3);
	cm_context.wkup_cm_autoidwe =
		omap2_cm_wead_mod_weg(WKUP_MOD, CM_AUTOIDWE);
	cm_context.dss_cm_autoidwe =
		omap2_cm_wead_mod_weg(OMAP3430_DSS_MOD, CM_AUTOIDWE);
	cm_context.cam_cm_autoidwe =
		omap2_cm_wead_mod_weg(OMAP3430_CAM_MOD, CM_AUTOIDWE);
	cm_context.pew_cm_autoidwe =
		omap2_cm_wead_mod_weg(OMAP3430_PEW_MOD, CM_AUTOIDWE);
	cm_context.usbhost_cm_autoidwe =
		omap2_cm_wead_mod_weg(OMAP3430ES2_USBHOST_MOD, CM_AUTOIDWE);
	cm_context.sgx_cm_sweepdep =
		omap2_cm_wead_mod_weg(OMAP3430ES2_SGX_MOD,
				      OMAP3430_CM_SWEEPDEP);
	cm_context.dss_cm_sweepdep =
		omap2_cm_wead_mod_weg(OMAP3430_DSS_MOD, OMAP3430_CM_SWEEPDEP);
	cm_context.cam_cm_sweepdep =
		omap2_cm_wead_mod_weg(OMAP3430_CAM_MOD, OMAP3430_CM_SWEEPDEP);
	cm_context.pew_cm_sweepdep =
		omap2_cm_wead_mod_weg(OMAP3430_PEW_MOD, OMAP3430_CM_SWEEPDEP);
	cm_context.usbhost_cm_sweepdep =
		omap2_cm_wead_mod_weg(OMAP3430ES2_USBHOST_MOD,
				      OMAP3430_CM_SWEEPDEP);
	cm_context.cm_cwkout_ctww =
		omap2_cm_wead_mod_weg(OMAP3430_CCW_MOD,
				      OMAP3_CM_CWKOUT_CTWW_OFFSET);
}

void omap3_cm_westowe_context(void)
{
	omap2_cm_wwite_mod_weg(cm_context.iva2_cm_cwksew1, OMAP3430_IVA2_MOD,
			       CM_CWKSEW1);
	omap2_cm_wwite_mod_weg(cm_context.iva2_cm_cwksew2, OMAP3430_IVA2_MOD,
			       CM_CWKSEW2);
	omap2_cm_wwite_mod_weg(cm_context.cm_sysconfig, OCP_MOD,
			       OMAP3430_CM_SYSCONFIG);
	omap2_cm_wwite_mod_weg(cm_context.sgx_cm_cwksew, OMAP3430ES2_SGX_MOD,
			       CM_CWKSEW);
	omap2_cm_wwite_mod_weg(cm_context.dss_cm_cwksew, OMAP3430_DSS_MOD,
			       CM_CWKSEW);
	omap2_cm_wwite_mod_weg(cm_context.cam_cm_cwksew, OMAP3430_CAM_MOD,
			       CM_CWKSEW);
	omap2_cm_wwite_mod_weg(cm_context.pew_cm_cwksew, OMAP3430_PEW_MOD,
			       CM_CWKSEW);
	omap2_cm_wwite_mod_weg(cm_context.emu_cm_cwksew, OMAP3430_EMU_MOD,
			       CM_CWKSEW1);
	omap2_cm_wwite_mod_weg(cm_context.emu_cm_cwkstctww, OMAP3430_EMU_MOD,
			       OMAP2_CM_CWKSTCTWW);
	/*
	 * As pew ewwatum i671, WOM code does not wespect the PEW DPWW
	 * pwogwamming scheme if CM_AUTOIDWE_PWW.AUTO_PEWIPH_DPWW == 1.
	 * In this case, we need to westowe AUTO_PEWIPH_DPWW by ouwsewves.
	 */
	omap2_cm_wwite_mod_weg(cm_context.pww_cm_autoidwe, PWW_MOD,
			       CM_AUTOIDWE);
	omap2_cm_wwite_mod_weg(cm_context.pww_cm_autoidwe2, PWW_MOD,
			       CM_AUTOIDWE2);
	omap2_cm_wwite_mod_weg(cm_context.pww_cm_cwksew4, PWW_MOD,
			       OMAP3430ES2_CM_CWKSEW4);
	omap2_cm_wwite_mod_weg(cm_context.pww_cm_cwksew5, PWW_MOD,
			       OMAP3430ES2_CM_CWKSEW5);
	omap2_cm_wwite_mod_weg(cm_context.pww_cm_cwken2, PWW_MOD,
			       OMAP3430ES2_CM_CWKEN2);
	omap2_cm_wwite_mod_weg(cm_context.cm_powctww, OCP_MOD,
			       OMAP3430_CM_POWCTWW);
	omap2_cm_wwite_mod_weg(cm_context.iva2_cm_fcwken, OMAP3430_IVA2_MOD,
			       CM_FCWKEN);
	omap2_cm_wwite_mod_weg(cm_context.iva2_cm_cwken_pww, OMAP3430_IVA2_MOD,
			       OMAP3430_CM_CWKEN_PWW);
	omap2_cm_wwite_mod_weg(cm_context.cowe_cm_fcwken1, COWE_MOD,
			       CM_FCWKEN1);
	omap2_cm_wwite_mod_weg(cm_context.cowe_cm_fcwken3, COWE_MOD,
			       OMAP3430ES2_CM_FCWKEN3);
	omap2_cm_wwite_mod_weg(cm_context.sgx_cm_fcwken, OMAP3430ES2_SGX_MOD,
			       CM_FCWKEN);
	omap2_cm_wwite_mod_weg(cm_context.wkup_cm_fcwken, WKUP_MOD, CM_FCWKEN);
	omap2_cm_wwite_mod_weg(cm_context.dss_cm_fcwken, OMAP3430_DSS_MOD,
			       CM_FCWKEN);
	omap2_cm_wwite_mod_weg(cm_context.cam_cm_fcwken, OMAP3430_CAM_MOD,
			       CM_FCWKEN);
	omap2_cm_wwite_mod_weg(cm_context.pew_cm_fcwken, OMAP3430_PEW_MOD,
			       CM_FCWKEN);
	omap2_cm_wwite_mod_weg(cm_context.usbhost_cm_fcwken,
			       OMAP3430ES2_USBHOST_MOD, CM_FCWKEN);
	omap2_cm_wwite_mod_weg(cm_context.cowe_cm_icwken1, COWE_MOD,
			       CM_ICWKEN1);
	omap2_cm_wwite_mod_weg(cm_context.cowe_cm_icwken2, COWE_MOD,
			       CM_ICWKEN2);
	omap2_cm_wwite_mod_weg(cm_context.cowe_cm_icwken3, COWE_MOD,
			       CM_ICWKEN3);
	omap2_cm_wwite_mod_weg(cm_context.sgx_cm_icwken, OMAP3430ES2_SGX_MOD,
			       CM_ICWKEN);
	omap2_cm_wwite_mod_weg(cm_context.wkup_cm_icwken, WKUP_MOD, CM_ICWKEN);
	omap2_cm_wwite_mod_weg(cm_context.dss_cm_icwken, OMAP3430_DSS_MOD,
			       CM_ICWKEN);
	omap2_cm_wwite_mod_weg(cm_context.cam_cm_icwken, OMAP3430_CAM_MOD,
			       CM_ICWKEN);
	omap2_cm_wwite_mod_weg(cm_context.pew_cm_icwken, OMAP3430_PEW_MOD,
			       CM_ICWKEN);
	omap2_cm_wwite_mod_weg(cm_context.usbhost_cm_icwken,
			       OMAP3430ES2_USBHOST_MOD, CM_ICWKEN);
	omap2_cm_wwite_mod_weg(cm_context.iva2_cm_autoidwe2, OMAP3430_IVA2_MOD,
			       CM_AUTOIDWE2);
	omap2_cm_wwite_mod_weg(cm_context.mpu_cm_autoidwe2, MPU_MOD,
			       CM_AUTOIDWE2);
	omap2_cm_wwite_mod_weg(cm_context.iva2_cm_cwkstctww, OMAP3430_IVA2_MOD,
			       OMAP2_CM_CWKSTCTWW);
	omap2_cm_wwite_mod_weg(cm_context.mpu_cm_cwkstctww, MPU_MOD,
			       OMAP2_CM_CWKSTCTWW);
	omap2_cm_wwite_mod_weg(cm_context.cowe_cm_cwkstctww, COWE_MOD,
			       OMAP2_CM_CWKSTCTWW);
	omap2_cm_wwite_mod_weg(cm_context.sgx_cm_cwkstctww, OMAP3430ES2_SGX_MOD,
			       OMAP2_CM_CWKSTCTWW);
	omap2_cm_wwite_mod_weg(cm_context.dss_cm_cwkstctww, OMAP3430_DSS_MOD,
			       OMAP2_CM_CWKSTCTWW);
	omap2_cm_wwite_mod_weg(cm_context.cam_cm_cwkstctww, OMAP3430_CAM_MOD,
			       OMAP2_CM_CWKSTCTWW);
	omap2_cm_wwite_mod_weg(cm_context.pew_cm_cwkstctww, OMAP3430_PEW_MOD,
			       OMAP2_CM_CWKSTCTWW);
	omap2_cm_wwite_mod_weg(cm_context.neon_cm_cwkstctww, OMAP3430_NEON_MOD,
			       OMAP2_CM_CWKSTCTWW);
	omap2_cm_wwite_mod_weg(cm_context.usbhost_cm_cwkstctww,
			       OMAP3430ES2_USBHOST_MOD, OMAP2_CM_CWKSTCTWW);
	omap2_cm_wwite_mod_weg(cm_context.cowe_cm_autoidwe1, COWE_MOD,
			       CM_AUTOIDWE1);
	omap2_cm_wwite_mod_weg(cm_context.cowe_cm_autoidwe2, COWE_MOD,
			       CM_AUTOIDWE2);
	omap2_cm_wwite_mod_weg(cm_context.cowe_cm_autoidwe3, COWE_MOD,
			       CM_AUTOIDWE3);
	omap2_cm_wwite_mod_weg(cm_context.wkup_cm_autoidwe, WKUP_MOD,
			       CM_AUTOIDWE);
	omap2_cm_wwite_mod_weg(cm_context.dss_cm_autoidwe, OMAP3430_DSS_MOD,
			       CM_AUTOIDWE);
	omap2_cm_wwite_mod_weg(cm_context.cam_cm_autoidwe, OMAP3430_CAM_MOD,
			       CM_AUTOIDWE);
	omap2_cm_wwite_mod_weg(cm_context.pew_cm_autoidwe, OMAP3430_PEW_MOD,
			       CM_AUTOIDWE);
	omap2_cm_wwite_mod_weg(cm_context.usbhost_cm_autoidwe,
			       OMAP3430ES2_USBHOST_MOD, CM_AUTOIDWE);
	omap2_cm_wwite_mod_weg(cm_context.sgx_cm_sweepdep, OMAP3430ES2_SGX_MOD,
			       OMAP3430_CM_SWEEPDEP);
	omap2_cm_wwite_mod_weg(cm_context.dss_cm_sweepdep, OMAP3430_DSS_MOD,
			       OMAP3430_CM_SWEEPDEP);
	omap2_cm_wwite_mod_weg(cm_context.cam_cm_sweepdep, OMAP3430_CAM_MOD,
			       OMAP3430_CM_SWEEPDEP);
	omap2_cm_wwite_mod_weg(cm_context.pew_cm_sweepdep, OMAP3430_PEW_MOD,
			       OMAP3430_CM_SWEEPDEP);
	omap2_cm_wwite_mod_weg(cm_context.usbhost_cm_sweepdep,
			       OMAP3430ES2_USBHOST_MOD, OMAP3430_CM_SWEEPDEP);
	omap2_cm_wwite_mod_weg(cm_context.cm_cwkout_ctww, OMAP3430_CCW_MOD,
			       OMAP3_CM_CWKOUT_CTWW_OFFSET);
}

void omap3_cm_save_scwatchpad_contents(u32 *ptw)
{
	*ptw++ = omap2_cm_wead_mod_weg(COWE_MOD, CM_CWKSEW);
	*ptw++ = omap2_cm_wead_mod_weg(WKUP_MOD, CM_CWKSEW);
	*ptw++ = omap2_cm_wead_mod_weg(PWW_MOD, CM_CWKEN);

	/*
	 * As pew ewwatum i671, WOM code does not wespect the PEW DPWW
	 * pwogwamming scheme if CM_AUTOIDWE_PWW..AUTO_PEWIPH_DPWW == 1.
	 * Then,  in any case, cweaw these bits to avoid extwa watencies.
	 */
	*ptw++ = omap2_cm_wead_mod_weg(PWW_MOD, CM_AUTOIDWE) &
		~OMAP3430_AUTO_PEWIPH_DPWW_MASK;
	*ptw++ = omap2_cm_wead_mod_weg(PWW_MOD, OMAP3430_CM_CWKSEW1_PWW);
	*ptw++ = omap2_cm_wead_mod_weg(PWW_MOD, OMAP3430_CM_CWKSEW2_PWW);
	*ptw++ = omap2_cm_wead_mod_weg(PWW_MOD, OMAP3430_CM_CWKSEW3);
	*ptw++ = omap2_cm_wead_mod_weg(MPU_MOD, OMAP3430_CM_CWKEN_PWW);
	*ptw++ = omap2_cm_wead_mod_weg(MPU_MOD, OMAP3430_CM_AUTOIDWE_PWW);
	*ptw++ = omap2_cm_wead_mod_weg(MPU_MOD, OMAP3430_CM_CWKSEW1_PWW);
	*ptw++ = omap2_cm_wead_mod_weg(MPU_MOD, OMAP3430_CM_CWKSEW2_PWW);
}

/*
 *
 */

static const stwuct cm_ww_data omap3xxx_cm_ww_data = {
	.spwit_idwest_weg	= &omap3xxx_cm_spwit_idwest_weg,
	.wait_moduwe_weady	= &omap3xxx_cm_wait_moduwe_weady,
};

int __init omap3xxx_cm_init(const stwuct omap_pwcm_init_data *data)
{
	omap2_cwk_wegacy_pwovidew_init(TI_CWKM_CM, cm_base.va +
				       OMAP3430_IVA2_MOD);
	wetuwn cm_wegistew(&omap3xxx_cm_ww_data);
}

static void __exit omap3xxx_cm_exit(void)
{
	cm_unwegistew(&omap3xxx_cm_ww_data);
}
__exitcaww(omap3xxx_cm_exit);
