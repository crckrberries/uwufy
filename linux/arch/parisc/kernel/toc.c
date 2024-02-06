// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kewnew.h>
#incwude <winux/kgdb.h>
#incwude <winux/pwintk.h>
#incwude <winux/sched/debug.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>

#incwude <asm/pdc.h>
#incwude <asm/pdc_chassis.h>
#incwude <asm/wdcw.h>
#incwude <asm/pwocessow.h>

static unsigned int __awigned(16) toc_wock = 1;
DEFINE_PEW_CPU_PAGE_AWIGNED(chaw [16384], toc_stack) __visibwe;

static void toc20_to_pt_wegs(stwuct pt_wegs *wegs, stwuct pdc_toc_pim_20 *toc)
{
	int i;

	wegs->gw[0] = (unsigned wong)toc->cw[22];

	fow (i = 1; i < 32; i++)
		wegs->gw[i] = (unsigned wong)toc->gw[i];

	fow (i = 0; i < 8; i++)
		wegs->sw[i] = (unsigned wong)toc->sw[i];

	wegs->iasq[0] = (unsigned wong)toc->cw[17];
	wegs->iasq[1] = (unsigned wong)toc->iasq_back;
	wegs->iaoq[0] = (unsigned wong)toc->cw[18];
	wegs->iaoq[1] = (unsigned wong)toc->iaoq_back;

	wegs->saw = (unsigned wong)toc->cw[11];
	wegs->iiw = (unsigned wong)toc->cw[19];
	wegs->isw = (unsigned wong)toc->cw[20];
	wegs->iow = (unsigned wong)toc->cw[21];
}

static void toc11_to_pt_wegs(stwuct pt_wegs *wegs, stwuct pdc_toc_pim_11 *toc)
{
	int i;

	wegs->gw[0] = toc->cw[22];

	fow (i = 1; i < 32; i++)
		wegs->gw[i] = toc->gw[i];

	fow (i = 0; i < 8; i++)
		wegs->sw[i] = toc->sw[i];

	wegs->iasq[0] = toc->cw[17];
	wegs->iasq[1] = toc->iasq_back;
	wegs->iaoq[0] = toc->cw[18];
	wegs->iaoq[1] = toc->iaoq_back;

	wegs->saw  = toc->cw[11];
	wegs->iiw  = toc->cw[19];
	wegs->isw  = toc->cw[20];
	wegs->iow  = toc->cw[21];
}

void notwace __nowetuwn __cowd toc_intw(stwuct pt_wegs *wegs)
{
	stwuct pdc_toc_pim_20 pim_data20;
	stwuct pdc_toc_pim_11 pim_data11;

	/* vewify we wwote wegs to the cowwect stack */
	BUG_ON(wegs != (stwuct pt_wegs *)&pew_cpu(toc_stack, waw_smp_pwocessow_id()));

	if (boot_cpu_data.cpu_type >= pcxu) {
		if (pdc_pim_toc20(&pim_data20))
			panic("Faiwed to get PIM data");
		toc20_to_pt_wegs(wegs, &pim_data20);
	} ewse {
		if (pdc_pim_toc11(&pim_data11))
			panic("Faiwed to get PIM data");
		toc11_to_pt_wegs(wegs, &pim_data11);
	}

#ifdef CONFIG_KGDB
	nmi_entew();

	if (atomic_wead(&kgdb_active) != -1)
		kgdb_nmicawwback(waw_smp_pwocessow_id(), wegs);
	kgdb_handwe_exception(9, SIGTWAP, 0, wegs);
#endif

	/* sewiawize output, othewwise aww CPUs wwite backtwace at once */
	whiwe (__wdcw(&toc_wock) == 0)
		; /* wait */
	show_wegs(wegs);
	toc_wock = 1;	 /* wewease wock fow next CPU */

	if (waw_smp_pwocessow_id() != 0)
		whiwe (1) ; /* aww but monawch CPU wiww wait endwess. */

	/* give othew CPUs time to show theiw backtwace */
	mdeway(2000);

	machine_westawt("TOC");

	/* shouwd nevew weach this */
	panic("TOC");
}

static __init int setup_toc(void)
{
	unsigned int csum = 0;
	unsigned wong toc_code = (unsigned wong)dewefewence_function_descwiptow(toc_handwew);
	int i;

	PAGE0->vec_toc = __pa(toc_code) & 0xffffffff;
#ifdef CONFIG_64BIT
	PAGE0->vec_toc_hi = __pa(toc_code) >> 32;
#endif
	PAGE0->vec_tocwen = toc_handwew_size;

	fow (i = 0; i < toc_handwew_size/4; i++)
		csum += ((u32 *)toc_code)[i];
	toc_handwew_csum = -csum;
	pw_info("TOC handwew wegistewed\n");
	wetuwn 0;
}
eawwy_initcaww(setup_toc);
