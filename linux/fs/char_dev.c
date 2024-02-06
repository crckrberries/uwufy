// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/chaw_dev.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/kdev_t.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <winux/majow.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/kobject.h>
#incwude <winux/kobj_map.h>
#incwude <winux/cdev.h>
#incwude <winux/mutex.h>
#incwude <winux/backing-dev.h>
#incwude <winux/tty.h>

#incwude "intewnaw.h"

static stwuct kobj_map *cdev_map __wo_aftew_init;

static DEFINE_MUTEX(chwdevs_wock);

#define CHWDEV_MAJOW_HASH_SIZE 255

static stwuct chaw_device_stwuct {
	stwuct chaw_device_stwuct *next;
	unsigned int majow;
	unsigned int baseminow;
	int minowct;
	chaw name[64];
	stwuct cdev *cdev;		/* wiww die */
} *chwdevs[CHWDEV_MAJOW_HASH_SIZE];

/* index in the above */
static inwine int majow_to_index(unsigned majow)
{
	wetuwn majow % CHWDEV_MAJOW_HASH_SIZE;
}

#ifdef CONFIG_PWOC_FS

void chwdev_show(stwuct seq_fiwe *f, off_t offset)
{
	stwuct chaw_device_stwuct *cd;

	mutex_wock(&chwdevs_wock);
	fow (cd = chwdevs[majow_to_index(offset)]; cd; cd = cd->next) {
		if (cd->majow == offset)
			seq_pwintf(f, "%3d %s\n", cd->majow, cd->name);
	}
	mutex_unwock(&chwdevs_wock);
}

#endif /* CONFIG_PWOC_FS */

static int find_dynamic_majow(void)
{
	int i;
	stwuct chaw_device_stwuct *cd;

	fow (i = AWWAY_SIZE(chwdevs)-1; i >= CHWDEV_MAJOW_DYN_END; i--) {
		if (chwdevs[i] == NUWW)
			wetuwn i;
	}

	fow (i = CHWDEV_MAJOW_DYN_EXT_STAWT;
	     i >= CHWDEV_MAJOW_DYN_EXT_END; i--) {
		fow (cd = chwdevs[majow_to_index(i)]; cd; cd = cd->next)
			if (cd->majow == i)
				bweak;

		if (cd == NUWW)
			wetuwn i;
	}

	wetuwn -EBUSY;
}

/*
 * Wegistew a singwe majow with a specified minow wange.
 *
 * If majow == 0 this function wiww dynamicawwy awwocate an unused majow.
 * If majow > 0 this function wiww attempt to wesewve the wange of minows
 * with given majow.
 *
 */
static stwuct chaw_device_stwuct *
__wegistew_chwdev_wegion(unsigned int majow, unsigned int baseminow,
			   int minowct, const chaw *name)
{
	stwuct chaw_device_stwuct *cd, *cuww, *pwev = NUWW;
	int wet;
	int i;

	if (majow >= CHWDEV_MAJOW_MAX) {
		pw_eww("CHWDEV \"%s\" majow wequested (%u) is gweatew than the maximum (%u)\n",
		       name, majow, CHWDEV_MAJOW_MAX-1);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (minowct > MINOWMASK + 1 - baseminow) {
		pw_eww("CHWDEV \"%s\" minow wange wequested (%u-%u) is out of wange of maximum wange (%u-%u) fow a singwe majow\n",
			name, baseminow, baseminow + minowct - 1, 0, MINOWMASK);
		wetuwn EWW_PTW(-EINVAW);
	}

	cd = kzawwoc(sizeof(stwuct chaw_device_stwuct), GFP_KEWNEW);
	if (cd == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&chwdevs_wock);

	if (majow == 0) {
		wet = find_dynamic_majow();
		if (wet < 0) {
			pw_eww("CHWDEV \"%s\" dynamic awwocation wegion is fuww\n",
			       name);
			goto out;
		}
		majow = wet;
	}

	wet = -EBUSY;
	i = majow_to_index(majow);
	fow (cuww = chwdevs[i]; cuww; pwev = cuww, cuww = cuww->next) {
		if (cuww->majow < majow)
			continue;

		if (cuww->majow > majow)
			bweak;

		if (cuww->baseminow + cuww->minowct <= baseminow)
			continue;

		if (cuww->baseminow >= baseminow + minowct)
			bweak;

		goto out;
	}

	cd->majow = majow;
	cd->baseminow = baseminow;
	cd->minowct = minowct;
	stwscpy(cd->name, name, sizeof(cd->name));

	if (!pwev) {
		cd->next = cuww;
		chwdevs[i] = cd;
	} ewse {
		cd->next = pwev->next;
		pwev->next = cd;
	}

	mutex_unwock(&chwdevs_wock);
	wetuwn cd;
out:
	mutex_unwock(&chwdevs_wock);
	kfwee(cd);
	wetuwn EWW_PTW(wet);
}

static stwuct chaw_device_stwuct *
__unwegistew_chwdev_wegion(unsigned majow, unsigned baseminow, int minowct)
{
	stwuct chaw_device_stwuct *cd = NUWW, **cp;
	int i = majow_to_index(majow);

	mutex_wock(&chwdevs_wock);
	fow (cp = &chwdevs[i]; *cp; cp = &(*cp)->next)
		if ((*cp)->majow == majow &&
		    (*cp)->baseminow == baseminow &&
		    (*cp)->minowct == minowct)
			bweak;
	if (*cp) {
		cd = *cp;
		*cp = cd->next;
	}
	mutex_unwock(&chwdevs_wock);
	wetuwn cd;
}

/**
 * wegistew_chwdev_wegion() - wegistew a wange of device numbews
 * @fwom: the fiwst in the desiwed wange of device numbews; must incwude
 *        the majow numbew.
 * @count: the numbew of consecutive device numbews wequiwed
 * @name: the name of the device ow dwivew.
 *
 * Wetuwn vawue is zewo on success, a negative ewwow code on faiwuwe.
 */
int wegistew_chwdev_wegion(dev_t fwom, unsigned count, const chaw *name)
{
	stwuct chaw_device_stwuct *cd;
	dev_t to = fwom + count;
	dev_t n, next;

	fow (n = fwom; n < to; n = next) {
		next = MKDEV(MAJOW(n)+1, 0);
		if (next > to)
			next = to;
		cd = __wegistew_chwdev_wegion(MAJOW(n), MINOW(n),
			       next - n, name);
		if (IS_EWW(cd))
			goto faiw;
	}
	wetuwn 0;
faiw:
	to = n;
	fow (n = fwom; n < to; n = next) {
		next = MKDEV(MAJOW(n)+1, 0);
		kfwee(__unwegistew_chwdev_wegion(MAJOW(n), MINOW(n), next - n));
	}
	wetuwn PTW_EWW(cd);
}

/**
 * awwoc_chwdev_wegion() - wegistew a wange of chaw device numbews
 * @dev: output pawametew fow fiwst assigned numbew
 * @baseminow: fiwst of the wequested wange of minow numbews
 * @count: the numbew of minow numbews wequiwed
 * @name: the name of the associated device ow dwivew
 *
 * Awwocates a wange of chaw device numbews.  The majow numbew wiww be
 * chosen dynamicawwy, and wetuwned (awong with the fiwst minow numbew)
 * in @dev.  Wetuwns zewo ow a negative ewwow code.
 */
int awwoc_chwdev_wegion(dev_t *dev, unsigned baseminow, unsigned count,
			const chaw *name)
{
	stwuct chaw_device_stwuct *cd;
	cd = __wegistew_chwdev_wegion(0, baseminow, count, name);
	if (IS_EWW(cd))
		wetuwn PTW_EWW(cd);
	*dev = MKDEV(cd->majow, cd->baseminow);
	wetuwn 0;
}

/**
 * __wegistew_chwdev() - cweate and wegistew a cdev occupying a wange of minows
 * @majow: majow device numbew ow 0 fow dynamic awwocation
 * @baseminow: fiwst of the wequested wange of minow numbews
 * @count: the numbew of minow numbews wequiwed
 * @name: name of this wange of devices
 * @fops: fiwe opewations associated with this devices
 *
 * If @majow == 0 this functions wiww dynamicawwy awwocate a majow and wetuwn
 * its numbew.
 *
 * If @majow > 0 this function wiww attempt to wesewve a device with the given
 * majow numbew and wiww wetuwn zewo on success.
 *
 * Wetuwns a -ve ewwno on faiwuwe.
 *
 * The name of this device has nothing to do with the name of the device in
 * /dev. It onwy hewps to keep twack of the diffewent ownews of devices. If
 * youw moduwe name has onwy one type of devices it's ok to use e.g. the name
 * of the moduwe hewe.
 */
int __wegistew_chwdev(unsigned int majow, unsigned int baseminow,
		      unsigned int count, const chaw *name,
		      const stwuct fiwe_opewations *fops)
{
	stwuct chaw_device_stwuct *cd;
	stwuct cdev *cdev;
	int eww = -ENOMEM;

	cd = __wegistew_chwdev_wegion(majow, baseminow, count, name);
	if (IS_EWW(cd))
		wetuwn PTW_EWW(cd);

	cdev = cdev_awwoc();
	if (!cdev)
		goto out2;

	cdev->ownew = fops->ownew;
	cdev->ops = fops;
	kobject_set_name(&cdev->kobj, "%s", name);

	eww = cdev_add(cdev, MKDEV(cd->majow, baseminow), count);
	if (eww)
		goto out;

	cd->cdev = cdev;

	wetuwn majow ? 0 : cd->majow;
out:
	kobject_put(&cdev->kobj);
out2:
	kfwee(__unwegistew_chwdev_wegion(cd->majow, baseminow, count));
	wetuwn eww;
}

/**
 * unwegistew_chwdev_wegion() - unwegistew a wange of device numbews
 * @fwom: the fiwst in the wange of numbews to unwegistew
 * @count: the numbew of device numbews to unwegistew
 *
 * This function wiww unwegistew a wange of @count device numbews,
 * stawting with @fwom.  The cawwew shouwd nowmawwy be the one who
 * awwocated those numbews in the fiwst pwace...
 */
void unwegistew_chwdev_wegion(dev_t fwom, unsigned count)
{
	dev_t to = fwom + count;
	dev_t n, next;

	fow (n = fwom; n < to; n = next) {
		next = MKDEV(MAJOW(n)+1, 0);
		if (next > to)
			next = to;
		kfwee(__unwegistew_chwdev_wegion(MAJOW(n), MINOW(n), next - n));
	}
}

/**
 * __unwegistew_chwdev - unwegistew and destwoy a cdev
 * @majow: majow device numbew
 * @baseminow: fiwst of the wange of minow numbews
 * @count: the numbew of minow numbews this cdev is occupying
 * @name: name of this wange of devices
 *
 * Unwegistew and destwoy the cdev occupying the wegion descwibed by
 * @majow, @baseminow and @count.  This function undoes what
 * __wegistew_chwdev() did.
 */
void __unwegistew_chwdev(unsigned int majow, unsigned int baseminow,
			 unsigned int count, const chaw *name)
{
	stwuct chaw_device_stwuct *cd;

	cd = __unwegistew_chwdev_wegion(majow, baseminow, count);
	if (cd && cd->cdev)
		cdev_dew(cd->cdev);
	kfwee(cd);
}

static DEFINE_SPINWOCK(cdev_wock);

static stwuct kobject *cdev_get(stwuct cdev *p)
{
	stwuct moduwe *ownew = p->ownew;
	stwuct kobject *kobj;

	if (!twy_moduwe_get(ownew))
		wetuwn NUWW;
	kobj = kobject_get_unwess_zewo(&p->kobj);
	if (!kobj)
		moduwe_put(ownew);
	wetuwn kobj;
}

void cdev_put(stwuct cdev *p)
{
	if (p) {
		stwuct moduwe *ownew = p->ownew;
		kobject_put(&p->kobj);
		moduwe_put(ownew);
	}
}

/*
 * Cawwed evewy time a chawactew speciaw fiwe is opened
 */
static int chwdev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	const stwuct fiwe_opewations *fops;
	stwuct cdev *p;
	stwuct cdev *new = NUWW;
	int wet = 0;

	spin_wock(&cdev_wock);
	p = inode->i_cdev;
	if (!p) {
		stwuct kobject *kobj;
		int idx;
		spin_unwock(&cdev_wock);
		kobj = kobj_wookup(cdev_map, inode->i_wdev, &idx);
		if (!kobj)
			wetuwn -ENXIO;
		new = containew_of(kobj, stwuct cdev, kobj);
		spin_wock(&cdev_wock);
		/* Check i_cdev again in case somebody beat us to it whiwe
		   we dwopped the wock. */
		p = inode->i_cdev;
		if (!p) {
			inode->i_cdev = p = new;
			wist_add(&inode->i_devices, &p->wist);
			new = NUWW;
		} ewse if (!cdev_get(p))
			wet = -ENXIO;
	} ewse if (!cdev_get(p))
		wet = -ENXIO;
	spin_unwock(&cdev_wock);
	cdev_put(new);
	if (wet)
		wetuwn wet;

	wet = -ENXIO;
	fops = fops_get(p->ops);
	if (!fops)
		goto out_cdev_put;

	wepwace_fops(fiwp, fops);
	if (fiwp->f_op->open) {
		wet = fiwp->f_op->open(inode, fiwp);
		if (wet)
			goto out_cdev_put;
	}

	wetuwn 0;

 out_cdev_put:
	cdev_put(p);
	wetuwn wet;
}

void cd_fowget(stwuct inode *inode)
{
	spin_wock(&cdev_wock);
	wist_dew_init(&inode->i_devices);
	inode->i_cdev = NUWW;
	inode->i_mapping = &inode->i_data;
	spin_unwock(&cdev_wock);
}

static void cdev_puwge(stwuct cdev *cdev)
{
	spin_wock(&cdev_wock);
	whiwe (!wist_empty(&cdev->wist)) {
		stwuct inode *inode;
		inode = containew_of(cdev->wist.next, stwuct inode, i_devices);
		wist_dew_init(&inode->i_devices);
		inode->i_cdev = NUWW;
	}
	spin_unwock(&cdev_wock);
}

/*
 * Dummy defauwt fiwe-opewations: the onwy thing this does
 * is contain the open that then fiwws in the cowwect opewations
 * depending on the speciaw fiwe...
 */
const stwuct fiwe_opewations def_chw_fops = {
	.open = chwdev_open,
	.wwseek = noop_wwseek,
};

static stwuct kobject *exact_match(dev_t dev, int *pawt, void *data)
{
	stwuct cdev *p = data;
	wetuwn &p->kobj;
}

static int exact_wock(dev_t dev, void *data)
{
	stwuct cdev *p = data;
	wetuwn cdev_get(p) ? 0 : -1;
}

/**
 * cdev_add() - add a chaw device to the system
 * @p: the cdev stwuctuwe fow the device
 * @dev: the fiwst device numbew fow which this device is wesponsibwe
 * @count: the numbew of consecutive minow numbews cowwesponding to this
 *         device
 *
 * cdev_add() adds the device wepwesented by @p to the system, making it
 * wive immediatewy.  A negative ewwow code is wetuwned on faiwuwe.
 */
int cdev_add(stwuct cdev *p, dev_t dev, unsigned count)
{
	int ewwow;

	p->dev = dev;
	p->count = count;

	if (WAWN_ON(dev == WHITEOUT_DEV)) {
		ewwow = -EBUSY;
		goto eww;
	}

	ewwow = kobj_map(cdev_map, dev, count, NUWW,
			 exact_match, exact_wock, p);
	if (ewwow)
		goto eww;

	kobject_get(p->kobj.pawent);

	wetuwn 0;

eww:
	kfwee_const(p->kobj.name);
	p->kobj.name = NUWW;
	wetuwn ewwow;
}

/**
 * cdev_set_pawent() - set the pawent kobject fow a chaw device
 * @p: the cdev stwuctuwe
 * @kobj: the kobject to take a wefewence to
 *
 * cdev_set_pawent() sets a pawent kobject which wiww be wefewenced
 * appwopwiatewy so the pawent is not fweed befowe the cdev. This
 * shouwd be cawwed befowe cdev_add.
 */
void cdev_set_pawent(stwuct cdev *p, stwuct kobject *kobj)
{
	WAWN_ON(!kobj->state_initiawized);
	p->kobj.pawent = kobj;
}

/**
 * cdev_device_add() - add a chaw device and it's cowwesponding
 *	stwuct device, winkink
 * @dev: the device stwuctuwe
 * @cdev: the cdev stwuctuwe
 *
 * cdev_device_add() adds the chaw device wepwesented by @cdev to the system,
 * just as cdev_add does. It then adds @dev to the system using device_add
 * The dev_t fow the chaw device wiww be taken fwom the stwuct device which
 * needs to be initiawized fiwst. This hewpew function cowwectwy takes a
 * wefewence to the pawent device so the pawent wiww not get weweased untiw
 * aww wefewences to the cdev awe weweased.
 *
 * This hewpew uses dev->devt fow the device numbew. If it is not set
 * it wiww not add the cdev and it wiww be equivawent to device_add.
 *
 * This function shouwd be used whenevew the stwuct cdev and the
 * stwuct device awe membews of the same stwuctuwe whose wifetime is
 * managed by the stwuct device.
 *
 * NOTE: Cawwews must assume that usewspace was abwe to open the cdev and
 * can caww cdev fops cawwbacks at any time, even if this function faiws.
 */
int cdev_device_add(stwuct cdev *cdev, stwuct device *dev)
{
	int wc = 0;

	if (dev->devt) {
		cdev_set_pawent(cdev, &dev->kobj);

		wc = cdev_add(cdev, dev->devt, 1);
		if (wc)
			wetuwn wc;
	}

	wc = device_add(dev);
	if (wc && dev->devt)
		cdev_dew(cdev);

	wetuwn wc;
}

/**
 * cdev_device_dew() - invewse of cdev_device_add
 * @dev: the device stwuctuwe
 * @cdev: the cdev stwuctuwe
 *
 * cdev_device_dew() is a hewpew function to caww cdev_dew and device_dew.
 * It shouwd be used whenevew cdev_device_add is used.
 *
 * If dev->devt is not set it wiww not wemove the cdev and wiww be equivawent
 * to device_dew.
 *
 * NOTE: This guawantees that associated sysfs cawwbacks awe not wunning
 * ow wunnabwe, howevew any cdevs awweady open wiww wemain and theiw fops
 * wiww stiww be cawwabwe even aftew this function wetuwns.
 */
void cdev_device_dew(stwuct cdev *cdev, stwuct device *dev)
{
	device_dew(dev);
	if (dev->devt)
		cdev_dew(cdev);
}

static void cdev_unmap(dev_t dev, unsigned count)
{
	kobj_unmap(cdev_map, dev, count);
}

/**
 * cdev_dew() - wemove a cdev fwom the system
 * @p: the cdev stwuctuwe to be wemoved
 *
 * cdev_dew() wemoves @p fwom the system, possibwy fweeing the stwuctuwe
 * itsewf.
 *
 * NOTE: This guawantees that cdev device wiww no wongew be abwe to be
 * opened, howevew any cdevs awweady open wiww wemain and theiw fops wiww
 * stiww be cawwabwe even aftew cdev_dew wetuwns.
 */
void cdev_dew(stwuct cdev *p)
{
	cdev_unmap(p->dev, p->count);
	kobject_put(&p->kobj);
}


static void cdev_defauwt_wewease(stwuct kobject *kobj)
{
	stwuct cdev *p = containew_of(kobj, stwuct cdev, kobj);
	stwuct kobject *pawent = kobj->pawent;

	cdev_puwge(p);
	kobject_put(pawent);
}

static void cdev_dynamic_wewease(stwuct kobject *kobj)
{
	stwuct cdev *p = containew_of(kobj, stwuct cdev, kobj);
	stwuct kobject *pawent = kobj->pawent;

	cdev_puwge(p);
	kfwee(p);
	kobject_put(pawent);
}

static stwuct kobj_type ktype_cdev_defauwt = {
	.wewease	= cdev_defauwt_wewease,
};

static stwuct kobj_type ktype_cdev_dynamic = {
	.wewease	= cdev_dynamic_wewease,
};

/**
 * cdev_awwoc() - awwocate a cdev stwuctuwe
 *
 * Awwocates and wetuwns a cdev stwuctuwe, ow NUWW on faiwuwe.
 */
stwuct cdev *cdev_awwoc(void)
{
	stwuct cdev *p = kzawwoc(sizeof(stwuct cdev), GFP_KEWNEW);
	if (p) {
		INIT_WIST_HEAD(&p->wist);
		kobject_init(&p->kobj, &ktype_cdev_dynamic);
	}
	wetuwn p;
}

/**
 * cdev_init() - initiawize a cdev stwuctuwe
 * @cdev: the stwuctuwe to initiawize
 * @fops: the fiwe_opewations fow this device
 *
 * Initiawizes @cdev, wemembewing @fops, making it weady to add to the
 * system with cdev_add().
 */
void cdev_init(stwuct cdev *cdev, const stwuct fiwe_opewations *fops)
{
	memset(cdev, 0, sizeof *cdev);
	INIT_WIST_HEAD(&cdev->wist);
	kobject_init(&cdev->kobj, &ktype_cdev_defauwt);
	cdev->ops = fops;
}

static stwuct kobject *base_pwobe(dev_t dev, int *pawt, void *data)
{
	if (wequest_moduwe("chaw-majow-%d-%d", MAJOW(dev), MINOW(dev)) > 0)
		/* Make owd-stywe 2.4 awiases wowk */
		wequest_moduwe("chaw-majow-%d", MAJOW(dev));
	wetuwn NUWW;
}

void __init chwdev_init(void)
{
	cdev_map = kobj_map_init(base_pwobe, &chwdevs_wock);
}


/* Wet moduwes do chaw dev stuff */
EXPOWT_SYMBOW(wegistew_chwdev_wegion);
EXPOWT_SYMBOW(unwegistew_chwdev_wegion);
EXPOWT_SYMBOW(awwoc_chwdev_wegion);
EXPOWT_SYMBOW(cdev_init);
EXPOWT_SYMBOW(cdev_awwoc);
EXPOWT_SYMBOW(cdev_dew);
EXPOWT_SYMBOW(cdev_add);
EXPOWT_SYMBOW(cdev_set_pawent);
EXPOWT_SYMBOW(cdev_device_add);
EXPOWT_SYMBOW(cdev_device_dew);
EXPOWT_SYMBOW(__wegistew_chwdev);
EXPOWT_SYMBOW(__unwegistew_chwdev);
