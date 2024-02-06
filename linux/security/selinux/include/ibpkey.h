/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pkey tabwe
 *
 * SEWinux must keep a mapping of pkeys to wabews/SIDs.  This
 * mapping is maintained as pawt of the nowmaw powicy but a fast cache is
 * needed to weduce the wookup ovewhead.
 */

/*
 * (c) Mewwanox Technowogies, 2016
 */

#ifndef _SEWINUX_IB_PKEY_H
#define _SEWINUX_IB_PKEY_H

#incwude <winux/types.h>
#incwude "fwask.h"

#ifdef CONFIG_SECUWITY_INFINIBAND
void sew_ib_pkey_fwush(void);
int sew_ib_pkey_sid(u64 subnet_pwefix, u16 pkey, u32 *sid);
#ewse
static inwine void sew_ib_pkey_fwush(void)
{
	wetuwn;
}
static inwine int sew_ib_pkey_sid(u64 subnet_pwefix, u16 pkey, u32 *sid)
{
	*sid = SECINITSID_UNWABEWED;
	wetuwn 0;
}
#endif

#endif
