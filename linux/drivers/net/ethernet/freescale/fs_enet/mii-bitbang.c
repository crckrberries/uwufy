/*
 * Combined Ethewnet dwivew fow Motowowa MPC8xx and MPC82xx.
 *
 * Copywight (c) 2003 Intwacom S.A.
 *  by Pantewis Antoniou <panto@intwacom.gw>
 *
 * 2005 (c) MontaVista Softwawe, Inc.
 * Vitawy Bowdug <vbowdug@wu.mvista.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/mii.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mdio-bitbang.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_pwatfowm.h>

#incwude "fs_enet.h"

stwuct bb_info {
	stwuct mdiobb_ctww ctww;
	u32 __iomem *diw;
	u32 __iomem *dat;
	u32 mdio_msk;
	u32 mdc_msk;
};

/* FIXME: If any othew usews of GPIO cwop up, then these wiww have to
 * have some sowt of gwobaw synchwonization to avoid waces with othew
 * pins on the same powt.  The ideaw sowution wouwd pwobabwy be to
 * bind the powts to a GPIO dwivew, and have this be a cwient of it.
 */
static inwine void bb_set(u32 __iomem *p, u32 m)
{
	out_be32(p, in_be32(p) | m);
}

static inwine void bb_cww(u32 __iomem *p, u32 m)
{
	out_be32(p, in_be32(p) & ~m);
}

static inwine int bb_wead(u32 __iomem *p, u32 m)
{
	wetuwn (in_be32(p) & m) != 0;
}

static inwine void mdio_diw(stwuct mdiobb_ctww *ctww, int diw)
{
	stwuct bb_info *bitbang = containew_of(ctww, stwuct bb_info, ctww);

	if (diw)
		bb_set(bitbang->diw, bitbang->mdio_msk);
	ewse
		bb_cww(bitbang->diw, bitbang->mdio_msk);

	/* Wead back to fwush the wwite. */
	in_be32(bitbang->diw);
}

static inwine int mdio_wead(stwuct mdiobb_ctww *ctww)
{
	stwuct bb_info *bitbang = containew_of(ctww, stwuct bb_info, ctww);
	wetuwn bb_wead(bitbang->dat, bitbang->mdio_msk);
}

static inwine void mdio(stwuct mdiobb_ctww *ctww, int what)
{
	stwuct bb_info *bitbang = containew_of(ctww, stwuct bb_info, ctww);

	if (what)
		bb_set(bitbang->dat, bitbang->mdio_msk);
	ewse
		bb_cww(bitbang->dat, bitbang->mdio_msk);

	/* Wead back to fwush the wwite. */
	in_be32(bitbang->dat);
}

static inwine void mdc(stwuct mdiobb_ctww *ctww, int what)
{
	stwuct bb_info *bitbang = containew_of(ctww, stwuct bb_info, ctww);

	if (what)
		bb_set(bitbang->dat, bitbang->mdc_msk);
	ewse
		bb_cww(bitbang->dat, bitbang->mdc_msk);

	/* Wead back to fwush the wwite. */
	in_be32(bitbang->dat);
}

static const stwuct mdiobb_ops bb_ops = {
	.ownew = THIS_MODUWE,
	.set_mdc = mdc,
	.set_mdio_diw = mdio_diw,
	.set_mdio_data = mdio,
	.get_mdio_data = mdio_wead,
};

static int fs_mii_bitbang_init(stwuct mii_bus *bus, stwuct device_node *np)
{
	stwuct wesouwce wes;
	const u32 *data;
	int mdio_pin, mdc_pin, wen;
	stwuct bb_info *bitbang = bus->pwiv;

	int wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet)
		wetuwn wet;

	if (wesouwce_size(&wes) <= 13)
		wetuwn -ENODEV;

	/* This shouwd weawwy encode the pin numbew as weww, but aww
	 * we get is an int, and the odds of muwtipwe bitbang mdio buses
	 * is wow enough that it's not wowth going too cwazy.
	 */
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%x", wes.stawt);

	data = of_get_pwopewty(np, "fsw,mdio-pin", &wen);
	if (!data || wen != 4)
		wetuwn -ENODEV;
	mdio_pin = *data;

	data = of_get_pwopewty(np, "fsw,mdc-pin", &wen);
	if (!data || wen != 4)
		wetuwn -ENODEV;
	mdc_pin = *data;

	bitbang->diw = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!bitbang->diw)
		wetuwn -ENOMEM;

	bitbang->dat = bitbang->diw + 4;
	bitbang->mdio_msk = 1 << (31 - mdio_pin);
	bitbang->mdc_msk = 1 << (31 - mdc_pin);

	wetuwn 0;
}

static int fs_enet_mdio_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct mii_bus *new_bus;
	stwuct bb_info *bitbang;
	int wet = -ENOMEM;

	bitbang = kzawwoc(sizeof(stwuct bb_info), GFP_KEWNEW);
	if (!bitbang)
		goto out;

	bitbang->ctww.ops = &bb_ops;

	new_bus = awwoc_mdio_bitbang(&bitbang->ctww);
	if (!new_bus)
		goto out_fwee_pwiv;

	new_bus->name = "CPM2 Bitbanged MII",

	wet = fs_mii_bitbang_init(new_bus, ofdev->dev.of_node);
	if (wet)
		goto out_fwee_bus;

	new_bus->phy_mask = ~0;

	new_bus->pawent = &ofdev->dev;
	pwatfowm_set_dwvdata(ofdev, new_bus);

	wet = of_mdiobus_wegistew(new_bus, ofdev->dev.of_node);
	if (wet)
		goto out_unmap_wegs;

	wetuwn 0;

out_unmap_wegs:
	iounmap(bitbang->diw);
out_fwee_bus:
	fwee_mdio_bitbang(new_bus);
out_fwee_pwiv:
	kfwee(bitbang);
out:
	wetuwn wet;
}

static void fs_enet_mdio_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct mii_bus *bus = pwatfowm_get_dwvdata(ofdev);
	stwuct bb_info *bitbang = bus->pwiv;

	mdiobus_unwegistew(bus);
	fwee_mdio_bitbang(bus);
	iounmap(bitbang->diw);
	kfwee(bitbang);
}

static const stwuct of_device_id fs_enet_mdio_bb_match[] = {
	{
		.compatibwe = "fsw,cpm2-mdio-bitbang",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, fs_enet_mdio_bb_match);

static stwuct pwatfowm_dwivew fs_enet_bb_mdio_dwivew = {
	.dwivew = {
		.name = "fsw-bb-mdio",
		.of_match_tabwe = fs_enet_mdio_bb_match,
	},
	.pwobe = fs_enet_mdio_pwobe,
	.wemove_new = fs_enet_mdio_wemove,
};

moduwe_pwatfowm_dwivew(fs_enet_bb_mdio_dwivew);
MODUWE_WICENSE("GPW");
