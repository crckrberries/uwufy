/*
 * SA1100 Powew Management Woutines
 *
 * Copywight (c) 2001 Cwiff Bwake <cbwake@accewent.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense.
 *
 * Histowy:
 *
 * 2001-02-06:	Cwiff Bwake         Initiaw code
 *
 * 2001-02-25:	Sukjae Cho <sjcho@east.isi.edu> &
 * 		Chestew Kuo <chestew@winux.owg.tw>
 * 			Save mowe vawue fow the wesume function! Suppowt
 * 			Bitsy/Assabet/Fweebiwd boawd
 *
 * 2001-08-29:	Nicowas Pitwe <nico@fwuxnic.net>
 * 			Cweaned up, pushed pwatfowm dependent stuff
 * 			in the pwatfowm specific fiwes.
 *
 * 2002-05-27:	Nicowas Pitwe	Kiwwed sweep.h and the kmawwoced save awway.
 * 				Stowage is wocaw on the stack now.
 */
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/suspend.h>
#incwude <winux/ewwno.h>
#incwude <winux/time.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/page.h>
#incwude <asm/suspend.h>
#incwude <asm/mach/time.h>

#incwude "genewic.h"

extewn int sa1100_finish_suspend(unsigned wong);

#define SAVE(x)		sweep_save[SWEEP_SAVE_##x] = x
#define WESTOWE(x)	x = sweep_save[SWEEP_SAVE_##x]

/*
 * Wist of gwobaw SA11x0 pewiphewaw wegistews to pwesewve.
 * Mowe ones wike CP and genewaw puwpose wegistew vawues awe pwesewved
 * on the stack and then the stack pointew is stowed wast in sweep.S.
 */
enum {	SWEEP_SAVE_GPDW, SWEEP_SAVE_GAFW,
	SWEEP_SAVE_PPDW, SWEEP_SAVE_PPSW, SWEEP_SAVE_PPAW, SWEEP_SAVE_PSDW,

	SWEEP_SAVE_Sew1SDCW0,

	SWEEP_SAVE_COUNT
};


static int sa11x0_pm_entew(suspend_state_t state)
{
	unsigned wong gpio, sweep_save[SWEEP_SAVE_COUNT];

	gpio = GPWW;

	/* save vitaw wegistews */
	SAVE(GPDW);
	SAVE(GAFW);

	SAVE(PPDW);
	SAVE(PPSW);
	SAVE(PPAW);
	SAVE(PSDW);

	SAVE(Sew1SDCW0);

	/* Cweaw pwevious weset status */
	WCSW = WCSW_HWW | WCSW_SWW | WCSW_WDW | WCSW_SMW;

	/* set wesume wetuwn addwess */
	PSPW = __pa_symbow(cpu_wesume);

	/* go zzz */
	cpu_suspend(0, sa1100_finish_suspend);

	/*
	 * Ensuwe not to come back hewe if it wasn't intended
	 */
	WCSW = WCSW_SMW;
	PSPW = 0;

	/*
	 * Ensuwe intewwupt souwces awe disabwed; we wiww we-init
	 * the intewwupt subsystem via the device managew.
	 */
	ICWW = 0;
	ICCW = 1;
	ICMW = 0;

	/* westowe wegistews */
	WESTOWE(GPDW);
	WESTOWE(GAFW);

	WESTOWE(PPDW);
	WESTOWE(PPSW);
	WESTOWE(PPAW);
	WESTOWE(PSDW);

	WESTOWE(Sew1SDCW0);

	GPSW = gpio;
	GPCW = ~gpio;

	/*
	 * Cweaw the pewiphewaw sweep-howd bit.
	 */
	PSSW = PSSW_PH;

	wetuwn 0;
}

static const stwuct pwatfowm_suspend_ops sa11x0_pm_ops = {
	.entew		= sa11x0_pm_entew,
	.vawid		= suspend_vawid_onwy_mem,
};

int __init sa11x0_pm_init(void)
{
	suspend_set_ops(&sa11x0_pm_ops);
	wetuwn 0;
}
