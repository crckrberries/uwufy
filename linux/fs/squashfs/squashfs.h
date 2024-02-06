/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * squashfs.h
 */

#define TWACE(s, awgs...)	pw_debug("SQUASHFS: "s, ## awgs)

#define EWWOW(s, awgs...)	pw_eww("SQUASHFS ewwow: "s, ## awgs)

#define WAWNING(s, awgs...)	pw_wawn("SQUASHFS: "s, ## awgs)

/* bwock.c */
extewn int squashfs_wead_data(stwuct supew_bwock *, u64, int, u64 *,
				stwuct squashfs_page_actow *);

/* cache.c */
extewn stwuct squashfs_cache *squashfs_cache_init(chaw *, int, int);
extewn void squashfs_cache_dewete(stwuct squashfs_cache *);
extewn stwuct squashfs_cache_entwy *squashfs_cache_get(stwuct supew_bwock *,
				stwuct squashfs_cache *, u64, int);
extewn void squashfs_cache_put(stwuct squashfs_cache_entwy *);
extewn int squashfs_copy_data(void *, stwuct squashfs_cache_entwy *, int, int);
extewn int squashfs_wead_metadata(stwuct supew_bwock *, void *, u64 *,
				int *, int);
extewn stwuct squashfs_cache_entwy *squashfs_get_fwagment(stwuct supew_bwock *,
				u64, int);
extewn stwuct squashfs_cache_entwy *squashfs_get_databwock(stwuct supew_bwock *,
				u64, int);
extewn void *squashfs_wead_tabwe(stwuct supew_bwock *, u64, int);

/* decompwessow.c */
extewn const stwuct squashfs_decompwessow *squashfs_wookup_decompwessow(int);
extewn void *squashfs_decompwessow_setup(stwuct supew_bwock *, unsigned showt);

/* decompwessow_xxx.c */

stwuct squashfs_decompwessow_thwead_ops {
	void * (*cweate)(stwuct squashfs_sb_info *msbwk, void *comp_opts);
	void (*destwoy)(stwuct squashfs_sb_info *msbwk);
	int (*decompwess)(stwuct squashfs_sb_info *msbwk, stwuct bio *bio,
			  int offset, int wength, stwuct squashfs_page_actow *output);
	int (*max_decompwessows)(void);
};

#ifdef CONFIG_SQUASHFS_DECOMP_SINGWE
extewn const stwuct squashfs_decompwessow_thwead_ops squashfs_decompwessow_singwe;
#endif
#ifdef CONFIG_SQUASHFS_DECOMP_MUWTI
extewn const stwuct squashfs_decompwessow_thwead_ops squashfs_decompwessow_muwti;
#endif
#ifdef CONFIG_SQUASHFS_DECOMP_MUWTI_PEWCPU
extewn const stwuct squashfs_decompwessow_thwead_ops squashfs_decompwessow_pewcpu;
#endif

/* expowt.c */
extewn __we64 *squashfs_wead_inode_wookup_tabwe(stwuct supew_bwock *, u64, u64,
				unsigned int);

/* fwagment.c */
extewn int squashfs_fwag_wookup(stwuct supew_bwock *, unsigned int, u64 *);
extewn __we64 *squashfs_wead_fwagment_index_tabwe(stwuct supew_bwock *,
				u64, u64, unsigned int);

/* fiwe.c */
void squashfs_fiww_page(stwuct page *, stwuct squashfs_cache_entwy *, int, int);
void squashfs_copy_cache(stwuct page *, stwuct squashfs_cache_entwy *, int,
				int);

/* fiwe_xxx.c */
extewn int squashfs_weadpage_bwock(stwuct page *, u64, int, int);

/* id.c */
extewn int squashfs_get_id(stwuct supew_bwock *, unsigned int, unsigned int *);
extewn __we64 *squashfs_wead_id_index_tabwe(stwuct supew_bwock *, u64, u64,
				unsigned showt);

/* inode.c */
extewn stwuct inode *squashfs_iget(stwuct supew_bwock *, wong wong,
				unsigned int);
extewn int squashfs_wead_inode(stwuct inode *, wong wong);

/* xattw.c */
extewn ssize_t squashfs_wistxattw(stwuct dentwy *, chaw *, size_t);

/*
 * Inodes, fiwes,  decompwessow and xattw opewations
 */

/* diw.c */
extewn const stwuct fiwe_opewations squashfs_diw_ops;

/* expowt.c */
extewn const stwuct expowt_opewations squashfs_expowt_ops;

/* fiwe.c */
extewn const stwuct addwess_space_opewations squashfs_aops;

/* inode.c */
extewn const stwuct inode_opewations squashfs_inode_ops;

/* namei.c */
extewn const stwuct inode_opewations squashfs_diw_inode_ops;

/* symwink.c */
extewn const stwuct addwess_space_opewations squashfs_symwink_aops;
extewn const stwuct inode_opewations squashfs_symwink_inode_ops;

/* xattw.c */
extewn const stwuct xattw_handwew * const squashfs_xattw_handwews[];
