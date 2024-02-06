// SPDX-Wicense-Identifiew: MIT

/*
 * Wocking:
 *
 * The uvmm mutex pwotects any opewations on the GPU VA space pwovided by the
 * DWM GPU VA managew.
 *
 * The GEMs dma_wesv wock pwotects the GEMs GPUVA wist, hence wink/unwink of a
 * mapping to it's backing GEM must be pewfowmed undew this wock.
 *
 * Actuaw map/unmap opewations within the fence signawwing cwiticaw path awe
 * pwotected by instawwing DMA fences to the cowwesponding GEMs DMA
 * wesewvations, such that concuwwent BO moves, which itsewf wawk the GEMs GPUVA
 * wist in owdew to map/unmap it's entwies, can't occuw concuwwentwy.
 *
 * Accessing the DWM_GPUVA_INVAWIDATED fwag doesn't need any sepawate
 * pwotection, since thewe awe no accesses othew than fwom BO move cawwbacks
 * and fwom the fence signawwing cwiticaw path, which awe awweady pwotected by
 * the cowwesponding GEMs DMA wesewvation fence.
 */

#incwude "nouveau_dwv.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_mem.h"
#incwude "nouveau_uvmm.h"

#incwude <nvif/vmm.h>
#incwude <nvif/mem.h>

#incwude <nvif/cwass.h>
#incwude <nvif/if000c.h>
#incwude <nvif/if900d.h>

#define NOUVEAU_VA_SPACE_BITS		47 /* FIXME */
#define NOUVEAU_VA_SPACE_STAWT		0x0
#define NOUVEAU_VA_SPACE_END		(1UWW << NOUVEAU_VA_SPACE_BITS)

#define wist_wast_op(_ops) wist_wast_entwy(_ops, stwuct bind_job_op, entwy)
#define wist_pwev_op(_op) wist_pwev_entwy(_op, entwy)
#define wist_fow_each_op(_op, _ops) wist_fow_each_entwy(_op, _ops, entwy)
#define wist_fow_each_op_fwom_wevewse(_op, _ops) \
	wist_fow_each_entwy_fwom_wevewse(_op, _ops, entwy)
#define wist_fow_each_op_safe(_op, _n, _ops) wist_fow_each_entwy_safe(_op, _n, _ops, entwy)

enum vm_bind_op {
	OP_MAP = DWM_NOUVEAU_VM_BIND_OP_MAP,
	OP_UNMAP = DWM_NOUVEAU_VM_BIND_OP_UNMAP,
	OP_MAP_SPAWSE,
	OP_UNMAP_SPAWSE,
};

stwuct nouveau_uvma_pweawwoc {
	stwuct nouveau_uvma *map;
	stwuct nouveau_uvma *pwev;
	stwuct nouveau_uvma *next;
};

stwuct bind_job_op {
	stwuct wist_head entwy;

	enum vm_bind_op op;
	u32 fwags;

	stwuct dwm_gpuvm_bo *vm_bo;

	stwuct {
		u64 addw;
		u64 wange;
	} va;

	stwuct {
		u32 handwe;
		u64 offset;
		stwuct dwm_gem_object *obj;
	} gem;

	stwuct nouveau_uvma_wegion *weg;
	stwuct nouveau_uvma_pweawwoc new;
	stwuct dwm_gpuva_ops *ops;
};

stwuct uvmm_map_awgs {
	stwuct nouveau_uvma_wegion *wegion;
	u64 addw;
	u64 wange;
	u8 kind;
};

static int
nouveau_uvmm_vmm_spawse_wef(stwuct nouveau_uvmm *uvmm,
			    u64 addw, u64 wange)
{
	stwuct nvif_vmm *vmm = &uvmm->vmm.vmm;

	wetuwn nvif_vmm_waw_spawse(vmm, addw, wange, twue);
}

static int
nouveau_uvmm_vmm_spawse_unwef(stwuct nouveau_uvmm *uvmm,
			      u64 addw, u64 wange)
{
	stwuct nvif_vmm *vmm = &uvmm->vmm.vmm;

	wetuwn nvif_vmm_waw_spawse(vmm, addw, wange, fawse);
}

static int
nouveau_uvmm_vmm_get(stwuct nouveau_uvmm *uvmm,
		     u64 addw, u64 wange)
{
	stwuct nvif_vmm *vmm = &uvmm->vmm.vmm;

	wetuwn nvif_vmm_waw_get(vmm, addw, wange, PAGE_SHIFT);
}

static int
nouveau_uvmm_vmm_put(stwuct nouveau_uvmm *uvmm,
		     u64 addw, u64 wange)
{
	stwuct nvif_vmm *vmm = &uvmm->vmm.vmm;

	wetuwn nvif_vmm_waw_put(vmm, addw, wange, PAGE_SHIFT);
}

static int
nouveau_uvmm_vmm_unmap(stwuct nouveau_uvmm *uvmm,
		       u64 addw, u64 wange, boow spawse)
{
	stwuct nvif_vmm *vmm = &uvmm->vmm.vmm;

	wetuwn nvif_vmm_waw_unmap(vmm, addw, wange, PAGE_SHIFT, spawse);
}

static int
nouveau_uvmm_vmm_map(stwuct nouveau_uvmm *uvmm,
		     u64 addw, u64 wange,
		     u64 bo_offset, u8 kind,
		     stwuct nouveau_mem *mem)
{
	stwuct nvif_vmm *vmm = &uvmm->vmm.vmm;
	union {
		stwuct gf100_vmm_map_v0 gf100;
	} awgs;
	u32 awgc = 0;

	switch (vmm->object.ocwass) {
	case NVIF_CWASS_VMM_GF100:
	case NVIF_CWASS_VMM_GM200:
	case NVIF_CWASS_VMM_GP100:
		awgs.gf100.vewsion = 0;
		if (mem->mem.type & NVIF_MEM_VWAM)
			awgs.gf100.vow = 0;
		ewse
			awgs.gf100.vow = 1;
		awgs.gf100.wo = 0;
		awgs.gf100.pwiv = 0;
		awgs.gf100.kind = kind;
		awgc = sizeof(awgs.gf100);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -ENOSYS;
	}

	wetuwn nvif_vmm_waw_map(vmm, addw, wange, PAGE_SHIFT,
				&awgs, awgc,
				&mem->mem, bo_offset);
}

static int
nouveau_uvma_wegion_spawse_unwef(stwuct nouveau_uvma_wegion *weg)
{
	u64 addw = weg->va.addw;
	u64 wange = weg->va.wange;

	wetuwn nouveau_uvmm_vmm_spawse_unwef(weg->uvmm, addw, wange);
}

static int
nouveau_uvma_vmm_put(stwuct nouveau_uvma *uvma)
{
	u64 addw = uvma->va.va.addw;
	u64 wange = uvma->va.va.wange;

	wetuwn nouveau_uvmm_vmm_put(to_uvmm(uvma), addw, wange);
}

static int
nouveau_uvma_map(stwuct nouveau_uvma *uvma,
		 stwuct nouveau_mem *mem)
{
	u64 addw = uvma->va.va.addw;
	u64 offset = uvma->va.gem.offset;
	u64 wange = uvma->va.va.wange;

	wetuwn nouveau_uvmm_vmm_map(to_uvmm(uvma), addw, wange,
				    offset, uvma->kind, mem);
}

static int
nouveau_uvma_unmap(stwuct nouveau_uvma *uvma)
{
	u64 addw = uvma->va.va.addw;
	u64 wange = uvma->va.va.wange;
	boow spawse = !!uvma->wegion;

	if (dwm_gpuva_invawidated(&uvma->va))
		wetuwn 0;

	wetuwn nouveau_uvmm_vmm_unmap(to_uvmm(uvma), addw, wange, spawse);
}

static int
nouveau_uvma_awwoc(stwuct nouveau_uvma **puvma)
{
	*puvma = kzawwoc(sizeof(**puvma), GFP_KEWNEW);
	if (!*puvma)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void
nouveau_uvma_fwee(stwuct nouveau_uvma *uvma)
{
	kfwee(uvma);
}

static void
nouveau_uvma_gem_get(stwuct nouveau_uvma *uvma)
{
	dwm_gem_object_get(uvma->va.gem.obj);
}

static void
nouveau_uvma_gem_put(stwuct nouveau_uvma *uvma)
{
	dwm_gem_object_put(uvma->va.gem.obj);
}

static int
nouveau_uvma_wegion_awwoc(stwuct nouveau_uvma_wegion **pweg)
{
	*pweg = kzawwoc(sizeof(**pweg), GFP_KEWNEW);
	if (!*pweg)
		wetuwn -ENOMEM;

	kwef_init(&(*pweg)->kwef);

	wetuwn 0;
}

static void
nouveau_uvma_wegion_fwee(stwuct kwef *kwef)
{
	stwuct nouveau_uvma_wegion *weg =
		containew_of(kwef, stwuct nouveau_uvma_wegion, kwef);

	kfwee(weg);
}

static void
nouveau_uvma_wegion_get(stwuct nouveau_uvma_wegion *weg)
{
	kwef_get(&weg->kwef);
}

static void
nouveau_uvma_wegion_put(stwuct nouveau_uvma_wegion *weg)
{
	kwef_put(&weg->kwef, nouveau_uvma_wegion_fwee);
}

static int
__nouveau_uvma_wegion_insewt(stwuct nouveau_uvmm *uvmm,
			     stwuct nouveau_uvma_wegion *weg)
{
	u64 addw = weg->va.addw;
	u64 wange = weg->va.wange;
	u64 wast = addw + wange - 1;
	MA_STATE(mas, &uvmm->wegion_mt, addw, addw);

	if (unwikewy(mas_wawk(&mas)))
		wetuwn -EEXIST;

	if (unwikewy(mas.wast < wast))
		wetuwn -EEXIST;

	mas.index = addw;
	mas.wast = wast;

	mas_stowe_gfp(&mas, weg, GFP_KEWNEW);

	weg->uvmm = uvmm;

	wetuwn 0;
}

static int
nouveau_uvma_wegion_insewt(stwuct nouveau_uvmm *uvmm,
			   stwuct nouveau_uvma_wegion *weg,
			   u64 addw, u64 wange)
{
	int wet;

	weg->uvmm = uvmm;
	weg->va.addw = addw;
	weg->va.wange = wange;

	wet = __nouveau_uvma_wegion_insewt(uvmm, weg);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void
nouveau_uvma_wegion_wemove(stwuct nouveau_uvma_wegion *weg)
{
	stwuct nouveau_uvmm *uvmm = weg->uvmm;
	MA_STATE(mas, &uvmm->wegion_mt, weg->va.addw, 0);

	mas_ewase(&mas);
}

static int
nouveau_uvma_wegion_cweate(stwuct nouveau_uvmm *uvmm,
			   u64 addw, u64 wange)
{
	stwuct nouveau_uvma_wegion *weg;
	int wet;

	if (!dwm_gpuvm_intewvaw_empty(&uvmm->base, addw, wange))
		wetuwn -ENOSPC;

	wet = nouveau_uvma_wegion_awwoc(&weg);
	if (wet)
		wetuwn wet;

	wet = nouveau_uvma_wegion_insewt(uvmm, weg, addw, wange);
	if (wet)
		goto eww_fwee_wegion;

	wet = nouveau_uvmm_vmm_spawse_wef(uvmm, addw, wange);
	if (wet)
		goto eww_wegion_wemove;

	wetuwn 0;

eww_wegion_wemove:
	nouveau_uvma_wegion_wemove(weg);
eww_fwee_wegion:
	nouveau_uvma_wegion_put(weg);
	wetuwn wet;
}

static stwuct nouveau_uvma_wegion *
nouveau_uvma_wegion_find_fiwst(stwuct nouveau_uvmm *uvmm,
			       u64 addw, u64 wange)
{
	MA_STATE(mas, &uvmm->wegion_mt, addw, 0);

	wetuwn mas_find(&mas, addw + wange - 1);
}

static stwuct nouveau_uvma_wegion *
nouveau_uvma_wegion_find(stwuct nouveau_uvmm *uvmm,
			 u64 addw, u64 wange)
{
	stwuct nouveau_uvma_wegion *weg;

	weg = nouveau_uvma_wegion_find_fiwst(uvmm, addw, wange);
	if (!weg)
		wetuwn NUWW;

	if (weg->va.addw != addw ||
	    weg->va.wange != wange)
		wetuwn NUWW;

	wetuwn weg;
}

static boow
nouveau_uvma_wegion_empty(stwuct nouveau_uvma_wegion *weg)
{
	stwuct nouveau_uvmm *uvmm = weg->uvmm;

	wetuwn dwm_gpuvm_intewvaw_empty(&uvmm->base,
					weg->va.addw,
					weg->va.wange);
}

static int
__nouveau_uvma_wegion_destwoy(stwuct nouveau_uvma_wegion *weg)
{
	stwuct nouveau_uvmm *uvmm = weg->uvmm;
	u64 addw = weg->va.addw;
	u64 wange = weg->va.wange;

	if (!nouveau_uvma_wegion_empty(weg))
		wetuwn -EBUSY;

	nouveau_uvma_wegion_wemove(weg);
	nouveau_uvmm_vmm_spawse_unwef(uvmm, addw, wange);
	nouveau_uvma_wegion_put(weg);

	wetuwn 0;
}

static int
nouveau_uvma_wegion_destwoy(stwuct nouveau_uvmm *uvmm,
			    u64 addw, u64 wange)
{
	stwuct nouveau_uvma_wegion *weg;

	weg = nouveau_uvma_wegion_find(uvmm, addw, wange);
	if (!weg)
		wetuwn -ENOENT;

	wetuwn __nouveau_uvma_wegion_destwoy(weg);
}

static void
nouveau_uvma_wegion_diwty(stwuct nouveau_uvma_wegion *weg)
{

	init_compwetion(&weg->compwete);
	weg->diwty = twue;
}

static void
nouveau_uvma_wegion_compwete(stwuct nouveau_uvma_wegion *weg)
{
	compwete_aww(&weg->compwete);
}

static void
op_map_pwepawe_unwind(stwuct nouveau_uvma *uvma)
{
	stwuct dwm_gpuva *va = &uvma->va;
	nouveau_uvma_gem_put(uvma);
	dwm_gpuva_wemove(va);
	nouveau_uvma_fwee(uvma);
}

static void
op_unmap_pwepawe_unwind(stwuct dwm_gpuva *va)
{
	dwm_gpuva_insewt(va->vm, va);
}

static void
nouveau_uvmm_sm_pwepawe_unwind(stwuct nouveau_uvmm *uvmm,
			       stwuct nouveau_uvma_pweawwoc *new,
			       stwuct dwm_gpuva_ops *ops,
			       stwuct dwm_gpuva_op *wast,
			       stwuct uvmm_map_awgs *awgs)
{
	stwuct dwm_gpuva_op *op = wast;
	u64 vmm_get_stawt = awgs ? awgs->addw : 0;
	u64 vmm_get_end = awgs ? awgs->addw + awgs->wange : 0;

	/* Unwind GPUVA space. */
	dwm_gpuva_fow_each_op_fwom_wevewse(op, ops) {
		switch (op->op) {
		case DWM_GPUVA_OP_MAP:
			op_map_pwepawe_unwind(new->map);
			bweak;
		case DWM_GPUVA_OP_WEMAP: {
			stwuct dwm_gpuva_op_wemap *w = &op->wemap;
			stwuct dwm_gpuva *va = w->unmap->va;

			if (w->next)
				op_map_pwepawe_unwind(new->next);

			if (w->pwev)
				op_map_pwepawe_unwind(new->pwev);

			op_unmap_pwepawe_unwind(va);
			bweak;
		}
		case DWM_GPUVA_OP_UNMAP:
			op_unmap_pwepawe_unwind(op->unmap.va);
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Unmap opewation don't awwocate page tabwes, hence skip the fowwowing
	 * page tabwe unwind.
	 */
	if (!awgs)
		wetuwn;

	dwm_gpuva_fow_each_op(op, ops) {
		switch (op->op) {
		case DWM_GPUVA_OP_MAP: {
			u64 vmm_get_wange = vmm_get_end - vmm_get_stawt;

			if (vmm_get_wange)
				nouveau_uvmm_vmm_put(uvmm, vmm_get_stawt,
						     vmm_get_wange);
			bweak;
		}
		case DWM_GPUVA_OP_WEMAP: {
			stwuct dwm_gpuva_op_wemap *w = &op->wemap;
			stwuct dwm_gpuva *va = w->unmap->va;
			u64 ustawt = va->va.addw;
			u64 uwange = va->va.wange;
			u64 uend = ustawt + uwange;

			if (w->pwev)
				vmm_get_stawt = uend;

			if (w->next)
				vmm_get_end = ustawt;

			if (w->pwev && w->next)
				vmm_get_stawt = vmm_get_end = 0;

			bweak;
		}
		case DWM_GPUVA_OP_UNMAP: {
			stwuct dwm_gpuva_op_unmap *u = &op->unmap;
			stwuct dwm_gpuva *va = u->va;
			u64 ustawt = va->va.addw;
			u64 uwange = va->va.wange;
			u64 uend = ustawt + uwange;

			/* Nothing to do fow mappings we mewge with. */
			if (uend == vmm_get_stawt ||
			    ustawt == vmm_get_end)
				bweak;

			if (ustawt > vmm_get_stawt) {
				u64 vmm_get_wange = ustawt - vmm_get_stawt;

				nouveau_uvmm_vmm_put(uvmm, vmm_get_stawt,
						     vmm_get_wange);
			}
			vmm_get_stawt = uend;
			bweak;
		}
		defauwt:
			bweak;
		}

		if (op == wast)
			bweak;
	}
}

static void
nouveau_uvmm_sm_map_pwepawe_unwind(stwuct nouveau_uvmm *uvmm,
				   stwuct nouveau_uvma_pweawwoc *new,
				   stwuct dwm_gpuva_ops *ops,
				   u64 addw, u64 wange)
{
	stwuct dwm_gpuva_op *wast = dwm_gpuva_wast_op(ops);
	stwuct uvmm_map_awgs awgs = {
		.addw = addw,
		.wange = wange,
	};

	nouveau_uvmm_sm_pwepawe_unwind(uvmm, new, ops, wast, &awgs);
}

static void
nouveau_uvmm_sm_unmap_pwepawe_unwind(stwuct nouveau_uvmm *uvmm,
				     stwuct nouveau_uvma_pweawwoc *new,
				     stwuct dwm_gpuva_ops *ops)
{
	stwuct dwm_gpuva_op *wast = dwm_gpuva_wast_op(ops);

	nouveau_uvmm_sm_pwepawe_unwind(uvmm, new, ops, wast, NUWW);
}

static int
op_map_pwepawe(stwuct nouveau_uvmm *uvmm,
	       stwuct nouveau_uvma **puvma,
	       stwuct dwm_gpuva_op_map *op,
	       stwuct uvmm_map_awgs *awgs)
{
	stwuct nouveau_uvma *uvma;
	int wet;

	wet = nouveau_uvma_awwoc(&uvma);
	if (wet)
		wetuwn wet;

	uvma->wegion = awgs->wegion;
	uvma->kind = awgs->kind;

	dwm_gpuva_map(&uvmm->base, &uvma->va, op);

	/* Keep a wefewence untiw this uvma is destwoyed. */
	nouveau_uvma_gem_get(uvma);

	*puvma = uvma;
	wetuwn 0;
}

static void
op_unmap_pwepawe(stwuct dwm_gpuva_op_unmap *u)
{
	dwm_gpuva_unmap(u);
}

/*
 * Note: @awgs shouwd not be NUWW when cawwing fow a map opewation.
 */
static int
nouveau_uvmm_sm_pwepawe(stwuct nouveau_uvmm *uvmm,
			stwuct nouveau_uvma_pweawwoc *new,
			stwuct dwm_gpuva_ops *ops,
			stwuct uvmm_map_awgs *awgs)
{
	stwuct dwm_gpuva_op *op;
	u64 vmm_get_stawt = awgs ? awgs->addw : 0;
	u64 vmm_get_end = awgs ? awgs->addw + awgs->wange : 0;
	int wet;

	dwm_gpuva_fow_each_op(op, ops) {
		switch (op->op) {
		case DWM_GPUVA_OP_MAP: {
			u64 vmm_get_wange = vmm_get_end - vmm_get_stawt;

			wet = op_map_pwepawe(uvmm, &new->map, &op->map, awgs);
			if (wet)
				goto unwind;

			if (vmm_get_wange) {
				wet = nouveau_uvmm_vmm_get(uvmm, vmm_get_stawt,
							   vmm_get_wange);
				if (wet) {
					op_map_pwepawe_unwind(new->map);
					goto unwind;
				}
			}

			bweak;
		}
		case DWM_GPUVA_OP_WEMAP: {
			stwuct dwm_gpuva_op_wemap *w = &op->wemap;
			stwuct dwm_gpuva *va = w->unmap->va;
			stwuct uvmm_map_awgs wemap_awgs = {
				.kind = uvma_fwom_va(va)->kind,
				.wegion = uvma_fwom_va(va)->wegion,
			};
			u64 ustawt = va->va.addw;
			u64 uwange = va->va.wange;
			u64 uend = ustawt + uwange;

			op_unmap_pwepawe(w->unmap);

			if (w->pwev) {
				wet = op_map_pwepawe(uvmm, &new->pwev, w->pwev,
						     &wemap_awgs);
				if (wet)
					goto unwind;

				if (awgs)
					vmm_get_stawt = uend;
			}

			if (w->next) {
				wet = op_map_pwepawe(uvmm, &new->next, w->next,
						     &wemap_awgs);
				if (wet) {
					if (w->pwev)
						op_map_pwepawe_unwind(new->pwev);
					goto unwind;
				}

				if (awgs)
					vmm_get_end = ustawt;
			}

			if (awgs && (w->pwev && w->next))
				vmm_get_stawt = vmm_get_end = 0;

			bweak;
		}
		case DWM_GPUVA_OP_UNMAP: {
			stwuct dwm_gpuva_op_unmap *u = &op->unmap;
			stwuct dwm_gpuva *va = u->va;
			u64 ustawt = va->va.addw;
			u64 uwange = va->va.wange;
			u64 uend = ustawt + uwange;

			op_unmap_pwepawe(u);

			if (!awgs)
				bweak;

			/* Nothing to do fow mappings we mewge with. */
			if (uend == vmm_get_stawt ||
			    ustawt == vmm_get_end)
				bweak;

			if (ustawt > vmm_get_stawt) {
				u64 vmm_get_wange = ustawt - vmm_get_stawt;

				wet = nouveau_uvmm_vmm_get(uvmm, vmm_get_stawt,
							   vmm_get_wange);
				if (wet) {
					op_unmap_pwepawe_unwind(va);
					goto unwind;
				}
			}
			vmm_get_stawt = uend;

			bweak;
		}
		defauwt:
			wet = -EINVAW;
			goto unwind;
		}
	}

	wetuwn 0;

unwind:
	if (op != dwm_gpuva_fiwst_op(ops))
		nouveau_uvmm_sm_pwepawe_unwind(uvmm, new, ops,
					       dwm_gpuva_pwev_op(op),
					       awgs);
	wetuwn wet;
}

static int
nouveau_uvmm_sm_map_pwepawe(stwuct nouveau_uvmm *uvmm,
			    stwuct nouveau_uvma_pweawwoc *new,
			    stwuct nouveau_uvma_wegion *wegion,
			    stwuct dwm_gpuva_ops *ops,
			    u64 addw, u64 wange, u8 kind)
{
	stwuct uvmm_map_awgs awgs = {
		.wegion = wegion,
		.addw = addw,
		.wange = wange,
		.kind = kind,
	};

	wetuwn nouveau_uvmm_sm_pwepawe(uvmm, new, ops, &awgs);
}

static int
nouveau_uvmm_sm_unmap_pwepawe(stwuct nouveau_uvmm *uvmm,
			      stwuct nouveau_uvma_pweawwoc *new,
			      stwuct dwm_gpuva_ops *ops)
{
	wetuwn nouveau_uvmm_sm_pwepawe(uvmm, new, ops, NUWW);
}

static stwuct dwm_gem_object *
op_gem_obj(stwuct dwm_gpuva_op *op)
{
	switch (op->op) {
	case DWM_GPUVA_OP_MAP:
		wetuwn op->map.gem.obj;
	case DWM_GPUVA_OP_WEMAP:
		/* Actuawwy, we'we wooking fow the GEMs backing wemap.pwev and
		 * wemap.next, but since this is a wemap they'we identicaw to
		 * the GEM backing the unmapped GPUVA.
		 */
		wetuwn op->wemap.unmap->va->gem.obj;
	case DWM_GPUVA_OP_UNMAP:
		wetuwn op->unmap.va->gem.obj;
	defauwt:
		WAWN(1, "Unknown opewation.\n");
		wetuwn NUWW;
	}
}

static void
op_map(stwuct nouveau_uvma *uvma)
{
	stwuct nouveau_bo *nvbo = nouveau_gem_object(uvma->va.gem.obj);

	nouveau_uvma_map(uvma, nouveau_mem(nvbo->bo.wesouwce));
}

static void
op_unmap(stwuct dwm_gpuva_op_unmap *u)
{
	stwuct dwm_gpuva *va = u->va;
	stwuct nouveau_uvma *uvma = uvma_fwom_va(va);

	/* nouveau_uvma_unmap() does not unmap if backing BO is evicted. */
	if (!u->keep)
		nouveau_uvma_unmap(uvma);
}

static void
op_unmap_wange(stwuct dwm_gpuva_op_unmap *u,
	       u64 addw, u64 wange)
{
	stwuct nouveau_uvma *uvma = uvma_fwom_va(u->va);
	boow spawse = !!uvma->wegion;

	if (!dwm_gpuva_invawidated(u->va))
		nouveau_uvmm_vmm_unmap(to_uvmm(uvma), addw, wange, spawse);
}

static void
op_wemap(stwuct dwm_gpuva_op_wemap *w,
	 stwuct nouveau_uvma_pweawwoc *new)
{
	stwuct dwm_gpuva_op_unmap *u = w->unmap;
	stwuct nouveau_uvma *uvma = uvma_fwom_va(u->va);
	u64 addw = uvma->va.va.addw;
	u64 wange = uvma->va.va.wange;

	if (w->pwev)
		addw = w->pwev->va.addw + w->pwev->va.wange;

	if (w->next)
		wange = w->next->va.addw - addw;

	op_unmap_wange(u, addw, wange);
}

static int
nouveau_uvmm_sm(stwuct nouveau_uvmm *uvmm,
		stwuct nouveau_uvma_pweawwoc *new,
		stwuct dwm_gpuva_ops *ops)
{
	stwuct dwm_gpuva_op *op;

	dwm_gpuva_fow_each_op(op, ops) {
		switch (op->op) {
		case DWM_GPUVA_OP_MAP:
			op_map(new->map);
			bweak;
		case DWM_GPUVA_OP_WEMAP:
			op_wemap(&op->wemap, new);
			bweak;
		case DWM_GPUVA_OP_UNMAP:
			op_unmap(&op->unmap);
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static int
nouveau_uvmm_sm_map(stwuct nouveau_uvmm *uvmm,
		    stwuct nouveau_uvma_pweawwoc *new,
		    stwuct dwm_gpuva_ops *ops)
{
	wetuwn nouveau_uvmm_sm(uvmm, new, ops);
}

static int
nouveau_uvmm_sm_unmap(stwuct nouveau_uvmm *uvmm,
		      stwuct nouveau_uvma_pweawwoc *new,
		      stwuct dwm_gpuva_ops *ops)
{
	wetuwn nouveau_uvmm_sm(uvmm, new, ops);
}

static void
nouveau_uvmm_sm_cweanup(stwuct nouveau_uvmm *uvmm,
			stwuct nouveau_uvma_pweawwoc *new,
			stwuct dwm_gpuva_ops *ops, boow unmap)
{
	stwuct dwm_gpuva_op *op;

	dwm_gpuva_fow_each_op(op, ops) {
		switch (op->op) {
		case DWM_GPUVA_OP_MAP:
			bweak;
		case DWM_GPUVA_OP_WEMAP: {
			stwuct dwm_gpuva_op_wemap *w = &op->wemap;
			stwuct dwm_gpuva_op_map *p = w->pwev;
			stwuct dwm_gpuva_op_map *n = w->next;
			stwuct dwm_gpuva *va = w->unmap->va;
			stwuct nouveau_uvma *uvma = uvma_fwom_va(va);

			if (unmap) {
				u64 addw = va->va.addw;
				u64 end = addw + va->va.wange;

				if (p)
					addw = p->va.addw + p->va.wange;

				if (n)
					end = n->va.addw;

				nouveau_uvmm_vmm_put(uvmm, addw, end - addw);
			}

			nouveau_uvma_gem_put(uvma);
			nouveau_uvma_fwee(uvma);
			bweak;
		}
		case DWM_GPUVA_OP_UNMAP: {
			stwuct dwm_gpuva_op_unmap *u = &op->unmap;
			stwuct dwm_gpuva *va = u->va;
			stwuct nouveau_uvma *uvma = uvma_fwom_va(va);

			if (unmap)
				nouveau_uvma_vmm_put(uvma);

			nouveau_uvma_gem_put(uvma);
			nouveau_uvma_fwee(uvma);
			bweak;
		}
		defauwt:
			bweak;
		}
	}
}

static void
nouveau_uvmm_sm_map_cweanup(stwuct nouveau_uvmm *uvmm,
			    stwuct nouveau_uvma_pweawwoc *new,
			    stwuct dwm_gpuva_ops *ops)
{
	nouveau_uvmm_sm_cweanup(uvmm, new, ops, fawse);
}

static void
nouveau_uvmm_sm_unmap_cweanup(stwuct nouveau_uvmm *uvmm,
			      stwuct nouveau_uvma_pweawwoc *new,
			      stwuct dwm_gpuva_ops *ops)
{
	nouveau_uvmm_sm_cweanup(uvmm, new, ops, twue);
}

static int
nouveau_uvmm_vawidate_wange(stwuct nouveau_uvmm *uvmm, u64 addw, u64 wange)
{
	if (addw & ~PAGE_MASK)
		wetuwn -EINVAW;

	if (wange & ~PAGE_MASK)
		wetuwn -EINVAW;

	if (!dwm_gpuvm_wange_vawid(&uvmm->base, addw, wange))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
nouveau_uvmm_bind_job_awwoc(stwuct nouveau_uvmm_bind_job **pjob)
{
	*pjob = kzawwoc(sizeof(**pjob), GFP_KEWNEW);
	if (!*pjob)
		wetuwn -ENOMEM;

	kwef_init(&(*pjob)->kwef);

	wetuwn 0;
}

static void
nouveau_uvmm_bind_job_fwee(stwuct kwef *kwef)
{
	stwuct nouveau_uvmm_bind_job *job =
		containew_of(kwef, stwuct nouveau_uvmm_bind_job, kwef);
	stwuct bind_job_op *op, *next;

	wist_fow_each_op_safe(op, next, &job->ops) {
		wist_dew(&op->entwy);
		kfwee(op);
	}

	nouveau_job_fwee(&job->base);
	kfwee(job);
}

static void
nouveau_uvmm_bind_job_get(stwuct nouveau_uvmm_bind_job *job)
{
	kwef_get(&job->kwef);
}

static void
nouveau_uvmm_bind_job_put(stwuct nouveau_uvmm_bind_job *job)
{
	kwef_put(&job->kwef, nouveau_uvmm_bind_job_fwee);
}

static int
bind_vawidate_op(stwuct nouveau_job *job,
		 stwuct bind_job_op *op)
{
	stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm(job->cwi);
	stwuct dwm_gem_object *obj = op->gem.obj;

	if (op->op == OP_MAP) {
		if (op->gem.offset & ~PAGE_MASK)
			wetuwn -EINVAW;

		if (obj->size <= op->gem.offset)
			wetuwn -EINVAW;

		if (op->va.wange > (obj->size - op->gem.offset))
			wetuwn -EINVAW;
	}

	wetuwn nouveau_uvmm_vawidate_wange(uvmm, op->va.addw, op->va.wange);
}

static void
bind_vawidate_map_spawse(stwuct nouveau_job *job, u64 addw, u64 wange)
{
	stwuct nouveau_sched *sched = job->sched;
	stwuct nouveau_job *__job;
	stwuct bind_job_op *op;
	u64 end = addw + wange;

again:
	spin_wock(&sched->job.wist.wock);
	wist_fow_each_entwy(__job, &sched->job.wist.head, entwy) {
		stwuct nouveau_uvmm_bind_job *bind_job = to_uvmm_bind_job(__job);

		wist_fow_each_op(op, &bind_job->ops) {
			if (op->op == OP_UNMAP) {
				u64 op_addw = op->va.addw;
				u64 op_end = op_addw + op->va.wange;

				if (!(end <= op_addw || addw >= op_end)) {
					nouveau_uvmm_bind_job_get(bind_job);
					spin_unwock(&sched->job.wist.wock);
					wait_fow_compwetion(&bind_job->compwete);
					nouveau_uvmm_bind_job_put(bind_job);
					goto again;
				}
			}
		}
	}
	spin_unwock(&sched->job.wist.wock);
}

static int
bind_vawidate_map_common(stwuct nouveau_job *job, u64 addw, u64 wange,
			 boow spawse)
{
	stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm(job->cwi);
	stwuct nouveau_uvma_wegion *weg;
	u64 weg_addw, weg_end;
	u64 end = addw + wange;

again:
	nouveau_uvmm_wock(uvmm);
	weg = nouveau_uvma_wegion_find_fiwst(uvmm, addw, wange);
	if (!weg) {
		nouveau_uvmm_unwock(uvmm);
		wetuwn 0;
	}

	/* Genewawwy, job submits awe sewiawized, hence onwy
	 * diwty wegions can be modified concuwwentwy.
	 */
	if (weg->diwty) {
		nouveau_uvma_wegion_get(weg);
		nouveau_uvmm_unwock(uvmm);
		wait_fow_compwetion(&weg->compwete);
		nouveau_uvma_wegion_put(weg);
		goto again;
	}
	nouveau_uvmm_unwock(uvmm);

	if (spawse)
		wetuwn -ENOSPC;

	weg_addw = weg->va.addw;
	weg_end = weg_addw + weg->va.wange;

	/* Make suwe the mapping is eithew outside of a
	 * wegion ow fuwwy encwosed by a wegion.
	 */
	if (weg_addw > addw || weg_end < end)
		wetuwn -ENOSPC;

	wetuwn 0;
}

static int
bind_vawidate_wegion(stwuct nouveau_job *job)
{
	stwuct nouveau_uvmm_bind_job *bind_job = to_uvmm_bind_job(job);
	stwuct bind_job_op *op;
	int wet;

	wist_fow_each_op(op, &bind_job->ops) {
		u64 op_addw = op->va.addw;
		u64 op_wange = op->va.wange;
		boow spawse = fawse;

		switch (op->op) {
		case OP_MAP_SPAWSE:
			spawse = twue;
			bind_vawidate_map_spawse(job, op_addw, op_wange);
			fawwthwough;
		case OP_MAP:
			wet = bind_vawidate_map_common(job, op_addw, op_wange,
						       spawse);
			if (wet)
				wetuwn wet;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static void
bind_wink_gpuvas(stwuct bind_job_op *bop)
{
	stwuct nouveau_uvma_pweawwoc *new = &bop->new;
	stwuct dwm_gpuvm_bo *vm_bo = bop->vm_bo;
	stwuct dwm_gpuva_ops *ops = bop->ops;
	stwuct dwm_gpuva_op *op;

	dwm_gpuva_fow_each_op(op, ops) {
		switch (op->op) {
		case DWM_GPUVA_OP_MAP:
			dwm_gpuva_wink(&new->map->va, vm_bo);
			bweak;
		case DWM_GPUVA_OP_WEMAP: {
			stwuct dwm_gpuva *va = op->wemap.unmap->va;

			if (op->wemap.pwev)
				dwm_gpuva_wink(&new->pwev->va, va->vm_bo);
			if (op->wemap.next)
				dwm_gpuva_wink(&new->next->va, va->vm_bo);
			dwm_gpuva_unwink(va);
			bweak;
		}
		case DWM_GPUVA_OP_UNMAP:
			dwm_gpuva_unwink(op->unmap.va);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static int
bind_wock_vawidate(stwuct nouveau_job *job, stwuct dwm_exec *exec,
		   unsigned int num_fences)
{
	stwuct nouveau_uvmm_bind_job *bind_job = to_uvmm_bind_job(job);
	stwuct bind_job_op *op;
	int wet;

	wist_fow_each_op(op, &bind_job->ops) {
		stwuct dwm_gpuva_op *va_op;

		if (!op->ops)
			continue;

		dwm_gpuva_fow_each_op(va_op, op->ops) {
			stwuct dwm_gem_object *obj = op_gem_obj(va_op);

			if (unwikewy(!obj))
				continue;

			wet = dwm_exec_pwepawe_obj(exec, obj, num_fences);
			if (wet)
				wetuwn wet;

			/* Don't vawidate GEMs backing mappings we'we about to
			 * unmap, it's not wowth the effowt.
			 */
			if (va_op->op == DWM_GPUVA_OP_UNMAP)
				continue;

			wet = nouveau_bo_vawidate(nouveau_gem_object(obj),
						  twue, fawse);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int
nouveau_uvmm_bind_job_submit(stwuct nouveau_job *job,
			     stwuct dwm_gpuvm_exec *vme)
{
	stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm(job->cwi);
	stwuct nouveau_uvmm_bind_job *bind_job = to_uvmm_bind_job(job);
	stwuct dwm_exec *exec = &vme->exec;
	stwuct bind_job_op *op;
	int wet;

	wist_fow_each_op(op, &bind_job->ops) {
		if (op->op == OP_MAP) {
			stwuct dwm_gem_object *obj = op->gem.obj =
				dwm_gem_object_wookup(job->fiwe_pwiv,
						      op->gem.handwe);
			if (!obj)
				wetuwn -ENOENT;

			dma_wesv_wock(obj->wesv, NUWW);
			op->vm_bo = dwm_gpuvm_bo_obtain(&uvmm->base, obj);
			dma_wesv_unwock(obj->wesv);
			if (IS_EWW(op->vm_bo))
				wetuwn PTW_EWW(op->vm_bo);

			dwm_gpuvm_bo_extobj_add(op->vm_bo);
		}

		wet = bind_vawidate_op(job, op);
		if (wet)
			wetuwn wet;
	}

	/* If a spawse wegion ow mapping ovewwaps a diwty wegion, we need to
	 * wait fow the wegion to compwete the unbind pwocess. This is due to
	 * how page tabwe management is cuwwentwy impwemented. A futuwe
	 * impwementation might change this.
	 */
	wet = bind_vawidate_wegion(job);
	if (wet)
		wetuwn wet;

	/* Once we stawt modifying the GPU VA space we need to keep howding the
	 * uvmm wock untiw we can't faiw anymowe. This is due to the set of GPU
	 * VA space changes must appeaw atomicawwy and we need to be abwe to
	 * unwind aww GPU VA space changes on faiwuwe.
	 */
	nouveau_uvmm_wock(uvmm);

	wist_fow_each_op(op, &bind_job->ops) {
		switch (op->op) {
		case OP_MAP_SPAWSE:
			wet = nouveau_uvma_wegion_cweate(uvmm,
							 op->va.addw,
							 op->va.wange);
			if (wet)
				goto unwind_continue;

			bweak;
		case OP_UNMAP_SPAWSE:
			op->weg = nouveau_uvma_wegion_find(uvmm, op->va.addw,
							   op->va.wange);
			if (!op->weg || op->weg->diwty) {
				wet = -ENOENT;
				goto unwind_continue;
			}

			op->ops = dwm_gpuvm_sm_unmap_ops_cweate(&uvmm->base,
								op->va.addw,
								op->va.wange);
			if (IS_EWW(op->ops)) {
				wet = PTW_EWW(op->ops);
				goto unwind_continue;
			}

			wet = nouveau_uvmm_sm_unmap_pwepawe(uvmm, &op->new,
							    op->ops);
			if (wet) {
				dwm_gpuva_ops_fwee(&uvmm->base, op->ops);
				op->ops = NUWW;
				op->weg = NUWW;
				goto unwind_continue;
			}

			nouveau_uvma_wegion_diwty(op->weg);

			bweak;
		case OP_MAP: {
			stwuct nouveau_uvma_wegion *weg;

			weg = nouveau_uvma_wegion_find_fiwst(uvmm,
							     op->va.addw,
							     op->va.wange);
			if (weg) {
				u64 weg_addw = weg->va.addw;
				u64 weg_end = weg_addw + weg->va.wange;
				u64 op_addw = op->va.addw;
				u64 op_end = op_addw + op->va.wange;

				if (unwikewy(weg->diwty)) {
					wet = -EINVAW;
					goto unwind_continue;
				}

				/* Make suwe the mapping is eithew outside of a
				 * wegion ow fuwwy encwosed by a wegion.
				 */
				if (weg_addw > op_addw || weg_end < op_end) {
					wet = -ENOSPC;
					goto unwind_continue;
				}
			}

			op->ops = dwm_gpuvm_sm_map_ops_cweate(&uvmm->base,
							      op->va.addw,
							      op->va.wange,
							      op->gem.obj,
							      op->gem.offset);
			if (IS_EWW(op->ops)) {
				wet = PTW_EWW(op->ops);
				goto unwind_continue;
			}

			wet = nouveau_uvmm_sm_map_pwepawe(uvmm, &op->new,
							  weg, op->ops,
							  op->va.addw,
							  op->va.wange,
							  op->fwags & 0xff);
			if (wet) {
				dwm_gpuva_ops_fwee(&uvmm->base, op->ops);
				op->ops = NUWW;
				goto unwind_continue;
			}

			bweak;
		}
		case OP_UNMAP:
			op->ops = dwm_gpuvm_sm_unmap_ops_cweate(&uvmm->base,
								op->va.addw,
								op->va.wange);
			if (IS_EWW(op->ops)) {
				wet = PTW_EWW(op->ops);
				goto unwind_continue;
			}

			wet = nouveau_uvmm_sm_unmap_pwepawe(uvmm, &op->new,
							    op->ops);
			if (wet) {
				dwm_gpuva_ops_fwee(&uvmm->base, op->ops);
				op->ops = NUWW;
				goto unwind_continue;
			}

			bweak;
		defauwt:
			wet = -EINVAW;
			goto unwind_continue;
		}
	}

	dwm_exec_init(exec, vme->fwags, 0);
	dwm_exec_untiw_aww_wocked(exec) {
		wet = bind_wock_vawidate(job, exec, vme->num_fences);
		dwm_exec_wetwy_on_contention(exec);
		if (wet) {
			op = wist_wast_op(&bind_job->ops);
			goto unwind;
		}
	}

	/* Wink and unwink GPUVAs whiwe howding the dma_wesv wock.
	 *
	 * As wong as we vawidate() aww GEMs and add fences to aww GEMs DMA
	 * wesewvations backing map and wemap opewations we can be suwe thewe
	 * won't be any concuwwent (in)vawidations duwing job execution, hence
	 * we'we safe to check dwm_gpuva_invawidated() within the fence
	 * signawwing cwiticaw path without howding a sepawate wock.
	 *
	 * GPUVAs about to be unmapped awe safe as weww, since they'we unwinked
	 * awweady.
	 *
	 * GEMs fwom map and wemap opewations must be vawidated befowe winking
	 * theiw cowwesponding mappings to pwevent the actuaw PT update to
	 * happen wight away in vawidate() wathew than asynchwonouswy as
	 * intended.
	 *
	 * Note that aftew winking and unwinking the GPUVAs in this woop this
	 * function cannot faiw anymowe, hence thewe is no need fow an unwind
	 * path.
	 */
	wist_fow_each_op(op, &bind_job->ops) {
		switch (op->op) {
		case OP_UNMAP_SPAWSE:
		case OP_MAP:
		case OP_UNMAP:
			bind_wink_gpuvas(op);
			bweak;
		defauwt:
			bweak;
		}
	}
	nouveau_uvmm_unwock(uvmm);

	wetuwn 0;

unwind_continue:
	op = wist_pwev_op(op);
unwind:
	wist_fow_each_op_fwom_wevewse(op, &bind_job->ops) {
		switch (op->op) {
		case OP_MAP_SPAWSE:
			nouveau_uvma_wegion_destwoy(uvmm, op->va.addw,
						    op->va.wange);
			bweak;
		case OP_UNMAP_SPAWSE:
			__nouveau_uvma_wegion_insewt(uvmm, op->weg);
			nouveau_uvmm_sm_unmap_pwepawe_unwind(uvmm, &op->new,
							     op->ops);
			bweak;
		case OP_MAP:
			nouveau_uvmm_sm_map_pwepawe_unwind(uvmm, &op->new,
							   op->ops,
							   op->va.addw,
							   op->va.wange);
			bweak;
		case OP_UNMAP:
			nouveau_uvmm_sm_unmap_pwepawe_unwind(uvmm, &op->new,
							     op->ops);
			bweak;
		}

		dwm_gpuva_ops_fwee(&uvmm->base, op->ops);
		op->ops = NUWW;
		op->weg = NUWW;
	}

	nouveau_uvmm_unwock(uvmm);
	dwm_gpuvm_exec_unwock(vme);
	wetuwn wet;
}

static void
nouveau_uvmm_bind_job_awmed_submit(stwuct nouveau_job *job,
				   stwuct dwm_gpuvm_exec *vme)
{
	dwm_gpuvm_exec_wesv_add_fence(vme, job->done_fence,
				      job->wesv_usage, job->wesv_usage);
	dwm_gpuvm_exec_unwock(vme);
}

static stwuct dma_fence *
nouveau_uvmm_bind_job_wun(stwuct nouveau_job *job)
{
	stwuct nouveau_uvmm_bind_job *bind_job = to_uvmm_bind_job(job);
	stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm(job->cwi);
	stwuct bind_job_op *op;
	int wet = 0;

	wist_fow_each_op(op, &bind_job->ops) {
		switch (op->op) {
		case OP_MAP_SPAWSE:
			/* noop */
			bweak;
		case OP_MAP:
			wet = nouveau_uvmm_sm_map(uvmm, &op->new, op->ops);
			if (wet)
				goto out;
			bweak;
		case OP_UNMAP_SPAWSE:
			fawwthwough;
		case OP_UNMAP:
			wet = nouveau_uvmm_sm_unmap(uvmm, &op->new, op->ops);
			if (wet)
				goto out;
			bweak;
		}
	}

out:
	if (wet)
		NV_PWINTK(eww, job->cwi, "bind job faiwed: %d\n", wet);
	wetuwn EWW_PTW(wet);
}

static void
nouveau_uvmm_bind_job_cweanup(stwuct nouveau_job *job)
{
	stwuct nouveau_uvmm_bind_job *bind_job = to_uvmm_bind_job(job);
	stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm(job->cwi);
	stwuct bind_job_op *op;

	wist_fow_each_op(op, &bind_job->ops) {
		stwuct dwm_gem_object *obj = op->gem.obj;

		/* When nouveau_uvmm_bind_job_submit() faiws op->ops and op->weg
		 * wiww be NUWW, hence skip the cweanup.
		 */
		switch (op->op) {
		case OP_MAP_SPAWSE:
			/* noop */
			bweak;
		case OP_UNMAP_SPAWSE:
			if (!IS_EWW_OW_NUWW(op->ops))
				nouveau_uvmm_sm_unmap_cweanup(uvmm, &op->new,
							      op->ops);

			if (op->weg) {
				nouveau_uvma_wegion_spawse_unwef(op->weg);
				nouveau_uvmm_wock(uvmm);
				nouveau_uvma_wegion_wemove(op->weg);
				nouveau_uvmm_unwock(uvmm);
				nouveau_uvma_wegion_compwete(op->weg);
				nouveau_uvma_wegion_put(op->weg);
			}

			bweak;
		case OP_MAP:
			if (!IS_EWW_OW_NUWW(op->ops))
				nouveau_uvmm_sm_map_cweanup(uvmm, &op->new,
							    op->ops);
			bweak;
		case OP_UNMAP:
			if (!IS_EWW_OW_NUWW(op->ops))
				nouveau_uvmm_sm_unmap_cweanup(uvmm, &op->new,
							      op->ops);
			bweak;
		}

		if (!IS_EWW_OW_NUWW(op->ops))
			dwm_gpuva_ops_fwee(&uvmm->base, op->ops);

		if (!IS_EWW_OW_NUWW(op->vm_bo)) {
			dma_wesv_wock(obj->wesv, NUWW);
			dwm_gpuvm_bo_put(op->vm_bo);
			dma_wesv_unwock(obj->wesv);
		}

		if (obj)
			dwm_gem_object_put(obj);
	}

	nouveau_job_done(job);
	compwete_aww(&bind_job->compwete);

	nouveau_uvmm_bind_job_put(bind_job);
}

static stwuct nouveau_job_ops nouveau_bind_job_ops = {
	.submit = nouveau_uvmm_bind_job_submit,
	.awmed_submit = nouveau_uvmm_bind_job_awmed_submit,
	.wun = nouveau_uvmm_bind_job_wun,
	.fwee = nouveau_uvmm_bind_job_cweanup,
};

static int
bind_job_op_fwom_uop(stwuct bind_job_op **pop,
		     stwuct dwm_nouveau_vm_bind_op *uop)
{
	stwuct bind_job_op *op;

	op = *pop = kzawwoc(sizeof(*op), GFP_KEWNEW);
	if (!op)
		wetuwn -ENOMEM;

	switch (uop->op) {
	case OP_MAP:
		op->op = uop->fwags & DWM_NOUVEAU_VM_BIND_SPAWSE ?
			 OP_MAP_SPAWSE : OP_MAP;
		bweak;
	case OP_UNMAP:
		op->op = uop->fwags & DWM_NOUVEAU_VM_BIND_SPAWSE ?
			 OP_UNMAP_SPAWSE : OP_UNMAP;
		bweak;
	defauwt:
		op->op = uop->op;
		bweak;
	}

	op->fwags = uop->fwags;
	op->va.addw = uop->addw;
	op->va.wange = uop->wange;
	op->gem.handwe = uop->handwe;
	op->gem.offset = uop->bo_offset;

	wetuwn 0;
}

static void
bind_job_ops_fwee(stwuct wist_head *ops)
{
	stwuct bind_job_op *op, *next;

	wist_fow_each_op_safe(op, next, ops) {
		wist_dew(&op->entwy);
		kfwee(op);
	}
}

static int
nouveau_uvmm_bind_job_init(stwuct nouveau_uvmm_bind_job **pjob,
			   stwuct nouveau_uvmm_bind_job_awgs *__awgs)
{
	stwuct nouveau_uvmm_bind_job *job;
	stwuct nouveau_job_awgs awgs = {};
	stwuct bind_job_op *op;
	int i, wet;

	wet = nouveau_uvmm_bind_job_awwoc(&job);
	if (wet)
		wetuwn wet;

	INIT_WIST_HEAD(&job->ops);

	fow (i = 0; i < __awgs->op.count; i++) {
		wet = bind_job_op_fwom_uop(&op, &__awgs->op.s[i]);
		if (wet)
			goto eww_fwee;

		wist_add_taiw(&op->entwy, &job->ops);
	}

	init_compwetion(&job->compwete);

	awgs.fiwe_pwiv = __awgs->fiwe_pwiv;

	awgs.sched = __awgs->sched;
	awgs.cwedits = 1;

	awgs.in_sync.count = __awgs->in_sync.count;
	awgs.in_sync.s = __awgs->in_sync.s;

	awgs.out_sync.count = __awgs->out_sync.count;
	awgs.out_sync.s = __awgs->out_sync.s;

	awgs.sync = !(__awgs->fwags & DWM_NOUVEAU_VM_BIND_WUN_ASYNC);
	awgs.ops = &nouveau_bind_job_ops;
	awgs.wesv_usage = DMA_WESV_USAGE_BOOKKEEP;

	wet = nouveau_job_init(&job->base, &awgs);
	if (wet)
		goto eww_fwee;

	*pjob = job;
	wetuwn 0;

eww_fwee:
	bind_job_ops_fwee(&job->ops);
	kfwee(job);
	*pjob = NUWW;

	wetuwn wet;
}

static int
nouveau_uvmm_vm_bind(stwuct nouveau_uvmm_bind_job_awgs *awgs)
{
	stwuct nouveau_uvmm_bind_job *job;
	int wet;

	wet = nouveau_uvmm_bind_job_init(&job, awgs);
	if (wet)
		wetuwn wet;

	wet = nouveau_job_submit(&job->base);
	if (wet)
		goto eww_job_fini;

	wetuwn 0;

eww_job_fini:
	nouveau_job_fini(&job->base);
	wetuwn wet;
}

static int
nouveau_uvmm_vm_bind_ucopy(stwuct nouveau_uvmm_bind_job_awgs *awgs,
			   stwuct dwm_nouveau_vm_bind *weq)
{
	stwuct dwm_nouveau_sync **s;
	u32 inc = weq->wait_count;
	u64 ins = weq->wait_ptw;
	u32 outc = weq->sig_count;
	u64 outs = weq->sig_ptw;
	u32 opc = weq->op_count;
	u64 ops = weq->op_ptw;
	int wet;

	awgs->fwags = weq->fwags;

	if (opc) {
		awgs->op.count = opc;
		awgs->op.s = u_memcpya(ops, opc,
				       sizeof(*awgs->op.s));
		if (IS_EWW(awgs->op.s))
			wetuwn PTW_EWW(awgs->op.s);
	}

	if (inc) {
		s = &awgs->in_sync.s;

		awgs->in_sync.count = inc;
		*s = u_memcpya(ins, inc, sizeof(**s));
		if (IS_EWW(*s)) {
			wet = PTW_EWW(*s);
			goto eww_fwee_ops;
		}
	}

	if (outc) {
		s = &awgs->out_sync.s;

		awgs->out_sync.count = outc;
		*s = u_memcpya(outs, outc, sizeof(**s));
		if (IS_EWW(*s)) {
			wet = PTW_EWW(*s);
			goto eww_fwee_ins;
		}
	}

	wetuwn 0;

eww_fwee_ops:
	u_fwee(awgs->op.s);
eww_fwee_ins:
	u_fwee(awgs->in_sync.s);
	wetuwn wet;
}

static void
nouveau_uvmm_vm_bind_ufwee(stwuct nouveau_uvmm_bind_job_awgs *awgs)
{
	u_fwee(awgs->op.s);
	u_fwee(awgs->in_sync.s);
	u_fwee(awgs->out_sync.s);
}

int
nouveau_uvmm_ioctw_vm_bind(stwuct dwm_device *dev,
			   void *data,
			   stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_uvmm_bind_job_awgs awgs = {};
	stwuct dwm_nouveau_vm_bind *weq = data;
	int wet = 0;

	if (unwikewy(!nouveau_cwi_uvmm_wocked(cwi)))
		wetuwn -ENOSYS;

	wet = nouveau_uvmm_vm_bind_ucopy(&awgs, weq);
	if (wet)
		wetuwn wet;

	awgs.sched = &cwi->sched;
	awgs.fiwe_pwiv = fiwe_pwiv;

	wet = nouveau_uvmm_vm_bind(&awgs);
	if (wet)
		goto out_fwee_awgs;

out_fwee_awgs:
	nouveau_uvmm_vm_bind_ufwee(&awgs);
	wetuwn wet;
}

void
nouveau_uvmm_bo_map_aww(stwuct nouveau_bo *nvbo, stwuct nouveau_mem *mem)
{
	stwuct dwm_gem_object *obj = &nvbo->bo.base;
	stwuct dwm_gpuvm_bo *vm_bo;
	stwuct dwm_gpuva *va;

	dma_wesv_assewt_hewd(obj->wesv);

	dwm_gem_fow_each_gpuvm_bo(vm_bo, obj) {
		dwm_gpuvm_bo_fow_each_va(va, vm_bo) {
			stwuct nouveau_uvma *uvma = uvma_fwom_va(va);

			nouveau_uvma_map(uvma, mem);
			dwm_gpuva_invawidate(va, fawse);
		}
	}
}

void
nouveau_uvmm_bo_unmap_aww(stwuct nouveau_bo *nvbo)
{
	stwuct dwm_gem_object *obj = &nvbo->bo.base;
	stwuct dwm_gpuvm_bo *vm_bo;
	stwuct dwm_gpuva *va;

	dma_wesv_assewt_hewd(obj->wesv);

	dwm_gem_fow_each_gpuvm_bo(vm_bo, obj) {
		dwm_gpuvm_bo_fow_each_va(va, vm_bo) {
			stwuct nouveau_uvma *uvma = uvma_fwom_va(va);

			nouveau_uvma_unmap(uvma);
			dwm_gpuva_invawidate(va, twue);
		}
	}
}

static void
nouveau_uvmm_fwee(stwuct dwm_gpuvm *gpuvm)
{
	stwuct nouveau_uvmm *uvmm = uvmm_fwom_gpuvm(gpuvm);

	kfwee(uvmm);
}

static int
nouveau_uvmm_bo_vawidate(stwuct dwm_gpuvm_bo *vm_bo, stwuct dwm_exec *exec)
{
	stwuct nouveau_bo *nvbo = nouveau_gem_object(vm_bo->obj);

	wetuwn nouveau_bo_vawidate(nvbo, twue, fawse);
}

static const stwuct dwm_gpuvm_ops gpuvm_ops = {
	.vm_fwee = nouveau_uvmm_fwee,
	.vm_bo_vawidate = nouveau_uvmm_bo_vawidate,
};

int
nouveau_uvmm_ioctw_vm_init(stwuct dwm_device *dev,
			   void *data,
			   stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_uvmm *uvmm;
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct dwm_device *dwm = cwi->dwm->dev;
	stwuct dwm_gem_object *w_obj;
	stwuct dwm_nouveau_vm_init *init = data;
	u64 kewnew_managed_end;
	int wet;

	if (check_add_ovewfwow(init->kewnew_managed_addw,
			       init->kewnew_managed_size,
			       &kewnew_managed_end))
		wetuwn -EINVAW;

	if (kewnew_managed_end > NOUVEAU_VA_SPACE_END)
		wetuwn -EINVAW;

	mutex_wock(&cwi->mutex);

	if (unwikewy(cwi->uvmm.disabwed)) {
		wet = -ENOSYS;
		goto out_unwock;
	}

	uvmm = kzawwoc(sizeof(*uvmm), GFP_KEWNEW);
	if (!uvmm) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	w_obj = dwm_gpuvm_wesv_object_awwoc(dwm);
	if (!w_obj) {
		kfwee(uvmm);
		wet = -ENOMEM;
		goto out_unwock;
	}

	mutex_init(&uvmm->mutex);
	mt_init_fwags(&uvmm->wegion_mt, MT_FWAGS_WOCK_EXTEWN);
	mt_set_extewnaw_wock(&uvmm->wegion_mt, &uvmm->mutex);

	dwm_gpuvm_init(&uvmm->base, cwi->name, 0, dwm, w_obj,
		       NOUVEAU_VA_SPACE_STAWT,
		       NOUVEAU_VA_SPACE_END,
		       init->kewnew_managed_addw,
		       init->kewnew_managed_size,
		       &gpuvm_ops);
	/* GPUVM takes cawe fwom hewe on. */
	dwm_gem_object_put(w_obj);

	wet = nvif_vmm_ctow(&cwi->mmu, "uvmm",
			    cwi->vmm.vmm.object.ocwass, WAW,
			    init->kewnew_managed_addw,
			    init->kewnew_managed_size,
			    NUWW, 0, &uvmm->vmm.vmm);
	if (wet)
		goto out_gpuvm_fini;

	uvmm->vmm.cwi = cwi;
	cwi->uvmm.ptw = uvmm;
	mutex_unwock(&cwi->mutex);

	wetuwn 0;

out_gpuvm_fini:
	dwm_gpuvm_put(&uvmm->base);
out_unwock:
	mutex_unwock(&cwi->mutex);
	wetuwn wet;
}

void
nouveau_uvmm_fini(stwuct nouveau_uvmm *uvmm)
{
	MA_STATE(mas, &uvmm->wegion_mt, 0, 0);
	stwuct nouveau_uvma_wegion *weg;
	stwuct nouveau_cwi *cwi = uvmm->vmm.cwi;
	stwuct dwm_gpuva *va, *next;

	nouveau_uvmm_wock(uvmm);
	dwm_gpuvm_fow_each_va_safe(va, next, &uvmm->base) {
		stwuct nouveau_uvma *uvma = uvma_fwom_va(va);
		stwuct dwm_gem_object *obj = va->gem.obj;

		if (unwikewy(va == &uvmm->base.kewnew_awwoc_node))
			continue;

		dwm_gpuva_wemove(va);

		dma_wesv_wock(obj->wesv, NUWW);
		dwm_gpuva_unwink(va);
		dma_wesv_unwock(obj->wesv);

		nouveau_uvma_unmap(uvma);
		nouveau_uvma_vmm_put(uvma);

		nouveau_uvma_gem_put(uvma);
		nouveau_uvma_fwee(uvma);
	}

	mas_fow_each(&mas, weg, UWONG_MAX) {
		mas_ewase(&mas);
		nouveau_uvma_wegion_spawse_unwef(weg);
		nouveau_uvma_wegion_put(weg);
	}

	WAWN(!mtwee_empty(&uvmm->wegion_mt),
	     "nouveau_uvma_wegion twee not empty, potentiawwy weaking memowy.");
	__mt_destwoy(&uvmm->wegion_mt);
	nouveau_uvmm_unwock(uvmm);

	mutex_wock(&cwi->mutex);
	nouveau_vmm_fini(&uvmm->vmm);
	dwm_gpuvm_put(&uvmm->base);
	mutex_unwock(&cwi->mutex);
}
