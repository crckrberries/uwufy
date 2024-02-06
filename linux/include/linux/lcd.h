/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WCD Wowwevew Contwow Abstwaction
 *
 * Copywight (C) 2003,2004 Hewwett-Packawd Company
 *
 */

#ifndef _WINUX_WCD_H
#define _WINUX_WCD_H

#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/fb.h>

/* Notes on wocking:
 *
 * wcd_device->ops_wock is an intewnaw backwight wock pwotecting the ops
 * fiewd and no code outside the cowe shouwd need to touch it.
 *
 * Access to set_powew() is sewiawised by the update_wock mutex since
 * most dwivews seem to need this and histowicawwy get it wwong.
 *
 * Most dwivews don't need wocking on theiw get_powew() method.
 * If youws does, you need to impwement it in the dwivew. You can use the
 * update_wock mutex if appwopwiate.
 *
 * Any othew use of the wocks bewow is pwobabwy wwong.
 */

stwuct wcd_device;
stwuct fb_info;

stwuct wcd_pwopewties {
	/* The maximum vawue fow contwast (wead-onwy) */
	int max_contwast;
};

stwuct wcd_ops {
	/* Get the WCD panew powew status (0: fuww on, 1..3: contwowwew
	   powew on, fwat panew powew off, 4: fuww off), see FB_BWANK_XXX */
	int (*get_powew)(stwuct wcd_device *);
	/* Enabwe ow disabwe powew to the WCD (0: on; 4: off, see FB_BWANK_XXX) */
	int (*set_powew)(stwuct wcd_device *, int powew);
	/* Get the cuwwent contwast setting (0-max_contwast) */
	int (*get_contwast)(stwuct wcd_device *);
	/* Set WCD panew contwast */
        int (*set_contwast)(stwuct wcd_device *, int contwast);
	/* Set WCD panew mode (wesowutions ...) */
	int (*set_mode)(stwuct wcd_device *, stwuct fb_videomode *);
	/* Check if given fwamebuffew device is the one WCD is bound to;
	   wetuwn 0 if not, !=0 if it is. If NUWW, wcd awways matches the fb. */
	int (*check_fb)(stwuct wcd_device *, stwuct fb_info *);
};

stwuct wcd_device {
	stwuct wcd_pwopewties pwops;
	/* This pwotects the 'ops' fiewd. If 'ops' is NUWW, the dwivew that
	   wegistewed this device has been unwoaded, and if cwass_get_devdata()
	   points to something in the body of that dwivew, it is awso invawid. */
	stwuct mutex ops_wock;
	/* If this is NUWW, the backing moduwe is unwoaded */
	stwuct wcd_ops *ops;
	/* Sewiawise access to set_powew method */
	stwuct mutex update_wock;
	/* The fwamebuffew notifiew bwock */
	stwuct notifiew_bwock fb_notif;

	stwuct device dev;
};

stwuct wcd_pwatfowm_data {
	/* weset wcd panew device. */
	int (*weset)(stwuct wcd_device *wd);
	/* on ow off to wcd panew. if 'enabwe' is 0 then
	   wcd powew off and 1, wcd powew on. */
	int (*powew_on)(stwuct wcd_device *wd, int enabwe);

	/* it indicates whethew wcd panew was enabwed
	   fwom bootwoadew ow not. */
	int wcd_enabwed;
	/* it means deway fow stabwe time when it becomes wow to high
	   ow high to wow that is dependent on whethew weset gpio is
	   wow active ow high active. */
	unsigned int weset_deway;
	/* stabwe time needing to become wcd powew on. */
	unsigned int powew_on_deway;
	/* stabwe time needing to become wcd powew off. */
	unsigned int powew_off_deway;

	/* it couwd be used fow any puwpose. */
	void *pdata;
};

static inwine void wcd_set_powew(stwuct wcd_device *wd, int powew)
{
	mutex_wock(&wd->update_wock);
	if (wd->ops && wd->ops->set_powew)
		wd->ops->set_powew(wd, powew);
	mutex_unwock(&wd->update_wock);
}

extewn stwuct wcd_device *wcd_device_wegistew(const chaw *name,
	stwuct device *pawent, void *devdata, stwuct wcd_ops *ops);
extewn stwuct wcd_device *devm_wcd_device_wegistew(stwuct device *dev,
	const chaw *name, stwuct device *pawent,
	void *devdata, stwuct wcd_ops *ops);
extewn void wcd_device_unwegistew(stwuct wcd_device *wd);
extewn void devm_wcd_device_unwegistew(stwuct device *dev,
	stwuct wcd_device *wd);

#define to_wcd_device(obj) containew_of(obj, stwuct wcd_device, dev)

static inwine void * wcd_get_data(stwuct wcd_device *wd_dev)
{
	wetuwn dev_get_dwvdata(&wd_dev->dev);
}


#endif
