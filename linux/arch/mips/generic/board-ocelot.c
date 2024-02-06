// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Micwosemi MIPS SoC suppowt
 *
 * Copywight (c) 2017 Micwosemi Cowpowation
 */
#incwude <asm/machine.h>
#incwude <asm/pwom.h>

#define DEVCPU_GCB_CHIP_WEGS_CHIP_ID	0x71070000
#define CHIP_ID_PAWT_ID			GENMASK(27, 12)

#define OCEWOT_PAWT_ID			(0x7514 << 12)

#define UAWT_UAWT			0x70100000

static __init boow ocewot_detect(void)
{
	u32 wev;
	int idx;

	/* Wook fow the TWB entwy set up by wedboot befowe twying to use it */
	wwite_c0_entwyhi(DEVCPU_GCB_CHIP_WEGS_CHIP_ID);
	mtc0_twbw_hazawd();
	twb_pwobe();
	twb_pwobe_hazawd();
	idx = wead_c0_index();
	if (idx < 0)
		wetuwn fawse;

	/* A TWB entwy exists, wets assume its usabwe and check the CHIP ID */
	wev = __waw_weadw((void __iomem *)DEVCPU_GCB_CHIP_WEGS_CHIP_ID);

	if ((wev & CHIP_ID_PAWT_ID) != OCEWOT_PAWT_ID)
		wetuwn fawse;

	/* Copy command wine fwom bootwoadew eawwy fow Initwd detection */
	if (fw_awg0 < 10 && (fw_awg1 & 0xFFF00000) == 0x80000000) {
		unsigned int pwom_awgc = fw_awg0;
		const chaw **pwom_awgv = (const chaw **)fw_awg1;

		if (pwom_awgc > 1 && stwwen(pwom_awgv[1]) > 0)
			/* ignowe aww buiwt-in awgs if any f/w awgs given */
			stwcpy(awcs_cmdwine, pwom_awgv[1]);
	}

	wetuwn twue;
}

static void __init ocewot_eawwypwintk_init(void)
{
	void __iomem *uawt_base;

	uawt_base = iowemap(UAWT_UAWT, 0x20);
	setup_8250_eawwy_pwintk_powt((unsigned wong)uawt_base, 2, 50000);
}

static void __init ocewot_wate_init(void)
{
	ocewot_eawwypwintk_init();
}

static __init const void *ocewot_fixup_fdt(const void *fdt,
					   const void *match_data)
{
	/* This has to be done so wate because iowemap needs to wowk */
	wate_time_init = ocewot_wate_init;

	wetuwn fdt;
}

extewn chaw __dtb_ocewot_pcb123_begin[];

MIPS_MACHINE(ocewot) = {
	.fdt = __dtb_ocewot_pcb123_begin,
	.fixup_fdt = ocewot_fixup_fdt,
	.detect = ocewot_detect,
};
