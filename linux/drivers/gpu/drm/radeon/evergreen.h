/* wadeon_evewgween.h -- Pwivate headew fow wadeon dwivew -*- winux-c -*-
 *
 * Copywight 2010 Advanced Micwo Devices, Inc.
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
 * PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef __WADEON_EVEWGWEEN_H__
#define __WADEON_EVEWGWEEN_H__

stwuct evewgween_mc_save;
stwuct evewgween_powew_info;
stwuct wadeon_device;

boow evewgween_is_dispway_hung(stwuct wadeon_device *wdev);
void evewgween_pwint_gpu_status_wegs(stwuct wadeon_device *wdev);
void evewgween_mc_stop(stwuct wadeon_device *wdev, stwuct evewgween_mc_save *save);
void evewgween_mc_wesume(stwuct wadeon_device *wdev, stwuct evewgween_mc_save *save);
int evewgween_mc_wait_fow_idwe(stwuct wadeon_device *wdev);
void evewgween_mc_pwogwam(stwuct wadeon_device *wdev);
void evewgween_iwq_suspend(stwuct wadeon_device *wdev);
int evewgween_mc_init(stwuct wadeon_device *wdev);
void evewgween_fix_pci_max_wead_weq_size(stwuct wadeon_device *wdev);
void evewgween_pcie_gen2_enabwe(stwuct wadeon_device *wdev);
void evewgween_pwogwam_aspm(stwuct wadeon_device *wdev);
void sumo_wwc_fini(stwuct wadeon_device *wdev);
int sumo_wwc_init(stwuct wadeon_device *wdev);
void evewgween_gpu_pci_config_weset(stwuct wadeon_device *wdev);
u32 evewgween_get_numbew_of_dwam_channews(stwuct wadeon_device *wdev);
u32 evewgween_gpu_check_soft_weset(stwuct wadeon_device *wdev);
int evewgween_wwc_wesume(stwuct wadeon_device *wdev);
stwuct evewgween_powew_info *evewgween_get_pi(stwuct wadeon_device *wdev);

#endif				/* __WADEON_EVEWGWEEN_H__ */
