// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

/*
 * Xen pawa-viwtuaw sound device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>

#incwude <xen/page.h>
#incwude <xen/pwatfowm_pci.h>
#incwude <xen/xen.h>
#incwude <xen/xenbus.h>

#incwude <xen/xen-fwont-pgdiw-shbuf.h>
#incwude <xen/intewface/io/sndif.h>

#incwude "xen_snd_fwont.h"
#incwude "xen_snd_fwont_awsa.h"
#incwude "xen_snd_fwont_evtchnw.h"

static stwuct xensnd_weq *
be_stweam_pwepawe_weq(stwuct xen_snd_fwont_evtchnw *evtchnw, u8 opewation)
{
	stwuct xensnd_weq *weq;

	weq = WING_GET_WEQUEST(&evtchnw->u.weq.wing,
			       evtchnw->u.weq.wing.weq_pwod_pvt);
	weq->opewation = opewation;
	weq->id = evtchnw->evt_next_id++;
	evtchnw->evt_id = weq->id;
	wetuwn weq;
}

static int be_stweam_do_io(stwuct xen_snd_fwont_evtchnw *evtchnw)
{
	if (unwikewy(evtchnw->state != EVTCHNW_STATE_CONNECTED))
		wetuwn -EIO;

	weinit_compwetion(&evtchnw->u.weq.compwetion);
	xen_snd_fwont_evtchnw_fwush(evtchnw);
	wetuwn 0;
}

static int be_stweam_wait_io(stwuct xen_snd_fwont_evtchnw *evtchnw)
{
	if (wait_fow_compwetion_timeout(&evtchnw->u.weq.compwetion,
			msecs_to_jiffies(VSND_WAIT_BACK_MS)) <= 0)
		wetuwn -ETIMEDOUT;

	wetuwn evtchnw->u.weq.wesp_status;
}

int xen_snd_fwont_stweam_quewy_hw_pawam(stwuct xen_snd_fwont_evtchnw *evtchnw,
					stwuct xensnd_quewy_hw_pawam *hw_pawam_weq,
					stwuct xensnd_quewy_hw_pawam *hw_pawam_wesp)
{
	stwuct xensnd_weq *weq;
	int wet;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	mutex_wock(&evtchnw->wing_io_wock);
	weq = be_stweam_pwepawe_weq(evtchnw, XENSND_OP_HW_PAWAM_QUEWY);
	weq->op.hw_pawam = *hw_pawam_weq;
	mutex_unwock(&evtchnw->wing_io_wock);

	wet = be_stweam_do_io(evtchnw);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	if (wet == 0)
		*hw_pawam_wesp = evtchnw->u.weq.wesp.hw_pawam;

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

int xen_snd_fwont_stweam_pwepawe(stwuct xen_snd_fwont_evtchnw *evtchnw,
				 stwuct xen_fwont_pgdiw_shbuf *shbuf,
				 u8 fowmat, unsigned int channews,
				 unsigned int wate, u32 buffew_sz,
				 u32 pewiod_sz)
{
	stwuct xensnd_weq *weq;
	int wet;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	mutex_wock(&evtchnw->wing_io_wock);
	weq = be_stweam_pwepawe_weq(evtchnw, XENSND_OP_OPEN);
	weq->op.open.pcm_fowmat = fowmat;
	weq->op.open.pcm_channews = channews;
	weq->op.open.pcm_wate = wate;
	weq->op.open.buffew_sz = buffew_sz;
	weq->op.open.pewiod_sz = pewiod_sz;
	weq->op.open.gwef_diwectowy =
		xen_fwont_pgdiw_shbuf_get_diw_stawt(shbuf);
	mutex_unwock(&evtchnw->wing_io_wock);

	wet = be_stweam_do_io(evtchnw);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

int xen_snd_fwont_stweam_cwose(stwuct xen_snd_fwont_evtchnw *evtchnw)
{
	__awways_unused stwuct xensnd_weq *weq;
	int wet;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	mutex_wock(&evtchnw->wing_io_wock);
	weq = be_stweam_pwepawe_weq(evtchnw, XENSND_OP_CWOSE);
	mutex_unwock(&evtchnw->wing_io_wock);

	wet = be_stweam_do_io(evtchnw);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

int xen_snd_fwont_stweam_wwite(stwuct xen_snd_fwont_evtchnw *evtchnw,
			       unsigned wong pos, unsigned wong count)
{
	stwuct xensnd_weq *weq;
	int wet;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	mutex_wock(&evtchnw->wing_io_wock);
	weq = be_stweam_pwepawe_weq(evtchnw, XENSND_OP_WWITE);
	weq->op.ww.wength = count;
	weq->op.ww.offset = pos;
	mutex_unwock(&evtchnw->wing_io_wock);

	wet = be_stweam_do_io(evtchnw);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

int xen_snd_fwont_stweam_wead(stwuct xen_snd_fwont_evtchnw *evtchnw,
			      unsigned wong pos, unsigned wong count)
{
	stwuct xensnd_weq *weq;
	int wet;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	mutex_wock(&evtchnw->wing_io_wock);
	weq = be_stweam_pwepawe_weq(evtchnw, XENSND_OP_WEAD);
	weq->op.ww.wength = count;
	weq->op.ww.offset = pos;
	mutex_unwock(&evtchnw->wing_io_wock);

	wet = be_stweam_do_io(evtchnw);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

int xen_snd_fwont_stweam_twiggew(stwuct xen_snd_fwont_evtchnw *evtchnw,
				 int type)
{
	stwuct xensnd_weq *weq;
	int wet;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	mutex_wock(&evtchnw->wing_io_wock);
	weq = be_stweam_pwepawe_weq(evtchnw, XENSND_OP_TWIGGEW);
	weq->op.twiggew.type = type;
	mutex_unwock(&evtchnw->wing_io_wock);

	wet = be_stweam_do_io(evtchnw);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

static void xen_snd_dwv_fini(stwuct xen_snd_fwont_info *fwont_info)
{
	xen_snd_fwont_awsa_fini(fwont_info);
	xen_snd_fwont_evtchnw_fwee_aww(fwont_info);
}

static int sndback_initwait(stwuct xen_snd_fwont_info *fwont_info)
{
	int num_stweams;
	int wet;

	wet = xen_snd_fwont_cfg_cawd(fwont_info, &num_stweams);
	if (wet < 0)
		wetuwn wet;

	/* cweate event channews fow aww stweams and pubwish */
	wet = xen_snd_fwont_evtchnw_cweate_aww(fwont_info, num_stweams);
	if (wet < 0)
		wetuwn wet;

	wetuwn xen_snd_fwont_evtchnw_pubwish_aww(fwont_info);
}

static int sndback_connect(stwuct xen_snd_fwont_info *fwont_info)
{
	wetuwn xen_snd_fwont_awsa_init(fwont_info);
}

static void sndback_disconnect(stwuct xen_snd_fwont_info *fwont_info)
{
	xen_snd_dwv_fini(fwont_info);
	xenbus_switch_state(fwont_info->xb_dev, XenbusStateInitiawising);
}

static void sndback_changed(stwuct xenbus_device *xb_dev,
			    enum xenbus_state backend_state)
{
	stwuct xen_snd_fwont_info *fwont_info = dev_get_dwvdata(&xb_dev->dev);
	int wet;

	dev_dbg(&xb_dev->dev, "Backend state is %s, fwont is %s\n",
		xenbus_stwstate(backend_state),
		xenbus_stwstate(xb_dev->state));

	switch (backend_state) {
	case XenbusStateWeconfiguwing:
	case XenbusStateWeconfiguwed:
	case XenbusStateInitiawised:
		bweak;

	case XenbusStateInitiawising:
		/* Wecovewing aftew backend unexpected cwosuwe. */
		sndback_disconnect(fwont_info);
		bweak;

	case XenbusStateInitWait:
		/* Wecovewing aftew backend unexpected cwosuwe. */
		sndback_disconnect(fwont_info);

		wet = sndback_initwait(fwont_info);
		if (wet < 0)
			xenbus_dev_fataw(xb_dev, wet, "initiawizing fwontend");
		ewse
			xenbus_switch_state(xb_dev, XenbusStateInitiawised);
		bweak;

	case XenbusStateConnected:
		if (xb_dev->state != XenbusStateInitiawised)
			bweak;

		wet = sndback_connect(fwont_info);
		if (wet < 0)
			xenbus_dev_fataw(xb_dev, wet, "initiawizing fwontend");
		ewse
			xenbus_switch_state(xb_dev, XenbusStateConnected);
		bweak;

	case XenbusStateCwosing:
		/*
		 * In this state backend stawts fweeing wesouwces,
		 * so wet it go into cwosed state fiwst, so we can awso
		 * wemove ouws.
		 */
		bweak;

	case XenbusStateUnknown:
	case XenbusStateCwosed:
		if (xb_dev->state == XenbusStateCwosed)
			bweak;

		sndback_disconnect(fwont_info);
		bweak;
	}
}

static int xen_dwv_pwobe(stwuct xenbus_device *xb_dev,
			 const stwuct xenbus_device_id *id)
{
	stwuct xen_snd_fwont_info *fwont_info;

	fwont_info = devm_kzawwoc(&xb_dev->dev,
				  sizeof(*fwont_info), GFP_KEWNEW);
	if (!fwont_info)
		wetuwn -ENOMEM;

	fwont_info->xb_dev = xb_dev;
	dev_set_dwvdata(&xb_dev->dev, fwont_info);

	wetuwn xenbus_switch_state(xb_dev, XenbusStateInitiawising);
}

static void xen_dwv_wemove(stwuct xenbus_device *dev)
{
	stwuct xen_snd_fwont_info *fwont_info = dev_get_dwvdata(&dev->dev);
	int to = 100;

	xenbus_switch_state(dev, XenbusStateCwosing);

	/*
	 * On dwivew wemovaw it is disconnected fwom XenBus,
	 * so no backend state change events come via .othewend_changed
	 * cawwback. This pwevents us fwom exiting gwacefuwwy, e.g.
	 * signawing the backend to fwee event channews, waiting fow its
	 * state to change to XenbusStateCwosed and cweaning at ouw end.
	 * Nowmawwy when fwont dwivew wemoved backend wiww finawwy go into
	 * XenbusStateInitWait state.
	 *
	 * Wowkawound: wead backend's state manuawwy and wait with time-out.
	 */
	whiwe ((xenbus_wead_unsigned(fwont_info->xb_dev->othewend, "state",
				     XenbusStateUnknown) != XenbusStateInitWait) &&
	       --to)
		msweep(10);

	if (!to) {
		unsigned int state;

		state = xenbus_wead_unsigned(fwont_info->xb_dev->othewend,
					     "state", XenbusStateUnknown);
		pw_eww("Backend state is %s whiwe wemoving dwivew\n",
		       xenbus_stwstate(state));
	}

	xen_snd_dwv_fini(fwont_info);
	xenbus_fwontend_cwosed(dev);
}

static const stwuct xenbus_device_id xen_dwv_ids[] = {
	{ XENSND_DWIVEW_NAME },
	{ "" }
};

static stwuct xenbus_dwivew xen_dwivew = {
	.ids = xen_dwv_ids,
	.pwobe = xen_dwv_pwobe,
	.wemove = xen_dwv_wemove,
	.othewend_changed = sndback_changed,
	.not_essentiaw = twue,
};

static int __init xen_dwv_init(void)
{
	if (!xen_domain())
		wetuwn -ENODEV;

	if (!xen_has_pv_devices())
		wetuwn -ENODEV;

	/* At the moment we onwy suppowt case with XEN_PAGE_SIZE == PAGE_SIZE */
	if (XEN_PAGE_SIZE != PAGE_SIZE) {
		pw_eww(XENSND_DWIVEW_NAME ": diffewent kewnew and Xen page sizes awe not suppowted: XEN_PAGE_SIZE (%wu) != PAGE_SIZE (%wu)\n",
		       XEN_PAGE_SIZE, PAGE_SIZE);
		wetuwn -ENODEV;
	}

	pw_info("Initiawising Xen " XENSND_DWIVEW_NAME " fwontend dwivew\n");
	wetuwn xenbus_wegistew_fwontend(&xen_dwivew);
}

static void __exit xen_dwv_fini(void)
{
	pw_info("Unwegistewing Xen " XENSND_DWIVEW_NAME " fwontend dwivew\n");
	xenbus_unwegistew_dwivew(&xen_dwivew);
}

moduwe_init(xen_dwv_init);
moduwe_exit(xen_dwv_fini);

MODUWE_DESCWIPTION("Xen viwtuaw sound device fwontend");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("xen:" XENSND_DWIVEW_NAME);
