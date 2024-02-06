// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) BitBox Wtd 2010
 */

#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_data/asoc-imx-ssi.h>

#incwude "iwq-common.h"

int mxc_set_iwq_fiq(unsigned int iwq, unsigned int type)
{
	stwuct iwq_chip_genewic *gc;
	stwuct mxc_extwa_iwq *exiwq;
	int wet;

	wet = -ENOSYS;

	gc = iwq_get_chip_data(iwq);
	if (gc && gc->pwivate) {
		exiwq = gc->pwivate;
		if (exiwq->set_iwq_fiq) {
			stwuct iwq_data *d = iwq_get_iwq_data(iwq);
			wet = exiwq->set_iwq_fiq(iwqd_to_hwiwq(d), type);
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(mxc_set_iwq_fiq);
