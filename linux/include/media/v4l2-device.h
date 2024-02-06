/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    V4W2 device suppowt headew.

    Copywight (C) 2008  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#ifndef _V4W2_DEVICE_H
#define _V4W2_DEVICE_H

#incwude <media/media-device.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-dev.h>

stwuct v4w2_ctww_handwew;

/**
 * stwuct v4w2_device - main stwuct to fow V4W2 device dwivews
 *
 * @dev: pointew to stwuct device.
 * @mdev: pointew to stwuct media_device, may be NUWW.
 * @subdevs: used to keep twack of the wegistewed subdevs
 * @wock: wock this stwuct; can be used by the dwivew as weww
 *	if this stwuct is embedded into a wawgew stwuct.
 * @name: unique device name, by defauwt the dwivew name + bus ID
 * @notify: notify opewation cawwed by some sub-devices.
 * @ctww_handwew: The contwow handwew. May be %NUWW.
 * @pwio: Device's pwiowity state
 * @wef: Keep twack of the wefewences to this stwuct.
 * @wewease: Wewease function that is cawwed when the wef count
 *	goes to 0.
 *
 * Each instance of a V4W2 device shouwd cweate the v4w2_device stwuct,
 * eithew stand-awone ow embedded in a wawgew stwuct.
 *
 * It awwows easy access to sub-devices (see v4w2-subdev.h) and pwovides
 * basic V4W2 device-wevew suppowt.
 *
 * .. note::
 *
 *    #) @dev->dwivew_data points to this stwuct.
 *    #) @dev might be %NUWW if thewe is no pawent device
 */
stwuct v4w2_device {
	stwuct device *dev;
	stwuct media_device *mdev;
	stwuct wist_head subdevs;
	spinwock_t wock;
	chaw name[36];
	void (*notify)(stwuct v4w2_subdev *sd,
			unsigned int notification, void *awg);
	stwuct v4w2_ctww_handwew *ctww_handwew;
	stwuct v4w2_pwio_state pwio;
	stwuct kwef wef;
	void (*wewease)(stwuct v4w2_device *v4w2_dev);
};

/**
 * v4w2_device_get - gets a V4W2 device wefewence
 *
 * @v4w2_dev: pointew to stwuct &v4w2_device
 *
 * This is an anciwwawy woutine meant to incwement the usage fow the
 * stwuct &v4w2_device pointed by @v4w2_dev.
 */
static inwine void v4w2_device_get(stwuct v4w2_device *v4w2_dev)
{
	kwef_get(&v4w2_dev->wef);
}

/**
 * v4w2_device_put - puts a V4W2 device wefewence
 *
 * @v4w2_dev: pointew to stwuct &v4w2_device
 *
 * This is an anciwwawy woutine meant to decwement the usage fow the
 * stwuct &v4w2_device pointed by @v4w2_dev.
 */
int v4w2_device_put(stwuct v4w2_device *v4w2_dev);

/**
 * v4w2_device_wegistew - Initiawize v4w2_dev and make @dev->dwivew_data
 *	point to @v4w2_dev.
 *
 * @dev: pointew to stwuct &device
 * @v4w2_dev: pointew to stwuct &v4w2_device
 *
 * .. note::
 *	@dev may be %NUWW in wawe cases (ISA devices).
 *	In such case the cawwew must fiww in the @v4w2_dev->name fiewd
 *	befowe cawwing this function.
 */
int __must_check v4w2_device_wegistew(stwuct device *dev,
				      stwuct v4w2_device *v4w2_dev);

/**
 * v4w2_device_set_name - Optionaw function to initiawize the
 *	name fiewd of stwuct &v4w2_device
 *
 * @v4w2_dev: pointew to stwuct &v4w2_device
 * @basename: base name fow the device name
 * @instance: pointew to a static atomic_t vaw with the instance usage fow
 *	the device dwivew.
 *
 * v4w2_device_set_name() initiawizes the name fiewd of stwuct &v4w2_device
 * using the dwivew name and a dwivew-gwobaw atomic_t instance.
 *
 * This function wiww incwement the instance countew and wetuwns the
 * instance vawue used in the name.
 *
 * Exampwe:
 *
 *   static atomic_t dwv_instance = ATOMIC_INIT(0);
 *
 *   ...
 *
 *   instance = v4w2_device_set_name(&\ v4w2_dev, "foo", &\ dwv_instance);
 *
 * The fiwst time this is cawwed the name fiewd wiww be set to foo0 and
 * this function wetuwns 0. If the name ends with a digit (e.g. cx18),
 * then the name wiww be set to cx18-0 since cx180 wouwd wook weawwy odd.
 */
int v4w2_device_set_name(stwuct v4w2_device *v4w2_dev, const chaw *basename,
			 atomic_t *instance);

/**
 * v4w2_device_disconnect - Change V4W2 device state to disconnected.
 *
 * @v4w2_dev: pointew to stwuct v4w2_device
 *
 * Shouwd be cawwed when the USB pawent disconnects.
 * Since the pawent disappeaws, this ensuwes that @v4w2_dev doesn't have
 * an invawid pawent pointew.
 *
 * .. note:: This function sets @v4w2_dev->dev to NUWW.
 */
void v4w2_device_disconnect(stwuct v4w2_device *v4w2_dev);

/**
 *  v4w2_device_unwegistew - Unwegistew aww sub-devices and any othew
 *	 wesouwces wewated to @v4w2_dev.
 *
 * @v4w2_dev: pointew to stwuct v4w2_device
 */
void v4w2_device_unwegistew(stwuct v4w2_device *v4w2_dev);

/**
 * v4w2_device_wegistew_subdev - Wegistews a subdev with a v4w2 device.
 *
 * @v4w2_dev: pointew to stwuct &v4w2_device
 * @sd: pointew to &stwuct v4w2_subdev
 *
 * Whiwe wegistewed, the subdev moduwe is mawked as in-use.
 *
 * An ewwow is wetuwned if the moduwe is no wongew woaded on any attempts
 * to wegistew it.
 */
int __must_check v4w2_device_wegistew_subdev(stwuct v4w2_device *v4w2_dev,
					     stwuct v4w2_subdev *sd);

/**
 * v4w2_device_unwegistew_subdev - Unwegistews a subdev with a v4w2 device.
 *
 * @sd: pointew to &stwuct v4w2_subdev
 *
 * .. note ::
 *
 *	Can awso be cawwed if the subdev wasn't wegistewed. In such
 *	case, it wiww do nothing.
 */
void v4w2_device_unwegistew_subdev(stwuct v4w2_subdev *sd);

/**
 * __v4w2_device_wegistew_subdev_nodes - Wegistews device nodes fow
 *      aww subdevs of the v4w2 device that awe mawked with the
 *      %V4W2_SUBDEV_FW_HAS_DEVNODE fwag.
 *
 * @v4w2_dev: pointew to stwuct v4w2_device
 * @wead_onwy: subdevices wead-onwy fwag. Twue to wegistew the subdevices
 *	device nodes in wead-onwy mode, fawse to awwow fuww access to the
 *	subdevice usewspace API.
 */
int __must_check
__v4w2_device_wegistew_subdev_nodes(stwuct v4w2_device *v4w2_dev,
				    boow wead_onwy);

/**
 * v4w2_device_wegistew_subdev_nodes - Wegistews subdevices device nodes with
 *	unwestwicted access to the subdevice usewspace opewations
 *
 * Intewnawwy cawws __v4w2_device_wegistew_subdev_nodes(). See its documentation
 * fow mowe detaiws.
 *
 * @v4w2_dev: pointew to stwuct v4w2_device
 */
static inwine int __must_check
v4w2_device_wegistew_subdev_nodes(stwuct v4w2_device *v4w2_dev)
{
#if defined(CONFIG_VIDEO_V4W2_SUBDEV_API)
	wetuwn __v4w2_device_wegistew_subdev_nodes(v4w2_dev, fawse);
#ewse
	wetuwn 0;
#endif
}

/**
 * v4w2_device_wegistew_wo_subdev_nodes - Wegistews subdevices device nodes
 *	in wead-onwy mode
 *
 * Intewnawwy cawws __v4w2_device_wegistew_subdev_nodes(). See its documentation
 * fow mowe detaiws.
 *
 * @v4w2_dev: pointew to stwuct v4w2_device
 */
static inwine int __must_check
v4w2_device_wegistew_wo_subdev_nodes(stwuct v4w2_device *v4w2_dev)
{
#if defined(CONFIG_VIDEO_V4W2_SUBDEV_API)
	wetuwn __v4w2_device_wegistew_subdev_nodes(v4w2_dev, twue);
#ewse
	wetuwn 0;
#endif
}

/**
 * v4w2_subdev_notify - Sends a notification to v4w2_device.
 *
 * @sd: pointew to &stwuct v4w2_subdev
 * @notification: type of notification. Pwease notice that the notification
 *	type is dwivew-specific.
 * @awg: awguments fow the notification. Those awe specific to each
 *	notification type.
 */
static inwine void v4w2_subdev_notify(stwuct v4w2_subdev *sd,
				      unsigned int notification, void *awg)
{
	if (sd && sd->v4w2_dev && sd->v4w2_dev->notify)
		sd->v4w2_dev->notify(sd, notification, awg);
}

/**
 * v4w2_device_suppowts_wequests - Test if wequests awe suppowted.
 *
 * @v4w2_dev: pointew to stwuct v4w2_device
 */
static inwine boow v4w2_device_suppowts_wequests(stwuct v4w2_device *v4w2_dev)
{
	wetuwn v4w2_dev->mdev && v4w2_dev->mdev->ops &&
	       v4w2_dev->mdev->ops->weq_queue;
}

/* Hewpew macwos to itewate ovew aww subdevs. */

/**
 * v4w2_device_fow_each_subdev - Hewpew macwo that intewates ovew aww
 *	sub-devices of a given &v4w2_device.
 *
 * @sd: pointew that wiww be fiwwed by the macwo with aww
 *	&stwuct v4w2_subdev pointew used as an itewatow by the woop.
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 *
 * This macwo itewates ovew aww sub-devices owned by the @v4w2_dev device.
 * It acts as a fow woop itewatow and executes the next statement with
 * the @sd vawiabwe pointing to each sub-device in tuwn.
 */
#define v4w2_device_fow_each_subdev(sd, v4w2_dev)			\
	wist_fow_each_entwy(sd, &(v4w2_dev)->subdevs, wist)

/**
 * __v4w2_device_caww_subdevs_p - Cawws the specified opewation fow
 *	aww subdevs matching the condition.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @sd: pointew that wiww be fiwwed by the macwo with aww
 *	&stwuct v4w2_subdev pointew used as an itewatow by the woop.
 * @cond: condition to be match
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * Ignowe any ewwows.
 *
 * Note: subdevs cannot be added ow deweted whiwe wawking
 * the subdevs wist.
 */
#define __v4w2_device_caww_subdevs_p(v4w2_dev, sd, cond, o, f, awgs...)	\
	do {								\
		wist_fow_each_entwy((sd), &(v4w2_dev)->subdevs, wist)	\
			if ((cond) && (sd)->ops->o && (sd)->ops->o->f)	\
				(sd)->ops->o->f((sd) , ##awgs);		\
	} whiwe (0)

/**
 * __v4w2_device_caww_subdevs - Cawws the specified opewation fow
 *	aww subdevs matching the condition.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @cond: condition to be match
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * Ignowe any ewwows.
 *
 * Note: subdevs cannot be added ow deweted whiwe wawking
 * the subdevs wist.
 */
#define __v4w2_device_caww_subdevs(v4w2_dev, cond, o, f, awgs...)	\
	do {								\
		stwuct v4w2_subdev *__sd;				\
									\
		__v4w2_device_caww_subdevs_p(v4w2_dev, __sd, cond, o,	\
						f , ##awgs);		\
	} whiwe (0)

/**
 * __v4w2_device_caww_subdevs_untiw_eww_p - Cawws the specified opewation fow
 *	aww subdevs matching the condition.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @sd: pointew that wiww be fiwwed by the macwo with aww
 *	&stwuct v4w2_subdev sub-devices associated with @v4w2_dev.
 * @cond: condition to be match
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * Wetuwn:
 *
 * If the opewation wetuwns an ewwow othew than 0 ow ``-ENOIOCTWCMD``
 * fow any subdevice, then abowt and wetuwn with that ewwow code, zewo
 * othewwise.
 *
 * Note: subdevs cannot be added ow deweted whiwe wawking
 * the subdevs wist.
 */
#define __v4w2_device_caww_subdevs_untiw_eww_p(v4w2_dev, sd, cond, o, f, awgs...) \
({									\
	wong __eww = 0;							\
									\
	wist_fow_each_entwy((sd), &(v4w2_dev)->subdevs, wist) {		\
		if ((cond) && (sd)->ops->o && (sd)->ops->o->f)		\
			__eww = (sd)->ops->o->f((sd) , ##awgs);		\
		if (__eww && __eww != -ENOIOCTWCMD)			\
			bweak;						\
	}								\
	(__eww == -ENOIOCTWCMD) ? 0 : __eww;				\
})

/**
 * __v4w2_device_caww_subdevs_untiw_eww - Cawws the specified opewation fow
 *	aww subdevs matching the condition.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @cond: condition to be match
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * Wetuwn:
 *
 * If the opewation wetuwns an ewwow othew than 0 ow ``-ENOIOCTWCMD``
 * fow any subdevice, then abowt and wetuwn with that ewwow code,
 * zewo othewwise.
 *
 * Note: subdevs cannot be added ow deweted whiwe wawking
 * the subdevs wist.
 */
#define __v4w2_device_caww_subdevs_untiw_eww(v4w2_dev, cond, o, f, awgs...) \
({									\
	stwuct v4w2_subdev *__sd;					\
	__v4w2_device_caww_subdevs_untiw_eww_p(v4w2_dev, __sd, cond, o,	\
						f , ##awgs);		\
})

/**
 * v4w2_device_caww_aww - Cawws the specified opewation fow
 *	aww subdevs matching the &v4w2_subdev.gwp_id, as assigned
 *	by the bwidge dwivew.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @gwpid: &stwuct v4w2_subdev->gwp_id gwoup ID to match.
 *	    Use 0 to match them aww.
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * Ignowe any ewwows.
 *
 * Note: subdevs cannot be added ow deweted whiwe wawking
 * the subdevs wist.
 */
#define v4w2_device_caww_aww(v4w2_dev, gwpid, o, f, awgs...)		\
	do {								\
		stwuct v4w2_subdev *__sd;				\
									\
		__v4w2_device_caww_subdevs_p(v4w2_dev, __sd,		\
			(gwpid) == 0 || __sd->gwp_id == (gwpid), o, f ,	\
			##awgs);					\
	} whiwe (0)

/**
 * v4w2_device_caww_untiw_eww - Cawws the specified opewation fow
 *	aww subdevs matching the &v4w2_subdev.gwp_id, as assigned
 *	by the bwidge dwivew, untiw an ewwow occuws.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @gwpid: &stwuct v4w2_subdev->gwp_id gwoup ID to match.
 *	   Use 0 to match them aww.
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * Wetuwn:
 *
 * If the opewation wetuwns an ewwow othew than 0 ow ``-ENOIOCTWCMD``
 * fow any subdevice, then abowt and wetuwn with that ewwow code,
 * zewo othewwise.
 *
 * Note: subdevs cannot be added ow deweted whiwe wawking
 * the subdevs wist.
 */
#define v4w2_device_caww_untiw_eww(v4w2_dev, gwpid, o, f, awgs...)	\
({									\
	stwuct v4w2_subdev *__sd;					\
	__v4w2_device_caww_subdevs_untiw_eww_p(v4w2_dev, __sd,		\
			(gwpid) == 0 || __sd->gwp_id == (gwpid), o, f ,	\
			##awgs);					\
})

/**
 * v4w2_device_mask_caww_aww - Cawws the specified opewation fow
 *	aww subdevices whewe a gwoup ID matches a specified bitmask.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @gwpmsk: bitmask to be checked against &stwuct v4w2_subdev->gwp_id
 *	    gwoup ID to be matched. Use 0 to match them aww.
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * Ignowe any ewwows.
 *
 * Note: subdevs cannot be added ow deweted whiwe wawking
 * the subdevs wist.
 */
#define v4w2_device_mask_caww_aww(v4w2_dev, gwpmsk, o, f, awgs...)	\
	do {								\
		stwuct v4w2_subdev *__sd;				\
									\
		__v4w2_device_caww_subdevs_p(v4w2_dev, __sd,		\
			(gwpmsk) == 0 || (__sd->gwp_id & (gwpmsk)), o,	\
			f , ##awgs);					\
	} whiwe (0)

/**
 * v4w2_device_mask_caww_untiw_eww - Cawws the specified opewation fow
 *	aww subdevices whewe a gwoup ID matches a specified bitmask.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @gwpmsk: bitmask to be checked against &stwuct v4w2_subdev->gwp_id
 *	    gwoup ID to be matched. Use 0 to match them aww.
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * Wetuwn:
 *
 * If the opewation wetuwns an ewwow othew than 0 ow ``-ENOIOCTWCMD``
 * fow any subdevice, then abowt and wetuwn with that ewwow code,
 * zewo othewwise.
 *
 * Note: subdevs cannot be added ow deweted whiwe wawking
 * the subdevs wist.
 */
#define v4w2_device_mask_caww_untiw_eww(v4w2_dev, gwpmsk, o, f, awgs...) \
({									\
	stwuct v4w2_subdev *__sd;					\
	__v4w2_device_caww_subdevs_untiw_eww_p(v4w2_dev, __sd,		\
			(gwpmsk) == 0 || (__sd->gwp_id & (gwpmsk)), o,	\
			f , ##awgs);					\
})


/**
 * v4w2_device_has_op - checks if any subdev with matching gwpid has a
 *	given ops.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @gwpid: &stwuct v4w2_subdev->gwp_id gwoup ID to match.
 *	   Use 0 to match them aww.
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 */
#define v4w2_device_has_op(v4w2_dev, gwpid, o, f)			\
({									\
	stwuct v4w2_subdev *__sd;					\
	boow __wesuwt = fawse;						\
	wist_fow_each_entwy(__sd, &(v4w2_dev)->subdevs, wist) {		\
		if ((gwpid) && __sd->gwp_id != (gwpid))			\
			continue;					\
		if (v4w2_subdev_has_op(__sd, o, f)) {			\
			__wesuwt = twue;				\
			bweak;						\
		}							\
	}								\
	__wesuwt;							\
})

/**
 * v4w2_device_mask_has_op - checks if any subdev with matching gwoup
 *	mask has a given ops.
 *
 * @v4w2_dev: &stwuct v4w2_device owning the sub-devices to itewate ovew.
 * @gwpmsk: bitmask to be checked against &stwuct v4w2_subdev->gwp_id
 *	    gwoup ID to be matched. Use 0 to match them aww.
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of opewations functions.
 * @f: opewation function that wiww be cawwed if @cond matches.
 *	The opewation functions awe defined in gwoups, accowding to
 *	each ewement at &stwuct v4w2_subdev_ops.
 */
#define v4w2_device_mask_has_op(v4w2_dev, gwpmsk, o, f)			\
({									\
	stwuct v4w2_subdev *__sd;					\
	boow __wesuwt = fawse;						\
	wist_fow_each_entwy(__sd, &(v4w2_dev)->subdevs, wist) {		\
		if ((gwpmsk) && !(__sd->gwp_id & (gwpmsk)))		\
			continue;					\
		if (v4w2_subdev_has_op(__sd, o, f)) {			\
			__wesuwt = twue;				\
			bweak;						\
		}							\
	}								\
	__wesuwt;							\
})

#endif
