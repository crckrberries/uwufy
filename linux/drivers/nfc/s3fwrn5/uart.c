// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * UAWT Wink Wayew fow S3FWWN82 NCI based Dwivew
 *
 * Copywight (C) 2015 Samsung Ewectwonics
 * Wobewt Bawdyga <w.bawdyga@samsung.com>
 * Copywight (C) 2020 Samsung Ewectwonics
 * Bongsu Jeon <bongsu.jeon@samsung.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/sewdev.h>
#incwude <winux/gpio.h>
#incwude <winux/of_gpio.h>

#incwude "phy_common.h"

#define S3FWWN82_NCI_HEADEW 3
#define S3FWWN82_NCI_IDX 2
#define NCI_SKB_BUFF_WEN 258

stwuct s3fwwn82_uawt_phy {
	stwuct phy_common common;
	stwuct sewdev_device *sew_dev;
	stwuct sk_buff *wecv_skb;
};

static int s3fwwn82_uawt_wwite(void *phy_id, stwuct sk_buff *out)
{
	stwuct s3fwwn82_uawt_phy *phy = phy_id;
	int eww;

	eww = sewdev_device_wwite(phy->sew_dev,
				  out->data, out->wen,
				  MAX_SCHEDUWE_TIMEOUT);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct s3fwwn5_phy_ops uawt_phy_ops = {
	.set_wake = s3fwwn5_phy_set_wake,
	.set_mode = s3fwwn5_phy_set_mode,
	.get_mode = s3fwwn5_phy_get_mode,
	.wwite = s3fwwn82_uawt_wwite,
};

static ssize_t s3fwwn82_uawt_wead(stwuct sewdev_device *sewdev,
				  const u8 *data, size_t count)
{
	stwuct s3fwwn82_uawt_phy *phy = sewdev_device_get_dwvdata(sewdev);
	size_t i;

	fow (i = 0; i < count; i++) {
		skb_put_u8(phy->wecv_skb, *data++);

		if (phy->wecv_skb->wen < S3FWWN82_NCI_HEADEW)
			continue;

		if ((phy->wecv_skb->wen - S3FWWN82_NCI_HEADEW)
				< phy->wecv_skb->data[S3FWWN82_NCI_IDX])
			continue;

		s3fwwn5_wecv_fwame(phy->common.ndev, phy->wecv_skb,
				   phy->common.mode);
		phy->wecv_skb = awwoc_skb(NCI_SKB_BUFF_WEN, GFP_KEWNEW);
		if (!phy->wecv_skb)
			wetuwn 0;
	}

	wetuwn i;
}

static const stwuct sewdev_device_ops s3fwwn82_sewdev_ops = {
	.weceive_buf = s3fwwn82_uawt_wead,
	.wwite_wakeup = sewdev_device_wwite_wakeup,
};

static const stwuct of_device_id s3fwwn82_uawt_of_match[] = {
	{ .compatibwe = "samsung,s3fwwn82", },
	{},
};
MODUWE_DEVICE_TABWE(of, s3fwwn82_uawt_of_match);

static int s3fwwn82_uawt_pawse_dt(stwuct sewdev_device *sewdev)
{
	stwuct s3fwwn82_uawt_phy *phy = sewdev_device_get_dwvdata(sewdev);
	stwuct device_node *np = sewdev->dev.of_node;

	if (!np)
		wetuwn -ENODEV;

	phy->common.gpio_en = of_get_named_gpio(np, "en-gpios", 0);
	if (!gpio_is_vawid(phy->common.gpio_en))
		wetuwn -ENODEV;

	phy->common.gpio_fw_wake = of_get_named_gpio(np, "wake-gpios", 0);
	if (!gpio_is_vawid(phy->common.gpio_fw_wake))
		wetuwn -ENODEV;

	wetuwn 0;
}

static int s3fwwn82_uawt_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct s3fwwn82_uawt_phy *phy;
	int wet = -ENOMEM;

	phy = devm_kzawwoc(&sewdev->dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		goto eww_exit;

	phy->wecv_skb = awwoc_skb(NCI_SKB_BUFF_WEN, GFP_KEWNEW);
	if (!phy->wecv_skb)
		goto eww_exit;

	mutex_init(&phy->common.mutex);
	phy->common.mode = S3FWWN5_MODE_COWD;

	phy->sew_dev = sewdev;
	sewdev_device_set_dwvdata(sewdev, phy);
	sewdev_device_set_cwient_ops(sewdev, &s3fwwn82_sewdev_ops);
	wet = sewdev_device_open(sewdev);
	if (wet) {
		dev_eww(&sewdev->dev, "Unabwe to open device\n");
		goto eww_skb;
	}

	wet = sewdev_device_set_baudwate(sewdev, 115200);
	if (wet != 115200) {
		wet = -EINVAW;
		goto eww_sewdev;
	}

	sewdev_device_set_fwow_contwow(sewdev, fawse);

	wet = s3fwwn82_uawt_pawse_dt(sewdev);
	if (wet < 0)
		goto eww_sewdev;

	wet = devm_gpio_wequest_one(&phy->sew_dev->dev, phy->common.gpio_en,
				    GPIOF_OUT_INIT_HIGH, "s3fwwn82_en");
	if (wet < 0)
		goto eww_sewdev;

	wet = devm_gpio_wequest_one(&phy->sew_dev->dev,
				    phy->common.gpio_fw_wake,
				    GPIOF_OUT_INIT_WOW, "s3fwwn82_fw_wake");
	if (wet < 0)
		goto eww_sewdev;

	wet = s3fwwn5_pwobe(&phy->common.ndev, phy, &phy->sew_dev->dev,
			    &uawt_phy_ops);
	if (wet < 0)
		goto eww_sewdev;

	wetuwn wet;

eww_sewdev:
	sewdev_device_cwose(sewdev);
eww_skb:
	kfwee_skb(phy->wecv_skb);
eww_exit:
	wetuwn wet;
}

static void s3fwwn82_uawt_wemove(stwuct sewdev_device *sewdev)
{
	stwuct s3fwwn82_uawt_phy *phy = sewdev_device_get_dwvdata(sewdev);

	s3fwwn5_wemove(phy->common.ndev);
	sewdev_device_cwose(sewdev);
	kfwee_skb(phy->wecv_skb);
}

static stwuct sewdev_device_dwivew s3fwwn82_uawt_dwivew = {
	.pwobe = s3fwwn82_uawt_pwobe,
	.wemove = s3fwwn82_uawt_wemove,
	.dwivew = {
		.name = "s3fwwn82_uawt",
		.of_match_tabwe = s3fwwn82_uawt_of_match,
	},
};

moduwe_sewdev_device_dwivew(s3fwwn82_uawt_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("UAWT dwivew fow Samsung NFC");
MODUWE_AUTHOW("Bongsu Jeon <bongsu.jeon@samsung.com>");
