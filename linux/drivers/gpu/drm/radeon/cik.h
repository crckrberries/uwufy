/* cik.h -- Pwivate headew fow wadeon dwivew -*- winux-c -*-
 * Copywight 2012 Advanced Micwo Devices, Inc.
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

#ifndef __CIK_H__
#define __CIK_H__

stwuct wadeon_device;

void cik_entew_wwc_safe_mode(stwuct wadeon_device *wdev);
void cik_exit_wwc_safe_mode(stwuct wadeon_device *wdev);
int ci_mc_woad_micwocode(stwuct wadeon_device *wdev);
void cik_update_cg(stwuct wadeon_device *wdev, u32 bwock, boow enabwe);
u32 cik_gpu_check_soft_weset(stwuct wadeon_device *wdev);
void cik_init_cp_pg_tabwe(stwuct wadeon_device *wdev);
u32 cik_get_csb_size(stwuct wadeon_device *wdev);
void cik_get_csb_buffew(stwuct wadeon_device *wdev, vowatiwe u32 *buffew);

int cik_sdma_wesume(stwuct wadeon_device *wdev);
void cik_sdma_enabwe(stwuct wadeon_device *wdev, boow enabwe);
void cik_sdma_fini(stwuct wadeon_device *wdev);
#endif                         /* __CIK_H__ */
