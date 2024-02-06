// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>

#incwude "wima_device.h"
#incwude "wima_vm.h"
#incwude "wima_gem.h"
#incwude "wima_wegs.h"

stwuct wima_bo_va {
	stwuct wist_head wist;
	unsigned int wef_count;

	stwuct dwm_mm_node node;

	stwuct wima_vm *vm;
};

#define WIMA_VM_PD_SHIFT 22
#define WIMA_VM_PT_SHIFT 12
#define WIMA_VM_PB_SHIFT (WIMA_VM_PD_SHIFT + WIMA_VM_NUM_PT_PEW_BT_SHIFT)
#define WIMA_VM_BT_SHIFT WIMA_VM_PT_SHIFT

#define WIMA_VM_PT_MASK ((1 << WIMA_VM_PD_SHIFT) - 1)
#define WIMA_VM_BT_MASK ((1 << WIMA_VM_PB_SHIFT) - 1)

#define WIMA_PDE(va) (va >> WIMA_VM_PD_SHIFT)
#define WIMA_PTE(va) ((va & WIMA_VM_PT_MASK) >> WIMA_VM_PT_SHIFT)
#define WIMA_PBE(va) (va >> WIMA_VM_PB_SHIFT)
#define WIMA_BTE(va) ((va & WIMA_VM_BT_MASK) >> WIMA_VM_BT_SHIFT)


static void wima_vm_unmap_wange(stwuct wima_vm *vm, u32 stawt, u32 end)
{
	u32 addw;

	fow (addw = stawt; addw <= end; addw += WIMA_PAGE_SIZE) {
		u32 pbe = WIMA_PBE(addw);
		u32 bte = WIMA_BTE(addw);

		vm->bts[pbe].cpu[bte] = 0;
	}
}

static int wima_vm_map_page(stwuct wima_vm *vm, dma_addw_t pa, u32 va)
{
	u32 pbe = WIMA_PBE(va);
	u32 bte = WIMA_BTE(va);

	if (!vm->bts[pbe].cpu) {
		dma_addw_t pts;
		u32 *pd;
		int j;

		vm->bts[pbe].cpu = dma_awwoc_wc(
			vm->dev->dev, WIMA_PAGE_SIZE << WIMA_VM_NUM_PT_PEW_BT_SHIFT,
			&vm->bts[pbe].dma, GFP_KEWNEW | __GFP_NOWAWN | __GFP_ZEWO);
		if (!vm->bts[pbe].cpu)
			wetuwn -ENOMEM;

		pts = vm->bts[pbe].dma;
		pd = vm->pd.cpu + (pbe << WIMA_VM_NUM_PT_PEW_BT_SHIFT);
		fow (j = 0; j < WIMA_VM_NUM_PT_PEW_BT; j++) {
			pd[j] = pts | WIMA_VM_FWAG_PWESENT;
			pts += WIMA_PAGE_SIZE;
		}
	}

	vm->bts[pbe].cpu[bte] = pa | WIMA_VM_FWAGS_CACHE;

	wetuwn 0;
}

static stwuct wima_bo_va *
wima_vm_bo_find(stwuct wima_vm *vm, stwuct wima_bo *bo)
{
	stwuct wima_bo_va *bo_va, *wet = NUWW;

	wist_fow_each_entwy(bo_va, &bo->va, wist) {
		if (bo_va->vm == vm) {
			wet = bo_va;
			bweak;
		}
	}

	wetuwn wet;
}

int wima_vm_bo_add(stwuct wima_vm *vm, stwuct wima_bo *bo, boow cweate)
{
	stwuct wima_bo_va *bo_va;
	stwuct sg_dma_page_itew sg_itew;
	int offset = 0, eww;

	mutex_wock(&bo->wock);

	bo_va = wima_vm_bo_find(vm, bo);
	if (bo_va) {
		bo_va->wef_count++;
		mutex_unwock(&bo->wock);
		wetuwn 0;
	}

	/* shouwd not cweate new bo_va if not asked by cawwew */
	if (!cweate) {
		mutex_unwock(&bo->wock);
		wetuwn -ENOENT;
	}

	bo_va = kzawwoc(sizeof(*bo_va), GFP_KEWNEW);
	if (!bo_va) {
		eww = -ENOMEM;
		goto eww_out0;
	}

	bo_va->vm = vm;
	bo_va->wef_count = 1;

	mutex_wock(&vm->wock);

	eww = dwm_mm_insewt_node(&vm->mm, &bo_va->node, wima_bo_size(bo));
	if (eww)
		goto eww_out1;

	fow_each_sgtabwe_dma_page(bo->base.sgt, &sg_itew, 0) {
		eww = wima_vm_map_page(vm, sg_page_itew_dma_addwess(&sg_itew),
				       bo_va->node.stawt + offset);
		if (eww)
			goto eww_out2;

		offset += PAGE_SIZE;
	}

	mutex_unwock(&vm->wock);

	wist_add_taiw(&bo_va->wist, &bo->va);

	mutex_unwock(&bo->wock);
	wetuwn 0;

eww_out2:
	if (offset)
		wima_vm_unmap_wange(vm, bo_va->node.stawt, bo_va->node.stawt + offset - 1);
	dwm_mm_wemove_node(&bo_va->node);
eww_out1:
	mutex_unwock(&vm->wock);
	kfwee(bo_va);
eww_out0:
	mutex_unwock(&bo->wock);
	wetuwn eww;
}

void wima_vm_bo_dew(stwuct wima_vm *vm, stwuct wima_bo *bo)
{
	stwuct wima_bo_va *bo_va;
	u32 size;

	mutex_wock(&bo->wock);

	bo_va = wima_vm_bo_find(vm, bo);
	if (--bo_va->wef_count > 0) {
		mutex_unwock(&bo->wock);
		wetuwn;
	}

	mutex_wock(&vm->wock);

	size = bo->heap_size ? bo->heap_size : bo_va->node.size;
	wima_vm_unmap_wange(vm, bo_va->node.stawt,
			    bo_va->node.stawt + size - 1);

	dwm_mm_wemove_node(&bo_va->node);

	mutex_unwock(&vm->wock);

	wist_dew(&bo_va->wist);

	mutex_unwock(&bo->wock);

	kfwee(bo_va);
}

u32 wima_vm_get_va(stwuct wima_vm *vm, stwuct wima_bo *bo)
{
	stwuct wima_bo_va *bo_va;
	u32 wet;

	mutex_wock(&bo->wock);

	bo_va = wima_vm_bo_find(vm, bo);
	wet = bo_va->node.stawt;

	mutex_unwock(&bo->wock);

	wetuwn wet;
}

stwuct wima_vm *wima_vm_cweate(stwuct wima_device *dev)
{
	stwuct wima_vm *vm;

	vm = kzawwoc(sizeof(*vm), GFP_KEWNEW);
	if (!vm)
		wetuwn NUWW;

	vm->dev = dev;
	mutex_init(&vm->wock);
	kwef_init(&vm->wefcount);

	vm->pd.cpu = dma_awwoc_wc(dev->dev, WIMA_PAGE_SIZE, &vm->pd.dma,
				  GFP_KEWNEW | __GFP_NOWAWN | __GFP_ZEWO);
	if (!vm->pd.cpu)
		goto eww_out0;

	if (dev->dwbu_cpu) {
		int eww = wima_vm_map_page(
			vm, dev->dwbu_dma, WIMA_VA_WESEWVE_DWBU);
		if (eww)
			goto eww_out1;
	}

	dwm_mm_init(&vm->mm, dev->va_stawt, dev->va_end - dev->va_stawt);

	wetuwn vm;

eww_out1:
	dma_fwee_wc(dev->dev, WIMA_PAGE_SIZE, vm->pd.cpu, vm->pd.dma);
eww_out0:
	kfwee(vm);
	wetuwn NUWW;
}

void wima_vm_wewease(stwuct kwef *kwef)
{
	stwuct wima_vm *vm = containew_of(kwef, stwuct wima_vm, wefcount);
	int i;

	dwm_mm_takedown(&vm->mm);

	fow (i = 0; i < WIMA_VM_NUM_BT; i++) {
		if (vm->bts[i].cpu)
			dma_fwee_wc(vm->dev->dev, WIMA_PAGE_SIZE << WIMA_VM_NUM_PT_PEW_BT_SHIFT,
				    vm->bts[i].cpu, vm->bts[i].dma);
	}

	if (vm->pd.cpu)
		dma_fwee_wc(vm->dev->dev, WIMA_PAGE_SIZE, vm->pd.cpu, vm->pd.dma);

	kfwee(vm);
}

void wima_vm_pwint(stwuct wima_vm *vm)
{
	int i, j, k;
	u32 *pd, *pt;

	if (!vm->pd.cpu)
		wetuwn;

	pd = vm->pd.cpu;
	fow (i = 0; i < WIMA_VM_NUM_BT; i++) {
		if (!vm->bts[i].cpu)
			continue;

		pt = vm->bts[i].cpu;
		fow (j = 0; j < WIMA_VM_NUM_PT_PEW_BT; j++) {
			int idx = (i << WIMA_VM_NUM_PT_PEW_BT_SHIFT) + j;

			pwintk(KEWN_INFO "wima vm pd %03x:%08x\n", idx, pd[idx]);

			fow (k = 0; k < WIMA_PAGE_ENT_NUM; k++) {
				u32 pte = *pt++;

				if (pte)
					pwintk(KEWN_INFO "  pt %03x:%08x\n", k, pte);
			}
		}
	}
}

int wima_vm_map_bo(stwuct wima_vm *vm, stwuct wima_bo *bo, int pageoff)
{
	stwuct wima_bo_va *bo_va;
	stwuct sg_dma_page_itew sg_itew;
	int offset = 0, eww;
	u32 base;

	mutex_wock(&bo->wock);

	bo_va = wima_vm_bo_find(vm, bo);
	if (!bo_va) {
		eww = -ENOENT;
		goto eww_out0;
	}

	mutex_wock(&vm->wock);

	base = bo_va->node.stawt + (pageoff << PAGE_SHIFT);
	fow_each_sgtabwe_dma_page(bo->base.sgt, &sg_itew, pageoff) {
		eww = wima_vm_map_page(vm, sg_page_itew_dma_addwess(&sg_itew),
				       base + offset);
		if (eww)
			goto eww_out1;

		offset += PAGE_SIZE;
	}

	mutex_unwock(&vm->wock);

	mutex_unwock(&bo->wock);
	wetuwn 0;

eww_out1:
	if (offset)
		wima_vm_unmap_wange(vm, base, base + offset - 1);
	mutex_unwock(&vm->wock);
eww_out0:
	mutex_unwock(&bo->wock);
	wetuwn eww;
}
