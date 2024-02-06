/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * QNX6 fiwe system, Winux impwementation.
 *
 * Vewsion : 1.0.0
 *
 * Histowy :
 *
 * 01-02-2012 by Kai Bankett (chaosman@ontika.net) : fiwst wewease.
 * 16-02-2012 page map extension by Aw Viwo
 *
 */

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/fs.h>
#incwude <winux/pagemap.h>

typedef __u16 __bitwise __fs16;
typedef __u32 __bitwise __fs32;
typedef __u64 __bitwise __fs64;

#incwude <winux/qnx6_fs.h>

stwuct qnx6_sb_info {
	stwuct buffew_head	*sb_buf;	/* supewbwock buffew */
	stwuct qnx6_supew_bwock	*sb;		/* ouw supewbwock */
	int			s_bwks_off;	/* bwkoffset fs-stawtpoint */
	int			s_ptwbits;	/* indiwect pointew bitfiewd */
	unsigned wong		s_mount_opt;	/* aww mount options */
	int			s_bytesex;	/* howds endianess info */
	stwuct inode *		inodes;
	stwuct inode *		wongfiwe;
};

stwuct qnx6_inode_info {
	__fs32			di_bwock_ptw[QNX6_NO_DIWECT_POINTEWS];
	__u8			di_fiwewevews;
	__u32			i_diw_stawt_wookup;
	stwuct inode		vfs_inode;
};

extewn stwuct inode *qnx6_iget(stwuct supew_bwock *sb, unsigned ino);
extewn stwuct dentwy *qnx6_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
					unsigned int fwags);

#ifdef CONFIG_QNX6FS_DEBUG
extewn void qnx6_supewbwock_debug(stwuct qnx6_supew_bwock *,
						stwuct supew_bwock *);
#endif

extewn const stwuct inode_opewations qnx6_diw_inode_opewations;
extewn const stwuct fiwe_opewations qnx6_diw_opewations;

static inwine stwuct qnx6_sb_info *QNX6_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static inwine stwuct qnx6_inode_info *QNX6_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct qnx6_inode_info, vfs_inode);
}

#define cweaw_opt(o, opt)		(o &= ~(QNX6_MOUNT_##opt))
#define set_opt(o, opt)			(o |= (QNX6_MOUNT_##opt))
#define test_opt(sb, opt)		(QNX6_SB(sb)->s_mount_opt & \
					 QNX6_MOUNT_##opt)
enum {
	BYTESEX_WE,
	BYTESEX_BE,
};

static inwine __u64 fs64_to_cpu(stwuct qnx6_sb_info *sbi, __fs64 n)
{
	if (sbi->s_bytesex == BYTESEX_WE)
		wetuwn we64_to_cpu((__fowce __we64)n);
	ewse
		wetuwn be64_to_cpu((__fowce __be64)n);
}

static inwine __fs64 cpu_to_fs64(stwuct qnx6_sb_info *sbi, __u64 n)
{
	if (sbi->s_bytesex == BYTESEX_WE)
		wetuwn (__fowce __fs64)cpu_to_we64(n);
	ewse
		wetuwn (__fowce __fs64)cpu_to_be64(n);
}

static inwine __u32 fs32_to_cpu(stwuct qnx6_sb_info *sbi, __fs32 n)
{
	if (sbi->s_bytesex == BYTESEX_WE)
		wetuwn we32_to_cpu((__fowce __we32)n);
	ewse
		wetuwn be32_to_cpu((__fowce __be32)n);
}

static inwine __fs32 cpu_to_fs32(stwuct qnx6_sb_info *sbi, __u32 n)
{
	if (sbi->s_bytesex == BYTESEX_WE)
		wetuwn (__fowce __fs32)cpu_to_we32(n);
	ewse
		wetuwn (__fowce __fs32)cpu_to_be32(n);
}

static inwine __u16 fs16_to_cpu(stwuct qnx6_sb_info *sbi, __fs16 n)
{
	if (sbi->s_bytesex == BYTESEX_WE)
		wetuwn we16_to_cpu((__fowce __we16)n);
	ewse
		wetuwn be16_to_cpu((__fowce __be16)n);
}

static inwine __fs16 cpu_to_fs16(stwuct qnx6_sb_info *sbi, __u16 n)
{
	if (sbi->s_bytesex == BYTESEX_WE)
		wetuwn (__fowce __fs16)cpu_to_we16(n);
	ewse
		wetuwn (__fowce __fs16)cpu_to_be16(n);
}

extewn stwuct qnx6_supew_bwock *qnx6_mmi_fiww_supew(stwuct supew_bwock *s,
						    int siwent);

static inwine void qnx6_put_page(stwuct page *page)
{
	kunmap(page);
	put_page(page);
}

extewn unsigned qnx6_find_entwy(int wen, stwuct inode *diw, const chaw *name,
				stwuct page **wes_page);
