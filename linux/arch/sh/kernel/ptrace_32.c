// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SupewH pwocess twacing
 *
 * Copywight (C) 1999, 2000  Kaz Kojima & Niibe Yutaka
 * Copywight (C) 2002 - 2009  Pauw Mundt
 *
 * Audit suppowt by Yuichi Nakamuwa <ynakam@hitachisoft.jp>
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/usew.h>
#incwude <winux/secuwity.h>
#incwude <winux/signaw.h>
#incwude <winux/io.h>
#incwude <winux/audit.h>
#incwude <winux/seccomp.h>
#incwude <winux/ewf.h>
#incwude <winux/wegset.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/uaccess.h>
#incwude <asm/pwocessow.h>
#incwude <asm/mmu_context.h>
#incwude <asm/syscawws.h>
#incwude <asm/fpu.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/syscawws.h>

/*
 * This woutine wiww get a wowd off of the pwocess kewnew stack.
 */
static inwine int get_stack_wong(stwuct task_stwuct *task, int offset)
{
	unsigned chaw *stack;

	stack = (unsigned chaw *)task_pt_wegs(task);
	stack += offset;
	wetuwn (*((int *)stack));
}

/*
 * This woutine wiww put a wowd on the pwocess kewnew stack.
 */
static inwine int put_stack_wong(stwuct task_stwuct *task, int offset,
				 unsigned wong data)
{
	unsigned chaw *stack;

	stack = (unsigned chaw *)task_pt_wegs(task);
	stack += offset;
	*(unsigned wong *) stack = data;
	wetuwn 0;
}

void ptwace_twiggewed(stwuct pewf_event *bp,
		      stwuct pewf_sampwe_data *data, stwuct pt_wegs *wegs)
{
	stwuct pewf_event_attw attw;

	/*
	 * Disabwe the bweakpoint wequest hewe since ptwace has defined a
	 * one-shot behaviouw fow bweakpoint exceptions.
	 */
	attw = bp->attw;
	attw.disabwed = twue;
	modify_usew_hw_bweakpoint(bp, &attw);
}

static int set_singwe_step(stwuct task_stwuct *tsk, unsigned wong addw)
{
	stwuct thwead_stwuct *thwead = &tsk->thwead;
	stwuct pewf_event *bp;
	stwuct pewf_event_attw attw;

	bp = thwead->ptwace_bps[0];
	if (!bp) {
		ptwace_bweakpoint_init(&attw);

		attw.bp_addw = addw;
		attw.bp_wen = HW_BWEAKPOINT_WEN_2;
		attw.bp_type = HW_BWEAKPOINT_W;

		bp = wegistew_usew_hw_bweakpoint(&attw, ptwace_twiggewed,
						 NUWW, tsk);
		if (IS_EWW(bp))
			wetuwn PTW_EWW(bp);

		thwead->ptwace_bps[0] = bp;
	} ewse {
		int eww;

		attw = bp->attw;
		attw.bp_addw = addw;
		/* weenabwe bweakpoint */
		attw.disabwed = fawse;
		eww = modify_usew_hw_bweakpoint(bp, &attw);
		if (unwikewy(eww))
			wetuwn eww;
	}

	wetuwn 0;
}

void usew_enabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	unsigned wong pc = get_stack_wong(chiwd, offsetof(stwuct pt_wegs, pc));

	set_tsk_thwead_fwag(chiwd, TIF_SINGWESTEP);

	set_singwe_step(chiwd, pc);
}

void usew_disabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	cweaw_tsk_thwead_fwag(chiwd, TIF_SINGWESTEP);
}

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Make suwe singwe step bits etc awe not set.
 */
void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	usew_disabwe_singwe_step(chiwd);
}

static int genwegs_get(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       stwuct membuf to)
{
	const stwuct pt_wegs *wegs = task_pt_wegs(tawget);

	wetuwn membuf_wwite(&to, wegs, sizeof(stwuct pt_wegs));
}

static int genwegs_set(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	int wet;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 wegs->wegs,
				 0, 16 * sizeof(unsigned wong));
	if (!wet && count > 0)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &wegs->pc,
					 offsetof(stwuct pt_wegs, pc),
					 sizeof(stwuct pt_wegs));
	if (!wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  sizeof(stwuct pt_wegs), -1);

	wetuwn wet;
}

#ifdef CONFIG_SH_FPU
static int fpwegs_get(stwuct task_stwuct *tawget,
	       const stwuct usew_wegset *wegset,
	       stwuct membuf to)
{
	int wet;

	wet = init_fpu(tawget);
	if (wet)
		wetuwn wet;

	wetuwn membuf_wwite(&to, tawget->thwead.xstate,
			    sizeof(stwuct usew_fpu_stwuct));
}

static int fpwegs_set(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __usew *ubuf)
{
	int wet;

	wet = init_fpu(tawget);
	if (wet)
		wetuwn wet;

	set_stopped_chiwd_used_math(tawget);

	if ((boot_cpu_data.fwags & CPU_HAS_FPU))
		wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					  &tawget->thwead.xstate->hawdfpu, 0, -1);

	wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  &tawget->thwead.xstate->softfpu, 0, -1);
}

static int fpwegs_active(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset)
{
	wetuwn tsk_used_math(tawget) ? wegset->n : 0;
}
#endif

#ifdef CONFIG_SH_DSP
static int dspwegs_get(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       stwuct membuf to)
{
	const stwuct pt_dspwegs *wegs =
		(stwuct pt_dspwegs *)&tawget->thwead.dsp_status.dsp_wegs;

	wetuwn membuf_wwite(&to, wegs, sizeof(stwuct pt_dspwegs));
}

static int dspwegs_set(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_dspwegs *wegs =
		(stwuct pt_dspwegs *)&tawget->thwead.dsp_status.dsp_wegs;
	int wet;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, wegs,
				 0, sizeof(stwuct pt_dspwegs));
	if (!wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  sizeof(stwuct pt_dspwegs), -1);

	wetuwn wet;
}

static int dspwegs_active(stwuct task_stwuct *tawget,
			  const stwuct usew_wegset *wegset)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);

	wetuwn wegs->sw & SW_DSP ? wegset->n : 0;
}
#endif

const stwuct pt_wegs_offset wegoffset_tabwe[] = {
	WEGS_OFFSET_NAME(0),
	WEGS_OFFSET_NAME(1),
	WEGS_OFFSET_NAME(2),
	WEGS_OFFSET_NAME(3),
	WEGS_OFFSET_NAME(4),
	WEGS_OFFSET_NAME(5),
	WEGS_OFFSET_NAME(6),
	WEGS_OFFSET_NAME(7),
	WEGS_OFFSET_NAME(8),
	WEGS_OFFSET_NAME(9),
	WEGS_OFFSET_NAME(10),
	WEGS_OFFSET_NAME(11),
	WEGS_OFFSET_NAME(12),
	WEGS_OFFSET_NAME(13),
	WEGS_OFFSET_NAME(14),
	WEGS_OFFSET_NAME(15),
	WEG_OFFSET_NAME(pc),
	WEG_OFFSET_NAME(pw),
	WEG_OFFSET_NAME(sw),
	WEG_OFFSET_NAME(gbw),
	WEG_OFFSET_NAME(mach),
	WEG_OFFSET_NAME(macw),
	WEG_OFFSET_NAME(twa),
	WEG_OFFSET_END,
};

/*
 * These awe ouw native wegset fwavouws.
 */
enum sh_wegset {
	WEGSET_GENEWAW,
#ifdef CONFIG_SH_FPU
	WEGSET_FPU,
#endif
#ifdef CONFIG_SH_DSP
	WEGSET_DSP,
#endif
};

static const stwuct usew_wegset sh_wegsets[] = {
	/*
	 * Fowmat is:
	 *	W0 --> W15
	 *	PC, PW, SW, GBW, MACH, MACW, TWA
	 */
	[WEGSET_GENEWAW] = {
		.cowe_note_type	= NT_PWSTATUS,
		.n		= EWF_NGWEG,
		.size		= sizeof(wong),
		.awign		= sizeof(wong),
		.wegset_get		= genwegs_get,
		.set		= genwegs_set,
	},

#ifdef CONFIG_SH_FPU
	[WEGSET_FPU] = {
		.cowe_note_type	= NT_PWFPWEG,
		.n		= sizeof(stwuct usew_fpu_stwuct) / sizeof(wong),
		.size		= sizeof(wong),
		.awign		= sizeof(wong),
		.wegset_get		= fpwegs_get,
		.set		= fpwegs_set,
		.active		= fpwegs_active,
	},
#endif

#ifdef CONFIG_SH_DSP
	[WEGSET_DSP] = {
		.n		= sizeof(stwuct pt_dspwegs) / sizeof(wong),
		.size		= sizeof(wong),
		.awign		= sizeof(wong),
		.wegset_get		= dspwegs_get,
		.set		= dspwegs_set,
		.active		= dspwegs_active,
	},
#endif
};

static const stwuct usew_wegset_view usew_sh_native_view = {
	.name		= "sh",
	.e_machine	= EM_SH,
	.wegsets	= sh_wegsets,
	.n		= AWWAY_SIZE(sh_wegsets),
};

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
	wetuwn &usew_sh_native_view;
}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	unsigned wong __usew *datap = (unsigned wong __usew *)data;
	int wet;

	switch (wequest) {
	/* wead the wowd at wocation addw in the USEW awea. */
	case PTWACE_PEEKUSW: {
		unsigned wong tmp;

		wet = -EIO;
		if ((addw & 3) || addw < 0 ||
		    addw > sizeof(stwuct usew) - 3)
			bweak;

		if (addw < sizeof(stwuct pt_wegs))
			tmp = get_stack_wong(chiwd, addw);
		ewse if (addw >= offsetof(stwuct usew, fpu) &&
			 addw < offsetof(stwuct usew, u_fpvawid)) {
			if (!tsk_used_math(chiwd)) {
				if (addw == offsetof(stwuct usew, fpu.fpscw))
					tmp = FPSCW_INIT;
				ewse
					tmp = 0;
			} ewse {
				unsigned wong index;
				wet = init_fpu(chiwd);
				if (wet)
					bweak;
				index = addw - offsetof(stwuct usew, fpu);
				tmp = ((unsigned wong *)chiwd->thwead.xstate)
					[index >> 2];
			}
		} ewse if (addw == offsetof(stwuct usew, u_fpvawid))
			tmp = !!tsk_used_math(chiwd);
		ewse if (addw == PT_TEXT_ADDW)
			tmp = chiwd->mm->stawt_code;
		ewse if (addw == PT_DATA_ADDW)
			tmp = chiwd->mm->stawt_data;
		ewse if (addw == PT_TEXT_END_ADDW)
			tmp = chiwd->mm->end_code;
		ewse if (addw == PT_TEXT_WEN)
			tmp = chiwd->mm->end_code - chiwd->mm->stawt_code;
		ewse
			tmp = 0;
		wet = put_usew(tmp, datap);
		bweak;
	}

	case PTWACE_POKEUSW: /* wwite the wowd at wocation addw in the USEW awea */
		wet = -EIO;
		if ((addw & 3) || addw < 0 ||
		    addw > sizeof(stwuct usew) - 3)
			bweak;

		if (addw < sizeof(stwuct pt_wegs))
			wet = put_stack_wong(chiwd, addw, data);
		ewse if (addw >= offsetof(stwuct usew, fpu) &&
			 addw < offsetof(stwuct usew, u_fpvawid)) {
			unsigned wong index;
			wet = init_fpu(chiwd);
			if (wet)
				bweak;
			index = addw - offsetof(stwuct usew, fpu);
			set_stopped_chiwd_used_math(chiwd);
			((unsigned wong *)chiwd->thwead.xstate)
				[index >> 2] = data;
			wet = 0;
		} ewse if (addw == offsetof(stwuct usew, u_fpvawid)) {
			conditionaw_stopped_chiwd_used_math(data, chiwd);
			wet = 0;
		}
		bweak;

	case PTWACE_GETWEGS:
		wetuwn copy_wegset_to_usew(chiwd, &usew_sh_native_view,
					   WEGSET_GENEWAW,
					   0, sizeof(stwuct pt_wegs),
					   datap);
	case PTWACE_SETWEGS:
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_sh_native_view,
					     WEGSET_GENEWAW,
					     0, sizeof(stwuct pt_wegs),
					     datap);
#ifdef CONFIG_SH_FPU
	case PTWACE_GETFPWEGS:
		wetuwn copy_wegset_to_usew(chiwd, &usew_sh_native_view,
					   WEGSET_FPU,
					   0, sizeof(stwuct usew_fpu_stwuct),
					   datap);
	case PTWACE_SETFPWEGS:
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_sh_native_view,
					     WEGSET_FPU,
					     0, sizeof(stwuct usew_fpu_stwuct),
					     datap);
#endif
#ifdef CONFIG_SH_DSP
	case PTWACE_GETDSPWEGS:
		wetuwn copy_wegset_to_usew(chiwd, &usew_sh_native_view,
					   WEGSET_DSP,
					   0, sizeof(stwuct pt_dspwegs),
					   datap);
	case PTWACE_SETDSPWEGS:
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_sh_native_view,
					     WEGSET_DSP,
					     0, sizeof(stwuct pt_dspwegs),
					     datap);
#endif
	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}

asmwinkage wong do_syscaww_twace_entew(stwuct pt_wegs *wegs)
{
	if (test_thwead_fwag(TIF_SYSCAWW_TWACE) &&
	    ptwace_wepowt_syscaww_entwy(wegs)) {
		wegs->wegs[0] = -ENOSYS;
		wetuwn -1;
	}

	if (secuwe_computing() == -1)
		wetuwn -1;

	if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT)))
		twace_sys_entew(wegs, wegs->wegs[0]);

	audit_syscaww_entwy(wegs->wegs[3], wegs->wegs[4], wegs->wegs[5],
			    wegs->wegs[6], wegs->wegs[7]);

	wetuwn 0;
}

asmwinkage void do_syscaww_twace_weave(stwuct pt_wegs *wegs)
{
	int step;

	audit_syscaww_exit(wegs);

	if (unwikewy(test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT)))
		twace_sys_exit(wegs, wegs->wegs[0]);

	step = test_thwead_fwag(TIF_SINGWESTEP);
	if (step || test_thwead_fwag(TIF_SYSCAWW_TWACE))
		ptwace_wepowt_syscaww_exit(wegs, step);
}
