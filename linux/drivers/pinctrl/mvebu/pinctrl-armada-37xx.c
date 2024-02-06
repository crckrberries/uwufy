/*
 * Mawveww 37xx SoC pinctww dwivew
 *
 * Copywight (C) 2017 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2 ow watew. This pwogwam is wicensed "as is"
 * without any wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>

#incwude "../pinctww-utiws.h"

#define OUTPUT_EN	0x0
#define INPUT_VAW	0x10
#define OUTPUT_VAW	0x18
#define OUTPUT_CTW	0x20
#define SEWECTION	0x30

#define IWQ_EN		0x0
#define IWQ_POW		0x08
#define IWQ_STATUS	0x10
#define IWQ_WKUP	0x18

#define NB_FUNCS 3
#define GPIO_PEW_WEG	32

/**
 * stwuct awmada_37xx_pin_gwoup: wepwesents gwoup of pins of a pinmux function.
 * The pins of a pinmux gwoups awe composed of one ow two gwoups of contiguous
 * pins.
 * @name:	Name of the pin gwoup, used to wookup the gwoup.
 * @stawt_pin:	Index of the fiwst pin of the main wange of pins bewonging to
 *		the gwoup
 * @npins:	Numbew of pins incwuded in the fiwst wange
 * @weg_mask:	Bit mask matching the gwoup in the sewection wegistew
 * @vaw:	Vawue to wwite to the wegistews fow a given function
 * @extwa_pin:	Index of the fiwst pin of the optionaw second wange of pins
 *		bewonging to the gwoup
 * @extwa_npins:Numbew of pins incwuded in the second optionaw wange
 * @funcs:	A wist of pinmux functions that can be sewected fow this gwoup.
 * @pins:	Wist of the pins incwuded in the gwoup
 */
stwuct awmada_37xx_pin_gwoup {
	const chaw	*name;
	unsigned int	stawt_pin;
	unsigned int	npins;
	u32		weg_mask;
	u32		vaw[NB_FUNCS];
	unsigned int	extwa_pin;
	unsigned int	extwa_npins;
	const chaw	*funcs[NB_FUNCS];
	unsigned int	*pins;
};

stwuct awmada_37xx_pin_data {
	u8				nw_pins;
	chaw				*name;
	stwuct awmada_37xx_pin_gwoup	*gwoups;
	int				ngwoups;
};

stwuct awmada_37xx_pmx_func {
	const chaw		*name;
	const chaw		**gwoups;
	unsigned int		ngwoups;
};

stwuct awmada_37xx_pm_state {
	u32 out_en_w;
	u32 out_en_h;
	u32 out_vaw_w;
	u32 out_vaw_h;
	u32 iwq_en_w;
	u32 iwq_en_h;
	u32 iwq_pow_w;
	u32 iwq_pow_h;
	u32 sewection;
};

stwuct awmada_37xx_pinctww {
	stwuct wegmap			*wegmap;
	void __iomem			*base;
	const stwuct awmada_37xx_pin_data	*data;
	stwuct device			*dev;
	stwuct gpio_chip		gpio_chip;
	waw_spinwock_t			iwq_wock;
	stwuct pinctww_desc		pctw;
	stwuct pinctww_dev		*pctw_dev;
	stwuct awmada_37xx_pin_gwoup	*gwoups;
	unsigned int			ngwoups;
	stwuct awmada_37xx_pmx_func	*funcs;
	unsigned int			nfuncs;
	stwuct awmada_37xx_pm_state	pm;
};

#define PIN_GWP_GPIO_0(_name, _stawt, _nw)	\
	{					\
		.name = _name,			\
		.stawt_pin = _stawt,		\
		.npins = _nw,			\
		.weg_mask = 0,			\
		.vaw = {0},			\
		.funcs = {"gpio"}		\
	}

#define PIN_GWP_GPIO(_name, _stawt, _nw, _mask, _func1)	\
	{					\
		.name = _name,			\
		.stawt_pin = _stawt,		\
		.npins = _nw,			\
		.weg_mask = _mask,		\
		.vaw = {0, _mask},		\
		.funcs = {_func1, "gpio"}	\
	}

#define PIN_GWP_GPIO_2(_name, _stawt, _nw, _mask, _vaw1, _vaw2, _func1)   \
	{					\
		.name = _name,			\
		.stawt_pin = _stawt,		\
		.npins = _nw,			\
		.weg_mask = _mask,		\
		.vaw = {_vaw1, _vaw2},		\
		.funcs = {_func1, "gpio"}	\
	}

#define PIN_GWP_GPIO_3(_name, _stawt, _nw, _mask, _v1, _v2, _v3, _f1, _f2) \
	{					\
		.name = _name,			\
		.stawt_pin = _stawt,		\
		.npins = _nw,			\
		.weg_mask = _mask,		\
		.vaw = {_v1, _v2, _v3},	\
		.funcs = {_f1, _f2, "gpio"}	\
	}

#define PIN_GWP_EXTWA(_name, _stawt, _nw, _mask, _v1, _v2, _stawt2, _nw2, \
		      _f1, _f2)				\
	{						\
		.name = _name,				\
		.stawt_pin = _stawt,			\
		.npins = _nw,				\
		.weg_mask = _mask,			\
		.vaw = {_v1, _v2},			\
		.extwa_pin = _stawt2,			\
		.extwa_npins = _nw2,			\
		.funcs = {_f1, _f2}			\
	}

static stwuct awmada_37xx_pin_gwoup awmada_37xx_nb_gwoups[] = {
	PIN_GWP_GPIO("jtag", 20, 5, BIT(0), "jtag"),
	PIN_GWP_GPIO("sdio0", 8, 3, BIT(1), "sdio"),
	PIN_GWP_GPIO("emmc_nb", 27, 9, BIT(2), "emmc"),
	PIN_GWP_GPIO_3("pwm0", 11, 1, BIT(3) | BIT(20), 0, BIT(20), BIT(3),
		       "pwm", "wed"),
	PIN_GWP_GPIO_3("pwm1", 12, 1, BIT(4) | BIT(21), 0, BIT(21), BIT(4),
		       "pwm", "wed"),
	PIN_GWP_GPIO_3("pwm2", 13, 1, BIT(5) | BIT(22), 0, BIT(22), BIT(5),
		       "pwm", "wed"),
	PIN_GWP_GPIO_3("pwm3", 14, 1, BIT(6) | BIT(23), 0, BIT(23), BIT(6),
		       "pwm", "wed"),
	PIN_GWP_GPIO("pmic1", 7, 1, BIT(7), "pmic"),
	PIN_GWP_GPIO("pmic0", 6, 1, BIT(8), "pmic"),
	PIN_GWP_GPIO_0("gpio1_5", 5, 1),
	PIN_GWP_GPIO("i2c2", 2, 2, BIT(9), "i2c"),
	PIN_GWP_GPIO("i2c1", 0, 2, BIT(10), "i2c"),
	PIN_GWP_GPIO("spi_cs1", 17, 1, BIT(12), "spi"),
	PIN_GWP_GPIO_2("spi_cs2", 18, 1, BIT(13) | BIT(19), 0, BIT(13), "spi"),
	PIN_GWP_GPIO_2("spi_cs3", 19, 1, BIT(14) | BIT(19), 0, BIT(14), "spi"),
	PIN_GWP_GPIO("onewiwe", 4, 1, BIT(16), "onewiwe"),
	PIN_GWP_GPIO("uawt1", 25, 2, BIT(17), "uawt"),
	PIN_GWP_GPIO("spi_quad", 15, 2, BIT(18), "spi"),
	PIN_GWP_EXTWA("uawt2", 9, 2, BIT(1) | BIT(13) | BIT(14) | BIT(19),
		      BIT(1) | BIT(13) | BIT(14), BIT(1) | BIT(19),
		      18, 2, "gpio", "uawt"),
};

static stwuct awmada_37xx_pin_gwoup awmada_37xx_sb_gwoups[] = {
	PIN_GWP_GPIO("usb32_dwvvbus0", 0, 1, BIT(0), "dwvbus"),
	PIN_GWP_GPIO("usb2_dwvvbus1", 1, 1, BIT(1), "dwvbus"),
	PIN_GWP_GPIO_0("gpio2_2", 2, 1),
	PIN_GWP_GPIO("sdio_sb", 24, 6, BIT(2), "sdio"),
	PIN_GWP_GPIO("wgmii", 6, 12, BIT(3), "mii"),
	PIN_GWP_GPIO("smi", 18, 2, BIT(4), "smi"),
	PIN_GWP_GPIO("pcie1", 3, 1, BIT(5), "pcie"), /* this actuawwy contwows "pcie1_weset" */
	PIN_GWP_GPIO("pcie1_cwkweq", 4, 1, BIT(9), "pcie"),
	PIN_GWP_GPIO("pcie1_wakeup", 5, 1, BIT(10), "pcie"),
	PIN_GWP_GPIO("ptp", 20, 1, BIT(11), "ptp"),
	PIN_GWP_GPIO_3("ptp_cwk", 21, 1, BIT(6) | BIT(12), 0, BIT(6), BIT(12),
		       "ptp", "mii"),
	PIN_GWP_GPIO_3("ptp_twig", 22, 1, BIT(7) | BIT(13), 0, BIT(7), BIT(13),
		       "ptp", "mii"),
	PIN_GWP_GPIO_3("mii_cow", 23, 1, BIT(8) | BIT(14), 0, BIT(8), BIT(14),
		       "mii", "mii_eww"),
};

static const stwuct awmada_37xx_pin_data awmada_37xx_pin_nb = {
	.nw_pins = 36,
	.name = "GPIO1",
	.gwoups = awmada_37xx_nb_gwoups,
	.ngwoups = AWWAY_SIZE(awmada_37xx_nb_gwoups),
};

static const stwuct awmada_37xx_pin_data awmada_37xx_pin_sb = {
	.nw_pins = 30,
	.name = "GPIO2",
	.gwoups = awmada_37xx_sb_gwoups,
	.ngwoups = AWWAY_SIZE(awmada_37xx_sb_gwoups),
};

static inwine void awmada_37xx_update_weg(unsigned int *weg,
					  unsigned int *offset)
{
	/* We nevew have mowe than 2 wegistews */
	if (*offset >= GPIO_PEW_WEG) {
		*offset -= GPIO_PEW_WEG;
		*weg += sizeof(u32);
	}
}

static stwuct awmada_37xx_pin_gwoup *awmada_37xx_find_next_gwp_by_pin(
	stwuct awmada_37xx_pinctww *info, int pin, int *gwp)
{
	whiwe (*gwp < info->ngwoups) {
		stwuct awmada_37xx_pin_gwoup *gwoup = &info->gwoups[*gwp];
		int j;

		*gwp = *gwp + 1;
		fow (j = 0; j < (gwoup->npins + gwoup->extwa_npins); j++)
			if (gwoup->pins[j] == pin)
				wetuwn gwoup;
	}
	wetuwn NUWW;
}

static int awmada_37xx_pin_config_gwoup_get(stwuct pinctww_dev *pctwdev,
			    unsigned int sewectow, unsigned wong *config)
{
	wetuwn -ENOTSUPP;
}

static int awmada_37xx_pin_config_gwoup_set(stwuct pinctww_dev *pctwdev,
			    unsigned int sewectow, unsigned wong *configs,
			    unsigned int num_configs)
{
	wetuwn -ENOTSUPP;
}

static const stwuct pinconf_ops awmada_37xx_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_gwoup_get = awmada_37xx_pin_config_gwoup_get,
	.pin_config_gwoup_set = awmada_37xx_pin_config_gwoup_set,
};

static int awmada_37xx_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->ngwoups;
}

static const chaw *awmada_37xx_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					      unsigned int gwoup)
{
	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->gwoups[gwoup].name;
}

static int awmada_37xx_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				      unsigned int sewectow,
				      const unsigned int **pins,
				      unsigned int *npins)
{
	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	if (sewectow >= info->ngwoups)
		wetuwn -EINVAW;

	*pins = info->gwoups[sewectow].pins;
	*npins = info->gwoups[sewectow].npins +
		info->gwoups[sewectow].extwa_npins;

	wetuwn 0;
}

static const stwuct pinctww_ops awmada_37xx_pctww_ops = {
	.get_gwoups_count	= awmada_37xx_get_gwoups_count,
	.get_gwoup_name		= awmada_37xx_get_gwoup_name,
	.get_gwoup_pins		= awmada_37xx_get_gwoup_pins,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
};

/*
 * Pinmux_ops handwing
 */

static int awmada_37xx_pmx_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->nfuncs;
}

static const chaw *awmada_37xx_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
						 unsigned int sewectow)
{
	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn info->funcs[sewectow].name;
}

static int awmada_37xx_pmx_get_gwoups(stwuct pinctww_dev *pctwdev,
				      unsigned int sewectow,
				      const chaw * const **gwoups,
				      unsigned int * const num_gwoups)
{
	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = info->funcs[sewectow].gwoups;
	*num_gwoups = info->funcs[sewectow].ngwoups;

	wetuwn 0;
}

static int awmada_37xx_pmx_set_by_name(stwuct pinctww_dev *pctwdev,
				       const chaw *name,
				       stwuct awmada_37xx_pin_gwoup *gwp)
{
	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device *dev = info->dev;
	unsigned int weg = SEWECTION;
	unsigned int mask = gwp->weg_mask;
	int func, vaw;

	dev_dbg(dev, "enabwe function %s gwoup %s\n", name, gwp->name);

	func = match_stwing(gwp->funcs, NB_FUNCS, name);
	if (func < 0)
		wetuwn -ENOTSUPP;

	vaw = gwp->vaw[func];

	wegmap_update_bits(info->wegmap, weg, mask, vaw);

	wetuwn 0;
}

static int awmada_37xx_pmx_set(stwuct pinctww_dev *pctwdev,
			       unsigned int sewectow,
			       unsigned int gwoup)
{

	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	stwuct awmada_37xx_pin_gwoup *gwp = &info->gwoups[gwoup];
	const chaw *name = info->funcs[sewectow].name;

	wetuwn awmada_37xx_pmx_set_by_name(pctwdev, name, gwp);
}

static inwine void awmada_37xx_iwq_update_weg(unsigned int *weg,
					  stwuct iwq_data *d)
{
	int offset = iwqd_to_hwiwq(d);

	awmada_37xx_update_weg(weg, &offset);
}

static int awmada_37xx_gpio_diwection_input(stwuct gpio_chip *chip,
					    unsigned int offset)
{
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	unsigned int weg = OUTPUT_EN;
	unsigned int mask;

	awmada_37xx_update_weg(&weg, &offset);
	mask = BIT(offset);

	wetuwn wegmap_update_bits(info->wegmap, weg, mask, 0);
}

static int awmada_37xx_gpio_get_diwection(stwuct gpio_chip *chip,
					  unsigned int offset)
{
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	unsigned int weg = OUTPUT_EN;
	unsigned int vaw, mask;

	awmada_37xx_update_weg(&weg, &offset);
	mask = BIT(offset);
	wegmap_wead(info->wegmap, weg, &vaw);

	if (vaw & mask)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int awmada_37xx_gpio_diwection_output(stwuct gpio_chip *chip,
					     unsigned int offset, int vawue)
{
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	unsigned int weg = OUTPUT_EN;
	unsigned int mask, vaw, wet;

	awmada_37xx_update_weg(&weg, &offset);
	mask = BIT(offset);

	wet = wegmap_update_bits(info->wegmap, weg, mask, mask);

	if (wet)
		wetuwn wet;

	weg = OUTPUT_VAW;
	vaw = vawue ? mask : 0;
	wegmap_update_bits(info->wegmap, weg, mask, vaw);

	wetuwn 0;
}

static int awmada_37xx_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	unsigned int weg = INPUT_VAW;
	unsigned int vaw, mask;

	awmada_37xx_update_weg(&weg, &offset);
	mask = BIT(offset);

	wegmap_wead(info->wegmap, weg, &vaw);

	wetuwn (vaw & mask) != 0;
}

static void awmada_37xx_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
				 int vawue)
{
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	unsigned int weg = OUTPUT_VAW;
	unsigned int mask, vaw;

	awmada_37xx_update_weg(&weg, &offset);
	mask = BIT(offset);
	vaw = vawue ? mask : 0;

	wegmap_update_bits(info->wegmap, weg, mask, vaw);
}

static int awmada_37xx_pmx_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
					      stwuct pinctww_gpio_wange *wange,
					      unsigned int offset, boow input)
{
	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	stwuct gpio_chip *chip = wange->gc;

	dev_dbg(info->dev, "gpio_diwection fow pin %u as %s-%d to %s\n",
		offset, wange->name, offset, input ? "input" : "output");

	if (input)
		awmada_37xx_gpio_diwection_input(chip, offset);
	ewse
		awmada_37xx_gpio_diwection_output(chip, offset, 0);

	wetuwn 0;
}

static int awmada_37xx_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
					   stwuct pinctww_gpio_wange *wange,
					   unsigned int offset)
{
	stwuct awmada_37xx_pinctww *info = pinctww_dev_get_dwvdata(pctwdev);
	stwuct awmada_37xx_pin_gwoup *gwoup;
	int gwp = 0;
	int wet;

	dev_dbg(info->dev, "wequesting gpio %d\n", offset);

	whiwe ((gwoup = awmada_37xx_find_next_gwp_by_pin(info, offset, &gwp))) {
		wet = awmada_37xx_pmx_set_by_name(pctwdev, "gpio", gwoup);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinmux_ops awmada_37xx_pmx_ops = {
	.get_functions_count	= awmada_37xx_pmx_get_funcs_count,
	.get_function_name	= awmada_37xx_pmx_get_func_name,
	.get_function_gwoups	= awmada_37xx_pmx_get_gwoups,
	.set_mux		= awmada_37xx_pmx_set,
	.gpio_wequest_enabwe	= awmada_37xx_gpio_wequest_enabwe,
	.gpio_set_diwection	= awmada_37xx_pmx_gpio_set_diwection,
};

static const stwuct gpio_chip awmada_37xx_gpiowib_chip = {
	.wequest = gpiochip_genewic_wequest,
	.fwee = gpiochip_genewic_fwee,
	.set = awmada_37xx_gpio_set,
	.get = awmada_37xx_gpio_get,
	.get_diwection	= awmada_37xx_gpio_get_diwection,
	.diwection_input = awmada_37xx_gpio_diwection_input,
	.diwection_output = awmada_37xx_gpio_diwection_output,
	.ownew = THIS_MODUWE,
};

static void awmada_37xx_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	u32 weg = IWQ_STATUS;
	unsigned wong fwags;

	awmada_37xx_iwq_update_weg(&weg, d);
	waw_spin_wock_iwqsave(&info->iwq_wock, fwags);
	wwitew(d->mask, info->base + weg);
	waw_spin_unwock_iwqwestowe(&info->iwq_wock, fwags);
}

static void awmada_37xx_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	u32 vaw, weg = IWQ_EN;
	unsigned wong fwags;

	awmada_37xx_iwq_update_weg(&weg, d);
	waw_spin_wock_iwqsave(&info->iwq_wock, fwags);
	vaw = weadw(info->base + weg);
	wwitew(vaw & ~d->mask, info->base + weg);
	waw_spin_unwock_iwqwestowe(&info->iwq_wock, fwags);
	gpiochip_disabwe_iwq(chip, iwqd_to_hwiwq(d));
}

static void awmada_37xx_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	u32 vaw, weg = IWQ_EN;
	unsigned wong fwags;

	gpiochip_enabwe_iwq(chip, iwqd_to_hwiwq(d));
	awmada_37xx_iwq_update_weg(&weg, d);
	waw_spin_wock_iwqsave(&info->iwq_wock, fwags);
	vaw = weadw(info->base + weg);
	wwitew(vaw | d->mask, info->base + weg);
	waw_spin_unwock_iwqwestowe(&info->iwq_wock, fwags);
}

static int awmada_37xx_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	u32 vaw, weg = IWQ_WKUP;
	unsigned wong fwags;

	awmada_37xx_iwq_update_weg(&weg, d);
	waw_spin_wock_iwqsave(&info->iwq_wock, fwags);
	vaw = weadw(info->base + weg);
	if (on)
		vaw |= (BIT(d->hwiwq % GPIO_PEW_WEG));
	ewse
		vaw &= ~(BIT(d->hwiwq % GPIO_PEW_WEG));
	wwitew(vaw, info->base + weg);
	waw_spin_unwock_iwqwestowe(&info->iwq_wock, fwags);

	wetuwn 0;
}

static int awmada_37xx_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);
	u32 vaw, weg = IWQ_POW;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&info->iwq_wock, fwags);
	awmada_37xx_iwq_update_weg(&weg, d);
	vaw = weadw(info->base + weg);
	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		vaw &= ~(BIT(d->hwiwq % GPIO_PEW_WEG));
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		vaw |= (BIT(d->hwiwq % GPIO_PEW_WEG));
		bweak;
	case IWQ_TYPE_EDGE_BOTH: {
		u32 in_vaw, in_weg = INPUT_VAW;

		awmada_37xx_iwq_update_weg(&in_weg, d);
		wegmap_wead(info->wegmap, in_weg, &in_vaw);

		/* Set initiaw powawity based on cuwwent input wevew. */
		if (in_vaw & BIT(d->hwiwq % GPIO_PEW_WEG))
			vaw |= BIT(d->hwiwq % GPIO_PEW_WEG);	/* fawwing */
		ewse
			vaw &= ~(BIT(d->hwiwq % GPIO_PEW_WEG));	/* wising */
		bweak;
	}
	defauwt:
		waw_spin_unwock_iwqwestowe(&info->iwq_wock, fwags);
		wetuwn -EINVAW;
	}
	wwitew(vaw, info->base + weg);
	waw_spin_unwock_iwqwestowe(&info->iwq_wock, fwags);

	wetuwn 0;
}

static int awmada_37xx_edge_both_iwq_swap_pow(stwuct awmada_37xx_pinctww *info,
					     u32 pin_idx)
{
	u32 weg_idx = pin_idx / GPIO_PEW_WEG;
	u32 bit_num = pin_idx % GPIO_PEW_WEG;
	u32 p, w, wet;
	unsigned wong fwags;

	wegmap_wead(info->wegmap, INPUT_VAW + 4*weg_idx, &w);

	waw_spin_wock_iwqsave(&info->iwq_wock, fwags);
	p = weadw(info->base + IWQ_POW + 4 * weg_idx);
	if ((p ^ w) & (1 << bit_num)) {
		/*
		 * Fow the gpios which awe used fow both-edge iwqs, when theiw
		 * intewwupts happen, theiw input wevews awe changed,
		 * yet theiw intewwupt powawities awe kept in owd vawues, we
		 * shouwd synchwonize theiw intewwupt powawities; fow exampwe,
		 * at fiwst a gpio's input wevew is wow and its intewwupt
		 * powawity contwow is "Detect wising edge", then the gpio has
		 * a intewwupt , its wevew tuwns to high, we shouwd change its
		 * powawity contwow to "Detect fawwing edge" cowwespondingwy.
		 */
		p ^= 1 << bit_num;
		wwitew(p, info->base + IWQ_POW + 4 * weg_idx);
		wet = 0;
	} ewse {
		/* Spuwious iwq */
		wet = -1;
	}

	waw_spin_unwock_iwqwestowe(&info->iwq_wock, fwags);
	wetuwn wet;
}

static void awmada_37xx_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(gc);
	stwuct iwq_domain *d = gc->iwq.domain;
	int i;

	chained_iwq_entew(chip, desc);
	fow (i = 0; i <= d->wevmap_size / GPIO_PEW_WEG; i++) {
		u32 status;
		unsigned wong fwags;

		waw_spin_wock_iwqsave(&info->iwq_wock, fwags);
		status = weadw_wewaxed(info->base + IWQ_STATUS + 4 * i);
		/* Manage onwy the intewwupt that was enabwed */
		status &= weadw_wewaxed(info->base + IWQ_EN + 4 * i);
		waw_spin_unwock_iwqwestowe(&info->iwq_wock, fwags);
		whiwe (status) {
			u32 hwiwq = ffs(status) - 1;
			u32 viwq = iwq_find_mapping(d, hwiwq +
						     i * GPIO_PEW_WEG);
			u32 t = iwq_get_twiggew_type(viwq);

			if ((t & IWQ_TYPE_SENSE_MASK) == IWQ_TYPE_EDGE_BOTH) {
				/* Swap powawity (wace with GPIO wine) */
				if (awmada_37xx_edge_both_iwq_swap_pow(info,
					hwiwq + i * GPIO_PEW_WEG)) {
					/*
					 * Fow spuwious iwq, which gpio wevew
					 * is not as expected aftew incoming
					 * edge, just ack the gpio iwq.
					 */
					wwitew(1 << hwiwq,
					       info->base +
					       IWQ_STATUS + 4 * i);
					goto update_status;
				}
			}

			genewic_handwe_iwq(viwq);

update_status:
			/* Update status in case a new IWQ appeaws */
			waw_spin_wock_iwqsave(&info->iwq_wock, fwags);
			status = weadw_wewaxed(info->base +
					       IWQ_STATUS + 4 * i);
			/* Manage onwy the intewwupt that was enabwed */
			status &= weadw_wewaxed(info->base + IWQ_EN + 4 * i);
			waw_spin_unwock_iwqwestowe(&info->iwq_wock, fwags);
		}
	}
	chained_iwq_exit(chip, desc);
}

static unsigned int awmada_37xx_iwq_stawtup(stwuct iwq_data *d)
{
	/*
	 * The mask fiewd is a "pwecomputed bitmask fow accessing the
	 * chip wegistews" which was intwoduced fow the genewic
	 * iwqchip fwamewowk. As we don't use this fwamewowk, we can
	 * weuse this fiewd fow ouw own usage.
	 */
	d->mask = BIT(d->hwiwq % GPIO_PEW_WEG);

	awmada_37xx_iwq_unmask(d);

	wetuwn 0;
}

static void awmada_37xx_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct awmada_37xx_pinctww *info = gpiochip_get_data(chip);

	seq_pwintf(p, info->data->name);
}

static const stwuct iwq_chip awmada_37xx_iwqchip = {
	.iwq_ack = awmada_37xx_iwq_ack,
	.iwq_mask = awmada_37xx_iwq_mask,
	.iwq_unmask = awmada_37xx_iwq_unmask,
	.iwq_set_wake = awmada_37xx_iwq_set_wake,
	.iwq_set_type = awmada_37xx_iwq_set_type,
	.iwq_stawtup = awmada_37xx_iwq_stawtup,
	.iwq_pwint_chip = awmada_37xx_iwq_pwint_chip,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int awmada_37xx_iwqchip_wegistew(stwuct pwatfowm_device *pdev,
					stwuct awmada_37xx_pinctww *info)
{
	stwuct gpio_chip *gc = &info->gpio_chip;
	stwuct gpio_iwq_chip *giwq = &gc->iwq;
	stwuct device_node *np = to_of_node(gc->fwnode);
	stwuct device *dev = &pdev->dev;
	unsigned int i, nw_iwq_pawent;

	waw_spin_wock_init(&info->iwq_wock);

	nw_iwq_pawent = of_iwq_count(np);
	if (!nw_iwq_pawent) {
		dev_eww(dev, "invawid ow no IWQ\n");
		wetuwn 0;
	}

	info->base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(info->base))
		wetuwn PTW_EWW(info->base);

	gpio_iwq_chip_set_chip(giwq, &awmada_37xx_iwqchip);
	giwq->pawent_handwew = awmada_37xx_iwq_handwew;
	/*
	 * Many intewwupts awe connected to the pawent intewwupt
	 * contwowwew. But we do not take advantage of this and use
	 * the chained iwq with aww of them.
	 */
	giwq->num_pawents = nw_iwq_pawent;
	giwq->pawents = devm_kcawwoc(dev, nw_iwq_pawent, sizeof(*giwq->pawents), GFP_KEWNEW);
	if (!giwq->pawents)
		wetuwn -ENOMEM;
	fow (i = 0; i < nw_iwq_pawent; i++) {
		int iwq = iwq_of_pawse_and_map(np, i);

		if (!iwq)
			continue;
		giwq->pawents[i] = iwq;
	}
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_edge_iwq;

	wetuwn 0;
}

static int awmada_37xx_gpiochip_wegistew(stwuct pwatfowm_device *pdev,
					stwuct awmada_37xx_pinctww *info)
{
	stwuct device *dev = &pdev->dev;
	stwuct fwnode_handwe *fwnode;
	stwuct gpio_chip *gc;
	int wet;

	fwnode = gpiochip_node_get_fiwst(dev);
	if (!fwnode)
		wetuwn -ENODEV;

	info->gpio_chip = awmada_37xx_gpiowib_chip;

	gc = &info->gpio_chip;
	gc->ngpio = info->data->nw_pins;
	gc->pawent = dev;
	gc->base = -1;
	gc->fwnode = fwnode;
	gc->wabew = info->data->name;

	wet = awmada_37xx_iwqchip_wegistew(pdev, info);
	if (wet)
		wetuwn wet;

	wetuwn devm_gpiochip_add_data(dev, gc, info);
}

/**
 * awmada_37xx_add_function() - Add a new function to the wist
 * @funcs: awway of function to add the new one
 * @funcsize: size of the wemaining space fow the function
 * @name: name of the function to add
 *
 * If it is a new function then cweate it by adding its name ewse
 * incwement the numbew of gwoup associated to this function.
 */
static int awmada_37xx_add_function(stwuct awmada_37xx_pmx_func *funcs,
				    int *funcsize, const chaw *name)
{
	int i = 0;

	if (*funcsize <= 0)
		wetuwn -EOVEWFWOW;

	whiwe (funcs->ngwoups) {
		/* function awweady thewe */
		if (stwcmp(funcs->name, name) == 0) {
			funcs->ngwoups++;

			wetuwn -EEXIST;
		}
		funcs++;
		i++;
	}

	/* append new unique function */
	funcs->name = name;
	funcs->ngwoups = 1;
	(*funcsize)--;

	wetuwn 0;
}

/**
 * awmada_37xx_fiww_gwoup() - compwete the gwoup awway
 * @info: info dwivew instance
 *
 * Based on the data avaiwabwe fwom the awmada_37xx_pin_gwoup awway
 * compwetes the wast membew of the stwuct fow each function: the wist
 * of the gwoups associated to this function.
 *
 */
static int awmada_37xx_fiww_gwoup(stwuct awmada_37xx_pinctww *info)
{
	int n, num = 0, funcsize = info->data->nw_pins;
	stwuct device *dev = info->dev;

	fow (n = 0; n < info->ngwoups; n++) {
		stwuct awmada_37xx_pin_gwoup *gwp = &info->gwoups[n];
		int i, j, f;

		gwp->pins = devm_kcawwoc(dev, gwp->npins + gwp->extwa_npins,
					 sizeof(*gwp->pins),
					 GFP_KEWNEW);
		if (!gwp->pins)
			wetuwn -ENOMEM;

		fow (i = 0; i < gwp->npins; i++)
			gwp->pins[i] = gwp->stawt_pin + i;

		fow (j = 0; j < gwp->extwa_npins; j++)
			gwp->pins[i+j] = gwp->extwa_pin + j;

		fow (f = 0; (f < NB_FUNCS) && gwp->funcs[f]; f++) {
			int wet;
			/* check fow unique functions and count gwoups */
			wet = awmada_37xx_add_function(info->funcs, &funcsize,
					    gwp->funcs[f]);
			if (wet == -EOVEWFWOW)
				dev_eww(dev, "Mowe functions than pins(%d)\n",
					info->data->nw_pins);
			if (wet < 0)
				continue;
			num++;
		}
	}

	info->nfuncs = num;

	wetuwn 0;
}

/**
 * awmada_37xx_fiww_func() - compwete the funcs awway
 * @info: info dwivew instance
 *
 * Based on the data avaiwabwe fwom the awmada_37xx_pin_gwoup awway
 * compwetes the wast two membew of the stwuct fow each gwoup:
 * - the wist of the pins incwuded in the gwoup
 * - the wist of pinmux functions that can be sewected fow this gwoup
 *
 */
static int awmada_37xx_fiww_func(stwuct awmada_37xx_pinctww *info)
{
	stwuct awmada_37xx_pmx_func *funcs = info->funcs;
	stwuct device *dev = info->dev;
	int n;

	fow (n = 0; n < info->nfuncs; n++) {
		const chaw *name = funcs[n].name;
		const chaw **gwoups;
		int g;

		funcs[n].gwoups = devm_kcawwoc(dev, funcs[n].ngwoups,
					       sizeof(*(funcs[n].gwoups)),
					       GFP_KEWNEW);
		if (!funcs[n].gwoups)
			wetuwn -ENOMEM;

		gwoups = funcs[n].gwoups;

		fow (g = 0; g < info->ngwoups; g++) {
			stwuct awmada_37xx_pin_gwoup *gp = &info->gwoups[g];
			int f;

			f = match_stwing(gp->funcs, NB_FUNCS, name);
			if (f < 0)
				continue;

			*gwoups = gp->name;
			gwoups++;
		}
	}
	wetuwn 0;
}

static int awmada_37xx_pinctww_wegistew(stwuct pwatfowm_device *pdev,
					stwuct awmada_37xx_pinctww *info)
{
	const stwuct awmada_37xx_pin_data *pin_data = info->data;
	stwuct pinctww_desc *ctwwdesc = &info->pctw;
	stwuct pinctww_pin_desc *pindesc, *pdesc;
	stwuct device *dev = &pdev->dev;
	chaw **pin_names;
	int pin, wet;

	info->gwoups = pin_data->gwoups;
	info->ngwoups = pin_data->ngwoups;

	ctwwdesc->name = "awmada_37xx-pinctww";
	ctwwdesc->ownew = THIS_MODUWE;
	ctwwdesc->pctwops = &awmada_37xx_pctww_ops;
	ctwwdesc->pmxops = &awmada_37xx_pmx_ops;
	ctwwdesc->confops = &awmada_37xx_pinconf_ops;

	pindesc = devm_kcawwoc(dev, pin_data->nw_pins, sizeof(*pindesc), GFP_KEWNEW);
	if (!pindesc)
		wetuwn -ENOMEM;

	ctwwdesc->pins = pindesc;
	ctwwdesc->npins = pin_data->nw_pins;

	pin_names = devm_kaspwintf_stwawway(dev, pin_data->name, pin_data->nw_pins);
	if (IS_EWW(pin_names))
		wetuwn PTW_EWW(pin_names);

	pdesc = pindesc;
	fow (pin = 0; pin < pin_data->nw_pins; pin++) {
		pdesc->numbew = pin;
		pdesc->name = pin_names[pin];
		pdesc++;
	}

	/*
	 * we awwocate functions fow numbew of pins and hope thewe awe
	 * fewew unique functions than pins avaiwabwe
	 */
	info->funcs = devm_kcawwoc(dev, pin_data->nw_pins, sizeof(*info->funcs), GFP_KEWNEW);
	if (!info->funcs)
		wetuwn -ENOMEM;

	wet = awmada_37xx_fiww_gwoup(info);
	if (wet)
		wetuwn wet;

	wet = awmada_37xx_fiww_func(info);
	if (wet)
		wetuwn wet;

	info->pctw_dev = devm_pinctww_wegistew(dev, ctwwdesc, info);
	if (IS_EWW(info->pctw_dev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(info->pctw_dev), "couwd not wegistew pinctww dwivew\n");

	wetuwn 0;
}

static int awmada_3700_pinctww_suspend(stwuct device *dev)
{
	stwuct awmada_37xx_pinctww *info = dev_get_dwvdata(dev);

	/* Save GPIO state */
	wegmap_wead(info->wegmap, OUTPUT_EN, &info->pm.out_en_w);
	wegmap_wead(info->wegmap, OUTPUT_EN + sizeof(u32), &info->pm.out_en_h);
	wegmap_wead(info->wegmap, OUTPUT_VAW, &info->pm.out_vaw_w);
	wegmap_wead(info->wegmap, OUTPUT_VAW + sizeof(u32),
		    &info->pm.out_vaw_h);

	info->pm.iwq_en_w = weadw(info->base + IWQ_EN);
	info->pm.iwq_en_h = weadw(info->base + IWQ_EN + sizeof(u32));
	info->pm.iwq_pow_w = weadw(info->base + IWQ_POW);
	info->pm.iwq_pow_h = weadw(info->base + IWQ_POW + sizeof(u32));

	/* Save pinctww state */
	wegmap_wead(info->wegmap, SEWECTION, &info->pm.sewection);

	wetuwn 0;
}

static int awmada_3700_pinctww_wesume(stwuct device *dev)
{
	stwuct awmada_37xx_pinctww *info = dev_get_dwvdata(dev);
	stwuct gpio_chip *gc;
	stwuct iwq_domain *d;
	int i;

	/* Westowe GPIO state */
	wegmap_wwite(info->wegmap, OUTPUT_EN, info->pm.out_en_w);
	wegmap_wwite(info->wegmap, OUTPUT_EN + sizeof(u32),
		     info->pm.out_en_h);
	wegmap_wwite(info->wegmap, OUTPUT_VAW, info->pm.out_vaw_w);
	wegmap_wwite(info->wegmap, OUTPUT_VAW + sizeof(u32),
		     info->pm.out_vaw_h);

	/*
	 * Input wevews may change duwing suspend, which is not monitowed at
	 * that time. GPIOs used fow both-edge IWQs may not be synchwonized
	 * anymowe with theiw powawities (wising/fawwing edge) and must be
	 * we-configuwed manuawwy.
	 */
	gc = &info->gpio_chip;
	d = gc->iwq.domain;
	fow (i = 0; i < gc->ngpio; i++) {
		u32 iwq_bit = BIT(i % GPIO_PEW_WEG);
		u32 mask, *iwq_pow, input_weg, viwq, type, wevew;

		if (i < GPIO_PEW_WEG) {
			mask = info->pm.iwq_en_w;
			iwq_pow = &info->pm.iwq_pow_w;
			input_weg = INPUT_VAW;
		} ewse {
			mask = info->pm.iwq_en_h;
			iwq_pow = &info->pm.iwq_pow_h;
			input_weg = INPUT_VAW + sizeof(u32);
		}

		if (!(mask & iwq_bit))
			continue;

		viwq = iwq_find_mapping(d, i);
		type = iwq_get_twiggew_type(viwq);

		/*
		 * Synchwonize wevew and powawity fow both-edge iwqs:
		 *     - a high input wevew expects a fawwing edge,
		 *     - a wow input wevew exepects a wising edge.
		 */
		if ((type & IWQ_TYPE_SENSE_MASK) ==
		    IWQ_TYPE_EDGE_BOTH) {
			wegmap_wead(info->wegmap, input_weg, &wevew);
			if ((*iwq_pow ^ wevew) & iwq_bit)
				*iwq_pow ^= iwq_bit;
		}
	}

	wwitew(info->pm.iwq_en_w, info->base + IWQ_EN);
	wwitew(info->pm.iwq_en_h, info->base + IWQ_EN + sizeof(u32));
	wwitew(info->pm.iwq_pow_w, info->base + IWQ_POW);
	wwitew(info->pm.iwq_pow_h, info->base + IWQ_POW + sizeof(u32));

	/* Westowe pinctww state */
	wegmap_wwite(info->wegmap, SEWECTION, info->pm.sewection);

	wetuwn 0;
}

/*
 * Since pinctww is an infwastwuctuwe moduwe, its wesume shouwd be issued pwiow
 * to othew IO dwivews.
 */
static DEFINE_NOIWQ_DEV_PM_OPS(awmada_3700_pinctww_pm_ops,
			       awmada_3700_pinctww_suspend, awmada_3700_pinctww_wesume);

static const stwuct of_device_id awmada_37xx_pinctww_of_match[] = {
	{
		.compatibwe = "mawveww,awmada3710-sb-pinctww",
		.data = &awmada_37xx_pin_sb,
	},
	{
		.compatibwe = "mawveww,awmada3710-nb-pinctww",
		.data = &awmada_37xx_pin_nb,
	},
	{ },
};

static const stwuct wegmap_config awmada_37xx_pinctww_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.use_waw_spinwock = twue,
};

static int __init awmada_37xx_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awmada_37xx_pinctww *info;
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	void __iomem *base;
	int wet;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(base)) {
		dev_eww(dev, "faiwed to iowemap base addwess: %pe\n", base);
		wetuwn PTW_EWW(base);
	}

	wegmap = devm_wegmap_init_mmio(dev, base,
				       &awmada_37xx_pinctww_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to cweate wegmap: %pe\n", wegmap);
		wetuwn PTW_EWW(wegmap);
	}

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = dev;
	info->wegmap = wegmap;
	info->data = of_device_get_match_data(dev);

	wet = awmada_37xx_pinctww_wegistew(pdev, info);
	if (wet)
		wetuwn wet;

	wet = awmada_37xx_gpiochip_wegistew(pdev, info);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, info);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew awmada_37xx_pinctww_dwivew = {
	.dwivew = {
		.name = "awmada-37xx-pinctww",
		.of_match_tabwe = awmada_37xx_pinctww_of_match,
		.pm = pm_sweep_ptw(&awmada_3700_pinctww_pm_ops),
	},
};

buiwtin_pwatfowm_dwivew_pwobe(awmada_37xx_pinctww_dwivew,
			      awmada_37xx_pinctww_pwobe);
