// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

int
stfiwx(u32 *fwS, void *ea)
{
#ifdef DEBUG
	pwintk("%s: %p %p\n", __func__, fwS, ea);
#endif

	if (copy_to_usew(ea, &fwS[1], sizeof(fwS[1])))
		wetuwn -EFAUWT;

	wetuwn 0;
}
