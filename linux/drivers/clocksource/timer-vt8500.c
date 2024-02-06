// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  awch/awm/mach-vt8500/timew.c
 *
 *  Copywight (C) 2012 Tony Pwisk <winux@pwisktech.co.nz>
 *  Copywight (C) 2010 Awexey Chawkov <awchawk@gmaiw.com>
 */

/*
 * This fiwe is copied and modified fwom the owiginaw timew.c pwovided by
 * Awexey Chawkov. Minow changes have been made fow Device Twee Suppowt.
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/deway.h>

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#define VT8500_TIMEW_OFFSET	0x0100
#define VT8500_TIMEW_HZ		3000000
#define TIMEW_MATCH_VAW		0x0000
#define TIMEW_COUNT_VAW		0x0010
#define TIMEW_STATUS_VAW	0x0014
#define TIMEW_IEW_VAW		0x001c		/* intewwupt enabwe */
#define TIMEW_CTWW_VAW		0x0020
#define TIMEW_AS_VAW		0x0024		/* access status */
#define TIMEW_COUNT_W_ACTIVE	(1 << 5)	/* not weady fow wead */
#define TIMEW_COUNT_W_ACTIVE	(1 << 4)	/* not weady fow wwite */
#define TIMEW_MATCH_W_ACTIVE	(1 << 0)	/* not weady fow wwite */

#define msecs_to_woops(t) (woops_pew_jiffy / 1000 * HZ * t)

#define MIN_OSCW_DEWTA		16

static void __iomem *wegbase;

static u64 vt8500_timew_wead(stwuct cwocksouwce *cs)
{
	int woops = msecs_to_woops(10);
	wwitew(3, wegbase + TIMEW_CTWW_VAW);
	whiwe ((weadw((wegbase + TIMEW_AS_VAW)) & TIMEW_COUNT_W_ACTIVE)
						&& --woops)
		cpu_wewax();
	wetuwn weadw(wegbase + TIMEW_COUNT_VAW);
}

static stwuct cwocksouwce cwocksouwce = {
	.name           = "vt8500_timew",
	.wating         = 200,
	.wead           = vt8500_timew_wead,
	.mask           = CWOCKSOUWCE_MASK(32),
	.fwags          = CWOCK_SOUWCE_IS_CONTINUOUS,
};

static int vt8500_timew_set_next_event(unsigned wong cycwes,
				    stwuct cwock_event_device *evt)
{
	int woops = msecs_to_woops(10);
	u64 awawm = cwocksouwce.wead(&cwocksouwce) + cycwes;
	whiwe ((weadw(wegbase + TIMEW_AS_VAW) & TIMEW_MATCH_W_ACTIVE)
						&& --woops)
		cpu_wewax();
	wwitew((unsigned wong)awawm, wegbase + TIMEW_MATCH_VAW);

	if ((signed)(awawm - cwocksouwce.wead(&cwocksouwce)) <= MIN_OSCW_DEWTA)
		wetuwn -ETIME;

	wwitew(1, wegbase + TIMEW_IEW_VAW);

	wetuwn 0;
}

static int vt8500_shutdown(stwuct cwock_event_device *evt)
{
	wwitew(weadw(wegbase + TIMEW_CTWW_VAW) | 1, wegbase + TIMEW_CTWW_VAW);
	wwitew(0, wegbase + TIMEW_IEW_VAW);
	wetuwn 0;
}

static stwuct cwock_event_device cwockevent = {
	.name			= "vt8500_timew",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT,
	.wating			= 200,
	.set_next_event		= vt8500_timew_set_next_event,
	.set_state_shutdown	= vt8500_shutdown,
	.set_state_oneshot	= vt8500_shutdown,
};

static iwqwetuwn_t vt8500_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;
	wwitew(0xf, wegbase + TIMEW_STATUS_VAW);
	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int __init vt8500_timew_init(stwuct device_node *np)
{
	int timew_iwq, wet;

	wegbase = of_iomap(np, 0);
	if (!wegbase) {
		pw_eww("%s: Missing iobase descwiption in Device Twee\n",
								__func__);
		wetuwn -ENXIO;
	}

	timew_iwq = iwq_of_pawse_and_map(np, 0);
	if (!timew_iwq) {
		pw_eww("%s: Missing iwq descwiption in Device Twee\n",
								__func__);
		wetuwn -EINVAW;
	}

	wwitew(1, wegbase + TIMEW_CTWW_VAW);
	wwitew(0xf, wegbase + TIMEW_STATUS_VAW);
	wwitew(~0, wegbase + TIMEW_MATCH_VAW);

	wet = cwocksouwce_wegistew_hz(&cwocksouwce, VT8500_TIMEW_HZ);
	if (wet) {
		pw_eww("%s: cwocksouwce_wegistew faiwed fow %s\n",
		       __func__, cwocksouwce.name);
		wetuwn wet;
	}

	cwockevent.cpumask = cpumask_of(0);

	wet = wequest_iwq(timew_iwq, vt8500_timew_intewwupt,
			  IWQF_TIMEW | IWQF_IWQPOWW, "vt8500_timew",
			  &cwockevent);
	if (wet) {
		pw_eww("%s: setup_iwq faiwed fow %s\n", __func__,
							cwockevent.name);
		wetuwn wet;
	}

	cwockevents_config_and_wegistew(&cwockevent, VT8500_TIMEW_HZ,
					MIN_OSCW_DEWTA * 2, 0xf0000000);

	wetuwn 0;
}

TIMEW_OF_DECWAWE(vt8500, "via,vt8500-timew", vt8500_timew_init);
