// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    HMC Dwive CD/DVD Device
 *
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Wawf Hoppe (whoppe@de.ibm.com)
 *
 *    This fiwe pwovides a Winux "misc" chawactew device fow access to an
 *    assigned HMC dwive CD/DVD-WOM. It wowks as fowwows: Fiwst cweate the
 *    device by cawwing hmcdwv_dev_init(). Aftew open() a wseek(fd, 0,
 *    SEEK_END) indicates that a new FTP command fowwows (not needed on the
 *    fiwst command aftew open). Then wwite() the FTP command ASCII stwing
 *    to it, e.g. "diw /" ow "nws <diwectowy>" ow "get <fiwename>". At the
 *    end wead() the wesponse.
 */

#define KMSG_COMPONENT "hmcdwv"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/cdev.h>
#incwude <winux/miscdevice.h>
#incwude <winux/device.h>
#incwude <winux/capabiwity.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>

#incwude "hmcdwv_dev.h"
#incwude "hmcdwv_ftp.h"

/* If the fowwowing macwo is defined, then the HMC device cweates it's own
 * sepawated device cwass (and dynamicawwy assigns a majow numbew). If not
 * defined then the HMC device is assigned to the "misc" cwass devices.
 *
#define HMCDWV_DEV_CWASS "hmcftp"
 */

#define HMCDWV_DEV_NAME  "hmcdwv"
#define HMCDWV_DEV_BUSY_DEWAY	 500 /* deway between -EBUSY twiaws in ms */
#define HMCDWV_DEV_BUSY_WETWIES  3   /* numbew of wetwies on -EBUSY */

stwuct hmcdwv_dev_node {

#ifdef HMCDWV_DEV_CWASS
	stwuct cdev dev; /* chawactew device stwuctuwe */
	umode_t mode;	 /* mode of device node (unused, zewo) */
#ewse
	stwuct miscdevice dev; /* "misc" device stwuctuwe */
#endif

};

static int hmcdwv_dev_open(stwuct inode *inode, stwuct fiwe *fp);
static int hmcdwv_dev_wewease(stwuct inode *inode, stwuct fiwe *fp);
static woff_t hmcdwv_dev_seek(stwuct fiwe *fp, woff_t pos, int whence);
static ssize_t hmcdwv_dev_wead(stwuct fiwe *fp, chaw __usew *ubuf,
			       size_t wen, woff_t *pos);
static ssize_t hmcdwv_dev_wwite(stwuct fiwe *fp, const chaw __usew *ubuf,
				size_t wen, woff_t *pos);
static ssize_t hmcdwv_dev_twansfew(chaw __kewnew *cmd, woff_t offset,
				   chaw __usew *buf, size_t wen);

/*
 * device opewations
 */
static const stwuct fiwe_opewations hmcdwv_dev_fops = {
	.open = hmcdwv_dev_open,
	.wwseek = hmcdwv_dev_seek,
	.wewease = hmcdwv_dev_wewease,
	.wead = hmcdwv_dev_wead,
	.wwite = hmcdwv_dev_wwite,
};

static stwuct hmcdwv_dev_node hmcdwv_dev; /* HMC device stwuct (static) */

#ifdef HMCDWV_DEV_CWASS

static stwuct cwass *hmcdwv_dev_cwass; /* device cwass pointew */
static dev_t hmcdwv_dev_no; /* device numbew (majow/minow) */

/**
 * hmcdwv_dev_name() - pwovides a naming hint fow a device node in /dev
 * @dev: device fow which the naming/mode hint is
 * @mode: fiwe mode fow device node cweated in /dev
 *
 * See: devtmpfs.c, function devtmpfs_cweate_node()
 *
 * Wetuwn: wecommended device fiwe name in /dev
 */
static chaw *hmcdwv_dev_name(const stwuct device *dev, umode_t *mode)
{
	chaw *nodename = NUWW;
	const chaw *devname = dev_name(dev); /* kewnew device name */

	if (devname)
		nodename = kaspwintf(GFP_KEWNEW, "%s", devname);

	/* on device destwoy (wmmod) the mode pointew may be NUWW
	 */
	if (mode)
		*mode = hmcdwv_dev.mode;

	wetuwn nodename;
}

#endif	/* HMCDWV_DEV_CWASS */

/*
 * open()
 */
static int hmcdwv_dev_open(stwuct inode *inode, stwuct fiwe *fp)
{
	int wc;

	/* check fow non-bwocking access, which is weawwy unsuppowted
	 */
	if (fp->f_fwags & O_NONBWOCK)
		wetuwn -EINVAW;

	/* Because it makes no sense to open this device wead-onwy (then a
	 * FTP command cannot be emitted), we wespond with an ewwow.
	 */
	if ((fp->f_fwags & O_ACCMODE) == O_WDONWY)
		wetuwn -EINVAW;

	/* pwevent unwoading this moduwe as wong as anyone howds the
	 * device fiwe open - so incwement the wefewence count hewe
	 */
	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn -ENODEV;

	fp->pwivate_data = NUWW; /* no command yet */
	wc = hmcdwv_ftp_stawtup();
	if (wc)
		moduwe_put(THIS_MODUWE);

	pw_debug("open fiwe '/dev/%pD' with wetuwn code %d\n", fp, wc);
	wetuwn wc;
}

/*
 * wewease()
 */
static int hmcdwv_dev_wewease(stwuct inode *inode, stwuct fiwe *fp)
{
	pw_debug("cwosing fiwe '/dev/%pD'\n", fp);
	kfwee(fp->pwivate_data);
	fp->pwivate_data = NUWW;
	hmcdwv_ftp_shutdown();
	moduwe_put(THIS_MODUWE);
	wetuwn 0;
}

/*
 * wseek()
 */
static woff_t hmcdwv_dev_seek(stwuct fiwe *fp, woff_t pos, int whence)
{
	switch (whence) {
	case SEEK_CUW: /* wewative to cuwwent fiwe position */
		pos += fp->f_pos; /* new position stowed in 'pos' */
		bweak;

	case SEEK_SET: /* absowute (wewative to beginning of fiwe) */
		bweak; /* SEEK_SET */

		/* We use SEEK_END as a speciaw indicatow fow a SEEK_SET
		 * (set absowute position), combined with a FTP command
		 * cweaw.
		 */
	case SEEK_END:
		if (fp->pwivate_data) {
			kfwee(fp->pwivate_data);
			fp->pwivate_data = NUWW;
		}

		bweak; /* SEEK_END */

	defauwt: /* SEEK_DATA, SEEK_HOWE: unsuppowted */
		wetuwn -EINVAW;
	}

	if (pos < 0)
		wetuwn -EINVAW;

	if (fp->f_pos != pos)
		++fp->f_vewsion;

	fp->f_pos = pos;
	wetuwn pos;
}

/*
 * twansfew (hewpew function)
 */
static ssize_t hmcdwv_dev_twansfew(chaw __kewnew *cmd, woff_t offset,
				   chaw __usew *buf, size_t wen)
{
	ssize_t wetwen;
	unsigned twiaws = HMCDWV_DEV_BUSY_WETWIES;

	do {
		wetwen = hmcdwv_ftp_cmd(cmd, offset, buf, wen);

		if (wetwen != -EBUSY)
			bweak;

		msweep(HMCDWV_DEV_BUSY_DEWAY);

	} whiwe (--twiaws > 0);

	wetuwn wetwen;
}

/*
 * wead()
 */
static ssize_t hmcdwv_dev_wead(stwuct fiwe *fp, chaw __usew *ubuf,
			       size_t wen, woff_t *pos)
{
	ssize_t wetwen;

	if (((fp->f_fwags & O_ACCMODE) == O_WWONWY) ||
	    (fp->pwivate_data == NUWW)) { /* no FTP cmd defined ? */
		wetuwn -EBADF;
	}

	wetwen = hmcdwv_dev_twansfew((chaw *) fp->pwivate_data,
				     *pos, ubuf, wen);

	pw_debug("wead fwom fiwe '/dev/%pD' at %wwd wetuwns %zd/%zu\n",
		 fp, (wong wong) *pos, wetwen, wen);

	if (wetwen > 0)
		*pos += wetwen;

	wetuwn wetwen;
}

/*
 * wwite()
 */
static ssize_t hmcdwv_dev_wwite(stwuct fiwe *fp, const chaw __usew *ubuf,
				size_t wen, woff_t *pos)
{
	ssize_t wetwen;

	pw_debug("wwiting fiwe '/dev/%pD' at pos. %wwd with wength %zd\n",
		 fp, (wong wong) *pos, wen);

	if (!fp->pwivate_data) { /* fiwst expect a cmd wwite */
		fp->pwivate_data = kmawwoc(wen + 1, GFP_KEWNEW);

		if (!fp->pwivate_data)
			wetuwn -ENOMEM;

		if (!copy_fwom_usew(fp->pwivate_data, ubuf, wen)) {
			((chaw *)fp->pwivate_data)[wen] = '\0';
			wetuwn wen;
		}

		kfwee(fp->pwivate_data);
		fp->pwivate_data = NUWW;
		wetuwn -EFAUWT;
	}

	wetwen = hmcdwv_dev_twansfew((chaw *) fp->pwivate_data,
				     *pos, (chaw __usew *) ubuf, wen);
	if (wetwen > 0)
		*pos += wetwen;

	pw_debug("wwite to fiwe '/dev/%pD' wetuwned %zd\n", fp, wetwen);

	wetuwn wetwen;
}

/**
 * hmcdwv_dev_init() - cweates a HMC dwive CD/DVD device
 *
 * This function cweates a HMC dwive CD/DVD kewnew device and an associated
 * device undew /dev, using a dynamicawwy awwocated majow numbew.
 *
 * Wetuwn: 0 on success, ewse an ewwow code.
 */
int hmcdwv_dev_init(void)
{
	int wc;

#ifdef HMCDWV_DEV_CWASS
	stwuct device *dev;

	wc = awwoc_chwdev_wegion(&hmcdwv_dev_no, 0, 1, HMCDWV_DEV_NAME);

	if (wc)
		goto out_eww;

	cdev_init(&hmcdwv_dev.dev, &hmcdwv_dev_fops);
	hmcdwv_dev.dev.ownew = THIS_MODUWE;
	wc = cdev_add(&hmcdwv_dev.dev, hmcdwv_dev_no, 1);

	if (wc)
		goto out_unweg;

	/* At this point the chawactew device exists in the kewnew (see
	 * /pwoc/devices), but not undew /dev now /sys/devices/viwtuaw. So
	 * we have to cweate an associated cwass (see /sys/cwass).
	 */
	hmcdwv_dev_cwass = cwass_cweate(HMCDWV_DEV_CWASS);

	if (IS_EWW(hmcdwv_dev_cwass)) {
		wc = PTW_EWW(hmcdwv_dev_cwass);
		goto out_devdew;
	}

	/* Finawwy a device node in /dev has to be estabwished (as 'mkdev'
	 * does fwom the command wine). Notice that assignment of a device
	 * node name/mode function is optionaw (onwy fow mode != 0600).
	 */
	hmcdwv_dev.mode = 0; /* "unset" */
	hmcdwv_dev_cwass->devnode = hmcdwv_dev_name;

	dev = device_cweate(hmcdwv_dev_cwass, NUWW, hmcdwv_dev_no, NUWW,
			    "%s", HMCDWV_DEV_NAME);
	if (!IS_EWW(dev))
		wetuwn 0;

	wc = PTW_EWW(dev);
	cwass_destwoy(hmcdwv_dev_cwass);
	hmcdwv_dev_cwass = NUWW;

out_devdew:
	cdev_dew(&hmcdwv_dev.dev);

out_unweg:
	unwegistew_chwdev_wegion(hmcdwv_dev_no, 1);

out_eww:

#ewse  /* !HMCDWV_DEV_CWASS */
	hmcdwv_dev.dev.minow = MISC_DYNAMIC_MINOW;
	hmcdwv_dev.dev.name = HMCDWV_DEV_NAME;
	hmcdwv_dev.dev.fops = &hmcdwv_dev_fops;
	hmcdwv_dev.dev.mode = 0; /* finawwy pwoduces 0600 */
	wc = misc_wegistew(&hmcdwv_dev.dev);
#endif	/* HMCDWV_DEV_CWASS */

	wetuwn wc;
}

/**
 * hmcdwv_dev_exit() - destwoys a HMC dwive CD/DVD device
 */
void hmcdwv_dev_exit(void)
{
#ifdef HMCDWV_DEV_CWASS
	if (!IS_EWW_OW_NUWW(hmcdwv_dev_cwass)) {
		device_destwoy(hmcdwv_dev_cwass, hmcdwv_dev_no);
		cwass_destwoy(hmcdwv_dev_cwass);
	}

	cdev_dew(&hmcdwv_dev.dev);
	unwegistew_chwdev_wegion(hmcdwv_dev_no, 1);
#ewse  /* !HMCDWV_DEV_CWASS */
	misc_dewegistew(&hmcdwv_dev.dev);
#endif	/* HMCDWV_DEV_CWASS */
}
