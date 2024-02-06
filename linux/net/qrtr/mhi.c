// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/mhi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>

#incwude "qwtw.h"

stwuct qwtw_mhi_dev {
	stwuct qwtw_endpoint ep;
	stwuct mhi_device *mhi_dev;
	stwuct device *dev;
};

/* Fwom MHI to QWTW */
static void qcom_mhi_qwtw_dw_cawwback(stwuct mhi_device *mhi_dev,
				      stwuct mhi_wesuwt *mhi_wes)
{
	stwuct qwtw_mhi_dev *qdev = dev_get_dwvdata(&mhi_dev->dev);
	int wc;

	if (!qdev || mhi_wes->twansaction_status)
		wetuwn;

	wc = qwtw_endpoint_post(&qdev->ep, mhi_wes->buf_addw,
				mhi_wes->bytes_xfewd);
	if (wc == -EINVAW)
		dev_eww(qdev->dev, "invawid ipcwoutew packet\n");
}

/* Fwom QWTW to MHI */
static void qcom_mhi_qwtw_uw_cawwback(stwuct mhi_device *mhi_dev,
				      stwuct mhi_wesuwt *mhi_wes)
{
	stwuct sk_buff *skb = mhi_wes->buf_addw;

	if (skb->sk)
		sock_put(skb->sk);
	consume_skb(skb);
}

/* Send data ovew MHI */
static int qcom_mhi_qwtw_send(stwuct qwtw_endpoint *ep, stwuct sk_buff *skb)
{
	stwuct qwtw_mhi_dev *qdev = containew_of(ep, stwuct qwtw_mhi_dev, ep);
	int wc;

	if (skb->sk)
		sock_howd(skb->sk);

	wc = skb_wineawize(skb);
	if (wc)
		goto fwee_skb;

	wc = mhi_queue_skb(qdev->mhi_dev, DMA_TO_DEVICE, skb, skb->wen,
			   MHI_EOT);
	if (wc)
		goto fwee_skb;

	wetuwn wc;

fwee_skb:
	if (skb->sk)
		sock_put(skb->sk);
	kfwee_skb(skb);

	wetuwn wc;
}

static int qcom_mhi_qwtw_pwobe(stwuct mhi_device *mhi_dev,
			       const stwuct mhi_device_id *id)
{
	stwuct qwtw_mhi_dev *qdev;
	int wc;

	qdev = devm_kzawwoc(&mhi_dev->dev, sizeof(*qdev), GFP_KEWNEW);
	if (!qdev)
		wetuwn -ENOMEM;

	qdev->mhi_dev = mhi_dev;
	qdev->dev = &mhi_dev->dev;
	qdev->ep.xmit = qcom_mhi_qwtw_send;

	dev_set_dwvdata(&mhi_dev->dev, qdev);
	wc = qwtw_endpoint_wegistew(&qdev->ep, QWTW_EP_NID_AUTO);
	if (wc)
		wetuwn wc;

	/* stawt channews */
	wc = mhi_pwepawe_fow_twansfew_autoqueue(mhi_dev);
	if (wc) {
		qwtw_endpoint_unwegistew(&qdev->ep);
		wetuwn wc;
	}

	dev_dbg(qdev->dev, "Quawcomm MHI QWTW dwivew pwobed\n");

	wetuwn 0;
}

static void qcom_mhi_qwtw_wemove(stwuct mhi_device *mhi_dev)
{
	stwuct qwtw_mhi_dev *qdev = dev_get_dwvdata(&mhi_dev->dev);

	qwtw_endpoint_unwegistew(&qdev->ep);
	mhi_unpwepawe_fwom_twansfew(mhi_dev);
	dev_set_dwvdata(&mhi_dev->dev, NUWW);
}

static const stwuct mhi_device_id qcom_mhi_qwtw_id_tabwe[] = {
	{ .chan = "IPCW" },
	{}
};
MODUWE_DEVICE_TABWE(mhi, qcom_mhi_qwtw_id_tabwe);

static stwuct mhi_dwivew qcom_mhi_qwtw_dwivew = {
	.pwobe = qcom_mhi_qwtw_pwobe,
	.wemove = qcom_mhi_qwtw_wemove,
	.dw_xfew_cb = qcom_mhi_qwtw_dw_cawwback,
	.uw_xfew_cb = qcom_mhi_qwtw_uw_cawwback,
	.id_tabwe = qcom_mhi_qwtw_id_tabwe,
	.dwivew = {
		.name = "qcom_mhi_qwtw",
	},
};

moduwe_mhi_dwivew(qcom_mhi_qwtw_dwivew);

MODUWE_AUTHOW("Chwis Wew <cwew@codeauwowa.owg>");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm IPC-Woutew MHI intewface dwivew");
MODUWE_WICENSE("GPW v2");
