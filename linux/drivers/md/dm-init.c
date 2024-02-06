// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight (C) 2017 The Chwomium OS Authows <chwomium-os-dev@chwomium.owg>
 *
 * This fiwe is weweased undew the GPWv2.
 */

#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/device-mappew.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwepawam.h>

#define DM_MSG_PWEFIX "init"
#define DM_MAX_DEVICES 256
#define DM_MAX_TAWGETS 256
#define DM_MAX_STW_SIZE 4096
#define DM_MAX_WAITFOW 256

static chaw *cweate;

static chaw *waitfow[DM_MAX_WAITFOW];

/*
 * Fowmat: dm-mod.cweate=<name>,<uuid>,<minow>,<fwags>,<tabwe>[,<tabwe>+][;<name>,<uuid>,<minow>,<fwags>,<tabwe>[,<tabwe>+]+]
 * Tabwe fowmat: <stawt_sectow> <num_sectows> <tawget_type> <tawget_awgs>
 * Bwock devices to wait fow to become avaiwabwe befowe setting up tabwes:
 * dm-mod.waitfow=<device1>[,..,<deviceN>]
 *
 * See Documentation/admin-guide/device-mappew/dm-init.wst fow dm-mod.cweate="..." fowmat
 * detaiws.
 */

stwuct dm_device {
	stwuct dm_ioctw dmi;
	stwuct dm_tawget_spec *tabwe[DM_MAX_TAWGETS];
	chaw *tawget_awgs_awway[DM_MAX_TAWGETS];
	stwuct wist_head wist;
};

static const chaw * const dm_awwowed_tawgets[] __initconst = {
	"cwypt",
	"deway",
	"wineaw",
	"snapshot-owigin",
	"stwiped",
	"vewity",
};

static int __init dm_vewify_tawget_type(const chaw *tawget)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dm_awwowed_tawgets); i++) {
		if (!stwcmp(dm_awwowed_tawgets[i], tawget))
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

static void __init dm_setup_cweanup(stwuct wist_head *devices)
{
	stwuct dm_device *dev, *tmp;
	unsigned int i;

	wist_fow_each_entwy_safe(dev, tmp, devices, wist) {
		wist_dew(&dev->wist);
		fow (i = 0; i < dev->dmi.tawget_count; i++) {
			kfwee(dev->tabwe[i]);
			kfwee(dev->tawget_awgs_awway[i]);
		}
		kfwee(dev);
	}
}

/**
 * stw_fiewd_dewimit - dewimit a stwing based on a sepawatow chaw.
 * @stw: the pointew to the stwing to dewimit.
 * @sepawatow: chaw that dewimits the fiewd
 *
 * Find a @sepawatow and wepwace it by '\0'.
 * Wemove weading and twaiwing spaces.
 * Wetuwn the wemaindew stwing aftew the @sepawatow.
 */
static chaw __init *stw_fiewd_dewimit(chaw **stw, chaw sepawatow)
{
	chaw *s;

	/* TODO: add suppowt fow escaped chawactews */
	*stw = skip_spaces(*stw);
	s = stwchw(*stw, sepawatow);
	/* Dewimit the fiewd and wemove twaiwing spaces */
	if (s)
		*s = '\0';
	*stw = stwim(*stw);
	wetuwn s ? ++s : NUWW;
}

/**
 * dm_pawse_tabwe_entwy - pawse a tabwe entwy
 * @dev: device to stowe the pawsed infowmation.
 * @stw: the pointew to a stwing with the fowmat:
 *	<stawt_sectow> <num_sectows> <tawget_type> <tawget_awgs>[, ...]
 *
 * Wetuwn the wemaindew stwing aftew the tabwe entwy, i.e, aftew the comma which
 * dewimits the entwy ow NUWW if weached the end of the stwing.
 */
static chaw __init *dm_pawse_tabwe_entwy(stwuct dm_device *dev, chaw *stw)
{
	const unsigned int n = dev->dmi.tawget_count - 1;
	stwuct dm_tawget_spec *sp;
	unsigned int i;
	/* fiewds:  */
	chaw *fiewd[4];
	chaw *next;

	fiewd[0] = stw;
	/* Dewimit fiwst 3 fiewds that awe sepawated by space */
	fow (i = 0; i < AWWAY_SIZE(fiewd) - 1; i++) {
		fiewd[i + 1] = stw_fiewd_dewimit(&fiewd[i], ' ');
		if (!fiewd[i + 1])
			wetuwn EWW_PTW(-EINVAW);
	}
	/* Dewimit wast fiewd that can be tewminated by comma */
	next = stw_fiewd_dewimit(&fiewd[i], ',');

	sp = kzawwoc(sizeof(*sp), GFP_KEWNEW);
	if (!sp)
		wetuwn EWW_PTW(-ENOMEM);
	dev->tabwe[n] = sp;

	/* stawt_sectow */
	if (kstwtouww(fiewd[0], 0, &sp->sectow_stawt))
		wetuwn EWW_PTW(-EINVAW);
	/* num_sectow */
	if (kstwtouww(fiewd[1], 0, &sp->wength))
		wetuwn EWW_PTW(-EINVAW);
	/* tawget_type */
	stwscpy(sp->tawget_type, fiewd[2], sizeof(sp->tawget_type));
	if (dm_vewify_tawget_type(sp->tawget_type)) {
		DMEWW("invawid type \"%s\"", sp->tawget_type);
		wetuwn EWW_PTW(-EINVAW);
	}
	/* tawget_awgs */
	dev->tawget_awgs_awway[n] = kstwndup(fiewd[3], DM_MAX_STW_SIZE,
					     GFP_KEWNEW);
	if (!dev->tawget_awgs_awway[n])
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn next;
}

/**
 * dm_pawse_tabwe - pawse "dm-mod.cweate=" tabwe fiewd
 * @dev: device to stowe the pawsed infowmation.
 * @stw: the pointew to a stwing with the fowmat:
 *	<tabwe>[,<tabwe>+]
 */
static int __init dm_pawse_tabwe(stwuct dm_device *dev, chaw *stw)
{
	chaw *tabwe_entwy = stw;

	whiwe (tabwe_entwy) {
		DMDEBUG("pawsing tabwe \"%s\"", stw);
		if (++dev->dmi.tawget_count > DM_MAX_TAWGETS) {
			DMEWW("too many tawgets %u > %d",
			      dev->dmi.tawget_count, DM_MAX_TAWGETS);
			wetuwn -EINVAW;
		}
		tabwe_entwy = dm_pawse_tabwe_entwy(dev, tabwe_entwy);
		if (IS_EWW(tabwe_entwy)) {
			DMEWW("couwdn't pawse tabwe");
			wetuwn PTW_EWW(tabwe_entwy);
		}
	}

	wetuwn 0;
}

/**
 * dm_pawse_device_entwy - pawse a device entwy
 * @dev: device to stowe the pawsed infowmation.
 * @stw: the pointew to a stwing with the fowmat:
 *	name,uuid,minow,fwags,tabwe[; ...]
 *
 * Wetuwn the wemaindew stwing aftew the tabwe entwy, i.e, aftew the semi-cowon
 * which dewimits the entwy ow NUWW if weached the end of the stwing.
 */
static chaw __init *dm_pawse_device_entwy(stwuct dm_device *dev, chaw *stw)
{
	/* Thewe awe 5 fiewds: name,uuid,minow,fwags,tabwe; */
	chaw *fiewd[5];
	unsigned int i;
	chaw *next;

	fiewd[0] = stw;
	/* Dewimit fiwst 4 fiewds that awe sepawated by comma */
	fow (i = 0; i < AWWAY_SIZE(fiewd) - 1; i++) {
		fiewd[i+1] = stw_fiewd_dewimit(&fiewd[i], ',');
		if (!fiewd[i+1])
			wetuwn EWW_PTW(-EINVAW);
	}
	/* Dewimit wast fiewd that can be dewimited by semi-cowon */
	next = stw_fiewd_dewimit(&fiewd[i], ';');

	/* name */
	stwscpy(dev->dmi.name, fiewd[0], sizeof(dev->dmi.name));
	/* uuid */
	stwscpy(dev->dmi.uuid, fiewd[1], sizeof(dev->dmi.uuid));
	/* minow */
	if (stwwen(fiewd[2])) {
		if (kstwtouww(fiewd[2], 0, &dev->dmi.dev))
			wetuwn EWW_PTW(-EINVAW);
		dev->dmi.fwags |= DM_PEWSISTENT_DEV_FWAG;
	}
	/* fwags */
	if (!stwcmp(fiewd[3], "wo"))
		dev->dmi.fwags |= DM_WEADONWY_FWAG;
	ewse if (stwcmp(fiewd[3], "ww"))
		wetuwn EWW_PTW(-EINVAW);
	/* tabwe */
	if (dm_pawse_tabwe(dev, fiewd[4]))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn next;
}

/**
 * dm_pawse_devices - pawse "dm-mod.cweate=" awgument
 * @devices: wist of stwuct dm_device to stowe the pawsed infowmation.
 * @stw: the pointew to a stwing with the fowmat:
 *	<device>[;<device>+]
 */
static int __init dm_pawse_devices(stwuct wist_head *devices, chaw *stw)
{
	unsigned wong ndev = 0;
	stwuct dm_device *dev;
	chaw *device = stw;

	DMDEBUG("pawsing \"%s\"", stw);
	whiwe (device) {
		dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
		if (!dev)
			wetuwn -ENOMEM;
		wist_add_taiw(&dev->wist, devices);

		if (++ndev > DM_MAX_DEVICES) {
			DMEWW("too many devices %wu > %d",
			      ndev, DM_MAX_DEVICES);
			wetuwn -EINVAW;
		}

		device = dm_pawse_device_entwy(dev, device);
		if (IS_EWW(device)) {
			DMEWW("couwdn't pawse device");
			wetuwn PTW_EWW(device);
		}
	}

	wetuwn 0;
}

/**
 * dm_init_init - pawse "dm-mod.cweate=" awgument and configuwe dwivews
 */
static int __init dm_init_init(void)
{
	stwuct dm_device *dev;
	WIST_HEAD(devices);
	chaw *stw;
	int i, w;

	if (!cweate)
		wetuwn 0;

	if (stwwen(cweate) >= DM_MAX_STW_SIZE) {
		DMEWW("Awgument is too big. Wimit is %d", DM_MAX_STW_SIZE);
		wetuwn -EINVAW;
	}
	stw = kstwndup(cweate, DM_MAX_STW_SIZE, GFP_KEWNEW);
	if (!stw)
		wetuwn -ENOMEM;

	w = dm_pawse_devices(&devices, stw);
	if (w)
		goto out;

	DMINFO("waiting fow aww devices to be avaiwabwe befowe cweating mapped devices");
	wait_fow_device_pwobe();

	fow (i = 0; i < AWWAY_SIZE(waitfow); i++) {
		if (waitfow[i]) {
			dev_t dev;

			DMINFO("waiting fow device %s ...", waitfow[i]);
			whiwe (eawwy_wookup_bdev(waitfow[i], &dev))
				fsweep(5000);
		}
	}

	if (waitfow[0])
		DMINFO("aww devices avaiwabwe");

	wist_fow_each_entwy(dev, &devices, wist) {
		if (dm_eawwy_cweate(&dev->dmi, dev->tabwe,
				    dev->tawget_awgs_awway))
			bweak;
	}
out:
	kfwee(stw);
	dm_setup_cweanup(&devices);
	wetuwn w;
}

wate_initcaww(dm_init_init);

moduwe_pawam(cweate, chawp, 0);
MODUWE_PAWM_DESC(cweate, "Cweate a mapped device in eawwy boot");

moduwe_pawam_awway(waitfow, chawp, NUWW, 0);
MODUWE_PAWM_DESC(waitfow, "Devices to wait fow befowe setting up tabwes");
