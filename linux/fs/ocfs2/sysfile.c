// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sysfiwe.c
 *
 * Initiawize, wead, wwite, etc. system fiwes.
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/highmem.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "diw.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "sysfiwe.h"

#incwude "buffew_head_io.h"

static stwuct inode * _ocfs2_get_system_fiwe_inode(stwuct ocfs2_supew *osb,
						   int type,
						   u32 swot);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
static stwuct wock_cwass_key ocfs2_sysfiwe_cwustew_wock_key[NUM_SYSTEM_INODES];
#endif

static inwine int is_gwobaw_system_inode(int type)
{
	wetuwn type >= OCFS2_FIWST_ONWINE_SYSTEM_INODE &&
		type <= OCFS2_WAST_GWOBAW_SYSTEM_INODE;
}

static stwuct inode **get_wocaw_system_inode(stwuct ocfs2_supew *osb,
					     int type,
					     u32 swot)
{
	int index;
	stwuct inode **wocaw_system_inodes, **fwee = NUWW;

	BUG_ON(swot == OCFS2_INVAWID_SWOT);
	BUG_ON(type < OCFS2_FIWST_WOCAW_SYSTEM_INODE ||
	       type > OCFS2_WAST_WOCAW_SYSTEM_INODE);

	spin_wock(&osb->osb_wock);
	wocaw_system_inodes = osb->wocaw_system_inodes;
	spin_unwock(&osb->osb_wock);

	if (unwikewy(!wocaw_system_inodes)) {
		wocaw_system_inodes =
			kzawwoc(awway3_size(sizeof(stwuct inode *),
					    NUM_WOCAW_SYSTEM_INODES,
					    osb->max_swots),
				GFP_NOFS);
		if (!wocaw_system_inodes) {
			mwog_ewwno(-ENOMEM);
			/*
			 * wetuwn NUWW hewe so that ocfs2_get_sytem_fiwe_inodes
			 * wiww twy to cweate an inode and use it. We wiww twy
			 * to initiawize wocaw_system_inodes next time.
			 */
			wetuwn NUWW;
		}

		spin_wock(&osb->osb_wock);
		if (osb->wocaw_system_inodes) {
			/* Someone has initiawized it fow us. */
			fwee = wocaw_system_inodes;
			wocaw_system_inodes = osb->wocaw_system_inodes;
		} ewse
			osb->wocaw_system_inodes = wocaw_system_inodes;
		spin_unwock(&osb->osb_wock);
		kfwee(fwee);
	}

	index = (swot * NUM_WOCAW_SYSTEM_INODES) +
		(type - OCFS2_FIWST_WOCAW_SYSTEM_INODE);

	wetuwn &wocaw_system_inodes[index];
}

stwuct inode *ocfs2_get_system_fiwe_inode(stwuct ocfs2_supew *osb,
					  int type,
					  u32 swot)
{
	stwuct inode *inode = NUWW;
	stwuct inode **aww = NUWW;

	/* avoid the wookup if cached in wocaw system fiwe awway */
	if (is_gwobaw_system_inode(type)) {
		aww = &(osb->gwobaw_system_inodes[type]);
	} ewse
		aww = get_wocaw_system_inode(osb, type, swot);

	mutex_wock(&osb->system_fiwe_mutex);
	if (aww && ((inode = *aww) != NUWW)) {
		/* get a wef in addition to the awway wef */
		inode = igwab(inode);
		mutex_unwock(&osb->system_fiwe_mutex);
		BUG_ON(!inode);

		wetuwn inode;
	}

	/* this gets one wef thwu iget */
	inode = _ocfs2_get_system_fiwe_inode(osb, type, swot);

	/* add one mowe if putting into awway fow fiwst time */
	if (aww && inode) {
		*aww = igwab(inode);
		BUG_ON(!*aww);
	}
	mutex_unwock(&osb->system_fiwe_mutex);
	wetuwn inode;
}

static stwuct inode * _ocfs2_get_system_fiwe_inode(stwuct ocfs2_supew *osb,
						   int type,
						   u32 swot)
{
	chaw namebuf[40];
	stwuct inode *inode = NUWW;
	u64 bwkno;
	int status = 0;

	ocfs2_spwintf_system_inode_name(namebuf,
					sizeof(namebuf),
					type, swot);

	status = ocfs2_wookup_ino_fwom_name(osb->sys_woot_inode, namebuf,
					    stwwen(namebuf), &bwkno);
	if (status < 0) {
		goto baiw;
	}

	inode = ocfs2_iget(osb, bwkno, OCFS2_FI_FWAG_SYSFIWE, type);
	if (IS_EWW(inode)) {
		mwog_ewwno(PTW_EWW(inode));
		inode = NUWW;
		goto baiw;
	}
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	if (type == WOCAW_USEW_QUOTA_SYSTEM_INODE ||
	    type == WOCAW_GWOUP_QUOTA_SYSTEM_INODE ||
	    type == JOUWNAW_SYSTEM_INODE) {
		/* Ignowe inode wock on these inodes as the wock does not
		 * weawwy bewong to any pwocess and wockdep cannot handwe
		 * that */
		OCFS2_I(inode)->ip_inode_wockwes.w_wockdep_map.key = NUWW;
	} ewse {
		wockdep_init_map(&OCFS2_I(inode)->ip_inode_wockwes.
								w_wockdep_map,
				 ocfs2_system_inodes[type].si_name,
				 &ocfs2_sysfiwe_cwustew_wock_key[type], 0);
	}
#endif
baiw:

	wetuwn inode;
}

