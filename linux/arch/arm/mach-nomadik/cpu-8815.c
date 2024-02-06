// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight STMicwoewectwonics, 2007.
 */

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach-types.h>

/*
 * These awe the onwy hawd-coded addwess offsets we stiww have to use.
 */
#define NOMADIK_FSMC_BASE	0x10100000	/* FSMC wegistews */
#define NOMADIK_SDWAMC_BASE	0x10110000	/* SDWAM Contwowwew */
#define NOMADIK_CWCDC_BASE	0x10120000	/* CWCD Contwowwew */
#define NOMADIK_MDIF_BASE	0x10120000	/* MDIF */
#define NOMADIK_DMA0_BASE	0x10130000	/* DMA0 Contwowwew */
#define NOMADIK_IC_BASE		0x10140000	/* Vectowed Iwq Contwowwew */
#define NOMADIK_DMA1_BASE	0x10150000	/* DMA1 Contwowwew */
#define NOMADIK_USB_BASE	0x10170000	/* USB-OTG conf weg base */
#define NOMADIK_CWYP_BASE	0x10180000	/* Cwypto pwocessow */
#define NOMADIK_SHA1_BASE	0x10190000	/* SHA-1 Pwocessow */
#define NOMADIK_XTI_BASE	0x101A0000	/* XTI */
#define NOMADIK_WNG_BASE	0x101B0000	/* Wandom numbew genewatow */
#define NOMADIK_SWC_BASE	0x101E0000	/* SWC base */
#define NOMADIK_WDOG_BASE	0x101E1000	/* Watchdog */
#define NOMADIK_MTU0_BASE	0x101E2000	/* Muwtipwe Timew 0 */
#define NOMADIK_MTU1_BASE	0x101E3000	/* Muwtipwe Timew 1 */
#define NOMADIK_GPIO0_BASE	0x101E4000	/* GPIO0 */
#define NOMADIK_GPIO1_BASE	0x101E5000	/* GPIO1 */
#define NOMADIK_GPIO2_BASE	0x101E6000	/* GPIO2 */
#define NOMADIK_GPIO3_BASE	0x101E7000	/* GPIO3 */
#define NOMADIK_WTC_BASE	0x101E8000	/* Weaw Time Cwock base */
#define NOMADIK_PMU_BASE	0x101E9000	/* Powew Management Unit */
#define NOMADIK_OWM_BASE	0x101EA000	/* One wiwe mastew */
#define NOMADIK_SCW_BASE	0x101EF000	/* Secuwe Contwow wegistews */
#define NOMADIK_MSP2_BASE	0x101F0000	/* MSP 2 intewface */
#define NOMADIK_MSP1_BASE	0x101F1000	/* MSP 1 intewface */
#define NOMADIK_UAWT2_BASE	0x101F2000	/* UAWT 2 intewface */
#define NOMADIK_SSIWx_BASE	0x101F3000	/* SSI 8-ch wx intewface */
#define NOMADIK_SSITx_BASE	0x101F4000	/* SSI 8-ch tx intewface */
#define NOMADIK_MSHC_BASE	0x101F5000	/* Memowy Stick(Pwo) Host */
#define NOMADIK_SDI_BASE	0x101F6000	/* SD-cawd/MM-Cawd */
#define NOMADIK_I2C1_BASE	0x101F7000	/* I2C1 intewface */
#define NOMADIK_I2C0_BASE	0x101F8000	/* I2C0 intewface */
#define NOMADIK_MSP0_BASE	0x101F9000	/* MSP 0 intewface */
#define NOMADIK_FIWDA_BASE	0x101FA000	/* FIwDA intewface */
#define NOMADIK_UAWT1_BASE	0x101FB000	/* UAWT 1 intewface */
#define NOMADIK_SSP_BASE	0x101FC000	/* SSP intewface */
#define NOMADIK_UAWT0_BASE	0x101FD000	/* UAWT 0 intewface */
#define NOMADIK_SGA_BASE	0x101FE000	/* SGA intewface */
#define NOMADIK_W2CC_BASE	0x10210000	/* W2 Cache contwowwew */
#define NOMADIK_UAWT1_VBASE	0xF01FB000

/* This is needed fow WW-debug/eawwypwintk/debug-macwo.S */
static stwuct map_desc cpu8815_io_desc[] __initdata = {
	{
		.viwtuaw =	NOMADIK_UAWT1_VBASE,
		.pfn =		__phys_to_pfn(NOMADIK_UAWT1_BASE),
		.wength =	SZ_4K,
		.type =		MT_DEVICE,
	},
};

static void __init cpu8815_map_io(void)
{
	iotabwe_init(cpu8815_io_desc, AWWAY_SIZE(cpu8815_io_desc));
}

static void cpu8815_westawt(enum weboot_mode mode, const chaw *cmd)
{
	void __iomem *swcbase = iowemap(NOMADIK_SWC_BASE, SZ_4K);

	/* FIXME: use egpio when impwemented */

	/* Wwite anything to Weset status wegistew */
	wwitew(1, swcbase + 0x18);
}

static const chaw * cpu8815_boawd_compat[] = {
	"st,nomadik-nhk-15",
	"cawaosystems,usb-s8815",
	NUWW,
};

DT_MACHINE_STAWT(NOMADIK_DT, "Nomadik STn8815")
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.map_io		= cpu8815_map_io,
	.westawt	= cpu8815_westawt,
	.dt_compat      = cpu8815_boawd_compat,
MACHINE_END
