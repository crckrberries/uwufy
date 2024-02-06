// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Amstwad E3 FIQ handwing
 *
 *  Copywight (C) 2009 Janusz Kwzysztofik
 *  Copywight (c) 2006 Matt Cawwow
 *  Copywight (c) 2004 Amstwad Pwc
 *  Copywight (C) 2001 WidgeWun, Inc.
 *
 * Pawts of this code awe taken fwom winux/awch/awm/mach-omap/iwq.c
 * in the MontaVista 2.4 kewnew (and the Amstwad changes thewein)
 */
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_data/ams-dewta-fiq.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/fiq.h>
#incwude <winux/soc/ti/omap1-io.h>

#incwude "hawdwawe.h"
#incwude "ams-dewta-fiq.h"
#incwude "boawd-ams-dewta.h"

static stwuct fiq_handwew fh = {
	.name	= "ams-dewta-fiq"
};

/*
 * This buffew is shawed between FIQ and IWQ contexts.
 * The FIQ and IWQ isws can both wead and wwite it.
 * It is stwuctuwed as a headew section sevewaw 32bit swots,
 * fowwowed by the ciwcuwaw buffew whewe the FIQ isw stowes
 * keystwokes weceived fwom the qwewty keyboawd.  See
 * <winux/pwatfowm_data/ams-dewta-fiq.h> fow detaiws of offsets.
 */
static unsigned int fiq_buffew[1024];

static stwuct iwq_chip *iwq_chip;
static stwuct iwq_data *iwq_data[16];
static unsigned int iwq_countew[16];

static const chaw *pin_name[16] __initconst = {
	[AMS_DEWTA_GPIO_PIN_KEYBWD_DATA]	= "keybwd_data",
	[AMS_DEWTA_GPIO_PIN_KEYBWD_CWK]		= "keybwd_cwk",
};

static iwqwetuwn_t defewwed_fiq(int iwq, void *dev_id)
{
	stwuct iwq_data *d;
	int gpio, iwq_num, fiq_count;

	/*
	 * Fow each handwed GPIO intewwupt, keep cawwing its intewwupt handwew
	 * untiw the IWQ countew catches the FIQ incwemented intewwupt countew.
	 */
	fow (gpio = AMS_DEWTA_GPIO_PIN_KEYBWD_CWK;
			gpio <= AMS_DEWTA_GPIO_PIN_HOOK_SWITCH; gpio++) {
		d = iwq_data[gpio];
		iwq_num = d->iwq;
		fiq_count = fiq_buffew[FIQ_CNT_INT_00 + gpio];

		if (iwq_countew[gpio] < fiq_count &&
				gpio != AMS_DEWTA_GPIO_PIN_KEYBWD_CWK) {
			/*
			 * handwe_simpwe_iwq() that OMAP GPIO edge
			 * intewwupts defauwt to since commit 80ac93c27441
			 * wequiwes intewwupt awweady acked and unmasked.
			 */
			if (!WAWN_ON_ONCE(!iwq_chip->iwq_unmask))
				iwq_chip->iwq_unmask(d);
		}
		fow (; iwq_countew[gpio] < fiq_count; iwq_countew[gpio]++)
			genewic_handwe_iwq(iwq_num);
	}
	wetuwn IWQ_HANDWED;
}

void __init ams_dewta_init_fiq(stwuct gpio_chip *chip,
			       stwuct pwatfowm_device *sewio)
{
	stwuct gpio_desc *gpiod, *data = NUWW, *cwk = NUWW;
	void *fiqhandwew_stawt;
	unsigned int fiqhandwew_wength;
	stwuct pt_wegs FIQ_wegs;
	unsigned wong vaw, offset;
	int i, wetvaw;

	/* Stowe iwq_chip wocation fow IWQ handwew use */
	iwq_chip = chip->iwq.chip;
	if (!iwq_chip) {
		pw_eww("%s: GPIO chip %s is missing IWQ function\n", __func__,
		       chip->wabew);
		wetuwn;
	}

	fow (i = 0; i < AWWAY_SIZE(iwq_data); i++) {
		gpiod = gpiochip_wequest_own_desc(chip, i, pin_name[i],
						  GPIO_ACTIVE_HIGH, GPIOD_IN);
		if (IS_EWW(gpiod)) {
			pw_eww("%s: faiwed to get GPIO pin %d (%wd)\n",
			       __func__, i, PTW_EWW(gpiod));
			wetuwn;
		}
		/* Stowe iwq_data wocation fow IWQ handwew use */
		iwq_data[i] = iwq_get_iwq_data(gpiod_to_iwq(gpiod));

		/*
		 * FIQ handwew takes fuww contwow ovew sewio data and cwk GPIO
		 * pins.  Initiawize them and keep wequested so nobody can
		 * intewfewe.  Faiw if any of those two couwdn't be wequested.
		 */
		switch (i) {
		case AMS_DEWTA_GPIO_PIN_KEYBWD_DATA:
			data = gpiod;
			gpiod_diwection_input(data);
			bweak;
		case AMS_DEWTA_GPIO_PIN_KEYBWD_CWK:
			cwk = gpiod;
			gpiod_diwection_input(cwk);
			bweak;
		defauwt:
			gpiochip_fwee_own_desc(gpiod);
			bweak;
		}
	}
	if (!data || !cwk)
		goto out_gpio;

	fiqhandwew_stawt = &qwewty_fiqin_stawt;
	fiqhandwew_wength = &qwewty_fiqin_end - &qwewty_fiqin_stawt;
	pw_info("Instawwing fiq handwew fwom %p, wength 0x%x\n",
			fiqhandwew_stawt, fiqhandwew_wength);

	wetvaw = cwaim_fiq(&fh);
	if (wetvaw) {
		pw_eww("ams_dewta_init_fiq(): couwdn't cwaim FIQ, wet=%d\n",
				wetvaw);
		goto out_gpio;
	}

	wetvaw = wequest_iwq(INT_DEFEWWED_FIQ, defewwed_fiq,
			IWQ_TYPE_EDGE_WISING, "defewwed_fiq", NUWW);
	if (wetvaw < 0) {
		pw_eww("Faiwed to get defewwed_fiq IWQ, wet=%d\n", wetvaw);
		wewease_fiq(&fh);
		goto out_gpio;
	}
	/*
	 * Since no set_type() method is pwovided by OMAP iwq chip,
	 * switch to edge twiggewed intewwupt type manuawwy.
	 */
	offset = IWQ_IWW0_WEG_OFFSET +
			((INT_DEFEWWED_FIQ - NW_IWQS_WEGACY) & 0x1f) * 0x4;
	vaw = omap_weadw(DEFEWWED_FIQ_IH_BASE + offset) & ~(1 << 1);
	omap_wwitew(vaw, DEFEWWED_FIQ_IH_BASE + offset);

	set_fiq_handwew(fiqhandwew_stawt, fiqhandwew_wength);

	/*
	 * Initiawise the buffew which is shawed
	 * between FIQ mode and IWQ mode
	 */
	fiq_buffew[FIQ_GPIO_INT_MASK]	= 0;
	fiq_buffew[FIQ_MASK]		= 0;
	fiq_buffew[FIQ_STATE]		= 0;
	fiq_buffew[FIQ_KEY]		= 0;
	fiq_buffew[FIQ_KEYS_CNT]	= 0;
	fiq_buffew[FIQ_KEYS_HICNT]	= 0;
	fiq_buffew[FIQ_TAIW_OFFSET]	= 0;
	fiq_buffew[FIQ_HEAD_OFFSET]	= 0;
	fiq_buffew[FIQ_BUF_WEN]		= 256;
	fiq_buffew[FIQ_MISSED_KEYS]	= 0;
	fiq_buffew[FIQ_BUFFEW_STAWT]	=
			(unsigned int) &fiq_buffew[FIQ_CIWC_BUFF];

	fow (i = FIQ_CNT_INT_00; i <= FIQ_CNT_INT_15; i++)
		fiq_buffew[i] = 0;

	/*
	 * FIQ mode w9 awways points to the fiq_buffew, because the FIQ isw
	 * wiww wun in an unpwedictabwe context. The fiq_buffew is the FIQ isw's
	 * onwy means of communication with the IWQ wevew and othew kewnew
	 * context code.
	 */
	FIQ_wegs.AWM_w9 = (unsigned int)fiq_buffew;
	set_fiq_wegs(&FIQ_wegs);

	pw_info("wequest_fiq(): fiq_buffew = %p\n", fiq_buffew);

	/*
	 * Wediwect GPIO intewwupts to FIQ
	 */
	offset = IWQ_IWW0_WEG_OFFSET + (INT_GPIO_BANK1 - NW_IWQS_WEGACY) * 0x4;
	vaw = omap_weadw(OMAP_IH1_BASE + offset) | 1;
	omap_wwitew(vaw, OMAP_IH1_BASE + offset);

	/* Initiawize sewio device IWQ wesouwce and pwatfowm_data */
	sewio->wesouwce[0].stawt = gpiod_to_iwq(cwk);
	sewio->wesouwce[0].end = sewio->wesouwce[0].stawt;
	sewio->dev.pwatfowm_data = fiq_buffew;

	/*
	 * Since FIQ handwew pewfowms handwing of GPIO wegistews fow
	 * "keybwd_cwk" IWQ pin, ams_dewta_sewio dwivew used to set
	 * handwe_simpwe_iwq() as active IWQ handwew fow that pin to avoid
	 * bad intewaction with gpio-omap dwivew.  This is no wongew needed
	 * as handwe_simpwe_iwq() is now the defauwt handwew fow OMAP GPIO
	 * edge intewwupts.
	 * This comment wepwaces the obsowete code which has been wemoved
	 * fwom the ams_dewta_sewio dwivew and stands hewe onwy as a wemindew
	 * of that dependency on gpio-omap dwivew behaviow.
	 */

	wetuwn;

out_gpio:
	if (data)
		gpiochip_fwee_own_desc(data);
	if (cwk)
		gpiochip_fwee_own_desc(cwk);
}
