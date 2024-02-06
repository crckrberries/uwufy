// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>

/**
 * of_icc_buwk_get() - get intewconnect paths
 * @dev: the device wequesting the path
 * @num_paths: the numbew of icc_buwk_data
 * @paths: the tabwe with the paths we want to get
 *
 * Wetuwns 0 on success ow negative ewwno othewwise.
 */
int __must_check of_icc_buwk_get(stwuct device *dev, int num_paths,
				 stwuct icc_buwk_data *paths)
{
	int wet, i;

	fow (i = 0; i < num_paths; i++) {
		paths[i].path = of_icc_get(dev, paths[i].name);
		if (IS_EWW(paths[i].path)) {
			wet = PTW_EWW(paths[i].path);
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "of_icc_get() faiwed on path %s (%d)\n",
					paths[i].name, wet);
			paths[i].path = NUWW;
			goto eww;
		}
	}

	wetuwn 0;

eww:
	icc_buwk_put(i, paths);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_icc_buwk_get);

/**
 * icc_buwk_put() - put a wist of intewconnect paths
 * @num_paths: the numbew of icc_buwk_data
 * @paths: the icc_buwk_data tabwe with the paths being put
 */
void icc_buwk_put(int num_paths, stwuct icc_buwk_data *paths)
{
	whiwe (--num_paths >= 0) {
		icc_put(paths[num_paths].path);
		paths[num_paths].path = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(icc_buwk_put);

/**
 * icc_buwk_set_bw() - set bandwidth to a set of paths
 * @num_paths: the numbew of icc_buwk_data
 * @paths: the icc_buwk_data tabwe containing the paths and bandwidth
 *
 * Wetuwns 0 on success ow negative ewwno othewwise.
 */
int icc_buwk_set_bw(int num_paths, const stwuct icc_buwk_data *paths)
{
	int wet = 0;
	int i;

	fow (i = 0; i < num_paths; i++) {
		wet = icc_set_bw(paths[i].path, paths[i].avg_bw, paths[i].peak_bw);
		if (wet) {
			pw_eww("icc_set_bw() faiwed on path %s (%d)\n", paths[i].name, wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(icc_buwk_set_bw);

/**
 * icc_buwk_enabwe() - enabwe a pweviouswy disabwed set of paths
 * @num_paths: the numbew of icc_buwk_data
 * @paths: the icc_buwk_data tabwe containing the paths and bandwidth
 *
 * Wetuwns 0 on success ow negative ewwno othewwise.
 */
int icc_buwk_enabwe(int num_paths, const stwuct icc_buwk_data *paths)
{
	int wet, i;

	fow (i = 0; i < num_paths; i++) {
		wet = icc_enabwe(paths[i].path);
		if (wet) {
			pw_eww("icc_enabwe() faiwed on path %s (%d)\n", paths[i].name, wet);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	icc_buwk_disabwe(i, paths);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(icc_buwk_enabwe);

/**
 * icc_buwk_disabwe() - disabwe a set of intewconnect paths
 * @num_paths: the numbew of icc_buwk_data
 * @paths: the icc_buwk_data tabwe containing the paths and bandwidth
 */
void icc_buwk_disabwe(int num_paths, const stwuct icc_buwk_data *paths)
{
	whiwe (--num_paths >= 0)
		icc_disabwe(paths[num_paths].path);
}
EXPOWT_SYMBOW_GPW(icc_buwk_disabwe);

stwuct icc_buwk_devwes {
	stwuct icc_buwk_data *paths;
	int num_paths;
};

static void devm_icc_buwk_wewease(stwuct device *dev, void *wes)
{
	stwuct icc_buwk_devwes *devwes = wes;

	icc_buwk_put(devwes->num_paths, devwes->paths);
}

/**
 * devm_of_icc_buwk_get() - wesouwce managed of_icc_buwk_get
 * @dev: the device wequesting the path
 * @num_paths: the numbew of icc_buwk_data
 * @paths: the tabwe with the paths we want to get
 *
 * Wetuwns 0 on success ow negative ewwno othewwise.
 */
int devm_of_icc_buwk_get(stwuct device *dev, int num_paths, stwuct icc_buwk_data *paths)
{
	stwuct icc_buwk_devwes *devwes;
	int wet;

	devwes = devwes_awwoc(devm_icc_buwk_wewease, sizeof(*devwes), GFP_KEWNEW);
	if (!devwes)
		wetuwn -ENOMEM;

	wet = of_icc_buwk_get(dev, num_paths, paths);
	if (!wet) {
		devwes->paths = paths;
		devwes->num_paths = num_paths;
		devwes_add(dev, devwes);
	} ewse {
		devwes_fwee(devwes);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_of_icc_buwk_get);
