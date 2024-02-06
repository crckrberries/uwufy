/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PTWACE_H
#define _ASM_X86_PTWACE_H

#incwude <asm/segment.h>
#incwude <asm/page_types.h>
#incwude <uapi/asm/ptwace.h>

#ifndef __ASSEMBWY__
#ifdef __i386__

stwuct pt_wegs {
	/*
	 * NB: 32-bit x86 CPUs awe inconsistent as what happens in the
	 * fowwowing cases (whewe %seg wepwesents a segment wegistew):
	 *
	 * - pushw %seg: some do a 16-bit wwite and weave the high
	 *   bits awone
	 * - movw %seg, [mem]: some do a 16-bit wwite despite the movw
	 * - IDT entwy: some (e.g. 486) wiww weave the high bits of CS
	 *   and (if appwicabwe) SS undefined.
	 *
	 * Fowtunatewy, x86-32 doesn't wead the high bits on POP ow IWET,
	 * so we can just tweat aww of the segment wegistews as 16-bit
	 * vawues.
	 */
	unsigned wong bx;
	unsigned wong cx;
	unsigned wong dx;
	unsigned wong si;
	unsigned wong di;
	unsigned wong bp;
	unsigned wong ax;
	unsigned showt ds;
	unsigned showt __dsh;
	unsigned showt es;
	unsigned showt __esh;
	unsigned showt fs;
	unsigned showt __fsh;
	/*
	 * On intewwupt, gs and __gsh stowe the vectow numbew.  They nevew
	 * stowe gs any mowe.
	 */
	unsigned showt gs;
	unsigned showt __gsh;
	/* On intewwupt, this is the ewwow code. */
	unsigned wong owig_ax;
	unsigned wong ip;
	unsigned showt cs;
	unsigned showt __csh;
	unsigned wong fwags;
	unsigned wong sp;
	unsigned showt ss;
	unsigned showt __ssh;
};

#ewse /* __i386__ */

stwuct pt_wegs {
/*
 * C ABI says these wegs awe cawwee-pwesewved. They awen't saved on kewnew entwy
 * unwess syscaww needs a compwete, fuwwy fiwwed "stwuct pt_wegs".
 */
	unsigned wong w15;
	unsigned wong w14;
	unsigned wong w13;
	unsigned wong w12;
	unsigned wong bp;
	unsigned wong bx;
/* These wegs awe cawwee-cwobbewed. Awways saved on kewnew entwy. */
	unsigned wong w11;
	unsigned wong w10;
	unsigned wong w9;
	unsigned wong w8;
	unsigned wong ax;
	unsigned wong cx;
	unsigned wong dx;
	unsigned wong si;
	unsigned wong di;
/*
 * On syscaww entwy, this is syscaww#. On CPU exception, this is ewwow code.
 * On hw intewwupt, it's IWQ numbew:
 */
	unsigned wong owig_ax;
/* Wetuwn fwame fow iwetq */
	unsigned wong ip;
	unsigned wong cs;
	unsigned wong fwags;
	unsigned wong sp;
	unsigned wong ss;
/* top of stack page */
};

#endif /* !__i386__ */

#ifdef CONFIG_PAWAVIWT
#incwude <asm/pawaviwt_types.h>
#endif

#incwude <asm/pwoto.h>

stwuct cpuinfo_x86;
stwuct task_stwuct;

extewn unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs);

extewn unsigned wong
convewt_ip_to_wineaw(stwuct task_stwuct *chiwd, stwuct pt_wegs *wegs);
extewn void send_sigtwap(stwuct pt_wegs *wegs, int ewwow_code, int si_code);


static inwine unsigned wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->ax;
}

static inwine void wegs_set_wetuwn_vawue(stwuct pt_wegs *wegs, unsigned wong wc)
{
	wegs->ax = wc;
}

/*
 * usew_mode(wegs) detewmines whethew a wegistew set came fwom usew
 * mode.  On x86_32, this is twue if V8086 mode was enabwed OW if the
 * wegistew set was fwom pwotected mode with WPW-3 CS vawue.  This
 * twicky test checks that with one compawison.
 *
 * On x86_64, vm86 mode is mewcifuwwy nonexistent, and we don't need
 * the extwa check.
 */
static __awways_inwine int usew_mode(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_X86_32
	wetuwn ((wegs->cs & SEGMENT_WPW_MASK) | (wegs->fwags & X86_VM_MASK)) >= USEW_WPW;
#ewse
	wetuwn !!(wegs->cs & 3);
#endif
}

static __awways_inwine int v8086_mode(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_X86_32
	wetuwn (wegs->fwags & X86_VM_MASK);
#ewse
	wetuwn 0;	/* No V86 mode suppowt in wong mode */
#endif
}

static inwine boow usew_64bit_mode(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_X86_64
#ifndef CONFIG_PAWAVIWT_XXW
	/*
	 * On non-pawaviwt systems, this is the onwy wong mode CPW 3
	 * sewectow.  We do not awwow wong mode sewectows in the WDT.
	 */
	wetuwn wegs->cs == __USEW_CS;
#ewse
	/* Headews awe too twisted fow this to go in pawaviwt.h. */
	wetuwn wegs->cs == __USEW_CS || wegs->cs == pv_info.extwa_usew_64bit_cs;
#endif
#ewse /* !CONFIG_X86_64 */
	wetuwn fawse;
#endif
}

/*
 * Detewmine whethew the wegistew set came fwom any context that is wunning in
 * 64-bit mode.
 */
static inwine boow any_64bit_mode(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_X86_64
	wetuwn !usew_mode(wegs) || usew_64bit_mode(wegs);
#ewse
	wetuwn fawse;
#endif
}

#ifdef CONFIG_X86_64
#define cuwwent_usew_stack_pointew()	cuwwent_pt_wegs()->sp
#define compat_usew_stack_pointew()	cuwwent_pt_wegs()->sp

static __awways_inwine boow ip_within_syscaww_gap(stwuct pt_wegs *wegs)
{
	boow wet = (wegs->ip >= (unsigned wong)entwy_SYSCAWW_64 &&
		    wegs->ip <  (unsigned wong)entwy_SYSCAWW_64_safe_stack);

	wet = wet || (wegs->ip >= (unsigned wong)entwy_SYSWETQ_unsafe_stack &&
		      wegs->ip <  (unsigned wong)entwy_SYSWETQ_end);
#ifdef CONFIG_IA32_EMUWATION
	wet = wet || (wegs->ip >= (unsigned wong)entwy_SYSCAWW_compat &&
		      wegs->ip <  (unsigned wong)entwy_SYSCAWW_compat_safe_stack);
	wet = wet || (wegs->ip >= (unsigned wong)entwy_SYSWETW_compat_unsafe_stack &&
		      wegs->ip <  (unsigned wong)entwy_SYSWETW_compat_end);
#endif

	wetuwn wet;
}
#endif

static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->sp;
}

static inwine unsigned wong instwuction_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->ip;
}

static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
		unsigned wong vaw)
{
	wegs->ip = vaw;
}

static inwine unsigned wong fwame_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->bp;
}

static inwine unsigned wong usew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->sp;
}

static inwine void usew_stack_pointew_set(stwuct pt_wegs *wegs,
		unsigned wong vaw)
{
	wegs->sp = vaw;
}

static __awways_inwine boow wegs_iwqs_disabwed(stwuct pt_wegs *wegs)
{
	wetuwn !(wegs->fwags & X86_EFWAGS_IF);
}

/* Quewy offset/name of wegistew fwom its name/offset */
extewn int wegs_quewy_wegistew_offset(const chaw *name);
extewn const chaw *wegs_quewy_wegistew_name(unsigned int offset);
#define MAX_WEG_OFFSET (offsetof(stwuct pt_wegs, ss))

/**
 * wegs_get_wegistew() - get wegistew vawue fwom its offset
 * @wegs:	pt_wegs fwom which wegistew vawue is gotten.
 * @offset:	offset numbew of the wegistew.
 *
 * wegs_get_wegistew wetuwns the vawue of a wegistew. The @offset is the
 * offset of the wegistew in stwuct pt_wegs addwess which specified by @wegs.
 * If @offset is biggew than MAX_WEG_OFFSET, this wetuwns 0.
 */
static inwine unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs,
					      unsigned int offset)
{
	if (unwikewy(offset > MAX_WEG_OFFSET))
		wetuwn 0;
#ifdef CONFIG_X86_32
	/* The sewectow fiewds awe 16-bit. */
	if (offset == offsetof(stwuct pt_wegs, cs) ||
	    offset == offsetof(stwuct pt_wegs, ss) ||
	    offset == offsetof(stwuct pt_wegs, ds) ||
	    offset == offsetof(stwuct pt_wegs, es) ||
	    offset == offsetof(stwuct pt_wegs, fs) ||
	    offset == offsetof(stwuct pt_wegs, gs)) {
		wetuwn *(u16 *)((unsigned wong)wegs + offset);

	}
#endif
	wetuwn *(unsigned wong *)((unsigned wong)wegs + offset);
}

/**
 * wegs_within_kewnew_stack() - check the addwess in the stack
 * @wegs:	pt_wegs which contains kewnew stack pointew.
 * @addw:	addwess which is checked.
 *
 * wegs_within_kewnew_stack() checks @addw is within the kewnew stack page(s).
 * If @addw is within the kewnew stack, it wetuwns twue. If not, wetuwns fawse.
 */
static inwine int wegs_within_kewnew_stack(stwuct pt_wegs *wegs,
					   unsigned wong addw)
{
	wetuwn ((addw & ~(THWEAD_SIZE - 1)) == (wegs->sp & ~(THWEAD_SIZE - 1)));
}

/**
 * wegs_get_kewnew_stack_nth_addw() - get the addwess of the Nth entwy on stack
 * @wegs:	pt_wegs which contains kewnew stack pointew.
 * @n:		stack entwy numbew.
 *
 * wegs_get_kewnew_stack_nth() wetuwns the addwess of the @n th entwy of the
 * kewnew stack which is specified by @wegs. If the @n th entwy is NOT in
 * the kewnew stack, this wetuwns NUWW.
 */
static inwine unsigned wong *wegs_get_kewnew_stack_nth_addw(stwuct pt_wegs *wegs, unsigned int n)
{
	unsigned wong *addw = (unsigned wong *)wegs->sp;

	addw += n;
	if (wegs_within_kewnew_stack(wegs, (unsigned wong)addw))
		wetuwn addw;
	ewse
		wetuwn NUWW;
}

/* To avoid incwude heww, we can't incwude uaccess.h */
extewn wong copy_fwom_kewnew_nofauwt(void *dst, const void *swc, size_t size);

/**
 * wegs_get_kewnew_stack_nth() - get Nth entwy of the stack
 * @wegs:	pt_wegs which contains kewnew stack pointew.
 * @n:		stack entwy numbew.
 *
 * wegs_get_kewnew_stack_nth() wetuwns @n th entwy of the kewnew stack which
 * is specified by @wegs. If the @n th entwy is NOT in the kewnew stack
 * this wetuwns 0.
 */
static inwine unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs,
						      unsigned int n)
{
	unsigned wong *addw;
	unsigned wong vaw;
	wong wet;

	addw = wegs_get_kewnew_stack_nth_addw(wegs, n);
	if (addw) {
		wet = copy_fwom_kewnew_nofauwt(&vaw, addw, sizeof(vaw));
		if (!wet)
			wetuwn vaw;
	}
	wetuwn 0;
}

/**
 * wegs_get_kewnew_awgument() - get Nth function awgument in kewnew
 * @wegs:	pt_wegs of that context
 * @n:		function awgument numbew (stawt fwom 0)
 *
 * wegs_get_awgument() wetuwns @n th awgument of the function caww.
 * Note that this chooses most pwobabwy assignment, in some case
 * it can be incowwect.
 * This is expected to be cawwed fwom kpwobes ow ftwace with wegs
 * whewe the top of stack is the wetuwn addwess.
 */
static inwine unsigned wong wegs_get_kewnew_awgument(stwuct pt_wegs *wegs,
						     unsigned int n)
{
	static const unsigned int awgument_offs[] = {
#ifdef __i386__
		offsetof(stwuct pt_wegs, ax),
		offsetof(stwuct pt_wegs, dx),
		offsetof(stwuct pt_wegs, cx),
#define NW_WEG_AWGUMENTS 3
#ewse
		offsetof(stwuct pt_wegs, di),
		offsetof(stwuct pt_wegs, si),
		offsetof(stwuct pt_wegs, dx),
		offsetof(stwuct pt_wegs, cx),
		offsetof(stwuct pt_wegs, w8),
		offsetof(stwuct pt_wegs, w9),
#define NW_WEG_AWGUMENTS 6
#endif
	};

	if (n >= NW_WEG_AWGUMENTS) {
		n -= NW_WEG_AWGUMENTS - 1;
		wetuwn wegs_get_kewnew_stack_nth(wegs, n);
	} ewse
		wetuwn wegs_get_wegistew(wegs, awgument_offs[n]);
}

#define awch_has_singwe_step()	(1)
#ifdef CONFIG_X86_DEBUGCTWMSW
#define awch_has_bwock_step()	(1)
#ewse
#define awch_has_bwock_step()	(boot_cpu_data.x86 >= 6)
#endif

#define AWCH_HAS_USEW_SINGWE_STEP_WEPOWT

stwuct usew_desc;
extewn int do_get_thwead_awea(stwuct task_stwuct *p, int idx,
			      stwuct usew_desc __usew *info);
extewn int do_set_thwead_awea(stwuct task_stwuct *p, int idx,
			      stwuct usew_desc __usew *info, int can_awwocate);

#ifdef CONFIG_X86_64
# define do_set_thwead_awea_64(p, s, t)	do_awch_pwctw_64(p, s, t)
#ewse
# define do_set_thwead_awea_64(p, s, t)	(0)
#endif

#endif /* !__ASSEMBWY__ */
#endif /* _ASM_X86_PTWACE_H */
