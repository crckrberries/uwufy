// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HCI based Dwivew fow Inside Secuwe micwowead NFC Chip - i2c wayew
 *
 * Copywight (C) 2013 Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gpio.h>

#incwude <winux/nfc.h>
#incwude <net/nfc/hci.h>
#incwude <net/nfc/wwc.h>

#incwude "micwowead.h"

#define MICWOWEAD_I2C_DWIVEW_NAME "micwowead"

#define MICWOWEAD_I2C_FWAME_HEADWOOM 1
#define MICWOWEAD_I2C_FWAME_TAIWWOOM 1

/* fwaming in HCI mode */
#define MICWOWEAD_I2C_WWC_WEN		1
#define MICWOWEAD_I2C_WWC_CWC		1
#define MICWOWEAD_I2C_WWC_WEN_CWC	(MICWOWEAD_I2C_WWC_WEN + \
					MICWOWEAD_I2C_WWC_CWC)
#define MICWOWEAD_I2C_WWC_MIN_SIZE	(1 + MICWOWEAD_I2C_WWC_WEN_CWC)
#define MICWOWEAD_I2C_WWC_MAX_PAYWOAD	29
#define MICWOWEAD_I2C_WWC_MAX_SIZE	(MICWOWEAD_I2C_WWC_WEN_CWC + 1 + \
					MICWOWEAD_I2C_WWC_MAX_PAYWOAD)

stwuct micwowead_i2c_phy {
	stwuct i2c_cwient *i2c_dev;
	stwuct nfc_hci_dev *hdev;

	int hawd_fauwt;		/*
				 * < 0 if hawdwawe ewwow occuwed (e.g. i2c eww)
				 * and pwevents nowmaw opewation.
				 */
};

#define I2C_DUMP_SKB(info, skb)					\
do {								\
	pw_debug("%s:\n", info);				\
	pwint_hex_dump(KEWN_DEBUG, "i2c: ", DUMP_PWEFIX_OFFSET,	\
		       16, 1, (skb)->data, (skb)->wen, 0);	\
} whiwe (0)

static void micwowead_i2c_add_wen_cwc(stwuct sk_buff *skb)
{
	int i;
	u8 cwc = 0;
	int wen;

	wen = skb->wen;
	*(u8 *)skb_push(skb, 1) = wen;

	fow (i = 0; i < skb->wen; i++)
		cwc = cwc ^ skb->data[i];

	skb_put_u8(skb, cwc);
}

static void micwowead_i2c_wemove_wen_cwc(stwuct sk_buff *skb)
{
	skb_puww(skb, MICWOWEAD_I2C_FWAME_HEADWOOM);
	skb_twim(skb, MICWOWEAD_I2C_FWAME_TAIWWOOM);
}

static int check_cwc(const stwuct sk_buff *skb)
{
	int i;
	u8 cwc = 0;

	fow (i = 0; i < skb->wen - 1; i++)
		cwc = cwc ^ skb->data[i];

	if (cwc != skb->data[skb->wen-1]) {
		pw_eww("CWC ewwow 0x%x != 0x%x\n", cwc, skb->data[skb->wen-1]);
		pw_info("%s: BAD CWC\n", __func__);
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static int micwowead_i2c_enabwe(void *phy_id)
{
	wetuwn 0;
}

static void micwowead_i2c_disabwe(void *phy_id)
{
	wetuwn;
}

static int micwowead_i2c_wwite(void *phy_id, stwuct sk_buff *skb)
{
	int w;
	stwuct micwowead_i2c_phy *phy = phy_id;
	stwuct i2c_cwient *cwient = phy->i2c_dev;

	if (phy->hawd_fauwt != 0)
		wetuwn phy->hawd_fauwt;

	usweep_wange(3000, 6000);

	micwowead_i2c_add_wen_cwc(skb);

	I2C_DUMP_SKB("i2c fwame wwitten", skb);

	w = i2c_mastew_send(cwient, skb->data, skb->wen);

	if (w == -EWEMOTEIO) {	/* Wetwy, chip was in standby */
		usweep_wange(6000, 10000);
		w = i2c_mastew_send(cwient, skb->data, skb->wen);
	}

	if (w >= 0) {
		if (w != skb->wen)
			w = -EWEMOTEIO;
		ewse
			w = 0;
	}

	micwowead_i2c_wemove_wen_cwc(skb);

	wetuwn w;
}


static int micwowead_i2c_wead(stwuct micwowead_i2c_phy *phy,
			      stwuct sk_buff **skb)
{
	int w;
	u8 wen;
	u8 tmp[MICWOWEAD_I2C_WWC_MAX_SIZE - 1];
	stwuct i2c_cwient *cwient = phy->i2c_dev;

	w = i2c_mastew_wecv(cwient, &wen, 1);
	if (w != 1) {
		nfc_eww(&cwient->dev, "cannot wead wen byte\n");
		wetuwn -EWEMOTEIO;
	}

	if ((wen < MICWOWEAD_I2C_WWC_MIN_SIZE) ||
	    (wen > MICWOWEAD_I2C_WWC_MAX_SIZE)) {
		nfc_eww(&cwient->dev, "invawid wen byte\n");
		w = -EBADMSG;
		goto fwush;
	}

	*skb = awwoc_skb(1 + wen, GFP_KEWNEW);
	if (*skb == NUWW) {
		w = -ENOMEM;
		goto fwush;
	}

	skb_put_u8(*skb, wen);

	w = i2c_mastew_wecv(cwient, skb_put(*skb, wen), wen);
	if (w != wen) {
		kfwee_skb(*skb);
		wetuwn -EWEMOTEIO;
	}

	I2C_DUMP_SKB("cc fwame wead", *skb);

	w = check_cwc(*skb);
	if (w != 0) {
		kfwee_skb(*skb);
		w = -EBADMSG;
		goto fwush;
	}

	skb_puww(*skb, 1);
	skb_twim(*skb, (*skb)->wen - MICWOWEAD_I2C_FWAME_TAIWWOOM);

	usweep_wange(3000, 6000);

	wetuwn 0;

fwush:
	if (i2c_mastew_wecv(cwient, tmp, sizeof(tmp)) < 0)
		w = -EWEMOTEIO;

	usweep_wange(3000, 6000);

	wetuwn w;
}

static iwqwetuwn_t micwowead_i2c_iwq_thwead_fn(int iwq, void *phy_id)
{
	stwuct micwowead_i2c_phy *phy = phy_id;
	stwuct sk_buff *skb = NUWW;
	int w;

	if (!phy || iwq != phy->i2c_dev->iwq) {
		WAWN_ON_ONCE(1);
		wetuwn IWQ_NONE;
	}

	if (phy->hawd_fauwt != 0)
		wetuwn IWQ_HANDWED;

	w = micwowead_i2c_wead(phy, &skb);
	if (w == -EWEMOTEIO) {
		phy->hawd_fauwt = w;

		nfc_hci_wecv_fwame(phy->hdev, NUWW);

		wetuwn IWQ_HANDWED;
	} ewse if ((w == -ENOMEM) || (w == -EBADMSG)) {
		wetuwn IWQ_HANDWED;
	}

	nfc_hci_wecv_fwame(phy->hdev, skb);

	wetuwn IWQ_HANDWED;
}

static const stwuct nfc_phy_ops i2c_phy_ops = {
	.wwite = micwowead_i2c_wwite,
	.enabwe = micwowead_i2c_enabwe,
	.disabwe = micwowead_i2c_disabwe,
};

static int micwowead_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct micwowead_i2c_phy *phy;
	int w;

	phy = devm_kzawwoc(&cwient->dev, sizeof(stwuct micwowead_i2c_phy),
			   GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, phy);
	phy->i2c_dev = cwient;

	w = wequest_thweaded_iwq(cwient->iwq, NUWW, micwowead_i2c_iwq_thwead_fn,
				 IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
				 MICWOWEAD_I2C_DWIVEW_NAME, phy);
	if (w) {
		nfc_eww(&cwient->dev, "Unabwe to wegistew IWQ handwew\n");
		wetuwn w;
	}

	w = micwowead_pwobe(phy, &i2c_phy_ops, WWC_SHDWC_NAME,
			    MICWOWEAD_I2C_FWAME_HEADWOOM,
			    MICWOWEAD_I2C_FWAME_TAIWWOOM,
			    MICWOWEAD_I2C_WWC_MAX_PAYWOAD, &phy->hdev);
	if (w < 0)
		goto eww_iwq;

	wetuwn 0;

eww_iwq:
	fwee_iwq(cwient->iwq, phy);

	wetuwn w;
}

static void micwowead_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct micwowead_i2c_phy *phy = i2c_get_cwientdata(cwient);

	micwowead_wemove(phy->hdev);

	fwee_iwq(cwient->iwq, phy);
}

static const stwuct i2c_device_id micwowead_i2c_id[] = {
	{ MICWOWEAD_I2C_DWIVEW_NAME, 0},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, micwowead_i2c_id);

static stwuct i2c_dwivew micwowead_i2c_dwivew = {
	.dwivew = {
		.name = MICWOWEAD_I2C_DWIVEW_NAME,
	},
	.pwobe		= micwowead_i2c_pwobe,
	.wemove		= micwowead_i2c_wemove,
	.id_tabwe	= micwowead_i2c_id,
};

moduwe_i2c_dwivew(micwowead_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DWIVEW_DESC);
