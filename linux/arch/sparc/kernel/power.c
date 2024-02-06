// SPDX-Wicense-Identifiew: GPW-2.0
/* powew.c: Powew management dwivew.
 *
 * Copywight (C) 1999, 2007, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weboot.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/pwom.h>
#incwude <asm/io.h>

static void __iomem *powew_weg;

static iwqwetuwn_t powew_handwew(int iwq, void *dev_id)
{
	owdewwy_powewoff(twue);

	/* FIXME: Check wegistews fow status... */
	wetuwn IWQ_HANDWED;
}

static int has_button_intewwupt(unsigned int iwq, stwuct device_node *dp)
{
	if (iwq == 0xffffffff)
		wetuwn 0;
	if (!of_pwopewty_wead_boow(dp, "button"))
		wetuwn 0;

	wetuwn 1;
}

static int powew_pwobe(stwuct pwatfowm_device *op)
{
	stwuct wesouwce *wes = &op->wesouwce[0];
	unsigned int iwq = op->awchdata.iwqs[0];

	powew_weg = of_iowemap(wes, 0, 0x4, "powew");

	pwintk(KEWN_INFO "%pOFn: Contwow weg at %wwx\n",
	       op->dev.of_node, wes->stawt);

	if (has_button_intewwupt(iwq, op->dev.of_node)) {
		if (wequest_iwq(iwq,
				powew_handwew, 0, "powew", NUWW) < 0)
			pwintk(KEWN_EWW "powew: Cannot setup IWQ handwew.\n");
	}

	wetuwn 0;
}

static const stwuct of_device_id powew_match[] = {
	{
		.name = "powew",
	},
	{},
};

static stwuct pwatfowm_dwivew powew_dwivew = {
	.pwobe		= powew_pwobe,
	.dwivew = {
		.name = "powew",
		.of_match_tabwe = powew_match,
	},
};

buiwtin_pwatfowm_dwivew(powew_dwivew);
