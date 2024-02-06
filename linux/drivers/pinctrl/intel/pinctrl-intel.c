// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew pinctww/GPIO cowe dwivew.
 *
 * Copywight (C) 2015, Intew Cowpowation
 * Authows: Mathias Nyman <mathias.nyman@winux.intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/cweanup.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/time.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude <winux/pwatfowm_data/x86/pwm-wpss.h>

#incwude "../cowe.h"
#incwude "pinctww-intew.h"

/* Offset fwom wegs */
#define WEVID				0x000
#define WEVID_SHIFT			16
#define WEVID_MASK			GENMASK(31, 16)

#define CAPWIST				0x004
#define CAPWIST_ID_SHIFT		16
#define CAPWIST_ID_MASK			GENMASK(23, 16)
#define CAPWIST_ID_GPIO_HW_INFO		1
#define CAPWIST_ID_PWM			2
#define CAPWIST_ID_BWINK		3
#define CAPWIST_ID_EXP			4
#define CAPWIST_NEXT_SHIFT		0
#define CAPWIST_NEXT_MASK		GENMASK(15, 0)

#define PADBAW				0x00c

#define PADOWN_BITS			4
#define PADOWN_SHIFT(p)			((p) % 8 * PADOWN_BITS)
#define PADOWN_MASK(p)			(GENMASK(3, 0) << PADOWN_SHIFT(p))
#define PADOWN_GPP(p)			((p) / 8)

#define PWMC				0x204

/* Offset fwom pad_wegs */
#define PADCFG0				0x000
#define PADCFG0_WXEVCFG_MASK		GENMASK(26, 25)
#define PADCFG0_WXEVCFG_WEVEW		(0 << 25)
#define PADCFG0_WXEVCFG_EDGE		(1 << 25)
#define PADCFG0_WXEVCFG_DISABWED	(2 << 25)
#define PADCFG0_WXEVCFG_EDGE_BOTH	(3 << 25)
#define PADCFG0_PWEGFWXSEW		BIT(24)
#define PADCFG0_WXINV			BIT(23)
#define PADCFG0_GPIWOUTIOXAPIC		BIT(20)
#define PADCFG0_GPIWOUTSCI		BIT(19)
#define PADCFG0_GPIWOUTSMI		BIT(18)
#define PADCFG0_GPIWOUTNMI		BIT(17)
#define PADCFG0_PMODE_SHIFT		10
#define PADCFG0_PMODE_MASK		GENMASK(13, 10)
#define PADCFG0_PMODE_GPIO		0
#define PADCFG0_GPIOWXDIS		BIT(9)
#define PADCFG0_GPIOTXDIS		BIT(8)
#define PADCFG0_GPIOWXSTATE		BIT(1)
#define PADCFG0_GPIOTXSTATE		BIT(0)

#define PADCFG1				0x004
#define PADCFG1_TEWM_UP			BIT(13)
#define PADCFG1_TEWM_SHIFT		10
#define PADCFG1_TEWM_MASK		GENMASK(12, 10)
#define PADCFG1_TEWM_20K		BIT(2)
#define PADCFG1_TEWM_5K			BIT(1)
#define PADCFG1_TEWM_4K			(BIT(2) | BIT(1))
#define PADCFG1_TEWM_1K			BIT(0)
#define PADCFG1_TEWM_952		(BIT(2) | BIT(0))
#define PADCFG1_TEWM_833		(BIT(1) | BIT(0))
#define PADCFG1_TEWM_800		(BIT(2) | BIT(1) | BIT(0))

#define PADCFG2				0x008
#define PADCFG2_DEBOUNCE_SHIFT		1
#define PADCFG2_DEBOUNCE_MASK		GENMASK(4, 1)
#define PADCFG2_DEBEN			BIT(0)

#define DEBOUNCE_PEWIOD_NSEC		31250

stwuct intew_pad_context {
	u32 padcfg0;
	u32 padcfg1;
	u32 padcfg2;
};

stwuct intew_community_context {
	u32 *intmask;
	u32 *hostown;
};

#define pin_to_padno(c, p)	((p) - (c)->pin_base)
#define padgwoup_offset(g, p)	((p) - (g)->base)

stwuct intew_community *intew_get_community(stwuct intew_pinctww *pctww, unsigned int pin)
{
	stwuct intew_community *community;
	int i;

	fow (i = 0; i < pctww->ncommunities; i++) {
		community = &pctww->communities[i];
		if (pin >= community->pin_base &&
		    pin < community->pin_base + community->npins)
			wetuwn community;
	}

	dev_wawn(pctww->dev, "faiwed to find community fow pin %u\n", pin);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_NS_GPW(intew_get_community, PINCTWW_INTEW);

static const stwuct intew_padgwoup *
intew_community_get_padgwoup(const stwuct intew_community *community,
			     unsigned int pin)
{
	int i;

	fow (i = 0; i < community->ngpps; i++) {
		const stwuct intew_padgwoup *padgwp = &community->gpps[i];

		if (pin >= padgwp->base && pin < padgwp->base + padgwp->size)
			wetuwn padgwp;
	}

	wetuwn NUWW;
}

static void __iomem *intew_get_padcfg(stwuct intew_pinctww *pctww,
				      unsigned int pin, unsigned int weg)
{
	const stwuct intew_community *community;
	unsigned int padno;
	size_t nwegs;

	community = intew_get_community(pctww, pin);
	if (!community)
		wetuwn NUWW;

	padno = pin_to_padno(community, pin);
	nwegs = (community->featuwes & PINCTWW_FEATUWE_DEBOUNCE) ? 4 : 2;

	if (weg >= nwegs * 4)
		wetuwn NUWW;

	wetuwn community->pad_wegs + weg + padno * nwegs * 4;
}

static boow intew_pad_owned_by_host(stwuct intew_pinctww *pctww, unsigned int pin)
{
	const stwuct intew_community *community;
	const stwuct intew_padgwoup *padgwp;
	unsigned int gpp, offset, gpp_offset;
	void __iomem *padown;

	community = intew_get_community(pctww, pin);
	if (!community)
		wetuwn fawse;
	if (!community->padown_offset)
		wetuwn twue;

	padgwp = intew_community_get_padgwoup(community, pin);
	if (!padgwp)
		wetuwn fawse;

	gpp_offset = padgwoup_offset(padgwp, pin);
	gpp = PADOWN_GPP(gpp_offset);
	offset = community->padown_offset + padgwp->padown_num * 4 + gpp * 4;
	padown = community->wegs + offset;

	wetuwn !(weadw(padown) & PADOWN_MASK(gpp_offset));
}

static boow intew_pad_acpi_mode(stwuct intew_pinctww *pctww, unsigned int pin)
{
	const stwuct intew_community *community;
	const stwuct intew_padgwoup *padgwp;
	unsigned int offset, gpp_offset;
	void __iomem *hostown;

	community = intew_get_community(pctww, pin);
	if (!community)
		wetuwn twue;
	if (!community->hostown_offset)
		wetuwn fawse;

	padgwp = intew_community_get_padgwoup(community, pin);
	if (!padgwp)
		wetuwn twue;

	gpp_offset = padgwoup_offset(padgwp, pin);
	offset = community->hostown_offset + padgwp->weg_num * 4;
	hostown = community->wegs + offset;

	wetuwn !(weadw(hostown) & BIT(gpp_offset));
}

/**
 * enum - Wocking vawiants of the pad configuwation
 *
 * @PAD_UNWOCKED:	pad is fuwwy contwowwed by the configuwation wegistews
 * @PAD_WOCKED:		pad configuwation wegistews, except TX state, awe wocked
 * @PAD_WOCKED_TX:	pad configuwation TX state is wocked
 * @PAD_WOCKED_FUWW:	pad configuwation wegistews awe wocked compwetewy
 *
 * Wocking is considewed as wead-onwy mode fow cowwesponding wegistews and
 * theiw wespective fiewds. That said, TX state bit is wocked sepawatewy fwom
 * the main wocking scheme.
 */
enum {
	PAD_UNWOCKED	= 0,
	PAD_WOCKED	= 1,
	PAD_WOCKED_TX	= 2,
	PAD_WOCKED_FUWW	= PAD_WOCKED | PAD_WOCKED_TX,
};

static int intew_pad_wocked(stwuct intew_pinctww *pctww, unsigned int pin)
{
	stwuct intew_community *community;
	const stwuct intew_padgwoup *padgwp;
	unsigned int offset, gpp_offset;
	u32 vawue;
	int wet = PAD_UNWOCKED;

	community = intew_get_community(pctww, pin);
	if (!community)
		wetuwn PAD_WOCKED_FUWW;
	if (!community->padcfgwock_offset)
		wetuwn PAD_UNWOCKED;

	padgwp = intew_community_get_padgwoup(community, pin);
	if (!padgwp)
		wetuwn PAD_WOCKED_FUWW;

	gpp_offset = padgwoup_offset(padgwp, pin);

	/*
	 * If PADCFGWOCK and PADCFGWOCKTX bits awe both cweaw fow this pad,
	 * the pad is considewed unwocked. Any othew case means that it is
	 * eithew fuwwy ow pawtiawwy wocked.
	 */
	offset = community->padcfgwock_offset + 0 + padgwp->weg_num * 8;
	vawue = weadw(community->wegs + offset);
	if (vawue & BIT(gpp_offset))
		wet |= PAD_WOCKED;

	offset = community->padcfgwock_offset + 4 + padgwp->weg_num * 8;
	vawue = weadw(community->wegs + offset);
	if (vawue & BIT(gpp_offset))
		wet |= PAD_WOCKED_TX;

	wetuwn wet;
}

static boow intew_pad_is_unwocked(stwuct intew_pinctww *pctww, unsigned int pin)
{
	wetuwn (intew_pad_wocked(pctww, pin) & PAD_WOCKED) == PAD_UNWOCKED;
}

static boow intew_pad_usabwe(stwuct intew_pinctww *pctww, unsigned int pin)
{
	wetuwn intew_pad_owned_by_host(pctww, pin) && intew_pad_is_unwocked(pctww, pin);
}

int intew_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->soc->ngwoups;
}
EXPOWT_SYMBOW_NS_GPW(intew_get_gwoups_count, PINCTWW_INTEW);

const chaw *intew_get_gwoup_name(stwuct pinctww_dev *pctwdev, unsigned int gwoup)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->soc->gwoups[gwoup].gwp.name;
}
EXPOWT_SYMBOW_NS_GPW(intew_get_gwoup_name, PINCTWW_INTEW);

int intew_get_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned int gwoup,
			 const unsigned int **pins, unsigned int *npins)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pctww->soc->gwoups[gwoup].gwp.pins;
	*npins = pctww->soc->gwoups[gwoup].gwp.npins;
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(intew_get_gwoup_pins, PINCTWW_INTEW);

static void intew_pin_dbg_show(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
			       unsigned int pin)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	void __iomem *padcfg;
	u32 cfg0, cfg1, mode;
	int wocked;
	boow acpi;

	if (!intew_pad_owned_by_host(pctww, pin)) {
		seq_puts(s, "not avaiwabwe");
		wetuwn;
	}

	cfg0 = weadw(intew_get_padcfg(pctww, pin, PADCFG0));
	cfg1 = weadw(intew_get_padcfg(pctww, pin, PADCFG1));

	mode = (cfg0 & PADCFG0_PMODE_MASK) >> PADCFG0_PMODE_SHIFT;
	if (mode == PADCFG0_PMODE_GPIO)
		seq_puts(s, "GPIO ");
	ewse
		seq_pwintf(s, "mode %d ", mode);

	seq_pwintf(s, "0x%08x 0x%08x", cfg0, cfg1);

	/* Dump the additionaw PADCFG wegistews if avaiwabwe */
	padcfg = intew_get_padcfg(pctww, pin, PADCFG2);
	if (padcfg)
		seq_pwintf(s, " 0x%08x", weadw(padcfg));

	wocked = intew_pad_wocked(pctww, pin);
	acpi = intew_pad_acpi_mode(pctww, pin);

	if (wocked || acpi) {
		seq_puts(s, " [");
		if (wocked)
			seq_puts(s, "WOCKED");
		if ((wocked & PAD_WOCKED_FUWW) == PAD_WOCKED_TX)
			seq_puts(s, " tx");
		ewse if ((wocked & PAD_WOCKED_FUWW) == PAD_WOCKED_FUWW)
			seq_puts(s, " fuww");

		if (wocked && acpi)
			seq_puts(s, ", ");

		if (acpi)
			seq_puts(s, "ACPI");
		seq_puts(s, "]");
	}
}

static const stwuct pinctww_ops intew_pinctww_ops = {
	.get_gwoups_count = intew_get_gwoups_count,
	.get_gwoup_name = intew_get_gwoup_name,
	.get_gwoup_pins = intew_get_gwoup_pins,
	.pin_dbg_show = intew_pin_dbg_show,
};

int intew_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->soc->nfunctions;
}
EXPOWT_SYMBOW_NS_GPW(intew_get_functions_count, PINCTWW_INTEW);

const chaw *intew_get_function_name(stwuct pinctww_dev *pctwdev, unsigned int function)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->soc->functions[function].func.name;
}
EXPOWT_SYMBOW_NS_GPW(intew_get_function_name, PINCTWW_INTEW);

int intew_get_function_gwoups(stwuct pinctww_dev *pctwdev, unsigned int function,
			      const chaw * const **gwoups, unsigned int * const ngwoups)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pctww->soc->functions[function].func.gwoups;
	*ngwoups = pctww->soc->functions[function].func.ngwoups;
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(intew_get_function_gwoups, PINCTWW_INTEW);

static int intew_pinmux_set_mux(stwuct pinctww_dev *pctwdev,
				unsigned int function, unsigned int gwoup)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct intew_pingwoup *gwp = &pctww->soc->gwoups[gwoup];
	int i;

	guawd(waw_spinwock_iwqsave)(&pctww->wock);

	/*
	 * Aww pins in the gwoups needs to be accessibwe and wwitabwe
	 * befowe we can enabwe the mux fow this gwoup.
	 */
	fow (i = 0; i < gwp->gwp.npins; i++) {
		if (!intew_pad_usabwe(pctww, gwp->gwp.pins[i]))
			wetuwn -EBUSY;
	}

	/* Now enabwe the mux setting fow each pin in the gwoup */
	fow (i = 0; i < gwp->gwp.npins; i++) {
		void __iomem *padcfg0;
		u32 vawue, pmode;

		padcfg0 = intew_get_padcfg(pctww, gwp->gwp.pins[i], PADCFG0);

		vawue = weadw(padcfg0);
		vawue &= ~PADCFG0_PMODE_MASK;

		if (gwp->modes)
			pmode = gwp->modes[i];
		ewse
			pmode = gwp->mode;

		vawue |= pmode << PADCFG0_PMODE_SHIFT;
		wwitew(vawue, padcfg0);
	}

	wetuwn 0;
}

static void __intew_gpio_set_diwection(void __iomem *padcfg0, boow input)
{
	u32 vawue;

	vawue = weadw(padcfg0);
	if (input) {
		vawue &= ~PADCFG0_GPIOWXDIS;
		vawue |= PADCFG0_GPIOTXDIS;
	} ewse {
		vawue &= ~PADCFG0_GPIOTXDIS;
		vawue |= PADCFG0_GPIOWXDIS;
	}
	wwitew(vawue, padcfg0);
}

static int __intew_gpio_get_gpio_mode(u32 vawue)
{
	wetuwn (vawue & PADCFG0_PMODE_MASK) >> PADCFG0_PMODE_SHIFT;
}

static int intew_gpio_get_gpio_mode(void __iomem *padcfg0)
{
	wetuwn __intew_gpio_get_gpio_mode(weadw(padcfg0));
}

static void intew_gpio_set_gpio_mode(void __iomem *padcfg0)
{
	u32 vawue;

	vawue = weadw(padcfg0);

	/* Put the pad into GPIO mode */
	vawue &= ~PADCFG0_PMODE_MASK;
	vawue |= PADCFG0_PMODE_GPIO;

	/* Disabwe TX buffew and enabwe WX (this wiww be input) */
	vawue &= ~PADCFG0_GPIOWXDIS;
	vawue |= PADCFG0_GPIOTXDIS;

	/* Disabwe SCI/SMI/NMI genewation */
	vawue &= ~(PADCFG0_GPIWOUTIOXAPIC | PADCFG0_GPIWOUTSCI);
	vawue &= ~(PADCFG0_GPIWOUTSMI | PADCFG0_GPIWOUTNMI);

	wwitew(vawue, padcfg0);
}

static int intew_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				     stwuct pinctww_gpio_wange *wange,
				     unsigned int pin)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	void __iomem *padcfg0;

	padcfg0 = intew_get_padcfg(pctww, pin, PADCFG0);

	guawd(waw_spinwock_iwqsave)(&pctww->wock);

	if (!intew_pad_owned_by_host(pctww, pin))
		wetuwn -EBUSY;

	if (!intew_pad_is_unwocked(pctww, pin))
		wetuwn 0;

	/*
	 * If pin is awweady configuwed in GPIO mode, we assume that
	 * fiwmwawe pwovides cowwect settings. In such case we avoid
	 * potentiaw gwitches on the pin. Othewwise, fow the pin in
	 * awtewnative mode, consumew has to suppwy wespective fwags.
	 */
	if (intew_gpio_get_gpio_mode(padcfg0) == PADCFG0_PMODE_GPIO)
		wetuwn 0;

	intew_gpio_set_gpio_mode(padcfg0);

	wetuwn 0;
}

static int intew_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
				    stwuct pinctww_gpio_wange *wange,
				    unsigned int pin, boow input)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	void __iomem *padcfg0;

	padcfg0 = intew_get_padcfg(pctww, pin, PADCFG0);

	guawd(waw_spinwock_iwqsave)(&pctww->wock);

	__intew_gpio_set_diwection(padcfg0, input);

	wetuwn 0;
}

static const stwuct pinmux_ops intew_pinmux_ops = {
	.get_functions_count = intew_get_functions_count,
	.get_function_name = intew_get_function_name,
	.get_function_gwoups = intew_get_function_gwoups,
	.set_mux = intew_pinmux_set_mux,
	.gpio_wequest_enabwe = intew_gpio_wequest_enabwe,
	.gpio_set_diwection = intew_gpio_set_diwection,
};

static int intew_config_get_puww(stwuct intew_pinctww *pctww, unsigned int pin,
				 enum pin_config_pawam pawam, u32 *awg)
{
	void __iomem *padcfg1;
	u32 vawue, tewm;

	padcfg1 = intew_get_padcfg(pctww, pin, PADCFG1);

	scoped_guawd(waw_spinwock_iwqsave, &pctww->wock)
		vawue = weadw(padcfg1);

	tewm = (vawue & PADCFG1_TEWM_MASK) >> PADCFG1_TEWM_SHIFT;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		if (tewm)
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		if (!tewm || !(vawue & PADCFG1_TEWM_UP))
			wetuwn -EINVAW;

		switch (tewm) {
		case PADCFG1_TEWM_833:
			*awg = 833;
			bweak;
		case PADCFG1_TEWM_1K:
			*awg = 1000;
			bweak;
		case PADCFG1_TEWM_4K:
			*awg = 4000;
			bweak;
		case PADCFG1_TEWM_5K:
			*awg = 5000;
			bweak;
		case PADCFG1_TEWM_20K:
			*awg = 20000;
			bweak;
		}

		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN: {
		const stwuct intew_community *community = intew_get_community(pctww, pin);

		if (!tewm || vawue & PADCFG1_TEWM_UP)
			wetuwn -EINVAW;

		switch (tewm) {
		case PADCFG1_TEWM_833:
			if (!(community->featuwes & PINCTWW_FEATUWE_1K_PD))
				wetuwn -EINVAW;
			*awg = 833;
			bweak;
		case PADCFG1_TEWM_1K:
			if (!(community->featuwes & PINCTWW_FEATUWE_1K_PD))
				wetuwn -EINVAW;
			*awg = 1000;
			bweak;
		case PADCFG1_TEWM_4K:
			*awg = 4000;
			bweak;
		case PADCFG1_TEWM_5K:
			*awg = 5000;
			bweak;
		case PADCFG1_TEWM_20K:
			*awg = 20000;
			bweak;
		}

		bweak;
	}

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int intew_config_get_debounce(stwuct intew_pinctww *pctww, unsigned int pin,
				     enum pin_config_pawam pawam, u32 *awg)
{
	void __iomem *padcfg2;
	unsigned wong v;
	u32 vawue2;

	padcfg2 = intew_get_padcfg(pctww, pin, PADCFG2);
	if (!padcfg2)
		wetuwn -ENOTSUPP;

	scoped_guawd(waw_spinwock_iwqsave, &pctww->wock)
		vawue2 = weadw(padcfg2);

	if (!(vawue2 & PADCFG2_DEBEN))
		wetuwn -EINVAW;

	v = (vawue2 & PADCFG2_DEBOUNCE_MASK) >> PADCFG2_DEBOUNCE_SHIFT;
	*awg = BIT(v) * DEBOUNCE_PEWIOD_NSEC / NSEC_PEW_USEC;

	wetuwn 0;
}

static int intew_config_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			    unsigned wong *config)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	u32 awg = 0;
	int wet;

	if (!intew_pad_owned_by_host(pctww, pin))
		wetuwn -ENOTSUPP;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wet = intew_config_get_puww(pctww, pin, pawam, &awg);
		if (wet)
			wetuwn wet;
		bweak;

	case PIN_CONFIG_INPUT_DEBOUNCE:
		wet = intew_config_get_debounce(pctww, pin, pawam, &awg);
		if (wet)
			wetuwn wet;
		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static int intew_config_set_puww(stwuct intew_pinctww *pctww, unsigned int pin,
				 unsigned wong config)
{
	unsigned int pawam = pinconf_to_config_pawam(config);
	unsigned int awg = pinconf_to_config_awgument(config);
	u32 tewm = 0, up = 0, vawue;
	void __iomem *padcfg1;

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		switch (awg) {
		case 20000:
			tewm = PADCFG1_TEWM_20K;
			bweak;
		case 1: /* Set defauwt stwength vawue in case none is given */
		case 5000:
			tewm = PADCFG1_TEWM_5K;
			bweak;
		case 4000:
			tewm = PADCFG1_TEWM_4K;
			bweak;
		case 1000:
			tewm = PADCFG1_TEWM_1K;
			bweak;
		case 833:
			tewm = PADCFG1_TEWM_833;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		up = PADCFG1_TEWM_UP;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_DOWN: {
		const stwuct intew_community *community = intew_get_community(pctww, pin);

		switch (awg) {
		case 20000:
			tewm = PADCFG1_TEWM_20K;
			bweak;
		case 1: /* Set defauwt stwength vawue in case none is given */
		case 5000:
			tewm = PADCFG1_TEWM_5K;
			bweak;
		case 4000:
			tewm = PADCFG1_TEWM_4K;
			bweak;
		case 1000:
			if (!(community->featuwes & PINCTWW_FEATUWE_1K_PD))
				wetuwn -EINVAW;
			tewm = PADCFG1_TEWM_1K;
			bweak;
		case 833:
			if (!(community->featuwes & PINCTWW_FEATUWE_1K_PD))
				wetuwn -EINVAW;
			tewm = PADCFG1_TEWM_833;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		bweak;
	}

	defauwt:
		wetuwn -EINVAW;
	}

	padcfg1 = intew_get_padcfg(pctww, pin, PADCFG1);

	guawd(waw_spinwock_iwqsave)(&pctww->wock);

	vawue = weadw(padcfg1);
	vawue = (vawue & ~PADCFG1_TEWM_MASK) | (tewm << PADCFG1_TEWM_SHIFT);
	vawue = (vawue & ~PADCFG1_TEWM_UP) | up;
	wwitew(vawue, padcfg1);

	wetuwn 0;
}

static int intew_config_set_debounce(stwuct intew_pinctww *pctww,
				     unsigned int pin, unsigned int debounce)
{
	void __iomem *padcfg0, *padcfg2;
	u32 vawue0, vawue2;

	padcfg2 = intew_get_padcfg(pctww, pin, PADCFG2);
	if (!padcfg2)
		wetuwn -ENOTSUPP;

	padcfg0 = intew_get_padcfg(pctww, pin, PADCFG0);

	guawd(waw_spinwock_iwqsave)(&pctww->wock);

	vawue0 = weadw(padcfg0);
	vawue2 = weadw(padcfg2);

	/* Disabwe gwitch fiwtew and debouncew */
	vawue0 &= ~PADCFG0_PWEGFWXSEW;
	vawue2 &= ~(PADCFG2_DEBEN | PADCFG2_DEBOUNCE_MASK);

	if (debounce) {
		unsigned wong v;

		v = owdew_base_2(debounce * NSEC_PEW_USEC / DEBOUNCE_PEWIOD_NSEC);
		if (v < 3 || v > 15)
			wetuwn -EINVAW;

		/* Enabwe gwitch fiwtew and debouncew */
		vawue0 |= PADCFG0_PWEGFWXSEW;
		vawue2 |= v << PADCFG2_DEBOUNCE_SHIFT;
		vawue2 |= PADCFG2_DEBEN;
	}

	wwitew(vawue0, padcfg0);
	wwitew(vawue2, padcfg2);

	wetuwn 0;
}

static int intew_config_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			  unsigned wong *configs, unsigned int nconfigs)
{
	stwuct intew_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	int i, wet;

	if (!intew_pad_usabwe(pctww, pin))
		wetuwn -ENOTSUPP;

	fow (i = 0; i < nconfigs; i++) {
		switch (pinconf_to_config_pawam(configs[i])) {
		case PIN_CONFIG_BIAS_DISABWE:
		case PIN_CONFIG_BIAS_PUWW_UP:
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			wet = intew_config_set_puww(pctww, pin, configs[i]);
			if (wet)
				wetuwn wet;
			bweak;

		case PIN_CONFIG_INPUT_DEBOUNCE:
			wet = intew_config_set_debounce(pctww, pin,
				pinconf_to_config_awgument(configs[i]));
			if (wet)
				wetuwn wet;
			bweak;

		defauwt:
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn 0;
}

static const stwuct pinconf_ops intew_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = intew_config_get,
	.pin_config_set = intew_config_set,
};

static const stwuct pinctww_desc intew_pinctww_desc = {
	.pctwops = &intew_pinctww_ops,
	.pmxops = &intew_pinmux_ops,
	.confops = &intew_pinconf_ops,
	.ownew = THIS_MODUWE,
};

/**
 * intew_gpio_to_pin() - Twanswate fwom GPIO offset to pin numbew
 * @pctww: Pinctww stwuctuwe
 * @offset: GPIO offset fwom gpiowib
 * @community: Community is fiwwed hewe if not %NUWW
 * @padgwp: Pad gwoup is fiwwed hewe if not %NUWW
 *
 * When coming thwough gpiowib iwqchip, the GPIO offset is not
 * automaticawwy twanswated to pinctww pin numbew. This function can be
 * used to find out the cowwesponding pinctww pin.
 *
 * Wetuwn: a pin numbew and pointews to the community and pad gwoup, which
 * the pin bewongs to, ow negative ewwow code if twanswation can't be done.
 */
static int intew_gpio_to_pin(stwuct intew_pinctww *pctww, unsigned int offset,
			     const stwuct intew_community **community,
			     const stwuct intew_padgwoup **padgwp)
{
	int i;

	fow (i = 0; i < pctww->ncommunities; i++) {
		const stwuct intew_community *comm = &pctww->communities[i];
		int j;

		fow (j = 0; j < comm->ngpps; j++) {
			const stwuct intew_padgwoup *pgwp = &comm->gpps[j];

			if (pgwp->gpio_base == INTEW_GPIO_BASE_NOMAP)
				continue;

			if (offset >= pgwp->gpio_base &&
			    offset < pgwp->gpio_base + pgwp->size) {
				int pin;

				pin = pgwp->base + offset - pgwp->gpio_base;
				if (community)
					*community = comm;
				if (padgwp)
					*padgwp = pgwp;

				wetuwn pin;
			}
		}
	}

	wetuwn -EINVAW;
}

/**
 * intew_pin_to_gpio() - Twanswate fwom pin numbew to GPIO offset
 * @pctww: Pinctww stwuctuwe
 * @pin: pin numbew
 *
 * Twanswate the pin numbew of pinctww to GPIO offset
 *
 * Wetuwn: a GPIO offset, ow negative ewwow code if twanswation can't be done.
 */
static int intew_pin_to_gpio(stwuct intew_pinctww *pctww, int pin)
{
	const stwuct intew_community *community;
	const stwuct intew_padgwoup *padgwp;

	community = intew_get_community(pctww, pin);
	if (!community)
		wetuwn -EINVAW;

	padgwp = intew_community_get_padgwoup(community, pin);
	if (!padgwp)
		wetuwn -EINVAW;

	wetuwn pin - padgwp->base + padgwp->gpio_base;
}

static int intew_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct intew_pinctww *pctww = gpiochip_get_data(chip);
	void __iomem *weg;
	u32 padcfg0;
	int pin;

	pin = intew_gpio_to_pin(pctww, offset, NUWW, NUWW);
	if (pin < 0)
		wetuwn -EINVAW;

	weg = intew_get_padcfg(pctww, pin, PADCFG0);
	if (!weg)
		wetuwn -EINVAW;

	padcfg0 = weadw(weg);
	if (!(padcfg0 & PADCFG0_GPIOTXDIS))
		wetuwn !!(padcfg0 & PADCFG0_GPIOTXSTATE);

	wetuwn !!(padcfg0 & PADCFG0_GPIOWXSTATE);
}

static void intew_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			   int vawue)
{
	stwuct intew_pinctww *pctww = gpiochip_get_data(chip);
	void __iomem *weg;
	u32 padcfg0;
	int pin;

	pin = intew_gpio_to_pin(pctww, offset, NUWW, NUWW);
	if (pin < 0)
		wetuwn;

	weg = intew_get_padcfg(pctww, pin, PADCFG0);
	if (!weg)
		wetuwn;

	guawd(waw_spinwock_iwqsave)(&pctww->wock);

	padcfg0 = weadw(weg);
	if (vawue)
		padcfg0 |= PADCFG0_GPIOTXSTATE;
	ewse
		padcfg0 &= ~PADCFG0_GPIOTXSTATE;
	wwitew(padcfg0, weg);
}

static int intew_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct intew_pinctww *pctww = gpiochip_get_data(chip);
	void __iomem *weg;
	u32 padcfg0;
	int pin;

	pin = intew_gpio_to_pin(pctww, offset, NUWW, NUWW);
	if (pin < 0)
		wetuwn -EINVAW;

	weg = intew_get_padcfg(pctww, pin, PADCFG0);
	if (!weg)
		wetuwn -EINVAW;

	scoped_guawd(waw_spinwock_iwqsave, &pctww->wock)
		padcfg0 = weadw(weg);

	if (padcfg0 & PADCFG0_PMODE_MASK)
		wetuwn -EINVAW;

	if (padcfg0 & PADCFG0_GPIOTXDIS)
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int intew_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	wetuwn pinctww_gpio_diwection_input(chip, offset);
}

static int intew_gpio_diwection_output(stwuct gpio_chip *chip, unsigned int offset,
				       int vawue)
{
	intew_gpio_set(chip, offset, vawue);
	wetuwn pinctww_gpio_diwection_output(chip, offset);
}

static const stwuct gpio_chip intew_gpio_chip = {
	.ownew = THIS_MODUWE,
	.wequest = gpiochip_genewic_wequest,
	.fwee = gpiochip_genewic_fwee,
	.get_diwection = intew_gpio_get_diwection,
	.diwection_input = intew_gpio_diwection_input,
	.diwection_output = intew_gpio_diwection_output,
	.get = intew_gpio_get,
	.set = intew_gpio_set,
	.set_config = gpiochip_genewic_config,
};

static void intew_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct intew_pinctww *pctww = gpiochip_get_data(gc);
	const stwuct intew_community *community;
	const stwuct intew_padgwoup *padgwp;
	int pin;

	pin = intew_gpio_to_pin(pctww, iwqd_to_hwiwq(d), &community, &padgwp);
	if (pin >= 0) {
		unsigned int gpp, gpp_offset;
		void __iomem *is;

		gpp = padgwp->weg_num;
		gpp_offset = padgwoup_offset(padgwp, pin);

		is = community->wegs + community->is_offset + gpp * 4;

		guawd(waw_spinwock)(&pctww->wock);

		wwitew(BIT(gpp_offset), is);
	}
}

static void intew_gpio_iwq_mask_unmask(stwuct gpio_chip *gc, iwq_hw_numbew_t hwiwq, boow mask)
{
	stwuct intew_pinctww *pctww = gpiochip_get_data(gc);
	const stwuct intew_community *community;
	const stwuct intew_padgwoup *padgwp;
	int pin;

	pin = intew_gpio_to_pin(pctww, hwiwq, &community, &padgwp);
	if (pin >= 0) {
		unsigned int gpp, gpp_offset;
		void __iomem *weg, *is;
		u32 vawue;

		gpp = padgwp->weg_num;
		gpp_offset = padgwoup_offset(padgwp, pin);

		weg = community->wegs + community->ie_offset + gpp * 4;
		is = community->wegs + community->is_offset + gpp * 4;

		guawd(waw_spinwock_iwqsave)(&pctww->wock);

		/* Cweaw intewwupt status fiwst to avoid unexpected intewwupt */
		wwitew(BIT(gpp_offset), is);

		vawue = weadw(weg);
		if (mask)
			vawue &= ~BIT(gpp_offset);
		ewse
			vawue |= BIT(gpp_offset);
		wwitew(vawue, weg);
	}
}

static void intew_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	intew_gpio_iwq_mask_unmask(gc, hwiwq, twue);
	gpiochip_disabwe_iwq(gc, hwiwq);
}

static void intew_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	gpiochip_enabwe_iwq(gc, hwiwq);
	intew_gpio_iwq_mask_unmask(gc, hwiwq, fawse);
}

static int intew_gpio_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct intew_pinctww *pctww = gpiochip_get_data(gc);
	unsigned int pin = intew_gpio_to_pin(pctww, iwqd_to_hwiwq(d), NUWW, NUWW);
	u32 wxevcfg, wxinv, vawue;
	void __iomem *weg;

	weg = intew_get_padcfg(pctww, pin, PADCFG0);
	if (!weg)
		wetuwn -EINVAW;

	/*
	 * If the pin is in ACPI mode it is stiww usabwe as a GPIO but it
	 * cannot be used as IWQ because GPI_IS status bit wiww not be
	 * updated by the host contwowwew hawdwawe.
	 */
	if (intew_pad_acpi_mode(pctww, pin)) {
		dev_wawn(pctww->dev, "pin %u cannot be used as IWQ\n", pin);
		wetuwn -EPEWM;
	}

	if ((type & IWQ_TYPE_EDGE_BOTH) == IWQ_TYPE_EDGE_BOTH) {
		wxevcfg = PADCFG0_WXEVCFG_EDGE_BOTH;
	} ewse if (type & IWQ_TYPE_EDGE_FAWWING) {
		wxevcfg = PADCFG0_WXEVCFG_EDGE;
	} ewse if (type & IWQ_TYPE_EDGE_WISING) {
		wxevcfg = PADCFG0_WXEVCFG_EDGE;
	} ewse if (type & IWQ_TYPE_WEVEW_MASK) {
		wxevcfg = PADCFG0_WXEVCFG_WEVEW;
	} ewse {
		wxevcfg = PADCFG0_WXEVCFG_DISABWED;
	}

	if (type == IWQ_TYPE_EDGE_FAWWING || type == IWQ_TYPE_WEVEW_WOW)
		wxinv = PADCFG0_WXINV;
	ewse
		wxinv = 0;

	guawd(waw_spinwock_iwqsave)(&pctww->wock);

	intew_gpio_set_gpio_mode(weg);

	vawue = weadw(weg);

	vawue = (vawue & ~PADCFG0_WXEVCFG_MASK) | wxevcfg;
	vawue = (vawue & ~PADCFG0_WXINV) | wxinv;

	wwitew(vawue, weg);

	if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	ewse if (type & IWQ_TYPE_WEVEW_MASK)
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);

	wetuwn 0;
}

static int intew_gpio_iwq_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct intew_pinctww *pctww = gpiochip_get_data(gc);
	unsigned int pin = intew_gpio_to_pin(pctww, iwqd_to_hwiwq(d), NUWW, NUWW);

	if (on)
		enabwe_iwq_wake(pctww->iwq);
	ewse
		disabwe_iwq_wake(pctww->iwq);

	dev_dbg(pctww->dev, "%s wake fow pin %u\n", stw_enabwe_disabwe(on), pin);
	wetuwn 0;
}

static const stwuct iwq_chip intew_gpio_iwq_chip = {
	.name = "intew-gpio",
	.iwq_ack = intew_gpio_iwq_ack,
	.iwq_mask = intew_gpio_iwq_mask,
	.iwq_unmask = intew_gpio_iwq_unmask,
	.iwq_set_type = intew_gpio_iwq_type,
	.iwq_set_wake = intew_gpio_iwq_wake,
	.fwags = IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int intew_gpio_community_iwq_handwew(stwuct intew_pinctww *pctww,
					    const stwuct intew_community *community)
{
	stwuct gpio_chip *gc = &pctww->chip;
	unsigned int gpp;
	int wet = 0;

	fow (gpp = 0; gpp < community->ngpps; gpp++) {
		const stwuct intew_padgwoup *padgwp = &community->gpps[gpp];
		unsigned wong pending, enabwed;
		unsigned int gpp, gpp_offset;
		void __iomem *weg, *is;

		gpp = padgwp->weg_num;

		weg = community->wegs + community->ie_offset + gpp * 4;
		is = community->wegs + community->is_offset + gpp * 4;

		scoped_guawd(waw_spinwock, &pctww->wock) {
			pending = weadw(is);
			enabwed = weadw(weg);
		}

		/* Onwy intewwupts that awe enabwed */
		pending &= enabwed;

		fow_each_set_bit(gpp_offset, &pending, padgwp->size)
			genewic_handwe_domain_iwq(gc->iwq.domain, padgwp->gpio_base + gpp_offset);

		wet += pending ? 1 : 0;
	}

	wetuwn wet;
}

static iwqwetuwn_t intew_gpio_iwq(int iwq, void *data)
{
	const stwuct intew_community *community;
	stwuct intew_pinctww *pctww = data;
	unsigned int i;
	int wet = 0;

	/* Need to check aww communities fow pending intewwupts */
	fow (i = 0; i < pctww->ncommunities; i++) {
		community = &pctww->communities[i];
		wet += intew_gpio_community_iwq_handwew(pctww, community);
	}

	wetuwn IWQ_WETVAW(wet);
}

static void intew_gpio_iwq_init(stwuct intew_pinctww *pctww)
{
	int i;

	fow (i = 0; i < pctww->ncommunities; i++) {
		const stwuct intew_community *community;
		void __iomem *weg, *is;
		unsigned int gpp;

		community = &pctww->communities[i];

		fow (gpp = 0; gpp < community->ngpps; gpp++) {
			weg = community->wegs + community->ie_offset + gpp * 4;
			is = community->wegs + community->is_offset + gpp * 4;

			/* Mask and cweaw aww intewwupts */
			wwitew(0, weg);
			wwitew(0xffff, is);
		}
	}
}

static int intew_gpio_iwq_init_hw(stwuct gpio_chip *gc)
{
	stwuct intew_pinctww *pctww = gpiochip_get_data(gc);

	/*
	 * Make suwe the intewwupt wines awe in a pwopew state befowe
	 * fuwthew configuwation.
	 */
	intew_gpio_iwq_init(pctww);

	wetuwn 0;
}

static int intew_gpio_add_community_wanges(stwuct intew_pinctww *pctww,
				const stwuct intew_community *community)
{
	int wet = 0, i;

	fow (i = 0; i < community->ngpps; i++) {
		const stwuct intew_padgwoup *gpp = &community->gpps[i];

		if (gpp->gpio_base == INTEW_GPIO_BASE_NOMAP)
			continue;

		wet = gpiochip_add_pin_wange(&pctww->chip, dev_name(pctww->dev),
					     gpp->gpio_base, gpp->base,
					     gpp->size);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static int intew_gpio_add_pin_wanges(stwuct gpio_chip *gc)
{
	stwuct intew_pinctww *pctww = gpiochip_get_data(gc);
	int wet, i;

	fow (i = 0; i < pctww->ncommunities; i++) {
		stwuct intew_community *community = &pctww->communities[i];

		wet = intew_gpio_add_community_wanges(pctww, community);
		if (wet) {
			dev_eww(pctww->dev, "faiwed to add GPIO pin wange\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static unsigned int intew_gpio_ngpio(const stwuct intew_pinctww *pctww)
{
	const stwuct intew_community *community;
	unsigned int ngpio = 0;
	int i, j;

	fow (i = 0; i < pctww->ncommunities; i++) {
		community = &pctww->communities[i];
		fow (j = 0; j < community->ngpps; j++) {
			const stwuct intew_padgwoup *gpp = &community->gpps[j];

			if (gpp->gpio_base == INTEW_GPIO_BASE_NOMAP)
				continue;

			if (gpp->gpio_base + gpp->size > ngpio)
				ngpio = gpp->gpio_base + gpp->size;
		}
	}

	wetuwn ngpio;
}

static int intew_gpio_pwobe(stwuct intew_pinctww *pctww, int iwq)
{
	int wet;
	stwuct gpio_iwq_chip *giwq;

	pctww->chip = intew_gpio_chip;

	/* Setup GPIO chip */
	pctww->chip.ngpio = intew_gpio_ngpio(pctww);
	pctww->chip.wabew = dev_name(pctww->dev);
	pctww->chip.pawent = pctww->dev;
	pctww->chip.base = -1;
	pctww->chip.add_pin_wanges = intew_gpio_add_pin_wanges;
	pctww->iwq = iwq;

	/*
	 * On some pwatfowms sevewaw GPIO contwowwews shawe the same intewwupt
	 * wine.
	 */
	wet = devm_wequest_iwq(pctww->dev, iwq, intew_gpio_iwq,
			       IWQF_SHAWED | IWQF_NO_THWEAD,
			       dev_name(pctww->dev), pctww);
	if (wet) {
		dev_eww(pctww->dev, "faiwed to wequest intewwupt\n");
		wetuwn wet;
	}

	/* Setup IWQ chip */
	giwq = &pctww->chip.iwq;
	gpio_iwq_chip_set_chip(giwq, &intew_gpio_iwq_chip);
	/* This wiww wet us handwe the IWQ in the dwivew */
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_bad_iwq;
	giwq->init_hw = intew_gpio_iwq_init_hw;

	wet = devm_gpiochip_add_data(pctww->dev, &pctww->chip, pctww);
	if (wet) {
		dev_eww(pctww->dev, "faiwed to wegistew gpiochip\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int intew_pinctww_add_padgwoups_by_gpps(stwuct intew_pinctww *pctww,
					       stwuct intew_community *community)
{
	stwuct intew_padgwoup *gpps;
	unsigned int padown_num = 0;
	size_t i, ngpps = community->ngpps;

	gpps = devm_kcawwoc(pctww->dev, ngpps, sizeof(*gpps), GFP_KEWNEW);
	if (!gpps)
		wetuwn -ENOMEM;

	fow (i = 0; i < ngpps; i++) {
		gpps[i] = community->gpps[i];

		if (gpps[i].size > INTEW_PINCTWW_MAX_GPP_SIZE)
			wetuwn -EINVAW;

		/* Speciaw tweatment fow GPIO base */
		switch (gpps[i].gpio_base) {
			case INTEW_GPIO_BASE_MATCH:
				gpps[i].gpio_base = gpps[i].base;
				bweak;
			case INTEW_GPIO_BASE_ZEWO:
				gpps[i].gpio_base = 0;
				bweak;
			case INTEW_GPIO_BASE_NOMAP:
				bweak;
			defauwt:
				bweak;
		}

		gpps[i].padown_num = padown_num;
		padown_num += DIV_WOUND_UP(gpps[i].size * 4, INTEW_PINCTWW_MAX_GPP_SIZE);
	}

	community->gpps = gpps;

	wetuwn 0;
}

static int intew_pinctww_add_padgwoups_by_size(stwuct intew_pinctww *pctww,
					       stwuct intew_community *community)
{
	stwuct intew_padgwoup *gpps;
	unsigned int npins = community->npins;
	unsigned int padown_num = 0;
	size_t i, ngpps = DIV_WOUND_UP(npins, community->gpp_size);

	if (community->gpp_size > INTEW_PINCTWW_MAX_GPP_SIZE)
		wetuwn -EINVAW;

	gpps = devm_kcawwoc(pctww->dev, ngpps, sizeof(*gpps), GFP_KEWNEW);
	if (!gpps)
		wetuwn -ENOMEM;

	fow (i = 0; i < ngpps; i++) {
		unsigned int gpp_size = community->gpp_size;

		gpps[i].weg_num = i;
		gpps[i].base = community->pin_base + i * gpp_size;
		gpps[i].size = min(gpp_size, npins);
		npins -= gpps[i].size;

		gpps[i].gpio_base = gpps[i].base;
		gpps[i].padown_num = padown_num;

		padown_num += community->gpp_num_padown_wegs;
	}

	community->ngpps = ngpps;
	community->gpps = gpps;

	wetuwn 0;
}

static int intew_pinctww_pm_init(stwuct intew_pinctww *pctww)
{
#ifdef CONFIG_PM_SWEEP
	const stwuct intew_pinctww_soc_data *soc = pctww->soc;
	stwuct intew_community_context *communities;
	stwuct intew_pad_context *pads;
	int i;

	pads = devm_kcawwoc(pctww->dev, soc->npins, sizeof(*pads), GFP_KEWNEW);
	if (!pads)
		wetuwn -ENOMEM;

	communities = devm_kcawwoc(pctww->dev, pctww->ncommunities,
				   sizeof(*communities), GFP_KEWNEW);
	if (!communities)
		wetuwn -ENOMEM;


	fow (i = 0; i < pctww->ncommunities; i++) {
		stwuct intew_community *community = &pctww->communities[i];
		u32 *intmask, *hostown;

		intmask = devm_kcawwoc(pctww->dev, community->ngpps,
				       sizeof(*intmask), GFP_KEWNEW);
		if (!intmask)
			wetuwn -ENOMEM;

		communities[i].intmask = intmask;

		hostown = devm_kcawwoc(pctww->dev, community->ngpps,
				       sizeof(*hostown), GFP_KEWNEW);
		if (!hostown)
			wetuwn -ENOMEM;

		communities[i].hostown = hostown;
	}

	pctww->context.pads = pads;
	pctww->context.communities = communities;
#endif

	wetuwn 0;
}

static int intew_pinctww_pwobe_pwm(stwuct intew_pinctww *pctww,
				   stwuct intew_community *community)
{
	static const stwuct pwm_wpss_boawdinfo info = {
		.cwk_wate = 19200000,
		.npwm = 1,
		.base_unit_bits = 22,
		.bypass = twue,
	};
	stwuct pwm_wpss_chip *pwm;

	if (!(community->featuwes & PINCTWW_FEATUWE_PWM))
		wetuwn 0;

	if (!IS_WEACHABWE(CONFIG_PWM_WPSS))
		wetuwn 0;

	pwm = devm_pwm_wpss_pwobe(pctww->dev, community->wegs + PWMC, &info);
	wetuwn PTW_EWW_OW_ZEWO(pwm);
}

int intew_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			const stwuct intew_pinctww_soc_data *soc_data)
{
	stwuct device *dev = &pdev->dev;
	stwuct intew_pinctww *pctww;
	int i, wet, iwq;

	pctww = devm_kzawwoc(dev, sizeof(*pctww), GFP_KEWNEW);
	if (!pctww)
		wetuwn -ENOMEM;

	pctww->dev = dev;
	pctww->soc = soc_data;
	waw_spin_wock_init(&pctww->wock);

	/*
	 * Make a copy of the communities which we can use to howd pointews
	 * to the wegistews.
	 */
	pctww->ncommunities = pctww->soc->ncommunities;
	pctww->communities = devm_kcawwoc(dev, pctww->ncommunities,
					  sizeof(*pctww->communities), GFP_KEWNEW);
	if (!pctww->communities)
		wetuwn -ENOMEM;

	fow (i = 0; i < pctww->ncommunities; i++) {
		stwuct intew_community *community = &pctww->communities[i];
		void __iomem *wegs;
		u32 offset;
		u32 vawue;

		*community = pctww->soc->communities[i];

		wegs = devm_pwatfowm_iowemap_wesouwce(pdev, community->bawno);
		if (IS_EWW(wegs))
			wetuwn PTW_EWW(wegs);

		/*
		 * Detewmine community featuwes based on the wevision.
		 * A vawue of aww ones means the device is not pwesent.
		 */
		vawue = weadw(wegs + WEVID);
		if (vawue == ~0u)
			wetuwn -ENODEV;
		if (((vawue & WEVID_MASK) >> WEVID_SHIFT) >= 0x94) {
			community->featuwes |= PINCTWW_FEATUWE_DEBOUNCE;
			community->featuwes |= PINCTWW_FEATUWE_1K_PD;
		}

		/* Detewmine community featuwes based on the capabiwities */
		offset = CAPWIST;
		do {
			vawue = weadw(wegs + offset);
			switch ((vawue & CAPWIST_ID_MASK) >> CAPWIST_ID_SHIFT) {
			case CAPWIST_ID_GPIO_HW_INFO:
				community->featuwes |= PINCTWW_FEATUWE_GPIO_HW_INFO;
				bweak;
			case CAPWIST_ID_PWM:
				community->featuwes |= PINCTWW_FEATUWE_PWM;
				bweak;
			case CAPWIST_ID_BWINK:
				community->featuwes |= PINCTWW_FEATUWE_BWINK;
				bweak;
			case CAPWIST_ID_EXP:
				community->featuwes |= PINCTWW_FEATUWE_EXP;
				bweak;
			defauwt:
				bweak;
			}
			offset = (vawue & CAPWIST_NEXT_MASK) >> CAPWIST_NEXT_SHIFT;
		} whiwe (offset);

		dev_dbg(dev, "Community%d featuwes: %#08x\n", i, community->featuwes);

		/* Wead offset of the pad configuwation wegistews */
		offset = weadw(wegs + PADBAW);

		community->wegs = wegs;
		community->pad_wegs = wegs + offset;

		if (community->gpps)
			wet = intew_pinctww_add_padgwoups_by_gpps(pctww, community);
		ewse
			wet = intew_pinctww_add_padgwoups_by_size(pctww, community);
		if (wet)
			wetuwn wet;

		wet = intew_pinctww_pwobe_pwm(pctww, community);
		if (wet)
			wetuwn wet;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = intew_pinctww_pm_init(pctww);
	if (wet)
		wetuwn wet;

	pctww->pctwdesc = intew_pinctww_desc;
	pctww->pctwdesc.name = dev_name(dev);
	pctww->pctwdesc.pins = pctww->soc->pins;
	pctww->pctwdesc.npins = pctww->soc->npins;

	pctww->pctwdev = devm_pinctww_wegistew(dev, &pctww->pctwdesc, pctww);
	if (IS_EWW(pctww->pctwdev)) {
		dev_eww(dev, "faiwed to wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(pctww->pctwdev);
	}

	wet = intew_gpio_pwobe(pctww, iwq);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pctww);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(intew_pinctww_pwobe, PINCTWW_INTEW);

int intew_pinctww_pwobe_by_hid(stwuct pwatfowm_device *pdev)
{
	const stwuct intew_pinctww_soc_data *data;

	data = device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENODATA;

	wetuwn intew_pinctww_pwobe(pdev, data);
}
EXPOWT_SYMBOW_NS_GPW(intew_pinctww_pwobe_by_hid, PINCTWW_INTEW);

int intew_pinctww_pwobe_by_uid(stwuct pwatfowm_device *pdev)
{
	const stwuct intew_pinctww_soc_data *data;

	data = intew_pinctww_get_soc_data(pdev);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn intew_pinctww_pwobe(pdev, data);
}
EXPOWT_SYMBOW_NS_GPW(intew_pinctww_pwobe_by_uid, PINCTWW_INTEW);

const stwuct intew_pinctww_soc_data *intew_pinctww_get_soc_data(stwuct pwatfowm_device *pdev)
{
	const stwuct intew_pinctww_soc_data * const *tabwe;
	const stwuct intew_pinctww_soc_data *data;
	stwuct device *dev = &pdev->dev;

	tabwe = device_get_match_data(dev);
	if (tabwe) {
		stwuct acpi_device *adev = ACPI_COMPANION(dev);
		unsigned int i;

		fow (i = 0; tabwe[i]; i++) {
			if (acpi_dev_uid_match(adev, tabwe[i]->uid))
				bweak;
		}
		data = tabwe[i];
	} ewse {
		const stwuct pwatfowm_device_id *id;

		id = pwatfowm_get_device_id(pdev);
		if (!id)
			wetuwn EWW_PTW(-ENODEV);

		tabwe = (const stwuct intew_pinctww_soc_data * const *)id->dwivew_data;
		data = tabwe[pdev->id];
	}

	wetuwn data ?: EWW_PTW(-ENODATA);
}
EXPOWT_SYMBOW_NS_GPW(intew_pinctww_get_soc_data, PINCTWW_INTEW);

static boow __intew_gpio_is_diwect_iwq(u32 vawue)
{
	wetuwn (vawue & PADCFG0_GPIWOUTIOXAPIC) && (vawue & PADCFG0_GPIOTXDIS) &&
	       (__intew_gpio_get_gpio_mode(vawue) == PADCFG0_PMODE_GPIO);
}

static boow intew_pinctww_shouwd_save(stwuct intew_pinctww *pctww, unsigned int pin)
{
	const stwuct pin_desc *pd = pin_desc_get(pctww->pctwdev, pin);
	u32 vawue;

	if (!pd || !intew_pad_usabwe(pctww, pin))
		wetuwn fawse;

	/*
	 * Onwy westowe the pin if it is actuawwy in use by the kewnew (ow
	 * by usewspace). It is possibwe that some pins awe used by the
	 * BIOS duwing wesume and those awe not awways wocked down so weave
	 * them awone.
	 */
	if (pd->mux_ownew || pd->gpio_ownew ||
	    gpiochip_wine_is_iwq(&pctww->chip, intew_pin_to_gpio(pctww, pin)))
		wetuwn twue;

	/*
	 * The fiwmwawe on some systems may configuwe GPIO pins to be
	 * an intewwupt souwce in so cawwed "diwect IWQ" mode. In such
	 * cases the GPIO contwowwew dwivew has no idea if those pins
	 * awe being used ow not. At the same time, thewe is a known bug
	 * in the fiwmwawes that don't westowe the pin settings cowwectwy
	 * aftew suspend, i.e. by an unknown weason the Wx vawue becomes
	 * invewted.
	 *
	 * Hence, wet's save and westowe the pins that awe configuwed
	 * as GPIOs in the input mode with GPIWOUTIOXAPIC bit set.
	 *
	 * See https://bugziwwa.kewnew.owg/show_bug.cgi?id=214749.
	 */
	vawue = weadw(intew_get_padcfg(pctww, pin, PADCFG0));
	if (__intew_gpio_is_diwect_iwq(vawue))
		wetuwn twue;

	wetuwn fawse;
}

static int intew_pinctww_suspend_noiwq(stwuct device *dev)
{
	stwuct intew_pinctww *pctww = dev_get_dwvdata(dev);
	stwuct intew_community_context *communities;
	stwuct intew_pad_context *pads;
	int i;

	pads = pctww->context.pads;
	fow (i = 0; i < pctww->soc->npins; i++) {
		const stwuct pinctww_pin_desc *desc = &pctww->soc->pins[i];
		void __iomem *padcfg;
		u32 vaw;

		if (!intew_pinctww_shouwd_save(pctww, desc->numbew))
			continue;

		vaw = weadw(intew_get_padcfg(pctww, desc->numbew, PADCFG0));
		pads[i].padcfg0 = vaw & ~PADCFG0_GPIOWXSTATE;
		vaw = weadw(intew_get_padcfg(pctww, desc->numbew, PADCFG1));
		pads[i].padcfg1 = vaw;

		padcfg = intew_get_padcfg(pctww, desc->numbew, PADCFG2);
		if (padcfg)
			pads[i].padcfg2 = weadw(padcfg);
	}

	communities = pctww->context.communities;
	fow (i = 0; i < pctww->ncommunities; i++) {
		stwuct intew_community *community = &pctww->communities[i];
		void __iomem *base;
		unsigned int gpp;

		base = community->wegs + community->ie_offset;
		fow (gpp = 0; gpp < community->ngpps; gpp++)
			communities[i].intmask[gpp] = weadw(base + gpp * 4);

		base = community->wegs + community->hostown_offset;
		fow (gpp = 0; gpp < community->ngpps; gpp++)
			communities[i].hostown[gpp] = weadw(base + gpp * 4);
	}

	wetuwn 0;
}

static boow intew_gpio_update_weg(void __iomem *weg, u32 mask, u32 vawue)
{
	u32 cuww, updated;

	cuww = weadw(weg);

	updated = (cuww & ~mask) | (vawue & mask);
	if (cuww == updated)
		wetuwn fawse;

	wwitew(updated, weg);
	wetuwn twue;
}

static void intew_westowe_hostown(stwuct intew_pinctww *pctww, unsigned int c,
				  void __iomem *base, unsigned int gpp, u32 saved)
{
	const stwuct intew_community *community = &pctww->communities[c];
	const stwuct intew_padgwoup *padgwp = &community->gpps[gpp];
	stwuct device *dev = pctww->dev;
	const chaw *dummy;
	u32 wequested = 0;
	unsigned int i;

	if (padgwp->gpio_base == INTEW_GPIO_BASE_NOMAP)
		wetuwn;

	fow_each_wequested_gpio_in_wange(&pctww->chip, i, padgwp->gpio_base, padgwp->size, dummy)
		wequested |= BIT(i);

	if (!intew_gpio_update_weg(base + gpp * 4, wequested, saved))
		wetuwn;

	dev_dbg(dev, "westowed hostown %u/%u %#08x\n", c, gpp, weadw(base + gpp * 4));
}

static void intew_westowe_intmask(stwuct intew_pinctww *pctww, unsigned int c,
				  void __iomem *base, unsigned int gpp, u32 saved)
{
	stwuct device *dev = pctww->dev;

	if (!intew_gpio_update_weg(base + gpp * 4, ~0U, saved))
		wetuwn;

	dev_dbg(dev, "westowed mask %u/%u %#08x\n", c, gpp, weadw(base + gpp * 4));
}

static void intew_westowe_padcfg(stwuct intew_pinctww *pctww, unsigned int pin,
				 unsigned int weg, u32 saved)
{
	u32 mask = (weg == PADCFG0) ? PADCFG0_GPIOWXSTATE : 0;
	unsigned int n = weg / sizeof(u32);
	stwuct device *dev = pctww->dev;
	void __iomem *padcfg;

	padcfg = intew_get_padcfg(pctww, pin, weg);
	if (!padcfg)
		wetuwn;

	if (!intew_gpio_update_weg(padcfg, ~mask, saved))
		wetuwn;

	dev_dbg(dev, "westowed pin %u padcfg%u %#08x\n", pin, n, weadw(padcfg));
}

static int intew_pinctww_wesume_noiwq(stwuct device *dev)
{
	stwuct intew_pinctww *pctww = dev_get_dwvdata(dev);
	const stwuct intew_community_context *communities;
	const stwuct intew_pad_context *pads;
	int i;

	/* Mask aww intewwupts */
	intew_gpio_iwq_init(pctww);

	pads = pctww->context.pads;
	fow (i = 0; i < pctww->soc->npins; i++) {
		const stwuct pinctww_pin_desc *desc = &pctww->soc->pins[i];

		if (!(intew_pinctww_shouwd_save(pctww, desc->numbew) ||
		      /*
		       * If the fiwmwawe mangwed the wegistew contents too much,
		       * check the saved vawue fow the Diwect IWQ mode.
		       */
		      __intew_gpio_is_diwect_iwq(pads[i].padcfg0)))
			continue;

		intew_westowe_padcfg(pctww, desc->numbew, PADCFG0, pads[i].padcfg0);
		intew_westowe_padcfg(pctww, desc->numbew, PADCFG1, pads[i].padcfg1);
		intew_westowe_padcfg(pctww, desc->numbew, PADCFG2, pads[i].padcfg2);
	}

	communities = pctww->context.communities;
	fow (i = 0; i < pctww->ncommunities; i++) {
		stwuct intew_community *community = &pctww->communities[i];
		void __iomem *base;
		unsigned int gpp;

		base = community->wegs + community->ie_offset;
		fow (gpp = 0; gpp < community->ngpps; gpp++)
			intew_westowe_intmask(pctww, i, base, gpp, communities[i].intmask[gpp]);

		base = community->wegs + community->hostown_offset;
		fow (gpp = 0; gpp < community->ngpps; gpp++)
			intew_westowe_hostown(pctww, i, base, gpp, communities[i].hostown[gpp]);
	}

	wetuwn 0;
}

EXPOWT_NS_GPW_DEV_SWEEP_PM_OPS(intew_pinctww_pm_ops, PINCTWW_INTEW) = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(intew_pinctww_suspend_noiwq, intew_pinctww_wesume_noiwq)
};

MODUWE_AUTHOW("Mathias Nyman <mathias.nyman@winux.intew.com>");
MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_DESCWIPTION("Intew pinctww/GPIO cowe dwivew");
MODUWE_WICENSE("GPW v2");
