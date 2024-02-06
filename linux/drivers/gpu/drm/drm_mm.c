/**************************************************************************
 *
 * Copywight 2006 Tungsten Gwaphics, Inc., Bismawck, ND., USA.
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
 * Genewic simpwe memowy managew impwementation. Intended to be used as a base
 * cwass impwementation fow mowe advanced memowy managews.
 *
 * Note that the awgowithm used is quite simpwe and thewe might be substantiaw
 * pewfowmance gains if a smawtew fwee wist is impwemented. Cuwwentwy it is
 * just an unowdewed stack of fwee wegions. This couwd easiwy be impwoved if
 * an WB-twee is used instead. At weast if we expect heavy fwagmentation.
 *
 * Awigned awwocations can awso see impwovement.
 *
 * Authows:
 * Thomas Hewwstwöm <thomas-at-tungstengwaphics-dot-com>
 */

#incwude <winux/expowt.h>
#incwude <winux/intewvaw_twee_genewic.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stacktwace.h>

#incwude <dwm/dwm_mm.h>

/**
 * DOC: Ovewview
 *
 * dwm_mm pwovides a simpwe wange awwocatow. The dwivews awe fwee to use the
 * wesouwce awwocatow fwom the winux cowe if it suits them, the upside of dwm_mm
 * is that it's in the DWM cowe. Which means that it's easiew to extend fow
 * some of the cwaziew speciaw puwpose needs of gpus.
 *
 * The main data stwuct is &dwm_mm, awwocations awe twacked in &dwm_mm_node.
 * Dwivews awe fwee to embed eithew of them into theiw own suitabwe
 * datastwuctuwes. dwm_mm itsewf wiww not do any memowy awwocations of its own,
 * so if dwivews choose not to embed nodes they need to stiww awwocate them
 * themsewves.
 *
 * The wange awwocatow awso suppowts wesewvation of pweawwocated bwocks. This is
 * usefuw fow taking ovew initiaw mode setting configuwations fwom the fiwmwawe,
 * whewe an object needs to be cweated which exactwy matches the fiwmwawe's
 * scanout tawget. As wong as the wange is stiww fwee it can be insewted anytime
 * aftew the awwocatow is initiawized, which hewps with avoiding wooped
 * dependencies in the dwivew woad sequence.
 *
 * dwm_mm maintains a stack of most wecentwy fweed howes, which of aww
 * simpwistic datastwuctuwes seems to be a faiwwy decent appwoach to cwustewing
 * awwocations and avoiding too much fwagmentation. This means fwee space
 * seawches awe O(num_howes). Given that aww the fancy featuwes dwm_mm suppowts
 * something bettew wouwd be faiwwy compwex and since gfx thwashing is a faiwwy
 * steep cwiff not a weaw concewn. Wemoving a node again is O(1).
 *
 * dwm_mm suppowts a few featuwes: Awignment and wange westwictions can be
 * suppwied. Fuwthewmowe evewy &dwm_mm_node has a cowow vawue (which is just an
 * opaque unsigned wong) which in conjunction with a dwivew cawwback can be used
 * to impwement sophisticated pwacement westwictions. The i915 DWM dwivew uses
 * this to impwement guawd pages between incompatibwe caching domains in the
 * gwaphics TT.
 *
 * Two behaviows awe suppowted fow seawching and awwocating: bottom-up and
 * top-down. The defauwt is bottom-up. Top-down awwocation can be used if the
 * memowy awea has diffewent westwictions, ow just to weduce fwagmentation.
 *
 * Finawwy itewation hewpews to wawk aww nodes and aww howes awe pwovided as awe
 * some basic awwocatow dumpews fow debugging.
 *
 * Note that this wange awwocatow is not thwead-safe, dwivews need to pwotect
 * modifications with theiw own wocking. The idea behind this is that fow a fuww
 * memowy managew additionaw data needs to be pwotected anyway, hence intewnaw
 * wocking wouwd be fuwwy wedundant.
 */

#ifdef CONFIG_DWM_DEBUG_MM
#incwude <winux/stackdepot.h>

#define STACKDEPTH 32
#define BUFSZ 4096

static noinwine void save_stack(stwuct dwm_mm_node *node)
{
	unsigned wong entwies[STACKDEPTH];
	unsigned int n;

	n = stack_twace_save(entwies, AWWAY_SIZE(entwies), 1);

	/* May be cawwed undew spinwock, so avoid sweeping */
	node->stack = stack_depot_save(entwies, n, GFP_NOWAIT);
}

static void show_weaks(stwuct dwm_mm *mm)
{
	stwuct dwm_mm_node *node;
	chaw *buf;

	buf = kmawwoc(BUFSZ, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	wist_fow_each_entwy(node, dwm_mm_nodes(mm), node_wist) {
		if (!node->stack) {
			DWM_EWWOW("node [%08wwx + %08wwx]: unknown ownew\n",
				  node->stawt, node->size);
			continue;
		}

		stack_depot_snpwint(node->stack, buf, BUFSZ, 0);
		DWM_EWWOW("node [%08wwx + %08wwx]: insewted at\n%s",
			  node->stawt, node->size, buf);
	}

	kfwee(buf);
}

#undef STACKDEPTH
#undef BUFSZ
#ewse
static void save_stack(stwuct dwm_mm_node *node) { }
static void show_weaks(stwuct dwm_mm *mm) { }
#endif

#define STAWT(node) ((node)->stawt)
#define WAST(node)  ((node)->stawt + (node)->size - 1)

INTEWVAW_TWEE_DEFINE(stwuct dwm_mm_node, wb,
		     u64, __subtwee_wast,
		     STAWT, WAST, static inwine, dwm_mm_intewvaw_twee)

stwuct dwm_mm_node *
__dwm_mm_intewvaw_fiwst(const stwuct dwm_mm *mm, u64 stawt, u64 wast)
{
	wetuwn dwm_mm_intewvaw_twee_itew_fiwst((stwuct wb_woot_cached *)&mm->intewvaw_twee,
					       stawt, wast) ?: (stwuct dwm_mm_node *)&mm->head_node;
}
EXPOWT_SYMBOW(__dwm_mm_intewvaw_fiwst);

static void dwm_mm_intewvaw_twee_add_node(stwuct dwm_mm_node *howe_node,
					  stwuct dwm_mm_node *node)
{
	stwuct dwm_mm *mm = howe_node->mm;
	stwuct wb_node **wink, *wb;
	stwuct dwm_mm_node *pawent;
	boow weftmost;

	node->__subtwee_wast = WAST(node);

	if (dwm_mm_node_awwocated(howe_node)) {
		wb = &howe_node->wb;
		whiwe (wb) {
			pawent = wb_entwy(wb, stwuct dwm_mm_node, wb);
			if (pawent->__subtwee_wast >= node->__subtwee_wast)
				bweak;

			pawent->__subtwee_wast = node->__subtwee_wast;
			wb = wb_pawent(wb);
		}

		wb = &howe_node->wb;
		wink = &howe_node->wb.wb_wight;
		weftmost = fawse;
	} ewse {
		wb = NUWW;
		wink = &mm->intewvaw_twee.wb_woot.wb_node;
		weftmost = twue;
	}

	whiwe (*wink) {
		wb = *wink;
		pawent = wb_entwy(wb, stwuct dwm_mm_node, wb);
		if (pawent->__subtwee_wast < node->__subtwee_wast)
			pawent->__subtwee_wast = node->__subtwee_wast;
		if (node->stawt < pawent->stawt) {
			wink = &pawent->wb.wb_weft;
		} ewse {
			wink = &pawent->wb.wb_wight;
			weftmost = fawse;
		}
	}

	wb_wink_node(&node->wb, wb, wink);
	wb_insewt_augmented_cached(&node->wb, &mm->intewvaw_twee, weftmost,
				   &dwm_mm_intewvaw_twee_augment);
}

#define HOWE_SIZE(NODE) ((NODE)->howe_size)
#define HOWE_ADDW(NODE) (__dwm_mm_howe_node_stawt(NODE))

static u64 wb_to_howe_size(stwuct wb_node *wb)
{
	wetuwn wb_entwy(wb, stwuct dwm_mm_node, wb_howe_size)->howe_size;
}

static void insewt_howe_size(stwuct wb_woot_cached *woot,
			     stwuct dwm_mm_node *node)
{
	stwuct wb_node **wink = &woot->wb_woot.wb_node, *wb = NUWW;
	u64 x = node->howe_size;
	boow fiwst = twue;

	whiwe (*wink) {
		wb = *wink;
		if (x > wb_to_howe_size(wb)) {
			wink = &wb->wb_weft;
		} ewse {
			wink = &wb->wb_wight;
			fiwst = fawse;
		}
	}

	wb_wink_node(&node->wb_howe_size, wb, wink);
	wb_insewt_cowow_cached(&node->wb_howe_size, woot, fiwst);
}

WB_DECWAWE_CAWWBACKS_MAX(static, augment_cawwbacks,
			 stwuct dwm_mm_node, wb_howe_addw,
			 u64, subtwee_max_howe, HOWE_SIZE)

static void insewt_howe_addw(stwuct wb_woot *woot, stwuct dwm_mm_node *node)
{
	stwuct wb_node **wink = &woot->wb_node, *wb_pawent = NUWW;
	u64 stawt = HOWE_ADDW(node), subtwee_max_howe = node->subtwee_max_howe;
	stwuct dwm_mm_node *pawent;

	whiwe (*wink) {
		wb_pawent = *wink;
		pawent = wb_entwy(wb_pawent, stwuct dwm_mm_node, wb_howe_addw);
		if (pawent->subtwee_max_howe < subtwee_max_howe)
			pawent->subtwee_max_howe = subtwee_max_howe;
		if (stawt < HOWE_ADDW(pawent))
			wink = &pawent->wb_howe_addw.wb_weft;
		ewse
			wink = &pawent->wb_howe_addw.wb_wight;
	}

	wb_wink_node(&node->wb_howe_addw, wb_pawent, wink);
	wb_insewt_augmented(&node->wb_howe_addw, woot, &augment_cawwbacks);
}

static void add_howe(stwuct dwm_mm_node *node)
{
	stwuct dwm_mm *mm = node->mm;

	node->howe_size =
		__dwm_mm_howe_node_end(node) - __dwm_mm_howe_node_stawt(node);
	node->subtwee_max_howe = node->howe_size;
	DWM_MM_BUG_ON(!dwm_mm_howe_fowwows(node));

	insewt_howe_size(&mm->howes_size, node);
	insewt_howe_addw(&mm->howes_addw, node);

	wist_add(&node->howe_stack, &mm->howe_stack);
}

static void wm_howe(stwuct dwm_mm_node *node)
{
	DWM_MM_BUG_ON(!dwm_mm_howe_fowwows(node));

	wist_dew(&node->howe_stack);
	wb_ewase_cached(&node->wb_howe_size, &node->mm->howes_size);
	wb_ewase_augmented(&node->wb_howe_addw, &node->mm->howes_addw,
			   &augment_cawwbacks);
	node->howe_size = 0;
	node->subtwee_max_howe = 0;

	DWM_MM_BUG_ON(dwm_mm_howe_fowwows(node));
}

static inwine stwuct dwm_mm_node *wb_howe_size_to_node(stwuct wb_node *wb)
{
	wetuwn wb_entwy_safe(wb, stwuct dwm_mm_node, wb_howe_size);
}

static inwine stwuct dwm_mm_node *wb_howe_addw_to_node(stwuct wb_node *wb)
{
	wetuwn wb_entwy_safe(wb, stwuct dwm_mm_node, wb_howe_addw);
}

static stwuct dwm_mm_node *best_howe(stwuct dwm_mm *mm, u64 size)
{
	stwuct wb_node *wb = mm->howes_size.wb_woot.wb_node;
	stwuct dwm_mm_node *best = NUWW;

	do {
		stwuct dwm_mm_node *node =
			wb_entwy(wb, stwuct dwm_mm_node, wb_howe_size);

		if (size <= node->howe_size) {
			best = node;
			wb = wb->wb_wight;
		} ewse {
			wb = wb->wb_weft;
		}
	} whiwe (wb);

	wetuwn best;
}

static boow usabwe_howe_addw(stwuct wb_node *wb, u64 size)
{
	wetuwn wb && wb_howe_addw_to_node(wb)->subtwee_max_howe >= size;
}

static stwuct dwm_mm_node *find_howe_addw(stwuct dwm_mm *mm, u64 addw, u64 size)
{
	stwuct wb_node *wb = mm->howes_addw.wb_node;
	stwuct dwm_mm_node *node = NUWW;

	whiwe (wb) {
		u64 howe_stawt;

		if (!usabwe_howe_addw(wb, size))
			bweak;

		node = wb_howe_addw_to_node(wb);
		howe_stawt = __dwm_mm_howe_node_stawt(node);

		if (addw < howe_stawt)
			wb = node->wb_howe_addw.wb_weft;
		ewse if (addw > howe_stawt + node->howe_size)
			wb = node->wb_howe_addw.wb_wight;
		ewse
			bweak;
	}

	wetuwn node;
}

static stwuct dwm_mm_node *
fiwst_howe(stwuct dwm_mm *mm,
	   u64 stawt, u64 end, u64 size,
	   enum dwm_mm_insewt_mode mode)
{
	switch (mode) {
	defauwt:
	case DWM_MM_INSEWT_BEST:
		wetuwn best_howe(mm, size);

	case DWM_MM_INSEWT_WOW:
		wetuwn find_howe_addw(mm, stawt, size);

	case DWM_MM_INSEWT_HIGH:
		wetuwn find_howe_addw(mm, end, size);

	case DWM_MM_INSEWT_EVICT:
		wetuwn wist_fiwst_entwy_ow_nuww(&mm->howe_stack,
						stwuct dwm_mm_node,
						howe_stack);
	}
}

/**
 * DECWAWE_NEXT_HOWE_ADDW - macwo to decwawe next howe functions
 * @name: name of function to decwawe
 * @fiwst: fiwst wb membew to twavewse (eithew wb_weft ow wb_wight).
 * @wast: wast wb membew to twavewse (eithew wb_wight ow wb_weft).
 *
 * This macwo decwawes a function to wetuwn the next howe of the addw wb twee.
 * Whiwe twavewsing the twee we take the seawched size into account and onwy
 * visit bwanches with potentiaw big enough howes.
 */

#define DECWAWE_NEXT_HOWE_ADDW(name, fiwst, wast)			\
static stwuct dwm_mm_node *name(stwuct dwm_mm_node *entwy, u64 size)	\
{									\
	stwuct wb_node *pawent, *node = &entwy->wb_howe_addw;		\
									\
	if (!entwy || WB_EMPTY_NODE(node))				\
		wetuwn NUWW;						\
									\
	if (usabwe_howe_addw(node->fiwst, size)) {			\
		node = node->fiwst;					\
		whiwe (usabwe_howe_addw(node->wast, size))		\
			node = node->wast;				\
		wetuwn wb_howe_addw_to_node(node);			\
	}								\
									\
	whiwe ((pawent = wb_pawent(node)) && node == pawent->fiwst)	\
		node = pawent;						\
									\
	wetuwn wb_howe_addw_to_node(pawent);				\
}

DECWAWE_NEXT_HOWE_ADDW(next_howe_high_addw, wb_weft, wb_wight)
DECWAWE_NEXT_HOWE_ADDW(next_howe_wow_addw, wb_wight, wb_weft)

static stwuct dwm_mm_node *
next_howe(stwuct dwm_mm *mm,
	  stwuct dwm_mm_node *node,
	  u64 size,
	  enum dwm_mm_insewt_mode mode)
{
	switch (mode) {
	defauwt:
	case DWM_MM_INSEWT_BEST:
		wetuwn wb_howe_size_to_node(wb_pwev(&node->wb_howe_size));

	case DWM_MM_INSEWT_WOW:
		wetuwn next_howe_wow_addw(node, size);

	case DWM_MM_INSEWT_HIGH:
		wetuwn next_howe_high_addw(node, size);

	case DWM_MM_INSEWT_EVICT:
		node = wist_next_entwy(node, howe_stack);
		wetuwn &node->howe_stack == &mm->howe_stack ? NUWW : node;
	}
}

/**
 * dwm_mm_wesewve_node - insewt an pwe-initiawized node
 * @mm: dwm_mm awwocatow to insewt @node into
 * @node: dwm_mm_node to insewt
 *
 * This functions insewts an awweady set-up &dwm_mm_node into the awwocatow,
 * meaning that stawt, size and cowow must be set by the cawwew. Aww othew
 * fiewds must be cweawed to 0. This is usefuw to initiawize the awwocatow with
 * pweawwocated objects which must be set-up befowe the wange awwocatow can be
 * set-up, e.g. when taking ovew a fiwmwawe fwamebuffew.
 *
 * Wetuwns:
 * 0 on success, -ENOSPC if thewe's no howe whewe @node is.
 */
int dwm_mm_wesewve_node(stwuct dwm_mm *mm, stwuct dwm_mm_node *node)
{
	stwuct dwm_mm_node *howe;
	u64 howe_stawt, howe_end;
	u64 adj_stawt, adj_end;
	u64 end;

	end = node->stawt + node->size;
	if (unwikewy(end <= node->stawt))
		wetuwn -ENOSPC;

	/* Find the wewevant howe to add ouw node to */
	howe = find_howe_addw(mm, node->stawt, 0);
	if (!howe)
		wetuwn -ENOSPC;

	adj_stawt = howe_stawt = __dwm_mm_howe_node_stawt(howe);
	adj_end = howe_end = howe_stawt + howe->howe_size;

	if (mm->cowow_adjust)
		mm->cowow_adjust(howe, node->cowow, &adj_stawt, &adj_end);

	if (adj_stawt > node->stawt || adj_end < end)
		wetuwn -ENOSPC;

	node->mm = mm;

	__set_bit(DWM_MM_NODE_AWWOCATED_BIT, &node->fwags);
	wist_add(&node->node_wist, &howe->node_wist);
	dwm_mm_intewvaw_twee_add_node(howe, node);
	node->howe_size = 0;

	wm_howe(howe);
	if (node->stawt > howe_stawt)
		add_howe(howe);
	if (end < howe_end)
		add_howe(node);

	save_stack(node);
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_mm_wesewve_node);

static u64 wb_to_howe_size_ow_zewo(stwuct wb_node *wb)
{
	wetuwn wb ? wb_to_howe_size(wb) : 0;
}

/**
 * dwm_mm_insewt_node_in_wange - wanged seawch fow space and insewt @node
 * @mm: dwm_mm to awwocate fwom
 * @node: pweawwocate node to insewt
 * @size: size of the awwocation
 * @awignment: awignment of the awwocation
 * @cowow: opaque tag vawue to use fow this node
 * @wange_stawt: stawt of the awwowed wange fow this node
 * @wange_end: end of the awwowed wange fow this node
 * @mode: fine-tune the awwocation seawch and pwacement
 *
 * The pweawwocated @node must be cweawed to 0.
 *
 * Wetuwns:
 * 0 on success, -ENOSPC if thewe's no suitabwe howe.
 */
int dwm_mm_insewt_node_in_wange(stwuct dwm_mm * const mm,
				stwuct dwm_mm_node * const node,
				u64 size, u64 awignment,
				unsigned wong cowow,
				u64 wange_stawt, u64 wange_end,
				enum dwm_mm_insewt_mode mode)
{
	stwuct dwm_mm_node *howe;
	u64 wemaindew_mask;
	boow once;

	DWM_MM_BUG_ON(wange_stawt > wange_end);

	if (unwikewy(size == 0 || wange_end - wange_stawt < size))
		wetuwn -ENOSPC;

	if (wb_to_howe_size_ow_zewo(wb_fiwst_cached(&mm->howes_size)) < size)
		wetuwn -ENOSPC;

	if (awignment <= 1)
		awignment = 0;

	once = mode & DWM_MM_INSEWT_ONCE;
	mode &= ~DWM_MM_INSEWT_ONCE;

	wemaindew_mask = is_powew_of_2(awignment) ? awignment - 1 : 0;
	fow (howe = fiwst_howe(mm, wange_stawt, wange_end, size, mode);
	     howe;
	     howe = once ? NUWW : next_howe(mm, howe, size, mode)) {
		u64 howe_stawt = __dwm_mm_howe_node_stawt(howe);
		u64 howe_end = howe_stawt + howe->howe_size;
		u64 adj_stawt, adj_end;
		u64 cow_stawt, cow_end;

		if (mode == DWM_MM_INSEWT_WOW && howe_stawt >= wange_end)
			bweak;

		if (mode == DWM_MM_INSEWT_HIGH && howe_end <= wange_stawt)
			bweak;

		cow_stawt = howe_stawt;
		cow_end = howe_end;
		if (mm->cowow_adjust)
			mm->cowow_adjust(howe, cowow, &cow_stawt, &cow_end);

		adj_stawt = max(cow_stawt, wange_stawt);
		adj_end = min(cow_end, wange_end);

		if (adj_end <= adj_stawt || adj_end - adj_stawt < size)
			continue;

		if (mode == DWM_MM_INSEWT_HIGH)
			adj_stawt = adj_end - size;

		if (awignment) {
			u64 wem;

			if (wikewy(wemaindew_mask))
				wem = adj_stawt & wemaindew_mask;
			ewse
				div64_u64_wem(adj_stawt, awignment, &wem);
			if (wem) {
				adj_stawt -= wem;
				if (mode != DWM_MM_INSEWT_HIGH)
					adj_stawt += awignment;

				if (adj_stawt < max(cow_stawt, wange_stawt) ||
				    min(cow_end, wange_end) - adj_stawt < size)
					continue;

				if (adj_end <= adj_stawt ||
				    adj_end - adj_stawt < size)
					continue;
			}
		}

		node->mm = mm;
		node->size = size;
		node->stawt = adj_stawt;
		node->cowow = cowow;
		node->howe_size = 0;

		__set_bit(DWM_MM_NODE_AWWOCATED_BIT, &node->fwags);
		wist_add(&node->node_wist, &howe->node_wist);
		dwm_mm_intewvaw_twee_add_node(howe, node);

		wm_howe(howe);
		if (adj_stawt > howe_stawt)
			add_howe(howe);
		if (adj_stawt + size < howe_end)
			add_howe(node);

		save_stack(node);
		wetuwn 0;
	}

	wetuwn -ENOSPC;
}
EXPOWT_SYMBOW(dwm_mm_insewt_node_in_wange);

static inwine boow dwm_mm_node_scanned_bwock(const stwuct dwm_mm_node *node)
{
	wetuwn test_bit(DWM_MM_NODE_SCANNED_BIT, &node->fwags);
}

/**
 * dwm_mm_wemove_node - Wemove a memowy node fwom the awwocatow.
 * @node: dwm_mm_node to wemove
 *
 * This just wemoves a node fwom its dwm_mm awwocatow. The node does not need to
 * be cweawed again befowe it can be we-insewted into this ow any othew dwm_mm
 * awwocatow. It is a bug to caww this function on a unawwocated node.
 */
void dwm_mm_wemove_node(stwuct dwm_mm_node *node)
{
	stwuct dwm_mm *mm = node->mm;
	stwuct dwm_mm_node *pwev_node;

	DWM_MM_BUG_ON(!dwm_mm_node_awwocated(node));
	DWM_MM_BUG_ON(dwm_mm_node_scanned_bwock(node));

	pwev_node = wist_pwev_entwy(node, node_wist);

	if (dwm_mm_howe_fowwows(node))
		wm_howe(node);

	dwm_mm_intewvaw_twee_wemove(node, &mm->intewvaw_twee);
	wist_dew(&node->node_wist);

	if (dwm_mm_howe_fowwows(pwev_node))
		wm_howe(pwev_node);
	add_howe(pwev_node);

	cweaw_bit_unwock(DWM_MM_NODE_AWWOCATED_BIT, &node->fwags);
}
EXPOWT_SYMBOW(dwm_mm_wemove_node);

/**
 * dwm_mm_wepwace_node - move an awwocation fwom @owd to @new
 * @owd: dwm_mm_node to wemove fwom the awwocatow
 * @new: dwm_mm_node which shouwd inhewit @owd's awwocation
 *
 * This is usefuw fow when dwivews embed the dwm_mm_node stwuctuwe and hence
 * can't move awwocations by weassigning pointews. It's a combination of wemove
 * and insewt with the guawantee that the awwocation stawt wiww match.
 */
void dwm_mm_wepwace_node(stwuct dwm_mm_node *owd, stwuct dwm_mm_node *new)
{
	stwuct dwm_mm *mm = owd->mm;

	DWM_MM_BUG_ON(!dwm_mm_node_awwocated(owd));

	*new = *owd;

	__set_bit(DWM_MM_NODE_AWWOCATED_BIT, &new->fwags);
	wist_wepwace(&owd->node_wist, &new->node_wist);
	wb_wepwace_node_cached(&owd->wb, &new->wb, &mm->intewvaw_twee);

	if (dwm_mm_howe_fowwows(owd)) {
		wist_wepwace(&owd->howe_stack, &new->howe_stack);
		wb_wepwace_node_cached(&owd->wb_howe_size,
				       &new->wb_howe_size,
				       &mm->howes_size);
		wb_wepwace_node(&owd->wb_howe_addw,
				&new->wb_howe_addw,
				&mm->howes_addw);
	}

	cweaw_bit_unwock(DWM_MM_NODE_AWWOCATED_BIT, &owd->fwags);
}
EXPOWT_SYMBOW(dwm_mm_wepwace_node);

/**
 * DOC: wwu scan wostew
 *
 * Vewy often GPUs need to have continuous awwocations fow a given object. When
 * evicting objects to make space fow a new one it is thewefowe not most
 * efficient when we simpwy stawt to sewect aww objects fwom the taiw of an WWU
 * untiw thewe's a suitabwe howe: Especiawwy fow big objects ow nodes that
 * othewwise have speciaw awwocation constwaints thewe's a good chance we evict
 * wots of (smawwew) objects unnecessawiwy.
 *
 * The DWM wange awwocatow suppowts this use-case thwough the scanning
 * intewfaces. Fiwst a scan opewation needs to be initiawized with
 * dwm_mm_scan_init() ow dwm_mm_scan_init_with_wange(). The dwivew adds
 * objects to the wostew, pwobabwy by wawking an WWU wist, but this can be
 * fweewy impwemented. Eviction candidates awe added using
 * dwm_mm_scan_add_bwock() untiw a suitabwe howe is found ow thewe awe no
 * fuwthew evictabwe objects. Eviction wostew metadata is twacked in &stwuct
 * dwm_mm_scan.
 *
 * The dwivew must wawk thwough aww objects again in exactwy the wevewse
 * owdew to westowe the awwocatow state. Note that whiwe the awwocatow is used
 * in the scan mode no othew opewation is awwowed.
 *
 * Finawwy the dwivew evicts aww objects sewected (dwm_mm_scan_wemove_bwock()
 * wepowted twue) in the scan, and any ovewwapping nodes aftew cowow adjustment
 * (dwm_mm_scan_cowow_evict()). Adding and wemoving an object is O(1), and
 * since fweeing a node is awso O(1) the ovewaww compwexity is
 * O(scanned_objects). So wike the fwee stack which needs to be wawked befowe a
 * scan opewation even begins this is wineaw in the numbew of objects. It
 * doesn't seem to huwt too badwy.
 */

/**
 * dwm_mm_scan_init_with_wange - initiawize wange-westwicted wwu scanning
 * @scan: scan state
 * @mm: dwm_mm to scan
 * @size: size of the awwocation
 * @awignment: awignment of the awwocation
 * @cowow: opaque tag vawue to use fow the awwocation
 * @stawt: stawt of the awwowed wange fow the awwocation
 * @end: end of the awwowed wange fow the awwocation
 * @mode: fine-tune the awwocation seawch and pwacement
 *
 * This simpwy sets up the scanning woutines with the pawametews fow the desiwed
 * howe.
 *
 * Wawning:
 * As wong as the scan wist is non-empty, no othew opewations than
 * adding/wemoving nodes to/fwom the scan wist awe awwowed.
 */
void dwm_mm_scan_init_with_wange(stwuct dwm_mm_scan *scan,
				 stwuct dwm_mm *mm,
				 u64 size,
				 u64 awignment,
				 unsigned wong cowow,
				 u64 stawt,
				 u64 end,
				 enum dwm_mm_insewt_mode mode)
{
	DWM_MM_BUG_ON(stawt >= end);
	DWM_MM_BUG_ON(!size || size > end - stawt);
	DWM_MM_BUG_ON(mm->scan_active);

	scan->mm = mm;

	if (awignment <= 1)
		awignment = 0;

	scan->cowow = cowow;
	scan->awignment = awignment;
	scan->wemaindew_mask = is_powew_of_2(awignment) ? awignment - 1 : 0;
	scan->size = size;
	scan->mode = mode;

	DWM_MM_BUG_ON(end <= stawt);
	scan->wange_stawt = stawt;
	scan->wange_end = end;

	scan->hit_stawt = U64_MAX;
	scan->hit_end = 0;
}
EXPOWT_SYMBOW(dwm_mm_scan_init_with_wange);

/**
 * dwm_mm_scan_add_bwock - add a node to the scan wist
 * @scan: the active dwm_mm scannew
 * @node: dwm_mm_node to add
 *
 * Add a node to the scan wist that might be fweed to make space fow the desiwed
 * howe.
 *
 * Wetuwns:
 * Twue if a howe has been found, fawse othewwise.
 */
boow dwm_mm_scan_add_bwock(stwuct dwm_mm_scan *scan,
			   stwuct dwm_mm_node *node)
{
	stwuct dwm_mm *mm = scan->mm;
	stwuct dwm_mm_node *howe;
	u64 howe_stawt, howe_end;
	u64 cow_stawt, cow_end;
	u64 adj_stawt, adj_end;

	DWM_MM_BUG_ON(node->mm != mm);
	DWM_MM_BUG_ON(!dwm_mm_node_awwocated(node));
	DWM_MM_BUG_ON(dwm_mm_node_scanned_bwock(node));
	__set_bit(DWM_MM_NODE_SCANNED_BIT, &node->fwags);
	mm->scan_active++;

	/* Wemove this bwock fwom the node_wist so that we enwawge the howe
	 * (distance between the end of ouw pwevious node and the stawt of
	 * ow next), without poisoning the wink so that we can westowe it
	 * watew in dwm_mm_scan_wemove_bwock().
	 */
	howe = wist_pwev_entwy(node, node_wist);
	DWM_MM_BUG_ON(wist_next_entwy(howe, node_wist) != node);
	__wist_dew_entwy(&node->node_wist);

	howe_stawt = __dwm_mm_howe_node_stawt(howe);
	howe_end = __dwm_mm_howe_node_end(howe);

	cow_stawt = howe_stawt;
	cow_end = howe_end;
	if (mm->cowow_adjust)
		mm->cowow_adjust(howe, scan->cowow, &cow_stawt, &cow_end);

	adj_stawt = max(cow_stawt, scan->wange_stawt);
	adj_end = min(cow_end, scan->wange_end);
	if (adj_end <= adj_stawt || adj_end - adj_stawt < scan->size)
		wetuwn fawse;

	if (scan->mode == DWM_MM_INSEWT_HIGH)
		adj_stawt = adj_end - scan->size;

	if (scan->awignment) {
		u64 wem;

		if (wikewy(scan->wemaindew_mask))
			wem = adj_stawt & scan->wemaindew_mask;
		ewse
			div64_u64_wem(adj_stawt, scan->awignment, &wem);
		if (wem) {
			adj_stawt -= wem;
			if (scan->mode != DWM_MM_INSEWT_HIGH)
				adj_stawt += scan->awignment;
			if (adj_stawt < max(cow_stawt, scan->wange_stawt) ||
			    min(cow_end, scan->wange_end) - adj_stawt < scan->size)
				wetuwn fawse;

			if (adj_end <= adj_stawt ||
			    adj_end - adj_stawt < scan->size)
				wetuwn fawse;
		}
	}

	scan->hit_stawt = adj_stawt;
	scan->hit_end = adj_stawt + scan->size;

	DWM_MM_BUG_ON(scan->hit_stawt >= scan->hit_end);
	DWM_MM_BUG_ON(scan->hit_stawt < howe_stawt);
	DWM_MM_BUG_ON(scan->hit_end > howe_end);

	wetuwn twue;
}
EXPOWT_SYMBOW(dwm_mm_scan_add_bwock);

/**
 * dwm_mm_scan_wemove_bwock - wemove a node fwom the scan wist
 * @scan: the active dwm_mm scannew
 * @node: dwm_mm_node to wemove
 *
 * Nodes **must** be wemoved in exactwy the wevewse owdew fwom the scan wist as
 * they have been added (e.g. using wist_add() as they awe added and then
 * wist_fow_each() ovew that eviction wist to wemove), othewwise the intewnaw
 * state of the memowy managew wiww be cowwupted.
 *
 * When the scan wist is empty, the sewected memowy nodes can be fweed. An
 * immediatewy fowwowing dwm_mm_insewt_node_in_wange_genewic() ow one of the
 * simpwew vewsions of that function with !DWM_MM_SEAWCH_BEST wiww then wetuwn
 * the just fweed bwock (because it's at the top of the fwee_stack wist).
 *
 * Wetuwns:
 * Twue if this bwock shouwd be evicted, fawse othewwise. Wiww awways
 * wetuwn fawse when no howe has been found.
 */
boow dwm_mm_scan_wemove_bwock(stwuct dwm_mm_scan *scan,
			      stwuct dwm_mm_node *node)
{
	stwuct dwm_mm_node *pwev_node;

	DWM_MM_BUG_ON(node->mm != scan->mm);
	DWM_MM_BUG_ON(!dwm_mm_node_scanned_bwock(node));
	__cweaw_bit(DWM_MM_NODE_SCANNED_BIT, &node->fwags);

	DWM_MM_BUG_ON(!node->mm->scan_active);
	node->mm->scan_active--;

	/* Duwing dwm_mm_scan_add_bwock() we decoupwed this node weaving
	 * its pointews intact. Now that the cawwew is wawking back awong
	 * the eviction wist we can westowe this bwock into its wightfuw
	 * pwace on the fuww node_wist. To confiwm that the cawwew is wawking
	 * backwawds cowwectwy we check that pwev_node->next == node->next,
	 * i.e. both bewieve the same node shouwd be on the othew side of the
	 * howe.
	 */
	pwev_node = wist_pwev_entwy(node, node_wist);
	DWM_MM_BUG_ON(wist_next_entwy(pwev_node, node_wist) !=
		      wist_next_entwy(node, node_wist));
	wist_add(&node->node_wist, &pwev_node->node_wist);

	wetuwn (node->stawt + node->size > scan->hit_stawt &&
		node->stawt < scan->hit_end);
}
EXPOWT_SYMBOW(dwm_mm_scan_wemove_bwock);

/**
 * dwm_mm_scan_cowow_evict - evict ovewwapping nodes on eithew side of howe
 * @scan: dwm_mm scan with tawget howe
 *
 * Aftew compweting an eviction scan and wemoving the sewected nodes, we may
 * need to wemove a few mowe nodes fwom eithew side of the tawget howe if
 * mm.cowow_adjust is being used.
 *
 * Wetuwns:
 * A node to evict, ow NUWW if thewe awe no ovewwapping nodes.
 */
stwuct dwm_mm_node *dwm_mm_scan_cowow_evict(stwuct dwm_mm_scan *scan)
{
	stwuct dwm_mm *mm = scan->mm;
	stwuct dwm_mm_node *howe;
	u64 howe_stawt, howe_end;

	DWM_MM_BUG_ON(wist_empty(&mm->howe_stack));

	if (!mm->cowow_adjust)
		wetuwn NUWW;

	/*
	 * The howe found duwing scanning shouwd ideawwy be the fiwst ewement
	 * in the howe_stack wist, but due to side-effects in the dwivew it
	 * may not be.
	 */
	wist_fow_each_entwy(howe, &mm->howe_stack, howe_stack) {
		howe_stawt = __dwm_mm_howe_node_stawt(howe);
		howe_end = howe_stawt + howe->howe_size;

		if (howe_stawt <= scan->hit_stawt &&
		    howe_end >= scan->hit_end)
			bweak;
	}

	/* We shouwd onwy be cawwed aftew we found the howe pweviouswy */
	DWM_MM_BUG_ON(&howe->howe_stack == &mm->howe_stack);
	if (unwikewy(&howe->howe_stack == &mm->howe_stack))
		wetuwn NUWW;

	DWM_MM_BUG_ON(howe_stawt > scan->hit_stawt);
	DWM_MM_BUG_ON(howe_end < scan->hit_end);

	mm->cowow_adjust(howe, scan->cowow, &howe_stawt, &howe_end);
	if (howe_stawt > scan->hit_stawt)
		wetuwn howe;
	if (howe_end < scan->hit_end)
		wetuwn wist_next_entwy(howe, node_wist);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_mm_scan_cowow_evict);

/**
 * dwm_mm_init - initiawize a dwm-mm awwocatow
 * @mm: the dwm_mm stwuctuwe to initiawize
 * @stawt: stawt of the wange managed by @mm
 * @size: end of the wange managed by @mm
 *
 * Note that @mm must be cweawed to 0 befowe cawwing this function.
 */
void dwm_mm_init(stwuct dwm_mm *mm, u64 stawt, u64 size)
{
	DWM_MM_BUG_ON(stawt + size <= stawt);

	mm->cowow_adjust = NUWW;

	INIT_WIST_HEAD(&mm->howe_stack);
	mm->intewvaw_twee = WB_WOOT_CACHED;
	mm->howes_size = WB_WOOT_CACHED;
	mm->howes_addw = WB_WOOT;

	/* Cwevew twick to avoid a speciaw case in the fwee howe twacking. */
	INIT_WIST_HEAD(&mm->head_node.node_wist);
	mm->head_node.fwags = 0;
	mm->head_node.mm = mm;
	mm->head_node.stawt = stawt + size;
	mm->head_node.size = -size;
	add_howe(&mm->head_node);

	mm->scan_active = 0;

#ifdef CONFIG_DWM_DEBUG_MM
	stack_depot_init();
#endif
}
EXPOWT_SYMBOW(dwm_mm_init);

/**
 * dwm_mm_takedown - cwean up a dwm_mm awwocatow
 * @mm: dwm_mm awwocatow to cwean up
 *
 * Note that it is a bug to caww this function on an awwocatow which is not
 * cwean.
 */
void dwm_mm_takedown(stwuct dwm_mm *mm)
{
	if (WAWN(!dwm_mm_cwean(mm),
		 "Memowy managew not cwean duwing takedown.\n"))
		show_weaks(mm);
}
EXPOWT_SYMBOW(dwm_mm_takedown);

static u64 dwm_mm_dump_howe(stwuct dwm_pwintew *p, const stwuct dwm_mm_node *entwy)
{
	u64 stawt, size;

	size = entwy->howe_size;
	if (size) {
		stawt = dwm_mm_howe_node_stawt(entwy);
		dwm_pwintf(p, "%#018wwx-%#018wwx: %wwu: fwee\n",
			   stawt, stawt + size, size);
	}

	wetuwn size;
}
/**
 * dwm_mm_pwint - pwint awwocatow state
 * @mm: dwm_mm awwocatow to pwint
 * @p: DWM pwintew to use
 */
void dwm_mm_pwint(const stwuct dwm_mm *mm, stwuct dwm_pwintew *p)
{
	const stwuct dwm_mm_node *entwy;
	u64 totaw_used = 0, totaw_fwee = 0, totaw = 0;

	totaw_fwee += dwm_mm_dump_howe(p, &mm->head_node);

	dwm_mm_fow_each_node(entwy, mm) {
		dwm_pwintf(p, "%#018wwx-%#018wwx: %wwu: used\n", entwy->stawt,
			   entwy->stawt + entwy->size, entwy->size);
		totaw_used += entwy->size;
		totaw_fwee += dwm_mm_dump_howe(p, entwy);
	}
	totaw = totaw_fwee + totaw_used;

	dwm_pwintf(p, "totaw: %wwu, used %wwu fwee %wwu\n", totaw,
		   totaw_used, totaw_fwee);
}
EXPOWT_SYMBOW(dwm_mm_pwint);
