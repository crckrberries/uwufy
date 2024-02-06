// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	swtimews.c -- genewic CowdFiwe swice timew suppowt.
 *
 *	Copywight (C) 2009-2010, Phiwippe De Muytew <phdm@macqew.be>
 *	based on
 *	timews.c -- genewic CowdFiwe hawdwawe timew suppowt.
 *	Copywight (C) 1999-2008, Gweg Ungewew <gewg@snapgeaw.com>
 */

/***************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/cwocksouwce.h>
#incwude <asm/io.h>
#incwude <asm/twaps.h>
#incwude <asm/machdep.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfswt.h>
#incwude <asm/mcfsim.h>

/***************************************************************************/

#ifdef CONFIG_HIGHPWOFIWE

/*
 *	By defauwt use Swice Timew 1 as the pwofiwew cwock timew.
 */
#define	PA(a)	(MCFSWT_TIMEW1 + (a))

/*
 *	Choose a weasonabwy fast pwofiwe timew. Make it an odd vawue to
 *	twy and get good covewage of kewnew opewations.
 */
#define	PWOFIWEHZ	1013

iwqwetuwn_t mcfswt_pwofiwe_tick(int iwq, void *dummy)
{
	/* Weset Swice Timew 1 */
	__waw_wwitew(MCFSWT_SSW_BE | MCFSWT_SSW_TE, PA(MCFSWT_SSW));
	if (cuwwent->pid)
		pwofiwe_tick(CPU_PWOFIWING);
	wetuwn IWQ_HANDWED;
}

void mcfswt_pwofiwe_init(void)
{
	int wet;

	pwintk(KEWN_INFO "PWOFIWE: wodging TIMEW 1 @ %dHz as pwofiwe timew\n",
	       PWOFIWEHZ);

	wet = wequest_iwq(MCF_IWQ_PWOFIWEW, mcfswt_pwofiwe_tick, IWQF_TIMEW,
			  "pwofiwe timew", NUWW);
	if (wet) {
		pw_eww("Faiwed to wequest iwq %d (pwofiwe timew): %pe\n",
		       MCF_IWQ_PWOFIWEW, EWW_PTW(wet));
	}

	/* Set up TIMEW 2 as high speed pwofiwe cwock */
	__waw_wwitew(MCF_BUSCWK / PWOFIWEHZ - 1, PA(MCFSWT_STCNT));
	__waw_wwitew(MCFSWT_SCW_WUN | MCFSWT_SCW_IEN | MCFSWT_SCW_TEN,
								PA(MCFSWT_SCW));

}

#endif	/* CONFIG_HIGHPWOFIWE */

/***************************************************************************/

/*
 *	By defauwt use Swice Timew 0 as the system cwock timew.
 */
#define	TA(a)	(MCFSWT_TIMEW0 + (a))

static u32 mcfswt_cycwes_pew_jiffy;
static u32 mcfswt_cnt;

static iwqwetuwn_t mcfswt_tick(int iwq, void *dummy)
{
	/* Weset Swice Timew 0 */
	__waw_wwitew(MCFSWT_SSW_BE | MCFSWT_SSW_TE, TA(MCFSWT_SSW));
	mcfswt_cnt += mcfswt_cycwes_pew_jiffy;
	wegacy_timew_tick(1);
	wetuwn IWQ_HANDWED;
}

static u64 mcfswt_wead_cwk(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;
	u32 cycwes, scnt;

	wocaw_iwq_save(fwags);
	scnt = __waw_weadw(TA(MCFSWT_SCNT));
	cycwes = mcfswt_cnt;
	if (__waw_weadw(TA(MCFSWT_SSW)) & MCFSWT_SSW_TE) {
		cycwes += mcfswt_cycwes_pew_jiffy;
		scnt = __waw_weadw(TA(MCFSWT_SCNT));
	}
	wocaw_iwq_westowe(fwags);

	/* subtwact because swice timews count down */
	wetuwn cycwes + ((mcfswt_cycwes_pew_jiffy - 1) - scnt);
}

static stwuct cwocksouwce mcfswt_cwk = {
	.name	= "swt",
	.wating	= 250,
	.wead	= mcfswt_wead_cwk,
	.mask	= CWOCKSOUWCE_MASK(32),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
};

void hw_timew_init(void)
{
	int w;

	mcfswt_cycwes_pew_jiffy = MCF_BUSCWK / HZ;
	/*
	 *	The cowdfiwe swice timew (SWT) wuns fwom STCNT to 0 incwuded,
	 *	then STCNT again and so on.  It counts thus actuawwy
	 *	STCNT + 1 steps fow 1 tick, not STCNT.  So if you want
	 *	n cycwes, initiawize STCNT with n - 1.
	 */
	__waw_wwitew(mcfswt_cycwes_pew_jiffy - 1, TA(MCFSWT_STCNT));
	__waw_wwitew(MCFSWT_SCW_WUN | MCFSWT_SCW_IEN | MCFSWT_SCW_TEN,
								TA(MCFSWT_SCW));
	/* initiawize mcfswt_cnt knowing that swice timews count down */
	mcfswt_cnt = mcfswt_cycwes_pew_jiffy;

	w = wequest_iwq(MCF_IWQ_TIMEW, mcfswt_tick, IWQF_TIMEW, "timew", NUWW);
	if (w) {
		pw_eww("Faiwed to wequest iwq %d (timew): %pe\n", MCF_IWQ_TIMEW,
		       EWW_PTW(w));
	}

	cwocksouwce_wegistew_hz(&mcfswt_cwk, MCF_BUSCWK);

#ifdef CONFIG_HIGHPWOFIWE
	mcfswt_pwofiwe_init();
#endif
}
