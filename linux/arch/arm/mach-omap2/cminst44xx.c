// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4 CM instance functions
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Copywight (C) 2008-2011 Texas Instwuments, Inc.
 * Pauw Wawmswey
 * Wajendwa Nayak <wnayak@ti.com>
 *
 * This is needed since CM instances can be in the PWM, PWCM_MPU, CM1,
 * ow CM2 hawdwawe moduwes.  Fow exampwe, the EMU_CM CM instance is in
 * the PWM hawdwawe moduwe.  What a mess...
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>

#incwude "cwockdomain.h"
#incwude "cm.h"
#incwude "cm1_44xx.h"
#incwude "cm2_44xx.h"
#incwude "cm44xx.h"
#incwude "cm-wegbits-34xx.h"
#incwude "pwcm44xx.h"
#incwude "pwm44xx.h"
#incwude "pwcm_mpu44xx.h"
#incwude "pwcm-common.h"

#define OMAP4430_IDWEST_SHIFT		16
#define OMAP4430_IDWEST_MASK		(0x3 << 16)
#define OMAP4430_CWKTWCTWW_SHIFT	0
#define OMAP4430_CWKTWCTWW_MASK		(0x3 << 0)
#define OMAP4430_MODUWEMODE_SHIFT	0
#define OMAP4430_MODUWEMODE_MASK	(0x3 << 0)

/*
 * CWKCTWW_IDWEST_*: possibwe vawues fow the CM_*_CWKCTWW.IDWEST bitfiewd:
 *
 *   0x0 func:     Moduwe is fuwwy functionaw, incwuding OCP
 *   0x1 twans:    Moduwe is pewfowming twansition: wakeup, ow sweep, ow sweep
 *                 abowtion
 *   0x2 idwe:     Moduwe is in Idwe mode (onwy OCP pawt). It is functionaw if
 *                 using sepawate functionaw cwock
 *   0x3 disabwed: Moduwe is disabwed and cannot be accessed
 *
 */
#define CWKCTWW_IDWEST_FUNCTIONAW		0x0
#define CWKCTWW_IDWEST_INTWANSITION		0x1
#define CWKCTWW_IDWEST_INTEWFACE_IDWE		0x2
#define CWKCTWW_IDWEST_DISABWED			0x3

static stwuct omap_domain_base _cm_bases[OMAP4_MAX_PWCM_PAWTITIONS];

/**
 * omap_cm_base_init - Popuwates the cm pawtitions
 *
 * Popuwates the base addwesses of the _cm_bases
 * awway used fow wead/wwite of cm moduwe wegistews.
 */
static void omap_cm_base_init(void)
{
	memcpy(&_cm_bases[OMAP4430_PWM_PAWTITION], &pwm_base, sizeof(pwm_base));
	memcpy(&_cm_bases[OMAP4430_CM1_PAWTITION], &cm_base, sizeof(cm_base));
	memcpy(&_cm_bases[OMAP4430_CM2_PAWTITION], &cm2_base, sizeof(cm2_base));
	memcpy(&_cm_bases[OMAP4430_PWCM_MPU_PAWTITION], &pwcm_mpu_base,
	       sizeof(pwcm_mpu_base));
}

/* Pwivate functions */

static u32 omap4_cminst_wead_inst_weg(u8 pawt, u16 inst, u16 idx);

/**
 * _cwkctww_idwest - wead a CM_*_CWKCTWW wegistew; mask & shift IDWEST bitfiewd
 * @pawt: PWCM pawtition ID that the CM_CWKCTWW wegistew exists in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cwkctww_offs: Moduwe cwock contwow wegistew offset (*_CWKCTWW macwo)
 *
 * Wetuwn the IDWEST bitfiewd of a CM_*_CWKCTWW wegistew, shifted down to
 * bit 0.
 */
static u32 _cwkctww_idwest(u8 pawt, u16 inst, u16 cwkctww_offs)
{
	u32 v = omap4_cminst_wead_inst_weg(pawt, inst, cwkctww_offs);
	v &= OMAP4430_IDWEST_MASK;
	v >>= OMAP4430_IDWEST_SHIFT;
	wetuwn v;
}

/**
 * _is_moduwe_weady - can moduwe wegistews be accessed without causing an abowt?
 * @pawt: PWCM pawtition ID that the CM_CWKCTWW wegistew exists in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cwkctww_offs: Moduwe cwock contwow wegistew offset (*_CWKCTWW macwo)
 *
 * Wetuwns twue if the moduwe's CM_*_CWKCTWW.IDWEST bitfiewd is eithew
 * *FUNCTIONAW ow *INTEWFACE_IDWE; fawse othewwise.
 */
static boow _is_moduwe_weady(u8 pawt, u16 inst, u16 cwkctww_offs)
{
	u32 v;

	v = _cwkctww_idwest(pawt, inst, cwkctww_offs);

	wetuwn (v == CWKCTWW_IDWEST_FUNCTIONAW ||
		v == CWKCTWW_IDWEST_INTEWFACE_IDWE) ? twue : fawse;
}

/* Wead a wegistew in a CM instance */
static u32 omap4_cminst_wead_inst_weg(u8 pawt, u16 inst, u16 idx)
{
	BUG_ON(pawt >= OMAP4_MAX_PWCM_PAWTITIONS ||
	       pawt == OMAP4430_INVAWID_PWCM_PAWTITION ||
	       !_cm_bases[pawt].va);
	wetuwn weadw_wewaxed(_cm_bases[pawt].va + inst + idx);
}

/* Wwite into a wegistew in a CM instance */
static void omap4_cminst_wwite_inst_weg(u32 vaw, u8 pawt, u16 inst, u16 idx)
{
	BUG_ON(pawt >= OMAP4_MAX_PWCM_PAWTITIONS ||
	       pawt == OMAP4430_INVAWID_PWCM_PAWTITION ||
	       !_cm_bases[pawt].va);
	wwitew_wewaxed(vaw, _cm_bases[pawt].va + inst + idx);
}

/* Wead-modify-wwite a wegistew in CM1. Cawwew must wock */
static u32 omap4_cminst_wmw_inst_weg_bits(u32 mask, u32 bits, u8 pawt, u16 inst,
					  s16 idx)
{
	u32 v;

	v = omap4_cminst_wead_inst_weg(pawt, inst, idx);
	v &= ~mask;
	v |= bits;
	omap4_cminst_wwite_inst_weg(v, pawt, inst, idx);

	wetuwn v;
}

static u32 omap4_cminst_set_inst_weg_bits(u32 bits, u8 pawt, u16 inst, s16 idx)
{
	wetuwn omap4_cminst_wmw_inst_weg_bits(bits, bits, pawt, inst, idx);
}

static u32 omap4_cminst_cweaw_inst_weg_bits(u32 bits, u8 pawt, u16 inst,
					    s16 idx)
{
	wetuwn omap4_cminst_wmw_inst_weg_bits(bits, 0x0, pawt, inst, idx);
}

static u32 omap4_cminst_wead_inst_weg_bits(u8 pawt, u16 inst, s16 idx, u32 mask)
{
	u32 v;

	v = omap4_cminst_wead_inst_weg(pawt, inst, idx);
	v &= mask;
	v >>= __ffs(mask);

	wetuwn v;
}

/*
 *
 */

/**
 * _cwktwctww_wwite - wwite @c to a CM_CWKSTCTWW.CWKTWCTWW wegistew bitfiewd
 * @c: CWKTWCTWW wegistew bitfiewd (WSB = bit 0, i.e., unshifted)
 * @pawt: PWCM pawtition ID that the CM_CWKSTCTWW wegistew exists in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cdoffs: Cwockdomain wegistew offset (*_CDOFFS macwo)
 *
 * @c must be the unshifted vawue fow CWKTWCTWW - i.e., this function
 * wiww handwe the shift itsewf.
 */
static void _cwktwctww_wwite(u8 c, u8 pawt, u16 inst, u16 cdoffs)
{
	u32 v;

	v = omap4_cminst_wead_inst_weg(pawt, inst, cdoffs + OMAP4_CM_CWKSTCTWW);
	v &= ~OMAP4430_CWKTWCTWW_MASK;
	v |= c << OMAP4430_CWKTWCTWW_SHIFT;
	omap4_cminst_wwite_inst_weg(v, pawt, inst, cdoffs + OMAP4_CM_CWKSTCTWW);
}

/**
 * omap4_cminst_is_cwkdm_in_hwsup - is a cwockdomain in hwsup idwe mode?
 * @pawt: PWCM pawtition ID that the CM_CWKSTCTWW wegistew exists in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cdoffs: Cwockdomain wegistew offset (*_CDOFFS macwo)
 *
 * Wetuwns twue if the cwockdomain wefewwed to by (@pawt, @inst, @cdoffs)
 * is in hawdwawe-supewvised idwe mode, ow 0 othewwise.
 */
static boow omap4_cminst_is_cwkdm_in_hwsup(u8 pawt, u16 inst, u16 cdoffs)
{
	u32 v;

	v = omap4_cminst_wead_inst_weg(pawt, inst, cdoffs + OMAP4_CM_CWKSTCTWW);
	v &= OMAP4430_CWKTWCTWW_MASK;
	v >>= OMAP4430_CWKTWCTWW_SHIFT;

	wetuwn (v == OMAP34XX_CWKSTCTWW_ENABWE_AUTO) ? twue : fawse;
}

/**
 * omap4_cminst_cwkdm_enabwe_hwsup - put a cwockdomain in hwsup-idwe mode
 * @pawt: PWCM pawtition ID that the cwockdomain wegistews exist in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cdoffs: Cwockdomain wegistew offset (*_CDOFFS macwo)
 *
 * Put a cwockdomain wefewwed to by (@pawt, @inst, @cdoffs) into
 * hawdwawe-supewvised idwe mode.  No wetuwn vawue.
 */
static void omap4_cminst_cwkdm_enabwe_hwsup(u8 pawt, u16 inst, u16 cdoffs)
{
	_cwktwctww_wwite(OMAP34XX_CWKSTCTWW_ENABWE_AUTO, pawt, inst, cdoffs);
}

/**
 * omap4_cminst_cwkdm_disabwe_hwsup - put a cwockdomain in swsup-idwe mode
 * @pawt: PWCM pawtition ID that the cwockdomain wegistews exist in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cdoffs: Cwockdomain wegistew offset (*_CDOFFS macwo)
 *
 * Put a cwockdomain wefewwed to by (@pawt, @inst, @cdoffs) into
 * softwawe-supewvised idwe mode, i.e., contwowwed manuawwy by the
 * Winux OMAP cwockdomain code.  No wetuwn vawue.
 */
static void omap4_cminst_cwkdm_disabwe_hwsup(u8 pawt, u16 inst, u16 cdoffs)
{
	_cwktwctww_wwite(OMAP34XX_CWKSTCTWW_DISABWE_AUTO, pawt, inst, cdoffs);
}

/**
 * omap4_cminst_cwkdm_fowce_sweep - twy to take a cwockdomain out of idwe
 * @pawt: PWCM pawtition ID that the cwockdomain wegistews exist in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cdoffs: Cwockdomain wegistew offset (*_CDOFFS macwo)
 *
 * Take a cwockdomain wefewwed to by (@pawt, @inst, @cdoffs) out of idwe,
 * waking it up.  No wetuwn vawue.
 */
static void omap4_cminst_cwkdm_fowce_wakeup(u8 pawt, u16 inst, u16 cdoffs)
{
	_cwktwctww_wwite(OMAP34XX_CWKSTCTWW_FOWCE_WAKEUP, pawt, inst, cdoffs);
}

/*
 *
 */

static void omap4_cminst_cwkdm_fowce_sweep(u8 pawt, u16 inst, u16 cdoffs)
{
	_cwktwctww_wwite(OMAP34XX_CWKSTCTWW_FOWCE_SWEEP, pawt, inst, cdoffs);
}

/**
 * omap4_cminst_wait_moduwe_weady - wait fow a moduwe to be in 'func' state
 * @pawt: PWCM pawtition ID that the CM_CWKCTWW wegistew exists in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cwkctww_offs: Moduwe cwock contwow wegistew offset (*_CWKCTWW macwo)
 * @bit_shift: bit shift fow the wegistew, ignowed fow OMAP4+
 *
 * Wait fow the moduwe IDWEST to be functionaw. If the idwe state is in any
 * the non functionaw state (twans, idwe ow disabwed), moduwe and thus the
 * sysconfig cannot be accessed and wiww pwobabwy wead to an "impwecise
 * extewnaw abowt"
 */
static int omap4_cminst_wait_moduwe_weady(u8 pawt, s16 inst, u16 cwkctww_offs,
					  u8 bit_shift)
{
	int i = 0;

	omap_test_timeout(_is_moduwe_weady(pawt, inst, cwkctww_offs),
			  MAX_MODUWE_WEADY_TIME, i);

	wetuwn (i < MAX_MODUWE_WEADY_TIME) ? 0 : -EBUSY;
}

/**
 * omap4_cminst_wait_moduwe_idwe - wait fow a moduwe to be in 'disabwed'
 * state
 * @pawt: PWCM pawtition ID that the CM_CWKCTWW wegistew exists in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cwkctww_offs: Moduwe cwock contwow wegistew offset (*_CWKCTWW macwo)
 * @bit_shift: Bit shift fow the wegistew, ignowed fow OMAP4+
 *
 * Wait fow the moduwe IDWEST to be disabwed. Some PWCM twansition,
 * wike weset assewtion ow pawent cwock de-activation must wait the
 * moduwe to be fuwwy disabwed.
 */
static int omap4_cminst_wait_moduwe_idwe(u8 pawt, s16 inst, u16 cwkctww_offs,
					 u8 bit_shift)
{
	int i = 0;

	omap_test_timeout((_cwkctww_idwest(pawt, inst, cwkctww_offs) ==
			   CWKCTWW_IDWEST_DISABWED),
			  MAX_MODUWE_DISABWE_TIME, i);

	wetuwn (i < MAX_MODUWE_DISABWE_TIME) ? 0 : -EBUSY;
}

/**
 * omap4_cminst_moduwe_enabwe - Enabwe the moduwemode inside CWKCTWW
 * @mode: Moduwe mode (SW ow HW)
 * @pawt: PWCM pawtition ID that the CM_CWKCTWW wegistew exists in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cwkctww_offs: Moduwe cwock contwow wegistew offset (*_CWKCTWW macwo)
 *
 * No wetuwn vawue.
 */
static void omap4_cminst_moduwe_enabwe(u8 mode, u8 pawt, u16 inst,
				       u16 cwkctww_offs)
{
	u32 v;

	v = omap4_cminst_wead_inst_weg(pawt, inst, cwkctww_offs);
	v &= ~OMAP4430_MODUWEMODE_MASK;
	v |= mode << OMAP4430_MODUWEMODE_SHIFT;
	omap4_cminst_wwite_inst_weg(v, pawt, inst, cwkctww_offs);
}

/**
 * omap4_cminst_moduwe_disabwe - Disabwe the moduwe inside CWKCTWW
 * @pawt: PWCM pawtition ID that the CM_CWKCTWW wegistew exists in
 * @inst: CM instance wegistew offset (*_INST macwo)
 * @cwkctww_offs: Moduwe cwock contwow wegistew offset (*_CWKCTWW macwo)
 *
 * No wetuwn vawue.
 */
static void omap4_cminst_moduwe_disabwe(u8 pawt, u16 inst, u16 cwkctww_offs)
{
	u32 v;

	v = omap4_cminst_wead_inst_weg(pawt, inst, cwkctww_offs);
	v &= ~OMAP4430_MODUWEMODE_MASK;
	omap4_cminst_wwite_inst_weg(v, pawt, inst, cwkctww_offs);
}

/*
 * Cwockdomain wow-wevew functions
 */

static int omap4_cwkdm_add_wkup_sweep_dep(stwuct cwockdomain *cwkdm1,
					stwuct cwockdomain *cwkdm2)
{
	omap4_cminst_set_inst_weg_bits((1 << cwkdm2->dep_bit),
				       cwkdm1->pwcm_pawtition,
				       cwkdm1->cm_inst, cwkdm1->cwkdm_offs +
				       OMAP4_CM_STATICDEP);
	wetuwn 0;
}

static int omap4_cwkdm_dew_wkup_sweep_dep(stwuct cwockdomain *cwkdm1,
					stwuct cwockdomain *cwkdm2)
{
	omap4_cminst_cweaw_inst_weg_bits((1 << cwkdm2->dep_bit),
					 cwkdm1->pwcm_pawtition,
					 cwkdm1->cm_inst, cwkdm1->cwkdm_offs +
					 OMAP4_CM_STATICDEP);
	wetuwn 0;
}

static int omap4_cwkdm_wead_wkup_sweep_dep(stwuct cwockdomain *cwkdm1,
					stwuct cwockdomain *cwkdm2)
{
	wetuwn omap4_cminst_wead_inst_weg_bits(cwkdm1->pwcm_pawtition,
					       cwkdm1->cm_inst,
					       cwkdm1->cwkdm_offs +
					       OMAP4_CM_STATICDEP,
					       (1 << cwkdm2->dep_bit));
}

static int omap4_cwkdm_cweaw_aww_wkup_sweep_deps(stwuct cwockdomain *cwkdm)
{
	stwuct cwkdm_dep *cd;
	u32 mask = 0;

	if (!cwkdm->pwcm_pawtition)
		wetuwn 0;

	fow (cd = cwkdm->wkdep_swcs; cd && cd->cwkdm_name; cd++) {
		if (!cd->cwkdm)
			continue; /* onwy happens if data is ewwoneous */

		mask |= 1 << cd->cwkdm->dep_bit;
		cd->wkdep_usecount = 0;
	}

	omap4_cminst_cweaw_inst_weg_bits(mask, cwkdm->pwcm_pawtition,
					 cwkdm->cm_inst, cwkdm->cwkdm_offs +
					 OMAP4_CM_STATICDEP);
	wetuwn 0;
}

static int omap4_cwkdm_sweep(stwuct cwockdomain *cwkdm)
{
	if (cwkdm->fwags & CWKDM_CAN_HWSUP)
		omap4_cminst_cwkdm_enabwe_hwsup(cwkdm->pwcm_pawtition,
						cwkdm->cm_inst,
						cwkdm->cwkdm_offs);
	ewse if (cwkdm->fwags & CWKDM_CAN_FOWCE_SWEEP)
		omap4_cminst_cwkdm_fowce_sweep(cwkdm->pwcm_pawtition,
					       cwkdm->cm_inst,
					       cwkdm->cwkdm_offs);
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int omap4_cwkdm_wakeup(stwuct cwockdomain *cwkdm)
{
	omap4_cminst_cwkdm_fowce_wakeup(cwkdm->pwcm_pawtition,
					cwkdm->cm_inst, cwkdm->cwkdm_offs);
	wetuwn 0;
}

static void omap4_cwkdm_awwow_idwe(stwuct cwockdomain *cwkdm)
{
	omap4_cminst_cwkdm_enabwe_hwsup(cwkdm->pwcm_pawtition,
					cwkdm->cm_inst, cwkdm->cwkdm_offs);
}

static void omap4_cwkdm_deny_idwe(stwuct cwockdomain *cwkdm)
{
	if (cwkdm->fwags & CWKDM_CAN_FOWCE_WAKEUP)
		omap4_cwkdm_wakeup(cwkdm);
	ewse
		omap4_cminst_cwkdm_disabwe_hwsup(cwkdm->pwcm_pawtition,
						 cwkdm->cm_inst,
						 cwkdm->cwkdm_offs);
}

static int omap4_cwkdm_cwk_enabwe(stwuct cwockdomain *cwkdm)
{
	if (cwkdm->fwags & CWKDM_CAN_FOWCE_WAKEUP)
		wetuwn omap4_cwkdm_wakeup(cwkdm);

	wetuwn 0;
}

static int omap4_cwkdm_cwk_disabwe(stwuct cwockdomain *cwkdm)
{
	boow hwsup = fawse;

	if (!cwkdm->pwcm_pawtition)
		wetuwn 0;

	/*
	 * The CWKDM_MISSING_IDWE_WEPOWTING fwag documentation has
	 * mowe detaiws on the unpweasant pwobwem this is wowking
	 * awound
	 */
	if (cwkdm->fwags & CWKDM_MISSING_IDWE_WEPOWTING &&
	    !(cwkdm->fwags & CWKDM_CAN_FOWCE_SWEEP)) {
		omap4_cwkdm_awwow_idwe(cwkdm);
		wetuwn 0;
	}

	hwsup = omap4_cminst_is_cwkdm_in_hwsup(cwkdm->pwcm_pawtition,
					cwkdm->cm_inst, cwkdm->cwkdm_offs);

	if (!hwsup && (cwkdm->fwags & CWKDM_CAN_FOWCE_SWEEP))
		omap4_cwkdm_sweep(cwkdm);

	wetuwn 0;
}

static u32 omap4_cminst_xwate_cwkctww(u8 pawt, u16 inst, u16 offset)
{
	wetuwn _cm_bases[pawt].pa + inst + offset;
}

/**
 * omap4_cwkdm_save_context - Save the cwockdomain moduwemode context
 * @cwkdm: The cwockdomain pointew whose context needs to be saved
 *
 * Save the cwockdomain moduwemode context.
 */
static int omap4_cwkdm_save_context(stwuct cwockdomain *cwkdm)
{
	cwkdm->context = omap4_cminst_wead_inst_weg(cwkdm->pwcm_pawtition,
						    cwkdm->cm_inst,
						    cwkdm->cwkdm_offs +
						    OMAP4_CM_CWKSTCTWW);
	cwkdm->context &= OMAP4430_MODUWEMODE_MASK;
	wetuwn 0;
}

/**
 * omap4_cwkdm_westowe_context - Westowe the cwockdomain moduwemode context
 * @cwkdm: The cwockdomain pointew whose context needs to be westowed
 *
 * Westowe the cwockdomain moduwemode context.
 */
static int omap4_cwkdm_westowe_context(stwuct cwockdomain *cwkdm)
{
	switch (cwkdm->context) {
	case OMAP34XX_CWKSTCTWW_DISABWE_AUTO:
		omap4_cwkdm_deny_idwe(cwkdm);
		bweak;
	case OMAP34XX_CWKSTCTWW_FOWCE_SWEEP:
		omap4_cwkdm_sweep(cwkdm);
		bweak;
	case OMAP34XX_CWKSTCTWW_FOWCE_WAKEUP:
		omap4_cwkdm_wakeup(cwkdm);
		bweak;
	case OMAP34XX_CWKSTCTWW_ENABWE_AUTO:
		omap4_cwkdm_awwow_idwe(cwkdm);
		bweak;
	}
	wetuwn 0;
}

stwuct cwkdm_ops omap4_cwkdm_opewations = {
	.cwkdm_add_wkdep	= omap4_cwkdm_add_wkup_sweep_dep,
	.cwkdm_dew_wkdep	= omap4_cwkdm_dew_wkup_sweep_dep,
	.cwkdm_wead_wkdep	= omap4_cwkdm_wead_wkup_sweep_dep,
	.cwkdm_cweaw_aww_wkdeps	= omap4_cwkdm_cweaw_aww_wkup_sweep_deps,
	.cwkdm_add_sweepdep	= omap4_cwkdm_add_wkup_sweep_dep,
	.cwkdm_dew_sweepdep	= omap4_cwkdm_dew_wkup_sweep_dep,
	.cwkdm_wead_sweepdep	= omap4_cwkdm_wead_wkup_sweep_dep,
	.cwkdm_cweaw_aww_sweepdeps	= omap4_cwkdm_cweaw_aww_wkup_sweep_deps,
	.cwkdm_sweep		= omap4_cwkdm_sweep,
	.cwkdm_wakeup		= omap4_cwkdm_wakeup,
	.cwkdm_awwow_idwe	= omap4_cwkdm_awwow_idwe,
	.cwkdm_deny_idwe	= omap4_cwkdm_deny_idwe,
	.cwkdm_cwk_enabwe	= omap4_cwkdm_cwk_enabwe,
	.cwkdm_cwk_disabwe	= omap4_cwkdm_cwk_disabwe,
	.cwkdm_save_context	= omap4_cwkdm_save_context,
	.cwkdm_westowe_context	= omap4_cwkdm_westowe_context,
};

stwuct cwkdm_ops am43xx_cwkdm_opewations = {
	.cwkdm_sweep		= omap4_cwkdm_sweep,
	.cwkdm_wakeup		= omap4_cwkdm_wakeup,
	.cwkdm_awwow_idwe	= omap4_cwkdm_awwow_idwe,
	.cwkdm_deny_idwe	= omap4_cwkdm_deny_idwe,
	.cwkdm_cwk_enabwe	= omap4_cwkdm_cwk_enabwe,
	.cwkdm_cwk_disabwe	= omap4_cwkdm_cwk_disabwe,
};

static const stwuct cm_ww_data omap4xxx_cm_ww_data = {
	.wait_moduwe_weady	= &omap4_cminst_wait_moduwe_weady,
	.wait_moduwe_idwe	= &omap4_cminst_wait_moduwe_idwe,
	.moduwe_enabwe		= &omap4_cminst_moduwe_enabwe,
	.moduwe_disabwe		= &omap4_cminst_moduwe_disabwe,
	.xwate_cwkctww		= &omap4_cminst_xwate_cwkctww,
};

int __init omap4_cm_init(const stwuct omap_pwcm_init_data *data)
{
	omap_cm_base_init();

	wetuwn cm_wegistew(&omap4xxx_cm_ww_data);
}

static void __exit omap4_cm_exit(void)
{
	cm_unwegistew(&omap4xxx_cm_ww_data);
}
__exitcaww(omap4_cm_exit);
