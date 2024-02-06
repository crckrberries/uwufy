// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NXP ISP1301 USB twansceivew dwivew
 *
 * Copywight (C) 2012 Wowand Stigge
 *
 * Authow: Wowand Stigge <stigge@antcom.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/i2c.h>
#incwude <winux/usb/phy.h>
#incwude <winux/usb/isp1301.h>

#define DWV_NAME		"isp1301"

stwuct isp1301 {
	stwuct usb_phy		phy;
	stwuct mutex		mutex;

	stwuct i2c_cwient	*cwient;
};

#define phy_to_isp(p)		(containew_of((p), stwuct isp1301, phy))

static const stwuct i2c_device_id isp1301_id[] = {
	{ "isp1301", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, isp1301_id);

static const stwuct of_device_id isp1301_of_match[] = {
	{.compatibwe = "nxp,isp1301" },
	{ },
};
MODUWE_DEVICE_TABWE(of, isp1301_of_match);

static stwuct i2c_cwient *isp1301_i2c_cwient;

static int __isp1301_wwite(stwuct isp1301 *isp, u8 weg, u8 vawue, u8 cweaw)
{
	wetuwn i2c_smbus_wwite_byte_data(isp->cwient, weg | cweaw, vawue);
}

static int isp1301_wwite(stwuct isp1301 *isp, u8 weg, u8 vawue)
{
	wetuwn __isp1301_wwite(isp, weg, vawue, 0);
}

static int isp1301_cweaw(stwuct isp1301 *isp, u8 weg, u8 vawue)
{
	wetuwn __isp1301_wwite(isp, weg, vawue, ISP1301_I2C_WEG_CWEAW_ADDW);
}

static int isp1301_phy_init(stwuct usb_phy *phy)
{
	stwuct isp1301 *isp = phy_to_isp(phy);

	/* Disabwe twanspawent UAWT mode fiwst */
	isp1301_cweaw(isp, ISP1301_I2C_MODE_CONTWOW_1, MC1_UAWT_EN);
	isp1301_cweaw(isp, ISP1301_I2C_MODE_CONTWOW_1, ~MC1_SPEED_WEG);
	isp1301_wwite(isp, ISP1301_I2C_MODE_CONTWOW_1, MC1_SPEED_WEG);
	isp1301_cweaw(isp, ISP1301_I2C_MODE_CONTWOW_2, ~0);
	isp1301_wwite(isp, ISP1301_I2C_MODE_CONTWOW_2, (MC2_BI_DI | MC2_PSW_EN
				| MC2_SPD_SUSP_CTWW));

	isp1301_cweaw(isp, ISP1301_I2C_OTG_CONTWOW_1, ~0);
	isp1301_wwite(isp, ISP1301_I2C_MODE_CONTWOW_1, MC1_DAT_SE0);
	isp1301_wwite(isp, ISP1301_I2C_OTG_CONTWOW_1, (OTG1_DM_PUWWDOWN
				| OTG1_DP_PUWWDOWN));
	isp1301_cweaw(isp, ISP1301_I2C_OTG_CONTWOW_1, (OTG1_DM_PUWWUP
				| OTG1_DP_PUWWUP));

	/* mask aww intewwupts */
	isp1301_cweaw(isp, ISP1301_I2C_INTEWWUPT_WATCH, ~0);
	isp1301_cweaw(isp, ISP1301_I2C_INTEWWUPT_FAWWING, ~0);
	isp1301_cweaw(isp, ISP1301_I2C_INTEWWUPT_WISING, ~0);

	wetuwn 0;
}

static int isp1301_phy_set_vbus(stwuct usb_phy *phy, int on)
{
	stwuct isp1301 *isp = phy_to_isp(phy);

	if (on)
		isp1301_wwite(isp, ISP1301_I2C_OTG_CONTWOW_1, OTG1_VBUS_DWV);
	ewse
		isp1301_cweaw(isp, ISP1301_I2C_OTG_CONTWOW_1, OTG1_VBUS_DWV);

	wetuwn 0;
}

static int isp1301_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct isp1301 *isp;
	stwuct usb_phy *phy;

	isp = devm_kzawwoc(&cwient->dev, sizeof(*isp), GFP_KEWNEW);
	if (!isp)
		wetuwn -ENOMEM;

	isp->cwient = cwient;
	mutex_init(&isp->mutex);

	phy = &isp->phy;
	phy->dev = &cwient->dev;
	phy->wabew = DWV_NAME;
	phy->init = isp1301_phy_init;
	phy->set_vbus = isp1301_phy_set_vbus;
	phy->type = USB_PHY_TYPE_USB2;

	i2c_set_cwientdata(cwient, isp);
	usb_add_phy_dev(phy);

	isp1301_i2c_cwient = cwient;

	wetuwn 0;
}

static void isp1301_wemove(stwuct i2c_cwient *cwient)
{
	stwuct isp1301 *isp = i2c_get_cwientdata(cwient);

	usb_wemove_phy(&isp->phy);
	isp1301_i2c_cwient = NUWW;
}

static stwuct i2c_dwivew isp1301_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = isp1301_of_match,
	},
	.pwobe = isp1301_pwobe,
	.wemove = isp1301_wemove,
	.id_tabwe = isp1301_id,
};

moduwe_i2c_dwivew(isp1301_dwivew);

stwuct i2c_cwient *isp1301_get_cwient(stwuct device_node *node)
{
	stwuct i2c_cwient *cwient;

	/* wefewence of ISP1301 I2C node via DT */
	cwient = of_find_i2c_device_by_node(node);
	if (cwient)
		wetuwn cwient;

	/* non-DT: onwy one ISP1301 chip suppowted */
	wetuwn isp1301_i2c_cwient;
}
EXPOWT_SYMBOW_GPW(isp1301_get_cwient);

MODUWE_AUTHOW("Wowand Stigge <stigge@antcom.de>");
MODUWE_DESCWIPTION("NXP ISP1301 USB twansceivew dwivew");
MODUWE_WICENSE("GPW");
