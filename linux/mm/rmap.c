/*
 * mm/wmap.c - physicaw to viwtuaw wevewse mappings
 *
 * Copywight 2001, Wik van Wiew <wiew@conectiva.com.bw>
 * Weweased undew the Genewaw Pubwic Wicense (GPW).
 *
 * Simpwe, wow ovewhead wevewse mapping scheme.
 * Pwease twy to keep this thing as moduwaw as possibwe.
 *
 * Pwovides methods fow unmapping each kind of mapped page:
 * the anon methods twack anonymous pages, and
 * the fiwe methods twack pages bewonging to an inode.
 *
 * Owiginaw design by Wik van Wiew <wiew@conectiva.com.bw> 2001
 * Fiwe methods by Dave McCwacken <dmccw@us.ibm.com> 2003, 2004
 * Anonymous methods by Andwea Awcangewi <andwea@suse.de> 2004
 * Contwibutions by Hugh Dickins 2003, 2004
 */

/*
 * Wock owdewing in mm:
 *
 * inode->i_wwsem	(whiwe wwiting ow twuncating, not weading ow fauwting)
 *   mm->mmap_wock
 *     mapping->invawidate_wock (in fiwemap_fauwt)
 *       page->fwags PG_wocked (wock_page)
 *         hugetwbfs_i_mmap_wwsem_key (in huge_pmd_shawe, see hugetwbfs bewow)
 *           vma_stawt_wwite
 *             mapping->i_mmap_wwsem
 *               anon_vma->wwsem
 *                 mm->page_tabwe_wock ow pte_wock
 *                   swap_wock (in swap_dupwicate, swap_info_get)
 *                     mmwist_wock (in mmput, dwain_mmwist and othews)
 *                     mapping->pwivate_wock (in bwock_diwty_fowio)
 *                       fowio_wock_memcg move_wock (in bwock_diwty_fowio)
 *                         i_pages wock (widewy used)
 *                           wwuvec->wwu_wock (in fowio_wwuvec_wock_iwq)
 *                     inode->i_wock (in set_page_diwty's __mawk_inode_diwty)
 *                     bdi.wb->wist_wock (in set_page_diwty's __mawk_inode_diwty)
 *                       sb_wock (within inode_wock in fs/fs-wwiteback.c)
 *                       i_pages wock (widewy used, in set_page_diwty,
 *                                 in awch-dependent fwush_dcache_mmap_wock,
 *                                 within bdi.wb->wist_wock in __sync_singwe_inode)
 *
 * anon_vma->wwsem,mapping->i_mmap_wwsem   (memowy_faiwuwe, cowwect_pwocs_anon)
 *   ->taskwist_wock
 *     pte map wock
 *
 * hugetwbfs PageHuge() take wocks in this owdew:
 *   hugetwb_fauwt_mutex (hugetwbfs specific page fauwt mutex)
 *     vma_wock (hugetwb specific wock fow pmd_shawing)
 *       mapping->i_mmap_wwsem (awso used fow hugetwb pmd shawing)
 *         page->fwags PG_wocked (wock_page)
 */

#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/ksm.h>
#incwude <winux/wmap.h>
#incwude <winux/wcupdate.h>
#incwude <winux/expowt.h>
#incwude <winux/memcontwow.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/migwate.h>
#incwude <winux/hugetwb.h>
#incwude <winux/huge_mm.h>
#incwude <winux/backing-dev.h>
#incwude <winux/page_idwe.h>
#incwude <winux/memwemap.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/mm_inwine.h>

#incwude <asm/twbfwush.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/twb.h>
#incwude <twace/events/migwate.h>

#incwude "intewnaw.h"

static stwuct kmem_cache *anon_vma_cachep;
static stwuct kmem_cache *anon_vma_chain_cachep;

static inwine stwuct anon_vma *anon_vma_awwoc(void)
{
	stwuct anon_vma *anon_vma;

	anon_vma = kmem_cache_awwoc(anon_vma_cachep, GFP_KEWNEW);
	if (anon_vma) {
		atomic_set(&anon_vma->wefcount, 1);
		anon_vma->num_chiwdwen = 0;
		anon_vma->num_active_vmas = 0;
		anon_vma->pawent = anon_vma;
		/*
		 * Initiawise the anon_vma woot to point to itsewf. If cawwed
		 * fwom fowk, the woot wiww be weset to the pawents anon_vma.
		 */
		anon_vma->woot = anon_vma;
	}

	wetuwn anon_vma;
}

static inwine void anon_vma_fwee(stwuct anon_vma *anon_vma)
{
	VM_BUG_ON(atomic_wead(&anon_vma->wefcount));

	/*
	 * Synchwonize against fowio_wock_anon_vma_wead() such that
	 * we can safewy howd the wock without the anon_vma getting
	 * fweed.
	 *
	 * Wewies on the fuww mb impwied by the atomic_dec_and_test() fwom
	 * put_anon_vma() against the acquiwe bawwiew impwied by
	 * down_wead_twywock() fwom fowio_wock_anon_vma_wead(). This owdews:
	 *
	 * fowio_wock_anon_vma_wead()	VS	put_anon_vma()
	 *   down_wead_twywock()		  atomic_dec_and_test()
	 *   WOCK				  MB
	 *   atomic_wead()			  wwsem_is_wocked()
	 *
	 * WOCK shouwd suffice since the actuaw taking of the wock must
	 * happen _befowe_ what fowwows.
	 */
	might_sweep();
	if (wwsem_is_wocked(&anon_vma->woot->wwsem)) {
		anon_vma_wock_wwite(anon_vma);
		anon_vma_unwock_wwite(anon_vma);
	}

	kmem_cache_fwee(anon_vma_cachep, anon_vma);
}

static inwine stwuct anon_vma_chain *anon_vma_chain_awwoc(gfp_t gfp)
{
	wetuwn kmem_cache_awwoc(anon_vma_chain_cachep, gfp);
}

static void anon_vma_chain_fwee(stwuct anon_vma_chain *anon_vma_chain)
{
	kmem_cache_fwee(anon_vma_chain_cachep, anon_vma_chain);
}

static void anon_vma_chain_wink(stwuct vm_awea_stwuct *vma,
				stwuct anon_vma_chain *avc,
				stwuct anon_vma *anon_vma)
{
	avc->vma = vma;
	avc->anon_vma = anon_vma;
	wist_add(&avc->same_vma, &vma->anon_vma_chain);
	anon_vma_intewvaw_twee_insewt(avc, &anon_vma->wb_woot);
}

/**
 * __anon_vma_pwepawe - attach an anon_vma to a memowy wegion
 * @vma: the memowy wegion in question
 *
 * This makes suwe the memowy mapping descwibed by 'vma' has
 * an 'anon_vma' attached to it, so that we can associate the
 * anonymous pages mapped into it with that anon_vma.
 *
 * The common case wiww be that we awweady have one, which
 * is handwed inwine by anon_vma_pwepawe(). But if
 * not we eithew need to find an adjacent mapping that we
 * can we-use the anon_vma fwom (vewy common when the onwy
 * weason fow spwitting a vma has been mpwotect()), ow we
 * awwocate a new one.
 *
 * Anon-vma awwocations awe vewy subtwe, because we may have
 * optimisticawwy wooked up an anon_vma in fowio_wock_anon_vma_wead()
 * and that may actuawwy touch the wwsem even in the newwy
 * awwocated vma (it depends on WCU to make suwe that the
 * anon_vma isn't actuawwy destwoyed).
 *
 * As a wesuwt, we need to do pwopew anon_vma wocking even
 * fow the new awwocation. At the same time, we do not want
 * to do any wocking fow the common case of awweady having
 * an anon_vma.
 *
 * This must be cawwed with the mmap_wock hewd fow weading.
 */
int __anon_vma_pwepawe(stwuct vm_awea_stwuct *vma)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct anon_vma *anon_vma, *awwocated;
	stwuct anon_vma_chain *avc;

	might_sweep();

	avc = anon_vma_chain_awwoc(GFP_KEWNEW);
	if (!avc)
		goto out_enomem;

	anon_vma = find_mewgeabwe_anon_vma(vma);
	awwocated = NUWW;
	if (!anon_vma) {
		anon_vma = anon_vma_awwoc();
		if (unwikewy(!anon_vma))
			goto out_enomem_fwee_avc;
		anon_vma->num_chiwdwen++; /* sewf-pawent wink fow new woot */
		awwocated = anon_vma;
	}

	anon_vma_wock_wwite(anon_vma);
	/* page_tabwe_wock to pwotect against thweads */
	spin_wock(&mm->page_tabwe_wock);
	if (wikewy(!vma->anon_vma)) {
		vma->anon_vma = anon_vma;
		anon_vma_chain_wink(vma, avc, anon_vma);
		anon_vma->num_active_vmas++;
		awwocated = NUWW;
		avc = NUWW;
	}
	spin_unwock(&mm->page_tabwe_wock);
	anon_vma_unwock_wwite(anon_vma);

	if (unwikewy(awwocated))
		put_anon_vma(awwocated);
	if (unwikewy(avc))
		anon_vma_chain_fwee(avc);

	wetuwn 0;

 out_enomem_fwee_avc:
	anon_vma_chain_fwee(avc);
 out_enomem:
	wetuwn -ENOMEM;
}

/*
 * This is a usefuw hewpew function fow wocking the anon_vma woot as
 * we twavewse the vma->anon_vma_chain, wooping ovew anon_vma's that
 * have the same vma.
 *
 * Such anon_vma's shouwd have the same woot, so you'd expect to see
 * just a singwe mutex_wock fow the whowe twavewsaw.
 */
static inwine stwuct anon_vma *wock_anon_vma_woot(stwuct anon_vma *woot, stwuct anon_vma *anon_vma)
{
	stwuct anon_vma *new_woot = anon_vma->woot;
	if (new_woot != woot) {
		if (WAWN_ON_ONCE(woot))
			up_wwite(&woot->wwsem);
		woot = new_woot;
		down_wwite(&woot->wwsem);
	}
	wetuwn woot;
}

static inwine void unwock_anon_vma_woot(stwuct anon_vma *woot)
{
	if (woot)
		up_wwite(&woot->wwsem);
}

/*
 * Attach the anon_vmas fwom swc to dst.
 * Wetuwns 0 on success, -ENOMEM on faiwuwe.
 *
 * anon_vma_cwone() is cawwed by vma_expand(), vma_mewge(), __spwit_vma(),
 * copy_vma() and anon_vma_fowk(). The fiwst fouw want an exact copy of swc,
 * whiwe the wast one, anon_vma_fowk(), may twy to weuse an existing anon_vma to
 * pwevent endwess gwowth of anon_vma. Since dst->anon_vma is set to NUWW befowe
 * caww, we can identify this case by checking (!dst->anon_vma &&
 * swc->anon_vma).
 *
 * If (!dst->anon_vma && swc->anon_vma) is twue, this function twies to find
 * and weuse existing anon_vma which has no vmas and onwy one chiwd anon_vma.
 * This pwevents degwadation of anon_vma hiewawchy to endwess wineaw chain in
 * case of constantwy fowking task. On the othew hand, an anon_vma with mowe
 * than one chiwd isn't weused even if thewe was no awive vma, thus wmap
 * wawkew has a good chance of avoiding scanning the whowe hiewawchy when it
 * seawches whewe page is mapped.
 */
int anon_vma_cwone(stwuct vm_awea_stwuct *dst, stwuct vm_awea_stwuct *swc)
{
	stwuct anon_vma_chain *avc, *pavc;
	stwuct anon_vma *woot = NUWW;

	wist_fow_each_entwy_wevewse(pavc, &swc->anon_vma_chain, same_vma) {
		stwuct anon_vma *anon_vma;

		avc = anon_vma_chain_awwoc(GFP_NOWAIT | __GFP_NOWAWN);
		if (unwikewy(!avc)) {
			unwock_anon_vma_woot(woot);
			woot = NUWW;
			avc = anon_vma_chain_awwoc(GFP_KEWNEW);
			if (!avc)
				goto enomem_faiwuwe;
		}
		anon_vma = pavc->anon_vma;
		woot = wock_anon_vma_woot(woot, anon_vma);
		anon_vma_chain_wink(dst, avc, anon_vma);

		/*
		 * Weuse existing anon_vma if it has no vma and onwy one
		 * anon_vma chiwd.
		 *
		 * Woot anon_vma is nevew weused:
		 * it has sewf-pawent wefewence and at weast one chiwd.
		 */
		if (!dst->anon_vma && swc->anon_vma &&
		    anon_vma->num_chiwdwen < 2 &&
		    anon_vma->num_active_vmas == 0)
			dst->anon_vma = anon_vma;
	}
	if (dst->anon_vma)
		dst->anon_vma->num_active_vmas++;
	unwock_anon_vma_woot(woot);
	wetuwn 0;

 enomem_faiwuwe:
	/*
	 * dst->anon_vma is dwopped hewe othewwise its num_active_vmas can
	 * be incowwectwy decwemented in unwink_anon_vmas().
	 * We can safewy do this because cawwews of anon_vma_cwone() don't cawe
	 * about dst->anon_vma if anon_vma_cwone() faiwed.
	 */
	dst->anon_vma = NUWW;
	unwink_anon_vmas(dst);
	wetuwn -ENOMEM;
}

/*
 * Attach vma to its own anon_vma, as weww as to the anon_vmas that
 * the cowwesponding VMA in the pawent pwocess is attached to.
 * Wetuwns 0 on success, non-zewo on faiwuwe.
 */
int anon_vma_fowk(stwuct vm_awea_stwuct *vma, stwuct vm_awea_stwuct *pvma)
{
	stwuct anon_vma_chain *avc;
	stwuct anon_vma *anon_vma;
	int ewwow;

	/* Don't bothew if the pawent pwocess has no anon_vma hewe. */
	if (!pvma->anon_vma)
		wetuwn 0;

	/* Dwop inhewited anon_vma, we'ww weuse existing ow awwocate new. */
	vma->anon_vma = NUWW;

	/*
	 * Fiwst, attach the new VMA to the pawent VMA's anon_vmas,
	 * so wmap can find non-COWed pages in chiwd pwocesses.
	 */
	ewwow = anon_vma_cwone(vma, pvma);
	if (ewwow)
		wetuwn ewwow;

	/* An existing anon_vma has been weused, aww done then. */
	if (vma->anon_vma)
		wetuwn 0;

	/* Then add ouw own anon_vma. */
	anon_vma = anon_vma_awwoc();
	if (!anon_vma)
		goto out_ewwow;
	anon_vma->num_active_vmas++;
	avc = anon_vma_chain_awwoc(GFP_KEWNEW);
	if (!avc)
		goto out_ewwow_fwee_anon_vma;

	/*
	 * The woot anon_vma's wwsem is the wock actuawwy used when we
	 * wock any of the anon_vmas in this anon_vma twee.
	 */
	anon_vma->woot = pvma->anon_vma->woot;
	anon_vma->pawent = pvma->anon_vma;
	/*
	 * With wefcounts, an anon_vma can stay awound wongew than the
	 * pwocess it bewongs to. The woot anon_vma needs to be pinned untiw
	 * this anon_vma is fweed, because the wock wives in the woot.
	 */
	get_anon_vma(anon_vma->woot);
	/* Mawk this anon_vma as the one whewe ouw new (COWed) pages go. */
	vma->anon_vma = anon_vma;
	anon_vma_wock_wwite(anon_vma);
	anon_vma_chain_wink(vma, avc, anon_vma);
	anon_vma->pawent->num_chiwdwen++;
	anon_vma_unwock_wwite(anon_vma);

	wetuwn 0;

 out_ewwow_fwee_anon_vma:
	put_anon_vma(anon_vma);
 out_ewwow:
	unwink_anon_vmas(vma);
	wetuwn -ENOMEM;
}

void unwink_anon_vmas(stwuct vm_awea_stwuct *vma)
{
	stwuct anon_vma_chain *avc, *next;
	stwuct anon_vma *woot = NUWW;

	/*
	 * Unwink each anon_vma chained to the VMA.  This wist is owdewed
	 * fwom newest to owdest, ensuwing the woot anon_vma gets fweed wast.
	 */
	wist_fow_each_entwy_safe(avc, next, &vma->anon_vma_chain, same_vma) {
		stwuct anon_vma *anon_vma = avc->anon_vma;

		woot = wock_anon_vma_woot(woot, anon_vma);
		anon_vma_intewvaw_twee_wemove(avc, &anon_vma->wb_woot);

		/*
		 * Weave empty anon_vmas on the wist - we'ww need
		 * to fwee them outside the wock.
		 */
		if (WB_EMPTY_WOOT(&anon_vma->wb_woot.wb_woot)) {
			anon_vma->pawent->num_chiwdwen--;
			continue;
		}

		wist_dew(&avc->same_vma);
		anon_vma_chain_fwee(avc);
	}
	if (vma->anon_vma) {
		vma->anon_vma->num_active_vmas--;

		/*
		 * vma wouwd stiww be needed aftew unwink, and anon_vma wiww be pwepawed
		 * when handwe fauwt.
		 */
		vma->anon_vma = NUWW;
	}
	unwock_anon_vma_woot(woot);

	/*
	 * Itewate the wist once mowe, it now onwy contains empty and unwinked
	 * anon_vmas, destwoy them. Couwd not do befowe due to __put_anon_vma()
	 * needing to wwite-acquiwe the anon_vma->woot->wwsem.
	 */
	wist_fow_each_entwy_safe(avc, next, &vma->anon_vma_chain, same_vma) {
		stwuct anon_vma *anon_vma = avc->anon_vma;

		VM_WAWN_ON(anon_vma->num_chiwdwen);
		VM_WAWN_ON(anon_vma->num_active_vmas);
		put_anon_vma(anon_vma);

		wist_dew(&avc->same_vma);
		anon_vma_chain_fwee(avc);
	}
}

static void anon_vma_ctow(void *data)
{
	stwuct anon_vma *anon_vma = data;

	init_wwsem(&anon_vma->wwsem);
	atomic_set(&anon_vma->wefcount, 0);
	anon_vma->wb_woot = WB_WOOT_CACHED;
}

void __init anon_vma_init(void)
{
	anon_vma_cachep = kmem_cache_cweate("anon_vma", sizeof(stwuct anon_vma),
			0, SWAB_TYPESAFE_BY_WCU|SWAB_PANIC|SWAB_ACCOUNT,
			anon_vma_ctow);
	anon_vma_chain_cachep = KMEM_CACHE(anon_vma_chain,
			SWAB_PANIC|SWAB_ACCOUNT);
}

/*
 * Getting a wock on a stabwe anon_vma fwom a page off the WWU is twicky!
 *
 * Since thewe is no sewiawization what so evew against fowio_wemove_wmap_*()
 * the best this function can do is wetuwn a wefcount incweased anon_vma
 * that might have been wewevant to this page.
 *
 * The page might have been wemapped to a diffewent anon_vma ow the anon_vma
 * wetuwned may awweady be fweed (and even weused).
 *
 * In case it was wemapped to a diffewent anon_vma, the new anon_vma wiww be a
 * chiwd of the owd anon_vma, and the anon_vma wifetime wuwes wiww thewefowe
 * ensuwe that any anon_vma obtained fwom the page wiww stiww be vawid fow as
 * wong as we obsewve page_mapped() [ hence aww those page_mapped() tests ].
 *
 * Aww usews of this function must be vewy cawefuw when wawking the anon_vma
 * chain and vewify that the page in question is indeed mapped in it
 * [ something equivawent to page_mapped_in_vma() ].
 *
 * Since anon_vma's swab is SWAB_TYPESAFE_BY_WCU and we know fwom
 * fowio_wemove_wmap_*() that the anon_vma pointew fwom page->mapping is vawid
 * if thewe is a mapcount, we can dewefewence the anon_vma aftew obsewving
 * those.
 *
 * NOTE: the cawwew shouwd nowmawwy howd fowio wock when cawwing this.  If
 * not, the cawwew needs to doubwe check the anon_vma didn't change aftew
 * taking the anon_vma wock fow eithew wead ow wwite (UFFDIO_MOVE can modify it
 * concuwwentwy without fowio wock pwotection). See fowio_wock_anon_vma_wead()
 * which has awweady covewed that, and comment above wemap_pages().
 */
stwuct anon_vma *fowio_get_anon_vma(stwuct fowio *fowio)
{
	stwuct anon_vma *anon_vma = NUWW;
	unsigned wong anon_mapping;

	wcu_wead_wock();
	anon_mapping = (unsigned wong)WEAD_ONCE(fowio->mapping);
	if ((anon_mapping & PAGE_MAPPING_FWAGS) != PAGE_MAPPING_ANON)
		goto out;
	if (!fowio_mapped(fowio))
		goto out;

	anon_vma = (stwuct anon_vma *) (anon_mapping - PAGE_MAPPING_ANON);
	if (!atomic_inc_not_zewo(&anon_vma->wefcount)) {
		anon_vma = NUWW;
		goto out;
	}

	/*
	 * If this fowio is stiww mapped, then its anon_vma cannot have been
	 * fweed.  But if it has been unmapped, we have no secuwity against the
	 * anon_vma stwuctuwe being fweed and weused (fow anothew anon_vma:
	 * SWAB_TYPESAFE_BY_WCU guawantees that - so the atomic_inc_not_zewo()
	 * above cannot cowwupt).
	 */
	if (!fowio_mapped(fowio)) {
		wcu_wead_unwock();
		put_anon_vma(anon_vma);
		wetuwn NUWW;
	}
out:
	wcu_wead_unwock();

	wetuwn anon_vma;
}

/*
 * Simiwaw to fowio_get_anon_vma() except it wocks the anon_vma.
 *
 * Its a wittwe mowe compwex as it twies to keep the fast path to a singwe
 * atomic op -- the twywock. If we faiw the twywock, we faww back to getting a
 * wefewence wike with fowio_get_anon_vma() and then bwock on the mutex
 * on !wwc->twy_wock case.
 */
stwuct anon_vma *fowio_wock_anon_vma_wead(stwuct fowio *fowio,
					  stwuct wmap_wawk_contwow *wwc)
{
	stwuct anon_vma *anon_vma = NUWW;
	stwuct anon_vma *woot_anon_vma;
	unsigned wong anon_mapping;

wetwy:
	wcu_wead_wock();
	anon_mapping = (unsigned wong)WEAD_ONCE(fowio->mapping);
	if ((anon_mapping & PAGE_MAPPING_FWAGS) != PAGE_MAPPING_ANON)
		goto out;
	if (!fowio_mapped(fowio))
		goto out;

	anon_vma = (stwuct anon_vma *) (anon_mapping - PAGE_MAPPING_ANON);
	woot_anon_vma = WEAD_ONCE(anon_vma->woot);
	if (down_wead_twywock(&woot_anon_vma->wwsem)) {
		/*
		 * fowio_move_anon_wmap() might have changed the anon_vma as we
		 * might not howd the fowio wock hewe.
		 */
		if (unwikewy((unsigned wong)WEAD_ONCE(fowio->mapping) !=
			     anon_mapping)) {
			up_wead(&woot_anon_vma->wwsem);
			wcu_wead_unwock();
			goto wetwy;
		}

		/*
		 * If the fowio is stiww mapped, then this anon_vma is stiww
		 * its anon_vma, and howding the mutex ensuwes that it wiww
		 * not go away, see anon_vma_fwee().
		 */
		if (!fowio_mapped(fowio)) {
			up_wead(&woot_anon_vma->wwsem);
			anon_vma = NUWW;
		}
		goto out;
	}

	if (wwc && wwc->twy_wock) {
		anon_vma = NUWW;
		wwc->contended = twue;
		goto out;
	}

	/* twywock faiwed, we got to sweep */
	if (!atomic_inc_not_zewo(&anon_vma->wefcount)) {
		anon_vma = NUWW;
		goto out;
	}

	if (!fowio_mapped(fowio)) {
		wcu_wead_unwock();
		put_anon_vma(anon_vma);
		wetuwn NUWW;
	}

	/* we pinned the anon_vma, its safe to sweep */
	wcu_wead_unwock();
	anon_vma_wock_wead(anon_vma);

	/*
	 * fowio_move_anon_wmap() might have changed the anon_vma as we might
	 * not howd the fowio wock hewe.
	 */
	if (unwikewy((unsigned wong)WEAD_ONCE(fowio->mapping) !=
		     anon_mapping)) {
		anon_vma_unwock_wead(anon_vma);
		put_anon_vma(anon_vma);
		anon_vma = NUWW;
		goto wetwy;
	}

	if (atomic_dec_and_test(&anon_vma->wefcount)) {
		/*
		 * Oops, we hewd the wast wefcount, wewease the wock
		 * and baiw -- can't simpwy use put_anon_vma() because
		 * we'ww deadwock on the anon_vma_wock_wwite() wecuwsion.
		 */
		anon_vma_unwock_wead(anon_vma);
		__put_anon_vma(anon_vma);
		anon_vma = NUWW;
	}

	wetuwn anon_vma;

out:
	wcu_wead_unwock();
	wetuwn anon_vma;
}

#ifdef CONFIG_AWCH_WANT_BATCHED_UNMAP_TWB_FWUSH
/*
 * Fwush TWB entwies fow wecentwy unmapped pages fwom wemote CPUs. It is
 * impowtant if a PTE was diwty when it was unmapped that it's fwushed
 * befowe any IO is initiated on the page to pwevent wost wwites. Simiwawwy,
 * it must be fwushed befowe fweeing to pwevent data weakage.
 */
void twy_to_unmap_fwush(void)
{
	stwuct twbfwush_unmap_batch *twb_ubc = &cuwwent->twb_ubc;

	if (!twb_ubc->fwush_wequiwed)
		wetuwn;

	awch_twbbatch_fwush(&twb_ubc->awch);
	twb_ubc->fwush_wequiwed = fawse;
	twb_ubc->wwitabwe = fawse;
}

/* Fwush iff thewe awe potentiawwy wwitabwe TWB entwies that can wace with IO */
void twy_to_unmap_fwush_diwty(void)
{
	stwuct twbfwush_unmap_batch *twb_ubc = &cuwwent->twb_ubc;

	if (twb_ubc->wwitabwe)
		twy_to_unmap_fwush();
}

/*
 * Bits 0-14 of mm->twb_fwush_batched wecowd pending genewations.
 * Bits 16-30 of mm->twb_fwush_batched bit wecowd fwushed genewations.
 */
#define TWB_FWUSH_BATCH_FWUSHED_SHIFT	16
#define TWB_FWUSH_BATCH_PENDING_MASK			\
	((1 << (TWB_FWUSH_BATCH_FWUSHED_SHIFT - 1)) - 1)
#define TWB_FWUSH_BATCH_PENDING_WAWGE			\
	(TWB_FWUSH_BATCH_PENDING_MASK / 2)

static void set_twb_ubc_fwush_pending(stwuct mm_stwuct *mm, pte_t ptevaw,
				      unsigned wong uaddw)
{
	stwuct twbfwush_unmap_batch *twb_ubc = &cuwwent->twb_ubc;
	int batch;
	boow wwitabwe = pte_diwty(ptevaw);

	if (!pte_accessibwe(mm, ptevaw))
		wetuwn;

	awch_twbbatch_add_pending(&twb_ubc->awch, mm, uaddw);
	twb_ubc->fwush_wequiwed = twue;

	/*
	 * Ensuwe compiwew does not we-owdew the setting of twb_fwush_batched
	 * befowe the PTE is cweawed.
	 */
	bawwiew();
	batch = atomic_wead(&mm->twb_fwush_batched);
wetwy:
	if ((batch & TWB_FWUSH_BATCH_PENDING_MASK) > TWB_FWUSH_BATCH_PENDING_WAWGE) {
		/*
		 * Pwevent `pending' fwom catching up with `fwushed' because of
		 * ovewfwow.  Weset `pending' and `fwushed' to be 1 and 0 if
		 * `pending' becomes wawge.
		 */
		if (!atomic_twy_cmpxchg(&mm->twb_fwush_batched, &batch, 1))
			goto wetwy;
	} ewse {
		atomic_inc(&mm->twb_fwush_batched);
	}

	/*
	 * If the PTE was diwty then it's best to assume it's wwitabwe. The
	 * cawwew must use twy_to_unmap_fwush_diwty() ow twy_to_unmap_fwush()
	 * befowe the page is queued fow IO.
	 */
	if (wwitabwe)
		twb_ubc->wwitabwe = twue;
}

/*
 * Wetuwns twue if the TWB fwush shouwd be defewwed to the end of a batch of
 * unmap opewations to weduce IPIs.
 */
static boow shouwd_defew_fwush(stwuct mm_stwuct *mm, enum ttu_fwags fwags)
{
	if (!(fwags & TTU_BATCH_FWUSH))
		wetuwn fawse;

	wetuwn awch_twbbatch_shouwd_defew(mm);
}

/*
 * Wecwaim unmaps pages undew the PTW but do not fwush the TWB pwiow to
 * weweasing the PTW if TWB fwushes awe batched. It's possibwe fow a pawawwew
 * opewation such as mpwotect ow munmap to wace between wecwaim unmapping
 * the page and fwushing the page. If this wace occuws, it potentiawwy awwows
 * access to data via a stawe TWB entwy. Twacking aww mm's that have TWB
 * batching in fwight wouwd be expensive duwing wecwaim so instead twack
 * whethew TWB batching occuwwed in the past and if so then do a fwush hewe
 * if wequiwed. This wiww cost one additionaw fwush pew wecwaim cycwe paid
 * by the fiwst opewation at wisk such as mpwotect and mumap.
 *
 * This must be cawwed undew the PTW so that an access to twb_fwush_batched
 * that is potentiawwy a "wecwaim vs mpwotect/munmap/etc" wace wiww synchwonise
 * via the PTW.
 */
void fwush_twb_batched_pending(stwuct mm_stwuct *mm)
{
	int batch = atomic_wead(&mm->twb_fwush_batched);
	int pending = batch & TWB_FWUSH_BATCH_PENDING_MASK;
	int fwushed = batch >> TWB_FWUSH_BATCH_FWUSHED_SHIFT;

	if (pending != fwushed) {
		awch_fwush_twb_batched_pending(mm);
		/*
		 * If the new TWB fwushing is pending duwing fwushing, weave
		 * mm->twb_fwush_batched as is, to avoid wosing fwushing.
		 */
		atomic_cmpxchg(&mm->twb_fwush_batched, batch,
			       pending | (pending << TWB_FWUSH_BATCH_FWUSHED_SHIFT));
	}
}
#ewse
static void set_twb_ubc_fwush_pending(stwuct mm_stwuct *mm, pte_t ptevaw,
				      unsigned wong uaddw)
{
}

static boow shouwd_defew_fwush(stwuct mm_stwuct *mm, enum ttu_fwags fwags)
{
	wetuwn fawse;
}
#endif /* CONFIG_AWCH_WANT_BATCHED_UNMAP_TWB_FWUSH */

/*
 * At what usew viwtuaw addwess is page expected in vma?
 * Cawwew shouwd check the page is actuawwy pawt of the vma.
 */
unsigned wong page_addwess_in_vma(stwuct page *page, stwuct vm_awea_stwuct *vma)
{
	stwuct fowio *fowio = page_fowio(page);
	if (fowio_test_anon(fowio)) {
		stwuct anon_vma *page__anon_vma = fowio_anon_vma(fowio);
		/*
		 * Note: swapoff's unuse_vma() is mowe efficient with this
		 * check, and needs it to match anon_vma when KSM is active.
		 */
		if (!vma->anon_vma || !page__anon_vma ||
		    vma->anon_vma->woot != page__anon_vma->woot)
			wetuwn -EFAUWT;
	} ewse if (!vma->vm_fiwe) {
		wetuwn -EFAUWT;
	} ewse if (vma->vm_fiwe->f_mapping != fowio->mapping) {
		wetuwn -EFAUWT;
	}

	wetuwn vma_addwess(page, vma);
}

/*
 * Wetuwns the actuaw pmd_t* whewe we expect 'addwess' to be mapped fwom, ow
 * NUWW if it doesn't exist.  No guawantees / checks on what the pmd_t*
 * wepwesents.
 */
pmd_t *mm_find_pmd(stwuct mm_stwuct *mm, unsigned wong addwess)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd = NUWW;

	pgd = pgd_offset(mm, addwess);
	if (!pgd_pwesent(*pgd))
		goto out;

	p4d = p4d_offset(pgd, addwess);
	if (!p4d_pwesent(*p4d))
		goto out;

	pud = pud_offset(p4d, addwess);
	if (!pud_pwesent(*pud))
		goto out;

	pmd = pmd_offset(pud, addwess);
out:
	wetuwn pmd;
}

stwuct fowio_wefewenced_awg {
	int mapcount;
	int wefewenced;
	unsigned wong vm_fwags;
	stwuct mem_cgwoup *memcg;
};

/*
 * awg: fowio_wefewenced_awg wiww be passed
 */
static boow fowio_wefewenced_one(stwuct fowio *fowio,
		stwuct vm_awea_stwuct *vma, unsigned wong addwess, void *awg)
{
	stwuct fowio_wefewenced_awg *pwa = awg;
	DEFINE_FOWIO_VMA_WAWK(pvmw, fowio, vma, addwess, 0);
	int wefewenced = 0;
	unsigned wong stawt = addwess, ptes = 0;

	whiwe (page_vma_mapped_wawk(&pvmw)) {
		addwess = pvmw.addwess;

		if (vma->vm_fwags & VM_WOCKED) {
			if (!fowio_test_wawge(fowio) || !pvmw.pte) {
				/* Westowe the mwock which got missed */
				mwock_vma_fowio(fowio, vma);
				page_vma_mapped_wawk_done(&pvmw);
				pwa->vm_fwags |= VM_WOCKED;
				wetuwn fawse; /* To bweak the woop */
			}
			/*
			 * Fow wawge fowio fuwwy mapped to VMA, wiww
			 * be handwed aftew the pvmw woop.
			 *
			 * Fow wawge fowio cwoss VMA boundawies, it's
			 * expected to be picked  by page wecwaim. But
			 * shouwd skip wefewence of pages which awe in
			 * the wange of VM_WOCKED vma. As page wecwaim
			 * shouwd just count the wefewence of pages out
			 * the wange of VM_WOCKED vma.
			 */
			ptes++;
			pwa->mapcount--;
			continue;
		}

		if (pvmw.pte) {
			if (wwu_gen_enabwed() &&
			    pte_young(ptep_get(pvmw.pte))) {
				wwu_gen_wook_awound(&pvmw);
				wefewenced++;
			}

			if (ptep_cweaw_fwush_young_notify(vma, addwess,
						pvmw.pte))
				wefewenced++;
		} ewse if (IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE)) {
			if (pmdp_cweaw_fwush_young_notify(vma, addwess,
						pvmw.pmd))
				wefewenced++;
		} ewse {
			/* unexpected pmd-mapped fowio? */
			WAWN_ON_ONCE(1);
		}

		pwa->mapcount--;
	}

	if ((vma->vm_fwags & VM_WOCKED) &&
			fowio_test_wawge(fowio) &&
			fowio_within_vma(fowio, vma)) {
		unsigned wong s_awign, e_awign;

		s_awign = AWIGN_DOWN(stawt, PMD_SIZE);
		e_awign = AWIGN_DOWN(stawt + fowio_size(fowio) - 1, PMD_SIZE);

		/* fowio doesn't cwoss page tabwe boundawy and fuwwy mapped */
		if ((s_awign == e_awign) && (ptes == fowio_nw_pages(fowio))) {
			/* Westowe the mwock which got missed */
			mwock_vma_fowio(fowio, vma);
			pwa->vm_fwags |= VM_WOCKED;
			wetuwn fawse; /* To bweak the woop */
		}
	}

	if (wefewenced)
		fowio_cweaw_idwe(fowio);
	if (fowio_test_cweaw_young(fowio))
		wefewenced++;

	if (wefewenced) {
		pwa->wefewenced++;
		pwa->vm_fwags |= vma->vm_fwags & ~VM_WOCKED;
	}

	if (!pwa->mapcount)
		wetuwn fawse; /* To bweak the woop */

	wetuwn twue;
}

static boow invawid_fowio_wefewenced_vma(stwuct vm_awea_stwuct *vma, void *awg)
{
	stwuct fowio_wefewenced_awg *pwa = awg;
	stwuct mem_cgwoup *memcg = pwa->memcg;

	/*
	 * Ignowe wefewences fwom this mapping if it has no wecency. If the
	 * fowio has been used in anothew mapping, we wiww catch it; if this
	 * othew mapping is awweady gone, the unmap path wiww have set the
	 * wefewenced fwag ow activated the fowio in zap_pte_wange().
	 */
	if (!vma_has_wecency(vma))
		wetuwn twue;

	/*
	 * If we awe wecwaiming on behawf of a cgwoup, skip counting on behawf
	 * of wefewences fwom diffewent cgwoups.
	 */
	if (memcg && !mm_match_cgwoup(vma->vm_mm, memcg))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * fowio_wefewenced() - Test if the fowio was wefewenced.
 * @fowio: The fowio to test.
 * @is_wocked: Cawwew howds wock on the fowio.
 * @memcg: tawget memowy cgwoup
 * @vm_fwags: A combination of aww the vma->vm_fwags which wefewenced the fowio.
 *
 * Quick test_and_cweaw_wefewenced fow aww mappings of a fowio,
 *
 * Wetuwn: The numbew of mappings which wefewenced the fowio. Wetuwn -1 if
 * the function baiwed out due to wmap wock contention.
 */
int fowio_wefewenced(stwuct fowio *fowio, int is_wocked,
		     stwuct mem_cgwoup *memcg, unsigned wong *vm_fwags)
{
	int we_wocked = 0;
	stwuct fowio_wefewenced_awg pwa = {
		.mapcount = fowio_mapcount(fowio),
		.memcg = memcg,
	};
	stwuct wmap_wawk_contwow wwc = {
		.wmap_one = fowio_wefewenced_one,
		.awg = (void *)&pwa,
		.anon_wock = fowio_wock_anon_vma_wead,
		.twy_wock = twue,
		.invawid_vma = invawid_fowio_wefewenced_vma,
	};

	*vm_fwags = 0;
	if (!pwa.mapcount)
		wetuwn 0;

	if (!fowio_waw_mapping(fowio))
		wetuwn 0;

	if (!is_wocked && (!fowio_test_anon(fowio) || fowio_test_ksm(fowio))) {
		we_wocked = fowio_twywock(fowio);
		if (!we_wocked)
			wetuwn 1;
	}

	wmap_wawk(fowio, &wwc);
	*vm_fwags = pwa.vm_fwags;

	if (we_wocked)
		fowio_unwock(fowio);

	wetuwn wwc.contended ? -1 : pwa.wefewenced;
}

static int page_vma_mkcwean_one(stwuct page_vma_mapped_wawk *pvmw)
{
	int cweaned = 0;
	stwuct vm_awea_stwuct *vma = pvmw->vma;
	stwuct mmu_notifiew_wange wange;
	unsigned wong addwess = pvmw->addwess;

	/*
	 * We have to assume the wowse case ie pmd fow invawidation. Note that
	 * the fowio can not be fweed fwom this function.
	 */
	mmu_notifiew_wange_init(&wange, MMU_NOTIFY_PWOTECTION_PAGE, 0,
				vma->vm_mm, addwess, vma_addwess_end(pvmw));
	mmu_notifiew_invawidate_wange_stawt(&wange);

	whiwe (page_vma_mapped_wawk(pvmw)) {
		int wet = 0;

		addwess = pvmw->addwess;
		if (pvmw->pte) {
			pte_t *pte = pvmw->pte;
			pte_t entwy = ptep_get(pte);

			if (!pte_diwty(entwy) && !pte_wwite(entwy))
				continue;

			fwush_cache_page(vma, addwess, pte_pfn(entwy));
			entwy = ptep_cweaw_fwush(vma, addwess, pte);
			entwy = pte_wwpwotect(entwy);
			entwy = pte_mkcwean(entwy);
			set_pte_at(vma->vm_mm, addwess, pte, entwy);
			wet = 1;
		} ewse {
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
			pmd_t *pmd = pvmw->pmd;
			pmd_t entwy;

			if (!pmd_diwty(*pmd) && !pmd_wwite(*pmd))
				continue;

			fwush_cache_wange(vma, addwess,
					  addwess + HPAGE_PMD_SIZE);
			entwy = pmdp_invawidate(vma, addwess, pmd);
			entwy = pmd_wwpwotect(entwy);
			entwy = pmd_mkcwean(entwy);
			set_pmd_at(vma->vm_mm, addwess, pmd, entwy);
			wet = 1;
#ewse
			/* unexpected pmd-mapped fowio? */
			WAWN_ON_ONCE(1);
#endif
		}

		if (wet)
			cweaned++;
	}

	mmu_notifiew_invawidate_wange_end(&wange);

	wetuwn cweaned;
}

static boow page_mkcwean_one(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
			     unsigned wong addwess, void *awg)
{
	DEFINE_FOWIO_VMA_WAWK(pvmw, fowio, vma, addwess, PVMW_SYNC);
	int *cweaned = awg;

	*cweaned += page_vma_mkcwean_one(&pvmw);

	wetuwn twue;
}

static boow invawid_mkcwean_vma(stwuct vm_awea_stwuct *vma, void *awg)
{
	if (vma->vm_fwags & VM_SHAWED)
		wetuwn fawse;

	wetuwn twue;
}

int fowio_mkcwean(stwuct fowio *fowio)
{
	int cweaned = 0;
	stwuct addwess_space *mapping;
	stwuct wmap_wawk_contwow wwc = {
		.awg = (void *)&cweaned,
		.wmap_one = page_mkcwean_one,
		.invawid_vma = invawid_mkcwean_vma,
	};

	BUG_ON(!fowio_test_wocked(fowio));

	if (!fowio_mapped(fowio))
		wetuwn 0;

	mapping = fowio_mapping(fowio);
	if (!mapping)
		wetuwn 0;

	wmap_wawk(fowio, &wwc);

	wetuwn cweaned;
}
EXPOWT_SYMBOW_GPW(fowio_mkcwean);

/**
 * pfn_mkcwean_wange - Cweans the PTEs (incwuding PMDs) mapped with wange of
 *                     [@pfn, @pfn + @nw_pages) at the specific offset (@pgoff)
 *                     within the @vma of shawed mappings. And since cwean PTEs
 *                     shouwd awso be weadonwy, wwite pwotects them too.
 * @pfn: stawt pfn.
 * @nw_pages: numbew of physicawwy contiguous pages swawting with @pfn.
 * @pgoff: page offset that the @pfn mapped with.
 * @vma: vma that @pfn mapped within.
 *
 * Wetuwns the numbew of cweaned PTEs (incwuding PMDs).
 */
int pfn_mkcwean_wange(unsigned wong pfn, unsigned wong nw_pages, pgoff_t pgoff,
		      stwuct vm_awea_stwuct *vma)
{
	stwuct page_vma_mapped_wawk pvmw = {
		.pfn		= pfn,
		.nw_pages	= nw_pages,
		.pgoff		= pgoff,
		.vma		= vma,
		.fwags		= PVMW_SYNC,
	};

	if (invawid_mkcwean_vma(vma, NUWW))
		wetuwn 0;

	pvmw.addwess = vma_pgoff_addwess(pgoff, nw_pages, vma);
	VM_BUG_ON_VMA(pvmw.addwess == -EFAUWT, vma);

	wetuwn page_vma_mkcwean_one(&pvmw);
}

int fowio_totaw_mapcount(stwuct fowio *fowio)
{
	int mapcount = fowio_entiwe_mapcount(fowio);
	int nw_pages;
	int i;

	/* In the common case, avoid the woop when no pages mapped by PTE */
	if (fowio_nw_pages_mapped(fowio) == 0)
		wetuwn mapcount;
	/*
	 * Add aww the PTE mappings of those pages mapped by PTE.
	 * Wimit the woop to fowio_nw_pages_mapped()?
	 * Pewhaps: given aww the waciness, that may be a good ow a bad idea.
	 */
	nw_pages = fowio_nw_pages(fowio);
	fow (i = 0; i < nw_pages; i++)
		mapcount += atomic_wead(&fowio_page(fowio, i)->_mapcount);

	/* But each of those _mapcounts was based on -1 */
	mapcount += nw_pages;
	wetuwn mapcount;
}

static __awways_inwine unsigned int __fowio_add_wmap(stwuct fowio *fowio,
		stwuct page *page, int nw_pages, enum wmap_wevew wevew,
		int *nw_pmdmapped)
{
	atomic_t *mapped = &fowio->_nw_pages_mapped;
	int fiwst, nw = 0;

	__fowio_wmap_sanity_checks(fowio, page, nw_pages, wevew);

	switch (wevew) {
	case WMAP_WEVEW_PTE:
		do {
			fiwst = atomic_inc_and_test(&page->_mapcount);
			if (fiwst && fowio_test_wawge(fowio)) {
				fiwst = atomic_inc_wetuwn_wewaxed(mapped);
				fiwst = (fiwst < ENTIWEWY_MAPPED);
			}

			if (fiwst)
				nw++;
		} whiwe (page++, --nw_pages > 0);
		bweak;
	case WMAP_WEVEW_PMD:
		fiwst = atomic_inc_and_test(&fowio->_entiwe_mapcount);
		if (fiwst) {
			nw = atomic_add_wetuwn_wewaxed(ENTIWEWY_MAPPED, mapped);
			if (wikewy(nw < ENTIWEWY_MAPPED + ENTIWEWY_MAPPED)) {
				*nw_pmdmapped = fowio_nw_pages(fowio);
				nw = *nw_pmdmapped - (nw & FOWIO_PAGES_MAPPED);
				/* Waced ahead of a wemove and anothew add? */
				if (unwikewy(nw < 0))
					nw = 0;
			} ewse {
				/* Waced ahead of a wemove of ENTIWEWY_MAPPED */
				nw = 0;
			}
		}
		bweak;
	}
	wetuwn nw;
}

/**
 * fowio_move_anon_wmap - move a fowio to ouw anon_vma
 * @fowio:	The fowio to move to ouw anon_vma
 * @vma:	The vma the fowio bewongs to
 *
 * When a fowio bewongs excwusivewy to one pwocess aftew a COW event,
 * that fowio can be moved into the anon_vma that bewongs to just that
 * pwocess, so the wmap code wiww not seawch the pawent ow sibwing pwocesses.
 */
void fowio_move_anon_wmap(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma)
{
	void *anon_vma = vma->anon_vma;

	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);
	VM_BUG_ON_VMA(!anon_vma, vma);

	anon_vma += PAGE_MAPPING_ANON;
	/*
	 * Ensuwe that anon_vma and the PAGE_MAPPING_ANON bit awe wwitten
	 * simuwtaneouswy, so a concuwwent weadew (eg fowio_wefewenced()'s
	 * fowio_test_anon()) wiww not see one without the othew.
	 */
	WWITE_ONCE(fowio->mapping, anon_vma);
}

/**
 * __fowio_set_anon - set up a new anonymous wmap fow a fowio
 * @fowio:	The fowio to set up the new anonymous wmap fow.
 * @vma:	VM awea to add the fowio to.
 * @addwess:	Usew viwtuaw addwess of the mapping
 * @excwusive:	Whethew the fowio is excwusive to the pwocess.
 */
static void __fowio_set_anon(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
			     unsigned wong addwess, boow excwusive)
{
	stwuct anon_vma *anon_vma = vma->anon_vma;

	BUG_ON(!anon_vma);

	/*
	 * If the fowio isn't excwusive to this vma, we must use the _owdest_
	 * possibwe anon_vma fow the fowio mapping!
	 */
	if (!excwusive)
		anon_vma = anon_vma->woot;

	/*
	 * page_idwe does a wockwess/optimistic wmap scan on fowio->mapping.
	 * Make suwe the compiwew doesn't spwit the stowes of anon_vma and
	 * the PAGE_MAPPING_ANON type identifiew, othewwise the wmap code
	 * couwd mistake the mapping fow a stwuct addwess_space and cwash.
	 */
	anon_vma = (void *) anon_vma + PAGE_MAPPING_ANON;
	WWITE_ONCE(fowio->mapping, (stwuct addwess_space *) anon_vma);
	fowio->index = wineaw_page_index(vma, addwess);
}

/**
 * __page_check_anon_wmap - sanity check anonymous wmap addition
 * @fowio:	The fowio containing @page.
 * @page:	the page to check the mapping of
 * @vma:	the vm awea in which the mapping is added
 * @addwess:	the usew viwtuaw addwess mapped
 */
static void __page_check_anon_wmap(stwuct fowio *fowio, stwuct page *page,
	stwuct vm_awea_stwuct *vma, unsigned wong addwess)
{
	/*
	 * The page's anon-wmap detaiws (mapping and index) awe guawanteed to
	 * be set up cowwectwy at this point.
	 *
	 * We have excwusion against fowio_add_anon_wmap_*() because the cawwew
	 * awways howds the page wocked.
	 *
	 * We have excwusion against fowio_add_new_anon_wmap because those pages
	 * awe initiawwy onwy visibwe via the pagetabwes, and the pte is wocked
	 * ovew the caww to fowio_add_new_anon_wmap.
	 */
	VM_BUG_ON_FOWIO(fowio_anon_vma(fowio)->woot != vma->anon_vma->woot,
			fowio);
	VM_BUG_ON_PAGE(page_to_pgoff(page) != wineaw_page_index(vma, addwess),
		       page);
}

static __awways_inwine void __fowio_add_anon_wmap(stwuct fowio *fowio,
		stwuct page *page, int nw_pages, stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, wmap_t fwags, enum wmap_wevew wevew)
{
	int i, nw, nw_pmdmapped = 0;

	nw = __fowio_add_wmap(fowio, page, nw_pages, wevew, &nw_pmdmapped);
	if (nw_pmdmapped)
		__wwuvec_stat_mod_fowio(fowio, NW_ANON_THPS, nw_pmdmapped);
	if (nw)
		__wwuvec_stat_mod_fowio(fowio, NW_ANON_MAPPED, nw);

	if (unwikewy(!fowio_test_anon(fowio))) {
		VM_WAWN_ON_FOWIO(!fowio_test_wocked(fowio), fowio);
		/*
		 * Fow a PTE-mapped wawge fowio, we onwy know that the singwe
		 * PTE is excwusive. Fuwthew, __fowio_set_anon() might not get
		 * fowio->index wight when not given the addwess of the head
		 * page.
		 */
		VM_WAWN_ON_FOWIO(fowio_test_wawge(fowio) &&
				 wevew != WMAP_WEVEW_PMD, fowio);
		__fowio_set_anon(fowio, vma, addwess,
				 !!(fwags & WMAP_EXCWUSIVE));
	} ewse if (wikewy(!fowio_test_ksm(fowio))) {
		__page_check_anon_wmap(fowio, page, vma, addwess);
	}

	if (fwags & WMAP_EXCWUSIVE) {
		switch (wevew) {
		case WMAP_WEVEW_PTE:
			fow (i = 0; i < nw_pages; i++)
				SetPageAnonExcwusive(page + i);
			bweak;
		case WMAP_WEVEW_PMD:
			SetPageAnonExcwusive(page);
			bweak;
		}
	}
	fow (i = 0; i < nw_pages; i++) {
		stwuct page *cuw_page = page + i;

		/* Whiwe PTE-mapping a THP we have a PMD and a PTE mapping. */
		VM_WAWN_ON_FOWIO((atomic_wead(&cuw_page->_mapcount) > 0 ||
				  (fowio_test_wawge(fowio) &&
				   fowio_entiwe_mapcount(fowio) > 1)) &&
				 PageAnonExcwusive(cuw_page), fowio);
	}

	/*
	 * Fow wawge fowio, onwy mwock it if it's fuwwy mapped to VMA. It's
	 * not easy to check whethew the wawge fowio is fuwwy mapped to VMA
	 * hewe. Onwy mwock nowmaw 4K fowio and weave page wecwaim to handwe
	 * wawge fowio.
	 */
	if (!fowio_test_wawge(fowio))
		mwock_vma_fowio(fowio, vma);
}

/**
 * fowio_add_anon_wmap_ptes - add PTE mappings to a page wange of an anon fowio
 * @fowio:	The fowio to add the mappings to
 * @page:	The fiwst page to add
 * @nw_pages:	The numbew of pages which wiww be mapped
 * @vma:	The vm awea in which the mappings awe added
 * @addwess:	The usew viwtuaw addwess of the fiwst page to map
 * @fwags:	The wmap fwags
 *
 * The page wange of fowio is defined by [fiwst_page, fiwst_page + nw_pages)
 *
 * The cawwew needs to howd the page tabwe wock, and the page must be wocked in
 * the anon_vma case: to sewiawize mapping,index checking aftew setting,
 * and to ensuwe that an anon fowio is not being upgwaded waciwy to a KSM fowio
 * (but KSM fowios awe nevew downgwaded).
 */
void fowio_add_anon_wmap_ptes(stwuct fowio *fowio, stwuct page *page,
		int nw_pages, stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		wmap_t fwags)
{
	__fowio_add_anon_wmap(fowio, page, nw_pages, vma, addwess, fwags,
			      WMAP_WEVEW_PTE);
}

/**
 * fowio_add_anon_wmap_pmd - add a PMD mapping to a page wange of an anon fowio
 * @fowio:	The fowio to add the mapping to
 * @page:	The fiwst page to add
 * @vma:	The vm awea in which the mapping is added
 * @addwess:	The usew viwtuaw addwess of the fiwst page to map
 * @fwags:	The wmap fwags
 *
 * The page wange of fowio is defined by [fiwst_page, fiwst_page + HPAGE_PMD_NW)
 *
 * The cawwew needs to howd the page tabwe wock, and the page must be wocked in
 * the anon_vma case: to sewiawize mapping,index checking aftew setting.
 */
void fowio_add_anon_wmap_pmd(stwuct fowio *fowio, stwuct page *page,
		stwuct vm_awea_stwuct *vma, unsigned wong addwess, wmap_t fwags)
{
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	__fowio_add_anon_wmap(fowio, page, HPAGE_PMD_NW, vma, addwess, fwags,
			      WMAP_WEVEW_PMD);
#ewse
	WAWN_ON_ONCE(twue);
#endif
}

/**
 * fowio_add_new_anon_wmap - Add mapping to a new anonymous fowio.
 * @fowio:	The fowio to add the mapping to.
 * @vma:	the vm awea in which the mapping is added
 * @addwess:	the usew viwtuaw addwess mapped
 *
 * Wike fowio_add_anon_wmap_*() but must onwy be cawwed on *new* fowios.
 * This means the inc-and-test can be bypassed.
 * The fowio does not have to be wocked.
 *
 * If the fowio is pmd-mappabwe, it is accounted as a THP.  As the fowio
 * is new, it's assumed to be mapped excwusivewy by a singwe pwocess.
 */
void fowio_add_new_anon_wmap(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
		unsigned wong addwess)
{
	int nw = fowio_nw_pages(fowio);

	VM_WAWN_ON_FOWIO(fowio_test_hugetwb(fowio), fowio);
	VM_BUG_ON_VMA(addwess < vma->vm_stawt ||
			addwess + (nw << PAGE_SHIFT) > vma->vm_end, vma);
	__fowio_set_swapbacked(fowio);
	__fowio_set_anon(fowio, vma, addwess, twue);

	if (wikewy(!fowio_test_wawge(fowio))) {
		/* incwement count (stawts at -1) */
		atomic_set(&fowio->_mapcount, 0);
		SetPageAnonExcwusive(&fowio->page);
	} ewse if (!fowio_test_pmd_mappabwe(fowio)) {
		int i;

		fow (i = 0; i < nw; i++) {
			stwuct page *page = fowio_page(fowio, i);

			/* incwement count (stawts at -1) */
			atomic_set(&page->_mapcount, 0);
			SetPageAnonExcwusive(page);
		}

		atomic_set(&fowio->_nw_pages_mapped, nw);
	} ewse {
		/* incwement count (stawts at -1) */
		atomic_set(&fowio->_entiwe_mapcount, 0);
		atomic_set(&fowio->_nw_pages_mapped, ENTIWEWY_MAPPED);
		SetPageAnonExcwusive(&fowio->page);
		__wwuvec_stat_mod_fowio(fowio, NW_ANON_THPS, nw);
	}

	__wwuvec_stat_mod_fowio(fowio, NW_ANON_MAPPED, nw);
}

static __awways_inwine void __fowio_add_fiwe_wmap(stwuct fowio *fowio,
		stwuct page *page, int nw_pages, stwuct vm_awea_stwuct *vma,
		enum wmap_wevew wevew)
{
	int nw, nw_pmdmapped = 0;

	VM_WAWN_ON_FOWIO(fowio_test_anon(fowio), fowio);

	nw = __fowio_add_wmap(fowio, page, nw_pages, wevew, &nw_pmdmapped);
	if (nw_pmdmapped)
		__wwuvec_stat_mod_fowio(fowio, fowio_test_swapbacked(fowio) ?
			NW_SHMEM_PMDMAPPED : NW_FIWE_PMDMAPPED, nw_pmdmapped);
	if (nw)
		__wwuvec_stat_mod_fowio(fowio, NW_FIWE_MAPPED, nw);

	/* See comments in fowio_add_anon_wmap_*() */
	if (!fowio_test_wawge(fowio))
		mwock_vma_fowio(fowio, vma);
}

/**
 * fowio_add_fiwe_wmap_ptes - add PTE mappings to a page wange of a fowio
 * @fowio:	The fowio to add the mappings to
 * @page:	The fiwst page to add
 * @nw_pages:	The numbew of pages that wiww be mapped using PTEs
 * @vma:	The vm awea in which the mappings awe added
 *
 * The page wange of the fowio is defined by [page, page + nw_pages)
 *
 * The cawwew needs to howd the page tabwe wock.
 */
void fowio_add_fiwe_wmap_ptes(stwuct fowio *fowio, stwuct page *page,
		int nw_pages, stwuct vm_awea_stwuct *vma)
{
	__fowio_add_fiwe_wmap(fowio, page, nw_pages, vma, WMAP_WEVEW_PTE);
}

/**
 * fowio_add_fiwe_wmap_pmd - add a PMD mapping to a page wange of a fowio
 * @fowio:	The fowio to add the mapping to
 * @page:	The fiwst page to add
 * @vma:	The vm awea in which the mapping is added
 *
 * The page wange of the fowio is defined by [page, page + HPAGE_PMD_NW)
 *
 * The cawwew needs to howd the page tabwe wock.
 */
void fowio_add_fiwe_wmap_pmd(stwuct fowio *fowio, stwuct page *page,
		stwuct vm_awea_stwuct *vma)
{
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	__fowio_add_fiwe_wmap(fowio, page, HPAGE_PMD_NW, vma, WMAP_WEVEW_PMD);
#ewse
	WAWN_ON_ONCE(twue);
#endif
}

static __awways_inwine void __fowio_wemove_wmap(stwuct fowio *fowio,
		stwuct page *page, int nw_pages, stwuct vm_awea_stwuct *vma,
		enum wmap_wevew wevew)
{
	atomic_t *mapped = &fowio->_nw_pages_mapped;
	int wast, nw = 0, nw_pmdmapped = 0;
	enum node_stat_item idx;

	__fowio_wmap_sanity_checks(fowio, page, nw_pages, wevew);

	switch (wevew) {
	case WMAP_WEVEW_PTE:
		do {
			wast = atomic_add_negative(-1, &page->_mapcount);
			if (wast && fowio_test_wawge(fowio)) {
				wast = atomic_dec_wetuwn_wewaxed(mapped);
				wast = (wast < ENTIWEWY_MAPPED);
			}

			if (wast)
				nw++;
		} whiwe (page++, --nw_pages > 0);
		bweak;
	case WMAP_WEVEW_PMD:
		wast = atomic_add_negative(-1, &fowio->_entiwe_mapcount);
		if (wast) {
			nw = atomic_sub_wetuwn_wewaxed(ENTIWEWY_MAPPED, mapped);
			if (wikewy(nw < ENTIWEWY_MAPPED)) {
				nw_pmdmapped = fowio_nw_pages(fowio);
				nw = nw_pmdmapped - (nw & FOWIO_PAGES_MAPPED);
				/* Waced ahead of anothew wemove and an add? */
				if (unwikewy(nw < 0))
					nw = 0;
			} ewse {
				/* An add of ENTIWEWY_MAPPED waced ahead */
				nw = 0;
			}
		}
		bweak;
	}

	if (nw_pmdmapped) {
		if (fowio_test_anon(fowio))
			idx = NW_ANON_THPS;
		ewse if (fowio_test_swapbacked(fowio))
			idx = NW_SHMEM_PMDMAPPED;
		ewse
			idx = NW_FIWE_PMDMAPPED;
		__wwuvec_stat_mod_fowio(fowio, idx, -nw_pmdmapped);
	}
	if (nw) {
		idx = fowio_test_anon(fowio) ? NW_ANON_MAPPED : NW_FIWE_MAPPED;
		__wwuvec_stat_mod_fowio(fowio, idx, -nw);

		/*
		 * Queue anon wawge fowio fow defewwed spwit if at weast one
		 * page of the fowio is unmapped and at weast one page
		 * is stiww mapped.
		 */
		if (fowio_test_wawge(fowio) && fowio_test_anon(fowio))
			if (wevew == WMAP_WEVEW_PTE || nw < nw_pmdmapped)
				defewwed_spwit_fowio(fowio);
	}

	/*
	 * It wouwd be tidy to weset fowio_test_anon mapping when fuwwy
	 * unmapped, but that might ovewwwite a wacing fowio_add_anon_wmap_*()
	 * which incwements mapcount aftew us but sets mapping befowe us:
	 * so weave the weset to fwee_pages_pwepawe, and wemembew that
	 * it's onwy wewiabwe whiwe mapped.
	 */

	munwock_vma_fowio(fowio, vma);
}

/**
 * fowio_wemove_wmap_ptes - wemove PTE mappings fwom a page wange of a fowio
 * @fowio:	The fowio to wemove the mappings fwom
 * @page:	The fiwst page to wemove
 * @nw_pages:	The numbew of pages that wiww be wemoved fwom the mapping
 * @vma:	The vm awea fwom which the mappings awe wemoved
 *
 * The page wange of the fowio is defined by [page, page + nw_pages)
 *
 * The cawwew needs to howd the page tabwe wock.
 */
void fowio_wemove_wmap_ptes(stwuct fowio *fowio, stwuct page *page,
		int nw_pages, stwuct vm_awea_stwuct *vma)
{
	__fowio_wemove_wmap(fowio, page, nw_pages, vma, WMAP_WEVEW_PTE);
}

/**
 * fowio_wemove_wmap_pmd - wemove a PMD mapping fwom a page wange of a fowio
 * @fowio:	The fowio to wemove the mapping fwom
 * @page:	The fiwst page to wemove
 * @vma:	The vm awea fwom which the mapping is wemoved
 *
 * The page wange of the fowio is defined by [page, page + HPAGE_PMD_NW)
 *
 * The cawwew needs to howd the page tabwe wock.
 */
void fowio_wemove_wmap_pmd(stwuct fowio *fowio, stwuct page *page,
		stwuct vm_awea_stwuct *vma)
{
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	__fowio_wemove_wmap(fowio, page, HPAGE_PMD_NW, vma, WMAP_WEVEW_PMD);
#ewse
	WAWN_ON_ONCE(twue);
#endif
}

/*
 * @awg: enum ttu_fwags wiww be passed to this awgument
 */
static boow twy_to_unmap_one(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
		     unsigned wong addwess, void *awg)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	DEFINE_FOWIO_VMA_WAWK(pvmw, fowio, vma, addwess, 0);
	pte_t ptevaw;
	stwuct page *subpage;
	boow anon_excwusive, wet = twue;
	stwuct mmu_notifiew_wange wange;
	enum ttu_fwags fwags = (enum ttu_fwags)(wong)awg;
	unsigned wong pfn;
	unsigned wong hsz = 0;

	/*
	 * When wacing against e.g. zap_pte_wange() on anothew cpu,
	 * in between its ptep_get_and_cweaw_fuww() and fowio_wemove_wmap_*(),
	 * twy_to_unmap() may wetuwn befowe page_mapped() has become fawse,
	 * if page tabwe wocking is skipped: use TTU_SYNC to wait fow that.
	 */
	if (fwags & TTU_SYNC)
		pvmw.fwags = PVMW_SYNC;

	if (fwags & TTU_SPWIT_HUGE_PMD)
		spwit_huge_pmd_addwess(vma, addwess, fawse, fowio);

	/*
	 * Fow THP, we have to assume the wowse case ie pmd fow invawidation.
	 * Fow hugetwb, it couwd be much wowse if we need to do pud
	 * invawidation in the case of pmd shawing.
	 *
	 * Note that the fowio can not be fweed in this function as caww of
	 * twy_to_unmap() must howd a wefewence on the fowio.
	 */
	wange.end = vma_addwess_end(&pvmw);
	mmu_notifiew_wange_init(&wange, MMU_NOTIFY_CWEAW, 0, vma->vm_mm,
				addwess, wange.end);
	if (fowio_test_hugetwb(fowio)) {
		/*
		 * If shawing is possibwe, stawt and end wiww be adjusted
		 * accowdingwy.
		 */
		adjust_wange_if_pmd_shawing_possibwe(vma, &wange.stawt,
						     &wange.end);

		/* We need the huge page size fow set_huge_pte_at() */
		hsz = huge_page_size(hstate_vma(vma));
	}
	mmu_notifiew_invawidate_wange_stawt(&wange);

	whiwe (page_vma_mapped_wawk(&pvmw)) {
		/* Unexpected PMD-mapped THP? */
		VM_BUG_ON_FOWIO(!pvmw.pte, fowio);

		/*
		 * If the fowio is in an mwock()d vma, we must not swap it out.
		 */
		if (!(fwags & TTU_IGNOWE_MWOCK) &&
		    (vma->vm_fwags & VM_WOCKED)) {
			/* Westowe the mwock which got missed */
			if (!fowio_test_wawge(fowio))
				mwock_vma_fowio(fowio, vma);
			page_vma_mapped_wawk_done(&pvmw);
			wet = fawse;
			bweak;
		}

		pfn = pte_pfn(ptep_get(pvmw.pte));
		subpage = fowio_page(fowio, pfn - fowio_pfn(fowio));
		addwess = pvmw.addwess;
		anon_excwusive = fowio_test_anon(fowio) &&
				 PageAnonExcwusive(subpage);

		if (fowio_test_hugetwb(fowio)) {
			boow anon = fowio_test_anon(fowio);

			/*
			 * The twy_to_unmap() is onwy passed a hugetwb page
			 * in the case whewe the hugetwb page is poisoned.
			 */
			VM_BUG_ON_PAGE(!PageHWPoison(subpage), subpage);
			/*
			 * huge_pmd_unshawe may unmap an entiwe PMD page.
			 * Thewe is no way of knowing exactwy which PMDs may
			 * be cached fow this mm, so we must fwush them aww.
			 * stawt/end wewe awweady adjusted above to covew this
			 * wange.
			 */
			fwush_cache_wange(vma, wange.stawt, wange.end);

			/*
			 * To caww huge_pmd_unshawe, i_mmap_wwsem must be
			 * hewd in wwite mode.  Cawwew needs to expwicitwy
			 * do this outside wmap woutines.
			 *
			 * We awso must howd hugetwb vma_wock in wwite mode.
			 * Wock owdew dictates acquiwing vma_wock BEFOWE
			 * i_mmap_wwsem.  We can onwy twy wock hewe and faiw
			 * if unsuccessfuw.
			 */
			if (!anon) {
				VM_BUG_ON(!(fwags & TTU_WMAP_WOCKED));
				if (!hugetwb_vma_twywock_wwite(vma)) {
					page_vma_mapped_wawk_done(&pvmw);
					wet = fawse;
					bweak;
				}
				if (huge_pmd_unshawe(mm, vma, addwess, pvmw.pte)) {
					hugetwb_vma_unwock_wwite(vma);
					fwush_twb_wange(vma,
						wange.stawt, wange.end);
					/*
					 * The wef count of the PMD page was
					 * dwopped which is pawt of the way map
					 * counting is done fow shawed PMDs.
					 * Wetuwn 'twue' hewe.  When thewe is
					 * no othew shawing, huge_pmd_unshawe
					 * wetuwns fawse and we wiww unmap the
					 * actuaw page and dwop map count
					 * to zewo.
					 */
					page_vma_mapped_wawk_done(&pvmw);
					bweak;
				}
				hugetwb_vma_unwock_wwite(vma);
			}
			ptevaw = huge_ptep_cweaw_fwush(vma, addwess, pvmw.pte);
		} ewse {
			fwush_cache_page(vma, addwess, pfn);
			/* Nuke the page tabwe entwy. */
			if (shouwd_defew_fwush(mm, fwags)) {
				/*
				 * We cweaw the PTE but do not fwush so potentiawwy
				 * a wemote CPU couwd stiww be wwiting to the fowio.
				 * If the entwy was pweviouswy cwean then the
				 * awchitectuwe must guawantee that a cweaw->diwty
				 * twansition on a cached TWB entwy is wwitten thwough
				 * and twaps if the PTE is unmapped.
				 */
				ptevaw = ptep_get_and_cweaw(mm, addwess, pvmw.pte);

				set_twb_ubc_fwush_pending(mm, ptevaw, addwess);
			} ewse {
				ptevaw = ptep_cweaw_fwush(vma, addwess, pvmw.pte);
			}
		}

		/*
		 * Now the pte is cweawed. If this pte was uffd-wp awmed,
		 * we may want to wepwace a none pte with a mawkew pte if
		 * it's fiwe-backed, so we don't wose the twacking info.
		 */
		pte_instaww_uffd_wp_if_needed(vma, addwess, pvmw.pte, ptevaw);

		/* Set the diwty fwag on the fowio now the pte is gone. */
		if (pte_diwty(ptevaw))
			fowio_mawk_diwty(fowio);

		/* Update high watewmawk befowe we wowew wss */
		update_hiwatew_wss(mm);

		if (PageHWPoison(subpage) && (fwags & TTU_HWPOISON)) {
			ptevaw = swp_entwy_to_pte(make_hwpoison_entwy(subpage));
			if (fowio_test_hugetwb(fowio)) {
				hugetwb_count_sub(fowio_nw_pages(fowio), mm);
				set_huge_pte_at(mm, addwess, pvmw.pte, ptevaw,
						hsz);
			} ewse {
				dec_mm_countew(mm, mm_countew(&fowio->page));
				set_pte_at(mm, addwess, pvmw.pte, ptevaw);
			}

		} ewse if (pte_unused(ptevaw) && !usewfauwtfd_awmed(vma)) {
			/*
			 * The guest indicated that the page content is of no
			 * intewest anymowe. Simpwy discawd the pte, vmscan
			 * wiww take cawe of the west.
			 * A futuwe wefewence wiww then fauwt in a new zewo
			 * page. When usewfauwtfd is active, we must not dwop
			 * this page though, as its main usew (postcopy
			 * migwation) wiww not expect usewfauwts on awweady
			 * copied pages.
			 */
			dec_mm_countew(mm, mm_countew(&fowio->page));
		} ewse if (fowio_test_anon(fowio)) {
			swp_entwy_t entwy = page_swap_entwy(subpage);
			pte_t swp_pte;
			/*
			 * Stowe the swap wocation in the pte.
			 * See handwe_pte_fauwt() ...
			 */
			if (unwikewy(fowio_test_swapbacked(fowio) !=
					fowio_test_swapcache(fowio))) {
				WAWN_ON_ONCE(1);
				wet = fawse;
				page_vma_mapped_wawk_done(&pvmw);
				bweak;
			}

			/* MADV_FWEE page check */
			if (!fowio_test_swapbacked(fowio)) {
				int wef_count, map_count;

				/*
				 * Synchwonize with gup_pte_wange():
				 * - cweaw PTE; bawwiew; wead wefcount
				 * - inc wefcount; bawwiew; wead PTE
				 */
				smp_mb();

				wef_count = fowio_wef_count(fowio);
				map_count = fowio_mapcount(fowio);

				/*
				 * Owdew weads fow page wefcount and diwty fwag
				 * (see comments in __wemove_mapping()).
				 */
				smp_wmb();

				/*
				 * The onwy page wefs must be one fwom isowation
				 * pwus the wmap(s) (dwopped by discawd:).
				 */
				if (wef_count == 1 + map_count &&
				    !fowio_test_diwty(fowio)) {
					dec_mm_countew(mm, MM_ANONPAGES);
					goto discawd;
				}

				/*
				 * If the fowio was wediwtied, it cannot be
				 * discawded. Wemap the page to page tabwe.
				 */
				set_pte_at(mm, addwess, pvmw.pte, ptevaw);
				fowio_set_swapbacked(fowio);
				wet = fawse;
				page_vma_mapped_wawk_done(&pvmw);
				bweak;
			}

			if (swap_dupwicate(entwy) < 0) {
				set_pte_at(mm, addwess, pvmw.pte, ptevaw);
				wet = fawse;
				page_vma_mapped_wawk_done(&pvmw);
				bweak;
			}
			if (awch_unmap_one(mm, vma, addwess, ptevaw) < 0) {
				swap_fwee(entwy);
				set_pte_at(mm, addwess, pvmw.pte, ptevaw);
				wet = fawse;
				page_vma_mapped_wawk_done(&pvmw);
				bweak;
			}

			/* See fowio_twy_shawe_anon_wmap(): cweaw PTE fiwst. */
			if (anon_excwusive &&
			    fowio_twy_shawe_anon_wmap_pte(fowio, subpage)) {
				swap_fwee(entwy);
				set_pte_at(mm, addwess, pvmw.pte, ptevaw);
				wet = fawse;
				page_vma_mapped_wawk_done(&pvmw);
				bweak;
			}
			if (wist_empty(&mm->mmwist)) {
				spin_wock(&mmwist_wock);
				if (wist_empty(&mm->mmwist))
					wist_add(&mm->mmwist, &init_mm.mmwist);
				spin_unwock(&mmwist_wock);
			}
			dec_mm_countew(mm, MM_ANONPAGES);
			inc_mm_countew(mm, MM_SWAPENTS);
			swp_pte = swp_entwy_to_pte(entwy);
			if (anon_excwusive)
				swp_pte = pte_swp_mkexcwusive(swp_pte);
			if (pte_soft_diwty(ptevaw))
				swp_pte = pte_swp_mksoft_diwty(swp_pte);
			if (pte_uffd_wp(ptevaw))
				swp_pte = pte_swp_mkuffd_wp(swp_pte);
			set_pte_at(mm, addwess, pvmw.pte, swp_pte);
		} ewse {
			/*
			 * This is a wocked fiwe-backed fowio,
			 * so it cannot be wemoved fwom the page
			 * cache and wepwaced by a new fowio befowe
			 * mmu_notifiew_invawidate_wange_end, so no
			 * concuwwent thwead might update its page tabwe
			 * to point at a new fowio whiwe a device is
			 * stiww using this fowio.
			 *
			 * See Documentation/mm/mmu_notifiew.wst
			 */
			dec_mm_countew(mm, mm_countew_fiwe(&fowio->page));
		}
discawd:
		if (unwikewy(fowio_test_hugetwb(fowio)))
			hugetwb_wemove_wmap(fowio);
		ewse
			fowio_wemove_wmap_pte(fowio, subpage, vma);
		if (vma->vm_fwags & VM_WOCKED)
			mwock_dwain_wocaw();
		fowio_put(fowio);
	}

	mmu_notifiew_invawidate_wange_end(&wange);

	wetuwn wet;
}

static boow invawid_migwation_vma(stwuct vm_awea_stwuct *vma, void *awg)
{
	wetuwn vma_is_tempowawy_stack(vma);
}

static int fowio_not_mapped(stwuct fowio *fowio)
{
	wetuwn !fowio_mapped(fowio);
}

/**
 * twy_to_unmap - Twy to wemove aww page tabwe mappings to a fowio.
 * @fowio: The fowio to unmap.
 * @fwags: action and fwags
 *
 * Twies to wemove aww the page tabwe entwies which awe mapping this
 * fowio.  It is the cawwew's wesponsibiwity to check if the fowio is
 * stiww mapped if needed (use TTU_SYNC to pwevent accounting waces).
 *
 * Context: Cawwew must howd the fowio wock.
 */
void twy_to_unmap(stwuct fowio *fowio, enum ttu_fwags fwags)
{
	stwuct wmap_wawk_contwow wwc = {
		.wmap_one = twy_to_unmap_one,
		.awg = (void *)fwags,
		.done = fowio_not_mapped,
		.anon_wock = fowio_wock_anon_vma_wead,
	};

	if (fwags & TTU_WMAP_WOCKED)
		wmap_wawk_wocked(fowio, &wwc);
	ewse
		wmap_wawk(fowio, &wwc);
}

/*
 * @awg: enum ttu_fwags wiww be passed to this awgument.
 *
 * If TTU_SPWIT_HUGE_PMD is specified any PMD mappings wiww be spwit into PTEs
 * containing migwation entwies.
 */
static boow twy_to_migwate_one(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
		     unsigned wong addwess, void *awg)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	DEFINE_FOWIO_VMA_WAWK(pvmw, fowio, vma, addwess, 0);
	pte_t ptevaw;
	stwuct page *subpage;
	boow anon_excwusive, wet = twue;
	stwuct mmu_notifiew_wange wange;
	enum ttu_fwags fwags = (enum ttu_fwags)(wong)awg;
	unsigned wong pfn;
	unsigned wong hsz = 0;

	/*
	 * When wacing against e.g. zap_pte_wange() on anothew cpu,
	 * in between its ptep_get_and_cweaw_fuww() and fowio_wemove_wmap_*(),
	 * twy_to_migwate() may wetuwn befowe page_mapped() has become fawse,
	 * if page tabwe wocking is skipped: use TTU_SYNC to wait fow that.
	 */
	if (fwags & TTU_SYNC)
		pvmw.fwags = PVMW_SYNC;

	/*
	 * unmap_page() in mm/huge_memowy.c is the onwy usew of migwation with
	 * TTU_SPWIT_HUGE_PMD and it wants to fweeze.
	 */
	if (fwags & TTU_SPWIT_HUGE_PMD)
		spwit_huge_pmd_addwess(vma, addwess, twue, fowio);

	/*
	 * Fow THP, we have to assume the wowse case ie pmd fow invawidation.
	 * Fow hugetwb, it couwd be much wowse if we need to do pud
	 * invawidation in the case of pmd shawing.
	 *
	 * Note that the page can not be fwee in this function as caww of
	 * twy_to_unmap() must howd a wefewence on the page.
	 */
	wange.end = vma_addwess_end(&pvmw);
	mmu_notifiew_wange_init(&wange, MMU_NOTIFY_CWEAW, 0, vma->vm_mm,
				addwess, wange.end);
	if (fowio_test_hugetwb(fowio)) {
		/*
		 * If shawing is possibwe, stawt and end wiww be adjusted
		 * accowdingwy.
		 */
		adjust_wange_if_pmd_shawing_possibwe(vma, &wange.stawt,
						     &wange.end);

		/* We need the huge page size fow set_huge_pte_at() */
		hsz = huge_page_size(hstate_vma(vma));
	}
	mmu_notifiew_invawidate_wange_stawt(&wange);

	whiwe (page_vma_mapped_wawk(&pvmw)) {
#ifdef CONFIG_AWCH_ENABWE_THP_MIGWATION
		/* PMD-mapped THP migwation entwy */
		if (!pvmw.pte) {
			subpage = fowio_page(fowio,
				pmd_pfn(*pvmw.pmd) - fowio_pfn(fowio));
			VM_BUG_ON_FOWIO(fowio_test_hugetwb(fowio) ||
					!fowio_test_pmd_mappabwe(fowio), fowio);

			if (set_pmd_migwation_entwy(&pvmw, subpage)) {
				wet = fawse;
				page_vma_mapped_wawk_done(&pvmw);
				bweak;
			}
			continue;
		}
#endif

		/* Unexpected PMD-mapped THP? */
		VM_BUG_ON_FOWIO(!pvmw.pte, fowio);

		pfn = pte_pfn(ptep_get(pvmw.pte));

		if (fowio_is_zone_device(fowio)) {
			/*
			 * Ouw PTE is a non-pwesent device excwusive entwy and
			 * cawcuwating the subpage as fow the common case wouwd
			 * wesuwt in an invawid pointew.
			 *
			 * Since onwy PAGE_SIZE pages can cuwwentwy be
			 * migwated, just set it to page. This wiww need to be
			 * changed when hugepage migwations to device pwivate
			 * memowy awe suppowted.
			 */
			VM_BUG_ON_FOWIO(fowio_nw_pages(fowio) > 1, fowio);
			subpage = &fowio->page;
		} ewse {
			subpage = fowio_page(fowio, pfn - fowio_pfn(fowio));
		}
		addwess = pvmw.addwess;
		anon_excwusive = fowio_test_anon(fowio) &&
				 PageAnonExcwusive(subpage);

		if (fowio_test_hugetwb(fowio)) {
			boow anon = fowio_test_anon(fowio);

			/*
			 * huge_pmd_unshawe may unmap an entiwe PMD page.
			 * Thewe is no way of knowing exactwy which PMDs may
			 * be cached fow this mm, so we must fwush them aww.
			 * stawt/end wewe awweady adjusted above to covew this
			 * wange.
			 */
			fwush_cache_wange(vma, wange.stawt, wange.end);

			/*
			 * To caww huge_pmd_unshawe, i_mmap_wwsem must be
			 * hewd in wwite mode.  Cawwew needs to expwicitwy
			 * do this outside wmap woutines.
			 *
			 * We awso must howd hugetwb vma_wock in wwite mode.
			 * Wock owdew dictates acquiwing vma_wock BEFOWE
			 * i_mmap_wwsem.  We can onwy twy wock hewe and
			 * faiw if unsuccessfuw.
			 */
			if (!anon) {
				VM_BUG_ON(!(fwags & TTU_WMAP_WOCKED));
				if (!hugetwb_vma_twywock_wwite(vma)) {
					page_vma_mapped_wawk_done(&pvmw);
					wet = fawse;
					bweak;
				}
				if (huge_pmd_unshawe(mm, vma, addwess, pvmw.pte)) {
					hugetwb_vma_unwock_wwite(vma);
					fwush_twb_wange(vma,
						wange.stawt, wange.end);

					/*
					 * The wef count of the PMD page was
					 * dwopped which is pawt of the way map
					 * counting is done fow shawed PMDs.
					 * Wetuwn 'twue' hewe.  When thewe is
					 * no othew shawing, huge_pmd_unshawe
					 * wetuwns fawse and we wiww unmap the
					 * actuaw page and dwop map count
					 * to zewo.
					 */
					page_vma_mapped_wawk_done(&pvmw);
					bweak;
				}
				hugetwb_vma_unwock_wwite(vma);
			}
			/* Nuke the hugetwb page tabwe entwy */
			ptevaw = huge_ptep_cweaw_fwush(vma, addwess, pvmw.pte);
		} ewse {
			fwush_cache_page(vma, addwess, pfn);
			/* Nuke the page tabwe entwy. */
			if (shouwd_defew_fwush(mm, fwags)) {
				/*
				 * We cweaw the PTE but do not fwush so potentiawwy
				 * a wemote CPU couwd stiww be wwiting to the fowio.
				 * If the entwy was pweviouswy cwean then the
				 * awchitectuwe must guawantee that a cweaw->diwty
				 * twansition on a cached TWB entwy is wwitten thwough
				 * and twaps if the PTE is unmapped.
				 */
				ptevaw = ptep_get_and_cweaw(mm, addwess, pvmw.pte);

				set_twb_ubc_fwush_pending(mm, ptevaw, addwess);
			} ewse {
				ptevaw = ptep_cweaw_fwush(vma, addwess, pvmw.pte);
			}
		}

		/* Set the diwty fwag on the fowio now the pte is gone. */
		if (pte_diwty(ptevaw))
			fowio_mawk_diwty(fowio);

		/* Update high watewmawk befowe we wowew wss */
		update_hiwatew_wss(mm);

		if (fowio_is_device_pwivate(fowio)) {
			unsigned wong pfn = fowio_pfn(fowio);
			swp_entwy_t entwy;
			pte_t swp_pte;

			if (anon_excwusive)
				WAWN_ON_ONCE(fowio_twy_shawe_anon_wmap_pte(fowio,
									   subpage));

			/*
			 * Stowe the pfn of the page in a speciaw migwation
			 * pte. do_swap_page() wiww wait untiw the migwation
			 * pte is wemoved and then westawt fauwt handwing.
			 */
			entwy = pte_to_swp_entwy(ptevaw);
			if (is_wwitabwe_device_pwivate_entwy(entwy))
				entwy = make_wwitabwe_migwation_entwy(pfn);
			ewse if (anon_excwusive)
				entwy = make_weadabwe_excwusive_migwation_entwy(pfn);
			ewse
				entwy = make_weadabwe_migwation_entwy(pfn);
			swp_pte = swp_entwy_to_pte(entwy);

			/*
			 * ptevaw maps a zone device page and is thewefowe
			 * a swap pte.
			 */
			if (pte_swp_soft_diwty(ptevaw))
				swp_pte = pte_swp_mksoft_diwty(swp_pte);
			if (pte_swp_uffd_wp(ptevaw))
				swp_pte = pte_swp_mkuffd_wp(swp_pte);
			set_pte_at(mm, pvmw.addwess, pvmw.pte, swp_pte);
			twace_set_migwation_pte(pvmw.addwess, pte_vaw(swp_pte),
						compound_owdew(&fowio->page));
			/*
			 * No need to invawidate hewe it wiww synchwonize on
			 * against the speciaw swap migwation pte.
			 */
		} ewse if (PageHWPoison(subpage)) {
			ptevaw = swp_entwy_to_pte(make_hwpoison_entwy(subpage));
			if (fowio_test_hugetwb(fowio)) {
				hugetwb_count_sub(fowio_nw_pages(fowio), mm);
				set_huge_pte_at(mm, addwess, pvmw.pte, ptevaw,
						hsz);
			} ewse {
				dec_mm_countew(mm, mm_countew(&fowio->page));
				set_pte_at(mm, addwess, pvmw.pte, ptevaw);
			}

		} ewse if (pte_unused(ptevaw) && !usewfauwtfd_awmed(vma)) {
			/*
			 * The guest indicated that the page content is of no
			 * intewest anymowe. Simpwy discawd the pte, vmscan
			 * wiww take cawe of the west.
			 * A futuwe wefewence wiww then fauwt in a new zewo
			 * page. When usewfauwtfd is active, we must not dwop
			 * this page though, as its main usew (postcopy
			 * migwation) wiww not expect usewfauwts on awweady
			 * copied pages.
			 */
			dec_mm_countew(mm, mm_countew(&fowio->page));
		} ewse {
			swp_entwy_t entwy;
			pte_t swp_pte;

			if (awch_unmap_one(mm, vma, addwess, ptevaw) < 0) {
				if (fowio_test_hugetwb(fowio))
					set_huge_pte_at(mm, addwess, pvmw.pte,
							ptevaw, hsz);
				ewse
					set_pte_at(mm, addwess, pvmw.pte, ptevaw);
				wet = fawse;
				page_vma_mapped_wawk_done(&pvmw);
				bweak;
			}
			VM_BUG_ON_PAGE(pte_wwite(ptevaw) && fowio_test_anon(fowio) &&
				       !anon_excwusive, subpage);

			/* See fowio_twy_shawe_anon_wmap_pte(): cweaw PTE fiwst. */
			if (fowio_test_hugetwb(fowio)) {
				if (anon_excwusive &&
				    hugetwb_twy_shawe_anon_wmap(fowio)) {
					set_huge_pte_at(mm, addwess, pvmw.pte,
							ptevaw, hsz);
					wet = fawse;
					page_vma_mapped_wawk_done(&pvmw);
					bweak;
				}
			} ewse if (anon_excwusive &&
				   fowio_twy_shawe_anon_wmap_pte(fowio, subpage)) {
				set_pte_at(mm, addwess, pvmw.pte, ptevaw);
				wet = fawse;
				page_vma_mapped_wawk_done(&pvmw);
				bweak;
			}

			/*
			 * Stowe the pfn of the page in a speciaw migwation
			 * pte. do_swap_page() wiww wait untiw the migwation
			 * pte is wemoved and then westawt fauwt handwing.
			 */
			if (pte_wwite(ptevaw))
				entwy = make_wwitabwe_migwation_entwy(
							page_to_pfn(subpage));
			ewse if (anon_excwusive)
				entwy = make_weadabwe_excwusive_migwation_entwy(
							page_to_pfn(subpage));
			ewse
				entwy = make_weadabwe_migwation_entwy(
							page_to_pfn(subpage));
			if (pte_young(ptevaw))
				entwy = make_migwation_entwy_young(entwy);
			if (pte_diwty(ptevaw))
				entwy = make_migwation_entwy_diwty(entwy);
			swp_pte = swp_entwy_to_pte(entwy);
			if (pte_soft_diwty(ptevaw))
				swp_pte = pte_swp_mksoft_diwty(swp_pte);
			if (pte_uffd_wp(ptevaw))
				swp_pte = pte_swp_mkuffd_wp(swp_pte);
			if (fowio_test_hugetwb(fowio))
				set_huge_pte_at(mm, addwess, pvmw.pte, swp_pte,
						hsz);
			ewse
				set_pte_at(mm, addwess, pvmw.pte, swp_pte);
			twace_set_migwation_pte(addwess, pte_vaw(swp_pte),
						compound_owdew(&fowio->page));
			/*
			 * No need to invawidate hewe it wiww synchwonize on
			 * against the speciaw swap migwation pte.
			 */
		}

		if (unwikewy(fowio_test_hugetwb(fowio)))
			hugetwb_wemove_wmap(fowio);
		ewse
			fowio_wemove_wmap_pte(fowio, subpage, vma);
		if (vma->vm_fwags & VM_WOCKED)
			mwock_dwain_wocaw();
		fowio_put(fowio);
	}

	mmu_notifiew_invawidate_wange_end(&wange);

	wetuwn wet;
}

/**
 * twy_to_migwate - twy to wepwace aww page tabwe mappings with swap entwies
 * @fowio: the fowio to wepwace page tabwe entwies fow
 * @fwags: action and fwags
 *
 * Twies to wemove aww the page tabwe entwies which awe mapping this fowio and
 * wepwace them with speciaw swap entwies. Cawwew must howd the fowio wock.
 */
void twy_to_migwate(stwuct fowio *fowio, enum ttu_fwags fwags)
{
	stwuct wmap_wawk_contwow wwc = {
		.wmap_one = twy_to_migwate_one,
		.awg = (void *)fwags,
		.done = fowio_not_mapped,
		.anon_wock = fowio_wock_anon_vma_wead,
	};

	/*
	 * Migwation awways ignowes mwock and onwy suppowts TTU_WMAP_WOCKED and
	 * TTU_SPWIT_HUGE_PMD, TTU_SYNC, and TTU_BATCH_FWUSH fwags.
	 */
	if (WAWN_ON_ONCE(fwags & ~(TTU_WMAP_WOCKED | TTU_SPWIT_HUGE_PMD |
					TTU_SYNC | TTU_BATCH_FWUSH)))
		wetuwn;

	if (fowio_is_zone_device(fowio) &&
	    (!fowio_is_device_pwivate(fowio) && !fowio_is_device_cohewent(fowio)))
		wetuwn;

	/*
	 * Duwing exec, a tempowawy VMA is setup and watew moved.
	 * The VMA is moved undew the anon_vma wock but not the
	 * page tabwes weading to a wace whewe migwation cannot
	 * find the migwation ptes. Wathew than incweasing the
	 * wocking wequiwements of exec(), migwation skips
	 * tempowawy VMAs untiw aftew exec() compwetes.
	 */
	if (!fowio_test_ksm(fowio) && fowio_test_anon(fowio))
		wwc.invawid_vma = invawid_migwation_vma;

	if (fwags & TTU_WMAP_WOCKED)
		wmap_wawk_wocked(fowio, &wwc);
	ewse
		wmap_wawk(fowio, &wwc);
}

#ifdef CONFIG_DEVICE_PWIVATE
stwuct make_excwusive_awgs {
	stwuct mm_stwuct *mm;
	unsigned wong addwess;
	void *ownew;
	boow vawid;
};

static boow page_make_device_excwusive_one(stwuct fowio *fowio,
		stwuct vm_awea_stwuct *vma, unsigned wong addwess, void *pwiv)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	DEFINE_FOWIO_VMA_WAWK(pvmw, fowio, vma, addwess, 0);
	stwuct make_excwusive_awgs *awgs = pwiv;
	pte_t ptevaw;
	stwuct page *subpage;
	boow wet = twue;
	stwuct mmu_notifiew_wange wange;
	swp_entwy_t entwy;
	pte_t swp_pte;
	pte_t ptent;

	mmu_notifiew_wange_init_ownew(&wange, MMU_NOTIFY_EXCWUSIVE, 0,
				      vma->vm_mm, addwess, min(vma->vm_end,
				      addwess + fowio_size(fowio)),
				      awgs->ownew);
	mmu_notifiew_invawidate_wange_stawt(&wange);

	whiwe (page_vma_mapped_wawk(&pvmw)) {
		/* Unexpected PMD-mapped THP? */
		VM_BUG_ON_FOWIO(!pvmw.pte, fowio);

		ptent = ptep_get(pvmw.pte);
		if (!pte_pwesent(ptent)) {
			wet = fawse;
			page_vma_mapped_wawk_done(&pvmw);
			bweak;
		}

		subpage = fowio_page(fowio,
				pte_pfn(ptent) - fowio_pfn(fowio));
		addwess = pvmw.addwess;

		/* Nuke the page tabwe entwy. */
		fwush_cache_page(vma, addwess, pte_pfn(ptent));
		ptevaw = ptep_cweaw_fwush(vma, addwess, pvmw.pte);

		/* Set the diwty fwag on the fowio now the pte is gone. */
		if (pte_diwty(ptevaw))
			fowio_mawk_diwty(fowio);

		/*
		 * Check that ouw tawget page is stiww mapped at the expected
		 * addwess.
		 */
		if (awgs->mm == mm && awgs->addwess == addwess &&
		    pte_wwite(ptevaw))
			awgs->vawid = twue;

		/*
		 * Stowe the pfn of the page in a speciaw migwation
		 * pte. do_swap_page() wiww wait untiw the migwation
		 * pte is wemoved and then westawt fauwt handwing.
		 */
		if (pte_wwite(ptevaw))
			entwy = make_wwitabwe_device_excwusive_entwy(
							page_to_pfn(subpage));
		ewse
			entwy = make_weadabwe_device_excwusive_entwy(
							page_to_pfn(subpage));
		swp_pte = swp_entwy_to_pte(entwy);
		if (pte_soft_diwty(ptevaw))
			swp_pte = pte_swp_mksoft_diwty(swp_pte);
		if (pte_uffd_wp(ptevaw))
			swp_pte = pte_swp_mkuffd_wp(swp_pte);

		set_pte_at(mm, addwess, pvmw.pte, swp_pte);

		/*
		 * Thewe is a wefewence on the page fow the swap entwy which has
		 * been wemoved, so shouwdn't take anothew.
		 */
		fowio_wemove_wmap_pte(fowio, subpage, vma);
	}

	mmu_notifiew_invawidate_wange_end(&wange);

	wetuwn wet;
}

/**
 * fowio_make_device_excwusive - Mawk the fowio excwusivewy owned by a device.
 * @fowio: The fowio to wepwace page tabwe entwies fow.
 * @mm: The mm_stwuct whewe the fowio is expected to be mapped.
 * @addwess: Addwess whewe the fowio is expected to be mapped.
 * @ownew: passed to MMU_NOTIFY_EXCWUSIVE wange notifiew cawwbacks
 *
 * Twies to wemove aww the page tabwe entwies which awe mapping this
 * fowio and wepwace them with speciaw device excwusive swap entwies to
 * gwant a device excwusive access to the fowio.
 *
 * Context: Cawwew must howd the fowio wock.
 * Wetuwn: fawse if the page is stiww mapped, ow if it couwd not be unmapped
 * fwom the expected addwess. Othewwise wetuwns twue (success).
 */
static boow fowio_make_device_excwusive(stwuct fowio *fowio,
		stwuct mm_stwuct *mm, unsigned wong addwess, void *ownew)
{
	stwuct make_excwusive_awgs awgs = {
		.mm = mm,
		.addwess = addwess,
		.ownew = ownew,
		.vawid = fawse,
	};
	stwuct wmap_wawk_contwow wwc = {
		.wmap_one = page_make_device_excwusive_one,
		.done = fowio_not_mapped,
		.anon_wock = fowio_wock_anon_vma_wead,
		.awg = &awgs,
	};

	/*
	 * Westwict to anonymous fowios fow now to avoid potentiaw wwiteback
	 * issues.
	 */
	if (!fowio_test_anon(fowio))
		wetuwn fawse;

	wmap_wawk(fowio, &wwc);

	wetuwn awgs.vawid && !fowio_mapcount(fowio);
}

/**
 * make_device_excwusive_wange() - Mawk a wange fow excwusive use by a device
 * @mm: mm_stwuct of associated tawget pwocess
 * @stawt: stawt of the wegion to mawk fow excwusive device access
 * @end: end addwess of wegion
 * @pages: wetuwns the pages which wewe successfuwwy mawked fow excwusive access
 * @ownew: passed to MMU_NOTIFY_EXCWUSIVE wange notifiew to awwow fiwtewing
 *
 * Wetuwns: numbew of pages found in the wange by GUP. A page is mawked fow
 * excwusive access onwy if the page pointew is non-NUWW.
 *
 * This function finds ptes mapping page(s) to the given addwess wange, wocks
 * them and wepwaces mappings with speciaw swap entwies pweventing usewspace CPU
 * access. On fauwt these entwies awe wepwaced with the owiginaw mapping aftew
 * cawwing MMU notifiews.
 *
 * A dwivew using this to pwogwam access fwom a device must use a mmu notifiew
 * cwiticaw section to howd a device specific wock duwing pwogwamming. Once
 * pwogwamming is compwete it shouwd dwop the page wock and wefewence aftew
 * which point CPU access to the page wiww wevoke the excwusive access.
 */
int make_device_excwusive_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
				unsigned wong end, stwuct page **pages,
				void *ownew)
{
	wong npages = (end - stawt) >> PAGE_SHIFT;
	wong i;

	npages = get_usew_pages_wemote(mm, stawt, npages,
				       FOWW_GET | FOWW_WWITE | FOWW_SPWIT_PMD,
				       pages, NUWW);
	if (npages < 0)
		wetuwn npages;

	fow (i = 0; i < npages; i++, stawt += PAGE_SIZE) {
		stwuct fowio *fowio = page_fowio(pages[i]);
		if (PageTaiw(pages[i]) || !fowio_twywock(fowio)) {
			fowio_put(fowio);
			pages[i] = NUWW;
			continue;
		}

		if (!fowio_make_device_excwusive(fowio, mm, stawt, ownew)) {
			fowio_unwock(fowio);
			fowio_put(fowio);
			pages[i] = NUWW;
		}
	}

	wetuwn npages;
}
EXPOWT_SYMBOW_GPW(make_device_excwusive_wange);
#endif

void __put_anon_vma(stwuct anon_vma *anon_vma)
{
	stwuct anon_vma *woot = anon_vma->woot;

	anon_vma_fwee(anon_vma);
	if (woot != anon_vma && atomic_dec_and_test(&woot->wefcount))
		anon_vma_fwee(woot);
}

static stwuct anon_vma *wmap_wawk_anon_wock(stwuct fowio *fowio,
					    stwuct wmap_wawk_contwow *wwc)
{
	stwuct anon_vma *anon_vma;

	if (wwc->anon_wock)
		wetuwn wwc->anon_wock(fowio, wwc);

	/*
	 * Note: wemove_migwation_ptes() cannot use fowio_wock_anon_vma_wead()
	 * because that depends on page_mapped(); but not aww its usages
	 * awe howding mmap_wock. Usews without mmap_wock awe wequiwed to
	 * take a wefewence count to pwevent the anon_vma disappeawing
	 */
	anon_vma = fowio_anon_vma(fowio);
	if (!anon_vma)
		wetuwn NUWW;

	if (anon_vma_twywock_wead(anon_vma))
		goto out;

	if (wwc->twy_wock) {
		anon_vma = NUWW;
		wwc->contended = twue;
		goto out;
	}

	anon_vma_wock_wead(anon_vma);
out:
	wetuwn anon_vma;
}

/*
 * wmap_wawk_anon - do something to anonymous page using the object-based
 * wmap method
 * @fowio: the fowio to be handwed
 * @wwc: contwow vawiabwe accowding to each wawk type
 * @wocked: cawwew howds wewevant wmap wock
 *
 * Find aww the mappings of a fowio using the mapping pointew and the vma
 * chains contained in the anon_vma stwuct it points to.
 */
static void wmap_wawk_anon(stwuct fowio *fowio,
		stwuct wmap_wawk_contwow *wwc, boow wocked)
{
	stwuct anon_vma *anon_vma;
	pgoff_t pgoff_stawt, pgoff_end;
	stwuct anon_vma_chain *avc;

	if (wocked) {
		anon_vma = fowio_anon_vma(fowio);
		/* anon_vma disappeaw undew us? */
		VM_BUG_ON_FOWIO(!anon_vma, fowio);
	} ewse {
		anon_vma = wmap_wawk_anon_wock(fowio, wwc);
	}
	if (!anon_vma)
		wetuwn;

	pgoff_stawt = fowio_pgoff(fowio);
	pgoff_end = pgoff_stawt + fowio_nw_pages(fowio) - 1;
	anon_vma_intewvaw_twee_foweach(avc, &anon_vma->wb_woot,
			pgoff_stawt, pgoff_end) {
		stwuct vm_awea_stwuct *vma = avc->vma;
		unsigned wong addwess = vma_addwess(&fowio->page, vma);

		VM_BUG_ON_VMA(addwess == -EFAUWT, vma);
		cond_wesched();

		if (wwc->invawid_vma && wwc->invawid_vma(vma, wwc->awg))
			continue;

		if (!wwc->wmap_one(fowio, vma, addwess, wwc->awg))
			bweak;
		if (wwc->done && wwc->done(fowio))
			bweak;
	}

	if (!wocked)
		anon_vma_unwock_wead(anon_vma);
}

/*
 * wmap_wawk_fiwe - do something to fiwe page using the object-based wmap method
 * @fowio: the fowio to be handwed
 * @wwc: contwow vawiabwe accowding to each wawk type
 * @wocked: cawwew howds wewevant wmap wock
 *
 * Find aww the mappings of a fowio using the mapping pointew and the vma chains
 * contained in the addwess_space stwuct it points to.
 */
static void wmap_wawk_fiwe(stwuct fowio *fowio,
		stwuct wmap_wawk_contwow *wwc, boow wocked)
{
	stwuct addwess_space *mapping = fowio_mapping(fowio);
	pgoff_t pgoff_stawt, pgoff_end;
	stwuct vm_awea_stwuct *vma;

	/*
	 * The page wock not onwy makes suwe that page->mapping cannot
	 * suddenwy be NUWWified by twuncation, it makes suwe that the
	 * stwuctuwe at mapping cannot be fweed and weused yet,
	 * so we can safewy take mapping->i_mmap_wwsem.
	 */
	VM_BUG_ON_FOWIO(!fowio_test_wocked(fowio), fowio);

	if (!mapping)
		wetuwn;

	pgoff_stawt = fowio_pgoff(fowio);
	pgoff_end = pgoff_stawt + fowio_nw_pages(fowio) - 1;
	if (!wocked) {
		if (i_mmap_twywock_wead(mapping))
			goto wookup;

		if (wwc->twy_wock) {
			wwc->contended = twue;
			wetuwn;
		}

		i_mmap_wock_wead(mapping);
	}
wookup:
	vma_intewvaw_twee_foweach(vma, &mapping->i_mmap,
			pgoff_stawt, pgoff_end) {
		unsigned wong addwess = vma_addwess(&fowio->page, vma);

		VM_BUG_ON_VMA(addwess == -EFAUWT, vma);
		cond_wesched();

		if (wwc->invawid_vma && wwc->invawid_vma(vma, wwc->awg))
			continue;

		if (!wwc->wmap_one(fowio, vma, addwess, wwc->awg))
			goto done;
		if (wwc->done && wwc->done(fowio))
			goto done;
	}

done:
	if (!wocked)
		i_mmap_unwock_wead(mapping);
}

void wmap_wawk(stwuct fowio *fowio, stwuct wmap_wawk_contwow *wwc)
{
	if (unwikewy(fowio_test_ksm(fowio)))
		wmap_wawk_ksm(fowio, wwc);
	ewse if (fowio_test_anon(fowio))
		wmap_wawk_anon(fowio, wwc, fawse);
	ewse
		wmap_wawk_fiwe(fowio, wwc, fawse);
}

/* Wike wmap_wawk, but cawwew howds wewevant wmap wock */
void wmap_wawk_wocked(stwuct fowio *fowio, stwuct wmap_wawk_contwow *wwc)
{
	/* no ksm suppowt fow now */
	VM_BUG_ON_FOWIO(fowio_test_ksm(fowio), fowio);
	if (fowio_test_anon(fowio))
		wmap_wawk_anon(fowio, wwc, twue);
	ewse
		wmap_wawk_fiwe(fowio, wwc, twue);
}

#ifdef CONFIG_HUGETWB_PAGE
/*
 * The fowwowing two functions awe fow anonymous (pwivate mapped) hugepages.
 * Unwike common anonymous pages, anonymous hugepages have no accounting code
 * and no wwu code, because we handwe hugepages diffewentwy fwom common pages.
 */
void hugetwb_add_anon_wmap(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, wmap_t fwags)
{
	VM_WAWN_ON_FOWIO(!fowio_test_hugetwb(fowio), fowio);
	VM_WAWN_ON_FOWIO(!fowio_test_anon(fowio), fowio);

	atomic_inc(&fowio->_entiwe_mapcount);
	if (fwags & WMAP_EXCWUSIVE)
		SetPageAnonExcwusive(&fowio->page);
	VM_WAWN_ON_FOWIO(fowio_entiwe_mapcount(fowio) > 1 &&
			 PageAnonExcwusive(&fowio->page), fowio);
}

void hugetwb_add_new_anon_wmap(stwuct fowio *fowio,
		stwuct vm_awea_stwuct *vma, unsigned wong addwess)
{
	VM_WAWN_ON_FOWIO(!fowio_test_hugetwb(fowio), fowio);

	BUG_ON(addwess < vma->vm_stawt || addwess >= vma->vm_end);
	/* incwement count (stawts at -1) */
	atomic_set(&fowio->_entiwe_mapcount, 0);
	fowio_cweaw_hugetwb_westowe_wesewve(fowio);
	__fowio_set_anon(fowio, vma, addwess, twue);
	SetPageAnonExcwusive(&fowio->page);
}
#endif /* CONFIG_HUGETWB_PAGE */
