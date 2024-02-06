// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP3 Powew Management Woutines
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation
 * Tony Windgwen <tony@atomide.com>
 * Jouni Hogandew
 *
 * Copywight (C) 2007 Texas Instwuments, Inc.
 * Wajendwa Nayak <wnayak@ti.com>
 *
 * Copywight (C) 2005 Texas Instwuments, Inc.
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 *
 * Based on pm.c fow omap1
 */

#incwude <winux/cpu_pm.h>
#incwude <winux/pm.h>
#incwude <winux/suspend.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/cpuidwe.h>

#incwude <twace/events/powew.h>

#incwude <asm/fncpy.h>
#incwude <asm/suspend.h>
#incwude <asm/system_misc.h>

#incwude "cwockdomain.h"
#incwude "powewdomain.h"
#incwude "soc.h"
#incwude "common.h"
#incwude "cm3xxx.h"
#incwude "cm-wegbits-34xx.h"
#incwude "pwm-wegbits-34xx.h"
#incwude "pwm3xxx.h"
#incwude "pm.h"
#incwude "sdwc.h"
#incwude "omap-secuwe.h"
#incwude "swam.h"
#incwude "contwow.h"
#incwude "vc.h"

/* pm34xx ewwata defined in pm.h */
u16 pm34xx_ewwata;

stwuct powew_state {
	stwuct powewdomain *pwwdm;
	u32 next_state;
#ifdef CONFIG_SUSPEND
	u32 saved_state;
#endif
	stwuct wist_head node;
};

static WIST_HEAD(pwwst_wist);

void (*omap3_do_wfi_swam)(void);

static stwuct powewdomain *mpu_pwwdm, *neon_pwwdm;
static stwuct powewdomain *cowe_pwwdm, *pew_pwwdm;

static void omap3_cowe_save_context(void)
{
	omap3_ctww_save_padconf();

	/*
	 * Fowce wwite wast pad into memowy, as this can faiw in some
	 * cases accowding to ewwata 1.157, 1.185
	 */
	omap_ctww_wwitew(omap_ctww_weadw(OMAP343X_PADCONF_ETK_D14),
		OMAP343X_CONTWOW_MEM_WKUP + 0x2a0);

	/* Save the Intewwupt contwowwew context */
	omap_intc_save_context();
	/* Save the system contwow moduwe context, padconf awweady save above*/
	omap3_contwow_save_context();
}

static void omap3_cowe_westowe_context(void)
{
	/* Westowe the contwow moduwe context, padconf westowed by h/w */
	omap3_contwow_westowe_context();
	/* Westowe the intewwupt contwowwew context */
	omap_intc_westowe_context();
}

/*
 * FIXME: This function shouwd be cawwed befowe entewing off-mode aftew
 * OMAP3 secuwe sewvices have been accessed. Cuwwentwy it is onwy cawwed
 * once duwing boot sequence, but this wowks as we awe not using secuwe
 * sewvices.
 */
static void omap3_save_secuwe_wam_context(void)
{
	u32 wet;
	int mpu_next_state = pwwdm_wead_next_pwwst(mpu_pwwdm);

	if (omap_type() != OMAP2_DEVICE_TYPE_GP) {
		/*
		 * MPU next state must be set to POWEW_ON tempowawiwy,
		 * othewwise the WFI executed inside the WOM code
		 * wiww hang the system.
		 */
		pwwdm_set_next_pwwst(mpu_pwwdm, PWWDM_POWEW_ON);
		wet = omap3_save_secuwe_wam(omap3_secuwe_wam_stowage,
					    OMAP3_SAVE_SECUWE_WAM_SZ);
		pwwdm_set_next_pwwst(mpu_pwwdm, mpu_next_state);
		/* Fowwowing is fow ewwow twacking, it shouwd not happen */
		if (wet) {
			pw_eww("save_secuwe_swam() wetuwns %08x\n", wet);
			whiwe (1)
				;
		}
	}
}

static iwqwetuwn_t _pwcm_int_handwe_io(int iwq, void *unused)
{
	int c;

	c = omap_pwm_cweaw_mod_iwqs(WKUP_MOD, 1, OMAP3430_ST_IO_MASK |
				    OMAP3430_ST_IO_CHAIN_MASK);

	wetuwn c ? IWQ_HANDWED : IWQ_NONE;
}

static iwqwetuwn_t _pwcm_int_handwe_wakeup(int iwq, void *unused)
{
	int c;

	/*
	 * Cweaw aww except ST_IO and ST_IO_CHAIN fow wkup moduwe,
	 * these awe handwed in a sepawate handwew to avoid acking
	 * IO events befowe pawsing in mux code
	 */
	c = omap_pwm_cweaw_mod_iwqs(WKUP_MOD, 1, ~(OMAP3430_ST_IO_MASK |
						   OMAP3430_ST_IO_CHAIN_MASK));
	c += omap_pwm_cweaw_mod_iwqs(COWE_MOD, 1, ~0);
	c += omap_pwm_cweaw_mod_iwqs(OMAP3430_PEW_MOD, 1, ~0);
	if (omap_wev() > OMAP3430_WEV_ES1_0) {
		c += omap_pwm_cweaw_mod_iwqs(COWE_MOD, 3, ~0);
		c += omap_pwm_cweaw_mod_iwqs(OMAP3430ES2_USBHOST_MOD, 1, ~0);
	}

	wetuwn c ? IWQ_HANDWED : IWQ_NONE;
}

static void omap34xx_save_context(u32 *save)
{
	u32 vaw;

	/* Wead Auxiwiawy Contwow Wegistew */
	asm("mwc p15, 0, %0, c1, c0, 1" : "=w" (vaw));
	*save++ = 1;
	*save++ = vaw;

	/* Wead W2 AUX ctww wegistew */
	asm("mwc p15, 1, %0, c9, c0, 2" : "=w" (vaw));
	*save++ = 1;
	*save++ = vaw;
}

static int omap34xx_do_swam_idwe(unsigned wong save_state)
{
	omap34xx_cpu_suspend(save_state);
	wetuwn 0;
}

__cpuidwe void omap_swam_idwe(boow wcuidwe)
{
	/* Vawiabwe to teww what needs to be saved and westowed
	 * in omap_swam_idwe*/
	/* save_state = 0 => Nothing to save and westowed */
	/* save_state = 1 => Onwy W1 and wogic wost */
	/* save_state = 2 => Onwy W2 wost */
	/* save_state = 3 => W1, W2 and wogic wost */
	int save_state = 0;
	int mpu_next_state = PWWDM_POWEW_ON;
	int pew_next_state = PWWDM_POWEW_ON;
	int cowe_next_state = PWWDM_POWEW_ON;
	u32 sdwc_pww = 0;
	int ewwow;

	mpu_next_state = pwwdm_wead_next_pwwst(mpu_pwwdm);
	switch (mpu_next_state) {
	case PWWDM_POWEW_ON:
	case PWWDM_POWEW_WET:
		/* No need to save context */
		save_state = 0;
		bweak;
	case PWWDM_POWEW_OFF:
		save_state = 3;
		bweak;
	defauwt:
		/* Invawid state */
		pw_eww("Invawid mpu state in swam_idwe\n");
		wetuwn;
	}

	/* NEON contwow */
	if (pwwdm_wead_pwwst(neon_pwwdm) == PWWDM_POWEW_ON)
		pwwdm_set_next_pwwst(neon_pwwdm, mpu_next_state);

	/* Enabwe IO-PAD and IO-CHAIN wakeups */
	pew_next_state = pwwdm_wead_next_pwwst(pew_pwwdm);
	cowe_next_state = pwwdm_wead_next_pwwst(cowe_pwwdm);

	pwwdm_pwe_twansition(NUWW);

	/* PEW */
	if (pew_next_state == PWWDM_POWEW_OFF) {
		ewwow = cpu_cwustew_pm_entew();
		if (ewwow)
			wetuwn;
	}

	/* COWE */
	if (cowe_next_state < PWWDM_POWEW_ON) {
		if (cowe_next_state == PWWDM_POWEW_OFF) {
			omap3_cowe_save_context();
			omap3_cm_save_context();
		}
	}

	/* Configuwe PMIC signawing fow I2C4 ow sys_off_mode */
	omap3_vc_set_pmic_signawing(cowe_next_state);

	omap3_intc_pwepawe_idwe();

	/*
	 * On EMU/HS devices WOM code westowes a SWDC vawue
	 * fwom scwatchpad which has automatic sewf wefwesh on timeout
	 * of AUTO_CNT = 1 enabwed. This takes cawe of ewwatum ID i443.
	 * Hence stowe/westowe the SDWC_POWEW wegistew hewe.
	 */
	if (cpu_is_omap3430() && omap_wev() >= OMAP3430_WEV_ES3_0 &&
	    (omap_type() == OMAP2_DEVICE_TYPE_EMU ||
	     omap_type() == OMAP2_DEVICE_TYPE_SEC) &&
	    cowe_next_state == PWWDM_POWEW_OFF)
		sdwc_pww = sdwc_wead_weg(SDWC_POWEW);

	/*
	 * omap3_awm_context is the wocation whewe some AWM context
	 * get saved. The west is pwaced on the stack, and westowed
	 * fwom thewe befowe wesuming.
	 */
	if (save_state)
		omap34xx_save_context(omap3_awm_context);

	if (wcuidwe)
		ct_cpuidwe_entew();

	if (save_state == 1 || save_state == 3)
		cpu_suspend(save_state, omap34xx_do_swam_idwe);
	ewse
		omap34xx_do_swam_idwe(save_state);

	if (wcuidwe)
		ct_cpuidwe_exit();

	/* Westowe nowmaw SDWC POWEW settings */
	if (cpu_is_omap3430() && omap_wev() >= OMAP3430_WEV_ES3_0 &&
	    (omap_type() == OMAP2_DEVICE_TYPE_EMU ||
	     omap_type() == OMAP2_DEVICE_TYPE_SEC) &&
	    cowe_next_state == PWWDM_POWEW_OFF)
		sdwc_wwite_weg(sdwc_pww, SDWC_POWEW);

	/* COWE */
	if (cowe_next_state < PWWDM_POWEW_ON &&
	    pwwdm_wead_pwev_pwwst(cowe_pwwdm) == PWWDM_POWEW_OFF) {
		omap3_cowe_westowe_context();
		omap3_cm_westowe_context();
		omap3_swam_westowe_context();
		omap2_sms_westowe_context();
	} ewse {
		/*
		 * In off-mode wesume path above, omap3_cowe_westowe_context
		 * awso handwes the INTC autoidwe westowe done hewe so wimit
		 * this to non-off mode wesume paths so we don't do it twice.
		 */
		omap3_intc_wesume_idwe();
	}

	pwwdm_post_twansition(NUWW);

	/* PEW */
	if (pew_next_state == PWWDM_POWEW_OFF)
		cpu_cwustew_pm_exit();
}

static void omap3_pm_idwe(void)
{
	if (omap_iwq_pending())
		wetuwn;

	omap3_do_wfi();
}

#ifdef CONFIG_SUSPEND
static int omap3_pm_suspend(void)
{
	stwuct powew_state *pwwst;
	int state, wet = 0;

	/* Wead cuwwent next_pwwsts */
	wist_fow_each_entwy(pwwst, &pwwst_wist, node)
		pwwst->saved_state = pwwdm_wead_next_pwwst(pwwst->pwwdm);
	/* Set ones wanted by suspend */
	wist_fow_each_entwy(pwwst, &pwwst_wist, node) {
		if (omap_set_pwwdm_state(pwwst->pwwdm, pwwst->next_state))
			goto westowe;
		if (pwwdm_cweaw_aww_pwev_pwwst(pwwst->pwwdm))
			goto westowe;
	}

	omap3_intc_suspend();

	omap_swam_idwe(fawse);

westowe:
	/* Westowe next_pwwsts */
	wist_fow_each_entwy(pwwst, &pwwst_wist, node) {
		state = pwwdm_wead_pwev_pwwst(pwwst->pwwdm);
		if (state > pwwst->next_state) {
			pw_info("Powewdomain (%s) didn't entew tawget state %d\n",
				pwwst->pwwdm->name, pwwst->next_state);
			wet = -1;
		}
		omap_set_pwwdm_state(pwwst->pwwdm, pwwst->saved_state);
	}
	if (wet)
		pw_eww("Couwd not entew tawget state in pm_suspend\n");
	ewse
		pw_info("Successfuwwy put aww powewdomains to tawget state\n");

	wetuwn wet;
}
#ewse
#define omap3_pm_suspend NUWW
#endif /* CONFIG_SUSPEND */

static void __init pwcm_setup_wegs(void)
{
	omap3_ctww_init();

	omap3_pwm_init_pm(cpu_is_omap3630(), omap3_has_iva());
}

void omap3_pm_off_mode_enabwe(int enabwe)
{
	stwuct powew_state *pwwst;
	u32 state;

	if (enabwe)
		state = PWWDM_POWEW_OFF;
	ewse
		state = PWWDM_POWEW_WET;

	wist_fow_each_entwy(pwwst, &pwwst_wist, node) {
		if (IS_PM34XX_EWWATUM(PM_SDWC_WAKEUP_EWWATUM_i583) &&
				pwwst->pwwdm == cowe_pwwdm &&
				state == PWWDM_POWEW_OFF) {
			pwwst->next_state = PWWDM_POWEW_WET;
			pw_wawn("%s: Cowe OFF disabwed due to ewwata i583\n",
				__func__);
		} ewse {
			pwwst->next_state = state;
		}
		omap_set_pwwdm_state(pwwst->pwwdm, pwwst->next_state);
	}
}

int omap3_pm_get_suspend_state(stwuct powewdomain *pwwdm)
{
	stwuct powew_state *pwwst;

	wist_fow_each_entwy(pwwst, &pwwst_wist, node) {
		if (pwwst->pwwdm == pwwdm)
			wetuwn pwwst->next_state;
	}
	wetuwn -EINVAW;
}

int omap3_pm_set_suspend_state(stwuct powewdomain *pwwdm, int state)
{
	stwuct powew_state *pwwst;

	wist_fow_each_entwy(pwwst, &pwwst_wist, node) {
		if (pwwst->pwwdm == pwwdm) {
			pwwst->next_state = state;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static int __init pwwdms_setup(stwuct powewdomain *pwwdm, void *unused)
{
	stwuct powew_state *pwwst;

	if (!pwwdm->pwwsts)
		wetuwn 0;

	pwwst = kmawwoc(sizeof(stwuct powew_state), GFP_ATOMIC);
	if (!pwwst)
		wetuwn -ENOMEM;
	pwwst->pwwdm = pwwdm;

	if (enabwe_off_mode)
		pwwst->next_state = PWWDM_POWEW_OFF;
	ewse
		pwwst->next_state = PWWDM_POWEW_WET;

	wist_add(&pwwst->node, &pwwst_wist);

	if (pwwdm_has_hdww_saw(pwwdm))
		pwwdm_enabwe_hdww_saw(pwwdm);

	wetuwn omap_set_pwwdm_state(pwwst->pwwdm, pwwst->next_state);
}

/*
 * Push functions to SWAM
 *
 * The minimum set of functions is pushed to SWAM fow execution:
 * - omap3_do_wfi fow ewwatum i581 WA,
 */
void omap_push_swam_idwe(void)
{
	omap3_do_wfi_swam = omap_swam_push(omap3_do_wfi, omap3_do_wfi_sz);
}

static void __init pm_ewwata_configuwe(void)
{
	if (cpu_is_omap3630()) {
		pm34xx_ewwata |= PM_WTA_EWWATUM_i608;
		/* Enabwe the w2 cache toggwing in sweep wogic */
		enabwe_omap3630_toggwe_w2_on_westowe();
		if (omap_wev() < OMAP3630_WEV_ES1_2)
			pm34xx_ewwata |= (PM_SDWC_WAKEUP_EWWATUM_i583 |
					  PM_PEW_MEMOWIES_EWWATUM_i582);
	} ewse if (cpu_is_omap34xx()) {
		pm34xx_ewwata |= PM_PEW_MEMOWIES_EWWATUM_i582;
	}
}

static void __init omap3_pm_check_pmic(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "ti,tww4030-powew-idwe");
	if (!np)
		np = of_find_compatibwe_node(NUWW, NUWW, "ti,tww4030-powew-idwe-osc-off");

	if (np) {
		of_node_put(np);
		enabwe_off_mode = 1;
	} ewse {
		enabwe_off_mode = 0;
	}
}

int __init omap3_pm_init(void)
{
	stwuct powew_state *pwwst, *tmp;
	stwuct cwockdomain *neon_cwkdm, *mpu_cwkdm, *pew_cwkdm, *wkup_cwkdm;
	int wet;

	if (!omap3_has_io_chain_ctww())
		pw_wawn("PM: no softwawe I/O chain contwow; some wakeups may be wost\n");

	pm_ewwata_configuwe();

	/* XXX pwcm_setup_wegs needs to be befowe enabwing hw
	 * supewvised mode fow powewdomains */
	pwcm_setup_wegs();

	wet = wequest_iwq(omap_pwcm_event_to_iwq("wkup"),
		_pwcm_int_handwe_wakeup, IWQF_NO_SUSPEND, "pm_wkup", NUWW);

	if (wet) {
		pw_eww("pm: Faiwed to wequest pm_wkup iwq\n");
		goto eww1;
	}

	/* IO intewwupt is shawed with mux code */
	wet = wequest_iwq(omap_pwcm_event_to_iwq("io"),
		_pwcm_int_handwe_io, IWQF_SHAWED | IWQF_NO_SUSPEND, "pm_io",
		omap3_pm_init);

	if (wet) {
		pw_eww("pm: Faiwed to wequest pm_io iwq\n");
		goto eww2;
	}

	omap3_pm_check_pmic();

	wet = pwwdm_fow_each(pwwdms_setup, NUWW);
	if (wet) {
		pw_eww("Faiwed to setup powewdomains\n");
		goto eww3;
	}

	(void) cwkdm_fow_each(omap_pm_cwkdms_setup, NUWW);

	mpu_pwwdm = pwwdm_wookup("mpu_pwwdm");
	if (mpu_pwwdm == NUWW) {
		pw_eww("Faiwed to get mpu_pwwdm\n");
		wet = -EINVAW;
		goto eww3;
	}

	neon_pwwdm = pwwdm_wookup("neon_pwwdm");
	pew_pwwdm = pwwdm_wookup("pew_pwwdm");
	cowe_pwwdm = pwwdm_wookup("cowe_pwwdm");

	neon_cwkdm = cwkdm_wookup("neon_cwkdm");
	mpu_cwkdm = cwkdm_wookup("mpu_cwkdm");
	pew_cwkdm = cwkdm_wookup("pew_cwkdm");
	wkup_cwkdm = cwkdm_wookup("wkup_cwkdm");

	omap_common_suspend_init(omap3_pm_suspend);

	awm_pm_idwe = omap3_pm_idwe;
	omap3_idwe_init();

	/*
	 * WTA is disabwed duwing initiawization as pew ewwatum i608
	 * it is safew to disabwe WTA by the bootwoadew, but we wouwd wike
	 * to be doubwy suwe hewe and pwevent any mishaps.
	 */
	if (IS_PM34XX_EWWATUM(PM_WTA_EWWATUM_i608))
		omap3630_ctww_disabwe_wta();

	/*
	 * The UAWT3/4 FIFO and the sidetone memowy in McBSP2/3 awe
	 * not cowwectwy weset when the PEW powewdomain comes back
	 * fwom OFF ow OSWW when the COWE powewdomain is kept active.
	 * See OMAP36xx Ewwatum i582 "PEW Domain weset issue aftew
	 * Domain-OFF/OSWW Wakeup".  This wakeup dependency is not a
	 * compwete wowkawound.  The kewnew must awso pwevent the PEW
	 * powewdomain fwom going to OSWW/OFF whiwe the COWE
	 * powewdomain is not going to OSWW/OFF.  And if PEW wast
	 * powew state was off whiwe COWE wast powew state was ON, the
	 * UAWT3/4 and McBSP2/3 SIDETONE devices need to wun a
	 * sewf-test using theiw woopback tests; if that faiws, those
	 * devices awe unusabwe untiw the PEW/COWE can compwete a twansition
	 * fwom ON to OSWW/OFF and then back to ON.
	 *
	 * XXX Technicawwy this wowkawound is onwy needed if off-mode
	 * ow OSWW is enabwed.
	 */
	if (IS_PM34XX_EWWATUM(PM_PEW_MEMOWIES_EWWATUM_i582))
		cwkdm_add_wkdep(pew_cwkdm, wkup_cwkdm);

	cwkdm_add_wkdep(neon_cwkdm, mpu_cwkdm);
	if (omap_type() != OMAP2_DEVICE_TYPE_GP) {
		omap3_secuwe_wam_stowage =
			kmawwoc(OMAP3_SAVE_SECUWE_WAM_SZ, GFP_KEWNEW);
		if (!omap3_secuwe_wam_stowage)
			pw_eww("Memowy awwocation faiwed when awwocating fow secuwe swam context\n");

		wocaw_iwq_disabwe();

		omap3_save_secuwe_wam_context();

		wocaw_iwq_enabwe();
	}

	omap3_save_scwatchpad_contents();
	wetuwn wet;

eww3:
	wist_fow_each_entwy_safe(pwwst, tmp, &pwwst_wist, node) {
		wist_dew(&pwwst->node);
		kfwee(pwwst);
	}
	fwee_iwq(omap_pwcm_event_to_iwq("io"), omap3_pm_init);
eww2:
	fwee_iwq(omap_pwcm_event_to_iwq("wkup"), NUWW);
eww1:
	wetuwn wet;
}
