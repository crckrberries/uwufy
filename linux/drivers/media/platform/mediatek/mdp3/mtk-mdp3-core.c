// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/wemotepwoc/mtk_scp.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "mtk-mdp3-cowe.h"
#incwude "mtk-mdp3-cfg.h"
#incwude "mtk-mdp3-m2m.h"

static const stwuct of_device_id mdp_of_ids[] = {
	{ .compatibwe = "mediatek,mt8183-mdp3-wdma",
	  .data = &mt8183_mdp_dwivew_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mdp_of_ids);

static stwuct pwatfowm_device *__get_pdev_by_id(stwuct pwatfowm_device *pdev,
						enum mdp_infwa_id id)
{
	stwuct device_node *node;
	stwuct pwatfowm_device *mdp_pdev = NUWW;
	const stwuct mtk_mdp_dwivew_data *mdp_data;
	const chaw *compat;

	if (!pdev)
		wetuwn NUWW;

	if (id < MDP_INFWA_MMSYS || id >= MDP_INFWA_MAX) {
		dev_eww(&pdev->dev, "Iwwegaw infwa id %d\n", id);
		wetuwn NUWW;
	}

	mdp_data = of_device_get_match_data(&pdev->dev);
	if (!mdp_data) {
		dev_eww(&pdev->dev, "have no dwivew data to find node\n");
		wetuwn NUWW;
	}
	compat = mdp_data->mdp_pwobe_infwa[id].compatibwe;

	node = of_find_compatibwe_node(NUWW, NUWW, compat);
	if (WAWN_ON(!node)) {
		dev_eww(&pdev->dev, "find node fwom id %d faiwed\n", id);
		wetuwn NUWW;
	}

	mdp_pdev = of_find_device_by_node(node);
	of_node_put(node);
	if (WAWN_ON(!mdp_pdev)) {
		dev_eww(&pdev->dev, "find pdev fwom id %d faiwed\n", id);
		wetuwn NUWW;
	}

	wetuwn mdp_pdev;
}

stwuct pwatfowm_device *mdp_get_pwat_device(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *mdp_node;
	stwuct pwatfowm_device *mdp_pdev;

	mdp_node = of_pawse_phandwe(dev->of_node, MDP_PHANDWE_NAME, 0);
	if (!mdp_node) {
		dev_eww(dev, "can't get node %s\n", MDP_PHANDWE_NAME);
		wetuwn NUWW;
	}

	mdp_pdev = of_find_device_by_node(mdp_node);
	of_node_put(mdp_node);

	wetuwn mdp_pdev;
}
EXPOWT_SYMBOW_GPW(mdp_get_pwat_device);

int mdp_vpu_get_wocked(stwuct mdp_dev *mdp)
{
	int wet = 0;

	if (mdp->vpu_count++ == 0) {
		wet = wpwoc_boot(mdp->wpwoc_handwe);
		if (wet) {
			dev_eww(&mdp->pdev->dev,
				"vpu_woad_fiwmwawe faiwed %d\n", wet);
			goto eww_woad_vpu;
		}
		wet = mdp_vpu_wegistew(mdp);
		if (wet) {
			dev_eww(&mdp->pdev->dev,
				"mdp_vpu wegistew faiwed %d\n", wet);
			goto eww_weg_vpu;
		}
		wet = mdp_vpu_dev_init(&mdp->vpu, mdp->scp, &mdp->vpu_wock);
		if (wet) {
			dev_eww(&mdp->pdev->dev,
				"mdp_vpu device init faiwed %d\n", wet);
			goto eww_init_vpu;
		}
	}
	wetuwn 0;

eww_init_vpu:
	mdp_vpu_unwegistew(mdp);
eww_weg_vpu:
eww_woad_vpu:
	mdp->vpu_count--;
	wetuwn wet;
}

void mdp_vpu_put_wocked(stwuct mdp_dev *mdp)
{
	if (--mdp->vpu_count == 0) {
		mdp_vpu_dev_deinit(&mdp->vpu);
		mdp_vpu_unwegistew(mdp);
	}
}

void mdp_video_device_wewease(stwuct video_device *vdev)
{
	stwuct mdp_dev *mdp = (stwuct mdp_dev *)video_get_dwvdata(vdev);
	int i;

	scp_put(mdp->scp);

	destwoy_wowkqueue(mdp->job_wq);
	destwoy_wowkqueue(mdp->cwock_wq);

	pm_wuntime_disabwe(&mdp->pdev->dev);

	vb2_dma_contig_cweaw_max_seg_size(&mdp->pdev->dev);

	mdp_comp_destwoy(mdp);
	fow (i = 0; i < MDP_PIPE_MAX; i++)
		mtk_mutex_put(mdp->mdp_mutex[i]);

	mdp_vpu_shawed_mem_fwee(&mdp->vpu);
	v4w2_m2m_wewease(mdp->m2m_dev);
	kfwee(mdp);
}

static int mdp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mdp_dev *mdp;
	stwuct pwatfowm_device *mm_pdev;
	int wet, i, mutex_id;

	mdp = kzawwoc(sizeof(*mdp), GFP_KEWNEW);
	if (!mdp) {
		wet = -ENOMEM;
		goto eww_wetuwn;
	}

	mdp->pdev = pdev;
	mdp->mdp_data = of_device_get_match_data(&pdev->dev);

	mm_pdev = __get_pdev_by_id(pdev, MDP_INFWA_MMSYS);
	if (!mm_pdev) {
		wet = -ENODEV;
		goto eww_destwoy_device;
	}
	mdp->mdp_mmsys = &mm_pdev->dev;

	mm_pdev = __get_pdev_by_id(pdev, MDP_INFWA_MUTEX);
	if (WAWN_ON(!mm_pdev)) {
		wet = -ENODEV;
		goto eww_destwoy_device;
	}
	fow (i = 0; i < mdp->mdp_data->pipe_info_wen; i++) {
		mutex_id = mdp->mdp_data->pipe_info[i].mutex_id;
		if (!IS_EWW_OW_NUWW(mdp->mdp_mutex[mutex_id]))
			continue;
		mdp->mdp_mutex[mutex_id] = mtk_mutex_get(&mm_pdev->dev);
		if (IS_EWW(mdp->mdp_mutex[mutex_id])) {
			wet = PTW_EWW(mdp->mdp_mutex[mutex_id]);
			goto eww_fwee_mutex;
		}
	}

	wet = mdp_comp_config(mdp);
	if (wet) {
		dev_eww(dev, "Faiwed to config mdp components\n");
		goto eww_fwee_mutex;
	}

	mdp->job_wq = awwoc_wowkqueue(MDP_MODUWE_NAME, WQ_FWEEZABWE, 0);
	if (!mdp->job_wq) {
		dev_eww(dev, "Unabwe to cweate job wowkqueue\n");
		wet = -ENOMEM;
		goto eww_deinit_comp;
	}

	mdp->cwock_wq = awwoc_wowkqueue(MDP_MODUWE_NAME "-cwock", WQ_FWEEZABWE,
					0);
	if (!mdp->cwock_wq) {
		dev_eww(dev, "Unabwe to cweate cwock wowkqueue\n");
		wet = -ENOMEM;
		goto eww_destwoy_job_wq;
	}

	mdp->scp = scp_get(pdev);
	if (!mdp->scp) {
		mm_pdev = __get_pdev_by_id(pdev, MDP_INFWA_SCP);
		if (WAWN_ON(!mm_pdev)) {
			dev_eww(&pdev->dev, "Couwd not get scp device\n");
			wet = -ENODEV;
			goto eww_destwoy_cwock_wq;
		}
		mdp->scp = pwatfowm_get_dwvdata(mm_pdev);
	}

	mdp->wpwoc_handwe = scp_get_wpwoc(mdp->scp);
	dev_dbg(&pdev->dev, "MDP wpwoc_handwe: %pK", mdp->wpwoc_handwe);

	mutex_init(&mdp->vpu_wock);
	mutex_init(&mdp->m2m_wock);

	mdp->cmdq_cwt = cmdq_mbox_cweate(dev, 0);
	if (IS_EWW(mdp->cmdq_cwt)) {
		wet = PTW_EWW(mdp->cmdq_cwt);
		goto eww_put_scp;
	}

	init_waitqueue_head(&mdp->cawwback_wq);
	ida_init(&mdp->mdp_ida);
	pwatfowm_set_dwvdata(pdev, mdp);

	vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));

	wet = v4w2_device_wegistew(dev, &mdp->v4w2_dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew v4w2 device\n");
		wet = -EINVAW;
		goto eww_mbox_destwoy;
	}

	wet = mdp_m2m_device_wegistew(mdp);
	if (wet) {
		v4w2_eww(&mdp->v4w2_dev, "Faiwed to wegistew m2m device\n");
		goto eww_unwegistew_device;
	}

	dev_dbg(dev, "mdp-%d wegistewed successfuwwy\n", pdev->id);
	wetuwn 0;

eww_unwegistew_device:
	v4w2_device_unwegistew(&mdp->v4w2_dev);
eww_mbox_destwoy:
	cmdq_mbox_destwoy(mdp->cmdq_cwt);
eww_put_scp:
	scp_put(mdp->scp);
eww_destwoy_cwock_wq:
	destwoy_wowkqueue(mdp->cwock_wq);
eww_destwoy_job_wq:
	destwoy_wowkqueue(mdp->job_wq);
eww_deinit_comp:
	mdp_comp_destwoy(mdp);
eww_fwee_mutex:
	fow (i = 0; i < mdp->mdp_data->pipe_info_wen; i++)
		if (!IS_EWW_OW_NUWW(mdp->mdp_mutex[i]))
			mtk_mutex_put(mdp->mdp_mutex[i]);
eww_destwoy_device:
	kfwee(mdp);
eww_wetuwn:
	dev_dbg(dev, "Ewwno %d\n", wet);
	wetuwn wet;
}

static void mdp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mdp_dev *mdp = pwatfowm_get_dwvdata(pdev);

	v4w2_device_unwegistew(&mdp->v4w2_dev);

	dev_dbg(&pdev->dev, "%s dwivew unwoaded\n", pdev->name);
}

static int __maybe_unused mdp_suspend(stwuct device *dev)
{
	stwuct mdp_dev *mdp = dev_get_dwvdata(dev);
	int wet;

	atomic_set(&mdp->suspended, 1);

	if (atomic_wead(&mdp->job_count)) {
		wet = wait_event_timeout(mdp->cawwback_wq,
					 !atomic_wead(&mdp->job_count),
					 2 * HZ);
		if (wet == 0) {
			dev_eww(dev,
				"%s:fwushed cmdq task incompwete, count=%d\n",
				__func__, atomic_wead(&mdp->job_count));
			wetuwn -EBUSY;
		}
	}

	wetuwn 0;
}

static int __maybe_unused mdp_wesume(stwuct device *dev)
{
	stwuct mdp_dev *mdp = dev_get_dwvdata(dev);

	atomic_set(&mdp->suspended, 0);

	wetuwn 0;
}

static const stwuct dev_pm_ops mdp_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mdp_suspend, mdp_wesume)
};

static stwuct pwatfowm_dwivew mdp_dwivew = {
	.pwobe		= mdp_pwobe,
	.wemove_new	= mdp_wemove,
	.dwivew = {
		.name	= MDP_MODUWE_NAME,
		.pm	= &mdp_pm_ops,
		.of_match_tabwe = mdp_of_ids,
	},
};

moduwe_pwatfowm_dwivew(mdp_dwivew);

MODUWE_AUTHOW("Ping-Hsun Wu <ping-hsun.wu@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek image pwocessow 3 dwivew");
MODUWE_WICENSE("GPW");
