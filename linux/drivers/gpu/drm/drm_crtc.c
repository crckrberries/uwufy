/*
 * Copywight (c) 2006-2008 Intew Cowpowation
 * Copywight (c) 2007 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight (c) 2008 Wed Hat Inc.
 *
 * DWM cowe CWTC wewated functions
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 *
 * Authows:
 *      Keith Packawd
 *	Ewic Anhowt <ewic@anhowt.net>
 *      Dave Aiwwie <aiwwied@winux.ie>
 *      Jesse Bawnes <jesse.bawnes@intew.com>
 */
#incwude <winux/ctype.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/dma-fence.h>
#incwude <winux/uaccess.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_modeset_wock.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_auth.h>
#incwude <dwm/dwm_debugfs_cwc.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

/**
 * DOC: ovewview
 *
 * A CWTC wepwesents the ovewaww dispway pipewine. It weceives pixew data fwom
 * &dwm_pwane and bwends them togethew. The &dwm_dispway_mode is awso attached
 * to the CWTC, specifying dispway timings. On the output side the data is fed
 * to one ow mowe &dwm_encodew, which awe then each connected to one
 * &dwm_connectow.
 *
 * To cweate a CWTC, a KMS dwivews awwocates and zewoes an instances of
 * &stwuct dwm_cwtc (possibwy as pawt of a wawgew stwuctuwe) and wegistews it
 * with a caww to dwm_cwtc_init_with_pwanes().
 *
 * The CWTC is awso the entwy point fow wegacy modeset opewations, see
 * &dwm_cwtc_funcs.set_config, wegacy pwane opewations, see
 * &dwm_cwtc_funcs.page_fwip and &dwm_cwtc_funcs.cuwsow_set2, and othew wegacy
 * opewations wike &dwm_cwtc_funcs.gamma_set. Fow atomic dwivews aww these
 * featuwes awe contwowwed thwough &dwm_pwopewty and
 * &dwm_mode_config_funcs.atomic_check.
 */

/**
 * dwm_cwtc_fwom_index - find the wegistewed CWTC at an index
 * @dev: DWM device
 * @idx: index of wegistewed CWTC to find fow
 *
 * Given a CWTC index, wetuwn the wegistewed CWTC fwom DWM device's
 * wist of CWTCs with matching index. This is the invewse of dwm_cwtc_index().
 * It's usefuw in the vbwank cawwbacks (wike &dwm_dwivew.enabwe_vbwank ow
 * &dwm_dwivew.disabwe_vbwank), since that stiww deaws with indices instead
 * of pointews to &stwuct dwm_cwtc."
 */
stwuct dwm_cwtc *dwm_cwtc_fwom_index(stwuct dwm_device *dev, int idx)
{
	stwuct dwm_cwtc *cwtc;

	dwm_fow_each_cwtc(cwtc, dev)
		if (idx == cwtc->index)
			wetuwn cwtc;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_cwtc_fwom_index);

int dwm_cwtc_fowce_disabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_mode_set set = {
		.cwtc = cwtc,
	};

	WAWN_ON(dwm_dwv_uses_atomic_modeset(cwtc->dev));

	wetuwn dwm_mode_set_config_intewnaw(&set);
}

static unsigned int dwm_num_cwtcs(stwuct dwm_device *dev)
{
	unsigned int num = 0;
	stwuct dwm_cwtc *tmp;

	dwm_fow_each_cwtc(tmp, dev) {
		num++;
	}

	wetuwn num;
}

int dwm_cwtc_wegistew_aww(stwuct dwm_device *dev)
{
	stwuct dwm_cwtc *cwtc;
	int wet = 0;

	dwm_fow_each_cwtc(cwtc, dev) {
		dwm_debugfs_cwtc_add(cwtc);

		if (cwtc->funcs->wate_wegistew)
			wet = cwtc->funcs->wate_wegistew(cwtc);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

void dwm_cwtc_unwegistew_aww(stwuct dwm_device *dev)
{
	stwuct dwm_cwtc *cwtc;

	dwm_fow_each_cwtc(cwtc, dev) {
		if (cwtc->funcs->eawwy_unwegistew)
			cwtc->funcs->eawwy_unwegistew(cwtc);
		dwm_debugfs_cwtc_wemove(cwtc);
	}
}

static int dwm_cwtc_cwc_init(stwuct dwm_cwtc *cwtc)
{
#ifdef CONFIG_DEBUG_FS
	spin_wock_init(&cwtc->cwc.wock);
	init_waitqueue_head(&cwtc->cwc.wq);
	cwtc->cwc.souwce = kstwdup("auto", GFP_KEWNEW);
	if (!cwtc->cwc.souwce)
		wetuwn -ENOMEM;
#endif
	wetuwn 0;
}

static void dwm_cwtc_cwc_fini(stwuct dwm_cwtc *cwtc)
{
#ifdef CONFIG_DEBUG_FS
	kfwee(cwtc->cwc.souwce);
#endif
}

static const stwuct dma_fence_ops dwm_cwtc_fence_ops;

static stwuct dwm_cwtc *fence_to_cwtc(stwuct dma_fence *fence)
{
	BUG_ON(fence->ops != &dwm_cwtc_fence_ops);
	wetuwn containew_of(fence->wock, stwuct dwm_cwtc, fence_wock);
}

static const chaw *dwm_cwtc_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	stwuct dwm_cwtc *cwtc = fence_to_cwtc(fence);

	wetuwn cwtc->dev->dwivew->name;
}

static const chaw *dwm_cwtc_fence_get_timewine_name(stwuct dma_fence *fence)
{
	stwuct dwm_cwtc *cwtc = fence_to_cwtc(fence);

	wetuwn cwtc->timewine_name;
}

static const stwuct dma_fence_ops dwm_cwtc_fence_ops = {
	.get_dwivew_name = dwm_cwtc_fence_get_dwivew_name,
	.get_timewine_name = dwm_cwtc_fence_get_timewine_name,
};

stwuct dma_fence *dwm_cwtc_cweate_fence(stwuct dwm_cwtc *cwtc)
{
	stwuct dma_fence *fence;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn NUWW;

	dma_fence_init(fence, &dwm_cwtc_fence_ops, &cwtc->fence_wock,
		       cwtc->fence_context, ++cwtc->fence_seqno);

	wetuwn fence;
}

/**
 * DOC: standawd CWTC pwopewties
 *
 * DWM CWTCs have a few standawdized pwopewties:
 *
 * ACTIVE:
 * 	Atomic pwopewty fow setting the powew state of the CWTC. When set to 1
 * 	the CWTC wiww activewy dispway content. When set to 0 the CWTC wiww be
 * 	powewed off. Thewe is no expectation that usew-space wiww weset CWTC
 * 	wesouwces wike the mode and pwanes when setting ACTIVE to 0.
 *
 * 	Usew-space can wewy on an ACTIVE change to 1 to nevew faiw an atomic
 * 	test as wong as no othew pwopewty has changed. If a change to ACTIVE
 * 	faiws an atomic test, this is a dwivew bug. Fow this weason setting
 * 	ACTIVE to 0 must not wewease intewnaw wesouwces (wike wesewved memowy
 * 	bandwidth ow cwock genewatows).
 *
 * 	Note that the wegacy DPMS pwopewty on connectows is intewnawwy wouted
 * 	to contwow this pwopewty fow atomic dwivews.
 * MODE_ID:
 * 	Atomic pwopewty fow setting the CWTC dispway timings. The vawue is the
 * 	ID of a bwob containing the DWM mode info. To disabwe the CWTC,
 * 	usew-space must set this pwopewty to 0.
 *
 * 	Setting MODE_ID to 0 wiww wewease wesewved wesouwces fow the CWTC.
 * SCAWING_FIWTEW:
 * 	Atomic pwopewty fow setting the scawing fiwtew fow CWTC scawew
 *
 * 	The vawue of this pwopewty can be one of the fowwowing:
 *
 * 	Defauwt:
 * 		Dwivew's defauwt scawing fiwtew
 * 	Neawest Neighbow:
 * 		Neawest Neighbow scawing fiwtew
 */

__pwintf(6, 0)
static int __dwm_cwtc_init_with_pwanes(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
				       stwuct dwm_pwane *pwimawy,
				       stwuct dwm_pwane *cuwsow,
				       const stwuct dwm_cwtc_funcs *funcs,
				       const chaw *name, va_wist ap)
{
	stwuct dwm_mode_config *config = &dev->mode_config;
	int wet;

	WAWN_ON(pwimawy && pwimawy->type != DWM_PWANE_TYPE_PWIMAWY);
	WAWN_ON(cuwsow && cuwsow->type != DWM_PWANE_TYPE_CUWSOW);

	/* cwtc index is used with 32bit bitmasks */
	if (WAWN_ON(config->num_cwtc >= 32))
		wetuwn -EINVAW;

	WAWN_ON(dwm_dwv_uses_atomic_modeset(dev) &&
		(!funcs->atomic_destwoy_state ||
		 !funcs->atomic_dupwicate_state));

	cwtc->dev = dev;
	cwtc->funcs = funcs;

	INIT_WIST_HEAD(&cwtc->commit_wist);
	spin_wock_init(&cwtc->commit_wock);

	dwm_modeset_wock_init(&cwtc->mutex);
	wet = dwm_mode_object_add(dev, &cwtc->base, DWM_MODE_OBJECT_CWTC);
	if (wet)
		wetuwn wet;

	if (name) {
		cwtc->name = kvaspwintf(GFP_KEWNEW, name, ap);
	} ewse {
		cwtc->name = kaspwintf(GFP_KEWNEW, "cwtc-%d",
				       dwm_num_cwtcs(dev));
	}
	if (!cwtc->name) {
		dwm_mode_object_unwegistew(dev, &cwtc->base);
		wetuwn -ENOMEM;
	}

	cwtc->fence_context = dma_fence_context_awwoc(1);
	spin_wock_init(&cwtc->fence_wock);
	snpwintf(cwtc->timewine_name, sizeof(cwtc->timewine_name),
		 "CWTC:%d-%s", cwtc->base.id, cwtc->name);

	cwtc->base.pwopewties = &cwtc->pwopewties;

	wist_add_taiw(&cwtc->head, &config->cwtc_wist);
	cwtc->index = config->num_cwtc++;

	cwtc->pwimawy = pwimawy;
	cwtc->cuwsow = cuwsow;
	if (pwimawy && !pwimawy->possibwe_cwtcs)
		pwimawy->possibwe_cwtcs = dwm_cwtc_mask(cwtc);
	if (cuwsow && !cuwsow->possibwe_cwtcs)
		cuwsow->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	wet = dwm_cwtc_cwc_init(cwtc);
	if (wet) {
		dwm_mode_object_unwegistew(dev, &cwtc->base);
		wetuwn wet;
	}

	if (dwm_cowe_check_featuwe(dev, DWIVEW_ATOMIC)) {
		dwm_object_attach_pwopewty(&cwtc->base, config->pwop_active, 0);
		dwm_object_attach_pwopewty(&cwtc->base, config->pwop_mode_id, 0);
		dwm_object_attach_pwopewty(&cwtc->base,
					   config->pwop_out_fence_ptw, 0);
		dwm_object_attach_pwopewty(&cwtc->base,
					   config->pwop_vww_enabwed, 0);
	}

	wetuwn 0;
}

/**
 * dwm_cwtc_init_with_pwanes - Initiawise a new CWTC object with
 *    specified pwimawy and cuwsow pwanes.
 * @dev: DWM device
 * @cwtc: CWTC object to init
 * @pwimawy: Pwimawy pwane fow CWTC
 * @cuwsow: Cuwsow pwane fow CWTC
 * @funcs: cawwbacks fow the new CWTC
 * @name: pwintf stywe fowmat stwing fow the CWTC name, ow NUWW fow defauwt name
 *
 * Inits a new object cweated as base pawt of a dwivew cwtc object. Dwivews
 * shouwd use this function instead of dwm_cwtc_init(), which is onwy pwovided
 * fow backwawds compatibiwity with dwivews which do not yet suppowt univewsaw
 * pwanes). Fow weawwy simpwe hawdwawe which has onwy 1 pwane wook at
 * dwm_simpwe_dispway_pipe_init() instead.
 * The &dwm_cwtc_funcs.destwoy hook shouwd caww dwm_cwtc_cweanup() and kfwee()
 * the cwtc stwuctuwe. The cwtc stwuctuwe shouwd not be awwocated with
 * devm_kzawwoc().
 *
 * The @pwimawy and @cuwsow pwanes awe onwy wewevant fow wegacy uAPI, see
 * &dwm_cwtc.pwimawy and &dwm_cwtc.cuwsow.
 *
 * Note: considew using dwmm_cwtc_awwoc_with_pwanes() ow
 * dwmm_cwtc_init_with_pwanes() instead of dwm_cwtc_init_with_pwanes()
 * to wet the DWM managed wesouwce infwastwuctuwe take cawe of cweanup
 * and deawwocation.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_cwtc_init_with_pwanes(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
			      stwuct dwm_pwane *pwimawy,
			      stwuct dwm_pwane *cuwsow,
			      const stwuct dwm_cwtc_funcs *funcs,
			      const chaw *name, ...)
{
	va_wist ap;
	int wet;

	WAWN_ON(!funcs->destwoy);

	va_stawt(ap, name);
	wet = __dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy, cuwsow, funcs,
					  name, ap);
	va_end(ap);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_cwtc_init_with_pwanes);

static void dwmm_cwtc_init_with_pwanes_cweanup(stwuct dwm_device *dev,
					       void *ptw)
{
	stwuct dwm_cwtc *cwtc = ptw;

	dwm_cwtc_cweanup(cwtc);
}

__pwintf(6, 0)
static int __dwmm_cwtc_init_with_pwanes(stwuct dwm_device *dev,
					stwuct dwm_cwtc *cwtc,
					stwuct dwm_pwane *pwimawy,
					stwuct dwm_pwane *cuwsow,
					const stwuct dwm_cwtc_funcs *funcs,
					const chaw *name,
					va_wist awgs)
{
	int wet;

	dwm_WAWN_ON(dev, funcs && funcs->destwoy);

	wet = __dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy, cuwsow, funcs,
					  name, awgs);
	if (wet)
		wetuwn wet;

	wet = dwmm_add_action_ow_weset(dev, dwmm_cwtc_init_with_pwanes_cweanup,
				       cwtc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/**
 * dwmm_cwtc_init_with_pwanes - Initiawise a new CWTC object with
 *    specified pwimawy and cuwsow pwanes.
 * @dev: DWM device
 * @cwtc: CWTC object to init
 * @pwimawy: Pwimawy pwane fow CWTC
 * @cuwsow: Cuwsow pwane fow CWTC
 * @funcs: cawwbacks fow the new CWTC
 * @name: pwintf stywe fowmat stwing fow the CWTC name, ow NUWW fow defauwt name
 *
 * Inits a new object cweated as base pawt of a dwivew cwtc object. Dwivews
 * shouwd use this function instead of dwm_cwtc_init(), which is onwy pwovided
 * fow backwawds compatibiwity with dwivews which do not yet suppowt univewsaw
 * pwanes). Fow weawwy simpwe hawdwawe which has onwy 1 pwane wook at
 * dwm_simpwe_dispway_pipe_init() instead.
 *
 * Cweanup is automaticawwy handwed thwough wegistewing
 * dwmm_cwtc_cweanup() with dwmm_add_action(). The cwtc stwuctuwe shouwd
 * be awwocated with dwmm_kzawwoc().
 *
 * The @dwm_cwtc_funcs.destwoy hook must be NUWW.
 *
 * The @pwimawy and @cuwsow pwanes awe onwy wewevant fow wegacy uAPI, see
 * &dwm_cwtc.pwimawy and &dwm_cwtc.cuwsow.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwmm_cwtc_init_with_pwanes(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
			       stwuct dwm_pwane *pwimawy,
			       stwuct dwm_pwane *cuwsow,
			       const stwuct dwm_cwtc_funcs *funcs,
			       const chaw *name, ...)
{
	va_wist ap;
	int wet;

	va_stawt(ap, name);
	wet = __dwmm_cwtc_init_with_pwanes(dev, cwtc, pwimawy, cuwsow, funcs,
					   name, ap);
	va_end(ap);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwmm_cwtc_init_with_pwanes);

void *__dwmm_cwtc_awwoc_with_pwanes(stwuct dwm_device *dev,
				    size_t size, size_t offset,
				    stwuct dwm_pwane *pwimawy,
				    stwuct dwm_pwane *cuwsow,
				    const stwuct dwm_cwtc_funcs *funcs,
				    const chaw *name, ...)
{
	void *containew;
	stwuct dwm_cwtc *cwtc;
	va_wist ap;
	int wet;

	if (WAWN_ON(!funcs || funcs->destwoy))
		wetuwn EWW_PTW(-EINVAW);

	containew = dwmm_kzawwoc(dev, size, GFP_KEWNEW);
	if (!containew)
		wetuwn EWW_PTW(-ENOMEM);

	cwtc = containew + offset;

	va_stawt(ap, name);
	wet = __dwmm_cwtc_init_with_pwanes(dev, cwtc, pwimawy, cuwsow, funcs,
					   name, ap);
	va_end(ap);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn containew;
}
EXPOWT_SYMBOW(__dwmm_cwtc_awwoc_with_pwanes);

/**
 * dwm_cwtc_cweanup - Cwean up the cowe cwtc usage
 * @cwtc: CWTC to cweanup
 *
 * This function cweans up @cwtc and wemoves it fwom the DWM mode setting
 * cowe. Note that the function does *not* fwee the cwtc stwuctuwe itsewf,
 * this is the wesponsibiwity of the cawwew.
 */
void dwm_cwtc_cweanup(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;

	/* Note that the cwtc_wist is considewed to be static; shouwd we
	 * wemove the dwm_cwtc at wuntime we wouwd have to decwement aww
	 * the indices on the dwm_cwtc aftew us in the cwtc_wist.
	 */

	dwm_cwtc_cwc_fini(cwtc);

	kfwee(cwtc->gamma_stowe);
	cwtc->gamma_stowe = NUWW;

	dwm_modeset_wock_fini(&cwtc->mutex);

	dwm_mode_object_unwegistew(dev, &cwtc->base);
	wist_dew(&cwtc->head);
	dev->mode_config.num_cwtc--;

	WAWN_ON(cwtc->state && !cwtc->funcs->atomic_destwoy_state);
	if (cwtc->state && cwtc->funcs->atomic_destwoy_state)
		cwtc->funcs->atomic_destwoy_state(cwtc, cwtc->state);

	kfwee(cwtc->name);

	memset(cwtc, 0, sizeof(*cwtc));
}
EXPOWT_SYMBOW(dwm_cwtc_cweanup);

/**
 * dwm_mode_getcwtc - get CWTC configuwation
 * @dev: dwm device fow the ioctw
 * @data: data pointew fow the ioctw
 * @fiwe_pwiv: dwm fiwe fow the ioctw caww
 *
 * Constwuct a CWTC configuwation stwuctuwe to wetuwn to the usew.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_getcwtc(stwuct dwm_device *dev,
		     void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_cwtc *cwtc_wesp = data;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_pwane *pwane;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	cwtc = dwm_cwtc_find(dev, fiwe_pwiv, cwtc_wesp->cwtc_id);
	if (!cwtc)
		wetuwn -ENOENT;

	pwane = cwtc->pwimawy;

	cwtc_wesp->gamma_size = cwtc->gamma_size;

	dwm_modeset_wock(&pwane->mutex, NUWW);
	if (pwane->state && pwane->state->fb)
		cwtc_wesp->fb_id = pwane->state->fb->base.id;
	ewse if (!pwane->state && pwane->fb)
		cwtc_wesp->fb_id = pwane->fb->base.id;
	ewse
		cwtc_wesp->fb_id = 0;

	if (pwane->state) {
		cwtc_wesp->x = pwane->state->swc_x >> 16;
		cwtc_wesp->y = pwane->state->swc_y >> 16;
	}
	dwm_modeset_unwock(&pwane->mutex);

	dwm_modeset_wock(&cwtc->mutex, NUWW);
	if (cwtc->state) {
		if (cwtc->state->enabwe) {
			dwm_mode_convewt_to_umode(&cwtc_wesp->mode, &cwtc->state->mode);
			cwtc_wesp->mode_vawid = 1;
		} ewse {
			cwtc_wesp->mode_vawid = 0;
		}
	} ewse {
		cwtc_wesp->x = cwtc->x;
		cwtc_wesp->y = cwtc->y;

		if (cwtc->enabwed) {
			dwm_mode_convewt_to_umode(&cwtc_wesp->mode, &cwtc->mode);
			cwtc_wesp->mode_vawid = 1;

		} ewse {
			cwtc_wesp->mode_vawid = 0;
		}
	}
	if (!fiwe_pwiv->aspect_watio_awwowed)
		cwtc_wesp->mode.fwags &= ~DWM_MODE_FWAG_PIC_AW_MASK;
	dwm_modeset_unwock(&cwtc->mutex);

	wetuwn 0;
}

static int __dwm_mode_set_config_intewnaw(stwuct dwm_mode_set *set,
					  stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_cwtc *cwtc = set->cwtc;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_cwtc *tmp;
	int wet;

	WAWN_ON(dwm_dwv_uses_atomic_modeset(cwtc->dev));

	/*
	 * NOTE: ->set_config can awso disabwe othew cwtcs (if we steaw aww
	 * connectows fwom it), hence we need to wefcount the fbs acwoss aww
	 * cwtcs. Atomic modeset wiww have sanew semantics ...
	 */
	dwm_fow_each_cwtc(tmp, cwtc->dev) {
		stwuct dwm_pwane *pwane = tmp->pwimawy;

		pwane->owd_fb = pwane->fb;
	}

	fb = set->fb;

	wet = cwtc->funcs->set_config(set, ctx);
	if (wet == 0) {
		stwuct dwm_pwane *pwane = cwtc->pwimawy;

		pwane->cwtc = fb ? cwtc : NUWW;
		pwane->fb = fb;
	}

	dwm_fow_each_cwtc(tmp, cwtc->dev) {
		stwuct dwm_pwane *pwane = tmp->pwimawy;

		if (pwane->fb)
			dwm_fwamebuffew_get(pwane->fb);
		if (pwane->owd_fb)
			dwm_fwamebuffew_put(pwane->owd_fb);
		pwane->owd_fb = NUWW;
	}

	wetuwn wet;
}

/**
 * dwm_mode_set_config_intewnaw - hewpew to caww &dwm_mode_config_funcs.set_config
 * @set: modeset config to set
 *
 * This is a wittwe hewpew to wwap intewnaw cawws to the
 * &dwm_mode_config_funcs.set_config dwivew intewface. The onwy thing it adds is
 * cowwect wefcounting dance.
 *
 * This shouwd onwy be used by non-atomic wegacy dwivews.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_set_config_intewnaw(stwuct dwm_mode_set *set)
{
	WAWN_ON(dwm_dwv_uses_atomic_modeset(set->cwtc->dev));

	wetuwn __dwm_mode_set_config_intewnaw(set, NUWW);
}
EXPOWT_SYMBOW(dwm_mode_set_config_intewnaw);

/**
 * dwm_cwtc_check_viewpowt - Checks that a fwamebuffew is big enough fow the
 *     CWTC viewpowt
 * @cwtc: CWTC that fwamebuffew wiww be dispwayed on
 * @x: x panning
 * @y: y panning
 * @mode: mode that fwamebuffew wiww be dispwayed undew
 * @fb: fwamebuffew to check size of
 */
int dwm_cwtc_check_viewpowt(const stwuct dwm_cwtc *cwtc,
			    int x, int y,
			    const stwuct dwm_dispway_mode *mode,
			    const stwuct dwm_fwamebuffew *fb)

{
	int hdispway, vdispway;

	dwm_mode_get_hv_timing(mode, &hdispway, &vdispway);

	if (cwtc->state &&
	    dwm_wotation_90_ow_270(cwtc->pwimawy->state->wotation))
		swap(hdispway, vdispway);

	wetuwn dwm_fwamebuffew_check_swc_coowds(x << 16, y << 16,
						hdispway << 16, vdispway << 16,
						fb);
}
EXPOWT_SYMBOW(dwm_cwtc_check_viewpowt);

/**
 * dwm_mode_setcwtc - set CWTC configuwation
 * @dev: dwm device fow the ioctw
 * @data: data pointew fow the ioctw
 * @fiwe_pwiv: dwm fiwe fow the ioctw caww
 *
 * Buiwd a new CWTC configuwation based on usew wequest.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_setcwtc(stwuct dwm_device *dev, void *data,
		     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_config *config = &dev->mode_config;
	stwuct dwm_mode_cwtc *cwtc_weq = data;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_pwane *pwane;
	stwuct dwm_connectow **connectow_set = NUWW, *connectow;
	stwuct dwm_fwamebuffew *fb = NUWW;
	stwuct dwm_dispway_mode *mode = NUWW;
	stwuct dwm_mode_set set;
	uint32_t __usew *set_connectows_ptw;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet, i, num_connectows = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	/*
	 * Univewsaw pwane swc offsets awe onwy 16.16, pwevent havoc fow
	 * dwivews using univewsaw pwane code intewnawwy.
	 */
	if (cwtc_weq->x & 0xffff0000 || cwtc_weq->y & 0xffff0000)
		wetuwn -EWANGE;

	cwtc = dwm_cwtc_find(dev, fiwe_pwiv, cwtc_weq->cwtc_id);
	if (!cwtc) {
		DWM_DEBUG_KMS("Unknown CWTC ID %d\n", cwtc_weq->cwtc_id);
		wetuwn -ENOENT;
	}
	DWM_DEBUG_KMS("[CWTC:%d:%s]\n", cwtc->base.id, cwtc->name);

	pwane = cwtc->pwimawy;

	/* awwow disabwing with the pwimawy pwane weased */
	if (cwtc_weq->mode_vawid && !dwm_wease_hewd(fiwe_pwiv, pwane->base.id))
		wetuwn -EACCES;

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx,
				   DWM_MODESET_ACQUIWE_INTEWWUPTIBWE, wet);

	if (cwtc_weq->mode_vawid) {
		/* If we have a mode we need a fwamebuffew. */
		/* If we pass -1, set the mode with the cuwwentwy bound fb */
		if (cwtc_weq->fb_id == -1) {
			stwuct dwm_fwamebuffew *owd_fb;

			if (pwane->state)
				owd_fb = pwane->state->fb;
			ewse
				owd_fb = pwane->fb;

			if (!owd_fb) {
				DWM_DEBUG_KMS("CWTC doesn't have cuwwent FB\n");
				wet = -EINVAW;
				goto out;
			}

			fb = owd_fb;
			/* Make wefcounting symmetwic with the wookup path. */
			dwm_fwamebuffew_get(fb);
		} ewse {
			fb = dwm_fwamebuffew_wookup(dev, fiwe_pwiv, cwtc_weq->fb_id);
			if (!fb) {
				DWM_DEBUG_KMS("Unknown FB ID%d\n",
						cwtc_weq->fb_id);
				wet = -ENOENT;
				goto out;
			}
		}

		mode = dwm_mode_cweate(dev);
		if (!mode) {
			wet = -ENOMEM;
			goto out;
		}
		if (!fiwe_pwiv->aspect_watio_awwowed &&
		    (cwtc_weq->mode.fwags & DWM_MODE_FWAG_PIC_AW_MASK) != DWM_MODE_FWAG_PIC_AW_NONE) {
			DWM_DEBUG_KMS("Unexpected aspect-watio fwag bits\n");
			wet = -EINVAW;
			goto out;
		}


		wet = dwm_mode_convewt_umode(dev, mode, &cwtc_weq->mode);
		if (wet) {
			DWM_DEBUG_KMS("Invawid mode (wet=%d, status=%s)\n",
				      wet, dwm_get_mode_status_name(mode->status));
			dwm_mode_debug_pwintmodewine(mode);
			goto out;
		}

		/*
		 * Check whethew the pwimawy pwane suppowts the fb pixew fowmat.
		 * Dwivews not impwementing the univewsaw pwanes API use a
		 * defauwt fowmats wist pwovided by the DWM cowe which doesn't
		 * match weaw hawdwawe capabiwities. Skip the check in that
		 * case.
		 */
		if (!pwane->fowmat_defauwt) {
			wet = dwm_pwane_check_pixew_fowmat(pwane,
							   fb->fowmat->fowmat,
							   fb->modifiew);
			if (wet) {
				DWM_DEBUG_KMS("Invawid pixew fowmat %p4cc, modifiew 0x%wwx\n",
					      &fb->fowmat->fowmat,
					      fb->modifiew);
				goto out;
			}
		}

		wet = dwm_cwtc_check_viewpowt(cwtc, cwtc_weq->x, cwtc_weq->y,
					      mode, fb);
		if (wet)
			goto out;

	}

	if (cwtc_weq->count_connectows == 0 && mode) {
		DWM_DEBUG_KMS("Count connectows is 0 but mode set\n");
		wet = -EINVAW;
		goto out;
	}

	if (cwtc_weq->count_connectows > 0 && (!mode || !fb)) {
		DWM_DEBUG_KMS("Count connectows is %d but no mode ow fb set\n",
			  cwtc_weq->count_connectows);
		wet = -EINVAW;
		goto out;
	}

	if (cwtc_weq->count_connectows > 0) {
		u32 out_id;

		/* Avoid unbounded kewnew memowy awwocation */
		if (cwtc_weq->count_connectows > config->num_connectow) {
			wet = -EINVAW;
			goto out;
		}

		connectow_set = kmawwoc_awway(cwtc_weq->count_connectows,
					      sizeof(stwuct dwm_connectow *),
					      GFP_KEWNEW);
		if (!connectow_set) {
			wet = -ENOMEM;
			goto out;
		}

		fow (i = 0; i < cwtc_weq->count_connectows; i++) {
			connectow_set[i] = NUWW;
			set_connectows_ptw = (uint32_t __usew *)(unsigned wong)cwtc_weq->set_connectows_ptw;
			if (get_usew(out_id, &set_connectows_ptw[i])) {
				wet = -EFAUWT;
				goto out;
			}

			connectow = dwm_connectow_wookup(dev, fiwe_pwiv, out_id);
			if (!connectow) {
				DWM_DEBUG_KMS("Connectow id %d unknown\n",
						out_id);
				wet = -ENOENT;
				goto out;
			}
			DWM_DEBUG_KMS("[CONNECTOW:%d:%s]\n",
					connectow->base.id,
					connectow->name);

			connectow_set[i] = connectow;
			num_connectows++;
		}
	}

	set.cwtc = cwtc;
	set.x = cwtc_weq->x;
	set.y = cwtc_weq->y;
	set.mode = mode;
	set.connectows = connectow_set;
	set.num_connectows = num_connectows;
	set.fb = fb;

	if (dwm_dwv_uses_atomic_modeset(dev))
		wet = cwtc->funcs->set_config(&set, &ctx);
	ewse
		wet = __dwm_mode_set_config_intewnaw(&set, &ctx);

out:
	if (fb)
		dwm_fwamebuffew_put(fb);

	if (connectow_set) {
		fow (i = 0; i < num_connectows; i++) {
			if (connectow_set[i])
				dwm_connectow_put(connectow_set[i]);
		}
	}
	kfwee(connectow_set);
	dwm_mode_destwoy(dev, mode);

	/* In case we need to wetwy... */
	connectow_set = NUWW;
	fb = NUWW;
	mode = NUWW;

	DWM_MODESET_WOCK_AWW_END(dev, ctx, wet);

	wetuwn wet;
}

int dwm_mode_cwtc_set_obj_pwop(stwuct dwm_mode_object *obj,
			       stwuct dwm_pwopewty *pwopewty,
			       uint64_t vawue)
{
	int wet = -EINVAW;
	stwuct dwm_cwtc *cwtc = obj_to_cwtc(obj);

	if (cwtc->funcs->set_pwopewty)
		wet = cwtc->funcs->set_pwopewty(cwtc, pwopewty, vawue);
	if (!wet)
		dwm_object_pwopewty_set_vawue(obj, pwopewty, vawue);

	wetuwn wet;
}

/**
 * dwm_cwtc_cweate_scawing_fiwtew_pwopewty - cweate a new scawing fiwtew
 * pwopewty
 *
 * @cwtc: dwm CWTC
 * @suppowted_fiwtews: bitmask of suppowted scawing fiwtews, must incwude
 *		       BIT(DWM_SCAWING_FIWTEW_DEFAUWT).
 *
 * This function wets dwivew to enabwe the scawing fiwtew pwopewty on a given
 * CWTC.
 *
 * WETUWNS:
 * Zewo fow success ow -ewwno
 */
int dwm_cwtc_cweate_scawing_fiwtew_pwopewty(stwuct dwm_cwtc *cwtc,
					    unsigned int suppowted_fiwtews)
{
	stwuct dwm_pwopewty *pwop =
		dwm_cweate_scawing_fiwtew_pwop(cwtc->dev, suppowted_fiwtews);

	if (IS_EWW(pwop))
		wetuwn PTW_EWW(pwop);

	dwm_object_attach_pwopewty(&cwtc->base, pwop,
				   DWM_SCAWING_FIWTEW_DEFAUWT);
	cwtc->scawing_fiwtew_pwopewty = pwop;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_cwtc_cweate_scawing_fiwtew_pwopewty);
