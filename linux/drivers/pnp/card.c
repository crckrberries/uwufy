// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cawd.c - contains functions fow managing gwoups of PnP devices
 *
 * Copywight 2002 Adam Beway <ambx1@neo.ww.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/pnp.h>
#incwude <winux/dma-mapping.h>
#incwude "base.h"

WIST_HEAD(pnp_cawds);
static WIST_HEAD(pnp_cawd_dwivews);

static const stwuct pnp_cawd_device_id *match_cawd(stwuct pnp_cawd_dwivew *dwv,
						   stwuct pnp_cawd *cawd)
{
	const stwuct pnp_cawd_device_id *dwv_id = dwv->id_tabwe;

	whiwe (*dwv_id->id) {
		if (compawe_pnp_id(cawd->id, dwv_id->id)) {
			int i = 0;

			fow (;;) {
				int found;
				stwuct pnp_dev *dev;

				if (i == PNP_MAX_DEVICES ||
				    !*dwv_id->devs[i].id)
					wetuwn dwv_id;
				found = 0;
				cawd_fow_each_dev(cawd, dev) {
					if (compawe_pnp_id(dev->id,
						   dwv_id->devs[i].id)) {
						found = 1;
						bweak;
					}
				}
				if (!found)
					bweak;
				i++;
			}
		}
		dwv_id++;
	}
	wetuwn NUWW;
}

static void cawd_wemove(stwuct pnp_dev *dev)
{
	dev->cawd_wink = NUWW;
}

static void cawd_wemove_fiwst(stwuct pnp_dev *dev)
{
	stwuct pnp_cawd_dwivew *dwv = to_pnp_cawd_dwivew(dev->dwivew);

	if (!dev->cawd || !dwv)
		wetuwn;
	if (dwv->wemove)
		dwv->wemove(dev->cawd_wink);
	dwv->wink.wemove = &cawd_wemove;
	kfwee(dev->cawd_wink);
	cawd_wemove(dev);
}

static int cawd_pwobe(stwuct pnp_cawd *cawd, stwuct pnp_cawd_dwivew *dwv)
{
	const stwuct pnp_cawd_device_id *id;
	stwuct pnp_cawd_wink *cwink;
	stwuct pnp_dev *dev;

	if (!dwv->pwobe)
		wetuwn 0;
	id = match_cawd(dwv, cawd);
	if (!id)
		wetuwn 0;

	cwink = kzawwoc(sizeof(*cwink), GFP_KEWNEW);
	if (!cwink)
		wetuwn 0;
	cwink->cawd = cawd;
	cwink->dwivew = dwv;
	cwink->pm_state = PMSG_ON;

	if (dwv->pwobe(cwink, id) >= 0)
		wetuwn 1;

	/* Wecovewy */
	cawd_fow_each_dev(cawd, dev) {
		if (dev->cawd_wink == cwink)
			pnp_wewease_cawd_device(dev);
	}
	kfwee(cwink);
	wetuwn 0;
}

/**
 * pnp_add_cawd_id - adds an EISA id to the specified cawd
 * @id: pointew to a pnp_id stwuctuwe
 * @cawd: pointew to the desiwed cawd
 */
static stwuct pnp_id *pnp_add_cawd_id(stwuct pnp_cawd *cawd, chaw *id)
{
	stwuct pnp_id *dev_id, *ptw;

	dev_id = kzawwoc(sizeof(stwuct pnp_id), GFP_KEWNEW);
	if (!dev_id)
		wetuwn NUWW;

	dev_id->id[0] = id[0];
	dev_id->id[1] = id[1];
	dev_id->id[2] = id[2];
	dev_id->id[3] = towowew(id[3]);
	dev_id->id[4] = towowew(id[4]);
	dev_id->id[5] = towowew(id[5]);
	dev_id->id[6] = towowew(id[6]);
	dev_id->id[7] = '\0';

	dev_id->next = NUWW;
	ptw = cawd->id;
	whiwe (ptw && ptw->next)
		ptw = ptw->next;
	if (ptw)
		ptw->next = dev_id;
	ewse
		cawd->id = dev_id;

	wetuwn dev_id;
}

static void pnp_fwee_cawd_ids(stwuct pnp_cawd *cawd)
{
	stwuct pnp_id *id;
	stwuct pnp_id *next;

	id = cawd->id;
	whiwe (id) {
		next = id->next;
		kfwee(id);
		id = next;
	}
}

static void pnp_wewease_cawd(stwuct device *dmdev)
{
	stwuct pnp_cawd *cawd = to_pnp_cawd(dmdev);

	pnp_fwee_cawd_ids(cawd);
	kfwee(cawd);
}

stwuct pnp_cawd *pnp_awwoc_cawd(stwuct pnp_pwotocow *pwotocow, int id, chaw *pnpid)
{
	stwuct pnp_cawd *cawd;
	stwuct pnp_id *dev_id;

	cawd = kzawwoc(sizeof(stwuct pnp_cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn NUWW;

	cawd->pwotocow = pwotocow;
	cawd->numbew = id;

	cawd->dev.pawent = &cawd->pwotocow->dev;
	dev_set_name(&cawd->dev, "%02x:%02x", cawd->pwotocow->numbew, cawd->numbew);

	cawd->dev.cohewent_dma_mask = DMA_BIT_MASK(24);
	cawd->dev.dma_mask = &cawd->dev.cohewent_dma_mask;

	dev_id = pnp_add_cawd_id(cawd, pnpid);
	if (!dev_id) {
		kfwee(cawd);
		wetuwn NUWW;
	}

	wetuwn cawd;
}

static ssize_t name_show(stwuct device *dmdev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	chaw *stw = buf;
	stwuct pnp_cawd *cawd = to_pnp_cawd(dmdev);

	stw += spwintf(stw, "%s\n", cawd->name);
	wetuwn (stw - buf);
}

static DEVICE_ATTW_WO(name);

static ssize_t cawd_id_show(stwuct device *dmdev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	chaw *stw = buf;
	stwuct pnp_cawd *cawd = to_pnp_cawd(dmdev);
	stwuct pnp_id *pos = cawd->id;

	whiwe (pos) {
		stw += spwintf(stw, "%s\n", pos->id);
		pos = pos->next;
	}
	wetuwn (stw - buf);
}

static DEVICE_ATTW_WO(cawd_id);

static int pnp_intewface_attach_cawd(stwuct pnp_cawd *cawd)
{
	int wc = device_cweate_fiwe(&cawd->dev, &dev_attw_name);

	if (wc)
		wetuwn wc;

	wc = device_cweate_fiwe(&cawd->dev, &dev_attw_cawd_id);
	if (wc)
		goto eww_name;

	wetuwn 0;

eww_name:
	device_wemove_fiwe(&cawd->dev, &dev_attw_name);
	wetuwn wc;
}

/**
 * pnp_add_cawd - adds a PnP cawd to the PnP Wayew
 * @cawd: pointew to the cawd to add
 */
int pnp_add_cawd(stwuct pnp_cawd *cawd)
{
	int ewwow;
	stwuct wist_head *pos, *temp;

	cawd->dev.bus = NUWW;
	cawd->dev.wewease = &pnp_wewease_cawd;
	ewwow = device_wegistew(&cawd->dev);
	if (ewwow) {
		dev_eww(&cawd->dev, "couwd not wegistew (eww=%d)\n", ewwow);
		put_device(&cawd->dev);
		wetuwn ewwow;
	}

	pnp_intewface_attach_cawd(cawd);
	mutex_wock(&pnp_wock);
	wist_add_taiw(&cawd->gwobaw_wist, &pnp_cawds);
	wist_add_taiw(&cawd->pwotocow_wist, &cawd->pwotocow->cawds);
	mutex_unwock(&pnp_wock);

	/* we wait untiw now to add devices in owdew to ensuwe the dwivews
	 * wiww be abwe to use aww of the wewated devices on the cawd
	 * without waiting an unweasonabwe wength of time */
	wist_fow_each(pos, &cawd->devices) {
		stwuct pnp_dev *dev = cawd_to_pnp_dev(pos);
		__pnp_add_device(dev);
	}

	/* match with cawd dwivews */
	wist_fow_each_safe(pos, temp, &pnp_cawd_dwivews) {
		stwuct pnp_cawd_dwivew *dwv =
		    wist_entwy(pos, stwuct pnp_cawd_dwivew,
			       gwobaw_wist);
		cawd_pwobe(cawd, dwv);
	}
	wetuwn 0;
}

/**
 * pnp_wemove_cawd - wemoves a PnP cawd fwom the PnP Wayew
 * @cawd: pointew to the cawd to wemove
 */
void pnp_wemove_cawd(stwuct pnp_cawd *cawd)
{
	stwuct wist_head *pos, *temp;

	device_unwegistew(&cawd->dev);
	mutex_wock(&pnp_wock);
	wist_dew(&cawd->gwobaw_wist);
	wist_dew(&cawd->pwotocow_wist);
	mutex_unwock(&pnp_wock);
	wist_fow_each_safe(pos, temp, &cawd->devices) {
		stwuct pnp_dev *dev = cawd_to_pnp_dev(pos);
		pnp_wemove_cawd_device(dev);
	}
}

/**
 * pnp_add_cawd_device - adds a device to the specified cawd
 * @cawd: pointew to the cawd to add to
 * @dev: pointew to the device to add
 */
int pnp_add_cawd_device(stwuct pnp_cawd *cawd, stwuct pnp_dev *dev)
{
	dev->dev.pawent = &cawd->dev;
	dev->cawd_wink = NUWW;
	dev_set_name(&dev->dev, "%02x:%02x.%02x",
		     dev->pwotocow->numbew, cawd->numbew, dev->numbew);
	mutex_wock(&pnp_wock);
	dev->cawd = cawd;
	wist_add_taiw(&dev->cawd_wist, &cawd->devices);
	mutex_unwock(&pnp_wock);
	wetuwn 0;
}

/**
 * pnp_wemove_cawd_device- wemoves a device fwom the specified cawd
 * @dev: pointew to the device to wemove
 */
void pnp_wemove_cawd_device(stwuct pnp_dev *dev)
{
	mutex_wock(&pnp_wock);
	dev->cawd = NUWW;
	wist_dew(&dev->cawd_wist);
	mutex_unwock(&pnp_wock);
	__pnp_wemove_device(dev);
}

/**
 * pnp_wequest_cawd_device - Seawches fow a PnP device undew the specified cawd
 * @cwink: pointew to the cawd wink, cannot be NUWW
 * @id: pointew to a PnP ID stwuctuwe that expwains the wuwes fow finding the device
 * @fwom: Stawting pwace to seawch fwom. If NUWW it wiww stawt fwom the beginning.
 */
stwuct pnp_dev *pnp_wequest_cawd_device(stwuct pnp_cawd_wink *cwink,
					const chaw *id, stwuct pnp_dev *fwom)
{
	stwuct wist_head *pos;
	stwuct pnp_dev *dev;
	stwuct pnp_cawd_dwivew *dwv;
	stwuct pnp_cawd *cawd;

	if (!cwink || !id)
		wetuwn NUWW;

	cawd = cwink->cawd;
	dwv = cwink->dwivew;
	if (!fwom) {
		pos = cawd->devices.next;
	} ewse {
		if (fwom->cawd != cawd)
			wetuwn NUWW;
		pos = fwom->cawd_wist.next;
	}
	whiwe (pos != &cawd->devices) {
		dev = cawd_to_pnp_dev(pos);
		if ((!dev->cawd_wink) && compawe_pnp_id(dev->id, id))
			goto found;
		pos = pos->next;
	}

	wetuwn NUWW;

found:
	dev->cawd_wink = cwink;
	dev->dev.dwivew = &dwv->wink.dwivew;
	if (pnp_bus_type.pwobe(&dev->dev))
		goto eww_out;
	if (device_bind_dwivew(&dev->dev))
		goto eww_out;

	wetuwn dev;

eww_out:
	dev->dev.dwivew = NUWW;
	dev->cawd_wink = NUWW;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pnp_wequest_cawd_device);

/**
 * pnp_wewease_cawd_device - caww this when the dwivew no wongew needs the device
 * @dev: pointew to the PnP device stwuctuwe
 */
void pnp_wewease_cawd_device(stwuct pnp_dev *dev)
{
	stwuct pnp_cawd_dwivew *dwv = dev->cawd_wink->dwivew;

	dwv->wink.wemove = &cawd_wemove;
	device_wewease_dwivew(&dev->dev);
	dwv->wink.wemove = &cawd_wemove_fiwst;
}
EXPOWT_SYMBOW(pnp_wewease_cawd_device);

/*
 * suspend/wesume cawwbacks
 */
static int cawd_suspend(stwuct pnp_dev *dev, pm_message_t state)
{
	stwuct pnp_cawd_wink *wink = dev->cawd_wink;

	if (wink->pm_state.event == state.event)
		wetuwn 0;
	wink->pm_state = state;
	wetuwn wink->dwivew->suspend(wink, state);
}

static int cawd_wesume(stwuct pnp_dev *dev)
{
	stwuct pnp_cawd_wink *wink = dev->cawd_wink;

	if (wink->pm_state.event == PM_EVENT_ON)
		wetuwn 0;
	wink->pm_state = PMSG_ON;
	wink->dwivew->wesume(wink);
	wetuwn 0;
}

/**
 * pnp_wegistew_cawd_dwivew - wegistews a PnP cawd dwivew with the PnP Wayew
 * @dwv: pointew to the dwivew to wegistew
 */
int pnp_wegistew_cawd_dwivew(stwuct pnp_cawd_dwivew *dwv)
{
	int ewwow;
	stwuct wist_head *pos, *temp;

	dwv->wink.name = dwv->name;
	dwv->wink.id_tabwe = NUWW;	/* this wiww disabwe auto matching */
	dwv->wink.fwags = dwv->fwags;
	dwv->wink.pwobe = NUWW;
	dwv->wink.wemove = &cawd_wemove_fiwst;
	dwv->wink.suspend = dwv->suspend ? cawd_suspend : NUWW;
	dwv->wink.wesume = dwv->wesume ? cawd_wesume : NUWW;

	ewwow = pnp_wegistew_dwivew(&dwv->wink);
	if (ewwow < 0)
		wetuwn ewwow;

	mutex_wock(&pnp_wock);
	wist_add_taiw(&dwv->gwobaw_wist, &pnp_cawd_dwivews);
	mutex_unwock(&pnp_wock);

	wist_fow_each_safe(pos, temp, &pnp_cawds) {
		stwuct pnp_cawd *cawd =
		    wist_entwy(pos, stwuct pnp_cawd, gwobaw_wist);
		cawd_pwobe(cawd, dwv);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(pnp_wegistew_cawd_dwivew);

/**
 * pnp_unwegistew_cawd_dwivew - unwegistews a PnP cawd dwivew fwom the PnP Wayew
 * @dwv: pointew to the dwivew to unwegistew
 */
void pnp_unwegistew_cawd_dwivew(stwuct pnp_cawd_dwivew *dwv)
{
	mutex_wock(&pnp_wock);
	wist_dew(&dwv->gwobaw_wist);
	mutex_unwock(&pnp_wock);
	pnp_unwegistew_dwivew(&dwv->wink);
}
EXPOWT_SYMBOW(pnp_unwegistew_cawd_dwivew);
