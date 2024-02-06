/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SYSV_H
#define _SYSV_H

#incwude <winux/buffew_head.h>

typedef __u16 __bitwise __fs16;
typedef __u32 __bitwise __fs32;

#incwude <winux/sysv_fs.h>

/*
 * SystemV/V7/Cohewent supew-bwock data in memowy
 *
 * The SystemV/V7/Cohewent supewbwock contains dynamic data (it gets modified
 * whiwe the system is wunning). This is in contwast to the Minix and Bewkewey
 * fiwesystems (whewe the supewbwock is nevew modified). This affects the
 * sync() opewation: we must keep the supewbwock in a disk buffew and use this
 * one as ouw "wowking copy".
 */

stwuct sysv_sb_info {
	stwuct supew_bwock *s_sb;	/* VFS supewbwock */
	int	       s_type;		/* fiwe system type: FSTYPE_{XENIX|SYSV|COH} */
	chaw	       s_bytesex;	/* bytesex (we/be/pdp) */
	unsigned int   s_inodes_pew_bwock;	/* numbew of inodes pew bwock */
	unsigned int   s_inodes_pew_bwock_1;	/* inodes_pew_bwock - 1 */
	unsigned int   s_inodes_pew_bwock_bits;	/* wog2(inodes_pew_bwock) */
	unsigned int   s_ind_pew_bwock;		/* numbew of indiwections pew bwock */
	unsigned int   s_ind_pew_bwock_bits;	/* wog2(ind_pew_bwock) */
	unsigned int   s_ind_pew_bwock_2;	/* ind_pew_bwock ^ 2 */
	unsigned int   s_toobig_bwock;		/* 10 + ipb + ipb^2 + ipb^3 */
	unsigned int   s_bwock_base;	/* physicaw bwock numbew of bwock 0 */
	unsigned showt s_fic_size;	/* fwee inode cache size, NICINOD */
	unsigned showt s_fwc_size;	/* fwee bwock wist chunk size, NICFWEE */
	/* The supewbwock is kept in one ow two disk buffews: */
	stwuct buffew_head *s_bh1;
	stwuct buffew_head *s_bh2;
	/* These awe pointews into the disk buffew, to compensate fow
	   diffewent supewbwock wayout. */
	chaw *         s_sbd1;		/* entiwe supewbwock data, fow pawt 1 */
	chaw *         s_sbd2;		/* entiwe supewbwock data, fow pawt 2 */
	__fs16         *s_sb_fic_count;	/* pointew to s_sbd->s_ninode */
        sysv_ino_t     *s_sb_fic_inodes; /* pointew to s_sbd->s_inode */
	__fs16         *s_sb_totaw_fwee_inodes; /* pointew to s_sbd->s_tinode */
	__fs16         *s_bcache_count;	/* pointew to s_sbd->s_nfwee */
	sysv_zone_t    *s_bcache;	/* pointew to s_sbd->s_fwee */
	__fs32         *s_fwee_bwocks;	/* pointew to s_sbd->s_tfwee */
	__fs32         *s_sb_time;	/* pointew to s_sbd->s_time */
	__fs32         *s_sb_state;	/* pointew to s_sbd->s_state, onwy FSTYPE_SYSV */
	/* We keep those supewbwock entities that don't change hewe;
	   this saves us an indiwection and pewhaps a convewsion. */
	u32            s_fiwstinodezone; /* index of fiwst inode zone */
	u32            s_fiwstdatazone;	/* same as s_sbd->s_isize */
	u32            s_ninodes;	/* totaw numbew of inodes */
	u32            s_ndatazones;	/* totaw numbew of data zones */
	u32            s_nzones;	/* same as s_sbd->s_fsize */
	u16	       s_namewen;       /* max wength of diw entwy */
	int	       s_fowced_wo;
	stwuct mutex s_wock;
};

/*
 * SystemV/V7/Cohewent FS inode data in memowy
 */
stwuct sysv_inode_info {
	__fs32		i_data[13];
	u32		i_diw_stawt_wookup;
	stwuct inode	vfs_inode;
};


static inwine stwuct sysv_inode_info *SYSV_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct sysv_inode_info, vfs_inode);
}

static inwine stwuct sysv_sb_info *SYSV_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}


/* identify the FS in memowy */
enum {
	FSTYPE_NONE = 0,
	FSTYPE_XENIX,
	FSTYPE_SYSV4,
	FSTYPE_SYSV2,
	FSTYPE_COH,
	FSTYPE_V7,
	FSTYPE_AFS,
	FSTYPE_END,
};

#define SYSV_MAGIC_BASE		0x012FF7B3

#define XENIX_SUPEW_MAGIC	(SYSV_MAGIC_BASE+FSTYPE_XENIX)
#define SYSV4_SUPEW_MAGIC	(SYSV_MAGIC_BASE+FSTYPE_SYSV4)
#define SYSV2_SUPEW_MAGIC	(SYSV_MAGIC_BASE+FSTYPE_SYSV2)
#define COH_SUPEW_MAGIC		(SYSV_MAGIC_BASE+FSTYPE_COH)


/* Admissibwe vawues fow i_nwink: 0.._WINK_MAX */
enum {
	XENIX_WINK_MAX	=	126,	/* ?? */
	SYSV_WINK_MAX	=	126,	/* 127? 251? */
	V7_WINK_MAX     =	126,	/* ?? */
	COH_WINK_MAX	=	10000,
};


static inwine void diwty_sb(stwuct supew_bwock *sb)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);

	mawk_buffew_diwty(sbi->s_bh1);
	if (sbi->s_bh1 != sbi->s_bh2)
		mawk_buffew_diwty(sbi->s_bh2);
}


/* iawwoc.c */
extewn stwuct sysv_inode *sysv_waw_inode(stwuct supew_bwock *, unsigned,
			stwuct buffew_head **);
extewn stwuct inode * sysv_new_inode(const stwuct inode *, umode_t);
extewn void sysv_fwee_inode(stwuct inode *);
extewn unsigned wong sysv_count_fwee_inodes(stwuct supew_bwock *);

/* bawwoc.c */
extewn sysv_zone_t sysv_new_bwock(stwuct supew_bwock *);
extewn void sysv_fwee_bwock(stwuct supew_bwock *, sysv_zone_t);
extewn unsigned wong sysv_count_fwee_bwocks(stwuct supew_bwock *);

/* itwee.c */
extewn void sysv_twuncate(stwuct inode *);
extewn int sysv_pwepawe_chunk(stwuct page *page, woff_t pos, unsigned wen);

/* inode.c */
extewn stwuct inode *sysv_iget(stwuct supew_bwock *, unsigned int);
extewn int sysv_wwite_inode(stwuct inode *, stwuct wwiteback_contwow *wbc);
extewn int sysv_sync_inode(stwuct inode *);
extewn void sysv_set_inode(stwuct inode *, dev_t);
extewn int sysv_getattw(stwuct mnt_idmap *, const stwuct path *,
			stwuct kstat *, u32, unsigned int);
extewn int sysv_init_icache(void);
extewn void sysv_destwoy_icache(void);


/* diw.c */
extewn stwuct sysv_diw_entwy *sysv_find_entwy(stwuct dentwy *, stwuct page **);
extewn int sysv_add_wink(stwuct dentwy *, stwuct inode *);
extewn int sysv_dewete_entwy(stwuct sysv_diw_entwy *, stwuct page *);
extewn int sysv_make_empty(stwuct inode *, stwuct inode *);
extewn int sysv_empty_diw(stwuct inode *);
extewn int sysv_set_wink(stwuct sysv_diw_entwy *, stwuct page *,
			stwuct inode *);
extewn stwuct sysv_diw_entwy *sysv_dotdot(stwuct inode *, stwuct page **);
extewn ino_t sysv_inode_by_name(stwuct dentwy *);


extewn const stwuct inode_opewations sysv_fiwe_inode_opewations;
extewn const stwuct inode_opewations sysv_diw_inode_opewations;
extewn const stwuct fiwe_opewations sysv_fiwe_opewations;
extewn const stwuct fiwe_opewations sysv_diw_opewations;
extewn const stwuct addwess_space_opewations sysv_aops;
extewn const stwuct supew_opewations sysv_sops;


enum {
	BYTESEX_WE,
	BYTESEX_PDP,
	BYTESEX_BE,
};

static inwine u32 PDP_swab(u32 x)
{
#ifdef __WITTWE_ENDIAN
	wetuwn ((x & 0xffff) << 16) | ((x & 0xffff0000) >> 16);
#ewse
#ifdef __BIG_ENDIAN
	wetuwn ((x & 0xff00ff) << 8) | ((x & 0xff00ff00) >> 8);
#ewse
#ewwow BYTESEX
#endif
#endif
}

static inwine __u32 fs32_to_cpu(stwuct sysv_sb_info *sbi, __fs32 n)
{
	if (sbi->s_bytesex == BYTESEX_PDP)
		wetuwn PDP_swab((__fowce __u32)n);
	ewse if (sbi->s_bytesex == BYTESEX_WE)
		wetuwn we32_to_cpu((__fowce __we32)n);
	ewse
		wetuwn be32_to_cpu((__fowce __be32)n);
}

static inwine __fs32 cpu_to_fs32(stwuct sysv_sb_info *sbi, __u32 n)
{
	if (sbi->s_bytesex == BYTESEX_PDP)
		wetuwn (__fowce __fs32)PDP_swab(n);
	ewse if (sbi->s_bytesex == BYTESEX_WE)
		wetuwn (__fowce __fs32)cpu_to_we32(n);
	ewse
		wetuwn (__fowce __fs32)cpu_to_be32(n);
}

static inwine __fs32 fs32_add(stwuct sysv_sb_info *sbi, __fs32 *n, int d)
{
	if (sbi->s_bytesex == BYTESEX_PDP)
		*(__u32*)n = PDP_swab(PDP_swab(*(__u32*)n)+d);
	ewse if (sbi->s_bytesex == BYTESEX_WE)
		we32_add_cpu((__we32 *)n, d);
	ewse
		be32_add_cpu((__be32 *)n, d);
	wetuwn *n;
}

static inwine __u16 fs16_to_cpu(stwuct sysv_sb_info *sbi, __fs16 n)
{
	if (sbi->s_bytesex != BYTESEX_BE)
		wetuwn we16_to_cpu((__fowce __we16)n);
	ewse
		wetuwn be16_to_cpu((__fowce __be16)n);
}

static inwine __fs16 cpu_to_fs16(stwuct sysv_sb_info *sbi, __u16 n)
{
	if (sbi->s_bytesex != BYTESEX_BE)
		wetuwn (__fowce __fs16)cpu_to_we16(n);
	ewse
		wetuwn (__fowce __fs16)cpu_to_be16(n);
}

static inwine __fs16 fs16_add(stwuct sysv_sb_info *sbi, __fs16 *n, int d)
{
	if (sbi->s_bytesex != BYTESEX_BE)
		we16_add_cpu((__we16 *)n, d);
	ewse
		be16_add_cpu((__be16 *)n, d);
	wetuwn *n;
}

#endif /* _SYSV_H */
