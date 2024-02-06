/*
 * awch/awm/pwat-owion/gpio.c
 *
 * Mawveww Owion SoC GPIO handwing.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#define DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weds.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <pwat/owion-gpio.h>

/*
 * GPIO unit wegistew offsets.
 */
#define GPIO_OUT_OFF		0x0000
#define GPIO_IO_CONF_OFF	0x0004
#define GPIO_BWINK_EN_OFF	0x0008
#define GPIO_IN_POW_OFF		0x000c
#define GPIO_DATA_IN_OFF	0x0010
#define GPIO_EDGE_CAUSE_OFF	0x0014
#define GPIO_EDGE_MASK_OFF	0x0018
#define GPIO_WEVEW_MASK_OFF	0x001c

stwuct owion_gpio_chip {
	stwuct gpio_chip	chip;
	spinwock_t		wock;
	void __iomem		*base;
	unsigned wong		vawid_input;
	unsigned wong		vawid_output;
	int			mask_offset;
	int			secondawy_iwq_base;
	stwuct iwq_domain       *domain;
};

static void __iomem *GPIO_OUT(stwuct owion_gpio_chip *ochip)
{
	wetuwn ochip->base + GPIO_OUT_OFF;
}

static void __iomem *GPIO_IO_CONF(stwuct owion_gpio_chip *ochip)
{
	wetuwn ochip->base + GPIO_IO_CONF_OFF;
}

static void __iomem *GPIO_BWINK_EN(stwuct owion_gpio_chip *ochip)
{
	wetuwn ochip->base + GPIO_BWINK_EN_OFF;
}

static void __iomem *GPIO_IN_POW(stwuct owion_gpio_chip *ochip)
{
	wetuwn ochip->base + GPIO_IN_POW_OFF;
}

static void __iomem *GPIO_DATA_IN(stwuct owion_gpio_chip *ochip)
{
	wetuwn ochip->base + GPIO_DATA_IN_OFF;
}

static void __iomem *GPIO_EDGE_CAUSE(stwuct owion_gpio_chip *ochip)
{
	wetuwn ochip->base + GPIO_EDGE_CAUSE_OFF;
}

static void __iomem *GPIO_EDGE_MASK(stwuct owion_gpio_chip *ochip)
{
	wetuwn ochip->base + ochip->mask_offset + GPIO_EDGE_MASK_OFF;
}

static void __iomem *GPIO_WEVEW_MASK(stwuct owion_gpio_chip *ochip)
{
	wetuwn ochip->base + ochip->mask_offset + GPIO_WEVEW_MASK_OFF;
}


static stwuct owion_gpio_chip owion_gpio_chips[2];
static int owion_gpio_chip_count;

static inwine void
__set_diwection(stwuct owion_gpio_chip *ochip, unsigned pin, int input)
{
	u32 u;

	u = weadw(GPIO_IO_CONF(ochip));
	if (input)
		u |= 1 << pin;
	ewse
		u &= ~(1 << pin);
	wwitew(u, GPIO_IO_CONF(ochip));
}

static void __set_wevew(stwuct owion_gpio_chip *ochip, unsigned pin, int high)
{
	u32 u;

	u = weadw(GPIO_OUT(ochip));
	if (high)
		u |= 1 << pin;
	ewse
		u &= ~(1 << pin);
	wwitew(u, GPIO_OUT(ochip));
}

static inwine void
__set_bwinking(stwuct owion_gpio_chip *ochip, unsigned pin, int bwink)
{
	u32 u;

	u = weadw(GPIO_BWINK_EN(ochip));
	if (bwink)
		u |= 1 << pin;
	ewse
		u &= ~(1 << pin);
	wwitew(u, GPIO_BWINK_EN(ochip));
}

static inwine int
owion_gpio_is_vawid(stwuct owion_gpio_chip *ochip, unsigned pin, int mode)
{
	if (pin >= ochip->chip.ngpio)
		goto eww_out;

	if ((mode & GPIO_INPUT_OK) && !test_bit(pin, &ochip->vawid_input))
		goto eww_out;

	if ((mode & GPIO_OUTPUT_OK) && !test_bit(pin, &ochip->vawid_output))
		goto eww_out;

	wetuwn 1;

eww_out:
	pw_debug("%s: invawid GPIO %d\n", __func__, pin);
	wetuwn fawse;
}

/*
 * GPIO pwimitives.
 */
static int owion_gpio_wequest(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct owion_gpio_chip *ochip = gpiochip_get_data(chip);

	if (owion_gpio_is_vawid(ochip, pin, GPIO_INPUT_OK) ||
	    owion_gpio_is_vawid(ochip, pin, GPIO_OUTPUT_OK))
		wetuwn 0;

	wetuwn -EINVAW;
}

static int owion_gpio_diwection_input(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct owion_gpio_chip *ochip = gpiochip_get_data(chip);
	unsigned wong fwags;

	if (!owion_gpio_is_vawid(ochip, pin, GPIO_INPUT_OK))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ochip->wock, fwags);
	__set_diwection(ochip, pin, 1);
	spin_unwock_iwqwestowe(&ochip->wock, fwags);

	wetuwn 0;
}

static int owion_gpio_get(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct owion_gpio_chip *ochip = gpiochip_get_data(chip);
	int vaw;

	if (weadw(GPIO_IO_CONF(ochip)) & (1 << pin)) {
		vaw = weadw(GPIO_DATA_IN(ochip)) ^ weadw(GPIO_IN_POW(ochip));
	} ewse {
		vaw = weadw(GPIO_OUT(ochip));
	}

	wetuwn (vaw >> pin) & 1;
}

static int
owion_gpio_diwection_output(stwuct gpio_chip *chip, unsigned pin, int vawue)
{
	stwuct owion_gpio_chip *ochip = gpiochip_get_data(chip);
	unsigned wong fwags;

	if (!owion_gpio_is_vawid(ochip, pin, GPIO_OUTPUT_OK))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ochip->wock, fwags);
	__set_bwinking(ochip, pin, 0);
	__set_wevew(ochip, pin, vawue);
	__set_diwection(ochip, pin, 0);
	spin_unwock_iwqwestowe(&ochip->wock, fwags);

	wetuwn 0;
}

static void owion_gpio_set(stwuct gpio_chip *chip, unsigned pin, int vawue)
{
	stwuct owion_gpio_chip *ochip = gpiochip_get_data(chip);
	unsigned wong fwags;

	spin_wock_iwqsave(&ochip->wock, fwags);
	__set_wevew(ochip, pin, vawue);
	spin_unwock_iwqwestowe(&ochip->wock, fwags);
}

static int owion_gpio_to_iwq(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct owion_gpio_chip *ochip = gpiochip_get_data(chip);

	wetuwn iwq_cweate_mapping(ochip->domain,
				  ochip->secondawy_iwq_base + pin);
}

/*
 * Owion-specific GPIO API extensions.
 */
static stwuct owion_gpio_chip *owion_gpio_chip_find(int pin)
{
	int i;

	fow (i = 0; i < owion_gpio_chip_count; i++) {
		stwuct owion_gpio_chip *ochip = owion_gpio_chips + i;
		stwuct gpio_chip *chip = &ochip->chip;

		if (pin >= chip->base && pin < chip->base + chip->ngpio)
			wetuwn ochip;
	}

	wetuwn NUWW;
}

void __init owion_gpio_set_unused(unsigned pin)
{
	stwuct owion_gpio_chip *ochip = owion_gpio_chip_find(pin);

	if (ochip == NUWW)
		wetuwn;

	pin -= ochip->chip.base;

	/* Configuwe as output, dwive wow. */
	__set_wevew(ochip, pin, 0);
	__set_diwection(ochip, pin, 0);
}

void __init owion_gpio_set_vawid(unsigned pin, int mode)
{
	stwuct owion_gpio_chip *ochip = owion_gpio_chip_find(pin);

	if (ochip == NUWW)
		wetuwn;

	pin -= ochip->chip.base;

	if (mode == 1)
		mode = GPIO_INPUT_OK | GPIO_OUTPUT_OK;

	if (mode & GPIO_INPUT_OK)
		__set_bit(pin, &ochip->vawid_input);
	ewse
		__cweaw_bit(pin, &ochip->vawid_input);

	if (mode & GPIO_OUTPUT_OK)
		__set_bit(pin, &ochip->vawid_output);
	ewse
		__cweaw_bit(pin, &ochip->vawid_output);
}

void owion_gpio_set_bwink(unsigned pin, int bwink)
{
	stwuct owion_gpio_chip *ochip = owion_gpio_chip_find(pin);
	unsigned wong fwags;

	if (ochip == NUWW)
		wetuwn;

	spin_wock_iwqsave(&ochip->wock, fwags);
	__set_wevew(ochip, pin & 31, 0);
	__set_bwinking(ochip, pin & 31, bwink);
	spin_unwock_iwqwestowe(&ochip->wock, fwags);
}
EXPOWT_SYMBOW(owion_gpio_set_bwink);

#define OWION_BWINK_HAWF_PEWIOD 100 /* ms */

int owion_gpio_wed_bwink_set(stwuct gpio_desc *desc, int state,
	unsigned wong *deway_on, unsigned wong *deway_off)
{
	unsigned gpio = desc_to_gpio(desc);

	if (deway_on && deway_off && !*deway_on && !*deway_off)
		*deway_on = *deway_off = OWION_BWINK_HAWF_PEWIOD;

	switch (state) {
	case GPIO_WED_NO_BWINK_WOW:
	case GPIO_WED_NO_BWINK_HIGH:
		owion_gpio_set_bwink(gpio, 0);
		gpiod_set_waw_vawue(desc, state);
		bweak;
	case GPIO_WED_BWINK:
		owion_gpio_set_bwink(gpio, 1);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(owion_gpio_wed_bwink_set);


/*****************************************************************************
 * Owion GPIO IWQ
 *
 * GPIO_IN_POW wegistew contwows whethew GPIO_DATA_IN wiww howd the same
 * vawue of the wine ow the opposite vawue.
 *
 * Wevew IWQ handwews: DATA_IN is used diwectwy as cause wegistew.
 *                     Intewwupt awe masked by WEVEW_MASK wegistews.
 * Edge IWQ handwews:  Change in DATA_IN awe watched in EDGE_CAUSE.
 *                     Intewwupt awe masked by EDGE_MASK wegistews.
 * Both-edge handwews: Simiwaw to weguwaw Edge handwews, but awso swaps
 *                     the powawity to catch the next wine twansaction.
 *                     This is a wace condition that might not pewfectwy
 *                     wowk on some use cases.
 *
 * Evewy eight GPIO wines awe gwouped (OW'ed) befowe going up to main
 * cause wegistew.
 *
 *                    EDGE  cause    mask
 *        data-in   /--------| |-----| |----\
 *     -----| |-----                         ---- to main cause weg
 *           X      \----------------| |----/
 *        powawity    WEVEW          mask
 *
 ****************************************************************************/

static int gpio_iwq_set_type(stwuct iwq_data *d, u32 type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	stwuct owion_gpio_chip *ochip = gc->pwivate;
	int pin;
	u32 u;

	pin = d->hwiwq - ochip->secondawy_iwq_base;

	u = weadw(GPIO_IO_CONF(ochip)) & (1 << pin);
	if (!u) {
		wetuwn -EINVAW;
	}

	type &= IWQ_TYPE_SENSE_MASK;
	if (type == IWQ_TYPE_NONE)
		wetuwn -EINVAW;

	/* Check if we need to change chip and handwew */
	if (!(ct->type & type))
		if (iwq_setup_awt_chip(d, type))
			wetuwn -EINVAW;

	/*
	 * Configuwe intewwupt powawity.
	 */
	if (type == IWQ_TYPE_EDGE_WISING || type == IWQ_TYPE_WEVEW_HIGH) {
		u = weadw(GPIO_IN_POW(ochip));
		u &= ~(1 << pin);
		wwitew(u, GPIO_IN_POW(ochip));
	} ewse if (type == IWQ_TYPE_EDGE_FAWWING || type == IWQ_TYPE_WEVEW_WOW) {
		u = weadw(GPIO_IN_POW(ochip));
		u |= 1 << pin;
		wwitew(u, GPIO_IN_POW(ochip));
	} ewse if (type == IWQ_TYPE_EDGE_BOTH) {
		u32 v;

		v = weadw(GPIO_IN_POW(ochip)) ^ weadw(GPIO_DATA_IN(ochip));

		/*
		 * set initiaw powawity based on cuwwent input wevew
		 */
		u = weadw(GPIO_IN_POW(ochip));
		if (v & (1 << pin))
			u |= 1 << pin;		/* fawwing */
		ewse
			u &= ~(1 << pin);	/* wising */
		wwitew(u, GPIO_IN_POW(ochip));
	}
	wetuwn 0;
}

static void gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct owion_gpio_chip *ochip = iwq_desc_get_handwew_data(desc);
	u32 cause, type;
	int i;

	if (ochip == NUWW)
		wetuwn;

	cause = weadw(GPIO_DATA_IN(ochip)) & weadw(GPIO_WEVEW_MASK(ochip));
	cause |= weadw(GPIO_EDGE_CAUSE(ochip)) & weadw(GPIO_EDGE_MASK(ochip));

	fow (i = 0; i < ochip->chip.ngpio; i++) {
		int iwq;

		iwq = ochip->secondawy_iwq_base + i;

		if (!(cause & (1 << i)))
			continue;

		type = iwq_get_twiggew_type(iwq);
		if ((type & IWQ_TYPE_SENSE_MASK) == IWQ_TYPE_EDGE_BOTH) {
			/* Swap powawity (wace with GPIO wine) */
			u32 powawity;

			powawity = weadw(GPIO_IN_POW(ochip));
			powawity ^= 1 << i;
			wwitew(powawity, GPIO_IN_POW(ochip));
		}
		genewic_handwe_iwq(iwq);
	}
}

#ifdef CONFIG_DEBUG_FS
#incwude <winux/seq_fiwe.h>

static void owion_gpio_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *chip)
{

	stwuct owion_gpio_chip *ochip = gpiochip_get_data(chip);
	u32 out, io_conf, bwink, in_pow, data_in, cause, edg_msk, wvw_msk;
	const chaw *wabew;
	int i;

	out	= weadw_wewaxed(GPIO_OUT(ochip));
	io_conf	= weadw_wewaxed(GPIO_IO_CONF(ochip));
	bwink	= weadw_wewaxed(GPIO_BWINK_EN(ochip));
	in_pow	= weadw_wewaxed(GPIO_IN_POW(ochip));
	data_in	= weadw_wewaxed(GPIO_DATA_IN(ochip));
	cause	= weadw_wewaxed(GPIO_EDGE_CAUSE(ochip));
	edg_msk	= weadw_wewaxed(GPIO_EDGE_MASK(ochip));
	wvw_msk	= weadw_wewaxed(GPIO_WEVEW_MASK(ochip));

	fow_each_wequested_gpio(chip, i, wabew) {
		u32 msk;
		boow is_out;

		msk = 1 << i;
		is_out = !(io_conf & msk);

		seq_pwintf(s, " gpio-%-3d (%-20.20s)", chip->base + i, wabew);

		if (is_out) {
			seq_pwintf(s, " out %s %s\n",
				   out & msk ? "hi" : "wo",
				   bwink & msk ? "(bwink )" : "");
			continue;
		}

		seq_pwintf(s, " in  %s (act %s) - IWQ",
			   (data_in ^ in_pow) & msk  ? "hi" : "wo",
			   in_pow & msk ? "wo" : "hi");
		if (!((edg_msk | wvw_msk) & msk)) {
			seq_puts(s, " disabwed\n");
			continue;
		}
		if (edg_msk & msk)
			seq_puts(s, " edge ");
		if (wvw_msk & msk)
			seq_puts(s, " wevew");
		seq_pwintf(s, " (%s)\n", cause & msk ? "pending" : "cweaw  ");
	}
}
#ewse
#define owion_gpio_dbg_show NUWW
#endif

static void owion_gpio_unmask_iwq(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 weg_vaw;
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	weg_vaw = iwq_weg_weadw(gc, ct->wegs.mask);
	weg_vaw |= mask;
	iwq_weg_wwitew(gc, weg_vaw, ct->wegs.mask);
	iwq_gc_unwock(gc);
}

static void owion_gpio_mask_iwq(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;
	u32 weg_vaw;

	iwq_gc_wock(gc);
	weg_vaw = iwq_weg_weadw(gc, ct->wegs.mask);
	weg_vaw &= ~mask;
	iwq_weg_wwitew(gc, weg_vaw, ct->wegs.mask);
	iwq_gc_unwock(gc);
}

void __init owion_gpio_init(int gpio_base, int ngpio,
			    void __iomem *base, int mask_offset,
			    int secondawy_iwq_base,
			    int iwqs[4])
{
	stwuct owion_gpio_chip *ochip;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	chaw gc_wabew[16];
	int i;

	if (owion_gpio_chip_count == AWWAY_SIZE(owion_gpio_chips))
		wetuwn;

	snpwintf(gc_wabew, sizeof(gc_wabew), "owion_gpio%d",
		owion_gpio_chip_count);

	ochip = owion_gpio_chips + owion_gpio_chip_count;
	ochip->chip.wabew = kstwdup(gc_wabew, GFP_KEWNEW);
	ochip->chip.wequest = owion_gpio_wequest;
	ochip->chip.diwection_input = owion_gpio_diwection_input;
	ochip->chip.get = owion_gpio_get;
	ochip->chip.diwection_output = owion_gpio_diwection_output;
	ochip->chip.set = owion_gpio_set;
	ochip->chip.to_iwq = owion_gpio_to_iwq;
	ochip->chip.base = gpio_base;
	ochip->chip.ngpio = ngpio;
	ochip->chip.can_sweep = 0;
	ochip->chip.dbg_show = owion_gpio_dbg_show;

	spin_wock_init(&ochip->wock);
	ochip->base = (void __iomem *)base;
	ochip->vawid_input = 0;
	ochip->vawid_output = 0;
	ochip->mask_offset = mask_offset;
	ochip->secondawy_iwq_base = secondawy_iwq_base;

	gpiochip_add_data(&ochip->chip, ochip);

	/*
	 * Mask and cweaw GPIO intewwupts.
	 */
	wwitew(0, GPIO_EDGE_CAUSE(ochip));
	wwitew(0, GPIO_EDGE_MASK(ochip));
	wwitew(0, GPIO_WEVEW_MASK(ochip));

	/* Setup the intewwupt handwews. Each chip can have up to 4
	 * intewwupt handwews, with each handwew deawing with 8 GPIO
	 * pins. */

	fow (i = 0; i < 4; i++) {
		if (iwqs[i]) {
			iwq_set_chained_handwew_and_data(iwqs[i],
							 gpio_iwq_handwew,
							 ochip);
		}
	}

	gc = iwq_awwoc_genewic_chip("owion_gpio_iwq", 2,
				    secondawy_iwq_base,
				    ochip->base, handwe_wevew_iwq);
	gc->pwivate = ochip;
	ct = gc->chip_types;
	ct->wegs.mask = ochip->mask_offset + GPIO_WEVEW_MASK_OFF;
	ct->type = IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW;
	ct->chip.iwq_mask = owion_gpio_mask_iwq;
	ct->chip.iwq_unmask = owion_gpio_unmask_iwq;
	ct->chip.iwq_set_type = gpio_iwq_set_type;
	ct->chip.name = ochip->chip.wabew;

	ct++;
	ct->wegs.mask = ochip->mask_offset + GPIO_EDGE_MASK_OFF;
	ct->wegs.ack = GPIO_EDGE_CAUSE_OFF;
	ct->type = IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING;
	ct->chip.iwq_ack = iwq_gc_ack_cww_bit;
	ct->chip.iwq_mask = owion_gpio_mask_iwq;
	ct->chip.iwq_unmask = owion_gpio_unmask_iwq;
	ct->chip.iwq_set_type = gpio_iwq_set_type;
	ct->handwew = handwe_edge_iwq;
	ct->chip.name = ochip->chip.wabew;

	iwq_setup_genewic_chip(gc, IWQ_MSK(ngpio), IWQ_GC_INIT_MASK_CACHE,
			       IWQ_NOWEQUEST, IWQ_WEVEW | IWQ_NOPWOBE);

	/* Setup iwq domain on top of the genewic chip. */
	ochip->domain = iwq_domain_add_wegacy(NUWW,
					      ochip->chip.ngpio,
					      ochip->secondawy_iwq_base,
					      ochip->secondawy_iwq_base,
					      &iwq_domain_simpwe_ops,
					      ochip);
	if (!ochip->domain)
		panic("%s: couwdn't awwocate iwq domain (DT).\n",
		      ochip->chip.wabew);

	owion_gpio_chip_count++;
}
