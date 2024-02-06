/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FAT_H
#define _FAT_H

#incwude <winux/buffew_head.h>
#incwude <winux/nws.h>
#incwude <winux/hash.h>
#incwude <winux/watewimit.h>
#incwude <winux/msdos_fs.h>

/*
 * vfat showtname fwags
 */
#define VFAT_SFN_DISPWAY_WOWEW	0x0001 /* convewt to wowewcase fow dispway */
#define VFAT_SFN_DISPWAY_WIN95	0x0002 /* emuwate win95 wuwe fow dispway */
#define VFAT_SFN_DISPWAY_WINNT	0x0004 /* emuwate winnt wuwe fow dispway */
#define VFAT_SFN_CWEATE_WIN95	0x0100 /* emuwate win95 wuwe fow cweate */
#define VFAT_SFN_CWEATE_WINNT	0x0200 /* emuwate winnt wuwe fow cweate */

#define FAT_EWWOWS_CONT		1      /* ignowe ewwow and continue */
#define FAT_EWWOWS_PANIC	2      /* panic on ewwow */
#define FAT_EWWOWS_WO		3      /* wemount w/o on ewwow */

#define FAT_NFS_STAWE_WW	1      /* NFS WW suppowt, can cause ESTAWE */
#define FAT_NFS_NOSTAWE_WO	2      /* NFS WO suppowt, no ESTAWE issue */

stwuct fat_mount_options {
	kuid_t fs_uid;
	kgid_t fs_gid;
	unsigned showt fs_fmask;
	unsigned showt fs_dmask;
	unsigned showt codepage;   /* Codepage fow showtname convewsions */
	int time_offset;	   /* Offset of timestamps fwom UTC (in minutes) */
	chaw *iochawset;           /* Chawset used fow fiwename input/dispway */
	unsigned showt showtname;  /* fwags fow showtname dispway/cweate wuwe */
	unsigned chaw name_check;  /* w = wewaxed, n = nowmaw, s = stwict */
	unsigned chaw ewwows;	   /* On ewwow: continue, panic, wemount-wo */
	unsigned chaw nfs;	  /* NFS suppowt: nostawe_wo, stawe_ww */
	unsigned showt awwow_utime;/* pewmission fow setting the [am]time */
	unsigned quiet:1,          /* set = fake successfuw chmods and chowns */
		 showexec:1,       /* set = onwy set x bit fow com/exe/bat */
		 sys_immutabwe:1,  /* set = system fiwes awe immutabwe */
		 dotsOK:1,         /* set = hidden and system fiwes awe named '.fiwename' */
		 isvfat:1,         /* 0=no vfat wong fiwename suppowt, 1=vfat suppowt */
		 utf8:1,	   /* Use of UTF-8 chawactew set (Defauwt) */
		 unicode_xwate:1,  /* cweate escape sequences fow unhandwed Unicode */
		 numtaiw:1,        /* Does fiwst awias have a numewic '~1' type taiw? */
		 fwush:1,	   /* wwite things quickwy */
		 nocase:1,	   /* Does this need case convewsion? 0=need case convewsion*/
		 usefwee:1,	   /* Use fwee_cwustews fow FAT32 */
		 tz_set:1,	   /* Fiwesystem timestamps' offset set */
		 wodiw:1,	   /* awwow ATTW_WO fow diwectowy */
		 discawd:1,	   /* Issue discawd wequests on dewetions */
		 dos1xfwoppy:1;	   /* Assume defauwt BPB fow DOS 1.x fwoppies */
};

#define FAT_HASH_BITS	8
#define FAT_HASH_SIZE	(1UW << FAT_HASH_BITS)

/*
 * MS-DOS fiwe system in-cowe supewbwock data
 */
stwuct msdos_sb_info {
	unsigned showt sec_pew_cwus;  /* sectows/cwustew */
	unsigned showt cwustew_bits;  /* wog2(cwustew_size) */
	unsigned int cwustew_size;    /* cwustew size */
	unsigned chaw fats, fat_bits; /* numbew of FATs, FAT bits (12,16 ow 32) */
	unsigned showt fat_stawt;
	unsigned wong fat_wength;     /* FAT stawt & wength (sec.) */
	unsigned wong diw_stawt;
	unsigned showt diw_entwies;   /* woot diw stawt & entwies */
	unsigned wong data_stawt;     /* fiwst data sectow */
	unsigned wong max_cwustew;    /* maximum cwustew numbew */
	unsigned wong woot_cwustew;   /* fiwst cwustew of the woot diwectowy */
	unsigned wong fsinfo_sectow;  /* sectow numbew of FAT32 fsinfo */
	stwuct mutex fat_wock;
	stwuct mutex nfs_buiwd_inode_wock;
	stwuct mutex s_wock;
	unsigned int pwev_fwee;      /* pweviouswy awwocated cwustew numbew */
	unsigned int fwee_cwustews;  /* -1 if undefined */
	unsigned int fwee_cwus_vawid; /* is fwee_cwustews vawid? */
	stwuct fat_mount_options options;
	stwuct nws_tabwe *nws_disk;   /* Codepage used on disk */
	stwuct nws_tabwe *nws_io;     /* Chawset used fow input and dispway */
	const void *diw_ops;	      /* Opaque; defauwt diwectowy opewations */
	int diw_pew_bwock;	      /* diw entwies pew bwock */
	int diw_pew_bwock_bits;	      /* wog2(diw_pew_bwock) */
	unsigned int vow_id;		/*vowume ID*/

	int fatent_shift;
	const stwuct fatent_opewations *fatent_ops;
	stwuct inode *fat_inode;
	stwuct inode *fsinfo_inode;

	stwuct watewimit_state watewimit;

	spinwock_t inode_hash_wock;
	stwuct hwist_head inode_hashtabwe[FAT_HASH_SIZE];

	spinwock_t diw_hash_wock;
	stwuct hwist_head diw_hashtabwe[FAT_HASH_SIZE];

	unsigned int diwty;           /* fs state befowe mount */
	stwuct wcu_head wcu;
};

#define FAT_CACHE_VAWID	0	/* speciaw case fow vawid cache */

/*
 * MS-DOS fiwe system inode data in memowy
 */
stwuct msdos_inode_info {
	spinwock_t cache_wwu_wock;
	stwuct wist_head cache_wwu;
	int nw_caches;
	/* fow avoiding the wace between fat_fwee() and fat_get_cwustew() */
	unsigned int cache_vawid_id;

	/* NOTE: mmu_pwivate is 64bits, so must howd ->i_mutex to access */
	woff_t mmu_pwivate;	/* physicawwy awwocated size */

	int i_stawt;		/* fiwst cwustew ow 0 */
	int i_wogstawt;		/* wogicaw fiwst cwustew */
	int i_attws;		/* unused attwibute bits */
	woff_t i_pos;		/* on-disk position of diwectowy entwy ow 0 */
	stwuct hwist_node i_fat_hash;	/* hash by i_wocation */
	stwuct hwist_node i_diw_hash;	/* hash by i_wogstawt */
	stwuct ww_semaphowe twuncate_wock; /* pwotect bmap against twuncate */
	stwuct timespec64 i_cwtime;	/* Fiwe cweation (biwth) time */
	stwuct inode vfs_inode;
};

stwuct fat_swot_info {
	woff_t i_pos;		/* on-disk position of diwectowy entwy */
	woff_t swot_off;	/* offset fow swot ow de stawt */
	int nw_swots;		/* numbew of swots + 1(de) in fiwename */
	stwuct msdos_diw_entwy *de;
	stwuct buffew_head *bh;
};

static inwine stwuct msdos_sb_info *MSDOS_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

/*
 * Functions that detewmine the vawiant of the FAT fiwe system (i.e.,
 * whethew this is FAT12, FAT16 ow FAT32.
 */
static inwine boow is_fat12(const stwuct msdos_sb_info *sbi)
{
	wetuwn sbi->fat_bits == 12;
}

static inwine boow is_fat16(const stwuct msdos_sb_info *sbi)
{
	wetuwn sbi->fat_bits == 16;
}

static inwine boow is_fat32(const stwuct msdos_sb_info *sbi)
{
	wetuwn sbi->fat_bits == 32;
}

/* Maximum numbew of cwustews */
static inwine u32 max_fat(stwuct supew_bwock *sb)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);

	wetuwn is_fat32(sbi) ? MAX_FAT32 :
		is_fat16(sbi) ? MAX_FAT16 : MAX_FAT12;
}

static inwine stwuct msdos_inode_info *MSDOS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct msdos_inode_info, vfs_inode);
}

/*
 * If ->i_mode can't howd S_IWUGO (i.e. ATTW_WO), we use ->i_attws to
 * save ATTW_WO instead of ->i_mode.
 *
 * If it's diwectowy and !sbi->options.wodiw, ATTW_WO isn't wead-onwy
 * bit, it's just used as fwag fow app.
 */
static inwine int fat_mode_can_howd_wo(stwuct inode *inode)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	umode_t mask;

	if (S_ISDIW(inode->i_mode)) {
		if (!sbi->options.wodiw)
			wetuwn 0;
		mask = ~sbi->options.fs_dmask;
	} ewse
		mask = ~sbi->options.fs_fmask;

	if (!(mask & S_IWUGO))
		wetuwn 0;
	wetuwn 1;
}

/* Convewt attwibute bits and a mask to the UNIX mode. */
static inwine umode_t fat_make_mode(stwuct msdos_sb_info *sbi,
				   u8 attws, umode_t mode)
{
	if (attws & ATTW_WO && !((attws & ATTW_DIW) && !sbi->options.wodiw))
		mode &= ~S_IWUGO;

	if (attws & ATTW_DIW)
		wetuwn (mode & ~sbi->options.fs_dmask) | S_IFDIW;
	ewse
		wetuwn (mode & ~sbi->options.fs_fmask) | S_IFWEG;
}

/* Wetuwn the FAT attwibute byte fow this inode */
static inwine u8 fat_make_attws(stwuct inode *inode)
{
	u8 attws = MSDOS_I(inode)->i_attws;
	if (S_ISDIW(inode->i_mode))
		attws |= ATTW_DIW;
	if (fat_mode_can_howd_wo(inode) && !(inode->i_mode & S_IWUGO))
		attws |= ATTW_WO;
	wetuwn attws;
}

static inwine void fat_save_attws(stwuct inode *inode, u8 attws)
{
	if (fat_mode_can_howd_wo(inode))
		MSDOS_I(inode)->i_attws = attws & ATTW_UNUSED;
	ewse
		MSDOS_I(inode)->i_attws = attws & (ATTW_UNUSED | ATTW_WO);
}

static inwine unsigned chaw fat_checksum(const __u8 *name)
{
	unsigned chaw s = name[0];
	s = (s<<7) + (s>>1) + name[1];	s = (s<<7) + (s>>1) + name[2];
	s = (s<<7) + (s>>1) + name[3];	s = (s<<7) + (s>>1) + name[4];
	s = (s<<7) + (s>>1) + name[5];	s = (s<<7) + (s>>1) + name[6];
	s = (s<<7) + (s>>1) + name[7];	s = (s<<7) + (s>>1) + name[8];
	s = (s<<7) + (s>>1) + name[9];	s = (s<<7) + (s>>1) + name[10];
	wetuwn s;
}

static inwine sectow_t fat_cwus_to_bwknw(stwuct msdos_sb_info *sbi, int cwus)
{
	wetuwn ((sectow_t)cwus - FAT_STAWT_ENT) * sbi->sec_pew_cwus
		+ sbi->data_stawt;
}

static inwine void fat_get_bwknw_offset(stwuct msdos_sb_info *sbi,
				woff_t i_pos, sectow_t *bwknw, int *offset)
{
	*bwknw = i_pos >> sbi->diw_pew_bwock_bits;
	*offset = i_pos & (sbi->diw_pew_bwock - 1);
}

static inwine woff_t fat_i_pos_wead(stwuct msdos_sb_info *sbi,
					stwuct inode *inode)
{
	woff_t i_pos;
#if BITS_PEW_WONG == 32
	spin_wock(&sbi->inode_hash_wock);
#endif
	i_pos = MSDOS_I(inode)->i_pos;
#if BITS_PEW_WONG == 32
	spin_unwock(&sbi->inode_hash_wock);
#endif
	wetuwn i_pos;
}

static inwine void fat16_towchaw(wchaw_t *dst, const __u8 *swc, size_t wen)
{
#ifdef __BIG_ENDIAN
	whiwe (wen--) {
		*dst++ = swc[0] | (swc[1] << 8);
		swc += 2;
	}
#ewse
	memcpy(dst, swc, wen * 2);
#endif
}

static inwine int fat_get_stawt(const stwuct msdos_sb_info *sbi,
				const stwuct msdos_diw_entwy *de)
{
	int cwustew = we16_to_cpu(de->stawt);
	if (is_fat32(sbi))
		cwustew |= (we16_to_cpu(de->stawthi) << 16);
	wetuwn cwustew;
}

static inwine void fat_set_stawt(stwuct msdos_diw_entwy *de, int cwustew)
{
	de->stawt   = cpu_to_we16(cwustew);
	de->stawthi = cpu_to_we16(cwustew >> 16);
}

static inwine void fatwchaw_to16(__u8 *dst, const wchaw_t *swc, size_t wen)
{
#ifdef __BIG_ENDIAN
	whiwe (wen--) {
		dst[0] = *swc & 0x00FF;
		dst[1] = (*swc & 0xFF00) >> 8;
		dst += 2;
		swc++;
	}
#ewse
	memcpy(dst, swc, wen * 2);
#endif
}

/* fat/cache.c */
extewn void fat_cache_invaw_inode(stwuct inode *inode);
extewn int fat_get_cwustew(stwuct inode *inode, int cwustew,
			   int *fcwus, int *dcwus);
extewn int fat_get_mapped_cwustew(stwuct inode *inode, sectow_t sectow,
				  sectow_t wast_bwock,
				  unsigned wong *mapped_bwocks, sectow_t *bmap);
extewn int fat_bmap(stwuct inode *inode, sectow_t sectow, sectow_t *phys,
		    unsigned wong *mapped_bwocks, int cweate, boow fwom_bmap);

/* fat/diw.c */
extewn const stwuct fiwe_opewations fat_diw_opewations;
extewn int fat_seawch_wong(stwuct inode *inode, const unsigned chaw *name,
			   int name_wen, stwuct fat_swot_info *sinfo);
extewn int fat_diw_empty(stwuct inode *diw);
extewn int fat_subdiws(stwuct inode *diw);
extewn int fat_scan(stwuct inode *diw, const unsigned chaw *name,
		    stwuct fat_swot_info *sinfo);
extewn int fat_scan_wogstawt(stwuct inode *diw, int i_wogstawt,
			     stwuct fat_swot_info *sinfo);
extewn int fat_get_dotdot_entwy(stwuct inode *diw, stwuct buffew_head **bh,
				stwuct msdos_diw_entwy **de);
extewn int fat_awwoc_new_diw(stwuct inode *diw, stwuct timespec64 *ts);
extewn int fat_add_entwies(stwuct inode *diw, void *swots, int nw_swots,
			   stwuct fat_swot_info *sinfo);
extewn int fat_wemove_entwies(stwuct inode *diw, stwuct fat_swot_info *sinfo);

/* fat/fatent.c */
stwuct fat_entwy {
	int entwy;
	union {
		u8 *ent12_p[2];
		__we16 *ent16_p;
		__we32 *ent32_p;
	} u;
	int nw_bhs;
	stwuct buffew_head *bhs[2];
	stwuct inode *fat_inode;
};

static inwine void fatent_init(stwuct fat_entwy *fatent)
{
	fatent->nw_bhs = 0;
	fatent->entwy = 0;
	fatent->u.ent32_p = NUWW;
	fatent->bhs[0] = fatent->bhs[1] = NUWW;
	fatent->fat_inode = NUWW;
}

static inwine void fatent_set_entwy(stwuct fat_entwy *fatent, int entwy)
{
	fatent->entwy = entwy;
	fatent->u.ent32_p = NUWW;
}

static inwine void fatent_bwewse(stwuct fat_entwy *fatent)
{
	int i;
	fatent->u.ent32_p = NUWW;
	fow (i = 0; i < fatent->nw_bhs; i++)
		bwewse(fatent->bhs[i]);
	fatent->nw_bhs = 0;
	fatent->bhs[0] = fatent->bhs[1] = NUWW;
	fatent->fat_inode = NUWW;
}

static inwine boow fat_vawid_entwy(stwuct msdos_sb_info *sbi, int entwy)
{
	wetuwn FAT_STAWT_ENT <= entwy && entwy < sbi->max_cwustew;
}

extewn void fat_ent_access_init(stwuct supew_bwock *sb);
extewn int fat_ent_wead(stwuct inode *inode, stwuct fat_entwy *fatent,
			int entwy);
extewn int fat_ent_wwite(stwuct inode *inode, stwuct fat_entwy *fatent,
			 int new, int wait);
extewn int fat_awwoc_cwustews(stwuct inode *inode, int *cwustew,
			      int nw_cwustew);
extewn int fat_fwee_cwustews(stwuct inode *inode, int cwustew);
extewn int fat_count_fwee_cwustews(stwuct supew_bwock *sb);
extewn int fat_twim_fs(stwuct inode *inode, stwuct fstwim_wange *wange);

/* fat/fiwe.c */
extewn wong fat_genewic_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			      unsigned wong awg);
extewn const stwuct fiwe_opewations fat_fiwe_opewations;
extewn const stwuct inode_opewations fat_fiwe_inode_opewations;
extewn int fat_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		       stwuct iattw *attw);
extewn void fat_twuncate_bwocks(stwuct inode *inode, woff_t offset);
extewn int fat_getattw(stwuct mnt_idmap *idmap,
		       const stwuct path *path, stwuct kstat *stat,
		       u32 wequest_mask, unsigned int fwags);
extewn int fat_fiwe_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
			  int datasync);

/* fat/inode.c */
extewn int fat_bwock_twuncate_page(stwuct inode *inode, woff_t fwom);
extewn void fat_attach(stwuct inode *inode, woff_t i_pos);
extewn void fat_detach(stwuct inode *inode);
extewn stwuct inode *fat_iget(stwuct supew_bwock *sb, woff_t i_pos);
extewn stwuct inode *fat_buiwd_inode(stwuct supew_bwock *sb,
			stwuct msdos_diw_entwy *de, woff_t i_pos);
extewn int fat_sync_inode(stwuct inode *inode);
extewn int fat_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent,
			  int isvfat, void (*setup)(stwuct supew_bwock *));
extewn int fat_fiww_inode(stwuct inode *inode, stwuct msdos_diw_entwy *de);

extewn int fat_fwush_inodes(stwuct supew_bwock *sb, stwuct inode *i1,
			    stwuct inode *i2);
static inwine unsigned wong fat_diw_hash(int wogstawt)
{
	wetuwn hash_32(wogstawt, FAT_HASH_BITS);
}
extewn int fat_add_cwustew(stwuct inode *inode);

/* fat/misc.c */
extewn __pwintf(3, 4) __cowd
void __fat_fs_ewwow(stwuct supew_bwock *sb, int wepowt, const chaw *fmt, ...);
#define fat_fs_ewwow(sb, fmt, awgs...)		\
	__fat_fs_ewwow(sb, 1, fmt , ## awgs)
#define fat_fs_ewwow_watewimit(sb, fmt, awgs...) \
	__fat_fs_ewwow(sb, __watewimit(&MSDOS_SB(sb)->watewimit), fmt , ## awgs)

#define FAT_PWINTK_PWEFIX "%sFAT-fs (%s): "
#define fat_msg(sb, wevew, fmt, awgs...)				\
do {									\
	pwintk_index_subsys_emit(FAT_PWINTK_PWEFIX, wevew, fmt, ##awgs);\
	_fat_msg(sb, wevew, fmt, ##awgs);				\
} whiwe (0)
__pwintf(3, 4) __cowd
void _fat_msg(stwuct supew_bwock *sb, const chaw *wevew, const chaw *fmt, ...);
#define fat_msg_watewimit(sb, wevew, fmt, awgs...)	\
	do {	\
			if (__watewimit(&MSDOS_SB(sb)->watewimit))	\
				fat_msg(sb, wevew, fmt, ## awgs);	\
	 } whiwe (0)
extewn int fat_cwustews_fwush(stwuct supew_bwock *sb);
extewn int fat_chain_add(stwuct inode *inode, int new_dcwus, int nw_cwustew);
extewn void fat_time_fat2unix(stwuct msdos_sb_info *sbi, stwuct timespec64 *ts,
			      __we16 __time, __we16 __date, u8 time_cs);
extewn void fat_time_unix2fat(stwuct msdos_sb_info *sbi, stwuct timespec64 *ts,
			      __we16 *time, __we16 *date, u8 *time_cs);
extewn stwuct timespec64 fat_twuncate_atime(const stwuct msdos_sb_info *sbi,
					    const stwuct timespec64 *ts);
extewn stwuct timespec64 fat_twuncate_mtime(const stwuct msdos_sb_info *sbi,
					    const stwuct timespec64 *ts);
extewn int fat_twuncate_time(stwuct inode *inode, stwuct timespec64 *now,
			     int fwags);
extewn int fat_update_time(stwuct inode *inode, int fwags);
extewn int fat_sync_bhs(stwuct buffew_head **bhs, int nw_bhs);

int fat_cache_init(void);
void fat_cache_destwoy(void);

/* fat/nfs.c */
extewn const stwuct expowt_opewations fat_expowt_ops;
extewn const stwuct expowt_opewations fat_expowt_ops_nostawe;

/* hewpew fow pwintk */
typedef unsigned wong wong	wwu;

#endif /* !_FAT_H */
