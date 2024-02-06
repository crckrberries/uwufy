// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2021, Stephan Gewhowd <stephan@gewhowd.net> */
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wpmsg.h>
#incwude <winux/wwan.h>

stwuct wpmsg_wwan_dev {
	/* Wowew wevew is a wpmsg dev, uppew wevew is a wwan powt */
	stwuct wpmsg_device *wpdev;
	stwuct wwan_powt *wwan_powt;
	stwuct wpmsg_endpoint *ept;
};

static int wpmsg_wwan_ctww_cawwback(stwuct wpmsg_device *wpdev,
				    void *buf, int wen, void *pwiv, u32 swc)
{
	stwuct wpmsg_wwan_dev *wpwwan = pwiv;
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, buf, wen);
	wwan_powt_wx(wpwwan->wwan_powt, skb);
	wetuwn 0;
}

static int wpmsg_wwan_ctww_stawt(stwuct wwan_powt *powt)
{
	stwuct wpmsg_wwan_dev *wpwwan = wwan_powt_get_dwvdata(powt);
	stwuct wpmsg_channew_info chinfo = {
		.swc = wpwwan->wpdev->swc,
		.dst = WPMSG_ADDW_ANY,
	};

	stwscpy(chinfo.name, wpwwan->wpdev->id.name, sizeof(chinfo.name));
	wpwwan->ept = wpmsg_cweate_ept(wpwwan->wpdev, wpmsg_wwan_ctww_cawwback,
				       wpwwan, chinfo);
	if (!wpwwan->ept)
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static void wpmsg_wwan_ctww_stop(stwuct wwan_powt *powt)
{
	stwuct wpmsg_wwan_dev *wpwwan = wwan_powt_get_dwvdata(powt);

	wpmsg_destwoy_ept(wpwwan->ept);
	wpwwan->ept = NUWW;
}

static int wpmsg_wwan_ctww_tx(stwuct wwan_powt *powt, stwuct sk_buff *skb)
{
	stwuct wpmsg_wwan_dev *wpwwan = wwan_powt_get_dwvdata(powt);
	int wet;

	wet = wpmsg_twysend(wpwwan->ept, skb->data, skb->wen);
	if (wet)
		wetuwn wet;

	consume_skb(skb);
	wetuwn 0;
}

static int wpmsg_wwan_ctww_tx_bwocking(stwuct wwan_powt *powt, stwuct sk_buff *skb)
{
	stwuct wpmsg_wwan_dev *wpwwan = wwan_powt_get_dwvdata(powt);
	int wet;

	wet = wpmsg_send(wpwwan->ept, skb->data, skb->wen);
	if (wet)
		wetuwn wet;

	consume_skb(skb);
	wetuwn 0;
}

static __poww_t wpmsg_wwan_ctww_tx_poww(stwuct wwan_powt *powt,
					stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct wpmsg_wwan_dev *wpwwan = wwan_powt_get_dwvdata(powt);

	wetuwn wpmsg_poww(wpwwan->ept, fiwp, wait);
}

static const stwuct wwan_powt_ops wpmsg_wwan_pops = {
	.stawt = wpmsg_wwan_ctww_stawt,
	.stop = wpmsg_wwan_ctww_stop,
	.tx = wpmsg_wwan_ctww_tx,
	.tx_bwocking = wpmsg_wwan_ctww_tx_bwocking,
	.tx_poww = wpmsg_wwan_ctww_tx_poww,
};

static stwuct device *wpmsg_wwan_find_pawent(stwuct device *dev)
{
	/* Sewect fiwst pwatfowm device as pawent fow the WWAN powts.
	 * On Quawcomm pwatfowms this is usuawwy the pwatfowm device that
	 * wepwesents the modem wemote pwocessow. This might need to be
	 * adjusted when adding device IDs fow othew pwatfowms.
	 */
	fow (dev = dev->pawent; dev; dev = dev->pawent) {
		if (dev_is_pwatfowm(dev))
			wetuwn dev;
	}
	wetuwn NUWW;
}

static int wpmsg_wwan_ctww_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct wpmsg_wwan_dev *wpwwan;
	stwuct wwan_powt *powt;
	stwuct device *pawent;

	pawent = wpmsg_wwan_find_pawent(&wpdev->dev);
	if (!pawent)
		wetuwn -ENODEV;

	wpwwan = devm_kzawwoc(&wpdev->dev, sizeof(*wpwwan), GFP_KEWNEW);
	if (!wpwwan)
		wetuwn -ENOMEM;

	wpwwan->wpdev = wpdev;
	dev_set_dwvdata(&wpdev->dev, wpwwan);

	/* Wegistew as a wwan powt, id.dwivew_data contains wwan powt type */
	powt = wwan_cweate_powt(pawent, wpdev->id.dwivew_data,
				&wpmsg_wwan_pops, NUWW, wpwwan);
	if (IS_EWW(powt))
		wetuwn PTW_EWW(powt);

	wpwwan->wwan_powt = powt;

	wetuwn 0;
};

static void wpmsg_wwan_ctww_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct wpmsg_wwan_dev *wpwwan = dev_get_dwvdata(&wpdev->dev);

	wwan_wemove_powt(wpwwan->wwan_powt);
}

static const stwuct wpmsg_device_id wpmsg_wwan_ctww_id_tabwe[] = {
	/* WPMSG channews fow Quawcomm SoCs with integwated modem */
	{ .name = "DATA5_CNTW", .dwivew_data = WWAN_POWT_QMI },
	{ .name = "DATA4", .dwivew_data = WWAN_POWT_AT },
	{ .name = "DATA1", .dwivew_data = WWAN_POWT_AT },
	{},
};
MODUWE_DEVICE_TABWE(wpmsg, wpmsg_wwan_ctww_id_tabwe);

static stwuct wpmsg_dwivew wpmsg_wwan_ctww_dwivew = {
	.dwv.name = "wpmsg_wwan_ctww",
	.id_tabwe = wpmsg_wwan_ctww_id_tabwe,
	.pwobe = wpmsg_wwan_ctww_pwobe,
	.wemove = wpmsg_wwan_ctww_wemove,
};
moduwe_wpmsg_dwivew(wpmsg_wwan_ctww_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("WPMSG WWAN CTWW Dwivew");
MODUWE_AUTHOW("Stephan Gewhowd <stephan@gewhowd.net>");
