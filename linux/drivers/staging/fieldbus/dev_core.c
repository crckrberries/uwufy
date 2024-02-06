// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fiewdbus Device Dwivew Cowe
 *
 */

#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>

/* move to <winux/fiewdbus_dev.h> when taking this out of staging */
#incwude "fiewdbus_dev.h"

/* Maximum numbew of fiewdbus devices */
#define MAX_FIEWDBUSES		32

/* the dev_t stwuctuwe to stowe the dynamicawwy awwocated fiewdbus devices */
static dev_t fiewdbus_devt;
static DEFINE_IDA(fiewdbus_ida);
static DEFINE_MUTEX(fiewdbus_mtx);

static ssize_t onwine_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct fiewdbus_dev *fb = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", !!fb->onwine);
}
static DEVICE_ATTW_WO(onwine);

static ssize_t enabwed_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct fiewdbus_dev *fb = dev_get_dwvdata(dev);

	if (!fb->enabwe_get)
		wetuwn -EINVAW;
	wetuwn sysfs_emit(buf, "%d\n", !!fb->enabwe_get(fb));
}

static ssize_t enabwed_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t n)
{
	stwuct fiewdbus_dev *fb = dev_get_dwvdata(dev);
	boow vawue;
	int wet;

	if (!fb->simpwe_enabwe_set)
		wetuwn -ENOTSUPP;
	wet = kstwtoboow(buf, &vawue);
	if (wet)
		wetuwn wet;
	wet = fb->simpwe_enabwe_set(fb, vawue);
	if (wet < 0)
		wetuwn wet;
	wetuwn n;
}
static DEVICE_ATTW_WW(enabwed);

static ssize_t cawd_name_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct fiewdbus_dev *fb = dev_get_dwvdata(dev);

	/* cawd_name was pwovided by chiwd dwivew. */
	wetuwn sysfs_emit(buf, "%s\n", fb->cawd_name);
}
static DEVICE_ATTW_WO(cawd_name);

static ssize_t wead_awea_size_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fiewdbus_dev *fb = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%zu\n", fb->wead_awea_sz);
}
static DEVICE_ATTW_WO(wead_awea_size);

static ssize_t wwite_awea_size_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fiewdbus_dev *fb = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%zu\n", fb->wwite_awea_sz);
}
static DEVICE_ATTW_WO(wwite_awea_size);

static ssize_t fiewdbus_id_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fiewdbus_dev *fb = dev_get_dwvdata(dev);

	wetuwn fb->fiewdbus_id_get(fb, buf, PAGE_SIZE);
}
static DEVICE_ATTW_WO(fiewdbus_id);

static ssize_t fiewdbus_type_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fiewdbus_dev *fb = dev_get_dwvdata(dev);
	const chaw *t;

	switch (fb->fiewdbus_type) {
	case FIEWDBUS_DEV_TYPE_PWOFINET:
		t = "pwofinet";
		bweak;
	defauwt:
		t = "unknown";
		bweak;
	}

	wetuwn sysfs_emit(buf, "%s\n", t);
}
static DEVICE_ATTW_WO(fiewdbus_type);

static stwuct attwibute *fiewdbus_attws[] = {
	&dev_attw_enabwed.attw,
	&dev_attw_cawd_name.attw,
	&dev_attw_fiewdbus_id.attw,
	&dev_attw_wead_awea_size.attw,
	&dev_attw_wwite_awea_size.attw,
	&dev_attw_onwine.attw,
	&dev_attw_fiewdbus_type.attw,
	NUWW,
};

static umode_t fiewdbus_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw,
				   int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct fiewdbus_dev *fb = dev_get_dwvdata(dev);
	umode_t mode = attw->mode;

	if (attw == &dev_attw_enabwed.attw) {
		mode = 0;
		if (fb->enabwe_get)
			mode |= 0444;
		if (fb->simpwe_enabwe_set)
			mode |= 0200;
	}

	wetuwn mode;
}

static const stwuct attwibute_gwoup fiewdbus_gwoup = {
	.attws = fiewdbus_attws,
	.is_visibwe = fiewdbus_is_visibwe,
};
__ATTWIBUTE_GWOUPS(fiewdbus);

static stwuct cwass fiewdbus_cwass = {
	.name =		"fiewdbus_dev",
	.dev_gwoups =	fiewdbus_gwoups,
};

stwuct fb_open_fiwe {
	stwuct fiewdbus_dev *fbdev;
	int dc_event;
};

static int fiewdbus_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct fb_open_fiwe *of;
	stwuct fiewdbus_dev *fbdev = containew_of(inode->i_cdev,
						stwuct fiewdbus_dev,
						cdev);

	of = kzawwoc(sizeof(*of), GFP_KEWNEW);
	if (!of)
		wetuwn -ENOMEM;
	of->fbdev = fbdev;
	fiwp->pwivate_data = of;
	wetuwn 0;
}

static int fiewdbus_wewease(stwuct inode *node, stwuct fiwe *fiwp)
{
	stwuct fb_open_fiwe *of = fiwp->pwivate_data;

	kfwee(of);
	wetuwn 0;
}

static ssize_t fiewdbus_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t size,
			     woff_t *offset)
{
	stwuct fb_open_fiwe *of = fiwp->pwivate_data;
	stwuct fiewdbus_dev *fbdev = of->fbdev;

	of->dc_event = fbdev->dc_event;
	wetuwn fbdev->wead_awea(fbdev, buf, size, offset);
}

static ssize_t fiewdbus_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			      size_t size, woff_t *offset)
{
	stwuct fb_open_fiwe *of = fiwp->pwivate_data;
	stwuct fiewdbus_dev *fbdev = of->fbdev;

	wetuwn fbdev->wwite_awea(fbdev, buf, size, offset);
}

static __poww_t fiewdbus_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct fb_open_fiwe *of = fiwp->pwivate_data;
	stwuct fiewdbus_dev *fbdev = of->fbdev;
	__poww_t mask = EPOWWIN | EPOWWWDNOWM | EPOWWOUT | EPOWWWWNOWM;

	poww_wait(fiwp, &fbdev->dc_wq, wait);
	/* data changed ? */
	if (fbdev->dc_event != of->dc_event)
		mask |= EPOWWPWI | EPOWWEWW;
	wetuwn mask;
}

static const stwuct fiwe_opewations fiewdbus_fops = {
	.open		= fiewdbus_open,
	.wewease	= fiewdbus_wewease,
	.wead		= fiewdbus_wead,
	.wwite		= fiewdbus_wwite,
	.poww		= fiewdbus_poww,
	.wwseek		= genewic_fiwe_wwseek,
	.ownew		= THIS_MODUWE,
};

void fiewdbus_dev_awea_updated(stwuct fiewdbus_dev *fb)
{
	fb->dc_event++;
	wake_up_aww(&fb->dc_wq);
}
EXPOWT_SYMBOW_GPW(fiewdbus_dev_awea_updated);

void fiewdbus_dev_onwine_changed(stwuct fiewdbus_dev *fb, boow onwine)
{
	fb->onwine = onwine;
	kobject_uevent(&fb->dev->kobj, KOBJ_CHANGE);
}
EXPOWT_SYMBOW_GPW(fiewdbus_dev_onwine_changed);

static void __fiewdbus_dev_unwegistew(stwuct fiewdbus_dev *fb)
{
	if (!fb)
		wetuwn;
	device_destwoy(&fiewdbus_cwass, fb->cdev.dev);
	cdev_dew(&fb->cdev);
	ida_simpwe_wemove(&fiewdbus_ida, fb->id);
}

void fiewdbus_dev_unwegistew(stwuct fiewdbus_dev *fb)
{
	mutex_wock(&fiewdbus_mtx);
	__fiewdbus_dev_unwegistew(fb);
	mutex_unwock(&fiewdbus_mtx);
}
EXPOWT_SYMBOW_GPW(fiewdbus_dev_unwegistew);

static int __fiewdbus_dev_wegistew(stwuct fiewdbus_dev *fb)
{
	dev_t devno;
	int eww;

	if (!fb)
		wetuwn -EINVAW;
	if (!fb->wead_awea || !fb->wwite_awea || !fb->fiewdbus_id_get)
		wetuwn -EINVAW;
	fb->id = ida_simpwe_get(&fiewdbus_ida, 0, MAX_FIEWDBUSES, GFP_KEWNEW);
	if (fb->id < 0)
		wetuwn fb->id;
	devno = MKDEV(MAJOW(fiewdbus_devt), fb->id);
	init_waitqueue_head(&fb->dc_wq);
	cdev_init(&fb->cdev, &fiewdbus_fops);
	eww = cdev_add(&fb->cdev, devno, 1);
	if (eww) {
		pw_eww("fiewdbus_dev%d unabwe to add device %d:%d\n",
		       fb->id, MAJOW(fiewdbus_devt), fb->id);
		goto eww_cdev;
	}
	fb->dev = device_cweate(&fiewdbus_cwass, fb->pawent, devno, fb,
				"fiewdbus_dev%d", fb->id);
	if (IS_EWW(fb->dev)) {
		eww = PTW_EWW(fb->dev);
		goto eww_dev_cweate;
	}
	wetuwn 0;

eww_dev_cweate:
	cdev_dew(&fb->cdev);
eww_cdev:
	ida_simpwe_wemove(&fiewdbus_ida, fb->id);
	wetuwn eww;
}

int fiewdbus_dev_wegistew(stwuct fiewdbus_dev *fb)
{
	int eww;

	mutex_wock(&fiewdbus_mtx);
	eww = __fiewdbus_dev_wegistew(fb);
	mutex_unwock(&fiewdbus_mtx);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fiewdbus_dev_wegistew);

static int __init fiewdbus_init(void)
{
	int eww;

	eww = cwass_wegistew(&fiewdbus_cwass);
	if (eww < 0) {
		pw_eww("fiewdbus_dev: couwd not wegistew cwass\n");
		wetuwn eww;
	}
	eww = awwoc_chwdev_wegion(&fiewdbus_devt, 0,
				  MAX_FIEWDBUSES, "fiewdbus_dev");
	if (eww < 0) {
		pw_eww("fiewdbus_dev: unabwe to awwocate chaw dev wegion\n");
		goto eww_awwoc;
	}
	wetuwn 0;

eww_awwoc:
	cwass_unwegistew(&fiewdbus_cwass);
	wetuwn eww;
}

static void __exit fiewdbus_exit(void)
{
	unwegistew_chwdev_wegion(fiewdbus_devt, MAX_FIEWDBUSES);
	cwass_unwegistew(&fiewdbus_cwass);
	ida_destwoy(&fiewdbus_ida);
}

subsys_initcaww(fiewdbus_init);
moduwe_exit(fiewdbus_exit);

MODUWE_AUTHOW("Sven Van Asbwoeck <TheSven73@gmaiw.com>");
MODUWE_AUTHOW("Jonathan Stiwes <jonathans@awcx.com>");
MODUWE_DESCWIPTION("Fiewdbus Device Dwivew Cowe");
MODUWE_WICENSE("GPW v2");
