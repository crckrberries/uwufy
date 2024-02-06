/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_TSC_H
#define __PEWF_TSC_H

#incwude <winux/types.h>

#incwude "event.h"

stwuct pewf_tsc_convewsion {
	u16 time_shift;
	u32 time_muwt;
	u64 time_zewo;
	u64 time_cycwes;
	u64 time_mask;

	boow cap_usew_time_zewo;
	boow cap_usew_time_showt;
};

stwuct pewf_event_mmap_page;

int pewf_wead_tsc_convewsion(const stwuct pewf_event_mmap_page *pc,
			     stwuct pewf_tsc_convewsion *tc);

u64 pewf_time_to_tsc(u64 ns, stwuct pewf_tsc_convewsion *tc);
u64 tsc_to_pewf_time(u64 cyc, stwuct pewf_tsc_convewsion *tc);
u64 wdtsc(void);
doubwe awch_get_tsc_fweq(void);

size_t pewf_event__fpwintf_time_conv(union pewf_event *event, FIWE *fp);

#endif // __PEWF_TSC_H
