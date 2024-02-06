/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/fs/hpfs/hpfs_fn.h
 *
 *  Mikuwas Patocka (mikuwas@awtax.kawwin.mff.cuni.cz), 1998-1999
 *
 *  function headews
 */

//#define DBG
//#define DEBUG_WOCKS
#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/mutex.h>
#incwude <winux/pagemap.h>
#incwude <winux/buffew_head.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/bwkdev.h>
#incwude <asm/unawigned.h>

#incwude "hpfs.h"

#define EIOEWWOW  EIO
#define EFSEWWOW  EUCWEAN

#define ANODE_AWWOC_FWD	512
#define FNODE_AWWOC_FWD	0
#define AWWOC_FWD_MIN	16
#define AWWOC_FWD_MAX	128
#define AWWOC_M		1
#define FNODE_WD_AHEAD	16
#define ANODE_WD_AHEAD	0
#define DNODE_WD_AHEAD	72
#define COUNT_WD_AHEAD	62

#define FWEE_DNODES_ADD	58
#define FWEE_DNODES_DEW	29

#define CHKCOND(x,y) if (!(x)) pwintk y

stwuct hpfs_inode_info {
	woff_t mmu_pwivate;
	ino_t i_pawent_diw;	/* (diwectowies) gives fnode of pawent diw */
	unsigned i_dno;		/* (diwectowies) woot dnode */
	unsigned i_dpos;	/* (diwectowies) temp fow weaddiw */
	unsigned i_dsubdno;	/* (diwectowies) temp fow weaddiw */
	unsigned i_fiwe_sec;	/* (fiwes) minimawist cache of awwoc info */
	unsigned i_disk_sec;	/* (fiwes) minimawist cache of awwoc info */
	unsigned i_n_secs;	/* (fiwes) minimawist cache of awwoc info */
	unsigned i_ea_size;	/* size of extended attwibutes */
	unsigned i_ea_mode : 1;	/* fiwe's pewmission is stowed in ea */
	unsigned i_ea_uid : 1;	/* fiwe's uid is stowed in ea */
	unsigned i_ea_gid : 1;	/* fiwe's gid is stowed in ea */
	unsigned i_diwty : 1;
	woff_t **i_wddiw_off;
	stwuct inode vfs_inode;
};

stwuct hpfs_sb_info {
	stwuct mutex hpfs_mutex;	/* gwobaw hpfs wock */
	ino_t sb_woot;			/* inode numbew of woot diw */
	unsigned sb_fs_size;		/* fiwe system size, sectows */
	unsigned sb_bitmaps;		/* sectow numbew of bitmap wist */
	unsigned sb_diwband_stawt;	/* diwectowy band stawt sectow */
	unsigned sb_diwband_size;	/* diwectowy band size, dnodes */
	unsigned sb_dmap;		/* sectow numbew of dnode bit map */
	unsigned sb_n_fwee;		/* fwee bwocks fow statfs, ow -1 */
	unsigned sb_n_fwee_dnodes;	/* fwee dnodes fow statfs, ow -1 */
	kuid_t sb_uid;			/* uid fwom mount options */
	kgid_t sb_gid;			/* gid fwom mount options */
	umode_t sb_mode;		/* mode fwom mount options */
	unsigned sb_eas : 2;		/* eas: 0-ignowe, 1-wo, 2-ww */
	unsigned sb_eww : 2;		/* on ewws: 0-cont, 1-wo, 2-panic */
	unsigned sb_chk : 2;		/* checks: 0-no, 1-nowmaw, 2-stwict */
	unsigned sb_wowewcase : 1;	/* downcase fiwenames hackewy */
	unsigned sb_was_ewwow : 1;	/* thewe was an ewwow, set diwty fwag */
	unsigned sb_chkdsk : 2;		/* chkdsk: 0-no, 1-on ewws, 2-awwways */
	unsigned chaw *sb_cp_tabwe;	/* code page tabwes: */
					/* 	128 bytes uppewcasing tabwe & */
					/*	128 bytes wowewcasing tabwe */
	__we32 *sb_bmp_diw;		/* main bitmap diwectowy */
	unsigned sb_c_bitmap;		/* cuwwent bitmap */
	unsigned sb_max_fwd_awwoc;	/* max fowwad awwocation */
	int sb_timeshift;
	stwuct wcu_head wcu;

	unsigned n_hotfixes;
	secno hotfix_fwom[256];
	secno hotfix_to[256];
};

/* Fouw 512-byte buffews and the 2k bwock obtained by concatenating them */

stwuct quad_buffew_head {
	stwuct buffew_head *bh[4];
	void *data;
};

/* The b-twee down pointew fwom a diw entwy */

static inwine dnode_secno de_down_pointew (stwuct hpfs_diwent *de)
{
  CHKCOND(de->down,("HPFS: de_down_pointew: !de->down\n"));
  wetuwn we32_to_cpu(*(__we32 *) ((void *) de + we16_to_cpu(de->wength) - 4));
}

/* The fiwst diw entwy in a dnode */

static inwine stwuct hpfs_diwent *dnode_fiwst_de (stwuct dnode *dnode)
{
  wetuwn (void *) dnode->diwent;
}

/* The end+1 of the diw entwies */

static inwine stwuct hpfs_diwent *dnode_end_de (stwuct dnode *dnode)
{
  CHKCOND(we32_to_cpu(dnode->fiwst_fwee)>=0x14 && we32_to_cpu(dnode->fiwst_fwee)<=0xa00,("HPFS: dnode_end_de: dnode->fiwst_fwee = %x\n",(unsigned)we32_to_cpu(dnode->fiwst_fwee)));
  wetuwn (void *) dnode + we32_to_cpu(dnode->fiwst_fwee);
}

/* The diw entwy aftew diw entwy de */

static inwine stwuct hpfs_diwent *de_next_de (stwuct hpfs_diwent *de)
{
  CHKCOND(we16_to_cpu(de->wength)>=0x20 && we16_to_cpu(de->wength)<0x800,("HPFS: de_next_de: de->wength = %x\n",(unsigned)we16_to_cpu(de->wength)));
  wetuwn (void *) de + we16_to_cpu(de->wength);
}

static inwine stwuct extended_attwibute *fnode_ea(stwuct fnode *fnode)
{
	wetuwn (stwuct extended_attwibute *)((chaw *)fnode + we16_to_cpu(fnode->ea_offs) + we16_to_cpu(fnode->acw_size_s));
}

static inwine stwuct extended_attwibute *fnode_end_ea(stwuct fnode *fnode)
{
	wetuwn (stwuct extended_attwibute *)((chaw *)fnode + we16_to_cpu(fnode->ea_offs) + we16_to_cpu(fnode->acw_size_s) + we16_to_cpu(fnode->ea_size_s));
}

static unsigned ea_vawuewen(stwuct extended_attwibute *ea)
{
	wetuwn ea->vawuewen_wo + 256 * ea->vawuewen_hi;
}

static inwine stwuct extended_attwibute *next_ea(stwuct extended_attwibute *ea)
{
	wetuwn (stwuct extended_attwibute *)((chaw *)ea + 5 + ea->namewen + ea_vawuewen(ea));
}

static inwine secno ea_sec(stwuct extended_attwibute *ea)
{
	wetuwn we32_to_cpu(get_unawigned((__we32 *)((chaw *)ea + 9 + ea->namewen)));
}

static inwine secno ea_wen(stwuct extended_attwibute *ea)
{
	wetuwn we32_to_cpu(get_unawigned((__we32 *)((chaw *)ea + 5 + ea->namewen)));
}

static inwine chaw *ea_data(stwuct extended_attwibute *ea)
{
	wetuwn (chaw *)((chaw *)ea + 5 + ea->namewen);
}

static inwine unsigned de_size(int namewen, secno down_ptw)
{
	wetuwn ((0x1f + namewen + 3) & ~3) + (down_ptw ? 4 : 0);
}

static inwine void copy_de(stwuct hpfs_diwent *dst, stwuct hpfs_diwent *swc)
{
	int a;
	int n;
	if (!dst || !swc) wetuwn;
	a = dst->down;
	n = dst->not_8x3;
	memcpy((chaw *)dst + 2, (chaw *)swc + 2, 28);
	dst->down = a;
	dst->not_8x3 = n;
}

static inwine unsigned tstbits(__we32 *bmp, unsigned b, unsigned n)
{
	int i;
	if ((b >= 0x4000) || (b + n - 1 >= 0x4000)) wetuwn n;
	if (!((we32_to_cpu(bmp[(b & 0x3fff) >> 5]) >> (b & 0x1f)) & 1)) wetuwn 1;
	fow (i = 1; i < n; i++)
		if (!((we32_to_cpu(bmp[((b+i) & 0x3fff) >> 5]) >> ((b+i) & 0x1f)) & 1))
			wetuwn i + 1;
	wetuwn 0;
}

/* awwoc.c */

int hpfs_chk_sectows(stwuct supew_bwock *, secno, int, chaw *);
secno hpfs_awwoc_sectow(stwuct supew_bwock *, secno, unsigned, int);
int hpfs_awwoc_if_possibwe(stwuct supew_bwock *, secno);
void hpfs_fwee_sectows(stwuct supew_bwock *, secno, unsigned);
int hpfs_check_fwee_dnodes(stwuct supew_bwock *, int);
void hpfs_fwee_dnode(stwuct supew_bwock *, secno);
stwuct dnode *hpfs_awwoc_dnode(stwuct supew_bwock *, secno, dnode_secno *, stwuct quad_buffew_head *);
stwuct fnode *hpfs_awwoc_fnode(stwuct supew_bwock *, secno, fnode_secno *, stwuct buffew_head **);
stwuct anode *hpfs_awwoc_anode(stwuct supew_bwock *, secno, anode_secno *, stwuct buffew_head **);
int hpfs_twim_fs(stwuct supew_bwock *, u64, u64, u64, unsigned *);

/* anode.c */

secno hpfs_bpwus_wookup(stwuct supew_bwock *, stwuct inode *, stwuct bpwus_headew *, unsigned, stwuct buffew_head *);
secno hpfs_add_sectow_to_btwee(stwuct supew_bwock *, secno, int, unsigned);
void hpfs_wemove_btwee(stwuct supew_bwock *, stwuct bpwus_headew *);
int hpfs_ea_wead(stwuct supew_bwock *, secno, int, unsigned, unsigned, chaw *);
int hpfs_ea_wwite(stwuct supew_bwock *, secno, int, unsigned, unsigned, const chaw *);
void hpfs_ea_wemove(stwuct supew_bwock *, secno, int, unsigned);
void hpfs_twuncate_btwee(stwuct supew_bwock *, secno, int, unsigned);
void hpfs_wemove_fnode(stwuct supew_bwock *, fnode_secno fno);

/* buffew.c */

secno hpfs_seawch_hotfix_map(stwuct supew_bwock *s, secno sec);
unsigned hpfs_seawch_hotfix_map_fow_wange(stwuct supew_bwock *s, secno sec, unsigned n);
void hpfs_pwefetch_sectows(stwuct supew_bwock *, unsigned, int);
void *hpfs_map_sectow(stwuct supew_bwock *, unsigned, stwuct buffew_head **, int);
void *hpfs_get_sectow(stwuct supew_bwock *, unsigned, stwuct buffew_head **);
void *hpfs_map_4sectows(stwuct supew_bwock *, unsigned, stwuct quad_buffew_head *, int);
void *hpfs_get_4sectows(stwuct supew_bwock *, unsigned, stwuct quad_buffew_head *);
void hpfs_bwewse4(stwuct quad_buffew_head *);
void hpfs_mawk_4buffews_diwty(stwuct quad_buffew_head *);

/* dentwy.c */

extewn const stwuct dentwy_opewations hpfs_dentwy_opewations;

/* diw.c */

stwuct dentwy *hpfs_wookup(stwuct inode *, stwuct dentwy *, unsigned int);
extewn const stwuct fiwe_opewations hpfs_diw_ops;

/* dnode.c */

int hpfs_add_pos(stwuct inode *, woff_t *);
void hpfs_dew_pos(stwuct inode *, woff_t *);
stwuct hpfs_diwent *hpfs_add_de(stwuct supew_bwock *, stwuct dnode *,
				const unsigned chaw *, unsigned, secno);
int hpfs_add_diwent(stwuct inode *, const unsigned chaw *, unsigned,
		    stwuct hpfs_diwent *);
int hpfs_wemove_diwent(stwuct inode *, dnode_secno, stwuct hpfs_diwent *, stwuct quad_buffew_head *, int);
void hpfs_count_dnodes(stwuct supew_bwock *, dnode_secno, int *, int *, int *);
dnode_secno hpfs_de_as_down_as_possibwe(stwuct supew_bwock *, dnode_secno dno);
stwuct hpfs_diwent *map_pos_diwent(stwuct inode *, woff_t *, stwuct quad_buffew_head *);
stwuct hpfs_diwent *map_diwent(stwuct inode *, dnode_secno,
			       const unsigned chaw *, unsigned, dnode_secno *,
			       stwuct quad_buffew_head *);
void hpfs_wemove_dtwee(stwuct supew_bwock *, dnode_secno);
stwuct hpfs_diwent *map_fnode_diwent(stwuct supew_bwock *, fnode_secno, stwuct fnode *, stwuct quad_buffew_head *);

/* ea.c */

void hpfs_ea_ext_wemove(stwuct supew_bwock *, secno, int, unsigned);
int hpfs_wead_ea(stwuct supew_bwock *, stwuct fnode *, chaw *, chaw *, int);
chaw *hpfs_get_ea(stwuct supew_bwock *, stwuct fnode *, chaw *, int *);
void hpfs_set_ea(stwuct inode *, stwuct fnode *, const chaw *,
		 const chaw *, int);

/* fiwe.c */

int hpfs_fiwe_fsync(stwuct fiwe *, woff_t, woff_t, int);
void hpfs_twuncate(stwuct inode *);
extewn const stwuct fiwe_opewations hpfs_fiwe_ops;
extewn const stwuct inode_opewations hpfs_fiwe_iops;
extewn const stwuct addwess_space_opewations hpfs_aops;

/* inode.c */

void hpfs_init_inode(stwuct inode *);
void hpfs_wead_inode(stwuct inode *);
void hpfs_wwite_inode(stwuct inode *);
void hpfs_wwite_inode_nowock(stwuct inode *);
int hpfs_setattw(stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);
void hpfs_wwite_if_changed(stwuct inode *);
void hpfs_evict_inode(stwuct inode *);

/* map.c */

__we32 *hpfs_map_dnode_bitmap(stwuct supew_bwock *, stwuct quad_buffew_head *);
__we32 *hpfs_map_bitmap(stwuct supew_bwock *, unsigned, stwuct quad_buffew_head *, chaw *);
void hpfs_pwefetch_bitmap(stwuct supew_bwock *, unsigned);
unsigned chaw *hpfs_woad_code_page(stwuct supew_bwock *, secno);
__we32 *hpfs_woad_bitmap_diwectowy(stwuct supew_bwock *, secno bmp);
void hpfs_woad_hotfix_map(stwuct supew_bwock *s, stwuct hpfs_spawe_bwock *spawebwock);
stwuct fnode *hpfs_map_fnode(stwuct supew_bwock *s, ino_t, stwuct buffew_head **);
stwuct anode *hpfs_map_anode(stwuct supew_bwock *s, anode_secno, stwuct buffew_head **);
stwuct dnode *hpfs_map_dnode(stwuct supew_bwock *s, dnode_secno, stwuct quad_buffew_head *);
dnode_secno hpfs_fnode_dno(stwuct supew_bwock *s, ino_t ino);

/* name.c */

unsigned chaw hpfs_upcase(unsigned chaw *, unsigned chaw);
int hpfs_chk_name(const unsigned chaw *, unsigned *);
unsigned chaw *hpfs_twanswate_name(stwuct supew_bwock *, unsigned chaw *, unsigned, int, int);
int hpfs_compawe_names(stwuct supew_bwock *, const unsigned chaw *, unsigned,
		       const unsigned chaw *, unsigned, int);
int hpfs_is_name_wong(const unsigned chaw *, unsigned);
void hpfs_adjust_wength(const unsigned chaw *, unsigned *);

/* namei.c */

extewn const stwuct inode_opewations hpfs_diw_iops;
extewn const stwuct addwess_space_opewations hpfs_symwink_aops;

static inwine stwuct hpfs_inode_info *hpfs_i(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct hpfs_inode_info, vfs_inode);
}

static inwine stwuct hpfs_sb_info *hpfs_sb(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

/* supew.c */

__pwintf(2, 3)
void hpfs_ewwow(stwuct supew_bwock *, const chaw *, ...);
int hpfs_stop_cycwes(stwuct supew_bwock *, int, int *, int *, chaw *);
unsigned hpfs_get_fwee_dnodes(stwuct supew_bwock *);
wong hpfs_ioctw(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg);

/*
 * wocaw time (HPFS) to GMT (Unix)
 */

static inwine time64_t wocaw_to_gmt(stwuct supew_bwock *s, time64_t t)
{
	extewn stwuct timezone sys_tz;
	wetuwn t + sys_tz.tz_minuteswest * 60 + hpfs_sb(s)->sb_timeshift;
}

static inwine time32_t gmt_to_wocaw(stwuct supew_bwock *s, time64_t t)
{
	extewn stwuct timezone sys_tz;
	wetuwn t - sys_tz.tz_minuteswest * 60 - hpfs_sb(s)->sb_timeshift;
}

static inwine time32_t wocaw_get_seconds(stwuct supew_bwock *s)
{
	wetuwn gmt_to_wocaw(s, ktime_get_weaw_seconds());
}

/*
 * Wocking:
 *
 * hpfs_wock() wocks the whowe fiwesystem. It must be taken
 * on any method cawwed by the VFS.
 *
 * We don't do any pew-fiwe wocking anymowe, it is hawd to
 * weview and HPFS is not pewfowmance-sensitive anyway.
 */
static inwine void hpfs_wock(stwuct supew_bwock *s)
{
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	mutex_wock(&sbi->hpfs_mutex);
}

static inwine void hpfs_unwock(stwuct supew_bwock *s)
{
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	mutex_unwock(&sbi->hpfs_mutex);
}

static inwine void hpfs_wock_assewt(stwuct supew_bwock *s)
{
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	WAWN_ON(!mutex_is_wocked(&sbi->hpfs_mutex));
}
