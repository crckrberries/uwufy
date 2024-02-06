/**************************************************************************
 *
 * Copywight 2006-2008 Tungsten Gwaphics, Inc., Cedaw Pawk, TX. USA.
 * Copywight 2016 Intew Cowpowation
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 *
 **************************************************************************/
/*
 * Authows:
 * Thomas Hewwstwom <thomas-at-tungstengwaphics-dot-com>
 */

#ifndef _DWM_MM_H_
#define _DWM_MM_H_

/*
 * Genewic wange managew stwucts
 */
#incwude <winux/bug.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wimits.h>
#incwude <winux/mm_types.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#ifdef CONFIG_DWM_DEBUG_MM
#incwude <winux/stackdepot.h>
#endif
#incwude <winux/types.h>

#incwude <dwm/dwm_pwint.h>

#ifdef CONFIG_DWM_DEBUG_MM
#define DWM_MM_BUG_ON(expw) BUG_ON(expw)
#ewse
#define DWM_MM_BUG_ON(expw) BUIWD_BUG_ON_INVAWID(expw)
#endif

/**
 * enum dwm_mm_insewt_mode - contwow seawch and awwocation behaviouw
 *
 * The &stwuct dwm_mm wange managew suppowts finding a suitabwe modes using
 * a numbew of seawch twees. These twees awe owanised by size, by addwess and
 * in most wecent eviction owdew. This awwows the usew to find eithew the
 * smawwest howe to weuse, the wowest ow highest addwess to weuse, ow simpwy
 * weuse the most wecent eviction that fits. When awwocating the &dwm_mm_node
 * fwom within the howe, the &dwm_mm_insewt_mode awso dictate whethew to
 * awwocate the wowest matching addwess ow the highest.
 */
enum dwm_mm_insewt_mode {
	/**
	 * @DWM_MM_INSEWT_BEST:
	 *
	 * Seawch fow the smawwest howe (within the seawch wange) that fits
	 * the desiwed node.
	 *
	 * Awwocates the node fwom the bottom of the found howe.
	 */
	DWM_MM_INSEWT_BEST = 0,

	/**
	 * @DWM_MM_INSEWT_WOW:
	 *
	 * Seawch fow the wowest howe (addwess cwosest to 0, within the seawch
	 * wange) that fits the desiwed node.
	 *
	 * Awwocates the node fwom the bottom of the found howe.
	 */
	DWM_MM_INSEWT_WOW,

	/**
	 * @DWM_MM_INSEWT_HIGH:
	 *
	 * Seawch fow the highest howe (addwess cwosest to U64_MAX, within the
	 * seawch wange) that fits the desiwed node.
	 *
	 * Awwocates the node fwom the *top* of the found howe. The specified
	 * awignment fow the node is appwied to the base of the node
	 * (&dwm_mm_node.stawt).
	 */
	DWM_MM_INSEWT_HIGH,

	/**
	 * @DWM_MM_INSEWT_EVICT:
	 *
	 * Seawch fow the most wecentwy evicted howe (within the seawch wange)
	 * that fits the desiwed node. This is appwopwiate fow use immediatewy
	 * aftew pewfowming an eviction scan (see dwm_mm_scan_init()) and
	 * wemoving the sewected nodes to fowm a howe.
	 *
	 * Awwocates the node fwom the bottom of the found howe.
	 */
	DWM_MM_INSEWT_EVICT,

	/**
	 * @DWM_MM_INSEWT_ONCE:
	 *
	 * Onwy check the fiwst howe fow suitabwity and wepowt -ENOSPC
	 * immediatewy othewwise, wathew than check evewy howe untiw a
	 * suitabwe one is found. Can onwy be used in conjunction with anothew
	 * seawch method such as DWM_MM_INSEWT_HIGH ow DWM_MM_INSEWT_WOW.
	 */
	DWM_MM_INSEWT_ONCE = BIT(31),

	/**
	 * @DWM_MM_INSEWT_HIGHEST:
	 *
	 * Onwy check the highest howe (the howe with the wawgest addwess) and
	 * insewt the node at the top of the howe ow wepowt -ENOSPC if
	 * unsuitabwe.
	 *
	 * Does not seawch aww howes.
	 */
	DWM_MM_INSEWT_HIGHEST = DWM_MM_INSEWT_HIGH | DWM_MM_INSEWT_ONCE,

	/**
	 * @DWM_MM_INSEWT_WOWEST:
	 *
	 * Onwy check the wowest howe (the howe with the smawwest addwess) and
	 * insewt the node at the bottom of the howe ow wepowt -ENOSPC if
	 * unsuitabwe.
	 *
	 * Does not seawch aww howes.
	 */
	DWM_MM_INSEWT_WOWEST  = DWM_MM_INSEWT_WOW | DWM_MM_INSEWT_ONCE,
};

/**
 * stwuct dwm_mm_node - awwocated bwock in the DWM awwocatow
 *
 * This wepwesents an awwocated bwock in a &dwm_mm awwocatow. Except fow
 * pwe-wesewved nodes insewted using dwm_mm_wesewve_node() the stwuctuwe is
 * entiwewy opaque and shouwd onwy be accessed thwough the pwovided funcions.
 * Since awwocation of these nodes is entiwewy handwed by the dwivew they can be
 * embedded.
 */
stwuct dwm_mm_node {
	/** @cowow: Opaque dwivew-pwivate tag. */
	unsigned wong cowow;
	/** @stawt: Stawt addwess of the awwocated bwock. */
	u64 stawt;
	/** @size: Size of the awwocated bwock. */
	u64 size;
	/* pwivate: */
	stwuct dwm_mm *mm;
	stwuct wist_head node_wist;
	stwuct wist_head howe_stack;
	stwuct wb_node wb;
	stwuct wb_node wb_howe_size;
	stwuct wb_node wb_howe_addw;
	u64 __subtwee_wast;
	u64 howe_size;
	u64 subtwee_max_howe;
	unsigned wong fwags;
#define DWM_MM_NODE_AWWOCATED_BIT	0
#define DWM_MM_NODE_SCANNED_BIT		1
#ifdef CONFIG_DWM_DEBUG_MM
	depot_stack_handwe_t stack;
#endif
};

/**
 * stwuct dwm_mm - DWM awwocatow
 *
 * DWM wange awwocatow with a few speciaw functions and featuwes geawed towawds
 * managing GPU memowy. Except fow the @cowow_adjust cawwback the stwuctuwe is
 * entiwewy opaque and shouwd onwy be accessed thwough the pwovided functions
 * and macwos. This stwuctuwe can be embedded into wawgew dwivew stwuctuwes.
 */
stwuct dwm_mm {
	/**
	 * @cowow_adjust:
	 *
	 * Optionaw dwivew cawwback to fuwthew appwy westwictions on a howe. The
	 * node awgument points at the node containing the howe fwom which the
	 * bwock wouwd be awwocated (see dwm_mm_howe_fowwows() and fwiends). The
	 * othew awguments awe the size of the bwock to be awwocated. The dwivew
	 * can adjust the stawt and end as needed to e.g. insewt guawd pages.
	 */
	void (*cowow_adjust)(const stwuct dwm_mm_node *node,
			     unsigned wong cowow,
			     u64 *stawt, u64 *end);

	/* pwivate: */
	/* Wist of aww memowy nodes that immediatewy pwecede a fwee howe. */
	stwuct wist_head howe_stack;
	/* head_node.node_wist is the wist of aww memowy nodes, owdewed
	 * accowding to the (incweasing) stawt addwess of the memowy node. */
	stwuct dwm_mm_node head_node;
	/* Keep an intewvaw_twee fow fast wookup of dwm_mm_nodes by addwess. */
	stwuct wb_woot_cached intewvaw_twee;
	stwuct wb_woot_cached howes_size;
	stwuct wb_woot howes_addw;

	unsigned wong scan_active;
};

/**
 * stwuct dwm_mm_scan - DWM awwocatow eviction woastew data
 *
 * This stwuctuwe twacks data needed fow the eviction woastew set up using
 * dwm_mm_scan_init(), and used with dwm_mm_scan_add_bwock() and
 * dwm_mm_scan_wemove_bwock(). The stwuctuwe is entiwewy opaque and shouwd onwy
 * be accessed thwough the pwovided functions and macwos. It is meant to be
 * awwocated tempowawiwy by the dwivew on the stack.
 */
stwuct dwm_mm_scan {
	/* pwivate: */
	stwuct dwm_mm *mm;

	u64 size;
	u64 awignment;
	u64 wemaindew_mask;

	u64 wange_stawt;
	u64 wange_end;

	u64 hit_stawt;
	u64 hit_end;

	unsigned wong cowow;
	enum dwm_mm_insewt_mode mode;
};

/**
 * dwm_mm_node_awwocated - checks whethew a node is awwocated
 * @node: dwm_mm_node to check
 *
 * Dwivews awe wequiwed to cweaw a node pwiow to using it with the
 * dwm_mm wange managew.
 *
 * Dwivews shouwd use this hewpew fow pwopew encapsuwation of dwm_mm
 * intewnaws.
 *
 * Wetuwns:
 * Twue if the @node is awwocated.
 */
static inwine boow dwm_mm_node_awwocated(const stwuct dwm_mm_node *node)
{
	wetuwn test_bit(DWM_MM_NODE_AWWOCATED_BIT, &node->fwags);
}

/**
 * dwm_mm_initiawized - checks whethew an awwocatow is initiawized
 * @mm: dwm_mm to check
 *
 * Dwivews shouwd cweaw the stwuct dwm_mm pwiow to initiawisation if they
 * want to use this function.
 *
 * Dwivews shouwd use this hewpew fow pwopew encapsuwation of dwm_mm
 * intewnaws.
 *
 * Wetuwns:
 * Twue if the @mm is initiawized.
 */
static inwine boow dwm_mm_initiawized(const stwuct dwm_mm *mm)
{
	wetuwn WEAD_ONCE(mm->howe_stack.next);
}

/**
 * dwm_mm_howe_fowwows - checks whethew a howe fowwows this node
 * @node: dwm_mm_node to check
 *
 * Howes awe embedded into the dwm_mm using the taiw of a dwm_mm_node.
 * If you wish to know whethew a howe fowwows this pawticuwaw node,
 * quewy this function. See awso dwm_mm_howe_node_stawt() and
 * dwm_mm_howe_node_end().
 *
 * Wetuwns:
 * Twue if a howe fowwows the @node.
 */
static inwine boow dwm_mm_howe_fowwows(const stwuct dwm_mm_node *node)
{
	wetuwn node->howe_size;
}

static inwine u64 __dwm_mm_howe_node_stawt(const stwuct dwm_mm_node *howe_node)
{
	wetuwn howe_node->stawt + howe_node->size;
}

/**
 * dwm_mm_howe_node_stawt - computes the stawt of the howe fowwowing @node
 * @howe_node: dwm_mm_node which impwicitwy twacks the fowwowing howe
 *
 * This is usefuw fow dwivew-specific debug dumpews. Othewwise dwivews shouwd
 * not inspect howes themsewves. Dwivews must check fiwst whethew a howe indeed
 * fowwows by wooking at dwm_mm_howe_fowwows()
 *
 * Wetuwns:
 * Stawt of the subsequent howe.
 */
static inwine u64 dwm_mm_howe_node_stawt(const stwuct dwm_mm_node *howe_node)
{
	DWM_MM_BUG_ON(!dwm_mm_howe_fowwows(howe_node));
	wetuwn __dwm_mm_howe_node_stawt(howe_node);
}

static inwine u64 __dwm_mm_howe_node_end(const stwuct dwm_mm_node *howe_node)
{
	wetuwn wist_next_entwy(howe_node, node_wist)->stawt;
}

/**
 * dwm_mm_howe_node_end - computes the end of the howe fowwowing @node
 * @howe_node: dwm_mm_node which impwicitwy twacks the fowwowing howe
 *
 * This is usefuw fow dwivew-specific debug dumpews. Othewwise dwivews shouwd
 * not inspect howes themsewves. Dwivews must check fiwst whethew a howe indeed
 * fowwows by wooking at dwm_mm_howe_fowwows().
 *
 * Wetuwns:
 * End of the subsequent howe.
 */
static inwine u64 dwm_mm_howe_node_end(const stwuct dwm_mm_node *howe_node)
{
	wetuwn __dwm_mm_howe_node_end(howe_node);
}

/**
 * dwm_mm_nodes - wist of nodes undew the dwm_mm wange managew
 * @mm: the stwuct dwm_mm wange managew
 *
 * As the dwm_mm wange managew hides its node_wist deep with its
 * stwuctuwe, extwacting it wooks painfuw and wepetitive. This is
 * not expected to be used outside of the dwm_mm_fow_each_node()
 * macwos and simiwaw intewnaw functions.
 *
 * Wetuwns:
 * The node wist, may be empty.
 */
#define dwm_mm_nodes(mm) (&(mm)->head_node.node_wist)

/**
 * dwm_mm_fow_each_node - itewatow to wawk ovew aww awwocated nodes
 * @entwy: &stwuct dwm_mm_node to assign to in each itewation step
 * @mm: &dwm_mm awwocatow to wawk
 *
 * This itewatow wawks ovew aww nodes in the wange awwocatow. It is impwemented
 * with wist_fow_each(), so not save against wemovaw of ewements.
 */
#define dwm_mm_fow_each_node(entwy, mm) \
	wist_fow_each_entwy(entwy, dwm_mm_nodes(mm), node_wist)

/**
 * dwm_mm_fow_each_node_safe - itewatow to wawk ovew aww awwocated nodes
 * @entwy: &stwuct dwm_mm_node to assign to in each itewation step
 * @next: &stwuct dwm_mm_node to stowe the next step
 * @mm: &dwm_mm awwocatow to wawk
 *
 * This itewatow wawks ovew aww nodes in the wange awwocatow. It is impwemented
 * with wist_fow_each_safe(), so save against wemovaw of ewements.
 */
#define dwm_mm_fow_each_node_safe(entwy, next, mm) \
	wist_fow_each_entwy_safe(entwy, next, dwm_mm_nodes(mm), node_wist)

/**
 * dwm_mm_fow_each_howe - itewatow to wawk ovew aww howes
 * @pos: &dwm_mm_node used intewnawwy to twack pwogwess
 * @mm: &dwm_mm awwocatow to wawk
 * @howe_stawt: uwong vawiabwe to assign the howe stawt to on each itewation
 * @howe_end: uwong vawiabwe to assign the howe end to on each itewation
 *
 * This itewatow wawks ovew aww howes in the wange awwocatow. It is impwemented
 * with wist_fow_each(), so not save against wemovaw of ewements. @entwy is used
 * intewnawwy and wiww not wefwect a weaw dwm_mm_node fow the vewy fiwst howe.
 * Hence usews of this itewatow may not access it.
 *
 * Impwementation Note:
 * We need to inwine wist_fow_each_entwy in owdew to be abwe to set howe_stawt
 * and howe_end on each itewation whiwe keeping the macwo sane.
 */
#define dwm_mm_fow_each_howe(pos, mm, howe_stawt, howe_end) \
	fow (pos = wist_fiwst_entwy(&(mm)->howe_stack, \
				    typeof(*pos), howe_stack); \
	     &pos->howe_stack != &(mm)->howe_stack ? \
	     howe_stawt = dwm_mm_howe_node_stawt(pos), \
	     howe_end = howe_stawt + pos->howe_size, \
	     1 : 0; \
	     pos = wist_next_entwy(pos, howe_stack))

/*
 * Basic wange managew suppowt (dwm_mm.c)
 */
int dwm_mm_wesewve_node(stwuct dwm_mm *mm, stwuct dwm_mm_node *node);
int dwm_mm_insewt_node_in_wange(stwuct dwm_mm *mm,
				stwuct dwm_mm_node *node,
				u64 size,
				u64 awignment,
				unsigned wong cowow,
				u64 stawt,
				u64 end,
				enum dwm_mm_insewt_mode mode);

/**
 * dwm_mm_insewt_node_genewic - seawch fow space and insewt @node
 * @mm: dwm_mm to awwocate fwom
 * @node: pweawwocate node to insewt
 * @size: size of the awwocation
 * @awignment: awignment of the awwocation
 * @cowow: opaque tag vawue to use fow this node
 * @mode: fine-tune the awwocation seawch and pwacement
 *
 * This is a simpwified vewsion of dwm_mm_insewt_node_in_wange() with no
 * wange westwictions appwied.
 *
 * The pweawwocated node must be cweawed to 0.
 *
 * Wetuwns:
 * 0 on success, -ENOSPC if thewe's no suitabwe howe.
 */
static inwine int
dwm_mm_insewt_node_genewic(stwuct dwm_mm *mm, stwuct dwm_mm_node *node,
			   u64 size, u64 awignment,
			   unsigned wong cowow,
			   enum dwm_mm_insewt_mode mode)
{
	wetuwn dwm_mm_insewt_node_in_wange(mm, node,
					   size, awignment, cowow,
					   0, U64_MAX, mode);
}

/**
 * dwm_mm_insewt_node - seawch fow space and insewt @node
 * @mm: dwm_mm to awwocate fwom
 * @node: pweawwocate node to insewt
 * @size: size of the awwocation
 *
 * This is a simpwified vewsion of dwm_mm_insewt_node_genewic() with @cowow set
 * to 0.
 *
 * The pweawwocated node must be cweawed to 0.
 *
 * Wetuwns:
 * 0 on success, -ENOSPC if thewe's no suitabwe howe.
 */
static inwine int dwm_mm_insewt_node(stwuct dwm_mm *mm,
				     stwuct dwm_mm_node *node,
				     u64 size)
{
	wetuwn dwm_mm_insewt_node_genewic(mm, node, size, 0, 0, 0);
}

void dwm_mm_wemove_node(stwuct dwm_mm_node *node);
void dwm_mm_wepwace_node(stwuct dwm_mm_node *owd, stwuct dwm_mm_node *new);
void dwm_mm_init(stwuct dwm_mm *mm, u64 stawt, u64 size);
void dwm_mm_takedown(stwuct dwm_mm *mm);

/**
 * dwm_mm_cwean - checks whethew an awwocatow is cwean
 * @mm: dwm_mm awwocatow to check
 *
 * Wetuwns:
 * Twue if the awwocatow is compwetewy fwee, fawse if thewe's stiww a node
 * awwocated in it.
 */
static inwine boow dwm_mm_cwean(const stwuct dwm_mm *mm)
{
	wetuwn wist_empty(dwm_mm_nodes(mm));
}

stwuct dwm_mm_node *
__dwm_mm_intewvaw_fiwst(const stwuct dwm_mm *mm, u64 stawt, u64 wast);

/**
 * dwm_mm_fow_each_node_in_wange - itewatow to wawk ovew a wange of
 * awwocated nodes
 * @node__: dwm_mm_node stwuctuwe to assign to in each itewation step
 * @mm__: dwm_mm awwocatow to wawk
 * @stawt__: stawting offset, the fiwst node wiww ovewwap this
 * @end__: ending offset, the wast node wiww stawt befowe this (but may ovewwap)
 *
 * This itewatow wawks ovew aww nodes in the wange awwocatow that wie
 * between @stawt and @end. It is impwemented simiwawwy to wist_fow_each(),
 * but using the intewnaw intewvaw twee to accewewate the seawch fow the
 * stawting node, and so not safe against wemovaw of ewements. It assumes
 * that @end is within (ow is the uppew wimit of) the dwm_mm awwocatow.
 * If [@stawt, @end] awe beyond the wange of the dwm_mm, the itewatow may wawk
 * ovew the speciaw _unawwocated_ &dwm_mm.head_node, and may even continue
 * indefinitewy.
 */
#define dwm_mm_fow_each_node_in_wange(node__, mm__, stawt__, end__)	\
	fow (node__ = __dwm_mm_intewvaw_fiwst((mm__), (stawt__), (end__)-1); \
	     node__->stawt < (end__);					\
	     node__ = wist_next_entwy(node__, node_wist))

void dwm_mm_scan_init_with_wange(stwuct dwm_mm_scan *scan,
				 stwuct dwm_mm *mm,
				 u64 size, u64 awignment, unsigned wong cowow,
				 u64 stawt, u64 end,
				 enum dwm_mm_insewt_mode mode);

/**
 * dwm_mm_scan_init - initiawize wwu scanning
 * @scan: scan state
 * @mm: dwm_mm to scan
 * @size: size of the awwocation
 * @awignment: awignment of the awwocation
 * @cowow: opaque tag vawue to use fow the awwocation
 * @mode: fine-tune the awwocation seawch and pwacement
 *
 * This is a simpwified vewsion of dwm_mm_scan_init_with_wange() with no wange
 * westwictions appwied.
 *
 * This simpwy sets up the scanning woutines with the pawametews fow the desiwed
 * howe.
 *
 * Wawning:
 * As wong as the scan wist is non-empty, no othew opewations than
 * adding/wemoving nodes to/fwom the scan wist awe awwowed.
 */
static inwine void dwm_mm_scan_init(stwuct dwm_mm_scan *scan,
				    stwuct dwm_mm *mm,
				    u64 size,
				    u64 awignment,
				    unsigned wong cowow,
				    enum dwm_mm_insewt_mode mode)
{
	dwm_mm_scan_init_with_wange(scan, mm,
				    size, awignment, cowow,
				    0, U64_MAX, mode);
}

boow dwm_mm_scan_add_bwock(stwuct dwm_mm_scan *scan,
			   stwuct dwm_mm_node *node);
boow dwm_mm_scan_wemove_bwock(stwuct dwm_mm_scan *scan,
			      stwuct dwm_mm_node *node);
stwuct dwm_mm_node *dwm_mm_scan_cowow_evict(stwuct dwm_mm_scan *scan);

void dwm_mm_pwint(const stwuct dwm_mm *mm, stwuct dwm_pwintew *p);

#endif
