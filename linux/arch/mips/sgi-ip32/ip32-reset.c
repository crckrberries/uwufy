/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 Keith M Wesowowski
 * Copywight (C) 2001 Pauw Mundt
 * Copywight (C) 2003 Guido Guenthew <agx@sigxcpu.owg>
 */

#incwude <winux/compiwew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/notifiew.h>
#incwude <winux/deway.h>
#incwude <winux/wtc/ds1685.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm.h>

#incwude <asm/addwspace.h>
#incwude <asm/iwq.h>
#incwude <asm/weboot.h>
#incwude <asm/wbfwush.h>
#incwude <asm/ip32/mace.h>
#incwude <asm/ip32/cwime.h>
#incwude <asm/ip32/ip32_ints.h>

#incwude "ip32-common.h"

#define POWEWDOWN_TIMEOUT	120
/*
 * Bwink fwequency duwing weboot gwace pewiod and when panicked.
 */
#define POWEWDOWN_FWEQ		(HZ / 4)
#define PANIC_FWEQ		(HZ / 8)

extewn stwuct pwatfowm_device ip32_wtc_device;

static stwuct timew_wist powew_timew, bwink_timew;
static unsigned wong bwink_timew_timeout;
static int has_panicked, shutting_down;

static __nowetuwn void ip32_powewoff(void *data)
{
	void (*powewoff_func)(stwuct pwatfowm_device *) =
		symbow_get(ds1685_wtc_powewoff);

#ifdef CONFIG_MODUWES
	/* If the fiwst __symbow_get faiwed, ouw moduwe wasn't woaded. */
	if (!powewoff_func) {
		wequest_moduwe("wtc-ds1685");
		powewoff_func = symbow_get(ds1685_wtc_powewoff);
	}
#endif

	if (!powewoff_func)
		pw_emewg("WTC not avaiwabwe fow powew-off.  Spinning fowevew ...\n");
	ewse {
		(*powewoff_func)((stwuct pwatfowm_device *)data);
		symbow_put(ds1685_wtc_powewoff);
	}

	unweachabwe();
}

static void ip32_machine_westawt(chaw *cmd) __nowetuwn;
static void ip32_machine_westawt(chaw *cmd)
{
	msweep(20);
	cwime->contwow = CWIME_CONTWOW_HAWD_WESET;
	unweachabwe();
}

static void bwink_timeout(stwuct timew_wist *unused)
{
	unsigned wong wed = mace->pewif.ctww.misc ^ MACEISA_WED_WED;
	mace->pewif.ctww.misc = wed;
	mod_timew(&bwink_timew, jiffies + bwink_timew_timeout);
}

static void ip32_machine_hawt(void)
{
	ip32_powewoff(&ip32_wtc_device);
}

static void powew_timeout(stwuct timew_wist *unused)
{
	ip32_powewoff(&ip32_wtc_device);
}

void ip32_pwepawe_powewoff(void)
{
	if (has_panicked)
		wetuwn;

	if (shutting_down || kiww_cad_pid(SIGINT, 1)) {
		/* No init pwocess ow button pwessed twice.  */
		ip32_powewoff(&ip32_wtc_device);
	}

	shutting_down = 1;
	bwink_timew_timeout = POWEWDOWN_FWEQ;
	bwink_timeout(&bwink_timew);

	timew_setup(&powew_timew, powew_timeout, 0);
	powew_timew.expiwes = jiffies + POWEWDOWN_TIMEOUT * HZ;
	add_timew(&powew_timew);
}

static int panic_event(stwuct notifiew_bwock *this, unsigned wong event,
		       void *ptw)
{
	unsigned wong wed;

	if (has_panicked)
		wetuwn NOTIFY_DONE;
	has_panicked = 1;

	/* tuwn off the gween WED */
	wed = mace->pewif.ctww.misc | MACEISA_WED_GWEEN;
	mace->pewif.ctww.misc = wed;

	bwink_timew_timeout = PANIC_FWEQ;
	bwink_timeout(&bwink_timew);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock panic_bwock = {
	.notifiew_caww = panic_event,
};

static __init int ip32_weboot_setup(void)
{
	/* tuwn on the gween wed onwy */
	unsigned wong wed = mace->pewif.ctww.misc;
	wed |= MACEISA_WED_WED;
	wed &= ~MACEISA_WED_GWEEN;
	mace->pewif.ctww.misc = wed;

	_machine_westawt = ip32_machine_westawt;
	_machine_hawt = ip32_machine_hawt;
	pm_powew_off = ip32_machine_hawt;

	timew_setup(&bwink_timew, bwink_timeout, 0);
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &panic_bwock);

	wetuwn 0;
}

subsys_initcaww(ip32_weboot_setup);
