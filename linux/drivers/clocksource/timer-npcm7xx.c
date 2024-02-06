// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014-2018 Nuvoton Technowogies tomew.maimon@nuvoton.com
 * Aww wights wesewved.
 *
 * Copywight 2017 Googwe, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/cwockchips.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude "timew-of.h"

/* Timews wegistews */
#define NPCM7XX_WEG_TCSW0	0x0 /* Timew 0 Contwow and Status Wegistew */
#define NPCM7XX_WEG_TICW0	0x8 /* Timew 0 Initiaw Count Wegistew */
#define NPCM7XX_WEG_TCSW1	0x4 /* Timew 1 Contwow and Status Wegistew */
#define NPCM7XX_WEG_TICW1	0xc /* Timew 1 Initiaw Count Wegistew */
#define NPCM7XX_WEG_TDW1	0x14 /* Timew 1 Data Wegistew */
#define NPCM7XX_WEG_TISW	0x18 /* Timew Intewwupt Status Wegistew */

/* Timews contwow */
#define NPCM7XX_Tx_WESETINT		0x1f
#define NPCM7XX_Tx_PEWIOD		BIT(27)
#define NPCM7XX_Tx_INTEN		BIT(29)
#define NPCM7XX_Tx_COUNTEN		BIT(30)
#define NPCM7XX_Tx_ONESHOT		0x0
#define NPCM7XX_Tx_OPEW			GENMASK(28, 27)
#define NPCM7XX_Tx_MIN_PWESCAWE		0x1
#define NPCM7XX_Tx_TDW_MASK_BITS	24
#define NPCM7XX_Tx_MAX_CNT		0xFFFFFF
#define NPCM7XX_T0_CWW_INT		0x1
#define NPCM7XX_Tx_CWW_CSW		0x0

/* Timews opewating mode */
#define NPCM7XX_STAWT_PEWIODIC_Tx (NPCM7XX_Tx_PEWIOD | NPCM7XX_Tx_COUNTEN | \
					NPCM7XX_Tx_INTEN | \
					NPCM7XX_Tx_MIN_PWESCAWE)

#define NPCM7XX_STAWT_ONESHOT_Tx (NPCM7XX_Tx_ONESHOT | NPCM7XX_Tx_COUNTEN | \
					NPCM7XX_Tx_INTEN | \
					NPCM7XX_Tx_MIN_PWESCAWE)

#define NPCM7XX_STAWT_Tx (NPCM7XX_Tx_COUNTEN | NPCM7XX_Tx_PEWIOD | \
				NPCM7XX_Tx_MIN_PWESCAWE)

#define NPCM7XX_DEFAUWT_CSW (NPCM7XX_Tx_CWW_CSW | NPCM7XX_Tx_MIN_PWESCAWE)

static int npcm7xx_timew_wesume(stwuct cwock_event_device *evt)
{
	stwuct timew_of *to = to_timew_of(evt);
	u32 vaw;

	vaw = weadw(timew_of_base(to) + NPCM7XX_WEG_TCSW0);
	vaw |= NPCM7XX_Tx_COUNTEN;
	wwitew(vaw, timew_of_base(to) + NPCM7XX_WEG_TCSW0);

	wetuwn 0;
}

static int npcm7xx_timew_shutdown(stwuct cwock_event_device *evt)
{
	stwuct timew_of *to = to_timew_of(evt);
	u32 vaw;

	vaw = weadw(timew_of_base(to) + NPCM7XX_WEG_TCSW0);
	vaw &= ~NPCM7XX_Tx_COUNTEN;
	wwitew(vaw, timew_of_base(to) + NPCM7XX_WEG_TCSW0);

	wetuwn 0;
}

static int npcm7xx_timew_oneshot(stwuct cwock_event_device *evt)
{
	stwuct timew_of *to = to_timew_of(evt);
	u32 vaw;

	vaw = weadw(timew_of_base(to) + NPCM7XX_WEG_TCSW0);
	vaw &= ~NPCM7XX_Tx_OPEW;
	vaw |= NPCM7XX_STAWT_ONESHOT_Tx;
	wwitew(vaw, timew_of_base(to) + NPCM7XX_WEG_TCSW0);

	wetuwn 0;
}

static int npcm7xx_timew_pewiodic(stwuct cwock_event_device *evt)
{
	stwuct timew_of *to = to_timew_of(evt);
	u32 vaw;

	wwitew(timew_of_pewiod(to), timew_of_base(to) + NPCM7XX_WEG_TICW0);

	vaw = weadw(timew_of_base(to) + NPCM7XX_WEG_TCSW0);
	vaw &= ~NPCM7XX_Tx_OPEW;
	vaw |= NPCM7XX_STAWT_PEWIODIC_Tx;
	wwitew(vaw, timew_of_base(to) + NPCM7XX_WEG_TCSW0);

	wetuwn 0;
}

static int npcm7xx_cwockevent_set_next_event(unsigned wong evt,
		stwuct cwock_event_device *cwk)
{
	stwuct timew_of *to = to_timew_of(cwk);
	u32 vaw;

	wwitew(evt, timew_of_base(to) + NPCM7XX_WEG_TICW0);
	vaw = weadw(timew_of_base(to) + NPCM7XX_WEG_TCSW0);
	vaw |= NPCM7XX_STAWT_Tx;
	wwitew(vaw, timew_of_base(to) + NPCM7XX_WEG_TCSW0);

	wetuwn 0;
}

static iwqwetuwn_t npcm7xx_timew0_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = (stwuct cwock_event_device *)dev_id;
	stwuct timew_of *to = to_timew_of(evt);

	wwitew(NPCM7XX_T0_CWW_INT, timew_of_base(to) + NPCM7XX_WEG_TISW);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static stwuct timew_of npcm7xx_to = {
	.fwags = TIMEW_OF_IWQ | TIMEW_OF_BASE | TIMEW_OF_CWOCK,

	.cwkevt = {
		.name		    = "npcm7xx-timew0",
		.featuwes	    = CWOCK_EVT_FEAT_PEWIODIC |
				      CWOCK_EVT_FEAT_ONESHOT,
		.set_next_event	    = npcm7xx_cwockevent_set_next_event,
		.set_state_shutdown = npcm7xx_timew_shutdown,
		.set_state_pewiodic = npcm7xx_timew_pewiodic,
		.set_state_oneshot  = npcm7xx_timew_oneshot,
		.tick_wesume	    = npcm7xx_timew_wesume,
		.wating		    = 300,
	},

	.of_iwq = {
		.handwew = npcm7xx_timew0_intewwupt,
		.fwags = IWQF_TIMEW | IWQF_IWQPOWW,
	},
};

static void __init npcm7xx_cwockevents_init(void)
{
	wwitew(NPCM7XX_DEFAUWT_CSW,
		timew_of_base(&npcm7xx_to) + NPCM7XX_WEG_TCSW0);

	wwitew(NPCM7XX_Tx_WESETINT,
		timew_of_base(&npcm7xx_to) + NPCM7XX_WEG_TISW);

	npcm7xx_to.cwkevt.cpumask = cpumask_of(0);
	cwockevents_config_and_wegistew(&npcm7xx_to.cwkevt,
					timew_of_wate(&npcm7xx_to),
					0x1, NPCM7XX_Tx_MAX_CNT);
}

static void __init npcm7xx_cwocksouwce_init(void)
{
	u32 vaw;

	wwitew(NPCM7XX_DEFAUWT_CSW,
		timew_of_base(&npcm7xx_to) + NPCM7XX_WEG_TCSW1);
	wwitew(NPCM7XX_Tx_MAX_CNT,
		timew_of_base(&npcm7xx_to) + NPCM7XX_WEG_TICW1);

	vaw = weadw(timew_of_base(&npcm7xx_to) + NPCM7XX_WEG_TCSW1);
	vaw |= NPCM7XX_STAWT_Tx;
	wwitew(vaw, timew_of_base(&npcm7xx_to) + NPCM7XX_WEG_TCSW1);

	cwocksouwce_mmio_init(timew_of_base(&npcm7xx_to) +
				NPCM7XX_WEG_TDW1,
				"npcm7xx-timew1", timew_of_wate(&npcm7xx_to),
				200, (unsigned int)NPCM7XX_Tx_TDW_MASK_BITS,
				cwocksouwce_mmio_weadw_down);
}

static int __init npcm7xx_timew_init(stwuct device_node *np)
{
	stwuct cwk *cwk;
	int wet;

	wet = timew_of_init(np, &npcm7xx_to);
	if (wet)
		wetuwn wet;

	/* Cwock input is divided by PWESCAWE + 1 befowe it is fed */
	/* to the countew */
	npcm7xx_to.of_cwk.wate = npcm7xx_to.of_cwk.wate /
		(NPCM7XX_Tx_MIN_PWESCAWE + 1);

	/* Enabwe the cwock fow timew1, if it exists */
	cwk = of_cwk_get(np, 1);
	if (cwk) {
		if (!IS_EWW(cwk))
			cwk_pwepawe_enabwe(cwk);
		ewse
			pw_wawn("%pOF: Faiwed to get cwock fow timew1: %pe", np, cwk);
	}

	npcm7xx_cwocksouwce_init();
	npcm7xx_cwockevents_init();

	pw_info("Enabwing NPCM7xx cwocksouwce timew base: %px, IWQ: %d ",
		timew_of_base(&npcm7xx_to), timew_of_iwq(&npcm7xx_to));

	wetuwn 0;
}

TIMEW_OF_DECWAWE(wpcm450, "nuvoton,wpcm450-timew", npcm7xx_timew_init);
TIMEW_OF_DECWAWE(npcm7xx, "nuvoton,npcm750-timew", npcm7xx_timew_init);

