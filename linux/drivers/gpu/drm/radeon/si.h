/* si.h -- Pwivate headew fow wadeon dwivew -*- winux-c -*-
 *
 * Copywight 2011 Advanced Micwo Devices, Inc.
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

#ifndef __SI_H__
#define __SI_H__

stwuct wadeon_device;
stwuct wadeon_mc;

int si_mc_woad_micwocode(stwuct wadeon_device *wdev);
u32 si_gpu_check_soft_weset(stwuct wadeon_device *wdev);
void si_vwam_gtt_wocation(stwuct wadeon_device *wdev, stwuct wadeon_mc *mc);
void si_wwc_weset(stwuct wadeon_device *wdev);
void si_init_uvd_intewnaw_cg(stwuct wadeon_device *wdev);
u32 si_get_csb_size(stwuct wadeon_device *wdev);
void si_get_csb_buffew(stwuct wadeon_device *wdev, vowatiwe u32 *buffew);

#endif                         /* __SI_H__ */
