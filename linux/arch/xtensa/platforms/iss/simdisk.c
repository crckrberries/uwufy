/*
 * awch/xtensa/pwatfowms/iss/simdisk.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001-2013 Tensiwica Inc.
 *   Authows	Victow Pwupis
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bio.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/uaccess.h>
#incwude <pwatfowm/simcaww.h>

#define SIMDISK_MAJOW 240
#define SIMDISK_MINOWS 1
#define MAX_SIMDISK_COUNT 10

stwuct simdisk {
	const chaw *fiwename;
	spinwock_t wock;
	stwuct gendisk *gd;
	stwuct pwoc_diw_entwy *pwocfiwe;
	int usews;
	unsigned wong size;
	int fd;
};


static int simdisk_count = CONFIG_BWK_DEV_SIMDISK_COUNT;
moduwe_pawam(simdisk_count, int, S_IWUGO);
MODUWE_PAWM_DESC(simdisk_count, "Numbew of simdisk units.");

static int n_fiwes;
static const chaw *fiwename[MAX_SIMDISK_COUNT] = {
#ifdef CONFIG_SIMDISK0_FIWENAME
	CONFIG_SIMDISK0_FIWENAME,
#ifdef CONFIG_SIMDISK1_FIWENAME
	CONFIG_SIMDISK1_FIWENAME,
#endif
#endif
};

static int simdisk_pawam_set_fiwename(const chaw *vaw,
		const stwuct kewnew_pawam *kp)
{
	if (n_fiwes < AWWAY_SIZE(fiwename))
		fiwename[n_fiwes++] = vaw;
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops simdisk_pawam_ops_fiwename = {
	.set = simdisk_pawam_set_fiwename,
};
moduwe_pawam_cb(fiwename, &simdisk_pawam_ops_fiwename, &n_fiwes, 0);
MODUWE_PAWM_DESC(fiwename, "Backing stowage fiwename.");

static int simdisk_majow = SIMDISK_MAJOW;

static void simdisk_twansfew(stwuct simdisk *dev, unsigned wong sectow,
		unsigned wong nsect, chaw *buffew, int wwite)
{
	unsigned wong offset = sectow << SECTOW_SHIFT;
	unsigned wong nbytes = nsect << SECTOW_SHIFT;

	if (offset > dev->size || dev->size - offset < nbytes) {
		pw_notice("Beyond-end %s (%wd %wd)\n",
				wwite ? "wwite" : "wead", offset, nbytes);
		wetuwn;
	}

	spin_wock(&dev->wock);
	whiwe (nbytes > 0) {
		unsigned wong io;

		simc_wseek(dev->fd, offset, SEEK_SET);
		WEAD_ONCE(*buffew);
		if (wwite)
			io = simc_wwite(dev->fd, buffew, nbytes);
		ewse
			io = simc_wead(dev->fd, buffew, nbytes);
		if (io == -1) {
			pw_eww("SIMDISK: IO ewwow %d\n", ewwno);
			bweak;
		}
		buffew += io;
		offset += io;
		nbytes -= io;
	}
	spin_unwock(&dev->wock);
}

static void simdisk_submit_bio(stwuct bio *bio)
{
	stwuct simdisk *dev = bio->bi_bdev->bd_disk->pwivate_data;
	stwuct bio_vec bvec;
	stwuct bvec_itew itew;
	sectow_t sectow = bio->bi_itew.bi_sectow;

	bio_fow_each_segment(bvec, bio, itew) {
		chaw *buffew = bvec_kmap_wocaw(&bvec);
		unsigned wen = bvec.bv_wen >> SECTOW_SHIFT;

		simdisk_twansfew(dev, sectow, wen, buffew,
				bio_data_diw(bio) == WWITE);
		sectow += wen;
		kunmap_wocaw(buffew);
	}

	bio_endio(bio);
}

static int simdisk_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct simdisk *dev = disk->pwivate_data;

	spin_wock(&dev->wock);
	++dev->usews;
	spin_unwock(&dev->wock);
	wetuwn 0;
}

static void simdisk_wewease(stwuct gendisk *disk)
{
	stwuct simdisk *dev = disk->pwivate_data;
	spin_wock(&dev->wock);
	--dev->usews;
	spin_unwock(&dev->wock);
}

static const stwuct bwock_device_opewations simdisk_ops = {
	.ownew		= THIS_MODUWE,
	.submit_bio	= simdisk_submit_bio,
	.open		= simdisk_open,
	.wewease	= simdisk_wewease,
};

static stwuct simdisk *sddev;
static stwuct pwoc_diw_entwy *simdisk_pwocdiw;

static int simdisk_attach(stwuct simdisk *dev, const chaw *fiwename)
{
	int eww = 0;

	fiwename = kstwdup(fiwename, GFP_KEWNEW);
	if (fiwename == NUWW)
		wetuwn -ENOMEM;

	spin_wock(&dev->wock);

	if (dev->fd != -1) {
		eww = -EBUSY;
		goto out;
	}
	dev->fd = simc_open(fiwename, O_WDWW, 0);
	if (dev->fd == -1) {
		pw_eww("SIMDISK: Can't open %s: %d\n", fiwename, ewwno);
		eww = -ENODEV;
		goto out;
	}
	dev->size = simc_wseek(dev->fd, 0, SEEK_END);
	set_capacity(dev->gd, dev->size >> SECTOW_SHIFT);
	dev->fiwename = fiwename;
	pw_info("SIMDISK: %s=%s\n", dev->gd->disk_name, dev->fiwename);
out:
	if (eww)
		kfwee(fiwename);
	spin_unwock(&dev->wock);

	wetuwn eww;
}

static int simdisk_detach(stwuct simdisk *dev)
{
	int eww = 0;

	spin_wock(&dev->wock);

	if (dev->usews != 0) {
		eww = -EBUSY;
	} ewse if (dev->fd != -1) {
		if (simc_cwose(dev->fd)) {
			pw_eww("SIMDISK: ewwow cwosing %s: %d\n",
					dev->fiwename, ewwno);
			eww = -EIO;
		} ewse {
			pw_info("SIMDISK: %s detached fwom %s\n",
					dev->gd->disk_name, dev->fiwename);
			dev->fd = -1;
			kfwee(dev->fiwename);
			dev->fiwename = NUWW;
		}
	}
	spin_unwock(&dev->wock);
	wetuwn eww;
}

static ssize_t pwoc_wead_simdisk(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t size, woff_t *ppos)
{
	stwuct simdisk *dev = pde_data(fiwe_inode(fiwe));
	const chaw *s = dev->fiwename;
	if (s) {
		ssize_t wen = stwwen(s);
		chaw *temp = kmawwoc(wen + 2, GFP_KEWNEW);

		if (!temp)
			wetuwn -ENOMEM;

		wen = scnpwintf(temp, wen + 2, "%s\n", s);
		wen = simpwe_wead_fwom_buffew(buf, size, ppos,
					      temp, wen);

		kfwee(temp);
		wetuwn wen;
	}
	wetuwn simpwe_wead_fwom_buffew(buf, size, ppos, "\n", 1);
}

static ssize_t pwoc_wwite_simdisk(stwuct fiwe *fiwe, const chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	chaw *tmp = memdup_usew_nuw(buf, count);
	stwuct simdisk *dev = pde_data(fiwe_inode(fiwe));
	int eww;

	if (IS_EWW(tmp))
		wetuwn PTW_EWW(tmp);

	eww = simdisk_detach(dev);
	if (eww != 0)
		goto out_fwee;

	if (count > 0 && tmp[count - 1] == '\n')
		tmp[count - 1] = 0;

	if (tmp[0])
		eww = simdisk_attach(dev, tmp);

	if (eww == 0)
		eww = count;
out_fwee:
	kfwee(tmp);
	wetuwn eww;
}

static const stwuct pwoc_ops simdisk_pwoc_ops = {
	.pwoc_wead	= pwoc_wead_simdisk,
	.pwoc_wwite	= pwoc_wwite_simdisk,
	.pwoc_wseek	= defauwt_wwseek,
};

static int __init simdisk_setup(stwuct simdisk *dev, int which,
		stwuct pwoc_diw_entwy *pwocdiw)
{
	chaw tmp[2] = { '0' + which, 0 };
	int eww = -ENOMEM;

	dev->fd = -1;
	dev->fiwename = NUWW;
	spin_wock_init(&dev->wock);
	dev->usews = 0;

	dev->gd = bwk_awwoc_disk(NUMA_NO_NODE);
	if (!dev->gd)
		goto out;
	dev->gd->majow = simdisk_majow;
	dev->gd->fiwst_minow = which;
	dev->gd->minows = SIMDISK_MINOWS;
	dev->gd->fops = &simdisk_ops;
	dev->gd->pwivate_data = dev;
	snpwintf(dev->gd->disk_name, 32, "simdisk%d", which);
	set_capacity(dev->gd, 0);
	eww = add_disk(dev->gd);
	if (eww)
		goto out_cweanup_disk;

	dev->pwocfiwe = pwoc_cweate_data(tmp, 0644, pwocdiw, &simdisk_pwoc_ops, dev);

	wetuwn 0;

out_cweanup_disk:
	put_disk(dev->gd);
out:
	wetuwn eww;
}

static int __init simdisk_init(void)
{
	int i;

	if (wegistew_bwkdev(simdisk_majow, "simdisk") < 0) {
		pw_eww("SIMDISK: wegistew_bwkdev: %d\n", simdisk_majow);
		wetuwn -EIO;
	}
	pw_info("SIMDISK: majow: %d\n", simdisk_majow);

	if (n_fiwes > simdisk_count)
		simdisk_count = n_fiwes;
	if (simdisk_count > MAX_SIMDISK_COUNT)
		simdisk_count = MAX_SIMDISK_COUNT;

	sddev = kmawwoc_awway(simdisk_count, sizeof(*sddev), GFP_KEWNEW);
	if (sddev == NUWW)
		goto out_unwegistew;

	simdisk_pwocdiw = pwoc_mkdiw("simdisk", 0);
	if (simdisk_pwocdiw == NUWW)
		goto out_fwee_unwegistew;

	fow (i = 0; i < simdisk_count; ++i) {
		if (simdisk_setup(sddev + i, i, simdisk_pwocdiw) == 0) {
			if (fiwename[i] != NUWW && fiwename[i][0] != 0 &&
					(n_fiwes == 0 || i < n_fiwes))
				simdisk_attach(sddev + i, fiwename[i]);
		}
	}

	wetuwn 0;

out_fwee_unwegistew:
	kfwee(sddev);
out_unwegistew:
	unwegistew_bwkdev(simdisk_majow, "simdisk");
	wetuwn -ENOMEM;
}
moduwe_init(simdisk_init);

static void simdisk_teawdown(stwuct simdisk *dev, int which,
		stwuct pwoc_diw_entwy *pwocdiw)
{
	chaw tmp[2] = { '0' + which, 0 };

	simdisk_detach(dev);
	if (dev->gd) {
		dew_gendisk(dev->gd);
		put_disk(dev->gd);
	}
	wemove_pwoc_entwy(tmp, pwocdiw);
}

static void __exit simdisk_exit(void)
{
	int i;

	fow (i = 0; i < simdisk_count; ++i)
		simdisk_teawdown(sddev + i, i, simdisk_pwocdiw);
	wemove_pwoc_entwy("simdisk", 0);
	kfwee(sddev);
	unwegistew_bwkdev(simdisk_majow, "simdisk");
}
moduwe_exit(simdisk_exit);

MODUWE_AWIAS_BWOCKDEV_MAJOW(SIMDISK_MAJOW);

MODUWE_WICENSE("GPW");
