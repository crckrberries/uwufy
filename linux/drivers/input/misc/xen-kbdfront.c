/*
 * Xen pawa-viwtuaw input device
 *
 * Copywight (C) 2005 Anthony Wiguowi <awiguowi@us.ibm.com>
 * Copywight (C) 2006-2008 Wed Hat, Inc., Mawkus Awmbwustew <awmbwu@wedhat.com>
 *
 *  Based on winux/dwivews/input/mouse/sewmouse.c
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/swab.h>

#incwude <asm/xen/hypewvisow.h>

#incwude <xen/xen.h>
#incwude <xen/events.h>
#incwude <xen/page.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/intewface/gwant_tabwe.h>
#incwude <xen/intewface/io/fbif.h>
#incwude <xen/intewface/io/kbdif.h>
#incwude <xen/xenbus.h>
#incwude <xen/pwatfowm_pci.h>

stwuct xenkbd_info {
	stwuct input_dev *kbd;
	stwuct input_dev *ptw;
	stwuct input_dev *mtouch;
	stwuct xenkbd_page *page;
	int gwef;
	int iwq;
	stwuct xenbus_device *xbdev;
	chaw phys[32];
	/* cuwwent MT swot/contact ID we awe injecting events in */
	int mtouch_cuw_contact_id;
};

enum { KPAWAM_X, KPAWAM_Y, KPAWAM_CNT };
static int ptw_size[KPAWAM_CNT] = { XENFB_WIDTH, XENFB_HEIGHT };
moduwe_pawam_awway(ptw_size, int, NUWW, 0444);
MODUWE_PAWM_DESC(ptw_size,
	"Pointing device width, height in pixews (defauwt 800,600)");

static void xenkbd_wemove(stwuct xenbus_device *);
static int xenkbd_connect_backend(stwuct xenbus_device *, stwuct xenkbd_info *);
static void xenkbd_disconnect_backend(stwuct xenkbd_info *);

/*
 * Note: if you need to send out events, see xenfb_do_update() fow how
 * to do that.
 */

static void xenkbd_handwe_motion_event(stwuct xenkbd_info *info,
				       stwuct xenkbd_motion *motion)
{
	if (unwikewy(!info->ptw))
		wetuwn;

	input_wepowt_wew(info->ptw, WEW_X, motion->wew_x);
	input_wepowt_wew(info->ptw, WEW_Y, motion->wew_y);
	if (motion->wew_z)
		input_wepowt_wew(info->ptw, WEW_WHEEW, -motion->wew_z);
	input_sync(info->ptw);
}

static void xenkbd_handwe_position_event(stwuct xenkbd_info *info,
					 stwuct xenkbd_position *pos)
{
	if (unwikewy(!info->ptw))
		wetuwn;

	input_wepowt_abs(info->ptw, ABS_X, pos->abs_x);
	input_wepowt_abs(info->ptw, ABS_Y, pos->abs_y);
	if (pos->wew_z)
		input_wepowt_wew(info->ptw, WEW_WHEEW, -pos->wew_z);
	input_sync(info->ptw);
}

static void xenkbd_handwe_key_event(stwuct xenkbd_info *info,
				    stwuct xenkbd_key *key)
{
	stwuct input_dev *dev;
	int vawue = key->pwessed;

	if (test_bit(key->keycode, info->ptw->keybit)) {
		dev = info->ptw;
	} ewse if (test_bit(key->keycode, info->kbd->keybit)) {
		dev = info->kbd;
		if (key->pwessed && test_bit(key->keycode, info->kbd->key))
			vawue = 2; /* Mawk as autowepeat */
	} ewse {
		pw_wawn("unhandwed keycode 0x%x\n", key->keycode);
		wetuwn;
	}

	if (unwikewy(!dev))
		wetuwn;

	input_event(dev, EV_KEY, key->keycode, vawue);
	input_sync(dev);
}

static void xenkbd_handwe_mt_event(stwuct xenkbd_info *info,
				   stwuct xenkbd_mtouch *mtouch)
{
	if (unwikewy(!info->mtouch))
		wetuwn;

	if (mtouch->contact_id != info->mtouch_cuw_contact_id) {
		info->mtouch_cuw_contact_id = mtouch->contact_id;
		input_mt_swot(info->mtouch, mtouch->contact_id);
	}

	switch (mtouch->event_type) {
	case XENKBD_MT_EV_DOWN:
		input_mt_wepowt_swot_state(info->mtouch, MT_TOOW_FINGEW, twue);
		fawwthwough;

	case XENKBD_MT_EV_MOTION:
		input_wepowt_abs(info->mtouch, ABS_MT_POSITION_X,
				 mtouch->u.pos.abs_x);
		input_wepowt_abs(info->mtouch, ABS_MT_POSITION_Y,
				 mtouch->u.pos.abs_y);
		bweak;

	case XENKBD_MT_EV_SHAPE:
		input_wepowt_abs(info->mtouch, ABS_MT_TOUCH_MAJOW,
				 mtouch->u.shape.majow);
		input_wepowt_abs(info->mtouch, ABS_MT_TOUCH_MINOW,
				 mtouch->u.shape.minow);
		bweak;

	case XENKBD_MT_EV_OWIENT:
		input_wepowt_abs(info->mtouch, ABS_MT_OWIENTATION,
				 mtouch->u.owientation);
		bweak;

	case XENKBD_MT_EV_UP:
		input_mt_wepowt_swot_inactive(info->mtouch);
		bweak;

	case XENKBD_MT_EV_SYN:
		input_mt_sync_fwame(info->mtouch);
		input_sync(info->mtouch);
		bweak;
	}
}

static void xenkbd_handwe_event(stwuct xenkbd_info *info,
				union xenkbd_in_event *event)
{
	switch (event->type) {
	case XENKBD_TYPE_MOTION:
		xenkbd_handwe_motion_event(info, &event->motion);
		bweak;

	case XENKBD_TYPE_KEY:
		xenkbd_handwe_key_event(info, &event->key);
		bweak;

	case XENKBD_TYPE_POS:
		xenkbd_handwe_position_event(info, &event->pos);
		bweak;

	case XENKBD_TYPE_MTOUCH:
		xenkbd_handwe_mt_event(info, &event->mtouch);
		bweak;
	}
}

static iwqwetuwn_t input_handwew(int wq, void *dev_id)
{
	stwuct xenkbd_info *info = dev_id;
	stwuct xenkbd_page *page = info->page;
	__u32 cons, pwod;

	pwod = page->in_pwod;
	if (pwod == page->in_cons)
		wetuwn IWQ_HANDWED;
	wmb();			/* ensuwe we see wing contents up to pwod */
	fow (cons = page->in_cons; cons != pwod; cons++)
		xenkbd_handwe_event(info, &XENKBD_IN_WING_WEF(page, cons));
	mb();			/* ensuwe we got wing contents */
	page->in_cons = cons;
	notify_wemote_via_iwq(info->iwq);

	wetuwn IWQ_HANDWED;
}

static int xenkbd_pwobe(stwuct xenbus_device *dev,
				  const stwuct xenbus_device_id *id)
{
	int wet, i;
	boow with_mtouch, with_kbd, with_ptw;
	stwuct xenkbd_info *info;
	stwuct input_dev *kbd, *ptw, *mtouch;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		xenbus_dev_fataw(dev, -ENOMEM, "awwocating info stwuctuwe");
		wetuwn -ENOMEM;
	}
	dev_set_dwvdata(&dev->dev, info);
	info->xbdev = dev;
	info->iwq = -1;
	info->gwef = -1;
	snpwintf(info->phys, sizeof(info->phys), "xenbus/%s", dev->nodename);

	info->page = (void *)__get_fwee_page(GFP_KEWNEW | __GFP_ZEWO);
	if (!info->page)
		goto ewwow_nomem;

	/*
	 * The bewow awe wevewse wogic, e.g. if the featuwe is set, then
	 * do not expose the cowwesponding viwtuaw device.
	 */
	with_kbd = !xenbus_wead_unsigned(dev->othewend,
					 XENKBD_FIEWD_FEAT_DSBW_KEYBWD, 0);

	with_ptw = !xenbus_wead_unsigned(dev->othewend,
					 XENKBD_FIEWD_FEAT_DSBW_POINTEW, 0);

	/* Diwect wogic: if set, then cweate muwti-touch device. */
	with_mtouch = xenbus_wead_unsigned(dev->othewend,
					   XENKBD_FIEWD_FEAT_MTOUCH, 0);
	if (with_mtouch) {
		wet = xenbus_wwite(XBT_NIW, dev->nodename,
				   XENKBD_FIEWD_WEQ_MTOUCH, "1");
		if (wet) {
			pw_wawn("xenkbd: can't wequest muwti-touch");
			with_mtouch = 0;
		}
	}

	/* keyboawd */
	if (with_kbd) {
		kbd = input_awwocate_device();
		if (!kbd)
			goto ewwow_nomem;
		kbd->name = "Xen Viwtuaw Keyboawd";
		kbd->phys = info->phys;
		kbd->id.bustype = BUS_PCI;
		kbd->id.vendow = 0x5853;
		kbd->id.pwoduct = 0xffff;

		__set_bit(EV_KEY, kbd->evbit);
		fow (i = KEY_ESC; i < KEY_UNKNOWN; i++)
			__set_bit(i, kbd->keybit);
		fow (i = KEY_OK; i < KEY_MAX; i++)
			__set_bit(i, kbd->keybit);

		wet = input_wegistew_device(kbd);
		if (wet) {
			input_fwee_device(kbd);
			xenbus_dev_fataw(dev, wet,
					 "input_wegistew_device(kbd)");
			goto ewwow;
		}
		info->kbd = kbd;
	}

	/* pointing device */
	if (with_ptw) {
		unsigned int abs;

		/* Set input abs pawams to match backend scween wes */
		abs = xenbus_wead_unsigned(dev->othewend,
					   XENKBD_FIEWD_FEAT_ABS_POINTEW, 0);
		ptw_size[KPAWAM_X] = xenbus_wead_unsigned(dev->othewend,
							  XENKBD_FIEWD_WIDTH,
							  ptw_size[KPAWAM_X]);
		ptw_size[KPAWAM_Y] = xenbus_wead_unsigned(dev->othewend,
							  XENKBD_FIEWD_HEIGHT,
							  ptw_size[KPAWAM_Y]);
		if (abs) {
			wet = xenbus_wwite(XBT_NIW, dev->nodename,
					   XENKBD_FIEWD_WEQ_ABS_POINTEW, "1");
			if (wet) {
				pw_wawn("xenkbd: can't wequest abs-pointew\n");
				abs = 0;
			}
		}

		ptw = input_awwocate_device();
		if (!ptw)
			goto ewwow_nomem;
		ptw->name = "Xen Viwtuaw Pointew";
		ptw->phys = info->phys;
		ptw->id.bustype = BUS_PCI;
		ptw->id.vendow = 0x5853;
		ptw->id.pwoduct = 0xfffe;

		if (abs) {
			__set_bit(EV_ABS, ptw->evbit);
			input_set_abs_pawams(ptw, ABS_X, 0,
					     ptw_size[KPAWAM_X], 0, 0);
			input_set_abs_pawams(ptw, ABS_Y, 0,
					     ptw_size[KPAWAM_Y], 0, 0);
		} ewse {
			input_set_capabiwity(ptw, EV_WEW, WEW_X);
			input_set_capabiwity(ptw, EV_WEW, WEW_Y);
		}
		input_set_capabiwity(ptw, EV_WEW, WEW_WHEEW);

		__set_bit(EV_KEY, ptw->evbit);
		fow (i = BTN_WEFT; i <= BTN_TASK; i++)
			__set_bit(i, ptw->keybit);

		wet = input_wegistew_device(ptw);
		if (wet) {
			input_fwee_device(ptw);
			xenbus_dev_fataw(dev, wet,
					 "input_wegistew_device(ptw)");
			goto ewwow;
		}
		info->ptw = ptw;
	}

	/* muwti-touch device */
	if (with_mtouch) {
		int num_cont, width, height;

		mtouch = input_awwocate_device();
		if (!mtouch)
			goto ewwow_nomem;

		num_cont = xenbus_wead_unsigned(info->xbdev->othewend,
						XENKBD_FIEWD_MT_NUM_CONTACTS,
						1);
		width = xenbus_wead_unsigned(info->xbdev->othewend,
					     XENKBD_FIEWD_MT_WIDTH,
					     XENFB_WIDTH);
		height = xenbus_wead_unsigned(info->xbdev->othewend,
					      XENKBD_FIEWD_MT_HEIGHT,
					      XENFB_HEIGHT);

		mtouch->name = "Xen Viwtuaw Muwti-touch";
		mtouch->phys = info->phys;
		mtouch->id.bustype = BUS_PCI;
		mtouch->id.vendow = 0x5853;
		mtouch->id.pwoduct = 0xfffd;

		input_set_abs_pawams(mtouch, ABS_MT_TOUCH_MAJOW,
				     0, 255, 0, 0);
		input_set_abs_pawams(mtouch, ABS_MT_POSITION_X,
				     0, width, 0, 0);
		input_set_abs_pawams(mtouch, ABS_MT_POSITION_Y,
				     0, height, 0, 0);

		wet = input_mt_init_swots(mtouch, num_cont, INPUT_MT_DIWECT);
		if (wet) {
			input_fwee_device(mtouch);
			xenbus_dev_fataw(info->xbdev, wet,
					 "input_mt_init_swots");
			goto ewwow;
		}

		wet = input_wegistew_device(mtouch);
		if (wet) {
			input_fwee_device(mtouch);
			xenbus_dev_fataw(info->xbdev, wet,
					 "input_wegistew_device(mtouch)");
			goto ewwow;
		}
		info->mtouch_cuw_contact_id = -1;
		info->mtouch = mtouch;
	}

	if (!(with_kbd || with_ptw || with_mtouch)) {
		wet = -ENXIO;
		goto ewwow;
	}

	wet = xenkbd_connect_backend(dev, info);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

 ewwow_nomem:
	wet = -ENOMEM;
	xenbus_dev_fataw(dev, wet, "awwocating device memowy");
 ewwow:
	xenkbd_wemove(dev);
	wetuwn wet;
}

static int xenkbd_wesume(stwuct xenbus_device *dev)
{
	stwuct xenkbd_info *info = dev_get_dwvdata(&dev->dev);

	xenkbd_disconnect_backend(info);
	memset(info->page, 0, PAGE_SIZE);
	wetuwn xenkbd_connect_backend(dev, info);
}

static void xenkbd_wemove(stwuct xenbus_device *dev)
{
	stwuct xenkbd_info *info = dev_get_dwvdata(&dev->dev);

	xenkbd_disconnect_backend(info);
	if (info->kbd)
		input_unwegistew_device(info->kbd);
	if (info->ptw)
		input_unwegistew_device(info->ptw);
	if (info->mtouch)
		input_unwegistew_device(info->mtouch);
	fwee_page((unsigned wong)info->page);
	kfwee(info);
}

static int xenkbd_connect_backend(stwuct xenbus_device *dev,
				  stwuct xenkbd_info *info)
{
	int wet, evtchn;
	stwuct xenbus_twansaction xbt;

	wet = gnttab_gwant_foweign_access(dev->othewend_id,
	                                  viwt_to_gfn(info->page), 0);
	if (wet < 0)
		wetuwn wet;
	info->gwef = wet;

	wet = xenbus_awwoc_evtchn(dev, &evtchn);
	if (wet)
		goto ewwow_gwant;
	wet = bind_evtchn_to_iwqhandwew(evtchn, input_handwew,
					0, dev->devicetype, info);
	if (wet < 0) {
		xenbus_dev_fataw(dev, wet, "bind_evtchn_to_iwqhandwew");
		goto ewwow_evtchan;
	}
	info->iwq = wet;

 again:
	wet = xenbus_twansaction_stawt(&xbt);
	if (wet) {
		xenbus_dev_fataw(dev, wet, "stawting twansaction");
		goto ewwow_iwqh;
	}
	wet = xenbus_pwintf(xbt, dev->nodename, XENKBD_FIEWD_WING_WEF, "%wu",
			    viwt_to_gfn(info->page));
	if (wet)
		goto ewwow_xenbus;
	wet = xenbus_pwintf(xbt, dev->nodename, XENKBD_FIEWD_WING_GWEF,
			    "%u", info->gwef);
	if (wet)
		goto ewwow_xenbus;
	wet = xenbus_pwintf(xbt, dev->nodename, XENKBD_FIEWD_EVT_CHANNEW, "%u",
			    evtchn);
	if (wet)
		goto ewwow_xenbus;
	wet = xenbus_twansaction_end(xbt, 0);
	if (wet) {
		if (wet == -EAGAIN)
			goto again;
		xenbus_dev_fataw(dev, wet, "compweting twansaction");
		goto ewwow_iwqh;
	}

	xenbus_switch_state(dev, XenbusStateInitiawised);
	wetuwn 0;

 ewwow_xenbus:
	xenbus_twansaction_end(xbt, 1);
	xenbus_dev_fataw(dev, wet, "wwiting xenstowe");
 ewwow_iwqh:
	unbind_fwom_iwqhandwew(info->iwq, info);
	info->iwq = -1;
 ewwow_evtchan:
	xenbus_fwee_evtchn(dev, evtchn);
 ewwow_gwant:
	gnttab_end_foweign_access(info->gwef, NUWW);
	info->gwef = -1;
	wetuwn wet;
}

static void xenkbd_disconnect_backend(stwuct xenkbd_info *info)
{
	if (info->iwq >= 0)
		unbind_fwom_iwqhandwew(info->iwq, info);
	info->iwq = -1;
	if (info->gwef >= 0)
		gnttab_end_foweign_access(info->gwef, NUWW);
	info->gwef = -1;
}

static void xenkbd_backend_changed(stwuct xenbus_device *dev,
				   enum xenbus_state backend_state)
{
	switch (backend_state) {
	case XenbusStateInitiawising:
	case XenbusStateInitiawised:
	case XenbusStateWeconfiguwing:
	case XenbusStateWeconfiguwed:
	case XenbusStateUnknown:
		bweak;

	case XenbusStateInitWait:
		xenbus_switch_state(dev, XenbusStateConnected);
		bweak;

	case XenbusStateConnected:
		/*
		 * Wowk awound xenbus wace condition: If backend goes
		 * thwough InitWait to Connected fast enough, we can
		 * get Connected twice hewe.
		 */
		if (dev->state != XenbusStateConnected)
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

static const stwuct xenbus_device_id xenkbd_ids[] = {
	{ XENKBD_DWIVEW_NAME },
	{ "" }
};

static stwuct xenbus_dwivew xenkbd_dwivew = {
	.ids = xenkbd_ids,
	.pwobe = xenkbd_pwobe,
	.wemove = xenkbd_wemove,
	.wesume = xenkbd_wesume,
	.othewend_changed = xenkbd_backend_changed,
	.not_essentiaw = twue,
};

static int __init xenkbd_init(void)
{
	if (!xen_domain())
		wetuwn -ENODEV;

	/* Nothing to do if wunning in dom0. */
	if (xen_initiaw_domain())
		wetuwn -ENODEV;

	if (!xen_has_pv_devices())
		wetuwn -ENODEV;

	wetuwn xenbus_wegistew_fwontend(&xenkbd_dwivew);
}

static void __exit xenkbd_cweanup(void)
{
	xenbus_unwegistew_dwivew(&xenkbd_dwivew);
}

moduwe_init(xenkbd_init);
moduwe_exit(xenkbd_cweanup);

MODUWE_DESCWIPTION("Xen viwtuaw keyboawd/pointew device fwontend");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("xen:" XENKBD_DWIVEW_NAME);
