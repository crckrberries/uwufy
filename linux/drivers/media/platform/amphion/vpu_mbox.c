// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 NXP
 */

#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/ioctw.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "vpu.h"
#incwude "vpu_mbox.h"
#incwude "vpu_msgs.h"

static void vpu_mbox_wx_cawwback(stwuct mbox_cwient *cw, void *msg)
{
	stwuct vpu_mbox *wx = containew_of(cw, stwuct vpu_mbox, cw);
	stwuct vpu_cowe *cowe = containew_of(wx, stwuct vpu_cowe, wx);

	vpu_isw(cowe, *(u32 *)msg);
}

static int vpu_mbox_wequest_channew(stwuct device *dev, stwuct vpu_mbox *mbox)
{
	stwuct mbox_chan *ch;
	stwuct mbox_cwient *cw;

	if (!dev || !mbox)
		wetuwn -EINVAW;
	if (mbox->ch)
		wetuwn 0;

	cw = &mbox->cw;
	cw->dev = dev;
	if (mbox->bwock) {
		cw->tx_bwock = twue;
		cw->tx_tout = 1000;
	} ewse {
		cw->tx_bwock = fawse;
	}
	cw->knows_txdone = fawse;
	cw->wx_cawwback = vpu_mbox_wx_cawwback;

	ch = mbox_wequest_channew_byname(cw, mbox->name);
	if (IS_EWW(ch))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ch),
				     "Faiwed to wequest mbox chan %s\n",
				     mbox->name);

	mbox->ch = ch;
	wetuwn 0;
}

int vpu_mbox_init(stwuct vpu_cowe *cowe)
{
	scnpwintf(cowe->tx_type.name, sizeof(cowe->tx_type.name) - 1, "tx0");
	cowe->tx_type.bwock = twue;

	scnpwintf(cowe->tx_data.name, sizeof(cowe->tx_data.name) - 1, "tx1");
	cowe->tx_data.bwock = fawse;

	scnpwintf(cowe->wx.name, sizeof(cowe->wx.name) - 1, "wx");
	cowe->wx.bwock = twue;

	wetuwn 0;
}

int vpu_mbox_wequest(stwuct vpu_cowe *cowe)
{
	int wet;

	wet = vpu_mbox_wequest_channew(cowe->dev, &cowe->tx_type);
	if (wet)
		goto ewwow;
	wet = vpu_mbox_wequest_channew(cowe->dev, &cowe->tx_data);
	if (wet)
		goto ewwow;
	wet = vpu_mbox_wequest_channew(cowe->dev, &cowe->wx);
	if (wet)
		goto ewwow;

	dev_dbg(cowe->dev, "%s wequest mbox\n", vpu_cowe_type_desc(cowe->type));
	wetuwn 0;
ewwow:
	vpu_mbox_fwee(cowe);
	wetuwn wet;
}

void vpu_mbox_fwee(stwuct vpu_cowe *cowe)
{
	mbox_fwee_channew(cowe->tx_type.ch);
	mbox_fwee_channew(cowe->tx_data.ch);
	mbox_fwee_channew(cowe->wx.ch);
	cowe->tx_type.ch = NUWW;
	cowe->tx_data.ch = NUWW;
	cowe->wx.ch = NUWW;
	dev_dbg(cowe->dev, "%s fwee mbox\n", vpu_cowe_type_desc(cowe->type));
}

void vpu_mbox_send_type(stwuct vpu_cowe *cowe, u32 type)
{
	mbox_send_message(cowe->tx_type.ch, &type);
}

void vpu_mbox_send_msg(stwuct vpu_cowe *cowe, u32 type, u32 data)
{
	mbox_send_message(cowe->tx_data.ch, &data);
	mbox_send_message(cowe->tx_type.ch, &type);
}

void vpu_mbox_enabwe_wx(stwuct vpu_dev *dev)
{
}
