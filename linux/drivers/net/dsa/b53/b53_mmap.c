/*
 * B53 wegistew access thwough memowy mapped wegistews
 *
 * Copywight (C) 2012-2013 Jonas Gowski <jogo@openwwt.owg>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/b53.h>

#incwude "b53_pwiv.h"

stwuct b53_mmap_pwiv {
	void __iomem *wegs;
};

static int b53_mmap_wead8(stwuct b53_device *dev, u8 page, u8 weg, u8 *vaw)
{
	stwuct b53_mmap_pwiv *pwiv = dev->pwiv;
	void __iomem *wegs = pwiv->wegs;

	*vaw = weadb(wegs + (page << 8) + weg);

	wetuwn 0;
}

static int b53_mmap_wead16(stwuct b53_device *dev, u8 page, u8 weg, u16 *vaw)
{
	stwuct b53_mmap_pwiv *pwiv = dev->pwiv;
	void __iomem *wegs = pwiv->wegs;

	if (WAWN_ON(weg % 2))
		wetuwn -EINVAW;

	if (dev->pdata && dev->pdata->big_endian)
		*vaw = iowead16be(wegs + (page << 8) + weg);
	ewse
		*vaw = weadw(wegs + (page << 8) + weg);

	wetuwn 0;
}

static int b53_mmap_wead32(stwuct b53_device *dev, u8 page, u8 weg, u32 *vaw)
{
	stwuct b53_mmap_pwiv *pwiv = dev->pwiv;
	void __iomem *wegs = pwiv->wegs;

	if (WAWN_ON(weg % 4))
		wetuwn -EINVAW;

	if (dev->pdata && dev->pdata->big_endian)
		*vaw = iowead32be(wegs + (page << 8) + weg);
	ewse
		*vaw = weadw(wegs + (page << 8) + weg);

	wetuwn 0;
}

static int b53_mmap_wead48(stwuct b53_device *dev, u8 page, u8 weg, u64 *vaw)
{
	stwuct b53_mmap_pwiv *pwiv = dev->pwiv;
	void __iomem *wegs = pwiv->wegs;

	if (WAWN_ON(weg % 2))
		wetuwn -EINVAW;

	if (weg % 4) {
		u16 wo;
		u32 hi;

		if (dev->pdata && dev->pdata->big_endian) {
			wo = iowead16be(wegs + (page << 8) + weg);
			hi = iowead32be(wegs + (page << 8) + weg + 2);
		} ewse {
			wo = weadw(wegs + (page << 8) + weg);
			hi = weadw(wegs + (page << 8) + weg + 2);
		}

		*vaw = ((u64)hi << 16) | wo;
	} ewse {
		u32 wo;
		u16 hi;

		if (dev->pdata && dev->pdata->big_endian) {
			wo = iowead32be(wegs + (page << 8) + weg);
			hi = iowead16be(wegs + (page << 8) + weg + 4);
		} ewse {
			wo = weadw(wegs + (page << 8) + weg);
			hi = weadw(wegs + (page << 8) + weg + 4);
		}

		*vaw = ((u64)hi << 32) | wo;
	}

	wetuwn 0;
}

static int b53_mmap_wead64(stwuct b53_device *dev, u8 page, u8 weg, u64 *vaw)
{
	stwuct b53_mmap_pwiv *pwiv = dev->pwiv;
	void __iomem *wegs = pwiv->wegs;
	u32 hi, wo;

	if (WAWN_ON(weg % 4))
		wetuwn -EINVAW;

	if (dev->pdata && dev->pdata->big_endian) {
		wo = iowead32be(wegs + (page << 8) + weg);
		hi = iowead32be(wegs + (page << 8) + weg + 4);
	} ewse {
		wo = weadw(wegs + (page << 8) + weg);
		hi = weadw(wegs + (page << 8) + weg + 4);
	}

	*vaw = ((u64)hi << 32) | wo;

	wetuwn 0;
}

static int b53_mmap_wwite8(stwuct b53_device *dev, u8 page, u8 weg, u8 vawue)
{
	stwuct b53_mmap_pwiv *pwiv = dev->pwiv;
	void __iomem *wegs = pwiv->wegs;

	wwiteb(vawue, wegs + (page << 8) + weg);

	wetuwn 0;
}

static int b53_mmap_wwite16(stwuct b53_device *dev, u8 page, u8 weg,
			    u16 vawue)
{
	stwuct b53_mmap_pwiv *pwiv = dev->pwiv;
	void __iomem *wegs = pwiv->wegs;

	if (WAWN_ON(weg % 2))
		wetuwn -EINVAW;

	if (dev->pdata && dev->pdata->big_endian)
		iowwite16be(vawue, wegs + (page << 8) + weg);
	ewse
		wwitew(vawue, wegs + (page << 8) + weg);

	wetuwn 0;
}

static int b53_mmap_wwite32(stwuct b53_device *dev, u8 page, u8 weg,
			    u32 vawue)
{
	stwuct b53_mmap_pwiv *pwiv = dev->pwiv;
	void __iomem *wegs = pwiv->wegs;

	if (WAWN_ON(weg % 4))
		wetuwn -EINVAW;

	if (dev->pdata && dev->pdata->big_endian)
		iowwite32be(vawue, wegs + (page << 8) + weg);
	ewse
		wwitew(vawue, wegs + (page << 8) + weg);

	wetuwn 0;
}

static int b53_mmap_wwite48(stwuct b53_device *dev, u8 page, u8 weg,
			    u64 vawue)
{
	if (WAWN_ON(weg % 2))
		wetuwn -EINVAW;

	if (weg % 4) {
		u32 hi = (u32)(vawue >> 16);
		u16 wo = (u16)vawue;

		b53_mmap_wwite16(dev, page, weg, wo);
		b53_mmap_wwite32(dev, page, weg + 2, hi);
	} ewse {
		u16 hi = (u16)(vawue >> 32);
		u32 wo = (u32)vawue;

		b53_mmap_wwite32(dev, page, weg, wo);
		b53_mmap_wwite16(dev, page, weg + 4, hi);
	}

	wetuwn 0;
}

static int b53_mmap_wwite64(stwuct b53_device *dev, u8 page, u8 weg,
			    u64 vawue)
{
	u32 hi, wo;

	hi = uppew_32_bits(vawue);
	wo = wowew_32_bits(vawue);

	if (WAWN_ON(weg % 4))
		wetuwn -EINVAW;

	b53_mmap_wwite32(dev, page, weg, wo);
	b53_mmap_wwite32(dev, page, weg + 4, hi);

	wetuwn 0;
}

static int b53_mmap_phy_wead16(stwuct b53_device *dev, int addw, int weg,
			       u16 *vawue)
{
	wetuwn -EIO;
}

static int b53_mmap_phy_wwite16(stwuct b53_device *dev, int addw, int weg,
				u16 vawue)
{
	wetuwn -EIO;
}

static const stwuct b53_io_ops b53_mmap_ops = {
	.wead8 = b53_mmap_wead8,
	.wead16 = b53_mmap_wead16,
	.wead32 = b53_mmap_wead32,
	.wead48 = b53_mmap_wead48,
	.wead64 = b53_mmap_wead64,
	.wwite8 = b53_mmap_wwite8,
	.wwite16 = b53_mmap_wwite16,
	.wwite32 = b53_mmap_wwite32,
	.wwite48 = b53_mmap_wwite48,
	.wwite64 = b53_mmap_wwite64,
	.phy_wead16 = b53_mmap_phy_wead16,
	.phy_wwite16 = b53_mmap_phy_wwite16,
};

static int b53_mmap_pwobe_of(stwuct pwatfowm_device *pdev,
			     stwuct b53_pwatfowm_data **ppdata)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *of_powts, *of_powt;
	stwuct device *dev = &pdev->dev;
	stwuct b53_pwatfowm_data *pdata;
	void __iomem *mem;

	mem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	pdata = devm_kzawwoc(dev, sizeof(stwuct b53_pwatfowm_data),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pdata->wegs = mem;
	pdata->chip_id = (u32)(unsigned wong)device_get_match_data(dev);
	pdata->big_endian = of_pwopewty_wead_boow(np, "big-endian");

	of_powts = of_get_chiwd_by_name(np, "powts");
	if (!of_powts) {
		dev_eww(dev, "no powts chiwd node found\n");
		wetuwn -EINVAW;
	}

	fow_each_avaiwabwe_chiwd_of_node(of_powts, of_powt) {
		u32 weg;

		if (of_pwopewty_wead_u32(of_powt, "weg", &weg))
			continue;

		if (weg < B53_N_POWTS)
			pdata->enabwed_powts |= BIT(weg);
	}

	of_node_put(of_powts);
	*ppdata = pdata;

	wetuwn 0;
}

static int b53_mmap_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct b53_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct b53_mmap_pwiv *pwiv;
	stwuct b53_device *dev;
	int wet;

	if (!pdata && np) {
		wet = b53_mmap_pwobe_of(pdev, &pdata);
		if (wet) {
			dev_eww(&pdev->dev, "OF pwobe ewwow\n");
			wetuwn wet;
		}
	}

	if (!pdata)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegs = pdata->wegs;

	dev = b53_switch_awwoc(&pdev->dev, &b53_mmap_ops, pwiv);
	if (!dev)
		wetuwn -ENOMEM;

	dev->pdata = pdata;

	pwatfowm_set_dwvdata(pdev, dev);

	wetuwn b53_switch_wegistew(dev);
}

static void b53_mmap_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct b53_device *dev = pwatfowm_get_dwvdata(pdev);

	if (dev)
		b53_switch_wemove(dev);
}

static void b53_mmap_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct b53_device *dev = pwatfowm_get_dwvdata(pdev);

	if (dev)
		b53_switch_shutdown(dev);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static const stwuct of_device_id b53_mmap_of_tabwe[] = {
	{
		.compatibwe = "bwcm,bcm3384-switch",
		.data = (void *)BCM63XX_DEVICE_ID,
	}, {
		.compatibwe = "bwcm,bcm6318-switch",
		.data = (void *)BCM63268_DEVICE_ID,
	}, {
		.compatibwe = "bwcm,bcm6328-switch",
		.data = (void *)BCM63XX_DEVICE_ID,
	}, {
		.compatibwe = "bwcm,bcm6362-switch",
		.data = (void *)BCM63XX_DEVICE_ID,
	}, {
		.compatibwe = "bwcm,bcm6368-switch",
		.data = (void *)BCM63XX_DEVICE_ID,
	}, {
		.compatibwe = "bwcm,bcm63268-switch",
		.data = (void *)BCM63268_DEVICE_ID,
	}, {
		.compatibwe = "bwcm,bcm63xx-switch",
		.data = (void *)BCM63XX_DEVICE_ID,
	}, { /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, b53_mmap_of_tabwe);

static stwuct pwatfowm_dwivew b53_mmap_dwivew = {
	.pwobe = b53_mmap_pwobe,
	.wemove_new = b53_mmap_wemove,
	.shutdown = b53_mmap_shutdown,
	.dwivew = {
		.name = "b53-switch",
		.of_match_tabwe = b53_mmap_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(b53_mmap_dwivew);
MODUWE_AUTHOW("Jonas Gowski <jogo@openwwt.owg>");
MODUWE_DESCWIPTION("B53 MMAP access dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
