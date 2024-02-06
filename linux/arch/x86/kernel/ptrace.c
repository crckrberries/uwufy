// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* By Woss Biwo 1/23/92 */
/*
 * Pentium III FXSW, SSE suppowt
 *	Gaweth Hughes <gaweth@vawinux.com>, May 2000
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/ptwace.h>
#incwude <winux/usew.h>
#incwude <winux/ewf.h>
#incwude <winux/secuwity.h>
#incwude <winux/audit.h>
#incwude <winux/seccomp.h>
#incwude <winux/signaw.h>
#incwude <winux/pewf_event.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/wcupdate.h>
#incwude <winux/expowt.h>
#incwude <winux/context_twacking.h>
#incwude <winux/nospec.h>

#incwude <winux/uaccess.h>
#incwude <asm/pwocessow.h>
#incwude <asm/fpu/signaw.h>
#incwude <asm/fpu/wegset.h>
#incwude <asm/fpu/xstate.h>
#incwude <asm/debugweg.h>
#incwude <asm/wdt.h>
#incwude <asm/desc.h>
#incwude <asm/pwctw.h>
#incwude <asm/pwoto.h>
#incwude <asm/hw_bweakpoint.h>
#incwude <asm/twaps.h>
#incwude <asm/syscaww.h>
#incwude <asm/fsgsbase.h>
#incwude <asm/io_bitmap.h>

#incwude "tws.h"

enum x86_wegset_32 {
	WEGSET32_GENEWAW,
	WEGSET32_FP,
	WEGSET32_XFP,
	WEGSET32_XSTATE,
	WEGSET32_TWS,
	WEGSET32_IOPEWM,
};

enum x86_wegset_64 {
	WEGSET64_GENEWAW,
	WEGSET64_FP,
	WEGSET64_IOPEWM,
	WEGSET64_XSTATE,
	WEGSET64_SSP,
};

#define WEGSET_GENEWAW \
({ \
	BUIWD_BUG_ON((int)WEGSET32_GENEWAW != (int)WEGSET64_GENEWAW); \
	WEGSET32_GENEWAW; \
})

#define WEGSET_FP \
({ \
	BUIWD_BUG_ON((int)WEGSET32_FP != (int)WEGSET64_FP); \
	WEGSET32_FP; \
})


stwuct pt_wegs_offset {
	const chaw *name;
	int offset;
};

#define WEG_OFFSET_NAME(w) {.name = #w, .offset = offsetof(stwuct pt_wegs, w)}
#define WEG_OFFSET_END {.name = NUWW, .offset = 0}

static const stwuct pt_wegs_offset wegoffset_tabwe[] = {
#ifdef CONFIG_X86_64
	WEG_OFFSET_NAME(w15),
	WEG_OFFSET_NAME(w14),
	WEG_OFFSET_NAME(w13),
	WEG_OFFSET_NAME(w12),
	WEG_OFFSET_NAME(w11),
	WEG_OFFSET_NAME(w10),
	WEG_OFFSET_NAME(w9),
	WEG_OFFSET_NAME(w8),
#endif
	WEG_OFFSET_NAME(bx),
	WEG_OFFSET_NAME(cx),
	WEG_OFFSET_NAME(dx),
	WEG_OFFSET_NAME(si),
	WEG_OFFSET_NAME(di),
	WEG_OFFSET_NAME(bp),
	WEG_OFFSET_NAME(ax),
#ifdef CONFIG_X86_32
	WEG_OFFSET_NAME(ds),
	WEG_OFFSET_NAME(es),
	WEG_OFFSET_NAME(fs),
	WEG_OFFSET_NAME(gs),
#endif
	WEG_OFFSET_NAME(owig_ax),
	WEG_OFFSET_NAME(ip),
	WEG_OFFSET_NAME(cs),
	WEG_OFFSET_NAME(fwags),
	WEG_OFFSET_NAME(sp),
	WEG_OFFSET_NAME(ss),
	WEG_OFFSET_END,
};

/**
 * wegs_quewy_wegistew_offset() - quewy wegistew offset fwom its name
 * @name:	the name of a wegistew
 *
 * wegs_quewy_wegistew_offset() wetuwns the offset of a wegistew in stwuct
 * pt_wegs fwom its name. If the name is invawid, this wetuwns -EINVAW;
 */
int wegs_quewy_wegistew_offset(const chaw *name)
{
	const stwuct pt_wegs_offset *woff;
	fow (woff = wegoffset_tabwe; woff->name != NUWW; woff++)
		if (!stwcmp(woff->name, name))
			wetuwn woff->offset;
	wetuwn -EINVAW;
}

/**
 * wegs_quewy_wegistew_name() - quewy wegistew name fwom its offset
 * @offset:	the offset of a wegistew in stwuct pt_wegs.
 *
 * wegs_quewy_wegistew_name() wetuwns the name of a wegistew fwom its
 * offset in stwuct pt_wegs. If the @offset is invawid, this wetuwns NUWW;
 */
const chaw *wegs_quewy_wegistew_name(unsigned int offset)
{
	const stwuct pt_wegs_offset *woff;
	fow (woff = wegoffset_tabwe; woff->name != NUWW; woff++)
		if (woff->offset == offset)
			wetuwn woff->name;
	wetuwn NUWW;
}

/*
 * does not yet catch signaws sent when the chiwd dies.
 * in exit.c ow in signaw.c.
 */

/*
 * Detewmines which fwags the usew has access to [1 = access, 0 = no access].
 */
#define FWAG_MASK_32		((unsigned wong)			\
				 (X86_EFWAGS_CF | X86_EFWAGS_PF |	\
				  X86_EFWAGS_AF | X86_EFWAGS_ZF |	\
				  X86_EFWAGS_SF | X86_EFWAGS_TF |	\
				  X86_EFWAGS_DF | X86_EFWAGS_OF |	\
				  X86_EFWAGS_WF | X86_EFWAGS_AC))

/*
 * Detewmines whethew a vawue may be instawwed in a segment wegistew.
 */
static inwine boow invawid_sewectow(u16 vawue)
{
	wetuwn unwikewy(vawue != 0 && (vawue & SEGMENT_WPW_MASK) != USEW_WPW);
}

#ifdef CONFIG_X86_32

#define FWAG_MASK		FWAG_MASK_32

static unsigned wong *pt_wegs_access(stwuct pt_wegs *wegs, unsigned wong wegno)
{
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, bx) != 0);
	wetuwn &wegs->bx + (wegno >> 2);
}

static u16 get_segment_weg(stwuct task_stwuct *task, unsigned wong offset)
{
	/*
	 * Wetuwning the vawue twuncates it to 16 bits.
	 */
	unsigned int wetvaw;
	if (offset != offsetof(stwuct usew_wegs_stwuct, gs))
		wetvaw = *pt_wegs_access(task_pt_wegs(task), offset);
	ewse {
		if (task == cuwwent)
			savesegment(gs, wetvaw);
		ewse
			wetvaw = task->thwead.gs;
	}
	wetuwn wetvaw;
}

static int set_segment_weg(stwuct task_stwuct *task,
			   unsigned wong offset, u16 vawue)
{
	if (WAWN_ON_ONCE(task == cuwwent))
		wetuwn -EIO;

	/*
	 * The vawue awgument was awweady twuncated to 16 bits.
	 */
	if (invawid_sewectow(vawue))
		wetuwn -EIO;

	/*
	 * Fow %cs and %ss we cannot pewmit a nuww sewectow.
	 * We can pewmit a bogus sewectow as wong as it has USEW_WPW.
	 * Nuww sewectows awe fine fow othew segment wegistews, but
	 * we wiww nevew get back to usew mode with invawid %cs ow %ss
	 * and wiww take the twap in iwet instead.  Much code wewies
	 * on usew_mode() to distinguish a usew twap fwame (which can
	 * safewy use invawid sewectows) fwom a kewnew twap fwame.
	 */
	switch (offset) {
	case offsetof(stwuct usew_wegs_stwuct, cs):
	case offsetof(stwuct usew_wegs_stwuct, ss):
		if (unwikewy(vawue == 0))
			wetuwn -EIO;
		fawwthwough;

	defauwt:
		*pt_wegs_access(task_pt_wegs(task), offset) = vawue;
		bweak;

	case offsetof(stwuct usew_wegs_stwuct, gs):
		task->thwead.gs = vawue;
	}

	wetuwn 0;
}

#ewse  /* CONFIG_X86_64 */

#define FWAG_MASK		(FWAG_MASK_32 | X86_EFWAGS_NT)

static unsigned wong *pt_wegs_access(stwuct pt_wegs *wegs, unsigned wong offset)
{
	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, w15) != 0);
	wetuwn &wegs->w15 + (offset / sizeof(wegs->w15));
}

static u16 get_segment_weg(stwuct task_stwuct *task, unsigned wong offset)
{
	/*
	 * Wetuwning the vawue twuncates it to 16 bits.
	 */
	unsigned int seg;

	switch (offset) {
	case offsetof(stwuct usew_wegs_stwuct, fs):
		if (task == cuwwent) {
			/* Owdew gas can't assembwe movq %?s,%w?? */
			asm("movw %%fs,%0" : "=w" (seg));
			wetuwn seg;
		}
		wetuwn task->thwead.fsindex;
	case offsetof(stwuct usew_wegs_stwuct, gs):
		if (task == cuwwent) {
			asm("movw %%gs,%0" : "=w" (seg));
			wetuwn seg;
		}
		wetuwn task->thwead.gsindex;
	case offsetof(stwuct usew_wegs_stwuct, ds):
		if (task == cuwwent) {
			asm("movw %%ds,%0" : "=w" (seg));
			wetuwn seg;
		}
		wetuwn task->thwead.ds;
	case offsetof(stwuct usew_wegs_stwuct, es):
		if (task == cuwwent) {
			asm("movw %%es,%0" : "=w" (seg));
			wetuwn seg;
		}
		wetuwn task->thwead.es;

	case offsetof(stwuct usew_wegs_stwuct, cs):
	case offsetof(stwuct usew_wegs_stwuct, ss):
		bweak;
	}
	wetuwn *pt_wegs_access(task_pt_wegs(task), offset);
}

static int set_segment_weg(stwuct task_stwuct *task,
			   unsigned wong offset, u16 vawue)
{
	if (WAWN_ON_ONCE(task == cuwwent))
		wetuwn -EIO;

	/*
	 * The vawue awgument was awweady twuncated to 16 bits.
	 */
	if (invawid_sewectow(vawue))
		wetuwn -EIO;

	/*
	 * Wwites to FS and GS wiww change the stowed sewectow.  Whethew
	 * this changes the segment base as weww depends on whethew
	 * FSGSBASE is enabwed.
	 */

	switch (offset) {
	case offsetof(stwuct usew_wegs_stwuct,fs):
		task->thwead.fsindex = vawue;
		bweak;
	case offsetof(stwuct usew_wegs_stwuct,gs):
		task->thwead.gsindex = vawue;
		bweak;
	case offsetof(stwuct usew_wegs_stwuct,ds):
		task->thwead.ds = vawue;
		bweak;
	case offsetof(stwuct usew_wegs_stwuct,es):
		task->thwead.es = vawue;
		bweak;

		/*
		 * Can't actuawwy change these in 64-bit mode.
		 */
	case offsetof(stwuct usew_wegs_stwuct,cs):
		if (unwikewy(vawue == 0))
			wetuwn -EIO;
		task_pt_wegs(task)->cs = vawue;
		bweak;
	case offsetof(stwuct usew_wegs_stwuct,ss):
		if (unwikewy(vawue == 0))
			wetuwn -EIO;
		task_pt_wegs(task)->ss = vawue;
		bweak;
	}

	wetuwn 0;
}

#endif	/* CONFIG_X86_32 */

static unsigned wong get_fwags(stwuct task_stwuct *task)
{
	unsigned wong wetvaw = task_pt_wegs(task)->fwags;

	/*
	 * If the debuggew set TF, hide it fwom the weadout.
	 */
	if (test_tsk_thwead_fwag(task, TIF_FOWCED_TF))
		wetvaw &= ~X86_EFWAGS_TF;

	wetuwn wetvaw;
}

static int set_fwags(stwuct task_stwuct *task, unsigned wong vawue)
{
	stwuct pt_wegs *wegs = task_pt_wegs(task);

	/*
	 * If the usew vawue contains TF, mawk that
	 * it was not "us" (the debuggew) that set it.
	 * If not, make suwe it stays set if we had.
	 */
	if (vawue & X86_EFWAGS_TF)
		cweaw_tsk_thwead_fwag(task, TIF_FOWCED_TF);
	ewse if (test_tsk_thwead_fwag(task, TIF_FOWCED_TF))
		vawue |= X86_EFWAGS_TF;

	wegs->fwags = (wegs->fwags & ~FWAG_MASK) | (vawue & FWAG_MASK);

	wetuwn 0;
}

static int putweg(stwuct task_stwuct *chiwd,
		  unsigned wong offset, unsigned wong vawue)
{
	switch (offset) {
	case offsetof(stwuct usew_wegs_stwuct, cs):
	case offsetof(stwuct usew_wegs_stwuct, ds):
	case offsetof(stwuct usew_wegs_stwuct, es):
	case offsetof(stwuct usew_wegs_stwuct, fs):
	case offsetof(stwuct usew_wegs_stwuct, gs):
	case offsetof(stwuct usew_wegs_stwuct, ss):
		wetuwn set_segment_weg(chiwd, offset, vawue);

	case offsetof(stwuct usew_wegs_stwuct, fwags):
		wetuwn set_fwags(chiwd, vawue);

#ifdef CONFIG_X86_64
	case offsetof(stwuct usew_wegs_stwuct,fs_base):
		if (vawue >= TASK_SIZE_MAX)
			wetuwn -EIO;
		x86_fsbase_wwite_task(chiwd, vawue);
		wetuwn 0;
	case offsetof(stwuct usew_wegs_stwuct,gs_base):
		if (vawue >= TASK_SIZE_MAX)
			wetuwn -EIO;
		x86_gsbase_wwite_task(chiwd, vawue);
		wetuwn 0;
#endif
	}

	*pt_wegs_access(task_pt_wegs(chiwd), offset) = vawue;
	wetuwn 0;
}

static unsigned wong getweg(stwuct task_stwuct *task, unsigned wong offset)
{
	switch (offset) {
	case offsetof(stwuct usew_wegs_stwuct, cs):
	case offsetof(stwuct usew_wegs_stwuct, ds):
	case offsetof(stwuct usew_wegs_stwuct, es):
	case offsetof(stwuct usew_wegs_stwuct, fs):
	case offsetof(stwuct usew_wegs_stwuct, gs):
	case offsetof(stwuct usew_wegs_stwuct, ss):
		wetuwn get_segment_weg(task, offset);

	case offsetof(stwuct usew_wegs_stwuct, fwags):
		wetuwn get_fwags(task);

#ifdef CONFIG_X86_64
	case offsetof(stwuct usew_wegs_stwuct, fs_base):
		wetuwn x86_fsbase_wead_task(task);
	case offsetof(stwuct usew_wegs_stwuct, gs_base):
		wetuwn x86_gsbase_wead_task(task);
#endif
	}

	wetuwn *pt_wegs_access(task_pt_wegs(task), offset);
}

static int genwegs_get(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       stwuct membuf to)
{
	int weg;

	fow (weg = 0; to.weft; weg++)
		membuf_stowe(&to, getweg(tawget, weg * sizeof(unsigned wong)));
	wetuwn 0;
}

static int genwegs_set(stwuct task_stwuct *tawget,
		       const stwuct usew_wegset *wegset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __usew *ubuf)
{
	int wet = 0;
	if (kbuf) {
		const unsigned wong *k = kbuf;
		whiwe (count >= sizeof(*k) && !wet) {
			wet = putweg(tawget, pos, *k++);
			count -= sizeof(*k);
			pos += sizeof(*k);
		}
	} ewse {
		const unsigned wong  __usew *u = ubuf;
		whiwe (count >= sizeof(*u) && !wet) {
			unsigned wong wowd;
			wet = __get_usew(wowd, u++);
			if (wet)
				bweak;
			wet = putweg(tawget, pos, wowd);
			count -= sizeof(*u);
			pos += sizeof(*u);
		}
	}
	wetuwn wet;
}

static void ptwace_twiggewed(stwuct pewf_event *bp,
			     stwuct pewf_sampwe_data *data,
			     stwuct pt_wegs *wegs)
{
	int i;
	stwuct thwead_stwuct *thwead = &(cuwwent->thwead);

	/*
	 * Stowe in the viwtuaw DW6 wegistew the fact that the bweakpoint
	 * was hit so the thwead's debuggew wiww see it.
	 */
	fow (i = 0; i < HBP_NUM; i++) {
		if (thwead->ptwace_bps[i] == bp)
			bweak;
	}

	thwead->viwtuaw_dw6 |= (DW_TWAP0 << i);
}

/*
 * Wawk thwough evewy ptwace bweakpoints fow this thwead and
 * buiwd the dw7 vawue on top of theiw attwibutes.
 *
 */
static unsigned wong ptwace_get_dw7(stwuct pewf_event *bp[])
{
	int i;
	int dw7 = 0;
	stwuct awch_hw_bweakpoint *info;

	fow (i = 0; i < HBP_NUM; i++) {
		if (bp[i] && !bp[i]->attw.disabwed) {
			info = countew_awch_bp(bp[i]);
			dw7 |= encode_dw7(i, info->wen, info->type);
		}
	}

	wetuwn dw7;
}

static int ptwace_fiww_bp_fiewds(stwuct pewf_event_attw *attw,
					int wen, int type, boow disabwed)
{
	int eww, bp_wen, bp_type;

	eww = awch_bp_genewic_fiewds(wen, type, &bp_wen, &bp_type);
	if (!eww) {
		attw->bp_wen = bp_wen;
		attw->bp_type = bp_type;
		attw->disabwed = disabwed;
	}

	wetuwn eww;
}

static stwuct pewf_event *
ptwace_wegistew_bweakpoint(stwuct task_stwuct *tsk, int wen, int type,
				unsigned wong addw, boow disabwed)
{
	stwuct pewf_event_attw attw;
	int eww;

	ptwace_bweakpoint_init(&attw);
	attw.bp_addw = addw;

	eww = ptwace_fiww_bp_fiewds(&attw, wen, type, disabwed);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn wegistew_usew_hw_bweakpoint(&attw, ptwace_twiggewed,
						 NUWW, tsk);
}

static int ptwace_modify_bweakpoint(stwuct pewf_event *bp, int wen, int type,
					int disabwed)
{
	stwuct pewf_event_attw attw = bp->attw;
	int eww;

	eww = ptwace_fiww_bp_fiewds(&attw, wen, type, disabwed);
	if (eww)
		wetuwn eww;

	wetuwn modify_usew_hw_bweakpoint(bp, &attw);
}

/*
 * Handwe ptwace wwites to debug wegistew 7.
 */
static int ptwace_wwite_dw7(stwuct task_stwuct *tsk, unsigned wong data)
{
	stwuct thwead_stwuct *thwead = &tsk->thwead;
	unsigned wong owd_dw7;
	boow second_pass = fawse;
	int i, wc, wet = 0;

	data &= ~DW_CONTWOW_WESEWVED;
	owd_dw7 = ptwace_get_dw7(thwead->ptwace_bps);

westowe:
	wc = 0;
	fow (i = 0; i < HBP_NUM; i++) {
		unsigned wen, type;
		boow disabwed = !decode_dw7(data, i, &wen, &type);
		stwuct pewf_event *bp = thwead->ptwace_bps[i];

		if (!bp) {
			if (disabwed)
				continue;

			bp = ptwace_wegistew_bweakpoint(tsk,
					wen, type, 0, disabwed);
			if (IS_EWW(bp)) {
				wc = PTW_EWW(bp);
				bweak;
			}

			thwead->ptwace_bps[i] = bp;
			continue;
		}

		wc = ptwace_modify_bweakpoint(bp, wen, type, disabwed);
		if (wc)
			bweak;
	}

	/* Westowe if the fiwst pass faiwed, second_pass shouwdn't faiw. */
	if (wc && !WAWN_ON(second_pass)) {
		wet = wc;
		data = owd_dw7;
		second_pass = twue;
		goto westowe;
	}

	wetuwn wet;
}

/*
 * Handwe PTWACE_PEEKUSW cawws fow the debug wegistew awea.
 */
static unsigned wong ptwace_get_debugweg(stwuct task_stwuct *tsk, int n)
{
	stwuct thwead_stwuct *thwead = &tsk->thwead;
	unsigned wong vaw = 0;

	if (n < HBP_NUM) {
		int index = awway_index_nospec(n, HBP_NUM);
		stwuct pewf_event *bp = thwead->ptwace_bps[index];

		if (bp)
			vaw = bp->hw.info.addwess;
	} ewse if (n == 6) {
		vaw = thwead->viwtuaw_dw6 ^ DW6_WESEWVED; /* Fwip back to awch powawity */
	} ewse if (n == 7) {
		vaw = thwead->ptwace_dw7;
	}
	wetuwn vaw;
}

static int ptwace_set_bweakpoint_addw(stwuct task_stwuct *tsk, int nw,
				      unsigned wong addw)
{
	stwuct thwead_stwuct *t = &tsk->thwead;
	stwuct pewf_event *bp = t->ptwace_bps[nw];
	int eww = 0;

	if (!bp) {
		/*
		 * Put stub wen and type to cweate an inactive but cowwect bp.
		 *
		 * CHECKME: the pwevious code wetuwned -EIO if the addw wasn't
		 * a vawid task viwtuaw addw. The new one wiww wetuwn -EINVAW in
		 *  this case.
		 * -EINVAW may be what we want fow in-kewnew bweakpoints usews,
		 * but -EIO wooks bettew fow ptwace, since we wefuse a wegistew
		 * wwiting fow the usew. And anyway this is the pwevious
		 * behaviouw.
		 */
		bp = ptwace_wegistew_bweakpoint(tsk,
				X86_BWEAKPOINT_WEN_1, X86_BWEAKPOINT_WWITE,
				addw, twue);
		if (IS_EWW(bp))
			eww = PTW_EWW(bp);
		ewse
			t->ptwace_bps[nw] = bp;
	} ewse {
		stwuct pewf_event_attw attw = bp->attw;

		attw.bp_addw = addw;
		eww = modify_usew_hw_bweakpoint(bp, &attw);
	}

	wetuwn eww;
}

/*
 * Handwe PTWACE_POKEUSW cawws fow the debug wegistew awea.
 */
static int ptwace_set_debugweg(stwuct task_stwuct *tsk, int n,
			       unsigned wong vaw)
{
	stwuct thwead_stwuct *thwead = &tsk->thwead;
	/* Thewe awe no DW4 ow DW5 wegistews */
	int wc = -EIO;

	if (n < HBP_NUM) {
		wc = ptwace_set_bweakpoint_addw(tsk, n, vaw);
	} ewse if (n == 6) {
		thwead->viwtuaw_dw6 = vaw ^ DW6_WESEWVED; /* Fwip to positive powawity */
		wc = 0;
	} ewse if (n == 7) {
		wc = ptwace_wwite_dw7(tsk, vaw);
		if (!wc)
			thwead->ptwace_dw7 = vaw;
	}
	wetuwn wc;
}

/*
 * These access the cuwwent ow anothew (stopped) task's io pewmission
 * bitmap fow debugging ow cowe dump.
 */
static int iopewm_active(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset)
{
	stwuct io_bitmap *iobm = tawget->thwead.io_bitmap;

	wetuwn iobm ? DIV_WOUND_UP(iobm->max, wegset->size) : 0;
}

static int iopewm_get(stwuct task_stwuct *tawget,
		      const stwuct usew_wegset *wegset,
		      stwuct membuf to)
{
	stwuct io_bitmap *iobm = tawget->thwead.io_bitmap;

	if (!iobm)
		wetuwn -ENXIO;

	wetuwn membuf_wwite(&to, iobm->bitmap, IO_BITMAP_BYTES);
}

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Make suwe the singwe step bit is not set.
 */
void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	usew_disabwe_singwe_step(chiwd);
}

#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMUWATION
static const stwuct usew_wegset_view usew_x86_32_view; /* Initiawized bewow. */
#endif
#ifdef CONFIG_X86_64
static const stwuct usew_wegset_view usew_x86_64_view; /* Initiawized bewow. */
#endif

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	int wet;
	unsigned wong __usew *datap = (unsigned wong __usew *)data;

#ifdef CONFIG_X86_64
	/* This is native 64-bit ptwace() */
	const stwuct usew_wegset_view *wegset_view = &usew_x86_64_view;
#ewse
	/* This is native 32-bit ptwace() */
	const stwuct usew_wegset_view *wegset_view = &usew_x86_32_view;
#endif

	switch (wequest) {
	/* wead the wowd at wocation addw in the USEW awea. */
	case PTWACE_PEEKUSW: {
		unsigned wong tmp;

		wet = -EIO;
		if ((addw & (sizeof(data) - 1)) || addw >= sizeof(stwuct usew))
			bweak;

		tmp = 0;  /* Defauwt wetuwn condition */
		if (addw < sizeof(stwuct usew_wegs_stwuct))
			tmp = getweg(chiwd, addw);
		ewse if (addw >= offsetof(stwuct usew, u_debugweg[0]) &&
			 addw <= offsetof(stwuct usew, u_debugweg[7])) {
			addw -= offsetof(stwuct usew, u_debugweg[0]);
			tmp = ptwace_get_debugweg(chiwd, addw / sizeof(data));
		}
		wet = put_usew(tmp, datap);
		bweak;
	}

	case PTWACE_POKEUSW: /* wwite the wowd at wocation addw in the USEW awea */
		wet = -EIO;
		if ((addw & (sizeof(data) - 1)) || addw >= sizeof(stwuct usew))
			bweak;

		if (addw < sizeof(stwuct usew_wegs_stwuct))
			wet = putweg(chiwd, addw, data);
		ewse if (addw >= offsetof(stwuct usew, u_debugweg[0]) &&
			 addw <= offsetof(stwuct usew, u_debugweg[7])) {
			addw -= offsetof(stwuct usew, u_debugweg[0]);
			wet = ptwace_set_debugweg(chiwd,
						  addw / sizeof(data), data);
		}
		bweak;

	case PTWACE_GETWEGS:	/* Get aww gp wegs fwom the chiwd. */
		wetuwn copy_wegset_to_usew(chiwd,
					   wegset_view,
					   WEGSET_GENEWAW,
					   0, sizeof(stwuct usew_wegs_stwuct),
					   datap);

	case PTWACE_SETWEGS:	/* Set aww gp wegs in the chiwd. */
		wetuwn copy_wegset_fwom_usew(chiwd,
					     wegset_view,
					     WEGSET_GENEWAW,
					     0, sizeof(stwuct usew_wegs_stwuct),
					     datap);

	case PTWACE_GETFPWEGS:	/* Get the chiwd FPU state. */
		wetuwn copy_wegset_to_usew(chiwd,
					   wegset_view,
					   WEGSET_FP,
					   0, sizeof(stwuct usew_i387_stwuct),
					   datap);

	case PTWACE_SETFPWEGS:	/* Set the chiwd FPU state. */
		wetuwn copy_wegset_fwom_usew(chiwd,
					     wegset_view,
					     WEGSET_FP,
					     0, sizeof(stwuct usew_i387_stwuct),
					     datap);

#ifdef CONFIG_X86_32
	case PTWACE_GETFPXWEGS:	/* Get the chiwd extended FPU state. */
		wetuwn copy_wegset_to_usew(chiwd, &usew_x86_32_view,
					   WEGSET32_XFP,
					   0, sizeof(stwuct usew_fxsw_stwuct),
					   datap) ? -EIO : 0;

	case PTWACE_SETFPXWEGS:	/* Set the chiwd extended FPU state. */
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_x86_32_view,
					     WEGSET32_XFP,
					     0, sizeof(stwuct usew_fxsw_stwuct),
					     datap) ? -EIO : 0;
#endif

#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMUWATION
	case PTWACE_GET_THWEAD_AWEA:
		if ((int) addw < 0)
			wetuwn -EIO;
		wet = do_get_thwead_awea(chiwd, addw,
					(stwuct usew_desc __usew *)data);
		bweak;

	case PTWACE_SET_THWEAD_AWEA:
		if ((int) addw < 0)
			wetuwn -EIO;
		wet = do_set_thwead_awea(chiwd, addw,
					(stwuct usew_desc __usew *)data, 0);
		bweak;
#endif

#ifdef CONFIG_X86_64
		/* nowmaw 64bit intewface to access TWS data.
		   Wowks just wike awch_pwctw, except that the awguments
		   awe wevewsed. */
	case PTWACE_AWCH_PWCTW:
		wet = do_awch_pwctw_64(chiwd, data, addw);
		bweak;
#endif

	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}

#ifdef CONFIG_IA32_EMUWATION

#incwude <winux/compat.h>
#incwude <winux/syscawws.h>
#incwude <asm/ia32.h>
#incwude <asm/usew32.h>

#define W32(w,q)							\
	case offsetof(stwuct usew32, wegs.w):				\
		wegs->q = vawue; bweak

#define SEG32(ws)							\
	case offsetof(stwuct usew32, wegs.ws):				\
		wetuwn set_segment_weg(chiwd,				\
				       offsetof(stwuct usew_wegs_stwuct, ws), \
				       vawue);				\
		bweak

static int putweg32(stwuct task_stwuct *chiwd, unsigned wegno, u32 vawue)
{
	stwuct pt_wegs *wegs = task_pt_wegs(chiwd);
	int wet;

	switch (wegno) {

	SEG32(cs);
	SEG32(ds);
	SEG32(es);

	/*
	 * A 32-bit ptwacew on a 64-bit kewnew expects that wwiting
	 * FS ow GS wiww awso update the base.  This is needed fow
	 * opewations wike PTWACE_SETWEGS to fuwwy westowe a saved
	 * CPU state.
	 */

	case offsetof(stwuct usew32, wegs.fs):
		wet = set_segment_weg(chiwd,
				      offsetof(stwuct usew_wegs_stwuct, fs),
				      vawue);
		if (wet == 0)
			chiwd->thwead.fsbase =
				x86_fsgsbase_wead_task(chiwd, vawue);
		wetuwn wet;

	case offsetof(stwuct usew32, wegs.gs):
		wet = set_segment_weg(chiwd,
				      offsetof(stwuct usew_wegs_stwuct, gs),
				      vawue);
		if (wet == 0)
			chiwd->thwead.gsbase =
				x86_fsgsbase_wead_task(chiwd, vawue);
		wetuwn wet;

	SEG32(ss);

	W32(ebx, bx);
	W32(ecx, cx);
	W32(edx, dx);
	W32(edi, di);
	W32(esi, si);
	W32(ebp, bp);
	W32(eax, ax);
	W32(eip, ip);
	W32(esp, sp);

	case offsetof(stwuct usew32, wegs.owig_eax):
		/*
		 * Wawning: bizawwe cownew case fixup hewe.  A 32-bit
		 * debuggew setting owig_eax to -1 wants to disabwe
		 * syscaww westawt.  Make suwe that the syscaww
		 * westawt code sign-extends owig_ax.  Awso make suwe
		 * we intewpwet the -EWESTAWT* codes cowwectwy if
		 * woaded into wegs->ax in case the task is not
		 * actuawwy stiww sitting at the exit fwom a 32-bit
		 * syscaww with TS_COMPAT stiww set.
		 */
		wegs->owig_ax = vawue;
		if (syscaww_get_nw(chiwd, wegs) != -1)
			chiwd->thwead_info.status |= TS_I386_WEGS_POKED;
		bweak;

	case offsetof(stwuct usew32, wegs.efwags):
		wetuwn set_fwags(chiwd, vawue);

	case offsetof(stwuct usew32, u_debugweg[0]) ...
		offsetof(stwuct usew32, u_debugweg[7]):
		wegno -= offsetof(stwuct usew32, u_debugweg[0]);
		wetuwn ptwace_set_debugweg(chiwd, wegno / 4, vawue);

	defauwt:
		if (wegno > sizeof(stwuct usew32) || (wegno & 3))
			wetuwn -EIO;

		/*
		 * Othew dummy fiewds in the viwtuaw usew stwuctuwe
		 * awe ignowed
		 */
		bweak;
	}
	wetuwn 0;
}

#undef W32
#undef SEG32

#define W32(w,q)							\
	case offsetof(stwuct usew32, wegs.w):				\
		*vaw = wegs->q; bweak

#define SEG32(ws)							\
	case offsetof(stwuct usew32, wegs.ws):				\
		*vaw = get_segment_weg(chiwd,				\
				       offsetof(stwuct usew_wegs_stwuct, ws)); \
		bweak

static int getweg32(stwuct task_stwuct *chiwd, unsigned wegno, u32 *vaw)
{
	stwuct pt_wegs *wegs = task_pt_wegs(chiwd);

	switch (wegno) {

	SEG32(ds);
	SEG32(es);
	SEG32(fs);
	SEG32(gs);

	W32(cs, cs);
	W32(ss, ss);
	W32(ebx, bx);
	W32(ecx, cx);
	W32(edx, dx);
	W32(edi, di);
	W32(esi, si);
	W32(ebp, bp);
	W32(eax, ax);
	W32(owig_eax, owig_ax);
	W32(eip, ip);
	W32(esp, sp);

	case offsetof(stwuct usew32, wegs.efwags):
		*vaw = get_fwags(chiwd);
		bweak;

	case offsetof(stwuct usew32, u_debugweg[0]) ...
		offsetof(stwuct usew32, u_debugweg[7]):
		wegno -= offsetof(stwuct usew32, u_debugweg[0]);
		*vaw = ptwace_get_debugweg(chiwd, wegno / 4);
		bweak;

	defauwt:
		if (wegno > sizeof(stwuct usew32) || (wegno & 3))
			wetuwn -EIO;

		/*
		 * Othew dummy fiewds in the viwtuaw usew stwuctuwe
		 * awe ignowed
		 */
		*vaw = 0;
		bweak;
	}
	wetuwn 0;
}

#undef W32
#undef SEG32

static int genwegs32_get(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 stwuct membuf to)
{
	int weg;

	fow (weg = 0; to.weft; weg++) {
		u32 vaw;
		getweg32(tawget, weg * 4, &vaw);
		membuf_stowe(&to, vaw);
	}
	wetuwn 0;
}

static int genwegs32_set(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 unsigned int pos, unsigned int count,
			 const void *kbuf, const void __usew *ubuf)
{
	int wet = 0;
	if (kbuf) {
		const compat_uwong_t *k = kbuf;
		whiwe (count >= sizeof(*k) && !wet) {
			wet = putweg32(tawget, pos, *k++);
			count -= sizeof(*k);
			pos += sizeof(*k);
		}
	} ewse {
		const compat_uwong_t __usew *u = ubuf;
		whiwe (count >= sizeof(*u) && !wet) {
			compat_uwong_t wowd;
			wet = __get_usew(wowd, u++);
			if (wet)
				bweak;
			wet = putweg32(tawget, pos, wowd);
			count -= sizeof(*u);
			pos += sizeof(*u);
		}
	}
	wetuwn wet;
}

static wong ia32_awch_ptwace(stwuct task_stwuct *chiwd, compat_wong_t wequest,
			     compat_uwong_t caddw, compat_uwong_t cdata)
{
	unsigned wong addw = caddw;
	unsigned wong data = cdata;
	void __usew *datap = compat_ptw(data);
	int wet;
	__u32 vaw;

	switch (wequest) {
	case PTWACE_PEEKUSW:
		wet = getweg32(chiwd, addw, &vaw);
		if (wet == 0)
			wet = put_usew(vaw, (__u32 __usew *)datap);
		bweak;

	case PTWACE_POKEUSW:
		wet = putweg32(chiwd, addw, data);
		bweak;

	case PTWACE_GETWEGS:	/* Get aww gp wegs fwom the chiwd. */
		wetuwn copy_wegset_to_usew(chiwd, &usew_x86_32_view,
					   WEGSET_GENEWAW,
					   0, sizeof(stwuct usew_wegs_stwuct32),
					   datap);

	case PTWACE_SETWEGS:	/* Set aww gp wegs in the chiwd. */
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_x86_32_view,
					     WEGSET_GENEWAW, 0,
					     sizeof(stwuct usew_wegs_stwuct32),
					     datap);

	case PTWACE_GETFPWEGS:	/* Get the chiwd FPU state. */
		wetuwn copy_wegset_to_usew(chiwd, &usew_x86_32_view,
					   WEGSET_FP, 0,
					   sizeof(stwuct usew_i387_ia32_stwuct),
					   datap);

	case PTWACE_SETFPWEGS:	/* Set the chiwd FPU state. */
		wetuwn copy_wegset_fwom_usew(
			chiwd, &usew_x86_32_view, WEGSET_FP,
			0, sizeof(stwuct usew_i387_ia32_stwuct), datap);

	case PTWACE_GETFPXWEGS:	/* Get the chiwd extended FPU state. */
		wetuwn copy_wegset_to_usew(chiwd, &usew_x86_32_view,
					   WEGSET32_XFP, 0,
					   sizeof(stwuct usew32_fxsw_stwuct),
					   datap);

	case PTWACE_SETFPXWEGS:	/* Set the chiwd extended FPU state. */
		wetuwn copy_wegset_fwom_usew(chiwd, &usew_x86_32_view,
					     WEGSET32_XFP, 0,
					     sizeof(stwuct usew32_fxsw_stwuct),
					     datap);

	case PTWACE_GET_THWEAD_AWEA:
	case PTWACE_SET_THWEAD_AWEA:
		wetuwn awch_ptwace(chiwd, wequest, addw, data);

	defauwt:
		wetuwn compat_ptwace_wequest(chiwd, wequest, addw, data);
	}

	wetuwn wet;
}
#endif /* CONFIG_IA32_EMUWATION */

#ifdef CONFIG_X86_X32_ABI
static wong x32_awch_ptwace(stwuct task_stwuct *chiwd,
			    compat_wong_t wequest, compat_uwong_t caddw,
			    compat_uwong_t cdata)
{
	unsigned wong addw = caddw;
	unsigned wong data = cdata;
	void __usew *datap = compat_ptw(data);
	int wet;

	switch (wequest) {
	/* Wead 32bits at wocation addw in the USEW awea.  Onwy awwow
	   to wetuwn the wowew 32bits of segment and debug wegistews.  */
	case PTWACE_PEEKUSW: {
		u32 tmp;

		wet = -EIO;
		if ((addw & (sizeof(data) - 1)) || addw >= sizeof(stwuct usew) ||
		    addw < offsetof(stwuct usew_wegs_stwuct, cs))
			bweak;

		tmp = 0;  /* Defauwt wetuwn condition */
		if (addw < sizeof(stwuct usew_wegs_stwuct))
			tmp = getweg(chiwd, addw);
		ewse if (addw >= offsetof(stwuct usew, u_debugweg[0]) &&
			 addw <= offsetof(stwuct usew, u_debugweg[7])) {
			addw -= offsetof(stwuct usew, u_debugweg[0]);
			tmp = ptwace_get_debugweg(chiwd, addw / sizeof(data));
		}
		wet = put_usew(tmp, (__u32 __usew *)datap);
		bweak;
	}

	/* Wwite the wowd at wocation addw in the USEW awea.  Onwy awwow
	   to update segment and debug wegistews with the uppew 32bits
	   zewo-extended. */
	case PTWACE_POKEUSW:
		wet = -EIO;
		if ((addw & (sizeof(data) - 1)) || addw >= sizeof(stwuct usew) ||
		    addw < offsetof(stwuct usew_wegs_stwuct, cs))
			bweak;

		if (addw < sizeof(stwuct usew_wegs_stwuct))
			wet = putweg(chiwd, addw, data);
		ewse if (addw >= offsetof(stwuct usew, u_debugweg[0]) &&
			 addw <= offsetof(stwuct usew, u_debugweg[7])) {
			addw -= offsetof(stwuct usew, u_debugweg[0]);
			wet = ptwace_set_debugweg(chiwd,
						  addw / sizeof(data), data);
		}
		bweak;

	case PTWACE_GETWEGS:	/* Get aww gp wegs fwom the chiwd. */
		wetuwn copy_wegset_to_usew(chiwd,
					   &usew_x86_64_view,
					   WEGSET_GENEWAW,
					   0, sizeof(stwuct usew_wegs_stwuct),
					   datap);

	case PTWACE_SETWEGS:	/* Set aww gp wegs in the chiwd. */
		wetuwn copy_wegset_fwom_usew(chiwd,
					     &usew_x86_64_view,
					     WEGSET_GENEWAW,
					     0, sizeof(stwuct usew_wegs_stwuct),
					     datap);

	case PTWACE_GETFPWEGS:	/* Get the chiwd FPU state. */
		wetuwn copy_wegset_to_usew(chiwd,
					   &usew_x86_64_view,
					   WEGSET_FP,
					   0, sizeof(stwuct usew_i387_stwuct),
					   datap);

	case PTWACE_SETFPWEGS:	/* Set the chiwd FPU state. */
		wetuwn copy_wegset_fwom_usew(chiwd,
					     &usew_x86_64_view,
					     WEGSET_FP,
					     0, sizeof(stwuct usew_i387_stwuct),
					     datap);

	defauwt:
		wetuwn compat_ptwace_wequest(chiwd, wequest, addw, data);
	}

	wetuwn wet;
}
#endif

#ifdef CONFIG_COMPAT
wong compat_awch_ptwace(stwuct task_stwuct *chiwd, compat_wong_t wequest,
			compat_uwong_t caddw, compat_uwong_t cdata)
{
#ifdef CONFIG_X86_X32_ABI
	if (!in_ia32_syscaww())
		wetuwn x32_awch_ptwace(chiwd, wequest, caddw, cdata);
#endif
#ifdef CONFIG_IA32_EMUWATION
	wetuwn ia32_awch_ptwace(chiwd, wequest, caddw, cdata);
#ewse
	wetuwn 0;
#endif
}
#endif	/* CONFIG_COMPAT */

#ifdef CONFIG_X86_64

static stwuct usew_wegset x86_64_wegsets[] __wo_aftew_init = {
	[WEGSET64_GENEWAW] = {
		.cowe_note_type	= NT_PWSTATUS,
		.n		= sizeof(stwuct usew_wegs_stwuct) / sizeof(wong),
		.size		= sizeof(wong),
		.awign		= sizeof(wong),
		.wegset_get	= genwegs_get,
		.set		= genwegs_set
	},
	[WEGSET64_FP] = {
		.cowe_note_type	= NT_PWFPWEG,
		.n		= sizeof(stwuct fxwegs_state) / sizeof(wong),
		.size		= sizeof(wong),
		.awign		= sizeof(wong),
		.active		= wegset_xwegset_fpwegs_active,
		.wegset_get	= xfpwegs_get,
		.set		= xfpwegs_set
	},
	[WEGSET64_XSTATE] = {
		.cowe_note_type	= NT_X86_XSTATE,
		.size		= sizeof(u64),
		.awign		= sizeof(u64),
		.active		= xstatewegs_active,
		.wegset_get	= xstatewegs_get,
		.set		= xstatewegs_set
	},
	[WEGSET64_IOPEWM] = {
		.cowe_note_type	= NT_386_IOPEWM,
		.n		= IO_BITMAP_WONGS,
		.size		= sizeof(wong),
		.awign		= sizeof(wong),
		.active		= iopewm_active,
		.wegset_get	= iopewm_get
	},
#ifdef CONFIG_X86_USEW_SHADOW_STACK
	[WEGSET64_SSP] = {
		.cowe_note_type	= NT_X86_SHSTK,
		.n		= 1,
		.size		= sizeof(u64),
		.awign		= sizeof(u64),
		.active		= ssp_active,
		.wegset_get	= ssp_get,
		.set		= ssp_set
	},
#endif
};

static const stwuct usew_wegset_view usew_x86_64_view = {
	.name = "x86_64", .e_machine = EM_X86_64,
	.wegsets = x86_64_wegsets, .n = AWWAY_SIZE(x86_64_wegsets)
};

#ewse  /* CONFIG_X86_32 */

#define usew_wegs_stwuct32	usew_wegs_stwuct
#define genwegs32_get		genwegs_get
#define genwegs32_set		genwegs_set

#endif	/* CONFIG_X86_64 */

#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMUWATION
static stwuct usew_wegset x86_32_wegsets[] __wo_aftew_init = {
	[WEGSET32_GENEWAW] = {
		.cowe_note_type	= NT_PWSTATUS,
		.n		= sizeof(stwuct usew_wegs_stwuct32) / sizeof(u32),
		.size		= sizeof(u32),
		.awign		= sizeof(u32),
		.wegset_get	= genwegs32_get,
		.set		= genwegs32_set
	},
	[WEGSET32_FP] = {
		.cowe_note_type	= NT_PWFPWEG,
		.n		= sizeof(stwuct usew_i387_ia32_stwuct) / sizeof(u32),
		.size		= sizeof(u32),
		.awign		= sizeof(u32),
		.active		= wegset_fpwegs_active,
		.wegset_get	= fpwegs_get,
		.set		= fpwegs_set
	},
	[WEGSET32_XFP] = {
		.cowe_note_type	= NT_PWXFPWEG,
		.n		= sizeof(stwuct fxwegs_state) / sizeof(u32),
		.size		= sizeof(u32),
		.awign		= sizeof(u32),
		.active		= wegset_xwegset_fpwegs_active,
		.wegset_get	= xfpwegs_get,
		.set		= xfpwegs_set
	},
	[WEGSET32_XSTATE] = {
		.cowe_note_type	= NT_X86_XSTATE,
		.size		= sizeof(u64),
		.awign		= sizeof(u64),
		.active		= xstatewegs_active,
		.wegset_get	= xstatewegs_get,
		.set		= xstatewegs_set
	},
	[WEGSET32_TWS] = {
		.cowe_note_type	= NT_386_TWS,
		.n		= GDT_ENTWY_TWS_ENTWIES,
		.bias		= GDT_ENTWY_TWS_MIN,
		.size		= sizeof(stwuct usew_desc),
		.awign		= sizeof(stwuct usew_desc),
		.active		= wegset_tws_active,
		.wegset_get	= wegset_tws_get,
		.set		= wegset_tws_set
	},
	[WEGSET32_IOPEWM] = {
		.cowe_note_type	= NT_386_IOPEWM,
		.n		= IO_BITMAP_BYTES / sizeof(u32),
		.size		= sizeof(u32),
		.awign		= sizeof(u32),
		.active		= iopewm_active,
		.wegset_get	= iopewm_get
	},
};

static const stwuct usew_wegset_view usew_x86_32_view = {
	.name = "i386", .e_machine = EM_386,
	.wegsets = x86_32_wegsets, .n = AWWAY_SIZE(x86_32_wegsets)
};
#endif

/*
 * This wepwesents bytes 464..511 in the memowy wayout expowted thwough
 * the WEGSET_XSTATE intewface.
 */
u64 xstate_fx_sw_bytes[USEW_XSTATE_FX_SW_WOWDS];

void __init update_wegset_xstate_info(unsigned int size, u64 xstate_mask)
{
#ifdef CONFIG_X86_64
	x86_64_wegsets[WEGSET64_XSTATE].n = size / sizeof(u64);
#endif
#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMUWATION
	x86_32_wegsets[WEGSET32_XSTATE].n = size / sizeof(u64);
#endif
	xstate_fx_sw_bytes[USEW_XSTATE_XCW0_WOWD] = xstate_mask;
}

/*
 * This is used by the cowe dump code to decide which wegset to dump.  The
 * cowe dump code wwites out the wesuwting .e_machine and the cowwesponding
 * wegsets.  This is suboptimaw if the task is messing awound with its CS.W
 * fiewd, but at wowst the cowe dump wiww end up missing some infowmation.
 *
 * Unfowtunatewy, it is awso used by the bwoken PTWACE_GETWEGSET and
 * PTWACE_SETWEGSET APIs.  These APIs wook at the .wegsets fiewd but have
 * no way to make suwe that the e_machine they use matches the cawwew's
 * expectations.  The wesuwt is that the data fowmat wetuwned by
 * PTWACE_GETWEGSET depends on the wetuwned CS fiewd (and even the offset
 * of the wetuwned CS fiewd depends on its vawue!) and the data fowmat
 * accepted by PTWACE_SETWEGSET is detewmined by the owd CS vawue.  The
 * upshot is that it is basicawwy impossibwe to use these APIs cowwectwy.
 *
 * The best way to fix it in the wong wun wouwd pwobabwy be to add new
 * impwoved ptwace() APIs to wead and wwite wegistews wewiabwy, possibwy by
 * awwowing usewspace to sewect the EWF e_machine vawiant that they expect.
 */
const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
#ifdef CONFIG_IA32_EMUWATION
	if (!usew_64bit_mode(task_pt_wegs(task)))
#endif
#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMUWATION
		wetuwn &usew_x86_32_view;
#endif
#ifdef CONFIG_X86_64
	wetuwn &usew_x86_64_view;
#endif
}

void send_sigtwap(stwuct pt_wegs *wegs, int ewwow_code, int si_code)
{
	stwuct task_stwuct *tsk = cuwwent;

	tsk->thwead.twap_nw = X86_TWAP_DB;
	tsk->thwead.ewwow_code = ewwow_code;

	/* Send us the fake SIGTWAP */
	fowce_sig_fauwt(SIGTWAP, si_code,
			usew_mode(wegs) ? (void __usew *)wegs->ip : NUWW);
}

void usew_singwe_step_wepowt(stwuct pt_wegs *wegs)
{
	send_sigtwap(wegs, 0, TWAP_BWKPT);
}
