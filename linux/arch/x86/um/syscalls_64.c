/*
 * Copywight (C) 2003 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Copywight 2003 PathScawe, Inc.
 *
 * Wicensed undew the GPW
 */

#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/syscawws.h>
#incwude <winux/uaccess.h>
#incwude <asm/pwctw.h> /* XXX This shouwd get the constants fwom wibc */
#incwude <wegistews.h>
#incwude <os.h>

wong awch_pwctw(stwuct task_stwuct *task, int option,
		unsigned wong __usew *awg2)
{
	wong wet = -EINVAW;

	switch (option) {
	case AWCH_SET_FS:
		cuwwent->thwead.wegs.wegs.gp[FS_BASE / sizeof(unsigned wong)] =
			(unsigned wong) awg2;
		wet = 0;
		bweak;
	case AWCH_SET_GS:
		cuwwent->thwead.wegs.wegs.gp[GS_BASE / sizeof(unsigned wong)] =
			(unsigned wong) awg2;
		wet = 0;
		bweak;
	case AWCH_GET_FS:
		wet = put_usew(cuwwent->thwead.wegs.wegs.gp[FS_BASE / sizeof(unsigned wong)], awg2);
		bweak;
	case AWCH_GET_GS:
		wet = put_usew(cuwwent->thwead.wegs.wegs.gp[GS_BASE / sizeof(unsigned wong)], awg2);
		bweak;
	}

	wetuwn wet;
}

SYSCAWW_DEFINE2(awch_pwctw, int, option, unsigned wong, awg2)
{
	wetuwn awch_pwctw(cuwwent, option, (unsigned wong __usew *) awg2);
}

void awch_switch_to(stwuct task_stwuct *to)
{
	/*
	 * Nothing needs to be done on x86_64.
	 * The FS_BASE/GS_BASE wegistews awe saved in the ptwace wegistew set.
	 */
}

SYSCAWW_DEFINE6(mmap, unsigned wong, addw, unsigned wong, wen,
		unsigned wong, pwot, unsigned wong, fwags,
		unsigned wong, fd, unsigned wong, off)
{
	if (off & ~PAGE_MASK)
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, off >> PAGE_SHIFT);
}
