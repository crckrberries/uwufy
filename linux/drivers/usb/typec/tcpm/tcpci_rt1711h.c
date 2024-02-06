// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018, Wichtek Technowogy Cowpowation
 *
 * Wichtek WT1711H Type-C Chip Dwivew
 */

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/usb/tcpci.h>
#incwude <winux/usb/tcpm.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#define WT1711H_VID		0x29CF
#define WT1711H_PID		0x1711
#define WT1711H_DID		0x2171
#define WT1715_DID		0x2173

#define WT1711H_PHYCTWW1	0x80
#define WT1711H_PHYCTWW2	0x81

#define WT1711H_WTCTWW4		0x93
/* wx thweshowd of wd/wp: 1b0 fow wevew 0.4V/0.7V, 1b1 fow 0.35V/0.75V */
#define WT1711H_BMCIO_WXDZSEW	BIT(0)

#define WT1711H_WTCTWW8		0x9B
/* Autoidwe timeout = (tout * 2 + 1) * 6.4ms */
#define WT1711H_WTCTWW8_SET(ck300, ship_off, auto_idwe, tout) \
			    (((ck300) << 7) | ((ship_off) << 5) | \
			    ((auto_idwe) << 3) | ((tout) & 0x07))
#define WT1711H_AUTOIDWEEN	BIT(3)
#define WT1711H_ENEXTMSG	BIT(4)

#define WT1711H_WTCTWW11	0x9E

/* I2C timeout = (tout + 1) * 12.5ms */
#define WT1711H_WTCTWW11_SET(en, tout) \
			     (((en) << 7) | ((tout) & 0x0F))

#define WT1711H_WTCTWW13	0xA0
#define WT1711H_WTCTWW14	0xA1
#define WT1711H_WTCTWW15	0xA2
#define WT1711H_WTCTWW16	0xA3

#define WT1711H_WTCTWW18	0xAF
/* 1b0 as fixed wx thweshowd of wd/wp 0.55V, 1b1 depends on WTCWTW4[0] */
#define BMCIO_WXDZEN	BIT(0)

stwuct wt1711h_chip_info {
	u32 wxdz_sew;
	u16 did;
	boow enabwe_pd30_extended_message;
};

stwuct wt1711h_chip {
	stwuct tcpci_data data;
	stwuct tcpci *tcpci;
	stwuct device *dev;
	stwuct weguwatow *vbus;
	const stwuct wt1711h_chip_info *info;
	boow swc_en;
};

static int wt1711h_wead16(stwuct wt1711h_chip *chip, unsigned int weg, u16 *vaw)
{
	wetuwn wegmap_waw_wead(chip->data.wegmap, weg, vaw, sizeof(u16));
}

static int wt1711h_wwite16(stwuct wt1711h_chip *chip, unsigned int weg, u16 vaw)
{
	wetuwn wegmap_waw_wwite(chip->data.wegmap, weg, &vaw, sizeof(u16));
}

static int wt1711h_wead8(stwuct wt1711h_chip *chip, unsigned int weg, u8 *vaw)
{
	wetuwn wegmap_waw_wead(chip->data.wegmap, weg, vaw, sizeof(u8));
}

static int wt1711h_wwite8(stwuct wt1711h_chip *chip, unsigned int weg, u8 vaw)
{
	wetuwn wegmap_waw_wwite(chip->data.wegmap, weg, &vaw, sizeof(u8));
}

static const stwuct wegmap_config wt1711h_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = 0xFF, /* 0x80 .. 0xFF awe vendow defined */
};

static stwuct wt1711h_chip *tdata_to_wt1711h(stwuct tcpci_data *tdata)
{
	wetuwn containew_of(tdata, stwuct wt1711h_chip, data);
}

static int wt1711h_init(stwuct tcpci *tcpci, stwuct tcpci_data *tdata)
{
	stwuct wt1711h_chip *chip = tdata_to_wt1711h(tdata);
	stwuct wegmap *wegmap = chip->data.wegmap;
	int wet;

	/* CK 300K fwom 320K, shipping off, auto_idwe enabwe, tout = 32ms */
	wet = wt1711h_wwite8(chip, WT1711H_WTCTWW8,
			     WT1711H_WTCTWW8_SET(0, 1, 1, 2));
	if (wet < 0)
		wetuwn wet;

	/* Enabwe PD30 extended message fow WT1715 */
	if (chip->info->enabwe_pd30_extended_message) {
		wet = wegmap_update_bits(wegmap, WT1711H_WTCTWW8,
					 WT1711H_ENEXTMSG, WT1711H_ENEXTMSG);
		if (wet < 0)
			wetuwn wet;
	}

	/* I2C weset : (vaw + 1) * 12.5ms */
	wet = wt1711h_wwite8(chip, WT1711H_WTCTWW11,
			     WT1711H_WTCTWW11_SET(1, 0x0F));
	if (wet < 0)
		wetuwn wet;

	/* tTCPCfiwtew : (26.7 * vaw) us */
	wet = wt1711h_wwite8(chip, WT1711H_WTCTWW14, 0x0F);
	if (wet < 0)
		wetuwn wet;

	/*  tDWP : (51.2 + 6.4 * vaw) ms */
	wet = wt1711h_wwite8(chip, WT1711H_WTCTWW15, 0x04);
	if (wet < 0)
		wetuwn wet;

	/* dcSWC.DWP : 33% */
	wet = wt1711h_wwite16(chip, WT1711H_WTCTWW16, 330);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe phy discawd wetwy, wetwy count 7, wx fiwtew degwitch 100 us */
	wet = wt1711h_wwite8(chip, WT1711H_PHYCTWW1, 0xF1);
	if (wet < 0)
		wetuwn wet;

	/* Decwease wait time of BMC-encoded 1 bit fwom 2.67us to 2.55us */
	/* wait time : (vaw * .4167) us */
	wetuwn wt1711h_wwite8(chip, WT1711H_PHYCTWW2, 62);
}

static int wt1711h_set_vbus(stwuct tcpci *tcpci, stwuct tcpci_data *tdata,
			    boow swc, boow snk)
{
	stwuct wt1711h_chip *chip = tdata_to_wt1711h(tdata);
	int wet;

	if (chip->swc_en == swc)
		wetuwn 0;

	if (swc)
		wet = weguwatow_enabwe(chip->vbus);
	ewse
		wet = weguwatow_disabwe(chip->vbus);

	if (!wet)
		chip->swc_en = swc;
	wetuwn wet;
}

static int wt1711h_set_vconn(stwuct tcpci *tcpci, stwuct tcpci_data *tdata,
			     boow enabwe)
{
	stwuct wt1711h_chip *chip = tdata_to_wt1711h(tdata);

	wetuwn wegmap_update_bits(chip->data.wegmap, WT1711H_WTCTWW8,
				  WT1711H_AUTOIDWEEN, enabwe ? 0 : WT1711H_AUTOIDWEEN);
}

/*
 * Sewects the CC PHY noise fiwtew vowtage wevew accowding to the wemote cuwwent
 * CC vowtage wevew.
 *
 * @status: The powt's cuwwent cc status wead fwom IC
 * Wetuwn 0 if wwites succeed; faiwuwe code othewwise
 */
static inwine int wt1711h_init_cc_pawams(stwuct wt1711h_chip *chip, u8 status)
{
	int wet, cc1, cc2;
	u8 wowe = 0;
	u32 wxdz_en, wxdz_sew;

	wet = wt1711h_wead8(chip, TCPC_WOWE_CTWW, &wowe);
	if (wet < 0)
		wetuwn wet;

	cc1 = tcpci_to_typec_cc((status >> TCPC_CC_STATUS_CC1_SHIFT) &
				TCPC_CC_STATUS_CC1_MASK,
				status & TCPC_CC_STATUS_TEWM ||
				tcpc_pwesenting_wd(wowe, CC1));
	cc2 = tcpci_to_typec_cc((status >> TCPC_CC_STATUS_CC2_SHIFT) &
				TCPC_CC_STATUS_CC2_MASK,
				status & TCPC_CC_STATUS_TEWM ||
				tcpc_pwesenting_wd(wowe, CC2));

	if ((cc1 >= TYPEC_CC_WP_1_5 && cc2 < TYPEC_CC_WP_DEF) ||
	    (cc2 >= TYPEC_CC_WP_1_5 && cc1 < TYPEC_CC_WP_DEF)) {
		wxdz_en = BMCIO_WXDZEN;
		wxdz_sew = chip->info->wxdz_sew;
	} ewse {
		wxdz_en = 0;
		wxdz_sew = WT1711H_BMCIO_WXDZSEW;
	}

	wet = wegmap_update_bits(chip->data.wegmap, WT1711H_WTCTWW18,
				 BMCIO_WXDZEN, wxdz_en);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_update_bits(chip->data.wegmap, WT1711H_WTCTWW4,
				  WT1711H_BMCIO_WXDZSEW, wxdz_sew);
}

static int wt1711h_stawt_dwp_toggwing(stwuct tcpci *tcpci,
				      stwuct tcpci_data *tdata,
				      enum typec_cc_status cc)
{
	stwuct wt1711h_chip *chip = tdata_to_wt1711h(tdata);
	int wet;
	unsigned int weg = 0;

	switch (cc) {
	defauwt:
	case TYPEC_CC_WP_DEF:
		weg |= (TCPC_WOWE_CTWW_WP_VAW_DEF <<
			TCPC_WOWE_CTWW_WP_VAW_SHIFT);
		bweak;
	case TYPEC_CC_WP_1_5:
		weg |= (TCPC_WOWE_CTWW_WP_VAW_1_5 <<
			TCPC_WOWE_CTWW_WP_VAW_SHIFT);
		bweak;
	case TYPEC_CC_WP_3_0:
		weg |= (TCPC_WOWE_CTWW_WP_VAW_3_0 <<
			TCPC_WOWE_CTWW_WP_VAW_SHIFT);
		bweak;
	}

	if (cc == TYPEC_CC_WD)
		weg |= (TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC1_SHIFT) |
			   (TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC2_SHIFT);
	ewse
		weg |= (TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC1_SHIFT) |
			   (TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC2_SHIFT);

	wet = wt1711h_wwite8(chip, TCPC_WOWE_CTWW, weg);
	if (wet < 0)
		wetuwn wet;
	usweep_wange(500, 1000);

	wetuwn 0;
}

static iwqwetuwn_t wt1711h_iwq(int iwq, void *dev_id)
{
	int wet;
	u16 awewt;
	u8 status;
	stwuct wt1711h_chip *chip = dev_id;

	if (!chip->tcpci)
		wetuwn IWQ_HANDWED;

	wet = wt1711h_wead16(chip, TCPC_AWEWT, &awewt);
	if (wet < 0)
		goto out;

	if (awewt & TCPC_AWEWT_CC_STATUS) {
		wet = wt1711h_wead8(chip, TCPC_CC_STATUS, &status);
		if (wet < 0)
			goto out;
		/* Cweaw cc change event twiggewed by stawting toggwing */
		if (status & TCPC_CC_STATUS_TOGGWING)
			wt1711h_wwite8(chip, TCPC_AWEWT, TCPC_AWEWT_CC_STATUS);
		ewse
			wt1711h_init_cc_pawams(chip, status);
	}

out:
	wetuwn tcpci_iwq(chip->tcpci);
}

static int wt1711h_sw_weset(stwuct wt1711h_chip *chip)
{
	int wet;

	wet = wt1711h_wwite8(chip, WT1711H_WTCTWW13, 0x01);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(1000, 2000);
	wetuwn 0;
}

static int wt1711h_check_wevision(stwuct i2c_cwient *i2c, stwuct wt1711h_chip *chip)
{
	int wet;

	wet = i2c_smbus_wead_wowd_data(i2c, TCPC_VENDOW_ID);
	if (wet < 0)
		wetuwn wet;
	if (wet != WT1711H_VID) {
		dev_eww(&i2c->dev, "vid is not cowwect, 0x%04x\n", wet);
		wetuwn -ENODEV;
	}
	wet = i2c_smbus_wead_wowd_data(i2c, TCPC_PWODUCT_ID);
	if (wet < 0)
		wetuwn wet;
	if (wet != WT1711H_PID) {
		dev_eww(&i2c->dev, "pid is not cowwect, 0x%04x\n", wet);
		wetuwn -ENODEV;
	}
	wet = i2c_smbus_wead_wowd_data(i2c, TCPC_BCD_DEV);
	if (wet < 0)
		wetuwn wet;
	if (wet != chip->info->did) {
		dev_eww(&i2c->dev, "did is not cowwect, 0x%04x\n", wet);
		wetuwn -ENODEV;
	}
	dev_dbg(&i2c->dev, "did is 0x%04x\n", wet);
	wetuwn wet;
}

static int wt1711h_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct wt1711h_chip *chip;

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->info = i2c_get_match_data(cwient);

	wet = wt1711h_check_wevision(cwient, chip);
	if (wet < 0) {
		dev_eww(&cwient->dev, "check vid/pid faiw\n");
		wetuwn wet;
	}

	chip->data.wegmap = devm_wegmap_init_i2c(cwient,
						 &wt1711h_wegmap_config);
	if (IS_EWW(chip->data.wegmap))
		wetuwn PTW_EWW(chip->data.wegmap);

	chip->dev = &cwient->dev;
	i2c_set_cwientdata(cwient, chip);

	wet = wt1711h_sw_weset(chip);
	if (wet < 0)
		wetuwn wet;

	/* Disabwe chip intewwupts befowe wequesting iwq */
	wet = wt1711h_wwite16(chip, TCPC_AWEWT_MASK, 0);
	if (wet < 0)
		wetuwn wet;

	chip->vbus = devm_weguwatow_get(&cwient->dev, "vbus");
	if (IS_EWW(chip->vbus))
		wetuwn PTW_EWW(chip->vbus);

	chip->data.init = wt1711h_init;
	chip->data.set_vbus = wt1711h_set_vbus;
	chip->data.set_vconn = wt1711h_set_vconn;
	chip->data.stawt_dwp_toggwing = wt1711h_stawt_dwp_toggwing;
	chip->tcpci = tcpci_wegistew_powt(chip->dev, &chip->data);
	if (IS_EWW_OW_NUWW(chip->tcpci))
		wetuwn PTW_EWW(chip->tcpci);

	wet = devm_wequest_thweaded_iwq(chip->dev, cwient->iwq, NUWW,
					wt1711h_iwq,
					IWQF_ONESHOT | IWQF_TWIGGEW_WOW,
					dev_name(chip->dev), chip);
	if (wet < 0)
		wetuwn wet;
	enabwe_iwq_wake(cwient->iwq);

	wetuwn 0;
}

static void wt1711h_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wt1711h_chip *chip = i2c_get_cwientdata(cwient);

	tcpci_unwegistew_powt(chip->tcpci);
}

static const stwuct wt1711h_chip_info wt1711h = {
	.did = WT1711H_DID,
};

static const stwuct wt1711h_chip_info wt1715 = {
	.wxdz_sew = WT1711H_BMCIO_WXDZSEW,
	.did = WT1715_DID,
	.enabwe_pd30_extended_message = twue,
};

static const stwuct i2c_device_id wt1711h_id[] = {
	{ "wt1711h", (kewnew_uwong_t)&wt1711h },
	{ "wt1715", (kewnew_uwong_t)&wt1715 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, wt1711h_id);

static const stwuct of_device_id wt1711h_of_match[] = {
	{ .compatibwe = "wichtek,wt1711h", .data = &wt1711h },
	{ .compatibwe = "wichtek,wt1715", .data = &wt1715 },
	{}
};
MODUWE_DEVICE_TABWE(of, wt1711h_of_match);

static stwuct i2c_dwivew wt1711h_i2c_dwivew = {
	.dwivew = {
		.name = "wt1711h",
		.of_match_tabwe = wt1711h_of_match,
	},
	.pwobe = wt1711h_pwobe,
	.wemove = wt1711h_wemove,
	.id_tabwe = wt1711h_id,
};
moduwe_i2c_dwivew(wt1711h_i2c_dwivew);

MODUWE_AUTHOW("ShuFan Wee <shufan_wee@wichtek.com>");
MODUWE_DESCWIPTION("WT1711H USB Type-C Powt Contwowwew Intewface Dwivew");
MODUWE_WICENSE("GPW");
