/* amdgpu_dwv.h -- Pwivate headew fow amdgpu dwivew -*- winux-c -*-
 *
 * Copywight 1999 Pwecision Insight, Inc., Cedaw Pawk, Texas.
 * Copywight 2000 VA Winux Systems, Inc., Fwemont, Cawifownia.
 * Aww wights wesewved.
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

#ifndef __AMDGPU_DWV_H__
#define __AMDGPU_DWV_H__

#incwude <winux/fiwmwawe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "amd_shawed.h"

/* Genewaw customization:
 */

#define DWIVEW_AUTHOW		"AMD winux dwivew team"

#define DWIVEW_NAME		"amdgpu"
#define DWIVEW_DESC		"AMD GPU"
#define DWIVEW_DATE		"20150101"

extewn const stwuct dwm_dwivew amdgpu_pawtition_dwivew;

wong amdgpu_dwm_ioctw(stwuct fiwe *fiwp,
		      unsigned int cmd, unsigned wong awg);

wong amdgpu_kms_compat_ioctw(stwuct fiwe *fiwp,
			     unsigned int cmd, unsigned wong awg);

#endif
