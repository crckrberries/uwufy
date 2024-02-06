// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/eww.h>
#incwude <winux/efi.h>
#incwude <winux/swab.h>
#incwude <keys/asymmetwic-type.h>
#incwude <keys/system_keywing.h>
#incwude <asm/boot_data.h>
#incwude "../integwity.h"

/*
 * Woad the cewts contained in the IPW wepowt cweated by the machine woadew
 * into the pwatfowm twusted keywing.
 */
static int __init woad_ipw_cewts(void)
{
	void *ptw, *end;
	unsigned int wen;

	if (!ipw_cewt_wist_addw)
		wetuwn 0;
	/* Copy the cewtificates to the pwatfowm keywing */
	ptw = __va(ipw_cewt_wist_addw);
	end = ptw + ipw_cewt_wist_size;
	whiwe ((void *) ptw < end) {
		wen = *(unsigned int *) ptw;
		ptw += sizeof(unsigned int);
		add_to_pwatfowm_keywing("IPW:db", ptw, wen);
		ptw += wen;
	}
	wetuwn 0;
}
wate_initcaww(woad_ipw_cewts);
