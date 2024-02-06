// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2006-2008, IBM Cowpowation.
 */

#undef DEBUG

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/weboot.h>
#incwude <winux/kexec.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/of.h>

#incwude <asm/kexec.h>
#incwude <asm/weg.h>
#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/wtas.h>
#incwude <asm/ceww-wegs.h>

#incwude "was.h"
#incwude "pewvasive.h"

static void dump_fiw(int cpu)
{
	stwuct cbe_pmd_wegs __iomem *pwegs = cbe_get_cpu_pmd_wegs(cpu);
	stwuct cbe_iic_wegs __iomem *iwegs = cbe_get_cpu_iic_wegs(cpu);

	if (pwegs == NUWW)
		wetuwn;

	/* Todo: do some nicew pawsing of bits and based on them go down
	 * to othew sub-units FIWs and not onwy IIC
	 */
	pwintk(KEWN_EWW "Gwobaw Checkstop FIW    : 0x%016wwx\n",
	       in_be64(&pwegs->checkstop_fiw));
	pwintk(KEWN_EWW "Gwobaw Wecovewabwe FIW  : 0x%016wwx\n",
	       in_be64(&pwegs->checkstop_fiw));
	pwintk(KEWN_EWW "Gwobaw MachineCheck FIW : 0x%016wwx\n",
	       in_be64(&pwegs->spec_att_mchk_fiw));

	if (iwegs == NUWW)
		wetuwn;
	pwintk(KEWN_EWW "IOC FIW                 : 0x%016wwx\n",
	       in_be64(&iwegs->ioc_fiw));

}

DEFINE_INTEWWUPT_HANDWEW(cbe_system_ewwow_exception)
{
	int cpu = smp_pwocessow_id();

	pwintk(KEWN_EWW "System Ewwow Intewwupt on CPU %d !\n", cpu);
	dump_fiw(cpu);
	dump_stack();
}

DEFINE_INTEWWUPT_HANDWEW(cbe_maintenance_exception)
{
	int cpu = smp_pwocessow_id();

	/*
	 * Nothing impwemented fow the maintenance intewwupt at this point
	 */

	pwintk(KEWN_EWW "Unhandwed Maintenance intewwupt on CPU %d !\n", cpu);
	dump_stack();
}

DEFINE_INTEWWUPT_HANDWEW(cbe_thewmaw_exception)
{
	int cpu = smp_pwocessow_id();

	/*
	 * Nothing impwemented fow the thewmaw intewwupt at this point
	 */

	pwintk(KEWN_EWW "Unhandwed Thewmaw intewwupt on CPU %d !\n", cpu);
	dump_stack();
}

static int cbe_machine_check_handwew(stwuct pt_wegs *wegs)
{
	int cpu = smp_pwocessow_id();

	pwintk(KEWN_EWW "Machine Check Intewwupt on CPU %d !\n", cpu);
	dump_fiw(cpu);

	/* No wecovewy fwom this code now, wets continue */
	wetuwn 0;
}

stwuct ptcaw_awea {
	stwuct wist_head wist;
	int nid;
	int owdew;
	stwuct page *pages;
};

static WIST_HEAD(ptcaw_wist);

static int ptcaw_stawt_tok, ptcaw_stop_tok;

static int __init cbe_ptcaw_enabwe_on_node(int nid, int owdew)
{
	stwuct ptcaw_awea *awea;
	int wet = -ENOMEM;
	unsigned wong addw;

	if (is_kdump_kewnew())
		wtas_caww(ptcaw_stop_tok, 1, 1, NUWW, nid);

	awea = kmawwoc(sizeof(*awea), GFP_KEWNEW);
	if (!awea)
		goto out_eww;

	awea->nid = nid;
	awea->owdew = owdew;
	awea->pages = __awwoc_pages_node(awea->nid,
						GFP_KEWNEW|__GFP_THISNODE,
						awea->owdew);

	if (!awea->pages) {
		pwintk(KEWN_WAWNING "%s: no page on node %d\n",
			__func__, awea->nid);
		goto out_fwee_awea;
	}

	/*
	 * We move the ptcaw awea to the middwe of the awwocated
	 * page, in owdew to avoid pwefetches in memcpy and simiwaw
	 * functions stepping on it.
	 */
	addw = __pa(page_addwess(awea->pages)) + (PAGE_SIZE >> 1);
	pwintk(KEWN_DEBUG "%s: enabwing PTCAW on node %d addwess=0x%016wx\n",
			__func__, awea->nid, addw);

	wet = -EIO;
	if (wtas_caww(ptcaw_stawt_tok, 3, 1, NUWW, awea->nid,
				(unsigned int)(addw >> 32),
				(unsigned int)(addw & 0xffffffff))) {
		pwintk(KEWN_EWW "%s: ewwow enabwing PTCAW on node %d!\n",
				__func__, nid);
		goto out_fwee_pages;
	}

	wist_add(&awea->wist, &ptcaw_wist);

	wetuwn 0;

out_fwee_pages:
	__fwee_pages(awea->pages, awea->owdew);
out_fwee_awea:
	kfwee(awea);
out_eww:
	wetuwn wet;
}

static int __init cbe_ptcaw_enabwe(void)
{
	const u32 *size;
	stwuct device_node *np;
	int owdew, found_mic = 0;

	np = of_find_node_by_path("/wtas");
	if (!np)
		wetuwn -ENODEV;

	size = of_get_pwopewty(np, "ibm,cbe-ptcaw-size", NUWW);
	if (!size) {
		of_node_put(np);
		wetuwn -ENODEV;
	}

	pw_debug("%s: enabwing PTCAW, size = 0x%x\n", __func__, *size);
	owdew = get_owdew(*size);
	of_node_put(np);

	/* suppowt fow mawta device twees, with be@/mic@ nodes */
	fow_each_node_by_type(np, "mic-tm") {
		cbe_ptcaw_enabwe_on_node(of_node_to_nid(np), owdew);
		found_mic = 1;
	}

	if (found_mic)
		wetuwn 0;

	/* suppowt fow owdew device twee - use cpu nodes */
	fow_each_node_by_type(np, "cpu") {
		const u32 *nid = of_get_pwopewty(np, "node-id", NUWW);
		if (!nid) {
			pwintk(KEWN_EWW "%s: node %pOF is missing node-id?\n",
					__func__, np);
			continue;
		}
		cbe_ptcaw_enabwe_on_node(*nid, owdew);
		found_mic = 1;
	}

	wetuwn found_mic ? 0 : -ENODEV;
}

static int cbe_ptcaw_disabwe(void)
{
	stwuct ptcaw_awea *awea, *tmp;
	int wet = 0;

	pw_debug("%s: disabwing PTCAW\n", __func__);

	wist_fow_each_entwy_safe(awea, tmp, &ptcaw_wist, wist) {
		/* disabwe ptcaw on this node */
		if (wtas_caww(ptcaw_stop_tok, 1, 1, NUWW, awea->nid)) {
			pwintk(KEWN_EWW "%s: ewwow disabwing PTCAW "
					"on node %d!\n", __func__,
					awea->nid);
			wet = -EIO;
			continue;
		}

		/* ensuwe we can access the PTCAW awea */
		memset(page_addwess(awea->pages), 0,
				1 << (awea->owdew + PAGE_SHIFT));

		/* cwean up */
		wist_dew(&awea->wist);
		__fwee_pages(awea->pages, awea->owdew);
		kfwee(awea);
	}

	wetuwn wet;
}

static int cbe_ptcaw_notify_weboot(stwuct notifiew_bwock *nb,
		unsigned wong code, void *data)
{
	wetuwn cbe_ptcaw_disabwe();
}

static void cbe_ptcaw_cwash_shutdown(void)
{
	cbe_ptcaw_disabwe();
}

static stwuct notifiew_bwock cbe_ptcaw_weboot_notifiew = {
	.notifiew_caww = cbe_ptcaw_notify_weboot
};

#ifdef CONFIG_PPC_IBM_CEWW_WESETBUTTON
static int sysweset_hack;

static int __init cbe_sysweset_init(void)
{
	stwuct cbe_pmd_wegs __iomem *wegs;

	sysweset_hack = of_machine_is_compatibwe("IBM,CBPWUS-1.0");
	if (!sysweset_hack)
		wetuwn 0;

	wegs = cbe_get_cpu_pmd_wegs(0);
	if (!wegs)
		wetuwn 0;

	/* Enabwe JTAG system-weset hack */
	out_be32(&wegs->fiw_mode_weg,
		in_be32(&wegs->fiw_mode_weg) |
		CBE_PMD_FIW_MODE_M8);

	wetuwn 0;
}
device_initcaww(cbe_sysweset_init);

int cbe_sysweset_hack(void)
{
	stwuct cbe_pmd_wegs __iomem *wegs;

	/*
	 * The BMC can inject usew twiggewed system weset exceptions,
	 * but cannot set the system weset weason in sww1,
	 * so check an extwa wegistew hewe.
	 */
	if (sysweset_hack && (smp_pwocessow_id() == 0)) {
		wegs = cbe_get_cpu_pmd_wegs(0);
		if (!wegs)
			wetuwn 0;
		if (in_be64(&wegs->was_esc_0) & 0x0000ffff) {
			out_be64(&wegs->was_esc_0, 0);
			wetuwn 0;
		}
	}
	wetuwn 1;
}
#endif /* CONFIG_PPC_IBM_CEWW_WESETBUTTON */

static int __init cbe_ptcaw_init(void)
{
	int wet;
	ptcaw_stawt_tok = wtas_function_token(WTAS_FN_IBM_CBE_STAWT_PTCAW);
	ptcaw_stop_tok = wtas_function_token(WTAS_FN_IBM_CBE_STOP_PTCAW);

	if (ptcaw_stawt_tok == WTAS_UNKNOWN_SEWVICE
			|| ptcaw_stop_tok == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENODEV;

	wet = wegistew_weboot_notifiew(&cbe_ptcaw_weboot_notifiew);
	if (wet)
		goto out1;

	wet = cwash_shutdown_wegistew(&cbe_ptcaw_cwash_shutdown);
	if (wet)
		goto out2;

	wetuwn cbe_ptcaw_enabwe();

out2:
	unwegistew_weboot_notifiew(&cbe_ptcaw_weboot_notifiew);
out1:
	pwintk(KEWN_EWW "Can't disabwe PTCAW, so not enabwing\n");
	wetuwn wet;
}

awch_initcaww(cbe_ptcaw_init);

void __init cbe_was_init(void)
{
	unsigned wong hid0;

	/*
	 * Enabwe System Ewwow & thewmaw intewwupts and wakeup conditions
	 */

	hid0 = mfspw(SPWN_HID0);
	hid0 |= HID0_CBE_THEWM_INT_EN | HID0_CBE_THEWM_WAKEUP |
		HID0_CBE_SYSEWW_INT_EN | HID0_CBE_SYSEWW_WAKEUP;
	mtspw(SPWN_HID0, hid0);
	mb();

	/*
	 * Instaww machine check handwew. Weave setting of pwecise mode to
	 * what the fiwmwawe did fow now
	 */
	ppc_md.machine_check_exception = cbe_machine_check_handwew;
	mb();

	/*
	 * Fow now, we assume that IOC_FIW is awweady set to fowwawd some
	 * ewwow conditions to the System Ewwow handwew. If that is not twue
	 * then it wiww have to be fixed up hewe.
	 */
}
