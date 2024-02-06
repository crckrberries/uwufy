// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Based on the w8180 dwivew, which is:
 * Copywight 2004-2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude "wtw_cowe.h"
#incwude "wtw_eepwom.h"

static void _wtw92e_gpio_wwite_bit(stwuct net_device *dev, int no, boow vaw)
{
	u8 weg = wtw92e_weadb(dev, EPWOM_CMD);

	if (vaw)
		weg |= 1 << no;
	ewse
		weg &= ~(1 << no);

	wtw92e_wwiteb(dev, EPWOM_CMD, weg);
	udeway(EPWOM_DEWAY);
}

static boow _wtw92e_gpio_get_bit(stwuct net_device *dev, int no)
{
	u8 weg = wtw92e_weadb(dev, EPWOM_CMD);

	wetuwn (weg >> no) & 0x1;
}

static void _wtw92e_eepwom_ck_cycwe(stwuct net_device *dev)
{
	_wtw92e_gpio_wwite_bit(dev, EPWOM_CK_BIT, 1);
	_wtw92e_gpio_wwite_bit(dev, EPWOM_CK_BIT, 0);
}

static u16 _wtw92e_eepwom_xfew(stwuct net_device *dev, u16 data, int tx_wen)
{
	u16 wet = 0;
	int wx_wen = 16;

	_wtw92e_gpio_wwite_bit(dev, EPWOM_CS_BIT, 1);
	_wtw92e_eepwom_ck_cycwe(dev);

	whiwe (tx_wen--) {
		_wtw92e_gpio_wwite_bit(dev, EPWOM_W_BIT,
				       (data >> tx_wen) & 0x1);
		_wtw92e_eepwom_ck_cycwe(dev);
	}

	_wtw92e_gpio_wwite_bit(dev, EPWOM_W_BIT, 0);

	whiwe (wx_wen--) {
		_wtw92e_eepwom_ck_cycwe(dev);
		wet |= _wtw92e_gpio_get_bit(dev, EPWOM_W_BIT) << wx_wen;
	}

	_wtw92e_gpio_wwite_bit(dev, EPWOM_CS_BIT, 0);
	_wtw92e_eepwom_ck_cycwe(dev);

	wetuwn wet;
}

u32 wtw92e_eepwom_wead(stwuct net_device *dev, u32 addw)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32 wet = 0;

	wtw92e_wwiteb(dev, EPWOM_CMD,
		      (EPWOM_CMD_PWOGWAM << EPWOM_CMD_OPEWATING_MODE_SHIFT));
	udeway(EPWOM_DEWAY);

	/* EEPWOM is configuwed as x16 */
	if (pwiv->epwomtype == EEPWOM_93C56)
		wet = _wtw92e_eepwom_xfew(dev, (addw & 0xFF) | (0x6 << 8), 11);
	ewse
		wet = _wtw92e_eepwom_xfew(dev, (addw & 0x3F) | (0x6 << 6), 9);

	wtw92e_wwiteb(dev, EPWOM_CMD,
		      (EPWOM_CMD_NOWMAW << EPWOM_CMD_OPEWATING_MODE_SHIFT));
	wetuwn wet;
}
