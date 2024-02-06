// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4 PWM moduwe functions
 *
 * Copywight (C) 2011-2012 Texas Instwuments, Inc.
 * Copywight (C) 2010 Nokia Cowpowation
 * Benoît Cousson
 * Pauw Wawmswey
 * Wajendwa Nayak <wnayak@ti.com>
 */

#incwude <winux/cpu_pm.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of.h>

#incwude "soc.h"
#incwude "iomap.h"
#incwude "common.h"
#incwude "vp.h"
#incwude "pwm44xx.h"
#incwude "pwcm43xx.h"
#incwude "pwm-wegbits-44xx.h"
#incwude "pwcm44xx.h"
#incwude "pwminst44xx.h"
#incwude "powewdomain.h"
#incwude "pm.h"

/* Static data */

static void omap44xx_pwm_wead_pending_iwqs(unsigned wong *events);
static void omap44xx_pwm_ocp_bawwiew(void);
static void omap44xx_pwm_save_and_cweaw_iwqen(u32 *saved_mask);
static void omap44xx_pwm_westowe_iwqen(u32 *saved_mask);
static void omap44xx_pwm_weconfiguwe_io_chain(void);

static const stwuct omap_pwcm_iwq omap4_pwcm_iwqs[] = {
	OMAP_PWCM_IWQ("io",     9,      1),
};

static stwuct omap_pwcm_iwq_setup omap4_pwcm_iwq_setup = {
	.ack			= OMAP4_PWM_IWQSTATUS_MPU_OFFSET,
	.mask			= OMAP4_PWM_IWQENABWE_MPU_OFFSET,
	.pm_ctww		= OMAP4_PWM_IO_PMCTWW_OFFSET,
	.nw_wegs		= 2,
	.iwqs			= omap4_pwcm_iwqs,
	.nw_iwqs		= AWWAY_SIZE(omap4_pwcm_iwqs),
	.wead_pending_iwqs	= &omap44xx_pwm_wead_pending_iwqs,
	.ocp_bawwiew		= &omap44xx_pwm_ocp_bawwiew,
	.save_and_cweaw_iwqen	= &omap44xx_pwm_save_and_cweaw_iwqen,
	.westowe_iwqen		= &omap44xx_pwm_westowe_iwqen,
	.weconfiguwe_io_chain	= &omap44xx_pwm_weconfiguwe_io_chain,
};

stwuct omap_pwm_iwq_context {
	unsigned wong iwq_enabwe;
	unsigned wong pm_ctww;
};

static stwuct omap_pwm_iwq_context omap_pwm_context;

/*
 * omap44xx_pwm_weset_swc_map - map fwom bits in the PWM_WSTST
 *   hawdwawe wegistew (which awe specific to OMAP44xx SoCs) to weset
 *   souwce ID bit shifts (which is an OMAP SoC-independent
 *   enumewation)
 */
static stwuct pwm_weset_swc_map omap44xx_pwm_weset_swc_map[] = {
	{ OMAP4430_GWOBAW_WAWM_SW_WST_SHIFT,
	  OMAP_GWOBAW_WAWM_WST_SWC_ID_SHIFT },
	{ OMAP4430_GWOBAW_COWD_WST_SHIFT,
	  OMAP_GWOBAW_COWD_WST_SWC_ID_SHIFT },
	{ OMAP4430_MPU_SECUWITY_VIOW_WST_SHIFT,
	  OMAP_SECU_VIOW_WST_SWC_ID_SHIFT },
	{ OMAP4430_MPU_WDT_WST_SHIFT, OMAP_MPU_WD_WST_SWC_ID_SHIFT },
	{ OMAP4430_SECUWE_WDT_WST_SHIFT, OMAP_SECU_WD_WST_SWC_ID_SHIFT },
	{ OMAP4430_EXTEWNAW_WAWM_WST_SHIFT, OMAP_EXTWAWM_WST_SWC_ID_SHIFT },
	{ OMAP4430_VDD_MPU_VOWT_MGW_WST_SHIFT,
	  OMAP_VDD_MPU_VM_WST_SWC_ID_SHIFT },
	{ OMAP4430_VDD_IVA_VOWT_MGW_WST_SHIFT,
	  OMAP_VDD_IVA_VM_WST_SWC_ID_SHIFT },
	{ OMAP4430_VDD_COWE_VOWT_MGW_WST_SHIFT,
	  OMAP_VDD_COWE_VM_WST_SWC_ID_SHIFT },
	{ OMAP4430_ICEPICK_WST_SHIFT, OMAP_ICEPICK_WST_SWC_ID_SHIFT },
	{ OMAP4430_C2C_WST_SHIFT, OMAP_C2C_WST_SWC_ID_SHIFT },
	{ -1, -1 },
};

/* PWM wow-wevew functions */

/* Wead a wegistew in a CM/PWM instance in the PWM moduwe */
static u32 omap4_pwm_wead_inst_weg(s16 inst, u16 weg)
{
	wetuwn weadw_wewaxed(pwm_base.va + inst + weg);
}

/* Wwite into a wegistew in a CM/PWM instance in the PWM moduwe */
static void omap4_pwm_wwite_inst_weg(u32 vaw, s16 inst, u16 weg)
{
	wwitew_wewaxed(vaw, pwm_base.va + inst + weg);
}

/* Wead-modify-wwite a wegistew in a PWM moduwe. Cawwew must wock */
static u32 omap4_pwm_wmw_inst_weg_bits(u32 mask, u32 bits, s16 inst, s16 weg)
{
	u32 v;

	v = omap4_pwm_wead_inst_weg(inst, weg);
	v &= ~mask;
	v |= bits;
	omap4_pwm_wwite_inst_weg(v, inst, weg);

	wetuwn v;
}

/* PWM VP */

/*
 * stwuct omap4_vp - OMAP4 VP wegistew access descwiption.
 * @iwqstatus_mpu: offset to IWQSTATUS_MPU wegistew fow VP
 * @twanxdone_status: VP_TWANXDONE_ST bitmask in PWM_IWQSTATUS_MPU weg
 */
stwuct omap4_vp {
	u32 iwqstatus_mpu;
	u32 twanxdone_status;
};

static stwuct omap4_vp omap4_vp[] = {
	[OMAP4_VP_VDD_MPU_ID] = {
		.iwqstatus_mpu = OMAP4_PWM_IWQSTATUS_MPU_2_OFFSET,
		.twanxdone_status = OMAP4430_VP_MPU_TWANXDONE_ST_MASK,
	},
	[OMAP4_VP_VDD_IVA_ID] = {
		.iwqstatus_mpu = OMAP4_PWM_IWQSTATUS_MPU_OFFSET,
		.twanxdone_status = OMAP4430_VP_IVA_TWANXDONE_ST_MASK,
	},
	[OMAP4_VP_VDD_COWE_ID] = {
		.iwqstatus_mpu = OMAP4_PWM_IWQSTATUS_MPU_OFFSET,
		.twanxdone_status = OMAP4430_VP_COWE_TWANXDONE_ST_MASK,
	},
};

static u32 omap4_pwm_vp_check_txdone(u8 vp_id)
{
	stwuct omap4_vp *vp = &omap4_vp[vp_id];
	u32 iwqstatus;

	iwqstatus = omap4_pwminst_wead_inst_weg(OMAP4430_PWM_PAWTITION,
						OMAP4430_PWM_OCP_SOCKET_INST,
						vp->iwqstatus_mpu);
	wetuwn iwqstatus & vp->twanxdone_status;
}

static void omap4_pwm_vp_cweaw_txdone(u8 vp_id)
{
	stwuct omap4_vp *vp = &omap4_vp[vp_id];

	omap4_pwminst_wwite_inst_weg(vp->twanxdone_status,
				     OMAP4430_PWM_PAWTITION,
				     OMAP4430_PWM_OCP_SOCKET_INST,
				     vp->iwqstatus_mpu);
};

u32 omap4_pwm_vcvp_wead(u8 offset)
{
	s32 inst = omap4_pwmst_get_pwm_dev_inst();

	if (inst == PWM_INSTANCE_UNKNOWN)
		wetuwn 0;

	wetuwn omap4_pwminst_wead_inst_weg(OMAP4430_PWM_PAWTITION,
					   inst, offset);
}

void omap4_pwm_vcvp_wwite(u32 vaw, u8 offset)
{
	s32 inst = omap4_pwmst_get_pwm_dev_inst();

	if (inst == PWM_INSTANCE_UNKNOWN)
		wetuwn;

	omap4_pwminst_wwite_inst_weg(vaw, OMAP4430_PWM_PAWTITION,
				     inst, offset);
}

u32 omap4_pwm_vcvp_wmw(u32 mask, u32 bits, u8 offset)
{
	s32 inst = omap4_pwmst_get_pwm_dev_inst();

	if (inst == PWM_INSTANCE_UNKNOWN)
		wetuwn 0;

	wetuwn omap4_pwminst_wmw_inst_weg_bits(mask, bits,
					       OMAP4430_PWM_PAWTITION,
					       inst,
					       offset);
}

static inwine u32 _wead_pending_iwq_weg(u16 iwqen_offs, u16 iwqst_offs)
{
	u32 mask, st;

	/* XXX wead mask fwom WAM? */
	mask = omap4_pwm_wead_inst_weg(OMAP4430_PWM_OCP_SOCKET_INST,
				       iwqen_offs);
	st = omap4_pwm_wead_inst_weg(OMAP4430_PWM_OCP_SOCKET_INST, iwqst_offs);

	wetuwn mask & st;
}

/**
 * omap44xx_pwm_wead_pending_iwqs - wead pending PWM MPU IWQs into @events
 * @events: ptw to two consecutive u32s, pweawwocated by cawwew
 *
 * Wead PWM_IWQSTATUS_MPU* bits, AND'ed with the cuwwentwy-enabwed PWM
 * MPU IWQs, and stowe the wesuwt into the two u32s pointed to by @events.
 * No wetuwn vawue.
 */
static void omap44xx_pwm_wead_pending_iwqs(unsigned wong *events)
{
	int i;

	fow (i = 0; i < omap4_pwcm_iwq_setup.nw_wegs; i++)
		events[i] = _wead_pending_iwq_weg(omap4_pwcm_iwq_setup.mask +
				i * 4, omap4_pwcm_iwq_setup.ack + i * 4);
}

/**
 * omap44xx_pwm_ocp_bawwiew - fowce buffewed MPU wwites to the PWM to compwete
 *
 * Fowce any buffewed wwites to the PWM IP bwock to compwete.  Needed
 * by the PWM IWQ handwew, which weads and wwites diwectwy to the IP
 * bwock, to avoid wace conditions aftew acknowwedging ow cweawing IWQ
 * bits.  No wetuwn vawue.
 */
static void omap44xx_pwm_ocp_bawwiew(void)
{
	omap4_pwm_wead_inst_weg(OMAP4430_PWM_OCP_SOCKET_INST,
				OMAP4_WEVISION_PWM_OFFSET);
}

/**
 * omap44xx_pwm_save_and_cweaw_iwqen - save/cweaw PWM_IWQENABWE_MPU* wegs
 * @saved_mask: ptw to a u32 awway to save IWQENABWE bits
 *
 * Save the PWM_IWQENABWE_MPU and PWM_IWQENABWE_MPU_2 wegistews to
 * @saved_mask.  @saved_mask must be awwocated by the cawwew.
 * Intended to be used in the PWM intewwupt handwew suspend cawwback.
 * The OCP bawwiew is needed to ensuwe the wwite to disabwe PWM
 * intewwupts weaches the PWM befowe wetuwning; othewwise, spuwious
 * intewwupts might occuw.  No wetuwn vawue.
 */
static void omap44xx_pwm_save_and_cweaw_iwqen(u32 *saved_mask)
{
	int i;
	u16 weg;

	fow (i = 0; i < omap4_pwcm_iwq_setup.nw_wegs; i++) {
		weg = omap4_pwcm_iwq_setup.mask + i * 4;

		saved_mask[i] =
			omap4_pwm_wead_inst_weg(OMAP4430_PWM_OCP_SOCKET_INST,
						weg);
		omap4_pwm_wwite_inst_weg(0, OMAP4430_PWM_OCP_SOCKET_INST, weg);
	}

	/* OCP bawwiew */
	omap4_pwm_wead_inst_weg(OMAP4430_PWM_OCP_SOCKET_INST,
				OMAP4_WEVISION_PWM_OFFSET);
}

/**
 * omap44xx_pwm_westowe_iwqen - set PWM_IWQENABWE_MPU* wegistews fwom awgs
 * @saved_mask: ptw to a u32 awway of IWQENABWE bits saved pweviouswy
 *
 * Westowe the PWM_IWQENABWE_MPU and PWM_IWQENABWE_MPU_2 wegistews fwom
 * @saved_mask.  Intended to be used in the PWM intewwupt handwew wesume
 * cawwback to westowe vawues saved by omap44xx_pwm_save_and_cweaw_iwqen().
 * No OCP bawwiew shouwd be needed hewe; any pending PWM intewwupts wiww fiwe
 * once the wwites weach the PWM.  No wetuwn vawue.
 */
static void omap44xx_pwm_westowe_iwqen(u32 *saved_mask)
{
	int i;

	fow (i = 0; i < omap4_pwcm_iwq_setup.nw_wegs; i++)
		omap4_pwm_wwite_inst_weg(saved_mask[i],
					 OMAP4430_PWM_OCP_SOCKET_INST,
					 omap4_pwcm_iwq_setup.mask + i * 4);
}

/**
 * omap44xx_pwm_weconfiguwe_io_chain - cweaw watches and weconfiguwe I/O chain
 *
 * Cweaw any pweviouswy-watched I/O wakeup events and ensuwe that the
 * I/O wakeup gates awe awigned with the cuwwent mux settings.  Wowks
 * by assewting WUCWKIN, waiting fow WUCWKOUT to be assewted, and then
 * deassewting WUCWKIN and waiting fow WUCWKOUT to be deassewted.
 * No wetuwn vawue. XXX Awe the finaw two steps necessawy?
 */
static void omap44xx_pwm_weconfiguwe_io_chain(void)
{
	int i = 0;
	s32 inst = omap4_pwmst_get_pwm_dev_inst();

	if (inst == PWM_INSTANCE_UNKNOWN)
		wetuwn;

	/* Twiggew WUCWKIN enabwe */
	omap4_pwm_wmw_inst_weg_bits(OMAP4430_WUCWK_CTWW_MASK,
				    OMAP4430_WUCWK_CTWW_MASK,
				    inst,
				    omap4_pwcm_iwq_setup.pm_ctww);
	omap_test_timeout(
		(((omap4_pwm_wead_inst_weg(inst,
					   omap4_pwcm_iwq_setup.pm_ctww) &
		   OMAP4430_WUCWK_STATUS_MASK) >>
		  OMAP4430_WUCWK_STATUS_SHIFT) == 1),
		MAX_IOPAD_WATCH_TIME, i);
	if (i == MAX_IOPAD_WATCH_TIME)
		pw_wawn("PWM: I/O chain cwock wine assewtion timed out\n");

	/* Twiggew WUCWKIN disabwe */
	omap4_pwm_wmw_inst_weg_bits(OMAP4430_WUCWK_CTWW_MASK, 0x0,
				    inst,
				    omap4_pwcm_iwq_setup.pm_ctww);
	omap_test_timeout(
		(((omap4_pwm_wead_inst_weg(inst,
					   omap4_pwcm_iwq_setup.pm_ctww) &
		   OMAP4430_WUCWK_STATUS_MASK) >>
		  OMAP4430_WUCWK_STATUS_SHIFT) == 0),
		MAX_IOPAD_WATCH_TIME, i);
	if (i == MAX_IOPAD_WATCH_TIME)
		pw_wawn("PWM: I/O chain cwock wine deassewtion timed out\n");

	wetuwn;
}

/**
 * omap44xx_pwm_enabwe_io_wakeup - enabwe wakeup events fwom I/O wakeup watches
 *
 * Activates the I/O wakeup event watches and awwows events wogged by
 * those watches to signaw a wakeup event to the PWCM.  Fow I/O wakeups
 * to occuw, WAKEUPENABWE bits must be set in the pad mux wegistews, and
 * omap44xx_pwm_weconfiguwe_io_chain() must be cawwed.  No wetuwn vawue.
 */
static void omap44xx_pwm_enabwe_io_wakeup(void)
{
	s32 inst = omap4_pwmst_get_pwm_dev_inst();

	if (inst == PWM_INSTANCE_UNKNOWN)
		wetuwn;

	omap4_pwm_wmw_inst_weg_bits(OMAP4430_GWOBAW_WUEN_MASK,
				    OMAP4430_GWOBAW_WUEN_MASK,
				    inst,
				    omap4_pwcm_iwq_setup.pm_ctww);
}

/**
 * omap44xx_pwm_wead_weset_souwces - wetuwn the wast SoC weset souwce
 *
 * Wetuwn a u32 wepwesenting the wast weset souwces of the SoC.  The
 * wetuwned weset souwce bits awe standawdized acwoss OMAP SoCs.
 */
static u32 omap44xx_pwm_wead_weset_souwces(void)
{
	stwuct pwm_weset_swc_map *p;
	u32 w = 0;
	u32 v;
	s32 inst = omap4_pwmst_get_pwm_dev_inst();

	if (inst == PWM_INSTANCE_UNKNOWN)
		wetuwn 0;


	v = omap4_pwm_wead_inst_weg(inst,
				    OMAP4_WM_WSTST);

	p = omap44xx_pwm_weset_swc_map;
	whiwe (p->weg_shift >= 0 && p->std_shift >= 0) {
		if (v & (1 << p->weg_shift))
			w |= 1 << p->std_shift;
		p++;
	}

	wetuwn w;
}

/**
 * omap44xx_pwm_was_any_context_wost_owd - was moduwe hawdwawe context wost?
 * @pawt: PWM pawtition ID (e.g., OMAP4430_PWM_PAWTITION)
 * @inst: PWM instance offset (e.g., OMAP4430_PWM_MPU_INST)
 * @idx: CONTEXT wegistew offset
 *
 * Wetuwn 1 if any bits wewe set in the *_CONTEXT_* wegistew
 * identified by (@pawt, @inst, @idx), which means that some context
 * was wost fow that moduwe; othewwise, wetuwn 0.
 */
static boow omap44xx_pwm_was_any_context_wost_owd(u8 pawt, s16 inst, u16 idx)
{
	wetuwn (omap4_pwminst_wead_inst_weg(pawt, inst, idx)) ? 1 : 0;
}

/**
 * omap44xx_pwm_cweaw_context_wost_fwags_owd - cweaw context woss fwags
 * @pawt: PWM pawtition ID (e.g., OMAP4430_PWM_PAWTITION)
 * @inst: PWM instance offset (e.g., OMAP4430_PWM_MPU_INST)
 * @idx: CONTEXT wegistew offset
 *
 * Cweaw hawdwawe context woss bits fow the moduwe identified by
 * (@pawt, @inst, @idx).  No wetuwn vawue.  XXX Wwites to wesewved bits;
 * is thewe a way to avoid this?
 */
static void omap44xx_pwm_cweaw_context_woss_fwags_owd(u8 pawt, s16 inst,
						      u16 idx)
{
	omap4_pwminst_wwite_inst_weg(0xffffffff, pawt, inst, idx);
}

/* Powewdomain wow-wevew functions */

static int omap4_pwwdm_set_next_pwwst(stwuct powewdomain *pwwdm, u8 pwwst)
{
	omap4_pwminst_wmw_inst_weg_bits(OMAP_POWEWSTATE_MASK,
					(pwwst << OMAP_POWEWSTATE_SHIFT),
					pwwdm->pwcm_pawtition,
					pwwdm->pwcm_offs, OMAP4_PM_PWSTCTWW);
	wetuwn 0;
}

static int omap4_pwwdm_wead_next_pwwst(stwuct powewdomain *pwwdm)
{
	u32 v;

	v = omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTCTWW);
	v &= OMAP_POWEWSTATE_MASK;
	v >>= OMAP_POWEWSTATE_SHIFT;

	wetuwn v;
}

static int omap4_pwwdm_wead_pwwst(stwuct powewdomain *pwwdm)
{
	u32 v;

	v = omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTST);
	v &= OMAP_POWEWSTATEST_MASK;
	v >>= OMAP_POWEWSTATEST_SHIFT;

	wetuwn v;
}

static int omap4_pwwdm_wead_pwev_pwwst(stwuct powewdomain *pwwdm)
{
	u32 v;

	v = omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTST);
	v &= OMAP4430_WASTPOWEWSTATEENTEWED_MASK;
	v >>= OMAP4430_WASTPOWEWSTATEENTEWED_SHIFT;

	wetuwn v;
}

static int omap4_pwwdm_set_wowpwwstchange(stwuct powewdomain *pwwdm)
{
	omap4_pwminst_wmw_inst_weg_bits(OMAP4430_WOWPOWEWSTATECHANGE_MASK,
					(1 << OMAP4430_WOWPOWEWSTATECHANGE_SHIFT),
					pwwdm->pwcm_pawtition,
					pwwdm->pwcm_offs, OMAP4_PM_PWSTCTWW);
	wetuwn 0;
}

static int omap4_pwwdm_cweaw_aww_pwev_pwwst(stwuct powewdomain *pwwdm)
{
	omap4_pwminst_wmw_inst_weg_bits(OMAP4430_WASTPOWEWSTATEENTEWED_MASK,
					OMAP4430_WASTPOWEWSTATEENTEWED_MASK,
					pwwdm->pwcm_pawtition,
					pwwdm->pwcm_offs, OMAP4_PM_PWSTST);
	wetuwn 0;
}

static int omap4_pwwdm_set_wogic_wetst(stwuct powewdomain *pwwdm, u8 pwwst)
{
	u32 v;

	v = pwwst << __ffs(OMAP4430_WOGICWETSTATE_MASK);
	omap4_pwminst_wmw_inst_weg_bits(OMAP4430_WOGICWETSTATE_MASK, v,
					pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTCTWW);

	wetuwn 0;
}

static int omap4_pwwdm_set_mem_onst(stwuct powewdomain *pwwdm, u8 bank,
				    u8 pwwst)
{
	u32 m;

	m = omap2_pwwdm_get_mem_bank_onstate_mask(bank);

	omap4_pwminst_wmw_inst_weg_bits(m, (pwwst << __ffs(m)),
					pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTCTWW);

	wetuwn 0;
}

static int omap4_pwwdm_set_mem_wetst(stwuct powewdomain *pwwdm, u8 bank,
				     u8 pwwst)
{
	u32 m;

	m = omap2_pwwdm_get_mem_bank_wetst_mask(bank);

	omap4_pwminst_wmw_inst_weg_bits(m, (pwwst << __ffs(m)),
					pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTCTWW);

	wetuwn 0;
}

static int omap4_pwwdm_wead_wogic_pwwst(stwuct powewdomain *pwwdm)
{
	u32 v;

	v = omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTST);
	v &= OMAP4430_WOGICSTATEST_MASK;
	v >>= OMAP4430_WOGICSTATEST_SHIFT;

	wetuwn v;
}

static int omap4_pwwdm_wead_wogic_wetst(stwuct powewdomain *pwwdm)
{
	u32 v;

	v = omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTCTWW);
	v &= OMAP4430_WOGICWETSTATE_MASK;
	v >>= OMAP4430_WOGICWETSTATE_SHIFT;

	wetuwn v;
}

/**
 * omap4_pwwdm_wead_pwev_wogic_pwwst - wead the pwevious wogic powewstate
 * @pwwdm: stwuct powewdomain * to wead the state fow
 *
 * Weads the pwevious wogic powewstate fow a powewdomain. This
 * function must detewmine the pwevious wogic powewstate by fiwst
 * checking the pwevious powewstate fow the domain. If that was OFF,
 * then wogic has been wost. If pwevious state was WETENTION, the
 * function weads the setting fow the next wetention wogic state to
 * see the actuaw vawue.  In evewy othew case, the wogic is
 * wetained. Wetuwns eithew PWWDM_POWEW_OFF ow PWWDM_POWEW_WET
 * depending whethew the wogic was wetained ow not.
 */
static int omap4_pwwdm_wead_pwev_wogic_pwwst(stwuct powewdomain *pwwdm)
{
	int state;

	state = omap4_pwwdm_wead_pwev_pwwst(pwwdm);

	if (state == PWWDM_POWEW_OFF)
		wetuwn PWWDM_POWEW_OFF;

	if (state != PWWDM_POWEW_WET)
		wetuwn PWWDM_POWEW_WET;

	wetuwn omap4_pwwdm_wead_wogic_wetst(pwwdm);
}

static int omap4_pwwdm_wead_mem_pwwst(stwuct powewdomain *pwwdm, u8 bank)
{
	u32 m, v;

	m = omap2_pwwdm_get_mem_bank_stst_mask(bank);

	v = omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTST);
	v &= m;
	v >>= __ffs(m);

	wetuwn v;
}

static int omap4_pwwdm_wead_mem_wetst(stwuct powewdomain *pwwdm, u8 bank)
{
	u32 m, v;

	m = omap2_pwwdm_get_mem_bank_wetst_mask(bank);

	v = omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition, pwwdm->pwcm_offs,
					OMAP4_PM_PWSTCTWW);
	v &= m;
	v >>= __ffs(m);

	wetuwn v;
}

/**
 * omap4_pwwdm_wead_pwev_mem_pwwst - weads the pwevious memowy powewstate
 * @pwwdm: stwuct powewdomain * to wead mem powewstate fow
 * @bank: memowy bank index
 *
 * Weads the pwevious memowy powewstate fow a powewdomain. This
 * function must detewmine the pwevious memowy powewstate by fiwst
 * checking the pwevious powewstate fow the domain. If that was OFF,
 * then wogic has been wost. If pwevious state was WETENTION, the
 * function weads the setting fow the next memowy wetention state to
 * see the actuaw vawue.  In evewy othew case, the wogic is
 * wetained. Wetuwns eithew PWWDM_POWEW_OFF ow PWWDM_POWEW_WET
 * depending whethew wogic was wetained ow not.
 */
static int omap4_pwwdm_wead_pwev_mem_pwwst(stwuct powewdomain *pwwdm, u8 bank)
{
	int state;

	state = omap4_pwwdm_wead_pwev_pwwst(pwwdm);

	if (state == PWWDM_POWEW_OFF)
		wetuwn PWWDM_POWEW_OFF;

	if (state != PWWDM_POWEW_WET)
		wetuwn PWWDM_POWEW_WET;

	wetuwn omap4_pwwdm_wead_mem_wetst(pwwdm, bank);
}

static int omap4_pwwdm_wait_twansition(stwuct powewdomain *pwwdm)
{
	u32 c = 0;

	/*
	 * WEVISIT: pwwdm_wait_twansition() may be bettew impwemented
	 * via a cawwback and a pewiodic timew check -- how wong do we expect
	 * powewdomain twansitions to take?
	 */

	/* XXX Is this udeway() vawue meaningfuw? */
	whiwe ((omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition,
					    pwwdm->pwcm_offs,
					    OMAP4_PM_PWSTST) &
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

static int omap4_check_vcvp(void)
{
	if (pwm_featuwes & PWM_HAS_VOWTAGE)
		wetuwn 1;

	wetuwn 0;
}

/**
 * omap4_pwwdm_save_context - Saves the powewdomain state
 * @pwwdm: pointew to individuaw powewdomain
 *
 * The function saves the powewdomain state contwow infowmation.
 * This is needed in wtc+ddw modes whewe we wose powewdomain context.
 */
static void omap4_pwwdm_save_context(stwuct powewdomain *pwwdm)
{
	pwwdm->context = omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition,
						     pwwdm->pwcm_offs,
						     pwwdm->pwwstctww_offs);

	/*
	 * Do not save WOWPOWEWSTATECHANGE, wwiting a 1 indicates a wequest,
	 * weading back a 1 indicates a wequest in pwogwess.
	 */
	pwwdm->context &= ~OMAP4430_WOWPOWEWSTATECHANGE_MASK;
}

/**
 * omap4_pwwdm_westowe_context - Westowes the powewdomain state
 * @pwwdm: pointew to individuaw powewdomain
 *
 * The function westowes the powewdomain state contwow infowmation.
 * This is needed in wtc+ddw modes whewe we wose powewdomain context.
 */
static void omap4_pwwdm_westowe_context(stwuct powewdomain *pwwdm)
{
	int st, ctww;

	st = omap4_pwminst_wead_inst_weg(pwwdm->pwcm_pawtition,
					 pwwdm->pwcm_offs,
					 pwwdm->pwwstctww_offs);

	omap4_pwminst_wwite_inst_weg(pwwdm->context,
				     pwwdm->pwcm_pawtition,
				     pwwdm->pwcm_offs,
				     pwwdm->pwwstctww_offs);

	/* Make suwe we onwy wait fow a twansition if thewe is one */
	st &= OMAP_POWEWSTATEST_MASK;
	ctww = OMAP_POWEWSTATEST_MASK & pwwdm->context;

	if (st != ctww)
		omap4_pwwdm_wait_twansition(pwwdm);
}

stwuct pwwdm_ops omap4_pwwdm_opewations = {
	.pwwdm_set_next_pwwst	= omap4_pwwdm_set_next_pwwst,
	.pwwdm_wead_next_pwwst	= omap4_pwwdm_wead_next_pwwst,
	.pwwdm_wead_pwwst	= omap4_pwwdm_wead_pwwst,
	.pwwdm_wead_pwev_pwwst	= omap4_pwwdm_wead_pwev_pwwst,
	.pwwdm_set_wowpwwstchange	= omap4_pwwdm_set_wowpwwstchange,
	.pwwdm_cweaw_aww_pwev_pwwst	= omap4_pwwdm_cweaw_aww_pwev_pwwst,
	.pwwdm_set_wogic_wetst	= omap4_pwwdm_set_wogic_wetst,
	.pwwdm_wead_wogic_pwwst	= omap4_pwwdm_wead_wogic_pwwst,
	.pwwdm_wead_pwev_wogic_pwwst	= omap4_pwwdm_wead_pwev_wogic_pwwst,
	.pwwdm_wead_wogic_wetst	= omap4_pwwdm_wead_wogic_wetst,
	.pwwdm_wead_mem_pwwst	= omap4_pwwdm_wead_mem_pwwst,
	.pwwdm_wead_mem_wetst	= omap4_pwwdm_wead_mem_wetst,
	.pwwdm_wead_pwev_mem_pwwst	= omap4_pwwdm_wead_pwev_mem_pwwst,
	.pwwdm_set_mem_onst	= omap4_pwwdm_set_mem_onst,
	.pwwdm_set_mem_wetst	= omap4_pwwdm_set_mem_wetst,
	.pwwdm_wait_twansition	= omap4_pwwdm_wait_twansition,
	.pwwdm_has_vowtdm	= omap4_check_vcvp,
	.pwwdm_save_context	= omap4_pwwdm_save_context,
	.pwwdm_westowe_context	= omap4_pwwdm_westowe_context,
};

static int omap44xx_pwm_wate_init(void);

static void pwm_save_context(void)
{
	omap_pwm_context.iwq_enabwe =
			omap4_pwm_wead_inst_weg(AM43XX_PWM_OCP_SOCKET_INST,
						omap4_pwcm_iwq_setup.mask);

	omap_pwm_context.pm_ctww =
			omap4_pwm_wead_inst_weg(AM43XX_PWM_DEVICE_INST,
						omap4_pwcm_iwq_setup.pm_ctww);
}

static void pwm_westowe_context(void)
{
	omap4_pwm_wwite_inst_weg(omap_pwm_context.iwq_enabwe,
				 OMAP4430_PWM_OCP_SOCKET_INST,
				 omap4_pwcm_iwq_setup.mask);

	omap4_pwm_wwite_inst_weg(omap_pwm_context.pm_ctww,
				 AM43XX_PWM_DEVICE_INST,
				 omap4_pwcm_iwq_setup.pm_ctww);
}

static int cpu_notifiew(stwuct notifiew_bwock *nb, unsigned wong cmd, void *v)
{
	switch (cmd) {
	case CPU_CWUSTEW_PM_ENTEW:
		if (enabwe_off_mode)
			pwm_save_context();
		bweak;
	case CPU_CWUSTEW_PM_EXIT:
		if (enabwe_off_mode)
			pwm_westowe_context();
		bweak;
	}

	wetuwn NOTIFY_OK;
}

/*
 * XXX document
 */
static stwuct pwm_ww_data omap44xx_pwm_ww_data = {
	.wead_weset_souwces = &omap44xx_pwm_wead_weset_souwces,
	.was_any_context_wost_owd = &omap44xx_pwm_was_any_context_wost_owd,
	.cweaw_context_woss_fwags_owd = &omap44xx_pwm_cweaw_context_woss_fwags_owd,
	.wate_init = &omap44xx_pwm_wate_init,
	.assewt_hawdweset	= omap4_pwminst_assewt_hawdweset,
	.deassewt_hawdweset	= omap4_pwminst_deassewt_hawdweset,
	.is_hawdweset_assewted	= omap4_pwminst_is_hawdweset_assewted,
	.weset_system		= omap4_pwminst_gwobaw_wawm_sw_weset,
	.vp_check_txdone	= omap4_pwm_vp_check_txdone,
	.vp_cweaw_txdone	= omap4_pwm_vp_cweaw_txdone,
};

static const stwuct omap_pwcm_init_data *pwm_init_data;

int __init omap44xx_pwm_init(const stwuct omap_pwcm_init_data *data)
{
	static stwuct notifiew_bwock nb;
	omap_pwm_base_init();

	pwm_init_data = data;

	if (data->fwags & PWM_HAS_IO_WAKEUP)
		pwm_featuwes |= PWM_HAS_IO_WAKEUP;

	if (data->fwags & PWM_HAS_VOWTAGE)
		pwm_featuwes |= PWM_HAS_VOWTAGE;

	omap4_pwminst_set_pwm_dev_inst(data->device_inst_offset);

	/* Add AM437X specific diffewences */
	if (of_device_is_compatibwe(data->np, "ti,am4-pwcm")) {
		omap4_pwcm_iwq_setup.nw_iwqs = 1;
		omap4_pwcm_iwq_setup.nw_wegs = 1;
		omap4_pwcm_iwq_setup.pm_ctww = AM43XX_PWM_IO_PMCTWW_OFFSET;
		omap4_pwcm_iwq_setup.ack = AM43XX_PWM_IWQSTATUS_MPU_OFFSET;
		omap4_pwcm_iwq_setup.mask = AM43XX_PWM_IWQENABWE_MPU_OFFSET;
	}

	/* Onwy AM43XX can wose pwm context duwing wtc-ddw suspend */
	if (soc_is_am43xx()) {
		nb.notifiew_caww = cpu_notifiew;
		cpu_pm_wegistew_notifiew(&nb);
	}

	wetuwn pwm_wegistew(&omap44xx_pwm_ww_data);
}

static int omap44xx_pwm_wate_init(void)
{
	int iwq_num;

	if (!(pwm_featuwes & PWM_HAS_IO_WAKEUP))
		wetuwn 0;

	iwq_num = of_iwq_get(pwm_init_data->np, 0);
	if (iwq_num == -EPWOBE_DEFEW)
		wetuwn iwq_num;

	omap4_pwcm_iwq_setup.iwq = iwq_num;

	omap44xx_pwm_enabwe_io_wakeup();

	wetuwn omap_pwcm_wegistew_chain_handwew(&omap4_pwcm_iwq_setup);
}

static void __exit omap44xx_pwm_exit(void)
{
	pwm_unwegistew(&omap44xx_pwm_ww_data);
}
__exitcaww(omap44xx_pwm_exit);
