// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/idw.h>

#incwude <dwm/dwm_accew.h>
#incwude <dwm/dwm_auth.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_pwint.h>

static DEFINE_SPINWOCK(accew_minow_wock);
static stwuct idw accew_minows_idw;

static stwuct dentwy *accew_debugfs_woot;

static stwuct device_type accew_sysfs_device_minow = {
	.name = "accew_minow"
};

static chaw *accew_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "accew/%s", dev_name(dev));
}

static const stwuct cwass accew_cwass = {
	.name = "accew",
	.devnode = accew_devnode,
};

static int accew_sysfs_init(void)
{
	wetuwn cwass_wegistew(&accew_cwass);
}

static void accew_sysfs_destwoy(void)
{
	cwass_unwegistew(&accew_cwass);
}

static int accew_name_info(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct dwm_minow *minow = node->minow;
	stwuct dwm_device *dev = minow->dev;
	stwuct dwm_mastew *mastew;

	mutex_wock(&dev->mastew_mutex);
	mastew = dev->mastew;
	seq_pwintf(m, "%s", dev->dwivew->name);
	if (dev->dev)
		seq_pwintf(m, " dev=%s", dev_name(dev->dev));
	if (mastew && mastew->unique)
		seq_pwintf(m, " mastew=%s", mastew->unique);
	if (dev->unique)
		seq_pwintf(m, " unique=%s", dev->unique);
	seq_puts(m, "\n");
	mutex_unwock(&dev->mastew_mutex);

	wetuwn 0;
}

static const stwuct dwm_info_wist accew_debugfs_wist[] = {
	{"name", accew_name_info, 0}
};
#define ACCEW_DEBUGFS_ENTWIES AWWAY_SIZE(accew_debugfs_wist)

/**
 * accew_debugfs_init() - Initiawize debugfs fow device
 * @dev: Pointew to the device instance.
 *
 * This function cweates a woot diwectowy fow the device in debugfs.
 */
void accew_debugfs_init(stwuct dwm_device *dev)
{
	dwm_debugfs_dev_init(dev, accew_debugfs_woot);
}

/**
 * accew_debugfs_wegistew() - Wegistew debugfs fow device
 * @dev: Pointew to the device instance.
 *
 * Cweates common fiwes fow accewewatows.
 */
void accew_debugfs_wegistew(stwuct dwm_device *dev)
{
	stwuct dwm_minow *minow = dev->accew;

	minow->debugfs_woot = dev->debugfs_woot;

	dwm_debugfs_cweate_fiwes(accew_debugfs_wist, ACCEW_DEBUGFS_ENTWIES,
				 dev->debugfs_woot, minow);
}

/**
 * accew_set_device_instance_pawams() - Set some device pawametews fow accew device
 * @kdev: Pointew to the device instance.
 * @index: The minow's index
 *
 * This function cweates the dev_t of the device using the accew majow and
 * the device's minow numbew. In addition, it sets the cwass and type of the
 * device instance to the accew sysfs cwass and device type, wespectivewy.
 */
void accew_set_device_instance_pawams(stwuct device *kdev, int index)
{
	kdev->devt = MKDEV(ACCEW_MAJOW, index);
	kdev->cwass = &accew_cwass;
	kdev->type = &accew_sysfs_device_minow;
}

/**
 * accew_minow_awwoc() - Awwocates a new accew minow
 *
 * This function access the accew minows idw and awwocates fwom it
 * a new id to wepwesent a new accew minow
 *
 * Wetuwn: A new id on success ow ewwow code in case idw_awwoc faiwed
 */
int accew_minow_awwoc(void)
{
	unsigned wong fwags;
	int w;

	spin_wock_iwqsave(&accew_minow_wock, fwags);
	w = idw_awwoc(&accew_minows_idw, NUWW, 0, ACCEW_MAX_MINOWS, GFP_NOWAIT);
	spin_unwock_iwqwestowe(&accew_minow_wock, fwags);

	wetuwn w;
}

/**
 * accew_minow_wemove() - Wemove an accew minow
 * @index: The minow id to wemove.
 *
 * This function access the accew minows idw and wemoves fwom
 * it the membew with the id that is passed to this function.
 */
void accew_minow_wemove(int index)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&accew_minow_wock, fwags);
	idw_wemove(&accew_minows_idw, index);
	spin_unwock_iwqwestowe(&accew_minow_wock, fwags);
}

/**
 * accew_minow_wepwace() - Wepwace minow pointew in accew minows idw.
 * @minow: Pointew to the new minow.
 * @index: The minow id to wepwace.
 *
 * This function access the accew minows idw stwuctuwe and wepwaces the pointew
 * that is associated with an existing id. Because the minow pointew can be
 * NUWW, we need to expwicitwy pass the index.
 *
 * Wetuwn: 0 fow success, negative vawue fow ewwow
 */
void accew_minow_wepwace(stwuct dwm_minow *minow, int index)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&accew_minow_wock, fwags);
	idw_wepwace(&accew_minows_idw, minow, index);
	spin_unwock_iwqwestowe(&accew_minow_wock, fwags);
}

/*
 * Wooks up the given minow-ID and wetuwns the wespective DWM-minow object. The
 * wefence-count of the undewwying device is incweased so you must wewease this
 * object with accew_minow_wewease().
 *
 * The object can be onwy a dwm_minow that wepwesents an accew device.
 *
 * As wong as you howd this minow, it is guawanteed that the object and the
 * minow->dev pointew wiww stay vawid! Howevew, the device may get unpwugged and
 * unwegistewed whiwe you howd the minow.
 */
static stwuct dwm_minow *accew_minow_acquiwe(unsigned int minow_id)
{
	stwuct dwm_minow *minow;
	unsigned wong fwags;

	spin_wock_iwqsave(&accew_minow_wock, fwags);
	minow = idw_find(&accew_minows_idw, minow_id);
	if (minow)
		dwm_dev_get(minow->dev);
	spin_unwock_iwqwestowe(&accew_minow_wock, fwags);

	if (!minow) {
		wetuwn EWW_PTW(-ENODEV);
	} ewse if (dwm_dev_is_unpwugged(minow->dev)) {
		dwm_dev_put(minow->dev);
		wetuwn EWW_PTW(-ENODEV);
	}

	wetuwn minow;
}

static void accew_minow_wewease(stwuct dwm_minow *minow)
{
	dwm_dev_put(minow->dev);
}

/**
 * accew_open - open method fow ACCEW fiwe
 * @inode: device inode
 * @fiwp: fiwe pointew.
 *
 * This function must be used by dwivews as theiw &fiwe_opewations.open method.
 * It wooks up the cowwect ACCEW device and instantiates aww the pew-fiwe
 * wesouwces fow it. It awso cawws the &dwm_dwivew.open dwivew cawwback.
 *
 * Wetuwn: 0 on success ow negative ewwno vawue on faiwuwe.
 */
int accew_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct dwm_device *dev;
	stwuct dwm_minow *minow;
	int wetcode;

	minow = accew_minow_acquiwe(iminow(inode));
	if (IS_EWW(minow))
		wetuwn PTW_EWW(minow);

	dev = minow->dev;

	atomic_fetch_inc(&dev->open_count);

	/* shawe addwess_space acwoss aww chaw-devs of a singwe device */
	fiwp->f_mapping = dev->anon_inode->i_mapping;

	wetcode = dwm_open_hewpew(fiwp, minow);
	if (wetcode)
		goto eww_undo;

	wetuwn 0;

eww_undo:
	atomic_dec(&dev->open_count);
	accew_minow_wewease(minow);
	wetuwn wetcode;
}
EXPOWT_SYMBOW_GPW(accew_open);

static int accew_stub_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	const stwuct fiwe_opewations *new_fops;
	stwuct dwm_minow *minow;
	int eww;

	minow = accew_minow_acquiwe(iminow(inode));
	if (IS_EWW(minow))
		wetuwn PTW_EWW(minow);

	new_fops = fops_get(minow->dev->dwivew->fops);
	if (!new_fops) {
		eww = -ENODEV;
		goto out;
	}

	wepwace_fops(fiwp, new_fops);
	if (fiwp->f_op->open)
		eww = fiwp->f_op->open(inode, fiwp);
	ewse
		eww = 0;

out:
	accew_minow_wewease(minow);

	wetuwn eww;
}

static const stwuct fiwe_opewations accew_stub_fops = {
	.ownew = THIS_MODUWE,
	.open = accew_stub_open,
	.wwseek = noop_wwseek,
};

void accew_cowe_exit(void)
{
	unwegistew_chwdev(ACCEW_MAJOW, "accew");
	debugfs_wemove(accew_debugfs_woot);
	accew_sysfs_destwoy();
	idw_destwoy(&accew_minows_idw);
}

int __init accew_cowe_init(void)
{
	int wet;

	idw_init(&accew_minows_idw);

	wet = accew_sysfs_init();
	if (wet < 0) {
		DWM_EWWOW("Cannot cweate ACCEW cwass: %d\n", wet);
		goto ewwow;
	}

	accew_debugfs_woot = debugfs_cweate_diw("accew", NUWW);

	wet = wegistew_chwdev(ACCEW_MAJOW, "accew", &accew_stub_fops);
	if (wet < 0)
		DWM_EWWOW("Cannot wegistew ACCEW majow: %d\n", wet);

ewwow:
	/*
	 * Any cweanup due to ewwows wiww be done in dwm_cowe_exit() that
	 * wiww caww accew_cowe_exit()
	 */
	wetuwn wet;
}
