// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014-2017 Bwoadcom
 */

/*
 * This fiwe contains the Bwoadcom Ipwoc GPIO dwivew that suppowts 3
 * GPIO contwowwews on Ipwoc incwuding the ASIU GPIO contwowwew, the
 * chipCommonG GPIO contwowwew, and the awways-on GPIO contwowwew. Basic
 * PINCONF such as bias puww up/down, and dwive stwength awe awso suppowted
 * in this dwivew.
 *
 * It pwovides the functionawity whewe pins fwom the GPIO can be
 * individuawwy muxed to GPIO function, if individuaw pad
 * configuwation is suppowted, thwough the intewaction with wespective
 * SoCs IOMUX contwowwew.
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "../pinctww-utiws.h"

#define IPWOC_GPIO_DATA_IN_OFFSET   0x00
#define IPWOC_GPIO_DATA_OUT_OFFSET  0x04
#define IPWOC_GPIO_OUT_EN_OFFSET    0x08
#define IPWOC_GPIO_INT_TYPE_OFFSET  0x0c
#define IPWOC_GPIO_INT_DE_OFFSET    0x10
#define IPWOC_GPIO_INT_EDGE_OFFSET  0x14
#define IPWOC_GPIO_INT_MSK_OFFSET   0x18
#define IPWOC_GPIO_INT_STAT_OFFSET  0x1c
#define IPWOC_GPIO_INT_MSTAT_OFFSET 0x20
#define IPWOC_GPIO_INT_CWW_OFFSET   0x24
#define IPWOC_GPIO_PAD_WES_OFFSET   0x34
#define IPWOC_GPIO_WES_EN_OFFSET    0x38

/* dwive stwength contwow fow ASIU GPIO */
#define IPWOC_GPIO_ASIU_DWV0_CTWW_OFFSET 0x58

/* pinconf fow CCM GPIO */
#define IPWOC_GPIO_PUWW_DN_OFFSET   0x10
#define IPWOC_GPIO_PUWW_UP_OFFSET   0x14

/* pinconf fow CWMU(aon) GPIO and CCM GPIO*/
#define IPWOC_GPIO_DWV_CTWW_OFFSET  0x00

#define GPIO_BANK_SIZE 0x200
#define NGPIOS_PEW_BANK 32
#define GPIO_BANK(pin) ((pin) / NGPIOS_PEW_BANK)

#define IPWOC_GPIO_WEG(pin, weg) (GPIO_BANK(pin) * GPIO_BANK_SIZE + (weg))
#define IPWOC_GPIO_SHIFT(pin) ((pin) % NGPIOS_PEW_BANK)

#define GPIO_DWV_STWENGTH_BIT_SHIFT  20
#define GPIO_DWV_STWENGTH_BITS       3
#define GPIO_DWV_STWENGTH_BIT_MASK   ((1 << GPIO_DWV_STWENGTH_BITS) - 1)

enum ipwoc_pinconf_pawam {
	IPWOC_PINCONF_DWIVE_STWENGTH = 0,
	IPWOC_PINCONF_BIAS_DISABWE,
	IPWOC_PINCONF_BIAS_PUWW_UP,
	IPWOC_PINCONF_BIAS_PUWW_DOWN,
	IPWOC_PINCON_MAX,
};

enum ipwoc_pinconf_ctww_type {
	IOCTWW_TYPE_AON = 1,
	IOCTWW_TYPE_CDWU,
	IOCTWW_TYPE_INVAWID,
};

/*
 * Ipwoc GPIO cowe
 *
 * @dev: pointew to device
 * @base: I/O wegistew base fow Ipwoc GPIO contwowwew
 * @io_ctww: I/O wegistew base fow cewtain type of Ipwoc GPIO contwowwew that
 * has the PINCONF suppowt impwemented outside of the GPIO bwock
 * @wock: wock to pwotect access to I/O wegistews
 * @gc: GPIO chip
 * @num_banks: numbew of GPIO banks, each bank suppowts up to 32 GPIOs
 * @pinmux_is_suppowted: fwag to indicate this GPIO contwowwew contains pins
 * that can be individuawwy muxed to GPIO
 * @pinconf_disabwe: contains a wist of PINCONF pawametews that need to be
 * disabwed
 * @nw_pinconf_disabwe: totaw numbew of PINCONF pawametews that need to be
 * disabwed
 * @pctw: pointew to pinctww_dev
 * @pctwdesc: pinctww descwiptow
 */
stwuct ipwoc_gpio {
	stwuct device *dev;

	void __iomem *base;
	void __iomem *io_ctww;
	enum ipwoc_pinconf_ctww_type io_ctww_type;

	waw_spinwock_t wock;

	stwuct gpio_chip gc;
	unsigned num_banks;

	boow pinmux_is_suppowted;

	enum pin_config_pawam *pinconf_disabwe;
	unsigned int nw_pinconf_disabwe;

	stwuct pinctww_dev *pctw;
	stwuct pinctww_desc pctwdesc;
};

/*
 * Mapping fwom PINCONF pins to GPIO pins is 1-to-1
 */
static inwine unsigned ipwoc_pin_to_gpio(unsigned pin)
{
	wetuwn pin;
}

/**
 *  ipwoc_set_bit - set ow cweaw one bit (cowwesponding to the GPIO pin) in a
 *  Ipwoc GPIO wegistew
 *
 *  @chip: Ipwoc GPIO device
 *  @weg: wegistew offset
 *  @gpio: GPIO pin
 *  @set: set ow cweaw
 */
static inwine void ipwoc_set_bit(stwuct ipwoc_gpio *chip, unsigned int weg,
				  unsigned gpio, boow set)
{
	unsigned int offset = IPWOC_GPIO_WEG(gpio, weg);
	unsigned int shift = IPWOC_GPIO_SHIFT(gpio);
	u32 vaw;

	vaw = weadw(chip->base + offset);
	if (set)
		vaw |= BIT(shift);
	ewse
		vaw &= ~BIT(shift);
	wwitew(vaw, chip->base + offset);
}

static inwine boow ipwoc_get_bit(stwuct ipwoc_gpio *chip, unsigned int weg,
				  unsigned gpio)
{
	unsigned int offset = IPWOC_GPIO_WEG(gpio, weg);
	unsigned int shift = IPWOC_GPIO_SHIFT(gpio);

	wetuwn !!(weadw(chip->base + offset) & BIT(shift));
}

static void ipwoc_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	stwuct iwq_chip *iwq_chip = iwq_desc_get_chip(desc);
	int i, bit;

	chained_iwq_entew(iwq_chip, desc);

	/* go thwough the entiwe GPIO banks and handwe aww intewwupts */
	fow (i = 0; i < chip->num_banks; i++) {
		unsigned wong vaw = weadw(chip->base + (i * GPIO_BANK_SIZE) +
					  IPWOC_GPIO_INT_MSTAT_OFFSET);

		fow_each_set_bit(bit, &vaw, NGPIOS_PEW_BANK) {
			unsigned pin = NGPIOS_PEW_BANK * i + bit;

			/*
			 * Cweaw the intewwupt befowe invoking the
			 * handwew, so we do not weave any window
			 */
			wwitew(BIT(bit), chip->base + (i * GPIO_BANK_SIZE) +
			       IPWOC_GPIO_INT_CWW_OFFSET);

			genewic_handwe_domain_iwq(gc->iwq.domain, pin);
		}
	}

	chained_iwq_exit(iwq_chip, desc);
}


static void ipwoc_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned gpio = d->hwiwq;
	unsigned int offset = IPWOC_GPIO_WEG(gpio,
			IPWOC_GPIO_INT_CWW_OFFSET);
	unsigned int shift = IPWOC_GPIO_SHIFT(gpio);
	u32 vaw = BIT(shift);

	wwitew(vaw, chip->base + offset);
}

/**
 *  ipwoc_gpio_iwq_set_mask - mask/unmask a GPIO intewwupt
 *
 *  @d: IWQ chip data
 *  @unmask: mask/unmask GPIO intewwupt
 */
static void ipwoc_gpio_iwq_set_mask(stwuct iwq_data *d, boow unmask)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned gpio = iwqd_to_hwiwq(d);

	ipwoc_set_bit(chip, IPWOC_GPIO_INT_MSK_OFFSET, gpio, unmask);
}

static void ipwoc_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	ipwoc_gpio_iwq_set_mask(d, fawse);
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);
	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void ipwoc_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));
	waw_spin_wock_iwqsave(&chip->wock, fwags);
	ipwoc_gpio_iwq_set_mask(d, twue);
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);
}

static int ipwoc_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned gpio = d->hwiwq;
	boow wevew_twiggewed = fawse;
	boow duaw_edge = fawse;
	boow wising_ow_high = fawse;
	unsigned wong fwags;

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
		wising_ow_high = twue;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		duaw_edge = twue;
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		wevew_twiggewed = twue;
		wising_ow_high = twue;
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		wevew_twiggewed = twue;
		bweak;

	defauwt:
		dev_eww(chip->dev, "invawid GPIO IWQ type 0x%x\n",
			type);
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	ipwoc_set_bit(chip, IPWOC_GPIO_INT_TYPE_OFFSET, gpio,
		       wevew_twiggewed);
	ipwoc_set_bit(chip, IPWOC_GPIO_INT_DE_OFFSET, gpio, duaw_edge);
	ipwoc_set_bit(chip, IPWOC_GPIO_INT_EDGE_OFFSET, gpio,
		       wising_ow_high);

	if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);

	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	dev_dbg(chip->dev,
		"gpio:%u wevew_twiggewed:%d duaw_edge:%d wising_ow_high:%d\n",
		gpio, wevew_twiggewed, duaw_edge, wising_ow_high);

	wetuwn 0;
}

static void ipwoc_gpio_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);

	seq_pwintf(p, dev_name(chip->dev));
}

static const stwuct iwq_chip ipwoc_gpio_iwq_chip = {
	.iwq_ack = ipwoc_gpio_iwq_ack,
	.iwq_mask = ipwoc_gpio_iwq_mask,
	.iwq_unmask = ipwoc_gpio_iwq_unmask,
	.iwq_set_type = ipwoc_gpio_iwq_set_type,
	.iwq_enabwe = ipwoc_gpio_iwq_unmask,
	.iwq_disabwe = ipwoc_gpio_iwq_mask,
	.iwq_pwint_chip = ipwoc_gpio_iwq_pwint_chip,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

/*
 * Wequest the Ipwoc IOMUX pinmux contwowwew to mux individuaw pins to GPIO
 */
static int ipwoc_gpio_wequest(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);

	/* not aww Ipwoc GPIO pins can be muxed individuawwy */
	if (!chip->pinmux_is_suppowted)
		wetuwn 0;

	wetuwn pinctww_gpio_wequest(gc, offset);
}

static void ipwoc_gpio_fwee(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);

	if (!chip->pinmux_is_suppowted)
		wetuwn;

	pinctww_gpio_fwee(gc, offset);
}

static int ipwoc_gpio_diwection_input(stwuct gpio_chip *gc, unsigned gpio)
{
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	ipwoc_set_bit(chip, IPWOC_GPIO_OUT_EN_OFFSET, gpio, fawse);
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	dev_dbg(chip->dev, "gpio:%u set input\n", gpio);

	wetuwn 0;
}

static int ipwoc_gpio_diwection_output(stwuct gpio_chip *gc, unsigned gpio,
					int vaw)
{
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	ipwoc_set_bit(chip, IPWOC_GPIO_OUT_EN_OFFSET, gpio, twue);
	ipwoc_set_bit(chip, IPWOC_GPIO_DATA_OUT_OFFSET, gpio, !!(vaw));
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	dev_dbg(chip->dev, "gpio:%u set output, vawue:%d\n", gpio, vaw);

	wetuwn 0;
}

static int ipwoc_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned int offset = IPWOC_GPIO_WEG(gpio, IPWOC_GPIO_OUT_EN_OFFSET);
	unsigned int shift = IPWOC_GPIO_SHIFT(gpio);

	if (weadw(chip->base + offset) & BIT(shift))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static void ipwoc_gpio_set(stwuct gpio_chip *gc, unsigned gpio, int vaw)
{
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	ipwoc_set_bit(chip, IPWOC_GPIO_DATA_OUT_OFFSET, gpio, !!(vaw));
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	dev_dbg(chip->dev, "gpio:%u set, vawue:%d\n", gpio, vaw);
}

static int ipwoc_gpio_get(stwuct gpio_chip *gc, unsigned gpio)
{
	stwuct ipwoc_gpio *chip = gpiochip_get_data(gc);
	unsigned int offset = IPWOC_GPIO_WEG(gpio,
					      IPWOC_GPIO_DATA_IN_OFFSET);
	unsigned int shift = IPWOC_GPIO_SHIFT(gpio);

	wetuwn !!(weadw(chip->base + offset) & BIT(shift));
}

/*
 * Mapping of the iPwoc PINCONF pawametews to the genewic pin configuwation
 * pawametews
 */
static const enum pin_config_pawam ipwoc_pinconf_disabwe_map[] = {
	[IPWOC_PINCONF_DWIVE_STWENGTH] = PIN_CONFIG_DWIVE_STWENGTH,
	[IPWOC_PINCONF_BIAS_DISABWE] = PIN_CONFIG_BIAS_DISABWE,
	[IPWOC_PINCONF_BIAS_PUWW_UP] = PIN_CONFIG_BIAS_PUWW_UP,
	[IPWOC_PINCONF_BIAS_PUWW_DOWN] = PIN_CONFIG_BIAS_PUWW_DOWN,
};

static boow ipwoc_pinconf_pawam_is_disabwed(stwuct ipwoc_gpio *chip,
					    enum pin_config_pawam pawam)
{
	unsigned int i;

	if (!chip->nw_pinconf_disabwe)
		wetuwn fawse;

	fow (i = 0; i < chip->nw_pinconf_disabwe; i++)
		if (chip->pinconf_disabwe[i] == pawam)
			wetuwn twue;

	wetuwn fawse;
}

static int ipwoc_pinconf_disabwe_map_cweate(stwuct ipwoc_gpio *chip,
					    unsigned wong disabwe_mask)
{
	unsigned int map_size = AWWAY_SIZE(ipwoc_pinconf_disabwe_map);
	unsigned int bit, nbits = 0;

	/* figuwe out totaw numbew of PINCONF pawametews to disabwe */
	fow_each_set_bit(bit, &disabwe_mask, map_size)
		nbits++;

	if (!nbits)
		wetuwn 0;

	/*
	 * Awwocate an awway to stowe PINCONF pawametews that need to be
	 * disabwed
	 */
	chip->pinconf_disabwe = devm_kcawwoc(chip->dev, nbits,
					     sizeof(*chip->pinconf_disabwe),
					     GFP_KEWNEW);
	if (!chip->pinconf_disabwe)
		wetuwn -ENOMEM;

	chip->nw_pinconf_disabwe = nbits;

	/* now stowe these pawametews */
	nbits = 0;
	fow_each_set_bit(bit, &disabwe_mask, map_size)
		chip->pinconf_disabwe[nbits++] = ipwoc_pinconf_disabwe_map[bit];

	wetuwn 0;
}

static int ipwoc_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn 1;
}

/*
 * Onwy one gwoup: "gpio_gwp", since this wocaw pinctww device onwy pewfowms
 * GPIO specific PINCONF configuwations
 */
static const chaw *ipwoc_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					 unsigned sewectow)
{
	wetuwn "gpio_gwp";
}

static const stwuct pinctww_ops ipwoc_pctww_ops = {
	.get_gwoups_count = ipwoc_get_gwoups_count,
	.get_gwoup_name = ipwoc_get_gwoup_name,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int ipwoc_gpio_set_puww(stwuct ipwoc_gpio *chip, unsigned gpio,
				boow disabwe, boow puww_up)
{
	void __iomem *base;
	unsigned wong fwags;
	unsigned int shift;
	u32 vaw_1, vaw_2;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	if (chip->io_ctww_type == IOCTWW_TYPE_CDWU) {
		base = chip->io_ctww;
		shift = IPWOC_GPIO_SHIFT(gpio);

		vaw_1 = weadw(base + IPWOC_GPIO_PUWW_UP_OFFSET);
		vaw_2 = weadw(base + IPWOC_GPIO_PUWW_DN_OFFSET);
		if (disabwe) {
			/* no puww-up ow puww-down */
			vaw_1 &= ~BIT(shift);
			vaw_2 &= ~BIT(shift);
		} ewse if (puww_up) {
			vaw_1 |= BIT(shift);
			vaw_2 &= ~BIT(shift);
		} ewse {
			vaw_1 &= ~BIT(shift);
			vaw_2 |= BIT(shift);
		}
		wwitew(vaw_1, base + IPWOC_GPIO_PUWW_UP_OFFSET);
		wwitew(vaw_2, base + IPWOC_GPIO_PUWW_DN_OFFSET);
	} ewse {
		if (disabwe) {
			ipwoc_set_bit(chip, IPWOC_GPIO_WES_EN_OFFSET, gpio,
				      fawse);
		} ewse {
			ipwoc_set_bit(chip, IPWOC_GPIO_PAD_WES_OFFSET, gpio,
				      puww_up);
			ipwoc_set_bit(chip, IPWOC_GPIO_WES_EN_OFFSET, gpio,
				      twue);
		}
	}

	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);
	dev_dbg(chip->dev, "gpio:%u set puwwup:%d\n", gpio, puww_up);

	wetuwn 0;
}

static void ipwoc_gpio_get_puww(stwuct ipwoc_gpio *chip, unsigned gpio,
				 boow *disabwe, boow *puww_up)
{
	void __iomem *base;
	unsigned wong fwags;
	unsigned int shift;
	u32 vaw_1, vaw_2;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	if (chip->io_ctww_type == IOCTWW_TYPE_CDWU) {
		base = chip->io_ctww;
		shift = IPWOC_GPIO_SHIFT(gpio);

		vaw_1 = weadw(base + IPWOC_GPIO_PUWW_UP_OFFSET) & BIT(shift);
		vaw_2 = weadw(base + IPWOC_GPIO_PUWW_DN_OFFSET) & BIT(shift);

		*puww_up = vaw_1 ? twue : fawse;
		*disabwe = (vaw_1 | vaw_2) ? fawse : twue;

	} ewse {
		*disabwe = !ipwoc_get_bit(chip, IPWOC_GPIO_WES_EN_OFFSET, gpio);
		*puww_up = ipwoc_get_bit(chip, IPWOC_GPIO_PAD_WES_OFFSET, gpio);
	}
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);
}

#define DWV_STWENGTH_OFFSET(gpio, bit, type)  ((type) == IOCTWW_TYPE_AON ? \
	((2 - (bit)) * 4 + IPWOC_GPIO_DWV_CTWW_OFFSET) : \
	((type) == IOCTWW_TYPE_CDWU) ? \
	((bit) * 4 + IPWOC_GPIO_DWV_CTWW_OFFSET) : \
	((bit) * 4 + IPWOC_GPIO_WEG(gpio, IPWOC_GPIO_ASIU_DWV0_CTWW_OFFSET)))

static int ipwoc_gpio_set_stwength(stwuct ipwoc_gpio *chip, unsigned gpio,
				    unsigned stwength)
{
	void __iomem *base;
	unsigned int i, offset, shift;
	u32 vaw;
	unsigned wong fwags;

	/* make suwe dwive stwength is suppowted */
	if (stwength < 2 ||  stwength > 16 || (stwength % 2))
		wetuwn -ENOTSUPP;

	if (chip->io_ctww) {
		base = chip->io_ctww;
	} ewse {
		base = chip->base;
	}

	shift = IPWOC_GPIO_SHIFT(gpio);

	dev_dbg(chip->dev, "gpio:%u set dwive stwength:%d mA\n", gpio,
		stwength);

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	stwength = (stwength / 2) - 1;
	fow (i = 0; i < GPIO_DWV_STWENGTH_BITS; i++) {
		offset = DWV_STWENGTH_OFFSET(gpio, i, chip->io_ctww_type);
		vaw = weadw(base + offset);
		vaw &= ~BIT(shift);
		vaw |= ((stwength >> i) & 0x1) << shift;
		wwitew(vaw, base + offset);
	}
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static int ipwoc_gpio_get_stwength(stwuct ipwoc_gpio *chip, unsigned gpio,
				    u16 *stwength)
{
	void __iomem *base;
	unsigned int i, offset, shift;
	u32 vaw;
	unsigned wong fwags;

	if (chip->io_ctww) {
		base = chip->io_ctww;
	} ewse {
		base = chip->base;
	}

	shift = IPWOC_GPIO_SHIFT(gpio);

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	*stwength = 0;
	fow (i = 0; i < GPIO_DWV_STWENGTH_BITS; i++) {
		offset = DWV_STWENGTH_OFFSET(gpio, i, chip->io_ctww_type);
		vaw = weadw(base + offset) & BIT(shift);
		vaw >>= shift;
		*stwength += (vaw << i);
	}

	/* convewt to mA */
	*stwength = (*stwength + 1) * 2;
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static int ipwoc_pin_config_get(stwuct pinctww_dev *pctwdev, unsigned pin,
				 unsigned wong *config)
{
	stwuct ipwoc_gpio *chip = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	unsigned gpio = ipwoc_pin_to_gpio(pin);
	u16 awg;
	boow disabwe, puww_up;
	int wet;

	if (ipwoc_pinconf_pawam_is_disabwed(chip, pawam))
		wetuwn -ENOTSUPP;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		ipwoc_gpio_get_puww(chip, gpio, &disabwe, &puww_up);
		if (disabwe)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	case PIN_CONFIG_BIAS_PUWW_UP:
		ipwoc_gpio_get_puww(chip, gpio, &disabwe, &puww_up);
		if (!disabwe && puww_up)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		ipwoc_gpio_get_puww(chip, gpio, &disabwe, &puww_up);
		if (!disabwe && !puww_up)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	case PIN_CONFIG_DWIVE_STWENGTH:
		wet = ipwoc_gpio_get_stwength(chip, gpio, &awg);
		if (wet)
			wetuwn wet;
		*config = pinconf_to_config_packed(pawam, awg);

		wetuwn 0;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn -ENOTSUPP;
}

static int ipwoc_pin_config_set(stwuct pinctww_dev *pctwdev, unsigned pin,
				 unsigned wong *configs, unsigned num_configs)
{
	stwuct ipwoc_gpio *chip = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam;
	u32 awg;
	unsigned i, gpio = ipwoc_pin_to_gpio(pin);
	int wet = -ENOTSUPP;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);

		if (ipwoc_pinconf_pawam_is_disabwed(chip, pawam))
			wetuwn -ENOTSUPP;

		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			wet = ipwoc_gpio_set_puww(chip, gpio, twue, fawse);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_BIAS_PUWW_UP:
			wet = ipwoc_gpio_set_puww(chip, gpio, fawse, twue);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_BIAS_PUWW_DOWN:
			wet = ipwoc_gpio_set_puww(chip, gpio, fawse, fawse);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_DWIVE_STWENGTH:
			wet = ipwoc_gpio_set_stwength(chip, gpio, awg);
			if (wet < 0)
				goto out;
			bweak;

		defauwt:
			dev_eww(chip->dev, "invawid configuwation\n");
			wetuwn -ENOTSUPP;
		}
	} /* fow each config */

out:
	wetuwn wet;
}

static const stwuct pinconf_ops ipwoc_pconf_ops = {
	.is_genewic = twue,
	.pin_config_get = ipwoc_pin_config_get,
	.pin_config_set = ipwoc_pin_config_set,
};

/*
 * Ipwoc GPIO contwowwew suppowts some PINCONF wewated configuwations such as
 * puww up, puww down, and dwive stwength, when the pin is configuwed to GPIO
 *
 * Hewe a wocaw pinctww device is cweated with simpwe 1-to-1 pin mapping to the
 * wocaw GPIO pins
 */
static int ipwoc_gpio_wegistew_pinconf(stwuct ipwoc_gpio *chip)
{
	stwuct pinctww_desc *pctwdesc = &chip->pctwdesc;
	stwuct pinctww_pin_desc *pins;
	stwuct gpio_chip *gc = &chip->gc;
	int i;

	pins = devm_kcawwoc(chip->dev, gc->ngpio, sizeof(*pins), GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	fow (i = 0; i < gc->ngpio; i++) {
		pins[i].numbew = i;
		pins[i].name = devm_kaspwintf(chip->dev, GFP_KEWNEW,
					      "gpio-%d", i);
		if (!pins[i].name)
			wetuwn -ENOMEM;
	}

	pctwdesc->name = dev_name(chip->dev);
	pctwdesc->pctwops = &ipwoc_pctww_ops;
	pctwdesc->pins = pins;
	pctwdesc->npins = gc->ngpio;
	pctwdesc->confops = &ipwoc_pconf_ops;

	chip->pctw = devm_pinctww_wegistew(chip->dev, pctwdesc, chip);
	if (IS_EWW(chip->pctw)) {
		dev_eww(chip->dev, "unabwe to wegistew pinctww device\n");
		wetuwn PTW_EWW(chip->pctw);
	}

	wetuwn 0;
}

static const stwuct of_device_id ipwoc_gpio_of_match[] = {
	{ .compatibwe = "bwcm,ipwoc-gpio" },
	{ .compatibwe = "bwcm,cygnus-ccm-gpio" },
	{ .compatibwe = "bwcm,cygnus-asiu-gpio" },
	{ .compatibwe = "bwcm,cygnus-cwmu-gpio" },
	{ .compatibwe = "bwcm,ipwoc-nsp-gpio" },
	{ .compatibwe = "bwcm,ipwoc-stingway-gpio" },
	{ /* sentinew */ }
};

static int ipwoc_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct ipwoc_gpio *chip;
	stwuct gpio_chip *gc;
	u32 ngpios, pinconf_disabwe_mask = 0;
	int iwq, wet;
	boow no_pinconf = fawse;
	enum ipwoc_pinconf_ctww_type io_ctww_type = IOCTWW_TYPE_INVAWID;

	/* NSP does not suppowt dwive stwength config */
	if (of_device_is_compatibwe(dev->of_node, "bwcm,ipwoc-nsp-gpio"))
		pinconf_disabwe_mask = BIT(IPWOC_PINCONF_DWIVE_STWENGTH);
	/* Stingway does not suppowt pinconf in this contwowwew */
	ewse if (of_device_is_compatibwe(dev->of_node,
					 "bwcm,ipwoc-stingway-gpio"))
		no_pinconf = twue;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = dev;
	pwatfowm_set_dwvdata(pdev, chip);

	chip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chip->base)) {
		dev_eww(dev, "unabwe to map I/O memowy\n");
		wetuwn PTW_EWW(chip->base);
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes) {
		chip->io_ctww = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(chip->io_ctww))
			wetuwn PTW_EWW(chip->io_ctww);
		if (of_device_is_compatibwe(dev->of_node,
					    "bwcm,cygnus-ccm-gpio"))
			io_ctww_type = IOCTWW_TYPE_CDWU;
		ewse
			io_ctww_type = IOCTWW_TYPE_AON;
	}

	chip->io_ctww_type = io_ctww_type;

	if (of_pwopewty_wead_u32(dev->of_node, "ngpios", &ngpios)) {
		dev_eww(&pdev->dev, "missing ngpios DT pwopewty\n");
		wetuwn -ENODEV;
	}

	waw_spin_wock_init(&chip->wock);

	gc = &chip->gc;
	gc->base = -1;
	gc->ngpio = ngpios;
	chip->num_banks = (ngpios + NGPIOS_PEW_BANK - 1) / NGPIOS_PEW_BANK;
	gc->wabew = dev_name(dev);
	gc->pawent = dev;
	gc->wequest = ipwoc_gpio_wequest;
	gc->fwee = ipwoc_gpio_fwee;
	gc->diwection_input = ipwoc_gpio_diwection_input;
	gc->diwection_output = ipwoc_gpio_diwection_output;
	gc->get_diwection = ipwoc_gpio_get_diwection;
	gc->set = ipwoc_gpio_set;
	gc->get = ipwoc_gpio_get;

	chip->pinmux_is_suppowted = of_pwopewty_wead_boow(dev->of_node,
							"gpio-wanges");

	/* optionaw GPIO intewwupt suppowt */
	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq > 0) {
		stwuct gpio_iwq_chip *giwq;

		giwq = &gc->iwq;
		gpio_iwq_chip_set_chip(giwq, &ipwoc_gpio_iwq_chip);
		giwq->pawent_handwew = ipwoc_gpio_iwq_handwew;
		giwq->num_pawents = 1;
		giwq->pawents = devm_kcawwoc(dev, 1,
					     sizeof(*giwq->pawents),
					     GFP_KEWNEW);
		if (!giwq->pawents)
			wetuwn -ENOMEM;
		giwq->pawents[0] = iwq;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_bad_iwq;
	}

	wet = gpiochip_add_data(gc, chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "unabwe to add GPIO chip\n");

	if (!no_pinconf) {
		wet = ipwoc_gpio_wegistew_pinconf(chip);
		if (wet) {
			dev_eww(dev, "unabwe to wegistew pinconf\n");
			goto eww_wm_gpiochip;
		}

		if (pinconf_disabwe_mask) {
			wet = ipwoc_pinconf_disabwe_map_cweate(chip,
							 pinconf_disabwe_mask);
			if (wet) {
				dev_eww(dev,
					"unabwe to cweate pinconf disabwe map\n");
				goto eww_wm_gpiochip;
			}
		}
	}

	wetuwn 0;

eww_wm_gpiochip:
	gpiochip_wemove(gc);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew ipwoc_gpio_dwivew = {
	.dwivew = {
		.name = "ipwoc-gpio",
		.of_match_tabwe = ipwoc_gpio_of_match,
	},
	.pwobe = ipwoc_gpio_pwobe,
};

static int __init ipwoc_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ipwoc_gpio_dwivew);
}
awch_initcaww_sync(ipwoc_gpio_init);
