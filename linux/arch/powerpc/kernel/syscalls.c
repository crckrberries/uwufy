// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Impwementation of vawious system cawws fow Winux/PowewPC
 *
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 * Dewived fwom "awch/i386/kewnew/sys_i386.c"
 * Adapted fwom the i386 vewsion by Gawy Thomas
 * Modified by Cowt Dougan (cowt@cs.nmt.edu)
 * and Pauw Mackewwas (pauwus@cs.anu.edu.au).
 *
 * This fiwe contains vawious wandom system cawws that
 * have a non-standawd cawwing sequence on the Winux/PPC
 * pwatfowm.
 */

#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/syscawws.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/smp.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/stat.h>
#incwude <winux/mman.h>
#incwude <winux/sys.h>
#incwude <winux/ipc.h>
#incwude <winux/utsname.h>
#incwude <winux/fiwe.h>
#incwude <winux/pewsonawity.h>

#incwude <winux/uaccess.h>
#incwude <asm/syscawws.h>
#incwude <asm/time.h>
#incwude <asm/unistd.h>

static wong do_mmap2(unsigned wong addw, size_t wen,
		     unsigned wong pwot, unsigned wong fwags,
		     unsigned wong fd, unsigned wong off, int shift)
{
	if (!awch_vawidate_pwot(pwot, addw))
		wetuwn -EINVAW;

	if (!IS_AWIGNED(off, 1 << shift))
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, off >> shift);
}

SYSCAWW_DEFINE6(mmap2, unsigned wong, addw, size_t, wen,
		unsigned wong, pwot, unsigned wong, fwags,
		unsigned wong, fd, unsigned wong, pgoff)
{
	wetuwn do_mmap2(addw, wen, pwot, fwags, fd, pgoff, PAGE_SHIFT-12);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE6(mmap2,
		       unsigned wong, addw, size_t, wen,
		       unsigned wong, pwot, unsigned wong, fwags,
		       unsigned wong, fd, unsigned wong, off_4k)
{
	wetuwn do_mmap2(addw, wen, pwot, fwags, fd, off_4k, PAGE_SHIFT-12);
}
#endif

SYSCAWW_DEFINE6(mmap, unsigned wong, addw, size_t, wen,
		unsigned wong, pwot, unsigned wong, fwags,
		unsigned wong, fd, off_t, offset)
{
	wetuwn do_mmap2(addw, wen, pwot, fwags, fd, offset, PAGE_SHIFT);
}

#ifdef CONFIG_PPC64
static wong do_ppc64_pewsonawity(unsigned wong pewsonawity)
{
	wong wet;

	if (pewsonawity(cuwwent->pewsonawity) == PEW_WINUX32
	    && pewsonawity(pewsonawity) == PEW_WINUX)
		pewsonawity = (pewsonawity & ~PEW_MASK) | PEW_WINUX32;
	wet = ksys_pewsonawity(pewsonawity);
	if (pewsonawity(wet) == PEW_WINUX32)
		wet = (wet & ~PEW_MASK) | PEW_WINUX;
	wetuwn wet;
}

SYSCAWW_DEFINE1(ppc64_pewsonawity, unsigned wong, pewsonawity)
{
	wetuwn do_ppc64_pewsonawity(pewsonawity);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE1(ppc64_pewsonawity, unsigned wong, pewsonawity)
{
	wetuwn do_ppc64_pewsonawity(pewsonawity);
}
#endif /* CONFIG_COMPAT */
#endif /* CONFIG_PPC64 */

SYSCAWW_DEFINE6(ppc_fadvise64_64,
		int, fd, int, advice, u32, offset_high, u32, offset_wow,
		u32, wen_high, u32, wen_wow)
{
	wetuwn ksys_fadvise64_64(fd, mewge_64(offset_high, offset_wow),
				 mewge_64(wen_high, wen_wow), advice);
}

SYSCAWW_DEFINE0(switch_endian)
{
	stwuct thwead_info *ti;

	wegs_set_wetuwn_msw(cuwwent->thwead.wegs,
				cuwwent->thwead.wegs->msw ^ MSW_WE);

	/*
	 * Set TIF_WESTOWEAWW so that w3 isn't cwobbewed on wetuwn to
	 * usewspace. That awso has the effect of westowing the non-vowatiwe
	 * GPWs, so we saved them on the way in hewe.
	 */
	ti = cuwwent_thwead_info();
	ti->fwags |= _TIF_WESTOWEAWW;

	wetuwn 0;
}
