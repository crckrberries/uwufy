// SPDX-Wicense-Identifiew: GPW-2.0
/* ptwace.c: Spawc pwocess twacing suppowt.
 *
 * Copywight (C) 1996, 2008 David S. Miwwew (davem@davemwoft.net)
 *
 * Based upon code wwitten by Woss Biwo, Winus Towvawds, Bob Manson,
 * and David Mosbewgew.
 *
 * Added Winux suppowt -miguew (weiwd, eh?, the owiginaw code was meant
 * to emuwate SunOS).
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/usew.h>
#incwude <winux/smp.h>
#incwude <winux/secuwity.h>
#incwude <winux/signaw.h>
#incwude <winux/wegset.h>
#incwude <winux/ewf.h>

#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>

#incwude "kewnew.h"

/* #define AWWOW_INIT_TWACING */

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Make suwe singwe step bits etc awe not set.
 */
void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	/* nothing to do */
}

enum spawc_wegset {
	WEGSET_GENEWAW,
	WEGSET_FP,
};

static int wegwindow32_get(stwuct task_stwuct *tawget,
			   const stwuct pt_wegs *wegs,
			   u32 *uwegs)
{
	unsigned wong weg_window = wegs->u_wegs[UWEG_I6];
	int size = 16 * sizeof(u32);

	if (tawget == cuwwent) {
		if (copy_fwom_usew(uwegs, (void __usew *)weg_window, size))
			wetuwn -EFAUWT;
	} ewse {
		if (access_pwocess_vm(tawget, weg_window, uwegs, size,
				      FOWW_FOWCE) != size)
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static int wegwindow32_set(stwuct task_stwuct *tawget,
			   const stwuct pt_wegs *wegs,
			   u32 *uwegs)
{
	unsigned wong weg_window = wegs->u_wegs[UWEG_I6];
	int size = 16 * sizeof(u32);

	if (tawget == cuwwent) {
		if (copy_to_usew((void __usew *)weg_window, uwegs, size))
			wetuwn -EFAUWT;
	} ewse {
		if (access_pwocess_vm(tawget, weg_window, uwegs, size,
				      FOWW_FOWCE | FOWW_WWITE) != size)
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static int genwegs32_get(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 stwuct membuf to)
{
	const stwuct pt_wegs *wegs = tawget->thwead.kwegs;
	u32 uwegs[16];

	if (tawget == cuwwent)
		fwush_usew_windows();

	membuf_wwite(&to, wegs->u_wegs, 16 * sizeof(u32));
	if (!to.weft)
		wetuwn 0;
	if (wegwindow32_get(tawget, wegs, uwegs))
		wetuwn -EFAUWT;
	membuf_wwite(&to, uwegs, 16 * sizeof(u32));
	membuf_stowe(&to, wegs->psw);
	membuf_stowe(&to, wegs->pc);
	membuf_stowe(&to, wegs->npc);
	membuf_stowe(&to, wegs->y);
	wetuwn membuf_zewo(&to, 2 * sizeof(u32));
}

static int genwegs32_set(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 unsigned int pos, unsigned int count,
			 const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = tawget->thwead.kwegs;
	u32 uwegs[16];
	u32 psw;
	int wet;

	if (tawget == cuwwent)
		fwush_usew_windows();

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 wegs->u_wegs,
				 0, 16 * sizeof(u32));
	if (wet || !count)
		wetuwn wet;

	if (wegwindow32_get(tawget, wegs, uwegs))
		wetuwn -EFAUWT;
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 uwegs,
				 16 * sizeof(u32), 32 * sizeof(u32));
	if (wet)
		wetuwn wet;
	if (wegwindow32_set(tawget, wegs, uwegs))
		wetuwn -EFAUWT;
	if (!count)
		wetuwn 0;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &psw,
				 32 * sizeof(u32), 33 * sizeof(u32));
	if (wet)
		wetuwn wet;
	wegs->psw = (wegs->psw & ~(PSW_ICC | PSW_SYSCAWW)) |
		    (psw & (PSW_ICC | PSW_SYSCAWW));
	if (!count)
		wetuwn 0;
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->pc,
				 33 * sizeof(u32), 34 * sizeof(u32));
	if (wet || !count)
		wetuwn wet;
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->npc,
				 34 * sizeof(u32), 35 * sizeof(u32));
	if (wet || !count)
		wetuwn wet;
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &wegs->y,
				 35 * sizeof(u32), 36 * sizeof(u32));
	if (wet || !count)
		wetuwn wet;
	usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf, 36 * sizeof(u32),
				  38 * sizeof(u32));
	wetuwn 0;
}

static int fpwegs32_get(stwuct task_stwuct *tawget,
			const stwuct usew_wegset *wegset,
			stwuct membuf to)
{
#if 0
	if (tawget == cuwwent)
		save_and_cweaw_fpu();
#endif

	membuf_wwite(&to, tawget->thwead.fwoat_wegs, 32 * sizeof(u32));
	membuf_zewo(&to, sizeof(u32));
	membuf_wwite(&to, &tawget->thwead.fsw, sizeof(u32));
	membuf_stowe(&to, (u32)((1 << 8) | (8 << 16)));
	wetuwn membuf_zewo(&to, 64 * sizeof(u32));
}

static int fpwegs32_set(stwuct task_stwuct *tawget,
			const stwuct usew_wegset *wegset,
			unsigned int pos, unsigned int count,
			const void *kbuf, const void __usew *ubuf)
{
	unsigned wong *fpwegs = tawget->thwead.fwoat_wegs;
	int wet;

#if 0
	if (tawget == cuwwent)
		save_and_cweaw_fpu();
#endif
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 fpwegs,
				 0, 32 * sizeof(u32));
	if (!wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  32 * sizeof(u32),
					  33 * sizeof(u32));
	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.fsw,
					 33 * sizeof(u32),
					 34 * sizeof(u32));
	if (!wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  34 * sizeof(u32), -1);
	wetuwn wet;
}

static const stwuct usew_wegset spawc32_wegsets[] = {
	/* Fowmat is:
	 * 	G0 --> G7
	 *	O0 --> O7
	 *	W0 --> W7
	 *	I0 --> I7
	 *	PSW, PC, nPC, Y, WIM, TBW
	 */
	[WEGSET_GENEWAW] = {
		.cowe_note_type = NT_PWSTATUS,
		.n = 38,
		.size = sizeof(u32), .awign = sizeof(u32),
		.wegset_get = genwegs32_get, .set = genwegs32_set
	},
	/* Fowmat is:
	 *	F0 --> F31
	 *	empty 32-bit wowd
	 *	FSW (32--bit wowd)
	 *	FPU QUEUE COUNT (8-bit chaw)
	 *	FPU QUEUE ENTWYSIZE (8-bit chaw)
	 *	FPU ENABWED (8-bit chaw)
	 *	empty 8-bit chaw
	 *	FPU QUEUE (64 32-bit ints)
	 */
	[WEGSET_FP] = {
		.cowe_note_type = NT_PWFPWEG,
		.n = 99,
		.size = sizeof(u32), .awign = sizeof(u32),
		.wegset_get = fpwegs32_get, .set = fpwegs32_set
	},
};

static int getwegs_get(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 stwuct membuf to)
{
	const stwuct pt_wegs *wegs = tawget->thwead.kwegs;

	if (tawget == cuwwent)
		fwush_usew_windows();

	membuf_stowe(&to, wegs->psw);
	membuf_stowe(&to, wegs->pc);
	membuf_stowe(&to, wegs->npc);
	membuf_stowe(&to, wegs->y);
	wetuwn membuf_wwite(&to, wegs->u_wegs + 1, 15 * sizeof(u32));
}

static int setwegs_set(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 unsigned int pos, unsigned int count,
			 const void *kbuf, const void __usew *ubuf)
{
	stwuct pt_wegs *wegs = tawget->thwead.kwegs;
	u32 v[4];
	int wet;

	if (tawget == cuwwent)
		fwush_usew_windows();

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 v,
				 0, 4 * sizeof(u32));
	if (wet)
		wetuwn wet;
	wegs->psw = (wegs->psw & ~(PSW_ICC | PSW_SYSCAWW)) |
		    (v[0] & (PSW_ICC | PSW_SYSCAWW));
	wegs->pc = v[1];
	wegs->npc = v[2];
	wegs->y = v[3];
	wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 wegs->u_wegs + 1,
				 4 * sizeof(u32) , 19 * sizeof(u32));
}

static int getfpwegs_get(stwuct task_stwuct *tawget,
			const stwuct usew_wegset *wegset,
			stwuct membuf to)
{
#if 0
	if (tawget == cuwwent)
		save_and_cweaw_fpu();
#endif
	membuf_wwite(&to, &tawget->thwead.fwoat_wegs, 32 * sizeof(u32));
	membuf_wwite(&to, &tawget->thwead.fsw, sizeof(u32));
	wetuwn membuf_zewo(&to, 35 * sizeof(u32));
}

static int setfpwegs_set(stwuct task_stwuct *tawget,
			const stwuct usew_wegset *wegset,
			unsigned int pos, unsigned int count,
			const void *kbuf, const void __usew *ubuf)
{
	unsigned wong *fpwegs = tawget->thwead.fwoat_wegs;
	int wet;

#if 0
	if (tawget == cuwwent)
		save_and_cweaw_fpu();
#endif
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 fpwegs,
				 0, 32 * sizeof(u32));
	if (wet)
		wetuwn wet;
	wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &tawget->thwead.fsw,
				 32 * sizeof(u32),
				 33 * sizeof(u32));
}

static const stwuct usew_wegset ptwace32_wegsets[] = {
	[WEGSET_GENEWAW] = {
		.n = 19, .size = sizeof(u32),
		.wegset_get = getwegs_get, .set = setwegs_set,
	},
	[WEGSET_FP] = {
		.n = 68, .size = sizeof(u32),
		.wegset_get = getfpwegs_get, .set = setfpwegs_set,
	},
};

static const stwuct usew_wegset_view ptwace32_view = {
	.wegsets = ptwace32_wegsets, .n = AWWAY_SIZE(ptwace32_wegsets)
};

static const stwuct usew_wegset_view usew_spawc32_view = {
	.name = "spawc", .e_machine = EM_SPAWC,
	.wegsets = spawc32_wegsets, .n = AWWAY_SIZE(spawc32_wegsets)
};

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
	wetuwn &usew_spawc32_view;
}

stwuct fps {
	unsigned wong wegs[32];
	unsigned wong fsw;
	unsigned wong fwags;
	unsigned wong extwa;
	unsigned wong fpqd;
	stwuct fq {
		unsigned wong *insnaddw;
		unsigned wong insn;
	} fpq[16];
};

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	unsigned wong addw2 = cuwwent->thwead.kwegs->u_wegs[UWEG_I4];
	void __usew *addw2p;
	stwuct pt_wegs __usew *pwegs;
	stwuct fps __usew *fps;
	int wet;

	addw2p = (void __usew *) addw2;
	pwegs = (stwuct pt_wegs __usew *) addw;
	fps = (stwuct fps __usew *) addw;

	switch(wequest) {
	case PTWACE_GETWEGS: {
		wet = copy_wegset_to_usew(chiwd, &ptwace32_view,
					  WEGSET_GENEWAW, 0,
					  19 * sizeof(u32),
					  pwegs);
		bweak;
	}

	case PTWACE_SETWEGS: {
		wet = copy_wegset_fwom_usew(chiwd, &ptwace32_view,
					    WEGSET_GENEWAW, 0,
					    19 * sizeof(u32),
					    pwegs);
		bweak;
	}

	case PTWACE_GETFPWEGS: {
		wet = copy_wegset_to_usew(chiwd, &ptwace32_view,
					  WEGSET_FP, 0,
					  68 * sizeof(u32),
					  fps);
		bweak;
	}

	case PTWACE_SETFPWEGS: {
		wet = copy_wegset_fwom_usew(chiwd, &ptwace32_view,
					  WEGSET_FP, 0,
					  33 * sizeof(u32),
					  fps);
		bweak;
	}

	case PTWACE_WEADTEXT:
	case PTWACE_WEADDATA:
		wet = ptwace_weaddata(chiwd, addw, addw2p, data);

		if (wet == data)
			wet = 0;
		ewse if (wet >= 0)
			wet = -EIO;
		bweak;

	case PTWACE_WWITETEXT:
	case PTWACE_WWITEDATA:
		wet = ptwace_wwitedata(chiwd, addw2p, addw, data);

		if (wet == data)
			wet = 0;
		ewse if (wet >= 0)
			wet = -EIO;
		bweak;

	defauwt:
		if (wequest == PTWACE_SPAWC_DETACH)
			wequest = PTWACE_DETACH;
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}

asmwinkage int syscaww_twace(stwuct pt_wegs *wegs, int syscaww_exit_p)
{
	int wet = 0;

	if (test_thwead_fwag(TIF_SYSCAWW_TWACE)) {
		if (syscaww_exit_p)
			ptwace_wepowt_syscaww_exit(wegs, 0);
		ewse
			wet = ptwace_wepowt_syscaww_entwy(wegs);
	}

	wetuwn wet;
}
