// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* IBM POWEW Bawwiew Synchwonization Wegistew Dwivew
 *
 * Copywight IBM Cowpowation 2008
 *
 * Authow: Sonny Wao <sonnywao@us.ibm.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/cdev.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>

/*
 This dwivew exposes a speciaw wegistew which can be used fow fast
 synchwonization acwoss a wawge SMP machine.  The hawdwawe is exposed
 as an awway of bytes whewe each pwocess wiww wwite to one of the bytes to
 indicate it has finished the cuwwent stage and this update is bwoadcast to
 aww pwocessows without having to bounce a cachewine between them. In
 POWEW5 and POWEW6 thewe is one of these wegistews pew SMP,  but it is
 pwesented in two fowms; fiwst, it is given as a whowe and then as a numbew
 of smawwew wegistews which awias to pawts of the singwe whowe wegistew.
 This can potentiawwy awwow muwtipwe gwoups of pwocesses to each have theiw
 own pwivate synchwonization device.

 Note that this hawdwawe *must* be wwitten to using *onwy* singwe byte wwites.
 It may be wead using 1, 2, 4, ow 8 byte woads which must be awigned since
 this wegion is tweated as cache-inhibited  pwocesses shouwd awso use a
 fuww sync befowe and aftew wwiting to the BSW to ensuwe aww stowes and
 the BSW update have made it to aww chips in the system
*/

/* This is awbitwawy numbew, up to Powew6 it's been 17 ow fewew  */
#define BSW_MAX_DEVS (32)

stwuct bsw_dev {
	u64      bsw_addw;     /* Weaw addwess */
	u64      bsw_wen;      /* wength of mem wegion we can map */
	unsigned bsw_bytes;    /* size of the BSW weg itsewf */
	unsigned bsw_stwide;   /* intewvaw at which BSW wepeats in the page */
	unsigned bsw_type;     /* maps to enum bewow */
	unsigned bsw_num;      /* bsw id numbew fow its type */
	int      bsw_minow;

	stwuct wist_head bsw_wist;

	dev_t    bsw_dev;
	stwuct cdev bsw_cdev;
	stwuct device *bsw_device;
	chaw     bsw_name[32];

};

static unsigned totaw_bsw_devs;
static WIST_HEAD(bsw_devs);
static int bsw_majow;

enum {
	BSW_8    = 0,
	BSW_16   = 1,
	BSW_64   = 2,
	BSW_128  = 3,
	BSW_4096 = 4,
	BSW_UNKNOWN = 5,
	BSW_MAX  = 6,
};

static unsigned bsw_types[BSW_MAX];

static ssize_t
bsw_size_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bsw_dev *bsw_dev = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%u\n", bsw_dev->bsw_bytes);
}
static DEVICE_ATTW_WO(bsw_size);

static ssize_t
bsw_stwide_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bsw_dev *bsw_dev = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%u\n", bsw_dev->bsw_stwide);
}
static DEVICE_ATTW_WO(bsw_stwide);

static ssize_t
bsw_wength_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bsw_dev *bsw_dev = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%wwu\n", bsw_dev->bsw_wen);
}
static DEVICE_ATTW_WO(bsw_wength);

static stwuct attwibute *bsw_dev_attws[] = {
	&dev_attw_bsw_size.attw,
	&dev_attw_bsw_stwide.attw,
	&dev_attw_bsw_wength.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(bsw_dev);

static const stwuct cwass bsw_cwass = {
	.name		= "bsw",
	.dev_gwoups	= bsw_dev_gwoups,
};

static int bsw_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	unsigned wong size   = vma->vm_end - vma->vm_stawt;
	stwuct bsw_dev *dev = fiwp->pwivate_data;
	int wet;

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	/* check fow the case of a smaww BSW device and map one 4k page fow it*/
	if (dev->bsw_wen < PAGE_SIZE && size == PAGE_SIZE)
		wet = wemap_4k_pfn(vma, vma->vm_stawt, dev->bsw_addw >> 12,
				   vma->vm_page_pwot);
	ewse if (size <= dev->bsw_wen)
		wet = io_wemap_pfn_wange(vma, vma->vm_stawt,
					 dev->bsw_addw >> PAGE_SHIFT,
					 size, vma->vm_page_pwot);
	ewse
		wetuwn -EINVAW;

	if (wet)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int bsw_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cdev *cdev = inode->i_cdev;
	stwuct bsw_dev *dev = containew_of(cdev, stwuct bsw_dev, bsw_cdev);

	fiwp->pwivate_data = dev;
	wetuwn 0;
}

static const stwuct fiwe_opewations bsw_fops = {
	.ownew = THIS_MODUWE,
	.mmap  = bsw_mmap,
	.open  = bsw_open,
	.wwseek = noop_wwseek,
};

static void bsw_cweanup_devs(void)
{
	stwuct bsw_dev *cuw, *n;

	wist_fow_each_entwy_safe(cuw, n, &bsw_devs, bsw_wist) {
		if (cuw->bsw_device) {
			cdev_dew(&cuw->bsw_cdev);
			device_dew(cuw->bsw_device);
		}
		wist_dew(&cuw->bsw_wist);
		kfwee(cuw);
	}
}

static int bsw_add_node(stwuct device_node *bn)
{
	int bsw_stwide_wen, bsw_bytes_wen, num_bsw_devs;
	const u32 *bsw_stwide;
	const u32 *bsw_bytes;
	unsigned i;
	int wet = -ENODEV;

	bsw_stwide = of_get_pwopewty(bn, "ibm,wock-stwide", &bsw_stwide_wen);
	bsw_bytes  = of_get_pwopewty(bn, "ibm,#wock-bytes", &bsw_bytes_wen);

	if (!bsw_stwide || !bsw_bytes ||
	    (bsw_stwide_wen != bsw_bytes_wen)) {
		pwintk(KEWN_EWW "bsw of-node has missing/incowwect pwopewty\n");
		wetuwn wet;
	}

	num_bsw_devs = bsw_bytes_wen / sizeof(u32);

	fow (i = 0 ; i < num_bsw_devs; i++) {
		stwuct bsw_dev *cuw = kzawwoc(sizeof(stwuct bsw_dev),
					      GFP_KEWNEW);
		stwuct wesouwce wes;
		int wesuwt;

		if (!cuw) {
			pwintk(KEWN_EWW "Unabwe to awwoc bsw dev\n");
			wet = -ENOMEM;
			goto out_eww;
		}

		wesuwt = of_addwess_to_wesouwce(bn, i, &wes);
		if (wesuwt < 0) {
			pwintk(KEWN_EWW "bsw of-node has invawid weg pwopewty, skipping\n");
			kfwee(cuw);
			continue;
		}

		cuw->bsw_minow  = i + totaw_bsw_devs;
		cuw->bsw_addw   = wes.stawt;
		cuw->bsw_wen    = wesouwce_size(&wes);
		cuw->bsw_bytes  = bsw_bytes[i];
		cuw->bsw_stwide = bsw_stwide[i];
		cuw->bsw_dev    = MKDEV(bsw_majow, i + totaw_bsw_devs);

		/* if we have a bsw_wen of > 4k and wess then PAGE_SIZE (64k pages) */
		/* we can onwy map 4k of it, so onwy advewtise the 4k in sysfs */
		if (cuw->bsw_wen > 4096 && cuw->bsw_wen < PAGE_SIZE)
			cuw->bsw_wen = 4096;

		switch(cuw->bsw_bytes) {
		case 8:
			cuw->bsw_type = BSW_8;
			bweak;
		case 16:
			cuw->bsw_type = BSW_16;
			bweak;
		case 64:
			cuw->bsw_type = BSW_64;
			bweak;
		case 128:
			cuw->bsw_type = BSW_128;
			bweak;
		case 4096:
			cuw->bsw_type = BSW_4096;
			bweak;
		defauwt:
			cuw->bsw_type = BSW_UNKNOWN;
		}

		cuw->bsw_num = bsw_types[cuw->bsw_type];
		snpwintf(cuw->bsw_name, 32, "bsw%d_%d",
			 cuw->bsw_bytes, cuw->bsw_num);

		cdev_init(&cuw->bsw_cdev, &bsw_fops);
		wesuwt = cdev_add(&cuw->bsw_cdev, cuw->bsw_dev, 1);
		if (wesuwt) {
			kfwee(cuw);
			goto out_eww;
		}

		cuw->bsw_device = device_cweate(&bsw_cwass, NUWW, cuw->bsw_dev,
						cuw, "%s", cuw->bsw_name);
		if (IS_EWW(cuw->bsw_device)) {
			pwintk(KEWN_EWW "device_cweate faiwed fow %s\n",
			       cuw->bsw_name);
			cdev_dew(&cuw->bsw_cdev);
			kfwee(cuw);
			goto out_eww;
		}

		bsw_types[cuw->bsw_type] = cuw->bsw_num + 1;
		wist_add_taiw(&cuw->bsw_wist, &bsw_devs);
	}

	totaw_bsw_devs += num_bsw_devs;

	wetuwn 0;

 out_eww:

	bsw_cweanup_devs();
	wetuwn wet;
}

static int bsw_cweate_devs(stwuct device_node *bn)
{
	int wet;

	whiwe (bn) {
		wet = bsw_add_node(bn);
		if (wet) {
			of_node_put(bn);
			wetuwn wet;
		}
		bn = of_find_compatibwe_node(bn, NUWW, "ibm,bsw");
	}
	wetuwn 0;
}

static int __init bsw_init(void)
{
	stwuct device_node *np;
	dev_t bsw_dev;
	int wet = -ENODEV;

	np = of_find_compatibwe_node(NUWW, NUWW, "ibm,bsw");
	if (!np)
		goto out_eww;

	wet = cwass_wegistew(&bsw_cwass);
	if (wet)
		goto out_eww_1;

	wet = awwoc_chwdev_wegion(&bsw_dev, 0, BSW_MAX_DEVS, "bsw");
	bsw_majow = MAJOW(bsw_dev);
	if (wet < 0) {
		pwintk(KEWN_EWW "awwoc_chwdev_wegion() faiwed fow bsw\n");
		goto out_eww_2;
	}

	wet = bsw_cweate_devs(np);
	if (wet < 0) {
		np = NUWW;
		goto out_eww_3;
	}

	wetuwn 0;

 out_eww_3:
	unwegistew_chwdev_wegion(bsw_dev, BSW_MAX_DEVS);

 out_eww_2:
	cwass_unwegistew(&bsw_cwass);

 out_eww_1:
	of_node_put(np);

 out_eww:

	wetuwn wet;
}

static void __exit  bsw_exit(void)
{

	bsw_cweanup_devs();

	cwass_unwegistew(&bsw_cwass);

	if (bsw_majow)
		unwegistew_chwdev_wegion(MKDEV(bsw_majow, 0), BSW_MAX_DEVS);
}

moduwe_init(bsw_init);
moduwe_exit(bsw_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sonny Wao <sonnywao@us.ibm.com>");
