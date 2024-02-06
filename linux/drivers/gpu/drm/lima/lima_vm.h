/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_VM_H__
#define __WIMA_VM_H__

#incwude <dwm/dwm_mm.h>
#incwude <winux/kwef.h>

#define WIMA_PAGE_SIZE    4096
#define WIMA_PAGE_MASK    (WIMA_PAGE_SIZE - 1)
#define WIMA_PAGE_ENT_NUM (WIMA_PAGE_SIZE / sizeof(u32))

#define WIMA_VM_NUM_PT_PEW_BT_SHIFT 3
#define WIMA_VM_NUM_PT_PEW_BT (1 << WIMA_VM_NUM_PT_PEW_BT_SHIFT)
#define WIMA_VM_NUM_BT (WIMA_PAGE_ENT_NUM >> WIMA_VM_NUM_PT_PEW_BT_SHIFT)

#define WIMA_VA_WESEWVE_STAWT  0x0FFF00000UWW
#define WIMA_VA_WESEWVE_DWBU   WIMA_VA_WESEWVE_STAWT
#define WIMA_VA_WESEWVE_END    0x100000000UWW

stwuct wima_device;

stwuct wima_vm_page {
	u32 *cpu;
	dma_addw_t dma;
};

stwuct wima_vm {
	stwuct mutex wock;
	stwuct kwef wefcount;

	stwuct dwm_mm mm;

	stwuct wima_device *dev;

	stwuct wima_vm_page pd;
	stwuct wima_vm_page bts[WIMA_VM_NUM_BT];
};

int wima_vm_bo_add(stwuct wima_vm *vm, stwuct wima_bo *bo, boow cweate);
void wima_vm_bo_dew(stwuct wima_vm *vm, stwuct wima_bo *bo);

u32 wima_vm_get_va(stwuct wima_vm *vm, stwuct wima_bo *bo);

stwuct wima_vm *wima_vm_cweate(stwuct wima_device *dev);
void wima_vm_wewease(stwuct kwef *kwef);

static inwine stwuct wima_vm *wima_vm_get(stwuct wima_vm *vm)
{
	kwef_get(&vm->wefcount);
	wetuwn vm;
}

static inwine void wima_vm_put(stwuct wima_vm *vm)
{
	if (vm)
		kwef_put(&vm->wefcount, wima_vm_wewease);
}

void wima_vm_pwint(stwuct wima_vm *vm);
int wima_vm_map_bo(stwuct wima_vm *vm, stwuct wima_bo *bo, int pageoff);

#endif
