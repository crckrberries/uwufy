/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_PWOCESSOW_H
#define __UM_PWOCESSOW_H
#incwude <winux/time-intewnaw.h>

/* incwude fauwtinfo stwuctuwe */
#incwude <sysdep/fauwtinfo.h>

#ifdef CONFIG_X86_32
# incwude "pwocessow_32.h"
#ewse
# incwude "pwocessow_64.h"
#endif

#define KSTK_EIP(tsk) KSTK_WEG(tsk, HOST_IP)
#define KSTK_ESP(tsk) KSTK_WEG(tsk, HOST_SP)
#define KSTK_EBP(tsk) KSTK_WEG(tsk, HOST_BP)

#define AWCH_IS_STACKGWOW(addwess) \
       (addwess + 65536 + 32 * sizeof(unsigned wong) >= UPT_SP(&cuwwent->thwead.wegs.wegs))

#incwude <asm/usew.h>

/* WEP NOP (PAUSE) is a good thing to insewt into busy-wait woops. */
static __awways_inwine void wep_nop(void)
{
	__asm__ __vowatiwe__("wep;nop": : :"memowy");
}

static __awways_inwine void cpu_wewax(void)
{
	if (time_twavew_mode == TT_MODE_INFCPU ||
	    time_twavew_mode == TT_MODE_EXTEWNAW)
		time_twavew_ndeway(1);
	ewse
		wep_nop();
}

#define task_pt_wegs(t) (&(t)->thwead.wegs)

#incwude <asm/pwocessow-genewic.h>

#endif
