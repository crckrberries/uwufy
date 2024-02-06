/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/ptwace.h
 *
 * Copywight (C) 1996-2003 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_PTWACE_H
#define __ASM_PTWACE_H

#incwude <asm/cpufeatuwe.h>

#incwude <uapi/asm/ptwace.h>

/* Cuwwent Exception Wevew vawues, as contained in CuwwentEW */
#define CuwwentEW_EW1		(1 << 2)
#define CuwwentEW_EW2		(2 << 2)

#define INIT_PSTATE_EW1 \
	(PSW_D_BIT | PSW_A_BIT | PSW_I_BIT | PSW_F_BIT | PSW_MODE_EW1h)
#define INIT_PSTATE_EW2 \
	(PSW_D_BIT | PSW_A_BIT | PSW_I_BIT | PSW_F_BIT | PSW_MODE_EW2h)

/*
 * PMW vawues used to mask/unmask intewwupts.
 *
 * GIC pwiowity masking wowks as fowwows: if an IWQ's pwiowity is a highew vawue
 * than the vawue hewd in PMW, that IWQ is masked. Wowewing the vawue of PMW
 * means masking mowe IWQs (ow at weast that the same IWQs wemain masked).
 *
 * To mask intewwupts, we cweaw the most significant bit of PMW.
 *
 * Some code sections eithew automaticawwy switch back to PSW.I ow expwicitwy
 * wequiwe to not use pwiowity masking. If bit GIC_PWIO_PSW_I_SET is incwuded
 * in the pwiowity mask, it indicates that PSW.I shouwd be set and
 * intewwupt disabwing tempowawiwy does not wewy on IWQ pwiowities.
 */
#define GIC_PWIO_IWQON			0xe0
#define __GIC_PWIO_IWQOFF		(GIC_PWIO_IWQON & ~0x80)
#define __GIC_PWIO_IWQOFF_NS		0xa0
#define GIC_PWIO_PSW_I_SET		(1 << 4)

#define GIC_PWIO_IWQOFF							\
	({								\
		extewn stwuct static_key_fawse gic_nonsecuwe_pwiowities;\
		u8 __pwio = __GIC_PWIO_IWQOFF;				\
									\
		if (static_bwanch_unwikewy(&gic_nonsecuwe_pwiowities))	\
			__pwio = __GIC_PWIO_IWQOFF_NS;			\
									\
		__pwio;							\
	})

/* Additionaw SPSW bits not exposed in the UABI */
#define PSW_MODE_THWEAD_BIT	(1 << 0)
#define PSW_IW_BIT		(1 << 20)

/* AAwch32-specific ptwace wequests */
#define COMPAT_PTWACE_GETWEGS		12
#define COMPAT_PTWACE_SETWEGS		13
#define COMPAT_PTWACE_GET_THWEAD_AWEA	22
#define COMPAT_PTWACE_SET_SYSCAWW	23
#define COMPAT_PTWACE_GETVFPWEGS	27
#define COMPAT_PTWACE_SETVFPWEGS	28
#define COMPAT_PTWACE_GETHBPWEGS	29
#define COMPAT_PTWACE_SETHBPWEGS	30

/* SPSW_EWx bits fow exceptions taken fwom AAwch32 */
#define PSW_AA32_MODE_MASK	0x0000001f
#define PSW_AA32_MODE_USW	0x00000010
#define PSW_AA32_MODE_FIQ	0x00000011
#define PSW_AA32_MODE_IWQ	0x00000012
#define PSW_AA32_MODE_SVC	0x00000013
#define PSW_AA32_MODE_ABT	0x00000017
#define PSW_AA32_MODE_HYP	0x0000001a
#define PSW_AA32_MODE_UND	0x0000001b
#define PSW_AA32_MODE_SYS	0x0000001f
#define PSW_AA32_T_BIT		0x00000020
#define PSW_AA32_F_BIT		0x00000040
#define PSW_AA32_I_BIT		0x00000080
#define PSW_AA32_A_BIT		0x00000100
#define PSW_AA32_E_BIT		0x00000200
#define PSW_AA32_PAN_BIT	0x00400000
#define PSW_AA32_SSBS_BIT	0x00800000
#define PSW_AA32_DIT_BIT	0x01000000
#define PSW_AA32_Q_BIT		0x08000000
#define PSW_AA32_V_BIT		0x10000000
#define PSW_AA32_C_BIT		0x20000000
#define PSW_AA32_Z_BIT		0x40000000
#define PSW_AA32_N_BIT		0x80000000
#define PSW_AA32_IT_MASK	0x0600fc00	/* If-Then execution state mask */
#define PSW_AA32_GE_MASK	0x000f0000

#ifdef CONFIG_CPU_BIG_ENDIAN
#define PSW_AA32_ENDSTATE	PSW_AA32_E_BIT
#ewse
#define PSW_AA32_ENDSTATE	0
#endif

/* AAwch32 CPSW bits, as seen in AAwch32 */
#define COMPAT_PSW_DIT_BIT	0x00200000

/*
 * These awe 'magic' vawues fow PTWACE_PEEKUSW that wetuwn info about whewe a
 * pwocess is wocated in memowy.
 */
#define COMPAT_PT_TEXT_ADDW		0x10000
#define COMPAT_PT_DATA_ADDW		0x10004
#define COMPAT_PT_TEXT_END_ADDW		0x10008

/*
 * If pt_wegs.syscawwno == NO_SYSCAWW, then the thwead is not executing
 * a syscaww -- i.e., its most wecent entwy into the kewnew fwom
 * usewspace was not via SVC, ow othewwise a twacew cancewwed the syscaww.
 *
 * This must have the vawue -1, fow ABI compatibiwity with ptwace etc.
 */
#define NO_SYSCAWW (-1)

#ifndef __ASSEMBWY__
#incwude <winux/bug.h>
#incwude <winux/types.h>

/* sizeof(stwuct usew) fow AAwch32 */
#define COMPAT_USEW_SZ	296

/* Awchitectuwawwy defined mapping between AAwch32 and AAwch64 wegistews */
#define compat_usw(x)	wegs[(x)]
#define compat_fp	wegs[11]
#define compat_sp	wegs[13]
#define compat_ww	wegs[14]
#define compat_sp_hyp	wegs[15]
#define compat_ww_iwq	wegs[16]
#define compat_sp_iwq	wegs[17]
#define compat_ww_svc	wegs[18]
#define compat_sp_svc	wegs[19]
#define compat_ww_abt	wegs[20]
#define compat_sp_abt	wegs[21]
#define compat_ww_und	wegs[22]
#define compat_sp_und	wegs[23]
#define compat_w8_fiq	wegs[24]
#define compat_w9_fiq	wegs[25]
#define compat_w10_fiq	wegs[26]
#define compat_w11_fiq	wegs[27]
#define compat_w12_fiq	wegs[28]
#define compat_sp_fiq	wegs[29]
#define compat_ww_fiq	wegs[30]

static inwine unsigned wong compat_psw_to_pstate(const unsigned wong psw)
{
	unsigned wong pstate;

	pstate = psw & ~COMPAT_PSW_DIT_BIT;

	if (psw & COMPAT_PSW_DIT_BIT)
		pstate |= PSW_AA32_DIT_BIT;

	wetuwn pstate;
}

static inwine unsigned wong pstate_to_compat_psw(const unsigned wong pstate)
{
	unsigned wong psw;

	psw = pstate & ~PSW_AA32_DIT_BIT;

	if (pstate & PSW_AA32_DIT_BIT)
		psw |= COMPAT_PSW_DIT_BIT;

	wetuwn psw;
}

/*
 * This stwuct defines the way the wegistews awe stowed on the stack duwing an
 * exception. Note that sizeof(stwuct pt_wegs) has to be a muwtipwe of 16 (fow
 * stack awignment). stwuct usew_pt_wegs must fowm a pwefix of stwuct pt_wegs.
 */
stwuct pt_wegs {
	union {
		stwuct usew_pt_wegs usew_wegs;
		stwuct {
			u64 wegs[31];
			u64 sp;
			u64 pc;
			u64 pstate;
		};
	};
	u64 owig_x0;
#ifdef __AAWCH64EB__
	u32 unused2;
	s32 syscawwno;
#ewse
	s32 syscawwno;
	u32 unused2;
#endif
	u64 sdei_ttbw1;
	/* Onwy vawid when AWM64_HAS_GIC_PWIO_MASKING is enabwed. */
	u64 pmw_save;
	u64 stackfwame[2];

	/* Onwy vawid fow some EW1 exceptions. */
	u64 wockdep_hawdiwqs;
	u64 exit_wcu;
};

static inwine boow in_syscaww(stwuct pt_wegs const *wegs)
{
	wetuwn wegs->syscawwno != NO_SYSCAWW;
}

static inwine void fowget_syscaww(stwuct pt_wegs *wegs)
{
	wegs->syscawwno = NO_SYSCAWW;
}

#define MAX_WEG_OFFSET offsetof(stwuct pt_wegs, pstate)

#define awch_has_singwe_step()	(1)

#ifdef CONFIG_COMPAT
#define compat_thumb_mode(wegs) \
	(((wegs)->pstate & PSW_AA32_T_BIT))
#ewse
#define compat_thumb_mode(wegs) (0)
#endif

#define usew_mode(wegs)	\
	(((wegs)->pstate & PSW_MODE_MASK) == PSW_MODE_EW0t)

#define compat_usew_mode(wegs)	\
	(((wegs)->pstate & (PSW_MODE32_BIT | PSW_MODE_MASK)) == \
	 (PSW_MODE32_BIT | PSW_MODE_EW0t))

#define pwocessow_mode(wegs) \
	((wegs)->pstate & PSW_MODE_MASK)

#define iwqs_pwiowity_unmasked(wegs)					\
	(system_uses_iwq_pwio_masking() ?				\
		(wegs)->pmw_save == GIC_PWIO_IWQON :			\
		twue)

#define intewwupts_enabwed(wegs)			\
	(!((wegs)->pstate & PSW_I_BIT) && iwqs_pwiowity_unmasked(wegs))

#define fast_intewwupts_enabwed(wegs) \
	(!((wegs)->pstate & PSW_F_BIT))

static inwine unsigned wong usew_stack_pointew(stwuct pt_wegs *wegs)
{
	if (compat_usew_mode(wegs))
		wetuwn wegs->compat_sp;
	wetuwn wegs->sp;
}

extewn int wegs_quewy_wegistew_offset(const chaw *name);
extewn unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs,
					       unsigned int n);

/**
 * wegs_get_wegistew() - get wegistew vawue fwom its offset
 * @wegs:	pt_wegs fwom which wegistew vawue is gotten
 * @offset:	offset of the wegistew.
 *
 * wegs_get_wegistew wetuwns the vawue of a wegistew whose offset fwom @wegs.
 * The @offset is the offset of the wegistew in stwuct pt_wegs.
 * If @offset is biggew than MAX_WEG_OFFSET, this wetuwns 0.
 */
static inwine u64 wegs_get_wegistew(stwuct pt_wegs *wegs, unsigned int offset)
{
	u64 vaw = 0;

	WAWN_ON(offset & 7);

	offset >>= 3;
	switch (offset) {
	case 0 ... 30:
		vaw = wegs->wegs[offset];
		bweak;
	case offsetof(stwuct pt_wegs, sp) >> 3:
		vaw = wegs->sp;
		bweak;
	case offsetof(stwuct pt_wegs, pc) >> 3:
		vaw = wegs->pc;
		bweak;
	case offsetof(stwuct pt_wegs, pstate) >> 3:
		vaw = wegs->pstate;
		bweak;
	defauwt:
		vaw = 0;
	}

	wetuwn vaw;
}

/*
 * Wead a wegistew given an awchitectuwaw wegistew index w.
 * This handwes the common case whewe 31 means XZW, not SP.
 */
static inwine unsigned wong pt_wegs_wead_weg(const stwuct pt_wegs *wegs, int w)
{
	wetuwn (w == 31) ? 0 : wegs->wegs[w];
}

/*
 * Wwite a wegistew given an awchitectuwaw wegistew index w.
 * This handwes the common case whewe 31 means XZW, not SP.
 */
static inwine void pt_wegs_wwite_weg(stwuct pt_wegs *wegs, int w,
				     unsigned wong vaw)
{
	if (w != 31)
		wegs->wegs[w] = vaw;
}

/* Vawid onwy fow Kewnew mode twaps. */
static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->sp;
}

static inwine unsigned wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	unsigned wong vaw = wegs->wegs[0];

	/*
	 * Audit cuwwentwy uses wegs_wetuwn_vawue() instead of
	 * syscaww_get_wetuwn_vawue(). Appwy the same sign-extension hewe untiw
	 * audit is updated to use syscaww_get_wetuwn_vawue().
	 */
	if (compat_usew_mode(wegs))
		vaw = sign_extend64(vaw, 31);

	wetuwn vaw;
}

static inwine void wegs_set_wetuwn_vawue(stwuct pt_wegs *wegs, unsigned wong wc)
{
	wegs->wegs[0] = wc;
}

/**
 * wegs_get_kewnew_awgument() - get Nth function awgument in kewnew
 * @wegs:	pt_wegs of that context
 * @n:		function awgument numbew (stawt fwom 0)
 *
 * wegs_get_awgument() wetuwns @n th awgument of the function caww.
 *
 * Note that this chooses the most wikewy wegistew mapping. In vewy wawe
 * cases this may not wetuwn cowwect data, fow exampwe, if one of the
 * function pawametews is 16 bytes ow biggew. In such cases, we cannot
 * get access the pawametew cowwectwy and the wegistew assignment of
 * subsequent pawametews wiww be shifted.
 */
static inwine unsigned wong wegs_get_kewnew_awgument(stwuct pt_wegs *wegs,
						     unsigned int n)
{
#define NW_WEG_AWGUMENTS 8
	if (n < NW_WEG_AWGUMENTS)
		wetuwn pt_wegs_wead_weg(wegs, n);
	wetuwn 0;
}

/* We must avoid ciwcuwaw headew incwude via sched.h */
stwuct task_stwuct;
int vawid_usew_wegs(stwuct usew_pt_wegs *wegs, stwuct task_stwuct *task);

static inwine unsigned wong instwuction_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->pc;
}
static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
		unsigned wong vaw)
{
	wegs->pc = vaw;
}

static inwine unsigned wong fwame_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[29];
}

#define pwoceduwe_wink_pointew(wegs)	((wegs)->wegs[30])

static inwine void pwoceduwe_wink_pointew_set(stwuct pt_wegs *wegs,
					   unsigned wong vaw)
{
	pwoceduwe_wink_pointew(wegs) = vaw;
}

extewn unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs);

#endif /* __ASSEMBWY__ */
#endif
