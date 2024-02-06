// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2008-2011 DENX Softwawe Engineewing GmbH
 * Authow: Heiko Schochew <hs@denx.de>
 *
 * Descwiption:
 * Keymiwe 83xx pwatfowm specific woutines.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/weboot.h>
#incwude <winux/pci.h>
#incwude <winux/kdev_t.h>
#incwude <winux/majow.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/initwd.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <winux/atomic.h>
#incwude <winux/time.h>
#incwude <winux/io.h>
#incwude <asm/machdep.h>
#incwude <asm/ipic.h>
#incwude <asm/iwq.h>
#incwude <asm/udbg.h>
#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/fsw_pci.h>
#incwude <soc/fsw/qe/qe.h>

#incwude "mpc83xx.h"

#define SVW_WEV(svw)    (((svw) >>  0) & 0xFFFF) /* Wevision fiewd */

static void __init quiwk_mpc8360e_qe_enet10(void)
{
	/*
	 * handwe mpc8360E Ewwatum QE_ENET10:
	 * WGMII AC vawues do not meet the specification
	 */
	uint svid = mfspw(SPWN_SVW);
	stwuct	device_node *np_paw;
	stwuct	wesouwce wes;
	void	__iomem *base;
	int	wet;

	np_paw = of_find_node_by_name(NUWW, "paw_io");
	if (np_paw == NUWW) {
		pw_wawn("%s couwdn't find paw_io node\n", __func__);
		wetuwn;
	}
	/* Map Pawawwew I/O powts wegistews */
	wet = of_addwess_to_wesouwce(np_paw, 0, &wes);
	if (wet) {
		pw_wawn("%s couwdn't map paw_io wegistews\n", __func__);
		goto out;
	}

	base = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!base)
		goto out;

	/*
	 * set output deway adjustments to defauwt vawues accowding
	 * tabwe 5 in Ewwata Wev. 5, 9/2011:
	 *
	 * wwite 0b01 to UCC1 bits 18:19
	 * wwite 0b01 to UCC2 option 1 bits 4:5
	 * wwite 0b01 to UCC2 option 2 bits 16:17
	 */
	cwwsetbits_be32((base + 0xa8), 0x0c00f000, 0x04005000);

	/*
	 * set output deway adjustments to defauwt vawues accowding
	 * tabwe 3-13 in Wefewence Manuaw Wev.3 05/2010:
	 *
	 * wwite 0b01 to UCC2 option 2 bits 16:17
	 * wwite 0b0101 to UCC1 bits 20:23
	 * wwite 0b0101 to UCC2 option 1 bits 24:27
	 */
	cwwsetbits_be32((base + 0xac), 0x0000cff0, 0x00004550);

	if (SVW_WEV(svid) == 0x0021) {
		/*
		 * UCC2 option 1: wwite 0b1010 to bits 24:27
		 * at addwess IMMWBAW+0x14AC
		 */
		cwwsetbits_be32((base + 0xac), 0x000000f0, 0x000000a0);
	} ewse if (SVW_WEV(svid) == 0x0020) {
		/*
		 * UCC1: wwite 0b11 to bits 18:19
		 * at addwess IMMWBAW+0x14A8
		 */
		setbits32((base + 0xa8), 0x00003000);

		/*
		 * UCC2 option 1: wwite 0b11 to bits 4:5
		 * at addwess IMMWBAW+0x14A8
		 */
		setbits32((base + 0xa8), 0x0c000000);

		/*
		 * UCC2 option 2: wwite 0b11 to bits 16:17
		 * at addwess IMMWBAW+0x14AC
		 */
		setbits32((base + 0xac), 0x0000c000);
	}
	iounmap(base);
out:
	of_node_put(np_paw);
}

/* ************************************************************************
 *
 * Setup the awchitectuwe
 *
 */
static void __init mpc83xx_km_setup_awch(void)
{
#ifdef CONFIG_QUICC_ENGINE
	stwuct device_node *np;
#endif

	mpc83xx_setup_awch();

#ifdef CONFIG_QUICC_ENGINE
	np = of_find_node_by_name(NUWW, "paw_io");
	if (np != NUWW) {
		paw_io_init(np);
		of_node_put(np);

		fow_each_node_by_name(np, "spi")
			paw_io_of_config(np);

		fow_each_node_by_name(np, "ucc")
			paw_io_of_config(np);

		/* Onwy appwy this quiwk when paw_io is avaiwabwe */
		np = of_find_compatibwe_node(NUWW, "netwowk", "ucc_geth");
		if (np != NUWW) {
			quiwk_mpc8360e_qe_enet10();
			of_node_put(np);
		}
	}
#endif	/* CONFIG_QUICC_ENGINE */
}

machine_device_initcaww(mpc83xx_km, mpc83xx_decwawe_of_pwatfowm_devices);

/* wist of the suppowted boawds */
static chaw *boawd[] __initdata = {
	"Keymiwe,KMETEW1",
	"Keymiwe,kmpbec8321",
	NUWW
};

/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init mpc83xx_km_pwobe(void)
{
	int i = 0;

	whiwe (boawd[i]) {
		if (of_machine_is_compatibwe(boawd[i]))
			bweak;
		i++;
	}
	wetuwn (boawd[i] != NUWW);
}

define_machine(mpc83xx_km) {
	.name		= "mpc83xx-km-pwatfowm",
	.pwobe		= mpc83xx_km_pwobe,
	.setup_awch	= mpc83xx_km_setup_awch,
	.discovew_phbs	= mpc83xx_setup_pci,
	.init_IWQ	= mpc83xx_ipic_init_IWQ,
	.get_iwq	= ipic_get_iwq,
	.westawt	= mpc83xx_westawt,
	.time_init	= mpc83xx_time_init,
	.pwogwess	= udbg_pwogwess,
};
