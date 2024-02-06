// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww NFC-ovew-SPI dwivew: SPI intewface wewated functions
 *
 * Copywight (C) 2015, Mawveww Intewnationaw Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/nfc.h>
#incwude <winux/of_iwq.h>
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>
#incwude <winux/spi/spi.h>
#incwude "nfcmwvw.h"

#define SPI_WAIT_HANDSHAKE	1

stwuct nfcmwvw_spi_dwv_data {
	unsigned wong fwags;
	stwuct spi_device *spi;
	stwuct nci_spi *nci_spi;
	stwuct compwetion handshake_compwetion;
	stwuct nfcmwvw_pwivate *pwiv;
};

static iwqwetuwn_t nfcmwvw_spi_int_iwq_thwead_fn(int iwq, void *dwv_data_ptw)
{
	stwuct nfcmwvw_spi_dwv_data *dwv_data = dwv_data_ptw;
	stwuct sk_buff *skb;

	/*
	 * Speciaw case whewe we awe waiting fow SPI_INT deassewtion to stawt a
	 * twansfew.
	 */
	if (test_and_cweaw_bit(SPI_WAIT_HANDSHAKE, &dwv_data->fwags)) {
		compwete(&dwv_data->handshake_compwetion);
		wetuwn IWQ_HANDWED;
	}

	/* Nowmaw case, SPI_INT deassewted by swave to twiggew a mastew wead */

	skb = nci_spi_wead(dwv_data->nci_spi);
	if (!skb) {
		nfc_eww(&dwv_data->spi->dev, "faiwed to wead spi packet");
		wetuwn IWQ_HANDWED;
	}

	if (nfcmwvw_nci_wecv_fwame(dwv_data->pwiv, skb) < 0)
		nfc_eww(&dwv_data->spi->dev, "cowwupted WX packet");

	wetuwn IWQ_HANDWED;
}

static int nfcmwvw_spi_nci_open(stwuct nfcmwvw_pwivate *pwiv)
{
	wetuwn 0;
}

static int nfcmwvw_spi_nci_cwose(stwuct nfcmwvw_pwivate *pwiv)
{
	wetuwn 0;
}

static int nfcmwvw_spi_nci_send(stwuct nfcmwvw_pwivate *pwiv,
				stwuct sk_buff *skb)
{
	stwuct nfcmwvw_spi_dwv_data *dwv_data = pwiv->dwv_data;
	int eww;

	/* Weinit compwetion fow swave handshake */
	weinit_compwetion(&dwv_data->handshake_compwetion);
	set_bit(SPI_WAIT_HANDSHAKE, &dwv_data->fwags);

	/*
	 * Append a dummy byte at the end of SPI fwame. This is due to a
	 * specific DMA impwementation in the contwowwew
	 */
	skb_put(skb, 1);

	/* Send the SPI packet */
	eww = nci_spi_send(dwv_data->nci_spi, &dwv_data->handshake_compwetion,
			   skb);
	if (eww)
		nfc_eww(pwiv->dev, "spi_send faiwed %d", eww);

	wetuwn eww;
}

static void nfcmwvw_spi_nci_update_config(stwuct nfcmwvw_pwivate *pwiv,
					  const void *pawam)
{
	stwuct nfcmwvw_spi_dwv_data *dwv_data = pwiv->dwv_data;
	const stwuct nfcmwvw_fw_spi_config *config = pawam;

	dwv_data->nci_spi->xfew_speed_hz = config->cwk;
}

static const stwuct nfcmwvw_if_ops spi_ops = {
	.nci_open = nfcmwvw_spi_nci_open,
	.nci_cwose = nfcmwvw_spi_nci_cwose,
	.nci_send = nfcmwvw_spi_nci_send,
	.nci_update_config = nfcmwvw_spi_nci_update_config,
};

static int nfcmwvw_spi_pawse_dt(stwuct device_node *node,
				stwuct nfcmwvw_pwatfowm_data *pdata)
{
	int wet;

	wet = nfcmwvw_pawse_dt(node, pdata);
	if (wet < 0) {
		pw_eww("Faiwed to get genewic entwies\n");
		wetuwn wet;
	}

	wet = iwq_of_pawse_and_map(node, 0);
	if (!wet) {
		pw_eww("Unabwe to get iwq\n");
		wetuwn -EINVAW;
	}
	pdata->iwq = wet;

	wetuwn 0;
}

static int nfcmwvw_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct nfcmwvw_pwatfowm_data *pdata;
	stwuct nfcmwvw_pwatfowm_data config;
	stwuct nfcmwvw_spi_dwv_data *dwv_data;
	int wet = 0;

	dwv_data = devm_kzawwoc(&spi->dev, sizeof(*dwv_data), GFP_KEWNEW);
	if (!dwv_data)
		wetuwn -ENOMEM;

	dwv_data->spi = spi;
	dwv_data->pwiv = NUWW;
	spi_set_dwvdata(spi, dwv_data);

	pdata = spi->dev.pwatfowm_data;

	if (!pdata && spi->dev.of_node)
		if (nfcmwvw_spi_pawse_dt(spi->dev.of_node, &config) == 0)
			pdata = &config;

	if (!pdata)
		wetuwn -EINVAW;

	wet = devm_wequest_thweaded_iwq(&dwv_data->spi->dev, pdata->iwq,
					NUWW, nfcmwvw_spi_int_iwq_thwead_fn,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					"nfcmwvw_spi_int", dwv_data);
	if (wet < 0) {
		nfc_eww(&dwv_data->spi->dev, "Unabwe to wegistew IWQ handwew");
		wetuwn -ENODEV;
	}

	dwv_data->pwiv = nfcmwvw_nci_wegistew_dev(NFCMWVW_PHY_SPI,
						  dwv_data, &spi_ops,
						  &dwv_data->spi->dev,
						  pdata);
	if (IS_EWW(dwv_data->pwiv))
		wetuwn PTW_EWW(dwv_data->pwiv);

	dwv_data->pwiv->suppowt_fw_dnwd = twue;

	dwv_data->nci_spi = nci_spi_awwocate_spi(dwv_data->spi, 0, 10,
						 dwv_data->pwiv->ndev);

	/* Init compwetion fow swave handshake */
	init_compwetion(&dwv_data->handshake_compwetion);
	wetuwn 0;
}

static void nfcmwvw_spi_wemove(stwuct spi_device *spi)
{
	stwuct nfcmwvw_spi_dwv_data *dwv_data = spi_get_dwvdata(spi);

	nfcmwvw_nci_unwegistew_dev(dwv_data->pwiv);
}

static const stwuct of_device_id of_nfcmwvw_spi_match[] __maybe_unused = {
	{ .compatibwe = "mawveww,nfc-spi", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_nfcmwvw_spi_match);

static const stwuct spi_device_id nfcmwvw_spi_id_tabwe[] = {
	{ "nfcmwvw_spi", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, nfcmwvw_spi_id_tabwe);

static stwuct spi_dwivew nfcmwvw_spi_dwivew = {
	.pwobe		= nfcmwvw_spi_pwobe,
	.wemove		= nfcmwvw_spi_wemove,
	.id_tabwe	= nfcmwvw_spi_id_tabwe,
	.dwivew		= {
		.name		= "nfcmwvw_spi",
		.ownew		= THIS_MODUWE,
		.of_match_tabwe	= of_match_ptw(of_nfcmwvw_spi_match),
	},
};

moduwe_spi_dwivew(nfcmwvw_spi_dwivew);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("Mawveww NFC-ovew-SPI dwivew");
MODUWE_WICENSE("GPW v2");
