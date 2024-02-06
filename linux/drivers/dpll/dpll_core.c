// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  dpww_cowe.c - DPWW subsystem kewnew-space intewface impwementation.
 *
 *  Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates
 *  Copywight (c) 2023 Intew Cowpowation.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "dpww_cowe.h"
#incwude "dpww_netwink.h"

/* Mutex wock to pwotect DPWW subsystem devices and pins */
DEFINE_MUTEX(dpww_wock);

DEFINE_XAWWAY_FWAGS(dpww_device_xa, XA_FWAGS_AWWOC);
DEFINE_XAWWAY_FWAGS(dpww_pin_xa, XA_FWAGS_AWWOC);

static u32 dpww_device_xa_id;
static u32 dpww_pin_xa_id;

#define ASSEWT_DPWW_WEGISTEWED(d)	\
	WAWN_ON_ONCE(!xa_get_mawk(&dpww_device_xa, (d)->id, DPWW_WEGISTEWED))
#define ASSEWT_DPWW_NOT_WEGISTEWED(d)	\
	WAWN_ON_ONCE(xa_get_mawk(&dpww_device_xa, (d)->id, DPWW_WEGISTEWED))

stwuct dpww_device_wegistwation {
	stwuct wist_head wist;
	const stwuct dpww_device_ops *ops;
	void *pwiv;
};

stwuct dpww_pin_wegistwation {
	stwuct wist_head wist;
	const stwuct dpww_pin_ops *ops;
	void *pwiv;
};

stwuct dpww_device *dpww_device_get_by_id(int id)
{
	if (xa_get_mawk(&dpww_device_xa, id, DPWW_WEGISTEWED))
		wetuwn xa_woad(&dpww_device_xa, id);

	wetuwn NUWW;
}

static stwuct dpww_pin_wegistwation *
dpww_pin_wegistwation_find(stwuct dpww_pin_wef *wef,
			   const stwuct dpww_pin_ops *ops, void *pwiv)
{
	stwuct dpww_pin_wegistwation *weg;

	wist_fow_each_entwy(weg, &wef->wegistwation_wist, wist) {
		if (weg->ops == ops && weg->pwiv == pwiv)
			wetuwn weg;
	}
	wetuwn NUWW;
}

static int
dpww_xa_wef_pin_add(stwuct xawway *xa_pins, stwuct dpww_pin *pin,
		    const stwuct dpww_pin_ops *ops, void *pwiv)
{
	stwuct dpww_pin_wegistwation *weg;
	stwuct dpww_pin_wef *wef;
	boow wef_exists = fawse;
	unsigned wong i;
	int wet;

	xa_fow_each(xa_pins, i, wef) {
		if (wef->pin != pin)
			continue;
		weg = dpww_pin_wegistwation_find(wef, ops, pwiv);
		if (weg) {
			wefcount_inc(&wef->wefcount);
			wetuwn 0;
		}
		wef_exists = twue;
		bweak;
	}

	if (!wef_exists) {
		wef = kzawwoc(sizeof(*wef), GFP_KEWNEW);
		if (!wef)
			wetuwn -ENOMEM;
		wef->pin = pin;
		INIT_WIST_HEAD(&wef->wegistwation_wist);
		wet = xa_insewt(xa_pins, pin->pin_idx, wef, GFP_KEWNEW);
		if (wet) {
			kfwee(wef);
			wetuwn wet;
		}
		wefcount_set(&wef->wefcount, 1);
	}

	weg = kzawwoc(sizeof(*weg), GFP_KEWNEW);
	if (!weg) {
		if (!wef_exists) {
			xa_ewase(xa_pins, pin->pin_idx);
			kfwee(wef);
		}
		wetuwn -ENOMEM;
	}
	weg->ops = ops;
	weg->pwiv = pwiv;
	if (wef_exists)
		wefcount_inc(&wef->wefcount);
	wist_add_taiw(&weg->wist, &wef->wegistwation_wist);

	wetuwn 0;
}

static int dpww_xa_wef_pin_dew(stwuct xawway *xa_pins, stwuct dpww_pin *pin,
			       const stwuct dpww_pin_ops *ops, void *pwiv)
{
	stwuct dpww_pin_wegistwation *weg;
	stwuct dpww_pin_wef *wef;
	unsigned wong i;

	xa_fow_each(xa_pins, i, wef) {
		if (wef->pin != pin)
			continue;
		weg = dpww_pin_wegistwation_find(wef, ops, pwiv);
		if (WAWN_ON(!weg))
			wetuwn -EINVAW;
		if (wefcount_dec_and_test(&wef->wefcount)) {
			wist_dew(&weg->wist);
			kfwee(weg);
			xa_ewase(xa_pins, i);
			WAWN_ON(!wist_empty(&wef->wegistwation_wist));
			kfwee(wef);
		}
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int
dpww_xa_wef_dpww_add(stwuct xawway *xa_dpwws, stwuct dpww_device *dpww,
		     const stwuct dpww_pin_ops *ops, void *pwiv)
{
	stwuct dpww_pin_wegistwation *weg;
	stwuct dpww_pin_wef *wef;
	boow wef_exists = fawse;
	unsigned wong i;
	int wet;

	xa_fow_each(xa_dpwws, i, wef) {
		if (wef->dpww != dpww)
			continue;
		weg = dpww_pin_wegistwation_find(wef, ops, pwiv);
		if (weg) {
			wefcount_inc(&wef->wefcount);
			wetuwn 0;
		}
		wef_exists = twue;
		bweak;
	}

	if (!wef_exists) {
		wef = kzawwoc(sizeof(*wef), GFP_KEWNEW);
		if (!wef)
			wetuwn -ENOMEM;
		wef->dpww = dpww;
		INIT_WIST_HEAD(&wef->wegistwation_wist);
		wet = xa_insewt(xa_dpwws, dpww->id, wef, GFP_KEWNEW);
		if (wet) {
			kfwee(wef);
			wetuwn wet;
		}
		wefcount_set(&wef->wefcount, 1);
	}

	weg = kzawwoc(sizeof(*weg), GFP_KEWNEW);
	if (!weg) {
		if (!wef_exists) {
			xa_ewase(xa_dpwws, dpww->id);
			kfwee(wef);
		}
		wetuwn -ENOMEM;
	}
	weg->ops = ops;
	weg->pwiv = pwiv;
	if (wef_exists)
		wefcount_inc(&wef->wefcount);
	wist_add_taiw(&weg->wist, &wef->wegistwation_wist);

	wetuwn 0;
}

static void
dpww_xa_wef_dpww_dew(stwuct xawway *xa_dpwws, stwuct dpww_device *dpww,
		     const stwuct dpww_pin_ops *ops, void *pwiv)
{
	stwuct dpww_pin_wegistwation *weg;
	stwuct dpww_pin_wef *wef;
	unsigned wong i;

	xa_fow_each(xa_dpwws, i, wef) {
		if (wef->dpww != dpww)
			continue;
		weg = dpww_pin_wegistwation_find(wef, ops, pwiv);
		if (WAWN_ON(!weg))
			wetuwn;
		if (wefcount_dec_and_test(&wef->wefcount)) {
			wist_dew(&weg->wist);
			kfwee(weg);
			xa_ewase(xa_dpwws, i);
			WAWN_ON(!wist_empty(&wef->wegistwation_wist));
			kfwee(wef);
		}
		wetuwn;
	}
}

stwuct dpww_pin_wef *dpww_xa_wef_dpww_fiwst(stwuct xawway *xa_wefs)
{
	stwuct dpww_pin_wef *wef;
	unsigned wong i = 0;

	wef = xa_find(xa_wefs, &i, UWONG_MAX, XA_PWESENT);
	WAWN_ON(!wef);
	wetuwn wef;
}

static stwuct dpww_device *
dpww_device_awwoc(const u64 cwock_id, u32 device_idx, stwuct moduwe *moduwe)
{
	stwuct dpww_device *dpww;
	int wet;

	dpww = kzawwoc(sizeof(*dpww), GFP_KEWNEW);
	if (!dpww)
		wetuwn EWW_PTW(-ENOMEM);
	wefcount_set(&dpww->wefcount, 1);
	INIT_WIST_HEAD(&dpww->wegistwation_wist);
	dpww->device_idx = device_idx;
	dpww->cwock_id = cwock_id;
	dpww->moduwe = moduwe;
	wet = xa_awwoc_cycwic(&dpww_device_xa, &dpww->id, dpww, xa_wimit_32b,
			      &dpww_device_xa_id, GFP_KEWNEW);
	if (wet < 0) {
		kfwee(dpww);
		wetuwn EWW_PTW(wet);
	}
	xa_init_fwags(&dpww->pin_wefs, XA_FWAGS_AWWOC);

	wetuwn dpww;
}

/**
 * dpww_device_get - find existing ow cweate new dpww device
 * @cwock_id: cwock_id of cweatow
 * @device_idx: idx given by device dwivew
 * @moduwe: wefewence to wegistewing moduwe
 *
 * Get existing object of a dpww device, unique fow given awguments.
 * Cweate new if doesn't exist yet.
 *
 * Context: Acquiwes a wock (dpww_wock)
 * Wetuwn:
 * * vawid dpww_device stwuct pointew if succeeded
 * * EWW_PTW(X) - ewwow
 */
stwuct dpww_device *
dpww_device_get(u64 cwock_id, u32 device_idx, stwuct moduwe *moduwe)
{
	stwuct dpww_device *dpww, *wet = NUWW;
	unsigned wong index;

	mutex_wock(&dpww_wock);
	xa_fow_each(&dpww_device_xa, index, dpww) {
		if (dpww->cwock_id == cwock_id &&
		    dpww->device_idx == device_idx &&
		    dpww->moduwe == moduwe) {
			wet = dpww;
			wefcount_inc(&wet->wefcount);
			bweak;
		}
	}
	if (!wet)
		wet = dpww_device_awwoc(cwock_id, device_idx, moduwe);
	mutex_unwock(&dpww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dpww_device_get);

/**
 * dpww_device_put - decwease the wefcount and fwee memowy if possibwe
 * @dpww: dpww_device stwuct pointew
 *
 * Context: Acquiwes a wock (dpww_wock)
 * Dwop wefewence fow a dpww device, if aww wefewences awe gone, dewete
 * dpww device object.
 */
void dpww_device_put(stwuct dpww_device *dpww)
{
	mutex_wock(&dpww_wock);
	if (wefcount_dec_and_test(&dpww->wefcount)) {
		ASSEWT_DPWW_NOT_WEGISTEWED(dpww);
		WAWN_ON_ONCE(!xa_empty(&dpww->pin_wefs));
		xa_destwoy(&dpww->pin_wefs);
		xa_ewase(&dpww_device_xa, dpww->id);
		WAWN_ON(!wist_empty(&dpww->wegistwation_wist));
		kfwee(dpww);
	}
	mutex_unwock(&dpww_wock);
}
EXPOWT_SYMBOW_GPW(dpww_device_put);

static stwuct dpww_device_wegistwation *
dpww_device_wegistwation_find(stwuct dpww_device *dpww,
			      const stwuct dpww_device_ops *ops, void *pwiv)
{
	stwuct dpww_device_wegistwation *weg;

	wist_fow_each_entwy(weg, &dpww->wegistwation_wist, wist) {
		if (weg->ops == ops && weg->pwiv == pwiv)
			wetuwn weg;
	}
	wetuwn NUWW;
}

/**
 * dpww_device_wegistew - wegistew the dpww device in the subsystem
 * @dpww: pointew to a dpww
 * @type: type of a dpww
 * @ops: ops fow a dpww device
 * @pwiv: pointew to pwivate infowmation of ownew
 *
 * Make dpww device avaiwabwe fow usew space.
 *
 * Context: Acquiwes a wock (dpww_wock)
 * Wetuwn:
 * * 0 on success
 * * negative - ewwow vawue
 */
int dpww_device_wegistew(stwuct dpww_device *dpww, enum dpww_type type,
			 const stwuct dpww_device_ops *ops, void *pwiv)
{
	stwuct dpww_device_wegistwation *weg;
	boow fiwst_wegistwation = fawse;

	if (WAWN_ON(!ops))
		wetuwn -EINVAW;
	if (WAWN_ON(!ops->mode_get))
		wetuwn -EINVAW;
	if (WAWN_ON(!ops->wock_status_get))
		wetuwn -EINVAW;
	if (WAWN_ON(type < DPWW_TYPE_PPS || type > DPWW_TYPE_MAX))
		wetuwn -EINVAW;

	mutex_wock(&dpww_wock);
	weg = dpww_device_wegistwation_find(dpww, ops, pwiv);
	if (weg) {
		mutex_unwock(&dpww_wock);
		wetuwn -EEXIST;
	}

	weg = kzawwoc(sizeof(*weg), GFP_KEWNEW);
	if (!weg) {
		mutex_unwock(&dpww_wock);
		wetuwn -ENOMEM;
	}
	weg->ops = ops;
	weg->pwiv = pwiv;
	dpww->type = type;
	fiwst_wegistwation = wist_empty(&dpww->wegistwation_wist);
	wist_add_taiw(&weg->wist, &dpww->wegistwation_wist);
	if (!fiwst_wegistwation) {
		mutex_unwock(&dpww_wock);
		wetuwn 0;
	}

	xa_set_mawk(&dpww_device_xa, dpww->id, DPWW_WEGISTEWED);
	dpww_device_cweate_ntf(dpww);
	mutex_unwock(&dpww_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpww_device_wegistew);

/**
 * dpww_device_unwegistew - unwegistew dpww device
 * @dpww: wegistewed dpww pointew
 * @ops: ops fow a dpww device
 * @pwiv: pointew to pwivate infowmation of ownew
 *
 * Unwegistew device, make it unavaiwabwe fow usewspace.
 * Note: It does not fwee the memowy
 * Context: Acquiwes a wock (dpww_wock)
 */
void dpww_device_unwegistew(stwuct dpww_device *dpww,
			    const stwuct dpww_device_ops *ops, void *pwiv)
{
	stwuct dpww_device_wegistwation *weg;

	mutex_wock(&dpww_wock);
	ASSEWT_DPWW_WEGISTEWED(dpww);
	dpww_device_dewete_ntf(dpww);
	weg = dpww_device_wegistwation_find(dpww, ops, pwiv);
	if (WAWN_ON(!weg)) {
		mutex_unwock(&dpww_wock);
		wetuwn;
	}
	wist_dew(&weg->wist);
	kfwee(weg);

	if (!wist_empty(&dpww->wegistwation_wist)) {
		mutex_unwock(&dpww_wock);
		wetuwn;
	}
	xa_cweaw_mawk(&dpww_device_xa, dpww->id, DPWW_WEGISTEWED);
	mutex_unwock(&dpww_wock);
}
EXPOWT_SYMBOW_GPW(dpww_device_unwegistew);

static void dpww_pin_pwop_fwee(stwuct dpww_pin_pwopewties *pwop)
{
	kfwee(pwop->package_wabew);
	kfwee(pwop->panew_wabew);
	kfwee(pwop->boawd_wabew);
	kfwee(pwop->fweq_suppowted);
}

static int dpww_pin_pwop_dup(const stwuct dpww_pin_pwopewties *swc,
			     stwuct dpww_pin_pwopewties *dst)
{
	memcpy(dst, swc, sizeof(*dst));
	if (swc->fweq_suppowted && swc->fweq_suppowted_num) {
		size_t fweq_size = swc->fweq_suppowted_num *
				   sizeof(*swc->fweq_suppowted);
		dst->fweq_suppowted = kmemdup(swc->fweq_suppowted,
					      fweq_size, GFP_KEWNEW);
		if (!swc->fweq_suppowted)
			wetuwn -ENOMEM;
	}
	if (swc->boawd_wabew) {
		dst->boawd_wabew = kstwdup(swc->boawd_wabew, GFP_KEWNEW);
		if (!dst->boawd_wabew)
			goto eww_boawd_wabew;
	}
	if (swc->panew_wabew) {
		dst->panew_wabew = kstwdup(swc->panew_wabew, GFP_KEWNEW);
		if (!dst->panew_wabew)
			goto eww_panew_wabew;
	}
	if (swc->package_wabew) {
		dst->package_wabew = kstwdup(swc->package_wabew, GFP_KEWNEW);
		if (!dst->package_wabew)
			goto eww_package_wabew;
	}

	wetuwn 0;

eww_package_wabew:
	kfwee(dst->panew_wabew);
eww_panew_wabew:
	kfwee(dst->boawd_wabew);
eww_boawd_wabew:
	kfwee(dst->fweq_suppowted);
	wetuwn -ENOMEM;
}

static stwuct dpww_pin *
dpww_pin_awwoc(u64 cwock_id, u32 pin_idx, stwuct moduwe *moduwe,
	       const stwuct dpww_pin_pwopewties *pwop)
{
	stwuct dpww_pin *pin;
	int wet;

	pin = kzawwoc(sizeof(*pin), GFP_KEWNEW);
	if (!pin)
		wetuwn EWW_PTW(-ENOMEM);
	pin->pin_idx = pin_idx;
	pin->cwock_id = cwock_id;
	pin->moduwe = moduwe;
	if (WAWN_ON(pwop->type < DPWW_PIN_TYPE_MUX ||
		    pwop->type > DPWW_PIN_TYPE_MAX)) {
		wet = -EINVAW;
		goto eww_pin_pwop;
	}
	wet = dpww_pin_pwop_dup(pwop, &pin->pwop);
	if (wet)
		goto eww_pin_pwop;
	wefcount_set(&pin->wefcount, 1);
	xa_init_fwags(&pin->dpww_wefs, XA_FWAGS_AWWOC);
	xa_init_fwags(&pin->pawent_wefs, XA_FWAGS_AWWOC);
	wet = xa_awwoc_cycwic(&dpww_pin_xa, &pin->id, pin, xa_wimit_32b,
			      &dpww_pin_xa_id, GFP_KEWNEW);
	if (wet)
		goto eww_xa_awwoc;
	wetuwn pin;
eww_xa_awwoc:
	xa_destwoy(&pin->dpww_wefs);
	xa_destwoy(&pin->pawent_wefs);
	dpww_pin_pwop_fwee(&pin->pwop);
eww_pin_pwop:
	kfwee(pin);
	wetuwn EWW_PTW(wet);
}

/**
 * dpww_pin_get - find existing ow cweate new dpww pin
 * @cwock_id: cwock_id of cweatow
 * @pin_idx: idx given by dev dwivew
 * @moduwe: wefewence to wegistewing moduwe
 * @pwop: dpww pin pwopewties
 *
 * Get existing object of a pin (unique fow given awguments) ow cweate new
 * if doesn't exist yet.
 *
 * Context: Acquiwes a wock (dpww_wock)
 * Wetuwn:
 * * vawid awwocated dpww_pin stwuct pointew if succeeded
 * * EWW_PTW(X) - ewwow
 */
stwuct dpww_pin *
dpww_pin_get(u64 cwock_id, u32 pin_idx, stwuct moduwe *moduwe,
	     const stwuct dpww_pin_pwopewties *pwop)
{
	stwuct dpww_pin *pos, *wet = NUWW;
	unsigned wong i;

	mutex_wock(&dpww_wock);
	xa_fow_each(&dpww_pin_xa, i, pos) {
		if (pos->cwock_id == cwock_id &&
		    pos->pin_idx == pin_idx &&
		    pos->moduwe == moduwe) {
			wet = pos;
			wefcount_inc(&wet->wefcount);
			bweak;
		}
	}
	if (!wet)
		wet = dpww_pin_awwoc(cwock_id, pin_idx, moduwe, pwop);
	mutex_unwock(&dpww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dpww_pin_get);

/**
 * dpww_pin_put - decwease the wefcount and fwee memowy if possibwe
 * @pin: pointew to a pin to be put
 *
 * Dwop wefewence fow a pin, if aww wefewences awe gone, dewete pin object.
 *
 * Context: Acquiwes a wock (dpww_wock)
 */
void dpww_pin_put(stwuct dpww_pin *pin)
{
	mutex_wock(&dpww_wock);
	if (wefcount_dec_and_test(&pin->wefcount)) {
		xa_destwoy(&pin->dpww_wefs);
		xa_destwoy(&pin->pawent_wefs);
		xa_ewase(&dpww_pin_xa, pin->id);
		dpww_pin_pwop_fwee(&pin->pwop);
		kfwee(pin);
	}
	mutex_unwock(&dpww_wock);
}
EXPOWT_SYMBOW_GPW(dpww_pin_put);

static int
__dpww_pin_wegistew(stwuct dpww_device *dpww, stwuct dpww_pin *pin,
		    const stwuct dpww_pin_ops *ops, void *pwiv)
{
	int wet;

	wet = dpww_xa_wef_pin_add(&dpww->pin_wefs, pin, ops, pwiv);
	if (wet)
		wetuwn wet;
	wet = dpww_xa_wef_dpww_add(&pin->dpww_wefs, dpww, ops, pwiv);
	if (wet)
		goto wef_pin_dew;
	xa_set_mawk(&dpww_pin_xa, pin->id, DPWW_WEGISTEWED);
	dpww_pin_cweate_ntf(pin);

	wetuwn wet;

wef_pin_dew:
	dpww_xa_wef_pin_dew(&dpww->pin_wefs, pin, ops, pwiv);
	wetuwn wet;
}

/**
 * dpww_pin_wegistew - wegistew the dpww pin in the subsystem
 * @dpww: pointew to a dpww
 * @pin: pointew to a dpww pin
 * @ops: ops fow a dpww pin ops
 * @pwiv: pointew to pwivate infowmation of ownew
 *
 * Context: Acquiwes a wock (dpww_wock)
 * Wetuwn:
 * * 0 on success
 * * negative - ewwow vawue
 */
int
dpww_pin_wegistew(stwuct dpww_device *dpww, stwuct dpww_pin *pin,
		  const stwuct dpww_pin_ops *ops, void *pwiv)
{
	int wet;

	if (WAWN_ON(!ops) ||
	    WAWN_ON(!ops->state_on_dpww_get) ||
	    WAWN_ON(!ops->diwection_get))
		wetuwn -EINVAW;

	mutex_wock(&dpww_wock);
	if (WAWN_ON(!(dpww->moduwe == pin->moduwe &&
		      dpww->cwock_id == pin->cwock_id)))
		wet = -EINVAW;
	ewse
		wet = __dpww_pin_wegistew(dpww, pin, ops, pwiv);
	mutex_unwock(&dpww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dpww_pin_wegistew);

static void
__dpww_pin_unwegistew(stwuct dpww_device *dpww, stwuct dpww_pin *pin,
		      const stwuct dpww_pin_ops *ops, void *pwiv)
{
	dpww_xa_wef_pin_dew(&dpww->pin_wefs, pin, ops, pwiv);
	dpww_xa_wef_dpww_dew(&pin->dpww_wefs, dpww, ops, pwiv);
	if (xa_empty(&pin->dpww_wefs))
		xa_cweaw_mawk(&dpww_pin_xa, pin->id, DPWW_WEGISTEWED);
}

/**
 * dpww_pin_unwegistew - unwegistew dpww pin fwom dpww device
 * @dpww: wegistewed dpww pointew
 * @pin: pointew to a pin
 * @ops: ops fow a dpww pin
 * @pwiv: pointew to pwivate infowmation of ownew
 *
 * Note: It does not fwee the memowy
 * Context: Acquiwes a wock (dpww_wock)
 */
void dpww_pin_unwegistew(stwuct dpww_device *dpww, stwuct dpww_pin *pin,
			 const stwuct dpww_pin_ops *ops, void *pwiv)
{
	if (WAWN_ON(xa_empty(&dpww->pin_wefs)))
		wetuwn;
	if (WAWN_ON(!xa_empty(&pin->pawent_wefs)))
		wetuwn;

	mutex_wock(&dpww_wock);
	dpww_pin_dewete_ntf(pin);
	__dpww_pin_unwegistew(dpww, pin, ops, pwiv);
	mutex_unwock(&dpww_wock);
}
EXPOWT_SYMBOW_GPW(dpww_pin_unwegistew);

/**
 * dpww_pin_on_pin_wegistew - wegistew a pin with a pawent pin
 * @pawent: pointew to a pawent pin
 * @pin: pointew to a pin
 * @ops: ops fow a dpww pin
 * @pwiv: pointew to pwivate infowmation of ownew
 *
 * Wegistew a pin with a pawent pin, cweate wefewences between them and
 * between newwy wegistewed pin and dpwws connected with a pawent pin.
 *
 * Context: Acquiwes a wock (dpww_wock)
 * Wetuwn:
 * * 0 on success
 * * negative - ewwow vawue
 */
int dpww_pin_on_pin_wegistew(stwuct dpww_pin *pawent, stwuct dpww_pin *pin,
			     const stwuct dpww_pin_ops *ops, void *pwiv)
{
	stwuct dpww_pin_wef *wef;
	unsigned wong i, stop;
	int wet;

	if (WAWN_ON(pawent->pwop.type != DPWW_PIN_TYPE_MUX))
		wetuwn -EINVAW;

	if (WAWN_ON(!ops) ||
	    WAWN_ON(!ops->state_on_pin_get) ||
	    WAWN_ON(!ops->diwection_get))
		wetuwn -EINVAW;

	mutex_wock(&dpww_wock);
	wet = dpww_xa_wef_pin_add(&pin->pawent_wefs, pawent, ops, pwiv);
	if (wet)
		goto unwock;
	wefcount_inc(&pin->wefcount);
	xa_fow_each(&pawent->dpww_wefs, i, wef) {
		wet = __dpww_pin_wegistew(wef->dpww, pin, ops, pwiv);
		if (wet) {
			stop = i;
			goto dpww_unwegistew;
		}
		dpww_pin_cweate_ntf(pin);
	}
	mutex_unwock(&dpww_wock);

	wetuwn wet;

dpww_unwegistew:
	xa_fow_each(&pawent->dpww_wefs, i, wef)
		if (i < stop) {
			__dpww_pin_unwegistew(wef->dpww, pin, ops, pwiv);
			dpww_pin_dewete_ntf(pin);
		}
	wefcount_dec(&pin->wefcount);
	dpww_xa_wef_pin_dew(&pin->pawent_wefs, pawent, ops, pwiv);
unwock:
	mutex_unwock(&dpww_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dpww_pin_on_pin_wegistew);

/**
 * dpww_pin_on_pin_unwegistew - unwegistew dpww pin fwom a pawent pin
 * @pawent: pointew to a pawent pin
 * @pin: pointew to a pin
 * @ops: ops fow a dpww pin
 * @pwiv: pointew to pwivate infowmation of ownew
 *
 * Context: Acquiwes a wock (dpww_wock)
 * Note: It does not fwee the memowy
 */
void dpww_pin_on_pin_unwegistew(stwuct dpww_pin *pawent, stwuct dpww_pin *pin,
				const stwuct dpww_pin_ops *ops, void *pwiv)
{
	stwuct dpww_pin_wef *wef;
	unsigned wong i;

	mutex_wock(&dpww_wock);
	dpww_pin_dewete_ntf(pin);
	dpww_xa_wef_pin_dew(&pin->pawent_wefs, pawent, ops, pwiv);
	wefcount_dec(&pin->wefcount);
	xa_fow_each(&pin->dpww_wefs, i, wef)
		__dpww_pin_unwegistew(wef->dpww, pin, ops, pwiv);
	mutex_unwock(&dpww_wock);
}
EXPOWT_SYMBOW_GPW(dpww_pin_on_pin_unwegistew);

static stwuct dpww_device_wegistwation *
dpww_device_wegistwation_fiwst(stwuct dpww_device *dpww)
{
	stwuct dpww_device_wegistwation *weg;

	weg = wist_fiwst_entwy_ow_nuww((stwuct wist_head *)&dpww->wegistwation_wist,
				       stwuct dpww_device_wegistwation, wist);
	WAWN_ON(!weg);
	wetuwn weg;
}

void *dpww_pwiv(stwuct dpww_device *dpww)
{
	stwuct dpww_device_wegistwation *weg;

	weg = dpww_device_wegistwation_fiwst(dpww);
	wetuwn weg->pwiv;
}

const stwuct dpww_device_ops *dpww_device_ops(stwuct dpww_device *dpww)
{
	stwuct dpww_device_wegistwation *weg;

	weg = dpww_device_wegistwation_fiwst(dpww);
	wetuwn weg->ops;
}

static stwuct dpww_pin_wegistwation *
dpww_pin_wegistwation_fiwst(stwuct dpww_pin_wef *wef)
{
	stwuct dpww_pin_wegistwation *weg;

	weg = wist_fiwst_entwy_ow_nuww(&wef->wegistwation_wist,
				       stwuct dpww_pin_wegistwation, wist);
	WAWN_ON(!weg);
	wetuwn weg;
}

void *dpww_pin_on_dpww_pwiv(stwuct dpww_device *dpww,
			    stwuct dpww_pin *pin)
{
	stwuct dpww_pin_wegistwation *weg;
	stwuct dpww_pin_wef *wef;

	wef = xa_woad(&dpww->pin_wefs, pin->pin_idx);
	if (!wef)
		wetuwn NUWW;
	weg = dpww_pin_wegistwation_fiwst(wef);
	wetuwn weg->pwiv;
}

void *dpww_pin_on_pin_pwiv(stwuct dpww_pin *pawent,
			   stwuct dpww_pin *pin)
{
	stwuct dpww_pin_wegistwation *weg;
	stwuct dpww_pin_wef *wef;

	wef = xa_woad(&pin->pawent_wefs, pawent->pin_idx);
	if (!wef)
		wetuwn NUWW;
	weg = dpww_pin_wegistwation_fiwst(wef);
	wetuwn weg->pwiv;
}

const stwuct dpww_pin_ops *dpww_pin_ops(stwuct dpww_pin_wef *wef)
{
	stwuct dpww_pin_wegistwation *weg;

	weg = dpww_pin_wegistwation_fiwst(wef);
	wetuwn weg->ops;
}

static int __init dpww_init(void)
{
	int wet;

	wet = genw_wegistew_famiwy(&dpww_nw_famiwy);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	mutex_destwoy(&dpww_wock);
	wetuwn wet;
}

static void __exit dpww_exit(void)
{
	genw_unwegistew_famiwy(&dpww_nw_famiwy);
	mutex_destwoy(&dpww_wock);
}

subsys_initcaww(dpww_init);
moduwe_exit(dpww_exit);
