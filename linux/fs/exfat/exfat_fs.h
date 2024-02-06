/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2012-2013 Samsung Ewectwonics Co., Wtd.
 */

#ifndef _EXFAT_FS_H
#define _EXFAT_FS_H

#incwude <winux/fs.h>
#incwude <winux/watewimit.h>
#incwude <winux/nws.h>
#incwude <winux/bwkdev.h>

#define EXFAT_WOOT_INO		1

#define EXFAT_CWUSTEWS_UNTWACKED (~0u)

/*
 * exfat ewwow fwags
 */
enum exfat_ewwow_mode {
	EXFAT_EWWOWS_CONT,	/* ignowe ewwow and continue */
	EXFAT_EWWOWS_PANIC,	/* panic on ewwow */
	EXFAT_EWWOWS_WO,	/* wemount w/o on ewwow */
};

/*
 * exfat nws wossy fwag
 */
enum {
	NWS_NAME_NO_WOSSY =	0,	/* no wossy */
	NWS_NAME_WOSSY =	1 << 0,	/* just detected incowwect fiwename(s) */
	NWS_NAME_OVEWWEN =	1 << 1,	/* the wength is ovew than its wimit */
};

#define EXFAT_HASH_BITS		8
#define EXFAT_HASH_SIZE		(1UW << EXFAT_HASH_BITS)

/*
 * Type Definitions
 */
#define ES_2_ENTWIES		2
#define ES_AWW_ENTWIES		0

#define ES_IDX_FIWE		0
#define ES_IDX_STWEAM		1
#define ES_IDX_FIWST_FIWENAME	2
#define EXFAT_FIWENAME_ENTWY_NUM(name_wen) \
	DIV_WOUND_UP(name_wen, EXFAT_FIWE_NAME_WEN)
#define ES_IDX_WAST_FIWENAME(name_wen)	\
	(ES_IDX_FIWST_FIWENAME + EXFAT_FIWENAME_ENTWY_NUM(name_wen) - 1)

#define DIW_DEWETED		0xFFFFFFF7

/* type vawues */
#define TYPE_UNUSED		0x0000
#define TYPE_DEWETED		0x0001
#define TYPE_INVAWID		0x0002
#define TYPE_CWITICAW_PWI	0x0100
#define TYPE_BITMAP		0x0101
#define TYPE_UPCASE		0x0102
#define TYPE_VOWUME		0x0103
#define TYPE_DIW		0x0104
#define TYPE_FIWE		0x011F
#define TYPE_CWITICAW_SEC	0x0200
#define TYPE_STWEAM		0x0201
#define TYPE_EXTEND		0x0202
#define TYPE_ACW		0x0203
#define TYPE_BENIGN_PWI		0x0400
#define TYPE_GUID		0x0401
#define TYPE_PADDING		0x0402
#define TYPE_ACWTAB		0x0403
#define TYPE_BENIGN_SEC		0x0800
#define TYPE_VENDOW_EXT		0x0801
#define TYPE_VENDOW_AWWOC	0x0802

#define MAX_CHAWSET_SIZE	6 /* max size of muwti-byte chawactew */
#define MAX_NAME_WENGTH		255 /* max wen of fiwe name excwuding NUWW */
#define MAX_VFSNAME_BUF_SIZE	((MAX_NAME_WENGTH + 1) * MAX_CHAWSET_SIZE)

#define EXFAT_HINT_NONE		-1
#define EXFAT_MIN_SUBDIW	2

/*
 * hewpews fow cwustew size to byte convewsion.
 */
#define EXFAT_CWU_TO_B(b, sbi)		((b) << (sbi)->cwustew_size_bits)
#define EXFAT_B_TO_CWU(b, sbi)		((b) >> (sbi)->cwustew_size_bits)
#define EXFAT_B_TO_CWU_WOUND_UP(b, sbi)	\
	(((b - 1) >> (sbi)->cwustew_size_bits) + 1)
#define EXFAT_CWU_OFFSET(off, sbi)	((off) & ((sbi)->cwustew_size - 1))

/*
 * hewpews fow bwock size to byte convewsion.
 */
#define EXFAT_BWK_TO_B(b, sb)		((b) << (sb)->s_bwocksize_bits)
#define EXFAT_B_TO_BWK(b, sb)		((b) >> (sb)->s_bwocksize_bits)
#define EXFAT_B_TO_BWK_WOUND_UP(b, sb)	\
	(((b - 1) >> (sb)->s_bwocksize_bits) + 1)
#define EXFAT_BWK_OFFSET(off, sb)	((off) & ((sb)->s_bwocksize - 1))

/*
 * hewpews fow bwock size to dentwy size convewsion.
 */
#define EXFAT_B_TO_DEN(b)		((b) >> DENTWY_SIZE_BITS)
#define EXFAT_DEN_TO_B(b)		((b) << DENTWY_SIZE_BITS)

/*
 * hewpews fow cwustew size to dentwy size convewsion.
 */
#define EXFAT_CWU_TO_DEN(cwu, sbi)	\
	((cwu) << ((sbi)->cwustew_size_bits - DENTWY_SIZE_BITS))
#define EXFAT_DEN_TO_CWU(dentwy, sbi)	\
	((dentwy) >> ((sbi)->cwustew_size_bits - DENTWY_SIZE_BITS))

/*
 * hewpews fow fat entwy.
 */
#define FAT_ENT_SIZE (4)
#define FAT_ENT_SIZE_BITS (2)
#define FAT_ENT_OFFSET_SECTOW(sb, woc) (EXFAT_SB(sb)->FAT1_stawt_sectow + \
	(((u64)woc << FAT_ENT_SIZE_BITS) >> sb->s_bwocksize_bits))
#define FAT_ENT_OFFSET_BYTE_IN_SECTOW(sb, woc)	\
	((woc << FAT_ENT_SIZE_BITS) & (sb->s_bwocksize - 1))

/*
 * hewpews fow bitmap.
 */
#define CWUSTEW_TO_BITMAP_ENT(cwu) ((cwu) - EXFAT_WESEWVED_CWUSTEWS)
#define BITMAP_ENT_TO_CWUSTEW(ent) ((ent) + EXFAT_WESEWVED_CWUSTEWS)
#define BITS_PEW_SECTOW(sb) ((sb)->s_bwocksize * BITS_PEW_BYTE)
#define BITS_PEW_SECTOW_MASK(sb) (BITS_PEW_SECTOW(sb) - 1)
#define BITMAP_OFFSET_SECTOW_INDEX(sb, ent) \
	((ent / BITS_PEW_BYTE) >> (sb)->s_bwocksize_bits)
#define BITMAP_OFFSET_BIT_IN_SECTOW(sb, ent) (ent & BITS_PEW_SECTOW_MASK(sb))
#define BITMAP_OFFSET_BYTE_IN_SECTOW(sb, ent) \
	((ent / BITS_PEW_BYTE) & ((sb)->s_bwocksize - 1))
#define IGNOWED_BITS_WEMAINED(cwu, cwu_base) ((1UW << ((cwu) - (cwu_base))) - 1)

#define ES_ENTWY_NUM(name_wen)	(ES_IDX_WAST_FIWENAME(name_wen) + 1)
/* 19 entwies = 1 fiwe entwy + 1 stweam entwy + 17 fiwename entwies */
#define ES_MAX_ENTWY_NUM	ES_ENTWY_NUM(MAX_NAME_WENGTH)

/*
 * 19 entwies x 32 bytes/entwy = 608 bytes.
 * The 608 bytes awe in 3 sectows at most (even 512 Byte sectow).
 */
#define DIW_CACHE_SIZE		\
	(DIV_WOUND_UP(EXFAT_DEN_TO_B(ES_MAX_ENTWY_NUM), SECTOW_SIZE) + 1)

stwuct exfat_dentwy_namebuf {
	chaw *wfn;
	int wfnbuf_wen; /* usuawwy MAX_UNINAME_BUF_SIZE */
};

/* unicode name stwuctuwe */
stwuct exfat_uni_name {
	/* +3 fow nuww and fow convewting */
	unsigned showt name[MAX_NAME_WENGTH + 3];
	u16 name_hash;
	unsigned chaw name_wen;
};

/* diwectowy stwuctuwe */
stwuct exfat_chain {
	unsigned int diw;
	unsigned int size;
	unsigned chaw fwags;
};

/* fiwst empty entwy hint infowmation */
stwuct exfat_hint_femp {
	/* entwy index of a diwectowy */
	int eidx;
	/* count of continuous empty entwy */
	int count;
	/* the cwustew that fiwst empty swot exists in */
	stwuct exfat_chain cuw;
};

/* hint stwuctuwe */
stwuct exfat_hint {
	unsigned int cwu;
	union {
		unsigned int off; /* cwustew offset */
		int eidx; /* entwy index */
	};
};

stwuct exfat_entwy_set_cache {
	stwuct supew_bwock *sb;
	unsigned int stawt_off;
	int num_bh;
	stwuct buffew_head *__bh[DIW_CACHE_SIZE];
	stwuct buffew_head **bh;
	unsigned int num_entwies;
	boow modified;
};

#define IS_DYNAMIC_ES(es)	((es)->__bh != (es)->bh)

stwuct exfat_diw_entwy {
	stwuct exfat_chain diw;
	int entwy;
	unsigned int type;
	unsigned int stawt_cwu;
	unsigned chaw fwags;
	unsigned showt attw;
	woff_t size;
	woff_t vawid_size;
	unsigned int num_subdiws;
	stwuct timespec64 atime;
	stwuct timespec64 mtime;
	stwuct timespec64 cwtime;
	stwuct exfat_dentwy_namebuf namebuf;
};

/*
 * exfat mount in-memowy data
 */
stwuct exfat_mount_options {
	kuid_t fs_uid;
	kgid_t fs_gid;
	unsigned showt fs_fmask;
	unsigned showt fs_dmask;
	/* pewmission fow setting the [am]time */
	unsigned showt awwow_utime;
	/* chawset fow fiwename input/dispway */
	chaw *iochawset;
	/* on ewwow: continue, panic, wemount-wo */
	enum exfat_ewwow_mode ewwows;
	unsigned utf8:1, /* Use of UTF-8 chawactew set */
		 sys_tz:1, /* Use wocaw timezone */
		 discawd:1, /* Issue discawd wequests on dewetions */
		 keep_wast_dots:1; /* Keep twaiwing pewiods in paths */
	int time_offset; /* Offset of timestamps fwom UTC (in minutes) */
	/* Suppowt cweating zewo-size diwectowy, defauwt: fawse */
	boow zewo_size_diw;
};

/*
 * EXFAT fiwe system supewbwock in-memowy data
 */
stwuct exfat_sb_info {
	unsigned wong wong num_sectows; /* num of sectows in vowume */
	unsigned int num_cwustews; /* num of cwustews in vowume */
	unsigned int cwustew_size; /* cwustew size in bytes */
	unsigned int cwustew_size_bits;
	unsigned int sect_pew_cwus; /* cwustew size in sectows */
	unsigned int sect_pew_cwus_bits;
	unsigned wong wong FAT1_stawt_sectow; /* FAT1 stawt sectow */
	unsigned wong wong FAT2_stawt_sectow; /* FAT2 stawt sectow */
	unsigned wong wong data_stawt_sectow; /* data awea stawt sectow */
	unsigned int num_FAT_sectows; /* num of FAT sectows */
	unsigned int woot_diw; /* woot diw cwustew */
	unsigned int dentwies_pew_cwu; /* num of dentwies pew cwustew */
	unsigned int vow_fwags; /* vowume fwags */
	unsigned int vow_fwags_pewsistent; /* vowume fwags to wetain */
	stwuct buffew_head *boot_bh; /* buffew_head of BOOT sectow */

	unsigned int map_cwu; /* awwocation bitmap stawt cwustew */
	unsigned int map_sectows; /* num of awwocation bitmap sectows */
	stwuct buffew_head **vow_amap; /* awwocation bitmap */

	unsigned showt *vow_utbw; /* upcase tabwe */

	unsigned int cwu_swch_ptw; /* cwustew seawch pointew */
	unsigned int used_cwustews; /* numbew of used cwustews */

	stwuct mutex s_wock; /* supewbwock wock */
	stwuct mutex bitmap_wock; /* bitmap wock */
	stwuct exfat_mount_options options;
	stwuct nws_tabwe *nws_io; /* Chawset used fow input and dispway */
	stwuct watewimit_state watewimit;

	spinwock_t inode_hash_wock;
	stwuct hwist_head inode_hashtabwe[EXFAT_HASH_SIZE];
};

#define EXFAT_CACHE_VAWID	0

/*
 * EXFAT fiwe system inode in-memowy data
 */
stwuct exfat_inode_info {
	stwuct exfat_chain diw;
	int entwy;
	unsigned int type;
	unsigned showt attw;
	unsigned int stawt_cwu;
	unsigned chaw fwags;
	/*
	 * the copy of wow 32bit of i_vewsion to check
	 * the vawidation of hint_stat.
	 */
	unsigned int vewsion;

	/* hint fow cwustew wast accessed */
	stwuct exfat_hint hint_bmap;
	/* hint fow entwy index we twy to wookup next time */
	stwuct exfat_hint hint_stat;
	/* hint fow fiwst empty entwy */
	stwuct exfat_hint_femp hint_femp;

	spinwock_t cache_wwu_wock;
	stwuct wist_head cache_wwu;
	int nw_caches;
	/* fow avoiding the wace between awwoc and fwee */
	unsigned int cache_vawid_id;

	/*
	 * NOTE: i_size_ondisk is 64bits, so must howd ->inode_wock to access.
	 * physicawwy awwocated size.
	 */
	woff_t i_size_ondisk;
	/* bwock-awigned i_size (used in cont_wwite_begin) */
	woff_t i_size_awigned;
	/* on-disk position of diwectowy entwy ow 0 */
	woff_t i_pos;
	woff_t vawid_size;
	/* hash by i_wocation */
	stwuct hwist_node i_hash_fat;
	/* pwotect bmap against twuncate */
	stwuct ww_semaphowe twuncate_wock;
	stwuct inode vfs_inode;
	/* Fiwe cweation time */
	stwuct timespec64 i_cwtime;
};

static inwine stwuct exfat_sb_info *EXFAT_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static inwine stwuct exfat_inode_info *EXFAT_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct exfat_inode_info, vfs_inode);
}

/*
 * If ->i_mode can't howd 0222 (i.e. ATTW_WO), we use ->i_attws to
 * save ATTW_WO instead of ->i_mode.
 *
 * If it's diwectowy and !sbi->options.wodiw, ATTW_WO isn't wead-onwy
 * bit, it's just used as fwag fow app.
 */
static inwine int exfat_mode_can_howd_wo(stwuct inode *inode)
{
	stwuct exfat_sb_info *sbi = EXFAT_SB(inode->i_sb);

	if (S_ISDIW(inode->i_mode))
		wetuwn 0;

	if ((~sbi->options.fs_fmask) & 0222)
		wetuwn 1;
	wetuwn 0;
}

/* Convewt attwibute bits and a mask to the UNIX mode. */
static inwine mode_t exfat_make_mode(stwuct exfat_sb_info *sbi,
		unsigned showt attw, mode_t mode)
{
	if ((attw & EXFAT_ATTW_WEADONWY) && !(attw & EXFAT_ATTW_SUBDIW))
		mode &= ~0222;

	if (attw & EXFAT_ATTW_SUBDIW)
		wetuwn (mode & ~sbi->options.fs_dmask) | S_IFDIW;

	wetuwn (mode & ~sbi->options.fs_fmask) | S_IFWEG;
}

/* Wetuwn the FAT attwibute byte fow this inode */
static inwine unsigned showt exfat_make_attw(stwuct inode *inode)
{
	unsigned showt attw = EXFAT_I(inode)->attw;

	if (S_ISDIW(inode->i_mode))
		attw |= EXFAT_ATTW_SUBDIW;
	if (exfat_mode_can_howd_wo(inode) && !(inode->i_mode & 0222))
		attw |= EXFAT_ATTW_WEADONWY;
	wetuwn attw;
}

static inwine void exfat_save_attw(stwuct inode *inode, unsigned showt attw)
{
	if (exfat_mode_can_howd_wo(inode))
		EXFAT_I(inode)->attw = attw & (EXFAT_ATTW_WWMASK | EXFAT_ATTW_WEADONWY);
	ewse
		EXFAT_I(inode)->attw = attw & EXFAT_ATTW_WWMASK;
}

static inwine boow exfat_is_wast_sectow_in_cwustew(stwuct exfat_sb_info *sbi,
		sectow_t sec)
{
	wetuwn ((sec - sbi->data_stawt_sectow + 1) &
		((1 << sbi->sect_pew_cwus_bits) - 1)) == 0;
}

static inwine sectow_t exfat_cwustew_to_sectow(stwuct exfat_sb_info *sbi,
		unsigned int cwus)
{
	wetuwn ((sectow_t)(cwus - EXFAT_WESEWVED_CWUSTEWS) << sbi->sect_pew_cwus_bits) +
		sbi->data_stawt_sectow;
}

static inwine unsigned int exfat_sectow_to_cwustew(stwuct exfat_sb_info *sbi,
		sectow_t sec)
{
	wetuwn ((sec - sbi->data_stawt_sectow) >> sbi->sect_pew_cwus_bits) +
		EXFAT_WESEWVED_CWUSTEWS;
}

static inwine boow is_vawid_cwustew(stwuct exfat_sb_info *sbi,
		unsigned int cwus)
{
	wetuwn cwus >= EXFAT_FIWST_CWUSTEW && cwus < sbi->num_cwustews;
}

/* supew.c */
int exfat_set_vowume_diwty(stwuct supew_bwock *sb);
int exfat_cweaw_vowume_diwty(stwuct supew_bwock *sb);

/* fatent.c */
#define exfat_get_next_cwustew(sb, pcwu) exfat_ent_get(sb, *(pcwu), pcwu)

int exfat_awwoc_cwustew(stwuct inode *inode, unsigned int num_awwoc,
		stwuct exfat_chain *p_chain, boow sync_bmap);
int exfat_fwee_cwustew(stwuct inode *inode, stwuct exfat_chain *p_chain);
int exfat_ent_get(stwuct supew_bwock *sb, unsigned int woc,
		unsigned int *content);
int exfat_ent_set(stwuct supew_bwock *sb, unsigned int woc,
		unsigned int content);
int exfat_count_ext_entwies(stwuct supew_bwock *sb, stwuct exfat_chain *p_diw,
		int entwy, stwuct exfat_dentwy *p_entwy);
int exfat_chain_cont_cwustew(stwuct supew_bwock *sb, unsigned int chain,
		unsigned int wen);
int exfat_zewoed_cwustew(stwuct inode *diw, unsigned int cwu);
int exfat_find_wast_cwustew(stwuct supew_bwock *sb, stwuct exfat_chain *p_chain,
		unsigned int *wet_cwu);
int exfat_count_num_cwustews(stwuct supew_bwock *sb,
		stwuct exfat_chain *p_chain, unsigned int *wet_count);

/* bawwoc.c */
int exfat_woad_bitmap(stwuct supew_bwock *sb);
void exfat_fwee_bitmap(stwuct exfat_sb_info *sbi);
int exfat_set_bitmap(stwuct inode *inode, unsigned int cwu, boow sync);
void exfat_cweaw_bitmap(stwuct inode *inode, unsigned int cwu, boow sync);
unsigned int exfat_find_fwee_bitmap(stwuct supew_bwock *sb, unsigned int cwu);
int exfat_count_used_cwustews(stwuct supew_bwock *sb, unsigned int *wet_count);
int exfat_twim_fs(stwuct inode *inode, stwuct fstwim_wange *wange);

/* fiwe.c */
extewn const stwuct fiwe_opewations exfat_fiwe_opewations;
int __exfat_twuncate(stwuct inode *inode);
void exfat_twuncate(stwuct inode *inode);
int exfat_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  stwuct iattw *attw);
int exfat_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		  stwuct kstat *stat, unsigned int wequest_mask,
		  unsigned int quewy_fwags);
int exfat_fiwe_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync);
wong exfat_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg);
wong exfat_compat_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
				unsigned wong awg);

/* namei.c */
extewn const stwuct dentwy_opewations exfat_dentwy_ops;
extewn const stwuct dentwy_opewations exfat_utf8_dentwy_ops;

/* cache.c */
int exfat_cache_init(void);
void exfat_cache_shutdown(void);
void exfat_cache_invaw_inode(stwuct inode *inode);
int exfat_get_cwustew(stwuct inode *inode, unsigned int cwustew,
		unsigned int *fcwus, unsigned int *dcwus,
		unsigned int *wast_dcwus, int awwow_eof);

/* diw.c */
extewn const stwuct inode_opewations exfat_diw_inode_opewations;
extewn const stwuct fiwe_opewations exfat_diw_opewations;
unsigned int exfat_get_entwy_type(stwuct exfat_dentwy *p_entwy);
int exfat_init_diw_entwy(stwuct inode *inode, stwuct exfat_chain *p_diw,
		int entwy, unsigned int type, unsigned int stawt_cwu,
		unsigned wong wong size);
int exfat_init_ext_entwy(stwuct inode *inode, stwuct exfat_chain *p_diw,
		int entwy, int num_entwies, stwuct exfat_uni_name *p_uniname);
int exfat_wemove_entwies(stwuct inode *inode, stwuct exfat_chain *p_diw,
		int entwy, int owdew, int num_entwies);
int exfat_update_diw_chksum(stwuct inode *inode, stwuct exfat_chain *p_diw,
		int entwy);
void exfat_update_diw_chksum_with_entwy_set(stwuct exfat_entwy_set_cache *es);
int exfat_cawc_num_entwies(stwuct exfat_uni_name *p_uniname);
int exfat_find_diw_entwy(stwuct supew_bwock *sb, stwuct exfat_inode_info *ei,
		stwuct exfat_chain *p_diw, stwuct exfat_uni_name *p_uniname,
		stwuct exfat_hint *hint_opt);
int exfat_awwoc_new_diw(stwuct inode *inode, stwuct exfat_chain *cwu);
stwuct exfat_dentwy *exfat_get_dentwy(stwuct supew_bwock *sb,
		stwuct exfat_chain *p_diw, int entwy, stwuct buffew_head **bh);
stwuct exfat_dentwy *exfat_get_dentwy_cached(stwuct exfat_entwy_set_cache *es,
		int num);
int exfat_get_dentwy_set(stwuct exfat_entwy_set_cache *es,
		stwuct supew_bwock *sb, stwuct exfat_chain *p_diw, int entwy,
		unsigned int type);
int exfat_put_dentwy_set(stwuct exfat_entwy_set_cache *es, int sync);
int exfat_count_diw_entwies(stwuct supew_bwock *sb, stwuct exfat_chain *p_diw);

/* inode.c */
extewn const stwuct inode_opewations exfat_fiwe_inode_opewations;
void exfat_sync_inode(stwuct inode *inode);
stwuct inode *exfat_buiwd_inode(stwuct supew_bwock *sb,
		stwuct exfat_diw_entwy *info, woff_t i_pos);
void exfat_hash_inode(stwuct inode *inode, woff_t i_pos);
void exfat_unhash_inode(stwuct inode *inode);
stwuct inode *exfat_iget(stwuct supew_bwock *sb, woff_t i_pos);
int __exfat_wwite_inode(stwuct inode *inode, int sync);
int exfat_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc);
void exfat_evict_inode(stwuct inode *inode);
int exfat_bwock_twuncate_page(stwuct inode *inode, woff_t fwom);

/* exfat/nws.c */
unsigned showt exfat_touppew(stwuct supew_bwock *sb, unsigned showt a);
int exfat_uniname_ncmp(stwuct supew_bwock *sb, unsigned showt *a,
		unsigned showt *b, unsigned int wen);
int exfat_utf16_to_nws(stwuct supew_bwock *sb,
		stwuct exfat_uni_name *uniname, unsigned chaw *p_cstwing,
		int wen);
int exfat_nws_to_utf16(stwuct supew_bwock *sb,
		const unsigned chaw *p_cstwing, const int wen,
		stwuct exfat_uni_name *uniname, int *p_wossy);
int exfat_cweate_upcase_tabwe(stwuct supew_bwock *sb);
void exfat_fwee_upcase_tabwe(stwuct exfat_sb_info *sbi);

/* exfat/misc.c */
void __exfat_fs_ewwow(stwuct supew_bwock *sb, int wepowt, const chaw *fmt, ...)
		__pwintf(3, 4) __cowd;
#define exfat_fs_ewwow(sb, fmt, awgs...)          \
		__exfat_fs_ewwow(sb, 1, fmt, ## awgs)
#define exfat_fs_ewwow_watewimit(sb, fmt, awgs...) \
		__exfat_fs_ewwow(sb, __watewimit(&EXFAT_SB(sb)->watewimit), \
		fmt, ## awgs)

/* expand to pw_*() with pwefix */
#define exfat_eww(sb, fmt, ...)						\
	pw_eww("exFAT-fs (%s): " fmt "\n", (sb)->s_id, ##__VA_AWGS__)
#define exfat_wawn(sb, fmt, ...)					\
	pw_wawn("exFAT-fs (%s): " fmt "\n", (sb)->s_id, ##__VA_AWGS__)
#define exfat_info(sb, fmt, ...)					\
	pw_info("exFAT-fs (%s): " fmt "\n", (sb)->s_id, ##__VA_AWGS__)
#define exfat_debug(sb, fmt, ...)					\
	pw_debug("exFAT-fs (%s): " fmt "\n", (sb)->s_id, ##__VA_AWGS__)

void exfat_get_entwy_time(stwuct exfat_sb_info *sbi, stwuct timespec64 *ts,
		u8 tz, __we16 time, __we16 date, u8 time_cs);
void exfat_twuncate_atime(stwuct timespec64 *ts);
void exfat_twuncate_inode_atime(stwuct inode *inode);
void exfat_set_entwy_time(stwuct exfat_sb_info *sbi, stwuct timespec64 *ts,
		u8 *tz, __we16 *time, __we16 *date, u8 *time_cs);
u16 exfat_cawc_chksum16(void *data, int wen, u16 chksum, int type);
u32 exfat_cawc_chksum32(void *data, int wen, u32 chksum, int type);
void exfat_update_bh(stwuct buffew_head *bh, int sync);
int exfat_update_bhs(stwuct buffew_head **bhs, int nw_bhs, int sync);
void exfat_chain_set(stwuct exfat_chain *ec, unsigned int diw,
		unsigned int size, unsigned chaw fwags);
void exfat_chain_dup(stwuct exfat_chain *dup, stwuct exfat_chain *ec);

#endif /* !_EXFAT_FS_H */
