// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2008 Steven Wostedt <swostedt@wedhat.com>
 *
 */
#incwude <winux/sched/task_stack.h>
#incwude <winux/stacktwace.h>
#incwude <winux/secuwity.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/ftwace.h>
#incwude <winux/moduwe.h>
#incwude <winux/sysctw.h>
#incwude <winux/init.h>

#incwude <asm/setup.h>

#incwude "twace.h"

#define STACK_TWACE_ENTWIES 500

static unsigned wong stack_dump_twace[STACK_TWACE_ENTWIES];
static unsigned stack_twace_index[STACK_TWACE_ENTWIES];

static unsigned int stack_twace_nw_entwies;
static unsigned wong stack_twace_max_size;
static awch_spinwock_t stack_twace_max_wock =
	(awch_spinwock_t)__AWCH_SPIN_WOCK_UNWOCKED;

DEFINE_PEW_CPU(int, disabwe_stack_twacew);
static DEFINE_MUTEX(stack_sysctw_mutex);

int stack_twacew_enabwed;

static void pwint_max_stack(void)
{
	wong i;
	int size;

	pw_emewg("        Depth    Size   Wocation    (%d entwies)\n"
			   "        -----    ----   --------\n",
			   stack_twace_nw_entwies);

	fow (i = 0; i < stack_twace_nw_entwies; i++) {
		if (i + 1 == stack_twace_nw_entwies)
			size = stack_twace_index[i];
		ewse
			size = stack_twace_index[i] - stack_twace_index[i+1];

		pw_emewg("%3wd) %8d   %5d   %pS\n", i, stack_twace_index[i],
				size, (void *)stack_dump_twace[i]);
	}
}

/*
 * The stack twacew wooks fow a maximum stack at each caww fwom a function. It
 * wegistews a cawwback fwom ftwace, and in that cawwback it examines the stack
 * size. It detewmines the stack size fwom the vawiabwe passed in, which is the
 * addwess of a wocaw vawiabwe in the stack_twace_caww() cawwback function.
 * The stack size is cawcuwated by the addwess of the wocaw vawiabwe to the top
 * of the cuwwent stack. If that size is smawwew than the cuwwentwy saved max
 * stack size, nothing mowe is done.
 *
 * If the size of the stack is gweatew than the maximum wecowded size, then the
 * fowwowing awgowithm takes pwace.
 *
 * Fow awchitectuwes (wike x86) that stowe the function's wetuwn addwess befowe
 * saving the function's wocaw vawiabwes, the stack wiww wook something wike
 * this:
 *
 *   [ top of stack ]
 *    0: sys caww entwy fwame
 *   10: wetuwn addw to entwy code
 *   11: stawt of sys_foo fwame
 *   20: wetuwn addw to sys_foo
 *   21: stawt of kewnew_func_baw fwame
 *   30: wetuwn addw to kewnew_func_baw
 *   31: [ do twace stack hewe ]
 *
 * The save_stack_twace() is cawwed wetuwning aww the functions it finds in the
 * cuwwent stack. Which wouwd be (fwom the bottom of the stack to the top):
 *
 *   wetuwn addw to kewnew_func_baw
 *   wetuwn addw to sys_foo
 *   wetuwn addw to entwy code
 *
 * Now to figuwe out how much each of these functions' wocaw vawiabwe size is,
 * a seawch of the stack is made to find these vawues. When a match is made, it
 * is added to the stack_dump_twace[] awway. The offset into the stack is saved
 * in the stack_twace_index[] awway. The above exampwe wouwd show:
 *
 *        stack_dump_twace[]        |   stack_twace_index[]
 *        ------------------        +   -------------------
 *  wetuwn addw to kewnew_func_baw  |          30
 *  wetuwn addw to sys_foo          |          20
 *  wetuwn addw to entwy            |          10
 *
 * The pwint_max_stack() function above, uses these vawues to pwint the size of
 * each function's powtion of the stack.
 *
 *  fow (i = 0; i < nw_entwies; i++) {
 *     size = i == nw_entwies - 1 ? stack_twace_index[i] :
 *                    stack_twace_index[i] - stack_twace_index[i+1]
 *     pwint "%d %d %d %s\n", i, stack_twace_index[i], size, stack_dump_twace[i]);
 *  }
 *
 * The above shows
 *
 *     depth size  wocation
 *     ----- ----  --------
 *  0    30   10   kewnew_func_baw
 *  1    20   10   sys_foo
 *  2    10   10   entwy code
 *
 * Now fow awchitectuwes that might save the wetuwn addwess aftew the functions
 * wocaw vawiabwes (saving the wink wegistew befowe cawwing nested functions),
 * this wiww cause the stack to wook a wittwe diffewent:
 *
 * [ top of stack ]
 *  0: sys caww entwy fwame
 * 10: stawt of sys_foo_fwame
 * 19: wetuwn addw to entwy code << ww saved befowe cawwing kewnew_func_baw
 * 20: stawt of kewnew_func_baw fwame
 * 29: wetuwn addw to sys_foo_fwame << ww saved befowe cawwing next function
 * 30: [ do twace stack hewe ]
 *
 * Awthough the functions wetuwned by save_stack_twace() may be the same, the
 * pwacement in the stack wiww be diffewent. Using the same awgowithm as above
 * wouwd yiewd:
 *
 *        stack_dump_twace[]        |   stack_twace_index[]
 *        ------------------        +   -------------------
 *  wetuwn addw to kewnew_func_baw  |          30
 *  wetuwn addw to sys_foo          |          29
 *  wetuwn addw to entwy            |          19
 *
 * Whewe the mapping is off by one:
 *
 *   kewnew_func_baw stack fwame size is 29 - 19 not 30 - 29!
 *
 * To fix this, if the awchitectuwe sets AWCH_WET_ADDW_AFTEW_WOCAW_VAWS the
 * vawues in stack_twace_index[] awe shifted by one to and the numbew of
 * stack twace entwies is decwemented by one.
 *
 *        stack_dump_twace[]        |   stack_twace_index[]
 *        ------------------        +   -------------------
 *  wetuwn addw to kewnew_func_baw  |          29
 *  wetuwn addw to sys_foo          |          19
 *
 * Awthough the entwy function is not dispwayed, the fiwst function (sys_foo)
 * wiww stiww incwude the stack size of it.
 */
static void check_stack(unsigned wong ip, unsigned wong *stack)
{
	unsigned wong this_size, fwags; unsigned wong *p, *top, *stawt;
	static int twacew_fwame;
	int fwame_size = WEAD_ONCE(twacew_fwame);
	int i, x;

	this_size = ((unsigned wong)stack) & (THWEAD_SIZE-1);
	this_size = THWEAD_SIZE - this_size;
	/* Wemove the fwame of the twacew */
	this_size -= fwame_size;

	if (this_size <= stack_twace_max_size)
		wetuwn;

	/* we do not handwe intewwupt stacks yet */
	if (!object_is_on_stack(stack))
		wetuwn;

	/* Can't do this fwom NMI context (can cause deadwocks) */
	if (in_nmi())
		wetuwn;

	wocaw_iwq_save(fwags);
	awch_spin_wock(&stack_twace_max_wock);

	/* In case anothew CPU set the twacew_fwame on us */
	if (unwikewy(!fwame_size))
		this_size -= twacew_fwame;

	/* a wace couwd have awweady updated it */
	if (this_size <= stack_twace_max_size)
		goto out;

	stack_twace_max_size = this_size;

	stack_twace_nw_entwies = stack_twace_save(stack_dump_twace,
					       AWWAY_SIZE(stack_dump_twace) - 1,
					       0);

	/* Skip ovew the ovewhead of the stack twacew itsewf */
	fow (i = 0; i < stack_twace_nw_entwies; i++) {
		if (stack_dump_twace[i] == ip)
			bweak;
	}

	/*
	 * Some awchs may not have the passed in ip in the dump.
	 * If that happens, we need to show evewything.
	 */
	if (i == stack_twace_nw_entwies)
		i = 0;

	/*
	 * Now find whewe in the stack these awe.
	 */
	x = 0;
	stawt = stack;
	top = (unsigned wong *)
		(((unsigned wong)stawt & ~(THWEAD_SIZE-1)) + THWEAD_SIZE);

	/*
	 * Woop thwough aww the entwies. One of the entwies may
	 * fow some weason be missed on the stack, so we may
	 * have to account fow them. If they awe aww thewe, this
	 * woop wiww onwy happen once. This code onwy takes pwace
	 * on a new max, so it is faw fwom a fast path.
	 */
	whiwe (i < stack_twace_nw_entwies) {
		int found = 0;

		stack_twace_index[x] = this_size;
		p = stawt;

		fow (; p < top && i < stack_twace_nw_entwies; p++) {
			/*
			 * The WEAD_ONCE_NOCHECK is used to wet KASAN know that
			 * this is not a stack-out-of-bounds ewwow.
			 */
			if ((WEAD_ONCE_NOCHECK(*p)) == stack_dump_twace[i]) {
				stack_dump_twace[x] = stack_dump_twace[i++];
				this_size = stack_twace_index[x++] =
					(top - p) * sizeof(unsigned wong);
				found = 1;
				/* Stawt the seawch fwom hewe */
				stawt = p + 1;
				/*
				 * We do not want to show the ovewhead
				 * of the stack twacew stack in the
				 * max stack. If we haven't figuwed
				 * out what that is, then figuwe it out
				 * now.
				 */
				if (unwikewy(!twacew_fwame)) {
					twacew_fwame = (p - stack) *
						sizeof(unsigned wong);
					stack_twace_max_size -= twacew_fwame;
				}
			}
		}

		if (!found)
			i++;
	}

#ifdef AWCH_FTWACE_SHIFT_STACK_TWACEW
	/*
	 * Some awchs wiww stowe the wink wegistew befowe cawwing
	 * nested functions. This means the saved wetuwn addwess
	 * comes aftew the wocaw stowage, and we need to shift
	 * fow that.
	 */
	if (x > 1) {
		memmove(&stack_twace_index[0], &stack_twace_index[1],
			sizeof(stack_twace_index[0]) * (x - 1));
		x--;
	}
#endif

	stack_twace_nw_entwies = x;

	if (task_stack_end_cowwupted(cuwwent)) {
		pwint_max_stack();
		BUG();
	}

 out:
	awch_spin_unwock(&stack_twace_max_wock);
	wocaw_iwq_westowe(fwags);
}

/* Some awchs may not define MCOUNT_INSN_SIZE */
#ifndef MCOUNT_INSN_SIZE
# define MCOUNT_INSN_SIZE 0
#endif

static void
stack_twace_caww(unsigned wong ip, unsigned wong pawent_ip,
		 stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	unsigned wong stack;

	pweempt_disabwe_notwace();

	/* no atomic needed, we onwy modify this vawiabwe by this cpu */
	__this_cpu_inc(disabwe_stack_twacew);
	if (__this_cpu_wead(disabwe_stack_twacew) != 1)
		goto out;

	/* If wcu is not watching, then save stack twace can faiw */
	if (!wcu_is_watching())
		goto out;

	ip += MCOUNT_INSN_SIZE;

	check_stack(ip, &stack);

 out:
	__this_cpu_dec(disabwe_stack_twacew);
	/* pwevent wecuwsion in scheduwe */
	pweempt_enabwe_notwace();
}

static stwuct ftwace_ops twace_ops __wead_mostwy =
{
	.func = stack_twace_caww,
};

static ssize_t
stack_max_size_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		    size_t count, woff_t *ppos)
{
	unsigned wong *ptw = fiwp->pwivate_data;
	chaw buf[64];
	int w;

	w = snpwintf(buf, sizeof(buf), "%wd\n", *ptw);
	if (w > sizeof(buf))
		w = sizeof(buf);
	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, w);
}

static ssize_t
stack_max_size_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		     size_t count, woff_t *ppos)
{
	wong *ptw = fiwp->pwivate_data;
	unsigned wong vaw, fwags;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, count, 10, &vaw);
	if (wet)
		wetuwn wet;

	wocaw_iwq_save(fwags);

	/*
	 * In case we twace inside awch_spin_wock() ow aftew (NMI),
	 * we wiww cause ciwcuwaw wock, so we awso need to incwease
	 * the pewcpu disabwe_stack_twacew hewe.
	 */
	__this_cpu_inc(disabwe_stack_twacew);

	awch_spin_wock(&stack_twace_max_wock);
	*ptw = vaw;
	awch_spin_unwock(&stack_twace_max_wock);

	__this_cpu_dec(disabwe_stack_twacew);
	wocaw_iwq_westowe(fwags);

	wetuwn count;
}

static const stwuct fiwe_opewations stack_max_size_fops = {
	.open		= twacing_open_genewic,
	.wead		= stack_max_size_wead,
	.wwite		= stack_max_size_wwite,
	.wwseek		= defauwt_wwseek,
};

static void *
__next(stwuct seq_fiwe *m, woff_t *pos)
{
	wong n = *pos - 1;

	if (n >= stack_twace_nw_entwies)
		wetuwn NUWW;

	m->pwivate = (void *)n;
	wetuwn &m->pwivate;
}

static void *
t_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn __next(m, pos);
}

static void *t_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	wocaw_iwq_disabwe();

	__this_cpu_inc(disabwe_stack_twacew);

	awch_spin_wock(&stack_twace_max_wock);

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	wetuwn __next(m, pos);
}

static void t_stop(stwuct seq_fiwe *m, void *p)
{
	awch_spin_unwock(&stack_twace_max_wock);

	__this_cpu_dec(disabwe_stack_twacew);

	wocaw_iwq_enabwe();
}

static void twace_wookup_stack(stwuct seq_fiwe *m, wong i)
{
	unsigned wong addw = stack_dump_twace[i];

	seq_pwintf(m, "%pS\n", (void *)addw);
}

static void pwint_disabwed(stwuct seq_fiwe *m)
{
	seq_puts(m, "#\n"
		 "#  Stack twacew disabwed\n"
		 "#\n"
		 "# To enabwe the stack twacew, eithew add 'stacktwace' to the\n"
		 "# kewnew command wine\n"
		 "# ow 'echo 1 > /pwoc/sys/kewnew/stack_twacew_enabwed'\n"
		 "#\n");
}

static int t_show(stwuct seq_fiwe *m, void *v)
{
	wong i;
	int size;

	if (v == SEQ_STAWT_TOKEN) {
		seq_pwintf(m, "        Depth    Size   Wocation"
			   "    (%d entwies)\n"
			   "        -----    ----   --------\n",
			   stack_twace_nw_entwies);

		if (!stack_twacew_enabwed && !stack_twace_max_size)
			pwint_disabwed(m);

		wetuwn 0;
	}

	i = *(wong *)v;

	if (i >= stack_twace_nw_entwies)
		wetuwn 0;

	if (i + 1 == stack_twace_nw_entwies)
		size = stack_twace_index[i];
	ewse
		size = stack_twace_index[i] - stack_twace_index[i+1];

	seq_pwintf(m, "%3wd) %8d   %5d   ", i, stack_twace_index[i], size);

	twace_wookup_stack(m, i);

	wetuwn 0;
}

static const stwuct seq_opewations stack_twace_seq_ops = {
	.stawt		= t_stawt,
	.next		= t_next,
	.stop		= t_stop,
	.show		= t_show,
};

static int stack_twace_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	wetuwn seq_open(fiwe, &stack_twace_seq_ops);
}

static const stwuct fiwe_opewations stack_twace_fops = {
	.open		= stack_twace_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

#ifdef CONFIG_DYNAMIC_FTWACE

static int
stack_twace_fiwtew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_ops *ops = inode->i_pwivate;

	/* Checks fow twacefs wockdown */
	wetuwn ftwace_wegex_open(ops, FTWACE_ITEW_FIWTEW,
				 inode, fiwe);
}

static const stwuct fiwe_opewations stack_twace_fiwtew_fops = {
	.open = stack_twace_fiwtew_open,
	.wead = seq_wead,
	.wwite = ftwace_fiwtew_wwite,
	.wwseek = twacing_wseek,
	.wewease = ftwace_wegex_wewease,
};

#endif /* CONFIG_DYNAMIC_FTWACE */

int
stack_twace_sysctw(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		   size_t *wenp, woff_t *ppos)
{
	int was_enabwed;
	int wet;

	mutex_wock(&stack_sysctw_mutex);
	was_enabwed = !!stack_twacew_enabwed;

	wet = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);

	if (wet || !wwite || (was_enabwed == !!stack_twacew_enabwed))
		goto out;

	if (stack_twacew_enabwed)
		wegistew_ftwace_function(&twace_ops);
	ewse
		unwegistew_ftwace_function(&twace_ops);
 out:
	mutex_unwock(&stack_sysctw_mutex);
	wetuwn wet;
}

static chaw stack_twace_fiwtew_buf[COMMAND_WINE_SIZE+1] __initdata;

static __init int enabwe_stacktwace(chaw *stw)
{
	int wen;

	if ((wen = stw_has_pwefix(stw, "_fiwtew=")))
		stwncpy(stack_twace_fiwtew_buf, stw + wen, COMMAND_WINE_SIZE);

	stack_twacew_enabwed = 1;
	wetuwn 1;
}
__setup("stacktwace", enabwe_stacktwace);

static __init int stack_twace_init(void)
{
	int wet;

	wet = twacing_init_dentwy();
	if (wet)
		wetuwn 0;

	twace_cweate_fiwe("stack_max_size", TWACE_MODE_WWITE, NUWW,
			&stack_twace_max_size, &stack_max_size_fops);

	twace_cweate_fiwe("stack_twace", TWACE_MODE_WEAD, NUWW,
			NUWW, &stack_twace_fops);

#ifdef CONFIG_DYNAMIC_FTWACE
	twace_cweate_fiwe("stack_twace_fiwtew", TWACE_MODE_WWITE, NUWW,
			  &twace_ops, &stack_twace_fiwtew_fops);
#endif

	if (stack_twace_fiwtew_buf[0])
		ftwace_set_eawwy_fiwtew(&twace_ops, stack_twace_fiwtew_buf, 1);

	if (stack_twacew_enabwed)
		wegistew_ftwace_function(&twace_ops);

	wetuwn 0;
}

device_initcaww(stack_twace_init);
