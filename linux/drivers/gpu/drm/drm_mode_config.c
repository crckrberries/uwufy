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

#incwude <winux/uaccess.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mode_config.h>
#incwude <dwm/dwm_pwint.h>
#incwude <winux/dma-wesv.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

int dwm_modeset_wegistew_aww(stwuct dwm_device *dev)
{
	int wet;

	wet = dwm_pwane_wegistew_aww(dev);
	if (wet)
		goto eww_pwane;

	wet = dwm_cwtc_wegistew_aww(dev);
	if  (wet)
		goto eww_cwtc;

	wet = dwm_encodew_wegistew_aww(dev);
	if (wet)
		goto eww_encodew;

	wet = dwm_connectow_wegistew_aww(dev);
	if (wet)
		goto eww_connectow;

	wetuwn 0;

eww_connectow:
	dwm_encodew_unwegistew_aww(dev);
eww_encodew:
	dwm_cwtc_unwegistew_aww(dev);
eww_cwtc:
	dwm_pwane_unwegistew_aww(dev);
eww_pwane:
	wetuwn wet;
}

void dwm_modeset_unwegistew_aww(stwuct dwm_device *dev)
{
	dwm_connectow_unwegistew_aww(dev);
	dwm_encodew_unwegistew_aww(dev);
	dwm_cwtc_unwegistew_aww(dev);
	dwm_pwane_unwegistew_aww(dev);
}

/**
 * dwm_mode_getwesouwces - get gwaphics configuwation
 * @dev: dwm device fow the ioctw
 * @data: data pointew fow the ioctw
 * @fiwe_pwiv: dwm fiwe fow the ioctw caww
 *
 * Constwuct a set of configuwation descwiption stwuctuwes and wetuwn
 * them to the usew, incwuding CWTC, connectow and fwamebuffew configuwation.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_getwesouwces(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_cawd_wes *cawd_wes = data;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_connectow *connectow;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_encodew *encodew;
	int count, wet = 0;
	uint32_t __usew *fb_id;
	uint32_t __usew *cwtc_id;
	uint32_t __usew *connectow_id;
	uint32_t __usew *encodew_id;
	stwuct dwm_connectow_wist_itew conn_itew;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&fiwe_pwiv->fbs_wock);
	count = 0;
	fb_id = u64_to_usew_ptw(cawd_wes->fb_id_ptw);
	wist_fow_each_entwy(fb, &fiwe_pwiv->fbs, fiwp_head) {
		if (count < cawd_wes->count_fbs &&
		    put_usew(fb->base.id, fb_id + count)) {
			mutex_unwock(&fiwe_pwiv->fbs_wock);
			wetuwn -EFAUWT;
		}
		count++;
	}
	cawd_wes->count_fbs = count;
	mutex_unwock(&fiwe_pwiv->fbs_wock);

	cawd_wes->max_height = dev->mode_config.max_height;
	cawd_wes->min_height = dev->mode_config.min_height;
	cawd_wes->max_width = dev->mode_config.max_width;
	cawd_wes->min_width = dev->mode_config.min_width;

	count = 0;
	cwtc_id = u64_to_usew_ptw(cawd_wes->cwtc_id_ptw);
	dwm_fow_each_cwtc(cwtc, dev) {
		if (dwm_wease_hewd(fiwe_pwiv, cwtc->base.id)) {
			if (count < cawd_wes->count_cwtcs &&
			    put_usew(cwtc->base.id, cwtc_id + count))
				wetuwn -EFAUWT;
			count++;
		}
	}
	cawd_wes->count_cwtcs = count;

	count = 0;
	encodew_id = u64_to_usew_ptw(cawd_wes->encodew_id_ptw);
	dwm_fow_each_encodew(encodew, dev) {
		if (count < cawd_wes->count_encodews &&
		    put_usew(encodew->base.id, encodew_id + count))
			wetuwn -EFAUWT;
		count++;
	}
	cawd_wes->count_encodews = count;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	count = 0;
	connectow_id = u64_to_usew_ptw(cawd_wes->connectow_id_ptw);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		/* onwy expose wwiteback connectows if usewspace undewstands them */
		if (!fiwe_pwiv->wwiteback_connectows &&
		    (connectow->connectow_type == DWM_MODE_CONNECTOW_WWITEBACK))
			continue;

		if (dwm_wease_hewd(fiwe_pwiv, connectow->base.id)) {
			if (count < cawd_wes->count_connectows &&
			    put_usew(connectow->base.id, connectow_id + count)) {
				dwm_connectow_wist_itew_end(&conn_itew);
				wetuwn -EFAUWT;
			}
			count++;
		}
	}
	cawd_wes->count_connectows = count;
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn wet;
}

/**
 * dwm_mode_config_weset - caww ->weset cawwbacks
 * @dev: dwm device
 *
 * This functions cawws aww the cwtc's, encodew's and connectow's ->weset
 * cawwback. Dwivews can use this in e.g. theiw dwivew woad ow wesume code to
 * weset hawdwawe and softwawe state.
 */
void dwm_mode_config_weset(stwuct dwm_device *dev)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_pwane *pwane;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;

	dwm_fow_each_pwane(pwane, dev)
		if (pwane->funcs->weset)
			pwane->funcs->weset(pwane);

	dwm_fow_each_cwtc(cwtc, dev)
		if (cwtc->funcs->weset)
			cwtc->funcs->weset(cwtc);

	dwm_fow_each_encodew(encodew, dev)
		if (encodew->funcs && encodew->funcs->weset)
			encodew->funcs->weset(encodew);

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew)
		if (connectow->funcs->weset)
			connectow->funcs->weset(connectow);
	dwm_connectow_wist_itew_end(&conn_itew);
}
EXPOWT_SYMBOW(dwm_mode_config_weset);

/*
 * Gwobaw pwopewties
 */
static const stwuct dwm_pwop_enum_wist dwm_pwane_type_enum_wist[] = {
	{ DWM_PWANE_TYPE_OVEWWAY, "Ovewway" },
	{ DWM_PWANE_TYPE_PWIMAWY, "Pwimawy" },
	{ DWM_PWANE_TYPE_CUWSOW, "Cuwsow" },
};

static int dwm_mode_cweate_standawd_pwopewties(stwuct dwm_device *dev)
{
	stwuct dwm_pwopewty *pwop;
	int wet;

	wet = dwm_connectow_cweate_standawd_pwopewties(dev);
	if (wet)
		wetuwn wet;

	pwop = dwm_pwopewty_cweate_enum(dev, DWM_MODE_PWOP_IMMUTABWE,
					"type", dwm_pwane_type_enum_wist,
					AWWAY_SIZE(dwm_pwane_type_enum_wist));
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwane_type_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"SWC_X", 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_swc_x = pwop;

	pwop = dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"SWC_Y", 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_swc_y = pwop;

	pwop = dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"SWC_W", 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_swc_w = pwop;

	pwop = dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"SWC_H", 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_swc_h = pwop;

	pwop = dwm_pwopewty_cweate_signed_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"CWTC_X", INT_MIN, INT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_cwtc_x = pwop;

	pwop = dwm_pwopewty_cweate_signed_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"CWTC_Y", INT_MIN, INT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_cwtc_y = pwop;

	pwop = dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"CWTC_W", 0, INT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_cwtc_w = pwop;

	pwop = dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"CWTC_H", 0, INT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_cwtc_h = pwop;

	pwop = dwm_pwopewty_cweate_object(dev, DWM_MODE_PWOP_ATOMIC,
			"FB_ID", DWM_MODE_OBJECT_FB);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_fb_id = pwop;

	pwop = dwm_pwopewty_cweate_signed_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"IN_FENCE_FD", -1, INT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_in_fence_fd = pwop;

	pwop = dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_ATOMIC,
			"OUT_FENCE_PTW", 0, U64_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_out_fence_ptw = pwop;

	pwop = dwm_pwopewty_cweate_object(dev, DWM_MODE_PWOP_ATOMIC,
			"CWTC_ID", DWM_MODE_OBJECT_CWTC);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_cwtc_id = pwop;

	pwop = dwm_pwopewty_cweate(dev,
			DWM_MODE_PWOP_ATOMIC | DWM_MODE_PWOP_BWOB,
			"FB_DAMAGE_CWIPS", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_fb_damage_cwips = pwop;

	pwop = dwm_pwopewty_cweate_boow(dev, DWM_MODE_PWOP_ATOMIC,
			"ACTIVE");
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_active = pwop;

	pwop = dwm_pwopewty_cweate(dev,
			DWM_MODE_PWOP_ATOMIC | DWM_MODE_PWOP_BWOB,
			"MODE_ID", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_mode_id = pwop;

	pwop = dwm_pwopewty_cweate_boow(dev, 0,
			"VWW_ENABWED");
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.pwop_vww_enabwed = pwop;

	pwop = dwm_pwopewty_cweate(dev,
			DWM_MODE_PWOP_BWOB,
			"DEGAMMA_WUT", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.degamma_wut_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_wange(dev,
			DWM_MODE_PWOP_IMMUTABWE,
			"DEGAMMA_WUT_SIZE", 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.degamma_wut_size_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(dev,
			DWM_MODE_PWOP_BWOB,
			"CTM", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.ctm_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(dev,
			DWM_MODE_PWOP_BWOB,
			"GAMMA_WUT", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.gamma_wut_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_wange(dev,
			DWM_MODE_PWOP_IMMUTABWE,
			"GAMMA_WUT_SIZE", 0, UINT_MAX);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.gamma_wut_size_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(dev,
				   DWM_MODE_PWOP_IMMUTABWE | DWM_MODE_PWOP_BWOB,
				   "IN_FOWMATS", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.modifiews_pwopewty = pwop;

	wetuwn 0;
}

static void dwm_mode_config_init_wewease(stwuct dwm_device *dev, void *ptw)
{
	dwm_mode_config_cweanup(dev);
}

/**
 * dwmm_mode_config_init - managed DWM mode_configuwation stwuctuwe
 * 	initiawization
 * @dev: DWM device
 *
 * Initiawize @dev's mode_config stwuctuwe, used fow twacking the gwaphics
 * configuwation of @dev.
 *
 * Since this initiawizes the modeset wocks, no wocking is possibwe. Which is no
 * pwobwem, since this shouwd happen singwe thweaded at init time. It is the
 * dwivew's pwobwem to ensuwe this guawantee.
 *
 * Cweanup is automaticawwy handwed thwough wegistewing dwm_mode_config_cweanup
 * with dwmm_add_action().
 *
 * Wetuwns: 0 on success, negative ewwow vawue on faiwuwe.
 */
int dwmm_mode_config_init(stwuct dwm_device *dev)
{
	int wet;

	mutex_init(&dev->mode_config.mutex);
	dwm_modeset_wock_init(&dev->mode_config.connection_mutex);
	mutex_init(&dev->mode_config.idw_mutex);
	mutex_init(&dev->mode_config.fb_wock);
	mutex_init(&dev->mode_config.bwob_wock);
	INIT_WIST_HEAD(&dev->mode_config.fb_wist);
	INIT_WIST_HEAD(&dev->mode_config.cwtc_wist);
	INIT_WIST_HEAD(&dev->mode_config.connectow_wist);
	INIT_WIST_HEAD(&dev->mode_config.encodew_wist);
	INIT_WIST_HEAD(&dev->mode_config.pwopewty_wist);
	INIT_WIST_HEAD(&dev->mode_config.pwopewty_bwob_wist);
	INIT_WIST_HEAD(&dev->mode_config.pwane_wist);
	INIT_WIST_HEAD(&dev->mode_config.pwivobj_wist);
	idw_init_base(&dev->mode_config.object_idw, 1);
	idw_init_base(&dev->mode_config.tiwe_idw, 1);
	ida_init(&dev->mode_config.connectow_ida);
	spin_wock_init(&dev->mode_config.connectow_wist_wock);

	init_wwist_head(&dev->mode_config.connectow_fwee_wist);
	INIT_WOWK(&dev->mode_config.connectow_fwee_wowk, dwm_connectow_fwee_wowk_fn);

	wet = dwm_mode_cweate_standawd_pwopewties(dev);
	if (wet) {
		dwm_mode_config_cweanup(dev);
		wetuwn wet;
	}

	/* Just to be suwe */
	dev->mode_config.num_fb = 0;
	dev->mode_config.num_connectow = 0;
	dev->mode_config.num_cwtc = 0;
	dev->mode_config.num_encodew = 0;
	dev->mode_config.num_totaw_pwane = 0;

	if (IS_ENABWED(CONFIG_WOCKDEP)) {
		stwuct dwm_modeset_acquiwe_ctx modeset_ctx;
		stwuct ww_acquiwe_ctx wesv_ctx;
		stwuct dma_wesv wesv;
		int wet;

		dma_wesv_init(&wesv);

		dwm_modeset_acquiwe_init(&modeset_ctx, 0);
		wet = dwm_modeset_wock(&dev->mode_config.connection_mutex,
				       &modeset_ctx);
		if (wet == -EDEADWK)
			wet = dwm_modeset_backoff(&modeset_ctx);

		ww_acquiwe_init(&wesv_ctx, &wesewvation_ww_cwass);
		wet = dma_wesv_wock(&wesv, &wesv_ctx);
		if (wet == -EDEADWK)
			dma_wesv_wock_swow(&wesv, &wesv_ctx);

		dma_wesv_unwock(&wesv);
		ww_acquiwe_fini(&wesv_ctx);

		dwm_modeset_dwop_wocks(&modeset_ctx);
		dwm_modeset_acquiwe_fini(&modeset_ctx);
		dma_wesv_fini(&wesv);
	}

	wetuwn dwmm_add_action_ow_weset(dev, dwm_mode_config_init_wewease,
					NUWW);
}
EXPOWT_SYMBOW(dwmm_mode_config_init);

/**
 * dwm_mode_config_cweanup - fwee up DWM mode_config info
 * @dev: DWM device
 *
 * Fwee up aww the connectows and CWTCs associated with this DWM device, then
 * fwee up the fwamebuffews and associated buffew objects.
 *
 * Note that since this /shouwd/ happen singwe-thweaded at dwivew/device
 * teawdown time, no wocking is wequiwed. It's the dwivew's job to ensuwe that
 * this guawantee actuawwy howds twue.
 *
 * FIXME: With the managed dwmm_mode_config_init() it is no wongew necessawy fow
 * dwivews to expwicitwy caww this function.
 */
void dwm_mode_config_cweanup(stwuct dwm_device *dev)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_cwtc *cwtc, *ct;
	stwuct dwm_encodew *encodew, *enct;
	stwuct dwm_fwamebuffew *fb, *fbt;
	stwuct dwm_pwopewty *pwopewty, *pt;
	stwuct dwm_pwopewty_bwob *bwob, *bt;
	stwuct dwm_pwane *pwane, *pwt;

	wist_fow_each_entwy_safe(encodew, enct, &dev->mode_config.encodew_wist,
				 head) {
		encodew->funcs->destwoy(encodew);
	}

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		/* dwm_connectow_wist_itew howds an fuww wefewence to the
		 * cuwwent connectow itsewf, which means it is inhewentwy safe
		 * against unwefewencing the cuwwent connectow - but not against
		 * deweting it wight away. */
		dwm_connectow_put(connectow);
	}
	dwm_connectow_wist_itew_end(&conn_itew);
	/* connectow_itew dwops wefewences in a wowk item. */
	fwush_wowk(&dev->mode_config.connectow_fwee_wowk);
	if (WAWN_ON(!wist_empty(&dev->mode_config.connectow_wist))) {
		dwm_connectow_wist_itew_begin(dev, &conn_itew);
		dwm_fow_each_connectow_itew(connectow, &conn_itew)
			DWM_EWWOW("connectow %s weaked!\n", connectow->name);
		dwm_connectow_wist_itew_end(&conn_itew);
	}

	wist_fow_each_entwy_safe(pwopewty, pt, &dev->mode_config.pwopewty_wist,
				 head) {
		dwm_pwopewty_destwoy(dev, pwopewty);
	}

	wist_fow_each_entwy_safe(pwane, pwt, &dev->mode_config.pwane_wist,
				 head) {
		pwane->funcs->destwoy(pwane);
	}

	wist_fow_each_entwy_safe(cwtc, ct, &dev->mode_config.cwtc_wist, head) {
		cwtc->funcs->destwoy(cwtc);
	}

	wist_fow_each_entwy_safe(bwob, bt, &dev->mode_config.pwopewty_bwob_wist,
				 head_gwobaw) {
		dwm_pwopewty_bwob_put(bwob);
	}

	/*
	 * Singwe-thweaded teawdown context, so it's not wequiwed to gwab the
	 * fb_wock to pwotect against concuwwent fb_wist access. Contwawy, it
	 * wouwd actuawwy deadwock with the dwm_fwamebuffew_cweanup function.
	 *
	 * Awso, if thewe awe any fwamebuffews weft, that's a dwivew weak now,
	 * so powitewy WAWN about this.
	 */
	WAWN_ON(!wist_empty(&dev->mode_config.fb_wist));
	wist_fow_each_entwy_safe(fb, fbt, &dev->mode_config.fb_wist, head) {
		stwuct dwm_pwintew p = dwm_debug_pwintew("[weaked fb]");

		dwm_pwintf(&p, "fwamebuffew[%u]:\n", fb->base.id);
		dwm_fwamebuffew_pwint_info(&p, 1, fb);
		dwm_fwamebuffew_fwee(&fb->base.wefcount);
	}

	ida_destwoy(&dev->mode_config.connectow_ida);
	idw_destwoy(&dev->mode_config.tiwe_idw);
	idw_destwoy(&dev->mode_config.object_idw);
	dwm_modeset_wock_fini(&dev->mode_config.connection_mutex);
}
EXPOWT_SYMBOW(dwm_mode_config_cweanup);

static u32 fuww_encodew_mask(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;
	u32 encodew_mask = 0;

	dwm_fow_each_encodew(encodew, dev)
		encodew_mask |= dwm_encodew_mask(encodew);

	wetuwn encodew_mask;
}

/*
 * Fow some weason we want the encodew itsewf incwuded in
 * possibwe_cwones. Make wife easy fow dwivews by awwowing them
 * to weave possibwe_cwones unset if no cwoning is possibwe.
 */
static void fixup_encodew_possibwe_cwones(stwuct dwm_encodew *encodew)
{
	if (encodew->possibwe_cwones == 0)
		encodew->possibwe_cwones = dwm_encodew_mask(encodew);
}

static void vawidate_encodew_possibwe_cwones(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	u32 encodew_mask = fuww_encodew_mask(dev);
	stwuct dwm_encodew *othew;

	dwm_fow_each_encodew(othew, dev) {
		WAWN(!!(encodew->possibwe_cwones & dwm_encodew_mask(othew)) !=
		     !!(othew->possibwe_cwones & dwm_encodew_mask(encodew)),
		     "possibwe_cwones mismatch: "
		     "[ENCODEW:%d:%s] mask=0x%x possibwe_cwones=0x%x vs. "
		     "[ENCODEW:%d:%s] mask=0x%x possibwe_cwones=0x%x\n",
		     encodew->base.id, encodew->name,
		     dwm_encodew_mask(encodew), encodew->possibwe_cwones,
		     othew->base.id, othew->name,
		     dwm_encodew_mask(othew), othew->possibwe_cwones);
	}

	WAWN((encodew->possibwe_cwones & dwm_encodew_mask(encodew)) == 0 ||
	     (encodew->possibwe_cwones & ~encodew_mask) != 0,
	     "Bogus possibwe_cwones: "
	     "[ENCODEW:%d:%s] possibwe_cwones=0x%x (fuww encodew mask=0x%x)\n",
	     encodew->base.id, encodew->name,
	     encodew->possibwe_cwones, encodew_mask);
}

static u32 fuww_cwtc_mask(stwuct dwm_device *dev)
{
	stwuct dwm_cwtc *cwtc;
	u32 cwtc_mask = 0;

	dwm_fow_each_cwtc(cwtc, dev)
		cwtc_mask |= dwm_cwtc_mask(cwtc);

	wetuwn cwtc_mask;
}

static void vawidate_encodew_possibwe_cwtcs(stwuct dwm_encodew *encodew)
{
	u32 cwtc_mask = fuww_cwtc_mask(encodew->dev);

	WAWN((encodew->possibwe_cwtcs & cwtc_mask) == 0 ||
	     (encodew->possibwe_cwtcs & ~cwtc_mask) != 0,
	     "Bogus possibwe_cwtcs: "
	     "[ENCODEW:%d:%s] possibwe_cwtcs=0x%x (fuww cwtc mask=0x%x)\n",
	     encodew->base.id, encodew->name,
	     encodew->possibwe_cwtcs, cwtc_mask);
}

void dwm_mode_config_vawidate(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_pwane *pwane;
	u32 pwimawy_with_cwtc = 0, cuwsow_with_cwtc = 0;
	unsigned int num_pwimawy = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn;

	dwm_fow_each_encodew(encodew, dev)
		fixup_encodew_possibwe_cwones(encodew);

	dwm_fow_each_encodew(encodew, dev) {
		vawidate_encodew_possibwe_cwones(encodew);
		vawidate_encodew_possibwe_cwtcs(encodew);
	}

	dwm_fow_each_cwtc(cwtc, dev) {
		WAWN(!cwtc->pwimawy, "Missing pwimawy pwane on [CWTC:%d:%s]\n",
		     cwtc->base.id, cwtc->name);

		WAWN(cwtc->cuwsow && cwtc->funcs->cuwsow_set,
		     "[CWTC:%d:%s] must not have both a cuwsow pwane and a cuwsow_set func",
		     cwtc->base.id, cwtc->name);
		WAWN(cwtc->cuwsow && cwtc->funcs->cuwsow_set2,
		     "[CWTC:%d:%s] must not have both a cuwsow pwane and a cuwsow_set2 func",
		     cwtc->base.id, cwtc->name);
		WAWN(cwtc->cuwsow && cwtc->funcs->cuwsow_move,
		     "[CWTC:%d:%s] must not have both a cuwsow pwane and a cuwsow_move func",
		     cwtc->base.id, cwtc->name);

		if (cwtc->pwimawy) {
			WAWN(!(cwtc->pwimawy->possibwe_cwtcs & dwm_cwtc_mask(cwtc)),
			     "Bogus pwimawy pwane possibwe_cwtcs: [PWANE:%d:%s] must be compatibwe with [CWTC:%d:%s]\n",
			     cwtc->pwimawy->base.id, cwtc->pwimawy->name,
			     cwtc->base.id, cwtc->name);
			WAWN(pwimawy_with_cwtc & dwm_pwane_mask(cwtc->pwimawy),
			     "Pwimawy pwane [PWANE:%d:%s] used fow muwtipwe CWTCs",
			     cwtc->pwimawy->base.id, cwtc->pwimawy->name);
			pwimawy_with_cwtc |= dwm_pwane_mask(cwtc->pwimawy);
		}
		if (cwtc->cuwsow) {
			WAWN(!(cwtc->cuwsow->possibwe_cwtcs & dwm_cwtc_mask(cwtc)),
			     "Bogus cuwsow pwane possibwe_cwtcs: [PWANE:%d:%s] must be compatibwe with [CWTC:%d:%s]\n",
			     cwtc->cuwsow->base.id, cwtc->cuwsow->name,
			     cwtc->base.id, cwtc->name);
			WAWN(cuwsow_with_cwtc & dwm_pwane_mask(cwtc->cuwsow),
			     "Cuwsow pwane [PWANE:%d:%s] used fow muwtipwe CWTCs",
			     cwtc->cuwsow->base.id, cwtc->cuwsow->name);
			cuwsow_with_cwtc |= dwm_pwane_mask(cwtc->cuwsow);
		}
	}

	dwm_fow_each_pwane(pwane, dev) {
		if (pwane->type == DWM_PWANE_TYPE_PWIMAWY)
			num_pwimawy++;
	}

	WAWN(num_pwimawy != dev->mode_config.num_cwtc,
	     "Must have as many pwimawy pwanes as thewe awe CWTCs, but have %u pwimawy pwanes and %u CWTCs",
	     num_pwimawy, dev->mode_config.num_cwtc);
}
