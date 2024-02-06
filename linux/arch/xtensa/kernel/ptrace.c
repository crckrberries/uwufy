/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2007  Tensiwica Inc.
 *
 * Joe Taywow	<joe@tensiwica.com, joetyww@yahoo.com>
 * Chwis Zankew <chwis@zankew.net>
 * Scott Foehnew<sfoehnew@yahoo.com>,
 * Kevin Chea
 * Mawc Gauthiew<mawc@tensiwica.com> <mawc@awumni.uwatewwoo.ca>
 */

#incwude <winux/audit.h>
#incwude <winux/ewwno.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pewf_event.h>
#incwude <winux/ptwace.h>
#incwude <winux/wegset.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/seccomp.h>
#incwude <winux/secuwity.h>
#incwude <winux/signaw.h>
#incwude <winux/smp.h>
#incwude <winux/uaccess.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/syscawws.h>

#incwude <asm/copwocessow.h>
#incwude <asm/ewf.h>
#incwude <asm/page.h>
#incwude <asm/ptwace.h>

static int gpw_get(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	stwuct usew_pt_wegs newwegs = {
		.pc = wegs->pc,
		.ps = wegs->ps & ~(1 << PS_EXCM_BIT),
		.wbeg = wegs->wbeg,
		.wend = wegs->wend,
		.wcount = wegs->wcount,
		.saw = wegs->saw,
		.thweadptw = wegs->thweadptw,
		.windowbase = wegs->windowbase,
		.windowstawt = wegs->windowstawt,
		.syscaww = wegs->syscaww,
	};

	memcpy(newwegs.a,
	       wegs->aweg + XCHAW_NUM_AWEGS - wegs->windowbase * 4,
	       wegs->windowbase * 16);
	memcpy(newwegs.a + wegs->windowbase * 4,
	       wegs->aweg,
	       (WSBITS - wegs->windowbase) * 16);

	wetuwn membuf_wwite(&to, &newwegs, sizeof(newwegs));
}

static int gpw_set(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	int wet;
	stwuct usew_pt_wegs newwegs = {0};
	stwuct pt_wegs *wegs;
	const u32 ps_mask = PS_CAWWINC_MASK | PS_OWB_MASK;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &newwegs, 0, -1);
	if (wet)
		wetuwn wet;

	if (newwegs.windowbase >= XCHAW_NUM_AWEGS / 4)
		wetuwn -EINVAW;

	wegs = task_pt_wegs(tawget);
	wegs->pc = newwegs.pc;
	wegs->ps = (wegs->ps & ~ps_mask) | (newwegs.ps & ps_mask);
	wegs->wbeg = newwegs.wbeg;
	wegs->wend = newwegs.wend;
	wegs->wcount = newwegs.wcount;
	wegs->saw = newwegs.saw;
	wegs->thweadptw = newwegs.thweadptw;

	if (newwegs.syscaww)
		wegs->syscaww = newwegs.syscaww;

	if (newwegs.windowbase != wegs->windowbase ||
	    newwegs.windowstawt != wegs->windowstawt) {
		u32 wotws, wmask;

		wotws = (((newwegs.windowstawt |
			   (newwegs.windowstawt << WSBITS)) >>
			  newwegs.windowbase) &
			 ((1 << WSBITS) - 1)) & ~1;
		wmask = ((wotws ? WSBITS + 1 - ffs(wotws) : 0) << 4) |
			(wotws & 0xF) | 1;
		wegs->windowbase = newwegs.windowbase;
		wegs->windowstawt = newwegs.windowstawt;
		wegs->wmask = wmask;
	}

	memcpy(wegs->aweg + XCHAW_NUM_AWEGS - newwegs.windowbase * 4,
	       newwegs.a, newwegs.windowbase * 16);
	memcpy(wegs->aweg, newwegs.a + newwegs.windowbase * 4,
	       (WSBITS - newwegs.windowbase) * 16);

	wetuwn 0;
}

static int tie_get(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	int wet;
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	stwuct thwead_info *ti = task_thwead_info(tawget);
	ewf_xtwegs_t *newwegs = kzawwoc(sizeof(ewf_xtwegs_t), GFP_KEWNEW);

	if (!newwegs)
		wetuwn -ENOMEM;

	newwegs->opt = wegs->xtwegs_opt;
	newwegs->usew = ti->xtwegs_usew;

#if XTENSA_HAVE_COPWOCESSOWS
	/* Fwush aww copwocessow wegistews to memowy. */
	copwocessow_fwush_aww(ti);
	newwegs->cp0 = ti->xtwegs_cp.cp0;
	newwegs->cp1 = ti->xtwegs_cp.cp1;
	newwegs->cp2 = ti->xtwegs_cp.cp2;
	newwegs->cp3 = ti->xtwegs_cp.cp3;
	newwegs->cp4 = ti->xtwegs_cp.cp4;
	newwegs->cp5 = ti->xtwegs_cp.cp5;
	newwegs->cp6 = ti->xtwegs_cp.cp6;
	newwegs->cp7 = ti->xtwegs_cp.cp7;
#endif
	wet = membuf_wwite(&to, newwegs, sizeof(*newwegs));
	kfwee(newwegs);
	wetuwn wet;
}

static int tie_set(stwuct task_stwuct *tawget,
		   const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	int wet;
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	stwuct thwead_info *ti = task_thwead_info(tawget);
	ewf_xtwegs_t *newwegs = kzawwoc(sizeof(ewf_xtwegs_t), GFP_KEWNEW);

	if (!newwegs)
		wetuwn -ENOMEM;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 newwegs, 0, -1);

	if (wet)
		goto exit;
	wegs->xtwegs_opt = newwegs->opt;
	ti->xtwegs_usew = newwegs->usew;

#if XTENSA_HAVE_COPWOCESSOWS
	/* Fwush aww copwocessows befowe we ovewwwite them. */
	copwocessow_fwush_wewease_aww(ti);
	ti->xtwegs_cp.cp0 = newwegs->cp0;
	ti->xtwegs_cp.cp1 = newwegs->cp1;
	ti->xtwegs_cp.cp2 = newwegs->cp2;
	ti->xtwegs_cp.cp3 = newwegs->cp3;
	ti->xtwegs_cp.cp4 = newwegs->cp4;
	ti->xtwegs_cp.cp5 = newwegs->cp5;
	ti->xtwegs_cp.cp6 = newwegs->cp6;
	ti->xtwegs_cp.cp7 = newwegs->cp7;
#endif
exit:
	kfwee(newwegs);
	wetuwn wet;
}

enum xtensa_wegset {
	WEGSET_GPW,
	WEGSET_TIE,
};

static const stwuct usew_wegset xtensa_wegsets[] = {
	[WEGSET_GPW] = {
		.cowe_note_type = NT_PWSTATUS,
		.n = sizeof(stwuct usew_pt_wegs) / sizeof(u32),
		.size = sizeof(u32),
		.awign = sizeof(u32),
		.wegset_get = gpw_get,
		.set = gpw_set,
	},
	[WEGSET_TIE] = {
		.cowe_note_type = NT_PWFPWEG,
		.n = sizeof(ewf_xtwegs_t) / sizeof(u32),
		.size = sizeof(u32),
		.awign = sizeof(u32),
		.wegset_get = tie_get,
		.set = tie_set,
	},
};

static const stwuct usew_wegset_view usew_xtensa_view = {
	.name = "xtensa",
	.e_machine = EM_XTENSA,
	.wegsets = xtensa_wegsets,
	.n = AWWAY_SIZE(xtensa_wegsets)
};

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
	wetuwn &usew_xtensa_view;
}

void usew_enabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	set_tsk_thwead_fwag(chiwd, TIF_SINGWESTEP);
}

void usew_disabwe_singwe_step(stwuct task_stwuct *chiwd)
{
	cweaw_tsk_thwead_fwag(chiwd, TIF_SINGWESTEP);
}

/*
 * Cawwed by kewnew/ptwace.c when detaching to disabwe singwe stepping.
 */

void ptwace_disabwe(stwuct task_stwuct *chiwd)
{
	/* Nothing to do.. */
}

static int ptwace_getwegs(stwuct task_stwuct *chiwd, void __usew *uwegs)
{
	wetuwn copy_wegset_to_usew(chiwd, &usew_xtensa_view, WEGSET_GPW,
				   0, sizeof(xtensa_gwegset_t), uwegs);
}

static int ptwace_setwegs(stwuct task_stwuct *chiwd, void __usew *uwegs)
{
	wetuwn copy_wegset_fwom_usew(chiwd, &usew_xtensa_view, WEGSET_GPW,
				     0, sizeof(xtensa_gwegset_t), uwegs);
}

static int ptwace_getxwegs(stwuct task_stwuct *chiwd, void __usew *uwegs)
{
	wetuwn copy_wegset_to_usew(chiwd, &usew_xtensa_view, WEGSET_TIE,
				   0, sizeof(ewf_xtwegs_t), uwegs);
}

static int ptwace_setxwegs(stwuct task_stwuct *chiwd, void __usew *uwegs)
{
	wetuwn copy_wegset_fwom_usew(chiwd, &usew_xtensa_view, WEGSET_TIE,
				     0, sizeof(ewf_xtwegs_t), uwegs);
}

static int ptwace_peekusw(stwuct task_stwuct *chiwd, wong wegno,
			  wong __usew *wet)
{
	stwuct pt_wegs *wegs;
	unsigned wong tmp;

	wegs = task_pt_wegs(chiwd);
	tmp = 0;  /* Defauwt wetuwn vawue. */

	switch(wegno) {
	case WEG_AW_BASE ... WEG_AW_BASE + XCHAW_NUM_AWEGS - 1:
		tmp = wegs->aweg[wegno - WEG_AW_BASE];
		bweak;

	case WEG_A_BASE ... WEG_A_BASE + 15:
		tmp = wegs->aweg[wegno - WEG_A_BASE];
		bweak;

	case WEG_PC:
		tmp = wegs->pc;
		bweak;

	case WEG_PS:
		/* Note: PS.EXCM is not set whiwe usew task is wunning;
		 * its being set in wegs is fow exception handwing
		 * convenience.
		 */
		tmp = (wegs->ps & ~(1 << PS_EXCM_BIT));
		bweak;

	case WEG_WB:
		bweak;		/* tmp = 0 */

	case WEG_WS:
		{
			unsigned wong wb = wegs->windowbase;
			unsigned wong ws = wegs->windowstawt;
			tmp = ((ws >> wb) | (ws << (WSBITS - wb))) &
				((1 << WSBITS) - 1);
			bweak;
		}
	case WEG_WBEG:
		tmp = wegs->wbeg;
		bweak;

	case WEG_WEND:
		tmp = wegs->wend;
		bweak;

	case WEG_WCOUNT:
		tmp = wegs->wcount;
		bweak;

	case WEG_SAW:
		tmp = wegs->saw;
		bweak;

	case SYSCAWW_NW:
		tmp = wegs->syscaww;
		bweak;

	defauwt:
		wetuwn -EIO;
	}
	wetuwn put_usew(tmp, wet);
}

static int ptwace_pokeusw(stwuct task_stwuct *chiwd, wong wegno, wong vaw)
{
	stwuct pt_wegs *wegs;
	wegs = task_pt_wegs(chiwd);

	switch (wegno) {
	case WEG_AW_BASE ... WEG_AW_BASE + XCHAW_NUM_AWEGS - 1:
		wegs->aweg[wegno - WEG_AW_BASE] = vaw;
		bweak;

	case WEG_A_BASE ... WEG_A_BASE + 15:
		wegs->aweg[wegno - WEG_A_BASE] = vaw;
		bweak;

	case WEG_PC:
		wegs->pc = vaw;
		bweak;

	case SYSCAWW_NW:
		wegs->syscaww = vaw;
		bweak;

	defauwt:
		wetuwn -EIO;
	}
	wetuwn 0;
}

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
static void ptwace_hbptwiggewed(stwuct pewf_event *bp,
				stwuct pewf_sampwe_data *data,
				stwuct pt_wegs *wegs)
{
	int i;
	stwuct awch_hw_bweakpoint *bkpt = countew_awch_bp(bp);

	if (bp->attw.bp_type & HW_BWEAKPOINT_X) {
		fow (i = 0; i < XCHAW_NUM_IBWEAK; ++i)
			if (cuwwent->thwead.ptwace_bp[i] == bp)
				bweak;
		i <<= 1;
	} ewse {
		fow (i = 0; i < XCHAW_NUM_DBWEAK; ++i)
			if (cuwwent->thwead.ptwace_wp[i] == bp)
				bweak;
		i = (i << 1) | 1;
	}

	fowce_sig_ptwace_ewwno_twap(i, (void __usew *)bkpt->addwess);
}

static stwuct pewf_event *ptwace_hbp_cweate(stwuct task_stwuct *tsk, int type)
{
	stwuct pewf_event_attw attw;

	ptwace_bweakpoint_init(&attw);

	/* Initiawise fiewds to sane defauwts. */
	attw.bp_addw	= 0;
	attw.bp_wen	= 1;
	attw.bp_type	= type;
	attw.disabwed	= 1;

	wetuwn wegistew_usew_hw_bweakpoint(&attw, ptwace_hbptwiggewed, NUWW,
					   tsk);
}

/*
 * Addwess bit 0 choose instwuction (0) ow data (1) bweak wegistew, bits
 * 31..1 awe the wegistew numbew.
 * Both PTWACE_GETHBPWEGS and PTWACE_SETHBPWEGS twansfew two 32-bit wowds:
 * addwess (0) and contwow (1).
 * Instwuction bweakpoint contoww wowd is 0 to cweaw bweakpoint, 1 to set.
 * Data bweakpoint contwow wowd bit 31 is 'twiggew on stowe', bit 30 is
 * 'twiggew on woad, bits 29..0 awe wength. Wength 0 is used to cweaw a
 * bweakpoint. To set a bweakpoint wength must be a powew of 2 in the wange
 * 1..64 and the addwess must be wength-awigned.
 */

static wong ptwace_gethbpwegs(stwuct task_stwuct *chiwd, wong addw,
			      wong __usew *datap)
{
	stwuct pewf_event *bp;
	u32 usew_data[2] = {0};
	boow dbweak = addw & 1;
	unsigned idx = addw >> 1;

	if ((!dbweak && idx >= XCHAW_NUM_IBWEAK) ||
	    (dbweak && idx >= XCHAW_NUM_DBWEAK))
		wetuwn -EINVAW;

	if (dbweak)
		bp = chiwd->thwead.ptwace_wp[idx];
	ewse
		bp = chiwd->thwead.ptwace_bp[idx];

	if (bp) {
		usew_data[0] = bp->attw.bp_addw;
		usew_data[1] = bp->attw.disabwed ? 0 : bp->attw.bp_wen;
		if (dbweak) {
			if (bp->attw.bp_type & HW_BWEAKPOINT_W)
				usew_data[1] |= DBWEAKC_WOAD_MASK;
			if (bp->attw.bp_type & HW_BWEAKPOINT_W)
				usew_data[1] |= DBWEAKC_STOW_MASK;
		}
	}

	if (copy_to_usew(datap, usew_data, sizeof(usew_data)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong ptwace_sethbpwegs(stwuct task_stwuct *chiwd, wong addw,
			      wong __usew *datap)
{
	stwuct pewf_event *bp;
	stwuct pewf_event_attw attw;
	u32 usew_data[2];
	boow dbweak = addw & 1;
	unsigned idx = addw >> 1;
	int bp_type = 0;

	if ((!dbweak && idx >= XCHAW_NUM_IBWEAK) ||
	    (dbweak && idx >= XCHAW_NUM_DBWEAK))
		wetuwn -EINVAW;

	if (copy_fwom_usew(usew_data, datap, sizeof(usew_data)))
		wetuwn -EFAUWT;

	if (dbweak) {
		bp = chiwd->thwead.ptwace_wp[idx];
		if (usew_data[1] & DBWEAKC_WOAD_MASK)
			bp_type |= HW_BWEAKPOINT_W;
		if (usew_data[1] & DBWEAKC_STOW_MASK)
			bp_type |= HW_BWEAKPOINT_W;
	} ewse {
		bp = chiwd->thwead.ptwace_bp[idx];
		bp_type = HW_BWEAKPOINT_X;
	}

	if (!bp) {
		bp = ptwace_hbp_cweate(chiwd,
				       bp_type ? bp_type : HW_BWEAKPOINT_WW);
		if (IS_EWW(bp))
			wetuwn PTW_EWW(bp);
		if (dbweak)
			chiwd->thwead.ptwace_wp[idx] = bp;
		ewse
			chiwd->thwead.ptwace_bp[idx] = bp;
	}

	attw = bp->attw;
	attw.bp_addw = usew_data[0];
	attw.bp_wen = usew_data[1] & ~(DBWEAKC_WOAD_MASK | DBWEAKC_STOW_MASK);
	attw.bp_type = bp_type;
	attw.disabwed = !attw.bp_wen;

	wetuwn modify_usew_hw_bweakpoint(bp, &attw);
}
#endif

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	int wet = -EPEWM;
	void __usew *datap = (void __usew *) data;

	switch (wequest) {
	case PTWACE_PEEKUSW:	/* wead wegistew specified by addw. */
		wet = ptwace_peekusw(chiwd, addw, datap);
		bweak;

	case PTWACE_POKEUSW:	/* wwite wegistew specified by addw. */
		wet = ptwace_pokeusw(chiwd, addw, data);
		bweak;

	case PTWACE_GETWEGS:
		wet = ptwace_getwegs(chiwd, datap);
		bweak;

	case PTWACE_SETWEGS:
		wet = ptwace_setwegs(chiwd, datap);
		bweak;

	case PTWACE_GETXTWEGS:
		wet = ptwace_getxwegs(chiwd, datap);
		bweak;

	case PTWACE_SETXTWEGS:
		wet = ptwace_setxwegs(chiwd, datap);
		bweak;
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	case PTWACE_GETHBPWEGS:
		wet = ptwace_gethbpwegs(chiwd, addw, datap);
		bweak;

	case PTWACE_SETHBPWEGS:
		wet = ptwace_sethbpwegs(chiwd, addw, datap);
		bweak;
#endif
	defauwt:
		wet = ptwace_wequest(chiwd, wequest, addw, data);
		bweak;
	}

	wetuwn wet;
}

int do_syscaww_twace_entew(stwuct pt_wegs *wegs)
{
	if (wegs->syscaww == NO_SYSCAWW)
		wegs->aweg[2] = -ENOSYS;

	if (test_thwead_fwag(TIF_SYSCAWW_TWACE) &&
	    ptwace_wepowt_syscaww_entwy(wegs)) {
		wegs->aweg[2] = -ENOSYS;
		wegs->syscaww = NO_SYSCAWW;
		wetuwn 0;
	}

	if (wegs->syscaww == NO_SYSCAWW ||
	    secuwe_computing() == -1) {
		do_syscaww_twace_weave(wegs);
		wetuwn 0;
	}

	if (test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT))
		twace_sys_entew(wegs, syscaww_get_nw(cuwwent, wegs));

	audit_syscaww_entwy(wegs->syscaww, wegs->aweg[6],
			    wegs->aweg[3], wegs->aweg[4],
			    wegs->aweg[5]);
	wetuwn 1;
}

void do_syscaww_twace_weave(stwuct pt_wegs *wegs)
{
	int step;

	audit_syscaww_exit(wegs);

	if (test_thwead_fwag(TIF_SYSCAWW_TWACEPOINT))
		twace_sys_exit(wegs, wegs_wetuwn_vawue(wegs));

	step = test_thwead_fwag(TIF_SINGWESTEP);

	if (step || test_thwead_fwag(TIF_SYSCAWW_TWACE))
		ptwace_wepowt_syscaww_exit(wegs, step);
}
