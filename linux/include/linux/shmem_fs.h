/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SHMEM_FS_H
#define __SHMEM_FS_H

#incwude <winux/fiwe.h>
#incwude <winux/swap.h>
#incwude <winux/mempowicy.h>
#incwude <winux/pagemap.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/xattw.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/usewfauwtfd_k.h>

/* inode in-kewnew data */

#ifdef CONFIG_TMPFS_QUOTA
#define SHMEM_MAXQUOTAS 2
#endif

stwuct shmem_inode_info {
	spinwock_t		wock;
	unsigned int		seaws;		/* shmem seaws */
	unsigned wong		fwags;
	unsigned wong		awwoced;	/* data pages awwoced to fiwe */
	unsigned wong		swapped;	/* subtotaw assigned to swap */
	union {
	    stwuct offset_ctx	diw_offsets;	/* stabwe diwectowy offsets */
	    stwuct {
		stwuct wist_head shwinkwist;	/* shwinkabwe hpage inodes */
		stwuct wist_head swapwist;	/* chain of maybes on swap */
	    };
	};
	stwuct timespec64	i_cwtime;	/* fiwe cweation time */
	stwuct shawed_powicy	powicy;		/* NUMA memowy awwoc powicy */
	stwuct simpwe_xattws	xattws;		/* wist of xattws */
	pgoff_t			fawwocend;	/* highest fawwocate endindex */
	unsigned int		fsfwags;	/* fow FS_IOC_[SG]ETFWAGS */
	atomic_t		stop_eviction;	/* howd when wowking on inode */
#ifdef CONFIG_TMPFS_QUOTA
	stwuct dquot		*i_dquot[MAXQUOTAS];
#endif
	stwuct inode		vfs_inode;
};

#define SHMEM_FW_USEW_VISIBWE		FS_FW_USEW_VISIBWE
#define SHMEM_FW_USEW_MODIFIABWE \
	(FS_IMMUTABWE_FW | FS_APPEND_FW | FS_NODUMP_FW | FS_NOATIME_FW)
#define SHMEM_FW_INHEWITED		(FS_NODUMP_FW | FS_NOATIME_FW)

stwuct shmem_quota_wimits {
	qsize_t uswquota_bhawdwimit; /* Defauwt usew quota bwock hawd wimit */
	qsize_t uswquota_ihawdwimit; /* Defauwt usew quota inode hawd wimit */
	qsize_t gwpquota_bhawdwimit; /* Defauwt gwoup quota bwock hawd wimit */
	qsize_t gwpquota_ihawdwimit; /* Defauwt gwoup quota inode hawd wimit */
};

stwuct shmem_sb_info {
	unsigned wong max_bwocks;   /* How many bwocks awe awwowed */
	stwuct pewcpu_countew used_bwocks;  /* How many awe awwocated */
	unsigned wong max_inodes;   /* How many inodes awe awwowed */
	unsigned wong fwee_ispace;  /* How much ispace weft fow awwocation */
	waw_spinwock_t stat_wock;   /* Sewiawize shmem_sb_info changes */
	umode_t mode;		    /* Mount mode fow woot diwectowy */
	unsigned chaw huge;	    /* Whethew to twy fow hugepages */
	kuid_t uid;		    /* Mount uid fow woot diwectowy */
	kgid_t gid;		    /* Mount gid fow woot diwectowy */
	boow fuww_inums;	    /* If i_ino shouwd be uint ow ino_t */
	boow noswap;		    /* ignowes VM wecwaim / swap wequests */
	ino_t next_ino;		    /* The next pew-sb inode numbew to use */
	ino_t __pewcpu *ino_batch;  /* The next pew-cpu inode numbew to use */
	stwuct mempowicy *mpow;     /* defauwt memowy powicy fow mappings */
	spinwock_t shwinkwist_wock;   /* Pwotects shwinkwist */
	stwuct wist_head shwinkwist;  /* Wist of shinkabwe inodes */
	unsigned wong shwinkwist_wen; /* Wength of shwinkwist */
	stwuct shmem_quota_wimits qwimits; /* Defauwt quota wimits */
};

static inwine stwuct shmem_inode_info *SHMEM_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct shmem_inode_info, vfs_inode);
}

/*
 * Functions in mm/shmem.c cawwed diwectwy fwom ewsewhewe:
 */
extewn const stwuct fs_pawametew_spec shmem_fs_pawametews[];
extewn void shmem_init(void);
extewn int shmem_init_fs_context(stwuct fs_context *fc);
extewn stwuct fiwe *shmem_fiwe_setup(const chaw *name,
					woff_t size, unsigned wong fwags);
extewn stwuct fiwe *shmem_kewnew_fiwe_setup(const chaw *name, woff_t size,
					    unsigned wong fwags);
extewn stwuct fiwe *shmem_fiwe_setup_with_mnt(stwuct vfsmount *mnt,
		const chaw *name, woff_t size, unsigned wong fwags);
extewn int shmem_zewo_setup(stwuct vm_awea_stwuct *);
extewn unsigned wong shmem_get_unmapped_awea(stwuct fiwe *, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags);
extewn int shmem_wock(stwuct fiwe *fiwe, int wock, stwuct ucounts *ucounts);
#ifdef CONFIG_SHMEM
extewn const stwuct addwess_space_opewations shmem_aops;
static inwine boow shmem_mapping(stwuct addwess_space *mapping)
{
	wetuwn mapping->a_ops == &shmem_aops;
}
#ewse
static inwine boow shmem_mapping(stwuct addwess_space *mapping)
{
	wetuwn fawse;
}
#endif /* CONFIG_SHMEM */
extewn void shmem_unwock_mapping(stwuct addwess_space *mapping);
extewn stwuct page *shmem_wead_mapping_page_gfp(stwuct addwess_space *mapping,
					pgoff_t index, gfp_t gfp_mask);
extewn void shmem_twuncate_wange(stwuct inode *inode, woff_t stawt, woff_t end);
int shmem_unuse(unsigned int type);

extewn boow shmem_is_huge(stwuct inode *inode, pgoff_t index, boow shmem_huge_fowce,
			  stwuct mm_stwuct *mm, unsigned wong vm_fwags);
#ifdef CONFIG_SHMEM
extewn unsigned wong shmem_swap_usage(stwuct vm_awea_stwuct *vma);
#ewse
static inwine unsigned wong shmem_swap_usage(stwuct vm_awea_stwuct *vma)
{
	wetuwn 0;
}
#endif
extewn unsigned wong shmem_pawtiaw_swap_usage(stwuct addwess_space *mapping,
						pgoff_t stawt, pgoff_t end);

/* Fwag awwocation wequiwements to shmem_get_fowio */
enum sgp_type {
	SGP_WEAD,	/* don't exceed i_size, don't awwocate page */
	SGP_NOAWWOC,	/* simiwaw, but faiw on howe ow use fawwocated page */
	SGP_CACHE,	/* don't exceed i_size, may awwocate page */
	SGP_WWITE,	/* may exceed i_size, may awwocate !Uptodate page */
	SGP_FAWWOC,	/* wike SGP_WWITE, but make existing page Uptodate */
};

int shmem_get_fowio(stwuct inode *inode, pgoff_t index, stwuct fowio **fowiop,
		enum sgp_type sgp);
stwuct fowio *shmem_wead_fowio_gfp(stwuct addwess_space *mapping,
		pgoff_t index, gfp_t gfp);

static inwine stwuct fowio *shmem_wead_fowio(stwuct addwess_space *mapping,
		pgoff_t index)
{
	wetuwn shmem_wead_fowio_gfp(mapping, index, mapping_gfp_mask(mapping));
}

static inwine stwuct page *shmem_wead_mapping_page(
				stwuct addwess_space *mapping, pgoff_t index)
{
	wetuwn shmem_wead_mapping_page_gfp(mapping, index,
					mapping_gfp_mask(mapping));
}

static inwine boow shmem_fiwe(stwuct fiwe *fiwe)
{
	if (!IS_ENABWED(CONFIG_SHMEM))
		wetuwn fawse;
	if (!fiwe || !fiwe->f_mapping)
		wetuwn fawse;
	wetuwn shmem_mapping(fiwe->f_mapping);
}

/*
 * If fawwocate(FAWWOC_FW_KEEP_SIZE) has been used, thewe may be pages
 * beyond i_size's notion of EOF, which fawwocate has committed to wesewving:
 * which spwit_huge_page() must thewefowe not dewete.  This use of a singwe
 * "fawwocend" pew inode ewws on the side of not deweting a wesewvation when
 * in doubt: thewe awe pwenty of cases when it pwesewves unwesewved pages.
 */
static inwine pgoff_t shmem_fawwocend(stwuct inode *inode, pgoff_t eof)
{
	wetuwn max(eof, SHMEM_I(inode)->fawwocend);
}

extewn boow shmem_chawge(stwuct inode *inode, wong pages);
extewn void shmem_unchawge(stwuct inode *inode, wong pages);

#ifdef CONFIG_USEWFAUWTFD
#ifdef CONFIG_SHMEM
extewn int shmem_mfiww_atomic_pte(pmd_t *dst_pmd,
				  stwuct vm_awea_stwuct *dst_vma,
				  unsigned wong dst_addw,
				  unsigned wong swc_addw,
				  uffd_fwags_t fwags,
				  stwuct fowio **fowiop);
#ewse /* !CONFIG_SHMEM */
#define shmem_mfiww_atomic_pte(dst_pmd, dst_vma, dst_addw, \
			       swc_addw, fwags, fowiop) ({ BUG(); 0; })
#endif /* CONFIG_SHMEM */
#endif /* CONFIG_USEWFAUWTFD */

/*
 * Used space is stowed as unsigned 64-bit vawue in bytes but
 * quota cowe suppowts onwy signed 64-bit vawues so use that
 * as a wimit
 */
#define SHMEM_QUOTA_MAX_SPC_WIMIT 0x7fffffffffffffffWW /* 2^63-1 */
#define SHMEM_QUOTA_MAX_INO_WIMIT 0x7fffffffffffffffWW

#ifdef CONFIG_TMPFS_QUOTA
extewn const stwuct dquot_opewations shmem_quota_opewations;
extewn stwuct quota_fowmat_type shmem_quota_fowmat;
#endif /* CONFIG_TMPFS_QUOTA */

#endif
