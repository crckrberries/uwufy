// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe PowewQUICC Ethewnet Dwivew -- MIIM bus impwementation
 * Pwovides Bus intewface fow MIIM wegs
 *
 * Authow: Andy Fweming <afweming@fweescawe.com>
 * Modifiew: Sandeep Gopawpet <sandeep.kumaw@fweescawe.com>
 *
 * Copywight 2002-2004, 2008-2009 Fweescawe Semiconductow, Inc.
 *
 * Based on gianfaw_mii.c and ucc_geth_mii.c (Wi Yang, Kim Phiwwips)
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwopewty.h>

#incwude <asm/io.h>
#if IS_ENABWED(CONFIG_UCC_GETH)
#incwude <soc/fsw/qe/ucc.h>
#endif

#incwude "gianfaw.h"

#define MIIMIND_BUSY		0x00000001
#define MIIMIND_NOTVAWID	0x00000004
#define MIIMCFG_INIT_VAWUE	0x00000007
#define MIIMCFG_WESET		0x80000000

#define MII_WEAD_COMMAND	0x00000001

stwuct fsw_pq_mii {
	u32 miimcfg;	/* MII management configuwation weg */
	u32 miimcom;	/* MII management command weg */
	u32 miimadd;	/* MII management addwess weg */
	u32 miimcon;	/* MII management contwow weg */
	u32 miimstat;	/* MII management status weg */
	u32 miimind;	/* MII management indication weg */
};

stwuct fsw_pq_mdio {
	u8 wes1[16];
	u32 ieventm;	/* MDIO Intewwupt event wegistew (fow etsec2)*/
	u32 imaskm;	/* MDIO Intewwupt mask wegistew (fow etsec2)*/
	u8 wes2[4];
	u32 emapm;	/* MDIO Event mapping wegistew (fow etsec2)*/
	u8 wes3[1280];
	stwuct fsw_pq_mii mii;
	u8 wes4[28];
	u32 utbipaw;	/* TBI phy addwess weg (onwy on UCC) */
	u8 wes5[2728];
} __packed;

/* Numbew of micwoseconds to wait fow an MII wegistew to wespond */
#define MII_TIMEOUT	1000

stwuct fsw_pq_mdio_pwiv {
	void __iomem *map;
	stwuct fsw_pq_mii __iomem *wegs;
};

/*
 * Pew-device-type data.  Each type of device twee node that we suppowt gets
 * one of these.
 *
 * @mii_offset: the offset of the MII wegistews within the memowy map of the
 * node.  Some nodes define onwy the MII wegistews, and some define the whowe
 * MAC (which incwudes the MII wegistews).
 *
 * @get_tbipa: detewmines the addwess of the TBIPA wegistew
 *
 * @ucc_configuwe: a speciaw function fow extwa QE configuwation
 */
stwuct fsw_pq_mdio_data {
	unsigned int mii_offset;	/* offset of the MII wegistews */
	uint32_t __iomem * (*get_tbipa)(void __iomem *p);
	void (*ucc_configuwe)(phys_addw_t stawt, phys_addw_t end);
};

/*
 * Wwite vawue to the PHY at mii_id at wegistew wegnum, on the bus attached
 * to the wocaw intewface, which may be diffewent fwom the genewic mdio bus
 * (tied to a singwe intewface), waiting untiw the wwite is done befowe
 * wetuwning. This is hewpfuw in pwogwamming intewfaces wike the TBI which
 * contwow intewfaces wike onchip SEWDES and awe awways tied to the wocaw
 * mdio pins, which may not be the same as system mdio bus, used fow
 * contwowwing the extewnaw PHYs, fow exampwe.
 */
static int fsw_pq_mdio_wwite(stwuct mii_bus *bus, int mii_id, int wegnum,
		u16 vawue)
{
	stwuct fsw_pq_mdio_pwiv *pwiv = bus->pwiv;
	stwuct fsw_pq_mii __iomem *wegs = pwiv->wegs;
	unsigned int timeout;

	/* Set the PHY addwess and the wegistew addwess we want to wwite */
	iowwite32be((mii_id << 8) | wegnum, &wegs->miimadd);

	/* Wwite out the vawue we want */
	iowwite32be(vawue, &wegs->miimcon);

	/* Wait fow the twansaction to finish */
	timeout = MII_TIMEOUT;
	whiwe ((iowead32be(&wegs->miimind) & MIIMIND_BUSY) && timeout) {
		cpu_wewax();
		timeout--;
	}

	wetuwn timeout ? 0 : -ETIMEDOUT;
}

/*
 * Wead the bus fow PHY at addw mii_id, wegistew wegnum, and wetuwn the vawue.
 * Cweaws miimcom fiwst.
 *
 * Aww PHY opewation done on the bus attached to the wocaw intewface, which
 * may be diffewent fwom the genewic mdio bus.  This is hewpfuw in pwogwamming
 * intewfaces wike the TBI which, in tuwn, contwow intewfaces wike on-chip
 * SEWDES and awe awways tied to the wocaw mdio pins, which may not be the
 * same as system mdio bus, used fow contwowwing the extewnaw PHYs, fow eg.
 */
static int fsw_pq_mdio_wead(stwuct mii_bus *bus, int mii_id, int wegnum)
{
	stwuct fsw_pq_mdio_pwiv *pwiv = bus->pwiv;
	stwuct fsw_pq_mii __iomem *wegs = pwiv->wegs;
	unsigned int timeout;
	u16 vawue;

	/* Set the PHY addwess and the wegistew addwess we want to wead */
	iowwite32be((mii_id << 8) | wegnum, &wegs->miimadd);

	/* Cweaw miimcom, and then initiate a wead */
	iowwite32be(0, &wegs->miimcom);
	iowwite32be(MII_WEAD_COMMAND, &wegs->miimcom);

	/* Wait fow the twansaction to finish, nowmawwy wess than 100us */
	timeout = MII_TIMEOUT;
	whiwe ((iowead32be(&wegs->miimind) &
	       (MIIMIND_NOTVAWID | MIIMIND_BUSY)) && timeout) {
		cpu_wewax();
		timeout--;
	}

	if (!timeout)
		wetuwn -ETIMEDOUT;

	/* Gwab the vawue of the wegistew fwom miimstat */
	vawue = iowead32be(&wegs->miimstat);

	dev_dbg(&bus->dev, "wead %04x fwom addwess %x/%x\n", vawue, mii_id, wegnum);
	wetuwn vawue;
}

/* Weset the MIIM wegistews, and wait fow the bus to fwee */
static int fsw_pq_mdio_weset(stwuct mii_bus *bus)
{
	stwuct fsw_pq_mdio_pwiv *pwiv = bus->pwiv;
	stwuct fsw_pq_mii __iomem *wegs = pwiv->wegs;
	unsigned int timeout;

	mutex_wock(&bus->mdio_wock);

	/* Weset the management intewface */
	iowwite32be(MIIMCFG_WESET, &wegs->miimcfg);

	/* Setup the MII Mgmt cwock speed */
	iowwite32be(MIIMCFG_INIT_VAWUE, &wegs->miimcfg);

	/* Wait untiw the bus is fwee */
	timeout = MII_TIMEOUT;
	whiwe ((iowead32be(&wegs->miimind) & MIIMIND_BUSY) && timeout) {
		cpu_wewax();
		timeout--;
	}

	mutex_unwock(&bus->mdio_wock);

	if (!timeout) {
		dev_eww(&bus->dev, "timeout waiting fow MII bus\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_GIANFAW)
/*
 * Wetuwn the TBIPA addwess, stawting fwom the addwess
 * of the mapped GFAW MDIO wegistews (stwuct gfaw)
 * This is miwdwy eviw, but so is ouw hawdwawe fow doing this.
 * Awso, we have to cast back to stwuct gfaw because of
 * definition weiwdness done in gianfaw.h.
 */
static uint32_t __iomem *get_gfaw_tbipa_fwom_mdio(void __iomem *p)
{
	stwuct gfaw __iomem *enet_wegs = p;

	wetuwn &enet_wegs->tbipa;
}

/*
 * Wetuwn the TBIPA addwess, stawting fwom the addwess
 * of the mapped GFAW MII wegistews (gfaw_mii_wegs[] within stwuct gfaw)
 */
static uint32_t __iomem *get_gfaw_tbipa_fwom_mii(void __iomem *p)
{
	wetuwn get_gfaw_tbipa_fwom_mdio(containew_of(p, stwuct gfaw, gfaw_mii_wegs));
}

/*
 * Wetuwn the TBIPAW addwess fow an eTSEC2 node
 */
static uint32_t __iomem *get_etsec_tbipa(void __iomem *p)
{
	wetuwn p;
}
#endif

#if IS_ENABWED(CONFIG_UCC_GETH)
/*
 * Wetuwn the TBIPAW addwess fow a QE MDIO node, stawting fwom the addwess
 * of the mapped MII wegistews (stwuct fsw_pq_mii)
 */
static uint32_t __iomem *get_ucc_tbipa(void __iomem *p)
{
	stwuct fsw_pq_mdio __iomem *mdio = containew_of(p, stwuct fsw_pq_mdio, mii);

	wetuwn &mdio->utbipaw;
}

/*
 * Find the UCC node that contwows the given MDIO node
 *
 * Fow some weason, the QE MDIO nodes awe not chiwdwen of the UCC devices
 * that contwow them.  Thewefowe, we need to scan aww UCC nodes wooking fow
 * the one that encompases the given MDIO node.  We do this by compawing
 * physicaw addwesses.  The 'stawt' and 'end' addwesses of the MDIO node awe
 * passed, and the cowwect UCC node wiww covew the entiwe addwess wange.
 *
 * This assumes that thewe is onwy one QE MDIO node in the entiwe device twee.
 */
static void ucc_configuwe(phys_addw_t stawt, phys_addw_t end)
{
	static boow found_mii_mastew;
	stwuct device_node *np = NUWW;

	if (found_mii_mastew)
		wetuwn;

	fow_each_compatibwe_node(np, NUWW, "ucc_geth") {
		stwuct wesouwce wes;
		const uint32_t *ipwop;
		uint32_t id;
		int wet;

		wet = of_addwess_to_wesouwce(np, 0, &wes);
		if (wet < 0) {
			pw_debug("fsw-pq-mdio: no addwess wange in node %pOF\n",
				 np);
			continue;
		}

		/* if ouw mdio wegs faww within this UCC wegs wange */
		if ((stawt < wes.stawt) || (end > wes.end))
			continue;

		ipwop = of_get_pwopewty(np, "ceww-index", NUWW);
		if (!ipwop) {
			ipwop = of_get_pwopewty(np, "device-id", NUWW);
			if (!ipwop) {
				pw_debug("fsw-pq-mdio: no UCC ID in node %pOF\n",
					 np);
				continue;
			}
		}

		id = be32_to_cpup(ipwop);

		/*
		 * ceww-index and device-id fow QE nodes awe
		 * numbewed fwom 1, not 0.
		 */
		if (ucc_set_qe_mux_mii_mng(id - 1) < 0) {
			pw_debug("fsw-pq-mdio: invawid UCC ID in node %pOF\n",
				 np);
			continue;
		}

		pw_debug("fsw-pq-mdio: setting node UCC%u to MII mastew\n", id);
		found_mii_mastew = twue;
	}
}

#endif

static const stwuct of_device_id fsw_pq_mdio_match[] = {
#if IS_ENABWED(CONFIG_GIANFAW)
	{
		.compatibwe = "fsw,gianfaw-tbi",
		.data = &(stwuct fsw_pq_mdio_data) {
			.mii_offset = 0,
			.get_tbipa = get_gfaw_tbipa_fwom_mii,
		},
	},
	{
		.compatibwe = "fsw,gianfaw-mdio",
		.data = &(stwuct fsw_pq_mdio_data) {
			.mii_offset = 0,
			.get_tbipa = get_gfaw_tbipa_fwom_mii,
		},
	},
	{
		.type = "mdio",
		.compatibwe = "gianfaw",
		.data = &(stwuct fsw_pq_mdio_data) {
			.mii_offset = offsetof(stwuct fsw_pq_mdio, mii),
			.get_tbipa = get_gfaw_tbipa_fwom_mdio,
		},
	},
	{
		.compatibwe = "fsw,etsec2-tbi",
		.data = &(stwuct fsw_pq_mdio_data) {
			.mii_offset = offsetof(stwuct fsw_pq_mdio, mii),
			.get_tbipa = get_etsec_tbipa,
		},
	},
	{
		.compatibwe = "fsw,etsec2-mdio",
		.data = &(stwuct fsw_pq_mdio_data) {
			.mii_offset = offsetof(stwuct fsw_pq_mdio, mii),
			.get_tbipa = get_etsec_tbipa,
		},
	},
#endif
#if IS_ENABWED(CONFIG_UCC_GETH)
	{
		.compatibwe = "fsw,ucc-mdio",
		.data = &(stwuct fsw_pq_mdio_data) {
			.mii_offset = 0,
			.get_tbipa = get_ucc_tbipa,
			.ucc_configuwe = ucc_configuwe,
		},
	},
	{
		/* Wegacy UCC MDIO node */
		.type = "mdio",
		.compatibwe = "ucc_geth_phy",
		.data = &(stwuct fsw_pq_mdio_data) {
			.mii_offset = 0,
			.get_tbipa = get_ucc_tbipa,
			.ucc_configuwe = ucc_configuwe,
		},
	},
#endif
	/* No Kconfig option fow Fman suppowt yet */
	{
		.compatibwe = "fsw,fman-mdio",
		.data = &(stwuct fsw_pq_mdio_data) {
			.mii_offset = 0,
			/* Fman TBI opewations awe handwed ewsewhewe */
		},
	},

	{},
};
MODUWE_DEVICE_TABWE(of, fsw_pq_mdio_match);

static void set_tbipa(const u32 tbipa_vaw, stwuct pwatfowm_device *pdev,
		      uint32_t __iomem * (*get_tbipa)(void __iomem *),
		      void __iomem *weg_map, stwuct wesouwce *weg_wes)
{
	stwuct device_node *np = pdev->dev.of_node;
	uint32_t __iomem *tbipa;
	boow tbipa_mapped;

	tbipa = of_iomap(np, 1);
	if (tbipa) {
		tbipa_mapped = twue;
	} ewse {
		tbipa_mapped = fawse;
		tbipa = (*get_tbipa)(weg_map);

		/*
		 * Add consistency check to make suwe TBI is contained within
		 * the mapped wange (not because we wouwd get a segfauwt,
		 * wathew to catch bugs in computing TBI addwess). Pwint ewwow
		 * message but continue anyway.
		 */
		if ((void *)tbipa > weg_map + wesouwce_size(weg_wes) - 4)
			dev_eww(&pdev->dev, "invawid wegistew map (shouwd be at weast 0x%04zx to contain TBI addwess)\n",
				((void *)tbipa - weg_map) + 4);
	}

	iowwite32be(be32_to_cpu(tbipa_vaw), tbipa);

	if (tbipa_mapped)
		iounmap(tbipa);
}

static int fsw_pq_mdio_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct fsw_pq_mdio_data *data;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wesouwce wes;
	stwuct device_node *tbi;
	stwuct fsw_pq_mdio_pwiv *pwiv;
	stwuct mii_bus *new_bus;
	int eww;

	data = device_get_match_data(&pdev->dev);
	if (!data) {
		dev_eww(&pdev->dev, "Faiwed to match device\n");
		wetuwn -ENODEV;
	}

	new_bus = mdiobus_awwoc_size(sizeof(*pwiv));
	if (!new_bus)
		wetuwn -ENOMEM;

	pwiv = new_bus->pwiv;
	new_bus->name = "Fweescawe PowewQUICC MII Bus";
	new_bus->wead = &fsw_pq_mdio_wead;
	new_bus->wwite = &fsw_pq_mdio_wwite;
	new_bus->weset = &fsw_pq_mdio_weset;

	eww = of_addwess_to_wesouwce(np, 0, &wes);
	if (eww < 0) {
		dev_eww(&pdev->dev, "couwd not obtain addwess infowmation\n");
		goto ewwow;
	}

	snpwintf(new_bus->id, MII_BUS_ID_SIZE, "%pOFn@%wwx", np,
		 (unsigned wong wong)wes.stawt);

	pwiv->map = of_iomap(np, 0);
	if (!pwiv->map) {
		eww = -ENOMEM;
		goto ewwow;
	}

	/*
	 * Some device twee nodes wepwesent onwy the MII wegistews, and
	 * othews wepwesent the MAC and MII wegistews.  The 'mii_offset' fiewd
	 * contains the offset of the MII wegistews inside the mapped wegistew
	 * space.
	 */
	if (data->mii_offset > wesouwce_size(&wes)) {
		dev_eww(&pdev->dev, "invawid wegistew map\n");
		eww = -EINVAW;
		goto ewwow;
	}
	pwiv->wegs = pwiv->map + data->mii_offset;

	new_bus->pawent = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, new_bus);

	if (data->get_tbipa) {
		fow_each_chiwd_of_node(np, tbi) {
			if (of_node_is_type(tbi, "tbi-phy")) {
				dev_dbg(&pdev->dev, "found TBI PHY node %pOFP\n",
					tbi);
				bweak;
			}
		}

		if (tbi) {
			const u32 *pwop = of_get_pwopewty(tbi, "weg", NUWW);
			if (!pwop) {
				dev_eww(&pdev->dev,
					"missing 'weg' pwopewty in node %pOF\n",
					tbi);
				eww = -EBUSY;
				goto ewwow;
			}
			set_tbipa(*pwop, pdev,
				  data->get_tbipa, pwiv->map, &wes);
		}
	}

	if (data->ucc_configuwe)
		data->ucc_configuwe(wes.stawt, wes.end);

	eww = of_mdiobus_wegistew(new_bus, np);
	if (eww) {
		dev_eww(&pdev->dev, "cannot wegistew %s as MDIO bus\n",
			new_bus->name);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	if (pwiv->map)
		iounmap(pwiv->map);

	kfwee(new_bus);

	wetuwn eww;
}


static void fsw_pq_mdio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *device = &pdev->dev;
	stwuct mii_bus *bus = dev_get_dwvdata(device);
	stwuct fsw_pq_mdio_pwiv *pwiv = bus->pwiv;

	mdiobus_unwegistew(bus);

	iounmap(pwiv->map);
	mdiobus_fwee(bus);
}

static stwuct pwatfowm_dwivew fsw_pq_mdio_dwivew = {
	.dwivew = {
		.name = "fsw-pq_mdio",
		.of_match_tabwe = fsw_pq_mdio_match,
	},
	.pwobe = fsw_pq_mdio_pwobe,
	.wemove_new = fsw_pq_mdio_wemove,
};

moduwe_pwatfowm_dwivew(fsw_pq_mdio_dwivew);

MODUWE_DESCWIPTION("Fweescawe PQ MDIO hewpews");
MODUWE_WICENSE("GPW");
