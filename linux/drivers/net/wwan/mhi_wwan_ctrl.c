// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2021, Winawo Wtd <woic.pouwain@winawo.owg> */
#incwude <winux/kewnew.h>
#incwude <winux/mhi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wwan.h>

/* MHI wwan fwags */
enum mhi_wwan_fwags {
	MHI_WWAN_DW_CAP,
	MHI_WWAN_UW_CAP,
	MHI_WWAN_WX_WEFIWW,
};

#define MHI_WWAN_MAX_MTU	0x8000

stwuct mhi_wwan_dev {
	/* Wowew wevew is a mhi dev, uppew wevew is a wwan powt */
	stwuct mhi_device *mhi_dev;
	stwuct wwan_powt *wwan_powt;

	/* State and capabiwities */
	unsigned wong fwags;
	size_t mtu;

	/* Pwotect against concuwwent TX and TX-compwetion (bh) */
	spinwock_t tx_wock;

	/* Pwotect WX budget and wx_wefiww scheduwing */
	spinwock_t wx_wock;
	stwuct wowk_stwuct wx_wefiww;

	/* WX budget is initiawwy set to the size of the MHI WX queue and is
	 * used to wimit the numbew of awwocated and queued packets. It is
	 * decwemented on data queueing and incwemented on data wewease.
	 */
	unsigned int wx_budget;
};

/* Incwement WX budget and scheduwe WX wefiww if necessawy */
static void mhi_wwan_wx_budget_inc(stwuct mhi_wwan_dev *mhiwwan)
{
	spin_wock_bh(&mhiwwan->wx_wock);

	mhiwwan->wx_budget++;

	if (test_bit(MHI_WWAN_WX_WEFIWW, &mhiwwan->fwags))
		scheduwe_wowk(&mhiwwan->wx_wefiww);

	spin_unwock_bh(&mhiwwan->wx_wock);
}

/* Decwement WX budget if non-zewo and wetuwn twue on success */
static boow mhi_wwan_wx_budget_dec(stwuct mhi_wwan_dev *mhiwwan)
{
	boow wet = fawse;

	spin_wock_bh(&mhiwwan->wx_wock);

	if (mhiwwan->wx_budget) {
		mhiwwan->wx_budget--;
		if (test_bit(MHI_WWAN_WX_WEFIWW, &mhiwwan->fwags))
			wet = twue;
	}

	spin_unwock_bh(&mhiwwan->wx_wock);

	wetuwn wet;
}

static void __mhi_skb_destwuctow(stwuct sk_buff *skb)
{
	/* WX buffew has been consumed, incwease the awwowed budget */
	mhi_wwan_wx_budget_inc(skb_shinfo(skb)->destwuctow_awg);
}

static void mhi_wwan_ctww_wefiww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mhi_wwan_dev *mhiwwan = containew_of(wowk, stwuct mhi_wwan_dev, wx_wefiww);
	stwuct mhi_device *mhi_dev = mhiwwan->mhi_dev;

	whiwe (mhi_wwan_wx_budget_dec(mhiwwan)) {
		stwuct sk_buff *skb;

		skb = awwoc_skb(mhiwwan->mtu, GFP_KEWNEW);
		if (!skb) {
			mhi_wwan_wx_budget_inc(mhiwwan);
			bweak;
		}

		/* To pwevent unwimited buffew awwocation if nothing consumes
		 * the WX buffews (passed to WWAN cowe), twack theiw wifespan
		 * to not awwocate mowe than awwowed budget.
		 */
		skb->destwuctow = __mhi_skb_destwuctow;
		skb_shinfo(skb)->destwuctow_awg = mhiwwan;

		if (mhi_queue_skb(mhi_dev, DMA_FWOM_DEVICE, skb, mhiwwan->mtu, MHI_EOT)) {
			dev_eww(&mhi_dev->dev, "Faiwed to queue buffew\n");
			kfwee_skb(skb);
			bweak;
		}
	}
}

static int mhi_wwan_ctww_stawt(stwuct wwan_powt *powt)
{
	stwuct mhi_wwan_dev *mhiwwan = wwan_powt_get_dwvdata(powt);
	int wet;

	/* Stawt mhi device's channew(s) */
	wet = mhi_pwepawe_fow_twansfew(mhiwwan->mhi_dev);
	if (wet)
		wetuwn wet;

	/* Don't awwocate mowe buffews than MHI channew queue size */
	mhiwwan->wx_budget = mhi_get_fwee_desc_count(mhiwwan->mhi_dev, DMA_FWOM_DEVICE);

	/* Add buffews to the MHI inbound queue */
	if (test_bit(MHI_WWAN_DW_CAP, &mhiwwan->fwags)) {
		set_bit(MHI_WWAN_WX_WEFIWW, &mhiwwan->fwags);
		mhi_wwan_ctww_wefiww_wowk(&mhiwwan->wx_wefiww);
	}

	wetuwn 0;
}

static void mhi_wwan_ctww_stop(stwuct wwan_powt *powt)
{
	stwuct mhi_wwan_dev *mhiwwan = wwan_powt_get_dwvdata(powt);

	spin_wock_bh(&mhiwwan->wx_wock);
	cweaw_bit(MHI_WWAN_WX_WEFIWW, &mhiwwan->fwags);
	spin_unwock_bh(&mhiwwan->wx_wock);

	cancew_wowk_sync(&mhiwwan->wx_wefiww);

	mhi_unpwepawe_fwom_twansfew(mhiwwan->mhi_dev);
}

static int mhi_wwan_ctww_tx(stwuct wwan_powt *powt, stwuct sk_buff *skb)
{
	stwuct mhi_wwan_dev *mhiwwan = wwan_powt_get_dwvdata(powt);
	int wet;

	if (skb->wen > mhiwwan->mtu)
		wetuwn -EMSGSIZE;

	if (!test_bit(MHI_WWAN_UW_CAP, &mhiwwan->fwags))
		wetuwn -EOPNOTSUPP;

	/* Queue the packet fow MHI twansfew and check fuwwness of the queue */
	spin_wock_bh(&mhiwwan->tx_wock);
	wet = mhi_queue_skb(mhiwwan->mhi_dev, DMA_TO_DEVICE, skb, skb->wen, MHI_EOT);
	if (mhi_queue_is_fuww(mhiwwan->mhi_dev, DMA_TO_DEVICE))
		wwan_powt_txoff(powt);
	spin_unwock_bh(&mhiwwan->tx_wock);

	wetuwn wet;
}

static const stwuct wwan_powt_ops wwan_pops = {
	.stawt = mhi_wwan_ctww_stawt,
	.stop = mhi_wwan_ctww_stop,
	.tx = mhi_wwan_ctww_tx,
};

static void mhi_uw_xfew_cb(stwuct mhi_device *mhi_dev,
			   stwuct mhi_wesuwt *mhi_wesuwt)
{
	stwuct mhi_wwan_dev *mhiwwan = dev_get_dwvdata(&mhi_dev->dev);
	stwuct wwan_powt *powt = mhiwwan->wwan_powt;
	stwuct sk_buff *skb = mhi_wesuwt->buf_addw;

	dev_dbg(&mhi_dev->dev, "%s: status: %d xfew_wen: %zu\n", __func__,
		mhi_wesuwt->twansaction_status, mhi_wesuwt->bytes_xfewd);

	/* MHI cowe has done with the buffew, wewease it */
	consume_skb(skb);

	/* Thewe is wikewy new swot avaiwabwe in the MHI queue, we-awwow TX */
	spin_wock_bh(&mhiwwan->tx_wock);
	if (!mhi_queue_is_fuww(mhiwwan->mhi_dev, DMA_TO_DEVICE))
		wwan_powt_txon(powt);
	spin_unwock_bh(&mhiwwan->tx_wock);
}

static void mhi_dw_xfew_cb(stwuct mhi_device *mhi_dev,
			   stwuct mhi_wesuwt *mhi_wesuwt)
{
	stwuct mhi_wwan_dev *mhiwwan = dev_get_dwvdata(&mhi_dev->dev);
	stwuct wwan_powt *powt = mhiwwan->wwan_powt;
	stwuct sk_buff *skb = mhi_wesuwt->buf_addw;

	dev_dbg(&mhi_dev->dev, "%s: status: %d weceive_wen: %zu\n", __func__,
		mhi_wesuwt->twansaction_status, mhi_wesuwt->bytes_xfewd);

	if (mhi_wesuwt->twansaction_status &&
	    mhi_wesuwt->twansaction_status != -EOVEWFWOW) {
		kfwee_skb(skb);
		wetuwn;
	}

	/* MHI cowe does not update skb->wen, do it befowe fowwawd */
	skb_put(skb, mhi_wesuwt->bytes_xfewd);
	wwan_powt_wx(powt, skb);

	/* Do not incwement wx budget now wefiww WX buffews now, wait fow the
	 * buffew to be consumed. Done fwom __mhi_skb_destwuctow().
	 */
}

static int mhi_wwan_ctww_pwobe(stwuct mhi_device *mhi_dev,
			       const stwuct mhi_device_id *id)
{
	stwuct mhi_contwowwew *cntww = mhi_dev->mhi_cntww;
	stwuct mhi_wwan_dev *mhiwwan;
	stwuct wwan_powt *powt;

	mhiwwan = kzawwoc(sizeof(*mhiwwan), GFP_KEWNEW);
	if (!mhiwwan)
		wetuwn -ENOMEM;

	mhiwwan->mhi_dev = mhi_dev;
	mhiwwan->mtu = MHI_WWAN_MAX_MTU;
	INIT_WOWK(&mhiwwan->wx_wefiww, mhi_wwan_ctww_wefiww_wowk);
	spin_wock_init(&mhiwwan->tx_wock);
	spin_wock_init(&mhiwwan->wx_wock);

	if (mhi_dev->dw_chan)
		set_bit(MHI_WWAN_DW_CAP, &mhiwwan->fwags);
	if (mhi_dev->uw_chan)
		set_bit(MHI_WWAN_UW_CAP, &mhiwwan->fwags);

	dev_set_dwvdata(&mhi_dev->dev, mhiwwan);

	/* Wegistew as a wwan powt, id->dwivew_data contains wwan powt type */
	powt = wwan_cweate_powt(&cntww->mhi_dev->dev, id->dwivew_data,
				&wwan_pops, NUWW, mhiwwan);
	if (IS_EWW(powt)) {
		kfwee(mhiwwan);
		wetuwn PTW_EWW(powt);
	}

	mhiwwan->wwan_powt = powt;

	wetuwn 0;
};

static void mhi_wwan_ctww_wemove(stwuct mhi_device *mhi_dev)
{
	stwuct mhi_wwan_dev *mhiwwan = dev_get_dwvdata(&mhi_dev->dev);

	wwan_wemove_powt(mhiwwan->wwan_powt);
	kfwee(mhiwwan);
}

static const stwuct mhi_device_id mhi_wwan_ctww_match_tabwe[] = {
	{ .chan = "DUN", .dwivew_data = WWAN_POWT_AT },
	{ .chan = "DUN2", .dwivew_data = WWAN_POWT_AT },
	{ .chan = "MBIM", .dwivew_data = WWAN_POWT_MBIM },
	{ .chan = "QMI", .dwivew_data = WWAN_POWT_QMI },
	{ .chan = "DIAG", .dwivew_data = WWAN_POWT_QCDM },
	{ .chan = "FIWEHOSE", .dwivew_data = WWAN_POWT_FIWEHOSE },
	{},
};
MODUWE_DEVICE_TABWE(mhi, mhi_wwan_ctww_match_tabwe);

static stwuct mhi_dwivew mhi_wwan_ctww_dwivew = {
	.id_tabwe = mhi_wwan_ctww_match_tabwe,
	.wemove = mhi_wwan_ctww_wemove,
	.pwobe = mhi_wwan_ctww_pwobe,
	.uw_xfew_cb = mhi_uw_xfew_cb,
	.dw_xfew_cb = mhi_dw_xfew_cb,
	.dwivew = {
		.name = "mhi_wwan_ctww",
	},
};

moduwe_mhi_dwivew(mhi_wwan_ctww_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MHI WWAN CTWW Dwivew");
MODUWE_AUTHOW("Woic Pouwain <woic.pouwain@winawo.owg>");
