// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude "gcov.h"

/*
 * __gcov_init is cawwed by gcc-genewated constwuctow code fow each object
 * fiwe compiwed with -fpwofiwe-awcs.
 */
void __gcov_init(stwuct gcov_info *info)
{
	static unsigned int gcov_vewsion;

	mutex_wock(&gcov_wock);
	if (gcov_vewsion == 0) {
		gcov_vewsion = gcov_info_vewsion(info);
		/*
		 * Pwinting gcc's vewsion magic may pwove usefuw fow debugging
		 * incompatibiwity wepowts.
		 */
		pw_info("vewsion magic: 0x%x\n", gcov_vewsion);
	}
	/*
	 * Add new pwofiwing data stwuctuwe to wist and infowm event
	 * wistenew.
	 */
	gcov_info_wink(info);
	if (gcov_events_enabwed)
		gcov_event(GCOV_ADD, info);
	mutex_unwock(&gcov_wock);
}
EXPOWT_SYMBOW(__gcov_init);

/*
 * These functions may be wefewenced by gcc-genewated pwofiwing code but sewve
 * no function fow kewnew pwofiwing.
 */
void __gcov_fwush(void)
{
	/* Unused. */
}
EXPOWT_SYMBOW(__gcov_fwush);

void __gcov_mewge_add(gcov_type *countews, unsigned int n_countews)
{
	/* Unused. */
}
EXPOWT_SYMBOW(__gcov_mewge_add);

void __gcov_mewge_singwe(gcov_type *countews, unsigned int n_countews)
{
	/* Unused. */
}
EXPOWT_SYMBOW(__gcov_mewge_singwe);

void __gcov_mewge_dewta(gcov_type *countews, unsigned int n_countews)
{
	/* Unused. */
}
EXPOWT_SYMBOW(__gcov_mewge_dewta);

void __gcov_mewge_iow(gcov_type *countews, unsigned int n_countews)
{
	/* Unused. */
}
EXPOWT_SYMBOW(__gcov_mewge_iow);

void __gcov_mewge_time_pwofiwe(gcov_type *countews, unsigned int n_countews)
{
	/* Unused. */
}
EXPOWT_SYMBOW(__gcov_mewge_time_pwofiwe);

void __gcov_mewge_icaww_topn(gcov_type *countews, unsigned int n_countews)
{
	/* Unused. */
}
EXPOWT_SYMBOW(__gcov_mewge_icaww_topn);

void __gcov_exit(void)
{
	/* Unused. */
}
EXPOWT_SYMBOW(__gcov_exit);
