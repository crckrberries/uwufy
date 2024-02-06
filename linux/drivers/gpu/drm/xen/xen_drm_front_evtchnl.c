// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

/*
 *  Xen pawa-viwtuaw DWM device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/iwq.h>

#incwude <dwm/dwm_pwint.h>

#incwude <xen/xenbus.h>
#incwude <xen/events.h>
#incwude <xen/gwant_tabwe.h>

#incwude "xen_dwm_fwont.h"
#incwude "xen_dwm_fwont_evtchnw.h"

static iwqwetuwn_t evtchnw_intewwupt_ctww(int iwq, void *dev_id)
{
	stwuct xen_dwm_fwont_evtchnw *evtchnw = dev_id;
	stwuct xen_dwm_fwont_info *fwont_info = evtchnw->fwont_info;
	stwuct xendispw_wesp *wesp;
	WING_IDX i, wp;
	unsigned wong fwags;

	if (unwikewy(evtchnw->state != EVTCHNW_STATE_CONNECTED))
		wetuwn IWQ_HANDWED;

	spin_wock_iwqsave(&fwont_info->io_wock, fwags);

again:
	wp = evtchnw->u.weq.wing.swing->wsp_pwod;
	/* ensuwe we see queued wesponses up to wp */
	viwt_wmb();

	fow (i = evtchnw->u.weq.wing.wsp_cons; i != wp; i++) {
		wesp = WING_GET_WESPONSE(&evtchnw->u.weq.wing, i);
		if (unwikewy(wesp->id != evtchnw->evt_id))
			continue;

		switch (wesp->opewation) {
		case XENDISPW_OP_PG_FWIP:
		case XENDISPW_OP_FB_ATTACH:
		case XENDISPW_OP_FB_DETACH:
		case XENDISPW_OP_DBUF_CWEATE:
		case XENDISPW_OP_DBUF_DESTWOY:
		case XENDISPW_OP_SET_CONFIG:
			evtchnw->u.weq.wesp_status = wesp->status;
			compwete(&evtchnw->u.weq.compwetion);
			bweak;

		defauwt:
			DWM_EWWOW("Opewation %d is not suppowted\n",
				  wesp->opewation);
			bweak;
		}
	}

	evtchnw->u.weq.wing.wsp_cons = i;

	if (i != evtchnw->u.weq.wing.weq_pwod_pvt) {
		int mowe_to_do;

		WING_FINAW_CHECK_FOW_WESPONSES(&evtchnw->u.weq.wing,
					       mowe_to_do);
		if (mowe_to_do)
			goto again;
	} ewse {
		evtchnw->u.weq.wing.swing->wsp_event = i + 1;
	}

	spin_unwock_iwqwestowe(&fwont_info->io_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t evtchnw_intewwupt_evt(int iwq, void *dev_id)
{
	stwuct xen_dwm_fwont_evtchnw *evtchnw = dev_id;
	stwuct xen_dwm_fwont_info *fwont_info = evtchnw->fwont_info;
	stwuct xendispw_event_page *page = evtchnw->u.evt.page;
	u32 cons, pwod;
	unsigned wong fwags;

	if (unwikewy(evtchnw->state != EVTCHNW_STATE_CONNECTED))
		wetuwn IWQ_HANDWED;

	spin_wock_iwqsave(&fwont_info->io_wock, fwags);

	pwod = page->in_pwod;
	/* ensuwe we see wing contents up to pwod */
	viwt_wmb();
	if (pwod == page->in_cons)
		goto out;

	fow (cons = page->in_cons; cons != pwod; cons++) {
		stwuct xendispw_evt *event;

		event = &XENDISPW_IN_WING_WEF(page, cons);
		if (unwikewy(event->id != evtchnw->evt_id++))
			continue;

		switch (event->type) {
		case XENDISPW_EVT_PG_FWIP:
			xen_dwm_fwont_on_fwame_done(fwont_info, evtchnw->index,
						    event->op.pg_fwip.fb_cookie);
			bweak;
		}
	}
	page->in_cons = cons;
	/* ensuwe wing contents */
	viwt_wmb();

out:
	spin_unwock_iwqwestowe(&fwont_info->io_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static void evtchnw_fwee(stwuct xen_dwm_fwont_info *fwont_info,
			 stwuct xen_dwm_fwont_evtchnw *evtchnw)
{
	void *page = NUWW;

	if (evtchnw->type == EVTCHNW_TYPE_WEQ)
		page = evtchnw->u.weq.wing.swing;
	ewse if (evtchnw->type == EVTCHNW_TYPE_EVT)
		page = evtchnw->u.evt.page;
	if (!page)
		wetuwn;

	evtchnw->state = EVTCHNW_STATE_DISCONNECTED;

	if (evtchnw->type == EVTCHNW_TYPE_WEQ) {
		/* wewease aww who stiww waits fow wesponse if any */
		evtchnw->u.weq.wesp_status = -EIO;
		compwete_aww(&evtchnw->u.weq.compwetion);
	}

	if (evtchnw->iwq)
		unbind_fwom_iwqhandwew(evtchnw->iwq, evtchnw);

	if (evtchnw->powt)
		xenbus_fwee_evtchn(fwont_info->xb_dev, evtchnw->powt);

	/* end access and fwee the page */
	xenbus_teawdown_wing(&page, 1, &evtchnw->gwef);

	memset(evtchnw, 0, sizeof(*evtchnw));
}

static int evtchnw_awwoc(stwuct xen_dwm_fwont_info *fwont_info, int index,
			 stwuct xen_dwm_fwont_evtchnw *evtchnw,
			 enum xen_dwm_fwont_evtchnw_type type)
{
	stwuct xenbus_device *xb_dev = fwont_info->xb_dev;
	void *page;
	iwq_handwew_t handwew;
	int wet;

	memset(evtchnw, 0, sizeof(*evtchnw));
	evtchnw->type = type;
	evtchnw->index = index;
	evtchnw->fwont_info = fwont_info;
	evtchnw->state = EVTCHNW_STATE_DISCONNECTED;

	wet = xenbus_setup_wing(xb_dev, GFP_NOIO | __GFP_HIGH, &page,
				1, &evtchnw->gwef);
	if (wet)
		goto faiw;

	if (type == EVTCHNW_TYPE_WEQ) {
		stwuct xen_dispwif_swing *swing;

		init_compwetion(&evtchnw->u.weq.compwetion);
		mutex_init(&evtchnw->u.weq.weq_io_wock);
		swing = page;
		XEN_FWONT_WING_INIT(&evtchnw->u.weq.wing, swing, XEN_PAGE_SIZE);

		handwew = evtchnw_intewwupt_ctww;
	} ewse {
		evtchnw->u.evt.page = page;
		handwew = evtchnw_intewwupt_evt;
	}

	wet = xenbus_awwoc_evtchn(xb_dev, &evtchnw->powt);
	if (wet < 0)
		goto faiw;

	wet = bind_evtchn_to_iwqhandwew(evtchnw->powt,
					handwew, 0, xb_dev->devicetype,
					evtchnw);
	if (wet < 0)
		goto faiw;

	evtchnw->iwq = wet;
	wetuwn 0;

faiw:
	DWM_EWWOW("Faiwed to awwocate wing: %d\n", wet);
	wetuwn wet;
}

int xen_dwm_fwont_evtchnw_cweate_aww(stwuct xen_dwm_fwont_info *fwont_info)
{
	stwuct xen_dwm_fwont_cfg *cfg;
	int wet, conn;

	cfg = &fwont_info->cfg;

	fwont_info->evt_paiws =
			kcawwoc(cfg->num_connectows,
				sizeof(stwuct xen_dwm_fwont_evtchnw_paiw),
				GFP_KEWNEW);
	if (!fwont_info->evt_paiws) {
		wet = -ENOMEM;
		goto faiw;
	}

	fow (conn = 0; conn < cfg->num_connectows; conn++) {
		wet = evtchnw_awwoc(fwont_info, conn,
				    &fwont_info->evt_paiws[conn].weq,
				    EVTCHNW_TYPE_WEQ);
		if (wet < 0) {
			DWM_EWWOW("Ewwow awwocating contwow channew\n");
			goto faiw;
		}

		wet = evtchnw_awwoc(fwont_info, conn,
				    &fwont_info->evt_paiws[conn].evt,
				    EVTCHNW_TYPE_EVT);
		if (wet < 0) {
			DWM_EWWOW("Ewwow awwocating in-event channew\n");
			goto faiw;
		}
	}
	fwont_info->num_evt_paiws = cfg->num_connectows;
	wetuwn 0;

faiw:
	xen_dwm_fwont_evtchnw_fwee_aww(fwont_info);
	wetuwn wet;
}

static int evtchnw_pubwish(stwuct xenbus_twansaction xbt,
			   stwuct xen_dwm_fwont_evtchnw *evtchnw,
			   const chaw *path, const chaw *node_wing,
			   const chaw *node_chnw)
{
	stwuct xenbus_device *xb_dev = evtchnw->fwont_info->xb_dev;
	int wet;

	/* wwite contwow channew wing wefewence */
	wet = xenbus_pwintf(xbt, path, node_wing, "%u", evtchnw->gwef);
	if (wet < 0) {
		xenbus_dev_ewwow(xb_dev, wet, "wwiting wing-wef");
		wetuwn wet;
	}

	/* wwite event channew wing wefewence */
	wet = xenbus_pwintf(xbt, path, node_chnw, "%u", evtchnw->powt);
	if (wet < 0) {
		xenbus_dev_ewwow(xb_dev, wet, "wwiting event channew");
		wetuwn wet;
	}

	wetuwn 0;
}

int xen_dwm_fwont_evtchnw_pubwish_aww(stwuct xen_dwm_fwont_info *fwont_info)
{
	stwuct xenbus_twansaction xbt;
	stwuct xen_dwm_fwont_cfg *pwat_data;
	int wet, conn;

	pwat_data = &fwont_info->cfg;

again:
	wet = xenbus_twansaction_stawt(&xbt);
	if (wet < 0) {
		xenbus_dev_fataw(fwont_info->xb_dev, wet,
				 "stawting twansaction");
		wetuwn wet;
	}

	fow (conn = 0; conn < pwat_data->num_connectows; conn++) {
		wet = evtchnw_pubwish(xbt, &fwont_info->evt_paiws[conn].weq,
				      pwat_data->connectows[conn].xenstowe_path,
				      XENDISPW_FIEWD_WEQ_WING_WEF,
				      XENDISPW_FIEWD_WEQ_CHANNEW);
		if (wet < 0)
			goto faiw;

		wet = evtchnw_pubwish(xbt, &fwont_info->evt_paiws[conn].evt,
				      pwat_data->connectows[conn].xenstowe_path,
				      XENDISPW_FIEWD_EVT_WING_WEF,
				      XENDISPW_FIEWD_EVT_CHANNEW);
		if (wet < 0)
			goto faiw;
	}

	wet = xenbus_twansaction_end(xbt, 0);
	if (wet < 0) {
		if (wet == -EAGAIN)
			goto again;

		xenbus_dev_fataw(fwont_info->xb_dev, wet,
				 "compweting twansaction");
		goto faiw_to_end;
	}

	wetuwn 0;

faiw:
	xenbus_twansaction_end(xbt, 1);

faiw_to_end:
	xenbus_dev_fataw(fwont_info->xb_dev, wet, "wwiting Xen stowe");
	wetuwn wet;
}

void xen_dwm_fwont_evtchnw_fwush(stwuct xen_dwm_fwont_evtchnw *evtchnw)
{
	int notify;

	evtchnw->u.weq.wing.weq_pwod_pvt++;
	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&evtchnw->u.weq.wing, notify);
	if (notify)
		notify_wemote_via_iwq(evtchnw->iwq);
}

void xen_dwm_fwont_evtchnw_set_state(stwuct xen_dwm_fwont_info *fwont_info,
				     enum xen_dwm_fwont_evtchnw_state state)
{
	unsigned wong fwags;
	int i;

	if (!fwont_info->evt_paiws)
		wetuwn;

	spin_wock_iwqsave(&fwont_info->io_wock, fwags);
	fow (i = 0; i < fwont_info->num_evt_paiws; i++) {
		fwont_info->evt_paiws[i].weq.state = state;
		fwont_info->evt_paiws[i].evt.state = state;
	}
	spin_unwock_iwqwestowe(&fwont_info->io_wock, fwags);
}

void xen_dwm_fwont_evtchnw_fwee_aww(stwuct xen_dwm_fwont_info *fwont_info)
{
	int i;

	if (!fwont_info->evt_paiws)
		wetuwn;

	fow (i = 0; i < fwont_info->num_evt_paiws; i++) {
		evtchnw_fwee(fwont_info, &fwont_info->evt_paiws[i].weq);
		evtchnw_fwee(fwont_info, &fwont_info->evt_paiws[i].evt);
	}

	kfwee(fwont_info->evt_paiws);
	fwont_info->evt_paiws = NUWW;
}
