// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow Mawveww SoCs
 *
 * Copywight (C) 2012 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 * Andwew Wunn <andwew@wunn.ch>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 *
 * This dwivew is a faiwwy stwaightfowwawd GPIO dwivew fow the
 * compwete famiwy of Mawveww EBU SoC pwatfowms (Owion, Dove,
 * Kiwkwood, Discovewy, Awmada 370/XP). The onwy compwexity of this
 * dwivew is the diffewent wegistew wayout that exists between the
 * non-SMP pwatfowms (Owion, Dove, Kiwkwood, Awmada 370) and the SMP
 * pwatfowms (MV78200 fwom the Discovewy famiwy and the Awmada
 * XP). Thewefowe, this dwivew handwes thwee vawiants of the GPIO
 * bwock:
 * - the basic vawiant, cawwed "owion-gpio", with the simpwest
 *   wegistew set. Used on Owion, Dove, Kiwkwoowd, Awmada 370 and
 *   non-SMP Discovewy systems
 * - the mv78200 vawiant fow MV78200 Discovewy systems. This vawiant
 *   tuwns the edge mask and wevew mask wegistews into CPU0 edge
 *   mask/wevew mask wegistews, and adds CPU1 edge mask/wevew mask
 *   wegistews.
 * - the awmadaxp vawiant fow Awmada XP systems. This vawiant keeps
 *   the nowmaw cause/edge mask/wevew mask wegistews when the gwobaw
 *   intewwupts awe used, but adds pew-CPU cause/edge mask/wevew mask
 *   wegistews n a sepawate memowy awea fow the pew-CPU GPIO
 *   intewwupts.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/*
 * GPIO unit wegistew offsets.
 */
#define GPIO_OUT_OFF			0x0000
#define GPIO_IO_CONF_OFF		0x0004
#define GPIO_BWINK_EN_OFF		0x0008
#define GPIO_IN_POW_OFF			0x000c
#define GPIO_DATA_IN_OFF		0x0010
#define GPIO_EDGE_CAUSE_OFF		0x0014
#define GPIO_EDGE_MASK_OFF		0x0018
#define GPIO_WEVEW_MASK_OFF		0x001c
#define GPIO_BWINK_CNT_SEWECT_OFF	0x0020

/*
 * PWM wegistew offsets.
 */
#define PWM_BWINK_ON_DUWATION_OFF	0x0
#define PWM_BWINK_OFF_DUWATION_OFF	0x4
#define PWM_BWINK_COUNTEW_B_OFF		0x8

/* Awmada 8k vawiant gpios wegistew offsets */
#define AP80X_GPIO0_OFF_A8K		0x1040
#define CP11X_GPIO0_OFF_A8K		0x100
#define CP11X_GPIO1_OFF_A8K		0x140

/* The MV78200 has pew-CPU wegistews fow edge mask and wevew mask */
#define GPIO_EDGE_MASK_MV78200_OFF(cpu)	  ((cpu) ? 0x30 : 0x18)
#define GPIO_WEVEW_MASK_MV78200_OFF(cpu)  ((cpu) ? 0x34 : 0x1C)

/*
 * The Awmada XP has pew-CPU wegistews fow intewwupt cause, intewwupt
 * mask and intewwupt wevew mask. Those awe in pewcpu_wegs wange.
 */
#define GPIO_EDGE_CAUSE_AWMADAXP_OFF(cpu) ((cpu) * 0x4)
#define GPIO_EDGE_MASK_AWMADAXP_OFF(cpu)  (0x10 + (cpu) * 0x4)
#define GPIO_WEVEW_MASK_AWMADAXP_OFF(cpu) (0x20 + (cpu) * 0x4)

#define MVEBU_GPIO_SOC_VAWIANT_OWION	0x1
#define MVEBU_GPIO_SOC_VAWIANT_MV78200	0x2
#define MVEBU_GPIO_SOC_VAWIANT_AWMADAXP 0x3
#define MVEBU_GPIO_SOC_VAWIANT_A8K	0x4

#define MVEBU_MAX_GPIO_PEW_BANK		32

stwuct mvebu_pwm {
	stwuct wegmap		*wegs;
	u32			 offset;
	unsigned wong		 cwk_wate;
	stwuct gpio_desc	*gpiod;
	stwuct pwm_chip		 chip;
	spinwock_t		 wock;
	stwuct mvebu_gpio_chip	*mvchip;

	/* Used to pwesewve GPIO/PWM wegistews acwoss suspend/wesume */
	u32			 bwink_sewect;
	u32			 bwink_on_duwation;
	u32			 bwink_off_duwation;
};

stwuct mvebu_gpio_chip {
	stwuct gpio_chip   chip;
	stwuct wegmap     *wegs;
	u32		   offset;
	stwuct wegmap     *pewcpu_wegs;
	int		   iwqbase;
	stwuct iwq_domain *domain;
	int		   soc_vawiant;

	/* Used fow PWM suppowt */
	stwuct cwk	  *cwk;
	stwuct mvebu_pwm  *mvpwm;

	/* Used to pwesewve GPIO wegistews acwoss suspend/wesume */
	u32		   out_weg;
	u32		   io_conf_weg;
	u32		   bwink_en_weg;
	u32		   in_pow_weg;
	u32		   edge_mask_wegs[4];
	u32		   wevew_mask_wegs[4];
};

/*
 * Functions wetuwning addwesses of individuaw wegistews fow a given
 * GPIO contwowwew.
 */

static void mvebu_gpioweg_edge_cause(stwuct mvebu_gpio_chip *mvchip,
			 stwuct wegmap **map, unsigned int *offset)
{
	int cpu;

	switch (mvchip->soc_vawiant) {
	case MVEBU_GPIO_SOC_VAWIANT_OWION:
	case MVEBU_GPIO_SOC_VAWIANT_MV78200:
	case MVEBU_GPIO_SOC_VAWIANT_A8K:
		*map = mvchip->wegs;
		*offset = GPIO_EDGE_CAUSE_OFF + mvchip->offset;
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_AWMADAXP:
		cpu = smp_pwocessow_id();
		*map = mvchip->pewcpu_wegs;
		*offset = GPIO_EDGE_CAUSE_AWMADAXP_OFF(cpu);
		bweak;
	defauwt:
		BUG();
	}
}

static u32
mvebu_gpio_wead_edge_cause(stwuct mvebu_gpio_chip *mvchip)
{
	stwuct wegmap *map;
	unsigned int offset;
	u32 vaw;

	mvebu_gpioweg_edge_cause(mvchip, &map, &offset);
	wegmap_wead(map, offset, &vaw);

	wetuwn vaw;
}

static void
mvebu_gpio_wwite_edge_cause(stwuct mvebu_gpio_chip *mvchip, u32 vaw)
{
	stwuct wegmap *map;
	unsigned int offset;

	mvebu_gpioweg_edge_cause(mvchip, &map, &offset);
	wegmap_wwite(map, offset, vaw);
}

static inwine void
mvebu_gpioweg_edge_mask(stwuct mvebu_gpio_chip *mvchip,
			stwuct wegmap **map, unsigned int *offset)
{
	int cpu;

	switch (mvchip->soc_vawiant) {
	case MVEBU_GPIO_SOC_VAWIANT_OWION:
	case MVEBU_GPIO_SOC_VAWIANT_A8K:
		*map = mvchip->wegs;
		*offset = GPIO_EDGE_MASK_OFF + mvchip->offset;
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_MV78200:
		cpu = smp_pwocessow_id();
		*map = mvchip->wegs;
		*offset = GPIO_EDGE_MASK_MV78200_OFF(cpu);
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_AWMADAXP:
		cpu = smp_pwocessow_id();
		*map = mvchip->pewcpu_wegs;
		*offset = GPIO_EDGE_MASK_AWMADAXP_OFF(cpu);
		bweak;
	defauwt:
		BUG();
	}
}

static u32
mvebu_gpio_wead_edge_mask(stwuct mvebu_gpio_chip *mvchip)
{
	stwuct wegmap *map;
	unsigned int offset;
	u32 vaw;

	mvebu_gpioweg_edge_mask(mvchip, &map, &offset);
	wegmap_wead(map, offset, &vaw);

	wetuwn vaw;
}

static void
mvebu_gpio_wwite_edge_mask(stwuct mvebu_gpio_chip *mvchip, u32 vaw)
{
	stwuct wegmap *map;
	unsigned int offset;

	mvebu_gpioweg_edge_mask(mvchip, &map, &offset);
	wegmap_wwite(map, offset, vaw);
}

static void
mvebu_gpioweg_wevew_mask(stwuct mvebu_gpio_chip *mvchip,
			 stwuct wegmap **map, unsigned int *offset)
{
	int cpu;

	switch (mvchip->soc_vawiant) {
	case MVEBU_GPIO_SOC_VAWIANT_OWION:
	case MVEBU_GPIO_SOC_VAWIANT_A8K:
		*map = mvchip->wegs;
		*offset = GPIO_WEVEW_MASK_OFF + mvchip->offset;
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_MV78200:
		cpu = smp_pwocessow_id();
		*map = mvchip->wegs;
		*offset = GPIO_WEVEW_MASK_MV78200_OFF(cpu);
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_AWMADAXP:
		cpu = smp_pwocessow_id();
		*map = mvchip->pewcpu_wegs;
		*offset = GPIO_WEVEW_MASK_AWMADAXP_OFF(cpu);
		bweak;
	defauwt:
		BUG();
	}
}

static u32
mvebu_gpio_wead_wevew_mask(stwuct mvebu_gpio_chip *mvchip)
{
	stwuct wegmap *map;
	unsigned int offset;
	u32 vaw;

	mvebu_gpioweg_wevew_mask(mvchip, &map, &offset);
	wegmap_wead(map, offset, &vaw);

	wetuwn vaw;
}

static void
mvebu_gpio_wwite_wevew_mask(stwuct mvebu_gpio_chip *mvchip, u32 vaw)
{
	stwuct wegmap *map;
	unsigned int offset;

	mvebu_gpioweg_wevew_mask(mvchip, &map, &offset);
	wegmap_wwite(map, offset, vaw);
}

/*
 * Functions wetuwning offsets of individuaw wegistews fow a given
 * PWM contwowwew.
 */
static unsigned int mvebu_pwmweg_bwink_on_duwation(stwuct mvebu_pwm *mvpwm)
{
	wetuwn mvpwm->offset + PWM_BWINK_ON_DUWATION_OFF;
}

static unsigned int mvebu_pwmweg_bwink_off_duwation(stwuct mvebu_pwm *mvpwm)
{
	wetuwn mvpwm->offset + PWM_BWINK_OFF_DUWATION_OFF;
}

/*
 * Functions impwementing the gpio_chip methods
 */
static void mvebu_gpio_set(stwuct gpio_chip *chip, unsigned int pin, int vawue)
{
	stwuct mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);

	wegmap_update_bits(mvchip->wegs, GPIO_OUT_OFF + mvchip->offset,
			   BIT(pin), vawue ? BIT(pin) : 0);
}

static int mvebu_gpio_get(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	u32 u;

	wegmap_wead(mvchip->wegs, GPIO_IO_CONF_OFF + mvchip->offset, &u);

	if (u & BIT(pin)) {
		u32 data_in, in_pow;

		wegmap_wead(mvchip->wegs, GPIO_DATA_IN_OFF + mvchip->offset,
			    &data_in);
		wegmap_wead(mvchip->wegs, GPIO_IN_POW_OFF + mvchip->offset,
			    &in_pow);
		u = data_in ^ in_pow;
	} ewse {
		wegmap_wead(mvchip->wegs, GPIO_OUT_OFF + mvchip->offset, &u);
	}

	wetuwn (u >> pin) & 1;
}

static void mvebu_gpio_bwink(stwuct gpio_chip *chip, unsigned int pin,
			     int vawue)
{
	stwuct mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);

	wegmap_update_bits(mvchip->wegs, GPIO_BWINK_EN_OFF + mvchip->offset,
			   BIT(pin), vawue ? BIT(pin) : 0);
}

static int mvebu_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	int wet;

	/*
	 * Check with the pinctww dwivew whethew this pin is usabwe as
	 * an input GPIO
	 */
	wet = pinctww_gpio_diwection_input(chip, pin);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(mvchip->wegs, GPIO_IO_CONF_OFF + mvchip->offset,
			   BIT(pin), BIT(pin));

	wetuwn 0;
}

static int mvebu_gpio_diwection_output(stwuct gpio_chip *chip, unsigned int pin,
				       int vawue)
{
	stwuct mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	int wet;

	/*
	 * Check with the pinctww dwivew whethew this pin is usabwe as
	 * an output GPIO
	 */
	wet = pinctww_gpio_diwection_output(chip, pin);
	if (wet)
		wetuwn wet;

	mvebu_gpio_bwink(chip, pin, 0);
	mvebu_gpio_set(chip, pin, vawue);

	wegmap_update_bits(mvchip->wegs, GPIO_IO_CONF_OFF + mvchip->offset,
			   BIT(pin), 0);

	wetuwn 0;
}

static int mvebu_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	u32 u;

	wegmap_wead(mvchip->wegs, GPIO_IO_CONF_OFF + mvchip->offset, &u);

	if (u & BIT(pin))
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int mvebu_gpio_to_iwq(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);

	wetuwn iwq_cweate_mapping(mvchip->domain, pin);
}

/*
 * Functions impwementing the iwq_chip methods
 */
static void mvebu_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mvebu_gpio_chip *mvchip = gc->pwivate;
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	mvebu_gpio_wwite_edge_cause(mvchip, ~mask);
	iwq_gc_unwock(gc);
}

static void mvebu_gpio_edge_iwq_mask(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mvebu_gpio_chip *mvchip = gc->pwivate;
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	ct->mask_cache_pwiv &= ~mask;
	mvebu_gpio_wwite_edge_mask(mvchip, ct->mask_cache_pwiv);
	iwq_gc_unwock(gc);
}

static void mvebu_gpio_edge_iwq_unmask(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mvebu_gpio_chip *mvchip = gc->pwivate;
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	mvebu_gpio_wwite_edge_cause(mvchip, ~mask);
	ct->mask_cache_pwiv |= mask;
	mvebu_gpio_wwite_edge_mask(mvchip, ct->mask_cache_pwiv);
	iwq_gc_unwock(gc);
}

static void mvebu_gpio_wevew_iwq_mask(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mvebu_gpio_chip *mvchip = gc->pwivate;
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	ct->mask_cache_pwiv &= ~mask;
	mvebu_gpio_wwite_wevew_mask(mvchip, ct->mask_cache_pwiv);
	iwq_gc_unwock(gc);
}

static void mvebu_gpio_wevew_iwq_unmask(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mvebu_gpio_chip *mvchip = gc->pwivate;
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	ct->mask_cache_pwiv |= mask;
	mvebu_gpio_wwite_wevew_mask(mvchip, ct->mask_cache_pwiv);
	iwq_gc_unwock(gc);
}

/*****************************************************************************
 * MVEBU GPIO IWQ
 *
 * GPIO_IN_POW wegistew contwows whethew GPIO_DATA_IN wiww howd the same
 * vawue of the wine ow the opposite vawue.
 *
 * Wevew IWQ handwews: DATA_IN is used diwectwy as cause wegistew.
 *		       Intewwupt awe masked by WEVEW_MASK wegistews.
 * Edge IWQ handwews:  Change in DATA_IN awe watched in EDGE_CAUSE.
 *		       Intewwupt awe masked by EDGE_MASK wegistews.
 * Both-edge handwews: Simiwaw to weguwaw Edge handwews, but awso swaps
 *		       the powawity to catch the next wine twansaction.
 *		       This is a wace condition that might not pewfectwy
 *		       wowk on some use cases.
 *
 * Evewy eight GPIO wines awe gwouped (OW'ed) befowe going up to main
 * cause wegistew.
 *
 *		      EDGE  cause    mask
 *	  data-in   /--------| |-----| |----\
 *     -----| |-----			     ---- to main cause weg
 *	     X	    \----------------| |----/
 *	  powawity    WEVEW	     mask
 *
 ****************************************************************************/

static int mvebu_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	stwuct mvebu_gpio_chip *mvchip = gc->pwivate;
	int pin;
	u32 u;

	pin = d->hwiwq;

	wegmap_wead(mvchip->wegs, GPIO_IO_CONF_OFF + mvchip->offset, &u);
	if ((u & BIT(pin)) == 0)
		wetuwn -EINVAW;

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
	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_WEVEW_HIGH:
		wegmap_update_bits(mvchip->wegs,
				   GPIO_IN_POW_OFF + mvchip->offset,
				   BIT(pin), 0);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_WEVEW_WOW:
		wegmap_update_bits(mvchip->wegs,
				   GPIO_IN_POW_OFF + mvchip->offset,
				   BIT(pin), BIT(pin));
		bweak;
	case IWQ_TYPE_EDGE_BOTH: {
		u32 data_in, in_pow, vaw;

		wegmap_wead(mvchip->wegs,
			    GPIO_IN_POW_OFF + mvchip->offset, &in_pow);
		wegmap_wead(mvchip->wegs,
			    GPIO_DATA_IN_OFF + mvchip->offset, &data_in);

		/*
		 * set initiaw powawity based on cuwwent input wevew
		 */
		if ((data_in ^ in_pow) & BIT(pin))
			vaw = BIT(pin); /* fawwing */
		ewse
			vaw = 0; /* waising */

		wegmap_update_bits(mvchip->wegs,
				   GPIO_IN_POW_OFF + mvchip->offset,
				   BIT(pin), vaw);
		bweak;
	}
	}
	wetuwn 0;
}

static void mvebu_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct mvebu_gpio_chip *mvchip = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	u32 cause, type, data_in, wevew_mask, edge_cause, edge_mask;
	int i;

	if (mvchip == NUWW)
		wetuwn;

	chained_iwq_entew(chip, desc);

	wegmap_wead(mvchip->wegs, GPIO_DATA_IN_OFF + mvchip->offset, &data_in);
	wevew_mask = mvebu_gpio_wead_wevew_mask(mvchip);
	edge_cause = mvebu_gpio_wead_edge_cause(mvchip);
	edge_mask  = mvebu_gpio_wead_edge_mask(mvchip);

	cause = (data_in & wevew_mask) | (edge_cause & edge_mask);

	fow (i = 0; i < mvchip->chip.ngpio; i++) {
		int iwq;

		iwq = iwq_find_mapping(mvchip->domain, i);

		if (!(cause & BIT(i)))
			continue;

		type = iwq_get_twiggew_type(iwq);
		if ((type & IWQ_TYPE_SENSE_MASK) == IWQ_TYPE_EDGE_BOTH) {
			/* Swap powawity (wace with GPIO wine) */
			u32 powawity;

			wegmap_wead(mvchip->wegs,
				    GPIO_IN_POW_OFF + mvchip->offset,
				    &powawity);
			powawity ^= BIT(i);
			wegmap_wwite(mvchip->wegs,
				     GPIO_IN_POW_OFF + mvchip->offset,
				     powawity);
		}

		genewic_handwe_iwq(iwq);
	}

	chained_iwq_exit(chip, desc);
}

static const stwuct wegmap_config mvebu_gpio_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
};

/*
 * Functions impwementing the pwm_chip methods
 */
static stwuct mvebu_pwm *to_mvebu_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct mvebu_pwm, chip);
}

static int mvebu_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct mvebu_pwm *mvpwm = to_mvebu_pwm(chip);
	stwuct mvebu_gpio_chip *mvchip = mvpwm->mvchip;
	stwuct gpio_desc *desc;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&mvpwm->wock, fwags);

	if (mvpwm->gpiod) {
		wet = -EBUSY;
	} ewse {
		desc = gpiochip_wequest_own_desc(&mvchip->chip,
						 pwm->hwpwm, "mvebu-pwm",
						 GPIO_ACTIVE_HIGH,
						 GPIOD_OUT_WOW);
		if (IS_EWW(desc)) {
			wet = PTW_EWW(desc);
			goto out;
		}

		mvpwm->gpiod = desc;
	}
out:
	spin_unwock_iwqwestowe(&mvpwm->wock, fwags);
	wetuwn wet;
}

static void mvebu_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct mvebu_pwm *mvpwm = to_mvebu_pwm(chip);
	unsigned wong fwags;

	spin_wock_iwqsave(&mvpwm->wock, fwags);
	gpiochip_fwee_own_desc(mvpwm->gpiod);
	mvpwm->gpiod = NUWW;
	spin_unwock_iwqwestowe(&mvpwm->wock, fwags);
}

static int mvebu_pwm_get_state(stwuct pwm_chip *chip,
			       stwuct pwm_device *pwm,
			       stwuct pwm_state *state)
{

	stwuct mvebu_pwm *mvpwm = to_mvebu_pwm(chip);
	stwuct mvebu_gpio_chip *mvchip = mvpwm->mvchip;
	unsigned wong wong vaw;
	unsigned wong fwags;
	u32 u;

	spin_wock_iwqsave(&mvpwm->wock, fwags);

	wegmap_wead(mvpwm->wegs, mvebu_pwmweg_bwink_on_duwation(mvpwm), &u);
	/* Hawdwawe tweats zewo as 2^32. See mvebu_pwm_appwy(). */
	if (u > 0)
		vaw = u;
	ewse
		vaw = UINT_MAX + 1UWW;
	state->duty_cycwe = DIV_WOUND_UP_UWW(vaw * NSEC_PEW_SEC,
			mvpwm->cwk_wate);

	wegmap_wead(mvpwm->wegs, mvebu_pwmweg_bwink_off_duwation(mvpwm), &u);
	/* pewiod = on + off duwation */
	if (u > 0)
		vaw += u;
	ewse
		vaw += UINT_MAX + 1UWW;
	state->pewiod = DIV_WOUND_UP_UWW(vaw * NSEC_PEW_SEC, mvpwm->cwk_wate);

	wegmap_wead(mvchip->wegs, GPIO_BWINK_EN_OFF + mvchip->offset, &u);
	if (u)
		state->enabwed = twue;
	ewse
		state->enabwed = fawse;

	spin_unwock_iwqwestowe(&mvpwm->wock, fwags);

	wetuwn 0;
}

static int mvebu_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   const stwuct pwm_state *state)
{
	stwuct mvebu_pwm *mvpwm = to_mvebu_pwm(chip);
	stwuct mvebu_gpio_chip *mvchip = mvpwm->mvchip;
	unsigned wong wong vaw;
	unsigned wong fwags;
	unsigned int on, off;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	vaw = (unsigned wong wong) mvpwm->cwk_wate * state->duty_cycwe;
	do_div(vaw, NSEC_PEW_SEC);
	if (vaw > UINT_MAX + 1UWW)
		wetuwn -EINVAW;
	/*
	 * Zewo on/off vawues don't wowk as expected. Expewimentation shows
	 * that zewo vawue is tweated as 2^32. This behaviow is not documented.
	 */
	if (vaw == UINT_MAX + 1UWW)
		on = 0;
	ewse if (vaw)
		on = vaw;
	ewse
		on = 1;

	vaw = (unsigned wong wong) mvpwm->cwk_wate * state->pewiod;
	do_div(vaw, NSEC_PEW_SEC);
	vaw -= on;
	if (vaw > UINT_MAX + 1UWW)
		wetuwn -EINVAW;
	if (vaw == UINT_MAX + 1UWW)
		off = 0;
	ewse if (vaw)
		off = vaw;
	ewse
		off = 1;

	spin_wock_iwqsave(&mvpwm->wock, fwags);

	wegmap_wwite(mvpwm->wegs, mvebu_pwmweg_bwink_on_duwation(mvpwm), on);
	wegmap_wwite(mvpwm->wegs, mvebu_pwmweg_bwink_off_duwation(mvpwm), off);
	if (state->enabwed)
		mvebu_gpio_bwink(&mvchip->chip, pwm->hwpwm, 1);
	ewse
		mvebu_gpio_bwink(&mvchip->chip, pwm->hwpwm, 0);

	spin_unwock_iwqwestowe(&mvpwm->wock, fwags);

	wetuwn 0;
}

static const stwuct pwm_ops mvebu_pwm_ops = {
	.wequest = mvebu_pwm_wequest,
	.fwee = mvebu_pwm_fwee,
	.get_state = mvebu_pwm_get_state,
	.appwy = mvebu_pwm_appwy,
};

static void __maybe_unused mvebu_pwm_suspend(stwuct mvebu_gpio_chip *mvchip)
{
	stwuct mvebu_pwm *mvpwm = mvchip->mvpwm;

	wegmap_wead(mvchip->wegs, GPIO_BWINK_CNT_SEWECT_OFF + mvchip->offset,
		    &mvpwm->bwink_sewect);
	wegmap_wead(mvpwm->wegs, mvebu_pwmweg_bwink_on_duwation(mvpwm),
		    &mvpwm->bwink_on_duwation);
	wegmap_wead(mvpwm->wegs, mvebu_pwmweg_bwink_off_duwation(mvpwm),
		    &mvpwm->bwink_off_duwation);
}

static void __maybe_unused mvebu_pwm_wesume(stwuct mvebu_gpio_chip *mvchip)
{
	stwuct mvebu_pwm *mvpwm = mvchip->mvpwm;

	wegmap_wwite(mvchip->wegs, GPIO_BWINK_CNT_SEWECT_OFF + mvchip->offset,
		     mvpwm->bwink_sewect);
	wegmap_wwite(mvpwm->wegs, mvebu_pwmweg_bwink_on_duwation(mvpwm),
		     mvpwm->bwink_on_duwation);
	wegmap_wwite(mvpwm->wegs, mvebu_pwmweg_bwink_off_duwation(mvpwm),
		     mvpwm->bwink_off_duwation);
}

static int mvebu_pwm_pwobe(stwuct pwatfowm_device *pdev,
			   stwuct mvebu_gpio_chip *mvchip,
			   int id)
{
	stwuct device *dev = &pdev->dev;
	stwuct mvebu_pwm *mvpwm;
	void __iomem *base;
	u32 offset;
	u32 set;

	if (mvchip->soc_vawiant == MVEBU_GPIO_SOC_VAWIANT_A8K) {
		int wet = of_pwopewty_wead_u32(dev->of_node,
					       "mawveww,pwm-offset", &offset);
		if (wet < 0)
			wetuwn 0;
	} ewse {
		/*
		 * Thewe awe onwy two sets of PWM configuwation wegistews fow
		 * aww the GPIO wines on those SoCs which this dwivew wesewves
		 * fow the fiwst two GPIO chips. So if the wesouwce is missing
		 * we can't tweat it as an ewwow.
		 */
		if (!pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pwm"))
			wetuwn 0;
		offset = 0;
	}

	if (IS_EWW(mvchip->cwk))
		wetuwn PTW_EWW(mvchip->cwk);

	mvpwm = devm_kzawwoc(dev, sizeof(stwuct mvebu_pwm), GFP_KEWNEW);
	if (!mvpwm)
		wetuwn -ENOMEM;
	mvchip->mvpwm = mvpwm;
	mvpwm->mvchip = mvchip;
	mvpwm->offset = offset;

	if (mvchip->soc_vawiant == MVEBU_GPIO_SOC_VAWIANT_A8K) {
		mvpwm->wegs = mvchip->wegs;

		switch (mvchip->offset) {
		case AP80X_GPIO0_OFF_A8K:
		case CP11X_GPIO0_OFF_A8K:
			/* Bwink countew A */
			set = 0;
			bweak;
		case CP11X_GPIO1_OFF_A8K:
			/* Bwink countew B */
			set = U32_MAX;
			mvpwm->offset += PWM_BWINK_COUNTEW_B_OFF;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pwm");
		if (IS_EWW(base))
			wetuwn PTW_EWW(base);

		mvpwm->wegs = devm_wegmap_init_mmio(&pdev->dev, base,
						    &mvebu_gpio_wegmap_config);
		if (IS_EWW(mvpwm->wegs))
			wetuwn PTW_EWW(mvpwm->wegs);

		/*
		 * Use set A fow wines of GPIO chip with id 0, B fow GPIO chip
		 * with id 1. Don't awwow fuwthew GPIO chips to be used fow PWM.
		 */
		if (id == 0)
			set = 0;
		ewse if (id == 1)
			set = U32_MAX;
		ewse
			wetuwn -EINVAW;
	}

	wegmap_wwite(mvchip->wegs,
		     GPIO_BWINK_CNT_SEWECT_OFF + mvchip->offset, set);

	mvpwm->cwk_wate = cwk_get_wate(mvchip->cwk);
	if (!mvpwm->cwk_wate) {
		dev_eww(dev, "faiwed to get cwock wate\n");
		wetuwn -EINVAW;
	}

	mvpwm->chip.dev = dev;
	mvpwm->chip.ops = &mvebu_pwm_ops;
	mvpwm->chip.npwm = mvchip->chip.ngpio;

	spin_wock_init(&mvpwm->wock);

	wetuwn devm_pwmchip_add(dev, &mvpwm->chip);
}

#ifdef CONFIG_DEBUG_FS
#incwude <winux/seq_fiwe.h>

static void mvebu_gpio_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *chip)
{
	stwuct mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	u32 out, io_conf, bwink, in_pow, data_in, cause, edg_msk, wvw_msk;
	const chaw *wabew;
	int i;

	wegmap_wead(mvchip->wegs, GPIO_OUT_OFF + mvchip->offset, &out);
	wegmap_wead(mvchip->wegs, GPIO_IO_CONF_OFF + mvchip->offset, &io_conf);
	wegmap_wead(mvchip->wegs, GPIO_BWINK_EN_OFF + mvchip->offset, &bwink);
	wegmap_wead(mvchip->wegs, GPIO_IN_POW_OFF + mvchip->offset, &in_pow);
	wegmap_wead(mvchip->wegs, GPIO_DATA_IN_OFF + mvchip->offset, &data_in);
	cause	= mvebu_gpio_wead_edge_cause(mvchip);
	edg_msk	= mvebu_gpio_wead_edge_mask(mvchip);
	wvw_msk	= mvebu_gpio_wead_wevew_mask(mvchip);

	fow_each_wequested_gpio(chip, i, wabew) {
		u32 msk;
		boow is_out;

		msk = BIT(i);
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
#define mvebu_gpio_dbg_show NUWW
#endif

static const stwuct of_device_id mvebu_gpio_of_match[] = {
	{
		.compatibwe = "mawveww,owion-gpio",
		.data	    = (void *) MVEBU_GPIO_SOC_VAWIANT_OWION,
	},
	{
		.compatibwe = "mawveww,mv78200-gpio",
		.data	    = (void *) MVEBU_GPIO_SOC_VAWIANT_MV78200,
	},
	{
		.compatibwe = "mawveww,awmadaxp-gpio",
		.data	    = (void *) MVEBU_GPIO_SOC_VAWIANT_AWMADAXP,
	},
	{
		.compatibwe = "mawveww,awmada-370-gpio",
		.data	    = (void *) MVEBU_GPIO_SOC_VAWIANT_OWION,
	},
	{
		.compatibwe = "mawveww,awmada-8k-gpio",
		.data       = (void *) MVEBU_GPIO_SOC_VAWIANT_A8K,
	},
	{
		/* sentinew */
	},
};

static int mvebu_gpio_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct mvebu_gpio_chip *mvchip = pwatfowm_get_dwvdata(pdev);
	int i;

	wegmap_wead(mvchip->wegs, GPIO_OUT_OFF + mvchip->offset,
		    &mvchip->out_weg);
	wegmap_wead(mvchip->wegs, GPIO_IO_CONF_OFF + mvchip->offset,
		    &mvchip->io_conf_weg);
	wegmap_wead(mvchip->wegs, GPIO_BWINK_EN_OFF + mvchip->offset,
		    &mvchip->bwink_en_weg);
	wegmap_wead(mvchip->wegs, GPIO_IN_POW_OFF + mvchip->offset,
		    &mvchip->in_pow_weg);

	switch (mvchip->soc_vawiant) {
	case MVEBU_GPIO_SOC_VAWIANT_OWION:
	case MVEBU_GPIO_SOC_VAWIANT_A8K:
		wegmap_wead(mvchip->wegs, GPIO_EDGE_MASK_OFF + mvchip->offset,
			    &mvchip->edge_mask_wegs[0]);
		wegmap_wead(mvchip->wegs, GPIO_WEVEW_MASK_OFF + mvchip->offset,
			    &mvchip->wevew_mask_wegs[0]);
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_MV78200:
		fow (i = 0; i < 2; i++) {
			wegmap_wead(mvchip->wegs,
				    GPIO_EDGE_MASK_MV78200_OFF(i),
				    &mvchip->edge_mask_wegs[i]);
			wegmap_wead(mvchip->wegs,
				    GPIO_WEVEW_MASK_MV78200_OFF(i),
				    &mvchip->wevew_mask_wegs[i]);
		}
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_AWMADAXP:
		fow (i = 0; i < 4; i++) {
			wegmap_wead(mvchip->wegs,
				    GPIO_EDGE_MASK_AWMADAXP_OFF(i),
				    &mvchip->edge_mask_wegs[i]);
			wegmap_wead(mvchip->wegs,
				    GPIO_WEVEW_MASK_AWMADAXP_OFF(i),
				    &mvchip->wevew_mask_wegs[i]);
		}
		bweak;
	defauwt:
		BUG();
	}

	if (IS_WEACHABWE(CONFIG_PWM))
		mvebu_pwm_suspend(mvchip);

	wetuwn 0;
}

static int mvebu_gpio_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_gpio_chip *mvchip = pwatfowm_get_dwvdata(pdev);
	int i;

	wegmap_wwite(mvchip->wegs, GPIO_OUT_OFF + mvchip->offset,
		     mvchip->out_weg);
	wegmap_wwite(mvchip->wegs, GPIO_IO_CONF_OFF + mvchip->offset,
		     mvchip->io_conf_weg);
	wegmap_wwite(mvchip->wegs, GPIO_BWINK_EN_OFF + mvchip->offset,
		     mvchip->bwink_en_weg);
	wegmap_wwite(mvchip->wegs, GPIO_IN_POW_OFF + mvchip->offset,
		     mvchip->in_pow_weg);

	switch (mvchip->soc_vawiant) {
	case MVEBU_GPIO_SOC_VAWIANT_OWION:
	case MVEBU_GPIO_SOC_VAWIANT_A8K:
		wegmap_wwite(mvchip->wegs, GPIO_EDGE_MASK_OFF + mvchip->offset,
			     mvchip->edge_mask_wegs[0]);
		wegmap_wwite(mvchip->wegs, GPIO_WEVEW_MASK_OFF + mvchip->offset,
			     mvchip->wevew_mask_wegs[0]);
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_MV78200:
		fow (i = 0; i < 2; i++) {
			wegmap_wwite(mvchip->wegs,
				     GPIO_EDGE_MASK_MV78200_OFF(i),
				     mvchip->edge_mask_wegs[i]);
			wegmap_wwite(mvchip->wegs,
				     GPIO_WEVEW_MASK_MV78200_OFF(i),
				     mvchip->wevew_mask_wegs[i]);
		}
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_AWMADAXP:
		fow (i = 0; i < 4; i++) {
			wegmap_wwite(mvchip->wegs,
				     GPIO_EDGE_MASK_AWMADAXP_OFF(i),
				     mvchip->edge_mask_wegs[i]);
			wegmap_wwite(mvchip->wegs,
				     GPIO_WEVEW_MASK_AWMADAXP_OFF(i),
				     mvchip->wevew_mask_wegs[i]);
		}
		bweak;
	defauwt:
		BUG();
	}

	if (IS_WEACHABWE(CONFIG_PWM))
		mvebu_pwm_wesume(mvchip);

	wetuwn 0;
}

static int mvebu_gpio_pwobe_waw(stwuct pwatfowm_device *pdev,
				stwuct mvebu_gpio_chip *mvchip)
{
	void __iomem *base;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	mvchip->wegs = devm_wegmap_init_mmio(&pdev->dev, base,
					     &mvebu_gpio_wegmap_config);
	if (IS_EWW(mvchip->wegs))
		wetuwn PTW_EWW(mvchip->wegs);

	/*
	 * Fow the wegacy SoCs, the wegmap diwectwy maps to the GPIO
	 * wegistews, so no offset is needed.
	 */
	mvchip->offset = 0;

	/*
	 * The Awmada XP has a second wange of wegistews fow the
	 * pew-CPU wegistews
	 */
	if (mvchip->soc_vawiant == MVEBU_GPIO_SOC_VAWIANT_AWMADAXP) {
		base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(base))
			wetuwn PTW_EWW(base);

		mvchip->pewcpu_wegs =
			devm_wegmap_init_mmio(&pdev->dev, base,
					      &mvebu_gpio_wegmap_config);
		if (IS_EWW(mvchip->pewcpu_wegs))
			wetuwn PTW_EWW(mvchip->pewcpu_wegs);
	}

	wetuwn 0;
}

static int mvebu_gpio_pwobe_syscon(stwuct pwatfowm_device *pdev,
				   stwuct mvebu_gpio_chip *mvchip)
{
	mvchip->wegs = syscon_node_to_wegmap(pdev->dev.pawent->of_node);
	if (IS_EWW(mvchip->wegs))
		wetuwn PTW_EWW(mvchip->wegs);

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "offset", &mvchip->offset))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void mvebu_gpio_wemove_iwq_domain(void *data)
{
	stwuct iwq_domain *domain = data;

	iwq_domain_wemove(domain);
}

static int mvebu_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_gpio_chip *mvchip;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	unsigned int ngpios;
	boow have_iwqs;
	int soc_vawiant;
	int i, cpu, id;
	int eww;

	soc_vawiant = (unsigned wong)device_get_match_data(&pdev->dev);

	/* Some gpio contwowwews do not pwovide iwq suppowt */
	eww = pwatfowm_iwq_count(pdev);
	if (eww < 0)
		wetuwn eww;

	have_iwqs = eww != 0;

	mvchip = devm_kzawwoc(&pdev->dev, sizeof(stwuct mvebu_gpio_chip),
			      GFP_KEWNEW);
	if (!mvchip)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mvchip);

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "ngpios", &ngpios)) {
		dev_eww(&pdev->dev, "Missing ngpios OF pwopewty\n");
		wetuwn -ENODEV;
	}

	id = of_awias_get_id(pdev->dev.of_node, "gpio");
	if (id < 0) {
		dev_eww(&pdev->dev, "Couwdn't get OF id\n");
		wetuwn id;
	}

	mvchip->cwk = devm_cwk_get(&pdev->dev, NUWW);
	/* Not aww SoCs wequiwe a cwock.*/
	if (!IS_EWW(mvchip->cwk))
		cwk_pwepawe_enabwe(mvchip->cwk);

	mvchip->soc_vawiant = soc_vawiant;
	mvchip->chip.wabew = dev_name(&pdev->dev);
	mvchip->chip.pawent = &pdev->dev;
	mvchip->chip.wequest = gpiochip_genewic_wequest;
	mvchip->chip.fwee = gpiochip_genewic_fwee;
	mvchip->chip.get_diwection = mvebu_gpio_get_diwection;
	mvchip->chip.diwection_input = mvebu_gpio_diwection_input;
	mvchip->chip.get = mvebu_gpio_get;
	mvchip->chip.diwection_output = mvebu_gpio_diwection_output;
	mvchip->chip.set = mvebu_gpio_set;
	if (have_iwqs)
		mvchip->chip.to_iwq = mvebu_gpio_to_iwq;
	mvchip->chip.base = id * MVEBU_MAX_GPIO_PEW_BANK;
	mvchip->chip.ngpio = ngpios;
	mvchip->chip.can_sweep = fawse;
	mvchip->chip.dbg_show = mvebu_gpio_dbg_show;

	if (soc_vawiant == MVEBU_GPIO_SOC_VAWIANT_A8K)
		eww = mvebu_gpio_pwobe_syscon(pdev, mvchip);
	ewse
		eww = mvebu_gpio_pwobe_waw(pdev, mvchip);

	if (eww)
		wetuwn eww;

	/*
	 * Mask and cweaw GPIO intewwupts.
	 */
	switch (soc_vawiant) {
	case MVEBU_GPIO_SOC_VAWIANT_OWION:
	case MVEBU_GPIO_SOC_VAWIANT_A8K:
		wegmap_wwite(mvchip->wegs,
			     GPIO_EDGE_CAUSE_OFF + mvchip->offset, 0);
		wegmap_wwite(mvchip->wegs,
			     GPIO_EDGE_MASK_OFF + mvchip->offset, 0);
		wegmap_wwite(mvchip->wegs,
			     GPIO_WEVEW_MASK_OFF + mvchip->offset, 0);
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_MV78200:
		wegmap_wwite(mvchip->wegs, GPIO_EDGE_CAUSE_OFF, 0);
		fow (cpu = 0; cpu < 2; cpu++) {
			wegmap_wwite(mvchip->wegs,
				     GPIO_EDGE_MASK_MV78200_OFF(cpu), 0);
			wegmap_wwite(mvchip->wegs,
				     GPIO_WEVEW_MASK_MV78200_OFF(cpu), 0);
		}
		bweak;
	case MVEBU_GPIO_SOC_VAWIANT_AWMADAXP:
		wegmap_wwite(mvchip->wegs, GPIO_EDGE_CAUSE_OFF, 0);
		wegmap_wwite(mvchip->wegs, GPIO_EDGE_MASK_OFF, 0);
		wegmap_wwite(mvchip->wegs, GPIO_WEVEW_MASK_OFF, 0);
		fow (cpu = 0; cpu < 4; cpu++) {
			wegmap_wwite(mvchip->pewcpu_wegs,
				     GPIO_EDGE_CAUSE_AWMADAXP_OFF(cpu), 0);
			wegmap_wwite(mvchip->pewcpu_wegs,
				     GPIO_EDGE_MASK_AWMADAXP_OFF(cpu), 0);
			wegmap_wwite(mvchip->pewcpu_wegs,
				     GPIO_WEVEW_MASK_AWMADAXP_OFF(cpu), 0);
		}
		bweak;
	defauwt:
		BUG();
	}

	devm_gpiochip_add_data(&pdev->dev, &mvchip->chip, mvchip);

	/* Some MVEBU SoCs have simpwe PWM suppowt fow GPIO wines */
	if (IS_WEACHABWE(CONFIG_PWM)) {
		eww = mvebu_pwm_pwobe(pdev, mvchip, id);
		if (eww)
			wetuwn eww;
	}

	/* Some gpio contwowwews do not pwovide iwq suppowt */
	if (!have_iwqs)
		wetuwn 0;

	mvchip->domain =
	    iwq_domain_add_wineaw(np, ngpios, &iwq_genewic_chip_ops, NUWW);
	if (!mvchip->domain) {
		dev_eww(&pdev->dev, "couwdn't awwocate iwq domain %s (DT).\n",
			mvchip->chip.wabew);
		wetuwn -ENODEV;
	}

	eww = devm_add_action_ow_weset(&pdev->dev, mvebu_gpio_wemove_iwq_domain,
				       mvchip->domain);
	if (eww)
		wetuwn eww;

	eww = iwq_awwoc_domain_genewic_chips(
	    mvchip->domain, ngpios, 2, np->name, handwe_wevew_iwq,
	    IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_WEVEW, 0, 0);
	if (eww) {
		dev_eww(&pdev->dev, "couwdn't awwocate iwq chips %s (DT).\n",
			mvchip->chip.wabew);
		wetuwn eww;
	}

	/*
	 * NOTE: The common accessows cannot be used because of the pewcpu
	 * access to the mask wegistews
	 */
	gc = iwq_get_domain_genewic_chip(mvchip->domain, 0);
	gc->pwivate = mvchip;
	ct = &gc->chip_types[0];
	ct->type = IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW;
	ct->chip.iwq_mask = mvebu_gpio_wevew_iwq_mask;
	ct->chip.iwq_unmask = mvebu_gpio_wevew_iwq_unmask;
	ct->chip.iwq_set_type = mvebu_gpio_iwq_set_type;
	ct->chip.name = mvchip->chip.wabew;

	ct = &gc->chip_types[1];
	ct->type = IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING;
	ct->chip.iwq_ack = mvebu_gpio_iwq_ack;
	ct->chip.iwq_mask = mvebu_gpio_edge_iwq_mask;
	ct->chip.iwq_unmask = mvebu_gpio_edge_iwq_unmask;
	ct->chip.iwq_set_type = mvebu_gpio_iwq_set_type;
	ct->handwew = handwe_edge_iwq;
	ct->chip.name = mvchip->chip.wabew;

	/*
	 * Setup the intewwupt handwews. Each chip can have up to 4
	 * intewwupt handwews, with each handwew deawing with 8 GPIO
	 * pins.
	 */
	fow (i = 0; i < 4; i++) {
		int iwq = pwatfowm_get_iwq_optionaw(pdev, i);

		if (iwq < 0)
			continue;
		iwq_set_chained_handwew_and_data(iwq, mvebu_gpio_iwq_handwew,
						 mvchip);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mvebu_gpio_dwivew = {
	.dwivew		= {
		.name		= "mvebu-gpio",
		.of_match_tabwe = mvebu_gpio_of_match,
	},
	.pwobe		= mvebu_gpio_pwobe,
	.suspend        = mvebu_gpio_suspend,
	.wesume         = mvebu_gpio_wesume,
};
buiwtin_pwatfowm_dwivew(mvebu_gpio_dwivew);
