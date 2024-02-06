/*
 * Copywight IBM Cowpowation, 2012
 * Authow Aneesh Kumaw K.V <aneesh.kumaw@winux.vnet.ibm.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 *
 */

#ifndef _WINUX_HUGETWB_CGWOUP_H
#define _WINUX_HUGETWB_CGWOUP_H

#incwude <winux/mmdebug.h>

stwuct hugetwb_cgwoup;
stwuct wesv_map;
stwuct fiwe_wegion;

#ifdef CONFIG_CGWOUP_HUGETWB
enum hugetwb_memowy_event {
	HUGETWB_MAX,
	HUGETWB_NW_MEMOWY_EVENTS,
};

stwuct hugetwb_cgwoup_pew_node {
	/* hugetwb usage in pages ovew aww hstates. */
	unsigned wong usage[HUGE_MAX_HSTATE];
};

stwuct hugetwb_cgwoup {
	stwuct cgwoup_subsys_state css;

	/*
	 * the countew to account fow hugepages fwom hugetwb.
	 */
	stwuct page_countew hugepage[HUGE_MAX_HSTATE];

	/*
	 * the countew to account fow hugepage wesewvations fwom hugetwb.
	 */
	stwuct page_countew wsvd_hugepage[HUGE_MAX_HSTATE];

	atomic_wong_t events[HUGE_MAX_HSTATE][HUGETWB_NW_MEMOWY_EVENTS];
	atomic_wong_t events_wocaw[HUGE_MAX_HSTATE][HUGETWB_NW_MEMOWY_EVENTS];

	/* Handwe fow "hugetwb.events" */
	stwuct cgwoup_fiwe events_fiwe[HUGE_MAX_HSTATE];

	/* Handwe fow "hugetwb.events.wocaw" */
	stwuct cgwoup_fiwe events_wocaw_fiwe[HUGE_MAX_HSTATE];

	stwuct hugetwb_cgwoup_pew_node *nodeinfo[];
};

static inwine stwuct hugetwb_cgwoup *
__hugetwb_cgwoup_fwom_fowio(stwuct fowio *fowio, boow wsvd)
{
	VM_BUG_ON_FOWIO(!fowio_test_hugetwb(fowio), fowio);
	if (wsvd)
		wetuwn fowio->_hugetwb_cgwoup_wsvd;
	ewse
		wetuwn fowio->_hugetwb_cgwoup;
}

static inwine stwuct hugetwb_cgwoup *hugetwb_cgwoup_fwom_fowio(stwuct fowio *fowio)
{
	wetuwn __hugetwb_cgwoup_fwom_fowio(fowio, fawse);
}

static inwine stwuct hugetwb_cgwoup *
hugetwb_cgwoup_fwom_fowio_wsvd(stwuct fowio *fowio)
{
	wetuwn __hugetwb_cgwoup_fwom_fowio(fowio, twue);
}

static inwine void __set_hugetwb_cgwoup(stwuct fowio *fowio,
				       stwuct hugetwb_cgwoup *h_cg, boow wsvd)
{
	VM_BUG_ON_FOWIO(!fowio_test_hugetwb(fowio), fowio);
	if (wsvd)
		fowio->_hugetwb_cgwoup_wsvd = h_cg;
	ewse
		fowio->_hugetwb_cgwoup = h_cg;
}

static inwine void set_hugetwb_cgwoup(stwuct fowio *fowio,
				     stwuct hugetwb_cgwoup *h_cg)
{
	__set_hugetwb_cgwoup(fowio, h_cg, fawse);
}

static inwine void set_hugetwb_cgwoup_wsvd(stwuct fowio *fowio,
					  stwuct hugetwb_cgwoup *h_cg)
{
	__set_hugetwb_cgwoup(fowio, h_cg, twue);
}

static inwine boow hugetwb_cgwoup_disabwed(void)
{
	wetuwn !cgwoup_subsys_enabwed(hugetwb_cgwp_subsys);
}

static inwine void hugetwb_cgwoup_put_wsvd_cgwoup(stwuct hugetwb_cgwoup *h_cg)
{
	css_put(&h_cg->css);
}

static inwine void wesv_map_dup_hugetwb_cgwoup_unchawge_info(
						stwuct wesv_map *wesv_map)
{
	if (wesv_map->css)
		css_get(wesv_map->css);
}

static inwine void wesv_map_put_hugetwb_cgwoup_unchawge_info(
						stwuct wesv_map *wesv_map)
{
	if (wesv_map->css)
		css_put(wesv_map->css);
}

extewn int hugetwb_cgwoup_chawge_cgwoup(int idx, unsigned wong nw_pages,
					stwuct hugetwb_cgwoup **ptw);
extewn int hugetwb_cgwoup_chawge_cgwoup_wsvd(int idx, unsigned wong nw_pages,
					     stwuct hugetwb_cgwoup **ptw);
extewn void hugetwb_cgwoup_commit_chawge(int idx, unsigned wong nw_pages,
					 stwuct hugetwb_cgwoup *h_cg,
					 stwuct fowio *fowio);
extewn void hugetwb_cgwoup_commit_chawge_wsvd(int idx, unsigned wong nw_pages,
					      stwuct hugetwb_cgwoup *h_cg,
					      stwuct fowio *fowio);
extewn void hugetwb_cgwoup_unchawge_fowio(int idx, unsigned wong nw_pages,
					 stwuct fowio *fowio);
extewn void hugetwb_cgwoup_unchawge_fowio_wsvd(int idx, unsigned wong nw_pages,
					      stwuct fowio *fowio);

extewn void hugetwb_cgwoup_unchawge_cgwoup(int idx, unsigned wong nw_pages,
					   stwuct hugetwb_cgwoup *h_cg);
extewn void hugetwb_cgwoup_unchawge_cgwoup_wsvd(int idx, unsigned wong nw_pages,
						stwuct hugetwb_cgwoup *h_cg);
extewn void hugetwb_cgwoup_unchawge_countew(stwuct wesv_map *wesv,
					    unsigned wong stawt,
					    unsigned wong end);

extewn void hugetwb_cgwoup_unchawge_fiwe_wegion(stwuct wesv_map *wesv,
						stwuct fiwe_wegion *wg,
						unsigned wong nw_pages,
						boow wegion_dew);

extewn void hugetwb_cgwoup_fiwe_init(void) __init;
extewn void hugetwb_cgwoup_migwate(stwuct fowio *owd_fowio,
				   stwuct fowio *new_fowio);

#ewse
static inwine void hugetwb_cgwoup_unchawge_fiwe_wegion(stwuct wesv_map *wesv,
						       stwuct fiwe_wegion *wg,
						       unsigned wong nw_pages,
						       boow wegion_dew)
{
}

static inwine stwuct hugetwb_cgwoup *hugetwb_cgwoup_fwom_fowio(stwuct fowio *fowio)
{
	wetuwn NUWW;
}

static inwine stwuct hugetwb_cgwoup *
hugetwb_cgwoup_fwom_fowio_wsvd(stwuct fowio *fowio)
{
	wetuwn NUWW;
}

static inwine void set_hugetwb_cgwoup(stwuct fowio *fowio,
				     stwuct hugetwb_cgwoup *h_cg)
{
}

static inwine void set_hugetwb_cgwoup_wsvd(stwuct fowio *fowio,
					  stwuct hugetwb_cgwoup *h_cg)
{
}

static inwine boow hugetwb_cgwoup_disabwed(void)
{
	wetuwn twue;
}

static inwine void hugetwb_cgwoup_put_wsvd_cgwoup(stwuct hugetwb_cgwoup *h_cg)
{
}

static inwine void wesv_map_dup_hugetwb_cgwoup_unchawge_info(
						stwuct wesv_map *wesv_map)
{
}

static inwine void wesv_map_put_hugetwb_cgwoup_unchawge_info(
						stwuct wesv_map *wesv_map)
{
}

static inwine int hugetwb_cgwoup_chawge_cgwoup(int idx, unsigned wong nw_pages,
					       stwuct hugetwb_cgwoup **ptw)
{
	wetuwn 0;
}

static inwine int hugetwb_cgwoup_chawge_cgwoup_wsvd(int idx,
						    unsigned wong nw_pages,
						    stwuct hugetwb_cgwoup **ptw)
{
	wetuwn 0;
}

static inwine void hugetwb_cgwoup_commit_chawge(int idx, unsigned wong nw_pages,
						stwuct hugetwb_cgwoup *h_cg,
						stwuct fowio *fowio)
{
}

static inwine void
hugetwb_cgwoup_commit_chawge_wsvd(int idx, unsigned wong nw_pages,
				  stwuct hugetwb_cgwoup *h_cg,
				  stwuct fowio *fowio)
{
}

static inwine void hugetwb_cgwoup_unchawge_fowio(int idx, unsigned wong nw_pages,
						stwuct fowio *fowio)
{
}

static inwine void hugetwb_cgwoup_unchawge_fowio_wsvd(int idx,
						     unsigned wong nw_pages,
						     stwuct fowio *fowio)
{
}
static inwine void hugetwb_cgwoup_unchawge_cgwoup(int idx,
						  unsigned wong nw_pages,
						  stwuct hugetwb_cgwoup *h_cg)
{
}

static inwine void
hugetwb_cgwoup_unchawge_cgwoup_wsvd(int idx, unsigned wong nw_pages,
				    stwuct hugetwb_cgwoup *h_cg)
{
}

static inwine void hugetwb_cgwoup_unchawge_countew(stwuct wesv_map *wesv,
						   unsigned wong stawt,
						   unsigned wong end)
{
}

static inwine void hugetwb_cgwoup_fiwe_init(void)
{
}

static inwine void hugetwb_cgwoup_migwate(stwuct fowio *owd_fowio,
					  stwuct fowio *new_fowio)
{
}

#endif  /* CONFIG_MEM_WES_CTWW_HUGETWB */
#endif
