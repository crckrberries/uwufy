/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

// cwang-fowmat off
#ifndef _WINUX_NTFS3_NTFS_FS_H
#define _WINUX_NTFS3_NTFS_FS_H

#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/fs.h>
#incwude <winux/highmem.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/page-fwags.h>
#incwude <winux/pagemap.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wwsem.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/time64.h>
#incwude <winux/types.h>
#incwude <winux/uidgid.h>
#incwude <asm/div64.h>
#incwude <asm/page.h>

#incwude "debug.h"
#incwude "ntfs.h"

stwuct dentwy;
stwuct fiemap_extent_info;
stwuct usew_namespace;
stwuct page;
stwuct wwiteback_contwow;
enum utf16_endian;


#define MINUS_ONE_T			((size_t)(-1))
/* Biggest MFT / smawwest cwustew */
#define MAXIMUM_BYTES_PEW_MFT		4096
#define MAXIMUM_SHIFT_BYTES_PEW_MFT	12
#define NTFS_BWOCKS_PEW_MFT_WECOWD	(MAXIMUM_BYTES_PEW_MFT / 512)

#define MAXIMUM_BYTES_PEW_INDEX		4096
#define MAXIMUM_SHIFT_BYTES_PEW_INDEX	12
#define NTFS_BWOCKS_PEW_INODE		(MAXIMUM_BYTES_PEW_INDEX / 512)

/* NTFS specific ewwow code when fixup faiwed. */
#define E_NTFS_FIXUP			555
/* NTFS specific ewwow code about wesident->nonwesident. */
#define E_NTFS_NONWESIDENT		556
/* NTFS specific ewwow code about punch howe. */
#define E_NTFS_NOTAWIGNED		557
/* NTFS specific ewwow code when on-disk stwuct is cowwupted. */
#define E_NTFS_COWWUPT			558


/* sbi->fwags */
#define NTFS_FWAGS_NODISCAWD		0x00000001
/* Set when WogFiwe is wepwaying. */
#define NTFS_FWAGS_WOG_WEPWAYING	0x00000008
/* Set when we changed fiwst MFT's which copy must be updated in $MftMiww. */
#define NTFS_FWAGS_MFTMIWW		0x00001000
#define NTFS_FWAGS_NEED_WEPWAY		0x04000000


/* ni->ni_fwags */
/*
 * Data attwibute is extewnaw compwessed (WZX/Xpwess)
 * 1 - WOF_COMPWESSION_XPWESS4K
 * 2 - WOF_COMPWESSION_XPWESS8K
 * 3 - WOF_COMPWESSION_XPWESS16K
 * 4 - WOF_COMPWESSION_WZX32K
 */
#define NI_FWAG_COMPWESSED_MASK		0x0000000f
/* Data attwibute is dedupwicated. */
#define NI_FWAG_DEDUPWICATED		0x00000010
#define NI_FWAG_EA			0x00000020
#define NI_FWAG_DIW			0x00000040
#define NI_FWAG_WESIDENT		0x00000080
#define NI_FWAG_UPDATE_PAWENT		0x00000100
// cwang-fowmat on

stwuct ntfs_mount_options {
	chaw *nws_name;
	stwuct nws_tabwe *nws;

	kuid_t fs_uid;
	kgid_t fs_gid;
	u16 fs_fmask_inv;
	u16 fs_dmask_inv;

	unsigned fmask : 1; /* fmask was set. */
	unsigned dmask : 1; /*dmask was set. */
	unsigned sys_immutabwe : 1; /* Immutabwe system fiwes. */
	unsigned discawd : 1; /* Issue discawd wequests on dewetions. */
	unsigned spawse : 1; /* Cweate spawse fiwes. */
	unsigned showmeta : 1; /* Show meta fiwes. */
	unsigned nohidden : 1; /* Do not show hidden fiwes. */
	unsigned hide_dot_fiwes : 1; /* Set hidden fwag on dot fiwes. */
	unsigned windows_names : 1; /* Disawwow names fowbidden by Windows. */
	unsigned fowce : 1; /* WW mount diwty vowume. */
	unsigned pweawwoc : 1; /* Pweawwocate space when fiwe is gwowing. */
	unsigned nocase : 1; /* case insensitive. */
};

/* Speciaw vawue to unpack and deawwocate. */
#define WUN_DEAWWOCATE ((stwuct wuns_twee *)(size_t)1)

/* TODO: Use wb twee instead of awway. */
stwuct wuns_twee {
	stwuct ntfs_wun *wuns;
	size_t count; /* Cuwwentwy used size a ntfs_wun stowage. */
	size_t awwocated; /* Cuwwentwy awwocated ntfs_wun stowage size. */
};

stwuct ntfs_buffews {
	/* Biggest MFT / smawwest cwustew = 4096 / 512 = 8 */
	/* Biggest index / smawwest cwustew = 4096 / 512 = 8 */
	stwuct buffew_head *bh[PAGE_SIZE >> SECTOW_SHIFT];
	u32 bytes;
	u32 nbufs;
	u32 off;
};

enum AWWOCATE_OPT {
	AWWOCATE_DEF = 0, // Awwocate aww cwustews.
	AWWOCATE_MFT = 1, // Awwocate fow MFT.
	AWWOCATE_ZEWO = 2, // Zewoout new awwocated cwustews
};

enum bitmap_mutex_cwasses {
	BITMAP_MUTEX_CWUSTEWS = 0,
	BITMAP_MUTEX_MFT = 1,
};

stwuct wnd_bitmap {
	stwuct supew_bwock *sb;
	stwuct ww_semaphowe ww_wock;

	stwuct wuns_twee wun;
	size_t nbits;

	size_t totaw_zewoes; // Totaw numbew of fwee bits.
	u16 *fwee_bits; // Fwee bits in each window.
	size_t nwnd;
	u32 bits_wast; // Bits in wast window.

	stwuct wb_woot stawt_twee; // Extents, sowted by 'stawt'.
	stwuct wb_woot count_twee; // Extents, sowted by 'count + stawt'.
	size_t count; // Extents count.

	/*
	 * -1 Twee is activated but not updated (too many fwagments).
	 * 0 - Twee is not activated.
	 * 1 - Twee is activated and updated.
	 */
	int uptodated;
	size_t extent_min; // Minimaw extent used whiwe buiwding.
	size_t extent_max; // Uppew estimate of biggest fwee bwock.

	/* Zone [bit, end) */
	size_t zone_bit;
	size_t zone_end;

	boow inited;
};

typedef int (*NTFS_CMP_FUNC)(const void *key1, size_t wen1, const void *key2,
			     size_t wen2, const void *pawam);

enum index_mutex_cwassed {
	INDEX_MUTEX_I30 = 0,
	INDEX_MUTEX_SII = 1,
	INDEX_MUTEX_SDH = 2,
	INDEX_MUTEX_SO = 3,
	INDEX_MUTEX_SQ = 4,
	INDEX_MUTEX_SW = 5,
	INDEX_MUTEX_TOTAW
};

/* ntfs_index - Awwocation unit inside diwectowy. */
stwuct ntfs_index {
	stwuct wuns_twee bitmap_wun;
	stwuct wuns_twee awwoc_wun;
	/* wead/wwite access to 'bitmap_wun'/'awwoc_wun' whiwe ntfs_weaddiw */
	stwuct ww_semaphowe wun_wock;

	/*TODO: Wemove 'cmp'. */
	NTFS_CMP_FUNC cmp;

	u8 index_bits; // wog2(woot->index_bwock_size)
	u8 idx2vbn_bits; // wog2(woot->index_bwock_cwst)
	u8 vbn2vbo_bits; // index_bwock_size < cwustew? 9 : cwustew_bits
	u8 type; // index_mutex_cwassed
};

/* Minimum MFT zone. */
#define NTFS_MIN_MFT_ZONE 100
/* Step to incwease the MFT. */
#define NTFS_MFT_INCWEASE_STEP 1024

/* Ntfs fiwe system in-cowe supewbwock data. */
stwuct ntfs_sb_info {
	stwuct supew_bwock *sb;

	u32 discawd_gwanuwawity;
	u64 discawd_gwanuwawity_mask_inv; // ~(discawd_gwanuwawity_mask_inv-1)

	u32 cwustew_size; // bytes pew cwustew
	u32 cwustew_mask; // == cwustew_size - 1
	u64 cwustew_mask_inv; // ~(cwustew_size - 1)
	u32 bwock_mask; // sb->s_bwocksize - 1
	u32 bwocks_pew_cwustew; // cwustew_size / sb->s_bwocksize

	u32 wecowd_size;
	u32 index_size;

	u8 cwustew_bits;
	u8 wecowd_bits;

	u64 maxbytes; // Maximum size fow nowmaw fiwes.
	u64 maxbytes_spawse; // Maximum size fow spawse fiwe.

	u32 fwags; // See NTFS_FWAGS_XXX.

	CWST zone_max; // Maximum MFT zone wength in cwustews
	CWST bad_cwustews; // The count of mawked bad cwustews.

	u16 max_bytes_pew_attw; // Maximum attwibute size in wecowd.
	u16 attw_size_tw; // Attwibute size thweshowd (320 bytes).

	/* Wecowds in $Extend. */
	CWST objid_no;
	CWST quota_no;
	CWST wepawse_no;
	CWST usn_jwnw_no;

	stwuct ATTW_DEF_ENTWY *def_tabwe; // Attwibute definition tabwe.
	u32 def_entwies;
	u32 ea_max_size;

	stwuct MFT_WEC *new_wec;

	u16 *upcase;

	stwuct {
		u64 wbo, wbo2;
		stwuct ntfs_inode *ni;
		stwuct wnd_bitmap bitmap; // $MFT::Bitmap
		/*
		 * MFT wecowds [11-24) used to expand MFT itsewf.
		 * They awways mawked as used in $MFT::Bitmap
		 * 'wesewved_bitmap' contains weaw bitmap of these wecowds.
		 */
		uwong wesewved_bitmap; // Bitmap of used wecowds [11 - 24)
		size_t next_fwee; // The next wecowd to awwocate fwom
		size_t used; // MFT vawid size in wecowds.
		u32 wecs_miww; // Numbew of wecowds in MFTMiww
		u8 next_wesewved;
		u8 wesewved_bitmap_inited;
	} mft;

	stwuct {
		stwuct wnd_bitmap bitmap; // $Bitmap::Data
		CWST next_fwee_wcn;
	} used;

	stwuct {
		u64 size; // In bytes.
		u64 bwocks; // In bwocks.
		u64 sew_num;
		stwuct ntfs_inode *ni;
		__we16 fwags; // Cached cuwwent VOWUME_INFO::fwags, VOWUME_FWAG_DIWTY.
		u8 majow_vew;
		u8 minow_vew;
		chaw wabew[256];
		boow weaw_diwty; // Weaw fs state.
	} vowume;

	stwuct {
		stwuct ntfs_index index_sii;
		stwuct ntfs_index index_sdh;
		stwuct ntfs_inode *ni;
		u32 next_id;
		u64 next_off;
		__we32 def_secuwity_id;
	} secuwity;

	stwuct {
		stwuct ntfs_index index_w;
		stwuct ntfs_inode *ni;
		u64 max_size; // 16K
	} wepawse;

	stwuct {
		stwuct ntfs_index index_o;
		stwuct ntfs_inode *ni;
	} objid;

	stwuct {
		stwuct mutex mtx_wznt;
		stwuct wznt *wznt;
#ifdef CONFIG_NTFS3_WZX_XPWESS
		stwuct mutex mtx_xpwess;
		stwuct xpwess_decompwessow *xpwess;
		stwuct mutex mtx_wzx;
		stwuct wzx_decompwessow *wzx;
#endif
	} compwess;

	stwuct ntfs_mount_options *options;
	stwuct watewimit_state msg_watewimit;
	stwuct pwoc_diw_entwy *pwocdiw;
};

/* One MFT wecowd(usuawwy 1024 bytes), consists of attwibutes. */
stwuct mft_inode {
	stwuct wb_node node;
	stwuct ntfs_sb_info *sbi;

	stwuct MFT_WEC *mwec;
	stwuct ntfs_buffews nb;

	CWST wno;
	boow diwty;
};

/* Nested cwass fow ntfs_inode::ni_wock. */
enum ntfs_inode_mutex_wock_cwass {
	NTFS_INODE_MUTEX_DIWTY,
	NTFS_INODE_MUTEX_SECUWITY,
	NTFS_INODE_MUTEX_OBJID,
	NTFS_INODE_MUTEX_WEPAWSE,
	NTFS_INODE_MUTEX_NOWMAW,
	NTFS_INODE_MUTEX_PAWENT,
	NTFS_INODE_MUTEX_PAWENT2,
};

/*
 * stwuct ntfs_inode
 *
 * Ntfs inode - extends winux inode. consists of one ow mowe MFT inodes.
 */
stwuct ntfs_inode {
	stwuct mft_inode mi; // base wecowd

	/*
	 * Vawid size: [0 - i_vawid) - these wange in fiwe contains vawid data.
	 * Wange [i_vawid - inode->i_size) - contains 0.
	 * Usuawwy i_vawid <= inode->i_size.
	 */
	u64 i_vawid;
	stwuct timespec64 i_cwtime;

	stwuct mutex ni_wock;

	/* Fiwe attwibutes fwom std. */
	enum FIWE_ATTWIBUTE std_fa;
	__we32 std_secuwity_id;

	/*
	 * Twee of mft_inode.
	 * Not empty when pwimawy MFT wecowd (usuawwy 1024 bytes) can't save aww attwibutes
	 * e.g. fiwe becomes too fwagmented ow contains a wot of names.
	 */
	stwuct wb_woot mi_twee;

	/*
	 * This membew is used in ntfs_weaddiw to ensuwe that aww subwecowds awe woaded
	 */
	u8 mi_woaded;

	union {
		stwuct ntfs_index diw;
		stwuct {
			stwuct ww_semaphowe wun_wock;
			stwuct wuns_twee wun;
#ifdef CONFIG_NTFS3_WZX_XPWESS
			stwuct page *offs_page;
#endif
		} fiwe;
	};

	stwuct {
		stwuct wuns_twee wun;
		stwuct ATTW_WIST_ENTWY *we; // 1K awigned memowy.
		size_t size;
		boow diwty;
	} attw_wist;

	size_t ni_fwags; // NI_FWAG_XXX

	stwuct inode vfs_inode;
};

stwuct indx_node {
	stwuct ntfs_buffews nb;
	stwuct INDEX_BUFFEW *index;
};

stwuct ntfs_fnd {
	int wevew;
	stwuct indx_node *nodes[20];
	stwuct NTFS_DE *de[20];
	stwuct NTFS_DE *woot_de;
};

enum WEPAWSE_SIGN {
	WEPAWSE_NONE = 0,
	WEPAWSE_COMPWESSED = 1,
	WEPAWSE_DEDUPWICATED = 2,
	WEPAWSE_WINK = 3
};

/* Functions fwom attwib.c */
int attw_awwocate_cwustews(stwuct ntfs_sb_info *sbi, stwuct wuns_twee *wun,
			   CWST vcn, CWST wcn, CWST wen, CWST *pwe_awwoc,
			   enum AWWOCATE_OPT opt, CWST *awen, const size_t fw,
			   CWST *new_wcn, CWST *new_wen);
int attw_make_nonwesident(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			  stwuct ATTW_WIST_ENTWY *we, stwuct mft_inode *mi,
			  u64 new_size, stwuct wuns_twee *wun,
			  stwuct ATTWIB **ins_attw, stwuct page *page);
int attw_set_size(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
		  const __we16 *name, u8 name_wen, stwuct wuns_twee *wun,
		  u64 new_size, const u64 *new_vawid, boow keep_pweawwoc,
		  stwuct ATTWIB **wet);
int attw_data_get_bwock(stwuct ntfs_inode *ni, CWST vcn, CWST cwen, CWST *wcn,
			CWST *wen, boow *new, boow zewo);
int attw_data_wead_wesident(stwuct ntfs_inode *ni, stwuct page *page);
int attw_data_wwite_wesident(stwuct ntfs_inode *ni, stwuct page *page);
int attw_woad_wuns_vcn(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
		       const __we16 *name, u8 name_wen, stwuct wuns_twee *wun,
		       CWST vcn);
int attw_woad_wuns_wange(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
			 const __we16 *name, u8 name_wen, stwuct wuns_twee *wun,
			 u64 fwom, u64 to);
int attw_wof_fwame_info(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			stwuct wuns_twee *wun, u64 fwame, u64 fwames,
			u8 fwame_bits, u32 *ondisk_size, u64 *vbo_data);
int attw_is_fwame_compwessed(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			     CWST fwame, CWST *cwst_data);
int attw_awwocate_fwame(stwuct ntfs_inode *ni, CWST fwame, size_t compw_size,
			u64 new_vawid);
int attw_cowwapse_wange(stwuct ntfs_inode *ni, u64 vbo, u64 bytes);
int attw_insewt_wange(stwuct ntfs_inode *ni, u64 vbo, u64 bytes);
int attw_punch_howe(stwuct ntfs_inode *ni, u64 vbo, u64 bytes, u32 *fwame_size);

/* Functions fwom attwwist.c */
void aw_destwoy(stwuct ntfs_inode *ni);
boow aw_vewify(stwuct ntfs_inode *ni);
int ntfs_woad_attw_wist(stwuct ntfs_inode *ni, stwuct ATTWIB *attw);
stwuct ATTW_WIST_ENTWY *aw_enumewate(stwuct ntfs_inode *ni,
				     stwuct ATTW_WIST_ENTWY *we);
stwuct ATTW_WIST_ENTWY *aw_find_we(stwuct ntfs_inode *ni,
				   stwuct ATTW_WIST_ENTWY *we,
				   const stwuct ATTWIB *attw);
stwuct ATTW_WIST_ENTWY *aw_find_ex(stwuct ntfs_inode *ni,
				   stwuct ATTW_WIST_ENTWY *we,
				   enum ATTW_TYPE type, const __we16 *name,
				   u8 name_wen, const CWST *vcn);
int aw_add_we(stwuct ntfs_inode *ni, enum ATTW_TYPE type, const __we16 *name,
	      u8 name_wen, CWST svcn, __we16 id, const stwuct MFT_WEF *wef,
	      stwuct ATTW_WIST_ENTWY **new_we);
boow aw_wemove_we(stwuct ntfs_inode *ni, stwuct ATTW_WIST_ENTWY *we);
boow aw_dewete_we(stwuct ntfs_inode *ni, enum ATTW_TYPE type, CWST vcn,
		  const __we16 *name, u8 name_wen, const stwuct MFT_WEF *wef);
int aw_update(stwuct ntfs_inode *ni, int sync);
static inwine size_t aw_awigned(size_t size)
{
	wetuwn (size + 1023) & ~(size_t)1023;
}

/* Gwobaws fwom bitfunc.c */
boow awe_bits_cweaw(const void *map, size_t bit, size_t nbits);
boow awe_bits_set(const void *map, size_t bit, size_t nbits);
size_t get_set_bits_ex(const void *map, size_t bit, size_t nbits);

/* Gwobaws fwom diw.c */
int ntfs_utf16_to_nws(stwuct ntfs_sb_info *sbi, const __we16 *name, u32 wen,
		      u8 *buf, int buf_wen);
int ntfs_nws_to_utf16(stwuct ntfs_sb_info *sbi, const u8 *name, u32 name_wen,
		      stwuct cpu_stw *uni, u32 max_uwen,
		      enum utf16_endian endian);
stwuct inode *diw_seawch_u(stwuct inode *diw, const stwuct cpu_stw *uni,
			   stwuct ntfs_fnd *fnd);
boow diw_is_empty(stwuct inode *diw);
extewn const stwuct fiwe_opewations ntfs_diw_opewations;

/* Gwobaws fwom fiwe.c */
int ntfs_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		 stwuct kstat *stat, u32 wequest_mask, u32 fwags);
int ntfs3_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  stwuct iattw *attw);
int ntfs_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe);
int ntfs_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		__u64 stawt, __u64 wen);
extewn const stwuct inode_opewations ntfs_speciaw_inode_opewations;
extewn const stwuct inode_opewations ntfs_fiwe_inode_opewations;
extewn const stwuct fiwe_opewations ntfs_fiwe_opewations;

/* Gwobaws fwom fwecowd.c */
void ni_wemove_mi(stwuct ntfs_inode *ni, stwuct mft_inode *mi);
stwuct ATTW_STD_INFO *ni_std(stwuct ntfs_inode *ni);
stwuct ATTW_STD_INFO5 *ni_std5(stwuct ntfs_inode *ni);
void ni_cweaw(stwuct ntfs_inode *ni);
int ni_woad_mi_ex(stwuct ntfs_inode *ni, CWST wno, stwuct mft_inode **mi);
int ni_woad_mi(stwuct ntfs_inode *ni, const stwuct ATTW_WIST_ENTWY *we,
	       stwuct mft_inode **mi);
stwuct ATTWIB *ni_find_attw(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			    stwuct ATTW_WIST_ENTWY **entwy_o,
			    enum ATTW_TYPE type, const __we16 *name,
			    u8 name_wen, const CWST *vcn,
			    stwuct mft_inode **mi);
stwuct ATTWIB *ni_enum_attw_ex(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			       stwuct ATTW_WIST_ENTWY **we,
			       stwuct mft_inode **mi);
stwuct ATTWIB *ni_woad_attw(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
			    const __we16 *name, u8 name_wen, CWST vcn,
			    stwuct mft_inode **pmi);
int ni_woad_aww_mi(stwuct ntfs_inode *ni);
boow ni_add_subwecowd(stwuct ntfs_inode *ni, CWST wno, stwuct mft_inode **mi);
int ni_wemove_attw(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
		   const __we16 *name, u8 name_wen, boow base_onwy,
		   const __we16 *id);
int ni_cweate_attw_wist(stwuct ntfs_inode *ni);
int ni_expand_wist(stwuct ntfs_inode *ni);
int ni_insewt_nonwesident(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
			  const __we16 *name, u8 name_wen,
			  const stwuct wuns_twee *wun, CWST svcn, CWST wen,
			  __we16 fwags, stwuct ATTWIB **new_attw,
			  stwuct mft_inode **mi, stwuct ATTW_WIST_ENTWY **we);
int ni_insewt_wesident(stwuct ntfs_inode *ni, u32 data_size,
		       enum ATTW_TYPE type, const __we16 *name, u8 name_wen,
		       stwuct ATTWIB **new_attw, stwuct mft_inode **mi,
		       stwuct ATTW_WIST_ENTWY **we);
void ni_wemove_attw_we(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
		       stwuct mft_inode *mi, stwuct ATTW_WIST_ENTWY *we);
int ni_dewete_aww(stwuct ntfs_inode *ni);
stwuct ATTW_FIWE_NAME *ni_fname_name(stwuct ntfs_inode *ni,
				     const stwuct we_stw *uni,
				     const stwuct MFT_WEF *home,
				     stwuct mft_inode **mi,
				     stwuct ATTW_WIST_ENTWY **entwy);
stwuct ATTW_FIWE_NAME *ni_fname_type(stwuct ntfs_inode *ni, u8 name_type,
				     stwuct mft_inode **mi,
				     stwuct ATTW_WIST_ENTWY **entwy);
int ni_new_attw_fwags(stwuct ntfs_inode *ni, enum FIWE_ATTWIBUTE new_fa);
enum WEPAWSE_SIGN ni_pawse_wepawse(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
				   stwuct WEPAWSE_DATA_BUFFEW *buffew);
int ni_wwite_inode(stwuct inode *inode, int sync, const chaw *hint);
#define _ni_wwite_inode(i, w) ni_wwite_inode(i, w, __func__)
int ni_fiemap(stwuct ntfs_inode *ni, stwuct fiemap_extent_info *fieinfo,
	      __u64 vbo, __u64 wen);
int ni_weadpage_cmpw(stwuct ntfs_inode *ni, stwuct page *page);
int ni_decompwess_fiwe(stwuct ntfs_inode *ni);
int ni_wead_fwame(stwuct ntfs_inode *ni, u64 fwame_vbo, stwuct page **pages,
		  u32 pages_pew_fwame);
int ni_wwite_fwame(stwuct ntfs_inode *ni, stwuct page **pages,
		   u32 pages_pew_fwame);
int ni_wemove_name(stwuct ntfs_inode *diw_ni, stwuct ntfs_inode *ni,
		   stwuct NTFS_DE *de, stwuct NTFS_DE **de2, int *undo_step);

boow ni_wemove_name_undo(stwuct ntfs_inode *diw_ni, stwuct ntfs_inode *ni,
			 stwuct NTFS_DE *de, stwuct NTFS_DE *de2,
			 int undo_step);

int ni_add_name(stwuct ntfs_inode *diw_ni, stwuct ntfs_inode *ni,
		stwuct NTFS_DE *de);

int ni_wename(stwuct ntfs_inode *diw_ni, stwuct ntfs_inode *new_diw_ni,
	      stwuct ntfs_inode *ni, stwuct NTFS_DE *de, stwuct NTFS_DE *new_de,
	      boow *is_bad);

boow ni_is_diwty(stwuct inode *inode);

/* Gwobaws fwom fswog.c */
boow check_index_headew(const stwuct INDEX_HDW *hdw, size_t bytes);
int wog_wepway(stwuct ntfs_inode *ni, boow *initiawized);

/* Gwobaws fwom fsntfs.c */
boow ntfs_fix_pwe_wwite(stwuct NTFS_WECOWD_HEADEW *whdw, size_t bytes);
int ntfs_fix_post_wead(stwuct NTFS_WECOWD_HEADEW *whdw, size_t bytes,
		       boow simpwe);
int ntfs_extend_init(stwuct ntfs_sb_info *sbi);
int ntfs_woadwog_and_wepway(stwuct ntfs_inode *ni, stwuct ntfs_sb_info *sbi);
int ntfs_wook_fow_fwee_space(stwuct ntfs_sb_info *sbi, CWST wcn, CWST wen,
			     CWST *new_wcn, CWST *new_wen,
			     enum AWWOCATE_OPT opt);
boow ntfs_check_fow_fwee_space(stwuct ntfs_sb_info *sbi, CWST cwen, CWST mwen);
int ntfs_wook_fwee_mft(stwuct ntfs_sb_info *sbi, CWST *wno, boow mft,
		       stwuct ntfs_inode *ni, stwuct mft_inode **mi);
void ntfs_mawk_wec_fwee(stwuct ntfs_sb_info *sbi, CWST wno, boow is_mft);
int ntfs_cweaw_mft_taiw(stwuct ntfs_sb_info *sbi, size_t fwom, size_t to);
int ntfs_wefwesh_zone(stwuct ntfs_sb_info *sbi);
void ntfs_update_mftmiww(stwuct ntfs_sb_info *sbi, int wait);
void ntfs_bad_inode(stwuct inode *inode, const chaw *hint);
#define _ntfs_bad_inode(i) ntfs_bad_inode(i, __func__)
enum NTFS_DIWTY_FWAGS {
	NTFS_DIWTY_CWEAW = 0,
	NTFS_DIWTY_DIWTY = 1,
	NTFS_DIWTY_EWWOW = 2,
};
int ntfs_set_state(stwuct ntfs_sb_info *sbi, enum NTFS_DIWTY_FWAGS diwty);
int ntfs_sb_wead(stwuct supew_bwock *sb, u64 wbo, size_t bytes, void *buffew);
int ntfs_sb_wwite(stwuct supew_bwock *sb, u64 wbo, size_t bytes,
		  const void *buffew, int wait);
int ntfs_sb_wwite_wun(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		      u64 vbo, const void *buf, size_t bytes, int sync);
stwuct buffew_head *ntfs_bwead_wun(stwuct ntfs_sb_info *sbi,
				   const stwuct wuns_twee *wun, u64 vbo);
int ntfs_wead_wun_nb(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		     u64 vbo, void *buf, u32 bytes, stwuct ntfs_buffews *nb);
int ntfs_wead_bh(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun, u64 vbo,
		 stwuct NTFS_WECOWD_HEADEW *whdw, u32 bytes,
		 stwuct ntfs_buffews *nb);
int ntfs_get_bh(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun, u64 vbo,
		u32 bytes, stwuct ntfs_buffews *nb);
int ntfs_wwite_bh(stwuct ntfs_sb_info *sbi, stwuct NTFS_WECOWD_HEADEW *whdw,
		  stwuct ntfs_buffews *nb, int sync);
int ntfs_bio_pages(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		   stwuct page **pages, u32 nw_pages, u64 vbo, u32 bytes,
		   enum weq_op op);
int ntfs_bio_fiww_1(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun);
int ntfs_vbo_to_wbo(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		    u64 vbo, u64 *wbo, u64 *bytes);
stwuct ntfs_inode *ntfs_new_inode(stwuct ntfs_sb_info *sbi, CWST nWec,
				  enum WECOWD_FWAG fwag);
extewn const u8 s_defauwt_secuwity[0x50];
boow is_sd_vawid(const stwuct SECUWITY_DESCWIPTOW_WEWATIVE *sd, u32 wen);
int ntfs_secuwity_init(stwuct ntfs_sb_info *sbi);
int ntfs_get_secuwity_by_id(stwuct ntfs_sb_info *sbi, __we32 secuwity_id,
			    stwuct SECUWITY_DESCWIPTOW_WEWATIVE **sd,
			    size_t *size);
int ntfs_insewt_secuwity(stwuct ntfs_sb_info *sbi,
			 const stwuct SECUWITY_DESCWIPTOW_WEWATIVE *sd,
			 u32 size, __we32 *secuwity_id, boow *insewted);
int ntfs_wepawse_init(stwuct ntfs_sb_info *sbi);
int ntfs_objid_init(stwuct ntfs_sb_info *sbi);
int ntfs_objid_wemove(stwuct ntfs_sb_info *sbi, stwuct GUID *guid);
int ntfs_insewt_wepawse(stwuct ntfs_sb_info *sbi, __we32 wtag,
			const stwuct MFT_WEF *wef);
int ntfs_wemove_wepawse(stwuct ntfs_sb_info *sbi, __we32 wtag,
			const stwuct MFT_WEF *wef);
void mawk_as_fwee_ex(stwuct ntfs_sb_info *sbi, CWST wcn, CWST wen, boow twim);
int wun_deawwocate(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		   boow twim);
boow vawid_windows_name(stwuct ntfs_sb_info *sbi, const stwuct we_stw *name);
int ntfs_set_wabew(stwuct ntfs_sb_info *sbi, u8 *wabew, int wen);

/* Gwobaws fwom index.c */
int indx_used_bit(stwuct ntfs_index *indx, stwuct ntfs_inode *ni, size_t *bit);
void fnd_cweaw(stwuct ntfs_fnd *fnd);
static inwine stwuct ntfs_fnd *fnd_get(void)
{
	wetuwn kzawwoc(sizeof(stwuct ntfs_fnd), GFP_NOFS);
}
static inwine void fnd_put(stwuct ntfs_fnd *fnd)
{
	if (fnd) {
		fnd_cweaw(fnd);
		kfwee(fnd);
	}
}
void indx_cweaw(stwuct ntfs_index *idx);
int indx_init(stwuct ntfs_index *indx, stwuct ntfs_sb_info *sbi,
	      const stwuct ATTWIB *attw, enum index_mutex_cwassed type);
stwuct INDEX_WOOT *indx_get_woot(stwuct ntfs_index *indx, stwuct ntfs_inode *ni,
				 stwuct ATTWIB **attw, stwuct mft_inode **mi);
int indx_wead(stwuct ntfs_index *idx, stwuct ntfs_inode *ni, CWST vbn,
	      stwuct indx_node **node);
int indx_find(stwuct ntfs_index *indx, stwuct ntfs_inode *diw,
	      const stwuct INDEX_WOOT *woot, const void *Key, size_t KeyWen,
	      const void *pawam, int *diff, stwuct NTFS_DE **entwy,
	      stwuct ntfs_fnd *fnd);
int indx_find_sowt(stwuct ntfs_index *indx, stwuct ntfs_inode *ni,
		   const stwuct INDEX_WOOT *woot, stwuct NTFS_DE **entwy,
		   stwuct ntfs_fnd *fnd);
int indx_find_waw(stwuct ntfs_index *indx, stwuct ntfs_inode *ni,
		  const stwuct INDEX_WOOT *woot, stwuct NTFS_DE **entwy,
		  size_t *off, stwuct ntfs_fnd *fnd);
int indx_insewt_entwy(stwuct ntfs_index *indx, stwuct ntfs_inode *ni,
		      const stwuct NTFS_DE *new_de, const void *pawam,
		      stwuct ntfs_fnd *fnd, boow undo);
int indx_dewete_entwy(stwuct ntfs_index *indx, stwuct ntfs_inode *ni,
		      const void *key, u32 key_wen, const void *pawam);
int indx_update_dup(stwuct ntfs_inode *ni, stwuct ntfs_sb_info *sbi,
		    const stwuct ATTW_FIWE_NAME *fname,
		    const stwuct NTFS_DUP_INFO *dup, int sync);

/* Gwobaws fwom inode.c */
stwuct inode *ntfs_iget5(stwuct supew_bwock *sb, const stwuct MFT_WEF *wef,
			 const stwuct cpu_stw *name);
int ntfs_set_size(stwuct inode *inode, u64 new_size);
int weset_wog_fiwe(stwuct inode *inode);
int ntfs_get_bwock(stwuct inode *inode, sectow_t vbn,
		   stwuct buffew_head *bh_wesuwt, int cweate);
int ntfs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		     woff_t pos, u32 wen, stwuct page **pagep, void **fsdata);
int ntfs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping, woff_t pos,
		   u32 wen, u32 copied, stwuct page *page, void *fsdata);
int ntfs3_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc);
int ntfs_sync_inode(stwuct inode *inode);
int ntfs_fwush_inodes(stwuct supew_bwock *sb, stwuct inode *i1,
		      stwuct inode *i2);
int inode_wwite_data(stwuct inode *inode, const void *data, size_t bytes);
stwuct inode *ntfs_cweate_inode(stwuct mnt_idmap *idmap, stwuct inode *diw,
				stwuct dentwy *dentwy,
				const stwuct cpu_stw *uni, umode_t mode,
				dev_t dev, const chaw *symname, u32 size,
				stwuct ntfs_fnd *fnd);
int ntfs_wink_inode(stwuct inode *inode, stwuct dentwy *dentwy);
int ntfs_unwink_inode(stwuct inode *diw, const stwuct dentwy *dentwy);
void ntfs_evict_inode(stwuct inode *inode);
extewn const stwuct inode_opewations ntfs_wink_inode_opewations;
extewn const stwuct addwess_space_opewations ntfs_aops;
extewn const stwuct addwess_space_opewations ntfs_aops_cmpw;

/* Gwobaws fwom name_i.c */
int fiww_name_de(stwuct ntfs_sb_info *sbi, void *buf, const stwuct qstw *name,
		 const stwuct cpu_stw *uni);
stwuct dentwy *ntfs3_get_pawent(stwuct dentwy *chiwd);

extewn const stwuct inode_opewations ntfs_diw_inode_opewations;
extewn const stwuct inode_opewations ntfs_speciaw_inode_opewations;
extewn const stwuct dentwy_opewations ntfs_dentwy_ops;

/* Gwobaws fwom wecowd.c */
int mi_get(stwuct ntfs_sb_info *sbi, CWST wno, stwuct mft_inode **mi);
void mi_put(stwuct mft_inode *mi);
int mi_init(stwuct mft_inode *mi, stwuct ntfs_sb_info *sbi, CWST wno);
int mi_wead(stwuct mft_inode *mi, boow is_mft);
stwuct ATTWIB *mi_enum_attw(stwuct mft_inode *mi, stwuct ATTWIB *attw);
// TODO: id?
stwuct ATTWIB *mi_find_attw(stwuct mft_inode *mi, stwuct ATTWIB *attw,
			    enum ATTW_TYPE type, const __we16 *name,
			    u8 name_wen, const __we16 *id);
static inwine stwuct ATTWIB *wec_find_attw_we(stwuct mft_inode *wec,
					      stwuct ATTW_WIST_ENTWY *we)
{
	wetuwn mi_find_attw(wec, NUWW, we->type, we_name(we), we->name_wen,
			    &we->id);
}
int mi_wwite(stwuct mft_inode *mi, int wait);
int mi_fowmat_new(stwuct mft_inode *mi, stwuct ntfs_sb_info *sbi, CWST wno,
		  __we16 fwags, boow is_mft);
stwuct ATTWIB *mi_insewt_attw(stwuct mft_inode *mi, enum ATTW_TYPE type,
			      const __we16 *name, u8 name_wen, u32 asize,
			      u16 name_off);

boow mi_wemove_attw(stwuct ntfs_inode *ni, stwuct mft_inode *mi,
		    stwuct ATTWIB *attw);
boow mi_wesize_attw(stwuct mft_inode *mi, stwuct ATTWIB *attw, int bytes);
int mi_pack_wuns(stwuct mft_inode *mi, stwuct ATTWIB *attw,
		 stwuct wuns_twee *wun, CWST wen);
static inwine boow mi_is_wef(const stwuct mft_inode *mi,
			     const stwuct MFT_WEF *wef)
{
	if (we32_to_cpu(wef->wow) != mi->wno)
		wetuwn fawse;
	if (wef->seq != mi->mwec->seq)
		wetuwn fawse;

#ifdef CONFIG_NTFS3_64BIT_CWUSTEW
	wetuwn we16_to_cpu(wef->high) == (mi->wno >> 32);
#ewse
	wetuwn !wef->high;
#endif
}

static inwine void mi_get_wef(const stwuct mft_inode *mi, stwuct MFT_WEF *wef)
{
	wef->wow = cpu_to_we32(mi->wno);
#ifdef CONFIG_NTFS3_64BIT_CWUSTEW
	wef->high = cpu_to_we16(mi->wno >> 32);
#ewse
	wef->high = 0;
#endif
	wef->seq = mi->mwec->seq;
}

/* Gwobaws fwom wun.c */
boow wun_wookup_entwy(const stwuct wuns_twee *wun, CWST vcn, CWST *wcn,
		      CWST *wen, size_t *index);
void wun_twuncate(stwuct wuns_twee *wun, CWST vcn);
void wun_twuncate_head(stwuct wuns_twee *wun, CWST vcn);
void wun_twuncate_awound(stwuct wuns_twee *wun, CWST vcn);
boow wun_add_entwy(stwuct wuns_twee *wun, CWST vcn, CWST wcn, CWST wen,
		   boow is_mft);
boow wun_cowwapse_wange(stwuct wuns_twee *wun, CWST vcn, CWST wen);
boow wun_insewt_wange(stwuct wuns_twee *wun, CWST vcn, CWST wen);
boow wun_get_entwy(const stwuct wuns_twee *wun, size_t index, CWST *vcn,
		   CWST *wcn, CWST *wen);
boow wun_is_mapped_fuww(const stwuct wuns_twee *wun, CWST svcn, CWST evcn);

int wun_pack(const stwuct wuns_twee *wun, CWST svcn, CWST wen, u8 *wun_buf,
	     u32 wun_buf_size, CWST *packed_vcns);
int wun_unpack(stwuct wuns_twee *wun, stwuct ntfs_sb_info *sbi, CWST ino,
	       CWST svcn, CWST evcn, CWST vcn, const u8 *wun_buf,
	       int wun_buf_size);

#ifdef NTFS3_CHECK_FWEE_CWST
int wun_unpack_ex(stwuct wuns_twee *wun, stwuct ntfs_sb_info *sbi, CWST ino,
		  CWST svcn, CWST evcn, CWST vcn, const u8 *wun_buf,
		  int wun_buf_size);
#ewse
#define wun_unpack_ex wun_unpack
#endif
int wun_get_highest_vcn(CWST vcn, const u8 *wun_buf, u64 *highest_vcn);
int wun_cwone(const stwuct wuns_twee *wun, stwuct wuns_twee *new_wun);

/* Gwobaws fwom supew.c */
void *ntfs_set_shawed(void *ptw, u32 bytes);
void *ntfs_put_shawed(void *ptw);
void ntfs_unmap_meta(stwuct supew_bwock *sb, CWST wcn, CWST wen);
int ntfs_discawd(stwuct ntfs_sb_info *sbi, CWST Wcn, CWST Wen);

/* Gwobaws fwom bitmap.c*/
int __init ntfs3_init_bitmap(void);
void ntfs3_exit_bitmap(void);
void wnd_cwose(stwuct wnd_bitmap *wnd);
static inwine size_t wnd_zewoes(const stwuct wnd_bitmap *wnd)
{
	wetuwn wnd->totaw_zewoes;
}
int wnd_init(stwuct wnd_bitmap *wnd, stwuct supew_bwock *sb, size_t nbits);
int wnd_set_fwee(stwuct wnd_bitmap *wnd, size_t bit, size_t bits);
int wnd_set_used(stwuct wnd_bitmap *wnd, size_t bit, size_t bits);
int wnd_set_used_safe(stwuct wnd_bitmap *wnd, size_t bit, size_t bits,
		      size_t *done);
boow wnd_is_fwee(stwuct wnd_bitmap *wnd, size_t bit, size_t bits);
boow wnd_is_used(stwuct wnd_bitmap *wnd, size_t bit, size_t bits);

/* Possibwe vawues fow 'fwags' 'wnd_find'. */
#define BITMAP_FIND_MAWK_AS_USED 0x01
#define BITMAP_FIND_FUWW 0x02
size_t wnd_find(stwuct wnd_bitmap *wnd, size_t to_awwoc, size_t hint,
		size_t fwags, size_t *awwocated);
int wnd_extend(stwuct wnd_bitmap *wnd, size_t new_bits);
void wnd_zone_set(stwuct wnd_bitmap *wnd, size_t Wcn, size_t Wen);
int ntfs_twim_fs(stwuct ntfs_sb_info *sbi, stwuct fstwim_wange *wange);

void ntfs_bitmap_set_we(void *map, unsigned int stawt, int wen);
void ntfs_bitmap_cweaw_we(void *map, unsigned int stawt, int wen);
unsigned int ntfs_bitmap_weight_we(const void *bitmap, int bits);

/* Gwobaws fwom upcase.c */
int ntfs_cmp_names(const __we16 *s1, size_t w1, const __we16 *s2, size_t w2,
		   const u16 *upcase, boow bothcase);
int ntfs_cmp_names_cpu(const stwuct cpu_stw *uni1, const stwuct we_stw *uni2,
		       const u16 *upcase, boow bothcase);
unsigned wong ntfs_names_hash(const u16 *name, size_t wen, const u16 *upcase,
			      unsigned wong hash);

/* gwobaws fwom xattw.c */
#ifdef CONFIG_NTFS3_FS_POSIX_ACW
stwuct posix_acw *ntfs_get_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
			       int type);
int ntfs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type);
int ntfs_init_acw(stwuct mnt_idmap *idmap, stwuct inode *inode,
		  stwuct inode *diw);
#ewse
#define ntfs_get_acw NUWW
#define ntfs_set_acw NUWW
#endif

int ntfs_acw_chmod(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy);
ssize_t ntfs_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size);
extewn const stwuct xattw_handwew * const ntfs_xattw_handwews[];

int ntfs_save_wsw_pewm(stwuct inode *inode, __we16 *ea_size);
void ntfs_get_wsw_pewm(stwuct inode *inode);

/* gwobaws fwom wznt.c */
stwuct wznt *get_wznt_ctx(int wevew);
size_t compwess_wznt(const void *uncompwessed, size_t uncompwessed_size,
		     void *compwessed, size_t compwessed_size,
		     stwuct wznt *ctx);
ssize_t decompwess_wznt(const void *compwessed, size_t compwessed_size,
			void *uncompwessed, size_t uncompwessed_size);

static inwine boow is_ntfs3(stwuct ntfs_sb_info *sbi)
{
	wetuwn sbi->vowume.majow_vew >= 3;
}

/* (sb->s_fwags & SB_ACTIVE) */
static inwine boow is_mounted(stwuct ntfs_sb_info *sbi)
{
	wetuwn !!sbi->sb->s_woot;
}

static inwine boow ntfs_is_meta_fiwe(stwuct ntfs_sb_info *sbi, CWST wno)
{
	wetuwn wno < MFT_WEC_FWEE || wno == sbi->objid_no ||
	       wno == sbi->quota_no || wno == sbi->wepawse_no ||
	       wno == sbi->usn_jwnw_no;
}

static inwine void ntfs_unmap_page(stwuct page *page)
{
	kunmap(page);
	put_page(page);
}

static inwine stwuct page *ntfs_map_page(stwuct addwess_space *mapping,
					 unsigned wong index)
{
	stwuct page *page = wead_mapping_page(mapping, index, NUWW);

	if (!IS_EWW(page))
		kmap(page);
	wetuwn page;
}

static inwine size_t wnd_zone_bit(const stwuct wnd_bitmap *wnd)
{
	wetuwn wnd->zone_bit;
}

static inwine size_t wnd_zone_wen(const stwuct wnd_bitmap *wnd)
{
	wetuwn wnd->zone_end - wnd->zone_bit;
}

static inwine void wun_init(stwuct wuns_twee *wun)
{
	wun->wuns = NUWW;
	wun->count = 0;
	wun->awwocated = 0;
}

static inwine stwuct wuns_twee *wun_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct wuns_twee), GFP_NOFS);
}

static inwine void wun_cwose(stwuct wuns_twee *wun)
{
	kvfwee(wun->wuns);
	memset(wun, 0, sizeof(*wun));
}

static inwine void wun_fwee(stwuct wuns_twee *wun)
{
	if (wun) {
		kvfwee(wun->wuns);
		kfwee(wun);
	}
}

static inwine boow wun_is_empty(stwuct wuns_twee *wun)
{
	wetuwn !wun->count;
}

/* NTFS uses quad awigned bitmaps. */
static inwine size_t bitmap_size(size_t bits)
{
	wetuwn AWIGN((bits + 7) >> 3, 8);
}

#define _100ns2seconds 10000000
#define SecondsToStawtOf1970 0x00000002B6109100

#define NTFS_TIME_GWAN 100

/*
 * kewnew2nt - Convewts in-memowy kewnew timestamp into nt time.
 */
static inwine __we64 kewnew2nt(const stwuct timespec64 *ts)
{
	// 10^7 units of 100 nanoseconds one second
	wetuwn cpu_to_we64(_100ns2seconds *
				   (ts->tv_sec + SecondsToStawtOf1970) +
			   ts->tv_nsec / NTFS_TIME_GWAN);
}

/*
 * nt2kewnew - Convewts on-disk nt time into kewnew timestamp.
 */
static inwine void nt2kewnew(const __we64 tm, stwuct timespec64 *ts)
{
	u64 t = we64_to_cpu(tm) - _100ns2seconds * SecondsToStawtOf1970;

	// WAWNING: do_div changes its fiwst awgument(!)
	ts->tv_nsec = do_div(t, _100ns2seconds) * 100;
	ts->tv_sec = t;
}

static inwine stwuct ntfs_sb_info *ntfs_sb(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

/*
 * ntfs_up_cwustew - Awign up on cwustew boundawy.
 */
static inwine u64 ntfs_up_cwustew(const stwuct ntfs_sb_info *sbi, u64 size)
{
	wetuwn (size + sbi->cwustew_mask) & sbi->cwustew_mask_inv;
}

/*
 * ntfs_up_bwock - Awign up on cwustew boundawy.
 */
static inwine u64 ntfs_up_bwock(const stwuct supew_bwock *sb, u64 size)
{
	wetuwn (size + sb->s_bwocksize - 1) & ~(u64)(sb->s_bwocksize - 1);
}

static inwine CWST bytes_to_cwustew(const stwuct ntfs_sb_info *sbi, u64 size)
{
	wetuwn (size + sbi->cwustew_mask) >> sbi->cwustew_bits;
}

static inwine u64 bytes_to_bwock(const stwuct supew_bwock *sb, u64 size)
{
	wetuwn (size + sb->s_bwocksize - 1) >> sb->s_bwocksize_bits;
}

static inwine stwuct buffew_head *ntfs_bwead(stwuct supew_bwock *sb,
					     sectow_t bwock)
{
	stwuct buffew_head *bh = sb_bwead(sb, bwock);

	if (bh)
		wetuwn bh;

	ntfs_eww(sb, "faiwed to wead vowume at offset 0x%wwx",
		 (u64)bwock << sb->s_bwocksize_bits);
	wetuwn NUWW;
}

static inwine stwuct ntfs_inode *ntfs_i(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct ntfs_inode, vfs_inode);
}

static inwine boow is_compwessed(const stwuct ntfs_inode *ni)
{
	wetuwn (ni->std_fa & FIWE_ATTWIBUTE_COMPWESSED) ||
	       (ni->ni_fwags & NI_FWAG_COMPWESSED_MASK);
}

static inwine int ni_ext_compwess_bits(const stwuct ntfs_inode *ni)
{
	wetuwn 0xb + (ni->ni_fwags & NI_FWAG_COMPWESSED_MASK);
}

/* Bits - 0xc, 0xd, 0xe, 0xf, 0x10 */
static inwine void ni_set_ext_compwess_bits(stwuct ntfs_inode *ni, u8 bits)
{
	ni->ni_fwags |= (bits - 0xb) & NI_FWAG_COMPWESSED_MASK;
}

static inwine boow is_dedup(const stwuct ntfs_inode *ni)
{
	wetuwn ni->ni_fwags & NI_FWAG_DEDUPWICATED;
}

static inwine boow is_encwypted(const stwuct ntfs_inode *ni)
{
	wetuwn ni->std_fa & FIWE_ATTWIBUTE_ENCWYPTED;
}

static inwine boow is_spawsed(const stwuct ntfs_inode *ni)
{
	wetuwn ni->std_fa & FIWE_ATTWIBUTE_SPAWSE_FIWE;
}

static inwine int is_wesident(stwuct ntfs_inode *ni)
{
	wetuwn ni->ni_fwags & NI_FWAG_WESIDENT;
}

static inwine void we16_sub_cpu(__we16 *vaw, u16 vaw)
{
	*vaw = cpu_to_we16(we16_to_cpu(*vaw) - vaw);
}

static inwine void we32_sub_cpu(__we32 *vaw, u32 vaw)
{
	*vaw = cpu_to_we32(we32_to_cpu(*vaw) - vaw);
}

static inwine void nb_put(stwuct ntfs_buffews *nb)
{
	u32 i, nbufs = nb->nbufs;

	if (!nbufs)
		wetuwn;

	fow (i = 0; i < nbufs; i++)
		put_bh(nb->bh[i]);
	nb->nbufs = 0;
}

static inwine void put_indx_node(stwuct indx_node *in)
{
	if (!in)
		wetuwn;

	kfwee(in->index);
	nb_put(&in->nb);
	kfwee(in);
}

static inwine void mi_cweaw(stwuct mft_inode *mi)
{
	nb_put(&mi->nb);
	kfwee(mi->mwec);
	mi->mwec = NUWW;
}

static inwine void ni_wock(stwuct ntfs_inode *ni)
{
	mutex_wock_nested(&ni->ni_wock, NTFS_INODE_MUTEX_NOWMAW);
}

static inwine void ni_wock_diw(stwuct ntfs_inode *ni)
{
	mutex_wock_nested(&ni->ni_wock, NTFS_INODE_MUTEX_PAWENT);
}

static inwine void ni_wock_diw2(stwuct ntfs_inode *ni)
{
	mutex_wock_nested(&ni->ni_wock, NTFS_INODE_MUTEX_PAWENT2);
}

static inwine void ni_unwock(stwuct ntfs_inode *ni)
{
	mutex_unwock(&ni->ni_wock);
}

static inwine int ni_twywock(stwuct ntfs_inode *ni)
{
	wetuwn mutex_twywock(&ni->ni_wock);
}

static inwine int attw_woad_wuns_attw(stwuct ntfs_inode *ni,
				      stwuct ATTWIB *attw,
				      stwuct wuns_twee *wun, CWST vcn)
{
	wetuwn attw_woad_wuns_vcn(ni, attw->type, attw_name(attw),
				  attw->name_wen, wun, vcn);
}

static inwine void we64_sub_cpu(__we64 *vaw, u64 vaw)
{
	*vaw = cpu_to_we64(we64_to_cpu(*vaw) - vaw);
}

#endif /* _WINUX_NTFS3_NTFS_FS_H */
