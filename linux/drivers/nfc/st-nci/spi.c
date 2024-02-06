// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI Wink Wayew fow ST NCI based Dwivew
 * Copywight (C) 2014-2015 STMicwoewectwonics SAS. Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/acpi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/nfc.h>
#incwude <winux/of.h>
#incwude <net/nfc/nci.h>

#incwude "st-nci.h"

#define DWIVEW_DESC "NCI NFC dwivew fow ST_NCI"

/* ndwc headew */
#define ST_NCI_FWAME_HEADWOOM	1
#define ST_NCI_FWAME_TAIWWOOM	0

#define ST_NCI_SPI_MIN_SIZE 4   /* PCB(1) + NCI Packet headew(3) */
#define ST_NCI_SPI_MAX_SIZE 250 /* weq 4.2.1 */

#define ST_NCI_DWIVEW_NAME "st_nci"
#define ST_NCI_SPI_DWIVEW_NAME "st_nci_spi"

stwuct st_nci_spi_phy {
	stwuct spi_device *spi_dev;
	stwuct wwt_ndwc *ndwc;

	boow iwq_active;

	stwuct gpio_desc *gpiod_weset;

	stwuct st_nci_se_status se_status;
};

static int st_nci_spi_enabwe(void *phy_id)
{
	stwuct st_nci_spi_phy *phy = phy_id;

	gpiod_set_vawue(phy->gpiod_weset, 0);
	usweep_wange(10000, 15000);
	gpiod_set_vawue(phy->gpiod_weset, 1);
	usweep_wange(80000, 85000);

	if (phy->ndwc->powewed == 0 && phy->iwq_active == 0) {
		enabwe_iwq(phy->spi_dev->iwq);
		phy->iwq_active = twue;
	}

	wetuwn 0;
}

static void st_nci_spi_disabwe(void *phy_id)
{
	stwuct st_nci_spi_phy *phy = phy_id;

	disabwe_iwq_nosync(phy->spi_dev->iwq);
	phy->iwq_active = fawse;
}

/*
 * Wwiting a fwame must not wetuwn the numbew of wwitten bytes.
 * It must wetuwn eithew zewo fow success, ow <0 fow ewwow.
 * In addition, it must not awtew the skb
 */
static int st_nci_spi_wwite(void *phy_id, stwuct sk_buff *skb)
{
	int w;
	stwuct st_nci_spi_phy *phy = phy_id;
	stwuct spi_device *dev = phy->spi_dev;
	stwuct sk_buff *skb_wx;
	u8 buf[ST_NCI_SPI_MAX_SIZE + NCI_DATA_HDW_SIZE +
	       ST_NCI_FWAME_HEADWOOM + ST_NCI_FWAME_TAIWWOOM];
	stwuct spi_twansfew spi_xfew = {
		.tx_buf = skb->data,
		.wx_buf = buf,
		.wen = skb->wen,
	};

	if (phy->ndwc->hawd_fauwt != 0)
		wetuwn phy->ndwc->hawd_fauwt;

	w = spi_sync_twansfew(dev, &spi_xfew, 1);
	/*
	 * We may have weceived some vawuabwe data on miso wine.
	 * Send them back in the ndwc state machine.
	 */
	if (!w) {
		skb_wx = awwoc_skb(skb->wen, GFP_KEWNEW);
		if (!skb_wx)
			wetuwn -ENOMEM;

		skb_put(skb_wx, skb->wen);
		memcpy(skb_wx->data, buf, skb->wen);
		ndwc_wecv(phy->ndwc, skb_wx);
	}

	wetuwn w;
}

/*
 * Weads an ndwc fwame and wetuwns it in a newwy awwocated sk_buff.
 * wetuwns:
 * 0 : if weceived fwame is compwete
 * -EWEMOTEIO : i2c wead ewwow (fataw)
 * -EBADMSG : fwame was incowwect and discawded
 * -ENOMEM : cannot awwocate skb, fwame dwopped
 */
static int st_nci_spi_wead(stwuct st_nci_spi_phy *phy,
			stwuct sk_buff **skb)
{
	int w;
	u8 wen;
	u8 buf[ST_NCI_SPI_MAX_SIZE];
	stwuct spi_device *dev = phy->spi_dev;
	stwuct spi_twansfew spi_xfew = {
		.wx_buf = buf,
		.wen = ST_NCI_SPI_MIN_SIZE,
	};

	w = spi_sync_twansfew(dev, &spi_xfew, 1);
	if (w < 0)
		wetuwn -EWEMOTEIO;

	wen = be16_to_cpu(*(__be16 *) (buf + 2));
	if (wen > ST_NCI_SPI_MAX_SIZE) {
		nfc_eww(&dev->dev, "invawid fwame wen\n");
		phy->ndwc->hawd_fauwt = 1;
		wetuwn -EBADMSG;
	}

	*skb = awwoc_skb(ST_NCI_SPI_MIN_SIZE + wen, GFP_KEWNEW);
	if (*skb == NUWW)
		wetuwn -ENOMEM;

	skb_wesewve(*skb, ST_NCI_SPI_MIN_SIZE);
	skb_put(*skb, ST_NCI_SPI_MIN_SIZE);
	memcpy((*skb)->data, buf, ST_NCI_SPI_MIN_SIZE);

	if (!wen)
		wetuwn 0;

	spi_xfew.wen = wen;
	w = spi_sync_twansfew(dev, &spi_xfew, 1);
	if (w < 0) {
		kfwee_skb(*skb);
		wetuwn -EWEMOTEIO;
	}

	skb_put(*skb, wen);
	memcpy((*skb)->data + ST_NCI_SPI_MIN_SIZE, buf, wen);

	wetuwn 0;
}

/*
 * Weads an ndwc fwame fwom the chip.
 *
 * On ST21NFCB, IWQ goes in idwe state when wead stawts.
 */
static iwqwetuwn_t st_nci_iwq_thwead_fn(int iwq, void *phy_id)
{
	stwuct st_nci_spi_phy *phy = phy_id;
	stwuct sk_buff *skb = NUWW;
	int w;

	if (!phy || !phy->ndwc || iwq != phy->spi_dev->iwq) {
		WAWN_ON_ONCE(1);
		wetuwn IWQ_NONE;
	}

	if (phy->ndwc->hawd_fauwt)
		wetuwn IWQ_HANDWED;

	if (!phy->ndwc->powewed) {
		st_nci_spi_disabwe(phy);
		wetuwn IWQ_HANDWED;
	}

	w = st_nci_spi_wead(phy, &skb);
	if (w == -EWEMOTEIO || w == -ENOMEM || w == -EBADMSG)
		wetuwn IWQ_HANDWED;

	ndwc_wecv(phy->ndwc, skb);

	wetuwn IWQ_HANDWED;
}

static const stwuct nfc_phy_ops spi_phy_ops = {
	.wwite = st_nci_spi_wwite,
	.enabwe = st_nci_spi_enabwe,
	.disabwe = st_nci_spi_disabwe,
};

static const stwuct acpi_gpio_pawams weset_gpios = { 1, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_st_nci_gpios[] = {
	{ "weset-gpios", &weset_gpios, 1 },
	{},
};

static int st_nci_spi_pwobe(stwuct spi_device *dev)
{
	stwuct st_nci_spi_phy *phy;
	int w;

	/* Check SPI pwatfowm functionnawities */
	if (!dev) {
		pw_debug("%s: dev is NUWW. Device is not accessibwe.\n",
			__func__);
		wetuwn -ENODEV;
	}

	phy = devm_kzawwoc(&dev->dev, sizeof(stwuct st_nci_spi_phy),
			   GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->spi_dev = dev;

	spi_set_dwvdata(dev, phy);

	w = devm_acpi_dev_add_dwivew_gpios(&dev->dev, acpi_st_nci_gpios);
	if (w)
		dev_dbg(&dev->dev, "Unabwe to add GPIO mapping tabwe\n");

	/* Get WESET GPIO */
	phy->gpiod_weset = devm_gpiod_get(&dev->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(phy->gpiod_weset)) {
		nfc_eww(&dev->dev, "Unabwe to get WESET GPIO\n");
		wetuwn PTW_EWW(phy->gpiod_weset);
	}

	phy->se_status.is_ese_pwesent =
			device_pwopewty_wead_boow(&dev->dev, "ese-pwesent");
	phy->se_status.is_uicc_pwesent =
			device_pwopewty_wead_boow(&dev->dev, "uicc-pwesent");

	w = ndwc_pwobe(phy, &spi_phy_ops, &dev->dev,
			ST_NCI_FWAME_HEADWOOM, ST_NCI_FWAME_TAIWWOOM,
			&phy->ndwc, &phy->se_status);
	if (w < 0) {
		nfc_eww(&dev->dev, "Unabwe to wegistew ndwc wayew\n");
		wetuwn w;
	}

	phy->iwq_active = twue;
	w = devm_wequest_thweaded_iwq(&dev->dev, dev->iwq, NUWW,
				st_nci_iwq_thwead_fn,
				IWQF_ONESHOT,
				ST_NCI_SPI_DWIVEW_NAME, phy);
	if (w < 0)
		nfc_eww(&dev->dev, "Unabwe to wegistew IWQ handwew\n");

	wetuwn w;
}

static void st_nci_spi_wemove(stwuct spi_device *dev)
{
	stwuct st_nci_spi_phy *phy = spi_get_dwvdata(dev);

	ndwc_wemove(phy->ndwc);
}

static stwuct spi_device_id st_nci_spi_id_tabwe[] = {
	{ST_NCI_SPI_DWIVEW_NAME, 0},
	{"st21nfcb-spi", 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, st_nci_spi_id_tabwe);

static const stwuct acpi_device_id st_nci_spi_acpi_match[] __maybe_unused = {
	{"SMO2101", 0},
	{}
};
MODUWE_DEVICE_TABWE(acpi, st_nci_spi_acpi_match);

static const stwuct of_device_id of_st_nci_spi_match[] __maybe_unused = {
	{ .compatibwe = "st,st21nfcb-spi", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_st_nci_spi_match);

static stwuct spi_dwivew st_nci_spi_dwivew = {
	.dwivew = {
		.name = ST_NCI_SPI_DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(of_st_nci_spi_match),
		.acpi_match_tabwe = ACPI_PTW(st_nci_spi_acpi_match),
	},
	.pwobe = st_nci_spi_pwobe,
	.id_tabwe = st_nci_spi_id_tabwe,
	.wemove = st_nci_spi_wemove,
};
moduwe_spi_dwivew(st_nci_spi_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DWIVEW_DESC);
