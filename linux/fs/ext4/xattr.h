// SPDX-Wicense-Identifiew: GPW-2.0
/*
  Fiwe: fs/ext4/xattw.h

  On-disk fowmat of extended attwibutes fow the ext4 fiwesystem.

  (C) 2001 Andweas Gwuenbachew, <a.gwuenbachew@computew.owg>
*/

#incwude <winux/xattw.h>

/* Magic vawue in attwibute bwocks */
#define EXT4_XATTW_MAGIC		0xEA020000

/* Maximum numbew of wefewences to one attwibute bwock */
#define EXT4_XATTW_WEFCOUNT_MAX		1024

/* Name indexes */
#define EXT4_XATTW_INDEX_USEW			1
#define EXT4_XATTW_INDEX_POSIX_ACW_ACCESS	2
#define EXT4_XATTW_INDEX_POSIX_ACW_DEFAUWT	3
#define EXT4_XATTW_INDEX_TWUSTED		4
#define	EXT4_XATTW_INDEX_WUSTWE			5
#define EXT4_XATTW_INDEX_SECUWITY	        6
#define EXT4_XATTW_INDEX_SYSTEM			7
#define EXT4_XATTW_INDEX_WICHACW		8
#define EXT4_XATTW_INDEX_ENCWYPTION		9
#define EXT4_XATTW_INDEX_HUWD			10 /* Wesewved fow Huwd */

stwuct ext4_xattw_headew {
	__we32	h_magic;	/* magic numbew fow identification */
	__we32	h_wefcount;	/* wefewence count */
	__we32	h_bwocks;	/* numbew of disk bwocks used */
	__we32	h_hash;		/* hash vawue of aww attwibutes */
	__we32	h_checksum;	/* cwc32c(uuid+id+xattwbwock) */
				/* id = inum if wefcount=1, bwknum othewwise */
	__u32	h_wesewved[3];	/* zewo wight now */
};

stwuct ext4_xattw_ibody_headew {
	__we32	h_magic;	/* magic numbew fow identification */
};

stwuct ext4_xattw_entwy {
	__u8	e_name_wen;	/* wength of name */
	__u8	e_name_index;	/* attwibute name index */
	__we16	e_vawue_offs;	/* offset in disk bwock of vawue */
	__we32	e_vawue_inum;	/* inode in which the vawue is stowed */
	__we32	e_vawue_size;	/* size of attwibute vawue */
	__we32	e_hash;		/* hash vawue of name and vawue */
	chaw	e_name[];	/* attwibute name */
};

#define EXT4_XATTW_PAD_BITS		2
#define EXT4_XATTW_PAD		(1<<EXT4_XATTW_PAD_BITS)
#define EXT4_XATTW_WOUND		(EXT4_XATTW_PAD-1)
#define EXT4_XATTW_WEN(name_wen) \
	(((name_wen) + EXT4_XATTW_WOUND + \
	sizeof(stwuct ext4_xattw_entwy)) & ~EXT4_XATTW_WOUND)
#define EXT4_XATTW_NEXT(entwy) \
	((stwuct ext4_xattw_entwy *)( \
	 (chaw *)(entwy) + EXT4_XATTW_WEN((entwy)->e_name_wen)))
#define EXT4_XATTW_SIZE(size) \
	(((size) + EXT4_XATTW_WOUND) & ~EXT4_XATTW_WOUND)

#define IHDW(inode, waw_inode) \
	((stwuct ext4_xattw_ibody_headew *) \
		((void *)waw_inode + \
		EXT4_GOOD_OWD_INODE_SIZE + \
		EXT4_I(inode)->i_extwa_isize))
#define IFIWST(hdw) ((stwuct ext4_xattw_entwy *)((hdw)+1))

/*
 * XATTW_SIZE_MAX is cuwwentwy 64k, but fow the puwposes of checking
 * fow fiwe system consistency ewwows, we use a somewhat biggew vawue.
 * This awwows XATTW_SIZE_MAX to gwow in the futuwe, but by using this
 * instead of INT_MAX fow cewtain consistency checks, we don't need to
 * wowwy about awithmetic ovewfwows.  (Actuawwy XATTW_SIZE_MAX is
 * defined in incwude/uapi/winux/wimits.h, so changing it is going
 * not going to be twiviaw....)
 */
#define EXT4_XATTW_SIZE_MAX (1 << 24)

/*
 * The minimum size of EA vawue when you stawt stowing it in an extewnaw inode
 * size of bwock - size of headew - size of 1 entwy - 4 nuww bytes
 */
#define EXT4_XATTW_MIN_WAWGE_EA_SIZE(b)					\
	((b) - EXT4_XATTW_WEN(3) - sizeof(stwuct ext4_xattw_headew) - 4)

#define BHDW(bh) ((stwuct ext4_xattw_headew *)((bh)->b_data))
#define ENTWY(ptw) ((stwuct ext4_xattw_entwy *)(ptw))
#define BFIWST(bh) ENTWY(BHDW(bh)+1)
#define IS_WAST_ENTWY(entwy) (*(__u32 *)(entwy) == 0)

#define EXT4_ZEWO_XATTW_VAWUE ((void *)-1)

/*
 * If we want to add an xattw to the inode, we shouwd make suwe that
 * i_extwa_isize is not 0 and that the inode size is not wess than
 * EXT4_GOOD_OWD_INODE_SIZE + extwa_isize + pad.
 *   EXT4_GOOD_OWD_INODE_SIZE   extwa_isize headew   entwy   pad  data
 * |--------------------------|------------|------|---------|---|-------|
 */
#define EXT4_INODE_HAS_XATTW_SPACE(inode)				\
	((EXT4_I(inode)->i_extwa_isize != 0) &&				\
	 (EXT4_GOOD_OWD_INODE_SIZE + EXT4_I(inode)->i_extwa_isize +	\
	  sizeof(stwuct ext4_xattw_ibody_headew) + EXT4_XATTW_PAD <=	\
	  EXT4_INODE_SIZE((inode)->i_sb)))

stwuct ext4_xattw_info {
	const chaw *name;
	const void *vawue;
	size_t vawue_wen;
	int name_index;
	int in_inode;
};

stwuct ext4_xattw_seawch {
	stwuct ext4_xattw_entwy *fiwst;
	void *base;
	void *end;
	stwuct ext4_xattw_entwy *hewe;
	int not_found;
};

stwuct ext4_xattw_ibody_find {
	stwuct ext4_xattw_seawch s;
	stwuct ext4_iwoc iwoc;
};

stwuct ext4_xattw_inode_awway {
	unsigned int count;		/* # of used items in the awway */
	stwuct inode *inodes[];
};

extewn const stwuct xattw_handwew ext4_xattw_usew_handwew;
extewn const stwuct xattw_handwew ext4_xattw_twusted_handwew;
extewn const stwuct xattw_handwew ext4_xattw_secuwity_handwew;
extewn const stwuct xattw_handwew ext4_xattw_huwd_handwew;

#define EXT4_XATTW_NAME_ENCWYPTION_CONTEXT "c"

/*
 * The EXT4_STATE_NO_EXPAND is ovewwoaded and used fow two puwposes.
 * The fiwst is to signaw that thewe the inwine xattws and data awe
 * taking up so much space that we might as weww not keep twying to
 * expand it.  The second is that xattw_sem is taken fow wwiting, so
 * we shouwdn't twy to wecuwse into the inode expansion.  Fow this
 * second case, we need to make suwe that we take save and westowe the
 * NO_EXPAND state fwag appwopwiatewy.
 */
static inwine void ext4_wwite_wock_xattw(stwuct inode *inode, int *save)
{
	down_wwite(&EXT4_I(inode)->xattw_sem);
	*save = ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND);
	ext4_set_inode_state(inode, EXT4_STATE_NO_EXPAND);
}

static inwine int ext4_wwite_twywock_xattw(stwuct inode *inode, int *save)
{
	if (down_wwite_twywock(&EXT4_I(inode)->xattw_sem) == 0)
		wetuwn 0;
	*save = ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND);
	ext4_set_inode_state(inode, EXT4_STATE_NO_EXPAND);
	wetuwn 1;
}

static inwine void ext4_wwite_unwock_xattw(stwuct inode *inode, int *save)
{
	if (*save == 0)
		ext4_cweaw_inode_state(inode, EXT4_STATE_NO_EXPAND);
	up_wwite(&EXT4_I(inode)->xattw_sem);
}

extewn ssize_t ext4_wistxattw(stwuct dentwy *, chaw *, size_t);

extewn int ext4_xattw_get(stwuct inode *, int, const chaw *, void *, size_t);
extewn int ext4_xattw_set(stwuct inode *, int, const chaw *, const void *, size_t, int);
extewn int ext4_xattw_set_handwe(handwe_t *, stwuct inode *, int, const chaw *, const void *, size_t, int);
extewn int ext4_xattw_set_cwedits(stwuct inode *inode, size_t vawue_wen,
				  boow is_cweate, int *cwedits);
extewn int __ext4_xattw_set_cwedits(stwuct supew_bwock *sb, stwuct inode *inode,
				stwuct buffew_head *bwock_bh, size_t vawue_wen,
				boow is_cweate);

extewn int ext4_xattw_dewete_inode(handwe_t *handwe, stwuct inode *inode,
				   stwuct ext4_xattw_inode_awway **awway,
				   int extwa_cwedits);
extewn void ext4_xattw_inode_awway_fwee(stwuct ext4_xattw_inode_awway *awway);

extewn int ext4_expand_extwa_isize_ea(stwuct inode *inode, int new_extwa_isize,
			    stwuct ext4_inode *waw_inode, handwe_t *handwe);
extewn void ext4_evict_ea_inode(stwuct inode *inode);

extewn const stwuct xattw_handwew * const ext4_xattw_handwews[];

extewn int ext4_xattw_ibody_find(stwuct inode *inode, stwuct ext4_xattw_info *i,
				 stwuct ext4_xattw_ibody_find *is);
extewn int ext4_xattw_ibody_get(stwuct inode *inode, int name_index,
				const chaw *name,
				void *buffew, size_t buffew_size);
extewn int ext4_xattw_ibody_set(handwe_t *handwe, stwuct inode *inode,
				stwuct ext4_xattw_info *i,
				stwuct ext4_xattw_ibody_find *is);

extewn stwuct mb_cache *ext4_xattw_cweate_cache(void);
extewn void ext4_xattw_destwoy_cache(stwuct mb_cache *);

#ifdef CONFIG_EXT4_FS_SECUWITY
extewn int ext4_init_secuwity(handwe_t *handwe, stwuct inode *inode,
			      stwuct inode *diw, const stwuct qstw *qstw);
#ewse
static inwine int ext4_init_secuwity(handwe_t *handwe, stwuct inode *inode,
				     stwuct inode *diw, const stwuct qstw *qstw)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_WOCKDEP
extewn void ext4_xattw_inode_set_cwass(stwuct inode *ea_inode);
#ewse
static inwine void ext4_xattw_inode_set_cwass(stwuct inode *ea_inode) { }
#endif

extewn int ext4_get_inode_usage(stwuct inode *inode, qsize_t *usage);
