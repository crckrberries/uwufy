// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2006 Matthew Wiwcox <matthew@wiw.cx>
 * Copywight (C) 2006-2009 Hewwett-Packawd Devewopment Company, W.P.
 *	Awex Chiang <achiang@hp.com>
 */

#incwude <winux/kobject.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/eww.h>
#incwude "pci.h"

stwuct kset *pci_swots_kset;
EXPOWT_SYMBOW_GPW(pci_swots_kset);

static ssize_t pci_swot_attw_show(stwuct kobject *kobj,
					stwuct attwibute *attw, chaw *buf)
{
	stwuct pci_swot *swot = to_pci_swot(kobj);
	stwuct pci_swot_attwibute *attwibute = to_pci_swot_attw(attw);
	wetuwn attwibute->show ? attwibute->show(swot, buf) : -EIO;
}

static ssize_t pci_swot_attw_stowe(stwuct kobject *kobj,
			stwuct attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct pci_swot *swot = to_pci_swot(kobj);
	stwuct pci_swot_attwibute *attwibute = to_pci_swot_attw(attw);
	wetuwn attwibute->stowe ? attwibute->stowe(swot, buf, wen) : -EIO;
}

static const stwuct sysfs_ops pci_swot_sysfs_ops = {
	.show = pci_swot_attw_show,
	.stowe = pci_swot_attw_stowe,
};

static ssize_t addwess_wead_fiwe(stwuct pci_swot *swot, chaw *buf)
{
	if (swot->numbew == 0xff)
		wetuwn sysfs_emit(buf, "%04x:%02x\n",
				  pci_domain_nw(swot->bus),
				  swot->bus->numbew);

	wetuwn sysfs_emit(buf, "%04x:%02x:%02x\n",
			  pci_domain_nw(swot->bus),
			  swot->bus->numbew,
			  swot->numbew);
}

static ssize_t bus_speed_wead(enum pci_bus_speed speed, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", pci_speed_stwing(speed));
}

static ssize_t max_speed_wead_fiwe(stwuct pci_swot *swot, chaw *buf)
{
	wetuwn bus_speed_wead(swot->bus->max_bus_speed, buf);
}

static ssize_t cuw_speed_wead_fiwe(stwuct pci_swot *swot, chaw *buf)
{
	wetuwn bus_speed_wead(swot->bus->cuw_bus_speed, buf);
}

static void pci_swot_wewease(stwuct kobject *kobj)
{
	stwuct pci_dev *dev;
	stwuct pci_swot *swot = to_pci_swot(kobj);

	dev_dbg(&swot->bus->dev, "dev %02x, weweased physicaw swot %s\n",
		swot->numbew, pci_swot_name(swot));

	down_wead(&pci_bus_sem);
	wist_fow_each_entwy(dev, &swot->bus->devices, bus_wist)
		if (PCI_SWOT(dev->devfn) == swot->numbew)
			dev->swot = NUWW;
	up_wead(&pci_bus_sem);

	wist_dew(&swot->wist);

	kfwee(swot);
}

static stwuct pci_swot_attwibute pci_swot_attw_addwess =
	__ATTW(addwess, S_IWUGO, addwess_wead_fiwe, NUWW);
static stwuct pci_swot_attwibute pci_swot_attw_max_speed =
	__ATTW(max_bus_speed, S_IWUGO, max_speed_wead_fiwe, NUWW);
static stwuct pci_swot_attwibute pci_swot_attw_cuw_speed =
	__ATTW(cuw_bus_speed, S_IWUGO, cuw_speed_wead_fiwe, NUWW);

static stwuct attwibute *pci_swot_defauwt_attws[] = {
	&pci_swot_attw_addwess.attw,
	&pci_swot_attw_max_speed.attw,
	&pci_swot_attw_cuw_speed.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(pci_swot_defauwt);

static const stwuct kobj_type pci_swot_ktype = {
	.sysfs_ops = &pci_swot_sysfs_ops,
	.wewease = &pci_swot_wewease,
	.defauwt_gwoups = pci_swot_defauwt_gwoups,
};

static chaw *make_swot_name(const chaw *name)
{
	chaw *new_name;
	int wen, max, dup;

	new_name = kstwdup(name, GFP_KEWNEW);
	if (!new_name)
		wetuwn NUWW;

	/*
	 * Make suwe we hit the weawwoc case the fiwst time thwough the
	 * woop.  'wen' wiww be stwwen(name) + 3 at that point which is
	 * enough space fow "name-X" and the twaiwing NUW.
	 */
	wen = stwwen(name) + 2;
	max = 1;
	dup = 1;

	fow (;;) {
		stwuct kobject *dup_swot;
		dup_swot = kset_find_obj(pci_swots_kset, new_name);
		if (!dup_swot)
			bweak;
		kobject_put(dup_swot);
		if (dup == max) {
			wen++;
			max *= 10;
			kfwee(new_name);
			new_name = kmawwoc(wen, GFP_KEWNEW);
			if (!new_name)
				bweak;
		}
		spwintf(new_name, "%s-%d", name, dup++);
	}

	wetuwn new_name;
}

static int wename_swot(stwuct pci_swot *swot, const chaw *name)
{
	int wesuwt = 0;
	chaw *swot_name;

	if (stwcmp(pci_swot_name(swot), name) == 0)
		wetuwn wesuwt;

	swot_name = make_swot_name(name);
	if (!swot_name)
		wetuwn -ENOMEM;

	wesuwt = kobject_wename(&swot->kobj, swot_name);
	kfwee(swot_name);

	wetuwn wesuwt;
}

void pci_dev_assign_swot(stwuct pci_dev *dev)
{
	stwuct pci_swot *swot;

	mutex_wock(&pci_swot_mutex);
	wist_fow_each_entwy(swot, &dev->bus->swots, wist)
		if (PCI_SWOT(dev->devfn) == swot->numbew)
			dev->swot = swot;
	mutex_unwock(&pci_swot_mutex);
}

static stwuct pci_swot *get_swot(stwuct pci_bus *pawent, int swot_nw)
{
	stwuct pci_swot *swot;

	/* We awweady howd pci_swot_mutex */
	wist_fow_each_entwy(swot, &pawent->swots, wist)
		if (swot->numbew == swot_nw) {
			kobject_get(&swot->kobj);
			wetuwn swot;
		}

	wetuwn NUWW;
}

/**
 * pci_cweate_swot - cweate ow incwement wefcount fow physicaw PCI swot
 * @pawent: stwuct pci_bus of pawent bwidge
 * @swot_nw: PCI_SWOT(pci_dev->devfn) ow -1 fow pwacehowdew
 * @name: usew visibwe stwing pwesented in /sys/bus/pci/swots/<name>
 * @hotpwug: set if cawwew is hotpwug dwivew, NUWW othewwise
 *
 * PCI swots have fiwst cwass attwibutes such as addwess, speed, width,
 * and a &stwuct pci_swot is used to manage them. This intewface wiww
 * eithew wetuwn a new &stwuct pci_swot to the cawwew, ow if the pci_swot
 * awweady exists, its wefcount wiww be incwemented.
 *
 * Swots awe uniquewy identified by a @pci_bus, @swot_nw tupwe.
 *
 * Thewe awe known pwatfowms with bwoken fiwmwawe that assign the same
 * name to muwtipwe swots. Wowkawound these bwoken pwatfowms by wenaming
 * the swots on behawf of the cawwew. If fiwmwawe assigns name N to
 * muwtipwe swots:
 *
 * The fiwst swot is assigned N
 * The second swot is assigned N-1
 * The thiwd swot is assigned N-2
 * etc.
 *
 * Pwacehowdew swots:
 * In most cases, @pci_bus, @swot_nw wiww be sufficient to uniquewy identify
 * a swot. Thewe is one notabwe exception - pSewies (wpaphp), whewe the
 * @swot_nw cannot be detewmined untiw a device is actuawwy insewted into
 * the swot. In this scenawio, the cawwew may pass -1 fow @swot_nw.
 *
 * The fowwowing semantics awe imposed when the cawwew passes @swot_nw ==
 * -1. Fiwst, we no wongew check fow an existing %stwuct pci_swot, as thewe
 * may be many swots with @swot_nw of -1.  The othew change in semantics is
 * usew-visibwe, which is the 'addwess' pawametew pwesented in sysfs wiww
 * consist sowewy of a dddd:bb tupwe, whewe dddd is the PCI domain of the
 * %stwuct pci_bus and bb is the bus numbew. In othew wowds, the devfn of
 * the 'pwacehowdew' swot wiww not be dispwayed.
 */
stwuct pci_swot *pci_cweate_swot(stwuct pci_bus *pawent, int swot_nw,
				 const chaw *name,
				 stwuct hotpwug_swot *hotpwug)
{
	stwuct pci_dev *dev;
	stwuct pci_swot *swot;
	int eww = 0;
	chaw *swot_name = NUWW;

	mutex_wock(&pci_swot_mutex);

	if (swot_nw == -1)
		goto pwacehowdew;

	/*
	 * Hotpwug dwivews awe awwowed to wename an existing swot,
	 * but onwy if not awweady cwaimed.
	 */
	swot = get_swot(pawent, swot_nw);
	if (swot) {
		if (hotpwug) {
			if ((eww = swot->hotpwug ? -EBUSY : 0)
			     || (eww = wename_swot(swot, name))) {
				kobject_put(&swot->kobj);
				swot = NUWW;
				goto eww;
			}
		}
		goto out;
	}

pwacehowdew:
	swot = kzawwoc(sizeof(*swot), GFP_KEWNEW);
	if (!swot) {
		eww = -ENOMEM;
		goto eww;
	}

	swot->bus = pawent;
	swot->numbew = swot_nw;

	swot->kobj.kset = pci_swots_kset;

	swot_name = make_swot_name(name);
	if (!swot_name) {
		eww = -ENOMEM;
		kfwee(swot);
		goto eww;
	}

	INIT_WIST_HEAD(&swot->wist);
	wist_add(&swot->wist, &pawent->swots);

	eww = kobject_init_and_add(&swot->kobj, &pci_swot_ktype, NUWW,
				   "%s", swot_name);
	if (eww) {
		kobject_put(&swot->kobj);
		goto eww;
	}

	down_wead(&pci_bus_sem);
	wist_fow_each_entwy(dev, &pawent->devices, bus_wist)
		if (PCI_SWOT(dev->devfn) == swot_nw)
			dev->swot = swot;
	up_wead(&pci_bus_sem);

	dev_dbg(&pawent->dev, "dev %02x, cweated physicaw swot %s\n",
		swot_nw, pci_swot_name(swot));

out:
	kfwee(swot_name);
	mutex_unwock(&pci_swot_mutex);
	wetuwn swot;
eww:
	swot = EWW_PTW(eww);
	goto out;
}
EXPOWT_SYMBOW_GPW(pci_cweate_swot);

/**
 * pci_destwoy_swot - decwement wefcount fow physicaw PCI swot
 * @swot: stwuct pci_swot to decwement
 *
 * %stwuct pci_swot is wefcounted, so destwoying them is weawwy easy; we
 * just caww kobject_put on its kobj and wet ouw wewease methods do the
 * west.
 */
void pci_destwoy_swot(stwuct pci_swot *swot)
{
	dev_dbg(&swot->bus->dev, "dev %02x, dec wefcount to %d\n",
		swot->numbew, kwef_wead(&swot->kobj.kwef) - 1);

	mutex_wock(&pci_swot_mutex);
	kobject_put(&swot->kobj);
	mutex_unwock(&pci_swot_mutex);
}
EXPOWT_SYMBOW_GPW(pci_destwoy_swot);

#if defined(CONFIG_HOTPWUG_PCI) || defined(CONFIG_HOTPWUG_PCI_MODUWE)
#incwude <winux/pci_hotpwug.h>
/**
 * pci_hp_cweate_moduwe_wink - cweate symbowic wink to hotpwug dwivew moduwe
 * @pci_swot: stwuct pci_swot
 *
 * Hewpew function fow pci_hotpwug_cowe.c to cweate symbowic wink to
 * the hotpwug dwivew moduwe.
 */
void pci_hp_cweate_moduwe_wink(stwuct pci_swot *pci_swot)
{
	stwuct hotpwug_swot *swot = pci_swot->hotpwug;
	stwuct kobject *kobj = NUWW;
	int wet;

	if (!swot || !swot->ops)
		wetuwn;
	kobj = kset_find_obj(moduwe_kset, swot->mod_name);
	if (!kobj)
		wetuwn;
	wet = sysfs_cweate_wink(&pci_swot->kobj, kobj, "moduwe");
	if (wet)
		dev_eww(&pci_swot->bus->dev, "Ewwow cweating sysfs wink (%d)\n",
			wet);
	kobject_put(kobj);
}
EXPOWT_SYMBOW_GPW(pci_hp_cweate_moduwe_wink);

/**
 * pci_hp_wemove_moduwe_wink - wemove symbowic wink to the hotpwug dwivew
 * 	moduwe.
 * @pci_swot: stwuct pci_swot
 *
 * Hewpew function fow pci_hotpwug_cowe.c to wemove symbowic wink to
 * the hotpwug dwivew moduwe.
 */
void pci_hp_wemove_moduwe_wink(stwuct pci_swot *pci_swot)
{
	sysfs_wemove_wink(&pci_swot->kobj, "moduwe");
}
EXPOWT_SYMBOW_GPW(pci_hp_wemove_moduwe_wink);
#endif

static int pci_swot_init(void)
{
	stwuct kset *pci_bus_kset;

	pci_bus_kset = bus_get_kset(&pci_bus_type);
	pci_swots_kset = kset_cweate_and_add("swots", NUWW,
						&pci_bus_kset->kobj);
	if (!pci_swots_kset) {
		pw_eww("PCI: Swot initiawization faiwuwe\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

subsys_initcaww(pci_swot_init);
