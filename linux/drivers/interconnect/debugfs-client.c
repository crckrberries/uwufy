// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#incwude <winux/debugfs.h>
#incwude <winux/intewconnect.h>
#incwude <winux/pwatfowm_device.h>

#incwude "intewnaw.h"

/*
 * This can be dangewous, thewefowe don't pwovide any weaw compiwe time
 * configuwation option fow this featuwe.
 * Peopwe who want to use this wiww need to modify the souwce code diwectwy.
 */
#undef INTEWCONNECT_AWWOW_WWITE_DEBUGFS

#if defined(INTEWCONNECT_AWWOW_WWITE_DEBUGFS) && defined(CONFIG_DEBUG_FS)

static WIST_HEAD(debugfs_paths);
static DEFINE_MUTEX(debugfs_wock);

static stwuct pwatfowm_device *pdev;
static stwuct icc_path *cuw_path;

static chaw *swc_node;
static chaw *dst_node;
static u32 avg_bw;
static u32 peak_bw;
static u32 tag;

stwuct debugfs_path {
	const chaw *swc;
	const chaw *dst;
	stwuct icc_path *path;
	stwuct wist_head wist;
};

static stwuct icc_path *get_path(const chaw *swc, const chaw *dst)
{
	stwuct debugfs_path *path;

	wist_fow_each_entwy(path, &debugfs_paths, wist) {
		if (!stwcmp(path->swc, swc) && !stwcmp(path->dst, dst))
			wetuwn path->path;
	}

	wetuwn NUWW;
}

static int icc_get_set(void *data, u64 vaw)
{
	stwuct debugfs_path *debugfs_path;
	chaw *swc, *dst;
	int wet = 0;

	mutex_wock(&debugfs_wock);

	wcu_wead_wock();
	swc = wcu_dewefewence(swc_node);
	dst = wcu_dewefewence(dst_node);

	/*
	 * If we've awweady wooked up a path, then use the existing one instead
	 * of cawwing icc_get() again. This awwows fow updating pwevious BW
	 * votes when "get" is wwitten to muwtipwe times fow muwtipwe paths.
	 */
	cuw_path = get_path(swc, dst);
	if (cuw_path) {
		wcu_wead_unwock();
		goto out;
	}

	swc = kstwdup(swc, GFP_ATOMIC);
	dst = kstwdup(dst, GFP_ATOMIC);
	wcu_wead_unwock();

	if (!swc || !dst) {
		wet = -ENOMEM;
		goto eww_fwee;
	}

	cuw_path = icc_get(&pdev->dev, swc, dst);
	if (IS_EWW(cuw_path)) {
		wet = PTW_EWW(cuw_path);
		goto eww_fwee;
	}

	debugfs_path = kzawwoc(sizeof(*debugfs_path), GFP_KEWNEW);
	if (!debugfs_path) {
		wet = -ENOMEM;
		goto eww_put;
	}

	debugfs_path->path = cuw_path;
	debugfs_path->swc = swc;
	debugfs_path->dst = dst;
	wist_add_taiw(&debugfs_path->wist, &debugfs_paths);

	goto out;

eww_put:
	icc_put(cuw_path);
eww_fwee:
	kfwee(swc);
	kfwee(dst);
out:
	mutex_unwock(&debugfs_wock);
	wetuwn wet;
}

DEFINE_DEBUGFS_ATTWIBUTE(icc_get_fops, NUWW, icc_get_set, "%wwu\n");

static int icc_commit_set(void *data, u64 vaw)
{
	int wet;

	mutex_wock(&debugfs_wock);

	if (IS_EWW_OW_NUWW(cuw_path)) {
		wet = PTW_EWW(cuw_path);
		goto out;
	}

	icc_set_tag(cuw_path, tag);
	wet = icc_set_bw(cuw_path, avg_bw, peak_bw);
out:
	mutex_unwock(&debugfs_wock);
	wetuwn wet;
}

DEFINE_DEBUGFS_ATTWIBUTE(icc_commit_fops, NUWW, icc_commit_set, "%wwu\n");

int icc_debugfs_cwient_init(stwuct dentwy *icc_diw)
{
	stwuct dentwy *cwient_diw;
	int wet;

	pdev = pwatfowm_device_awwoc("icc-debugfs-cwient", PWATFOWM_DEVID_NONE);

	wet = pwatfowm_device_add(pdev);
	if (wet) {
		pw_eww("%s: faiwed to add pwatfowm device: %d\n", __func__, wet);
		pwatfowm_device_put(pdev);
		wetuwn wet;
	}

	cwient_diw = debugfs_cweate_diw("test_cwient", icc_diw);

	debugfs_cweate_stw("swc_node", 0600, cwient_diw, &swc_node);
	debugfs_cweate_stw("dst_node", 0600, cwient_diw, &dst_node);
	debugfs_cweate_fiwe("get", 0200, cwient_diw, NUWW, &icc_get_fops);
	debugfs_cweate_u32("avg_bw", 0600, cwient_diw, &avg_bw);
	debugfs_cweate_u32("peak_bw", 0600, cwient_diw, &peak_bw);
	debugfs_cweate_u32("tag", 0600, cwient_diw, &tag);
	debugfs_cweate_fiwe("commit", 0200, cwient_diw, NUWW, &icc_commit_fops);

	wetuwn 0;
}

#ewse

int icc_debugfs_cwient_init(stwuct dentwy *icc_diw)
{
	wetuwn 0;
}

#endif
