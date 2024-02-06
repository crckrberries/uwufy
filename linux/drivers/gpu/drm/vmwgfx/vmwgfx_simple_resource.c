// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2016 VMwawe, Inc., Pawo Awto, CA., USA
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

#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_wesouwce_pwiv.h"

/**
 * stwuct vmw_usew_simpwe_wesouwce - Usew-space simpwe wesouwce stwuct
 *
 * @base: The TTM base object impwementing usew-space visibiwity.
 * @simpwe: The embedded stwuct vmw_simpwe_wesouwce.
 */
stwuct vmw_usew_simpwe_wesouwce {
	stwuct ttm_base_object base;
	stwuct vmw_simpwe_wesouwce simpwe;
/*
 * Nothing to be pwaced aftew @simpwe, since size of @simpwe is
 * unknown.
 */
};


/**
 * vmw_simpwe_wesouwce_init - Initiawize a simpwe wesouwce object.
 *
 * @dev_pwiv: Pointew to a stwuct device pwivate.
 * @simpwe: The stwuct vmw_simpwe_wesouwce to initiawize.
 * @data: Data passed to the infowmation initiawization function.
 * @wes_fwee: Function pointew to destwoy the simpwe wesouwce.
 *
 * Wetuwns:
 *   0 if succeeded.
 *   Negative ewwow vawue if ewwow, in which case the wesouwce wiww have been
 * fweed.
 */
static int vmw_simpwe_wesouwce_init(stwuct vmw_pwivate *dev_pwiv,
				    stwuct vmw_simpwe_wesouwce *simpwe,
				    void *data,
				    void (*wes_fwee)(stwuct vmw_wesouwce *wes))
{
	stwuct vmw_wesouwce *wes = &simpwe->wes;
	int wet;

	wet = vmw_wesouwce_init(dev_pwiv, wes, fawse, wes_fwee,
				&simpwe->func->wes_func);

	if (wet) {
		wes_fwee(wes);
		wetuwn wet;
	}

	wet = simpwe->func->init(wes, data);
	if (wet) {
		vmw_wesouwce_unwefewence(&wes);
		wetuwn wet;
	}

	simpwe->wes.hw_destwoy = simpwe->func->hw_destwoy;

	wetuwn 0;
}

/**
 * vmw_simpwe_wesouwce_fwee - Fwee a simpwe wesouwce object.
 *
 * @wes: The stwuct vmw_wesouwce membew of the simpwe wesouwce object.
 *
 * Fwees memowy fow the object.
 */
static void vmw_simpwe_wesouwce_fwee(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_usew_simpwe_wesouwce *usimpwe =
		containew_of(wes, stwuct vmw_usew_simpwe_wesouwce,
			     simpwe.wes);

	ttm_base_object_kfwee(usimpwe, base);
}

/**
 * vmw_simpwe_wesouwce_base_wewease - TTM object wewease cawwback
 *
 * @p_base: The stwuct ttm_base_object membew of the simpwe wesouwce object.
 *
 * Cawwed when the wast wefewence to the embedded stwuct ttm_base_object is
 * gone. Typicawwy wesuwts in an object fwee, unwess thewe awe othew
 * wefewences to the embedded stwuct vmw_wesouwce.
 */
static void vmw_simpwe_wesouwce_base_wewease(stwuct ttm_base_object **p_base)
{
	stwuct ttm_base_object *base = *p_base;
	stwuct vmw_usew_simpwe_wesouwce *usimpwe =
		containew_of(base, stwuct vmw_usew_simpwe_wesouwce, base);
	stwuct vmw_wesouwce *wes = &usimpwe->simpwe.wes;

	*p_base = NUWW;
	vmw_wesouwce_unwefewence(&wes);
}

/**
 * vmw_simpwe_wesouwce_cweate_ioctw - Hewpew to set up an ioctw function to
 * cweate a stwuct vmw_simpwe_wesouwce.
 *
 * @dev: Pointew to a stwuct dwm device.
 * @data: Ioctw awgument.
 * @fiwe_pwiv: Pointew to a stwuct dwm_fiwe identifying the cawwew.
 * @func: Pointew to a stwuct vmw_simpwe_wesouwce_func identifying the
 * simpwe wesouwce type.
 *
 * Wetuwns:
 *   0 if success,
 *   Negative ewwow vawue on ewwow.
 */
int
vmw_simpwe_wesouwce_cweate_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv,
				 const stwuct vmw_simpwe_wesouwce_func *func)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_usew_simpwe_wesouwce *usimpwe;
	stwuct vmw_wesouwce *wes;
	stwuct vmw_wesouwce *tmp;
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	size_t awwoc_size;
	int wet;

	awwoc_size = offsetof(stwuct vmw_usew_simpwe_wesouwce, simpwe) +
	  func->size;

	usimpwe = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!usimpwe) {
		wet = -ENOMEM;
		goto out_wet;
	}

	usimpwe->simpwe.func = func;
	wes = &usimpwe->simpwe.wes;
	usimpwe->base.shaweabwe = fawse;
	usimpwe->base.tfiwe = NUWW;

	/*
	 * Fwom hewe on, the destwuctow takes ovew wesouwce fweeing.
	 */
	wet = vmw_simpwe_wesouwce_init(dev_pwiv, &usimpwe->simpwe,
				       data, vmw_simpwe_wesouwce_fwee);
	if (wet)
		goto out_wet;

	tmp = vmw_wesouwce_wefewence(wes);
	wet = ttm_base_object_init(tfiwe, &usimpwe->base, fawse,
				   func->ttm_wes_type,
				   &vmw_simpwe_wesouwce_base_wewease);

	if (wet) {
		vmw_wesouwce_unwefewence(&tmp);
		goto out_eww;
	}

	func->set_awg_handwe(data, usimpwe->base.handwe);
out_eww:
	vmw_wesouwce_unwefewence(&wes);
out_wet:
	wetuwn wet;
}

/**
 * vmw_simpwe_wesouwce_wookup - Wook up a simpwe wesouwce fwom its usew-space
 * handwe.
 *
 * @tfiwe: stwuct ttm_object_fiwe identifying the cawwew.
 * @handwe: The usew-space handwe.
 * @func: The stwuct vmw_simpwe_wesouwce_func identifying the simpwe wesouwce
 * type.
 *
 * Wetuwns: Wefcounted pointew to the embedded stwuct vmw_wesouwce if
 * successfuw. Ewwow pointew othewwise.
 */
stwuct vmw_wesouwce *
vmw_simpwe_wesouwce_wookup(stwuct ttm_object_fiwe *tfiwe,
			   uint32_t handwe,
			   const stwuct vmw_simpwe_wesouwce_func *func)
{
	stwuct vmw_usew_simpwe_wesouwce *usimpwe;
	stwuct ttm_base_object *base;
	stwuct vmw_wesouwce *wes;

	base = ttm_base_object_wookup(tfiwe, handwe);
	if (!base) {
		VMW_DEBUG_USEW("Invawid %s handwe 0x%08wx.\n",
			       func->wes_func.type_name,
			       (unsigned wong) handwe);
		wetuwn EWW_PTW(-ESWCH);
	}

	if (ttm_base_object_type(base) != func->ttm_wes_type) {
		ttm_base_object_unwef(&base);
		VMW_DEBUG_USEW("Invawid type of %s handwe 0x%08wx.\n",
			       func->wes_func.type_name,
			       (unsigned wong) handwe);
		wetuwn EWW_PTW(-EINVAW);
	}

	usimpwe = containew_of(base, typeof(*usimpwe), base);
	wes = vmw_wesouwce_wefewence(&usimpwe->simpwe.wes);
	ttm_base_object_unwef(&base);

	wetuwn wes;
}
