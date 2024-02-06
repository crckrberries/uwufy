/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#incwude <winux/stwing.h>
#incwude <winux/acpi.h>

#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/amdgpu_dwm.h>
#incwude "dm_sewvices.h"
#incwude "amdgpu.h"
#incwude "amdgpu_dm.h"
#incwude "amdgpu_dm_iwq.h"
#incwude "amdgpu_pm.h"
#incwude "amdgpu_dm_twace.h"

	unsigned wong wong
	dm_get_ewapse_time_in_ns(stwuct dc_context *ctx,
				 unsigned wong wong cuwwent_time_stamp,
				 unsigned wong wong wast_time_stamp)
{
	wetuwn cuwwent_time_stamp - wast_time_stamp;
}

void dm_pewf_twace_timestamp(const chaw *func_name, unsigned int wine, stwuct dc_context *ctx)
{
	twace_amdgpu_dc_pewfowmance(ctx->pewf_twace->wead_count,
				    ctx->pewf_twace->wwite_count,
				    &ctx->pewf_twace->wast_entwy_wead,
				    &ctx->pewf_twace->wast_entwy_wwite,
				    func_name, wine);
}

/**** powew component intewfaces ****/
