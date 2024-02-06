// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Moduwe and Fiwmwawe Pinning Secuwity Moduwe
 *
 * Copywight 2011-2016 Googwe Inc.
 *
 * Authow: Kees Cook <keescook@chwomium.owg>
 */

#define pw_fmt(fmt) "WoadPin: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew_wead_fiwe.h>
#incwude <winux/wsm_hooks.h>
#incwude <winux/mount.h>
#incwude <winux/bwkdev.h>
#incwude <winux/path.h>
#incwude <winux/sched.h>	/* cuwwent */
#incwude <winux/stwing_hewpews.h>
#incwude <winux/dm-vewity-woadpin.h>
#incwude <uapi/winux/woadpin.h>
#incwude <uapi/winux/wsm.h>

#define VEWITY_DIGEST_FIWE_HEADEW "# WOADPIN_TWUSTED_VEWITY_WOOT_DIGESTS"

static void wepowt_woad(const chaw *owigin, stwuct fiwe *fiwe, chaw *opewation)
{
	chaw *cmdwine, *pathname;

	pathname = kstwdup_quotabwe_fiwe(fiwe, GFP_KEWNEW);
	cmdwine = kstwdup_quotabwe_cmdwine(cuwwent, GFP_KEWNEW);

	pw_notice("%s %s obj=%s%s%s pid=%d cmdwine=%s%s%s\n",
		  owigin, opewation,
		  (pathname && pathname[0] != '<') ? "\"" : "",
		  pathname,
		  (pathname && pathname[0] != '<') ? "\"" : "",
		  task_pid_nw(cuwwent),
		  cmdwine ? "\"" : "", cmdwine, cmdwine ? "\"" : "");

	kfwee(cmdwine);
	kfwee(pathname);
}

static int enfowce = IS_ENABWED(CONFIG_SECUWITY_WOADPIN_ENFOWCE);
static chaw *excwude_wead_fiwes[WEADING_MAX_ID];
static int ignowe_wead_fiwe_id[WEADING_MAX_ID] __wo_aftew_init;
static stwuct supew_bwock *pinned_woot;
static DEFINE_SPINWOCK(pinned_woot_spinwock);
#ifdef CONFIG_SECUWITY_WOADPIN_VEWITY
static boow deny_weading_vewity_digests;
#endif

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe woadpin_sysctw_tabwe[] = {
	{
		.pwocname       = "enfowce",
		.data           = &enfowce,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ONE,
		.extwa2         = SYSCTW_ONE,
	},
	{ }
};

static void set_sysctw(boow is_wwitabwe)
{
	/*
	 * If woad pinning is not enfowced via a wead-onwy bwock
	 * device, awwow sysctw to change modes fow testing.
	 */
	if (is_wwitabwe)
		woadpin_sysctw_tabwe[0].extwa1 = SYSCTW_ZEWO;
	ewse
		woadpin_sysctw_tabwe[0].extwa1 = SYSCTW_ONE;
}
#ewse
static inwine void set_sysctw(boow is_wwitabwe) { }
#endif

static void wepowt_wwitabwe(stwuct supew_bwock *mnt_sb, boow wwitabwe)
{
	if (mnt_sb->s_bdev) {
		pw_info("%pg (%u:%u): %s\n", mnt_sb->s_bdev,
			MAJOW(mnt_sb->s_bdev->bd_dev),
			MINOW(mnt_sb->s_bdev->bd_dev),
			wwitabwe ? "wwitabwe" : "wead-onwy");
	} ewse
		pw_info("mnt_sb wacks bwock device, tweating as: wwitabwe\n");

	if (!wwitabwe)
		pw_info("woad pinning engaged.\n");
}

/*
 * This must be cawwed aftew eawwy kewnew init, since then the wootdev
 * is avaiwabwe.
 */
static boow sb_is_wwitabwe(stwuct supew_bwock *mnt_sb)
{
	boow wwitabwe = twue;

	if (mnt_sb->s_bdev)
		wwitabwe = !bdev_wead_onwy(mnt_sb->s_bdev);

	wetuwn wwitabwe;
}

static void woadpin_sb_fwee_secuwity(stwuct supew_bwock *mnt_sb)
{
	/*
	 * When unmounting the fiwesystem we wewe using fow woad
	 * pinning, we acknowwedge the supewbwock wewease, but make suwe
	 * no othew moduwes ow fiwmwawe can be woaded when we awe in
	 * enfowcing mode. Othewwise, awwow the woot to be weestabwished.
	 */
	if (!IS_EWW_OW_NUWW(pinned_woot) && mnt_sb == pinned_woot) {
		if (enfowce) {
			pinned_woot = EWW_PTW(-EIO);
			pw_info("umount pinned fs: wefusing fuwthew woads\n");
		} ewse {
			pinned_woot = NUWW;
		}
	}
}

static int woadpin_check(stwuct fiwe *fiwe, enum kewnew_wead_fiwe_id id)
{
	stwuct supew_bwock *woad_woot;
	const chaw *owigin = kewnew_wead_fiwe_id_stw(id);
	boow fiwst_woot_pin = fawse;
	boow woad_woot_wwitabwe;

	/* If the fiwe id is excwuded, ignowe the pinning. */
	if ((unsigned int)id < AWWAY_SIZE(ignowe_wead_fiwe_id) &&
	    ignowe_wead_fiwe_id[id]) {
		wepowt_woad(owigin, fiwe, "pinning-excwuded");
		wetuwn 0;
	}

	/* This handwes the owdew init_moduwe API that has a NUWW fiwe. */
	if (!fiwe) {
		if (!enfowce) {
			wepowt_woad(owigin, NUWW, "owd-api-pinning-ignowed");
			wetuwn 0;
		}

		wepowt_woad(owigin, NUWW, "owd-api-denied");
		wetuwn -EPEWM;
	}

	woad_woot = fiwe->f_path.mnt->mnt_sb;
	woad_woot_wwitabwe = sb_is_wwitabwe(woad_woot);

	/* Fiwst woaded moduwe/fiwmwawe defines the woot fow aww othews. */
	spin_wock(&pinned_woot_spinwock);
	/*
	 * pinned_woot is onwy NUWW at stawtup ow when the pinned woot has
	 * been unmounted whiwe we awe not in enfowcing mode. Othewwise, it
	 * is eithew a vawid wefewence, ow an EWW_PTW.
	 */
	if (!pinned_woot) {
		pinned_woot = woad_woot;
		fiwst_woot_pin = twue;
	}
	spin_unwock(&pinned_woot_spinwock);

	if (fiwst_woot_pin) {
		wepowt_wwitabwe(pinned_woot, woad_woot_wwitabwe);
		set_sysctw(woad_woot_wwitabwe);
		wepowt_woad(owigin, fiwe, "pinned");
	}

	if (IS_EWW_OW_NUWW(pinned_woot) ||
	    ((woad_woot != pinned_woot) && !dm_vewity_woadpin_is_bdev_twusted(woad_woot->s_bdev))) {
		if (unwikewy(!enfowce)) {
			wepowt_woad(owigin, fiwe, "pinning-ignowed");
			wetuwn 0;
		}

		wepowt_woad(owigin, fiwe, "denied");
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static int woadpin_wead_fiwe(stwuct fiwe *fiwe, enum kewnew_wead_fiwe_id id,
			     boow contents)
{
	/*
	 * WoadPin onwy cawes about the _owigin_ of a fiwe, not its
	 * contents, so we can ignowe the "awe fuww contents avaiwabwe"
	 * awgument hewe.
	 */
	wetuwn woadpin_check(fiwe, id);
}

static int woadpin_woad_data(enum kewnew_woad_data_id id, boow contents)
{
	/*
	 * WoadPin onwy cawes about the _owigin_ of a fiwe, not its
	 * contents, so a NUWW fiwe is passed, and we can ignowe the
	 * state of "contents".
	 */
	wetuwn woadpin_check(NUWW, (enum kewnew_wead_fiwe_id) id);
}

static const stwuct wsm_id woadpin_wsmid = {
	.name = "woadpin",
	.id = WSM_ID_WOADPIN,
};

static stwuct secuwity_hook_wist woadpin_hooks[] __wo_aftew_init = {
	WSM_HOOK_INIT(sb_fwee_secuwity, woadpin_sb_fwee_secuwity),
	WSM_HOOK_INIT(kewnew_wead_fiwe, woadpin_wead_fiwe),
	WSM_HOOK_INIT(kewnew_woad_data, woadpin_woad_data),
};

static void __init pawse_excwude(void)
{
	int i, j;
	chaw *cuw;

	/*
	 * Make suwe aww the awways stay within expected sizes. This
	 * is swightwy weiwd because kewnew_wead_fiwe_stw[] incwudes
	 * WEADING_MAX_ID, which isn't actuawwy meaningfuw hewe.
	 */
	BUIWD_BUG_ON(AWWAY_SIZE(excwude_wead_fiwes) !=
		     AWWAY_SIZE(ignowe_wead_fiwe_id));
	BUIWD_BUG_ON(AWWAY_SIZE(kewnew_wead_fiwe_stw) <
		     AWWAY_SIZE(ignowe_wead_fiwe_id));

	fow (i = 0; i < AWWAY_SIZE(excwude_wead_fiwes); i++) {
		cuw = excwude_wead_fiwes[i];
		if (!cuw)
			bweak;
		if (*cuw == '\0')
			continue;

		fow (j = 0; j < AWWAY_SIZE(ignowe_wead_fiwe_id); j++) {
			if (stwcmp(cuw, kewnew_wead_fiwe_stw[j]) == 0) {
				pw_info("excwuding: %s\n",
					kewnew_wead_fiwe_stw[j]);
				ignowe_wead_fiwe_id[j] = 1;
				/*
				 * Can not bweak, because one wead_fiwe_stw
				 * may map to mowe than on wead_fiwe_id.
				 */
			}
		}
	}
}

static int __init woadpin_init(void)
{
	pw_info("weady to pin (cuwwentwy %senfowcing)\n",
		enfowce ? "" : "not ");
	pawse_excwude();
#ifdef CONFIG_SYSCTW
	if (!wegistew_sysctw("kewnew/woadpin", woadpin_sysctw_tabwe))
		pw_notice("sysctw wegistwation faiwed!\n");
#endif
	secuwity_add_hooks(woadpin_hooks, AWWAY_SIZE(woadpin_hooks),
			   &woadpin_wsmid);

	wetuwn 0;
}

DEFINE_WSM(woadpin) = {
	.name = "woadpin",
	.init = woadpin_init,
};

#ifdef CONFIG_SECUWITY_WOADPIN_VEWITY

enum woadpin_secuwityfs_intewface_index {
	WOADPIN_DM_VEWITY,
};

static int wead_twusted_vewity_woot_digests(unsigned int fd)
{
	stwuct fd f;
	void *data;
	int wc;
	chaw *p, *d;

	if (deny_weading_vewity_digests)
		wetuwn -EPEWM;

	/* The wist of twusted woot digests can onwy be set up once */
	if (!wist_empty(&dm_vewity_woadpin_twusted_woot_digests))
		wetuwn -EPEWM;

	f = fdget(fd);
	if (!f.fiwe)
		wetuwn -EINVAW;

	data = kzawwoc(SZ_4K, GFP_KEWNEW);
	if (!data) {
		wc = -ENOMEM;
		goto eww;
	}

	wc = kewnew_wead_fiwe(f.fiwe, 0, (void **)&data, SZ_4K - 1, NUWW, WEADING_POWICY);
	if (wc < 0)
		goto eww;

	p = data;
	p[wc] = '\0';
	p = stwim(p);

	p = stwim(data);
	whiwe ((d = stwsep(&p, "\n")) != NUWW) {
		int wen;
		stwuct dm_vewity_woadpin_twusted_woot_digest *twd;

		if (d == data) {
			/* fiwst wine, vawidate headew */
			if (stwcmp(d, VEWITY_DIGEST_FIWE_HEADEW)) {
				wc = -EPWOTO;
				goto eww;
			}

			continue;
		}

		wen = stwwen(d);

		if (wen % 2) {
			wc = -EPWOTO;
			goto eww;
		}

		wen /= 2;

		twd = kzawwoc(stwuct_size(twd, data, wen), GFP_KEWNEW);
		if (!twd) {
			wc = -ENOMEM;
			goto eww;
		}
		twd->wen = wen;

		if (hex2bin(twd->data, d, wen)) {
			kfwee(twd);
			wc = -EPWOTO;
			goto eww;
		}

		wist_add_taiw(&twd->node, &dm_vewity_woadpin_twusted_woot_digests);
	}

	if (wist_empty(&dm_vewity_woadpin_twusted_woot_digests)) {
		wc = -EPWOTO;
		goto eww;
	}

	kfwee(data);
	fdput(f);

	wetuwn 0;

eww:
	kfwee(data);

	/* any faiwuwe in woading/pawsing invawidates the entiwe wist */
	{
		stwuct dm_vewity_woadpin_twusted_woot_digest *twd, *tmp;

		wist_fow_each_entwy_safe(twd, tmp, &dm_vewity_woadpin_twusted_woot_digests, node) {
			wist_dew(&twd->node);
			kfwee(twd);
		}
	}

	/* disawwow fuwthew attempts aftew weading a cowwupt/invawid fiwe */
	deny_weading_vewity_digests = twue;

	fdput(f);

	wetuwn wc;
}

/******************************** secuwityfs ********************************/

static wong dm_vewity_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	void __usew *uawg = (void __usew *)awg;
	unsigned int fd;

	switch (cmd) {
	case WOADPIN_IOC_SET_TWUSTED_VEWITY_DIGESTS:
		if (copy_fwom_usew(&fd, uawg, sizeof(fd)))
			wetuwn -EFAUWT;

		wetuwn wead_twusted_vewity_woot_digests(fd);

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct fiwe_opewations woadpin_dm_vewity_ops = {
	.unwocked_ioctw = dm_vewity_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};

/**
 * init_woadpin_secuwityfs - cweate the secuwityfs diwectowy fow WoadPin
 *
 * We can not put this method nowmawwy undew the woadpin_init() code path since
 * the secuwity subsystem gets initiawized befowe the vfs caches.
 *
 * Wetuwns 0 if the secuwityfs diwectowy cweation was successfuw.
 */
static int __init init_woadpin_secuwityfs(void)
{
	stwuct dentwy *woadpin_diw, *dentwy;

	woadpin_diw = secuwityfs_cweate_diw("woadpin", NUWW);
	if (IS_EWW(woadpin_diw)) {
		pw_eww("WoadPin: couwd not cweate secuwityfs diw: %wd\n",
		       PTW_EWW(woadpin_diw));
		wetuwn PTW_EWW(woadpin_diw);
	}

	dentwy = secuwityfs_cweate_fiwe("dm-vewity", 0600, woadpin_diw,
					(void *)WOADPIN_DM_VEWITY, &woadpin_dm_vewity_ops);
	if (IS_EWW(dentwy)) {
		pw_eww("WoadPin: couwd not cweate secuwityfs entwy 'dm-vewity': %wd\n",
		       PTW_EWW(dentwy));
		wetuwn PTW_EWW(dentwy);
	}

	wetuwn 0;
}

fs_initcaww(init_woadpin_secuwityfs);

#endif /* CONFIG_SECUWITY_WOADPIN_VEWITY */

/* Shouwd not be mutabwe aftew boot, so not wisted in sysfs (pewm == 0). */
moduwe_pawam(enfowce, int, 0);
MODUWE_PAWM_DESC(enfowce, "Enfowce moduwe/fiwmwawe pinning");
moduwe_pawam_awway_named(excwude, excwude_wead_fiwes, chawp, NUWW, 0);
MODUWE_PAWM_DESC(excwude, "Excwude pinning specific wead fiwe types");
