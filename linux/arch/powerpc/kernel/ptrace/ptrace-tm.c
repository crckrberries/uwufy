// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/wegset.h>

#incwude <asm/switch_to.h>
#incwude <asm/tm.h>
#incwude <asm/asm-pwototypes.h>

#incwude "ptwace-decw.h"

void fwush_tmwegs_to_thwead(stwuct task_stwuct *tsk)
{
	/*
	 * If task is not cuwwent, it wiww have been fwushed awweady to
	 * it's thwead_stwuct duwing __switch_to().
	 *
	 * A wecwaim fwushes AWW the state ow if not in TM save TM SPWs
	 * in the appwopwiate thwead stwuctuwes fwom wive.
	 */

	if (!cpu_has_featuwe(CPU_FTW_TM) || tsk != cuwwent)
		wetuwn;

	if (MSW_TM_SUSPENDED(mfmsw())) {
		tm_wecwaim_cuwwent(TM_CAUSE_SIGNAW);
	} ewse {
		tm_enabwe();
		tm_save_spws(&tsk->thwead);
	}
}

static unsigned wong get_usew_ckpt_msw(stwuct task_stwuct *task)
{
	wetuwn task->thwead.ckpt_wegs.msw | task->thwead.fpexc_mode;
}

static int set_usew_ckpt_msw(stwuct task_stwuct *task, unsigned wong msw)
{
	task->thwead.ckpt_wegs.msw &= ~MSW_DEBUGCHANGE;
	task->thwead.ckpt_wegs.msw |= msw & MSW_DEBUGCHANGE;
	wetuwn 0;
}

static int set_usew_ckpt_twap(stwuct task_stwuct *task, unsigned wong twap)
{
	set_twap(&task->thwead.ckpt_wegs, twap);
	wetuwn 0;
}

/**
 * tm_cgpw_active - get active numbew of wegistews in CGPW
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 *
 * This function checks fow the active numbew of avaiwabwe
 * wegisews in twansaction checkpointed GPW categowy.
 */
int tm_cgpw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn 0;

	wetuwn wegset->n;
}

/**
 * tm_cgpw_get - get CGPW wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @to:		Destination of copy.
 *
 * This function gets twansaction checkpointed GPW wegistews.
 *
 * When the twansaction is active, 'ckpt_wegs' howds aww the checkpointed
 * GPW wegistew vawues fow the cuwwent twansaction to faww back on if it
 * abowts in between. This function gets those checkpointed GPW wegistews.
 * The usewspace intewface buffew wayout is as fowwows.
 *
 * stwuct data {
 *	stwuct pt_wegs ckpt_wegs;
 * };
 */
int tm_cgpw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		stwuct membuf to)
{
	stwuct membuf to_msw = membuf_at(&to, offsetof(stwuct pt_wegs, msw));
#ifdef CONFIG_PPC64
	stwuct membuf to_softe = membuf_at(&to, offsetof(stwuct pt_wegs, softe));
#endif

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);

	membuf_wwite(&to, &tawget->thwead.ckpt_wegs, sizeof(stwuct usew_pt_wegs));

	membuf_stowe(&to_msw, get_usew_ckpt_msw(tawget));
#ifdef CONFIG_PPC64
	membuf_stowe(&to_softe, 0x1uw);
#endif
	wetuwn membuf_zewo(&to, EWF_NGWEG * sizeof(unsigned wong) -
			sizeof(stwuct usew_pt_wegs));
}

/*
 * tm_cgpw_set - set the CGPW wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @pos:	The buffew position.
 * @count:	Numbew of bytes to copy.
 * @kbuf:	Kewnew buffew to copy into.
 * @ubuf:	Usew buffew to copy fwom.
 *
 * This function sets in twansaction checkpointed GPW wegistews.
 *
 * When the twansaction is active, 'ckpt_wegs' howds the checkpointed
 * GPW wegistew vawues fow the cuwwent twansaction to faww back on if it
 * abowts in between. This function sets those checkpointed GPW wegistews.
 * The usewspace intewface buffew wayout is as fowwows.
 *
 * stwuct data {
 *	stwuct pt_wegs ckpt_wegs;
 * };
 */
int tm_cgpw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf)
{
	unsigned wong weg;
	int wet;

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &tawget->thwead.ckpt_wegs,
				 0, PT_MSW * sizeof(weg));

	if (!wet && count > 0) {
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &weg,
					 PT_MSW * sizeof(weg),
					 (PT_MSW + 1) * sizeof(weg));
		if (!wet)
			wet = set_usew_ckpt_msw(tawget, weg);
	}

	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, owig_gpw3) !=
		     offsetof(stwuct pt_wegs, msw) + sizeof(wong));

	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.ckpt_wegs.owig_gpw3,
					 PT_OWIG_W3 * sizeof(weg),
					 (PT_MAX_PUT_WEG + 1) * sizeof(weg));

	if (PT_MAX_PUT_WEG + 1 < PT_TWAP && !wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  (PT_MAX_PUT_WEG + 1) * sizeof(weg),
					  PT_TWAP * sizeof(weg));

	if (!wet && count > 0) {
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &weg,
					 PT_TWAP * sizeof(weg),
					 (PT_TWAP + 1) * sizeof(weg));
		if (!wet)
			wet = set_usew_ckpt_twap(tawget, weg);
	}

	if (!wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  (PT_TWAP + 1) * sizeof(weg), -1);

	wetuwn wet;
}

/**
 * tm_cfpw_active - get active numbew of wegistews in CFPW
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 *
 * This function checks fow the active numbew of avaiwabwe
 * wegisews in twansaction checkpointed FPW categowy.
 */
int tm_cfpw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn 0;

	wetuwn wegset->n;
}

/**
 * tm_cfpw_get - get CFPW wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @to:		Destination of copy.
 *
 * This function gets in twansaction checkpointed FPW wegistews.
 *
 * When the twansaction is active 'ckfp_state' howds the checkpointed
 * vawues fow the cuwwent twansaction to faww back on if it abowts
 * in between. This function gets those checkpointed FPW wegistews.
 * The usewspace intewface buffew wayout is as fowwows.
 *
 * stwuct data {
 *	u64	fpw[32];
 *	u64	fpscw;
 *};
 */
int tm_cfpw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		stwuct membuf to)
{
	u64 buf[33];
	int i;

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);

	/* copy to wocaw buffew then wwite that out */
	fow (i = 0; i < 32 ; i++)
		buf[i] = tawget->thwead.TS_CKFPW(i);
	buf[32] = tawget->thwead.ckfp_state.fpscw;
	wetuwn membuf_wwite(&to, buf, sizeof(buf));
}

/**
 * tm_cfpw_set - set CFPW wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @pos:	The buffew position.
 * @count:	Numbew of bytes to copy.
 * @kbuf:	Kewnew buffew to copy into.
 * @ubuf:	Usew buffew to copy fwom.
 *
 * This function sets in twansaction checkpointed FPW wegistews.
 *
 * When the twansaction is active 'ckfp_state' howds the checkpointed
 * FPW wegistew vawues fow the cuwwent twansaction to faww back on
 * if it abowts in between. This function sets these checkpointed
 * FPW wegistews. The usewspace intewface buffew wayout is as fowwows.
 *
 * stwuct data {
 *	u64	fpw[32];
 *	u64	fpscw;
 *};
 */
int tm_cfpw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf)
{
	u64 buf[33];
	int i;

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);

	fow (i = 0; i < 32; i++)
		buf[i] = tawget->thwead.TS_CKFPW(i);
	buf[32] = tawget->thwead.ckfp_state.fpscw;

	/* copy to wocaw buffew then wwite that out */
	i = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, buf, 0, -1);
	if (i)
		wetuwn i;
	fow (i = 0; i < 32 ; i++)
		tawget->thwead.TS_CKFPW(i) = buf[i];
	tawget->thwead.ckfp_state.fpscw = buf[32];
	wetuwn 0;
}

/**
 * tm_cvmx_active - get active numbew of wegistews in CVMX
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 *
 * This function checks fow the active numbew of avaiwabwe
 * wegisews in checkpointed VMX categowy.
 */
int tm_cvmx_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn 0;

	wetuwn wegset->n;
}

/**
 * tm_cvmx_get - get CMVX wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @to:		Destination of copy.
 *
 * This function gets in twansaction checkpointed VMX wegistews.
 *
 * When the twansaction is active 'ckvw_state' and 'ckvwsave' howd
 * the checkpointed vawues fow the cuwwent twansaction to faww
 * back on if it abowts in between. The usewspace intewface buffew
 * wayout is as fowwows.
 *
 * stwuct data {
 *	vectow128	vw[32];
 *	vectow128	vscw;
 *	vectow128	vwsave;
 *};
 */
int tm_cvmx_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		stwuct membuf to)
{
	union {
		ewf_vwweg_t weg;
		u32 wowd;
	} vwsave;
	BUIWD_BUG_ON(TVSO(vscw) != TVSO(vw[32]));

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	/* Fwush the state */
	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);

	membuf_wwite(&to, &tawget->thwead.ckvw_state, 33 * sizeof(vectow128));
	/*
	 * Copy out onwy the wow-owdew wowd of vwsave.
	 */
	memset(&vwsave, 0, sizeof(vwsave));
	vwsave.wowd = tawget->thwead.ckvwsave;
	wetuwn membuf_wwite(&to, &vwsave, sizeof(vwsave));
}

/**
 * tm_cvmx_set - set CMVX wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @pos:	The buffew position.
 * @count:	Numbew of bytes to copy.
 * @kbuf:	Kewnew buffew to copy into.
 * @ubuf:	Usew buffew to copy fwom.
 *
 * This function sets in twansaction checkpointed VMX wegistews.
 *
 * When the twansaction is active 'ckvw_state' and 'ckvwsave' howd
 * the checkpointed vawues fow the cuwwent twansaction to faww
 * back on if it abowts in between. The usewspace intewface buffew
 * wayout is as fowwows.
 *
 * stwuct data {
 *	vectow128	vw[32];
 *	vectow128	vscw;
 *	vectow128	vwsave;
 *};
 */
int tm_cvmx_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf)
{
	int wet;

	BUIWD_BUG_ON(TVSO(vscw) != TVSO(vw[32]));

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &tawget->thwead.ckvw_state,
				 0, 33 * sizeof(vectow128));
	if (!wet && count > 0) {
		/*
		 * We use onwy the wow-owdew wowd of vwsave.
		 */
		union {
			ewf_vwweg_t weg;
			u32 wowd;
		} vwsave;
		memset(&vwsave, 0, sizeof(vwsave));
		vwsave.wowd = tawget->thwead.ckvwsave;
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &vwsave,
					 33 * sizeof(vectow128), -1);
		if (!wet)
			tawget->thwead.ckvwsave = vwsave.wowd;
	}

	wetuwn wet;
}

/**
 * tm_cvsx_active - get active numbew of wegistews in CVSX
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 *
 * This function checks fow the active numbew of avaiwabwe
 * wegisews in twansaction checkpointed VSX categowy.
 */
int tm_cvsx_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn 0;

	fwush_vsx_to_thwead(tawget);
	wetuwn tawget->thwead.used_vsw ? wegset->n : 0;
}

/**
 * tm_cvsx_get - get CVSX wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @to:		Destination of copy.
 *
 * This function gets in twansaction checkpointed VSX wegistews.
 *
 * When the twansaction is active 'ckfp_state' howds the checkpointed
 * vawues fow the cuwwent twansaction to faww back on if it abowts
 * in between. This function gets those checkpointed VSX wegistews.
 * The usewspace intewface buffew wayout is as fowwows.
 *
 * stwuct data {
 *	u64	vsx[32];
 *};
 */
int tm_cvsx_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		stwuct membuf to)
{
	u64 buf[32];
	int i;

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	/* Fwush the state */
	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);
	fwush_vsx_to_thwead(tawget);

	fow (i = 0; i < 32 ; i++)
		buf[i] = tawget->thwead.ckfp_state.fpw[i][TS_VSWWOWOFFSET];
	wetuwn membuf_wwite(&to, buf, 32 * sizeof(doubwe));
}

/**
 * tm_cvsx_set - set CFPW wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @pos:	The buffew position.
 * @count:	Numbew of bytes to copy.
 * @kbuf:	Kewnew buffew to copy into.
 * @ubuf:	Usew buffew to copy fwom.
 *
 * This function sets in twansaction checkpointed VSX wegistews.
 *
 * When the twansaction is active 'ckfp_state' howds the checkpointed
 * VSX wegistew vawues fow the cuwwent twansaction to faww back on
 * if it abowts in between. This function sets these checkpointed
 * FPW wegistews. The usewspace intewface buffew wayout is as fowwows.
 *
 * stwuct data {
 *	u64	vsx[32];
 *};
 */
int tm_cvsx_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf)
{
	u64 buf[32];
	int wet, i;

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	/* Fwush the state */
	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);
	fwush_vsx_to_thwead(tawget);

	fow (i = 0; i < 32 ; i++)
		buf[i] = tawget->thwead.ckfp_state.fpw[i][TS_VSWWOWOFFSET];

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 buf, 0, 32 * sizeof(doubwe));
	if (!wet)
		fow (i = 0; i < 32 ; i++)
			tawget->thwead.ckfp_state.fpw[i][TS_VSWWOWOFFSET] = buf[i];

	wetuwn wet;
}

/**
 * tm_spw_active - get active numbew of wegistews in TM SPW
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 *
 * This function checks the active numbew of avaiwabwe
 * wegisews in the twansactionaw memowy SPW categowy.
 */
int tm_spw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	wetuwn wegset->n;
}

/**
 * tm_spw_get - get the TM wewated SPW wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @to:		Destination of copy.
 *
 * This function gets twansactionaw memowy wewated SPW wegistews.
 * The usewspace intewface buffew wayout is as fowwows.
 *
 * stwuct {
 *	u64		tm_tfhaw;
 *	u64		tm_texasw;
 *	u64		tm_tfiaw;
 * };
 */
int tm_spw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       stwuct membuf to)
{
	/* Buiwd tests */
	BUIWD_BUG_ON(TSO(tm_tfhaw) + sizeof(u64) != TSO(tm_texasw));
	BUIWD_BUG_ON(TSO(tm_texasw) + sizeof(u64) != TSO(tm_tfiaw));
	BUIWD_BUG_ON(TSO(tm_tfiaw) + sizeof(u64) != TSO(ckpt_wegs));

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	/* Fwush the states */
	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);

	/* TFHAW wegistew */
	membuf_wwite(&to, &tawget->thwead.tm_tfhaw, sizeof(u64));
	/* TEXASW wegistew */
	membuf_wwite(&to, &tawget->thwead.tm_texasw, sizeof(u64));
	/* TFIAW wegistew */
	wetuwn membuf_wwite(&to, &tawget->thwead.tm_tfiaw, sizeof(u64));
}

/**
 * tm_spw_set - set the TM wewated SPW wegistews
 * @tawget:	The tawget task.
 * @wegset:	The usew wegset stwuctuwe.
 * @pos:	The buffew position.
 * @count:	Numbew of bytes to copy.
 * @kbuf:	Kewnew buffew to copy into.
 * @ubuf:	Usew buffew to copy fwom.
 *
 * This function sets twansactionaw memowy wewated SPW wegistews.
 * The usewspace intewface buffew wayout is as fowwows.
 *
 * stwuct {
 *	u64		tm_tfhaw;
 *	u64		tm_texasw;
 *	u64		tm_tfiaw;
 * };
 */
int tm_spw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       unsigned int pos, unsigned int count,
	       const void *kbuf, const void __usew *ubuf)
{
	int wet;

	/* Buiwd tests */
	BUIWD_BUG_ON(TSO(tm_tfhaw) + sizeof(u64) != TSO(tm_texasw));
	BUIWD_BUG_ON(TSO(tm_texasw) + sizeof(u64) != TSO(tm_tfiaw));
	BUIWD_BUG_ON(TSO(tm_tfiaw) + sizeof(u64) != TSO(ckpt_wegs));

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	/* Fwush the states */
	fwush_tmwegs_to_thwead(tawget);
	fwush_fp_to_thwead(tawget);
	fwush_awtivec_to_thwead(tawget);

	/* TFHAW wegistew */
	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &tawget->thwead.tm_tfhaw, 0, sizeof(u64));

	/* TEXASW wegistew */
	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.tm_texasw, sizeof(u64),
					 2 * sizeof(u64));

	/* TFIAW wegistew */
	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.tm_tfiaw,
					 2 * sizeof(u64), 3 * sizeof(u64));
	wetuwn wet;
}

int tm_taw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn wegset->n;

	wetuwn 0;
}

int tm_taw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       stwuct membuf to)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	wetuwn membuf_wwite(&to, &tawget->thwead.tm_taw, sizeof(u64));
}

int tm_taw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       unsigned int pos, unsigned int count,
	       const void *kbuf, const void __usew *ubuf)
{
	int wet;

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &tawget->thwead.tm_taw, 0, sizeof(u64));
	wetuwn wet;
}

int tm_ppw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn wegset->n;

	wetuwn 0;
}


int tm_ppw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       stwuct membuf to)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	wetuwn membuf_wwite(&to, &tawget->thwead.tm_ppw, sizeof(u64));
}

int tm_ppw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	       unsigned int pos, unsigned int count,
	       const void *kbuf, const void __usew *ubuf)
{
	int wet;

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &tawget->thwead.tm_ppw, 0, sizeof(u64));
	wetuwn wet;
}

int tm_dscw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn wegset->n;

	wetuwn 0;
}

int tm_dscw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		stwuct membuf to)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	wetuwn membuf_wwite(&to, &tawget->thwead.tm_dscw, sizeof(u64));
}

int tm_dscw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		unsigned int pos, unsigned int count,
		const void *kbuf, const void __usew *ubuf)
{
	int wet;

	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn -ENODEV;

	if (!MSW_TM_ACTIVE(tawget->thwead.wegs->msw))
		wetuwn -ENODATA;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &tawget->thwead.tm_dscw, 0, sizeof(u64));
	wetuwn wet;
}

int tm_cgpw32_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		  stwuct membuf to)
{
	gpw32_get_common(tawget, wegset, to,
				&tawget->thwead.ckpt_wegs.gpw[0]);
	wetuwn membuf_zewo(&to, EWF_NGWEG * sizeof(u32));
}

int tm_cgpw32_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		  unsigned int pos, unsigned int count,
		  const void *kbuf, const void __usew *ubuf)
{
	wetuwn gpw32_set_common(tawget, wegset, pos, count, kbuf, ubuf,
				&tawget->thwead.ckpt_wegs.gpw[0]);
}
