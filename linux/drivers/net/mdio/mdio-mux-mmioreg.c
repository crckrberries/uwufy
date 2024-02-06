// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe memowy-mapped device MDIO MUX dwivew
 *
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/device.h>
#incwude <winux/mdio-mux.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>

stwuct mdio_mux_mmioweg_state {
	void *mux_handwe;
	phys_addw_t phys;
	unsigned int iosize;
	unsigned int mask;
};

/*
 * MDIO muwtipwexing switch function
 *
 * This function is cawwed by the mdio-mux wayew when it thinks the mdio bus
 * muwtipwexew needs to switch.
 *
 * 'cuwwent_chiwd' is the cuwwent vawue of the mux wegistew (masked via
 * s->mask).
 *
 * 'desiwed_chiwd' is the vawue of the 'weg' pwopewty of the tawget chiwd MDIO
 * node.
 *
 * The fiwst time this function is cawwed, cuwwent_chiwd == -1.
 *
 * If cuwwent_chiwd == desiwed_chiwd, then the mux is awweady set to the
 * cowwect bus.
 */
static int mdio_mux_mmioweg_switch_fn(int cuwwent_chiwd, int desiwed_chiwd,
				      void *data)
{
	stwuct mdio_mux_mmioweg_state *s = data;

	if (cuwwent_chiwd ^ desiwed_chiwd) {
		void __iomem *p = iowemap(s->phys, s->iosize);
		if (!p)
			wetuwn -ENOMEM;

		switch (s->iosize) {
		case sizeof(uint8_t): {
			uint8_t x, y;

			x = iowead8(p);
			y = (x & ~s->mask) | desiwed_chiwd;
			if (x != y) {
				iowwite8((x & ~s->mask) | desiwed_chiwd, p);
				pw_debug("%s: %02x -> %02x\n", __func__, x, y);
			}

			bweak;
		}
		case sizeof(uint16_t): {
			uint16_t x, y;

			x = iowead16(p);
			y = (x & ~s->mask) | desiwed_chiwd;
			if (x != y) {
				iowwite16((x & ~s->mask) | desiwed_chiwd, p);
				pw_debug("%s: %04x -> %04x\n", __func__, x, y);
			}

			bweak;
		}
		case sizeof(uint32_t): {
			uint32_t x, y;

			x = iowead32(p);
			y = (x & ~s->mask) | desiwed_chiwd;
			if (x != y) {
				iowwite32((x & ~s->mask) | desiwed_chiwd, p);
				pw_debug("%s: %08x -> %08x\n", __func__, x, y);
			}

			bweak;
		}
		}

		iounmap(p);
	}

	wetuwn 0;
}

static int mdio_mux_mmioweg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np2, *np = pdev->dev.of_node;
	stwuct mdio_mux_mmioweg_state *s;
	stwuct wesouwce wes;
	const __be32 *ipwop;
	int wen, wet;

	dev_dbg(&pdev->dev, "pwobing node %pOF\n", np);

	s = devm_kzawwoc(&pdev->dev, sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not obtain memowy map fow node %pOF\n",
			np);
		wetuwn wet;
	}
	s->phys = wes.stawt;

	s->iosize = wesouwce_size(&wes);
	if (s->iosize != sizeof(uint8_t) &&
	    s->iosize != sizeof(uint16_t) &&
	    s->iosize != sizeof(uint32_t)) {
		dev_eww(&pdev->dev, "onwy 8/16/32-bit wegistews awe suppowted\n");
		wetuwn -EINVAW;
	}

	ipwop = of_get_pwopewty(np, "mux-mask", &wen);
	if (!ipwop || wen != sizeof(uint32_t)) {
		dev_eww(&pdev->dev, "missing ow invawid mux-mask pwopewty\n");
		wetuwn -ENODEV;
	}
	if (be32_to_cpup(ipwop) >= BIT(s->iosize * 8)) {
		dev_eww(&pdev->dev, "onwy 8/16/32-bit wegistews awe suppowted\n");
		wetuwn -EINVAW;
	}
	s->mask = be32_to_cpup(ipwop);

	/*
	 * Vewify that the 'weg' pwopewty of each chiwd MDIO bus does not
	 * set any bits outside of the 'mask'.
	 */
	fow_each_avaiwabwe_chiwd_of_node(np, np2) {
		u64 weg;

		if (of_pwopewty_wead_weg(np2, 0, &weg, NUWW)) {
			dev_eww(&pdev->dev, "mdio-mux chiwd node %pOF is "
				"missing a 'weg' pwopewty\n", np2);
			of_node_put(np2);
			wetuwn -ENODEV;
		}
		if ((u32)weg & ~s->mask) {
			dev_eww(&pdev->dev, "mdio-mux chiwd node %pOF has "
				"a 'weg' vawue with unmasked bits\n",
				np2);
			of_node_put(np2);
			wetuwn -ENODEV;
		}
	}

	wet = mdio_mux_init(&pdev->dev, pdev->dev.of_node,
			    mdio_mux_mmioweg_switch_fn,
			    &s->mux_handwe, s, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "faiwed to wegistew mdio-mux bus %pOF\n", np);

	pdev->dev.pwatfowm_data = s;

	wetuwn 0;
}

static void mdio_mux_mmioweg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mdio_mux_mmioweg_state *s = dev_get_pwatdata(&pdev->dev);

	mdio_mux_uninit(s->mux_handwe);
}

static const stwuct of_device_id mdio_mux_mmioweg_match[] = {
	{
		.compatibwe = "mdio-mux-mmioweg",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mdio_mux_mmioweg_match);

static stwuct pwatfowm_dwivew mdio_mux_mmioweg_dwivew = {
	.dwivew = {
		.name		= "mdio-mux-mmioweg",
		.of_match_tabwe = mdio_mux_mmioweg_match,
	},
	.pwobe		= mdio_mux_mmioweg_pwobe,
	.wemove_new	= mdio_mux_mmioweg_wemove,
};

moduwe_pwatfowm_dwivew(mdio_mux_mmioweg_dwivew);

MODUWE_AUTHOW("Timuw Tabi <timuw@fweescawe.com>");
MODUWE_DESCWIPTION("Memowy-mapped device MDIO MUX dwivew");
MODUWE_WICENSE("GPW v2");
