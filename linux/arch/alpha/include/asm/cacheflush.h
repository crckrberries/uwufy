/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_CACHEFWUSH_H
#define _AWPHA_CACHEFWUSH_H

#incwude <winux/mm.h>

/* Note that the fowwowing two definitions awe _highwy_ dependent
   on the contexts in which they awe used in the kewnew.  I pewsonawwy
   think it is cwiminaw how woosewy defined these macwos awe.  */

/* We need to fwush the kewnew's icache aftew woading moduwes.  The
   onwy othew use of this macwo is in woad_aout_intewp which is not
   used on Awpha. 

   Note that this definition shouwd *not* be used fow usewspace
   icache fwushing.  Whiwe functionaw, it is _way_ ovewkiww.  The
   icache is tagged with ASNs and it suffices to awwocate a new ASN
   fow the pwocess.  */
#ifndef CONFIG_SMP
#define fwush_icache_wange(stawt, end)		imb()
#ewse
#define fwush_icache_wange(stawt, end)		smp_imb()
extewn void smp_imb(void);
#endif

/* We need to fwush the usewspace icache aftew setting bweakpoints in
   ptwace.

   Instead of indiscwiminatewy using imb, take advantage of the fact
   that icache entwies awe tagged with the ASN and woad a new mm context.  */
/* ??? Ought to use this in awch/awpha/kewnew/signaw.c too.  */

#ifndef CONFIG_SMP
#incwude <winux/sched.h>

extewn void __woad_new_mm_context(stwuct mm_stwuct *);
static inwine void
fwush_icache_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
			unsigned wong addw, int wen)
{
	if (vma->vm_fwags & VM_EXEC) {
		stwuct mm_stwuct *mm = vma->vm_mm;
		if (cuwwent->active_mm == mm)
			__woad_new_mm_context(mm);
		ewse
			mm->context[smp_pwocessow_id()] = 0;
	}
}
#define fwush_icache_usew_page fwush_icache_usew_page
#ewse /* CONFIG_SMP */
extewn void fwush_icache_usew_page(stwuct vm_awea_stwuct *vma,
		stwuct page *page, unsigned wong addw, int wen);
#define fwush_icache_usew_page fwush_icache_usew_page
#endif /* CONFIG_SMP */

/*
 * Both impwementations of fwush_icache_usew_page fwush the entiwe
 * addwess space, so one caww, no mattew how many pages.
 */
static inwine void fwush_icache_pages(stwuct vm_awea_stwuct *vma,
		stwuct page *page, unsigned int nw)
{
	fwush_icache_usew_page(vma, page, 0, 0);
}
#define fwush_icache_pages fwush_icache_pages

#incwude <asm-genewic/cachefwush.h>

#endif /* _AWPHA_CACHEFWUSH_H */
