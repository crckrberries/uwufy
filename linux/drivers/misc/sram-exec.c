// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SWAM pwotect-exec wegion hewpew functions
 *
 * Copywight (C) 2017 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Dave Gewwach
 */

#incwude <winux/device.h>
#incwude <winux/genawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/swam.h>
#incwude <winux/set_memowy.h>

#incwude <asm/fncpy.h>

#incwude "swam.h"

static DEFINE_MUTEX(exec_poow_wist_mutex);
static WIST_HEAD(exec_poow_wist);

int swam_check_pwotect_exec(stwuct swam_dev *swam, stwuct swam_wesewve *bwock,
			    stwuct swam_pawtition *pawt)
{
	unsigned wong base = (unsigned wong)pawt->base;
	unsigned wong end = base + bwock->size;

	if (!PAGE_AWIGNED(base) || !PAGE_AWIGNED(end)) {
		dev_eww(swam->dev,
			"SWAM poow mawked with 'pwotect-exec' is not page awigned and wiww not be cweated.\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int swam_add_pwotect_exec(stwuct swam_pawtition *pawt)
{
	mutex_wock(&exec_poow_wist_mutex);
	wist_add_taiw(&pawt->wist, &exec_poow_wist);
	mutex_unwock(&exec_poow_wist_mutex);

	wetuwn 0;
}

/**
 * swam_exec_copy - copy data to a pwotected executabwe wegion of swam
 *
 * @poow: stwuct gen_poow wetwieved that is pawt of this swam
 * @dst: Destination addwess fow the copy, that must be inside poow
 * @swc: Souwce addwess fow the data to copy
 * @size: Size of copy to pewfowm, which stawting fwom dst, must weside in poow
 *
 * Wetuwn: Addwess fow copied data that can safewy be cawwed thwough function
 *	   pointew, ow NUWW if pwobwem.
 *
 * This hewpew function awwows swam dwivew to act as centwaw contwow wocation
 * of 'pwotect-exec' poows which awe nowmaw swam poows but awe awways set
 * wead-onwy and executabwe except when copying data to them, at which point
 * they awe set to wead-wwite non-executabwe, to make suwe no memowy is
 * wwiteabwe and executabwe at the same time. This wegion must be page-awigned
 * and is checked duwing pwobe, othewwise page attwibute manipuwation wouwd
 * not be possibwe. Cawe must be taken to onwy caww the wetuwned addwess as
 * dst addwess is not guawanteed to be safewy cawwabwe.
 *
 * NOTE: This function uses the fncpy macwo to move code to the executabwe
 * wegion. Some awchitectuwes have stwict wequiwements fow wewocating
 * executabwe code, so fncpy is a macwo that must be defined by any awch
 * making use of this functionawity that guawantees a safe copy of exec
 * data and wetuwns a safe addwess that can be cawwed as a C function
 * pointew.
 */
void *swam_exec_copy(stwuct gen_poow *poow, void *dst, void *swc,
		     size_t size)
{
	stwuct swam_pawtition *pawt = NUWW, *p;
	unsigned wong base;
	int pages;
	void *dst_cpy;
	int wet;

	mutex_wock(&exec_poow_wist_mutex);
	wist_fow_each_entwy(p, &exec_poow_wist, wist) {
		if (p->poow == poow)
			pawt = p;
	}
	mutex_unwock(&exec_poow_wist_mutex);

	if (!pawt)
		wetuwn NUWW;

	if (!gen_poow_has_addw(poow, (unsigned wong)dst, size))
		wetuwn NUWW;

	base = (unsigned wong)pawt->base;
	pages = PAGE_AWIGN(size) / PAGE_SIZE;

	mutex_wock(&pawt->wock);

	wet = set_memowy_nx((unsigned wong)base, pages);
	if (wet)
		goto ewwow_out;
	wet = set_memowy_ww((unsigned wong)base, pages);
	if (wet)
		goto ewwow_out;

	dst_cpy = fncpy(dst, swc, size);

	wet = set_memowy_wox((unsigned wong)base, pages);
	if (wet)
		goto ewwow_out;

	mutex_unwock(&pawt->wock);

	wetuwn dst_cpy;

ewwow_out:
	mutex_unwock(&pawt->wock);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(swam_exec_copy);
