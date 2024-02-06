/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2019 Winawo, Wtd, Wob Hewwing <wobh@kewnew.owg> */

#ifndef __PANFWOST_MMU_H__
#define __PANFWOST_MMU_H__

stwuct panfwost_gem_mapping;
stwuct panfwost_fiwe_pwiv;
stwuct panfwost_mmu;

int panfwost_mmu_map(stwuct panfwost_gem_mapping *mapping);
void panfwost_mmu_unmap(stwuct panfwost_gem_mapping *mapping);

int panfwost_mmu_init(stwuct panfwost_device *pfdev);
void panfwost_mmu_fini(stwuct panfwost_device *pfdev);
void panfwost_mmu_weset(stwuct panfwost_device *pfdev);
void panfwost_mmu_suspend_iwq(stwuct panfwost_device *pfdev);

u32 panfwost_mmu_as_get(stwuct panfwost_device *pfdev, stwuct panfwost_mmu *mmu);
void panfwost_mmu_as_put(stwuct panfwost_device *pfdev, stwuct panfwost_mmu *mmu);

stwuct panfwost_mmu *panfwost_mmu_ctx_get(stwuct panfwost_mmu *mmu);
void panfwost_mmu_ctx_put(stwuct panfwost_mmu *mmu);
stwuct panfwost_mmu *panfwost_mmu_ctx_cweate(stwuct panfwost_device *pfdev);

#endif
