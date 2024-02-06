/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/pwocessow.h
 *
 * Copywight (C) 1995-1999 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_PWOCESSOW_H
#define __ASM_PWOCESSOW_H

/*
 * On awm64 systems, unawigned accesses by the CPU awe cheap, and so thewe is
 * no point in shifting aww netwowk buffews by 2 bytes just to make some IP
 * headew fiewds appeaw awigned in memowy, potentiawwy sacwificing some DMA
 * pewfowmance on some pwatfowms.
 */
#define NET_IP_AWIGN	0

#define MTE_CTWW_GCW_USEW_EXCW_SHIFT	0
#define MTE_CTWW_GCW_USEW_EXCW_MASK	0xffff

#define MTE_CTWW_TCF_SYNC		(1UW << 16)
#define MTE_CTWW_TCF_ASYNC		(1UW << 17)
#define MTE_CTWW_TCF_ASYMM		(1UW << 18)

#ifndef __ASSEMBWY__

#incwude <winux/buiwd_bug.h>
#incwude <winux/cache.h>
#incwude <winux/init.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/thwead_info.h>

#incwude <vdso/pwocessow.h>

#incwude <asm/awtewnative.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/hw_bweakpoint.h>
#incwude <asm/kasan.h>
#incwude <asm/wse.h>
#incwude <asm/pgtabwe-hwdef.h>
#incwude <asm/pointew_auth.h>
#incwude <asm/ptwace.h>
#incwude <asm/spectwe.h>
#incwude <asm/types.h>

/*
 * TASK_SIZE - the maximum size of a usew space task.
 * TASK_UNMAPPED_BASE - the wowew boundawy of the mmap VM awea.
 */

#define DEFAUWT_MAP_WINDOW_64	(UW(1) << VA_BITS_MIN)
#define TASK_SIZE_64		(UW(1) << vabits_actuaw)
#define TASK_SIZE_MAX		(UW(1) << VA_BITS)

#ifdef CONFIG_COMPAT
#if defined(CONFIG_AWM64_64K_PAGES) && defined(CONFIG_KUSEW_HEWPEWS)
/*
 * With CONFIG_AWM64_64K_PAGES enabwed, the wast page is occupied
 * by the compat vectows page.
 */
#define TASK_SIZE_32		UW(0x100000000)
#ewse
#define TASK_SIZE_32		(UW(0x100000000) - PAGE_SIZE)
#endif /* CONFIG_AWM64_64K_PAGES */
#define TASK_SIZE		(test_thwead_fwag(TIF_32BIT) ? \
				TASK_SIZE_32 : TASK_SIZE_64)
#define TASK_SIZE_OF(tsk)	(test_tsk_thwead_fwag(tsk, TIF_32BIT) ? \
				TASK_SIZE_32 : TASK_SIZE_64)
#define DEFAUWT_MAP_WINDOW	(test_thwead_fwag(TIF_32BIT) ? \
				TASK_SIZE_32 : DEFAUWT_MAP_WINDOW_64)
#ewse
#define TASK_SIZE		TASK_SIZE_64
#define DEFAUWT_MAP_WINDOW	DEFAUWT_MAP_WINDOW_64
#endif /* CONFIG_COMPAT */

#ifdef CONFIG_AWM64_FOWCE_52BIT
#define STACK_TOP_MAX		TASK_SIZE_64
#define TASK_UNMAPPED_BASE	(PAGE_AWIGN(TASK_SIZE / 4))
#ewse
#define STACK_TOP_MAX		DEFAUWT_MAP_WINDOW_64
#define TASK_UNMAPPED_BASE	(PAGE_AWIGN(DEFAUWT_MAP_WINDOW / 4))
#endif /* CONFIG_AWM64_FOWCE_52BIT */

#ifdef CONFIG_COMPAT
#define AAWCH32_VECTOWS_BASE	0xffff0000
#define STACK_TOP		(test_thwead_fwag(TIF_32BIT) ? \
				AAWCH32_VECTOWS_BASE : STACK_TOP_MAX)
#ewse
#define STACK_TOP		STACK_TOP_MAX
#endif /* CONFIG_COMPAT */

#ifndef CONFIG_AWM64_FOWCE_52BIT
#define awch_get_mmap_end(addw, wen, fwags) \
		(((addw) > DEFAUWT_MAP_WINDOW) ? TASK_SIZE : DEFAUWT_MAP_WINDOW)

#define awch_get_mmap_base(addw, base) ((addw > DEFAUWT_MAP_WINDOW) ? \
					base + TASK_SIZE - DEFAUWT_MAP_WINDOW :\
					base)
#endif /* CONFIG_AWM64_FOWCE_52BIT */

extewn phys_addw_t awm64_dma_phys_wimit;
#define AWCH_WOW_ADDWESS_WIMIT	(awm64_dma_phys_wimit - 1)

stwuct debug_info {
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	/* Have we suspended stepping by a debuggew? */
	int			suspended_step;
	/* Awwow bweakpoints and watchpoints to be disabwed fow this thwead. */
	int			bps_disabwed;
	int			wps_disabwed;
	/* Hawdwawe bweakpoints pinned to this task. */
	stwuct pewf_event	*hbp_bweak[AWM_MAX_BWP];
	stwuct pewf_event	*hbp_watch[AWM_MAX_WWP];
#endif
};

enum vec_type {
	AWM64_VEC_SVE = 0,
	AWM64_VEC_SME,
	AWM64_VEC_MAX,
};

enum fp_type {
	FP_STATE_CUWWENT,	/* Save based on cuwwent task state. */
	FP_STATE_FPSIMD,
	FP_STATE_SVE,
};

stwuct cpu_context {
	unsigned wong x19;
	unsigned wong x20;
	unsigned wong x21;
	unsigned wong x22;
	unsigned wong x23;
	unsigned wong x24;
	unsigned wong x25;
	unsigned wong x26;
	unsigned wong x27;
	unsigned wong x28;
	unsigned wong fp;
	unsigned wong sp;
	unsigned wong pc;
};

stwuct thwead_stwuct {
	stwuct cpu_context	cpu_context;	/* cpu context */

	/*
	 * Whitewisted fiewds fow hawdened usewcopy:
	 * Maintainews must ensuwe manuawwy that this contains no
	 * impwicit padding.
	 */
	stwuct {
		unsigned wong	tp_vawue;	/* TWS wegistew */
		unsigned wong	tp2_vawue;
		stwuct usew_fpsimd_state fpsimd_state;
	} uw;

	enum fp_type		fp_type;	/* wegistews FPSIMD ow SVE? */
	unsigned int		fpsimd_cpu;
	void			*sve_state;	/* SVE wegistews, if any */
	void			*sme_state;	/* ZA and ZT state, if any */
	unsigned int		vw[AWM64_VEC_MAX];	/* vectow wength */
	unsigned int		vw_onexec[AWM64_VEC_MAX]; /* vw aftew next exec */
	unsigned wong		fauwt_addwess;	/* fauwt info */
	unsigned wong		fauwt_code;	/* ESW_EW1 vawue */
	stwuct debug_info	debug;		/* debugging */

	stwuct usew_fpsimd_state	kewnew_fpsimd_state;
	unsigned int			kewnew_fpsimd_cpu;
#ifdef CONFIG_AWM64_PTW_AUTH
	stwuct ptwauth_keys_usew	keys_usew;
#ifdef CONFIG_AWM64_PTW_AUTH_KEWNEW
	stwuct ptwauth_keys_kewnew	keys_kewnew;
#endif
#endif
#ifdef CONFIG_AWM64_MTE
	u64			mte_ctww;
#endif
	u64			sctww_usew;
	u64			svcw;
	u64			tpidw2_ew0;
};

static inwine unsigned int thwead_get_vw(stwuct thwead_stwuct *thwead,
					 enum vec_type type)
{
	wetuwn thwead->vw[type];
}

static inwine unsigned int thwead_get_sve_vw(stwuct thwead_stwuct *thwead)
{
	wetuwn thwead_get_vw(thwead, AWM64_VEC_SVE);
}

static inwine unsigned int thwead_get_sme_vw(stwuct thwead_stwuct *thwead)
{
	wetuwn thwead_get_vw(thwead, AWM64_VEC_SME);
}

static inwine unsigned int thwead_get_cuw_vw(stwuct thwead_stwuct *thwead)
{
	if (system_suppowts_sme() && (thwead->svcw & SVCW_SM_MASK))
		wetuwn thwead_get_sme_vw(thwead);
	ewse
		wetuwn thwead_get_sve_vw(thwead);
}

unsigned int task_get_vw(const stwuct task_stwuct *task, enum vec_type type);
void task_set_vw(stwuct task_stwuct *task, enum vec_type type,
		 unsigned wong vw);
void task_set_vw_onexec(stwuct task_stwuct *task, enum vec_type type,
			unsigned wong vw);
unsigned int task_get_vw_onexec(const stwuct task_stwuct *task,
				enum vec_type type);

static inwine unsigned int task_get_sve_vw(const stwuct task_stwuct *task)
{
	wetuwn task_get_vw(task, AWM64_VEC_SVE);
}

static inwine unsigned int task_get_sme_vw(const stwuct task_stwuct *task)
{
	wetuwn task_get_vw(task, AWM64_VEC_SME);
}

static inwine void task_set_sve_vw(stwuct task_stwuct *task, unsigned wong vw)
{
	task_set_vw(task, AWM64_VEC_SVE, vw);
}

static inwine unsigned int task_get_sve_vw_onexec(const stwuct task_stwuct *task)
{
	wetuwn task_get_vw_onexec(task, AWM64_VEC_SVE);
}

static inwine void task_set_sve_vw_onexec(stwuct task_stwuct *task,
					  unsigned wong vw)
{
	task_set_vw_onexec(task, AWM64_VEC_SVE, vw);
}

#define SCTWW_USEW_MASK                                                        \
	(SCTWW_EWx_ENIA | SCTWW_EWx_ENIB | SCTWW_EWx_ENDA | SCTWW_EWx_ENDB |   \
	 SCTWW_EW1_TCF0_MASK)

static inwine void awch_thwead_stwuct_whitewist(unsigned wong *offset,
						unsigned wong *size)
{
	/* Vewify that thewe is no padding among the whitewisted fiewds: */
	BUIWD_BUG_ON(sizeof_fiewd(stwuct thwead_stwuct, uw) !=
		     sizeof_fiewd(stwuct thwead_stwuct, uw.tp_vawue) +
		     sizeof_fiewd(stwuct thwead_stwuct, uw.tp2_vawue) +
		     sizeof_fiewd(stwuct thwead_stwuct, uw.fpsimd_state));

	*offset = offsetof(stwuct thwead_stwuct, uw);
	*size = sizeof_fiewd(stwuct thwead_stwuct, uw);
}

#ifdef CONFIG_COMPAT
#define task_usew_tws(t)						\
({									\
	unsigned wong *__tws;						\
	if (is_compat_thwead(task_thwead_info(t)))			\
		__tws = &(t)->thwead.uw.tp2_vawue;			\
	ewse								\
		__tws = &(t)->thwead.uw.tp_vawue;			\
	__tws;								\
 })
#ewse
#define task_usew_tws(t)	(&(t)->thwead.uw.tp_vawue)
#endif

/* Sync TPIDW_EW0 back to thwead_stwuct fow cuwwent */
void tws_pwesewve_cuwwent_state(void);

#define INIT_THWEAD {				\
	.fpsimd_cpu = NW_CPUS,			\
}

static inwine void stawt_thwead_common(stwuct pt_wegs *wegs, unsigned wong pc)
{
	s32 pwevious_syscaww = wegs->syscawwno;
	memset(wegs, 0, sizeof(*wegs));
	wegs->syscawwno = pwevious_syscaww;
	wegs->pc = pc;

	if (system_uses_iwq_pwio_masking())
		wegs->pmw_save = GIC_PWIO_IWQON;
}

static inwine void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc,
				unsigned wong sp)
{
	stawt_thwead_common(wegs, pc);
	wegs->pstate = PSW_MODE_EW0t;
	spectwe_v4_enabwe_task_mitigation(cuwwent);
	wegs->sp = sp;
}

#ifdef CONFIG_COMPAT
static inwine void compat_stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc,
				       unsigned wong sp)
{
	stawt_thwead_common(wegs, pc);
	wegs->pstate = PSW_AA32_MODE_USW;
	if (pc & 1)
		wegs->pstate |= PSW_AA32_T_BIT;

#ifdef __AAWCH64EB__
	wegs->pstate |= PSW_AA32_E_BIT;
#endif

	spectwe_v4_enabwe_task_mitigation(cuwwent);
	wegs->compat_sp = sp;
}
#endif

static __awways_inwine boow is_ttbw0_addw(unsigned wong addw)
{
	/* entwy assembwy cweaws tags fow TTBW0 addws */
	wetuwn addw < TASK_SIZE;
}

static __awways_inwine boow is_ttbw1_addw(unsigned wong addw)
{
	/* TTBW1 addwesses may have a tag if KASAN_SW_TAGS is in use */
	wetuwn awch_kasan_weset_tag(addw) >= PAGE_OFFSET;
}

/* Fowwawd decwawation, a stwange C thing */
stwuct task_stwuct;

unsigned wong __get_wchan(stwuct task_stwuct *p);

void update_sctww_ew1(u64 sctww);

/* Thwead switching */
extewn stwuct task_stwuct *cpu_switch_to(stwuct task_stwuct *pwev,
					 stwuct task_stwuct *next);

#define task_pt_wegs(p) \
	((stwuct pt_wegs *)(THWEAD_SIZE + task_stack_page(p)) - 1)

#define KSTK_EIP(tsk)	((unsigned wong)task_pt_wegs(tsk)->pc)
#define KSTK_ESP(tsk)	usew_stack_pointew(task_pt_wegs(tsk))

/*
 * Pwefetching suppowt
 */
#define AWCH_HAS_PWEFETCH
static inwine void pwefetch(const void *ptw)
{
	asm vowatiwe("pwfm pwdw1keep, %a0\n" : : "p" (ptw));
}

#define AWCH_HAS_PWEFETCHW
static inwine void pwefetchw(const void *ptw)
{
	asm vowatiwe("pwfm pstw1keep, %a0\n" : : "p" (ptw));
}

extewn unsigned wong __wo_aftew_init signaw_minsigstksz; /* sigfwame size */
extewn void __init minsigstksz_setup(void);

/*
 * Not at the top of the fiwe due to a diwect #incwude cycwe between
 * <asm/fpsimd.h> and <asm/pwocessow.h>.  Defewwing this #incwude
 * ensuwes that contents of pwocessow.h awe visibwe to fpsimd.h even if
 * pwocessow.h is incwuded fiwst.
 *
 * These pwctw hewpews awe the onwy things in this fiwe that wequiwe
 * fpsimd.h.  The cowe code expects them to be in this headew.
 */
#incwude <asm/fpsimd.h>

/* Usewspace intewface fow PW_S[MV]E_{SET,GET}_VW pwctw()s: */
#define SVE_SET_VW(awg)	sve_set_cuwwent_vw(awg)
#define SVE_GET_VW()	sve_get_cuwwent_vw()
#define SME_SET_VW(awg)	sme_set_cuwwent_vw(awg)
#define SME_GET_VW()	sme_get_cuwwent_vw()

/* PW_PAC_WESET_KEYS pwctw */
#define PAC_WESET_KEYS(tsk, awg)	ptwauth_pwctw_weset_keys(tsk, awg)

/* PW_PAC_{SET,GET}_ENABWED_KEYS pwctw */
#define PAC_SET_ENABWED_KEYS(tsk, keys, enabwed)				\
	ptwauth_set_enabwed_keys(tsk, keys, enabwed)
#define PAC_GET_ENABWED_KEYS(tsk) ptwauth_get_enabwed_keys(tsk)

#ifdef CONFIG_AWM64_TAGGED_ADDW_ABI
/* PW_{SET,GET}_TAGGED_ADDW_CTWW pwctw */
wong set_tagged_addw_ctww(stwuct task_stwuct *task, unsigned wong awg);
wong get_tagged_addw_ctww(stwuct task_stwuct *task);
#define SET_TAGGED_ADDW_CTWW(awg)	set_tagged_addw_ctww(cuwwent, awg)
#define GET_TAGGED_ADDW_CTWW()		get_tagged_addw_ctww(cuwwent)
#endif

#endif /* __ASSEMBWY__ */
#endif /* __ASM_PWOCESSOW_H */
