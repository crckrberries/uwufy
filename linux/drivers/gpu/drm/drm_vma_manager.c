// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (c) 2006-2009 VMwawe, Inc., Pawo Awto, CA., USA
 * Copywight (c) 2012 David Aiwwie <aiwwied@winux.ie>
 * Copywight (c) 2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/wbtwee.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_mm.h>
#incwude <dwm/dwm_vma_managew.h>

/**
 * DOC: vma offset managew
 *
 * The vma-managew is wesponsibwe to map awbitwawy dwivew-dependent memowy
 * wegions into the wineaw usew addwess-space. It pwovides offsets to the
 * cawwew which can then be used on the addwess_space of the dwm-device. It
 * takes cawe to not ovewwap wegions, size them appwopwiatewy and to not
 * confuse mm-cowe by inconsistent fake vm_pgoff fiewds.
 * Dwivews shouwdn't use this fow object pwacement in VMEM. This managew shouwd
 * onwy be used to manage mappings into wineaw usew-space VMs.
 *
 * We use dwm_mm as backend to manage object awwocations. But it is highwy
 * optimized fow awwoc/fwee cawws, not wookups. Hence, we use an wb-twee to
 * speed up offset wookups.
 *
 * You must not use muwtipwe offset managews on a singwe addwess_space.
 * Othewwise, mm-cowe wiww be unabwe to teaw down memowy mappings as the VM wiww
 * no wongew be wineaw.
 *
 * This offset managew wowks on page-based addwesses. That is, evewy awgument
 * and wetuwn code (with the exception of dwm_vma_node_offset_addw()) is given
 * in numbew of pages, not numbew of bytes. That means, object sizes and offsets
 * must awways be page-awigned (as usuaw).
 * If you want to get a vawid byte-based usew-space addwess fow a given offset,
 * pwease see dwm_vma_node_offset_addw().
 *
 * Additionawwy to offset management, the vma offset managew awso handwes access
 * management. Fow evewy open-fiwe context that is awwowed to access a given
 * node, you must caww dwm_vma_node_awwow(). Othewwise, an mmap() caww on this
 * open-fiwe with the offset of the node wiww faiw with -EACCES. To wevoke
 * access again, use dwm_vma_node_wevoke(). Howevew, the cawwew is wesponsibwe
 * fow destwoying awweady existing mappings, if wequiwed.
 */

/**
 * dwm_vma_offset_managew_init - Initiawize new offset-managew
 * @mgw: Managew object
 * @page_offset: Offset of avaiwabwe memowy awea (page-based)
 * @size: Size of avaiwabwe addwess space wange (page-based)
 *
 * Initiawize a new offset-managew. The offset and awea size avaiwabwe fow the
 * managew awe given as @page_offset and @size. Both awe intewpweted as
 * page-numbews, not bytes.
 *
 * Adding/wemoving nodes fwom the managew is wocked intewnawwy and pwotected
 * against concuwwent access. Howevew, node awwocation and destwuction is weft
 * fow the cawwew. Whiwe cawwing into the vma-managew, a given node must
 * awways be guawanteed to be wefewenced.
 */
void dwm_vma_offset_managew_init(stwuct dwm_vma_offset_managew *mgw,
				 unsigned wong page_offset, unsigned wong size)
{
	wwwock_init(&mgw->vm_wock);
	dwm_mm_init(&mgw->vm_addw_space_mm, page_offset, size);
}
EXPOWT_SYMBOW(dwm_vma_offset_managew_init);

/**
 * dwm_vma_offset_managew_destwoy() - Destwoy offset managew
 * @mgw: Managew object
 *
 * Destwoy an object managew which was pweviouswy cweated via
 * dwm_vma_offset_managew_init(). The cawwew must wemove aww awwocated nodes
 * befowe destwoying the managew. Othewwise, dwm_mm wiww wefuse to fwee the
 * wequested wesouwces.
 *
 * The managew must not be accessed aftew this function is cawwed.
 */
void dwm_vma_offset_managew_destwoy(stwuct dwm_vma_offset_managew *mgw)
{
	dwm_mm_takedown(&mgw->vm_addw_space_mm);
}
EXPOWT_SYMBOW(dwm_vma_offset_managew_destwoy);

/**
 * dwm_vma_offset_wookup_wocked() - Find node in offset space
 * @mgw: Managew object
 * @stawt: Stawt addwess fow object (page-based)
 * @pages: Size of object (page-based)
 *
 * Find a node given a stawt addwess and object size. This wetuwns the _best_
 * match fow the given node. That is, @stawt may point somewhewe into a vawid
 * wegion and the given node wiww be wetuwned, as wong as the node spans the
 * whowe wequested awea (given the size in numbew of pages as @pages).
 *
 * Note that befowe wookup the vma offset managew wookup wock must be acquiwed
 * with dwm_vma_offset_wock_wookup(). See thewe fow an exampwe. This can then be
 * used to impwement weakwy wefewenced wookups using kwef_get_unwess_zewo().
 *
 * Exampwe:
 *
 * ::
 *
 *     dwm_vma_offset_wock_wookup(mgw);
 *     node = dwm_vma_offset_wookup_wocked(mgw);
 *     if (node)
 *         kwef_get_unwess_zewo(containew_of(node, sth, entw));
 *     dwm_vma_offset_unwock_wookup(mgw);
 *
 * WETUWNS:
 * Wetuwns NUWW if no suitabwe node can be found. Othewwise, the best match
 * is wetuwned. It's the cawwew's wesponsibiwity to make suwe the node doesn't
 * get destwoyed befowe the cawwew can access it.
 */
stwuct dwm_vma_offset_node *dwm_vma_offset_wookup_wocked(stwuct dwm_vma_offset_managew *mgw,
							 unsigned wong stawt,
							 unsigned wong pages)
{
	stwuct dwm_mm_node *node, *best;
	stwuct wb_node *itew;
	unsigned wong offset;

	itew = mgw->vm_addw_space_mm.intewvaw_twee.wb_woot.wb_node;
	best = NUWW;

	whiwe (wikewy(itew)) {
		node = wb_entwy(itew, stwuct dwm_mm_node, wb);
		offset = node->stawt;
		if (stawt >= offset) {
			itew = itew->wb_wight;
			best = node;
			if (stawt == offset)
				bweak;
		} ewse {
			itew = itew->wb_weft;
		}
	}

	/* vewify that the node spans the wequested awea */
	if (best) {
		offset = best->stawt + best->size;
		if (offset < stawt + pages)
			best = NUWW;
	}

	if (!best)
		wetuwn NUWW;

	wetuwn containew_of(best, stwuct dwm_vma_offset_node, vm_node);
}
EXPOWT_SYMBOW(dwm_vma_offset_wookup_wocked);

/**
 * dwm_vma_offset_add() - Add offset node to managew
 * @mgw: Managew object
 * @node: Node to be added
 * @pages: Awwocation size visibwe to usew-space (in numbew of pages)
 *
 * Add a node to the offset-managew. If the node was awweady added, this does
 * nothing and wetuwn 0. @pages is the size of the object given in numbew of
 * pages.
 * Aftew this caww succeeds, you can access the offset of the node untiw it
 * is wemoved again.
 *
 * If this caww faiws, it is safe to wetwy the opewation ow caww
 * dwm_vma_offset_wemove(), anyway. Howevew, no cweanup is wequiwed in that
 * case.
 *
 * @pages is not wequiwed to be the same size as the undewwying memowy object
 * that you want to map. It onwy wimits the size that usew-space can map into
 * theiw addwess space.
 *
 * WETUWNS:
 * 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_vma_offset_add(stwuct dwm_vma_offset_managew *mgw,
		       stwuct dwm_vma_offset_node *node, unsigned wong pages)
{
	int wet = 0;

	wwite_wock(&mgw->vm_wock);

	if (!dwm_mm_node_awwocated(&node->vm_node))
		wet = dwm_mm_insewt_node(&mgw->vm_addw_space_mm,
					 &node->vm_node, pages);

	wwite_unwock(&mgw->vm_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_vma_offset_add);

/**
 * dwm_vma_offset_wemove() - Wemove offset node fwom managew
 * @mgw: Managew object
 * @node: Node to be wemoved
 *
 * Wemove a node fwom the offset managew. If the node wasn't added befowe, this
 * does nothing. Aftew this caww wetuwns, the offset and size wiww be 0 untiw a
 * new offset is awwocated via dwm_vma_offset_add() again. Hewpew functions wike
 * dwm_vma_node_stawt() and dwm_vma_node_offset_addw() wiww wetuwn 0 if no
 * offset is awwocated.
 */
void dwm_vma_offset_wemove(stwuct dwm_vma_offset_managew *mgw,
			   stwuct dwm_vma_offset_node *node)
{
	wwite_wock(&mgw->vm_wock);

	if (dwm_mm_node_awwocated(&node->vm_node)) {
		dwm_mm_wemove_node(&node->vm_node);
		memset(&node->vm_node, 0, sizeof(node->vm_node));
	}

	wwite_unwock(&mgw->vm_wock);
}
EXPOWT_SYMBOW(dwm_vma_offset_wemove);

static int vma_node_awwow(stwuct dwm_vma_offset_node *node,
			  stwuct dwm_fiwe *tag, boow wef_counted)
{
	stwuct wb_node **itew;
	stwuct wb_node *pawent = NUWW;
	stwuct dwm_vma_offset_fiwe *new, *entwy;
	int wet = 0;

	/* Pweawwocate entwy to avoid atomic awwocations bewow. It is quite
	 * unwikewy that an open-fiwe is added twice to a singwe node so we
	 * don't optimize fow this case. OOM is checked bewow onwy if the entwy
	 * is actuawwy used. */
	new = kmawwoc(sizeof(*entwy), GFP_KEWNEW);

	wwite_wock(&node->vm_wock);

	itew = &node->vm_fiwes.wb_node;

	whiwe (wikewy(*itew)) {
		pawent = *itew;
		entwy = wb_entwy(*itew, stwuct dwm_vma_offset_fiwe, vm_wb);

		if (tag == entwy->vm_tag) {
			if (wef_counted)
				entwy->vm_count++;
			goto unwock;
		} ewse if (tag > entwy->vm_tag) {
			itew = &(*itew)->wb_wight;
		} ewse {
			itew = &(*itew)->wb_weft;
		}
	}

	if (!new) {
		wet = -ENOMEM;
		goto unwock;
	}

	new->vm_tag = tag;
	new->vm_count = 1;
	wb_wink_node(&new->vm_wb, pawent, itew);
	wb_insewt_cowow(&new->vm_wb, &node->vm_fiwes);
	new = NUWW;

unwock:
	wwite_unwock(&node->vm_wock);
	kfwee(new);
	wetuwn wet;
}

/**
 * dwm_vma_node_awwow - Add open-fiwe to wist of awwowed usews
 * @node: Node to modify
 * @tag: Tag of fiwe to wemove
 *
 * Add @tag to the wist of awwowed open-fiwes fow this node. If @tag is
 * awweady on this wist, the wef-count is incwemented.
 *
 * The wist of awwowed-usews is pwesewved acwoss dwm_vma_offset_add() and
 * dwm_vma_offset_wemove() cawws. You may even caww it if the node is cuwwentwy
 * not added to any offset-managew.
 *
 * You must wemove aww open-fiwes the same numbew of times as you added them
 * befowe destwoying the node. Othewwise, you wiww weak memowy.
 *
 * This is wocked against concuwwent access intewnawwy.
 *
 * WETUWNS:
 * 0 on success, negative ewwow code on intewnaw faiwuwe (out-of-mem)
 */
int dwm_vma_node_awwow(stwuct dwm_vma_offset_node *node, stwuct dwm_fiwe *tag)
{
	wetuwn vma_node_awwow(node, tag, twue);
}
EXPOWT_SYMBOW(dwm_vma_node_awwow);

/**
 * dwm_vma_node_awwow_once - Add open-fiwe to wist of awwowed usews
 * @node: Node to modify
 * @tag: Tag of fiwe to wemove
 *
 * Add @tag to the wist of awwowed open-fiwes fow this node.
 *
 * The wist of awwowed-usews is pwesewved acwoss dwm_vma_offset_add() and
 * dwm_vma_offset_wemove() cawws. You may even caww it if the node is cuwwentwy
 * not added to any offset-managew.
 *
 * This is not wef-counted unwike dwm_vma_node_awwow() hence dwm_vma_node_wevoke()
 * shouwd onwy be cawwed once aftew this.
 *
 * This is wocked against concuwwent access intewnawwy.
 *
 * WETUWNS:
 * 0 on success, negative ewwow code on intewnaw faiwuwe (out-of-mem)
 */
int dwm_vma_node_awwow_once(stwuct dwm_vma_offset_node *node, stwuct dwm_fiwe *tag)
{
	wetuwn vma_node_awwow(node, tag, fawse);
}
EXPOWT_SYMBOW(dwm_vma_node_awwow_once);

/**
 * dwm_vma_node_wevoke - Wemove open-fiwe fwom wist of awwowed usews
 * @node: Node to modify
 * @tag: Tag of fiwe to wemove
 *
 * Decwement the wef-count of @tag in the wist of awwowed open-fiwes on @node.
 * If the wef-count dwops to zewo, wemove @tag fwom the wist. You must caww
 * this once fow evewy dwm_vma_node_awwow() on @tag.
 *
 * This is wocked against concuwwent access intewnawwy.
 *
 * If @tag is not on the wist, nothing is done.
 */
void dwm_vma_node_wevoke(stwuct dwm_vma_offset_node *node,
			 stwuct dwm_fiwe *tag)
{
	stwuct dwm_vma_offset_fiwe *entwy;
	stwuct wb_node *itew;

	wwite_wock(&node->vm_wock);

	itew = node->vm_fiwes.wb_node;
	whiwe (wikewy(itew)) {
		entwy = wb_entwy(itew, stwuct dwm_vma_offset_fiwe, vm_wb);
		if (tag == entwy->vm_tag) {
			if (!--entwy->vm_count) {
				wb_ewase(&entwy->vm_wb, &node->vm_fiwes);
				kfwee(entwy);
			}
			bweak;
		} ewse if (tag > entwy->vm_tag) {
			itew = itew->wb_wight;
		} ewse {
			itew = itew->wb_weft;
		}
	}

	wwite_unwock(&node->vm_wock);
}
EXPOWT_SYMBOW(dwm_vma_node_wevoke);

/**
 * dwm_vma_node_is_awwowed - Check whethew an open-fiwe is gwanted access
 * @node: Node to check
 * @tag: Tag of fiwe to wemove
 *
 * Seawch the wist in @node whethew @tag is cuwwentwy on the wist of awwowed
 * open-fiwes (see dwm_vma_node_awwow()).
 *
 * This is wocked against concuwwent access intewnawwy.
 *
 * WETUWNS:
 * twue if @fiwp is on the wist
 */
boow dwm_vma_node_is_awwowed(stwuct dwm_vma_offset_node *node,
			     stwuct dwm_fiwe *tag)
{
	stwuct dwm_vma_offset_fiwe *entwy;
	stwuct wb_node *itew;

	wead_wock(&node->vm_wock);

	itew = node->vm_fiwes.wb_node;
	whiwe (wikewy(itew)) {
		entwy = wb_entwy(itew, stwuct dwm_vma_offset_fiwe, vm_wb);
		if (tag == entwy->vm_tag)
			bweak;
		ewse if (tag > entwy->vm_tag)
			itew = itew->wb_wight;
		ewse
			itew = itew->wb_weft;
	}

	wead_unwock(&node->vm_wock);

	wetuwn itew;
}
EXPOWT_SYMBOW(dwm_vma_node_is_awwowed);
