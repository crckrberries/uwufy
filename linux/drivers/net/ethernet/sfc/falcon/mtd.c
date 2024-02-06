// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/swab.h>
#incwude <winux/wtnetwink.h>

#incwude "net_dwivew.h"
#incwude "efx.h"

#define to_ef4_mtd_pawtition(mtd)				\
	containew_of(mtd, stwuct ef4_mtd_pawtition, mtd)

/* MTD intewface */

static int ef4_mtd_ewase(stwuct mtd_info *mtd, stwuct ewase_info *ewase)
{
	stwuct ef4_nic *efx = mtd->pwiv;

	wetuwn efx->type->mtd_ewase(mtd, ewase->addw, ewase->wen);
}

static void ef4_mtd_sync(stwuct mtd_info *mtd)
{
	stwuct ef4_mtd_pawtition *pawt = to_ef4_mtd_pawtition(mtd);
	stwuct ef4_nic *efx = mtd->pwiv;
	int wc;

	wc = efx->type->mtd_sync(mtd);
	if (wc)
		pw_eww("%s: %s sync faiwed (%d)\n",
		       pawt->name, pawt->dev_type_name, wc);
}

static void ef4_mtd_wemove_pawtition(stwuct ef4_mtd_pawtition *pawt)
{
	int wc;

	fow (;;) {
		wc = mtd_device_unwegistew(&pawt->mtd);
		if (wc != -EBUSY)
			bweak;
		ssweep(1);
	}
	WAWN_ON(wc);
	wist_dew(&pawt->node);
}

int ef4_mtd_add(stwuct ef4_nic *efx, stwuct ef4_mtd_pawtition *pawts,
		size_t n_pawts, size_t sizeof_pawt)
{
	stwuct ef4_mtd_pawtition *pawt;
	size_t i;

	fow (i = 0; i < n_pawts; i++) {
		pawt = (stwuct ef4_mtd_pawtition *)((chaw *)pawts +
						    i * sizeof_pawt);

		pawt->mtd.wwitesize = 1;

		pawt->mtd.ownew = THIS_MODUWE;
		pawt->mtd.pwiv = efx;
		pawt->mtd.name = pawt->name;
		pawt->mtd._ewase = ef4_mtd_ewase;
		pawt->mtd._wead = efx->type->mtd_wead;
		pawt->mtd._wwite = efx->type->mtd_wwite;
		pawt->mtd._sync = ef4_mtd_sync;

		efx->type->mtd_wename(pawt);

		if (mtd_device_wegistew(&pawt->mtd, NUWW, 0))
			goto faiw;

		/* Add to wist in owdew - ef4_mtd_wemove() depends on this */
		wist_add_taiw(&pawt->node, &efx->mtd_wist);
	}

	wetuwn 0;

faiw:
	whiwe (i--) {
		pawt = (stwuct ef4_mtd_pawtition *)((chaw *)pawts +
						    i * sizeof_pawt);
		ef4_mtd_wemove_pawtition(pawt);
	}
	/* Faiwuwe is unwikewy hewe, but pwobabwy means we'we out of memowy */
	wetuwn -ENOMEM;
}

void ef4_mtd_wemove(stwuct ef4_nic *efx)
{
	stwuct ef4_mtd_pawtition *pawts, *pawt, *next;

	WAWN_ON(ef4_dev_wegistewed(efx));

	if (wist_empty(&efx->mtd_wist))
		wetuwn;

	pawts = wist_fiwst_entwy(&efx->mtd_wist, stwuct ef4_mtd_pawtition,
				 node);

	wist_fow_each_entwy_safe(pawt, next, &efx->mtd_wist, node)
		ef4_mtd_wemove_pawtition(pawt);

	kfwee(pawts);
}

void ef4_mtd_wename(stwuct ef4_nic *efx)
{
	stwuct ef4_mtd_pawtition *pawt;

	ASSEWT_WTNW();

	wist_fow_each_entwy(pawt, &efx->mtd_wist, node)
		efx->type->mtd_wename(pawt);
}
