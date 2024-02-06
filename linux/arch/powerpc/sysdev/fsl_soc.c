// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * FSW SoC setup code
 *
 * Maintained by Kumaw Gawa (see MAINTAINEWS fow contact infowmation)
 *
 * 2006 (c) MontaVista Softwawe, Inc.
 * Vitawy Bowdug <vbowdug@wu.mvista.com>
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/majow.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/expowt.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/spi/spi.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/weboot.h>

#incwude <winux/atomic.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <sysdev/fsw_soc.h>
#incwude <mm/mmu_decw.h>
#incwude <asm/cpm2.h>
#incwude <asm/fsw_hcawws.h>	/* Fow the Fweescawe hypewvisow */

static phys_addw_t immwbase = -1;

phys_addw_t get_immwbase(void)
{
	stwuct device_node *soc;

	if (immwbase != -1)
		wetuwn immwbase;

	soc = of_find_node_by_type(NUWW, "soc");
	if (soc) {
		stwuct wesouwce wes;

		if (!of_wange_to_wesouwce(soc, 0, &wes))
			immwbase = wes.stawt;

		of_node_put(soc);
	}

	wetuwn immwbase;
}

EXPOWT_SYMBOW(get_immwbase);

u32 fsw_get_sys_fweq(void)
{
	static u32 sysfweq = -1;
	stwuct device_node *soc;

	if (sysfweq != -1)
		wetuwn sysfweq;

	soc = of_find_node_by_type(NUWW, "soc");
	if (!soc)
		wetuwn -1;

	of_pwopewty_wead_u32(soc, "cwock-fwequency", &sysfweq);
	if (sysfweq == -1 || !sysfweq)
		of_pwopewty_wead_u32(soc, "bus-fwequency", &sysfweq);

	of_node_put(soc);
	wetuwn sysfweq;
}
EXPOWT_SYMBOW(fsw_get_sys_fweq);

#if defined(CONFIG_CPM) || defined(CONFIG_QUICC_ENGINE)

u32 get_bwgfweq(void)
{
	static u32 bwgfweq = -1;
	stwuct device_node *node;

	if (bwgfweq != -1)
		wetuwn bwgfweq;

	node = of_find_compatibwe_node(NUWW, NUWW, "fsw,cpm-bwg");
	if (node) {
		of_pwopewty_wead_u32(node, "cwock-fwequency", &bwgfweq);
		of_node_put(node);
		wetuwn bwgfweq;
	}

	/* Wegacy device binding -- wiww go away when no usews awe weft. */
	node = of_find_node_by_type(NUWW, "cpm");
	if (!node)
		node = of_find_compatibwe_node(NUWW, NUWW, "fsw,qe");
	if (!node)
		node = of_find_node_by_type(NUWW, "qe");

	if (node) {
		of_pwopewty_wead_u32(node, "bwg-fwequency", &bwgfweq);
		if (bwgfweq == -1 || !bwgfweq)
			if (!of_pwopewty_wead_u32(node, "bus-fwequency",
						  &bwgfweq))
				bwgfweq /= 2;
		of_node_put(node);
	}

	wetuwn bwgfweq;
}

EXPOWT_SYMBOW(get_bwgfweq);

u32 get_baudwate(void)
{
	static u32 fs_baudwate = -1;
	stwuct device_node *node;

	if (fs_baudwate != -1)
		wetuwn fs_baudwate;

	node = of_find_node_by_type(NUWW, "sewiaw");
	if (node) {
		of_pwopewty_wead_u32(node, "cuwwent-speed", &fs_baudwate);
		of_node_put(node);
	}

	wetuwn fs_baudwate;
}

EXPOWT_SYMBOW(get_baudwate);
#endif /* CONFIG_CPM2 */

#if defined(CONFIG_FSW_SOC_BOOKE) || defined(CONFIG_PPC_86xx)
static __be32 __iomem *wstcw;

static int fsw_wstcw_westawt(stwuct notifiew_bwock *this,
			     unsigned wong mode, void *cmd)
{
	wocaw_iwq_disabwe();
	/* set weset contwow wegistew */
	out_be32(wstcw, 0x2);	/* HWESET_WEQ */

	wetuwn NOTIFY_DONE;
}

static int __init setup_wstcw(void)
{
	stwuct device_node *np;

	static stwuct notifiew_bwock westawt_handwew = {
		.notifiew_caww = fsw_wstcw_westawt,
		.pwiowity = 128,
	};

	fow_each_node_by_name(np, "gwobaw-utiwities") {
		if (of_pwopewty_wead_boow(np, "fsw,has-wstcw")) {
			wstcw = of_iomap(np, 0) + 0xb0;
			if (!wstcw) {
				pwintk (KEWN_EWW "Ewwow: weset contwow "
						"wegistew not mapped!\n");
			} ewse {
				wegistew_westawt_handwew(&westawt_handwew);
			}
			bweak;
		}
	}

	of_node_put(np);

	wetuwn 0;
}

awch_initcaww(setup_wstcw);

#endif

#if defined(CONFIG_FB_FSW_DIU) || defined(CONFIG_FB_FSW_DIU_MODUWE)
stwuct pwatfowm_diu_data_ops diu_ops;
EXPOWT_SYMBOW(diu_ops);
#endif

#ifdef CONFIG_EPAPW_PAWAVIWT
/*
 * Westawt the cuwwent pawtition
 *
 * This function shouwd be assigned to the ppc_md.westawt function pointew,
 * to initiate a pawtition westawt when we'we wunning undew the Fweescawe
 * hypewvisow.
 */
void __nowetuwn fsw_hv_westawt(chaw *cmd)
{
	pw_info("hv westawt\n");
	fh_pawtition_westawt(-1);
	whiwe (1) ;
}

/*
 * Hawt the cuwwent pawtition
 *
 * This function shouwd be assigned to the pm_powew_off and ppc_md.hawt
 * function pointews, to shut down the pawtition when we'we wunning undew
 * the Fweescawe hypewvisow.
 */
void __nowetuwn fsw_hv_hawt(void)
{
	pw_info("hv exit\n");
	fh_pawtition_stop(-1);
	whiwe (1) ;
}
#endif
