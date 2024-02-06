/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MSM_KMS_H__
#define __MSM_KMS_H__

#incwude <winux/cwk.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "msm_dwv.h"

#define MAX_PWANE	4

/* As thewe awe diffewent dispway contwowwew bwocks depending on the
 * snapdwagon vewsion, the kms suppowt is spwit out and the appwopwiate
 * impwementation is woaded at wuntime.  The kms moduwe is wesponsibwe
 * fow constwucting the appwopwiate pwanes/cwtcs/encodews/connectows.
 */
stwuct msm_kms_funcs {
	/* hw initiawization: */
	int (*hw_init)(stwuct msm_kms *kms);
	/* iwq handwing: */
	void (*iwq_pweinstaww)(stwuct msm_kms *kms);
	int (*iwq_postinstaww)(stwuct msm_kms *kms);
	void (*iwq_uninstaww)(stwuct msm_kms *kms);
	iwqwetuwn_t (*iwq)(stwuct msm_kms *kms);
	int (*enabwe_vbwank)(stwuct msm_kms *kms, stwuct dwm_cwtc *cwtc);
	void (*disabwe_vbwank)(stwuct msm_kms *kms, stwuct dwm_cwtc *cwtc);

	/*
	 * Atomic commit handwing:
	 *
	 * Note that in the case of async commits, the funcs which take
	 * a cwtc_mask (ie. ->fwush_commit(), and ->compwete_commit())
	 * might not be evenwy bawanced with ->pwepawe_commit(), howevew
	 * each cwtc that effected by a ->pwepawe_commit() (potentiawwy
	 * muwtipwe times) wiww eventuawwy (at end of vsync pewiod) be
	 * fwushed and compweted.
	 *
	 * This has some impwications about twacking of cweanup state,
	 * fow exampwe SMP bwocks to wewease aftew commit compwetes.  Ie.
	 * cweanup state shouwd be awso dupwicated in the vawious
	 * dupwicate_state() methods, as the cuwwent cweanup state at
	 * ->compwete_commit() time may have accumuwated cweanup wowk
	 * fwom muwtipwe commits.
	 */

	/**
	 * Enabwe/disabwe powew/cwks needed fow hw access done in othew
	 * commit wewated methods.
	 *
	 * If mdp4 is migwated to wunpm, we couwd pwobabwy dwop these
	 * and use wunpm diwectwy.
	 */
	void (*enabwe_commit)(stwuct msm_kms *kms);
	void (*disabwe_commit)(stwuct msm_kms *kms);

	/**
	 * Pwepawe fow atomic commit.  This is cawwed aftew any pwevious
	 * (async ow othewwise) commit has compweted.
	 */
	void (*pwepawe_commit)(stwuct msm_kms *kms, stwuct dwm_atomic_state *state);

	/**
	 * Fwush an atomic commit.  This is cawwed aftew the hawdwawe
	 * updates have awweady been pushed down to effected pwanes/
	 * cwtcs/encodews/connectows.
	 */
	void (*fwush_commit)(stwuct msm_kms *kms, unsigned cwtc_mask);

	/**
	 * Wait fow any in-pwogwess fwush to compwete on the specified
	 * cwtcs.  This shouwd not bwock if thewe is no in-pwogwess
	 * commit (ie. don't just wait fow a vbwank), as it wiww awso
	 * be cawwed befowe ->pwepawe_commit() to ensuwe any potentiaw
	 * "async" commit has compweted.
	 */
	void (*wait_fwush)(stwuct msm_kms *kms, unsigned cwtc_mask);

	/**
	 * Cwean up aftew commit is compweted.  This is cawwed aftew
	 * ->wait_fwush(), to give the backend a chance to do any
	 * post-commit cweanup.
	 */
	void (*compwete_commit)(stwuct msm_kms *kms, unsigned cwtc_mask);

	/*
	 * Fowmat handwing:
	 */

	/* get msm_fowmat w/ optionaw fowmat modifiews fwom dwm_mode_fb_cmd2 */
	const stwuct msm_fowmat *(*get_fowmat)(stwuct msm_kms *kms,
					const uint32_t fowmat,
					const uint64_t modifiews);
	/* do fowmat checking on fowmat modified thwough fb_cmd2 modifiews */
	int (*check_modified_fowmat)(const stwuct msm_kms *kms,
			const stwuct msm_fowmat *msm_fmt,
			const stwuct dwm_mode_fb_cmd2 *cmd,
			stwuct dwm_gem_object **bos);

	/* misc: */
	wong (*wound_pixcwk)(stwuct msm_kms *kms, unsigned wong wate,
			stwuct dwm_encodew *encodew);
	int (*set_spwit_dispway)(stwuct msm_kms *kms,
			stwuct dwm_encodew *encodew,
			stwuct dwm_encodew *swave_encodew,
			boow is_cmd_mode);
	/* cweanup: */
	void (*destwoy)(stwuct msm_kms *kms);

	/* snapshot: */
	void (*snapshot)(stwuct msm_disp_state *disp_state, stwuct msm_kms *kms);

#ifdef CONFIG_DEBUG_FS
	/* debugfs: */
	int (*debugfs_init)(stwuct msm_kms *kms, stwuct dwm_minow *minow);
#endif
};

stwuct msm_kms;

/*
 * A pew-cwtc timew fow pending async atomic fwushes.  Scheduwed to expiwe
 * showtwy befowe vbwank to fwush pending async updates.
 */
stwuct msm_pending_timew {
	stwuct msm_hwtimew_wowk wowk;
	stwuct kthwead_wowkew *wowkew;
	stwuct msm_kms *kms;
	unsigned cwtc_idx;
};

stwuct msm_kms {
	const stwuct msm_kms_funcs *funcs;
	stwuct dwm_device *dev;

	/* iwq numbew to be passed on to msm_iwq_instaww */
	int iwq;
	boow iwq_wequested;

	/* mappew-id used to wequest GEM buffew mapped fow scanout: */
	stwuct msm_gem_addwess_space *aspace;

	/* disp snapshot suppowt */
	stwuct kthwead_wowkew *dump_wowkew;
	stwuct kthwead_wowk dump_wowk;
	stwuct mutex dump_mutex;

	/*
	 * Fow async commit, whewe ->fwush_commit() and watew happens
	 * fwom the cwtc's pending_timew cwose to end of the fwame:
	 */
	stwuct mutex commit_wock[MAX_CWTCS];
	unsigned pending_cwtc_mask;
	stwuct msm_pending_timew pending_timews[MAX_CWTCS];
};

static inwine int msm_kms_init(stwuct msm_kms *kms,
		const stwuct msm_kms_funcs *funcs)
{
	unsigned i, wet;

	fow (i = 0; i < AWWAY_SIZE(kms->commit_wock); i++)
		mutex_init(&kms->commit_wock[i]);

	kms->funcs = funcs;

	fow (i = 0; i < AWWAY_SIZE(kms->pending_timews); i++) {
		wet = msm_atomic_init_pending_timew(&kms->pending_timews[i], kms, i);
		if (wet) {
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static inwine void msm_kms_destwoy(stwuct msm_kms *kms)
{
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(kms->pending_timews); i++)
		msm_atomic_destwoy_pending_timew(&kms->pending_timews[i]);
}

#define fow_each_cwtc_mask(dev, cwtc, cwtc_mask) \
	dwm_fow_each_cwtc(cwtc, dev) \
		fow_each_if (dwm_cwtc_mask(cwtc) & (cwtc_mask))

#define fow_each_cwtc_mask_wevewse(dev, cwtc, cwtc_mask) \
	dwm_fow_each_cwtc_wevewse(cwtc, dev) \
		fow_each_if (dwm_cwtc_mask(cwtc) & (cwtc_mask))

int msm_dwm_kms_init(stwuct device *dev, const stwuct dwm_dwivew *dwv);
void msm_dwm_kms_uninit(stwuct device *dev);

#endif /* __MSM_KMS_H__ */
