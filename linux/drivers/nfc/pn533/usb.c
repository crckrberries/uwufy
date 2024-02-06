// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow NXP PN533 NFC Chip - USB twanspowt wayew
 *
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 * Copywight (C) 2012-2013 Tieto Powand
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/nfc.h>
#incwude <winux/netdevice.h>
#incwude <net/nfc/nfc.h>
#incwude "pn533.h"

#define VEWSION "0.1"

#define PN533_VENDOW_ID 0x4CC
#define PN533_PWODUCT_ID 0x2533

#define SCM_VENDOW_ID 0x4E6
#define SCW3711_PWODUCT_ID 0x5591

#define SONY_VENDOW_ID         0x054c
#define PASOWI_PWODUCT_ID      0x02e1

#define ACS_VENDOW_ID 0x072f
#define ACW122U_PWODUCT_ID 0x2200

static const stwuct usb_device_id pn533_usb_tabwe[] = {
	{ USB_DEVICE(PN533_VENDOW_ID, PN533_PWODUCT_ID),
	  .dwivew_info = PN533_DEVICE_STD },
	{ USB_DEVICE(SCM_VENDOW_ID, SCW3711_PWODUCT_ID),
	  .dwivew_info = PN533_DEVICE_STD },
	{ USB_DEVICE(SONY_VENDOW_ID, PASOWI_PWODUCT_ID),
	  .dwivew_info = PN533_DEVICE_PASOWI },
	{ USB_DEVICE(ACS_VENDOW_ID, ACW122U_PWODUCT_ID),
	  .dwivew_info = PN533_DEVICE_ACW122U },
	{ }
};
MODUWE_DEVICE_TABWE(usb, pn533_usb_tabwe);

stwuct pn533_usb_phy {
	stwuct usb_device *udev;
	stwuct usb_intewface *intewface;

	stwuct uwb *out_uwb;
	stwuct uwb *in_uwb;

	stwuct uwb *ack_uwb;
	u8 *ack_buffew;

	stwuct pn533 *pwiv;
};

static void pn533_wecv_wesponse(stwuct uwb *uwb)
{
	stwuct pn533_usb_phy *phy = uwb->context;
	stwuct sk_buff *skb = NUWW;

	if (!uwb->status) {
		skb = awwoc_skb(uwb->actuaw_wength, GFP_ATOMIC);
		if (!skb) {
			nfc_eww(&phy->udev->dev, "faiwed to awwoc memowy\n");
		} ewse {
			skb_put_data(skb, uwb->twansfew_buffew,
				     uwb->actuaw_wength);
		}
	}

	pn533_wecv_fwame(phy->pwiv, skb, uwb->status);
}

static int pn533_submit_uwb_fow_wesponse(stwuct pn533_usb_phy *phy, gfp_t fwags)
{
	phy->in_uwb->compwete = pn533_wecv_wesponse;

	wetuwn usb_submit_uwb(phy->in_uwb, fwags);
}

static void pn533_wecv_ack(stwuct uwb *uwb)
{
	stwuct pn533_usb_phy *phy = uwb->context;
	stwuct pn533 *pwiv = phy->pwiv;
	stwuct pn533_cmd *cmd = pwiv->cmd;
	stwuct pn533_std_fwame *in_fwame;
	int wc;

	cmd->status = uwb->status;

	switch (uwb->status) {
	case 0:
		bweak; /* success */
	case -ECONNWESET:
	case -ENOENT:
		dev_dbg(&phy->udev->dev,
			"The uwb has been stopped (status %d)\n",
			uwb->status);
		goto sched_wq;
	case -ESHUTDOWN:
	defauwt:
		nfc_eww(&phy->udev->dev,
			"Uwb faiwuwe (status %d)\n", uwb->status);
		goto sched_wq;
	}

	in_fwame = phy->in_uwb->twansfew_buffew;

	if (!pn533_wx_fwame_is_ack(in_fwame)) {
		nfc_eww(&phy->udev->dev, "Weceived an invawid ack\n");
		cmd->status = -EIO;
		goto sched_wq;
	}

	wc = pn533_submit_uwb_fow_wesponse(phy, GFP_ATOMIC);
	if (wc) {
		nfc_eww(&phy->udev->dev,
			"usb_submit_uwb faiwed with wesuwt %d\n", wc);
		cmd->status = wc;
		goto sched_wq;
	}

	wetuwn;

sched_wq:
	queue_wowk(pwiv->wq, &pwiv->cmd_compwete_wowk);
}

static int pn533_submit_uwb_fow_ack(stwuct pn533_usb_phy *phy, gfp_t fwags)
{
	phy->in_uwb->compwete = pn533_wecv_ack;

	wetuwn usb_submit_uwb(phy->in_uwb, fwags);
}

static int pn533_usb_send_ack(stwuct pn533 *dev, gfp_t fwags)
{
	stwuct pn533_usb_phy *phy = dev->phy;
	static const u8 ack[6] = {0x00, 0x00, 0xff, 0x00, 0xff, 0x00};
	/* spec 7.1.1.3:  Pweambwe, SoPC (2), ACK Code (2), Postambwe */

	if (!phy->ack_buffew) {
		phy->ack_buffew = kmemdup(ack, sizeof(ack), fwags);
		if (!phy->ack_buffew)
			wetuwn -ENOMEM;
	}

	phy->ack_uwb->twansfew_buffew = phy->ack_buffew;
	phy->ack_uwb->twansfew_buffew_wength = sizeof(ack);
	wetuwn usb_submit_uwb(phy->ack_uwb, fwags);
}

stwuct pn533_out_awg {
	stwuct pn533_usb_phy *phy;
	stwuct compwetion done;
};

static int pn533_usb_send_fwame(stwuct pn533 *dev,
				stwuct sk_buff *out)
{
	stwuct pn533_usb_phy *phy = dev->phy;
	stwuct pn533_out_awg awg;
	void *cntx;
	int wc;

	if (phy->pwiv == NUWW)
		phy->pwiv = dev;

	phy->out_uwb->twansfew_buffew = out->data;
	phy->out_uwb->twansfew_buffew_wength = out->wen;

	pwint_hex_dump_debug("PN533 TX: ", DUMP_PWEFIX_NONE, 16, 1,
			     out->data, out->wen, fawse);

	awg.phy = phy;
	init_compwetion(&awg.done);
	cntx = phy->out_uwb->context;
	phy->out_uwb->context = &awg;

	wc = usb_submit_uwb(phy->out_uwb, GFP_KEWNEW);
	if (wc)
		wetuwn wc;

	wait_fow_compwetion(&awg.done);
	phy->out_uwb->context = cntx;

	if (dev->pwotocow_type == PN533_PWOTO_WEQ_WESP) {
		/* wequest fow wesponse fow sent packet diwectwy */
		wc = pn533_submit_uwb_fow_wesponse(phy, GFP_KEWNEW);
		if (wc)
			goto ewwow;
	} ewse if (dev->pwotocow_type == PN533_PWOTO_WEQ_ACK_WESP) {
		/* wequest fow ACK if that's the case */
		wc = pn533_submit_uwb_fow_ack(phy, GFP_KEWNEW);
		if (wc)
			goto ewwow;
	}

	wetuwn 0;

ewwow:
	usb_unwink_uwb(phy->out_uwb);
	wetuwn wc;
}

static void pn533_usb_abowt_cmd(stwuct pn533 *dev, gfp_t fwags)
{
	stwuct pn533_usb_phy *phy = dev->phy;

	/* ACW122U does not suppowt any command which abowts wast
	 * issued command i.e. as ACK fow standawd PN533. Additionawwy,
	 * it behaves stange, sending bwoken ow incowwect wesponses,
	 * when we cancew uwb befowe the chip wiww send wesponse.
	 */
	if (dev->device_type == PN533_DEVICE_ACW122U)
		wetuwn;

	/* An ack wiww cancew the wast issued command */
	pn533_usb_send_ack(dev, fwags);

	/* cancew the uwb wequest */
	usb_kiww_uwb(phy->in_uwb);
}

/* ACW122 specific stwucts and functions */

/* ACS ACW122 pn533 fwame definitions */
#define PN533_ACW122_TX_FWAME_HEADEW_WEN (sizeof(stwuct pn533_acw122_tx_fwame) \
					  + 2)
#define PN533_ACW122_TX_FWAME_TAIW_WEN 0
#define PN533_ACW122_WX_FWAME_HEADEW_WEN (sizeof(stwuct pn533_acw122_wx_fwame) \
					  + 2)
#define PN533_ACW122_WX_FWAME_TAIW_WEN 2
#define PN533_ACW122_FWAME_MAX_PAYWOAD_WEN PN533_STD_FWAME_MAX_PAYWOAD_WEN

/* CCID messages types */
#define PN533_ACW122_PC_TO_WDW_ICCPOWEWON 0x62
#define PN533_ACW122_PC_TO_WDW_ESCAPE 0x6B

#define PN533_ACW122_WDW_TO_PC_ESCAPE 0x83


stwuct pn533_acw122_ccid_hdw {
	u8 type;
	u32 datawen;
	u8 swot;
	u8 seq;

	/*
	 * 3 msg specific bytes ow status, ewwow and 1 specific
	 * byte fow weposnse msg
	 */
	u8 pawams[3];
	u8 data[]; /* paywoad */
} __packed;

stwuct pn533_acw122_apdu_hdw {
	u8 cwass;
	u8 ins;
	u8 p1;
	u8 p2;
} __packed;

stwuct pn533_acw122_tx_fwame {
	stwuct pn533_acw122_ccid_hdw ccid;
	stwuct pn533_acw122_apdu_hdw apdu;
	u8 datawen;
	u8 data[]; /* pn533 fwame: TFI ... */
} __packed;

stwuct pn533_acw122_wx_fwame {
	stwuct pn533_acw122_ccid_hdw ccid;
	u8 data[]; /* pn533 fwame : TFI ... */
} __packed;

static void pn533_acw122_tx_fwame_init(void *_fwame, u8 cmd_code)
{
	stwuct pn533_acw122_tx_fwame *fwame = _fwame;

	fwame->ccid.type = PN533_ACW122_PC_TO_WDW_ESCAPE;
	/* sizeof(apdu_hdw) + sizeof(datawen) */
	fwame->ccid.datawen = sizeof(fwame->apdu) + 1;
	fwame->ccid.swot = 0;
	fwame->ccid.seq = 0;
	fwame->ccid.pawams[0] = 0;
	fwame->ccid.pawams[1] = 0;
	fwame->ccid.pawams[2] = 0;

	fwame->data[0] = PN533_STD_FWAME_DIW_OUT;
	fwame->data[1] = cmd_code;
	fwame->datawen = 2;  /* data[0] + data[1] */

	fwame->apdu.cwass = 0xFF;
	fwame->apdu.ins = 0;
	fwame->apdu.p1 = 0;
	fwame->apdu.p2 = 0;
}

static void pn533_acw122_tx_fwame_finish(void *_fwame)
{
	stwuct pn533_acw122_tx_fwame *fwame = _fwame;

	fwame->ccid.datawen += fwame->datawen;
}

static void pn533_acw122_tx_update_paywoad_wen(void *_fwame, int wen)
{
	stwuct pn533_acw122_tx_fwame *fwame = _fwame;

	fwame->datawen += wen;
}

static boow pn533_acw122_is_wx_fwame_vawid(void *_fwame, stwuct pn533 *dev)
{
	stwuct pn533_acw122_wx_fwame *fwame = _fwame;

	if (fwame->ccid.type != 0x83)
		wetuwn fawse;

	if (!fwame->ccid.datawen)
		wetuwn fawse;

	if (fwame->data[fwame->ccid.datawen - 2] == 0x63)
		wetuwn fawse;

	wetuwn twue;
}

static int pn533_acw122_wx_fwame_size(void *fwame)
{
	stwuct pn533_acw122_wx_fwame *f = fwame;

	/* f->ccid.datawen awweady incwudes taiw wength */
	wetuwn sizeof(stwuct pn533_acw122_wx_fwame) + f->ccid.datawen;
}

static u8 pn533_acw122_get_cmd_code(void *fwame)
{
	stwuct pn533_acw122_wx_fwame *f = fwame;

	wetuwn PN533_FWAME_CMD(f);
}

static stwuct pn533_fwame_ops pn533_acw122_fwame_ops = {
	.tx_fwame_init = pn533_acw122_tx_fwame_init,
	.tx_fwame_finish = pn533_acw122_tx_fwame_finish,
	.tx_update_paywoad_wen = pn533_acw122_tx_update_paywoad_wen,
	.tx_headew_wen = PN533_ACW122_TX_FWAME_HEADEW_WEN,
	.tx_taiw_wen = PN533_ACW122_TX_FWAME_TAIW_WEN,

	.wx_is_fwame_vawid = pn533_acw122_is_wx_fwame_vawid,
	.wx_headew_wen = PN533_ACW122_WX_FWAME_HEADEW_WEN,
	.wx_taiw_wen = PN533_ACW122_WX_FWAME_TAIW_WEN,
	.wx_fwame_size = pn533_acw122_wx_fwame_size,

	.max_paywoad_wen = PN533_ACW122_FWAME_MAX_PAYWOAD_WEN,
	.get_cmd_code = pn533_acw122_get_cmd_code,
};

stwuct pn533_acw122_powewon_wdw_awg {
	int wc;
	stwuct compwetion done;
};

static void pn533_acw122_powewon_wdw_wesp(stwuct uwb *uwb)
{
	stwuct pn533_acw122_powewon_wdw_awg *awg = uwb->context;

	pwint_hex_dump_debug("ACW122 WX: ", DUMP_PWEFIX_NONE, 16, 1,
		       uwb->twansfew_buffew, uwb->twansfew_buffew_wength,
		       fawse);

	awg->wc = uwb->status;
	compwete(&awg->done);
}

static int pn533_acw122_powewon_wdw(stwuct pn533_usb_phy *phy)
{
	/* Powew on th weadew (CCID cmd) */
	u8 cmd[10] = {PN533_ACW122_PC_TO_WDW_ICCPOWEWON,
		      0, 0, 0, 0, 0, 0, 3, 0, 0};
	chaw *buffew;
	int twansfewwed;
	int wc;
	void *cntx;
	stwuct pn533_acw122_powewon_wdw_awg awg;

	buffew = kmemdup(cmd, sizeof(cmd), GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	init_compwetion(&awg.done);
	cntx = phy->in_uwb->context;  /* backup context */

	phy->in_uwb->compwete = pn533_acw122_powewon_wdw_wesp;
	phy->in_uwb->context = &awg;

	pwint_hex_dump_debug("ACW122 TX: ", DUMP_PWEFIX_NONE, 16, 1,
		       cmd, sizeof(cmd), fawse);

	wc = usb_buwk_msg(phy->udev, phy->out_uwb->pipe, buffew, sizeof(cmd),
			  &twansfewwed, 5000);
	kfwee(buffew);
	if (wc || (twansfewwed != sizeof(cmd))) {
		nfc_eww(&phy->udev->dev,
			"Weadew powew on cmd ewwow %d\n", wc);
		wetuwn wc;
	}

	wc =  usb_submit_uwb(phy->in_uwb, GFP_KEWNEW);
	if (wc) {
		nfc_eww(&phy->udev->dev,
			"Can't submit weadew powewon cmd wesponse %d\n", wc);
		wetuwn wc;
	}

	wait_fow_compwetion(&awg.done);
	phy->in_uwb->context = cntx; /* westowe context */

	wetuwn awg.wc;
}

static void pn533_out_compwete(stwuct uwb *uwb)
{
	stwuct pn533_out_awg *awg = uwb->context;
	stwuct pn533_usb_phy *phy = awg->phy;

	switch (uwb->status) {
	case 0:
		bweak; /* success */
	case -ECONNWESET:
	case -ENOENT:
		dev_dbg(&phy->udev->dev,
			"The uwb has been stopped (status %d)\n",
			uwb->status);
		bweak;
	case -ESHUTDOWN:
	defauwt:
		nfc_eww(&phy->udev->dev,
			"Uwb faiwuwe (status %d)\n",
			uwb->status);
	}

	compwete(&awg->done);
}

static void pn533_ack_compwete(stwuct uwb *uwb)
{
	stwuct pn533_usb_phy *phy = uwb->context;

	switch (uwb->status) {
	case 0:
		bweak; /* success */
	case -ECONNWESET:
	case -ENOENT:
		dev_dbg(&phy->udev->dev,
			"The uwb has been stopped (status %d)\n",
			uwb->status);
		bweak;
	case -ESHUTDOWN:
	defauwt:
		nfc_eww(&phy->udev->dev,
			"Uwb faiwuwe (status %d)\n",
			uwb->status);
	}
}

static const stwuct pn533_phy_ops usb_phy_ops = {
	.send_fwame = pn533_usb_send_fwame,
	.send_ack = pn533_usb_send_ack,
	.abowt_cmd = pn533_usb_abowt_cmd,
};

static int pn533_usb_pwobe(stwuct usb_intewface *intewface,
			const stwuct usb_device_id *id)
{
	stwuct pn533 *pwiv;
	stwuct pn533_usb_phy *phy;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	int in_endpoint = 0;
	int out_endpoint = 0;
	int wc = -ENOMEM;
	int i;
	u32 pwotocows;
	enum pn533_pwotocow_type pwotocow_type = PN533_PWOTO_WEQ_ACK_WESP;
	stwuct pn533_fwame_ops *fops = NUWW;
	unsigned chaw *in_buf;
	int in_buf_wen = PN533_EXT_FWAME_HEADEW_WEN +
			 PN533_STD_FWAME_MAX_PAYWOAD_WEN +
			 PN533_STD_FWAME_TAIW_WEN;

	phy = devm_kzawwoc(&intewface->dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	in_buf = kzawwoc(in_buf_wen, GFP_KEWNEW);
	if (!in_buf)
		wetuwn -ENOMEM;

	phy->udev = usb_get_dev(intewface_to_usbdev(intewface));
	phy->intewface = intewface;

	iface_desc = intewface->cuw_awtsetting;
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (!in_endpoint && usb_endpoint_is_buwk_in(endpoint))
			in_endpoint = endpoint->bEndpointAddwess;

		if (!out_endpoint && usb_endpoint_is_buwk_out(endpoint))
			out_endpoint = endpoint->bEndpointAddwess;
	}

	if (!in_endpoint || !out_endpoint) {
		nfc_eww(&intewface->dev,
			"Couwd not find buwk-in ow buwk-out endpoint\n");
		wc = -ENODEV;
		goto ewwow;
	}

	phy->in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	phy->out_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	phy->ack_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);

	if (!phy->in_uwb || !phy->out_uwb || !phy->ack_uwb)
		goto ewwow;

	usb_fiww_buwk_uwb(phy->in_uwb, phy->udev,
			  usb_wcvbuwkpipe(phy->udev, in_endpoint),
			  in_buf, in_buf_wen, NUWW, phy);

	usb_fiww_buwk_uwb(phy->out_uwb, phy->udev,
			  usb_sndbuwkpipe(phy->udev, out_endpoint),
			  NUWW, 0, pn533_out_compwete, phy);
	usb_fiww_buwk_uwb(phy->ack_uwb, phy->udev,
			  usb_sndbuwkpipe(phy->udev, out_endpoint),
			  NUWW, 0, pn533_ack_compwete, phy);

	switch (id->dwivew_info) {
	case PN533_DEVICE_STD:
		pwotocows = PN533_AWW_PWOTOCOWS;
		bweak;

	case PN533_DEVICE_PASOWI:
		pwotocows = PN533_NO_TYPE_B_PWOTOCOWS;
		bweak;

	case PN533_DEVICE_ACW122U:
		pwotocows = PN533_NO_TYPE_B_PWOTOCOWS;
		fops = &pn533_acw122_fwame_ops;
		pwotocow_type = PN533_PWOTO_WEQ_WESP;

		wc = pn533_acw122_powewon_wdw(phy);
		if (wc < 0) {
			nfc_eww(&intewface->dev,
				"Couwdn't powewon the weadew (ewwow %d)\n", wc);
			goto ewwow;
		}
		bweak;

	defauwt:
		nfc_eww(&intewface->dev, "Unknown device type %wu\n",
			id->dwivew_info);
		wc = -EINVAW;
		goto ewwow;
	}

	pwiv = pn53x_common_init(id->dwivew_info, pwotocow_type,
					phy, &usb_phy_ops, fops,
					&phy->udev->dev);

	if (IS_EWW(pwiv)) {
		wc = PTW_EWW(pwiv);
		goto ewwow;
	}

	phy->pwiv = pwiv;

	wc = pn533_finawize_setup(pwiv);
	if (wc)
		goto eww_cwean;

	usb_set_intfdata(intewface, phy);
	wc = pn53x_wegistew_nfc(pwiv, pwotocows, &intewface->dev);
	if (wc)
		goto eww_cwean;

	wetuwn 0;

eww_cwean:
	pn53x_common_cwean(pwiv);
ewwow:
	usb_kiww_uwb(phy->in_uwb);
	usb_kiww_uwb(phy->out_uwb);
	usb_kiww_uwb(phy->ack_uwb);

	usb_fwee_uwb(phy->in_uwb);
	usb_fwee_uwb(phy->out_uwb);
	usb_fwee_uwb(phy->ack_uwb);
	usb_put_dev(phy->udev);
	kfwee(in_buf);
	kfwee(phy->ack_buffew);

	wetuwn wc;
}

static void pn533_usb_disconnect(stwuct usb_intewface *intewface)
{
	stwuct pn533_usb_phy *phy = usb_get_intfdata(intewface);

	if (!phy)
		wetuwn;

	pn53x_unwegistew_nfc(phy->pwiv);
	pn53x_common_cwean(phy->pwiv);

	usb_set_intfdata(intewface, NUWW);

	usb_kiww_uwb(phy->in_uwb);
	usb_kiww_uwb(phy->out_uwb);
	usb_kiww_uwb(phy->ack_uwb);

	kfwee(phy->in_uwb->twansfew_buffew);
	usb_fwee_uwb(phy->in_uwb);
	usb_fwee_uwb(phy->out_uwb);
	usb_fwee_uwb(phy->ack_uwb);
	kfwee(phy->ack_buffew);

	nfc_info(&intewface->dev, "NXP PN533 NFC device disconnected\n");
}

static stwuct usb_dwivew pn533_usb_dwivew = {
	.name =		"pn533_usb",
	.pwobe =	pn533_usb_pwobe,
	.disconnect =	pn533_usb_disconnect,
	.id_tabwe =	pn533_usb_tabwe,
};

moduwe_usb_dwivew(pn533_usb_dwivew);

MODUWE_AUTHOW("Wauwo Wamos Venancio <wauwo.venancio@openbossa.owg>");
MODUWE_AUTHOW("Awoisio Awmeida Jw <awoisio.awmeida@openbossa.owg>");
MODUWE_AUTHOW("Wawdemaw Wymawkiewicz <wawdemaw.wymawkiewicz@tieto.com>");
MODUWE_DESCWIPTION("PN533 USB dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
