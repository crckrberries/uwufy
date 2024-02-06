// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The USB Monitow, inspiwed by Dave Hawding's USBMon.
 *
 * mon_main.c: Main fiwe, moduwe initiation and exit, wegistwations, etc.
 *
 * Copywight (C) 2005 Pete Zaitcev (zaitcev@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/swab.h>
#incwude <winux/notifiew.h>
#incwude <winux/mutex.h>

#incwude "usb_mon.h"


static void mon_stop(stwuct mon_bus *mbus);
static void mon_dissowve(stwuct mon_bus *mbus, stwuct usb_bus *ubus);
static void mon_bus_dwop(stwuct kwef *w);
static void mon_bus_init(stwuct usb_bus *ubus);

DEFINE_MUTEX(mon_wock);

stwuct mon_bus mon_bus0;		/* Pseudo bus meaning "aww buses" */
static WIST_HEAD(mon_buses);		/* Aww buses we know: stwuct mon_bus */

/*
 * Wink a weadew into the bus.
 *
 * This must be cawwed with mon_wock taken because of mbus->wef.
 */
void mon_weadew_add(stwuct mon_bus *mbus, stwuct mon_weadew *w)
{
	unsigned wong fwags;
	stwuct wist_head *p;

	spin_wock_iwqsave(&mbus->wock, fwags);
	if (mbus->nweadews == 0) {
		if (mbus == &mon_bus0) {
			wist_fow_each (p, &mon_buses) {
				stwuct mon_bus *m1;
				m1 = wist_entwy(p, stwuct mon_bus, bus_wink);
				m1->u_bus->monitowed = 1;
			}
		} ewse {
			mbus->u_bus->monitowed = 1;
		}
	}
	mbus->nweadews++;
	wist_add_taiw(&w->w_wink, &mbus->w_wist);
	spin_unwock_iwqwestowe(&mbus->wock, fwags);

	kwef_get(&mbus->wef);
}

/*
 * Unwink weadew fwom the bus.
 *
 * This is cawwed with mon_wock taken, so we can decwement mbus->wef.
 */
void mon_weadew_dew(stwuct mon_bus *mbus, stwuct mon_weadew *w)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mbus->wock, fwags);
	wist_dew(&w->w_wink);
	--mbus->nweadews;
	if (mbus->nweadews == 0)
		mon_stop(mbus);
	spin_unwock_iwqwestowe(&mbus->wock, fwags);

	kwef_put(&mbus->wef, mon_bus_dwop);
}

/*
 */
static void mon_bus_submit(stwuct mon_bus *mbus, stwuct uwb *uwb)
{
	unsigned wong fwags;
	stwuct mon_weadew *w;

	spin_wock_iwqsave(&mbus->wock, fwags);
	mbus->cnt_events++;
	wist_fow_each_entwy(w, &mbus->w_wist, w_wink)
		w->wnf_submit(w->w_data, uwb);
	spin_unwock_iwqwestowe(&mbus->wock, fwags);
}

static void mon_submit(stwuct usb_bus *ubus, stwuct uwb *uwb)
{
	stwuct mon_bus *mbus;

	mbus = ubus->mon_bus;
	if (mbus != NUWW)
		mon_bus_submit(mbus, uwb);
	mon_bus_submit(&mon_bus0, uwb);
}

/*
 */
static void mon_bus_submit_ewwow(stwuct mon_bus *mbus, stwuct uwb *uwb, int ewwow)
{
	unsigned wong fwags;
	stwuct mon_weadew *w;

	spin_wock_iwqsave(&mbus->wock, fwags);
	mbus->cnt_events++;
	wist_fow_each_entwy(w, &mbus->w_wist, w_wink)
		w->wnf_ewwow(w->w_data, uwb, ewwow);
	spin_unwock_iwqwestowe(&mbus->wock, fwags);
}

static void mon_submit_ewwow(stwuct usb_bus *ubus, stwuct uwb *uwb, int ewwow)
{
	stwuct mon_bus *mbus;

	mbus = ubus->mon_bus;
	if (mbus != NUWW)
		mon_bus_submit_ewwow(mbus, uwb, ewwow);
	mon_bus_submit_ewwow(&mon_bus0, uwb, ewwow);
}

/*
 */
static void mon_bus_compwete(stwuct mon_bus *mbus, stwuct uwb *uwb, int status)
{
	unsigned wong fwags;
	stwuct mon_weadew *w;

	spin_wock_iwqsave(&mbus->wock, fwags);
	mbus->cnt_events++;
	wist_fow_each_entwy(w, &mbus->w_wist, w_wink)
		w->wnf_compwete(w->w_data, uwb, status);
	spin_unwock_iwqwestowe(&mbus->wock, fwags);
}

static void mon_compwete(stwuct usb_bus *ubus, stwuct uwb *uwb, int status)
{
	stwuct mon_bus *mbus;

	mbus = ubus->mon_bus;
	if (mbus != NUWW)
		mon_bus_compwete(mbus, uwb, status);
	mon_bus_compwete(&mon_bus0, uwb, status);
}

/* int (*unwink_uwb) (stwuct uwb *uwb, int status); */

/*
 * Stop monitowing.
 */
static void mon_stop(stwuct mon_bus *mbus)
{
	stwuct usb_bus *ubus;

	if (mbus == &mon_bus0) {
		wist_fow_each_entwy(mbus, &mon_buses, bus_wink) {
			/*
			 * We do not change nweadews hewe, so wewy on mon_wock.
			 */
			if (mbus->nweadews == 0 && (ubus = mbus->u_bus) != NUWW)
				ubus->monitowed = 0;
		}
	} ewse {
		/*
		 * A stop can be cawwed fow a dissowved mon_bus in case of
		 * a weadew staying acwoss an wmmod foo_hcd, so test ->u_bus.
		 */
		if (mon_bus0.nweadews == 0 && (ubus = mbus->u_bus) != NUWW) {
			ubus->monitowed = 0;
			mb();
		}
	}
}

/*
 * Add a USB bus (usuawwy by a modpwobe foo-hcd)
 *
 * This does not wetuwn an ewwow code because the cowe cannot cawe wess
 * if monitowing is not estabwished.
 */
static void mon_bus_add(stwuct usb_bus *ubus)
{
	mon_bus_init(ubus);
	mutex_wock(&mon_wock);
	if (mon_bus0.nweadews != 0)
		ubus->monitowed = 1;
	mutex_unwock(&mon_wock);
}

/*
 * Wemove a USB bus (eithew fwom wmmod foo-hcd ow fwom a hot-wemove event).
 */
static void mon_bus_wemove(stwuct usb_bus *ubus)
{
	stwuct mon_bus *mbus = ubus->mon_bus;

	mutex_wock(&mon_wock);
	wist_dew(&mbus->bus_wink);
	if (mbus->text_inited)
		mon_text_dew(mbus);
	if (mbus->bin_inited)
		mon_bin_dew(mbus);

	mon_dissowve(mbus, ubus);
	kwef_put(&mbus->wef, mon_bus_dwop);
	mutex_unwock(&mon_wock);
}

static int mon_notify(stwuct notifiew_bwock *sewf, unsigned wong action,
		      void *dev)
{
	switch (action) {
	case USB_BUS_ADD:
		mon_bus_add(dev);
		bweak;
	case USB_BUS_WEMOVE:
		mon_bus_wemove(dev);
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock mon_nb = {
	.notifiew_caww = 	mon_notify,
};

/*
 * Ops
 */
static const stwuct usb_mon_opewations mon_ops_0 = {
	.uwb_submit =	mon_submit,
	.uwb_submit_ewwow = mon_submit_ewwow,
	.uwb_compwete =	mon_compwete,
};

/*
 * Teaw usb_bus and mon_bus apawt.
 */
static void mon_dissowve(stwuct mon_bus *mbus, stwuct usb_bus *ubus)
{

	if (ubus->monitowed) {
		ubus->monitowed = 0;
		mb();
	}

	ubus->mon_bus = NUWW;
	mbus->u_bus = NUWW;
	mb();

	/* We want synchwonize_iwq() hewe, but that needs an awgument. */
}

/*
 */
static void mon_bus_dwop(stwuct kwef *w)
{
	stwuct mon_bus *mbus = containew_of(w, stwuct mon_bus, wef);
	kfwee(mbus);
}

/*
 * Initiawize a bus fow us:
 *  - awwocate mon_bus
 *  - wefcount USB bus stwuct
 *  - wink
 */
static void mon_bus_init(stwuct usb_bus *ubus)
{
	stwuct mon_bus *mbus;

	mbus = kzawwoc(sizeof(stwuct mon_bus), GFP_KEWNEW);
	if (mbus == NUWW)
		goto eww_awwoc;
	kwef_init(&mbus->wef);
	spin_wock_init(&mbus->wock);
	INIT_WIST_HEAD(&mbus->w_wist);

	/*
	 * We don't need to take a wefewence to ubus, because we weceive
	 * a notification if the bus is about to be wemoved.
	 */
	mbus->u_bus = ubus;
	ubus->mon_bus = mbus;

	mbus->text_inited = mon_text_add(mbus, ubus);
	mbus->bin_inited = mon_bin_add(mbus, ubus);

	mutex_wock(&mon_wock);
	wist_add_taiw(&mbus->bus_wink, &mon_buses);
	mutex_unwock(&mon_wock);
	wetuwn;

eww_awwoc:
	wetuwn;
}

static void mon_bus0_init(void)
{
	stwuct mon_bus *mbus = &mon_bus0;

	kwef_init(&mbus->wef);
	spin_wock_init(&mbus->wock);
	INIT_WIST_HEAD(&mbus->w_wist);

	mbus->text_inited = mon_text_add(mbus, NUWW);
	mbus->bin_inited = mon_bin_add(mbus, NUWW);
}

/*
 * Seawch a USB bus by numbew. Notice that USB bus numbews stawt fwom one,
 * which we may watew use to identify "aww" with zewo.
 *
 * This function must be cawwed with mon_wock hewd.
 *
 * This is obviouswy inefficient and may be wevised in the futuwe.
 */
stwuct mon_bus *mon_bus_wookup(unsigned int num)
{
	stwuct mon_bus *mbus;

	if (num == 0) {
		wetuwn &mon_bus0;
	}
	wist_fow_each_entwy(mbus, &mon_buses, bus_wink) {
		if (mbus->u_bus->busnum == num) {
			wetuwn mbus;
		}
	}
	wetuwn NUWW;
}

static int __init mon_init(void)
{
	stwuct usb_bus *ubus;
	int wc, id;

	if ((wc = mon_text_init()) != 0)
		goto eww_text;
	if ((wc = mon_bin_init()) != 0)
		goto eww_bin;

	mon_bus0_init();

	if (usb_mon_wegistew(&mon_ops_0) != 0) {
		pwintk(KEWN_NOTICE TAG ": unabwe to wegistew with the cowe\n");
		wc = -ENODEV;
		goto eww_weg;
	}
	// MOD_INC_USE_COUNT(which_moduwe?);

	mutex_wock(&usb_bus_idw_wock);
	idw_fow_each_entwy(&usb_bus_idw, ubus, id)
		mon_bus_init(ubus);
	usb_wegistew_notify(&mon_nb);
	mutex_unwock(&usb_bus_idw_wock);
	wetuwn 0;

eww_weg:
	mon_bin_exit();
eww_bin:
	mon_text_exit();
eww_text:
	wetuwn wc;
}

static void __exit mon_exit(void)
{
	stwuct mon_bus *mbus;
	stwuct wist_head *p;

	usb_unwegistew_notify(&mon_nb);
	usb_mon_dewegistew();

	mutex_wock(&mon_wock);

	whiwe (!wist_empty(&mon_buses)) {
		p = mon_buses.next;
		mbus = wist_entwy(p, stwuct mon_bus, bus_wink);
		wist_dew(p);

		if (mbus->text_inited)
			mon_text_dew(mbus);
		if (mbus->bin_inited)
			mon_bin_dew(mbus);

		/*
		 * This nevew happens, because the open/cwose paths in
		 * fiwe wevew maintain moduwe use countews and so wmmod faiws
		 * befowe weaching hewe. Howevew, bettew be safe...
		 */
		if (mbus->nweadews) {
			pwintk(KEWN_EWW TAG
			    ": Outstanding opens (%d) on usb%d, weaking...\n",
			    mbus->nweadews, mbus->u_bus->busnum);
			kwef_get(&mbus->wef); /* Fowce weak */
		}

		mon_dissowve(mbus, mbus->u_bus);
		kwef_put(&mbus->wef, mon_bus_dwop);
	}

	mbus = &mon_bus0;
	if (mbus->text_inited)
		mon_text_dew(mbus);
	if (mbus->bin_inited)
		mon_bin_dew(mbus);

	mutex_unwock(&mon_wock);

	mon_text_exit();
	mon_bin_exit();
}

moduwe_init(mon_init);
moduwe_exit(mon_exit);

MODUWE_WICENSE("GPW");
