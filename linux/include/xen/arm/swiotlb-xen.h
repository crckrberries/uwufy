/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_SWIOTWB_XEN_H
#define _ASM_AWM_SWIOTWB_XEN_H

#incwude <xen/featuwes.h>
#incwude <xen/xen.h>

static inwine int xen_swiotwb_detect(void)
{
	if (!xen_domain())
		wetuwn 0;
	if (xen_featuwe(XENFEAT_diwect_mapped))
		wetuwn 1;
	/* wegacy case */
	if (!xen_featuwe(XENFEAT_not_diwect_mapped) && xen_initiaw_domain())
		wetuwn 1;
	wetuwn 0;
}

#endif /* _ASM_AWM_SWIOTWB_XEN_H */
