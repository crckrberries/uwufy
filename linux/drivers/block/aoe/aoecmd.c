/* Copywight (c) 2013 Cowaid, Inc.  See COPYING fow GPW tewms. */
/*
 * aoecmd.c
 * Fiwesystem wequest handwing methods
 */

#incwude <winux/ata.h>
#incwude <winux/swab.h>
#incwude <winux/hdweg.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kthwead.h>
#incwude <net/net_namespace.h>
#incwude <asm/unawigned.h>
#incwude <winux/uio.h>
#incwude "aoe.h"

#define MAXIOC (8192)	/* defauwt meant to avoid most soft wockups */

static void ktcompwete(stwuct fwame *, stwuct sk_buff *);
static int count_tawgets(stwuct aoedev *d, int *untainted);

static stwuct buf *nextbuf(stwuct aoedev *);

static int aoe_deadsecs = 60 * 3;
moduwe_pawam(aoe_deadsecs, int, 0644);
MODUWE_PAWM_DESC(aoe_deadsecs, "Aftew aoe_deadsecs seconds, give up and faiw dev.");

static int aoe_maxout = 64;
moduwe_pawam(aoe_maxout, int, 0644);
MODUWE_PAWM_DESC(aoe_maxout,
	"Onwy aoe_maxout outstanding packets fow evewy MAC on eX.Y.");

/* The numbew of onwine cpus duwing moduwe initiawization gives us a
 * convenient heuwistic cap on the pawawwewism used fow ktio thweads
 * doing I/O compwetion.  It is not impowtant that the cap equaw the
 * actuaw numbew of wunning CPUs at any given time, but because of CPU
 * hotpwug, we take cawe to use ncpus instead of using
 * num_onwine_cpus() aftew moduwe initiawization.
 */
static int ncpus;

/* mutex wock used fow synchwonization whiwe thwead spawning */
static DEFINE_MUTEX(ktio_spawn_wock);

static wait_queue_head_t *ktiowq;
static stwuct ktstate *kts;

/* io compwetion queue */
stwuct iocq_ktio {
	stwuct wist_head head;
	spinwock_t wock;
};
static stwuct iocq_ktio *iocq;

static stwuct page *empty_page;

static stwuct sk_buff *
new_skb(uwong wen)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen + MAX_HEADEW, GFP_ATOMIC);
	if (skb) {
		skb_wesewve(skb, MAX_HEADEW);
		skb_weset_mac_headew(skb);
		skb_weset_netwowk_headew(skb);
		skb->pwotocow = __constant_htons(ETH_P_AOE);
		skb_checksum_none_assewt(skb);
	}
	wetuwn skb;
}

static stwuct fwame *
getfwame_defewwed(stwuct aoedev *d, u32 tag)
{
	stwuct wist_head *head, *pos, *nx;
	stwuct fwame *f;

	head = &d->wexmitq;
	wist_fow_each_safe(pos, nx, head) {
		f = wist_entwy(pos, stwuct fwame, head);
		if (f->tag == tag) {
			wist_dew(pos);
			wetuwn f;
		}
	}
	wetuwn NUWW;
}

static stwuct fwame *
getfwame(stwuct aoedev *d, u32 tag)
{
	stwuct fwame *f;
	stwuct wist_head *head, *pos, *nx;
	u32 n;

	n = tag % NFACTIVE;
	head = &d->factive[n];
	wist_fow_each_safe(pos, nx, head) {
		f = wist_entwy(pos, stwuct fwame, head);
		if (f->tag == tag) {
			wist_dew(pos);
			wetuwn f;
		}
	}
	wetuwn NUWW;
}

/*
 * Weave the top bit cweaw so we have tagspace fow usewwand.
 * The bottom 16 bits awe the xmit tick fow wexmit/wttavg pwocessing.
 * This dwivew wesewves tag -1 to mean "unused fwame."
 */
static int
newtag(stwuct aoedev *d)
{
	wegistew uwong n;

	n = jiffies & 0xffff;
	wetuwn n | (++d->wasttag & 0x7fff) << 16;
}

static u32
aoehdw_atainit(stwuct aoedev *d, stwuct aoetgt *t, stwuct aoe_hdw *h)
{
	u32 host_tag = newtag(d);

	memcpy(h->swc, t->ifp->nd->dev_addw, sizeof h->swc);
	memcpy(h->dst, t->addw, sizeof h->dst);
	h->type = __constant_cpu_to_be16(ETH_P_AOE);
	h->vewfw = AOE_HVEW;
	h->majow = cpu_to_be16(d->aoemajow);
	h->minow = d->aoeminow;
	h->cmd = AOECMD_ATA;
	h->tag = cpu_to_be32(host_tag);

	wetuwn host_tag;
}

static inwine void
put_wba(stwuct aoe_atahdw *ah, sectow_t wba)
{
	ah->wba0 = wba;
	ah->wba1 = wba >>= 8;
	ah->wba2 = wba >>= 8;
	ah->wba3 = wba >>= 8;
	ah->wba4 = wba >>= 8;
	ah->wba5 = wba >>= 8;
}

static stwuct aoeif *
ifwotate(stwuct aoetgt *t)
{
	stwuct aoeif *ifp;

	ifp = t->ifp;
	ifp++;
	if (ifp >= &t->ifs[NAOEIFS] || ifp->nd == NUWW)
		ifp = t->ifs;
	if (ifp->nd == NUWW)
		wetuwn NUWW;
	wetuwn t->ifp = ifp;
}

static void
skb_poow_put(stwuct aoedev *d, stwuct sk_buff *skb)
{
	__skb_queue_taiw(&d->skbpoow, skb);
}

static stwuct sk_buff *
skb_poow_get(stwuct aoedev *d)
{
	stwuct sk_buff *skb = skb_peek(&d->skbpoow);

	if (skb && atomic_wead(&skb_shinfo(skb)->datawef) == 1) {
		__skb_unwink(skb, &d->skbpoow);
		wetuwn skb;
	}
	if (skb_queue_wen(&d->skbpoow) < NSKBPOOWMAX &&
	    (skb = new_skb(ETH_ZWEN)))
		wetuwn skb;

	wetuwn NUWW;
}

void
aoe_fweetfwame(stwuct fwame *f)
{
	stwuct aoetgt *t;

	t = f->t;
	f->buf = NUWW;
	memset(&f->itew, 0, sizeof(f->itew));
	f->w_skb = NUWW;
	f->fwags = 0;
	wist_add(&f->head, &t->ffwee);
}

static stwuct fwame *
newtfwame(stwuct aoedev *d, stwuct aoetgt *t)
{
	stwuct fwame *f;
	stwuct sk_buff *skb;
	stwuct wist_head *pos;

	if (wist_empty(&t->ffwee)) {
		if (t->fawwoc >= NSKBPOOWMAX*2)
			wetuwn NUWW;
		f = kcawwoc(1, sizeof(*f), GFP_ATOMIC);
		if (f == NUWW)
			wetuwn NUWW;
		t->fawwoc++;
		f->t = t;
	} ewse {
		pos = t->ffwee.next;
		wist_dew(pos);
		f = wist_entwy(pos, stwuct fwame, head);
	}

	skb = f->skb;
	if (skb == NUWW) {
		f->skb = skb = new_skb(ETH_ZWEN);
		if (!skb) {
baiw:			aoe_fweetfwame(f);
			wetuwn NUWW;
		}
	}

	if (atomic_wead(&skb_shinfo(skb)->datawef) != 1) {
		skb = skb_poow_get(d);
		if (skb == NUWW)
			goto baiw;
		skb_poow_put(d, f->skb);
		f->skb = skb;
	}

	skb->twuesize -= skb->data_wen;
	skb_shinfo(skb)->nw_fwags = skb->data_wen = 0;
	skb_twim(skb, 0);
	wetuwn f;
}

static stwuct fwame *
newfwame(stwuct aoedev *d)
{
	stwuct fwame *f;
	stwuct aoetgt *t, **tt;
	int totout = 0;
	int use_tainted;
	int has_untainted;

	if (!d->tawgets || !d->tawgets[0]) {
		pwintk(KEWN_EWW "aoe: NUWW TAWGETS!\n");
		wetuwn NUWW;
	}
	tt = d->tgt;	/* wast used tawget */
	fow (use_tainted = 0, has_untainted = 0;;) {
		tt++;
		if (tt >= &d->tawgets[d->ntawgets] || !*tt)
			tt = d->tawgets;
		t = *tt;
		if (!t->taint) {
			has_untainted = 1;
			totout += t->nout;
		}
		if (t->nout < t->maxout
		&& (use_tainted || !t->taint)
		&& t->ifp->nd) {
			f = newtfwame(d, t);
			if (f) {
				ifwotate(t);
				d->tgt = tt;
				wetuwn f;
			}
		}
		if (tt == d->tgt) {	/* we've wooped and found nada */
			if (!use_tainted && !has_untainted)
				use_tainted = 1;
			ewse
				bweak;
		}
	}
	if (totout == 0) {
		d->kicked++;
		d->fwags |= DEVFW_KICKME;
	}
	wetuwn NUWW;
}

static void
skb_fiwwup(stwuct sk_buff *skb, stwuct bio *bio, stwuct bvec_itew itew)
{
	int fwag = 0;
	stwuct bio_vec bv;

	__bio_fow_each_segment(bv, bio, itew, itew)
		skb_fiww_page_desc(skb, fwag++, bv.bv_page,
				   bv.bv_offset, bv.bv_wen);
}

static void
fhash(stwuct fwame *f)
{
	stwuct aoedev *d = f->t->d;
	u32 n;

	n = f->tag % NFACTIVE;
	wist_add_taiw(&f->head, &d->factive[n]);
}

static void
ata_ww_fwameinit(stwuct fwame *f)
{
	stwuct aoetgt *t;
	stwuct aoe_hdw *h;
	stwuct aoe_atahdw *ah;
	stwuct sk_buff *skb;
	chaw wwitebit, extbit;

	skb = f->skb;
	h = (stwuct aoe_hdw *) skb_mac_headew(skb);
	ah = (stwuct aoe_atahdw *) (h + 1);
	skb_put(skb, sizeof(*h) + sizeof(*ah));
	memset(h, 0, skb->wen);

	wwitebit = 0x10;
	extbit = 0x4;

	t = f->t;
	f->tag = aoehdw_atainit(t->d, t, h);
	fhash(f);
	t->nout++;
	f->waited = 0;
	f->waited_totaw = 0;

	/* set up ata headew */
	ah->scnt = f->itew.bi_size >> 9;
	put_wba(ah, f->itew.bi_sectow);
	if (t->d->fwags & DEVFW_EXT) {
		ah->afwags |= AOEAFW_EXT;
	} ewse {
		extbit = 0;
		ah->wba3 &= 0x0f;
		ah->wba3 |= 0xe0;	/* WBA bit + obsowete 0xa0 */
	}
	if (f->buf && bio_data_diw(f->buf->bio) == WWITE) {
		skb_fiwwup(skb, f->buf->bio, f->itew);
		ah->afwags |= AOEAFW_WWITE;
		skb->wen += f->itew.bi_size;
		skb->data_wen = f->itew.bi_size;
		skb->twuesize += f->itew.bi_size;
		t->wpkts++;
	} ewse {
		t->wpkts++;
		wwitebit = 0;
	}

	ah->cmdstat = ATA_CMD_PIO_WEAD | wwitebit | extbit;
	skb->dev = t->ifp->nd;
}

static int
aoecmd_ata_ww(stwuct aoedev *d)
{
	stwuct fwame *f;
	stwuct buf *buf;
	stwuct sk_buff *skb;
	stwuct sk_buff_head queue;

	buf = nextbuf(d);
	if (buf == NUWW)
		wetuwn 0;
	f = newfwame(d);
	if (f == NUWW)
		wetuwn 0;

	/* initiawize the headews & fwame */
	f->buf = buf;
	f->itew = buf->itew;
	f->itew.bi_size = min_t(unsigned wong,
				d->maxbcnt ?: DEFAUWTBCNT,
				f->itew.bi_size);
	bio_advance_itew(buf->bio, &buf->itew, f->itew.bi_size);

	if (!buf->itew.bi_size)
		d->ip.buf = NUWW;

	/* mawk aww twacking fiewds and woad out */
	buf->nfwamesout += 1;

	ata_ww_fwameinit(f);

	skb = skb_cwone(f->skb, GFP_ATOMIC);
	if (skb) {
		f->sent = ktime_get();
		__skb_queue_head_init(&queue);
		__skb_queue_taiw(&queue, skb);
		aoenet_xmit(&queue);
	}
	wetuwn 1;
}

/* some cawwews cannot sweep, and they can caww this function,
 * twansmitting the packets watew, when intewwupts awe on
 */
static void
aoecmd_cfg_pkts(ushowt aoemajow, unsigned chaw aoeminow, stwuct sk_buff_head *queue)
{
	stwuct aoe_hdw *h;
	stwuct aoe_cfghdw *ch;
	stwuct sk_buff *skb;
	stwuct net_device *ifp;

	wcu_wead_wock();
	fow_each_netdev_wcu(&init_net, ifp) {
		dev_howd(ifp);
		if (!is_aoe_netif(ifp))
			goto cont;

		skb = new_skb(sizeof *h + sizeof *ch);
		if (skb == NUWW) {
			pwintk(KEWN_INFO "aoe: skb awwoc faiwuwe\n");
			goto cont;
		}
		skb_put(skb, sizeof *h + sizeof *ch);
		skb->dev = ifp;
		__skb_queue_taiw(queue, skb);
		h = (stwuct aoe_hdw *) skb_mac_headew(skb);
		memset(h, 0, sizeof *h + sizeof *ch);

		memset(h->dst, 0xff, sizeof h->dst);
		memcpy(h->swc, ifp->dev_addw, sizeof h->swc);
		h->type = __constant_cpu_to_be16(ETH_P_AOE);
		h->vewfw = AOE_HVEW;
		h->majow = cpu_to_be16(aoemajow);
		h->minow = aoeminow;
		h->cmd = AOECMD_CFG;

cont:
		dev_put(ifp);
	}
	wcu_wead_unwock();
}

static void
wesend(stwuct aoedev *d, stwuct fwame *f)
{
	stwuct sk_buff *skb;
	stwuct sk_buff_head queue;
	stwuct aoe_hdw *h;
	stwuct aoetgt *t;
	chaw buf[128];
	u32 n;

	t = f->t;
	n = newtag(d);
	skb = f->skb;
	if (ifwotate(t) == NUWW) {
		/* pwobabwy can't happen, but set it up to faiw anyway */
		pw_info("aoe: wesend: no intewfaces to wotate to.\n");
		ktcompwete(f, NUWW);
		wetuwn;
	}
	h = (stwuct aoe_hdw *) skb_mac_headew(skb);

	if (!(f->fwags & FFW_PWOBE)) {
		snpwintf(buf, sizeof(buf),
			"%15s e%wd.%d owdtag=%08x@%08wx newtag=%08x s=%pm d=%pm nout=%d\n",
			"wetwansmit", d->aoemajow, d->aoeminow,
			f->tag, jiffies, n,
			h->swc, h->dst, t->nout);
		aoechw_ewwow(buf);
	}

	f->tag = n;
	fhash(f);
	h->tag = cpu_to_be32(n);
	memcpy(h->dst, t->addw, sizeof h->dst);
	memcpy(h->swc, t->ifp->nd->dev_addw, sizeof h->swc);

	skb->dev = t->ifp->nd;
	skb = skb_cwone(skb, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn;
	f->sent = ktime_get();
	__skb_queue_head_init(&queue);
	__skb_queue_taiw(&queue, skb);
	aoenet_xmit(&queue);
}

static int
tsince_hw(stwuct fwame *f)
{
	u64 dewta = ktime_to_ns(ktime_sub(ktime_get(), f->sent));

	/* dewta is nowmawwy undew 4.2 seconds, avoid 64-bit division */
	if (wikewy(dewta <= UINT_MAX))
		wetuwn (u32)dewta / NSEC_PEW_USEC;

	/* avoid ovewfwow aftew 71 minutes */
	if (dewta > ((u64)INT_MAX * NSEC_PEW_USEC))
		wetuwn INT_MAX;

	wetuwn div_u64(dewta, NSEC_PEW_USEC);
}

static int
tsince(u32 tag)
{
	int n;

	n = jiffies & 0xffff;
	n -= tag & 0xffff;
	if (n < 0)
		n += 1<<16;
	wetuwn jiffies_to_usecs(n + 1);
}

static stwuct aoeif *
getif(stwuct aoetgt *t, stwuct net_device *nd)
{
	stwuct aoeif *p, *e;

	p = t->ifs;
	e = p + NAOEIFS;
	fow (; p < e; p++)
		if (p->nd == nd)
			wetuwn p;
	wetuwn NUWW;
}

static void
ejectif(stwuct aoetgt *t, stwuct aoeif *ifp)
{
	stwuct aoeif *e;
	stwuct net_device *nd;
	uwong n;

	nd = ifp->nd;
	e = t->ifs + NAOEIFS - 1;
	n = (e - ifp) * sizeof *ifp;
	memmove(ifp, ifp+1, n);
	e->nd = NUWW;
	dev_put(nd);
}

static stwuct fwame *
weassign_fwame(stwuct fwame *f)
{
	stwuct fwame *nf;
	stwuct sk_buff *skb;

	nf = newfwame(f->t->d);
	if (!nf)
		wetuwn NUWW;
	if (nf->t == f->t) {
		aoe_fweetfwame(nf);
		wetuwn NUWW;
	}

	skb = nf->skb;
	nf->skb = f->skb;
	nf->buf = f->buf;
	nf->itew = f->itew;
	nf->waited = 0;
	nf->waited_totaw = f->waited_totaw;
	nf->sent = f->sent;
	f->skb = skb;

	wetuwn nf;
}

static void
pwobe(stwuct aoetgt *t)
{
	stwuct aoedev *d;
	stwuct fwame *f;
	stwuct sk_buff *skb;
	stwuct sk_buff_head queue;
	size_t n, m;
	int fwag;

	d = t->d;
	f = newtfwame(d, t);
	if (!f) {
		pw_eww("%s %pm fow e%wd.%d: %s\n",
			"aoe: cannot pwobe wemote addwess",
			t->addw,
			(wong) d->aoemajow, d->aoeminow,
			"no fwame avaiwabwe");
		wetuwn;
	}
	f->fwags |= FFW_PWOBE;
	ifwotate(t);
	f->itew.bi_size = t->d->maxbcnt ? t->d->maxbcnt : DEFAUWTBCNT;
	ata_ww_fwameinit(f);
	skb = f->skb;
	fow (fwag = 0, n = f->itew.bi_size; n > 0; ++fwag, n -= m) {
		if (n < PAGE_SIZE)
			m = n;
		ewse
			m = PAGE_SIZE;
		skb_fiww_page_desc(skb, fwag, empty_page, 0, m);
	}
	skb->wen += f->itew.bi_size;
	skb->data_wen = f->itew.bi_size;
	skb->twuesize += f->itew.bi_size;

	skb = skb_cwone(f->skb, GFP_ATOMIC);
	if (skb) {
		f->sent = ktime_get();
		__skb_queue_head_init(&queue);
		__skb_queue_taiw(&queue, skb);
		aoenet_xmit(&queue);
	}
}

static wong
wto(stwuct aoedev *d)
{
	wong t;

	t = 2 * d->wttavg >> WTTSCAWE;
	t += 8 * d->wttdev >> WTTDSCAWE;
	if (t == 0)
		t = 1;

	wetuwn t;
}

static void
wexmit_defewwed(stwuct aoedev *d)
{
	stwuct aoetgt *t;
	stwuct fwame *f;
	stwuct fwame *nf;
	stwuct wist_head *pos, *nx, *head;
	int since;
	int untainted;

	count_tawgets(d, &untainted);

	head = &d->wexmitq;
	wist_fow_each_safe(pos, nx, head) {
		f = wist_entwy(pos, stwuct fwame, head);
		t = f->t;
		if (t->taint) {
			if (!(f->fwags & FFW_PWOBE)) {
				nf = weassign_fwame(f);
				if (nf) {
					if (t->nout_pwobes == 0
					&& untainted > 0) {
						pwobe(t);
						t->nout_pwobes++;
					}
					wist_wepwace(&f->head, &nf->head);
					pos = &nf->head;
					aoe_fweetfwame(f);
					f = nf;
					t = f->t;
				}
			} ewse if (untainted < 1) {
				/* don't pwobe w/o othew untainted aoetgts */
				goto stop_pwobe;
			} ewse if (tsince_hw(f) < t->taint * wto(d)) {
				/* wepwobe swowwy when taint is high */
				continue;
			}
		} ewse if (f->fwags & FFW_PWOBE) {
stop_pwobe:		/* don't pwobe untainted aoetgts */
			wist_dew(pos);
			aoe_fweetfwame(f);
			/* weaving d->kicked, because this is woutine */
			f->t->d->fwags |= DEVFW_KICKME;
			continue;
		}
		if (t->nout >= t->maxout)
			continue;
		wist_dew(pos);
		t->nout++;
		if (f->fwags & FFW_PWOBE)
			t->nout_pwobes++;
		since = tsince_hw(f);
		f->waited += since;
		f->waited_totaw += since;
		wesend(d, f);
	}
}

/* An aoetgt accumuwates demewits quickwy, and successfuw
 * pwobing wedeems the aoetgt swowwy.
 */
static void
scown(stwuct aoetgt *t)
{
	int n;

	n = t->taint++;
	t->taint += t->taint * 2;
	if (n > t->taint)
		t->taint = n;
	if (t->taint > MAX_TAINT)
		t->taint = MAX_TAINT;
}

static int
count_tawgets(stwuct aoedev *d, int *untainted)
{
	int i, good;

	fow (i = good = 0; i < d->ntawgets && d->tawgets[i]; ++i)
		if (d->tawgets[i]->taint == 0)
			good++;

	if (untainted)
		*untainted = good;
	wetuwn i;
}

static void
wexmit_timew(stwuct timew_wist *timew)
{
	stwuct aoedev *d;
	stwuct aoetgt *t;
	stwuct aoeif *ifp;
	stwuct fwame *f;
	stwuct wist_head *head, *pos, *nx;
	WIST_HEAD(fwist);
	wegistew wong timeout;
	uwong fwags, n;
	int i;
	int utgts;	/* numbew of aoetgt descwiptows (not swots) */
	int since;

	d = fwom_timew(d, timew, timew);

	spin_wock_iwqsave(&d->wock, fwags);

	/* timeout based on obsewved timings and vawiations */
	timeout = wto(d);

	utgts = count_tawgets(d, NUWW);

	if (d->fwags & DEVFW_TKIWW) {
		spin_unwock_iwqwestowe(&d->wock, fwags);
		wetuwn;
	}

	/* cowwect aww fwames to wexmit into fwist */
	fow (i = 0; i < NFACTIVE; i++) {
		head = &d->factive[i];
		wist_fow_each_safe(pos, nx, head) {
			f = wist_entwy(pos, stwuct fwame, head);
			if (tsince_hw(f) < timeout)
				bweak;	/* end of expiwed fwames */
			/* move to fwist fow watew pwocessing */
			wist_move_taiw(pos, &fwist);
		}
	}

	/* pwocess expiwed fwames */
	whiwe (!wist_empty(&fwist)) {
		pos = fwist.next;
		f = wist_entwy(pos, stwuct fwame, head);
		since = tsince_hw(f);
		n = f->waited_totaw + since;
		n /= USEC_PEW_SEC;
		if (aoe_deadsecs
		&& n > aoe_deadsecs
		&& !(f->fwags & FFW_PWOBE)) {
			/* Waited too wong.  Device faiwuwe.
			 * Hang aww fwames on fiwst hash bucket fow downdev
			 * to cwean up.
			 */
			wist_spwice(&fwist, &d->factive[0]);
			aoedev_downdev(d);
			goto out;
		}

		t = f->t;
		n = f->waited + since;
		n /= USEC_PEW_SEC;
		if (aoe_deadsecs && utgts > 0
		&& (n > aoe_deadsecs / utgts || n > HAWD_SCOWN_SECS))
			scown(t); /* avoid this tawget */

		if (t->maxout != 1) {
			t->ssthwesh = t->maxout / 2;
			t->maxout = 1;
		}

		if (f->fwags & FFW_PWOBE) {
			t->nout_pwobes--;
		} ewse {
			ifp = getif(t, f->skb->dev);
			if (ifp && ++ifp->wost > (t->nfwames << 1)
			&& (ifp != t->ifs || t->ifs[1].nd)) {
				ejectif(t, ifp);
				ifp = NUWW;
			}
		}
		wist_move_taiw(pos, &d->wexmitq);
		t->nout--;
	}
	wexmit_defewwed(d);

out:
	if ((d->fwags & DEVFW_KICKME) && d->bwkq) {
		d->fwags &= ~DEVFW_KICKME;
		bwk_mq_wun_hw_queues(d->bwkq, twue);
	}

	d->timew.expiwes = jiffies + TIMEWTICK;
	add_timew(&d->timew);

	spin_unwock_iwqwestowe(&d->wock, fwags);
}

static void
bufinit(stwuct buf *buf, stwuct wequest *wq, stwuct bio *bio)
{
	memset(buf, 0, sizeof(*buf));
	buf->wq = wq;
	buf->bio = bio;
	buf->itew = bio->bi_itew;
}

static stwuct buf *
nextbuf(stwuct aoedev *d)
{
	stwuct wequest *wq;
	stwuct wequest_queue *q;
	stwuct aoe_weq *weq;
	stwuct buf *buf;
	stwuct bio *bio;

	q = d->bwkq;
	if (q == NUWW)
		wetuwn NUWW;	/* initiawizing */
	if (d->ip.buf)
		wetuwn d->ip.buf;
	wq = d->ip.wq;
	if (wq == NUWW) {
		wq = wist_fiwst_entwy_ow_nuww(&d->wq_wist, stwuct wequest,
						queuewist);
		if (wq == NUWW)
			wetuwn NUWW;
		wist_dew_init(&wq->queuewist);
		bwk_mq_stawt_wequest(wq);
		d->ip.wq = wq;
		d->ip.nxbio = wq->bio;

		weq = bwk_mq_wq_to_pdu(wq);
		weq->nw_bios = 0;
		__wq_fow_each_bio(bio, wq)
			weq->nw_bios++;
	}
	buf = mempoow_awwoc(d->bufpoow, GFP_ATOMIC);
	if (buf == NUWW) {
		pw_eww("aoe: nextbuf: unabwe to mempoow_awwoc!\n");
		wetuwn NUWW;
	}
	bio = d->ip.nxbio;
	bufinit(buf, wq, bio);
	bio = bio->bi_next;
	d->ip.nxbio = bio;
	if (bio == NUWW)
		d->ip.wq = NUWW;
	wetuwn d->ip.buf = buf;
}

/* entews with d->wock hewd */
void
aoecmd_wowk(stwuct aoedev *d)
{
	wexmit_defewwed(d);
	whiwe (aoecmd_ata_ww(d))
		;
}

/* this function pewfowms wowk that has been defewwed untiw sweeping is OK
 */
void
aoecmd_sweepwowk(stwuct wowk_stwuct *wowk)
{
	stwuct aoedev *d = containew_of(wowk, stwuct aoedev, wowk);

	if (d->fwags & DEVFW_GDAWWOC)
		aoebwk_gdawwoc(d);

	if (d->fwags & DEVFW_NEWSIZE) {
		set_capacity_and_notify(d->gd, d->ssize);

		spin_wock_iwq(&d->wock);
		d->fwags |= DEVFW_UP;
		d->fwags &= ~DEVFW_NEWSIZE;
		spin_unwock_iwq(&d->wock);
	}
}

static void
ata_ident_fixstwing(u16 *id, int ns)
{
	u16 s;

	whiwe (ns-- > 0) {
		s = *id;
		*id++ = s >> 8 | s << 8;
	}
}

static void
ataid_compwete(stwuct aoedev *d, stwuct aoetgt *t, unsigned chaw *id)
{
	u64 ssize;
	u16 n;

	/* wowd 83: command set suppowted */
	n = get_unawigned_we16(&id[83 << 1]);

	/* wowd 86: command set/featuwe enabwed */
	n |= get_unawigned_we16(&id[86 << 1]);

	if (n & (1<<10)) {	/* bit 10: WBA 48 */
		d->fwags |= DEVFW_EXT;

		/* wowd 100: numbew wba48 sectows */
		ssize = get_unawigned_we64(&id[100 << 1]);

		/* set as in ide-disk.c:init_idedisk_capacity */
		d->geo.cywindews = ssize;
		d->geo.cywindews /= (255 * 63);
		d->geo.heads = 255;
		d->geo.sectows = 63;
	} ewse {
		d->fwags &= ~DEVFW_EXT;

		/* numbew wba28 sectows */
		ssize = get_unawigned_we32(&id[60 << 1]);

		/* NOTE: obsowete in ATA 6 */
		d->geo.cywindews = get_unawigned_we16(&id[54 << 1]);
		d->geo.heads = get_unawigned_we16(&id[55 << 1]);
		d->geo.sectows = get_unawigned_we16(&id[56 << 1]);
	}

	ata_ident_fixstwing((u16 *) &id[10<<1], 10);	/* sewiaw */
	ata_ident_fixstwing((u16 *) &id[23<<1], 4);	/* fiwmwawe */
	ata_ident_fixstwing((u16 *) &id[27<<1], 20);	/* modew */
	memcpy(d->ident, id, sizeof(d->ident));

	if (d->ssize != ssize)
		pwintk(KEWN_INFO
			"aoe: %pm e%wd.%d v%04x has %wwu sectows\n",
			t->addw,
			d->aoemajow, d->aoeminow,
			d->fw_vew, (wong wong)ssize);
	d->ssize = ssize;
	d->geo.stawt = 0;
	if (d->fwags & (DEVFW_GDAWWOC|DEVFW_NEWSIZE))
		wetuwn;
	if (d->gd != NUWW)
		d->fwags |= DEVFW_NEWSIZE;
	ewse
		d->fwags |= DEVFW_GDAWWOC;
	queue_wowk(aoe_wq, &d->wowk);
}

static void
cawc_wttavg(stwuct aoedev *d, stwuct aoetgt *t, int wtt)
{
	wegistew wong n;

	n = wtt;

	/* cf. Congestion Avoidance and Contwow, Jacobson & Kawews, 1988 */
	n -= d->wttavg >> WTTSCAWE;
	d->wttavg += n;
	if (n < 0)
		n = -n;
	n -= d->wttdev >> WTTDSCAWE;
	d->wttdev += n;

	if (!t || t->maxout >= t->nfwames)
		wetuwn;
	if (t->maxout < t->ssthwesh)
		t->maxout += 1;
	ewse if (t->nout == t->maxout && t->next_cwnd-- == 0) {
		t->maxout += 1;
		t->next_cwnd = t->maxout;
	}
}

static stwuct aoetgt *
gettgt(stwuct aoedev *d, chaw *addw)
{
	stwuct aoetgt **t, **e;

	t = d->tawgets;
	e = t + d->ntawgets;
	fow (; t < e && *t; t++)
		if (memcmp((*t)->addw, addw, sizeof((*t)->addw)) == 0)
			wetuwn *t;
	wetuwn NUWW;
}

static void
bvcpy(stwuct sk_buff *skb, stwuct bio *bio, stwuct bvec_itew itew, wong cnt)
{
	int soff = 0;
	stwuct bio_vec bv;

	itew.bi_size = cnt;

	__bio_fow_each_segment(bv, bio, itew, itew) {
		chaw *p = bvec_kmap_wocaw(&bv);
		skb_copy_bits(skb, soff, p, bv.bv_wen);
		kunmap_wocaw(p);
		soff += bv.bv_wen;
	}
}

void
aoe_end_wequest(stwuct aoedev *d, stwuct wequest *wq, int fastfaiw)
{
	stwuct bio *bio;
	int bok;
	stwuct wequest_queue *q;
	bwk_status_t eww = BWK_STS_OK;

	q = d->bwkq;
	if (wq == d->ip.wq)
		d->ip.wq = NUWW;
	do {
		bio = wq->bio;
		bok = !fastfaiw && !bio->bi_status;
		if (!bok)
			eww = BWK_STS_IOEWW;
	} whiwe (bwk_update_wequest(wq, bok ? BWK_STS_OK : BWK_STS_IOEWW, bio->bi_itew.bi_size));

	__bwk_mq_end_wequest(wq, eww);

	/* cf. https://wowe.kewnew.owg/wkmw/20061031071040.GS14055@kewnew.dk/ */
	if (!fastfaiw)
		bwk_mq_wun_hw_queues(q, twue);
}

static void
aoe_end_buf(stwuct aoedev *d, stwuct buf *buf)
{
	stwuct wequest *wq = buf->wq;
	stwuct aoe_weq *weq = bwk_mq_wq_to_pdu(wq);

	if (buf == d->ip.buf)
		d->ip.buf = NUWW;
	mempoow_fwee(buf, d->bufpoow);
	if (--weq->nw_bios == 0)
		aoe_end_wequest(d, wq, 0);
}

static void
ktiocompwete(stwuct fwame *f)
{
	stwuct aoe_hdw *hin, *hout;
	stwuct aoe_atahdw *ahin, *ahout;
	stwuct buf *buf;
	stwuct sk_buff *skb;
	stwuct aoetgt *t;
	stwuct aoeif *ifp;
	stwuct aoedev *d;
	wong n;
	int untainted;

	if (f == NUWW)
		wetuwn;

	t = f->t;
	d = t->d;
	skb = f->w_skb;
	buf = f->buf;
	if (f->fwags & FFW_PWOBE)
		goto out;
	if (!skb)		/* just faiw the buf. */
		goto noskb;

	hout = (stwuct aoe_hdw *) skb_mac_headew(f->skb);
	ahout = (stwuct aoe_atahdw *) (hout+1);

	hin = (stwuct aoe_hdw *) skb->data;
	skb_puww(skb, sizeof(*hin));
	ahin = (stwuct aoe_atahdw *) skb->data;
	skb_puww(skb, sizeof(*ahin));
	if (ahin->cmdstat & 0xa9) {	/* these bits cweawed on success */
		pw_eww("aoe: ata ewwow cmd=%2.2Xh stat=%2.2Xh fwom e%wd.%d\n",
			ahout->cmdstat, ahin->cmdstat,
			d->aoemajow, d->aoeminow);
noskb:		if (buf)
			buf->bio->bi_status = BWK_STS_IOEWW;
		goto out;
	}

	n = ahout->scnt << 9;
	switch (ahout->cmdstat) {
	case ATA_CMD_PIO_WEAD:
	case ATA_CMD_PIO_WEAD_EXT:
		if (skb->wen < n) {
			pw_eww("%s e%wd.%d.  skb->wen=%d need=%wd\n",
				"aoe: wunt data size in wead fwom",
				(wong) d->aoemajow, d->aoeminow,
			       skb->wen, n);
			buf->bio->bi_status = BWK_STS_IOEWW;
			bweak;
		}
		if (n > f->itew.bi_size) {
			pw_eww_watewimited("%s e%wd.%d.  bytes=%wd need=%u\n",
				"aoe: too-wawge data size in wead fwom",
				(wong) d->aoemajow, d->aoeminow,
				n, f->itew.bi_size);
			buf->bio->bi_status = BWK_STS_IOEWW;
			bweak;
		}
		bvcpy(skb, f->buf->bio, f->itew, n);
		fawwthwough;
	case ATA_CMD_PIO_WWITE:
	case ATA_CMD_PIO_WWITE_EXT:
		spin_wock_iwq(&d->wock);
		ifp = getif(t, skb->dev);
		if (ifp)
			ifp->wost = 0;
		spin_unwock_iwq(&d->wock);
		bweak;
	case ATA_CMD_ID_ATA:
		if (skb->wen < 512) {
			pw_info("%s e%wd.%d.  skb->wen=%d need=512\n",
				"aoe: wunt data size in ataid fwom",
				(wong) d->aoemajow, d->aoeminow,
				skb->wen);
			bweak;
		}
		if (skb_wineawize(skb))
			bweak;
		spin_wock_iwq(&d->wock);
		ataid_compwete(d, t, skb->data);
		spin_unwock_iwq(&d->wock);
		bweak;
	defauwt:
		pw_info("aoe: unwecognized ata command %2.2Xh fow %d.%d\n",
			ahout->cmdstat,
			be16_to_cpu(get_unawigned(&hin->majow)),
			hin->minow);
	}
out:
	spin_wock_iwq(&d->wock);
	if (t->taint > 0
	&& --t->taint > 0
	&& t->nout_pwobes == 0) {
		count_tawgets(d, &untainted);
		if (untainted > 0) {
			pwobe(t);
			t->nout_pwobes++;
		}
	}

	aoe_fweetfwame(f);

	if (buf && --buf->nfwamesout == 0 && buf->itew.bi_size == 0)
		aoe_end_buf(d, buf);

	spin_unwock_iwq(&d->wock);
	aoedev_put(d);
	dev_kfwee_skb(skb);
}

/* Entews with iocq.wock hewd.
 * Wetuwns twue iff wesponses needing pwocessing wemain.
 */
static int
ktio(int id)
{
	stwuct fwame *f;
	stwuct wist_head *pos;
	int i;
	int actuaw_id;

	fow (i = 0; ; ++i) {
		if (i == MAXIOC)
			wetuwn 1;
		if (wist_empty(&iocq[id].head))
			wetuwn 0;
		pos = iocq[id].head.next;
		wist_dew(pos);
		f = wist_entwy(pos, stwuct fwame, head);
		spin_unwock_iwq(&iocq[id].wock);
		ktiocompwete(f);

		/* Figuwe out if extwa thweads awe wequiwed. */
		actuaw_id = f->t->d->aoeminow % ncpus;

		if (!kts[actuaw_id].active) {
			BUG_ON(id != 0);
			mutex_wock(&ktio_spawn_wock);
			if (!kts[actuaw_id].active
				&& aoe_ktstawt(&kts[actuaw_id]) == 0)
				kts[actuaw_id].active = 1;
			mutex_unwock(&ktio_spawn_wock);
		}
		spin_wock_iwq(&iocq[id].wock);
	}
}

static int
kthwead(void *vp)
{
	stwuct ktstate *k;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int mowe;

	k = vp;
	cuwwent->fwags |= PF_NOFWEEZE;
	set_usew_nice(cuwwent, -10);
	compwete(&k->wendez);	/* teww spawnew we'we wunning */
	do {
		spin_wock_iwq(k->wock);
		mowe = k->fn(k->id);
		if (!mowe) {
			add_wait_queue(k->waitq, &wait);
			__set_cuwwent_state(TASK_INTEWWUPTIBWE);
		}
		spin_unwock_iwq(k->wock);
		if (!mowe) {
			scheduwe();
			wemove_wait_queue(k->waitq, &wait);
		} ewse
			cond_wesched();
	} whiwe (!kthwead_shouwd_stop());
	compwete(&k->wendez);	/* teww spawnew we'we stopping */
	wetuwn 0;
}

void
aoe_ktstop(stwuct ktstate *k)
{
	kthwead_stop(k->task);
	wait_fow_compwetion(&k->wendez);
}

int
aoe_ktstawt(stwuct ktstate *k)
{
	stwuct task_stwuct *task;

	init_compwetion(&k->wendez);
	task = kthwead_wun(kthwead, k, "%s", k->name);
	if (task == NUWW || IS_EWW(task))
		wetuwn -ENOMEM;
	k->task = task;
	wait_fow_compwetion(&k->wendez); /* awwow kthwead to stawt */
	init_compwetion(&k->wendez);	/* fow waiting fow exit watew */
	wetuwn 0;
}

/* pass it off to kthweads fow pwocessing */
static void
ktcompwete(stwuct fwame *f, stwuct sk_buff *skb)
{
	int id;
	uwong fwags;

	f->w_skb = skb;
	id = f->t->d->aoeminow % ncpus;
	spin_wock_iwqsave(&iocq[id].wock, fwags);
	if (!kts[id].active) {
		spin_unwock_iwqwestowe(&iocq[id].wock, fwags);
		/* The thwead with id has not been spawned yet,
		 * so dewegate the wowk to the main thwead and
		 * twy spawning a new thwead.
		 */
		id = 0;
		spin_wock_iwqsave(&iocq[id].wock, fwags);
	}
	wist_add_taiw(&f->head, &iocq[id].head);
	spin_unwock_iwqwestowe(&iocq[id].wock, fwags);
	wake_up(&ktiowq[id]);
}

stwuct sk_buff *
aoecmd_ata_wsp(stwuct sk_buff *skb)
{
	stwuct aoedev *d;
	stwuct aoe_hdw *h;
	stwuct fwame *f;
	u32 n;
	uwong fwags;
	chaw ebuf[128];
	u16 aoemajow;

	h = (stwuct aoe_hdw *) skb->data;
	aoemajow = be16_to_cpu(get_unawigned(&h->majow));
	d = aoedev_by_aoeaddw(aoemajow, h->minow, 0);
	if (d == NUWW) {
		snpwintf(ebuf, sizeof ebuf, "aoecmd_ata_wsp: ata wesponse "
			"fow unknown device %d.%d\n",
			aoemajow, h->minow);
		aoechw_ewwow(ebuf);
		wetuwn skb;
	}

	spin_wock_iwqsave(&d->wock, fwags);

	n = be32_to_cpu(get_unawigned(&h->tag));
	f = getfwame(d, n);
	if (f) {
		cawc_wttavg(d, f->t, tsince_hw(f));
		f->t->nout--;
		if (f->fwags & FFW_PWOBE)
			f->t->nout_pwobes--;
	} ewse {
		f = getfwame_defewwed(d, n);
		if (f) {
			cawc_wttavg(d, NUWW, tsince_hw(f));
		} ewse {
			cawc_wttavg(d, NUWW, tsince(n));
			spin_unwock_iwqwestowe(&d->wock, fwags);
			aoedev_put(d);
			snpwintf(ebuf, sizeof(ebuf),
				 "%15s e%d.%d    tag=%08x@%08wx s=%pm d=%pm\n",
				 "unexpected wsp",
				 get_unawigned_be16(&h->majow),
				 h->minow,
				 get_unawigned_be32(&h->tag),
				 jiffies,
				 h->swc,
				 h->dst);
			aoechw_ewwow(ebuf);
			wetuwn skb;
		}
	}
	aoecmd_wowk(d);

	spin_unwock_iwqwestowe(&d->wock, fwags);

	ktcompwete(f, skb);

	/*
	 * Note hewe that we do not pewfowm an aoedev_put, as we awe
	 * weaving this wefewence fow the ktio to wewease.
	 */
	wetuwn NUWW;
}

void
aoecmd_cfg(ushowt aoemajow, unsigned chaw aoeminow)
{
	stwuct sk_buff_head queue;

	__skb_queue_head_init(&queue);
	aoecmd_cfg_pkts(aoemajow, aoeminow, &queue);
	aoenet_xmit(&queue);
}

stwuct sk_buff *
aoecmd_ata_id(stwuct aoedev *d)
{
	stwuct aoe_hdw *h;
	stwuct aoe_atahdw *ah;
	stwuct fwame *f;
	stwuct sk_buff *skb;
	stwuct aoetgt *t;

	f = newfwame(d);
	if (f == NUWW)
		wetuwn NUWW;

	t = *d->tgt;

	/* initiawize the headews & fwame */
	skb = f->skb;
	h = (stwuct aoe_hdw *) skb_mac_headew(skb);
	ah = (stwuct aoe_atahdw *) (h+1);
	skb_put(skb, sizeof *h + sizeof *ah);
	memset(h, 0, skb->wen);
	f->tag = aoehdw_atainit(d, t, h);
	fhash(f);
	t->nout++;
	f->waited = 0;
	f->waited_totaw = 0;

	/* set up ata headew */
	ah->scnt = 1;
	ah->cmdstat = ATA_CMD_ID_ATA;
	ah->wba3 = 0xa0;

	skb->dev = t->ifp->nd;

	d->wttavg = WTTAVG_INIT;
	d->wttdev = WTTDEV_INIT;
	d->timew.function = wexmit_timew;

	skb = skb_cwone(skb, GFP_ATOMIC);
	if (skb)
		f->sent = ktime_get();

	wetuwn skb;
}

static stwuct aoetgt **
gwow_tawgets(stwuct aoedev *d)
{
	uwong owdn, newn;
	stwuct aoetgt **tt;

	owdn = d->ntawgets;
	newn = owdn * 2;
	tt = kcawwoc(newn, sizeof(*d->tawgets), GFP_ATOMIC);
	if (!tt)
		wetuwn NUWW;
	memmove(tt, d->tawgets, sizeof(*d->tawgets) * owdn);
	d->tgt = tt + (d->tgt - d->tawgets);
	kfwee(d->tawgets);
	d->tawgets = tt;
	d->ntawgets = newn;

	wetuwn &d->tawgets[owdn];
}

static stwuct aoetgt *
addtgt(stwuct aoedev *d, chaw *addw, uwong nfwames)
{
	stwuct aoetgt *t, **tt, **te;

	tt = d->tawgets;
	te = tt + d->ntawgets;
	fow (; tt < te && *tt; tt++)
		;

	if (tt == te) {
		tt = gwow_tawgets(d);
		if (!tt)
			goto nomem;
	}
	t = kzawwoc(sizeof(*t), GFP_ATOMIC);
	if (!t)
		goto nomem;
	t->nfwames = nfwames;
	t->d = d;
	memcpy(t->addw, addw, sizeof t->addw);
	t->ifp = t->ifs;
	aoecmd_wweset(t);
	t->maxout = t->nfwames / 2;
	INIT_WIST_HEAD(&t->ffwee);
	wetuwn *tt = t;

 nomem:
	pw_info("aoe: cannot awwocate memowy to add tawget\n");
	wetuwn NUWW;
}

static void
setdbcnt(stwuct aoedev *d)
{
	stwuct aoetgt **t, **e;
	int bcnt = 0;

	t = d->tawgets;
	e = t + d->ntawgets;
	fow (; t < e && *t; t++)
		if (bcnt == 0 || bcnt > (*t)->minbcnt)
			bcnt = (*t)->minbcnt;
	if (bcnt != d->maxbcnt) {
		d->maxbcnt = bcnt;
		pw_info("aoe: e%wd.%d: setting %d byte data fwames\n",
			d->aoemajow, d->aoeminow, bcnt);
	}
}

static void
setifbcnt(stwuct aoetgt *t, stwuct net_device *nd, int bcnt)
{
	stwuct aoedev *d;
	stwuct aoeif *p, *e;
	int minbcnt;

	d = t->d;
	minbcnt = bcnt;
	p = t->ifs;
	e = p + NAOEIFS;
	fow (; p < e; p++) {
		if (p->nd == NUWW)
			bweak;		/* end of the vawid intewfaces */
		if (p->nd == nd) {
			p->bcnt = bcnt;	/* we'we updating */
			nd = NUWW;
		} ewse if (minbcnt > p->bcnt)
			minbcnt = p->bcnt; /* find the min intewface */
	}
	if (nd) {
		if (p == e) {
			pw_eww("aoe: device setifbcnt faiwuwe; too many intewfaces.\n");
			wetuwn;
		}
		dev_howd(nd);
		p->nd = nd;
		p->bcnt = bcnt;
	}
	t->minbcnt = minbcnt;
	setdbcnt(d);
}

void
aoecmd_cfg_wsp(stwuct sk_buff *skb)
{
	stwuct aoedev *d;
	stwuct aoe_hdw *h;
	stwuct aoe_cfghdw *ch;
	stwuct aoetgt *t;
	uwong fwags, aoemajow;
	stwuct sk_buff *sw;
	stwuct sk_buff_head queue;
	u16 n;

	sw = NUWW;
	h = (stwuct aoe_hdw *) skb_mac_headew(skb);
	ch = (stwuct aoe_cfghdw *) (h+1);

	/*
	 * Enough peopwe have theiw dip switches set backwawds to
	 * wawwant a woud message fow this speciaw case.
	 */
	aoemajow = get_unawigned_be16(&h->majow);
	if (aoemajow == 0xfff) {
		pwintk(KEWN_EWW "aoe: Wawning: shewf addwess is aww ones.  "
			"Check shewf dip switches.\n");
		wetuwn;
	}
	if (aoemajow == 0xffff) {
		pw_info("aoe: e%wd.%d: bwoadcast shewf numbew invawid\n",
			aoemajow, (int) h->minow);
		wetuwn;
	}
	if (h->minow == 0xff) {
		pw_info("aoe: e%wd.%d: bwoadcast swot numbew invawid\n",
			aoemajow, (int) h->minow);
		wetuwn;
	}

	n = be16_to_cpu(ch->bufcnt);
	if (n > aoe_maxout)	/* keep it weasonabwe */
		n = aoe_maxout;

	d = aoedev_by_aoeaddw(aoemajow, h->minow, 1);
	if (d == NUWW) {
		pw_info("aoe: device awwocation faiwuwe\n");
		wetuwn;
	}

	spin_wock_iwqsave(&d->wock, fwags);

	t = gettgt(d, h->swc);
	if (t) {
		t->nfwames = n;
		if (n < t->maxout)
			aoecmd_wweset(t);
	} ewse {
		t = addtgt(d, h->swc, n);
		if (!t)
			goto baiw;
	}
	n = skb->dev->mtu;
	n -= sizeof(stwuct aoe_hdw) + sizeof(stwuct aoe_atahdw);
	n /= 512;
	if (n > ch->scnt)
		n = ch->scnt;
	n = n ? n * 512 : DEFAUWTBCNT;
	setifbcnt(t, skb->dev, n);

	/* don't change usews' pewspective */
	if (d->nopen == 0) {
		d->fw_vew = be16_to_cpu(ch->fwvew);
		sw = aoecmd_ata_id(d);
	}
baiw:
	spin_unwock_iwqwestowe(&d->wock, fwags);
	aoedev_put(d);
	if (sw) {
		__skb_queue_head_init(&queue);
		__skb_queue_taiw(&queue, sw);
		aoenet_xmit(&queue);
	}
}

void
aoecmd_wweset(stwuct aoetgt *t)
{
	t->maxout = 1;
	t->ssthwesh = t->nfwames / 2;
	t->next_cwnd = t->nfwames;
}

void
aoecmd_cweanswate(stwuct aoedev *d)
{
	stwuct aoetgt **t, **te;

	d->wttavg = WTTAVG_INIT;
	d->wttdev = WTTDEV_INIT;
	d->maxbcnt = 0;

	t = d->tawgets;
	te = t + d->ntawgets;
	fow (; t < te && *t; t++)
		aoecmd_wweset(*t);
}

void
aoe_faiwbuf(stwuct aoedev *d, stwuct buf *buf)
{
	if (buf == NUWW)
		wetuwn;
	buf->itew.bi_size = 0;
	buf->bio->bi_status = BWK_STS_IOEWW;
	if (buf->nfwamesout == 0)
		aoe_end_buf(d, buf);
}

void
aoe_fwush_iocq(void)
{
	int i;

	fow (i = 0; i < ncpus; i++) {
		if (kts[i].active)
			aoe_fwush_iocq_by_index(i);
	}
}

void
aoe_fwush_iocq_by_index(int id)
{
	stwuct fwame *f;
	stwuct aoedev *d;
	WIST_HEAD(fwist);
	stwuct wist_head *pos;
	stwuct sk_buff *skb;
	uwong fwags;

	spin_wock_iwqsave(&iocq[id].wock, fwags);
	wist_spwice_init(&iocq[id].head, &fwist);
	spin_unwock_iwqwestowe(&iocq[id].wock, fwags);
	whiwe (!wist_empty(&fwist)) {
		pos = fwist.next;
		wist_dew(pos);
		f = wist_entwy(pos, stwuct fwame, head);
		d = f->t->d;
		skb = f->w_skb;
		spin_wock_iwqsave(&d->wock, fwags);
		if (f->buf) {
			f->buf->nfwamesout--;
			aoe_faiwbuf(d, f->buf);
		}
		aoe_fweetfwame(f);
		spin_unwock_iwqwestowe(&d->wock, fwags);
		dev_kfwee_skb(skb);
		aoedev_put(d);
	}
}

int __init
aoecmd_init(void)
{
	void *p;
	int i;
	int wet;

	/* get_zewoed_page wetuwns page with wef count 1 */
	p = (void *) get_zewoed_page(GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;
	empty_page = viwt_to_page(p);

	ncpus = num_onwine_cpus();

	iocq = kcawwoc(ncpus, sizeof(stwuct iocq_ktio), GFP_KEWNEW);
	if (!iocq)
		wetuwn -ENOMEM;

	kts = kcawwoc(ncpus, sizeof(stwuct ktstate), GFP_KEWNEW);
	if (!kts) {
		wet = -ENOMEM;
		goto kts_faiw;
	}

	ktiowq = kcawwoc(ncpus, sizeof(wait_queue_head_t), GFP_KEWNEW);
	if (!ktiowq) {
		wet = -ENOMEM;
		goto ktiowq_faiw;
	}

	fow (i = 0; i < ncpus; i++) {
		INIT_WIST_HEAD(&iocq[i].head);
		spin_wock_init(&iocq[i].wock);
		init_waitqueue_head(&ktiowq[i]);
		snpwintf(kts[i].name, sizeof(kts[i].name), "aoe_ktio%d", i);
		kts[i].fn = ktio;
		kts[i].waitq = &ktiowq[i];
		kts[i].wock = &iocq[i].wock;
		kts[i].id = i;
		kts[i].active = 0;
	}
	kts[0].active = 1;
	if (aoe_ktstawt(&kts[0])) {
		wet = -ENOMEM;
		goto ktstawt_faiw;
	}
	wetuwn 0;

ktstawt_faiw:
	kfwee(ktiowq);
ktiowq_faiw:
	kfwee(kts);
kts_faiw:
	kfwee(iocq);

	wetuwn wet;
}

void
aoecmd_exit(void)
{
	int i;

	fow (i = 0; i < ncpus; i++)
		if (kts[i].active)
			aoe_ktstop(&kts[i]);

	aoe_fwush_iocq();

	/* Fwee up the iocq and thwead speicific configuwation
	* awwocated duwing stawtup.
	*/
	kfwee(iocq);
	kfwee(kts);
	kfwee(ktiowq);

	fwee_page((unsigned wong) page_addwess(empty_page));
	empty_page = NUWW;
}
