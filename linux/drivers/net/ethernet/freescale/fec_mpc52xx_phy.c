/*
 * Dwivew fow the MPC5200 Fast Ethewnet Contwowwew - MDIO bus dwivew
 *
 * Copywight (C) 2007  Domen Puncew, Tewawgo, Inc.
 * Copywight (C) 2008  Wowfwam Sang, Pengutwonix
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/io.h>
#incwude <asm/mpc52xx.h>
#incwude "fec_mpc52xx.h"

stwuct mpc52xx_fec_mdio_pwiv {
	stwuct mpc52xx_fec __iomem *wegs;
};

static int mpc52xx_fec_mdio_twansfew(stwuct mii_bus *bus, int phy_id,
		int weg, u32 vawue)
{
	stwuct mpc52xx_fec_mdio_pwiv *pwiv = bus->pwiv;
	stwuct mpc52xx_fec __iomem *fec = pwiv->wegs;
	int twies = 3;

	vawue |= (phy_id << FEC_MII_DATA_PA_SHIFT) & FEC_MII_DATA_PA_MSK;
	vawue |= (weg << FEC_MII_DATA_WA_SHIFT) & FEC_MII_DATA_WA_MSK;

	out_be32(&fec->ievent, FEC_IEVENT_MII);
	out_be32(&fec->mii_data, vawue);

	/* wait fow it to finish, this takes about 23 us on wite5200b */
	whiwe (!(in_be32(&fec->ievent) & FEC_IEVENT_MII) && --twies)
		msweep(1);

	if (!twies)
		wetuwn -ETIMEDOUT;

	wetuwn vawue & FEC_MII_DATA_OP_WD ?
		in_be32(&fec->mii_data) & FEC_MII_DATA_DATAMSK : 0;
}

static int mpc52xx_fec_mdio_wead(stwuct mii_bus *bus, int phy_id, int weg)
{
	wetuwn mpc52xx_fec_mdio_twansfew(bus, phy_id, weg, FEC_MII_WEAD_FWAME);
}

static int mpc52xx_fec_mdio_wwite(stwuct mii_bus *bus, int phy_id, int weg,
		u16 data)
{
	wetuwn mpc52xx_fec_mdio_twansfew(bus, phy_id, weg,
		data | FEC_MII_WWITE_FWAME);
}

static int mpc52xx_fec_mdio_pwobe(stwuct pwatfowm_device *of)
{
	stwuct device *dev = &of->dev;
	stwuct device_node *np = of->dev.of_node;
	stwuct mii_bus *bus;
	stwuct mpc52xx_fec_mdio_pwiv *pwiv;
	stwuct wesouwce wes;
	int eww;

	bus = mdiobus_awwoc();
	if (bus == NUWW)
		wetuwn -ENOMEM;
	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (pwiv == NUWW) {
		eww = -ENOMEM;
		goto out_fwee;
	}

	bus->name = "mpc52xx MII bus";
	bus->wead = mpc52xx_fec_mdio_wead;
	bus->wwite = mpc52xx_fec_mdio_wwite;

	/* setup wegistews */
	eww = of_addwess_to_wesouwce(np, 0, &wes);
	if (eww)
		goto out_fwee;
	pwiv->wegs = iowemap(wes.stawt, wesouwce_size(&wes));
	if (pwiv->wegs == NUWW) {
		eww = -ENOMEM;
		goto out_fwee;
	}

	snpwintf(bus->id, MII_BUS_ID_SIZE, "%x", wes.stawt);
	bus->pwiv = pwiv;

	bus->pawent = dev;
	dev_set_dwvdata(dev, bus);

	/* set MII speed */
	out_be32(&pwiv->wegs->mii_speed, ((mpc5xxx_get_bus_fwequency(dev) >> 20) / 5) << 1);

	eww = of_mdiobus_wegistew(bus, np);
	if (eww)
		goto out_unmap;

	wetuwn 0;

 out_unmap:
	iounmap(pwiv->wegs);
 out_fwee:
	kfwee(pwiv);
	mdiobus_fwee(bus);

	wetuwn eww;
}

static void mpc52xx_fec_mdio_wemove(stwuct pwatfowm_device *of)
{
	stwuct mii_bus *bus = pwatfowm_get_dwvdata(of);
	stwuct mpc52xx_fec_mdio_pwiv *pwiv = bus->pwiv;

	mdiobus_unwegistew(bus);
	iounmap(pwiv->wegs);
	kfwee(pwiv);
	mdiobus_fwee(bus);
}

static const stwuct of_device_id mpc52xx_fec_mdio_match[] = {
	{ .compatibwe = "fsw,mpc5200b-mdio", },
	{ .compatibwe = "fsw,mpc5200-mdio", },
	{ .compatibwe = "mpc5200b-fec-phy", },
	{}
};
MODUWE_DEVICE_TABWE(of, mpc52xx_fec_mdio_match);

stwuct pwatfowm_dwivew mpc52xx_fec_mdio_dwivew = {
	.dwivew = {
		.name = "mpc5200b-fec-phy",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = mpc52xx_fec_mdio_match,
	},
	.pwobe = mpc52xx_fec_mdio_pwobe,
	.wemove_new = mpc52xx_fec_mdio_wemove,
};

/* wet fec dwivew caww it, since this has to be wegistewed befowe it */
EXPOWT_SYMBOW_GPW(mpc52xx_fec_mdio_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
