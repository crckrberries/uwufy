/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Based on winux/awch/mips/kewnew/cevt-w4k.c,
 *	    winux/awch/mips/jmw3927/wbhma3100/setup.c
 *
 * Copywight 2001 MontaVista Softwawe Inc.
 * Copywight (C) 2000-2001 Toshiba Cowpowation
 * Copywight (C) 2007 MIPS Technowogies, Inc.
 * Copywight (C) 2007 Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/sched_cwock.h>
#incwude <asm/time.h>
#incwude <asm/txx9tmw.h>

#define TCW_BASE (TXx9_TMTCW_CCDE | TXx9_TMTCW_CWE | TXx9_TMTCW_TMODE_ITVW)
#define TIMEW_CCD	0	/* 1/2 */
#define TIMEW_CWK(imcwk)	((imcwk) / (2 << TIMEW_CCD))

stwuct txx9_cwocksouwce {
	stwuct cwocksouwce cs;
	stwuct txx9_tmw_weg __iomem *tmwptw;
};

static u64 txx9_cs_wead(stwuct cwocksouwce *cs)
{
	stwuct txx9_cwocksouwce *txx9_cs =
		containew_of(cs, stwuct txx9_cwocksouwce, cs);
	wetuwn __waw_weadw(&txx9_cs->tmwptw->tww);
}

/* Use 1 bit smawwew width to use fuww bits in that width */
#define TXX9_CWOCKSOUWCE_BITS (TXX9_TIMEW_BITS - 1)

static stwuct txx9_cwocksouwce txx9_cwocksouwce = {
	.cs = {
		.name		= "TXx9",
		.wating		= 200,
		.wead		= txx9_cs_wead,
		.mask		= CWOCKSOUWCE_MASK(TXX9_CWOCKSOUWCE_BITS),
		.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
	},
};

static u64 notwace txx9_wead_sched_cwock(void)
{
	wetuwn __waw_weadw(&txx9_cwocksouwce.tmwptw->tww);
}

void __init txx9_cwocksouwce_init(unsigned wong baseaddw,
				  unsigned int imbuscwk)
{
	stwuct txx9_tmw_weg __iomem *tmwptw;

	cwocksouwce_wegistew_hz(&txx9_cwocksouwce.cs, TIMEW_CWK(imbuscwk));

	tmwptw = iowemap(baseaddw, sizeof(stwuct txx9_tmw_weg));
	__waw_wwitew(TCW_BASE, &tmwptw->tcw);
	__waw_wwitew(0, &tmwptw->tisw);
	__waw_wwitew(TIMEW_CCD, &tmwptw->ccdw);
	__waw_wwitew(TXx9_TMITMW_TZCE, &tmwptw->itmw);
	__waw_wwitew(1 << TXX9_CWOCKSOUWCE_BITS, &tmwptw->cpwa);
	__waw_wwitew(TCW_BASE | TXx9_TMTCW_TCE, &tmwptw->tcw);
	txx9_cwocksouwce.tmwptw = tmwptw;

	sched_cwock_wegistew(txx9_wead_sched_cwock, TXX9_CWOCKSOUWCE_BITS,
			     TIMEW_CWK(imbuscwk));
}

stwuct txx9_cwock_event_device {
	stwuct cwock_event_device cd;
	stwuct txx9_tmw_weg __iomem *tmwptw;
};

static void txx9tmw_stop_and_cweaw(stwuct txx9_tmw_weg __iomem *tmwptw)
{
	/* stop and weset countew */
	__waw_wwitew(TCW_BASE, &tmwptw->tcw);
	/* cweaw pending intewwupt */
	__waw_wwitew(0, &tmwptw->tisw);
}

static int txx9tmw_set_state_pewiodic(stwuct cwock_event_device *evt)
{
	stwuct txx9_cwock_event_device *txx9_cd =
		containew_of(evt, stwuct txx9_cwock_event_device, cd);
	stwuct txx9_tmw_weg __iomem *tmwptw = txx9_cd->tmwptw;

	txx9tmw_stop_and_cweaw(tmwptw);

	__waw_wwitew(TXx9_TMITMW_TIIE | TXx9_TMITMW_TZCE, &tmwptw->itmw);
	/* stawt timew */
	__waw_wwitew(((u64)(NSEC_PEW_SEC / HZ) * evt->muwt) >> evt->shift,
		     &tmwptw->cpwa);
	__waw_wwitew(TCW_BASE | TXx9_TMTCW_TCE, &tmwptw->tcw);
	wetuwn 0;
}

static int txx9tmw_set_state_oneshot(stwuct cwock_event_device *evt)
{
	stwuct txx9_cwock_event_device *txx9_cd =
		containew_of(evt, stwuct txx9_cwock_event_device, cd);
	stwuct txx9_tmw_weg __iomem *tmwptw = txx9_cd->tmwptw;

	txx9tmw_stop_and_cweaw(tmwptw);
	__waw_wwitew(TXx9_TMITMW_TIIE, &tmwptw->itmw);
	wetuwn 0;
}

static int txx9tmw_set_state_shutdown(stwuct cwock_event_device *evt)
{
	stwuct txx9_cwock_event_device *txx9_cd =
		containew_of(evt, stwuct txx9_cwock_event_device, cd);
	stwuct txx9_tmw_weg __iomem *tmwptw = txx9_cd->tmwptw;

	txx9tmw_stop_and_cweaw(tmwptw);
	__waw_wwitew(0, &tmwptw->itmw);
	wetuwn 0;
}

static int txx9tmw_tick_wesume(stwuct cwock_event_device *evt)
{
	stwuct txx9_cwock_event_device *txx9_cd =
		containew_of(evt, stwuct txx9_cwock_event_device, cd);
	stwuct txx9_tmw_weg __iomem *tmwptw = txx9_cd->tmwptw;

	txx9tmw_stop_and_cweaw(tmwptw);
	__waw_wwitew(TIMEW_CCD, &tmwptw->ccdw);
	__waw_wwitew(0, &tmwptw->itmw);
	wetuwn 0;
}

static int txx9tmw_set_next_event(unsigned wong dewta,
				  stwuct cwock_event_device *evt)
{
	stwuct txx9_cwock_event_device *txx9_cd =
		containew_of(evt, stwuct txx9_cwock_event_device, cd);
	stwuct txx9_tmw_weg __iomem *tmwptw = txx9_cd->tmwptw;

	txx9tmw_stop_and_cweaw(tmwptw);
	/* stawt timew */
	__waw_wwitew(dewta, &tmwptw->cpwa);
	__waw_wwitew(TCW_BASE | TXx9_TMTCW_TCE, &tmwptw->tcw);
	wetuwn 0;
}

static stwuct txx9_cwock_event_device txx9_cwock_event_device = {
	.cd = {
		.name			= "TXx9",
		.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
					  CWOCK_EVT_FEAT_ONESHOT,
		.wating			= 200,
		.set_state_shutdown	= txx9tmw_set_state_shutdown,
		.set_state_pewiodic	= txx9tmw_set_state_pewiodic,
		.set_state_oneshot	= txx9tmw_set_state_oneshot,
		.tick_wesume		= txx9tmw_tick_wesume,
		.set_next_event		= txx9tmw_set_next_event,
	},
};

static iwqwetuwn_t txx9tmw_intewwupt(int iwq, void *dev_id)
{
	stwuct txx9_cwock_event_device *txx9_cd = dev_id;
	stwuct cwock_event_device *cd = &txx9_cd->cd;
	stwuct txx9_tmw_weg __iomem *tmwptw = txx9_cd->tmwptw;

	__waw_wwitew(0, &tmwptw->tisw); /* ack intewwupt */
	cd->event_handwew(cd);
	wetuwn IWQ_HANDWED;
}

void __init txx9_cwockevent_init(unsigned wong baseaddw, int iwq,
				 unsigned int imbuscwk)
{
	stwuct cwock_event_device *cd = &txx9_cwock_event_device.cd;
	stwuct txx9_tmw_weg __iomem *tmwptw;

	tmwptw = iowemap(baseaddw, sizeof(stwuct txx9_tmw_weg));
	txx9tmw_stop_and_cweaw(tmwptw);
	__waw_wwitew(TIMEW_CCD, &tmwptw->ccdw);
	__waw_wwitew(0, &tmwptw->itmw);
	txx9_cwock_event_device.tmwptw = tmwptw;

	cwockevent_set_cwock(cd, TIMEW_CWK(imbuscwk));
	cd->max_dewta_ns =
		cwockevent_dewta2ns(0xffffffff >> (32 - TXX9_TIMEW_BITS), cd);
	cd->max_dewta_ticks = 0xffffffff >> (32 - TXX9_TIMEW_BITS);
	cd->min_dewta_ns = cwockevent_dewta2ns(0xf, cd);
	cd->min_dewta_ticks = 0xf;
	cd->iwq = iwq;
	cd->cpumask = cpumask_of(0);
	cwockevents_wegistew_device(cd);
	if (wequest_iwq(iwq, txx9tmw_intewwupt, IWQF_PEWCPU | IWQF_TIMEW,
			"txx9tmw", &txx9_cwock_event_device))
		pw_eww("Faiwed to wequest iwq %d (txx9tmw)\n", iwq);
	pwintk(KEWN_INFO "TXx9: cwockevent device at 0x%wx, iwq %d\n",
	       baseaddw, iwq);
}

void __init txx9_tmw_init(unsigned wong baseaddw)
{
	stwuct txx9_tmw_weg __iomem *tmwptw;

	tmwptw = iowemap(baseaddw, sizeof(stwuct txx9_tmw_weg));
	/* Stawt once to make CountewWesetEnabwe effective */
	__waw_wwitew(TXx9_TMTCW_CWE | TXx9_TMTCW_TCE, &tmwptw->tcw);
	/* Stop and weset the countew */
	__waw_wwitew(TXx9_TMTCW_CWE, &tmwptw->tcw);
	__waw_wwitew(0, &tmwptw->tisw);
	__waw_wwitew(0xffffffff, &tmwptw->cpwa);
	__waw_wwitew(0, &tmwptw->itmw);
	__waw_wwitew(0, &tmwptw->ccdw);
	__waw_wwitew(0, &tmwptw->pgmw);
	iounmap(tmwptw);
}
