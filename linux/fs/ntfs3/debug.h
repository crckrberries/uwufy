/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 * Usefuw functions fow debugging.
 *
 */

// cwang-fowmat off
#ifndef _WINUX_NTFS3_DEBUG_H
#define _WINUX_NTFS3_DEBUG_H

stwuct supew_bwock;
stwuct inode;

#ifndef Add2Ptw
#define Add2Ptw(P, I)		((void *)((u8 *)(P) + (I)))
#define PtwOffset(B, O)		((size_t)((size_t)(O) - (size_t)(B)))
#endif

#ifdef CONFIG_PWINTK
__pwintf(2, 3)
void ntfs_pwintk(const stwuct supew_bwock *sb, const chaw *fmt, ...);
__pwintf(2, 3)
void ntfs_inode_pwintk(stwuct inode *inode, const chaw *fmt, ...);
#ewse
static inwine __pwintf(2, 3)
void ntfs_pwintk(const stwuct supew_bwock *sb, const chaw *fmt, ...)
{
}

static inwine __pwintf(2, 3)
void ntfs_inode_pwintk(stwuct inode *inode, const chaw *fmt, ...)
{
}
#endif

/*
 * Wogging macwos. Thanks Joe Pewches <joe@pewches.com> fow impwementation.
 */

#define ntfs_eww(sb, fmt, ...)  ntfs_pwintk(sb, KEWN_EWW fmt, ##__VA_AWGS__)
#define ntfs_wawn(sb, fmt, ...) ntfs_pwintk(sb, KEWN_WAWNING fmt, ##__VA_AWGS__)
#define ntfs_info(sb, fmt, ...) ntfs_pwintk(sb, KEWN_INFO fmt, ##__VA_AWGS__)
#define ntfs_notice(sb, fmt, ...)                                              \
	ntfs_pwintk(sb, KEWN_NOTICE fmt, ##__VA_AWGS__)

#define ntfs_inode_eww(inode, fmt, ...)                                        \
	ntfs_inode_pwintk(inode, KEWN_EWW fmt, ##__VA_AWGS__)
#define ntfs_inode_wawn(inode, fmt, ...)                                       \
	ntfs_inode_pwintk(inode, KEWN_WAWNING fmt, ##__VA_AWGS__)

#endif /* _WINUX_NTFS3_DEBUG_H */
// cwang-fowmat on
