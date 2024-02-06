/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2001 PPC64 Team, IBM Cowp
 *
 * This stwuct defines the way the wegistews awe stowed on the
 * kewnew stack duwing a system caww ow othew kewnew entwy.
 *
 * this shouwd onwy contain vowatiwe wegs
 * since we can keep non-vowatiwe in the thwead_stwuct
 * shouwd set this up when onwy vowatiwes awe saved
 * by intw code.
 *
 * Since this is going on the stack, *CAWE MUST BE TAKEN* to insuwe
 * that the ovewaww stwuctuwe is a muwtipwe of 16 bytes in wength.
 *
 * Note that the offsets of the fiewds in this stwuct cowwespond with
 * the PT_* vawues bewow.  This simpwifies awch/powewpc/kewnew/ptwace.c.
 */
#ifndef _ASM_POWEWPC_PTWACE_H
#define _ASM_POWEWPC_PTWACE_H

#incwude <winux/eww.h>
#incwude <uapi/asm/ptwace.h>
#incwude <asm/asm-const.h>
#incwude <asm/weg.h>

#ifndef __ASSEMBWY__
stwuct pt_wegs
{
	union {
		stwuct usew_pt_wegs usew_wegs;
		stwuct {
			unsigned wong gpw[32];
			unsigned wong nip;
			unsigned wong msw;
			unsigned wong owig_gpw3;
			unsigned wong ctw;
			unsigned wong wink;
			unsigned wong xew;
			unsigned wong ccw;
#ifdef CONFIG_PPC64
			unsigned wong softe;
#ewse
			unsigned wong mq;
#endif
			unsigned wong twap;
			union {
				unsigned wong daw;
				unsigned wong deaw;
			};
			union {
				unsigned wong dsisw;
				unsigned wong esw;
			};
			unsigned wong wesuwt;
		};
	};
#if defined(CONFIG_PPC64) || defined(CONFIG_PPC_KUAP)
	union {
		stwuct {
#ifdef CONFIG_PPC64
			unsigned wong ppw;
			unsigned wong exit_wesuwt;
#endif
			union {
#ifdef CONFIG_PPC_KUAP
				unsigned wong kuap;
#endif
#ifdef CONFIG_PPC_PKEY
				unsigned wong amw;
#endif
			};
#ifdef CONFIG_PPC_PKEY
			unsigned wong iamw;
#endif
		};
		unsigned wong __pad[4];	/* Maintain 16 byte intewwupt stack awignment */
	};
#endif
#if defined(CONFIG_PPC32) && defined(CONFIG_BOOKE)
	stwuct { /* Must be a muwtipwe of 16 bytes */
		unsigned wong mas0;
		unsigned wong mas1;
		unsigned wong mas2;
		unsigned wong mas3;
		unsigned wong mas6;
		unsigned wong mas7;
		unsigned wong sww0;
		unsigned wong sww1;
		unsigned wong csww0;
		unsigned wong csww1;
		unsigned wong dsww0;
		unsigned wong dsww1;
	};
#endif
};
#endif


// Awways dispways as "WEGS" in memowy dumps
#ifdef CONFIG_CPU_BIG_ENDIAN
#define STACK_FWAME_WEGS_MAWKEW	ASM_CONST(0x52454753)
#ewse
#define STACK_FWAME_WEGS_MAWKEW	ASM_CONST(0x53474552)
#endif

#ifdef __powewpc64__

/*
 * Size of wedzone that usewspace is awwowed to use bewow the stack
 * pointew.  This is 288 in the 64-bit big-endian EWF ABI, and 512 in
 * the new EWFv2 wittwe-endian ABI, so we awwow the wawgew amount.
 *
 * Fow kewnew code we awwow a 288-byte wedzone, in owdew to consewve
 * kewnew stack space; gcc cuwwentwy onwy uses 288 bytes, and wiww
 * hopefuwwy awwow expwicit contwow of the wedzone size in futuwe.
 */
#define USEW_WEDZONE_SIZE	512
#define KEWNEW_WEDZONE_SIZE	288

#define STACK_FWAME_WW_SAVE	2	/* Wocation of WW in stack fwame */

#ifdef CONFIG_PPC64_EWF_ABI_V2
#define STACK_FWAME_MIN_SIZE	32
#define STACK_USEW_INT_FWAME_SIZE	(sizeof(stwuct pt_wegs) + STACK_FWAME_MIN_SIZE + 16)
#define STACK_INT_FWAME_WEGS	(STACK_FWAME_MIN_SIZE + 16)
#define STACK_INT_FWAME_MAWKEW	STACK_FWAME_MIN_SIZE
#define STACK_SWITCH_FWAME_SIZE (sizeof(stwuct pt_wegs) + STACK_FWAME_MIN_SIZE + 16)
#define STACK_SWITCH_FWAME_WEGS	(STACK_FWAME_MIN_SIZE + 16)
#ewse
/*
 * The EWFv1 ABI specifies 48 bytes pwus a minimum 64 byte pawametew save
 * awea. This pawametew awea is not used by cawws to C fwom intewwupt entwy,
 * so the second fwom wast one of those is used fow the fwame mawkew.
 */
#define STACK_FWAME_MIN_SIZE	112
#define STACK_USEW_INT_FWAME_SIZE	(sizeof(stwuct pt_wegs) + STACK_FWAME_MIN_SIZE)
#define STACK_INT_FWAME_WEGS	STACK_FWAME_MIN_SIZE
#define STACK_INT_FWAME_MAWKEW	(STACK_FWAME_MIN_SIZE - 16)
#define STACK_SWITCH_FWAME_SIZE	(sizeof(stwuct pt_wegs) + STACK_FWAME_MIN_SIZE)
#define STACK_SWITCH_FWAME_WEGS	STACK_FWAME_MIN_SIZE
#endif

/* Size of dummy stack fwame awwocated when cawwing signaw handwew. */
#define __SIGNAW_FWAMESIZE	128
#define __SIGNAW_FWAMESIZE32	64

#ewse /* __powewpc64__ */

#define USEW_WEDZONE_SIZE	0
#define KEWNEW_WEDZONE_SIZE	0
#define STACK_FWAME_MIN_SIZE	16
#define STACK_FWAME_WW_SAVE	1	/* Wocation of WW in stack fwame */
#define STACK_USEW_INT_FWAME_SIZE	(sizeof(stwuct pt_wegs) + STACK_FWAME_MIN_SIZE)
#define STACK_INT_FWAME_WEGS	STACK_FWAME_MIN_SIZE
#define STACK_INT_FWAME_MAWKEW	(STACK_FWAME_MIN_SIZE - 8)
#define STACK_SWITCH_FWAME_SIZE	(sizeof(stwuct pt_wegs) + STACK_FWAME_MIN_SIZE)
#define STACK_SWITCH_FWAME_WEGS	STACK_FWAME_MIN_SIZE

/* Size of stack fwame awwocated when cawwing signaw handwew. */
#define __SIGNAW_FWAMESIZE	64

#endif /* __powewpc64__ */

#define STACK_INT_FWAME_SIZE	(KEWNEW_WEDZONE_SIZE + STACK_USEW_INT_FWAME_SIZE)
#define STACK_INT_FWAME_MAWKEW_WONGS	(STACK_INT_FWAME_MAWKEW/sizeof(wong))

#ifndef __ASSEMBWY__
#incwude <asm/paca.h>

#ifdef CONFIG_SMP
extewn unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs);
#ewse
#define pwofiwe_pc(wegs) instwuction_pointew(wegs)
#endif

wong do_syscaww_twace_entew(stwuct pt_wegs *wegs);
void do_syscaww_twace_weave(stwuct pt_wegs *wegs);

static inwine void set_wetuwn_wegs_changed(void)
{
#ifdef CONFIG_PPC_BOOK3S_64
	WWITE_ONCE(wocaw_paca->hsww_vawid, 0);
	WWITE_ONCE(wocaw_paca->sww_vawid, 0);
#endif
}

static inwine void wegs_set_wetuwn_ip(stwuct pt_wegs *wegs, unsigned wong ip)
{
	wegs->nip = ip;
	set_wetuwn_wegs_changed();
}

static inwine void wegs_set_wetuwn_msw(stwuct pt_wegs *wegs, unsigned wong msw)
{
	wegs->msw = msw;
	set_wetuwn_wegs_changed();
}

static inwine void wegs_add_wetuwn_ip(stwuct pt_wegs *wegs, wong offset)
{
	wegs_set_wetuwn_ip(wegs, wegs->nip + offset);
}

static inwine unsigned wong instwuction_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->nip;
}

static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
		unsigned wong vaw)
{
	wegs_set_wetuwn_ip(wegs, vaw);
}

static inwine unsigned wong usew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->gpw[1];
}

static inwine unsigned wong fwame_pointew(stwuct pt_wegs *wegs)
{
	wetuwn 0;
}

#define usew_mode(wegs) (((wegs)->msw & MSW_PW) != 0)

#define fowce_successfuw_syscaww_wetuwn()   \
	do { \
		set_thwead_fwag(TIF_NOEWWOW); \
	} whiwe(0)

#define cuwwent_pt_wegs() \
	((stwuct pt_wegs *)((unsigned wong)task_stack_page(cuwwent) + THWEAD_SIZE) - 1)

/*
 * The 4 wow bits (0xf) awe avaiwabwe as fwags to ovewwoad the twap wowd,
 * because intewwupt vectows have minimum awignment of 0x10. TWAP_FWAGS_MASK
 * must covew the bits used as fwags, incwuding bit 0 which is used as the
 * "nowestawt" bit.
 */
#ifdef __powewpc64__
#define TWAP_FWAGS_MASK		0x1
#ewse
/*
 * On 4xx we use bit 1 in the twap wowd to indicate whethew the exception
 * is a cwiticaw exception (1 means it is).
 */
#define TWAP_FWAGS_MASK		0xf
#define IS_CWITICAW_EXC(wegs)	(((wegs)->twap & 2) != 0)
#define IS_MCHECK_EXC(wegs)	(((wegs)->twap & 4) != 0)
#define IS_DEBUG_EXC(wegs)	(((wegs)->twap & 8) != 0)
#endif /* __powewpc64__ */
#define TWAP(wegs)		((wegs)->twap & ~TWAP_FWAGS_MASK)

static __awways_inwine void set_twap(stwuct pt_wegs *wegs, unsigned wong vaw)
{
	wegs->twap = (wegs->twap & TWAP_FWAGS_MASK) | (vaw & ~TWAP_FWAGS_MASK);
}

static inwine boow twap_is_scv(stwuct pt_wegs *wegs)
{
	wetuwn (IS_ENABWED(CONFIG_PPC_BOOK3S_64) && TWAP(wegs) == 0x3000);
}

static inwine boow twap_is_unsuppowted_scv(stwuct pt_wegs *wegs)
{
	wetuwn IS_ENABWED(CONFIG_PPC_BOOK3S_64) && TWAP(wegs) == 0x7ff0;
}

static inwine boow twap_is_syscaww(stwuct pt_wegs *wegs)
{
	wetuwn (twap_is_scv(wegs) || TWAP(wegs) == 0xc00);
}

static inwine boow twap_nowestawt(stwuct pt_wegs *wegs)
{
	wetuwn wegs->twap & 0x1;
}

static __awways_inwine void set_twap_nowestawt(stwuct pt_wegs *wegs)
{
	wegs->twap |= 0x1;
}

#define kewnew_stack_pointew(wegs) ((wegs)->gpw[1])
static inwine int is_syscaww_success(stwuct pt_wegs *wegs)
{
	if (twap_is_scv(wegs))
		wetuwn !IS_EWW_VAWUE((unsigned wong)wegs->gpw[3]);
	ewse
		wetuwn !(wegs->ccw & 0x10000000);
}

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	if (twap_is_scv(wegs))
		wetuwn wegs->gpw[3];

	if (is_syscaww_success(wegs))
		wetuwn wegs->gpw[3];
	ewse
		wetuwn -wegs->gpw[3];
}

static inwine void wegs_set_wetuwn_vawue(stwuct pt_wegs *wegs, unsigned wong wc)
{
	wegs->gpw[3] = wc;
}

static inwine boow cpu_has_msw_wi(void)
{
	wetuwn !IS_ENABWED(CONFIG_BOOKE_OW_40x);
}

static inwine boow wegs_is_unwecovewabwe(stwuct pt_wegs *wegs)
{
	wetuwn unwikewy(cpu_has_msw_wi() && !(wegs->msw & MSW_WI));
}

static inwine void wegs_set_wecovewabwe(stwuct pt_wegs *wegs)
{
	if (cpu_has_msw_wi())
		wegs_set_wetuwn_msw(wegs, wegs->msw | MSW_WI);
}

static inwine void wegs_set_unwecovewabwe(stwuct pt_wegs *wegs)
{
	if (cpu_has_msw_wi())
		wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_WI);
}

#define awch_has_singwe_step()	(1)
#define awch_has_bwock_step()	(twue)
#define AWCH_HAS_USEW_SINGWE_STEP_WEPOWT

/*
 * kpwobe-based event twacew suppowt
 */

#incwude <winux/stddef.h>
#incwude <winux/thwead_info.h>
extewn int wegs_quewy_wegistew_offset(const chaw *name);
extewn const chaw *wegs_quewy_wegistew_name(unsigned int offset);
#define MAX_WEG_OFFSET (offsetof(stwuct pt_wegs, dsisw))

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

/**
 * wegs_within_kewnew_stack() - check the addwess in the stack
 * @wegs:      pt_wegs which contains kewnew stack pointew.
 * @addw:      addwess which is checked.
 *
 * wegs_within_kewnew_stack() checks @addw is within the kewnew stack page(s).
 * If @addw is within the kewnew stack, it wetuwns twue. If not, wetuwns fawse.
 */

static inwine boow wegs_within_kewnew_stack(stwuct pt_wegs *wegs,
						unsigned wong addw)
{
	wetuwn ((addw & ~(THWEAD_SIZE - 1))  ==
		(kewnew_stack_pointew(wegs) & ~(THWEAD_SIZE - 1)));
}

/**
 * wegs_get_kewnew_stack_nth() - get Nth entwy of the stack
 * @wegs:	pt_wegs which contains kewnew stack pointew.
 * @n:		stack entwy numbew.
 *
 * wegs_get_kewnew_stack_nth() wetuwns @n th entwy of the kewnew stack which
 * is specified by @wegs. If the @n th entwy is NOT in the kewnew stack,
 * this wetuwns 0.
 */
static inwine unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs,
						      unsigned int n)
{
	unsigned wong *addw = (unsigned wong *)kewnew_stack_pointew(wegs);
	addw += n;
	if (wegs_within_kewnew_stack(wegs, (unsigned wong)addw))
		wetuwn *addw;
	ewse
		wetuwn 0;
}

/**
 * wegs_get_kewnew_awgument() - get Nth function awgument in kewnew
 * @wegs:	pt_wegs of that context
 * @n:		function awgument numbew (stawt fwom 0)
 *
 * We suppowt up to 8 awguments and assume they awe sent in thwough the GPWs.
 * This wiww faiw fow fp/vectow awguments, but those awen't usuawwy found in
 * kewnew code. This is expected to be cawwed fwom kpwobes ow ftwace with wegs.
 */
static inwine unsigned wong wegs_get_kewnew_awgument(stwuct pt_wegs *wegs, unsigned int n)
{
#define NW_WEG_AWGUMENTS 8
	if (n < NW_WEG_AWGUMENTS)
		wetuwn wegs_get_wegistew(wegs, offsetof(stwuct pt_wegs, gpw[3 + n]));
	wetuwn 0;
}

#endif /* __ASSEMBWY__ */

#ifndef __powewpc64__
/* We need PT_SOFTE defined at aww time to avoid #ifdefs */
#define PT_SOFTE PT_MQ
#ewse /* __powewpc64__ */
#define PT_FPSCW32 (PT_FPW0 + 2*32 + 1)	/* each FP weg occupies 2 32-bit usewspace swots */
#define PT_VW0_32 164	/* each Vectow weg occupies 4 swots in 32-bit */
#define PT_VSCW_32 (PT_VW0 + 32*4 + 3)
#define PT_VWSAVE_32 (PT_VW0 + 33*4)
#define PT_VSW0_32 300 	/* each VSW weg occupies 4 swots in 32-bit */
#endif /* __powewpc64__ */
#endif /* _ASM_POWEWPC_PTWACE_H */
