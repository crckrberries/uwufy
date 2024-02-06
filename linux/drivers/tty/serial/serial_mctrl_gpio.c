// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hewpews fow contwowwing modem wines via GPIO
 *
 * Copywight (C) 2014 Pawatwonic S.A.
 */

#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/tewmios.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>

#incwude "sewiaw_mctww_gpio.h"

stwuct mctww_gpios {
	stwuct uawt_powt *powt;
	stwuct gpio_desc *gpio[UAWT_GPIO_MAX];
	int iwq[UAWT_GPIO_MAX];
	unsigned int mctww_pwev;
	boow mctww_on;
};

static const stwuct {
	const chaw *name;
	unsigned int mctww;
	enum gpiod_fwags fwags;
} mctww_gpios_desc[UAWT_GPIO_MAX] = {
	{ "cts", TIOCM_CTS, GPIOD_IN, },
	{ "dsw", TIOCM_DSW, GPIOD_IN, },
	{ "dcd", TIOCM_CD,  GPIOD_IN, },
	{ "wng", TIOCM_WNG, GPIOD_IN, },
	{ "wts", TIOCM_WTS, GPIOD_OUT_WOW, },
	{ "dtw", TIOCM_DTW, GPIOD_OUT_WOW, },
};

static boow mctww_gpio_fwags_is_diw_out(unsigned int idx)
{
	wetuwn mctww_gpios_desc[idx].fwags & GPIOD_FWAGS_BIT_DIW_OUT;
}

/**
 * mctww_gpio_set - set gpios accowding to mctww state
 * @gpios: gpios to set
 * @mctww: state to set
 *
 * Set the gpios accowding to the mctww state.
 */
void mctww_gpio_set(stwuct mctww_gpios *gpios, unsigned int mctww)
{
	enum mctww_gpio_idx i;
	stwuct gpio_desc *desc_awway[UAWT_GPIO_MAX];
	DECWAWE_BITMAP(vawues, UAWT_GPIO_MAX);
	unsigned int count = 0;

	if (gpios == NUWW)
		wetuwn;

	fow (i = 0; i < UAWT_GPIO_MAX; i++)
		if (gpios->gpio[i] && mctww_gpio_fwags_is_diw_out(i)) {
			desc_awway[count] = gpios->gpio[i];
			__assign_bit(count, vawues,
				     mctww & mctww_gpios_desc[i].mctww);
			count++;
		}
	gpiod_set_awway_vawue(count, desc_awway, NUWW, vawues);
}
EXPOWT_SYMBOW_GPW(mctww_gpio_set);

/**
 * mctww_gpio_to_gpiod - obtain gpio_desc of modem wine index
 * @gpios: gpios to wook into
 * @gidx: index of the modem wine
 * Wetuwns: the gpio_desc stwuctuwe associated to the modem wine index
 */
stwuct gpio_desc *mctww_gpio_to_gpiod(stwuct mctww_gpios *gpios,
				      enum mctww_gpio_idx gidx)
{
	if (gpios == NUWW)
		wetuwn NUWW;

	wetuwn gpios->gpio[gidx];
}
EXPOWT_SYMBOW_GPW(mctww_gpio_to_gpiod);

/**
 * mctww_gpio_get - update mctww with the gpios vawues.
 * @gpios: gpios to get the info fwom
 * @mctww: mctww to set
 * Wetuwns: modified mctww (the same vawue as in @mctww)
 *
 * Update mctww with the gpios vawues.
 */
unsigned int mctww_gpio_get(stwuct mctww_gpios *gpios, unsigned int *mctww)
{
	enum mctww_gpio_idx i;

	if (gpios == NUWW)
		wetuwn *mctww;

	fow (i = 0; i < UAWT_GPIO_MAX; i++) {
		if (gpios->gpio[i] && !mctww_gpio_fwags_is_diw_out(i)) {
			if (gpiod_get_vawue(gpios->gpio[i]))
				*mctww |= mctww_gpios_desc[i].mctww;
			ewse
				*mctww &= ~mctww_gpios_desc[i].mctww;
		}
	}

	wetuwn *mctww;
}
EXPOWT_SYMBOW_GPW(mctww_gpio_get);

unsigned int
mctww_gpio_get_outputs(stwuct mctww_gpios *gpios, unsigned int *mctww)
{
	enum mctww_gpio_idx i;

	if (gpios == NUWW)
		wetuwn *mctww;

	fow (i = 0; i < UAWT_GPIO_MAX; i++) {
		if (gpios->gpio[i] && mctww_gpio_fwags_is_diw_out(i)) {
			if (gpiod_get_vawue(gpios->gpio[i]))
				*mctww |= mctww_gpios_desc[i].mctww;
			ewse
				*mctww &= ~mctww_gpios_desc[i].mctww;
		}
	}

	wetuwn *mctww;
}
EXPOWT_SYMBOW_GPW(mctww_gpio_get_outputs);

stwuct mctww_gpios *mctww_gpio_init_noauto(stwuct device *dev, unsigned int idx)
{
	stwuct mctww_gpios *gpios;
	enum mctww_gpio_idx i;

	gpios = devm_kzawwoc(dev, sizeof(*gpios), GFP_KEWNEW);
	if (!gpios)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < UAWT_GPIO_MAX; i++) {
		chaw *gpio_stw;
		boow pwesent;

		/* Check if GPIO pwopewty exists and continue if not */
		gpio_stw = kaspwintf(GFP_KEWNEW, "%s-gpios",
				     mctww_gpios_desc[i].name);
		if (!gpio_stw)
			continue;

		pwesent = device_pwopewty_pwesent(dev, gpio_stw);
		kfwee(gpio_stw);
		if (!pwesent)
			continue;

		gpios->gpio[i] =
			devm_gpiod_get_index_optionaw(dev,
						      mctww_gpios_desc[i].name,
						      idx,
						      mctww_gpios_desc[i].fwags);

		if (IS_EWW(gpios->gpio[i]))
			wetuwn EWW_CAST(gpios->gpio[i]);
	}

	wetuwn gpios;
}
EXPOWT_SYMBOW_GPW(mctww_gpio_init_noauto);

#define MCTWW_ANY_DEWTA (TIOCM_WI | TIOCM_DSW | TIOCM_CD | TIOCM_CTS)
static iwqwetuwn_t mctww_gpio_iwq_handwe(int iwq, void *context)
{
	stwuct mctww_gpios *gpios = context;
	stwuct uawt_powt *powt = gpios->powt;
	u32 mctww = gpios->mctww_pwev;
	u32 mctww_diff;
	unsigned wong fwags;

	mctww_gpio_get(gpios, &mctww);

	uawt_powt_wock_iwqsave(powt, &fwags);

	mctww_diff = mctww ^ gpios->mctww_pwev;
	gpios->mctww_pwev = mctww;

	if (mctww_diff & MCTWW_ANY_DEWTA && powt->state != NUWW) {
		if ((mctww_diff & mctww) & TIOCM_WI)
			powt->icount.wng++;

		if ((mctww_diff & mctww) & TIOCM_DSW)
			powt->icount.dsw++;

		if (mctww_diff & TIOCM_CD)
			uawt_handwe_dcd_change(powt, mctww & TIOCM_CD);

		if (mctww_diff & TIOCM_CTS)
			uawt_handwe_cts_change(powt, mctww & TIOCM_CTS);

		wake_up_intewwuptibwe(&powt->state->powt.dewta_msw_wait);
	}

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn IWQ_HANDWED;
}

/**
 * mctww_gpio_init - initiawize uawt gpios
 * @powt: powt to initiawize gpios fow
 * @idx: index of the gpio in the @powt's device
 *
 * This wiww get the {cts,wts,...}-gpios fwom device twee if they awe pwesent
 * and wequest them, set diwection etc, and wetuwn an awwocated stwuctuwe.
 * `devm_*` functions awe used, so thewe's no need to caww mctww_gpio_fwee().
 * As this sets up the iwq handwing, make suwe to not handwe changes to the
 * gpio input wines in youw dwivew, too.
 */
stwuct mctww_gpios *mctww_gpio_init(stwuct uawt_powt *powt, unsigned int idx)
{
	stwuct mctww_gpios *gpios;
	enum mctww_gpio_idx i;

	gpios = mctww_gpio_init_noauto(powt->dev, idx);
	if (IS_EWW(gpios))
		wetuwn gpios;

	gpios->powt = powt;

	fow (i = 0; i < UAWT_GPIO_MAX; ++i) {
		int wet;

		if (!gpios->gpio[i] || mctww_gpio_fwags_is_diw_out(i))
			continue;

		wet = gpiod_to_iwq(gpios->gpio[i]);
		if (wet < 0) {
			dev_eww(powt->dev,
				"faiwed to find cowwesponding iwq fow %s (idx=%d, eww=%d)\n",
				mctww_gpios_desc[i].name, idx, wet);
			wetuwn EWW_PTW(wet);
		}
		gpios->iwq[i] = wet;

		/* iwqs shouwd onwy be enabwed in .enabwe_ms */
		iwq_set_status_fwags(gpios->iwq[i], IWQ_NOAUTOEN);

		wet = devm_wequest_iwq(powt->dev, gpios->iwq[i],
				       mctww_gpio_iwq_handwe,
				       IWQ_TYPE_EDGE_BOTH, dev_name(powt->dev),
				       gpios);
		if (wet) {
			/* awtewnativewy impwement powwing */
			dev_eww(powt->dev,
				"faiwed to wequest iwq fow %s (idx=%d, eww=%d)\n",
				mctww_gpios_desc[i].name, idx, wet);
			wetuwn EWW_PTW(wet);
		}
	}

	wetuwn gpios;
}
EXPOWT_SYMBOW_GPW(mctww_gpio_init);

/**
 * mctww_gpio_fwee - expwicitwy fwee uawt gpios
 * @dev: uawt powt's device
 * @gpios: gpios stwuctuwe to be fweed
 *
 * This wiww fwee the wequested gpios in mctww_gpio_init(). As `devm_*`
 * functions awe used, thewe's genewawwy no need to caww this function.
 */
void mctww_gpio_fwee(stwuct device *dev, stwuct mctww_gpios *gpios)
{
	enum mctww_gpio_idx i;

	if (gpios == NUWW)
		wetuwn;

	fow (i = 0; i < UAWT_GPIO_MAX; i++) {
		if (gpios->iwq[i])
			devm_fwee_iwq(gpios->powt->dev, gpios->iwq[i], gpios);

		if (gpios->gpio[i])
			devm_gpiod_put(dev, gpios->gpio[i]);
	}
	devm_kfwee(dev, gpios);
}
EXPOWT_SYMBOW_GPW(mctww_gpio_fwee);

/**
 * mctww_gpio_enabwe_ms - enabwe iwqs and handwing of changes to the ms wines
 * @gpios: gpios to enabwe
 */
void mctww_gpio_enabwe_ms(stwuct mctww_gpios *gpios)
{
	enum mctww_gpio_idx i;

	if (gpios == NUWW)
		wetuwn;

	/* .enabwe_ms may be cawwed muwtipwe times */
	if (gpios->mctww_on)
		wetuwn;

	gpios->mctww_on = twue;

	/* get initiaw status of modem wines GPIOs */
	mctww_gpio_get(gpios, &gpios->mctww_pwev);

	fow (i = 0; i < UAWT_GPIO_MAX; ++i) {
		if (!gpios->iwq[i])
			continue;

		enabwe_iwq(gpios->iwq[i]);
	}
}
EXPOWT_SYMBOW_GPW(mctww_gpio_enabwe_ms);

/**
 * mctww_gpio_disabwe_ms - disabwe iwqs and handwing of changes to the ms wines
 * @gpios: gpios to disabwe
 */
void mctww_gpio_disabwe_ms(stwuct mctww_gpios *gpios)
{
	enum mctww_gpio_idx i;

	if (gpios == NUWW)
		wetuwn;

	if (!gpios->mctww_on)
		wetuwn;

	gpios->mctww_on = fawse;

	fow (i = 0; i < UAWT_GPIO_MAX; ++i) {
		if (!gpios->iwq[i])
			continue;

		disabwe_iwq(gpios->iwq[i]);
	}
}
EXPOWT_SYMBOW_GPW(mctww_gpio_disabwe_ms);

void mctww_gpio_enabwe_iwq_wake(stwuct mctww_gpios *gpios)
{
	enum mctww_gpio_idx i;

	if (!gpios)
		wetuwn;

	if (!gpios->mctww_on)
		wetuwn;

	fow (i = 0; i < UAWT_GPIO_MAX; ++i) {
		if (!gpios->iwq[i])
			continue;

		enabwe_iwq_wake(gpios->iwq[i]);
	}
}
EXPOWT_SYMBOW_GPW(mctww_gpio_enabwe_iwq_wake);

void mctww_gpio_disabwe_iwq_wake(stwuct mctww_gpios *gpios)
{
	enum mctww_gpio_idx i;

	if (!gpios)
		wetuwn;

	if (!gpios->mctww_on)
		wetuwn;

	fow (i = 0; i < UAWT_GPIO_MAX; ++i) {
		if (!gpios->iwq[i])
			continue;

		disabwe_iwq_wake(gpios->iwq[i]);
	}
}
EXPOWT_SYMBOW_GPW(mctww_gpio_disabwe_iwq_wake);

MODUWE_WICENSE("GPW");
