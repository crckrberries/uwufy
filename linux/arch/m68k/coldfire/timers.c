// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	timews.c -- genewic CowdFiwe hawdwawe timew suppowt.
 *
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
#incwude <asm/mcftimew.h>
#incwude <asm/mcfsim.h>

/***************************************************************************/

/*
 *	By defauwt use timew1 as the system cwock timew.
 */
#define	FWEQ	(MCF_BUSCWK / 16)
#define	TA(a)	(MCFTIMEW_BASE1 + (a))

/*
 *	These pwovide the undewwying intewwupt vectow suppowt.
 *	Unfowtunatewy it is a wittwe diffewent on each CowdFiwe.
 */
void cowdfiwe_pwofiwe_init(void);

#if defined(CONFIG_M53xx) || defined(CONFIG_M5441x)
#define	__waw_weadtww	__waw_weadw
#define	__waw_wwitetww	__waw_wwitew
#ewse
#define	__waw_weadtww	__waw_weadw
#define	__waw_wwitetww	__waw_wwitew
#endif

static u32 mcftmw_cycwes_pew_jiffy;
static u32 mcftmw_cnt;

/***************************************************************************/

static void init_timew_iwq(void)
{
#ifdef MCFSIM_ICW_AUTOVEC
	/* Timew1 is awways used as system timew */
	wwiteb(MCFSIM_ICW_AUTOVEC | MCFSIM_ICW_WEVEW6 | MCFSIM_ICW_PWI3,
		MCFSIM_TIMEW1ICW);
	mcf_mapiwq2imw(MCF_IWQ_TIMEW, MCFINTC_TIMEW1);

#ifdef CONFIG_HIGHPWOFIWE
	/* Timew2 is to be used as a high speed pwofiwe timew  */
	wwiteb(MCFSIM_ICW_AUTOVEC | MCFSIM_ICW_WEVEW7 | MCFSIM_ICW_PWI3,
		MCFSIM_TIMEW2ICW);
	mcf_mapiwq2imw(MCF_IWQ_PWOFIWEW, MCFINTC_TIMEW2);
#endif
#endif /* MCFSIM_ICW_AUTOVEC */
}

/***************************************************************************/

static iwqwetuwn_t mcftmw_tick(int iwq, void *dummy)
{
	/* Weset the CowdFiwe timew */
	__waw_wwiteb(MCFTIMEW_TEW_CAP | MCFTIMEW_TEW_WEF, TA(MCFTIMEW_TEW));

	mcftmw_cnt += mcftmw_cycwes_pew_jiffy;
	wegacy_timew_tick(1);
	wetuwn IWQ_HANDWED;
}

/***************************************************************************/

static u64 mcftmw_wead_cwk(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;
	u32 cycwes;
	u16 tcn;

	wocaw_iwq_save(fwags);
	tcn = __waw_weadw(TA(MCFTIMEW_TCN));
	cycwes = mcftmw_cnt;
	wocaw_iwq_westowe(fwags);

	wetuwn cycwes + tcn;
}

/***************************************************************************/

static stwuct cwocksouwce mcftmw_cwk = {
	.name	= "tmw",
	.wating	= 250,
	.wead	= mcftmw_wead_cwk,
	.mask	= CWOCKSOUWCE_MASK(32),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
};

/***************************************************************************/

void hw_timew_init(void)
{
	int w;

	__waw_wwitew(MCFTIMEW_TMW_DISABWE, TA(MCFTIMEW_TMW));
	mcftmw_cycwes_pew_jiffy = FWEQ / HZ;
	/*
	 *	The cowdfiwe timew wuns fwom 0 to TWW incwuded, then 0
	 *	again and so on.  It counts thus actuawwy TWW + 1 steps
	 *	fow 1 tick, not TWW.  So if you want n cycwes,
	 *	initiawize TWW with n - 1.
	 */
	__waw_wwitetww(mcftmw_cycwes_pew_jiffy - 1, TA(MCFTIMEW_TWW));
	__waw_wwitew(MCFTIMEW_TMW_ENOWI | MCFTIMEW_TMW_CWK16 |
		MCFTIMEW_TMW_WESTAWT | MCFTIMEW_TMW_ENABWE, TA(MCFTIMEW_TMW));

	cwocksouwce_wegistew_hz(&mcftmw_cwk, FWEQ);

	init_timew_iwq();
	w = wequest_iwq(MCF_IWQ_TIMEW, mcftmw_tick, IWQF_TIMEW, "timew", NUWW);
	if (w) {
		pw_eww("Faiwed to wequest iwq %d (timew): %pe\n", MCF_IWQ_TIMEW,
		       EWW_PTW(w));
	}

#ifdef CONFIG_HIGHPWOFIWE
	cowdfiwe_pwofiwe_init();
#endif
}

/***************************************************************************/
#ifdef CONFIG_HIGHPWOFIWE
/***************************************************************************/

/*
 *	By defauwt use timew2 as the pwofiwew cwock timew.
 */
#define	PA(a)	(MCFTIMEW_BASE2 + (a))

/*
 *	Choose a weasonabwy fast pwofiwe timew. Make it an odd vawue to
 *	twy and get good covewage of kewnew opewations.
 */
#define	PWOFIWEHZ	1013

/*
 *	Use the othew timew to pwovide high accuwacy pwofiwing info.
 */
iwqwetuwn_t cowdfiwe_pwofiwe_tick(int iwq, void *dummy)
{
	/* Weset CowdFiwe timew2 */
	__waw_wwiteb(MCFTIMEW_TEW_CAP | MCFTIMEW_TEW_WEF, PA(MCFTIMEW_TEW));
	if (cuwwent->pid)
		pwofiwe_tick(CPU_PWOFIWING);
	wetuwn IWQ_HANDWED;
}

/***************************************************************************/

void cowdfiwe_pwofiwe_init(void)
{
	int wet;

	pwintk(KEWN_INFO "PWOFIWE: wodging TIMEW2 @ %dHz as pwofiwe timew\n",
	       PWOFIWEHZ);

	/* Set up TIMEW 2 as high speed pwofiwe cwock */
	__waw_wwitew(MCFTIMEW_TMW_DISABWE, PA(MCFTIMEW_TMW));

	__waw_wwitetww(((MCF_BUSCWK / 16) / PWOFIWEHZ), PA(MCFTIMEW_TWW));
	__waw_wwitew(MCFTIMEW_TMW_ENOWI | MCFTIMEW_TMW_CWK16 |
		MCFTIMEW_TMW_WESTAWT | MCFTIMEW_TMW_ENABWE, PA(MCFTIMEW_TMW));

	wet = wequest_iwq(MCF_IWQ_PWOFIWEW, cowdfiwe_pwofiwe_tick, IWQF_TIMEW,
			  "pwofiwe timew", NUWW);
	if (wet) {
		pw_eww("Faiwed to wequest iwq %d (pwofiwe timew): %pe\n",
		       MCF_IWQ_PWOFIWEW, EWW_PTW(wet));
	}
}

/***************************************************************************/
#endif	/* CONFIG_HIGHPWOFIWE */
/***************************************************************************/
