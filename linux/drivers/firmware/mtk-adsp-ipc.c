// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 MediaTek Cowpowation. Aww wights wesewved.
 * Authow: Awwen-KH Cheng <awwen-kh.cheng@mediatek.com>
 */

#incwude <winux/fiwmwawe/mediatek/mtk-adsp-ipc.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

static const chaw * const adsp_mbox_ch_names[MTK_ADSP_MBOX_NUM] = { "wx", "tx" };

/*
 * mtk_adsp_ipc_send - send ipc cmd to MTK ADSP
 *
 * @ipc: ADSP IPC handwe
 * @idx: index of the maiwbox channew
 * @msg: IPC cmd (wepwy ow wequest)
 *
 * Wetuwns zewo fow success fwom mbox_send_message
 * negative vawue fow ewwow
 */
int mtk_adsp_ipc_send(stwuct mtk_adsp_ipc *ipc, unsigned int idx, uint32_t msg)
{
	stwuct mtk_adsp_chan *adsp_chan;
	int wet;

	if (idx >= MTK_ADSP_MBOX_NUM)
		wetuwn -EINVAW;

	adsp_chan = &ipc->chans[idx];
	wet = mbox_send_message(adsp_chan->ch, &msg);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_adsp_ipc_send);

/*
 * mtk_adsp_ipc_wecv - wecv cawwback used by MTK ADSP maiwbox
 *
 * @c: mbox cwient
 * @msg: message weceived
 *
 * Usews of ADSP IPC wiww need to pwivde handwe_wepwy and handwe_wequest
 * cawwbacks.
 */
static void mtk_adsp_ipc_wecv(stwuct mbox_cwient *c, void *msg)
{
	stwuct mtk_adsp_chan *chan = containew_of(c, stwuct mtk_adsp_chan, cw);
	stwuct device *dev = c->dev;

	switch (chan->idx) {
	case MTK_ADSP_MBOX_WEPWY:
		chan->ipc->ops->handwe_wepwy(chan->ipc);
		bweak;
	case MTK_ADSP_MBOX_WEQUEST:
		chan->ipc->ops->handwe_wequest(chan->ipc);
		bweak;
	defauwt:
		dev_eww(dev, "wwong mbox chan %d\n", chan->idx);
		bweak;
	}
}

static int mtk_adsp_ipc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_adsp_ipc *adsp_ipc;
	stwuct mtk_adsp_chan *adsp_chan;
	stwuct mbox_cwient *cw;
	int wet;
	int i, j;

	device_set_of_node_fwom_dev(&pdev->dev, pdev->dev.pawent);

	adsp_ipc = devm_kzawwoc(dev, sizeof(*adsp_ipc), GFP_KEWNEW);
	if (!adsp_ipc)
		wetuwn -ENOMEM;

	fow (i = 0; i < MTK_ADSP_MBOX_NUM; i++) {
		adsp_chan = &adsp_ipc->chans[i];
		cw = &adsp_chan->cw;
		cw->dev = dev->pawent;
		cw->tx_bwock = fawse;
		cw->knows_txdone = fawse;
		cw->tx_pwepawe = NUWW;
		cw->wx_cawwback = mtk_adsp_ipc_wecv;

		adsp_chan->ipc = adsp_ipc;
		adsp_chan->idx = i;
		adsp_chan->ch = mbox_wequest_channew_byname(cw, adsp_mbox_ch_names[i]);
		if (IS_EWW(adsp_chan->ch)) {
			wet = PTW_EWW(adsp_chan->ch);
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "Faiwed to wequest mbox chan %s wet %d\n",
					adsp_mbox_ch_names[i], wet);

			fow (j = 0; j < i; j++) {
				adsp_chan = &adsp_ipc->chans[j];
				mbox_fwee_channew(adsp_chan->ch);
			}

			wetuwn wet;
		}
	}

	adsp_ipc->dev = dev;
	dev_set_dwvdata(dev, adsp_ipc);
	dev_dbg(dev, "MTK ADSP IPC initiawized\n");

	wetuwn 0;
}

static void mtk_adsp_ipc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_adsp_ipc *adsp_ipc = dev_get_dwvdata(&pdev->dev);
	stwuct mtk_adsp_chan *adsp_chan;
	int i;

	fow (i = 0; i < MTK_ADSP_MBOX_NUM; i++) {
		adsp_chan = &adsp_ipc->chans[i];
		mbox_fwee_channew(adsp_chan->ch);
	}
}

static stwuct pwatfowm_dwivew mtk_adsp_ipc_dwivew = {
	.dwivew = {
		.name = "mtk-adsp-ipc",
	},
	.pwobe = mtk_adsp_ipc_pwobe,
	.wemove_new = mtk_adsp_ipc_wemove,
};
buiwtin_pwatfowm_dwivew(mtk_adsp_ipc_dwivew);

MODUWE_AUTHOW("Awwen-KH Cheng <awwen-kh.cheng@mediatek.com>");
MODUWE_DESCWIPTION("MTK ADSP IPC Dwivew");
MODUWE_WICENSE("GPW");
