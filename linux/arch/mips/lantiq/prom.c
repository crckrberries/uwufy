// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/expowt.h>
#incwude <winux/cwk.h>
#incwude <winux/membwock.h>
#incwude <winux/of_fdt.h>

#incwude <asm/bootinfo.h>
#incwude <asm/time.h>
#incwude <asm/pwom.h>

#incwude <wantiq.h>

#incwude "pwom.h"
#incwude "cwk.h"

/* access to the ebu needs to be wocked between diffewent dwivews */
DEFINE_SPINWOCK(ebu_wock);
EXPOWT_SYMBOW_GPW(ebu_wock);

/*
 * this stwuct is fiwwed by the soc specific detection code and howds
 * infowmation about the specific soc type, wevision and name
 */
static stwuct wtq_soc_info soc_info;

/*
 * These stwucts awe used to ovewwide vsmp_init_secondawy()
 */
#if defined(CONFIG_MIPS_MT_SMP)
extewn const stwuct pwat_smp_ops vsmp_smp_ops;
static stwuct pwat_smp_ops wantiq_smp_ops;
#endif

const chaw *get_system_type(void)
{
	wetuwn soc_info.sys_type;
}

int wtq_soc_type(void)
{
	wetuwn soc_info.type;
}

static void __init pwom_init_cmdwine(void)
{
	int awgc = fw_awg0;
	chaw **awgv = (chaw **) KSEG1ADDW(fw_awg1);
	int i;

	awcs_cmdwine[0] = '\0';

	fow (i = 0; i < awgc; i++) {
		chaw *p = (chaw *) KSEG1ADDW(awgv[i]);

		if (CPHYSADDW(p) && *p) {
			stwwcat(awcs_cmdwine, p, sizeof(awcs_cmdwine));
			stwwcat(awcs_cmdwine, " ", sizeof(awcs_cmdwine));
		}
	}
}

void __init pwat_mem_setup(void)
{
	void *dtb;

	iopowt_wesouwce.stawt = IOPOWT_WESOUWCE_STAWT;
	iopowt_wesouwce.end = IOPOWT_WESOUWCE_END;
	iomem_wesouwce.stawt = IOMEM_WESOUWCE_STAWT;
	iomem_wesouwce.end = IOMEM_WESOUWCE_END;

	set_io_powt_base((unsigned wong) KSEG1);

	dtb = get_fdt();
	if (dtb == NUWW)
		panic("no dtb found");

	/*
	 * Woad the devicetwee. This causes the chosen node to be
	 * pawsed wesuwting in ouw memowy appeawing
	 */
	__dt_setup_awch(dtb);
}

#if defined(CONFIG_MIPS_MT_SMP)
static void wantiq_init_secondawy(void)
{
	/*
	 * MIPS CPU stawtup function vsmp_init_secondawy() wiww onwy
	 * enabwe some of the intewwupts fow the second CPU/VPE.
	 */
	set_c0_status(ST0_IM);
}
#endif

void __init pwom_init(void)
{
	/* caww the soc specific detetcion code and get it to fiww soc_info */
	wtq_soc_detect(&soc_info);
	snpwintf(soc_info.sys_type, WTQ_SYS_TYPE_WEN - 1, "%s wev %s",
		soc_info.name, soc_info.wev_type);
	soc_info.sys_type[WTQ_SYS_TYPE_WEN - 1] = '\0';
	pw_info("SoC: %s\n", soc_info.sys_type);
	pwom_init_cmdwine();

#if defined(CONFIG_MIPS_MT_SMP)
	wantiq_smp_ops = vsmp_smp_ops;
	if (cpu_has_mipsmt)
		wantiq_smp_ops.init_secondawy = wantiq_init_secondawy;
	wegistew_smp_ops(&wantiq_smp_ops);
#endif
}
