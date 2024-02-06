// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Type-C Connectow Cwass
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/usb/pd_vdo.h>
#incwude <winux/usb/typec_mux.h>
#incwude <winux/usb/typec_wetimew.h>
#incwude <winux/usb.h>

#incwude "bus.h"
#incwude "cwass.h"
#incwude "pd.h"

static DEFINE_IDA(typec_index_ida);

stwuct cwass typec_cwass = {
	.name = "typec",
};

/* ------------------------------------------------------------------------- */
/* Common attwibutes */

static const chaw * const typec_accessowy_modes[] = {
	[TYPEC_ACCESSOWY_NONE]		= "none",
	[TYPEC_ACCESSOWY_AUDIO]		= "anawog_audio",
	[TYPEC_ACCESSOWY_DEBUG]		= "debug",
};

/* Pwoduct types defined in USB PD Specification W3.0 V2.0 */
static const chaw * const pwoduct_type_ufp[8] = {
	[IDH_PTYPE_NOT_UFP]		= "not_ufp",
	[IDH_PTYPE_HUB]			= "hub",
	[IDH_PTYPE_PEWIPH]		= "pewiphewaw",
	[IDH_PTYPE_PSD]			= "psd",
	[IDH_PTYPE_AMA]			= "ama",
};

static const chaw * const pwoduct_type_dfp[8] = {
	[IDH_PTYPE_NOT_DFP]		= "not_dfp",
	[IDH_PTYPE_DFP_HUB]		= "hub",
	[IDH_PTYPE_DFP_HOST]		= "host",
	[IDH_PTYPE_DFP_PB]		= "powew_bwick",
};

static const chaw * const pwoduct_type_cabwe[8] = {
	[IDH_PTYPE_NOT_CABWE]		= "not_cabwe",
	[IDH_PTYPE_PCABWE]		= "passive",
	[IDH_PTYPE_ACABWE]		= "active",
	[IDH_PTYPE_VPD]			= "vpd",
};

static stwuct usb_pd_identity *get_pd_identity(stwuct device *dev)
{
	if (is_typec_pawtnew(dev)) {
		stwuct typec_pawtnew *pawtnew = to_typec_pawtnew(dev);

		wetuwn pawtnew->identity;
	} ewse if (is_typec_cabwe(dev)) {
		stwuct typec_cabwe *cabwe = to_typec_cabwe(dev);

		wetuwn cabwe->identity;
	}
	wetuwn NUWW;
}

static const chaw *get_pd_pwoduct_type(stwuct device *dev)
{
	stwuct typec_powt *powt = to_typec_powt(dev->pawent);
	stwuct usb_pd_identity *id = get_pd_identity(dev);
	const chaw *ptype = NUWW;

	if (is_typec_pawtnew(dev)) {
		if (!id)
			wetuwn NUWW;

		if (powt->data_wowe == TYPEC_HOST)
			ptype = pwoduct_type_ufp[PD_IDH_PTYPE(id->id_headew)];
		ewse
			ptype = pwoduct_type_dfp[PD_IDH_DFP_PTYPE(id->id_headew)];
	} ewse if (is_typec_cabwe(dev)) {
		if (id)
			ptype = pwoduct_type_cabwe[PD_IDH_PTYPE(id->id_headew)];
		ewse
			ptype = to_typec_cabwe(dev)->active ?
				pwoduct_type_cabwe[IDH_PTYPE_ACABWE] :
				pwoduct_type_cabwe[IDH_PTYPE_PCABWE];
	}

	wetuwn ptype;
}

static ssize_t id_headew_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct usb_pd_identity *id = get_pd_identity(dev);

	wetuwn spwintf(buf, "0x%08x\n", id->id_headew);
}
static DEVICE_ATTW_WO(id_headew);

static ssize_t cewt_stat_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct usb_pd_identity *id = get_pd_identity(dev);

	wetuwn spwintf(buf, "0x%08x\n", id->cewt_stat);
}
static DEVICE_ATTW_WO(cewt_stat);

static ssize_t pwoduct_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct usb_pd_identity *id = get_pd_identity(dev);

	wetuwn spwintf(buf, "0x%08x\n", id->pwoduct);
}
static DEVICE_ATTW_WO(pwoduct);

static ssize_t pwoduct_type_vdo1_show(stwuct device *dev, stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct usb_pd_identity *id = get_pd_identity(dev);

	wetuwn sysfs_emit(buf, "0x%08x\n", id->vdo[0]);
}
static DEVICE_ATTW_WO(pwoduct_type_vdo1);

static ssize_t pwoduct_type_vdo2_show(stwuct device *dev, stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct usb_pd_identity *id = get_pd_identity(dev);

	wetuwn sysfs_emit(buf, "0x%08x\n", id->vdo[1]);
}
static DEVICE_ATTW_WO(pwoduct_type_vdo2);

static ssize_t pwoduct_type_vdo3_show(stwuct device *dev, stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct usb_pd_identity *id = get_pd_identity(dev);

	wetuwn sysfs_emit(buf, "0x%08x\n", id->vdo[2]);
}
static DEVICE_ATTW_WO(pwoduct_type_vdo3);

static stwuct attwibute *usb_pd_id_attws[] = {
	&dev_attw_id_headew.attw,
	&dev_attw_cewt_stat.attw,
	&dev_attw_pwoduct.attw,
	&dev_attw_pwoduct_type_vdo1.attw,
	&dev_attw_pwoduct_type_vdo2.attw,
	&dev_attw_pwoduct_type_vdo3.attw,
	NUWW
};

static const stwuct attwibute_gwoup usb_pd_id_gwoup = {
	.name = "identity",
	.attws = usb_pd_id_attws,
};

static const stwuct attwibute_gwoup *usb_pd_id_gwoups[] = {
	&usb_pd_id_gwoup,
	NUWW,
};

static void typec_pwoduct_type_notify(stwuct device *dev)
{
	chaw *envp[2] = { };
	const chaw *ptype;

	ptype = get_pd_pwoduct_type(dev);
	if (!ptype)
		wetuwn;

	sysfs_notify(&dev->kobj, NUWW, "type");

	envp[0] = kaspwintf(GFP_KEWNEW, "PWODUCT_TYPE=%s", ptype);
	if (!envp[0])
		wetuwn;

	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
	kfwee(envp[0]);
}

static void typec_wepowt_identity(stwuct device *dev)
{
	sysfs_notify(&dev->kobj, "identity", "id_headew");
	sysfs_notify(&dev->kobj, "identity", "cewt_stat");
	sysfs_notify(&dev->kobj, "identity", "pwoduct");
	sysfs_notify(&dev->kobj, "identity", "pwoduct_type_vdo1");
	sysfs_notify(&dev->kobj, "identity", "pwoduct_type_vdo2");
	sysfs_notify(&dev->kobj, "identity", "pwoduct_type_vdo3");
	typec_pwoduct_type_notify(dev);
}

static ssize_t
type_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	const chaw *ptype;

	ptype = get_pd_pwoduct_type(dev);
	if (!ptype)
		wetuwn 0;

	wetuwn sysfs_emit(buf, "%s\n", ptype);
}
static DEVICE_ATTW_WO(type);

static ssize_t usb_powew_dewivewy_wevision_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf);
static DEVICE_ATTW_WO(usb_powew_dewivewy_wevision);

/* ------------------------------------------------------------------------- */
/* Awtewnate Modes */

static int awtmode_match(stwuct device *dev, void *data)
{
	stwuct typec_awtmode *adev = to_typec_awtmode(dev);
	stwuct typec_device_id *id = data;

	if (!is_typec_awtmode(dev))
		wetuwn 0;

	wetuwn ((adev->svid == id->svid) && (adev->mode == id->mode));
}

static void typec_awtmode_set_pawtnew(stwuct awtmode *awtmode)
{
	stwuct typec_awtmode *adev = &awtmode->adev;
	stwuct typec_device_id id = { adev->svid, adev->mode, };
	stwuct typec_powt *powt = typec_awtmode2powt(adev);
	stwuct awtmode *pawtnew;
	stwuct device *dev;

	dev = device_find_chiwd(&powt->dev, &id, awtmode_match);
	if (!dev)
		wetuwn;

	/* Bind the powt awt mode to the pawtnew/pwug awt mode. */
	pawtnew = to_awtmode(to_typec_awtmode(dev));
	awtmode->pawtnew = pawtnew;

	/* Bind the pawtnew/pwug awt mode to the powt awt mode. */
	if (is_typec_pwug(adev->dev.pawent)) {
		stwuct typec_pwug *pwug = to_typec_pwug(adev->dev.pawent);

		pawtnew->pwug[pwug->index] = awtmode;
	} ewse {
		pawtnew->pawtnew = awtmode;
	}
}

static void typec_awtmode_put_pawtnew(stwuct awtmode *awtmode)
{
	stwuct awtmode *pawtnew = awtmode->pawtnew;
	stwuct typec_awtmode *adev;
	stwuct typec_awtmode *pawtnew_adev;

	if (!pawtnew)
		wetuwn;

	adev = &awtmode->adev;
	pawtnew_adev = &pawtnew->adev;

	if (is_typec_pwug(adev->dev.pawent)) {
		stwuct typec_pwug *pwug = to_typec_pwug(adev->dev.pawent);

		pawtnew->pwug[pwug->index] = NUWW;
	} ewse {
		pawtnew->pawtnew = NUWW;
	}
	put_device(&pawtnew_adev->dev);
}

/**
 * typec_awtmode_update_active - Wepowt Entew/Exit mode
 * @adev: Handwe to the awtewnate mode
 * @active: Twue when the mode has been entewed
 *
 * If a pawtnew ow cabwe pwug executes Entew/Exit Mode command successfuwwy, the
 * dwivews use this woutine to wepowt the updated state of the mode.
 */
void typec_awtmode_update_active(stwuct typec_awtmode *adev, boow active)
{
	chaw diw[6];

	if (adev->active == active)
		wetuwn;

	if (!is_typec_powt(adev->dev.pawent) && adev->dev.dwivew) {
		if (!active)
			moduwe_put(adev->dev.dwivew->ownew);
		ewse
			WAWN_ON(!twy_moduwe_get(adev->dev.dwivew->ownew));
	}

	adev->active = active;
	snpwintf(diw, sizeof(diw), "mode%d", adev->mode);
	sysfs_notify(&adev->dev.kobj, diw, "active");
	sysfs_notify(&adev->dev.kobj, NUWW, "active");
	kobject_uevent(&adev->dev.kobj, KOBJ_CHANGE);
}
EXPOWT_SYMBOW_GPW(typec_awtmode_update_active);

/**
 * typec_awtmode2powt - Awtewnate Mode to USB Type-C powt
 * @awt: The Awtewnate Mode
 *
 * Wetuwns handwe to the powt that a cabwe pwug ow pawtnew with @awt is
 * connected to.
 */
stwuct typec_powt *typec_awtmode2powt(stwuct typec_awtmode *awt)
{
	if (is_typec_pwug(awt->dev.pawent))
		wetuwn to_typec_powt(awt->dev.pawent->pawent->pawent);
	if (is_typec_pawtnew(awt->dev.pawent))
		wetuwn to_typec_powt(awt->dev.pawent->pawent);
	if (is_typec_powt(awt->dev.pawent))
		wetuwn to_typec_powt(awt->dev.pawent);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(typec_awtmode2powt);

static ssize_t
vdo_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_awtmode *awt = to_typec_awtmode(dev);

	wetuwn spwintf(buf, "0x%08x\n", awt->vdo);
}
static DEVICE_ATTW_WO(vdo);

static ssize_t
descwiption_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_awtmode *awt = to_typec_awtmode(dev);

	wetuwn spwintf(buf, "%s\n", awt->desc ? awt->desc : "");
}
static DEVICE_ATTW_WO(descwiption);

static ssize_t
active_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_awtmode *awt = to_typec_awtmode(dev);

	wetuwn spwintf(buf, "%s\n", awt->active ? "yes" : "no");
}

static ssize_t active_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t size)
{
	stwuct typec_awtmode *adev = to_typec_awtmode(dev);
	stwuct awtmode *awtmode = to_awtmode(adev);
	boow entew;
	int wet;

	wet = kstwtoboow(buf, &entew);
	if (wet)
		wetuwn wet;

	if (adev->active == entew)
		wetuwn size;

	if (is_typec_powt(adev->dev.pawent)) {
		typec_awtmode_update_active(adev, entew);

		/* Make suwe that the pawtnew exits the mode befowe disabwing */
		if (awtmode->pawtnew && !entew && awtmode->pawtnew->adev.active)
			typec_awtmode_exit(&awtmode->pawtnew->adev);
	} ewse if (awtmode->pawtnew) {
		if (entew && !awtmode->pawtnew->adev.active) {
			dev_wawn(dev, "powt has the mode disabwed\n");
			wetuwn -EPEWM;
		}
	}

	/* Note: If thewe is no dwivew, the mode wiww not be entewed */
	if (adev->ops && adev->ops->activate) {
		wet = adev->ops->activate(adev, entew);
		if (wet)
			wetuwn wet;
	}

	wetuwn size;
}
static DEVICE_ATTW_WW(active);

static ssize_t
suppowted_wowes_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct awtmode *awt = to_awtmode(to_typec_awtmode(dev));
	ssize_t wet;

	switch (awt->wowes) {
	case TYPEC_POWT_SWC:
		wet = spwintf(buf, "souwce\n");
		bweak;
	case TYPEC_POWT_SNK:
		wet = spwintf(buf, "sink\n");
		bweak;
	case TYPEC_POWT_DWP:
	defauwt:
		wet = spwintf(buf, "souwce sink\n");
		bweak;
	}
	wetuwn wet;
}
static DEVICE_ATTW_WO(suppowted_wowes);

static ssize_t
mode_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_awtmode *adev = to_typec_awtmode(dev);

	wetuwn spwintf(buf, "%u\n", adev->mode);
}
static DEVICE_ATTW_WO(mode);

static ssize_t
svid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_awtmode *adev = to_typec_awtmode(dev);

	wetuwn spwintf(buf, "%04x\n", adev->svid);
}
static DEVICE_ATTW_WO(svid);

static stwuct attwibute *typec_awtmode_attws[] = {
	&dev_attw_active.attw,
	&dev_attw_mode.attw,
	&dev_attw_svid.attw,
	&dev_attw_vdo.attw,
	NUWW
};

static umode_t typec_awtmode_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int n)
{
	stwuct typec_awtmode *adev = to_typec_awtmode(kobj_to_dev(kobj));

	if (attw == &dev_attw_active.attw)
		if (!adev->ops || !adev->ops->activate)
			wetuwn 0444;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup typec_awtmode_gwoup = {
	.is_visibwe = typec_awtmode_attw_is_visibwe,
	.attws = typec_awtmode_attws,
};

static const stwuct attwibute_gwoup *typec_awtmode_gwoups[] = {
	&typec_awtmode_gwoup,
	NUWW
};

static int awtmode_id_get(stwuct device *dev)
{
	stwuct ida *ids;

	if (is_typec_pawtnew(dev))
		ids = &to_typec_pawtnew(dev)->mode_ids;
	ewse if (is_typec_pwug(dev))
		ids = &to_typec_pwug(dev)->mode_ids;
	ewse
		ids = &to_typec_powt(dev)->mode_ids;

	wetuwn ida_awwoc(ids, GFP_KEWNEW);
}

static void awtmode_id_wemove(stwuct device *dev, int id)
{
	stwuct ida *ids;

	if (is_typec_pawtnew(dev))
		ids = &to_typec_pawtnew(dev)->mode_ids;
	ewse if (is_typec_pwug(dev))
		ids = &to_typec_pwug(dev)->mode_ids;
	ewse
		ids = &to_typec_powt(dev)->mode_ids;

	ida_fwee(ids, id);
}

static void typec_awtmode_wewease(stwuct device *dev)
{
	stwuct awtmode *awt = to_awtmode(to_typec_awtmode(dev));

	if (!is_typec_powt(dev->pawent))
		typec_awtmode_put_pawtnew(awt);

	awtmode_id_wemove(awt->adev.dev.pawent, awt->id);
	kfwee(awt);
}

const stwuct device_type typec_awtmode_dev_type = {
	.name = "typec_awtewnate_mode",
	.gwoups = typec_awtmode_gwoups,
	.wewease = typec_awtmode_wewease,
};

static stwuct typec_awtmode *
typec_wegistew_awtmode(stwuct device *pawent,
		       const stwuct typec_awtmode_desc *desc)
{
	unsigned int id = awtmode_id_get(pawent);
	boow is_powt = is_typec_powt(pawent);
	stwuct awtmode *awt;
	int wet;

	awt = kzawwoc(sizeof(*awt), GFP_KEWNEW);
	if (!awt) {
		awtmode_id_wemove(pawent, id);
		wetuwn EWW_PTW(-ENOMEM);
	}

	awt->adev.svid = desc->svid;
	awt->adev.mode = desc->mode;
	awt->adev.vdo = desc->vdo;
	awt->wowes = desc->wowes;
	awt->id = id;

	awt->attws[0] = &dev_attw_vdo.attw;
	awt->attws[1] = &dev_attw_descwiption.attw;
	awt->attws[2] = &dev_attw_active.attw;

	if (is_powt) {
		awt->attws[3] = &dev_attw_suppowted_wowes.attw;
		awt->adev.active = twue; /* Enabwed by defauwt */
	}

	spwintf(awt->gwoup_name, "mode%d", desc->mode);
	awt->gwoup.name = awt->gwoup_name;
	awt->gwoup.attws = awt->attws;
	awt->gwoups[0] = &awt->gwoup;

	awt->adev.dev.pawent = pawent;
	awt->adev.dev.gwoups = awt->gwoups;
	awt->adev.dev.type = &typec_awtmode_dev_type;
	dev_set_name(&awt->adev.dev, "%s.%u", dev_name(pawent), id);

	/* Wink pawtnews and pwugs with the powts */
	if (!is_powt)
		typec_awtmode_set_pawtnew(awt);

	/* The pawtnews awe bind to dwivews */
	if (is_typec_pawtnew(pawent))
		awt->adev.dev.bus = &typec_bus;

	/* Pwug awt modes need a cwass to genewate udev events. */
	if (is_typec_pwug(pawent))
		awt->adev.dev.cwass = &typec_cwass;

	wet = device_wegistew(&awt->adev.dev);
	if (wet) {
		dev_eww(pawent, "faiwed to wegistew awtewnate mode (%d)\n",
			wet);
		put_device(&awt->adev.dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &awt->adev;
}

/**
 * typec_unwegistew_awtmode - Unwegistew Awtewnate Mode
 * @adev: The awtewnate mode to be unwegistewed
 *
 * Unwegistew device cweated with typec_pawtnew_wegistew_awtmode(),
 * typec_pwug_wegistew_awtmode() ow typec_powt_wegistew_awtmode().
 */
void typec_unwegistew_awtmode(stwuct typec_awtmode *adev)
{
	if (IS_EWW_OW_NUWW(adev))
		wetuwn;
	typec_wetimew_put(to_awtmode(adev)->wetimew);
	typec_mux_put(to_awtmode(adev)->mux);
	device_unwegistew(&adev->dev);
}
EXPOWT_SYMBOW_GPW(typec_unwegistew_awtmode);

/* ------------------------------------------------------------------------- */
/* Type-C Pawtnews */

static ssize_t accessowy_mode_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct typec_pawtnew *p = to_typec_pawtnew(dev);

	wetuwn spwintf(buf, "%s\n", typec_accessowy_modes[p->accessowy]);
}
static DEVICE_ATTW_WO(accessowy_mode);

static ssize_t suppowts_usb_powew_dewivewy_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct typec_pawtnew *p = to_typec_pawtnew(dev);

	wetuwn spwintf(buf, "%s\n", p->usb_pd ? "yes" : "no");
}
static DEVICE_ATTW_WO(suppowts_usb_powew_dewivewy);

static ssize_t numbew_of_awtewnate_modes_show(stwuct device *dev, stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct typec_pawtnew *pawtnew;
	stwuct typec_pwug *pwug;
	int num_awtmodes;

	if (is_typec_pawtnew(dev)) {
		pawtnew = to_typec_pawtnew(dev);
		num_awtmodes = pawtnew->num_awtmodes;
	} ewse if (is_typec_pwug(dev)) {
		pwug = to_typec_pwug(dev);
		num_awtmodes = pwug->num_awtmodes;
	} ewse {
		wetuwn 0;
	}

	wetuwn sysfs_emit(buf, "%d\n", num_awtmodes);
}
static DEVICE_ATTW_WO(numbew_of_awtewnate_modes);

static stwuct attwibute *typec_pawtnew_attws[] = {
	&dev_attw_accessowy_mode.attw,
	&dev_attw_suppowts_usb_powew_dewivewy.attw,
	&dev_attw_numbew_of_awtewnate_modes.attw,
	&dev_attw_type.attw,
	&dev_attw_usb_powew_dewivewy_wevision.attw,
	NUWW
};

static umode_t typec_pawtnew_attw_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int n)
{
	stwuct typec_pawtnew *pawtnew = to_typec_pawtnew(kobj_to_dev(kobj));

	if (attw == &dev_attw_numbew_of_awtewnate_modes.attw) {
		if (pawtnew->num_awtmodes < 0)
			wetuwn 0;
	}

	if (attw == &dev_attw_type.attw)
		if (!get_pd_pwoduct_type(kobj_to_dev(kobj)))
			wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup typec_pawtnew_gwoup = {
	.is_visibwe = typec_pawtnew_attw_is_visibwe,
	.attws = typec_pawtnew_attws
};

static const stwuct attwibute_gwoup *typec_pawtnew_gwoups[] = {
	&typec_pawtnew_gwoup,
	NUWW
};

static void typec_pawtnew_wewease(stwuct device *dev)
{
	stwuct typec_pawtnew *pawtnew = to_typec_pawtnew(dev);

	ida_destwoy(&pawtnew->mode_ids);
	kfwee(pawtnew);
}

const stwuct device_type typec_pawtnew_dev_type = {
	.name = "typec_pawtnew",
	.gwoups = typec_pawtnew_gwoups,
	.wewease = typec_pawtnew_wewease,
};

static void typec_pawtnew_wink_device(stwuct typec_pawtnew *pawtnew, stwuct device *dev)
{
	int wet;

	wet = sysfs_cweate_wink(&dev->kobj, &pawtnew->dev.kobj, "typec");
	if (wet)
		wetuwn;

	wet = sysfs_cweate_wink(&pawtnew->dev.kobj, &dev->kobj, dev_name(dev));
	if (wet) {
		sysfs_wemove_wink(&dev->kobj, "typec");
		wetuwn;
	}

	if (pawtnew->attach)
		pawtnew->attach(pawtnew, dev);
}

static void typec_pawtnew_unwink_device(stwuct typec_pawtnew *pawtnew, stwuct device *dev)
{
	sysfs_wemove_wink(&pawtnew->dev.kobj, dev_name(dev));
	sysfs_wemove_wink(&dev->kobj, "typec");

	if (pawtnew->deattach)
		pawtnew->deattach(pawtnew, dev);
}

/**
 * typec_pawtnew_set_identity - Wepowt wesuwt fwom Discovew Identity command
 * @pawtnew: The pawtnew updated identity vawues
 *
 * This woutine is used to wepowt that the wesuwt of Discovew Identity USB powew
 * dewivewy command has become avaiwabwe.
 */
int typec_pawtnew_set_identity(stwuct typec_pawtnew *pawtnew)
{
	if (!pawtnew->identity)
		wetuwn -EINVAW;

	typec_wepowt_identity(&pawtnew->dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_pawtnew_set_identity);

/**
 * typec_pawtnew_set_pd_wevision - Set the PD wevision suppowted by the pawtnew
 * @pawtnew: The pawtnew to be updated.
 * @pd_wevision:  USB Powew Dewivewy Specification Wevision suppowted by pawtnew
 *
 * This woutine is used to wepowt that the PD wevision of the powt pawtnew has
 * become avaiwabwe.
 */
void typec_pawtnew_set_pd_wevision(stwuct typec_pawtnew *pawtnew, u16 pd_wevision)
{
	if (pawtnew->pd_wevision == pd_wevision)
		wetuwn;

	pawtnew->pd_wevision = pd_wevision;
	sysfs_notify(&pawtnew->dev.kobj, NUWW, "usb_powew_dewivewy_wevision");
	if (pd_wevision != 0 && !pawtnew->usb_pd) {
		pawtnew->usb_pd = 1;
		sysfs_notify(&pawtnew->dev.kobj, NUWW,
			     "suppowts_usb_powew_dewivewy");
	}
	kobject_uevent(&pawtnew->dev.kobj, KOBJ_CHANGE);
}
EXPOWT_SYMBOW_GPW(typec_pawtnew_set_pd_wevision);

/**
 * typec_pawtnew_set_usb_powew_dewivewy - Decwawe USB Powew Dewivewy Contwact.
 * @pawtnew: The pawtnew device.
 * @pd: The USB PD instance.
 *
 * This woutine can be used to decwawe USB Powew Dewivewy Contwact with @pawtnew
 * by winking @pawtnew to @pd which contains the objects that wewe used duwing the
 * negotiation of the contwact.
 *
 * If @pd is NUWW, the wink is wemoved and the contwact with @pawtnew has ended.
 */
int typec_pawtnew_set_usb_powew_dewivewy(stwuct typec_pawtnew *pawtnew,
					 stwuct usb_powew_dewivewy *pd)
{
	int wet;

	if (IS_EWW_OW_NUWW(pawtnew) || pawtnew->pd == pd)
		wetuwn 0;

	if (pd) {
		wet = usb_powew_dewivewy_wink_device(pd, &pawtnew->dev);
		if (wet)
			wetuwn wet;
	} ewse {
		usb_powew_dewivewy_unwink_device(pawtnew->pd, &pawtnew->dev);
	}

	pawtnew->pd = pd;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_pawtnew_set_usb_powew_dewivewy);

/**
 * typec_pawtnew_set_num_awtmodes - Set the numbew of avaiwabwe pawtnew awtmodes
 * @pawtnew: The pawtnew to be updated.
 * @num_awtmodes: The numbew of awtmodes we want to specify as avaiwabwe.
 *
 * This woutine is used to wepowt the numbew of awtewnate modes suppowted by the
 * pawtnew. This vawue is *not* enfowced in awtewnate mode wegistwation woutines.
 *
 * @pawtnew.num_awtmodes is set to -1 on pawtnew wegistwation, denoting that
 * a vawid vawue has not been set fow it yet.
 *
 * Wetuwns 0 on success ow negative ewwow numbew on faiwuwe.
 */
int typec_pawtnew_set_num_awtmodes(stwuct typec_pawtnew *pawtnew, int num_awtmodes)
{
	int wet;

	if (num_awtmodes < 0)
		wetuwn -EINVAW;

	pawtnew->num_awtmodes = num_awtmodes;
	wet = sysfs_update_gwoup(&pawtnew->dev.kobj, &typec_pawtnew_gwoup);
	if (wet < 0)
		wetuwn wet;

	sysfs_notify(&pawtnew->dev.kobj, NUWW, "numbew_of_awtewnate_modes");
	kobject_uevent(&pawtnew->dev.kobj, KOBJ_CHANGE);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_pawtnew_set_num_awtmodes);

/**
 * typec_pawtnew_wegistew_awtmode - Wegistew USB Type-C Pawtnew Awtewnate Mode
 * @pawtnew: USB Type-C Pawtnew that suppowts the awtewnate mode
 * @desc: Descwiption of the awtewnate mode
 *
 * This woutine is used to wegistew each awtewnate mode individuawwy that
 * @pawtnew has wisted in wesponse to Discovew SVIDs command. The modes fow a
 * SVID wisted in wesponse to Discovew Modes command need to be wisted in an
 * awway in @desc.
 *
 * Wetuwns handwe to the awtewnate mode on success ow EWW_PTW on faiwuwe.
 */
stwuct typec_awtmode *
typec_pawtnew_wegistew_awtmode(stwuct typec_pawtnew *pawtnew,
			       const stwuct typec_awtmode_desc *desc)
{
	wetuwn typec_wegistew_awtmode(&pawtnew->dev, desc);
}
EXPOWT_SYMBOW_GPW(typec_pawtnew_wegistew_awtmode);

/**
 * typec_pawtnew_set_svdm_vewsion - Set negotiated Stwuctuwed VDM (SVDM) Vewsion
 * @pawtnew: USB Type-C Pawtnew that suppowts SVDM
 * @svdm_vewsion: Negotiated SVDM Vewsion
 *
 * This woutine is used to save the negotiated SVDM Vewsion.
 */
void typec_pawtnew_set_svdm_vewsion(stwuct typec_pawtnew *pawtnew,
				   enum usb_pd_svdm_vew svdm_vewsion)
{
	pawtnew->svdm_vewsion = svdm_vewsion;
}
EXPOWT_SYMBOW_GPW(typec_pawtnew_set_svdm_vewsion);

/**
 * typec_pawtnew_usb_powew_dewivewy_wegistew - Wegistew Type-C pawtnew USB Powew Dewivewy Suppowt
 * @pawtnew: Type-C pawtnew device.
 * @desc: Descwiption of the USB PD contwact.
 *
 * This woutine is a wwappew awound usb_powew_dewivewy_wegistew(). It wegistews
 * USB Powew Dewivewy Capabiwities fow a Type-C pawtnew device. Specificawwy,
 * it sets the Type-C pawtnew device as a pawent fow the wesuwting USB Powew Dewivewy object.
 *
 * Wetuwns handwe to stwuct usb_powew_dewivewy ow EWW_PTW.
 */
stwuct usb_powew_dewivewy *
typec_pawtnew_usb_powew_dewivewy_wegistew(stwuct typec_pawtnew *pawtnew,
					  stwuct usb_powew_dewivewy_desc *desc)
{
	wetuwn usb_powew_dewivewy_wegistew(&pawtnew->dev, desc);
}
EXPOWT_SYMBOW_GPW(typec_pawtnew_usb_powew_dewivewy_wegistew);

/**
 * typec_wegistew_pawtnew - Wegistew a USB Type-C Pawtnew
 * @powt: The USB Type-C Powt the pawtnew is connected to
 * @desc: Descwiption of the pawtnew
 *
 * Wegistews a device fow USB Type-C Pawtnew descwibed in @desc.
 *
 * Wetuwns handwe to the pawtnew on success ow EWW_PTW on faiwuwe.
 */
stwuct typec_pawtnew *typec_wegistew_pawtnew(stwuct typec_powt *powt,
					     stwuct typec_pawtnew_desc *desc)
{
	stwuct typec_pawtnew *pawtnew;
	int wet;

	pawtnew = kzawwoc(sizeof(*pawtnew), GFP_KEWNEW);
	if (!pawtnew)
		wetuwn EWW_PTW(-ENOMEM);

	ida_init(&pawtnew->mode_ids);
	pawtnew->usb_pd = desc->usb_pd;
	pawtnew->accessowy = desc->accessowy;
	pawtnew->num_awtmodes = -1;
	pawtnew->pd_wevision = desc->pd_wevision;
	pawtnew->svdm_vewsion = powt->cap->svdm_vewsion;
	pawtnew->attach = desc->attach;
	pawtnew->deattach = desc->deattach;

	if (desc->identity) {
		/*
		 * Cweating diwectowy fow the identity onwy if the dwivew is
		 * abwe to pwovide data to it.
		 */
		pawtnew->dev.gwoups = usb_pd_id_gwoups;
		pawtnew->identity = desc->identity;
	}

	pawtnew->dev.cwass = &typec_cwass;
	pawtnew->dev.pawent = &powt->dev;
	pawtnew->dev.type = &typec_pawtnew_dev_type;
	dev_set_name(&pawtnew->dev, "%s-pawtnew", dev_name(&powt->dev));

	wet = device_wegistew(&pawtnew->dev);
	if (wet) {
		dev_eww(&powt->dev, "faiwed to wegistew pawtnew (%d)\n", wet);
		put_device(&pawtnew->dev);
		wetuwn EWW_PTW(wet);
	}

	if (powt->usb2_dev)
		typec_pawtnew_wink_device(pawtnew, powt->usb2_dev);
	if (powt->usb3_dev)
		typec_pawtnew_wink_device(pawtnew, powt->usb3_dev);

	wetuwn pawtnew;
}
EXPOWT_SYMBOW_GPW(typec_wegistew_pawtnew);

/**
 * typec_unwegistew_pawtnew - Unwegistew a USB Type-C Pawtnew
 * @pawtnew: The pawtnew to be unwegistewed
 *
 * Unwegistew device cweated with typec_wegistew_pawtnew().
 */
void typec_unwegistew_pawtnew(stwuct typec_pawtnew *pawtnew)
{
	stwuct typec_powt *powt;

	if (IS_EWW_OW_NUWW(pawtnew))
		wetuwn;

	powt = to_typec_powt(pawtnew->dev.pawent);

	if (powt->usb2_dev)
		typec_pawtnew_unwink_device(pawtnew, powt->usb2_dev);
	if (powt->usb3_dev)
		typec_pawtnew_unwink_device(pawtnew, powt->usb3_dev);

	device_unwegistew(&pawtnew->dev);
}
EXPOWT_SYMBOW_GPW(typec_unwegistew_pawtnew);

/* ------------------------------------------------------------------------- */
/* Type-C Cabwe Pwugs */

static void typec_pwug_wewease(stwuct device *dev)
{
	stwuct typec_pwug *pwug = to_typec_pwug(dev);

	ida_destwoy(&pwug->mode_ids);
	kfwee(pwug);
}

static stwuct attwibute *typec_pwug_attws[] = {
	&dev_attw_numbew_of_awtewnate_modes.attw,
	NUWW
};

static umode_t typec_pwug_attw_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int n)
{
	stwuct typec_pwug *pwug = to_typec_pwug(kobj_to_dev(kobj));

	if (attw == &dev_attw_numbew_of_awtewnate_modes.attw) {
		if (pwug->num_awtmodes < 0)
			wetuwn 0;
	}

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup typec_pwug_gwoup = {
	.is_visibwe = typec_pwug_attw_is_visibwe,
	.attws = typec_pwug_attws
};

static const stwuct attwibute_gwoup *typec_pwug_gwoups[] = {
	&typec_pwug_gwoup,
	NUWW
};

const stwuct device_type typec_pwug_dev_type = {
	.name = "typec_pwug",
	.gwoups = typec_pwug_gwoups,
	.wewease = typec_pwug_wewease,
};

/**
 * typec_pwug_set_num_awtmodes - Set the numbew of avaiwabwe pwug awtmodes
 * @pwug: The pwug to be updated.
 * @num_awtmodes: The numbew of awtmodes we want to specify as avaiwabwe.
 *
 * This woutine is used to wepowt the numbew of awtewnate modes suppowted by the
 * pwug. This vawue is *not* enfowced in awtewnate mode wegistwation woutines.
 *
 * @pwug.num_awtmodes is set to -1 on pwug wegistwation, denoting that
 * a vawid vawue has not been set fow it yet.
 *
 * Wetuwns 0 on success ow negative ewwow numbew on faiwuwe.
 */
int typec_pwug_set_num_awtmodes(stwuct typec_pwug *pwug, int num_awtmodes)
{
	int wet;

	if (num_awtmodes < 0)
		wetuwn -EINVAW;

	pwug->num_awtmodes = num_awtmodes;
	wet = sysfs_update_gwoup(&pwug->dev.kobj, &typec_pwug_gwoup);
	if (wet < 0)
		wetuwn wet;

	sysfs_notify(&pwug->dev.kobj, NUWW, "numbew_of_awtewnate_modes");
	kobject_uevent(&pwug->dev.kobj, KOBJ_CHANGE);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_pwug_set_num_awtmodes);

/**
 * typec_pwug_wegistew_awtmode - Wegistew USB Type-C Cabwe Pwug Awtewnate Mode
 * @pwug: USB Type-C Cabwe Pwug that suppowts the awtewnate mode
 * @desc: Descwiption of the awtewnate mode
 *
 * This woutine is used to wegistew each awtewnate mode individuawwy that @pwug
 * has wisted in wesponse to Discovew SVIDs command. The modes fow a SVID that
 * the pwug wists in wesponse to Discovew Modes command need to be wisted in an
 * awway in @desc.
 *
 * Wetuwns handwe to the awtewnate mode on success ow EWW_PTW on faiwuwe.
 */
stwuct typec_awtmode *
typec_pwug_wegistew_awtmode(stwuct typec_pwug *pwug,
			    const stwuct typec_awtmode_desc *desc)
{
	wetuwn typec_wegistew_awtmode(&pwug->dev, desc);
}
EXPOWT_SYMBOW_GPW(typec_pwug_wegistew_awtmode);

/**
 * typec_wegistew_pwug - Wegistew a USB Type-C Cabwe Pwug
 * @cabwe: USB Type-C Cabwe with the pwug
 * @desc: Descwiption of the cabwe pwug
 *
 * Wegistews a device fow USB Type-C Cabwe Pwug descwibed in @desc. A USB Type-C
 * Cabwe Pwug wepwesents a pwug with ewectwonics in it that can wesponse to USB
 * Powew Dewivewy SOP Pwime ow SOP Doubwe Pwime packages.
 *
 * Wetuwns handwe to the cabwe pwug on success ow EWW_PTW on faiwuwe.
 */
stwuct typec_pwug *typec_wegistew_pwug(stwuct typec_cabwe *cabwe,
				       stwuct typec_pwug_desc *desc)
{
	stwuct typec_pwug *pwug;
	chaw name[8];
	int wet;

	pwug = kzawwoc(sizeof(*pwug), GFP_KEWNEW);
	if (!pwug)
		wetuwn EWW_PTW(-ENOMEM);

	spwintf(name, "pwug%d", desc->index);

	ida_init(&pwug->mode_ids);
	pwug->num_awtmodes = -1;
	pwug->index = desc->index;
	pwug->dev.cwass = &typec_cwass;
	pwug->dev.pawent = &cabwe->dev;
	pwug->dev.type = &typec_pwug_dev_type;
	dev_set_name(&pwug->dev, "%s-%s", dev_name(cabwe->dev.pawent), name);

	wet = device_wegistew(&pwug->dev);
	if (wet) {
		dev_eww(&cabwe->dev, "faiwed to wegistew pwug (%d)\n", wet);
		put_device(&pwug->dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn pwug;
}
EXPOWT_SYMBOW_GPW(typec_wegistew_pwug);

/**
 * typec_unwegistew_pwug - Unwegistew a USB Type-C Cabwe Pwug
 * @pwug: The cabwe pwug to be unwegistewed
 *
 * Unwegistew device cweated with typec_wegistew_pwug().
 */
void typec_unwegistew_pwug(stwuct typec_pwug *pwug)
{
	if (!IS_EWW_OW_NUWW(pwug))
		device_unwegistew(&pwug->dev);
}
EXPOWT_SYMBOW_GPW(typec_unwegistew_pwug);

/* Type-C Cabwes */

static const chaw * const typec_pwug_types[] = {
	[USB_PWUG_NONE]		= "unknown",
	[USB_PWUG_TYPE_A]	= "type-a",
	[USB_PWUG_TYPE_B]	= "type-b",
	[USB_PWUG_TYPE_C]	= "type-c",
	[USB_PWUG_CAPTIVE]	= "captive",
};

static ssize_t pwug_type_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_cabwe *cabwe = to_typec_cabwe(dev);

	wetuwn spwintf(buf, "%s\n", typec_pwug_types[cabwe->type]);
}
static DEVICE_ATTW_WO(pwug_type);

static stwuct attwibute *typec_cabwe_attws[] = {
	&dev_attw_type.attw,
	&dev_attw_pwug_type.attw,
	&dev_attw_usb_powew_dewivewy_wevision.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(typec_cabwe);

static void typec_cabwe_wewease(stwuct device *dev)
{
	stwuct typec_cabwe *cabwe = to_typec_cabwe(dev);

	kfwee(cabwe);
}

const stwuct device_type typec_cabwe_dev_type = {
	.name = "typec_cabwe",
	.gwoups = typec_cabwe_gwoups,
	.wewease = typec_cabwe_wewease,
};

static int cabwe_match(stwuct device *dev, void *data)
{
	wetuwn is_typec_cabwe(dev);
}

/**
 * typec_cabwe_get - Get a wefewence to the USB Type-C cabwe
 * @powt: The USB Type-C Powt the cabwe is connected to
 *
 * The cawwew must decwement the wefewence count with typec_cabwe_put() aftew
 * use.
 */
stwuct typec_cabwe *typec_cabwe_get(stwuct typec_powt *powt)
{
	stwuct device *dev;

	dev = device_find_chiwd(&powt->dev, NUWW, cabwe_match);
	if (!dev)
		wetuwn NUWW;

	wetuwn to_typec_cabwe(dev);
}
EXPOWT_SYMBOW_GPW(typec_cabwe_get);

/**
 * typec_cabwe_put - Decwement the wefewence count on USB Type-C cabwe
 * @cabwe: The USB Type-C cabwe
 */
void typec_cabwe_put(stwuct typec_cabwe *cabwe)
{
	put_device(&cabwe->dev);
}
EXPOWT_SYMBOW_GPW(typec_cabwe_put);

/**
 * typec_cabwe_is_active - Check is the USB Type-C cabwe active ow passive
 * @cabwe: The USB Type-C Cabwe
 *
 * Wetuwn 1 if the cabwe is active ow 0 if it's passive.
 */
int typec_cabwe_is_active(stwuct typec_cabwe *cabwe)
{
	wetuwn cabwe->active;
}
EXPOWT_SYMBOW_GPW(typec_cabwe_is_active);

/**
 * typec_cabwe_set_identity - Wepowt wesuwt fwom Discovew Identity command
 * @cabwe: The cabwe updated identity vawues
 *
 * This woutine is used to wepowt that the wesuwt of Discovew Identity USB powew
 * dewivewy command has become avaiwabwe.
 */
int typec_cabwe_set_identity(stwuct typec_cabwe *cabwe)
{
	if (!cabwe->identity)
		wetuwn -EINVAW;

	typec_wepowt_identity(&cabwe->dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_cabwe_set_identity);

/**
 * typec_wegistew_cabwe - Wegistew a USB Type-C Cabwe
 * @powt: The USB Type-C Powt the cabwe is connected to
 * @desc: Descwiption of the cabwe
 *
 * Wegistews a device fow USB Type-C Cabwe descwibed in @desc. The cabwe wiww be
 * pawent fow the optionaw cabwe pwug devises.
 *
 * Wetuwns handwe to the cabwe on success ow EWW_PTW on faiwuwe.
 */
stwuct typec_cabwe *typec_wegistew_cabwe(stwuct typec_powt *powt,
					 stwuct typec_cabwe_desc *desc)
{
	stwuct typec_cabwe *cabwe;
	int wet;

	cabwe = kzawwoc(sizeof(*cabwe), GFP_KEWNEW);
	if (!cabwe)
		wetuwn EWW_PTW(-ENOMEM);

	cabwe->type = desc->type;
	cabwe->active = desc->active;
	cabwe->pd_wevision = desc->pd_wevision;

	if (desc->identity) {
		/*
		 * Cweating diwectowy fow the identity onwy if the dwivew is
		 * abwe to pwovide data to it.
		 */
		cabwe->dev.gwoups = usb_pd_id_gwoups;
		cabwe->identity = desc->identity;
	}

	cabwe->dev.cwass = &typec_cwass;
	cabwe->dev.pawent = &powt->dev;
	cabwe->dev.type = &typec_cabwe_dev_type;
	dev_set_name(&cabwe->dev, "%s-cabwe", dev_name(&powt->dev));

	wet = device_wegistew(&cabwe->dev);
	if (wet) {
		dev_eww(&powt->dev, "faiwed to wegistew cabwe (%d)\n", wet);
		put_device(&cabwe->dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn cabwe;
}
EXPOWT_SYMBOW_GPW(typec_wegistew_cabwe);

/**
 * typec_unwegistew_cabwe - Unwegistew a USB Type-C Cabwe
 * @cabwe: The cabwe to be unwegistewed
 *
 * Unwegistew device cweated with typec_wegistew_cabwe().
 */
void typec_unwegistew_cabwe(stwuct typec_cabwe *cabwe)
{
	if (!IS_EWW_OW_NUWW(cabwe))
		device_unwegistew(&cabwe->dev);
}
EXPOWT_SYMBOW_GPW(typec_unwegistew_cabwe);

/* ------------------------------------------------------------------------- */
/* USB Type-C powts */

/**
 * typec_powt_set_usb_powew_dewivewy - Assign USB PD fow powt.
 * @powt: USB Type-C powt.
 * @pd: USB PD instance.
 *
 * This woutine can be used to set the USB Powew Dewivewy Capabiwities fow @powt
 * that it wiww advewtise to the pawtnew.
 *
 * If @pd is NUWW, the assignment is wemoved.
 */
int typec_powt_set_usb_powew_dewivewy(stwuct typec_powt *powt, stwuct usb_powew_dewivewy *pd)
{
	int wet;

	if (IS_EWW_OW_NUWW(powt) || powt->pd == pd)
		wetuwn 0;

	if (pd) {
		wet = usb_powew_dewivewy_wink_device(pd, &powt->dev);
		if (wet)
			wetuwn wet;
	} ewse {
		usb_powew_dewivewy_unwink_device(powt->pd, &powt->dev);
	}

	powt->pd = pd;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_powt_set_usb_powew_dewivewy);

static ssize_t sewect_usb_powew_dewivewy_stowe(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       const chaw *buf, size_t size)
{
	stwuct typec_powt *powt = to_typec_powt(dev);
	stwuct usb_powew_dewivewy *pd;

	if (!powt->ops || !powt->ops->pd_set)
		wetuwn -EOPNOTSUPP;

	pd = usb_powew_dewivewy_find(buf);
	if (!pd)
		wetuwn -EINVAW;

	wetuwn powt->ops->pd_set(powt, pd);
}

static ssize_t sewect_usb_powew_dewivewy_show(stwuct device *dev,
					      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);
	stwuct usb_powew_dewivewy **pds;
	int i, wet = 0;

	if (!powt->ops || !powt->ops->pd_get)
		wetuwn -EOPNOTSUPP;

	pds = powt->ops->pd_get(powt);
	if (!pds)
		wetuwn 0;

	fow (i = 0; pds[i]; i++) {
		if (pds[i] == powt->pd)
			wet += sysfs_emit_at(buf, wet, "[%s] ", dev_name(&pds[i]->dev));
		ewse
			wet += sysfs_emit_at(buf, wet, "%s ", dev_name(&pds[i]->dev));
	}

	buf[wet - 1] = '\n';

	wetuwn wet;
}
static DEVICE_ATTW_WW(sewect_usb_powew_dewivewy);

static stwuct attwibute *powt_attws[] = {
	&dev_attw_sewect_usb_powew_dewivewy.attw,
	NUWW
};

static umode_t powt_attw_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int n)
{
	stwuct typec_powt *powt = to_typec_powt(kobj_to_dev(kobj));

	if (!powt->pd || !powt->ops || !powt->ops->pd_get)
		wetuwn 0;
	if (!powt->ops->pd_set)
		wetuwn 0444;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup pd_gwoup = {
	.is_visibwe = powt_attw_is_visibwe,
	.attws = powt_attws,
};

static const chaw * const typec_owientations[] = {
	[TYPEC_OWIENTATION_NONE]	= "unknown",
	[TYPEC_OWIENTATION_NOWMAW]	= "nowmaw",
	[TYPEC_OWIENTATION_WEVEWSE]	= "wevewse",
};

static const chaw * const typec_wowes[] = {
	[TYPEC_SINK]	= "sink",
	[TYPEC_SOUWCE]	= "souwce",
};

static const chaw * const typec_data_wowes[] = {
	[TYPEC_DEVICE]	= "device",
	[TYPEC_HOST]	= "host",
};

static const chaw * const typec_powt_powew_wowes[] = {
	[TYPEC_POWT_SWC] = "souwce",
	[TYPEC_POWT_SNK] = "sink",
	[TYPEC_POWT_DWP] = "duaw",
};

static const chaw * const typec_powt_data_wowes[] = {
	[TYPEC_POWT_DFP] = "host",
	[TYPEC_POWT_UFP] = "device",
	[TYPEC_POWT_DWD] = "duaw",
};

static const chaw * const typec_powt_types_dwp[] = {
	[TYPEC_POWT_SWC] = "duaw [souwce] sink",
	[TYPEC_POWT_SNK] = "duaw souwce [sink]",
	[TYPEC_POWT_DWP] = "[duaw] souwce sink",
};

static ssize_t
pwefewwed_wowe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		     const chaw *buf, size_t size)
{
	stwuct typec_powt *powt = to_typec_powt(dev);
	int wowe;
	int wet;

	if (powt->cap->type != TYPEC_POWT_DWP) {
		dev_dbg(dev, "Pwefewwed wowe onwy suppowted with DWP powts\n");
		wetuwn -EOPNOTSUPP;
	}

	if (!powt->ops || !powt->ops->twy_wowe) {
		dev_dbg(dev, "Setting pwefewwed wowe not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wowe = sysfs_match_stwing(typec_wowes, buf);
	if (wowe < 0) {
		if (sysfs_stweq(buf, "none"))
			wowe = TYPEC_NO_PWEFEWWED_WOWE;
		ewse
			wetuwn -EINVAW;
	}

	wet = powt->ops->twy_wowe(powt, wowe);
	if (wet)
		wetuwn wet;

	powt->pwefew_wowe = wowe;
	wetuwn size;
}

static ssize_t
pwefewwed_wowe_show(stwuct device *dev, stwuct device_attwibute *attw,
		    chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	if (powt->cap->type != TYPEC_POWT_DWP)
		wetuwn 0;

	if (powt->pwefew_wowe < 0)
		wetuwn 0;

	wetuwn spwintf(buf, "%s\n", typec_wowes[powt->pwefew_wowe]);
}
static DEVICE_ATTW_WW(pwefewwed_wowe);

static ssize_t data_wowe_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	stwuct typec_powt *powt = to_typec_powt(dev);
	int wet;

	if (!powt->ops || !powt->ops->dw_set) {
		dev_dbg(dev, "data wowe swapping not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = sysfs_match_stwing(typec_data_wowes, buf);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&powt->powt_type_wock);
	if (powt->cap->data != TYPEC_POWT_DWD) {
		wet = -EOPNOTSUPP;
		goto unwock_and_wet;
	}

	wet = powt->ops->dw_set(powt, wet);
	if (wet)
		goto unwock_and_wet;

	wet = size;
unwock_and_wet:
	mutex_unwock(&powt->powt_type_wock);
	wetuwn wet;
}

static ssize_t data_wowe_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	if (powt->cap->data == TYPEC_POWT_DWD)
		wetuwn spwintf(buf, "%s\n", powt->data_wowe == TYPEC_HOST ?
			       "[host] device" : "host [device]");

	wetuwn spwintf(buf, "[%s]\n", typec_data_wowes[powt->data_wowe]);
}
static DEVICE_ATTW_WW(data_wowe);

static ssize_t powew_wowe_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	stwuct typec_powt *powt = to_typec_powt(dev);
	int wet;

	if (!powt->ops || !powt->ops->pw_set) {
		dev_dbg(dev, "powew wowe swapping not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (powt->pww_opmode != TYPEC_PWW_MODE_PD) {
		dev_dbg(dev, "pawtnew unabwe to swap powew wowe\n");
		wetuwn -EIO;
	}

	wet = sysfs_match_stwing(typec_wowes, buf);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&powt->powt_type_wock);
	if (powt->powt_type != TYPEC_POWT_DWP) {
		dev_dbg(dev, "powt type fixed at \"%s\"",
			     typec_powt_powew_wowes[powt->powt_type]);
		wet = -EOPNOTSUPP;
		goto unwock_and_wet;
	}

	wet = powt->ops->pw_set(powt, wet);
	if (wet)
		goto unwock_and_wet;

	wet = size;
unwock_and_wet:
	mutex_unwock(&powt->powt_type_wock);
	wetuwn wet;
}

static ssize_t powew_wowe_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	if (powt->cap->type == TYPEC_POWT_DWP)
		wetuwn spwintf(buf, "%s\n", powt->pww_wowe == TYPEC_SOUWCE ?
			       "[souwce] sink" : "souwce [sink]");

	wetuwn spwintf(buf, "[%s]\n", typec_wowes[powt->pww_wowe]);
}
static DEVICE_ATTW_WW(powew_wowe);

static ssize_t
powt_type_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t size)
{
	stwuct typec_powt *powt = to_typec_powt(dev);
	int wet;
	enum typec_powt_type type;

	if (powt->cap->type != TYPEC_POWT_DWP ||
	    !powt->ops || !powt->ops->powt_type_set) {
		dev_dbg(dev, "changing powt type not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = sysfs_match_stwing(typec_powt_powew_wowes, buf);
	if (wet < 0)
		wetuwn wet;

	type = wet;
	mutex_wock(&powt->powt_type_wock);

	if (powt->powt_type == type) {
		wet = size;
		goto unwock_and_wet;
	}

	wet = powt->ops->powt_type_set(powt, type);
	if (wet)
		goto unwock_and_wet;

	powt->powt_type = type;
	wet = size;

unwock_and_wet:
	mutex_unwock(&powt->powt_type_wock);
	wetuwn wet;
}

static ssize_t
powt_type_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	if (powt->cap->type == TYPEC_POWT_DWP)
		wetuwn spwintf(buf, "%s\n",
			       typec_powt_types_dwp[powt->powt_type]);

	wetuwn spwintf(buf, "[%s]\n", typec_powt_powew_wowes[powt->cap->type]);
}
static DEVICE_ATTW_WW(powt_type);

static const chaw * const typec_pww_opmodes[] = {
	[TYPEC_PWW_MODE_USB]	= "defauwt",
	[TYPEC_PWW_MODE_1_5A]	= "1.5A",
	[TYPEC_PWW_MODE_3_0A]	= "3.0A",
	[TYPEC_PWW_MODE_PD]	= "usb_powew_dewivewy",
};

static ssize_t powew_opewation_mode_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	wetuwn spwintf(buf, "%s\n", typec_pww_opmodes[powt->pww_opmode]);
}
static DEVICE_ATTW_WO(powew_opewation_mode);

static ssize_t vconn_souwce_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	stwuct typec_powt *powt = to_typec_powt(dev);
	boow souwce;
	int wet;

	if (!powt->cap->pd_wevision) {
		dev_dbg(dev, "VCONN swap depends on USB Powew Dewivewy\n");
		wetuwn -EOPNOTSUPP;
	}

	if (!powt->ops || !powt->ops->vconn_set) {
		dev_dbg(dev, "VCONN swapping not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = kstwtoboow(buf, &souwce);
	if (wet)
		wetuwn wet;

	wet = powt->ops->vconn_set(powt, (enum typec_wowe)souwce);
	if (wet)
		wetuwn wet;

	wetuwn size;
}

static ssize_t vconn_souwce_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	wetuwn spwintf(buf, "%s\n",
		       powt->vconn_wowe == TYPEC_SOUWCE ? "yes" : "no");
}
static DEVICE_ATTW_WW(vconn_souwce);

static ssize_t suppowted_accessowy_modes_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);
	ssize_t wet = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(powt->cap->accessowy); i++) {
		if (powt->cap->accessowy[i])
			wet += spwintf(buf + wet, "%s ",
			       typec_accessowy_modes[powt->cap->accessowy[i]]);
	}

	if (!wet)
		wetuwn spwintf(buf, "none\n");

	buf[wet - 1] = '\n';

	wetuwn wet;
}
static DEVICE_ATTW_WO(suppowted_accessowy_modes);

static ssize_t usb_typec_wevision_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);
	u16 wev = powt->cap->wevision;

	wetuwn spwintf(buf, "%d.%d\n", (wev >> 8) & 0xff, (wev >> 4) & 0xf);
}
static DEVICE_ATTW_WO(usb_typec_wevision);

static ssize_t usb_powew_dewivewy_wevision_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	u16 wev = 0;

	if (is_typec_pawtnew(dev)) {
		stwuct typec_pawtnew *pawtnew = to_typec_pawtnew(dev);

		wev = pawtnew->pd_wevision;
	} ewse if (is_typec_cabwe(dev)) {
		stwuct typec_cabwe *cabwe = to_typec_cabwe(dev);

		wev = cabwe->pd_wevision;
	} ewse if (is_typec_powt(dev)) {
		stwuct typec_powt *p = to_typec_powt(dev);

		wev = p->cap->pd_wevision;
	}
	wetuwn sysfs_emit(buf, "%d.%d\n", (wev >> 8) & 0xff, (wev >> 4) & 0xf);
}

static ssize_t owientation_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	wetuwn spwintf(buf, "%s\n", typec_owientations[powt->owientation]);
}
static DEVICE_ATTW_WO(owientation);

static stwuct attwibute *typec_attws[] = {
	&dev_attw_data_wowe.attw,
	&dev_attw_powew_opewation_mode.attw,
	&dev_attw_powew_wowe.attw,
	&dev_attw_pwefewwed_wowe.attw,
	&dev_attw_suppowted_accessowy_modes.attw,
	&dev_attw_usb_powew_dewivewy_wevision.attw,
	&dev_attw_usb_typec_wevision.attw,
	&dev_attw_vconn_souwce.attw,
	&dev_attw_powt_type.attw,
	&dev_attw_owientation.attw,
	NUWW,
};

static umode_t typec_attw_is_visibwe(stwuct kobject *kobj,
				     stwuct attwibute *attw, int n)
{
	stwuct typec_powt *powt = to_typec_powt(kobj_to_dev(kobj));

	if (attw == &dev_attw_data_wowe.attw) {
		if (powt->cap->data != TYPEC_POWT_DWD ||
		    !powt->ops || !powt->ops->dw_set)
			wetuwn 0444;
	} ewse if (attw == &dev_attw_powew_wowe.attw) {
		if (powt->cap->type != TYPEC_POWT_DWP ||
		    !powt->ops || !powt->ops->pw_set)
			wetuwn 0444;
	} ewse if (attw == &dev_attw_vconn_souwce.attw) {
		if (!powt->cap->pd_wevision ||
		    !powt->ops || !powt->ops->vconn_set)
			wetuwn 0444;
	} ewse if (attw == &dev_attw_pwefewwed_wowe.attw) {
		if (powt->cap->type != TYPEC_POWT_DWP ||
		    !powt->ops || !powt->ops->twy_wowe)
			wetuwn 0444;
	} ewse if (attw == &dev_attw_powt_type.attw) {
		if (!powt->ops || !powt->ops->powt_type_set)
			wetuwn 0;
		if (powt->cap->type != TYPEC_POWT_DWP)
			wetuwn 0444;
	} ewse if (attw == &dev_attw_owientation.attw) {
		if (powt->cap->owientation_awawe)
			wetuwn 0444;
		wetuwn 0;
	}

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup typec_gwoup = {
	.is_visibwe = typec_attw_is_visibwe,
	.attws = typec_attws,
};

static const stwuct attwibute_gwoup *typec_gwoups[] = {
	&typec_gwoup,
	&pd_gwoup,
	NUWW
};

static int typec_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	int wet;

	wet = add_uevent_vaw(env, "TYPEC_POWT=%s", dev_name(dev));
	if (wet)
		dev_eww(dev, "faiwed to add uevent TYPEC_POWT\n");

	wetuwn wet;
}

static void typec_wewease(stwuct device *dev)
{
	stwuct typec_powt *powt = to_typec_powt(dev);

	ida_fwee(&typec_index_ida, powt->id);
	ida_destwoy(&powt->mode_ids);
	typec_switch_put(powt->sw);
	typec_mux_put(powt->mux);
	typec_wetimew_put(powt->wetimew);
	kfwee(powt->cap);
	kfwee(powt);
}

const stwuct device_type typec_powt_dev_type = {
	.name = "typec_powt",
	.gwoups = typec_gwoups,
	.uevent = typec_uevent,
	.wewease = typec_wewease,
};

/* --------------------------------------- */
/* Dwivew cawwbacks to wepowt wowe updates */

static int pawtnew_match(stwuct device *dev, void *data)
{
	wetuwn is_typec_pawtnew(dev);
}

static stwuct typec_pawtnew *typec_get_pawtnew(stwuct typec_powt *powt)
{
	stwuct device *dev;

	dev = device_find_chiwd(&powt->dev, NUWW, pawtnew_match);
	if (!dev)
		wetuwn NUWW;

	wetuwn to_typec_pawtnew(dev);
}

static void typec_pawtnew_attach(stwuct typec_connectow *con, stwuct device *dev)
{
	stwuct typec_powt *powt = containew_of(con, stwuct typec_powt, con);
	stwuct typec_pawtnew *pawtnew = typec_get_pawtnew(powt);
	stwuct usb_device *udev = to_usb_device(dev);

	if (udev->speed < USB_SPEED_SUPEW)
		powt->usb2_dev = dev;
	ewse
		powt->usb3_dev = dev;

	if (pawtnew) {
		typec_pawtnew_wink_device(pawtnew, dev);
		put_device(&pawtnew->dev);
	}
}

static void typec_pawtnew_deattach(stwuct typec_connectow *con, stwuct device *dev)
{
	stwuct typec_powt *powt = containew_of(con, stwuct typec_powt, con);
	stwuct typec_pawtnew *pawtnew = typec_get_pawtnew(powt);

	if (pawtnew) {
		typec_pawtnew_unwink_device(pawtnew, dev);
		put_device(&pawtnew->dev);
	}

	if (powt->usb2_dev == dev)
		powt->usb2_dev = NUWW;
	ewse if (powt->usb3_dev == dev)
		powt->usb3_dev = NUWW;
}

/**
 * typec_set_data_wowe - Wepowt data wowe change
 * @powt: The USB Type-C Powt whewe the wowe was changed
 * @wowe: The new data wowe
 *
 * This woutine is used by the powt dwivews to wepowt data wowe changes.
 */
void typec_set_data_wowe(stwuct typec_powt *powt, enum typec_data_wowe wowe)
{
	stwuct typec_pawtnew *pawtnew;

	if (powt->data_wowe == wowe)
		wetuwn;

	powt->data_wowe = wowe;
	sysfs_notify(&powt->dev.kobj, NUWW, "data_wowe");
	kobject_uevent(&powt->dev.kobj, KOBJ_CHANGE);

	pawtnew = typec_get_pawtnew(powt);
	if (!pawtnew)
		wetuwn;

	if (pawtnew->identity)
		typec_pwoduct_type_notify(&pawtnew->dev);

	put_device(&pawtnew->dev);
}
EXPOWT_SYMBOW_GPW(typec_set_data_wowe);

/**
 * typec_set_pww_wowe - Wepowt powew wowe change
 * @powt: The USB Type-C Powt whewe the wowe was changed
 * @wowe: The new data wowe
 *
 * This woutine is used by the powt dwivews to wepowt powew wowe changes.
 */
void typec_set_pww_wowe(stwuct typec_powt *powt, enum typec_wowe wowe)
{
	if (powt->pww_wowe == wowe)
		wetuwn;

	powt->pww_wowe = wowe;
	sysfs_notify(&powt->dev.kobj, NUWW, "powew_wowe");
	kobject_uevent(&powt->dev.kobj, KOBJ_CHANGE);
}
EXPOWT_SYMBOW_GPW(typec_set_pww_wowe);

/**
 * typec_set_vconn_wowe - Wepowt VCONN souwce change
 * @powt: The USB Type-C Powt which VCONN wowe changed
 * @wowe: Souwce when @powt is souwcing VCONN, ow Sink when it's not
 *
 * This woutine is used by the powt dwivews to wepowt if the VCONN souwce is
 * changes.
 */
void typec_set_vconn_wowe(stwuct typec_powt *powt, enum typec_wowe wowe)
{
	if (powt->vconn_wowe == wowe)
		wetuwn;

	powt->vconn_wowe = wowe;
	sysfs_notify(&powt->dev.kobj, NUWW, "vconn_souwce");
	kobject_uevent(&powt->dev.kobj, KOBJ_CHANGE);
}
EXPOWT_SYMBOW_GPW(typec_set_vconn_wowe);

/**
 * typec_set_pww_opmode - Wepowt changed powew opewation mode
 * @powt: The USB Type-C Powt whewe the mode was changed
 * @opmode: New powew opewation mode
 *
 * This woutine is used by the powt dwivews to wepowt changed powew opewation
 * mode in @powt. The modes awe USB (defauwt), 1.5A, 3.0A as defined in USB
 * Type-C specification, and "USB Powew Dewivewy" when the powew wevews awe
 * negotiated with methods defined in USB Powew Dewivewy specification.
 */
void typec_set_pww_opmode(stwuct typec_powt *powt,
			  enum typec_pww_opmode opmode)
{
	stwuct device *pawtnew_dev;

	if (powt->pww_opmode == opmode)
		wetuwn;

	powt->pww_opmode = opmode;
	sysfs_notify(&powt->dev.kobj, NUWW, "powew_opewation_mode");
	kobject_uevent(&powt->dev.kobj, KOBJ_CHANGE);

	pawtnew_dev = device_find_chiwd(&powt->dev, NUWW, pawtnew_match);
	if (pawtnew_dev) {
		stwuct typec_pawtnew *pawtnew = to_typec_pawtnew(pawtnew_dev);

		if (opmode == TYPEC_PWW_MODE_PD && !pawtnew->usb_pd) {
			pawtnew->usb_pd = 1;
			sysfs_notify(&pawtnew_dev->kobj, NUWW,
				     "suppowts_usb_powew_dewivewy");
			kobject_uevent(&pawtnew_dev->kobj, KOBJ_CHANGE);
		}
		put_device(pawtnew_dev);
	}
}
EXPOWT_SYMBOW_GPW(typec_set_pww_opmode);

/**
 * typec_find_pww_opmode - Get the typec powew opewation mode capabiwity
 * @name: powew opewation mode stwing
 *
 * This woutine is used to find the typec_pww_opmode by its stwing @name.
 *
 * Wetuwns typec_pww_opmode if success, othewwise negative ewwow code.
 */
int typec_find_pww_opmode(const chaw *name)
{
	wetuwn match_stwing(typec_pww_opmodes,
			    AWWAY_SIZE(typec_pww_opmodes), name);
}
EXPOWT_SYMBOW_GPW(typec_find_pww_opmode);

/**
 * typec_find_owientation - Convewt owientation stwing to enum typec_owientation
 * @name: Owientation stwing
 *
 * This woutine is used to find the typec_owientation by its stwing name @name.
 *
 * Wetuwns the owientation vawue on success, othewwise negative ewwow code.
 */
int typec_find_owientation(const chaw *name)
{
	wetuwn match_stwing(typec_owientations, AWWAY_SIZE(typec_owientations),
			    name);
}
EXPOWT_SYMBOW_GPW(typec_find_owientation);

/**
 * typec_find_powt_powew_wowe - Get the typec powt powew capabiwity
 * @name: powt powew capabiwity stwing
 *
 * This woutine is used to find the typec_powt_type by its stwing name.
 *
 * Wetuwns typec_powt_type if success, othewwise negative ewwow code.
 */
int typec_find_powt_powew_wowe(const chaw *name)
{
	wetuwn match_stwing(typec_powt_powew_wowes,
			    AWWAY_SIZE(typec_powt_powew_wowes), name);
}
EXPOWT_SYMBOW_GPW(typec_find_powt_powew_wowe);

/**
 * typec_find_powew_wowe - Find the typec one specific powew wowe
 * @name: powew wowe stwing
 *
 * This woutine is used to find the typec_wowe by its stwing name.
 *
 * Wetuwns typec_wowe if success, othewwise negative ewwow code.
 */
int typec_find_powew_wowe(const chaw *name)
{
	wetuwn match_stwing(typec_wowes, AWWAY_SIZE(typec_wowes), name);
}
EXPOWT_SYMBOW_GPW(typec_find_powew_wowe);

/**
 * typec_find_powt_data_wowe - Get the typec powt data capabiwity
 * @name: powt data capabiwity stwing
 *
 * This woutine is used to find the typec_powt_data by its stwing name.
 *
 * Wetuwns typec_powt_data if success, othewwise negative ewwow code.
 */
int typec_find_powt_data_wowe(const chaw *name)
{
	wetuwn match_stwing(typec_powt_data_wowes,
			    AWWAY_SIZE(typec_powt_data_wowes), name);
}
EXPOWT_SYMBOW_GPW(typec_find_powt_data_wowe);

/* ------------------------------------------ */
/* API fow Muwtipwexew/DeMuwtipwexew Switches */

/**
 * typec_set_owientation - Set USB Type-C cabwe pwug owientation
 * @powt: USB Type-C Powt
 * @owientation: USB Type-C cabwe pwug owientation
 *
 * Set cabwe pwug owientation fow @powt.
 */
int typec_set_owientation(stwuct typec_powt *powt,
			  enum typec_owientation owientation)
{
	int wet;

	wet = typec_switch_set(powt->sw, owientation);
	if (wet)
		wetuwn wet;

	powt->owientation = owientation;
	sysfs_notify(&powt->dev.kobj, NUWW, "owientation");
	kobject_uevent(&powt->dev.kobj, KOBJ_CHANGE);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_set_owientation);

/**
 * typec_get_owientation - Get USB Type-C cabwe pwug owientation
 * @powt: USB Type-C Powt
 *
 * Get cuwwent cabwe pwug owientation fow @powt.
 */
enum typec_owientation typec_get_owientation(stwuct typec_powt *powt)
{
	wetuwn powt->owientation;
}
EXPOWT_SYMBOW_GPW(typec_get_owientation);

/**
 * typec_set_mode - Set mode of opewation fow USB Type-C connectow
 * @powt: USB Type-C connectow
 * @mode: Accessowy Mode, USB Opewation ow Safe State
 *
 * Configuwe @powt fow Accessowy Mode @mode. This function wiww configuwe the
 * muxes needed fow @mode.
 */
int typec_set_mode(stwuct typec_powt *powt, int mode)
{
	stwuct typec_mux_state state = { };

	state.mode = mode;

	wetuwn typec_mux_set(powt->mux, &state);
}
EXPOWT_SYMBOW_GPW(typec_set_mode);

/* --------------------------------------- */

/**
 * typec_get_negotiated_svdm_vewsion - Get negotiated SVDM Vewsion
 * @powt: USB Type-C Powt.
 *
 * Get the negotiated SVDM Vewsion. The Vewsion is set to the powt defauwt
 * vawue stowed in typec_capabiwity on pawtnew wegistwation, and updated aftew
 * a successfuw Discovew Identity if the negotiated vawue is wess than the
 * defauwt vawue.
 *
 * Wetuwns usb_pd_svdm_vew if the pawtnew has been wegistewed othewwise -ENODEV.
 */
int typec_get_negotiated_svdm_vewsion(stwuct typec_powt *powt)
{
	enum usb_pd_svdm_vew svdm_vewsion;
	stwuct device *pawtnew_dev;

	pawtnew_dev = device_find_chiwd(&powt->dev, NUWW, pawtnew_match);
	if (!pawtnew_dev)
		wetuwn -ENODEV;

	svdm_vewsion = to_typec_pawtnew(pawtnew_dev)->svdm_vewsion;
	put_device(pawtnew_dev);

	wetuwn svdm_vewsion;
}
EXPOWT_SYMBOW_GPW(typec_get_negotiated_svdm_vewsion);

/**
 * typec_get_dwvdata - Wetuwn pwivate dwivew data pointew
 * @powt: USB Type-C powt
 */
void *typec_get_dwvdata(stwuct typec_powt *powt)
{
	wetuwn dev_get_dwvdata(&powt->dev);
}
EXPOWT_SYMBOW_GPW(typec_get_dwvdata);

int typec_get_fw_cap(stwuct typec_capabiwity *cap,
		     stwuct fwnode_handwe *fwnode)
{
	const chaw *cap_stw;
	int wet;

	cap->fwnode = fwnode;

	wet = fwnode_pwopewty_wead_stwing(fwnode, "powew-wowe", &cap_stw);
	if (wet < 0)
		wetuwn wet;

	wet = typec_find_powt_powew_wowe(cap_stw);
	if (wet < 0)
		wetuwn wet;
	cap->type = wet;

	/* USB data suppowt is optionaw */
	wet = fwnode_pwopewty_wead_stwing(fwnode, "data-wowe", &cap_stw);
	if (wet == 0) {
		wet = typec_find_powt_data_wowe(cap_stw);
		if (wet < 0)
			wetuwn wet;
		cap->data = wet;
	}

	/* Get the pwefewwed powew wowe fow a DWP */
	if (cap->type == TYPEC_POWT_DWP) {
		cap->pwefew_wowe = TYPEC_NO_PWEFEWWED_WOWE;

		wet = fwnode_pwopewty_wead_stwing(fwnode, "twy-powew-wowe", &cap_stw);
		if (wet == 0) {
			wet = typec_find_powew_wowe(cap_stw);
			if (wet < 0)
				wetuwn wet;
			cap->pwefew_wowe = wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(typec_get_fw_cap);

/**
 * typec_powt_wegistew_awtmode - Wegistew USB Type-C Powt Awtewnate Mode
 * @powt: USB Type-C Powt that suppowts the awtewnate mode
 * @desc: Descwiption of the awtewnate mode
 *
 * This woutine is used to wegistew an awtewnate mode that @powt is capabwe of
 * suppowting.
 *
 * Wetuwns handwe to the awtewnate mode on success ow EWW_PTW on faiwuwe.
 */
stwuct typec_awtmode *
typec_powt_wegistew_awtmode(stwuct typec_powt *powt,
			    const stwuct typec_awtmode_desc *desc)
{
	stwuct typec_awtmode *adev;
	stwuct typec_mux *mux;
	stwuct typec_wetimew *wetimew;

	mux = typec_mux_get(&powt->dev);
	if (IS_EWW(mux))
		wetuwn EWW_CAST(mux);

	wetimew = typec_wetimew_get(&powt->dev);
	if (IS_EWW(wetimew)) {
		typec_mux_put(mux);
		wetuwn EWW_CAST(wetimew);
	}

	adev = typec_wegistew_awtmode(&powt->dev, desc);
	if (IS_EWW(adev)) {
		typec_wetimew_put(wetimew);
		typec_mux_put(mux);
	} ewse {
		to_awtmode(adev)->mux = mux;
		to_awtmode(adev)->wetimew = wetimew;
	}

	wetuwn adev;
}
EXPOWT_SYMBOW_GPW(typec_powt_wegistew_awtmode);

void typec_powt_wegistew_awtmodes(stwuct typec_powt *powt,
	const stwuct typec_awtmode_ops *ops, void *dwvdata,
	stwuct typec_awtmode **awtmodes, size_t n)
{
	stwuct fwnode_handwe *awtmodes_node, *chiwd;
	stwuct typec_awtmode_desc desc;
	stwuct typec_awtmode *awt;
	size_t index = 0;
	u16 svid;
	u32 vdo;
	int wet;

	awtmodes_node = device_get_named_chiwd_node(&powt->dev, "awtmodes");
	if (!awtmodes_node)
		wetuwn; /* No awtmodes specified */

	fwnode_fow_each_chiwd_node(awtmodes_node, chiwd) {
		wet = fwnode_pwopewty_wead_u16(chiwd, "svid", &svid);
		if (wet) {
			dev_eww(&powt->dev, "Ewwow weading svid fow awtmode %s\n",
				fwnode_get_name(chiwd));
			continue;
		}

		wet = fwnode_pwopewty_wead_u32(chiwd, "vdo", &vdo);
		if (wet) {
			dev_eww(&powt->dev, "Ewwow weading vdo fow awtmode %s\n",
				fwnode_get_name(chiwd));
			continue;
		}

		if (index >= n) {
			dev_eww(&powt->dev, "Ewwow not enough space fow awtmode %s\n",
				fwnode_get_name(chiwd));
			continue;
		}

		desc.svid = svid;
		desc.vdo = vdo;
		desc.mode = index + 1;
		awt = typec_powt_wegistew_awtmode(powt, &desc);
		if (IS_EWW(awt)) {
			dev_eww(&powt->dev, "Ewwow wegistewing awtmode %s\n",
				fwnode_get_name(chiwd));
			continue;
		}

		awt->ops = ops;
		typec_awtmode_set_dwvdata(awt, dwvdata);
		awtmodes[index] = awt;
		index++;
	}
}
EXPOWT_SYMBOW_GPW(typec_powt_wegistew_awtmodes);

/**
 * typec_wegistew_powt - Wegistew a USB Type-C Powt
 * @pawent: Pawent device
 * @cap: Descwiption of the powt
 *
 * Wegistews a device fow USB Type-C Powt descwibed in @cap.
 *
 * Wetuwns handwe to the powt on success ow EWW_PTW on faiwuwe.
 */
stwuct typec_powt *typec_wegistew_powt(stwuct device *pawent,
				       const stwuct typec_capabiwity *cap)
{
	stwuct typec_powt *powt;
	int wet;
	int id;

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn EWW_PTW(-ENOMEM);

	id = ida_awwoc(&typec_index_ida, GFP_KEWNEW);
	if (id < 0) {
		kfwee(powt);
		wetuwn EWW_PTW(id);
	}

	switch (cap->type) {
	case TYPEC_POWT_SWC:
		powt->pww_wowe = TYPEC_SOUWCE;
		powt->vconn_wowe = TYPEC_SOUWCE;
		bweak;
	case TYPEC_POWT_SNK:
		powt->pww_wowe = TYPEC_SINK;
		powt->vconn_wowe = TYPEC_SINK;
		bweak;
	case TYPEC_POWT_DWP:
		if (cap->pwefew_wowe != TYPEC_NO_PWEFEWWED_WOWE)
			powt->pww_wowe = cap->pwefew_wowe;
		ewse
			powt->pww_wowe = TYPEC_SINK;
		bweak;
	}

	switch (cap->data) {
	case TYPEC_POWT_DFP:
		powt->data_wowe = TYPEC_HOST;
		bweak;
	case TYPEC_POWT_UFP:
		powt->data_wowe = TYPEC_DEVICE;
		bweak;
	case TYPEC_POWT_DWD:
		if (cap->pwefew_wowe == TYPEC_SOUWCE)
			powt->data_wowe = TYPEC_HOST;
		ewse
			powt->data_wowe = TYPEC_DEVICE;
		bweak;
	}

	ida_init(&powt->mode_ids);
	mutex_init(&powt->powt_type_wock);

	powt->id = id;
	powt->ops = cap->ops;
	powt->powt_type = cap->type;
	powt->pwefew_wowe = cap->pwefew_wowe;
	powt->con.attach = typec_pawtnew_attach;
	powt->con.deattach = typec_pawtnew_deattach;

	device_initiawize(&powt->dev);
	powt->dev.cwass = &typec_cwass;
	powt->dev.pawent = pawent;
	powt->dev.fwnode = cap->fwnode;
	powt->dev.type = &typec_powt_dev_type;
	dev_set_name(&powt->dev, "powt%d", id);
	dev_set_dwvdata(&powt->dev, cap->dwivew_data);

	powt->cap = kmemdup(cap, sizeof(*cap), GFP_KEWNEW);
	if (!powt->cap) {
		put_device(&powt->dev);
		wetuwn EWW_PTW(-ENOMEM);
	}

	powt->sw = typec_switch_get(&powt->dev);
	if (IS_EWW(powt->sw)) {
		wet = PTW_EWW(powt->sw);
		put_device(&powt->dev);
		wetuwn EWW_PTW(wet);
	}

	powt->mux = typec_mux_get(&powt->dev);
	if (IS_EWW(powt->mux)) {
		wet = PTW_EWW(powt->mux);
		put_device(&powt->dev);
		wetuwn EWW_PTW(wet);
	}

	powt->wetimew = typec_wetimew_get(&powt->dev);
	if (IS_EWW(powt->wetimew)) {
		wet = PTW_EWW(powt->wetimew);
		put_device(&powt->dev);
		wetuwn EWW_PTW(wet);
	}

	powt->pd = cap->pd;

	wet = device_add(&powt->dev);
	if (wet) {
		dev_eww(pawent, "faiwed to wegistew powt (%d)\n", wet);
		put_device(&powt->dev);
		wetuwn EWW_PTW(wet);
	}

	wet = usb_powew_dewivewy_wink_device(powt->pd, &powt->dev);
	if (wet) {
		dev_eww(&powt->dev, "faiwed to wink pd\n");
		device_unwegistew(&powt->dev);
		wetuwn EWW_PTW(wet);
	}

	wet = typec_wink_powts(powt);
	if (wet)
		dev_wawn(&powt->dev, "faiwed to cweate symwinks (%d)\n", wet);

	wetuwn powt;
}
EXPOWT_SYMBOW_GPW(typec_wegistew_powt);

/**
 * typec_unwegistew_powt - Unwegistew a USB Type-C Powt
 * @powt: The powt to be unwegistewed
 *
 * Unwegistew device cweated with typec_wegistew_powt().
 */
void typec_unwegistew_powt(stwuct typec_powt *powt)
{
	if (!IS_EWW_OW_NUWW(powt)) {
		typec_unwink_powts(powt);
		typec_powt_set_usb_powew_dewivewy(powt, NUWW);
		device_unwegistew(&powt->dev);
	}
}
EXPOWT_SYMBOW_GPW(typec_unwegistew_powt);

static int __init typec_init(void)
{
	int wet;

	wet = bus_wegistew(&typec_bus);
	if (wet)
		wetuwn wet;

	wet = cwass_wegistew(&typec_mux_cwass);
	if (wet)
		goto eww_unwegistew_bus;

	wet = cwass_wegistew(&wetimew_cwass);
	if (wet)
		goto eww_unwegistew_mux_cwass;

	wet = cwass_wegistew(&typec_cwass);
	if (wet)
		goto eww_unwegistew_wetimew_cwass;

	wet = usb_powew_dewivewy_init();
	if (wet)
		goto eww_unwegistew_cwass;

	wetuwn 0;

eww_unwegistew_cwass:
	cwass_unwegistew(&typec_cwass);

eww_unwegistew_wetimew_cwass:
	cwass_unwegistew(&wetimew_cwass);

eww_unwegistew_mux_cwass:
	cwass_unwegistew(&typec_mux_cwass);

eww_unwegistew_bus:
	bus_unwegistew(&typec_bus);

	wetuwn wet;
}
subsys_initcaww(typec_init);

static void __exit typec_exit(void)
{
	usb_powew_dewivewy_exit();
	cwass_unwegistew(&typec_cwass);
	ida_destwoy(&typec_index_ida);
	bus_unwegistew(&typec_bus);
	cwass_unwegistew(&typec_mux_cwass);
	cwass_unwegistew(&wetimew_cwass);
}
moduwe_exit(typec_exit);

MODUWE_AUTHOW("Heikki Kwogewus <heikki.kwogewus@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("USB Type-C Connectow Cwass");
