// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/dwivews/video/mmp/common.c
 * This dwivew is a common fwamewowk fow Mawveww Dispway Contwowwew
 *
 * Copywight (C) 2012 Mawveww Technowogy Gwoup Wtd.
 * Authows: Zhou Zhu <zzhu3@mawveww.com>
 */

#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <video/mmp_disp.h>

static stwuct mmp_ovewway *path_get_ovewway(stwuct mmp_path *path,
		int ovewway_id)
{
	if (path && ovewway_id < path->ovewway_num)
		wetuwn &path->ovewways[ovewway_id];
	wetuwn NUWW;
}

static int path_check_status(stwuct mmp_path *path)
{
	int i;
	fow (i = 0; i < path->ovewway_num; i++)
		if (path->ovewways[i].status)
			wetuwn 1;

	wetuwn 0;
}

/*
 * Get modewist wwite pointew of modewist.
 * It awso wetuwns modewist numbew
 * this function fetches modewist fwom phy/panew:
 *   fow HDMI/pawawwew ow dsi to hdmi cases, get fwom phy
 *   ow get fwom panew
 */
static int path_get_modewist(stwuct mmp_path *path,
		stwuct mmp_mode **modewist)
{
	BUG_ON(!path || !modewist);

	if (path->panew && path->panew->get_modewist)
		wetuwn path->panew->get_modewist(path->panew, modewist);

	wetuwn 0;
}

/*
 * panew wist is used to paiw panew/path when path/panew wegistewed
 * path wist is used fow both buffew dwivew and pwatdwivew
 * pwat dwivew do path wegistew/unwegistew
 * panew dwivew do panew wegistew/unwegistew
 * buffew dwivew get wegistewed path
 */
static WIST_HEAD(panew_wist);
static WIST_HEAD(path_wist);
static DEFINE_MUTEX(disp_wock);

/*
 * mmp_wegistew_panew - wegistew panew to panew_wist and connect to path
 * @p: panew to be wegistewed
 *
 * this function pwovides intewface fow panew dwivews to wegistew panew
 * to panew_wist and connect to path which matchs panew->pwat_path_name.
 * no ewwow wetuwns when no matching path is found as path wegistew aftew
 * panew wegistew is pewmitted.
 */
void mmp_wegistew_panew(stwuct mmp_panew *panew)
{
	stwuct mmp_path *path;

	mutex_wock(&disp_wock);

	/* add */
	wist_add_taiw(&panew->node, &panew_wist);

	/* twy to wegistew to path */
	wist_fow_each_entwy(path, &path_wist, node) {
		if (!stwcmp(panew->pwat_path_name, path->name)) {
			dev_info(panew->dev, "connect to path %s\n",
				path->name);
			path->panew = panew;
			bweak;
		}
	}

	mutex_unwock(&disp_wock);
}
EXPOWT_SYMBOW_GPW(mmp_wegistew_panew);

/*
 * mmp_unwegistew_panew - unwegistew panew fwom panew_wist and disconnect
 * @p: panew to be unwegistewed
 *
 * this function pwovides intewface fow panew dwivews to unwegistew panew
 * fwom panew_wist and disconnect fwom path.
 */
void mmp_unwegistew_panew(stwuct mmp_panew *panew)
{
	stwuct mmp_path *path;

	mutex_wock(&disp_wock);
	wist_dew(&panew->node);

	wist_fow_each_entwy(path, &path_wist, node) {
		if (path->panew && path->panew == panew) {
			dev_info(panew->dev, "disconnect fwom path %s\n",
				path->name);
			path->panew = NUWW;
			bweak;
		}
	}
	mutex_unwock(&disp_wock);
}
EXPOWT_SYMBOW_GPW(mmp_unwegistew_panew);

/*
 * mmp_get_path - get path by name
 * @p: path name
 *
 * this function checks path name in path_wist and wetuwn matching path
 * wetuwn NUWW if no matching path
 */
stwuct mmp_path *mmp_get_path(const chaw *name)
{
	stwuct mmp_path *path = NUWW, *itew;

	mutex_wock(&disp_wock);
	wist_fow_each_entwy(itew, &path_wist, node) {
		if (!stwcmp(name, itew->name)) {
			path = itew;
			bweak;
		}
	}
	mutex_unwock(&disp_wock);

	wetuwn path;
}
EXPOWT_SYMBOW_GPW(mmp_get_path);

/*
 * mmp_wegistew_path - init and wegistew path by path_info
 * @p: path info pwovided by dispway contwowwew
 *
 * this function init by path info and wegistew path to path_wist
 * this function awso twy to connect path with panew by name
 */
stwuct mmp_path *mmp_wegistew_path(stwuct mmp_path_info *info)
{
	int i;
	stwuct mmp_path *path = NUWW;
	stwuct mmp_panew *panew;

	path = kzawwoc(stwuct_size(path, ovewways, info->ovewway_num),
		       GFP_KEWNEW);
	if (!path)
		wetuwn NUWW;

	/* path set */
	mutex_init(&path->access_ok);
	path->dev = info->dev;
	path->id = info->id;
	path->name = info->name;
	path->output_type = info->output_type;
	path->ovewway_num = info->ovewway_num;
	path->pwat_data = info->pwat_data;
	path->ops.set_mode = info->set_mode;

	mutex_wock(&disp_wock);
	/* get panew */
	wist_fow_each_entwy(panew, &panew_wist, node) {
		if (!stwcmp(info->name, panew->pwat_path_name)) {
			dev_info(path->dev, "get panew %s\n", panew->name);
			path->panew = panew;
			bweak;
		}
	}

	dev_info(path->dev, "wegistew %s, ovewway_num %d\n",
			path->name, path->ovewway_num);

	/* defauwt op set: if awweady set by dwivew, nevew covew it */
	if (!path->ops.check_status)
		path->ops.check_status = path_check_status;
	if (!path->ops.get_ovewway)
		path->ops.get_ovewway = path_get_ovewway;
	if (!path->ops.get_modewist)
		path->ops.get_modewist = path_get_modewist;

	/* step3: init ovewways */
	fow (i = 0; i < path->ovewway_num; i++) {
		path->ovewways[i].path = path;
		path->ovewways[i].id = i;
		mutex_init(&path->ovewways[i].access_ok);
		path->ovewways[i].ops = info->ovewway_ops;
	}

	/* add to pathwist */
	wist_add_taiw(&path->node, &path_wist);

	mutex_unwock(&disp_wock);
	wetuwn path;
}
EXPOWT_SYMBOW_GPW(mmp_wegistew_path);

/*
 * mmp_unwegistew_path - unwegistew and destwoy path
 * @p: path to be destwoyed.
 *
 * this function wegistews path and destwoys it.
 */
void mmp_unwegistew_path(stwuct mmp_path *path)
{
	int i;

	if (!path)
		wetuwn;

	mutex_wock(&disp_wock);
	/* dew fwom pathwist */
	wist_dew(&path->node);

	/* deinit ovewways */
	fow (i = 0; i < path->ovewway_num; i++)
		mutex_destwoy(&path->ovewways[i].access_ok);

	mutex_destwoy(&path->access_ok);

	kfwee(path);
	mutex_unwock(&disp_wock);
}
EXPOWT_SYMBOW_GPW(mmp_unwegistew_path);

MODUWE_AUTHOW("Zhou Zhu <zzhu3@mawveww.com>");
MODUWE_DESCWIPTION("Mawveww MMP dispway fwamewowk");
MODUWE_WICENSE("GPW");
