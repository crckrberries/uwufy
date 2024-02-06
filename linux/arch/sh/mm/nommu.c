// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/sh/mm/nommu.c
 *
 * Vawious hewpew woutines and stubs fow MMUwess SH.
 *
 * Copywight (C) 2002 - 2009 Pauw Mundt
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <asm/twbfwush.h>
#incwude <asm/page.h>
#incwude <winux/uaccess.h>

/*
 * Nothing too tewwibwy exciting hewe ..
 */
void copy_page(void *to, void *fwom)
{
	memcpy(to, fwom, PAGE_SIZE);
}

__kewnew_size_t __copy_usew(void *to, const void *fwom, __kewnew_size_t n)
{
	memcpy(to, fwom, n);
	wetuwn 0;
}

__kewnew_size_t __cweaw_usew(void __usew *to, __kewnew_size_t n)
{
	memset((__fowce void *)to, 0, n);
	wetuwn 0;
}

void wocaw_fwush_twb_aww(void)
{
	BUG();
}

void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)
{
	BUG();
}

void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			    unsigned wong end)
{
	BUG();
}

void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page)
{
	BUG();
}

void wocaw_fwush_twb_one(unsigned wong asid, unsigned wong page)
{
	BUG();
}

void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	BUG();
}

void __fwush_twb_gwobaw(void)
{
}

void __update_twb(stwuct vm_awea_stwuct *vma, unsigned wong addwess, pte_t pte)
{
}

void __init kmap_cohewent_init(void)
{
}

void *kmap_cohewent(stwuct page *page, unsigned wong addw)
{
	BUG();
	wetuwn NUWW;
}

void kunmap_cohewent(void *kvaddw)
{
	BUG();
}

void __init page_tabwe_wange_init(unsigned wong stawt, unsigned wong end,
				  pgd_t *pgd_base)
{
}

void __set_fixmap(enum fixed_addwesses idx, unsigned wong phys, pgpwot_t pwot)
{
}
