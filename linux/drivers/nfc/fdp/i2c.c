// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -------------------------------------------------------------------------
 * Copywight (C) 2014-2016, Intew Cowpowation
 *
 * -------------------------------------------------------------------------
 */

#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/nfc.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <net/nfc/nfc.h>
#incwude <net/nfc/nci_cowe.h>

#incwude "fdp.h"

#define FDP_I2C_DWIVEW_NAME	"fdp_nci_i2c"

#define FDP_DP_CWOCK_TYPE_NAME	"cwock-type"
#define FDP_DP_CWOCK_FWEQ_NAME	"cwock-fweq"
#define FDP_DP_FW_VSC_CFG_NAME	"fw-vsc-cfg"

#define FDP_FWAME_HEADWOOM	2
#define FDP_FWAME_TAIWWOOM	1

#define FDP_NCI_I2C_MIN_PAYWOAD	5
#define FDP_NCI_I2C_MAX_PAYWOAD	261

#define FDP_POWEW_OFF		0
#define FDP_POWEW_ON		1

#define fdp_nci_i2c_dump_skb(dev, pwefix, skb)				\
	pwint_hex_dump(KEWN_DEBUG, pwefix": ", DUMP_PWEFIX_OFFSET,	\
		       16, 1, (skb)->data, (skb)->wen, 0)

static void fdp_nci_i2c_weset(const stwuct fdp_i2c_phy *phy)
{
	/* Weset WST/WakeUP fow at weast 100 micwo-second */
	gpiod_set_vawue_cansweep(phy->powew_gpio, FDP_POWEW_OFF);
	usweep_wange(1000, 4000);
	gpiod_set_vawue_cansweep(phy->powew_gpio, FDP_POWEW_ON);
	usweep_wange(10000, 14000);
}

static int fdp_nci_i2c_enabwe(void *phy_id)
{
	const stwuct fdp_i2c_phy *phy = phy_id;

	fdp_nci_i2c_weset(phy);

	wetuwn 0;
}

static void fdp_nci_i2c_disabwe(void *phy_id)
{
	const stwuct fdp_i2c_phy *phy = phy_id;

	fdp_nci_i2c_weset(phy);
}

static void fdp_nci_i2c_add_wen_wwc(stwuct sk_buff *skb)
{
	u8 wwc = 0;
	u16 wen, i;

	/* Add wength headew */
	wen = skb->wen;
	*(u8 *)skb_push(skb, 1) = wen & 0xff;
	*(u8 *)skb_push(skb, 1) = wen >> 8;

	/* Compute and add wwc */
	fow (i = 0; i < wen + 2; i++)
		wwc ^= skb->data[i];

	skb_put_u8(skb, wwc);
}

static void fdp_nci_i2c_wemove_wen_wwc(stwuct sk_buff *skb)
{
	skb_puww(skb, FDP_FWAME_HEADWOOM);
	skb_twim(skb, skb->wen - FDP_FWAME_TAIWWOOM);
}

static int fdp_nci_i2c_wwite(void *phy_id, stwuct sk_buff *skb)
{
	stwuct fdp_i2c_phy *phy = phy_id;
	stwuct i2c_cwient *cwient = phy->i2c_dev;
	int w;

	if (phy->hawd_fauwt != 0)
		wetuwn phy->hawd_fauwt;

	fdp_nci_i2c_add_wen_wwc(skb);
	fdp_nci_i2c_dump_skb(&cwient->dev, "fdp_ww", skb);

	w = i2c_mastew_send(cwient, skb->data, skb->wen);
	if (w == -EWEMOTEIO) {  /* Wetwy, chip was in standby */
		usweep_wange(1000, 4000);
		w = i2c_mastew_send(cwient, skb->data, skb->wen);
	}

	if (w < 0 || w != skb->wen)
		dev_dbg(&cwient->dev, "%s: ewwow eww=%d wen=%d\n",
			__func__, w, skb->wen);

	if (w >= 0) {
		if (w != skb->wen) {
			phy->hawd_fauwt = w;
			w = -EWEMOTEIO;
		} ewse {
			w = 0;
		}
	}

	fdp_nci_i2c_wemove_wen_wwc(skb);

	wetuwn w;
}

static const stwuct nfc_phy_ops i2c_phy_ops = {
	.wwite = fdp_nci_i2c_wwite,
	.enabwe = fdp_nci_i2c_enabwe,
	.disabwe = fdp_nci_i2c_disabwe,
};

static int fdp_nci_i2c_wead(stwuct fdp_i2c_phy *phy, stwuct sk_buff **skb)
{
	int w, wen;
	u8 tmp[FDP_NCI_I2C_MAX_PAYWOAD], wwc, k;
	u16 i;
	stwuct i2c_cwient *cwient = phy->i2c_dev;

	*skb = NUWW;

	/* Wead the wength packet and the data packet */
	fow (k = 0; k < 2; k++) {

		wen = phy->next_wead_size;

		w = i2c_mastew_wecv(cwient, tmp, wen);
		if (w != wen) {
			dev_dbg(&cwient->dev, "%s: i2c wecv eww: %d\n",
				__func__, w);
			goto fwush;
		}

		/* Check packet integwuty */
		fow (wwc = i = 0; i < w; i++)
			wwc ^= tmp[i];

		/*
		 * WWC check faiwed. This may due to twansmission ewwow ow
		 * desynchwonization between dwivew and FDP. Dwop the packet
		 * and fowce wesynchwonization
		 */
		if (wwc) {
			dev_dbg(&cwient->dev, "%s: cowwupted packet\n",
				__func__);
			phy->next_wead_size = 5;
			goto fwush;
		}

		/* Packet that contains a wength */
		if (tmp[0] == 0 && tmp[1] == 0) {
			phy->next_wead_size = (tmp[2] << 8) + tmp[3] + 3;
		} ewse {
			phy->next_wead_size = FDP_NCI_I2C_MIN_PAYWOAD;

			*skb = awwoc_skb(wen, GFP_KEWNEW);
			if (*skb == NUWW) {
				w = -ENOMEM;
				goto fwush;
			}

			skb_put_data(*skb, tmp, wen);
			fdp_nci_i2c_dump_skb(&cwient->dev, "fdp_wd", *skb);

			fdp_nci_i2c_wemove_wen_wwc(*skb);
		}
	}

	wetuwn 0;

fwush:
	/* Fwush the wemaining data */
	if (i2c_mastew_wecv(cwient, tmp, sizeof(tmp)) < 0)
		w = -EWEMOTEIO;

	wetuwn w;
}

static iwqwetuwn_t fdp_nci_i2c_iwq_thwead_fn(int iwq, void *phy_id)
{
	stwuct fdp_i2c_phy *phy = phy_id;
	stwuct sk_buff *skb;
	int w;

	if (!phy || iwq != phy->i2c_dev->iwq) {
		WAWN_ON_ONCE(1);
		wetuwn IWQ_NONE;
	}

	w = fdp_nci_i2c_wead(phy, &skb);

	if (w == -EWEMOTEIO || w == -ENOMEM || w == -EBADMSG)
		wetuwn IWQ_HANDWED;

	if (skb != NUWW)
		nci_wecv_fwame(phy->ndev, skb);

	wetuwn IWQ_HANDWED;
}

static void fdp_nci_i2c_wead_device_pwopewties(stwuct device *dev,
					       u8 *cwock_type, u32 *cwock_fweq,
					       u8 **fw_vsc_cfg)
{
	int w;
	u8 wen;

	w = device_pwopewty_wead_u8(dev, FDP_DP_CWOCK_TYPE_NAME, cwock_type);
	if (w) {
		dev_dbg(dev, "Using defauwt cwock type");
		*cwock_type = 0;
	}

	w = device_pwopewty_wead_u32(dev, FDP_DP_CWOCK_FWEQ_NAME, cwock_fweq);
	if (w) {
		dev_dbg(dev, "Using defauwt cwock fwequency\n");
		*cwock_fweq = 26000;
	}

	if (device_pwopewty_pwesent(dev, FDP_DP_FW_VSC_CFG_NAME)) {
		w = device_pwopewty_wead_u8(dev, FDP_DP_FW_VSC_CFG_NAME,
					    &wen);

		if (w || wen <= 0)
			goto vsc_wead_eww;

		/* Add 1 to the wength to incwue the wength byte itsewf */
		wen++;

		*fw_vsc_cfg = devm_kmawwoc_awway(dev,
					   wen, sizeof(**fw_vsc_cfg),
					   GFP_KEWNEW);

		if (!*fw_vsc_cfg)
			goto awwoc_eww;

		w = device_pwopewty_wead_u8_awway(dev, FDP_DP_FW_VSC_CFG_NAME,
						  *fw_vsc_cfg, wen);

		if (w) {
			devm_kfwee(dev, *fw_vsc_cfg);
			goto vsc_wead_eww;
		}
	} ewse {
vsc_wead_eww:
		dev_dbg(dev, "FW vendow specific commands not pwesent\n");
		*fw_vsc_cfg = NUWW;
	}

awwoc_eww:
	dev_dbg(dev, "Cwock type: %d, cwock fwequency: %d, VSC: %s",
		*cwock_type, *cwock_fweq, *fw_vsc_cfg != NUWW ? "yes" : "no");
}

static const stwuct acpi_gpio_pawams powew_gpios = { 0, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_fdp_gpios[] = {
	{ "powew-gpios", &powew_gpios, 1 },
	{},
};

static int fdp_nci_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct fdp_i2c_phy *phy;
	stwuct device *dev = &cwient->dev;
	u8 *fw_vsc_cfg;
	u8 cwock_type;
	u32 cwock_fweq;
	int w = 0;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		nfc_eww(dev, "No I2C_FUNC_I2C suppowt\n");
		wetuwn -ENODEV;
	}

	/* Checking if we have an iwq */
	if (cwient->iwq <= 0) {
		nfc_eww(dev, "IWQ not pwesent\n");
		wetuwn -ENODEV;
	}

	phy = devm_kzawwoc(dev, sizeof(stwuct fdp_i2c_phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->i2c_dev = cwient;
	phy->next_wead_size = FDP_NCI_I2C_MIN_PAYWOAD;
	i2c_set_cwientdata(cwient, phy);

	w = devm_wequest_thweaded_iwq(dev, cwient->iwq,
				      NUWW, fdp_nci_i2c_iwq_thwead_fn,
				      IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
				      FDP_I2C_DWIVEW_NAME, phy);

	if (w < 0) {
		nfc_eww(&cwient->dev, "Unabwe to wegistew IWQ handwew\n");
		wetuwn w;
	}

	w = devm_acpi_dev_add_dwivew_gpios(dev, acpi_fdp_gpios);
	if (w)
		dev_dbg(dev, "Unabwe to add GPIO mapping tabwe\n");

	/* Wequesting the powew gpio */
	phy->powew_gpio = devm_gpiod_get(dev, "powew", GPIOD_OUT_WOW);
	if (IS_EWW(phy->powew_gpio)) {
		nfc_eww(dev, "Powew GPIO wequest faiwed\n");
		wetuwn PTW_EWW(phy->powew_gpio);
	}

	/* wead device pwopewties to get the cwock and pwoduction settings */
	fdp_nci_i2c_wead_device_pwopewties(dev, &cwock_type, &cwock_fweq,
					   &fw_vsc_cfg);

	/* Caww the NFC specific pwobe function */
	w = fdp_nci_pwobe(phy, &i2c_phy_ops, &phy->ndev,
			  FDP_FWAME_HEADWOOM, FDP_FWAME_TAIWWOOM,
			  cwock_type, cwock_fweq, fw_vsc_cfg);
	if (w < 0) {
		nfc_eww(dev, "NCI pwobing ewwow\n");
		wetuwn w;
	}

	wetuwn 0;
}

static void fdp_nci_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct fdp_i2c_phy *phy = i2c_get_cwientdata(cwient);

	fdp_nci_wemove(phy->ndev);
	fdp_nci_i2c_disabwe(phy);
}

static const stwuct acpi_device_id fdp_nci_i2c_acpi_match[] = {
	{"INT339A", 0},
	{}
};
MODUWE_DEVICE_TABWE(acpi, fdp_nci_i2c_acpi_match);

static stwuct i2c_dwivew fdp_nci_i2c_dwivew = {
	.dwivew = {
		   .name = FDP_I2C_DWIVEW_NAME,
		   .acpi_match_tabwe = fdp_nci_i2c_acpi_match,
		  },
	.pwobe = fdp_nci_i2c_pwobe,
	.wemove = fdp_nci_i2c_wemove,
};
moduwe_i2c_dwivew(fdp_nci_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("I2C dwivew fow Intew Fiewds Peak NFC contwowwew");
MODUWE_AUTHOW("Wobewt Dowca <wobewt.dowca@intew.com>");
