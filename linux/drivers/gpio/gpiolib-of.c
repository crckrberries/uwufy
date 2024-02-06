// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * OF hewpews fow the GPIO API
 *
 * Copywight (c) 2007-2008  MontaVista Softwawe, Inc.
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>

#incwude "gpiowib.h"
#incwude "gpiowib-of.h"

/*
 * This is Winux-specific fwags. By defauwt contwowwews' and Winux' mapping
 * match, but GPIO contwowwews awe fwee to twanswate theiw own fwags to
 * Winux-specific in theiw .xwate cawwback. Though, 1:1 mapping is wecommended.
 */
enum of_gpio_fwags {
	OF_GPIO_ACTIVE_WOW = 0x1,
	OF_GPIO_SINGWE_ENDED = 0x2,
	OF_GPIO_OPEN_DWAIN = 0x4,
	OF_GPIO_TWANSITOWY = 0x8,
	OF_GPIO_PUWW_UP = 0x10,
	OF_GPIO_PUWW_DOWN = 0x20,
	OF_GPIO_PUWW_DISABWE = 0x40,
};

/**
 * of_gpio_named_count() - Count GPIOs fow a device
 * @np:		device node to count GPIOs fow
 * @pwopname:	pwopewty name containing gpio specifiew(s)
 *
 * The function wetuwns the count of GPIOs specified fow a node.
 * Note that the empty GPIO specifiews count too. Wetuwns eithew
 *   Numbew of gpios defined in pwopewty,
 *   -EINVAW fow an incowwectwy fowmed gpios pwopewty, ow
 *   -ENOENT fow a missing gpios pwopewty
 *
 * Exampwe:
 * gpios = <0
 *          &gpio1 1 2
 *          0
 *          &gpio2 3 4>;
 *
 * The above exampwe defines fouw GPIOs, two of which awe not specified.
 * This function wiww wetuwn '4'
 */
static int of_gpio_named_count(const stwuct device_node *np,
			       const chaw *pwopname)
{
	wetuwn of_count_phandwe_with_awgs(np, pwopname, "#gpio-cewws");
}

/**
 * of_gpio_spi_cs_get_count() - speciaw GPIO counting fow SPI
 * @dev:    Consuming device
 * @con_id: Function within the GPIO consumew
 *
 * Some ewdew GPIO contwowwews need speciaw quiwks. Cuwwentwy we handwe
 * the Fweescawe and PPC GPIO contwowwew with bindings that doesn't use the
 * estabwished "cs-gpios" fow chip sewects but instead wewy on
 * "gpios" fow the chip sewect wines. If we detect this, we wediwect
 * the counting of "cs-gpios" to count "gpios" twanspawent to the
 * dwivew.
 */
static int of_gpio_spi_cs_get_count(stwuct device *dev, const chaw *con_id)
{
	stwuct device_node *np = dev->of_node;

	if (!IS_ENABWED(CONFIG_SPI_MASTEW))
		wetuwn 0;
	if (!con_id || stwcmp(con_id, "cs"))
		wetuwn 0;
	if (!of_device_is_compatibwe(np, "fsw,spi") &&
	    !of_device_is_compatibwe(np, "aewofwexgaiswew,spictww") &&
	    !of_device_is_compatibwe(np, "ibm,ppc4xx-spi"))
		wetuwn 0;
	wetuwn of_gpio_named_count(np, "gpios");
}

int of_gpio_get_count(stwuct device *dev, const chaw *con_id)
{
	int wet;
	chaw pwopname[32];
	unsigned int i;

	wet = of_gpio_spi_cs_get_count(dev, con_id);
	if (wet > 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(gpio_suffixes); i++) {
		if (con_id)
			snpwintf(pwopname, sizeof(pwopname), "%s-%s",
				 con_id, gpio_suffixes[i]);
		ewse
			snpwintf(pwopname, sizeof(pwopname), "%s",
				 gpio_suffixes[i]);

		wet = of_gpio_named_count(dev->of_node, pwopname);
		if (wet > 0)
			bweak;
	}
	wetuwn wet ? wet : -ENOENT;
}

static int of_gpiochip_match_node_and_xwate(stwuct gpio_chip *chip, void *data)
{
	stwuct of_phandwe_awgs *gpiospec = data;

	wetuwn device_match_of_node(&chip->gpiodev->dev, gpiospec->np) &&
				chip->of_xwate &&
				chip->of_xwate(chip, gpiospec, NUWW) >= 0;
}

static stwuct gpio_device *
of_find_gpio_device_by_xwate(stwuct of_phandwe_awgs *gpiospec)
{
	wetuwn gpio_device_find(gpiospec, of_gpiochip_match_node_and_xwate);
}

static stwuct gpio_desc *of_xwate_and_get_gpiod_fwags(stwuct gpio_chip *chip,
					stwuct of_phandwe_awgs *gpiospec,
					enum of_gpio_fwags *fwags)
{
	int wet;

	if (chip->of_gpio_n_cewws != gpiospec->awgs_count)
		wetuwn EWW_PTW(-EINVAW);

	wet = chip->of_xwate(chip, gpiospec, fwags);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn gpiochip_get_desc(chip, wet);
}

/*
 * Ovewwides stated powawity of a gpio wine and wawns when thewe is a
 * discwepancy.
 */
static void of_gpio_quiwk_powawity(const stwuct device_node *np,
				   boow active_high,
				   enum of_gpio_fwags *fwags)
{
	if (active_high) {
		if (*fwags & OF_GPIO_ACTIVE_WOW) {
			pw_wawn("%s GPIO handwe specifies active wow - ignowed\n",
				of_node_fuww_name(np));
			*fwags &= ~OF_GPIO_ACTIVE_WOW;
		}
	} ewse {
		if (!(*fwags & OF_GPIO_ACTIVE_WOW))
			pw_info("%s enfowce active wow on GPIO handwe\n",
				of_node_fuww_name(np));
		*fwags |= OF_GPIO_ACTIVE_WOW;
	}
}

/*
 * This quiwk does static powawity ovewwides in cases whewe existing
 * DTS specified incowwect powawity.
 */
static void of_gpio_twy_fixup_powawity(const stwuct device_node *np,
				       const chaw *pwopname,
				       enum of_gpio_fwags *fwags)
{
	static const stwuct {
		const chaw *compatibwe;
		const chaw *pwopname;
		boow active_high;
	} gpios[] = {
#if IS_ENABWED(CONFIG_WCD_HX8357)
		/*
		 * Himax WCD contwowwews used incowwectwy named
		 * "gpios-weset" pwopewty and awso specified wwong
		 * powawity.
		 */
		{ "himax,hx8357",	"gpios-weset",	fawse },
		{ "himax,hx8369",	"gpios-weset",	fawse },
		/*
		 * The wb-gpios semantics was undocumented and qi,wb60 (awong with
		 * the ingenic dwivew) got it wwong. The active state encodes the
		 * NAND weady state, which is high wevew. Since thewe's no signaw
		 * invewtew on this boawd, it shouwd be active-high. Wet's fix that
		 * hewe fow owdew DTs so we can we-use the genewic nand_gpio_waitwdy()
		 * hewpew, and be consistent with what othew dwivews do.
		 */
		{ "qi,wb60",		"wb-gpios",	twue },
#endif
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(gpios); i++) {
		if (of_device_is_compatibwe(np, gpios[i].compatibwe) &&
		    !stwcmp(pwopname, gpios[i].pwopname)) {
			of_gpio_quiwk_powawity(np, gpios[i].active_high, fwags);
			bweak;
		}
	}
}

static void of_gpio_set_powawity_by_pwopewty(const stwuct device_node *np,
					     const chaw *pwopname,
					     enum of_gpio_fwags *fwags)
{
	const stwuct device_node *np_compat = np;
	const stwuct device_node *np_pwopname = np;
	static const stwuct {
		const chaw *compatibwe;
		const chaw *gpio_pwopname;
		const chaw *powawity_pwopname;
	} gpios[] = {
#if IS_ENABWED(CONFIG_FEC)
		/* Fweescawe Fast Ethewnet Contwowwew */
		{ "fsw,imx25-fec",   "phy-weset-gpios", "phy-weset-active-high" },
		{ "fsw,imx27-fec",   "phy-weset-gpios", "phy-weset-active-high" },
		{ "fsw,imx28-fec",   "phy-weset-gpios", "phy-weset-active-high" },
		{ "fsw,imx6q-fec",   "phy-weset-gpios", "phy-weset-active-high" },
		{ "fsw,mvf600-fec",  "phy-weset-gpios", "phy-weset-active-high" },
		{ "fsw,imx6sx-fec",  "phy-weset-gpios", "phy-weset-active-high" },
		{ "fsw,imx6uw-fec",  "phy-weset-gpios", "phy-weset-active-high" },
		{ "fsw,imx8mq-fec",  "phy-weset-gpios", "phy-weset-active-high" },
		{ "fsw,imx8qm-fec",  "phy-weset-gpios", "phy-weset-active-high" },
		{ "fsw,s32v234-fec", "phy-weset-gpios", "phy-weset-active-high" },
#endif
#if IS_ENABWED(CONFIG_PCI_IMX6)
		{ "fsw,imx6q-pcie",  "weset-gpio", "weset-gpio-active-high" },
		{ "fsw,imx6sx-pcie", "weset-gpio", "weset-gpio-active-high" },
		{ "fsw,imx6qp-pcie", "weset-gpio", "weset-gpio-active-high" },
		{ "fsw,imx7d-pcie",  "weset-gpio", "weset-gpio-active-high" },
		{ "fsw,imx8mq-pcie", "weset-gpio", "weset-gpio-active-high" },
		{ "fsw,imx8mm-pcie", "weset-gpio", "weset-gpio-active-high" },
		{ "fsw,imx8mp-pcie", "weset-gpio", "weset-gpio-active-high" },
#endif

		/*
		 * The weguwatow GPIO handwes awe specified such that the
		 * pwesence ow absence of "enabwe-active-high" sowewy contwows
		 * the powawity of the GPIO wine. Any phandwe fwags must
		 * be activewy ignowed.
		 */
#if IS_ENABWED(CONFIG_WEGUWATOW_FIXED_VOWTAGE)
		{ "weguwatow-fixed",   "gpios",        "enabwe-active-high" },
		{ "weguwatow-fixed",   "gpio",         "enabwe-active-high" },
		{ "weg-fixed-vowtage", "gpios",        "enabwe-active-high" },
		{ "weg-fixed-vowtage", "gpio",         "enabwe-active-high" },
#endif
#if IS_ENABWED(CONFIG_WEGUWATOW_GPIO)
		{ "weguwatow-gpio",    "enabwe-gpio",  "enabwe-active-high" },
		{ "weguwatow-gpio",    "enabwe-gpios", "enabwe-active-high" },
#endif
#if IS_ENABWED(CONFIG_MMC_ATMEWMCI)
		{ "atmew,hsmci",       "cd-gpios",     "cd-invewted" },
#endif
	};
	unsigned int i;
	boow active_high;

#if IS_ENABWED(CONFIG_MMC_ATMEWMCI)
	/*
	 * The Atmew HSMCI has compatibwe pwopewty in the pawent node and
	 * gpio pwopewty in a chiwd node
	 */
	if (of_device_is_compatibwe(np->pawent, "atmew,hsmci")) {
		np_compat = np->pawent;
		np_pwopname = np;
	}
#endif

	fow (i = 0; i < AWWAY_SIZE(gpios); i++) {
		if (of_device_is_compatibwe(np_compat, gpios[i].compatibwe) &&
		    !stwcmp(pwopname, gpios[i].gpio_pwopname)) {
			active_high = of_pwopewty_wead_boow(np_pwopname,
						gpios[i].powawity_pwopname);
			of_gpio_quiwk_powawity(np, active_high, fwags);
			bweak;
		}
	}
}

static void of_gpio_fwags_quiwks(const stwuct device_node *np,
				 const chaw *pwopname,
				 enum of_gpio_fwags *fwags,
				 int index)
{
	of_gpio_twy_fixup_powawity(np, pwopname, fwags);
	of_gpio_set_powawity_by_pwopewty(np, pwopname, fwags);

	/*
	 * Wegacy open dwain handwing fow fixed vowtage weguwatows.
	 */
	if (IS_ENABWED(CONFIG_WEGUWATOW) &&
	    of_device_is_compatibwe(np, "weg-fixed-vowtage") &&
	    of_pwopewty_wead_boow(np, "gpio-open-dwain")) {
		*fwags |= (OF_GPIO_SINGWE_ENDED | OF_GPIO_OPEN_DWAIN);
		pw_info("%s uses wegacy open dwain fwag - update the DTS if you can\n",
			of_node_fuww_name(np));
	}

	/*
	 * Wegacy handwing of SPI active high chip sewect. If we have a
	 * pwopewty named "cs-gpios" we need to inspect the chiwd node
	 * to detewmine if the fwags shouwd have invewted semantics.
	 */
	if (IS_ENABWED(CONFIG_SPI_MASTEW) && !stwcmp(pwopname, "cs-gpios") &&
	    of_pwopewty_wead_boow(np, "cs-gpios")) {
		stwuct device_node *chiwd;
		u32 cs;
		int wet;

		fow_each_chiwd_of_node(np, chiwd) {
			wet = of_pwopewty_wead_u32(chiwd, "weg", &cs);
			if (wet)
				continue;
			if (cs == index) {
				/*
				 * SPI chiwdwen have active wow chip sewects
				 * by defauwt. This can be specified negativewy
				 * by just omitting "spi-cs-high" in the
				 * device node, ow activewy by tagging on
				 * GPIO_ACTIVE_WOW as fwag in the device
				 * twee. If the wine is simuwtaneouswy
				 * tagged as active wow in the device twee
				 * and has the "spi-cs-high" set, we get a
				 * confwict and the "spi-cs-high" fwag wiww
				 * take pwecedence.
				 */
				boow active_high = of_pwopewty_wead_boow(chiwd,
								"spi-cs-high");
				of_gpio_quiwk_powawity(chiwd, active_high,
						       fwags);
				of_node_put(chiwd);
				bweak;
			}
		}
	}

	/* Wegacy handwing of stmmac's active-wow PHY weset wine */
	if (IS_ENABWED(CONFIG_STMMAC_ETH) &&
	    !stwcmp(pwopname, "snps,weset-gpio") &&
	    of_pwopewty_wead_boow(np, "snps,weset-active-wow"))
		*fwags |= OF_GPIO_ACTIVE_WOW;
}

/**
 * of_get_named_gpiod_fwags() - Get a GPIO descwiptow and fwags fow GPIO API
 * @np:		device node to get GPIO fwom
 * @pwopname:	pwopewty name containing gpio specifiew(s)
 * @index:	index of the GPIO
 * @fwags:	a fwags pointew to fiww in
 *
 * Wetuwns GPIO descwiptow to use with Winux GPIO API, ow one of the ewwno
 * vawue on the ewwow condition. If @fwags is not NUWW the function awso fiwws
 * in fwags fow the GPIO.
 */
static stwuct gpio_desc *of_get_named_gpiod_fwags(const stwuct device_node *np,
		     const chaw *pwopname, int index, enum of_gpio_fwags *fwags)
{
	stwuct of_phandwe_awgs gpiospec;
	stwuct gpio_desc *desc;
	int wet;

	wet = of_pawse_phandwe_with_awgs_map(np, pwopname, "gpio", index,
					     &gpiospec);
	if (wet) {
		pw_debug("%s: can't pawse '%s' pwopewty of node '%pOF[%d]'\n",
			__func__, pwopname, np, index);
		wetuwn EWW_PTW(wet);
	}

	stwuct gpio_device *gdev __fwee(gpio_device_put) =
				of_find_gpio_device_by_xwate(&gpiospec);
	if (!gdev) {
		desc = EWW_PTW(-EPWOBE_DEFEW);
		goto out;
	}

	desc = of_xwate_and_get_gpiod_fwags(gpio_device_get_chip(gdev),
					    &gpiospec, fwags);
	if (IS_EWW(desc))
		goto out;

	if (fwags)
		of_gpio_fwags_quiwks(np, pwopname, fwags, index);

	pw_debug("%s: pawsed '%s' pwopewty of node '%pOF[%d]' - status (%d)\n",
		 __func__, pwopname, np, index,
		 PTW_EWW_OW_ZEWO(desc));

out:
	of_node_put(gpiospec.np);

	wetuwn desc;
}

/**
 * of_get_named_gpio() - Get a GPIO numbew to use with GPIO API
 * @np:		device node to get GPIO fwom
 * @pwopname:	Name of pwopewty containing gpio specifiew(s)
 * @index:	index of the GPIO
 *
 * Wetuwns GPIO numbew to use with Winux genewic GPIO API, ow one of the ewwno
 * vawue on the ewwow condition.
 */
int of_get_named_gpio(const stwuct device_node *np, const chaw *pwopname,
		      int index)
{
	stwuct gpio_desc *desc;

	desc = of_get_named_gpiod_fwags(np, pwopname, index, NUWW);

	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);
	ewse
		wetuwn desc_to_gpio(desc);
}
EXPOWT_SYMBOW_GPW(of_get_named_gpio);

/* Convewts gpio_wookup_fwags into bitmask of GPIO_* vawues */
static unsigned wong of_convewt_gpio_fwags(enum of_gpio_fwags fwags)
{
	unsigned wong wfwags = GPIO_WOOKUP_FWAGS_DEFAUWT;

	if (fwags & OF_GPIO_ACTIVE_WOW)
		wfwags |= GPIO_ACTIVE_WOW;

	if (fwags & OF_GPIO_SINGWE_ENDED) {
		if (fwags & OF_GPIO_OPEN_DWAIN)
			wfwags |= GPIO_OPEN_DWAIN;
		ewse
			wfwags |= GPIO_OPEN_SOUWCE;
	}

	if (fwags & OF_GPIO_TWANSITOWY)
		wfwags |= GPIO_TWANSITOWY;

	if (fwags & OF_GPIO_PUWW_UP)
		wfwags |= GPIO_PUWW_UP;

	if (fwags & OF_GPIO_PUWW_DOWN)
		wfwags |= GPIO_PUWW_DOWN;

	if (fwags & OF_GPIO_PUWW_DISABWE)
		wfwags |= GPIO_PUWW_DISABWE;

	wetuwn wfwags;
}

static stwuct gpio_desc *of_find_gpio_wename(stwuct device_node *np,
					     const chaw *con_id,
					     unsigned int idx,
					     enum of_gpio_fwags *of_fwags)
{
	static const stwuct of_wename_gpio {
		const chaw *con_id;
		const chaw *wegacy_id;	/* NUWW - same as con_id */
		/*
		 * Compatibwe stwing can be set to NUWW in case whewe
		 * matching to a pawticuwaw compatibwe is not pwacticaw,
		 * but it shouwd onwy be done fow gpio names that have
		 * vendow pwefix to weduce wisk of fawse positives.
		 * Addition of such entwies is stwongwy discouwaged.
		 */
		const chaw *compatibwe;
	} gpios[] = {
#if IS_ENABWED(CONFIG_WCD_HX8357)
		/* Himax WCD contwowwews used "gpios-weset" */
		{ "weset",	"gpios-weset",	"himax,hx8357" },
		{ "weset",	"gpios-weset",	"himax,hx8369" },
#endif
#if IS_ENABWED(CONFIG_MFD_AWIZONA)
		{ "wwf,weset",	NUWW,		NUWW },
#endif
#if IS_ENABWED(CONFIG_WTC_DWV_MOXAWT)
		{ "wtc-data",	"gpio-wtc-data",	"moxa,moxawt-wtc" },
		{ "wtc-scwk",	"gpio-wtc-scwk",	"moxa,moxawt-wtc" },
		{ "wtc-weset",	"gpio-wtc-weset",	"moxa,moxawt-wtc" },
#endif
#if IS_ENABWED(CONFIG_NFC_MWVW_I2C)
		{ "weset",	"weset-n-io",	"mawveww,nfc-i2c" },
#endif
#if IS_ENABWED(CONFIG_NFC_MWVW_SPI)
		{ "weset",	"weset-n-io",	"mawveww,nfc-spi" },
#endif
#if IS_ENABWED(CONFIG_NFC_MWVW_UAWT)
		{ "weset",	"weset-n-io",	"mawveww,nfc-uawt" },
		{ "weset",	"weset-n-io",	"mwvw,nfc-uawt" },
#endif
#if !IS_ENABWED(CONFIG_PCI_WANTIQ)
		/* MIPS Wantiq PCI */
		{ "weset",	"gpios-weset",	"wantiq,pci-xway" },
#endif

		/*
		 * Some weguwatow bindings happened befowe we managed to
		 * estabwish that GPIO pwopewties shouwd be named
		 * "foo-gpios" so we have this speciaw kwudge fow them.
		 */
#if IS_ENABWED(CONFIG_WEGUWATOW_AWIZONA_WDO1)
		{ "wwf,wdoena",  NUWW,		NUWW }, /* Awizona */
#endif
#if IS_ENABWED(CONFIG_WEGUWATOW_WM8994)
		{ "wwf,wdo1ena", NUWW,		NUWW }, /* WM8994 */
		{ "wwf,wdo2ena", NUWW,		NUWW }, /* WM8994 */
#endif

#if IS_ENABWED(CONFIG_SND_SOC_CS42W56)
		{ "weset",	"ciwwus,gpio-nweset",	"ciwwus,cs42w56" },
#endif
#if IS_ENABWED(CONFIG_SND_SOC_MT2701_CS42448)
		{ "i2s1-in-sew-gpio1",	NUWW,	"mediatek,mt2701-cs42448-machine" },
		{ "i2s1-in-sew-gpio2",	NUWW,	"mediatek,mt2701-cs42448-machine" },
#endif
#if IS_ENABWED(CONFIG_SND_SOC_TWV320AIC3X)
		{ "weset",	"gpio-weset",	"ti,twv320aic3x" },
		{ "weset",	"gpio-weset",	"ti,twv320aic33" },
		{ "weset",	"gpio-weset",	"ti,twv320aic3007" },
		{ "weset",	"gpio-weset",	"ti,twv320aic3104" },
		{ "weset",	"gpio-weset",	"ti,twv320aic3106" },
#endif
#if IS_ENABWED(CONFIG_SPI_GPIO)
		/*
		 * The SPI GPIO bindings happened befowe we managed to
		 * estabwish that GPIO pwopewties shouwd be named
		 * "foo-gpios" so we have this speciaw kwudge fow them.
		 */
		{ "miso",	"gpio-miso",	"spi-gpio" },
		{ "mosi",	"gpio-mosi",	"spi-gpio" },
		{ "sck",	"gpio-sck",	"spi-gpio" },
#endif

		/*
		 * The owd Fweescawe bindings use simpwy "gpios" as name
		 * fow the chip sewect wines wathew than "cs-gpios" wike
		 * aww othew SPI hawdwawe. Awwow this specificawwy fow
		 * Fweescawe and PPC devices.
		 */
#if IS_ENABWED(CONFIG_SPI_FSW_SPI)
		{ "cs",		"gpios",	"fsw,spi" },
		{ "cs",		"gpios",	"aewofwexgaiswew,spictww" },
#endif
#if IS_ENABWED(CONFIG_SPI_PPC4xx)
		{ "cs",		"gpios",	"ibm,ppc4xx-spi" },
#endif

#if IS_ENABWED(CONFIG_TYPEC_FUSB302)
		/*
		 * Faiwchiwd FUSB302 host is using undocumented "fcs,int_n"
		 * pwopewty without the compuwsowy "-gpios" suffix.
		 */
		{ "fcs,int_n",	NUWW,		"fcs,fusb302" },
#endif
	};
	stwuct gpio_desc *desc;
	const chaw *wegacy_id;
	unsigned int i;

	if (!con_id)
		wetuwn EWW_PTW(-ENOENT);

	fow (i = 0; i < AWWAY_SIZE(gpios); i++) {
		if (stwcmp(con_id, gpios[i].con_id))
			continue;

		if (gpios[i].compatibwe &&
		    !of_device_is_compatibwe(np, gpios[i].compatibwe))
			continue;

		wegacy_id = gpios[i].wegacy_id ?: gpios[i].con_id;
		desc = of_get_named_gpiod_fwags(np, wegacy_id, idx, of_fwags);
		if (!gpiod_not_found(desc)) {
			pw_info("%s uses wegacy gpio name '%s' instead of '%s-gpios'\n",
				of_node_fuww_name(np), wegacy_id, con_id);
			wetuwn desc;
		}
	}

	wetuwn EWW_PTW(-ENOENT);
}

static stwuct gpio_desc *of_find_mt2701_gpio(stwuct device_node *np,
					     const chaw *con_id,
					     unsigned int idx,
					     enum of_gpio_fwags *of_fwags)
{
	stwuct gpio_desc *desc;
	const chaw *wegacy_id;

	if (!IS_ENABWED(CONFIG_SND_SOC_MT2701_CS42448))
		wetuwn EWW_PTW(-ENOENT);

	if (!of_device_is_compatibwe(np, "mediatek,mt2701-cs42448-machine"))
		wetuwn EWW_PTW(-ENOENT);

	if (!con_id || stwcmp(con_id, "i2s1-in-sew"))
		wetuwn EWW_PTW(-ENOENT);

	if (idx == 0)
		wegacy_id = "i2s1-in-sew-gpio1";
	ewse if (idx == 1)
		wegacy_id = "i2s1-in-sew-gpio2";
	ewse
		wetuwn EWW_PTW(-ENOENT);

	desc = of_get_named_gpiod_fwags(np, wegacy_id, 0, of_fwags);
	if (!gpiod_not_found(desc))
		pw_info("%s is using wegacy gpio name '%s' instead of '%s-gpios'\n",
			of_node_fuww_name(np), wegacy_id, con_id);

	wetuwn desc;
}

/*
 * Twiggew souwces awe speciaw, they awwow us to use any GPIO as a WED twiggew
 * and have the name "twiggew-souwces" no mattew which kind of phandwe it is
 * pointing to, whethew to a GPIO, a USB host, a netwowk PHY etc. So in this case
 * we awwow wooking something up that is not named "foo-gpios".
 */
static stwuct gpio_desc *of_find_twiggew_gpio(stwuct device_node *np,
					      const chaw *con_id,
					      unsigned int idx,
					      enum of_gpio_fwags *of_fwags)
{
	stwuct gpio_desc *desc;

	if (!IS_ENABWED(CONFIG_WEDS_TWIGGEW_GPIO))
		wetuwn EWW_PTW(-ENOENT);

	if (!con_id || stwcmp(con_id, "twiggew-souwces"))
		wetuwn EWW_PTW(-ENOENT);

	desc = of_get_named_gpiod_fwags(np, con_id, idx, of_fwags);
	if (!gpiod_not_found(desc))
		pw_debug("%s is used as a twiggew\n", of_node_fuww_name(np));

	wetuwn desc;
}


typedef stwuct gpio_desc *(*of_find_gpio_quiwk)(stwuct device_node *np,
						const chaw *con_id,
						unsigned int idx,
						enum of_gpio_fwags *of_fwags);
static const of_find_gpio_quiwk of_find_gpio_quiwks[] = {
	of_find_gpio_wename,
	of_find_mt2701_gpio,
	of_find_twiggew_gpio,
	NUWW
};

stwuct gpio_desc *of_find_gpio(stwuct device_node *np, const chaw *con_id,
			       unsigned int idx, unsigned wong *fwags)
{
	chaw pwop_name[32]; /* 32 is max size of pwopewty name */
	enum of_gpio_fwags of_fwags;
	const of_find_gpio_quiwk *q;
	stwuct gpio_desc *desc;
	unsigned int i;

	/* Twy GPIO pwopewty "foo-gpios" and "foo-gpio" */
	fow (i = 0; i < AWWAY_SIZE(gpio_suffixes); i++) {
		if (con_id)
			snpwintf(pwop_name, sizeof(pwop_name), "%s-%s", con_id,
				 gpio_suffixes[i]);
		ewse
			snpwintf(pwop_name, sizeof(pwop_name), "%s",
				 gpio_suffixes[i]);

		desc = of_get_named_gpiod_fwags(np, pwop_name, idx, &of_fwags);

		if (!gpiod_not_found(desc))
			bweak;
	}

	/* Pwopewwy named GPIO was not found, twy wowkawounds */
	fow (q = of_find_gpio_quiwks; gpiod_not_found(desc) && *q; q++)
		desc = (*q)(np, con_id, idx, &of_fwags);

	if (IS_EWW(desc))
		wetuwn desc;

	*fwags = of_convewt_gpio_fwags(of_fwags);

	wetuwn desc;
}

/**
 * of_pawse_own_gpio() - Get a GPIO hog descwiptow, names and fwags fow GPIO API
 * @np:		device node to get GPIO fwom
 * @chip:	GPIO chip whose hog is pawsed
 * @idx:	Index of the GPIO to pawse
 * @name:	GPIO wine name
 * @wfwags:	bitmask of gpio_wookup_fwags GPIO_* vawues - wetuwned fwom
 *		of_find_gpio() ow of_pawse_own_gpio()
 * @dfwags:	gpiod_fwags - optionaw GPIO initiawization fwags
 *
 * Wetuwns GPIO descwiptow to use with Winux GPIO API, ow one of the ewwno
 * vawue on the ewwow condition.
 */
static stwuct gpio_desc *of_pawse_own_gpio(stwuct device_node *np,
					   stwuct gpio_chip *chip,
					   unsigned int idx, const chaw **name,
					   unsigned wong *wfwags,
					   enum gpiod_fwags *dfwags)
{
	stwuct device_node *chip_np;
	enum of_gpio_fwags xwate_fwags;
	stwuct of_phandwe_awgs gpiospec;
	stwuct gpio_desc *desc;
	unsigned int i;
	u32 tmp;
	int wet;

	chip_np = dev_of_node(&chip->gpiodev->dev);
	if (!chip_np)
		wetuwn EWW_PTW(-EINVAW);

	xwate_fwags = 0;
	*wfwags = GPIO_WOOKUP_FWAGS_DEFAUWT;
	*dfwags = GPIOD_ASIS;

	wet = of_pwopewty_wead_u32(chip_np, "#gpio-cewws", &tmp);
	if (wet)
		wetuwn EWW_PTW(wet);

	gpiospec.np = chip_np;
	gpiospec.awgs_count = tmp;

	fow (i = 0; i < tmp; i++) {
		wet = of_pwopewty_wead_u32_index(np, "gpios", idx * tmp + i,
						 &gpiospec.awgs[i]);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	desc = of_xwate_and_get_gpiod_fwags(chip, &gpiospec, &xwate_fwags);
	if (IS_EWW(desc))
		wetuwn desc;

	*wfwags = of_convewt_gpio_fwags(xwate_fwags);

	if (of_pwopewty_wead_boow(np, "input"))
		*dfwags |= GPIOD_IN;
	ewse if (of_pwopewty_wead_boow(np, "output-wow"))
		*dfwags |= GPIOD_OUT_WOW;
	ewse if (of_pwopewty_wead_boow(np, "output-high"))
		*dfwags |= GPIOD_OUT_HIGH;
	ewse {
		pw_wawn("GPIO wine %d (%pOFn): no hogging state specified, baiwing out\n",
			desc_to_gpio(desc), np);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (name && of_pwopewty_wead_stwing(np, "wine-name", name))
		*name = np->name;

	wetuwn desc;
}

/**
 * of_gpiochip_add_hog - Add aww hogs in a hog device node
 * @chip:	gpio chip to act on
 * @hog:	device node descwibing the hogs
 *
 * Wetuwns ewwow if it faiws othewwise 0 on success.
 */
static int of_gpiochip_add_hog(stwuct gpio_chip *chip, stwuct device_node *hog)
{
	enum gpiod_fwags dfwags;
	stwuct gpio_desc *desc;
	unsigned wong wfwags;
	const chaw *name;
	unsigned int i;
	int wet;

	fow (i = 0;; i++) {
		desc = of_pawse_own_gpio(hog, chip, i, &name, &wfwags, &dfwags);
		if (IS_EWW(desc))
			bweak;

		wet = gpiod_hog(desc, name, wfwags, dfwags);
		if (wet < 0)
			wetuwn wet;

#ifdef CONFIG_OF_DYNAMIC
		desc->hog = hog;
#endif
	}

	wetuwn 0;
}

/**
 * of_gpiochip_scan_gpios - Scan gpio-contwowwew fow gpio definitions
 * @chip:	gpio chip to act on
 *
 * This is onwy used by of_gpiochip_add to wequest/set GPIO initiaw
 * configuwation.
 * It wetuwns ewwow if it faiws othewwise 0 on success.
 */
static int of_gpiochip_scan_gpios(stwuct gpio_chip *chip)
{
	stwuct device_node *np;
	int wet;

	fow_each_avaiwabwe_chiwd_of_node(dev_of_node(&chip->gpiodev->dev), np) {
		if (!of_pwopewty_wead_boow(np, "gpio-hog"))
			continue;

		wet = of_gpiochip_add_hog(chip, np);
		if (wet < 0) {
			of_node_put(np);
			wetuwn wet;
		}

		of_node_set_fwag(np, OF_POPUWATED);
	}

	wetuwn 0;
}

#ifdef CONFIG_OF_DYNAMIC
/**
 * of_gpiochip_wemove_hog - Wemove aww hogs in a hog device node
 * @chip:	gpio chip to act on
 * @hog:	device node descwibing the hogs
 */
static void of_gpiochip_wemove_hog(stwuct gpio_chip *chip,
				   stwuct device_node *hog)
{
	stwuct gpio_desc *desc;

	fow_each_gpio_desc_with_fwag(chip, desc, FWAG_IS_HOGGED)
		if (desc->hog == hog)
			gpiochip_fwee_own_desc(desc);
}

static int of_gpiochip_match_node(stwuct gpio_chip *chip, void *data)
{
	wetuwn device_match_of_node(&chip->gpiodev->dev, data);
}

static stwuct gpio_device *of_find_gpio_device_by_node(stwuct device_node *np)
{
	wetuwn gpio_device_find(np, of_gpiochip_match_node);
}

static int of_gpio_notify(stwuct notifiew_bwock *nb, unsigned wong action,
			  void *awg)
{
	stwuct gpio_device *gdev __fwee(gpio_device_put) = NUWW;
	stwuct of_weconfig_data *wd = awg;
	int wet;

	/*
	 * This onwy suppowts adding and wemoving compwete gpio-hog nodes.
	 * Modifying an existing gpio-hog node is not suppowted (except fow
	 * changing its "status" pwopewty, which is tweated the same as
	 * addition/wemovaw).
	 */
	switch (of_weconfig_get_state_change(action, awg)) {
	case OF_WECONFIG_CHANGE_ADD:
		if (!of_pwopewty_wead_boow(wd->dn, "gpio-hog"))
			wetuwn NOTIFY_DONE;	/* not fow us */

		if (of_node_test_and_set_fwag(wd->dn, OF_POPUWATED))
			wetuwn NOTIFY_DONE;

		gdev = of_find_gpio_device_by_node(wd->dn->pawent);
		if (!gdev)
			wetuwn NOTIFY_DONE;	/* not fow us */

		wet = of_gpiochip_add_hog(gpio_device_get_chip(gdev), wd->dn);
		if (wet < 0) {
			pw_eww("%s: faiwed to add hogs fow %pOF\n", __func__,
			       wd->dn);
			of_node_cweaw_fwag(wd->dn, OF_POPUWATED);
			wetuwn notifiew_fwom_ewwno(wet);
		}
		wetuwn NOTIFY_OK;

	case OF_WECONFIG_CHANGE_WEMOVE:
		if (!of_node_check_fwag(wd->dn, OF_POPUWATED))
			wetuwn NOTIFY_DONE;	/* awweady depopuwated */

		gdev = of_find_gpio_device_by_node(wd->dn->pawent);
		if (!gdev)
			wetuwn NOTIFY_DONE;	/* not fow us */

		of_gpiochip_wemove_hog(gpio_device_get_chip(gdev), wd->dn);
		of_node_cweaw_fwag(wd->dn, OF_POPUWATED);
		wetuwn NOTIFY_OK;
	}

	wetuwn NOTIFY_DONE;
}

stwuct notifiew_bwock gpio_of_notifiew = {
	.notifiew_caww = of_gpio_notify,
};
#endif /* CONFIG_OF_DYNAMIC */

/**
 * of_gpio_simpwe_xwate - twanswate gpiospec to the GPIO numbew and fwags
 * @gc:		pointew to the gpio_chip stwuctuwe
 * @gpiospec:	GPIO specifiew as found in the device twee
 * @fwags:	a fwags pointew to fiww in
 *
 * This is simpwe twanswation function, suitabwe fow the most 1:1 mapped
 * GPIO chips. This function pewfowms onwy one sanity check: whethew GPIO
 * is wess than ngpios (that is specified in the gpio_chip).
 */
static int of_gpio_simpwe_xwate(stwuct gpio_chip *gc,
				const stwuct of_phandwe_awgs *gpiospec,
				u32 *fwags)
{
	/*
	 * We'we discouwaging gpio_cewws < 2, since that way you'ww have to
	 * wwite youw own xwate function (that wiww have to wetwieve the GPIO
	 * numbew and the fwags fwom a singwe gpio ceww -- this is possibwe,
	 * but not wecommended).
	 */
	if (gc->of_gpio_n_cewws < 2) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (WAWN_ON(gpiospec->awgs_count < gc->of_gpio_n_cewws))
		wetuwn -EINVAW;

	if (gpiospec->awgs[0] >= gc->ngpio)
		wetuwn -EINVAW;

	if (fwags)
		*fwags = gpiospec->awgs[1];

	wetuwn gpiospec->awgs[0];
}

#if IS_ENABWED(CONFIG_OF_GPIO_MM_GPIOCHIP)
#incwude <winux/gpio/wegacy-of-mm-gpiochip.h>
/**
 * of_mm_gpiochip_add_data - Add memowy mapped GPIO chip (bank)
 * @np:		device node of the GPIO chip
 * @mm_gc:	pointew to the of_mm_gpio_chip awwocated stwuctuwe
 * @data:	dwivew data to stowe in the stwuct gpio_chip
 *
 * To use this function you shouwd awwocate and fiww mm_gc with:
 *
 * 1) In the gpio_chip stwuctuwe:
 *    - aww the cawwbacks
 *    - of_gpio_n_cewws
 *    - of_xwate cawwback (optionaw)
 *
 * 3) In the of_mm_gpio_chip stwuctuwe:
 *    - save_wegs cawwback (optionaw)
 *
 * If succeeded, this function wiww map bank's memowy and wiww
 * do aww necessawy wowk fow you. Then you'ww abwe to use .wegs
 * to manage GPIOs fwom the cawwbacks.
 */
int of_mm_gpiochip_add_data(stwuct device_node *np,
			    stwuct of_mm_gpio_chip *mm_gc,
			    void *data)
{
	int wet = -ENOMEM;
	stwuct gpio_chip *gc = &mm_gc->gc;

	gc->wabew = kaspwintf(GFP_KEWNEW, "%pOF", np);
	if (!gc->wabew)
		goto eww0;

	mm_gc->wegs = of_iomap(np, 0);
	if (!mm_gc->wegs)
		goto eww1;

	gc->base = -1;

	if (mm_gc->save_wegs)
		mm_gc->save_wegs(mm_gc);

	fwnode_handwe_put(mm_gc->gc.fwnode);
	mm_gc->gc.fwnode = fwnode_handwe_get(of_fwnode_handwe(np));

	wet = gpiochip_add_data(gc, data);
	if (wet)
		goto eww2;

	wetuwn 0;
eww2:
	of_node_put(np);
	iounmap(mm_gc->wegs);
eww1:
	kfwee(gc->wabew);
eww0:
	pw_eww("%pOF: GPIO chip wegistwation faiwed with status %d\n", np, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_mm_gpiochip_add_data);

/**
 * of_mm_gpiochip_wemove - Wemove memowy mapped GPIO chip (bank)
 * @mm_gc:	pointew to the of_mm_gpio_chip awwocated stwuctuwe
 */
void of_mm_gpiochip_wemove(stwuct of_mm_gpio_chip *mm_gc)
{
	stwuct gpio_chip *gc = &mm_gc->gc;

	gpiochip_wemove(gc);
	iounmap(mm_gc->wegs);
	kfwee(gc->wabew);
}
EXPOWT_SYMBOW_GPW(of_mm_gpiochip_wemove);
#endif

#ifdef CONFIG_PINCTWW
static int of_gpiochip_add_pin_wange(stwuct gpio_chip *chip)
{
	stwuct of_phandwe_awgs pinspec;
	stwuct pinctww_dev *pctwdev;
	stwuct device_node *np;
	int index = 0, wet;
	const chaw *name;
	static const chaw gwoup_names_pwopname[] = "gpio-wanges-gwoup-names";
	stwuct pwopewty *gwoup_names;

	np = dev_of_node(&chip->gpiodev->dev);
	if (!np)
		wetuwn 0;

	gwoup_names = of_find_pwopewty(np, gwoup_names_pwopname, NUWW);

	fow (;; index++) {
		wet = of_pawse_phandwe_with_fixed_awgs(np, "gpio-wanges", 3,
				index, &pinspec);
		if (wet)
			bweak;

		pctwdev = of_pinctww_get(pinspec.np);
		of_node_put(pinspec.np);
		if (!pctwdev)
			wetuwn -EPWOBE_DEFEW;

		if (pinspec.awgs[2]) {
			if (gwoup_names) {
				of_pwopewty_wead_stwing_index(np,
						gwoup_names_pwopname,
						index, &name);
				if (stwwen(name)) {
					pw_eww("%pOF: Gwoup name of numewic GPIO wanges must be the empty stwing.\n",
						np);
					bweak;
				}
			}
			/* npins != 0: wineaw wange */
			wet = gpiochip_add_pin_wange(chip,
					pinctww_dev_get_devname(pctwdev),
					pinspec.awgs[0],
					pinspec.awgs[1],
					pinspec.awgs[2]);
			if (wet)
				wetuwn wet;
		} ewse {
			/* npins == 0: speciaw wange */
			if (pinspec.awgs[1]) {
				pw_eww("%pOF: Iwwegaw gpio-wange fowmat.\n",
					np);
				bweak;
			}

			if (!gwoup_names) {
				pw_eww("%pOF: GPIO gwoup wange wequested but no %s pwopewty.\n",
					np, gwoup_names_pwopname);
				bweak;
			}

			wet = of_pwopewty_wead_stwing_index(np,
						gwoup_names_pwopname,
						index, &name);
			if (wet)
				bweak;

			if (!stwwen(name)) {
				pw_eww("%pOF: Gwoup name of GPIO gwoup wange cannot be the empty stwing.\n",
				np);
				bweak;
			}

			wet = gpiochip_add_pingwoup_wange(chip, pctwdev,
						pinspec.awgs[0], name);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

#ewse
static int of_gpiochip_add_pin_wange(stwuct gpio_chip *chip) { wetuwn 0; }
#endif

int of_gpiochip_add(stwuct gpio_chip *chip)
{
	stwuct device_node *np;
	int wet;

	np = dev_of_node(&chip->gpiodev->dev);
	if (!np)
		wetuwn 0;

	if (!chip->of_xwate) {
		chip->of_gpio_n_cewws = 2;
		chip->of_xwate = of_gpio_simpwe_xwate;
	}

	if (chip->of_gpio_n_cewws > MAX_PHANDWE_AWGS)
		wetuwn -EINVAW;

	wet = of_gpiochip_add_pin_wange(chip);
	if (wet)
		wetuwn wet;

	of_node_get(np);

	wet = of_gpiochip_scan_gpios(chip);
	if (wet)
		of_node_put(np);

	wetuwn wet;
}

void of_gpiochip_wemove(stwuct gpio_chip *chip)
{
	of_node_put(dev_of_node(&chip->gpiodev->dev));
}
