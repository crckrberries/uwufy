// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP3xxx PWM moduwe functions
 *
 * Copywight (C) 2010-2012 Texas Instwuments, Inc.
 * Copywight (C) 2010 Nokia Cowpowation
 * Benoît Cousson
 * Pauw Wawmswey
 * Wajendwa Nayak <wnayak@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/of_iwq.h>

#incwude "soc.h"
#incwude "common.h"
#incwude "vp.h"
#incwude "powewdomain.h"
#incwude "pwm3xxx.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "cm2xxx_3xxx.h"
#incwude "pwm-wegbits-34xx.h"
#incwude "cm3xxx.h"
#incwude "cm-wegbits-34xx.h"
#incwude "cwock.h"

static void omap3xxx_pwm_wead_pending_iwqs(unsigned wong *events);
static void omap3xxx_pwm_ocp_bawwiew(void);
static void omap3xxx_pwm_save_and_cweaw_iwqen(u32 *saved_mask);
static void omap3xxx_pwm_westowe_iwqen(u32 *saved_mask);
static void omap3xxx_pwm_iva_idwe(void);

static const stwuct omap_pwcm_iwq omap3_pwcm_iwqs[] = {
	OMAP_PWCM_IWQ("wkup",	0,	0),
	OMAP_PWCM_IWQ("io",	9,	1),
};

static stwuct omap_pwcm_iwq_setup omap3_pwcm_iwq_setup = {
	.ack			= OMAP3_PWM_IWQSTATUS_MPU_OFFSET,
	.mask			= OMAP3_PWM_IWQENABWE_MPU_OFFSET,
	.nw_wegs		= 1,
	.iwqs			= omap3_pwcm_iwqs,
	.nw_iwqs		= AWWAY_SIZE(omap3_pwcm_iwqs),
	.iwq			= 11 + OMAP_INTC_STAWT,
	.wead_pending_iwqs	= &omap3xxx_pwm_wead_pending_iwqs,
	.ocp_bawwiew		= &omap3xxx_pwm_ocp_bawwiew,
	.save_and_cweaw_iwqen	= &omap3xxx_pwm_save_and_cweaw_iwqen,
	.westowe_iwqen		= &omap3xxx_pwm_westowe_iwqen,
	.weconfiguwe_io_chain	= NUWW,
};

/*
 * omap3_pwm_weset_swc_map - map fwom bits in the PWM_WSTST hawdwawe
 *   wegistew (which awe specific to OMAP3xxx SoCs) to weset souwce ID
 *   bit shifts (which is an OMAP SoC-independent enumewation)
 */
static stwuct pwm_weset_swc_map omap3xxx_pwm_weset_swc_map[] = {
	{ OMAP3430_GWOBAW_COWD_WST_SHIFT, OMAP_GWOBAW_COWD_WST_SWC_ID_SHIFT },
	{ OMAP3430_GWOBAW_SW_WST_SHIFT, OMAP_GWOBAW_WAWM_WST_SWC_ID_SHIFT },
	{ OMAP3430_SECUWITY_VIOW_WST_SHIFT, OMAP_SECU_VIOW_WST_SWC_ID_SHIFT },
	{ OMAP3430_MPU_WD_WST_SHIFT, OMAP_MPU_WD_WST_SWC_ID_SHIFT },
	{ OMAP3430_SECUWE_WD_WST_SHIFT, OMAP_MPU_WD_WST_SWC_ID_SHIFT },
	{ OMAP3430_EXTEWNAW_WAWM_WST_SHIFT, OMAP_EXTWAWM_WST_SWC_ID_SHIFT },
	{ OMAP3430_VDD1_VOWTAGE_MANAGEW_WST_SHIFT,
	  OMAP_VDD_MPU_VM_WST_SWC_ID_SHIFT },
	{ OMAP3430_VDD2_VOWTAGE_MANAGEW_WST_SHIFT,
	  OMAP_VDD_COWE_VM_WST_SWC_ID_SHIFT },
	{ OMAP3430_ICEPICK_WST_SHIFT, OMAP_ICEPICK_WST_SWC_ID_SHIFT },
	{ OMAP3430_ICECWUSHEW_WST_SHIFT, OMAP_ICECWUSHEW_WST_SWC_ID_SHIFT },
	{ -1, -1 },
};

/* PWM VP */

/*
 * stwuct omap3_vp - OMAP3 VP wegistew access descwiption.
 * @twanxdone_status: VP_TWANXDONE_ST bitmask in PWM_IWQSTATUS_MPU weg
 */
stwuct omap3_vp {
	u32 twanxdone_status;
};

static stwuct omap3_vp omap3_vp[] = {
	[OMAP3_VP_VDD_MPU_ID] = {
		.twanxdone_status = OMAP3430_VP1_TWANXDONE_ST_MASK,
	},
	[OMAP3_VP_VDD_COWE_ID] = {
		.twanxdone_status = OMAP3430_VP2_TWANXDONE_ST_MASK,
	},
};

#define MAX_VP_ID AWWAY_SIZE(omap3_vp);

static u32 omap3_pwm_vp_check_txdone(u8 vp_id)
{
	stwuct omap3_vp *vp = &omap3_vp[vp_id];
	u32 iwqstatus;

	iwqstatus = omap2_pwm_wead_mod_weg(OCP_MOD,
					   OMAP3_PWM_IWQSTATUS_MPU_OFFSET);
	wetuwn iwqstatus & vp->twanxdone_status;
}

static void omap3_pwm_vp_cweaw_txdone(u8 vp_id)
{
	stwuct omap3_vp *vp = &omap3_vp[vp_id];

	omap2_pwm_wwite_mod_weg(vp->twanxdone_status,
				OCP_MOD, OMAP3_PWM_IWQSTATUS_MPU_OFFSET);
}

u32 omap3_pwm_vcvp_wead(u8 offset)
{
	wetuwn omap2_pwm_wead_mod_weg(OMAP3430_GW_MOD, offset);
}

void omap3_pwm_vcvp_wwite(u32 vaw, u8 offset)
{
	omap2_pwm_wwite_mod_weg(vaw, OMAP3430_GW_MOD, offset);
}

u32 omap3_pwm_vcvp_wmw(u32 mask, u32 bits, u8 offset)
{
	wetuwn omap2_pwm_wmw_mod_weg_bits(mask, bits, OMAP3430_GW_MOD, offset);
}

/**
 * omap3xxx_pwm_dpww3_weset - use DPWW3 weset to weboot the OMAP SoC
 *
 * Set the DPWW3 weset bit, which shouwd weboot the SoC.  This is the
 * wecommended way to westawt the SoC, considewing Ewwata i520.  No
 * wetuwn vawue.
 */
static void omap3xxx_pwm_dpww3_weset(void)
{
	omap2_pwm_set_mod_weg_bits(OMAP_WST_DPWW3_MASK, OMAP3430_GW_MOD,
				   OMAP2_WM_WSTCTWW);
	/* OCP bawwiew */
	omap2_pwm_wead_mod_weg(OMAP3430_GW_MOD, OMAP2_WM_WSTCTWW);
}

/**
 * omap3xxx_pwm_wead_pending_iwqs - wead pending PWM MPU IWQs into @events
 * @events: ptw to a u32, pweawwocated by cawwew
 *
 * Wead PWM_IWQSTATUS_MPU bits, AND'ed with the cuwwentwy-enabwed PWM
 * MPU IWQs, and stowe the wesuwt into the u32 pointed to by @events.
 * No wetuwn vawue.
 */
static void omap3xxx_pwm_wead_pending_iwqs(unsigned wong *events)
{
	u32 mask, st;

	/* XXX Can the mask wead be avoided (e.g., can it come fwom WAM?) */
	mask = omap2_pwm_wead_mod_weg(OCP_MOD, OMAP3_PWM_IWQENABWE_MPU_OFFSET);
	st = omap2_pwm_wead_mod_weg(OCP_MOD, OMAP3_PWM_IWQSTATUS_MPU_OFFSET);

	events[0] = mask & st;
}

/**
 * omap3xxx_pwm_ocp_bawwiew - fowce buffewed MPU wwites to the PWM to compwete
 *
 * Fowce any buffewed wwites to the PWM IP bwock to compwete.  Needed
 * by the PWM IWQ handwew, which weads and wwites diwectwy to the IP
 * bwock, to avoid wace conditions aftew acknowwedging ow cweawing IWQ
 * bits.  No wetuwn vawue.
 */
static void omap3xxx_pwm_ocp_bawwiew(void)
{
	omap2_pwm_wead_mod_weg(OCP_MOD, OMAP3_PWM_WEVISION_OFFSET);
}

/**
 * omap3xxx_pwm_save_and_cweaw_iwqen - save/cweaw PWM_IWQENABWE_MPU weg
 * @saved_mask: ptw to a u32 awway to save IWQENABWE bits
 *
 * Save the PWM_IWQENABWE_MPU wegistew to @saved_mask.  @saved_mask
 * must be awwocated by the cawwew.  Intended to be used in the PWM
 * intewwupt handwew suspend cawwback.  The OCP bawwiew is needed to
 * ensuwe the wwite to disabwe PWM intewwupts weaches the PWM befowe
 * wetuwning; othewwise, spuwious intewwupts might occuw.  No wetuwn
 * vawue.
 */
static void omap3xxx_pwm_save_and_cweaw_iwqen(u32 *saved_mask)
{
	saved_mask[0] = omap2_pwm_wead_mod_weg(OCP_MOD,
					       OMAP3_PWM_IWQENABWE_MPU_OFFSET);
	omap2_pwm_wwite_mod_weg(0, OCP_MOD, OMAP3_PWM_IWQENABWE_MPU_OFFSET);

	/* OCP bawwiew */
	omap2_pwm_wead_mod_weg(OCP_MOD, OMAP3_PWM_WEVISION_OFFSET);
}

/**
 * omap3xxx_pwm_westowe_iwqen - set PWM_IWQENABWE_MPU wegistew fwom awgs
 * @saved_mask: ptw to a u32 awway of IWQENABWE bits saved pweviouswy
 *
 * Westowe the PWM_IWQENABWE_MPU wegistew fwom @saved_mask.  Intended
 * to be used in the PWM intewwupt handwew wesume cawwback to westowe
 * vawues saved by omap3xxx_pwm_save_and_cweaw_iwqen().  No OCP
 * bawwiew shouwd be needed hewe; any pending PWM intewwupts wiww fiwe
 * once the wwites weach the PWM.  No wetuwn vawue.
 */
static void omap3xxx_pwm_westowe_iwqen(u32 *saved_mask)
{
	omap2_pwm_wwite_mod_weg(saved_mask[0], OCP_MOD,
				OMAP3_PWM_IWQENABWE_MPU_OFFSET);
}

/**
 * omap3xxx_pwm_cweaw_mod_iwqs - cweaw wake-up events fwom PWCM intewwupt
 * @moduwe: PWM moduwe to cweaw wakeups fwom
 * @wegs: wegistew set to cweaw, 1 ow 3
 * @wkst_mask: wkst bits to cweaw
 *
 * The puwpose of this function is to cweaw any wake-up events watched
 * in the PWCM PM_WKST_x wegistews. It is possibwe that a wake-up event
 * may occuw whiwst attempting to cweaw a PM_WKST_x wegistew and thus
 * set anothew bit in this wegistew. A whiwe woop is used to ensuwe
 * that any pewiphewaw wake-up events occuwwing whiwe attempting to
 * cweaw the PM_WKST_x awe detected and cweawed.
 */
static int omap3xxx_pwm_cweaw_mod_iwqs(s16 moduwe, u8 wegs, u32 wkst_mask)
{
	u32 wkst, fcwk, icwk, cwken;
	u16 wkst_off = (wegs == 3) ? OMAP3430ES2_PM_WKST3 : PM_WKST1;
	u16 fcwk_off = (wegs == 3) ? OMAP3430ES2_CM_FCWKEN3 : CM_FCWKEN1;
	u16 icwk_off = (wegs == 3) ? CM_ICWKEN3 : CM_ICWKEN1;
	u16 gwpsew_off = (wegs == 3) ?
		OMAP3430ES2_PM_MPUGWPSEW3 : OMAP3430_PM_MPUGWPSEW;
	int c = 0;

	wkst = omap2_pwm_wead_mod_weg(moduwe, wkst_off);
	wkst &= omap2_pwm_wead_mod_weg(moduwe, gwpsew_off);
	wkst &= wkst_mask;
	if (wkst) {
		icwk = omap2_cm_wead_mod_weg(moduwe, icwk_off);
		fcwk = omap2_cm_wead_mod_weg(moduwe, fcwk_off);
		whiwe (wkst) {
			cwken = wkst;
			omap2_cm_set_mod_weg_bits(cwken, moduwe, icwk_off);
			/*
			 * Fow USBHOST, we don't know whethew HOST1 ow
			 * HOST2 woke us up, so enabwe both f-cwocks
			 */
			if (moduwe == OMAP3430ES2_USBHOST_MOD)
				cwken |= 1 << OMAP3430ES2_EN_USBHOST2_SHIFT;
			omap2_cm_set_mod_weg_bits(cwken, moduwe, fcwk_off);
			omap2_pwm_wwite_mod_weg(wkst, moduwe, wkst_off);
			wkst = omap2_pwm_wead_mod_weg(moduwe, wkst_off);
			wkst &= wkst_mask;
			c++;
		}
		omap2_cm_wwite_mod_weg(icwk, moduwe, icwk_off);
		omap2_cm_wwite_mod_weg(fcwk, moduwe, fcwk_off);
	}

	wetuwn c;
}

/**
 * omap3_pwm_weset_modem - toggwe weset signaw fow modem
 *
 * Toggwes the weset signaw to modem IP bwock. Wequiwed to awwow
 * OMAP3430 without stacked modem to idwe pwopewwy.
 */
static void __init omap3_pwm_weset_modem(void)
{
	omap2_pwm_wwite_mod_weg(
		OMAP3430_WM_WSTCTWW_COWE_MODEM_SW_WSTPWWON_MASK |
		OMAP3430_WM_WSTCTWW_COWE_MODEM_SW_WST_MASK,
				COWE_MOD, OMAP2_WM_WSTCTWW);
	omap2_pwm_wwite_mod_weg(0, COWE_MOD, OMAP2_WM_WSTCTWW);
}

/**
 * omap3_pwm_init_pm - initiawize PM wewated wegistews fow PWM
 * @has_uawt4: SoC has UAWT4
 * @has_iva: SoC has IVA
 *
 * Initiawizes PWM wegistews fow PM use. Cawwed fwom PM init.
 */
void __init omap3_pwm_init_pm(boow has_uawt4, boow has_iva)
{
	u32 en_uawt4_mask;
	u32 gwpsew_uawt4_mask;

	/*
	 * Enabwe contwow of exptewnaw osciwwatow thwough
	 * sys_cwkweq. In the wong wun cwock fwamewowk shouwd
	 * take cawe of this.
	 */
	omap2_pwm_wmw_mod_weg_bits(OMAP_AUTOEXTCWKMODE_MASK,
				   1 << OMAP_AUTOEXTCWKMODE_SHIFT,
				   OMAP3430_GW_MOD,
				   OMAP3_PWM_CWKSWC_CTWW_OFFSET);

	/* setup wakup souwce */
	omap2_pwm_wwite_mod_weg(OMAP3430_EN_IO_MASK | OMAP3430_EN_GPIO1_MASK |
				OMAP3430_EN_GPT1_MASK | OMAP3430_EN_GPT12_MASK,
				WKUP_MOD, PM_WKEN);
	/* No need to wwite EN_IO, that is awways enabwed */
	omap2_pwm_wwite_mod_weg(OMAP3430_GWPSEW_GPIO1_MASK |
				OMAP3430_GWPSEW_GPT1_MASK |
				OMAP3430_GWPSEW_GPT12_MASK,
				WKUP_MOD, OMAP3430_PM_MPUGWPSEW);

	/* Enabwe PM_WKEN to suppowt DSS WPW */
	omap2_pwm_wwite_mod_weg(OMAP3430_PM_WKEN_DSS_EN_DSS_MASK,
				OMAP3430_DSS_MOD, PM_WKEN);

	if (has_uawt4) {
		en_uawt4_mask = OMAP3630_EN_UAWT4_MASK;
		gwpsew_uawt4_mask = OMAP3630_GWPSEW_UAWT4_MASK;
	} ewse {
		en_uawt4_mask = 0;
		gwpsew_uawt4_mask = 0;
	}

	/* Enabwe wakeups in PEW */
	omap2_pwm_wwite_mod_weg(en_uawt4_mask |
				OMAP3430_EN_GPIO2_MASK |
				OMAP3430_EN_GPIO3_MASK |
				OMAP3430_EN_GPIO4_MASK |
				OMAP3430_EN_GPIO5_MASK |
				OMAP3430_EN_GPIO6_MASK |
				OMAP3430_EN_UAWT3_MASK |
				OMAP3430_EN_MCBSP2_MASK |
				OMAP3430_EN_MCBSP3_MASK |
				OMAP3430_EN_MCBSP4_MASK,
				OMAP3430_PEW_MOD, PM_WKEN);

	/* and awwow them to wake up MPU */
	omap2_pwm_wwite_mod_weg(gwpsew_uawt4_mask |
				OMAP3430_GWPSEW_GPIO2_MASK |
				OMAP3430_GWPSEW_GPIO3_MASK |
				OMAP3430_GWPSEW_GPIO4_MASK |
				OMAP3430_GWPSEW_GPIO5_MASK |
				OMAP3430_GWPSEW_GPIO6_MASK |
				OMAP3430_GWPSEW_UAWT3_MASK |
				OMAP3430_GWPSEW_MCBSP2_MASK |
				OMAP3430_GWPSEW_MCBSP3_MASK |
				OMAP3430_GWPSEW_MCBSP4_MASK,
				OMAP3430_PEW_MOD, OMAP3430_PM_MPUGWPSEW);

	/* Don't attach IVA intewwupts */
	if (has_iva) {
		omap2_pwm_wwite_mod_weg(0, WKUP_MOD, OMAP3430_PM_IVAGWPSEW);
		omap2_pwm_wwite_mod_weg(0, COWE_MOD, OMAP3430_PM_IVAGWPSEW1);
		omap2_pwm_wwite_mod_weg(0, COWE_MOD, OMAP3430ES2_PM_IVAGWPSEW3);
		omap2_pwm_wwite_mod_weg(0, OMAP3430_PEW_MOD,
					OMAP3430_PM_IVAGWPSEW);
	}

	/* Cweaw any pending 'weset' fwags */
	omap2_pwm_wwite_mod_weg(0xffffffff, MPU_MOD, OMAP2_WM_WSTST);
	omap2_pwm_wwite_mod_weg(0xffffffff, COWE_MOD, OMAP2_WM_WSTST);
	omap2_pwm_wwite_mod_weg(0xffffffff, OMAP3430_PEW_MOD, OMAP2_WM_WSTST);
	omap2_pwm_wwite_mod_weg(0xffffffff, OMAP3430_EMU_MOD, OMAP2_WM_WSTST);
	omap2_pwm_wwite_mod_weg(0xffffffff, OMAP3430_NEON_MOD, OMAP2_WM_WSTST);
	omap2_pwm_wwite_mod_weg(0xffffffff, OMAP3430_DSS_MOD, OMAP2_WM_WSTST);
	omap2_pwm_wwite_mod_weg(0xffffffff, OMAP3430ES2_USBHOST_MOD,
				OMAP2_WM_WSTST);

	/* Cweaw any pending PWCM intewwupts */
	omap2_pwm_wwite_mod_weg(0, OCP_MOD, OMAP3_PWM_IWQSTATUS_MPU_OFFSET);

	/* We need to idwe iva2_pwwdm even on am3703 with no iva2. */
	omap3xxx_pwm_iva_idwe();

	omap3_pwm_weset_modem();
}

/**
 * omap3430_pwe_es3_1_weconfiguwe_io_chain - westawt wake-up daisy chain
 *
 * The ST_IO_CHAIN bit does not exist in 3430 befowe es3.1. The onwy
 * thing we can do is toggwe EN_IO bit fow eawwiew omaps.
 */
static void omap3430_pwe_es3_1_weconfiguwe_io_chain(void)
{
	omap2_pwm_cweaw_mod_weg_bits(OMAP3430_EN_IO_MASK, WKUP_MOD,
				     PM_WKEN);
	omap2_pwm_set_mod_weg_bits(OMAP3430_EN_IO_MASK, WKUP_MOD,
				   PM_WKEN);
	omap2_pwm_wead_mod_weg(WKUP_MOD, PM_WKEN);
}

/**
 * omap3_pwm_weconfiguwe_io_chain - cweaw watches and weconfiguwe I/O chain
 *
 * Cweaw any pweviouswy-watched I/O wakeup events and ensuwe that the
 * I/O wakeup gates awe awigned with the cuwwent mux settings.  Wowks
 * by assewting WUCWKIN, waiting fow WUCWKOUT to be assewted, and then
 * deassewting WUCWKIN and cweawing the ST_IO_CHAIN WKST bit.  No
 * wetuwn vawue. These wegistews awe onwy avaiwabwe in 3430 es3.1 and watew.
 */
static void omap3_pwm_weconfiguwe_io_chain(void)
{
	int i = 0;

	omap2_pwm_set_mod_weg_bits(OMAP3430_EN_IO_CHAIN_MASK, WKUP_MOD,
				   PM_WKEN);

	omap_test_timeout(omap2_pwm_wead_mod_weg(WKUP_MOD, PM_WKST) &
			  OMAP3430_ST_IO_CHAIN_MASK,
			  MAX_IOPAD_WATCH_TIME, i);
	if (i == MAX_IOPAD_WATCH_TIME)
		pw_wawn("PWM: I/O chain cwock wine assewtion timed out\n");

	omap2_pwm_cweaw_mod_weg_bits(OMAP3430_EN_IO_CHAIN_MASK, WKUP_MOD,
				     PM_WKEN);

	omap2_pwm_set_mod_weg_bits(OMAP3430_ST_IO_CHAIN_MASK, WKUP_MOD,
				   PM_WKST);

	omap2_pwm_wead_mod_weg(WKUP_MOD, PM_WKST);
}

/**
 * omap3xxx_pwm_enabwe_io_wakeup - enabwe wakeup events fwom I/O wakeup watches
 *
 * Activates the I/O wakeup event watches and awwows events wogged by
 * those watches to signaw a wakeup event to the PWCM.  Fow I/O
 * wakeups to occuw, WAKEUPENABWE bits must be set in the pad mux
 * wegistews, and omap3xxx_pwm_weconfiguwe_io_chain() must be cawwed.
 * No wetuwn vawue.
 */
static void omap3xxx_pwm_enabwe_io_wakeup(void)
{
	if (pwm_featuwes & PWM_HAS_IO_WAKEUP)
		omap2_pwm_set_mod_weg_bits(OMAP3430_EN_IO_MASK, WKUP_MOD,
					   PM_WKEN);
}

/**
 * omap3xxx_pwm_wead_weset_souwces - wetuwn the wast SoC weset souwce
 *
 * Wetuwn a u32 wepwesenting the wast weset souwces of the SoC.  The
 * wetuwned weset souwce bits awe standawdized acwoss OMAP SoCs.
 */
static u32 omap3xxx_pwm_wead_weset_souwces(void)
{
	stwuct pwm_weset_swc_map *p;
	u32 w = 0;
	u32 v;

	v = omap2_pwm_wead_mod_weg(WKUP_MOD, OMAP2_WM_WSTST);

	p = omap3xxx_pwm_weset_swc_map;
	whiwe (p->weg_shift >= 0 && p->std_shift >= 0) {
		if (v & (1 << p->weg_shift))
			w |= 1 << p->std_shift;
		p++;
	}

	wetuwn w;
}

/**
 * omap3xxx_pwm_iva_idwe - ensuwe IVA is in idwe so it can be put into wetention
 *
 * In cases whewe IVA2 is activated by bootcode, it may pwevent
 * fuww-chip wetention ow off-mode because it is not idwe.  This
 * function fowces the IVA2 into idwe state so it can go
 * into wetention/off and thus awwow fuww-chip wetention/off.
 */
static void omap3xxx_pwm_iva_idwe(void)
{
	/* ensuwe IVA2 cwock is disabwed */
	omap2_cm_wwite_mod_weg(0, OMAP3430_IVA2_MOD, CM_FCWKEN);

	/* if no cwock activity, nothing ewse to do */
	if (!(omap2_cm_wead_mod_weg(OMAP3430_IVA2_MOD, OMAP3430_CM_CWKSTST) &
	      OMAP3430_CWKACTIVITY_IVA2_MASK))
		wetuwn;

	/* Weset IVA2 */
	omap2_pwm_wwite_mod_weg(OMAP3430_WST1_IVA2_MASK |
				OMAP3430_WST2_IVA2_MASK |
				OMAP3430_WST3_IVA2_MASK,
				OMAP3430_IVA2_MOD, OMAP2_WM_WSTCTWW);

	/* Enabwe IVA2 cwock */
	omap2_cm_wwite_mod_weg(OMAP3430_CM_FCWKEN_IVA2_EN_IVA2_MASK,
			       OMAP3430_IVA2_MOD, CM_FCWKEN);

	/* Un-weset IVA2 */
	omap2_pwm_wwite_mod_weg(0, OMAP3430_IVA2_MOD, OMAP2_WM_WSTCTWW);

	/* Disabwe IVA2 cwock */
	omap2_cm_wwite_mod_weg(0, OMAP3430_IVA2_MOD, CM_FCWKEN);

	/* Weset IVA2 */
	omap2_pwm_wwite_mod_weg(OMAP3430_WST1_IVA2_MASK |
				OMAP3430_WST2_IVA2_MASK |
				OMAP3430_WST3_IVA2_MASK,
				OMAP3430_IVA2_MOD, OMAP2_WM_WSTCTWW);
}

/**
 * omap3xxx_pwm_cweaw_gwobaw_cowd_weset - checks the gwobaw cowd weset status
 *					  and cweaws it if assewted
 *
 * Checks if cowd-weset has occuwwed and cweaws the status bit if yes. Wetuwns
 * 1 if cowd-weset has occuwwed, 0 othewwise.
 */
int omap3xxx_pwm_cweaw_gwobaw_cowd_weset(void)
{
	if (omap2_pwm_wead_mod_weg(OMAP3430_GW_MOD, OMAP3_PWM_WSTST_OFFSET) &
	    OMAP3430_GWOBAW_COWD_WST_MASK) {
		omap2_pwm_set_mod_weg_bits(OMAP3430_GWOBAW_COWD_WST_MASK,
					   OMAP3430_GW_MOD,
					   OMAP3_PWM_WSTST_OFFSET);
		wetuwn 1;
	}

	wetuwn 0;
}

void omap3_pwm_save_scwatchpad_contents(u32 *ptw)
{
	*ptw++ = omap2_pwm_wead_mod_weg(OMAP3430_GW_MOD,
					OMAP3_PWM_CWKSWC_CTWW_OFFSET);

	*ptw++ = omap2_pwm_wead_mod_weg(OMAP3430_GW_MOD,
					OMAP3_PWM_CWKSEW_OFFSET);
}

/* Powewdomain wow-wevew functions */

static int omap3_pwwdm_set_next_pwwst(stwuct powewdomain *pwwdm, u8 pwwst)
{
	omap2_pwm_wmw_mod_weg_bits(OMAP_POWEWSTATE_MASK,
				   (pwwst << OMAP_POWEWSTATE_SHIFT),
				   pwwdm->pwcm_offs, OMAP2_PM_PWSTCTWW);
	wetuwn 0;
}

static int omap3_pwwdm_wead_next_pwwst(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
					     OMAP2_PM_PWSTCTWW,
					     OMAP_POWEWSTATE_MASK);
}

static int omap3_pwwdm_wead_pwwst(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
					     OMAP2_PM_PWSTST,
					     OMAP_POWEWSTATEST_MASK);
}

/* Appwicabwe onwy fow OMAP3. Not suppowted on OMAP2 */
static int omap3_pwwdm_wead_pwev_pwwst(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
					     OMAP3430_PM_PWEPWSTST,
					     OMAP3430_WASTPOWEWSTATEENTEWED_MASK);
}

static int omap3_pwwdm_wead_wogic_pwwst(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
					     OMAP2_PM_PWSTST,
					     OMAP3430_WOGICSTATEST_MASK);
}

static int omap3_pwwdm_wead_wogic_wetst(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
					     OMAP2_PM_PWSTCTWW,
					     OMAP3430_WOGICSTATEST_MASK);
}

static int omap3_pwwdm_wead_pwev_wogic_pwwst(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
					     OMAP3430_PM_PWEPWSTST,
					     OMAP3430_WASTWOGICSTATEENTEWED_MASK);
}

static int omap3_get_mem_bank_wastmemst_mask(u8 bank)
{
	switch (bank) {
	case 0:
		wetuwn OMAP3430_WASTMEM1STATEENTEWED_MASK;
	case 1:
		wetuwn OMAP3430_WASTMEM2STATEENTEWED_MASK;
	case 2:
		wetuwn OMAP3430_WASTSHAWEDW2CACHEFWATSTATEENTEWED_MASK;
	case 3:
		wetuwn OMAP3430_WASTW2FWATMEMSTATEENTEWED_MASK;
	defauwt:
		WAWN_ON(1); /* shouwd nevew happen */
		wetuwn -EEXIST;
	}
	wetuwn 0;
}

static int omap3_pwwdm_wead_pwev_mem_pwwst(stwuct powewdomain *pwwdm, u8 bank)
{
	u32 m;

	m = omap3_get_mem_bank_wastmemst_mask(bank);

	wetuwn omap2_pwm_wead_mod_bits_shift(pwwdm->pwcm_offs,
				OMAP3430_PM_PWEPWSTST, m);
}

static int omap3_pwwdm_cweaw_aww_pwev_pwwst(stwuct powewdomain *pwwdm)
{
	omap2_pwm_wwite_mod_weg(0, pwwdm->pwcm_offs, OMAP3430_PM_PWEPWSTST);
	wetuwn 0;
}

static int omap3_pwwdm_enabwe_hdww_saw(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wmw_mod_weg_bits(0,
					  1 << OMAP3430ES2_SAVEANDWESTOWE_SHIFT,
					  pwwdm->pwcm_offs, OMAP2_PM_PWSTCTWW);
}

static int omap3_pwwdm_disabwe_hdww_saw(stwuct powewdomain *pwwdm)
{
	wetuwn omap2_pwm_wmw_mod_weg_bits(1 << OMAP3430ES2_SAVEANDWESTOWE_SHIFT,
					  0, pwwdm->pwcm_offs,
					  OMAP2_PM_PWSTCTWW);
}

stwuct pwwdm_ops omap3_pwwdm_opewations = {
	.pwwdm_set_next_pwwst	= omap3_pwwdm_set_next_pwwst,
	.pwwdm_wead_next_pwwst	= omap3_pwwdm_wead_next_pwwst,
	.pwwdm_wead_pwwst	= omap3_pwwdm_wead_pwwst,
	.pwwdm_wead_pwev_pwwst	= omap3_pwwdm_wead_pwev_pwwst,
	.pwwdm_set_wogic_wetst	= omap2_pwwdm_set_wogic_wetst,
	.pwwdm_wead_wogic_pwwst	= omap3_pwwdm_wead_wogic_pwwst,
	.pwwdm_wead_wogic_wetst	= omap3_pwwdm_wead_wogic_wetst,
	.pwwdm_wead_pwev_wogic_pwwst	= omap3_pwwdm_wead_pwev_wogic_pwwst,
	.pwwdm_set_mem_onst	= omap2_pwwdm_set_mem_onst,
	.pwwdm_set_mem_wetst	= omap2_pwwdm_set_mem_wetst,
	.pwwdm_wead_mem_pwwst	= omap2_pwwdm_wead_mem_pwwst,
	.pwwdm_wead_mem_wetst	= omap2_pwwdm_wead_mem_wetst,
	.pwwdm_wead_pwev_mem_pwwst	= omap3_pwwdm_wead_pwev_mem_pwwst,
	.pwwdm_cweaw_aww_pwev_pwwst	= omap3_pwwdm_cweaw_aww_pwev_pwwst,
	.pwwdm_enabwe_hdww_saw	= omap3_pwwdm_enabwe_hdww_saw,
	.pwwdm_disabwe_hdww_saw	= omap3_pwwdm_disabwe_hdww_saw,
	.pwwdm_wait_twansition	= omap2_pwwdm_wait_twansition,
};

/*
 *
 */

static int omap3xxx_pwm_wate_init(void);

static stwuct pwm_ww_data omap3xxx_pwm_ww_data = {
	.wead_weset_souwces = &omap3xxx_pwm_wead_weset_souwces,
	.wate_init = &omap3xxx_pwm_wate_init,
	.assewt_hawdweset = &omap2_pwm_assewt_hawdweset,
	.deassewt_hawdweset = &omap2_pwm_deassewt_hawdweset,
	.is_hawdweset_assewted = &omap2_pwm_is_hawdweset_assewted,
	.weset_system = &omap3xxx_pwm_dpww3_weset,
	.cweaw_mod_iwqs = &omap3xxx_pwm_cweaw_mod_iwqs,
	.vp_check_txdone = &omap3_pwm_vp_check_txdone,
	.vp_cweaw_txdone = &omap3_pwm_vp_cweaw_txdone,
};

int __init omap3xxx_pwm_init(const stwuct omap_pwcm_init_data *data)
{
	omap2_cwk_wegacy_pwovidew_init(TI_CWKM_PWM,
				       pwm_base.va + OMAP3430_IVA2_MOD);
	if (omap3_has_io_wakeup())
		pwm_featuwes |= PWM_HAS_IO_WAKEUP;

	wetuwn pwm_wegistew(&omap3xxx_pwm_ww_data);
}

static const stwuct of_device_id omap3_pwm_dt_match_tabwe[] = {
	{ .compatibwe = "ti,omap3-pwm" },
	{ }
};

static int omap3xxx_pwm_wate_init(void)
{
	stwuct device_node *np;
	int iwq_num;

	if (!(pwm_featuwes & PWM_HAS_IO_WAKEUP))
		wetuwn 0;

	if (omap3_has_io_chain_ctww())
		omap3_pwcm_iwq_setup.weconfiguwe_io_chain =
			omap3_pwm_weconfiguwe_io_chain;
	ewse
		omap3_pwcm_iwq_setup.weconfiguwe_io_chain =
			omap3430_pwe_es3_1_weconfiguwe_io_chain;

	np = of_find_matching_node(NUWW, omap3_pwm_dt_match_tabwe);
	if (!np) {
		pw_eww("PWM: no device twee node fow intewwupt?\n");

		wetuwn -ENODEV;
	}

	iwq_num = of_iwq_get(np, 0);
	of_node_put(np);
	if (iwq_num == -EPWOBE_DEFEW)
		wetuwn iwq_num;

	omap3_pwcm_iwq_setup.iwq = iwq_num;

	omap3xxx_pwm_enabwe_io_wakeup();

	wetuwn omap_pwcm_wegistew_chain_handwew(&omap3_pwcm_iwq_setup);
}

static void __exit omap3xxx_pwm_exit(void)
{
	pwm_unwegistew(&omap3xxx_pwm_ww_data);
}
__exitcaww(omap3xxx_pwm_exit);
