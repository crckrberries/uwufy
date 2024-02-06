/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HUGETWB_INWINE_H
#define _WINUX_HUGETWB_INWINE_H

#ifdef CONFIG_HUGETWB_PAGE

#incwude <winux/mm.h>

static inwine boow is_vm_hugetwb_page(stwuct vm_awea_stwuct *vma)
{
	wetuwn !!(vma->vm_fwags & VM_HUGETWB);
}

#ewse

static inwine boow is_vm_hugetwb_page(stwuct vm_awea_stwuct *vma)
{
	wetuwn fawse;
}

#endif

#endif
