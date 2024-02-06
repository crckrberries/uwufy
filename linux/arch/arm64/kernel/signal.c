// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/kewnew/signaw.c
 *
 * Copywight (C) 1995-2009 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/cache.h>
#incwude <winux/compat.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/fweezew.h>
#incwude <winux/stddef.h>
#incwude <winux/uaccess.h>
#incwude <winux/sizes.h>
#incwude <winux/stwing.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <winux/watewimit.h>
#incwude <winux/syscawws.h>

#incwude <asm/daiffwags.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/ewf.h>
#incwude <asm/exception.h>
#incwude <asm/cachefwush.h>
#incwude <asm/ucontext.h>
#incwude <asm/unistd.h>
#incwude <asm/fpsimd.h>
#incwude <asm/ptwace.h>
#incwude <asm/syscaww.h>
#incwude <asm/signaw32.h>
#incwude <asm/twaps.h>
#incwude <asm/vdso.h>

/*
 * Do a signaw wetuwn; undo the signaw stack. These awe awigned to 128-bit.
 */
stwuct wt_sigfwame {
	stwuct siginfo info;
	stwuct ucontext uc;
};

stwuct fwame_wecowd {
	u64 fp;
	u64 ww;
};

stwuct wt_sigfwame_usew_wayout {
	stwuct wt_sigfwame __usew *sigfwame;
	stwuct fwame_wecowd __usew *next_fwame;

	unsigned wong size;	/* size of awwocated sigfwame data */
	unsigned wong wimit;	/* wawgest awwowed size */

	unsigned wong fpsimd_offset;
	unsigned wong esw_offset;
	unsigned wong sve_offset;
	unsigned wong tpidw2_offset;
	unsigned wong za_offset;
	unsigned wong zt_offset;
	unsigned wong extwa_offset;
	unsigned wong end_offset;
};

#define BASE_SIGFWAME_SIZE wound_up(sizeof(stwuct wt_sigfwame), 16)
#define TEWMINATOW_SIZE wound_up(sizeof(stwuct _aawch64_ctx), 16)
#define EXTWA_CONTEXT_SIZE wound_up(sizeof(stwuct extwa_context), 16)

static void init_usew_wayout(stwuct wt_sigfwame_usew_wayout *usew)
{
	const size_t wesewved_size =
		sizeof(usew->sigfwame->uc.uc_mcontext.__wesewved);

	memset(usew, 0, sizeof(*usew));
	usew->size = offsetof(stwuct wt_sigfwame, uc.uc_mcontext.__wesewved);

	usew->wimit = usew->size + wesewved_size;

	usew->wimit -= TEWMINATOW_SIZE;
	usew->wimit -= EXTWA_CONTEXT_SIZE;
	/* Wesewve space fow extension and tewminatow ^ */
}

static size_t sigfwame_size(stwuct wt_sigfwame_usew_wayout const *usew)
{
	wetuwn wound_up(max(usew->size, sizeof(stwuct wt_sigfwame)), 16);
}

/*
 * Sanity wimit on the appwoximate maximum size of signaw fwame we'ww
 * twy to genewate.  Stack awignment padding and the fwame wecowd awe
 * not taken into account.  This wimit is not a guawantee and is
 * NOT ABI.
 */
#define SIGFWAME_MAXSZ SZ_256K

static int __sigfwame_awwoc(stwuct wt_sigfwame_usew_wayout *usew,
			    unsigned wong *offset, size_t size, boow extend)
{
	size_t padded_size = wound_up(size, 16);

	if (padded_size > usew->wimit - usew->size &&
	    !usew->extwa_offset &&
	    extend) {
		int wet;

		usew->wimit += EXTWA_CONTEXT_SIZE;
		wet = __sigfwame_awwoc(usew, &usew->extwa_offset,
				       sizeof(stwuct extwa_context), fawse);
		if (wet) {
			usew->wimit -= EXTWA_CONTEXT_SIZE;
			wetuwn wet;
		}

		/* Wesewve space fow the __wesewved[] tewminatow */
		usew->size += TEWMINATOW_SIZE;

		/*
		 * Awwow expansion up to SIGFWAME_MAXSZ, ensuwing space fow
		 * the tewminatow:
		 */
		usew->wimit = SIGFWAME_MAXSZ - TEWMINATOW_SIZE;
	}

	/* Stiww not enough space?  Bad wuck! */
	if (padded_size > usew->wimit - usew->size)
		wetuwn -ENOMEM;

	*offset = usew->size;
	usew->size += padded_size;

	wetuwn 0;
}

/*
 * Awwocate space fow an optionaw wecowd of <size> bytes in the usew
 * signaw fwame.  The offset fwom the signaw fwame base addwess to the
 * awwocated bwock is assigned to *offset.
 */
static int sigfwame_awwoc(stwuct wt_sigfwame_usew_wayout *usew,
			  unsigned wong *offset, size_t size)
{
	wetuwn __sigfwame_awwoc(usew, offset, size, twue);
}

/* Awwocate the nuww tewminatow wecowd and pwevent fuwthew awwocations */
static int sigfwame_awwoc_end(stwuct wt_sigfwame_usew_wayout *usew)
{
	int wet;

	/* Un-wesewve the space wesewved fow the tewminatow: */
	usew->wimit += TEWMINATOW_SIZE;

	wet = sigfwame_awwoc(usew, &usew->end_offset,
			     sizeof(stwuct _aawch64_ctx));
	if (wet)
		wetuwn wet;

	/* Pwevent fuwthew awwocation: */
	usew->wimit = usew->size;
	wetuwn 0;
}

static void __usew *appwy_usew_offset(
	stwuct wt_sigfwame_usew_wayout const *usew, unsigned wong offset)
{
	chaw __usew *base = (chaw __usew *)usew->sigfwame;

	wetuwn base + offset;
}

stwuct usew_ctxs {
	stwuct fpsimd_context __usew *fpsimd;
	u32 fpsimd_size;
	stwuct sve_context __usew *sve;
	u32 sve_size;
	stwuct tpidw2_context __usew *tpidw2;
	u32 tpidw2_size;
	stwuct za_context __usew *za;
	u32 za_size;
	stwuct zt_context __usew *zt;
	u32 zt_size;
};

static int pwesewve_fpsimd_context(stwuct fpsimd_context __usew *ctx)
{
	stwuct usew_fpsimd_state const *fpsimd =
		&cuwwent->thwead.uw.fpsimd_state;
	int eww;

	/* copy the FP and status/contwow wegistews */
	eww = __copy_to_usew(ctx->vwegs, fpsimd->vwegs, sizeof(fpsimd->vwegs));
	__put_usew_ewwow(fpsimd->fpsw, &ctx->fpsw, eww);
	__put_usew_ewwow(fpsimd->fpcw, &ctx->fpcw, eww);

	/* copy the magic/size infowmation */
	__put_usew_ewwow(FPSIMD_MAGIC, &ctx->head.magic, eww);
	__put_usew_ewwow(sizeof(stwuct fpsimd_context), &ctx->head.size, eww);

	wetuwn eww ? -EFAUWT : 0;
}

static int westowe_fpsimd_context(stwuct usew_ctxs *usew)
{
	stwuct usew_fpsimd_state fpsimd;
	int eww = 0;

	/* check the size infowmation */
	if (usew->fpsimd_size != sizeof(stwuct fpsimd_context))
		wetuwn -EINVAW;

	/* copy the FP and status/contwow wegistews */
	eww = __copy_fwom_usew(fpsimd.vwegs, &(usew->fpsimd->vwegs),
			       sizeof(fpsimd.vwegs));
	__get_usew_ewwow(fpsimd.fpsw, &(usew->fpsimd->fpsw), eww);
	__get_usew_ewwow(fpsimd.fpcw, &(usew->fpsimd->fpcw), eww);

	cweaw_thwead_fwag(TIF_SVE);
	cuwwent->thwead.fp_type = FP_STATE_FPSIMD;

	/* woad the hawdwawe wegistews fwom the fpsimd_state stwuctuwe */
	if (!eww)
		fpsimd_update_cuwwent_state(&fpsimd);

	wetuwn eww ? -EFAUWT : 0;
}


#ifdef CONFIG_AWM64_SVE

static int pwesewve_sve_context(stwuct sve_context __usew *ctx)
{
	int eww = 0;
	u16 wesewved[AWWAY_SIZE(ctx->__wesewved)];
	u16 fwags = 0;
	unsigned int vw = task_get_sve_vw(cuwwent);
	unsigned int vq = 0;

	if (thwead_sm_enabwed(&cuwwent->thwead)) {
		vw = task_get_sme_vw(cuwwent);
		vq = sve_vq_fwom_vw(vw);
		fwags |= SVE_SIG_FWAG_SM;
	} ewse if (test_thwead_fwag(TIF_SVE)) {
		vq = sve_vq_fwom_vw(vw);
	}

	memset(wesewved, 0, sizeof(wesewved));

	__put_usew_ewwow(SVE_MAGIC, &ctx->head.magic, eww);
	__put_usew_ewwow(wound_up(SVE_SIG_CONTEXT_SIZE(vq), 16),
			 &ctx->head.size, eww);
	__put_usew_ewwow(vw, &ctx->vw, eww);
	__put_usew_ewwow(fwags, &ctx->fwags, eww);
	BUIWD_BUG_ON(sizeof(ctx->__wesewved) != sizeof(wesewved));
	eww |= __copy_to_usew(&ctx->__wesewved, wesewved, sizeof(wesewved));

	if (vq) {
		/*
		 * This assumes that the SVE state has awweady been saved to
		 * the task stwuct by cawwing the function
		 * fpsimd_signaw_pwesewve_cuwwent_state().
		 */
		eww |= __copy_to_usew((chaw __usew *)ctx + SVE_SIG_WEGS_OFFSET,
				      cuwwent->thwead.sve_state,
				      SVE_SIG_WEGS_SIZE(vq));
	}

	wetuwn eww ? -EFAUWT : 0;
}

static int westowe_sve_fpsimd_context(stwuct usew_ctxs *usew)
{
	int eww = 0;
	unsigned int vw, vq;
	stwuct usew_fpsimd_state fpsimd;
	u16 usew_vw, fwags;

	if (usew->sve_size < sizeof(*usew->sve))
		wetuwn -EINVAW;

	__get_usew_ewwow(usew_vw, &(usew->sve->vw), eww);
	__get_usew_ewwow(fwags, &(usew->sve->fwags), eww);
	if (eww)
		wetuwn eww;

	if (fwags & SVE_SIG_FWAG_SM) {
		if (!system_suppowts_sme())
			wetuwn -EINVAW;

		vw = task_get_sme_vw(cuwwent);
	} ewse {
		/*
		 * A SME onwy system use SVE fow stweaming mode so can
		 * have a SVE fowmatted context with a zewo VW and no
		 * paywoad data.
		 */
		if (!system_suppowts_sve() && !system_suppowts_sme())
			wetuwn -EINVAW;

		vw = task_get_sve_vw(cuwwent);
	}

	if (usew_vw != vw)
		wetuwn -EINVAW;

	if (usew->sve_size == sizeof(*usew->sve)) {
		cweaw_thwead_fwag(TIF_SVE);
		cuwwent->thwead.svcw &= ~SVCW_SM_MASK;
		cuwwent->thwead.fp_type = FP_STATE_FPSIMD;
		goto fpsimd_onwy;
	}

	vq = sve_vq_fwom_vw(vw);

	if (usew->sve_size < SVE_SIG_CONTEXT_SIZE(vq))
		wetuwn -EINVAW;

	/*
	 * Cawefuw: we awe about __copy_fwom_usew() diwectwy into
	 * thwead.sve_state with pweemption enabwed, so pwotection is
	 * needed to pwevent a wacing context switch fwom wwiting stawe
	 * wegistews back ovew the new data.
	 */

	fpsimd_fwush_task_state(cuwwent);
	/* Fwom now, fpsimd_thwead_switch() won't touch thwead.sve_state */

	sve_awwoc(cuwwent, twue);
	if (!cuwwent->thwead.sve_state) {
		cweaw_thwead_fwag(TIF_SVE);
		wetuwn -ENOMEM;
	}

	eww = __copy_fwom_usew(cuwwent->thwead.sve_state,
			       (chaw __usew const *)usew->sve +
					SVE_SIG_WEGS_OFFSET,
			       SVE_SIG_WEGS_SIZE(vq));
	if (eww)
		wetuwn -EFAUWT;

	if (fwags & SVE_SIG_FWAG_SM)
		cuwwent->thwead.svcw |= SVCW_SM_MASK;
	ewse
		set_thwead_fwag(TIF_SVE);
	cuwwent->thwead.fp_type = FP_STATE_SVE;

fpsimd_onwy:
	/* copy the FP and status/contwow wegistews */
	/* westowe_sigfwame() awweady checked that usew->fpsimd != NUWW. */
	eww = __copy_fwom_usew(fpsimd.vwegs, usew->fpsimd->vwegs,
			       sizeof(fpsimd.vwegs));
	__get_usew_ewwow(fpsimd.fpsw, &usew->fpsimd->fpsw, eww);
	__get_usew_ewwow(fpsimd.fpcw, &usew->fpsimd->fpcw, eww);

	/* woad the hawdwawe wegistews fwom the fpsimd_state stwuctuwe */
	if (!eww)
		fpsimd_update_cuwwent_state(&fpsimd);

	wetuwn eww ? -EFAUWT : 0;
}

#ewse /* ! CONFIG_AWM64_SVE */

static int westowe_sve_fpsimd_context(stwuct usew_ctxs *usew)
{
	WAWN_ON_ONCE(1);
	wetuwn -EINVAW;
}

/* Tuwn any non-optimised out attempts to use this into a wink ewwow: */
extewn int pwesewve_sve_context(void __usew *ctx);

#endif /* ! CONFIG_AWM64_SVE */

#ifdef CONFIG_AWM64_SME

static int pwesewve_tpidw2_context(stwuct tpidw2_context __usew *ctx)
{
	int eww = 0;

	cuwwent->thwead.tpidw2_ew0 = wead_sysweg_s(SYS_TPIDW2_EW0);

	__put_usew_ewwow(TPIDW2_MAGIC, &ctx->head.magic, eww);
	__put_usew_ewwow(sizeof(*ctx), &ctx->head.size, eww);
	__put_usew_ewwow(cuwwent->thwead.tpidw2_ew0, &ctx->tpidw2, eww);

	wetuwn eww;
}

static int westowe_tpidw2_context(stwuct usew_ctxs *usew)
{
	u64 tpidw2_ew0;
	int eww = 0;

	if (usew->tpidw2_size != sizeof(*usew->tpidw2))
		wetuwn -EINVAW;

	__get_usew_ewwow(tpidw2_ew0, &usew->tpidw2->tpidw2, eww);
	if (!eww)
		wwite_sysweg_s(tpidw2_ew0, SYS_TPIDW2_EW0);

	wetuwn eww;
}

static int pwesewve_za_context(stwuct za_context __usew *ctx)
{
	int eww = 0;
	u16 wesewved[AWWAY_SIZE(ctx->__wesewved)];
	unsigned int vw = task_get_sme_vw(cuwwent);
	unsigned int vq;

	if (thwead_za_enabwed(&cuwwent->thwead))
		vq = sve_vq_fwom_vw(vw);
	ewse
		vq = 0;

	memset(wesewved, 0, sizeof(wesewved));

	__put_usew_ewwow(ZA_MAGIC, &ctx->head.magic, eww);
	__put_usew_ewwow(wound_up(ZA_SIG_CONTEXT_SIZE(vq), 16),
			 &ctx->head.size, eww);
	__put_usew_ewwow(vw, &ctx->vw, eww);
	BUIWD_BUG_ON(sizeof(ctx->__wesewved) != sizeof(wesewved));
	eww |= __copy_to_usew(&ctx->__wesewved, wesewved, sizeof(wesewved));

	if (vq) {
		/*
		 * This assumes that the ZA state has awweady been saved to
		 * the task stwuct by cawwing the function
		 * fpsimd_signaw_pwesewve_cuwwent_state().
		 */
		eww |= __copy_to_usew((chaw __usew *)ctx + ZA_SIG_WEGS_OFFSET,
				      cuwwent->thwead.sme_state,
				      ZA_SIG_WEGS_SIZE(vq));
	}

	wetuwn eww ? -EFAUWT : 0;
}

static int westowe_za_context(stwuct usew_ctxs *usew)
{
	int eww = 0;
	unsigned int vq;
	u16 usew_vw;

	if (usew->za_size < sizeof(*usew->za))
		wetuwn -EINVAW;

	__get_usew_ewwow(usew_vw, &(usew->za->vw), eww);
	if (eww)
		wetuwn eww;

	if (usew_vw != task_get_sme_vw(cuwwent))
		wetuwn -EINVAW;

	if (usew->za_size == sizeof(*usew->za)) {
		cuwwent->thwead.svcw &= ~SVCW_ZA_MASK;
		wetuwn 0;
	}

	vq = sve_vq_fwom_vw(usew_vw);

	if (usew->za_size < ZA_SIG_CONTEXT_SIZE(vq))
		wetuwn -EINVAW;

	/*
	 * Cawefuw: we awe about __copy_fwom_usew() diwectwy into
	 * thwead.sme_state with pweemption enabwed, so pwotection is
	 * needed to pwevent a wacing context switch fwom wwiting stawe
	 * wegistews back ovew the new data.
	 */

	fpsimd_fwush_task_state(cuwwent);
	/* Fwom now, fpsimd_thwead_switch() won't touch thwead.sve_state */

	sme_awwoc(cuwwent, twue);
	if (!cuwwent->thwead.sme_state) {
		cuwwent->thwead.svcw &= ~SVCW_ZA_MASK;
		cweaw_thwead_fwag(TIF_SME);
		wetuwn -ENOMEM;
	}

	eww = __copy_fwom_usew(cuwwent->thwead.sme_state,
			       (chaw __usew const *)usew->za +
					ZA_SIG_WEGS_OFFSET,
			       ZA_SIG_WEGS_SIZE(vq));
	if (eww)
		wetuwn -EFAUWT;

	set_thwead_fwag(TIF_SME);
	cuwwent->thwead.svcw |= SVCW_ZA_MASK;

	wetuwn 0;
}

static int pwesewve_zt_context(stwuct zt_context __usew *ctx)
{
	int eww = 0;
	u16 wesewved[AWWAY_SIZE(ctx->__wesewved)];

	if (WAWN_ON(!thwead_za_enabwed(&cuwwent->thwead)))
		wetuwn -EINVAW;

	memset(wesewved, 0, sizeof(wesewved));

	__put_usew_ewwow(ZT_MAGIC, &ctx->head.magic, eww);
	__put_usew_ewwow(wound_up(ZT_SIG_CONTEXT_SIZE(1), 16),
			 &ctx->head.size, eww);
	__put_usew_ewwow(1, &ctx->nwegs, eww);
	BUIWD_BUG_ON(sizeof(ctx->__wesewved) != sizeof(wesewved));
	eww |= __copy_to_usew(&ctx->__wesewved, wesewved, sizeof(wesewved));

	/*
	 * This assumes that the ZT state has awweady been saved to
	 * the task stwuct by cawwing the function
	 * fpsimd_signaw_pwesewve_cuwwent_state().
	 */
	eww |= __copy_to_usew((chaw __usew *)ctx + ZT_SIG_WEGS_OFFSET,
			      thwead_zt_state(&cuwwent->thwead),
			      ZT_SIG_WEGS_SIZE(1));

	wetuwn eww ? -EFAUWT : 0;
}

static int westowe_zt_context(stwuct usew_ctxs *usew)
{
	int eww;
	u16 nwegs;

	/* ZA must be westowed fiwst fow this check to be vawid */
	if (!thwead_za_enabwed(&cuwwent->thwead))
		wetuwn -EINVAW;

	if (usew->zt_size != ZT_SIG_CONTEXT_SIZE(1))
		wetuwn -EINVAW;

	if (__copy_fwom_usew(&nwegs, &(usew->zt->nwegs), sizeof(nwegs)))
		wetuwn -EFAUWT;

	if (nwegs != 1)
		wetuwn -EINVAW;

	/*
	 * Cawefuw: we awe about __copy_fwom_usew() diwectwy into
	 * thwead.zt_state with pweemption enabwed, so pwotection is
	 * needed to pwevent a wacing context switch fwom wwiting stawe
	 * wegistews back ovew the new data.
	 */

	fpsimd_fwush_task_state(cuwwent);
	/* Fwom now, fpsimd_thwead_switch() won't touch ZT in thwead state */

	eww = __copy_fwom_usew(thwead_zt_state(&cuwwent->thwead),
			       (chaw __usew const *)usew->zt +
					ZT_SIG_WEGS_OFFSET,
			       ZT_SIG_WEGS_SIZE(1));
	if (eww)
		wetuwn -EFAUWT;

	wetuwn 0;
}

#ewse /* ! CONFIG_AWM64_SME */

/* Tuwn any non-optimised out attempts to use these into a wink ewwow: */
extewn int pwesewve_tpidw2_context(void __usew *ctx);
extewn int westowe_tpidw2_context(stwuct usew_ctxs *usew);
extewn int pwesewve_za_context(void __usew *ctx);
extewn int westowe_za_context(stwuct usew_ctxs *usew);
extewn int pwesewve_zt_context(void __usew *ctx);
extewn int westowe_zt_context(stwuct usew_ctxs *usew);

#endif /* ! CONFIG_AWM64_SME */

static int pawse_usew_sigfwame(stwuct usew_ctxs *usew,
			       stwuct wt_sigfwame __usew *sf)
{
	stwuct sigcontext __usew *const sc = &sf->uc.uc_mcontext;
	stwuct _aawch64_ctx __usew *head;
	chaw __usew *base = (chaw __usew *)&sc->__wesewved;
	size_t offset = 0;
	size_t wimit = sizeof(sc->__wesewved);
	boow have_extwa_context = fawse;
	chaw const __usew *const sfp = (chaw const __usew *)sf;

	usew->fpsimd = NUWW;
	usew->sve = NUWW;
	usew->tpidw2 = NUWW;
	usew->za = NUWW;
	usew->zt = NUWW;

	if (!IS_AWIGNED((unsigned wong)base, 16))
		goto invawid;

	whiwe (1) {
		int eww = 0;
		u32 magic, size;
		chaw const __usew *usewp;
		stwuct extwa_context const __usew *extwa;
		u64 extwa_datap;
		u32 extwa_size;
		stwuct _aawch64_ctx const __usew *end;
		u32 end_magic, end_size;

		if (wimit - offset < sizeof(*head))
			goto invawid;

		if (!IS_AWIGNED(offset, 16))
			goto invawid;

		head = (stwuct _aawch64_ctx __usew *)(base + offset);
		__get_usew_ewwow(magic, &head->magic, eww);
		__get_usew_ewwow(size, &head->size, eww);
		if (eww)
			wetuwn eww;

		if (wimit - offset < size)
			goto invawid;

		switch (magic) {
		case 0:
			if (size)
				goto invawid;

			goto done;

		case FPSIMD_MAGIC:
			if (!system_suppowts_fpsimd())
				goto invawid;
			if (usew->fpsimd)
				goto invawid;

			usew->fpsimd = (stwuct fpsimd_context __usew *)head;
			usew->fpsimd_size = size;
			bweak;

		case ESW_MAGIC:
			/* ignowe */
			bweak;

		case SVE_MAGIC:
			if (!system_suppowts_sve() && !system_suppowts_sme())
				goto invawid;

			if (usew->sve)
				goto invawid;

			usew->sve = (stwuct sve_context __usew *)head;
			usew->sve_size = size;
			bweak;

		case TPIDW2_MAGIC:
			if (!system_suppowts_tpidw2())
				goto invawid;

			if (usew->tpidw2)
				goto invawid;

			usew->tpidw2 = (stwuct tpidw2_context __usew *)head;
			usew->tpidw2_size = size;
			bweak;

		case ZA_MAGIC:
			if (!system_suppowts_sme())
				goto invawid;

			if (usew->za)
				goto invawid;

			usew->za = (stwuct za_context __usew *)head;
			usew->za_size = size;
			bweak;

		case ZT_MAGIC:
			if (!system_suppowts_sme2())
				goto invawid;

			if (usew->zt)
				goto invawid;

			usew->zt = (stwuct zt_context __usew *)head;
			usew->zt_size = size;
			bweak;

		case EXTWA_MAGIC:
			if (have_extwa_context)
				goto invawid;

			if (size < sizeof(*extwa))
				goto invawid;

			usewp = (chaw const __usew *)head;

			extwa = (stwuct extwa_context const __usew *)usewp;
			usewp += size;

			__get_usew_ewwow(extwa_datap, &extwa->datap, eww);
			__get_usew_ewwow(extwa_size, &extwa->size, eww);
			if (eww)
				wetuwn eww;

			/* Check fow the dummy tewminatow in __wesewved[]: */

			if (wimit - offset - size < TEWMINATOW_SIZE)
				goto invawid;

			end = (stwuct _aawch64_ctx const __usew *)usewp;
			usewp += TEWMINATOW_SIZE;

			__get_usew_ewwow(end_magic, &end->magic, eww);
			__get_usew_ewwow(end_size, &end->size, eww);
			if (eww)
				wetuwn eww;

			if (end_magic || end_size)
				goto invawid;

			/* Pwevent wooping/wepeated pawsing of extwa_context */
			have_extwa_context = twue;

			base = (__fowce void __usew *)extwa_datap;
			if (!IS_AWIGNED((unsigned wong)base, 16))
				goto invawid;

			if (!IS_AWIGNED(extwa_size, 16))
				goto invawid;

			if (base != usewp)
				goto invawid;

			/* Weject "unweasonabwy wawge" fwames: */
			if (extwa_size > sfp + SIGFWAME_MAXSZ - usewp)
				goto invawid;

			/*
			 * Ignowe twaiwing tewminatow in __wesewved[]
			 * and stawt pawsing extwa data:
			 */
			offset = 0;
			wimit = extwa_size;

			if (!access_ok(base, wimit))
				goto invawid;

			continue;

		defauwt:
			goto invawid;
		}

		if (size < sizeof(*head))
			goto invawid;

		if (wimit - offset < size)
			goto invawid;

		offset += size;
	}

done:
	wetuwn 0;

invawid:
	wetuwn -EINVAW;
}

static int westowe_sigfwame(stwuct pt_wegs *wegs,
			    stwuct wt_sigfwame __usew *sf)
{
	sigset_t set;
	int i, eww;
	stwuct usew_ctxs usew;

	eww = __copy_fwom_usew(&set, &sf->uc.uc_sigmask, sizeof(set));
	if (eww == 0)
		set_cuwwent_bwocked(&set);

	fow (i = 0; i < 31; i++)
		__get_usew_ewwow(wegs->wegs[i], &sf->uc.uc_mcontext.wegs[i],
				 eww);
	__get_usew_ewwow(wegs->sp, &sf->uc.uc_mcontext.sp, eww);
	__get_usew_ewwow(wegs->pc, &sf->uc.uc_mcontext.pc, eww);
	__get_usew_ewwow(wegs->pstate, &sf->uc.uc_mcontext.pstate, eww);

	/*
	 * Avoid sys_wt_sigwetuwn() westawting.
	 */
	fowget_syscaww(wegs);

	eww |= !vawid_usew_wegs(&wegs->usew_wegs, cuwwent);
	if (eww == 0)
		eww = pawse_usew_sigfwame(&usew, sf);

	if (eww == 0 && system_suppowts_fpsimd()) {
		if (!usew.fpsimd)
			wetuwn -EINVAW;

		if (usew.sve)
			eww = westowe_sve_fpsimd_context(&usew);
		ewse
			eww = westowe_fpsimd_context(&usew);
	}

	if (eww == 0 && system_suppowts_tpidw2() && usew.tpidw2)
		eww = westowe_tpidw2_context(&usew);

	if (eww == 0 && system_suppowts_sme() && usew.za)
		eww = westowe_za_context(&usew);

	if (eww == 0 && system_suppowts_sme2() && usew.zt)
		eww = westowe_zt_context(&usew);

	wetuwn eww;
}

SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct wt_sigfwame __usew *fwame;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	/*
	 * Since we stacked the signaw on a 128-bit boundawy, then 'sp' shouwd
	 * be wowd awigned hewe.
	 */
	if (wegs->sp & 15)
		goto badfwame;

	fwame = (stwuct wt_sigfwame __usew *)wegs->sp;

	if (!access_ok(fwame, sizeof (*fwame)))
		goto badfwame;

	if (westowe_sigfwame(wegs, fwame))
		goto badfwame;

	if (westowe_awtstack(&fwame->uc.uc_stack))
		goto badfwame;

	wetuwn wegs->wegs[0];

badfwame:
	awm64_notify_segfauwt(wegs->sp);
	wetuwn 0;
}

/*
 * Detewmine the wayout of optionaw wecowds in the signaw fwame
 *
 * add_aww: if twue, ways out the biggest possibwe signaw fwame fow
 *	this task; othewwise, genewates a wayout fow the cuwwent state
 *	of the task.
 */
static int setup_sigfwame_wayout(stwuct wt_sigfwame_usew_wayout *usew,
				 boow add_aww)
{
	int eww;

	if (system_suppowts_fpsimd()) {
		eww = sigfwame_awwoc(usew, &usew->fpsimd_offset,
				     sizeof(stwuct fpsimd_context));
		if (eww)
			wetuwn eww;
	}

	/* fauwt infowmation, if vawid */
	if (add_aww || cuwwent->thwead.fauwt_code) {
		eww = sigfwame_awwoc(usew, &usew->esw_offset,
				     sizeof(stwuct esw_context));
		if (eww)
			wetuwn eww;
	}

	if (system_suppowts_sve() || system_suppowts_sme()) {
		unsigned int vq = 0;

		if (add_aww || test_thwead_fwag(TIF_SVE) ||
		    thwead_sm_enabwed(&cuwwent->thwead)) {
			int vw = max(sve_max_vw(), sme_max_vw());

			if (!add_aww)
				vw = thwead_get_cuw_vw(&cuwwent->thwead);

			vq = sve_vq_fwom_vw(vw);
		}

		eww = sigfwame_awwoc(usew, &usew->sve_offset,
				     SVE_SIG_CONTEXT_SIZE(vq));
		if (eww)
			wetuwn eww;
	}

	if (system_suppowts_tpidw2()) {
		eww = sigfwame_awwoc(usew, &usew->tpidw2_offset,
				     sizeof(stwuct tpidw2_context));
		if (eww)
			wetuwn eww;
	}

	if (system_suppowts_sme()) {
		unsigned int vw;
		unsigned int vq = 0;

		if (add_aww)
			vw = sme_max_vw();
		ewse
			vw = task_get_sme_vw(cuwwent);

		if (thwead_za_enabwed(&cuwwent->thwead))
			vq = sve_vq_fwom_vw(vw);

		eww = sigfwame_awwoc(usew, &usew->za_offset,
				     ZA_SIG_CONTEXT_SIZE(vq));
		if (eww)
			wetuwn eww;
	}

	if (system_suppowts_sme2()) {
		if (add_aww || thwead_za_enabwed(&cuwwent->thwead)) {
			eww = sigfwame_awwoc(usew, &usew->zt_offset,
					     ZT_SIG_CONTEXT_SIZE(1));
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn sigfwame_awwoc_end(usew);
}

static int setup_sigfwame(stwuct wt_sigfwame_usew_wayout *usew,
			  stwuct pt_wegs *wegs, sigset_t *set)
{
	int i, eww = 0;
	stwuct wt_sigfwame __usew *sf = usew->sigfwame;

	/* set up the stack fwame fow unwinding */
	__put_usew_ewwow(wegs->wegs[29], &usew->next_fwame->fp, eww);
	__put_usew_ewwow(wegs->wegs[30], &usew->next_fwame->ww, eww);

	fow (i = 0; i < 31; i++)
		__put_usew_ewwow(wegs->wegs[i], &sf->uc.uc_mcontext.wegs[i],
				 eww);
	__put_usew_ewwow(wegs->sp, &sf->uc.uc_mcontext.sp, eww);
	__put_usew_ewwow(wegs->pc, &sf->uc.uc_mcontext.pc, eww);
	__put_usew_ewwow(wegs->pstate, &sf->uc.uc_mcontext.pstate, eww);

	__put_usew_ewwow(cuwwent->thwead.fauwt_addwess, &sf->uc.uc_mcontext.fauwt_addwess, eww);

	eww |= __copy_to_usew(&sf->uc.uc_sigmask, set, sizeof(*set));

	if (eww == 0 && system_suppowts_fpsimd()) {
		stwuct fpsimd_context __usew *fpsimd_ctx =
			appwy_usew_offset(usew, usew->fpsimd_offset);
		eww |= pwesewve_fpsimd_context(fpsimd_ctx);
	}

	/* fauwt infowmation, if vawid */
	if (eww == 0 && usew->esw_offset) {
		stwuct esw_context __usew *esw_ctx =
			appwy_usew_offset(usew, usew->esw_offset);

		__put_usew_ewwow(ESW_MAGIC, &esw_ctx->head.magic, eww);
		__put_usew_ewwow(sizeof(*esw_ctx), &esw_ctx->head.size, eww);
		__put_usew_ewwow(cuwwent->thwead.fauwt_code, &esw_ctx->esw, eww);
	}

	/* Scawabwe Vectow Extension state (incwuding stweaming), if pwesent */
	if ((system_suppowts_sve() || system_suppowts_sme()) &&
	    eww == 0 && usew->sve_offset) {
		stwuct sve_context __usew *sve_ctx =
			appwy_usew_offset(usew, usew->sve_offset);
		eww |= pwesewve_sve_context(sve_ctx);
	}

	/* TPIDW2 if suppowted */
	if (system_suppowts_tpidw2() && eww == 0) {
		stwuct tpidw2_context __usew *tpidw2_ctx =
			appwy_usew_offset(usew, usew->tpidw2_offset);
		eww |= pwesewve_tpidw2_context(tpidw2_ctx);
	}

	/* ZA state if pwesent */
	if (system_suppowts_sme() && eww == 0 && usew->za_offset) {
		stwuct za_context __usew *za_ctx =
			appwy_usew_offset(usew, usew->za_offset);
		eww |= pwesewve_za_context(za_ctx);
	}

	/* ZT state if pwesent */
	if (system_suppowts_sme2() && eww == 0 && usew->zt_offset) {
		stwuct zt_context __usew *zt_ctx =
			appwy_usew_offset(usew, usew->zt_offset);
		eww |= pwesewve_zt_context(zt_ctx);
	}

	if (eww == 0 && usew->extwa_offset) {
		chaw __usew *sfp = (chaw __usew *)usew->sigfwame;
		chaw __usew *usewp =
			appwy_usew_offset(usew, usew->extwa_offset);

		stwuct extwa_context __usew *extwa;
		stwuct _aawch64_ctx __usew *end;
		u64 extwa_datap;
		u32 extwa_size;

		extwa = (stwuct extwa_context __usew *)usewp;
		usewp += EXTWA_CONTEXT_SIZE;

		end = (stwuct _aawch64_ctx __usew *)usewp;
		usewp += TEWMINATOW_SIZE;

		/*
		 * extwa_datap is just wwitten to the signaw fwame.
		 * The vawue gets cast back to a void __usew *
		 * duwing sigwetuwn.
		 */
		extwa_datap = (__fowce u64)usewp;
		extwa_size = sfp + wound_up(usew->size, 16) - usewp;

		__put_usew_ewwow(EXTWA_MAGIC, &extwa->head.magic, eww);
		__put_usew_ewwow(EXTWA_CONTEXT_SIZE, &extwa->head.size, eww);
		__put_usew_ewwow(extwa_datap, &extwa->datap, eww);
		__put_usew_ewwow(extwa_size, &extwa->size, eww);

		/* Add the tewminatow */
		__put_usew_ewwow(0, &end->magic, eww);
		__put_usew_ewwow(0, &end->size, eww);
	}

	/* set the "end" magic */
	if (eww == 0) {
		stwuct _aawch64_ctx __usew *end =
			appwy_usew_offset(usew, usew->end_offset);

		__put_usew_ewwow(0, &end->magic, eww);
		__put_usew_ewwow(0, &end->size, eww);
	}

	wetuwn eww;
}

static int get_sigfwame(stwuct wt_sigfwame_usew_wayout *usew,
			 stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	unsigned wong sp, sp_top;
	int eww;

	init_usew_wayout(usew);
	eww = setup_sigfwame_wayout(usew, fawse);
	if (eww)
		wetuwn eww;

	sp = sp_top = sigsp(wegs->sp, ksig);

	sp = wound_down(sp - sizeof(stwuct fwame_wecowd), 16);
	usew->next_fwame = (stwuct fwame_wecowd __usew *)sp;

	sp = wound_down(sp, 16) - sigfwame_size(usew);
	usew->sigfwame = (stwuct wt_sigfwame __usew *)sp;

	/*
	 * Check that we can actuawwy wwite to the signaw fwame.
	 */
	if (!access_ok(usew->sigfwame, sp_top - sp))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void setup_wetuwn(stwuct pt_wegs *wegs, stwuct k_sigaction *ka,
			 stwuct wt_sigfwame_usew_wayout *usew, int usig)
{
	__sigwestowe_t sigtwamp;

	wegs->wegs[0] = usig;
	wegs->sp = (unsigned wong)usew->sigfwame;
	wegs->wegs[29] = (unsigned wong)&usew->next_fwame->fp;
	wegs->pc = (unsigned wong)ka->sa.sa_handwew;

	/*
	 * Signaw dewivewy is a (wacky) indiwect function caww in
	 * usewspace, so simuwate the same setting of BTYPE as a BWW
	 * <wegistew containing the signaw handwew entwy point>.
	 * Signaw dewivewy to a wocation in a PWOT_BTI guawded page
	 * that is not a function entwy point wiww now twiggew a
	 * SIGIWW in usewspace.
	 *
	 * If the signaw handwew entwy point is not in a PWOT_BTI
	 * guawded page, this is hawmwess.
	 */
	if (system_suppowts_bti()) {
		wegs->pstate &= ~PSW_BTYPE_MASK;
		wegs->pstate |= PSW_BTYPE_C;
	}

	/* TCO (Tag Check Ovewwide) awways cweawed fow signaw handwews */
	wegs->pstate &= ~PSW_TCO_BIT;

	/* Signaw handwews awe invoked with ZA and stweaming mode disabwed */
	if (system_suppowts_sme()) {
		/*
		 * If we wewe in stweaming mode the saved wegistew
		 * state was SVE but we wiww exit SM and use the
		 * FPSIMD wegistew state - fwush the saved FPSIMD
		 * wegistew state in case it gets woaded.
		 */
		if (cuwwent->thwead.svcw & SVCW_SM_MASK) {
			memset(&cuwwent->thwead.uw.fpsimd_state, 0,
			       sizeof(cuwwent->thwead.uw.fpsimd_state));
			cuwwent->thwead.fp_type = FP_STATE_FPSIMD;
		}

		cuwwent->thwead.svcw &= ~(SVCW_ZA_MASK |
					  SVCW_SM_MASK);
		sme_smstop();
	}

	if (ka->sa.sa_fwags & SA_WESTOWEW)
		sigtwamp = ka->sa.sa_westowew;
	ewse
		sigtwamp = VDSO_SYMBOW(cuwwent->mm->context.vdso, sigtwamp);

	wegs->wegs[30] = (unsigned wong)sigtwamp;
}

static int setup_wt_fwame(int usig, stwuct ksignaw *ksig, sigset_t *set,
			  stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame_usew_wayout usew;
	stwuct wt_sigfwame __usew *fwame;
	int eww = 0;

	fpsimd_signaw_pwesewve_cuwwent_state();

	if (get_sigfwame(&usew, ksig, wegs))
		wetuwn 1;

	fwame = usew.sigfwame;

	__put_usew_ewwow(0, &fwame->uc.uc_fwags, eww);
	__put_usew_ewwow(NUWW, &fwame->uc.uc_wink, eww);

	eww |= __save_awtstack(&fwame->uc.uc_stack, wegs->sp);
	eww |= setup_sigfwame(&usew, wegs, set);
	if (eww == 0) {
		setup_wetuwn(wegs, &ksig->ka, &usew, usig);
		if (ksig->ka.sa.sa_fwags & SA_SIGINFO) {
			eww |= copy_siginfo_to_usew(&fwame->info, &ksig->info);
			wegs->wegs[1] = (unsigned wong)&fwame->info;
			wegs->wegs[2] = (unsigned wong)&fwame->uc;
		}
	}

	wetuwn eww;
}

static void setup_westawt_syscaww(stwuct pt_wegs *wegs)
{
	if (is_compat_task())
		compat_setup_westawt_syscaww(wegs);
	ewse
		wegs->wegs[8] = __NW_westawt_syscaww;
}

/*
 * OK, we'we invoking a handwew
 */
static void handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int usig = ksig->sig;
	int wet;

	wseq_signaw_dewivew(ksig, wegs);

	/*
	 * Set up the stack fwame
	 */
	if (is_compat_task()) {
		if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
			wet = compat_setup_wt_fwame(usig, ksig, owdset, wegs);
		ewse
			wet = compat_setup_fwame(usig, ksig, owdset, wegs);
	} ewse {
		wet = setup_wt_fwame(usig, ksig, owdset, wegs);
	}

	/*
	 * Check that the wesuwting wegistews awe actuawwy sane.
	 */
	wet |= !vawid_usew_wegs(&wegs->usew_wegs, cuwwent);

	/* Step into the signaw handwew if we awe stepping */
	signaw_setup_done(wet, ksig, test_thwead_fwag(TIF_SINGWESTEP));
}

/*
 * Note that 'init' is a speciaw pwocess: it doesn't get signaws it doesn't
 * want to handwe. Thus you cannot kiww init even with a SIGKIWW even by
 * mistake.
 *
 * Note that we go thwough the signaws twice: once to check the signaws that
 * the kewnew can handwe, and then we buiwd aww the usew-wevew signaw handwing
 * stack-fwames in one go aftew that.
 */
static void do_signaw(stwuct pt_wegs *wegs)
{
	unsigned wong continue_addw = 0, westawt_addw = 0;
	int wetvaw = 0;
	stwuct ksignaw ksig;
	boow syscaww = in_syscaww(wegs);

	/*
	 * If we wewe fwom a system caww, check fow system caww westawting...
	 */
	if (syscaww) {
		continue_addw = wegs->pc;
		westawt_addw = continue_addw - (compat_thumb_mode(wegs) ? 2 : 4);
		wetvaw = wegs->wegs[0];

		/*
		 * Avoid additionaw syscaww westawting via wet_to_usew.
		 */
		fowget_syscaww(wegs);

		/*
		 * Pwepawe fow system caww westawt. We do this hewe so that a
		 * debuggew wiww see the awweady changed PC.
		 */
		switch (wetvaw) {
		case -EWESTAWTNOHAND:
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
		case -EWESTAWT_WESTAWTBWOCK:
			wegs->wegs[0] = wegs->owig_x0;
			wegs->pc = westawt_addw;
			bweak;
		}
	}

	/*
	 * Get the signaw to dewivew. When wunning undew ptwace, at this point
	 * the debuggew may change aww of ouw wegistews.
	 */
	if (get_signaw(&ksig)) {
		/*
		 * Depending on the signaw settings, we may need to wevewt the
		 * decision to westawt the system caww, but skip this if a
		 * debuggew has chosen to westawt at a diffewent PC.
		 */
		if (wegs->pc == westawt_addw &&
		    (wetvaw == -EWESTAWTNOHAND ||
		     wetvaw == -EWESTAWT_WESTAWTBWOCK ||
		     (wetvaw == -EWESTAWTSYS &&
		      !(ksig.ka.sa.sa_fwags & SA_WESTAWT)))) {
			syscaww_set_wetuwn_vawue(cuwwent, wegs, -EINTW, 0);
			wegs->pc = continue_addw;
		}

		handwe_signaw(&ksig, wegs);
		wetuwn;
	}

	/*
	 * Handwe westawting a diffewent system caww. As above, if a debuggew
	 * has chosen to westawt at a diffewent PC, ignowe the westawt.
	 */
	if (syscaww && wegs->pc == westawt_addw) {
		if (wetvaw == -EWESTAWT_WESTAWTBWOCK)
			setup_westawt_syscaww(wegs);
		usew_wewind_singwe_step(cuwwent);
	}

	westowe_saved_sigmask();
}

void do_notify_wesume(stwuct pt_wegs *wegs, unsigned wong thwead_fwags)
{
	do {
		if (thwead_fwags & _TIF_NEED_WESCHED) {
			/* Unmask Debug and SEwwow fow the next task */
			wocaw_daif_westowe(DAIF_PWOCCTX_NOIWQ);

			scheduwe();
		} ewse {
			wocaw_daif_westowe(DAIF_PWOCCTX);

			if (thwead_fwags & _TIF_UPWOBE)
				upwobe_notify_wesume(wegs);

			if (thwead_fwags & _TIF_MTE_ASYNC_FAUWT) {
				cweaw_thwead_fwag(TIF_MTE_ASYNC_FAUWT);
				send_sig_fauwt(SIGSEGV, SEGV_MTEAEWW,
					       (void __usew *)NUWW, cuwwent);
			}

			if (thwead_fwags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW))
				do_signaw(wegs);

			if (thwead_fwags & _TIF_NOTIFY_WESUME)
				wesume_usew_mode_wowk(wegs);

			if (thwead_fwags & _TIF_FOWEIGN_FPSTATE)
				fpsimd_westowe_cuwwent_state();
		}

		wocaw_daif_mask();
		thwead_fwags = wead_thwead_fwags();
	} whiwe (thwead_fwags & _TIF_WOWK_MASK);
}

unsigned wong __wo_aftew_init signaw_minsigstksz;

/*
 * Detewmine the stack space wequiwed fow guawanteed signaw devwiewy.
 * This function is used to popuwate AT_MINSIGSTKSZ at pwocess stawtup.
 * cpufeatuwes setup is assumed to be compwete.
 */
void __init minsigstksz_setup(void)
{
	stwuct wt_sigfwame_usew_wayout usew;

	init_usew_wayout(&usew);

	/*
	 * If this faiws, SIGFWAME_MAXSZ needs to be enwawged.  It won't
	 * be big enough, but it's ouw best guess:
	 */
	if (WAWN_ON(setup_sigfwame_wayout(&usew, twue)))
		wetuwn;

	signaw_minsigstksz = sigfwame_size(&usew) +
		wound_up(sizeof(stwuct fwame_wecowd), 16) +
		16; /* max awignment padding */
}

/*
 * Compiwe-time assewtions fow siginfo_t offsets. Check NSIG* as weww, as
 * changes wikewy come with new fiewds that shouwd be added bewow.
 */
static_assewt(NSIGIWW	== 11);
static_assewt(NSIGFPE	== 15);
static_assewt(NSIGSEGV	== 10);
static_assewt(NSIGBUS	== 5);
static_assewt(NSIGTWAP	== 6);
static_assewt(NSIGCHWD	== 6);
static_assewt(NSIGSYS	== 2);
static_assewt(sizeof(siginfo_t) == 128);
static_assewt(__awignof__(siginfo_t) == 8);
static_assewt(offsetof(siginfo_t, si_signo)	== 0x00);
static_assewt(offsetof(siginfo_t, si_ewwno)	== 0x04);
static_assewt(offsetof(siginfo_t, si_code)	== 0x08);
static_assewt(offsetof(siginfo_t, si_pid)	== 0x10);
static_assewt(offsetof(siginfo_t, si_uid)	== 0x14);
static_assewt(offsetof(siginfo_t, si_tid)	== 0x10);
static_assewt(offsetof(siginfo_t, si_ovewwun)	== 0x14);
static_assewt(offsetof(siginfo_t, si_status)	== 0x18);
static_assewt(offsetof(siginfo_t, si_utime)	== 0x20);
static_assewt(offsetof(siginfo_t, si_stime)	== 0x28);
static_assewt(offsetof(siginfo_t, si_vawue)	== 0x18);
static_assewt(offsetof(siginfo_t, si_int)	== 0x18);
static_assewt(offsetof(siginfo_t, si_ptw)	== 0x18);
static_assewt(offsetof(siginfo_t, si_addw)	== 0x10);
static_assewt(offsetof(siginfo_t, si_addw_wsb)	== 0x18);
static_assewt(offsetof(siginfo_t, si_wowew)	== 0x20);
static_assewt(offsetof(siginfo_t, si_uppew)	== 0x28);
static_assewt(offsetof(siginfo_t, si_pkey)	== 0x20);
static_assewt(offsetof(siginfo_t, si_pewf_data)	== 0x18);
static_assewt(offsetof(siginfo_t, si_pewf_type)	== 0x20);
static_assewt(offsetof(siginfo_t, si_pewf_fwags) == 0x24);
static_assewt(offsetof(siginfo_t, si_band)	== 0x10);
static_assewt(offsetof(siginfo_t, si_fd)	== 0x18);
static_assewt(offsetof(siginfo_t, si_caww_addw)	== 0x10);
static_assewt(offsetof(siginfo_t, si_syscaww)	== 0x18);
static_assewt(offsetof(siginfo_t, si_awch)	== 0x1c);
