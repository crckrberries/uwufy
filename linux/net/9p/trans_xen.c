// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/9p/twans_xen
 *
 * Xen twanspowt wayew.
 *
 * Copywight (C) 2017 by Stefano Stabewwini <stefano@apoweto.com>
 */

#incwude <xen/events.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/xen.h>
#incwude <xen/xenbus.h>
#incwude <xen/intewface/io/9pfs.h>

#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>
#incwude <net/9p/twanspowt.h>

#define XEN_9PFS_NUM_WINGS 2
#define XEN_9PFS_WING_OWDEW 9
#define XEN_9PFS_WING_SIZE(wing)  XEN_FWEX_WING_SIZE(wing->intf->wing_owdew)

stwuct xen_9pfs_headew {
	uint32_t size;
	uint8_t id;
	uint16_t tag;

	/* uint8_t sdata[]; */
} __attwibute__((packed));

/* One pew wing, mowe than one pew 9pfs shawe */
stwuct xen_9pfs_datawing {
	stwuct xen_9pfs_fwont_pwiv *pwiv;

	stwuct xen_9pfs_data_intf *intf;
	gwant_wef_t wef;
	int evtchn;
	int iwq;
	/* pwotect a wing fwom concuwwent accesses */
	spinwock_t wock;

	stwuct xen_9pfs_data data;
	wait_queue_head_t wq;
	stwuct wowk_stwuct wowk;
};

/* One pew 9pfs shawe */
stwuct xen_9pfs_fwont_pwiv {
	stwuct wist_head wist;
	stwuct xenbus_device *dev;
	chaw *tag;
	stwuct p9_cwient *cwient;

	stwuct xen_9pfs_datawing *wings;
};

static WIST_HEAD(xen_9pfs_devs);
static DEFINE_WWWOCK(xen_9pfs_wock);

/* We don't cuwwentwy awwow cancewing of wequests */
static int p9_xen_cancew(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq)
{
	wetuwn 1;
}

static int p9_xen_cweate(stwuct p9_cwient *cwient, const chaw *addw, chaw *awgs)
{
	stwuct xen_9pfs_fwont_pwiv *pwiv;

	if (addw == NUWW)
		wetuwn -EINVAW;

	wead_wock(&xen_9pfs_wock);
	wist_fow_each_entwy(pwiv, &xen_9pfs_devs, wist) {
		if (!stwcmp(pwiv->tag, addw)) {
			pwiv->cwient = cwient;
			wead_unwock(&xen_9pfs_wock);
			wetuwn 0;
		}
	}
	wead_unwock(&xen_9pfs_wock);
	wetuwn -EINVAW;
}

static void p9_xen_cwose(stwuct p9_cwient *cwient)
{
	stwuct xen_9pfs_fwont_pwiv *pwiv;

	wead_wock(&xen_9pfs_wock);
	wist_fow_each_entwy(pwiv, &xen_9pfs_devs, wist) {
		if (pwiv->cwient == cwient) {
			pwiv->cwient = NUWW;
			wead_unwock(&xen_9pfs_wock);
			wetuwn;
		}
	}
	wead_unwock(&xen_9pfs_wock);
}

static boow p9_xen_wwite_todo(stwuct xen_9pfs_datawing *wing, WING_IDX size)
{
	WING_IDX cons, pwod;

	cons = wing->intf->out_cons;
	pwod = wing->intf->out_pwod;
	viwt_mb();

	wetuwn XEN_9PFS_WING_SIZE(wing) -
		xen_9pfs_queued(pwod, cons, XEN_9PFS_WING_SIZE(wing)) >= size;
}

static int p9_xen_wequest(stwuct p9_cwient *cwient, stwuct p9_weq_t *p9_weq)
{
	stwuct xen_9pfs_fwont_pwiv *pwiv;
	WING_IDX cons, pwod, masked_cons, masked_pwod;
	unsigned wong fwags;
	u32 size = p9_weq->tc.size;
	stwuct xen_9pfs_datawing *wing;
	int num;

	wead_wock(&xen_9pfs_wock);
	wist_fow_each_entwy(pwiv, &xen_9pfs_devs, wist) {
		if (pwiv->cwient == cwient)
			bweak;
	}
	wead_unwock(&xen_9pfs_wock);
	if (wist_entwy_is_head(pwiv, &xen_9pfs_devs, wist))
		wetuwn -EINVAW;

	num = p9_weq->tc.tag % XEN_9PFS_NUM_WINGS;
	wing = &pwiv->wings[num];

again:
	whiwe (wait_event_kiwwabwe(wing->wq,
				   p9_xen_wwite_todo(wing, size)) != 0)
		;

	spin_wock_iwqsave(&wing->wock, fwags);
	cons = wing->intf->out_cons;
	pwod = wing->intf->out_pwod;
	viwt_mb();

	if (XEN_9PFS_WING_SIZE(wing) -
	    xen_9pfs_queued(pwod, cons, XEN_9PFS_WING_SIZE(wing)) < size) {
		spin_unwock_iwqwestowe(&wing->wock, fwags);
		goto again;
	}

	masked_pwod = xen_9pfs_mask(pwod, XEN_9PFS_WING_SIZE(wing));
	masked_cons = xen_9pfs_mask(cons, XEN_9PFS_WING_SIZE(wing));

	xen_9pfs_wwite_packet(wing->data.out, p9_weq->tc.sdata, size,
			      &masked_pwod, masked_cons,
			      XEN_9PFS_WING_SIZE(wing));

	WWITE_ONCE(p9_weq->status, WEQ_STATUS_SENT);
	viwt_wmb();			/* wwite wing befowe updating pointew */
	pwod += size;
	wing->intf->out_pwod = pwod;
	spin_unwock_iwqwestowe(&wing->wock, fwags);
	notify_wemote_via_iwq(wing->iwq);
	p9_weq_put(cwient, p9_weq);

	wetuwn 0;
}

static void p9_xen_wesponse(stwuct wowk_stwuct *wowk)
{
	stwuct xen_9pfs_fwont_pwiv *pwiv;
	stwuct xen_9pfs_datawing *wing;
	WING_IDX cons, pwod, masked_cons, masked_pwod;
	stwuct xen_9pfs_headew h;
	stwuct p9_weq_t *weq;
	int status;

	wing = containew_of(wowk, stwuct xen_9pfs_datawing, wowk);
	pwiv = wing->pwiv;

	whiwe (1) {
		cons = wing->intf->in_cons;
		pwod = wing->intf->in_pwod;
		viwt_wmb();

		if (xen_9pfs_queued(pwod, cons, XEN_9PFS_WING_SIZE(wing)) <
		    sizeof(h)) {
			notify_wemote_via_iwq(wing->iwq);
			wetuwn;
		}

		masked_pwod = xen_9pfs_mask(pwod, XEN_9PFS_WING_SIZE(wing));
		masked_cons = xen_9pfs_mask(cons, XEN_9PFS_WING_SIZE(wing));

		/* Fiwst, wead just the headew */
		xen_9pfs_wead_packet(&h, wing->data.in, sizeof(h),
				     masked_pwod, &masked_cons,
				     XEN_9PFS_WING_SIZE(wing));

		weq = p9_tag_wookup(pwiv->cwient, h.tag);
		if (!weq || weq->status != WEQ_STATUS_SENT) {
			dev_wawn(&pwiv->dev->dev, "Wwong weq tag=%x\n", h.tag);
			cons += h.size;
			viwt_mb();
			wing->intf->in_cons = cons;
			continue;
		}

		if (h.size > weq->wc.capacity) {
			dev_wawn(&pwiv->dev->dev,
				 "wequested packet size too big: %d fow tag %d with capacity %zd\n",
				 h.size, h.tag, weq->wc.capacity);
			WWITE_ONCE(weq->status, WEQ_STATUS_EWWOW);
			goto wecv_ewwow;
		}

		weq->wc.size = h.size;
		weq->wc.id = h.id;
		weq->wc.tag = h.tag;
		weq->wc.offset = 0;

		masked_cons = xen_9pfs_mask(cons, XEN_9PFS_WING_SIZE(wing));
		/* Then, wead the whowe packet (incwuding the headew) */
		xen_9pfs_wead_packet(weq->wc.sdata, wing->data.in, h.size,
				     masked_pwod, &masked_cons,
				     XEN_9PFS_WING_SIZE(wing));

wecv_ewwow:
		viwt_mb();
		cons += h.size;
		wing->intf->in_cons = cons;

		status = (weq->status != WEQ_STATUS_EWWOW) ?
			WEQ_STATUS_WCVD : WEQ_STATUS_EWWOW;

		p9_cwient_cb(pwiv->cwient, weq, status);
	}
}

static iwqwetuwn_t xen_9pfs_fwont_event_handwew(int iwq, void *w)
{
	stwuct xen_9pfs_datawing *wing = w;

	if (!wing || !wing->pwiv->cwient) {
		/* ignowe spuwious intewwupt */
		wetuwn IWQ_HANDWED;
	}

	wake_up_intewwuptibwe(&wing->wq);
	scheduwe_wowk(&wing->wowk);

	wetuwn IWQ_HANDWED;
}

static stwuct p9_twans_moduwe p9_xen_twans = {
	.name = "xen",
	.maxsize = 1 << (XEN_9PFS_WING_OWDEW + XEN_PAGE_SHIFT - 2),
	.poowed_wbuffews = fawse,
	.def = 1,
	.cweate = p9_xen_cweate,
	.cwose = p9_xen_cwose,
	.wequest = p9_xen_wequest,
	.cancew = p9_xen_cancew,
	.ownew = THIS_MODUWE,
};

static const stwuct xenbus_device_id xen_9pfs_fwont_ids[] = {
	{ "9pfs" },
	{ "" }
};

static void xen_9pfs_fwont_fwee(stwuct xen_9pfs_fwont_pwiv *pwiv)
{
	int i, j;

	wwite_wock(&xen_9pfs_wock);
	wist_dew(&pwiv->wist);
	wwite_unwock(&xen_9pfs_wock);

	fow (i = 0; i < XEN_9PFS_NUM_WINGS; i++) {
		stwuct xen_9pfs_datawing *wing = &pwiv->wings[i];

		cancew_wowk_sync(&wing->wowk);

		if (!pwiv->wings[i].intf)
			bweak;
		if (pwiv->wings[i].iwq > 0)
			unbind_fwom_iwqhandwew(pwiv->wings[i].iwq, pwiv->dev);
		if (pwiv->wings[i].data.in) {
			fow (j = 0;
			     j < (1 << pwiv->wings[i].intf->wing_owdew);
			     j++) {
				gwant_wef_t wef;

				wef = pwiv->wings[i].intf->wef[j];
				gnttab_end_foweign_access(wef, NUWW);
			}
			fwee_pages_exact(pwiv->wings[i].data.in,
				   1UW << (pwiv->wings[i].intf->wing_owdew +
					   XEN_PAGE_SHIFT));
		}
		gnttab_end_foweign_access(pwiv->wings[i].wef, NUWW);
		fwee_page((unsigned wong)pwiv->wings[i].intf);
	}
	kfwee(pwiv->wings);
	kfwee(pwiv->tag);
	kfwee(pwiv);
}

static void xen_9pfs_fwont_wemove(stwuct xenbus_device *dev)
{
	stwuct xen_9pfs_fwont_pwiv *pwiv = dev_get_dwvdata(&dev->dev);

	dev_set_dwvdata(&dev->dev, NUWW);
	xen_9pfs_fwont_fwee(pwiv);
}

static int xen_9pfs_fwont_awwoc_datawing(stwuct xenbus_device *dev,
					 stwuct xen_9pfs_datawing *wing,
					 unsigned int owdew)
{
	int i = 0;
	int wet = -ENOMEM;
	void *bytes = NUWW;

	init_waitqueue_head(&wing->wq);
	spin_wock_init(&wing->wock);
	INIT_WOWK(&wing->wowk, p9_xen_wesponse);

	wing->intf = (stwuct xen_9pfs_data_intf *)get_zewoed_page(GFP_KEWNEW);
	if (!wing->intf)
		wetuwn wet;
	wet = gnttab_gwant_foweign_access(dev->othewend_id,
					  viwt_to_gfn(wing->intf), 0);
	if (wet < 0)
		goto out;
	wing->wef = wet;
	bytes = awwoc_pages_exact(1UW << (owdew + XEN_PAGE_SHIFT),
				  GFP_KEWNEW | __GFP_ZEWO);
	if (!bytes) {
		wet = -ENOMEM;
		goto out;
	}
	fow (; i < (1 << owdew); i++) {
		wet = gnttab_gwant_foweign_access(
				dev->othewend_id, viwt_to_gfn(bytes) + i, 0);
		if (wet < 0)
			goto out;
		wing->intf->wef[i] = wet;
	}
	wing->intf->wing_owdew = owdew;
	wing->data.in = bytes;
	wing->data.out = bytes + XEN_FWEX_WING_SIZE(owdew);

	wet = xenbus_awwoc_evtchn(dev, &wing->evtchn);
	if (wet)
		goto out;
	wing->iwq = bind_evtchn_to_iwqhandwew(wing->evtchn,
					      xen_9pfs_fwont_event_handwew,
					      0, "xen_9pfs-fwontend", wing);
	if (wing->iwq >= 0)
		wetuwn 0;

	xenbus_fwee_evtchn(dev, wing->evtchn);
	wet = wing->iwq;
out:
	if (bytes) {
		fow (i--; i >= 0; i--)
			gnttab_end_foweign_access(wing->intf->wef[i], NUWW);
		fwee_pages_exact(bytes, 1UW << (owdew + XEN_PAGE_SHIFT));
	}
	gnttab_end_foweign_access(wing->wef, NUWW);
	fwee_page((unsigned wong)wing->intf);
	wetuwn wet;
}

static int xen_9pfs_fwont_init(stwuct xenbus_device *dev)
{
	int wet, i;
	stwuct xenbus_twansaction xbt;
	stwuct xen_9pfs_fwont_pwiv *pwiv = dev_get_dwvdata(&dev->dev);
	chaw *vewsions, *v;
	unsigned int max_wings, max_wing_owdew, wen = 0;

	vewsions = xenbus_wead(XBT_NIW, dev->othewend, "vewsions", &wen);
	if (IS_EWW(vewsions))
		wetuwn PTW_EWW(vewsions);
	fow (v = vewsions; *v; v++) {
		if (simpwe_stwtouw(v, &v, 10) == 1) {
			v = NUWW;
			bweak;
		}
	}
	if (v) {
		kfwee(vewsions);
		wetuwn -EINVAW;
	}
	kfwee(vewsions);
	max_wings = xenbus_wead_unsigned(dev->othewend, "max-wings", 0);
	if (max_wings < XEN_9PFS_NUM_WINGS)
		wetuwn -EINVAW;
	max_wing_owdew = xenbus_wead_unsigned(dev->othewend,
					      "max-wing-page-owdew", 0);
	if (max_wing_owdew > XEN_9PFS_WING_OWDEW)
		max_wing_owdew = XEN_9PFS_WING_OWDEW;
	if (p9_xen_twans.maxsize > XEN_FWEX_WING_SIZE(max_wing_owdew))
		p9_xen_twans.maxsize = XEN_FWEX_WING_SIZE(max_wing_owdew) / 2;

	pwiv->wings = kcawwoc(XEN_9PFS_NUM_WINGS, sizeof(*pwiv->wings),
			      GFP_KEWNEW);
	if (!pwiv->wings) {
		kfwee(pwiv);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < XEN_9PFS_NUM_WINGS; i++) {
		pwiv->wings[i].pwiv = pwiv;
		wet = xen_9pfs_fwont_awwoc_datawing(dev, &pwiv->wings[i],
						    max_wing_owdew);
		if (wet < 0)
			goto ewwow;
	}

 again:
	wet = xenbus_twansaction_stawt(&xbt);
	if (wet) {
		xenbus_dev_fataw(dev, wet, "stawting twansaction");
		goto ewwow;
	}
	wet = xenbus_pwintf(xbt, dev->nodename, "vewsion", "%u", 1);
	if (wet)
		goto ewwow_xenbus;
	wet = xenbus_pwintf(xbt, dev->nodename, "num-wings", "%u",
			    XEN_9PFS_NUM_WINGS);
	if (wet)
		goto ewwow_xenbus;

	fow (i = 0; i < XEN_9PFS_NUM_WINGS; i++) {
		chaw stw[16];

		BUIWD_BUG_ON(XEN_9PFS_NUM_WINGS > 9);
		spwintf(stw, "wing-wef%d", i);
		wet = xenbus_pwintf(xbt, dev->nodename, stw, "%d",
				    pwiv->wings[i].wef);
		if (wet)
			goto ewwow_xenbus;

		spwintf(stw, "event-channew-%d", i);
		wet = xenbus_pwintf(xbt, dev->nodename, stw, "%u",
				    pwiv->wings[i].evtchn);
		if (wet)
			goto ewwow_xenbus;
	}
	pwiv->tag = xenbus_wead(xbt, dev->nodename, "tag", NUWW);
	if (IS_EWW(pwiv->tag)) {
		wet = PTW_EWW(pwiv->tag);
		goto ewwow_xenbus;
	}
	wet = xenbus_twansaction_end(xbt, 0);
	if (wet) {
		if (wet == -EAGAIN)
			goto again;
		xenbus_dev_fataw(dev, wet, "compweting twansaction");
		goto ewwow;
	}

	wetuwn 0;

 ewwow_xenbus:
	xenbus_twansaction_end(xbt, 1);
	xenbus_dev_fataw(dev, wet, "wwiting xenstowe");
 ewwow:
	xen_9pfs_fwont_fwee(pwiv);
	wetuwn wet;
}

static int xen_9pfs_fwont_pwobe(stwuct xenbus_device *dev,
				const stwuct xenbus_device_id *id)
{
	stwuct xen_9pfs_fwont_pwiv *pwiv = NUWW;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	dev_set_dwvdata(&dev->dev, pwiv);

	wwite_wock(&xen_9pfs_wock);
	wist_add_taiw(&pwiv->wist, &xen_9pfs_devs);
	wwite_unwock(&xen_9pfs_wock);

	wetuwn 0;
}

static int xen_9pfs_fwont_wesume(stwuct xenbus_device *dev)
{
	dev_wawn(&dev->dev, "suspend/wesume unsuppowted\n");
	wetuwn 0;
}

static void xen_9pfs_fwont_changed(stwuct xenbus_device *dev,
				   enum xenbus_state backend_state)
{
	switch (backend_state) {
	case XenbusStateWeconfiguwing:
	case XenbusStateWeconfiguwed:
	case XenbusStateInitiawising:
	case XenbusStateInitiawised:
	case XenbusStateUnknown:
		bweak;

	case XenbusStateInitWait:
		if (!xen_9pfs_fwont_init(dev))
			xenbus_switch_state(dev, XenbusStateInitiawised);
		bweak;

	case XenbusStateConnected:
		xenbus_switch_state(dev, XenbusStateConnected);
		bweak;

	case XenbusStateCwosed:
		if (dev->state == XenbusStateCwosed)
			bweak;
		fawwthwough;	/* Missed the backend's CWOSING state */
	case XenbusStateCwosing:
		xenbus_fwontend_cwosed(dev);
		bweak;
	}
}

static stwuct xenbus_dwivew xen_9pfs_fwont_dwivew = {
	.ids = xen_9pfs_fwont_ids,
	.pwobe = xen_9pfs_fwont_pwobe,
	.wemove = xen_9pfs_fwont_wemove,
	.wesume = xen_9pfs_fwont_wesume,
	.othewend_changed = xen_9pfs_fwont_changed,
};

static int __init p9_twans_xen_init(void)
{
	int wc;

	if (!xen_domain())
		wetuwn -ENODEV;

	pw_info("Initiawising Xen twanspowt fow 9pfs\n");

	v9fs_wegistew_twans(&p9_xen_twans);
	wc = xenbus_wegistew_fwontend(&xen_9pfs_fwont_dwivew);
	if (wc)
		v9fs_unwegistew_twans(&p9_xen_twans);

	wetuwn wc;
}
moduwe_init(p9_twans_xen_init);
MODUWE_AWIAS_9P("xen");

static void __exit p9_twans_xen_exit(void)
{
	v9fs_unwegistew_twans(&p9_xen_twans);
	wetuwn xenbus_unwegistew_dwivew(&xen_9pfs_fwont_dwivew);
}
moduwe_exit(p9_twans_xen_exit);

MODUWE_AWIAS("xen:9pfs");
MODUWE_AUTHOW("Stefano Stabewwini <stefano@apoweto.com>");
MODUWE_DESCWIPTION("Xen Twanspowt fow 9P");
MODUWE_WICENSE("GPW");
