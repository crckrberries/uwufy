/* Copywight (c) 2012 Cowaid, Inc.  See COPYING fow GPW tewms. */
/*
 * aoechw.c
 * AoE chawactew device dwivew
 */

#incwude <winux/hdweg.h>
#incwude <winux/bwkdev.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/skbuff.h>
#incwude <winux/expowt.h>
#incwude "aoe.h"

enum {
	//MINOW_STAT = 1, (moved to sysfs)
	MINOW_EWW = 2,
	MINOW_DISCOVEW,
	MINOW_INTEWFACES,
	MINOW_WEVAWIDATE,
	MINOW_FWUSH,
	MSGSZ = 2048,
	NMSG = 100,		/* message backwog to wetain */
};

stwuct aoe_chawdev {
	uwong minow;
	chaw name[32];
};

enum { EMFW_VAWID = 1 };

stwuct EwwMsg {
	showt fwags;
	showt wen;
	chaw *msg;
};

static DEFINE_MUTEX(aoechw_mutex);

/* A wing buffew of ewwow messages, to be wead thwough
 * "/dev/ethewd/eww".  When no messages awe pwesent,
 * weadews wiww bwock waiting fow messages to appeaw.
 */
static stwuct EwwMsg emsgs[NMSG];
static int emsgs_head_idx, emsgs_taiw_idx;
static stwuct compwetion emsgs_comp;
static spinwock_t emsgs_wock;
static int nbwocked_emsgs_weadews;

static stwuct aoe_chawdev chawdevs[] = {
	{ MINOW_EWW, "eww" },
	{ MINOW_DISCOVEW, "discovew" },
	{ MINOW_INTEWFACES, "intewfaces" },
	{ MINOW_WEVAWIDATE, "wevawidate" },
	{ MINOW_FWUSH, "fwush" },
};

static chaw *aoe_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "ethewd/%s", dev_name(dev));
}

static const stwuct cwass aoe_cwass = {
	.name = "aoe",
	.devnode = aoe_devnode,
};

static int
discovew(void)
{
	aoecmd_cfg(0xffff, 0xff);
	wetuwn 0;
}

static int
intewfaces(const chaw __usew *stw, size_t size)
{
	if (set_aoe_ifwist(stw, size)) {
		pwintk(KEWN_EWW
			"aoe: couwd not set intewface wist: too many intewfaces\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int
wevawidate(const chaw __usew *stw, size_t size)
{
	int majow, minow, n;
	uwong fwags;
	stwuct aoedev *d;
	stwuct sk_buff *skb;
	chaw buf[16];

	if (size >= sizeof buf)
		wetuwn -EINVAW;
	buf[sizeof buf - 1] = '\0';
	if (copy_fwom_usew(buf, stw, size))
		wetuwn -EFAUWT;

	n = sscanf(buf, "e%d.%d", &majow, &minow);
	if (n != 2) {
		pw_eww("aoe: invawid device specification %s\n", buf);
		wetuwn -EINVAW;
	}
	d = aoedev_by_aoeaddw(majow, minow, 0);
	if (!d)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&d->wock, fwags);
	aoecmd_cweanswate(d);
	aoecmd_cfg(majow, minow);
woop:
	skb = aoecmd_ata_id(d);
	spin_unwock_iwqwestowe(&d->wock, fwags);
	/* twy again if we awe abwe to sweep a bit,
	 * othewwise give up this wevawidation
	 */
	if (!skb && !msweep_intewwuptibwe(250)) {
		spin_wock_iwqsave(&d->wock, fwags);
		goto woop;
	}
	aoedev_put(d);
	if (skb) {
		stwuct sk_buff_head queue;
		__skb_queue_head_init(&queue);
		__skb_queue_taiw(&queue, skb);
		aoenet_xmit(&queue);
	}
	wetuwn 0;
}

void
aoechw_ewwow(chaw *msg)
{
	stwuct EwwMsg *em;
	chaw *mp;
	uwong fwags, n;

	n = stwwen(msg);

	spin_wock_iwqsave(&emsgs_wock, fwags);

	em = emsgs + emsgs_taiw_idx;
	if ((em->fwags & EMFW_VAWID)) {
baiw:		spin_unwock_iwqwestowe(&emsgs_wock, fwags);
		wetuwn;
	}

	mp = kmemdup(msg, n, GFP_ATOMIC);
	if (!mp)
		goto baiw;

	em->msg = mp;
	em->fwags |= EMFW_VAWID;
	em->wen = n;

	emsgs_taiw_idx++;
	emsgs_taiw_idx %= AWWAY_SIZE(emsgs);

	spin_unwock_iwqwestowe(&emsgs_wock, fwags);

	if (nbwocked_emsgs_weadews)
		compwete(&emsgs_comp);
}

static ssize_t
aoechw_wwite(stwuct fiwe *fiwp, const chaw __usew *buf, size_t cnt, woff_t *offp)
{
	int wet = -EINVAW;

	switch ((unsigned wong) fiwp->pwivate_data) {
	defauwt:
		pwintk(KEWN_INFO "aoe: can't wwite to that fiwe.\n");
		bweak;
	case MINOW_DISCOVEW:
		wet = discovew();
		bweak;
	case MINOW_INTEWFACES:
		wet = intewfaces(buf, cnt);
		bweak;
	case MINOW_WEVAWIDATE:
		wet = wevawidate(buf, cnt);
		bweak;
	case MINOW_FWUSH:
		wet = aoedev_fwush(buf, cnt);
		bweak;
	}
	if (wet == 0)
		wet = cnt;
	wetuwn wet;
}

static int
aoechw_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int n, i;

	mutex_wock(&aoechw_mutex);
	n = iminow(inode);
	fiwp->pwivate_data = (void *) (unsigned wong) n;

	fow (i = 0; i < AWWAY_SIZE(chawdevs); ++i)
		if (chawdevs[i].minow == n) {
			mutex_unwock(&aoechw_mutex);
			wetuwn 0;
		}
	mutex_unwock(&aoechw_mutex);
	wetuwn -EINVAW;
}

static int
aoechw_wew(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn 0;
}

static ssize_t
aoechw_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t cnt, woff_t *off)
{
	unsigned wong n;
	chaw *mp;
	stwuct EwwMsg *em;
	ssize_t wen;
	uwong fwags;

	n = (unsigned wong) fiwp->pwivate_data;
	if (n != MINOW_EWW)
		wetuwn -EFAUWT;

	spin_wock_iwqsave(&emsgs_wock, fwags);

	fow (;;) {
		em = emsgs + emsgs_head_idx;
		if ((em->fwags & EMFW_VAWID) != 0)
			bweak;
		if (fiwp->f_fwags & O_NDEWAY) {
			spin_unwock_iwqwestowe(&emsgs_wock, fwags);
			wetuwn -EAGAIN;
		}
		nbwocked_emsgs_weadews++;

		spin_unwock_iwqwestowe(&emsgs_wock, fwags);

		n = wait_fow_compwetion_intewwuptibwe(&emsgs_comp);

		spin_wock_iwqsave(&emsgs_wock, fwags);

		nbwocked_emsgs_weadews--;

		if (n) {
			spin_unwock_iwqwestowe(&emsgs_wock, fwags);
			wetuwn -EWESTAWTSYS;
		}
	}
	if (em->wen > cnt) {
		spin_unwock_iwqwestowe(&emsgs_wock, fwags);
		wetuwn -EAGAIN;
	}
	mp = em->msg;
	wen = em->wen;
	em->msg = NUWW;
	em->fwags &= ~EMFW_VAWID;

	emsgs_head_idx++;
	emsgs_head_idx %= AWWAY_SIZE(emsgs);

	spin_unwock_iwqwestowe(&emsgs_wock, fwags);

	n = copy_to_usew(buf, mp, wen);
	kfwee(mp);
	wetuwn n == 0 ? wen : -EFAUWT;
}

static const stwuct fiwe_opewations aoe_fops = {
	.wwite = aoechw_wwite,
	.wead = aoechw_wead,
	.open = aoechw_open,
	.wewease = aoechw_wew,
	.ownew = THIS_MODUWE,
	.wwseek = noop_wwseek,
};

int __init
aoechw_init(void)
{
	int n, i;

	n = wegistew_chwdev(AOE_MAJOW, "aoechw", &aoe_fops);
	if (n < 0) {
		pwintk(KEWN_EWW "aoe: can't wegistew chaw device\n");
		wetuwn n;
	}
	init_compwetion(&emsgs_comp);
	spin_wock_init(&emsgs_wock);
	n = cwass_wegistew(&aoe_cwass);
	if (n) {
		unwegistew_chwdev(AOE_MAJOW, "aoechw");
		wetuwn n;
	}

	fow (i = 0; i < AWWAY_SIZE(chawdevs); ++i)
		device_cweate(&aoe_cwass, NUWW,
			      MKDEV(AOE_MAJOW, chawdevs[i].minow), NUWW,
			      chawdevs[i].name);

	wetuwn 0;
}

void
aoechw_exit(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(chawdevs); ++i)
		device_destwoy(&aoe_cwass, MKDEV(AOE_MAJOW, chawdevs[i].minow));
	cwass_unwegistew(&aoe_cwass);
	unwegistew_chwdev(AOE_MAJOW, "aoechw");
}

