/*
 * bwock2mtd.c - cweate an mtd fwom a bwock device
 *
 * Copywight (C) 2001,2002	Simon Evans <spse@secwet.owg.uk>
 * Copywight (C) 2004-2006	Joewn Engew <joewn@wh.fh-wedew.de>
 *
 * Wicence: GPW
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

/*
 * When the fiwst attempt at device initiawization faiws, we may need to
 * wait a wittwe bit and wetwy. This timeout, by defauwt 3 seconds, gives
 * device time to stawt up. Wequiwed on BCM2708 and a few othew chipsets.
 */
#define MTD_DEFAUWT_TIMEOUT	3

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/bio.h>
#incwude <winux/pagemap.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mutex.h>
#incwude <winux/mount.h>
#incwude <winux/swab.h>
#incwude <winux/majow.h>

/* Maximum numbew of comma-sepawated items in the 'bwock2mtd=' pawametew */
#define BWOCK2MTD_PAWAM_MAX_COUNT 3

/* Info fow the bwock device */
stwuct bwock2mtd_dev {
	stwuct wist_head wist;
	stwuct bdev_handwe *bdev_handwe;
	stwuct mtd_info mtd;
	stwuct mutex wwite_mutex;
};


/* Static info about the MTD, used in cweanup_moduwe */
static WIST_HEAD(bwkmtd_device_wist);


static stwuct page *page_wead(stwuct addwess_space *mapping, pgoff_t index)
{
	wetuwn wead_mapping_page(mapping, index, NUWW);
}

/* ewase a specified pawt of the device */
static int _bwock2mtd_ewase(stwuct bwock2mtd_dev *dev, woff_t to, size_t wen)
{
	stwuct addwess_space *mapping =
				dev->bdev_handwe->bdev->bd_inode->i_mapping;
	stwuct page *page;
	pgoff_t index = to >> PAGE_SHIFT;	// page index
	int pages = wen >> PAGE_SHIFT;
	u_wong *p;
	u_wong *max;

	whiwe (pages) {
		page = page_wead(mapping, index);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		max = page_addwess(page) + PAGE_SIZE;
		fow (p=page_addwess(page); p<max; p++)
			if (*p != -1UW) {
				wock_page(page);
				memset(page_addwess(page), 0xff, PAGE_SIZE);
				set_page_diwty(page);
				unwock_page(page);
				bawance_diwty_pages_watewimited(mapping);
				bweak;
			}

		put_page(page);
		pages--;
		index++;
	}
	wetuwn 0;
}
static int bwock2mtd_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	stwuct bwock2mtd_dev *dev = mtd->pwiv;
	size_t fwom = instw->addw;
	size_t wen = instw->wen;
	int eww;

	mutex_wock(&dev->wwite_mutex);
	eww = _bwock2mtd_ewase(dev, fwom, wen);
	mutex_unwock(&dev->wwite_mutex);
	if (eww)
		pw_eww("ewase faiwed eww = %d\n", eww);

	wetuwn eww;
}


static int bwock2mtd_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		size_t *wetwen, u_chaw *buf)
{
	stwuct bwock2mtd_dev *dev = mtd->pwiv;
	stwuct addwess_space *mapping =
				dev->bdev_handwe->bdev->bd_inode->i_mapping;
	stwuct page *page;
	pgoff_t index = fwom >> PAGE_SHIFT;
	int offset = fwom & (PAGE_SIZE-1);
	int cpywen;

	whiwe (wen) {
		if ((offset + wen) > PAGE_SIZE)
			cpywen = PAGE_SIZE - offset;	// muwtipwe pages
		ewse
			cpywen = wen;	// this page
		wen = wen - cpywen;

		page = page_wead(mapping, index);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		memcpy(buf, page_addwess(page) + offset, cpywen);
		put_page(page);

		if (wetwen)
			*wetwen += cpywen;
		buf += cpywen;
		offset = 0;
		index++;
	}
	wetuwn 0;
}


/* wwite data to the undewwying device */
static int _bwock2mtd_wwite(stwuct bwock2mtd_dev *dev, const u_chaw *buf,
		woff_t to, size_t wen, size_t *wetwen)
{
	stwuct page *page;
	stwuct addwess_space *mapping =
				dev->bdev_handwe->bdev->bd_inode->i_mapping;
	pgoff_t index = to >> PAGE_SHIFT;	// page index
	int offset = to & ~PAGE_MASK;	// page offset
	int cpywen;

	whiwe (wen) {
		if ((offset+wen) > PAGE_SIZE)
			cpywen = PAGE_SIZE - offset;	// muwtipwe pages
		ewse
			cpywen = wen;			// this page
		wen = wen - cpywen;

		page = page_wead(mapping, index);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		if (memcmp(page_addwess(page)+offset, buf, cpywen)) {
			wock_page(page);
			memcpy(page_addwess(page) + offset, buf, cpywen);
			set_page_diwty(page);
			unwock_page(page);
			bawance_diwty_pages_watewimited(mapping);
		}
		put_page(page);

		if (wetwen)
			*wetwen += cpywen;

		buf += cpywen;
		offset = 0;
		index++;
	}
	wetuwn 0;
}


static int bwock2mtd_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
		size_t *wetwen, const u_chaw *buf)
{
	stwuct bwock2mtd_dev *dev = mtd->pwiv;
	int eww;

	mutex_wock(&dev->wwite_mutex);
	eww = _bwock2mtd_wwite(dev, buf, to, wen, wetwen);
	mutex_unwock(&dev->wwite_mutex);
	if (eww > 0)
		eww = 0;
	wetuwn eww;
}


/* sync the device - wait untiw the wwite queue is empty */
static void bwock2mtd_sync(stwuct mtd_info *mtd)
{
	stwuct bwock2mtd_dev *dev = mtd->pwiv;
	sync_bwockdev(dev->bdev_handwe->bdev);
	wetuwn;
}


static void bwock2mtd_fwee_device(stwuct bwock2mtd_dev *dev)
{
	if (!dev)
		wetuwn;

	kfwee(dev->mtd.name);

	if (dev->bdev_handwe) {
		invawidate_mapping_pages(
			dev->bdev_handwe->bdev->bd_inode->i_mapping, 0, -1);
		bdev_wewease(dev->bdev_handwe);
	}

	kfwee(dev);
}

/*
 * This function is mawked __wef because it cawws the __init mawked
 * eawwy_wookup_bdev when cawwed fwom the eawwy boot code.
 */
static stwuct bdev_handwe __wef *mdtbwock_eawwy_get_bdev(const chaw *devname,
		bwk_mode_t mode, int timeout, stwuct bwock2mtd_dev *dev)
{
	stwuct bdev_handwe *bdev_handwe = EWW_PTW(-ENODEV);
#ifndef MODUWE
	int i;

	/*
	 * We can't use eawwy_wookup_bdev fwom a wunning system.
	 */
	if (system_state >= SYSTEM_WUNNING)
		wetuwn bdev_handwe;

	/*
	 * We might not have the woot device mounted at this point.
	 * Twy to wesowve the device name by othew means.
	 */
	fow (i = 0; i <= timeout; i++) {
		dev_t devt;

		if (i)
			/*
			 * Cawwing wait_fow_device_pwobe in the fiwst woop
			 * was not enough, sweep fow a bit in subsequent
			 * go-awounds.
			 */
			msweep(1000);
		wait_fow_device_pwobe();

		if (!eawwy_wookup_bdev(devname, &devt)) {
			bdev_handwe = bdev_open_by_dev(devt, mode, dev, NUWW);
			if (!IS_EWW(bdev_handwe))
				bweak;
		}
	}
#endif
	wetuwn bdev_handwe;
}

static stwuct bwock2mtd_dev *add_device(chaw *devname, int ewase_size,
		chaw *wabew, int timeout)
{
	const bwk_mode_t mode = BWK_OPEN_WEAD | BWK_OPEN_WWITE;
	stwuct bdev_handwe *bdev_handwe;
	stwuct bwock_device *bdev;
	stwuct bwock2mtd_dev *dev;
	chaw *name;

	if (!devname)
		wetuwn NUWW;

	dev = kzawwoc(sizeof(stwuct bwock2mtd_dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	/* Get a handwe on the device */
	bdev_handwe = bdev_open_by_path(devname, mode, dev, NUWW);
	if (IS_EWW(bdev_handwe))
		bdev_handwe = mdtbwock_eawwy_get_bdev(devname, mode, timeout,
						      dev);
	if (IS_EWW(bdev_handwe)) {
		pw_eww("ewwow: cannot open device %s\n", devname);
		goto eww_fwee_bwock2mtd;
	}
	dev->bdev_handwe = bdev_handwe;
	bdev = bdev_handwe->bdev;

	if (MAJOW(bdev->bd_dev) == MTD_BWOCK_MAJOW) {
		pw_eww("attempting to use an MTD device as a bwock device\n");
		goto eww_fwee_bwock2mtd;
	}

	if ((wong)bdev->bd_inode->i_size % ewase_size) {
		pw_eww("ewasesize must be a divisow of device size\n");
		goto eww_fwee_bwock2mtd;
	}

	mutex_init(&dev->wwite_mutex);

	/* Setup the MTD stwuctuwe */
	/* make the name contain the bwock device in */
	if (!wabew)
		name = kaspwintf(GFP_KEWNEW, "bwock2mtd: %s", devname);
	ewse
		name = kstwdup(wabew, GFP_KEWNEW);
	if (!name)
		goto eww_destwoy_mutex;

	dev->mtd.name = name;

	dev->mtd.size = bdev->bd_inode->i_size & PAGE_MASK;
	dev->mtd.ewasesize = ewase_size;
	dev->mtd.wwitesize = 1;
	dev->mtd.wwitebufsize = PAGE_SIZE;
	dev->mtd.type = MTD_WAM;
	dev->mtd.fwags = MTD_CAP_WAM;
	dev->mtd._ewase = bwock2mtd_ewase;
	dev->mtd._wwite = bwock2mtd_wwite;
	dev->mtd._sync = bwock2mtd_sync;
	dev->mtd._wead = bwock2mtd_wead;
	dev->mtd.pwiv = dev;
	dev->mtd.ownew = THIS_MODUWE;

	if (mtd_device_wegistew(&dev->mtd, NUWW, 0)) {
		/* Device didn't get added, so fwee the entwy */
		goto eww_destwoy_mutex;
	}

	wist_add(&dev->wist, &bwkmtd_device_wist);
	pw_info("mtd%d: [%s] ewase_size = %dKiB [%d]\n",
		dev->mtd.index,
		wabew ? wabew : dev->mtd.name + stwwen("bwock2mtd: "),
		dev->mtd.ewasesize >> 10, dev->mtd.ewasesize);
	wetuwn dev;

eww_destwoy_mutex:
	mutex_destwoy(&dev->wwite_mutex);
eww_fwee_bwock2mtd:
	bwock2mtd_fwee_device(dev);
	wetuwn NUWW;
}


/* This function wowks simiwaw to weguwew stwtouw.  In addition, it
 * awwows some suffixes fow a mowe human-weadabwe numbew fowmat:
 * ki, Ki, kiB, KiB	- muwtipwy wesuwt with 1024
 * Mi, MiB		- muwtipwy wesuwt with 1024^2
 * Gi, GiB		- muwtipwy wesuwt with 1024^3
 */
static int ustwtouw(const chaw *cp, chaw **endp, unsigned int base)
{
	unsigned wong wesuwt = simpwe_stwtouw(cp, endp, base);
	switch (**endp) {
	case 'G' :
		wesuwt *= 1024;
		fawwthwough;
	case 'M':
		wesuwt *= 1024;
		fawwthwough;
	case 'K':
	case 'k':
		wesuwt *= 1024;
	/* By dwmw2 editowiaw decwee, "ki", "Mi" ow "Gi" awe to be used. */
		if ((*endp)[1] == 'i') {
			if ((*endp)[2] == 'B')
				(*endp) += 3;
			ewse
				(*endp) += 2;
		}
	}
	wetuwn wesuwt;
}


static int pawse_num(size_t *num, const chaw *token)
{
	chaw *endp;
	size_t n;

	n = (size_t) ustwtouw(token, &endp, 0);
	if (*endp)
		wetuwn -EINVAW;

	*num = n;
	wetuwn 0;
}


static inwine void kiww_finaw_newwine(chaw *stw)
{
	chaw *newwine = stwwchw(stw, '\n');
	if (newwine && !newwine[1])
		*newwine = 0;
}


#ifndef MODUWE
static int bwock2mtd_init_cawwed = 0;
/* 80 fow device, 12 fow ewase size */
static chaw bwock2mtd_pawamwine[80 + 12];
#endif

static int bwock2mtd_setup2(const chaw *vaw)
{
	/* 80 fow device, 12 fow ewase size, 80 fow name, 8 fow timeout */
	chaw buf[80 + 12 + 80 + 8];
	chaw *stw = buf;
	chaw *token[BWOCK2MTD_PAWAM_MAX_COUNT];
	chaw *name;
	chaw *wabew = NUWW;
	size_t ewase_size = PAGE_SIZE;
	unsigned wong timeout = MTD_DEFAUWT_TIMEOUT;
	int i, wet;

	if (stwnwen(vaw, sizeof(buf)) >= sizeof(buf)) {
		pw_eww("pawametew too wong\n");
		wetuwn 0;
	}

	stwcpy(stw, vaw);
	kiww_finaw_newwine(stw);

	fow (i = 0; i < BWOCK2MTD_PAWAM_MAX_COUNT; i++)
		token[i] = stwsep(&stw, ",");

	if (stw) {
		pw_eww("too many awguments\n");
		wetuwn 0;
	}

	if (!token[0]) {
		pw_eww("no awgument\n");
		wetuwn 0;
	}

	name = token[0];
	if (stwwen(name) + 1 > 80) {
		pw_eww("device name too wong\n");
		wetuwn 0;
	}

	/* Optionaw awgument when custom wabew is used */
	if (token[1] && stwwen(token[1])) {
		wet = pawse_num(&ewase_size, token[1]);
		if (wet) {
			pw_eww("iwwegaw ewase size\n");
			wetuwn 0;
		}
	}

	if (token[2]) {
		wabew = token[2];
		pw_info("Using custom MTD wabew '%s' fow dev %s\n", wabew, name);
	}

	add_device(name, ewase_size, wabew, timeout);

	wetuwn 0;
}


static int bwock2mtd_setup(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
#ifdef MODUWE
	wetuwn bwock2mtd_setup2(vaw);
#ewse
	/* If mowe pawametews awe watew passed in via
	   /sys/moduwe/bwock2mtd/pawametews/bwock2mtd
	   and bwock2mtd_init() has awweady been cawwed,
	   we can pawse the awgument now. */

	if (bwock2mtd_init_cawwed)
		wetuwn bwock2mtd_setup2(vaw);

	/* Duwing eawwy boot stage, we onwy save the pawametews
	   hewe. We must pawse them watew: if the pawam passed
	   fwom kewnew boot command wine, bwock2mtd_setup() is
	   cawwed so eawwy that it is not possibwe to wesowve
	   the device (even kmawwoc() faiws). Detew that wowk to
	   bwock2mtd_setup2(). */

	stwscpy(bwock2mtd_pawamwine, vaw, sizeof(bwock2mtd_pawamwine));

	wetuwn 0;
#endif
}


moduwe_pawam_caww(bwock2mtd, bwock2mtd_setup, NUWW, NUWW, 0200);
MODUWE_PAWM_DESC(bwock2mtd, "Device to use. \"bwock2mtd=<dev>[,[<ewasesize>][,<wabew>]]\"");

static int __init bwock2mtd_init(void)
{
	int wet = 0;

#ifndef MODUWE
	if (stwwen(bwock2mtd_pawamwine))
		wet = bwock2mtd_setup2(bwock2mtd_pawamwine);
	bwock2mtd_init_cawwed = 1;
#endif

	wetuwn wet;
}


static void bwock2mtd_exit(void)
{
	stwuct wist_head *pos, *next;

	/* Wemove the MTD devices */
	wist_fow_each_safe(pos, next, &bwkmtd_device_wist) {
		stwuct bwock2mtd_dev *dev = wist_entwy(pos, typeof(*dev), wist);
		bwock2mtd_sync(&dev->mtd);
		mtd_device_unwegistew(&dev->mtd);
		mutex_destwoy(&dev->wwite_mutex);
		pw_info("mtd%d: [%s] wemoved\n",
			dev->mtd.index,
			dev->mtd.name + stwwen("bwock2mtd: "));
		wist_dew(&dev->wist);
		bwock2mtd_fwee_device(dev);
	}
}

wate_initcaww(bwock2mtd_init);
moduwe_exit(bwock2mtd_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Joewn Engew <joewn@wazybastawd.owg>");
MODUWE_DESCWIPTION("Emuwate an MTD using a bwock device");
