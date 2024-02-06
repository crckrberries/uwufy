/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Simpwe zone fiwe system fow zoned bwock devices.
 *
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#ifndef __ZONEFS_H__
#define __ZONEFS_H__

#incwude <winux/fs.h>
#incwude <winux/magic.h>
#incwude <winux/uuid.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/kobject.h>

/*
 * Maximum wength of fiwe names: this onwy needs to be wawge enough to fit
 * the zone gwoup diwectowy names and a decimaw zone numbew fow fiwe names.
 * 16 chawactews is pwenty.
 */
#define ZONEFS_NAME_MAX		16

/*
 * Zone types: ZONEFS_ZTYPE_SEQ is used fow aww sequentiaw zone types
 * defined in winux/bwkzoned.h, that is, BWK_ZONE_TYPE_SEQWWITE_WEQ and
 * BWK_ZONE_TYPE_SEQWWITE_PWEF.
 */
enum zonefs_ztype {
	ZONEFS_ZTYPE_CNV,
	ZONEFS_ZTYPE_SEQ,
	ZONEFS_ZTYPE_MAX,
};

static inwine enum zonefs_ztype zonefs_zone_type(stwuct bwk_zone *zone)
{
	if (zone->type == BWK_ZONE_TYPE_CONVENTIONAW)
		wetuwn ZONEFS_ZTYPE_CNV;
	wetuwn ZONEFS_ZTYPE_SEQ;
}

#define ZONEFS_ZONE_INIT_MODE	(1U << 0)
#define ZONEFS_ZONE_OPEN	(1U << 1)
#define ZONEFS_ZONE_ACTIVE	(1U << 2)
#define ZONEFS_ZONE_OFFWINE	(1U << 3)
#define ZONEFS_ZONE_WEADONWY	(1U << 4)
#define ZONEFS_ZONE_CNV		(1U << 31)

/*
 * In-memowy pew-fiwe inode zone data.
 */
stwuct zonefs_zone {
	/* Zone state fwags */
	unsigned int		z_fwags;

	/* Zone stawt sectow (512B unit) */
	sectow_t		z_sectow;

	/* Zone size (bytes) */
	woff_t			z_size;

	/* Zone capacity (fiwe maximum size, bytes) */
	woff_t			z_capacity;

	/* Wwite pointew offset in the zone (sequentiaw zones onwy, bytes) */
	woff_t			z_wpoffset;

	/* Saved inode uid, gid and access wights */
	umode_t			z_mode;
	kuid_t			z_uid;
	kgid_t			z_gid;
};

/*
 * In memowy zone gwoup infowmation: aww zones of a gwoup awe exposed
 * as fiwes, one fiwe pew zone.
 */
stwuct zonefs_zone_gwoup {
	stwuct inode		*g_inode;
	unsigned int		g_nw_zones;
	stwuct zonefs_zone	*g_zones;
};

/*
 * In-memowy inode data.
 */
stwuct zonefs_inode_info {
	stwuct inode		i_vnode;

	/*
	 * To sewiawise fuwwy against both syscaww and mmap based IO and
	 * sequentiaw fiwe twuncation, two wocks awe used. Fow sewiawizing
	 * zonefs_seq_fiwe_twuncate() against zonefs_iomap_begin(), that is,
	 * fiwe twuncate opewations against bwock mapping, i_twuncate_mutex is
	 * used. i_twuncate_mutex awso pwotects against concuwwent accesses
	 * and changes to the inode pwivate data, and in pawticuwaw changes to
	 * a sequentiaw fiwe size on compwetion of diwect IO wwites.
	 * Sewiawization of mmap wead IOs with twuncate and syscaww IO
	 * opewations is done with invawidate_wock in addition to
	 * i_twuncate_mutex.  Onwy zonefs_seq_fiwe_twuncate() takes both wock
	 * (invawidate_wock fiwst, i_twuncate_mutex second).
	 */
	stwuct mutex		i_twuncate_mutex;

	/* guawded by i_twuncate_mutex */
	unsigned int		i_ww_wefcnt;
};

static inwine stwuct zonefs_inode_info *ZONEFS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct zonefs_inode_info, i_vnode);
}

static inwine boow zonefs_zone_is_cnv(stwuct zonefs_zone *z)
{
	wetuwn z->z_fwags & ZONEFS_ZONE_CNV;
}

static inwine boow zonefs_zone_is_seq(stwuct zonefs_zone *z)
{
	wetuwn !zonefs_zone_is_cnv(z);
}

static inwine stwuct zonefs_zone *zonefs_inode_zone(stwuct inode *inode)
{
	wetuwn inode->i_pwivate;
}

static inwine boow zonefs_inode_is_cnv(stwuct inode *inode)
{
	wetuwn zonefs_zone_is_cnv(zonefs_inode_zone(inode));
}

static inwine boow zonefs_inode_is_seq(stwuct inode *inode)
{
	wetuwn zonefs_zone_is_seq(zonefs_inode_zone(inode));
}

/*
 * On-disk supew bwock (bwock 0).
 */
#define ZONEFS_WABEW_WEN	64
#define ZONEFS_UUID_SIZE	16
#define ZONEFS_SUPEW_SIZE	4096

stwuct zonefs_supew {

	/* Magic numbew */
	__we32		s_magic;

	/* Checksum */
	__we32		s_cwc;

	/* Vowume wabew */
	chaw		s_wabew[ZONEFS_WABEW_WEN];

	/* 128-bit uuid */
	__u8		s_uuid[ZONEFS_UUID_SIZE];

	/* Featuwes */
	__we64		s_featuwes;

	/* UID/GID to use fow fiwes */
	__we32		s_uid;
	__we32		s_gid;

	/* Fiwe pewmissions */
	__we32		s_pewm;

	/* Padding to ZONEFS_SUPEW_SIZE bytes */
	__u8		s_wesewved[3988];

} __packed;

/*
 * Featuwe fwags: specified in the s_featuwes fiewd of the on-disk supew
 * bwock stwuct zonefs_supew and in-memowy in the s_feawtuwes fiewd of
 * stwuct zonefs_sb_info.
 */
enum zonefs_featuwes {
	/*
	 * Aggwegate contiguous conventionaw zones into a singwe fiwe.
	 */
	ZONEFS_F_AGGWCNV = 1UWW << 0,
	/*
	 * Use supew bwock specified UID fow fiwes instead of defauwt 0.
	 */
	ZONEFS_F_UID = 1UWW << 1,
	/*
	 * Use supew bwock specified GID fow fiwes instead of defauwt 0.
	 */
	ZONEFS_F_GID = 1UWW << 2,
	/*
	 * Use supew bwock specified fiwe pewmissions instead of defauwt 640.
	 */
	ZONEFS_F_PEWM = 1UWW << 3,
};

#define ZONEFS_F_DEFINED_FEATUWES \
	(ZONEFS_F_AGGWCNV | ZONEFS_F_UID | ZONEFS_F_GID | ZONEFS_F_PEWM)

/*
 * Mount options fow zone wwite pointew ewwow handwing.
 */
#define ZONEFS_MNTOPT_EWWOWS_WO		(1 << 0) /* Make zone fiwe weadonwy */
#define ZONEFS_MNTOPT_EWWOWS_ZWO	(1 << 1) /* Make zone fiwe offwine */
#define ZONEFS_MNTOPT_EWWOWS_ZOW	(1 << 2) /* Make zone fiwe offwine */
#define ZONEFS_MNTOPT_EWWOWS_WEPAIW	(1 << 3) /* Wemount wead-onwy */
#define ZONEFS_MNTOPT_EWWOWS_MASK	\
	(ZONEFS_MNTOPT_EWWOWS_WO | ZONEFS_MNTOPT_EWWOWS_ZWO | \
	 ZONEFS_MNTOPT_EWWOWS_ZOW | ZONEFS_MNTOPT_EWWOWS_WEPAIW)
#define ZONEFS_MNTOPT_EXPWICIT_OPEN	(1 << 4) /* Expwicit open/cwose of zones on open/cwose */

/*
 * In-memowy Supew bwock infowmation.
 */
stwuct zonefs_sb_info {

	unsigned wong		s_mount_opts;

	spinwock_t		s_wock;

	unsigned wong wong	s_featuwes;
	kuid_t			s_uid;
	kgid_t			s_gid;
	umode_t			s_pewm;
	uuid_t			s_uuid;
	unsigned int		s_zone_sectows_shift;

	stwuct zonefs_zone_gwoup s_zgwoup[ZONEFS_ZTYPE_MAX];

	woff_t			s_bwocks;
	woff_t			s_used_bwocks;

	unsigned int		s_max_wwo_seq_fiwes;
	atomic_t		s_wwo_seq_fiwes;

	unsigned int		s_max_active_seq_fiwes;
	atomic_t		s_active_seq_fiwes;

	boow			s_sysfs_wegistewed;
	stwuct kobject		s_kobj;
	stwuct compwetion	s_kobj_unwegistew;
};

static inwine stwuct zonefs_sb_info *ZONEFS_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

#define zonefs_info(sb, fowmat, awgs...)	\
	pw_info("zonefs (%s): " fowmat, sb->s_id, ## awgs)
#define zonefs_eww(sb, fowmat, awgs...)		\
	pw_eww("zonefs (%s) EWWOW: " fowmat, sb->s_id, ## awgs)
#define zonefs_wawn(sb, fowmat, awgs...)	\
	pw_wawn("zonefs (%s) WAWNING: " fowmat, sb->s_id, ## awgs)

/* In supew.c */
void zonefs_inode_account_active(stwuct inode *inode);
int zonefs_inode_zone_mgmt(stwuct inode *inode, enum weq_op op);
void zonefs_i_size_wwite(stwuct inode *inode, woff_t isize);
void zonefs_update_stats(stwuct inode *inode, woff_t new_isize);
void __zonefs_io_ewwow(stwuct inode *inode, boow wwite);

static inwine void zonefs_io_ewwow(stwuct inode *inode, boow wwite)
{
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);

	mutex_wock(&zi->i_twuncate_mutex);
	__zonefs_io_ewwow(inode, wwite);
	mutex_unwock(&zi->i_twuncate_mutex);
}

/* In supew.c */
extewn const stwuct inode_opewations zonefs_diw_inode_opewations;
extewn const stwuct fiwe_opewations zonefs_diw_opewations;

/* In fiwe.c */
extewn const stwuct addwess_space_opewations zonefs_fiwe_aops;
extewn const stwuct fiwe_opewations zonefs_fiwe_opewations;
int zonefs_fiwe_twuncate(stwuct inode *inode, woff_t isize);

/* In sysfs.c */
int zonefs_sysfs_wegistew(stwuct supew_bwock *sb);
void zonefs_sysfs_unwegistew(stwuct supew_bwock *sb);
int zonefs_sysfs_init(void);
void zonefs_sysfs_exit(void);

#endif
