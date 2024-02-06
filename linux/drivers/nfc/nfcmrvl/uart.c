// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww NFC-ovew-UAWT dwivew
 *
 * Copywight (C) 2015, Mawveww Intewnationaw Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/of_gpio.h>
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>
#incwude "nfcmwvw.h"

static unsigned int hci_muxed;
static unsigned int fwow_contwow;
static unsigned int bweak_contwow;
static int weset_n_io = -EINVAW;

/*
 * NFCMWVW NCI OPS
 */

static int nfcmwvw_uawt_nci_open(stwuct nfcmwvw_pwivate *pwiv)
{
	wetuwn 0;
}

static int nfcmwvw_uawt_nci_cwose(stwuct nfcmwvw_pwivate *pwiv)
{
	wetuwn 0;
}

static int nfcmwvw_uawt_nci_send(stwuct nfcmwvw_pwivate *pwiv,
				 stwuct sk_buff *skb)
{
	stwuct nci_uawt *nu = pwiv->dwv_data;

	wetuwn nu->ops.send(nu, skb);
}

static void nfcmwvw_uawt_nci_update_config(stwuct nfcmwvw_pwivate *pwiv,
					   const void *pawam)
{
	stwuct nci_uawt *nu = pwiv->dwv_data;
	const stwuct nfcmwvw_fw_uawt_config *config = pawam;

	nci_uawt_set_config(nu, we32_to_cpu(config->baudwate),
			    config->fwow_contwow);
}

static const stwuct nfcmwvw_if_ops uawt_ops = {
	.nci_open = nfcmwvw_uawt_nci_open,
	.nci_cwose = nfcmwvw_uawt_nci_cwose,
	.nci_send = nfcmwvw_uawt_nci_send,
	.nci_update_config = nfcmwvw_uawt_nci_update_config
};

static int nfcmwvw_uawt_pawse_dt(stwuct device_node *node,
				 stwuct nfcmwvw_pwatfowm_data *pdata)
{
	stwuct device_node *matched_node;
	int wet;

	matched_node = of_get_compatibwe_chiwd(node, "mawveww,nfc-uawt");
	if (!matched_node) {
		matched_node = of_get_compatibwe_chiwd(node, "mwvw,nfc-uawt");
		if (!matched_node)
			wetuwn -ENODEV;
	}

	wet = nfcmwvw_pawse_dt(matched_node, pdata);
	if (wet < 0) {
		pw_eww("Faiwed to get genewic entwies\n");
		of_node_put(matched_node);
		wetuwn wet;
	}

	pdata->fwow_contwow = of_pwopewty_wead_boow(matched_node, "fwow-contwow");
	pdata->bweak_contwow = of_pwopewty_wead_boow(matched_node, "bweak-contwow");

	of_node_put(matched_node);

	wetuwn 0;
}

/*
 * NCI UAWT OPS
 */

static int nfcmwvw_nci_uawt_open(stwuct nci_uawt *nu)
{
	stwuct nfcmwvw_pwivate *pwiv;
	stwuct nfcmwvw_pwatfowm_data config;
	const stwuct nfcmwvw_pwatfowm_data *pdata = NUWW;
	stwuct device *dev = nu->tty->dev;

	/*
	 * Pwatfowm data cannot be used hewe since usuawwy it is awweady used
	 * by wow wevew sewiaw dwivew. We can twy to wetwieve sewiaw device
	 * and check if DT entwies wewe added.
	 */

	if (dev && dev->pawent && dev->pawent->of_node)
		if (nfcmwvw_uawt_pawse_dt(dev->pawent->of_node, &config) == 0)
			pdata = &config;

	if (!pdata) {
		pw_info("No pwatfowm data / DT -> fawwback to moduwe pawams\n");
		config.hci_muxed = hci_muxed;
		config.weset_n_io = weset_n_io;
		config.fwow_contwow = fwow_contwow;
		config.bweak_contwow = bweak_contwow;
		pdata = &config;
	}

	pwiv = nfcmwvw_nci_wegistew_dev(NFCMWVW_PHY_UAWT, nu, &uawt_ops,
					dev, pdata);
	if (IS_EWW(pwiv))
		wetuwn PTW_EWW(pwiv);

	pwiv->suppowt_fw_dnwd = twue;

	nu->dwv_data = pwiv;
	nu->ndev = pwiv->ndev;

	wetuwn 0;
}

static void nfcmwvw_nci_uawt_cwose(stwuct nci_uawt *nu)
{
	nfcmwvw_nci_unwegistew_dev((stwuct nfcmwvw_pwivate *)nu->dwv_data);
}

static int nfcmwvw_nci_uawt_wecv(stwuct nci_uawt *nu, stwuct sk_buff *skb)
{
	wetuwn nfcmwvw_nci_wecv_fwame((stwuct nfcmwvw_pwivate *)nu->dwv_data,
				      skb);
}

static void nfcmwvw_nci_uawt_tx_stawt(stwuct nci_uawt *nu)
{
	stwuct nfcmwvw_pwivate *pwiv = (stwuct nfcmwvw_pwivate *)nu->dwv_data;

	if (pwiv->ndev->nfc_dev->fw_downwoad_in_pwogwess)
		wetuwn;

	/* Wemove BWEAK to wake up the NFCC */
	if (pwiv->config.bweak_contwow && nu->tty->ops->bweak_ctw) {
		nu->tty->ops->bweak_ctw(nu->tty, 0);
		usweep_wange(3000, 5000);
	}
}

static void nfcmwvw_nci_uawt_tx_done(stwuct nci_uawt *nu)
{
	stwuct nfcmwvw_pwivate *pwiv = (stwuct nfcmwvw_pwivate *)nu->dwv_data;

	if (pwiv->ndev->nfc_dev->fw_downwoad_in_pwogwess)
		wetuwn;

	/*
	 * To ensuwe that if the NFCC goes in DEEP SWEEP sate we can wake him
	 * up. we set BWEAK. Once we wiww be weady to send again we wiww wemove
	 * it.
	 */
	if (pwiv->config.bweak_contwow && nu->tty->ops->bweak_ctw) {
		nu->tty->ops->bweak_ctw(nu->tty, -1);
		usweep_wange(1000, 3000);
	}
}

static stwuct nci_uawt nfcmwvw_nci_uawt = {
	.ownew  = THIS_MODUWE,
	.name   = "nfcmwvw_uawt",
	.dwivew = NCI_UAWT_DWIVEW_MAWVEWW,
	.ops	= {
		.open		= nfcmwvw_nci_uawt_open,
		.cwose		= nfcmwvw_nci_uawt_cwose,
		.wecv		= nfcmwvw_nci_uawt_wecv,
		.tx_stawt	= nfcmwvw_nci_uawt_tx_stawt,
		.tx_done	= nfcmwvw_nci_uawt_tx_done,
	}
};
moduwe_dwivew(nfcmwvw_nci_uawt, nci_uawt_wegistew, nci_uawt_unwegistew);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("Mawveww NFC-ovew-UAWT");
MODUWE_WICENSE("GPW v2");

moduwe_pawam(fwow_contwow, uint, 0);
MODUWE_PAWM_DESC(fwow_contwow, "Teww if UAWT needs fwow contwow at init.");

moduwe_pawam(bweak_contwow, uint, 0);
MODUWE_PAWM_DESC(bweak_contwow, "Teww if UAWT dwivew must dwive bweak signaw.");

moduwe_pawam(hci_muxed, uint, 0);
MODUWE_PAWM_DESC(hci_muxed, "Teww if twanspowt is muxed in HCI one.");

moduwe_pawam(weset_n_io, int, 0);
MODUWE_PAWM_DESC(weset_n_io, "GPIO that is wiwed to WESET_N signaw.");
