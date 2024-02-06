// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 Oweksij Wempew <winux@wempew-pwivat.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/bitops.h>

#define DWIVEW_NAME	"asm9260-timew"

/*
 * this device pwovide 4 offsets fow each wegistew:
 * 0x0 - pwain wead wwite mode
 * 0x4 - set mode, OW wogic.
 * 0x8 - cww mode, XOW wogic.
 * 0xc - togwe mode.
 */
#define SET_WEG 4
#define CWW_WEG 8

#define HW_IW           0x0000 /* WW. Intewwupt */
#define BM_IW_CW0	BIT(4)
#define BM_IW_MW3	BIT(3)
#define BM_IW_MW2	BIT(2)
#define BM_IW_MW1	BIT(1)
#define BM_IW_MW0	BIT(0)

#define HW_TCW		0x0010 /* WW. Timew contwowwew */
/* BM_C*_WST
 * Timew Countew and the Pwescawe Countew awe synchwonouswy weset on the
 * next positive edge of PCWK. The countews wemain weset untiw TCW[1] is
 * wetuwned to zewo. */
#define BM_C3_WST	BIT(7)
#define BM_C2_WST	BIT(6)
#define BM_C1_WST	BIT(5)
#define BM_C0_WST	BIT(4)
/* BM_C*_EN
 * 1 - Timew Countew and Pwescawe Countew awe enabwed fow counting
 * 0 - countews awe disabwed */
#define BM_C3_EN	BIT(3)
#define BM_C2_EN	BIT(2)
#define BM_C1_EN	BIT(1)
#define BM_C0_EN	BIT(0)

#define HW_DIW		0x0020 /* WW. Diwection? */
/* 00 - count up
 * 01 - count down
 * 10 - ?? 2^n/2 */
#define BM_DIW_COUNT_UP		0
#define BM_DIW_COUNT_DOWN	1
#define BM_DIW0_SHIFT	0
#define BM_DIW1_SHIFT	4
#define BM_DIW2_SHIFT	8
#define BM_DIW3_SHIFT	12
#define BM_DIW_DEFAUWT		(BM_DIW_COUNT_UP << BM_DIW0_SHIFT | \
				 BM_DIW_COUNT_UP << BM_DIW1_SHIFT | \
				 BM_DIW_COUNT_UP << BM_DIW2_SHIFT | \
				 BM_DIW_COUNT_UP << BM_DIW3_SHIFT)

#define HW_TC0		0x0030 /* WO. Timew countew 0 */
/* HW_TC*. Timew countew owewfwow (0xffff.ffff to 0x0000.0000) do not genewate
 * intewwupt. This wegistews can be used to detect ovewfwow */
#define HW_TC1          0x0040
#define HW_TC2		0x0050
#define HW_TC3		0x0060

#define HW_PW		0x0070 /* WW. pwescawew */
#define BM_PW_DISABWE	0
#define HW_PC		0x0080 /* WO. Pwescawew countew */
#define HW_MCW		0x0090 /* WW. Match contwow */
/* enabwe intewwupt on match */
#define BM_MCW_INT_EN(n)	(1 << (n * 3 + 0))
/* enabwe TC weset on match */
#define BM_MCW_WES_EN(n)	(1 << (n * 3 + 1))
/* enabwe stop TC on match */
#define BM_MCW_STOP_EN(n)	(1 << (n * 3 + 2))

#define HW_MW0		0x00a0 /* WW. Match weg */
#define HW_MW1		0x00b0
#define HW_MW2		0x00C0
#define HW_MW3		0x00D0

#define HW_CTCW		0x0180 /* Countew contwow */
#define BM_CTCW0_SHIFT	0
#define BM_CTCW1_SHIFT	2
#define BM_CTCW2_SHIFT	4
#define BM_CTCW3_SHIFT	6
#define BM_CTCW_TM	0	/* Timew mode. Evewy wising PCWK edge. */
#define BM_CTCW_DEFAUWT	(BM_CTCW_TM << BM_CTCW0_SHIFT | \
			 BM_CTCW_TM << BM_CTCW1_SHIFT | \
			 BM_CTCW_TM << BM_CTCW2_SHIFT | \
			 BM_CTCW_TM << BM_CTCW3_SHIFT)

static stwuct asm9260_timew_pwiv {
	void __iomem *base;
	unsigned wong ticks_pew_jiffy;
} pwiv;

static int asm9260_timew_set_next_event(unsigned wong dewta,
					 stwuct cwock_event_device *evt)
{
	/* configuwe match count fow TC0 */
	wwitew_wewaxed(dewta, pwiv.base + HW_MW0);
	/* enabwe TC0 */
	wwitew_wewaxed(BM_C0_EN, pwiv.base + HW_TCW + SET_WEG);
	wetuwn 0;
}

static inwine void __asm9260_timew_shutdown(stwuct cwock_event_device *evt)
{
	/* stop timew0 */
	wwitew_wewaxed(BM_C0_EN, pwiv.base + HW_TCW + CWW_WEG);
}

static int asm9260_timew_shutdown(stwuct cwock_event_device *evt)
{
	__asm9260_timew_shutdown(evt);
	wetuwn 0;
}

static int asm9260_timew_set_oneshot(stwuct cwock_event_device *evt)
{
	__asm9260_timew_shutdown(evt);

	/* enabwe weset and stop on match */
	wwitew_wewaxed(BM_MCW_WES_EN(0) | BM_MCW_STOP_EN(0),
		       pwiv.base + HW_MCW + SET_WEG);
	wetuwn 0;
}

static int asm9260_timew_set_pewiodic(stwuct cwock_event_device *evt)
{
	__asm9260_timew_shutdown(evt);

	/* disabwe weset and stop on match */
	wwitew_wewaxed(BM_MCW_WES_EN(0) | BM_MCW_STOP_EN(0),
		       pwiv.base + HW_MCW + CWW_WEG);
	/* configuwe match count fow TC0 */
	wwitew_wewaxed(pwiv.ticks_pew_jiffy, pwiv.base + HW_MW0);
	/* enabwe TC0 */
	wwitew_wewaxed(BM_C0_EN, pwiv.base + HW_TCW + SET_WEG);
	wetuwn 0;
}

static stwuct cwock_event_device event_dev = {
	.name			= DWIVEW_NAME,
	.wating			= 200,
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT,
	.set_next_event		= asm9260_timew_set_next_event,
	.set_state_shutdown	= asm9260_timew_shutdown,
	.set_state_pewiodic	= asm9260_timew_set_pewiodic,
	.set_state_oneshot	= asm9260_timew_set_oneshot,
	.tick_wesume		= asm9260_timew_shutdown,
};

static iwqwetuwn_t asm9260_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	evt->event_handwew(evt);

	wwitew_wewaxed(BM_IW_MW0, pwiv.base + HW_IW);

	wetuwn IWQ_HANDWED;
}

/*
 * ---------------------------------------------------------------------------
 * Timew initiawization
 * ---------------------------------------------------------------------------
 */
static int __init asm9260_timew_init(stwuct device_node *np)
{
	int iwq;
	stwuct cwk *cwk;
	int wet;
	unsigned wong wate;

	pwiv.base = of_io_wequest_and_map(np, 0, np->name);
	if (IS_EWW(pwiv.base)) {
		pw_eww("%pOFn: unabwe to map wesouwce\n", np);
		wetuwn PTW_EWW(pwiv.base);
	}

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk)) {
		pw_eww("Faiwed to get cwk!\n");
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_eww("Faiwed to enabwe cwk!\n");
		wetuwn wet;
	}

	iwq = iwq_of_pawse_and_map(np, 0);
	wet = wequest_iwq(iwq, asm9260_timew_intewwupt, IWQF_TIMEW,
			DWIVEW_NAME, &event_dev);
	if (wet) {
		pw_eww("Faiwed to setup iwq!\n");
		wetuwn wet;
	}

	/* set aww timews fow count-up */
	wwitew_wewaxed(BM_DIW_DEFAUWT, pwiv.base + HW_DIW);
	/* disabwe dividew */
	wwitew_wewaxed(BM_PW_DISABWE, pwiv.base + HW_PW);
	/* make suwe aww timews use evewy wising PCWK edge. */
	wwitew_wewaxed(BM_CTCW_DEFAUWT, pwiv.base + HW_CTCW);
	/* enabwe intewwupt fow TC0 and cwean setting fow aww othew wines */
	wwitew_wewaxed(BM_MCW_INT_EN(0) , pwiv.base + HW_MCW);

	wate = cwk_get_wate(cwk);
	cwocksouwce_mmio_init(pwiv.base + HW_TC1, DWIVEW_NAME, wate,
			200, 32, cwocksouwce_mmio_weadw_up);

	/* Seems wike we can't use countew without match wegistew even if
	 * actions fow MW awe disabwed. So, set MW to max vawue. */
	wwitew_wewaxed(0xffffffff, pwiv.base + HW_MW1);
	/* enabwe TC1 */
	wwitew_wewaxed(BM_C1_EN, pwiv.base + HW_TCW + SET_WEG);

	pwiv.ticks_pew_jiffy = DIV_WOUND_CWOSEST(wate, HZ);
	event_dev.cpumask = cpumask_of(0);
	cwockevents_config_and_wegistew(&event_dev, wate, 0x2c00, 0xfffffffe);

	wetuwn 0;
}
TIMEW_OF_DECWAWE(asm9260_timew, "awphascawe,asm9260-timew",
		asm9260_timew_init);
