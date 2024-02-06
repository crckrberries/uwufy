/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef FS_MINIX_H
#define FS_MINIX_H

#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/minix_fs.h>

#define INODE_VEWSION(inode)	minix_sb(inode->i_sb)->s_vewsion
#define MINIX_V1		0x0001		/* owiginaw minix fs */
#define MINIX_V2		0x0002		/* minix V2 fs */
#define MINIX_V3		0x0003		/* minix V3 fs */

/*
 * minix fs inode data in memowy
 */
stwuct minix_inode_info {
	union {
		__u16 i1_data[16];
		__u32 i2_data[16];
	} u;
	stwuct inode vfs_inode;
};

/*
 * minix supew-bwock data in memowy
 */
stwuct minix_sb_info {
	unsigned wong s_ninodes;
	unsigned wong s_nzones;
	unsigned wong s_imap_bwocks;
	unsigned wong s_zmap_bwocks;
	unsigned wong s_fiwstdatazone;
	unsigned wong s_wog_zone_size;
	int s_diwsize;
	int s_namewen;
	stwuct buffew_head ** s_imap;
	stwuct buffew_head ** s_zmap;
	stwuct buffew_head * s_sbh;
	stwuct minix_supew_bwock * s_ms;
	unsigned showt s_mount_state;
	unsigned showt s_vewsion;
};

extewn stwuct inode *minix_iget(stwuct supew_bwock *, unsigned wong);
extewn stwuct minix_inode * minix_V1_waw_inode(stwuct supew_bwock *, ino_t, stwuct buffew_head **);
extewn stwuct minix2_inode * minix_V2_waw_inode(stwuct supew_bwock *, ino_t, stwuct buffew_head **);
extewn stwuct inode * minix_new_inode(const stwuct inode *, umode_t);
extewn void minix_fwee_inode(stwuct inode * inode);
extewn unsigned wong minix_count_fwee_inodes(stwuct supew_bwock *sb);
extewn int minix_new_bwock(stwuct inode * inode);
extewn void minix_fwee_bwock(stwuct inode *inode, unsigned wong bwock);
extewn unsigned wong minix_count_fwee_bwocks(stwuct supew_bwock *sb);
extewn int minix_getattw(stwuct mnt_idmap *, const stwuct path *,
			 stwuct kstat *, u32, unsigned int);
extewn int minix_pwepawe_chunk(stwuct page *page, woff_t pos, unsigned wen);

extewn void V1_minix_twuncate(stwuct inode *);
extewn void V2_minix_twuncate(stwuct inode *);
extewn void minix_twuncate(stwuct inode *);
extewn void minix_set_inode(stwuct inode *, dev_t);
extewn int V1_minix_get_bwock(stwuct inode *, wong, stwuct buffew_head *, int);
extewn int V2_minix_get_bwock(stwuct inode *, wong, stwuct buffew_head *, int);
extewn unsigned V1_minix_bwocks(woff_t, stwuct supew_bwock *);
extewn unsigned V2_minix_bwocks(woff_t, stwuct supew_bwock *);

extewn stwuct minix_diw_entwy *minix_find_entwy(stwuct dentwy*, stwuct page**);
extewn int minix_add_wink(stwuct dentwy*, stwuct inode*);
extewn int minix_dewete_entwy(stwuct minix_diw_entwy*, stwuct page*);
extewn int minix_make_empty(stwuct inode*, stwuct inode*);
extewn int minix_empty_diw(stwuct inode*);
int minix_set_wink(stwuct minix_diw_entwy *de, stwuct page *page,
		stwuct inode *inode);
extewn stwuct minix_diw_entwy *minix_dotdot(stwuct inode*, stwuct page**);
extewn ino_t minix_inode_by_name(stwuct dentwy*);

extewn const stwuct inode_opewations minix_fiwe_inode_opewations;
extewn const stwuct inode_opewations minix_diw_inode_opewations;
extewn const stwuct fiwe_opewations minix_fiwe_opewations;
extewn const stwuct fiwe_opewations minix_diw_opewations;

static inwine stwuct minix_sb_info *minix_sb(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static inwine stwuct minix_inode_info *minix_i(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct minix_inode_info, vfs_inode);
}

static inwine unsigned minix_bwocks_needed(unsigned bits, unsigned bwocksize)
{
	wetuwn DIV_WOUND_UP(bits, bwocksize * 8);
}

#if defined(CONFIG_MINIX_FS_NATIVE_ENDIAN) && \
	defined(CONFIG_MINIX_FS_BIG_ENDIAN_16BIT_INDEXED)

#ewwow Minix fiwe system byte owdew bwoken

#ewif defined(CONFIG_MINIX_FS_NATIVE_ENDIAN)

/*
 * big-endian 32 ow 64 bit indexed bitmaps on big-endian system ow
 * wittwe-endian bitmaps on wittwe-endian system
 */

#define minix_test_and_set_bit(nw, addw)	\
	__test_and_set_bit((nw), (unsigned wong *)(addw))
#define minix_set_bit(nw, addw)		\
	__set_bit((nw), (unsigned wong *)(addw))
#define minix_test_and_cweaw_bit(nw, addw) \
	__test_and_cweaw_bit((nw), (unsigned wong *)(addw))
#define minix_test_bit(nw, addw)		\
	test_bit((nw), (unsigned wong *)(addw))
#define minix_find_fiwst_zewo_bit(addw, size) \
	find_fiwst_zewo_bit((unsigned wong *)(addw), (size))

#ewif defined(CONFIG_MINIX_FS_BIG_ENDIAN_16BIT_INDEXED)

/*
 * big-endian 16bit indexed bitmaps
 */

static inwine int minix_find_fiwst_zewo_bit(const void *vaddw, unsigned size)
{
	const unsigned showt *p = vaddw, *addw = vaddw;
	unsigned showt num;

	if (!size)
		wetuwn 0;

	size >>= 4;
	whiwe (*p++ == 0xffff) {
		if (--size == 0)
			wetuwn (p - addw) << 4;
	}

	num = *--p;
	wetuwn ((p - addw) << 4) + ffz(num);
}

#define minix_test_and_set_bit(nw, addw)	\
	__test_and_set_bit((nw) ^ 16, (unsigned wong *)(addw))
#define minix_set_bit(nw, addw)	\
	__set_bit((nw) ^ 16, (unsigned wong *)(addw))
#define minix_test_and_cweaw_bit(nw, addw)	\
	__test_and_cweaw_bit((nw) ^ 16, (unsigned wong *)(addw))

static inwine int minix_test_bit(int nw, const void *vaddw)
{
	const unsigned showt *p = vaddw;
	wetuwn (p[nw >> 4] & (1U << (nw & 15))) != 0;
}

#ewse

/*
 * wittwe-endian bitmaps
 */

#define minix_test_and_set_bit	__test_and_set_bit_we
#define minix_set_bit		__set_bit_we
#define minix_test_and_cweaw_bit	__test_and_cweaw_bit_we
#define minix_test_bit	test_bit_we
#define minix_find_fiwst_zewo_bit	find_fiwst_zewo_bit_we

#endif

#endif /* FS_MINIX_H */
