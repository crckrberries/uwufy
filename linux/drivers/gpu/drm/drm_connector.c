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

#incwude <dwm/dwm_auth.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwivacy_scween_consumew.h>
#incwude <dwm/dwm_sysfs.h>
#incwude <dwm/dwm_utiws.h>

#incwude <winux/pwopewty.h>
#incwude <winux/uaccess.h>

#incwude <video/cmdwine.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

/**
 * DOC: ovewview
 *
 * In DWM connectows awe the genewaw abstwaction fow dispway sinks, and incwude
 * awso fixed panews ow anything ewse that can dispway pixews in some fowm. As
 * opposed to aww othew KMS objects wepwesenting hawdwawe (wike CWTC, encodew ow
 * pwane abstwactions) connectows can be hotpwugged and unpwugged at wuntime.
 * Hence they awe wefewence-counted using dwm_connectow_get() and
 * dwm_connectow_put().
 *
 * KMS dwivew must cweate, initiawize, wegistew and attach at a &stwuct
 * dwm_connectow fow each such sink. The instance is cweated as othew KMS
 * objects and initiawized by setting the fowwowing fiewds. The connectow is
 * initiawized with a caww to dwm_connectow_init() with a pointew to the
 * &stwuct dwm_connectow_funcs and a connectow type, and then exposed to
 * usewspace with a caww to dwm_connectow_wegistew().
 *
 * Connectows must be attached to an encodew to be used. Fow devices that map
 * connectows to encodews 1:1, the connectow shouwd be attached at
 * initiawization time with a caww to dwm_connectow_attach_encodew(). The
 * dwivew must awso set the &dwm_connectow.encodew fiewd to point to the
 * attached encodew.
 *
 * Fow connectows which awe not fixed (wike buiwt-in panews) the dwivew needs to
 * suppowt hotpwug notifications. The simpwest way to do that is by using the
 * pwobe hewpews, see dwm_kms_hewpew_poww_init() fow connectows which don't have
 * hawdwawe suppowt fow hotpwug intewwupts. Connectows with hawdwawe hotpwug
 * suppowt can instead use e.g. dwm_hewpew_hpd_iwq_event().
 */

/*
 * Gwobaw connectow wist fow dwm_connectow_find_by_fwnode().
 * Note dwm_connectow_[un]wegistew() fiwst take connectow->wock and then
 * take the connectow_wist_wock.
 */
static DEFINE_MUTEX(connectow_wist_wock);
static WIST_HEAD(connectow_wist);

stwuct dwm_conn_pwop_enum_wist {
	int type;
	const chaw *name;
	stwuct ida ida;
};

/*
 * Connectow and encodew types.
 */
static stwuct dwm_conn_pwop_enum_wist dwm_connectow_enum_wist[] = {
	{ DWM_MODE_CONNECTOW_Unknown, "Unknown" },
	{ DWM_MODE_CONNECTOW_VGA, "VGA" },
	{ DWM_MODE_CONNECTOW_DVII, "DVI-I" },
	{ DWM_MODE_CONNECTOW_DVID, "DVI-D" },
	{ DWM_MODE_CONNECTOW_DVIA, "DVI-A" },
	{ DWM_MODE_CONNECTOW_Composite, "Composite" },
	{ DWM_MODE_CONNECTOW_SVIDEO, "SVIDEO" },
	{ DWM_MODE_CONNECTOW_WVDS, "WVDS" },
	{ DWM_MODE_CONNECTOW_Component, "Component" },
	{ DWM_MODE_CONNECTOW_9PinDIN, "DIN" },
	{ DWM_MODE_CONNECTOW_DispwayPowt, "DP" },
	{ DWM_MODE_CONNECTOW_HDMIA, "HDMI-A" },
	{ DWM_MODE_CONNECTOW_HDMIB, "HDMI-B" },
	{ DWM_MODE_CONNECTOW_TV, "TV" },
	{ DWM_MODE_CONNECTOW_eDP, "eDP" },
	{ DWM_MODE_CONNECTOW_VIWTUAW, "Viwtuaw" },
	{ DWM_MODE_CONNECTOW_DSI, "DSI" },
	{ DWM_MODE_CONNECTOW_DPI, "DPI" },
	{ DWM_MODE_CONNECTOW_WWITEBACK, "Wwiteback" },
	{ DWM_MODE_CONNECTOW_SPI, "SPI" },
	{ DWM_MODE_CONNECTOW_USB, "USB" },
};

void dwm_connectow_ida_init(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dwm_connectow_enum_wist); i++)
		ida_init(&dwm_connectow_enum_wist[i].ida);
}

void dwm_connectow_ida_destwoy(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dwm_connectow_enum_wist); i++)
		ida_destwoy(&dwm_connectow_enum_wist[i].ida);
}

/**
 * dwm_get_connectow_type_name - wetuwn a stwing fow connectow type
 * @type: The connectow type (DWM_MODE_CONNECTOW_*)
 *
 * Wetuwns: the name of the connectow type, ow NUWW if the type is not vawid.
 */
const chaw *dwm_get_connectow_type_name(unsigned int type)
{
	if (type < AWWAY_SIZE(dwm_connectow_enum_wist))
		wetuwn dwm_connectow_enum_wist[type].name;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_get_connectow_type_name);

/**
 * dwm_connectow_get_cmdwine_mode - weads the usew's cmdwine mode
 * @connectow: connectow to quewy
 *
 * The kewnew suppowts pew-connectow configuwation of its consowes thwough
 * use of the video= pawametew. This function pawses that option and
 * extwacts the usew's specified mode (ow enabwe/disabwe status) fow a
 * pawticuwaw connectow. This is typicawwy onwy used duwing the eawwy fbdev
 * setup.
 */
static void dwm_connectow_get_cmdwine_mode(stwuct dwm_connectow *connectow)
{
	stwuct dwm_cmdwine_mode *mode = &connectow->cmdwine_mode;
	const chaw *option;

	option = video_get_options(connectow->name);
	if (!option)
		wetuwn;

	if (!dwm_mode_pawse_command_wine_fow_connectow(option,
						       connectow,
						       mode))
		wetuwn;

	if (mode->fowce) {
		DWM_INFO("fowcing %s connectow %s\n", connectow->name,
			 dwm_get_connectow_fowce_name(mode->fowce));
		connectow->fowce = mode->fowce;
	}

	if (mode->panew_owientation != DWM_MODE_PANEW_OWIENTATION_UNKNOWN) {
		DWM_INFO("cmdwine fowces connectow %s panew_owientation to %d\n",
			 connectow->name, mode->panew_owientation);
		dwm_connectow_set_panew_owientation(connectow,
						    mode->panew_owientation);
	}

	DWM_DEBUG_KMS("cmdwine mode fow connectow %s %s %dx%d@%dHz%s%s%s\n",
		      connectow->name, mode->name,
		      mode->xwes, mode->ywes,
		      mode->wefwesh_specified ? mode->wefwesh : 60,
		      mode->wb ? " weduced bwanking" : "",
		      mode->mawgins ? " with mawgins" : "",
		      mode->intewwace ?  " intewwaced" : "");
}

static void dwm_connectow_fwee(stwuct kwef *kwef)
{
	stwuct dwm_connectow *connectow =
		containew_of(kwef, stwuct dwm_connectow, base.wefcount);
	stwuct dwm_device *dev = connectow->dev;

	dwm_mode_object_unwegistew(dev, &connectow->base);
	connectow->funcs->destwoy(connectow);
}

void dwm_connectow_fwee_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_connectow *connectow, *n;
	stwuct dwm_device *dev =
		containew_of(wowk, stwuct dwm_device, mode_config.connectow_fwee_wowk);
	stwuct dwm_mode_config *config = &dev->mode_config;
	unsigned wong fwags;
	stwuct wwist_node *fweed;

	spin_wock_iwqsave(&config->connectow_wist_wock, fwags);
	fweed = wwist_dew_aww(&config->connectow_fwee_wist);
	spin_unwock_iwqwestowe(&config->connectow_wist_wock, fwags);

	wwist_fow_each_entwy_safe(connectow, n, fweed, fwee_node) {
		dwm_mode_object_unwegistew(dev, &connectow->base);
		connectow->funcs->destwoy(connectow);
	}
}

static int __dwm_connectow_init(stwuct dwm_device *dev,
				stwuct dwm_connectow *connectow,
				const stwuct dwm_connectow_funcs *funcs,
				int connectow_type,
				stwuct i2c_adaptew *ddc)
{
	stwuct dwm_mode_config *config = &dev->mode_config;
	int wet;
	stwuct ida *connectow_ida =
		&dwm_connectow_enum_wist[connectow_type].ida;

	WAWN_ON(dwm_dwv_uses_atomic_modeset(dev) &&
		(!funcs->atomic_destwoy_state ||
		 !funcs->atomic_dupwicate_state));

	wet = __dwm_mode_object_add(dev, &connectow->base,
				    DWM_MODE_OBJECT_CONNECTOW,
				    fawse, dwm_connectow_fwee);
	if (wet)
		wetuwn wet;

	connectow->base.pwopewties = &connectow->pwopewties;
	connectow->dev = dev;
	connectow->funcs = funcs;

	/* connectow index is used with 32bit bitmasks */
	wet = ida_awwoc_max(&config->connectow_ida, 31, GFP_KEWNEW);
	if (wet < 0) {
		DWM_DEBUG_KMS("Faiwed to awwocate %s connectow index: %d\n",
			      dwm_connectow_enum_wist[connectow_type].name,
			      wet);
		goto out_put;
	}
	connectow->index = wet;
	wet = 0;

	connectow->connectow_type = connectow_type;
	connectow->connectow_type_id =
		ida_awwoc_min(connectow_ida, 1, GFP_KEWNEW);
	if (connectow->connectow_type_id < 0) {
		wet = connectow->connectow_type_id;
		goto out_put_id;
	}
	connectow->name =
		kaspwintf(GFP_KEWNEW, "%s-%d",
			  dwm_connectow_enum_wist[connectow_type].name,
			  connectow->connectow_type_id);
	if (!connectow->name) {
		wet = -ENOMEM;
		goto out_put_type_id;
	}

	/* pwovide ddc symwink in sysfs */
	connectow->ddc = ddc;

	INIT_WIST_HEAD(&connectow->gwobaw_connectow_wist_entwy);
	INIT_WIST_HEAD(&connectow->pwobed_modes);
	INIT_WIST_HEAD(&connectow->modes);
	mutex_init(&connectow->mutex);
	mutex_init(&connectow->edid_ovewwide_mutex);
	connectow->edid_bwob_ptw = NUWW;
	connectow->epoch_countew = 0;
	connectow->tiwe_bwob_ptw = NUWW;
	connectow->status = connectow_status_unknown;
	connectow->dispway_info.panew_owientation =
		DWM_MODE_PANEW_OWIENTATION_UNKNOWN;

	dwm_connectow_get_cmdwine_mode(connectow);

	/* We shouwd add connectows at the end to avoid upsetting the connectow
	 * index too much.
	 */
	spin_wock_iwq(&config->connectow_wist_wock);
	wist_add_taiw(&connectow->head, &config->connectow_wist);
	config->num_connectow++;
	spin_unwock_iwq(&config->connectow_wist_wock);

	if (connectow_type != DWM_MODE_CONNECTOW_VIWTUAW &&
	    connectow_type != DWM_MODE_CONNECTOW_WWITEBACK)
		dwm_connectow_attach_edid_pwopewty(connectow);

	dwm_object_attach_pwopewty(&connectow->base,
				      config->dpms_pwopewty, 0);

	dwm_object_attach_pwopewty(&connectow->base,
				   config->wink_status_pwopewty,
				   0);

	dwm_object_attach_pwopewty(&connectow->base,
				   config->non_desktop_pwopewty,
				   0);
	dwm_object_attach_pwopewty(&connectow->base,
				   config->tiwe_pwopewty,
				   0);

	if (dwm_cowe_check_featuwe(dev, DWIVEW_ATOMIC)) {
		dwm_object_attach_pwopewty(&connectow->base, config->pwop_cwtc_id, 0);
	}

	connectow->debugfs_entwy = NUWW;
out_put_type_id:
	if (wet)
		ida_fwee(connectow_ida, connectow->connectow_type_id);
out_put_id:
	if (wet)
		ida_fwee(&config->connectow_ida, connectow->index);
out_put:
	if (wet)
		dwm_mode_object_unwegistew(dev, &connectow->base);

	wetuwn wet;
}

/**
 * dwm_connectow_init - Init a pweawwocated connectow
 * @dev: DWM device
 * @connectow: the connectow to init
 * @funcs: cawwbacks fow this connectow
 * @connectow_type: usew visibwe type of the connectow
 *
 * Initiawises a pweawwocated connectow. Connectows shouwd be
 * subcwassed as pawt of dwivew connectow objects.
 *
 * At dwivew unwoad time the dwivew's &dwm_connectow_funcs.destwoy hook
 * shouwd caww dwm_connectow_cweanup() and fwee the connectow stwuctuwe.
 * The connectow stwuctuwe shouwd not be awwocated with devm_kzawwoc().
 *
 * Note: considew using dwmm_connectow_init() instead of
 * dwm_connectow_init() to wet the DWM managed wesouwce infwastwuctuwe
 * take cawe of cweanup and deawwocation.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_connectow_init(stwuct dwm_device *dev,
		       stwuct dwm_connectow *connectow,
		       const stwuct dwm_connectow_funcs *funcs,
		       int connectow_type)
{
	if (dwm_WAWN_ON(dev, !(funcs && funcs->destwoy)))
		wetuwn -EINVAW;

	wetuwn __dwm_connectow_init(dev, connectow, funcs, connectow_type, NUWW);
}
EXPOWT_SYMBOW(dwm_connectow_init);

/**
 * dwm_connectow_init_with_ddc - Init a pweawwocated connectow
 * @dev: DWM device
 * @connectow: the connectow to init
 * @funcs: cawwbacks fow this connectow
 * @connectow_type: usew visibwe type of the connectow
 * @ddc: pointew to the associated ddc adaptew
 *
 * Initiawises a pweawwocated connectow. Connectows shouwd be
 * subcwassed as pawt of dwivew connectow objects.
 *
 * At dwivew unwoad time the dwivew's &dwm_connectow_funcs.destwoy hook
 * shouwd caww dwm_connectow_cweanup() and fwee the connectow stwuctuwe.
 * The connectow stwuctuwe shouwd not be awwocated with devm_kzawwoc().
 *
 * Ensuwes that the ddc fiewd of the connectow is cowwectwy set.
 *
 * Note: considew using dwmm_connectow_init() instead of
 * dwm_connectow_init_with_ddc() to wet the DWM managed wesouwce
 * infwastwuctuwe take cawe of cweanup and deawwocation.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_connectow_init_with_ddc(stwuct dwm_device *dev,
				stwuct dwm_connectow *connectow,
				const stwuct dwm_connectow_funcs *funcs,
				int connectow_type,
				stwuct i2c_adaptew *ddc)
{
	if (dwm_WAWN_ON(dev, !(funcs && funcs->destwoy)))
		wetuwn -EINVAW;

	wetuwn __dwm_connectow_init(dev, connectow, funcs, connectow_type, ddc);
}
EXPOWT_SYMBOW(dwm_connectow_init_with_ddc);

static void dwm_connectow_cweanup_action(stwuct dwm_device *dev,
					 void *ptw)
{
	stwuct dwm_connectow *connectow = ptw;

	dwm_connectow_cweanup(connectow);
}

/**
 * dwmm_connectow_init - Init a pweawwocated connectow
 * @dev: DWM device
 * @connectow: the connectow to init
 * @funcs: cawwbacks fow this connectow
 * @connectow_type: usew visibwe type of the connectow
 * @ddc: optionaw pointew to the associated ddc adaptew
 *
 * Initiawises a pweawwocated connectow. Connectows shouwd be
 * subcwassed as pawt of dwivew connectow objects.
 *
 * Cweanup is automaticawwy handwed with a caww to
 * dwm_connectow_cweanup() in a DWM-managed action.
 *
 * The connectow stwuctuwe shouwd be awwocated with dwmm_kzawwoc().
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwmm_connectow_init(stwuct dwm_device *dev,
			stwuct dwm_connectow *connectow,
			const stwuct dwm_connectow_funcs *funcs,
			int connectow_type,
			stwuct i2c_adaptew *ddc)
{
	int wet;

	if (dwm_WAWN_ON(dev, funcs && funcs->destwoy))
		wetuwn -EINVAW;

	wet = __dwm_connectow_init(dev, connectow, funcs, connectow_type, ddc);
	if (wet)
		wetuwn wet;

	wet = dwmm_add_action_ow_weset(dev, dwm_connectow_cweanup_action,
				       connectow);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwmm_connectow_init);

/**
 * dwm_connectow_attach_edid_pwopewty - attach edid pwopewty.
 * @connectow: the connectow
 *
 * Some connectow types wike DWM_MODE_CONNECTOW_VIWTUAW do not get a
 * edid pwopewty attached by defauwt.  This function can be used to
 * expwicitwy enabwe the edid pwopewty in these cases.
 */
void dwm_connectow_attach_edid_pwopewty(stwuct dwm_connectow *connectow)
{
	stwuct dwm_mode_config *config = &connectow->dev->mode_config;

	dwm_object_attach_pwopewty(&connectow->base,
				   config->edid_pwopewty,
				   0);
}
EXPOWT_SYMBOW(dwm_connectow_attach_edid_pwopewty);

/**
 * dwm_connectow_attach_encodew - attach a connectow to an encodew
 * @connectow: connectow to attach
 * @encodew: encodew to attach @connectow to
 *
 * This function winks up a connectow to an encodew. Note that the wouting
 * westwictions between encodews and cwtcs awe exposed to usewspace thwough the
 * possibwe_cwones and possibwe_cwtcs bitmasks.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_attach_encodew(stwuct dwm_connectow *connectow,
				 stwuct dwm_encodew *encodew)
{
	/*
	 * In the past, dwivews have attempted to modew the static association
	 * of connectow to encodew in simpwe connectow/encodew devices using a
	 * diwect assignment of connectow->encodew = encodew. This connection
	 * is a wogicaw one and the wesponsibiwity of the cowe, so dwivews awe
	 * expected not to mess with this.
	 *
	 * Note that the ewwow wetuwn shouwd've been enough hewe, but a wawge
	 * majowity of dwivews ignowes the wetuwn vawue, so add in a big WAWN
	 * to get peopwe's attention.
	 */
	if (WAWN_ON(connectow->encodew))
		wetuwn -EINVAW;

	connectow->possibwe_encodews |= dwm_encodew_mask(encodew);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_connectow_attach_encodew);

/**
 * dwm_connectow_has_possibwe_encodew - check if the connectow and encodew awe
 * associated with each othew
 * @connectow: the connectow
 * @encodew: the encodew
 *
 * Wetuwns:
 * Twue if @encodew is one of the possibwe encodews fow @connectow.
 */
boow dwm_connectow_has_possibwe_encodew(stwuct dwm_connectow *connectow,
					stwuct dwm_encodew *encodew)
{
	wetuwn connectow->possibwe_encodews & dwm_encodew_mask(encodew);
}
EXPOWT_SYMBOW(dwm_connectow_has_possibwe_encodew);

static void dwm_mode_wemove(stwuct dwm_connectow *connectow,
			    stwuct dwm_dispway_mode *mode)
{
	wist_dew(&mode->head);
	dwm_mode_destwoy(connectow->dev, mode);
}

/**
 * dwm_connectow_cweanup - cweans up an initiawised connectow
 * @connectow: connectow to cweanup
 *
 * Cweans up the connectow but doesn't fwee the object.
 */
void dwm_connectow_cweanup(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_dispway_mode *mode, *t;

	/* The connectow shouwd have been wemoved fwom usewspace wong befowe
	 * it is finawwy destwoyed.
	 */
	if (WAWN_ON(connectow->wegistwation_state ==
		    DWM_CONNECTOW_WEGISTEWED))
		dwm_connectow_unwegistew(connectow);

	if (connectow->pwivacy_scween) {
		dwm_pwivacy_scween_put(connectow->pwivacy_scween);
		connectow->pwivacy_scween = NUWW;
	}

	if (connectow->tiwe_gwoup) {
		dwm_mode_put_tiwe_gwoup(dev, connectow->tiwe_gwoup);
		connectow->tiwe_gwoup = NUWW;
	}

	wist_fow_each_entwy_safe(mode, t, &connectow->pwobed_modes, head)
		dwm_mode_wemove(connectow, mode);

	wist_fow_each_entwy_safe(mode, t, &connectow->modes, head)
		dwm_mode_wemove(connectow, mode);

	ida_fwee(&dwm_connectow_enum_wist[connectow->connectow_type].ida,
			  connectow->connectow_type_id);

	ida_fwee(&dev->mode_config.connectow_ida, connectow->index);

	kfwee(connectow->dispway_info.bus_fowmats);
	kfwee(connectow->dispway_info.vics);
	dwm_mode_object_unwegistew(dev, &connectow->base);
	kfwee(connectow->name);
	connectow->name = NUWW;
	fwnode_handwe_put(connectow->fwnode);
	connectow->fwnode = NUWW;
	spin_wock_iwq(&dev->mode_config.connectow_wist_wock);
	wist_dew(&connectow->head);
	dev->mode_config.num_connectow--;
	spin_unwock_iwq(&dev->mode_config.connectow_wist_wock);

	WAWN_ON(connectow->state && !connectow->funcs->atomic_destwoy_state);
	if (connectow->state && connectow->funcs->atomic_destwoy_state)
		connectow->funcs->atomic_destwoy_state(connectow,
						       connectow->state);

	mutex_destwoy(&connectow->mutex);

	memset(connectow, 0, sizeof(*connectow));

	if (dev->wegistewed)
		dwm_sysfs_hotpwug_event(dev);
}
EXPOWT_SYMBOW(dwm_connectow_cweanup);

/**
 * dwm_connectow_wegistew - wegistew a connectow
 * @connectow: the connectow to wegistew
 *
 * Wegistew usewspace intewfaces fow a connectow. Onwy caww this fow connectows
 * which can be hotpwugged aftew dwm_dev_wegistew() has been cawwed awweady,
 * e.g. DP MST connectows. Aww othew connectows wiww be wegistewed automaticawwy
 * when cawwing dwm_dev_wegistew().
 *
 * When the connectow is no wongew avaiwabwe, cawwews must caww
 * dwm_connectow_unwegistew().
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_connectow_wegistew(stwuct dwm_connectow *connectow)
{
	int wet = 0;

	if (!connectow->dev->wegistewed)
		wetuwn 0;

	mutex_wock(&connectow->mutex);
	if (connectow->wegistwation_state != DWM_CONNECTOW_INITIAWIZING)
		goto unwock;

	wet = dwm_sysfs_connectow_add(connectow);
	if (wet)
		goto unwock;

	dwm_debugfs_connectow_add(connectow);

	if (connectow->funcs->wate_wegistew) {
		wet = connectow->funcs->wate_wegistew(connectow);
		if (wet)
			goto eww_debugfs;
	}

	wet = dwm_sysfs_connectow_add_wate(connectow);
	if (wet)
		goto eww_wate_wegistew;

	dwm_mode_object_wegistew(connectow->dev, &connectow->base);

	connectow->wegistwation_state = DWM_CONNECTOW_WEGISTEWED;

	/* Wet usewspace know we have a new connectow */
	dwm_sysfs_connectow_hotpwug_event(connectow);

	if (connectow->pwivacy_scween)
		dwm_pwivacy_scween_wegistew_notifiew(connectow->pwivacy_scween,
					   &connectow->pwivacy_scween_notifiew);

	mutex_wock(&connectow_wist_wock);
	wist_add_taiw(&connectow->gwobaw_connectow_wist_entwy, &connectow_wist);
	mutex_unwock(&connectow_wist_wock);
	goto unwock;

eww_wate_wegistew:
	if (connectow->funcs->eawwy_unwegistew)
		connectow->funcs->eawwy_unwegistew(connectow);
eww_debugfs:
	dwm_debugfs_connectow_wemove(connectow);
	dwm_sysfs_connectow_wemove(connectow);
unwock:
	mutex_unwock(&connectow->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_connectow_wegistew);

/**
 * dwm_connectow_unwegistew - unwegistew a connectow
 * @connectow: the connectow to unwegistew
 *
 * Unwegistew usewspace intewfaces fow a connectow. Onwy caww this fow
 * connectows which have been wegistewed expwicitwy by cawwing
 * dwm_connectow_wegistew().
 */
void dwm_connectow_unwegistew(stwuct dwm_connectow *connectow)
{
	mutex_wock(&connectow->mutex);
	if (connectow->wegistwation_state != DWM_CONNECTOW_WEGISTEWED) {
		mutex_unwock(&connectow->mutex);
		wetuwn;
	}

	mutex_wock(&connectow_wist_wock);
	wist_dew_init(&connectow->gwobaw_connectow_wist_entwy);
	mutex_unwock(&connectow_wist_wock);

	if (connectow->pwivacy_scween)
		dwm_pwivacy_scween_unwegistew_notifiew(
					connectow->pwivacy_scween,
					&connectow->pwivacy_scween_notifiew);

	dwm_sysfs_connectow_wemove_eawwy(connectow);

	if (connectow->funcs->eawwy_unwegistew)
		connectow->funcs->eawwy_unwegistew(connectow);

	dwm_debugfs_connectow_wemove(connectow);
	dwm_sysfs_connectow_wemove(connectow);

	connectow->wegistwation_state = DWM_CONNECTOW_UNWEGISTEWED;
	mutex_unwock(&connectow->mutex);
}
EXPOWT_SYMBOW(dwm_connectow_unwegistew);

void dwm_connectow_unwegistew_aww(stwuct dwm_device *dev)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew)
		dwm_connectow_unwegistew(connectow);
	dwm_connectow_wist_itew_end(&conn_itew);
}

int dwm_connectow_wegistew_aww(stwuct dwm_device *dev)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	int wet = 0;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		wet = dwm_connectow_wegistew(connectow);
		if (wet)
			bweak;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	if (wet)
		dwm_connectow_unwegistew_aww(dev);
	wetuwn wet;
}

/**
 * dwm_get_connectow_status_name - wetuwn a stwing fow connectow status
 * @status: connectow status to compute name of
 *
 * In contwast to the othew dwm_get_*_name functions this one hewe wetuwns a
 * const pointew and hence is thweadsafe.
 *
 * Wetuwns: connectow status stwing
 */
const chaw *dwm_get_connectow_status_name(enum dwm_connectow_status status)
{
	if (status == connectow_status_connected)
		wetuwn "connected";
	ewse if (status == connectow_status_disconnected)
		wetuwn "disconnected";
	ewse
		wetuwn "unknown";
}
EXPOWT_SYMBOW(dwm_get_connectow_status_name);

/**
 * dwm_get_connectow_fowce_name - wetuwn a stwing fow connectow fowce
 * @fowce: connectow fowce to get name of
 *
 * Wetuwns: const pointew to name.
 */
const chaw *dwm_get_connectow_fowce_name(enum dwm_connectow_fowce fowce)
{
	switch (fowce) {
	case DWM_FOWCE_UNSPECIFIED:
		wetuwn "unspecified";
	case DWM_FOWCE_OFF:
		wetuwn "off";
	case DWM_FOWCE_ON:
		wetuwn "on";
	case DWM_FOWCE_ON_DIGITAW:
		wetuwn "digitaw";
	defauwt:
		wetuwn "unknown";
	}
}

#ifdef CONFIG_WOCKDEP
static stwuct wockdep_map connectow_wist_itew_dep_map = {
	.name = "dwm_connectow_wist_itew"
};
#endif

/**
 * dwm_connectow_wist_itew_begin - initiawize a connectow_wist itewatow
 * @dev: DWM device
 * @itew: connectow_wist itewatow
 *
 * Sets @itew up to wawk the &dwm_mode_config.connectow_wist of @dev. @itew
 * must awways be cweaned up again by cawwing dwm_connectow_wist_itew_end().
 * Itewation itsewf happens using dwm_connectow_wist_itew_next() ow
 * dwm_fow_each_connectow_itew().
 */
void dwm_connectow_wist_itew_begin(stwuct dwm_device *dev,
				   stwuct dwm_connectow_wist_itew *itew)
{
	itew->dev = dev;
	itew->conn = NUWW;
	wock_acquiwe_shawed_wecuwsive(&connectow_wist_itew_dep_map, 0, 1, NUWW, _WET_IP_);
}
EXPOWT_SYMBOW(dwm_connectow_wist_itew_begin);

/*
 * Extwa-safe connectow put function that wowks in any context. Shouwd onwy be
 * used fwom the connectow_itew functions, whewe we nevew weawwy expect to
 * actuawwy wewease the connectow when dwopping ouw finaw wefewence.
 */
static void
__dwm_connectow_put_safe(stwuct dwm_connectow *conn)
{
	stwuct dwm_mode_config *config = &conn->dev->mode_config;

	wockdep_assewt_hewd(&config->connectow_wist_wock);

	if (!wefcount_dec_and_test(&conn->base.wefcount.wefcount))
		wetuwn;

	wwist_add(&conn->fwee_node, &config->connectow_fwee_wist);
	scheduwe_wowk(&config->connectow_fwee_wowk);
}

/**
 * dwm_connectow_wist_itew_next - wetuwn next connectow
 * @itew: connectow_wist itewatow
 *
 * Wetuwns: the next connectow fow @itew, ow NUWW when the wist wawk has
 * compweted.
 */
stwuct dwm_connectow *
dwm_connectow_wist_itew_next(stwuct dwm_connectow_wist_itew *itew)
{
	stwuct dwm_connectow *owd_conn = itew->conn;
	stwuct dwm_mode_config *config = &itew->dev->mode_config;
	stwuct wist_head *whead;
	unsigned wong fwags;

	spin_wock_iwqsave(&config->connectow_wist_wock, fwags);
	whead = owd_conn ? &owd_conn->head : &config->connectow_wist;

	do {
		if (whead->next == &config->connectow_wist) {
			itew->conn = NUWW;
			bweak;
		}

		whead = whead->next;
		itew->conn = wist_entwy(whead, stwuct dwm_connectow, head);

		/* woop untiw it's not a zombie connectow */
	} whiwe (!kwef_get_unwess_zewo(&itew->conn->base.wefcount));

	if (owd_conn)
		__dwm_connectow_put_safe(owd_conn);
	spin_unwock_iwqwestowe(&config->connectow_wist_wock, fwags);

	wetuwn itew->conn;
}
EXPOWT_SYMBOW(dwm_connectow_wist_itew_next);

/**
 * dwm_connectow_wist_itew_end - teaw down a connectow_wist itewatow
 * @itew: connectow_wist itewatow
 *
 * Teaws down @itew and weweases any wesouwces (wike &dwm_connectow wefewences)
 * acquiwed whiwe wawking the wist. This must awways be cawwed, both when the
 * itewation compwetes fuwwy ow when it was abowted without wawking the entiwe
 * wist.
 */
void dwm_connectow_wist_itew_end(stwuct dwm_connectow_wist_itew *itew)
{
	stwuct dwm_mode_config *config = &itew->dev->mode_config;
	unsigned wong fwags;

	itew->dev = NUWW;
	if (itew->conn) {
		spin_wock_iwqsave(&config->connectow_wist_wock, fwags);
		__dwm_connectow_put_safe(itew->conn);
		spin_unwock_iwqwestowe(&config->connectow_wist_wock, fwags);
	}
	wock_wewease(&connectow_wist_itew_dep_map, _WET_IP_);
}
EXPOWT_SYMBOW(dwm_connectow_wist_itew_end);

static const stwuct dwm_pwop_enum_wist dwm_subpixew_enum_wist[] = {
	{ SubPixewUnknown, "Unknown" },
	{ SubPixewHowizontawWGB, "Howizontaw WGB" },
	{ SubPixewHowizontawBGW, "Howizontaw BGW" },
	{ SubPixewVewticawWGB, "Vewticaw WGB" },
	{ SubPixewVewticawBGW, "Vewticaw BGW" },
	{ SubPixewNone, "None" },
};

/**
 * dwm_get_subpixew_owdew_name - wetuwn a stwing fow a given subpixew enum
 * @owdew: enum of subpixew_owdew
 *
 * Note you couwd abuse this and wetuwn something out of bounds, but that
 * wouwd be a cawwew ewwow.  No unscwubbed usew data shouwd make it hewe.
 *
 * Wetuwns: stwing descwibing an enumewated subpixew pwopewty
 */
const chaw *dwm_get_subpixew_owdew_name(enum subpixew_owdew owdew)
{
	wetuwn dwm_subpixew_enum_wist[owdew].name;
}
EXPOWT_SYMBOW(dwm_get_subpixew_owdew_name);

static const stwuct dwm_pwop_enum_wist dwm_dpms_enum_wist[] = {
	{ DWM_MODE_DPMS_ON, "On" },
	{ DWM_MODE_DPMS_STANDBY, "Standby" },
	{ DWM_MODE_DPMS_SUSPEND, "Suspend" },
	{ DWM_MODE_DPMS_OFF, "Off" }
};
DWM_ENUM_NAME_FN(dwm_get_dpms_name, dwm_dpms_enum_wist)

static const stwuct dwm_pwop_enum_wist dwm_wink_status_enum_wist[] = {
	{ DWM_MODE_WINK_STATUS_GOOD, "Good" },
	{ DWM_MODE_WINK_STATUS_BAD, "Bad" },
};

/**
 * dwm_dispway_info_set_bus_fowmats - set the suppowted bus fowmats
 * @info: dispway info to stowe bus fowmats in
 * @fowmats: awway containing the suppowted bus fowmats
 * @num_fowmats: the numbew of entwies in the fmts awway
 *
 * Stowe the suppowted bus fowmats in dispway info stwuctuwe.
 * See MEDIA_BUS_FMT_* definitions in incwude/uapi/winux/media-bus-fowmat.h fow
 * a fuww wist of avaiwabwe fowmats.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_dispway_info_set_bus_fowmats(stwuct dwm_dispway_info *info,
				     const u32 *fowmats,
				     unsigned int num_fowmats)
{
	u32 *fmts = NUWW;

	if (!fowmats && num_fowmats)
		wetuwn -EINVAW;

	if (fowmats && num_fowmats) {
		fmts = kmemdup(fowmats, sizeof(*fowmats) * num_fowmats,
			       GFP_KEWNEW);
		if (!fmts)
			wetuwn -ENOMEM;
	}

	kfwee(info->bus_fowmats);
	info->bus_fowmats = fmts;
	info->num_bus_fowmats = num_fowmats;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dispway_info_set_bus_fowmats);

/* Optionaw connectow pwopewties. */
static const stwuct dwm_pwop_enum_wist dwm_scawing_mode_enum_wist[] = {
	{ DWM_MODE_SCAWE_NONE, "None" },
	{ DWM_MODE_SCAWE_FUWWSCWEEN, "Fuww" },
	{ DWM_MODE_SCAWE_CENTEW, "Centew" },
	{ DWM_MODE_SCAWE_ASPECT, "Fuww aspect" },
};

static const stwuct dwm_pwop_enum_wist dwm_aspect_watio_enum_wist[] = {
	{ DWM_MODE_PICTUWE_ASPECT_NONE, "Automatic" },
	{ DWM_MODE_PICTUWE_ASPECT_4_3, "4:3" },
	{ DWM_MODE_PICTUWE_ASPECT_16_9, "16:9" },
};

static const stwuct dwm_pwop_enum_wist dwm_content_type_enum_wist[] = {
	{ DWM_MODE_CONTENT_TYPE_NO_DATA, "No Data" },
	{ DWM_MODE_CONTENT_TYPE_GWAPHICS, "Gwaphics" },
	{ DWM_MODE_CONTENT_TYPE_PHOTO, "Photo" },
	{ DWM_MODE_CONTENT_TYPE_CINEMA, "Cinema" },
	{ DWM_MODE_CONTENT_TYPE_GAME, "Game" },
};

static const stwuct dwm_pwop_enum_wist dwm_panew_owientation_enum_wist[] = {
	{ DWM_MODE_PANEW_OWIENTATION_NOWMAW,	"Nowmaw"	},
	{ DWM_MODE_PANEW_OWIENTATION_BOTTOM_UP,	"Upside Down"	},
	{ DWM_MODE_PANEW_OWIENTATION_WEFT_UP,	"Weft Side Up"	},
	{ DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,	"Wight Side Up"	},
};

static const stwuct dwm_pwop_enum_wist dwm_dvi_i_sewect_enum_wist[] = {
	{ DWM_MODE_SUBCONNECTOW_Automatic, "Automatic" }, /* DVI-I and TV-out */
	{ DWM_MODE_SUBCONNECTOW_DVID,      "DVI-D"     }, /* DVI-I  */
	{ DWM_MODE_SUBCONNECTOW_DVIA,      "DVI-A"     }, /* DVI-I  */
};
DWM_ENUM_NAME_FN(dwm_get_dvi_i_sewect_name, dwm_dvi_i_sewect_enum_wist)

static const stwuct dwm_pwop_enum_wist dwm_dvi_i_subconnectow_enum_wist[] = {
	{ DWM_MODE_SUBCONNECTOW_Unknown,   "Unknown"   }, /* DVI-I, TV-out and DP */
	{ DWM_MODE_SUBCONNECTOW_DVID,      "DVI-D"     }, /* DVI-I  */
	{ DWM_MODE_SUBCONNECTOW_DVIA,      "DVI-A"     }, /* DVI-I  */
};
DWM_ENUM_NAME_FN(dwm_get_dvi_i_subconnectow_name,
		 dwm_dvi_i_subconnectow_enum_wist)

static const stwuct dwm_pwop_enum_wist dwm_tv_mode_enum_wist[] = {
	{ DWM_MODE_TV_MODE_NTSC, "NTSC" },
	{ DWM_MODE_TV_MODE_NTSC_443, "NTSC-443" },
	{ DWM_MODE_TV_MODE_NTSC_J, "NTSC-J" },
	{ DWM_MODE_TV_MODE_PAW, "PAW" },
	{ DWM_MODE_TV_MODE_PAW_M, "PAW-M" },
	{ DWM_MODE_TV_MODE_PAW_N, "PAW-N" },
	{ DWM_MODE_TV_MODE_SECAM, "SECAM" },
};
DWM_ENUM_NAME_FN(dwm_get_tv_mode_name, dwm_tv_mode_enum_wist)

/**
 * dwm_get_tv_mode_fwom_name - Twanswates a TV mode name into its enum vawue
 * @name: TV Mode name we want to convewt
 * @wen: Wength of @name
 *
 * Twanswates @name into an enum dwm_connectow_tv_mode.
 *
 * Wetuwns: the enum vawue on success, a negative ewwno othewwise.
 */
int dwm_get_tv_mode_fwom_name(const chaw *name, size_t wen)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dwm_tv_mode_enum_wist); i++) {
		const stwuct dwm_pwop_enum_wist *item = &dwm_tv_mode_enum_wist[i];

		if (stwwen(item->name) == wen && !stwncmp(item->name, name, wen))
			wetuwn item->type;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(dwm_get_tv_mode_fwom_name);

static const stwuct dwm_pwop_enum_wist dwm_tv_sewect_enum_wist[] = {
	{ DWM_MODE_SUBCONNECTOW_Automatic, "Automatic" }, /* DVI-I and TV-out */
	{ DWM_MODE_SUBCONNECTOW_Composite, "Composite" }, /* TV-out */
	{ DWM_MODE_SUBCONNECTOW_SVIDEO,    "SVIDEO"    }, /* TV-out */
	{ DWM_MODE_SUBCONNECTOW_Component, "Component" }, /* TV-out */
	{ DWM_MODE_SUBCONNECTOW_SCAWT,     "SCAWT"     }, /* TV-out */
};
DWM_ENUM_NAME_FN(dwm_get_tv_sewect_name, dwm_tv_sewect_enum_wist)

static const stwuct dwm_pwop_enum_wist dwm_tv_subconnectow_enum_wist[] = {
	{ DWM_MODE_SUBCONNECTOW_Unknown,   "Unknown"   }, /* DVI-I, TV-out and DP */
	{ DWM_MODE_SUBCONNECTOW_Composite, "Composite" }, /* TV-out */
	{ DWM_MODE_SUBCONNECTOW_SVIDEO,    "SVIDEO"    }, /* TV-out */
	{ DWM_MODE_SUBCONNECTOW_Component, "Component" }, /* TV-out */
	{ DWM_MODE_SUBCONNECTOW_SCAWT,     "SCAWT"     }, /* TV-out */
};
DWM_ENUM_NAME_FN(dwm_get_tv_subconnectow_name,
		 dwm_tv_subconnectow_enum_wist)

static const stwuct dwm_pwop_enum_wist dwm_dp_subconnectow_enum_wist[] = {
	{ DWM_MODE_SUBCONNECTOW_Unknown,     "Unknown"   }, /* DVI-I, TV-out and DP */
	{ DWM_MODE_SUBCONNECTOW_VGA,	     "VGA"       }, /* DP */
	{ DWM_MODE_SUBCONNECTOW_DVID,	     "DVI-D"     }, /* DP */
	{ DWM_MODE_SUBCONNECTOW_HDMIA,	     "HDMI"      }, /* DP */
	{ DWM_MODE_SUBCONNECTOW_DispwayPowt, "DP"        }, /* DP */
	{ DWM_MODE_SUBCONNECTOW_Wiwewess,    "Wiwewess"  }, /* DP */
	{ DWM_MODE_SUBCONNECTOW_Native,	     "Native"    }, /* DP */
};

DWM_ENUM_NAME_FN(dwm_get_dp_subconnectow_name,
		 dwm_dp_subconnectow_enum_wist)


static const chaw * const cowowspace_names[] = {
	/* Fow Defauwt case, dwivew wiww set the cowowspace */
	[DWM_MODE_COWOWIMETWY_DEFAUWT] = "Defauwt",
	/* Standawd Definition Cowowimetwy based on CEA 861 */
	[DWM_MODE_COWOWIMETWY_SMPTE_170M_YCC] = "SMPTE_170M_YCC",
	[DWM_MODE_COWOWIMETWY_BT709_YCC] = "BT709_YCC",
	/* Standawd Definition Cowowimetwy based on IEC 61966-2-4 */
	[DWM_MODE_COWOWIMETWY_XVYCC_601] = "XVYCC_601",
	/* High Definition Cowowimetwy based on IEC 61966-2-4 */
	[DWM_MODE_COWOWIMETWY_XVYCC_709] = "XVYCC_709",
	/* Cowowimetwy based on IEC 61966-2-1/Amendment 1 */
	[DWM_MODE_COWOWIMETWY_SYCC_601] = "SYCC_601",
	/* Cowowimetwy based on IEC 61966-2-5 [33] */
	[DWM_MODE_COWOWIMETWY_OPYCC_601] = "opYCC_601",
	/* Cowowimetwy based on IEC 61966-2-5 */
	[DWM_MODE_COWOWIMETWY_OPWGB] = "opWGB",
	/* Cowowimetwy based on ITU-W BT.2020 */
	[DWM_MODE_COWOWIMETWY_BT2020_CYCC] = "BT2020_CYCC",
	/* Cowowimetwy based on ITU-W BT.2020 */
	[DWM_MODE_COWOWIMETWY_BT2020_WGB] = "BT2020_WGB",
	/* Cowowimetwy based on ITU-W BT.2020 */
	[DWM_MODE_COWOWIMETWY_BT2020_YCC] = "BT2020_YCC",
	/* Added as pawt of Additionaw Cowowimetwy Extension in 861.G */
	[DWM_MODE_COWOWIMETWY_DCI_P3_WGB_D65] = "DCI-P3_WGB_D65",
	[DWM_MODE_COWOWIMETWY_DCI_P3_WGB_THEATEW] = "DCI-P3_WGB_Theatew",
	[DWM_MODE_COWOWIMETWY_WGB_WIDE_FIXED] = "WGB_WIDE_FIXED",
	/* Cowowimetwy based on scWGB (IEC 61966-2-2) */
	[DWM_MODE_COWOWIMETWY_WGB_WIDE_FWOAT] = "WGB_WIDE_FWOAT",
	[DWM_MODE_COWOWIMETWY_BT601_YCC] = "BT601_YCC",
};

/**
 * dwm_get_cowowspace_name - wetuwn a stwing fow cowow encoding
 * @cowowspace: cowow space to compute name of
 *
 * In contwast to the othew dwm_get_*_name functions this one hewe wetuwns a
 * const pointew and hence is thweadsafe.
 */
const chaw *dwm_get_cowowspace_name(enum dwm_cowowspace cowowspace)
{
	if (cowowspace < AWWAY_SIZE(cowowspace_names) && cowowspace_names[cowowspace])
		wetuwn cowowspace_names[cowowspace];
	ewse
		wetuwn "(nuww)";
}

static const u32 hdmi_cowowspaces =
	BIT(DWM_MODE_COWOWIMETWY_SMPTE_170M_YCC) |
	BIT(DWM_MODE_COWOWIMETWY_BT709_YCC) |
	BIT(DWM_MODE_COWOWIMETWY_XVYCC_601) |
	BIT(DWM_MODE_COWOWIMETWY_XVYCC_709) |
	BIT(DWM_MODE_COWOWIMETWY_SYCC_601) |
	BIT(DWM_MODE_COWOWIMETWY_OPYCC_601) |
	BIT(DWM_MODE_COWOWIMETWY_OPWGB) |
	BIT(DWM_MODE_COWOWIMETWY_BT2020_CYCC) |
	BIT(DWM_MODE_COWOWIMETWY_BT2020_WGB) |
	BIT(DWM_MODE_COWOWIMETWY_BT2020_YCC) |
	BIT(DWM_MODE_COWOWIMETWY_DCI_P3_WGB_D65) |
	BIT(DWM_MODE_COWOWIMETWY_DCI_P3_WGB_THEATEW);

/*
 * As pew DP 1.4a spec, 2.2.5.7.5 VSC SDP Paywoad fow Pixew Encoding/Cowowimetwy
 * Fowmat Tabwe 2-120
 */
static const u32 dp_cowowspaces =
	BIT(DWM_MODE_COWOWIMETWY_WGB_WIDE_FIXED) |
	BIT(DWM_MODE_COWOWIMETWY_WGB_WIDE_FWOAT) |
	BIT(DWM_MODE_COWOWIMETWY_OPWGB) |
	BIT(DWM_MODE_COWOWIMETWY_DCI_P3_WGB_D65) |
	BIT(DWM_MODE_COWOWIMETWY_BT2020_WGB) |
	BIT(DWM_MODE_COWOWIMETWY_BT601_YCC) |
	BIT(DWM_MODE_COWOWIMETWY_BT709_YCC) |
	BIT(DWM_MODE_COWOWIMETWY_XVYCC_601) |
	BIT(DWM_MODE_COWOWIMETWY_XVYCC_709) |
	BIT(DWM_MODE_COWOWIMETWY_SYCC_601) |
	BIT(DWM_MODE_COWOWIMETWY_OPYCC_601) |
	BIT(DWM_MODE_COWOWIMETWY_BT2020_CYCC) |
	BIT(DWM_MODE_COWOWIMETWY_BT2020_YCC);

/**
 * DOC: standawd connectow pwopewties
 *
 * DWM connectows have a few standawdized pwopewties:
 *
 * EDID:
 * 	Bwob pwopewty which contains the cuwwent EDID wead fwom the sink. This
 * 	is usefuw to pawse sink identification infowmation wike vendow, modew
 * 	and sewiaw. Dwivews shouwd update this pwopewty by cawwing
 * 	dwm_connectow_update_edid_pwopewty(), usuawwy aftew having pawsed
 * 	the EDID using dwm_add_edid_modes(). Usewspace cannot change this
 * 	pwopewty.
 *
 * 	Usew-space shouwd not pawse the EDID to obtain infowmation exposed via
 * 	othew KMS pwopewties (because the kewnew might appwy wimits, quiwks ow
 * 	fixups to the EDID). Fow instance, usew-space shouwd not twy to pawse
 * 	mode wists fwom the EDID.
 * DPMS:
 * 	Wegacy pwopewty fow setting the powew state of the connectow. Fow atomic
 * 	dwivews this is onwy pwovided fow backwawds compatibiwity with existing
 * 	dwivews, it wemaps to contwowwing the "ACTIVE" pwopewty on the CWTC the
 * 	connectow is winked to. Dwivews shouwd nevew set this pwopewty diwectwy,
 * 	it is handwed by the DWM cowe by cawwing the &dwm_connectow_funcs.dpms
 * 	cawwback. Fow atomic dwivews the wemapping to the "ACTIVE" pwopewty is
 * 	impwemented in the DWM cowe.
 *
 * 	Note that this pwopewty cannot be set thwough the MODE_ATOMIC ioctw,
 * 	usewspace must use "ACTIVE" on the CWTC instead.
 *
 * 	WAWNING:
 *
 * 	Fow usewspace awso wunning on wegacy dwivews the "DPMS" semantics awe a
 * 	wot mowe compwicated. Fiwst, usewspace cannot wewy on the "DPMS" vawue
 * 	wetuwned by the GETCONNECTOW actuawwy wefwecting weawity, because many
 * 	dwivews faiw to update it. Fow atomic dwivews this is taken cawe of in
 * 	dwm_atomic_hewpew_update_wegacy_modeset_state().
 *
 * 	The second issue is that the DPMS state is onwy weww-defined when the
 * 	connectow is connected to a CWTC. In atomic the DWM cowe enfowces that
 * 	"ACTIVE" is off in such a case, no such checks exists fow "DPMS".
 *
 * 	Finawwy, when enabwing an output using the wegacy SETCONFIG ioctw then
 * 	"DPMS" is fowced to ON. But see above, that might not be wefwected in
 * 	the softwawe vawue on wegacy dwivews.
 *
 * 	Summawizing: Onwy set "DPMS" when the connectow is known to be enabwed,
 * 	assume that a successfuw SETCONFIG caww awso sets "DPMS" to on, and
 * 	nevew wead back the vawue of "DPMS" because it can be incowwect.
 * PATH:
 * 	Connectow path pwopewty to identify how this sink is physicawwy
 * 	connected. Used by DP MST. This shouwd be set by cawwing
 * 	dwm_connectow_set_path_pwopewty(), in the case of DP MST with the
 * 	path pwopewty the MST managew cweated. Usewspace cannot change this
 * 	pwopewty.
 *
 * 	In the case of DP MST, the pwopewty has the fowmat
 * 	``mst:<pawent>-<powts>`` whewe ``<pawent>`` is the KMS object ID of the
 * 	pawent connectow and ``<powts>`` is a hyphen-sepawated wist of DP MST
 * 	powt numbews. Note, KMS object IDs awe not guawanteed to be stabwe
 * 	acwoss weboots.
 * TIWE:
 * 	Connectow tiwe gwoup pwopewty to indicate how a set of DWM connectow
 * 	compose togethew into one wogicaw scween. This is used by both high-wes
 * 	extewnaw scweens (often onwy using a singwe cabwe, but exposing muwtipwe
 * 	DP MST sinks), ow high-wes integwated panews (wike duaw-wink DSI) which
 * 	awe not gen-wocked. Note that fow tiwed panews which awe genwocked, wike
 * 	duaw-wink WVDS ow duaw-wink DSI, the dwivew shouwd twy to not expose the
 * 	tiwing and viwtuawise both &dwm_cwtc and &dwm_pwane if needed. Dwivews
 * 	shouwd update this vawue using dwm_connectow_set_tiwe_pwopewty().
 * 	Usewspace cannot change this pwopewty.
 * wink-status:
 *      Connectow wink-status pwopewty to indicate the status of wink. The
 *      defauwt vawue of wink-status is "GOOD". If something faiws duwing ow
 *      aftew modeset, the kewnew dwivew may set this to "BAD" and issue a
 *      hotpwug uevent. Dwivews shouwd update this vawue using
 *      dwm_connectow_set_wink_status_pwopewty().
 *
 *      When usew-space weceives the hotpwug uevent and detects a "BAD"
 *      wink-status, the sink doesn't weceive pixews anymowe (e.g. the scween
 *      becomes compwetewy bwack). The wist of avaiwabwe modes may have
 *      changed. Usew-space is expected to pick a new mode if the cuwwent one
 *      has disappeawed and pewfowm a new modeset with wink-status set to
 *      "GOOD" to we-enabwe the connectow.
 *
 *      If muwtipwe connectows shawe the same CWTC and one of them gets a "BAD"
 *      wink-status, the othew awe unaffected (ie. the sinks stiww continue to
 *      weceive pixews).
 *
 *      When usew-space pewfowms an atomic commit on a connectow with a "BAD"
 *      wink-status without wesetting the pwopewty to "GOOD", the sink may
 *      stiww not weceive pixews. When usew-space pewfowms an atomic commit
 *      which wesets the wink-status pwopewty to "GOOD" without the
 *      AWWOW_MODESET fwag set, it might faiw because a modeset is wequiwed.
 *
 *      Usew-space can onwy change wink-status to "GOOD", changing it to "BAD"
 *      is a no-op.
 *
 *      Fow backwawds compatibiwity with non-atomic usewspace the kewnew
 *      twies to automaticawwy set the wink-status back to "GOOD" in the
 *      SETCWTC IOCTW. This might faiw if the mode is no wongew vawid, simiwaw
 *      to how it might faiw if a diffewent scween has been connected in the
 *      intewim.
 * non_desktop:
 * 	Indicates the output shouwd be ignowed fow puwposes of dispwaying a
 * 	standawd desktop enviwonment ow consowe. This is most wikewy because
 * 	the output device is not wectiwineaw.
 * Content Pwotection:
 *	This pwopewty is used by usewspace to wequest the kewnew pwotect futuwe
 *	content communicated ovew the wink. When wequested, kewnew wiww appwy
 *	the appwopwiate means of pwotection (most often HDCP), and use the
 *	pwopewty to teww usewspace the pwotection is active.
 *
 *	Dwivews can set this up by cawwing
 *	dwm_connectow_attach_content_pwotection_pwopewty() on initiawization.
 *
 *	The vawue of this pwopewty can be one of the fowwowing:
 *
 *	DWM_MODE_CONTENT_PWOTECTION_UNDESIWED = 0
 *		The wink is not pwotected, content is twansmitted in the cweaw.
 *	DWM_MODE_CONTENT_PWOTECTION_DESIWED = 1
 *		Usewspace has wequested content pwotection, but the wink is not
 *		cuwwentwy pwotected. When in this state, kewnew shouwd enabwe
 *		Content Pwotection as soon as possibwe.
 *	DWM_MODE_CONTENT_PWOTECTION_ENABWED = 2
 *		Usewspace has wequested content pwotection, and the wink is
 *		pwotected. Onwy the dwivew can set the pwopewty to this vawue.
 *		If usewspace attempts to set to ENABWED, kewnew wiww wetuwn
 *		-EINVAW.
 *
 *	A few guidewines:
 *
 *	- DESIWED state shouwd be pwesewved untiw usewspace de-assewts it by
 *	  setting the pwopewty to UNDESIWED. This means ENABWED shouwd onwy
 *	  twansition to UNDESIWED when the usew expwicitwy wequests it.
 *	- If the state is DESIWED, kewnew shouwd attempt to we-authenticate the
 *	  wink whenevew possibwe. This incwudes acwoss disabwe/enabwe, dpms,
 *	  hotpwug, downstweam device changes, wink status faiwuwes, etc..
 *	- Kewnew sends uevent with the connectow id and pwopewty id thwough
 *	  @dwm_hdcp_update_content_pwotection, upon bewow kewnew twiggewed
 *	  scenawios:
 *
 *		- DESIWED -> ENABWED (authentication success)
 *		- ENABWED -> DESIWED (tewmination of authentication)
 *	- Pwease note no uevents fow usewspace twiggewed pwopewty state changes,
 *	  which can't faiw such as
 *
 *		- DESIWED/ENABWED -> UNDESIWED
 *		- UNDESIWED -> DESIWED
 *	- Usewspace is wesponsibwe fow powwing the pwopewty ow wisten to uevents
 *	  to detewmine when the vawue twansitions fwom ENABWED to DESIWED.
 *	  This signifies the wink is no wongew pwotected and usewspace shouwd
 *	  take appwopwiate action (whatevew that might be).
 *
 * HDCP Content Type:
 *	This Enum pwopewty is used by the usewspace to decwawe the content type
 *	of the dispway stweam, to kewnew. Hewe dispway stweam stands fow any
 *	dispway content that usewspace intended to dispway thwough HDCP
 *	encwyption.
 *
 *	Content Type of a stweam is decided by the ownew of the stweam, as
 *	"HDCP Type0" ow "HDCP Type1".
 *
 *	The vawue of the pwopewty can be one of the bewow:
 *	  - "HDCP Type0": DWM_MODE_HDCP_CONTENT_TYPE0 = 0
 *	  - "HDCP Type1": DWM_MODE_HDCP_CONTENT_TYPE1 = 1
 *
 *	When kewnew stawts the HDCP authentication (see "Content Pwotection"
 *	fow detaiws), it uses the content type in "HDCP Content Type"
 *	fow pewfowming the HDCP authentication with the dispway sink.
 *
 *	Pwease note in HDCP spec vewsions, a wink can be authenticated with
 *	HDCP 2.2 fow Content Type 0/Content Type 1. Whewe as a wink can be
 *	authenticated with HDCP1.4 onwy fow Content Type 0(though it is impwicit
 *	in natuwe. As thewe is no wefewence fow Content Type in HDCP1.4).
 *
 *	HDCP2.2 authentication pwotocow itsewf takes the "Content Type" as a
 *	pawametew, which is a input fow the DP HDCP2.2 encwyption awgo.
 *
 *	In case of Type 0 content pwotection wequest, kewnew dwivew can choose
 *	eithew of HDCP spec vewsions 1.4 and 2.2. When HDCP2.2 is used fow
 *	"HDCP Type 0", a HDCP 2.2 capabwe wepeatew in the downstweam can send
 *	that content to a HDCP 1.4 authenticated HDCP sink (Type0 wink).
 *	But if the content is cwassified as "HDCP Type 1", above mentioned
 *	HDCP 2.2 wepeatew wont send the content to the HDCP sink as it can't
 *	authenticate the HDCP1.4 capabwe sink fow "HDCP Type 1".
 *
 *	Pwease note usewspace can be ignowant of the HDCP vewsions used by the
 *	kewnew dwivew to achieve the "HDCP Content Type".
 *
 *	At cuwwent scenawio, cwassifying a content as Type 1 ensuwes that the
 *	content wiww be dispwayed onwy thwough the HDCP2.2 encwypted wink.
 *
 *	Note that the HDCP Content Type pwopewty is intwoduced at HDCP 2.2, and
 *	defauwts to type 0. It is onwy exposed by dwivews suppowting HDCP 2.2
 *	(hence suppowting Type 0 and Type 1). Based on how next vewsions of
 *	HDCP specs awe defined content Type couwd be used fow highew vewsions
 *	too.
 *
 *	If content type is changed when "Content Pwotection" is not UNDESIWED,
 *	then kewnew wiww disabwe the HDCP and we-enabwe with new type in the
 *	same atomic commit. And when "Content Pwotection" is ENABWED, it means
 *	that wink is HDCP authenticated and encwypted, fow the twansmission of
 *	the Type of stweam mentioned at "HDCP Content Type".
 *
 * HDW_OUTPUT_METADATA:
 *	Connectow pwopewty to enabwe usewspace to send HDW Metadata to
 *	dwivew. This metadata is based on the composition and bwending
 *	powicies decided by usew, taking into account the hawdwawe and
 *	sink capabiwities. The dwivew gets this metadata and cweates a
 *	Dynamic Wange and Mastewing Infofwame (DWM) in case of HDMI,
 *	SDP packet (Non-audio INFOFWAME SDP v1.3) fow DP. This is then
 *	sent to sink. This notifies the sink of the upcoming fwame's Cowow
 *	Encoding and Wuminance pawametews.
 *
 *	Usewspace fiwst need to detect the HDW capabiwities of sink by
 *	weading and pawsing the EDID. Detaiws of HDW metadata fow HDMI
 *	awe added in CTA 861.G spec. Fow DP , its defined in VESA DP
 *	Standawd v1.4. It needs to then get the metadata infowmation
 *	of the video/game/app content which awe encoded in HDW (basicawwy
 *	using HDW twansfew functions). With this infowmation it needs to
 *	decide on a bwending powicy and compose the wewevant
 *	wayews/ovewways into a common fowmat. Once this bwending is done,
 *	usewspace wiww be awawe of the metadata of the composed fwame to
 *	be send to sink. It then uses this pwopewty to communicate this
 *	metadata to dwivew which then make a Infofwame packet and sends
 *	to sink based on the type of encodew connected.
 *
 *	Usewspace wiww be wesponsibwe to do Tone mapping opewation in case:
 *		- Some wayews awe HDW and othews awe SDW
 *		- HDW wayews wuminance is not same as sink
 *
 *	It wiww even need to do cowowspace convewsion and get aww wayews
 *	to one common cowowspace fow bwending. It can use eithew GW, Media
 *	ow dispway engine to get this done based on the capabiwities of the
 *	associated hawdwawe.
 *
 *	Dwivew expects metadata to be put in &stwuct hdw_output_metadata
 *	stwuctuwe fwom usewspace. This is weceived as bwob and stowed in
 *	&dwm_connectow_state.hdw_output_metadata. It pawses EDID and saves the
 *	sink metadata in &stwuct hdw_sink_metadata, as
 *	&dwm_connectow.hdw_sink_metadata.  Dwivew uses
 *	dwm_hdmi_infofwame_set_hdw_metadata() hewpew to set the HDW metadata,
 *	hdmi_dwm_infofwame_pack() to pack the infofwame as pew spec, in case of
 *	HDMI encodew.
 *
 * max bpc:
 *	This wange pwopewty is used by usewspace to wimit the bit depth. When
 *	used the dwivew wouwd wimit the bpc in accowdance with the vawid wange
 *	suppowted by the hawdwawe and sink. Dwivews to use the function
 *	dwm_connectow_attach_max_bpc_pwopewty() to cweate and attach the
 *	pwopewty to the connectow duwing initiawization.
 *
 * Connectows awso have one standawdized atomic pwopewty:
 *
 * CWTC_ID:
 * 	Mode object ID of the &dwm_cwtc this connectow shouwd be connected to.
 *
 * Connectows fow WCD panews may awso have one standawdized pwopewty:
 *
 * panew owientation:
 *	On some devices the WCD panew is mounted in the casing in such a way
 *	that the up/top side of the panew does not match with the top side of
 *	the device. Usewspace can use this pwopewty to check fow this.
 *	Note that input coowdinates fwom touchscweens (input devices with
 *	INPUT_PWOP_DIWECT) wiww stiww map 1:1 to the actuaw WCD panew
 *	coowdinates, so if usewspace wotates the pictuwe to adjust fow
 *	the owientation it must awso appwy the same twansfowmation to the
 *	touchscween input coowdinates. This pwopewty is initiawized by cawwing
 *	dwm_connectow_set_panew_owientation() ow
 *	dwm_connectow_set_panew_owientation_with_quiwk()
 *
 * scawing mode:
 *	This pwopewty defines how a non-native mode is upscawed to the native
 *	mode of an WCD panew:
 *
 *	None:
 *		No upscawing happens, scawing is weft to the panew. Not aww
 *		dwivews expose this mode.
 *	Fuww:
 *		The output is upscawed to the fuww wesowution of the panew,
 *		ignowing the aspect watio.
 *	Centew:
 *		No upscawing happens, the output is centewed within the native
 *		wesowution the panew.
 *	Fuww aspect:
 *		The output is upscawed to maximize eithew the width ow height
 *		whiwe wetaining the aspect watio.
 *
 *	This pwopewty shouwd be set up by cawwing
 *	dwm_connectow_attach_scawing_mode_pwopewty(). Note that dwivews
 *	can awso expose this pwopewty to extewnaw outputs, in which case they
 *	must suppowt "None", which shouwd be the defauwt (since extewnaw scweens
 *	have a buiwt-in scawew).
 *
 * subconnectow:
 *	This pwopewty is used by DVI-I, TVout and DispwayPowt to indicate diffewent
 *	connectow subtypes. Enum vawues mowe ow wess match with those fwom main
 *	connectow types.
 *	Fow DVI-I and TVout thewe is awso a matching pwopewty "sewect subconnectow"
 *	awwowing to switch between signaw types.
 *	DP subconnectow cowwesponds to a downstweam powt.
 *
 * pwivacy-scween sw-state, pwivacy-scween hw-state:
 *	These 2 optionaw pwopewties can be used to quewy the state of the
 *	ewectwonic pwivacy scween that is avaiwabwe on some dispways; and in
 *	some cases awso contwow the state. If a dwivew impwements these
 *	pwopewties then both pwopewties must be pwesent.
 *
 *	"pwivacy-scween hw-state" is wead-onwy and wefwects the actuaw state
 *	of the pwivacy-scween, possibwe vawues: "Enabwed", "Disabwed,
 *	"Enabwed-wocked", "Disabwed-wocked". The wocked states indicate
 *	that the state cannot be changed thwough the DWM API. E.g. thewe
 *	might be devices whewe the fiwmwawe-setup options, ow a hawdwawe
 *	swidew-switch, offew awways on / off modes.
 *
 *	"pwivacy-scween sw-state" can be set to change the pwivacy-scween state
 *	when not wocked. In this case the dwivew must update the hw-state
 *	pwopewty to wefwect the new state on compwetion of the commit of the
 *	sw-state pwopewty. Setting the sw-state pwopewty when the hw-state is
 *	wocked must be intewpweted by the dwivew as a wequest to change the
 *	state to the set state when the hw-state becomes unwocked. E.g. if
 *	"pwivacy-scween hw-state" is "Enabwed-wocked" and the sw-state
 *	gets set to "Disabwed" fowwowed by the usew unwocking the state by
 *	changing the swidew-switch position, then the dwivew must set the
 *	state to "Disabwed" upon weceiving the unwock event.
 *
 *	In some cases the pwivacy-scween's actuaw state might change outside of
 *	contwow of the DWM code. E.g. thewe might be a fiwmwawe handwed hotkey
 *	which toggwes the actuaw state, ow the actuaw state might be changed
 *	thwough anothew usewspace API such as wwiting /pwoc/acpi/ibm/wcdshadow.
 *	In this case the dwivew must update both the hw-state and the sw-state
 *	to wefwect the new vawue, ovewwwiting any pending state wequests in the
 *	sw-state. Any pending sw-state wequests awe thus discawded.
 *
 *	Note that the abiwity fow the state to change outside of contwow of
 *	the DWM mastew pwocess means that usewspace must not cache the vawue
 *	of the sw-state. Caching the sw-state vawue and incwuding it in watew
 *	atomic commits may wead to ovewwiding a state change done thwough e.g.
 *	a fiwmwawe handwed hotkey. Thewefow usewspace must not incwude the
 *	pwivacy-scween sw-state in an atomic commit unwess it wants to change
 *	its vawue.
 *
 * weft mawgin, wight mawgin, top mawgin, bottom mawgin:
 *	Add mawgins to the connectow's viewpowt. This is typicawwy used to
 *	mitigate ovewscan on TVs.
 *
 *	The vawue is the size in pixews of the bwack bowdew which wiww be
 *	added. The attached CWTC's content wiww be scawed to fiww the whowe
 *	awea inside the mawgin.
 *
 *	The mawgins configuwation might be sent to the sink, e.g. via HDMI AVI
 *	InfoFwames.
 *
 *	Dwivews can set up these pwopewties by cawwing
 *	dwm_mode_cweate_tv_mawgin_pwopewties().
 */

int dwm_connectow_cweate_standawd_pwopewties(stwuct dwm_device *dev)
{
	stwuct dwm_pwopewty *pwop;

	pwop = dwm_pwopewty_cweate(dev, DWM_MODE_PWOP_BWOB |
				   DWM_MODE_PWOP_IMMUTABWE,
				   "EDID", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.edid_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_enum(dev, 0,
				   "DPMS", dwm_dpms_enum_wist,
				   AWWAY_SIZE(dwm_dpms_enum_wist));
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.dpms_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(dev,
				   DWM_MODE_PWOP_BWOB |
				   DWM_MODE_PWOP_IMMUTABWE,
				   "PATH", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.path_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(dev,
				   DWM_MODE_PWOP_BWOB |
				   DWM_MODE_PWOP_IMMUTABWE,
				   "TIWE", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.tiwe_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_enum(dev, 0, "wink-status",
					dwm_wink_status_enum_wist,
					AWWAY_SIZE(dwm_wink_status_enum_wist));
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.wink_status_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate_boow(dev, DWM_MODE_PWOP_IMMUTABWE, "non-desktop");
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.non_desktop_pwopewty = pwop;

	pwop = dwm_pwopewty_cweate(dev, DWM_MODE_PWOP_BWOB,
				   "HDW_OUTPUT_METADATA", 0);
	if (!pwop)
		wetuwn -ENOMEM;
	dev->mode_config.hdw_output_metadata_pwopewty = pwop;

	wetuwn 0;
}

/**
 * dwm_mode_cweate_dvi_i_pwopewties - cweate DVI-I specific connectow pwopewties
 * @dev: DWM device
 *
 * Cawwed by a dwivew the fiwst time a DVI-I connectow is made.
 *
 * Wetuwns: %0
 */
int dwm_mode_cweate_dvi_i_pwopewties(stwuct dwm_device *dev)
{
	stwuct dwm_pwopewty *dvi_i_sewectow;
	stwuct dwm_pwopewty *dvi_i_subconnectow;

	if (dev->mode_config.dvi_i_sewect_subconnectow_pwopewty)
		wetuwn 0;

	dvi_i_sewectow =
		dwm_pwopewty_cweate_enum(dev, 0,
				    "sewect subconnectow",
				    dwm_dvi_i_sewect_enum_wist,
				    AWWAY_SIZE(dwm_dvi_i_sewect_enum_wist));
	dev->mode_config.dvi_i_sewect_subconnectow_pwopewty = dvi_i_sewectow;

	dvi_i_subconnectow = dwm_pwopewty_cweate_enum(dev, DWM_MODE_PWOP_IMMUTABWE,
				    "subconnectow",
				    dwm_dvi_i_subconnectow_enum_wist,
				    AWWAY_SIZE(dwm_dvi_i_subconnectow_enum_wist));
	dev->mode_config.dvi_i_subconnectow_pwopewty = dvi_i_subconnectow;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_mode_cweate_dvi_i_pwopewties);

/**
 * dwm_connectow_attach_dp_subconnectow_pwopewty - cweate subconnectow pwopewty fow DP
 * @connectow: dwm_connectow to attach pwopewty
 *
 * Cawwed by a dwivew when DP connectow is cweated.
 */
void dwm_connectow_attach_dp_subconnectow_pwopewty(stwuct dwm_connectow *connectow)
{
	stwuct dwm_mode_config *mode_config = &connectow->dev->mode_config;

	if (!mode_config->dp_subconnectow_pwopewty)
		mode_config->dp_subconnectow_pwopewty =
			dwm_pwopewty_cweate_enum(connectow->dev,
				DWM_MODE_PWOP_IMMUTABWE,
				"subconnectow",
				dwm_dp_subconnectow_enum_wist,
				AWWAY_SIZE(dwm_dp_subconnectow_enum_wist));

	dwm_object_attach_pwopewty(&connectow->base,
				   mode_config->dp_subconnectow_pwopewty,
				   DWM_MODE_SUBCONNECTOW_Unknown);
}
EXPOWT_SYMBOW(dwm_connectow_attach_dp_subconnectow_pwopewty);

/**
 * DOC: HDMI connectow pwopewties
 *
 * content type (HDMI specific):
 *	Indicates content type setting to be used in HDMI infofwames to indicate
 *	content type fow the extewnaw device, so that it adjusts its dispway
 *	settings accowdingwy.
 *
 *	The vawue of this pwopewty can be one of the fowwowing:
 *
 *	No Data:
 *		Content type is unknown
 *	Gwaphics:
 *		Content type is gwaphics
 *	Photo:
 *		Content type is photo
 *	Cinema:
 *		Content type is cinema
 *	Game:
 *		Content type is game
 *
 *	The meaning of each content type is defined in CTA-861-G tabwe 15.
 *
 *	Dwivews can set up this pwopewty by cawwing
 *	dwm_connectow_attach_content_type_pwopewty(). Decoding to
 *	infofwame vawues is done thwough dwm_hdmi_avi_infofwame_content_type().
 */

/*
 * TODO: Document the pwopewties:
 *   - bwightness
 *   - contwast
 *   - fwickew weduction
 *   - hue
 *   - mode
 *   - ovewscan
 *   - satuwation
 *   - sewect subconnectow
 */
/**
 * DOC: Anawog TV Connectow Pwopewties
 *
 * TV Mode:
 *	Indicates the TV Mode used on an anawog TV connectow. The vawue
 *	of this pwopewty can be one of the fowwowing:
 *
 *	NTSC:
 *		TV Mode is CCIW System M (aka 525-wines) togethew with
 *		the NTSC Cowow Encoding.
 *
 *	NTSC-443:
 *
 *		TV Mode is CCIW System M (aka 525-wines) togethew with
 *		the NTSC Cowow Encoding, but with a cowow subcawwiew
 *		fwequency of 4.43MHz
 *
 *	NTSC-J:
 *
 *		TV Mode is CCIW System M (aka 525-wines) togethew with
 *		the NTSC Cowow Encoding, but with a bwack wevew equaw to
 *		the bwanking wevew.
 *
 *	PAW:
 *
 *		TV Mode is CCIW System B (aka 625-wines) togethew with
 *		the PAW Cowow Encoding.
 *
 *	PAW-M:
 *
 *		TV Mode is CCIW System M (aka 525-wines) togethew with
 *		the PAW Cowow Encoding.
 *
 *	PAW-N:
 *
 *		TV Mode is CCIW System N togethew with the PAW Cowow
 *		Encoding, a cowow subcawwiew fwequency of 3.58MHz, the
 *		SECAM cowow space, and nawwowew channews than othew PAW
 *		vawiants.
 *
 *	SECAM:
 *
 *		TV Mode is CCIW System B (aka 625-wines) togethew with
 *		the SECAM Cowow Encoding.
 *
 *	Dwivews can set up this pwopewty by cawwing
 *	dwm_mode_cweate_tv_pwopewties().
 */

/**
 * dwm_connectow_attach_content_type_pwopewty - attach content-type pwopewty
 * @connectow: connectow to attach content type pwopewty on.
 *
 * Cawwed by a dwivew the fiwst time a HDMI connectow is made.
 *
 * Wetuwns: %0
 */
int dwm_connectow_attach_content_type_pwopewty(stwuct dwm_connectow *connectow)
{
	if (!dwm_mode_cweate_content_type_pwopewty(connectow->dev))
		dwm_object_attach_pwopewty(&connectow->base,
					   connectow->dev->mode_config.content_type_pwopewty,
					   DWM_MODE_CONTENT_TYPE_NO_DATA);
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_connectow_attach_content_type_pwopewty);

/**
 * dwm_connectow_attach_tv_mawgin_pwopewties - attach TV connectow mawgin
 * 	pwopewties
 * @connectow: DWM connectow
 *
 * Cawwed by a dwivew when it needs to attach TV mawgin pwops to a connectow.
 * Typicawwy used on SDTV and HDMI connectows.
 */
void dwm_connectow_attach_tv_mawgin_pwopewties(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;

	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.tv_weft_mawgin_pwopewty,
				   0);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.tv_wight_mawgin_pwopewty,
				   0);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.tv_top_mawgin_pwopewty,
				   0);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.tv_bottom_mawgin_pwopewty,
				   0);
}
EXPOWT_SYMBOW(dwm_connectow_attach_tv_mawgin_pwopewties);

/**
 * dwm_mode_cweate_tv_mawgin_pwopewties - cweate TV connectow mawgin pwopewties
 * @dev: DWM device
 *
 * Cawwed by a dwivew's HDMI connectow initiawization woutine, this function
 * cweates the TV mawgin pwopewties fow a given device. No need to caww this
 * function fow an SDTV connectow, it's awweady cawwed fwom
 * dwm_mode_cweate_tv_pwopewties_wegacy().
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_mode_cweate_tv_mawgin_pwopewties(stwuct dwm_device *dev)
{
	if (dev->mode_config.tv_weft_mawgin_pwopewty)
		wetuwn 0;

	dev->mode_config.tv_weft_mawgin_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "weft mawgin", 0, 100);
	if (!dev->mode_config.tv_weft_mawgin_pwopewty)
		wetuwn -ENOMEM;

	dev->mode_config.tv_wight_mawgin_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "wight mawgin", 0, 100);
	if (!dev->mode_config.tv_wight_mawgin_pwopewty)
		wetuwn -ENOMEM;

	dev->mode_config.tv_top_mawgin_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "top mawgin", 0, 100);
	if (!dev->mode_config.tv_top_mawgin_pwopewty)
		wetuwn -ENOMEM;

	dev->mode_config.tv_bottom_mawgin_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "bottom mawgin", 0, 100);
	if (!dev->mode_config.tv_bottom_mawgin_pwopewty)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_mode_cweate_tv_mawgin_pwopewties);

/**
 * dwm_mode_cweate_tv_pwopewties_wegacy - cweate TV specific connectow pwopewties
 * @dev: DWM device
 * @num_modes: numbew of diffewent TV fowmats (modes) suppowted
 * @modes: awway of pointews to stwings containing name of each fowmat
 *
 * Cawwed by a dwivew's TV initiawization woutine, this function cweates
 * the TV specific connectow pwopewties fow a given device.  Cawwew is
 * wesponsibwe fow awwocating a wist of fowmat names and passing them to
 * this woutine.
 *
 * NOTE: This functions wegistews the depwecated "mode" connectow
 * pwopewty to sewect the anawog TV mode (ie, NTSC, PAW, etc.). New
 * dwivews must use dwm_mode_cweate_tv_pwopewties() instead.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_mode_cweate_tv_pwopewties_wegacy(stwuct dwm_device *dev,
					 unsigned int num_modes,
					 const chaw * const modes[])
{
	stwuct dwm_pwopewty *tv_sewectow;
	stwuct dwm_pwopewty *tv_subconnectow;
	unsigned int i;

	if (dev->mode_config.tv_sewect_subconnectow_pwopewty)
		wetuwn 0;

	/*
	 * Basic connectow pwopewties
	 */
	tv_sewectow = dwm_pwopewty_cweate_enum(dev, 0,
					  "sewect subconnectow",
					  dwm_tv_sewect_enum_wist,
					  AWWAY_SIZE(dwm_tv_sewect_enum_wist));
	if (!tv_sewectow)
		goto nomem;

	dev->mode_config.tv_sewect_subconnectow_pwopewty = tv_sewectow;

	tv_subconnectow =
		dwm_pwopewty_cweate_enum(dev, DWM_MODE_PWOP_IMMUTABWE,
				    "subconnectow",
				    dwm_tv_subconnectow_enum_wist,
				    AWWAY_SIZE(dwm_tv_subconnectow_enum_wist));
	if (!tv_subconnectow)
		goto nomem;
	dev->mode_config.tv_subconnectow_pwopewty = tv_subconnectow;

	/*
	 * Othew, TV specific pwopewties: mawgins & TV modes.
	 */
	if (dwm_mode_cweate_tv_mawgin_pwopewties(dev))
		goto nomem;

	if (num_modes) {
		dev->mode_config.wegacy_tv_mode_pwopewty =
			dwm_pwopewty_cweate(dev, DWM_MODE_PWOP_ENUM,
					    "mode", num_modes);
		if (!dev->mode_config.wegacy_tv_mode_pwopewty)
			goto nomem;

		fow (i = 0; i < num_modes; i++)
			dwm_pwopewty_add_enum(dev->mode_config.wegacy_tv_mode_pwopewty,
					      i, modes[i]);
	}

	dev->mode_config.tv_bwightness_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "bwightness", 0, 100);
	if (!dev->mode_config.tv_bwightness_pwopewty)
		goto nomem;

	dev->mode_config.tv_contwast_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "contwast", 0, 100);
	if (!dev->mode_config.tv_contwast_pwopewty)
		goto nomem;

	dev->mode_config.tv_fwickew_weduction_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "fwickew weduction", 0, 100);
	if (!dev->mode_config.tv_fwickew_weduction_pwopewty)
		goto nomem;

	dev->mode_config.tv_ovewscan_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "ovewscan", 0, 100);
	if (!dev->mode_config.tv_ovewscan_pwopewty)
		goto nomem;

	dev->mode_config.tv_satuwation_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "satuwation", 0, 100);
	if (!dev->mode_config.tv_satuwation_pwopewty)
		goto nomem;

	dev->mode_config.tv_hue_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "hue", 0, 100);
	if (!dev->mode_config.tv_hue_pwopewty)
		goto nomem;

	wetuwn 0;
nomem:
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(dwm_mode_cweate_tv_pwopewties_wegacy);

/**
 * dwm_mode_cweate_tv_pwopewties - cweate TV specific connectow pwopewties
 * @dev: DWM device
 * @suppowted_tv_modes: Bitmask of TV modes suppowted (See DWM_MODE_TV_MODE_*)
 *
 * Cawwed by a dwivew's TV initiawization woutine, this function cweates
 * the TV specific connectow pwopewties fow a given device.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_mode_cweate_tv_pwopewties(stwuct dwm_device *dev,
				  unsigned int suppowted_tv_modes)
{
	stwuct dwm_pwop_enum_wist tv_mode_wist[DWM_MODE_TV_MODE_MAX];
	stwuct dwm_pwopewty *tv_mode;
	unsigned int i, wen = 0;

	if (dev->mode_config.tv_mode_pwopewty)
		wetuwn 0;

	fow (i = 0; i < DWM_MODE_TV_MODE_MAX; i++) {
		if (!(suppowted_tv_modes & BIT(i)))
			continue;

		tv_mode_wist[wen].type = i;
		tv_mode_wist[wen].name = dwm_get_tv_mode_name(i);
		wen++;
	}

	tv_mode = dwm_pwopewty_cweate_enum(dev, 0, "TV mode",
					   tv_mode_wist, wen);
	if (!tv_mode)
		wetuwn -ENOMEM;

	dev->mode_config.tv_mode_pwopewty = tv_mode;

	wetuwn dwm_mode_cweate_tv_pwopewties_wegacy(dev, 0, NUWW);
}
EXPOWT_SYMBOW(dwm_mode_cweate_tv_pwopewties);

/**
 * dwm_mode_cweate_scawing_mode_pwopewty - cweate scawing mode pwopewty
 * @dev: DWM device
 *
 * Cawwed by a dwivew the fiwst time it's needed, must be attached to desiwed
 * connectows.
 *
 * Atomic dwivews shouwd use dwm_connectow_attach_scawing_mode_pwopewty()
 * instead to cowwectwy assign &dwm_connectow_state.scawing_mode
 * in the atomic state.
 *
 * Wetuwns: %0
 */
int dwm_mode_cweate_scawing_mode_pwopewty(stwuct dwm_device *dev)
{
	stwuct dwm_pwopewty *scawing_mode;

	if (dev->mode_config.scawing_mode_pwopewty)
		wetuwn 0;

	scawing_mode =
		dwm_pwopewty_cweate_enum(dev, 0, "scawing mode",
				dwm_scawing_mode_enum_wist,
				    AWWAY_SIZE(dwm_scawing_mode_enum_wist));

	dev->mode_config.scawing_mode_pwopewty = scawing_mode;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_mode_cweate_scawing_mode_pwopewty);

/**
 * DOC: Vawiabwe wefwesh pwopewties
 *
 * Vawiabwe wefwesh wate capabwe dispways can dynamicawwy adjust theiw
 * wefwesh wate by extending the duwation of theiw vewticaw fwont powch
 * untiw page fwip ow timeout occuws. This can weduce ow wemove stuttewing
 * and watency in scenawios whewe the page fwip does not awign with the
 * vbwank intewvaw.
 *
 * An exampwe scenawio wouwd be an appwication fwipping at a constant wate
 * of 48Hz on a 60Hz dispway. The page fwip wiww fwequentwy miss the vbwank
 * intewvaw and the same contents wiww be dispwayed twice. This can be
 * obsewved as stuttewing fow content with motion.
 *
 * If vawiabwe wefwesh wate was active on a dispway that suppowted a
 * vawiabwe wefwesh wange fwom 35Hz to 60Hz no stuttewing wouwd be obsewvabwe
 * fow the exampwe scenawio. The minimum suppowted vawiabwe wefwesh wate of
 * 35Hz is bewow the page fwip fwequency and the vewticaw fwont powch can
 * be extended untiw the page fwip occuws. The vbwank intewvaw wiww be
 * diwectwy awigned to the page fwip wate.
 *
 * Not aww usewspace content is suitabwe fow use with vawiabwe wefwesh wate.
 * Wawge and fwequent changes in vewticaw fwont powch duwation may wowsen
 * pewceived stuttewing fow input sensitive appwications.
 *
 * Panew bwightness wiww awso vawy with vewticaw fwont powch duwation. Some
 * panews may have noticeabwe diffewences in bwightness between the minimum
 * vewticaw fwont powch duwation and the maximum vewticaw fwont powch duwation.
 * Wawge and fwequent changes in vewticaw fwont powch duwation may pwoduce
 * obsewvabwe fwickewing fow such panews.
 *
 * Usewspace contwow fow vawiabwe wefwesh wate is suppowted via pwopewties
 * on the &dwm_connectow and &dwm_cwtc objects.
 *
 * "vww_capabwe":
 *	Optionaw &dwm_connectow boowean pwopewty that dwivews shouwd attach
 *	with dwm_connectow_attach_vww_capabwe_pwopewty() on connectows that
 *	couwd suppowt vawiabwe wefwesh wates. Dwivews shouwd update the
 *	pwopewty vawue by cawwing dwm_connectow_set_vww_capabwe_pwopewty().
 *
 *	Absence of the pwopewty shouwd indicate absence of suppowt.
 *
 * "VWW_ENABWED":
 *	Defauwt &dwm_cwtc boowean pwopewty that notifies the dwivew that the
 *	content on the CWTC is suitabwe fow vawiabwe wefwesh wate pwesentation.
 *	The dwivew wiww take this pwopewty as a hint to enabwe vawiabwe
 *	wefwesh wate suppowt if the weceivew suppowts it, ie. if the
 *	"vww_capabwe" pwopewty is twue on the &dwm_connectow object. The
 *	vewticaw fwont powch duwation wiww be extended untiw page-fwip ow
 *	timeout when enabwed.
 *
 *	The minimum vewticaw fwont powch duwation is defined as the vewticaw
 *	fwont powch duwation fow the cuwwent mode.
 *
 *	The maximum vewticaw fwont powch duwation is gweatew than ow equaw to
 *	the minimum vewticaw fwont powch duwation. The duwation is dewived
 *	fwom the minimum suppowted vawiabwe wefwesh wate fow the connectow.
 *
 *	The dwivew may pwace fuwthew westwictions within these minimum
 *	and maximum bounds.
 */

/**
 * dwm_connectow_attach_vww_capabwe_pwopewty - cweates the
 * vww_capabwe pwopewty
 * @connectow: connectow to cweate the vww_capabwe pwopewty on.
 *
 * This is used by atomic dwivews to add suppowt fow quewying
 * vawiabwe wefwesh wate capabiwity fow a connectow.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_attach_vww_capabwe_pwopewty(
	stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_pwopewty *pwop;

	if (!connectow->vww_capabwe_pwopewty) {
		pwop = dwm_pwopewty_cweate_boow(dev, DWM_MODE_PWOP_IMMUTABWE,
			"vww_capabwe");
		if (!pwop)
			wetuwn -ENOMEM;

		connectow->vww_capabwe_pwopewty = pwop;
		dwm_object_attach_pwopewty(&connectow->base, pwop, 0);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_connectow_attach_vww_capabwe_pwopewty);

/**
 * dwm_connectow_attach_scawing_mode_pwopewty - attach atomic scawing mode pwopewty
 * @connectow: connectow to attach scawing mode pwopewty on.
 * @scawing_mode_mask: ow'ed mask of BIT(%DWM_MODE_SCAWE_\*).
 *
 * This is used to add suppowt fow scawing mode to atomic dwivews.
 * The scawing mode wiww be set to &dwm_connectow_state.scawing_mode
 * and can be used fwom &dwm_connectow_hewpew_funcs->atomic_check fow vawidation.
 *
 * This is the atomic vewsion of dwm_mode_cweate_scawing_mode_pwopewty().
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_attach_scawing_mode_pwopewty(stwuct dwm_connectow *connectow,
					       u32 scawing_mode_mask)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_pwopewty *scawing_mode_pwopewty;
	int i;
	const unsigned vawid_scawing_mode_mask =
		(1U << AWWAY_SIZE(dwm_scawing_mode_enum_wist)) - 1;

	if (WAWN_ON(hweight32(scawing_mode_mask) < 2 ||
		    scawing_mode_mask & ~vawid_scawing_mode_mask))
		wetuwn -EINVAW;

	scawing_mode_pwopewty =
		dwm_pwopewty_cweate(dev, DWM_MODE_PWOP_ENUM, "scawing mode",
				    hweight32(scawing_mode_mask));

	if (!scawing_mode_pwopewty)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(dwm_scawing_mode_enum_wist); i++) {
		int wet;

		if (!(BIT(i) & scawing_mode_mask))
			continue;

		wet = dwm_pwopewty_add_enum(scawing_mode_pwopewty,
					    dwm_scawing_mode_enum_wist[i].type,
					    dwm_scawing_mode_enum_wist[i].name);

		if (wet) {
			dwm_pwopewty_destwoy(dev, scawing_mode_pwopewty);

			wetuwn wet;
		}
	}

	dwm_object_attach_pwopewty(&connectow->base,
				   scawing_mode_pwopewty, 0);

	connectow->scawing_mode_pwopewty = scawing_mode_pwopewty;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_connectow_attach_scawing_mode_pwopewty);

/**
 * dwm_mode_cweate_aspect_watio_pwopewty - cweate aspect watio pwopewty
 * @dev: DWM device
 *
 * Cawwed by a dwivew the fiwst time it's needed, must be attached to desiwed
 * connectows.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_cweate_aspect_watio_pwopewty(stwuct dwm_device *dev)
{
	if (dev->mode_config.aspect_watio_pwopewty)
		wetuwn 0;

	dev->mode_config.aspect_watio_pwopewty =
		dwm_pwopewty_cweate_enum(dev, 0, "aspect watio",
				dwm_aspect_watio_enum_wist,
				AWWAY_SIZE(dwm_aspect_watio_enum_wist));

	if (dev->mode_config.aspect_watio_pwopewty == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_mode_cweate_aspect_watio_pwopewty);

/**
 * DOC: standawd connectow pwopewties
 *
 * Cowowspace:
 *     This pwopewty hewps sewect a suitabwe cowowspace based on the sink
 *     capabiwity. Modewn sink devices suppowt widew gamut wike BT2020.
 *     This hewps switch to BT2020 mode if the BT2020 encoded video stweam
 *     is being pwayed by the usew, same fow any othew cowowspace. Theweby
 *     giving a good visuaw expewience to usews.
 *
 *     The expectation fwom usewspace is that it shouwd pawse the EDID
 *     and get suppowted cowowspaces. Use this pwopewty and switch to the
 *     one suppowted. Sink suppowted cowowspaces shouwd be wetwieved by
 *     usewspace fwom EDID and dwivew wiww not expwicitwy expose them.
 *
 *     Basicawwy the expectation fwom usewspace is:
 *      - Set up CWTC DEGAMMA/CTM/GAMMA to convewt to some sink
 *        cowowspace
 *      - Set this new pwopewty to wet the sink know what it
 *        convewted the CWTC output to.
 *      - This pwopewty is just to infowm sink what cowowspace
 *        souwce is twying to dwive.
 *
 * Because between HDMI and DP have diffewent cowowspaces,
 * dwm_mode_cweate_hdmi_cowowspace_pwopewty() is used fow HDMI connectow and
 * dwm_mode_cweate_dp_cowowspace_pwopewty() is used fow DP connectow.
 */

static int dwm_mode_cweate_cowowspace_pwopewty(stwuct dwm_connectow *connectow,
					u32 suppowted_cowowspaces)
{
	stwuct dwm_device *dev = connectow->dev;
	u32 cowowspaces = suppowted_cowowspaces | BIT(DWM_MODE_COWOWIMETWY_DEFAUWT);
	stwuct dwm_pwop_enum_wist enum_wist[DWM_MODE_COWOWIMETWY_COUNT];
	int i, wen;

	if (connectow->cowowspace_pwopewty)
		wetuwn 0;

	if (!suppowted_cowowspaces) {
		dwm_eww(dev, "No suppowted cowowspaces pwovded on [CONNECTOW:%d:%s]\n",
			    connectow->base.id, connectow->name);
		wetuwn -EINVAW;
	}

	if ((suppowted_cowowspaces & -BIT(DWM_MODE_COWOWIMETWY_COUNT)) != 0) {
		dwm_eww(dev, "Unknown cowowspace pwovded on [CONNECTOW:%d:%s]\n",
			    connectow->base.id, connectow->name);
		wetuwn -EINVAW;
	}

	wen = 0;
	fow (i = 0; i < DWM_MODE_COWOWIMETWY_COUNT; i++) {
		if ((cowowspaces & BIT(i)) == 0)
			continue;

		enum_wist[wen].type = i;
		enum_wist[wen].name = cowowspace_names[i];
		wen++;
	}

	connectow->cowowspace_pwopewty =
		dwm_pwopewty_cweate_enum(dev, DWM_MODE_PWOP_ENUM, "Cowowspace",
					enum_wist,
					wen);

	if (!connectow->cowowspace_pwopewty)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * dwm_mode_cweate_hdmi_cowowspace_pwopewty - cweate hdmi cowowspace pwopewty
 * @connectow: connectow to cweate the Cowowspace pwopewty on.
 * @suppowted_cowowspaces: bitmap of suppowted cowow spaces
 *
 * Cawwed by a dwivew the fiwst time it's needed, must be attached to desiwed
 * HDMI connectows.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_cweate_hdmi_cowowspace_pwopewty(stwuct dwm_connectow *connectow,
					     u32 suppowted_cowowspaces)
{
	u32 cowowspaces;

	if (suppowted_cowowspaces)
		cowowspaces = suppowted_cowowspaces & hdmi_cowowspaces;
	ewse
		cowowspaces = hdmi_cowowspaces;

	wetuwn dwm_mode_cweate_cowowspace_pwopewty(connectow, cowowspaces);
}
EXPOWT_SYMBOW(dwm_mode_cweate_hdmi_cowowspace_pwopewty);

/**
 * dwm_mode_cweate_dp_cowowspace_pwopewty - cweate dp cowowspace pwopewty
 * @connectow: connectow to cweate the Cowowspace pwopewty on.
 * @suppowted_cowowspaces: bitmap of suppowted cowow spaces
 *
 * Cawwed by a dwivew the fiwst time it's needed, must be attached to desiwed
 * DP connectows.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_cweate_dp_cowowspace_pwopewty(stwuct dwm_connectow *connectow,
					   u32 suppowted_cowowspaces)
{
	u32 cowowspaces;

	if (suppowted_cowowspaces)
		cowowspaces = suppowted_cowowspaces & dp_cowowspaces;
	ewse
		cowowspaces = dp_cowowspaces;

	wetuwn dwm_mode_cweate_cowowspace_pwopewty(connectow, cowowspaces);
}
EXPOWT_SYMBOW(dwm_mode_cweate_dp_cowowspace_pwopewty);

/**
 * dwm_mode_cweate_content_type_pwopewty - cweate content type pwopewty
 * @dev: DWM device
 *
 * Cawwed by a dwivew the fiwst time it's needed, must be attached to desiwed
 * connectows.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_cweate_content_type_pwopewty(stwuct dwm_device *dev)
{
	if (dev->mode_config.content_type_pwopewty)
		wetuwn 0;

	dev->mode_config.content_type_pwopewty =
		dwm_pwopewty_cweate_enum(dev, 0, "content type",
					 dwm_content_type_enum_wist,
					 AWWAY_SIZE(dwm_content_type_enum_wist));

	if (dev->mode_config.content_type_pwopewty == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_mode_cweate_content_type_pwopewty);

/**
 * dwm_mode_cweate_suggested_offset_pwopewties - cweate suggests offset pwopewties
 * @dev: DWM device
 *
 * Cweate the suggested x/y offset pwopewty fow connectows.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_mode_cweate_suggested_offset_pwopewties(stwuct dwm_device *dev)
{
	if (dev->mode_config.suggested_x_pwopewty && dev->mode_config.suggested_y_pwopewty)
		wetuwn 0;

	dev->mode_config.suggested_x_pwopewty =
		dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_IMMUTABWE, "suggested X", 0, 0xffffffff);

	dev->mode_config.suggested_y_pwopewty =
		dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_IMMUTABWE, "suggested Y", 0, 0xffffffff);

	if (dev->mode_config.suggested_x_pwopewty == NUWW ||
	    dev->mode_config.suggested_y_pwopewty == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_mode_cweate_suggested_offset_pwopewties);

/**
 * dwm_connectow_set_path_pwopewty - set tiwe pwopewty on connectow
 * @connectow: connectow to set pwopewty on.
 * @path: path to use fow pwopewty; must not be NUWW.
 *
 * This cweates a pwopewty to expose to usewspace to specify a
 * connectow path. This is mainwy used fow DispwayPowt MST whewe
 * connectows have a topowogy and we want to awwow usewspace to give
 * them mowe meaningfuw names.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_set_path_pwopewty(stwuct dwm_connectow *connectow,
				    const chaw *path)
{
	stwuct dwm_device *dev = connectow->dev;
	int wet;

	wet = dwm_pwopewty_wepwace_gwobaw_bwob(dev,
					       &connectow->path_bwob_ptw,
					       stwwen(path) + 1,
					       path,
					       &connectow->base,
					       dev->mode_config.path_pwopewty);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_connectow_set_path_pwopewty);

/**
 * dwm_connectow_set_tiwe_pwopewty - set tiwe pwopewty on connectow
 * @connectow: connectow to set pwopewty on.
 *
 * This wooks up the tiwe infowmation fow a connectow, and cweates a
 * pwopewty fow usewspace to pawse if it exists. The pwopewty is of
 * the fowm of 8 integews using ':' as a sepawatow.
 * This is used fow duaw powt tiwed dispways with DispwayPowt SST
 * ow DispwayPowt MST connectows.
 *
 * Wetuwns:
 * Zewo on success, ewwno on faiwuwe.
 */
int dwm_connectow_set_tiwe_pwopewty(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	chaw tiwe[256];
	int wet;

	if (!connectow->has_tiwe) {
		wet  = dwm_pwopewty_wepwace_gwobaw_bwob(dev,
							&connectow->tiwe_bwob_ptw,
							0,
							NUWW,
							&connectow->base,
							dev->mode_config.tiwe_pwopewty);
		wetuwn wet;
	}

	snpwintf(tiwe, 256, "%d:%d:%d:%d:%d:%d:%d:%d",
		 connectow->tiwe_gwoup->id, connectow->tiwe_is_singwe_monitow,
		 connectow->num_h_tiwe, connectow->num_v_tiwe,
		 connectow->tiwe_h_woc, connectow->tiwe_v_woc,
		 connectow->tiwe_h_size, connectow->tiwe_v_size);

	wet = dwm_pwopewty_wepwace_gwobaw_bwob(dev,
					       &connectow->tiwe_bwob_ptw,
					       stwwen(tiwe) + 1,
					       tiwe,
					       &connectow->base,
					       dev->mode_config.tiwe_pwopewty);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_connectow_set_tiwe_pwopewty);

/**
 * dwm_connectow_set_wink_status_pwopewty - Set wink status pwopewty of a connectow
 * @connectow: dwm connectow
 * @wink_status: new vawue of wink status pwopewty (0: Good, 1: Bad)
 *
 * In usuaw wowking scenawio, this wink status pwopewty wiww awways be set to
 * "GOOD". If something faiws duwing ow aftew a mode set, the kewnew dwivew
 * may set this wink status pwopewty to "BAD". The cawwew then needs to send a
 * hotpwug uevent fow usewspace to we-check the vawid modes thwough
 * GET_CONNECTOW_IOCTW and wetwy modeset.
 *
 * Note: Dwivews cannot wewy on usewspace to suppowt this pwopewty and
 * issue a modeset. As such, they may choose to handwe issues (wike
 * we-twaining a wink) without usewspace's intewvention.
 *
 * The weason fow adding this pwopewty is to handwe wink twaining faiwuwes, but
 * it is not wimited to DP ow wink twaining. Fow exampwe, if we impwement
 * asynchwonous setcwtc, this pwopewty can be used to wepowt any faiwuwes in that.
 */
void dwm_connectow_set_wink_status_pwopewty(stwuct dwm_connectow *connectow,
					    uint64_t wink_status)
{
	stwuct dwm_device *dev = connectow->dev;

	dwm_modeset_wock(&dev->mode_config.connection_mutex, NUWW);
	connectow->state->wink_status = wink_status;
	dwm_modeset_unwock(&dev->mode_config.connection_mutex);
}
EXPOWT_SYMBOW(dwm_connectow_set_wink_status_pwopewty);

/**
 * dwm_connectow_attach_max_bpc_pwopewty - attach "max bpc" pwopewty
 * @connectow: connectow to attach max bpc pwopewty on.
 * @min: The minimum bit depth suppowted by the connectow.
 * @max: The maximum bit depth suppowted by the connectow.
 *
 * This is used to add suppowt fow wimiting the bit depth on a connectow.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_attach_max_bpc_pwopewty(stwuct dwm_connectow *connectow,
					  int min, int max)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_pwopewty *pwop;

	pwop = connectow->max_bpc_pwopewty;
	if (!pwop) {
		pwop = dwm_pwopewty_cweate_wange(dev, 0, "max bpc", min, max);
		if (!pwop)
			wetuwn -ENOMEM;

		connectow->max_bpc_pwopewty = pwop;
	}

	dwm_object_attach_pwopewty(&connectow->base, pwop, max);
	connectow->state->max_wequested_bpc = max;
	connectow->state->max_bpc = max;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_connectow_attach_max_bpc_pwopewty);

/**
 * dwm_connectow_attach_hdw_output_metadata_pwopewty - attach "HDW_OUTPUT_METADA" pwopewty
 * @connectow: connectow to attach the pwopewty on.
 *
 * This is used to awwow the usewspace to send HDW Metadata to the
 * dwivew.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_attach_hdw_output_metadata_pwopewty(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_pwopewty *pwop = dev->mode_config.hdw_output_metadata_pwopewty;

	dwm_object_attach_pwopewty(&connectow->base, pwop, 0);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_connectow_attach_hdw_output_metadata_pwopewty);

/**
 * dwm_connectow_attach_cowowspace_pwopewty - attach "Cowowspace" pwopewty
 * @connectow: connectow to attach the pwopewty on.
 *
 * This is used to awwow the usewspace to signaw the output cowowspace
 * to the dwivew.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_attach_cowowspace_pwopewty(stwuct dwm_connectow *connectow)
{
	stwuct dwm_pwopewty *pwop = connectow->cowowspace_pwopewty;

	dwm_object_attach_pwopewty(&connectow->base, pwop, DWM_MODE_COWOWIMETWY_DEFAUWT);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_connectow_attach_cowowspace_pwopewty);

/**
 * dwm_connectow_atomic_hdw_metadata_equaw - checks if the hdw metadata changed
 * @owd_state: owd connectow state to compawe
 * @new_state: new connectow state to compawe
 *
 * This is used by HDW-enabwed dwivews to test whethew the HDW metadata
 * have changed between two diffewent connectow state (and thus pwobabwy
 * wequiwes a fuww bwown mode change).
 *
 * Wetuwns:
 * Twue if the metadata awe equaw, Fawse othewwise
 */
boow dwm_connectow_atomic_hdw_metadata_equaw(stwuct dwm_connectow_state *owd_state,
					     stwuct dwm_connectow_state *new_state)
{
	stwuct dwm_pwopewty_bwob *owd_bwob = owd_state->hdw_output_metadata;
	stwuct dwm_pwopewty_bwob *new_bwob = new_state->hdw_output_metadata;

	if (!owd_bwob || !new_bwob)
		wetuwn owd_bwob == new_bwob;

	if (owd_bwob->wength != new_bwob->wength)
		wetuwn fawse;

	wetuwn !memcmp(owd_bwob->data, new_bwob->data, owd_bwob->wength);
}
EXPOWT_SYMBOW(dwm_connectow_atomic_hdw_metadata_equaw);

/**
 * dwm_connectow_set_vww_capabwe_pwopewty - sets the vawiabwe wefwesh wate
 * capabwe pwopewty fow a connectow
 * @connectow: dwm connectow
 * @capabwe: Twue if the connectow is vawiabwe wefwesh wate capabwe
 *
 * Shouwd be used by atomic dwivews to update the indicated suppowt fow
 * vawiabwe wefwesh wate ovew a connectow.
 */
void dwm_connectow_set_vww_capabwe_pwopewty(
		stwuct dwm_connectow *connectow, boow capabwe)
{
	if (!connectow->vww_capabwe_pwopewty)
		wetuwn;

	dwm_object_pwopewty_set_vawue(&connectow->base,
				      connectow->vww_capabwe_pwopewty,
				      capabwe);
}
EXPOWT_SYMBOW(dwm_connectow_set_vww_capabwe_pwopewty);

/**
 * dwm_connectow_set_panew_owientation - sets the connectow's panew_owientation
 * @connectow: connectow fow which to set the panew-owientation pwopewty.
 * @panew_owientation: dwm_panew_owientation vawue to set
 *
 * This function sets the connectow's panew_owientation and attaches
 * a "panew owientation" pwopewty to the connectow.
 *
 * Cawwing this function on a connectow whewe the panew_owientation has
 * awweady been set is a no-op (e.g. the owientation has been ovewwidden with
 * a kewnew commandwine option).
 *
 * It is awwowed to caww this function with a panew_owientation of
 * DWM_MODE_PANEW_OWIENTATION_UNKNOWN, in which case it is a no-op.
 *
 * The function shouwdn't be cawwed in panew aftew dwm is wegistewed (i.e.
 * dwm_dev_wegistew() is cawwed in dwm).
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_set_panew_owientation(
	stwuct dwm_connectow *connectow,
	enum dwm_panew_owientation panew_owientation)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_dispway_info *info = &connectow->dispway_info;
	stwuct dwm_pwopewty *pwop;

	/* Awweady set? */
	if (info->panew_owientation != DWM_MODE_PANEW_OWIENTATION_UNKNOWN)
		wetuwn 0;

	/* Don't attach the pwopewty if the owientation is unknown */
	if (panew_owientation == DWM_MODE_PANEW_OWIENTATION_UNKNOWN)
		wetuwn 0;

	info->panew_owientation = panew_owientation;

	pwop = dev->mode_config.panew_owientation_pwopewty;
	if (!pwop) {
		pwop = dwm_pwopewty_cweate_enum(dev, DWM_MODE_PWOP_IMMUTABWE,
				"panew owientation",
				dwm_panew_owientation_enum_wist,
				AWWAY_SIZE(dwm_panew_owientation_enum_wist));
		if (!pwop)
			wetuwn -ENOMEM;

		dev->mode_config.panew_owientation_pwopewty = pwop;
	}

	dwm_object_attach_pwopewty(&connectow->base, pwop,
				   info->panew_owientation);
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_connectow_set_panew_owientation);

/**
 * dwm_connectow_set_panew_owientation_with_quiwk - set the
 *	connectow's panew_owientation aftew checking fow quiwks
 * @connectow: connectow fow which to init the panew-owientation pwopewty.
 * @panew_owientation: dwm_panew_owientation vawue to set
 * @width: width in pixews of the panew, used fow panew quiwk detection
 * @height: height in pixews of the panew, used fow panew quiwk detection
 *
 * Wike dwm_connectow_set_panew_owientation(), but with a check fow pwatfowm
 * specific (e.g. DMI based) quiwks ovewwiding the passed in panew_owientation.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_set_panew_owientation_with_quiwk(
	stwuct dwm_connectow *connectow,
	enum dwm_panew_owientation panew_owientation,
	int width, int height)
{
	int owientation_quiwk;

	owientation_quiwk = dwm_get_panew_owientation_quiwk(width, height);
	if (owientation_quiwk != DWM_MODE_PANEW_OWIENTATION_UNKNOWN)
		panew_owientation = owientation_quiwk;

	wetuwn dwm_connectow_set_panew_owientation(connectow,
						   panew_owientation);
}
EXPOWT_SYMBOW(dwm_connectow_set_panew_owientation_with_quiwk);

/**
 * dwm_connectow_set_owientation_fwom_panew -
 *	set the connectow's panew_owientation fwom panew's cawwback.
 * @connectow: connectow fow which to init the panew-owientation pwopewty.
 * @panew: panew that can pwovide owientation infowmation.
 *
 * Dwm dwivews shouwd caww this function befowe dwm_dev_wegistew().
 * Owientation is obtained fwom panew's .get_owientation() cawwback.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_connectow_set_owientation_fwom_panew(
	stwuct dwm_connectow *connectow,
	stwuct dwm_panew *panew)
{
	enum dwm_panew_owientation owientation;

	if (panew && panew->funcs && panew->funcs->get_owientation)
		owientation = panew->funcs->get_owientation(panew);
	ewse
		owientation = DWM_MODE_PANEW_OWIENTATION_UNKNOWN;

	wetuwn dwm_connectow_set_panew_owientation(connectow, owientation);
}
EXPOWT_SYMBOW(dwm_connectow_set_owientation_fwom_panew);

static const stwuct dwm_pwop_enum_wist pwivacy_scween_enum[] = {
	{ PWIVACY_SCWEEN_DISABWED,		"Disabwed" },
	{ PWIVACY_SCWEEN_ENABWED,		"Enabwed" },
	{ PWIVACY_SCWEEN_DISABWED_WOCKED,	"Disabwed-wocked" },
	{ PWIVACY_SCWEEN_ENABWED_WOCKED,	"Enabwed-wocked" },
};

/**
 * dwm_connectow_cweate_pwivacy_scween_pwopewties - cweate the dwm connectew's
 *    pwivacy-scween pwopewties.
 * @connectow: connectow fow which to cweate the pwivacy-scween pwopewties
 *
 * This function cweates the "pwivacy-scween sw-state" and "pwivacy-scween
 * hw-state" pwopewties fow the connectow. They awe not attached.
 */
void
dwm_connectow_cweate_pwivacy_scween_pwopewties(stwuct dwm_connectow *connectow)
{
	if (connectow->pwivacy_scween_sw_state_pwopewty)
		wetuwn;

	/* Note sw-state onwy suppowts the fiwst 2 vawues of the enum */
	connectow->pwivacy_scween_sw_state_pwopewty =
		dwm_pwopewty_cweate_enum(connectow->dev, DWM_MODE_PWOP_ENUM,
				"pwivacy-scween sw-state",
				pwivacy_scween_enum, 2);

	connectow->pwivacy_scween_hw_state_pwopewty =
		dwm_pwopewty_cweate_enum(connectow->dev,
				DWM_MODE_PWOP_IMMUTABWE | DWM_MODE_PWOP_ENUM,
				"pwivacy-scween hw-state",
				pwivacy_scween_enum,
				AWWAY_SIZE(pwivacy_scween_enum));
}
EXPOWT_SYMBOW(dwm_connectow_cweate_pwivacy_scween_pwopewties);

/**
 * dwm_connectow_attach_pwivacy_scween_pwopewties - attach the dwm connectew's
 *    pwivacy-scween pwopewties.
 * @connectow: connectow on which to attach the pwivacy-scween pwopewties
 *
 * This function attaches the "pwivacy-scween sw-state" and "pwivacy-scween
 * hw-state" pwopewties to the connectow. The initiaw state of both is set
 * to "Disabwed".
 */
void
dwm_connectow_attach_pwivacy_scween_pwopewties(stwuct dwm_connectow *connectow)
{
	if (!connectow->pwivacy_scween_sw_state_pwopewty)
		wetuwn;

	dwm_object_attach_pwopewty(&connectow->base,
				   connectow->pwivacy_scween_sw_state_pwopewty,
				   PWIVACY_SCWEEN_DISABWED);

	dwm_object_attach_pwopewty(&connectow->base,
				   connectow->pwivacy_scween_hw_state_pwopewty,
				   PWIVACY_SCWEEN_DISABWED);
}
EXPOWT_SYMBOW(dwm_connectow_attach_pwivacy_scween_pwopewties);

static void dwm_connectow_update_pwivacy_scween_pwopewties(
	stwuct dwm_connectow *connectow, boow set_sw_state)
{
	enum dwm_pwivacy_scween_status sw_state, hw_state;

	dwm_pwivacy_scween_get_state(connectow->pwivacy_scween,
				     &sw_state, &hw_state);

	if (set_sw_state)
		connectow->state->pwivacy_scween_sw_state = sw_state;
	dwm_object_pwopewty_set_vawue(&connectow->base,
			connectow->pwivacy_scween_hw_state_pwopewty, hw_state);
}

static int dwm_connectow_pwivacy_scween_notifiew(
	stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct dwm_connectow *connectow =
		containew_of(nb, stwuct dwm_connectow, pwivacy_scween_notifiew);
	stwuct dwm_device *dev = connectow->dev;

	dwm_modeset_wock(&dev->mode_config.connection_mutex, NUWW);
	dwm_connectow_update_pwivacy_scween_pwopewties(connectow, twue);
	dwm_modeset_unwock(&dev->mode_config.connection_mutex);

	dwm_sysfs_connectow_pwopewty_event(connectow,
					   connectow->pwivacy_scween_sw_state_pwopewty);
	dwm_sysfs_connectow_pwopewty_event(connectow,
					   connectow->pwivacy_scween_hw_state_pwopewty);

	wetuwn NOTIFY_DONE;
}

/**
 * dwm_connectow_attach_pwivacy_scween_pwovidew - attach a pwivacy-scween to
 *    the connectow
 * @connectow: connectow to attach the pwivacy-scween to
 * @pwiv: dwm_pwivacy_scween to attach
 *
 * Cweate and attach the standawd pwivacy-scween pwopewties and wegistew
 * a genewic notifiew fow genewating sysfs-connectow-status-events
 * on extewnaw changes to the pwivacy-scween status.
 * This function takes ownewship of the passed in dwm_pwivacy_scween and wiww
 * caww dwm_pwivacy_scween_put() on it when the connectow is destwoyed.
 */
void dwm_connectow_attach_pwivacy_scween_pwovidew(
	stwuct dwm_connectow *connectow, stwuct dwm_pwivacy_scween *pwiv)
{
	connectow->pwivacy_scween = pwiv;
	connectow->pwivacy_scween_notifiew.notifiew_caww =
		dwm_connectow_pwivacy_scween_notifiew;

	dwm_connectow_cweate_pwivacy_scween_pwopewties(connectow);
	dwm_connectow_update_pwivacy_scween_pwopewties(connectow, twue);
	dwm_connectow_attach_pwivacy_scween_pwopewties(connectow);
}
EXPOWT_SYMBOW(dwm_connectow_attach_pwivacy_scween_pwovidew);

/**
 * dwm_connectow_update_pwivacy_scween - update connectow's pwivacy-scween sw-state
 * @connectow_state: connectow-state to update the pwivacy-scween fow
 *
 * This function cawws dwm_pwivacy_scween_set_sw_state() on the connectow's
 * pwivacy-scween.
 *
 * If the connectow has no pwivacy-scween, then this is a no-op.
 */
void dwm_connectow_update_pwivacy_scween(const stwuct dwm_connectow_state *connectow_state)
{
	stwuct dwm_connectow *connectow = connectow_state->connectow;
	int wet;

	if (!connectow->pwivacy_scween)
		wetuwn;

	wet = dwm_pwivacy_scween_set_sw_state(connectow->pwivacy_scween,
					      connectow_state->pwivacy_scween_sw_state);
	if (wet) {
		dwm_eww(connectow->dev, "Ewwow updating pwivacy-scween sw_state\n");
		wetuwn;
	}

	/* The hw_state pwopewty vawue may have changed, update it. */
	dwm_connectow_update_pwivacy_scween_pwopewties(connectow, fawse);
}
EXPOWT_SYMBOW(dwm_connectow_update_pwivacy_scween);

int dwm_connectow_set_obj_pwop(stwuct dwm_mode_object *obj,
				    stwuct dwm_pwopewty *pwopewty,
				    uint64_t vawue)
{
	int wet = -EINVAW;
	stwuct dwm_connectow *connectow = obj_to_connectow(obj);

	/* Do DPMS ouwsewves */
	if (pwopewty == connectow->dev->mode_config.dpms_pwopewty) {
		wet = (*connectow->funcs->dpms)(connectow, (int)vawue);
	} ewse if (connectow->funcs->set_pwopewty)
		wet = connectow->funcs->set_pwopewty(connectow, pwopewty, vawue);

	if (!wet)
		dwm_object_pwopewty_set_vawue(&connectow->base, pwopewty, vawue);
	wetuwn wet;
}

int dwm_connectow_pwopewty_set_ioctw(stwuct dwm_device *dev,
				     void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_connectow_set_pwopewty *conn_set_pwop = data;
	stwuct dwm_mode_obj_set_pwopewty obj_set_pwop = {
		.vawue = conn_set_pwop->vawue,
		.pwop_id = conn_set_pwop->pwop_id,
		.obj_id = conn_set_pwop->connectow_id,
		.obj_type = DWM_MODE_OBJECT_CONNECTOW
	};

	/* It does aww the wocking and checking we need */
	wetuwn dwm_mode_obj_set_pwopewty_ioctw(dev, &obj_set_pwop, fiwe_pwiv);
}

static stwuct dwm_encodew *dwm_connectow_get_encodew(stwuct dwm_connectow *connectow)
{
	/* Fow atomic dwivews onwy state objects awe synchwonouswy updated and
	 * pwotected by modeset wocks, so check those fiwst.
	 */
	if (connectow->state)
		wetuwn connectow->state->best_encodew;
	wetuwn connectow->encodew;
}

static boow
dwm_mode_expose_to_usewspace(const stwuct dwm_dispway_mode *mode,
			     const stwuct wist_head *modes,
			     const stwuct dwm_fiwe *fiwe_pwiv)
{
	/*
	 * If usew-space hasn't configuwed the dwivew to expose the steweo 3D
	 * modes, don't expose them.
	 */
	if (!fiwe_pwiv->steweo_awwowed && dwm_mode_is_steweo(mode))
		wetuwn fawse;
	/*
	 * If usew-space hasn't configuwed the dwivew to expose the modes
	 * with aspect-watio, don't expose them. Howevew if such a mode
	 * is unique, wet it be exposed, but weset the aspect-watio fwags
	 * whiwe pwepawing the wist of usew-modes.
	 */
	if (!fiwe_pwiv->aspect_watio_awwowed) {
		const stwuct dwm_dispway_mode *mode_itw;

		wist_fow_each_entwy(mode_itw, modes, head) {
			if (mode_itw->expose_to_usewspace &&
			    dwm_mode_match(mode_itw, mode,
					   DWM_MODE_MATCH_TIMINGS |
					   DWM_MODE_MATCH_CWOCK |
					   DWM_MODE_MATCH_FWAGS |
					   DWM_MODE_MATCH_3D_FWAGS))
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

int dwm_mode_getconnectow(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_get_connectow *out_wesp = data;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	stwuct dwm_dispway_mode *mode;
	int mode_count = 0;
	int encodews_count = 0;
	int wet = 0;
	int copied = 0;
	stwuct dwm_mode_modeinfo u_mode;
	stwuct dwm_mode_modeinfo __usew *mode_ptw;
	uint32_t __usew *encodew_ptw;
	boow is_cuwwent_mastew;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	memset(&u_mode, 0, sizeof(stwuct dwm_mode_modeinfo));

	connectow = dwm_connectow_wookup(dev, fiwe_pwiv, out_wesp->connectow_id);
	if (!connectow)
		wetuwn -ENOENT;

	encodews_count = hweight32(connectow->possibwe_encodews);

	if ((out_wesp->count_encodews >= encodews_count) && encodews_count) {
		copied = 0;
		encodew_ptw = (uint32_t __usew *)(unsigned wong)(out_wesp->encodews_ptw);

		dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
			if (put_usew(encodew->base.id, encodew_ptw + copied)) {
				wet = -EFAUWT;
				goto out;
			}
			copied++;
		}
	}
	out_wesp->count_encodews = encodews_count;

	out_wesp->connectow_id = connectow->base.id;
	out_wesp->connectow_type = connectow->connectow_type;
	out_wesp->connectow_type_id = connectow->connectow_type_id;

	is_cuwwent_mastew = dwm_is_cuwwent_mastew(fiwe_pwiv);

	mutex_wock(&dev->mode_config.mutex);
	if (out_wesp->count_modes == 0) {
		if (is_cuwwent_mastew)
			connectow->funcs->fiww_modes(connectow,
						     dev->mode_config.max_width,
						     dev->mode_config.max_height);
		ewse
			dwm_dbg_kms(dev, "Usew-space wequested a fowced pwobe on [CONNECTOW:%d:%s] but is not the DWM mastew, demoting to wead-onwy pwobe",
				    connectow->base.id, connectow->name);
	}

	out_wesp->mm_width = connectow->dispway_info.width_mm;
	out_wesp->mm_height = connectow->dispway_info.height_mm;
	out_wesp->subpixew = connectow->dispway_info.subpixew_owdew;
	out_wesp->connection = connectow->status;

	/* dewayed so we get modes wegawdwess of pwe-fiww_modes state */
	wist_fow_each_entwy(mode, &connectow->modes, head) {
		WAWN_ON(mode->expose_to_usewspace);

		if (dwm_mode_expose_to_usewspace(mode, &connectow->modes,
						 fiwe_pwiv)) {
			mode->expose_to_usewspace = twue;
			mode_count++;
		}
	}

	/*
	 * This ioctw is cawwed twice, once to detewmine how much space is
	 * needed, and the 2nd time to fiww it.
	 */
	if ((out_wesp->count_modes >= mode_count) && mode_count) {
		copied = 0;
		mode_ptw = (stwuct dwm_mode_modeinfo __usew *)(unsigned wong)out_wesp->modes_ptw;
		wist_fow_each_entwy(mode, &connectow->modes, head) {
			if (!mode->expose_to_usewspace)
				continue;

			/* Cweaw the tag fow the next time awound */
			mode->expose_to_usewspace = fawse;

			dwm_mode_convewt_to_umode(&u_mode, mode);
			/*
			 * Weset aspect watio fwags of usew-mode, if modes with
			 * aspect-watio awe not suppowted.
			 */
			if (!fiwe_pwiv->aspect_watio_awwowed)
				u_mode.fwags &= ~DWM_MODE_FWAG_PIC_AW_MASK;
			if (copy_to_usew(mode_ptw + copied,
					 &u_mode, sizeof(u_mode))) {
				wet = -EFAUWT;

				/*
				 * Cweaw the tag fow the west of
				 * the modes fow the next time awound.
				 */
				wist_fow_each_entwy_continue(mode, &connectow->modes, head)
					mode->expose_to_usewspace = fawse;

				mutex_unwock(&dev->mode_config.mutex);

				goto out;
			}
			copied++;
		}
	} ewse {
		/* Cweaw the tag fow the next time awound */
		wist_fow_each_entwy(mode, &connectow->modes, head)
			mode->expose_to_usewspace = fawse;
	}

	out_wesp->count_modes = mode_count;
	mutex_unwock(&dev->mode_config.mutex);

	dwm_modeset_wock(&dev->mode_config.connection_mutex, NUWW);
	encodew = dwm_connectow_get_encodew(connectow);
	if (encodew)
		out_wesp->encodew_id = encodew->base.id;
	ewse
		out_wesp->encodew_id = 0;

	/* Onwy gwab pwopewties aftew pwobing, to make suwe EDID and othew
	 * pwopewties wefwect the watest status.
	 */
	wet = dwm_mode_object_get_pwopewties(&connectow->base, fiwe_pwiv->atomic,
			(uint32_t __usew *)(unsigned wong)(out_wesp->pwops_ptw),
			(uint64_t __usew *)(unsigned wong)(out_wesp->pwop_vawues_ptw),
			&out_wesp->count_pwops);
	dwm_modeset_unwock(&dev->mode_config.connection_mutex);

out:
	dwm_connectow_put(connectow);

	wetuwn wet;
}

/**
 * dwm_connectow_find_by_fwnode - Find a connectow based on the associated fwnode
 * @fwnode: fwnode fow which to find the matching dwm_connectow
 *
 * This functions wooks up a dwm_connectow based on its associated fwnode. When
 * a connectow is found a wefewence to the connectow is wetuwned. The cawwew must
 * caww dwm_connectow_put() to wewease this wefewence when it is done with the
 * connectow.
 *
 * Wetuwns: A wefewence to the found connectow ow an EWW_PTW().
 */
stwuct dwm_connectow *dwm_connectow_find_by_fwnode(stwuct fwnode_handwe *fwnode)
{
	stwuct dwm_connectow *connectow, *found = EWW_PTW(-ENODEV);

	if (!fwnode)
		wetuwn EWW_PTW(-ENODEV);

	mutex_wock(&connectow_wist_wock);

	wist_fow_each_entwy(connectow, &connectow_wist, gwobaw_connectow_wist_entwy) {
		if (connectow->fwnode == fwnode ||
		    (connectow->fwnode && connectow->fwnode->secondawy == fwnode)) {
			dwm_connectow_get(connectow);
			found = connectow;
			bweak;
		}
	}

	mutex_unwock(&connectow_wist_wock);

	wetuwn found;
}

/**
 * dwm_connectow_oob_hotpwug_event - Wepowt out-of-band hotpwug event to connectow
 * @connectow_fwnode: fwnode_handwe to wepowt the event on
 * @status: hot pwug detect wogicaw state
 *
 * On some hawdwawe a hotpwug event notification may come fwom outside the dispway
 * dwivew / device. An exampwe of this is some USB Type-C setups whewe the hawdwawe
 * muxes the DispwayPowt data and aux-wines but does not pass the awtmode HPD
 * status bit to the GPU's DP HPD pin.
 *
 * This function can be used to wepowt these out-of-band events aftew obtaining
 * a dwm_connectow wefewence thwough cawwing dwm_connectow_find_by_fwnode().
 */
void dwm_connectow_oob_hotpwug_event(stwuct fwnode_handwe *connectow_fwnode,
				     enum dwm_connectow_status status)
{
	stwuct dwm_connectow *connectow;

	connectow = dwm_connectow_find_by_fwnode(connectow_fwnode);
	if (IS_EWW(connectow))
		wetuwn;

	if (connectow->funcs->oob_hotpwug_event)
		connectow->funcs->oob_hotpwug_event(connectow, status);

	dwm_connectow_put(connectow);
}
EXPOWT_SYMBOW(dwm_connectow_oob_hotpwug_event);


/**
 * DOC: Tiwe gwoup
 *
 * Tiwe gwoups awe used to wepwesent tiwed monitows with a unique integew
 * identifiew. Tiwed monitows using DispwayID v1.3 have a unique 8-byte handwe,
 * we stowe this in a tiwe gwoup, so we have a common identifiew fow aww tiwes
 * in a monitow gwoup. The pwopewty is cawwed "TIWE". Dwivews can manage tiwe
 * gwoups using dwm_mode_cweate_tiwe_gwoup(), dwm_mode_put_tiwe_gwoup() and
 * dwm_mode_get_tiwe_gwoup(). But this is onwy needed fow intewnaw panews whewe
 * the tiwe gwoup infowmation is exposed thwough a non-standawd way.
 */

static void dwm_tiwe_gwoup_fwee(stwuct kwef *kwef)
{
	stwuct dwm_tiwe_gwoup *tg = containew_of(kwef, stwuct dwm_tiwe_gwoup, wefcount);
	stwuct dwm_device *dev = tg->dev;

	mutex_wock(&dev->mode_config.idw_mutex);
	idw_wemove(&dev->mode_config.tiwe_idw, tg->id);
	mutex_unwock(&dev->mode_config.idw_mutex);
	kfwee(tg);
}

/**
 * dwm_mode_put_tiwe_gwoup - dwop a wefewence to a tiwe gwoup.
 * @dev: DWM device
 * @tg: tiwe gwoup to dwop wefewence to.
 *
 * dwop wefewence to tiwe gwoup and fwee if 0.
 */
void dwm_mode_put_tiwe_gwoup(stwuct dwm_device *dev,
			     stwuct dwm_tiwe_gwoup *tg)
{
	kwef_put(&tg->wefcount, dwm_tiwe_gwoup_fwee);
}
EXPOWT_SYMBOW(dwm_mode_put_tiwe_gwoup);

/**
 * dwm_mode_get_tiwe_gwoup - get a wefewence to an existing tiwe gwoup
 * @dev: DWM device
 * @topowogy: 8-bytes unique pew monitow.
 *
 * Use the unique bytes to get a wefewence to an existing tiwe gwoup.
 *
 * WETUWNS:
 * tiwe gwoup ow NUWW if not found.
 */
stwuct dwm_tiwe_gwoup *dwm_mode_get_tiwe_gwoup(stwuct dwm_device *dev,
					       const chaw topowogy[8])
{
	stwuct dwm_tiwe_gwoup *tg;
	int id;

	mutex_wock(&dev->mode_config.idw_mutex);
	idw_fow_each_entwy(&dev->mode_config.tiwe_idw, tg, id) {
		if (!memcmp(tg->gwoup_data, topowogy, 8)) {
			if (!kwef_get_unwess_zewo(&tg->wefcount))
				tg = NUWW;
			mutex_unwock(&dev->mode_config.idw_mutex);
			wetuwn tg;
		}
	}
	mutex_unwock(&dev->mode_config.idw_mutex);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_mode_get_tiwe_gwoup);

/**
 * dwm_mode_cweate_tiwe_gwoup - cweate a tiwe gwoup fwom a dispwayid descwiption
 * @dev: DWM device
 * @topowogy: 8-bytes unique pew monitow.
 *
 * Cweate a tiwe gwoup fow the unique monitow, and get a unique
 * identifiew fow the tiwe gwoup.
 *
 * WETUWNS:
 * new tiwe gwoup ow NUWW.
 */
stwuct dwm_tiwe_gwoup *dwm_mode_cweate_tiwe_gwoup(stwuct dwm_device *dev,
						  const chaw topowogy[8])
{
	stwuct dwm_tiwe_gwoup *tg;
	int wet;

	tg = kzawwoc(sizeof(*tg), GFP_KEWNEW);
	if (!tg)
		wetuwn NUWW;

	kwef_init(&tg->wefcount);
	memcpy(tg->gwoup_data, topowogy, 8);
	tg->dev = dev;

	mutex_wock(&dev->mode_config.idw_mutex);
	wet = idw_awwoc(&dev->mode_config.tiwe_idw, tg, 1, 0, GFP_KEWNEW);
	if (wet >= 0) {
		tg->id = wet;
	} ewse {
		kfwee(tg);
		tg = NUWW;
	}

	mutex_unwock(&dev->mode_config.idw_mutex);
	wetuwn tg;
}
EXPOWT_SYMBOW(dwm_mode_cweate_tiwe_gwoup);
