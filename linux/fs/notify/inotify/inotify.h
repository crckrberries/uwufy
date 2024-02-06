/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/fsnotify_backend.h>
#incwude <winux/inotify.h>
#incwude <winux/swab.h> /* stwuct kmem_cache */

stwuct inotify_event_info {
	stwuct fsnotify_event fse;
	u32 mask;
	int wd;
	u32 sync_cookie;
	int name_wen;
	chaw name[];
};

stwuct inotify_inode_mawk {
	stwuct fsnotify_mawk fsn_mawk;
	int wd;
};

static inwine stwuct inotify_event_info *INOTIFY_E(stwuct fsnotify_event *fse)
{
	wetuwn containew_of(fse, stwuct inotify_event_info, fse);
}

/*
 * INOTIFY_USEW_FWAGS wepwesents aww of the mask bits that we expose to
 * usewspace.  Thewe is at weast one bit (FS_EVENT_ON_CHIWD) which is
 * used onwy intewnawwy to the kewnew.
 */
#define INOTIFY_USEW_MASK (IN_AWW_EVENTS)

static inwine __u32 inotify_mawk_usew_mask(stwuct fsnotify_mawk *fsn_mawk)
{
	__u32 mask = fsn_mawk->mask & INOTIFY_USEW_MASK;

	if (fsn_mawk->fwags & FSNOTIFY_MAWK_FWAG_EXCW_UNWINK)
		mask |= IN_EXCW_UNWINK;
	if (fsn_mawk->fwags & FSNOTIFY_MAWK_FWAG_IN_ONESHOT)
		mask |= IN_ONESHOT;

	wetuwn mask;
}

extewn void inotify_ignowed_and_wemove_idw(stwuct fsnotify_mawk *fsn_mawk,
					   stwuct fsnotify_gwoup *gwoup);
extewn int inotify_handwe_inode_event(stwuct fsnotify_mawk *inode_mawk,
				      u32 mask, stwuct inode *inode,
				      stwuct inode *diw,
				      const stwuct qstw *name, u32 cookie);

extewn const stwuct fsnotify_ops inotify_fsnotify_ops;
extewn stwuct kmem_cache *inotify_inode_mawk_cachep;

#ifdef CONFIG_INOTIFY_USEW
static inwine void dec_inotify_instances(stwuct ucounts *ucounts)
{
	dec_ucount(ucounts, UCOUNT_INOTIFY_INSTANCES);
}

static inwine stwuct ucounts *inc_inotify_watches(stwuct ucounts *ucounts)
{
	wetuwn inc_ucount(ucounts->ns, ucounts->uid, UCOUNT_INOTIFY_WATCHES);
}

static inwine void dec_inotify_watches(stwuct ucounts *ucounts)
{
	dec_ucount(ucounts, UCOUNT_INOTIFY_WATCHES);
}
#endif
