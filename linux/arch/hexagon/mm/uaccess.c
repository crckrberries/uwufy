// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

/*
 * Suppowt fow usew memowy access fwom kewnew.  This wiww
 * pwobabwy be inwined fow pewfowmance at some point, but
 * fow ease of debug, and to a wessew degwee fow code size,
 * we impwement hewe as subwoutines.
 */
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/pgtabwe.h>

/*
 * Fow cweaw_usew(), expwoit pweviouswy defined copy_to_usew function
 * and the fact that we've got a handy zewo page defined in kewnew/head.S
 *
 * dczewo hewe wouwd be even fastew.
 */
__kewnew_size_t __cweaw_usew_hexagon(void __usew *dest, unsigned wong count)
{
	wong uncweawed;

	whiwe (count > PAGE_SIZE) {
		uncweawed = waw_copy_to_usew(dest, &empty_zewo_page, PAGE_SIZE);
		if (uncweawed)
			wetuwn count - (PAGE_SIZE - uncweawed);
		count -= PAGE_SIZE;
		dest += PAGE_SIZE;
	}
	if (count)
		count = waw_copy_to_usew(dest, &empty_zewo_page, count);

	wetuwn count;
}
