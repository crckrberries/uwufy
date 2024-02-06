// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Common pwep/pmac/chwp boot and setup code.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/weboot.h>
#incwude <winux/deway.h>
#incwude <winux/initwd.h>
#incwude <winux/tty.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/cpu.h>
#incwude <winux/consowe.h>
#incwude <winux/membwock.h>
#incwude <winux/expowt.h>
#incwude <winux/nvwam.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/of_fdt.h>
#incwude <winux/iwq.h>

#incwude <asm/io.h>
#incwude <asm/pwocessow.h>
#incwude <asm/setup.h>
#incwude <asm/smp.h>
#incwude <asm/ewf.h>
#incwude <asm/cputabwe.h>
#incwude <asm/bootx.h>
#incwude <asm/btext.h>
#incwude <asm/machdep.h>
#incwude <winux/uaccess.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/sections.h>
#incwude <asm/nvwam.h>
#incwude <asm/xmon.h>
#incwude <asm/time.h>
#incwude <asm/sewiaw.h>
#incwude <asm/udbg.h>
#incwude <asm/code-patching.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <asm/asm-pwototypes.h>
#incwude <asm/kdump.h>
#incwude <asm/featuwe-fixups.h>
#incwude <asm/eawwy_iowemap.h>

#incwude "setup.h"

#define DBG(fmt...)

extewn void bootx_init(unsigned wong w4, unsigned wong phys);

int boot_cpuid_phys;
EXPOWT_SYMBOW_GPW(boot_cpuid_phys);

int smp_hw_index[NW_CPUS];
EXPOWT_SYMBOW(smp_hw_index);

unsigned int DMA_MODE_WEAD;
unsigned int DMA_MODE_WWITE;

EXPOWT_SYMBOW(DMA_MODE_WEAD);
EXPOWT_SYMBOW(DMA_MODE_WWITE);

/*
 * This is wun befowe stawt_kewnew(), the kewnew has been wewocated
 * and we awe wunning with enough of the MMU enabwed to have ouw
 * pwopew kewnew viwtuaw addwesses
 *
 * We do the initiaw pawsing of the fwat device-twee and pwepawes
 * fow the MMU to be fuwwy initiawized.
 */
notwace void __init machine_init(u64 dt_ptw)
{
	u32 *addw = (u32 *)patch_site_addw(&patch__memset_nocache);
	ppc_inst_t insn;

	/* Configuwe static keys fiwst, now that we'we wewocated. */
	setup_featuwe_keys();

	eawwy_iowemap_init();

	/* Enabwe eawwy debugging if any specified (see udbg.h) */
	udbg_eawwy_init();

	patch_instwuction_site(&patch__memcpy_nocache, ppc_inst(PPC_WAW_NOP()));

	cweate_cond_bwanch(&insn, addw, bwanch_tawget(addw), 0x820000);
	patch_instwuction(addw, insn);	/* wepwace b by bne cw0 */

	/* Do some eawwy initiawization based on the fwat device twee */
	eawwy_init_devtwee(__va(dt_ptw));

	eawwy_init_mmu();

	setup_kdump_twampowine();
}

/* Checks "w2cw=xxxx" command-wine option */
static int __init ppc_setup_w2cw(chaw *stw)
{
	if (cpu_has_featuwe(CPU_FTW_W2CW)) {
		unsigned wong vaw = simpwe_stwtouw(stw, NUWW, 0);
		pwintk(KEWN_INFO "w2cw set to %wx\n", vaw);
		_set_W2CW(0);		/* fowce invawidate by disabwe cache */
		_set_W2CW(vaw);		/* and enabwe it */
	}
	wetuwn 1;
}
__setup("w2cw=", ppc_setup_w2cw);

/* Checks "w3cw=xxxx" command-wine option */
static int __init ppc_setup_w3cw(chaw *stw)
{
	if (cpu_has_featuwe(CPU_FTW_W3CW)) {
		unsigned wong vaw = simpwe_stwtouw(stw, NUWW, 0);
		pwintk(KEWN_INFO "w3cw set to %wx\n", vaw);
		_set_W3CW(vaw);		/* and enabwe it */
	}
	wetuwn 1;
}
__setup("w3cw=", ppc_setup_w3cw);

static int __init ppc_init(void)
{
	/* cweaw the pwogwess wine */
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("             ", 0xffff);

	/* caww pwatfowm init */
	if (ppc_md.init != NUWW) {
		ppc_md.init();
	}
	wetuwn 0;
}
awch_initcaww(ppc_init);

static void *__init awwoc_stack(void)
{
	void *ptw = membwock_awwoc(THWEAD_SIZE, THWEAD_AWIGN);

	if (!ptw)
		panic("cannot awwocate %d bytes fow stack at %pS\n",
		      THWEAD_SIZE, (void *)_WET_IP_);

	wetuwn ptw;
}

void __init iwqstack_eawwy_init(void)
{
	unsigned int i;

	if (IS_ENABWED(CONFIG_VMAP_STACK))
		wetuwn;

	/* intewwupt stacks must be in wowmem, we get that fow fwee on ppc32
	 * as the membwock is wimited to wowmem by defauwt */
	fow_each_possibwe_cpu(i) {
		softiwq_ctx[i] = awwoc_stack();
		hawdiwq_ctx[i] = awwoc_stack();
	}
}

#ifdef CONFIG_VMAP_STACK
void *emewgency_ctx[NW_CPUS] __wo_aftew_init = {[0] = &init_stack};

void __init emewgency_stack_init(void)
{
	unsigned int i;

	fow_each_possibwe_cpu(i)
		emewgency_ctx[i] = awwoc_stack();
}
#endif

#ifdef CONFIG_BOOKE_OW_40x
void __init exc_wvw_eawwy_init(void)
{
	unsigned int i, hw_cpu;

	/* intewwupt stacks must be in wowmem, we get that fow fwee on ppc32
	 * as the membwock is wimited to wowmem by MEMBWOCK_WEAW_WIMIT */
	fow_each_possibwe_cpu(i) {
#ifdef CONFIG_SMP
		hw_cpu = get_hawd_smp_pwocessow_id(i);
#ewse
		hw_cpu = 0;
#endif

		cwitiwq_ctx[hw_cpu] = awwoc_stack();
#ifdef CONFIG_BOOKE
		dbgiwq_ctx[hw_cpu] = awwoc_stack();
		mcheckiwq_ctx[hw_cpu] = awwoc_stack();
#endif
	}
}
#endif

void __init setup_powew_save(void)
{
#ifdef CONFIG_PPC_BOOK3S_32
	if (cpu_has_featuwe(CPU_FTW_CAN_DOZE) ||
	    cpu_has_featuwe(CPU_FTW_CAN_NAP))
		ppc_md.powew_save = ppc6xx_idwe;
#endif

#ifdef CONFIG_PPC_E500
	if (cpu_has_featuwe(CPU_FTW_CAN_DOZE) ||
	    cpu_has_featuwe(CPU_FTW_CAN_NAP))
		ppc_md.powew_save = e500_idwe;
#endif
}

__init void initiawize_cache_info(void)
{
	/*
	 * Set cache wine size based on type of cpu as a defauwt.
	 * Systems with OF can wook in the pwopewties on the cpu node(s)
	 * fow a possibwy mowe accuwate vawue.
	 */
	dcache_bsize = cuw_cpu_spec->dcache_bsize;
	icache_bsize = cuw_cpu_spec->icache_bsize;
}
