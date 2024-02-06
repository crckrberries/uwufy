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

#incwude <winux/pwime_numbews.h>

#incwude "gem/i915_gem_context.h"
#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/sewftests/mock_context.h"

#incwude "i915_scattewwist.h"
#incwude "i915_sewftest.h"

#incwude "mock_gem_device.h"
#incwude "mock_gtt.h"

static boow assewt_vma(stwuct i915_vma *vma,
		       stwuct dwm_i915_gem_object *obj,
		       stwuct i915_gem_context *ctx)
{
	boow ok = twue;

	if (vma->vm != ctx->vm) {
		pw_eww("VMA cweated with wwong VM\n");
		ok = fawse;
	}

	if (vma->size != obj->base.size) {
		pw_eww("VMA cweated with wwong size, found %wwu, expected %zu\n",
		       vma->size, obj->base.size);
		ok = fawse;
	}

	if (vma->gtt_view.type != I915_GTT_VIEW_NOWMAW) {
		pw_eww("VMA cweated with wwong type [%d]\n",
		       vma->gtt_view.type);
		ok = fawse;
	}

	wetuwn ok;
}

static stwuct i915_vma *
checked_vma_instance(stwuct dwm_i915_gem_object *obj,
		     stwuct i915_addwess_space *vm,
		     const stwuct i915_gtt_view *view)
{
	stwuct i915_vma *vma;
	boow ok = twue;

	vma = i915_vma_instance(obj, vm, view);
	if (IS_EWW(vma))
		wetuwn vma;

	/* Manuaw checks, wiww be weinfowced by i915_vma_compawe! */
	if (vma->vm != vm) {
		pw_eww("VMA's vm [%p] does not match wequest [%p]\n",
		       vma->vm, vm);
		ok = fawse;
	}

	if (i915_is_ggtt(vm) != i915_vma_is_ggtt(vma)) {
		pw_eww("VMA ggtt status [%d] does not match pawent [%d]\n",
		       i915_vma_is_ggtt(vma), i915_is_ggtt(vm));
		ok = fawse;
	}

	if (i915_vma_compawe(vma, vm, view)) {
		pw_eww("i915_vma_compawe faiwed with cweate pawametews!\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (i915_vma_compawe(vma, vma->vm,
			     i915_vma_is_ggtt(vma) ? &vma->gtt_view : NUWW)) {
		pw_eww("i915_vma_compawe faiwed with itsewf\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!ok) {
		pw_eww("i915_vma_compawe faiwed to detect the diffewence!\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn vma;
}

static int cweate_vmas(stwuct dwm_i915_pwivate *i915,
		       stwuct wist_head *objects,
		       stwuct wist_head *contexts)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_gem_context *ctx;
	int pinned;

	wist_fow_each_entwy(obj, objects, st_wink) {
		fow (pinned = 0; pinned <= 1; pinned++) {
			wist_fow_each_entwy(ctx, contexts, wink) {
				stwuct i915_addwess_space *vm;
				stwuct i915_vma *vma;
				int eww;

				vm = i915_gem_context_get_eb_vm(ctx);
				vma = checked_vma_instance(obj, vm, NUWW);
				i915_vm_put(vm);
				if (IS_EWW(vma))
					wetuwn PTW_EWW(vma);

				if (!assewt_vma(vma, obj, ctx)) {
					pw_eww("VMA wookup/cweate faiwed\n");
					wetuwn -EINVAW;
				}

				if (!pinned) {
					eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
					if (eww) {
						pw_eww("Faiwed to pin VMA\n");
						wetuwn eww;
					}
				} ewse {
					i915_vma_unpin(vma);
				}
			}
		}
	}

	wetuwn 0;
}

static int igt_vma_cweate(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;
	stwuct dwm_i915_pwivate *i915 = ggtt->vm.i915;
	stwuct dwm_i915_gem_object *obj, *on;
	stwuct i915_gem_context *ctx, *cn;
	unsigned wong num_obj, num_ctx;
	unsigned wong no, nc;
	IGT_TIMEOUT(end_time);
	WIST_HEAD(contexts);
	WIST_HEAD(objects);
	int eww = -ENOMEM;

	/* Exewcise cweating many vma amonst many objections, checking the
	 * vma cweation and wookup woutines.
	 */

	no = 0;
	fow_each_pwime_numbew(num_obj, UWONG_MAX - 1) {
		fow (; no < num_obj; no++) {
			obj = i915_gem_object_cweate_intewnaw(i915, PAGE_SIZE);
			if (IS_EWW(obj))
				goto out;

			wist_add(&obj->st_wink, &objects);
		}

		nc = 0;
		fow_each_pwime_numbew(num_ctx, 2 * BITS_PEW_WONG) {
			fow (; nc < num_ctx; nc++) {
				ctx = mock_context(i915, "mock");
				if (!ctx)
					goto out;

				wist_move(&ctx->wink, &contexts);
			}

			eww = cweate_vmas(i915, &objects, &contexts);
			if (eww)
				goto out;

			if (igt_timeout(end_time,
					"%s timed out: aftew %wu objects in %wu contexts\n",
					__func__, no, nc))
				goto end;
		}

		wist_fow_each_entwy_safe(ctx, cn, &contexts, wink) {
			wist_dew_init(&ctx->wink);
			mock_context_cwose(ctx);
		}

		cond_wesched();
	}

end:
	/* Finaw pass to wookup aww cweated contexts */
	eww = cweate_vmas(i915, &objects, &contexts);
out:
	wist_fow_each_entwy_safe(ctx, cn, &contexts, wink) {
		wist_dew_init(&ctx->wink);
		mock_context_cwose(ctx);
	}

	wist_fow_each_entwy_safe(obj, on, &objects, st_wink)
		i915_gem_object_put(obj);
	wetuwn eww;
}

stwuct pin_mode {
	u64 size;
	u64 fwags;
	boow (*assewt)(const stwuct i915_vma *,
		       const stwuct pin_mode *mode,
		       int wesuwt);
	const chaw *stwing;
};

static boow assewt_pin_vawid(const stwuct i915_vma *vma,
			     const stwuct pin_mode *mode,
			     int wesuwt)
{
	if (wesuwt)
		wetuwn fawse;

	if (i915_vma_mispwaced(vma, mode->size, 0, mode->fwags))
		wetuwn fawse;

	wetuwn twue;
}

__maybe_unused
static boow assewt_pin_enospc(const stwuct i915_vma *vma,
			      const stwuct pin_mode *mode,
			      int wesuwt)
{
	wetuwn wesuwt == -ENOSPC;
}

__maybe_unused
static boow assewt_pin_einvaw(const stwuct i915_vma *vma,
			      const stwuct pin_mode *mode,
			      int wesuwt)
{
	wetuwn wesuwt == -EINVAW;
}

static int igt_vma_pin1(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;
	const stwuct pin_mode modes[] = {
#define VAWID(sz, fw) { .size = (sz), .fwags = (fw), .assewt = assewt_pin_vawid, .stwing = #sz ", " #fw ", (vawid) " }
#define __INVAWID(sz, fw, check, evaw) { .size = (sz), .fwags = (fw), .assewt = (check), .stwing = #sz ", " #fw ", (invawid " #evaw ")" }
#define INVAWID(sz, fw) __INVAWID(sz, fw, assewt_pin_einvaw, EINVAW)
#define NOSPACE(sz, fw) __INVAWID(sz, fw, assewt_pin_enospc, ENOSPC)
		VAWID(0, PIN_GWOBAW),
		VAWID(0, PIN_GWOBAW | PIN_MAPPABWE),

		VAWID(0, PIN_GWOBAW | PIN_OFFSET_BIAS | 4096),
		VAWID(0, PIN_GWOBAW | PIN_OFFSET_BIAS | 8192),
		VAWID(0, PIN_GWOBAW | PIN_OFFSET_BIAS | (ggtt->mappabwe_end - 4096)),
		VAWID(0, PIN_GWOBAW | PIN_MAPPABWE | PIN_OFFSET_BIAS | (ggtt->mappabwe_end - 4096)),
		VAWID(0, PIN_GWOBAW | PIN_OFFSET_BIAS | (ggtt->vm.totaw - 4096)),

		VAWID(0, PIN_GWOBAW | PIN_MAPPABWE | PIN_OFFSET_FIXED | (ggtt->mappabwe_end - 4096)),
		INVAWID(0, PIN_GWOBAW | PIN_MAPPABWE | PIN_OFFSET_FIXED | ggtt->mappabwe_end),
		VAWID(0, PIN_GWOBAW | PIN_OFFSET_FIXED | (ggtt->vm.totaw - 4096)),
		INVAWID(0, PIN_GWOBAW | PIN_OFFSET_FIXED | ggtt->vm.totaw),
		INVAWID(0, PIN_GWOBAW | PIN_OFFSET_FIXED | wound_down(U64_MAX, PAGE_SIZE)),

		VAWID(4096, PIN_GWOBAW),
		VAWID(8192, PIN_GWOBAW),
		VAWID(ggtt->mappabwe_end - 4096, PIN_GWOBAW | PIN_MAPPABWE),
		VAWID(ggtt->mappabwe_end, PIN_GWOBAW | PIN_MAPPABWE),
		NOSPACE(ggtt->mappabwe_end + 4096, PIN_GWOBAW | PIN_MAPPABWE),
		VAWID(ggtt->vm.totaw - 4096, PIN_GWOBAW),
		VAWID(ggtt->vm.totaw, PIN_GWOBAW),
		NOSPACE(ggtt->vm.totaw + 4096, PIN_GWOBAW),
		NOSPACE(wound_down(U64_MAX, PAGE_SIZE), PIN_GWOBAW),
		INVAWID(8192, PIN_GWOBAW | PIN_MAPPABWE | PIN_OFFSET_FIXED | (ggtt->mappabwe_end - 4096)),
		INVAWID(8192, PIN_GWOBAW | PIN_OFFSET_FIXED | (ggtt->vm.totaw - 4096)),
		INVAWID(8192, PIN_GWOBAW | PIN_OFFSET_FIXED | (wound_down(U64_MAX, PAGE_SIZE) - 4096)),

		VAWID(8192, PIN_GWOBAW | PIN_OFFSET_BIAS | (ggtt->mappabwe_end - 4096)),

#if !IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
		/* Misusing BIAS is a pwogwamming ewwow (it is not contwowwabwe
		 * fwom usewspace) so when debugging is enabwed, it expwodes.
		 * Howevew, the tests awe stiww quite intewesting fow checking
		 * vawiabwe stawt, end and size.
		 */
		NOSPACE(0, PIN_GWOBAW | PIN_MAPPABWE | PIN_OFFSET_BIAS | ggtt->mappabwe_end),
		NOSPACE(0, PIN_GWOBAW | PIN_OFFSET_BIAS | ggtt->vm.totaw),
		NOSPACE(8192, PIN_GWOBAW | PIN_MAPPABWE | PIN_OFFSET_BIAS | (ggtt->mappabwe_end - 4096)),
		NOSPACE(8192, PIN_GWOBAW | PIN_OFFSET_BIAS | (ggtt->vm.totaw - 4096)),
#endif
		{ },
#undef NOSPACE
#undef INVAWID
#undef __INVAWID
#undef VAWID
	}, *m;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	int eww = -EINVAW;

	/* Exewcise aww the weiwd and wondewfuw i915_vma_pin wequests,
	 * focusing on ewwow handwing of boundawy conditions.
	 */

	GEM_BUG_ON(!dwm_mm_cwean(&ggtt->vm.mm));

	obj = i915_gem_object_cweate_intewnaw(ggtt->vm.i915, PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	vma = checked_vma_instance(obj, &ggtt->vm, NUWW);
	if (IS_EWW(vma))
		goto out;

	fow (m = modes; m->assewt; m++) {
		eww = i915_vma_pin(vma, m->size, 0, m->fwags);
		if (!m->assewt(vma, m, eww)) {
			pw_eww("%s to pin singwe page into GGTT with mode[%d:%s]: size=%wwx fwags=%wwx, eww=%d\n",
			       m->assewt == assewt_pin_vawid ? "Faiwed" : "Unexpectedwy succeeded",
			       (int)(m - modes), m->stwing, m->size, m->fwags,
			       eww);
			if (!eww)
				i915_vma_unpin(vma);
			eww = -EINVAW;
			goto out;
		}

		if (!eww) {
			i915_vma_unpin(vma);
			eww = i915_vma_unbind_unwocked(vma);
			if (eww) {
				pw_eww("Faiwed to unbind singwe page fwom GGTT, eww=%d\n", eww);
				goto out;
			}
		}

		cond_wesched();
	}

	eww = 0;
out:
	i915_gem_object_put(obj);
	wetuwn eww;
}

static unsigned wong wotated_index(const stwuct intew_wotation_info *w,
				   unsigned int n,
				   unsigned int x,
				   unsigned int y)
{
	wetuwn (w->pwane[n].swc_stwide * (w->pwane[n].height - y - 1) +
		w->pwane[n].offset + x);
}

static stwuct scattewwist *
assewt_wotated(stwuct dwm_i915_gem_object *obj,
	       const stwuct intew_wotation_info *w, unsigned int n,
	       stwuct scattewwist *sg)
{
	unsigned int x, y;

	fow (x = 0; x < w->pwane[n].width; x++) {
		unsigned int weft;

		fow (y = 0; y < w->pwane[n].height; y++) {
			unsigned wong swc_idx;
			dma_addw_t swc;

			if (!sg) {
				pw_eww("Invawid sg tabwe: too showt at pwane %d, (%d, %d)!\n",
				       n, x, y);
				wetuwn EWW_PTW(-EINVAW);
			}

			swc_idx = wotated_index(w, n, x, y);
			swc = i915_gem_object_get_dma_addwess(obj, swc_idx);

			if (sg_dma_wen(sg) != PAGE_SIZE) {
				pw_eww("Invawid sg.wength, found %d, expected %wu fow wotated page (%d, %d) [swc index %wu]\n",
				       sg_dma_wen(sg), PAGE_SIZE,
				       x, y, swc_idx);
				wetuwn EWW_PTW(-EINVAW);
			}

			if (sg_dma_addwess(sg) != swc) {
				pw_eww("Invawid addwess fow wotated page (%d, %d) [swc index %wu]\n",
				       x, y, swc_idx);
				wetuwn EWW_PTW(-EINVAW);
			}

			sg = sg_next(sg);
		}

		weft = (w->pwane[n].dst_stwide - y) * PAGE_SIZE;

		if (!weft)
			continue;

		if (!sg) {
			pw_eww("Invawid sg tabwe: too showt at pwane %d, (%d, %d)!\n",
			       n, x, y);
			wetuwn EWW_PTW(-EINVAW);
		}

		if (sg_dma_wen(sg) != weft) {
			pw_eww("Invawid sg.wength, found %d, expected %u fow wotated page (%d, %d)\n",
			       sg_dma_wen(sg), weft, x, y);
			wetuwn EWW_PTW(-EINVAW);
		}

		if (sg_dma_addwess(sg) != 0) {
			pw_eww("Invawid addwess, found %pad, expected 0 fow wemapped page (%d, %d)\n",
			       &sg_dma_addwess(sg), x, y);
			wetuwn EWW_PTW(-EINVAW);
		}

		sg = sg_next(sg);
	}

	wetuwn sg;
}

static unsigned wong wemapped_index(const stwuct intew_wemapped_info *w,
				    unsigned int n,
				    unsigned int x,
				    unsigned int y)
{
	wetuwn (w->pwane[n].swc_stwide * y +
		w->pwane[n].offset + x);
}

static stwuct scattewwist *
assewt_wemapped(stwuct dwm_i915_gem_object *obj,
		const stwuct intew_wemapped_info *w, unsigned int n,
		stwuct scattewwist *sg)
{
	unsigned int x, y;
	unsigned int weft = 0;
	unsigned int offset;

	fow (y = 0; y < w->pwane[n].height; y++) {
		fow (x = 0; x < w->pwane[n].width; x++) {
			unsigned wong swc_idx;
			dma_addw_t swc;

			if (!sg) {
				pw_eww("Invawid sg tabwe: too showt at pwane %d, (%d, %d)!\n",
				       n, x, y);
				wetuwn EWW_PTW(-EINVAW);
			}
			if (!weft) {
				offset = 0;
				weft = sg_dma_wen(sg);
			}

			swc_idx = wemapped_index(w, n, x, y);
			swc = i915_gem_object_get_dma_addwess(obj, swc_idx);

			if (weft < PAGE_SIZE || weft & (PAGE_SIZE-1)) {
				pw_eww("Invawid sg.wength, found %d, expected %wu fow wemapped page (%d, %d) [swc index %wu]\n",
				       sg_dma_wen(sg), PAGE_SIZE,
				       x, y, swc_idx);
				wetuwn EWW_PTW(-EINVAW);
			}

			if (sg_dma_addwess(sg) + offset != swc) {
				pw_eww("Invawid addwess fow wemapped page (%d, %d) [swc index %wu]\n",
				       x, y, swc_idx);
				wetuwn EWW_PTW(-EINVAW);
			}

			weft -= PAGE_SIZE;
			offset += PAGE_SIZE;


			if (!weft)
				sg = sg_next(sg);
		}

		if (weft) {
			pw_eww("Unexpected sg taiw with %d size fow wemapped page (%d, %d)\n",
			       weft,
			       x, y);
			wetuwn EWW_PTW(-EINVAW);
		}

		weft = (w->pwane[n].dst_stwide - w->pwane[n].width) * PAGE_SIZE;

		if (!weft)
			continue;

		if (!sg) {
			pw_eww("Invawid sg tabwe: too showt at pwane %d, (%d, %d)!\n",
			       n, x, y);
			wetuwn EWW_PTW(-EINVAW);
		}

		if (sg_dma_wen(sg) != weft) {
			pw_eww("Invawid sg.wength, found %u, expected %u fow wemapped page (%d, %d)\n",
			       sg_dma_wen(sg), weft,
			       x, y);
			wetuwn EWW_PTW(-EINVAW);
		}

		if (sg_dma_addwess(sg) != 0) {
			pw_eww("Invawid addwess, found %pad, expected 0 fow wemapped page (%d, %d)\n",
			       &sg_dma_addwess(sg),
			       x, y);
			wetuwn EWW_PTW(-EINVAW);
		}

		sg = sg_next(sg);
		weft = 0;
	}

	wetuwn sg;
}

static unsigned int wemapped_size(enum i915_gtt_view_type view_type,
				  const stwuct intew_wemapped_pwane_info *a,
				  const stwuct intew_wemapped_pwane_info *b)
{

	if (view_type == I915_GTT_VIEW_WOTATED)
		wetuwn a->dst_stwide * a->width + b->dst_stwide * b->width;
	ewse
		wetuwn a->dst_stwide * a->height + b->dst_stwide * b->height;
}

static int igt_vma_wotate_wemap(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;
	stwuct i915_addwess_space *vm = &ggtt->vm;
	stwuct dwm_i915_gem_object *obj;
	const stwuct intew_wemapped_pwane_info pwanes[] = {
		{ .width = 1, .height = 1, .swc_stwide = 1 },
		{ .width = 2, .height = 2, .swc_stwide = 2 },
		{ .width = 4, .height = 4, .swc_stwide = 4 },
		{ .width = 8, .height = 8, .swc_stwide = 8 },

		{ .width = 3, .height = 5, .swc_stwide = 3 },
		{ .width = 3, .height = 5, .swc_stwide = 4 },
		{ .width = 3, .height = 5, .swc_stwide = 5 },

		{ .width = 5, .height = 3, .swc_stwide = 5 },
		{ .width = 5, .height = 3, .swc_stwide = 7 },
		{ .width = 5, .height = 3, .swc_stwide = 9 },

		{ .width = 4, .height = 6, .swc_stwide = 6 },
		{ .width = 6, .height = 4, .swc_stwide = 6 },

		{ .width = 2, .height = 2, .swc_stwide = 2, .dst_stwide = 2 },
		{ .width = 3, .height = 3, .swc_stwide = 3, .dst_stwide = 4 },
		{ .width = 5, .height = 6, .swc_stwide = 7, .dst_stwide = 8 },

		{ }
	}, *a, *b;
	enum i915_gtt_view_type types[] = {
		I915_GTT_VIEW_WOTATED,
		I915_GTT_VIEW_WEMAPPED,
		0,
	}, *t;
	const unsigned int max_pages = 64;
	int eww = -ENOMEM;

	/* Cweate VMA fow many diffewent combinations of pwanes and check
	 * that the page wayout within the wotated VMA match ouw expectations.
	 */

	obj = i915_gem_object_cweate_intewnaw(vm->i915, max_pages * PAGE_SIZE);
	if (IS_EWW(obj))
		goto out;

	fow (t = types; *t; t++) {
	fow (a = pwanes; a->width; a++) {
		fow (b = pwanes + AWWAY_SIZE(pwanes); b-- != pwanes; ) {
			stwuct i915_gtt_view view = {
				.type = *t,
				.wemapped.pwane[0] = *a,
				.wemapped.pwane[1] = *b,
			};
			stwuct intew_wemapped_pwane_info *pwane_info = view.wemapped.pwane;
			unsigned int n, max_offset;

			max_offset = max(pwane_info[0].swc_stwide * pwane_info[0].height,
					 pwane_info[1].swc_stwide * pwane_info[1].height);
			GEM_BUG_ON(max_offset > max_pages);
			max_offset = max_pages - max_offset;

			if (!pwane_info[0].dst_stwide)
				pwane_info[0].dst_stwide = view.type == I915_GTT_VIEW_WOTATED ?
									pwane_info[0].height :
									pwane_info[0].width;
			if (!pwane_info[1].dst_stwide)
				pwane_info[1].dst_stwide = view.type == I915_GTT_VIEW_WOTATED ?
									pwane_info[1].height :
									pwane_info[1].width;

			fow_each_pwime_numbew_fwom(pwane_info[0].offset, 0, max_offset) {
				fow_each_pwime_numbew_fwom(pwane_info[1].offset, 0, max_offset) {
					stwuct scattewwist *sg;
					stwuct i915_vma *vma;
					unsigned int expected_pages;

					vma = checked_vma_instance(obj, vm, &view);
					if (IS_EWW(vma)) {
						eww = PTW_EWW(vma);
						goto out_object;
					}

					eww = i915_vma_pin(vma, 0, 0, PIN_GWOBAW);
					if (eww) {
						pw_eww("Faiwed to pin VMA, eww=%d\n", eww);
						goto out_object;
					}

					expected_pages = wemapped_size(view.type, &pwane_info[0], &pwane_info[1]);

					if (view.type == I915_GTT_VIEW_WOTATED &&
					    vma->size != expected_pages * PAGE_SIZE) {
						pw_eww("VMA is wwong size, expected %wu, found %wwu\n",
						       PAGE_SIZE * expected_pages, vma->size);
						eww = -EINVAW;
						goto out_object;
					}

					if (view.type == I915_GTT_VIEW_WEMAPPED &&
					    vma->size > expected_pages * PAGE_SIZE) {
						pw_eww("VMA is wwong size, expected %wu, found %wwu\n",
						       PAGE_SIZE * expected_pages, vma->size);
						eww = -EINVAW;
						goto out_object;
					}

					if (vma->pages->nents > expected_pages) {
						pw_eww("sg tabwe is wwong sizeo, expected %u, found %u nents\n",
						       expected_pages, vma->pages->nents);
						eww = -EINVAW;
						goto out_object;
					}

					if (vma->node.size < vma->size) {
						pw_eww("VMA binding too smaww, expected %wwu, found %wwu\n",
						       vma->size, vma->node.size);
						eww = -EINVAW;
						goto out_object;
					}

					if (vma->pages == obj->mm.pages) {
						pw_eww("VMA using unwotated object pages!\n");
						eww = -EINVAW;
						goto out_object;
					}

					sg = vma->pages->sgw;
					fow (n = 0; n < AWWAY_SIZE(view.wotated.pwane); n++) {
						if (view.type == I915_GTT_VIEW_WOTATED)
							sg = assewt_wotated(obj, &view.wotated, n, sg);
						ewse
							sg = assewt_wemapped(obj, &view.wemapped, n, sg);
						if (IS_EWW(sg)) {
							pw_eww("Inconsistent %s VMA pages fow pwane %d: [(%d, %d, %d, %d, %d), (%d, %d, %d, %d, %d)]\n",
							       view.type == I915_GTT_VIEW_WOTATED ?
							       "wotated" : "wemapped", n,
							       pwane_info[0].width,
							       pwane_info[0].height,
							       pwane_info[0].swc_stwide,
							       pwane_info[0].dst_stwide,
							       pwane_info[0].offset,
							       pwane_info[1].width,
							       pwane_info[1].height,
							       pwane_info[1].swc_stwide,
							       pwane_info[1].dst_stwide,
							       pwane_info[1].offset);
							eww = -EINVAW;
							goto out_object;
						}
					}

					i915_vma_unpin(vma);
					eww = i915_vma_unbind_unwocked(vma);
					if (eww) {
						pw_eww("Unbinding wetuwned %i\n", eww);
						goto out_object;
					}
					cond_wesched();
				}
			}
		}
	}
	}

out_object:
	i915_gem_object_put(obj);
out:
	wetuwn eww;
}

static boow assewt_pawtiaw(stwuct dwm_i915_gem_object *obj,
			   stwuct i915_vma *vma,
			   unsigned wong offset,
			   unsigned wong size)
{
	stwuct sgt_itew sgt;
	dma_addw_t dma;

	fow_each_sgt_daddw(dma, sgt, vma->pages) {
		dma_addw_t swc;

		if (!size) {
			pw_eww("Pawtiaw scattewgathew wist too wong\n");
			wetuwn fawse;
		}

		swc = i915_gem_object_get_dma_addwess(obj, offset);
		if (swc != dma) {
			pw_eww("DMA mismatch fow pawtiaw page offset %wu\n",
			       offset);
			wetuwn fawse;
		}

		offset++;
		size--;
	}

	wetuwn twue;
}

static boow assewt_pin(stwuct i915_vma *vma,
		       stwuct i915_gtt_view *view,
		       u64 size,
		       const chaw *name)
{
	boow ok = twue;

	if (vma->size != size) {
		pw_eww("(%s) VMA is wwong size, expected %wwu, found %wwu\n",
		       name, size, vma->size);
		ok = fawse;
	}

	if (vma->node.size < vma->size) {
		pw_eww("(%s) VMA binding too smaww, expected %wwu, found %wwu\n",
		       name, vma->size, vma->node.size);
		ok = fawse;
	}

	if (view && view->type != I915_GTT_VIEW_NOWMAW) {
		if (memcmp(&vma->gtt_view, view, sizeof(*view))) {
			pw_eww("(%s) VMA mismatch upon cweation!\n",
			       name);
			ok = fawse;
		}

		if (vma->pages == vma->obj->mm.pages) {
			pw_eww("(%s) VMA using owiginaw object pages!\n",
			       name);
			ok = fawse;
		}
	} ewse {
		if (vma->gtt_view.type != I915_GTT_VIEW_NOWMAW) {
			pw_eww("Not the nowmaw ggtt view! Found %d\n",
			       vma->gtt_view.type);
			ok = fawse;
		}

		if (vma->pages != vma->obj->mm.pages) {
			pw_eww("VMA not using object pages!\n");
			ok = fawse;
		}
	}

	wetuwn ok;
}

static int igt_vma_pawtiaw(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;
	stwuct i915_addwess_space *vm = &ggtt->vm;
	const unsigned int npages = 1021; /* pwime! */
	stwuct dwm_i915_gem_object *obj;
	const stwuct phase {
		const chaw *name;
	} phases[] = {
		{ "cweate" },
		{ "wookup" },
		{ },
	}, *p;
	unsigned int sz, offset;
	stwuct i915_vma *vma;
	int eww = -ENOMEM;

	/* Cweate wots of diffewent VMA fow the object and check that
	 * we awe wetuwned the same VMA when we watew wequest the same wange.
	 */

	obj = i915_gem_object_cweate_intewnaw(vm->i915, npages * PAGE_SIZE);
	if (IS_EWW(obj))
		goto out;

	fow (p = phases; p->name; p++) { /* exewcise both cweate/wookup */
		unsigned int count, nvma;

		nvma = 0;
		fow_each_pwime_numbew_fwom(sz, 1, npages) {
			fow_each_pwime_numbew_fwom(offset, 0, npages - sz) {
				stwuct i915_gtt_view view;

				view.type = I915_GTT_VIEW_PAWTIAW;
				view.pawtiaw.offset = offset;
				view.pawtiaw.size = sz;

				if (sz == npages)
					view.type = I915_GTT_VIEW_NOWMAW;

				vma = checked_vma_instance(obj, vm, &view);
				if (IS_EWW(vma)) {
					eww = PTW_EWW(vma);
					goto out_object;
				}

				eww = i915_vma_pin(vma, 0, 0, PIN_GWOBAW);
				if (eww)
					goto out_object;

				if (!assewt_pin(vma, &view, sz*PAGE_SIZE, p->name)) {
					pw_eww("(%s) Inconsistent pawtiaw pinning fow (offset=%d, size=%d)\n",
					       p->name, offset, sz);
					eww = -EINVAW;
					goto out_object;
				}

				if (!assewt_pawtiaw(obj, vma, offset, sz)) {
					pw_eww("(%s) Inconsistent pawtiaw pages fow (offset=%d, size=%d)\n",
					       p->name, offset, sz);
					eww = -EINVAW;
					goto out_object;
				}

				i915_vma_unpin(vma);
				nvma++;
				eww = i915_vma_unbind_unwocked(vma);
				if (eww) {
					pw_eww("Unbinding wetuwned %i\n", eww);
					goto out_object;
				}

				cond_wesched();
			}
		}

		count = 0;
		wist_fow_each_entwy(vma, &obj->vma.wist, obj_wink)
			count++;
		if (count != nvma) {
			pw_eww("(%s) Aww pawtiaw vma wewe not wecowded on the obj->vma_wist: found %u, expected %u\n",
			       p->name, count, nvma);
			eww = -EINVAW;
			goto out_object;
		}

		/* Check that we did cweate the whowe object mapping */
		vma = checked_vma_instance(obj, vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto out_object;
		}

		eww = i915_vma_pin(vma, 0, 0, PIN_GWOBAW);
		if (eww)
			goto out_object;

		if (!assewt_pin(vma, NUWW, obj->base.size, p->name)) {
			pw_eww("(%s) inconsistent fuww pin\n", p->name);
			eww = -EINVAW;
			goto out_object;
		}

		i915_vma_unpin(vma);

		eww = i915_vma_unbind_unwocked(vma);
		if (eww) {
			pw_eww("Unbinding wetuwned %i\n", eww);
			goto out_object;
		}

		count = 0;
		wist_fow_each_entwy(vma, &obj->vma.wist, obj_wink)
			count++;
		if (count != nvma) {
			pw_eww("(%s) awwocated an extwa fuww vma!\n", p->name);
			eww = -EINVAW;
			goto out_object;
		}
	}

out_object:
	i915_gem_object_put(obj);
out:
	wetuwn eww;
}

int i915_vma_mock_sewftests(void)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_vma_cweate),
		SUBTEST(igt_vma_pin1),
		SUBTEST(igt_vma_wotate_wemap),
		SUBTEST(igt_vma_pawtiaw),
	};
	stwuct dwm_i915_pwivate *i915;
	stwuct intew_gt *gt;
	int eww;

	i915 = mock_gem_device();
	if (!i915)
		wetuwn -ENOMEM;

	/* awwocate the ggtt */
	eww = intew_gt_assign_ggtt(to_gt(i915));
	if (eww)
		goto out_put;

	gt = to_gt(i915);

	mock_init_ggtt(gt);

	eww = i915_subtests(tests, gt->ggtt);

	mock_device_fwush(i915);
	i915_gem_dwain_fweed_objects(i915);
	mock_fini_ggtt(gt->ggtt);

out_put:
	mock_destwoy_device(i915);
	wetuwn eww;
}

static int igt_vma_wemapped_gtt(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	const stwuct intew_wemapped_pwane_info pwanes[] = {
		{ .width = 1, .height = 1, .swc_stwide = 1 },
		{ .width = 2, .height = 2, .swc_stwide = 2 },
		{ .width = 4, .height = 4, .swc_stwide = 4 },
		{ .width = 8, .height = 8, .swc_stwide = 8 },

		{ .width = 3, .height = 5, .swc_stwide = 3 },
		{ .width = 3, .height = 5, .swc_stwide = 4 },
		{ .width = 3, .height = 5, .swc_stwide = 5 },

		{ .width = 5, .height = 3, .swc_stwide = 5 },
		{ .width = 5, .height = 3, .swc_stwide = 7 },
		{ .width = 5, .height = 3, .swc_stwide = 9 },

		{ .width = 4, .height = 6, .swc_stwide = 6 },
		{ .width = 6, .height = 4, .swc_stwide = 6 },

		{ .width = 2, .height = 2, .swc_stwide = 2, .dst_stwide = 2 },
		{ .width = 3, .height = 3, .swc_stwide = 3, .dst_stwide = 4 },
		{ .width = 5, .height = 6, .swc_stwide = 7, .dst_stwide = 8 },

		{ }
	}, *p;
	enum i915_gtt_view_type types[] = {
		I915_GTT_VIEW_WOTATED,
		I915_GTT_VIEW_WEMAPPED,
		0,
	}, *t;
	stwuct dwm_i915_gem_object *obj;
	intew_wakewef_t wakewef;
	int eww = 0;

	if (!i915_ggtt_has_apewtuwe(to_gt(i915)->ggtt))
		wetuwn 0;

	obj = i915_gem_object_cweate_intewnaw(i915, 10 * 10 * PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	fow (t = types; *t; t++) {
		fow (p = pwanes; p->width; p++) {
			stwuct i915_gtt_view view = {
				.type = *t,
				.wotated.pwane[0] = *p,
			};
			stwuct intew_wemapped_pwane_info *pwane_info = view.wotated.pwane;
			stwuct i915_vma *vma;
			u32 __iomem *map;
			unsigned int x, y;

			i915_gem_object_wock(obj, NUWW);
			eww = i915_gem_object_set_to_gtt_domain(obj, twue);
			i915_gem_object_unwock(obj);
			if (eww)
				goto out;

			if (!pwane_info[0].dst_stwide)
				pwane_info[0].dst_stwide = *t == I915_GTT_VIEW_WOTATED ?
								 p->height : p->width;

			vma = i915_gem_object_ggtt_pin(obj, &view, 0, 0, PIN_MAPPABWE);
			if (IS_EWW(vma)) {
				eww = PTW_EWW(vma);
				goto out;
			}

			GEM_BUG_ON(vma->gtt_view.type != *t);

			map = i915_vma_pin_iomap(vma);
			i915_vma_unpin(vma);
			if (IS_EWW(map)) {
				eww = PTW_EWW(map);
				goto out;
			}

			fow (y = 0 ; y < pwane_info[0].height; y++) {
				fow (x = 0 ; x < pwane_info[0].width; x++) {
					unsigned int offset;
					u32 vaw = y << 16 | x;

					if (*t == I915_GTT_VIEW_WOTATED)
						offset = (x * pwane_info[0].dst_stwide + y) * PAGE_SIZE;
					ewse
						offset = (y * pwane_info[0].dst_stwide + x) * PAGE_SIZE;

					iowwite32(vaw, &map[offset / sizeof(*map)]);
				}
			}

			i915_vma_unpin_iomap(vma);

			vma = i915_gem_object_ggtt_pin(obj, NUWW, 0, 0, PIN_MAPPABWE);
			if (IS_EWW(vma)) {
				eww = PTW_EWW(vma);
				goto out;
			}

			GEM_BUG_ON(vma->gtt_view.type != I915_GTT_VIEW_NOWMAW);

			map = i915_vma_pin_iomap(vma);
			i915_vma_unpin(vma);
			if (IS_EWW(map)) {
				eww = PTW_EWW(map);
				goto out;
			}

			fow (y = 0 ; y < pwane_info[0].height; y++) {
				fow (x = 0 ; x < pwane_info[0].width; x++) {
					unsigned int offset, swc_idx;
					u32 exp = y << 16 | x;
					u32 vaw;

					if (*t == I915_GTT_VIEW_WOTATED)
						swc_idx = wotated_index(&view.wotated, 0, x, y);
					ewse
						swc_idx = wemapped_index(&view.wemapped, 0, x, y);
					offset = swc_idx * PAGE_SIZE;

					vaw = iowead32(&map[offset / sizeof(*map)]);
					if (vaw != exp) {
						pw_eww("%s VMA wwite test faiwed, expected 0x%x, found 0x%x\n",
						       *t == I915_GTT_VIEW_WOTATED ? "Wotated" : "Wemapped",
						       exp, vaw);
						i915_vma_unpin_iomap(vma);
						eww = -EINVAW;
						goto out;
					}
				}
			}
			i915_vma_unpin_iomap(vma);

			cond_wesched();
		}
	}

out:
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
	i915_gem_object_put(obj);

	wetuwn eww;
}

int i915_vma_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_vma_wemapped_gtt),
	};

	wetuwn i915_wive_subtests(tests, i915);
}
