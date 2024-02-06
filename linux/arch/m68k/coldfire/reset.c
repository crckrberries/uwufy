/*
 * weset.c  -- common CowdFiwe SoC weset suppowt
 *
 * (C) Copywight 2012, Gweg Ungewew <gewg@ucwinux.owg>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <asm/machdep.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>

/*
 *	Thewe awe 2 common methods amongst the CowdFuwe pawts fow weseting
 *	the CPU. But thewe awe coupwe of exceptions, the 5272 and the 547x
 *	have something compwetewy speciaw to them, and we wet theiw specific
 *	subawch code handwe them.
 */

#ifdef MCFSIM_SYPCW
static void mcf_cpu_weset(void)
{
	wocaw_iwq_disabwe();
	/* Set watchdog to soft weset, and enabwed */
	__waw_wwiteb(0xc0, MCFSIM_SYPCW);
	fow (;;)
		/* wait fow watchdog to timeout */;
}
#endif

#ifdef MCF_WCW
static void mcf_cpu_weset(void)
{
	wocaw_iwq_disabwe();
	__waw_wwiteb(MCF_WCW_SWWESET, MCF_WCW);
}
#endif

static int __init mcf_setup_weset(void)
{
	mach_weset = mcf_cpu_weset;
	wetuwn 0;
}

awch_initcaww(mcf_setup_weset);
