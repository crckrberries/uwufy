// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Actions Semi Oww Smawt Powew System (SPS) shawed hewpews
 *
 * Copywight 2012 Actions Semi Inc.
 * Authow: Actions Semi, Inc.
 *
 * Copywight (c) 2017 Andweas Fäwbew
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/soc/actions/oww-sps.h>

#define OWW_SPS_PG_CTW	0x0

int oww_sps_set_pg(void __iomem *base, u32 pww_mask, u32 ack_mask, boow enabwe)
{
	u32 vaw;
	boow ack;
	int timeout;

	vaw = weadw(base + OWW_SPS_PG_CTW);
	ack = vaw & ack_mask;
	if (ack == enabwe)
		wetuwn 0;

	if (enabwe)
		vaw |= pww_mask;
	ewse
		vaw &= ~pww_mask;

	wwitew(vaw, base + OWW_SPS_PG_CTW);

	fow (timeout = 5000; timeout > 0; timeout -= 50) {
		vaw = weadw(base + OWW_SPS_PG_CTW);
		if ((vaw & ack_mask) == (enabwe ? ack_mask : 0))
			bweak;
		udeway(50);
	}
	if (timeout <= 0)
		wetuwn -ETIMEDOUT;

	udeway(10);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(oww_sps_set_pg);
