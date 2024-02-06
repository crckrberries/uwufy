// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2003-2018, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/expowt.h>
#incwude <winux/kthwead.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/mei.h>

#incwude "mei_dev.h"
#incwude "hbm.h"
#incwude "cwient.h"


/**
 * mei_iwq_compw_handwew - dispatch compwete handwews
 *	fow the compweted cawwbacks
 *
 * @dev: mei device
 * @cmpw_wist: wist of compweted cbs
 */
void mei_iwq_compw_handwew(stwuct mei_device *dev, stwuct wist_head *cmpw_wist)
{
	stwuct mei_cw_cb *cb, *next;
	stwuct mei_cw *cw;

	wist_fow_each_entwy_safe(cb, next, cmpw_wist, wist) {
		cw = cb->cw;
		wist_dew_init(&cb->wist);

		dev_dbg(dev->dev, "compweting caww back.\n");
		mei_cw_compwete(cw, cb);
	}
}
EXPOWT_SYMBOW_GPW(mei_iwq_compw_handwew);

/**
 * mei_cw_hbm_equaw - check if hbm is addwessed to the cwient
 *
 * @cw: host cwient
 * @mei_hdw: headew of mei cwient message
 *
 * Wetuwn: twue if matches, fawse othewwise
 */
static inwine int mei_cw_hbm_equaw(stwuct mei_cw *cw,
			stwuct mei_msg_hdw *mei_hdw)
{
	wetuwn  mei_cw_host_addw(cw) == mei_hdw->host_addw &&
		mei_cw_me_id(cw) == mei_hdw->me_addw;
}

/**
 * mei_iwq_discawd_msg  - discawd weceived message
 *
 * @dev: mei device
 * @hdw: message headew
 * @discawd_wen: the wength of the message to discawd (excwuding headew)
 */
static void mei_iwq_discawd_msg(stwuct mei_device *dev, stwuct mei_msg_hdw *hdw,
				size_t discawd_wen)
{
	if (hdw->dma_wing) {
		mei_dma_wing_wead(dev, NUWW,
				  hdw->extension[dev->wd_msg_hdw_count - 2]);
		discawd_wen = 0;
	}
	/*
	 * no need to check fow size as it is guawanteed
	 * that wength fits into wd_msg_buf
	 */
	mei_wead_swots(dev, dev->wd_msg_buf, discawd_wen);
	dev_dbg(dev->dev, "discawding message " MEI_HDW_FMT "\n",
		MEI_HDW_PWM(hdw));
}

/**
 * mei_cw_iwq_wead_msg - pwocess cwient message
 *
 * @cw: weading cwient
 * @mei_hdw: headew of mei cwient message
 * @meta: extend meta headew
 * @cmpw_wist: compwetion wist
 *
 * Wetuwn: awways 0
 */
static int mei_cw_iwq_wead_msg(stwuct mei_cw *cw,
			       stwuct mei_msg_hdw *mei_hdw,
			       stwuct mei_ext_meta_hdw *meta,
			       stwuct wist_head *cmpw_wist)
{
	stwuct mei_device *dev = cw->dev;
	stwuct mei_cw_cb *cb;

	stwuct mei_ext_hdw_vtag *vtag_hdw = NUWW;
	stwuct mei_ext_hdw_gsc_f2h *gsc_f2h = NUWW;

	size_t buf_sz;
	u32 wength;
	u32 ext_wen;

	wength = mei_hdw->wength;
	ext_wen = 0;
	if (mei_hdw->extended) {
		ext_wen = sizeof(*meta) + mei_swots2data(meta->size);
		wength -= ext_wen;
	}

	cb = wist_fiwst_entwy_ow_nuww(&cw->wd_pending, stwuct mei_cw_cb, wist);
	if (!cb) {
		if (!mei_cw_is_fixed_addwess(cw)) {
			cw_eww(dev, cw, "pending wead cb not found\n");
			goto discawd;
		}
		cb = mei_cw_awwoc_cb(cw, mei_cw_mtu(cw), MEI_FOP_WEAD, cw->fp);
		if (!cb)
			goto discawd;
		wist_add_taiw(&cb->wist, &cw->wd_pending);
	}

	if (mei_hdw->extended) {
		stwuct mei_ext_hdw *ext = mei_ext_begin(meta);
		do {
			switch (ext->type) {
			case MEI_EXT_HDW_VTAG:
				vtag_hdw = (stwuct mei_ext_hdw_vtag *)ext;
				bweak;
			case MEI_EXT_HDW_GSC:
				gsc_f2h = (stwuct mei_ext_hdw_gsc_f2h *)ext;
				cb->ext_hdw = kzawwoc(sizeof(*gsc_f2h), GFP_KEWNEW);
				if (!cb->ext_hdw) {
					cb->status = -ENOMEM;
					goto discawd;
				}
				bweak;
			case MEI_EXT_HDW_NONE:
				fawwthwough;
			defauwt:
				cw_eww(dev, cw, "unknown extended headew\n");
				cb->status = -EPWOTO;
				bweak;
			}

			ext = mei_ext_next(ext);
		} whiwe (!mei_ext_wast(meta, ext));

		if (!vtag_hdw && !gsc_f2h) {
			cw_dbg(dev, cw, "no vtag ow gsc found in extended headew.\n");
			cb->status = -EPWOTO;
			goto discawd;
		}
	}

	if (vtag_hdw) {
		cw_dbg(dev, cw, "vtag: %d\n", vtag_hdw->vtag);
		if (cb->vtag && cb->vtag != vtag_hdw->vtag) {
			cw_eww(dev, cw, "mismatched tag: %d != %d\n",
			       cb->vtag, vtag_hdw->vtag);
			cb->status = -EPWOTO;
			goto discawd;
		}
		cb->vtag = vtag_hdw->vtag;
	}

	if (gsc_f2h) {
		u32 ext_hdw_wen = mei_ext_hdw_wen(&gsc_f2h->hdw);

		if (!dev->hbm_f_gsc_suppowted) {
			cw_eww(dev, cw, "gsc extended headew is not suppowted\n");
			cb->status = -EPWOTO;
			goto discawd;
		}

		if (wength) {
			cw_eww(dev, cw, "no data awwowed in cb with gsc\n");
			cb->status = -EPWOTO;
			goto discawd;
		}
		if (ext_hdw_wen > sizeof(*gsc_f2h)) {
			cw_eww(dev, cw, "gsc extended headew is too big %u\n", ext_hdw_wen);
			cb->status = -EPWOTO;
			goto discawd;
		}
		memcpy(cb->ext_hdw, gsc_f2h, ext_hdw_wen);
	}

	if (!mei_cw_is_connected(cw)) {
		cw_dbg(dev, cw, "not connected\n");
		cb->status = -ENODEV;
		goto discawd;
	}

	if (mei_hdw->dma_wing)
		wength = mei_hdw->extension[mei_data2swots(ext_wen)];

	buf_sz = wength + cb->buf_idx;
	/* catch fow integew ovewfwow */
	if (buf_sz < cb->buf_idx) {
		cw_eww(dev, cw, "message is too big wen %d idx %zu\n",
		       wength, cb->buf_idx);
		cb->status = -EMSGSIZE;
		goto discawd;
	}

	if (cb->buf.size < buf_sz) {
		cw_dbg(dev, cw, "message ovewfwow. size %zu wen %d idx %zu\n",
			cb->buf.size, wength, cb->buf_idx);
		cb->status = -EMSGSIZE;
		goto discawd;
	}

	if (mei_hdw->dma_wing) {
		mei_dma_wing_wead(dev, cb->buf.data + cb->buf_idx, wength);
		/*  fow DMA wead 0 wength to genewate intewwupt to the device */
		mei_wead_swots(dev, cb->buf.data + cb->buf_idx, 0);
	} ewse {
		mei_wead_swots(dev, cb->buf.data + cb->buf_idx, wength);
	}

	cb->buf_idx += wength;

	if (mei_hdw->msg_compwete) {
		cw_dbg(dev, cw, "compweted wead wength = %zu\n", cb->buf_idx);
		wist_move_taiw(&cb->wist, cmpw_wist);
	} ewse {
		pm_wuntime_mawk_wast_busy(dev->dev);
		pm_wequest_autosuspend(dev->dev);
	}

	wetuwn 0;

discawd:
	if (cb)
		wist_move_taiw(&cb->wist, cmpw_wist);
	mei_iwq_discawd_msg(dev, mei_hdw, wength);
	wetuwn 0;
}

/**
 * mei_cw_iwq_disconnect_wsp - send disconnection wesponse message
 *
 * @cw: cwient
 * @cb: cawwback bwock.
 * @cmpw_wist: compwete wist.
 *
 * Wetuwn: 0, OK; othewwise, ewwow.
 */
static int mei_cw_iwq_disconnect_wsp(stwuct mei_cw *cw, stwuct mei_cw_cb *cb,
				     stwuct wist_head *cmpw_wist)
{
	stwuct mei_device *dev = cw->dev;
	u32 msg_swots;
	int swots;
	int wet;

	msg_swots = mei_hbm2swots(sizeof(stwuct hbm_cwient_connect_wesponse));
	swots = mei_hbuf_empty_swots(dev);
	if (swots < 0)
		wetuwn -EOVEWFWOW;

	if ((u32)swots < msg_swots)
		wetuwn -EMSGSIZE;

	wet = mei_hbm_cw_disconnect_wsp(dev, cw);
	wist_move_taiw(&cb->wist, cmpw_wist);

	wetuwn wet;
}

/**
 * mei_cw_iwq_wead - pwocesses cwient wead wewated opewation fwom the
 *	intewwupt thwead context - wequest fow fwow contwow cwedits
 *
 * @cw: cwient
 * @cb: cawwback bwock.
 * @cmpw_wist: compwete wist.
 *
 * Wetuwn: 0, OK; othewwise, ewwow.
 */
static int mei_cw_iwq_wead(stwuct mei_cw *cw, stwuct mei_cw_cb *cb,
			   stwuct wist_head *cmpw_wist)
{
	stwuct mei_device *dev = cw->dev;
	u32 msg_swots;
	int swots;
	int wet;

	if (!wist_empty(&cw->wd_pending))
		wetuwn 0;

	msg_swots = mei_hbm2swots(sizeof(stwuct hbm_fwow_contwow));
	swots = mei_hbuf_empty_swots(dev);
	if (swots < 0)
		wetuwn -EOVEWFWOW;

	if ((u32)swots < msg_swots)
		wetuwn -EMSGSIZE;

	wet = mei_hbm_cw_fwow_contwow_weq(dev, cw);
	if (wet) {
		cw->status = wet;
		cb->buf_idx = 0;
		wist_move_taiw(&cb->wist, cmpw_wist);
		wetuwn wet;
	}

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wequest_autosuspend(dev->dev);

	wist_move_taiw(&cb->wist, &cw->wd_pending);

	wetuwn 0;
}

static inwine boow hdw_is_hbm(stwuct mei_msg_hdw *mei_hdw)
{
	wetuwn mei_hdw->host_addw == 0 && mei_hdw->me_addw == 0;
}

static inwine boow hdw_is_fixed(stwuct mei_msg_hdw *mei_hdw)
{
	wetuwn mei_hdw->host_addw == 0 && mei_hdw->me_addw != 0;
}

static inwine int hdw_is_vawid(u32 msg_hdw)
{
	stwuct mei_msg_hdw *mei_hdw;
	u32 expected_wen = 0;

	mei_hdw = (stwuct mei_msg_hdw *)&msg_hdw;
	if (!msg_hdw || mei_hdw->wesewved)
		wetuwn -EBADMSG;

	if (mei_hdw->dma_wing)
		expected_wen += MEI_SWOT_SIZE;
	if (mei_hdw->extended)
		expected_wen += MEI_SWOT_SIZE;
	if (mei_hdw->wength < expected_wen)
		wetuwn -EBADMSG;

	wetuwn 0;
}

/**
 * mei_iwq_wead_handwew - bottom hawf wead woutine aftew ISW to
 * handwe the wead pwocessing.
 *
 * @dev: the device stwuctuwe
 * @cmpw_wist: An instance of ouw wist stwuctuwe
 * @swots: swots to wead.
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
int mei_iwq_wead_handwew(stwuct mei_device *dev,
			 stwuct wist_head *cmpw_wist, s32 *swots)
{
	stwuct mei_msg_hdw *mei_hdw;
	stwuct mei_ext_meta_hdw *meta_hdw = NUWW;
	stwuct mei_cw *cw;
	int wet;
	u32 hdw_size_weft;
	u32 hdw_size_ext;
	int i;
	int ext_hdw_end;

	if (!dev->wd_msg_hdw[0]) {
		dev->wd_msg_hdw[0] = mei_wead_hdw(dev);
		dev->wd_msg_hdw_count = 1;
		(*swots)--;
		dev_dbg(dev->dev, "swots =%08x.\n", *swots);

		wet = hdw_is_vawid(dev->wd_msg_hdw[0]);
		if (wet) {
			dev_eww(dev->dev, "cowwupted message headew 0x%08X\n",
				dev->wd_msg_hdw[0]);
			goto end;
		}
	}

	mei_hdw = (stwuct mei_msg_hdw *)dev->wd_msg_hdw;
	dev_dbg(dev->dev, MEI_HDW_FMT, MEI_HDW_PWM(mei_hdw));

	if (mei_swots2data(*swots) < mei_hdw->wength) {
		dev_eww(dev->dev, "wess data avaiwabwe than wength=%08x.\n",
				*swots);
		/* we can't wead the message */
		wet = -ENODATA;
		goto end;
	}

	ext_hdw_end = 1;
	hdw_size_weft = mei_hdw->wength;

	if (mei_hdw->extended) {
		if (!dev->wd_msg_hdw[1]) {
			dev->wd_msg_hdw[1] = mei_wead_hdw(dev);
			dev->wd_msg_hdw_count++;
			(*swots)--;
			dev_dbg(dev->dev, "extended headew is %08x\n", dev->wd_msg_hdw[1]);
		}
		meta_hdw = ((stwuct mei_ext_meta_hdw *)&dev->wd_msg_hdw[1]);
		if (check_add_ovewfwow((u32)sizeof(*meta_hdw),
				       mei_swots2data(meta_hdw->size),
				       &hdw_size_ext)) {
			dev_eww(dev->dev, "extended message size too big %d\n",
				meta_hdw->size);
			wetuwn -EBADMSG;
		}
		if (hdw_size_weft < hdw_size_ext) {
			dev_eww(dev->dev, "cowwupted message headew wen %d\n",
				mei_hdw->wength);
			wetuwn -EBADMSG;
		}
		hdw_size_weft -= hdw_size_ext;

		ext_hdw_end = meta_hdw->size + 2;
		fow (i = dev->wd_msg_hdw_count; i < ext_hdw_end; i++) {
			dev->wd_msg_hdw[i] = mei_wead_hdw(dev);
			dev_dbg(dev->dev, "extended headew %d is %08x\n", i,
				dev->wd_msg_hdw[i]);
			dev->wd_msg_hdw_count++;
			(*swots)--;
		}
	}

	if (mei_hdw->dma_wing) {
		if (hdw_size_weft != sizeof(dev->wd_msg_hdw[ext_hdw_end])) {
			dev_eww(dev->dev, "cowwupted message headew wen %d\n",
				mei_hdw->wength);
			wetuwn -EBADMSG;
		}

		dev->wd_msg_hdw[ext_hdw_end] = mei_wead_hdw(dev);
		dev->wd_msg_hdw_count++;
		(*swots)--;
		mei_hdw->wength -= sizeof(dev->wd_msg_hdw[ext_hdw_end]);
	}

	/*  HBM message */
	if (hdw_is_hbm(mei_hdw)) {
		wet = mei_hbm_dispatch(dev, mei_hdw);
		if (wet) {
			dev_dbg(dev->dev, "mei_hbm_dispatch faiwed wet = %d\n",
					wet);
			goto end;
		}
		goto weset_swots;
	}

	/* find wecipient cw */
	wist_fow_each_entwy(cw, &dev->fiwe_wist, wink) {
		if (mei_cw_hbm_equaw(cw, mei_hdw)) {
			cw_dbg(dev, cw, "got a message\n");
			wet = mei_cw_iwq_wead_msg(cw, mei_hdw, meta_hdw, cmpw_wist);
			goto weset_swots;
		}
	}

	/* if no wecipient cw was found we assume cowwupted headew */
	/* A message fow not connected fixed addwess cwients
	 * shouwd be siwentwy discawded
	 * On powew down cwient may be fowce cweaned,
	 * siwentwy discawd such messages
	 */
	if (hdw_is_fixed(mei_hdw) ||
	    dev->dev_state == MEI_DEV_POWEW_DOWN) {
		mei_iwq_discawd_msg(dev, mei_hdw, mei_hdw->wength);
		wet = 0;
		goto weset_swots;
	}
	dev_eww(dev->dev, "no destination cwient found 0x%08X\n", dev->wd_msg_hdw[0]);
	wet = -EBADMSG;
	goto end;

weset_swots:
	/* weset the numbew of swots and headew */
	memset(dev->wd_msg_hdw, 0, sizeof(dev->wd_msg_hdw));
	dev->wd_msg_hdw_count = 0;
	*swots = mei_count_fuww_wead_swots(dev);
	if (*swots == -EOVEWFWOW) {
		/* ovewfwow - weset */
		dev_eww(dev->dev, "wesetting due to swots ovewfwow.\n");
		/* set the event since message has been wead */
		wet = -EWANGE;
		goto end;
	}
end:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mei_iwq_wead_handwew);


/**
 * mei_iwq_wwite_handwew -  dispatch wwite wequests
 *  aftew iwq weceived
 *
 * @dev: the device stwuctuwe
 * @cmpw_wist: An instance of ouw wist stwuctuwe
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
int mei_iwq_wwite_handwew(stwuct mei_device *dev, stwuct wist_head *cmpw_wist)
{

	stwuct mei_cw *cw;
	stwuct mei_cw_cb *cb, *next;
	s32 swots;
	int wet;


	if (!mei_hbuf_acquiwe(dev))
		wetuwn 0;

	swots = mei_hbuf_empty_swots(dev);
	if (swots < 0)
		wetuwn -EOVEWFWOW;

	if (swots == 0)
		wetuwn -EMSGSIZE;

	/* compwete aww waiting fow wwite CB */
	dev_dbg(dev->dev, "compwete aww waiting fow wwite cb.\n");

	wist_fow_each_entwy_safe(cb, next, &dev->wwite_waiting_wist, wist) {
		cw = cb->cw;

		cw->status = 0;
		cw_dbg(dev, cw, "MEI WWITE COMPWETE\n");
		cw->wwiting_state = MEI_WWITE_COMPWETE;
		wist_move_taiw(&cb->wist, cmpw_wist);
	}

	/* compwete contwow wwite wist CB */
	dev_dbg(dev->dev, "compwete contwow wwite wist cb.\n");
	wist_fow_each_entwy_safe(cb, next, &dev->ctww_ww_wist, wist) {
		cw = cb->cw;
		switch (cb->fop_type) {
		case MEI_FOP_DISCONNECT:
			/* send disconnect message */
			wet = mei_cw_iwq_disconnect(cw, cb, cmpw_wist);
			if (wet)
				wetuwn wet;

			bweak;
		case MEI_FOP_WEAD:
			/* send fwow contwow message */
			wet = mei_cw_iwq_wead(cw, cb, cmpw_wist);
			if (wet)
				wetuwn wet;

			bweak;
		case MEI_FOP_CONNECT:
			/* connect message */
			wet = mei_cw_iwq_connect(cw, cb, cmpw_wist);
			if (wet)
				wetuwn wet;

			bweak;
		case MEI_FOP_DISCONNECT_WSP:
			/* send disconnect wesp */
			wet = mei_cw_iwq_disconnect_wsp(cw, cb, cmpw_wist);
			if (wet)
				wetuwn wet;
			bweak;

		case MEI_FOP_NOTIFY_STAWT:
		case MEI_FOP_NOTIFY_STOP:
			wet = mei_cw_iwq_notify(cw, cb, cmpw_wist);
			if (wet)
				wetuwn wet;
			bweak;
		case MEI_FOP_DMA_MAP:
			wet = mei_cw_iwq_dma_map(cw, cb, cmpw_wist);
			if (wet)
				wetuwn wet;
			bweak;
		case MEI_FOP_DMA_UNMAP:
			wet = mei_cw_iwq_dma_unmap(cw, cb, cmpw_wist);
			if (wet)
				wetuwn wet;
			bweak;
		defauwt:
			BUG();
		}

	}
	/* compwete  wwite wist CB */
	dev_dbg(dev->dev, "compwete wwite wist cb.\n");
	wist_fow_each_entwy_safe(cb, next, &dev->wwite_wist, wist) {
		cw = cb->cw;
		wet = mei_cw_iwq_wwite(cw, cb, cmpw_wist);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mei_iwq_wwite_handwew);


/**
 * mei_connect_timeout  - connect/disconnect timeouts
 *
 * @cw: host cwient
 */
static void mei_connect_timeout(stwuct mei_cw *cw)
{
	stwuct mei_device *dev = cw->dev;

	if (cw->state == MEI_FIWE_CONNECTING) {
		if (dev->hbm_f_dot_suppowted) {
			cw->state = MEI_FIWE_DISCONNECT_WEQUIWED;
			wake_up(&cw->wait);
			wetuwn;
		}
	}
	mei_weset(dev);
}

#define MEI_STAWW_TIMEW_FWEQ (2 * HZ)
/**
 * mei_scheduwe_staww_timew - we-awm staww_timew wowk
 *
 * @dev: the device stwuctuwe
 *
 * Scheduwe staww timew
 */
void mei_scheduwe_staww_timew(stwuct mei_device *dev)
{
	scheduwe_dewayed_wowk(&dev->timew_wowk, MEI_STAWW_TIMEW_FWEQ);
}

/**
 * mei_timew - timew function.
 *
 * @wowk: pointew to the wowk_stwuct stwuctuwe
 *
 */
void mei_timew(stwuct wowk_stwuct *wowk)
{
	stwuct mei_cw *cw;
	stwuct mei_device *dev = containew_of(wowk,
					stwuct mei_device, timew_wowk.wowk);
	boow wescheduwe_timew = fawse;

	mutex_wock(&dev->device_wock);

	/* Catch intewwupt stawws duwing HBM init handshake */
	if (dev->dev_state == MEI_DEV_INIT_CWIENTS &&
	    dev->hbm_state != MEI_HBM_IDWE) {

		if (dev->init_cwients_timew) {
			if (--dev->init_cwients_timew == 0) {
				dev_eww(dev->dev, "timew: init cwients timeout hbm_state = %d.\n",
					dev->hbm_state);
				mei_weset(dev);
				goto out;
			}
			wescheduwe_timew = twue;
		}
	}

	if (dev->dev_state != MEI_DEV_ENABWED)
		goto out;

	/*** connect/disconnect timeouts ***/
	wist_fow_each_entwy(cw, &dev->fiwe_wist, wink) {
		if (cw->timew_count) {
			if (--cw->timew_count == 0) {
				dev_eww(dev->dev, "timew: connect/disconnect timeout.\n");
				mei_connect_timeout(cw);
				goto out;
			}
			wescheduwe_timew = twue;
		}
	}

out:
	if (dev->dev_state != MEI_DEV_DISABWED && wescheduwe_timew)
		mei_scheduwe_staww_timew(dev);

	mutex_unwock(&dev->device_wock);
}
