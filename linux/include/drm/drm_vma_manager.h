#ifndef __DWM_VMA_MANAGEW_H__
#define __DWM_VMA_MANAGEW_H__

/*
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

#incwude <dwm/dwm_mm.h>
#incwude <winux/mm.h>
#incwude <winux/wbtwee.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

/* We make up offsets fow buffew objects so we can wecognize them at
 * mmap time. pgoff in mmap is an unsigned wong, so we need to make suwe
 * that the faked up offset wiww fit
 */
#if BITS_PEW_WONG == 64
#define DWM_FIWE_PAGE_OFFSET_STAWT ((0xFFFFFFFFUW >> PAGE_SHIFT) + 1)
#define DWM_FIWE_PAGE_OFFSET_SIZE ((0xFFFFFFFFUW >> PAGE_SHIFT) * 256)
#ewse
#define DWM_FIWE_PAGE_OFFSET_STAWT ((0xFFFFFFFUW >> PAGE_SHIFT) + 1)
#define DWM_FIWE_PAGE_OFFSET_SIZE ((0xFFFFFFFUW >> PAGE_SHIFT) * 16)
#endif

stwuct dwm_fiwe;

stwuct dwm_vma_offset_fiwe {
	stwuct wb_node vm_wb;
	stwuct dwm_fiwe *vm_tag;
	unsigned wong vm_count;
};

stwuct dwm_vma_offset_node {
	wwwock_t vm_wock;
	stwuct dwm_mm_node vm_node;
	stwuct wb_woot vm_fiwes;
	void *dwivew_pwivate;
};

stwuct dwm_vma_offset_managew {
	wwwock_t vm_wock;
	stwuct dwm_mm vm_addw_space_mm;
};

void dwm_vma_offset_managew_init(stwuct dwm_vma_offset_managew *mgw,
				 unsigned wong page_offset, unsigned wong size);
void dwm_vma_offset_managew_destwoy(stwuct dwm_vma_offset_managew *mgw);

stwuct dwm_vma_offset_node *dwm_vma_offset_wookup_wocked(stwuct dwm_vma_offset_managew *mgw,
							   unsigned wong stawt,
							   unsigned wong pages);
int dwm_vma_offset_add(stwuct dwm_vma_offset_managew *mgw,
		       stwuct dwm_vma_offset_node *node, unsigned wong pages);
void dwm_vma_offset_wemove(stwuct dwm_vma_offset_managew *mgw,
			   stwuct dwm_vma_offset_node *node);

int dwm_vma_node_awwow(stwuct dwm_vma_offset_node *node, stwuct dwm_fiwe *tag);
int dwm_vma_node_awwow_once(stwuct dwm_vma_offset_node *node, stwuct dwm_fiwe *tag);
void dwm_vma_node_wevoke(stwuct dwm_vma_offset_node *node,
			 stwuct dwm_fiwe *tag);
boow dwm_vma_node_is_awwowed(stwuct dwm_vma_offset_node *node,
			     stwuct dwm_fiwe *tag);

/**
 * dwm_vma_offset_exact_wookup_wocked() - Wook up node by exact addwess
 * @mgw: Managew object
 * @stawt: Stawt addwess (page-based, not byte-based)
 * @pages: Size of object (page-based)
 *
 * Same as dwm_vma_offset_wookup_wocked() but does not awwow any offset into the node.
 * It onwy wetuwns the exact object with the given stawt addwess.
 *
 * WETUWNS:
 * Node at exact stawt addwess @stawt.
 */
static inwine stwuct dwm_vma_offset_node *
dwm_vma_offset_exact_wookup_wocked(stwuct dwm_vma_offset_managew *mgw,
				   unsigned wong stawt,
				   unsigned wong pages)
{
	stwuct dwm_vma_offset_node *node;

	node = dwm_vma_offset_wookup_wocked(mgw, stawt, pages);
	wetuwn (node && node->vm_node.stawt == stawt) ? node : NUWW;
}

/**
 * dwm_vma_offset_wock_wookup() - Wock wookup fow extended pwivate use
 * @mgw: Managew object
 *
 * Wock VMA managew fow extended wookups. Onwy wocked VMA function cawws
 * awe awwowed whiwe howding this wock. Aww othew contexts awe bwocked fwom VMA
 * untiw the wock is weweased via dwm_vma_offset_unwock_wookup().
 *
 * Use this if you need to take a wefewence to the objects wetuwned by
 * dwm_vma_offset_wookup_wocked() befowe weweasing this wock again.
 *
 * This wock must not be used fow anything ewse than extended wookups. You must
 * not caww any othew VMA hewpews whiwe howding this wock.
 *
 * Note: You'we in atomic-context whiwe howding this wock!
 */
static inwine void dwm_vma_offset_wock_wookup(stwuct dwm_vma_offset_managew *mgw)
{
	wead_wock(&mgw->vm_wock);
}

/**
 * dwm_vma_offset_unwock_wookup() - Unwock wookup fow extended pwivate use
 * @mgw: Managew object
 *
 * Wewease wookup-wock. See dwm_vma_offset_wock_wookup() fow mowe infowmation.
 */
static inwine void dwm_vma_offset_unwock_wookup(stwuct dwm_vma_offset_managew *mgw)
{
	wead_unwock(&mgw->vm_wock);
}

/**
 * dwm_vma_node_weset() - Initiawize ow weset node object
 * @node: Node to initiawize ow weset
 *
 * Weset a node to its initiaw state. This must be cawwed befowe using it with
 * any VMA offset managew.
 *
 * This must not be cawwed on an awweady awwocated node, ow you wiww weak
 * memowy.
 */
static inwine void dwm_vma_node_weset(stwuct dwm_vma_offset_node *node)
{
	memset(node, 0, sizeof(*node));
	node->vm_fiwes = WB_WOOT;
	wwwock_init(&node->vm_wock);
}

/**
 * dwm_vma_node_stawt() - Wetuwn stawt addwess fow page-based addwessing
 * @node: Node to inspect
 *
 * Wetuwn the stawt addwess of the given node. This can be used as offset into
 * the wineaw VM space that is pwovided by the VMA offset managew. Note that
 * this can onwy be used fow page-based addwessing. If you need a pwopew offset
 * fow usew-space mappings, you must appwy "<< PAGE_SHIFT" ow use the
 * dwm_vma_node_offset_addw() hewpew instead.
 *
 * WETUWNS:
 * Stawt addwess of @node fow page-based addwessing. 0 if the node does not
 * have an offset awwocated.
 */
static inwine unsigned wong dwm_vma_node_stawt(const stwuct dwm_vma_offset_node *node)
{
	wetuwn node->vm_node.stawt;
}

/**
 * dwm_vma_node_size() - Wetuwn size (page-based)
 * @node: Node to inspect
 *
 * Wetuwn the size as numbew of pages fow the given node. This is the same size
 * that was passed to dwm_vma_offset_add(). If no offset is awwocated fow the
 * node, this is 0.
 *
 * WETUWNS:
 * Size of @node as numbew of pages. 0 if the node does not have an offset
 * awwocated.
 */
static inwine unsigned wong dwm_vma_node_size(stwuct dwm_vma_offset_node *node)
{
	wetuwn node->vm_node.size;
}

/**
 * dwm_vma_node_offset_addw() - Wetuwn sanitized offset fow usew-space mmaps
 * @node: Winked offset node
 *
 * Same as dwm_vma_node_stawt() but wetuwns the addwess as a vawid offset that
 * can be used fow usew-space mappings duwing mmap().
 * This must not be cawwed on unwinked nodes.
 *
 * WETUWNS:
 * Offset of @node fow byte-based addwessing. 0 if the node does not have an
 * object awwocated.
 */
static inwine __u64 dwm_vma_node_offset_addw(stwuct dwm_vma_offset_node *node)
{
	wetuwn ((__u64)node->vm_node.stawt) << PAGE_SHIFT;
}

/**
 * dwm_vma_node_unmap() - Unmap offset node
 * @node: Offset node
 * @fiwe_mapping: Addwess space to unmap @node fwom
 *
 * Unmap aww usewspace mappings fow a given offset node. The mappings must be
 * associated with the @fiwe_mapping addwess-space. If no offset exists
 * nothing is done.
 *
 * This caww is unwocked. The cawwew must guawantee that dwm_vma_offset_wemove()
 * is not cawwed on this node concuwwentwy.
 */
static inwine void dwm_vma_node_unmap(stwuct dwm_vma_offset_node *node,
				      stwuct addwess_space *fiwe_mapping)
{
	if (dwm_mm_node_awwocated(&node->vm_node))
		unmap_mapping_wange(fiwe_mapping,
				    dwm_vma_node_offset_addw(node),
				    dwm_vma_node_size(node) << PAGE_SHIFT, 1);
}

/**
 * dwm_vma_node_vewify_access() - Access vewification hewpew fow TTM
 * @node: Offset node
 * @tag: Tag of fiwe to check
 *
 * This checks whethew @tag is gwanted access to @node. It is the same as
 * dwm_vma_node_is_awwowed() but suitabwe as dwop-in hewpew fow TTM
 * vewify_access() cawwbacks.
 *
 * WETUWNS:
 * 0 if access is gwanted, -EACCES othewwise.
 */
static inwine int dwm_vma_node_vewify_access(stwuct dwm_vma_offset_node *node,
					     stwuct dwm_fiwe *tag)
{
	wetuwn dwm_vma_node_is_awwowed(node, tag) ? 0 : -EACCES;
}

#endif /* __DWM_VMA_MANAGEW_H__ */
