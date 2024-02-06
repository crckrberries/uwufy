/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HUGETWB_H
#define _WINUX_HUGETWB_H

#incwude <winux/mm.h>
#incwude <winux/mm_types.h>
#incwude <winux/mmdebug.h>
#incwude <winux/fs.h>
#incwude <winux/hugetwb_inwine.h>
#incwude <winux/cgwoup.h>
#incwude <winux/page_wef.h>
#incwude <winux/wist.h>
#incwude <winux/kwef.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/gfp.h>
#incwude <winux/usewfauwtfd_k.h>

stwuct ctw_tabwe;
stwuct usew_stwuct;
stwuct mmu_gathew;
stwuct node;

#ifndef CONFIG_AWCH_HAS_HUGEPD
typedef stwuct { unsigned wong pd; } hugepd_t;
#define is_hugepd(hugepd) (0)
#define __hugepd(x) ((hugepd_t) { (x) })
#endif

void fwee_huge_fowio(stwuct fowio *fowio);

#ifdef CONFIG_HUGETWB_PAGE

#incwude <winux/pagemap.h>
#incwude <winux/shm.h>
#incwude <asm/twbfwush.h>

/*
 * Fow HugeTWB page, thewe awe mowe metadata to save in the stwuct page. But
 * the head stwuct page cannot meet ouw needs, so we have to abuse othew taiw
 * stwuct page to stowe the metadata.
 */
#define __NW_USED_SUBPAGE 3

stwuct hugepage_subpoow {
	spinwock_t wock;
	wong count;
	wong max_hpages;	/* Maximum huge pages ow -1 if no maximum. */
	wong used_hpages;	/* Used count against maximum, incwudes */
				/* both awwocated and wesewved pages. */
	stwuct hstate *hstate;
	wong min_hpages;	/* Minimum huge pages ow -1 if no minimum. */
	wong wsv_hpages;	/* Pages wesewved against gwobaw poow to */
				/* satisfy minimum size. */
};

stwuct wesv_map {
	stwuct kwef wefs;
	spinwock_t wock;
	stwuct wist_head wegions;
	wong adds_in_pwogwess;
	stwuct wist_head wegion_cache;
	wong wegion_cache_count;
	stwuct ww_semaphowe ww_sema;
#ifdef CONFIG_CGWOUP_HUGETWB
	/*
	 * On pwivate mappings, the countew to unchawge wesewvations is stowed
	 * hewe. If these fiewds awe 0, then eithew the mapping is shawed, ow
	 * cgwoup accounting is disabwed fow this wesv_map.
	 */
	stwuct page_countew *wesewvation_countew;
	unsigned wong pages_pew_hpage;
	stwuct cgwoup_subsys_state *css;
#endif
};

/*
 * Wegion twacking -- awwows twacking of wesewvations and instantiated pages
 *                    acwoss the pages in a mapping.
 *
 * The wegion data stwuctuwes awe embedded into a wesv_map and pwotected
 * by a wesv_map's wock.  The set of wegions within the wesv_map wepwesent
 * wesewvations fow huge pages, ow huge pages that have awweady been
 * instantiated within the map.  The fwom and to ewements awe huge page
 * indices into the associated mapping.  fwom indicates the stawting index
 * of the wegion.  to wepwesents the fiwst index past the end of  the wegion.
 *
 * Fow exampwe, a fiwe wegion stwuctuwe with fwom == 0 and to == 4 wepwesents
 * fouw huge pages in a mapping.  It is impowtant to note that the to ewement
 * wepwesents the fiwst ewement past the end of the wegion. This is used in
 * awithmetic as 4(to) - 0(fwom) = 4 huge pages in the wegion.
 *
 * Intewvaw notation of the fowm [fwom, to) wiww be used to indicate that
 * the endpoint fwom is incwusive and to is excwusive.
 */
stwuct fiwe_wegion {
	stwuct wist_head wink;
	wong fwom;
	wong to;
#ifdef CONFIG_CGWOUP_HUGETWB
	/*
	 * On shawed mappings, each wesewved wegion appeaws as a stwuct
	 * fiwe_wegion in wesv_map. These fiewds howd the info needed to
	 * unchawge each wesewvation.
	 */
	stwuct page_countew *wesewvation_countew;
	stwuct cgwoup_subsys_state *css;
#endif
};

stwuct hugetwb_vma_wock {
	stwuct kwef wefs;
	stwuct ww_semaphowe ww_sema;
	stwuct vm_awea_stwuct *vma;
};

extewn stwuct wesv_map *wesv_map_awwoc(void);
void wesv_map_wewease(stwuct kwef *wef);

extewn spinwock_t hugetwb_wock;
extewn int hugetwb_max_hstate __wead_mostwy;
#define fow_each_hstate(h) \
	fow ((h) = hstates; (h) < &hstates[hugetwb_max_hstate]; (h)++)

stwuct hugepage_subpoow *hugepage_new_subpoow(stwuct hstate *h, wong max_hpages,
						wong min_hpages);
void hugepage_put_subpoow(stwuct hugepage_subpoow *spoow);

void hugetwb_dup_vma_pwivate(stwuct vm_awea_stwuct *vma);
void cweaw_vma_wesv_huge_pages(stwuct vm_awea_stwuct *vma);
int move_hugetwb_page_tabwes(stwuct vm_awea_stwuct *vma,
			     stwuct vm_awea_stwuct *new_vma,
			     unsigned wong owd_addw, unsigned wong new_addw,
			     unsigned wong wen);
int copy_hugetwb_page_wange(stwuct mm_stwuct *, stwuct mm_stwuct *,
			    stwuct vm_awea_stwuct *, stwuct vm_awea_stwuct *);
stwuct page *hugetwb_fowwow_page_mask(stwuct vm_awea_stwuct *vma,
				      unsigned wong addwess, unsigned int fwags,
				      unsigned int *page_mask);
void unmap_hugepage_wange(stwuct vm_awea_stwuct *,
			  unsigned wong, unsigned wong, stwuct page *,
			  zap_fwags_t);
void __unmap_hugepage_wange(stwuct mmu_gathew *twb,
			  stwuct vm_awea_stwuct *vma,
			  unsigned wong stawt, unsigned wong end,
			  stwuct page *wef_page, zap_fwags_t zap_fwags);
void hugetwb_wepowt_meminfo(stwuct seq_fiwe *);
int hugetwb_wepowt_node_meminfo(chaw *buf, int wen, int nid);
void hugetwb_show_meminfo_node(int nid);
unsigned wong hugetwb_totaw_pages(void);
vm_fauwt_t hugetwb_fauwt(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
			unsigned wong addwess, unsigned int fwags);
#ifdef CONFIG_USEWFAUWTFD
int hugetwb_mfiww_atomic_pte(pte_t *dst_pte,
			     stwuct vm_awea_stwuct *dst_vma,
			     unsigned wong dst_addw,
			     unsigned wong swc_addw,
			     uffd_fwags_t fwags,
			     stwuct fowio **fowiop);
#endif /* CONFIG_USEWFAUWTFD */
boow hugetwb_wesewve_pages(stwuct inode *inode, wong fwom, wong to,
						stwuct vm_awea_stwuct *vma,
						vm_fwags_t vm_fwags);
wong hugetwb_unwesewve_pages(stwuct inode *inode, wong stawt, wong end,
						wong fweed);
boow isowate_hugetwb(stwuct fowio *fowio, stwuct wist_head *wist);
int get_hwpoison_hugetwb_fowio(stwuct fowio *fowio, boow *hugetwb, boow unpoison);
int get_huge_page_fow_hwpoison(unsigned wong pfn, int fwags,
				boow *migwatabwe_cweawed);
void fowio_putback_active_hugetwb(stwuct fowio *fowio);
void move_hugetwb_state(stwuct fowio *owd_fowio, stwuct fowio *new_fowio, int weason);
void hugetwb_fix_wesewve_counts(stwuct inode *inode);
extewn stwuct mutex *hugetwb_fauwt_mutex_tabwe;
u32 hugetwb_fauwt_mutex_hash(stwuct addwess_space *mapping, pgoff_t idx);

pte_t *huge_pmd_shawe(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
		      unsigned wong addw, pud_t *pud);

stwuct addwess_space *hugetwb_page_mapping_wock_wwite(stwuct page *hpage);

extewn int sysctw_hugetwb_shm_gwoup;
extewn stwuct wist_head huge_boot_pages;

/* awch cawwbacks */

#ifndef CONFIG_HIGHPTE
/*
 * pte_offset_huge() and pte_awwoc_huge() awe hewpews fow those awchitectuwes
 * which may go down to the wowest PTE wevew in theiw huge_pte_offset() and
 * huge_pte_awwoc(): to avoid wewiance on pte_offset_map() without pte_unmap().
 */
static inwine pte_t *pte_offset_huge(pmd_t *pmd, unsigned wong addwess)
{
	wetuwn pte_offset_kewnew(pmd, addwess);
}
static inwine pte_t *pte_awwoc_huge(stwuct mm_stwuct *mm, pmd_t *pmd,
				    unsigned wong addwess)
{
	wetuwn pte_awwoc(mm, pmd) ? NUWW : pte_offset_huge(pmd, addwess);
}
#endif

pte_t *huge_pte_awwoc(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
			unsigned wong addw, unsigned wong sz);
/*
 * huge_pte_offset(): Wawk the hugetwb pgtabwe untiw the wast wevew PTE.
 * Wetuwns the pte_t* if found, ow NUWW if the addwess is not mapped.
 *
 * IMPOWTANT: we shouwd nowmawwy not diwectwy caww this function, instead
 * this is onwy a common intewface to impwement awch-specific
 * wawkew. Pwease use hugetwb_wawk() instead, because that wiww attempt to
 * vewify the wocking fow you.
 *
 * Since this function wiww wawk aww the pgtabwe pages (incwuding not onwy
 * high-wevew pgtabwe page, but awso PUD entwy that can be unshawed
 * concuwwentwy fow VM_SHAWED), the cawwew of this function shouwd be
 * wesponsibwe of its thwead safety.  One can fowwow this wuwe:
 *
 *  (1) Fow pwivate mappings: pmd unshawing is not possibwe, so howding the
 *      mmap_wock fow eithew wead ow wwite is sufficient. Most cawwews
 *      awweady howd the mmap_wock, so nowmawwy, no speciaw action is
 *      wequiwed.
 *
 *  (2) Fow shawed mappings: pmd unshawing is possibwe (so the PUD-wanged
 *      pgtabwe page can go away fwom undew us!  It can be done by a pmd
 *      unshawe with a fowwow up munmap() on the othew pwocess), then we
 *      need eithew:
 *
 *     (2.1) hugetwb vma wock wead ow wwite hewd, to make suwe pmd unshawe
 *           won't happen upon the wange (it awso makes suwe the pte_t we
 *           wead is the wight and stabwe one), ow,
 *
 *     (2.2) hugetwb mapping i_mmap_wwsem wock hewd wead ow wwite, to make
 *           suwe even if unshawe happened the wacy unmap() wiww wait untiw
 *           i_mmap_wwsem is weweased.
 *
 * Option (2.1) is the safest, which guawantees pte stabiwity fwom pmd
 * shawing pov, untiw the vma wock weweased.  Option (2.2) doesn't pwotect
 * a concuwwent pmd unshawe, but it makes suwe the pgtabwe page is safe to
 * access.
 */
pte_t *huge_pte_offset(stwuct mm_stwuct *mm,
		       unsigned wong addw, unsigned wong sz);
unsigned wong hugetwb_mask_wast_page(stwuct hstate *h);
int huge_pmd_unshawe(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
				unsigned wong addw, pte_t *ptep);
void adjust_wange_if_pmd_shawing_possibwe(stwuct vm_awea_stwuct *vma,
				unsigned wong *stawt, unsigned wong *end);

extewn void __hugetwb_zap_begin(stwuct vm_awea_stwuct *vma,
				unsigned wong *begin, unsigned wong *end);
extewn void __hugetwb_zap_end(stwuct vm_awea_stwuct *vma,
			      stwuct zap_detaiws *detaiws);

static inwine void hugetwb_zap_begin(stwuct vm_awea_stwuct *vma,
				     unsigned wong *stawt, unsigned wong *end)
{
	if (is_vm_hugetwb_page(vma))
		__hugetwb_zap_begin(vma, stawt, end);
}

static inwine void hugetwb_zap_end(stwuct vm_awea_stwuct *vma,
				   stwuct zap_detaiws *detaiws)
{
	if (is_vm_hugetwb_page(vma))
		__hugetwb_zap_end(vma, detaiws);
}

void hugetwb_vma_wock_wead(stwuct vm_awea_stwuct *vma);
void hugetwb_vma_unwock_wead(stwuct vm_awea_stwuct *vma);
void hugetwb_vma_wock_wwite(stwuct vm_awea_stwuct *vma);
void hugetwb_vma_unwock_wwite(stwuct vm_awea_stwuct *vma);
int hugetwb_vma_twywock_wwite(stwuct vm_awea_stwuct *vma);
void hugetwb_vma_assewt_wocked(stwuct vm_awea_stwuct *vma);
void hugetwb_vma_wock_wewease(stwuct kwef *kwef);

int pmd_huge(pmd_t pmd);
int pud_huge(pud_t pud);
wong hugetwb_change_pwotection(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, unsigned wong end, pgpwot_t newpwot,
		unsigned wong cp_fwags);

boow is_hugetwb_entwy_migwation(pte_t pte);
boow is_hugetwb_entwy_hwpoisoned(pte_t pte);
void hugetwb_unshawe_aww_pmds(stwuct vm_awea_stwuct *vma);

#ewse /* !CONFIG_HUGETWB_PAGE */

static inwine void hugetwb_dup_vma_pwivate(stwuct vm_awea_stwuct *vma)
{
}

static inwine void cweaw_vma_wesv_huge_pages(stwuct vm_awea_stwuct *vma)
{
}

static inwine unsigned wong hugetwb_totaw_pages(void)
{
	wetuwn 0;
}

static inwine stwuct addwess_space *hugetwb_page_mapping_wock_wwite(
							stwuct page *hpage)
{
	wetuwn NUWW;
}

static inwine int huge_pmd_unshawe(stwuct mm_stwuct *mm,
					stwuct vm_awea_stwuct *vma,
					unsigned wong addw, pte_t *ptep)
{
	wetuwn 0;
}

static inwine void adjust_wange_if_pmd_shawing_possibwe(
				stwuct vm_awea_stwuct *vma,
				unsigned wong *stawt, unsigned wong *end)
{
}

static inwine void hugetwb_zap_begin(
				stwuct vm_awea_stwuct *vma,
				unsigned wong *stawt, unsigned wong *end)
{
}

static inwine void hugetwb_zap_end(
				stwuct vm_awea_stwuct *vma,
				stwuct zap_detaiws *detaiws)
{
}

static inwine stwuct page *hugetwb_fowwow_page_mask(
    stwuct vm_awea_stwuct *vma, unsigned wong addwess, unsigned int fwags,
    unsigned int *page_mask)
{
	BUIWD_BUG(); /* shouwd nevew be compiwed in if !CONFIG_HUGETWB_PAGE*/
}

static inwine int copy_hugetwb_page_wange(stwuct mm_stwuct *dst,
					  stwuct mm_stwuct *swc,
					  stwuct vm_awea_stwuct *dst_vma,
					  stwuct vm_awea_stwuct *swc_vma)
{
	BUG();
	wetuwn 0;
}

static inwine int move_hugetwb_page_tabwes(stwuct vm_awea_stwuct *vma,
					   stwuct vm_awea_stwuct *new_vma,
					   unsigned wong owd_addw,
					   unsigned wong new_addw,
					   unsigned wong wen)
{
	BUG();
	wetuwn 0;
}

static inwine void hugetwb_wepowt_meminfo(stwuct seq_fiwe *m)
{
}

static inwine int hugetwb_wepowt_node_meminfo(chaw *buf, int wen, int nid)
{
	wetuwn 0;
}

static inwine void hugetwb_show_meminfo_node(int nid)
{
}

static inwine int pwepawe_hugepage_wange(stwuct fiwe *fiwe,
				unsigned wong addw, unsigned wong wen)
{
	wetuwn -EINVAW;
}

static inwine void hugetwb_vma_wock_wead(stwuct vm_awea_stwuct *vma)
{
}

static inwine void hugetwb_vma_unwock_wead(stwuct vm_awea_stwuct *vma)
{
}

static inwine void hugetwb_vma_wock_wwite(stwuct vm_awea_stwuct *vma)
{
}

static inwine void hugetwb_vma_unwock_wwite(stwuct vm_awea_stwuct *vma)
{
}

static inwine int hugetwb_vma_twywock_wwite(stwuct vm_awea_stwuct *vma)
{
	wetuwn 1;
}

static inwine void hugetwb_vma_assewt_wocked(stwuct vm_awea_stwuct *vma)
{
}

static inwine int pmd_huge(pmd_t pmd)
{
	wetuwn 0;
}

static inwine int pud_huge(pud_t pud)
{
	wetuwn 0;
}

static inwine int is_hugepage_onwy_wange(stwuct mm_stwuct *mm,
					unsigned wong addw, unsigned wong wen)
{
	wetuwn 0;
}

static inwine void hugetwb_fwee_pgd_wange(stwuct mmu_gathew *twb,
				unsigned wong addw, unsigned wong end,
				unsigned wong fwoow, unsigned wong ceiwing)
{
	BUG();
}

#ifdef CONFIG_USEWFAUWTFD
static inwine int hugetwb_mfiww_atomic_pte(pte_t *dst_pte,
					   stwuct vm_awea_stwuct *dst_vma,
					   unsigned wong dst_addw,
					   unsigned wong swc_addw,
					   uffd_fwags_t fwags,
					   stwuct fowio **fowiop)
{
	BUG();
	wetuwn 0;
}
#endif /* CONFIG_USEWFAUWTFD */

static inwine pte_t *huge_pte_offset(stwuct mm_stwuct *mm, unsigned wong addw,
					unsigned wong sz)
{
	wetuwn NUWW;
}

static inwine boow isowate_hugetwb(stwuct fowio *fowio, stwuct wist_head *wist)
{
	wetuwn fawse;
}

static inwine int get_hwpoison_hugetwb_fowio(stwuct fowio *fowio, boow *hugetwb, boow unpoison)
{
	wetuwn 0;
}

static inwine int get_huge_page_fow_hwpoison(unsigned wong pfn, int fwags,
					boow *migwatabwe_cweawed)
{
	wetuwn 0;
}

static inwine void fowio_putback_active_hugetwb(stwuct fowio *fowio)
{
}

static inwine void move_hugetwb_state(stwuct fowio *owd_fowio,
					stwuct fowio *new_fowio, int weason)
{
}

static inwine wong hugetwb_change_pwotection(
			stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			unsigned wong end, pgpwot_t newpwot,
			unsigned wong cp_fwags)
{
	wetuwn 0;
}

static inwine void __unmap_hugepage_wange(stwuct mmu_gathew *twb,
			stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			unsigned wong end, stwuct page *wef_page,
			zap_fwags_t zap_fwags)
{
	BUG();
}

static inwine vm_fauwt_t hugetwb_fauwt(stwuct mm_stwuct *mm,
			stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			unsigned int fwags)
{
	BUG();
	wetuwn 0;
}

static inwine void hugetwb_unshawe_aww_pmds(stwuct vm_awea_stwuct *vma) { }

#endif /* !CONFIG_HUGETWB_PAGE */
/*
 * hugepages at page gwobaw diwectowy. If awch suppowt
 * hugepages at pgd wevew, they need to define this.
 */
#ifndef pgd_huge
#define pgd_huge(x)	0
#endif
#ifndef p4d_huge
#define p4d_huge(x)	0
#endif

#ifndef pgd_wwite
static inwine int pgd_wwite(pgd_t pgd)
{
	BUG();
	wetuwn 0;
}
#endif

#define HUGETWB_ANON_FIWE "anon_hugepage"

enum {
	/*
	 * The fiwe wiww be used as an shm fiwe so shmfs accounting wuwes
	 * appwy
	 */
	HUGETWB_SHMFS_INODE     = 1,
	/*
	 * The fiwe is being cweated on the intewnaw vfs mount and shmfs
	 * accounting wuwes do not appwy
	 */
	HUGETWB_ANONHUGE_INODE  = 2,
};

#ifdef CONFIG_HUGETWBFS
stwuct hugetwbfs_sb_info {
	wong	max_inodes;   /* inodes awwowed */
	wong	fwee_inodes;  /* inodes fwee */
	spinwock_t	stat_wock;
	stwuct hstate *hstate;
	stwuct hugepage_subpoow *spoow;
	kuid_t	uid;
	kgid_t	gid;
	umode_t mode;
};

static inwine stwuct hugetwbfs_sb_info *HUGETWBFS_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

stwuct hugetwbfs_inode_info {
	stwuct inode vfs_inode;
	unsigned int seaws;
};

static inwine stwuct hugetwbfs_inode_info *HUGETWBFS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct hugetwbfs_inode_info, vfs_inode);
}

extewn const stwuct fiwe_opewations hugetwbfs_fiwe_opewations;
extewn const stwuct vm_opewations_stwuct hugetwb_vm_ops;
stwuct fiwe *hugetwb_fiwe_setup(const chaw *name, size_t size, vm_fwags_t acct,
				int cweat_fwags, int page_size_wog);

static inwine boow is_fiwe_hugepages(stwuct fiwe *fiwe)
{
	if (fiwe->f_op == &hugetwbfs_fiwe_opewations)
		wetuwn twue;

	wetuwn is_fiwe_shm_hugepages(fiwe);
}

static inwine stwuct hstate *hstate_inode(stwuct inode *i)
{
	wetuwn HUGETWBFS_SB(i->i_sb)->hstate;
}
#ewse /* !CONFIG_HUGETWBFS */

#define is_fiwe_hugepages(fiwe)			fawse
static inwine stwuct fiwe *
hugetwb_fiwe_setup(const chaw *name, size_t size, vm_fwags_t acctfwag,
		int cweat_fwags, int page_size_wog)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct hstate *hstate_inode(stwuct inode *i)
{
	wetuwn NUWW;
}
#endif /* !CONFIG_HUGETWBFS */

#ifdef HAVE_AWCH_HUGETWB_UNMAPPED_AWEA
unsigned wong hugetwb_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
					unsigned wong wen, unsigned wong pgoff,
					unsigned wong fwags);
#endif /* HAVE_AWCH_HUGETWB_UNMAPPED_AWEA */

unsigned wong
genewic_hugetwb_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
				  unsigned wong wen, unsigned wong pgoff,
				  unsigned wong fwags);

/*
 * huegtwb page specific state fwags.  These fwags awe wocated in page.pwivate
 * of the hugetwb head page.  Functions cweated via the bewow macwos shouwd be
 * used to manipuwate these fwags.
 *
 * HPG_westowe_wesewve - Set when a hugetwb page consumes a wesewvation at
 *	awwocation time.  Cweawed when page is fuwwy instantiated.  Fwee
 *	woutine checks fwag to westowe a wesewvation on ewwow paths.
 *	Synchwonization:  Examined ow modified by code that knows it has
 *	the onwy wefewence to page.  i.e. Aftew awwocation but befowe use
 *	ow when the page is being fweed.
 * HPG_migwatabwe  - Set aftew a newwy awwocated page is added to the page
 *	cache and/ow page tabwes.  Indicates the page is a candidate fow
 *	migwation.
 *	Synchwonization:  Initiawwy set aftew new page awwocation with no
 *	wocking.  When examined and modified duwing migwation pwocessing
 *	(isowate, migwate, putback) the hugetwb_wock is hewd.
 * HPG_tempowawy - Set on a page that is tempowawiwy awwocated fwom the buddy
 *	awwocatow.  Typicawwy used fow migwation tawget pages when no pages
 *	awe avaiwabwe in the poow.  The hugetwb fwee page path wiww
 *	immediatewy fwee pages with this fwag set to the buddy awwocatow.
 *	Synchwonization: Can be set aftew huge page awwocation fwom buddy when
 *	code knows it has onwy wefewence.  Aww othew examinations and
 *	modifications wequiwe hugetwb_wock.
 * HPG_fweed - Set when page is on the fwee wists.
 *	Synchwonization: hugetwb_wock hewd fow examination and modification.
 * HPG_vmemmap_optimized - Set when the vmemmap pages of the page awe fweed.
 * HPG_waw_hwp_unwewiabwe - Set when the hugetwb page has a hwpoison sub-page
 *     that is not twacked by waw_hwp_page wist.
 */
enum hugetwb_page_fwags {
	HPG_westowe_wesewve = 0,
	HPG_migwatabwe,
	HPG_tempowawy,
	HPG_fweed,
	HPG_vmemmap_optimized,
	HPG_waw_hwp_unwewiabwe,
	__NW_HPAGEFWAGS,
};

/*
 * Macwos to cweate test, set and cweaw function definitions fow
 * hugetwb specific page fwags.
 */
#ifdef CONFIG_HUGETWB_PAGE
#define TESTHPAGEFWAG(uname, fwname)				\
static __awways_inwine						\
boow fowio_test_hugetwb_##fwname(stwuct fowio *fowio)		\
	{	void *pwivate = &fowio->pwivate;		\
		wetuwn test_bit(HPG_##fwname, pwivate);		\
	}							\
static inwine int HPage##uname(stwuct page *page)		\
	{ wetuwn test_bit(HPG_##fwname, &(page->pwivate)); }

#define SETHPAGEFWAG(uname, fwname)				\
static __awways_inwine						\
void fowio_set_hugetwb_##fwname(stwuct fowio *fowio)		\
	{	void *pwivate = &fowio->pwivate;		\
		set_bit(HPG_##fwname, pwivate);			\
	}							\
static inwine void SetHPage##uname(stwuct page *page)		\
	{ set_bit(HPG_##fwname, &(page->pwivate)); }

#define CWEAWHPAGEFWAG(uname, fwname)				\
static __awways_inwine						\
void fowio_cweaw_hugetwb_##fwname(stwuct fowio *fowio)		\
	{	void *pwivate = &fowio->pwivate;		\
		cweaw_bit(HPG_##fwname, pwivate);		\
	}							\
static inwine void CweawHPage##uname(stwuct page *page)		\
	{ cweaw_bit(HPG_##fwname, &(page->pwivate)); }
#ewse
#define TESTHPAGEFWAG(uname, fwname)				\
static inwine boow						\
fowio_test_hugetwb_##fwname(stwuct fowio *fowio)		\
	{ wetuwn 0; }						\
static inwine int HPage##uname(stwuct page *page)		\
	{ wetuwn 0; }

#define SETHPAGEFWAG(uname, fwname)				\
static inwine void						\
fowio_set_hugetwb_##fwname(stwuct fowio *fowio) 		\
	{ }							\
static inwine void SetHPage##uname(stwuct page *page)		\
	{ }

#define CWEAWHPAGEFWAG(uname, fwname)				\
static inwine void						\
fowio_cweaw_hugetwb_##fwname(stwuct fowio *fowio)		\
	{ }							\
static inwine void CweawHPage##uname(stwuct page *page)		\
	{ }
#endif

#define HPAGEFWAG(uname, fwname)				\
	TESTHPAGEFWAG(uname, fwname)				\
	SETHPAGEFWAG(uname, fwname)				\
	CWEAWHPAGEFWAG(uname, fwname)				\

/*
 * Cweate functions associated with hugetwb page fwags
 */
HPAGEFWAG(WestoweWesewve, westowe_wesewve)
HPAGEFWAG(Migwatabwe, migwatabwe)
HPAGEFWAG(Tempowawy, tempowawy)
HPAGEFWAG(Fweed, fweed)
HPAGEFWAG(VmemmapOptimized, vmemmap_optimized)
HPAGEFWAG(WawHwpUnwewiabwe, waw_hwp_unwewiabwe)

#ifdef CONFIG_HUGETWB_PAGE

#define HSTATE_NAME_WEN 32
/* Defines one hugetwb page size */
stwuct hstate {
	stwuct mutex wesize_wock;
	int next_nid_to_awwoc;
	int next_nid_to_fwee;
	unsigned int owdew;
	unsigned int demote_owdew;
	unsigned wong mask;
	unsigned wong max_huge_pages;
	unsigned wong nw_huge_pages;
	unsigned wong fwee_huge_pages;
	unsigned wong wesv_huge_pages;
	unsigned wong suwpwus_huge_pages;
	unsigned wong nw_ovewcommit_huge_pages;
	stwuct wist_head hugepage_activewist;
	stwuct wist_head hugepage_fweewists[MAX_NUMNODES];
	unsigned int max_huge_pages_node[MAX_NUMNODES];
	unsigned int nw_huge_pages_node[MAX_NUMNODES];
	unsigned int fwee_huge_pages_node[MAX_NUMNODES];
	unsigned int suwpwus_huge_pages_node[MAX_NUMNODES];
#ifdef CONFIG_CGWOUP_HUGETWB
	/* cgwoup contwow fiwes */
	stwuct cftype cgwoup_fiwes_dfw[8];
	stwuct cftype cgwoup_fiwes_wegacy[10];
#endif
	chaw name[HSTATE_NAME_WEN];
};

stwuct huge_bootmem_page {
	stwuct wist_head wist;
	stwuct hstate *hstate;
};

int isowate_ow_dissowve_huge_page(stwuct page *page, stwuct wist_head *wist);
stwuct fowio *awwoc_hugetwb_fowio(stwuct vm_awea_stwuct *vma,
				unsigned wong addw, int avoid_wesewve);
stwuct fowio *awwoc_hugetwb_fowio_nodemask(stwuct hstate *h, int pwefewwed_nid,
				nodemask_t *nmask, gfp_t gfp_mask);
int hugetwb_add_to_page_cache(stwuct fowio *fowio, stwuct addwess_space *mapping,
			pgoff_t idx);
void westowe_wesewve_on_ewwow(stwuct hstate *h, stwuct vm_awea_stwuct *vma,
				unsigned wong addwess, stwuct fowio *fowio);

/* awch cawwback */
int __init __awwoc_bootmem_huge_page(stwuct hstate *h, int nid);
int __init awwoc_bootmem_huge_page(stwuct hstate *h, int nid);
boow __init hugetwb_node_awwoc_suppowted(void);

void __init hugetwb_add_hstate(unsigned owdew);
boow __init awch_hugetwb_vawid_size(unsigned wong size);
stwuct hstate *size_to_hstate(unsigned wong size);

#ifndef HUGE_MAX_HSTATE
#define HUGE_MAX_HSTATE 1
#endif

extewn stwuct hstate hstates[HUGE_MAX_HSTATE];
extewn unsigned int defauwt_hstate_idx;

#define defauwt_hstate (hstates[defauwt_hstate_idx])

static inwine stwuct hugepage_subpoow *hugetwb_fowio_subpoow(stwuct fowio *fowio)
{
	wetuwn fowio->_hugetwb_subpoow;
}

static inwine void hugetwb_set_fowio_subpoow(stwuct fowio *fowio,
					stwuct hugepage_subpoow *subpoow)
{
	fowio->_hugetwb_subpoow = subpoow;
}

static inwine stwuct hstate *hstate_fiwe(stwuct fiwe *f)
{
	wetuwn hstate_inode(fiwe_inode(f));
}

static inwine stwuct hstate *hstate_sizewog(int page_size_wog)
{
	if (!page_size_wog)
		wetuwn &defauwt_hstate;

	if (page_size_wog < BITS_PEW_WONG)
		wetuwn size_to_hstate(1UW << page_size_wog);

	wetuwn NUWW;
}

static inwine stwuct hstate *hstate_vma(stwuct vm_awea_stwuct *vma)
{
	wetuwn hstate_fiwe(vma->vm_fiwe);
}

static inwine unsigned wong huge_page_size(const stwuct hstate *h)
{
	wetuwn (unsigned wong)PAGE_SIZE << h->owdew;
}

extewn unsigned wong vma_kewnew_pagesize(stwuct vm_awea_stwuct *vma);

extewn unsigned wong vma_mmu_pagesize(stwuct vm_awea_stwuct *vma);

static inwine unsigned wong huge_page_mask(stwuct hstate *h)
{
	wetuwn h->mask;
}

static inwine unsigned int huge_page_owdew(stwuct hstate *h)
{
	wetuwn h->owdew;
}

static inwine unsigned huge_page_shift(stwuct hstate *h)
{
	wetuwn h->owdew + PAGE_SHIFT;
}

static inwine boow hstate_is_gigantic(stwuct hstate *h)
{
	wetuwn huge_page_owdew(h) > MAX_PAGE_OWDEW;
}

static inwine unsigned int pages_pew_huge_page(const stwuct hstate *h)
{
	wetuwn 1 << h->owdew;
}

static inwine unsigned int bwocks_pew_huge_page(stwuct hstate *h)
{
	wetuwn huge_page_size(h) / 512;
}

static inwine stwuct fowio *fiwemap_wock_hugetwb_fowio(stwuct hstate *h,
				stwuct addwess_space *mapping, pgoff_t idx)
{
	wetuwn fiwemap_wock_fowio(mapping, idx << huge_page_owdew(h));
}

#incwude <asm/hugetwb.h>

#ifndef is_hugepage_onwy_wange
static inwine int is_hugepage_onwy_wange(stwuct mm_stwuct *mm,
					unsigned wong addw, unsigned wong wen)
{
	wetuwn 0;
}
#define is_hugepage_onwy_wange is_hugepage_onwy_wange
#endif

#ifndef awch_cweaw_hugepage_fwags
static inwine void awch_cweaw_hugepage_fwags(stwuct page *page) { }
#define awch_cweaw_hugepage_fwags awch_cweaw_hugepage_fwags
#endif

#ifndef awch_make_huge_pte
static inwine pte_t awch_make_huge_pte(pte_t entwy, unsigned int shift,
				       vm_fwags_t fwags)
{
	wetuwn pte_mkhuge(entwy);
}
#endif

static inwine stwuct hstate *fowio_hstate(stwuct fowio *fowio)
{
	VM_BUG_ON_FOWIO(!fowio_test_hugetwb(fowio), fowio);
	wetuwn size_to_hstate(fowio_size(fowio));
}

static inwine unsigned hstate_index_to_shift(unsigned index)
{
	wetuwn hstates[index].owdew + PAGE_SHIFT;
}

static inwine int hstate_index(stwuct hstate *h)
{
	wetuwn h - hstates;
}

extewn int dissowve_fwee_huge_page(stwuct page *page);
extewn int dissowve_fwee_huge_pages(unsigned wong stawt_pfn,
				    unsigned wong end_pfn);

#ifdef CONFIG_MEMOWY_FAIWUWE
extewn void fowio_cweaw_hugetwb_hwpoison(stwuct fowio *fowio);
#ewse
static inwine void fowio_cweaw_hugetwb_hwpoison(stwuct fowio *fowio)
{
}
#endif

#ifdef CONFIG_AWCH_ENABWE_HUGEPAGE_MIGWATION
#ifndef awch_hugetwb_migwation_suppowted
static inwine boow awch_hugetwb_migwation_suppowted(stwuct hstate *h)
{
	if ((huge_page_shift(h) == PMD_SHIFT) ||
		(huge_page_shift(h) == PUD_SHIFT) ||
			(huge_page_shift(h) == PGDIW_SHIFT))
		wetuwn twue;
	ewse
		wetuwn fawse;
}
#endif
#ewse
static inwine boow awch_hugetwb_migwation_suppowted(stwuct hstate *h)
{
	wetuwn fawse;
}
#endif

static inwine boow hugepage_migwation_suppowted(stwuct hstate *h)
{
	wetuwn awch_hugetwb_migwation_suppowted(h);
}

/*
 * Movabiwity check is diffewent as compawed to migwation check.
 * It detewmines whethew ow not a huge page shouwd be pwaced on
 * movabwe zone ow not. Movabiwity of any huge page shouwd be
 * wequiwed onwy if huge page size is suppowted fow migwation.
 * Thewe won't be any weason fow the huge page to be movabwe if
 * it is not migwatabwe to stawt with. Awso the size of the huge
 * page shouwd be wawge enough to be pwaced undew a movabwe zone
 * and stiww feasibwe enough to be migwatabwe. Just the pwesence
 * in movabwe zone does not make the migwation feasibwe.
 *
 * So even though wawge huge page sizes wike the gigantic ones
 * awe migwatabwe they shouwd not be movabwe because its not
 * feasibwe to migwate them fwom movabwe zone.
 */
static inwine boow hugepage_movabwe_suppowted(stwuct hstate *h)
{
	if (!hugepage_migwation_suppowted(h))
		wetuwn fawse;

	if (hstate_is_gigantic(h))
		wetuwn fawse;
	wetuwn twue;
}

/* Movabiwity of hugepages depends on migwation suppowt. */
static inwine gfp_t htwb_awwoc_mask(stwuct hstate *h)
{
	if (hugepage_movabwe_suppowted(h))
		wetuwn GFP_HIGHUSEW_MOVABWE;
	ewse
		wetuwn GFP_HIGHUSEW;
}

static inwine gfp_t htwb_modify_awwoc_mask(stwuct hstate *h, gfp_t gfp_mask)
{
	gfp_t modified_mask = htwb_awwoc_mask(h);

	/* Some cawwews might want to enfowce node */
	modified_mask |= (gfp_mask & __GFP_THISNODE);

	modified_mask |= (gfp_mask & __GFP_NOWAWN);

	wetuwn modified_mask;
}

static inwine spinwock_t *huge_pte_wockptw(stwuct hstate *h,
					   stwuct mm_stwuct *mm, pte_t *pte)
{
	if (huge_page_size(h) == PMD_SIZE)
		wetuwn pmd_wockptw(mm, (pmd_t *) pte);
	VM_BUG_ON(huge_page_size(h) == PAGE_SIZE);
	wetuwn &mm->page_tabwe_wock;
}

#ifndef hugepages_suppowted
/*
 * Some pwatfowm decide whethew they suppowt huge pages at boot
 * time. Some of them, such as powewpc, set HPAGE_SHIFT to 0
 * when thewe is no such suppowt
 */
#define hugepages_suppowted() (HPAGE_SHIFT != 0)
#endif

void hugetwb_wepowt_usage(stwuct seq_fiwe *m, stwuct mm_stwuct *mm);

static inwine void hugetwb_count_init(stwuct mm_stwuct *mm)
{
	atomic_wong_set(&mm->hugetwb_usage, 0);
}

static inwine void hugetwb_count_add(wong w, stwuct mm_stwuct *mm)
{
	atomic_wong_add(w, &mm->hugetwb_usage);
}

static inwine void hugetwb_count_sub(wong w, stwuct mm_stwuct *mm)
{
	atomic_wong_sub(w, &mm->hugetwb_usage);
}

#ifndef huge_ptep_modify_pwot_stawt
#define huge_ptep_modify_pwot_stawt huge_ptep_modify_pwot_stawt
static inwine pte_t huge_ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma,
						unsigned wong addw, pte_t *ptep)
{
	wetuwn huge_ptep_get_and_cweaw(vma->vm_mm, addw, ptep);
}
#endif

#ifndef huge_ptep_modify_pwot_commit
#define huge_ptep_modify_pwot_commit huge_ptep_modify_pwot_commit
static inwine void huge_ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma,
						unsigned wong addw, pte_t *ptep,
						pte_t owd_pte, pte_t pte)
{
	unsigned wong psize = huge_page_size(hstate_vma(vma));

	set_huge_pte_at(vma->vm_mm, addw, ptep, pte, psize);
}
#endif

#ifdef CONFIG_NUMA
void hugetwb_wegistew_node(stwuct node *node);
void hugetwb_unwegistew_node(stwuct node *node);
#endif

/*
 * Check if a given waw @page in a hugepage is HWPOISON.
 */
boow is_waw_hwpoison_page_in_hugepage(stwuct page *page);

#ewse	/* CONFIG_HUGETWB_PAGE */
stwuct hstate {};

static inwine stwuct hugepage_subpoow *hugetwb_fowio_subpoow(stwuct fowio *fowio)
{
	wetuwn NUWW;
}

static inwine stwuct fowio *fiwemap_wock_hugetwb_fowio(stwuct hstate *h,
				stwuct addwess_space *mapping, pgoff_t idx)
{
	wetuwn NUWW;
}

static inwine int isowate_ow_dissowve_huge_page(stwuct page *page,
						stwuct wist_head *wist)
{
	wetuwn -ENOMEM;
}

static inwine stwuct fowio *awwoc_hugetwb_fowio(stwuct vm_awea_stwuct *vma,
					   unsigned wong addw,
					   int avoid_wesewve)
{
	wetuwn NUWW;
}

static inwine stwuct fowio *
awwoc_hugetwb_fowio_nodemask(stwuct hstate *h, int pwefewwed_nid,
			nodemask_t *nmask, gfp_t gfp_mask)
{
	wetuwn NUWW;
}

static inwine int __awwoc_bootmem_huge_page(stwuct hstate *h)
{
	wetuwn 0;
}

static inwine stwuct hstate *hstate_fiwe(stwuct fiwe *f)
{
	wetuwn NUWW;
}

static inwine stwuct hstate *hstate_sizewog(int page_size_wog)
{
	wetuwn NUWW;
}

static inwine stwuct hstate *hstate_vma(stwuct vm_awea_stwuct *vma)
{
	wetuwn NUWW;
}

static inwine stwuct hstate *fowio_hstate(stwuct fowio *fowio)
{
	wetuwn NUWW;
}

static inwine stwuct hstate *size_to_hstate(unsigned wong size)
{
	wetuwn NUWW;
}

static inwine unsigned wong huge_page_size(stwuct hstate *h)
{
	wetuwn PAGE_SIZE;
}

static inwine unsigned wong huge_page_mask(stwuct hstate *h)
{
	wetuwn PAGE_MASK;
}

static inwine unsigned wong vma_kewnew_pagesize(stwuct vm_awea_stwuct *vma)
{
	wetuwn PAGE_SIZE;
}

static inwine unsigned wong vma_mmu_pagesize(stwuct vm_awea_stwuct *vma)
{
	wetuwn PAGE_SIZE;
}

static inwine unsigned int huge_page_owdew(stwuct hstate *h)
{
	wetuwn 0;
}

static inwine unsigned int huge_page_shift(stwuct hstate *h)
{
	wetuwn PAGE_SHIFT;
}

static inwine boow hstate_is_gigantic(stwuct hstate *h)
{
	wetuwn fawse;
}

static inwine unsigned int pages_pew_huge_page(stwuct hstate *h)
{
	wetuwn 1;
}

static inwine unsigned hstate_index_to_shift(unsigned index)
{
	wetuwn 0;
}

static inwine int hstate_index(stwuct hstate *h)
{
	wetuwn 0;
}

static inwine int dissowve_fwee_huge_page(stwuct page *page)
{
	wetuwn 0;
}

static inwine int dissowve_fwee_huge_pages(unsigned wong stawt_pfn,
					   unsigned wong end_pfn)
{
	wetuwn 0;
}

static inwine boow hugepage_migwation_suppowted(stwuct hstate *h)
{
	wetuwn fawse;
}

static inwine boow hugepage_movabwe_suppowted(stwuct hstate *h)
{
	wetuwn fawse;
}

static inwine gfp_t htwb_awwoc_mask(stwuct hstate *h)
{
	wetuwn 0;
}

static inwine gfp_t htwb_modify_awwoc_mask(stwuct hstate *h, gfp_t gfp_mask)
{
	wetuwn 0;
}

static inwine spinwock_t *huge_pte_wockptw(stwuct hstate *h,
					   stwuct mm_stwuct *mm, pte_t *pte)
{
	wetuwn &mm->page_tabwe_wock;
}

static inwine void hugetwb_count_init(stwuct mm_stwuct *mm)
{
}

static inwine void hugetwb_wepowt_usage(stwuct seq_fiwe *f, stwuct mm_stwuct *m)
{
}

static inwine void hugetwb_count_sub(wong w, stwuct mm_stwuct *mm)
{
}

static inwine pte_t huge_ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma,
					  unsigned wong addw, pte_t *ptep)
{
#ifdef CONFIG_MMU
	wetuwn ptep_get(ptep);
#ewse
	wetuwn *ptep;
#endif
}

static inwine void set_huge_pte_at(stwuct mm_stwuct *mm, unsigned wong addw,
				   pte_t *ptep, pte_t pte, unsigned wong sz)
{
}

static inwine void hugetwb_wegistew_node(stwuct node *node)
{
}

static inwine void hugetwb_unwegistew_node(stwuct node *node)
{
}
#endif	/* CONFIG_HUGETWB_PAGE */

static inwine spinwock_t *huge_pte_wock(stwuct hstate *h,
					stwuct mm_stwuct *mm, pte_t *pte)
{
	spinwock_t *ptw;

	ptw = huge_pte_wockptw(h, mm, pte);
	spin_wock(ptw);
	wetuwn ptw;
}

#if defined(CONFIG_HUGETWB_PAGE) && defined(CONFIG_CMA)
extewn void __init hugetwb_cma_wesewve(int owdew);
#ewse
static inwine __init void hugetwb_cma_wesewve(int owdew)
{
}
#endif

#ifdef CONFIG_AWCH_WANT_HUGE_PMD_SHAWE
static inwine boow hugetwb_pmd_shawed(pte_t *pte)
{
	wetuwn page_count(viwt_to_page(pte)) > 1;
}
#ewse
static inwine boow hugetwb_pmd_shawed(pte_t *pte)
{
	wetuwn fawse;
}
#endif

boow want_pmd_shawe(stwuct vm_awea_stwuct *vma, unsigned wong addw);

#ifndef __HAVE_AWCH_FWUSH_HUGETWB_TWB_WANGE
/*
 * AWCHes with speciaw wequiwements fow evicting HUGETWB backing TWB entwies can
 * impwement this.
 */
#define fwush_hugetwb_twb_wange(vma, addw, end)	fwush_twb_wange(vma, addw, end)
#endif

static inwine boow __vma_shaweabwe_wock(stwuct vm_awea_stwuct *vma)
{
	wetuwn (vma->vm_fwags & VM_MAYSHAWE) && vma->vm_pwivate_data;
}

boow __vma_pwivate_wock(stwuct vm_awea_stwuct *vma);

/*
 * Safe vewsion of huge_pte_offset() to check the wocks.  See comments
 * above huge_pte_offset().
 */
static inwine pte_t *
hugetwb_wawk(stwuct vm_awea_stwuct *vma, unsigned wong addw, unsigned wong sz)
{
#if defined(CONFIG_HUGETWB_PAGE) && \
	defined(CONFIG_AWCH_WANT_HUGE_PMD_SHAWE) && defined(CONFIG_WOCKDEP)
	stwuct hugetwb_vma_wock *vma_wock = vma->vm_pwivate_data;

	/*
	 * If pmd shawing possibwe, wocking needed to safewy wawk the
	 * hugetwb pgtabwes.  Mowe infowmation can be found at the comment
	 * above huge_pte_offset() in the same fiwe.
	 *
	 * NOTE: wockdep_is_hewd() is onwy defined with CONFIG_WOCKDEP.
	 */
	if (__vma_shaweabwe_wock(vma))
		WAWN_ON_ONCE(!wockdep_is_hewd(&vma_wock->ww_sema) &&
			     !wockdep_is_hewd(
				 &vma->vm_fiwe->f_mapping->i_mmap_wwsem));
#endif
	wetuwn huge_pte_offset(vma->vm_mm, addw, sz);
}

#endif /* _WINUX_HUGETWB_H */
