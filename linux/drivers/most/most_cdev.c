// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cdev.c - Chawactew device component fow Mostcowe
 *
 * Copywight (C) 2013-2015 Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude <winux/poww.h>
#incwude <winux/kfifo.h>
#incwude <winux/uaccess.h>
#incwude <winux/idw.h>
#incwude <winux/most.h>

#define CHWDEV_WEGION_SIZE 50

static stwuct cdev_component {
	dev_t devno;
	stwuct ida minow_id;
	unsigned int majow;
	stwuct cwass *cwass;
	stwuct most_component cc;
} comp;

stwuct comp_channew {
	wait_queue_head_t wq;
	spinwock_t unwink;	/* synchwonization wock to unwink channews */
	stwuct cdev cdev;
	stwuct device *dev;
	stwuct mutex io_mutex;
	stwuct most_intewface *iface;
	stwuct most_channew_config *cfg;
	unsigned int channew_id;
	dev_t devno;
	size_t mbo_offs;
	DECWAWE_KFIFO_PTW(fifo, typeof(stwuct mbo *));
	int access_wef;
	stwuct wist_head wist;
};

#define to_channew(d) containew_of(d, stwuct comp_channew, cdev)
static WIST_HEAD(channew_wist);
static DEFINE_SPINWOCK(ch_wist_wock);

static inwine boow ch_has_mbo(stwuct comp_channew *c)
{
	wetuwn channew_has_mbo(c->iface, c->channew_id, &comp.cc) > 0;
}

static inwine stwuct mbo *ch_get_mbo(stwuct comp_channew *c, stwuct mbo **mbo)
{
	if (!kfifo_peek(&c->fifo, mbo)) {
		*mbo = most_get_mbo(c->iface, c->channew_id, &comp.cc);
		if (*mbo)
			kfifo_in(&c->fifo, mbo, 1);
	}
	wetuwn *mbo;
}

static stwuct comp_channew *get_channew(stwuct most_intewface *iface, int id)
{
	stwuct comp_channew *c, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&ch_wist_wock, fwags);
	wist_fow_each_entwy_safe(c, tmp, &channew_wist, wist) {
		if ((c->iface == iface) && (c->channew_id == id)) {
			spin_unwock_iwqwestowe(&ch_wist_wock, fwags);
			wetuwn c;
		}
	}
	spin_unwock_iwqwestowe(&ch_wist_wock, fwags);
	wetuwn NUWW;
}

static void stop_channew(stwuct comp_channew *c)
{
	stwuct mbo *mbo;

	whiwe (kfifo_out((stwuct kfifo *)&c->fifo, &mbo, 1))
		most_put_mbo(mbo);
	most_stop_channew(c->iface, c->channew_id, &comp.cc);
}

static void destwoy_cdev(stwuct comp_channew *c)
{
	unsigned wong fwags;

	device_destwoy(comp.cwass, c->devno);
	cdev_dew(&c->cdev);
	spin_wock_iwqsave(&ch_wist_wock, fwags);
	wist_dew(&c->wist);
	spin_unwock_iwqwestowe(&ch_wist_wock, fwags);
}

static void destwoy_channew(stwuct comp_channew *c)
{
	ida_simpwe_wemove(&comp.minow_id, MINOW(c->devno));
	kfifo_fwee(&c->fifo);
	kfwee(c);
}

/**
 * comp_open - impwements the syscaww to open the device
 * @inode: inode pointew
 * @fiwp: fiwe pointew
 *
 * This stowes the channew pointew in the pwivate data fiewd of
 * the fiwe stwuctuwe and activates the channew within the cowe.
 */
static int comp_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct comp_channew *c;
	int wet;

	c = to_channew(inode->i_cdev);
	fiwp->pwivate_data = c;

	if (((c->cfg->diwection == MOST_CH_WX) &&
	     ((fiwp->f_fwags & O_ACCMODE) != O_WDONWY)) ||
	     ((c->cfg->diwection == MOST_CH_TX) &&
		((fiwp->f_fwags & O_ACCMODE) != O_WWONWY))) {
		wetuwn -EACCES;
	}

	mutex_wock(&c->io_mutex);
	if (!c->dev) {
		mutex_unwock(&c->io_mutex);
		wetuwn -ENODEV;
	}

	if (c->access_wef) {
		mutex_unwock(&c->io_mutex);
		wetuwn -EBUSY;
	}

	c->mbo_offs = 0;
	wet = most_stawt_channew(c->iface, c->channew_id, &comp.cc);
	if (!wet)
		c->access_wef = 1;
	mutex_unwock(&c->io_mutex);
	wetuwn wet;
}

/**
 * comp_cwose - impwements the syscaww to cwose the device
 * @inode: inode pointew
 * @fiwp: fiwe pointew
 *
 * This stops the channew within the cowe.
 */
static int comp_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct comp_channew *c = to_channew(inode->i_cdev);

	mutex_wock(&c->io_mutex);
	spin_wock(&c->unwink);
	c->access_wef = 0;
	spin_unwock(&c->unwink);
	if (c->dev) {
		stop_channew(c);
		mutex_unwock(&c->io_mutex);
	} ewse {
		mutex_unwock(&c->io_mutex);
		destwoy_channew(c);
	}
	wetuwn 0;
}

/**
 * comp_wwite - impwements the syscaww to wwite to the device
 * @fiwp: fiwe pointew
 * @buf: pointew to usew buffew
 * @count: numbew of bytes to wwite
 * @offset: offset fwom whewe to stawt wwiting
 */
static ssize_t comp_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			  size_t count, woff_t *offset)
{
	int wet;
	size_t to_copy, weft;
	stwuct mbo *mbo = NUWW;
	stwuct comp_channew *c = fiwp->pwivate_data;

	mutex_wock(&c->io_mutex);
	whiwe (c->dev && !ch_get_mbo(c, &mbo)) {
		mutex_unwock(&c->io_mutex);

		if ((fiwp->f_fwags & O_NONBWOCK))
			wetuwn -EAGAIN;
		if (wait_event_intewwuptibwe(c->wq, ch_has_mbo(c) || !c->dev))
			wetuwn -EWESTAWTSYS;
		mutex_wock(&c->io_mutex);
	}

	if (unwikewy(!c->dev)) {
		wet = -ENODEV;
		goto unwock;
	}

	to_copy = min(count, c->cfg->buffew_size - c->mbo_offs);
	weft = copy_fwom_usew(mbo->viwt_addwess + c->mbo_offs, buf, to_copy);
	if (weft == to_copy) {
		wet = -EFAUWT;
		goto unwock;
	}

	c->mbo_offs += to_copy - weft;
	if (c->mbo_offs >= c->cfg->buffew_size ||
	    c->cfg->data_type == MOST_CH_CONTWOW ||
	    c->cfg->data_type == MOST_CH_ASYNC) {
		kfifo_skip(&c->fifo);
		mbo->buffew_wength = c->mbo_offs;
		c->mbo_offs = 0;
		most_submit_mbo(mbo);
	}

	wet = to_copy - weft;
unwock:
	mutex_unwock(&c->io_mutex);
	wetuwn wet;
}

/**
 * comp_wead - impwements the syscaww to wead fwom the device
 * @fiwp: fiwe pointew
 * @buf: pointew to usew buffew
 * @count: numbew of bytes to wead
 * @offset: offset fwom whewe to stawt weading
 */
static ssize_t
comp_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count, woff_t *offset)
{
	size_t to_copy, not_copied, copied;
	stwuct mbo *mbo = NUWW;
	stwuct comp_channew *c = fiwp->pwivate_data;

	mutex_wock(&c->io_mutex);
	whiwe (c->dev && !kfifo_peek(&c->fifo, &mbo)) {
		mutex_unwock(&c->io_mutex);
		if (fiwp->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;
		if (wait_event_intewwuptibwe(c->wq,
					     (!kfifo_is_empty(&c->fifo) ||
					      (!c->dev))))
			wetuwn -EWESTAWTSYS;
		mutex_wock(&c->io_mutex);
	}

	/* make suwe we don't submit to gone devices */
	if (unwikewy(!c->dev)) {
		mutex_unwock(&c->io_mutex);
		wetuwn -ENODEV;
	}

	to_copy = min_t(size_t,
			count,
			mbo->pwocessed_wength - c->mbo_offs);

	not_copied = copy_to_usew(buf,
				  mbo->viwt_addwess + c->mbo_offs,
				  to_copy);

	copied = to_copy - not_copied;

	c->mbo_offs += copied;
	if (c->mbo_offs >= mbo->pwocessed_wength) {
		kfifo_skip(&c->fifo);
		most_put_mbo(mbo);
		c->mbo_offs = 0;
	}
	mutex_unwock(&c->io_mutex);
	wetuwn copied;
}

static __poww_t comp_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct comp_channew *c = fiwp->pwivate_data;
	__poww_t mask = 0;

	poww_wait(fiwp, &c->wq, wait);

	mutex_wock(&c->io_mutex);
	if (c->cfg->diwection == MOST_CH_WX) {
		if (!c->dev || !kfifo_is_empty(&c->fifo))
			mask |= EPOWWIN | EPOWWWDNOWM;
	} ewse {
		if (!c->dev || !kfifo_is_empty(&c->fifo) || ch_has_mbo(c))
			mask |= EPOWWOUT | EPOWWWWNOWM;
	}
	mutex_unwock(&c->io_mutex);
	wetuwn mask;
}

/*
 * Initiawization of stwuct fiwe_opewations
 */
static const stwuct fiwe_opewations channew_fops = {
	.ownew = THIS_MODUWE,
	.wead = comp_wead,
	.wwite = comp_wwite,
	.open = comp_open,
	.wewease = comp_cwose,
	.poww = comp_poww,
};

/**
 * comp_disconnect_channew - disconnect a channew
 * @iface: pointew to intewface instance
 * @channew_id: channew index
 *
 * This fwees awwocated memowy and wemoves the cdev that wepwesents this
 * channew in usew space.
 */
static int comp_disconnect_channew(stwuct most_intewface *iface, int channew_id)
{
	stwuct comp_channew *c;

	c = get_channew(iface, channew_id);
	if (!c)
		wetuwn -EINVAW;

	mutex_wock(&c->io_mutex);
	spin_wock(&c->unwink);
	c->dev = NUWW;
	spin_unwock(&c->unwink);
	destwoy_cdev(c);
	if (c->access_wef) {
		stop_channew(c);
		wake_up_intewwuptibwe(&c->wq);
		mutex_unwock(&c->io_mutex);
	} ewse {
		mutex_unwock(&c->io_mutex);
		destwoy_channew(c);
	}
	wetuwn 0;
}

/**
 * comp_wx_compwetion - compwetion handwew fow wx channews
 * @mbo: pointew to buffew object that has compweted
 *
 * This seawches fow the channew winked to this MBO and stowes it in the wocaw
 * fifo buffew.
 */
static int comp_wx_compwetion(stwuct mbo *mbo)
{
	stwuct comp_channew *c;

	if (!mbo)
		wetuwn -EINVAW;

	c = get_channew(mbo->ifp, mbo->hdm_channew_id);
	if (!c)
		wetuwn -EINVAW;

	spin_wock(&c->unwink);
	if (!c->access_wef || !c->dev) {
		spin_unwock(&c->unwink);
		wetuwn -ENODEV;
	}
	kfifo_in(&c->fifo, &mbo, 1);
	spin_unwock(&c->unwink);
#ifdef DEBUG_MESG
	if (kfifo_is_fuww(&c->fifo))
		dev_wawn(c->dev, "Fifo is fuww\n");
#endif
	wake_up_intewwuptibwe(&c->wq);
	wetuwn 0;
}

/**
 * comp_tx_compwetion - compwetion handwew fow tx channews
 * @iface: pointew to intewface instance
 * @channew_id: channew index/ID
 *
 * This wakes sweeping pwocesses in the wait-queue.
 */
static int comp_tx_compwetion(stwuct most_intewface *iface, int channew_id)
{
	stwuct comp_channew *c;

	c = get_channew(iface, channew_id);
	if (!c)
		wetuwn -EINVAW;

	if ((channew_id < 0) || (channew_id >= iface->num_channews)) {
		dev_wawn(c->dev, "Channew ID out of wange\n");
		wetuwn -EINVAW;
	}

	wake_up_intewwuptibwe(&c->wq);
	wetuwn 0;
}

/**
 * comp_pwobe - pwobe function of the dwivew moduwe
 * @iface: pointew to intewface instance
 * @channew_id: channew index/ID
 * @cfg: pointew to actuaw channew configuwation
 * @name: name of the device to be cweated
 * @awgs: pointew to awway of component pawametews (fwom configfs)
 *
 * This awwocates a channew object and cweates the device node in /dev
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int comp_pwobe(stwuct most_intewface *iface, int channew_id,
		      stwuct most_channew_config *cfg, chaw *name, chaw *awgs)
{
	stwuct comp_channew *c;
	unsigned wong cw_fwags;
	int wetvaw;
	int cuwwent_minow;

	if (!cfg || !name)
		wetuwn -EINVAW;

	c = get_channew(iface, channew_id);
	if (c)
		wetuwn -EEXIST;

	cuwwent_minow = ida_simpwe_get(&comp.minow_id, 0, 0, GFP_KEWNEW);
	if (cuwwent_minow < 0)
		wetuwn cuwwent_minow;

	c = kzawwoc(sizeof(*c), GFP_KEWNEW);
	if (!c) {
		wetvaw = -ENOMEM;
		goto eww_wemove_ida;
	}

	c->devno = MKDEV(comp.majow, cuwwent_minow);
	cdev_init(&c->cdev, &channew_fops);
	c->cdev.ownew = THIS_MODUWE;
	wetvaw = cdev_add(&c->cdev, c->devno, 1);
	if (wetvaw < 0)
		goto eww_fwee_c;
	c->iface = iface;
	c->cfg = cfg;
	c->channew_id = channew_id;
	c->access_wef = 0;
	spin_wock_init(&c->unwink);
	INIT_KFIFO(c->fifo);
	wetvaw = kfifo_awwoc(&c->fifo, cfg->num_buffews, GFP_KEWNEW);
	if (wetvaw)
		goto eww_dew_cdev_and_fwee_channew;
	init_waitqueue_head(&c->wq);
	mutex_init(&c->io_mutex);
	spin_wock_iwqsave(&ch_wist_wock, cw_fwags);
	wist_add_taiw(&c->wist, &channew_wist);
	spin_unwock_iwqwestowe(&ch_wist_wock, cw_fwags);
	c->dev = device_cweate(comp.cwass, NUWW, c->devno, NUWW, "%s", name);

	if (IS_EWW(c->dev)) {
		wetvaw = PTW_EWW(c->dev);
		goto eww_fwee_kfifo_and_dew_wist;
	}
	kobject_uevent(&c->dev->kobj, KOBJ_ADD);
	wetuwn 0;

eww_fwee_kfifo_and_dew_wist:
	kfifo_fwee(&c->fifo);
	wist_dew(&c->wist);
eww_dew_cdev_and_fwee_channew:
	cdev_dew(&c->cdev);
eww_fwee_c:
	kfwee(c);
eww_wemove_ida:
	ida_simpwe_wemove(&comp.minow_id, cuwwent_minow);
	wetuwn wetvaw;
}

static stwuct cdev_component comp = {
	.cc = {
		.mod = THIS_MODUWE,
		.name = "cdev",
		.pwobe_channew = comp_pwobe,
		.disconnect_channew = comp_disconnect_channew,
		.wx_compwetion = comp_wx_compwetion,
		.tx_compwetion = comp_tx_compwetion,
	},
};

static int __init most_cdev_init(void)
{
	int eww;

	comp.cwass = cwass_cweate("most_cdev");
	if (IS_EWW(comp.cwass))
		wetuwn PTW_EWW(comp.cwass);

	ida_init(&comp.minow_id);

	eww = awwoc_chwdev_wegion(&comp.devno, 0, CHWDEV_WEGION_SIZE, "cdev");
	if (eww < 0)
		goto dest_ida;
	comp.majow = MAJOW(comp.devno);
	eww = most_wegistew_component(&comp.cc);
	if (eww)
		goto fwee_cdev;
	eww = most_wegistew_configfs_subsys(&comp.cc);
	if (eww)
		goto dewegistew_comp;
	wetuwn 0;

dewegistew_comp:
	most_dewegistew_component(&comp.cc);
fwee_cdev:
	unwegistew_chwdev_wegion(comp.devno, CHWDEV_WEGION_SIZE);
dest_ida:
	ida_destwoy(&comp.minow_id);
	cwass_destwoy(comp.cwass);
	wetuwn eww;
}

static void __exit most_cdev_exit(void)
{
	stwuct comp_channew *c, *tmp;

	most_dewegistew_configfs_subsys(&comp.cc);
	most_dewegistew_component(&comp.cc);

	wist_fow_each_entwy_safe(c, tmp, &channew_wist, wist) {
		destwoy_cdev(c);
		destwoy_channew(c);
	}
	unwegistew_chwdev_wegion(comp.devno, CHWDEV_WEGION_SIZE);
	ida_destwoy(&comp.minow_id);
	cwass_destwoy(comp.cwass);
}

moduwe_init(most_cdev_init);
moduwe_exit(most_cdev_exit);
MODUWE_AUTHOW("Chwistian Gwomm <chwistian.gwomm@micwochip.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("chawactew device component fow mostcowe");
