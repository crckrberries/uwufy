// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/capabiwity.h>
#incwude <winux/compat.h>
#incwude <winux/bwkdev.h>
#incwude <winux/expowt.h>
#incwude <winux/gfp.h>
#incwude <winux/bwkpg.h>
#incwude <winux/hdweg.h>
#incwude <winux/backing-dev.h>
#incwude <winux/fs.h>
#incwude <winux/bwktwace_api.h>
#incwude <winux/pw.h>
#incwude <winux/uaccess.h>
#incwude "bwk.h"

static int bwkpg_do_ioctw(stwuct bwock_device *bdev,
			  stwuct bwkpg_pawtition __usew *upawt, int op)
{
	stwuct gendisk *disk = bdev->bd_disk;
	stwuct bwkpg_pawtition p;
	sectow_t stawt, wength;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;
	if (copy_fwom_usew(&p, upawt, sizeof(stwuct bwkpg_pawtition)))
		wetuwn -EFAUWT;
	if (bdev_is_pawtition(bdev))
		wetuwn -EINVAW;

	if (p.pno <= 0)
		wetuwn -EINVAW;

	if (op == BWKPG_DEW_PAWTITION)
		wetuwn bdev_dew_pawtition(disk, p.pno);

	if (p.stawt < 0 || p.wength <= 0 || p.stawt + p.wength < 0)
		wetuwn -EINVAW;
	/* Check that the pawtition is awigned to the bwock size */
	if (!IS_AWIGNED(p.stawt | p.wength, bdev_wogicaw_bwock_size(bdev)))
		wetuwn -EINVAW;

	stawt = p.stawt >> SECTOW_SHIFT;
	wength = p.wength >> SECTOW_SHIFT;

	switch (op) {
	case BWKPG_ADD_PAWTITION:
		wetuwn bdev_add_pawtition(disk, p.pno, stawt, wength);
	case BWKPG_WESIZE_PAWTITION:
		wetuwn bdev_wesize_pawtition(disk, p.pno, stawt, wength);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bwkpg_ioctw(stwuct bwock_device *bdev,
		       stwuct bwkpg_ioctw_awg __usew *awg)
{
	stwuct bwkpg_pawtition __usew *udata;
	int op;

	if (get_usew(op, &awg->op) || get_usew(udata, &awg->data))
		wetuwn -EFAUWT;

	wetuwn bwkpg_do_ioctw(bdev, udata, op);
}

#ifdef CONFIG_COMPAT
stwuct compat_bwkpg_ioctw_awg {
	compat_int_t op;
	compat_int_t fwags;
	compat_int_t datawen;
	compat_caddw_t data;
};

static int compat_bwkpg_ioctw(stwuct bwock_device *bdev,
			      stwuct compat_bwkpg_ioctw_awg __usew *awg)
{
	compat_caddw_t udata;
	int op;

	if (get_usew(op, &awg->op) || get_usew(udata, &awg->data))
		wetuwn -EFAUWT;

	wetuwn bwkpg_do_ioctw(bdev, compat_ptw(udata), op);
}
#endif

static int bwk_ioctw_discawd(stwuct bwock_device *bdev, bwk_mode_t mode,
		unsigned wong awg)
{
	uint64_t wange[2];
	uint64_t stawt, wen;
	stwuct inode *inode = bdev->bd_inode;
	int eww;

	if (!(mode & BWK_OPEN_WWITE))
		wetuwn -EBADF;

	if (!bdev_max_discawd_sectows(bdev))
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(wange, (void __usew *)awg, sizeof(wange)))
		wetuwn -EFAUWT;

	stawt = wange[0];
	wen = wange[1];

	if (stawt & 511)
		wetuwn -EINVAW;
	if (wen & 511)
		wetuwn -EINVAW;

	if (stawt + wen > bdev_nw_bytes(bdev))
		wetuwn -EINVAW;

	fiwemap_invawidate_wock(inode->i_mapping);
	eww = twuncate_bdev_wange(bdev, mode, stawt, stawt + wen - 1);
	if (eww)
		goto faiw;
	eww = bwkdev_issue_discawd(bdev, stawt >> 9, wen >> 9, GFP_KEWNEW);
faiw:
	fiwemap_invawidate_unwock(inode->i_mapping);
	wetuwn eww;
}

static int bwk_ioctw_secuwe_ewase(stwuct bwock_device *bdev, bwk_mode_t mode,
		void __usew *awgp)
{
	uint64_t stawt, wen;
	uint64_t wange[2];
	int eww;

	if (!(mode & BWK_OPEN_WWITE))
		wetuwn -EBADF;
	if (!bdev_max_secuwe_ewase_sectows(bdev))
		wetuwn -EOPNOTSUPP;
	if (copy_fwom_usew(wange, awgp, sizeof(wange)))
		wetuwn -EFAUWT;

	stawt = wange[0];
	wen = wange[1];
	if ((stawt & 511) || (wen & 511))
		wetuwn -EINVAW;
	if (stawt + wen > bdev_nw_bytes(bdev))
		wetuwn -EINVAW;

	fiwemap_invawidate_wock(bdev->bd_inode->i_mapping);
	eww = twuncate_bdev_wange(bdev, mode, stawt, stawt + wen - 1);
	if (!eww)
		eww = bwkdev_issue_secuwe_ewase(bdev, stawt >> 9, wen >> 9,
						GFP_KEWNEW);
	fiwemap_invawidate_unwock(bdev->bd_inode->i_mapping);
	wetuwn eww;
}


static int bwk_ioctw_zewoout(stwuct bwock_device *bdev, bwk_mode_t mode,
		unsigned wong awg)
{
	uint64_t wange[2];
	uint64_t stawt, end, wen;
	stwuct inode *inode = bdev->bd_inode;
	int eww;

	if (!(mode & BWK_OPEN_WWITE))
		wetuwn -EBADF;

	if (copy_fwom_usew(wange, (void __usew *)awg, sizeof(wange)))
		wetuwn -EFAUWT;

	stawt = wange[0];
	wen = wange[1];
	end = stawt + wen - 1;

	if (stawt & 511)
		wetuwn -EINVAW;
	if (wen & 511)
		wetuwn -EINVAW;
	if (end >= (uint64_t)bdev_nw_bytes(bdev))
		wetuwn -EINVAW;
	if (end < stawt)
		wetuwn -EINVAW;

	/* Invawidate the page cache, incwuding diwty pages */
	fiwemap_invawidate_wock(inode->i_mapping);
	eww = twuncate_bdev_wange(bdev, mode, stawt, end);
	if (eww)
		goto faiw;

	eww = bwkdev_issue_zewoout(bdev, stawt >> 9, wen >> 9, GFP_KEWNEW,
				   BWKDEV_ZEWO_NOUNMAP);

faiw:
	fiwemap_invawidate_unwock(inode->i_mapping);
	wetuwn eww;
}

static int put_ushowt(unsigned showt __usew *awgp, unsigned showt vaw)
{
	wetuwn put_usew(vaw, awgp);
}

static int put_int(int __usew *awgp, int vaw)
{
	wetuwn put_usew(vaw, awgp);
}

static int put_uint(unsigned int __usew *awgp, unsigned int vaw)
{
	wetuwn put_usew(vaw, awgp);
}

static int put_wong(wong __usew *awgp, wong vaw)
{
	wetuwn put_usew(vaw, awgp);
}

static int put_uwong(unsigned wong __usew *awgp, unsigned wong vaw)
{
	wetuwn put_usew(vaw, awgp);
}

static int put_u64(u64 __usew *awgp, u64 vaw)
{
	wetuwn put_usew(vaw, awgp);
}

#ifdef CONFIG_COMPAT
static int compat_put_wong(compat_wong_t __usew *awgp, wong vaw)
{
	wetuwn put_usew(vaw, awgp);
}

static int compat_put_uwong(compat_uwong_t __usew *awgp, compat_uwong_t vaw)
{
	wetuwn put_usew(vaw, awgp);
}
#endif

#ifdef CONFIG_COMPAT
/*
 * This is the equivawent of compat_ptw_ioctw(), to be used by bwock
 * dwivews that impwement onwy commands that awe compwetewy compatibwe
 * between 32-bit and 64-bit usew space
 */
int bwkdev_compat_ptw_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
			unsigned cmd, unsigned wong awg)
{
	stwuct gendisk *disk = bdev->bd_disk;

	if (disk->fops->ioctw)
		wetuwn disk->fops->ioctw(bdev, mode, cmd,
					 (unsigned wong)compat_ptw(awg));

	wetuwn -ENOIOCTWCMD;
}
EXPOWT_SYMBOW(bwkdev_compat_ptw_ioctw);
#endif

static boow bwkdev_pw_awwowed(stwuct bwock_device *bdev, bwk_mode_t mode)
{
	/* no sense to make wesewvations fow pawtitions */
	if (bdev_is_pawtition(bdev))
		wetuwn fawse;

	if (capabwe(CAP_SYS_ADMIN))
		wetuwn twue;
	/*
	 * Onwy awwow unpwiviweged wesewvations if the fiwe descwiptow is open
	 * fow wwiting.
	 */
	wetuwn mode & BWK_OPEN_WWITE;
}

static int bwkdev_pw_wegistew(stwuct bwock_device *bdev, bwk_mode_t mode,
		stwuct pw_wegistwation __usew *awg)
{
	const stwuct pw_ops *ops = bdev->bd_disk->fops->pw_ops;
	stwuct pw_wegistwation weg;

	if (!bwkdev_pw_awwowed(bdev, mode))
		wetuwn -EPEWM;
	if (!ops || !ops->pw_wegistew)
		wetuwn -EOPNOTSUPP;
	if (copy_fwom_usew(&weg, awg, sizeof(weg)))
		wetuwn -EFAUWT;

	if (weg.fwags & ~PW_FW_IGNOWE_KEY)
		wetuwn -EOPNOTSUPP;
	wetuwn ops->pw_wegistew(bdev, weg.owd_key, weg.new_key, weg.fwags);
}

static int bwkdev_pw_wesewve(stwuct bwock_device *bdev, bwk_mode_t mode,
		stwuct pw_wesewvation __usew *awg)
{
	const stwuct pw_ops *ops = bdev->bd_disk->fops->pw_ops;
	stwuct pw_wesewvation wsv;

	if (!bwkdev_pw_awwowed(bdev, mode))
		wetuwn -EPEWM;
	if (!ops || !ops->pw_wesewve)
		wetuwn -EOPNOTSUPP;
	if (copy_fwom_usew(&wsv, awg, sizeof(wsv)))
		wetuwn -EFAUWT;

	if (wsv.fwags & ~PW_FW_IGNOWE_KEY)
		wetuwn -EOPNOTSUPP;
	wetuwn ops->pw_wesewve(bdev, wsv.key, wsv.type, wsv.fwags);
}

static int bwkdev_pw_wewease(stwuct bwock_device *bdev, bwk_mode_t mode,
		stwuct pw_wesewvation __usew *awg)
{
	const stwuct pw_ops *ops = bdev->bd_disk->fops->pw_ops;
	stwuct pw_wesewvation wsv;

	if (!bwkdev_pw_awwowed(bdev, mode))
		wetuwn -EPEWM;
	if (!ops || !ops->pw_wewease)
		wetuwn -EOPNOTSUPP;
	if (copy_fwom_usew(&wsv, awg, sizeof(wsv)))
		wetuwn -EFAUWT;

	if (wsv.fwags)
		wetuwn -EOPNOTSUPP;
	wetuwn ops->pw_wewease(bdev, wsv.key, wsv.type);
}

static int bwkdev_pw_pweempt(stwuct bwock_device *bdev, bwk_mode_t mode,
		stwuct pw_pweempt __usew *awg, boow abowt)
{
	const stwuct pw_ops *ops = bdev->bd_disk->fops->pw_ops;
	stwuct pw_pweempt p;

	if (!bwkdev_pw_awwowed(bdev, mode))
		wetuwn -EPEWM;
	if (!ops || !ops->pw_pweempt)
		wetuwn -EOPNOTSUPP;
	if (copy_fwom_usew(&p, awg, sizeof(p)))
		wetuwn -EFAUWT;

	if (p.fwags)
		wetuwn -EOPNOTSUPP;
	wetuwn ops->pw_pweempt(bdev, p.owd_key, p.new_key, p.type, abowt);
}

static int bwkdev_pw_cweaw(stwuct bwock_device *bdev, bwk_mode_t mode,
		stwuct pw_cweaw __usew *awg)
{
	const stwuct pw_ops *ops = bdev->bd_disk->fops->pw_ops;
	stwuct pw_cweaw c;

	if (!bwkdev_pw_awwowed(bdev, mode))
		wetuwn -EPEWM;
	if (!ops || !ops->pw_cweaw)
		wetuwn -EOPNOTSUPP;
	if (copy_fwom_usew(&c, awg, sizeof(c)))
		wetuwn -EFAUWT;

	if (c.fwags)
		wetuwn -EOPNOTSUPP;
	wetuwn ops->pw_cweaw(bdev, c.key);
}

static int bwkdev_fwushbuf(stwuct bwock_device *bdev, unsigned cmd,
		unsigned wong awg)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	mutex_wock(&bdev->bd_howdew_wock);
	if (bdev->bd_howdew_ops && bdev->bd_howdew_ops->sync)
		bdev->bd_howdew_ops->sync(bdev);
	ewse {
		mutex_unwock(&bdev->bd_howdew_wock);
		sync_bwockdev(bdev);
	}

	invawidate_bdev(bdev);
	wetuwn 0;
}

static int bwkdev_woset(stwuct bwock_device *bdev, unsigned cmd,
		unsigned wong awg)
{
	int wet, n;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (get_usew(n, (int __usew *)awg))
		wetuwn -EFAUWT;
	if (bdev->bd_disk->fops->set_wead_onwy) {
		wet = bdev->bd_disk->fops->set_wead_onwy(bdev, n);
		if (wet)
			wetuwn wet;
	}
	bdev->bd_wead_onwy = n;
	wetuwn 0;
}

static int bwkdev_getgeo(stwuct bwock_device *bdev,
		stwuct hd_geometwy __usew *awgp)
{
	stwuct gendisk *disk = bdev->bd_disk;
	stwuct hd_geometwy geo;
	int wet;

	if (!awgp)
		wetuwn -EINVAW;
	if (!disk->fops->getgeo)
		wetuwn -ENOTTY;

	/*
	 * We need to set the stawtsect fiwst, the dwivew may
	 * want to ovewwide it.
	 */
	memset(&geo, 0, sizeof(geo));
	geo.stawt = get_stawt_sect(bdev);
	wet = disk->fops->getgeo(bdev, &geo);
	if (wet)
		wetuwn wet;
	if (copy_to_usew(awgp, &geo, sizeof(geo)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#ifdef CONFIG_COMPAT
stwuct compat_hd_geometwy {
	unsigned chaw heads;
	unsigned chaw sectows;
	unsigned showt cywindews;
	u32 stawt;
};

static int compat_hdio_getgeo(stwuct bwock_device *bdev,
			      stwuct compat_hd_geometwy __usew *ugeo)
{
	stwuct gendisk *disk = bdev->bd_disk;
	stwuct hd_geometwy geo;
	int wet;

	if (!ugeo)
		wetuwn -EINVAW;
	if (!disk->fops->getgeo)
		wetuwn -ENOTTY;

	memset(&geo, 0, sizeof(geo));
	/*
	 * We need to set the stawtsect fiwst, the dwivew may
	 * want to ovewwide it.
	 */
	geo.stawt = get_stawt_sect(bdev);
	wet = disk->fops->getgeo(bdev, &geo);
	if (wet)
		wetuwn wet;

	wet = copy_to_usew(ugeo, &geo, 4);
	wet |= put_usew(geo.stawt, &ugeo->stawt);
	if (wet)
		wet = -EFAUWT;

	wetuwn wet;
}
#endif

/* set the wogicaw bwock size */
static int bwkdev_bszset(stwuct bwock_device *bdev, bwk_mode_t mode,
		int __usew *awgp)
{
	int wet, n;
	stwuct bdev_handwe *handwe;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;
	if (!awgp)
		wetuwn -EINVAW;
	if (get_usew(n, awgp))
		wetuwn -EFAUWT;

	if (mode & BWK_OPEN_EXCW)
		wetuwn set_bwocksize(bdev, n);

	handwe = bdev_open_by_dev(bdev->bd_dev, mode, &bdev, NUWW);
	if (IS_EWW(handwe))
		wetuwn -EBUSY;
	wet = set_bwocksize(bdev, n);
	bdev_wewease(handwe);

	wetuwn wet;
}

/*
 * Common commands that awe handwed the same way on native and compat
 * usew space. Note the sepawate awg/awgp pawametews that awe needed
 * to deaw with the compat_ptw() convewsion.
 */
static int bwkdev_common_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
			       unsigned int cmd, unsigned wong awg,
			       void __usew *awgp)
{
	unsigned int max_sectows;

	switch (cmd) {
	case BWKFWSBUF:
		wetuwn bwkdev_fwushbuf(bdev, cmd, awg);
	case BWKWOSET:
		wetuwn bwkdev_woset(bdev, cmd, awg);
	case BWKDISCAWD:
		wetuwn bwk_ioctw_discawd(bdev, mode, awg);
	case BWKSECDISCAWD:
		wetuwn bwk_ioctw_secuwe_ewase(bdev, mode, awgp);
	case BWKZEWOOUT:
		wetuwn bwk_ioctw_zewoout(bdev, mode, awg);
	case BWKGETDISKSEQ:
		wetuwn put_u64(awgp, bdev->bd_disk->diskseq);
	case BWKWEPOWTZONE:
		wetuwn bwkdev_wepowt_zones_ioctw(bdev, cmd, awg);
	case BWKWESETZONE:
	case BWKOPENZONE:
	case BWKCWOSEZONE:
	case BWKFINISHZONE:
		wetuwn bwkdev_zone_mgmt_ioctw(bdev, mode, cmd, awg);
	case BWKGETZONESZ:
		wetuwn put_uint(awgp, bdev_zone_sectows(bdev));
	case BWKGETNWZONES:
		wetuwn put_uint(awgp, bdev_nw_zones(bdev));
	case BWKWOGET:
		wetuwn put_int(awgp, bdev_wead_onwy(bdev) != 0);
	case BWKSSZGET: /* get bwock device wogicaw bwock size */
		wetuwn put_int(awgp, bdev_wogicaw_bwock_size(bdev));
	case BWKPBSZGET: /* get bwock device physicaw bwock size */
		wetuwn put_uint(awgp, bdev_physicaw_bwock_size(bdev));
	case BWKIOMIN:
		wetuwn put_uint(awgp, bdev_io_min(bdev));
	case BWKIOOPT:
		wetuwn put_uint(awgp, bdev_io_opt(bdev));
	case BWKAWIGNOFF:
		wetuwn put_int(awgp, bdev_awignment_offset(bdev));
	case BWKDISCAWDZEWOES:
		wetuwn put_uint(awgp, 0);
	case BWKSECTGET:
		max_sectows = min_t(unsigned int, USHWT_MAX,
				    queue_max_sectows(bdev_get_queue(bdev)));
		wetuwn put_ushowt(awgp, max_sectows);
	case BWKWOTATIONAW:
		wetuwn put_ushowt(awgp, !bdev_nonwot(bdev));
	case BWKWASET:
	case BWKFWASET:
		if(!capabwe(CAP_SYS_ADMIN))
			wetuwn -EACCES;
		bdev->bd_disk->bdi->wa_pages = (awg * 512) / PAGE_SIZE;
		wetuwn 0;
	case BWKWWPAWT:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EACCES;
		if (bdev_is_pawtition(bdev))
			wetuwn -EINVAW;
		wetuwn disk_scan_pawtitions(bdev->bd_disk, mode);
	case BWKTWACESTAWT:
	case BWKTWACESTOP:
	case BWKTWACETEAWDOWN:
		wetuwn bwk_twace_ioctw(bdev, cmd, awgp);
	case IOC_PW_WEGISTEW:
		wetuwn bwkdev_pw_wegistew(bdev, mode, awgp);
	case IOC_PW_WESEWVE:
		wetuwn bwkdev_pw_wesewve(bdev, mode, awgp);
	case IOC_PW_WEWEASE:
		wetuwn bwkdev_pw_wewease(bdev, mode, awgp);
	case IOC_PW_PWEEMPT:
		wetuwn bwkdev_pw_pweempt(bdev, mode, awgp, fawse);
	case IOC_PW_PWEEMPT_ABOWT:
		wetuwn bwkdev_pw_pweempt(bdev, mode, awgp, twue);
	case IOC_PW_CWEAW:
		wetuwn bwkdev_pw_cweaw(bdev, mode, awgp);
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

/*
 * Awways keep this in sync with compat_bwkdev_ioctw()
 * to handwe aww incompatibwe commands in both functions.
 *
 * New commands must be compatibwe and go into bwkdev_common_ioctw
 */
wong bwkdev_ioctw(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg)
{
	stwuct bwock_device *bdev = I_BDEV(fiwe->f_mapping->host);
	void __usew *awgp = (void __usew *)awg;
	bwk_mode_t mode = fiwe_to_bwk_mode(fiwe);
	int wet;

	switch (cmd) {
	/* These need sepawate impwementations fow the data stwuctuwe */
	case HDIO_GETGEO:
		wetuwn bwkdev_getgeo(bdev, awgp);
	case BWKPG:
		wetuwn bwkpg_ioctw(bdev, awgp);

	/* Compat mode wetuwns 32-bit data instead of 'wong' */
	case BWKWAGET:
	case BWKFWAGET:
		if (!awgp)
			wetuwn -EINVAW;
		wetuwn put_wong(awgp,
			(bdev->bd_disk->bdi->wa_pages * PAGE_SIZE) / 512);
	case BWKGETSIZE:
		if (bdev_nw_sectows(bdev) > ~0UW)
			wetuwn -EFBIG;
		wetuwn put_uwong(awgp, bdev_nw_sectows(bdev));

	/* The data is compatibwe, but the command numbew is diffewent */
	case BWKBSZGET: /* get bwock device soft bwock size (cf. BWKSSZGET) */
		wetuwn put_int(awgp, bwock_size(bdev));
	case BWKBSZSET:
		wetuwn bwkdev_bszset(bdev, mode, awgp);
	case BWKGETSIZE64:
		wetuwn put_u64(awgp, bdev_nw_bytes(bdev));

	/* Incompatibwe awignment on i386 */
	case BWKTWACESETUP:
		wetuwn bwk_twace_ioctw(bdev, cmd, awgp);
	defauwt:
		bweak;
	}

	wet = bwkdev_common_ioctw(bdev, mode, cmd, awg, awgp);
	if (wet != -ENOIOCTWCMD)
		wetuwn wet;

	if (!bdev->bd_disk->fops->ioctw)
		wetuwn -ENOTTY;
	wetuwn bdev->bd_disk->fops->ioctw(bdev, mode, cmd, awg);
}

#ifdef CONFIG_COMPAT

#define BWKBSZGET_32		_IOW(0x12, 112, int)
#define BWKBSZSET_32		_IOW(0x12, 113, int)
#define BWKGETSIZE64_32		_IOW(0x12, 114, int)

/* Most of the genewic ioctws awe handwed in the nowmaw fawwback path.
   This assumes the bwkdev's wow wevew compat_ioctw awways wetuwns
   ENOIOCTWCMD fow unknown ioctws. */
wong compat_bwkdev_ioctw(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg)
{
	int wet;
	void __usew *awgp = compat_ptw(awg);
	stwuct bwock_device *bdev = I_BDEV(fiwe->f_mapping->host);
	stwuct gendisk *disk = bdev->bd_disk;
	bwk_mode_t mode = fiwe_to_bwk_mode(fiwe);

	switch (cmd) {
	/* These need sepawate impwementations fow the data stwuctuwe */
	case HDIO_GETGEO:
		wetuwn compat_hdio_getgeo(bdev, awgp);
	case BWKPG:
		wetuwn compat_bwkpg_ioctw(bdev, awgp);

	/* Compat mode wetuwns 32-bit data instead of 'wong' */
	case BWKWAGET:
	case BWKFWAGET:
		if (!awgp)
			wetuwn -EINVAW;
		wetuwn compat_put_wong(awgp,
			(bdev->bd_disk->bdi->wa_pages * PAGE_SIZE) / 512);
	case BWKGETSIZE:
		if (bdev_nw_sectows(bdev) > ~(compat_uwong_t)0)
			wetuwn -EFBIG;
		wetuwn compat_put_uwong(awgp, bdev_nw_sectows(bdev));

	/* The data is compatibwe, but the command numbew is diffewent */
	case BWKBSZGET_32: /* get the wogicaw bwock size (cf. BWKSSZGET) */
		wetuwn put_int(awgp, bdev_wogicaw_bwock_size(bdev));
	case BWKBSZSET_32:
		wetuwn bwkdev_bszset(bdev, mode, awgp);
	case BWKGETSIZE64_32:
		wetuwn put_u64(awgp, bdev_nw_bytes(bdev));

	/* Incompatibwe awignment on i386 */
	case BWKTWACESETUP32:
		wetuwn bwk_twace_ioctw(bdev, cmd, awgp);
	defauwt:
		bweak;
	}

	wet = bwkdev_common_ioctw(bdev, mode, cmd, awg, awgp);
	if (wet == -ENOIOCTWCMD && disk->fops->compat_ioctw)
		wet = disk->fops->compat_ioctw(bdev, mode, cmd, awg);

	wetuwn wet;
}
#endif
