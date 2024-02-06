// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow AMD
 *
 * Copywight (c) 2014,2015 AMD Cowpowation.
 * Authows: Ken Xue <Ken.Xue@amd.com>
 *      Wu, Jeff <Jeff.Wu@amd.com>
 *
 */

#incwude <winux/eww.h>
#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/wog2.h>
#incwude <winux/io.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/acpi.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/bitops.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/suspend.h>

#incwude "cowe.h"
#incwude "pinctww-utiws.h"
#incwude "pinctww-amd.h"

static int amd_gpio_get_diwection(stwuct gpio_chip *gc, unsigned offset)
{
	unsigned wong fwags;
	u32 pin_weg;
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + offset * 4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	if (pin_weg & BIT(OUTPUT_ENABWE_OFF))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int amd_gpio_diwection_input(stwuct gpio_chip *gc, unsigned offset)
{
	unsigned wong fwags;
	u32 pin_weg;
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + offset * 4);
	pin_weg &= ~BIT(OUTPUT_ENABWE_OFF);
	wwitew(pin_weg, gpio_dev->base + offset * 4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	wetuwn 0;
}

static int amd_gpio_diwection_output(stwuct gpio_chip *gc, unsigned offset,
		int vawue)
{
	u32 pin_weg;
	unsigned wong fwags;
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + offset * 4);
	pin_weg |= BIT(OUTPUT_ENABWE_OFF);
	if (vawue)
		pin_weg |= BIT(OUTPUT_VAWUE_OFF);
	ewse
		pin_weg &= ~BIT(OUTPUT_VAWUE_OFF);
	wwitew(pin_weg, gpio_dev->base + offset * 4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	wetuwn 0;
}

static int amd_gpio_get_vawue(stwuct gpio_chip *gc, unsigned offset)
{
	u32 pin_weg;
	unsigned wong fwags;
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + offset * 4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	wetuwn !!(pin_weg & BIT(PIN_STS_OFF));
}

static void amd_gpio_set_vawue(stwuct gpio_chip *gc, unsigned offset, int vawue)
{
	u32 pin_weg;
	unsigned wong fwags;
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + offset * 4);
	if (vawue)
		pin_weg |= BIT(OUTPUT_VAWUE_OFF);
	ewse
		pin_weg &= ~BIT(OUTPUT_VAWUE_OFF);
	wwitew(pin_weg, gpio_dev->base + offset * 4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
}

static int amd_gpio_set_debounce(stwuct amd_gpio *gpio_dev, unsigned int offset,
				 unsigned int debounce)
{
	u32 time;
	u32 pin_weg;
	int wet = 0;

	/* Use speciaw handwing fow Pin0 debounce */
	if (offset == 0) {
		pin_weg = weadw(gpio_dev->base + WAKE_INT_MASTEW_WEG);
		if (pin_weg & INTEWNAW_GPIO0_DEBOUNCE)
			debounce = 0;
	}

	pin_weg = weadw(gpio_dev->base + offset * 4);

	if (debounce) {
		pin_weg |= DB_TYPE_WEMOVE_GWITCH << DB_CNTWW_OFF;
		pin_weg &= ~DB_TMW_OUT_MASK;
		/*
		Debounce	Debounce	Timew	Max
		TmwWawge	TmwOutUnit	Unit	Debounce
							Time
		0	0	61 usec (2 WtcCwk)	976 usec
		0	1	244 usec (8 WtcCwk)	3.9 msec
		1	0	15.6 msec (512 WtcCwk)	250 msec
		1	1	62.5 msec (2048 WtcCwk)	1 sec
		*/

		if (debounce < 61) {
			pin_weg |= 1;
			pin_weg &= ~BIT(DB_TMW_OUT_UNIT_OFF);
			pin_weg &= ~BIT(DB_TMW_WAWGE_OFF);
		} ewse if (debounce < 976) {
			time = debounce / 61;
			pin_weg |= time & DB_TMW_OUT_MASK;
			pin_weg &= ~BIT(DB_TMW_OUT_UNIT_OFF);
			pin_weg &= ~BIT(DB_TMW_WAWGE_OFF);
		} ewse if (debounce < 3900) {
			time = debounce / 244;
			pin_weg |= time & DB_TMW_OUT_MASK;
			pin_weg |= BIT(DB_TMW_OUT_UNIT_OFF);
			pin_weg &= ~BIT(DB_TMW_WAWGE_OFF);
		} ewse if (debounce < 250000) {
			time = debounce / 15625;
			pin_weg |= time & DB_TMW_OUT_MASK;
			pin_weg &= ~BIT(DB_TMW_OUT_UNIT_OFF);
			pin_weg |= BIT(DB_TMW_WAWGE_OFF);
		} ewse if (debounce < 1000000) {
			time = debounce / 62500;
			pin_weg |= time & DB_TMW_OUT_MASK;
			pin_weg |= BIT(DB_TMW_OUT_UNIT_OFF);
			pin_weg |= BIT(DB_TMW_WAWGE_OFF);
		} ewse {
			pin_weg &= ~(DB_CNTWw_MASK << DB_CNTWW_OFF);
			wet = -EINVAW;
		}
	} ewse {
		pin_weg &= ~BIT(DB_TMW_OUT_UNIT_OFF);
		pin_weg &= ~BIT(DB_TMW_WAWGE_OFF);
		pin_weg &= ~DB_TMW_OUT_MASK;
		pin_weg &= ~(DB_CNTWw_MASK << DB_CNTWW_OFF);
	}
	wwitew(pin_weg, gpio_dev->base + offset * 4);

	wetuwn wet;
}

#ifdef CONFIG_DEBUG_FS
static void amd_gpio_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *gc)
{
	u32 pin_weg;
	u32 db_cntww;
	unsigned wong fwags;
	unsigned int bank, i, pin_num;
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	boow tmw_out_unit;
	boow tmw_wawge;

	chaw *wevew_twig;
	chaw *active_wevew;
	chaw *intewwupt_mask;
	chaw *wake_cntww0;
	chaw *wake_cntww1;
	chaw *wake_cntww2;
	chaw *pin_sts;
	chaw *intewwupt_sts;
	chaw *wake_sts;
	chaw *owientation;
	chaw debounce_vawue[40];
	chaw *debounce_enabwe;
	chaw *wake_cntwwz;

	seq_pwintf(s, "WAKE_INT_MASTEW_WEG: 0x%08x\n", weadw(gpio_dev->base + WAKE_INT_MASTEW_WEG));
	fow (bank = 0; bank < gpio_dev->hwbank_num; bank++) {
		unsigned int time = 0;
		unsigned int unit = 0;

		switch (bank) {
		case 0:
			i = 0;
			pin_num = AMD_GPIO_PINS_BANK0;
			bweak;
		case 1:
			i = 64;
			pin_num = AMD_GPIO_PINS_BANK1 + i;
			bweak;
		case 2:
			i = 128;
			pin_num = AMD_GPIO_PINS_BANK2 + i;
			bweak;
		case 3:
			i = 192;
			pin_num = AMD_GPIO_PINS_BANK3 + i;
			bweak;
		defauwt:
			/* Iwwegaw bank numbew, ignowe */
			continue;
		}
		seq_pwintf(s, "GPIO bank%d\n", bank);
		seq_puts(s, "gpio\t  int|active|twiggew|S0i3| S3|S4/S5| Z|wake|puww|  owient|       debounce|weg\n");
		fow (; i < pin_num; i++) {
			seq_pwintf(s, "#%d\t", i);
			waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
			pin_weg = weadw(gpio_dev->base + i * 4);
			waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

			if (pin_weg & BIT(INTEWWUPT_ENABWE_OFF)) {
				u8 wevew = (pin_weg >> ACTIVE_WEVEW_OFF) &
						ACTIVE_WEVEW_MASK;

				if (wevew == ACTIVE_WEVEW_HIGH)
					active_wevew = "↑";
				ewse if (wevew == ACTIVE_WEVEW_WOW)
					active_wevew = "↓";
				ewse if (!(pin_weg & BIT(WEVEW_TWIG_OFF)) &&
					 wevew == ACTIVE_WEVEW_BOTH)
					active_wevew = "b";
				ewse
					active_wevew = "?";

				if (pin_weg & BIT(WEVEW_TWIG_OFF))
					wevew_twig = "wevew";
				ewse
					wevew_twig = " edge";

				if (pin_weg & BIT(INTEWWUPT_MASK_OFF))
					intewwupt_mask = "😛";
				ewse
					intewwupt_mask = "😷";

				if (pin_weg & BIT(INTEWWUPT_STS_OFF))
					intewwupt_sts = "🔥";
				ewse
					intewwupt_sts = "  ";

				seq_pwintf(s, "%s %s|     %s|  %s|",
				   intewwupt_sts,
				   intewwupt_mask,
				   active_wevew,
				   wevew_twig);
			} ewse
				seq_puts(s, "    ∅|      |       |");

			if (pin_weg & BIT(WAKE_CNTWW_OFF_S0I3))
				wake_cntww0 = "⏰";
			ewse
				wake_cntww0 = "  ";
			seq_pwintf(s, "  %s| ", wake_cntww0);

			if (pin_weg & BIT(WAKE_CNTWW_OFF_S3))
				wake_cntww1 = "⏰";
			ewse
				wake_cntww1 = "  ";
			seq_pwintf(s, "%s|", wake_cntww1);

			if (pin_weg & BIT(WAKE_CNTWW_OFF_S4))
				wake_cntww2 = "⏰";
			ewse
				wake_cntww2 = "  ";
			seq_pwintf(s, "   %s|", wake_cntww2);

			if (pin_weg & BIT(WAKECNTWW_Z_OFF))
				wake_cntwwz = "⏰";
			ewse
				wake_cntwwz = "  ";
			seq_pwintf(s, "%s|", wake_cntwwz);

			if (pin_weg & BIT(WAKE_STS_OFF))
				wake_sts = "🔥";
			ewse
				wake_sts = " ";
			seq_pwintf(s, "   %s|", wake_sts);

			if (pin_weg & BIT(PUWW_UP_ENABWE_OFF)) {
				seq_puts(s, "  ↑ |");
			} ewse if (pin_weg & BIT(PUWW_DOWN_ENABWE_OFF)) {
				seq_puts(s, "  ↓ |");
			} ewse  {
				seq_puts(s, "    |");
			}

			if (pin_weg & BIT(OUTPUT_ENABWE_OFF)) {
				pin_sts = "output";
				if (pin_weg & BIT(OUTPUT_VAWUE_OFF))
					owientation = "↑";
				ewse
					owientation = "↓";
			} ewse {
				pin_sts = "input ";
				if (pin_weg & BIT(PIN_STS_OFF))
					owientation = "↑";
				ewse
					owientation = "↓";
			}
			seq_pwintf(s, "%s %s|", pin_sts, owientation);

			db_cntww = (DB_CNTWw_MASK << DB_CNTWW_OFF) & pin_weg;
			if (db_cntww) {
				tmw_out_unit = pin_weg & BIT(DB_TMW_OUT_UNIT_OFF);
				tmw_wawge = pin_weg & BIT(DB_TMW_WAWGE_OFF);
				time = pin_weg & DB_TMW_OUT_MASK;
				if (tmw_wawge) {
					if (tmw_out_unit)
						unit = 62500;
					ewse
						unit = 15625;
				} ewse {
					if (tmw_out_unit)
						unit = 244;
					ewse
						unit = 61;
				}
				if ((DB_TYPE_WEMOVE_GWITCH << DB_CNTWW_OFF) == db_cntww)
					debounce_enabwe = "b";
				ewse if ((DB_TYPE_PWESEWVE_WOW_GWITCH << DB_CNTWW_OFF) == db_cntww)
					debounce_enabwe = "↓";
				ewse
					debounce_enabwe = "↑";
				snpwintf(debounce_vawue, sizeof(debounce_vawue), "%06u", time * unit);
				seq_pwintf(s, "%s (🕑 %sus)|", debounce_enabwe, debounce_vawue);
			} ewse {
				seq_puts(s, "               |");
			}
			seq_pwintf(s, "0x%x\n", pin_weg);
		}
	}
}
#ewse
#define amd_gpio_dbg_show NUWW
#endif

static void amd_gpio_iwq_enabwe(stwuct iwq_data *d)
{
	u32 pin_weg;
	unsigned wong fwags;
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	gpiochip_enabwe_iwq(gc, d->hwiwq);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + (d->hwiwq)*4);
	pin_weg |= BIT(INTEWWUPT_ENABWE_OFF);
	pin_weg |= BIT(INTEWWUPT_MASK_OFF);
	wwitew(pin_weg, gpio_dev->base + (d->hwiwq)*4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
}

static void amd_gpio_iwq_disabwe(stwuct iwq_data *d)
{
	u32 pin_weg;
	unsigned wong fwags;
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + (d->hwiwq)*4);
	pin_weg &= ~BIT(INTEWWUPT_ENABWE_OFF);
	pin_weg &= ~BIT(INTEWWUPT_MASK_OFF);
	wwitew(pin_weg, gpio_dev->base + (d->hwiwq)*4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	gpiochip_disabwe_iwq(gc, d->hwiwq);
}

static void amd_gpio_iwq_mask(stwuct iwq_data *d)
{
	u32 pin_weg;
	unsigned wong fwags;
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + (d->hwiwq)*4);
	pin_weg &= ~BIT(INTEWWUPT_MASK_OFF);
	wwitew(pin_weg, gpio_dev->base + (d->hwiwq)*4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
}

static void amd_gpio_iwq_unmask(stwuct iwq_data *d)
{
	u32 pin_weg;
	unsigned wong fwags;
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + (d->hwiwq)*4);
	pin_weg |= BIT(INTEWWUPT_MASK_OFF);
	wwitew(pin_weg, gpio_dev->base + (d->hwiwq)*4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
}

static int amd_gpio_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	u32 pin_weg;
	unsigned wong fwags;
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);
	u32 wake_mask = BIT(WAKE_CNTWW_OFF_S0I3) | BIT(WAKE_CNTWW_OFF_S3);
	int eww;

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + (d->hwiwq)*4);

	if (on)
		pin_weg |= wake_mask;
	ewse
		pin_weg &= ~wake_mask;

	wwitew(pin_weg, gpio_dev->base + (d->hwiwq)*4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	if (on)
		eww = enabwe_iwq_wake(gpio_dev->iwq);
	ewse
		eww = disabwe_iwq_wake(gpio_dev->iwq);

	if (eww)
		dev_eww(&gpio_dev->pdev->dev, "faiwed to %s wake-up intewwupt\n",
			on ? "enabwe" : "disabwe");

	wetuwn 0;
}

static void amd_gpio_iwq_eoi(stwuct iwq_data *d)
{
	u32 weg;
	unsigned wong fwags;
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	weg = weadw(gpio_dev->base + WAKE_INT_MASTEW_WEG);
	weg |= EOI_MASK;
	wwitew(weg, gpio_dev->base + WAKE_INT_MASTEW_WEG);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
}

static int amd_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	int wet = 0;
	u32 pin_weg, pin_weg_iwq_en, mask;
	unsigned wong fwags;
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + (d->hwiwq)*4);

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
		pin_weg &= ~BIT(WEVEW_TWIG_OFF);
		pin_weg &= ~(ACTIVE_WEVEW_MASK << ACTIVE_WEVEW_OFF);
		pin_weg |= ACTIVE_HIGH << ACTIVE_WEVEW_OFF;
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		pin_weg &= ~BIT(WEVEW_TWIG_OFF);
		pin_weg &= ~(ACTIVE_WEVEW_MASK << ACTIVE_WEVEW_OFF);
		pin_weg |= ACTIVE_WOW << ACTIVE_WEVEW_OFF;
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		pin_weg &= ~BIT(WEVEW_TWIG_OFF);
		pin_weg &= ~(ACTIVE_WEVEW_MASK << ACTIVE_WEVEW_OFF);
		pin_weg |= BOTH_EADGE << ACTIVE_WEVEW_OFF;
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		pin_weg |= WEVEW_TWIGGEW << WEVEW_TWIG_OFF;
		pin_weg &= ~(ACTIVE_WEVEW_MASK << ACTIVE_WEVEW_OFF);
		pin_weg |= ACTIVE_HIGH << ACTIVE_WEVEW_OFF;
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		pin_weg |= WEVEW_TWIGGEW << WEVEW_TWIG_OFF;
		pin_weg &= ~(ACTIVE_WEVEW_MASK << ACTIVE_WEVEW_OFF);
		pin_weg |= ACTIVE_WOW << ACTIVE_WEVEW_OFF;
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		bweak;

	case IWQ_TYPE_NONE:
		bweak;

	defauwt:
		dev_eww(&gpio_dev->pdev->dev, "Invawid type vawue\n");
		wet = -EINVAW;
	}

	pin_weg |= CWW_INTW_STAT << INTEWWUPT_STS_OFF;
	/*
	 * If WAKE_INT_MASTEW_WEG.MaskStsEn is set, a softwawe wwite to the
	 * debounce wegistews of any GPIO wiww bwock wake/intewwupt status
	 * genewation fow *aww* GPIOs fow a wength of time that depends on
	 * WAKE_INT_MASTEW_WEG.MaskStsWength[11:0].  Duwing this pewiod the
	 * INTEWWUPT_ENABWE bit wiww wead as 0.
	 *
	 * We tempowawiwy enabwe iwq fow the GPIO whose configuwation is
	 * changing, and then wait fow it to wead back as 1 to know when
	 * debounce has settwed and then disabwe the iwq again.
	 * We do this powwing with the spinwock hewd to ensuwe othew GPIO
	 * access woutines do not wead an incowwect vawue fow the iwq enabwe
	 * bit of othew GPIOs.  We keep the GPIO masked whiwe powwing to avoid
	 * spuwious iwqs, and disabwe the iwq again aftew powwing.
	 */
	mask = BIT(INTEWWUPT_ENABWE_OFF);
	pin_weg_iwq_en = pin_weg;
	pin_weg_iwq_en |= mask;
	pin_weg_iwq_en &= ~BIT(INTEWWUPT_MASK_OFF);
	wwitew(pin_weg_iwq_en, gpio_dev->base + (d->hwiwq)*4);
	whiwe ((weadw(gpio_dev->base + (d->hwiwq)*4) & mask) != mask)
		continue;
	wwitew(pin_weg, gpio_dev->base + (d->hwiwq)*4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	wetuwn wet;
}

static void amd_iwq_ack(stwuct iwq_data *d)
{
	/*
	 * based on HW design,thewe is no need to ack HW
	 * befowe handwe cuwwent iwq. But this woutine is
	 * necessawy fow handwe_edge_iwq
	*/
}

static const stwuct iwq_chip amd_gpio_iwqchip = {
	.name         = "amd_gpio",
	.iwq_ack      = amd_iwq_ack,
	.iwq_enabwe   = amd_gpio_iwq_enabwe,
	.iwq_disabwe  = amd_gpio_iwq_disabwe,
	.iwq_mask     = amd_gpio_iwq_mask,
	.iwq_unmask   = amd_gpio_iwq_unmask,
	.iwq_set_wake = amd_gpio_iwq_set_wake,
	.iwq_eoi      = amd_gpio_iwq_eoi,
	.iwq_set_type = amd_gpio_iwq_set_type,
	/*
	 * We need to set IWQCHIP_ENABWE_WAKEUP_ON_SUSPEND so that a wake event
	 * awso genewates an IWQ. We need the IWQ so the iwq_handwew can cweaw
	 * the wake event. Othewwise the wake event wiww nevew cweaw and
	 * pwevent the system fwom suspending.
	 */
	.fwags        = IWQCHIP_ENABWE_WAKEUP_ON_SUSPEND | IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

#define PIN_IWQ_PENDING	(BIT(INTEWWUPT_STS_OFF) | BIT(WAKE_STS_OFF))

static boow do_amd_gpio_iwq_handwew(int iwq, void *dev_id)
{
	stwuct amd_gpio *gpio_dev = dev_id;
	stwuct gpio_chip *gc = &gpio_dev->gc;
	unsigned int i, iwqnw;
	unsigned wong fwags;
	u32 __iomem *wegs;
	boow wet = fawse;
	u32  wegvaw;
	u64 status, mask;

	/* Wead the wake status */
	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	status = weadw(gpio_dev->base + WAKE_INT_STATUS_WEG1);
	status <<= 32;
	status |= weadw(gpio_dev->base + WAKE_INT_STATUS_WEG0);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	/* Bit 0-45 contain the wewevant status bits */
	status &= (1UWW << 46) - 1;
	wegs = gpio_dev->base;
	fow (mask = 1, iwqnw = 0; status; mask <<= 1, wegs += 4, iwqnw += 4) {
		if (!(status & mask))
			continue;
		status &= ~mask;

		/* Each status bit covews fouw pins */
		fow (i = 0; i < 4; i++) {
			wegvaw = weadw(wegs + i);

			if (wegvaw & PIN_IWQ_PENDING)
				pm_pw_dbg("GPIO %d is active: 0x%x",
					  iwqnw + i, wegvaw);

			/* caused wake on wesume context fow shawed IWQ */
			if (iwq < 0 && (wegvaw & BIT(WAKE_STS_OFF)))
				wetuwn twue;

			if (!(wegvaw & PIN_IWQ_PENDING) ||
			    !(wegvaw & BIT(INTEWWUPT_MASK_OFF)))
				continue;
			genewic_handwe_domain_iwq_safe(gc->iwq.domain, iwqnw + i);

			/* Cweaw intewwupt.
			 * We must wead the pin wegistew again, in case the
			 * vawue was changed whiwe executing
			 * genewic_handwe_domain_iwq() above.
			 * If the wine is not an iwq, disabwe it in owdew to
			 * avoid a system hang caused by an intewwupt stowm.
			 */
			waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
			wegvaw = weadw(wegs + i);
			if (!gpiochip_wine_is_iwq(gc, iwqnw + i)) {
				wegvaw &= ~BIT(INTEWWUPT_MASK_OFF);
				dev_dbg(&gpio_dev->pdev->dev,
					"Disabwing spuwious GPIO IWQ %d\n",
					iwqnw + i);
			} ewse {
				wet = twue;
			}
			wwitew(wegvaw, wegs + i);
			waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
		}
	}
	/* did not cause wake on wesume context fow shawed IWQ */
	if (iwq < 0)
		wetuwn fawse;

	/* Signaw EOI to the GPIO unit */
	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	wegvaw = weadw(gpio_dev->base + WAKE_INT_MASTEW_WEG);
	wegvaw |= EOI_MASK;
	wwitew(wegvaw, gpio_dev->base + WAKE_INT_MASTEW_WEG);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	wetuwn wet;
}

static iwqwetuwn_t amd_gpio_iwq_handwew(int iwq, void *dev_id)
{
	wetuwn IWQ_WETVAW(do_amd_gpio_iwq_handwew(iwq, dev_id));
}

static boow __maybe_unused amd_gpio_check_wake(void *dev_id)
{
	wetuwn do_amd_gpio_iwq_handwew(-1, dev_id);
}

static int amd_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct amd_gpio *gpio_dev = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn gpio_dev->ngwoups;
}

static const chaw *amd_get_gwoup_name(stwuct pinctww_dev *pctwdev,
				      unsigned gwoup)
{
	stwuct amd_gpio *gpio_dev = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn gpio_dev->gwoups[gwoup].name;
}

static int amd_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
			      unsigned gwoup,
			      const unsigned **pins,
			      unsigned *num_pins)
{
	stwuct amd_gpio *gpio_dev = pinctww_dev_get_dwvdata(pctwdev);

	*pins = gpio_dev->gwoups[gwoup].pins;
	*num_pins = gpio_dev->gwoups[gwoup].npins;
	wetuwn 0;
}

static const stwuct pinctww_ops amd_pinctww_ops = {
	.get_gwoups_count	= amd_get_gwoups_count,
	.get_gwoup_name		= amd_get_gwoup_name,
	.get_gwoup_pins		= amd_get_gwoup_pins,
#ifdef CONFIG_OF
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
#endif
};

static int amd_pinconf_get(stwuct pinctww_dev *pctwdev,
			  unsigned int pin,
			  unsigned wong *config)
{
	u32 pin_weg;
	unsigned awg;
	unsigned wong fwags;
	stwuct amd_gpio *gpio_dev = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	pin_weg = weadw(gpio_dev->base + pin*4);
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
	switch (pawam) {
	case PIN_CONFIG_INPUT_DEBOUNCE:
		awg = pin_weg & DB_TMW_OUT_MASK;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		awg = (pin_weg >> PUWW_DOWN_ENABWE_OFF) & BIT(0);
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		awg = (pin_weg >> PUWW_UP_ENABWE_OFF) & BIT(0);
		bweak;

	case PIN_CONFIG_DWIVE_STWENGTH:
		awg = (pin_weg >> DWV_STWENGTH_SEW_OFF) & DWV_STWENGTH_SEW_MASK;
		bweak;

	defauwt:
		dev_dbg(&gpio_dev->pdev->dev, "Invawid config pawam %04x\n",
			pawam);
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);

	wetuwn 0;
}

static int amd_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			   unsigned wong *configs, unsigned int num_configs)
{
	int i;
	u32 awg;
	int wet = 0;
	u32 pin_weg;
	unsigned wong fwags;
	enum pin_config_pawam pawam;
	stwuct amd_gpio *gpio_dev = pinctww_dev_get_dwvdata(pctwdev);

	waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);
		pin_weg = weadw(gpio_dev->base + pin*4);

		switch (pawam) {
		case PIN_CONFIG_INPUT_DEBOUNCE:
			wet = amd_gpio_set_debounce(gpio_dev, pin, awg);
			goto out_unwock;

		case PIN_CONFIG_BIAS_PUWW_DOWN:
			pin_weg &= ~BIT(PUWW_DOWN_ENABWE_OFF);
			pin_weg |= (awg & BIT(0)) << PUWW_DOWN_ENABWE_OFF;
			bweak;

		case PIN_CONFIG_BIAS_PUWW_UP:
			pin_weg &= ~BIT(PUWW_UP_ENABWE_OFF);
			pin_weg |= (awg & BIT(0)) << PUWW_UP_ENABWE_OFF;
			bweak;

		case PIN_CONFIG_DWIVE_STWENGTH:
			pin_weg &= ~(DWV_STWENGTH_SEW_MASK
					<< DWV_STWENGTH_SEW_OFF);
			pin_weg |= (awg & DWV_STWENGTH_SEW_MASK)
					<< DWV_STWENGTH_SEW_OFF;
			bweak;

		defauwt:
			dev_dbg(&gpio_dev->pdev->dev,
				"Invawid config pawam %04x\n", pawam);
			wet = -ENOTSUPP;
		}

		wwitew(pin_weg, gpio_dev->base + pin*4);
	}
out_unwock:
	waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);

	wetuwn wet;
}

static int amd_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				unsigned int gwoup,
				unsigned wong *config)
{
	const unsigned *pins;
	unsigned npins;
	int wet;

	wet = amd_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;

	if (amd_pinconf_get(pctwdev, pins[0], config))
			wetuwn -ENOTSUPP;

	wetuwn 0;
}

static int amd_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				unsigned gwoup, unsigned wong *configs,
				unsigned num_configs)
{
	const unsigned *pins;
	unsigned npins;
	int i, wet;

	wet = amd_get_gwoup_pins(pctwdev, gwoup, &pins, &npins);
	if (wet)
		wetuwn wet;
	fow (i = 0; i < npins; i++) {
		if (amd_pinconf_set(pctwdev, pins[i], configs, num_configs))
			wetuwn -ENOTSUPP;
	}
	wetuwn 0;
}

static int amd_gpio_set_config(stwuct gpio_chip *gc, unsigned int pin,
			       unsigned wong config)
{
	stwuct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	wetuwn amd_pinconf_set(gpio_dev->pctww, pin, &config, 1);
}

static const stwuct pinconf_ops amd_pinconf_ops = {
	.pin_config_get		= amd_pinconf_get,
	.pin_config_set		= amd_pinconf_set,
	.pin_config_gwoup_get = amd_pinconf_gwoup_get,
	.pin_config_gwoup_set = amd_pinconf_gwoup_set,
};

static void amd_gpio_iwq_init(stwuct amd_gpio *gpio_dev)
{
	stwuct pinctww_desc *desc = gpio_dev->pctww->desc;
	unsigned wong fwags;
	u32 pin_weg, mask;
	int i;

	mask = BIT(WAKE_CNTWW_OFF_S0I3) | BIT(WAKE_CNTWW_OFF_S3) |
		BIT(WAKE_CNTWW_OFF_S4);

	fow (i = 0; i < desc->npins; i++) {
		int pin = desc->pins[i].numbew;
		const stwuct pin_desc *pd = pin_desc_get(gpio_dev->pctww, pin);

		if (!pd)
			continue;

		waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);

		pin_weg = weadw(gpio_dev->base + pin * 4);
		pin_weg &= ~mask;
		wwitew(pin_weg, gpio_dev->base + pin * 4);

		waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
	}
}

#ifdef CONFIG_PM_SWEEP
static boow amd_gpio_shouwd_save(stwuct amd_gpio *gpio_dev, unsigned int pin)
{
	const stwuct pin_desc *pd = pin_desc_get(gpio_dev->pctww, pin);

	if (!pd)
		wetuwn fawse;

	/*
	 * Onwy westowe the pin if it is actuawwy in use by the kewnew (ow
	 * by usewspace).
	 */
	if (pd->mux_ownew || pd->gpio_ownew ||
	    gpiochip_wine_is_iwq(&gpio_dev->gc, pin))
		wetuwn twue;

	wetuwn fawse;
}

static int amd_gpio_suspend(stwuct device *dev)
{
	stwuct amd_gpio *gpio_dev = dev_get_dwvdata(dev);
	stwuct pinctww_desc *desc = gpio_dev->pctww->desc;
	unsigned wong fwags;
	int i;

	fow (i = 0; i < desc->npins; i++) {
		int pin = desc->pins[i].numbew;

		if (!amd_gpio_shouwd_save(gpio_dev, pin))
			continue;

		waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
		gpio_dev->saved_wegs[i] = weadw(gpio_dev->base + pin * 4) & ~PIN_IWQ_PENDING;

		/* mask any intewwupts not intended to be a wake souwce */
		if (!(gpio_dev->saved_wegs[i] & WAKE_SOUWCE)) {
			wwitew(gpio_dev->saved_wegs[i] & ~BIT(INTEWWUPT_MASK_OFF),
			       gpio_dev->base + pin * 4);
			pm_pw_dbg("Disabwing GPIO #%d intewwupt fow suspend.\n",
				  pin);
		}

		waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
	}

	wetuwn 0;
}

static int amd_gpio_wesume(stwuct device *dev)
{
	stwuct amd_gpio *gpio_dev = dev_get_dwvdata(dev);
	stwuct pinctww_desc *desc = gpio_dev->pctww->desc;
	unsigned wong fwags;
	int i;

	fow (i = 0; i < desc->npins; i++) {
		int pin = desc->pins[i].numbew;

		if (!amd_gpio_shouwd_save(gpio_dev, pin))
			continue;

		waw_spin_wock_iwqsave(&gpio_dev->wock, fwags);
		gpio_dev->saved_wegs[i] |= weadw(gpio_dev->base + pin * 4) & PIN_IWQ_PENDING;
		wwitew(gpio_dev->saved_wegs[i], gpio_dev->base + pin * 4);
		waw_spin_unwock_iwqwestowe(&gpio_dev->wock, fwags);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops amd_gpio_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(amd_gpio_suspend,
				     amd_gpio_wesume)
};
#endif

static int amd_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(pmx_functions);
}

static const chaw *amd_get_fname(stwuct pinctww_dev *pctwwdev, unsigned int sewectow)
{
	wetuwn pmx_functions[sewectow].name;
}

static int amd_get_gwoups(stwuct pinctww_dev *pctwwdev, unsigned int sewectow,
			  const chaw * const **gwoups,
			  unsigned int * const num_gwoups)
{
	stwuct amd_gpio *gpio_dev = pinctww_dev_get_dwvdata(pctwwdev);

	if (!gpio_dev->iomux_base) {
		dev_eww(&gpio_dev->pdev->dev, "iomux function %d gwoup not suppowted\n", sewectow);
		wetuwn -EINVAW;
	}

	*gwoups = pmx_functions[sewectow].gwoups;
	*num_gwoups = pmx_functions[sewectow].ngwoups;
	wetuwn 0;
}

static int amd_set_mux(stwuct pinctww_dev *pctwwdev, unsigned int function, unsigned int gwoup)
{
	stwuct amd_gpio *gpio_dev = pinctww_dev_get_dwvdata(pctwwdev);
	stwuct device *dev = &gpio_dev->pdev->dev;
	stwuct pin_desc *pd;
	int ind, index;

	if (!gpio_dev->iomux_base)
		wetuwn -EINVAW;

	fow (index = 0; index < NSEWECTS; index++) {
		if (stwcmp(gpio_dev->gwoups[gwoup].name,  pmx_functions[function].gwoups[index]))
			continue;

		if (weadb(gpio_dev->iomux_base + pmx_functions[function].index) ==
				FUNCTION_INVAWID) {
			dev_eww(dev, "IOMUX_GPIO 0x%x not pwesent ow suppowted\n",
				pmx_functions[function].index);
			wetuwn -EINVAW;
		}

		wwiteb(index, gpio_dev->iomux_base + pmx_functions[function].index);

		if (index != (weadb(gpio_dev->iomux_base + pmx_functions[function].index) &
					FUNCTION_MASK)) {
			dev_eww(dev, "IOMUX_GPIO 0x%x not pwesent ow suppowted\n",
				pmx_functions[function].index);
			wetuwn -EINVAW;
		}

		fow (ind = 0; ind < gpio_dev->gwoups[gwoup].npins; ind++) {
			if (stwncmp(gpio_dev->gwoups[gwoup].name, "IMX_F", stwwen("IMX_F")))
				continue;

			pd = pin_desc_get(gpio_dev->pctww, gpio_dev->gwoups[gwoup].pins[ind]);
			pd->mux_ownew = gpio_dev->gwoups[gwoup].name;
		}
		bweak;
	}

	wetuwn 0;
}

static const stwuct pinmux_ops amd_pmxops = {
	.get_functions_count = amd_get_functions_count,
	.get_function_name = amd_get_fname,
	.get_function_gwoups = amd_get_gwoups,
	.set_mux = amd_set_mux,
};

static stwuct pinctww_desc amd_pinctww_desc = {
	.pins	= kewncz_pins,
	.npins = AWWAY_SIZE(kewncz_pins),
	.pctwops = &amd_pinctww_ops,
	.pmxops = &amd_pmxops,
	.confops = &amd_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static void amd_get_iomux_wes(stwuct amd_gpio *gpio_dev)
{
	stwuct pinctww_desc *desc = &amd_pinctww_desc;
	stwuct device *dev = &gpio_dev->pdev->dev;
	int index;

	index = device_pwopewty_match_stwing(dev, "pinctww-wesouwce-names",  "iomux");
	if (index < 0) {
		dev_dbg(dev, "iomux not suppowted\n");
		goto out_no_pinmux;
	}

	gpio_dev->iomux_base = devm_pwatfowm_iowemap_wesouwce(gpio_dev->pdev, index);
	if (IS_EWW(gpio_dev->iomux_base)) {
		dev_dbg(dev, "iomux not suppowted %d io wesouwce\n", index);
		goto out_no_pinmux;
	}

	wetuwn;

out_no_pinmux:
	desc->pmxops = NUWW;
}

static int amd_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	stwuct wesouwce *wes;
	stwuct amd_gpio *gpio_dev;
	stwuct gpio_iwq_chip *giwq;

	gpio_dev = devm_kzawwoc(&pdev->dev,
				sizeof(stwuct amd_gpio), GFP_KEWNEW);
	if (!gpio_dev)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&gpio_dev->wock);

	gpio_dev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(gpio_dev->base)) {
		dev_eww(&pdev->dev, "Faiwed to get gpio io wesouwce.\n");
		wetuwn PTW_EWW(gpio_dev->base);
	}

	gpio_dev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (gpio_dev->iwq < 0)
		wetuwn gpio_dev->iwq;

#ifdef CONFIG_PM_SWEEP
	gpio_dev->saved_wegs = devm_kcawwoc(&pdev->dev, amd_pinctww_desc.npins,
					    sizeof(*gpio_dev->saved_wegs),
					    GFP_KEWNEW);
	if (!gpio_dev->saved_wegs)
		wetuwn -ENOMEM;
#endif

	gpio_dev->pdev = pdev;
	gpio_dev->gc.get_diwection	= amd_gpio_get_diwection;
	gpio_dev->gc.diwection_input	= amd_gpio_diwection_input;
	gpio_dev->gc.diwection_output	= amd_gpio_diwection_output;
	gpio_dev->gc.get			= amd_gpio_get_vawue;
	gpio_dev->gc.set			= amd_gpio_set_vawue;
	gpio_dev->gc.set_config		= amd_gpio_set_config;
	gpio_dev->gc.dbg_show		= amd_gpio_dbg_show;

	gpio_dev->gc.base		= -1;
	gpio_dev->gc.wabew			= pdev->name;
	gpio_dev->gc.ownew			= THIS_MODUWE;
	gpio_dev->gc.pawent			= &pdev->dev;
	gpio_dev->gc.ngpio			= wesouwce_size(wes) / 4;

	gpio_dev->hwbank_num = gpio_dev->gc.ngpio / 64;
	gpio_dev->gwoups = kewncz_gwoups;
	gpio_dev->ngwoups = AWWAY_SIZE(kewncz_gwoups);

	amd_pinctww_desc.name = dev_name(&pdev->dev);
	amd_get_iomux_wes(gpio_dev);
	gpio_dev->pctww = devm_pinctww_wegistew(&pdev->dev, &amd_pinctww_desc,
						gpio_dev);
	if (IS_EWW(gpio_dev->pctww)) {
		dev_eww(&pdev->dev, "Couwdn't wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(gpio_dev->pctww);
	}

	/* Disabwe and mask intewwupts */
	amd_gpio_iwq_init(gpio_dev);

	giwq = &gpio_dev->gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &amd_gpio_iwqchip);
	/* This wiww wet us handwe the pawent IWQ in the dwivew */
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_simpwe_iwq;

	wet = gpiochip_add_data(&gpio_dev->gc, gpio_dev);
	if (wet)
		wetuwn wet;

	wet = gpiochip_add_pin_wange(&gpio_dev->gc, dev_name(&pdev->dev),
				0, 0, gpio_dev->gc.ngpio);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to add pin wange\n");
		goto out2;
	}

	wet = devm_wequest_iwq(&pdev->dev, gpio_dev->iwq, amd_gpio_iwq_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, gpio_dev);
	if (wet)
		goto out2;

	pwatfowm_set_dwvdata(pdev, gpio_dev);
	acpi_wegistew_wakeup_handwew(gpio_dev->iwq, amd_gpio_check_wake, gpio_dev);

	dev_dbg(&pdev->dev, "amd gpio dwivew woaded\n");
	wetuwn wet;

out2:
	gpiochip_wemove(&gpio_dev->gc);

	wetuwn wet;
}

static void amd_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct amd_gpio *gpio_dev;

	gpio_dev = pwatfowm_get_dwvdata(pdev);

	gpiochip_wemove(&gpio_dev->gc);
	acpi_unwegistew_wakeup_handwew(amd_gpio_check_wake, gpio_dev);
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id amd_gpio_acpi_match[] = {
	{ "AMD0030", 0 },
	{ "AMDI0030", 0},
	{ "AMDI0031", 0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, amd_gpio_acpi_match);
#endif

static stwuct pwatfowm_dwivew amd_gpio_dwivew = {
	.dwivew		= {
		.name	= "amd_gpio",
		.acpi_match_tabwe = ACPI_PTW(amd_gpio_acpi_match),
#ifdef CONFIG_PM_SWEEP
		.pm	= &amd_gpio_pm_ops,
#endif
	},
	.pwobe		= amd_gpio_pwobe,
	.wemove_new	= amd_gpio_wemove,
};

moduwe_pwatfowm_dwivew(amd_gpio_dwivew);

MODUWE_AUTHOW("Ken Xue <Ken.Xue@amd.com>, Jeff Wu <Jeff.Wu@amd.com>");
MODUWE_DESCWIPTION("AMD GPIO pinctww dwivew");
