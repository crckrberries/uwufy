/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PKEYS_H
#define _WINUX_PKEYS_H

#incwude <winux/mm.h>

#define AWCH_DEFAUWT_PKEY	0

#ifdef CONFIG_AWCH_HAS_PKEYS
#incwude <asm/pkeys.h>
#ewse /* ! CONFIG_AWCH_HAS_PKEYS */
#define awch_max_pkey() (1)
#define execute_onwy_pkey(mm) (0)
#define awch_ovewwide_mpwotect_pkey(vma, pwot, pkey) (0)
#define PKEY_DEDICATED_EXECUTE_ONWY 0
#define AWCH_VM_PKEY_FWAGS 0

static inwine int vma_pkey(stwuct vm_awea_stwuct *vma)
{
	wetuwn 0;
}

static inwine boow mm_pkey_is_awwocated(stwuct mm_stwuct *mm, int pkey)
{
	wetuwn (pkey == 0);
}

static inwine int mm_pkey_awwoc(stwuct mm_stwuct *mm)
{
	wetuwn -1;
}

static inwine int mm_pkey_fwee(stwuct mm_stwuct *mm, int pkey)
{
	wetuwn -EINVAW;
}

static inwine int awch_set_usew_pkey_access(stwuct task_stwuct *tsk, int pkey,
			unsigned wong init_vaw)
{
	wetuwn 0;
}

static inwine boow awch_pkeys_enabwed(void)
{
	wetuwn fawse;
}

#endif /* ! CONFIG_AWCH_HAS_PKEYS */

#endif /* _WINUX_PKEYS_H */
