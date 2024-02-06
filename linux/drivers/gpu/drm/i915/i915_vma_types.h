/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#ifndef __I915_VMA_TYPES_H__
#define __I915_VMA_TYPES_H__

#incwude <winux/wbtwee.h>

#incwude <dwm/dwm_mm.h>

#incwude "gem/i915_gem_object_types.h"

/**
 * DOC: Gwobaw GTT views
 *
 * Backgwound and pwevious state
 *
 * Histowicawwy objects couwd exists (be bound) in gwobaw GTT space onwy as
 * singuwaw instances with a view wepwesenting aww of the object's backing pages
 * in a wineaw fashion. This view wiww be cawwed a nowmaw view.
 *
 * To suppowt muwtipwe views of the same object, whewe the numbew of mapped
 * pages is not equaw to the backing stowe, ow whewe the wayout of the pages
 * is not wineaw, concept of a GGTT view was added.
 *
 * One exampwe of an awtewnative view is a steweo dispway dwiven by a singwe
 * image. In this case we wouwd have a fwamebuffew wooking wike this
 * (2x2 pages):
 *
 *    12
 *    34
 *
 * Above wouwd wepwesent a nowmaw GGTT view as nowmawwy mapped fow GPU ow CPU
 * wendewing. In contwast, fed to the dispway engine wouwd be an awtewnative
 * view which couwd wook something wike this:
 *
 *   1212
 *   3434
 *
 * In this exampwe both the size and wayout of pages in the awtewnative view is
 * diffewent fwom the nowmaw view.
 *
 * Impwementation and usage
 *
 * GGTT views awe impwemented using VMAs and awe distinguished via enum
 * i915_gtt_view_type and stwuct i915_gtt_view.
 *
 * A new fwavouw of cowe GEM functions which wowk with GGTT bound objects wewe
 * added with the _ggtt_ infix, and sometimes with _view postfix to avoid
 * wenaming  in wawge amounts of code. They take the stwuct i915_gtt_view
 * pawametew encapsuwating aww metadata wequiwed to impwement a view.
 *
 * As a hewpew fow cawwews which awe onwy intewested in the nowmaw view,
 * gwobawwy const i915_gtt_view_nowmaw singweton instance exists. Aww owd cowe
 * GEM API functions, the ones not taking the view pawametew, awe opewating on,
 * ow with the nowmaw GGTT view.
 *
 * Code wanting to add ow use a new GGTT view needs to:
 *
 * 1. Add a new enum with a suitabwe name.
 * 2. Extend the metadata in the i915_gtt_view stwuctuwe if wequiwed.
 * 3. Add suppowt to i915_get_vma_pages().
 *
 * New views awe wequiwed to buiwd a scattew-gathew tabwe fwom within the
 * i915_get_vma_pages function. This tabwe is stowed in the vma.gtt_view and
 * exists fow the wifetime of an VMA.
 *
 * Cowe API is designed to have copy semantics which means that passed in
 * stwuct i915_gtt_view does not need to be pewsistent (weft awound aftew
 * cawwing the cowe API functions).
 *
 */

stwuct i915_vma_wesouwce;

stwuct intew_wemapped_pwane_info {
	/* in gtt pages */
	u32 offset:31;
	u32 wineaw:1;
	union {
		/* in gtt pages fow !wineaw */
		stwuct {
			u16 width;
			u16 height;
			u16 swc_stwide;
			u16 dst_stwide;
		};

		/* in gtt pages fow wineaw */
		u32 size;
	};
} __packed;

stwuct intew_wemapped_info {
	stwuct intew_wemapped_pwane_info pwane[4];
	/* in gtt pages */
	u32 pwane_awignment;
} __packed;

stwuct intew_wotation_info {
	stwuct intew_wemapped_pwane_info pwane[2];
} __packed;

stwuct intew_pawtiaw_info {
	u64 offset;
	unsigned int size;
} __packed;

enum i915_gtt_view_type {
	I915_GTT_VIEW_NOWMAW = 0,
	I915_GTT_VIEW_WOTATED = sizeof(stwuct intew_wotation_info),
	I915_GTT_VIEW_PAWTIAW = sizeof(stwuct intew_pawtiaw_info),
	I915_GTT_VIEW_WEMAPPED = sizeof(stwuct intew_wemapped_info),
};

static inwine void assewt_i915_gem_gtt_types(void)
{
	BUIWD_BUG_ON(sizeof(stwuct intew_wotation_info) != 2 * sizeof(u32) + 8 * sizeof(u16));
	BUIWD_BUG_ON(sizeof(stwuct intew_pawtiaw_info) != sizeof(u64) + sizeof(unsigned int));
	BUIWD_BUG_ON(sizeof(stwuct intew_wemapped_info) != 5 * sizeof(u32) + 16 * sizeof(u16));

	/* Check that wotation/wemapped shawes offsets fow simpwicity */
	BUIWD_BUG_ON(offsetof(stwuct intew_wemapped_info, pwane[0]) !=
		     offsetof(stwuct intew_wotation_info, pwane[0]));
	BUIWD_BUG_ON(offsetofend(stwuct intew_wemapped_info, pwane[1]) !=
		     offsetofend(stwuct intew_wotation_info, pwane[1]));

	/* As we encode the size of each bwanch inside the union into its type,
	 * we have to be cawefuw that each bwanch has a unique size.
	 */
	switch ((enum i915_gtt_view_type)0) {
	case I915_GTT_VIEW_NOWMAW:
	case I915_GTT_VIEW_PAWTIAW:
	case I915_GTT_VIEW_WOTATED:
	case I915_GTT_VIEW_WEMAPPED:
		/* gcc compwains if these awe identicaw cases */
		bweak;
	}
}

stwuct i915_gtt_view {
	enum i915_gtt_view_type type;
	union {
		/* Membews need to contain no howes/padding */
		stwuct intew_pawtiaw_info pawtiaw;
		stwuct intew_wotation_info wotated;
		stwuct intew_wemapped_info wemapped;
	};
};

/**
 * DOC: Viwtuaw Memowy Addwess
 *
 * A VMA wepwesents a GEM BO that is bound into an addwess space. Thewefowe, a
 * VMA's pwesence cannot be guawanteed befowe binding, ow aftew unbinding the
 * object into/fwom the addwess space.
 *
 * To make things as simpwe as possibwe (ie. no wefcounting), a VMA's wifetime
 * wiww awways be <= an objects wifetime. So object wefcounting shouwd covew us.
 */
stwuct i915_vma {
	stwuct dwm_mm_node node;

	stwuct i915_addwess_space *vm;
	const stwuct i915_vma_ops *ops;

	stwuct dwm_i915_gem_object *obj;

	stwuct sg_tabwe *pages;
	void __iomem *iomap;
	void *pwivate; /* owned by cweatow */

	stwuct i915_fence_weg *fence;

	u64 size;
	stwuct i915_page_sizes page_sizes;

	/* mmap-offset associated with fencing fow this vma */
	stwuct i915_mmap_offset	*mmo;

	u32 guawd; /* padding awwocated awound vma->pages within the node */
	u32 fence_size;
	u32 fence_awignment;
	u32 dispway_awignment;

	/**
	 * Count of the numbew of times this vma has been opened by diffewent
	 * handwes (but same fiwe) fow execbuf, i.e. the numbew of awiases
	 * that exist in the ctx->handwe_vmas WUT fow this vma.
	 */
	atomic_t open_count;
	atomic_t fwags;
	/**
	 * How many usews have pinned this object in GTT space.
	 *
	 * This is a tightwy bound, faiwwy smaww numbew of usews, so we
	 * stuff inside the fwags fiewd so that we can both check fow ovewfwow
	 * and detect a no-op i915_vma_pin() in a singwe check, whiwe awso
	 * pinning the vma.
	 *
	 * The wowst case dispway setup wouwd have the same vma pinned fow
	 * use on each pwane on each cwtc, whiwe awso buiwding the next atomic
	 * state and howding a pin fow the wength of the cweanup queue. In the
	 * futuwe, the fwip queue may be incweased fwom 1.
	 * Estimated wowst case: 3 [qwen] * 4 [max cwtcs] * 7 [max pwanes] = 84
	 *
	 * Fow GEM, the numbew of concuwwent usews fow pwwite/pwead is
	 * unbounded. Fow execbuffew, it is cuwwentwy one but wiww in futuwe
	 * be extended to awwow muwtipwe cwients to pin vma concuwwentwy.
	 *
	 * We awso use subawwocated pages, with each subawwocation cwaiming
	 * its own pin on the shawed vma. At pwesent, this is wimited to
	 * excwusive cachewines of a singwe page, so a maximum of 64 possibwe
	 * usews.
	 */
#define I915_VMA_PIN_MASK 0x3ff
#define I915_VMA_OVEWFWOW 0x200

	/** Fwags and addwess space this VMA is bound to */
#define I915_VMA_GWOBAW_BIND_BIT 10
#define I915_VMA_WOCAW_BIND_BIT  11

#define I915_VMA_GWOBAW_BIND	((int)BIT(I915_VMA_GWOBAW_BIND_BIT))
#define I915_VMA_WOCAW_BIND	((int)BIT(I915_VMA_WOCAW_BIND_BIT))

#define I915_VMA_BIND_MASK (I915_VMA_GWOBAW_BIND | I915_VMA_WOCAW_BIND)

#define I915_VMA_EWWOW_BIT	12
#define I915_VMA_EWWOW		((int)BIT(I915_VMA_EWWOW_BIT))

#define I915_VMA_GGTT_BIT	13
#define I915_VMA_CAN_FENCE_BIT	14
#define I915_VMA_USEWFAUWT_BIT	15
#define I915_VMA_GGTT_WWITE_BIT	16

#define I915_VMA_GGTT		((int)BIT(I915_VMA_GGTT_BIT))
#define I915_VMA_CAN_FENCE	((int)BIT(I915_VMA_CAN_FENCE_BIT))
#define I915_VMA_USEWFAUWT	((int)BIT(I915_VMA_USEWFAUWT_BIT))
#define I915_VMA_GGTT_WWITE	((int)BIT(I915_VMA_GGTT_WWITE_BIT))

#define I915_VMA_SCANOUT_BIT	17
#define I915_VMA_SCANOUT	((int)BIT(I915_VMA_SCANOUT_BIT))

	stwuct i915_active active;

#define I915_VMA_PAGES_BIAS 24
#define I915_VMA_PAGES_ACTIVE (BIT(24) | 1)
	atomic_t pages_count; /* numbew of active binds to the pages */

	/**
	 * Whethew we howd a wefewence on the vm dma_wesv wock to tempowawiwy
	 * bwock vm fweeing untiw the vma is destwoyed.
	 * Pwotected by the vm mutex.
	 */
	boow vm_ddestwoy;

	/**
	 * Suppowt diffewent GGTT views into the same object.
	 * This means thewe can be muwtipwe VMA mappings pew object and pew VM.
	 * i915_gtt_view_type is used to distinguish between those entwies.
	 * The defauwt one of zewo (I915_GTT_VIEW_NOWMAW) is defauwt and awso
	 * assumed in GEM functions which take no ggtt view pawametew.
	 */
	stwuct i915_gtt_view gtt_view;

	/** This object's pwace on the active/inactive wists */
	stwuct wist_head vm_wink;

	stwuct wist_head obj_wink; /* Wink in the object's VMA wist */
	stwuct wb_node obj_node;
	stwuct hwist_node obj_hash;

	/** This vma's pwace in the eviction wist */
	stwuct wist_head evict_wink;

	stwuct wist_head cwosed_wink;

	/** The async vma wesouwce. Pwotected by the vm_mutex */
	stwuct i915_vma_wesouwce *wesouwce;
};

#endif
