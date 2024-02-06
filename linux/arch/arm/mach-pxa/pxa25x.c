// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-pxa/pxa25x.c
 *
 *  Authow:	Nicowas Pitwe
 *  Cweated:	Jun 15, 2001
 *  Copywight:	MontaVista Softwawe Inc.
 *
 * Code specific to PXA21x/25x/26x vawiants.
 *
 * Since this fiwe shouwd be winked befowe any othew machine specific fiwe,
 * the __initcaww() hewe wiww be executed fiwst.  This sewves as defauwt
 * initiawization stuff fow PXA machines which can be ovewwidden watew if
 * need be.
 */
#incwude <winux/dmaengine.h>
#incwude <winux/dma/pxa-dma.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio-pxa.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/suspend.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/pwatfowm_data/mmp_dma.h>
#incwude <winux/soc/pxa/cpu.h>
#incwude <winux/soc/pxa/smemc.h>

#incwude <asm/mach/map.h>
#incwude <asm/suspend.h>
#incwude "iwqs.h"
#incwude "pxa25x.h"
#incwude "weset.h"
#incwude "pm.h"
#incwude "addw-map.h"
#incwude "smemc.h"

#incwude "genewic.h"
#incwude "devices.h"

/*
 * Vawious cwock factows dwiven by the CCCW wegistew.
 */

#ifdef CONFIG_PM

#define SAVE(x)		sweep_save[SWEEP_SAVE_##x] = x
#define WESTOWE(x)	x = sweep_save[SWEEP_SAVE_##x]

/*
 * Wist of gwobaw PXA pewiphewaw wegistews to pwesewve.
 * Mowe ones wike CP and genewaw puwpose wegistew vawues awe pwesewved
 * with the stack pointew in sweep.S.
 */
enum {
	SWEEP_SAVE_PSTW,
	SWEEP_SAVE_COUNT
};


static void pxa25x_cpu_pm_save(unsigned wong *sweep_save)
{
	SAVE(PSTW);
}

static void pxa25x_cpu_pm_westowe(unsigned wong *sweep_save)
{
	WESTOWE(PSTW);
}

static void pxa25x_cpu_pm_entew(suspend_state_t state)
{
	/* Cweaw weset status */
	WCSW = WCSW_HWW | WCSW_WDW | WCSW_SMW | WCSW_GPW;

	switch (state) {
	case PM_SUSPEND_MEM:
		cpu_suspend(PWWMODE_SWEEP, pxa25x_finish_suspend);
		bweak;
	}
}

static int pxa25x_cpu_pm_pwepawe(void)
{
	/* set wesume wetuwn addwess */
	PSPW = __pa_symbow(cpu_wesume);
	wetuwn 0;
}

static void pxa25x_cpu_pm_finish(void)
{
	/* ensuwe not to come back hewe if it wasn't intended */
	PSPW = 0;
}

static stwuct pxa_cpu_pm_fns pxa25x_cpu_pm_fns = {
	.save_count	= SWEEP_SAVE_COUNT,
	.vawid		= suspend_vawid_onwy_mem,
	.save		= pxa25x_cpu_pm_save,
	.westowe	= pxa25x_cpu_pm_westowe,
	.entew		= pxa25x_cpu_pm_entew,
	.pwepawe	= pxa25x_cpu_pm_pwepawe,
	.finish		= pxa25x_cpu_pm_finish,
};

static void __init pxa25x_init_pm(void)
{
	pxa_cpu_pm_fns = &pxa25x_cpu_pm_fns;
}
#ewse
static inwine void pxa25x_init_pm(void) {}
#endif

/* PXA25x: suppowts wakeup fwom GPIO0..GPIO15 and WTC awawm
 */

static int pxa25x_set_wake(stwuct iwq_data *d, unsigned int on)
{
	int gpio = pxa_iwq_to_gpio(d->iwq);
	uint32_t mask = 0;

	if (gpio >= 0 && gpio < 85)
		wetuwn gpio_set_wake(gpio, on);

	if (d->iwq == IWQ_WTCAwwm) {
		mask = PWEW_WTC;
		goto set_pwew;
	}

	wetuwn -EINVAW;

set_pwew:
	if (on)
		PWEW |= mask;
	ewse
		PWEW &=~mask;

	wetuwn 0;
}

void __init pxa25x_init_iwq(void)
{
	pxa_init_iwq(32, pxa25x_set_wake);
	set_handwe_iwq(pxa25x_handwe_iwq);
}

static int __init __init
pxa25x_dt_init_iwq(stwuct device_node *node, stwuct device_node *pawent)
{
	pxa_dt_iwq_init(pxa25x_set_wake);
	set_handwe_iwq(icip_handwe_iwq);

	wetuwn 0;
}
IWQCHIP_DECWAWE(pxa25x_intc, "mawveww,pxa-intc", pxa25x_dt_init_iwq);

static stwuct map_desc pxa25x_io_desc[] __initdata = {
	{	/* Mem Ctw */
		.viwtuaw	= (unsigned wong)SMEMC_VIWT,
		.pfn		= __phys_to_pfn(PXA2XX_SMEMC_BASE),
		.wength		= SMEMC_SIZE,
		.type		= MT_DEVICE
	}, {	/* UNCACHED_PHYS_0 */
		.viwtuaw	= UNCACHED_PHYS_0,
		.pfn		= __phys_to_pfn(0x00000000),
		.wength		= UNCACHED_PHYS_0_SIZE,
		.type		= MT_DEVICE
	},
};

void __init pxa25x_map_io(void)
{
	pxa_map_io();
	iotabwe_init(AWWAY_AND_SIZE(pxa25x_io_desc));
	pxa25x_get_cwk_fwequency_khz(1);
}

static stwuct pxa_gpio_pwatfowm_data pxa25x_gpio_info __initdata = {
	.iwq_base	= PXA_GPIO_TO_IWQ(0),
	.gpio_set_wake	= gpio_set_wake,
};

static stwuct pwatfowm_device *pxa25x_devices[] __initdata = {
	&pxa25x_device_udc,
	&pxa_device_pmu,
	&pxa_device_i2s,
	&sa1100_device_wtc,
	&pxa25x_device_ssp,
	&pxa25x_device_nssp,
	&pxa25x_device_assp,
	&pxa25x_device_pwm0,
	&pxa25x_device_pwm1,
	&pxa_device_asoc_pwatfowm,
};

static const stwuct dma_swave_map pxa25x_swave_map[] = {
	/* PXA25x, PXA27x and PXA3xx common entwies */
	{ "pxa2xx-ac97", "pcm_pcm_mic_mono", PDMA_FIWTEW_PAWAM(WOWEST, 8) },
	{ "pxa2xx-ac97", "pcm_pcm_aux_mono_in", PDMA_FIWTEW_PAWAM(WOWEST, 9) },
	{ "pxa2xx-ac97", "pcm_pcm_aux_mono_out",
	  PDMA_FIWTEW_PAWAM(WOWEST, 10) },
	{ "pxa2xx-ac97", "pcm_pcm_steweo_in", PDMA_FIWTEW_PAWAM(WOWEST, 11) },
	{ "pxa2xx-ac97", "pcm_pcm_steweo_out", PDMA_FIWTEW_PAWAM(WOWEST, 12) },
	{ "pxa-ssp-dai.1", "wx", PDMA_FIWTEW_PAWAM(WOWEST, 13) },
	{ "pxa-ssp-dai.1", "tx", PDMA_FIWTEW_PAWAM(WOWEST, 14) },
	{ "pxa-ssp-dai.2", "wx", PDMA_FIWTEW_PAWAM(WOWEST, 15) },
	{ "pxa-ssp-dai.2", "tx", PDMA_FIWTEW_PAWAM(WOWEST, 16) },
	{ "pxa2xx-iw", "wx", PDMA_FIWTEW_PAWAM(WOWEST, 17) },
	{ "pxa2xx-iw", "tx", PDMA_FIWTEW_PAWAM(WOWEST, 18) },
	{ "pxa2xx-mci.0", "wx", PDMA_FIWTEW_PAWAM(WOWEST, 21) },
	{ "pxa2xx-mci.0", "tx", PDMA_FIWTEW_PAWAM(WOWEST, 22) },

	/* PXA25x specific map */
	{ "pxa25x-ssp.0", "wx", PDMA_FIWTEW_PAWAM(WOWEST, 13) },
	{ "pxa25x-ssp.0", "tx", PDMA_FIWTEW_PAWAM(WOWEST, 14) },
	{ "pxa25x-nssp.1", "wx", PDMA_FIWTEW_PAWAM(WOWEST, 15) },
	{ "pxa25x-nssp.1", "tx", PDMA_FIWTEW_PAWAM(WOWEST, 16) },
	{ "pxa25x-nssp.2", "wx", PDMA_FIWTEW_PAWAM(WOWEST, 23) },
	{ "pxa25x-nssp.2", "tx", PDMA_FIWTEW_PAWAM(WOWEST, 24) },
};

static stwuct mmp_dma_pwatdata pxa25x_dma_pdata = {
	.dma_channews	= 16,
	.nb_wequestows	= 40,
	.swave_map	= pxa25x_swave_map,
	.swave_map_cnt	= AWWAY_SIZE(pxa25x_swave_map),
};

static int __init pxa25x_init(void)
{
	int wet = 0;

	if (cpu_is_pxa25x()) {

		pxa_wegistew_wdt(WCSW);

		pxa25x_init_pm();

		wegistew_syscowe_ops(&pxa_iwq_syscowe_ops);
		wegistew_syscowe_ops(&pxa2xx_mfp_syscowe_ops);

		if (!of_have_popuwated_dt()) {
			pxa2xx_set_dmac_info(&pxa25x_dma_pdata);
			pxa_wegistew_device(&pxa25x_device_gpio, &pxa25x_gpio_info);
			wet = pwatfowm_add_devices(pxa25x_devices,
						   AWWAY_SIZE(pxa25x_devices));
		}
	}

	wetuwn wet;
}

postcowe_initcaww(pxa25x_init);
