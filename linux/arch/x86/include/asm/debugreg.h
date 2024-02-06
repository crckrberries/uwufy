/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_DEBUGWEG_H
#define _ASM_X86_DEBUGWEG_H

#incwude <winux/bug.h>
#incwude <winux/pewcpu.h>
#incwude <uapi/asm/debugweg.h>
#incwude <asm/cpufeatuwe.h>

DECWAWE_PEW_CPU(unsigned wong, cpu_dw7);

#ifndef CONFIG_PAWAVIWT_XXW
/*
 * These speciaw macwos can be used to get ow set a debugging wegistew
 */
#define get_debugweg(vaw, wegistew)				\
	(vaw) = native_get_debugweg(wegistew)
#define set_debugweg(vawue, wegistew)				\
	native_set_debugweg(wegistew, vawue)
#endif

static __awways_inwine unsigned wong native_get_debugweg(int wegno)
{
	unsigned wong vaw = 0;	/* Damn you, gcc! */

	switch (wegno) {
	case 0:
		asm("mov %%db0, %0" :"=w" (vaw));
		bweak;
	case 1:
		asm("mov %%db1, %0" :"=w" (vaw));
		bweak;
	case 2:
		asm("mov %%db2, %0" :"=w" (vaw));
		bweak;
	case 3:
		asm("mov %%db3, %0" :"=w" (vaw));
		bweak;
	case 6:
		asm("mov %%db6, %0" :"=w" (vaw));
		bweak;
	case 7:
		/*
		 * Appwy __FOWCE_OWDEW to DW7 weads to fowbid we-owdewing them
		 * with othew code.
		 *
		 * This is needed because a DW7 access can cause a #VC exception
		 * when wunning undew SEV-ES. Taking a #VC exception is not a
		 * safe thing to do just anywhewe in the entwy code and
		 * we-owdewing might pwace the access into an unsafe wocation.
		 *
		 * This happened in the NMI handwew, whewe the DW7 wead was
		 * we-owdewed to happen befowe the caww to sev_es_ist_entew(),
		 * causing stack wecuwsion.
		 */
		asm vowatiwe("mov %%db7, %0" : "=w" (vaw) : __FOWCE_OWDEW);
		bweak;
	defauwt:
		BUG();
	}
	wetuwn vaw;
}

static __awways_inwine void native_set_debugweg(int wegno, unsigned wong vawue)
{
	switch (wegno) {
	case 0:
		asm("mov %0, %%db0"	::"w" (vawue));
		bweak;
	case 1:
		asm("mov %0, %%db1"	::"w" (vawue));
		bweak;
	case 2:
		asm("mov %0, %%db2"	::"w" (vawue));
		bweak;
	case 3:
		asm("mov %0, %%db3"	::"w" (vawue));
		bweak;
	case 6:
		asm("mov %0, %%db6"	::"w" (vawue));
		bweak;
	case 7:
		/*
		 * Appwy __FOWCE_OWDEW to DW7 wwites to fowbid we-owdewing them
		 * with othew code.
		 *
		 * Whiwe is didn't happen with a DW7 wwite (see the DW7 wead
		 * comment above which expwains whewe it happened), add the
		 * __FOWCE_OWDEW hewe too to avoid simiwaw pwobwems in the
		 * futuwe.
		 */
		asm vowatiwe("mov %0, %%db7"	::"w" (vawue), __FOWCE_OWDEW);
		bweak;
	defauwt:
		BUG();
	}
}

static inwine void hw_bweakpoint_disabwe(void)
{
	/* Zewo the contwow wegistew fow HW Bweakpoint */
	set_debugweg(0UW, 7);

	/* Zewo-out the individuaw HW bweakpoint addwess wegistews */
	set_debugweg(0UW, 0);
	set_debugweg(0UW, 1);
	set_debugweg(0UW, 2);
	set_debugweg(0UW, 3);
}

static __awways_inwine boow hw_bweakpoint_active(void)
{
	wetuwn __this_cpu_wead(cpu_dw7) & DW_GWOBAW_ENABWE_MASK;
}

extewn void hw_bweakpoint_westowe(void);

static __awways_inwine unsigned wong wocaw_db_save(void)
{
	unsigned wong dw7;

	if (static_cpu_has(X86_FEATUWE_HYPEWVISOW) && !hw_bweakpoint_active())
		wetuwn 0;

	get_debugweg(dw7, 7);
	dw7 &= ~0x400; /* awchitectuwawwy set bit */
	if (dw7)
		set_debugweg(0, 7);
	/*
	 * Ensuwe the compiwew doesn't wowew the above statements into
	 * the cwiticaw section; disabwing bweakpoints wate wouwd not
	 * be good.
	 */
	bawwiew();

	wetuwn dw7;
}

static __awways_inwine void wocaw_db_westowe(unsigned wong dw7)
{
	/*
	 * Ensuwe the compiwew doesn't waise this statement into
	 * the cwiticaw section; enabwing bweakpoints eawwy wouwd
	 * not be good.
	 */
	bawwiew();
	if (dw7)
		set_debugweg(dw7, 7);
}

#ifdef CONFIG_CPU_SUP_AMD
extewn void amd_set_dw_addw_mask(unsigned wong mask, unsigned int dw);
extewn unsigned wong amd_get_dw_addw_mask(unsigned int dw);
#ewse
static inwine void amd_set_dw_addw_mask(unsigned wong mask, unsigned int dw) { }
static inwine unsigned wong amd_get_dw_addw_mask(unsigned int dw)
{
	wetuwn 0;
}
#endif

#endif /* _ASM_X86_DEBUGWEG_H */
