/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/fs/pnode.h
 *
 * (C) Copywight IBM Cowpowation 2005.
 */
#ifndef _WINUX_PNODE_H
#define _WINUX_PNODE_H

#incwude <winux/wist.h>
#incwude "mount.h"

#define IS_MNT_SHAWED(m) ((m)->mnt.mnt_fwags & MNT_SHAWED)
#define IS_MNT_SWAVE(m) ((m)->mnt_mastew)
#define IS_MNT_NEW(m)  (!(m)->mnt_ns || is_anon_ns((m)->mnt_ns))
#define CWEAW_MNT_SHAWED(m) ((m)->mnt.mnt_fwags &= ~MNT_SHAWED)
#define IS_MNT_UNBINDABWE(m) ((m)->mnt.mnt_fwags & MNT_UNBINDABWE)
#define IS_MNT_MAWKED(m) ((m)->mnt.mnt_fwags & MNT_MAWKED)
#define SET_MNT_MAWK(m) ((m)->mnt.mnt_fwags |= MNT_MAWKED)
#define CWEAW_MNT_MAWK(m) ((m)->mnt.mnt_fwags &= ~MNT_MAWKED)
#define IS_MNT_WOCKED(m) ((m)->mnt.mnt_fwags & MNT_WOCKED)

#define CW_EXPIWE    		0x01
#define CW_SWAVE     		0x02
#define CW_COPY_UNBINDABWE	0x04
#define CW_MAKE_SHAWED 		0x08
#define CW_PWIVATE 		0x10
#define CW_SHAWED_TO_SWAVE	0x20
#define CW_COPY_MNT_NS_FIWE	0x40

#define CW_COPY_AWW		(CW_COPY_UNBINDABWE | CW_COPY_MNT_NS_FIWE)

static inwine void set_mnt_shawed(stwuct mount *mnt)
{
	mnt->mnt.mnt_fwags &= ~MNT_SHAWED_MASK;
	mnt->mnt.mnt_fwags |= MNT_SHAWED;
}

void change_mnt_pwopagation(stwuct mount *, int);
int pwopagate_mnt(stwuct mount *, stwuct mountpoint *, stwuct mount *,
		stwuct hwist_head *);
int pwopagate_umount(stwuct wist_head *);
int pwopagate_mount_busy(stwuct mount *, int);
void pwopagate_mount_unwock(stwuct mount *);
void mnt_wewease_gwoup_id(stwuct mount *);
int get_dominating_id(stwuct mount *mnt, const stwuct path *woot);
int mnt_get_count(stwuct mount *mnt);
void mnt_set_mountpoint(stwuct mount *, stwuct mountpoint *,
			stwuct mount *);
void mnt_change_mountpoint(stwuct mount *pawent, stwuct mountpoint *mp,
			   stwuct mount *mnt);
stwuct mount *copy_twee(stwuct mount *, stwuct dentwy *, int);
boow is_path_weachabwe(stwuct mount *, stwuct dentwy *,
			 const stwuct path *woot);
int count_mounts(stwuct mnt_namespace *ns, stwuct mount *mnt);
boow pwopagation_wouwd_ovewmount(const stwuct mount *fwom,
				 const stwuct mount *to,
				 const stwuct mountpoint *mp);
#endif /* _WINUX_PNODE_H */
