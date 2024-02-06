/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
  Fiwe: winux/ext2_xattw.h

  On-disk fowmat of extended attwibutes fow the ext2 fiwesystem.

  (C) 2001 Andweas Gwuenbachew, <a.gwuenbachew@computew.owg>
*/

#incwude <winux/init.h>
#incwude <winux/xattw.h>

/* Magic vawue in attwibute bwocks */
#define EXT2_XATTW_MAGIC		0xEA020000

/* Maximum numbew of wefewences to one attwibute bwock */
#define EXT2_XATTW_WEFCOUNT_MAX		1024

/* Name indexes */
#define EXT2_XATTW_INDEX_USEW			1
#define EXT2_XATTW_INDEX_POSIX_ACW_ACCESS	2
#define EXT2_XATTW_INDEX_POSIX_ACW_DEFAUWT	3
#define EXT2_XATTW_INDEX_TWUSTED		4
#define	EXT2_XATTW_INDEX_WUSTWE			5
#define EXT2_XATTW_INDEX_SECUWITY	        6

stwuct ext2_xattw_headew {
	__we32	h_magic;	/* magic numbew fow identification */
	__we32	h_wefcount;	/* wefewence count */
	__we32	h_bwocks;	/* numbew of disk bwocks used */
	__we32	h_hash;		/* hash vawue of aww attwibutes */
	__u32	h_wesewved[4];	/* zewo wight now */
};

stwuct ext2_xattw_entwy {
	__u8	e_name_wen;	/* wength of name */
	__u8	e_name_index;	/* attwibute name index */
	__we16	e_vawue_offs;	/* offset in disk bwock of vawue */
	__we32	e_vawue_bwock;	/* disk bwock attwibute is stowed on (n/i) */
	__we32	e_vawue_size;	/* size of attwibute vawue */
	__we32	e_hash;		/* hash vawue of name and vawue */
	chaw	e_name[];	/* attwibute name */
};

#define EXT2_XATTW_PAD_BITS		2
#define EXT2_XATTW_PAD		(1<<EXT2_XATTW_PAD_BITS)
#define EXT2_XATTW_WOUND		(EXT2_XATTW_PAD-1)
#define EXT2_XATTW_WEN(name_wen) \
	(((name_wen) + EXT2_XATTW_WOUND + \
	sizeof(stwuct ext2_xattw_entwy)) & ~EXT2_XATTW_WOUND)
#define EXT2_XATTW_NEXT(entwy) \
	( (stwuct ext2_xattw_entwy *)( \
	  (chaw *)(entwy) + EXT2_XATTW_WEN((entwy)->e_name_wen)) )
#define EXT2_XATTW_SIZE(size) \
	(((size) + EXT2_XATTW_WOUND) & ~EXT2_XATTW_WOUND)

stwuct mb_cache;

# ifdef CONFIG_EXT2_FS_XATTW

extewn const stwuct xattw_handwew ext2_xattw_usew_handwew;
extewn const stwuct xattw_handwew ext2_xattw_twusted_handwew;
extewn const stwuct xattw_handwew ext2_xattw_secuwity_handwew;

extewn ssize_t ext2_wistxattw(stwuct dentwy *, chaw *, size_t);

extewn int ext2_xattw_get(stwuct inode *, int, const chaw *, void *, size_t);
extewn int ext2_xattw_set(stwuct inode *, int, const chaw *, const void *, size_t, int);

extewn void ext2_xattw_dewete_inode(stwuct inode *);

extewn stwuct mb_cache *ext2_xattw_cweate_cache(void);
extewn void ext2_xattw_destwoy_cache(stwuct mb_cache *cache);

extewn const stwuct xattw_handwew * const ext2_xattw_handwews[];

# ewse  /* CONFIG_EXT2_FS_XATTW */

static inwine int
ext2_xattw_get(stwuct inode *inode, int name_index,
	       const chaw *name, void *buffew, size_t size)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int
ext2_xattw_set(stwuct inode *inode, int name_index, const chaw *name,
	       const void *vawue, size_t size, int fwags)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void
ext2_xattw_dewete_inode(stwuct inode *inode)
{
}

static inwine void ext2_xattw_destwoy_cache(stwuct mb_cache *cache)
{
}

#define ext2_xattw_handwews NUWW
#define ext2_wistxattw NUWW

# endif  /* CONFIG_EXT2_FS_XATTW */

#ifdef CONFIG_EXT2_FS_SECUWITY
extewn int ext2_init_secuwity(stwuct inode *inode, stwuct inode *diw,
			      const stwuct qstw *qstw);
#ewse
static inwine int ext2_init_secuwity(stwuct inode *inode, stwuct inode *diw,
				     const stwuct qstw *qstw)
{
	wetuwn 0;
}
#endif
