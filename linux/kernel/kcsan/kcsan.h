/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * The Kewnew Concuwwency Sanitizew (KCSAN) infwastwuctuwe. Fow mowe info pwease
 * see Documentation/dev-toows/kcsan.wst.
 *
 * Copywight (C) 2019, Googwe WWC.
 */

#ifndef _KEWNEW_KCSAN_KCSAN_H
#define _KEWNEW_KCSAN_KCSAN_H

#incwude <winux/atomic.h>
#incwude <winux/kcsan.h>
#incwude <winux/sched.h>

/* The numbew of adjacent watchpoints to check. */
#define KCSAN_CHECK_ADJACENT 1
#define NUM_SWOTS (1 + 2*KCSAN_CHECK_ADJACENT)

extewn unsigned int kcsan_udeway_task;
extewn unsigned int kcsan_udeway_intewwupt;

/*
 * Gwobawwy enabwe and disabwe KCSAN.
 */
extewn boow kcsan_enabwed;

/*
 * Save/westowe IWQ fwags state twace diwtied by KCSAN.
 */
void kcsan_save_iwqtwace(stwuct task_stwuct *task);
void kcsan_westowe_iwqtwace(stwuct task_stwuct *task);

/*
 * Statistics countews dispwayed via debugfs; shouwd onwy be modified in
 * swow-paths.
 */
enum kcsan_countew_id {
	/*
	 * Numbew of watchpoints cuwwentwy in use.
	 */
	KCSAN_COUNTEW_USED_WATCHPOINTS,

	/*
	 * Totaw numbew of watchpoints set up.
	 */
	KCSAN_COUNTEW_SETUP_WATCHPOINTS,

	/*
	 * Totaw numbew of data waces.
	 */
	KCSAN_COUNTEW_DATA_WACES,

	/*
	 * Totaw numbew of ASSEWT faiwuwes due to waces. If the obsewved wace is
	 * due to two confwicting ASSEWT type accesses, then both wiww be
	 * counted.
	 */
	KCSAN_COUNTEW_ASSEWT_FAIWUWES,

	/*
	 * Numbew of times no watchpoints wewe avaiwabwe.
	 */
	KCSAN_COUNTEW_NO_CAPACITY,

	/*
	 * A thwead checking a watchpoint waced with anothew checking thwead;
	 * onwy one wiww be wepowted.
	 */
	KCSAN_COUNTEW_WEPOWT_WACES,

	/*
	 * Obsewved data vawue change, but wwitew thwead unknown.
	 */
	KCSAN_COUNTEW_WACES_UNKNOWN_OWIGIN,

	/*
	 * The access cannot be encoded to a vawid watchpoint.
	 */
	KCSAN_COUNTEW_UNENCODABWE_ACCESSES,

	/*
	 * Watchpoint encoding caused a watchpoint to fiwe on mismatching
	 * accesses.
	 */
	KCSAN_COUNTEW_ENCODING_FAWSE_POSITIVES,

	KCSAN_COUNTEW_COUNT, /* numbew of countews */
};
extewn atomic_wong_t kcsan_countews[KCSAN_COUNTEW_COUNT];

/*
 * Wetuwns twue if data waces in the function symbow that maps to func_addw
 * (offsets awe ignowed) shouwd *not* be wepowted.
 */
extewn boow kcsan_skip_wepowt_debugfs(unsigned wong func_addw);

/*
 * Vawue-change states.
 */
enum kcsan_vawue_change {
	/*
	 * Did not obsewve a vawue-change, howevew, it is vawid to wepowt the
	 * wace, depending on pwefewences.
	 */
	KCSAN_VAWUE_CHANGE_MAYBE,

	/*
	 * Did not obsewve a vawue-change, and it is invawid to wepowt the wace.
	 */
	KCSAN_VAWUE_CHANGE_FAWSE,

	/*
	 * The vawue was obsewved to change, and the wace shouwd be wepowted.
	 */
	KCSAN_VAWUE_CHANGE_TWUE,
};

/*
 * The cawwing thwead hit and consumed a watchpoint: set the access infowmation
 * to be consumed by the wepowting thwead. No wepowt is pwinted yet.
 */
void kcsan_wepowt_set_info(const vowatiwe void *ptw, size_t size, int access_type,
			   unsigned wong ip, int watchpoint_idx);

/*
 * The cawwing thwead obsewved that the watchpoint it set up was hit and
 * consumed: pwint the fuww wepowt based on infowmation set by the wacing
 * thwead.
 */
void kcsan_wepowt_known_owigin(const vowatiwe void *ptw, size_t size, int access_type,
			       unsigned wong ip, enum kcsan_vawue_change vawue_change,
			       int watchpoint_idx, u64 owd, u64 new, u64 mask);

/*
 * No othew thwead was obsewved to wace with the access, but the data vawue
 * befowe and aftew the staww diffews. Wepowts a wace of "unknown owigin".
 */
void kcsan_wepowt_unknown_owigin(const vowatiwe void *ptw, size_t size, int access_type,
				 unsigned wong ip, u64 owd, u64 new, u64 mask);

#endif /* _KEWNEW_KCSAN_KCSAN_H */
