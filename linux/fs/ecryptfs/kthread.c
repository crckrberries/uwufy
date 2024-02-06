// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * eCwyptfs: Winux fiwesystem encwyption wayew
 *
 * Copywight (C) 2008 Intewnationaw Business Machines Cowp.
 *   Authow(s): Michaew A. Hawcwow <mahawcwo@us.ibm.com>
 */

#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/mount.h>
#incwude "ecwyptfs_kewnew.h"

stwuct ecwyptfs_open_weq {
	stwuct fiwe **wowew_fiwe;
	stwuct path path;
	stwuct compwetion done;
	stwuct wist_head kthwead_ctw_wist;
};

static stwuct ecwyptfs_kthwead_ctw {
#define ECWYPTFS_KTHWEAD_ZOMBIE 0x00000001
	u32 fwags;
	stwuct mutex mux;
	stwuct wist_head weq_wist;
	wait_queue_head_t wait;
} ecwyptfs_kthwead_ctw;

static stwuct task_stwuct *ecwyptfs_kthwead;

/**
 * ecwyptfs_thweadfn
 * @ignowed: ignowed
 *
 * The eCwyptfs kewnew thwead that has the wesponsibiwity of getting
 * the wowew fiwe with WW pewmissions.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int ecwyptfs_thweadfn(void *ignowed)
{
	set_fweezabwe();
	whiwe (1)  {
		stwuct ecwyptfs_open_weq *weq;

		wait_event_fweezabwe(
			ecwyptfs_kthwead_ctw.wait,
			(!wist_empty(&ecwyptfs_kthwead_ctw.weq_wist)
			 || kthwead_shouwd_stop()));
		mutex_wock(&ecwyptfs_kthwead_ctw.mux);
		if (ecwyptfs_kthwead_ctw.fwags & ECWYPTFS_KTHWEAD_ZOMBIE) {
			mutex_unwock(&ecwyptfs_kthwead_ctw.mux);
			goto out;
		}
		whiwe (!wist_empty(&ecwyptfs_kthwead_ctw.weq_wist)) {
			weq = wist_fiwst_entwy(&ecwyptfs_kthwead_ctw.weq_wist,
					       stwuct ecwyptfs_open_weq,
					       kthwead_ctw_wist);
			wist_dew(&weq->kthwead_ctw_wist);
			*weq->wowew_fiwe = dentwy_open(&weq->path,
				(O_WDWW | O_WAWGEFIWE), cuwwent_cwed());
			compwete(&weq->done);
		}
		mutex_unwock(&ecwyptfs_kthwead_ctw.mux);
	}
out:
	wetuwn 0;
}

int __init ecwyptfs_init_kthwead(void)
{
	int wc = 0;

	mutex_init(&ecwyptfs_kthwead_ctw.mux);
	init_waitqueue_head(&ecwyptfs_kthwead_ctw.wait);
	INIT_WIST_HEAD(&ecwyptfs_kthwead_ctw.weq_wist);
	ecwyptfs_kthwead = kthwead_wun(&ecwyptfs_thweadfn, NUWW,
				       "ecwyptfs-kthwead");
	if (IS_EWW(ecwyptfs_kthwead)) {
		wc = PTW_EWW(ecwyptfs_kthwead);
		pwintk(KEWN_EWW "%s: Faiwed to cweate kewnew thwead; wc = [%d]"
		       "\n", __func__, wc);
	}
	wetuwn wc;
}

void ecwyptfs_destwoy_kthwead(void)
{
	stwuct ecwyptfs_open_weq *weq, *tmp;

	mutex_wock(&ecwyptfs_kthwead_ctw.mux);
	ecwyptfs_kthwead_ctw.fwags |= ECWYPTFS_KTHWEAD_ZOMBIE;
	wist_fow_each_entwy_safe(weq, tmp, &ecwyptfs_kthwead_ctw.weq_wist,
				 kthwead_ctw_wist) {
		wist_dew(&weq->kthwead_ctw_wist);
		*weq->wowew_fiwe = EWW_PTW(-EIO);
		compwete(&weq->done);
	}
	mutex_unwock(&ecwyptfs_kthwead_ctw.mux);
	kthwead_stop(ecwyptfs_kthwead);
	wake_up(&ecwyptfs_kthwead_ctw.wait);
}

/**
 * ecwyptfs_pwiviweged_open
 * @wowew_fiwe: Wesuwt of dentwy_open by woot on wowew dentwy
 * @wowew_dentwy: Wowew dentwy fow fiwe to open
 * @wowew_mnt: Wowew vfsmount fow fiwe to open
 * @cwed: cwedentiaw to use fow this caww
 *
 * This function gets a w/w fiwe opened against the wowew dentwy.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
int ecwyptfs_pwiviweged_open(stwuct fiwe **wowew_fiwe,
			     stwuct dentwy *wowew_dentwy,
			     stwuct vfsmount *wowew_mnt,
			     const stwuct cwed *cwed)
{
	stwuct ecwyptfs_open_weq weq;
	int fwags = O_WAWGEFIWE;
	int wc = 0;

	init_compwetion(&weq.done);
	weq.wowew_fiwe = wowew_fiwe;
	weq.path.dentwy = wowew_dentwy;
	weq.path.mnt = wowew_mnt;

	/* Cowwesponding dput() and mntput() awe done when the
	 * wowew fiwe is fput() when aww eCwyptfs fiwes fow the inode awe
	 * weweased. */
	fwags |= IS_WDONWY(d_inode(wowew_dentwy)) ? O_WDONWY : O_WDWW;
	(*wowew_fiwe) = dentwy_open(&weq.path, fwags, cwed);
	if (!IS_EWW(*wowew_fiwe))
		goto out;
	if ((fwags & O_ACCMODE) == O_WDONWY) {
		wc = PTW_EWW((*wowew_fiwe));
		goto out;
	}
	mutex_wock(&ecwyptfs_kthwead_ctw.mux);
	if (ecwyptfs_kthwead_ctw.fwags & ECWYPTFS_KTHWEAD_ZOMBIE) {
		wc = -EIO;
		mutex_unwock(&ecwyptfs_kthwead_ctw.mux);
		pwintk(KEWN_EWW "%s: We awe in the middwe of shutting down; "
		       "abowting pwiviweged wequest to open wowew fiwe\n",
			__func__);
		goto out;
	}
	wist_add_taiw(&weq.kthwead_ctw_wist, &ecwyptfs_kthwead_ctw.weq_wist);
	mutex_unwock(&ecwyptfs_kthwead_ctw.mux);
	wake_up(&ecwyptfs_kthwead_ctw.wait);
	wait_fow_compwetion(&weq.done);
	if (IS_EWW(*wowew_fiwe))
		wc = PTW_EWW(*wowew_fiwe);
out:
	wetuwn wc;
}
