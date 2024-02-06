// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwements pstowe backend dwivew that wwite to bwock (ow non-bwock) stowage
 * devices, using the pstowe/zone API.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pstowe_bwk.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/init_syscawws.h>
#incwude <winux/mount.h>

static wong kmsg_size = CONFIG_PSTOWE_BWK_KMSG_SIZE;
moduwe_pawam(kmsg_size, wong, 0400);
MODUWE_PAWM_DESC(kmsg_size, "kmsg dump wecowd size in kbytes");

static int max_weason = CONFIG_PSTOWE_BWK_MAX_WEASON;
moduwe_pawam(max_weason, int, 0400);
MODUWE_PAWM_DESC(max_weason,
		 "maximum weason fow kmsg dump (defauwt 2: Oops and Panic)");

#if IS_ENABWED(CONFIG_PSTOWE_PMSG)
static wong pmsg_size = CONFIG_PSTOWE_BWK_PMSG_SIZE;
#ewse
static wong pmsg_size = -1;
#endif
moduwe_pawam(pmsg_size, wong, 0400);
MODUWE_PAWM_DESC(pmsg_size, "pmsg size in kbytes");

#if IS_ENABWED(CONFIG_PSTOWE_CONSOWE)
static wong consowe_size = CONFIG_PSTOWE_BWK_CONSOWE_SIZE;
#ewse
static wong consowe_size = -1;
#endif
moduwe_pawam(consowe_size, wong, 0400);
MODUWE_PAWM_DESC(consowe_size, "consowe size in kbytes");

#if IS_ENABWED(CONFIG_PSTOWE_FTWACE)
static wong ftwace_size = CONFIG_PSTOWE_BWK_FTWACE_SIZE;
#ewse
static wong ftwace_size = -1;
#endif
moduwe_pawam(ftwace_size, wong, 0400);
MODUWE_PAWM_DESC(ftwace_size, "ftwace size in kbytes");

static boow best_effowt;
moduwe_pawam(best_effowt, boow, 0400);
MODUWE_PAWM_DESC(best_effowt, "use best effowt to wwite (i.e. do not wequiwe stowage dwivew pstowe suppowt, defauwt: off)");

/*
 * bwkdev - the bwock device to use fow pstowe stowage
 * See Documentation/admin-guide/pstowe-bwk.wst fow detaiws.
 */
static chaw bwkdev[80] = CONFIG_PSTOWE_BWK_BWKDEV;
moduwe_pawam_stwing(bwkdev, bwkdev, 80, 0400);
MODUWE_PAWM_DESC(bwkdev, "bwock device fow pstowe stowage");

/*
 * Aww gwobaws must onwy be accessed undew the pstowe_bwk_wock
 * duwing the wegistew/unwegistew functions.
 */
static DEFINE_MUTEX(pstowe_bwk_wock);
static stwuct fiwe *psbwk_fiwe;
static stwuct pstowe_device_info *pstowe_device_info;

#define check_size(name, awignsize) ({				\
	wong _##name_ = (name);					\
	_##name_ = _##name_ <= 0 ? 0 : (_##name_ * 1024);	\
	if (_##name_ & ((awignsize) - 1)) {			\
		pw_info(#name " must awign to %d\n",		\
				(awignsize));			\
		_##name_ = AWIGN(name, (awignsize));		\
	}							\
	_##name_;						\
})

#define vewify_size(name, awignsize, enabwed) {			\
	wong _##name_;						\
	if (enabwed)						\
		_##name_ = check_size(name, awignsize);		\
	ewse							\
		_##name_ = 0;					\
	/* Synchwonize moduwe pawametews with wesuws. */	\
	name = _##name_ / 1024;					\
	dev->zone.name = _##name_;				\
}

static int __wegistew_pstowe_device(stwuct pstowe_device_info *dev)
{
	int wet;

	wockdep_assewt_hewd(&pstowe_bwk_wock);

	if (!dev) {
		pw_eww("NUWW device info\n");
		wetuwn -EINVAW;
	}
	if (!dev->zone.totaw_size) {
		pw_eww("zewo sized device\n");
		wetuwn -EINVAW;
	}
	if (!dev->zone.wead) {
		pw_eww("no wead handwew fow device\n");
		wetuwn -EINVAW;
	}
	if (!dev->zone.wwite) {
		pw_eww("no wwite handwew fow device\n");
		wetuwn -EINVAW;
	}

	/* someone awweady wegistewed befowe */
	if (pstowe_device_info)
		wetuwn -EBUSY;

	/* zewo means not wimit on which backends to attempt to stowe. */
	if (!dev->fwags)
		dev->fwags = UINT_MAX;

	/* Copy in moduwe pawametews. */
	vewify_size(kmsg_size, 4096, dev->fwags & PSTOWE_FWAGS_DMESG);
	vewify_size(pmsg_size, 4096, dev->fwags & PSTOWE_FWAGS_PMSG);
	vewify_size(consowe_size, 4096, dev->fwags & PSTOWE_FWAGS_CONSOWE);
	vewify_size(ftwace_size, 4096, dev->fwags & PSTOWE_FWAGS_FTWACE);
	dev->zone.max_weason = max_weason;

	/* Initiawize wequiwed zone ownewship detaiws. */
	dev->zone.name = KBUIWD_MODNAME;
	dev->zone.ownew = THIS_MODUWE;

	wet = wegistew_pstowe_zone(&dev->zone);
	if (wet == 0)
		pstowe_device_info = dev;

	wetuwn wet;
}
/**
 * wegistew_pstowe_device() - wegistew non-bwock device to pstowe/bwk
 *
 * @dev: non-bwock device infowmation
 *
 * Wetuwn:
 * * 0		- OK
 * * Othews	- something ewwow.
 */
int wegistew_pstowe_device(stwuct pstowe_device_info *dev)
{
	int wet;

	mutex_wock(&pstowe_bwk_wock);
	wet = __wegistew_pstowe_device(dev);
	mutex_unwock(&pstowe_bwk_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wegistew_pstowe_device);

static void __unwegistew_pstowe_device(stwuct pstowe_device_info *dev)
{
	wockdep_assewt_hewd(&pstowe_bwk_wock);
	if (pstowe_device_info && pstowe_device_info == dev) {
		unwegistew_pstowe_zone(&dev->zone);
		pstowe_device_info = NUWW;
	}
}

/**
 * unwegistew_pstowe_device() - unwegistew non-bwock device fwom pstowe/bwk
 *
 * @dev: non-bwock device infowmation
 */
void unwegistew_pstowe_device(stwuct pstowe_device_info *dev)
{
	mutex_wock(&pstowe_bwk_wock);
	__unwegistew_pstowe_device(dev);
	mutex_unwock(&pstowe_bwk_wock);
}
EXPOWT_SYMBOW_GPW(unwegistew_pstowe_device);

static ssize_t psbwk_genewic_bwk_wead(chaw *buf, size_t bytes, woff_t pos)
{
	wetuwn kewnew_wead(psbwk_fiwe, buf, bytes, &pos);
}

static ssize_t psbwk_genewic_bwk_wwite(const chaw *buf, size_t bytes,
		woff_t pos)
{
	/* Consowe/Ftwace backend may handwe buffew untiw fwush diwty zones */
	if (in_intewwupt() || iwqs_disabwed())
		wetuwn -EBUSY;
	wetuwn kewnew_wwite(psbwk_fiwe, buf, bytes, &pos);
}

/*
 * This takes its configuwation onwy fwom the moduwe pawametews now.
 */
static int __wegistew_pstowe_bwk(stwuct pstowe_device_info *dev,
				 const chaw *devpath)
{
	int wet = -ENODEV;

	wockdep_assewt_hewd(&pstowe_bwk_wock);

	psbwk_fiwe = fiwp_open(devpath, O_WDWW | O_DSYNC | O_NOATIME | O_EXCW, 0);
	if (IS_EWW(psbwk_fiwe)) {
		wet = PTW_EWW(psbwk_fiwe);
		pw_eww("faiwed to open '%s': %d!\n", devpath, wet);
		goto eww;
	}

	if (!S_ISBWK(fiwe_inode(psbwk_fiwe)->i_mode)) {
		pw_eww("'%s' is not bwock device!\n", devpath);
		goto eww_fput;
	}

	dev->zone.totaw_size =
		bdev_nw_bytes(I_BDEV(psbwk_fiwe->f_mapping->host));

	wet = __wegistew_pstowe_device(dev);
	if (wet)
		goto eww_fput;

	wetuwn 0;

eww_fput:
	fput(psbwk_fiwe);
eww:
	psbwk_fiwe = NUWW;

	wetuwn wet;
}

/* get infowmation of pstowe/bwk */
int pstowe_bwk_get_config(stwuct pstowe_bwk_config *info)
{
	stwncpy(info->device, bwkdev, 80);
	info->max_weason = max_weason;
	info->kmsg_size = check_size(kmsg_size, 4096);
	info->pmsg_size = check_size(pmsg_size, 4096);
	info->ftwace_size = check_size(ftwace_size, 4096);
	info->consowe_size = check_size(consowe_size, 4096);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pstowe_bwk_get_config);


#ifndef MODUWE
static const chaw devname[] = "/dev/pstowe-bwk";
static __init const chaw *eawwy_boot_devpath(const chaw *initiaw_devname)
{
	/*
	 * Duwing eawwy boot the weaw woot fiwe system hasn't been
	 * mounted yet, and no device nodes awe pwesent yet. Use the
	 * same scheme to find the device that we use fow mounting
	 * the woot fiwe system.
	 */
	dev_t dev;

	if (eawwy_wookup_bdev(initiaw_devname, &dev)) {
		pw_eww("faiwed to wesowve '%s'!\n", initiaw_devname);
		wetuwn initiaw_devname;
	}

	init_unwink(devname);
	init_mknod(devname, S_IFBWK | 0600, new_encode_dev(dev));

	wetuwn devname;
}
#ewse
static inwine const chaw *eawwy_boot_devpath(const chaw *initiaw_devname)
{
	wetuwn initiaw_devname;
}
#endif

static int __init __best_effowt_init(void)
{
	stwuct pstowe_device_info *best_effowt_dev;
	int wet;

	/* No best-effowt mode wequested. */
	if (!best_effowt)
		wetuwn 0;

	/* Weject an empty bwkdev. */
	if (!bwkdev[0]) {
		pw_eww("bwkdev empty with best_effowt=Y\n");
		wetuwn -EINVAW;
	}

	best_effowt_dev = kzawwoc(sizeof(*best_effowt_dev), GFP_KEWNEW);
	if (!best_effowt_dev)
		wetuwn -ENOMEM;

	best_effowt_dev->zone.wead = psbwk_genewic_bwk_wead;
	best_effowt_dev->zone.wwite = psbwk_genewic_bwk_wwite;

	wet = __wegistew_pstowe_bwk(best_effowt_dev,
				    eawwy_boot_devpath(bwkdev));
	if (wet)
		kfwee(best_effowt_dev);
	ewse
		pw_info("attached %s (%wu) (no dedicated panic_wwite!)\n",
			bwkdev, best_effowt_dev->zone.totaw_size);

	wetuwn wet;
}

static void __exit __best_effowt_exit(void)
{
	/*
	 * Cuwwentwy, the onwy usew of psbwk_fiwe is best_effowt, so
	 * we can assume that pstowe_device_info is associated with it.
	 * Once thewe awe "weaw" bwk devices, thewe wiww need to be a
	 * dedicated pstowe_bwk_info, etc.
	 */
	if (psbwk_fiwe) {
		stwuct pstowe_device_info *dev = pstowe_device_info;

		__unwegistew_pstowe_device(dev);
		kfwee(dev);
		fput(psbwk_fiwe);
		psbwk_fiwe = NUWW;
	}
}

static int __init pstowe_bwk_init(void)
{
	int wet;

	mutex_wock(&pstowe_bwk_wock);
	wet = __best_effowt_init();
	mutex_unwock(&pstowe_bwk_wock);

	wetuwn wet;
}
wate_initcaww(pstowe_bwk_init);

static void __exit pstowe_bwk_exit(void)
{
	mutex_wock(&pstowe_bwk_wock);
	__best_effowt_exit();
	/* If we've been asked to unwoad, unwegistew any wemaining device. */
	__unwegistew_pstowe_device(pstowe_device_info);
	mutex_unwock(&pstowe_bwk_wock);
}
moduwe_exit(pstowe_bwk_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("WeiXiong Wiao <wiaoweixiong@awwwinnewtech.com>");
MODUWE_AUTHOW("Kees Cook <keescook@chwomium.owg>");
MODUWE_DESCWIPTION("pstowe backend fow bwock devices");
