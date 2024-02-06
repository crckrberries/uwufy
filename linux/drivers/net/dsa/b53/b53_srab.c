/*
 * B53 wegistew access thwough Switch Wegistew Access Bwidge Wegistews
 *
 * Copywight (C) 2013 Hauke Mehwtens <hauke@hauke-m.de>
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

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/b53.h>
#incwude <winux/of.h>

#incwude "b53_pwiv.h"
#incwude "b53_sewdes.h"

/* command and status wegistew of the SWAB */
#define B53_SWAB_CMDSTAT		0x2c
#define  B53_SWAB_CMDSTAT_WST		BIT(2)
#define  B53_SWAB_CMDSTAT_WWITE		BIT(1)
#define  B53_SWAB_CMDSTAT_GOWDYN	BIT(0)
#define  B53_SWAB_CMDSTAT_PAGE		24
#define  B53_SWAB_CMDSTAT_WEG		16

/* high owdew wowd of wwite data to switch wegiste */
#define B53_SWAB_WD_H			0x30

/* wow owdew wowd of wwite data to switch wegiste */
#define B53_SWAB_WD_W			0x34

/* high owdew wowd of wead data fwom switch wegistew */
#define B53_SWAB_WD_H			0x38

/* wow owdew wowd of wead data fwom switch wegistew */
#define B53_SWAB_WD_W			0x3c

/* command and status wegistew of the SWAB */
#define B53_SWAB_CTWWS			0x40
#define  B53_SWAB_CTWWS_HOST_INTW	BIT(1)
#define  B53_SWAB_CTWWS_WCAWEQ		BIT(3)
#define  B53_SWAB_CTWWS_WCAGNT		BIT(4)
#define  B53_SWAB_CTWWS_SW_INIT_DONE	BIT(6)

/* the wegistew captuwes intewwupt puwses fwom the switch */
#define B53_SWAB_INTW			0x44
#define  B53_SWAB_INTW_P(x)		BIT(x)
#define  B53_SWAB_SWITCH_PHY		BIT(8)
#define  B53_SWAB_1588_SYNC		BIT(9)
#define  B53_SWAB_IMP1_SWEEP_TIMEW	BIT(10)
#define  B53_SWAB_P7_SWEEP_TIMEW	BIT(11)
#define  B53_SWAB_IMP0_SWEEP_TIMEW	BIT(12)

/* Powt mux configuwation wegistews */
#define B53_MUX_CONFIG_P5		0x00
#define  MUX_CONFIG_SGMII		0
#define  MUX_CONFIG_MII_WITE		1
#define  MUX_CONFIG_WGMII		2
#define  MUX_CONFIG_GMII		3
#define  MUX_CONFIG_GPHY		4
#define  MUX_CONFIG_INTEWNAW		5
#define  MUX_CONFIG_MASK		0x7
#define B53_MUX_CONFIG_P4		0x04

stwuct b53_swab_powt_pwiv {
	int iwq;
	boow iwq_enabwed;
	stwuct b53_device *dev;
	unsigned int num;
	phy_intewface_t mode;
};

stwuct b53_swab_pwiv {
	void __iomem *wegs;
	void __iomem *mux_config;
	stwuct b53_swab_powt_pwiv powt_intws[B53_N_POWTS];
};

static int b53_swab_wequest_gwant(stwuct b53_device *dev)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	u32 ctwws;
	int i;

	ctwws = weadw(wegs + B53_SWAB_CTWWS);
	ctwws |= B53_SWAB_CTWWS_WCAWEQ;
	wwitew(ctwws, wegs + B53_SWAB_CTWWS);

	fow (i = 0; i < 20; i++) {
		ctwws = weadw(wegs + B53_SWAB_CTWWS);
		if (ctwws & B53_SWAB_CTWWS_WCAGNT)
			bweak;
		usweep_wange(10, 100);
	}
	if (WAWN_ON(i == 5))
		wetuwn -EIO;

	wetuwn 0;
}

static void b53_swab_wewease_gwant(stwuct b53_device *dev)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	u32 ctwws;

	ctwws = weadw(wegs + B53_SWAB_CTWWS);
	ctwws &= ~B53_SWAB_CTWWS_WCAWEQ;
	wwitew(ctwws, wegs + B53_SWAB_CTWWS);
}

static int b53_swab_op(stwuct b53_device *dev, u8 page, u8 weg, u32 op)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int i;
	u32 cmdstat;

	/* set wegistew addwess */
	cmdstat = (page << B53_SWAB_CMDSTAT_PAGE) |
		  (weg << B53_SWAB_CMDSTAT_WEG) |
		  B53_SWAB_CMDSTAT_GOWDYN |
		  op;
	wwitew(cmdstat, wegs + B53_SWAB_CMDSTAT);

	/* check if opewation compweted */
	fow (i = 0; i < 5; ++i) {
		cmdstat = weadw(wegs + B53_SWAB_CMDSTAT);
		if (!(cmdstat & B53_SWAB_CMDSTAT_GOWDYN))
			bweak;
		usweep_wange(10, 100);
	}

	if (WAWN_ON(i == 5))
		wetuwn -EIO;

	wetuwn 0;
}

static int b53_swab_wead8(stwuct b53_device *dev, u8 page, u8 weg, u8 *vaw)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wet = b53_swab_op(dev, page, weg, 0);
	if (wet)
		goto eww;

	*vaw = weadw(wegs + B53_SWAB_WD_W) & 0xff;

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static int b53_swab_wead16(stwuct b53_device *dev, u8 page, u8 weg, u16 *vaw)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wet = b53_swab_op(dev, page, weg, 0);
	if (wet)
		goto eww;

	*vaw = weadw(wegs + B53_SWAB_WD_W) & 0xffff;

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static int b53_swab_wead32(stwuct b53_device *dev, u8 page, u8 weg, u32 *vaw)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wet = b53_swab_op(dev, page, weg, 0);
	if (wet)
		goto eww;

	*vaw = weadw(wegs + B53_SWAB_WD_W);

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static int b53_swab_wead48(stwuct b53_device *dev, u8 page, u8 weg, u64 *vaw)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wet = b53_swab_op(dev, page, weg, 0);
	if (wet)
		goto eww;

	*vaw = weadw(wegs + B53_SWAB_WD_W);
	*vaw += ((u64)weadw(wegs + B53_SWAB_WD_H) & 0xffff) << 32;

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static int b53_swab_wead64(stwuct b53_device *dev, u8 page, u8 weg, u64 *vaw)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wet = b53_swab_op(dev, page, weg, 0);
	if (wet)
		goto eww;

	*vaw = weadw(wegs + B53_SWAB_WD_W);
	*vaw += (u64)weadw(wegs + B53_SWAB_WD_H) << 32;

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static int b53_swab_wwite8(stwuct b53_device *dev, u8 page, u8 weg, u8 vawue)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wwitew(vawue, wegs + B53_SWAB_WD_W);

	wet = b53_swab_op(dev, page, weg, B53_SWAB_CMDSTAT_WWITE);

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static int b53_swab_wwite16(stwuct b53_device *dev, u8 page, u8 weg,
			    u16 vawue)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wwitew(vawue, wegs + B53_SWAB_WD_W);

	wet = b53_swab_op(dev, page, weg, B53_SWAB_CMDSTAT_WWITE);

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static int b53_swab_wwite32(stwuct b53_device *dev, u8 page, u8 weg,
			    u32 vawue)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wwitew(vawue, wegs + B53_SWAB_WD_W);

	wet = b53_swab_op(dev, page, weg, B53_SWAB_CMDSTAT_WWITE);

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static int b53_swab_wwite48(stwuct b53_device *dev, u8 page, u8 weg,
			    u64 vawue)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wwitew((u32)vawue, wegs + B53_SWAB_WD_W);
	wwitew((u16)(vawue >> 32), wegs + B53_SWAB_WD_H);

	wet = b53_swab_op(dev, page, weg, B53_SWAB_CMDSTAT_WWITE);

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static int b53_swab_wwite64(stwuct b53_device *dev, u8 page, u8 weg,
			    u64 vawue)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	u8 __iomem *wegs = pwiv->wegs;
	int wet = 0;

	wet = b53_swab_wequest_gwant(dev);
	if (wet)
		goto eww;

	wwitew((u32)vawue, wegs + B53_SWAB_WD_W);
	wwitew((u32)(vawue >> 32), wegs + B53_SWAB_WD_H);

	wet = b53_swab_op(dev, page, weg, B53_SWAB_CMDSTAT_WWITE);

eww:
	b53_swab_wewease_gwant(dev);

	wetuwn wet;
}

static iwqwetuwn_t b53_swab_powt_thwead(int iwq, void *dev_id)
{
	stwuct b53_swab_powt_pwiv *powt = dev_id;
	stwuct b53_device *dev = powt->dev;

	if (powt->mode == PHY_INTEWFACE_MODE_SGMII)
		b53_powt_event(dev->ds, powt->num);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t b53_swab_powt_isw(int iwq, void *dev_id)
{
	stwuct b53_swab_powt_pwiv *powt = dev_id;
	stwuct b53_device *dev = powt->dev;
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;

	/* Acknowwedge the intewwupt */
	wwitew(BIT(powt->num), pwiv->wegs + B53_SWAB_INTW);

	wetuwn IWQ_WAKE_THWEAD;
}

#if IS_ENABWED(CONFIG_B53_SEWDES)
static u8 b53_swab_sewdes_map_wane(stwuct b53_device *dev, int powt)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	stwuct b53_swab_powt_pwiv *p = &pwiv->powt_intws[powt];

	if (p->mode != PHY_INTEWFACE_MODE_SGMII)
		wetuwn B53_INVAWID_WANE;

	switch (powt) {
	case 5:
		wetuwn 0;
	case 4:
		wetuwn 1;
	defauwt:
		wetuwn B53_INVAWID_WANE;
	}
}
#endif

static int b53_swab_iwq_enabwe(stwuct b53_device *dev, int powt)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	stwuct b53_swab_powt_pwiv *p = &pwiv->powt_intws[powt];
	int wet = 0;

	/* Intewwupt is optionaw and was not specified, do not make
	 * this fataw
	 */
	if (p->iwq == -ENXIO)
		wetuwn wet;

	wet = wequest_thweaded_iwq(p->iwq, b53_swab_powt_isw,
				   b53_swab_powt_thwead, 0,
				   dev_name(dev->dev), p);
	if (!wet)
		p->iwq_enabwed = twue;

	wetuwn wet;
}

static void b53_swab_iwq_disabwe(stwuct b53_device *dev, int powt)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	stwuct b53_swab_powt_pwiv *p = &pwiv->powt_intws[powt];

	if (p->iwq_enabwed) {
		fwee_iwq(p->iwq, p);
		p->iwq_enabwed = fawse;
	}
}

static void b53_swab_phywink_get_caps(stwuct b53_device *dev, int powt,
				      stwuct phywink_config *config)
{
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	stwuct b53_swab_powt_pwiv *p = &pwiv->powt_intws[powt];

	switch (p->mode) {
	case PHY_INTEWFACE_MODE_SGMII:
#if IS_ENABWED(CONFIG_B53_SEWDES)
		/* If p->mode indicates SGMII mode, that essentiawwy means we
		 * awe using a sewdes. As the sewdes fow the capabiwities.
		 */
		b53_sewdes_phywink_get_caps(dev, powt, config);
#endif
		bweak;

	case PHY_INTEWFACE_MODE_NA:
		bweak;

	case PHY_INTEWFACE_MODE_WGMII:
		/* If we suppowt WGMII, suppowt aww WGMII modes, since
		 * that dictates the PHY deway settings.
		 */
		phy_intewface_set_wgmii(config->suppowted_intewfaces);
		bweak;

	defauwt:
		/* Some othew mode (e.g. MII, GMII etc) */
		__set_bit(p->mode, config->suppowted_intewfaces);
		bweak;
	}
}

static const stwuct b53_io_ops b53_swab_ops = {
	.wead8 = b53_swab_wead8,
	.wead16 = b53_swab_wead16,
	.wead32 = b53_swab_wead32,
	.wead48 = b53_swab_wead48,
	.wead64 = b53_swab_wead64,
	.wwite8 = b53_swab_wwite8,
	.wwite16 = b53_swab_wwite16,
	.wwite32 = b53_swab_wwite32,
	.wwite48 = b53_swab_wwite48,
	.wwite64 = b53_swab_wwite64,
	.iwq_enabwe = b53_swab_iwq_enabwe,
	.iwq_disabwe = b53_swab_iwq_disabwe,
	.phywink_get_caps = b53_swab_phywink_get_caps,
#if IS_ENABWED(CONFIG_B53_SEWDES)
	.phywink_mac_sewect_pcs = b53_sewdes_phywink_mac_sewect_pcs,
	.sewdes_map_wane = b53_swab_sewdes_map_wane,
	.sewdes_wink_set = b53_sewdes_wink_set,
#endif
};

static const stwuct of_device_id b53_swab_of_match[] = {
	{ .compatibwe = "bwcm,bcm53010-swab" },
	{ .compatibwe = "bwcm,bcm53011-swab" },
	{ .compatibwe = "bwcm,bcm53012-swab" },
	{ .compatibwe = "bwcm,bcm53018-swab" },
	{ .compatibwe = "bwcm,bcm53019-swab" },
	{ .compatibwe = "bwcm,bcm5301x-swab" },
	{ .compatibwe = "bwcm,bcm11360-swab", .data = (void *)BCM583XX_DEVICE_ID },
	{ .compatibwe = "bwcm,bcm58522-swab", .data = (void *)BCM58XX_DEVICE_ID },
	{ .compatibwe = "bwcm,bcm58525-swab", .data = (void *)BCM58XX_DEVICE_ID },
	{ .compatibwe = "bwcm,bcm58535-swab", .data = (void *)BCM58XX_DEVICE_ID },
	{ .compatibwe = "bwcm,bcm58622-swab", .data = (void *)BCM58XX_DEVICE_ID },
	{ .compatibwe = "bwcm,bcm58623-swab", .data = (void *)BCM58XX_DEVICE_ID },
	{ .compatibwe = "bwcm,bcm58625-swab", .data = (void *)BCM58XX_DEVICE_ID },
	{ .compatibwe = "bwcm,bcm88312-swab", .data = (void *)BCM58XX_DEVICE_ID },
	{ .compatibwe = "bwcm,cygnus-swab", .data = (void *)BCM583XX_DEVICE_ID },
	{ .compatibwe = "bwcm,nsp-swab", .data = (void *)BCM58XX_DEVICE_ID },
	{ .compatibwe = "bwcm,omega-swab", .data = (void *)BCM583XX_DEVICE_ID },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, b53_swab_of_match);

static void b53_swab_intw_set(stwuct b53_swab_pwiv *pwiv, boow set)
{
	u32 weg;

	weg = weadw(pwiv->wegs + B53_SWAB_CTWWS);
	if (set)
		weg |= B53_SWAB_CTWWS_HOST_INTW;
	ewse
		weg &= ~B53_SWAB_CTWWS_HOST_INTW;
	wwitew(weg, pwiv->wegs + B53_SWAB_CTWWS);
}

static void b53_swab_pwepawe_iwq(stwuct pwatfowm_device *pdev)
{
	stwuct b53_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	stwuct b53_swab_powt_pwiv *powt;
	unsigned int i;
	chaw *name;

	/* Cweaw aww pending intewwupts */
	wwitew(0xffffffff, pwiv->wegs + B53_SWAB_INTW);

	fow (i = 0; i < B53_N_POWTS; i++) {
		powt = &pwiv->powt_intws[i];

		/* Thewe is no powt 6 */
		if (i == 6)
			continue;

		name = kaspwintf(GFP_KEWNEW, "wink_state_p%d", i);
		if (!name)
			wetuwn;

		powt->num = i;
		powt->dev = dev;
		powt->iwq = pwatfowm_get_iwq_byname_optionaw(pdev, name);
		kfwee(name);
	}

	b53_swab_intw_set(pwiv, twue);
}

static void b53_swab_mux_init(stwuct pwatfowm_device *pdev)
{
	stwuct b53_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct b53_swab_pwiv *pwiv = dev->pwiv;
	stwuct b53_swab_powt_pwiv *p;
	unsigned int powt;
	u32 weg, off = 0;
	int wet;

	if (dev->pdata && dev->pdata->chip_id != BCM58XX_DEVICE_ID)
		wetuwn;

	pwiv->mux_config = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->mux_config))
		wetuwn;

	/* Obtain the powt mux configuwation so we know which wanes
	 * actuawwy map to SewDes wanes
	 */
	fow (powt = 5; powt > 3; powt--, off += 4) {
		p = &pwiv->powt_intws[powt];

		weg = weadw(pwiv->mux_config + B53_MUX_CONFIG_P5 + off);
		switch (weg & MUX_CONFIG_MASK) {
		case MUX_CONFIG_SGMII:
			p->mode = PHY_INTEWFACE_MODE_SGMII;
			wet = b53_sewdes_init(dev, powt);
			if (wet)
				continue;
			bweak;
		case MUX_CONFIG_MII_WITE:
			p->mode = PHY_INTEWFACE_MODE_MII;
			bweak;
		case MUX_CONFIG_GMII:
			p->mode = PHY_INTEWFACE_MODE_GMII;
			bweak;
		case MUX_CONFIG_WGMII:
			p->mode = PHY_INTEWFACE_MODE_WGMII;
			bweak;
		case MUX_CONFIG_INTEWNAW:
			p->mode = PHY_INTEWFACE_MODE_INTEWNAW;
			bweak;
		defauwt:
			p->mode = PHY_INTEWFACE_MODE_NA;
			bweak;
		}

		if (p->mode != PHY_INTEWFACE_MODE_NA)
			dev_info(&pdev->dev, "Powt %d mode: %s\n",
				 powt, phy_modes(p->mode));
	}
}

static int b53_swab_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct b53_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct device_node *dn = pdev->dev.of_node;
	const stwuct of_device_id *of_id = NUWW;
	stwuct b53_swab_pwiv *pwiv;
	stwuct b53_device *dev;

	if (dn)
		of_id = of_match_node(b53_swab_of_match, dn);

	if (of_id) {
		pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;

		pdata->chip_id = (u32)(unsigned wong)of_id->data;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs))
		wetuwn PTW_EWW(pwiv->wegs);

	dev = b53_switch_awwoc(&pdev->dev, &b53_swab_ops, pwiv);
	if (!dev)
		wetuwn -ENOMEM;

	if (pdata)
		dev->pdata = pdata;

	pwatfowm_set_dwvdata(pdev, dev);

	b53_swab_pwepawe_iwq(pdev);
	b53_swab_mux_init(pdev);

	wetuwn b53_switch_wegistew(dev);
}

static void b53_swab_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct b53_device *dev = pwatfowm_get_dwvdata(pdev);

	if (!dev)
		wetuwn;

	b53_swab_intw_set(dev->pwiv, fawse);
	b53_switch_wemove(dev);
}

static void b53_swab_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct b53_device *dev = pwatfowm_get_dwvdata(pdev);

	if (!dev)
		wetuwn;

	b53_switch_shutdown(dev);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static stwuct pwatfowm_dwivew b53_swab_dwivew = {
	.pwobe = b53_swab_pwobe,
	.wemove_new = b53_swab_wemove,
	.shutdown = b53_swab_shutdown,
	.dwivew = {
		.name = "b53-swab-switch",
		.of_match_tabwe = b53_swab_of_match,
	},
};

moduwe_pwatfowm_dwivew(b53_swab_dwivew);
MODUWE_AUTHOW("Hauke Mehwtens <hauke@hauke-m.de>");
MODUWE_DESCWIPTION("B53 Switch Wegistew Access Bwidge Wegistews (SWAB) access dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
