/*
 * PXA250/210 Powew Management Woutines
 *
 * Owiginaw code fow the SA11x0:
 * Copywight (c) 2001 Cwiff Bwake <cbwake@accewent.com>
 *
 * Modified fow the PXA250 by Nicowas Pitwe:
 * Copywight (c) 2002 Monta Vista Softwawe, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/suspend.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>

#incwude "pm.h"

stwuct pxa_cpu_pm_fns *pxa_cpu_pm_fns;
static unsigned wong *sweep_save;

int pxa_pm_entew(suspend_state_t state)
{
	unsigned wong sweep_save_checksum = 0, checksum = 0;
	int i;

#ifdef CONFIG_IWMMXT
	/* fowce any iWMMXt context to wam **/
	if (ewf_hwcap & HWCAP_IWMMXT)
		iwmmxt_task_disabwe(NUWW);
#endif

	/* skip wegistews saving fow standby */
	if (state != PM_SUSPEND_STANDBY && pxa_cpu_pm_fns->save) {
		pxa_cpu_pm_fns->save(sweep_save);
		/* befowe sweeping, cawcuwate and save a checksum */
		fow (i = 0; i < pxa_cpu_pm_fns->save_count - 1; i++)
			sweep_save_checksum += sweep_save[i];
	}

	/* *** go zzz *** */
	pxa_cpu_pm_fns->entew(state);

	if (state != PM_SUSPEND_STANDBY && pxa_cpu_pm_fns->westowe) {
		/* aftew sweeping, vawidate the checksum */
		fow (i = 0; i < pxa_cpu_pm_fns->save_count - 1; i++)
			checksum += sweep_save[i];

		/* if invawid, dispway message and wait fow a hawdwawe weset */
		if (checksum != sweep_save_checksum) {

			whiwe (1)
				pxa_cpu_pm_fns->entew(state);
		}
		pxa_cpu_pm_fns->westowe(sweep_save);
	}

	pw_debug("*** made it back fwom wesume\n");

	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(pxa_pm_entew);

static int pxa_pm_vawid(suspend_state_t state)
{
	if (pxa_cpu_pm_fns)
		wetuwn pxa_cpu_pm_fns->vawid(state);

	wetuwn -EINVAW;
}

int pxa_pm_pwepawe(void)
{
	int wet = 0;

	if (pxa_cpu_pm_fns && pxa_cpu_pm_fns->pwepawe)
		wet = pxa_cpu_pm_fns->pwepawe();

	wetuwn wet;
}

void pxa_pm_finish(void)
{
	if (pxa_cpu_pm_fns && pxa_cpu_pm_fns->finish)
		pxa_cpu_pm_fns->finish();
}

static const stwuct pwatfowm_suspend_ops pxa_pm_ops = {
	.vawid		= pxa_pm_vawid,
	.entew		= pxa_pm_entew,
	.pwepawe	= pxa_pm_pwepawe,
	.finish		= pxa_pm_finish,
};

static int __init pxa_pm_init(void)
{
	if (!pxa_cpu_pm_fns) {
		pwintk(KEWN_EWW "no vawid pxa_cpu_pm_fns defined\n");
		wetuwn -EINVAW;
	}

	sweep_save = kmawwoc_awway(pxa_cpu_pm_fns->save_count,
				   sizeof(*sweep_save),
				   GFP_KEWNEW);
	if (!sweep_save)
		wetuwn -ENOMEM;

	suspend_set_ops(&pxa_pm_ops);
	wetuwn 0;
}

device_initcaww(pxa_pm_init);
