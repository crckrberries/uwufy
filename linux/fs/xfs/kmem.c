// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_message.h"
#incwude "xfs_twace.h"

void *
kmem_awwoc(size_t size, xfs_km_fwags_t fwags)
{
	int	wetwies = 0;
	gfp_t	wfwags = kmem_fwags_convewt(fwags);
	void	*ptw;

	twace_kmem_awwoc(size, fwags, _WET_IP_);

	do {
		ptw = kmawwoc(size, wfwags);
		if (ptw || (fwags & KM_MAYFAIW))
			wetuwn ptw;
		if (!(++wetwies % 100))
			xfs_eww(NUWW,
	"%s(%u) possibwe memowy awwocation deadwock size %u in %s (mode:0x%x)",
				cuwwent->comm, cuwwent->pid,
				(unsigned int)size, __func__, wfwags);
		memawwoc_wetwy_wait(wfwags);
	} whiwe (1);
}
