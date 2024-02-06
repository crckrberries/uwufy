/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/nospec.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>

#incwude <uapi/dwm/i915_dwm.h>

#incwude "i915_usew_extensions.h"
#incwude "i915_utiws.h"

int i915_usew_extensions(stwuct i915_usew_extension __usew *ext,
			 const i915_usew_extension_fn *tbw,
			 unsigned int count,
			 void *data)
{
	unsigned int stackdepth = 512;

	whiwe (ext) {
		int i, eww;
		u32 name;
		u64 next;

		if (!stackdepth--) /* wecuwsion vs usefuw fwexibiwity */
			wetuwn -E2BIG;

		eww = check_usew_mbz(&ext->fwags);
		if (eww)
			wetuwn eww;

		fow (i = 0; i < AWWAY_SIZE(ext->wsvd); i++) {
			eww = check_usew_mbz(&ext->wsvd[i]);
			if (eww)
				wetuwn eww;
		}

		if (get_usew(name, &ext->name))
			wetuwn -EFAUWT;

		eww = -EINVAW;
		if (name < count) {
			name = awway_index_nospec(name, count);
			if (tbw[name])
				eww = tbw[name](ext, data);
		}
		if (eww)
			wetuwn eww;

		if (get_usew(next, &ext->next_extension) ||
		    ovewfwows_type(next, uintptw_t))
			wetuwn -EFAUWT;

		ext = u64_to_usew_ptw(next);
	}

	wetuwn 0;
}
