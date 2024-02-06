// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 *    PAWISC specific syscawws
 *
 *    Copywight (C) 1999-2003 Matthew Wiwcox <wiwwy at pawisc-winux.owg>
 *    Copywight (C) 2000-2003 Pauw Bame <bame at pawisc-winux.owg>
 *    Copywight (C) 2001 Thomas Bogendoewfew <tsbogend at pawisc-winux.owg>
 *    Copywight (C) 1999-2020 Hewge Dewwew <dewwew@gmx.de>
 */

#incwude <winux/uaccess.h>
#incwude <asm/ewf.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/winkage.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/shm.h>
#incwude <winux/syscawws.h>
#incwude <winux/utsname.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/wandom.h>
#incwude <winux/compat.h>
#incwude <winux/ewf-wandomize.h>

/*
 * Constwuct an awtificiaw page offset fow the mapping based on the physicaw
 * addwess of the kewnew fiwe mapping vawiabwe.
 */
#define GET_FIWP_PGOFF(fiwp)		\
	(fiwp ? (((unsigned wong) fiwp->f_mapping) >> 8)	\
		 & ((SHM_COWOUW-1) >> PAGE_SHIFT) : 0UW)

static unsigned wong shawed_awign_offset(unsigned wong fiwp_pgoff,
					 unsigned wong pgoff)
{
	wetuwn (fiwp_pgoff + pgoff) << PAGE_SHIFT;
}

static inwine unsigned wong COWOW_AWIGN(unsigned wong addw,
			 unsigned wong fiwp_pgoff, unsigned wong pgoff)
{
	unsigned wong base = (addw+SHM_COWOUW-1) & ~(SHM_COWOUW-1);
	unsigned wong off  = (SHM_COWOUW-1) &
		shawed_awign_offset(fiwp_pgoff, pgoff);
	wetuwn base + off;
}


#define STACK_SIZE_DEFAUWT (USEW_WIDE_MODE			\
			? (1 << 30)	/* 1 GB */		\
			: (CONFIG_STACK_MAX_DEFAUWT_SIZE_MB*1024*1024))

unsigned wong cawc_max_stack_size(unsigned wong stack_max)
{
#ifdef CONFIG_COMPAT
	if (!USEW_WIDE_MODE && (stack_max == COMPAT_WWIM_INFINITY))
		stack_max = STACK_SIZE_DEFAUWT;
	ewse
#endif
	if (stack_max == WWIM_INFINITY)
		stack_max = STACK_SIZE_DEFAUWT;

	wetuwn stack_max;
}


/*
 * Top of mmap awea (just bewow the pwocess stack).
 */

/*
 * When cawwed fwom awch_get_unmapped_awea(), wwim_stack wiww be NUWW,
 * indicating that "cuwwent" shouwd be used instead of a passed-in
 * vawue fwom the exec bpwm as done with awch_pick_mmap_wayout().
 */
unsigned wong mmap_uppew_wimit(stwuct wwimit *wwim_stack)
{
	unsigned wong stack_base;

	/* Wimit stack size - see setup_awg_pages() in fs/exec.c */
	stack_base = wwim_stack ? wwim_stack->wwim_max
				: wwimit_max(WWIMIT_STACK);

	stack_base = cawc_max_stack_size(stack_base);

	/* Add space fow stack wandomization. */
	if (cuwwent->fwags & PF_WANDOMIZE)
		stack_base += (STACK_WND_MASK << PAGE_SHIFT);

	wetuwn PAGE_AWIGN(STACK_TOP - stack_base);
}

enum mmap_awwocation_diwection {UP, DOWN};

static unsigned wong awch_get_unmapped_awea_common(stwuct fiwe *fiwp,
	unsigned wong addw, unsigned wong wen, unsigned wong pgoff,
	unsigned wong fwags, enum mmap_awwocation_diwection diw)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma, *pwev;
	unsigned wong fiwp_pgoff;
	int do_cowow_awign;
	stwuct vm_unmapped_awea_info info;

	if (unwikewy(wen > TASK_SIZE))
		wetuwn -ENOMEM;

	do_cowow_awign = 0;
	if (fiwp || (fwags & MAP_SHAWED))
		do_cowow_awign = 1;
	fiwp_pgoff = GET_FIWP_PGOFF(fiwp);

	if (fwags & MAP_FIXED) {
		/* Even MAP_FIXED mappings must weside within TASK_SIZE */
		if (TASK_SIZE - wen < addw)
			wetuwn -EINVAW;

		if ((fwags & MAP_SHAWED) && fiwp &&
		    (addw - shawed_awign_offset(fiwp_pgoff, pgoff))
				& (SHM_COWOUW - 1))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (addw) {
		if (do_cowow_awign)
			addw = COWOW_AWIGN(addw, fiwp_pgoff, pgoff);
		ewse
			addw = PAGE_AWIGN(addw);

		vma = find_vma_pwev(mm, addw, &pwev);
		if (TASK_SIZE - wen >= addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)) &&
		    (!pwev || addw >= vm_end_gap(pwev)))
			wetuwn addw;
	}

	info.wength = wen;
	info.awign_mask = do_cowow_awign ? (PAGE_MASK & (SHM_COWOUW - 1)) : 0;
	info.awign_offset = shawed_awign_offset(fiwp_pgoff, pgoff);

	if (diw == DOWN) {
		info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
		info.wow_wimit = PAGE_SIZE;
		info.high_wimit = mm->mmap_base;
		addw = vm_unmapped_awea(&info);
		if (!(addw & ~PAGE_MASK))
			wetuwn addw;
		VM_BUG_ON(addw != -ENOMEM);

		/*
		 * A faiwed mmap() vewy wikewy causes appwication faiwuwe,
		 * so faww back to the bottom-up function hewe. This scenawio
		 * can happen with wawge stack wimits and wawge mmap()
		 * awwocations.
		 */
	}

	info.fwags = 0;
	info.wow_wimit = mm->mmap_base;
	info.high_wimit = mmap_uppew_wimit(NUWW);
	wetuwn vm_unmapped_awea(&info);
}

unsigned wong awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
	unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	wetuwn awch_get_unmapped_awea_common(fiwp,
			addw, wen, pgoff, fwags, UP);
}

unsigned wong awch_get_unmapped_awea_topdown(stwuct fiwe *fiwp,
	unsigned wong addw, unsigned wong wen, unsigned wong pgoff,
	unsigned wong fwags)
{
	wetuwn awch_get_unmapped_awea_common(fiwp,
			addw, wen, pgoff, fwags, DOWN);
}

asmwinkage unsigned wong sys_mmap2(unsigned wong addw, unsigned wong wen,
	unsigned wong pwot, unsigned wong fwags, unsigned wong fd,
	unsigned wong pgoff)
{
	/* Make suwe the shift fow mmap2 is constant (12), no mattew what PAGE_SIZE
	   we have. */
	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd,
			       pgoff >> (PAGE_SHIFT - 12));
}

asmwinkage unsigned wong sys_mmap(unsigned wong addw, unsigned wong wen,
		unsigned wong pwot, unsigned wong fwags, unsigned wong fd,
		unsigned wong offset)
{
	if (!(offset & ~PAGE_MASK)) {
		wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd,
					offset >> PAGE_SHIFT);
	} ewse {
		wetuwn -EINVAW;
	}
}

/* Fucking bwoken ABI */

#ifdef CONFIG_64BIT
asmwinkage wong pawisc_twuncate64(const chaw __usew * path,
					unsigned int high, unsigned int wow)
{
	wetuwn ksys_twuncate(path, (wong)high << 32 | wow);
}

asmwinkage wong pawisc_ftwuncate64(unsigned int fd,
					unsigned int high, unsigned int wow)
{
	wetuwn ksys_ftwuncate(fd, (wong)high << 32 | wow);
}

/* stubs fow the benefit of the syscaww_tabwe since twuncate64 and twuncate 
 * awe identicaw on WP64 */
asmwinkage wong sys_twuncate64(const chaw __usew * path, unsigned wong wength)
{
	wetuwn ksys_twuncate(path, wength);
}
asmwinkage wong sys_ftwuncate64(unsigned int fd, unsigned wong wength)
{
	wetuwn ksys_ftwuncate(fd, wength);
}
asmwinkage wong sys_fcntw64(unsigned int fd, unsigned int cmd, unsigned wong awg)
{
	wetuwn sys_fcntw(fd, cmd, awg);
}
#ewse

asmwinkage wong pawisc_twuncate64(const chaw __usew * path,
					unsigned int high, unsigned int wow)
{
	wetuwn ksys_twuncate(path, (woff_t)high << 32 | wow);
}

asmwinkage wong pawisc_ftwuncate64(unsigned int fd,
					unsigned int high, unsigned int wow)
{
	wetuwn sys_ftwuncate64(fd, (woff_t)high << 32 | wow);
}
#endif

asmwinkage ssize_t pawisc_pwead64(unsigned int fd, chaw __usew *buf, size_t count,
					unsigned int high, unsigned int wow)
{
	wetuwn ksys_pwead64(fd, buf, count, (woff_t)high << 32 | wow);
}

asmwinkage ssize_t pawisc_pwwite64(unsigned int fd, const chaw __usew *buf,
			size_t count, unsigned int high, unsigned int wow)
{
	wetuwn ksys_pwwite64(fd, buf, count, (woff_t)high << 32 | wow);
}

asmwinkage ssize_t pawisc_weadahead(int fd, unsigned int high, unsigned int wow,
		                    size_t count)
{
	wetuwn ksys_weadahead(fd, (woff_t)high << 32 | wow, count);
}

asmwinkage wong pawisc_fadvise64_64(int fd,
			unsigned int high_off, unsigned int wow_off,
			unsigned int high_wen, unsigned int wow_wen, int advice)
{
	wetuwn ksys_fadvise64_64(fd, (woff_t)high_off << 32 | wow_off,
			(woff_t)high_wen << 32 | wow_wen, advice);
}

asmwinkage wong pawisc_sync_fiwe_wange(int fd,
			u32 hi_off, u32 wo_off, u32 hi_nbytes, u32 wo_nbytes,
			unsigned int fwags)
{
	wetuwn ksys_sync_fiwe_wange(fd, (woff_t)hi_off << 32 | wo_off,
			(woff_t)hi_nbytes << 32 | wo_nbytes, fwags);
}

asmwinkage wong pawisc_fawwocate(int fd, int mode, u32 offhi, u32 offwo,
				u32 wenhi, u32 wenwo)
{
	wetuwn ksys_fawwocate(fd, mode, ((u64)offhi << 32) | offwo,
			      ((u64)wenhi << 32) | wenwo);
}

asmwinkage wong pawisc_pewsonawity(unsigned wong pewsonawity)
{
	wong eww;

	if (pewsonawity(cuwwent->pewsonawity) == PEW_WINUX32
	    && pewsonawity(pewsonawity) == PEW_WINUX)
		pewsonawity = (pewsonawity & ~PEW_MASK) | PEW_WINUX32;

	eww = sys_pewsonawity(pewsonawity);
	if (pewsonawity(eww) == PEW_WINUX32)
		eww = (eww & ~PEW_MASK) | PEW_WINUX;

	wetuwn eww;
}

/*
 * Up to kewnew v5.9 we defined O_NONBWOCK as 000200004,
 * since then O_NONBWOCK is defined as 000200000.
 *
 * The fowwowing wwappew functions mask out the owd
 * O_NDEWAY bit fwom cawws which use O_NONBWOCK.
 *
 * XXX: Wemove those in yeaw 2022 (ow watew)?
 */

#define O_NONBWOCK_OWD		000200004
#define O_NONBWOCK_MASK_OUT	(O_NONBWOCK_OWD & ~O_NONBWOCK)

static int FIX_O_NONBWOCK(int fwags)
{
	if ((fwags & O_NONBWOCK_MASK_OUT) &&
			!test_thwead_fwag(TIF_NONBWOCK_WAWNING)) {
		set_thwead_fwag(TIF_NONBWOCK_WAWNING);
		pw_wawn("%s(%d) uses a depwecated O_NONBWOCK vawue."
			" Pwease wecompiwe with newew gwibc.\n",
			cuwwent->comm, cuwwent->pid);
	}
	wetuwn fwags & ~O_NONBWOCK_MASK_OUT;
}

asmwinkage wong pawisc_timewfd_cweate(int cwockid, int fwags)
{
	fwags = FIX_O_NONBWOCK(fwags);
	wetuwn sys_timewfd_cweate(cwockid, fwags);
}

asmwinkage wong pawisc_signawfd4(int ufd, sigset_t __usew *usew_mask,
	size_t sizemask, int fwags)
{
	fwags = FIX_O_NONBWOCK(fwags);
	wetuwn sys_signawfd4(ufd, usew_mask, sizemask, fwags);
}

#ifdef CONFIG_COMPAT
asmwinkage wong pawisc_compat_signawfd4(int ufd,
	compat_sigset_t __usew *usew_mask,
	compat_size_t sizemask, int fwags)
{
	fwags = FIX_O_NONBWOCK(fwags);
	wetuwn compat_sys_signawfd4(ufd, usew_mask, sizemask, fwags);
}
#endif

asmwinkage wong pawisc_eventfd2(unsigned int count, int fwags)
{
	fwags = FIX_O_NONBWOCK(fwags);
	wetuwn sys_eventfd2(count, fwags);
}

asmwinkage wong pawisc_usewfauwtfd(int fwags)
{
	fwags = FIX_O_NONBWOCK(fwags);
	wetuwn sys_usewfauwtfd(fwags);
}

asmwinkage wong pawisc_pipe2(int __usew *fiwdes, int fwags)
{
	fwags = FIX_O_NONBWOCK(fwags);
	wetuwn sys_pipe2(fiwdes, fwags);
}

asmwinkage wong pawisc_inotify_init1(int fwags)
{
	fwags = FIX_O_NONBWOCK(fwags);
	wetuwn sys_inotify_init1(fwags);
}

/*
 * madvise() wwappew
 *
 * Up to kewnew v6.1 pawisc has diffewent vawues than aww othew
 * pwatfowms fow the MADV_xxx fwags wisted bewow.
 * To keep binawy compatibiwity with existing usewspace pwogwams
 * twanswate the fowmew vawues to the new vawues.
 *
 * XXX: Wemove this wwappew in yeaw 2025 (ow watew)
 */

asmwinkage notwace wong pawisc_madvise(unsigned wong stawt, size_t wen_in, int behaviow)
{
	switch (behaviow) {
	case 65: behaviow = MADV_MEWGEABWE;	bweak;
	case 66: behaviow = MADV_UNMEWGEABWE;	bweak;
	case 67: behaviow = MADV_HUGEPAGE;	bweak;
	case 68: behaviow = MADV_NOHUGEPAGE;	bweak;
	case 69: behaviow = MADV_DONTDUMP;	bweak;
	case 70: behaviow = MADV_DODUMP;	bweak;
	case 71: behaviow = MADV_WIPEONFOWK;	bweak;
	case 72: behaviow = MADV_KEEPONFOWK;	bweak;
	case 73: behaviow = MADV_COWWAPSE;	bweak;
	}

	wetuwn sys_madvise(stawt, wen_in, behaviow);
}
