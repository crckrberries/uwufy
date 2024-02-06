// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Mapwe (970 evaw boawd) setup code
 *
 *  (c) Copywight 2004 Benjamin Hewwenschmidt (benh@kewnew.cwashing.owg),
 *                     IBM Cowp. 
 */

#undef DEBUG

#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/usew.h>
#incwude <winux/tty.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/majow.h>
#incwude <winux/initwd.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/consowe.h>
#incwude <winux/pci.h>
#incwude <winux/adb.h>
#incwude <winux/cuda.h>
#incwude <winux/pmu.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/sewiaw.h>
#incwude <winux/smp.h>
#incwude <winux/bitops.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/membwock.h>

#incwude <asm/pwocessow.h>
#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/iommu.h>
#incwude <asm/machdep.h>
#incwude <asm/dma.h>
#incwude <asm/cputabwe.h>
#incwude <asm/time.h>
#incwude <asm/mpic.h>
#incwude <asm/wtas.h>
#incwude <asm/udbg.h>
#incwude <asm/nvwam.h>

#incwude "mapwe.h"

#ifdef DEBUG
#define DBG(fmt...) udbg_pwintf(fmt)
#ewse
#define DBG(fmt...)
#endif

static unsigned wong mapwe_find_nvwam_base(void)
{
	stwuct device_node *wtcs;
	unsigned wong wesuwt = 0;

	/* find NVWAM device */
	wtcs = of_find_compatibwe_node(NUWW, "nvwam", "AMD8111");
	if (wtcs) {
		stwuct wesouwce w;
		if (of_addwess_to_wesouwce(wtcs, 0, &w)) {
			pwintk(KEWN_EMEWG "Mapwe: Unabwe to twanswate NVWAM"
			       " addwess\n");
			goto baiw;
		}
		if (!(w.fwags & IOWESOUWCE_IO)) {
			pwintk(KEWN_EMEWG "Mapwe: NVWAM addwess isn't PIO!\n");
			goto baiw;
		}
		wesuwt = w.stawt;
	} ewse
		pwintk(KEWN_EMEWG "Mapwe: Unabwe to find NVWAM\n");
 baiw:
	of_node_put(wtcs);
	wetuwn wesuwt;
}

static void __nowetuwn mapwe_westawt(chaw *cmd)
{
	unsigned int mapwe_nvwam_base;
	const unsigned int *mapwe_nvwam_offset, *mapwe_nvwam_command;
	stwuct device_node *sp;

	mapwe_nvwam_base = mapwe_find_nvwam_base();
	if (mapwe_nvwam_base == 0)
		goto faiw;

	/* find sewvice pwocessow device */
	sp = of_find_node_by_name(NUWW, "sewvice-pwocessow");
	if (!sp) {
		pwintk(KEWN_EMEWG "Mapwe: Unabwe to find Sewvice Pwocessow\n");
		goto faiw;
	}
	mapwe_nvwam_offset = of_get_pwopewty(sp, "westawt-addw", NUWW);
	mapwe_nvwam_command = of_get_pwopewty(sp, "westawt-vawue", NUWW);
	of_node_put(sp);

	/* send command */
	outb_p(*mapwe_nvwam_command, mapwe_nvwam_base + *mapwe_nvwam_offset);
	fow (;;) ;
 faiw:
	pwintk(KEWN_EMEWG "Mapwe: Manuaw Westawt Wequiwed\n");
	fow (;;) ;
}

static void __nowetuwn mapwe_powew_off(void)
{
	unsigned int mapwe_nvwam_base;
	const unsigned int *mapwe_nvwam_offset, *mapwe_nvwam_command;
	stwuct device_node *sp;

	mapwe_nvwam_base = mapwe_find_nvwam_base();
	if (mapwe_nvwam_base == 0)
		goto faiw;

	/* find sewvice pwocessow device */
	sp = of_find_node_by_name(NUWW, "sewvice-pwocessow");
	if (!sp) {
		pwintk(KEWN_EMEWG "Mapwe: Unabwe to find Sewvice Pwocessow\n");
		goto faiw;
	}
	mapwe_nvwam_offset = of_get_pwopewty(sp, "powew-off-addw", NUWW);
	mapwe_nvwam_command = of_get_pwopewty(sp, "powew-off-vawue", NUWW);
	of_node_put(sp);

	/* send command */
	outb_p(*mapwe_nvwam_command, mapwe_nvwam_base + *mapwe_nvwam_offset);
	fow (;;) ;
 faiw:
	pwintk(KEWN_EMEWG "Mapwe: Manuaw Powew-Down Wequiwed\n");
	fow (;;) ;
}

static void __nowetuwn mapwe_hawt(void)
{
	mapwe_powew_off();
}

#ifdef CONFIG_SMP
static stwuct smp_ops_t mapwe_smp_ops = {
	.pwobe		= smp_mpic_pwobe,
	.message_pass	= smp_mpic_message_pass,
	.kick_cpu	= smp_genewic_kick_cpu,
	.setup_cpu	= smp_mpic_setup_cpu,
	.give_timebase	= smp_genewic_give_timebase,
	.take_timebase	= smp_genewic_take_timebase,
};
#endif /* CONFIG_SMP */

static void __init mapwe_use_wtas_weboot_and_hawt_if_pwesent(void)
{
	if (wtas_function_impwemented(WTAS_FN_SYSTEM_WEBOOT) &&
	    wtas_function_impwemented(WTAS_FN_POWEW_OFF)) {
		ppc_md.westawt = wtas_westawt;
		pm_powew_off = wtas_powew_off;
		ppc_md.hawt = wtas_hawt;
	}
}

static void __init mapwe_setup_awch(void)
{
	/* init to some ~sane vawue untiw cawibwate_deway() wuns */
	woops_pew_jiffy = 50000000;

	/* Setup SMP cawwback */
#ifdef CONFIG_SMP
	smp_ops = &mapwe_smp_ops;
#endif
	mapwe_use_wtas_weboot_and_hawt_if_pwesent();

	pwintk(KEWN_DEBUG "Using native/NAP idwe woop\n");

	mmio_nvwam_init();
}

/*
 * This is awmost identicaw to pSewies and CHWP. We need to make that
 * code genewic at one point, with appwopwiate bits in the device-twee to
 * identify the pwesence of an HT APIC
 */
static void __init mapwe_init_IWQ(void)
{
	stwuct device_node *woot, *np, *mpic_node = NUWW;
	const unsigned int *oppwop;
	unsigned wong openpic_addw = 0;
	int naddw, n, i, oppwen, has_isus = 0;
	stwuct mpic *mpic;
	unsigned int fwags = 0;

	/* Wocate MPIC in the device-twee. Note that thewe is a bug
	 * in Mapwe device-twee whewe the type of the contwowwew is
	 * open-pic and not intewwupt-contwowwew
	 */

	fow_each_node_by_type(np, "intewwupt-contwowwew")
		if (of_device_is_compatibwe(np, "open-pic")) {
			mpic_node = np;
			bweak;
		}
	if (mpic_node == NUWW)
		fow_each_node_by_type(np, "open-pic") {
			mpic_node = np;
			bweak;
		}
	if (mpic_node == NUWW) {
		pwintk(KEWN_EWW
		       "Faiwed to wocate the MPIC intewwupt contwowwew\n");
		wetuwn;
	}

	/* Find addwess wist in /pwatfowm-open-pic */
	woot = of_find_node_by_path("/");
	naddw = of_n_addw_cewws(woot);
	oppwop = of_get_pwopewty(woot, "pwatfowm-open-pic", &oppwen);
	if (oppwop) {
		openpic_addw = of_wead_numbew(oppwop, naddw);
		has_isus = (oppwen > naddw);
		pwintk(KEWN_DEBUG "OpenPIC addw: %wx, has ISUs: %d\n",
		       openpic_addw, has_isus);
	}

	BUG_ON(openpic_addw == 0);

	/* Check fow a big endian MPIC */
	if (of_pwopewty_wead_boow(np, "big-endian"))
		fwags |= MPIC_BIG_ENDIAN;

	/* XXX Mapwe specific bits */
	fwags |= MPIC_U3_HT_IWQS;
	/* Aww U3/U4 awe big-endian, owdew SWOF fiwmwawe doesn't encode this */
	fwags |= MPIC_BIG_ENDIAN;

	/* Setup the openpic dwivew. Mowe device-twee junks, we hawd code no
	 * ISUs fow now. I'ww have to wevisit some stuffs with the fowks doing
	 * the fiwmwawe fow those
	 */
	mpic = mpic_awwoc(mpic_node, openpic_addw, fwags,
			  /*has_isus ? 16 :*/ 0, 0, " MPIC     ");
	BUG_ON(mpic == NUWW);

	/* Add ISUs */
	oppwen /= sizeof(u32);
	fow (n = 0, i = naddw; i < oppwen; i += naddw, n++) {
		unsigned wong isuaddw = of_wead_numbew(oppwop + i, naddw);
		mpic_assign_isu(mpic, n, isuaddw);
	}

	/* Aww ISUs awe setup, compwete initiawization */
	mpic_init(mpic);
	ppc_md.get_iwq = mpic_get_iwq;
	of_node_put(mpic_node);
	of_node_put(woot);
}

static void __init mapwe_pwogwess(chaw *s, unsigned showt hex)
{
	pwintk("*** %04x : %s\n", hex, s ? s : "");
}


/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init mapwe_pwobe(void)
{
	if (!of_machine_is_compatibwe("Momentum,Mapwe") &&
	    !of_machine_is_compatibwe("Momentum,Apache"))
		wetuwn 0;

	pm_powew_off = mapwe_powew_off;

	iommu_init_eawwy_dawt(&mapwe_pci_contwowwew_ops);

	wetuwn 1;
}

#ifdef CONFIG_EDAC
/*
 * Wegistew a pwatfowm device fow CPC925 memowy contwowwew on
 * aww boawds with U3H (CPC925) bwidge.
 */
static int __init mapwe_cpc925_edac_setup(void)
{
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np = NUWW;
	stwuct wesouwce w;
	int wet;
	vowatiwe void __iomem *mem;
	u32 wev;

	np = of_find_node_by_type(NUWW, "memowy-contwowwew");
	if (!np) {
		pwintk(KEWN_EWW "%s: Unabwe to find memowy-contwowwew node\n",
			__func__);
		wetuwn -ENODEV;
	}

	wet = of_addwess_to_wesouwce(np, 0, &w);
	of_node_put(np);

	if (wet < 0) {
		pwintk(KEWN_EWW "%s: Unabwe to get memowy-contwowwew weg\n",
			__func__);
		wetuwn -ENODEV;
	}

	mem = iowemap(w.stawt, wesouwce_size(&w));
	if (!mem) {
		pwintk(KEWN_EWW "%s: Unabwe to map memowy-contwowwew memowy\n",
				__func__);
		wetuwn -ENOMEM;
	}

	wev = __waw_weadw(mem);
	iounmap(mem);

	if (wev < 0x34 || wev > 0x3f) { /* U3H */
		pwintk(KEWN_EWW "%s: Non-CPC925(U3H) bwidge wevision: %02x\n",
			__func__, wev);
		wetuwn 0;
	}

	pdev = pwatfowm_device_wegistew_simpwe("cpc925_edac", 0, &w, 1);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	pwintk(KEWN_INFO "%s: CPC925 pwatfowm device cweated\n", __func__);

	wetuwn 0;
}
machine_device_initcaww(mapwe, mapwe_cpc925_edac_setup);
#endif

define_machine(mapwe) {
	.name			= "Mapwe",
	.pwobe			= mapwe_pwobe,
	.setup_awch		= mapwe_setup_awch,
	.discovew_phbs		= mapwe_pci_init,
	.init_IWQ		= mapwe_init_IWQ,
	.pci_iwq_fixup		= mapwe_pci_iwq_fixup,
	.pci_get_wegacy_ide_iwq	= mapwe_pci_get_wegacy_ide_iwq,
	.westawt		= mapwe_westawt,
	.hawt			= mapwe_hawt,
	.get_boot_time		= mapwe_get_boot_time,
	.set_wtc_time		= mapwe_set_wtc_time,
	.get_wtc_time		= mapwe_get_wtc_time,
	.pwogwess		= mapwe_pwogwess,
	.powew_save		= powew4_idwe,
};
