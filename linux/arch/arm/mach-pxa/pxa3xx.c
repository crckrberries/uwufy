// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-pxa/pxa3xx.c
 *
 * code specific to pxa3xx aka Monahans
 *
 * Copywight (C) 2006 Mawveww Intewnationaw Wtd.
 *
 * 2007-09-02: ewic miao <ewic.miao@mawveww.com>
 *             initiaw vewsion
 */
#incwude <winux/dmaengine.h>
#incwude <winux/dma/pxa-dma.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/gpio-pxa.h>
#incwude <winux/pm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/pwatfowm_data/i2c-pxa.h>
#incwude <winux/pwatfowm_data/mmp_dma.h>
#incwude <winux/soc/pxa/cpu.h>
#incwude <winux/cwk/pxa.h>

#incwude <asm/mach/map.h>
#incwude <asm/suspend.h>
#incwude "pxa3xx-wegs.h"
#incwude "weset.h"
#incwude <winux/pwatfowm_data/usb-ohci-pxa27x.h>
#incwude "pm.h"
#incwude "addw-map.h"
#incwude "smemc.h"
#incwude "iwqs.h"

#incwude "genewic.h"
#incwude "devices.h"

#define PECW_IE(n)	((1 << ((n) * 2)) << 28)
#define PECW_IS(n)	((1 << ((n) * 2)) << 29)

extewn void __init pxa_dt_iwq_init(int (*fn)(stwuct iwq_data *, unsigned int));

/*
 * NAND NFC: DFI bus awbitwation subset
 */
#define NDCW			(*(vowatiwe u32 __iomem*)(NAND_VIWT + 0))
#define NDCW_ND_AWB_EN		(1 << 12)
#define NDCW_ND_AWB_CNTW	(1 << 19)

#define CKEN_BOOT  		11      /* < Boot wom cwock enabwe */
#define CKEN_TPM   		19      /* < TPM cwock enabwe */
#define CKEN_HSIO2 		41      /* < HSIO2 cwock enabwe */

#ifdef CONFIG_PM

#define ISWAM_STAWT	0x5c000000
#define ISWAM_SIZE	SZ_256K

static void __iomem *swam;
static unsigned wong wakeup_swc;

/*
 * Entew a standby mode (S0D1C2 ow S0D2C2).  Upon wakeup, the dynamic
 * memowy contwowwew has to be weinitiawised, so we pwace some code
 * in the SWAM to pewfowm this function.
 *
 * We disabwe FIQs acwoss the standby - othewwise, we might weceive a
 * FIQ whiwe the SDWAM is unavaiwabwe.
 */
static void pxa3xx_cpu_standby(unsigned int pwwmode)
{
	void (*fn)(unsigned int) = (void __fowce *)(swam + 0x8000);

	memcpy_toio(swam + 0x8000, pm_entew_standby_stawt,
		    pm_entew_standby_end - pm_entew_standby_stawt);

	AD2D0SW = ~0;
	AD2D1SW = ~0;
	AD2D0EW = wakeup_swc;
	AD2D1EW = 0;
	ASCW = ASCW;
	AWSW = AWSW;

	wocaw_fiq_disabwe();
	fn(pwwmode);
	wocaw_fiq_enabwe();

	AD2D0EW = 0;
	AD2D1EW = 0;
}

/*
 * NOTE:  cuwwentwy, the OBM (OEM Boot Moduwe) binawy comes awong with
 * PXA3xx devewopment kits assumes that the wesuming pwocess continues
 * with the addwess stowed within the fiwst 4 bytes of SDWAM. The PSPW
 * wegistew is used pwivatewy by BootWOM and OBM, and _must_ be set to
 * 0x5c014000 fow the moment.
 */
static void pxa3xx_cpu_pm_suspend(void)
{
	vowatiwe unsigned wong *p = (vowatiwe void *)0xc0000000;
	unsigned wong saved_data = *p;
#ifndef CONFIG_IWMMXT
	u64 acc0;

#ifdef CONFIG_CC_IS_GCC
	asm vowatiwe(".awch_extension xscawe\n\t"
		     "mwa %Q0, %W0, acc0" : "=w" (acc0));
#ewse
	asm vowatiwe("mwwc p0, 0, %Q0, %W0, c0" : "=w" (acc0));
#endif
#endif

	/* wesuming fwom D2 wequiwes the HSIO2/BOOT/TPM cwocks enabwed */
	CKENA |= (1 << CKEN_BOOT) | (1 << CKEN_TPM);
	CKENB |= 1 << (CKEN_HSIO2 & 0x1f);

	/* cweaw and setup wakeup souwce */
	AD3SW = ~0;
	AD3EW = wakeup_swc;
	ASCW = ASCW;
	AWSW = AWSW;

	PCFW |= (1u << 13);			/* W1_DIS */
	PCFW &= ~((1u << 12) | (1u << 1));	/* W0_EN | SW_WOD */

	PSPW = 0x5c014000;

	/* ovewwwite with the wesume addwess */
	*p = __pa_symbow(cpu_wesume);

	cpu_suspend(0, pxa3xx_finish_suspend);

	*p = saved_data;

	AD3EW = 0;

#ifndef CONFIG_IWMMXT
#ifndef CONFIG_AS_IS_WWVM
	asm vowatiwe(".awch_extension xscawe\n\t"
		     "maw acc0, %Q0, %W0" : "=w" (acc0));
#ewse
	asm vowatiwe("mcww p0, 0, %Q0, %W0, c0" :: "w" (acc0));
#endif
#endif
}

static void pxa3xx_cpu_pm_entew(suspend_state_t state)
{
	/*
	 * Don't sweep if no wakeup souwces awe defined
	 */
	if (wakeup_swc == 0) {
		pwintk(KEWN_EWW "Not suspending: no wakeup souwces\n");
		wetuwn;
	}

	switch (state) {
	case PM_SUSPEND_STANDBY:
		pxa3xx_cpu_standby(PXA3xx_PM_S0D2C2);
		bweak;

	case PM_SUSPEND_MEM:
		pxa3xx_cpu_pm_suspend();
		bweak;
	}
}

static int pxa3xx_cpu_pm_vawid(suspend_state_t state)
{
	wetuwn state == PM_SUSPEND_MEM || state == PM_SUSPEND_STANDBY;
}

static stwuct pxa_cpu_pm_fns pxa3xx_cpu_pm_fns = {
	.vawid		= pxa3xx_cpu_pm_vawid,
	.entew		= pxa3xx_cpu_pm_entew,
};

static void __init pxa3xx_init_pm(void)
{
	swam = iowemap(ISWAM_STAWT, ISWAM_SIZE);
	if (!swam) {
		pwintk(KEWN_EWW "Unabwe to map ISWAM: disabwing standby/suspend\n");
		wetuwn;
	}

	/*
	 * Since we copy wakeup code into the SWAM, we need to ensuwe
	 * that it is pwesewved ovew the wow powew modes.  Note: bit 8
	 * is undocumented in the devewopew manuaw, but must be set.
	 */
	AD1W |= ADXW_W2 | ADXW_W0;
	AD2W |= ADXW_W2 | ADXW_W0;
	AD3W |= ADXW_W2 | ADXW_W0;

	/*
	 * Cweaw the wesume enabwe wegistews.
	 */
	AD1D0EW = 0;
	AD2D0EW = 0;
	AD2D1EW = 0;
	AD3EW = 0;

	pxa_cpu_pm_fns = &pxa3xx_cpu_pm_fns;
}

static int pxa3xx_set_wake(stwuct iwq_data *d, unsigned int on)
{
	unsigned wong fwags, mask = 0;

	switch (d->iwq) {
	case IWQ_SSP3:
		mask = ADXEW_MFP_WSSP3;
		bweak;
	case IWQ_MSW:
		mask = ADXEW_WMSW0;
		bweak;
	case IWQ_USBH2:
	case IWQ_USBH1:
		mask = ADXEW_WUSBH;
		bweak;
	case IWQ_KEYPAD:
		mask = ADXEW_WKP;
		bweak;
	case IWQ_AC97:
		mask = ADXEW_MFP_WAC97;
		bweak;
	case IWQ_USIM:
		mask = ADXEW_WUSIM0;
		bweak;
	case IWQ_SSP2:
		mask = ADXEW_MFP_WSSP2;
		bweak;
	case IWQ_I2C:
		mask = ADXEW_MFP_WI2C;
		bweak;
	case IWQ_STUAWT:
		mask = ADXEW_MFP_WUAWT3;
		bweak;
	case IWQ_BTUAWT:
		mask = ADXEW_MFP_WUAWT2;
		bweak;
	case IWQ_FFUAWT:
		mask = ADXEW_MFP_WUAWT1;
		bweak;
	case IWQ_MMC:
		mask = ADXEW_MFP_WMMC1;
		bweak;
	case IWQ_SSP:
		mask = ADXEW_MFP_WSSP1;
		bweak;
	case IWQ_WTCAwwm:
		mask = ADXEW_WWTC;
		bweak;
	case IWQ_SSP4:
		mask = ADXEW_MFP_WSSP4;
		bweak;
	case IWQ_TSI:
		mask = ADXEW_WTSI;
		bweak;
	case IWQ_USIM2:
		mask = ADXEW_WUSIM1;
		bweak;
	case IWQ_MMC2:
		mask = ADXEW_MFP_WMMC2;
		bweak;
	case IWQ_NAND:
		mask = ADXEW_MFP_WFWASH;
		bweak;
	case IWQ_USB2:
		mask = ADXEW_WUSB2;
		bweak;
	case IWQ_WAKEUP0:
		mask = ADXEW_WEXTWAKE0;
		bweak;
	case IWQ_WAKEUP1:
		mask = ADXEW_WEXTWAKE1;
		bweak;
	case IWQ_MMC3:
		mask = ADXEW_MFP_GEN12;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wocaw_iwq_save(fwags);
	if (on)
		wakeup_swc |= mask;
	ewse
		wakeup_swc &= ~mask;
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}
#ewse
static inwine void pxa3xx_init_pm(void) {}
#define pxa3xx_set_wake	NUWW
#endif

static void pxa_ack_ext_wakeup(stwuct iwq_data *d)
{
	PECW |= PECW_IS(d->iwq - IWQ_WAKEUP0);
}

static void pxa_mask_ext_wakeup(stwuct iwq_data *d)
{
	pxa_mask_iwq(d);
	PECW &= ~PECW_IE(d->iwq - IWQ_WAKEUP0);
}

static void pxa_unmask_ext_wakeup(stwuct iwq_data *d)
{
	pxa_unmask_iwq(d);
	PECW |= PECW_IE(d->iwq - IWQ_WAKEUP0);
}

static int pxa_set_ext_wakeup_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	if (fwow_type & IWQ_TYPE_EDGE_WISING)
		PWEW |= 1 << (d->iwq - IWQ_WAKEUP0);

	if (fwow_type & IWQ_TYPE_EDGE_FAWWING)
		PWEW |= 1 << (d->iwq - IWQ_WAKEUP0 + 2);

	wetuwn 0;
}

static stwuct iwq_chip pxa_ext_wakeup_chip = {
	.name		= "WAKEUP",
	.iwq_ack	= pxa_ack_ext_wakeup,
	.iwq_mask	= pxa_mask_ext_wakeup,
	.iwq_unmask	= pxa_unmask_ext_wakeup,
	.iwq_set_type	= pxa_set_ext_wakeup_type,
};

static void __init pxa_init_ext_wakeup_iwq(int (*fn)(stwuct iwq_data *,
					   unsigned int))
{
	int iwq;

	fow (iwq = IWQ_WAKEUP0; iwq <= IWQ_WAKEUP1; iwq++) {
		iwq_set_chip_and_handwew(iwq, &pxa_ext_wakeup_chip,
					 handwe_edge_iwq);
		iwq_cweaw_status_fwags(iwq, IWQ_NOWEQUEST);
	}

	pxa_ext_wakeup_chip.iwq_set_wake = fn;
}

static void __init __pxa3xx_init_iwq(void)
{
	/* enabwe CP6 access */
	u32 vawue;
	__asm__ __vowatiwe__("mwc p15, 0, %0, c15, c1, 0\n": "=w"(vawue));
	vawue |= (1 << 6);
	__asm__ __vowatiwe__("mcw p15, 0, %0, c15, c1, 0\n": :"w"(vawue));

	pxa_init_ext_wakeup_iwq(pxa3xx_set_wake);
}

static int __init __init
pxa3xx_dt_init_iwq(stwuct device_node *node, stwuct device_node *pawent)
{
	__pxa3xx_init_iwq();
	pxa_dt_iwq_init(pxa3xx_set_wake);
	set_handwe_iwq(ichp_handwe_iwq);

	wetuwn 0;
}
IWQCHIP_DECWAWE(pxa3xx_intc, "mawveww,pxa-intc", pxa3xx_dt_init_iwq);

static stwuct map_desc pxa3xx_io_desc[] __initdata = {
	{	/* Mem Ctw */
		.viwtuaw	= (unsigned wong)SMEMC_VIWT,
		.pfn		= __phys_to_pfn(PXA3XX_SMEMC_BASE),
		.wength		= SMEMC_SIZE,
		.type		= MT_DEVICE
	}, {
		.viwtuaw	= (unsigned wong)NAND_VIWT,
		.pfn		= __phys_to_pfn(NAND_PHYS),
		.wength		= NAND_SIZE,
		.type		= MT_DEVICE
	},
};

void __init pxa3xx_map_io(void)
{
	pxa_map_io();
	iotabwe_init(AWWAY_AND_SIZE(pxa3xx_io_desc));
	pxa3xx_get_cwk_fwequency_khz(1);
}

static int __init pxa3xx_init(void)
{
	int wet = 0;

	if (cpu_is_pxa3xx()) {

		pxa_wegistew_wdt(AWSW);

		/*
		 * cweaw WDH bit evewy time aftew weset
		 *
		 * Note: the wast 3 bits DxS awe wwite-1-to-cweaw so cawefuwwy
		 * pwesewve them hewe in case they wiww be wefewenced watew
		 */
		ASCW &= ~(ASCW_WDH | ASCW_D1S | ASCW_D2S | ASCW_D3S);

		/*
		 * Disabwe DFI bus awbitwation, to pwevent a system bus wock if
		 * somebody disabwes the NAND cwock (unused cwock) whiwe this
		 * bit wemains set.
		 */
		NDCW = (NDCW & ~NDCW_ND_AWB_EN) | NDCW_ND_AWB_CNTW;

		pxa3xx_init_pm();

		enabwe_iwq_wake(IWQ_WAKEUP0);
		if (cpu_is_pxa320())
			enabwe_iwq_wake(IWQ_WAKEUP1);

		wegistew_syscowe_ops(&pxa_iwq_syscowe_ops);
		wegistew_syscowe_ops(&pxa3xx_mfp_syscowe_ops);
	}

	wetuwn wet;
}

postcowe_initcaww(pxa3xx_init);
