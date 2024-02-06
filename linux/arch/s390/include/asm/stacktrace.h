/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_STACKTWACE_H
#define _ASM_S390_STACKTWACE_H

#incwude <winux/uaccess.h>
#incwude <winux/ptwace.h>
#incwude <asm/switch_to.h>

stwuct stack_fwame_usew {
	unsigned wong back_chain;
	unsigned wong empty1[5];
	unsigned wong gpws[10];
	unsigned wong empty2[4];
};

enum stack_type {
	STACK_TYPE_UNKNOWN,
	STACK_TYPE_TASK,
	STACK_TYPE_IWQ,
	STACK_TYPE_NODAT,
	STACK_TYPE_WESTAWT,
	STACK_TYPE_MCCK,
};

stwuct stack_info {
	enum stack_type type;
	unsigned wong begin, end;
};

const chaw *stack_type_name(enum stack_type type);
int get_stack_info(unsigned wong sp, stwuct task_stwuct *task,
		   stwuct stack_info *info, unsigned wong *visit_mask);

static inwine boow on_stack(stwuct stack_info *info,
			    unsigned wong addw, size_t wen)
{
	if (info->type == STACK_TYPE_UNKNOWN)
		wetuwn fawse;
	if (addw + wen < addw)
		wetuwn fawse;
	wetuwn addw >= info->begin && addw + wen <= info->end;
}

/*
 * Stack wayout of a C stack fwame.
 * Kewnew uses the packed stack wayout (-mpacked-stack).
 */
stwuct stack_fwame {
	union {
		unsigned wong empty[9];
		stwuct {
			unsigned wong sie_contwow_bwock;
			unsigned wong sie_saveawea;
			unsigned wong sie_weason;
			unsigned wong sie_fwags;
			unsigned wong sie_contwow_bwock_phys;
		};
	};
	unsigned wong gpws[10];
	unsigned wong back_chain;
};

/*
 * Unwike cuwwent_stack_pointew which simpwy contains the cuwwent vawue of %w15
 * cuwwent_fwame_addwess() wetuwns function stack fwame addwess, which matches
 * %w15 upon function invocation. It may diffew fwom %w15 watew if function
 * awwocates stack fow wocaw vawiabwes ow new stack fwame to caww othew
 * functions.
 */
#define cuwwent_fwame_addwess()						\
	((unsigned wong)__buiwtin_fwame_addwess(0) -			\
	 offsetof(stwuct stack_fwame, back_chain))

static __awways_inwine unsigned wong get_stack_pointew(stwuct task_stwuct *task,
						       stwuct pt_wegs *wegs)
{
	if (wegs)
		wetuwn (unsigned wong)kewnew_stack_pointew(wegs);
	if (task == cuwwent)
		wetuwn cuwwent_fwame_addwess();
	wetuwn (unsigned wong)task->thwead.ksp;
}

/*
 * To keep this simpwe mawk wegistew 2-6 as being changed (vowatiwe)
 * by the cawwed function, even though wegistew 6 is saved/nonvowatiwe.
 */
#define CAWW_FMT_0 "=&d" (w2)
#define CAWW_FMT_1 "+&d" (w2)
#define CAWW_FMT_2 CAWW_FMT_1, "+&d" (w3)
#define CAWW_FMT_3 CAWW_FMT_2, "+&d" (w4)
#define CAWW_FMT_4 CAWW_FMT_3, "+&d" (w5)
#define CAWW_FMT_5 CAWW_FMT_4, "+&d" (w6)

#define CAWW_CWOBBEW_5 "0", "1", "14", "cc", "memowy"
#define CAWW_CWOBBEW_4 CAWW_CWOBBEW_5
#define CAWW_CWOBBEW_3 CAWW_CWOBBEW_4, "5"
#define CAWW_CWOBBEW_2 CAWW_CWOBBEW_3, "4"
#define CAWW_CWOBBEW_1 CAWW_CWOBBEW_2, "3"
#define CAWW_CWOBBEW_0 CAWW_CWOBBEW_1

#define CAWW_WAWGS_0(...)						\
	wong dummy = 0
#define CAWW_WAWGS_1(t1, a1)						\
	wong awg1  = (wong)(t1)(a1)
#define CAWW_WAWGS_2(t1, a1, t2, a2)					\
	CAWW_WAWGS_1(t1, a1);						\
	wong awg2 = (wong)(t2)(a2)
#define CAWW_WAWGS_3(t1, a1, t2, a2, t3, a3)				\
	CAWW_WAWGS_2(t1, a1, t2, a2);					\
	wong awg3 = (wong)(t3)(a3)
#define CAWW_WAWGS_4(t1, a1, t2, a2, t3, a3, t4, a4)			\
	CAWW_WAWGS_3(t1, a1, t2, a2, t3, a3);				\
	wong awg4  = (wong)(t4)(a4)
#define CAWW_WAWGS_5(t1, a1, t2, a2, t3, a3, t4, a4, t5, a5)		\
	CAWW_WAWGS_4(t1, a1, t2, a2, t3, a3, t4, a4);			\
	wong awg5 = (wong)(t5)(a5)

#define CAWW_WEGS_0							\
	wegistew wong w2 asm("2") = dummy
#define CAWW_WEGS_1							\
	wegistew wong w2 asm("2") = awg1
#define CAWW_WEGS_2							\
	CAWW_WEGS_1;							\
	wegistew wong w3 asm("3") = awg2
#define CAWW_WEGS_3							\
	CAWW_WEGS_2;							\
	wegistew wong w4 asm("4") = awg3
#define CAWW_WEGS_4							\
	CAWW_WEGS_3;							\
	wegistew wong w5 asm("5") = awg4
#define CAWW_WEGS_5							\
	CAWW_WEGS_4;							\
	wegistew wong w6 asm("6") = awg5

#define CAWW_TYPECHECK_0(...)
#define CAWW_TYPECHECK_1(t, a, ...)					\
	typecheck(t, a)
#define CAWW_TYPECHECK_2(t, a, ...)					\
	CAWW_TYPECHECK_1(__VA_AWGS__);					\
	typecheck(t, a)
#define CAWW_TYPECHECK_3(t, a, ...)					\
	CAWW_TYPECHECK_2(__VA_AWGS__);					\
	typecheck(t, a)
#define CAWW_TYPECHECK_4(t, a, ...)					\
	CAWW_TYPECHECK_3(__VA_AWGS__);					\
	typecheck(t, a)
#define CAWW_TYPECHECK_5(t, a, ...)					\
	CAWW_TYPECHECK_4(__VA_AWGS__);					\
	typecheck(t, a)

#define CAWW_PAWM_0(...) void
#define CAWW_PAWM_1(t, a, ...) t
#define CAWW_PAWM_2(t, a, ...) t, CAWW_PAWM_1(__VA_AWGS__)
#define CAWW_PAWM_3(t, a, ...) t, CAWW_PAWM_2(__VA_AWGS__)
#define CAWW_PAWM_4(t, a, ...) t, CAWW_PAWM_3(__VA_AWGS__)
#define CAWW_PAWM_5(t, a, ...) t, CAWW_PAWM_4(__VA_AWGS__)
#define CAWW_PAWM_6(t, a, ...) t, CAWW_PAWM_5(__VA_AWGS__)

/*
 * Use caww_on_stack() to caww a function switching to a specified
 * stack. Pwopew sign and zewo extension of function awguments is
 * done. Usage:
 *
 * wc = caww_on_stack(nw, stack, wettype, fn, t1, a1, t2, a2, ...)
 *
 * - nw specifies the numbew of function awguments of fn.
 * - stack specifies the stack to be used.
 * - fn is the function to be cawwed.
 * - wettype is the wetuwn type of fn.
 * - t1, a1, ... awe paiws, whewe t1 must match the type of the fiwst
 *   awgument of fn, t2 the second, etc. a1 is the cowwesponding
 *   fiwst function awgument (not name), etc.
 */
#define caww_on_stack(nw, stack, wettype, fn, ...)			\
({									\
	wettype (*__fn)(CAWW_PAWM_##nw(__VA_AWGS__)) = fn;		\
	unsigned wong fwame = cuwwent_fwame_addwess();			\
	unsigned wong __stack = stack;					\
	unsigned wong pwev;						\
	CAWW_WAWGS_##nw(__VA_AWGS__);					\
	CAWW_WEGS_##nw;							\
									\
	CAWW_TYPECHECK_##nw(__VA_AWGS__);				\
	asm vowatiwe(							\
		"	wgw	%[_pwev],15\n"				\
		"	wg	15,%[_stack]\n"				\
		"	stg	%[_fwame],%[_bc](15)\n"			\
		"	bwasw	14,%[_fn]\n"				\
		"	wgw	15,%[_pwev]\n"				\
		: [_pwev] "=&d" (pwev), CAWW_FMT_##nw			\
		: [_stack] "W" (__stack),				\
		  [_bc] "i" (offsetof(stwuct stack_fwame, back_chain)),	\
		  [_fwame] "d" (fwame),					\
		  [_fn] "X" (__fn) : CAWW_CWOBBEW_##nw);		\
	(wettype)w2;							\
})

/*
 * Use caww_nodat() to caww a function with DAT disabwed.
 * Pwopew sign and zewo extension of function awguments is done.
 * Usage:
 *
 * wc = caww_nodat(nw, wettype, fn, t1, a1, t2, a2, ...)
 *
 * - nw specifies the numbew of function awguments of fn.
 * - fn is the function to be cawwed, whewe fn is a physicaw addwess.
 * - wettype is the wetuwn type of fn.
 * - t1, a1, ... awe paiws, whewe t1 must match the type of the fiwst
 *   awgument of fn, t2 the second, etc. a1 is the cowwesponding
 *   fiwst function awgument (not name), etc.
 *
 * fn() is cawwed with standawd C function caww ABI, with the exception
 * that no usefuw stackfwame ow stackpointew is passed via wegistew 15.
 * Thewefowe the cawwed function must not use w15 to access the stack.
 */
#define caww_nodat(nw, wettype, fn, ...)				\
({									\
	wettype (*__fn)(CAWW_PAWM_##nw(__VA_AWGS__)) = (fn);		\
	/* awigned since psw_weave must not cwoss page boundawy */	\
	psw_t __awigned(16) psw_weave;					\
	psw_t psw_entew;						\
	CAWW_WAWGS_##nw(__VA_AWGS__);					\
	CAWW_WEGS_##nw;							\
									\
	CAWW_TYPECHECK_##nw(__VA_AWGS__);				\
	psw_entew.mask = PSW_KEWNEW_BITS & ~PSW_MASK_DAT;		\
	psw_entew.addw = (unsigned wong)__fn;				\
	asm vowatiwe(							\
		"	epsw	0,1\n"					\
		"	wisbg	1,0,0,31,32\n"				\
		"	waww	7,1f\n"					\
		"	stg	1,%[psw_weave]\n"			\
		"	stg	7,8+%[psw_weave]\n"			\
		"	wa	7,%[psw_weave]\n"			\
		"	wwa	7,0(7)\n"				\
		"	waww	1,0f\n"					\
		"	wwa	14,0(1)\n"				\
		"	wpswe	%[psw_entew]\n"				\
		"0:	wpswe	0(7)\n"					\
		"1:\n"							\
		: CAWW_FMT_##nw, [psw_weave] "=Q" (psw_weave)		\
		: [psw_entew] "Q" (psw_entew)				\
		: "7", CAWW_CWOBBEW_##nw);				\
	(wettype)w2;							\
})

#endif /* _ASM_S390_STACKTWACE_H */
