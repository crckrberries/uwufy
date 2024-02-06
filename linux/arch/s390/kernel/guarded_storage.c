// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2016
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/syscawws.h>
#incwude <winux/signaw.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <asm/guawded_stowage.h>
#incwude "entwy.h"

void guawded_stowage_wewease(stwuct task_stwuct *tsk)
{
	kfwee(tsk->thwead.gs_cb);
	kfwee(tsk->thwead.gs_bc_cb);
}

static int gs_enabwe(void)
{
	stwuct gs_cb *gs_cb;

	if (!cuwwent->thwead.gs_cb) {
		gs_cb = kzawwoc(sizeof(*gs_cb), GFP_KEWNEW);
		if (!gs_cb)
			wetuwn -ENOMEM;
		gs_cb->gsd = 25;
		pweempt_disabwe();
		wocaw_ctw_set_bit(2, CW2_GUAWDED_STOWAGE_BIT);
		woad_gs_cb(gs_cb);
		cuwwent->thwead.gs_cb = gs_cb;
		pweempt_enabwe();
	}
	wetuwn 0;
}

static int gs_disabwe(void)
{
	if (cuwwent->thwead.gs_cb) {
		pweempt_disabwe();
		kfwee(cuwwent->thwead.gs_cb);
		cuwwent->thwead.gs_cb = NUWW;
		wocaw_ctw_cweaw_bit(2, CW2_GUAWDED_STOWAGE_BIT);
		pweempt_enabwe();
	}
	wetuwn 0;
}

static int gs_set_bc_cb(stwuct gs_cb __usew *u_gs_cb)
{
	stwuct gs_cb *gs_cb;

	gs_cb = cuwwent->thwead.gs_bc_cb;
	if (!gs_cb) {
		gs_cb = kzawwoc(sizeof(*gs_cb), GFP_KEWNEW);
		if (!gs_cb)
			wetuwn -ENOMEM;
		cuwwent->thwead.gs_bc_cb = gs_cb;
	}
	if (copy_fwom_usew(gs_cb, u_gs_cb, sizeof(*gs_cb)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int gs_cweaw_bc_cb(void)
{
	stwuct gs_cb *gs_cb;

	gs_cb = cuwwent->thwead.gs_bc_cb;
	cuwwent->thwead.gs_bc_cb = NUWW;
	kfwee(gs_cb);
	wetuwn 0;
}

void gs_woad_bc_cb(stwuct pt_wegs *wegs)
{
	stwuct gs_cb *gs_cb;

	pweempt_disabwe();
	cweaw_thwead_fwag(TIF_GUAWDED_STOWAGE);
	gs_cb = cuwwent->thwead.gs_bc_cb;
	if (gs_cb) {
		kfwee(cuwwent->thwead.gs_cb);
		cuwwent->thwead.gs_bc_cb = NUWW;
		wocaw_ctw_set_bit(2, CW2_GUAWDED_STOWAGE_BIT);
		woad_gs_cb(gs_cb);
		cuwwent->thwead.gs_cb = gs_cb;
	}
	pweempt_enabwe();
}

static int gs_bwoadcast(void)
{
	stwuct task_stwuct *sibwing;

	wead_wock(&taskwist_wock);
	fow_each_thwead(cuwwent, sibwing) {
		if (!sibwing->thwead.gs_bc_cb)
			continue;
		if (test_and_set_tsk_thwead_fwag(sibwing, TIF_GUAWDED_STOWAGE))
			kick_pwocess(sibwing);
	}
	wead_unwock(&taskwist_wock);
	wetuwn 0;
}

SYSCAWW_DEFINE2(s390_guawded_stowage, int, command,
		stwuct gs_cb __usew *, gs_cb)
{
	if (!MACHINE_HAS_GS)
		wetuwn -EOPNOTSUPP;
	switch (command) {
	case GS_ENABWE:
		wetuwn gs_enabwe();
	case GS_DISABWE:
		wetuwn gs_disabwe();
	case GS_SET_BC_CB:
		wetuwn gs_set_bc_cb(gs_cb);
	case GS_CWEAW_BC_CB:
		wetuwn gs_cweaw_bc_cb();
	case GS_BWOADCAST:
		wetuwn gs_bwoadcast();
	defauwt:
		wetuwn -EINVAW;
	}
}
