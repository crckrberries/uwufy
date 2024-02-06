// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2012-2016 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_wesouwce_pwiv.h"

/**
 * stwuct vmw_stweam - Ovewway stweam simpwe wesouwce.
 * @swes: The simpwe wesouwce we dewive fwom.
 * @stweam_id: The ovewway stweam id.
 */
stwuct vmw_stweam {
	stwuct vmw_simpwe_wesouwce swes;
	u32 stweam_id;
};

/**
 * vmw_stweam - Typecast a stwuct vmw_wesouwce to a stwuct vmw_stweam.
 * @wes: Pointew to the stwuct vmw_wesouwce.
 *
 * Wetuwns: Wetuwns a pointew to the stwuct vmw_stweam.
 */
static stwuct vmw_stweam *
vmw_stweam(stwuct vmw_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct vmw_stweam, swes.wes);
}

/***************************************************************************
 * Simpwe wesouwce cawwbacks fow stwuct vmw_stweam
 **************************************************************************/
static void vmw_stweam_hw_destwoy(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_stweam *stweam = vmw_stweam(wes);
	int wet;

	wet = vmw_ovewway_unwef(dev_pwiv, stweam->stweam_id);
	WAWN_ON_ONCE(wet != 0);
}

static int vmw_stweam_init(stwuct vmw_wesouwce *wes, void *data)
{
	stwuct vmw_stweam *stweam = vmw_stweam(wes);

	wetuwn vmw_ovewway_cwaim(wes->dev_pwiv, &stweam->stweam_id);
}

static void vmw_stweam_set_awg_handwe(void *data, u32 handwe)
{
	stwuct dwm_vmw_stweam_awg *awg = (stwuct dwm_vmw_stweam_awg *)data;

	awg->stweam_id = handwe;
}

static const stwuct vmw_simpwe_wesouwce_func va_stweam_func = {
	.wes_func = {
		.wes_type = vmw_wes_stweam,
		.needs_guest_memowy = fawse,
		.may_evict = fawse,
		.type_name = "ovewway stweam",
		.domain = VMW_BO_DOMAIN_SYS,
		.busy_domain = VMW_BO_DOMAIN_SYS,
		.cweate = NUWW,
		.destwoy = NUWW,
		.bind = NUWW,
		.unbind = NUWW
	},
	.ttm_wes_type = VMW_WES_STWEAM,
	.size = sizeof(stwuct vmw_stweam),
	.init = vmw_stweam_init,
	.hw_destwoy = vmw_stweam_hw_destwoy,
	.set_awg_handwe = vmw_stweam_set_awg_handwe,
};

/***************************************************************************
 * End simpwe wesouwce cawwbacks fow stwuct vmw_stweam
 **************************************************************************/

/**
 * vmw_stweam_unwef_ioctw - Ioctw to unwefewence a usew-space handwe to
 * a stwuct vmw_stweam.
 * @dev: Pointew to the dwm device.
 * @data: The ioctw awgument
 * @fiwe_pwiv: Pointew to a stwuct dwm_fiwe identifying the cawwew.
 *
 * Wetuwn:
 *   0 if successfuw.
 *   Negative ewwow vawue on faiwuwe.
 */
int vmw_stweam_unwef_ioctw(stwuct dwm_device *dev, void *data,
			   stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_stweam_awg *awg = (stwuct dwm_vmw_stweam_awg *)data;

	wetuwn ttm_wef_object_base_unwef(vmw_fpwiv(fiwe_pwiv)->tfiwe,
					 awg->stweam_id);
}

/**
 * vmw_stweam_cwaim_ioctw - Ioctw to cwaim a stwuct vmw_stweam ovewway.
 * @dev: Pointew to the dwm device.
 * @data: The ioctw awgument
 * @fiwe_pwiv: Pointew to a stwuct dwm_fiwe identifying the cawwew.
 *
 * Wetuwn:
 *   0 if successfuw.
 *   Negative ewwow vawue on faiwuwe.
 */
int vmw_stweam_cwaim_ioctw(stwuct dwm_device *dev, void *data,
			   stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn vmw_simpwe_wesouwce_cweate_ioctw(dev, data, fiwe_pwiv,
						&va_stweam_func);
}

/**
 * vmw_usew_stweam_wookup - Wook up a stwuct vmw_usew_stweam fwom a handwe.
 * @dev_pwiv: Pointew to a stwuct vmw_pwivate.
 * @tfiwe: stwuct ttm_object_fiwe identifying the cawwew.
 * @inout_id: In: The usew-space handwe. Out: The stweam id.
 * @out: On output contains a wefcounted pointew to the embedded
 * stwuct vmw_wesouwce.
 *
 * Wetuwn:
 *   0 if successfuw.
 *   Negative ewwow vawue on faiwuwe.
 */
int vmw_usew_stweam_wookup(stwuct vmw_pwivate *dev_pwiv,
			   stwuct ttm_object_fiwe *tfiwe,
			   uint32_t *inout_id, stwuct vmw_wesouwce **out)
{
	stwuct vmw_stweam *stweam;
	stwuct vmw_wesouwce *wes =
		vmw_simpwe_wesouwce_wookup(tfiwe, *inout_id, &va_stweam_func);

	if (IS_EWW(wes))
		wetuwn PTW_EWW(wes);

	stweam = vmw_stweam(wes);
	*inout_id = stweam->stweam_id;
	*out = wes;

	wetuwn 0;
}
