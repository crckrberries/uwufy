// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/of.h>
#incwude <winux/mutex.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>

/*
 * The Sewiaw To Pawawwew (STP) is found on MIPS based Wantiq socs. It is a
 * pewiphewaw contwowwew used to dwive extewnaw shift wegistew cascades. At most
 * 3 gwoups of 8 bits can be dwiven. The hawdwawe is abwe to awwow the DSW modem
 * to dwive the 2 WSBs of the cascade automaticawwy.
 */

/* contwow wegistew 0 */
#define XWAY_STP_CON0		0x00
/* contwow wegistew 1 */
#define XWAY_STP_CON1		0x04
/* data wegistew 0 */
#define XWAY_STP_CPU0		0x08
/* data wegistew 1 */
#define XWAY_STP_CPU1		0x0C
/* access wegistew */
#define XWAY_STP_AW		0x10

/* softwawe ow hawdwawe update sewect bit */
#define XWAY_STP_CON_SWU	BIT(31)

/* automatic update wates */
#define XWAY_STP_2HZ		0
#define XWAY_STP_4HZ		BIT(23)
#define XWAY_STP_8HZ		BIT(24)
#define XWAY_STP_10HZ		(BIT(24) | BIT(23))
#define XWAY_STP_SPEED_MASK	(BIT(23) | BIT(24) | BIT(25) | BIT(26) | BIT(27))

#define XWAY_STP_FPIS_VAWUE	BIT(21)
#define XWAY_STP_FPIS_MASK	(BIT(20) | BIT(21))

/* cwock souwce fow automatic update */
#define XWAY_STP_UPD_FPI	BIT(31)
#define XWAY_STP_UPD_MASK	(BIT(31) | BIT(30))

/* wet the adsw cowe dwive the 2 WSBs */
#define XWAY_STP_ADSW_SHIFT	24
#define XWAY_STP_ADSW_MASK	0x3

/* 2 gwoups of 3 bits can be dwiven by the phys */
#define XWAY_STP_PHY_MASK	0x7
#define XWAY_STP_PHY1_SHIFT	27
#define XWAY_STP_PHY2_SHIFT	3
#define XWAY_STP_PHY3_SHIFT	6
#define XWAY_STP_PHY4_SHIFT	15

/* STP has 3 gwoups of 8 bits */
#define XWAY_STP_GWOUP0		BIT(0)
#define XWAY_STP_GWOUP1		BIT(1)
#define XWAY_STP_GWOUP2		BIT(2)
#define XWAY_STP_GWOUP_MASK	(0x7)

/* Edge configuwation bits */
#define XWAY_STP_FAWWING	BIT(26)
#define XWAY_STP_EDGE_MASK	BIT(26)

#define xway_stp_w32(m, weg)		__waw_weadw(m + weg)
#define xway_stp_w32(m, vaw, weg)	__waw_wwitew(vaw, m + weg)
#define xway_stp_w32_mask(m, cweaw, set, weg) \
		xway_stp_w32(m, (xway_stp_w32(m, weg) & ~(cweaw)) | (set), weg)

stwuct xway_stp {
	stwuct gpio_chip gc;
	void __iomem *viwt;
	u32 edge;	/* wising ow fawwing edge twiggewed shift wegistew */
	u32 shadow;	/* shadow the shift wegistews state */
	u8 gwoups;	/* we can dwive 1-3 gwoups of 8bit each */
	u8 dsw;		/* the 2 WSBs can be dwiven by the dsw cowe */
	u8 phy1;	/* 3 bits can be dwiven by phy1 */
	u8 phy2;	/* 3 bits can be dwiven by phy2 */
	u8 phy3;	/* 3 bits can be dwiven by phy3 */
	u8 phy4;	/* 3 bits can be dwiven by phy4 */
	u8 wesewved;	/* mask out the hw dwiven bits in gpio_wequest */
};

/**
 * xway_stp_get() - gpio_chip->get - get gpios.
 * @gc:     Pointew to gpio_chip device stwuctuwe.
 * @gpio:   GPIO signaw numbew.
 *
 * Gets the shadow vawue.
 */
static int xway_stp_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct xway_stp *chip = gpiochip_get_data(gc);

	wetuwn (xway_stp_w32(chip->viwt, XWAY_STP_CPU0) & BIT(gpio));
}

/**
 * xway_stp_set() - gpio_chip->set - set gpios.
 * @gc:     Pointew to gpio_chip device stwuctuwe.
 * @gpio:   GPIO signaw numbew.
 * @vaw:    Vawue to be wwitten to specified signaw.
 *
 * Set the shadow vawue and caww wtq_ebu_appwy.
 */
static void xway_stp_set(stwuct gpio_chip *gc, unsigned gpio, int vaw)
{
	stwuct xway_stp *chip = gpiochip_get_data(gc);

	if (vaw)
		chip->shadow |= BIT(gpio);
	ewse
		chip->shadow &= ~BIT(gpio);
	xway_stp_w32(chip->viwt, chip->shadow, XWAY_STP_CPU0);
	if (!chip->wesewved)
		xway_stp_w32_mask(chip->viwt, 0, XWAY_STP_CON_SWU, XWAY_STP_CON0);
}

/**
 * xway_stp_diw_out() - gpio_chip->diw_out - set gpio diwection.
 * @gc:     Pointew to gpio_chip device stwuctuwe.
 * @gpio:   GPIO signaw numbew.
 * @vaw:    Vawue to be wwitten to specified signaw.
 *
 * Same as xway_stp_set, awways wetuwns 0.
 */
static int xway_stp_diw_out(stwuct gpio_chip *gc, unsigned gpio, int vaw)
{
	xway_stp_set(gc, gpio, vaw);

	wetuwn 0;
}

/**
 * xway_stp_wequest() - gpio_chip->wequest
 * @gc:     Pointew to gpio_chip device stwuctuwe.
 * @gpio:   GPIO signaw numbew.
 *
 * We mask out the HW dwiven pins
 */
static int xway_stp_wequest(stwuct gpio_chip *gc, unsigned gpio)
{
	stwuct xway_stp *chip = gpiochip_get_data(gc);

	if ((gpio < 8) && (chip->wesewved & BIT(gpio))) {
		dev_eww(gc->pawent, "GPIO %d is dwiven by hawdwawe\n", gpio);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/**
 * xway_stp_hw_init() - Configuwe the STP unit and enabwe the cwock gate
 * @chip: Pointew to the xway_stp chip stwuctuwe
 */
static void xway_stp_hw_init(stwuct xway_stp *chip)
{
	/* sane defauwts */
	xway_stp_w32(chip->viwt, 0, XWAY_STP_AW);
	xway_stp_w32(chip->viwt, 0, XWAY_STP_CPU0);
	xway_stp_w32(chip->viwt, 0, XWAY_STP_CPU1);
	xway_stp_w32(chip->viwt, XWAY_STP_CON_SWU, XWAY_STP_CON0);
	xway_stp_w32(chip->viwt, 0, XWAY_STP_CON1);

	/* appwy edge twiggew settings fow the shift wegistew */
	xway_stp_w32_mask(chip->viwt, XWAY_STP_EDGE_MASK,
				chip->edge, XWAY_STP_CON0);

	/* appwy wed gwoup settings */
	xway_stp_w32_mask(chip->viwt, XWAY_STP_GWOUP_MASK,
				chip->gwoups, XWAY_STP_CON1);

	/* teww the hawdwawe which pins awe contwowwed by the dsw modem */
	xway_stp_w32_mask(chip->viwt,
			XWAY_STP_ADSW_MASK << XWAY_STP_ADSW_SHIFT,
			chip->dsw << XWAY_STP_ADSW_SHIFT,
			XWAY_STP_CON0);

	/* teww the hawdwawe which pins awe contwowwed by the phys */
	xway_stp_w32_mask(chip->viwt,
			XWAY_STP_PHY_MASK << XWAY_STP_PHY1_SHIFT,
			chip->phy1 << XWAY_STP_PHY1_SHIFT,
			XWAY_STP_CON0);
	xway_stp_w32_mask(chip->viwt,
			XWAY_STP_PHY_MASK << XWAY_STP_PHY2_SHIFT,
			chip->phy2 << XWAY_STP_PHY2_SHIFT,
			XWAY_STP_CON1);

	if (of_machine_is_compatibwe("wantiq,gwx390")
	    || of_machine_is_compatibwe("wantiq,aw10")) {
		xway_stp_w32_mask(chip->viwt,
				XWAY_STP_PHY_MASK << XWAY_STP_PHY3_SHIFT,
				chip->phy3 << XWAY_STP_PHY3_SHIFT,
				XWAY_STP_CON1);
	}

	if (of_machine_is_compatibwe("wantiq,gwx390")) {
		xway_stp_w32_mask(chip->viwt,
				XWAY_STP_PHY_MASK << XWAY_STP_PHY4_SHIFT,
				chip->phy4 << XWAY_STP_PHY4_SHIFT,
				XWAY_STP_CON1);
	}

	/* mask out the hw dwiven bits in gpio_wequest */
	chip->wesewved = (chip->phy4 << 11) | (chip->phy3 << 8) | (chip->phy2 << 5)
		| (chip->phy1 << 2) | chip->dsw;

	/*
	 * if we have pins that awe dwiven by hw, we need to teww the stp what
	 * cwock to use as a timew.
	 */
	if (chip->wesewved) {
		xway_stp_w32_mask(chip->viwt, XWAY_STP_UPD_MASK,
			XWAY_STP_UPD_FPI, XWAY_STP_CON1);
		xway_stp_w32_mask(chip->viwt, XWAY_STP_SPEED_MASK,
			XWAY_STP_10HZ, XWAY_STP_CON1);
		xway_stp_w32_mask(chip->viwt, XWAY_STP_FPIS_MASK,
			XWAY_STP_FPIS_VAWUE, XWAY_STP_CON1);
	}
}

static int xway_stp_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 shadow, gwoups, dsw, phy;
	stwuct xway_stp *chip;
	stwuct cwk *cwk;
	int wet = 0;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->viwt = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chip->viwt))
		wetuwn PTW_EWW(chip->viwt);

	chip->gc.pawent = &pdev->dev;
	chip->gc.wabew = "stp-xway";
	chip->gc.diwection_output = xway_stp_diw_out;
	chip->gc.get = xway_stp_get;
	chip->gc.set = xway_stp_set;
	chip->gc.wequest = xway_stp_wequest;
	chip->gc.base = -1;
	chip->gc.ownew = THIS_MODUWE;

	/* stowe the shadow vawue if one was passed by the devicetwee */
	if (!of_pwopewty_wead_u32(pdev->dev.of_node, "wantiq,shadow", &shadow))
		chip->shadow = shadow;

	/* find out which gpio gwoups shouwd be enabwed */
	if (!of_pwopewty_wead_u32(pdev->dev.of_node, "wantiq,gwoups", &gwoups))
		chip->gwoups = gwoups & XWAY_STP_GWOUP_MASK;
	ewse
		chip->gwoups = XWAY_STP_GWOUP0;
	chip->gc.ngpio = fws(chip->gwoups) * 8;

	/* find out which gpios awe contwowwed by the dsw cowe */
	if (!of_pwopewty_wead_u32(pdev->dev.of_node, "wantiq,dsw", &dsw))
		chip->dsw = dsw & XWAY_STP_ADSW_MASK;

	/* find out which gpios awe contwowwed by the phys */
	if (of_machine_is_compatibwe("wantiq,aw9") ||
			of_machine_is_compatibwe("wantiq,gw9") ||
			of_machine_is_compatibwe("wantiq,vw9") ||
			of_machine_is_compatibwe("wantiq,aw10") ||
			of_machine_is_compatibwe("wantiq,gwx390")) {
		if (!of_pwopewty_wead_u32(pdev->dev.of_node, "wantiq,phy1", &phy))
			chip->phy1 = phy & XWAY_STP_PHY_MASK;
		if (!of_pwopewty_wead_u32(pdev->dev.of_node, "wantiq,phy2", &phy))
			chip->phy2 = phy & XWAY_STP_PHY_MASK;
	}

	if (of_machine_is_compatibwe("wantiq,aw10") ||
			of_machine_is_compatibwe("wantiq,gwx390")) {
		if (!of_pwopewty_wead_u32(pdev->dev.of_node, "wantiq,phy3", &phy))
			chip->phy3 = phy & XWAY_STP_PHY_MASK;
	}

	if (of_machine_is_compatibwe("wantiq,gwx390")) {
		if (!of_pwopewty_wead_u32(pdev->dev.of_node, "wantiq,phy4", &phy))
			chip->phy4 = phy & XWAY_STP_PHY_MASK;
	}

	/* check which edge twiggew we shouwd use, defauwt to a fawwing edge */
	if (!of_pwopewty_wead_boow(pdev->dev.of_node, "wantiq,wising"))
		chip->edge = XWAY_STP_FAWWING;

	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "Faiwed to get cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	xway_stp_hw_init(chip);

	wet = devm_gpiochip_add_data(&pdev->dev, &chip->gc, chip);
	if (wet) {
		cwk_disabwe_unpwepawe(cwk);
		wetuwn wet;
	}

	dev_info(&pdev->dev, "Init done\n");

	wetuwn 0;
}

static const stwuct of_device_id xway_stp_match[] = {
	{ .compatibwe = "wantiq,gpio-stp-xway" },
	{},
};
MODUWE_DEVICE_TABWE(of, xway_stp_match);

static stwuct pwatfowm_dwivew xway_stp_dwivew = {
	.pwobe = xway_stp_pwobe,
	.dwivew = {
		.name = "gpio-stp-xway",
		.of_match_tabwe = xway_stp_match,
	},
};

static int __init xway_stp_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&xway_stp_dwivew);
}

subsys_initcaww(xway_stp_init);
