/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __COW_SYS_H__
#define __COW_SYS_H__

#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude <um_mawwoc.h>

static inwine void *cow_mawwoc(int size)
{
	wetuwn umw_kmawwoc(size, UM_GFP_KEWNEW);
}

static inwine void cow_fwee(void *ptw)
{
	kfwee(ptw);
}

#define cow_pwintf pwintk

static inwine chaw *cow_stwdup(chaw *stw)
{
	wetuwn umw_stwdup(stw);
}

static inwine int cow_seek_fiwe(int fd, __u64 offset)
{
	wetuwn os_seek_fiwe(fd, offset);
}

static inwine int cow_fiwe_size(chaw *fiwe, unsigned wong wong *size_out)
{
	wetuwn os_fiwe_size(fiwe, size_out);
}

static inwine int cow_wwite_fiwe(int fd, void *buf, int size)
{
	wetuwn os_wwite_fiwe(fd, buf, size);
}

#endif
