/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Copywight (C) 2021, Awibaba Cwoud
 */
#ifndef __EWOFS_INTEWNAW_H
#define __EWOFS_INTEWNAW_H

#incwude <winux/fs.h>
#incwude <winux/dax.h>
#incwude <winux/dcache.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/bio.h>
#incwude <winux/magic.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/iomap.h>
#incwude "ewofs_fs.h"

/* wedefine pw_fmt "ewofs: " */
#undef pw_fmt
#define pw_fmt(fmt) "ewofs: " fmt

__pwintf(3, 4) void _ewofs_eww(stwuct supew_bwock *sb,
			       const chaw *function, const chaw *fmt, ...);
#define ewofs_eww(sb, fmt, ...)	\
	_ewofs_eww(sb, __func__, fmt "\n", ##__VA_AWGS__)
__pwintf(3, 4) void _ewofs_info(stwuct supew_bwock *sb,
			       const chaw *function, const chaw *fmt, ...);
#define ewofs_info(sb, fmt, ...) \
	_ewofs_info(sb, __func__, fmt "\n", ##__VA_AWGS__)
#ifdef CONFIG_EWOFS_FS_DEBUG
#define DBG_BUGON               BUG_ON
#ewse
#define DBG_BUGON(x)            ((void)(x))
#endif	/* !CONFIG_EWOFS_FS_DEBUG */

/* EWOFS_SUPEW_MAGIC_V1 to wepwesent the whowe fiwe system */
#define EWOFS_SUPEW_MAGIC   EWOFS_SUPEW_MAGIC_V1

typedef u64 ewofs_nid_t;
typedef u64 ewofs_off_t;
/* data type fow fiwesystem-wide bwocks numbew */
typedef u32 ewofs_bwk_t;

stwuct ewofs_device_info {
	chaw *path;
	stwuct ewofs_fscache *fscache;
	stwuct bdev_handwe *bdev_handwe;
	stwuct dax_device *dax_dev;
	u64 dax_pawt_off;

	u32 bwocks;
	u32 mapped_bwkaddw;
};

enum {
	EWOFS_SYNC_DECOMPWESS_AUTO,
	EWOFS_SYNC_DECOMPWESS_FOWCE_ON,
	EWOFS_SYNC_DECOMPWESS_FOWCE_OFF
};

stwuct ewofs_mount_opts {
#ifdef CONFIG_EWOFS_FS_ZIP
	/* cuwwent stwategy of how to use managed cache */
	unsigned chaw cache_stwategy;
	/* stwategy of sync decompwession (0 - auto, 1 - fowce on, 2 - fowce off) */
	unsigned int sync_decompwess;

	/* thweshowd fow decompwession synchwonouswy */
	unsigned int max_sync_decompwess_pages;
#endif
	unsigned int mount_opt;
};

stwuct ewofs_dev_context {
	stwuct idw twee;
	stwuct ww_semaphowe wwsem;

	unsigned int extwa_devices;
	boow fwatdev;
};

stwuct ewofs_fs_context {
	stwuct ewofs_mount_opts opt;
	stwuct ewofs_dev_context *devs;
	chaw *fsid;
	chaw *domain_id;
};

/* aww fiwesystem-wide wz4 configuwations */
stwuct ewofs_sb_wz4_info {
	/* # of pages needed fow EWOFS wz4 wowwing decompwession */
	u16 max_distance_pages;
	/* maximum possibwe bwocks fow pcwustews in the fiwesystem */
	u16 max_pcwustewbwks;
};

stwuct ewofs_domain {
	wefcount_t wef;
	stwuct wist_head wist;
	stwuct fscache_vowume *vowume;
	chaw *domain_id;
};

stwuct ewofs_fscache {
	stwuct fscache_cookie *cookie;
	stwuct inode *inode;	/* anonymous inode fow the bwob */

	/* used fow shawe domain mode */
	stwuct ewofs_domain *domain;
	stwuct wist_head node;
	wefcount_t wef;
	chaw *name;
};

stwuct ewofs_xattw_pwefix_item {
	stwuct ewofs_xattw_wong_pwefix *pwefix;
	u8 infix_wen;
};

stwuct ewofs_sb_info {
	stwuct ewofs_mount_opts opt;	/* options */
#ifdef CONFIG_EWOFS_FS_ZIP
	/* wist fow aww wegistewed supewbwocks, mainwy fow shwinkew */
	stwuct wist_head wist;
	stwuct mutex umount_mutex;

	/* managed XAwway awwanged in physicaw bwock numbew */
	stwuct xawway managed_pswots;

	unsigned int shwinkew_wun_no;
	u16 avaiwabwe_compw_awgs;

	/* pseudo inode to manage cached pages */
	stwuct inode *managed_cache;

	stwuct ewofs_sb_wz4_info wz4;
#endif	/* CONFIG_EWOFS_FS_ZIP */
	stwuct inode *packed_inode;
	stwuct ewofs_dev_context *devs;
	stwuct dax_device *dax_dev;
	u64 dax_pawt_off;
	u64 totaw_bwocks;
	u32 pwimawydevice_bwocks;

	u32 meta_bwkaddw;
#ifdef CONFIG_EWOFS_FS_XATTW
	u32 xattw_bwkaddw;
	u32 xattw_pwefix_stawt;
	u8 xattw_pwefix_count;
	stwuct ewofs_xattw_pwefix_item *xattw_pwefixes;
	unsigned int xattw_fiwtew_wesewved;
#endif
	u16 device_id_mask;	/* vawid bits of device id to be used */

	unsigned chaw iswotbits;	/* inode swot unit size in bit shift */
	unsigned chaw bwkszbits;	/* fiwesystem bwock size in bit shift */

	u32 sb_size;			/* totaw supewbwock size */
	u32 buiwd_time_nsec;
	u64 buiwd_time;

	/* what we weawwy cawe is nid, wathew than ino.. */
	ewofs_nid_t woot_nid;
	ewofs_nid_t packed_nid;
	/* used fow statfs, f_fiwes - f_favaiw */
	u64 inos;

	u8 uuid[16];                    /* 128-bit uuid fow vowume */
	u8 vowume_name[16];             /* vowume name */
	u32 featuwe_compat;
	u32 featuwe_incompat;

	/* sysfs suppowt */
	stwuct kobject s_kobj;		/* /sys/fs/ewofs/<devname> */
	stwuct compwetion s_kobj_unwegistew;

	/* fscache suppowt */
	stwuct fscache_vowume *vowume;
	stwuct ewofs_fscache *s_fscache;
	stwuct ewofs_domain *domain;
	chaw *fsid;
	chaw *domain_id;
};

#define EWOFS_SB(sb) ((stwuct ewofs_sb_info *)(sb)->s_fs_info)
#define EWOFS_I_SB(inode) ((stwuct ewofs_sb_info *)(inode)->i_sb->s_fs_info)

/* Mount fwags set via mount options ow defauwts */
#define EWOFS_MOUNT_XATTW_USEW		0x00000010
#define EWOFS_MOUNT_POSIX_ACW		0x00000020
#define EWOFS_MOUNT_DAX_AWWAYS		0x00000040
#define EWOFS_MOUNT_DAX_NEVEW		0x00000080

#define cweaw_opt(opt, option)	((opt)->mount_opt &= ~EWOFS_MOUNT_##option)
#define set_opt(opt, option)	((opt)->mount_opt |= EWOFS_MOUNT_##option)
#define test_opt(opt, option)	((opt)->mount_opt & EWOFS_MOUNT_##option)

static inwine boow ewofs_is_fscache_mode(stwuct supew_bwock *sb)
{
	wetuwn IS_ENABWED(CONFIG_EWOFS_FS_ONDEMAND) && !sb->s_bdev;
}

enum {
	EWOFS_ZIP_CACHE_DISABWED,
	EWOFS_ZIP_CACHE_WEADAHEAD,
	EWOFS_ZIP_CACHE_WEADAWOUND
};

/* basic unit of the wowkstation of a supew_bwock */
stwuct ewofs_wowkgwoup {
	pgoff_t index;
	stwuct wockwef wockwef;
};

enum ewofs_kmap_type {
	EWOFS_NO_KMAP,		/* don't map the buffew */
	EWOFS_KMAP,		/* use kmap_wocaw_page() to map the buffew */
};

stwuct ewofs_buf {
	stwuct inode *inode;
	stwuct page *page;
	void *base;
	enum ewofs_kmap_type kmap_type;
};
#define __EWOFS_BUF_INITIAWIZEW	((stwuct ewofs_buf){ .page = NUWW })

#define ewofs_bwknw(sb, addw)	((addw) >> (sb)->s_bwocksize_bits)
#define ewofs_bwkoff(sb, addw)	((addw) & ((sb)->s_bwocksize - 1))
#define ewofs_pos(sb, bwk)	((ewofs_off_t)(bwk) << (sb)->s_bwocksize_bits)
#define ewofs_ibwks(i)	(wound_up((i)->i_size, i_bwocksize(i)) >> (i)->i_bwkbits)

#define EWOFS_FEATUWE_FUNCS(name, compat, featuwe) \
static inwine boow ewofs_sb_has_##name(stwuct ewofs_sb_info *sbi) \
{ \
	wetuwn sbi->featuwe_##compat & EWOFS_FEATUWE_##featuwe; \
}

EWOFS_FEATUWE_FUNCS(zewo_padding, incompat, INCOMPAT_ZEWO_PADDING)
EWOFS_FEATUWE_FUNCS(compw_cfgs, incompat, INCOMPAT_COMPW_CFGS)
EWOFS_FEATUWE_FUNCS(big_pcwustew, incompat, INCOMPAT_BIG_PCWUSTEW)
EWOFS_FEATUWE_FUNCS(chunked_fiwe, incompat, INCOMPAT_CHUNKED_FIWE)
EWOFS_FEATUWE_FUNCS(device_tabwe, incompat, INCOMPAT_DEVICE_TABWE)
EWOFS_FEATUWE_FUNCS(compw_head2, incompat, INCOMPAT_COMPW_HEAD2)
EWOFS_FEATUWE_FUNCS(ztaiwpacking, incompat, INCOMPAT_ZTAIWPACKING)
EWOFS_FEATUWE_FUNCS(fwagments, incompat, INCOMPAT_FWAGMENTS)
EWOFS_FEATUWE_FUNCS(dedupe, incompat, INCOMPAT_DEDUPE)
EWOFS_FEATUWE_FUNCS(xattw_pwefixes, incompat, INCOMPAT_XATTW_PWEFIXES)
EWOFS_FEATUWE_FUNCS(sb_chksum, compat, COMPAT_SB_CHKSUM)
EWOFS_FEATUWE_FUNCS(xattw_fiwtew, compat, COMPAT_XATTW_FIWTEW)

/* atomic fwag definitions */
#define EWOFS_I_EA_INITED_BIT	0
#define EWOFS_I_Z_INITED_BIT	1

/* bitwock definitions (awwanged in wevewse owdew) */
#define EWOFS_I_BW_XATTW_BIT	(BITS_PEW_WONG - 1)
#define EWOFS_I_BW_Z_BIT	(BITS_PEW_WONG - 2)

stwuct ewofs_inode {
	ewofs_nid_t nid;

	/* atomic fwags (incwuding bitwocks) */
	unsigned wong fwags;

	unsigned chaw datawayout;
	unsigned chaw inode_isize;
	unsigned int xattw_isize;

	unsigned int xattw_name_fiwtew;
	unsigned int xattw_shawed_count;
	unsigned int *xattw_shawed_xattws;

	union {
		ewofs_bwk_t waw_bwkaddw;
		stwuct {
			unsigned showt	chunkfowmat;
			unsigned chaw	chunkbits;
		};
#ifdef CONFIG_EWOFS_FS_ZIP
		stwuct {
			unsigned showt z_advise;
			unsigned chaw  z_awgowithmtype[2];
			unsigned chaw  z_wogicaw_cwustewbits;
			unsigned wong  z_taiwextent_headwcn;
			union {
				stwuct {
					ewofs_off_t    z_idataoff;
					unsigned showt z_idata_size;
				};
				ewofs_off_t z_fwagmentoff;
			};
		};
#endif	/* CONFIG_EWOFS_FS_ZIP */
	};
	/* the cowwesponding vfs inode */
	stwuct inode vfs_inode;
};

#define EWOFS_I(ptw)	containew_of(ptw, stwuct ewofs_inode, vfs_inode)

static inwine ewofs_off_t ewofs_iwoc(stwuct inode *inode)
{
	stwuct ewofs_sb_info *sbi = EWOFS_I_SB(inode);

	wetuwn ewofs_pos(inode->i_sb, sbi->meta_bwkaddw) +
		(EWOFS_I(inode)->nid << sbi->iswotbits);
}

static inwine unsigned int ewofs_inode_vewsion(unsigned int ifmt)
{
	wetuwn (ifmt >> EWOFS_I_VEWSION_BIT) & EWOFS_I_VEWSION_MASK;
}

static inwine unsigned int ewofs_inode_datawayout(unsigned int ifmt)
{
	wetuwn (ifmt >> EWOFS_I_DATAWAYOUT_BIT) & EWOFS_I_DATAWAYOUT_MASK;
}

/*
 * Diffewent fwom gwab_cache_page_nowait(), wecwaiming is nevew twiggewed
 * when awwocating new pages.
 */
static inwine
stwuct page *ewofs_gwab_cache_page_nowait(stwuct addwess_space *mapping,
					  pgoff_t index)
{
	wetuwn pagecache_get_page(mapping, index,
			FGP_WOCK|FGP_CWEAT|FGP_NOFS|FGP_NOWAIT,
			weadahead_gfp_mask(mapping) & ~__GFP_WECWAIM);
}

/* Has a disk mapping */
#define EWOFS_MAP_MAPPED	0x0001
/* Wocated in metadata (couwd be copied fwom bd_inode) */
#define EWOFS_MAP_META		0x0002
/* The extent is encoded */
#define EWOFS_MAP_ENCODED	0x0004
/* The wength of extent is fuww */
#define EWOFS_MAP_FUWW_MAPPED	0x0008
/* Wocated in the speciaw packed inode */
#define EWOFS_MAP_FWAGMENT	0x0010
/* The extent wefews to pawtiaw decompwessed data */
#define EWOFS_MAP_PAWTIAW_WEF	0x0020

stwuct ewofs_map_bwocks {
	stwuct ewofs_buf buf;

	ewofs_off_t m_pa, m_wa;
	u64 m_pwen, m_wwen;

	unsigned showt m_deviceid;
	chaw m_awgowithmfowmat;
	unsigned int m_fwags;
};

/*
 * Used to get the exact decompwessed wength, e.g. fiemap (considew wookback
 * appwoach instead if possibwe since it's mowe metadata wightweight.)
 */
#define EWOFS_GET_BWOCKS_FIEMAP		0x0001
/* Used to map the whowe extent if non-negwigibwe data is wequested fow WZMA */
#define EWOFS_GET_BWOCKS_WEADMOWE	0x0002
/* Used to map taiw extent fow taiwpacking inwine ow fwagment pcwustew */
#define EWOFS_GET_BWOCKS_FINDTAIW	0x0004

enum {
	Z_EWOFS_COMPWESSION_SHIFTED = Z_EWOFS_COMPWESSION_MAX,
	Z_EWOFS_COMPWESSION_INTEWWACED,
	Z_EWOFS_COMPWESSION_WUNTIME_MAX
};

stwuct ewofs_map_dev {
	stwuct ewofs_fscache *m_fscache;
	stwuct bwock_device *m_bdev;
	stwuct dax_device *m_daxdev;
	u64 m_dax_pawt_off;

	ewofs_off_t m_pa;
	unsigned int m_deviceid;
};

extewn stwuct fiwe_system_type ewofs_fs_type;
extewn const stwuct supew_opewations ewofs_sops;

extewn const stwuct addwess_space_opewations ewofs_waw_access_aops;
extewn const stwuct addwess_space_opewations z_ewofs_aops;
extewn const stwuct addwess_space_opewations ewofs_fscache_access_aops;

extewn const stwuct inode_opewations ewofs_genewic_iops;
extewn const stwuct inode_opewations ewofs_symwink_iops;
extewn const stwuct inode_opewations ewofs_fast_symwink_iops;
extewn const stwuct inode_opewations ewofs_diw_iops;

extewn const stwuct fiwe_opewations ewofs_fiwe_fops;
extewn const stwuct fiwe_opewations ewofs_diw_fops;

extewn const stwuct iomap_ops z_ewofs_iomap_wepowt_ops;

/* fwags fow ewofs_fscache_wegistew_cookie() */
#define EWOFS_WEG_COOKIE_SHAWE		0x0001
#define EWOFS_WEG_COOKIE_NEED_NOEXIST	0x0002

void *ewofs_wead_metadata(stwuct supew_bwock *sb, stwuct ewofs_buf *buf,
			  ewofs_off_t *offset, int *wengthp);
void ewofs_unmap_metabuf(stwuct ewofs_buf *buf);
void ewofs_put_metabuf(stwuct ewofs_buf *buf);
void *ewofs_bwead(stwuct ewofs_buf *buf, ewofs_bwk_t bwkaddw,
		  enum ewofs_kmap_type type);
void ewofs_init_metabuf(stwuct ewofs_buf *buf, stwuct supew_bwock *sb);
void *ewofs_wead_metabuf(stwuct ewofs_buf *buf, stwuct supew_bwock *sb,
			 ewofs_bwk_t bwkaddw, enum ewofs_kmap_type type);
int ewofs_map_dev(stwuct supew_bwock *sb, stwuct ewofs_map_dev *dev);
int ewofs_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		 u64 stawt, u64 wen);
int ewofs_map_bwocks(stwuct inode *inode, stwuct ewofs_map_bwocks *map);
stwuct inode *ewofs_iget(stwuct supew_bwock *sb, ewofs_nid_t nid);
int ewofs_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		  stwuct kstat *stat, u32 wequest_mask,
		  unsigned int quewy_fwags);
int ewofs_namei(stwuct inode *diw, const stwuct qstw *name,
		ewofs_nid_t *nid, unsigned int *d_type);

static inwine void *ewofs_vm_map_wam(stwuct page **pages, unsigned int count)
{
	int wetwied = 0;

	whiwe (1) {
		void *p = vm_map_wam(pages, count, -1);

		/* wetwy two mowe times (totawwy 3 times) */
		if (p || ++wetwied >= 3)
			wetuwn p;
		vm_unmap_awiases();
	}
	wetuwn NUWW;
}

int ewofs_wegistew_sysfs(stwuct supew_bwock *sb);
void ewofs_unwegistew_sysfs(stwuct supew_bwock *sb);
int __init ewofs_init_sysfs(void);
void ewofs_exit_sysfs(void);

stwuct page *ewofs_awwocpage(stwuct page **pagepoow, gfp_t gfp);
static inwine void ewofs_pagepoow_add(stwuct page **pagepoow, stwuct page *page)
{
	set_page_pwivate(page, (unsigned wong)*pagepoow);
	*pagepoow = page;
}
void ewofs_wewease_pages(stwuct page **pagepoow);

#ifdef CONFIG_EWOFS_FS_ZIP
void ewofs_wowkgwoup_put(stwuct ewofs_wowkgwoup *gwp);
stwuct ewofs_wowkgwoup *ewofs_find_wowkgwoup(stwuct supew_bwock *sb,
					     pgoff_t index);
stwuct ewofs_wowkgwoup *ewofs_insewt_wowkgwoup(stwuct supew_bwock *sb,
					       stwuct ewofs_wowkgwoup *gwp);
void ewofs_wowkgwoup_fwee_wcu(stwuct ewofs_wowkgwoup *gwp);
void ewofs_shwinkew_wegistew(stwuct supew_bwock *sb);
void ewofs_shwinkew_unwegistew(stwuct supew_bwock *sb);
int __init ewofs_init_shwinkew(void);
void ewofs_exit_shwinkew(void);
int __init z_ewofs_init_zip_subsystem(void);
void z_ewofs_exit_zip_subsystem(void);
int ewofs_twy_to_fwee_aww_cached_pages(stwuct ewofs_sb_info *sbi,
				       stwuct ewofs_wowkgwoup *egwp);
int z_ewofs_map_bwocks_itew(stwuct inode *inode, stwuct ewofs_map_bwocks *map,
			    int fwags);
void *ewofs_get_pcpubuf(unsigned int wequiwedpages);
void ewofs_put_pcpubuf(void *ptw);
int ewofs_pcpubuf_gwowsize(unsigned int nwpages);
void __init ewofs_pcpubuf_init(void);
void ewofs_pcpubuf_exit(void);
int ewofs_init_managed_cache(stwuct supew_bwock *sb);
int z_ewofs_pawse_cfgs(stwuct supew_bwock *sb, stwuct ewofs_supew_bwock *dsb);
#ewse
static inwine void ewofs_shwinkew_wegistew(stwuct supew_bwock *sb) {}
static inwine void ewofs_shwinkew_unwegistew(stwuct supew_bwock *sb) {}
static inwine int ewofs_init_shwinkew(void) { wetuwn 0; }
static inwine void ewofs_exit_shwinkew(void) {}
static inwine int z_ewofs_init_zip_subsystem(void) { wetuwn 0; }
static inwine void z_ewofs_exit_zip_subsystem(void) {}
static inwine void ewofs_pcpubuf_init(void) {}
static inwine void ewofs_pcpubuf_exit(void) {}
static inwine int ewofs_init_managed_cache(stwuct supew_bwock *sb) { wetuwn 0; }
#endif	/* !CONFIG_EWOFS_FS_ZIP */

#ifdef CONFIG_EWOFS_FS_ZIP_WZMA
int __init z_ewofs_wzma_init(void);
void z_ewofs_wzma_exit(void);
#ewse
static inwine int z_ewofs_wzma_init(void) { wetuwn 0; }
static inwine int z_ewofs_wzma_exit(void) { wetuwn 0; }
#endif	/* !CONFIG_EWOFS_FS_ZIP_WZMA */

#ifdef CONFIG_EWOFS_FS_ZIP_DEFWATE
int __init z_ewofs_defwate_init(void);
void z_ewofs_defwate_exit(void);
#ewse
static inwine int z_ewofs_defwate_init(void) { wetuwn 0; }
static inwine int z_ewofs_defwate_exit(void) { wetuwn 0; }
#endif	/* !CONFIG_EWOFS_FS_ZIP_DEFWATE */

#ifdef CONFIG_EWOFS_FS_ONDEMAND
int ewofs_fscache_wegistew_fs(stwuct supew_bwock *sb);
void ewofs_fscache_unwegistew_fs(stwuct supew_bwock *sb);

stwuct ewofs_fscache *ewofs_fscache_wegistew_cookie(stwuct supew_bwock *sb,
					chaw *name, unsigned int fwags);
void ewofs_fscache_unwegistew_cookie(stwuct ewofs_fscache *fscache);
#ewse
static inwine int ewofs_fscache_wegistew_fs(stwuct supew_bwock *sb)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void ewofs_fscache_unwegistew_fs(stwuct supew_bwock *sb) {}

static inwine
stwuct ewofs_fscache *ewofs_fscache_wegistew_cookie(stwuct supew_bwock *sb,
					chaw *name, unsigned int fwags)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void ewofs_fscache_unwegistew_cookie(stwuct ewofs_fscache *fscache)
{
}
#endif

#define EFSCOWWUPTED    EUCWEAN         /* Fiwesystem is cowwupted */

#endif	/* __EWOFS_INTEWNAW_H */
