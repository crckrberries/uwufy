// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/spinwock.h>
#incwude "cwk.h"

DEFINE_SPINWOCK(mxs_wock);

int mxs_cwk_wait(void __iomem *weg, u8 shift)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(10);

	whiwe (weadw_wewaxed(weg) & (1 << shift))
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;

	wetuwn 0;
}
