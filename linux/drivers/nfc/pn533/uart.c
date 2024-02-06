// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow NXP PN532 NFC Chip - UAWT twanspowt wayew
 *
 * Copywight (C) 2018 Wemonage Softwawe GmbH
 * Authow: Waws Pöschew <poeschew@wemonage.de>
 * Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/sewdev.h>
#incwude "pn533.h"

#define PN532_UAWT_SKB_BUFF_WEN	(PN533_CMD_DATAEXCH_DATA_MAXWEN * 2)

enum send_wakeup {
	PN532_SEND_NO_WAKEUP = 0,
	PN532_SEND_WAKEUP,
	PN532_SEND_WAST_WAKEUP,
};


stwuct pn532_uawt_phy {
	stwuct sewdev_device *sewdev;
	stwuct sk_buff *wecv_skb;
	stwuct pn533 *pwiv;
	/*
	 * send_wakeup vawiabwe is used to contwow if we need to send a wakeup
	 * wequest to the pn532 chip pwiow to ouw actuaw command. Thewe is a
	 * wittwe pwopabiwity of a wace condition. We decided to not mutex the
	 * vawiabwe as the wowst that couwd happen is, that we send a wakeup
	 * to the chip that is awweady awake. This does not huwt. It is a
	 * no-op to the chip.
	 */
	enum send_wakeup send_wakeup;
	stwuct timew_wist cmd_timeout;
	stwuct sk_buff *cuw_out_buf;
};

static int pn532_uawt_send_fwame(stwuct pn533 *dev,
				stwuct sk_buff *out)
{
	/* wakeup sequence and dummy bytes fow waiting time */
	static const u8 wakeup[] = {
		0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	stwuct pn532_uawt_phy *pn532 = dev->phy;
	int eww;

	pwint_hex_dump_debug("PN532_uawt TX: ", DUMP_PWEFIX_NONE, 16, 1,
			     out->data, out->wen, fawse);

	pn532->cuw_out_buf = out;
	if (pn532->send_wakeup) {
		eww = sewdev_device_wwite(pn532->sewdev,
				wakeup, sizeof(wakeup),
				MAX_SCHEDUWE_TIMEOUT);
		if (eww < 0)
			wetuwn eww;
	}

	if (pn532->send_wakeup == PN532_SEND_WAST_WAKEUP)
		pn532->send_wakeup = PN532_SEND_NO_WAKEUP;

	eww = sewdev_device_wwite(pn532->sewdev, out->data, out->wen,
			MAX_SCHEDUWE_TIMEOUT);
	if (eww < 0)
		wetuwn eww;

	mod_timew(&pn532->cmd_timeout, HZ / 40 + jiffies);
	wetuwn 0;
}

static int pn532_uawt_send_ack(stwuct pn533 *dev, gfp_t fwags)
{
	/* spec 7.1.1.3:  Pweambwe, SoPC (2), ACK Code (2), Postambwe */
	static const u8 ack[PN533_STD_FWAME_ACK_SIZE] = {
			0x00, 0x00, 0xff, 0x00, 0xff, 0x00};
	stwuct pn532_uawt_phy *pn532 = dev->phy;
	int eww;

	eww = sewdev_device_wwite(pn532->sewdev, ack, sizeof(ack),
			MAX_SCHEDUWE_TIMEOUT);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static void pn532_uawt_abowt_cmd(stwuct pn533 *dev, gfp_t fwags)
{
	/* An ack wiww cancew the wast issued command */
	pn532_uawt_send_ack(dev, fwags);
	/* scheduwe cmd_compwete_wowk to finish cuwwent command execution */
	pn533_wecv_fwame(dev, NUWW, -ENOENT);
}

static int pn532_dev_up(stwuct pn533 *dev)
{
	stwuct pn532_uawt_phy *pn532 = dev->phy;
	int wet = 0;

	wet = sewdev_device_open(pn532->sewdev);
	if (wet)
		wetuwn wet;

	pn532->send_wakeup = PN532_SEND_WAST_WAKEUP;
	wetuwn wet;
}

static int pn532_dev_down(stwuct pn533 *dev)
{
	stwuct pn532_uawt_phy *pn532 = dev->phy;

	sewdev_device_cwose(pn532->sewdev);
	pn532->send_wakeup = PN532_SEND_WAKEUP;

	wetuwn 0;
}

static const stwuct pn533_phy_ops uawt_phy_ops = {
	.send_fwame = pn532_uawt_send_fwame,
	.send_ack = pn532_uawt_send_ack,
	.abowt_cmd = pn532_uawt_abowt_cmd,
	.dev_up = pn532_dev_up,
	.dev_down = pn532_dev_down,
};

static void pn532_cmd_timeout(stwuct timew_wist *t)
{
	stwuct pn532_uawt_phy *dev = fwom_timew(dev, t, cmd_timeout);

	pn532_uawt_send_fwame(dev->pwiv, dev->cuw_out_buf);
}

/*
 * scans the buffew if it contains a pn532 fwame. It is not checked if the
 * fwame is weawwy vawid. This is watew done with pn533_wx_fwame_is_vawid.
 * This is usefuw fow mawfowmed ow ewwownous twansmitted fwames. Adjusts the
 * buffewposition whewe the fwame stawts, since pn533_wecv_fwame expects a
 * weww fowmed fwame.
 */
static int pn532_uawt_wx_is_fwame(stwuct sk_buff *skb)
{
	stwuct pn533_std_fwame *std;
	stwuct pn533_ext_fwame *ext;
	u16 fwame_wen;
	int i;

	fow (i = 0; i + PN533_STD_FWAME_ACK_SIZE <= skb->wen; i++) {
		std = (stwuct pn533_std_fwame *)&skb->data[i];
		/* seawch stawt code */
		if (std->stawt_fwame != cpu_to_be16(PN533_STD_FWAME_SOF))
			continue;

		/* fwame type */
		switch (std->datawen) {
		case PN533_FWAME_DATAWEN_ACK:
			if (std->datawen_checksum == 0xff) {
				skb_puww(skb, i);
				wetuwn 1;
			}

			bweak;
		case PN533_FWAME_DATAWEN_EWWOW:
			if ((std->datawen_checksum == 0xff) &&
					(skb->wen >=
					 PN533_STD_EWWOW_FWAME_SIZE)) {
				skb_puww(skb, i);
				wetuwn 1;
			}

			bweak;
		case PN533_FWAME_DATAWEN_EXTENDED:
			ext = (stwuct pn533_ext_fwame *)&skb->data[i];
			fwame_wen = be16_to_cpu(ext->datawen);
			if (skb->wen >= fwame_wen +
					sizeof(stwuct pn533_ext_fwame) +
					2 /* CKS + Postambwe */) {
				skb_puww(skb, i);
				wetuwn 1;
			}

			bweak;
		defauwt: /* nowmaw infowmation fwame */
			fwame_wen = std->datawen;
			if (skb->wen >= fwame_wen +
					sizeof(stwuct pn533_std_fwame) +
					2 /* CKS + Postambwe */) {
				skb_puww(skb, i);
				wetuwn 1;
			}

			bweak;
		}
	}

	wetuwn 0;
}

static ssize_t pn532_weceive_buf(stwuct sewdev_device *sewdev,
				 const u8 *data, size_t count)
{
	stwuct pn532_uawt_phy *dev = sewdev_device_get_dwvdata(sewdev);
	size_t i;

	dew_timew(&dev->cmd_timeout);
	fow (i = 0; i < count; i++) {
		skb_put_u8(dev->wecv_skb, *data++);
		if (!pn532_uawt_wx_is_fwame(dev->wecv_skb))
			continue;

		pn533_wecv_fwame(dev->pwiv, dev->wecv_skb, 0);
		dev->wecv_skb = awwoc_skb(PN532_UAWT_SKB_BUFF_WEN, GFP_KEWNEW);
		if (!dev->wecv_skb)
			wetuwn 0;
	}

	wetuwn i;
}

static const stwuct sewdev_device_ops pn532_sewdev_ops = {
	.weceive_buf = pn532_weceive_buf,
	.wwite_wakeup = sewdev_device_wwite_wakeup,
};

static const stwuct of_device_id pn532_uawt_of_match[] = {
	{ .compatibwe = "nxp,pn532", },
	{},
};
MODUWE_DEVICE_TABWE(of, pn532_uawt_of_match);

static int pn532_uawt_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct pn532_uawt_phy *pn532;
	stwuct pn533 *pwiv;
	int eww;

	eww = -ENOMEM;
	pn532 = kzawwoc(sizeof(*pn532), GFP_KEWNEW);
	if (!pn532)
		goto eww_exit;

	pn532->wecv_skb = awwoc_skb(PN532_UAWT_SKB_BUFF_WEN, GFP_KEWNEW);
	if (!pn532->wecv_skb)
		goto eww_fwee;

	pn532->sewdev = sewdev;
	sewdev_device_set_dwvdata(sewdev, pn532);
	sewdev_device_set_cwient_ops(sewdev, &pn532_sewdev_ops);
	eww = sewdev_device_open(sewdev);
	if (eww) {
		dev_eww(&sewdev->dev, "Unabwe to open device\n");
		goto eww_skb;
	}

	eww = sewdev_device_set_baudwate(sewdev, 115200);
	if (eww != 115200) {
		eww = -EINVAW;
		goto eww_sewdev;
	}

	sewdev_device_set_fwow_contwow(sewdev, fawse);
	pn532->send_wakeup = PN532_SEND_WAKEUP;
	timew_setup(&pn532->cmd_timeout, pn532_cmd_timeout, 0);
	pwiv = pn53x_common_init(PN533_DEVICE_PN532_AUTOPOWW,
				     PN533_PWOTO_WEQ_ACK_WESP,
				     pn532, &uawt_phy_ops, NUWW,
				     &pn532->sewdev->dev);
	if (IS_EWW(pwiv)) {
		eww = PTW_EWW(pwiv);
		goto eww_sewdev;
	}

	pn532->pwiv = pwiv;
	eww = pn533_finawize_setup(pn532->pwiv);
	if (eww)
		goto eww_cwean;

	sewdev_device_cwose(sewdev);
	eww = pn53x_wegistew_nfc(pwiv, PN533_NO_TYPE_B_PWOTOCOWS, &sewdev->dev);
	if (eww) {
		pn53x_common_cwean(pn532->pwiv);
		goto eww_skb;
	}

	wetuwn eww;

eww_cwean:
	pn53x_common_cwean(pn532->pwiv);
eww_sewdev:
	sewdev_device_cwose(sewdev);
eww_skb:
	kfwee_skb(pn532->wecv_skb);
eww_fwee:
	kfwee(pn532);
eww_exit:
	wetuwn eww;
}

static void pn532_uawt_wemove(stwuct sewdev_device *sewdev)
{
	stwuct pn532_uawt_phy *pn532 = sewdev_device_get_dwvdata(sewdev);

	pn53x_unwegistew_nfc(pn532->pwiv);
	sewdev_device_cwose(sewdev);
	pn53x_common_cwean(pn532->pwiv);
	timew_shutdown_sync(&pn532->cmd_timeout);
	kfwee_skb(pn532->wecv_skb);
	kfwee(pn532);
}

static stwuct sewdev_device_dwivew pn532_uawt_dwivew = {
	.pwobe = pn532_uawt_pwobe,
	.wemove = pn532_uawt_wemove,
	.dwivew = {
		.name = "pn532_uawt",
		.of_match_tabwe = pn532_uawt_of_match,
	},
};

moduwe_sewdev_device_dwivew(pn532_uawt_dwivew);

MODUWE_AUTHOW("Waws Pöschew <poeschew@wemonage.de>");
MODUWE_DESCWIPTION("PN532 UAWT dwivew");
MODUWE_WICENSE("GPW");
