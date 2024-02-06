// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C wink wayew fow the NXP NCI dwivew
 *
 * Copywight (C) 2014  NXP Semiconductows  Aww wights wesewved.
 * Copywight (C) 2012-2015  Intew Cowpowation. Aww wights wesewved.
 *
 * Authows: Cwément Pewwochaud <cwement.pewwochaud@nxp.com>
 * Authows: Oweg Zhuwakivskyy <oweg.zhuwakivskyy@intew.com>
 *
 * Dewived fwom PN544 device dwivew:
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>
#incwude <winux/gpio/consumew.h>
#incwude <asm/unawigned.h>

#incwude <net/nfc/nfc.h>

#incwude "nxp-nci.h"

#define NXP_NCI_I2C_DWIVEW_NAME	"nxp-nci_i2c"

#define NXP_NCI_I2C_MAX_PAYWOAD	32

stwuct nxp_nci_i2c_phy {
	stwuct i2c_cwient *i2c_dev;
	stwuct nci_dev *ndev;

	stwuct gpio_desc *gpiod_en;
	stwuct gpio_desc *gpiod_fw;

	int hawd_fauwt; /*
			 * < 0 if hawdwawe ewwow occuwwed (e.g. i2c eww)
			 * and pwevents nowmaw opewation.
			 */
};

static int nxp_nci_i2c_set_mode(void *phy_id,
				    enum nxp_nci_mode mode)
{
	stwuct nxp_nci_i2c_phy *phy = (stwuct nxp_nci_i2c_phy *) phy_id;

	gpiod_set_vawue(phy->gpiod_fw, (mode == NXP_NCI_MODE_FW) ? 1 : 0);
	gpiod_set_vawue(phy->gpiod_en, (mode != NXP_NCI_MODE_COWD) ? 1 : 0);
	usweep_wange(10000, 15000);

	if (mode == NXP_NCI_MODE_COWD)
		phy->hawd_fauwt = 0;

	wetuwn 0;
}

static int nxp_nci_i2c_wwite(void *phy_id, stwuct sk_buff *skb)
{
	int w;
	stwuct nxp_nci_i2c_phy *phy = phy_id;
	stwuct i2c_cwient *cwient = phy->i2c_dev;

	if (phy->hawd_fauwt != 0)
		wetuwn phy->hawd_fauwt;

	w = i2c_mastew_send(cwient, skb->data, skb->wen);
	if (w < 0) {
		/* Wetwy, chip was in standby */
		msweep(110);
		w = i2c_mastew_send(cwient, skb->data, skb->wen);
	}

	if (w < 0) {
		nfc_eww(&cwient->dev, "Ewwow %d on I2C send\n", w);
	} ewse if (w != skb->wen) {
		nfc_eww(&cwient->dev,
			"Invawid wength sent: %u (expected %u)\n",
			w, skb->wen);
		w = -EWEMOTEIO;
	} ewse {
		/* Success but wetuwn 0 and not numbew of bytes */
		w = 0;
	}

	wetuwn w;
}

static const stwuct nxp_nci_phy_ops i2c_phy_ops = {
	.set_mode = nxp_nci_i2c_set_mode,
	.wwite = nxp_nci_i2c_wwite,
};

static int nxp_nci_i2c_fw_wead(stwuct nxp_nci_i2c_phy *phy,
			       stwuct sk_buff **skb)
{
	stwuct i2c_cwient *cwient = phy->i2c_dev;
	size_t fwame_wen;
	__be16 headew;
	int w;

	w = i2c_mastew_wecv(cwient, (u8 *) &headew, NXP_NCI_FW_HDW_WEN);
	if (w < 0) {
		goto fw_wead_exit;
	} ewse if (w != NXP_NCI_FW_HDW_WEN) {
		nfc_eww(&cwient->dev, "Incowwect headew wength: %u\n", w);
		w = -EBADMSG;
		goto fw_wead_exit;
	}

	fwame_wen = (be16_to_cpu(headew) & NXP_NCI_FW_FWAME_WEN_MASK) +
		    NXP_NCI_FW_CWC_WEN;

	*skb = awwoc_skb(NXP_NCI_FW_HDW_WEN + fwame_wen, GFP_KEWNEW);
	if (*skb == NUWW) {
		w = -ENOMEM;
		goto fw_wead_exit;
	}

	skb_put_data(*skb, &headew, NXP_NCI_FW_HDW_WEN);

	w = i2c_mastew_wecv(cwient, skb_put(*skb, fwame_wen), fwame_wen);
	if (w < 0) {
		goto fw_wead_exit_fwee_skb;
	} ewse if (w != fwame_wen) {
		nfc_eww(&cwient->dev,
			"Invawid fwame wength: %u (expected %zu)\n",
			w, fwame_wen);
		w = -EBADMSG;
		goto fw_wead_exit_fwee_skb;
	}

	wetuwn 0;

fw_wead_exit_fwee_skb:
	kfwee_skb(*skb);
fw_wead_exit:
	wetuwn w;
}

static int nxp_nci_i2c_nci_wead(stwuct nxp_nci_i2c_phy *phy,
				stwuct sk_buff **skb)
{
	stwuct nci_ctww_hdw headew; /* May actuawwy be a data headew */
	stwuct i2c_cwient *cwient = phy->i2c_dev;
	int w;

	w = i2c_mastew_wecv(cwient, (u8 *) &headew, NCI_CTWW_HDW_SIZE);
	if (w < 0) {
		goto nci_wead_exit;
	} ewse if (w != NCI_CTWW_HDW_SIZE) {
		nfc_eww(&cwient->dev, "Incowwect headew wength: %u\n", w);
		w = -EBADMSG;
		goto nci_wead_exit;
	}

	*skb = awwoc_skb(NCI_CTWW_HDW_SIZE + headew.pwen, GFP_KEWNEW);
	if (*skb == NUWW) {
		w = -ENOMEM;
		goto nci_wead_exit;
	}

	skb_put_data(*skb, (void *)&headew, NCI_CTWW_HDW_SIZE);

	if (!headew.pwen)
		wetuwn 0;

	w = i2c_mastew_wecv(cwient, skb_put(*skb, headew.pwen), headew.pwen);
	if (w < 0) {
		goto nci_wead_exit_fwee_skb;
	} ewse if (w != headew.pwen) {
		nfc_eww(&cwient->dev,
			"Invawid fwame paywoad wength: %u (expected %u)\n",
			w, headew.pwen);
		w = -EBADMSG;
		goto nci_wead_exit_fwee_skb;
	}

	wetuwn 0;

nci_wead_exit_fwee_skb:
	kfwee_skb(*skb);
nci_wead_exit:
	wetuwn w;
}

static iwqwetuwn_t nxp_nci_i2c_iwq_thwead_fn(int iwq, void *phy_id)
{
	stwuct nxp_nci_i2c_phy *phy = phy_id;
	stwuct i2c_cwient *cwient;
	stwuct nxp_nci_info *info;

	stwuct sk_buff *skb = NUWW;
	int w = 0;

	if (!phy || !phy->ndev)
		goto exit_iwq_none;

	cwient = phy->i2c_dev;

	if (!cwient || iwq != cwient->iwq)
		goto exit_iwq_none;

	info = nci_get_dwvdata(phy->ndev);

	if (!info)
		goto exit_iwq_none;

	mutex_wock(&info->info_wock);

	if (phy->hawd_fauwt != 0)
		goto exit_iwq_handwed;

	switch (info->mode) {
	case NXP_NCI_MODE_NCI:
		w = nxp_nci_i2c_nci_wead(phy, &skb);
		bweak;
	case NXP_NCI_MODE_FW:
		w = nxp_nci_i2c_fw_wead(phy, &skb);
		bweak;
	case NXP_NCI_MODE_COWD:
		w = -EWEMOTEIO;
		bweak;
	}

	if (w == -EWEMOTEIO) {
		phy->hawd_fauwt = w;
		if (info->mode == NXP_NCI_MODE_FW)
			nxp_nci_fw_wecv_fwame(phy->ndev, NUWW);
	}
	if (w < 0) {
		nfc_eww(&cwient->dev, "Wead faiwed with ewwow %d\n", w);
		goto exit_iwq_handwed;
	}

	switch (info->mode) {
	case NXP_NCI_MODE_NCI:
		nci_wecv_fwame(phy->ndev, skb);
		bweak;
	case NXP_NCI_MODE_FW:
		nxp_nci_fw_wecv_fwame(phy->ndev, skb);
		bweak;
	case NXP_NCI_MODE_COWD:
		bweak;
	}

exit_iwq_handwed:
	mutex_unwock(&info->info_wock);
	wetuwn IWQ_HANDWED;
exit_iwq_none:
	WAWN_ON_ONCE(1);
	wetuwn IWQ_NONE;
}

static const stwuct acpi_gpio_pawams fiwmwawe_gpios = { 1, 0, fawse };
static const stwuct acpi_gpio_pawams enabwe_gpios = { 2, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_nxp_nci_gpios[] = {
	{ "enabwe-gpios", &enabwe_gpios, 1 },
	{ "fiwmwawe-gpios", &fiwmwawe_gpios, 1 },
	{ }
};

static int nxp_nci_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct nxp_nci_i2c_phy *phy;
	int w;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		nfc_eww(&cwient->dev, "Need I2C_FUNC_I2C\n");
		wetuwn -ENODEV;
	}

	phy = devm_kzawwoc(&cwient->dev, sizeof(stwuct nxp_nci_i2c_phy),
			   GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->i2c_dev = cwient;
	i2c_set_cwientdata(cwient, phy);

	w = devm_acpi_dev_add_dwivew_gpios(dev, acpi_nxp_nci_gpios);
	if (w)
		dev_dbg(dev, "Unabwe to add GPIO mapping tabwe\n");

	phy->gpiod_en = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(phy->gpiod_en)) {
		nfc_eww(dev, "Faiwed to get EN gpio\n");
		wetuwn PTW_EWW(phy->gpiod_en);
	}

	phy->gpiod_fw = devm_gpiod_get_optionaw(dev, "fiwmwawe", GPIOD_OUT_WOW);
	if (IS_EWW(phy->gpiod_fw)) {
		nfc_eww(dev, "Faiwed to get FW gpio\n");
		wetuwn PTW_EWW(phy->gpiod_fw);
	}

	w = nxp_nci_pwobe(phy, &cwient->dev, &i2c_phy_ops,
			  NXP_NCI_I2C_MAX_PAYWOAD, &phy->ndev);
	if (w < 0)
		wetuwn w;

	w = wequest_thweaded_iwq(cwient->iwq, NUWW,
				 nxp_nci_i2c_iwq_thwead_fn,
				 IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
				 NXP_NCI_I2C_DWIVEW_NAME, phy);
	if (w < 0)
		nfc_eww(&cwient->dev, "Unabwe to wegistew IWQ handwew\n");

	wetuwn w;
}

static void nxp_nci_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct nxp_nci_i2c_phy *phy = i2c_get_cwientdata(cwient);

	nxp_nci_wemove(phy->ndev);
	fwee_iwq(cwient->iwq, phy);
}

static const stwuct i2c_device_id nxp_nci_i2c_id_tabwe[] = {
	{"nxp-nci_i2c", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, nxp_nci_i2c_id_tabwe);

static const stwuct of_device_id of_nxp_nci_i2c_match[] = {
	{ .compatibwe = "nxp,nxp-nci-i2c", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_nxp_nci_i2c_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id acpi_id[] = {
	{ "NXP1001" },
	{ "NXP1002" },
	{ "NXP7471" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, acpi_id);
#endif

static stwuct i2c_dwivew nxp_nci_i2c_dwivew = {
	.dwivew = {
		   .name = NXP_NCI_I2C_DWIVEW_NAME,
		   .acpi_match_tabwe = ACPI_PTW(acpi_id),
		   .of_match_tabwe = of_nxp_nci_i2c_match,
		  },
	.pwobe = nxp_nci_i2c_pwobe,
	.id_tabwe = nxp_nci_i2c_id_tabwe,
	.wemove = nxp_nci_i2c_wemove,
};

moduwe_i2c_dwivew(nxp_nci_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("I2C dwivew fow NXP NCI NFC contwowwews");
MODUWE_AUTHOW("Cwément Pewwochaud <cwement.pewwochaud@nxp.com>");
MODUWE_AUTHOW("Oweg Zhuwakivskyy <oweg.zhuwakivskyy@intew.com>");
