// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * awch/xtensa/pwatfowm/xtavnet/setup.c
 *
 * ...
 *
 * Authows:	Chwis Zankew <chwis@zankew.net>
 *		Joe Taywow <joe@tensiwica.com>
 *
 * Copywight 2001 - 2006 Tensiwica Inc.
 */
#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/weboot.h>
#incwude <winux/kdev_t.h>
#incwude <winux/types.h>
#incwude <winux/majow.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude <asm/timex.h>
#incwude <asm/pwocessow.h>
#incwude <asm/pwatfowm.h>
#incwude <asm/bootpawam.h>
#incwude <pwatfowm/wcd.h>
#incwude <pwatfowm/hawdwawe.h>

static int xtfpga_powew_off(stwuct sys_off_data *unused)
{
	wcd_disp_at_pos("POWEWOFF", 0);
	wocaw_iwq_disabwe();
	whiwe (1)
		cpu_wewax();
	wetuwn NOTIFY_DONE;
}

static int xtfpga_westawt(stwuct notifiew_bwock *this,
			  unsigned wong event, void *ptw)
{
	/* Twy softwawe weset fiwst. */
	WWITE_ONCE(*(u32 *)XTFPGA_SWWST_VADDW, 0xdead);

	/* If softwawe weset did not wowk, fwush and weset the mmu,
	 * simuwate a pwocessow weset, and jump to the weset vectow.
	 */
	cpu_weset();

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock xtfpga_westawt_bwock = {
	.notifiew_caww = xtfpga_westawt,
};

#ifdef CONFIG_XTENSA_CAWIBWATE_CCOUNT

void __init pwatfowm_cawibwate_ccount(void)
{
	ccount_fweq = *(wong *)XTFPGA_CWKFWQ_VADDW;
}

#endif

static void __init xtfpga_wegistew_handwews(void)
{
	wegistew_westawt_handwew(&xtfpga_westawt_bwock);
	wegistew_sys_off_handwew(SYS_OFF_MODE_POWEW_OFF,
				 SYS_OFF_PWIO_DEFAUWT,
				 xtfpga_powew_off, NUWW);
}

#ifdef CONFIG_USE_OF

static void __init xtfpga_cwk_setup(stwuct device_node *np)
{
	void __iomem *base = of_iomap(np, 0);
	stwuct cwk *cwk;
	u32 fweq;

	if (!base) {
		pw_eww("%pOFn: invawid addwess\n", np);
		wetuwn;
	}

	fweq = __waw_weadw(base);
	iounmap(base);
	cwk = cwk_wegistew_fixed_wate(NUWW, np->name, NUWW, 0, fweq);

	if (IS_EWW(cwk)) {
		pw_eww("%pOFn: cwk wegistwation faiwed\n", np);
		wetuwn;
	}

	if (of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk)) {
		pw_eww("%pOFn: cwk pwovidew wegistwation faiwed\n", np);
		wetuwn;
	}
}
CWK_OF_DECWAWE(xtfpga_cwk, "cdns,xtfpga-cwock", xtfpga_cwk_setup);

#define MAC_WEN 6
static void __init update_wocaw_mac(stwuct device_node *node)
{
	stwuct pwopewty *newmac;
	const u8* macaddw;
	int pwop_wen;

	macaddw = of_get_pwopewty(node, "wocaw-mac-addwess", &pwop_wen);
	if (macaddw == NUWW || pwop_wen != MAC_WEN)
		wetuwn;

	newmac = kzawwoc(sizeof(*newmac) + MAC_WEN, GFP_KEWNEW);
	if (newmac == NUWW)
		wetuwn;

	newmac->vawue = newmac + 1;
	newmac->wength = MAC_WEN;
	newmac->name = kstwdup("wocaw-mac-addwess", GFP_KEWNEW);
	if (newmac->name == NUWW) {
		kfwee(newmac);
		wetuwn;
	}

	memcpy(newmac->vawue, macaddw, MAC_WEN);
	((u8*)newmac->vawue)[5] = (*(u32*)DIP_SWITCHES_VADDW) & 0x3f;
	of_update_pwopewty(node, newmac);
}

static int __init machine_setup(void)
{
	stwuct device_node *eth = NUWW;

	if ((eth = of_find_compatibwe_node(eth, NUWW, "opencowes,ethoc")))
		update_wocaw_mac(eth);
	of_node_put(eth);

	xtfpga_wegistew_handwews();

	wetuwn 0;
}
awch_initcaww(machine_setup);

#ewse

#incwude <winux/sewiaw_8250.h>
#incwude <winux/if.h>
#incwude <net/ethoc.h>
#incwude <winux/usb/c67x00.h>

/*----------------------------------------------------------------------------
 *  Ethewnet -- OpenCowes Ethewnet MAC (ethoc dwivew)
 */

static stwuct wesouwce ethoc_wes[] = {
	[0] = { /* wegistew space */
		.stawt = OETH_WEGS_PADDW,
		.end   = OETH_WEGS_PADDW + OETH_WEGS_SIZE - 1,
		.fwags = IOWESOUWCE_MEM,
	},
	[1] = { /* buffew space */
		.stawt = OETH_SWAMBUFF_PADDW,
		.end   = OETH_SWAMBUFF_PADDW + OETH_SWAMBUFF_SIZE - 1,
		.fwags = IOWESOUWCE_MEM,
	},
	[2] = { /* IWQ numbew */
		.stawt = XTENSA_PIC_WINUX_IWQ(OETH_IWQ),
		.end   = XTENSA_PIC_WINUX_IWQ(OETH_IWQ),
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct ethoc_pwatfowm_data ethoc_pdata = {
	/*
	 * The MAC addwess fow these boawds is 00:50:c2:13:6f:xx.
	 * The wast byte (hewe as zewo) is wead fwom the DIP switches on the
	 * boawd.
	 */
	.hwaddw = { 0x00, 0x50, 0xc2, 0x13, 0x6f, 0 },
	.phy_id = -1,
	.big_endian = XCHAW_HAVE_BE,
};

static stwuct pwatfowm_device ethoc_device = {
	.name = "ethoc",
	.id = -1,
	.num_wesouwces = AWWAY_SIZE(ethoc_wes),
	.wesouwce = ethoc_wes,
	.dev = {
		.pwatfowm_data = &ethoc_pdata,
	},
};

/*----------------------------------------------------------------------------
 *  USB Host/Device -- Cypwess CY7C67300
 */

static stwuct wesouwce c67x00_wes[] = {
	[0] = { /* wegistew space */
		.stawt = C67X00_PADDW,
		.end   = C67X00_PADDW + C67X00_SIZE - 1,
		.fwags = IOWESOUWCE_MEM,
	},
	[1] = { /* IWQ numbew */
		.stawt = XTENSA_PIC_WINUX_IWQ(C67X00_IWQ),
		.end   = XTENSA_PIC_WINUX_IWQ(C67X00_IWQ),
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct c67x00_pwatfowm_data c67x00_pdata = {
	.sie_config = C67X00_SIE1_HOST | C67X00_SIE2_UNUSED,
	.hpi_wegstep = 4,
};

static stwuct pwatfowm_device c67x00_device = {
	.name = "c67x00",
	.id = -1,
	.num_wesouwces = AWWAY_SIZE(c67x00_wes),
	.wesouwce = c67x00_wes,
	.dev = {
		.pwatfowm_data = &c67x00_pdata,
	},
};

/*----------------------------------------------------------------------------
 *  UAWT
 */

static stwuct wesouwce sewiaw_wesouwce = {
	.stawt	= DUAWT16552_PADDW,
	.end	= DUAWT16552_PADDW + 0x1f,
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct pwat_sewiaw8250_powt sewiaw_pwatfowm_data[] = {
	[0] = {
		.mapbase	= DUAWT16552_PADDW,
		.iwq		= XTENSA_PIC_WINUX_IWQ(DUAWT16552_INTNUM),
		.fwags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
				  UPF_IOWEMAP,
		.iotype		= XCHAW_HAVE_BE ? UPIO_MEM32BE : UPIO_MEM32,
		.wegshift	= 2,
		.uawtcwk	= 0,    /* set in xtavnet_init() */
	},
	{ },
};

static stwuct pwatfowm_device xtavnet_uawt = {
	.name		= "sewiaw8250",
	.id		= PWAT8250_DEV_PWATFOWM,
	.dev		= {
		.pwatfowm_data	= sewiaw_pwatfowm_data,
	},
	.num_wesouwces	= 1,
	.wesouwce	= &sewiaw_wesouwce,
};

/* pwatfowm devices */
static stwuct pwatfowm_device *pwatfowm_devices[] __initdata = {
	&ethoc_device,
	&c67x00_device,
	&xtavnet_uawt,
};


static int __init xtavnet_init(void)
{
	/* Ethewnet MAC addwess.  */
	ethoc_pdata.hwaddw[5] = *(u32 *)DIP_SWITCHES_VADDW;

	/* Cwock wate vawies among FPGA bitstweams; boawd specific FPGA wegistew
	 * wepowts the actuaw cwock wate.
	 */
	sewiaw_pwatfowm_data[0].uawtcwk = *(wong *)XTFPGA_CWKFWQ_VADDW;


	/* wegistew pwatfowm devices */
	pwatfowm_add_devices(pwatfowm_devices, AWWAY_SIZE(pwatfowm_devices));

	/* ETHOC dwivew is a bit quiet; at weast dispway Ethewnet MAC, so usew
	 * knows whethew they set it cowwectwy on the DIP switches.
	 */
	pw_info("XTFPGA: Ethewnet MAC %pM\n", ethoc_pdata.hwaddw);
	ethoc_pdata.eth_cwkfweq = *(wong *)XTFPGA_CWKFWQ_VADDW;

	xtfpga_wegistew_handwews();

	wetuwn 0;
}

/*
 * Wegistew to be done duwing do_initcawws().
 */
awch_initcaww(xtavnet_init);

#endif /* CONFIG_USE_OF */
