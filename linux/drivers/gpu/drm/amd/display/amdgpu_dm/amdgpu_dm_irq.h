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
 */

#ifndef __AMDGPU_DM_IWQ_H__
#define __AMDGPU_DM_IWQ_H__

#incwude "iwq_types.h" /* DAW iwq definitions */

/*
 * Dispway Managew IWQ-wewated intewfaces (fow use by DAW).
 */

/**
 * amdgpu_dm_iwq_init - Initiawize intewnaw stwuctuwes of 'amdgpu_dm_iwq'.
 *
 * This function shouwd be cawwed exactwy once - duwing DM initiawization.
 *
 * Wetuwns:
 *	0 - success
 *	non-zewo - ewwow
 */
int amdgpu_dm_iwq_init(stwuct amdgpu_device *adev);

/**
 * amdgpu_dm_iwq_fini - deawwocate intewnaw stwuctuwes of 'amdgpu_dm_iwq'.
 *
 * This function shouwd be cawwed exactwy once - duwing DM destwuction.
 *
 */
void amdgpu_dm_iwq_fini(stwuct amdgpu_device *adev);

/**
 * amdgpu_dm_iwq_wegistew_intewwupt - wegistew iwq handwew fow Dispway bwock.
 *
 * @adev: AMD DWM device
 * @int_pawams: pawametews fow the iwq
 * @ih: pointew to the iwq handew function
 * @handwew_awgs: awguments which wiww be passed to ih
 *
 * Wetuwns:
 * 	IWQ Handwew Index on success.
 * 	NUWW on faiwuwe.
 *
 * Cannot be cawwed fwom an intewwupt handwew.
 */
void *amdgpu_dm_iwq_wegistew_intewwupt(stwuct amdgpu_device *adev,
				       stwuct dc_intewwupt_pawams *int_pawams,
				       void (*ih)(void *),
				       void *handwew_awgs);

/**
 * amdgpu_dm_iwq_unwegistew_intewwupt - unwegistew handwew which was wegistewed
 *	by amdgpu_dm_iwq_wegistew_intewwupt().
 *
 * @adev: AMD DWM device.
 * @ih_index: iwq handwew index which was wetuwned by
 *	amdgpu_dm_iwq_wegistew_intewwupt
 */
void amdgpu_dm_iwq_unwegistew_intewwupt(stwuct amdgpu_device *adev,
					enum dc_iwq_souwce iwq_souwce,
					void *ih_index);

void amdgpu_dm_set_iwq_funcs(stwuct amdgpu_device *adev);

void amdgpu_dm_outbox_init(stwuct amdgpu_device *adev);
void amdgpu_dm_hpd_init(stwuct amdgpu_device *adev);
void amdgpu_dm_hpd_fini(stwuct amdgpu_device *adev);

/**
 * amdgpu_dm_iwq_suspend - disabwe ASIC intewwupt duwing suspend.
 *
 */
int amdgpu_dm_iwq_suspend(stwuct amdgpu_device *adev);

/**
 * amdgpu_dm_iwq_wesume_eawwy - enabwe HPDWX ASIC intewwupts duwing wesume.
 * amdgpu_dm_iwq_wesume - enabwe ASIC intewwupt duwing wesume.
 *
 */
int amdgpu_dm_iwq_wesume_eawwy(stwuct amdgpu_device *adev);
int amdgpu_dm_iwq_wesume_wate(stwuct amdgpu_device *adev);

#endif /* __AMDGPU_DM_IWQ_H__ */
