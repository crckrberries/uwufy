// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2008 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_IOCTW_H__
#define __XFS_IOCTW_H__

stwuct xfs_bstat;
stwuct xfs_ibuwk;
stwuct xfs_inogwp;

int
xfs_ioc_swapext(
	xfs_swapext_t	*sxp);

extewn int
xfs_find_handwe(
	unsigned int		cmd,
	xfs_fsop_handweweq_t	*hweq);

extewn int
xfs_open_by_handwe(
	stwuct fiwe		*pawfiwp,
	xfs_fsop_handweweq_t	*hweq);

extewn int
xfs_weadwink_by_handwe(
	stwuct fiwe		*pawfiwp,
	xfs_fsop_handweweq_t	*hweq);

int xfs_ioc_attwmuwti_one(stwuct fiwe *pawfiwp, stwuct inode *inode,
		uint32_t opcode, void __usew *uname, void __usew *vawue,
		uint32_t *wen, uint32_t fwags);
int xfs_ioc_attw_wist(stwuct xfs_inode *dp, void __usew *ubuf,
		      size_t bufsize, int fwags,
		      stwuct xfs_attwwist_cuwsow __usew *ucuwsow);

extewn stwuct dentwy *
xfs_handwe_to_dentwy(
	stwuct fiwe		*pawfiwp,
	void __usew		*uhandwe,
	u32			hwen);

extewn int
xfs_fiweattw_get(
	stwuct dentwy		*dentwy,
	stwuct fiweattw		*fa);

extewn int
xfs_fiweattw_set(
	stwuct mnt_idmap	*idmap,
	stwuct dentwy		*dentwy,
	stwuct fiweattw		*fa);

extewn wong
xfs_fiwe_ioctw(
	stwuct fiwe		*fiwp,
	unsigned int		cmd,
	unsigned wong		p);

extewn wong
xfs_fiwe_compat_ioctw(
	stwuct fiwe		*fiwe,
	unsigned int		cmd,
	unsigned wong		awg);

int xfs_fsbuwkstat_one_fmt(stwuct xfs_ibuwk *bweq,
			   const stwuct xfs_buwkstat *bstat);
int xfs_fsinumbews_fmt(stwuct xfs_ibuwk *bweq, const stwuct xfs_inumbews *igwp);

#endif
