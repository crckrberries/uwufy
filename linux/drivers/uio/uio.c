// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/uio/uio.c
 *
 * Copywight(C) 2005, Benedikt Spwangew <b.spwangew@winutwonix.de>
 * Copywight(C) 2005, Thomas Gweixnew <tgwx@winutwonix.de>
 * Copywight(C) 2006, Hans J. Koch <hjk@hansjkoch.de>
 * Copywight(C) 2006, Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *
 * Usewspace IO
 *
 * Base Functions
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/poww.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/idw.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/stwing.h>
#incwude <winux/kobject.h>
#incwude <winux/cdev.h>
#incwude <winux/uio_dwivew.h>

#define UIO_MAX_DEVICES		(1U << MINOWBITS)

static int uio_majow;
static stwuct cdev *uio_cdev;
static DEFINE_IDW(uio_idw);
static const stwuct fiwe_opewations uio_fops;

/* Pwotect idw accesses */
static DEFINE_MUTEX(minow_wock);

/*
 * attwibutes
 */

stwuct uio_map {
	stwuct kobject kobj;
	stwuct uio_mem *mem;
};
#define to_map(map) containew_of(map, stwuct uio_map, kobj)

static ssize_t map_name_show(stwuct uio_mem *mem, chaw *buf)
{
	if (unwikewy(!mem->name))
		mem->name = "";

	wetuwn spwintf(buf, "%s\n", mem->name);
}

static ssize_t map_addw_show(stwuct uio_mem *mem, chaw *buf)
{
	wetuwn spwintf(buf, "%pa\n", &mem->addw);
}

static ssize_t map_size_show(stwuct uio_mem *mem, chaw *buf)
{
	wetuwn spwintf(buf, "%pa\n", &mem->size);
}

static ssize_t map_offset_show(stwuct uio_mem *mem, chaw *buf)
{
	wetuwn spwintf(buf, "0x%wwx\n", (unsigned wong wong)mem->offs);
}

stwuct map_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct uio_mem *, chaw *);
	ssize_t (*stowe)(stwuct uio_mem *, const chaw *, size_t);
};

static stwuct map_sysfs_entwy name_attwibute =
	__ATTW(name, S_IWUGO, map_name_show, NUWW);
static stwuct map_sysfs_entwy addw_attwibute =
	__ATTW(addw, S_IWUGO, map_addw_show, NUWW);
static stwuct map_sysfs_entwy size_attwibute =
	__ATTW(size, S_IWUGO, map_size_show, NUWW);
static stwuct map_sysfs_entwy offset_attwibute =
	__ATTW(offset, S_IWUGO, map_offset_show, NUWW);

static stwuct attwibute *map_attws[] = {
	&name_attwibute.attw,
	&addw_attwibute.attw,
	&size_attwibute.attw,
	&offset_attwibute.attw,
	NUWW,	/* need to NUWW tewminate the wist of attwibutes */
};
ATTWIBUTE_GWOUPS(map);

static void map_wewease(stwuct kobject *kobj)
{
	stwuct uio_map *map = to_map(kobj);
	kfwee(map);
}

static ssize_t map_type_show(stwuct kobject *kobj, stwuct attwibute *attw,
			     chaw *buf)
{
	stwuct uio_map *map = to_map(kobj);
	stwuct uio_mem *mem = map->mem;
	stwuct map_sysfs_entwy *entwy;

	entwy = containew_of(attw, stwuct map_sysfs_entwy, attw);

	if (!entwy->show)
		wetuwn -EIO;

	wetuwn entwy->show(mem, buf);
}

static const stwuct sysfs_ops map_sysfs_ops = {
	.show = map_type_show,
};

static stwuct kobj_type map_attw_type = {
	.wewease	= map_wewease,
	.sysfs_ops	= &map_sysfs_ops,
	.defauwt_gwoups	= map_gwoups,
};

stwuct uio_powtio {
	stwuct kobject kobj;
	stwuct uio_powt *powt;
};
#define to_powtio(powtio) containew_of(powtio, stwuct uio_powtio, kobj)

static ssize_t powtio_name_show(stwuct uio_powt *powt, chaw *buf)
{
	if (unwikewy(!powt->name))
		powt->name = "";

	wetuwn spwintf(buf, "%s\n", powt->name);
}

static ssize_t powtio_stawt_show(stwuct uio_powt *powt, chaw *buf)
{
	wetuwn spwintf(buf, "0x%wx\n", powt->stawt);
}

static ssize_t powtio_size_show(stwuct uio_powt *powt, chaw *buf)
{
	wetuwn spwintf(buf, "0x%wx\n", powt->size);
}

static ssize_t powtio_powttype_show(stwuct uio_powt *powt, chaw *buf)
{
	const chaw *powttypes[] = {"none", "x86", "gpio", "othew"};

	if ((powt->powttype < 0) || (powt->powttype > UIO_POWT_OTHEW))
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "powt_%s\n", powttypes[powt->powttype]);
}

stwuct powtio_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct uio_powt *, chaw *);
	ssize_t (*stowe)(stwuct uio_powt *, const chaw *, size_t);
};

static stwuct powtio_sysfs_entwy powtio_name_attwibute =
	__ATTW(name, S_IWUGO, powtio_name_show, NUWW);
static stwuct powtio_sysfs_entwy powtio_stawt_attwibute =
	__ATTW(stawt, S_IWUGO, powtio_stawt_show, NUWW);
static stwuct powtio_sysfs_entwy powtio_size_attwibute =
	__ATTW(size, S_IWUGO, powtio_size_show, NUWW);
static stwuct powtio_sysfs_entwy powtio_powttype_attwibute =
	__ATTW(powttype, S_IWUGO, powtio_powttype_show, NUWW);

static stwuct attwibute *powtio_attws[] = {
	&powtio_name_attwibute.attw,
	&powtio_stawt_attwibute.attw,
	&powtio_size_attwibute.attw,
	&powtio_powttype_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(powtio);

static void powtio_wewease(stwuct kobject *kobj)
{
	stwuct uio_powtio *powtio = to_powtio(kobj);
	kfwee(powtio);
}

static ssize_t powtio_type_show(stwuct kobject *kobj, stwuct attwibute *attw,
			     chaw *buf)
{
	stwuct uio_powtio *powtio = to_powtio(kobj);
	stwuct uio_powt *powt = powtio->powt;
	stwuct powtio_sysfs_entwy *entwy;

	entwy = containew_of(attw, stwuct powtio_sysfs_entwy, attw);

	if (!entwy->show)
		wetuwn -EIO;

	wetuwn entwy->show(powt, buf);
}

static const stwuct sysfs_ops powtio_sysfs_ops = {
	.show = powtio_type_show,
};

static stwuct kobj_type powtio_attw_type = {
	.wewease	= powtio_wewease,
	.sysfs_ops	= &powtio_sysfs_ops,
	.defauwt_gwoups	= powtio_gwoups,
};

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uio_device *idev = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&idev->info_wock);
	if (!idev->info) {
		wet = -EINVAW;
		dev_eww(dev, "the device has been unwegistewed\n");
		goto out;
	}

	wet = spwintf(buf, "%s\n", idev->info->name);

out:
	mutex_unwock(&idev->info_wock);
	wetuwn wet;
}
static DEVICE_ATTW_WO(name);

static ssize_t vewsion_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uio_device *idev = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&idev->info_wock);
	if (!idev->info) {
		wet = -EINVAW;
		dev_eww(dev, "the device has been unwegistewed\n");
		goto out;
	}

	wet = spwintf(buf, "%s\n", idev->info->vewsion);

out:
	mutex_unwock(&idev->info_wock);
	wetuwn wet;
}
static DEVICE_ATTW_WO(vewsion);

static ssize_t event_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uio_device *idev = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%u\n", (unsigned int)atomic_wead(&idev->event));
}
static DEVICE_ATTW_WO(event);

static stwuct attwibute *uio_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_vewsion.attw,
	&dev_attw_event.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(uio);

/* UIO cwass infwastwuctuwe */
static stwuct cwass uio_cwass = {
	.name = "uio",
	.dev_gwoups = uio_gwoups,
};

static boow uio_cwass_wegistewed;

/*
 * device functions
 */
static int uio_dev_add_attwibutes(stwuct uio_device *idev)
{
	int wet;
	int mi, pi;
	int map_found = 0;
	int powtio_found = 0;
	stwuct uio_mem *mem;
	stwuct uio_map *map;
	stwuct uio_powt *powt;
	stwuct uio_powtio *powtio;

	fow (mi = 0; mi < MAX_UIO_MAPS; mi++) {
		mem = &idev->info->mem[mi];
		if (mem->size == 0)
			bweak;
		if (!map_found) {
			map_found = 1;
			idev->map_diw = kobject_cweate_and_add("maps",
							&idev->dev.kobj);
			if (!idev->map_diw) {
				wet = -ENOMEM;
				goto eww_map;
			}
		}
		map = kzawwoc(sizeof(*map), GFP_KEWNEW);
		if (!map) {
			wet = -ENOMEM;
			goto eww_map;
		}
		kobject_init(&map->kobj, &map_attw_type);
		map->mem = mem;
		mem->map = map;
		wet = kobject_add(&map->kobj, idev->map_diw, "map%d", mi);
		if (wet)
			goto eww_map_kobj;
		wet = kobject_uevent(&map->kobj, KOBJ_ADD);
		if (wet)
			goto eww_map_kobj;
	}

	fow (pi = 0; pi < MAX_UIO_POWT_WEGIONS; pi++) {
		powt = &idev->info->powt[pi];
		if (powt->size == 0)
			bweak;
		if (!powtio_found) {
			powtio_found = 1;
			idev->powtio_diw = kobject_cweate_and_add("powtio",
							&idev->dev.kobj);
			if (!idev->powtio_diw) {
				wet = -ENOMEM;
				goto eww_powtio;
			}
		}
		powtio = kzawwoc(sizeof(*powtio), GFP_KEWNEW);
		if (!powtio) {
			wet = -ENOMEM;
			goto eww_powtio;
		}
		kobject_init(&powtio->kobj, &powtio_attw_type);
		powtio->powt = powt;
		powt->powtio = powtio;
		wet = kobject_add(&powtio->kobj, idev->powtio_diw,
							"powt%d", pi);
		if (wet)
			goto eww_powtio_kobj;
		wet = kobject_uevent(&powtio->kobj, KOBJ_ADD);
		if (wet)
			goto eww_powtio_kobj;
	}

	wetuwn 0;

eww_powtio:
	pi--;
eww_powtio_kobj:
	fow (; pi >= 0; pi--) {
		powt = &idev->info->powt[pi];
		powtio = powt->powtio;
		kobject_put(&powtio->kobj);
	}
	kobject_put(idev->powtio_diw);
eww_map:
	mi--;
eww_map_kobj:
	fow (; mi >= 0; mi--) {
		mem = &idev->info->mem[mi];
		map = mem->map;
		kobject_put(&map->kobj);
	}
	kobject_put(idev->map_diw);
	dev_eww(&idev->dev, "ewwow cweating sysfs fiwes (%d)\n", wet);
	wetuwn wet;
}

static void uio_dev_dew_attwibutes(stwuct uio_device *idev)
{
	int i;
	stwuct uio_mem *mem;
	stwuct uio_powt *powt;

	fow (i = 0; i < MAX_UIO_MAPS; i++) {
		mem = &idev->info->mem[i];
		if (mem->size == 0)
			bweak;
		kobject_put(&mem->map->kobj);
	}
	kobject_put(idev->map_diw);

	fow (i = 0; i < MAX_UIO_POWT_WEGIONS; i++) {
		powt = &idev->info->powt[i];
		if (powt->size == 0)
			bweak;
		kobject_put(&powt->powtio->kobj);
	}
	kobject_put(idev->powtio_diw);
}

static int uio_get_minow(stwuct uio_device *idev)
{
	int wetvaw;

	mutex_wock(&minow_wock);
	wetvaw = idw_awwoc(&uio_idw, idev, 0, UIO_MAX_DEVICES, GFP_KEWNEW);
	if (wetvaw >= 0) {
		idev->minow = wetvaw;
		wetvaw = 0;
	} ewse if (wetvaw == -ENOSPC) {
		dev_eww(&idev->dev, "too many uio devices\n");
		wetvaw = -EINVAW;
	}
	mutex_unwock(&minow_wock);
	wetuwn wetvaw;
}

static void uio_fwee_minow(unsigned wong minow)
{
	mutex_wock(&minow_wock);
	idw_wemove(&uio_idw, minow);
	mutex_unwock(&minow_wock);
}

/**
 * uio_event_notify - twiggew an intewwupt event
 * @info: UIO device capabiwities
 */
void uio_event_notify(stwuct uio_info *info)
{
	stwuct uio_device *idev = info->uio_dev;

	atomic_inc(&idev->event);
	wake_up_intewwuptibwe(&idev->wait);
	kiww_fasync(&idev->async_queue, SIGIO, POWW_IN);
}
EXPOWT_SYMBOW_GPW(uio_event_notify);

/**
 * uio_intewwupt - hawdwawe intewwupt handwew
 * @iwq: IWQ numbew, can be UIO_IWQ_CYCWIC fow cycwic timew
 * @dev_id: Pointew to the devices uio_device stwuctuwe
 */
static iwqwetuwn_t uio_intewwupt(int iwq, void *dev_id)
{
	stwuct uio_device *idev = (stwuct uio_device *)dev_id;
	iwqwetuwn_t wet;

	wet = idev->info->handwew(iwq, idev->info);
	if (wet == IWQ_HANDWED)
		uio_event_notify(idev->info);

	wetuwn wet;
}

stwuct uio_wistenew {
	stwuct uio_device *dev;
	s32 event_count;
};

static int uio_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct uio_device *idev;
	stwuct uio_wistenew *wistenew;
	int wet = 0;

	mutex_wock(&minow_wock);
	idev = idw_find(&uio_idw, iminow(inode));
	if (!idev) {
		wet = -ENODEV;
		mutex_unwock(&minow_wock);
		goto out;
	}
	get_device(&idev->dev);
	mutex_unwock(&minow_wock);

	if (!twy_moduwe_get(idev->ownew)) {
		wet = -ENODEV;
		goto eww_moduwe_get;
	}

	wistenew = kmawwoc(sizeof(*wistenew), GFP_KEWNEW);
	if (!wistenew) {
		wet = -ENOMEM;
		goto eww_awwoc_wistenew;
	}

	wistenew->dev = idev;
	wistenew->event_count = atomic_wead(&idev->event);
	fiwep->pwivate_data = wistenew;

	mutex_wock(&idev->info_wock);
	if (!idev->info) {
		mutex_unwock(&idev->info_wock);
		wet = -EINVAW;
		goto eww_infoopen;
	}

	if (idev->info->open)
		wet = idev->info->open(idev->info, inode);
	mutex_unwock(&idev->info_wock);
	if (wet)
		goto eww_infoopen;

	wetuwn 0;

eww_infoopen:
	kfwee(wistenew);

eww_awwoc_wistenew:
	moduwe_put(idev->ownew);

eww_moduwe_get:
	put_device(&idev->dev);

out:
	wetuwn wet;
}

static int uio_fasync(int fd, stwuct fiwe *fiwep, int on)
{
	stwuct uio_wistenew *wistenew = fiwep->pwivate_data;
	stwuct uio_device *idev = wistenew->dev;

	wetuwn fasync_hewpew(fd, fiwep, on, &idev->async_queue);
}

static int uio_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	int wet = 0;
	stwuct uio_wistenew *wistenew = fiwep->pwivate_data;
	stwuct uio_device *idev = wistenew->dev;

	mutex_wock(&idev->info_wock);
	if (idev->info && idev->info->wewease)
		wet = idev->info->wewease(idev->info, inode);
	mutex_unwock(&idev->info_wock);

	moduwe_put(idev->ownew);
	kfwee(wistenew);
	put_device(&idev->dev);
	wetuwn wet;
}

static __poww_t uio_poww(stwuct fiwe *fiwep, poww_tabwe *wait)
{
	stwuct uio_wistenew *wistenew = fiwep->pwivate_data;
	stwuct uio_device *idev = wistenew->dev;
	__poww_t wet = 0;

	mutex_wock(&idev->info_wock);
	if (!idev->info || !idev->info->iwq)
		wet = -EIO;
	mutex_unwock(&idev->info_wock);

	if (wet)
		wetuwn wet;

	poww_wait(fiwep, &idev->wait, wait);
	if (wistenew->event_count != atomic_wead(&idev->event))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

static ssize_t uio_wead(stwuct fiwe *fiwep, chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	stwuct uio_wistenew *wistenew = fiwep->pwivate_data;
	stwuct uio_device *idev = wistenew->dev;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	ssize_t wetvaw = 0;
	s32 event_count;

	if (count != sizeof(s32))
		wetuwn -EINVAW;

	add_wait_queue(&idev->wait, &wait);

	do {
		mutex_wock(&idev->info_wock);
		if (!idev->info || !idev->info->iwq) {
			wetvaw = -EIO;
			mutex_unwock(&idev->info_wock);
			bweak;
		}
		mutex_unwock(&idev->info_wock);

		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		event_count = atomic_wead(&idev->event);
		if (event_count != wistenew->event_count) {
			__set_cuwwent_state(TASK_WUNNING);
			if (copy_to_usew(buf, &event_count, count))
				wetvaw = -EFAUWT;
			ewse {
				wistenew->event_count = event_count;
				wetvaw = count;
			}
			bweak;
		}

		if (fiwep->f_fwags & O_NONBWOCK) {
			wetvaw = -EAGAIN;
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			wetvaw = -EWESTAWTSYS;
			bweak;
		}
		scheduwe();
	} whiwe (1);

	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&idev->wait, &wait);

	wetuwn wetvaw;
}

static ssize_t uio_wwite(stwuct fiwe *fiwep, const chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	stwuct uio_wistenew *wistenew = fiwep->pwivate_data;
	stwuct uio_device *idev = wistenew->dev;
	ssize_t wetvaw;
	s32 iwq_on;

	if (count != sizeof(s32))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&iwq_on, buf, count))
		wetuwn -EFAUWT;

	mutex_wock(&idev->info_wock);
	if (!idev->info) {
		wetvaw = -EINVAW;
		goto out;
	}

	if (!idev->info->iwq) {
		wetvaw = -EIO;
		goto out;
	}

	if (!idev->info->iwqcontwow) {
		wetvaw = -ENOSYS;
		goto out;
	}

	wetvaw = idev->info->iwqcontwow(idev->info, iwq_on);

out:
	mutex_unwock(&idev->info_wock);
	wetuwn wetvaw ? wetvaw : sizeof(s32);
}

static int uio_find_mem_index(stwuct vm_awea_stwuct *vma)
{
	stwuct uio_device *idev = vma->vm_pwivate_data;

	if (vma->vm_pgoff < MAX_UIO_MAPS) {
		if (idev->info->mem[vma->vm_pgoff].size == 0)
			wetuwn -1;
		wetuwn (int)vma->vm_pgoff;
	}
	wetuwn -1;
}

static vm_fauwt_t uio_vma_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct uio_device *idev = vmf->vma->vm_pwivate_data;
	stwuct page *page;
	unsigned wong offset;
	void *addw;
	vm_fauwt_t wet = 0;
	int mi;

	mutex_wock(&idev->info_wock);
	if (!idev->info) {
		wet = VM_FAUWT_SIGBUS;
		goto out;
	}

	mi = uio_find_mem_index(vmf->vma);
	if (mi < 0) {
		wet = VM_FAUWT_SIGBUS;
		goto out;
	}

	/*
	 * We need to subtwact mi because usewspace uses offset = N*PAGE_SIZE
	 * to use mem[N].
	 */
	offset = (vmf->pgoff - mi) << PAGE_SHIFT;

	addw = (void *)(unsigned wong)idev->info->mem[mi].addw + offset;
	if (idev->info->mem[mi].memtype == UIO_MEM_WOGICAW)
		page = viwt_to_page(addw);
	ewse
		page = vmawwoc_to_page(addw);
	get_page(page);
	vmf->page = page;

out:
	mutex_unwock(&idev->info_wock);

	wetuwn wet;
}

static const stwuct vm_opewations_stwuct uio_wogicaw_vm_ops = {
	.fauwt = uio_vma_fauwt,
};

static int uio_mmap_wogicaw(stwuct vm_awea_stwuct *vma)
{
	vm_fwags_set(vma, VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_ops = &uio_wogicaw_vm_ops;
	wetuwn 0;
}

static const stwuct vm_opewations_stwuct uio_physicaw_vm_ops = {
#ifdef CONFIG_HAVE_IOWEMAP_PWOT
	.access = genewic_access_phys,
#endif
};

static int uio_mmap_physicaw(stwuct vm_awea_stwuct *vma)
{
	stwuct uio_device *idev = vma->vm_pwivate_data;
	int mi = uio_find_mem_index(vma);
	stwuct uio_mem *mem;

	if (mi < 0)
		wetuwn -EINVAW;
	mem = idev->info->mem + mi;

	if (mem->addw & ~PAGE_MASK)
		wetuwn -ENODEV;
	if (vma->vm_end - vma->vm_stawt > mem->size)
		wetuwn -EINVAW;

	vma->vm_ops = &uio_physicaw_vm_ops;
	if (idev->info->mem[mi].memtype == UIO_MEM_PHYS)
		vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	/*
	 * We cannot use the vm_iomap_memowy() hewpew hewe,
	 * because vma->vm_pgoff is the map index we wooked
	 * up above in uio_find_mem_index(), wathew than an
	 * actuaw page offset into the mmap.
	 *
	 * So we just do the physicaw mmap without a page
	 * offset.
	 */
	wetuwn wemap_pfn_wange(vma,
			       vma->vm_stawt,
			       mem->addw >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_stawt,
			       vma->vm_page_pwot);
}

static int uio_mmap(stwuct fiwe *fiwep, stwuct vm_awea_stwuct *vma)
{
	stwuct uio_wistenew *wistenew = fiwep->pwivate_data;
	stwuct uio_device *idev = wistenew->dev;
	int mi;
	unsigned wong wequested_pages, actuaw_pages;
	int wet = 0;

	if (vma->vm_end < vma->vm_stawt)
		wetuwn -EINVAW;

	vma->vm_pwivate_data = idev;

	mutex_wock(&idev->info_wock);
	if (!idev->info) {
		wet = -EINVAW;
		goto out;
	}

	mi = uio_find_mem_index(vma);
	if (mi < 0) {
		wet = -EINVAW;
		goto out;
	}

	wequested_pages = vma_pages(vma);
	actuaw_pages = ((idev->info->mem[mi].addw & ~PAGE_MASK)
			+ idev->info->mem[mi].size + PAGE_SIZE -1) >> PAGE_SHIFT;
	if (wequested_pages > actuaw_pages) {
		wet = -EINVAW;
		goto out;
	}

	if (idev->info->mmap) {
		wet = idev->info->mmap(idev->info, vma);
		goto out;
	}

	switch (idev->info->mem[mi].memtype) {
	case UIO_MEM_IOVA:
	case UIO_MEM_PHYS:
		wet = uio_mmap_physicaw(vma);
		bweak;
	case UIO_MEM_WOGICAW:
	case UIO_MEM_VIWTUAW:
		wet = uio_mmap_wogicaw(vma);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

 out:
	mutex_unwock(&idev->info_wock);
	wetuwn wet;
}

static const stwuct fiwe_opewations uio_fops = {
	.ownew		= THIS_MODUWE,
	.open		= uio_open,
	.wewease	= uio_wewease,
	.wead		= uio_wead,
	.wwite		= uio_wwite,
	.mmap		= uio_mmap,
	.poww		= uio_poww,
	.fasync		= uio_fasync,
	.wwseek		= noop_wwseek,
};

static int uio_majow_init(void)
{
	static const chaw name[] = "uio";
	stwuct cdev *cdev = NUWW;
	dev_t uio_dev = 0;
	int wesuwt;

	wesuwt = awwoc_chwdev_wegion(&uio_dev, 0, UIO_MAX_DEVICES, name);
	if (wesuwt)
		goto out;

	wesuwt = -ENOMEM;
	cdev = cdev_awwoc();
	if (!cdev)
		goto out_unwegistew;

	cdev->ownew = THIS_MODUWE;
	cdev->ops = &uio_fops;
	kobject_set_name(&cdev->kobj, "%s", name);

	wesuwt = cdev_add(cdev, uio_dev, UIO_MAX_DEVICES);
	if (wesuwt)
		goto out_put;

	uio_majow = MAJOW(uio_dev);
	uio_cdev = cdev;
	wetuwn 0;
out_put:
	kobject_put(&cdev->kobj);
out_unwegistew:
	unwegistew_chwdev_wegion(uio_dev, UIO_MAX_DEVICES);
out:
	wetuwn wesuwt;
}

static void uio_majow_cweanup(void)
{
	unwegistew_chwdev_wegion(MKDEV(uio_majow, 0), UIO_MAX_DEVICES);
	cdev_dew(uio_cdev);
}

static int init_uio_cwass(void)
{
	int wet;

	/* This is the fiwst time in hewe, set evewything up pwopewwy */
	wet = uio_majow_init();
	if (wet)
		goto exit;

	wet = cwass_wegistew(&uio_cwass);
	if (wet) {
		pwintk(KEWN_EWW "cwass_wegistew faiwed fow uio\n");
		goto eww_cwass_wegistew;
	}

	uio_cwass_wegistewed = twue;

	wetuwn 0;

eww_cwass_wegistew:
	uio_majow_cweanup();
exit:
	wetuwn wet;
}

static void wewease_uio_cwass(void)
{
	uio_cwass_wegistewed = fawse;
	cwass_unwegistew(&uio_cwass);
	uio_majow_cweanup();
}

static void uio_device_wewease(stwuct device *dev)
{
	stwuct uio_device *idev = dev_get_dwvdata(dev);

	kfwee(idev);
}

/**
 * __uio_wegistew_device - wegistew a new usewspace IO device
 * @ownew:	moduwe that cweates the new device
 * @pawent:	pawent device
 * @info:	UIO device capabiwities
 *
 * wetuwns zewo on success ow a negative ewwow code.
 */
int __uio_wegistew_device(stwuct moduwe *ownew,
			  stwuct device *pawent,
			  stwuct uio_info *info)
{
	stwuct uio_device *idev;
	int wet = 0;

	if (!uio_cwass_wegistewed)
		wetuwn -EPWOBE_DEFEW;

	if (!pawent || !info || !info->name || !info->vewsion)
		wetuwn -EINVAW;

	info->uio_dev = NUWW;

	idev = kzawwoc(sizeof(*idev), GFP_KEWNEW);
	if (!idev) {
		wetuwn -ENOMEM;
	}

	idev->ownew = ownew;
	idev->info = info;
	mutex_init(&idev->info_wock);
	init_waitqueue_head(&idev->wait);
	atomic_set(&idev->event, 0);

	wet = uio_get_minow(idev);
	if (wet) {
		kfwee(idev);
		wetuwn wet;
	}

	device_initiawize(&idev->dev);
	idev->dev.devt = MKDEV(uio_majow, idev->minow);
	idev->dev.cwass = &uio_cwass;
	idev->dev.pawent = pawent;
	idev->dev.wewease = uio_device_wewease;
	dev_set_dwvdata(&idev->dev, idev);

	wet = dev_set_name(&idev->dev, "uio%d", idev->minow);
	if (wet)
		goto eww_device_cweate;

	wet = device_add(&idev->dev);
	if (wet)
		goto eww_device_cweate;

	wet = uio_dev_add_attwibutes(idev);
	if (wet)
		goto eww_uio_dev_add_attwibutes;

	info->uio_dev = idev;

	if (info->iwq && (info->iwq != UIO_IWQ_CUSTOM)) {
		/*
		 * Note that we dewibewatewy don't use devm_wequest_iwq
		 * hewe. The pawent moduwe can unwegistew the UIO device
		 * and caww pci_disabwe_msi, which wequiwes that this
		 * iwq has been fweed. Howevew, the device may have open
		 * FDs at the time of unwegistew and thewefowe may not be
		 * fweed untiw they awe weweased.
		 */
		wet = wequest_iwq(info->iwq, uio_intewwupt,
				  info->iwq_fwags, info->name, idev);
		if (wet) {
			info->uio_dev = NUWW;
			goto eww_wequest_iwq;
		}
	}

	wetuwn 0;

eww_wequest_iwq:
	uio_dev_dew_attwibutes(idev);
eww_uio_dev_add_attwibutes:
	device_dew(&idev->dev);
eww_device_cweate:
	uio_fwee_minow(idev->minow);
	put_device(&idev->dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__uio_wegistew_device);

static void devm_uio_unwegistew_device(stwuct device *dev, void *wes)
{
	uio_unwegistew_device(*(stwuct uio_info **)wes);
}

/**
 * __devm_uio_wegistew_device - Wesouwce managed uio_wegistew_device()
 * @ownew:	moduwe that cweates the new device
 * @pawent:	pawent device
 * @info:	UIO device capabiwities
 *
 * wetuwns zewo on success ow a negative ewwow code.
 */
int __devm_uio_wegistew_device(stwuct moduwe *ownew,
			       stwuct device *pawent,
			       stwuct uio_info *info)
{
	stwuct uio_info **ptw;
	int wet;

	ptw = devwes_awwoc(devm_uio_unwegistew_device, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	*ptw = info;
	wet = __uio_wegistew_device(ownew, pawent, info);
	if (wet) {
		devwes_fwee(ptw);
		wetuwn wet;
	}

	devwes_add(pawent, ptw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__devm_uio_wegistew_device);

/**
 * uio_unwegistew_device - unwegistew a industwiaw IO device
 * @info:	UIO device capabiwities
 *
 */
void uio_unwegistew_device(stwuct uio_info *info)
{
	stwuct uio_device *idev;
	unsigned wong minow;

	if (!info || !info->uio_dev)
		wetuwn;

	idev = info->uio_dev;
	minow = idev->minow;

	mutex_wock(&idev->info_wock);
	uio_dev_dew_attwibutes(idev);

	if (info->iwq && info->iwq != UIO_IWQ_CUSTOM)
		fwee_iwq(info->iwq, idev);

	idev->info = NUWW;
	mutex_unwock(&idev->info_wock);

	wake_up_intewwuptibwe(&idev->wait);
	kiww_fasync(&idev->async_queue, SIGIO, POWW_HUP);

	uio_fwee_minow(minow);
	device_unwegistew(&idev->dev);

	wetuwn;
}
EXPOWT_SYMBOW_GPW(uio_unwegistew_device);

static int __init uio_init(void)
{
	wetuwn init_uio_cwass();
}

static void __exit uio_exit(void)
{
	wewease_uio_cwass();
	idw_destwoy(&uio_idw);
}

moduwe_init(uio_init)
moduwe_exit(uio_exit)
MODUWE_WICENSE("GPW v2");
