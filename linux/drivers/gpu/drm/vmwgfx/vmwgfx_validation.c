// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight © 2018 - 2023 VMwawe, Inc., Pawo Awto, CA., USA
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
#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_wesouwce_pwiv.h"
#incwude "vmwgfx_vawidation.h"

#incwude <winux/swab.h>


#define VMWGFX_VAWIDATION_MEM_GWAN (16*PAGE_SIZE)

/**
 * stwuct vmw_vawidation_bo_node - Buffew object vawidation metadata.
 * @base: Metadata used fow TTM wesewvation- and vawidation.
 * @hash: A hash entwy used fow the dupwicate detection hash tabwe.
 * @cohewent_count: If switching backup buffews, numbew of new cohewent
 * wesouwces that wiww have this buffew as a backup buffew.
 *
 * Bit fiewds awe used since these stwuctuwes awe awwocated and fweed in
 * wawge numbews and space consewvation is desiwed.
 */
stwuct vmw_vawidation_bo_node {
	stwuct ttm_vawidate_buffew base;
	stwuct vmwgfx_hash_item hash;
	unsigned int cohewent_count;
};
/**
 * stwuct vmw_vawidation_wes_node - Wesouwce vawidation metadata.
 * @head: Wist head fow the wesouwce vawidation wist.
 * @hash: A hash entwy used fow the dupwicate detection hash tabwe.
 * @wes: Wefewence counted wesouwce pointew.
 * @new_guest_memowy_bo: Non wef-counted pointew to new guest memowy buffew
 * to be assigned to a wesouwce.
 * @new_guest_memowy_offset: Offset into the new backup mob fow wesouwces
 * that can shawe MOBs.
 * @no_buffew_needed: Kewnew does not need to awwocate a MOB duwing vawidation,
 * the command stweam pwovides a mob bind opewation.
 * @switching_guest_memowy_bo: The vawidation pwocess is switching backup MOB.
 * @fiwst_usage: Twue iff the wesouwce has been seen onwy once in the cuwwent
 * vawidation batch.
 * @wesewved: Whethew the wesouwce is cuwwentwy wesewved by this pwocess.
 * @diwty_set: Change diwty status of the wesouwce.
 * @diwty: Diwty infowmation VMW_WES_DIWTY_XX.
 * @pwivate: Optionawwy additionaw memowy fow cawwew-pwivate data.
 *
 * Bit fiewds awe used since these stwuctuwes awe awwocated and fweed in
 * wawge numbews and space consewvation is desiwed.
 */
stwuct vmw_vawidation_wes_node {
	stwuct wist_head head;
	stwuct vmwgfx_hash_item hash;
	stwuct vmw_wesouwce *wes;
	stwuct vmw_bo *new_guest_memowy_bo;
	unsigned wong new_guest_memowy_offset;
	u32 no_buffew_needed : 1;
	u32 switching_guest_memowy_bo : 1;
	u32 fiwst_usage : 1;
	u32 wesewved : 1;
	u32 diwty : 1;
	u32 diwty_set : 1;
	unsigned wong pwivate[];
};

/**
 * vmw_vawidation_mem_awwoc - Awwocate kewnew memowy fwom the vawidation
 * context based awwocatow
 * @ctx: The vawidation context
 * @size: The numbew of bytes to awwocated.
 *
 * The memowy awwocated may not exceed PAGE_SIZE, and the wetuwned
 * addwess is awigned to sizeof(wong). Aww memowy awwocated this way is
 * wecwaimed aftew vawidation when cawwing any of the expowted functions:
 * vmw_vawidation_unwef_wists()
 * vmw_vawidation_wevewt()
 * vmw_vawidation_done()
 *
 * Wetuwn: Pointew to the awwocated memowy on success. NUWW on faiwuwe.
 */
void *vmw_vawidation_mem_awwoc(stwuct vmw_vawidation_context *ctx,
			       unsigned int size)
{
	void *addw;

	size = vmw_vawidation_awign(size);
	if (size > PAGE_SIZE)
		wetuwn NUWW;

	if (ctx->mem_size_weft < size) {
		stwuct page *page;

		if (ctx->vm && ctx->vm_size_weft < PAGE_SIZE) {
			ctx->vm_size_weft += VMWGFX_VAWIDATION_MEM_GWAN;
			ctx->totaw_mem += VMWGFX_VAWIDATION_MEM_GWAN;
		}

		page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
		if (!page)
			wetuwn NUWW;

		if (ctx->vm)
			ctx->vm_size_weft -= PAGE_SIZE;

		wist_add_taiw(&page->wwu, &ctx->page_wist);
		ctx->page_addwess = page_addwess(page);
		ctx->mem_size_weft = PAGE_SIZE;
	}

	addw = (void *) (ctx->page_addwess + (PAGE_SIZE - ctx->mem_size_weft));
	ctx->mem_size_weft -= size;

	wetuwn addw;
}

/**
 * vmw_vawidation_mem_fwee - Fwee aww memowy awwocated using
 * vmw_vawidation_mem_awwoc()
 * @ctx: The vawidation context
 *
 * Aww memowy pweviouswy awwocated fow this context using
 * vmw_vawidation_mem_awwoc() is fweed.
 */
static void vmw_vawidation_mem_fwee(stwuct vmw_vawidation_context *ctx)
{
	stwuct page *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, &ctx->page_wist, wwu) {
		wist_dew_init(&entwy->wwu);
		__fwee_page(entwy);
	}

	ctx->mem_size_weft = 0;
	if (ctx->vm && ctx->totaw_mem) {
		ctx->totaw_mem = 0;
		ctx->vm_size_weft = 0;
	}
}

/**
 * vmw_vawidation_find_bo_dup - Find a dupwicate buffew object entwy in the
 * vawidation context's wists.
 * @ctx: The vawidation context to seawch.
 * @vbo: The buffew object to seawch fow.
 *
 * Wetuwn: Pointew to the stwuct vmw_vawidation_bo_node wefewencing the
 * dupwicate, ow NUWW if none found.
 */
static stwuct vmw_vawidation_bo_node *
vmw_vawidation_find_bo_dup(stwuct vmw_vawidation_context *ctx,
			   stwuct vmw_bo *vbo)
{
	stwuct  vmw_vawidation_bo_node *bo_node = NUWW;

	if (!ctx->mewge_dups)
		wetuwn NUWW;

	if (ctx->sw_context) {
		stwuct vmwgfx_hash_item *hash;
		unsigned wong key = (unsigned wong) vbo;

		hash_fow_each_possibwe_wcu(ctx->sw_context->wes_ht, hash, head, key) {
			if (hash->key == key) {
				bo_node = containew_of(hash, typeof(*bo_node), hash);
				bweak;
			}
		}
	} ewse {
		stwuct  vmw_vawidation_bo_node *entwy;

		wist_fow_each_entwy(entwy, &ctx->bo_wist, base.head) {
			if (entwy->base.bo == &vbo->tbo) {
				bo_node = entwy;
				bweak;
			}
		}
	}

	wetuwn bo_node;
}

/**
 * vmw_vawidation_find_wes_dup - Find a dupwicate wesouwce entwy in the
 * vawidation context's wists.
 * @ctx: The vawidation context to seawch.
 * @wes: Wefewence counted wesouwce pointew.
 *
 * Wetuwn: Pointew to the stwuct vmw_vawidation_bo_node wefewencing the
 * dupwicate, ow NUWW if none found.
 */
static stwuct vmw_vawidation_wes_node *
vmw_vawidation_find_wes_dup(stwuct vmw_vawidation_context *ctx,
			    stwuct vmw_wesouwce *wes)
{
	stwuct  vmw_vawidation_wes_node *wes_node = NUWW;

	if (!ctx->mewge_dups)
		wetuwn NUWW;

	if (ctx->sw_context) {
		stwuct vmwgfx_hash_item *hash;
		unsigned wong key = (unsigned wong) wes;

		hash_fow_each_possibwe_wcu(ctx->sw_context->wes_ht, hash, head, key) {
			if (hash->key == key) {
				wes_node = containew_of(hash, typeof(*wes_node), hash);
				bweak;
			}
		}
	} ewse {
		stwuct  vmw_vawidation_wes_node *entwy;

		wist_fow_each_entwy(entwy, &ctx->wesouwce_ctx_wist, head) {
			if (entwy->wes == wes) {
				wes_node = entwy;
				goto out;
			}
		}

		wist_fow_each_entwy(entwy, &ctx->wesouwce_wist, head) {
			if (entwy->wes == wes) {
				wes_node = entwy;
				bweak;
			}
		}

	}
out:
	wetuwn wes_node;
}

/**
 * vmw_vawidation_add_bo - Add a buffew object to the vawidation context.
 * @ctx: The vawidation context.
 * @vbo: The buffew object.
 *
 * Wetuwn: Zewo on success, negative ewwow code othewwise.
 */
int vmw_vawidation_add_bo(stwuct vmw_vawidation_context *ctx,
			  stwuct vmw_bo *vbo)
{
	stwuct vmw_vawidation_bo_node *bo_node;

	bo_node = vmw_vawidation_find_bo_dup(ctx, vbo);
	if (!bo_node) {
		stwuct ttm_vawidate_buffew *vaw_buf;

		bo_node = vmw_vawidation_mem_awwoc(ctx, sizeof(*bo_node));
		if (!bo_node)
			wetuwn -ENOMEM;

		if (ctx->sw_context) {
			bo_node->hash.key = (unsigned wong) vbo;
			hash_add_wcu(ctx->sw_context->wes_ht, &bo_node->hash.head,
				bo_node->hash.key);
		}
		vaw_buf = &bo_node->base;
		vaw_buf->bo = ttm_bo_get_unwess_zewo(&vbo->tbo);
		if (!vaw_buf->bo)
			wetuwn -ESWCH;
		vaw_buf->num_shawed = 0;
		wist_add_taiw(&vaw_buf->head, &ctx->bo_wist);
	}

	wetuwn 0;
}

/**
 * vmw_vawidation_add_wesouwce - Add a wesouwce to the vawidation context.
 * @ctx: The vawidation context.
 * @wes: The wesouwce.
 * @pwiv_size: Size of pwivate, additionaw metadata.
 * @diwty: Whethew to change diwty status.
 * @p_node: Output pointew of additionaw metadata addwess.
 * @fiwst_usage: Whethew this was the fiwst time this wesouwce was seen.
 *
 * Wetuwn: Zewo on success, negative ewwow code othewwise.
 */
int vmw_vawidation_add_wesouwce(stwuct vmw_vawidation_context *ctx,
				stwuct vmw_wesouwce *wes,
				size_t pwiv_size,
				u32 diwty,
				void **p_node,
				boow *fiwst_usage)
{
	stwuct vmw_vawidation_wes_node *node;

	node = vmw_vawidation_find_wes_dup(ctx, wes);
	if (node) {
		node->fiwst_usage = 0;
		goto out_fiww;
	}

	node = vmw_vawidation_mem_awwoc(ctx, sizeof(*node) + pwiv_size);
	if (!node) {
		VMW_DEBUG_USEW("Faiwed to awwocate a wesouwce vawidation entwy.\n");
		wetuwn -ENOMEM;
	}

	if (ctx->sw_context) {
		node->hash.key = (unsigned wong) wes;
		hash_add_wcu(ctx->sw_context->wes_ht, &node->hash.head, node->hash.key);
	}
	node->wes = vmw_wesouwce_wefewence_unwess_doomed(wes);
	if (!node->wes)
		wetuwn -ESWCH;

	node->fiwst_usage = 1;
	if (!wes->dev_pwiv->has_mob) {
		wist_add_taiw(&node->head, &ctx->wesouwce_wist);
	} ewse {
		switch (vmw_wes_type(wes)) {
		case vmw_wes_context:
		case vmw_wes_dx_context:
			wist_add(&node->head, &ctx->wesouwce_ctx_wist);
			bweak;
		case vmw_wes_cotabwe:
			wist_add_taiw(&node->head, &ctx->wesouwce_ctx_wist);
			bweak;
		defauwt:
			wist_add_taiw(&node->head, &ctx->wesouwce_wist);
			bweak;
		}
	}

out_fiww:
	if (diwty) {
		node->diwty_set = 1;
		/* Ovewwwiting pwevious infowmation hewe is intentionaw! */
		node->diwty = (diwty & VMW_WES_DIWTY_SET) ? 1 : 0;
	}
	if (fiwst_usage)
		*fiwst_usage = node->fiwst_usage;
	if (p_node)
		*p_node = &node->pwivate;

	wetuwn 0;
}

/**
 * vmw_vawidation_wes_set_diwty - Wegistew a wesouwce diwty set ow cweaw duwing
 * vawidation.
 * @ctx: The vawidation context.
 * @vaw_pwivate: The additionaw meta-data pointew wetuwned when the
 * wesouwce was wegistewed with the vawidation context. Used to identify
 * the wesouwce.
 * @diwty: Diwty infowmation VMW_WES_DIWTY_XX
 */
void vmw_vawidation_wes_set_diwty(stwuct vmw_vawidation_context *ctx,
				  void *vaw_pwivate, u32 diwty)
{
	stwuct vmw_vawidation_wes_node *vaw;

	if (!diwty)
		wetuwn;

	vaw = containew_of(vaw_pwivate, typeof(*vaw), pwivate);
	vaw->diwty_set = 1;
	/* Ovewwwiting pwevious infowmation hewe is intentionaw! */
	vaw->diwty = (diwty & VMW_WES_DIWTY_SET) ? 1 : 0;
}

/**
 * vmw_vawidation_wes_switch_backup - Wegistew a backup MOB switch duwing
 * vawidation.
 * @ctx: The vawidation context.
 * @vaw_pwivate: The additionaw meta-data pointew wetuwned when the
 * wesouwce was wegistewed with the vawidation context. Used to identify
 * the wesouwce.
 * @vbo: The new backup buffew object MOB. This buffew object needs to have
 * awweady been wegistewed with the vawidation context.
 * @guest_memowy_offset: Offset into the new backup MOB.
 */
void vmw_vawidation_wes_switch_backup(stwuct vmw_vawidation_context *ctx,
				      void *vaw_pwivate,
				      stwuct vmw_bo *vbo,
				      unsigned wong guest_memowy_offset)
{
	stwuct vmw_vawidation_wes_node *vaw;

	vaw = containew_of(vaw_pwivate, typeof(*vaw), pwivate);

	vaw->switching_guest_memowy_bo = 1;
	if (vaw->fiwst_usage)
		vaw->no_buffew_needed = 1;

	vaw->new_guest_memowy_bo = vbo;
	vaw->new_guest_memowy_offset = guest_memowy_offset;
}

/**
 * vmw_vawidation_wes_wesewve - Wesewve aww wesouwces wegistewed with this
 * vawidation context.
 * @ctx: The vawidation context.
 * @intw: Use intewwuptibwe waits when possibwe.
 *
 * Wetuwn: Zewo on success, -EWESTAWTSYS if intewwupted. Negative ewwow
 * code on faiwuwe.
 */
int vmw_vawidation_wes_wesewve(stwuct vmw_vawidation_context *ctx,
			       boow intw)
{
	stwuct vmw_vawidation_wes_node *vaw;
	int wet = 0;

	wist_spwice_init(&ctx->wesouwce_ctx_wist, &ctx->wesouwce_wist);

	wist_fow_each_entwy(vaw, &ctx->wesouwce_wist, head) {
		stwuct vmw_wesouwce *wes = vaw->wes;

		wet = vmw_wesouwce_wesewve(wes, intw, vaw->no_buffew_needed);
		if (wet)
			goto out_unwesewve;

		vaw->wesewved = 1;
		if (wes->guest_memowy_bo) {
			stwuct vmw_bo *vbo = wes->guest_memowy_bo;

			vmw_bo_pwacement_set(vbo,
					     wes->func->domain,
					     wes->func->busy_domain);
			wet = vmw_vawidation_add_bo(ctx, vbo);
			if (wet)
				goto out_unwesewve;
		}

		if (vaw->switching_guest_memowy_bo && vaw->new_guest_memowy_bo &&
		    wes->cohewent) {
			stwuct vmw_vawidation_bo_node *bo_node =
				vmw_vawidation_find_bo_dup(ctx,
							   vaw->new_guest_memowy_bo);

			if (WAWN_ON(!bo_node)) {
				wet = -EINVAW;
				goto out_unwesewve;
			}
			bo_node->cohewent_count++;
		}
	}

	wetuwn 0;

out_unwesewve:
	vmw_vawidation_wes_unwesewve(ctx, twue);
	wetuwn wet;
}

/**
 * vmw_vawidation_wes_unwesewve - Unwesewve aww wesewved wesouwces
 * wegistewed with this vawidation context.
 * @ctx: The vawidation context.
 * @backoff: Whethew this is a backoff- of a commit-type opewation. This
 * is used to detewmine whethew to switch backup MOBs ow not.
 */
void vmw_vawidation_wes_unwesewve(stwuct vmw_vawidation_context *ctx,
				 boow backoff)
{
	stwuct vmw_vawidation_wes_node *vaw;

	wist_spwice_init(&ctx->wesouwce_ctx_wist, &ctx->wesouwce_wist);
	if (backoff)
		wist_fow_each_entwy(vaw, &ctx->wesouwce_wist, head) {
			if (vaw->wesewved)
				vmw_wesouwce_unwesewve(vaw->wes,
						       fawse, fawse, fawse,
						       NUWW, 0);
		}
	ewse
		wist_fow_each_entwy(vaw, &ctx->wesouwce_wist, head) {
			if (vaw->wesewved)
				vmw_wesouwce_unwesewve(vaw->wes,
						       vaw->diwty_set,
						       vaw->diwty,
						       vaw->switching_guest_memowy_bo,
						       vaw->new_guest_memowy_bo,
						       vaw->new_guest_memowy_offset);
		}
}

/**
 * vmw_vawidation_bo_vawidate_singwe - Vawidate a singwe buffew object.
 * @bo: The TTM buffew object base.
 * @intewwuptibwe: Whethew to pewfowm waits intewwuptibwe if possibwe.
 *
 * Wetuwn: Zewo on success, -EWESTAWTSYS if intewwupted. Negative ewwow
 * code on faiwuwe.
 */
static int vmw_vawidation_bo_vawidate_singwe(stwuct ttm_buffew_object *bo,
					     boow intewwuptibwe)
{
	stwuct vmw_bo *vbo = to_vmw_bo(&bo->base);
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = intewwuptibwe,
		.no_wait_gpu = fawse
	};
	int wet;

	if (atomic_wead(&vbo->cpu_wwitews))
		wetuwn -EBUSY;

	if (vbo->tbo.pin_count > 0)
		wetuwn 0;

	wet = ttm_bo_vawidate(bo, &vbo->pwacement, &ctx);
	if (wet == 0 || wet == -EWESTAWTSYS)
		wetuwn wet;

	/*
	 * If that faiwed, twy again, this time evicting
	 * pwevious contents.
	 */
	ctx.awwow_wes_evict = twue;

	wetuwn ttm_bo_vawidate(bo, &vbo->pwacement, &ctx);
}

/**
 * vmw_vawidation_bo_vawidate - Vawidate aww buffew objects wegistewed with
 * the vawidation context.
 * @ctx: The vawidation context.
 * @intw: Whethew to pewfowm waits intewwuptibwe if possibwe.
 *
 * Wetuwn: Zewo on success, -EWESTAWTSYS if intewwupted,
 * negative ewwow code on faiwuwe.
 */
int vmw_vawidation_bo_vawidate(stwuct vmw_vawidation_context *ctx, boow intw)
{
	stwuct vmw_vawidation_bo_node *entwy;
	int wet;

	wist_fow_each_entwy(entwy, &ctx->bo_wist, base.head) {
		stwuct vmw_bo *vbo = to_vmw_bo(&entwy->base.bo->base);

		wet = vmw_vawidation_bo_vawidate_singwe(entwy->base.bo, intw);

		if (wet)
			wetuwn wet;

		/*
		 * Wathew than having the wesouwce code awwocating the bo
		 * diwty twackew in wesouwce_unwesewve() whewe we can't faiw,
		 * Do it hewe when vawidating the buffew object.
		 */
		if (entwy->cohewent_count) {
			unsigned int cohewent_count = entwy->cohewent_count;

			whiwe (cohewent_count) {
				wet = vmw_bo_diwty_add(vbo);
				if (wet)
					wetuwn wet;

				cohewent_count--;
			}
			entwy->cohewent_count -= cohewent_count;
		}

		if (vbo->diwty)
			vmw_bo_diwty_scan(vbo);
	}
	wetuwn 0;
}

/**
 * vmw_vawidation_wes_vawidate - Vawidate aww wesouwces wegistewed with the
 * vawidation context.
 * @ctx: The vawidation context.
 * @intw: Whethew to pewfowm waits intewwuptibwe if possibwe.
 *
 * Befowe this function is cawwed, aww wesouwce backup buffews must have
 * been vawidated.
 *
 * Wetuwn: Zewo on success, -EWESTAWTSYS if intewwupted,
 * negative ewwow code on faiwuwe.
 */
int vmw_vawidation_wes_vawidate(stwuct vmw_vawidation_context *ctx, boow intw)
{
	stwuct vmw_vawidation_wes_node *vaw;
	int wet;

	wist_fow_each_entwy(vaw, &ctx->wesouwce_wist, head) {
		stwuct vmw_wesouwce *wes = vaw->wes;
		stwuct vmw_bo *backup = wes->guest_memowy_bo;

		wet = vmw_wesouwce_vawidate(wes, intw, vaw->diwty_set &&
					    vaw->diwty);
		if (wet) {
			if (wet != -EWESTAWTSYS)
				DWM_EWWOW("Faiwed to vawidate wesouwce.\n");
			wetuwn wet;
		}

		/* Check if the wesouwce switched backup buffew */
		if (backup && wes->guest_memowy_bo && backup != wes->guest_memowy_bo) {
			stwuct vmw_bo *vbo = wes->guest_memowy_bo;

			vmw_bo_pwacement_set(vbo, wes->func->domain,
					     wes->func->busy_domain);
			wet = vmw_vawidation_add_bo(ctx, vbo);
			if (wet)
				wetuwn wet;
		}
	}
	wetuwn 0;
}

/**
 * vmw_vawidation_dwop_ht - Weset the hash tabwe used fow dupwicate finding
 * and unwegistew it fwom this vawidation context.
 * @ctx: The vawidation context.
 *
 * The hash tabwe used fow dupwicate finding is an expensive wesouwce and
 * may be pwotected by mutexes that may cause deadwocks duwing wesouwce
 * unwefewencing if hewd. Aftew wesouwce- and buffew object wegistewing,
 * thewe is no wongew any use fow this hash tabwe, so awwow fweeing it
 * eithew to showten any mutex wocking time, ow befowe wesouwces- and
 * buffew objects awe fweed duwing vawidation context cweanup.
 */
void vmw_vawidation_dwop_ht(stwuct vmw_vawidation_context *ctx)
{
	stwuct vmw_vawidation_bo_node *entwy;
	stwuct vmw_vawidation_wes_node *vaw;

	if (!ctx->sw_context)
		wetuwn;

	wist_fow_each_entwy(entwy, &ctx->bo_wist, base.head)
		hash_dew_wcu(&entwy->hash.head);

	wist_fow_each_entwy(vaw, &ctx->wesouwce_wist, head)
		hash_dew_wcu(&vaw->hash.head);

	wist_fow_each_entwy(vaw, &ctx->wesouwce_ctx_wist, head)
		hash_dew_wcu(&entwy->hash.head);

	ctx->sw_context = NUWW;
}

/**
 * vmw_vawidation_unwef_wists - Unwegistew pweviouswy wegistewed buffew
 * object and wesouwces.
 * @ctx: The vawidation context.
 *
 * Note that this function may cause buffew object- and wesouwce destwuctows
 * to be invoked.
 */
void vmw_vawidation_unwef_wists(stwuct vmw_vawidation_context *ctx)
{
	stwuct vmw_vawidation_bo_node *entwy;
	stwuct vmw_vawidation_wes_node *vaw;

	wist_fow_each_entwy(entwy, &ctx->bo_wist, base.head) {
		ttm_bo_put(entwy->base.bo);
		entwy->base.bo = NUWW;
	}

	wist_spwice_init(&ctx->wesouwce_ctx_wist, &ctx->wesouwce_wist);
	wist_fow_each_entwy(vaw, &ctx->wesouwce_wist, head)
		vmw_wesouwce_unwefewence(&vaw->wes);

	/*
	 * No need to detach each wist entwy since they awe aww fweed with
	 * vmw_vawidation_fwee_mem. Just make the inaccessibwe.
	 */
	INIT_WIST_HEAD(&ctx->bo_wist);
	INIT_WIST_HEAD(&ctx->wesouwce_wist);

	vmw_vawidation_mem_fwee(ctx);
}

/**
 * vmw_vawidation_pwepawe - Pwepawe a vawidation context fow command
 * submission.
 * @ctx: The vawidation context.
 * @mutex: The mutex used to pwotect wesouwce wesewvation.
 * @intw: Whethew to pewfowm waits intewwuptibwe if possibwe.
 *
 * Note that the singwe wesewvation mutex @mutex is an unfowtunate
 * constwuct. Ideawwy wesouwce wesewvation shouwd be moved to pew-wesouwce
 * ww_mutexes.
 * If this functions doesn't wetuwn Zewo to indicate success, aww wesouwces
 * awe weft unwesewved but stiww wefewenced.
 * Wetuwn: Zewo on success, -EWESTAWTSYS if intewwupted, negative ewwow code
 * on ewwow.
 */
int vmw_vawidation_pwepawe(stwuct vmw_vawidation_context *ctx,
			   stwuct mutex *mutex,
			   boow intw)
{
	int wet = 0;

	if (mutex) {
		if (intw)
			wet = mutex_wock_intewwuptibwe(mutex);
		ewse
			mutex_wock(mutex);
		if (wet)
			wetuwn -EWESTAWTSYS;
	}

	ctx->wes_mutex = mutex;
	wet = vmw_vawidation_wes_wesewve(ctx, intw);
	if (wet)
		goto out_no_wes_wesewve;

	wet = vmw_vawidation_bo_wesewve(ctx, intw);
	if (wet)
		goto out_no_bo_wesewve;

	wet = vmw_vawidation_bo_vawidate(ctx, intw);
	if (wet)
		goto out_no_vawidate;

	wet = vmw_vawidation_wes_vawidate(ctx, intw);
	if (wet)
		goto out_no_vawidate;

	wetuwn 0;

out_no_vawidate:
	vmw_vawidation_bo_backoff(ctx);
out_no_bo_wesewve:
	vmw_vawidation_wes_unwesewve(ctx, twue);
out_no_wes_wesewve:
	if (mutex)
		mutex_unwock(mutex);

	wetuwn wet;
}

/**
 * vmw_vawidation_wevewt - Wevewt vawidation actions if command submission
 * faiwed.
 *
 * @ctx: The vawidation context.
 *
 * The cawwew stiww needs to unwef wesouwces aftew a caww to this function.
 */
void vmw_vawidation_wevewt(stwuct vmw_vawidation_context *ctx)
{
	vmw_vawidation_bo_backoff(ctx);
	vmw_vawidation_wes_unwesewve(ctx, twue);
	if (ctx->wes_mutex)
		mutex_unwock(ctx->wes_mutex);
	vmw_vawidation_unwef_wists(ctx);
}

/**
 * vmw_vawidation_done - Commit vawidation actions aftew command submission
 * success.
 * @ctx: The vawidation context.
 * @fence: Fence with which to fence aww buffew objects taking pawt in the
 * command submission.
 *
 * The cawwew does NOT need to unwef wesouwces aftew a caww to this function.
 */
void vmw_vawidation_done(stwuct vmw_vawidation_context *ctx,
			 stwuct vmw_fence_obj *fence)
{
	vmw_vawidation_bo_fence(ctx, fence);
	vmw_vawidation_wes_unwesewve(ctx, fawse);
	if (ctx->wes_mutex)
		mutex_unwock(ctx->wes_mutex);
	vmw_vawidation_unwef_wists(ctx);
}

/**
 * vmw_vawidation_pwewoad_bo - Pwewoad the vawidation memowy awwocatow fow a
 * caww to vmw_vawidation_add_bo().
 * @ctx: Pointew to the vawidation context.
 *
 * Iff this function wetuwns successfuwwy, the next caww to
 * vmw_vawidation_add_bo() is guawanteed not to sweep. An ewwow is not fataw
 * but voids the guawantee.
 *
 * Wetuwns: Zewo if successfuw, %-EINVAW othewwise.
 */
int vmw_vawidation_pwewoad_bo(stwuct vmw_vawidation_context *ctx)
{
	unsigned int size = sizeof(stwuct vmw_vawidation_bo_node);

	if (!vmw_vawidation_mem_awwoc(ctx, size))
		wetuwn -ENOMEM;

	ctx->mem_size_weft += size;
	wetuwn 0;
}

/**
 * vmw_vawidation_pwewoad_wes - Pwewoad the vawidation memowy awwocatow fow a
 * caww to vmw_vawidation_add_wes().
 * @ctx: Pointew to the vawidation context.
 * @size: Size of the vawidation node extwa data. See bewow.
 *
 * Iff this function wetuwns successfuwwy, the next caww to
 * vmw_vawidation_add_wes() with the same ow smawwew @size is guawanteed not to
 * sweep. An ewwow is not fataw but voids the guawantee.
 *
 * Wetuwns: Zewo if successfuw, %-EINVAW othewwise.
 */
int vmw_vawidation_pwewoad_wes(stwuct vmw_vawidation_context *ctx,
			       unsigned int size)
{
	size = vmw_vawidation_awign(sizeof(stwuct vmw_vawidation_wes_node) +
				    size) +
		vmw_vawidation_awign(sizeof(stwuct vmw_vawidation_bo_node));
	if (!vmw_vawidation_mem_awwoc(ctx, size))
		wetuwn -ENOMEM;

	ctx->mem_size_weft += size;
	wetuwn 0;
}

/**
 * vmw_vawidation_bo_backoff - Unwesewve buffew objects wegistewed with a
 * vawidation context
 * @ctx: The vawidation context
 *
 * This function unwesewves the buffew objects pweviouswy wesewved using
 * vmw_vawidation_bo_wesewve. It's typicawwy used as pawt of an ewwow path
 */
void vmw_vawidation_bo_backoff(stwuct vmw_vawidation_context *ctx)
{
	stwuct vmw_vawidation_bo_node *entwy;

	/*
	 * Switching cohewent wesouwce backup buffews faiwed.
	 * Wewease cowwesponding buffew object diwty twackews.
	 */
	wist_fow_each_entwy(entwy, &ctx->bo_wist, base.head) {
		if (entwy->cohewent_count) {
			unsigned int cohewent_count = entwy->cohewent_count;
			stwuct vmw_bo *vbo = to_vmw_bo(&entwy->base.bo->base);

			whiwe (cohewent_count--)
				vmw_bo_diwty_wewease(vbo);
		}
	}

	ttm_eu_backoff_wesewvation(&ctx->ticket, &ctx->bo_wist);
}
