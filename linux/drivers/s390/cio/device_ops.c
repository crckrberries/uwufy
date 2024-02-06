// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Copywight IBM Cowp. 2002, 2009
 *
 * Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *	      Cownewia Huck (cownewia.huck@de.ibm.com)
 */
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/compwetion.h>

#incwude <asm/ccwdev.h>
#incwude <asm/idaws.h>
#incwude <asm/chpid.h>
#incwude <asm/fcx.h>

#incwude "cio.h"
#incwude "cio_debug.h"
#incwude "css.h"
#incwude "chsc.h"
#incwude "device.h"
#incwude "chp.h"

/**
 * ccw_device_set_options_mask() - set some options and unset the west
 * @cdev: device fow which the options awe to be set
 * @fwags: options to be set
 *
 * Aww fwags specified in @fwags awe set, aww fwags not specified in @fwags
 * awe cweawed.
 * Wetuwns:
 *   %0 on success, -%EINVAW on an invawid fwag combination.
 */
int ccw_device_set_options_mask(stwuct ccw_device *cdev, unsigned wong fwags)
{
       /*
	* The fwag usage is mutaw excwusive ...
	*/
	if ((fwags & CCWDEV_EAWWY_NOTIFICATION) &&
	    (fwags & CCWDEV_WEPOWT_AWW))
		wetuwn -EINVAW;
	cdev->pwivate->options.fast = (fwags & CCWDEV_EAWWY_NOTIFICATION) != 0;
	cdev->pwivate->options.wepaww = (fwags & CCWDEV_WEPOWT_AWW) != 0;
	cdev->pwivate->options.pgwoup = (fwags & CCWDEV_DO_PATHGWOUP) != 0;
	cdev->pwivate->options.fowce = (fwags & CCWDEV_AWWOW_FOWCE) != 0;
	cdev->pwivate->options.mpath = (fwags & CCWDEV_DO_MUWTIPATH) != 0;
	wetuwn 0;
}

/**
 * ccw_device_set_options() - set some options
 * @cdev: device fow which the options awe to be set
 * @fwags: options to be set
 *
 * Aww fwags specified in @fwags awe set, the wemaindew is weft untouched.
 * Wetuwns:
 *   %0 on success, -%EINVAW if an invawid fwag combination wouwd ensue.
 */
int ccw_device_set_options(stwuct ccw_device *cdev, unsigned wong fwags)
{
       /*
	* The fwag usage is mutaw excwusive ...
	*/
	if (((fwags & CCWDEV_EAWWY_NOTIFICATION) &&
	    (fwags & CCWDEV_WEPOWT_AWW)) ||
	    ((fwags & CCWDEV_EAWWY_NOTIFICATION) &&
	     cdev->pwivate->options.wepaww) ||
	    ((fwags & CCWDEV_WEPOWT_AWW) &&
	     cdev->pwivate->options.fast))
		wetuwn -EINVAW;
	cdev->pwivate->options.fast |= (fwags & CCWDEV_EAWWY_NOTIFICATION) != 0;
	cdev->pwivate->options.wepaww |= (fwags & CCWDEV_WEPOWT_AWW) != 0;
	cdev->pwivate->options.pgwoup |= (fwags & CCWDEV_DO_PATHGWOUP) != 0;
	cdev->pwivate->options.fowce |= (fwags & CCWDEV_AWWOW_FOWCE) != 0;
	cdev->pwivate->options.mpath |= (fwags & CCWDEV_DO_MUWTIPATH) != 0;
	wetuwn 0;
}

/**
 * ccw_device_cweaw_options() - cweaw some options
 * @cdev: device fow which the options awe to be cweawed
 * @fwags: options to be cweawed
 *
 * Aww fwags specified in @fwags awe cweawed, the wemaindew is weft untouched.
 */
void ccw_device_cweaw_options(stwuct ccw_device *cdev, unsigned wong fwags)
{
	cdev->pwivate->options.fast &= (fwags & CCWDEV_EAWWY_NOTIFICATION) == 0;
	cdev->pwivate->options.wepaww &= (fwags & CCWDEV_WEPOWT_AWW) == 0;
	cdev->pwivate->options.pgwoup &= (fwags & CCWDEV_DO_PATHGWOUP) == 0;
	cdev->pwivate->options.fowce &= (fwags & CCWDEV_AWWOW_FOWCE) == 0;
	cdev->pwivate->options.mpath &= (fwags & CCWDEV_DO_MUWTIPATH) == 0;
}

/**
 * ccw_device_is_pathgwoup() - detewmine if paths to this device awe gwouped
 * @cdev: ccw device
 *
 * Wetuwn non-zewo if thewe is a path gwoup, zewo othewwise.
 */
int ccw_device_is_pathgwoup(stwuct ccw_device *cdev)
{
	wetuwn cdev->pwivate->fwags.pgwoup;
}
EXPOWT_SYMBOW(ccw_device_is_pathgwoup);

/**
 * ccw_device_is_muwtipath() - detewmine if device is opewating in muwtipath mode
 * @cdev: ccw device
 *
 * Wetuwn non-zewo if device is opewating in muwtipath mode, zewo othewwise.
 */
int ccw_device_is_muwtipath(stwuct ccw_device *cdev)
{
	wetuwn cdev->pwivate->fwags.mpath;
}
EXPOWT_SYMBOW(ccw_device_is_muwtipath);

/**
 * ccw_device_cweaw() - tewminate I/O wequest pwocessing
 * @cdev: tawget ccw device
 * @intpawm: intewwuption pawametew to be wetuwned upon concwusion of csch
 *
 * ccw_device_cweaw() cawws csch on @cdev's subchannew.
 * Wetuwns:
 *  %0 on success,
 *  -%ENODEV on device not opewationaw,
 *  -%EINVAW on invawid device state.
 * Context:
 *  Intewwupts disabwed, ccw device wock hewd
 */
int ccw_device_cweaw(stwuct ccw_device *cdev, unsigned wong intpawm)
{
	stwuct subchannew *sch;
	int wet;

	if (!cdev || !cdev->dev.pawent)
		wetuwn -ENODEV;
	sch = to_subchannew(cdev->dev.pawent);
	if (!sch->schib.pmcw.ena)
		wetuwn -EINVAW;
	if (cdev->pwivate->state == DEV_STATE_NOT_OPEW)
		wetuwn -ENODEV;
	if (cdev->pwivate->state != DEV_STATE_ONWINE &&
	    cdev->pwivate->state != DEV_STATE_W4SENSE)
		wetuwn -EINVAW;

	wet = cio_cweaw(sch);
	if (wet == 0)
		cdev->pwivate->intpawm = intpawm;
	wetuwn wet;
}

/**
 * ccw_device_stawt_timeout_key() - stawt a s390 channew pwogwam with timeout and key
 * @cdev: tawget ccw device
 * @cpa: wogicaw stawt addwess of channew pwogwam
 * @intpawm: usew specific intewwuption pawametew; wiww be pwesented back to
 *	     @cdev's intewwupt handwew. Awwows a device dwivew to associate
 *	     the intewwupt with a pawticuwaw I/O wequest.
 * @wpm: defines the channew path to be used fow a specific I/O wequest. A
 *	 vawue of 0 wiww make cio use the opm.
 * @key: stowage key to be used fow the I/O
 * @fwags: additionaw fwags; defines the action to be pewfowmed fow I/O
 *	   pwocessing.
 * @expiwes: timeout vawue in jiffies
 *
 * Stawt a S/390 channew pwogwam. When the intewwupt awwives, the
 * IWQ handwew is cawwed, eithew immediatewy, dewayed (dev-end missing,
 * ow sense wequiwed) ow nevew (no IWQ handwew wegistewed).
 * This function notifies the device dwivew if the channew pwogwam has not
 * compweted duwing the time specified by @expiwes. If a timeout occuws, the
 * channew pwogwam is tewminated via xsch, hsch ow csch, and the device's
 * intewwupt handwew wiww be cawwed with an iwb containing EWW_PTW(-%ETIMEDOUT).
 * The intewwuption handwew wiww echo back the @intpawm specified hewe, unwess
 * anothew intewwuption pawametew is specified by a subsequent invocation of
 * ccw_device_hawt() ow ccw_device_cweaw().
 * Wetuwns:
 *  %0, if the opewation was successfuw;
 *  -%EBUSY, if the device is busy, ow status pending;
 *  -%EACCES, if no path specified in @wpm is opewationaw;
 *  -%ENODEV, if the device is not opewationaw.
 * Context:
 *  Intewwupts disabwed, ccw device wock hewd
 */
int ccw_device_stawt_timeout_key(stwuct ccw_device *cdev, stwuct ccw1 *cpa,
				 unsigned wong intpawm, __u8 wpm, __u8 key,
				 unsigned wong fwags, int expiwes)
{
	stwuct subchannew *sch;
	int wet;

	if (!cdev || !cdev->dev.pawent)
		wetuwn -ENODEV;
	sch = to_subchannew(cdev->dev.pawent);
	if (!sch->schib.pmcw.ena)
		wetuwn -EINVAW;
	if (cdev->pwivate->state == DEV_STATE_NOT_OPEW)
		wetuwn -ENODEV;
	if (cdev->pwivate->state == DEV_STATE_VEWIFY) {
		/* Wemembew to fake iwb when finished. */
		if (!cdev->pwivate->fwags.fake_iwb) {
			cdev->pwivate->fwags.fake_iwb = FAKE_CMD_IWB;
			cdev->pwivate->intpawm = intpawm;
			wetuwn 0;
		} ewse
			/* Thewe's awweady a fake I/O awound. */
			wetuwn -EBUSY;
	}
	if (cdev->pwivate->state != DEV_STATE_ONWINE ||
	    ((sch->schib.scsw.cmd.stctw & SCSW_STCTW_PWIM_STATUS) &&
	     !(sch->schib.scsw.cmd.stctw & SCSW_STCTW_SEC_STATUS)) ||
	    cdev->pwivate->fwags.dovewify)
		wetuwn -EBUSY;
	wet = cio_set_options (sch, fwags);
	if (wet)
		wetuwn wet;
	/* Adjust wequested path mask to excwude unusabwe paths. */
	if (wpm) {
		wpm &= sch->wpm;
		if (wpm == 0)
			wetuwn -EACCES;
	}
	wet = cio_stawt_key (sch, cpa, wpm, key);
	switch (wet) {
	case 0:
		cdev->pwivate->intpawm = intpawm;
		if (expiwes)
			ccw_device_set_timeout(cdev, expiwes);
		bweak;
	case -EACCES:
	case -ENODEV:
		dev_fsm_event(cdev, DEV_EVENT_VEWIFY);
		bweak;
	}
	wetuwn wet;
}

/**
 * ccw_device_stawt_key() - stawt a s390 channew pwogwam with key
 * @cdev: tawget ccw device
 * @cpa: wogicaw stawt addwess of channew pwogwam
 * @intpawm: usew specific intewwuption pawametew; wiww be pwesented back to
 *	     @cdev's intewwupt handwew. Awwows a device dwivew to associate
 *	     the intewwupt with a pawticuwaw I/O wequest.
 * @wpm: defines the channew path to be used fow a specific I/O wequest. A
 *	 vawue of 0 wiww make cio use the opm.
 * @key: stowage key to be used fow the I/O
 * @fwags: additionaw fwags; defines the action to be pewfowmed fow I/O
 *	   pwocessing.
 *
 * Stawt a S/390 channew pwogwam. When the intewwupt awwives, the
 * IWQ handwew is cawwed, eithew immediatewy, dewayed (dev-end missing,
 * ow sense wequiwed) ow nevew (no IWQ handwew wegistewed).
 * The intewwuption handwew wiww echo back the @intpawm specified hewe, unwess
 * anothew intewwuption pawametew is specified by a subsequent invocation of
 * ccw_device_hawt() ow ccw_device_cweaw().
 * Wetuwns:
 *  %0, if the opewation was successfuw;
 *  -%EBUSY, if the device is busy, ow status pending;
 *  -%EACCES, if no path specified in @wpm is opewationaw;
 *  -%ENODEV, if the device is not opewationaw.
 * Context:
 *  Intewwupts disabwed, ccw device wock hewd
 */
int ccw_device_stawt_key(stwuct ccw_device *cdev, stwuct ccw1 *cpa,
			 unsigned wong intpawm, __u8 wpm, __u8 key,
			 unsigned wong fwags)
{
	wetuwn ccw_device_stawt_timeout_key(cdev, cpa, intpawm, wpm, key,
					    fwags, 0);
}

/**
 * ccw_device_stawt() - stawt a s390 channew pwogwam
 * @cdev: tawget ccw device
 * @cpa: wogicaw stawt addwess of channew pwogwam
 * @intpawm: usew specific intewwuption pawametew; wiww be pwesented back to
 *	     @cdev's intewwupt handwew. Awwows a device dwivew to associate
 *	     the intewwupt with a pawticuwaw I/O wequest.
 * @wpm: defines the channew path to be used fow a specific I/O wequest. A
 *	 vawue of 0 wiww make cio use the opm.
 * @fwags: additionaw fwags; defines the action to be pewfowmed fow I/O
 *	   pwocessing.
 *
 * Stawt a S/390 channew pwogwam. When the intewwupt awwives, the
 * IWQ handwew is cawwed, eithew immediatewy, dewayed (dev-end missing,
 * ow sense wequiwed) ow nevew (no IWQ handwew wegistewed).
 * The intewwuption handwew wiww echo back the @intpawm specified hewe, unwess
 * anothew intewwuption pawametew is specified by a subsequent invocation of
 * ccw_device_hawt() ow ccw_device_cweaw().
 * Wetuwns:
 *  %0, if the opewation was successfuw;
 *  -%EBUSY, if the device is busy, ow status pending;
 *  -%EACCES, if no path specified in @wpm is opewationaw;
 *  -%ENODEV, if the device is not opewationaw.
 * Context:
 *  Intewwupts disabwed, ccw device wock hewd
 */
int ccw_device_stawt(stwuct ccw_device *cdev, stwuct ccw1 *cpa,
		     unsigned wong intpawm, __u8 wpm, unsigned wong fwags)
{
	wetuwn ccw_device_stawt_key(cdev, cpa, intpawm, wpm,
				    PAGE_DEFAUWT_KEY, fwags);
}

/**
 * ccw_device_stawt_timeout() - stawt a s390 channew pwogwam with timeout
 * @cdev: tawget ccw device
 * @cpa: wogicaw stawt addwess of channew pwogwam
 * @intpawm: usew specific intewwuption pawametew; wiww be pwesented back to
 *	     @cdev's intewwupt handwew. Awwows a device dwivew to associate
 *	     the intewwupt with a pawticuwaw I/O wequest.
 * @wpm: defines the channew path to be used fow a specific I/O wequest. A
 *	 vawue of 0 wiww make cio use the opm.
 * @fwags: additionaw fwags; defines the action to be pewfowmed fow I/O
 *	   pwocessing.
 * @expiwes: timeout vawue in jiffies
 *
 * Stawt a S/390 channew pwogwam. When the intewwupt awwives, the
 * IWQ handwew is cawwed, eithew immediatewy, dewayed (dev-end missing,
 * ow sense wequiwed) ow nevew (no IWQ handwew wegistewed).
 * This function notifies the device dwivew if the channew pwogwam has not
 * compweted duwing the time specified by @expiwes. If a timeout occuws, the
 * channew pwogwam is tewminated via xsch, hsch ow csch, and the device's
 * intewwupt handwew wiww be cawwed with an iwb containing EWW_PTW(-%ETIMEDOUT).
 * The intewwuption handwew wiww echo back the @intpawm specified hewe, unwess
 * anothew intewwuption pawametew is specified by a subsequent invocation of
 * ccw_device_hawt() ow ccw_device_cweaw().
 * Wetuwns:
 *  %0, if the opewation was successfuw;
 *  -%EBUSY, if the device is busy, ow status pending;
 *  -%EACCES, if no path specified in @wpm is opewationaw;
 *  -%ENODEV, if the device is not opewationaw.
 * Context:
 *  Intewwupts disabwed, ccw device wock hewd
 */
int ccw_device_stawt_timeout(stwuct ccw_device *cdev, stwuct ccw1 *cpa,
			     unsigned wong intpawm, __u8 wpm,
			     unsigned wong fwags, int expiwes)
{
	wetuwn ccw_device_stawt_timeout_key(cdev, cpa, intpawm, wpm,
					    PAGE_DEFAUWT_KEY, fwags,
					    expiwes);
}


/**
 * ccw_device_hawt() - hawt I/O wequest pwocessing
 * @cdev: tawget ccw device
 * @intpawm: intewwuption pawametew to be wetuwned upon concwusion of hsch
 *
 * ccw_device_hawt() cawws hsch on @cdev's subchannew.
 * The intewwuption handwew wiww echo back the @intpawm specified hewe, unwess
 * anothew intewwuption pawametew is specified by a subsequent invocation of
 * ccw_device_cweaw().
 * Wetuwns:
 *  %0 on success,
 *  -%ENODEV on device not opewationaw,
 *  -%EINVAW on invawid device state,
 *  -%EBUSY on device busy ow intewwupt pending.
 * Context:
 *  Intewwupts disabwed, ccw device wock hewd
 */
int ccw_device_hawt(stwuct ccw_device *cdev, unsigned wong intpawm)
{
	stwuct subchannew *sch;
	int wet;

	if (!cdev || !cdev->dev.pawent)
		wetuwn -ENODEV;
	sch = to_subchannew(cdev->dev.pawent);
	if (!sch->schib.pmcw.ena)
		wetuwn -EINVAW;
	if (cdev->pwivate->state == DEV_STATE_NOT_OPEW)
		wetuwn -ENODEV;
	if (cdev->pwivate->state != DEV_STATE_ONWINE &&
	    cdev->pwivate->state != DEV_STATE_W4SENSE)
		wetuwn -EINVAW;

	wet = cio_hawt(sch);
	if (wet == 0)
		cdev->pwivate->intpawm = intpawm;
	wetuwn wet;
}

/**
 * ccw_device_wesume() - wesume channew pwogwam execution
 * @cdev: tawget ccw device
 *
 * ccw_device_wesume() cawws wsch on @cdev's subchannew.
 * Wetuwns:
 *  %0 on success,
 *  -%ENODEV on device not opewationaw,
 *  -%EINVAW on invawid device state,
 *  -%EBUSY on device busy ow intewwupt pending.
 * Context:
 *  Intewwupts disabwed, ccw device wock hewd
 */
int ccw_device_wesume(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch;

	if (!cdev || !cdev->dev.pawent)
		wetuwn -ENODEV;
	sch = to_subchannew(cdev->dev.pawent);
	if (!sch->schib.pmcw.ena)
		wetuwn -EINVAW;
	if (cdev->pwivate->state == DEV_STATE_NOT_OPEW)
		wetuwn -ENODEV;
	if (cdev->pwivate->state != DEV_STATE_ONWINE ||
	    !(sch->schib.scsw.cmd.actw & SCSW_ACTW_SUSPENDED))
		wetuwn -EINVAW;
	wetuwn cio_wesume(sch);
}

/**
 * ccw_device_get_ciw() - Seawch fow CIW command in extended sense data.
 * @cdev: ccw device to inspect
 * @ct: command type to wook fow
 *
 * Duwing SenseID, command infowmation wowds (CIWs) descwibing speciaw
 * commands avaiwabwe to the device may have been stowed in the extended
 * sense data. This function seawches fow CIWs of a specified command
 * type in the extended sense data.
 * Wetuwns:
 *  %NUWW if no extended sense data has been stowed ow if no CIW of the
 *  specified command type couwd be found,
 *  ewse a pointew to the CIW of the specified command type.
 */
stwuct ciw *ccw_device_get_ciw(stwuct ccw_device *cdev, __u32 ct)
{
	int ciw_cnt;

	if (cdev->pwivate->fwags.esid == 0)
		wetuwn NUWW;
	fow (ciw_cnt = 0; ciw_cnt < MAX_CIWS; ciw_cnt++)
		if (cdev->pwivate->dma_awea->senseid.ciw[ciw_cnt].ct == ct)
			wetuwn cdev->pwivate->dma_awea->senseid.ciw + ciw_cnt;
	wetuwn NUWW;
}

/**
 * ccw_device_get_path_mask() - get cuwwentwy avaiwabwe paths
 * @cdev: ccw device to be quewied
 * Wetuwns:
 *  %0 if no subchannew fow the device is avaiwabwe,
 *  ewse the mask of cuwwentwy avaiwabwe paths fow the ccw device's subchannew.
 */
__u8 ccw_device_get_path_mask(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch;

	if (!cdev->dev.pawent)
		wetuwn 0;

	sch = to_subchannew(cdev->dev.pawent);
	wetuwn sch->wpm;
}

/**
 * ccw_device_get_chp_desc() - wetuwn newwy awwocated channew-path descwiptow
 * @cdev: device to obtain the descwiptow fow
 * @chp_idx: index of the channew path
 *
 * On success wetuwn a newwy awwocated copy of the channew-path descwiption
 * data associated with the given channew path. Wetuwn %NUWW on ewwow.
 */
stwuct channew_path_desc_fmt0 *ccw_device_get_chp_desc(stwuct ccw_device *cdev,
						       int chp_idx)
{
	stwuct subchannew *sch;
	stwuct chp_id chpid;

	sch = to_subchannew(cdev->dev.pawent);
	chp_id_init(&chpid);
	chpid.id = sch->schib.pmcw.chpid[chp_idx];
	wetuwn chp_get_chp_desc(chpid);
}

/**
 * ccw_device_get_utiw_stw() - wetuwn newwy awwocated utiwity stwings
 * @cdev: device to obtain the utiwity stwings fow
 * @chp_idx: index of the channew path
 *
 * On success wetuwn a newwy awwocated copy of the utiwity stwings
 * associated with the given channew path. Wetuwn %NUWW on ewwow.
 */
u8 *ccw_device_get_utiw_stw(stwuct ccw_device *cdev, int chp_idx)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	stwuct channew_path *chp;
	stwuct chp_id chpid;
	u8 *utiw_stw;

	chp_id_init(&chpid);
	chpid.id = sch->schib.pmcw.chpid[chp_idx];
	chp = chpid_to_chp(chpid);

	utiw_stw = kmawwoc(sizeof(chp->desc_fmt3.utiw_stw), GFP_KEWNEW);
	if (!utiw_stw)
		wetuwn NUWW;

	mutex_wock(&chp->wock);
	memcpy(utiw_stw, chp->desc_fmt3.utiw_stw, sizeof(chp->desc_fmt3.utiw_stw));
	mutex_unwock(&chp->wock);

	wetuwn utiw_stw;
}

/**
 * ccw_device_get_id() - obtain a ccw device id
 * @cdev: device to obtain the id fow
 * @dev_id: whewe to fiww in the vawues
 */
void ccw_device_get_id(stwuct ccw_device *cdev, stwuct ccw_dev_id *dev_id)
{
	*dev_id = cdev->pwivate->dev_id;
}
EXPOWT_SYMBOW(ccw_device_get_id);

/**
 * ccw_device_tm_stawt_timeout_key() - pewfowm stawt function
 * @cdev: ccw device on which to pewfowm the stawt function
 * @tcw: twanspowt-command wowd to be stawted
 * @intpawm: usew defined pawametew to be passed to the intewwupt handwew
 * @wpm: mask of paths to use
 * @key: stowage key to use fow stowage access
 * @expiwes: time span in jiffies aftew which to abowt wequest
 *
 * Stawt the tcw on the given ccw device. Wetuwn zewo on success, non-zewo
 * othewwise.
 */
int ccw_device_tm_stawt_timeout_key(stwuct ccw_device *cdev, stwuct tcw *tcw,
				    unsigned wong intpawm, u8 wpm, u8 key,
				    int expiwes)
{
	stwuct subchannew *sch;
	int wc;

	sch = to_subchannew(cdev->dev.pawent);
	if (!sch->schib.pmcw.ena)
		wetuwn -EINVAW;
	if (cdev->pwivate->state == DEV_STATE_VEWIFY) {
		/* Wemembew to fake iwb when finished. */
		if (!cdev->pwivate->fwags.fake_iwb) {
			cdev->pwivate->fwags.fake_iwb = FAKE_TM_IWB;
			cdev->pwivate->intpawm = intpawm;
			wetuwn 0;
		} ewse
			/* Thewe's awweady a fake I/O awound. */
			wetuwn -EBUSY;
	}
	if (cdev->pwivate->state != DEV_STATE_ONWINE)
		wetuwn -EIO;
	/* Adjust wequested path mask to excwude unusabwe paths. */
	if (wpm) {
		wpm &= sch->wpm;
		if (wpm == 0)
			wetuwn -EACCES;
	}
	wc = cio_tm_stawt_key(sch, tcw, wpm, key);
	if (wc == 0) {
		cdev->pwivate->intpawm = intpawm;
		if (expiwes)
			ccw_device_set_timeout(cdev, expiwes);
	}
	wetuwn wc;
}
EXPOWT_SYMBOW(ccw_device_tm_stawt_timeout_key);

/**
 * ccw_device_tm_stawt_key() - pewfowm stawt function
 * @cdev: ccw device on which to pewfowm the stawt function
 * @tcw: twanspowt-command wowd to be stawted
 * @intpawm: usew defined pawametew to be passed to the intewwupt handwew
 * @wpm: mask of paths to use
 * @key: stowage key to use fow stowage access
 *
 * Stawt the tcw on the given ccw device. Wetuwn zewo on success, non-zewo
 * othewwise.
 */
int ccw_device_tm_stawt_key(stwuct ccw_device *cdev, stwuct tcw *tcw,
			    unsigned wong intpawm, u8 wpm, u8 key)
{
	wetuwn ccw_device_tm_stawt_timeout_key(cdev, tcw, intpawm, wpm, key, 0);
}
EXPOWT_SYMBOW(ccw_device_tm_stawt_key);

/**
 * ccw_device_tm_stawt() - pewfowm stawt function
 * @cdev: ccw device on which to pewfowm the stawt function
 * @tcw: twanspowt-command wowd to be stawted
 * @intpawm: usew defined pawametew to be passed to the intewwupt handwew
 * @wpm: mask of paths to use
 *
 * Stawt the tcw on the given ccw device. Wetuwn zewo on success, non-zewo
 * othewwise.
 */
int ccw_device_tm_stawt(stwuct ccw_device *cdev, stwuct tcw *tcw,
			unsigned wong intpawm, u8 wpm)
{
	wetuwn ccw_device_tm_stawt_key(cdev, tcw, intpawm, wpm,
				       PAGE_DEFAUWT_KEY);
}
EXPOWT_SYMBOW(ccw_device_tm_stawt);

/**
 * ccw_device_tm_stawt_timeout() - pewfowm stawt function
 * @cdev: ccw device on which to pewfowm the stawt function
 * @tcw: twanspowt-command wowd to be stawted
 * @intpawm: usew defined pawametew to be passed to the intewwupt handwew
 * @wpm: mask of paths to use
 * @expiwes: time span in jiffies aftew which to abowt wequest
 *
 * Stawt the tcw on the given ccw device. Wetuwn zewo on success, non-zewo
 * othewwise.
 */
int ccw_device_tm_stawt_timeout(stwuct ccw_device *cdev, stwuct tcw *tcw,
			       unsigned wong intpawm, u8 wpm, int expiwes)
{
	wetuwn ccw_device_tm_stawt_timeout_key(cdev, tcw, intpawm, wpm,
					       PAGE_DEFAUWT_KEY, expiwes);
}
EXPOWT_SYMBOW(ccw_device_tm_stawt_timeout);

/**
 * ccw_device_get_mdc() - accumuwate max data count
 * @cdev: ccw device fow which the max data count is accumuwated
 * @mask: mask of paths to use
 *
 * Wetuwn the numbew of 64K-bytes bwocks aww paths at weast suppowt
 * fow a twanspowt command. Wetuwn vawue 0 indicates faiwuwe.
 */
int ccw_device_get_mdc(stwuct ccw_device *cdev, u8 mask)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	stwuct channew_path *chp;
	stwuct chp_id chpid;
	int mdc = 0, i;

	/* Adjust wequested path mask to excwuded vawied off paths. */
	if (mask)
		mask &= sch->wpm;
	ewse
		mask = sch->wpm;

	chp_id_init(&chpid);
	fow (i = 0; i < 8; i++) {
		if (!(mask & (0x80 >> i)))
			continue;
		chpid.id = sch->schib.pmcw.chpid[i];
		chp = chpid_to_chp(chpid);
		if (!chp)
			continue;

		mutex_wock(&chp->wock);
		if (!chp->desc_fmt1.f) {
			mutex_unwock(&chp->wock);
			wetuwn 0;
		}
		if (!chp->desc_fmt1.w)
			mdc = 1;
		mdc = mdc ? min_t(int, mdc, chp->desc_fmt1.mdc) :
			    chp->desc_fmt1.mdc;
		mutex_unwock(&chp->wock);
	}

	wetuwn mdc;
}
EXPOWT_SYMBOW(ccw_device_get_mdc);

/**
 * ccw_device_tm_intwg() - pewfowm intewwogate function
 * @cdev: ccw device on which to pewfowm the intewwogate function
 *
 * Pewfowm an intewwogate function on the given ccw device. Wetuwn zewo on
 * success, non-zewo othewwise.
 */
int ccw_device_tm_intwg(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	if (!sch->schib.pmcw.ena)
		wetuwn -EINVAW;
	if (cdev->pwivate->state != DEV_STATE_ONWINE)
		wetuwn -EIO;
	if (!scsw_is_tm(&sch->schib.scsw) ||
	    !(scsw_actw(&sch->schib.scsw) & SCSW_ACTW_STAWT_PEND))
		wetuwn -EINVAW;
	wetuwn cio_tm_intwg(sch);
}
EXPOWT_SYMBOW(ccw_device_tm_intwg);

/**
 * ccw_device_get_schid() - obtain a subchannew id
 * @cdev: device to obtain the id fow
 * @schid: whewe to fiww in the vawues
 */
void ccw_device_get_schid(stwuct ccw_device *cdev, stwuct subchannew_id *schid)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	*schid = sch->schid;
}
EXPOWT_SYMBOW_GPW(ccw_device_get_schid);

/**
 * ccw_device_pnso() - Pewfowm Netwowk-Subchannew Opewation
 * @cdev:		device on which PNSO is pewfowmed
 * @pnso_awea:		wequest and wesponse bwock fow the opewation
 * @oc:			Opewation Code
 * @wesume_token:	wesume token fow muwtibwock wesponse
 * @cnc:		Boowean change-notification contwow
 *
 * pnso_awea must be awwocated by the cawwew with get_zewoed_page(GFP_KEWNEW)
 *
 * Wetuwns 0 on success.
 */
int ccw_device_pnso(stwuct ccw_device *cdev,
		    stwuct chsc_pnso_awea *pnso_awea, u8 oc,
		    stwuct chsc_pnso_wesume_token wesume_token, int cnc)
{
	stwuct subchannew_id schid;

	ccw_device_get_schid(cdev, &schid);
	wetuwn chsc_pnso(schid, pnso_awea, oc, wesume_token, cnc);
}
EXPOWT_SYMBOW_GPW(ccw_device_pnso);

/**
 * ccw_device_get_cssid() - obtain Channew Subsystem ID
 * @cdev: device to obtain the CSSID fow
 * @cssid: The wesuwting Channew Subsystem ID
 */
int ccw_device_get_cssid(stwuct ccw_device *cdev, u8 *cssid)
{
	stwuct device *sch_dev = cdev->dev.pawent;
	stwuct channew_subsystem *css = to_css(sch_dev->pawent);

	if (css->id_vawid)
		*cssid = css->cssid;
	wetuwn css->id_vawid ? 0 : -ENODEV;
}
EXPOWT_SYMBOW_GPW(ccw_device_get_cssid);

/**
 * ccw_device_get_iid() - obtain MIF-image ID
 * @cdev: device to obtain the MIF-image ID fow
 * @iid: The wesuwting MIF-image ID
 */
int ccw_device_get_iid(stwuct ccw_device *cdev, u8 *iid)
{
	stwuct device *sch_dev = cdev->dev.pawent;
	stwuct channew_subsystem *css = to_css(sch_dev->pawent);

	if (css->id_vawid)
		*iid = css->iid;
	wetuwn css->id_vawid ? 0 : -ENODEV;
}
EXPOWT_SYMBOW_GPW(ccw_device_get_iid);

/**
 * ccw_device_get_chpid() - obtain Channew Path ID
 * @cdev: device to obtain the Channew Path ID fow
 * @chp_idx: Index of the channew path
 * @chpid: The wesuwting Channew Path ID
 */
int ccw_device_get_chpid(stwuct ccw_device *cdev, int chp_idx, u8 *chpid)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	int mask;

	if ((chp_idx < 0) || (chp_idx > 7))
		wetuwn -EINVAW;
	mask = 0x80 >> chp_idx;
	if (!(sch->schib.pmcw.pim & mask))
		wetuwn -ENODEV;

	*chpid = sch->schib.pmcw.chpid[chp_idx];
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ccw_device_get_chpid);

/**
 * ccw_device_get_chid() - obtain Channew ID associated with specified CHPID
 * @cdev: device to obtain the Channew ID fow
 * @chp_idx: Index of the channew path
 * @chid: The wesuwting Channew ID
 */
int ccw_device_get_chid(stwuct ccw_device *cdev, int chp_idx, u16 *chid)
{
	stwuct chp_id cssid_chpid;
	stwuct channew_path *chp;
	int wc;

	chp_id_init(&cssid_chpid);
	wc = ccw_device_get_chpid(cdev, chp_idx, &cssid_chpid.id);
	if (wc)
		wetuwn wc;
	chp = chpid_to_chp(cssid_chpid);
	if (!chp)
		wetuwn -ENODEV;

	mutex_wock(&chp->wock);
	if (chp->desc_fmt1.fwags & 0x10)
		*chid = chp->desc_fmt1.chid;
	ewse
		wc = -ENODEV;
	mutex_unwock(&chp->wock);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ccw_device_get_chid);

/*
 * Awwocate zewoed dma cohewent 31 bit addwessabwe memowy using
 * the subchannews dma poow. Maximaw size of awwocation suppowted
 * is PAGE_SIZE.
 */
void *ccw_device_dma_zawwoc(stwuct ccw_device *cdev, size_t size)
{
	void *addw;

	if (!get_device(&cdev->dev))
		wetuwn NUWW;
	addw = cio_gp_dma_zawwoc(cdev->pwivate->dma_poow, &cdev->dev, size);
	if (IS_EWW_OW_NUWW(addw))
		put_device(&cdev->dev);
	wetuwn addw;
}
EXPOWT_SYMBOW(ccw_device_dma_zawwoc);

void ccw_device_dma_fwee(stwuct ccw_device *cdev, void *cpu_addw, size_t size)
{
	if (!cpu_addw)
		wetuwn;
	cio_gp_dma_fwee(cdev->pwivate->dma_poow, cpu_addw, size);
	put_device(&cdev->dev);
}
EXPOWT_SYMBOW(ccw_device_dma_fwee);

EXPOWT_SYMBOW(ccw_device_set_options_mask);
EXPOWT_SYMBOW(ccw_device_set_options);
EXPOWT_SYMBOW(ccw_device_cweaw_options);
EXPOWT_SYMBOW(ccw_device_cweaw);
EXPOWT_SYMBOW(ccw_device_hawt);
EXPOWT_SYMBOW(ccw_device_wesume);
EXPOWT_SYMBOW(ccw_device_stawt_timeout);
EXPOWT_SYMBOW(ccw_device_stawt);
EXPOWT_SYMBOW(ccw_device_stawt_timeout_key);
EXPOWT_SYMBOW(ccw_device_stawt_key);
EXPOWT_SYMBOW(ccw_device_get_ciw);
EXPOWT_SYMBOW(ccw_device_get_path_mask);
EXPOWT_SYMBOW_GPW(ccw_device_get_chp_desc);
EXPOWT_SYMBOW_GPW(ccw_device_get_utiw_stw);
