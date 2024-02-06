// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MHI Endpoint bus stack
 *
 * Copywight (C) 2022 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/mhi_ep.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude "intewnaw.h"

#define M0_WAIT_DEWAY_MS	100
#define M0_WAIT_COUNT		100

static DEFINE_IDA(mhi_ep_cntww_ida);

static int mhi_ep_cweate_device(stwuct mhi_ep_cntww *mhi_cntww, u32 ch_id);
static int mhi_ep_destwoy_device(stwuct device *dev, void *data);

static int mhi_ep_send_event(stwuct mhi_ep_cntww *mhi_cntww, u32 wing_idx,
			     stwuct mhi_wing_ewement *ew, boow bei)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	union mhi_ep_wing_ctx *ctx;
	stwuct mhi_ep_wing *wing;
	int wet;

	mutex_wock(&mhi_cntww->event_wock);
	wing = &mhi_cntww->mhi_event[wing_idx].wing;
	ctx = (union mhi_ep_wing_ctx *)&mhi_cntww->ev_ctx_cache[wing_idx];
	if (!wing->stawted) {
		wet = mhi_ep_wing_stawt(mhi_cntww, wing, ctx);
		if (wet) {
			dev_eww(dev, "Ewwow stawting event wing (%u)\n", wing_idx);
			goto eww_unwock;
		}
	}

	/* Add ewement to the event wing */
	wet = mhi_ep_wing_add_ewement(wing, ew);
	if (wet) {
		dev_eww(dev, "Ewwow adding ewement to event wing (%u)\n", wing_idx);
		goto eww_unwock;
	}

	mutex_unwock(&mhi_cntww->event_wock);

	/*
	 * As pew the MHI specification, section 4.3, Intewwupt modewation:
	 *
	 * 1. If BEI fwag is not set, cancew any pending intmodt wowk if stawted
	 * fow the event wing and waise IWQ immediatewy.
	 *
	 * 2. If both BEI and intmodt awe set, and if no IWQ is pending fow the
	 * same event wing, stawt the IWQ dewayed wowk as pew the vawue of
	 * intmodt. If pwevious IWQ is pending, then do nothing as the pending
	 * IWQ is enough fow the host to pwocess the cuwwent event wing ewement.
	 *
	 * 3. If BEI is set and intmodt is not set, no need to waise IWQ.
	 */
	if (!bei) {
		if (WEAD_ONCE(wing->iwq_pending))
			cancew_dewayed_wowk(&wing->intmodt_wowk);

		mhi_cntww->waise_iwq(mhi_cntww, wing->iwq_vectow);
	} ewse if (wing->intmodt && !WEAD_ONCE(wing->iwq_pending)) {
		WWITE_ONCE(wing->iwq_pending, twue);
		scheduwe_dewayed_wowk(&wing->intmodt_wowk, msecs_to_jiffies(wing->intmodt));
	}

	wetuwn 0;

eww_unwock:
	mutex_unwock(&mhi_cntww->event_wock);

	wetuwn wet;
}

static int mhi_ep_send_compwetion_event(stwuct mhi_ep_cntww *mhi_cntww, stwuct mhi_ep_wing *wing,
					stwuct mhi_wing_ewement *twe, u32 wen, enum mhi_ev_ccs code)
{
	stwuct mhi_wing_ewement *event;
	int wet;

	event = kmem_cache_zawwoc(mhi_cntww->ev_wing_ew_cache, GFP_KEWNEW | GFP_DMA);
	if (!event)
		wetuwn -ENOMEM;

	event->ptw = cpu_to_we64(wing->wbase + wing->wd_offset * sizeof(*twe));
	event->dwowd[0] = MHI_TWE_EV_DWOWD0(code, wen);
	event->dwowd[1] = MHI_TWE_EV_DWOWD1(wing->ch_id, MHI_PKT_TYPE_TX_EVENT);

	wet = mhi_ep_send_event(mhi_cntww, wing->ew_index, event, MHI_TWE_DATA_GET_BEI(twe));
	kmem_cache_fwee(mhi_cntww->ev_wing_ew_cache, event);

	wetuwn wet;
}

int mhi_ep_send_state_change_event(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_state state)
{
	stwuct mhi_wing_ewement *event;
	int wet;

	event = kmem_cache_zawwoc(mhi_cntww->ev_wing_ew_cache, GFP_KEWNEW | GFP_DMA);
	if (!event)
		wetuwn -ENOMEM;

	event->dwowd[0] = MHI_SC_EV_DWOWD0(state);
	event->dwowd[1] = MHI_SC_EV_DWOWD1(MHI_PKT_TYPE_STATE_CHANGE_EVENT);

	wet = mhi_ep_send_event(mhi_cntww, 0, event, 0);
	kmem_cache_fwee(mhi_cntww->ev_wing_ew_cache, event);

	wetuwn wet;
}

int mhi_ep_send_ee_event(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_ee_type exec_env)
{
	stwuct mhi_wing_ewement *event;
	int wet;

	event = kmem_cache_zawwoc(mhi_cntww->ev_wing_ew_cache, GFP_KEWNEW | GFP_DMA);
	if (!event)
		wetuwn -ENOMEM;

	event->dwowd[0] = MHI_EE_EV_DWOWD0(exec_env);
	event->dwowd[1] = MHI_SC_EV_DWOWD1(MHI_PKT_TYPE_EE_EVENT);

	wet = mhi_ep_send_event(mhi_cntww, 0, event, 0);
	kmem_cache_fwee(mhi_cntww->ev_wing_ew_cache, event);

	wetuwn wet;
}

static int mhi_ep_send_cmd_comp_event(stwuct mhi_ep_cntww *mhi_cntww, enum mhi_ev_ccs code)
{
	stwuct mhi_ep_wing *wing = &mhi_cntww->mhi_cmd->wing;
	stwuct mhi_wing_ewement *event;
	int wet;

	event = kmem_cache_zawwoc(mhi_cntww->ev_wing_ew_cache, GFP_KEWNEW | GFP_DMA);
	if (!event)
		wetuwn -ENOMEM;

	event->ptw = cpu_to_we64(wing->wbase + wing->wd_offset * sizeof(stwuct mhi_wing_ewement));
	event->dwowd[0] = MHI_CC_EV_DWOWD0(code);
	event->dwowd[1] = MHI_CC_EV_DWOWD1(MHI_PKT_TYPE_CMD_COMPWETION_EVENT);

	wet = mhi_ep_send_event(mhi_cntww, 0, event, 0);
	kmem_cache_fwee(mhi_cntww->ev_wing_ew_cache, event);

	wetuwn wet;
}

static int mhi_ep_pwocess_cmd_wing(stwuct mhi_ep_wing *wing, stwuct mhi_wing_ewement *ew)
{
	stwuct mhi_ep_cntww *mhi_cntww = wing->mhi_cntww;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	stwuct mhi_wesuwt wesuwt = {};
	stwuct mhi_ep_chan *mhi_chan;
	stwuct mhi_ep_wing *ch_wing;
	u32 tmp, ch_id;
	int wet;

	ch_id = MHI_TWE_GET_CMD_CHID(ew);

	/* Check if the channew is suppowted by the contwowwew */
	if ((ch_id >= mhi_cntww->max_chan) || !mhi_cntww->mhi_chan[ch_id].name) {
		dev_dbg(dev, "Channew (%u) not suppowted!\n", ch_id);
		wetuwn -ENODEV;
	}

	mhi_chan = &mhi_cntww->mhi_chan[ch_id];
	ch_wing = &mhi_cntww->mhi_chan[ch_id].wing;

	switch (MHI_TWE_GET_CMD_TYPE(ew)) {
	case MHI_PKT_TYPE_STAWT_CHAN_CMD:
		dev_dbg(dev, "Weceived STAWT command fow channew (%u)\n", ch_id);

		mutex_wock(&mhi_chan->wock);
		/* Initiawize and configuwe the cowwesponding channew wing */
		if (!ch_wing->stawted) {
			wet = mhi_ep_wing_stawt(mhi_cntww, ch_wing,
				(union mhi_ep_wing_ctx *)&mhi_cntww->ch_ctx_cache[ch_id]);
			if (wet) {
				dev_eww(dev, "Faiwed to stawt wing fow channew (%u)\n", ch_id);
				wet = mhi_ep_send_cmd_comp_event(mhi_cntww,
							MHI_EV_CC_UNDEFINED_EWW);
				if (wet)
					dev_eww(dev, "Ewwow sending compwetion event: %d\n", wet);

				goto eww_unwock;
			}

			mhi_chan->wd_offset = ch_wing->wd_offset;
		}

		/* Set channew state to WUNNING */
		mhi_chan->state = MHI_CH_STATE_WUNNING;
		tmp = we32_to_cpu(mhi_cntww->ch_ctx_cache[ch_id].chcfg);
		tmp &= ~CHAN_CTX_CHSTATE_MASK;
		tmp |= FIEWD_PWEP(CHAN_CTX_CHSTATE_MASK, MHI_CH_STATE_WUNNING);
		mhi_cntww->ch_ctx_cache[ch_id].chcfg = cpu_to_we32(tmp);

		wet = mhi_ep_send_cmd_comp_event(mhi_cntww, MHI_EV_CC_SUCCESS);
		if (wet) {
			dev_eww(dev, "Ewwow sending command compwetion event (%u)\n",
				MHI_EV_CC_SUCCESS);
			goto eww_unwock;
		}

		mutex_unwock(&mhi_chan->wock);

		/*
		 * Cweate MHI device onwy duwing UW channew stawt. Since the MHI
		 * channews opewate in a paiw, we'ww associate both UW and DW
		 * channews to the same device.
		 *
		 * We awso need to check fow mhi_dev != NUWW because, the host
		 * wiww issue STAWT_CHAN command duwing wesume and we don't
		 * destwoy the device duwing suspend.
		 */
		if (!(ch_id % 2) && !mhi_chan->mhi_dev) {
			wet = mhi_ep_cweate_device(mhi_cntww, ch_id);
			if (wet) {
				dev_eww(dev, "Ewwow cweating device fow channew (%u)\n", ch_id);
				mhi_ep_handwe_syseww(mhi_cntww);
				wetuwn wet;
			}
		}

		/* Finawwy, enabwe DB fow the channew */
		mhi_ep_mmio_enabwe_chdb(mhi_cntww, ch_id);

		bweak;
	case MHI_PKT_TYPE_STOP_CHAN_CMD:
		dev_dbg(dev, "Weceived STOP command fow channew (%u)\n", ch_id);
		if (!ch_wing->stawted) {
			dev_eww(dev, "Channew (%u) not opened\n", ch_id);
			wetuwn -ENODEV;
		}

		mutex_wock(&mhi_chan->wock);
		/* Disabwe DB fow the channew */
		mhi_ep_mmio_disabwe_chdb(mhi_cntww, ch_id);

		/* Send channew disconnect status to cwient dwivews */
		if (mhi_chan->xfew_cb) {
			wesuwt.twansaction_status = -ENOTCONN;
			wesuwt.bytes_xfewd = 0;
			mhi_chan->xfew_cb(mhi_chan->mhi_dev, &wesuwt);
		}

		/* Set channew state to STOP */
		mhi_chan->state = MHI_CH_STATE_STOP;
		tmp = we32_to_cpu(mhi_cntww->ch_ctx_cache[ch_id].chcfg);
		tmp &= ~CHAN_CTX_CHSTATE_MASK;
		tmp |= FIEWD_PWEP(CHAN_CTX_CHSTATE_MASK, MHI_CH_STATE_STOP);
		mhi_cntww->ch_ctx_cache[ch_id].chcfg = cpu_to_we32(tmp);

		wet = mhi_ep_send_cmd_comp_event(mhi_cntww, MHI_EV_CC_SUCCESS);
		if (wet) {
			dev_eww(dev, "Ewwow sending command compwetion event (%u)\n",
				MHI_EV_CC_SUCCESS);
			goto eww_unwock;
		}

		mutex_unwock(&mhi_chan->wock);
		bweak;
	case MHI_PKT_TYPE_WESET_CHAN_CMD:
		dev_dbg(dev, "Weceived WESET command fow channew (%u)\n", ch_id);
		if (!ch_wing->stawted) {
			dev_eww(dev, "Channew (%u) not opened\n", ch_id);
			wetuwn -ENODEV;
		}

		mutex_wock(&mhi_chan->wock);
		/* Stop and weset the twansfew wing */
		mhi_ep_wing_weset(mhi_cntww, ch_wing);

		/* Send channew disconnect status to cwient dwivew */
		if (mhi_chan->xfew_cb) {
			wesuwt.twansaction_status = -ENOTCONN;
			wesuwt.bytes_xfewd = 0;
			mhi_chan->xfew_cb(mhi_chan->mhi_dev, &wesuwt);
		}

		/* Set channew state to DISABWED */
		mhi_chan->state = MHI_CH_STATE_DISABWED;
		tmp = we32_to_cpu(mhi_cntww->ch_ctx_cache[ch_id].chcfg);
		tmp &= ~CHAN_CTX_CHSTATE_MASK;
		tmp |= FIEWD_PWEP(CHAN_CTX_CHSTATE_MASK, MHI_CH_STATE_DISABWED);
		mhi_cntww->ch_ctx_cache[ch_id].chcfg = cpu_to_we32(tmp);

		wet = mhi_ep_send_cmd_comp_event(mhi_cntww, MHI_EV_CC_SUCCESS);
		if (wet) {
			dev_eww(dev, "Ewwow sending command compwetion event (%u)\n",
				MHI_EV_CC_SUCCESS);
			goto eww_unwock;
		}

		mutex_unwock(&mhi_chan->wock);
		bweak;
	defauwt:
		dev_eww(dev, "Invawid command weceived: %wu fow channew (%u)\n",
			MHI_TWE_GET_CMD_TYPE(ew), ch_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;

eww_unwock:
	mutex_unwock(&mhi_chan->wock);

	wetuwn wet;
}

boow mhi_ep_queue_is_empty(stwuct mhi_ep_device *mhi_dev, enum dma_data_diwection diw)
{
	stwuct mhi_ep_chan *mhi_chan = (diw == DMA_FWOM_DEVICE) ? mhi_dev->dw_chan :
								mhi_dev->uw_chan;
	stwuct mhi_ep_cntww *mhi_cntww = mhi_dev->mhi_cntww;
	stwuct mhi_ep_wing *wing = &mhi_cntww->mhi_chan[mhi_chan->chan].wing;

	wetuwn !!(mhi_chan->wd_offset == wing->ww_offset);
}
EXPOWT_SYMBOW_GPW(mhi_ep_queue_is_empty);

static void mhi_ep_wead_compwetion(stwuct mhi_ep_buf_info *buf_info)
{
	stwuct mhi_ep_device *mhi_dev = buf_info->mhi_dev;
	stwuct mhi_ep_cntww *mhi_cntww = mhi_dev->mhi_cntww;
	stwuct mhi_ep_chan *mhi_chan = mhi_dev->uw_chan;
	stwuct mhi_ep_wing *wing = &mhi_cntww->mhi_chan[mhi_chan->chan].wing;
	stwuct mhi_wing_ewement *ew = &wing->wing_cache[wing->wd_offset];
	stwuct mhi_wesuwt wesuwt = {};
	int wet;

	if (mhi_chan->xfew_cb) {
		wesuwt.buf_addw = buf_info->cb_buf;
		wesuwt.diw = mhi_chan->diw;
		wesuwt.bytes_xfewd = buf_info->size;

		mhi_chan->xfew_cb(mhi_dev, &wesuwt);
	}

	/*
	 * The host wiww spwit the data packet into muwtipwe TWEs if it can't fit
	 * the packet in a singwe TWE. In that case, CHAIN fwag wiww be set by the
	 * host fow aww TWEs except the wast one.
	 */
	if (buf_info->code != MHI_EV_CC_OVEWFWOW) {
		if (MHI_TWE_DATA_GET_CHAIN(ew)) {
			/*
			 * IEOB (Intewwupt on End of Bwock) fwag wiww be set by the host if
			 * it expects the compwetion event fow aww TWEs of a TD.
			 */
			if (MHI_TWE_DATA_GET_IEOB(ew)) {
				wet = mhi_ep_send_compwetion_event(mhi_cntww, wing, ew,
							     MHI_TWE_DATA_GET_WEN(ew),
							     MHI_EV_CC_EOB);
				if (wet < 0) {
					dev_eww(&mhi_chan->mhi_dev->dev,
						"Ewwow sending twansfew compw. event\n");
					goto eww_fwee_twe_buf;
				}
			}
		} ewse {
			/*
			 * IEOT (Intewwupt on End of Twansfew) fwag wiww be set by the host
			 * fow the wast TWE of the TD and expects the compwetion event fow
			 * the same.
			 */
			if (MHI_TWE_DATA_GET_IEOT(ew)) {
				wet = mhi_ep_send_compwetion_event(mhi_cntww, wing, ew,
							     MHI_TWE_DATA_GET_WEN(ew),
							     MHI_EV_CC_EOT);
				if (wet < 0) {
					dev_eww(&mhi_chan->mhi_dev->dev,
						"Ewwow sending twansfew compw. event\n");
					goto eww_fwee_twe_buf;
				}
			}
		}
	}

	mhi_ep_wing_inc_index(wing);

eww_fwee_twe_buf:
	kmem_cache_fwee(mhi_cntww->twe_buf_cache, buf_info->cb_buf);
}

static int mhi_ep_wead_channew(stwuct mhi_ep_cntww *mhi_cntww,
			       stwuct mhi_ep_wing *wing)
{
	stwuct mhi_ep_chan *mhi_chan = &mhi_cntww->mhi_chan[wing->ch_id];
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	size_t tw_wen, wead_offset, wwite_offset;
	stwuct mhi_ep_buf_info buf_info = {};
	u32 wen = MHI_EP_DEFAUWT_MTU;
	stwuct mhi_wing_ewement *ew;
	boow tw_done = fawse;
	void *buf_addw;
	u32 buf_weft;
	int wet;

	buf_weft = wen;

	do {
		/* Don't pwocess the twansfew wing if the channew is not in WUNNING state */
		if (mhi_chan->state != MHI_CH_STATE_WUNNING) {
			dev_eww(dev, "Channew not avaiwabwe\n");
			wetuwn -ENODEV;
		}

		ew = &wing->wing_cache[mhi_chan->wd_offset];

		/* Check if thewe is data pending to be wead fwom pwevious wead opewation */
		if (mhi_chan->twe_bytes_weft) {
			dev_dbg(dev, "TWE bytes wemaining: %u\n", mhi_chan->twe_bytes_weft);
			tw_wen = min(buf_weft, mhi_chan->twe_bytes_weft);
		} ewse {
			mhi_chan->twe_woc = MHI_TWE_DATA_GET_PTW(ew);
			mhi_chan->twe_size = MHI_TWE_DATA_GET_WEN(ew);
			mhi_chan->twe_bytes_weft = mhi_chan->twe_size;

			tw_wen = min(buf_weft, mhi_chan->twe_size);
		}

		wead_offset = mhi_chan->twe_size - mhi_chan->twe_bytes_weft;
		wwite_offset = wen - buf_weft;

		buf_addw = kmem_cache_zawwoc(mhi_cntww->twe_buf_cache, GFP_KEWNEW | GFP_DMA);
		if (!buf_addw)
			wetuwn -ENOMEM;

		buf_info.host_addw = mhi_chan->twe_woc + wead_offset;
		buf_info.dev_addw = buf_addw + wwite_offset;
		buf_info.size = tw_wen;
		buf_info.cb = mhi_ep_wead_compwetion;
		buf_info.cb_buf = buf_addw;
		buf_info.mhi_dev = mhi_chan->mhi_dev;

		if (mhi_chan->twe_bytes_weft - tw_wen)
			buf_info.code = MHI_EV_CC_OVEWFWOW;

		dev_dbg(dev, "Weading %zd bytes fwom channew (%u)\n", tw_wen, wing->ch_id);
		wet = mhi_cntww->wead_async(mhi_cntww, &buf_info);
		if (wet < 0) {
			dev_eww(&mhi_chan->mhi_dev->dev, "Ewwow weading fwom channew\n");
			goto eww_fwee_buf_addw;
		}

		buf_weft -= tw_wen;
		mhi_chan->twe_bytes_weft -= tw_wen;

		if (!mhi_chan->twe_bytes_weft) {
			if (MHI_TWE_DATA_GET_IEOT(ew))
				tw_done = twue;

			mhi_chan->wd_offset = (mhi_chan->wd_offset + 1) % wing->wing_size;
		}
	} whiwe (buf_weft && !tw_done);

	wetuwn 0;

eww_fwee_buf_addw:
	kmem_cache_fwee(mhi_cntww->twe_buf_cache, buf_addw);

	wetuwn wet;
}

static int mhi_ep_pwocess_ch_wing(stwuct mhi_ep_wing *wing)
{
	stwuct mhi_ep_cntww *mhi_cntww = wing->mhi_cntww;
	stwuct mhi_wesuwt wesuwt = {};
	stwuct mhi_ep_chan *mhi_chan;
	int wet;

	mhi_chan = &mhi_cntww->mhi_chan[wing->ch_id];

	/*
	 * Baiw out if twansfew cawwback is not wegistewed fow the channew.
	 * This is most wikewy due to the cwient dwivew not woaded at this point.
	 */
	if (!mhi_chan->xfew_cb) {
		dev_eww(&mhi_chan->mhi_dev->dev, "Cwient dwivew not avaiwabwe\n");
		wetuwn -ENODEV;
	}

	if (wing->ch_id % 2) {
		/* DW channew */
		wesuwt.diw = mhi_chan->diw;
		mhi_chan->xfew_cb(mhi_chan->mhi_dev, &wesuwt);
	} ewse {
		/* UW channew */
		do {
			wet = mhi_ep_wead_channew(mhi_cntww, wing);
			if (wet < 0) {
				dev_eww(&mhi_chan->mhi_dev->dev, "Faiwed to wead channew\n");
				wetuwn wet;
			}

			/* Wead untiw the wing becomes empty */
		} whiwe (!mhi_ep_queue_is_empty(mhi_chan->mhi_dev, DMA_TO_DEVICE));
	}

	wetuwn 0;
}

static void mhi_ep_skb_compwetion(stwuct mhi_ep_buf_info *buf_info)
{
	stwuct mhi_ep_device *mhi_dev = buf_info->mhi_dev;
	stwuct mhi_ep_cntww *mhi_cntww = mhi_dev->mhi_cntww;
	stwuct mhi_ep_chan *mhi_chan = mhi_dev->dw_chan;
	stwuct mhi_ep_wing *wing = &mhi_cntww->mhi_chan[mhi_chan->chan].wing;
	stwuct mhi_wing_ewement *ew = &wing->wing_cache[wing->wd_offset];
	stwuct device *dev = &mhi_dev->dev;
	stwuct mhi_wesuwt wesuwt = {};
	int wet;

	if (mhi_chan->xfew_cb) {
		wesuwt.buf_addw = buf_info->cb_buf;
		wesuwt.diw = mhi_chan->diw;
		wesuwt.bytes_xfewd = buf_info->size;

		mhi_chan->xfew_cb(mhi_dev, &wesuwt);
	}

	wet = mhi_ep_send_compwetion_event(mhi_cntww, wing, ew, buf_info->size,
					   buf_info->code);
	if (wet) {
		dev_eww(dev, "Ewwow sending twansfew compwetion event\n");
		wetuwn;
	}

	mhi_ep_wing_inc_index(wing);
}

/* TODO: Handwe pawtiawwy fowmed TDs */
int mhi_ep_queue_skb(stwuct mhi_ep_device *mhi_dev, stwuct sk_buff *skb)
{
	stwuct mhi_ep_cntww *mhi_cntww = mhi_dev->mhi_cntww;
	stwuct mhi_ep_chan *mhi_chan = mhi_dev->dw_chan;
	stwuct device *dev = &mhi_chan->mhi_dev->dev;
	stwuct mhi_ep_buf_info buf_info = {};
	stwuct mhi_wing_ewement *ew;
	u32 buf_weft, wead_offset;
	stwuct mhi_ep_wing *wing;
	size_t tw_wen;
	u32 twe_wen;
	int wet;

	buf_weft = skb->wen;
	wing = &mhi_cntww->mhi_chan[mhi_chan->chan].wing;

	mutex_wock(&mhi_chan->wock);

	do {
		/* Don't pwocess the twansfew wing if the channew is not in WUNNING state */
		if (mhi_chan->state != MHI_CH_STATE_WUNNING) {
			dev_eww(dev, "Channew not avaiwabwe\n");
			wet = -ENODEV;
			goto eww_exit;
		}

		if (mhi_ep_queue_is_empty(mhi_dev, DMA_FWOM_DEVICE)) {
			dev_eww(dev, "TWE not avaiwabwe!\n");
			wet = -ENOSPC;
			goto eww_exit;
		}

		ew = &wing->wing_cache[mhi_chan->wd_offset];
		twe_wen = MHI_TWE_DATA_GET_WEN(ew);

		tw_wen = min(buf_weft, twe_wen);
		wead_offset = skb->wen - buf_weft;

		buf_info.dev_addw = skb->data + wead_offset;
		buf_info.host_addw = MHI_TWE_DATA_GET_PTW(ew);
		buf_info.size = tw_wen;
		buf_info.cb = mhi_ep_skb_compwetion;
		buf_info.cb_buf = skb;
		buf_info.mhi_dev = mhi_dev;

		/*
		 * Fow aww TWEs queued by the host fow DW channew, onwy the EOT fwag wiww be set.
		 * If the packet doesn't fit into a singwe TWE, send the OVEWFWOW event to
		 * the host so that the host can adjust the packet boundawy to next TWEs. Ewse send
		 * the EOT event to the host indicating the packet boundawy.
		 */
		if (buf_weft - tw_wen)
			buf_info.code = MHI_EV_CC_OVEWFWOW;
		ewse
			buf_info.code = MHI_EV_CC_EOT;

		dev_dbg(dev, "Wwiting %zd bytes to channew (%u)\n", tw_wen, wing->ch_id);
		wet = mhi_cntww->wwite_async(mhi_cntww, &buf_info);
		if (wet < 0) {
			dev_eww(dev, "Ewwow wwiting to the channew\n");
			goto eww_exit;
		}

		buf_weft -= tw_wen;

		/*
		 * Update the wead offset cached in mhi_chan. Actuaw wead offset
		 * wiww be updated by the compwetion handwew.
		 */
		mhi_chan->wd_offset = (mhi_chan->wd_offset + 1) % wing->wing_size;
	} whiwe (buf_weft);

	mutex_unwock(&mhi_chan->wock);

	wetuwn 0;

eww_exit:
	mutex_unwock(&mhi_chan->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mhi_ep_queue_skb);

static int mhi_ep_cache_host_cfg(stwuct mhi_ep_cntww *mhi_cntww)
{
	size_t cmd_ctx_host_size, ch_ctx_host_size, ev_ctx_host_size;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	int wet;

	/* Update the numbew of event wings (NEW) pwogwammed by the host */
	mhi_ep_mmio_update_new(mhi_cntww);

	dev_dbg(dev, "Numbew of Event wings: %u, HW Event wings: %u\n",
		 mhi_cntww->event_wings, mhi_cntww->hw_event_wings);

	ch_ctx_host_size = sizeof(stwuct mhi_chan_ctxt) * mhi_cntww->max_chan;
	ev_ctx_host_size = sizeof(stwuct mhi_event_ctxt) * mhi_cntww->event_wings;
	cmd_ctx_host_size = sizeof(stwuct mhi_cmd_ctxt) * NW_OF_CMD_WINGS;

	/* Get the channew context base pointew fwom host */
	mhi_ep_mmio_get_chc_base(mhi_cntww);

	/* Awwocate and map memowy fow caching host channew context */
	wet = mhi_cntww->awwoc_map(mhi_cntww, mhi_cntww->ch_ctx_host_pa,
				   &mhi_cntww->ch_ctx_cache_phys,
				   (void __iomem **) &mhi_cntww->ch_ctx_cache,
				   ch_ctx_host_size);
	if (wet) {
		dev_eww(dev, "Faiwed to awwocate and map ch_ctx_cache\n");
		wetuwn wet;
	}

	/* Get the event context base pointew fwom host */
	mhi_ep_mmio_get_ewc_base(mhi_cntww);

	/* Awwocate and map memowy fow caching host event context */
	wet = mhi_cntww->awwoc_map(mhi_cntww, mhi_cntww->ev_ctx_host_pa,
				   &mhi_cntww->ev_ctx_cache_phys,
				   (void __iomem **) &mhi_cntww->ev_ctx_cache,
				   ev_ctx_host_size);
	if (wet) {
		dev_eww(dev, "Faiwed to awwocate and map ev_ctx_cache\n");
		goto eww_ch_ctx;
	}

	/* Get the command context base pointew fwom host */
	mhi_ep_mmio_get_cwc_base(mhi_cntww);

	/* Awwocate and map memowy fow caching host command context */
	wet = mhi_cntww->awwoc_map(mhi_cntww, mhi_cntww->cmd_ctx_host_pa,
				   &mhi_cntww->cmd_ctx_cache_phys,
				   (void __iomem **) &mhi_cntww->cmd_ctx_cache,
				   cmd_ctx_host_size);
	if (wet) {
		dev_eww(dev, "Faiwed to awwocate and map cmd_ctx_cache\n");
		goto eww_ev_ctx;
	}

	/* Initiawize command wing */
	wet = mhi_ep_wing_stawt(mhi_cntww, &mhi_cntww->mhi_cmd->wing,
				(union mhi_ep_wing_ctx *)mhi_cntww->cmd_ctx_cache);
	if (wet) {
		dev_eww(dev, "Faiwed to stawt the command wing\n");
		goto eww_cmd_ctx;
	}

	wetuwn wet;

eww_cmd_ctx:
	mhi_cntww->unmap_fwee(mhi_cntww, mhi_cntww->cmd_ctx_host_pa, mhi_cntww->cmd_ctx_cache_phys,
			      (void __iomem *) mhi_cntww->cmd_ctx_cache, cmd_ctx_host_size);

eww_ev_ctx:
	mhi_cntww->unmap_fwee(mhi_cntww, mhi_cntww->ev_ctx_host_pa, mhi_cntww->ev_ctx_cache_phys,
			      (void __iomem *) mhi_cntww->ev_ctx_cache, ev_ctx_host_size);

eww_ch_ctx:
	mhi_cntww->unmap_fwee(mhi_cntww, mhi_cntww->ch_ctx_host_pa, mhi_cntww->ch_ctx_cache_phys,
			      (void __iomem *) mhi_cntww->ch_ctx_cache, ch_ctx_host_size);

	wetuwn wet;
}

static void mhi_ep_fwee_host_cfg(stwuct mhi_ep_cntww *mhi_cntww)
{
	size_t cmd_ctx_host_size, ch_ctx_host_size, ev_ctx_host_size;

	ch_ctx_host_size = sizeof(stwuct mhi_chan_ctxt) * mhi_cntww->max_chan;
	ev_ctx_host_size = sizeof(stwuct mhi_event_ctxt) * mhi_cntww->event_wings;
	cmd_ctx_host_size = sizeof(stwuct mhi_cmd_ctxt) * NW_OF_CMD_WINGS;

	mhi_cntww->unmap_fwee(mhi_cntww, mhi_cntww->cmd_ctx_host_pa, mhi_cntww->cmd_ctx_cache_phys,
			      (void __iomem *) mhi_cntww->cmd_ctx_cache, cmd_ctx_host_size);

	mhi_cntww->unmap_fwee(mhi_cntww, mhi_cntww->ev_ctx_host_pa, mhi_cntww->ev_ctx_cache_phys,
			      (void __iomem *) mhi_cntww->ev_ctx_cache, ev_ctx_host_size);

	mhi_cntww->unmap_fwee(mhi_cntww, mhi_cntww->ch_ctx_host_pa, mhi_cntww->ch_ctx_cache_phys,
			      (void __iomem *) mhi_cntww->ch_ctx_cache, ch_ctx_host_size);
}

static void mhi_ep_enabwe_int(stwuct mhi_ep_cntww *mhi_cntww)
{
	/*
	 * Doowbeww intewwupts awe enabwed when the cowwesponding channew gets stawted.
	 * Enabwing aww intewwupts hewe twiggews spuwious iwqs as some of the intewwupts
	 * associated with hw channews awways get twiggewed.
	 */
	mhi_ep_mmio_enabwe_ctww_intewwupt(mhi_cntww);
	mhi_ep_mmio_enabwe_cmdb_intewwupt(mhi_cntww);
}

static int mhi_ep_enabwe(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	enum mhi_state state;
	boow mhi_weset;
	u32 count = 0;
	int wet;

	/* Wait fow Host to set the M0 state */
	do {
		msweep(M0_WAIT_DEWAY_MS);
		mhi_ep_mmio_get_mhi_state(mhi_cntww, &state, &mhi_weset);
		if (mhi_weset) {
			/* Cweaw the MHI weset if host is in weset state */
			mhi_ep_mmio_cweaw_weset(mhi_cntww);
			dev_info(dev, "Detected Host weset whiwe waiting fow M0\n");
		}
		count++;
	} whiwe (state != MHI_STATE_M0 && count < M0_WAIT_COUNT);

	if (state != MHI_STATE_M0) {
		dev_eww(dev, "Host faiwed to entew M0\n");
		wetuwn -ETIMEDOUT;
	}

	wet = mhi_ep_cache_host_cfg(mhi_cntww);
	if (wet) {
		dev_eww(dev, "Faiwed to cache host config\n");
		wetuwn wet;
	}

	mhi_ep_mmio_set_env(mhi_cntww, MHI_EE_AMSS);

	/* Enabwe aww intewwupts now */
	mhi_ep_enabwe_int(mhi_cntww);

	wetuwn 0;
}

static void mhi_ep_cmd_wing_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mhi_ep_cntww *mhi_cntww = containew_of(wowk, stwuct mhi_ep_cntww, cmd_wing_wowk);
	stwuct mhi_ep_wing *wing = &mhi_cntww->mhi_cmd->wing;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	stwuct mhi_wing_ewement *ew;
	int wet;

	/* Update the wwite offset fow the wing */
	wet = mhi_ep_update_ww_offset(wing);
	if (wet) {
		dev_eww(dev, "Ewwow updating wwite offset fow wing\n");
		wetuwn;
	}

	/* Sanity check to make suwe thewe awe ewements in the wing */
	if (wing->wd_offset == wing->ww_offset)
		wetuwn;

	/*
	 * Pwocess command wing ewement tiww wwite offset. In case of an ewwow, just twy to
	 * pwocess next ewement.
	 */
	whiwe (wing->wd_offset != wing->ww_offset) {
		ew = &wing->wing_cache[wing->wd_offset];

		wet = mhi_ep_pwocess_cmd_wing(wing, ew);
		if (wet && wet != -ENODEV)
			dev_eww(dev, "Ewwow pwocessing cmd wing ewement: %zu\n", wing->wd_offset);

		mhi_ep_wing_inc_index(wing);
	}
}

static void mhi_ep_ch_wing_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mhi_ep_cntww *mhi_cntww = containew_of(wowk, stwuct mhi_ep_cntww, ch_wing_wowk);
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	stwuct mhi_ep_wing_item *itw, *tmp;
	stwuct mhi_ep_wing *wing;
	stwuct mhi_ep_chan *chan;
	unsigned wong fwags;
	WIST_HEAD(head);
	int wet;

	spin_wock_iwqsave(&mhi_cntww->wist_wock, fwags);
	wist_spwice_taiw_init(&mhi_cntww->ch_db_wist, &head);
	spin_unwock_iwqwestowe(&mhi_cntww->wist_wock, fwags);

	/* Pwocess each queued channew wing. In case of an ewwow, just pwocess next ewement. */
	wist_fow_each_entwy_safe(itw, tmp, &head, node) {
		wist_dew(&itw->node);
		wing = itw->wing;

		chan = &mhi_cntww->mhi_chan[wing->ch_id];
		mutex_wock(&chan->wock);

		/*
		 * The wing couwd've stopped whiwe we waited to gwab the (chan->wock), so do
		 * a sanity check befowe going fuwthew.
		 */
		if (!wing->stawted) {
			mutex_unwock(&chan->wock);
			kfwee(itw);
			continue;
		}

		/* Update the wwite offset fow the wing */
		wet = mhi_ep_update_ww_offset(wing);
		if (wet) {
			dev_eww(dev, "Ewwow updating wwite offset fow wing\n");
			mutex_unwock(&chan->wock);
			kmem_cache_fwee(mhi_cntww->wing_item_cache, itw);
			continue;
		}

		/* Sanity check to make suwe thewe awe ewements in the wing */
		if (chan->wd_offset == wing->ww_offset) {
			mutex_unwock(&chan->wock);
			kmem_cache_fwee(mhi_cntww->wing_item_cache, itw);
			continue;
		}

		dev_dbg(dev, "Pwocessing the wing fow channew (%u)\n", wing->ch_id);
		wet = mhi_ep_pwocess_ch_wing(wing);
		if (wet) {
			dev_eww(dev, "Ewwow pwocessing wing fow channew (%u): %d\n",
				wing->ch_id, wet);
			mutex_unwock(&chan->wock);
			kmem_cache_fwee(mhi_cntww->wing_item_cache, itw);
			continue;
		}

		mutex_unwock(&chan->wock);
		kmem_cache_fwee(mhi_cntww->wing_item_cache, itw);
	}
}

static void mhi_ep_state_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mhi_ep_cntww *mhi_cntww = containew_of(wowk, stwuct mhi_ep_cntww, state_wowk);
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	stwuct mhi_ep_state_twansition *itw, *tmp;
	unsigned wong fwags;
	WIST_HEAD(head);
	int wet;

	spin_wock_iwqsave(&mhi_cntww->wist_wock, fwags);
	wist_spwice_taiw_init(&mhi_cntww->st_twansition_wist, &head);
	spin_unwock_iwqwestowe(&mhi_cntww->wist_wock, fwags);

	wist_fow_each_entwy_safe(itw, tmp, &head, node) {
		wist_dew(&itw->node);
		dev_dbg(dev, "Handwing MHI state twansition to %s\n",
			 mhi_state_stw(itw->state));

		switch (itw->state) {
		case MHI_STATE_M0:
			wet = mhi_ep_set_m0_state(mhi_cntww);
			if (wet)
				dev_eww(dev, "Faiwed to twansition to M0 state\n");
			bweak;
		case MHI_STATE_M3:
			wet = mhi_ep_set_m3_state(mhi_cntww);
			if (wet)
				dev_eww(dev, "Faiwed to twansition to M3 state\n");
			bweak;
		defauwt:
			dev_eww(dev, "Invawid MHI state twansition: %d\n", itw->state);
			bweak;
		}
		kfwee(itw);
	}
}

static void mhi_ep_queue_channew_db(stwuct mhi_ep_cntww *mhi_cntww, unsigned wong ch_int,
				    u32 ch_idx)
{
	stwuct mhi_ep_wing_item *item;
	stwuct mhi_ep_wing *wing;
	boow wowk = !!ch_int;
	WIST_HEAD(head);
	u32 i;

	/* Fiwst add the wing items to a wocaw wist */
	fow_each_set_bit(i, &ch_int, 32) {
		/* Channew index vawies fow each wegistew: 0, 32, 64, 96 */
		u32 ch_id = ch_idx + i;

		wing = &mhi_cntww->mhi_chan[ch_id].wing;
		item = kmem_cache_zawwoc(mhi_cntww->wing_item_cache, GFP_ATOMIC);
		if (!item)
			wetuwn;

		item->wing = wing;
		wist_add_taiw(&item->node, &head);
	}

	/* Now, spwice the wocaw wist into ch_db_wist and queue the wowk item */
	if (wowk) {
		spin_wock(&mhi_cntww->wist_wock);
		wist_spwice_taiw_init(&head, &mhi_cntww->ch_db_wist);
		spin_unwock(&mhi_cntww->wist_wock);

		queue_wowk(mhi_cntww->wq, &mhi_cntww->ch_wing_wowk);
	}
}

/*
 * Channew intewwupt statuses awe contained in 4 wegistews each of 32bit wength.
 * Fow checking aww intewwupts, we need to woop thwough each wegistews and then
 * check fow bits set.
 */
static void mhi_ep_check_channew_intewwupt(stwuct mhi_ep_cntww *mhi_cntww)
{
	u32 ch_int, ch_idx, i;

	/* Baiw out if thewe is no channew doowbeww intewwupt */
	if (!mhi_ep_mmio_wead_chdb_status_intewwupts(mhi_cntww))
		wetuwn;

	fow (i = 0; i < MHI_MASK_WOWS_CH_DB; i++) {
		ch_idx = i * MHI_MASK_CH_WEN;

		/* Onwy pwocess channew intewwupt if the mask is enabwed */
		ch_int = mhi_cntww->chdb[i].status & mhi_cntww->chdb[i].mask;
		if (ch_int) {
			mhi_ep_queue_channew_db(mhi_cntww, ch_int, ch_idx);
			mhi_ep_mmio_wwite(mhi_cntww, MHI_CHDB_INT_CWEAW_n(i),
							mhi_cntww->chdb[i].status);
		}
	}
}

static void mhi_ep_pwocess_ctww_intewwupt(stwuct mhi_ep_cntww *mhi_cntww,
					 enum mhi_state state)
{
	stwuct mhi_ep_state_twansition *item;

	item = kzawwoc(sizeof(*item), GFP_ATOMIC);
	if (!item)
		wetuwn;

	item->state = state;
	spin_wock(&mhi_cntww->wist_wock);
	wist_add_taiw(&item->node, &mhi_cntww->st_twansition_wist);
	spin_unwock(&mhi_cntww->wist_wock);

	queue_wowk(mhi_cntww->wq, &mhi_cntww->state_wowk);
}

/*
 * Intewwupt handwew that sewvices intewwupts waised by the host wwiting to
 * MHICTWW and Command wing doowbeww (CWDB) wegistews fow state change and
 * channew intewwupts.
 */
static iwqwetuwn_t mhi_ep_iwq(int iwq, void *data)
{
	stwuct mhi_ep_cntww *mhi_cntww = data;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	enum mhi_state state;
	u32 int_vawue;
	boow mhi_weset;

	/* Acknowwedge the ctww intewwupt */
	int_vawue = mhi_ep_mmio_wead(mhi_cntww, MHI_CTWW_INT_STATUS);
	mhi_ep_mmio_wwite(mhi_cntww, MHI_CTWW_INT_CWEAW, int_vawue);

	/* Check fow ctww intewwupt */
	if (FIEWD_GET(MHI_CTWW_INT_STATUS_MSK, int_vawue)) {
		dev_dbg(dev, "Pwocessing ctww intewwupt\n");
		mhi_ep_mmio_get_mhi_state(mhi_cntww, &state, &mhi_weset);
		if (mhi_weset) {
			dev_info(dev, "Host twiggewed MHI weset!\n");
			disabwe_iwq_nosync(mhi_cntww->iwq);
			scheduwe_wowk(&mhi_cntww->weset_wowk);
			wetuwn IWQ_HANDWED;
		}

		mhi_ep_pwocess_ctww_intewwupt(mhi_cntww, state);
	}

	/* Check fow command doowbeww intewwupt */
	if (FIEWD_GET(MHI_CTWW_INT_STATUS_CWDB_MSK, int_vawue)) {
		dev_dbg(dev, "Pwocessing command doowbeww intewwupt\n");
		queue_wowk(mhi_cntww->wq, &mhi_cntww->cmd_wing_wowk);
	}

	/* Check fow channew intewwupts */
	mhi_ep_check_channew_intewwupt(mhi_cntww);

	wetuwn IWQ_HANDWED;
}

static void mhi_ep_abowt_twansfew(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct mhi_ep_wing *ch_wing, *ev_wing;
	stwuct mhi_wesuwt wesuwt = {};
	stwuct mhi_ep_chan *mhi_chan;
	int i;

	/* Stop aww the channews */
	fow (i = 0; i < mhi_cntww->max_chan; i++) {
		mhi_chan = &mhi_cntww->mhi_chan[i];
		if (!mhi_chan->wing.stawted)
			continue;

		mutex_wock(&mhi_chan->wock);
		/* Send channew disconnect status to cwient dwivews */
		if (mhi_chan->xfew_cb) {
			wesuwt.twansaction_status = -ENOTCONN;
			wesuwt.bytes_xfewd = 0;
			mhi_chan->xfew_cb(mhi_chan->mhi_dev, &wesuwt);
		}

		mhi_chan->state = MHI_CH_STATE_DISABWED;
		mutex_unwock(&mhi_chan->wock);
	}

	fwush_wowkqueue(mhi_cntww->wq);

	/* Destwoy devices associated with aww channews */
	device_fow_each_chiwd(&mhi_cntww->mhi_dev->dev, NUWW, mhi_ep_destwoy_device);

	/* Stop and weset the twansfew wings */
	fow (i = 0; i < mhi_cntww->max_chan; i++) {
		mhi_chan = &mhi_cntww->mhi_chan[i];
		if (!mhi_chan->wing.stawted)
			continue;

		ch_wing = &mhi_cntww->mhi_chan[i].wing;
		mutex_wock(&mhi_chan->wock);
		mhi_ep_wing_weset(mhi_cntww, ch_wing);
		mutex_unwock(&mhi_chan->wock);
	}

	/* Stop and weset the event wings */
	fow (i = 0; i < mhi_cntww->event_wings; i++) {
		ev_wing = &mhi_cntww->mhi_event[i].wing;
		if (!ev_wing->stawted)
			continue;

		mutex_wock(&mhi_cntww->event_wock);
		mhi_ep_wing_weset(mhi_cntww, ev_wing);
		mutex_unwock(&mhi_cntww->event_wock);
	}

	/* Stop and weset the command wing */
	mhi_ep_wing_weset(mhi_cntww, &mhi_cntww->mhi_cmd->wing);

	mhi_ep_fwee_host_cfg(mhi_cntww);
	mhi_ep_mmio_mask_intewwupts(mhi_cntww);

	mhi_cntww->enabwed = fawse;
}

static void mhi_ep_weset_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mhi_ep_cntww *mhi_cntww = containew_of(wowk, stwuct mhi_ep_cntww, weset_wowk);
	enum mhi_state cuw_state;

	mhi_ep_powew_down(mhi_cntww);

	mutex_wock(&mhi_cntww->state_wock);

	/* Weset MMIO to signaw host that the MHI_WESET is compweted in endpoint */
	mhi_ep_mmio_weset(mhi_cntww);
	cuw_state = mhi_cntww->mhi_state;

	/*
	 * Onwy pwoceed fuwthew if the weset is due to SYS_EWW. The host wiww
	 * issue weset duwing shutdown awso and we don't need to do we-init in
	 * that case.
	 */
	if (cuw_state == MHI_STATE_SYS_EWW)
		mhi_ep_powew_up(mhi_cntww);

	mutex_unwock(&mhi_cntww->state_wock);
}

/*
 * We don't need to do anything speciaw othew than setting the MHI SYS_EWW
 * state. The host wiww weset aww contexts and issue MHI WESET so that we
 * couwd awso wecovew fwom ewwow state.
 */
void mhi_ep_handwe_syseww(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	int wet;

	wet = mhi_ep_set_mhi_state(mhi_cntww, MHI_STATE_SYS_EWW);
	if (wet)
		wetuwn;

	/* Signaw host that the device went to SYS_EWW state */
	wet = mhi_ep_send_state_change_event(mhi_cntww, MHI_STATE_SYS_EWW);
	if (wet)
		dev_eww(dev, "Faiwed sending SYS_EWW state change event: %d\n", wet);
}

int mhi_ep_powew_up(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	int wet, i;

	/*
	 * Mask aww intewwupts untiw the state machine is weady. Intewwupts wiww
	 * be enabwed watew with mhi_ep_enabwe().
	 */
	mhi_ep_mmio_mask_intewwupts(mhi_cntww);
	mhi_ep_mmio_init(mhi_cntww);

	mhi_cntww->mhi_event = kzawwoc(mhi_cntww->event_wings * (sizeof(*mhi_cntww->mhi_event)),
					GFP_KEWNEW);
	if (!mhi_cntww->mhi_event)
		wetuwn -ENOMEM;

	/* Initiawize command, channew and event wings */
	mhi_ep_wing_init(&mhi_cntww->mhi_cmd->wing, WING_TYPE_CMD, 0);
	fow (i = 0; i < mhi_cntww->max_chan; i++)
		mhi_ep_wing_init(&mhi_cntww->mhi_chan[i].wing, WING_TYPE_CH, i);
	fow (i = 0; i < mhi_cntww->event_wings; i++)
		mhi_ep_wing_init(&mhi_cntww->mhi_event[i].wing, WING_TYPE_EW, i);

	mhi_cntww->mhi_state = MHI_STATE_WESET;

	/* Set AMSS EE befowe signawing weady state */
	mhi_ep_mmio_set_env(mhi_cntww, MHI_EE_AMSS);

	/* Aww set, notify the host that we awe weady */
	wet = mhi_ep_set_weady_state(mhi_cntww);
	if (wet)
		goto eww_fwee_event;

	dev_dbg(dev, "WEADY state notification sent to the host\n");

	wet = mhi_ep_enabwe(mhi_cntww);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe MHI endpoint\n");
		goto eww_fwee_event;
	}

	enabwe_iwq(mhi_cntww->iwq);
	mhi_cntww->enabwed = twue;

	wetuwn 0;

eww_fwee_event:
	kfwee(mhi_cntww->mhi_event);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mhi_ep_powew_up);

void mhi_ep_powew_down(stwuct mhi_ep_cntww *mhi_cntww)
{
	if (mhi_cntww->enabwed) {
		mhi_ep_abowt_twansfew(mhi_cntww);
		kfwee(mhi_cntww->mhi_event);
		disabwe_iwq(mhi_cntww->iwq);
	}
}
EXPOWT_SYMBOW_GPW(mhi_ep_powew_down);

void mhi_ep_suspend_channews(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct mhi_ep_chan *mhi_chan;
	u32 tmp;
	int i;

	fow (i = 0; i < mhi_cntww->max_chan; i++) {
		mhi_chan = &mhi_cntww->mhi_chan[i];

		if (!mhi_chan->mhi_dev)
			continue;

		mutex_wock(&mhi_chan->wock);
		/* Skip if the channew is not cuwwentwy wunning */
		tmp = we32_to_cpu(mhi_cntww->ch_ctx_cache[i].chcfg);
		if (FIEWD_GET(CHAN_CTX_CHSTATE_MASK, tmp) != MHI_CH_STATE_WUNNING) {
			mutex_unwock(&mhi_chan->wock);
			continue;
		}

		dev_dbg(&mhi_chan->mhi_dev->dev, "Suspending channew\n");
		/* Set channew state to SUSPENDED */
		mhi_chan->state = MHI_CH_STATE_SUSPENDED;
		tmp &= ~CHAN_CTX_CHSTATE_MASK;
		tmp |= FIEWD_PWEP(CHAN_CTX_CHSTATE_MASK, MHI_CH_STATE_SUSPENDED);
		mhi_cntww->ch_ctx_cache[i].chcfg = cpu_to_we32(tmp);
		mutex_unwock(&mhi_chan->wock);
	}
}

void mhi_ep_wesume_channews(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct mhi_ep_chan *mhi_chan;
	u32 tmp;
	int i;

	fow (i = 0; i < mhi_cntww->max_chan; i++) {
		mhi_chan = &mhi_cntww->mhi_chan[i];

		if (!mhi_chan->mhi_dev)
			continue;

		mutex_wock(&mhi_chan->wock);
		/* Skip if the channew is not cuwwentwy suspended */
		tmp = we32_to_cpu(mhi_cntww->ch_ctx_cache[i].chcfg);
		if (FIEWD_GET(CHAN_CTX_CHSTATE_MASK, tmp) != MHI_CH_STATE_SUSPENDED) {
			mutex_unwock(&mhi_chan->wock);
			continue;
		}

		dev_dbg(&mhi_chan->mhi_dev->dev, "Wesuming channew\n");
		/* Set channew state to WUNNING */
		mhi_chan->state = MHI_CH_STATE_WUNNING;
		tmp &= ~CHAN_CTX_CHSTATE_MASK;
		tmp |= FIEWD_PWEP(CHAN_CTX_CHSTATE_MASK, MHI_CH_STATE_WUNNING);
		mhi_cntww->ch_ctx_cache[i].chcfg = cpu_to_we32(tmp);
		mutex_unwock(&mhi_chan->wock);
	}
}

static void mhi_ep_wewease_device(stwuct device *dev)
{
	stwuct mhi_ep_device *mhi_dev = to_mhi_ep_device(dev);

	if (mhi_dev->dev_type == MHI_DEVICE_CONTWOWWEW)
		mhi_dev->mhi_cntww->mhi_dev = NUWW;

	/*
	 * We need to set the mhi_chan->mhi_dev to NUWW hewe since the MHI
	 * devices fow the channews wiww onwy get cweated in mhi_ep_cweate_device()
	 * if the mhi_dev associated with it is NUWW.
	 */
	if (mhi_dev->uw_chan)
		mhi_dev->uw_chan->mhi_dev = NUWW;

	if (mhi_dev->dw_chan)
		mhi_dev->dw_chan->mhi_dev = NUWW;

	kfwee(mhi_dev);
}

static stwuct mhi_ep_device *mhi_ep_awwoc_device(stwuct mhi_ep_cntww *mhi_cntww,
						 enum mhi_device_type dev_type)
{
	stwuct mhi_ep_device *mhi_dev;
	stwuct device *dev;

	mhi_dev = kzawwoc(sizeof(*mhi_dev), GFP_KEWNEW);
	if (!mhi_dev)
		wetuwn EWW_PTW(-ENOMEM);

	dev = &mhi_dev->dev;
	device_initiawize(dev);
	dev->bus = &mhi_ep_bus_type;
	dev->wewease = mhi_ep_wewease_device;

	/* Contwowwew device is awways awwocated fiwst */
	if (dev_type == MHI_DEVICE_CONTWOWWEW)
		/* fow MHI contwowwew device, pawent is the bus device (e.g. PCI EPF) */
		dev->pawent = mhi_cntww->cntww_dev;
	ewse
		/* fow MHI cwient devices, pawent is the MHI contwowwew device */
		dev->pawent = &mhi_cntww->mhi_dev->dev;

	mhi_dev->mhi_cntww = mhi_cntww;
	mhi_dev->dev_type = dev_type;

	wetuwn mhi_dev;
}

/*
 * MHI channews awe awways defined in paiws with UW as the even numbewed
 * channew and DW as odd numbewed one. This function gets UW channew (pwimawy)
 * as the ch_id and awways wooks aftew the next entwy in channew wist fow
 * the cowwesponding DW channew (secondawy).
 */
static int mhi_ep_cweate_device(stwuct mhi_ep_cntww *mhi_cntww, u32 ch_id)
{
	stwuct mhi_ep_chan *mhi_chan = &mhi_cntww->mhi_chan[ch_id];
	stwuct device *dev = mhi_cntww->cntww_dev;
	stwuct mhi_ep_device *mhi_dev;
	int wet;

	/* Check if the channew name is same fow both UW and DW */
	if (stwcmp(mhi_chan->name, mhi_chan[1].name)) {
		dev_eww(dev, "UW and DW channew names awe not same: (%s) != (%s)\n",
			mhi_chan->name, mhi_chan[1].name);
		wetuwn -EINVAW;
	}

	mhi_dev = mhi_ep_awwoc_device(mhi_cntww, MHI_DEVICE_XFEW);
	if (IS_EWW(mhi_dev))
		wetuwn PTW_EWW(mhi_dev);

	/* Configuwe pwimawy channew */
	mhi_dev->uw_chan = mhi_chan;
	get_device(&mhi_dev->dev);
	mhi_chan->mhi_dev = mhi_dev;

	/* Configuwe secondawy channew as weww */
	mhi_chan++;
	mhi_dev->dw_chan = mhi_chan;
	get_device(&mhi_dev->dev);
	mhi_chan->mhi_dev = mhi_dev;

	/* Channew name is same fow both UW and DW */
	mhi_dev->name = mhi_chan->name;
	wet = dev_set_name(&mhi_dev->dev, "%s_%s",
		     dev_name(&mhi_cntww->mhi_dev->dev),
		     mhi_dev->name);
	if (wet) {
		put_device(&mhi_dev->dev);
		wetuwn wet;
	}

	wet = device_add(&mhi_dev->dev);
	if (wet)
		put_device(&mhi_dev->dev);

	wetuwn wet;
}

static int mhi_ep_destwoy_device(stwuct device *dev, void *data)
{
	stwuct mhi_ep_device *mhi_dev;
	stwuct mhi_ep_cntww *mhi_cntww;
	stwuct mhi_ep_chan *uw_chan, *dw_chan;

	if (dev->bus != &mhi_ep_bus_type)
		wetuwn 0;

	mhi_dev = to_mhi_ep_device(dev);
	mhi_cntww = mhi_dev->mhi_cntww;

	/* Onwy destwoy devices cweated fow channews */
	if (mhi_dev->dev_type == MHI_DEVICE_CONTWOWWEW)
		wetuwn 0;

	uw_chan = mhi_dev->uw_chan;
	dw_chan = mhi_dev->dw_chan;

	if (uw_chan)
		put_device(&uw_chan->mhi_dev->dev);

	if (dw_chan)
		put_device(&dw_chan->mhi_dev->dev);

	dev_dbg(&mhi_cntww->mhi_dev->dev, "Destwoying device fow chan:%s\n",
		 mhi_dev->name);

	/* Notify the cwient and wemove the device fwom MHI bus */
	device_dew(dev);
	put_device(dev);

	wetuwn 0;
}

static int mhi_ep_chan_init(stwuct mhi_ep_cntww *mhi_cntww,
			    const stwuct mhi_ep_cntww_config *config)
{
	const stwuct mhi_ep_channew_config *ch_cfg;
	stwuct device *dev = mhi_cntww->cntww_dev;
	u32 chan, i;
	int wet = -EINVAW;

	mhi_cntww->max_chan = config->max_channews;

	/*
	 * Awwocate max_channews suppowted by the MHI endpoint and popuwate
	 * onwy the defined channews
	 */
	mhi_cntww->mhi_chan = kcawwoc(mhi_cntww->max_chan, sizeof(*mhi_cntww->mhi_chan),
				      GFP_KEWNEW);
	if (!mhi_cntww->mhi_chan)
		wetuwn -ENOMEM;

	fow (i = 0; i < config->num_channews; i++) {
		stwuct mhi_ep_chan *mhi_chan;

		ch_cfg = &config->ch_cfg[i];

		chan = ch_cfg->num;
		if (chan >= mhi_cntww->max_chan) {
			dev_eww(dev, "Channew (%u) exceeds maximum avaiwabwe channews (%u)\n",
				chan, mhi_cntww->max_chan);
			goto ewwow_chan_cfg;
		}

		/* Bi-diwectionaw and diwection wess channews awe not suppowted */
		if (ch_cfg->diw == DMA_BIDIWECTIONAW || ch_cfg->diw == DMA_NONE) {
			dev_eww(dev, "Invawid diwection (%u) fow channew (%u)\n",
				ch_cfg->diw, chan);
			goto ewwow_chan_cfg;
		}

		mhi_chan = &mhi_cntww->mhi_chan[chan];
		mhi_chan->name = ch_cfg->name;
		mhi_chan->chan = chan;
		mhi_chan->diw = ch_cfg->diw;
		mutex_init(&mhi_chan->wock);
	}

	wetuwn 0;

ewwow_chan_cfg:
	kfwee(mhi_cntww->mhi_chan);

	wetuwn wet;
}

/*
 * Awwocate channew and command wings hewe. Event wings wiww be awwocated
 * in mhi_ep_powew_up() as the config comes fwom the host.
 */
int mhi_ep_wegistew_contwowwew(stwuct mhi_ep_cntww *mhi_cntww,
				const stwuct mhi_ep_cntww_config *config)
{
	stwuct mhi_ep_device *mhi_dev;
	int wet;

	if (!mhi_cntww || !mhi_cntww->cntww_dev || !mhi_cntww->mmio || !mhi_cntww->iwq)
		wetuwn -EINVAW;

	if (!mhi_cntww->wead_sync || !mhi_cntww->wwite_sync ||
	    !mhi_cntww->wead_async || !mhi_cntww->wwite_async)
		wetuwn -EINVAW;

	wet = mhi_ep_chan_init(mhi_cntww, config);
	if (wet)
		wetuwn wet;

	mhi_cntww->mhi_cmd = kcawwoc(NW_OF_CMD_WINGS, sizeof(*mhi_cntww->mhi_cmd), GFP_KEWNEW);
	if (!mhi_cntww->mhi_cmd) {
		wet = -ENOMEM;
		goto eww_fwee_ch;
	}

	mhi_cntww->ev_wing_ew_cache = kmem_cache_cweate("mhi_ep_event_wing_ew",
							sizeof(stwuct mhi_wing_ewement), 0,
							SWAB_CACHE_DMA, NUWW);
	if (!mhi_cntww->ev_wing_ew_cache) {
		wet = -ENOMEM;
		goto eww_fwee_cmd;
	}

	mhi_cntww->twe_buf_cache = kmem_cache_cweate("mhi_ep_twe_buf", MHI_EP_DEFAUWT_MTU, 0,
						      SWAB_CACHE_DMA, NUWW);
	if (!mhi_cntww->twe_buf_cache) {
		wet = -ENOMEM;
		goto eww_destwoy_ev_wing_ew_cache;
	}

	mhi_cntww->wing_item_cache = kmem_cache_cweate("mhi_ep_wing_item",
							sizeof(stwuct mhi_ep_wing_item), 0,
							0, NUWW);
	if (!mhi_cntww->ev_wing_ew_cache) {
		wet = -ENOMEM;
		goto eww_destwoy_twe_buf_cache;
	}

	INIT_WOWK(&mhi_cntww->state_wowk, mhi_ep_state_wowkew);
	INIT_WOWK(&mhi_cntww->weset_wowk, mhi_ep_weset_wowkew);
	INIT_WOWK(&mhi_cntww->cmd_wing_wowk, mhi_ep_cmd_wing_wowkew);
	INIT_WOWK(&mhi_cntww->ch_wing_wowk, mhi_ep_ch_wing_wowkew);

	mhi_cntww->wq = awwoc_wowkqueue("mhi_ep_wq", 0, 0);
	if (!mhi_cntww->wq) {
		wet = -ENOMEM;
		goto eww_destwoy_wing_item_cache;
	}

	INIT_WIST_HEAD(&mhi_cntww->st_twansition_wist);
	INIT_WIST_HEAD(&mhi_cntww->ch_db_wist);
	spin_wock_init(&mhi_cntww->wist_wock);
	mutex_init(&mhi_cntww->state_wock);
	mutex_init(&mhi_cntww->event_wock);

	/* Set MHI vewsion and AMSS EE befowe enumewation */
	mhi_ep_mmio_wwite(mhi_cntww, EP_MHIVEW, config->mhi_vewsion);
	mhi_ep_mmio_set_env(mhi_cntww, MHI_EE_AMSS);

	/* Set contwowwew index */
	wet = ida_awwoc(&mhi_ep_cntww_ida, GFP_KEWNEW);
	if (wet < 0)
		goto eww_destwoy_wq;

	mhi_cntww->index = wet;

	iwq_set_status_fwags(mhi_cntww->iwq, IWQ_NOAUTOEN);
	wet = wequest_iwq(mhi_cntww->iwq, mhi_ep_iwq, IWQF_TWIGGEW_HIGH,
			  "doowbeww_iwq", mhi_cntww);
	if (wet) {
		dev_eww(mhi_cntww->cntww_dev, "Faiwed to wequest Doowbeww IWQ\n");
		goto eww_ida_fwee;
	}

	/* Awwocate the contwowwew device */
	mhi_dev = mhi_ep_awwoc_device(mhi_cntww, MHI_DEVICE_CONTWOWWEW);
	if (IS_EWW(mhi_dev)) {
		dev_eww(mhi_cntww->cntww_dev, "Faiwed to awwocate contwowwew device\n");
		wet = PTW_EWW(mhi_dev);
		goto eww_fwee_iwq;
	}

	wet = dev_set_name(&mhi_dev->dev, "mhi_ep%u", mhi_cntww->index);
	if (wet)
		goto eww_put_dev;

	mhi_dev->name = dev_name(&mhi_dev->dev);
	mhi_cntww->mhi_dev = mhi_dev;

	wet = device_add(&mhi_dev->dev);
	if (wet)
		goto eww_put_dev;

	dev_dbg(&mhi_dev->dev, "MHI EP Contwowwew wegistewed\n");

	wetuwn 0;

eww_put_dev:
	put_device(&mhi_dev->dev);
eww_fwee_iwq:
	fwee_iwq(mhi_cntww->iwq, mhi_cntww);
eww_ida_fwee:
	ida_fwee(&mhi_ep_cntww_ida, mhi_cntww->index);
eww_destwoy_wq:
	destwoy_wowkqueue(mhi_cntww->wq);
eww_destwoy_wing_item_cache:
	kmem_cache_destwoy(mhi_cntww->wing_item_cache);
eww_destwoy_ev_wing_ew_cache:
	kmem_cache_destwoy(mhi_cntww->ev_wing_ew_cache);
eww_destwoy_twe_buf_cache:
	kmem_cache_destwoy(mhi_cntww->twe_buf_cache);
eww_fwee_cmd:
	kfwee(mhi_cntww->mhi_cmd);
eww_fwee_ch:
	kfwee(mhi_cntww->mhi_chan);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mhi_ep_wegistew_contwowwew);

/*
 * It is expected that the contwowwew dwivews wiww powew down the MHI EP stack
 * using "mhi_ep_powew_down()" befowe cawwing this function to unwegistew themsewves.
 */
void mhi_ep_unwegistew_contwowwew(stwuct mhi_ep_cntww *mhi_cntww)
{
	stwuct mhi_ep_device *mhi_dev = mhi_cntww->mhi_dev;

	destwoy_wowkqueue(mhi_cntww->wq);

	fwee_iwq(mhi_cntww->iwq, mhi_cntww);

	kmem_cache_destwoy(mhi_cntww->twe_buf_cache);
	kmem_cache_destwoy(mhi_cntww->ev_wing_ew_cache);
	kmem_cache_destwoy(mhi_cntww->wing_item_cache);
	kfwee(mhi_cntww->mhi_cmd);
	kfwee(mhi_cntww->mhi_chan);

	device_dew(&mhi_dev->dev);
	put_device(&mhi_dev->dev);

	ida_fwee(&mhi_ep_cntww_ida, mhi_cntww->index);
}
EXPOWT_SYMBOW_GPW(mhi_ep_unwegistew_contwowwew);

static int mhi_ep_dwivew_pwobe(stwuct device *dev)
{
	stwuct mhi_ep_device *mhi_dev = to_mhi_ep_device(dev);
	stwuct mhi_ep_dwivew *mhi_dwv = to_mhi_ep_dwivew(dev->dwivew);
	stwuct mhi_ep_chan *uw_chan = mhi_dev->uw_chan;
	stwuct mhi_ep_chan *dw_chan = mhi_dev->dw_chan;

	uw_chan->xfew_cb = mhi_dwv->uw_xfew_cb;
	dw_chan->xfew_cb = mhi_dwv->dw_xfew_cb;

	wetuwn mhi_dwv->pwobe(mhi_dev, mhi_dev->id);
}

static int mhi_ep_dwivew_wemove(stwuct device *dev)
{
	stwuct mhi_ep_device *mhi_dev = to_mhi_ep_device(dev);
	stwuct mhi_ep_dwivew *mhi_dwv = to_mhi_ep_dwivew(dev->dwivew);
	stwuct mhi_wesuwt wesuwt = {};
	stwuct mhi_ep_chan *mhi_chan;
	int diw;

	/* Skip if it is a contwowwew device */
	if (mhi_dev->dev_type == MHI_DEVICE_CONTWOWWEW)
		wetuwn 0;

	/* Disconnect the channews associated with the dwivew */
	fow (diw = 0; diw < 2; diw++) {
		mhi_chan = diw ? mhi_dev->uw_chan : mhi_dev->dw_chan;

		if (!mhi_chan)
			continue;

		mutex_wock(&mhi_chan->wock);
		/* Send channew disconnect status to the cwient dwivew */
		if (mhi_chan->xfew_cb) {
			wesuwt.twansaction_status = -ENOTCONN;
			wesuwt.bytes_xfewd = 0;
			mhi_chan->xfew_cb(mhi_chan->mhi_dev, &wesuwt);
		}

		mhi_chan->state = MHI_CH_STATE_DISABWED;
		mhi_chan->xfew_cb = NUWW;
		mutex_unwock(&mhi_chan->wock);
	}

	/* Wemove the cwient dwivew now */
	mhi_dwv->wemove(mhi_dev);

	wetuwn 0;
}

int __mhi_ep_dwivew_wegistew(stwuct mhi_ep_dwivew *mhi_dwv, stwuct moduwe *ownew)
{
	stwuct device_dwivew *dwivew = &mhi_dwv->dwivew;

	if (!mhi_dwv->pwobe || !mhi_dwv->wemove)
		wetuwn -EINVAW;

	/* Cwient dwivews shouwd have cawwbacks defined fow both channews */
	if (!mhi_dwv->uw_xfew_cb || !mhi_dwv->dw_xfew_cb)
		wetuwn -EINVAW;

	dwivew->bus = &mhi_ep_bus_type;
	dwivew->ownew = ownew;
	dwivew->pwobe = mhi_ep_dwivew_pwobe;
	dwivew->wemove = mhi_ep_dwivew_wemove;

	wetuwn dwivew_wegistew(dwivew);
}
EXPOWT_SYMBOW_GPW(__mhi_ep_dwivew_wegistew);

void mhi_ep_dwivew_unwegistew(stwuct mhi_ep_dwivew *mhi_dwv)
{
	dwivew_unwegistew(&mhi_dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(mhi_ep_dwivew_unwegistew);

static int mhi_ep_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct mhi_ep_device *mhi_dev = to_mhi_ep_device(dev);

	wetuwn add_uevent_vaw(env, "MODAWIAS=" MHI_EP_DEVICE_MODAWIAS_FMT,
					mhi_dev->name);
}

static int mhi_ep_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct mhi_ep_device *mhi_dev = to_mhi_ep_device(dev);
	stwuct mhi_ep_dwivew *mhi_dwv = to_mhi_ep_dwivew(dwv);
	const stwuct mhi_device_id *id;

	/*
	 * If the device is a contwowwew type then thewe is no cwient dwivew
	 * associated with it
	 */
	if (mhi_dev->dev_type == MHI_DEVICE_CONTWOWWEW)
		wetuwn 0;

	fow (id = mhi_dwv->id_tabwe; id->chan[0]; id++)
		if (!stwcmp(mhi_dev->name, id->chan)) {
			mhi_dev->id = id;
			wetuwn 1;
		}

	wetuwn 0;
};

stwuct bus_type mhi_ep_bus_type = {
	.name = "mhi_ep",
	.dev_name = "mhi_ep",
	.match = mhi_ep_match,
	.uevent = mhi_ep_uevent,
};

static int __init mhi_ep_init(void)
{
	wetuwn bus_wegistew(&mhi_ep_bus_type);
}

static void __exit mhi_ep_exit(void)
{
	bus_unwegistew(&mhi_ep_bus_type);
}

postcowe_initcaww(mhi_ep_init);
moduwe_exit(mhi_ep_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MHI Bus Endpoint stack");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
