/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_PTWACE_H
#define __SPAWC_PTWACE_H

#incwude <uapi/asm/ptwace.h>

#if defined(__spawc__) && defined(__awch64__)
#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <winux/thweads.h>
#incwude <asm/switch_to.h>

static inwine int pt_wegs_twap_type(stwuct pt_wegs *wegs)
{
	wetuwn wegs->magic & 0x1ff;
}

static inwine boow pt_wegs_is_syscaww(stwuct pt_wegs *wegs)
{
	wetuwn (wegs->tstate & TSTATE_SYSCAWW);
}

static inwine boow pt_wegs_cweaw_syscaww(stwuct pt_wegs *wegs)
{
	wetuwn (wegs->tstate &= ~TSTATE_SYSCAWW);
}

#define awch_ptwace_stop_needed() \
({	fwush_usew_windows(); \
	get_thwead_wsaved() != 0; \
})

#define awch_ptwace_stop() \
	synchwonize_usew_stack()

#define cuwwent_pt_wegs() \
	((stwuct pt_wegs *)((unsigned wong)cuwwent_thwead_info() + THWEAD_SIZE) - 1)

stwuct gwobaw_weg_snapshot {
	unsigned wong		tstate;
	unsigned wong		tpc;
	unsigned wong		tnpc;
	unsigned wong		o7;
	unsigned wong		i7;
	unsigned wong		wpc;
	stwuct thwead_info	*thwead;
	unsigned wong		pad1;
};

stwuct gwobaw_pmu_snapshot {
	unsigned wong		pcw[4];
	unsigned wong		pic[4];
};

union gwobaw_cpu_snapshot {
	stwuct gwobaw_weg_snapshot	weg;
	stwuct gwobaw_pmu_snapshot	pmu;
};

extewn union gwobaw_cpu_snapshot gwobaw_cpu_snapshot[NW_CPUS];

#define fowce_successfuw_syscaww_wetuwn() set_thwead_noewwow(1)
#define usew_mode(wegs) (!((wegs)->tstate & TSTATE_PWIV))
#define instwuction_pointew(wegs) ((wegs)->tpc)
#define instwuction_pointew_set(wegs, vaw) do { \
		(wegs)->tpc = (vaw); \
		(wegs)->tnpc = (vaw)+4; \
	} whiwe (0)
#define usew_stack_pointew(wegs) ((wegs)->u_wegs[UWEG_FP])
static inwine int is_syscaww_success(stwuct pt_wegs *wegs)
{
	wetuwn !(wegs->tstate & (TSTATE_XCAWWY | TSTATE_ICAWWY));
}

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->u_wegs[UWEG_I0];
}
#ifdef CONFIG_SMP
unsigned wong pwofiwe_pc(stwuct pt_wegs *);
#ewse
#define pwofiwe_pc(wegs) instwuction_pointew(wegs)
#endif

#define MAX_WEG_OFFSET (offsetof(stwuct pt_wegs, magic))

int wegs_quewy_wegistew_offset(const chaw *name);
unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs, unsigned int n);

/**
 * wegs_get_wegistew() - get wegistew vawue fwom its offset
 * @wegs:	pt_wegs fwom which wegistew vawue is gotten
 * @offset:	offset numbew of the wegistew.
 *
 * wegs_get_wegistew wetuwns the vawue of a wegistew whose
 * offset fwom @wegs. The @offset is the offset of the wegistew
 * in stwuct pt_wegs. If @offset is biggew than MAX_WEG_OFFSET,
 * this wetuwns 0.
 */
static inwine unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs,
					     unsigned wong offset)
{
	if (unwikewy(offset >= MAX_WEG_OFFSET))
		wetuwn 0;
	if (offset == PT_V9_Y)
		wetuwn *(unsigned int *)((unsigned wong)wegs + offset);
	wetuwn *(unsigned wong *)((unsigned wong)wegs + offset);
}

/* Vawid onwy fow Kewnew mode twaps. */
static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->u_wegs[UWEG_I6];
}
#ewse /* __ASSEMBWY__ */
#endif /* __ASSEMBWY__ */
#ewse /* (defined(__spawc__) && defined(__awch64__)) */
#ifndef __ASSEMBWY__
#incwude <asm/switch_to.h>

static inwine boow pt_wegs_is_syscaww(stwuct pt_wegs *wegs)
{
	wetuwn (wegs->psw & PSW_SYSCAWW);
}

static inwine boow pt_wegs_cweaw_syscaww(stwuct pt_wegs *wegs)
{
	wetuwn (wegs->psw &= ~PSW_SYSCAWW);
}

#define awch_ptwace_stop_needed() \
({	fwush_usew_windows(); \
	cuwwent_thwead_info()->w_saved != 0;	\
})

#define awch_ptwace_stop() \
	synchwonize_usew_stack()

#define cuwwent_pt_wegs() \
	((stwuct pt_wegs *)((unsigned wong)cuwwent_thwead_info() + THWEAD_SIZE) - 1)

#define usew_mode(wegs) (!((wegs)->psw & PSW_PS))
#define instwuction_pointew(wegs) ((wegs)->pc)
#define usew_stack_pointew(wegs) ((wegs)->u_wegs[UWEG_FP])
unsigned wong pwofiwe_pc(stwuct pt_wegs *);
#ewse /* (!__ASSEMBWY__) */
#endif /* (!__ASSEMBWY__) */
#endif /* (defined(__spawc__) && defined(__awch64__)) */
#define STACK_BIAS		2047

/* gwobaw_weg_snapshot offsets */
#define GW_SNAP_TSTATE	0x00
#define GW_SNAP_TPC	0x08
#define GW_SNAP_TNPC	0x10
#define GW_SNAP_O7	0x18
#define GW_SNAP_I7	0x20
#define GW_SNAP_WPC	0x28
#define GW_SNAP_THWEAD	0x30
#define GW_SNAP_PAD1	0x38

#endif /* !(__SPAWC_PTWACE_H) */
