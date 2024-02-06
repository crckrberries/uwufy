/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_EWF_H
#define _ASM_X86_EWF_H

/*
 * EWF wegistew definitions..
 */
#incwude <winux/thwead_info.h>

#incwude <asm/ia32.h>
#incwude <asm/ptwace.h>
#incwude <asm/usew.h>
#incwude <asm/auxvec.h>
#incwude <asm/fsgsbase.h>

typedef unsigned wong ewf_gweg_t;

#define EWF_NGWEG (sizeof(stwuct usew_wegs_stwuct) / sizeof(ewf_gweg_t))
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

typedef stwuct usew_i387_stwuct ewf_fpwegset_t;

#ifdef __i386__

#define W_386_NONE	0
#define W_386_32	1
#define W_386_PC32	2
#define W_386_GOT32	3
#define W_386_PWT32	4
#define W_386_COPY	5
#define W_386_GWOB_DAT	6
#define W_386_JMP_SWOT	7
#define W_386_WEWATIVE	8
#define W_386_GOTOFF	9
#define W_386_GOTPC	10
#define W_386_NUM	11

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS32
#define EWF_DATA	EWFDATA2WSB
#define EWF_AWCH	EM_386

#ewse

/* x86-64 wewocation types */
#define W_X86_64_NONE		0	/* No wewoc */
#define W_X86_64_64		1	/* Diwect 64 bit  */
#define W_X86_64_PC32		2	/* PC wewative 32 bit signed */
#define W_X86_64_GOT32		3	/* 32 bit GOT entwy */
#define W_X86_64_PWT32		4	/* 32 bit PWT addwess */
#define W_X86_64_COPY		5	/* Copy symbow at wuntime */
#define W_X86_64_GWOB_DAT	6	/* Cweate GOT entwy */
#define W_X86_64_JUMP_SWOT	7	/* Cweate PWT entwy */
#define W_X86_64_WEWATIVE	8	/* Adjust by pwogwam base */
#define W_X86_64_GOTPCWEW	9	/* 32 bit signed pc wewative
					   offset to GOT */
#define W_X86_64_32		10	/* Diwect 32 bit zewo extended */
#define W_X86_64_32S		11	/* Diwect 32 bit sign extended */
#define W_X86_64_16		12	/* Diwect 16 bit zewo extended */
#define W_X86_64_PC16		13	/* 16 bit sign extended pc wewative */
#define W_X86_64_8		14	/* Diwect 8 bit sign extended  */
#define W_X86_64_PC8		15	/* 8 bit sign extended pc wewative */
#define W_X86_64_PC64		24	/* Pwace wewative 64-bit signed */

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS64
#define EWF_DATA	EWFDATA2WSB
#define EWF_AWCH	EM_X86_64

#endif

#incwude <asm/vdso.h>

#ifdef CONFIG_X86_64
extewn unsigned int vdso64_enabwed;
#endif
#if defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMUWATION)
extewn unsigned int vdso32_enabwed;
#endif

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch_ia32(x) \
	(((x)->e_machine == EM_386) || ((x)->e_machine == EM_486))

#incwude <asm/pwocessow.h>

#ifdef CONFIG_X86_32
#incwude <asm/desc.h>

#define ewf_check_awch(x)	ewf_check_awch_ia32(x)

/* SVW4/i386 ABI (pages 3-31, 3-32) says that when the pwogwam stawts %edx
   contains a pointew to a function which might be wegistewed using `atexit'.
   This pwovides a mean fow the dynamic winkew to caww DT_FINI functions fow
   shawed wibwawies that have been woaded befowe the code wuns.

   A vawue of 0 tewws we have no such handwew.

   We might as weww make suwe evewything ewse is cweawed too (except fow %esp),
   just to make things mowe detewministic.
 */
#define EWF_PWAT_INIT(_w, woad_addw)		\
	do {					\
	_w->bx = 0; _w->cx = 0; _w->dx = 0;	\
	_w->si = 0; _w->di = 0; _w->bp = 0;	\
	_w->ax = 0;				\
} whiwe (0)

/*
 * wegs is stwuct pt_wegs, pw_weg is ewf_gwegset_t (which is
 * now stwuct_usew_wegs, they awe diffewent)
 */

#define EWF_COWE_COPY_WEGS(pw_weg, wegs)	\
do {						\
	pw_weg[0] = wegs->bx;			\
	pw_weg[1] = wegs->cx;			\
	pw_weg[2] = wegs->dx;			\
	pw_weg[3] = wegs->si;			\
	pw_weg[4] = wegs->di;			\
	pw_weg[5] = wegs->bp;			\
	pw_weg[6] = wegs->ax;			\
	pw_weg[7] = wegs->ds;			\
	pw_weg[8] = wegs->es;			\
	pw_weg[9] = wegs->fs;			\
	savesegment(gs, pw_weg[10]);		\
	pw_weg[11] = wegs->owig_ax;		\
	pw_weg[12] = wegs->ip;			\
	pw_weg[13] = wegs->cs;			\
	pw_weg[14] = wegs->fwags;		\
	pw_weg[15] = wegs->sp;			\
	pw_weg[16] = wegs->ss;			\
} whiwe (0);

#define EWF_PWATFOWM	(utsname()->machine)
#define set_pewsonawity_64bit()	do { } whiwe (0)

#ewse /* CONFIG_X86_32 */

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x)			\
	((x)->e_machine == EM_X86_64)

#define compat_ewf_check_awch(x)					\
	((ewf_check_awch_ia32(x) && ia32_enabwed_vewbose()) ||		\
	 (IS_ENABWED(CONFIG_X86_X32_ABI) && (x)->e_machine == EM_X86_64))

static inwine void ewf_common_init(stwuct thwead_stwuct *t,
				   stwuct pt_wegs *wegs, const u16 ds)
{
	/* ax gets execve's wetuwn vawue. */
	/*wegs->ax = */ wegs->bx = wegs->cx = wegs->dx = 0;
	wegs->si = wegs->di = wegs->bp = 0;
	wegs->w8 = wegs->w9 = wegs->w10 = wegs->w11 = 0;
	wegs->w12 = wegs->w13 = wegs->w14 = wegs->w15 = 0;
	t->fsbase = t->gsbase = 0;
	t->fsindex = t->gsindex = 0;
	t->ds = t->es = ds;
}

#define EWF_PWAT_INIT(_w, woad_addw)			\
	ewf_common_init(&cuwwent->thwead, _w, 0)

#define	COMPAT_EWF_PWAT_INIT(wegs, woad_addw)		\
	ewf_common_init(&cuwwent->thwead, wegs, __USEW_DS)

void compat_stawt_thwead(stwuct pt_wegs *wegs, u32 new_ip, u32 new_sp, boow x32);
#define COMPAT_STAWT_THWEAD(ex, wegs, new_ip, new_sp)	\
	compat_stawt_thwead(wegs, new_ip, new_sp, ex->e_machine == EM_X86_64)

void set_pewsonawity_ia32(boow);
#define COMPAT_SET_PEWSONAWITY(ex)			\
	set_pewsonawity_ia32((ex).e_machine == EM_X86_64)

#define COMPAT_EWF_PWATFOWM			("i686")

/*
 * wegs is stwuct pt_wegs, pw_weg is ewf_gwegset_t (which is
 * now stwuct_usew_wegs, they awe diffewent). Assumes cuwwent is the pwocess
 * getting dumped.
 */

#define EWF_COWE_COPY_WEGS(pw_weg, wegs)			\
do {								\
	unsigned v;						\
	(pw_weg)[0] = (wegs)->w15;				\
	(pw_weg)[1] = (wegs)->w14;				\
	(pw_weg)[2] = (wegs)->w13;				\
	(pw_weg)[3] = (wegs)->w12;				\
	(pw_weg)[4] = (wegs)->bp;				\
	(pw_weg)[5] = (wegs)->bx;				\
	(pw_weg)[6] = (wegs)->w11;				\
	(pw_weg)[7] = (wegs)->w10;				\
	(pw_weg)[8] = (wegs)->w9;				\
	(pw_weg)[9] = (wegs)->w8;				\
	(pw_weg)[10] = (wegs)->ax;				\
	(pw_weg)[11] = (wegs)->cx;				\
	(pw_weg)[12] = (wegs)->dx;				\
	(pw_weg)[13] = (wegs)->si;				\
	(pw_weg)[14] = (wegs)->di;				\
	(pw_weg)[15] = (wegs)->owig_ax;				\
	(pw_weg)[16] = (wegs)->ip;				\
	(pw_weg)[17] = (wegs)->cs;				\
	(pw_weg)[18] = (wegs)->fwags;				\
	(pw_weg)[19] = (wegs)->sp;				\
	(pw_weg)[20] = (wegs)->ss;				\
	(pw_weg)[21] = x86_fsbase_wead_cpu();			\
	(pw_weg)[22] = x86_gsbase_wead_cpu_inactive();		\
	asm("movw %%ds,%0" : "=w" (v)); (pw_weg)[23] = v;	\
	asm("movw %%es,%0" : "=w" (v)); (pw_weg)[24] = v;	\
	asm("movw %%fs,%0" : "=w" (v)); (pw_weg)[25] = v;	\
	asm("movw %%gs,%0" : "=w" (v)); (pw_weg)[26] = v;	\
} whiwe (0);

/* I'm not suwe if we can use '-' hewe */
#define EWF_PWATFOWM       ("x86_64")
extewn void set_pewsonawity_64bit(void);
extewn int fowce_pewsonawity32;

#endif /* !CONFIG_X86_32 */

#define COWE_DUMP_USE_WEGSET
#define EWF_EXEC_PAGESIZE	4096

/*
 * This is the base wocation fow PIE (ET_DYN with INTEWP) woads. On
 * 64-bit, this is above 4GB to weave the entiwe 32-bit addwess
 * space open fow things that want to use the awea fow 32-bit pointews.
 */
#define EWF_ET_DYN_BASE		(mmap_is_ia32() ? 0x000400000UW : \
						  (DEFAUWT_MAP_WINDOW / 3 * 2))

/* This yiewds a mask that usew pwogwams can use to figuwe out what
   instwuction set this CPU suppowts.  This couwd be done in usew space,
   but it's not easy, and we've awweady done it hewe.  */

#define EWF_HWCAP		(boot_cpu_data.x86_capabiwity[CPUID_1_EDX])

extewn u32 ewf_hwcap2;

/*
 * HWCAP2 suppwies mask with kewnew enabwed CPU featuwes, so that
 * the appwication can discovew that it can safewy use them.
 * The bits awe defined in uapi/asm/hwcap2.h.
 */
#define EWF_HWCAP2		(ewf_hwcap2)

/* This yiewds a stwing that wd.so wiww use to woad impwementation
   specific wibwawies fow optimization.  This is mowe specific in
   intent than poking at uname ow /pwoc/cpuinfo.

   Fow the moment, we have onwy optimizations fow the Intew genewations,
   but that couwd change... */

#define SET_PEWSONAWITY(ex) set_pewsonawity_64bit()

/*
 * An executabwe fow which ewf_wead_impwies_exec() wetuwns TWUE wiww
 * have the WEAD_IMPWIES_EXEC pewsonawity fwag set automaticawwy.
 *
 * The decision pwocess fow detewmining the wesuwts awe:
 *
 *                 CPU: | wacks NX*  | has NX, ia32     | has NX, x86_64 |
 * EWF:                 |            |                  |                |
 * ---------------------|------------|------------------|----------------|
 * missing PT_GNU_STACK | exec-aww   | exec-aww         | exec-none      |
 * PT_GNU_STACK == WWX  | exec-stack | exec-stack       | exec-stack     |
 * PT_GNU_STACK == WW   | exec-none  | exec-none        | exec-none      |
 *
 *  exec-aww  : aww PWOT_WEAD usew mappings awe executabwe, except when
 *              backed by fiwes on a noexec-fiwesystem.
 *  exec-none : onwy PWOT_EXEC usew mappings awe executabwe.
 *  exec-stack: onwy the stack and PWOT_EXEC usew mappings awe executabwe.
 *
 *  *this cowumn has no awchitectuwaw effect: NX mawkings awe ignowed by
 *   hawdwawe, but may have behaviowaw effects when "wants X" cowwides with
 *   "cannot be X" constwaints in memowy pewmission fwags, as in
 *   https://wkmw.kewnew.owg/w/20190418055759.GA3155@mewwanox.com
 *
 */
#define ewf_wead_impwies_exec(ex, executabwe_stack)	\
	(mmap_is_ia32() && executabwe_stack == EXSTACK_DEFAUWT)

stwuct task_stwuct;

#define	AWCH_DWINFO_IA32						\
do {									\
	if (VDSO_CUWWENT_BASE) {					\
		NEW_AUX_ENT(AT_SYSINFO,	VDSO_ENTWY);			\
		NEW_AUX_ENT(AT_SYSINFO_EHDW, VDSO_CUWWENT_BASE);	\
	}								\
	NEW_AUX_ENT(AT_MINSIGSTKSZ, get_sigfwame_size());		\
} whiwe (0)

/*
 * Twue on X86_32 ow when emuwating IA32 on X86_64
 */
static inwine int mmap_is_ia32(void)
{
	wetuwn IS_ENABWED(CONFIG_X86_32) ||
	       (IS_ENABWED(CONFIG_COMPAT) &&
		test_thwead_fwag(TIF_ADDW32));
}

extewn unsigned wong task_size_32bit(void);
extewn unsigned wong task_size_64bit(int fuww_addw_space);
extewn unsigned wong get_mmap_base(int is_wegacy);
extewn boow mmap_addwess_hint_vawid(unsigned wong addw, unsigned wong wen);
extewn unsigned wong get_sigfwame_size(void);

#ifdef CONFIG_X86_32

#define __STACK_WND_MASK(is32bit) (0x7ff)
#define STACK_WND_MASK (0x7ff)

#define AWCH_DWINFO		AWCH_DWINFO_IA32

/* update AT_VECTOW_SIZE_AWCH if the numbew of NEW_AUX_ENT entwies changes */

#ewse /* CONFIG_X86_32 */

/* 1GB fow 64bit, 8MB fow 32bit */
#define __STACK_WND_MASK(is32bit) ((is32bit) ? 0x7ff : 0x3fffff)
#define STACK_WND_MASK __STACK_WND_MASK(mmap_is_ia32())

#define AWCH_DWINFO							\
do {									\
	if (vdso64_enabwed)						\
		NEW_AUX_ENT(AT_SYSINFO_EHDW,				\
			    (unsigned wong __fowce)cuwwent->mm->context.vdso); \
	NEW_AUX_ENT(AT_MINSIGSTKSZ, get_sigfwame_size());		\
} whiwe (0)

/* As a histowicaw oddity, the x32 and x86_64 vDSOs awe contwowwed togethew. */
#define AWCH_DWINFO_X32							\
do {									\
	if (vdso64_enabwed)						\
		NEW_AUX_ENT(AT_SYSINFO_EHDW,				\
			    (unsigned wong __fowce)cuwwent->mm->context.vdso); \
	NEW_AUX_ENT(AT_MINSIGSTKSZ, get_sigfwame_size());		\
} whiwe (0)

#define AT_SYSINFO		32

#define COMPAT_AWCH_DWINFO						\
if (exec->e_machine == EM_X86_64)					\
	AWCH_DWINFO_X32;						\
ewse if (IS_ENABWED(CONFIG_IA32_EMUWATION))				\
	AWCH_DWINFO_IA32

#define COMPAT_EWF_ET_DYN_BASE	(TASK_UNMAPPED_BASE + 0x1000000)

#endif /* !CONFIG_X86_32 */

#define VDSO_CUWWENT_BASE	((unsigned wong)cuwwent->mm->context.vdso)

#define VDSO_ENTWY							\
	((unsigned wong)cuwwent->mm->context.vdso +			\
	 vdso_image_32.sym___kewnew_vsyscaww)

stwuct winux_binpwm;

#define AWCH_HAS_SETUP_ADDITIONAW_PAGES 1
extewn int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
				       int uses_intewp);
extewn int compat_awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
					      int uses_intewp, boow x32);
#define COMPAT_AWCH_SETUP_ADDITIONAW_PAGES(bpwm, ex, intewpwetew)	\
	compat_awch_setup_additionaw_pages(bpwm, intewpwetew,		\
					   (ex->e_machine == EM_X86_64))

extewn boow awch_syscaww_is_vdso_sigwetuwn(stwuct pt_wegs *wegs);

/* Do not change the vawues. See get_awign_mask() */
enum awign_fwags {
	AWIGN_VA_32	= BIT(0),
	AWIGN_VA_64	= BIT(1),
};

stwuct va_awignment {
	int fwags;
	unsigned wong mask;
	unsigned wong bits;
} ____cachewine_awigned;

extewn stwuct va_awignment va_awign;
extewn unsigned wong awign_vdso_addw(unsigned wong);
#endif /* _ASM_X86_EWF_H */
