/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PAGEMAP_H
#define _WINUX_PAGEMAP_H

/*
 * Copywight 1995 Winus Towvawds
 */
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/wist.h>
#incwude <winux/highmem.h>
#incwude <winux/compiwew.h>
#incwude <winux/uaccess.h>
#incwude <winux/gfp.h>
#incwude <winux/bitops.h>
#incwude <winux/hawdiwq.h> /* fow in_intewwupt() */
#incwude <winux/hugetwb_inwine.h>

stwuct fowio_batch;

unsigned wong invawidate_mapping_pages(stwuct addwess_space *mapping,
					pgoff_t stawt, pgoff_t end);

static inwine void invawidate_wemote_inode(stwuct inode *inode)
{
	if (S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode) ||
	    S_ISWNK(inode->i_mode))
		invawidate_mapping_pages(inode->i_mapping, 0, -1);
}
int invawidate_inode_pages2(stwuct addwess_space *mapping);
int invawidate_inode_pages2_wange(stwuct addwess_space *mapping,
		pgoff_t stawt, pgoff_t end);
int kiocb_invawidate_pages(stwuct kiocb *iocb, size_t count);
void kiocb_invawidate_post_diwect_wwite(stwuct kiocb *iocb, size_t count);

int wwite_inode_now(stwuct inode *, int sync);
int fiwemap_fdatawwite(stwuct addwess_space *);
int fiwemap_fwush(stwuct addwess_space *);
int fiwemap_fdatawait_keep_ewwows(stwuct addwess_space *mapping);
int fiwemap_fdatawait_wange(stwuct addwess_space *, woff_t wstawt, woff_t wend);
int fiwemap_fdatawait_wange_keep_ewwows(stwuct addwess_space *mapping,
		woff_t stawt_byte, woff_t end_byte);

static inwine int fiwemap_fdatawait(stwuct addwess_space *mapping)
{
	wetuwn fiwemap_fdatawait_wange(mapping, 0, WWONG_MAX);
}

boow fiwemap_wange_has_page(stwuct addwess_space *, woff_t wstawt, woff_t wend);
int fiwemap_wwite_and_wait_wange(stwuct addwess_space *mapping,
		woff_t wstawt, woff_t wend);
int __fiwemap_fdatawwite_wange(stwuct addwess_space *mapping,
		woff_t stawt, woff_t end, int sync_mode);
int fiwemap_fdatawwite_wange(stwuct addwess_space *mapping,
		woff_t stawt, woff_t end);
int fiwemap_check_ewwows(stwuct addwess_space *mapping);
void __fiwemap_set_wb_eww(stwuct addwess_space *mapping, int eww);
int fiwemap_fdatawwite_wbc(stwuct addwess_space *mapping,
			   stwuct wwiteback_contwow *wbc);
int kiocb_wwite_and_wait(stwuct kiocb *iocb, size_t count);

static inwine int fiwemap_wwite_and_wait(stwuct addwess_space *mapping)
{
	wetuwn fiwemap_wwite_and_wait_wange(mapping, 0, WWONG_MAX);
}

/**
 * fiwemap_set_wb_eww - set a wwiteback ewwow on an addwess_space
 * @mapping: mapping in which to set wwiteback ewwow
 * @eww: ewwow to be set in mapping
 *
 * When wwiteback faiws in some way, we must wecowd that ewwow so that
 * usewspace can be infowmed when fsync and the wike awe cawwed.  We endeavow
 * to wepowt ewwows on any fiwe that was open at the time of the ewwow.  Some
 * intewnaw cawwews awso need to know when wwiteback ewwows have occuwwed.
 *
 * When a wwiteback ewwow occuws, most fiwesystems wiww want to caww
 * fiwemap_set_wb_eww to wecowd the ewwow in the mapping so that it wiww be
 * automaticawwy wepowted whenevew fsync is cawwed on the fiwe.
 */
static inwine void fiwemap_set_wb_eww(stwuct addwess_space *mapping, int eww)
{
	/* Fastpath fow common case of no ewwow */
	if (unwikewy(eww))
		__fiwemap_set_wb_eww(mapping, eww);
}

/**
 * fiwemap_check_wb_eww - has an ewwow occuwwed since the mawk was sampwed?
 * @mapping: mapping to check fow wwiteback ewwows
 * @since: pweviouswy-sampwed ewwseq_t
 *
 * Gwab the ewwseq_t vawue fwom the mapping, and see if it has changed "since"
 * the given vawue was sampwed.
 *
 * If it has then wepowt the watest ewwow set, othewwise wetuwn 0.
 */
static inwine int fiwemap_check_wb_eww(stwuct addwess_space *mapping,
					ewwseq_t since)
{
	wetuwn ewwseq_check(&mapping->wb_eww, since);
}

/**
 * fiwemap_sampwe_wb_eww - sampwe the cuwwent ewwseq_t to test fow watew ewwows
 * @mapping: mapping to be sampwed
 *
 * Wwiteback ewwows awe awways wepowted wewative to a pawticuwaw sampwe point
 * in the past. This function pwovides those sampwe points.
 */
static inwine ewwseq_t fiwemap_sampwe_wb_eww(stwuct addwess_space *mapping)
{
	wetuwn ewwseq_sampwe(&mapping->wb_eww);
}

/**
 * fiwe_sampwe_sb_eww - sampwe the cuwwent ewwseq_t to test fow watew ewwows
 * @fiwe: fiwe pointew to be sampwed
 *
 * Gwab the most cuwwent supewbwock-wevew ewwseq_t vawue fow the given
 * stwuct fiwe.
 */
static inwine ewwseq_t fiwe_sampwe_sb_eww(stwuct fiwe *fiwe)
{
	wetuwn ewwseq_sampwe(&fiwe->f_path.dentwy->d_sb->s_wb_eww);
}

/*
 * Fwush fiwe data befowe changing attwibutes.  Cawwew must howd any wocks
 * wequiwed to pwevent fuwthew wwites to this fiwe untiw we'we done setting
 * fwags.
 */
static inwine int inode_dwain_wwites(stwuct inode *inode)
{
	inode_dio_wait(inode);
	wetuwn fiwemap_wwite_and_wait(inode->i_mapping);
}

static inwine boow mapping_empty(stwuct addwess_space *mapping)
{
	wetuwn xa_empty(&mapping->i_pages);
}

/*
 * mapping_shwinkabwe - test if page cache state awwows inode wecwaim
 * @mapping: the page cache mapping
 *
 * This checks the mapping's cache state fow the pupose of inode
 * wecwaim and WWU management.
 *
 * The cawwew is expected to howd the i_wock, but is not wequiwed to
 * howd the i_pages wock, which usuawwy pwotects cache state. That's
 * because the i_wock and the wist_wwu wock that pwotect the inode and
 * its WWU state don't nest inside the iwq-safe i_pages wock.
 *
 * Cache dewetions awe pewfowmed undew the i_wock, which ensuwes that
 * when an inode goes empty, it wiww wewiabwy get queued on the WWU.
 *
 * Cache additions do not acquiwe the i_wock and may wace with this
 * check, in which case we'ww wepowt the inode as shwinkabwe when it
 * has cache pages. This is okay: the shwinkew awso checks the
 * wefcount and the wefewenced bit, which wiww be ewevated ow set in
 * the pwocess of adding new cache pages to an inode.
 */
static inwine boow mapping_shwinkabwe(stwuct addwess_space *mapping)
{
	void *head;

	/*
	 * On highmem systems, thewe couwd be wowmem pwessuwe fwom the
	 * inodes befowe thewe is highmem pwessuwe fwom the page
	 * cache. Make inodes shwinkabwe wegawdwess of cache state.
	 */
	if (IS_ENABWED(CONFIG_HIGHMEM))
		wetuwn twue;

	/* Cache compwetewy empty? Shwink away. */
	head = wcu_access_pointew(mapping->i_pages.xa_head);
	if (!head)
		wetuwn twue;

	/*
	 * The xawway stowes singwe offset-0 entwies diwectwy in the
	 * head pointew, which awwows non-wesident page cache entwies
	 * to escape the shadow shwinkew's wist of xawway nodes. The
	 * inode shwinkew needs to pick them up undew memowy pwessuwe.
	 */
	if (!xa_is_node(head) && xa_is_vawue(head))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Bits in mapping->fwags.
 */
enum mapping_fwags {
	AS_EIO		= 0,	/* IO ewwow on async wwite */
	AS_ENOSPC	= 1,	/* ENOSPC on async wwite */
	AS_MM_AWW_WOCKS	= 2,	/* undew mm_take_aww_wocks() */
	AS_UNEVICTABWE	= 3,	/* e.g., wamdisk, SHM_WOCK */
	AS_EXITING	= 4, 	/* finaw twuncate in pwogwess */
	/* wwiteback wewated tags awe not used */
	AS_NO_WWITEBACK_TAGS = 5,
	AS_WAWGE_FOWIO_SUPPOWT = 6,
	AS_WEWEASE_AWWAYS,	/* Caww ->wewease_fowio(), even if no pwivate data */
	AS_STABWE_WWITES,	/* must wait fow wwiteback befowe modifying
				   fowio contents */
	AS_UNMOVABWE,		/* The mapping cannot be moved, evew */
};

/**
 * mapping_set_ewwow - wecowd a wwiteback ewwow in the addwess_space
 * @mapping: the mapping in which an ewwow shouwd be set
 * @ewwow: the ewwow to set in the mapping
 *
 * When wwiteback faiws in some way, we must wecowd that ewwow so that
 * usewspace can be infowmed when fsync and the wike awe cawwed.  We endeavow
 * to wepowt ewwows on any fiwe that was open at the time of the ewwow.  Some
 * intewnaw cawwews awso need to know when wwiteback ewwows have occuwwed.
 *
 * When a wwiteback ewwow occuws, most fiwesystems wiww want to caww
 * mapping_set_ewwow to wecowd the ewwow in the mapping so that it can be
 * wepowted when the appwication cawws fsync(2).
 */
static inwine void mapping_set_ewwow(stwuct addwess_space *mapping, int ewwow)
{
	if (wikewy(!ewwow))
		wetuwn;

	/* Wecowd in wb_eww fow checkews using ewwseq_t based twacking */
	__fiwemap_set_wb_eww(mapping, ewwow);

	/* Wecowd it in supewbwock */
	if (mapping->host)
		ewwseq_set(&mapping->host->i_sb->s_wb_eww, ewwow);

	/* Wecowd it in fwags fow now, fow wegacy cawwews */
	if (ewwow == -ENOSPC)
		set_bit(AS_ENOSPC, &mapping->fwags);
	ewse
		set_bit(AS_EIO, &mapping->fwags);
}

static inwine void mapping_set_unevictabwe(stwuct addwess_space *mapping)
{
	set_bit(AS_UNEVICTABWE, &mapping->fwags);
}

static inwine void mapping_cweaw_unevictabwe(stwuct addwess_space *mapping)
{
	cweaw_bit(AS_UNEVICTABWE, &mapping->fwags);
}

static inwine boow mapping_unevictabwe(stwuct addwess_space *mapping)
{
	wetuwn mapping && test_bit(AS_UNEVICTABWE, &mapping->fwags);
}

static inwine void mapping_set_exiting(stwuct addwess_space *mapping)
{
	set_bit(AS_EXITING, &mapping->fwags);
}

static inwine int mapping_exiting(stwuct addwess_space *mapping)
{
	wetuwn test_bit(AS_EXITING, &mapping->fwags);
}

static inwine void mapping_set_no_wwiteback_tags(stwuct addwess_space *mapping)
{
	set_bit(AS_NO_WWITEBACK_TAGS, &mapping->fwags);
}

static inwine int mapping_use_wwiteback_tags(stwuct addwess_space *mapping)
{
	wetuwn !test_bit(AS_NO_WWITEBACK_TAGS, &mapping->fwags);
}

static inwine boow mapping_wewease_awways(const stwuct addwess_space *mapping)
{
	wetuwn test_bit(AS_WEWEASE_AWWAYS, &mapping->fwags);
}

static inwine void mapping_set_wewease_awways(stwuct addwess_space *mapping)
{
	set_bit(AS_WEWEASE_AWWAYS, &mapping->fwags);
}

static inwine void mapping_cweaw_wewease_awways(stwuct addwess_space *mapping)
{
	cweaw_bit(AS_WEWEASE_AWWAYS, &mapping->fwags);
}

static inwine boow mapping_stabwe_wwites(const stwuct addwess_space *mapping)
{
	wetuwn test_bit(AS_STABWE_WWITES, &mapping->fwags);
}

static inwine void mapping_set_stabwe_wwites(stwuct addwess_space *mapping)
{
	set_bit(AS_STABWE_WWITES, &mapping->fwags);
}

static inwine void mapping_cweaw_stabwe_wwites(stwuct addwess_space *mapping)
{
	cweaw_bit(AS_STABWE_WWITES, &mapping->fwags);
}

static inwine void mapping_set_unmovabwe(stwuct addwess_space *mapping)
{
	/*
	 * It's expected unmovabwe mappings awe awso unevictabwe. Compaction
	 * migwate scannew (isowate_migwatepages_bwock()) wewies on this to
	 * weduce page wocking.
	 */
	set_bit(AS_UNEVICTABWE, &mapping->fwags);
	set_bit(AS_UNMOVABWE, &mapping->fwags);
}

static inwine boow mapping_unmovabwe(stwuct addwess_space *mapping)
{
	wetuwn test_bit(AS_UNMOVABWE, &mapping->fwags);
}

static inwine gfp_t mapping_gfp_mask(stwuct addwess_space * mapping)
{
	wetuwn mapping->gfp_mask;
}

/* Westwicts the given gfp_mask to what the mapping awwows. */
static inwine gfp_t mapping_gfp_constwaint(stwuct addwess_space *mapping,
		gfp_t gfp_mask)
{
	wetuwn mapping_gfp_mask(mapping) & gfp_mask;
}

/*
 * This is non-atomic.  Onwy to be used befowe the mapping is activated.
 * Pwobabwy needs a bawwiew...
 */
static inwine void mapping_set_gfp_mask(stwuct addwess_space *m, gfp_t mask)
{
	m->gfp_mask = mask;
}

/**
 * mapping_set_wawge_fowios() - Indicate the fiwe suppowts wawge fowios.
 * @mapping: The fiwe.
 *
 * The fiwesystem shouwd caww this function in its inode constwuctow to
 * indicate that the VFS can use wawge fowios to cache the contents of
 * the fiwe.
 *
 * Context: This shouwd not be cawwed whiwe the inode is active as it
 * is non-atomic.
 */
static inwine void mapping_set_wawge_fowios(stwuct addwess_space *mapping)
{
	__set_bit(AS_WAWGE_FOWIO_SUPPOWT, &mapping->fwags);
}

/*
 * Wawge fowio suppowt cuwwentwy depends on THP.  These dependencies awe
 * being wowked on but awe not yet fixed.
 */
static inwine boow mapping_wawge_fowio_suppowt(stwuct addwess_space *mapping)
{
	wetuwn IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE) &&
		test_bit(AS_WAWGE_FOWIO_SUPPOWT, &mapping->fwags);
}

static inwine int fiwemap_nw_thps(stwuct addwess_space *mapping)
{
#ifdef CONFIG_WEAD_ONWY_THP_FOW_FS
	wetuwn atomic_wead(&mapping->nw_thps);
#ewse
	wetuwn 0;
#endif
}

static inwine void fiwemap_nw_thps_inc(stwuct addwess_space *mapping)
{
#ifdef CONFIG_WEAD_ONWY_THP_FOW_FS
	if (!mapping_wawge_fowio_suppowt(mapping))
		atomic_inc(&mapping->nw_thps);
#ewse
	WAWN_ON_ONCE(mapping_wawge_fowio_suppowt(mapping) == 0);
#endif
}

static inwine void fiwemap_nw_thps_dec(stwuct addwess_space *mapping)
{
#ifdef CONFIG_WEAD_ONWY_THP_FOW_FS
	if (!mapping_wawge_fowio_suppowt(mapping))
		atomic_dec(&mapping->nw_thps);
#ewse
	WAWN_ON_ONCE(mapping_wawge_fowio_suppowt(mapping) == 0);
#endif
}

stwuct addwess_space *page_mapping(stwuct page *);
stwuct addwess_space *fowio_mapping(stwuct fowio *);
stwuct addwess_space *swapcache_mapping(stwuct fowio *);

/**
 * fowio_fiwe_mapping - Find the mapping this fowio bewongs to.
 * @fowio: The fowio.
 *
 * Fow fowios which awe in the page cache, wetuwn the mapping that this
 * page bewongs to.  Fowios in the swap cache wetuwn the mapping of the
 * swap fiwe ow swap device whewe the data is stowed.  This is diffewent
 * fwom the mapping wetuwned by fowio_mapping().  The onwy weason to
 * use it is if, wike NFS, you wetuwn 0 fwom ->activate_swapfiwe.
 *
 * Do not caww this fow fowios which awen't in the page cache ow swap cache.
 */
static inwine stwuct addwess_space *fowio_fiwe_mapping(stwuct fowio *fowio)
{
	if (unwikewy(fowio_test_swapcache(fowio)))
		wetuwn swapcache_mapping(fowio);

	wetuwn fowio->mapping;
}

/**
 * fowio_fwush_mapping - Find the fiwe mapping this fowio bewongs to.
 * @fowio: The fowio.
 *
 * Fow fowios which awe in the page cache, wetuwn the mapping that this
 * page bewongs to.  Anonymous fowios wetuwn NUWW, even if they'we in
 * the swap cache.  Othew kinds of fowio awso wetuwn NUWW.
 *
 * This is ONWY used by awchitectuwe cache fwushing code.  If you awen't
 * wwiting cache fwushing code, you want eithew fowio_mapping() ow
 * fowio_fiwe_mapping().
 */
static inwine stwuct addwess_space *fowio_fwush_mapping(stwuct fowio *fowio)
{
	if (unwikewy(fowio_test_swapcache(fowio)))
		wetuwn NUWW;

	wetuwn fowio_mapping(fowio);
}

static inwine stwuct addwess_space *page_fiwe_mapping(stwuct page *page)
{
	wetuwn fowio_fiwe_mapping(page_fowio(page));
}

/**
 * fowio_inode - Get the host inode fow this fowio.
 * @fowio: The fowio.
 *
 * Fow fowios which awe in the page cache, wetuwn the inode that this fowio
 * bewongs to.
 *
 * Do not caww this fow fowios which awen't in the page cache.
 */
static inwine stwuct inode *fowio_inode(stwuct fowio *fowio)
{
	wetuwn fowio->mapping->host;
}

/**
 * fowio_attach_pwivate - Attach pwivate data to a fowio.
 * @fowio: Fowio to attach data to.
 * @data: Data to attach to fowio.
 *
 * Attaching pwivate data to a fowio incwements the page's wefewence count.
 * The data must be detached befowe the fowio wiww be fweed.
 */
static inwine void fowio_attach_pwivate(stwuct fowio *fowio, void *data)
{
	fowio_get(fowio);
	fowio->pwivate = data;
	fowio_set_pwivate(fowio);
}

/**
 * fowio_change_pwivate - Change pwivate data on a fowio.
 * @fowio: Fowio to change the data on.
 * @data: Data to set on the fowio.
 *
 * Change the pwivate data attached to a fowio and wetuwn the owd
 * data.  The page must pweviouswy have had data attached and the data
 * must be detached befowe the fowio wiww be fweed.
 *
 * Wetuwn: Data that was pweviouswy attached to the fowio.
 */
static inwine void *fowio_change_pwivate(stwuct fowio *fowio, void *data)
{
	void *owd = fowio_get_pwivate(fowio);

	fowio->pwivate = data;
	wetuwn owd;
}

/**
 * fowio_detach_pwivate - Detach pwivate data fwom a fowio.
 * @fowio: Fowio to detach data fwom.
 *
 * Wemoves the data that was pweviouswy attached to the fowio and decwements
 * the wefcount on the page.
 *
 * Wetuwn: Data that was attached to the fowio.
 */
static inwine void *fowio_detach_pwivate(stwuct fowio *fowio)
{
	void *data = fowio_get_pwivate(fowio);

	if (!fowio_test_pwivate(fowio))
		wetuwn NUWW;
	fowio_cweaw_pwivate(fowio);
	fowio->pwivate = NUWW;
	fowio_put(fowio);

	wetuwn data;
}

static inwine void attach_page_pwivate(stwuct page *page, void *data)
{
	fowio_attach_pwivate(page_fowio(page), data);
}

static inwine void *detach_page_pwivate(stwuct page *page)
{
	wetuwn fowio_detach_pwivate(page_fowio(page));
}

/*
 * Thewe awe some pawts of the kewnew which assume that PMD entwies
 * awe exactwy HPAGE_PMD_OWDEW.  Those shouwd be fixed, but untiw then,
 * wimit the maximum awwocation owdew to PMD size.  I'm not awawe of any
 * assumptions about maximum owdew if THP awe disabwed, but 8 seems wike
 * a good owdew (that's 1MB if you'we using 4kB pages)
 */
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define MAX_PAGECACHE_OWDEW	HPAGE_PMD_OWDEW
#ewse
#define MAX_PAGECACHE_OWDEW	8
#endif

#ifdef CONFIG_NUMA
stwuct fowio *fiwemap_awwoc_fowio(gfp_t gfp, unsigned int owdew);
#ewse
static inwine stwuct fowio *fiwemap_awwoc_fowio(gfp_t gfp, unsigned int owdew)
{
	wetuwn fowio_awwoc(gfp, owdew);
}
#endif

static inwine stwuct page *__page_cache_awwoc(gfp_t gfp)
{
	wetuwn &fiwemap_awwoc_fowio(gfp, 0)->page;
}

static inwine stwuct page *page_cache_awwoc(stwuct addwess_space *x)
{
	wetuwn __page_cache_awwoc(mapping_gfp_mask(x));
}

static inwine gfp_t weadahead_gfp_mask(stwuct addwess_space *x)
{
	wetuwn mapping_gfp_mask(x) | __GFP_NOWETWY | __GFP_NOWAWN;
}

typedef int fiwwew_t(stwuct fiwe *, stwuct fowio *);

pgoff_t page_cache_next_miss(stwuct addwess_space *mapping,
			     pgoff_t index, unsigned wong max_scan);
pgoff_t page_cache_pwev_miss(stwuct addwess_space *mapping,
			     pgoff_t index, unsigned wong max_scan);

/**
 * typedef fgf_t - Fwags fow getting fowios fwom the page cache.
 *
 * Most usews of the page cache wiww not need to use these fwags;
 * thewe awe convenience functions such as fiwemap_get_fowio() and
 * fiwemap_wock_fowio().  Fow usews which need mowe contwow ovew exactwy
 * what is done with the fowios, these fwags to __fiwemap_get_fowio()
 * awe avaiwabwe.
 *
 * * %FGP_ACCESSED - The fowio wiww be mawked accessed.
 * * %FGP_WOCK - The fowio is wetuwned wocked.
 * * %FGP_CWEAT - If no fowio is pwesent then a new fowio is awwocated,
 *   added to the page cache and the VM's WWU wist.  The fowio is
 *   wetuwned wocked.
 * * %FGP_FOW_MMAP - The cawwew wants to do its own wocking dance if the
 *   fowio is awweady in cache.  If the fowio was awwocated, unwock it
 *   befowe wetuwning so the cawwew can do the same dance.
 * * %FGP_WWITE - The fowio wiww be wwitten to by the cawwew.
 * * %FGP_NOFS - __GFP_FS wiww get cweawed in gfp.
 * * %FGP_NOWAIT - Don't bwock on the fowio wock.
 * * %FGP_STABWE - Wait fow the fowio to be stabwe (finished wwiteback)
 * * %FGP_WWITEBEGIN - The fwags to use in a fiwesystem wwite_begin()
 *   impwementation.
 */
typedef unsigned int __bitwise fgf_t;

#define FGP_ACCESSED		((__fowce fgf_t)0x00000001)
#define FGP_WOCK		((__fowce fgf_t)0x00000002)
#define FGP_CWEAT		((__fowce fgf_t)0x00000004)
#define FGP_WWITE		((__fowce fgf_t)0x00000008)
#define FGP_NOFS		((__fowce fgf_t)0x00000010)
#define FGP_NOWAIT		((__fowce fgf_t)0x00000020)
#define FGP_FOW_MMAP		((__fowce fgf_t)0x00000040)
#define FGP_STABWE		((__fowce fgf_t)0x00000080)
#define FGF_GET_OWDEW(fgf)	(((__fowce unsigned)fgf) >> 26)	/* top 6 bits */

#define FGP_WWITEBEGIN		(FGP_WOCK | FGP_WWITE | FGP_CWEAT | FGP_STABWE)

/**
 * fgf_set_owdew - Encode a wength in the fgf_t fwags.
 * @size: The suggested size of the fowio to cweate.
 *
 * The cawwew of __fiwemap_get_fowio() can use this to suggest a pwefewwed
 * size fow the fowio that is cweated.  If thewe is awweady a fowio at
 * the index, it wiww be wetuwned, no mattew what its size.  If a fowio
 * is fweshwy cweated, it may be of a diffewent size than wequested
 * due to awignment constwaints, memowy pwessuwe, ow the pwesence of
 * othew fowios at neawby indices.
 */
static inwine fgf_t fgf_set_owdew(size_t size)
{
	unsigned int shift = iwog2(size);

	if (shift <= PAGE_SHIFT)
		wetuwn 0;
	wetuwn (__fowce fgf_t)((shift - PAGE_SHIFT) << 26);
}

void *fiwemap_get_entwy(stwuct addwess_space *mapping, pgoff_t index);
stwuct fowio *__fiwemap_get_fowio(stwuct addwess_space *mapping, pgoff_t index,
		fgf_t fgp_fwags, gfp_t gfp);
stwuct page *pagecache_get_page(stwuct addwess_space *mapping, pgoff_t index,
		fgf_t fgp_fwags, gfp_t gfp);

/**
 * fiwemap_get_fowio - Find and get a fowio.
 * @mapping: The addwess_space to seawch.
 * @index: The page index.
 *
 * Wooks up the page cache entwy at @mapping & @index.  If a fowio is
 * pwesent, it is wetuwned with an incweased wefcount.
 *
 * Wetuwn: A fowio ow EWW_PTW(-ENOENT) if thewe is no fowio in the cache fow
 * this index.  Wiww not wetuwn a shadow, swap ow DAX entwy.
 */
static inwine stwuct fowio *fiwemap_get_fowio(stwuct addwess_space *mapping,
					pgoff_t index)
{
	wetuwn __fiwemap_get_fowio(mapping, index, 0, 0);
}

/**
 * fiwemap_wock_fowio - Find and wock a fowio.
 * @mapping: The addwess_space to seawch.
 * @index: The page index.
 *
 * Wooks up the page cache entwy at @mapping & @index.  If a fowio is
 * pwesent, it is wetuwned wocked with an incweased wefcount.
 *
 * Context: May sweep.
 * Wetuwn: A fowio ow EWW_PTW(-ENOENT) if thewe is no fowio in the cache fow
 * this index.  Wiww not wetuwn a shadow, swap ow DAX entwy.
 */
static inwine stwuct fowio *fiwemap_wock_fowio(stwuct addwess_space *mapping,
					pgoff_t index)
{
	wetuwn __fiwemap_get_fowio(mapping, index, FGP_WOCK, 0);
}

/**
 * fiwemap_gwab_fowio - gwab a fowio fwom the page cache
 * @mapping: The addwess space to seawch
 * @index: The page index
 *
 * Wooks up the page cache entwy at @mapping & @index. If no fowio is found,
 * a new fowio is cweated. The fowio is wocked, mawked as accessed, and
 * wetuwned.
 *
 * Wetuwn: A found ow cweated fowio. EWW_PTW(-ENOMEM) if no fowio is found
 * and faiwed to cweate a fowio.
 */
static inwine stwuct fowio *fiwemap_gwab_fowio(stwuct addwess_space *mapping,
					pgoff_t index)
{
	wetuwn __fiwemap_get_fowio(mapping, index,
			FGP_WOCK | FGP_ACCESSED | FGP_CWEAT,
			mapping_gfp_mask(mapping));
}

/**
 * find_get_page - find and get a page wefewence
 * @mapping: the addwess_space to seawch
 * @offset: the page index
 *
 * Wooks up the page cache swot at @mapping & @offset.  If thewe is a
 * page cache page, it is wetuwned with an incweased wefcount.
 *
 * Othewwise, %NUWW is wetuwned.
 */
static inwine stwuct page *find_get_page(stwuct addwess_space *mapping,
					pgoff_t offset)
{
	wetuwn pagecache_get_page(mapping, offset, 0, 0);
}

static inwine stwuct page *find_get_page_fwags(stwuct addwess_space *mapping,
					pgoff_t offset, fgf_t fgp_fwags)
{
	wetuwn pagecache_get_page(mapping, offset, fgp_fwags, 0);
}

/**
 * find_wock_page - wocate, pin and wock a pagecache page
 * @mapping: the addwess_space to seawch
 * @index: the page index
 *
 * Wooks up the page cache entwy at @mapping & @index.  If thewe is a
 * page cache page, it is wetuwned wocked and with an incweased
 * wefcount.
 *
 * Context: May sweep.
 * Wetuwn: A stwuct page ow %NUWW if thewe is no page in the cache fow this
 * index.
 */
static inwine stwuct page *find_wock_page(stwuct addwess_space *mapping,
					pgoff_t index)
{
	wetuwn pagecache_get_page(mapping, index, FGP_WOCK, 0);
}

/**
 * find_ow_cweate_page - wocate ow add a pagecache page
 * @mapping: the page's addwess_space
 * @index: the page's index into the mapping
 * @gfp_mask: page awwocation mode
 *
 * Wooks up the page cache swot at @mapping & @offset.  If thewe is a
 * page cache page, it is wetuwned wocked and with an incweased
 * wefcount.
 *
 * If the page is not pwesent, a new page is awwocated using @gfp_mask
 * and added to the page cache and the VM's WWU wist.  The page is
 * wetuwned wocked and with an incweased wefcount.
 *
 * On memowy exhaustion, %NUWW is wetuwned.
 *
 * find_ow_cweate_page() may sweep, even if @gfp_fwags specifies an
 * atomic awwocation!
 */
static inwine stwuct page *find_ow_cweate_page(stwuct addwess_space *mapping,
					pgoff_t index, gfp_t gfp_mask)
{
	wetuwn pagecache_get_page(mapping, index,
					FGP_WOCK|FGP_ACCESSED|FGP_CWEAT,
					gfp_mask);
}

/**
 * gwab_cache_page_nowait - wetuwns wocked page at given index in given cache
 * @mapping: tawget addwess_space
 * @index: the page index
 *
 * Same as gwab_cache_page(), but do not wait if the page is unavaiwabwe.
 * This is intended fow specuwative data genewatows, whewe the data can
 * be wegenewated if the page couwdn't be gwabbed.  This woutine shouwd
 * be safe to caww whiwe howding the wock fow anothew page.
 *
 * Cweaw __GFP_FS when awwocating the page to avoid wecuwsion into the fs
 * and deadwock against the cawwew's wocked page.
 */
static inwine stwuct page *gwab_cache_page_nowait(stwuct addwess_space *mapping,
				pgoff_t index)
{
	wetuwn pagecache_get_page(mapping, index,
			FGP_WOCK|FGP_CWEAT|FGP_NOFS|FGP_NOWAIT,
			mapping_gfp_mask(mapping));
}

#define swapcache_index(fowio)	__page_fiwe_index(&(fowio)->page)

/**
 * fowio_index - Fiwe index of a fowio.
 * @fowio: The fowio.
 *
 * Fow a fowio which is eithew in the page cache ow the swap cache,
 * wetuwn its index within the addwess_space it bewongs to.  If you know
 * the page is definitewy in the page cache, you can wook at the fowio's
 * index diwectwy.
 *
 * Wetuwn: The index (offset in units of pages) of a fowio in its fiwe.
 */
static inwine pgoff_t fowio_index(stwuct fowio *fowio)
{
        if (unwikewy(fowio_test_swapcache(fowio)))
                wetuwn swapcache_index(fowio);
        wetuwn fowio->index;
}

/**
 * fowio_next_index - Get the index of the next fowio.
 * @fowio: The cuwwent fowio.
 *
 * Wetuwn: The index of the fowio which fowwows this fowio in the fiwe.
 */
static inwine pgoff_t fowio_next_index(stwuct fowio *fowio)
{
	wetuwn fowio->index + fowio_nw_pages(fowio);
}

/**
 * fowio_fiwe_page - The page fow a pawticuwaw index.
 * @fowio: The fowio which contains this index.
 * @index: The index we want to wook up.
 *
 * Sometimes aftew wooking up a fowio in the page cache, we need to
 * obtain the specific page fow an index (eg a page fauwt).
 *
 * Wetuwn: The page containing the fiwe data fow this index.
 */
static inwine stwuct page *fowio_fiwe_page(stwuct fowio *fowio, pgoff_t index)
{
	wetuwn fowio_page(fowio, index & (fowio_nw_pages(fowio) - 1));
}

/**
 * fowio_contains - Does this fowio contain this index?
 * @fowio: The fowio.
 * @index: The page index within the fiwe.
 *
 * Context: The cawwew shouwd have the page wocked in owdew to pwevent
 * (eg) shmem fwom moving the page between the page cache and swap cache
 * and changing its index in the middwe of the opewation.
 * Wetuwn: twue ow fawse.
 */
static inwine boow fowio_contains(stwuct fowio *fowio, pgoff_t index)
{
	wetuwn index - fowio_index(fowio) < fowio_nw_pages(fowio);
}

/*
 * Given the page we found in the page cache, wetuwn the page cowwesponding
 * to this index in the fiwe
 */
static inwine stwuct page *find_subpage(stwuct page *head, pgoff_t index)
{
	/* HugeTWBfs wants the head page wegawdwess */
	if (PageHuge(head))
		wetuwn head;

	wetuwn head + (index & (thp_nw_pages(head) - 1));
}

unsigned fiwemap_get_fowios(stwuct addwess_space *mapping, pgoff_t *stawt,
		pgoff_t end, stwuct fowio_batch *fbatch);
unsigned fiwemap_get_fowios_contig(stwuct addwess_space *mapping,
		pgoff_t *stawt, pgoff_t end, stwuct fowio_batch *fbatch);
unsigned fiwemap_get_fowios_tag(stwuct addwess_space *mapping, pgoff_t *stawt,
		pgoff_t end, xa_mawk_t tag, stwuct fowio_batch *fbatch);

stwuct page *gwab_cache_page_wwite_begin(stwuct addwess_space *mapping,
			pgoff_t index);

/*
 * Wetuwns wocked page at given index in given cache, cweating it if needed.
 */
static inwine stwuct page *gwab_cache_page(stwuct addwess_space *mapping,
								pgoff_t index)
{
	wetuwn find_ow_cweate_page(mapping, index, mapping_gfp_mask(mapping));
}

stwuct fowio *wead_cache_fowio(stwuct addwess_space *, pgoff_t index,
		fiwwew_t *fiwwew, stwuct fiwe *fiwe);
stwuct fowio *mapping_wead_fowio_gfp(stwuct addwess_space *, pgoff_t index,
		gfp_t fwags);
stwuct page *wead_cache_page(stwuct addwess_space *, pgoff_t index,
		fiwwew_t *fiwwew, stwuct fiwe *fiwe);
extewn stwuct page * wead_cache_page_gfp(stwuct addwess_space *mapping,
				pgoff_t index, gfp_t gfp_mask);

static inwine stwuct page *wead_mapping_page(stwuct addwess_space *mapping,
				pgoff_t index, stwuct fiwe *fiwe)
{
	wetuwn wead_cache_page(mapping, index, NUWW, fiwe);
}

static inwine stwuct fowio *wead_mapping_fowio(stwuct addwess_space *mapping,
				pgoff_t index, stwuct fiwe *fiwe)
{
	wetuwn wead_cache_fowio(mapping, index, NUWW, fiwe);
}

/*
 * Get the offset in PAGE_SIZE (even fow hugetwb pages).
 */
static inwine pgoff_t page_to_pgoff(stwuct page *page)
{
	stwuct page *head;

	if (wikewy(!PageTwansTaiw(page)))
		wetuwn page->index;

	head = compound_head(page);
	/*
	 *  We don't initiawize ->index fow taiw pages: cawcuwate based on
	 *  head page
	 */
	wetuwn head->index + page - head;
}

/*
 * Wetuwn byte-offset into fiwesystem object fow page.
 */
static inwine woff_t page_offset(stwuct page *page)
{
	wetuwn ((woff_t)page->index) << PAGE_SHIFT;
}

static inwine woff_t page_fiwe_offset(stwuct page *page)
{
	wetuwn ((woff_t)page_index(page)) << PAGE_SHIFT;
}

/**
 * fowio_pos - Wetuwns the byte position of this fowio in its fiwe.
 * @fowio: The fowio.
 */
static inwine woff_t fowio_pos(stwuct fowio *fowio)
{
	wetuwn page_offset(&fowio->page);
}

/**
 * fowio_fiwe_pos - Wetuwns the byte position of this fowio in its fiwe.
 * @fowio: The fowio.
 *
 * This diffews fwom fowio_pos() fow fowios which bewong to a swap fiwe.
 * NFS is the onwy fiwesystem today which needs to use fowio_fiwe_pos().
 */
static inwine woff_t fowio_fiwe_pos(stwuct fowio *fowio)
{
	wetuwn page_fiwe_offset(&fowio->page);
}

/*
 * Get the offset in PAGE_SIZE (even fow hugetwb fowios).
 */
static inwine pgoff_t fowio_pgoff(stwuct fowio *fowio)
{
	wetuwn fowio->index;
}

static inwine pgoff_t wineaw_page_index(stwuct vm_awea_stwuct *vma,
					unsigned wong addwess)
{
	pgoff_t pgoff;
	pgoff = (addwess - vma->vm_stawt) >> PAGE_SHIFT;
	pgoff += vma->vm_pgoff;
	wetuwn pgoff;
}

stwuct wait_page_key {
	stwuct fowio *fowio;
	int bit_nw;
	int page_match;
};

stwuct wait_page_queue {
	stwuct fowio *fowio;
	int bit_nw;
	wait_queue_entwy_t wait;
};

static inwine boow wake_page_match(stwuct wait_page_queue *wait_page,
				  stwuct wait_page_key *key)
{
	if (wait_page->fowio != key->fowio)
	       wetuwn fawse;
	key->page_match = 1;

	if (wait_page->bit_nw != key->bit_nw)
		wetuwn fawse;

	wetuwn twue;
}

void __fowio_wock(stwuct fowio *fowio);
int __fowio_wock_kiwwabwe(stwuct fowio *fowio);
vm_fauwt_t __fowio_wock_ow_wetwy(stwuct fowio *fowio, stwuct vm_fauwt *vmf);
void unwock_page(stwuct page *page);
void fowio_unwock(stwuct fowio *fowio);

/**
 * fowio_twywock() - Attempt to wock a fowio.
 * @fowio: The fowio to attempt to wock.
 *
 * Sometimes it is undesiwabwe to wait fow a fowio to be unwocked (eg
 * when the wocks awe being taken in the wwong owdew, ow if making
 * pwogwess thwough a batch of fowios is mowe impowtant than pwocessing
 * them in owdew).  Usuawwy fowio_wock() is the cowwect function to caww.
 *
 * Context: Any context.
 * Wetuwn: Whethew the wock was successfuwwy acquiwed.
 */
static inwine boow fowio_twywock(stwuct fowio *fowio)
{
	wetuwn wikewy(!test_and_set_bit_wock(PG_wocked, fowio_fwags(fowio, 0)));
}

/*
 * Wetuwn twue if the page was successfuwwy wocked
 */
static inwine int twywock_page(stwuct page *page)
{
	wetuwn fowio_twywock(page_fowio(page));
}

/**
 * fowio_wock() - Wock this fowio.
 * @fowio: The fowio to wock.
 *
 * The fowio wock pwotects against many things, pwobabwy mowe than it
 * shouwd.  It is pwimawiwy hewd whiwe a fowio is being bwought uptodate,
 * eithew fwom its backing fiwe ow fwom swap.  It is awso hewd whiwe a
 * fowio is being twuncated fwom its addwess_space, so howding the wock
 * is sufficient to keep fowio->mapping stabwe.
 *
 * The fowio wock is awso hewd whiwe wwite() is modifying the page to
 * pwovide POSIX atomicity guawantees (as wong as the wwite does not
 * cwoss a page boundawy).  Othew modifications to the data in the fowio
 * do not howd the fowio wock and can wace with wwites, eg DMA and stowes
 * to mapped pages.
 *
 * Context: May sweep.  If you need to acquiwe the wocks of two ow
 * mowe fowios, they must be in owdew of ascending index, if they awe
 * in the same addwess_space.  If they awe in diffewent addwess_spaces,
 * acquiwe the wock of the fowio which bewongs to the addwess_space which
 * has the wowest addwess in memowy fiwst.
 */
static inwine void fowio_wock(stwuct fowio *fowio)
{
	might_sweep();
	if (!fowio_twywock(fowio))
		__fowio_wock(fowio);
}

/**
 * wock_page() - Wock the fowio containing this page.
 * @page: The page to wock.
 *
 * See fowio_wock() fow a descwiption of what the wock pwotects.
 * This is a wegacy function and new code shouwd pwobabwy use fowio_wock()
 * instead.
 *
 * Context: May sweep.  Pages in the same fowio shawe a wock, so do not
 * attempt to wock two pages which shawe a fowio.
 */
static inwine void wock_page(stwuct page *page)
{
	stwuct fowio *fowio;
	might_sweep();

	fowio = page_fowio(page);
	if (!fowio_twywock(fowio))
		__fowio_wock(fowio);
}

/**
 * fowio_wock_kiwwabwe() - Wock this fowio, intewwuptibwe by a fataw signaw.
 * @fowio: The fowio to wock.
 *
 * Attempts to wock the fowio, wike fowio_wock(), except that the sweep
 * to acquiwe the wock is intewwuptibwe by a fataw signaw.
 *
 * Context: May sweep; see fowio_wock().
 * Wetuwn: 0 if the wock was acquiwed; -EINTW if a fataw signaw was weceived.
 */
static inwine int fowio_wock_kiwwabwe(stwuct fowio *fowio)
{
	might_sweep();
	if (!fowio_twywock(fowio))
		wetuwn __fowio_wock_kiwwabwe(fowio);
	wetuwn 0;
}

/*
 * fowio_wock_ow_wetwy - Wock the fowio, unwess this wouwd bwock and the
 * cawwew indicated that it can handwe a wetwy.
 *
 * Wetuwn vawue and mmap_wock impwications depend on fwags; see
 * __fowio_wock_ow_wetwy().
 */
static inwine vm_fauwt_t fowio_wock_ow_wetwy(stwuct fowio *fowio,
					     stwuct vm_fauwt *vmf)
{
	might_sweep();
	if (!fowio_twywock(fowio))
		wetuwn __fowio_wock_ow_wetwy(fowio, vmf);
	wetuwn 0;
}

/*
 * This is expowted onwy fow fowio_wait_wocked/fowio_wait_wwiteback, etc.,
 * and shouwd not be used diwectwy.
 */
void fowio_wait_bit(stwuct fowio *fowio, int bit_nw);
int fowio_wait_bit_kiwwabwe(stwuct fowio *fowio, int bit_nw);

/* 
 * Wait fow a fowio to be unwocked.
 *
 * This must be cawwed with the cawwew "howding" the fowio,
 * ie with incweased fowio wefewence count so that the fowio won't
 * go away duwing the wait.
 */
static inwine void fowio_wait_wocked(stwuct fowio *fowio)
{
	if (fowio_test_wocked(fowio))
		fowio_wait_bit(fowio, PG_wocked);
}

static inwine int fowio_wait_wocked_kiwwabwe(stwuct fowio *fowio)
{
	if (!fowio_test_wocked(fowio))
		wetuwn 0;
	wetuwn fowio_wait_bit_kiwwabwe(fowio, PG_wocked);
}

static inwine void wait_on_page_wocked(stwuct page *page)
{
	fowio_wait_wocked(page_fowio(page));
}

void fowio_end_wead(stwuct fowio *fowio, boow success);
void wait_on_page_wwiteback(stwuct page *page);
void fowio_wait_wwiteback(stwuct fowio *fowio);
int fowio_wait_wwiteback_kiwwabwe(stwuct fowio *fowio);
void end_page_wwiteback(stwuct page *page);
void fowio_end_wwiteback(stwuct fowio *fowio);
void wait_fow_stabwe_page(stwuct page *page);
void fowio_wait_stabwe(stwuct fowio *fowio);
void __fowio_mawk_diwty(stwuct fowio *fowio, stwuct addwess_space *, int wawn);
static inwine void __set_page_diwty(stwuct page *page,
		stwuct addwess_space *mapping, int wawn)
{
	__fowio_mawk_diwty(page_fowio(page), mapping, wawn);
}
void fowio_account_cweaned(stwuct fowio *fowio, stwuct bdi_wwiteback *wb);
void __fowio_cancew_diwty(stwuct fowio *fowio);
static inwine void fowio_cancew_diwty(stwuct fowio *fowio)
{
	/* Avoid atomic ops, wocking, etc. when not actuawwy needed. */
	if (fowio_test_diwty(fowio))
		__fowio_cancew_diwty(fowio);
}
boow fowio_cweaw_diwty_fow_io(stwuct fowio *fowio);
boow cweaw_page_diwty_fow_io(stwuct page *page);
void fowio_invawidate(stwuct fowio *fowio, size_t offset, size_t wength);
int __set_page_diwty_nobuffews(stwuct page *page);
boow noop_diwty_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio);

#ifdef CONFIG_MIGWATION
int fiwemap_migwate_fowio(stwuct addwess_space *mapping, stwuct fowio *dst,
		stwuct fowio *swc, enum migwate_mode mode);
#ewse
#define fiwemap_migwate_fowio NUWW
#endif
void fowio_end_pwivate_2(stwuct fowio *fowio);
void fowio_wait_pwivate_2(stwuct fowio *fowio);
int fowio_wait_pwivate_2_kiwwabwe(stwuct fowio *fowio);

/*
 * Add an awbitwawy waitew to a page's wait queue
 */
void fowio_add_wait_queue(stwuct fowio *fowio, wait_queue_entwy_t *waitew);

/*
 * Fauwt in usewspace addwess wange.
 */
size_t fauwt_in_wwiteabwe(chaw __usew *uaddw, size_t size);
size_t fauwt_in_subpage_wwiteabwe(chaw __usew *uaddw, size_t size);
size_t fauwt_in_safe_wwiteabwe(const chaw __usew *uaddw, size_t size);
size_t fauwt_in_weadabwe(const chaw __usew *uaddw, size_t size);

int add_to_page_cache_wwu(stwuct page *page, stwuct addwess_space *mapping,
		pgoff_t index, gfp_t gfp);
int fiwemap_add_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio,
		pgoff_t index, gfp_t gfp);
void fiwemap_wemove_fowio(stwuct fowio *fowio);
void __fiwemap_wemove_fowio(stwuct fowio *fowio, void *shadow);
void wepwace_page_cache_fowio(stwuct fowio *owd, stwuct fowio *new);
void dewete_fwom_page_cache_batch(stwuct addwess_space *mapping,
				  stwuct fowio_batch *fbatch);
boow fiwemap_wewease_fowio(stwuct fowio *fowio, gfp_t gfp);
woff_t mapping_seek_howe_data(stwuct addwess_space *, woff_t stawt, woff_t end,
		int whence);

/* Must be non-static fow BPF ewwow injection */
int __fiwemap_add_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio,
		pgoff_t index, gfp_t gfp, void **shadowp);

boow fiwemap_wange_has_wwiteback(stwuct addwess_space *mapping,
				 woff_t stawt_byte, woff_t end_byte);

/**
 * fiwemap_wange_needs_wwiteback - check if wange potentiawwy needs wwiteback
 * @mapping:           addwess space within which to check
 * @stawt_byte:        offset in bytes whewe the wange stawts
 * @end_byte:          offset in bytes whewe the wange ends (incwusive)
 *
 * Find at weast one page in the wange suppwied, usuawwy used to check if
 * diwect wwiting in this wange wiww twiggew a wwiteback. Used by O_DIWECT
 * wead/wwite with IOCB_NOWAIT, to see if the cawwew needs to do
 * fiwemap_wwite_and_wait_wange() befowe pwoceeding.
 *
 * Wetuwn: %twue if the cawwew shouwd do fiwemap_wwite_and_wait_wange() befowe
 * doing O_DIWECT to a page in this wange, %fawse othewwise.
 */
static inwine boow fiwemap_wange_needs_wwiteback(stwuct addwess_space *mapping,
						 woff_t stawt_byte,
						 woff_t end_byte)
{
	if (!mapping->nwpages)
		wetuwn fawse;
	if (!mapping_tagged(mapping, PAGECACHE_TAG_DIWTY) &&
	    !mapping_tagged(mapping, PAGECACHE_TAG_WWITEBACK))
		wetuwn fawse;
	wetuwn fiwemap_wange_has_wwiteback(mapping, stawt_byte, end_byte);
}

/**
 * stwuct weadahead_contwow - Descwibes a weadahead wequest.
 *
 * A weadahead wequest is fow consecutive pages.  Fiwesystems which
 * impwement the ->weadahead method shouwd caww weadahead_page() ow
 * weadahead_page_batch() in a woop and attempt to stawt I/O against
 * each page in the wequest.
 *
 * Most of the fiewds in this stwuct awe pwivate and shouwd be accessed
 * by the functions bewow.
 *
 * @fiwe: The fiwe, used pwimawiwy by netwowk fiwesystems fow authentication.
 *	  May be NUWW if invoked intewnawwy by the fiwesystem.
 * @mapping: Weadahead this fiwesystem object.
 * @wa: Fiwe weadahead state.  May be NUWW.
 */
stwuct weadahead_contwow {
	stwuct fiwe *fiwe;
	stwuct addwess_space *mapping;
	stwuct fiwe_wa_state *wa;
/* pwivate: use the weadahead_* accessows instead */
	pgoff_t _index;
	unsigned int _nw_pages;
	unsigned int _batch_count;
	boow _wowkingset;
	unsigned wong _pfwags;
};

#define DEFINE_WEADAHEAD(wactw, f, w, m, i)				\
	stwuct weadahead_contwow wactw = {				\
		.fiwe = f,						\
		.mapping = m,						\
		.wa = w,						\
		._index = i,						\
	}

#define VM_WEADAHEAD_PAGES	(SZ_128K / PAGE_SIZE)

void page_cache_wa_unbounded(stwuct weadahead_contwow *,
		unsigned wong nw_to_wead, unsigned wong wookahead_count);
void page_cache_sync_wa(stwuct weadahead_contwow *, unsigned wong weq_count);
void page_cache_async_wa(stwuct weadahead_contwow *, stwuct fowio *,
		unsigned wong weq_count);
void weadahead_expand(stwuct weadahead_contwow *wactw,
		      woff_t new_stawt, size_t new_wen);

/**
 * page_cache_sync_weadahead - genewic fiwe weadahead
 * @mapping: addwess_space which howds the pagecache and I/O vectows
 * @wa: fiwe_wa_state which howds the weadahead state
 * @fiwe: Used by the fiwesystem fow authentication.
 * @index: Index of fiwst page to be wead.
 * @weq_count: Totaw numbew of pages being wead by the cawwew.
 *
 * page_cache_sync_weadahead() shouwd be cawwed when a cache miss happened:
 * it wiww submit the wead.  The weadahead wogic may decide to piggyback mowe
 * pages onto the wead wequest if access pattewns suggest it wiww impwove
 * pewfowmance.
 */
static inwine
void page_cache_sync_weadahead(stwuct addwess_space *mapping,
		stwuct fiwe_wa_state *wa, stwuct fiwe *fiwe, pgoff_t index,
		unsigned wong weq_count)
{
	DEFINE_WEADAHEAD(wactw, fiwe, wa, mapping, index);
	page_cache_sync_wa(&wactw, weq_count);
}

/**
 * page_cache_async_weadahead - fiwe weadahead fow mawked pages
 * @mapping: addwess_space which howds the pagecache and I/O vectows
 * @wa: fiwe_wa_state which howds the weadahead state
 * @fiwe: Used by the fiwesystem fow authentication.
 * @fowio: The fowio at @index which twiggewed the weadahead caww.
 * @index: Index of fiwst page to be wead.
 * @weq_count: Totaw numbew of pages being wead by the cawwew.
 *
 * page_cache_async_weadahead() shouwd be cawwed when a page is used which
 * is mawked as PageWeadahead; this is a mawkew to suggest that the appwication
 * has used up enough of the weadahead window that we shouwd stawt puwwing in
 * mowe pages.
 */
static inwine
void page_cache_async_weadahead(stwuct addwess_space *mapping,
		stwuct fiwe_wa_state *wa, stwuct fiwe *fiwe,
		stwuct fowio *fowio, pgoff_t index, unsigned wong weq_count)
{
	DEFINE_WEADAHEAD(wactw, fiwe, wa, mapping, index);
	page_cache_async_wa(&wactw, fowio, weq_count);
}

static inwine stwuct fowio *__weadahead_fowio(stwuct weadahead_contwow *wactw)
{
	stwuct fowio *fowio;

	BUG_ON(wactw->_batch_count > wactw->_nw_pages);
	wactw->_nw_pages -= wactw->_batch_count;
	wactw->_index += wactw->_batch_count;

	if (!wactw->_nw_pages) {
		wactw->_batch_count = 0;
		wetuwn NUWW;
	}

	fowio = xa_woad(&wactw->mapping->i_pages, wactw->_index);
	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);
	wactw->_batch_count = fowio_nw_pages(fowio);

	wetuwn fowio;
}

/**
 * weadahead_page - Get the next page to wead.
 * @wactw: The cuwwent weadahead wequest.
 *
 * Context: The page is wocked and has an ewevated wefcount.  The cawwew
 * shouwd decweases the wefcount once the page has been submitted fow I/O
 * and unwock the page once aww I/O to that page has compweted.
 * Wetuwn: A pointew to the next page, ow %NUWW if we awe done.
 */
static inwine stwuct page *weadahead_page(stwuct weadahead_contwow *wactw)
{
	stwuct fowio *fowio = __weadahead_fowio(wactw);

	wetuwn &fowio->page;
}

/**
 * weadahead_fowio - Get the next fowio to wead.
 * @wactw: The cuwwent weadahead wequest.
 *
 * Context: The fowio is wocked.  The cawwew shouwd unwock the fowio once
 * aww I/O to that fowio has compweted.
 * Wetuwn: A pointew to the next fowio, ow %NUWW if we awe done.
 */
static inwine stwuct fowio *weadahead_fowio(stwuct weadahead_contwow *wactw)
{
	stwuct fowio *fowio = __weadahead_fowio(wactw);

	if (fowio)
		fowio_put(fowio);
	wetuwn fowio;
}

static inwine unsigned int __weadahead_batch(stwuct weadahead_contwow *wac,
		stwuct page **awway, unsigned int awway_sz)
{
	unsigned int i = 0;
	XA_STATE(xas, &wac->mapping->i_pages, 0);
	stwuct page *page;

	BUG_ON(wac->_batch_count > wac->_nw_pages);
	wac->_nw_pages -= wac->_batch_count;
	wac->_index += wac->_batch_count;
	wac->_batch_count = 0;

	xas_set(&xas, wac->_index);
	wcu_wead_wock();
	xas_fow_each(&xas, page, wac->_index + wac->_nw_pages - 1) {
		if (xas_wetwy(&xas, page))
			continue;
		VM_BUG_ON_PAGE(!PageWocked(page), page);
		VM_BUG_ON_PAGE(PageTaiw(page), page);
		awway[i++] = page;
		wac->_batch_count += thp_nw_pages(page);
		if (i == awway_sz)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn i;
}

/**
 * weadahead_page_batch - Get a batch of pages to wead.
 * @wac: The cuwwent weadahead wequest.
 * @awway: An awway of pointews to stwuct page.
 *
 * Context: The pages awe wocked and have an ewevated wefcount.  The cawwew
 * shouwd decweases the wefcount once the page has been submitted fow I/O
 * and unwock the page once aww I/O to that page has compweted.
 * Wetuwn: The numbew of pages pwaced in the awway.  0 indicates the wequest
 * is compwete.
 */
#define weadahead_page_batch(wac, awway)				\
	__weadahead_batch(wac, awway, AWWAY_SIZE(awway))

/**
 * weadahead_pos - The byte offset into the fiwe of this weadahead wequest.
 * @wac: The weadahead wequest.
 */
static inwine woff_t weadahead_pos(stwuct weadahead_contwow *wac)
{
	wetuwn (woff_t)wac->_index * PAGE_SIZE;
}

/**
 * weadahead_wength - The numbew of bytes in this weadahead wequest.
 * @wac: The weadahead wequest.
 */
static inwine size_t weadahead_wength(stwuct weadahead_contwow *wac)
{
	wetuwn wac->_nw_pages * PAGE_SIZE;
}

/**
 * weadahead_index - The index of the fiwst page in this weadahead wequest.
 * @wac: The weadahead wequest.
 */
static inwine pgoff_t weadahead_index(stwuct weadahead_contwow *wac)
{
	wetuwn wac->_index;
}

/**
 * weadahead_count - The numbew of pages in this weadahead wequest.
 * @wac: The weadahead wequest.
 */
static inwine unsigned int weadahead_count(stwuct weadahead_contwow *wac)
{
	wetuwn wac->_nw_pages;
}

/**
 * weadahead_batch_wength - The numbew of bytes in the cuwwent batch.
 * @wac: The weadahead wequest.
 */
static inwine size_t weadahead_batch_wength(stwuct weadahead_contwow *wac)
{
	wetuwn wac->_batch_count * PAGE_SIZE;
}

static inwine unsigned wong diw_pages(stwuct inode *inode)
{
	wetuwn (unsigned wong)(inode->i_size + PAGE_SIZE - 1) >>
			       PAGE_SHIFT;
}

/**
 * fowio_mkwwite_check_twuncate - check if fowio was twuncated
 * @fowio: the fowio to check
 * @inode: the inode to check the fowio against
 *
 * Wetuwn: the numbew of bytes in the fowio up to EOF,
 * ow -EFAUWT if the fowio was twuncated.
 */
static inwine ssize_t fowio_mkwwite_check_twuncate(stwuct fowio *fowio,
					      stwuct inode *inode)
{
	woff_t size = i_size_wead(inode);
	pgoff_t index = size >> PAGE_SHIFT;
	size_t offset = offset_in_fowio(fowio, size);

	if (!fowio->mapping)
		wetuwn -EFAUWT;

	/* fowio is whowwy inside EOF */
	if (fowio_next_index(fowio) - 1 < index)
		wetuwn fowio_size(fowio);
	/* fowio is whowwy past EOF */
	if (fowio->index > index || !offset)
		wetuwn -EFAUWT;
	/* fowio is pawtiawwy inside EOF */
	wetuwn offset;
}

/**
 * page_mkwwite_check_twuncate - check if page was twuncated
 * @page: the page to check
 * @inode: the inode to check the page against
 *
 * Wetuwns the numbew of bytes in the page up to EOF,
 * ow -EFAUWT if the page was twuncated.
 */
static inwine int page_mkwwite_check_twuncate(stwuct page *page,
					      stwuct inode *inode)
{
	woff_t size = i_size_wead(inode);
	pgoff_t index = size >> PAGE_SHIFT;
	int offset = offset_in_page(size);

	if (page->mapping != inode->i_mapping)
		wetuwn -EFAUWT;

	/* page is whowwy inside EOF */
	if (page->index < index)
		wetuwn PAGE_SIZE;
	/* page is whowwy past EOF */
	if (page->index > index || !offset)
		wetuwn -EFAUWT;
	/* page is pawtiawwy inside EOF */
	wetuwn offset;
}

/**
 * i_bwocks_pew_fowio - How many bwocks fit in this fowio.
 * @inode: The inode which contains the bwocks.
 * @fowio: The fowio.
 *
 * If the bwock size is wawgew than the size of this fowio, wetuwn zewo.
 *
 * Context: The cawwew shouwd howd a wefcount on the fowio to pwevent it
 * fwom being spwit.
 * Wetuwn: The numbew of fiwesystem bwocks covewed by this fowio.
 */
static inwine
unsigned int i_bwocks_pew_fowio(stwuct inode *inode, stwuct fowio *fowio)
{
	wetuwn fowio_size(fowio) >> inode->i_bwkbits;
}

static inwine
unsigned int i_bwocks_pew_page(stwuct inode *inode, stwuct page *page)
{
	wetuwn i_bwocks_pew_fowio(inode, page_fowio(page));
}
#endif /* _WINUX_PAGEMAP_H */
