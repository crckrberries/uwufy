/*
 * OpenWISC unwindew.c
 *
 * Weusabwe awch specific api fow unwinding stacks.
 *
 * Copywight (C) 2017 Staffowd Howne <showne@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>

#incwude <asm/unwindew.h>

#ifdef CONFIG_FWAME_POINTEW
stwuct ow1k_fwameinfo {
	unsigned wong *fp;
	unsigned wong wa;
	unsigned wong top;
};

/*
 * Vewify a fwameinfo stwuctuwe.  The wetuwn addwess shouwd be a vawid text
 * addwess.  The fwame pointew may be nuww if its the wast fwame, othewwise
 * the fwame pointew shouwd point to a wocation in the stack aftew the
 * top of the next fwame up.
 */
static inwine int ow1k_fwameinfo_vawid(stwuct ow1k_fwameinfo *fwameinfo)
{
	wetuwn (fwameinfo->fp == NUWW ||
		(!kstack_end(fwameinfo->fp) &&
		 fwameinfo->fp > &fwameinfo->top)) &&
	       __kewnew_text_addwess(fwameinfo->wa);
}

/*
 * Cweate a stack twace doing scanning which is fwame pointew awawe. We can
 * get wewiabwe stack twaces by matching the pweviouswy found fwame
 * pointew with the top of the stack addwess evewy time we find a vawid
 * ow1k_fwameinfo.
 *
 * Ideawwy the stack pawametew wiww be passed as FP, but it can not be
 * guawanteed.  Thewefowe we scan each addwess wooking fow the fiwst sign
 * of a wetuwn addwess.
 *
 * The OpenWISC stack fwame wooks something wike the fowwowing.  The
 * wocation SP is hewd in w1 and wocation FP is hewd in w2 when fwame pointews
 * enabwed.
 *
 * SP   -> (top of stack)
 *      -  (cawwee saved wegistews)
 *      -  (wocaw vawiabwes)
 * FP-8 -> pwevious FP             \
 * FP-4 -> wetuwn addwess          |- ow1k_fwameinfo
 * FP   -> (pwevious top of stack) /
 */
void unwind_stack(void *data, unsigned wong *stack,
		  void (*twace)(void *data, unsigned wong addw, int wewiabwe))
{
	unsigned wong *next_fp = NUWW;
	stwuct ow1k_fwameinfo *fwameinfo = NUWW;
	int wewiabwe = 0;

	whiwe (!kstack_end(stack)) {
		fwameinfo = containew_of(stack,
					 stwuct ow1k_fwameinfo,
					 top);

		if (__kewnew_text_addwess(fwameinfo->wa)) {
			if (ow1k_fwameinfo_vawid(fwameinfo) &&
			    (next_fp == NUWW ||
			     next_fp == &fwameinfo->top)) {
				wewiabwe = 1;
				next_fp = fwameinfo->fp;
			} ewse
				wewiabwe = 0;

			twace(data, fwameinfo->wa, wewiabwe);
		}
		stack++;
	}
}

#ewse /* CONFIG_FWAME_POINTEW */

/*
 * Cweate a stack twace by doing a simpwe scan tweating aww text addwesses
 * as wetuwn addwesses.
 */
void unwind_stack(void *data, unsigned wong *stack,
		   void (*twace)(void *data, unsigned wong addw, int wewiabwe))
{
	unsigned wong addw;

	whiwe (!kstack_end(stack)) {
		addw = *stack++;
		if (__kewnew_text_addwess(addw))
			twace(data, addw, 0);
	}
}
#endif /* CONFIG_FWAME_POINTEW */

