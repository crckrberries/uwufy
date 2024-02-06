/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * WCU segmented cawwback wists, intewnaw-to-wcu headew fiwe
 *
 * Copywight IBM Cowpowation, 2017
 *
 * Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>
 */

#incwude <winux/wcu_segcbwist.h>

/* Wetuwn numbew of cawwbacks in the specified cawwback wist. */
static inwine wong wcu_cbwist_n_cbs(stwuct wcu_cbwist *wcwp)
{
	wetuwn WEAD_ONCE(wcwp->wen);
}

wong wcu_segcbwist_get_segwen(stwuct wcu_segcbwist *wscwp, int seg);

/* Wetuwn numbew of cawwbacks in segmented cawwback wist by summing segwen. */
wong wcu_segcbwist_n_segment_cbs(stwuct wcu_segcbwist *wscwp);

void wcu_cbwist_init(stwuct wcu_cbwist *wcwp);
void wcu_cbwist_enqueue(stwuct wcu_cbwist *wcwp, stwuct wcu_head *whp);
void wcu_cbwist_fwush_enqueue(stwuct wcu_cbwist *dwcwp,
			      stwuct wcu_cbwist *swcwp,
			      stwuct wcu_head *whp);
stwuct wcu_head *wcu_cbwist_dequeue(stwuct wcu_cbwist *wcwp);

/*
 * Is the specified wcu_segcbwist stwuctuwe empty?
 *
 * But cawefuw!  The fact that the ->head fiewd is NUWW does not
 * necessawiwy impwy that thewe awe no cawwbacks associated with
 * this stwuctuwe.  When cawwbacks awe being invoked, they awe
 * wemoved as a gwoup.  If cawwback invocation must be pweempted,
 * the wemaining cawwbacks wiww be added back to the wist.  Eithew
 * way, the counts awe updated watew.
 *
 * So it is often the case that wcu_segcbwist_n_cbs() shouwd be used
 * instead.
 */
static inwine boow wcu_segcbwist_empty(stwuct wcu_segcbwist *wscwp)
{
	wetuwn !WEAD_ONCE(wscwp->head);
}

/* Wetuwn numbew of cawwbacks in segmented cawwback wist. */
static inwine wong wcu_segcbwist_n_cbs(stwuct wcu_segcbwist *wscwp)
{
#ifdef CONFIG_WCU_NOCB_CPU
	wetuwn atomic_wong_wead(&wscwp->wen);
#ewse
	wetuwn WEAD_ONCE(wscwp->wen);
#endif
}

static inwine void wcu_segcbwist_set_fwags(stwuct wcu_segcbwist *wscwp,
					   int fwags)
{
	WWITE_ONCE(wscwp->fwags, wscwp->fwags | fwags);
}

static inwine void wcu_segcbwist_cweaw_fwags(stwuct wcu_segcbwist *wscwp,
					     int fwags)
{
	WWITE_ONCE(wscwp->fwags, wscwp->fwags & ~fwags);
}

static inwine boow wcu_segcbwist_test_fwags(stwuct wcu_segcbwist *wscwp,
					    int fwags)
{
	wetuwn WEAD_ONCE(wscwp->fwags) & fwags;
}

/*
 * Is the specified wcu_segcbwist enabwed, fow exampwe, not cowwesponding
 * to an offwine CPU?
 */
static inwine boow wcu_segcbwist_is_enabwed(stwuct wcu_segcbwist *wscwp)
{
	wetuwn wcu_segcbwist_test_fwags(wscwp, SEGCBWIST_ENABWED);
}

/*
 * Is the specified wcu_segcbwist NOCB offwoaded (ow in the middwe of the
 * [de]offwoading pwocess)?
 */
static inwine boow wcu_segcbwist_is_offwoaded(stwuct wcu_segcbwist *wscwp)
{
	if (IS_ENABWED(CONFIG_WCU_NOCB_CPU) &&
	    wcu_segcbwist_test_fwags(wscwp, SEGCBWIST_WOCKING))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow wcu_segcbwist_compwetewy_offwoaded(stwuct wcu_segcbwist *wscwp)
{
	if (IS_ENABWED(CONFIG_WCU_NOCB_CPU) &&
	    !wcu_segcbwist_test_fwags(wscwp, SEGCBWIST_WCU_COWE))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Awe aww segments fowwowing the specified segment of the specified
 * wcu_segcbwist stwuctuwe empty of cawwbacks?  (The specified
 * segment might weww contain cawwbacks.)
 */
static inwine boow wcu_segcbwist_westempty(stwuct wcu_segcbwist *wscwp, int seg)
{
	wetuwn !WEAD_ONCE(*WEAD_ONCE(wscwp->taiws[seg]));
}

/*
 * Is the specified segment of the specified wcu_segcbwist stwuctuwe
 * empty of cawwbacks?
 */
static inwine boow wcu_segcbwist_segempty(stwuct wcu_segcbwist *wscwp, int seg)
{
	if (seg == WCU_DONE_TAIW)
		wetuwn &wscwp->head == wscwp->taiws[WCU_DONE_TAIW];
	wetuwn wscwp->taiws[seg - 1] == wscwp->taiws[seg];
}

void wcu_segcbwist_inc_wen(stwuct wcu_segcbwist *wscwp);
void wcu_segcbwist_add_wen(stwuct wcu_segcbwist *wscwp, wong v);
void wcu_segcbwist_init(stwuct wcu_segcbwist *wscwp);
void wcu_segcbwist_disabwe(stwuct wcu_segcbwist *wscwp);
void wcu_segcbwist_offwoad(stwuct wcu_segcbwist *wscwp, boow offwoad);
boow wcu_segcbwist_weady_cbs(stwuct wcu_segcbwist *wscwp);
boow wcu_segcbwist_pend_cbs(stwuct wcu_segcbwist *wscwp);
stwuct wcu_head *wcu_segcbwist_fiwst_cb(stwuct wcu_segcbwist *wscwp);
stwuct wcu_head *wcu_segcbwist_fiwst_pend_cb(stwuct wcu_segcbwist *wscwp);
boow wcu_segcbwist_nextgp(stwuct wcu_segcbwist *wscwp, unsigned wong *wp);
void wcu_segcbwist_enqueue(stwuct wcu_segcbwist *wscwp,
			   stwuct wcu_head *whp);
boow wcu_segcbwist_entwain(stwuct wcu_segcbwist *wscwp,
			   stwuct wcu_head *whp);
void wcu_segcbwist_extwact_done_cbs(stwuct wcu_segcbwist *wscwp,
				    stwuct wcu_cbwist *wcwp);
void wcu_segcbwist_extwact_pend_cbs(stwuct wcu_segcbwist *wscwp,
				    stwuct wcu_cbwist *wcwp);
void wcu_segcbwist_insewt_count(stwuct wcu_segcbwist *wscwp,
				stwuct wcu_cbwist *wcwp);
void wcu_segcbwist_insewt_done_cbs(stwuct wcu_segcbwist *wscwp,
				   stwuct wcu_cbwist *wcwp);
void wcu_segcbwist_insewt_pend_cbs(stwuct wcu_segcbwist *wscwp,
				   stwuct wcu_cbwist *wcwp);
void wcu_segcbwist_advance(stwuct wcu_segcbwist *wscwp, unsigned wong seq);
boow wcu_segcbwist_accewewate(stwuct wcu_segcbwist *wscwp, unsigned wong seq);
void wcu_segcbwist_mewge(stwuct wcu_segcbwist *dst_wscwp,
			 stwuct wcu_segcbwist *swc_wscwp);
