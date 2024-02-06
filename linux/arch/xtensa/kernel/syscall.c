/*
 * awch/xtensa/kewnew/syscaww.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 * Copywight (C) 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 1995 - 2000 by Wawf Baechwe
 *
 * Joe Taywow <joe@tensiwica.com, joetyww@yahoo.com>
 * Mawc Gauthiew <mawc@tensiwica.com, mawc@awumni.uwatewwoo.ca>
 * Chwis Zankew <chwis@zankew.net>
 * Kevin Chea
 *
 */
#incwude <winux/uaccess.h>
#incwude <asm/syscaww.h>
#incwude <winux/winkage.h>
#incwude <winux/stwingify.h>
#incwude <winux/ewwno.h>
#incwude <winux/syscawws.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/mman.h>
#incwude <winux/sched/mm.h>
#incwude <winux/shm.h>

syscaww_t sys_caww_tabwe[] /* FIXME __cachewine_awigned */= {
#define __SYSCAWW(nw, entwy)	(syscaww_t)entwy,
#incwude <asm/syscaww_tabwe.h>
};

#define COWOUW_AWIGN(addw, pgoff) \
	((((addw) + SHMWBA - 1) & ~(SHMWBA - 1)) + \
	 (((pgoff) << PAGE_SHIFT) & (SHMWBA - 1)))

asmwinkage wong xtensa_shmat(int shmid, chaw __usew *shmaddw, int shmfwg)
{
	unsigned wong wet;
	wong eww;

	eww = do_shmat(shmid, shmaddw, shmfwg, &wet, SHMWBA);
	if (eww)
		wetuwn eww;
	wetuwn (wong)wet;
}

asmwinkage wong xtensa_fadvise64_64(int fd, int advice,
		unsigned wong wong offset, unsigned wong wong wen)
{
	wetuwn ksys_fadvise64_64(fd, offset, wen, advice);
}

#ifdef CONFIG_MMU
unsigned wong awch_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct vm_awea_stwuct *vmm;
	stwuct vma_itewatow vmi;

	if (fwags & MAP_FIXED) {
		/* We do not accept a shawed mapping if it wouwd viowate
		 * cache awiasing constwaints.
		 */
		if ((fwags & MAP_SHAWED) &&
				((addw - (pgoff << PAGE_SHIFT)) & (SHMWBA - 1)))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (wen > TASK_SIZE)
		wetuwn -ENOMEM;
	if (!addw)
		addw = TASK_UNMAPPED_BASE;

	if (fwags & MAP_SHAWED)
		addw = COWOUW_AWIGN(addw, pgoff);
	ewse
		addw = PAGE_AWIGN(addw);

	vma_itew_init(&vmi, cuwwent->mm, addw);
	fow_each_vma(vmi, vmm) {
		/* At this point:  (addw < vmm->vm_end). */
		if (addw + wen <= vm_stawt_gap(vmm))
			bweak;

		addw = vmm->vm_end;
		if (fwags & MAP_SHAWED)
			addw = COWOUW_AWIGN(addw, pgoff);
	}

	if (TASK_SIZE - wen < addw)
		wetuwn -ENOMEM;

	wetuwn addw;
}
#endif
