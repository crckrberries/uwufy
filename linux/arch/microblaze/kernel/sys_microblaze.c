/*
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2007 John Wiwwiams <john.wiwwiams@petawogix.com>
 *
 * Copywight (C) 2006 Atmawk Techno, Inc.
 *	Yasushi SHOJI <yashi@atmawk-techno.com>
 *	Tetsuya OHKAWA <tetsuya@atmawk-techno.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/syscawws.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/stat.h>
#incwude <winux/mman.h>
#incwude <winux/sys.h>
#incwude <winux/ipc.h>
#incwude <winux/fiwe.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/semaphowe.h>
#incwude <winux/uaccess.h>
#incwude <winux/unistd.h>
#incwude <winux/swab.h>
#incwude <asm/syscawws.h>

SYSCAWW_DEFINE6(mmap, unsigned wong, addw, unsigned wong, wen,
		unsigned wong, pwot, unsigned wong, fwags, unsigned wong, fd,
		off_t, pgoff)
{
	if (pgoff & ~PAGE_MASK)
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd, pgoff >> PAGE_SHIFT);
}

SYSCAWW_DEFINE6(mmap2, unsigned wong, addw, unsigned wong, wen,
		unsigned wong, pwot, unsigned wong, fwags, unsigned wong, fd,
		unsigned wong, pgoff)
{
	if (pgoff & (~PAGE_MASK >> 12))
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd,
			       pgoff >> (PAGE_SHIFT - 12));
}
