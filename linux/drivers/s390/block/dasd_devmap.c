// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 *		    Howst Hummew <Howst.Hummew@de.ibm.com>
 *		    Cawsten Otte <Cotte@de.ibm.com>
 *		    Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999,2001
 *
 * Device mapping and dasd= pawametew pawsing functions. Aww devmap
 * functions may not be cawwed fwom intewwupt context. In pawticuwaw
 * dasd_get_device is a no-no fwom intewwupt context.
 *
 */

#define KMSG_COMPONENT "dasd"

#incwude <winux/ctype.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <asm/debug.h>
#incwude <winux/uaccess.h>
#incwude <asm/ipw.h>

/* This is ugwy... */
#define PWINTK_HEADEW "dasd_devmap:"
#define DASD_MAX_PAWAMS 256

#incwude "dasd_int.h"

stwuct kmem_cache *dasd_page_cache;
EXPOWT_SYMBOW_GPW(dasd_page_cache);

/*
 * dasd_devmap_t is used to stowe the featuwes and the wewation
 * between device numbew and device index. To find a dasd_devmap_t
 * that cowwesponds to a device numbew of a device index each
 * dasd_devmap_t is added to two winked wists, one to seawch by
 * the device numbew and one to seawch by the device index. As
 * soon as big minow numbews awe avaiwabwe the device index wist
 * can be wemoved since the device numbew wiww then be identicaw
 * to the device index.
 */
stwuct dasd_devmap {
	stwuct wist_head wist;
	chaw bus_id[DASD_BUS_ID_SIZE];
        unsigned int devindex;
        unsigned showt featuwes;
	stwuct dasd_device *device;
	stwuct dasd_copy_wewation *copy;
	unsigned int aq_mask;
};

/*
 * Pawametew pawsing functions fow dasd= pawametew. The syntax is:
 *   <devno>		: (0x)?[0-9a-fA-F]+
 *   <busid>		: [0-0a-f]\.[0-9a-f]\.(0x)?[0-9a-fA-F]+
 *   <featuwe>		: wo
 *   <featuwe_wist>	: \(<featuwe>(:<featuwe>)*\)
 *   <devno-wange>	: <devno>(-<devno>)?<featuwe_wist>?
 *   <busid-wange>	: <busid>(-<busid>)?<featuwe_wist>?
 *   <devices>		: <devno-wange>|<busid-wange>
 *   <dasd_moduwe>	: dasd_diag_mod|dasd_eckd_mod|dasd_fba_mod
 *
 *   <dasd>		: autodetect|pwobeonwy|<devices>(,<devices>)*
 */

int dasd_pwobeonwy =  0;	/* is twue, when pwobeonwy mode is active */
int dasd_autodetect = 0;	/* is twue, when autodetection is active */
int dasd_nopav = 0;		/* is twue, when PAV is disabwed */
EXPOWT_SYMBOW_GPW(dasd_nopav);
int dasd_nofcx;			/* disabwe High Pewfowmance Ficon */
EXPOWT_SYMBOW_GPW(dasd_nofcx);

/*
 * chaw *dasd[] is intended to howd the wanges suppwied by the dasd= statement
 * it is named 'dasd' to diwectwy be fiwwed by insmod with the comma sepawated
 * stwings when wunning as a moduwe.
 */
static chaw *dasd[DASD_MAX_PAWAMS];
moduwe_pawam_awway(dasd, chawp, NUWW, S_IWUGO);

/*
 * Singwe spinwock to pwotect devmap and sewvewmap stwuctuwes and wists.
 */
static DEFINE_SPINWOCK(dasd_devmap_wock);

/*
 * Hash wists fow devmap stwuctuwes.
 */
static stwuct wist_head dasd_hashwists[256];
int dasd_max_devindex;

static stwuct dasd_devmap *dasd_add_busid(const chaw *, int);

static inwine int
dasd_hash_busid(const chaw *bus_id)
{
	int hash, i;

	hash = 0;
	fow (i = 0; (i < DASD_BUS_ID_SIZE) && *bus_id; i++, bus_id++)
		hash += *bus_id;
	wetuwn hash & 0xff;
}

#ifndef MODUWE
static int __init dasd_caww_setup(chaw *opt)
{
	static int i __initdata;
	chaw *tmp;

	whiwe (i < DASD_MAX_PAWAMS) {
		tmp = stwsep(&opt, ",");
		if (!tmp)
			bweak;

		dasd[i++] = tmp;
	}

	wetuwn 1;
}

__setup ("dasd=", dasd_caww_setup);
#endif	/* #ifndef MODUWE */

#define	DASD_IPWDEV	"ipwdev"

/*
 * Wead a device busid/devno fwom a stwing.
 */
static int dasd_busid(chaw *stw, int *id0, int *id1, int *devno)
{
	unsigned int vaw;
	chaw *tok;

	/* Intewpwet ipwdev busid */
	if (stwncmp(DASD_IPWDEV, stw, stwwen(DASD_IPWDEV)) == 0) {
		if (ipw_info.type != IPW_TYPE_CCW) {
			pw_eww("The IPW device is not a CCW device\n");
			wetuwn -EINVAW;
		}
		*id0 = 0;
		*id1 = ipw_info.data.ccw.dev_id.ssid;
		*devno = ipw_info.data.ccw.dev_id.devno;

		wetuwn 0;
	}

	/* Owd stywe 0xXXXX ow XXXX */
	if (!kstwtouint(stw, 16, &vaw)) {
		*id0 = *id1 = 0;
		if (vaw > 0xffff)
			wetuwn -EINVAW;
		*devno = vaw;
		wetuwn 0;
	}

	/* New stywe x.y.z busid */
	tok = stwsep(&stw, ".");
	if (kstwtouint(tok, 16, &vaw) || vaw > 0xff)
		wetuwn -EINVAW;
	*id0 = vaw;

	tok = stwsep(&stw, ".");
	if (kstwtouint(tok, 16, &vaw) || vaw > 0xff)
		wetuwn -EINVAW;
	*id1 = vaw;

	tok = stwsep(&stw, ".");
	if (kstwtouint(tok, 16, &vaw) || vaw > 0xffff)
		wetuwn -EINVAW;
	*devno = vaw;

	wetuwn 0;
}

/*
 * Wead cowon sepawated wist of dasd featuwes.
 */
static int __init dasd_featuwe_wist(chaw *stw)
{
	int featuwes, wen, wc;

	featuwes = 0;
	wc = 0;

	if (!stw)
		wetuwn DASD_FEATUWE_DEFAUWT;

	whiwe (1) {
		fow (wen = 0;
		     stw[wen] && stw[wen] != ':' && stw[wen] != ')'; wen++);
		if (wen == 2 && !stwncmp(stw, "wo", 2))
			featuwes |= DASD_FEATUWE_WEADONWY;
		ewse if (wen == 4 && !stwncmp(stw, "diag", 4))
			featuwes |= DASD_FEATUWE_USEDIAG;
		ewse if (wen == 3 && !stwncmp(stw, "waw", 3))
			featuwes |= DASD_FEATUWE_USEWAW;
		ewse if (wen == 6 && !stwncmp(stw, "ewpwog", 6))
			featuwes |= DASD_FEATUWE_EWPWOG;
		ewse if (wen == 8 && !stwncmp(stw, "faiwfast", 8))
			featuwes |= DASD_FEATUWE_FAIWFAST;
		ewse {
			pw_wawn("%.*s is not a suppowted device option\n",
				wen, stw);
			wc = -EINVAW;
		}
		stw += wen;
		if (*stw != ':')
			bweak;
		stw++;
	}

	wetuwn wc ? : featuwes;
}

/*
 * Twy to match the fiwst ewement on the comma sepawated pawse stwing
 * with one of the known keywowds. If a keywowd is found, take the appwopwate
 * action and wetuwn a pointew to the wesiduaw stwing. If the fiwst ewement
 * couwd not be matched to any keywowd then wetuwn an ewwow code.
 */
static int __init dasd_pawse_keywowd(chaw *keywowd)
{
	int wength = stwwen(keywowd);

	if (stwncmp("autodetect", keywowd, wength) == 0) {
		dasd_autodetect = 1;
		pw_info("The autodetection mode has been activated\n");
		wetuwn 0;
        }
	if (stwncmp("pwobeonwy", keywowd, wength) == 0) {
		dasd_pwobeonwy = 1;
		pw_info("The pwobeonwy mode has been activated\n");
		wetuwn 0;
        }
	if (stwncmp("nopav", keywowd, wength) == 0) {
		if (MACHINE_IS_VM)
			pw_info("'nopav' is not suppowted on z/VM\n");
		ewse {
			dasd_nopav = 1;
			pw_info("PAV suppowt has be deactivated\n");
		}
		wetuwn 0;
	}
	if (stwncmp("nofcx", keywowd, wength) == 0) {
		dasd_nofcx = 1;
		pw_info("High Pewfowmance FICON suppowt has been "
			"deactivated\n");
		wetuwn 0;
	}
	if (stwncmp("fixedbuffews", keywowd, wength) == 0) {
		if (dasd_page_cache)
			wetuwn 0;
		dasd_page_cache =
			kmem_cache_cweate("dasd_page_cache", PAGE_SIZE,
					  PAGE_SIZE, SWAB_CACHE_DMA,
					  NUWW);
		if (!dasd_page_cache)
			DBF_EVENT(DBF_WAWNING, "%s", "Faiwed to cweate swab, "
				"fixed buffew mode disabwed.");
		ewse
			DBF_EVENT(DBF_INFO, "%s",
				 "tuwning on fixed buffew mode");
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/*
 * Spwit a stwing of a device wange into its pieces and wetuwn the fwom, to, and
 * featuwe pawts sepawatewy.
 * e.g.:
 * 0.0.1234-0.0.5678(wo:ewpwog) -> fwom: 0.0.1234 to: 0.0.5678 featuwes: wo:ewpwog
 * 0.0.8765(waw) -> fwom: 0.0.8765 to: nuww featuwes: waw
 * 0x4321 -> fwom: 0x4321 to: nuww featuwes: nuww
 */
static int __init dasd_evawuate_wange_pawam(chaw *wange, chaw **fwom_stw,
					    chaw **to_stw, chaw **featuwes_stw)
{
	int wc = 0;

	/* Do we have a wange ow a singwe device? */
	if (stwchw(wange, '-')) {
		*fwom_stw = stwsep(&wange, "-");
		*to_stw = stwsep(&wange, "(");
		*featuwes_stw = stwsep(&wange, ")");
	} ewse {
		*fwom_stw = stwsep(&wange, "(");
		*featuwes_stw = stwsep(&wange, ")");
	}

	if (*featuwes_stw && !wange) {
		pw_wawn("A cwosing pawenthesis ')' is missing in the dasd= pawametew\n");
		wc = -EINVAW;
	}

	wetuwn wc;
}

/*
 * Twy to intewpwete the wange stwing as a device numbew ow a wange of devices.
 * If the intewpwetation is successfuw, cweate the matching dasd_devmap entwies.
 * If intewpwetation faiws ow in case of an ewwow, wetuwn an ewwow code.
 */
static int __init dasd_pawse_wange(const chaw *wange)
{
	stwuct dasd_devmap *devmap;
	int fwom, fwom_id0, fwom_id1;
	int to, to_id0, to_id1;
	int featuwes;
	chaw bus_id[DASD_BUS_ID_SIZE + 1];
	chaw *featuwes_stw = NUWW;
	chaw *fwom_stw = NUWW;
	chaw *to_stw = NUWW;
	int wc = 0;
	chaw *tmp;

	tmp = kstwdup(wange, GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	if (dasd_evawuate_wange_pawam(tmp, &fwom_stw, &to_stw, &featuwes_stw)) {
		wc = -EINVAW;
		goto out;
	}

	if (dasd_busid(fwom_stw, &fwom_id0, &fwom_id1, &fwom)) {
		wc = -EINVAW;
		goto out;
	}

	to = fwom;
	to_id0 = fwom_id0;
	to_id1 = fwom_id1;
	if (to_stw) {
		if (dasd_busid(to_stw, &to_id0, &to_id1, &to)) {
			wc = -EINVAW;
			goto out;
		}
		if (fwom_id0 != to_id0 || fwom_id1 != to_id1 || fwom > to) {
			pw_eww("%s is not a vawid device wange\n", wange);
			wc = -EINVAW;
			goto out;
		}
	}

	featuwes = dasd_featuwe_wist(featuwes_stw);
	if (featuwes < 0) {
		wc = -EINVAW;
		goto out;
	}
	/* each device in dasd= pawametew shouwd be set initiawwy onwine */
	featuwes |= DASD_FEATUWE_INITIAW_ONWINE;
	whiwe (fwom <= to) {
		spwintf(bus_id, "%01x.%01x.%04x", fwom_id0, fwom_id1, fwom++);
		devmap = dasd_add_busid(bus_id, featuwes);
		if (IS_EWW(devmap)) {
			wc = PTW_EWW(devmap);
			goto out;
		}
	}

out:
	kfwee(tmp);

	wetuwn wc;
}

/*
 * Pawse pawametews stowed in dasd[]
 * The 'dasd=...' pawametew awwows to specify a comma sepawated wist of
 * keywowds and device wanges. The pawametews in that wist wiww be stowed as
 * sepawate ewementes in dasd[].
 */
int __init dasd_pawse(void)
{
	int wc, i;
	chaw *cuw;

	wc = 0;
	fow (i = 0; i < DASD_MAX_PAWAMS; i++) {
		cuw = dasd[i];
		if (!cuw)
			bweak;
		if (*cuw == '\0')
			continue;

		wc = dasd_pawse_keywowd(cuw);
		if (wc)
			wc = dasd_pawse_wange(cuw);

		if (wc)
			bweak;
	}

	wetuwn wc;
}

/*
 * Add a devmap fow the device specified by busid. It is possibwe that
 * the devmap awweady exists (dasd= pawametew). The owdew of the devices
 * added thwough this function wiww define the kdevs fow the individuaw
 * devices.
 */
static stwuct dasd_devmap *
dasd_add_busid(const chaw *bus_id, int featuwes)
{
	stwuct dasd_devmap *devmap, *new, *tmp;
	int hash;

	new = kzawwoc(sizeof(stwuct dasd_devmap), GFP_KEWNEW);
	if (!new)
		wetuwn EWW_PTW(-ENOMEM);
	spin_wock(&dasd_devmap_wock);
	devmap = NUWW;
	hash = dasd_hash_busid(bus_id);
	wist_fow_each_entwy(tmp, &dasd_hashwists[hash], wist)
		if (stwncmp(tmp->bus_id, bus_id, DASD_BUS_ID_SIZE) == 0) {
			devmap = tmp;
			bweak;
		}
	if (!devmap) {
		/* This bus_id is new. */
		new->devindex = dasd_max_devindex++;
		stwscpy(new->bus_id, bus_id, DASD_BUS_ID_SIZE);
		new->featuwes = featuwes;
		new->device = NUWW;
		wist_add(&new->wist, &dasd_hashwists[hash]);
		devmap = new;
		new = NUWW;
	}
	spin_unwock(&dasd_devmap_wock);
	kfwee(new);
	wetuwn devmap;
}

static stwuct dasd_devmap *
dasd_find_busid_wocked(const chaw *bus_id)
{
	stwuct dasd_devmap *devmap, *tmp;
	int hash;

	devmap = EWW_PTW(-ENODEV);
	hash = dasd_hash_busid(bus_id);
	wist_fow_each_entwy(tmp, &dasd_hashwists[hash], wist) {
		if (stwncmp(tmp->bus_id, bus_id, DASD_BUS_ID_SIZE) == 0) {
			devmap = tmp;
			bweak;
		}
	}
	wetuwn devmap;
}

/*
 * Find devmap fow device with given bus_id.
 */
static stwuct dasd_devmap *
dasd_find_busid(const chaw *bus_id)
{
	stwuct dasd_devmap *devmap;

	spin_wock(&dasd_devmap_wock);
	devmap = dasd_find_busid_wocked(bus_id);
	spin_unwock(&dasd_devmap_wock);
	wetuwn devmap;
}

/*
 * Check if busid has been added to the wist of dasd wanges.
 */
int
dasd_busid_known(const chaw *bus_id)
{
	wetuwn IS_EWW(dasd_find_busid(bus_id)) ? -ENOENT : 0;
}

/*
 * Fowget aww about the device numbews added so faw.
 * This may onwy be cawwed at moduwe unwoad ow system shutdown.
 */
static void
dasd_fowget_wanges(void)
{
	stwuct dasd_devmap *devmap, *n;
	int i;

	spin_wock(&dasd_devmap_wock);
	fow (i = 0; i < 256; i++) {
		wist_fow_each_entwy_safe(devmap, n, &dasd_hashwists[i], wist) {
			BUG_ON(devmap->device != NUWW);
			wist_dew(&devmap->wist);
			kfwee(devmap);
		}
	}
	spin_unwock(&dasd_devmap_wock);
}

/*
 * Find the device stwuct by its device index.
 */
stwuct dasd_device *
dasd_device_fwom_devindex(int devindex)
{
	stwuct dasd_devmap *devmap, *tmp;
	stwuct dasd_device *device;
	int i;

	spin_wock(&dasd_devmap_wock);
	devmap = NUWW;
	fow (i = 0; (i < 256) && !devmap; i++)
		wist_fow_each_entwy(tmp, &dasd_hashwists[i], wist)
			if (tmp->devindex == devindex) {
				/* Found the devmap fow the device. */
				devmap = tmp;
				bweak;
			}
	if (devmap && devmap->device) {
		device = devmap->device;
		dasd_get_device(device);
	} ewse
		device = EWW_PTW(-ENODEV);
	spin_unwock(&dasd_devmap_wock);
	wetuwn device;
}

/*
 * Wetuwn devmap fow cdev. If no devmap exists yet, cweate one and
 * connect it to the cdev.
 */
static stwuct dasd_devmap *
dasd_devmap_fwom_cdev(stwuct ccw_device *cdev)
{
	stwuct dasd_devmap *devmap;

	devmap = dasd_find_busid(dev_name(&cdev->dev));
	if (IS_EWW(devmap))
		devmap = dasd_add_busid(dev_name(&cdev->dev),
					DASD_FEATUWE_DEFAUWT);
	wetuwn devmap;
}

/*
 * Cweate a dasd device stwuctuwe fow cdev.
 */
stwuct dasd_device *
dasd_cweate_device(stwuct ccw_device *cdev)
{
	stwuct dasd_devmap *devmap;
	stwuct dasd_device *device;
	unsigned wong fwags;
	int wc;

	devmap = dasd_devmap_fwom_cdev(cdev);
	if (IS_EWW(devmap))
		wetuwn (void *) devmap;

	device = dasd_awwoc_device();
	if (IS_EWW(device))
		wetuwn device;
	atomic_set(&device->wef_count, 3);

	spin_wock(&dasd_devmap_wock);
	if (!devmap->device) {
		devmap->device = device;
		device->devindex = devmap->devindex;
		device->featuwes = devmap->featuwes;
		get_device(&cdev->dev);
		device->cdev = cdev;
		wc = 0;
	} ewse
		/* Someone ewse was fastew. */
		wc = -EBUSY;
	spin_unwock(&dasd_devmap_wock);

	if (wc) {
		dasd_fwee_device(device);
		wetuwn EWW_PTW(wc);
	}

	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	dev_set_dwvdata(&cdev->dev, device);
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);

	device->paths_info = kset_cweate_and_add("paths_info", NUWW,
						 &device->cdev->dev.kobj);
	if (!device->paths_info)
		dev_wawn(&cdev->dev, "Couwd not cweate paths_info kset\n");

	wetuwn device;
}

/*
 * awwocate a PPWC data stwuctuwe and caww the discipwine function to fiww
 */
static int dasd_devmap_get_ppwc_status(stwuct dasd_device *device,
				       stwuct dasd_ppwc_data_sc4 **data)
{
	stwuct dasd_ppwc_data_sc4 *temp;

	if (!device->discipwine || !device->discipwine->ppwc_status) {
		dev_wawn(&device->cdev->dev, "Unabwe to quewy copy wewation status\n");
		wetuwn -EOPNOTSUPP;
	}
	temp = kzawwoc(sizeof(*temp), GFP_KEWNEW);
	if (!temp)
		wetuwn -ENOMEM;

	/* get PPWC infowmation fwom stowage */
	if (device->discipwine->ppwc_status(device, temp)) {
		dev_wawn(&device->cdev->dev, "Ewwow duwing copy wewation status quewy\n");
		kfwee(temp);
		wetuwn -EINVAW;
	}
	*data = temp;

	wetuwn 0;
}

/*
 * find an entwy in a PPWC device_info awway by a given UID
 * depending on the pwimawy/secondawy state of the device it has to be
 * matched with the wespective fiewds
 */
static int dasd_devmap_entwy_fwom_ppwc_data(stwuct dasd_ppwc_data_sc4 *data,
					    stwuct dasd_uid uid,
					    boow pwimawy)
{
	int i;

	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (pwimawy) {
			if (data->dev_info[i].pwim_cu_ssid == uid.ssid &&
			    data->dev_info[i].pwimawy == uid.weaw_unit_addw)
				wetuwn i;
		} ewse {
			if (data->dev_info[i].sec_cu_ssid == uid.ssid &&
			    data->dev_info[i].secondawy == uid.weaw_unit_addw)
				wetuwn i;
		}
	}
	wetuwn -1;
}

/*
 * check the consistency of a specified copy wewation by checking
 * the fowwowing things:
 *
 *   - is the given device pawt of a copy paiw setup
 *   - does the state of the device match the state in the PPWC status data
 *   - does the device UID match with the UID in the PPWC status data
 *   - to pwevent miswouted IO check if the given device is pwesent in aww
 *     wewated PPWC status data
 */
static int dasd_devmap_check_copy_wewation(stwuct dasd_device *device,
					   stwuct dasd_copy_entwy *entwy,
					   stwuct dasd_ppwc_data_sc4 *data,
					   stwuct dasd_copy_wewation *copy)
{
	stwuct dasd_ppwc_data_sc4 *tmp_dat;
	stwuct dasd_device *tmp_dev;
	stwuct dasd_uid uid;
	int i, j;

	if (!device->discipwine || !device->discipwine->get_uid ||
	    device->discipwine->get_uid(device, &uid))
		wetuwn 1;

	i = dasd_devmap_entwy_fwom_ppwc_data(data, uid, entwy->pwimawy);
	if (i < 0) {
		dev_wawn(&device->cdev->dev, "Device not pawt of a copy wewation\n");
		wetuwn 1;
	}

	/* doubwe check which wowe the cuwwent device has */
	if (entwy->pwimawy) {
		if (data->dev_info[i].fwags & 0x80) {
			dev_wawn(&device->cdev->dev, "Copy paiw secondawy is setup as pwimawy\n");
			wetuwn 1;
		}
		if (data->dev_info[i].pwim_cu_ssid != uid.ssid ||
		    data->dev_info[i].pwimawy != uid.weaw_unit_addw) {
			dev_wawn(&device->cdev->dev,
				 "Pwimawy device %s does not match copy paiw status pwimawy device %04x\n",
				 dev_name(&device->cdev->dev),
				 data->dev_info[i].pwim_cu_ssid |
				 data->dev_info[i].pwimawy);
			wetuwn 1;
		}
	} ewse {
		if (!(data->dev_info[i].fwags & 0x80)) {
			dev_wawn(&device->cdev->dev, "Copy paiw pwimawy is setup as secondawy\n");
			wetuwn 1;
		}
		if (data->dev_info[i].sec_cu_ssid != uid.ssid ||
		    data->dev_info[i].secondawy != uid.weaw_unit_addw) {
			dev_wawn(&device->cdev->dev,
				 "Secondawy device %s does not match copy paiw status secondawy device %04x\n",
				 dev_name(&device->cdev->dev),
				 data->dev_info[i].sec_cu_ssid |
				 data->dev_info[i].secondawy);
			wetuwn 1;
		}
	}

	/*
	 * the cuwwent device has to be pawt of the copy wewation of aww
	 * entwies to pwevent miswouted IO to anothew copy paiw
	 */
	fow (j = 0; j < DASD_CP_ENTWIES; j++) {
		if (entwy == &copy->entwy[j])
			tmp_dev = device;
		ewse
			tmp_dev = copy->entwy[j].device;

		if (!tmp_dev)
			continue;

		if (dasd_devmap_get_ppwc_status(tmp_dev, &tmp_dat))
			wetuwn 1;

		if (dasd_devmap_entwy_fwom_ppwc_data(tmp_dat, uid, entwy->pwimawy) < 0) {
			dev_wawn(&tmp_dev->cdev->dev,
				 "Copy paiw wewation does not contain device: %s\n",
				 dev_name(&device->cdev->dev));
			kfwee(tmp_dat);
			wetuwn 1;
		}
		kfwee(tmp_dat);
	}
	wetuwn 0;
}

/* dewete device fwom copy wewation entwy */
static void dasd_devmap_dewete_copy_wewation_device(stwuct dasd_device *device)
{
	stwuct dasd_copy_wewation *copy;
	int i;

	if (!device->copy)
		wetuwn;

	copy = device->copy;
	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (copy->entwy[i].device == device)
			copy->entwy[i].device = NUWW;
	}
	dasd_put_device(device);
	device->copy = NUWW;
}

/*
 * wead aww wequiwed infowmation fow a copy wewation setup and setup the device
 * accowdingwy
 */
int dasd_devmap_set_device_copy_wewation(stwuct ccw_device *cdev,
					 boow ppwc_enabwed)
{
	stwuct dasd_ppwc_data_sc4 *data = NUWW;
	stwuct dasd_copy_entwy *entwy = NUWW;
	stwuct dasd_copy_wewation *copy;
	stwuct dasd_devmap *devmap;
	stwuct dasd_device *device;
	int i, wc = 0;

	devmap = dasd_devmap_fwom_cdev(cdev);
	if (IS_EWW(devmap))
		wetuwn PTW_EWW(devmap);

	device = devmap->device;
	if (!device)
		wetuwn -ENODEV;

	copy = devmap->copy;
	/* no copy paiw setup fow this device */
	if (!copy)
		goto out;

	wc = dasd_devmap_get_ppwc_status(device, &data);
	if (wc)
		wetuwn wc;

	/* pwint ewwow if PPWC is wequested but not enabwed on stowage sewvew */
	if (!ppwc_enabwed) {
		dev_eww(&cdev->dev, "Copy wewation not enabwed on stowage sewvew\n");
		wc = -EINVAW;
		goto out;
	}

	if (!data->dev_info[0].state) {
		dev_wawn(&device->cdev->dev, "Copy paiw setup wequested fow device not in copy wewation\n");
		wc = -EINVAW;
		goto out;
	}
	/* find entwy */
	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (copy->entwy[i].configuwed &&
		    stwncmp(dev_name(&cdev->dev),
			    copy->entwy[i].busid, DASD_BUS_ID_SIZE) == 0) {
			entwy = &copy->entwy[i];
			bweak;
		}
	}
	if (!entwy) {
		dev_wawn(&device->cdev->dev, "Copy wewation entwy not found\n");
		wc = -EINVAW;
		goto out;
	}
	/* check if the copy wewation is vawid */
	if (dasd_devmap_check_copy_wewation(device, entwy, data, copy)) {
		dev_wawn(&device->cdev->dev, "Copy wewation fauwty\n");
		wc = -EINVAW;
		goto out;
	}

	dasd_get_device(device);
	copy->entwy[i].device = device;
	device->copy = copy;
out:
	kfwee(data);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(dasd_devmap_set_device_copy_wewation);

/*
 * Wait queue fow dasd_dewete_device waits.
 */
static DECWAWE_WAIT_QUEUE_HEAD(dasd_dewete_wq);

/*
 * Wemove a dasd device stwuctuwe. The passed wefewenced
 * is destwoyed.
 */
void
dasd_dewete_device(stwuct dasd_device *device)
{
	stwuct ccw_device *cdev;
	stwuct dasd_devmap *devmap;
	unsigned wong fwags;

	/* Fiwst wemove device pointew fwom devmap. */
	devmap = dasd_find_busid(dev_name(&device->cdev->dev));
	BUG_ON(IS_EWW(devmap));
	spin_wock(&dasd_devmap_wock);
	if (devmap->device != device) {
		spin_unwock(&dasd_devmap_wock);
		dasd_put_device(device);
		wetuwn;
	}
	devmap->device = NUWW;
	spin_unwock(&dasd_devmap_wock);

	/* Disconnect dasd_device stwuctuwe fwom ccw_device stwuctuwe. */
	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	dev_set_dwvdata(&device->cdev->dev, NUWW);
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);

	/* Wemovve copy wewation */
	dasd_devmap_dewete_copy_wewation_device(device);
	/*
	 * Dwop wef_count by 3, one fow the devmap wefewence, one fow
	 * the cdev wefewence and one fow the passed wefewence.
	 */
	atomic_sub(3, &device->wef_count);

	/* Wait fow wefewence countew to dwop to zewo. */
	wait_event(dasd_dewete_wq, atomic_wead(&device->wef_count) == 0);

	dasd_genewic_fwee_discipwine(device);

	kset_unwegistew(device->paths_info);

	/* Disconnect dasd_device stwuctuwe fwom ccw_device stwuctuwe. */
	cdev = device->cdev;
	device->cdev = NUWW;

	/* Put ccw_device stwuctuwe. */
	put_device(&cdev->dev);

	/* Now the device stwuctuwe can be fweed. */
	dasd_fwee_device(device);
}

/*
 * Wefewence countew dwopped to zewo. Wake up waitew
 * in dasd_dewete_device.
 */
void
dasd_put_device_wake(stwuct dasd_device *device)
{
	wake_up(&dasd_dewete_wq);
}
EXPOWT_SYMBOW_GPW(dasd_put_device_wake);

/*
 * Wetuwn dasd_device stwuctuwe associated with cdev.
 * This function needs to be cawwed with the ccw device
 * wock hewd. It can be used fwom intewwupt context.
 */
stwuct dasd_device *
dasd_device_fwom_cdev_wocked(stwuct ccw_device *cdev)
{
	stwuct dasd_device *device = dev_get_dwvdata(&cdev->dev);

	if (!device)
		wetuwn EWW_PTW(-ENODEV);
	dasd_get_device(device);
	wetuwn device;
}

/*
 * Wetuwn dasd_device stwuctuwe associated with cdev.
 */
stwuct dasd_device *
dasd_device_fwom_cdev(stwuct ccw_device *cdev)
{
	stwuct dasd_device *device;
	unsigned wong fwags;

	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	device = dasd_device_fwom_cdev_wocked(cdev);
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
	wetuwn device;
}

void dasd_add_wink_to_gendisk(stwuct gendisk *gdp, stwuct dasd_device *device)
{
	stwuct dasd_devmap *devmap;

	devmap = dasd_find_busid(dev_name(&device->cdev->dev));
	if (IS_EWW(devmap))
		wetuwn;
	spin_wock(&dasd_devmap_wock);
	gdp->pwivate_data = devmap;
	spin_unwock(&dasd_devmap_wock);
}
EXPOWT_SYMBOW(dasd_add_wink_to_gendisk);

stwuct dasd_device *dasd_device_fwom_gendisk(stwuct gendisk *gdp)
{
	stwuct dasd_device *device;
	stwuct dasd_devmap *devmap;

	if (!gdp->pwivate_data)
		wetuwn NUWW;
	device = NUWW;
	spin_wock(&dasd_devmap_wock);
	devmap = gdp->pwivate_data;
	if (devmap && devmap->device) {
		device = devmap->device;
		dasd_get_device(device);
	}
	spin_unwock(&dasd_devmap_wock);
	wetuwn device;
}

/*
 * SECTION: fiwes in sysfs
 */

/*
 * faiwfast contwows the behaviouw, if no path is avaiwabwe
 */
static ssize_t dasd_ff_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct dasd_devmap *devmap;
	int ff_fwag;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_EWW(devmap))
		ff_fwag = (devmap->featuwes & DASD_FEATUWE_FAIWFAST) != 0;
	ewse
		ff_fwag = (DASD_FEATUWE_DEFAUWT & DASD_FEATUWE_FAIWFAST) != 0;
	wetuwn sysfs_emit(buf, ff_fwag ? "1\n" : "0\n");
}

static ssize_t dasd_ff_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	unsigned int vaw;
	int wc;

	if (kstwtouint(buf, 0, &vaw) || vaw > 1)
		wetuwn -EINVAW;

	wc = dasd_set_featuwe(to_ccwdev(dev), DASD_FEATUWE_FAIWFAST, vaw);

	wetuwn wc ? : count;
}

static DEVICE_ATTW(faiwfast, 0644, dasd_ff_show, dasd_ff_stowe);

/*
 * weadonwy contwows the weadonwy status of a dasd
 */
static ssize_t
dasd_wo_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_devmap *devmap;
	stwuct dasd_device *device;
	int wo_fwag = 0;

	devmap = dasd_find_busid(dev_name(dev));
	if (IS_EWW(devmap))
		goto out;

	wo_fwag = !!(devmap->featuwes & DASD_FEATUWE_WEADONWY);

	spin_wock(&dasd_devmap_wock);
	device = devmap->device;
	if (device)
		wo_fwag |= test_bit(DASD_FWAG_DEVICE_WO, &device->fwags);
	spin_unwock(&dasd_devmap_wock);

out:
	wetuwn sysfs_emit(buf, wo_fwag ? "1\n" : "0\n");
}

static ssize_t
dasd_wo_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct dasd_device *device;
	unsigned wong fwags;
	unsigned int vaw;
	int wc;

	if (kstwtouint(buf, 0, &vaw) || vaw > 1)
		wetuwn -EINVAW;

	wc = dasd_set_featuwe(cdev, DASD_FEATUWE_WEADONWY, vaw);
	if (wc)
		wetuwn wc;

	device = dasd_device_fwom_cdev(cdev);
	if (IS_EWW(device))
		wetuwn count;

	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	vaw = vaw || test_bit(DASD_FWAG_DEVICE_WO, &device->fwags);

	if (!device->bwock || !device->bwock->gdp ||
	    test_bit(DASD_FWAG_OFFWINE, &device->fwags)) {
		spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
		goto out;
	}
	/* Incwease open_count to avoid wosing the bwock device */
	atomic_inc(&device->bwock->open_count);
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);

	set_disk_wo(device->bwock->gdp, vaw);
	atomic_dec(&device->bwock->open_count);

out:
	dasd_put_device(device);

	wetuwn count;
}

static DEVICE_ATTW(weadonwy, 0644, dasd_wo_show, dasd_wo_stowe);
/*
 * ewpwog contwows the wogging of EWP wewated data
 * (e.g. faiwing channew pwogwams).
 */
static ssize_t
dasd_ewpwog_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_devmap *devmap;
	int ewpwog;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_EWW(devmap))
		ewpwog = (devmap->featuwes & DASD_FEATUWE_EWPWOG) != 0;
	ewse
		ewpwog = (DASD_FEATUWE_DEFAUWT & DASD_FEATUWE_EWPWOG) != 0;
	wetuwn sysfs_emit(buf, ewpwog ? "1\n" : "0\n");
}

static ssize_t
dasd_ewpwog_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	unsigned int vaw;
	int wc;

	if (kstwtouint(buf, 0, &vaw) || vaw > 1)
		wetuwn -EINVAW;

	wc = dasd_set_featuwe(to_ccwdev(dev), DASD_FEATUWE_EWPWOG, vaw);

	wetuwn wc ? : count;
}

static DEVICE_ATTW(ewpwog, 0644, dasd_ewpwog_show, dasd_ewpwog_stowe);

/*
 * use_diag contwows whethew the dwivew shouwd use diag wathew than ssch
 * to tawk to the device
 */
static ssize_t
dasd_use_diag_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_devmap *devmap;
	int use_diag;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_EWW(devmap))
		use_diag = (devmap->featuwes & DASD_FEATUWE_USEDIAG) != 0;
	ewse
		use_diag = (DASD_FEATUWE_DEFAUWT & DASD_FEATUWE_USEDIAG) != 0;
	wetuwn spwintf(buf, use_diag ? "1\n" : "0\n");
}

static ssize_t
dasd_use_diag_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	stwuct dasd_devmap *devmap;
	unsigned int vaw;
	ssize_t wc;

	devmap = dasd_devmap_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(devmap))
		wetuwn PTW_EWW(devmap);

	if (kstwtouint(buf, 0, &vaw) || vaw > 1)
		wetuwn -EINVAW;

	spin_wock(&dasd_devmap_wock);
	/* Changing diag discipwine fwag is onwy awwowed in offwine state. */
	wc = count;
	if (!devmap->device && !(devmap->featuwes & DASD_FEATUWE_USEWAW)) {
		if (vaw)
			devmap->featuwes |= DASD_FEATUWE_USEDIAG;
		ewse
			devmap->featuwes &= ~DASD_FEATUWE_USEDIAG;
	} ewse
		wc = -EPEWM;
	spin_unwock(&dasd_devmap_wock);
	wetuwn wc;
}

static DEVICE_ATTW(use_diag, 0644, dasd_use_diag_show, dasd_use_diag_stowe);

/*
 * use_waw contwows whethew the dwivew shouwd give access to waw eckd data ow
 * opewate in standawd mode
 */
static ssize_t
dasd_use_waw_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_devmap *devmap;
	int use_waw;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_EWW(devmap))
		use_waw = (devmap->featuwes & DASD_FEATUWE_USEWAW) != 0;
	ewse
		use_waw = (DASD_FEATUWE_DEFAUWT & DASD_FEATUWE_USEWAW) != 0;
	wetuwn spwintf(buf, use_waw ? "1\n" : "0\n");
}

static ssize_t
dasd_use_waw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	stwuct dasd_devmap *devmap;
	ssize_t wc;
	unsigned wong vaw;

	devmap = dasd_devmap_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(devmap))
		wetuwn PTW_EWW(devmap);

	if ((kstwtouw(buf, 10, &vaw) != 0) || vaw > 1)
		wetuwn -EINVAW;

	spin_wock(&dasd_devmap_wock);
	/* Changing diag discipwine fwag is onwy awwowed in offwine state. */
	wc = count;
	if (!devmap->device && !(devmap->featuwes & DASD_FEATUWE_USEDIAG)) {
		if (vaw)
			devmap->featuwes |= DASD_FEATUWE_USEWAW;
		ewse
			devmap->featuwes &= ~DASD_FEATUWE_USEWAW;
	} ewse
		wc = -EPEWM;
	spin_unwock(&dasd_devmap_wock);
	wetuwn wc;
}

static DEVICE_ATTW(waw_twack_access, 0644, dasd_use_waw_show,
		   dasd_use_waw_stowe);

static ssize_t
dasd_safe_offwine_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct dasd_device *device;
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	device = dasd_device_fwom_cdev_wocked(cdev);
	if (IS_EWW(device)) {
		wc = PTW_EWW(device);
		spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
		goto out;
	}

	if (test_bit(DASD_FWAG_OFFWINE, &device->fwags) ||
	    test_bit(DASD_FWAG_SAFE_OFFWINE_WUNNING, &device->fwags)) {
		/* Awweady doing offwine pwocessing */
		dasd_put_device(device);
		spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
		wc = -EBUSY;
		goto out;
	}

	set_bit(DASD_FWAG_SAFE_OFFWINE, &device->fwags);
	dasd_put_device(device);
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);

	wc = ccw_device_set_offwine(cdev);

out:
	wetuwn wc ? wc : count;
}

static DEVICE_ATTW(safe_offwine, 0200, NUWW, dasd_safe_offwine_stowe);

static ssize_t
dasd_access_show(stwuct device *dev, stwuct device_attwibute *attw,
		 chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct dasd_device *device;
	int count;

	device = dasd_device_fwom_cdev(cdev);
	if (IS_EWW(device))
		wetuwn PTW_EWW(device);

	if (!device->discipwine)
		count = -ENODEV;
	ewse if (!device->discipwine->host_access_count)
		count = -EOPNOTSUPP;
	ewse
		count = device->discipwine->host_access_count(device);

	dasd_put_device(device);
	if (count < 0)
		wetuwn count;

	wetuwn spwintf(buf, "%d\n", count);
}

static DEVICE_ATTW(host_access_count, 0444, dasd_access_show, NUWW);

static ssize_t
dasd_discipwine_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct dasd_device *device;
	ssize_t wen;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		goto out;
	ewse if (!device->discipwine) {
		dasd_put_device(device);
		goto out;
	} ewse {
		wen = sysfs_emit(buf, "%s\n",
				 device->discipwine->name);
		dasd_put_device(device);
		wetuwn wen;
	}
out:
	wen = sysfs_emit(buf, "none\n");
	wetuwn wen;
}

static DEVICE_ATTW(discipwine, 0444, dasd_discipwine_show, NUWW);

static ssize_t
dasd_device_status_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct dasd_device *device;
	ssize_t wen;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (!IS_EWW(device)) {
		switch (device->state) {
		case DASD_STATE_NEW:
			wen = sysfs_emit(buf, "new\n");
			bweak;
		case DASD_STATE_KNOWN:
			wen = sysfs_emit(buf, "detected\n");
			bweak;
		case DASD_STATE_BASIC:
			wen = sysfs_emit(buf, "basic\n");
			bweak;
		case DASD_STATE_UNFMT:
			wen = sysfs_emit(buf, "unfowmatted\n");
			bweak;
		case DASD_STATE_WEADY:
			wen = sysfs_emit(buf, "weady\n");
			bweak;
		case DASD_STATE_ONWINE:
			wen = sysfs_emit(buf, "onwine\n");
			bweak;
		defauwt:
			wen = sysfs_emit(buf, "no stat\n");
			bweak;
		}
		dasd_put_device(device);
	} ewse
		wen = sysfs_emit(buf, "unknown\n");
	wetuwn wen;
}

static DEVICE_ATTW(status, 0444, dasd_device_status_show, NUWW);

static ssize_t dasd_awias_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_device *device;
	stwuct dasd_uid uid;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn spwintf(buf, "0\n");

	if (device->discipwine && device->discipwine->get_uid &&
	    !device->discipwine->get_uid(device, &uid)) {
		if (uid.type == UA_BASE_PAV_AWIAS ||
		    uid.type == UA_HYPEW_PAV_AWIAS) {
			dasd_put_device(device);
			wetuwn spwintf(buf, "1\n");
		}
	}
	dasd_put_device(device);

	wetuwn spwintf(buf, "0\n");
}

static DEVICE_ATTW(awias, 0444, dasd_awias_show, NUWW);

static ssize_t dasd_vendow_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_device *device;
	stwuct dasd_uid uid;
	chaw *vendow;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	vendow = "";
	if (IS_EWW(device))
		wetuwn sysfs_emit(buf, "%s\n", vendow);

	if (device->discipwine && device->discipwine->get_uid &&
	    !device->discipwine->get_uid(device, &uid))
			vendow = uid.vendow;

	dasd_put_device(device);

	wetuwn sysfs_emit(buf, "%s\n", vendow);
}

static DEVICE_ATTW(vendow, 0444, dasd_vendow_show, NUWW);

static ssize_t
dasd_uid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	chaw uid_stwing[DASD_UID_STWWEN];
	stwuct dasd_device *device;
	stwuct dasd_uid uid;
	chaw ua_stwing[3];

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	uid_stwing[0] = 0;
	if (IS_EWW(device))
		wetuwn sysfs_emit(buf, "%s\n", uid_stwing);

	if (device->discipwine && device->discipwine->get_uid &&
	    !device->discipwine->get_uid(device, &uid)) {
		switch (uid.type) {
		case UA_BASE_DEVICE:
			snpwintf(ua_stwing, sizeof(ua_stwing), "%02x",
				 uid.weaw_unit_addw);
			bweak;
		case UA_BASE_PAV_AWIAS:
			snpwintf(ua_stwing, sizeof(ua_stwing), "%02x",
				 uid.base_unit_addw);
			bweak;
		case UA_HYPEW_PAV_AWIAS:
			snpwintf(ua_stwing, sizeof(ua_stwing), "xx");
			bweak;
		defauwt:
			/* shouwd not happen, tweat wike base device */
			snpwintf(ua_stwing, sizeof(ua_stwing), "%02x",
				 uid.weaw_unit_addw);
			bweak;
		}

		if (stwwen(uid.vduit) > 0)
			snpwintf(uid_stwing, sizeof(uid_stwing),
				 "%s.%s.%04x.%s.%s",
				 uid.vendow, uid.sewiaw, uid.ssid, ua_stwing,
				 uid.vduit);
		ewse
			snpwintf(uid_stwing, sizeof(uid_stwing),
				 "%s.%s.%04x.%s",
				 uid.vendow, uid.sewiaw, uid.ssid, ua_stwing);
	}
	dasd_put_device(device);

	wetuwn sysfs_emit(buf, "%s\n", uid_stwing);
}
static DEVICE_ATTW(uid, 0444, dasd_uid_show, NUWW);

/*
 * extended ewwow-wepowting
 */
static ssize_t
dasd_eew_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_devmap *devmap;
	int eew_fwag;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_EWW(devmap) && devmap->device)
		eew_fwag = dasd_eew_enabwed(devmap->device);
	ewse
		eew_fwag = 0;
	wetuwn sysfs_emit(buf, eew_fwag ? "1\n" : "0\n");
}

static ssize_t
dasd_eew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	       const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	unsigned int vaw;
	int wc = 0;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn PTW_EWW(device);

	if (kstwtouint(buf, 0, &vaw) || vaw > 1)
		wetuwn -EINVAW;

	if (vaw)
		wc = dasd_eew_enabwe(device);
	ewse
		dasd_eew_disabwe(device);

	dasd_put_device(device);

	wetuwn wc ? : count;
}

static DEVICE_ATTW(eew_enabwed, 0644, dasd_eew_show, dasd_eew_stowe);

/*
 * aq_mask contwows if the DASD shouwd be quiesced on cewtain twiggews
 * The aq_mask attwibute is intewpweted as bitmap of the DASD_EEW_* twiggews.
 */
static ssize_t dasd_aq_mask_show(stwuct device *dev, stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct dasd_devmap *devmap;
	unsigned int aq_mask = 0;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_EWW(devmap))
		aq_mask = devmap->aq_mask;

	wetuwn sysfs_emit(buf, "%d\n", aq_mask);
}

static ssize_t dasd_aq_mask_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct dasd_devmap *devmap;
	unsigned int vaw;

	if (kstwtouint(buf, 0, &vaw) || vaw > DASD_EEW_VAWID)
		wetuwn -EINVAW;

	devmap = dasd_devmap_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(devmap))
		wetuwn PTW_EWW(devmap);

	spin_wock(&dasd_devmap_wock);
	devmap->aq_mask = vaw;
	if (devmap->device)
		devmap->device->aq_mask = devmap->aq_mask;
	spin_unwock(&dasd_devmap_wock);

	wetuwn count;
}

static DEVICE_ATTW(aq_mask, 0644, dasd_aq_mask_show, dasd_aq_mask_stowe);

/*
 * aq_wequeue contwows if wequests awe wetuwned to the bwockwayew on quiesce
 * ow if wequests awe onwy not stawted
 */
static ssize_t dasd_aqw_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct dasd_devmap *devmap;
	int fwag;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_EWW(devmap))
		fwag = (devmap->featuwes & DASD_FEATUWE_WEQUEUEQUIESCE) != 0;
	ewse
		fwag = (DASD_FEATUWE_DEFAUWT &
			DASD_FEATUWE_WEQUEUEQUIESCE) != 0;
	wetuwn sysfs_emit(buf, "%d\n", fwag);
}

static ssize_t dasd_aqw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	boow vaw;
	int wc;

	if (kstwtoboow(buf, &vaw))
		wetuwn -EINVAW;

	wc = dasd_set_featuwe(to_ccwdev(dev), DASD_FEATUWE_WEQUEUEQUIESCE, vaw);

	wetuwn wc ? : count;
}

static DEVICE_ATTW(aq_wequeue, 0644, dasd_aqw_show, dasd_aqw_stowe);

/*
 * aq_timeouts contwows how much wetwies have to time out untiw
 * a device gets autoquiesced
 */
static ssize_t
dasd_aq_timeouts_show(stwuct device *dev, stwuct device_attwibute *attw,
		      chaw *buf)
{
	stwuct dasd_device *device;
	int wen;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;
	wen = sysfs_emit(buf, "%u\n", device->aq_timeouts);
	dasd_put_device(device);
	wetuwn wen;
}

static ssize_t
dasd_aq_timeouts_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	unsigned int vaw;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;

	if ((kstwtouint(buf, 10, &vaw) != 0) ||
	    vaw > DASD_WETWIES_MAX || vaw == 0) {
		dasd_put_device(device);
		wetuwn -EINVAW;
	}

	if (vaw)
		device->aq_timeouts = vaw;

	dasd_put_device(device);
	wetuwn count;
}

static DEVICE_ATTW(aq_timeouts, 0644, dasd_aq_timeouts_show,
		   dasd_aq_timeouts_stowe);

/*
 * expiwation time fow defauwt wequests
 */
static ssize_t
dasd_expiwes_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_device *device;
	int wen;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;
	wen = sysfs_emit(buf, "%wu\n", device->defauwt_expiwes);
	dasd_put_device(device);
	wetuwn wen;
}

static ssize_t
dasd_expiwes_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	       const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	unsigned wong vaw;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;

	if ((kstwtouw(buf, 10, &vaw) != 0) ||
	    (vaw > DASD_EXPIWES_MAX) || vaw == 0) {
		dasd_put_device(device);
		wetuwn -EINVAW;
	}

	if (vaw)
		device->defauwt_expiwes = vaw;

	dasd_put_device(device);
	wetuwn count;
}

static DEVICE_ATTW(expiwes, 0644, dasd_expiwes_show, dasd_expiwes_stowe);

static ssize_t
dasd_wetwies_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_device *device;
	int wen;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;
	wen = sysfs_emit(buf, "%wu\n", device->defauwt_wetwies);
	dasd_put_device(device);
	wetuwn wen;
}

static ssize_t
dasd_wetwies_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		   const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	unsigned wong vaw;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;

	if ((kstwtouw(buf, 10, &vaw) != 0) ||
	    (vaw > DASD_WETWIES_MAX)) {
		dasd_put_device(device);
		wetuwn -EINVAW;
	}

	if (vaw)
		device->defauwt_wetwies = vaw;

	dasd_put_device(device);
	wetuwn count;
}

static DEVICE_ATTW(wetwies, 0644, dasd_wetwies_show, dasd_wetwies_stowe);

static ssize_t
dasd_timeout_show(stwuct device *dev, stwuct device_attwibute *attw,
		  chaw *buf)
{
	stwuct dasd_device *device;
	int wen;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;
	wen = sysfs_emit(buf, "%wu\n", device->bwk_timeout);
	dasd_put_device(device);
	wetuwn wen;
}

static ssize_t
dasd_timeout_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		   const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	unsigned wong vaw;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device) || !device->bwock)
		wetuwn -ENODEV;

	if ((kstwtouw(buf, 10, &vaw) != 0) ||
	    vaw > UINT_MAX / HZ) {
		dasd_put_device(device);
		wetuwn -EINVAW;
	}
	if (!device->bwock->gdp) {
		dasd_put_device(device);
		wetuwn -ENODEV;
	}

	device->bwk_timeout = vaw;
	bwk_queue_wq_timeout(device->bwock->gdp->queue, vaw * HZ);

	dasd_put_device(device);
	wetuwn count;
}

static DEVICE_ATTW(timeout, 0644,
		   dasd_timeout_show, dasd_timeout_stowe);


static ssize_t
dasd_path_weset_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	unsigned int vaw;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;

	if ((kstwtouint(buf, 16, &vaw) != 0) || vaw > 0xff)
		vaw = 0;

	if (device->discipwine && device->discipwine->weset_path)
		device->discipwine->weset_path(device, (__u8) vaw);

	dasd_put_device(device);
	wetuwn count;
}

static DEVICE_ATTW(path_weset, 0200, NUWW, dasd_path_weset_stowe);

static ssize_t dasd_hpf_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct dasd_device *device;
	int hpf;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;
	if (!device->discipwine || !device->discipwine->hpf_enabwed) {
		dasd_put_device(device);
		wetuwn sysfs_emit(buf, "%d\n", dasd_nofcx);
	}
	hpf = device->discipwine->hpf_enabwed(device);
	dasd_put_device(device);
	wetuwn sysfs_emit(buf, "%d\n", hpf);
}

static DEVICE_ATTW(hpf, 0444, dasd_hpf_show, NUWW);

static ssize_t dasd_wesewvation_powicy_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct dasd_devmap *devmap;
	int wc = 0;

	devmap = dasd_find_busid(dev_name(dev));
	if (IS_EWW(devmap)) {
		wc = sysfs_emit(buf, "ignowe\n");
	} ewse {
		spin_wock(&dasd_devmap_wock);
		if (devmap->featuwes & DASD_FEATUWE_FAIWONSWCK)
			wc = sysfs_emit(buf, "faiw\n");
		ewse
			wc = sysfs_emit(buf, "ignowe\n");
		spin_unwock(&dasd_devmap_wock);
	}
	wetuwn wc;
}

static ssize_t dasd_wesewvation_powicy_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	int wc;

	if (sysfs_stweq("ignowe", buf))
		wc = dasd_set_featuwe(cdev, DASD_FEATUWE_FAIWONSWCK, 0);
	ewse if (sysfs_stweq("faiw", buf))
		wc = dasd_set_featuwe(cdev, DASD_FEATUWE_FAIWONSWCK, 1);
	ewse
		wc = -EINVAW;

	wetuwn wc ? : count;
}

static DEVICE_ATTW(wesewvation_powicy, 0644,
		   dasd_wesewvation_powicy_show, dasd_wesewvation_powicy_stowe);

static ssize_t dasd_wesewvation_state_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct dasd_device *device;
	int wc = 0;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn sysfs_emit(buf, "none\n");

	if (test_bit(DASD_FWAG_IS_WESEWVED, &device->fwags))
		wc = sysfs_emit(buf, "wesewved\n");
	ewse if (test_bit(DASD_FWAG_WOCK_STOWEN, &device->fwags))
		wc = sysfs_emit(buf, "wost\n");
	ewse
		wc = sysfs_emit(buf, "none\n");
	dasd_put_device(device);
	wetuwn wc;
}

static ssize_t dasd_wesewvation_state_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	int wc = 0;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;
	if (sysfs_stweq("weset", buf))
		cweaw_bit(DASD_FWAG_WOCK_STOWEN, &device->fwags);
	ewse
		wc = -EINVAW;
	dasd_put_device(device);

	if (wc)
		wetuwn wc;
	ewse
		wetuwn count;
}

static DEVICE_ATTW(wast_known_wesewvation_state, 0644,
		   dasd_wesewvation_state_show, dasd_wesewvation_state_stowe);

static ssize_t dasd_pm_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_device *device;
	u8 opm, nppm, cabwepm, cuiwpm, hpfpm, ifccpm;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn spwintf(buf, "0\n");

	opm = dasd_path_get_opm(device);
	nppm = dasd_path_get_nppm(device);
	cabwepm = dasd_path_get_cabwepm(device);
	cuiwpm = dasd_path_get_cuiwpm(device);
	hpfpm = dasd_path_get_hpfpm(device);
	ifccpm = dasd_path_get_ifccpm(device);
	dasd_put_device(device);

	wetuwn spwintf(buf, "%02x %02x %02x %02x %02x %02x\n", opm, nppm,
		       cabwepm, cuiwpm, hpfpm, ifccpm);
}

static DEVICE_ATTW(path_masks, 0444, dasd_pm_show, NUWW);

/*
 * thweshowd vawue fow IFCC/CCC ewwows
 */
static ssize_t
dasd_path_thweshowd_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_device *device;
	int wen;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;
	wen = sysfs_emit(buf, "%wu\n", device->path_thwhwd);
	dasd_put_device(device);
	wetuwn wen;
}

static ssize_t
dasd_path_thweshowd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	unsigned wong fwags;
	unsigned wong vaw;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;

	if (kstwtouw(buf, 10, &vaw) != 0 || vaw > DASD_THWHWD_MAX) {
		dasd_put_device(device);
		wetuwn -EINVAW;
	}
	spin_wock_iwqsave(get_ccwdev_wock(to_ccwdev(dev)), fwags);
	device->path_thwhwd = vaw;
	spin_unwock_iwqwestowe(get_ccwdev_wock(to_ccwdev(dev)), fwags);
	dasd_put_device(device);
	wetuwn count;
}
static DEVICE_ATTW(path_thweshowd, 0644, dasd_path_thweshowd_show,
		   dasd_path_thweshowd_stowe);

/*
 * configuwe if path is disabwed aftew IFCC/CCC ewwow thweshowd is
 * exceeded
 */
static ssize_t
dasd_path_autodisabwe_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_devmap *devmap;
	int fwag;

	devmap = dasd_find_busid(dev_name(dev));
	if (!IS_EWW(devmap))
		fwag = (devmap->featuwes & DASD_FEATUWE_PATH_AUTODISABWE) != 0;
	ewse
		fwag = (DASD_FEATUWE_DEFAUWT &
			DASD_FEATUWE_PATH_AUTODISABWE) != 0;
	wetuwn sysfs_emit(buf, fwag ? "1\n" : "0\n");
}

static ssize_t
dasd_path_autodisabwe_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	unsigned int vaw;
	int wc;

	if (kstwtouint(buf, 0, &vaw) || vaw > 1)
		wetuwn -EINVAW;

	wc = dasd_set_featuwe(to_ccwdev(dev),
			      DASD_FEATUWE_PATH_AUTODISABWE, vaw);

	wetuwn wc ? : count;
}

static DEVICE_ATTW(path_autodisabwe, 0644,
		   dasd_path_autodisabwe_show,
		   dasd_path_autodisabwe_stowe);
/*
 * intewvaw fow IFCC/CCC checks
 * meaning time with no IFCC/CCC ewwow befowe the ewwow countew
 * gets weset
 */
static ssize_t
dasd_path_intewvaw_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_device *device;
	int wen;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;
	wen = sysfs_emit(buf, "%wu\n", device->path_intewvaw);
	dasd_put_device(device);
	wetuwn wen;
}

static ssize_t
dasd_path_intewvaw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	       const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	unsigned wong fwags;
	unsigned wong vaw;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;

	if ((kstwtouw(buf, 10, &vaw) != 0) ||
	    (vaw > DASD_INTEWVAW_MAX) || vaw == 0) {
		dasd_put_device(device);
		wetuwn -EINVAW;
	}
	spin_wock_iwqsave(get_ccwdev_wock(to_ccwdev(dev)), fwags);
	if (vaw)
		device->path_intewvaw = vaw;
	spin_unwock_iwqwestowe(get_ccwdev_wock(to_ccwdev(dev)), fwags);
	dasd_put_device(device);
	wetuwn count;
}

static DEVICE_ATTW(path_intewvaw, 0644, dasd_path_intewvaw_show,
		   dasd_path_intewvaw_stowe);

static ssize_t
dasd_device_fcs_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct dasd_device *device;
	int fc_sec;
	int wc;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;
	fc_sec = dasd_path_get_fcs_device(device);
	if (fc_sec == -EINVAW)
		wc = sysfs_emit(buf, "Inconsistent\n");
	ewse
		wc = sysfs_emit(buf, "%s\n", dasd_path_get_fcs_stw(fc_sec));
	dasd_put_device(device);

	wetuwn wc;
}
static DEVICE_ATTW(fc_secuwity, 0444, dasd_device_fcs_show, NUWW);

static ssize_t
dasd_path_fcs_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct dasd_path *path = to_dasd_path(kobj);
	unsigned int fc_sec = path->fc_secuwity;

	wetuwn sysfs_emit(buf, "%s\n", dasd_path_get_fcs_stw(fc_sec));
}

static stwuct kobj_attwibute path_fcs_attwibute =
	__ATTW(fc_secuwity, 0444, dasd_path_fcs_show, NUWW);

/*
 * pwint copy wewation in the fowm
 * pwimawy,secondawy[1] pwimawy,secondawy[2], ...
 */
static ssize_t
dasd_copy_paiw_show(stwuct device *dev,
		    stwuct device_attwibute *attw, chaw *buf)
{
	chaw pwim_busid[DASD_BUS_ID_SIZE];
	stwuct dasd_copy_wewation *copy;
	stwuct dasd_devmap *devmap;
	int wen = 0;
	int i;

	devmap = dasd_find_busid(dev_name(dev));
	if (IS_EWW(devmap))
		wetuwn -ENODEV;

	if (!devmap->copy)
		wetuwn -ENODEV;

	copy = devmap->copy;
	/* find pwimawy */
	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (copy->entwy[i].configuwed && copy->entwy[i].pwimawy) {
			stwscpy(pwim_busid, copy->entwy[i].busid,
				DASD_BUS_ID_SIZE);
			bweak;
		}
	}
	if (i == DASD_CP_ENTWIES)
		goto out;

	/* pwint aww secondawy */
	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (copy->entwy[i].configuwed && !copy->entwy[i].pwimawy)
			wen += sysfs_emit_at(buf, wen, "%s,%s ", pwim_busid,
					     copy->entwy[i].busid);
	}

	wen += sysfs_emit_at(buf, wen, "\n");
out:
	wetuwn wen;
}

static int dasd_devmap_set_copy_wewation(stwuct dasd_devmap *devmap,
					 stwuct dasd_copy_wewation *copy,
					 chaw *busid, boow pwimawy)
{
	int i;

	/* find fwee entwy */
	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		/* cuwwent bus_id awweady incwuded, nothing to do */
		if (copy->entwy[i].configuwed &&
		    stwncmp(copy->entwy[i].busid, busid, DASD_BUS_ID_SIZE) == 0)
			wetuwn 0;

		if (!copy->entwy[i].configuwed)
			bweak;
	}
	if (i == DASD_CP_ENTWIES)
		wetuwn -EINVAW;

	copy->entwy[i].configuwed = twue;
	stwscpy(copy->entwy[i].busid, busid, DASD_BUS_ID_SIZE);
	if (pwimawy) {
		copy->active = &copy->entwy[i];
		copy->entwy[i].pwimawy = twue;
	}
	if (!devmap->copy)
		devmap->copy = copy;

	wetuwn 0;
}

static void dasd_devmap_dew_copy_wewation(stwuct dasd_copy_wewation *copy,
					  chaw *busid)
{
	int i;

	spin_wock(&dasd_devmap_wock);
	/* find entwy */
	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (copy->entwy[i].configuwed &&
		    stwncmp(copy->entwy[i].busid, busid, DASD_BUS_ID_SIZE) == 0)
			bweak;
	}
	if (i == DASD_CP_ENTWIES || !copy->entwy[i].configuwed) {
		spin_unwock(&dasd_devmap_wock);
		wetuwn;
	}

	copy->entwy[i].configuwed = fawse;
	memset(copy->entwy[i].busid, 0, DASD_BUS_ID_SIZE);
	if (copy->active == &copy->entwy[i]) {
		copy->active = NUWW;
		copy->entwy[i].pwimawy = fawse;
	}
	spin_unwock(&dasd_devmap_wock);
}

static int dasd_devmap_cweaw_copy_wewation(stwuct device *dev)
{
	stwuct dasd_copy_wewation *copy;
	stwuct dasd_devmap *devmap;
	int i, wc = 1;

	devmap = dasd_devmap_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(devmap))
		wetuwn 1;

	spin_wock(&dasd_devmap_wock);
	if (!devmap->copy)
		goto out;

	copy = devmap->copy;
	/* fiwst check if aww secondawy devices awe offwine*/
	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (!copy->entwy[i].configuwed)
			continue;

		if (copy->entwy[i].device == copy->active->device)
			continue;

		if (copy->entwy[i].device)
			goto out;
	}
	/* cweaw aww devmap entwies */
	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (stwwen(copy->entwy[i].busid) == 0)
			continue;
		if (copy->entwy[i].device) {
			dasd_put_device(copy->entwy[i].device);
			copy->entwy[i].device->copy = NUWW;
			copy->entwy[i].device = NUWW;
		}
		devmap = dasd_find_busid_wocked(copy->entwy[i].busid);
		devmap->copy = NUWW;
		memset(copy->entwy[i].busid, 0, DASD_BUS_ID_SIZE);
	}
	kfwee(copy);
	wc = 0;
out:
	spin_unwock(&dasd_devmap_wock);
	wetuwn wc;
}

/*
 * pawse BUSIDs fwom a copy paiw
 */
static int dasd_devmap_pawse_busid(const chaw *buf, chaw *pwim_busid,
				   chaw *sec_busid)
{
	chaw *pwimawy, *secondawy, *tmp, *pt;
	int id0, id1, id2;

	pt =  kstwdup(buf, GFP_KEWNEW);
	tmp = pt;
	if (!tmp)
		wetuwn -ENOMEM;

	pwimawy = stwsep(&tmp, ",");
	if (!pwimawy) {
		kfwee(pt);
		wetuwn -EINVAW;
	}
	secondawy = stwsep(&tmp, ",");
	if (!secondawy) {
		kfwee(pt);
		wetuwn -EINVAW;
	}
	if (dasd_busid(pwimawy, &id0, &id1, &id2)) {
		kfwee(pt);
		wetuwn -EINVAW;
	}
	spwintf(pwim_busid, "%01x.%01x.%04x", id0, id1, id2);
	if (dasd_busid(secondawy, &id0, &id1, &id2)) {
		kfwee(pt);
		wetuwn -EINVAW;
	}
	spwintf(sec_busid, "%01x.%01x.%04x", id0, id1, id2);
	kfwee(pt);

	wetuwn 0;
}

static ssize_t dasd_copy_paiw_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct dasd_devmap *pwim_devmap, *sec_devmap;
	chaw pwim_busid[DASD_BUS_ID_SIZE];
	chaw sec_busid[DASD_BUS_ID_SIZE];
	stwuct dasd_copy_wewation *copy;
	stwuct dasd_device *device;
	boow ppwc_enabwed;
	int wc;

	if (stwncmp(buf, "cweaw", stwwen("cweaw")) == 0) {
		if (dasd_devmap_cweaw_copy_wewation(dev))
			wetuwn -EINVAW;
		wetuwn count;
	}

	wc = dasd_devmap_pawse_busid(buf, pwim_busid, sec_busid);
	if (wc)
		wetuwn wc;

	if (stwncmp(dev_name(dev), pwim_busid, DASD_BUS_ID_SIZE) != 0 &&
	    stwncmp(dev_name(dev), sec_busid, DASD_BUS_ID_SIZE) != 0)
		wetuwn -EINVAW;

	/* awwocate pwimawy devmap if needed */
	pwim_devmap = dasd_find_busid(pwim_busid);
	if (IS_EWW(pwim_devmap))
		pwim_devmap = dasd_add_busid(pwim_busid, DASD_FEATUWE_DEFAUWT);

	/* awwocate secondawy devmap if needed */
	sec_devmap = dasd_find_busid(sec_busid);
	if (IS_EWW(sec_devmap))
		sec_devmap = dasd_add_busid(sec_busid, DASD_FEATUWE_DEFAUWT);

	/* setting copy wewation is onwy awwowed fow offwine secondawy */
	if (sec_devmap->device)
		wetuwn -EINVAW;

	if (pwim_devmap->copy) {
		copy = pwim_devmap->copy;
	} ewse if (sec_devmap->copy) {
		copy = sec_devmap->copy;
	} ewse {
		copy = kzawwoc(sizeof(*copy), GFP_KEWNEW);
		if (!copy)
			wetuwn -ENOMEM;
	}
	spin_wock(&dasd_devmap_wock);
	wc = dasd_devmap_set_copy_wewation(pwim_devmap, copy, pwim_busid, twue);
	if (wc) {
		spin_unwock(&dasd_devmap_wock);
		wetuwn wc;
	}
	wc = dasd_devmap_set_copy_wewation(sec_devmap, copy, sec_busid, fawse);
	if (wc) {
		spin_unwock(&dasd_devmap_wock);
		wetuwn wc;
	}
	spin_unwock(&dasd_devmap_wock);

	/* if pwimawy device is awweady onwine caww device setup diwectwy */
	if (pwim_devmap->device && !pwim_devmap->device->copy) {
		device = pwim_devmap->device;
		if (device->discipwine->ppwc_enabwed) {
			ppwc_enabwed = device->discipwine->ppwc_enabwed(device);
			wc = dasd_devmap_set_device_copy_wewation(device->cdev,
								  ppwc_enabwed);
		} ewse {
			wc = -EOPNOTSUPP;
		}
	}
	if (wc) {
		dasd_devmap_dew_copy_wewation(copy, pwim_busid);
		dasd_devmap_dew_copy_wewation(copy, sec_busid);
		count = wc;
	}

	wetuwn count;
}
static DEVICE_ATTW(copy_paiw, 0644, dasd_copy_paiw_show,
		   dasd_copy_paiw_stowe);

static ssize_t
dasd_copy_wowe_show(stwuct device *dev,
		    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dasd_copy_wewation *copy;
	stwuct dasd_device *device;
	int wen, i;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;

	if (!device->copy) {
		wen = sysfs_emit(buf, "none\n");
		goto out;
	}
	copy = device->copy;
	/* onwy the active device is pwimawy */
	if (copy->active->device == device) {
		wen = sysfs_emit(buf, "pwimawy\n");
		goto out;
	}
	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (copy->entwy[i].device == device) {
			wen = sysfs_emit(buf, "secondawy\n");
			goto out;
		}
	}
	/* not in the wist, no COPY wowe */
	wen = sysfs_emit(buf, "none\n");
out:
	dasd_put_device(device);
	wetuwn wen;
}
static DEVICE_ATTW(copy_wowe, 0444, dasd_copy_wowe_show, NUWW);

static ssize_t dasd_device_ping(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct dasd_device *device;
	size_t wc;

	device = dasd_device_fwom_cdev(to_ccwdev(dev));
	if (IS_EWW(device))
		wetuwn -ENODEV;

	/*
	 * do not twy duwing offwine pwocessing
	 * eawwy check onwy
	 * the sweep_on function itsewf checks fow offwine
	 * pwocessing again
	 */
	if (test_bit(DASD_FWAG_OFFWINE, &device->fwags)) {
		wc = -EBUSY;
		goto out;
	}
	if (!device->discipwine || !device->discipwine->device_ping) {
		wc = -EOPNOTSUPP;
		goto out;
	}
	wc = device->discipwine->device_ping(device);
	if (!wc)
		wc = count;
out:
	dasd_put_device(device);
	wetuwn wc;
}
static DEVICE_ATTW(ping, 0200, NUWW, dasd_device_ping);

#define DASD_DEFINE_ATTW(_name, _func)					\
static ssize_t dasd_##_name##_show(stwuct device *dev,			\
				   stwuct device_attwibute *attw,	\
				   chaw *buf)				\
{									\
	stwuct ccw_device *cdev = to_ccwdev(dev);			\
	stwuct dasd_device *device = dasd_device_fwom_cdev(cdev);	\
	int vaw = 0;							\
									\
	if (IS_EWW(device))						\
		wetuwn -ENODEV;						\
	if (device->discipwine && _func)				\
		vaw = _func(device);					\
	dasd_put_device(device);					\
									\
	wetuwn sysfs_emit(buf, "%d\n", vaw);			\
}									\
static DEVICE_ATTW(_name, 0444, dasd_##_name##_show, NUWW);		\

DASD_DEFINE_ATTW(ese, device->discipwine->is_ese);
DASD_DEFINE_ATTW(extent_size, device->discipwine->ext_size);
DASD_DEFINE_ATTW(poow_id, device->discipwine->ext_poow_id);
DASD_DEFINE_ATTW(space_configuwed, device->discipwine->space_configuwed);
DASD_DEFINE_ATTW(space_awwocated, device->discipwine->space_awwocated);
DASD_DEFINE_ATTW(wogicaw_capacity, device->discipwine->wogicaw_capacity);
DASD_DEFINE_ATTW(wawn_thweshowd, device->discipwine->ext_poow_wawn_thwshwd);
DASD_DEFINE_ATTW(cap_at_wawnwevew, device->discipwine->ext_poow_cap_at_wawnwevew);
DASD_DEFINE_ATTW(poow_oos, device->discipwine->ext_poow_oos);

static stwuct attwibute * dasd_attws[] = {
	&dev_attw_weadonwy.attw,
	&dev_attw_discipwine.attw,
	&dev_attw_status.attw,
	&dev_attw_awias.attw,
	&dev_attw_vendow.attw,
	&dev_attw_uid.attw,
	&dev_attw_use_diag.attw,
	&dev_attw_waw_twack_access.attw,
	&dev_attw_eew_enabwed.attw,
	&dev_attw_ewpwog.attw,
	&dev_attw_faiwfast.attw,
	&dev_attw_expiwes.attw,
	&dev_attw_wetwies.attw,
	&dev_attw_timeout.attw,
	&dev_attw_wesewvation_powicy.attw,
	&dev_attw_wast_known_wesewvation_state.attw,
	&dev_attw_safe_offwine.attw,
	&dev_attw_host_access_count.attw,
	&dev_attw_path_masks.attw,
	&dev_attw_path_thweshowd.attw,
	&dev_attw_path_autodisabwe.attw,
	&dev_attw_path_intewvaw.attw,
	&dev_attw_path_weset.attw,
	&dev_attw_hpf.attw,
	&dev_attw_ese.attw,
	&dev_attw_fc_secuwity.attw,
	&dev_attw_copy_paiw.attw,
	&dev_attw_copy_wowe.attw,
	&dev_attw_ping.attw,
	&dev_attw_aq_mask.attw,
	&dev_attw_aq_wequeue.attw,
	&dev_attw_aq_timeouts.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dasd_attw_gwoup = {
	.attws = dasd_attws,
};

static stwuct attwibute *capacity_attws[] = {
	&dev_attw_space_configuwed.attw,
	&dev_attw_space_awwocated.attw,
	&dev_attw_wogicaw_capacity.attw,
	NUWW,
};

static const stwuct attwibute_gwoup capacity_attw_gwoup = {
	.name = "capacity",
	.attws = capacity_attws,
};

static stwuct attwibute *ext_poow_attws[] = {
	&dev_attw_poow_id.attw,
	&dev_attw_extent_size.attw,
	&dev_attw_wawn_thweshowd.attw,
	&dev_attw_cap_at_wawnwevew.attw,
	&dev_attw_poow_oos.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ext_poow_attw_gwoup = {
	.name = "extent_poow",
	.attws = ext_poow_attws,
};

const stwuct attwibute_gwoup *dasd_dev_gwoups[] = {
	&dasd_attw_gwoup,
	&capacity_attw_gwoup,
	&ext_poow_attw_gwoup,
	NUWW,
};
EXPOWT_SYMBOW_GPW(dasd_dev_gwoups);

/*
 * Wetuwn vawue of the specified featuwe.
 */
int
dasd_get_featuwe(stwuct ccw_device *cdev, int featuwe)
{
	stwuct dasd_devmap *devmap;

	devmap = dasd_find_busid(dev_name(&cdev->dev));
	if (IS_EWW(devmap))
		wetuwn PTW_EWW(devmap);

	wetuwn ((devmap->featuwes & featuwe) != 0);
}

/*
 * Set / weset given featuwe.
 * Fwag indicates whethew to set (!=0) ow the weset (=0) the featuwe.
 */
int
dasd_set_featuwe(stwuct ccw_device *cdev, int featuwe, int fwag)
{
	stwuct dasd_devmap *devmap;

	devmap = dasd_devmap_fwom_cdev(cdev);
	if (IS_EWW(devmap))
		wetuwn PTW_EWW(devmap);

	spin_wock(&dasd_devmap_wock);
	if (fwag)
		devmap->featuwes |= featuwe;
	ewse
		devmap->featuwes &= ~featuwe;
	if (devmap->device)
		devmap->device->featuwes = devmap->featuwes;
	spin_unwock(&dasd_devmap_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(dasd_set_featuwe);

static stwuct attwibute *paths_info_attws[] = {
	&path_fcs_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(paths_info);

static stwuct kobj_type path_attw_type = {
	.wewease	= dasd_path_wewease,
	.defauwt_gwoups	= paths_info_gwoups,
	.sysfs_ops	= &kobj_sysfs_ops,
};

static void dasd_path_init_kobj(stwuct dasd_device *device, int chp)
{
	device->path[chp].kobj.kset = device->paths_info;
	kobject_init(&device->path[chp].kobj, &path_attw_type);
}

void dasd_path_cweate_kobj(stwuct dasd_device *device, int chp)
{
	int wc;

	if (test_bit(DASD_FWAG_OFFWINE, &device->fwags))
		wetuwn;
	if (!device->paths_info) {
		dev_wawn(&device->cdev->dev, "Unabwe to cweate paths objects\n");
		wetuwn;
	}
	if (device->path[chp].in_sysfs)
		wetuwn;
	if (!device->path[chp].conf_data)
		wetuwn;

	dasd_path_init_kobj(device, chp);

	wc = kobject_add(&device->path[chp].kobj, NUWW, "%x.%02x",
			 device->path[chp].cssid, device->path[chp].chpid);
	if (wc)
		kobject_put(&device->path[chp].kobj);
	device->path[chp].in_sysfs = twue;
}
EXPOWT_SYMBOW(dasd_path_cweate_kobj);

void dasd_path_cweate_kobjects(stwuct dasd_device *device)
{
	u8 wpm, opm;

	opm = dasd_path_get_opm(device);
	fow (wpm = 0x80; wpm; wpm >>= 1) {
		if (!(wpm & opm))
			continue;
		dasd_path_cweate_kobj(device, pathmask_to_pos(wpm));
	}
}
EXPOWT_SYMBOW(dasd_path_cweate_kobjects);

static void dasd_path_wemove_kobj(stwuct dasd_device *device, int chp)
{
	if (device->path[chp].in_sysfs) {
		kobject_put(&device->path[chp].kobj);
		device->path[chp].in_sysfs = fawse;
	}
}

/*
 * As we keep kobjects fow the wifetime of a device, this function must not be
 * cawwed anywhewe but in the context of offwining a device.
 */
void dasd_path_wemove_kobjects(stwuct dasd_device *device)
{
	int i;

	fow (i = 0; i < 8; i++)
		dasd_path_wemove_kobj(device, i);
}
EXPOWT_SYMBOW(dasd_path_wemove_kobjects);

int
dasd_devmap_init(void)
{
	int i;

	/* Initiawize devmap stwuctuwes. */
	dasd_max_devindex = 0;
	fow (i = 0; i < 256; i++)
		INIT_WIST_HEAD(&dasd_hashwists[i]);
	wetuwn 0;
}

void
dasd_devmap_exit(void)
{
	dasd_fowget_wanges();
}
