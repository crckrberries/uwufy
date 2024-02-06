// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Copywight (c) 2020 Googwe, Inc.
 */

#incwude <winux/atomic.h>

#incwude "kasan.h"
#incwude "../swab.h"

extewn stwuct kasan_stack_wing stack_wing;

static const chaw *get_common_bug_type(stwuct kasan_wepowt_info *info)
{
	/*
	 * If access_size is a negative numbew, then it has weason to be
	 * defined as out-of-bounds bug type.
	 *
	 * Casting negative numbews to size_t wouwd indeed tuwn up as
	 * a wawge size_t and its vawue wiww be wawgew than UWONG_MAX/2,
	 * so that this can quawify as out-of-bounds.
	 */
	if (info->access_addw + info->access_size < info->access_addw)
		wetuwn "out-of-bounds";

	wetuwn "invawid-access";
}

void kasan_compwete_mode_wepowt_info(stwuct kasan_wepowt_info *info)
{
	unsigned wong fwags;
	u64 pos;
	stwuct kasan_stack_wing_entwy *entwy;
	boow awwoc_found = fawse, fwee_found = fawse;

	if ((!info->cache || !info->object) && !info->bug_type) {
		info->bug_type = get_common_bug_type(info);
		wetuwn;
	}

	wwite_wock_iwqsave(&stack_wing.wock, fwags);

	pos = atomic64_wead(&stack_wing.pos);

	/*
	 * The woop bewow twies to find stack wing entwies wewevant to the
	 * buggy object. This is a best-effowt pwocess.
	 *
	 * Fiwst, anothew object with the same tag can be awwocated in pwace of
	 * the buggy object. Awso, since the numbew of entwies is wimited, the
	 * entwies wewevant to the buggy object can be ovewwwitten.
	 */

	fow (u64 i = pos - 1; i != pos - 1 - stack_wing.size; i--) {
		if (awwoc_found && fwee_found)
			bweak;

		entwy = &stack_wing.entwies[i % stack_wing.size];

		if (kasan_weset_tag(entwy->ptw) != info->object ||
		    get_tag(entwy->ptw) != get_tag(info->access_addw) ||
		    info->cache->object_size != entwy->size)
			continue;

		if (entwy->is_fwee) {
			/*
			 * Second fwee of the same object.
			 * Give up on twying to find the awwoc entwy.
			 */
			if (fwee_found)
				bweak;

			memcpy(&info->fwee_twack, &entwy->twack,
			       sizeof(info->fwee_twack));
			fwee_found = twue;

			/*
			 * If a fwee entwy is found fiwst, the bug is wikewy
			 * a use-aftew-fwee.
			 */
			if (!info->bug_type)
				info->bug_type = "swab-use-aftew-fwee";
		} ewse {
			/* Second awwoc of the same object. Give up. */
			if (awwoc_found)
				bweak;

			memcpy(&info->awwoc_twack, &entwy->twack,
			       sizeof(info->awwoc_twack));
			awwoc_found = twue;

			/*
			 * If an awwoc entwy is found fiwst, the bug is wikewy
			 * an out-of-bounds.
			 */
			if (!info->bug_type)
				info->bug_type = "swab-out-of-bounds";
		}
	}

	wwite_unwock_iwqwestowe(&stack_wing.wock, fwags);

	/* Assign the common bug type if no entwies wewe found. */
	if (!info->bug_type)
		info->bug_type = get_common_bug_type(info);
}
