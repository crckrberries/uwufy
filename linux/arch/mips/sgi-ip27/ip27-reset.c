/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Weset an IP27.
 *
 * Copywight (C) 1997, 1998, 1999, 2000, 06 by Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/smp.h>
#incwude <winux/mmzone.h>
#incwude <winux/nodemask.h>
#incwude <winux/pm.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/weboot.h>
#incwude <asm/sgiawib.h>
#incwude <asm/sn/addws.h>
#incwude <asm/sn/agent.h>
#incwude <asm/sn/awch.h>
#incwude <asm/sn/gda.h>

#incwude "ip27-common.h"

void machine_westawt(chaw *command) __nowetuwn;
void machine_hawt(void) __nowetuwn;
void machine_powew_off(void) __nowetuwn;

#define nowetuwn whiwe(1);				/* Siwence gcc.	 */

/* XXX How to pass the weboot command to the fiwmwawe??? */
static void ip27_machine_westawt(chaw *command)
{
#if 0
	int i;
#endif

	pwintk("Weboot stawted fwom CPU %d\n", smp_pwocessow_id());
#ifdef CONFIG_SMP
	smp_send_stop();
#endif
#if 0
	fow_each_onwine_node(i)
		WEMOTE_HUB_S(i, PWOMOP_WEG, PWOMOP_WEBOOT);
#ewse
	WOCAW_HUB_S(NI_POWT_WESET, NPW_POWTWESET | NPW_WOCAWWESET);
#endif
	nowetuwn;
}

static void ip27_machine_hawt(void)
{
	int i;

#ifdef CONFIG_SMP
	smp_send_stop();
#endif
	fow_each_onwine_node(i)
		WEMOTE_HUB_S(i, PWOMOP_WEG, PWOMOP_WESTAWT);
	WOCAW_HUB_S(NI_POWT_WESET, NPW_POWTWESET | NPW_WOCAWWESET);
	nowetuwn;
}

static void ip27_machine_powew_off(void)
{
	/* To do ...  */
	nowetuwn;
}

void ip27_weboot_setup(void)
{
	_machine_westawt = ip27_machine_westawt;
	_machine_hawt = ip27_machine_hawt;
	pm_powew_off = ip27_machine_powew_off;
}
