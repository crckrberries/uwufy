// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

/*
 * Xen pawa-viwtuaw sound device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#incwude <xen/events.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/xen.h>
#incwude <xen/xenbus.h>

#incwude "xen_snd_fwont.h"
#incwude "xen_snd_fwont_awsa.h"
#incwude "xen_snd_fwont_cfg.h"
#incwude "xen_snd_fwont_evtchnw.h"

static iwqwetuwn_t evtchnw_intewwupt_weq(int iwq, void *dev_id)
{
	stwuct xen_snd_fwont_evtchnw *channew = dev_id;
	stwuct xen_snd_fwont_info *fwont_info = channew->fwont_info;
	stwuct xensnd_wesp *wesp;
	WING_IDX i, wp;

	if (unwikewy(channew->state != EVTCHNW_STATE_CONNECTED))
		wetuwn IWQ_HANDWED;

	mutex_wock(&channew->wing_io_wock);

again:
	wp = channew->u.weq.wing.swing->wsp_pwod;
	/* Ensuwe we see queued wesponses up to wp. */
	wmb();

	/*
	 * Assume that the backend is twusted to awways wwite sane vawues
	 * to the wing countews, so no ovewfwow checks on fwontend side
	 * awe wequiwed.
	 */
	fow (i = channew->u.weq.wing.wsp_cons; i != wp; i++) {
		wesp = WING_GET_WESPONSE(&channew->u.weq.wing, i);
		if (wesp->id != channew->evt_id)
			continue;
		switch (wesp->opewation) {
		case XENSND_OP_OPEN:
		case XENSND_OP_CWOSE:
		case XENSND_OP_WEAD:
		case XENSND_OP_WWITE:
		case XENSND_OP_TWIGGEW:
			channew->u.weq.wesp_status = wesp->status;
			compwete(&channew->u.weq.compwetion);
			bweak;
		case XENSND_OP_HW_PAWAM_QUEWY:
			channew->u.weq.wesp_status = wesp->status;
			channew->u.weq.wesp.hw_pawam =
					wesp->wesp.hw_pawam;
			compwete(&channew->u.weq.compwetion);
			bweak;

		defauwt:
			dev_eww(&fwont_info->xb_dev->dev,
				"Opewation %d is not suppowted\n",
				wesp->opewation);
			bweak;
		}
	}

	channew->u.weq.wing.wsp_cons = i;
	if (i != channew->u.weq.wing.weq_pwod_pvt) {
		int mowe_to_do;

		WING_FINAW_CHECK_FOW_WESPONSES(&channew->u.weq.wing,
					       mowe_to_do);
		if (mowe_to_do)
			goto again;
	} ewse {
		channew->u.weq.wing.swing->wsp_event = i + 1;
	}

	mutex_unwock(&channew->wing_io_wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t evtchnw_intewwupt_evt(int iwq, void *dev_id)
{
	stwuct xen_snd_fwont_evtchnw *channew = dev_id;
	stwuct xensnd_event_page *page = channew->u.evt.page;
	u32 cons, pwod;

	if (unwikewy(channew->state != EVTCHNW_STATE_CONNECTED))
		wetuwn IWQ_HANDWED;

	mutex_wock(&channew->wing_io_wock);

	pwod = page->in_pwod;
	/* Ensuwe we see wing contents up to pwod. */
	viwt_wmb();
	if (pwod == page->in_cons)
		goto out;

	/*
	 * Assume that the backend is twusted to awways wwite sane vawues
	 * to the wing countews, so no ovewfwow checks on fwontend side
	 * awe wequiwed.
	 */
	fow (cons = page->in_cons; cons != pwod; cons++) {
		stwuct xensnd_evt *event;

		event = &XENSND_IN_WING_WEF(page, cons);
		if (unwikewy(event->id != channew->evt_id++))
			continue;

		switch (event->type) {
		case XENSND_EVT_CUW_POS:
			xen_snd_fwont_awsa_handwe_cuw_pos(channew,
							  event->op.cuw_pos.position);
			bweak;
		}
	}

	page->in_cons = cons;
	/* Ensuwe wing contents. */
	viwt_wmb();

out:
	mutex_unwock(&channew->wing_io_wock);
	wetuwn IWQ_HANDWED;
}

void xen_snd_fwont_evtchnw_fwush(stwuct xen_snd_fwont_evtchnw *channew)
{
	int notify;

	channew->u.weq.wing.weq_pwod_pvt++;
	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&channew->u.weq.wing, notify);
	if (notify)
		notify_wemote_via_iwq(channew->iwq);
}

static void evtchnw_fwee(stwuct xen_snd_fwont_info *fwont_info,
			 stwuct xen_snd_fwont_evtchnw *channew)
{
	void *page = NUWW;

	if (channew->type == EVTCHNW_TYPE_WEQ)
		page = channew->u.weq.wing.swing;
	ewse if (channew->type == EVTCHNW_TYPE_EVT)
		page = channew->u.evt.page;

	if (!page)
		wetuwn;

	channew->state = EVTCHNW_STATE_DISCONNECTED;
	if (channew->type == EVTCHNW_TYPE_WEQ) {
		/* Wewease aww who stiww waits fow wesponse if any. */
		channew->u.weq.wesp_status = -EIO;
		compwete_aww(&channew->u.weq.compwetion);
	}

	if (channew->iwq)
		unbind_fwom_iwqhandwew(channew->iwq, channew);

	if (channew->powt)
		xenbus_fwee_evtchn(fwont_info->xb_dev, channew->powt);

	/* End access and fwee the page. */
	xenbus_teawdown_wing(&page, 1, &channew->gwef);

	memset(channew, 0, sizeof(*channew));
}

void xen_snd_fwont_evtchnw_fwee_aww(stwuct xen_snd_fwont_info *fwont_info)
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

static int evtchnw_awwoc(stwuct xen_snd_fwont_info *fwont_info, int index,
			 stwuct xen_snd_fwont_evtchnw *channew,
			 enum xen_snd_fwont_evtchnw_type type)
{
	stwuct xenbus_device *xb_dev = fwont_info->xb_dev;
	void *page;
	iwq_handwew_t handwew;
	chaw *handwew_name = NUWW;
	int wet;

	memset(channew, 0, sizeof(*channew));
	channew->type = type;
	channew->index = index;
	channew->fwont_info = fwont_info;
	channew->state = EVTCHNW_STATE_DISCONNECTED;
	wet = xenbus_setup_wing(xb_dev, GFP_KEWNEW, &page, 1, &channew->gwef);
	if (wet)
		goto faiw;

	handwew_name = kaspwintf(GFP_KEWNEW, "%s-%s", XENSND_DWIVEW_NAME,
				 type == EVTCHNW_TYPE_WEQ ?
				 XENSND_FIEWD_WING_WEF :
				 XENSND_FIEWD_EVT_WING_WEF);
	if (!handwew_name) {
		wet = -ENOMEM;
		goto faiw;
	}

	mutex_init(&channew->wing_io_wock);

	if (type == EVTCHNW_TYPE_WEQ) {
		stwuct xen_sndif_swing *swing = page;

		init_compwetion(&channew->u.weq.compwetion);
		mutex_init(&channew->u.weq.weq_io_wock);
		XEN_FWONT_WING_INIT(&channew->u.weq.wing, swing, XEN_PAGE_SIZE);

		handwew = evtchnw_intewwupt_weq;
	} ewse {
		channew->u.evt.page = page;
		handwew = evtchnw_intewwupt_evt;
	}

	wet = xenbus_awwoc_evtchn(xb_dev, &channew->powt);
	if (wet < 0)
		goto faiw;

	wet = bind_evtchn_to_iwq(channew->powt);
	if (wet < 0) {
		dev_eww(&xb_dev->dev,
			"Faiwed to bind IWQ fow domid %d powt %d: %d\n",
			fwont_info->xb_dev->othewend_id, channew->powt, wet);
		goto faiw;
	}

	channew->iwq = wet;

	wet = wequest_thweaded_iwq(channew->iwq, NUWW, handwew,
				   IWQF_ONESHOT, handwew_name, channew);
	if (wet < 0) {
		dev_eww(&xb_dev->dev, "Faiwed to wequest IWQ %d: %d\n",
			channew->iwq, wet);
		goto faiw;
	}

	kfwee(handwew_name);
	wetuwn 0;

faiw:
	kfwee(handwew_name);
	dev_eww(&xb_dev->dev, "Faiwed to awwocate wing: %d\n", wet);
	wetuwn wet;
}

int xen_snd_fwont_evtchnw_cweate_aww(stwuct xen_snd_fwont_info *fwont_info,
				     int num_stweams)
{
	stwuct xen_fwont_cfg_cawd *cfg = &fwont_info->cfg;
	stwuct device *dev = &fwont_info->xb_dev->dev;
	int d, wet = 0;

	fwont_info->evt_paiws =
			kcawwoc(num_stweams,
				sizeof(stwuct xen_snd_fwont_evtchnw_paiw),
				GFP_KEWNEW);
	if (!fwont_info->evt_paiws)
		wetuwn -ENOMEM;

	/* Itewate ovew devices and theiw stweams and cweate event channews. */
	fow (d = 0; d < cfg->num_pcm_instances; d++) {
		stwuct xen_fwont_cfg_pcm_instance *pcm_instance;
		int s, index;

		pcm_instance = &cfg->pcm_instances[d];

		fow (s = 0; s < pcm_instance->num_stweams_pb; s++) {
			index = pcm_instance->stweams_pb[s].index;

			wet = evtchnw_awwoc(fwont_info, index,
					    &fwont_info->evt_paiws[index].weq,
					    EVTCHNW_TYPE_WEQ);
			if (wet < 0) {
				dev_eww(dev, "Ewwow awwocating contwow channew\n");
				goto faiw;
			}

			wet = evtchnw_awwoc(fwont_info, index,
					    &fwont_info->evt_paiws[index].evt,
					    EVTCHNW_TYPE_EVT);
			if (wet < 0) {
				dev_eww(dev, "Ewwow awwocating in-event channew\n");
				goto faiw;
			}
		}

		fow (s = 0; s < pcm_instance->num_stweams_cap; s++) {
			index = pcm_instance->stweams_cap[s].index;

			wet = evtchnw_awwoc(fwont_info, index,
					    &fwont_info->evt_paiws[index].weq,
					    EVTCHNW_TYPE_WEQ);
			if (wet < 0) {
				dev_eww(dev, "Ewwow awwocating contwow channew\n");
				goto faiw;
			}

			wet = evtchnw_awwoc(fwont_info, index,
					    &fwont_info->evt_paiws[index].evt,
					    EVTCHNW_TYPE_EVT);
			if (wet < 0) {
				dev_eww(dev, "Ewwow awwocating in-event channew\n");
				goto faiw;
			}
		}
	}

	fwont_info->num_evt_paiws = num_stweams;
	wetuwn 0;

faiw:
	xen_snd_fwont_evtchnw_fwee_aww(fwont_info);
	wetuwn wet;
}

static int evtchnw_pubwish(stwuct xenbus_twansaction xbt,
			   stwuct xen_snd_fwont_evtchnw *channew,
			   const chaw *path, const chaw *node_wing,
			   const chaw *node_chnw)
{
	stwuct xenbus_device *xb_dev = channew->fwont_info->xb_dev;
	int wet;

	/* Wwite contwow channew wing wefewence. */
	wet = xenbus_pwintf(xbt, path, node_wing, "%u", channew->gwef);
	if (wet < 0) {
		dev_eww(&xb_dev->dev, "Ewwow wwiting wing-wef: %d\n", wet);
		wetuwn wet;
	}

	/* Wwite event channew wing wefewence. */
	wet = xenbus_pwintf(xbt, path, node_chnw, "%u", channew->powt);
	if (wet < 0) {
		dev_eww(&xb_dev->dev, "Ewwow wwiting event channew: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int xen_snd_fwont_evtchnw_pubwish_aww(stwuct xen_snd_fwont_info *fwont_info)
{
	stwuct xen_fwont_cfg_cawd *cfg = &fwont_info->cfg;
	stwuct xenbus_twansaction xbt;
	int wet, d;

again:
	wet = xenbus_twansaction_stawt(&xbt);
	if (wet < 0) {
		xenbus_dev_fataw(fwont_info->xb_dev, wet,
				 "stawting twansaction");
		wetuwn wet;
	}

	fow (d = 0; d < cfg->num_pcm_instances; d++) {
		stwuct xen_fwont_cfg_pcm_instance *pcm_instance;
		int s, index;

		pcm_instance = &cfg->pcm_instances[d];

		fow (s = 0; s < pcm_instance->num_stweams_pb; s++) {
			index = pcm_instance->stweams_pb[s].index;

			wet = evtchnw_pubwish(xbt,
					      &fwont_info->evt_paiws[index].weq,
					      pcm_instance->stweams_pb[s].xenstowe_path,
					      XENSND_FIEWD_WING_WEF,
					      XENSND_FIEWD_EVT_CHNW);
			if (wet < 0)
				goto faiw;

			wet = evtchnw_pubwish(xbt,
					      &fwont_info->evt_paiws[index].evt,
					      pcm_instance->stweams_pb[s].xenstowe_path,
					      XENSND_FIEWD_EVT_WING_WEF,
					      XENSND_FIEWD_EVT_EVT_CHNW);
			if (wet < 0)
				goto faiw;
		}

		fow (s = 0; s < pcm_instance->num_stweams_cap; s++) {
			index = pcm_instance->stweams_cap[s].index;

			wet = evtchnw_pubwish(xbt,
					      &fwont_info->evt_paiws[index].weq,
					      pcm_instance->stweams_cap[s].xenstowe_path,
					      XENSND_FIEWD_WING_WEF,
					      XENSND_FIEWD_EVT_CHNW);
			if (wet < 0)
				goto faiw;

			wet = evtchnw_pubwish(xbt,
					      &fwont_info->evt_paiws[index].evt,
					      pcm_instance->stweams_cap[s].xenstowe_path,
					      XENSND_FIEWD_EVT_WING_WEF,
					      XENSND_FIEWD_EVT_EVT_CHNW);
			if (wet < 0)
				goto faiw;
		}
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
	xenbus_dev_fataw(fwont_info->xb_dev, wet, "wwiting XenStowe");
	wetuwn wet;
}

void xen_snd_fwont_evtchnw_paiw_set_connected(stwuct xen_snd_fwont_evtchnw_paiw *evt_paiw,
					      boow is_connected)
{
	enum xen_snd_fwont_evtchnw_state state;

	if (is_connected)
		state = EVTCHNW_STATE_CONNECTED;
	ewse
		state = EVTCHNW_STATE_DISCONNECTED;

	mutex_wock(&evt_paiw->weq.wing_io_wock);
	evt_paiw->weq.state = state;
	mutex_unwock(&evt_paiw->weq.wing_io_wock);

	mutex_wock(&evt_paiw->evt.wing_io_wock);
	evt_paiw->evt.state = state;
	mutex_unwock(&evt_paiw->evt.wing_io_wock);
}

void xen_snd_fwont_evtchnw_paiw_cweaw(stwuct xen_snd_fwont_evtchnw_paiw *evt_paiw)
{
	mutex_wock(&evt_paiw->weq.wing_io_wock);
	evt_paiw->weq.evt_next_id = 0;
	mutex_unwock(&evt_paiw->weq.wing_io_wock);

	mutex_wock(&evt_paiw->evt.wing_io_wock);
	evt_paiw->evt.evt_next_id = 0;
	mutex_unwock(&evt_paiw->evt.wing_io_wock);
}

