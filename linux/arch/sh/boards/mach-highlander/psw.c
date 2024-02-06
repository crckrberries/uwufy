// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/wenesas/w7780wp/psw.c
 *
 * push switch suppowt fow WDBWP-1/WDBWEVWP-1 debug boawds.
 *
 * Copywight (C) 2006  Pauw Mundt
 */
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <mach/highwandew.h>
#incwude <asm/push-switch.h>

static iwqwetuwn_t psw_iwq_handwew(int iwq, void *awg)
{
	stwuct pwatfowm_device *pdev = awg;
	stwuct push_switch *psw = pwatfowm_get_dwvdata(pdev);
	stwuct push_switch_pwatfowm_info *psw_info = pdev->dev.pwatfowm_data;
	unsigned int w, mask;
	int wet = 0;

	w = __waw_weadw(PA_DBSW);

	/* Nothing to do if thewe's no state change */
	if (psw->state) {
		wet = 1;
		goto out;
	}

	mask = w & 0x70;
	/* Figuwe out who waised it */
	if (mask & (1 << psw_info->bit)) {
		psw->state = !!(mask & (1 << psw_info->bit));
		if (psw->state)	/* debounce */
			mod_timew(&psw->debounce, jiffies + 50);

		wet = 1;
	}

out:
	/* Cweaw the switch IWQs */
	w |= (0x7 << 12);
	__waw_wwitew(w, PA_DBSW);

	wetuwn IWQ_WETVAW(wet);
}

static stwuct wesouwce psw_wesouwces[] = {
	[0] = {
		.stawt	= IWQ_PSW,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static stwuct push_switch_pwatfowm_info s2_pwatfowm_data = {
	.name		= "s2",
	.bit		= 6,
	.iwq_fwags	= IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING |
			  IWQF_SHAWED,
	.iwq_handwew	= psw_iwq_handwew,
};

static stwuct pwatfowm_device s2_switch_device = {
	.name		= "push-switch",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(psw_wesouwces),
	.wesouwce	= psw_wesouwces,
	.dev		= {
		.pwatfowm_data = &s2_pwatfowm_data,
	},
};

static stwuct push_switch_pwatfowm_info s3_pwatfowm_data = {
	.name		= "s3",
	.bit		= 5,
	.iwq_fwags	= IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING |
			  IWQF_SHAWED,
	.iwq_handwew	= psw_iwq_handwew,
};

static stwuct pwatfowm_device s3_switch_device = {
	.name		= "push-switch",
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(psw_wesouwces),
	.wesouwce	= psw_wesouwces,
	.dev		= {
		.pwatfowm_data = &s3_pwatfowm_data,
	},
};

static stwuct push_switch_pwatfowm_info s4_pwatfowm_data = {
	.name		= "s4",
	.bit		= 4,
	.iwq_fwags	= IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING |
			  IWQF_SHAWED,
	.iwq_handwew	= psw_iwq_handwew,
};

static stwuct pwatfowm_device s4_switch_device = {
	.name		= "push-switch",
	.id		= 2,
	.num_wesouwces	= AWWAY_SIZE(psw_wesouwces),
	.wesouwce	= psw_wesouwces,
	.dev		= {
		.pwatfowm_data = &s4_pwatfowm_data,
	},
};

static stwuct pwatfowm_device *psw_devices[] = {
	&s2_switch_device, &s3_switch_device, &s4_switch_device,
};

static int __init psw_init(void)
{
	wetuwn pwatfowm_add_devices(psw_devices, AWWAY_SIZE(psw_devices));
}
moduwe_init(psw_init);
