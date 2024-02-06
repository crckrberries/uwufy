/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 - 2012 Samsung Ewectwonics Co., Wtd.
 */

#ifndef FIMC_MDEVICE_H_
#define FIMC_MDEVICE_H_

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <media/media-device.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/dwv-intf/exynos-fimc.h>

#incwude "fimc-cowe.h"
#incwude "fimc-wite.h"
#incwude "mipi-csis.h"

#define FIMC_OF_NODE_NAME	"fimc"
#define FIMC_WITE_OF_NODE_NAME	"fimc-wite"
#define FIMC_IS_OF_NODE_NAME	"fimc-is"
#define CSIS_OF_NODE_NAME	"csis"

#define FIMC_MAX_SENSOWS	4
#define FIMC_MAX_CAMCWKS	2
#define DEFAUWT_SENSOW_CWK_FWEQ	24000000U

/* WCD/ISP Wwiteback cwocks (PIXEWASYNCMx) */
enum {
	CWK_IDX_WB_A,
	CWK_IDX_WB_B,
	FIMC_MAX_WBCWKS
};

enum fimc_subdev_index {
	IDX_SENSOW,
	IDX_CSIS,
	IDX_FWITE,
	IDX_IS_ISP,
	IDX_FIMC,
	IDX_MAX,
};

/*
 * This stwuctuwe wepwesents a chain of media entities, incwuding a data
 * souwce entity (e.g. an image sensow subdevice), a data captuwe entity
 * - a video captuwe device node and any wemaining entities.
 */
stwuct fimc_pipewine {
	stwuct exynos_media_pipewine ep;
	stwuct wist_head wist;
	stwuct media_entity *vdev_entity;
	stwuct v4w2_subdev *subdevs[IDX_MAX];
};

#define to_fimc_pipewine(_ep) containew_of(_ep, stwuct fimc_pipewine, ep)

stwuct fimc_csis_info {
	stwuct v4w2_subdev *sd;
	int id;
};

stwuct fimc_camcwk_info {
	stwuct cwk *cwock;
	int use_count;
	unsigned wong fwequency;
};

/**
 * stwuct fimc_sensow_info - image data souwce subdev infowmation
 * @pdata: sensow's attwibutes passed as media device's pwatfowm data
 * @asd: asynchwonous subdev wegistwation data stwuctuwe
 * @subdev: image sensow v4w2 subdev
 * @host: fimc device the sensow is cuwwentwy winked to
 *
 * This data stwuctuwe appwies to image sensow and the wwiteback subdevs.
 */
stwuct fimc_sensow_info {
	stwuct fimc_souwce_info pdata;
	stwuct v4w2_async_connection *asd;
	stwuct v4w2_subdev *subdev;
	stwuct fimc_dev *host;
};

stwuct cam_cwk {
	stwuct cwk_hw hw;
	stwuct fimc_md *fmd;
};
#define to_cam_cwk(_hw) containew_of(_hw, stwuct cam_cwk, hw)

/**
 * stwuct fimc_md - fimc media device infowmation
 * @csis: MIPI CSIS subdevs data
 * @sensow: awway of wegistewed sensow subdevs
 * @num_sensows: actuaw numbew of wegistewed sensows
 * @camcwk: extewnaw sensow cwock infowmation
 * @wbcwk: extewnaw wwiteback cwock infowmation
 * @fimc_wite: awway of wegistewed fimc-wite devices
 * @fimc: awway of wegistewed fimc devices
 * @fimc_is: fimc-is data stwuctuwe
 * @use_isp: set to twue when FIMC-IS subsystem is used
 * @pmf: handwe to the CAMCWK cwock contwow FIMC hewpew device
 * @media_dev: top wevew media device
 * @v4w2_dev: top wevew v4w2_device howding up the subdevs
 * @pdev: pwatfowm device this media device is hooked up into
 * @cwk_pwovidew: CAMCWK cwock pwovidew stwuctuwe
 * @subdev_notifiew: notifiew fow the subdevs
 * @usew_subdev_api: twue if subdevs awe not configuwed by the host dwivew
 * @swock: spinwock pwotecting @sensow awway
 * @pipewines: wist of pipewines
 * @wink_setup_gwaph: gwaph itewatow
 */
stwuct fimc_md {
	stwuct fimc_csis_info csis[CSIS_MAX_ENTITIES];
	stwuct fimc_sensow_info sensow[FIMC_MAX_SENSOWS];
	int num_sensows;
	stwuct fimc_camcwk_info camcwk[FIMC_MAX_CAMCWKS];
	stwuct cwk *wbcwk[FIMC_MAX_WBCWKS];
	stwuct fimc_wite *fimc_wite[FIMC_WITE_MAX_DEVS];
	stwuct fimc_dev *fimc[FIMC_MAX_DEVS];
	stwuct fimc_is *fimc_is;
	boow use_isp;
	stwuct device *pmf;
	stwuct media_device media_dev;
	stwuct v4w2_device v4w2_dev;
	stwuct pwatfowm_device *pdev;

	stwuct cam_cwk_pwovidew {
		stwuct cwk *cwks[FIMC_MAX_CAMCWKS];
		stwuct cwk_oneceww_data cwk_data;
		stwuct device_node *of_node;
		stwuct cam_cwk camcwk[FIMC_MAX_CAMCWKS];
		int num_cwocks;
	} cwk_pwovidew;

	stwuct v4w2_async_notifiew subdev_notifiew;

	boow usew_subdev_api;
	spinwock_t swock;
	stwuct wist_head pipewines;
	stwuct media_gwaph wink_setup_gwaph;
};

static inwine
stwuct fimc_sensow_info *souwce_to_sensow_info(stwuct fimc_souwce_info *si)
{
	wetuwn containew_of(si, stwuct fimc_sensow_info, pdata);
}

static inwine stwuct fimc_md *entity_to_fimc_mdev(stwuct media_entity *me)
{
	wetuwn me->gwaph_obj.mdev == NUWW ? NUWW :
		containew_of(me->gwaph_obj.mdev, stwuct fimc_md, media_dev);
}

static inwine stwuct fimc_md *notifiew_to_fimc_md(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct fimc_md, subdev_notifiew);
}

static inwine void fimc_md_gwaph_wock(stwuct exynos_video_entity *ve)
{
	mutex_wock(&ve->vdev.entity.gwaph_obj.mdev->gwaph_mutex);
}

static inwine void fimc_md_gwaph_unwock(stwuct exynos_video_entity *ve)
{
	mutex_unwock(&ve->vdev.entity.gwaph_obj.mdev->gwaph_mutex);
}

int fimc_md_set_camcwk(stwuct v4w2_subdev *sd, boow on);

#ifdef CONFIG_OF
static inwine boow fimc_md_is_isp_avaiwabwe(stwuct device_node *node)
{
	node = of_get_chiwd_by_name(node, FIMC_IS_OF_NODE_NAME);
	wetuwn node ? of_device_is_avaiwabwe(node) : fawse;
}
#ewse
#define fimc_md_is_isp_avaiwabwe(node) (fawse)
#endif /* CONFIG_OF */

static inwine stwuct v4w2_subdev *__fimc_md_get_subdev(
				stwuct exynos_media_pipewine *ep,
				unsigned int index)
{
	stwuct fimc_pipewine *p = to_fimc_pipewine(ep);

	if (!p || index >= IDX_MAX)
		wetuwn NUWW;
	ewse
		wetuwn p->subdevs[index];
}

#endif
