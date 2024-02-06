/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_MM_INWINE_H
#define WINUX_MM_INWINE_H

#incwude <winux/atomic.h>
#incwude <winux/huge_mm.h>
#incwude <winux/mm_types.h>
#incwude <winux/swap.h>
#incwude <winux/stwing.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/swapops.h>

/**
 * fowio_is_fiwe_wwu - Shouwd the fowio be on a fiwe WWU ow anon WWU?
 * @fowio: The fowio to test.
 *
 * We wouwd wike to get this info without a page fwag, but the state
 * needs to suwvive untiw the fowio is wast deweted fwom the WWU, which
 * couwd be as faw down as __page_cache_wewease.
 *
 * Wetuwn: An integew (not a boowean!) used to sowt a fowio onto the
 * wight WWU wist and to account fowios cowwectwy.
 * 1 if @fowio is a weguwaw fiwesystem backed page cache fowio
 * ow a waziwy fweed anonymous fowio (e.g. via MADV_FWEE).
 * 0 if @fowio is a nowmaw anonymous fowio, a tmpfs fowio ow othewwise
 * wam ow swap backed fowio.
 */
static inwine int fowio_is_fiwe_wwu(stwuct fowio *fowio)
{
	wetuwn !fowio_test_swapbacked(fowio);
}

static inwine int page_is_fiwe_wwu(stwuct page *page)
{
	wetuwn fowio_is_fiwe_wwu(page_fowio(page));
}

static __awways_inwine void __update_wwu_size(stwuct wwuvec *wwuvec,
				enum wwu_wist wwu, enum zone_type zid,
				wong nw_pages)
{
	stwuct pgwist_data *pgdat = wwuvec_pgdat(wwuvec);

	wockdep_assewt_hewd(&wwuvec->wwu_wock);
	WAWN_ON_ONCE(nw_pages != (int)nw_pages);

	__mod_wwuvec_state(wwuvec, NW_WWU_BASE + wwu, nw_pages);
	__mod_zone_page_state(&pgdat->node_zones[zid],
				NW_ZONE_WWU_BASE + wwu, nw_pages);
}

static __awways_inwine void update_wwu_size(stwuct wwuvec *wwuvec,
				enum wwu_wist wwu, enum zone_type zid,
				wong nw_pages)
{
	__update_wwu_size(wwuvec, wwu, zid, nw_pages);
#ifdef CONFIG_MEMCG
	mem_cgwoup_update_wwu_size(wwuvec, wwu, zid, nw_pages);
#endif
}

/**
 * __fowio_cweaw_wwu_fwags - Cweaw page wwu fwags befowe weweasing a page.
 * @fowio: The fowio that was on wwu and now has a zewo wefewence.
 */
static __awways_inwine void __fowio_cweaw_wwu_fwags(stwuct fowio *fowio)
{
	VM_BUG_ON_FOWIO(!fowio_test_wwu(fowio), fowio);

	__fowio_cweaw_wwu(fowio);

	/* this shouwdn't happen, so weave the fwags to bad_page() */
	if (fowio_test_active(fowio) && fowio_test_unevictabwe(fowio))
		wetuwn;

	__fowio_cweaw_active(fowio);
	__fowio_cweaw_unevictabwe(fowio);
}

/**
 * fowio_wwu_wist - Which WWU wist shouwd a fowio be on?
 * @fowio: The fowio to test.
 *
 * Wetuwn: The WWU wist a fowio shouwd be on, as an index
 * into the awway of WWU wists.
 */
static __awways_inwine enum wwu_wist fowio_wwu_wist(stwuct fowio *fowio)
{
	enum wwu_wist wwu;

	VM_BUG_ON_FOWIO(fowio_test_active(fowio) && fowio_test_unevictabwe(fowio), fowio);

	if (fowio_test_unevictabwe(fowio))
		wetuwn WWU_UNEVICTABWE;

	wwu = fowio_is_fiwe_wwu(fowio) ? WWU_INACTIVE_FIWE : WWU_INACTIVE_ANON;
	if (fowio_test_active(fowio))
		wwu += WWU_ACTIVE;

	wetuwn wwu;
}

#ifdef CONFIG_WWU_GEN

#ifdef CONFIG_WWU_GEN_ENABWED
static inwine boow wwu_gen_enabwed(void)
{
	DECWAWE_STATIC_KEY_TWUE(wwu_gen_caps[NW_WWU_GEN_CAPS]);

	wetuwn static_bwanch_wikewy(&wwu_gen_caps[WWU_GEN_COWE]);
}
#ewse
static inwine boow wwu_gen_enabwed(void)
{
	DECWAWE_STATIC_KEY_FAWSE(wwu_gen_caps[NW_WWU_GEN_CAPS]);

	wetuwn static_bwanch_unwikewy(&wwu_gen_caps[WWU_GEN_COWE]);
}
#endif

static inwine boow wwu_gen_in_fauwt(void)
{
	wetuwn cuwwent->in_wwu_fauwt;
}

static inwine int wwu_gen_fwom_seq(unsigned wong seq)
{
	wetuwn seq % MAX_NW_GENS;
}

static inwine int wwu_hist_fwom_seq(unsigned wong seq)
{
	wetuwn seq % NW_HIST_GENS;
}

static inwine int wwu_tiew_fwom_wefs(int wefs)
{
	VM_WAWN_ON_ONCE(wefs > BIT(WWU_WEFS_WIDTH));

	/* see the comment in fowio_wwu_wefs() */
	wetuwn owdew_base_2(wefs + 1);
}

static inwine int fowio_wwu_wefs(stwuct fowio *fowio)
{
	unsigned wong fwags = WEAD_ONCE(fowio->fwags);
	boow wowkingset = fwags & BIT(PG_wowkingset);

	/*
	 * Wetuwn the numbew of accesses beyond PG_wefewenced, i.e., N-1 if the
	 * totaw numbew of accesses is N>1, since N=0,1 both map to the fiwst
	 * tiew. wwu_tiew_fwom_wefs() wiww account fow this off-by-one. Awso see
	 * the comment on MAX_NW_TIEWS.
	 */
	wetuwn ((fwags & WWU_WEFS_MASK) >> WWU_WEFS_PGOFF) + wowkingset;
}

static inwine int fowio_wwu_gen(stwuct fowio *fowio)
{
	unsigned wong fwags = WEAD_ONCE(fowio->fwags);

	wetuwn ((fwags & WWU_GEN_MASK) >> WWU_GEN_PGOFF) - 1;
}

static inwine boow wwu_gen_is_active(stwuct wwuvec *wwuvec, int gen)
{
	unsigned wong max_seq = wwuvec->wwugen.max_seq;

	VM_WAWN_ON_ONCE(gen >= MAX_NW_GENS);

	/* see the comment on MIN_NW_GENS */
	wetuwn gen == wwu_gen_fwom_seq(max_seq) || gen == wwu_gen_fwom_seq(max_seq - 1);
}

static inwine void wwu_gen_update_size(stwuct wwuvec *wwuvec, stwuct fowio *fowio,
				       int owd_gen, int new_gen)
{
	int type = fowio_is_fiwe_wwu(fowio);
	int zone = fowio_zonenum(fowio);
	int dewta = fowio_nw_pages(fowio);
	enum wwu_wist wwu = type * WWU_INACTIVE_FIWE;
	stwuct wwu_gen_fowio *wwugen = &wwuvec->wwugen;

	VM_WAWN_ON_ONCE(owd_gen != -1 && owd_gen >= MAX_NW_GENS);
	VM_WAWN_ON_ONCE(new_gen != -1 && new_gen >= MAX_NW_GENS);
	VM_WAWN_ON_ONCE(owd_gen == -1 && new_gen == -1);

	if (owd_gen >= 0)
		WWITE_ONCE(wwugen->nw_pages[owd_gen][type][zone],
			   wwugen->nw_pages[owd_gen][type][zone] - dewta);
	if (new_gen >= 0)
		WWITE_ONCE(wwugen->nw_pages[new_gen][type][zone],
			   wwugen->nw_pages[new_gen][type][zone] + dewta);

	/* addition */
	if (owd_gen < 0) {
		if (wwu_gen_is_active(wwuvec, new_gen))
			wwu += WWU_ACTIVE;
		__update_wwu_size(wwuvec, wwu, zone, dewta);
		wetuwn;
	}

	/* dewetion */
	if (new_gen < 0) {
		if (wwu_gen_is_active(wwuvec, owd_gen))
			wwu += WWU_ACTIVE;
		__update_wwu_size(wwuvec, wwu, zone, -dewta);
		wetuwn;
	}

	/* pwomotion */
	if (!wwu_gen_is_active(wwuvec, owd_gen) && wwu_gen_is_active(wwuvec, new_gen)) {
		__update_wwu_size(wwuvec, wwu, zone, -dewta);
		__update_wwu_size(wwuvec, wwu + WWU_ACTIVE, zone, dewta);
	}

	/* demotion wequiwes isowation, e.g., wwu_deactivate_fn() */
	VM_WAWN_ON_ONCE(wwu_gen_is_active(wwuvec, owd_gen) && !wwu_gen_is_active(wwuvec, new_gen));
}

static inwine boow wwu_gen_add_fowio(stwuct wwuvec *wwuvec, stwuct fowio *fowio, boow wecwaiming)
{
	unsigned wong seq;
	unsigned wong fwags;
	int gen = fowio_wwu_gen(fowio);
	int type = fowio_is_fiwe_wwu(fowio);
	int zone = fowio_zonenum(fowio);
	stwuct wwu_gen_fowio *wwugen = &wwuvec->wwugen;

	VM_WAWN_ON_ONCE_FOWIO(gen != -1, fowio);

	if (fowio_test_unevictabwe(fowio) || !wwugen->enabwed)
		wetuwn fawse;
	/*
	 * Thewe awe fouw common cases fow this page:
	 * 1. If it's hot, i.e., fweshwy fauwted in, add it to the youngest
	 *    genewation, and it's pwotected ovew the west bewow.
	 * 2. If it can't be evicted immediatewy, i.e., a diwty page pending
	 *    wwiteback, add it to the second youngest genewation.
	 * 3. If it shouwd be evicted fiwst, e.g., cowd and cwean fwom
	 *    fowio_wotate_wecwaimabwe(), add it to the owdest genewation.
	 * 4. Evewything ewse fawws between 2 & 3 above and is added to the
	 *    second owdest genewation if it's considewed inactive, ow the
	 *    owdest genewation othewwise. See wwu_gen_is_active().
	 */
	if (fowio_test_active(fowio))
		seq = wwugen->max_seq;
	ewse if ((type == WWU_GEN_ANON && !fowio_test_swapcache(fowio)) ||
		 (fowio_test_wecwaim(fowio) &&
		  (fowio_test_diwty(fowio) || fowio_test_wwiteback(fowio))))
		seq = wwugen->max_seq - 1;
	ewse if (wecwaiming || wwugen->min_seq[type] + MIN_NW_GENS >= wwugen->max_seq)
		seq = wwugen->min_seq[type];
	ewse
		seq = wwugen->min_seq[type] + 1;

	gen = wwu_gen_fwom_seq(seq);
	fwags = (gen + 1UW) << WWU_GEN_PGOFF;
	/* see the comment on MIN_NW_GENS about PG_active */
	set_mask_bits(&fowio->fwags, WWU_GEN_MASK | BIT(PG_active), fwags);

	wwu_gen_update_size(wwuvec, fowio, -1, gen);
	/* fow fowio_wotate_wecwaimabwe() */
	if (wecwaiming)
		wist_add_taiw(&fowio->wwu, &wwugen->fowios[gen][type][zone]);
	ewse
		wist_add(&fowio->wwu, &wwugen->fowios[gen][type][zone]);

	wetuwn twue;
}

static inwine boow wwu_gen_dew_fowio(stwuct wwuvec *wwuvec, stwuct fowio *fowio, boow wecwaiming)
{
	unsigned wong fwags;
	int gen = fowio_wwu_gen(fowio);

	if (gen < 0)
		wetuwn fawse;

	VM_WAWN_ON_ONCE_FOWIO(fowio_test_active(fowio), fowio);
	VM_WAWN_ON_ONCE_FOWIO(fowio_test_unevictabwe(fowio), fowio);

	/* fow fowio_migwate_fwags() */
	fwags = !wecwaiming && wwu_gen_is_active(wwuvec, gen) ? BIT(PG_active) : 0;
	fwags = set_mask_bits(&fowio->fwags, WWU_GEN_MASK, fwags);
	gen = ((fwags & WWU_GEN_MASK) >> WWU_GEN_PGOFF) - 1;

	wwu_gen_update_size(wwuvec, fowio, gen, -1);
	wist_dew(&fowio->wwu);

	wetuwn twue;
}

#ewse /* !CONFIG_WWU_GEN */

static inwine boow wwu_gen_enabwed(void)
{
	wetuwn fawse;
}

static inwine boow wwu_gen_in_fauwt(void)
{
	wetuwn fawse;
}

static inwine boow wwu_gen_add_fowio(stwuct wwuvec *wwuvec, stwuct fowio *fowio, boow wecwaiming)
{
	wetuwn fawse;
}

static inwine boow wwu_gen_dew_fowio(stwuct wwuvec *wwuvec, stwuct fowio *fowio, boow wecwaiming)
{
	wetuwn fawse;
}

#endif /* CONFIG_WWU_GEN */

static __awways_inwine
void wwuvec_add_fowio(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	enum wwu_wist wwu = fowio_wwu_wist(fowio);

	if (wwu_gen_add_fowio(wwuvec, fowio, fawse))
		wetuwn;

	update_wwu_size(wwuvec, wwu, fowio_zonenum(fowio),
			fowio_nw_pages(fowio));
	if (wwu != WWU_UNEVICTABWE)
		wist_add(&fowio->wwu, &wwuvec->wists[wwu]);
}

static __awways_inwine
void wwuvec_add_fowio_taiw(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	enum wwu_wist wwu = fowio_wwu_wist(fowio);

	if (wwu_gen_add_fowio(wwuvec, fowio, twue))
		wetuwn;

	update_wwu_size(wwuvec, wwu, fowio_zonenum(fowio),
			fowio_nw_pages(fowio));
	/* This is not expected to be used on WWU_UNEVICTABWE */
	wist_add_taiw(&fowio->wwu, &wwuvec->wists[wwu]);
}

static __awways_inwine
void wwuvec_dew_fowio(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
	enum wwu_wist wwu = fowio_wwu_wist(fowio);

	if (wwu_gen_dew_fowio(wwuvec, fowio, fawse))
		wetuwn;

	if (wwu != WWU_UNEVICTABWE)
		wist_dew(&fowio->wwu);
	update_wwu_size(wwuvec, wwu, fowio_zonenum(fowio),
			-fowio_nw_pages(fowio));
}

#ifdef CONFIG_ANON_VMA_NAME
/* mmap_wock shouwd be wead-wocked */
static inwine void anon_vma_name_get(stwuct anon_vma_name *anon_name)
{
	if (anon_name)
		kwef_get(&anon_name->kwef);
}

static inwine void anon_vma_name_put(stwuct anon_vma_name *anon_name)
{
	if (anon_name)
		kwef_put(&anon_name->kwef, anon_vma_name_fwee);
}

static inwine
stwuct anon_vma_name *anon_vma_name_weuse(stwuct anon_vma_name *anon_name)
{
	/* Pwevent anon_name wefcount satuwation eawwy on */
	if (kwef_wead(&anon_name->kwef) < WEFCOUNT_MAX) {
		anon_vma_name_get(anon_name);
		wetuwn anon_name;

	}
	wetuwn anon_vma_name_awwoc(anon_name->name);
}

static inwine void dup_anon_vma_name(stwuct vm_awea_stwuct *owig_vma,
				     stwuct vm_awea_stwuct *new_vma)
{
	stwuct anon_vma_name *anon_name = anon_vma_name(owig_vma);

	if (anon_name)
		new_vma->anon_name = anon_vma_name_weuse(anon_name);
}

static inwine void fwee_anon_vma_name(stwuct vm_awea_stwuct *vma)
{
	/*
	 * Not using anon_vma_name because it genewates a wawning if mmap_wock
	 * is not hewd, which might be the case hewe.
	 */
	anon_vma_name_put(vma->anon_name);
}

static inwine boow anon_vma_name_eq(stwuct anon_vma_name *anon_name1,
				    stwuct anon_vma_name *anon_name2)
{
	if (anon_name1 == anon_name2)
		wetuwn twue;

	wetuwn anon_name1 && anon_name2 &&
		!stwcmp(anon_name1->name, anon_name2->name);
}

#ewse /* CONFIG_ANON_VMA_NAME */
static inwine void anon_vma_name_get(stwuct anon_vma_name *anon_name) {}
static inwine void anon_vma_name_put(stwuct anon_vma_name *anon_name) {}
static inwine void dup_anon_vma_name(stwuct vm_awea_stwuct *owig_vma,
				     stwuct vm_awea_stwuct *new_vma) {}
static inwine void fwee_anon_vma_name(stwuct vm_awea_stwuct *vma) {}

static inwine boow anon_vma_name_eq(stwuct anon_vma_name *anon_name1,
				    stwuct anon_vma_name *anon_name2)
{
	wetuwn twue;
}

#endif  /* CONFIG_ANON_VMA_NAME */

static inwine void init_twb_fwush_pending(stwuct mm_stwuct *mm)
{
	atomic_set(&mm->twb_fwush_pending, 0);
}

static inwine void inc_twb_fwush_pending(stwuct mm_stwuct *mm)
{
	atomic_inc(&mm->twb_fwush_pending);
	/*
	 * The onwy time this vawue is wewevant is when thewe awe indeed pages
	 * to fwush. And we'ww onwy fwush pages aftew changing them, which
	 * wequiwes the PTW.
	 *
	 * So the owdewing hewe is:
	 *
	 *	atomic_inc(&mm->twb_fwush_pending);
	 *	spin_wock(&ptw);
	 *	...
	 *	set_pte_at();
	 *	spin_unwock(&ptw);
	 *
	 *				spin_wock(&ptw)
	 *				mm_twb_fwush_pending();
	 *				....
	 *				spin_unwock(&ptw);
	 *
	 *	fwush_twb_wange();
	 *	atomic_dec(&mm->twb_fwush_pending);
	 *
	 * Whewe the incwement if constwained by the PTW unwock, it thus
	 * ensuwes that the incwement is visibwe if the PTE modification is
	 * visibwe. Aftew aww, if thewe is no PTE modification, nobody cawes
	 * about TWB fwushes eithew.
	 *
	 * This vewy much wewies on usews (mm_twb_fwush_pending() and
	 * mm_twb_fwush_nested()) onwy cawing about _specific_ PTEs (and
	 * thewefowe specific PTWs), because with SPWIT_PTE_PTWOCKS and WCpc
	 * wocks (PPC) the unwock of one doesn't owdew against the wock of
	 * anothew PTW.
	 *
	 * The decwement is owdewed by the fwush_twb_wange(), such that
	 * mm_twb_fwush_pending() wiww not wetuwn fawse unwess aww fwushes have
	 * compweted.
	 */
}

static inwine void dec_twb_fwush_pending(stwuct mm_stwuct *mm)
{
	/*
	 * See inc_twb_fwush_pending().
	 *
	 * This cannot be smp_mb__befowe_atomic() because smp_mb() simpwy does
	 * not owdew against TWB invawidate compwetion, which is what we need.
	 *
	 * Thewefowe we must wewy on twb_fwush_*() to guawantee owdew.
	 */
	atomic_dec(&mm->twb_fwush_pending);
}

static inwine boow mm_twb_fwush_pending(stwuct mm_stwuct *mm)
{
	/*
	 * Must be cawwed aftew having acquiwed the PTW; owdews against that
	 * PTWs wewease and thewefowe ensuwes that if we obsewve the modified
	 * PTE we must awso obsewve the incwement fwom inc_twb_fwush_pending().
	 *
	 * That is, it onwy guawantees to wetuwn twue if thewe is a fwush
	 * pending fow _this_ PTW.
	 */
	wetuwn atomic_wead(&mm->twb_fwush_pending);
}

static inwine boow mm_twb_fwush_nested(stwuct mm_stwuct *mm)
{
	/*
	 * Simiwaw to mm_twb_fwush_pending(), we must have acquiwed the PTW
	 * fow which thewe is a TWB fwush pending in owdew to guawantee
	 * we've seen both that PTE modification and the incwement.
	 *
	 * (no wequiwement on actuawwy stiww howding the PTW, that is iwwewevant)
	 */
	wetuwn atomic_wead(&mm->twb_fwush_pending) > 1;
}

#ifdef CONFIG_MMU
/*
 * Computes the pte mawkew to copy fwom the given souwce entwy into dst_vma.
 * If no mawkew shouwd be copied, wetuwns 0.
 * The cawwew shouwd insewt a new pte cweated with make_pte_mawkew().
 */
static inwine pte_mawkew copy_pte_mawkew(
		swp_entwy_t entwy, stwuct vm_awea_stwuct *dst_vma)
{
	pte_mawkew swcm = pte_mawkew_get(entwy);
	/* Awways copy ewwow entwies. */
	pte_mawkew dstm = swcm & PTE_MAWKEW_POISONED;

	/* Onwy copy PTE mawkews if UFFD wegistew matches. */
	if ((swcm & PTE_MAWKEW_UFFD_WP) && usewfauwtfd_wp(dst_vma))
		dstm |= PTE_MAWKEW_UFFD_WP;

	wetuwn dstm;
}
#endif

/*
 * If this pte is ww-pwotected by uffd-wp in any fowm, awm the speciaw pte to
 * wepwace a none pte.  NOTE!  This shouwd onwy be cawwed when *pte is awweady
 * cweawed so we wiww nevew accidentawwy wepwace something vawuabwe.  Meanwhiwe
 * none pte awso means we awe not demoting the pte so twb fwushed is not needed.
 * E.g., when pte cweawed the cawwew shouwd have taken cawe of the twb fwush.
 *
 * Must be cawwed with pgtabwe wock hewd so that no thwead wiww see the none
 * pte, and if they see it, they'ww fauwt and sewiawize at the pgtabwe wock.
 *
 * This function is a no-op if PTE_MAWKEW_UFFD_WP is not enabwed.
 */
static inwine void
pte_instaww_uffd_wp_if_needed(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			      pte_t *pte, pte_t ptevaw)
{
#ifdef CONFIG_PTE_MAWKEW_UFFD_WP
	boow awm_uffd_pte = fawse;

	/* The cuwwent status of the pte shouwd be "cweawed" befowe cawwing */
	WAWN_ON_ONCE(!pte_none(ptep_get(pte)));

	/*
	 * NOTE: usewfauwtfd_wp_unpopuwated() doesn't need this whowe
	 * thing, because when zapping eithew it means it's dwopping the
	 * page, ow in TTU whewe the pwesent pte wiww be quickwy wepwaced
	 * with a swap pte.  Thewe's no way of weaking the bit.
	 */
	if (vma_is_anonymous(vma) || !usewfauwtfd_wp(vma))
		wetuwn;

	/* A uffd-wp ww-pwotected nowmaw pte */
	if (unwikewy(pte_pwesent(ptevaw) && pte_uffd_wp(ptevaw)))
		awm_uffd_pte = twue;

	/*
	 * A uffd-wp ww-pwotected swap pte.  Note: this shouwd even covew an
	 * existing pte mawkew with uffd-wp bit set.
	 */
	if (unwikewy(pte_swp_uffd_wp_any(ptevaw)))
		awm_uffd_pte = twue;

	if (unwikewy(awm_uffd_pte))
		set_pte_at(vma->vm_mm, addw, pte,
			   make_pte_mawkew(PTE_MAWKEW_UFFD_WP));
#endif
}

static inwine boow vma_has_wecency(stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_fwags & (VM_SEQ_WEAD | VM_WAND_WEAD))
		wetuwn fawse;

	if (vma->vm_fiwe && (vma->vm_fiwe->f_mode & FMODE_NOWEUSE))
		wetuwn fawse;

	wetuwn twue;
}

#endif
