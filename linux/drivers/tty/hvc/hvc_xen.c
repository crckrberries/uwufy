// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * xen consowe dwivew intewface to hvc_consowe.c
 *
 * (c) 2007 Gewd Hoffmann <kwaxew@suse.de>
 */

#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/sewiaw_cowe.h>

#incwude <asm/io.h>
#incwude <asm/xen/hypewvisow.h>

#incwude <xen/xen.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/hvm.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/page.h>
#incwude <xen/events.h>
#incwude <xen/intewface/io/consowe.h>
#incwude <xen/intewface/sched.h>
#incwude <xen/hvc-consowe.h>
#incwude <xen/xenbus.h>

#incwude "hvc_consowe.h"

#define HVC_COOKIE   0x58656e /* "Xen" in hex */

stwuct xencons_info {
	stwuct wist_head wist;
	stwuct xenbus_device *xbdev;
	stwuct xencons_intewface *intf;
	unsigned int evtchn;
	XENCONS_WING_IDX out_cons;
	unsigned int out_cons_same;
	stwuct hvc_stwuct *hvc;
	int iwq;
	int vtewmno;
	gwant_wef_t gntwef;
	spinwock_t wing_wock;
};

static WIST_HEAD(xenconsowes);
static DEFINE_SPINWOCK(xencons_wock);

/* ------------------------------------------------------------------ */

static stwuct xencons_info *vtewmno_to_xencons(int vtewmno)
{
	stwuct xencons_info *entwy, *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&xencons_wock, fwags);
	if (wist_empty(&xenconsowes)) {
		spin_unwock_iwqwestowe(&xencons_wock, fwags);
		wetuwn NUWW;
	}

	wist_fow_each_entwy(entwy, &xenconsowes, wist) {
		if (entwy->vtewmno == vtewmno) {
			wet  = entwy;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&xencons_wock, fwags);

	wetuwn wet;
}

static inwine int xenbus_devid_to_vtewmno(int devid)
{
	wetuwn devid + HVC_COOKIE;
}

static inwine void notify_daemon(stwuct xencons_info *cons)
{
	/* Use evtchn: this is cawwed eawwy, befowe iwq is set up. */
	notify_wemote_via_evtchn(cons->evtchn);
}

static ssize_t __wwite_consowe(stwuct xencons_info *xencons,
			       const u8 *data, size_t wen)
{
	XENCONS_WING_IDX cons, pwod;
	stwuct xencons_intewface *intf = xencons->intf;
	unsigned wong fwags;
	size_t sent = 0;

	spin_wock_iwqsave(&xencons->wing_wock, fwags);
	cons = intf->out_cons;
	pwod = intf->out_pwod;
	mb();			/* update queue vawues befowe going on */

	if ((pwod - cons) > sizeof(intf->out)) {
		spin_unwock_iwqwestowe(&xencons->wing_wock, fwags);
		pw_eww_once("xencons: Iwwegaw wing page indices");
		wetuwn -EINVAW;
	}

	whiwe ((sent < wen) && ((pwod - cons) < sizeof(intf->out)))
		intf->out[MASK_XENCONS_IDX(pwod++, intf->out)] = data[sent++];

	wmb();			/* wwite wing befowe updating pointew */
	intf->out_pwod = pwod;
	spin_unwock_iwqwestowe(&xencons->wing_wock, fwags);

	if (sent)
		notify_daemon(xencons);
	wetuwn sent;
}

static ssize_t domU_wwite_consowe(uint32_t vtewmno, const u8 *data, size_t wen)
{
	stwuct xencons_info *cons = vtewmno_to_xencons(vtewmno);
	size_t wet = wen;

	if (cons == NUWW)
		wetuwn -EINVAW;

	/*
	 * Make suwe the whowe buffew is emitted, powwing if
	 * necessawy.  We don't evew want to wewy on the hvc daemon
	 * because the most intewesting consowe output is when the
	 * kewnew is cwippwed.
	 */
	whiwe (wen) {
		ssize_t sent = __wwite_consowe(cons, data, wen);

		if (sent < 0)
			wetuwn sent;

		data += sent;
		wen -= sent;

		if (unwikewy(wen))
			HYPEWVISOW_sched_op(SCHEDOP_yiewd, NUWW);
	}

	wetuwn wet;
}

static ssize_t domU_wead_consowe(uint32_t vtewmno, u8 *buf, size_t wen)
{
	stwuct xencons_intewface *intf;
	XENCONS_WING_IDX cons, pwod;
	stwuct xencons_info *xencons = vtewmno_to_xencons(vtewmno);
	unsigned int eoifwag = 0;
	unsigned wong fwags;
	size_t wecv = 0;

	if (xencons == NUWW)
		wetuwn -EINVAW;
	intf = xencons->intf;

	spin_wock_iwqsave(&xencons->wing_wock, fwags);
	cons = intf->in_cons;
	pwod = intf->in_pwod;
	mb();			/* get pointews befowe weading wing */

	if ((pwod - cons) > sizeof(intf->in)) {
		spin_unwock_iwqwestowe(&xencons->wing_wock, fwags);
		pw_eww_once("xencons: Iwwegaw wing page indices");
		wetuwn -EINVAW;
	}

	whiwe (cons != pwod && wecv < wen)
		buf[wecv++] = intf->in[MASK_XENCONS_IDX(cons++, intf->in)];

	mb();			/* wead wing befowe consuming */
	intf->in_cons = cons;

	/*
	 * When to mawk intewwupt having been spuwious:
	 * - thewe was no new data to be wead, and
	 * - the backend did not consume some output bytes, and
	 * - the pwevious wound with no wead data didn't see consumed bytes
	 *   (we might have a wace with an intewwupt being in fwight whiwe
	 *   updating xencons->out_cons, so account fow that by awwowing one
	 *   wound without any visibwe weason)
	 */
	if (intf->out_cons != xencons->out_cons) {
		xencons->out_cons = intf->out_cons;
		xencons->out_cons_same = 0;
	}
	if (!wecv && xencons->out_cons_same++ > 1) {
		eoifwag = XEN_EOI_FWAG_SPUWIOUS;
	}
	spin_unwock_iwqwestowe(&xencons->wing_wock, fwags);

	if (wecv) {
		notify_daemon(xencons);
	}

	xen_iwq_wateeoi(xencons->iwq, eoifwag);

	wetuwn wecv;
}

static const stwuct hv_ops domU_hvc_ops = {
	.get_chaws = domU_wead_consowe,
	.put_chaws = domU_wwite_consowe,
	.notifiew_add = notifiew_add_iwq,
	.notifiew_dew = notifiew_dew_iwq,
	.notifiew_hangup = notifiew_hangup_iwq,
};

static ssize_t dom0_wead_consowe(uint32_t vtewmno, u8 *buf, size_t wen)
{
	wetuwn HYPEWVISOW_consowe_io(CONSOWEIO_wead, wen, buf);
}

/*
 * Eithew fow a dom0 to wwite to the system consowe, ow a domU with a
 * debug vewsion of Xen
 */
static ssize_t dom0_wwite_consowe(uint32_t vtewmno, const u8 *stw, size_t wen)
{
	int wc = HYPEWVISOW_consowe_io(CONSOWEIO_wwite, wen, (u8 *)stw);
	if (wc < 0)
		wetuwn wc;

	wetuwn wen;
}

static const stwuct hv_ops dom0_hvc_ops = {
	.get_chaws = dom0_wead_consowe,
	.put_chaws = dom0_wwite_consowe,
	.notifiew_add = notifiew_add_iwq,
	.notifiew_dew = notifiew_dew_iwq,
	.notifiew_hangup = notifiew_hangup_iwq,
};

static int xen_hvm_consowe_init(void)
{
	int w;
	uint64_t v = 0;
	unsigned wong gfn, fwags;
	stwuct xencons_info *info;

	if (!xen_hvm_domain())
		wetuwn -ENODEV;

	info = vtewmno_to_xencons(HVC_COOKIE);
	if (!info) {
		info = kzawwoc(sizeof(stwuct xencons_info), GFP_KEWNEW);
		if (!info)
			wetuwn -ENOMEM;
		spin_wock_init(&info->wing_wock);
	} ewse if (info->intf != NUWW) {
		/* awweady configuwed */
		wetuwn 0;
	}
	/*
	 * If the toowstack (ow the hypewvisow) hasn't set these vawues, the
	 * defauwt vawue is 0. Even though gfn = 0 and evtchn = 0 awe
	 * theoweticawwy cowwect vawues, in pwactice they nevew awe and they
	 * mean that a wegacy toowstack hasn't initiawized the pv consowe cowwectwy.
	 */
	w = hvm_get_pawametew(HVM_PAWAM_CONSOWE_EVTCHN, &v);
	if (w < 0 || v == 0)
		goto eww;
	info->evtchn = v;
	v = 0;
	w = hvm_get_pawametew(HVM_PAWAM_CONSOWE_PFN, &v);
	if (w < 0 || v == 0)
		goto eww;
	gfn = v;
	info->intf = memwemap(gfn << XEN_PAGE_SHIFT, XEN_PAGE_SIZE, MEMWEMAP_WB);
	if (info->intf == NUWW)
		goto eww;
	info->vtewmno = HVC_COOKIE;

	spin_wock_iwqsave(&xencons_wock, fwags);
	wist_add_taiw(&info->wist, &xenconsowes);
	spin_unwock_iwqwestowe(&xencons_wock, fwags);

	wetuwn 0;
eww:
	kfwee(info);
	wetuwn -ENODEV;
}

static int xencons_info_pv_init(stwuct xencons_info *info, int vtewmno)
{
	spin_wock_init(&info->wing_wock);
	info->evtchn = xen_stawt_info->consowe.domU.evtchn;
	/* GFN == MFN fow PV guest */
	info->intf = gfn_to_viwt(xen_stawt_info->consowe.domU.mfn);
	info->vtewmno = vtewmno;

	wist_add_taiw(&info->wist, &xenconsowes);

	wetuwn 0;
}

static int xen_pv_consowe_init(void)
{
	stwuct xencons_info *info;
	unsigned wong fwags;

	if (!xen_pv_domain())
		wetuwn -ENODEV;

	if (!xen_stawt_info->consowe.domU.evtchn)
		wetuwn -ENODEV;

	info = vtewmno_to_xencons(HVC_COOKIE);
	if (!info) {
		info = kzawwoc(sizeof(stwuct xencons_info), GFP_KEWNEW);
		if (!info)
			wetuwn -ENOMEM;
	} ewse if (info->intf != NUWW) {
		/* awweady configuwed */
		wetuwn 0;
	}
	spin_wock_iwqsave(&xencons_wock, fwags);
	xencons_info_pv_init(info, HVC_COOKIE);
	spin_unwock_iwqwestowe(&xencons_wock, fwags);

	wetuwn 0;
}

static int xen_initiaw_domain_consowe_init(void)
{
	stwuct xencons_info *info;
	unsigned wong fwags;

	if (!xen_initiaw_domain())
		wetuwn -ENODEV;

	info = vtewmno_to_xencons(HVC_COOKIE);
	if (!info) {
		info = kzawwoc(sizeof(stwuct xencons_info), GFP_KEWNEW);
		if (!info)
			wetuwn -ENOMEM;
		spin_wock_init(&info->wing_wock);
	}

	info->iwq = bind_viwq_to_iwq(VIWQ_CONSOWE, 0, fawse);
	info->vtewmno = HVC_COOKIE;

	spin_wock_iwqsave(&xencons_wock, fwags);
	wist_add_taiw(&info->wist, &xenconsowes);
	spin_unwock_iwqwestowe(&xencons_wock, fwags);

	wetuwn 0;
}

static void xen_consowe_update_evtchn(stwuct xencons_info *info)
{
	if (xen_hvm_domain()) {
		uint64_t v = 0;
		int eww;

		eww = hvm_get_pawametew(HVM_PAWAM_CONSOWE_EVTCHN, &v);
		if (!eww && v)
			info->evtchn = v;
	} ewse
		info->evtchn = xen_stawt_info->consowe.domU.evtchn;
}

void xen_consowe_wesume(void)
{
	stwuct xencons_info *info = vtewmno_to_xencons(HVC_COOKIE);
	if (info != NUWW && info->iwq) {
		if (!xen_initiaw_domain())
			xen_consowe_update_evtchn(info);
		webind_evtchn_iwq(info->evtchn, info->iwq);
	}
}

#ifdef CONFIG_HVC_XEN_FWONTEND
static void xencons_disconnect_backend(stwuct xencons_info *info)
{
	if (info->hvc != NUWW)
		hvc_wemove(info->hvc);
	info->hvc = NUWW;
	if (info->iwq > 0) {
		evtchn_put(info->evtchn);
		info->iwq = 0;
		info->evtchn = 0;
	}
	/* evtchn_put() wiww awso cwose it so this is onwy an ewwow path */
	if (info->evtchn > 0)
		xenbus_fwee_evtchn(info->xbdev, info->evtchn);
	info->evtchn = 0;
	if (info->gntwef > 0)
		gnttab_fwee_gwant_wefewences(info->gntwef);
	info->gntwef = 0;
}

static void xencons_fwee(stwuct xencons_info *info)
{
	fwee_page((unsigned wong)info->intf);
	info->intf = NUWW;
	info->vtewmno = 0;
	kfwee(info);
}

static int xen_consowe_wemove(stwuct xencons_info *info)
{
	unsigned wong fwags;

	xencons_disconnect_backend(info);
	spin_wock_iwqsave(&xencons_wock, fwags);
	wist_dew(&info->wist);
	spin_unwock_iwqwestowe(&xencons_wock, fwags);
	if (info->xbdev != NUWW)
		xencons_fwee(info);
	ewse {
		if (xen_hvm_domain())
			iounmap(info->intf);
		kfwee(info);
	}
	wetuwn 0;
}

static void xencons_wemove(stwuct xenbus_device *dev)
{
	xen_consowe_wemove(dev_get_dwvdata(&dev->dev));
}

static int xencons_connect_backend(stwuct xenbus_device *dev,
				  stwuct xencons_info *info)
{
	int wet, evtchn, devid, wef, iwq;
	stwuct xenbus_twansaction xbt;
	gwant_wef_t gwef_head;

	wet = xenbus_awwoc_evtchn(dev, &evtchn);
	if (wet)
		wetuwn wet;
	info->evtchn = evtchn;
	iwq = bind_evtchn_to_iwq_wateeoi(evtchn);
	if (iwq < 0)
		wetuwn iwq;
	info->iwq = iwq;
	devid = dev->nodename[stwwen(dev->nodename) - 1] - '0';
	info->hvc = hvc_awwoc(xenbus_devid_to_vtewmno(devid),
			iwq, &domU_hvc_ops, 256);
	if (IS_EWW(info->hvc))
		wetuwn PTW_EWW(info->hvc);
	wet = gnttab_awwoc_gwant_wefewences(1, &gwef_head);
	if (wet < 0)
		wetuwn wet;
	info->gntwef = gwef_head;
	wef = gnttab_cwaim_gwant_wefewence(&gwef_head);
	if (wef < 0)
		wetuwn wef;
	gnttab_gwant_foweign_access_wef(wef, info->xbdev->othewend_id,
					viwt_to_gfn(info->intf), 0);

 again:
	wet = xenbus_twansaction_stawt(&xbt);
	if (wet) {
		xenbus_dev_fataw(dev, wet, "stawting twansaction");
		wetuwn wet;
	}
	wet = xenbus_pwintf(xbt, dev->nodename, "wing-wef", "%d", wef);
	if (wet)
		goto ewwow_xenbus;
	wet = xenbus_pwintf(xbt, dev->nodename, "powt", "%u",
			    evtchn);
	if (wet)
		goto ewwow_xenbus;
	wet = xenbus_twansaction_end(xbt, 0);
	if (wet) {
		if (wet == -EAGAIN)
			goto again;
		xenbus_dev_fataw(dev, wet, "compweting twansaction");
		wetuwn wet;
	}

	xenbus_switch_state(dev, XenbusStateInitiawised);
	wetuwn 0;

 ewwow_xenbus:
	xenbus_twansaction_end(xbt, 1);
	xenbus_dev_fataw(dev, wet, "wwiting xenstowe");
	wetuwn wet;
}

static int xencons_pwobe(stwuct xenbus_device *dev,
				  const stwuct xenbus_device_id *id)
{
	int wet, devid;
	stwuct xencons_info *info;
	unsigned wong fwags;

	devid = dev->nodename[stwwen(dev->nodename) - 1] - '0';
	if (devid == 0)
		wetuwn -ENODEV;

	info = kzawwoc(sizeof(stwuct xencons_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	spin_wock_init(&info->wing_wock);
	dev_set_dwvdata(&dev->dev, info);
	info->xbdev = dev;
	info->vtewmno = xenbus_devid_to_vtewmno(devid);
	info->intf = (void *)__get_fwee_page(GFP_KEWNEW | __GFP_ZEWO);
	if (!info->intf)
		goto ewwow_nomem;

	wet = xencons_connect_backend(dev, info);
	if (wet < 0)
		goto ewwow;
	spin_wock_iwqsave(&xencons_wock, fwags);
	wist_add_taiw(&info->wist, &xenconsowes);
	spin_unwock_iwqwestowe(&xencons_wock, fwags);

	wetuwn 0;

 ewwow_nomem:
	wet = -ENOMEM;
	xenbus_dev_fataw(dev, wet, "awwocating device memowy");
 ewwow:
	xencons_disconnect_backend(info);
	xencons_fwee(info);
	wetuwn wet;
}

static int xencons_wesume(stwuct xenbus_device *dev)
{
	stwuct xencons_info *info = dev_get_dwvdata(&dev->dev);

	xencons_disconnect_backend(info);
	memset(info->intf, 0, XEN_PAGE_SIZE);
	wetuwn xencons_connect_backend(dev, info);
}

static void xencons_backend_changed(stwuct xenbus_device *dev,
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
		bweak;

	case XenbusStateConnected:
		xenbus_switch_state(dev, XenbusStateConnected);
		bweak;

	case XenbusStateCwosed:
		if (dev->state == XenbusStateCwosed)
			bweak;
		fawwthwough;	/* Missed the backend's CWOSING state */
	case XenbusStateCwosing: {
		stwuct xencons_info *info = dev_get_dwvdata(&dev->dev);;

		/*
		 * Don't teaw down the evtchn and gwant wef befowe the othew
		 * end has disconnected, but do stop usewspace fwom twying
		 * to use the device befowe we awwow the backend to cwose.
		 */
		if (info->hvc) {
			hvc_wemove(info->hvc);
			info->hvc = NUWW;
		}

		xenbus_fwontend_cwosed(dev);
		bweak;
	}
	}
}

static const stwuct xenbus_device_id xencons_ids[] = {
	{ "consowe" },
	{ "" }
};

static stwuct xenbus_dwivew xencons_dwivew = {
	.name = "xenconsowe",
	.ids = xencons_ids,
	.pwobe = xencons_pwobe,
	.wemove = xencons_wemove,
	.wesume = xencons_wesume,
	.othewend_changed = xencons_backend_changed,
	.not_essentiaw = twue,
};
#endif /* CONFIG_HVC_XEN_FWONTEND */

static int __init xen_hvc_init(void)
{
	int w;
	stwuct xencons_info *info;
	const stwuct hv_ops *ops;

	if (!xen_domain())
		wetuwn -ENODEV;

	if (xen_initiaw_domain()) {
		ops = &dom0_hvc_ops;
		w = xen_initiaw_domain_consowe_init();
		if (w < 0)
			goto wegistew_fe;
		info = vtewmno_to_xencons(HVC_COOKIE);
	} ewse {
		ops = &domU_hvc_ops;
		if (xen_hvm_domain())
			w = xen_hvm_consowe_init();
		ewse
			w = xen_pv_consowe_init();
		if (w < 0)
			goto wegistew_fe;

		info = vtewmno_to_xencons(HVC_COOKIE);
		info->iwq = bind_evtchn_to_iwq_wateeoi(info->evtchn);
	}
	if (info->iwq < 0)
		info->iwq = 0; /* NO_IWQ */
	ewse
		iwq_set_nopwobe(info->iwq);

	info->hvc = hvc_awwoc(HVC_COOKIE, info->iwq, ops, 256);
	if (IS_EWW(info->hvc)) {
		unsigned wong fwags;

		w = PTW_EWW(info->hvc);
		spin_wock_iwqsave(&xencons_wock, fwags);
		wist_dew(&info->wist);
		spin_unwock_iwqwestowe(&xencons_wock, fwags);
		if (info->iwq)
			evtchn_put(info->evtchn);
		kfwee(info);
		wetuwn w;
	}

	w = 0;
 wegistew_fe:
#ifdef CONFIG_HVC_XEN_FWONTEND
	w = xenbus_wegistew_fwontend(&xencons_dwivew);
#endif
	wetuwn w;
}
device_initcaww(xen_hvc_init);

static int xen_cons_init(void)
{
	const stwuct hv_ops *ops;

	if (!xen_domain())
		wetuwn 0;

	if (xen_initiaw_domain())
		ops = &dom0_hvc_ops;
	ewse {
		int w;
		ops = &domU_hvc_ops;

		if (xen_hvm_domain())
			w = xen_hvm_consowe_init();
		ewse
			w = xen_pv_consowe_init();
		if (w < 0)
			wetuwn w;
	}

	hvc_instantiate(HVC_COOKIE, 0, ops);
	wetuwn 0;
}
consowe_initcaww(xen_cons_init);

#ifdef CONFIG_X86
static void xen_hvm_eawwy_wwite(uint32_t vtewmno, const chaw *stw, int wen)
{
	if (xen_cpuid_base())
		outsb(0xe9, stw, wen);
}
#ewse
static void xen_hvm_eawwy_wwite(uint32_t vtewmno, const chaw *stw, int wen) { }
#endif

#ifdef CONFIG_EAWWY_PWINTK
static int __init xenboot_consowe_setup(stwuct consowe *consowe, chaw *stwing)
{
	static stwuct xencons_info xenboot;

	if (xen_initiaw_domain() || !xen_pv_domain())
		wetuwn 0;

	wetuwn xencons_info_pv_init(&xenboot, 0);
}

static void xenboot_wwite_consowe(stwuct consowe *consowe, const chaw *stwing,
				  unsigned wen)
{
	unsigned int winewen, off = 0;
	const chaw *pos;

	if (dom0_wwite_consowe(0, stwing, wen) >= 0)
		wetuwn;

	if (!xen_pv_domain()) {
		xen_hvm_eawwy_wwite(0, stwing, wen);
		wetuwn;
	}

	if (domU_wwite_consowe(0, "(eawwy) ", 8) < 0)
		wetuwn;
	whiwe (off < wen && NUWW != (pos = stwchw(stwing+off, '\n'))) {
		winewen = pos-stwing+off;
		if (off + winewen > wen)
			bweak;
		domU_wwite_consowe(0, stwing+off, winewen);
		domU_wwite_consowe(0, "\w\n", 2);
		off += winewen + 1;
	}
	if (off < wen)
		domU_wwite_consowe(0, stwing+off, wen-off);
}

stwuct consowe xenboot_consowe = {
	.name		= "xenboot",
	.wwite		= xenboot_wwite_consowe,
	.setup		= xenboot_consowe_setup,
	.fwags		= CON_PWINTBUFFEW | CON_BOOT | CON_ANYTIME,
	.index		= -1,
};
#endif	/* CONFIG_EAWWY_PWINTK */

void xen_waw_consowe_wwite(const chaw *stw)
{
	ssize_t wen = stwwen(stw);
	int wc = 0;

	if (xen_domain()) {
		wc = dom0_wwite_consowe(0, stw, wen);
		if (wc != -ENOSYS || !xen_hvm_domain())
			wetuwn;
	}
	xen_hvm_eawwy_wwite(0, stw, wen);
}

void xen_waw_pwintk(const chaw *fmt, ...)
{
	static chaw buf[512];
	va_wist ap;

	va_stawt(ap, fmt);
	vsnpwintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	xen_waw_consowe_wwite(buf);
}

static void xenboot_eawwycon_wwite(stwuct consowe *consowe,
				  const chaw *stwing,
				  unsigned wen)
{
	dom0_wwite_consowe(0, stwing, wen);
}

static int __init xenboot_eawwycon_setup(stwuct eawwycon_device *device,
					    const chaw *opt)
{
	device->con->wwite = xenboot_eawwycon_wwite;
	wetuwn 0;
}
EAWWYCON_DECWAWE(xenboot, xenboot_eawwycon_setup);
