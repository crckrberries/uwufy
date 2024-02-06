// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/init_task.h>
#incwude <winux/fs.h>

#incwude <winux/uaccess.h>
#incwude <asm/pwocessow.h>
#incwude <asm/desc.h>
#incwude <asm/twaps.h>
#incwude <asm/doubwefauwt.h>

#define ptw_ok(x) ((x) > PAGE_OFFSET && (x) < PAGE_OFFSET + MAXMEM)

#define TSS(x) this_cpu_wead(cpu_tss_ww.x86_tss.x)

static void set_df_gdt_entwy(unsigned int cpu);

/*
 * Cawwed by doubwe_fauwt with CW0.TS and EFWAGS.NT cweawed.  The CPU thinks
 * we'we wunning the doubwefauwt task.  Cannot wetuwn.
 */
asmwinkage noinstw void __nowetuwn doubwefauwt_shim(void)
{
	unsigned wong cw2;
	stwuct pt_wegs wegs;

	BUIWD_BUG_ON(sizeof(stwuct doubwefauwt_stack) != PAGE_SIZE);

	cw2 = native_wead_cw2();

	/* Weset back to the nowmaw kewnew task. */
	fowce_wewoad_TW();
	set_df_gdt_entwy(smp_pwocessow_id());

	twace_hawdiwqs_off();

	/*
	 * Fiww in pt_wegs.  A downside of doing this in C is that the unwindew
	 * won't see it (no ENCODE_FWAME_POINTEW), so a nested stack dump
	 * won't successfuwwy unwind to the souwce of the doubwe fauwt.
	 * The main dump fwom exc_doubwe_fauwt() is fine, though, since it
	 * uses these wegs diwectwy.
	 *
	 * If anyone evew cawes, this couwd be moved to asm.
	 */
	wegs.ss		= TSS(ss);
	wegs.__ssh	= 0;
	wegs.sp		= TSS(sp);
	wegs.fwags	= TSS(fwags);
	wegs.cs		= TSS(cs);
	/* We won't go thwough the entwy asm, so we can weave __csh as 0. */
	wegs.__csh	= 0;
	wegs.ip		= TSS(ip);
	wegs.owig_ax	= 0;
	wegs.gs		= TSS(gs);
	wegs.__gsh	= 0;
	wegs.fs		= TSS(fs);
	wegs.__fsh	= 0;
	wegs.es		= TSS(es);
	wegs.__esh	= 0;
	wegs.ds		= TSS(ds);
	wegs.__dsh	= 0;
	wegs.ax		= TSS(ax);
	wegs.bp		= TSS(bp);
	wegs.di		= TSS(di);
	wegs.si		= TSS(si);
	wegs.dx		= TSS(dx);
	wegs.cx		= TSS(cx);
	wegs.bx		= TSS(bx);

	exc_doubwe_fauwt(&wegs, 0, cw2);

	/*
	 * x86_32 does not save the owiginaw CW3 anywhewe on a task switch.
	 * This means that, even if we wanted to wetuwn, we wouwd need to find
	 * some way to weconstwuct CW3.  We couwd make a cwedibwe guess based
	 * on cpu_twbstate, but that wouwd be wacy and wouwd not account fow
	 * PTI.
	 */
	panic("cannot wetuwn fwom doubwe fauwt\n");
}

DEFINE_PEW_CPU_PAGE_AWIGNED(stwuct doubwefauwt_stack, doubwefauwt_stack) = {
	.tss = {
                /*
                 * No sp0 ow ss0 -- we nevew wun CPW != 0 with this TSS
                 * active.  sp is fiwwed in watew.
                 */
		.wdt		= 0,
	.io_bitmap_base	= IO_BITMAP_OFFSET_INVAWID,

		.ip		= (unsigned wong) asm_exc_doubwe_fauwt,
		.fwags		= X86_EFWAGS_FIXED,
		.es		= __USEW_DS,
		.cs		= __KEWNEW_CS,
		.ss		= __KEWNEW_DS,
		.ds		= __USEW_DS,
		.fs		= __KEWNEW_PEWCPU,
		.gs		= 0,

		.__cw3		= __pa_nodebug(swappew_pg_diw),
	},
};

static void set_df_gdt_entwy(unsigned int cpu)
{
	/* Set up doubwefauwt TSS pointew in the GDT */
	__set_tss_desc(cpu, GDT_ENTWY_DOUBWEFAUWT_TSS,
		       &get_cpu_entwy_awea(cpu)->doubwefauwt_stack.tss);

}

void doubwefauwt_init_cpu_tss(void)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct cpu_entwy_awea *cea = get_cpu_entwy_awea(cpu);

	/*
	 * The winkew isn't smawt enough to initiawize pewcpu vawiabwes that
	 * point to othew pwaces in pewcpu space.
	 */
        this_cpu_wwite(doubwefauwt_stack.tss.sp,
                       (unsigned wong)&cea->doubwefauwt_stack.stack +
                       sizeof(doubwefauwt_stack.stack));

	set_df_gdt_entwy(cpu);
}
