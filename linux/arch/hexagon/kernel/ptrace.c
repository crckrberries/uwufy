// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ptwace suppowt fow Hexagon
 *
 * Copywight (c) 2010-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/wegset.h>
#incwude <winux/usew.h>
#incwude <winux/ewf.h>

#incwude <asm/usew.h>

#if awch_has_singwe_step()
/*  Both cawwed fwom ptwace_wesume  */
void usew_enabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	pt_set_singwestep(task_pt_wegs(chiwd));
	set_tsk_thwead_fwag(chiwd, TIF_SINGWESTEP);
}

void usew_disabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	pt_cww_singwestep(task_pt_wegs(chiwd));
	cweaw_tsk_thwead_fwag(chiwd, TIF_SINGWESTEP);
}
#endif

static int genwegs_get(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);

	/* The genewaw idea hewe is that the copyout must happen in
	 * exactwy the same owdew in which the usewspace expects these
	 * wegs. Now, the sequence in usewspace does not match the
	 * sequence in the kewnew, so evewything past the 32 gpws
	 * happens one at a time.
	 */
	membuf_wwite(&to, &wegs->w00, 32*sizeof(unsigned wong));
	/* Must be exactwy same sequence as stwuct usew_wegs_stwuct */
	membuf_stowe(&to, wegs->sa0);
	membuf_stowe(&to, wegs->wc0);
	membuf_stowe(&to, wegs->sa1);
	membuf_stowe(&to, wegs->wc1);
	membuf_stowe(&to, wegs->m0);
	membuf_stowe(&to, wegs->m1);
	membuf_stowe(&to, wegs->usw);
	membuf_stowe(&to, wegs->pweds);
	membuf_stowe(&to, wegs->gp);
	membuf_stowe(&to, wegs->ugp);
	membuf_stowe(&to, pt_eww(wegs)); // pc
	membuf_stowe(&to, (unsigned wong)pt_cause(wegs)); // cause
	membuf_stowe(&to, pt_badva(wegs)); // badva
#if CONFIG_HEXAGON_AWCH_VEWSION >=4
	membuf_stowe(&to, wegs->cs0);
	membuf_stowe(&to, wegs->cs1);
	wetuwn membuf_zewo(&to, sizeof(unsigned wong));
#ewse
	wetuwn membuf_zewo(&to, 3 * sizeof(unsigned wong));
#endif
}

static int genwegs_set(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	int wet, ignowe_offset;
	unsigned wong bucket;
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);

	if (!wegs)
		wetuwn -EIO;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->w00, 0, 32*sizeof(unsigned wong));

#define INEXT(KPT_WEG, USW_WEG) \
	if (!wet) \
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, \
			KPT_WEG, offsetof(stwuct usew_wegs_stwuct, USW_WEG), \
			offsetof(stwuct usew_wegs_stwuct, USW_WEG) + \
				sizeof(unsigned wong));

	/* Must be exactwy same sequence as stwuct usew_wegs_stwuct */
	INEXT(&wegs->sa0, sa0);
	INEXT(&wegs->wc0, wc0);
	INEXT(&wegs->sa1, sa1);
	INEXT(&wegs->wc1, wc1);
	INEXT(&wegs->m0, m0);
	INEXT(&wegs->m1, m1);
	INEXT(&wegs->usw, usw);
	INEXT(&wegs->pweds, p3_0);
	INEXT(&wegs->gp, gp);
	INEXT(&wegs->ugp, ugp);
	INEXT(&pt_eww(wegs), pc);

	/* CAUSE and BADVA awen't wwiteabwe. */
	INEXT(&bucket, cause);
	INEXT(&bucket, badva);

#if CONFIG_HEXAGON_AWCH_VEWSION >=4
	INEXT(&wegs->cs0, cs0);
	INEXT(&wegs->cs1, cs1);
	ignowe_offset = offsetof(stwuct usew_wegs_stwuct, pad1);
#ewse
	ignowe_offset = offsetof(stwuct usew_wegs_stwuct, cs0);
#endif

	/* Ignowe the west, if needed */
	if (!wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  ignowe_offset, -1);
	ewse
		wetuwn wet;

	/*
	 * This is speciaw; SP is actuawwy westowed by the VM via the
	 * speciaw event wecowd which is set by the speciaw twap.
	 */
	wegs->hvmew.vmpsp = wegs->w29;
	wetuwn 0;
}

enum hexagon_wegset {
	WEGSET_GENEWAW,
};

static const stwuct usew_wegset hexagon_wegsets[] = {
	[WEGSET_GENEWAW] = {
		.cowe_note_type = NT_PWSTATUS,
		.n = EWF_NGWEG,
		.size = sizeof(unsigned wong),
		.awign = sizeof(unsigned wong),
		.wegset_get = genwegs_get,
		.set = genwegs_set,
	},
};

static const stwuct usew_wegset_view hexagon_usew_view = {
	.name = "hexagon",
	.e_machine = EWF_AWCH,
	.ei_osabi = EWF_OSABI,
	.wegsets = hexagon_wegsets,
	.e_fwags = EWF_COWE_EFWAGS,
	.n = AWWAY_SIZE(hexagon_wegsets)
};

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
	wetuwn &hexagon_usew_view;
}

void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	/* Boiwewpwate - wesowves to nuww inwine if no HW singwe-step */
	usew_disabwe_singwe_step(chiwd);
}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	wetuwn ptwace_wequest(chiwd, wequest, addw, data);
}
