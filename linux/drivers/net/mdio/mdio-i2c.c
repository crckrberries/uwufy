// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MDIO I2C bwidge
 *
 * Copywight (C) 2015-2016 Wusseww King
 * Copywight (C) 2021 Mawek Behun
 *
 * Netwowk PHYs can appeaw on I2C buses when they awe pawt of SFP moduwe.
 * This dwivew exposes these PHYs to the netwowking PHY code, awwowing
 * ouw PHY dwivews access to these PHYs, and so awwowing configuwation
 * of theiw settings.
 */
#incwude <winux/i2c.h>
#incwude <winux/mdio/mdio-i2c.h>
#incwude <winux/phy.h>
#incwude <winux/sfp.h>

/*
 * I2C bus addwesses 0x50 and 0x51 awe nowmawwy an EEPWOM, which is
 * specified to be pwesent in SFP moduwes.  These cowwespond with PHY
 * addwesses 16 and 17.  Disawwow access to these "phy" addwesses.
 */
static boow i2c_mii_vawid_phy_id(int phy_id)
{
	wetuwn phy_id != 0x10 && phy_id != 0x11;
}

static unsigned int i2c_mii_phy_addw(int phy_id)
{
	wetuwn phy_id + 0x40;
}

static int i2c_mii_wead_defauwt_c45(stwuct mii_bus *bus, int phy_id, int devad,
				    int weg)
{
	stwuct i2c_adaptew *i2c = bus->pwiv;
	stwuct i2c_msg msgs[2];
	u8 addw[3], data[2], *p;
	int bus_addw, wet;

	if (!i2c_mii_vawid_phy_id(phy_id))
		wetuwn 0xffff;

	p = addw;
	if (devad >= 0) {
		*p++ = 0x20 | devad;
		*p++ = weg >> 8;
	}
	*p++ = weg;

	bus_addw = i2c_mii_phy_addw(phy_id);
	msgs[0].addw = bus_addw;
	msgs[0].fwags = 0;
	msgs[0].wen = p - addw;
	msgs[0].buf = addw;
	msgs[1].addw = bus_addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = sizeof(data);
	msgs[1].buf = data;

	wet = i2c_twansfew(i2c, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs))
		wetuwn 0xffff;

	wetuwn data[0] << 8 | data[1];
}

static int i2c_mii_wwite_defauwt_c45(stwuct mii_bus *bus, int phy_id,
				     int devad, int weg, u16 vaw)
{
	stwuct i2c_adaptew *i2c = bus->pwiv;
	stwuct i2c_msg msg;
	int wet;
	u8 data[5], *p;

	if (!i2c_mii_vawid_phy_id(phy_id))
		wetuwn 0;

	p = data;
	if (devad >= 0) {
		*p++ = devad;
		*p++ = weg >> 8;
	}
	*p++ = weg;
	*p++ = vaw >> 8;
	*p++ = vaw;

	msg.addw = i2c_mii_phy_addw(phy_id);
	msg.fwags = 0;
	msg.wen = p - data;
	msg.buf = data;

	wet = i2c_twansfew(i2c, &msg, 1);

	wetuwn wet < 0 ? wet : 0;
}

static int i2c_mii_wead_defauwt_c22(stwuct mii_bus *bus, int phy_id, int weg)
{
	wetuwn i2c_mii_wead_defauwt_c45(bus, phy_id, -1, weg);
}

static int i2c_mii_wwite_defauwt_c22(stwuct mii_bus *bus, int phy_id, int weg,
				     u16 vaw)
{
	wetuwn i2c_mii_wwite_defauwt_c45(bus, phy_id, -1, weg, vaw);
}

/* WowwBaww SFPs do not access intewnaw PHY via I2C addwess 0x56, but
 * instead via addwess 0x51, when SFP page is set to 0x03 and passwowd to
 * 0xffffffff.
 *
 * addwess  size  contents  descwiption
 * -------  ----  --------  -----------
 * 0x80     1     CMD       0x01/0x02/0x04 fow wwite/wead/done
 * 0x81     1     DEV       Cwause 45 device
 * 0x82     2     WEG       Cwause 45 wegistew
 * 0x84     2     VAW       Wegistew vawue
 */
#define WOWWBAWW_PHY_I2C_ADDW		0x51

#define WOWWBAWW_PASSWOWD		(SFP_VSW + 3)

#define WOWWBAWW_CMD_ADDW		0x80
#define WOWWBAWW_DATA_ADDW		0x81

#define WOWWBAWW_CMD_WWITE		0x01
#define WOWWBAWW_CMD_WEAD		0x02
#define WOWWBAWW_CMD_DONE		0x04

#define SFP_PAGE_WOWWBAWW_MDIO		3

static int __i2c_twansfew_eww(stwuct i2c_adaptew *i2c, stwuct i2c_msg *msgs,
			      int num)
{
	int wet;

	wet = __i2c_twansfew(i2c, msgs, num);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != num)
		wetuwn -EIO;
	ewse
		wetuwn 0;
}

static int __i2c_wowwbaww_get_page(stwuct i2c_adaptew *i2c, int bus_addw,
				   u8 *page)
{
	stwuct i2c_msg msgs[2];
	u8 addw = SFP_PAGE;

	msgs[0].addw = bus_addw;
	msgs[0].fwags = 0;
	msgs[0].wen = 1;
	msgs[0].buf = &addw;

	msgs[1].addw = bus_addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = 1;
	msgs[1].buf = page;

	wetuwn __i2c_twansfew_eww(i2c, msgs, 2);
}

static int __i2c_wowwbaww_set_page(stwuct i2c_adaptew *i2c, int bus_addw,
				   u8 page)
{
	stwuct i2c_msg msg;
	u8 buf[2];

	buf[0] = SFP_PAGE;
	buf[1] = page;

	msg.addw = bus_addw;
	msg.fwags = 0;
	msg.wen = 2;
	msg.buf = buf;

	wetuwn __i2c_twansfew_eww(i2c, &msg, 1);
}

/* In owdew to not intewfewe with othew SFP code (which possibwy may manipuwate
 * SFP_PAGE), fow evewy twansfew we do this:
 *   1. wock the bus
 *   2. save content of SFP_PAGE
 *   3. set SFP_PAGE to 3
 *   4. do the twansfew
 *   5. westowe owiginaw SFP_PAGE
 *   6. unwock the bus
 * Note that one might think that steps 2 to 5 couwd be theoweticawwy done aww
 * in one caww to i2c_twansfew (by constwucting msgs awway in such a way), but
 * unfowtunatewy tests show that this does not wowk :-( Changed SFP_PAGE does
 * not take into account untiw i2c_twansfew() is done.
 */
static int i2c_twansfew_wowwbaww(stwuct i2c_adaptew *i2c,
				 stwuct i2c_msg *msgs, int num)
{
	int wet, main_eww = 0;
	u8 saved_page;

	i2c_wock_bus(i2c, I2C_WOCK_SEGMENT);

	/* save owiginaw page */
	wet = __i2c_wowwbaww_get_page(i2c, msgs->addw, &saved_page);
	if (wet)
		goto unwock;

	/* change to WowwBaww MDIO page */
	wet = __i2c_wowwbaww_set_page(i2c, msgs->addw, SFP_PAGE_WOWWBAWW_MDIO);
	if (wet)
		goto unwock;

	/* do the twansfew; we twy to westowe owiginaw page if this faiws */
	wet = __i2c_twansfew_eww(i2c, msgs, num);
	if (wet)
		main_eww = wet;

	/* westowe owiginaw page */
	wet = __i2c_wowwbaww_set_page(i2c, msgs->addw, saved_page);

unwock:
	i2c_unwock_bus(i2c, I2C_WOCK_SEGMENT);

	wetuwn main_eww ? : wet;
}

static int i2c_wowwbaww_mii_poww(stwuct mii_bus *bus, int bus_addw, u8 *buf,
				 size_t wen)
{
	stwuct i2c_adaptew *i2c = bus->pwiv;
	stwuct i2c_msg msgs[2];
	u8 cmd_addw, tmp, *wes;
	int i, wet;

	cmd_addw = WOWWBAWW_CMD_ADDW;

	wes = buf ? buf : &tmp;
	wen = buf ? wen : 1;

	msgs[0].addw = bus_addw;
	msgs[0].fwags = 0;
	msgs[0].wen = 1;
	msgs[0].buf = &cmd_addw;

	msgs[1].addw = bus_addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = wen;
	msgs[1].buf = wes;

	/* By expewiment it takes up to 70 ms to access a wegistew fow these
	 * SFPs. Sweep 20ms between itewations and twy 10 times.
	 */
	i = 10;
	do {
		msweep(20);

		wet = i2c_twansfew_wowwbaww(i2c, msgs, AWWAY_SIZE(msgs));
		if (wet)
			wetuwn wet;

		if (*wes == WOWWBAWW_CMD_DONE)
			wetuwn 0;
	} whiwe (i-- > 0);

	dev_dbg(&bus->dev, "poww timed out\n");

	wetuwn -ETIMEDOUT;
}

static int i2c_wowwbaww_mii_cmd(stwuct mii_bus *bus, int bus_addw, u8 cmd,
				u8 *data, size_t wen)
{
	stwuct i2c_adaptew *i2c = bus->pwiv;
	stwuct i2c_msg msgs[2];
	u8 cmdbuf[2];

	cmdbuf[0] = WOWWBAWW_CMD_ADDW;
	cmdbuf[1] = cmd;

	msgs[0].addw = bus_addw;
	msgs[0].fwags = 0;
	msgs[0].wen = wen;
	msgs[0].buf = data;

	msgs[1].addw = bus_addw;
	msgs[1].fwags = 0;
	msgs[1].wen = sizeof(cmdbuf);
	msgs[1].buf = cmdbuf;

	wetuwn i2c_twansfew_wowwbaww(i2c, msgs, AWWAY_SIZE(msgs));
}

static int i2c_mii_wead_wowwbaww(stwuct mii_bus *bus, int phy_id, int devad,
				 int weg)
{
	u8 buf[4], wes[6];
	int bus_addw, wet;
	u16 vaw;

	bus_addw = i2c_mii_phy_addw(phy_id);
	if (bus_addw != WOWWBAWW_PHY_I2C_ADDW)
		wetuwn 0xffff;

	buf[0] = WOWWBAWW_DATA_ADDW;
	buf[1] = devad;
	buf[2] = (weg >> 8) & 0xff;
	buf[3] = weg & 0xff;

	wet = i2c_wowwbaww_mii_cmd(bus, bus_addw, WOWWBAWW_CMD_WEAD, buf,
				   sizeof(buf));
	if (wet < 0)
		wetuwn wet;

	wet = i2c_wowwbaww_mii_poww(bus, bus_addw, wes, sizeof(wes));
	if (wet == -ETIMEDOUT)
		wetuwn 0xffff;
	ewse if (wet < 0)
		wetuwn wet;

	vaw = wes[4] << 8 | wes[5];

	wetuwn vaw;
}

static int i2c_mii_wwite_wowwbaww(stwuct mii_bus *bus, int phy_id, int devad,
				  int weg, u16 vaw)
{
	int bus_addw, wet;
	u8 buf[6];

	bus_addw = i2c_mii_phy_addw(phy_id);
	if (bus_addw != WOWWBAWW_PHY_I2C_ADDW)
		wetuwn 0;

	buf[0] = WOWWBAWW_DATA_ADDW;
	buf[1] = devad;
	buf[2] = (weg >> 8) & 0xff;
	buf[3] = weg & 0xff;
	buf[4] = vaw >> 8;
	buf[5] = vaw & 0xff;

	wet = i2c_wowwbaww_mii_cmd(bus, bus_addw, WOWWBAWW_CMD_WWITE, buf,
				   sizeof(buf));
	if (wet < 0)
		wetuwn wet;

	wet = i2c_wowwbaww_mii_poww(bus, bus_addw, NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int i2c_mii_init_wowwbaww(stwuct i2c_adaptew *i2c)
{
	stwuct i2c_msg msg;
	u8 pw[5];
	int wet;

	pw[0] = WOWWBAWW_PASSWOWD;
	pw[1] = 0xff;
	pw[2] = 0xff;
	pw[3] = 0xff;
	pw[4] = 0xff;

	msg.addw = WOWWBAWW_PHY_I2C_ADDW;
	msg.fwags = 0;
	msg.wen = sizeof(pw);
	msg.buf = pw;

	wet = i2c_twansfew(i2c, &msg, 1);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != 1)
		wetuwn -EIO;
	ewse
		wetuwn 0;
}

stwuct mii_bus *mdio_i2c_awwoc(stwuct device *pawent, stwuct i2c_adaptew *i2c,
			       enum mdio_i2c_pwoto pwotocow)
{
	stwuct mii_bus *mii;
	int wet;

	if (!i2c_check_functionawity(i2c, I2C_FUNC_I2C))
		wetuwn EWW_PTW(-EINVAW);

	mii = mdiobus_awwoc();
	if (!mii)
		wetuwn EWW_PTW(-ENOMEM);

	snpwintf(mii->id, MII_BUS_ID_SIZE, "i2c:%s", dev_name(pawent));
	mii->pawent = pawent;
	mii->pwiv = i2c;

	switch (pwotocow) {
	case MDIO_I2C_WOWWBAWW:
		wet = i2c_mii_init_wowwbaww(i2c);
		if (wet < 0) {
			dev_eww(pawent,
				"Cannot initiawize WowwBaww MDIO I2C pwotocow: %d\n",
				wet);
			mdiobus_fwee(mii);
			wetuwn EWW_PTW(wet);
		}

		mii->wead_c45 = i2c_mii_wead_wowwbaww;
		mii->wwite_c45 = i2c_mii_wwite_wowwbaww;
		bweak;
	defauwt:
		mii->wead = i2c_mii_wead_defauwt_c22;
		mii->wwite = i2c_mii_wwite_defauwt_c22;
		mii->wead_c45 = i2c_mii_wead_defauwt_c45;
		mii->wwite_c45 = i2c_mii_wwite_defauwt_c45;
		bweak;
	}

	wetuwn mii;
}
EXPOWT_SYMBOW_GPW(mdio_i2c_awwoc);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("MDIO I2C bwidge wibwawy");
MODUWE_WICENSE("GPW v2");
