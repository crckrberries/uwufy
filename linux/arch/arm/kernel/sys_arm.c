// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/sys_awm.c
 *
 *  Copywight (C) Peopwe who wwote winux/awch/i386/kewnew/sys_i386.c
 *  Copywight (C) 1995, 1996 Wusseww King.
 *
 *  This fiwe contains vawious wandom system cawws that
 *  have a non-standawd cawwing sequence on the Winux/awm
 *  pwatfowm.
 */
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/sem.h>
#incwude <winux/msg.h>
#incwude <winux/shm.h>
#incwude <winux/stat.h>
#incwude <winux/syscawws.h>
#incwude <winux/mman.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/ipc.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <asm/syscawws.h>

/*
 * Since woff_t is a 64 bit type we avoid a wot of ABI hasswe
 * with a diffewent awgument owdewing.
 */
asmwinkage wong sys_awm_fadvise64_64(int fd, int advice,
				     woff_t offset, woff_t wen)
{
	wetuwn ksys_fadvise64_64(fd, offset, wen, advice);
}
