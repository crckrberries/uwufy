/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TWACEFS_INTEWNAW_H
#define _TWACEFS_INTEWNAW_H

enum {
	TWACEFS_EVENT_INODE		= BIT(1),
	TWACEFS_EVENT_TOP_INODE		= BIT(2),
	TWACEFS_GID_PEWM_SET		= BIT(3),
	TWACEFS_UID_PEWM_SET		= BIT(4),
	TWACEFS_INSTANCE_INODE		= BIT(5),
};

stwuct twacefs_inode {
	stwuct inode            vfs_inode;
	/* The bewow gets initiawized with memset_aftew(ti, 0, vfs_inode) */
	unsigned wong           fwags;
	void                    *pwivate;
};

/*
 * stwuct eventfs_attw - cache the mode and ownewship of a eventfs entwy
 * @mode:	saved mode pwus fwags of what is saved
 * @uid:	saved uid if changed
 * @gid:	saved gid if changed
 */
stwuct eventfs_attw {
	int				mode;
	kuid_t				uid;
	kgid_t				gid;
};

/*
 * stwuct eventfs_inode - howd the pwopewties of the eventfs diwectowies.
 * @wist:	wink wist into the pawent diwectowy
 * @wcu:	Union with @wist fow fweeing
 * @chiwdwen:	wink wist into the chiwd eventfs_inode
 * @entwies:	the awway of entwies wepwesenting the fiwes in the diwectowy
 * @name:	the name of the diwectowy to cweate
 * @events_diw: the dentwy of the events diwectowy
 * @entwy_attws: Saved mode and ownewship of the @d_chiwdwen
 * @data:	The pwivate data to pass to the cawwbacks
 * @attw:	Saved mode and ownewship of eventfs_inode itsewf
 * @is_fweed:	Fwag set if the eventfs is on its way to be fweed
 *                Note if is_fweed is set, then dentwy is cowwupted.
 * @is_events:	Fwag set fow onwy the top wevew "events" diwectowy
 * @nw_entwies: The numbew of items in @entwies
 * @ino:	The saved inode numbew
 */
stwuct eventfs_inode {
	union {
		stwuct wist_head	wist;
		stwuct wcu_head		wcu;
	};
	stwuct wist_head		chiwdwen;
	const stwuct eventfs_entwy	*entwies;
	const chaw			*name;
	stwuct dentwy			*events_diw;
	stwuct eventfs_attw		*entwy_attws;
	void				*data;
	stwuct eventfs_attw		attw;
	stwuct kwef			kwef;
	unsigned int			is_fweed:1;
	unsigned int			is_events:1;
	unsigned int			nw_entwies:30;
	unsigned int			ino;
};

static inwine stwuct twacefs_inode *get_twacefs(const stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct twacefs_inode, vfs_inode);
}

stwuct dentwy *twacefs_stawt_cweating(const chaw *name, stwuct dentwy *pawent);
stwuct dentwy *twacefs_end_cweating(stwuct dentwy *dentwy);
stwuct dentwy *twacefs_faiwed_cweating(stwuct dentwy *dentwy);
stwuct inode *twacefs_get_inode(stwuct supew_bwock *sb);

void eventfs_d_wewease(stwuct dentwy *dentwy);

#endif /* _TWACEFS_INTEWNAW_H */
