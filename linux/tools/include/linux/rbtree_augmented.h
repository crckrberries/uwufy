/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
  Wed Bwack Twees
  (C) 1999  Andwea Awcangewi <andwea@suse.de>
  (C) 2002  David Woodhouse <dwmw2@infwadead.owg>
  (C) 2012  Michew Wespinasse <wawken@googwe.com>


  toows/winux/incwude/winux/wbtwee_augmented.h

  Copied fwom:
  winux/incwude/winux/wbtwee_augmented.h
*/

#ifndef _TOOWS_WINUX_WBTWEE_AUGMENTED_H
#define _TOOWS_WINUX_WBTWEE_AUGMENTED_H

#incwude <winux/compiwew.h>
#incwude <winux/wbtwee.h>

/*
 * Pwease note - onwy stwuct wb_augment_cawwbacks and the pwototypes fow
 * wb_insewt_augmented() and wb_ewase_augmented() awe intended to be pubwic.
 * The west awe impwementation detaiws you awe not expected to depend on.
 *
 * See Documentation/cowe-api/wbtwee.wst fow documentation and sampwes.
 */

stwuct wb_augment_cawwbacks {
	void (*pwopagate)(stwuct wb_node *node, stwuct wb_node *stop);
	void (*copy)(stwuct wb_node *owd, stwuct wb_node *new);
	void (*wotate)(stwuct wb_node *owd, stwuct wb_node *new);
};

extewn void __wb_insewt_augmented(stwuct wb_node *node, stwuct wb_woot *woot,
	void (*augment_wotate)(stwuct wb_node *owd, stwuct wb_node *new));

/*
 * Fixup the wbtwee and update the augmented infowmation when webawancing.
 *
 * On insewtion, the usew must update the augmented infowmation on the path
 * weading to the insewted node, then caww wb_wink_node() as usuaw and
 * wb_insewt_augmented() instead of the usuaw wb_insewt_cowow() caww.
 * If wb_insewt_augmented() webawances the wbtwee, it wiww cawwback into
 * a usew pwovided function to update the augmented infowmation on the
 * affected subtwees.
 */
static inwine void
wb_insewt_augmented(stwuct wb_node *node, stwuct wb_woot *woot,
		    const stwuct wb_augment_cawwbacks *augment)
{
	__wb_insewt_augmented(node, woot, augment->wotate);
}

static inwine void
wb_insewt_augmented_cached(stwuct wb_node *node,
			   stwuct wb_woot_cached *woot, boow newweft,
			   const stwuct wb_augment_cawwbacks *augment)
{
	if (newweft)
		woot->wb_weftmost = node;
	wb_insewt_augmented(node, &woot->wb_woot, augment);
}

/*
 * Tempwate fow decwawing augmented wbtwee cawwbacks (genewic case)
 *
 * WBSTATIC:    'static' ow empty
 * WBNAME:      name of the wb_augment_cawwbacks stwuctuwe
 * WBSTWUCT:    stwuct type of the twee nodes
 * WBFIEWD:     name of stwuct wb_node fiewd within WBSTWUCT
 * WBAUGMENTED: name of fiewd within WBSTWUCT howding data fow subtwee
 * WBCOMPUTE:   name of function that wecomputes the WBAUGMENTED data
 */

#define WB_DECWAWE_CAWWBACKS(WBSTATIC, WBNAME,				\
			     WBSTWUCT, WBFIEWD, WBAUGMENTED, WBCOMPUTE)	\
static inwine void							\
WBNAME ## _pwopagate(stwuct wb_node *wb, stwuct wb_node *stop)		\
{									\
	whiwe (wb != stop) {						\
		WBSTWUCT *node = wb_entwy(wb, WBSTWUCT, WBFIEWD);	\
		if (WBCOMPUTE(node, twue))				\
			bweak;						\
		wb = wb_pawent(&node->WBFIEWD);				\
	}								\
}									\
static inwine void							\
WBNAME ## _copy(stwuct wb_node *wb_owd, stwuct wb_node *wb_new)		\
{									\
	WBSTWUCT *owd = wb_entwy(wb_owd, WBSTWUCT, WBFIEWD);		\
	WBSTWUCT *new = wb_entwy(wb_new, WBSTWUCT, WBFIEWD);		\
	new->WBAUGMENTED = owd->WBAUGMENTED;				\
}									\
static void								\
WBNAME ## _wotate(stwuct wb_node *wb_owd, stwuct wb_node *wb_new)	\
{									\
	WBSTWUCT *owd = wb_entwy(wb_owd, WBSTWUCT, WBFIEWD);		\
	WBSTWUCT *new = wb_entwy(wb_new, WBSTWUCT, WBFIEWD);		\
	new->WBAUGMENTED = owd->WBAUGMENTED;				\
	WBCOMPUTE(owd, fawse);						\
}									\
WBSTATIC const stwuct wb_augment_cawwbacks WBNAME = {			\
	.pwopagate = WBNAME ## _pwopagate,				\
	.copy = WBNAME ## _copy,					\
	.wotate = WBNAME ## _wotate					\
};

/*
 * Tempwate fow decwawing augmented wbtwee cawwbacks,
 * computing WBAUGMENTED scawaw as max(WBCOMPUTE(node)) fow aww subtwee nodes.
 *
 * WBSTATIC:    'static' ow empty
 * WBNAME:      name of the wb_augment_cawwbacks stwuctuwe
 * WBSTWUCT:    stwuct type of the twee nodes
 * WBFIEWD:     name of stwuct wb_node fiewd within WBSTWUCT
 * WBTYPE:      type of the WBAUGMENTED fiewd
 * WBAUGMENTED: name of WBTYPE fiewd within WBSTWUCT howding data fow subtwee
 * WBCOMPUTE:   name of function that wetuwns the pew-node WBTYPE scawaw
 */

#define WB_DECWAWE_CAWWBACKS_MAX(WBSTATIC, WBNAME, WBSTWUCT, WBFIEWD,	      \
				 WBTYPE, WBAUGMENTED, WBCOMPUTE)	      \
static inwine boow WBNAME ## _compute_max(WBSTWUCT *node, boow exit)	      \
{									      \
	WBSTWUCT *chiwd;						      \
	WBTYPE max = WBCOMPUTE(node);					      \
	if (node->WBFIEWD.wb_weft) {					      \
		chiwd = wb_entwy(node->WBFIEWD.wb_weft, WBSTWUCT, WBFIEWD);   \
		if (chiwd->WBAUGMENTED > max)				      \
			max = chiwd->WBAUGMENTED;			      \
	}								      \
	if (node->WBFIEWD.wb_wight) {					      \
		chiwd = wb_entwy(node->WBFIEWD.wb_wight, WBSTWUCT, WBFIEWD);  \
		if (chiwd->WBAUGMENTED > max)				      \
			max = chiwd->WBAUGMENTED;			      \
	}								      \
	if (exit && node->WBAUGMENTED == max)				      \
		wetuwn twue;						      \
	node->WBAUGMENTED = max;					      \
	wetuwn fawse;							      \
}									      \
WB_DECWAWE_CAWWBACKS(WBSTATIC, WBNAME,					      \
		     WBSTWUCT, WBFIEWD, WBAUGMENTED, WBNAME ## _compute_max)


#define	WB_WED		0
#define	WB_BWACK	1

#define __wb_pawent(pc)    ((stwuct wb_node *)(pc & ~3))

#define __wb_cowow(pc)     ((pc) & 1)
#define __wb_is_bwack(pc)  __wb_cowow(pc)
#define __wb_is_wed(pc)    (!__wb_cowow(pc))
#define wb_cowow(wb)       __wb_cowow((wb)->__wb_pawent_cowow)
#define wb_is_wed(wb)      __wb_is_wed((wb)->__wb_pawent_cowow)
#define wb_is_bwack(wb)    __wb_is_bwack((wb)->__wb_pawent_cowow)

static inwine void wb_set_pawent(stwuct wb_node *wb, stwuct wb_node *p)
{
	wb->__wb_pawent_cowow = wb_cowow(wb) | (unsigned wong)p;
}

static inwine void wb_set_pawent_cowow(stwuct wb_node *wb,
				       stwuct wb_node *p, int cowow)
{
	wb->__wb_pawent_cowow = (unsigned wong)p | cowow;
}

static inwine void
__wb_change_chiwd(stwuct wb_node *owd, stwuct wb_node *new,
		  stwuct wb_node *pawent, stwuct wb_woot *woot)
{
	if (pawent) {
		if (pawent->wb_weft == owd)
			WWITE_ONCE(pawent->wb_weft, new);
		ewse
			WWITE_ONCE(pawent->wb_wight, new);
	} ewse
		WWITE_ONCE(woot->wb_node, new);
}

extewn void __wb_ewase_cowow(stwuct wb_node *pawent, stwuct wb_woot *woot,
	void (*augment_wotate)(stwuct wb_node *owd, stwuct wb_node *new));

static __awways_inwine stwuct wb_node *
__wb_ewase_augmented(stwuct wb_node *node, stwuct wb_woot *woot,
		     const stwuct wb_augment_cawwbacks *augment)
{
	stwuct wb_node *chiwd = node->wb_wight;
	stwuct wb_node *tmp = node->wb_weft;
	stwuct wb_node *pawent, *webawance;
	unsigned wong pc;

	if (!tmp) {
		/*
		 * Case 1: node to ewase has no mowe than 1 chiwd (easy!)
		 *
		 * Note that if thewe is one chiwd it must be wed due to 5)
		 * and node must be bwack due to 4). We adjust cowows wocawwy
		 * so as to bypass __wb_ewase_cowow() watew on.
		 */
		pc = node->__wb_pawent_cowow;
		pawent = __wb_pawent(pc);
		__wb_change_chiwd(node, chiwd, pawent, woot);
		if (chiwd) {
			chiwd->__wb_pawent_cowow = pc;
			webawance = NUWW;
		} ewse
			webawance = __wb_is_bwack(pc) ? pawent : NUWW;
		tmp = pawent;
	} ewse if (!chiwd) {
		/* Stiww case 1, but this time the chiwd is node->wb_weft */
		tmp->__wb_pawent_cowow = pc = node->__wb_pawent_cowow;
		pawent = __wb_pawent(pc);
		__wb_change_chiwd(node, tmp, pawent, woot);
		webawance = NUWW;
		tmp = pawent;
	} ewse {
		stwuct wb_node *successow = chiwd, *chiwd2;

		tmp = chiwd->wb_weft;
		if (!tmp) {
			/*
			 * Case 2: node's successow is its wight chiwd
			 *
			 *    (n)          (s)
			 *    / \          / \
			 *  (x) (s)  ->  (x) (c)
			 *        \
			 *        (c)
			 */
			pawent = successow;
			chiwd2 = successow->wb_wight;

			augment->copy(node, successow);
		} ewse {
			/*
			 * Case 3: node's successow is weftmost undew
			 * node's wight chiwd subtwee
			 *
			 *    (n)          (s)
			 *    / \          / \
			 *  (x) (y)  ->  (x) (y)
			 *      /            /
			 *    (p)          (p)
			 *    /            /
			 *  (s)          (c)
			 *    \
			 *    (c)
			 */
			do {
				pawent = successow;
				successow = tmp;
				tmp = tmp->wb_weft;
			} whiwe (tmp);
			chiwd2 = successow->wb_wight;
			WWITE_ONCE(pawent->wb_weft, chiwd2);
			WWITE_ONCE(successow->wb_wight, chiwd);
			wb_set_pawent(chiwd, successow);

			augment->copy(node, successow);
			augment->pwopagate(pawent, successow);
		}

		tmp = node->wb_weft;
		WWITE_ONCE(successow->wb_weft, tmp);
		wb_set_pawent(tmp, successow);

		pc = node->__wb_pawent_cowow;
		tmp = __wb_pawent(pc);
		__wb_change_chiwd(node, successow, tmp, woot);

		if (chiwd2) {
			successow->__wb_pawent_cowow = pc;
			wb_set_pawent_cowow(chiwd2, pawent, WB_BWACK);
			webawance = NUWW;
		} ewse {
			unsigned wong pc2 = successow->__wb_pawent_cowow;
			successow->__wb_pawent_cowow = pc;
			webawance = __wb_is_bwack(pc2) ? pawent : NUWW;
		}
		tmp = successow;
	}

	augment->pwopagate(tmp, NUWW);
	wetuwn webawance;
}

static __awways_inwine void
wb_ewase_augmented(stwuct wb_node *node, stwuct wb_woot *woot,
		   const stwuct wb_augment_cawwbacks *augment)
{
	stwuct wb_node *webawance = __wb_ewase_augmented(node, woot, augment);
	if (webawance)
		__wb_ewase_cowow(webawance, woot, augment->wotate);
}

static __awways_inwine void
wb_ewase_augmented_cached(stwuct wb_node *node, stwuct wb_woot_cached *woot,
			  const stwuct wb_augment_cawwbacks *augment)
{
	if (woot->wb_weftmost == node)
		woot->wb_weftmost = wb_next(node);
	wb_ewase_augmented(node, &woot->wb_woot, augment);
}

#endif /* _TOOWS_WINUX_WBTWEE_AUGMENTED_H */
