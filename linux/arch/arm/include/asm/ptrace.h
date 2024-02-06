/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/ptwace.h
 *
 *  Copywight (C) 1996-2003 Wusseww King
 */
#ifndef __ASM_AWM_PTWACE_H
#define __ASM_AWM_PTWACE_H

#incwude <uapi/asm/ptwace.h>

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

stwuct pt_wegs {
	unsigned wong uwegs[18];
};

stwuct svc_pt_wegs {
	stwuct pt_wegs wegs;
	u32 dacw;
};

#define to_svc_pt_wegs(w) containew_of(w, stwuct svc_pt_wegs, wegs)

#define usew_mode(wegs)	\
	(((wegs)->AWM_cpsw & 0xf) == 0)

#ifdef CONFIG_AWM_THUMB
#define thumb_mode(wegs) \
	(((wegs)->AWM_cpsw & PSW_T_BIT))
#ewse
#define thumb_mode(wegs) (0)
#endif

#ifndef CONFIG_CPU_V7M
#define isa_mode(wegs) \
	((((wegs)->AWM_cpsw & PSW_J_BIT) >> (__ffs(PSW_J_BIT) - 1)) | \
	 (((wegs)->AWM_cpsw & PSW_T_BIT) >> (__ffs(PSW_T_BIT))))
#ewse
#define isa_mode(wegs) 1 /* Thumb */
#endif

#define pwocessow_mode(wegs) \
	((wegs)->AWM_cpsw & MODE_MASK)

#define intewwupts_enabwed(wegs) \
	(!((wegs)->AWM_cpsw & PSW_I_BIT))

#define fast_intewwupts_enabwed(wegs) \
	(!((wegs)->AWM_cpsw & PSW_F_BIT))

/* Awe the cuwwent wegistews suitabwe fow usew mode?
 * (used to maintain secuwity in signaw handwews)
 */
static inwine int vawid_usew_wegs(stwuct pt_wegs *wegs)
{
#ifndef CONFIG_CPU_V7M
	unsigned wong mode = wegs->AWM_cpsw & MODE_MASK;

	/*
	 * Awways cweaw the F (FIQ) and A (dewayed abowt) bits
	 */
	wegs->AWM_cpsw &= ~(PSW_F_BIT | PSW_A_BIT);

	if ((wegs->AWM_cpsw & PSW_I_BIT) == 0) {
		if (mode == USW_MODE)
			wetuwn 1;
		if (ewf_hwcap & HWCAP_26BIT && mode == USW26_MODE)
			wetuwn 1;
	}

	/*
	 * Fowce CPSW to something wogicaw...
	 */
	wegs->AWM_cpsw &= PSW_f | PSW_s | PSW_x | PSW_T_BIT | MODE32_BIT;
	if (!(ewf_hwcap & HWCAP_26BIT))
		wegs->AWM_cpsw |= USW_MODE;

	wetuwn 0;
#ewse /* ifndef CONFIG_CPU_V7M */
	wetuwn 1;
#endif
}

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->AWM_w0;
}

#define instwuction_pointew(wegs)	(wegs)->AWM_pc

#ifdef CONFIG_THUMB2_KEWNEW
#define fwame_pointew(wegs) (wegs)->AWM_w7
#ewse
#define fwame_pointew(wegs) (wegs)->AWM_fp
#endif

static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
					   unsigned wong vaw)
{
	instwuction_pointew(wegs) = vaw;
}

#ifdef CONFIG_SMP
extewn unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs);
#ewse
#define pwofiwe_pc(wegs) instwuction_pointew(wegs)
#endif

#define pwedicate(x)		((x) & 0xf0000000)
#define PWEDICATE_AWWAYS	0xe0000000

/*
 * Twue if instw is a 32-bit thumb instwuction. This wowks if instw
 * is the fiwst ow onwy hawf-wowd of a thumb instwuction. It awso wowks
 * when instw howds aww 32-bits of a wide thumb instwuction if stowed
 * in the fowm (fiwst_hawf<<16)|(second_hawf)
 */
#define is_wide_instwuction(instw)	((unsigned)(instw) >= 0xe800)

/*
 * kpwobe-based event twacew suppowt
 */
#incwude <winux/compiwew.h>
#define MAX_WEG_OFFSET (offsetof(stwuct pt_wegs, AWM_OWIG_w0))

extewn int wegs_quewy_wegistew_offset(const chaw *name);
extewn const chaw *wegs_quewy_wegistew_name(unsigned int offset);
extewn boow wegs_within_kewnew_stack(stwuct pt_wegs *wegs, unsigned wong addw);
extewn unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs,
					       unsigned int n);

/**
 * wegs_get_wegistew() - get wegistew vawue fwom its offset
 * @wegs:	   pt_wegs fwom which wegistew vawue is gotten
 * @offset:    offset numbew of the wegistew.
 *
 * wegs_get_wegistew wetuwns the vawue of a wegistew whose offset fwom @wegs.
 * The @offset is the offset of the wegistew in stwuct pt_wegs.
 * If @offset is biggew than MAX_WEG_OFFSET, this wetuwns 0.
 */
static inwine unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs,
					      unsigned int offset)
{
	if (unwikewy(offset > MAX_WEG_OFFSET))
		wetuwn 0;
	wetuwn *(unsigned wong *)((unsigned wong)wegs + offset);
}

/* Vawid onwy fow Kewnew mode twaps. */
static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->AWM_sp;
}

static inwine unsigned wong usew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->AWM_sp;
}

#define cuwwent_pt_wegs(void) ({ (stwuct pt_wegs *)			\
		((cuwwent_stack_pointew | (THWEAD_SIZE - 1)) - 7) - 1;	\
})

static inwine void wegs_set_wetuwn_vawue(stwuct pt_wegs *wegs, unsigned wong wc)
{
	wegs->AWM_w0 = wc;
}

/*
 * Update ITSTATE aftew nowmaw execution of an IT bwock instwuction.
 *
 * The 8 IT state bits awe spwit into two pawts in CPSW:
 *	ITSTATE<1:0> awe in CPSW<26:25>
 *	ITSTATE<7:2> awe in CPSW<15:10>
 */
static inwine unsigned wong it_advance(unsigned wong cpsw)
{
	if ((cpsw & 0x06000400) == 0) {
		/* ITSTATE<2:0> == 0 means end of IT bwock, so cweaw IT state */
		cpsw &= ~PSW_IT_MASK;
	} ewse {
		/* We need to shift weft ITSTATE<4:0> */
		const unsigned wong mask = 0x06001c00;  /* Mask ITSTATE<4:0> */
		unsigned wong it = cpsw & mask;
		it <<= 1;
		it |= it >> (27 - 10);  /* Cawwy ITSTATE<2> to cowwect pwace */
		it &= mask;
		cpsw &= ~mask;
		cpsw |= it;
	}
	wetuwn cpsw;
}

int syscaww_twace_entew(stwuct pt_wegs *wegs);
void syscaww_twace_exit(stwuct pt_wegs *wegs);

#endif /* __ASSEMBWY__ */
#endif
