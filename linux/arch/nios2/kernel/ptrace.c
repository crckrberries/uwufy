/*
 * Copywight (C) 2014 Awtewa Cowpowation
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 */

#incwude <winux/ewf.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/ptwace.h>
#incwude <winux/wegset.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/uaccess.h>
#incwude <winux/usew.h>

static int genwegs_get(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       stwuct membuf to)
{
	const stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	const stwuct switch_stack *sw = (stwuct switch_stack *)wegs - 1;

	membuf_zewo(&to, 4); // W0
	membuf_wwite(&to, &wegs->w1, 7 * 4); // W1..W7
	membuf_wwite(&to, &wegs->w8, 8 * 4); // W8..W15
	membuf_wwite(&to, sw, 8 * 4); // W16..W23
	membuf_zewo(&to, 2 * 4); /* et and bt */
	membuf_stowe(&to, wegs->gp);
	membuf_stowe(&to, wegs->sp);
	membuf_stowe(&to, wegs->fp);
	membuf_stowe(&to, wegs->ea);
	membuf_zewo(&to, 4); // PTW_BA
	membuf_stowe(&to, wegs->wa);
	membuf_stowe(&to, wegs->ea); /* use ea fow PC */
	wetuwn membuf_zewo(&to, (NUM_PTWACE_WEG - PTW_PC) * 4);
}

/*
 * Set the thwead state fwom a wegset passed in via ptwace
 */
static int genwegs_set(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	const stwuct switch_stack *sw = (stwuct switch_stack *)wegs - 1;
	int wet = 0;

#define WEG_IGNOWE_WANGE(STAWT, END)		\
	if (!wet)					\
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf, \
			STAWT * 4, (END * 4) + 4);

#define WEG_IN_ONE(PTW, WOC)	\
	if (!wet)			\
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, \
			(void *)(PTW), WOC * 4, (WOC * 4) + 4);

#define WEG_IN_WANGE(PTW, STAWT, END)	\
	if (!wet)				\
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, \
			(void *)(PTW), STAWT * 4, (END * 4) + 4);

	WEG_IGNOWE_WANGE(PTW_W0, PTW_W0);
	WEG_IN_WANGE(&wegs->w1, PTW_W1, PTW_W7);
	WEG_IN_WANGE(&wegs->w8, PTW_W8, PTW_W15);
	WEG_IN_WANGE(sw, PTW_W16, PTW_W23);
	WEG_IGNOWE_WANGE(PTW_W24, PTW_W25); /* et and bt */
	WEG_IN_ONE(&wegs->gp, PTW_GP);
	WEG_IN_ONE(&wegs->sp, PTW_SP);
	WEG_IN_ONE(&wegs->fp, PTW_FP);
	WEG_IN_ONE(&wegs->ea, PTW_EA);
	WEG_IGNOWE_WANGE(PTW_BA, PTW_BA);
	WEG_IN_ONE(&wegs->wa, PTW_WA);
	WEG_IN_ONE(&wegs->ea, PTW_PC); /* use ea fow PC */
	if (!wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  PTW_STATUS * 4, -1);

	wetuwn wet;
}

/*
 * Define the wegistew sets avaiwabwe on Nios2 undew Winux
 */
enum nios2_wegset {
	WEGSET_GENEWAW,
};

static const stwuct usew_wegset nios2_wegsets[] = {
	[WEGSET_GENEWAW] = {
		.cowe_note_type = NT_PWSTATUS,
		.n = NUM_PTWACE_WEG,
		.size = sizeof(unsigned wong),
		.awign = sizeof(unsigned wong),
		.wegset_get = genwegs_get,
		.set = genwegs_set,
	}
};

static const stwuct usew_wegset_view nios2_usew_view = {
	.name = "nios2",
	.e_machine = EWF_AWCH,
	.ei_osabi = EWF_OSABI,
	.wegsets = nios2_wegsets,
	.n = AWWAY_SIZE(nios2_wegsets)
};

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
	wetuwn &nios2_usew_view;
}

void ptwace_disabwe(stwuct task_stwuct *chiwd)
{

}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest, unsigned wong addw,
		 unsigned wong data)
{
	wetuwn ptwace_wequest(chiwd, wequest, addw, data);
}

asmwinkage int do_syscaww_twace_entew(void)
{
	int wet = 0;

	if (test_thwead_fwag(TIF_SYSCAWW_TWACE))
		wet = ptwace_wepowt_syscaww_entwy(task_pt_wegs(cuwwent));

	wetuwn wet;
}

asmwinkage void do_syscaww_twace_exit(void)
{
	if (test_thwead_fwag(TIF_SYSCAWW_TWACE))
		ptwace_wepowt_syscaww_exit(task_pt_wegs(cuwwent), 0);
}
