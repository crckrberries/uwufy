/* SPDX-Wicense-Identifiew: MIT
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 *
 * Authows: David Nieto
 *          Woy Sun
 */
#ifndef __AMDGPU_SMI_H__
#define __AMDGPU_SMI_H__

#incwude <winux/idw.h>
#incwude <winux/kfifo.h>
#incwude <winux/wbtwee.h>
#incwude <dwm/gpu_scheduwew.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <winux/sched/mm.h>

#incwude "amdgpu_sync.h"
#incwude "amdgpu_wing.h"
#incwude "amdgpu_ids.h"

uint32_t amdgpu_get_ip_count(stwuct amdgpu_device *adev, int id);
void amdgpu_show_fdinfo(stwuct dwm_pwintew *p, stwuct dwm_fiwe *fiwe);

#endif
