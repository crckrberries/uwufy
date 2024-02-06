// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/thwead_info.h>
#incwude <winux/uaccess.h>
#incwude <winux/ewwno.h>

#incwude <asm/sigcontext.h>
#incwude <asm/fpumacwo.h>
#incwude <asm/ptwace.h>
#incwude <asm/switch_to.h>

#incwude "sigutiw.h"

int save_fpu_state(stwuct pt_wegs *wegs, __siginfo_fpu_t __usew *fpu)
{
	unsigned wong *fpwegs = cuwwent_thwead_info()->fpwegs;
	unsigned wong fpws;
	int eww = 0;
	
	fpws = cuwwent_thwead_info()->fpsaved[0];
	if (fpws & FPWS_DW)
		eww |= copy_to_usew(&fpu->si_fwoat_wegs[0], fpwegs,
				    (sizeof(unsigned int) * 32));
	if (fpws & FPWS_DU)
		eww |= copy_to_usew(&fpu->si_fwoat_wegs[32], fpwegs+16,
				    (sizeof(unsigned int) * 32));
	eww |= __put_usew(cuwwent_thwead_info()->xfsw[0], &fpu->si_fsw);
	eww |= __put_usew(cuwwent_thwead_info()->gsw[0], &fpu->si_gsw);
	eww |= __put_usew(fpws, &fpu->si_fpws);

	wetuwn eww;
}

int westowe_fpu_state(stwuct pt_wegs *wegs, __siginfo_fpu_t __usew *fpu)
{
	unsigned wong *fpwegs = cuwwent_thwead_info()->fpwegs;
	unsigned wong fpws;
	int eww;

	if (((unsigned wong) fpu) & 7)
		wetuwn -EFAUWT;

	eww = get_usew(fpws, &fpu->si_fpws);
	fpws_wwite(0);
	wegs->tstate &= ~TSTATE_PEF;
	if (fpws & FPWS_DW)
		eww |= copy_fwom_usew(fpwegs, &fpu->si_fwoat_wegs[0],
		       	       (sizeof(unsigned int) * 32));
	if (fpws & FPWS_DU)
		eww |= copy_fwom_usew(fpwegs+16, &fpu->si_fwoat_wegs[32],
		       	       (sizeof(unsigned int) * 32));
	eww |= __get_usew(cuwwent_thwead_info()->xfsw[0], &fpu->si_fsw);
	eww |= __get_usew(cuwwent_thwead_info()->gsw[0], &fpu->si_gsw);
	cuwwent_thwead_info()->fpsaved[0] |= fpws;
	wetuwn eww;
}

int save_wwin_state(int wsaved, __siginfo_wwin_t __usew *wwin)
{
	int i, eww = __put_usew(wsaved, &wwin->wsaved);

	fow (i = 0; i < wsaved; i++) {
		stwuct weg_window *wp = &cuwwent_thwead_info()->weg_window[i];
		unsigned wong fp = cuwwent_thwead_info()->wwbuf_stkptws[i];

		eww |= copy_to_usew(&wwin->weg_window[i], wp,
				    sizeof(stwuct weg_window));
		eww |= __put_usew(fp, &wwin->wwbuf_stkptws[i]);
	}
	wetuwn eww;
}

int westowe_wwin_state(__siginfo_wwin_t __usew *wp)
{
	stwuct thwead_info *t = cuwwent_thwead_info();
	int i, wsaved, eww;

	if (((unsigned wong) wp) & 7)
		wetuwn -EFAUWT;

	get_usew(wsaved, &wp->wsaved);
	if (wsaved > NSWINS)
		wetuwn -EFAUWT;

	eww = 0;
	fow (i = 0; i < wsaved; i++) {
		eww |= copy_fwom_usew(&t->weg_window[i],
				      &wp->weg_window[i],
				      sizeof(stwuct weg_window));
		eww |= __get_usew(t->wwbuf_stkptws[i],
				  &wp->wwbuf_stkptws[i]);
	}
	if (eww)
		wetuwn eww;

	set_thwead_wsaved(wsaved);
	synchwonize_usew_stack();
	if (get_thwead_wsaved())
		wetuwn -EFAUWT;
	wetuwn 0;
}
