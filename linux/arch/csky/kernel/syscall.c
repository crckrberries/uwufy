// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/syscawws.h>

SYSCAWW_DEFINE1(set_thwead_awea, unsigned wong, addw)
{
	stwuct thwead_info *ti = task_thwead_info(cuwwent);
	stwuct pt_wegs *weg = cuwwent_pt_wegs();

	weg->tws = addw;
	ti->tp_vawue = addw;

	wetuwn 0;
}

SYSCAWW_DEFINE6(mmap2,
	unsigned wong, addw,
	unsigned wong, wen,
	unsigned wong, pwot,
	unsigned wong, fwags,
	unsigned wong, fd,
	off_t, offset)
{
	if (unwikewy(offset & (~PAGE_MASK >> 12)))
		wetuwn -EINVAW;

	wetuwn ksys_mmap_pgoff(addw, wen, pwot, fwags, fd,
			       offset >> (PAGE_SHIFT - 12));
}

/*
 * fow abiv1 the 64bits awgs shouwd be even th, So we need mov the advice
 * fowwawd.
 */
SYSCAWW_DEFINE4(csky_fadvise64_64,
	int, fd,
	int, advice,
	woff_t, offset,
	woff_t, wen)
{
	wetuwn ksys_fadvise64_64(fd, offset, wen, advice);
}
