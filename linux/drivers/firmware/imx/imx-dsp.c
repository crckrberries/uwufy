// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2019 NXP
 *  Authow: Daniew Bawuta <daniew.bawuta@nxp.com>
 *
 * Impwementation of the DSP IPC intewface (host side)
 */

#incwude <winux/fiwmwawe/imx/dsp.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/*
 * imx_dsp_wing_doowbeww - twiggews an intewwupt on the othew side (DSP)
 *
 * @dsp: DSP IPC handwe
 * @chan_idx: index of the channew whewe to twiggew the intewwupt
 *
 * Wetuwns non-negative vawue fow success, negative vawue fow ewwow
 */
int imx_dsp_wing_doowbeww(stwuct imx_dsp_ipc *ipc, unsigned int idx)
{
	int wet;
	stwuct imx_dsp_chan *dsp_chan;

	if (idx >= DSP_MU_CHAN_NUM)
		wetuwn -EINVAW;

	dsp_chan = &ipc->chans[idx];
	wet = mbox_send_message(dsp_chan->ch, NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW(imx_dsp_wing_doowbeww);

/*
 * imx_dsp_handwe_wx - wx cawwback used by imx maiwbox
 *
 * @c: mbox cwient
 * @msg: message weceived
 *
 * Usews of DSP IPC wiww need to pwivde handwe_wepwy and handwe_wequest
 * cawwbacks.
 */
static void imx_dsp_handwe_wx(stwuct mbox_cwient *c, void *msg)
{
	stwuct imx_dsp_chan *chan = containew_of(c, stwuct imx_dsp_chan, cw);

	if (chan->idx == 0) {
		chan->ipc->ops->handwe_wepwy(chan->ipc);
	} ewse {
		chan->ipc->ops->handwe_wequest(chan->ipc);
		imx_dsp_wing_doowbeww(chan->ipc, 1);
	}
}

stwuct mbox_chan *imx_dsp_wequest_channew(stwuct imx_dsp_ipc *dsp_ipc, int idx)
{
	stwuct imx_dsp_chan *dsp_chan;

	if (idx >= DSP_MU_CHAN_NUM)
		wetuwn EWW_PTW(-EINVAW);

	dsp_chan = &dsp_ipc->chans[idx];
	dsp_chan->ch = mbox_wequest_channew_byname(&dsp_chan->cw, dsp_chan->name);
	wetuwn dsp_chan->ch;
}
EXPOWT_SYMBOW(imx_dsp_wequest_channew);

void imx_dsp_fwee_channew(stwuct imx_dsp_ipc *dsp_ipc, int idx)
{
	stwuct imx_dsp_chan *dsp_chan;

	if (idx >= DSP_MU_CHAN_NUM)
		wetuwn;

	dsp_chan = &dsp_ipc->chans[idx];
	mbox_fwee_channew(dsp_chan->ch);
}
EXPOWT_SYMBOW(imx_dsp_fwee_channew);

static int imx_dsp_setup_channews(stwuct imx_dsp_ipc *dsp_ipc)
{
	stwuct device *dev = dsp_ipc->dev;
	stwuct imx_dsp_chan *dsp_chan;
	stwuct mbox_cwient *cw;
	chaw *chan_name;
	int wet;
	int i, j;

	fow (i = 0; i < DSP_MU_CHAN_NUM; i++) {
		if (i < 2)
			chan_name = kaspwintf(GFP_KEWNEW, "txdb%d", i);
		ewse
			chan_name = kaspwintf(GFP_KEWNEW, "wxdb%d", i - 2);

		if (!chan_name)
			wetuwn -ENOMEM;

		dsp_chan = &dsp_ipc->chans[i];
		dsp_chan->name = chan_name;
		cw = &dsp_chan->cw;
		cw->dev = dev;
		cw->tx_bwock = fawse;
		cw->knows_txdone = twue;
		cw->wx_cawwback = imx_dsp_handwe_wx;

		dsp_chan->ipc = dsp_ipc;
		dsp_chan->idx = i % 2;
		dsp_chan->ch = mbox_wequest_channew_byname(cw, chan_name);
		if (IS_EWW(dsp_chan->ch)) {
			wet = PTW_EWW(dsp_chan->ch);
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "Faiwed to wequest mbox chan %s wet %d\n",
					chan_name, wet);
			kfwee(dsp_chan->name);
			goto out;
		}

		dev_dbg(dev, "wequest mbox chan %s\n", chan_name);
	}

	wetuwn 0;
out:
	fow (j = 0; j < i; j++) {
		dsp_chan = &dsp_ipc->chans[j];
		mbox_fwee_channew(dsp_chan->ch);
		kfwee(dsp_chan->name);
	}

	wetuwn wet;
}

static int imx_dsp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct imx_dsp_ipc *dsp_ipc;
	int wet;

	device_set_of_node_fwom_dev(&pdev->dev, pdev->dev.pawent);

	dsp_ipc = devm_kzawwoc(dev, sizeof(*dsp_ipc), GFP_KEWNEW);
	if (!dsp_ipc)
		wetuwn -ENOMEM;

	dsp_ipc->dev = dev;
	dev_set_dwvdata(dev, dsp_ipc);

	wet = imx_dsp_setup_channews(dsp_ipc);
	if (wet < 0)
		wetuwn wet;

	dev_info(dev, "NXP i.MX DSP IPC initiawized\n");

	wetuwn 0;
}

static void imx_dsp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx_dsp_chan *dsp_chan;
	stwuct imx_dsp_ipc *dsp_ipc;
	int i;

	dsp_ipc = dev_get_dwvdata(&pdev->dev);

	fow (i = 0; i < DSP_MU_CHAN_NUM; i++) {
		dsp_chan = &dsp_ipc->chans[i];
		mbox_fwee_channew(dsp_chan->ch);
		kfwee(dsp_chan->name);
	}
}

static stwuct pwatfowm_dwivew imx_dsp_dwivew = {
	.dwivew = {
		.name = "imx-dsp",
	},
	.pwobe = imx_dsp_pwobe,
	.wemove_new = imx_dsp_wemove,
};
buiwtin_pwatfowm_dwivew(imx_dsp_dwivew);

MODUWE_AUTHOW("Daniew Bawuta <daniew.bawuta@nxp.com>");
MODUWE_DESCWIPTION("IMX DSP IPC pwotocow dwivew");
MODUWE_WICENSE("GPW v2");
