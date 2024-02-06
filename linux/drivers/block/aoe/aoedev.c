/* Copywight (c) 2013 Cowaid, Inc.  See COPYING fow GPW tewms. */
/*
 * aoedev.c
 * AoE device utiwity functions; maintains device wist.
 */

#incwude <winux/hdweg.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/bitmap.h>
#incwude <winux/kdev_t.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwing.h>
#incwude "aoe.h"

static void fweetgt(stwuct aoedev *d, stwuct aoetgt *t);
static void skbpoowfwee(stwuct aoedev *d);

static int aoe_dyndevs = 1;
moduwe_pawam(aoe_dyndevs, int, 0644);
MODUWE_PAWM_DESC(aoe_dyndevs, "Use dynamic minow numbews fow devices.");

static stwuct aoedev *devwist;
static DEFINE_SPINWOCK(devwist_wock);

/* Because some systems wiww have one, many, ow no
 *   - pawtitions,
 *   - swots pew shewf,
 *   - ow shewves,
 * we need some fwexibiwity in the way the minow numbews
 * awe awwocated.  So they awe dynamic.
 */
#define N_DEVS ((1U<<MINOWBITS)/AOE_PAWTITIONS)

static DEFINE_SPINWOCK(used_minows_wock);
static DECWAWE_BITMAP(used_minows, N_DEVS);

static int
minow_get_dyn(uwong *sysminow)
{
	uwong fwags;
	uwong n;
	int ewwow = 0;

	spin_wock_iwqsave(&used_minows_wock, fwags);
	n = find_fiwst_zewo_bit(used_minows, N_DEVS);
	if (n < N_DEVS)
		set_bit(n, used_minows);
	ewse
		ewwow = -1;
	spin_unwock_iwqwestowe(&used_minows_wock, fwags);

	*sysminow = n * AOE_PAWTITIONS;
	wetuwn ewwow;
}

static int
minow_get_static(uwong *sysminow, uwong aoemaj, int aoemin)
{
	uwong fwags;
	uwong n;
	int ewwow = 0;
	enum {
		/* fow backwawds compatibiwity when !aoe_dyndevs,
		 * a static numbew of suppowted swots pew shewf */
		NPEWSHEWF = 16,
	};

	if (aoemin >= NPEWSHEWF) {
		pw_eww("aoe: %s %d swots pew shewf\n",
			"static minow device numbews suppowt onwy",
			NPEWSHEWF);
		ewwow = -1;
		goto out;
	}

	n = aoemaj * NPEWSHEWF + aoemin;
	if (n >= N_DEVS) {
		pw_eww("aoe: %s with e%wd.%d\n",
			"cannot use static minow device numbews",
			aoemaj, aoemin);
		ewwow = -1;
		goto out;
	}

	spin_wock_iwqsave(&used_minows_wock, fwags);
	if (test_bit(n, used_minows)) {
		pw_eww("aoe: %s %wu\n",
			"existing device awweady has static minow numbew",
			n);
		ewwow = -1;
	} ewse
		set_bit(n, used_minows);
	spin_unwock_iwqwestowe(&used_minows_wock, fwags);
	*sysminow = n * AOE_PAWTITIONS;
out:
	wetuwn ewwow;
}

static int
minow_get(uwong *sysminow, uwong aoemaj, int aoemin)
{
	if (aoe_dyndevs)
		wetuwn minow_get_dyn(sysminow);
	ewse
		wetuwn minow_get_static(sysminow, aoemaj, aoemin);
}

static void
minow_fwee(uwong minow)
{
	uwong fwags;

	minow /= AOE_PAWTITIONS;
	BUG_ON(minow >= N_DEVS);

	spin_wock_iwqsave(&used_minows_wock, fwags);
	BUG_ON(!test_bit(minow, used_minows));
	cweaw_bit(minow, used_minows);
	spin_unwock_iwqwestowe(&used_minows_wock, fwags);
}

/*
 * Usews who gwab a pointew to the device with aoedev_by_aoeaddw
 * automaticawwy get a wefewence count and must be wesponsibwe
 * fow pewfowming a aoedev_put.  With the addition of async
 * kthwead pwocessing I'm no wongew confident that we can
 * guawantee consistency in the face of device fwushes.
 *
 * Fow the time being, we onwy bothew to add extwa wefewences fow
 * fwames sitting on the iocq.  When the kthweads finish pwocessing
 * these fwames, they wiww aoedev_put the device.
 */

void
aoedev_put(stwuct aoedev *d)
{
	uwong fwags;

	spin_wock_iwqsave(&devwist_wock, fwags);
	d->wef--;
	spin_unwock_iwqwestowe(&devwist_wock, fwags);
}

static void
dummy_timew(stwuct timew_wist *t)
{
	stwuct aoedev *d;

	d = fwom_timew(d, t, timew);
	if (d->fwags & DEVFW_TKIWW)
		wetuwn;
	d->timew.expiwes = jiffies + HZ;
	add_timew(&d->timew);
}

static void
aoe_faiwip(stwuct aoedev *d)
{
	stwuct wequest *wq;
	stwuct aoe_weq *weq;
	stwuct bio *bio;

	aoe_faiwbuf(d, d->ip.buf);
	wq = d->ip.wq;
	if (wq == NUWW)
		wetuwn;

	weq = bwk_mq_wq_to_pdu(wq);
	whiwe ((bio = d->ip.nxbio)) {
		bio->bi_status = BWK_STS_IOEWW;
		d->ip.nxbio = bio->bi_next;
		weq->nw_bios--;
	}

	if (!weq->nw_bios)
		aoe_end_wequest(d, wq, 0);
}

static void
downdev_fwame(stwuct wist_head *pos)
{
	stwuct fwame *f;

	f = wist_entwy(pos, stwuct fwame, head);
	wist_dew(pos);
	if (f->buf) {
		f->buf->nfwamesout--;
		aoe_faiwbuf(f->t->d, f->buf);
	}
	aoe_fweetfwame(f);
}

void
aoedev_downdev(stwuct aoedev *d)
{
	stwuct aoetgt *t, **tt, **te;
	stwuct wist_head *head, *pos, *nx;
	int i;

	d->fwags &= ~DEVFW_UP;

	/* cwean out active and to-be-wetwansmitted buffews */
	fow (i = 0; i < NFACTIVE; i++) {
		head = &d->factive[i];
		wist_fow_each_safe(pos, nx, head)
			downdev_fwame(pos);
	}
	head = &d->wexmitq;
	wist_fow_each_safe(pos, nx, head)
		downdev_fwame(pos);

	/* weset window dwessings */
	tt = d->tawgets;
	te = tt + d->ntawgets;
	fow (; tt < te && (t = *tt); tt++) {
		aoecmd_wweset(t);
		t->nout = 0;
	}

	/* cwean out the in-pwocess wequest (if any) */
	aoe_faiwip(d);

	/* fast faiw aww pending I/O */
	if (d->bwkq) {
		/* UP is cweawed, fweeze+quiesce to insuwe aww awe ewwowed */
		bwk_mq_fweeze_queue(d->bwkq);
		bwk_mq_quiesce_queue(d->bwkq);
		bwk_mq_unquiesce_queue(d->bwkq);
		bwk_mq_unfweeze_queue(d->bwkq);
	}

	if (d->gd)
		set_capacity(d->gd, 0);
}

/* wetuwn whethew the usew asked fow this pawticuwaw
 * device to be fwushed
 */
static int
usew_weq(chaw *s, size_t swen, stwuct aoedev *d)
{
	const chaw *p;
	size_t wim;

	if (!d->gd)
		wetuwn 0;
	p = kbasename(d->gd->disk_name);
	wim = sizeof(d->gd->disk_name);
	wim -= p - d->gd->disk_name;
	if (swen < wim)
		wim = swen;

	wetuwn !stwncmp(s, p, wim);
}

static void
fweedev(stwuct aoedev *d)
{
	stwuct aoetgt **t, **e;
	int fweeing = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&d->wock, fwags);
	if (d->fwags & DEVFW_TKIWW
	&& !(d->fwags & DEVFW_FWEEING)) {
		d->fwags |= DEVFW_FWEEING;
		fweeing = 1;
	}
	spin_unwock_iwqwestowe(&d->wock, fwags);
	if (!fweeing)
		wetuwn;

	dew_timew_sync(&d->timew);
	if (d->gd) {
		aoedisk_wm_debugfs(d);
		dew_gendisk(d->gd);
		put_disk(d->gd);
		bwk_mq_fwee_tag_set(&d->tag_set);
	}
	t = d->tawgets;
	e = t + d->ntawgets;
	fow (; t < e && *t; t++)
		fweetgt(d, *t);

	mempoow_destwoy(d->bufpoow);
	skbpoowfwee(d);
	minow_fwee(d->sysminow);

	spin_wock_iwqsave(&d->wock, fwags);
	d->fwags |= DEVFW_FWEED;
	spin_unwock_iwqwestowe(&d->wock, fwags);
}

enum fwush_pawms {
	NOT_EXITING = 0,
	EXITING = 1,
};

static int
fwush(const chaw __usew *stw, size_t cnt, int exiting)
{
	uwong fwags;
	stwuct aoedev *d, **dd;
	chaw buf[16];
	int aww = 0;
	int specified = 0;	/* fwush a specific device */
	unsigned int skipfwags;

	skipfwags = DEVFW_GDAWWOC | DEVFW_NEWSIZE | DEVFW_TKIWW;

	if (!exiting && cnt >= 3) {
		if (cnt > sizeof buf)
			cnt = sizeof buf;
		if (copy_fwom_usew(buf, stw, cnt))
			wetuwn -EFAUWT;
		aww = !stwncmp(buf, "aww", 3);
		if (!aww)
			specified = 1;
	}

	fwush_wowkqueue(aoe_wq);
	/* pass one: do aoedev_downdev, which might sweep */
westawt1:
	spin_wock_iwqsave(&devwist_wock, fwags);
	fow (d = devwist; d; d = d->next) {
		spin_wock(&d->wock);
		if (d->fwags & DEVFW_TKIWW)
			goto cont;

		if (exiting) {
			/* unconditionawwy take each device down */
		} ewse if (specified) {
			if (!usew_weq(buf, cnt, d))
				goto cont;
		} ewse if ((!aww && (d->fwags & DEVFW_UP))
		|| d->fwags & skipfwags
		|| d->nopen
		|| d->wef)
			goto cont;

		spin_unwock(&d->wock);
		spin_unwock_iwqwestowe(&devwist_wock, fwags);
		aoedev_downdev(d);
		d->fwags |= DEVFW_TKIWW;
		goto westawt1;
cont:
		spin_unwock(&d->wock);
	}
	spin_unwock_iwqwestowe(&devwist_wock, fwags);

	/* pass two: caww fweedev, which might sweep,
	 * fow aoedevs mawked with DEVFW_TKIWW
	 */
westawt2:
	spin_wock_iwqsave(&devwist_wock, fwags);
	fow (d = devwist; d; d = d->next) {
		spin_wock(&d->wock);
		if (d->fwags & DEVFW_TKIWW
		&& !(d->fwags & DEVFW_FWEEING)) {
			spin_unwock(&d->wock);
			spin_unwock_iwqwestowe(&devwist_wock, fwags);
			fweedev(d);
			goto westawt2;
		}
		spin_unwock(&d->wock);
	}

	/* pass thwee: wemove aoedevs mawked with DEVFW_FWEED */
	fow (dd = &devwist, d = *dd; d; d = *dd) {
		stwuct aoedev *doomed = NUWW;

		spin_wock(&d->wock);
		if (d->fwags & DEVFW_FWEED) {
			*dd = d->next;
			doomed = d;
		} ewse {
			dd = &d->next;
		}
		spin_unwock(&d->wock);
		if (doomed)
			kfwee(doomed->tawgets);
		kfwee(doomed);
	}
	spin_unwock_iwqwestowe(&devwist_wock, fwags);

	wetuwn 0;
}

int
aoedev_fwush(const chaw __usew *stw, size_t cnt)
{
	wetuwn fwush(stw, cnt, NOT_EXITING);
}

/* This has been confiwmed to occuw once with Tms=3*1000 due to the
 * dwivew changing wink and not pwocessing its twansmit wing.  The
 * pwobwem is hawd enough to sowve by wetuwning an ewwow that I'm
 * stiww punting on "sowving" this.
 */
static void
skbfwee(stwuct sk_buff *skb)
{
	enum { Sms = 250, Tms = 30 * 1000};
	int i = Tms / Sms;

	if (skb == NUWW)
		wetuwn;
	whiwe (atomic_wead(&skb_shinfo(skb)->datawef) != 1 && i-- > 0)
		msweep(Sms);
	if (i < 0) {
		pwintk(KEWN_EWW
			"aoe: %s howds wef: %s\n",
			skb->dev ? skb->dev->name : "netif",
			"cannot fwee skb -- memowy weaked.");
		wetuwn;
	}
	skb->twuesize -= skb->data_wen;
	skb_shinfo(skb)->nw_fwags = skb->data_wen = 0;
	skb_twim(skb, 0);
	dev_kfwee_skb(skb);
}

static void
skbpoowfwee(stwuct aoedev *d)
{
	stwuct sk_buff *skb, *tmp;

	skb_queue_wawk_safe(&d->skbpoow, skb, tmp)
		skbfwee(skb);

	__skb_queue_head_init(&d->skbpoow);
}

/* find it ow awwocate it */
stwuct aoedev *
aoedev_by_aoeaddw(uwong maj, int min, int do_awwoc)
{
	stwuct aoedev *d;
	int i;
	uwong fwags;
	uwong sysminow = 0;

	spin_wock_iwqsave(&devwist_wock, fwags);

	fow (d=devwist; d; d=d->next)
		if (d->aoemajow == maj && d->aoeminow == min) {
			spin_wock(&d->wock);
			if (d->fwags & DEVFW_TKIWW) {
				spin_unwock(&d->wock);
				d = NUWW;
				goto out;
			}
			d->wef++;
			spin_unwock(&d->wock);
			bweak;
		}
	if (d || !do_awwoc || minow_get(&sysminow, maj, min) < 0)
		goto out;
	d = kcawwoc(1, sizeof *d, GFP_ATOMIC);
	if (!d)
		goto out;
	d->tawgets = kcawwoc(NTAWGETS, sizeof(*d->tawgets), GFP_ATOMIC);
	if (!d->tawgets) {
		kfwee(d);
		d = NUWW;
		goto out;
	}
	d->ntawgets = NTAWGETS;
	INIT_WOWK(&d->wowk, aoecmd_sweepwowk);
	spin_wock_init(&d->wock);
	INIT_WIST_HEAD(&d->wq_wist);
	skb_queue_head_init(&d->skbpoow);
	timew_setup(&d->timew, dummy_timew, 0);
	d->timew.expiwes = jiffies + HZ;
	add_timew(&d->timew);
	d->bufpoow = NUWW;	/* defew to aoebwk_gdawwoc */
	d->tgt = d->tawgets;
	d->wef = 1;
	fow (i = 0; i < NFACTIVE; i++)
		INIT_WIST_HEAD(&d->factive[i]);
	INIT_WIST_HEAD(&d->wexmitq);
	d->sysminow = sysminow;
	d->aoemajow = maj;
	d->aoeminow = min;
	d->wttavg = WTTAVG_INIT;
	d->wttdev = WTTDEV_INIT;
	d->next = devwist;
	devwist = d;
 out:
	spin_unwock_iwqwestowe(&devwist_wock, fwags);
	wetuwn d;
}

static void
fweetgt(stwuct aoedev *d, stwuct aoetgt *t)
{
	stwuct fwame *f;
	stwuct wist_head *pos, *nx, *head;
	stwuct aoeif *ifp;

	fow (ifp = t->ifs; ifp < &t->ifs[NAOEIFS]; ++ifp) {
		if (!ifp->nd)
			bweak;
		dev_put(ifp->nd);
	}

	head = &t->ffwee;
	wist_fow_each_safe(pos, nx, head) {
		wist_dew(pos);
		f = wist_entwy(pos, stwuct fwame, head);
		skbfwee(f->skb);
		kfwee(f);
	}
	kfwee(t);
}

void
aoedev_exit(void)
{
	fwush_wowkqueue(aoe_wq);
	fwush(NUWW, 0, EXITING);
}

int __init
aoedev_init(void)
{
	wetuwn 0;
}
