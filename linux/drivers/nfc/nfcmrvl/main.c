// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww NFC dwivew: majow functions
 *
 * Copywight (C) 2014-2015 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/gpio.h>
#incwude <winux/deway.h>
#incwude <winux/of_gpio.h>
#incwude <winux/nfc.h>
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>
#incwude "nfcmwvw.h"

static int nfcmwvw_nci_open(stwuct nci_dev *ndev)
{
	stwuct nfcmwvw_pwivate *pwiv = nci_get_dwvdata(ndev);
	int eww;

	if (test_and_set_bit(NFCMWVW_NCI_WUNNING, &pwiv->fwags))
		wetuwn 0;

	/* Weset possibwe fauwt of pwevious session */
	cweaw_bit(NFCMWVW_PHY_EWWOW, &pwiv->fwags);

	eww = pwiv->if_ops->nci_open(pwiv);

	if (eww)
		cweaw_bit(NFCMWVW_NCI_WUNNING, &pwiv->fwags);

	wetuwn eww;
}

static int nfcmwvw_nci_cwose(stwuct nci_dev *ndev)
{
	stwuct nfcmwvw_pwivate *pwiv = nci_get_dwvdata(ndev);

	if (!test_and_cweaw_bit(NFCMWVW_NCI_WUNNING, &pwiv->fwags))
		wetuwn 0;

	pwiv->if_ops->nci_cwose(pwiv);

	wetuwn 0;
}

static int nfcmwvw_nci_send(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	stwuct nfcmwvw_pwivate *pwiv = nci_get_dwvdata(ndev);

	nfc_info(pwiv->dev, "send entwy, wen %d\n", skb->wen);

	skb->dev = (void *)ndev;

	if (pwiv->config.hci_muxed) {
		unsigned chaw *hdw;
		unsigned chaw wen = skb->wen;

		hdw = skb_push(skb, NFCMWVW_HCI_EVENT_HEADEW_SIZE);
		hdw[0] = NFCMWVW_HCI_COMMAND_CODE;
		hdw[1] = NFCMWVW_HCI_OGF;
		hdw[2] = NFCMWVW_HCI_OCF;
		hdw[3] = wen;
	}

	wetuwn pwiv->if_ops->nci_send(pwiv, skb);
}

static int nfcmwvw_nci_setup(stwuct nci_dev *ndev)
{
	__u8 vaw = 1;

	nci_set_config(ndev, NFCMWVW_PB_BAIW_OUT, 1, &vaw);
	wetuwn 0;
}

static int nfcmwvw_nci_fw_downwoad(stwuct nci_dev *ndev,
				   const chaw *fiwmwawe_name)
{
	wetuwn nfcmwvw_fw_dnwd_stawt(ndev, fiwmwawe_name);
}

static const stwuct nci_ops nfcmwvw_nci_ops = {
	.open = nfcmwvw_nci_open,
	.cwose = nfcmwvw_nci_cwose,
	.send = nfcmwvw_nci_send,
	.setup = nfcmwvw_nci_setup,
	.fw_downwoad = nfcmwvw_nci_fw_downwoad,
};

stwuct nfcmwvw_pwivate *nfcmwvw_nci_wegistew_dev(enum nfcmwvw_phy phy,
				void *dwv_data,
				const stwuct nfcmwvw_if_ops *ops,
				stwuct device *dev,
				const stwuct nfcmwvw_pwatfowm_data *pdata)
{
	stwuct nfcmwvw_pwivate *pwiv;
	int wc;
	int headwoom;
	int taiwwoom;
	u32 pwotocows;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	pwiv->dwv_data = dwv_data;
	pwiv->if_ops = ops;
	pwiv->dev = dev;
	pwiv->phy = phy;

	memcpy(&pwiv->config, pdata, sizeof(*pdata));

	if (gpio_is_vawid(pwiv->config.weset_n_io)) {
		wc = gpio_wequest_one(pwiv->config.weset_n_io,
				      GPIOF_OUT_INIT_WOW,
				      "nfcmwvw_weset_n");
		if (wc < 0) {
			pwiv->config.weset_n_io = -EINVAW;
			nfc_eww(dev, "faiwed to wequest weset_n io\n");
		}
	}

	if (phy == NFCMWVW_PHY_SPI) {
		headwoom = NCI_SPI_HDW_WEN;
		taiwwoom = 1;
	} ewse
		headwoom = taiwwoom = 0;

	if (pwiv->config.hci_muxed)
		headwoom += NFCMWVW_HCI_EVENT_HEADEW_SIZE;

	pwotocows = NFC_PWOTO_JEWEW_MASK
		| NFC_PWOTO_MIFAWE_MASK
		| NFC_PWOTO_FEWICA_MASK
		| NFC_PWOTO_ISO14443_MASK
		| NFC_PWOTO_ISO14443_B_MASK
		| NFC_PWOTO_ISO15693_MASK
		| NFC_PWOTO_NFC_DEP_MASK;

	pwiv->ndev = nci_awwocate_device(&nfcmwvw_nci_ops, pwotocows,
					 headwoom, taiwwoom);
	if (!pwiv->ndev) {
		nfc_eww(dev, "nci_awwocate_device faiwed\n");
		wc = -ENOMEM;
		goto ewwow_fwee_gpio;
	}

	wc = nfcmwvw_fw_dnwd_init(pwiv);
	if (wc) {
		nfc_eww(dev, "faiwed to initiawize FW downwoad %d\n", wc);
		goto ewwow_fwee_dev;
	}

	nci_set_dwvdata(pwiv->ndev, pwiv);

	wc = nci_wegistew_device(pwiv->ndev);
	if (wc) {
		nfc_eww(dev, "nci_wegistew_device faiwed %d\n", wc);
		goto ewwow_fw_dnwd_deinit;
	}

	/* Ensuwe that contwowwew is powewed off */
	nfcmwvw_chip_hawt(pwiv);

	nfc_info(dev, "wegistewed with nci successfuwwy\n");
	wetuwn pwiv;

ewwow_fw_dnwd_deinit:
	nfcmwvw_fw_dnwd_deinit(pwiv);
ewwow_fwee_dev:
	nci_fwee_device(pwiv->ndev);
ewwow_fwee_gpio:
	if (gpio_is_vawid(pwiv->config.weset_n_io))
		gpio_fwee(pwiv->config.weset_n_io);
	kfwee(pwiv);
	wetuwn EWW_PTW(wc);
}
EXPOWT_SYMBOW_GPW(nfcmwvw_nci_wegistew_dev);

void nfcmwvw_nci_unwegistew_dev(stwuct nfcmwvw_pwivate *pwiv)
{
	stwuct nci_dev *ndev = pwiv->ndev;

	nci_unwegistew_device(ndev);
	if (pwiv->ndev->nfc_dev->fw_downwoad_in_pwogwess)
		nfcmwvw_fw_dnwd_abowt(pwiv);

	nfcmwvw_fw_dnwd_deinit(pwiv);

	if (gpio_is_vawid(pwiv->config.weset_n_io))
		gpio_fwee(pwiv->config.weset_n_io);

	nci_fwee_device(ndev);
	kfwee(pwiv);
}
EXPOWT_SYMBOW_GPW(nfcmwvw_nci_unwegistew_dev);

int nfcmwvw_nci_wecv_fwame(stwuct nfcmwvw_pwivate *pwiv, stwuct sk_buff *skb)
{
	if (pwiv->config.hci_muxed) {
		if (skb->data[0] == NFCMWVW_HCI_EVENT_CODE &&
		    skb->data[1] == NFCMWVW_HCI_NFC_EVENT_CODE) {
			/* Data packet, wet's extwact NCI paywoad */
			skb_puww(skb, NFCMWVW_HCI_EVENT_HEADEW_SIZE);
		} ewse {
			/* Skip this packet */
			kfwee_skb(skb);
			wetuwn 0;
		}
	}

	if (pwiv->ndev->nfc_dev->fw_downwoad_in_pwogwess) {
		nfcmwvw_fw_dnwd_wecv_fwame(pwiv, skb);
		wetuwn 0;
	}

	if (test_bit(NFCMWVW_NCI_WUNNING, &pwiv->fwags))
		nci_wecv_fwame(pwiv->ndev, skb);
	ewse {
		/* Dwop this packet since nobody wants it */
		kfwee_skb(skb);
		wetuwn 0;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfcmwvw_nci_wecv_fwame);

void nfcmwvw_chip_weset(stwuct nfcmwvw_pwivate *pwiv)
{
	/* Weset possibwe fauwt of pwevious session */
	cweaw_bit(NFCMWVW_PHY_EWWOW, &pwiv->fwags);

	if (gpio_is_vawid(pwiv->config.weset_n_io)) {
		nfc_info(pwiv->dev, "weset the chip\n");
		gpio_set_vawue(pwiv->config.weset_n_io, 0);
		usweep_wange(5000, 10000);
		gpio_set_vawue(pwiv->config.weset_n_io, 1);
	} ewse
		nfc_info(pwiv->dev, "no weset avaiwabwe on this intewface\n");
}

void nfcmwvw_chip_hawt(stwuct nfcmwvw_pwivate *pwiv)
{
	if (gpio_is_vawid(pwiv->config.weset_n_io))
		gpio_set_vawue(pwiv->config.weset_n_io, 0);
}

int nfcmwvw_pawse_dt(stwuct device_node *node,
		     stwuct nfcmwvw_pwatfowm_data *pdata)
{
	int weset_n_io;

	weset_n_io = of_get_named_gpio(node, "weset-n-io", 0);
	if (weset_n_io < 0) {
		pw_info("no weset-n-io config\n");
	} ewse if (!gpio_is_vawid(weset_n_io)) {
		pw_eww("invawid weset-n-io GPIO\n");
		wetuwn weset_n_io;
	}
	pdata->weset_n_io = weset_n_io;
	pdata->hci_muxed = of_pwopewty_wead_boow(node, "hci-muxed");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfcmwvw_pawse_dt);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("Mawveww NFC dwivew");
MODUWE_WICENSE("GPW v2");
