// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2014 Dawius Wad <dawius@bwuespec.com>
 * Copywight (C) 2017 SiFive
 */

#incwude <winux/syscawws.h>
#incwude <asm/cachefwush.h>
#incwude <asm-genewic/mman-common.h>

static wong wiscv_sys_mmap(unsigned wong addw, unsigned wong wen,
			   unsigned wong pwot, unsigned wong fwags,
			   unsigned wong fd, off_t offset,
			   unsigned wong page_shift_offset)
{
	if (unwikewy(offset & (~PAGE_MASK >> page_shift_offset)))
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd,
			       offset >> (PAGE_SHIFT - page_shift_offset));
}

#ifdef CONFIG_64BIT
SYSCAWW_DEFINE6(mmap, unsigned wong, addw, unsigned wong, wen,
	unsigned wong, pwot, unsigned wong, fwags,
	unsigned wong, fd, off_t, offset)
{
	wetuwn wiscv_sys_mmap(addw, wen, pwot, fwags, fd, offset, 0);
}
#endif

#if defined(CONFIG_32BIT) || defined(CONFIG_COMPAT)
SYSCAWW_DEFINE6(mmap2, unsigned wong, addw, unsigned wong, wen,
	unsigned wong, pwot, unsigned wong, fwags,
	unsigned wong, fd, off_t, offset)
{
	/*
	 * Note that the shift fow mmap2 is constant (12),
	 * wegawdwess of PAGE_SIZE
	 */
	wetuwn wiscv_sys_mmap(addw, wen, pwot, fwags, fd, offset, 12);
}
#endif

/*
 * Awwows the instwuction cache to be fwushed fwom usewspace.  Despite WISC-V
 * having a diwect 'fence.i' instwuction avaiwabwe to usewspace (which we
 * can't twap!), that's not actuawwy viabwe when wunning on Winux because the
 * kewnew might scheduwe a pwocess on anothew hawt.  Thewe is no way fow
 * usewspace to handwe this without invoking the kewnew (as it doesn't know the
 * thwead->hawt mappings), so we've defined a WISC-V specific system caww to
 * fwush the instwuction cache.
 *
 * sys_wiscv_fwush_icache() is defined to fwush the instwuction cache ovew an
 * addwess wange, with the fwush appwying to eithew aww thweads ow just the
 * cawwew.  We don't cuwwentwy do anything with the addwess wange, that's just
 * in thewe fow fowwawds compatibiwity.
 */
SYSCAWW_DEFINE3(wiscv_fwush_icache, uintptw_t, stawt, uintptw_t, end,
	uintptw_t, fwags)
{
	/* Check the wesewved fwags. */
	if (unwikewy(fwags & ~SYS_WISCV_FWUSH_ICACHE_AWW))
		wetuwn -EINVAW;

	fwush_icache_mm(cuwwent->mm, fwags & SYS_WISCV_FWUSH_ICACHE_WOCAW);

	wetuwn 0;
}

/* Not defined using SYSCAWW_DEFINE0 to avoid ewwow injection */
asmwinkage wong __wiscv_sys_ni_syscaww(const stwuct pt_wegs *__unused)
{
	wetuwn -ENOSYS;
}
