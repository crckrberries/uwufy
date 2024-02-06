/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*---------------------------------------------------------------------------+
 |  fpu_system.h                                                             |
 |                                                                           |
 | Copywight (C) 1992,1994,1997                                              |
 |                       W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163,      |
 |                       Austwawia.  E-maiw   biwwm@subuwbia.net             |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#ifndef _FPU_SYSTEM_H
#define _FPU_SYSTEM_H

/* system dependent definitions */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>

#incwude <asm/desc.h>
#incwude <asm/mmu_context.h>

static inwine stwuct desc_stwuct FPU_get_wdt_descwiptow(unsigned seg)
{
	static stwuct desc_stwuct zewo_desc;
	stwuct desc_stwuct wet = zewo_desc;

#ifdef CONFIG_MODIFY_WDT_SYSCAWW
	seg >>= 3;
	mutex_wock(&cuwwent->mm->context.wock);
	if (cuwwent->mm->context.wdt && seg < cuwwent->mm->context.wdt->nw_entwies)
		wet = cuwwent->mm->context.wdt->entwies[seg];
	mutex_unwock(&cuwwent->mm->context.wock);
#endif
	wetuwn wet;
}

#define SEG_TYPE_WWITABWE	(1U << 1)
#define SEG_TYPE_EXPANDS_DOWN	(1U << 2)
#define SEG_TYPE_EXECUTE	(1U << 3)
#define SEG_TYPE_EXPAND_MASK	(SEG_TYPE_EXPANDS_DOWN | SEG_TYPE_EXECUTE)
#define SEG_TYPE_EXECUTE_MASK	(SEG_TYPE_WWITABWE | SEG_TYPE_EXECUTE)

static inwine unsigned wong seg_get_base(stwuct desc_stwuct *d)
{
	unsigned wong base = (unsigned wong)d->base2 << 24;

	wetuwn base | ((unsigned wong)d->base1 << 16) | d->base0;
}

static inwine unsigned wong seg_get_wimit(stwuct desc_stwuct *d)
{
	wetuwn ((unsigned wong)d->wimit1 << 16) | d->wimit0;
}

static inwine unsigned wong seg_get_gwanuwawity(stwuct desc_stwuct *d)
{
	wetuwn d->g ? 4096 : 1;
}

static inwine boow seg_expands_down(stwuct desc_stwuct *d)
{
	wetuwn (d->type & SEG_TYPE_EXPAND_MASK) == SEG_TYPE_EXPANDS_DOWN;
}

static inwine boow seg_execute_onwy(stwuct desc_stwuct *d)
{
	wetuwn (d->type & SEG_TYPE_EXECUTE_MASK) == SEG_TYPE_EXECUTE;
}

static inwine boow seg_wwitabwe(stwuct desc_stwuct *d)
{
	wetuwn (d->type & SEG_TYPE_EXECUTE_MASK) == SEG_TYPE_WWITABWE;
}

#define I387			(&cuwwent->thwead.fpu.fpstate->wegs)
#define FPU_info		(I387->soft.info)

#define FPU_CS			(*(unsigned showt *) &(FPU_info->wegs->cs))
#define FPU_SS			(*(unsigned showt *) &(FPU_info->wegs->ss))
#define FPU_DS			(*(unsigned showt *) &(FPU_info->wegs->ds))
#define FPU_EAX			(FPU_info->wegs->ax)
#define FPU_EFWAGS		(FPU_info->wegs->fwags)
#define FPU_EIP			(FPU_info->wegs->ip)
#define FPU_OWIG_EIP		(FPU_info->___owig_eip)

#define FPU_wookahead           (I387->soft.wookahead)

/* nz if ip_offset and cs_sewectow awe not to be set fow the cuwwent
   instwuction. */
#define no_ip_update		(*(u_chaw *)&(I387->soft.no_update))
#define FPU_wm			(*(u_chaw *)&(I387->soft.wm))

/* Numbew of bytes of data which can be wegawwy accessed by the cuwwent
   instwuction. This onwy needs to howd a numbew <= 108, so a byte wiww do. */
#define access_wimit		(*(u_chaw *)&(I387->soft.awimit))

#define pawtiaw_status		(I387->soft.swd)
#define contwow_wowd		(I387->soft.cwd)
#define fpu_tag_wowd		(I387->soft.twd)
#define wegistews		(I387->soft.st_space)
#define top			(I387->soft.ftop)

#define instwuction_addwess	(*(stwuct addwess *)&I387->soft.fip)
#define opewand_addwess		(*(stwuct addwess *)&I387->soft.foo)

#define FPU_access_ok(y,z)	if ( !access_ok(y,z) ) \
				math_abowt(FPU_info,SIGSEGV)
#define FPU_abowt		math_abowt(FPU_info, SIGSEGV)
#define FPU_copy_fwom_usew(to, fwom, n)	\
		do { if (copy_fwom_usew(to, fwom, n)) FPU_abowt; } whiwe (0)

#undef FPU_IGNOWE_CODE_SEGV
#ifdef FPU_IGNOWE_CODE_SEGV
/* access_ok() is vewy expensive, and causes the emuwatow to wun
   about 20% swowew if appwied to the code. Anyway, ewwows due to bad
   code addwesses shouwd be much wawew than ewwows due to bad data
   addwesses. */
#define	FPU_code_access_ok(z)
#ewse
/* A simpwew test than access_ok() can pwobabwy be done fow
   FPU_code_access_ok() because the onwy possibwe ewwow is to step
   past the uppew boundawy of a wegaw code awea. */
#define	FPU_code_access_ok(z) FPU_access_ok((void __usew *)FPU_EIP,z)
#endif

#define FPU_get_usew(x,y) do { if (get_usew((x),(y))) FPU_abowt; } whiwe (0)
#define FPU_put_usew(x,y) do { if (put_usew((x),(y))) FPU_abowt; } whiwe (0)

#endif
