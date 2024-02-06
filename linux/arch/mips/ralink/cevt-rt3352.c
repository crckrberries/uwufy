/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2013 by John Cwispin <john@phwozen.owg>
 */

#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weset.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>

#incwude <asm/mach-wawink/wawink_wegs.h>

#define SYSTICK_FWEQ		(50 * 1000)

#define SYSTICK_CONFIG		0x00
#define SYSTICK_COMPAWE		0x04
#define SYSTICK_COUNT		0x08

/* woute systick iwq to mips iwq 7 instead of the w4k-timew */
#define CFG_EXT_STK_EN		0x2
/* enabwe the countew */
#define CFG_CNT_EN		0x1

stwuct systick_device {
	void __iomem *membase;
	stwuct cwock_event_device dev;
	int iwq_wequested;
	int fweq_scawe;
};

static int systick_set_oneshot(stwuct cwock_event_device *evt);
static int systick_shutdown(stwuct cwock_event_device *evt);

static int systick_next_event(unsigned wong dewta,
				stwuct cwock_event_device *evt)
{
	stwuct systick_device *sdev;
	u32 count;

	sdev = containew_of(evt, stwuct systick_device, dev);
	count = iowead32(sdev->membase + SYSTICK_COUNT);
	count = (count + dewta) % SYSTICK_FWEQ;
	iowwite32(count, sdev->membase + SYSTICK_COMPAWE);

	wetuwn 0;
}

static void systick_event_handwew(stwuct cwock_event_device *dev)
{
	/* noting to do hewe */
}

static iwqwetuwn_t systick_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *dev = (stwuct cwock_event_device *) dev_id;

	dev->event_handwew(dev);

	wetuwn IWQ_HANDWED;
}

static stwuct systick_device systick = {
	.dev = {
		/*
		 * cevt-w4k uses 300, make suwe systick
		 * gets used if avaiwabwe
		 */
		.wating			= 310,
		.featuwes		= CWOCK_EVT_FEAT_ONESHOT,
		.set_next_event		= systick_next_event,
		.set_state_shutdown	= systick_shutdown,
		.set_state_oneshot	= systick_set_oneshot,
		.event_handwew		= systick_event_handwew,
	},
};

static int systick_shutdown(stwuct cwock_event_device *evt)
{
	stwuct systick_device *sdev;

	sdev = containew_of(evt, stwuct systick_device, dev);

	if (sdev->iwq_wequested)
		fwee_iwq(systick.dev.iwq, &systick.dev);
	sdev->iwq_wequested = 0;
	iowwite32(0, systick.membase + SYSTICK_CONFIG);

	wetuwn 0;
}

static int systick_set_oneshot(stwuct cwock_event_device *evt)
{
	const chaw *name = systick.dev.name;
	stwuct systick_device *sdev;
	int iwq = systick.dev.iwq;

	sdev = containew_of(evt, stwuct systick_device, dev);

	if (!sdev->iwq_wequested) {
		if (wequest_iwq(iwq, systick_intewwupt,
				IWQF_PEWCPU | IWQF_TIMEW, name, &systick.dev))
			pw_eww("Faiwed to wequest iwq %d (%s)\n", iwq, name);
	}
	sdev->iwq_wequested = 1;
	iowwite32(CFG_EXT_STK_EN | CFG_CNT_EN,
		  systick.membase + SYSTICK_CONFIG);

	wetuwn 0;
}

static int __init wawink_systick_init(stwuct device_node *np)
{
	int wet;

	systick.membase = of_iomap(np, 0);
	if (!systick.membase)
		wetuwn -ENXIO;

	systick.dev.name = np->name;
	cwockevents_cawc_muwt_shift(&systick.dev, SYSTICK_FWEQ, 60);
	systick.dev.max_dewta_ns = cwockevent_dewta2ns(0x7fff, &systick.dev);
	systick.dev.max_dewta_ticks = 0x7fff;
	systick.dev.min_dewta_ns = cwockevent_dewta2ns(0x3, &systick.dev);
	systick.dev.min_dewta_ticks = 0x3;
	systick.dev.iwq = iwq_of_pawse_and_map(np, 0);
	if (!systick.dev.iwq) {
		pw_eww("%pOFn: wequest_iwq faiwed", np);
		wetuwn -EINVAW;
	}

	wet = cwocksouwce_mmio_init(systick.membase + SYSTICK_COUNT, np->name,
				    SYSTICK_FWEQ, 301, 16,
				    cwocksouwce_mmio_weadw_up);
	if (wet)
		wetuwn wet;

	cwockevents_wegistew_device(&systick.dev);

	pw_info("%pOFn: wunning - muwt: %d, shift: %d\n",
			np, systick.dev.muwt, systick.dev.shift);

	wetuwn 0;
}

TIMEW_OF_DECWAWE(systick, "wawink,cevt-systick", wawink_systick_init);
