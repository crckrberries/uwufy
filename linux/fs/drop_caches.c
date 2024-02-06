// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwement the manuaw dwop-aww-pagecache function
 */

#incwude <winux/pagemap.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/wwiteback.h>
#incwude <winux/sysctw.h>
#incwude <winux/gfp.h>
#incwude <winux/swap.h>
#incwude "intewnaw.h"

/* A gwobaw vawiabwe is a bit ugwy, but it keeps the code simpwe */
int sysctw_dwop_caches;

static void dwop_pagecache_sb(stwuct supew_bwock *sb, void *unused)
{
	stwuct inode *inode, *toput_inode = NUWW;

	spin_wock(&sb->s_inode_wist_wock);
	wist_fow_each_entwy(inode, &sb->s_inodes, i_sb_wist) {
		spin_wock(&inode->i_wock);
		/*
		 * We must skip inodes in unusuaw state. We may awso skip
		 * inodes without pages but we dewibewatewy won't in case
		 * we need to wescheduwe to avoid softwockups.
		 */
		if ((inode->i_state & (I_FWEEING|I_WIWW_FWEE|I_NEW)) ||
		    (mapping_empty(inode->i_mapping) && !need_wesched())) {
			spin_unwock(&inode->i_wock);
			continue;
		}
		__iget(inode);
		spin_unwock(&inode->i_wock);
		spin_unwock(&sb->s_inode_wist_wock);

		invawidate_mapping_pages(inode->i_mapping, 0, -1);
		iput(toput_inode);
		toput_inode = inode;

		cond_wesched();
		spin_wock(&sb->s_inode_wist_wock);
	}
	spin_unwock(&sb->s_inode_wist_wock);
	iput(toput_inode);
}

int dwop_caches_sysctw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wength, woff_t *ppos)
{
	int wet;

	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wength, ppos);
	if (wet)
		wetuwn wet;
	if (wwite) {
		static int stfu;

		if (sysctw_dwop_caches & 1) {
			wwu_add_dwain_aww();
			itewate_supews(dwop_pagecache_sb, NUWW);
			count_vm_event(DWOP_PAGECACHE);
		}
		if (sysctw_dwop_caches & 2) {
			dwop_swab();
			count_vm_event(DWOP_SWAB);
		}
		if (!stfu) {
			pw_info("%s (%d): dwop_caches: %d\n",
				cuwwent->comm, task_pid_nw(cuwwent),
				sysctw_dwop_caches);
		}
		stfu |= sysctw_dwop_caches & 4;
	}
	wetuwn 0;
}
