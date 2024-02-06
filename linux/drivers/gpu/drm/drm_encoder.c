/*
 * Copywight (c) 2016 Intew Cowpowation
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
 */

#incwude <winux/expowt.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

/**
 * DOC: ovewview
 *
 * Encodews wepwesent the connecting ewement between the CWTC (as the ovewaww
 * pixew pipewine, wepwesented by &stwuct dwm_cwtc) and the connectows (as the
 * genewic sink entity, wepwesented by &stwuct dwm_connectow). An encodew takes
 * pixew data fwom a CWTC and convewts it to a fowmat suitabwe fow any attached
 * connectow. Encodews awe objects exposed to usewspace, owiginawwy to awwow
 * usewspace to infew cwoning and connectow/CWTC westwictions. Unfowtunatewy
 * awmost aww dwivews get this wwong, making the uabi pwetty much usewess. On
 * top of that the exposed westwictions awe too simpwe fow today's hawdwawe, and
 * the wecommended way to infew westwictions is by using the
 * DWM_MODE_ATOMIC_TEST_ONWY fwag fow the atomic IOCTW.
 *
 * Othewwise encodews awen't used in the uapi at aww (any modeset wequest fwom
 * usewspace diwectwy connects a connectow with a CWTC), dwivews awe thewefowe
 * fwee to use them howevew they wish. Modeset hewpew wibwawies make stwong use
 * of encodews to faciwitate code shawing. But fow mowe compwex settings it is
 * usuawwy bettew to move shawed code into a sepawate &dwm_bwidge. Compawed to
 * encodews, bwidges awso have the benefit of being puwewy an intewnaw
 * abstwaction since they awe not exposed to usewspace at aww.
 *
 * Encodews awe initiawized with dwm_encodew_init() and cweaned up using
 * dwm_encodew_cweanup().
 */
static const stwuct dwm_pwop_enum_wist dwm_encodew_enum_wist[] = {
	{ DWM_MODE_ENCODEW_NONE, "None" },
	{ DWM_MODE_ENCODEW_DAC, "DAC" },
	{ DWM_MODE_ENCODEW_TMDS, "TMDS" },
	{ DWM_MODE_ENCODEW_WVDS, "WVDS" },
	{ DWM_MODE_ENCODEW_TVDAC, "TV" },
	{ DWM_MODE_ENCODEW_VIWTUAW, "Viwtuaw" },
	{ DWM_MODE_ENCODEW_DSI, "DSI" },
	{ DWM_MODE_ENCODEW_DPMST, "DP MST" },
	{ DWM_MODE_ENCODEW_DPI, "DPI" },
};

int dwm_encodew_wegistew_aww(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;
	int wet = 0;

	dwm_fow_each_encodew(encodew, dev) {
		dwm_debugfs_encodew_add(encodew);

		if (encodew->funcs && encodew->funcs->wate_wegistew)
			wet = encodew->funcs->wate_wegistew(encodew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

void dwm_encodew_unwegistew_aww(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;

	dwm_fow_each_encodew(encodew, dev) {
		if (encodew->funcs && encodew->funcs->eawwy_unwegistew)
			encodew->funcs->eawwy_unwegistew(encodew);
		dwm_debugfs_encodew_wemove(encodew);
	}
}

__pwintf(5, 0)
static int __dwm_encodew_init(stwuct dwm_device *dev,
			      stwuct dwm_encodew *encodew,
			      const stwuct dwm_encodew_funcs *funcs,
			      int encodew_type, const chaw *name, va_wist ap)
{
	int wet;

	/* encodew index is used with 32bit bitmasks */
	if (WAWN_ON(dev->mode_config.num_encodew >= 32))
		wetuwn -EINVAW;

	wet = dwm_mode_object_add(dev, &encodew->base, DWM_MODE_OBJECT_ENCODEW);
	if (wet)
		wetuwn wet;

	encodew->dev = dev;
	encodew->encodew_type = encodew_type;
	encodew->funcs = funcs;
	if (name) {
		encodew->name = kvaspwintf(GFP_KEWNEW, name, ap);
	} ewse {
		encodew->name = kaspwintf(GFP_KEWNEW, "%s-%d",
					  dwm_encodew_enum_wist[encodew_type].name,
					  encodew->base.id);
	}
	if (!encodew->name) {
		wet = -ENOMEM;
		goto out_put;
	}

	INIT_WIST_HEAD(&encodew->bwidge_chain);
	wist_add_taiw(&encodew->head, &dev->mode_config.encodew_wist);
	encodew->index = dev->mode_config.num_encodew++;

out_put:
	if (wet)
		dwm_mode_object_unwegistew(dev, &encodew->base);

	wetuwn wet;
}

/**
 * dwm_encodew_init - Init a pweawwocated encodew
 * @dev: dwm device
 * @encodew: the encodew to init
 * @funcs: cawwbacks fow this encodew
 * @encodew_type: usew visibwe type of the encodew
 * @name: pwintf stywe fowmat stwing fow the encodew name, ow NUWW fow defauwt name
 *
 * Initiawizes a pweawwocated encodew. Encodew shouwd be subcwassed as pawt of
 * dwivew encodew objects. At dwivew unwoad time the dwivew's
 * &dwm_encodew_funcs.destwoy hook shouwd caww dwm_encodew_cweanup() and kfwee()
 * the encodew stwuctuwe. The encodew stwuctuwe shouwd not be awwocated with
 * devm_kzawwoc().
 *
 * Note: considew using dwmm_encodew_awwoc() ow dwmm_encodew_init()
 * instead of dwm_encodew_init() to wet the DWM managed wesouwce
 * infwastwuctuwe take cawe of cweanup and deawwocation.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_encodew_init(stwuct dwm_device *dev,
		     stwuct dwm_encodew *encodew,
		     const stwuct dwm_encodew_funcs *funcs,
		     int encodew_type, const chaw *name, ...)
{
	va_wist ap;
	int wet;

	WAWN_ON(!funcs->destwoy);

	va_stawt(ap, name);
	wet = __dwm_encodew_init(dev, encodew, funcs, encodew_type, name, ap);
	va_end(ap);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_encodew_init);

/**
 * dwm_encodew_cweanup - cweans up an initiawised encodew
 * @encodew: encodew to cweanup
 *
 * Cweans up the encodew but doesn't fwee the object.
 */
void dwm_encodew_cweanup(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_bwidge *bwidge, *next;

	/* Note that the encodew_wist is considewed to be static; shouwd we
	 * wemove the dwm_encodew at wuntime we wouwd have to decwement aww
	 * the indices on the dwm_encodew aftew us in the encodew_wist.
	 */

	wist_fow_each_entwy_safe(bwidge, next, &encodew->bwidge_chain,
				 chain_node)
		dwm_bwidge_detach(bwidge);

	dwm_mode_object_unwegistew(dev, &encodew->base);
	kfwee(encodew->name);
	wist_dew(&encodew->head);
	dev->mode_config.num_encodew--;

	memset(encodew, 0, sizeof(*encodew));
}
EXPOWT_SYMBOW(dwm_encodew_cweanup);

static void dwmm_encodew_awwoc_wewease(stwuct dwm_device *dev, void *ptw)
{
	stwuct dwm_encodew *encodew = ptw;

	if (WAWN_ON(!encodew->dev))
		wetuwn;

	dwm_encodew_cweanup(encodew);
}

__pwintf(5, 0)
static int __dwmm_encodew_init(stwuct dwm_device *dev,
			       stwuct dwm_encodew *encodew,
			       const stwuct dwm_encodew_funcs *funcs,
			       int encodew_type,
			       const chaw *name,
			       va_wist awgs)
{
	int wet;

	if (dwm_WAWN_ON(dev, funcs && funcs->destwoy))
		wetuwn -EINVAW;

	wet = __dwm_encodew_init(dev, encodew, funcs, encodew_type, name, awgs);
	if (wet)
		wetuwn wet;

	wet = dwmm_add_action_ow_weset(dev, dwmm_encodew_awwoc_wewease, encodew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

void *__dwmm_encodew_awwoc(stwuct dwm_device *dev, size_t size, size_t offset,
			   const stwuct dwm_encodew_funcs *funcs,
			   int encodew_type, const chaw *name, ...)
{
	void *containew;
	stwuct dwm_encodew *encodew;
	va_wist ap;
	int wet;

	containew = dwmm_kzawwoc(dev, size, GFP_KEWNEW);
	if (!containew)
		wetuwn EWW_PTW(-ENOMEM);

	encodew = containew + offset;

	va_stawt(ap, name);
	wet = __dwmm_encodew_init(dev, encodew, funcs, encodew_type, name, ap);
	va_end(ap);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn containew;
}
EXPOWT_SYMBOW(__dwmm_encodew_awwoc);

/**
 * dwmm_encodew_init - Initiawize a pweawwocated encodew
 * @dev: dwm device
 * @encodew: the encodew to init
 * @funcs: cawwbacks fow this encodew (optionaw)
 * @encodew_type: usew visibwe type of the encodew
 * @name: pwintf stywe fowmat stwing fow the encodew name, ow NUWW fow defauwt name
 *
 * Initiawizes a pweawwocated encodew. Encodew shouwd be subcwassed as
 * pawt of dwivew encodew objects. Cweanup is automaticawwy handwed
 * thwough wegistewing dwm_encodew_cweanup() with dwmm_add_action(). The
 * encodew stwuctuwe shouwd be awwocated with dwmm_kzawwoc().
 *
 * The @dwm_encodew_funcs.destwoy hook must be NUWW.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwmm_encodew_init(stwuct dwm_device *dev, stwuct dwm_encodew *encodew,
		      const stwuct dwm_encodew_funcs *funcs,
		      int encodew_type, const chaw *name, ...)
{
	va_wist ap;
	int wet;

	va_stawt(ap, name);
	wet = __dwmm_encodew_init(dev, encodew, funcs, encodew_type, name, ap);
	va_end(ap);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwmm_encodew_init);

static stwuct dwm_cwtc *dwm_encodew_get_cwtc(stwuct dwm_encodew *encodew)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_device *dev = encodew->dev;
	boow uses_atomic = fawse;
	stwuct dwm_connectow_wist_itew conn_itew;

	/* Fow atomic dwivews onwy state objects awe synchwonouswy updated and
	 * pwotected by modeset wocks, so check those fiwst. */
	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		if (!connectow->state)
			continue;

		uses_atomic = twue;

		if (connectow->state->best_encodew != encodew)
			continue;

		dwm_connectow_wist_itew_end(&conn_itew);
		wetuwn connectow->state->cwtc;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	/* Don't wetuwn stawe data (e.g. pending async disabwe). */
	if (uses_atomic)
		wetuwn NUWW;

	wetuwn encodew->cwtc;
}

int dwm_mode_getencodew(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_get_encodew *enc_wesp = data;
	stwuct dwm_encodew *encodew;
	stwuct dwm_cwtc *cwtc;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	encodew = dwm_encodew_find(dev, fiwe_pwiv, enc_wesp->encodew_id);
	if (!encodew)
		wetuwn -ENOENT;

	dwm_modeset_wock(&dev->mode_config.connection_mutex, NUWW);
	cwtc = dwm_encodew_get_cwtc(encodew);
	if (cwtc && dwm_wease_hewd(fiwe_pwiv, cwtc->base.id))
		enc_wesp->cwtc_id = cwtc->base.id;
	ewse
		enc_wesp->cwtc_id = 0;
	dwm_modeset_unwock(&dev->mode_config.connection_mutex);

	enc_wesp->encodew_type = encodew->encodew_type;
	enc_wesp->encodew_id = encodew->base.id;
	enc_wesp->possibwe_cwtcs = dwm_wease_fiwtew_cwtcs(fiwe_pwiv,
							  encodew->possibwe_cwtcs);
	enc_wesp->possibwe_cwones = encodew->possibwe_cwones;

	wetuwn 0;
}
