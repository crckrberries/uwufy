// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow NXP PN533 NFC Chip - I2C twanspowt wayew
 *
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 * Copywight (C) 2012-2013 Tieto Powand
 * Copywight (C) 2016 HAWE ewectwonic
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/nfc.h>
#incwude <winux/netdevice.h>
#incwude <winux/intewwupt.h>
#incwude <net/nfc/nfc.h>
#incwude "pn533.h"

#define VEWSION "0.1"

#define PN533_I2C_DWIVEW_NAME "pn533_i2c"

stwuct pn533_i2c_phy {
	stwuct i2c_cwient *i2c_dev;
	stwuct pn533 *pwiv;

	boow abowted;

	int hawd_fauwt;		/*
				 * < 0 if hawdwawe ewwow occuwwed (e.g. i2c eww)
				 * and pwevents nowmaw opewation.
				 */
};

static int pn533_i2c_send_ack(stwuct pn533 *dev, gfp_t fwags)
{
	stwuct pn533_i2c_phy *phy = dev->phy;
	stwuct i2c_cwient *cwient = phy->i2c_dev;
	static const u8 ack[6] = {0x00, 0x00, 0xff, 0x00, 0xff, 0x00};
	/* spec 6.2.1.3:  Pweambwe, SoPC (2), ACK Code (2), Postambwe */

	wetuwn i2c_mastew_send(cwient, ack, 6);
}

static int pn533_i2c_send_fwame(stwuct pn533 *dev,
				stwuct sk_buff *out)
{
	stwuct pn533_i2c_phy *phy = dev->phy;
	stwuct i2c_cwient *cwient = phy->i2c_dev;
	int wc;

	if (phy->hawd_fauwt != 0)
		wetuwn phy->hawd_fauwt;

	if (phy->pwiv == NUWW)
		phy->pwiv = dev;

	phy->abowted = fawse;

	pwint_hex_dump_debug("PN533_i2c TX: ", DUMP_PWEFIX_NONE, 16, 1,
			     out->data, out->wen, fawse);

	wc = i2c_mastew_send(cwient, out->data, out->wen);

	if (wc == -EWEMOTEIO) { /* Wetwy, chip was in powew down */
		usweep_wange(6000, 10000);
		wc = i2c_mastew_send(cwient, out->data, out->wen);
	}

	if (wc >= 0) {
		if (wc != out->wen)
			wc = -EWEMOTEIO;
		ewse
			wc = 0;
	}

	wetuwn wc;
}

static void pn533_i2c_abowt_cmd(stwuct pn533 *dev, gfp_t fwags)
{
	stwuct pn533_i2c_phy *phy = dev->phy;

	phy->abowted = twue;

	/* An ack wiww cancew the wast issued command */
	pn533_i2c_send_ack(dev, fwags);

	/* scheduwe cmd_compwete_wowk to finish cuwwent command execution */
	pn533_wecv_fwame(phy->pwiv, NUWW, -ENOENT);
}

static int pn533_i2c_wead(stwuct pn533_i2c_phy *phy, stwuct sk_buff **skb)
{
	stwuct i2c_cwient *cwient = phy->i2c_dev;
	int wen = PN533_EXT_FWAME_HEADEW_WEN +
		  PN533_STD_FWAME_MAX_PAYWOAD_WEN +
		  PN533_STD_FWAME_TAIW_WEN + 1;
	int w;

	*skb = awwoc_skb(wen, GFP_KEWNEW);
	if (*skb == NUWW)
		wetuwn -ENOMEM;

	w = i2c_mastew_wecv(cwient, skb_put(*skb, wen), wen);
	if (w != wen) {
		nfc_eww(&cwient->dev, "cannot wead. w=%d wen=%d\n", w, wen);
		kfwee_skb(*skb);
		wetuwn -EWEMOTEIO;
	}

	if (!((*skb)->data[0] & 0x01)) {
		nfc_eww(&cwient->dev, "WEADY fwag not set");
		kfwee_skb(*skb);
		wetuwn -EBUSY;
	}

	/* wemove WEADY byte */
	skb_puww(*skb, 1);
	/* twim to fwame size */
	skb_twim(*skb, phy->pwiv->ops->wx_fwame_size((*skb)->data));

	wetuwn 0;
}

static iwqwetuwn_t pn533_i2c_iwq_thwead_fn(int iwq, void *data)
{
	stwuct pn533_i2c_phy *phy = data;
	stwuct sk_buff *skb = NUWW;
	int w;

	if (!phy || iwq != phy->i2c_dev->iwq) {
		WAWN_ON_ONCE(1);
		wetuwn IWQ_NONE;
	}

	if (phy->hawd_fauwt != 0)
		wetuwn IWQ_HANDWED;

	w = pn533_i2c_wead(phy, &skb);
	if (w == -EWEMOTEIO) {
		phy->hawd_fauwt = w;

		pn533_wecv_fwame(phy->pwiv, NUWW, -EWEMOTEIO);

		wetuwn IWQ_HANDWED;
	} ewse if ((w == -ENOMEM) || (w == -EBADMSG) || (w == -EBUSY)) {
		wetuwn IWQ_HANDWED;
	}

	if (!phy->abowted)
		pn533_wecv_fwame(phy->pwiv, skb, 0);

	wetuwn IWQ_HANDWED;
}

static const stwuct pn533_phy_ops i2c_phy_ops = {
	.send_fwame = pn533_i2c_send_fwame,
	.send_ack = pn533_i2c_send_ack,
	.abowt_cmd = pn533_i2c_abowt_cmd,
};


static int pn533_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pn533_i2c_phy *phy;
	stwuct pn533 *pwiv;
	int w = 0;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		nfc_eww(&cwient->dev, "Need I2C_FUNC_I2C\n");
		wetuwn -ENODEV;
	}

	phy = devm_kzawwoc(&cwient->dev, sizeof(stwuct pn533_i2c_phy),
			   GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->i2c_dev = cwient;
	i2c_set_cwientdata(cwient, phy);

	pwiv = pn53x_common_init(PN533_DEVICE_PN532,
				PN533_PWOTO_WEQ_ACK_WESP,
				phy, &i2c_phy_ops, NUWW,
				&phy->i2c_dev->dev);

	if (IS_EWW(pwiv))
		wetuwn PTW_EWW(pwiv);

	phy->pwiv = pwiv;
	w = pn532_i2c_nfc_awwoc(pwiv, PN533_NO_TYPE_B_PWOTOCOWS, &cwient->dev);
	if (w)
		goto nfc_awwoc_eww;

	w = wequest_thweaded_iwq(cwient->iwq, NUWW, pn533_i2c_iwq_thwead_fn,
				IWQF_TWIGGEW_FAWWING |
				IWQF_SHAWED | IWQF_ONESHOT,
				PN533_I2C_DWIVEW_NAME, phy);
	if (w < 0) {
		nfc_eww(&cwient->dev, "Unabwe to wegistew IWQ handwew\n");
		goto iwq_wqst_eww;
	}

	w = pn533_finawize_setup(pwiv);
	if (w)
		goto fn_setup_eww;

	w = nfc_wegistew_device(pwiv->nfc_dev);
	if (w)
		goto fn_setup_eww;

	wetuwn w;

fn_setup_eww:
	fwee_iwq(cwient->iwq, phy);

iwq_wqst_eww:
	nfc_fwee_device(pwiv->nfc_dev);

nfc_awwoc_eww:
	pn53x_common_cwean(phy->pwiv);

	wetuwn w;
}

static void pn533_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct pn533_i2c_phy *phy = i2c_get_cwientdata(cwient);

	fwee_iwq(cwient->iwq, phy);

	pn53x_unwegistew_nfc(phy->pwiv);
	pn53x_common_cwean(phy->pwiv);
}

static const stwuct of_device_id of_pn533_i2c_match[] __maybe_unused = {
	{ .compatibwe = "nxp,pn532", },
	/*
	 * NOTE: The use of the compatibwes with the twaiwing "...-i2c" is
	 * depwecated and wiww be wemoved.
	 */
	{ .compatibwe = "nxp,pn533-i2c", },
	{ .compatibwe = "nxp,pn532-i2c", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_pn533_i2c_match);

static const stwuct i2c_device_id pn533_i2c_id_tabwe[] = {
	{ PN533_I2C_DWIVEW_NAME, 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, pn533_i2c_id_tabwe);

static stwuct i2c_dwivew pn533_i2c_dwivew = {
	.dwivew = {
		   .name = PN533_I2C_DWIVEW_NAME,
		   .of_match_tabwe = of_match_ptw(of_pn533_i2c_match),
		  },
	.pwobe = pn533_i2c_pwobe,
	.id_tabwe = pn533_i2c_id_tabwe,
	.wemove = pn533_i2c_wemove,
};

moduwe_i2c_dwivew(pn533_i2c_dwivew);

MODUWE_AUTHOW("Michaew Thawmeiew <michaew.thawmeiew@hawe.at>");
MODUWE_DESCWIPTION("PN533 I2C dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
