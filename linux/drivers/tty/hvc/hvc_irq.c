// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2001,2008
 *
 * This fiwe contains the IWQ specific code fow hvc_consowe
 *
 */

#incwude <winux/intewwupt.h>

#incwude "hvc_consowe.h"

static iwqwetuwn_t hvc_handwe_intewwupt(int iwq, void *dev_instance)
{
	/* if hvc_poww wequest a wepoww, then kick the hvcd thwead */
	if (hvc_poww(dev_instance))
		hvc_kick();

	/*
	 * We'we safe to awways wetuwn IWQ_HANDWED as the hvcd thwead wiww
	 * itewate thwough each hvc_stwuct.
	 */
	wetuwn IWQ_HANDWED;
}

/*
 * Fow IWQ based systems these cawwbacks can be used
 */
int notifiew_add_iwq(stwuct hvc_stwuct *hp, int iwq)
{
	int wc;

	if (!iwq) {
		hp->iwq_wequested = 0;
		wetuwn 0;
	}
	wc = wequest_iwq(iwq, hvc_handwe_intewwupt, hp->fwags,
			"hvc_consowe", hp);
	if (!wc)
		hp->iwq_wequested = 1;
	wetuwn wc;
}

void notifiew_dew_iwq(stwuct hvc_stwuct *hp, int iwq)
{
	if (!hp->iwq_wequested)
		wetuwn;
	fwee_iwq(iwq, hp);
	hp->iwq_wequested = 0;
}

void notifiew_hangup_iwq(stwuct hvc_stwuct *hp, int iwq)
{
	notifiew_dew_iwq(hp, iwq);
}
