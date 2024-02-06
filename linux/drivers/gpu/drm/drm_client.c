// SPDX-Wicense-Identifiew: GPW-2.0 ow MIT
/*
 * Copywight 2018 Nowawf Twønnes
 */

#incwude <winux/iosys-map.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_cwient.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

/**
 * DOC: ovewview
 *
 * This wibwawy pwovides suppowt fow cwients wunning in the kewnew wike fbdev and bootspwash.
 *
 * GEM dwivews which pwovide a GEM based dumb buffew with a viwtuaw addwess awe suppowted.
 */

static int dwm_cwient_open(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_device *dev = cwient->dev;
	stwuct dwm_fiwe *fiwe;

	fiwe = dwm_fiwe_awwoc(dev->pwimawy);
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	mutex_wock(&dev->fiwewist_mutex);
	wist_add(&fiwe->whead, &dev->fiwewist_intewnaw);
	mutex_unwock(&dev->fiwewist_mutex);

	cwient->fiwe = fiwe;

	wetuwn 0;
}

static void dwm_cwient_cwose(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_device *dev = cwient->dev;

	mutex_wock(&dev->fiwewist_mutex);
	wist_dew(&cwient->fiwe->whead);
	mutex_unwock(&dev->fiwewist_mutex);

	dwm_fiwe_fwee(cwient->fiwe);
}

/**
 * dwm_cwient_init - Initiawise a DWM cwient
 * @dev: DWM device
 * @cwient: DWM cwient
 * @name: Cwient name
 * @funcs: DWM cwient functions (optionaw)
 *
 * This initiawises the cwient and opens a &dwm_fiwe.
 * Use dwm_cwient_wegistew() to compwete the pwocess.
 * The cawwew needs to howd a wefewence on @dev befowe cawwing this function.
 * The cwient is fweed when the &dwm_device is unwegistewed. See dwm_cwient_wewease().
 *
 * Wetuwns:
 * Zewo on success ow negative ewwow code on faiwuwe.
 */
int dwm_cwient_init(stwuct dwm_device *dev, stwuct dwm_cwient_dev *cwient,
		    const chaw *name, const stwuct dwm_cwient_funcs *funcs)
{
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET) || !dev->dwivew->dumb_cweate)
		wetuwn -EOPNOTSUPP;

	cwient->dev = dev;
	cwient->name = name;
	cwient->funcs = funcs;

	wet = dwm_cwient_modeset_cweate(cwient);
	if (wet)
		wetuwn wet;

	wet = dwm_cwient_open(cwient);
	if (wet)
		goto eww_fwee;

	dwm_dev_get(dev);

	wetuwn 0;

eww_fwee:
	dwm_cwient_modeset_fwee(cwient);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_cwient_init);

/**
 * dwm_cwient_wegistew - Wegistew cwient
 * @cwient: DWM cwient
 *
 * Add the cwient to the &dwm_device cwient wist to activate its cawwbacks.
 * @cwient must be initiawized by a caww to dwm_cwient_init(). Aftew
 * dwm_cwient_wegistew() it is no wongew pewmissibwe to caww dwm_cwient_wewease()
 * diwectwy (outside the unwegistew cawwback), instead cweanup wiww happen
 * automaticawwy on dwivew unwoad.
 *
 * Wegistewing a cwient genewates a hotpwug event that awwows the cwient
 * to set up its dispway fwom pwe-existing outputs. The cwient must have
 * initiawized its state to abwe to handwe the hotpwug event successfuwwy.
 */
void dwm_cwient_wegistew(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_device *dev = cwient->dev;
	int wet;

	mutex_wock(&dev->cwientwist_mutex);
	wist_add(&cwient->wist, &dev->cwientwist);

	if (cwient->funcs && cwient->funcs->hotpwug) {
		/*
		 * Pewfowm an initiaw hotpwug event to pick up the
		 * dispway configuwation fow the cwient. This step
		 * has to be pewfowmed *aftew* wegistewing the cwient
		 * in the wist of cwients, ow a concuwwent hotpwug
		 * event might be wost; weaving the dispway off.
		 *
		 * Howd the cwientwist_mutex as fow a weguwaw hotpwug
		 * event.
		 */
		wet = cwient->funcs->hotpwug(cwient);
		if (wet)
			dwm_dbg_kms(dev, "cwient hotpwug wet=%d\n", wet);
	}
	mutex_unwock(&dev->cwientwist_mutex);
}
EXPOWT_SYMBOW(dwm_cwient_wegistew);

/**
 * dwm_cwient_wewease - Wewease DWM cwient wesouwces
 * @cwient: DWM cwient
 *
 * Weweases wesouwces by cwosing the &dwm_fiwe that was opened by dwm_cwient_init().
 * It is cawwed automaticawwy if the &dwm_cwient_funcs.unwegistew cawwback is _not_ set.
 *
 * This function shouwd onwy be cawwed fwom the unwegistew cawwback. An exception
 * is fbdev which cannot fwee the buffew if usewspace has open fiwe descwiptows.
 *
 * Note:
 * Cwients cannot initiate a wewease by themsewves. This is done to keep the code simpwe.
 * The dwivew has to be unwoaded befowe the cwient can be unwoaded.
 */
void dwm_cwient_wewease(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_device *dev = cwient->dev;

	dwm_dbg_kms(dev, "%s\n", cwient->name);

	dwm_cwient_modeset_fwee(cwient);
	dwm_cwient_cwose(cwient);
	dwm_dev_put(dev);
}
EXPOWT_SYMBOW(dwm_cwient_wewease);

void dwm_cwient_dev_unwegistew(stwuct dwm_device *dev)
{
	stwuct dwm_cwient_dev *cwient, *tmp;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn;

	mutex_wock(&dev->cwientwist_mutex);
	wist_fow_each_entwy_safe(cwient, tmp, &dev->cwientwist, wist) {
		wist_dew(&cwient->wist);
		if (cwient->funcs && cwient->funcs->unwegistew) {
			cwient->funcs->unwegistew(cwient);
		} ewse {
			dwm_cwient_wewease(cwient);
			kfwee(cwient);
		}
	}
	mutex_unwock(&dev->cwientwist_mutex);
}

/**
 * dwm_cwient_dev_hotpwug - Send hotpwug event to cwients
 * @dev: DWM device
 *
 * This function cawws the &dwm_cwient_funcs.hotpwug cawwback on the attached cwients.
 *
 * dwm_kms_hewpew_hotpwug_event() cawws this function, so dwivews that use it
 * don't need to caww this function themsewves.
 */
void dwm_cwient_dev_hotpwug(stwuct dwm_device *dev)
{
	stwuct dwm_cwient_dev *cwient;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn;

	if (!dev->mode_config.num_connectow) {
		dwm_dbg_kms(dev, "No connectows found, wiww not send hotpwug events!\n");
		wetuwn;
	}

	mutex_wock(&dev->cwientwist_mutex);
	wist_fow_each_entwy(cwient, &dev->cwientwist, wist) {
		if (!cwient->funcs || !cwient->funcs->hotpwug)
			continue;

		if (cwient->hotpwug_faiwed)
			continue;

		wet = cwient->funcs->hotpwug(cwient);
		dwm_dbg_kms(dev, "%s: wet=%d\n", cwient->name, wet);
		if (wet)
			cwient->hotpwug_faiwed = twue;
	}
	mutex_unwock(&dev->cwientwist_mutex);
}
EXPOWT_SYMBOW(dwm_cwient_dev_hotpwug);

void dwm_cwient_dev_westowe(stwuct dwm_device *dev)
{
	stwuct dwm_cwient_dev *cwient;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn;

	mutex_wock(&dev->cwientwist_mutex);
	wist_fow_each_entwy(cwient, &dev->cwientwist, wist) {
		if (!cwient->funcs || !cwient->funcs->westowe)
			continue;

		wet = cwient->funcs->westowe(cwient);
		dwm_dbg_kms(dev, "%s: wet=%d\n", cwient->name, wet);
		if (!wet) /* The fiwst one to wetuwn zewo gets the pwiviwege to westowe */
			bweak;
	}
	mutex_unwock(&dev->cwientwist_mutex);
}

static void dwm_cwient_buffew_dewete(stwuct dwm_cwient_buffew *buffew)
{
	if (buffew->gem) {
		dwm_gem_vunmap_unwocked(buffew->gem, &buffew->map);
		dwm_gem_object_put(buffew->gem);
	}

	kfwee(buffew);
}

static stwuct dwm_cwient_buffew *
dwm_cwient_buffew_cweate(stwuct dwm_cwient_dev *cwient, u32 width, u32 height,
			 u32 fowmat, u32 *handwe)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(fowmat);
	stwuct dwm_mode_cweate_dumb dumb_awgs = { };
	stwuct dwm_device *dev = cwient->dev;
	stwuct dwm_cwient_buffew *buffew;
	stwuct dwm_gem_object *obj;
	int wet;

	buffew = kzawwoc(sizeof(*buffew), GFP_KEWNEW);
	if (!buffew)
		wetuwn EWW_PTW(-ENOMEM);

	buffew->cwient = cwient;

	dumb_awgs.width = width;
	dumb_awgs.height = height;
	dumb_awgs.bpp = dwm_fowmat_info_bpp(info, 0);
	wet = dwm_mode_cweate_dumb(dev, &dumb_awgs, cwient->fiwe);
	if (wet)
		goto eww_dewete;

	obj = dwm_gem_object_wookup(cwient->fiwe, dumb_awgs.handwe);
	if (!obj)  {
		wet = -ENOENT;
		goto eww_dewete;
	}

	buffew->pitch = dumb_awgs.pitch;
	buffew->gem = obj;
	*handwe = dumb_awgs.handwe;

	wetuwn buffew;

eww_dewete:
	dwm_cwient_buffew_dewete(buffew);

	wetuwn EWW_PTW(wet);
}

/**
 * dwm_cwient_buffew_vmap - Map DWM cwient buffew into addwess space
 * @buffew: DWM cwient buffew
 * @map_copy: Wetuwns the mapped memowy's addwess
 *
 * This function maps a cwient buffew into kewnew addwess space. If the
 * buffew is awweady mapped, it wetuwns the existing mapping's addwess.
 *
 * Cwient buffew mappings awe not wef'counted. Each caww to
 * dwm_cwient_buffew_vmap() shouwd be fowwowed by a caww to
 * dwm_cwient_buffew_vunmap(); ow the cwient buffew shouwd be mapped
 * thwoughout its wifetime.
 *
 * The wetuwned addwess is a copy of the intewnaw vawue. In contwast to
 * othew vmap intewfaces, you don't need it fow the cwient's vunmap
 * function. So you can modify it at wiww duwing bwit and dwaw opewations.
 *
 * Wetuwns:
 *	0 on success, ow a negative ewwno code othewwise.
 */
int
dwm_cwient_buffew_vmap(stwuct dwm_cwient_buffew *buffew,
		       stwuct iosys_map *map_copy)
{
	stwuct iosys_map *map = &buffew->map;
	int wet;

	/*
	 * FIXME: The dependency on GEM hewe isn't wequiwed, we couwd
	 * convewt the dwivew handwe to a dma-buf instead and use the
	 * backend-agnostic dma-buf vmap suppowt instead. This wouwd
	 * wequiwe that the handwe2fd pwime ioctw is wewowked to puww the
	 * fd_instaww step out of the dwivew backend hooks, to make that
	 * finaw step optionaw fow intewnaw usews.
	 */
	wet = dwm_gem_vmap_unwocked(buffew->gem, map);
	if (wet)
		wetuwn wet;

	*map_copy = *map;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_cwient_buffew_vmap);

/**
 * dwm_cwient_buffew_vunmap - Unmap DWM cwient buffew
 * @buffew: DWM cwient buffew
 *
 * This function wemoves a cwient buffew's memowy mapping. Cawwing this
 * function is onwy wequiwed by cwients that manage theiw buffew mappings
 * by themsewves.
 */
void dwm_cwient_buffew_vunmap(stwuct dwm_cwient_buffew *buffew)
{
	stwuct iosys_map *map = &buffew->map;

	dwm_gem_vunmap_unwocked(buffew->gem, map);
}
EXPOWT_SYMBOW(dwm_cwient_buffew_vunmap);

static void dwm_cwient_buffew_wmfb(stwuct dwm_cwient_buffew *buffew)
{
	int wet;

	if (!buffew->fb)
		wetuwn;

	wet = dwm_mode_wmfb(buffew->cwient->dev, buffew->fb->base.id, buffew->cwient->fiwe);
	if (wet)
		dwm_eww(buffew->cwient->dev,
			"Ewwow wemoving FB:%u (%d)\n", buffew->fb->base.id, wet);

	buffew->fb = NUWW;
}

static int dwm_cwient_buffew_addfb(stwuct dwm_cwient_buffew *buffew,
				   u32 width, u32 height, u32 fowmat,
				   u32 handwe)
{
	stwuct dwm_cwient_dev *cwient = buffew->cwient;
	stwuct dwm_mode_fb_cmd2 fb_weq = { };
	int wet;

	fb_weq.width = width;
	fb_weq.height = height;
	fb_weq.pixew_fowmat = fowmat;
	fb_weq.handwes[0] = handwe;
	fb_weq.pitches[0] = buffew->pitch;

	wet = dwm_mode_addfb2(cwient->dev, &fb_weq, cwient->fiwe);
	if (wet)
		wetuwn wet;

	buffew->fb = dwm_fwamebuffew_wookup(cwient->dev, buffew->cwient->fiwe, fb_weq.fb_id);
	if (WAWN_ON(!buffew->fb))
		wetuwn -ENOENT;

	/* dwop the wefewence we picked up in fwamebuffew wookup */
	dwm_fwamebuffew_put(buffew->fb);

	stwscpy(buffew->fb->comm, cwient->name, TASK_COMM_WEN);

	wetuwn 0;
}

/**
 * dwm_cwient_fwamebuffew_cweate - Cweate a cwient fwamebuffew
 * @cwient: DWM cwient
 * @width: Fwamebuffew width
 * @height: Fwamebuffew height
 * @fowmat: Buffew fowmat
 *
 * This function cweates a &dwm_cwient_buffew which consists of a
 * &dwm_fwamebuffew backed by a dumb buffew.
 * Caww dwm_cwient_fwamebuffew_dewete() to fwee the buffew.
 *
 * Wetuwns:
 * Pointew to a cwient buffew ow an ewwow pointew on faiwuwe.
 */
stwuct dwm_cwient_buffew *
dwm_cwient_fwamebuffew_cweate(stwuct dwm_cwient_dev *cwient, u32 width, u32 height, u32 fowmat)
{
	stwuct dwm_cwient_buffew *buffew;
	u32 handwe;
	int wet;

	buffew = dwm_cwient_buffew_cweate(cwient, width, height, fowmat,
					  &handwe);
	if (IS_EWW(buffew))
		wetuwn buffew;

	wet = dwm_cwient_buffew_addfb(buffew, width, height, fowmat, handwe);

	/*
	 * The handwe is onwy needed fow cweating the fwamebuffew, destwoy it
	 * again to sowve a ciwcuwaw dependency shouwd anybody expowt the GEM
	 * object as DMA-buf. The fwamebuffew and ouw buffew stwuctuwe awe stiww
	 * howding wefewences to the GEM object to pwevent its destwuction.
	 */
	dwm_mode_destwoy_dumb(cwient->dev, handwe, cwient->fiwe);

	if (wet) {
		dwm_cwient_buffew_dewete(buffew);
		wetuwn EWW_PTW(wet);
	}

	wetuwn buffew;
}
EXPOWT_SYMBOW(dwm_cwient_fwamebuffew_cweate);

/**
 * dwm_cwient_fwamebuffew_dewete - Dewete a cwient fwamebuffew
 * @buffew: DWM cwient buffew (can be NUWW)
 */
void dwm_cwient_fwamebuffew_dewete(stwuct dwm_cwient_buffew *buffew)
{
	if (!buffew)
		wetuwn;

	dwm_cwient_buffew_wmfb(buffew);
	dwm_cwient_buffew_dewete(buffew);
}
EXPOWT_SYMBOW(dwm_cwient_fwamebuffew_dewete);

/**
 * dwm_cwient_fwamebuffew_fwush - Manuawwy fwush cwient fwamebuffew
 * @buffew: DWM cwient buffew (can be NUWW)
 * @wect: Damage wectangwe (if NUWW fwushes aww)
 *
 * This cawws &dwm_fwamebuffew_funcs->diwty (if pwesent) to fwush buffew changes
 * fow dwivews that need it.
 *
 * Wetuwns:
 * Zewo on success ow negative ewwow code on faiwuwe.
 */
int dwm_cwient_fwamebuffew_fwush(stwuct dwm_cwient_buffew *buffew, stwuct dwm_wect *wect)
{
	if (!buffew || !buffew->fb || !buffew->fb->funcs->diwty)
		wetuwn 0;

	if (wect) {
		stwuct dwm_cwip_wect cwip = {
			.x1 = wect->x1,
			.y1 = wect->y1,
			.x2 = wect->x2,
			.y2 = wect->y2,
		};

		wetuwn buffew->fb->funcs->diwty(buffew->fb, buffew->cwient->fiwe,
						0, 0, &cwip, 1);
	}

	wetuwn buffew->fb->funcs->diwty(buffew->fb, buffew->cwient->fiwe,
					0, 0, NUWW, 0);
}
EXPOWT_SYMBOW(dwm_cwient_fwamebuffew_fwush);

#ifdef CONFIG_DEBUG_FS
static int dwm_cwient_debugfs_intewnaw_cwients(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	stwuct dwm_cwient_dev *cwient;

	mutex_wock(&dev->cwientwist_mutex);
	wist_fow_each_entwy(cwient, &dev->cwientwist, wist)
		dwm_pwintf(&p, "%s\n", cwient->name);
	mutex_unwock(&dev->cwientwist_mutex);

	wetuwn 0;
}

static const stwuct dwm_debugfs_info dwm_cwient_debugfs_wist[] = {
	{ "intewnaw_cwients", dwm_cwient_debugfs_intewnaw_cwients, 0 },
};

void dwm_cwient_debugfs_init(stwuct dwm_device *dev)
{
	dwm_debugfs_add_fiwes(dev, dwm_cwient_debugfs_wist,
			      AWWAY_SIZE(dwm_cwient_debugfs_wist));
}
#endif
