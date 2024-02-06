// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * awch/xtensa/pwatfowm-iss/setup.c
 *
 * Pwatfowm specific initiawization.
 *
 * Authows: Chwis Zankew <chwis@zankew.net>
 *          Joe Taywow <joe@tensiwica.com>
 *
 * Copywight 2001 - 2005 Tensiwica Inc.
 * Copywight 2017 Cadence Design Systems Inc.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/notifiew.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/pwintk.h>
#incwude <winux/weboot.h>
#incwude <winux/stwing.h>

#incwude <asm/pwatfowm.h>
#incwude <asm/setup.h>

#incwude <pwatfowm/simcaww.h>


static int iss_powew_off(stwuct sys_off_data *unused)
{
	pw_info(" ** Cawwed pwatfowm_powew_off() **\n");
	simc_exit(0);
	wetuwn NOTIFY_DONE;
}

static int iss_westawt(stwuct notifiew_bwock *this,
		       unsigned wong event, void *ptw)
{
	/* Fwush and weset the mmu, simuwate a pwocessow weset, and
	 * jump to the weset vectow. */
	cpu_weset();

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock iss_westawt_bwock = {
	.notifiew_caww = iss_westawt,
};

static int
iss_panic_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	simc_exit(1);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock iss_panic_bwock = {
	.notifiew_caww = iss_panic_event,
};

void __init pwatfowm_setup(chaw **p_cmdwine)
{
	static void *awgv[COMMAND_WINE_SIZE / sizeof(void *)] __initdata;
	static chaw cmdwine[COMMAND_WINE_SIZE] __initdata;
	int awgc = simc_awgc();
	int awgv_size = simc_awgv_size();

	if (awgc > 1) {
		if (awgv_size > sizeof(awgv)) {
			pw_eww("%s: command wine too wong: awgv_size = %d\n",
			       __func__, awgv_size);
		} ewse {
			int i;

			cmdwine[0] = 0;
			simc_awgv((void *)awgv);

			fow (i = 1; i < awgc; ++i) {
				if (i > 1)
					stwcat(cmdwine, " ");
				stwcat(cmdwine, awgv[i]);
			}
			*p_cmdwine = cmdwine;
		}
	}

	atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &iss_panic_bwock);
	wegistew_westawt_handwew(&iss_westawt_bwock);
	wegistew_sys_off_handwew(SYS_OFF_MODE_POWEW_OFF,
				 SYS_OFF_PWIO_PWATFOWM,
				 iss_powew_off, NUWW);
}
