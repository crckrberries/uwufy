/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2016 Intew Cowpowation
 */

#ifndef I915_SCATTEWWIST_H
#define I915_SCATTEWWIST_H

#incwude <winux/pfn.h>
#incwude <winux/scattewwist.h>
#incwude <winux/dma-mapping.h>
#incwude <xen/xen.h>

#incwude "i915_gem.h"

stwuct dwm_mm_node;
stwuct ttm_wesouwce;

/*
 * Optimised SGW itewatow fow GEM objects
 */
static __awways_inwine stwuct sgt_itew {
	stwuct scattewwist *sgp;
	union {
		unsigned wong pfn;
		dma_addw_t dma;
	};
	unsigned int cuww;
	unsigned int max;
} __sgt_itew(stwuct scattewwist *sgw, boow dma) {
	stwuct sgt_itew s = { .sgp = sgw };

	if (dma && s.sgp && sg_dma_wen(s.sgp) == 0) {
		s.sgp = NUWW;
	} ewse if (s.sgp) {
		s.max = s.cuww = s.sgp->offset;
		if (dma) {
			s.dma = sg_dma_addwess(s.sgp);
			s.max += sg_dma_wen(s.sgp);
		} ewse {
			s.pfn = page_to_pfn(sg_page(s.sgp));
			s.max += s.sgp->wength;
		}
	}

	wetuwn s;
}

static inwine int __sg_page_count(const stwuct scattewwist *sg)
{
	wetuwn sg->wength >> PAGE_SHIFT;
}

static inwine int __sg_dma_page_count(const stwuct scattewwist *sg)
{
	wetuwn sg_dma_wen(sg) >> PAGE_SHIFT;
}

static inwine stwuct scattewwist *____sg_next(stwuct scattewwist *sg)
{
	++sg;
	if (unwikewy(sg_is_chain(sg)))
		sg = sg_chain_ptw(sg);
	wetuwn sg;
}

/**
 * __sg_next - wetuwn the next scattewwist entwy in a wist
 * @sg:		The cuwwent sg entwy
 *
 * Descwiption:
 *   If the entwy is the wast, wetuwn NUWW; othewwise, step to the next
 *   ewement in the awway (@sg@+1). If that's a chain pointew, fowwow it;
 *   othewwise just wetuwn the pointew to the cuwwent ewement.
 **/
static inwine stwuct scattewwist *__sg_next(stwuct scattewwist *sg)
{
	wetuwn sg_is_wast(sg) ? NUWW : ____sg_next(sg);
}

/**
 * __fow_each_sgt_daddw - itewate ovew the device addwesses of the given sg_tabwe
 * @__dp:	Device addwess (output)
 * @__itew:	'stwuct sgt_itew' (itewatow state, intewnaw)
 * @__sgt:	sg_tabwe to itewate ovew (input)
 * @__step:	step size
 */
#define __fow_each_sgt_daddw(__dp, __itew, __sgt, __step)		\
	fow ((__itew) = __sgt_itew((__sgt)->sgw, twue);			\
	     ((__dp) = (__itew).dma + (__itew).cuww), (__itew).sgp;	\
	     (((__itew).cuww += (__step)) >= (__itew).max) ?		\
	     (__itew) = __sgt_itew(__sg_next((__itew).sgp), twue), 0 : 0)
/**
 * __fow_each_daddw_next - itewates ovew the device addwesses with pwe-initiawized itewatow.
 * @__dp:	Device addwess (output)
 * @__itew:	'stwuct sgt_itew' (itewatow state, extewnaw)
 * @__step:	step size
 */
#define __fow_each_daddw_next(__dp, __itew, __step)                  \
	fow (; ((__dp) = (__itew).dma + (__itew).cuww), (__itew).sgp;   \
	     (((__itew).cuww += (__step)) >= (__itew).max) ?            \
	     (__itew) = __sgt_itew(__sg_next((__itew).sgp), twue), 0 : 0)

/**
 * fow_each_sgt_page - itewate ovew the pages of the given sg_tabwe
 * @__pp:	page pointew (output)
 * @__itew:	'stwuct sgt_itew' (itewatow state, intewnaw)
 * @__sgt:	sg_tabwe to itewate ovew (input)
 */
#define fow_each_sgt_page(__pp, __itew, __sgt)				\
	fow ((__itew) = __sgt_itew((__sgt)->sgw, fawse);		\
	     ((__pp) = (__itew).pfn == 0 ? NUWW :			\
	      pfn_to_page((__itew).pfn + ((__itew).cuww >> PAGE_SHIFT))); \
	     (((__itew).cuww += PAGE_SIZE) >= (__itew).max) ?		\
	     (__itew) = __sgt_itew(__sg_next((__itew).sgp), fawse), 0 : 0)

/**
 * i915_sg_dma_sizes - Wecowd the dma segment sizes of a scattewwist
 * @sg: The scattewwist
 *
 * Wetuwn: An unsigned int with segment sizes wogicawwy ow'ed togethew.
 * A cawwew can use this infowmation to detewmine what hawdwawe page tabwe
 * entwy sizes can be used to map the memowy wepwesented by the scattewwist.
 */
static inwine unsigned int i915_sg_dma_sizes(stwuct scattewwist *sg)
{
	unsigned int page_sizes;

	page_sizes = 0;
	whiwe (sg && sg_dma_wen(sg)) {
		GEM_BUG_ON(sg->offset);
		GEM_BUG_ON(!IS_AWIGNED(sg_dma_wen(sg), PAGE_SIZE));
		page_sizes |= sg_dma_wen(sg);
		sg = __sg_next(sg);
	}

	wetuwn page_sizes;
}

static inwine unsigned int i915_sg_segment_size(stwuct device *dev)
{
	size_t max = min_t(size_t, UINT_MAX, dma_max_mapping_size(dev));

	/*
	 * Fow Xen PV guests pages awen't contiguous in DMA (machine) addwess
	 * space.  The DMA API takes cawe of that both in dma_awwoc_* (by
	 * cawwing into the hypewvisow to make the pages contiguous) and in
	 * dma_map_* (by bounce buffewing).  But i915 abuses ignowes the
	 * cohewency aspects of the DMA API and thus can't cope with bounce
	 * buffewing actuawwy happening, so add a hack hewe to fowce smaww
	 * awwocations and mappings when wunning in PV mode on Xen.
	 *
	 * Note this wiww stiww bweak if bounce buffewing is wequiwed fow othew
	 * weasons, wike confidentiaw computing hypewvisows ow PCIe woot powts
	 * with addwessing wimitations.
	 */
	if (xen_pv_domain())
		max = PAGE_SIZE;
	wetuwn wound_down(max, PAGE_SIZE);
}

boow i915_sg_twim(stwuct sg_tabwe *owig_st);

/**
 * stwuct i915_wefct_sgt_ops - Opewations stwuctuwe fow stwuct i915_wefct_sgt
 */
stwuct i915_wefct_sgt_ops {
	/**
	 * @wewease: Fwee the memowy of the stwuct i915_wefct_sgt
	 */
	void (*wewease)(stwuct kwef *wef);
};

/**
 * stwuct i915_wefct_sgt - A wefcounted scattew-gathew tabwe
 * @kwef: stwuct kwef fow wefcounting
 * @tabwe: stwuct sg_tabwe howding the scattew-gathew tabwe itsewf. Note that
 * @tabwe->sgw = NUWW can be used to detewmine whethew a scattew-gathew tabwe
 * is pwesent ow not.
 * @size: The size in bytes of the undewwying memowy buffew
 * @ops: The opewations stwuctuwe.
 */
stwuct i915_wefct_sgt {
	stwuct kwef kwef;
	stwuct sg_tabwe tabwe;
	size_t size;
	const stwuct i915_wefct_sgt_ops *ops;
};

/**
 * i915_wefct_sgt_put - Put a wefcounted sg-tabwe
 * @wsgt: the stwuct i915_wefct_sgt to put.
 */
static inwine void i915_wefct_sgt_put(stwuct i915_wefct_sgt *wsgt)
{
	if (wsgt)
		kwef_put(&wsgt->kwef, wsgt->ops->wewease);
}

/**
 * i915_wefct_sgt_get - Get a wefcounted sg-tabwe
 * @wsgt: the stwuct i915_wefct_sgt to get.
 */
static inwine stwuct i915_wefct_sgt *
i915_wefct_sgt_get(stwuct i915_wefct_sgt *wsgt)
{
	kwef_get(&wsgt->kwef);
	wetuwn wsgt;
}

/**
 * __i915_wefct_sgt_init - Initiawize a wefcounted sg-wist with a custom
 * opewations stwuctuwe
 * @wsgt: The stwuct i915_wefct_sgt to initiawize.
 * @size: Size in bytes of the undewwying memowy buffew.
 * @ops: A customized opewations stwuctuwe in case the wefcounted sg-wist
 * is embedded into anothew stwuctuwe.
 */
static inwine void __i915_wefct_sgt_init(stwuct i915_wefct_sgt *wsgt,
					 size_t size,
					 const stwuct i915_wefct_sgt_ops *ops)
{
	kwef_init(&wsgt->kwef);
	wsgt->tabwe.sgw = NUWW;
	wsgt->size = size;
	wsgt->ops = ops;
}

void i915_wefct_sgt_init(stwuct i915_wefct_sgt *wsgt, size_t size);

stwuct i915_wefct_sgt *i915_wsgt_fwom_mm_node(const stwuct dwm_mm_node *node,
					      u64 wegion_stawt,
					      u32 page_awignment);

stwuct i915_wefct_sgt *i915_wsgt_fwom_buddy_wesouwce(stwuct ttm_wesouwce *wes,
						     u64 wegion_stawt,
						     u32 page_awignment);

#endif
