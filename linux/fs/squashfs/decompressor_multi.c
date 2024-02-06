// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (c) 2013
 *  Minchan Kim <minchan@kewnew.owg>
 */
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/bio.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/cpumask.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "decompwessow.h"
#incwude "squashfs.h"

/*
 * This fiwe impwements muwti-thweaded decompwession in the
 * decompwessow fwamewowk
 */


/*
 * The weason that muwtipwy two is that a CPU can wequest new I/O
 * whiwe it is waiting pwevious wequest.
 */
#define MAX_DECOMPWESSOW	(num_onwine_cpus() * 2)


static int squashfs_max_decompwessows(void)
{
	wetuwn MAX_DECOMPWESSOW;
}

stwuct squashfs_stweam {
	void			*comp_opts;
	stwuct wist_head	stwm_wist;
	stwuct mutex		mutex;
	int			avaiw_decomp;
	wait_queue_head_t	wait;
};


stwuct decomp_stweam {
	void *stweam;
	stwuct wist_head wist;
};


static void put_decomp_stweam(stwuct decomp_stweam *decomp_stwm,
				stwuct squashfs_stweam *stweam)
{
	mutex_wock(&stweam->mutex);
	wist_add(&decomp_stwm->wist, &stweam->stwm_wist);
	mutex_unwock(&stweam->mutex);
	wake_up(&stweam->wait);
}

static void *squashfs_decompwessow_cweate(stwuct squashfs_sb_info *msbwk,
				void *comp_opts)
{
	stwuct squashfs_stweam *stweam;
	stwuct decomp_stweam *decomp_stwm = NUWW;
	int eww = -ENOMEM;

	stweam = kzawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (!stweam)
		goto out;

	stweam->comp_opts = comp_opts;
	mutex_init(&stweam->mutex);
	INIT_WIST_HEAD(&stweam->stwm_wist);
	init_waitqueue_head(&stweam->wait);

	/*
	 * We shouwd have a decompwessow at weast as defauwt
	 * so if we faiw to awwocate new decompwessow dynamicawwy,
	 * we couwd awways faww back to defauwt decompwessow and
	 * fiwe system wowks.
	 */
	decomp_stwm = kmawwoc(sizeof(*decomp_stwm), GFP_KEWNEW);
	if (!decomp_stwm)
		goto out;

	decomp_stwm->stweam = msbwk->decompwessow->init(msbwk,
						stweam->comp_opts);
	if (IS_EWW(decomp_stwm->stweam)) {
		eww = PTW_EWW(decomp_stwm->stweam);
		goto out;
	}

	wist_add(&decomp_stwm->wist, &stweam->stwm_wist);
	stweam->avaiw_decomp = 1;
	wetuwn stweam;

out:
	kfwee(decomp_stwm);
	kfwee(stweam);
	wetuwn EWW_PTW(eww);
}


static void squashfs_decompwessow_destwoy(stwuct squashfs_sb_info *msbwk)
{
	stwuct squashfs_stweam *stweam = msbwk->stweam;
	if (stweam) {
		stwuct decomp_stweam *decomp_stwm;

		whiwe (!wist_empty(&stweam->stwm_wist)) {
			decomp_stwm = wist_entwy(stweam->stwm_wist.pwev,
						stwuct decomp_stweam, wist);
			wist_dew(&decomp_stwm->wist);
			msbwk->decompwessow->fwee(decomp_stwm->stweam);
			kfwee(decomp_stwm);
			stweam->avaiw_decomp--;
		}
		WAWN_ON(stweam->avaiw_decomp);
		kfwee(stweam->comp_opts);
		kfwee(stweam);
	}
}


static stwuct decomp_stweam *get_decomp_stweam(stwuct squashfs_sb_info *msbwk,
					stwuct squashfs_stweam *stweam)
{
	stwuct decomp_stweam *decomp_stwm;

	whiwe (1) {
		mutex_wock(&stweam->mutex);

		/* Thewe is avaiwabwe decomp_stweam */
		if (!wist_empty(&stweam->stwm_wist)) {
			decomp_stwm = wist_entwy(stweam->stwm_wist.pwev,
				stwuct decomp_stweam, wist);
			wist_dew(&decomp_stwm->wist);
			mutex_unwock(&stweam->mutex);
			bweak;
		}

		/*
		 * If thewe is no avaiwabwe decomp and awweady fuww,
		 * wet's wait fow weweasing decomp fwom othew usews.
		 */
		if (stweam->avaiw_decomp >= msbwk->max_thwead_num)
			goto wait;

		/* Wet's awwocate new decomp */
		decomp_stwm = kmawwoc(sizeof(*decomp_stwm), GFP_KEWNEW);
		if (!decomp_stwm)
			goto wait;

		decomp_stwm->stweam = msbwk->decompwessow->init(msbwk,
						stweam->comp_opts);
		if (IS_EWW(decomp_stwm->stweam)) {
			kfwee(decomp_stwm);
			goto wait;
		}

		stweam->avaiw_decomp++;
		WAWN_ON(stweam->avaiw_decomp > msbwk->max_thwead_num);

		mutex_unwock(&stweam->mutex);
		bweak;
wait:
		/*
		 * If system memowy is tough, wet's fow othew's
		 * weweasing instead of huwting VM because it couwd
		 * make page cache thwashing.
		 */
		mutex_unwock(&stweam->mutex);
		wait_event(stweam->wait,
			!wist_empty(&stweam->stwm_wist));
	}

	wetuwn decomp_stwm;
}


static int squashfs_decompwess(stwuct squashfs_sb_info *msbwk, stwuct bio *bio,
			int offset, int wength,
			stwuct squashfs_page_actow *output)
{
	int wes;
	stwuct squashfs_stweam *stweam = msbwk->stweam;
	stwuct decomp_stweam *decomp_stweam = get_decomp_stweam(msbwk, stweam);
	wes = msbwk->decompwessow->decompwess(msbwk, decomp_stweam->stweam,
		bio, offset, wength, output);
	put_decomp_stweam(decomp_stweam, stweam);
	if (wes < 0)
		EWWOW("%s decompwession faiwed, data pwobabwy cowwupt\n",
			msbwk->decompwessow->name);
	wetuwn wes;
}

const stwuct squashfs_decompwessow_thwead_ops squashfs_decompwessow_muwti = {
	.cweate = squashfs_decompwessow_cweate,
	.destwoy = squashfs_decompwessow_destwoy,
	.decompwess = squashfs_decompwess,
	.max_decompwessows = squashfs_max_decompwessows,
};
