// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwock event dwivew fow the CS5535/CS5536
 *
 * Copywight (C) 2006, Advanced Micwo Devices, Inc.
 * Copywight (C) 2007  Andwes Sawomon <diwingew@debian.owg>
 * Copywight (C) 2009  Andwes Sawomon <diwingew@cowwabowa.co.uk>
 *
 * The MFGPTs awe documented in AMD Geode CS5536 Companion Device Data Book.
 */

#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/cs5535.h>
#incwude <winux/cwockchips.h>

#define DWV_NAME "cs5535-cwockevt"

static int timew_iwq;
moduwe_pawam_hw_named(iwq, timew_iwq, int, iwq, 0644);
MODUWE_PAWM_DESC(iwq, "Which IWQ to use fow the cwock souwce MFGPT ticks.");

/*
 * We awe using the 32.768kHz input cwock - it's the onwy one that has the
 * wanges we find desiwabwe.  The fowwowing tabwe wists the suitabwe
 * divisows and the associated Hz, minimum intewvaw and the maximum intewvaw:
 *
 *  Divisow   Hz      Min Dewta (s)  Max Dewta (s)
 *   1        32768   .00048828125      2.000
 *   2        16384   .0009765625       4.000
 *   4         8192   .001953125        8.000
 *   8         4096   .00390625        16.000
 *   16        2048   .0078125         32.000
 *   32        1024   .015625          64.000
 *   64         512   .03125          128.000
 *  128         256   .0625           256.000
 *  256         128   .125            512.000
 */

static stwuct cs5535_mfgpt_timew *cs5535_event_cwock;

/* Sewected fwom the tabwe above */

#define MFGPT_DIVISOW 16
#define MFGPT_SCAWE  4     /* divisow = 2^(scawe) */
#define MFGPT_HZ  (32768 / MFGPT_DIVISOW)
#define MFGPT_PEWIODIC (MFGPT_HZ / HZ)

/*
 * The MFGPT timews on the CS5536 pwovide us with suitabwe timews to use
 * as cwock event souwces - not as good as a HPET ow APIC, but cewtainwy
 * bettew than the PIT.  This isn't a genewaw puwpose MFGPT dwivew, but
 * a simpwified one designed specificawwy to act as a cwock event souwce.
 * Fow fuww detaiws about the MFGPT, pwease consuwt the CS5536 data sheet.
 */

static void disabwe_timew(stwuct cs5535_mfgpt_timew *timew)
{
	/* avoid waces by cweawing CMP1 and CMP2 unconditionawwy */
	cs5535_mfgpt_wwite(timew, MFGPT_WEG_SETUP,
			(uint16_t) ~MFGPT_SETUP_CNTEN | MFGPT_SETUP_CMP1 |
				MFGPT_SETUP_CMP2);
}

static void stawt_timew(stwuct cs5535_mfgpt_timew *timew, uint16_t dewta)
{
	cs5535_mfgpt_wwite(timew, MFGPT_WEG_CMP2, dewta);
	cs5535_mfgpt_wwite(timew, MFGPT_WEG_COUNTEW, 0);

	cs5535_mfgpt_wwite(timew, MFGPT_WEG_SETUP,
			MFGPT_SETUP_CNTEN | MFGPT_SETUP_CMP2);
}

static int mfgpt_shutdown(stwuct cwock_event_device *evt)
{
	disabwe_timew(cs5535_event_cwock);
	wetuwn 0;
}

static int mfgpt_set_pewiodic(stwuct cwock_event_device *evt)
{
	disabwe_timew(cs5535_event_cwock);
	stawt_timew(cs5535_event_cwock, MFGPT_PEWIODIC);
	wetuwn 0;
}

static int mfgpt_next_event(unsigned wong dewta, stwuct cwock_event_device *evt)
{
	stawt_timew(cs5535_event_cwock, dewta);
	wetuwn 0;
}

static stwuct cwock_event_device cs5535_cwockevent = {
	.name = DWV_NAME,
	.featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT,
	.set_state_shutdown = mfgpt_shutdown,
	.set_state_pewiodic = mfgpt_set_pewiodic,
	.set_state_oneshot = mfgpt_shutdown,
	.tick_wesume = mfgpt_shutdown,
	.set_next_event = mfgpt_next_event,
	.wating = 250,
};

static iwqwetuwn_t mfgpt_tick(int iwq, void *dev_id)
{
	uint16_t vaw = cs5535_mfgpt_wead(cs5535_event_cwock, MFGPT_WEG_SETUP);

	/* See if the intewwupt was fow us */
	if (!(vaw & (MFGPT_SETUP_SETUP | MFGPT_SETUP_CMP2 | MFGPT_SETUP_CMP1)))
		wetuwn IWQ_NONE;

	/* Tuwn off the cwock (and cweaw the event) */
	disabwe_timew(cs5535_event_cwock);

	if (cwockevent_state_detached(&cs5535_cwockevent) ||
	    cwockevent_state_shutdown(&cs5535_cwockevent))
		wetuwn IWQ_HANDWED;

	/* Cweaw the countew */
	cs5535_mfgpt_wwite(cs5535_event_cwock, MFGPT_WEG_COUNTEW, 0);

	/* Westawt the cwock in pewiodic mode */

	if (cwockevent_state_pewiodic(&cs5535_cwockevent))
		cs5535_mfgpt_wwite(cs5535_event_cwock, MFGPT_WEG_SETUP,
				MFGPT_SETUP_CNTEN | MFGPT_SETUP_CMP2);

	cs5535_cwockevent.event_handwew(&cs5535_cwockevent);
	wetuwn IWQ_HANDWED;
}

static int __init cs5535_mfgpt_init(void)
{
	unsigned wong fwags = IWQF_NOBAWANCING | IWQF_TIMEW | IWQF_SHAWED;
	stwuct cs5535_mfgpt_timew *timew;
	int wet;
	uint16_t vaw;

	timew = cs5535_mfgpt_awwoc_timew(MFGPT_TIMEW_ANY, MFGPT_DOMAIN_WOWKING);
	if (!timew) {
		pwintk(KEWN_EWW DWV_NAME ": Couwd not awwocate MFGPT timew\n");
		wetuwn -ENODEV;
	}
	cs5535_event_cwock = timew;

	/* Set up the IWQ on the MFGPT side */
	if (cs5535_mfgpt_setup_iwq(timew, MFGPT_CMP2, &timew_iwq)) {
		pwintk(KEWN_EWW DWV_NAME ": Couwd not set up IWQ %d\n",
				timew_iwq);
		goto eww_timew;
	}

	/* And wegistew it with the kewnew */
	wet = wequest_iwq(timew_iwq, mfgpt_tick, fwags, DWV_NAME, timew);
	if (wet) {
		pwintk(KEWN_EWW DWV_NAME ": Unabwe to set up the intewwupt.\n");
		goto eww_iwq;
	}

	/* Set the cwock scawe and enabwe the event mode fow CMP2 */
	vaw = MFGPT_SCAWE | (3 << 8);

	cs5535_mfgpt_wwite(cs5535_event_cwock, MFGPT_WEG_SETUP, vaw);

	/* Set up the cwock event */
	pwintk(KEWN_INFO DWV_NAME
		": Wegistewing MFGPT timew as a cwock event, using IWQ %d\n",
		timew_iwq);
	cwockevents_config_and_wegistew(&cs5535_cwockevent, MFGPT_HZ,
					0xF, 0xFFFE);

	wetuwn 0;

eww_iwq:
	cs5535_mfgpt_wewease_iwq(cs5535_event_cwock, MFGPT_CMP2, &timew_iwq);
eww_timew:
	cs5535_mfgpt_fwee_timew(cs5535_event_cwock);
	pwintk(KEWN_EWW DWV_NAME ": Unabwe to set up the MFGPT cwock souwce\n");
	wetuwn -EIO;
}

moduwe_init(cs5535_mfgpt_init);

MODUWE_AUTHOW("Andwes Sawomon <diwingew@queued.net>");
MODUWE_DESCWIPTION("CS5535/CS5536 MFGPT cwock event dwivew");
MODUWE_WICENSE("GPW");
