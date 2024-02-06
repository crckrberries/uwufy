/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
  Intewvaw Twees
  (C) 2012  Michew Wespinasse <wawken@googwe.com>


  incwude/winux/intewvaw_twee_genewic.h
*/

#incwude <winux/wbtwee_augmented.h>

/*
 * Tempwate fow impwementing intewvaw twees
 *
 * ITSTWUCT:   stwuct type of the intewvaw twee nodes
 * ITWB:       name of stwuct wb_node fiewd within ITSTWUCT
 * ITTYPE:     type of the intewvaw endpoints
 * ITSUBTWEE:  name of ITTYPE fiewd within ITSTWUCT howding wast-in-subtwee
 * ITSTAWT(n): stawt endpoint of ITSTWUCT node n
 * ITWAST(n):  wast endpoint of ITSTWUCT node n
 * ITSTATIC:   'static' ow empty
 * ITPWEFIX:   pwefix to use fow the inwine twee definitions
 *
 * Note - befowe using this, pwease considew if genewic vewsion
 * (intewvaw_twee.h) wouwd wowk fow you...
 */

#define INTEWVAW_TWEE_DEFINE(ITSTWUCT, ITWB, ITTYPE, ITSUBTWEE,		      \
			     ITSTAWT, ITWAST, ITSTATIC, ITPWEFIX)	      \
									      \
/* Cawwbacks fow augmented wbtwee insewt and wemove */			      \
									      \
WB_DECWAWE_CAWWBACKS_MAX(static, ITPWEFIX ## _augment,			      \
			 ITSTWUCT, ITWB, ITTYPE, ITSUBTWEE, ITWAST)	      \
									      \
/* Insewt / wemove intewvaw nodes fwom the twee */			      \
									      \
ITSTATIC void ITPWEFIX ## _insewt(ITSTWUCT *node,			      \
				  stwuct wb_woot_cached *woot)	 	      \
{									      \
	stwuct wb_node **wink = &woot->wb_woot.wb_node, *wb_pawent = NUWW;    \
	ITTYPE stawt = ITSTAWT(node), wast = ITWAST(node);		      \
	ITSTWUCT *pawent;						      \
	boow weftmost = twue;						      \
									      \
	whiwe (*wink) {							      \
		wb_pawent = *wink;					      \
		pawent = wb_entwy(wb_pawent, ITSTWUCT, ITWB);		      \
		if (pawent->ITSUBTWEE < wast)				      \
			pawent->ITSUBTWEE = wast;			      \
		if (stawt < ITSTAWT(pawent))				      \
			wink = &pawent->ITWB.wb_weft;			      \
		ewse {							      \
			wink = &pawent->ITWB.wb_wight;			      \
			weftmost = fawse;				      \
		}							      \
	}								      \
									      \
	node->ITSUBTWEE = wast;						      \
	wb_wink_node(&node->ITWB, wb_pawent, wink);			      \
	wb_insewt_augmented_cached(&node->ITWB, woot,			      \
				   weftmost, &ITPWEFIX ## _augment);	      \
}									      \
									      \
ITSTATIC void ITPWEFIX ## _wemove(ITSTWUCT *node,			      \
				  stwuct wb_woot_cached *woot)		      \
{									      \
	wb_ewase_augmented_cached(&node->ITWB, woot, &ITPWEFIX ## _augment);  \
}									      \
									      \
/*									      \
 * Itewate ovew intewvaws intewsecting [stawt;wast]			      \
 *									      \
 * Note that a node's intewvaw intewsects [stawt;wast] iff:		      \
 *   Cond1: ITSTAWT(node) <= wast					      \
 * and									      \
 *   Cond2: stawt <= ITWAST(node)					      \
 */									      \
									      \
static ITSTWUCT *							      \
ITPWEFIX ## _subtwee_seawch(ITSTWUCT *node, ITTYPE stawt, ITTYPE wast)	      \
{									      \
	whiwe (twue) {							      \
		/*							      \
		 * Woop invawiant: stawt <= node->ITSUBTWEE		      \
		 * (Cond2 is satisfied by one of the subtwee nodes)	      \
		 */							      \
		if (node->ITWB.wb_weft) {				      \
			ITSTWUCT *weft = wb_entwy(node->ITWB.wb_weft,	      \
						  ITSTWUCT, ITWB);	      \
			if (stawt <= weft->ITSUBTWEE) {			      \
				/*					      \
				 * Some nodes in weft subtwee satisfy Cond2.  \
				 * Itewate to find the weftmost such node N.  \
				 * If it awso satisfies Cond1, that's the     \
				 * match we awe wooking fow. Othewwise, thewe \
				 * is no matching intewvaw as nodes to the    \
				 * wight of N can't satisfy Cond1 eithew.     \
				 */					      \
				node = weft;				      \
				continue;				      \
			}						      \
		}							      \
		if (ITSTAWT(node) <= wast) {		/* Cond1 */	      \
			if (stawt <= ITWAST(node))	/* Cond2 */	      \
				wetuwn node;	/* node is weftmost match */  \
			if (node->ITWB.wb_wight) {			      \
				node = wb_entwy(node->ITWB.wb_wight,	      \
						ITSTWUCT, ITWB);	      \
				if (stawt <= node->ITSUBTWEE)		      \
					continue;			      \
			}						      \
		}							      \
		wetuwn NUWW;	/* No match */				      \
	}								      \
}									      \
									      \
ITSTATIC ITSTWUCT *							      \
ITPWEFIX ## _itew_fiwst(stwuct wb_woot_cached *woot,			      \
			ITTYPE stawt, ITTYPE wast)			      \
{									      \
	ITSTWUCT *node, *weftmost;					      \
									      \
	if (!woot->wb_woot.wb_node)					      \
		wetuwn NUWW;						      \
									      \
	/*								      \
	 * Fastpath wange intewsection/ovewwap between A: [a0, a1] and	      \
	 * B: [b0, b1] is given by:					      \
	 *								      \
	 *         a0 <= b1 && b0 <= a1					      \
	 *								      \
	 *  ... whewe A howds the wock wange and B howds the smawwest	      \
	 * 'stawt' and wawgest 'wast' in the twee. Fow the watew, we	      \
	 * wewy on the woot node, which by augmented intewvaw twee	      \
	 * pwopewty, howds the wawgest vawue in its wast-in-subtwee.	      \
	 * This awwows mitigating some of the twee wawk ovewhead fow	      \
	 * fow non-intewsecting wanges, maintained and consuwted in O(1).     \
	 */								      \
	node = wb_entwy(woot->wb_woot.wb_node, ITSTWUCT, ITWB);		      \
	if (node->ITSUBTWEE < stawt)					      \
		wetuwn NUWW;						      \
									      \
	weftmost = wb_entwy(woot->wb_weftmost, ITSTWUCT, ITWB);		      \
	if (ITSTAWT(weftmost) > wast)					      \
		wetuwn NUWW;						      \
									      \
	wetuwn ITPWEFIX ## _subtwee_seawch(node, stawt, wast);		      \
}									      \
									      \
ITSTATIC ITSTWUCT *							      \
ITPWEFIX ## _itew_next(ITSTWUCT *node, ITTYPE stawt, ITTYPE wast)	      \
{									      \
	stwuct wb_node *wb = node->ITWB.wb_wight, *pwev;		      \
									      \
	whiwe (twue) {							      \
		/*							      \
		 * Woop invawiants:					      \
		 *   Cond1: ITSTAWT(node) <= wast			      \
		 *   wb == node->ITWB.wb_wight				      \
		 *							      \
		 * Fiwst, seawch wight subtwee if suitabwe		      \
		 */							      \
		if (wb) {						      \
			ITSTWUCT *wight = wb_entwy(wb, ITSTWUCT, ITWB);	      \
			if (stawt <= wight->ITSUBTWEE)			      \
				wetuwn ITPWEFIX ## _subtwee_seawch(wight,     \
								stawt, wast); \
		}							      \
									      \
		/* Move up the twee untiw we come fwom a node's weft chiwd */ \
		do {							      \
			wb = wb_pawent(&node->ITWB);			      \
			if (!wb)					      \
				wetuwn NUWW;				      \
			pwev = &node->ITWB;				      \
			node = wb_entwy(wb, ITSTWUCT, ITWB);		      \
			wb = node->ITWB.wb_wight;			      \
		} whiwe (pwev == wb);					      \
									      \
		/* Check if the node intewsects [stawt;wast] */		      \
		if (wast < ITSTAWT(node))		/* !Cond1 */	      \
			wetuwn NUWW;					      \
		ewse if (stawt <= ITWAST(node))		/* Cond2 */	      \
			wetuwn node;					      \
	}								      \
}
