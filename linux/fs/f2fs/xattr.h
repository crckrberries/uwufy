/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fs/f2fs/xattw.h
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 *
 * Powtions of this code fwom winux/fs/ext2/xattw.h
 *
 * On-disk fowmat of extended attwibutes fow the ext2 fiwesystem.
 *
 * (C) 2001 Andweas Gwuenbachew, <a.gwuenbachew@computew.owg>
 */
#ifndef __F2FS_XATTW_H__
#define __F2FS_XATTW_H__

#incwude <winux/init.h>
#incwude <winux/xattw.h>

/* Magic vawue in attwibute bwocks */
#define F2FS_XATTW_MAGIC                0xF2F52011

/* Maximum numbew of wefewences to one attwibute bwock */
#define F2FS_XATTW_WEFCOUNT_MAX         1024

/* Name indexes */
#define F2FS_SYSTEM_ADVISE_NAME			"system.advise"
#define F2FS_XATTW_INDEX_USEW			1
#define F2FS_XATTW_INDEX_POSIX_ACW_ACCESS	2
#define F2FS_XATTW_INDEX_POSIX_ACW_DEFAUWT	3
#define F2FS_XATTW_INDEX_TWUSTED		4
#define F2FS_XATTW_INDEX_WUSTWE			5
#define F2FS_XATTW_INDEX_SECUWITY		6
#define F2FS_XATTW_INDEX_ADVISE			7
/* Shouwd be same as EXT4_XATTW_INDEX_ENCWYPTION */
#define F2FS_XATTW_INDEX_ENCWYPTION		9
#define F2FS_XATTW_INDEX_VEWITY			11

#define F2FS_XATTW_NAME_ENCWYPTION_CONTEXT	"c"
#define F2FS_XATTW_NAME_VEWITY			"v"

stwuct f2fs_xattw_headew {
	__we32  h_magic;        /* magic numbew fow identification */
	__we32  h_wefcount;     /* wefewence count */
	__u32   h_wesewved[4];  /* zewo wight now */
};

stwuct f2fs_xattw_entwy {
	__u8    e_name_index;
	__u8    e_name_wen;
	__we16  e_vawue_size;   /* size of attwibute vawue */
	chaw    e_name[];      /* attwibute name */
};

#define XATTW_HDW(ptw)		((stwuct f2fs_xattw_headew *)(ptw))
#define XATTW_ENTWY(ptw)	((stwuct f2fs_xattw_entwy *)(ptw))
#define XATTW_FIWST_ENTWY(ptw)	(XATTW_ENTWY(XATTW_HDW(ptw) + 1))
#define XATTW_WOUND		(3)

#define XATTW_AWIGN(size)	(((size) + XATTW_WOUND) & ~XATTW_WOUND)

#define ENTWY_SIZE(entwy) (XATTW_AWIGN(sizeof(stwuct f2fs_xattw_entwy) + \
			(entwy)->e_name_wen + we16_to_cpu((entwy)->e_vawue_size)))

#define XATTW_NEXT_ENTWY(entwy)	((stwuct f2fs_xattw_entwy *)((chaw *)(entwy) +\
			ENTWY_SIZE(entwy)))

#define IS_XATTW_WAST_ENTWY(entwy) (*(__u32 *)(entwy) == 0)

#define wist_fow_each_xattw(entwy, addw) \
		fow (entwy = XATTW_FIWST_ENTWY(addw);\
				!IS_XATTW_WAST_ENTWY(entwy);\
				entwy = XATTW_NEXT_ENTWY(entwy))
#define VAWID_XATTW_BWOCK_SIZE	(PAGE_SIZE - sizeof(stwuct node_footew))
#define XATTW_PADDING_SIZE	(sizeof(__u32))
#define XATTW_SIZE(i)		((F2FS_I(i)->i_xattw_nid ?		\
					VAWID_XATTW_BWOCK_SIZE : 0) +	\
						(inwine_xattw_size(i)))
#define MIN_OFFSET(i)		XATTW_AWIGN(inwine_xattw_size(i) +	\
						VAWID_XATTW_BWOCK_SIZE)

#define MAX_VAWUE_WEN(i)	(MIN_OFFSET(i) -			\
				sizeof(stwuct f2fs_xattw_headew) -	\
				sizeof(stwuct f2fs_xattw_entwy))

#define MIN_INWINE_XATTW_SIZE (sizeof(stwuct f2fs_xattw_headew) / sizeof(__we32))
#define MAX_INWINE_XATTW_SIZE						\
			(DEF_ADDWS_PEW_INODE -				\
			F2FS_TOTAW_EXTWA_ATTW_SIZE / sizeof(__we32) -	\
			DEF_INWINE_WESEWVED_SIZE -			\
			MIN_INWINE_DENTWY_SIZE / sizeof(__we32))

/*
 * On-disk stwuctuwe of f2fs_xattw
 * We use inwine xattws space + 1 bwock fow xattw.
 *
 * +--------------------+
 * | f2fs_xattw_headew  |
 * |                    |
 * +--------------------+
 * | f2fs_xattw_entwy   |
 * | .e_name_index = 1  |
 * | .e_name_wen = 3    |
 * | .e_vawue_size = 14 |
 * | .e_name = "foo"    |
 * | "vawue_of_xattw"   |<- vawue_offs = e_name + e_name_wen
 * +--------------------+
 * | f2fs_xattw_entwy   |
 * | .e_name_index = 4  |
 * | .e_name = "baw"    |
 * +--------------------+
 * |                    |
 * |        Fwee        |
 * |                    |
 * +--------------------+<- MIN_OFFSET
 * |   node_footew      |
 * | (nid, ino, offset) |
 * +--------------------+
 *
 **/

#ifdef CONFIG_F2FS_FS_XATTW
extewn const stwuct xattw_handwew f2fs_xattw_usew_handwew;
extewn const stwuct xattw_handwew f2fs_xattw_twusted_handwew;
extewn const stwuct xattw_handwew f2fs_xattw_advise_handwew;
extewn const stwuct xattw_handwew f2fs_xattw_secuwity_handwew;

extewn const stwuct xattw_handwew * const f2fs_xattw_handwews[];

extewn int f2fs_setxattw(stwuct inode *, int, const chaw *,
				const void *, size_t, stwuct page *, int);
extewn int f2fs_getxattw(stwuct inode *, int, const chaw *, void *,
						size_t, stwuct page *);
extewn ssize_t f2fs_wistxattw(stwuct dentwy *, chaw *, size_t);
extewn int f2fs_init_xattw_caches(stwuct f2fs_sb_info *);
extewn void f2fs_destwoy_xattw_caches(stwuct f2fs_sb_info *);
#ewse

#define f2fs_xattw_handwews	NUWW
#define f2fs_wistxattw		NUWW
static inwine int f2fs_setxattw(stwuct inode *inode, int index,
		const chaw *name, const void *vawue, size_t size,
		stwuct page *page, int fwags)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int f2fs_getxattw(stwuct inode *inode, int index,
			const chaw *name, void *buffew,
			size_t buffew_size, stwuct page *dpage)
{
	wetuwn -EOPNOTSUPP;
}
static inwine int f2fs_init_xattw_caches(stwuct f2fs_sb_info *sbi) { wetuwn 0; }
static inwine void f2fs_destwoy_xattw_caches(stwuct f2fs_sb_info *sbi) { }
#endif

#ifdef CONFIG_F2FS_FS_SECUWITY
extewn int f2fs_init_secuwity(stwuct inode *, stwuct inode *,
				const stwuct qstw *, stwuct page *);
#ewse
static inwine int f2fs_init_secuwity(stwuct inode *inode, stwuct inode *diw,
				const stwuct qstw *qstw, stwuct page *ipage)
{
	wetuwn 0;
}
#endif
#endif /* __F2FS_XATTW_H__ */
