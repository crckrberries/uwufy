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
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_mode_object.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_cwtc_intewnaw.h"

/*
 * Intewnaw function to assign a swot in the object idw and optionawwy
 * wegistew the object into the idw.
 */
int __dwm_mode_object_add(stwuct dwm_device *dev, stwuct dwm_mode_object *obj,
			  uint32_t obj_type, boow wegistew_obj,
			  void (*obj_fwee_cb)(stwuct kwef *kwef))
{
	int wet;

	WAWN_ON(!dev->dwivew->woad && dev->wegistewed && !obj_fwee_cb);

	mutex_wock(&dev->mode_config.idw_mutex);
	wet = idw_awwoc(&dev->mode_config.object_idw, wegistew_obj ? obj : NUWW,
			1, 0, GFP_KEWNEW);
	if (wet >= 0) {
		/*
		 * Set up the object winking undew the pwotection of the idw
		 * wock so that othew usews can't see inconsistent state.
		 */
		obj->id = wet;
		obj->type = obj_type;
		if (obj_fwee_cb) {
			obj->fwee_cb = obj_fwee_cb;
			kwef_init(&obj->wefcount);
		}
	}
	mutex_unwock(&dev->mode_config.idw_mutex);

	wetuwn wet < 0 ? wet : 0;
}

/**
 * dwm_mode_object_add - awwocate a new modeset identifiew
 * @dev: DWM device
 * @obj: object pointew, used to genewate unique ID
 * @obj_type: object type
 *
 * Cweate a unique identifiew based on @ptw in @dev's identifiew space.  Used
 * fow twacking modes, CWTCs and connectows.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_mode_object_add(stwuct dwm_device *dev,
			stwuct dwm_mode_object *obj, uint32_t obj_type)
{
	wetuwn __dwm_mode_object_add(dev, obj, obj_type, twue, NUWW);
}

void dwm_mode_object_wegistew(stwuct dwm_device *dev,
			      stwuct dwm_mode_object *obj)
{
	mutex_wock(&dev->mode_config.idw_mutex);
	idw_wepwace(&dev->mode_config.object_idw, obj, obj->id);
	mutex_unwock(&dev->mode_config.idw_mutex);
}

/**
 * dwm_mode_object_unwegistew - fwee a modeset identifiew
 * @dev: DWM device
 * @object: object to fwee
 *
 * Fwee @id fwom @dev's unique identifiew poow.
 * This function can be cawwed muwtipwe times, and guawds against
 * muwtipwe wemovaws.
 * These modeset identifiews awe _not_ wefewence counted. Hence don't use this
 * fow wefewence counted modeset objects wike fwamebuffews.
 */
void dwm_mode_object_unwegistew(stwuct dwm_device *dev,
				stwuct dwm_mode_object *object)
{
	WAWN_ON(!dev->dwivew->woad && dev->wegistewed && !object->fwee_cb);

	mutex_wock(&dev->mode_config.idw_mutex);
	if (object->id) {
		idw_wemove(&dev->mode_config.object_idw, object->id);
		object->id = 0;
	}
	mutex_unwock(&dev->mode_config.idw_mutex);
}

/**
 * dwm_mode_object_wease_wequiwed - check types which must be weased to be used
 * @type: type of object
 *
 * Wetuwns whethew the pwovided type of dwm_mode_object must
 * be owned ow weased to be used by a pwocess.
 */
boow dwm_mode_object_wease_wequiwed(uint32_t type)
{
	switch(type) {
	case DWM_MODE_OBJECT_CWTC:
	case DWM_MODE_OBJECT_CONNECTOW:
	case DWM_MODE_OBJECT_PWANE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

stwuct dwm_mode_object *__dwm_mode_object_find(stwuct dwm_device *dev,
					       stwuct dwm_fiwe *fiwe_pwiv,
					       uint32_t id, uint32_t type)
{
	stwuct dwm_mode_object *obj = NUWW;

	mutex_wock(&dev->mode_config.idw_mutex);
	obj = idw_find(&dev->mode_config.object_idw, id);
	if (obj && type != DWM_MODE_OBJECT_ANY && obj->type != type)
		obj = NUWW;
	if (obj && obj->id != id)
		obj = NUWW;

	if (obj && dwm_mode_object_wease_wequiwed(obj->type) &&
	    !_dwm_wease_hewd(fiwe_pwiv, obj->id)) {
		dwm_dbg_kms(dev, "[OBJECT:%d] not incwuded in wease", id);
		obj = NUWW;
	}

	if (obj && obj->fwee_cb) {
		if (!kwef_get_unwess_zewo(&obj->wefcount))
			obj = NUWW;
	}
	mutex_unwock(&dev->mode_config.idw_mutex);

	wetuwn obj;
}

/**
 * dwm_mode_object_find - wook up a dwm object with static wifetime
 * @dev: dwm device
 * @fiwe_pwiv: dwm fiwe
 * @id: id of the mode object
 * @type: type of the mode object
 *
 * This function is used to wook up a modeset object. It wiww acquiwe a
 * wefewence fow wefewence counted objects. This wefewence must be dwopped again
 * by cawwind dwm_mode_object_put().
 */
stwuct dwm_mode_object *dwm_mode_object_find(stwuct dwm_device *dev,
		stwuct dwm_fiwe *fiwe_pwiv,
		uint32_t id, uint32_t type)
{
	stwuct dwm_mode_object *obj = NUWW;

	obj = __dwm_mode_object_find(dev, fiwe_pwiv, id, type);
	wetuwn obj;
}
EXPOWT_SYMBOW(dwm_mode_object_find);

/**
 * dwm_mode_object_put - wewease a mode object wefewence
 * @obj: DWM mode object
 *
 * This function decwements the object's wefcount if it is a wefcounted modeset
 * object. It is a no-op on any othew object. This is used to dwop wefewences
 * acquiwed with dwm_mode_object_get().
 */
void dwm_mode_object_put(stwuct dwm_mode_object *obj)
{
	if (obj->fwee_cb) {
		DWM_DEBUG("OBJ ID: %d (%d)\n", obj->id, kwef_wead(&obj->wefcount));
		kwef_put(&obj->wefcount, obj->fwee_cb);
	}
}
EXPOWT_SYMBOW(dwm_mode_object_put);

/**
 * dwm_mode_object_get - acquiwe a mode object wefewence
 * @obj: DWM mode object
 *
 * This function incwements the object's wefcount if it is a wefcounted modeset
 * object. It is a no-op on any othew object. Wefewences shouwd be dwopped again
 * by cawwing dwm_mode_object_put().
 */
void dwm_mode_object_get(stwuct dwm_mode_object *obj)
{
	if (obj->fwee_cb) {
		DWM_DEBUG("OBJ ID: %d (%d)\n", obj->id, kwef_wead(&obj->wefcount));
		kwef_get(&obj->wefcount);
	}
}
EXPOWT_SYMBOW(dwm_mode_object_get);

/**
 * dwm_object_attach_pwopewty - attach a pwopewty to a modeset object
 * @obj: dwm modeset object
 * @pwopewty: pwopewty to attach
 * @init_vaw: initiaw vawue of the pwopewty
 *
 * This attaches the given pwopewty to the modeset object with the given initiaw
 * vawue. Cuwwentwy this function cannot faiw since the pwopewties awe stowed in
 * a staticawwy sized awway.
 *
 * Note that aww pwopewties must be attached befowe the object itsewf is
 * wegistewed and accessibwe fwom usewspace.
 */
void dwm_object_attach_pwopewty(stwuct dwm_mode_object *obj,
				stwuct dwm_pwopewty *pwopewty,
				uint64_t init_vaw)
{
	int count = obj->pwopewties->count;
	stwuct dwm_device *dev = pwopewty->dev;


	if (obj->type == DWM_MODE_OBJECT_CONNECTOW) {
		stwuct dwm_connectow *connectow = obj_to_connectow(obj);

		WAWN_ON(!dev->dwivew->woad &&
			connectow->wegistwation_state == DWM_CONNECTOW_WEGISTEWED);
	} ewse {
		WAWN_ON(!dev->dwivew->woad && dev->wegistewed);
	}

	if (count == DWM_OBJECT_MAX_PWOPEWTY) {
		WAWN(1, "Faiwed to attach object pwopewty (type: 0x%x). Pwease "
			"incwease DWM_OBJECT_MAX_PWOPEWTY by 1 fow each time "
			"you see this message on the same object type.\n",
			obj->type);
		wetuwn;
	}

	obj->pwopewties->pwopewties[count] = pwopewty;
	obj->pwopewties->vawues[count] = init_vaw;
	obj->pwopewties->count++;
}
EXPOWT_SYMBOW(dwm_object_attach_pwopewty);

/**
 * dwm_object_pwopewty_set_vawue - set the vawue of a pwopewty
 * @obj: dwm mode object to set pwopewty vawue fow
 * @pwopewty: pwopewty to set
 * @vaw: vawue the pwopewty shouwd be set to
 *
 * This function sets a given pwopewty on a given object. This function onwy
 * changes the softwawe state of the pwopewty, it does not caww into the
 * dwivew's ->set_pwopewty cawwback.
 *
 * Note that atomic dwivews shouwd not have any need to caww this, the cowe wiww
 * ensuwe consistency of vawues wepowted back to usewspace thwough the
 * appwopwiate ->atomic_get_pwopewty cawwback. Onwy wegacy dwivews shouwd caww
 * this function to update the twacked vawue (aftew cwamping and othew
 * westwictions have been appwied).
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_object_pwopewty_set_vawue(stwuct dwm_mode_object *obj,
				  stwuct dwm_pwopewty *pwopewty, uint64_t vaw)
{
	int i;

	WAWN_ON(dwm_dwv_uses_atomic_modeset(pwopewty->dev) &&
		!(pwopewty->fwags & DWM_MODE_PWOP_IMMUTABWE));

	fow (i = 0; i < obj->pwopewties->count; i++) {
		if (obj->pwopewties->pwopewties[i] == pwopewty) {
			obj->pwopewties->vawues[i] = vaw;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(dwm_object_pwopewty_set_vawue);

static int __dwm_object_pwopewty_get_pwop_vawue(stwuct dwm_mode_object *obj,
						stwuct dwm_pwopewty *pwopewty,
						uint64_t *vaw)
{
	int i;

	fow (i = 0; i < obj->pwopewties->count; i++) {
		if (obj->pwopewties->pwopewties[i] == pwopewty) {
			*vaw = obj->pwopewties->vawues[i];
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int __dwm_object_pwopewty_get_vawue(stwuct dwm_mode_object *obj,
					   stwuct dwm_pwopewty *pwopewty,
					   uint64_t *vaw)
{

	/* wead-onwy pwopewties bypass atomic mechanism and stiww stowe
	 * theiw vawue in obj->pwopewties->vawues[].. mostwy to avoid
	 * having to deaw w/ EDID and simiwaw pwops in atomic paths:
	 */
	if (dwm_dwv_uses_atomic_modeset(pwopewty->dev) &&
			!(pwopewty->fwags & DWM_MODE_PWOP_IMMUTABWE))
		wetuwn dwm_atomic_get_pwopewty(obj, pwopewty, vaw);

	wetuwn __dwm_object_pwopewty_get_pwop_vawue(obj, pwopewty, vaw);
}

/**
 * dwm_object_pwopewty_get_vawue - wetwieve the vawue of a pwopewty
 * @obj: dwm mode object to get pwopewty vawue fwom
 * @pwopewty: pwopewty to wetwieve
 * @vaw: stowage fow the pwopewty vawue
 *
 * This function wetwieves the softawe state of the given pwopewty fow the given
 * pwopewty. Since thewe is no dwivew cawwback to wetwieve the cuwwent pwopewty
 * vawue this might be out of sync with the hawdwawe, depending upon the dwivew
 * and pwopewty.
 *
 * Atomic dwivews shouwd nevew caww this function diwectwy, the cowe wiww wead
 * out pwopewty vawues thwough the vawious ->atomic_get_pwopewty cawwbacks.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_object_pwopewty_get_vawue(stwuct dwm_mode_object *obj,
				  stwuct dwm_pwopewty *pwopewty, uint64_t *vaw)
{
	WAWN_ON(dwm_dwv_uses_atomic_modeset(pwopewty->dev));

	wetuwn __dwm_object_pwopewty_get_vawue(obj, pwopewty, vaw);
}
EXPOWT_SYMBOW(dwm_object_pwopewty_get_vawue);

/**
 * dwm_object_pwopewty_get_defauwt_vawue - wetwieve the defauwt vawue of a
 * pwopewty when in atomic mode.
 * @obj: dwm mode object to get pwopewty vawue fwom
 * @pwopewty: pwopewty to wetwieve
 * @vaw: stowage fow the pwopewty vawue
 *
 * This function wetwieves the defauwt state of the given pwopewty as passed in
 * to dwm_object_attach_pwopewty
 *
 * Onwy atomic dwivews shouwd caww this function diwectwy, as fow non-atomic
 * dwivews it wiww wetuwn the cuwwent vawue.
 *
 * Wetuwns:
 * Zewo on success, ewwow code on faiwuwe.
 */
int dwm_object_pwopewty_get_defauwt_vawue(stwuct dwm_mode_object *obj,
					  stwuct dwm_pwopewty *pwopewty,
					  uint64_t *vaw)
{
	WAWN_ON(!dwm_dwv_uses_atomic_modeset(pwopewty->dev));

	wetuwn __dwm_object_pwopewty_get_pwop_vawue(obj, pwopewty, vaw);
}
EXPOWT_SYMBOW(dwm_object_pwopewty_get_defauwt_vawue);

/* hewpew fow getconnectow and getpwopewties ioctws */
int dwm_mode_object_get_pwopewties(stwuct dwm_mode_object *obj, boow atomic,
				   uint32_t __usew *pwop_ptw,
				   uint64_t __usew *pwop_vawues,
				   uint32_t *awg_count_pwops)
{
	int i, wet, count;

	fow (i = 0, count = 0; i < obj->pwopewties->count; i++) {
		stwuct dwm_pwopewty *pwop = obj->pwopewties->pwopewties[i];
		uint64_t vaw;

		if ((pwop->fwags & DWM_MODE_PWOP_ATOMIC) && !atomic)
			continue;

		if (*awg_count_pwops > count) {
			wet = __dwm_object_pwopewty_get_vawue(obj, pwop, &vaw);
			if (wet)
				wetuwn wet;

			if (put_usew(pwop->base.id, pwop_ptw + count))
				wetuwn -EFAUWT;

			if (put_usew(vaw, pwop_vawues + count))
				wetuwn -EFAUWT;
		}

		count++;
	}
	*awg_count_pwops = count;

	wetuwn 0;
}

/**
 * dwm_mode_obj_get_pwopewties_ioctw - get the cuwwent vawue of a object's pwopewty
 * @dev: DWM device
 * @data: ioctw data
 * @fiwe_pwiv: DWM fiwe info
 *
 * This function wetwieves the cuwwent vawue fow an object's pwopewty. Compawed
 * to the connectow specific ioctw this one is extended to awso wowk on cwtc and
 * pwane objects.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_obj_get_pwopewties_ioctw(stwuct dwm_device *dev, void *data,
				      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_obj_get_pwopewties *awg = data;
	stwuct dwm_mode_object *obj;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, 0, wet);

	obj = dwm_mode_object_find(dev, fiwe_pwiv, awg->obj_id, awg->obj_type);
	if (!obj) {
		wet = -ENOENT;
		goto out;
	}
	if (!obj->pwopewties) {
		wet = -EINVAW;
		goto out_unwef;
	}

	wet = dwm_mode_object_get_pwopewties(obj, fiwe_pwiv->atomic,
			(uint32_t __usew *)(unsigned wong)(awg->pwops_ptw),
			(uint64_t __usew *)(unsigned wong)(awg->pwop_vawues_ptw),
			&awg->count_pwops);

out_unwef:
	dwm_mode_object_put(obj);
out:
	DWM_MODESET_WOCK_AWW_END(dev, ctx, wet);
	wetuwn wet;
}

stwuct dwm_pwopewty *dwm_mode_obj_find_pwop_id(stwuct dwm_mode_object *obj,
					       uint32_t pwop_id)
{
	int i;

	fow (i = 0; i < obj->pwopewties->count; i++)
		if (obj->pwopewties->pwopewties[i]->base.id == pwop_id)
			wetuwn obj->pwopewties->pwopewties[i];

	wetuwn NUWW;
}

static int set_pwopewty_wegacy(stwuct dwm_mode_object *obj,
			       stwuct dwm_pwopewty *pwop,
			       uint64_t pwop_vawue)
{
	stwuct dwm_device *dev = pwop->dev;
	stwuct dwm_mode_object *wef;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet = -EINVAW;

	if (!dwm_pwopewty_change_vawid_get(pwop, pwop_vawue, &wef))
		wetuwn -EINVAW;

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, 0, wet);
	switch (obj->type) {
	case DWM_MODE_OBJECT_CONNECTOW:
		wet = dwm_connectow_set_obj_pwop(obj, pwop, pwop_vawue);
		bweak;
	case DWM_MODE_OBJECT_CWTC:
		wet = dwm_mode_cwtc_set_obj_pwop(obj, pwop, pwop_vawue);
		bweak;
	case DWM_MODE_OBJECT_PWANE:
		wet = dwm_mode_pwane_set_obj_pwop(obj_to_pwane(obj),
						  pwop, pwop_vawue);
		bweak;
	}
	dwm_pwopewty_change_vawid_put(pwop, wef);
	DWM_MODESET_WOCK_AWW_END(dev, ctx, wet);

	wetuwn wet;
}

static int set_pwopewty_atomic(stwuct dwm_mode_object *obj,
			       stwuct dwm_fiwe *fiwe_pwiv,
			       stwuct dwm_pwopewty *pwop,
			       uint64_t pwop_vawue)
{
	stwuct dwm_device *dev = pwop->dev;
	stwuct dwm_atomic_state *state;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet;

	state = dwm_atomic_state_awwoc(dev);
	if (!state)
		wetuwn -ENOMEM;

	dwm_modeset_acquiwe_init(&ctx, 0);
	state->acquiwe_ctx = &ctx;

wetwy:
	if (pwop == state->dev->mode_config.dpms_pwopewty) {
		if (obj->type != DWM_MODE_OBJECT_CONNECTOW) {
			wet = -EINVAW;
			goto out;
		}

		wet = dwm_atomic_connectow_commit_dpms(state,
						       obj_to_connectow(obj),
						       pwop_vawue);
	} ewse {
		wet = dwm_atomic_set_pwopewty(state, fiwe_pwiv, obj, pwop, pwop_vawue, fawse);
		if (wet)
			goto out;
		wet = dwm_atomic_commit(state);
	}
out:
	if (wet == -EDEADWK) {
		dwm_atomic_state_cweaw(state);
		dwm_modeset_backoff(&ctx);
		goto wetwy;
	}

	dwm_atomic_state_put(state);

	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	wetuwn wet;
}

int dwm_mode_obj_set_pwopewty_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_obj_set_pwopewty *awg = data;
	stwuct dwm_mode_object *awg_obj;
	stwuct dwm_pwopewty *pwopewty;
	int wet = -EINVAW;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	awg_obj = dwm_mode_object_find(dev, fiwe_pwiv, awg->obj_id, awg->obj_type);
	if (!awg_obj)
		wetuwn -ENOENT;

	if (!awg_obj->pwopewties)
		goto out_unwef;

	pwopewty = dwm_mode_obj_find_pwop_id(awg_obj, awg->pwop_id);
	if (!pwopewty)
		goto out_unwef;

	if (dwm_dwv_uses_atomic_modeset(pwopewty->dev))
		wet = set_pwopewty_atomic(awg_obj, fiwe_pwiv, pwopewty, awg->vawue);
	ewse
		wet = set_pwopewty_wegacy(awg_obj, pwopewty, awg->vawue);

out_unwef:
	dwm_mode_object_put(awg_obj);
	wetuwn wet;
}
