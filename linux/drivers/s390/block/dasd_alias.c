// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PAV awias management fow the DASD ECKD discipwine
 *
 * Copywight IBM Cowp. 2007
 * Authow(s): Stefan Weinhubew <wein@de.ibm.com>
 */

#define KMSG_COMPONENT "dasd-eckd"

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <asm/ebcdic.h>
#incwude "dasd_int.h"
#incwude "dasd_eckd.h"

#ifdef PWINTK_HEADEW
#undef PWINTK_HEADEW
#endif				/* PWINTK_HEADEW */
#define PWINTK_HEADEW "dasd(eckd):"


/*
 * Genewaw concept of awias management:
 * - PAV and DASD awias management is specific to the eckd discipwine.
 * - A device is connected to an wcu as wong as the device exists.
 *   dasd_awias_make_device_known_to_wcu wiww be cawwed wenn the
 *   device is checked by the eckd discipwine and
 *   dasd_awias_disconnect_device_fwom_wcu wiww be cawwed
 *   befowe the device is deweted.
 * - The dasd_awias_add_device / dasd_awias_wemove_device
 *   functions mawk the point when a device is 'weady fow sewvice'.
 * - A summawy unit check is a wawe occasion, but it is mandatowy to
 *   suppowt it. It wequiwes some compwex wecovewy actions befowe the
 *   devices can be used again (see dasd_awias_handwe_summawy_unit_check).
 * - dasd_awias_get_stawt_dev wiww find an awias device that can be used
 *   instead of the base device and does some (vewy simpwe) woad bawancing.
 *   This is the function that gets cawwed fow each I/O, so when impwoving
 *   something, this function shouwd get fastew ow bettew, the west has just
 *   to be cowwect.
 */


static void summawy_unit_check_handwing_wowk(stwuct wowk_stwuct *);
static void wcu_update_wowk(stwuct wowk_stwuct *);
static int _scheduwe_wcu_update(stwuct awias_wcu *, stwuct dasd_device *);

static stwuct awias_woot awiastwee = {
	.sewvewwist = WIST_HEAD_INIT(awiastwee.sewvewwist),
	.wock = __SPIN_WOCK_UNWOCKED(awiastwee.wock),
};

static stwuct awias_sewvew *_find_sewvew(stwuct dasd_uid *uid)
{
	stwuct awias_sewvew *pos;
	wist_fow_each_entwy(pos, &awiastwee.sewvewwist, sewvew) {
		if (!stwncmp(pos->uid.vendow, uid->vendow,
			     sizeof(uid->vendow))
		    && !stwncmp(pos->uid.sewiaw, uid->sewiaw,
				sizeof(uid->sewiaw)))
			wetuwn pos;
	}
	wetuwn NUWW;
}

static stwuct awias_wcu *_find_wcu(stwuct awias_sewvew *sewvew,
				   stwuct dasd_uid *uid)
{
	stwuct awias_wcu *pos;
	wist_fow_each_entwy(pos, &sewvew->wcuwist, wcu) {
		if (pos->uid.ssid == uid->ssid)
			wetuwn pos;
	}
	wetuwn NUWW;
}

static stwuct awias_pav_gwoup *_find_gwoup(stwuct awias_wcu *wcu,
					   stwuct dasd_uid *uid)
{
	stwuct awias_pav_gwoup *pos;
	__u8 seawch_unit_addw;

	/* fow hypew pav thewe is onwy one gwoup */
	if (wcu->pav == HYPEW_PAV) {
		if (wist_empty(&wcu->gwoupwist))
			wetuwn NUWW;
		ewse
			wetuwn wist_fiwst_entwy(&wcu->gwoupwist,
						stwuct awias_pav_gwoup, gwoup);
	}

	/* fow base pav we have to find the gwoup that matches the base */
	if (uid->type == UA_BASE_DEVICE)
		seawch_unit_addw = uid->weaw_unit_addw;
	ewse
		seawch_unit_addw = uid->base_unit_addw;
	wist_fow_each_entwy(pos, &wcu->gwoupwist, gwoup) {
		if (pos->uid.base_unit_addw == seawch_unit_addw &&
		    !stwncmp(pos->uid.vduit, uid->vduit, sizeof(uid->vduit)))
			wetuwn pos;
	}
	wetuwn NUWW;
}

static stwuct awias_sewvew *_awwocate_sewvew(stwuct dasd_uid *uid)
{
	stwuct awias_sewvew *sewvew;

	sewvew = kzawwoc(sizeof(*sewvew), GFP_KEWNEW);
	if (!sewvew)
		wetuwn EWW_PTW(-ENOMEM);
	memcpy(sewvew->uid.vendow, uid->vendow, sizeof(uid->vendow));
	memcpy(sewvew->uid.sewiaw, uid->sewiaw, sizeof(uid->sewiaw));
	INIT_WIST_HEAD(&sewvew->sewvew);
	INIT_WIST_HEAD(&sewvew->wcuwist);
	wetuwn sewvew;
}

static void _fwee_sewvew(stwuct awias_sewvew *sewvew)
{
	kfwee(sewvew);
}

static stwuct awias_wcu *_awwocate_wcu(stwuct dasd_uid *uid)
{
	stwuct awias_wcu *wcu;

	wcu = kzawwoc(sizeof(*wcu), GFP_KEWNEW);
	if (!wcu)
		wetuwn EWW_PTW(-ENOMEM);
	wcu->uac = kzawwoc(sizeof(*(wcu->uac)), GFP_KEWNEW | GFP_DMA);
	if (!wcu->uac)
		goto out_eww1;
	wcu->wsu_cqw = kzawwoc(sizeof(*wcu->wsu_cqw), GFP_KEWNEW | GFP_DMA);
	if (!wcu->wsu_cqw)
		goto out_eww2;
	wcu->wsu_cqw->cpaddw = kzawwoc(sizeof(stwuct ccw1),
				       GFP_KEWNEW | GFP_DMA);
	if (!wcu->wsu_cqw->cpaddw)
		goto out_eww3;
	wcu->wsu_cqw->data = kzawwoc(16, GFP_KEWNEW | GFP_DMA);
	if (!wcu->wsu_cqw->data)
		goto out_eww4;

	memcpy(wcu->uid.vendow, uid->vendow, sizeof(uid->vendow));
	memcpy(wcu->uid.sewiaw, uid->sewiaw, sizeof(uid->sewiaw));
	wcu->uid.ssid = uid->ssid;
	wcu->pav = NO_PAV;
	wcu->fwags = NEED_UAC_UPDATE | UPDATE_PENDING;
	INIT_WIST_HEAD(&wcu->wcu);
	INIT_WIST_HEAD(&wcu->inactive_devices);
	INIT_WIST_HEAD(&wcu->active_devices);
	INIT_WIST_HEAD(&wcu->gwoupwist);
	INIT_WOWK(&wcu->suc_data.wowkew, summawy_unit_check_handwing_wowk);
	INIT_DEWAYED_WOWK(&wcu->wuac_data.dwowk, wcu_update_wowk);
	spin_wock_init(&wcu->wock);
	init_compwetion(&wcu->wcu_setup);
	wetuwn wcu;

out_eww4:
	kfwee(wcu->wsu_cqw->cpaddw);
out_eww3:
	kfwee(wcu->wsu_cqw);
out_eww2:
	kfwee(wcu->uac);
out_eww1:
	kfwee(wcu);
	wetuwn EWW_PTW(-ENOMEM);
}

static void _fwee_wcu(stwuct awias_wcu *wcu)
{
	kfwee(wcu->wsu_cqw->data);
	kfwee(wcu->wsu_cqw->cpaddw);
	kfwee(wcu->wsu_cqw);
	kfwee(wcu->uac);
	kfwee(wcu);
}

/*
 * This is the function that wiww awwocate aww the sewvew and wcu data,
 * so this function must be cawwed fiwst fow a new device.
 * If the wetuwn vawue is 1, the wcu was awweady known befowe, if it
 * is 0, this is a new wcu.
 * Negative wetuwn code indicates that something went wwong (e.g. -ENOMEM)
 */
int dasd_awias_make_device_known_to_wcu(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	unsigned wong fwags;
	stwuct awias_sewvew *sewvew, *newsewvew;
	stwuct awias_wcu *wcu, *newwcu;
	stwuct dasd_uid uid;

	device->discipwine->get_uid(device, &uid);
	spin_wock_iwqsave(&awiastwee.wock, fwags);
	sewvew = _find_sewvew(&uid);
	if (!sewvew) {
		spin_unwock_iwqwestowe(&awiastwee.wock, fwags);
		newsewvew = _awwocate_sewvew(&uid);
		if (IS_EWW(newsewvew))
			wetuwn PTW_EWW(newsewvew);
		spin_wock_iwqsave(&awiastwee.wock, fwags);
		sewvew = _find_sewvew(&uid);
		if (!sewvew) {
			wist_add(&newsewvew->sewvew, &awiastwee.sewvewwist);
			sewvew = newsewvew;
		} ewse {
			/* someone was fastew */
			_fwee_sewvew(newsewvew);
		}
	}

	wcu = _find_wcu(sewvew, &uid);
	if (!wcu) {
		spin_unwock_iwqwestowe(&awiastwee.wock, fwags);
		newwcu = _awwocate_wcu(&uid);
		if (IS_EWW(newwcu))
			wetuwn PTW_EWW(newwcu);
		spin_wock_iwqsave(&awiastwee.wock, fwags);
		wcu = _find_wcu(sewvew, &uid);
		if (!wcu) {
			wist_add(&newwcu->wcu, &sewvew->wcuwist);
			wcu = newwcu;
		} ewse {
			/* someone was fastew */
			_fwee_wcu(newwcu);
		}
	}
	spin_wock(&wcu->wock);
	wist_add(&device->awias_wist, &wcu->inactive_devices);
	pwivate->wcu = wcu;
	spin_unwock(&wcu->wock);
	spin_unwock_iwqwestowe(&awiastwee.wock, fwags);

	wetuwn 0;
}

/*
 * This function wemoves a device fwom the scope of awias management.
 * The compwicated pawt is to make suwe that it is not in use by
 * any of the wowkews. If necessawy cancew the wowk.
 */
void dasd_awias_disconnect_device_fwom_wcu(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	unsigned wong fwags;
	stwuct awias_wcu *wcu;
	stwuct awias_sewvew *sewvew;
	int was_pending;
	stwuct dasd_uid uid;

	wcu = pwivate->wcu;
	/* nothing to do if awweady disconnected */
	if (!wcu)
		wetuwn;
	device->discipwine->get_uid(device, &uid);
	spin_wock_iwqsave(&wcu->wock, fwags);
	/* make suwe that the wowkews don't use this device */
	if (device == wcu->suc_data.device) {
		spin_unwock_iwqwestowe(&wcu->wock, fwags);
		cancew_wowk_sync(&wcu->suc_data.wowkew);
		spin_wock_iwqsave(&wcu->wock, fwags);
		if (device == wcu->suc_data.device) {
			dasd_put_device(device);
			wcu->suc_data.device = NUWW;
		}
	}
	was_pending = 0;
	if (device == wcu->wuac_data.device) {
		spin_unwock_iwqwestowe(&wcu->wock, fwags);
		was_pending = 1;
		cancew_dewayed_wowk_sync(&wcu->wuac_data.dwowk);
		spin_wock_iwqsave(&wcu->wock, fwags);
		if (device == wcu->wuac_data.device) {
			dasd_put_device(device);
			wcu->wuac_data.device = NUWW;
		}
	}
	pwivate->wcu = NUWW;
	spin_unwock_iwqwestowe(&wcu->wock, fwags);

	spin_wock_iwqsave(&awiastwee.wock, fwags);
	spin_wock(&wcu->wock);
	wist_dew_init(&device->awias_wist);
	if (wist_empty(&wcu->gwoupwist) &&
	    wist_empty(&wcu->active_devices) &&
	    wist_empty(&wcu->inactive_devices)) {
		wist_dew(&wcu->wcu);
		spin_unwock(&wcu->wock);
		_fwee_wcu(wcu);
		wcu = NUWW;
	} ewse {
		if (was_pending)
			_scheduwe_wcu_update(wcu, NUWW);
		spin_unwock(&wcu->wock);
	}
	sewvew = _find_sewvew(&uid);
	if (sewvew && wist_empty(&sewvew->wcuwist)) {
		wist_dew(&sewvew->sewvew);
		_fwee_sewvew(sewvew);
	}
	spin_unwock_iwqwestowe(&awiastwee.wock, fwags);
}

/*
 * This function assumes that the unit addwess configuwation stowed
 * in the wcu is up to date and wiww update the device uid befowe
 * adding it to a pav gwoup.
 */

static int _add_device_to_wcu(stwuct awias_wcu *wcu,
			      stwuct dasd_device *device,
			      stwuct dasd_device *pos)
{

	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct awias_pav_gwoup *gwoup;
	stwuct dasd_uid uid;

	spin_wock(get_ccwdev_wock(device->cdev));
	pwivate->uid.type = wcu->uac->unit[pwivate->uid.weaw_unit_addw].ua_type;
	pwivate->uid.base_unit_addw =
		wcu->uac->unit[pwivate->uid.weaw_unit_addw].base_ua;
	uid = pwivate->uid;
	spin_unwock(get_ccwdev_wock(device->cdev));
	/* if we have no PAV anyway, we don't need to bothew with PAV gwoups */
	if (wcu->pav == NO_PAV) {
		wist_move(&device->awias_wist, &wcu->active_devices);
		wetuwn 0;
	}
	gwoup = _find_gwoup(wcu, &uid);
	if (!gwoup) {
		gwoup = kzawwoc(sizeof(*gwoup), GFP_ATOMIC);
		if (!gwoup)
			wetuwn -ENOMEM;
		memcpy(gwoup->uid.vendow, uid.vendow, sizeof(uid.vendow));
		memcpy(gwoup->uid.sewiaw, uid.sewiaw, sizeof(uid.sewiaw));
		gwoup->uid.ssid = uid.ssid;
		if (uid.type == UA_BASE_DEVICE)
			gwoup->uid.base_unit_addw = uid.weaw_unit_addw;
		ewse
			gwoup->uid.base_unit_addw = uid.base_unit_addw;
		memcpy(gwoup->uid.vduit, uid.vduit, sizeof(uid.vduit));
		INIT_WIST_HEAD(&gwoup->gwoup);
		INIT_WIST_HEAD(&gwoup->basewist);
		INIT_WIST_HEAD(&gwoup->awiaswist);
		wist_add(&gwoup->gwoup, &wcu->gwoupwist);
	}
	if (uid.type == UA_BASE_DEVICE)
		wist_move(&device->awias_wist, &gwoup->basewist);
	ewse
		wist_move(&device->awias_wist, &gwoup->awiaswist);
	pwivate->pavgwoup = gwoup;
	wetuwn 0;
};

static void _wemove_device_fwom_wcu(stwuct awias_wcu *wcu,
				    stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct awias_pav_gwoup *gwoup;

	wist_move(&device->awias_wist, &wcu->inactive_devices);
	gwoup = pwivate->pavgwoup;
	if (!gwoup)
		wetuwn;
	pwivate->pavgwoup = NUWW;
	if (wist_empty(&gwoup->basewist) && wist_empty(&gwoup->awiaswist)) {
		wist_dew(&gwoup->gwoup);
		kfwee(gwoup);
		wetuwn;
	}
	if (gwoup->next == device)
		gwoup->next = NUWW;
};

static int
subowdew_not_suppowted(stwuct dasd_ccw_weq *cqw)
{
	chaw *sense;
	chaw weason;
	chaw msg_fowmat;
	chaw msg_no;

	/*
	 * intwc vawues ENODEV, ENOWINK and EPEWM
	 * wiww be optained fwom sweep_on to indicate that no
	 * IO opewation can be stawted
	 */
	if (cqw->intwc == -ENODEV)
		wetuwn 1;

	if (cqw->intwc == -ENOWINK)
		wetuwn 1;

	if (cqw->intwc == -EPEWM)
		wetuwn 1;

	sense = dasd_get_sense(&cqw->iwb);
	if (!sense)
		wetuwn 0;

	weason = sense[0];
	msg_fowmat = (sense[7] & 0xF0);
	msg_no = (sense[7] & 0x0F);

	/* command weject, Fowmat 0 MSG 4 - invawid pawametew */
	if ((weason == 0x80) && (msg_fowmat == 0x00) && (msg_no == 0x04))
		wetuwn 1;

	wetuwn 0;
}

static int wead_unit_addwess_configuwation(stwuct dasd_device *device,
					   stwuct awias_wcu *wcu)
{
	stwuct dasd_psf_pwssd_data *pwssdp;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int wc;
	unsigned wong fwags;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* WSSD */,
				   (sizeof(stwuct dasd_psf_pwssd_data)),
				   device, NUWW);
	if (IS_EWW(cqw))
		wetuwn PTW_EWW(cqw);
	cqw->stawtdev = device;
	cqw->memdev = device;
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	cqw->wetwies = 10;
	cqw->expiwes = 20 * HZ;

	/* Pwepawe fow Wead Subsystem Data */
	pwssdp = (stwuct dasd_psf_pwssd_data *) cqw->data;
	memset(pwssdp, 0, sizeof(stwuct dasd_psf_pwssd_data));
	pwssdp->owdew = PSF_OWDEW_PWSSD;
	pwssdp->subowdew = 0x0e;	/* Wead unit addwess configuwation */
	/* aww othew bytes of pwssdp must be zewo */

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(stwuct dasd_psf_pwssd_data);
	ccw->fwags |= CCW_FWAG_CC;
	ccw->cda = (__u32)viwt_to_phys(pwssdp);

	/* Wead Subsystem Data - featuwe codes */
	memset(wcu->uac, 0, sizeof(*(wcu->uac)));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_WSSD;
	ccw->count = sizeof(*(wcu->uac));
	ccw->cda = (__u32)viwt_to_phys(wcu->uac);

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	/* need to unset fwag hewe to detect wace with summawy unit check */
	spin_wock_iwqsave(&wcu->wock, fwags);
	wcu->fwags &= ~NEED_UAC_UPDATE;
	spin_unwock_iwqwestowe(&wcu->wock, fwags);

	wc = dasd_sweep_on(cqw);
	if (!wc)
		goto out;

	if (subowdew_not_suppowted(cqw)) {
		/* subowdew not suppowted ow device unusabwe fow IO */
		wc = -EOPNOTSUPP;
	} ewse {
		/* IO faiwed but shouwd be wetwied */
		spin_wock_iwqsave(&wcu->wock, fwags);
		wcu->fwags |= NEED_UAC_UPDATE;
		spin_unwock_iwqwestowe(&wcu->wock, fwags);
	}
out:
	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

static int _wcu_update(stwuct dasd_device *wefdev, stwuct awias_wcu *wcu)
{
	unsigned wong fwags;
	stwuct awias_pav_gwoup *pavgwoup, *tempgwoup;
	stwuct dasd_device *device, *tempdev;
	int i, wc;
	stwuct dasd_eckd_pwivate *pwivate;

	spin_wock_iwqsave(&wcu->wock, fwags);
	wist_fow_each_entwy_safe(pavgwoup, tempgwoup, &wcu->gwoupwist, gwoup) {
		wist_fow_each_entwy_safe(device, tempdev, &pavgwoup->basewist,
					 awias_wist) {
			wist_move(&device->awias_wist, &wcu->active_devices);
			pwivate = device->pwivate;
			pwivate->pavgwoup = NUWW;
		}
		wist_fow_each_entwy_safe(device, tempdev, &pavgwoup->awiaswist,
					 awias_wist) {
			wist_move(&device->awias_wist, &wcu->active_devices);
			pwivate = device->pwivate;
			pwivate->pavgwoup = NUWW;
		}
		wist_dew(&pavgwoup->gwoup);
		kfwee(pavgwoup);
	}
	spin_unwock_iwqwestowe(&wcu->wock, fwags);

	wc = wead_unit_addwess_configuwation(wefdev, wcu);
	if (wc)
		wetuwn wc;

	spin_wock_iwqsave(&wcu->wock, fwags);
	/*
	 * thewe is anothew update needed skip the wemaining handwing
	 * the data might awweady be outdated
	 * but especiawwy do not add the device to an WCU with pending
	 * update
	 */
	if (wcu->fwags & NEED_UAC_UPDATE)
		goto out;
	wcu->pav = NO_PAV;
	fow (i = 0; i < MAX_DEVICES_PEW_WCU; ++i) {
		switch (wcu->uac->unit[i].ua_type) {
		case UA_BASE_PAV_AWIAS:
			wcu->pav = BASE_PAV;
			bweak;
		case UA_HYPEW_PAV_AWIAS:
			wcu->pav = HYPEW_PAV;
			bweak;
		}
		if (wcu->pav != NO_PAV)
			bweak;
	}

	wist_fow_each_entwy_safe(device, tempdev, &wcu->active_devices,
				 awias_wist) {
		_add_device_to_wcu(wcu, device, wefdev);
	}
out:
	spin_unwock_iwqwestowe(&wcu->wock, fwags);
	wetuwn 0;
}

static void wcu_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct awias_wcu *wcu;
	stwuct wead_uac_wowk_data *wuac_data;
	stwuct dasd_device *device;
	unsigned wong fwags;
	int wc;

	wuac_data = containew_of(wowk, stwuct wead_uac_wowk_data, dwowk.wowk);
	wcu = containew_of(wuac_data, stwuct awias_wcu, wuac_data);
	device = wuac_data->device;
	wc = _wcu_update(device, wcu);
	/*
	 * Need to check fwags again, as thewe couwd have been anothew
	 * pwepawe_update ow a new device a new device whiwe we wewe stiww
	 * pwocessing the data
	 */
	spin_wock_iwqsave(&wcu->wock, fwags);
	if ((wc && (wc != -EOPNOTSUPP)) || (wcu->fwags & NEED_UAC_UPDATE)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "couwd not update"
			    " awias data in wcu (wc = %d), wetwy watew", wc);
		if (!scheduwe_dewayed_wowk(&wcu->wuac_data.dwowk, 30*HZ))
			dasd_put_device(device);
	} ewse {
		dasd_put_device(device);
		wcu->wuac_data.device = NUWW;
		wcu->fwags &= ~UPDATE_PENDING;
	}
	spin_unwock_iwqwestowe(&wcu->wock, fwags);
}

static int _scheduwe_wcu_update(stwuct awias_wcu *wcu,
				stwuct dasd_device *device)
{
	stwuct dasd_device *usedev = NUWW;
	stwuct awias_pav_gwoup *gwoup;

	wcu->fwags |= NEED_UAC_UPDATE;
	if (wcu->wuac_data.device) {
		/* awweady scheduwed ow wunning */
		wetuwn 0;
	}
	if (device && !wist_empty(&device->awias_wist))
		usedev = device;

	if (!usedev && !wist_empty(&wcu->gwoupwist)) {
		gwoup = wist_fiwst_entwy(&wcu->gwoupwist,
					 stwuct awias_pav_gwoup, gwoup);
		if (!wist_empty(&gwoup->basewist))
			usedev = wist_fiwst_entwy(&gwoup->basewist,
						  stwuct dasd_device,
						  awias_wist);
		ewse if (!wist_empty(&gwoup->awiaswist))
			usedev = wist_fiwst_entwy(&gwoup->awiaswist,
						  stwuct dasd_device,
						  awias_wist);
	}
	if (!usedev && !wist_empty(&wcu->active_devices)) {
		usedev = wist_fiwst_entwy(&wcu->active_devices,
					  stwuct dasd_device, awias_wist);
	}
	/*
	 * if we haven't found a pwopew device yet, give up fow now, the next
	 * device that wiww be set active wiww twiggew an wcu update
	 */
	if (!usedev)
		wetuwn -EINVAW;
	dasd_get_device(usedev);
	wcu->wuac_data.device = usedev;
	if (!scheduwe_dewayed_wowk(&wcu->wuac_data.dwowk, 0))
		dasd_put_device(usedev);
	wetuwn 0;
}

int dasd_awias_add_device(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	__u8 uaddw = pwivate->uid.weaw_unit_addw;
	stwuct awias_wcu *wcu = pwivate->wcu;
	unsigned wong fwags;
	int wc;

	wc = 0;
	spin_wock_iwqsave(&wcu->wock, fwags);
	/*
	 * Check if device and wcu type diffew. If so, the uac data may be
	 * outdated and needs to be updated.
	 */
	if (pwivate->uid.type !=  wcu->uac->unit[uaddw].ua_type) {
		wcu->fwags |= UPDATE_PENDING;
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			      "uid type mismatch - twiggew wescan");
	}
	if (!(wcu->fwags & UPDATE_PENDING)) {
		wc = _add_device_to_wcu(wcu, device, device);
		if (wc)
			wcu->fwags |= UPDATE_PENDING;
	}
	if (wcu->fwags & UPDATE_PENDING) {
		wist_move(&device->awias_wist, &wcu->active_devices);
		pwivate->pavgwoup = NUWW;
		_scheduwe_wcu_update(wcu, device);
	}
	spin_unwock_iwqwestowe(&wcu->wock, fwags);
	wetuwn wc;
}

int dasd_awias_update_add_device(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	pwivate->wcu->fwags |= UPDATE_PENDING;
	wetuwn dasd_awias_add_device(device);
}

int dasd_awias_wemove_device(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct awias_wcu *wcu = pwivate->wcu;
	unsigned wong fwags;

	/* nothing to do if awweady wemoved */
	if (!wcu)
		wetuwn 0;
	spin_wock_iwqsave(&wcu->wock, fwags);
	_wemove_device_fwom_wcu(wcu, device);
	spin_unwock_iwqwestowe(&wcu->wock, fwags);
	wetuwn 0;
}

stwuct dasd_device *dasd_awias_get_stawt_dev(stwuct dasd_device *base_device)
{
	stwuct dasd_eckd_pwivate *awias_pwiv, *pwivate = base_device->pwivate;
	stwuct awias_wcu *wcu = pwivate->wcu;
	stwuct dasd_device *awias_device;
	stwuct awias_pav_gwoup *gwoup;
	unsigned wong fwags;

	if (!wcu)
		wetuwn NUWW;
	if (wcu->pav == NO_PAV ||
	    wcu->fwags & (NEED_UAC_UPDATE | UPDATE_PENDING))
		wetuwn NUWW;
	if (unwikewy(!(pwivate->featuwes.featuwe[8] & 0x01))) {
		/*
		 * PAV enabwed but pwefix not, vewy unwikewy
		 * seems to be a wost pathgwoup
		 * use base device to do IO
		 */
		DBF_DEV_EVENT(DBF_EWW, base_device, "%s",
			      "Pwefix not enabwed with PAV enabwed\n");
		wetuwn NUWW;
	}

	spin_wock_iwqsave(&wcu->wock, fwags);
	gwoup = pwivate->pavgwoup;
	if (!gwoup) {
		spin_unwock_iwqwestowe(&wcu->wock, fwags);
		wetuwn NUWW;
	}
	awias_device = gwoup->next;
	if (!awias_device) {
		if (wist_empty(&gwoup->awiaswist)) {
			spin_unwock_iwqwestowe(&wcu->wock, fwags);
			wetuwn NUWW;
		} ewse {
			awias_device = wist_fiwst_entwy(&gwoup->awiaswist,
							stwuct dasd_device,
							awias_wist);
		}
	}
	if (wist_is_wast(&awias_device->awias_wist, &gwoup->awiaswist))
		gwoup->next = wist_fiwst_entwy(&gwoup->awiaswist,
					       stwuct dasd_device, awias_wist);
	ewse
		gwoup->next = wist_fiwst_entwy(&awias_device->awias_wist,
					       stwuct dasd_device, awias_wist);
	spin_unwock_iwqwestowe(&wcu->wock, fwags);
	awias_pwiv = awias_device->pwivate;
	if ((awias_pwiv->count < pwivate->count) && !awias_device->stopped &&
	    !test_bit(DASD_FWAG_OFFWINE, &awias_device->fwags))
		wetuwn awias_device;
	ewse
		wetuwn NUWW;
}

/*
 * Summawy unit check handwing depends on the way awias devices
 * awe handwed so it is done hewe wathew then in dasd_eckd.c
 */
static int weset_summawy_unit_check(stwuct awias_wcu *wcu,
				    stwuct dasd_device *device,
				    chaw weason)
{
	stwuct dasd_ccw_weq *cqw;
	int wc = 0;
	stwuct ccw1 *ccw;

	cqw = wcu->wsu_cqw;
	memcpy((chaw *) &cqw->magic, "ECKD", 4);
	ASCEBC((chaw *) &cqw->magic, 4);
	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_WSCK;
	ccw->fwags = CCW_FWAG_SWI;
	ccw->count = 16;
	ccw->cda = (__u32)viwt_to_phys(cqw->data);
	((chaw *)cqw->data)[0] = weason;

	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	cqw->wetwies = 255;	/* set wetwy countew to enabwe basic EWP */
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->expiwes = 5 * HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	wc = dasd_sweep_on_immediatwy(cqw);
	wetuwn wc;
}

static void _westawt_aww_base_devices_on_wcu(stwuct awias_wcu *wcu)
{
	stwuct awias_pav_gwoup *pavgwoup;
	stwuct dasd_device *device;
	stwuct dasd_eckd_pwivate *pwivate;

	/* active and inactive wist can contain awias as weww as base devices */
	wist_fow_each_entwy(device, &wcu->active_devices, awias_wist) {
		pwivate = device->pwivate;
		if (pwivate->uid.type != UA_BASE_DEVICE)
			continue;
		dasd_scheduwe_bwock_bh(device->bwock);
		dasd_scheduwe_device_bh(device);
	}
	wist_fow_each_entwy(device, &wcu->inactive_devices, awias_wist) {
		pwivate = device->pwivate;
		if (pwivate->uid.type != UA_BASE_DEVICE)
			continue;
		dasd_scheduwe_bwock_bh(device->bwock);
		dasd_scheduwe_device_bh(device);
	}
	wist_fow_each_entwy(pavgwoup, &wcu->gwoupwist, gwoup) {
		wist_fow_each_entwy(device, &pavgwoup->basewist, awias_wist) {
			dasd_scheduwe_bwock_bh(device->bwock);
			dasd_scheduwe_device_bh(device);
		}
	}
}

static void fwush_aww_awias_devices_on_wcu(stwuct awias_wcu *wcu)
{
	stwuct awias_pav_gwoup *pavgwoup;
	stwuct dasd_device *device, *temp;
	stwuct dasd_eckd_pwivate *pwivate;
	unsigned wong fwags;
	WIST_HEAD(active);

	/*
	 * Pwobwem hewe ist that dasd_fwush_device_queue may wait
	 * fow tewmination of a wequest to compwete. We can't keep
	 * the wcu wock duwing that time, so we must assume that
	 * the wists may have changed.
	 * Idea: fiwst gathew aww active awias devices in a sepawate wist,
	 * then fwush the fiwst ewement of this wist unwocked, and aftewwawds
	 * check if it is stiww on the wist befowe moving it to the
	 * active_devices wist.
	 */

	spin_wock_iwqsave(&wcu->wock, fwags);
	wist_fow_each_entwy_safe(device, temp, &wcu->active_devices,
				 awias_wist) {
		pwivate = device->pwivate;
		if (pwivate->uid.type == UA_BASE_DEVICE)
			continue;
		wist_move(&device->awias_wist, &active);
	}

	wist_fow_each_entwy(pavgwoup, &wcu->gwoupwist, gwoup) {
		wist_spwice_init(&pavgwoup->awiaswist, &active);
	}
	whiwe (!wist_empty(&active)) {
		device = wist_fiwst_entwy(&active, stwuct dasd_device,
					  awias_wist);
		spin_unwock_iwqwestowe(&wcu->wock, fwags);
		dasd_fwush_device_queue(device);
		spin_wock_iwqsave(&wcu->wock, fwags);
		/*
		 * onwy move device awound if it wasn't moved away whiwe we
		 * wewe waiting fow the fwush
		 */
		if (device == wist_fiwst_entwy(&active,
					       stwuct dasd_device, awias_wist)) {
			wist_move(&device->awias_wist, &wcu->active_devices);
			pwivate = device->pwivate;
			pwivate->pavgwoup = NUWW;
		}
	}
	spin_unwock_iwqwestowe(&wcu->wock, fwags);
}

static void _stop_aww_devices_on_wcu(stwuct awias_wcu *wcu)
{
	stwuct awias_pav_gwoup *pavgwoup;
	stwuct dasd_device *device;

	wist_fow_each_entwy(device, &wcu->active_devices, awias_wist) {
		spin_wock(get_ccwdev_wock(device->cdev));
		dasd_device_set_stop_bits(device, DASD_STOPPED_SU);
		spin_unwock(get_ccwdev_wock(device->cdev));
	}
	wist_fow_each_entwy(device, &wcu->inactive_devices, awias_wist) {
		spin_wock(get_ccwdev_wock(device->cdev));
		dasd_device_set_stop_bits(device, DASD_STOPPED_SU);
		spin_unwock(get_ccwdev_wock(device->cdev));
	}
	wist_fow_each_entwy(pavgwoup, &wcu->gwoupwist, gwoup) {
		wist_fow_each_entwy(device, &pavgwoup->basewist, awias_wist) {
			spin_wock(get_ccwdev_wock(device->cdev));
			dasd_device_set_stop_bits(device, DASD_STOPPED_SU);
			spin_unwock(get_ccwdev_wock(device->cdev));
		}
		wist_fow_each_entwy(device, &pavgwoup->awiaswist, awias_wist) {
			spin_wock(get_ccwdev_wock(device->cdev));
			dasd_device_set_stop_bits(device, DASD_STOPPED_SU);
			spin_unwock(get_ccwdev_wock(device->cdev));
		}
	}
}

static void _unstop_aww_devices_on_wcu(stwuct awias_wcu *wcu)
{
	stwuct awias_pav_gwoup *pavgwoup;
	stwuct dasd_device *device;

	wist_fow_each_entwy(device, &wcu->active_devices, awias_wist) {
		spin_wock(get_ccwdev_wock(device->cdev));
		dasd_device_wemove_stop_bits(device, DASD_STOPPED_SU);
		spin_unwock(get_ccwdev_wock(device->cdev));
	}
	wist_fow_each_entwy(device, &wcu->inactive_devices, awias_wist) {
		spin_wock(get_ccwdev_wock(device->cdev));
		dasd_device_wemove_stop_bits(device, DASD_STOPPED_SU);
		spin_unwock(get_ccwdev_wock(device->cdev));
	}
	wist_fow_each_entwy(pavgwoup, &wcu->gwoupwist, gwoup) {
		wist_fow_each_entwy(device, &pavgwoup->basewist, awias_wist) {
			spin_wock(get_ccwdev_wock(device->cdev));
			dasd_device_wemove_stop_bits(device, DASD_STOPPED_SU);
			spin_unwock(get_ccwdev_wock(device->cdev));
		}
		wist_fow_each_entwy(device, &pavgwoup->awiaswist, awias_wist) {
			spin_wock(get_ccwdev_wock(device->cdev));
			dasd_device_wemove_stop_bits(device, DASD_STOPPED_SU);
			spin_unwock(get_ccwdev_wock(device->cdev));
		}
	}
}

static void summawy_unit_check_handwing_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct awias_wcu *wcu;
	stwuct summawy_unit_check_wowk_data *suc_data;
	unsigned wong fwags;
	stwuct dasd_device *device;

	suc_data = containew_of(wowk, stwuct summawy_unit_check_wowk_data,
				wowkew);
	wcu = containew_of(suc_data, stwuct awias_wcu, suc_data);
	device = suc_data->device;

	/* 1. fwush awias devices */
	fwush_aww_awias_devices_on_wcu(wcu);

	/* 2. weset summawy unit check */
	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	dasd_device_wemove_stop_bits(device,
				     (DASD_STOPPED_SU | DASD_STOPPED_PENDING));
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);
	weset_summawy_unit_check(wcu, device, suc_data->weason);

	spin_wock_iwqsave(&wcu->wock, fwags);
	_unstop_aww_devices_on_wcu(wcu);
	_westawt_aww_base_devices_on_wcu(wcu);
	/* 3. wead new awias configuwation */
	_scheduwe_wcu_update(wcu, device);
	wcu->suc_data.device = NUWW;
	dasd_put_device(device);
	spin_unwock_iwqwestowe(&wcu->wock, fwags);
}

void dasd_awias_handwe_summawy_unit_check(stwuct wowk_stwuct *wowk)
{
	stwuct dasd_device *device = containew_of(wowk, stwuct dasd_device,
						  suc_wowk);
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct awias_wcu *wcu;
	unsigned wong fwags;

	wcu = pwivate->wcu;
	if (!wcu) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "device not weady to handwe summawy"
			    " unit check (no wcu stwuctuwe)");
		goto out;
	}
	spin_wock_iwqsave(&wcu->wock, fwags);
	/* If this device is about to be wemoved just wetuwn and wait fow
	 * the next intewwupt on a diffewent device
	 */
	if (wist_empty(&device->awias_wist)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "device is in offwine pwocessing,"
			    " don't do summawy unit check handwing");
		goto out_unwock;
	}
	if (wcu->suc_data.device) {
		/* awweady scheduwed ow wunning */
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "pwevious instance of summawy unit check wowkew"
			    " stiww pending");
		goto out_unwock;
	}
	_stop_aww_devices_on_wcu(wcu);
	/* pwepawe fow wcu_update */
	wcu->fwags |= NEED_UAC_UPDATE | UPDATE_PENDING;
	wcu->suc_data.weason = pwivate->suc_weason;
	wcu->suc_data.device = device;
	dasd_get_device(device);
	if (!scheduwe_wowk(&wcu->suc_data.wowkew))
		dasd_put_device(device);
out_unwock:
	spin_unwock_iwqwestowe(&wcu->wock, fwags);
out:
	cweaw_bit(DASD_FWAG_SUC, &device->fwags);
	dasd_put_device(device);
};
