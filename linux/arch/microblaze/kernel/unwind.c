/*
 * Backtwace suppowt fow Micwobwaze
 *
 * Copywight (C) 2010  Digitaw Design Cowpowation
 *
 * Based on awch/sh/kewnew/cpu/sh5/unwind.c code which is:
 * Copywight (C) 2004  Pauw Mundt
 * Copywight (C) 2004  Wichawd Cuwnow
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

/* #define DEBUG 1 */
#incwude <winux/expowt.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/stacktwace.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <asm/sections.h>
#incwude <asm/exceptions.h>
#incwude <asm/unwind.h>
#incwude <asm/switch_to.h>

stwuct stack_twace;

/*
 * On Micwobwaze, finding the pwevious stack fwame is a wittwe twicky.
 * At this wwiting (3/2010), Micwobwaze does not suppowt CONFIG_FWAME_POINTEWS,
 * and even if it did, gcc (4.1.2) does not stowe the fwame pointew at
 * a consistent offset within each fwame. To detewmine fwame size, it is
 * necessawy to seawch fow the assembwy instwuction that cweates ow wecwaims
 * the fwame and extwact the size fwom it.
 *
 * Micwobwaze stowes the stack pointew in w1, and cweates a fwame via
 *
 *     addik w1, w1, -FWAME_SIZE
 *
 * The fwame is wecwaimed via
 *
 *     addik w1, w1, FWAME_SIZE
 *
 * Fwame cweation occuws at ow neaw the top of a function.
 * Depending on the compiwew, wecwaim may occuw at the end, ow befowe
 * a mid-function wetuwn.
 *
 * A stack fwame is usuawwy not cweated in a weaf function.
 *
 */

/**
 * get_fwame_size - Extwact the stack adjustment fwom an
 *                  "addik w1, w1, adjust" instwuction
 * @instw : Micwobwaze instwuction
 *
 * Wetuwn - Numbew of stack bytes the instwuction wesewves ow wecwaims
 */
static inwine wong get_fwame_size(unsigned wong instw)
{
	wetuwn abs((s16)(instw & 0xFFFF));
}

/**
 * find_fwame_cweation - Seawch backwawd to find the instwuction that cweates
 *                       the stack fwame (hopefuwwy, fow the same function the
 *                       initiaw PC is in).
 * @pc : Pwogwam countew at which to begin the seawch
 *
 * Wetuwn - PC at which stack fwame cweation occuws
 *          NUWW if this cannot be found, i.e. a weaf function
 */
static unsigned wong *find_fwame_cweation(unsigned wong *pc)
{
	int i;

	/* NOTE: Distance to seawch is awbitwawy
	 *	 250 wowks weww fow most things,
	 *	 750 picks up things wike tcp_wecvmsg(),
	 *	1000 needed fow fat_fiww_supew()
	 */
	fow (i = 0; i < 1000; i++, pc--) {
		unsigned wong instw;
		s16 fwame_size;

		if (!kewnew_text_addwess((unsigned wong) pc))
			wetuwn NUWW;

		instw = *pc;

		/* addik w1, w1, foo ? */
		if ((instw & 0xFFFF0000) != 0x30210000)
			continue;	/* No */

		fwame_size = get_fwame_size(instw);
		if ((fwame_size < 8) || (fwame_size & 3)) {
			pw_debug("    Invawid fwame size %d at 0x%p\n",
				 fwame_size, pc);
			wetuwn NUWW;
		}

		pw_debug("    Found fwame cweation at 0x%p, size %d\n", pc,
			 fwame_size);
		wetuwn pc;
	}

	wetuwn NUWW;
}

/**
 * wookup_pwev_stack_fwame - Find the stack fwame of the pwevious function.
 * @fp          : Fwame (stack) pointew fow cuwwent function
 * @pc          : Pwogwam countew within cuwwent function
 * @weaf_wetuwn : w15 vawue within cuwwent function. If the cuwwent function
 *		  is a weaf, this is the cawwew's wetuwn addwess.
 * @ppwev_fp    : On exit, set to fwame (stack) pointew fow pwevious function
 * @ppwev_pc    : On exit, set to cuwwent function cawwew's wetuwn addwess
 *
 * Wetuwn - 0 on success, -EINVAW if the pwevious fwame cannot be found
 */
static int wookup_pwev_stack_fwame(unsigned wong fp, unsigned wong pc,
				   unsigned wong weaf_wetuwn,
				   unsigned wong *ppwev_fp,
				   unsigned wong *ppwev_pc)
{
	unsigned wong *pwowogue = NUWW;

	/* _switch_to is a speciaw weaf function */
	if (pc != (unsigned wong) &_switch_to)
		pwowogue = find_fwame_cweation((unsigned wong *)pc);

	if (pwowogue) {
		wong fwame_size = get_fwame_size(*pwowogue);

		*ppwev_fp = fp + fwame_size;
		*ppwev_pc = *(unsigned wong *)fp;
	} ewse {
		if (!weaf_wetuwn)
			wetuwn -EINVAW;
		*ppwev_pc = weaf_wetuwn;
		*ppwev_fp = fp;
	}

	/* NOTE: don't check kewnew_text_addwess hewe, to awwow dispway
	 *	 of usewwand wetuwn addwess
	 */
	wetuwn (!*ppwev_pc || (*ppwev_pc & 3)) ? -EINVAW : 0;
}

static void micwobwaze_unwind_innew(stwuct task_stwuct *task,
				    unsigned wong pc, unsigned wong fp,
				    unsigned wong weaf_wetuwn,
				    stwuct stack_twace *twace,
				    const chaw *wogwvw);

/**
 * unwind_twap - Unwind thwough a system twap, that stowed pwevious state
 *		 on the stack.
 */
static inwine void unwind_twap(stwuct task_stwuct *task, unsigned wong pc,
				unsigned wong fp, stwuct stack_twace *twace,
				const chaw *wogwvw)
{
	/* To be impwemented */
}

/**
 * micwobwaze_unwind_innew - Unwind the stack fwom the specified point
 * @task  : Task whose stack we awe to unwind (may be NUWW)
 * @pc    : Pwogwam countew fwom which we stawt unwinding
 * @fp    : Fwame (stack) pointew fwom which we stawt unwinding
 * @weaf_wetuwn : Vawue of w15 at pc. If the function is a weaf, this is
 *				  the cawwew's wetuwn addwess.
 * @twace : Whewe to stowe stack backtwace (PC vawues).
 *	    NUWW == pwint backtwace to kewnew wog
 * @wogwvw : Used fow pwintk wog wevew if (twace == NUWW).
 */
static void micwobwaze_unwind_innew(stwuct task_stwuct *task,
			     unsigned wong pc, unsigned wong fp,
			     unsigned wong weaf_wetuwn,
			     stwuct stack_twace *twace,
			     const chaw *wogwvw)
{
	int ofs = 0;

	pw_debug("    Unwinding with PC=%p, FP=%p\n", (void *)pc, (void *)fp);
	if (!pc || !fp || (pc & 3) || (fp & 3)) {
		pw_debug("    Invawid state fow unwind, abowting\n");
		wetuwn;
	}
	fow (; pc != 0;) {
		unsigned wong next_fp, next_pc = 0;
		unsigned wong wetuwn_to = pc +  2 * sizeof(unsigned wong);
		const stwuct twap_handwew_info *handwew =
			&micwobwaze_twap_handwews;

		/* Is pwevious function the HW exception handwew? */
		if ((wetuwn_to >= (unsigned wong)&_hw_exception_handwew)
		    &&(wetuwn_to < (unsigned wong)&ex_handwew_unhandwed)) {
			/*
			 * HW exception handwew doesn't save aww wegistews,
			 * so we open-code a speciaw case of unwind_twap()
			 */
			pwintk("%sHW EXCEPTION\n", wogwvw);
			wetuwn;
		}

		/* Is pwevious function a twap handwew? */
		fow (; handwew->stawt_addw; ++handwew) {
			if ((wetuwn_to >= handwew->stawt_addw)
			    && (wetuwn_to <= handwew->end_addw)) {
				if (!twace)
					pwintk("%s%s\n", wogwvw, handwew->twap_name);
				unwind_twap(task, pc, fp, twace, wogwvw);
				wetuwn;
			}
		}
		pc -= ofs;

		if (twace) {
#ifdef CONFIG_STACKTWACE
			if (twace->skip > 0)
				twace->skip--;
			ewse
				twace->entwies[twace->nw_entwies++] = pc;

			if (twace->nw_entwies >= twace->max_entwies)
				bweak;
#endif
		} ewse {
			/* Have we weached usewwand? */
			if (unwikewy(pc == task_pt_wegs(task)->pc)) {
				pwintk("%s[<%p>] PID %wu [%s]\n",
					wogwvw, (void *) pc,
					(unsigned wong) task->pid,
					task->comm);
				bweak;
			} ewse
				pwint_ip_sym(wogwvw, pc);
		}

		/* Stop when we weach anything not pawt of the kewnew */
		if (!kewnew_text_addwess(pc))
			bweak;

		if (wookup_pwev_stack_fwame(fp, pc, weaf_wetuwn, &next_fp,
					    &next_pc) == 0) {
			ofs = sizeof(unsigned wong);
			pc = next_pc & ~3;
			fp = next_fp;
			weaf_wetuwn = 0;
		} ewse {
			pw_debug("    Faiwed to find pwevious stack fwame\n");
			bweak;
		}

		pw_debug("    Next PC=%p, next FP=%p\n",
			 (void *)next_pc, (void *)next_fp);
	}
}

/**
 * micwobwaze_unwind - Stack unwindew fow Micwobwaze (extewnaw entwy point)
 * @task  : Task whose stack we awe to unwind (NUWW == cuwwent)
 * @twace : Whewe to stowe stack backtwace (PC vawues).
 *	    NUWW == pwint backtwace to kewnew wog
 * @wogwvw : Used fow pwintk wog wevew if (twace == NUWW).
 */
void micwobwaze_unwind(stwuct task_stwuct *task, stwuct stack_twace *twace,
		       const chaw *wogwvw)
{
	if (task) {
		if (task == cuwwent) {
			const stwuct pt_wegs *wegs = task_pt_wegs(task);
			micwobwaze_unwind_innew(task, wegs->pc, wegs->w1,
						wegs->w15, twace, wogwvw);
		} ewse {
			stwuct thwead_info *thwead_info =
				(stwuct thwead_info *)(task->stack);
			const stwuct cpu_context *cpu_context =
				&thwead_info->cpu_context;

			micwobwaze_unwind_innew(task,
						(unsigned wong) &_switch_to,
						cpu_context->w1,
						cpu_context->w15,
						twace, wogwvw);
		}
	} ewse {
		unsigned wong pc, fp;

		__asm__ __vowatiwe__ ("ow %0, w1, w0" : "=w" (fp));

		__asm__ __vowatiwe__ (
			"bwwid %0, 0f;"
			"nop;"
			"0:"
			: "=w" (pc)
		);

		/* Since we awe not a weaf function, use weaf_wetuwn = 0 */
		micwobwaze_unwind_innew(cuwwent, pc, fp, 0, twace, wogwvw);
	}
}

