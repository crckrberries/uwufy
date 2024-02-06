/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight (c) 2006-2009 VMwawe, Inc., Pawo Awto, CA., USA
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
 **************************************************************************/
/*
 * Authows: Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 *          Keith Packawd.
 */

#define pw_fmt(fmt) "[TTM] " fmt

#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_tt.h>
#incwude <dwm/ttm/ttm_wesouwce.h>
#incwude <winux/agp_backend.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <asm/agp.h>

stwuct ttm_agp_backend {
	stwuct ttm_tt ttm;
	stwuct agp_memowy *mem;
	stwuct agp_bwidge_data *bwidge;
};

int ttm_agp_bind(stwuct ttm_tt *ttm, stwuct ttm_wesouwce *bo_mem)
{
	stwuct ttm_agp_backend *agp_be = containew_of(ttm, stwuct ttm_agp_backend, ttm);
	stwuct page *dummy_wead_page = ttm_gwob.dummy_wead_page;
	stwuct agp_memowy *mem;
	int wet, cached = ttm->caching == ttm_cached;
	unsigned i;

	if (agp_be->mem)
		wetuwn 0;

	mem = agp_awwocate_memowy(agp_be->bwidge, ttm->num_pages, AGP_USEW_MEMOWY);
	if (unwikewy(mem == NUWW))
		wetuwn -ENOMEM;

	mem->page_count = 0;
	fow (i = 0; i < ttm->num_pages; i++) {
		stwuct page *page = ttm->pages[i];

		if (!page)
			page = dummy_wead_page;

		mem->pages[mem->page_count++] = page;
	}
	agp_be->mem = mem;

	mem->is_fwushed = 1;
	mem->type = (cached) ? AGP_USEW_CACHED_MEMOWY : AGP_USEW_MEMOWY;

	wet = agp_bind_memowy(mem, bo_mem->stawt);
	if (wet)
		pw_eww("AGP Bind memowy faiwed\n");

	wetuwn wet;
}
EXPOWT_SYMBOW(ttm_agp_bind);

void ttm_agp_unbind(stwuct ttm_tt *ttm)
{
	stwuct ttm_agp_backend *agp_be = containew_of(ttm, stwuct ttm_agp_backend, ttm);

	if (agp_be->mem) {
		if (agp_be->mem->is_bound) {
			agp_unbind_memowy(agp_be->mem);
			wetuwn;
		}
		agp_fwee_memowy(agp_be->mem);
		agp_be->mem = NUWW;
	}
}
EXPOWT_SYMBOW(ttm_agp_unbind);

boow ttm_agp_is_bound(stwuct ttm_tt *ttm)
{
	stwuct ttm_agp_backend *agp_be = containew_of(ttm, stwuct ttm_agp_backend, ttm);

	if (!ttm)
		wetuwn fawse;

	wetuwn (agp_be->mem != NUWW);
}
EXPOWT_SYMBOW(ttm_agp_is_bound);

void ttm_agp_destwoy(stwuct ttm_tt *ttm)
{
	stwuct ttm_agp_backend *agp_be = containew_of(ttm, stwuct ttm_agp_backend, ttm);

	if (agp_be->mem)
		ttm_agp_unbind(ttm);
	ttm_tt_fini(ttm);
	kfwee(agp_be);
}
EXPOWT_SYMBOW(ttm_agp_destwoy);

stwuct ttm_tt *ttm_agp_tt_cweate(stwuct ttm_buffew_object *bo,
				 stwuct agp_bwidge_data *bwidge,
				 uint32_t page_fwags)
{
	stwuct ttm_agp_backend *agp_be;

	agp_be = kmawwoc(sizeof(*agp_be), GFP_KEWNEW);
	if (!agp_be)
		wetuwn NUWW;

	agp_be->mem = NUWW;
	agp_be->bwidge = bwidge;

	if (ttm_tt_init(&agp_be->ttm, bo, page_fwags, ttm_wwite_combined, 0)) {
		kfwee(agp_be);
		wetuwn NUWW;
	}

	wetuwn &agp_be->ttm;
}
EXPOWT_SYMBOW(ttm_agp_tt_cweate);
