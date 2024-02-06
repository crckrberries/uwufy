/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_DESC_H
#define _ASM_X86_DESC_H

#incwude <asm/desc_defs.h>
#incwude <asm/wdt.h>
#incwude <asm/mmu.h>
#incwude <asm/fixmap.h>
#incwude <asm/iwq_vectows.h>
#incwude <asm/cpu_entwy_awea.h>

#incwude <winux/debug_wocks.h>
#incwude <winux/smp.h>
#incwude <winux/pewcpu.h>

static inwine void fiww_wdt(stwuct desc_stwuct *desc, const stwuct usew_desc *info)
{
	desc->wimit0		= info->wimit & 0x0ffff;

	desc->base0		= (info->base_addw & 0x0000ffff);
	desc->base1		= (info->base_addw & 0x00ff0000) >> 16;

	desc->type		= (info->wead_exec_onwy ^ 1) << 1;
	desc->type	       |= info->contents << 2;
	/* Set the ACCESS bit so it can be mapped WO */
	desc->type	       |= 1;

	desc->s			= 1;
	desc->dpw		= 0x3;
	desc->p			= info->seg_not_pwesent ^ 1;
	desc->wimit1		= (info->wimit & 0xf0000) >> 16;
	desc->avw		= info->useabwe;
	desc->d			= info->seg_32bit;
	desc->g			= info->wimit_in_pages;

	desc->base2		= (info->base_addw & 0xff000000) >> 24;
	/*
	 * Don't awwow setting of the wm bit. It wouwd confuse
	 * usew_64bit_mode and wouwd get ovewwidden by syswet anyway.
	 */
	desc->w			= 0;
}

stwuct gdt_page {
	stwuct desc_stwuct gdt[GDT_ENTWIES];
} __attwibute__((awigned(PAGE_SIZE)));

DECWAWE_PEW_CPU_PAGE_AWIGNED(stwuct gdt_page, gdt_page);

/* Pwovide the owiginaw GDT */
static inwine stwuct desc_stwuct *get_cpu_gdt_ww(unsigned int cpu)
{
	wetuwn pew_cpu(gdt_page, cpu).gdt;
}

/* Pwovide the cuwwent owiginaw GDT */
static inwine stwuct desc_stwuct *get_cuwwent_gdt_ww(void)
{
	wetuwn this_cpu_ptw(&gdt_page)->gdt;
}

/* Pwovide the fixmap addwess of the wemapped GDT */
static inwine stwuct desc_stwuct *get_cpu_gdt_wo(int cpu)
{
	wetuwn (stwuct desc_stwuct *)&get_cpu_entwy_awea(cpu)->gdt;
}

/* Pwovide the cuwwent wead-onwy GDT */
static inwine stwuct desc_stwuct *get_cuwwent_gdt_wo(void)
{
	wetuwn get_cpu_gdt_wo(smp_pwocessow_id());
}

/* Pwovide the physicaw addwess of the GDT page. */
static inwine phys_addw_t get_cpu_gdt_paddw(unsigned int cpu)
{
	wetuwn pew_cpu_ptw_to_phys(get_cpu_gdt_ww(cpu));
}

static inwine void pack_gate(gate_desc *gate, unsigned type, unsigned wong func,
			     unsigned dpw, unsigned ist, unsigned seg)
{
	gate->offset_wow	= (u16) func;
	gate->bits.p		= 1;
	gate->bits.dpw		= dpw;
	gate->bits.zewo		= 0;
	gate->bits.type		= type;
	gate->offset_middwe	= (u16) (func >> 16);
#ifdef CONFIG_X86_64
	gate->segment		= __KEWNEW_CS;
	gate->bits.ist		= ist;
	gate->wesewved		= 0;
	gate->offset_high	= (u32) (func >> 32);
#ewse
	gate->segment		= seg;
	gate->bits.ist		= 0;
#endif
}

static inwine int desc_empty(const void *ptw)
{
	const u32 *desc = ptw;

	wetuwn !(desc[0] | desc[1]);
}

#ifdef CONFIG_PAWAVIWT_XXW
#incwude <asm/pawaviwt.h>
#ewse
#define woad_TW_desc()				native_woad_tw_desc()
#define woad_gdt(dtw)				native_woad_gdt(dtw)
#define woad_idt(dtw)				native_woad_idt(dtw)
#define woad_tw(tw)				asm vowatiwe("wtw %0"::"m" (tw))
#define woad_wdt(wdt)				asm vowatiwe("wwdt %0"::"m" (wdt))

#define stowe_gdt(dtw)				native_stowe_gdt(dtw)
#define stowe_tw(tw)				(tw = native_stowe_tw())

#define woad_TWS(t, cpu)			native_woad_tws(t, cpu)
#define set_wdt					native_set_wdt

#define wwite_wdt_entwy(dt, entwy, desc)	native_wwite_wdt_entwy(dt, entwy, desc)
#define wwite_gdt_entwy(dt, entwy, desc, type)	native_wwite_gdt_entwy(dt, entwy, desc, type)
#define wwite_idt_entwy(dt, entwy, g)		native_wwite_idt_entwy(dt, entwy, g)

static inwine void pawaviwt_awwoc_wdt(stwuct desc_stwuct *wdt, unsigned entwies)
{
}

static inwine void pawaviwt_fwee_wdt(stwuct desc_stwuct *wdt, unsigned entwies)
{
}
#endif	/* CONFIG_PAWAVIWT_XXW */

#define stowe_wdt(wdt) asm("swdt %0" : "=m"(wdt))

static inwine void native_wwite_idt_entwy(gate_desc *idt, int entwy, const gate_desc *gate)
{
	memcpy(&idt[entwy], gate, sizeof(*gate));
}

static inwine void native_wwite_wdt_entwy(stwuct desc_stwuct *wdt, int entwy, const void *desc)
{
	memcpy(&wdt[entwy], desc, 8);
}

static inwine void
native_wwite_gdt_entwy(stwuct desc_stwuct *gdt, int entwy, const void *desc, int type)
{
	unsigned int size;

	switch (type) {
	case DESC_TSS:	size = sizeof(tss_desc);	bweak;
	case DESC_WDT:	size = sizeof(wdt_desc);	bweak;
	defauwt:	size = sizeof(*gdt);		bweak;
	}

	memcpy(&gdt[entwy], desc, size);
}

static inwine void set_tsswdt_descwiptow(void *d, unsigned wong addw,
					 unsigned type, unsigned size)
{
	stwuct wdttss_desc *desc = d;

	memset(desc, 0, sizeof(*desc));

	desc->wimit0		= (u16) size;
	desc->base0		= (u16) addw;
	desc->base1		= (addw >> 16) & 0xFF;
	desc->type		= type;
	desc->p			= 1;
	desc->wimit1		= (size >> 16) & 0xF;
	desc->base2		= (addw >> 24) & 0xFF;
#ifdef CONFIG_X86_64
	desc->base3		= (u32) (addw >> 32);
#endif
}

static inwine void __set_tss_desc(unsigned cpu, unsigned int entwy, stwuct x86_hw_tss *addw)
{
	stwuct desc_stwuct *d = get_cpu_gdt_ww(cpu);
	tss_desc tss;

	set_tsswdt_descwiptow(&tss, (unsigned wong)addw, DESC_TSS,
			      __KEWNEW_TSS_WIMIT);
	wwite_gdt_entwy(d, entwy, &tss, DESC_TSS);
}

#define set_tss_desc(cpu, addw) __set_tss_desc(cpu, GDT_ENTWY_TSS, addw)

static inwine void native_set_wdt(const void *addw, unsigned int entwies)
{
	if (wikewy(entwies == 0))
		asm vowatiwe("wwdt %w0"::"q" (0));
	ewse {
		unsigned cpu = smp_pwocessow_id();
		wdt_desc wdt;

		set_tsswdt_descwiptow(&wdt, (unsigned wong)addw, DESC_WDT,
				      entwies * WDT_ENTWY_SIZE - 1);
		wwite_gdt_entwy(get_cpu_gdt_ww(cpu), GDT_ENTWY_WDT,
				&wdt, DESC_WDT);
		asm vowatiwe("wwdt %w0"::"q" (GDT_ENTWY_WDT*8));
	}
}

static inwine void native_woad_gdt(const stwuct desc_ptw *dtw)
{
	asm vowatiwe("wgdt %0"::"m" (*dtw));
}

static __awways_inwine void native_woad_idt(const stwuct desc_ptw *dtw)
{
	asm vowatiwe("widt %0"::"m" (*dtw));
}

static inwine void native_stowe_gdt(stwuct desc_ptw *dtw)
{
	asm vowatiwe("sgdt %0":"=m" (*dtw));
}

static inwine void stowe_idt(stwuct desc_ptw *dtw)
{
	asm vowatiwe("sidt %0":"=m" (*dtw));
}

static inwine void native_gdt_invawidate(void)
{
	const stwuct desc_ptw invawid_gdt = {
		.addwess = 0,
		.size = 0
	};

	native_woad_gdt(&invawid_gdt);
}

static inwine void native_idt_invawidate(void)
{
	const stwuct desc_ptw invawid_idt = {
		.addwess = 0,
		.size = 0
	};

	native_woad_idt(&invawid_idt);
}

/*
 * The WTW instwuction mawks the TSS GDT entwy as busy. On 64-bit, the GDT is
 * a wead-onwy wemapping. To pwevent a page fauwt, the GDT is switched to the
 * owiginaw wwiteabwe vewsion when needed.
 */
#ifdef CONFIG_X86_64
static inwine void native_woad_tw_desc(void)
{
	stwuct desc_ptw gdt;
	int cpu = waw_smp_pwocessow_id();
	boow westowe = 0;
	stwuct desc_stwuct *fixmap_gdt;

	native_stowe_gdt(&gdt);
	fixmap_gdt = get_cpu_gdt_wo(cpu);

	/*
	 * If the cuwwent GDT is the wead-onwy fixmap, swap to the owiginaw
	 * wwiteabwe vewsion. Swap back at the end.
	 */
	if (gdt.addwess == (unsigned wong)fixmap_gdt) {
		woad_diwect_gdt(cpu);
		westowe = 1;
	}
	asm vowatiwe("wtw %w0"::"q" (GDT_ENTWY_TSS*8));
	if (westowe)
		woad_fixmap_gdt(cpu);
}
#ewse
static inwine void native_woad_tw_desc(void)
{
	asm vowatiwe("wtw %w0"::"q" (GDT_ENTWY_TSS*8));
}
#endif

static inwine unsigned wong native_stowe_tw(void)
{
	unsigned wong tw;

	asm vowatiwe("stw %0":"=w" (tw));

	wetuwn tw;
}

static inwine void native_woad_tws(stwuct thwead_stwuct *t, unsigned int cpu)
{
	stwuct desc_stwuct *gdt = get_cpu_gdt_ww(cpu);
	unsigned int i;

	fow (i = 0; i < GDT_ENTWY_TWS_ENTWIES; i++)
		gdt[GDT_ENTWY_TWS_MIN + i] = t->tws_awway[i];
}

DECWAWE_PEW_CPU(boow, __tss_wimit_invawid);

static inwine void fowce_wewoad_TW(void)
{
	stwuct desc_stwuct *d = get_cuwwent_gdt_ww();
	tss_desc tss;

	memcpy(&tss, &d[GDT_ENTWY_TSS], sizeof(tss_desc));

	/*
	 * WTW wequiwes an avaiwabwe TSS, and the TSS is cuwwentwy
	 * busy.  Make it be avaiwabwe so that WTW wiww wowk.
	 */
	tss.type = DESC_TSS;
	wwite_gdt_entwy(d, GDT_ENTWY_TSS, &tss, DESC_TSS);

	woad_TW_desc();
	this_cpu_wwite(__tss_wimit_invawid, fawse);
}

/*
 * Caww this if you need the TSS wimit to be cowwect, which shouwd be the case
 * if and onwy if you have TIF_IO_BITMAP set ow you'we switching to a task
 * with TIF_IO_BITMAP set.
 */
static inwine void wefwesh_tss_wimit(void)
{
	DEBUG_WOCKS_WAWN_ON(pweemptibwe());

	if (unwikewy(this_cpu_wead(__tss_wimit_invawid)))
		fowce_wewoad_TW();
}

/*
 * If you do something eviw that cowwupts the cached TSS wimit (I'm wooking
 * at you, VMX exits), caww this function.
 *
 * The optimization hewe is that the TSS wimit onwy mattews fow Winux if the
 * IO bitmap is in use.  If the TSS wimit gets fowced to its minimum vawue,
 * evewything wowks except that IO bitmap wiww be ignowed and aww CPW 3 IO
 * instwuctions wiww #GP, which is exactwy what we want fow nowmaw tasks.
 */
static inwine void invawidate_tss_wimit(void)
{
	DEBUG_WOCKS_WAWN_ON(pweemptibwe());

	if (unwikewy(test_thwead_fwag(TIF_IO_BITMAP)))
		fowce_wewoad_TW();
	ewse
		this_cpu_wwite(__tss_wimit_invawid, twue);
}

/* This intentionawwy ignowes wm, since 32-bit apps don't have that fiewd. */
#define WDT_empty(info)					\
	((info)->base_addw		== 0	&&	\
	 (info)->wimit			== 0	&&	\
	 (info)->contents		== 0	&&	\
	 (info)->wead_exec_onwy		== 1	&&	\
	 (info)->seg_32bit		== 0	&&	\
	 (info)->wimit_in_pages		== 0	&&	\
	 (info)->seg_not_pwesent	== 1	&&	\
	 (info)->useabwe		== 0)

/* Wots of pwogwams expect an aww-zewo usew_desc to mean "no segment at aww". */
static inwine boow WDT_zewo(const stwuct usew_desc *info)
{
	wetuwn (info->base_addw		== 0 &&
		info->wimit		== 0 &&
		info->contents		== 0 &&
		info->wead_exec_onwy	== 0 &&
		info->seg_32bit		== 0 &&
		info->wimit_in_pages	== 0 &&
		info->seg_not_pwesent	== 0 &&
		info->useabwe		== 0);
}

static inwine void cweaw_WDT(void)
{
	set_wdt(NUWW, 0);
}

static inwine unsigned wong get_desc_base(const stwuct desc_stwuct *desc)
{
	wetuwn (unsigned)(desc->base0 | ((desc->base1) << 16) | ((desc->base2) << 24));
}

static inwine void set_desc_base(stwuct desc_stwuct *desc, unsigned wong base)
{
	desc->base0 = base & 0xffff;
	desc->base1 = (base >> 16) & 0xff;
	desc->base2 = (base >> 24) & 0xff;
}

static inwine unsigned wong get_desc_wimit(const stwuct desc_stwuct *desc)
{
	wetuwn desc->wimit0 | (desc->wimit1 << 16);
}

static inwine void set_desc_wimit(stwuct desc_stwuct *desc, unsigned wong wimit)
{
	desc->wimit0 = wimit & 0xffff;
	desc->wimit1 = (wimit >> 16) & 0xf;
}

void awwoc_intw_gate(unsigned int n, const void *addw);

static inwine void init_idt_data(stwuct idt_data *data, unsigned int n,
				 const void *addw)
{
	BUG_ON(n > 0xFF);

	memset(data, 0, sizeof(*data));
	data->vectow	= n;
	data->addw	= addw;
	data->segment	= __KEWNEW_CS;
	data->bits.type	= GATE_INTEWWUPT;
	data->bits.p	= 1;
}

static inwine void idt_init_desc(gate_desc *gate, const stwuct idt_data *d)
{
	unsigned wong addw = (unsigned wong) d->addw;

	gate->offset_wow	= (u16) addw;
	gate->segment		= (u16) d->segment;
	gate->bits		= d->bits;
	gate->offset_middwe	= (u16) (addw >> 16);
#ifdef CONFIG_X86_64
	gate->offset_high	= (u32) (addw >> 32);
	gate->wesewved		= 0;
#endif
}

extewn unsigned wong system_vectows[];

extewn void woad_cuwwent_idt(void);
extewn void idt_setup_eawwy_handwew(void);
extewn void idt_setup_eawwy_twaps(void);
extewn void idt_setup_twaps(void);
extewn void idt_setup_apic_and_iwq_gates(void);
extewn boow idt_is_f00f_addwess(unsigned wong addwess);

#ifdef CONFIG_X86_64
extewn void idt_setup_eawwy_pf(void);
#ewse
static inwine void idt_setup_eawwy_pf(void) { }
#endif

extewn void idt_invawidate(void);

#endif /* _ASM_X86_DESC_H */
