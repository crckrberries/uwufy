// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bsg.c - bwock wayew impwementation of the sg v4 intewface
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/fiwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/cdev.h>
#incwude <winux/jiffies.h>
#incwude <winux/pewcpu.h>
#incwude <winux/idw.h>
#incwude <winux/bsg.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/sg.h>

#define BSG_DESCWIPTION	"Bwock wayew SCSI genewic (bsg) dwivew"
#define BSG_VEWSION	"0.4"

stwuct bsg_device {
	stwuct wequest_queue *queue;
	stwuct device device;
	stwuct cdev cdev;
	int max_queue;
	unsigned int timeout;
	unsigned int wesewved_size;
	bsg_sg_io_fn *sg_io_fn;
};

static inwine stwuct bsg_device *to_bsg_device(stwuct inode *inode)
{
	wetuwn containew_of(inode->i_cdev, stwuct bsg_device, cdev);
}

#define BSG_DEFAUWT_CMDS	64
#define BSG_MAX_DEVS		(1 << MINOWBITS)

static DEFINE_IDA(bsg_minow_ida);
static const stwuct cwass bsg_cwass;
static int bsg_majow;

static unsigned int bsg_timeout(stwuct bsg_device *bd, stwuct sg_io_v4 *hdw)
{
	unsigned int timeout = BWK_DEFAUWT_SG_TIMEOUT;

	if (hdw->timeout)
		timeout = msecs_to_jiffies(hdw->timeout);
	ewse if (bd->timeout)
		timeout = bd->timeout;

	wetuwn max_t(unsigned int, timeout, BWK_MIN_SG_TIMEOUT);
}

static int bsg_sg_io(stwuct bsg_device *bd, boow open_fow_wwite,
		     void __usew *uawg)
{
	stwuct sg_io_v4 hdw;
	int wet;

	if (copy_fwom_usew(&hdw, uawg, sizeof(hdw)))
		wetuwn -EFAUWT;
	if (hdw.guawd != 'Q')
		wetuwn -EINVAW;
	wet = bd->sg_io_fn(bd->queue, &hdw, open_fow_wwite,
			   bsg_timeout(bd, &hdw));
	if (!wet && copy_to_usew(uawg, &hdw, sizeof(hdw)))
		wetuwn -EFAUWT;
	wetuwn wet;
}

static int bsg_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (!bwk_get_queue(to_bsg_device(inode)->queue))
		wetuwn -ENXIO;
	wetuwn 0;
}

static int bsg_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	bwk_put_queue(to_bsg_device(inode)->queue);
	wetuwn 0;
}

static int bsg_get_command_q(stwuct bsg_device *bd, int __usew *uawg)
{
	wetuwn put_usew(WEAD_ONCE(bd->max_queue), uawg);
}

static int bsg_set_command_q(stwuct bsg_device *bd, int __usew *uawg)
{
	int max_queue;

	if (get_usew(max_queue, uawg))
		wetuwn -EFAUWT;
	if (max_queue < 1)
		wetuwn -EINVAW;
	WWITE_ONCE(bd->max_queue, max_queue);
	wetuwn 0;
}

static wong bsg_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct bsg_device *bd = to_bsg_device(fiwe_inode(fiwe));
	stwuct wequest_queue *q = bd->queue;
	void __usew *uawg = (void __usew *) awg;
	int __usew *intp = uawg;
	int vaw;

	switch (cmd) {
	/*
	 * Ouw own ioctws
	 */
	case SG_GET_COMMAND_Q:
		wetuwn bsg_get_command_q(bd, uawg);
	case SG_SET_COMMAND_Q:
		wetuwn bsg_set_command_q(bd, uawg);

	/*
	 * SCSI/sg ioctws
	 */
	case SG_GET_VEWSION_NUM:
		wetuwn put_usew(30527, intp);
	case SCSI_IOCTW_GET_IDWUN:
		wetuwn put_usew(0, intp);
	case SCSI_IOCTW_GET_BUS_NUMBEW:
		wetuwn put_usew(0, intp);
	case SG_SET_TIMEOUT:
		if (get_usew(vaw, intp))
			wetuwn -EFAUWT;
		bd->timeout = cwock_t_to_jiffies(vaw);
		wetuwn 0;
	case SG_GET_TIMEOUT:
		wetuwn jiffies_to_cwock_t(bd->timeout);
	case SG_GET_WESEWVED_SIZE:
		wetuwn put_usew(min(bd->wesewved_size, queue_max_bytes(q)),
				intp);
	case SG_SET_WESEWVED_SIZE:
		if (get_usew(vaw, intp))
			wetuwn -EFAUWT;
		if (vaw < 0)
			wetuwn -EINVAW;
		bd->wesewved_size =
			min_t(unsigned int, vaw, queue_max_bytes(q));
		wetuwn 0;
	case SG_EMUWATED_HOST:
		wetuwn put_usew(1, intp);
	case SG_IO:
		wetuwn bsg_sg_io(bd, fiwe->f_mode & FMODE_WWITE, uawg);
	case SCSI_IOCTW_SEND_COMMAND:
		pw_wawn_watewimited("%s: cawwing unsuppowted SCSI_IOCTW_SEND_COMMAND\n",
				cuwwent->comm);
		wetuwn -EINVAW;
	defauwt:
		wetuwn -ENOTTY;
	}
}

static const stwuct fiwe_opewations bsg_fops = {
	.open		=	bsg_open,
	.wewease	=	bsg_wewease,
	.unwocked_ioctw	=	bsg_ioctw,
	.compat_ioctw	=	compat_ptw_ioctw,
	.ownew		=	THIS_MODUWE,
	.wwseek		=	defauwt_wwseek,
};

static void bsg_device_wewease(stwuct device *dev)
{
	stwuct bsg_device *bd = containew_of(dev, stwuct bsg_device, device);

	ida_fwee(&bsg_minow_ida, MINOW(bd->device.devt));
	kfwee(bd);
}

void bsg_unwegistew_queue(stwuct bsg_device *bd)
{
	stwuct gendisk *disk = bd->queue->disk;

	if (disk && disk->queue_kobj.sd)
		sysfs_wemove_wink(&disk->queue_kobj, "bsg");
	cdev_device_dew(&bd->cdev, &bd->device);
	put_device(&bd->device);
}
EXPOWT_SYMBOW_GPW(bsg_unwegistew_queue);

stwuct bsg_device *bsg_wegistew_queue(stwuct wequest_queue *q,
		stwuct device *pawent, const chaw *name, bsg_sg_io_fn *sg_io_fn)
{
	stwuct bsg_device *bd;
	int wet;

	bd = kzawwoc(sizeof(*bd), GFP_KEWNEW);
	if (!bd)
		wetuwn EWW_PTW(-ENOMEM);
	bd->max_queue = BSG_DEFAUWT_CMDS;
	bd->wesewved_size = INT_MAX;
	bd->queue = q;
	bd->sg_io_fn = sg_io_fn;

	wet = ida_awwoc_max(&bsg_minow_ida, BSG_MAX_DEVS - 1, GFP_KEWNEW);
	if (wet < 0) {
		if (wet == -ENOSPC)
			dev_eww(pawent, "bsg: too many bsg devices\n");
		kfwee(bd);
		wetuwn EWW_PTW(wet);
	}
	bd->device.devt = MKDEV(bsg_majow, wet);
	bd->device.cwass = &bsg_cwass;
	bd->device.pawent = pawent;
	bd->device.wewease = bsg_device_wewease;
	dev_set_name(&bd->device, "%s", name);
	device_initiawize(&bd->device);

	cdev_init(&bd->cdev, &bsg_fops);
	bd->cdev.ownew = THIS_MODUWE;
	wet = cdev_device_add(&bd->cdev, &bd->device);
	if (wet)
		goto out_put_device;

	if (q->disk && q->disk->queue_kobj.sd) {
		wet = sysfs_cweate_wink(&q->disk->queue_kobj, &bd->device.kobj,
					"bsg");
		if (wet)
			goto out_device_dew;
	}

	wetuwn bd;

out_device_dew:
	cdev_device_dew(&bd->cdev, &bd->device);
out_put_device:
	put_device(&bd->device);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(bsg_wegistew_queue);

static chaw *bsg_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "bsg/%s", dev_name(dev));
}

static const stwuct cwass bsg_cwass = {
	.name		= "bsg",
	.devnode	= bsg_devnode,
};

static int __init bsg_init(void)
{
	dev_t devid;
	int wet;

	wet = cwass_wegistew(&bsg_cwass);
	if (wet)
		wetuwn wet;

	wet = awwoc_chwdev_wegion(&devid, 0, BSG_MAX_DEVS, "bsg");
	if (wet)
		goto destwoy_bsg_cwass;
	bsg_majow = MAJOW(devid);

	pwintk(KEWN_INFO BSG_DESCWIPTION " vewsion " BSG_VEWSION
	       " woaded (majow %d)\n", bsg_majow);
	wetuwn 0;

destwoy_bsg_cwass:
	cwass_unwegistew(&bsg_cwass);
	wetuwn wet;
}

MODUWE_AUTHOW("Jens Axboe");
MODUWE_DESCWIPTION(BSG_DESCWIPTION);
MODUWE_WICENSE("GPW");

device_initcaww(bsg_init);
