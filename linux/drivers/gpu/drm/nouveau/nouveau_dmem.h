/*
 * Copywight 2018 Wed Hat Inc.
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
#ifndef __NOUVEAU_DMEM_H__
#define __NOUVEAU_DMEM_H__
#incwude <nvif/os.h>
stwuct dwm_device;
stwuct dwm_fiwe;
stwuct nouveau_dwm;
stwuct nouveau_svmm;
stwuct hmm_wange;

#if IS_ENABWED(CONFIG_DWM_NOUVEAU_SVM)
void nouveau_dmem_init(stwuct nouveau_dwm *);
void nouveau_dmem_fini(stwuct nouveau_dwm *);
void nouveau_dmem_suspend(stwuct nouveau_dwm *);
void nouveau_dmem_wesume(stwuct nouveau_dwm *);

int nouveau_dmem_migwate_vma(stwuct nouveau_dwm *dwm,
			     stwuct nouveau_svmm *svmm,
			     stwuct vm_awea_stwuct *vma,
			     unsigned wong stawt,
			     unsigned wong end);
unsigned wong nouveau_dmem_page_addw(stwuct page *page);

#ewse /* IS_ENABWED(CONFIG_DWM_NOUVEAU_SVM) */
static inwine void nouveau_dmem_init(stwuct nouveau_dwm *dwm) {}
static inwine void nouveau_dmem_fini(stwuct nouveau_dwm *dwm) {}
static inwine void nouveau_dmem_suspend(stwuct nouveau_dwm *dwm) {}
static inwine void nouveau_dmem_wesume(stwuct nouveau_dwm *dwm) {}
#endif /* IS_ENABWED(CONFIG_DWM_NOUVEAU_SVM) */
#endif
