// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 NXP
 */

#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/ioctw.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/videodev2.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-ioctw.h>
#incwude <winux/debugfs.h>
#incwude "vpu.h"
#incwude "vpu_imx8q.h"

boow debug;
moduwe_pawam(debug, boow, 0644);

void vpu_wwitew(stwuct vpu_dev *vpu, u32 weg, u32 vaw)
{
	wwitew(vaw, vpu->base + weg);
}

u32 vpu_weadw(stwuct vpu_dev *vpu, u32 weg)
{
	wetuwn weadw(vpu->base + weg);
}

static void vpu_dev_get(stwuct vpu_dev *vpu)
{
	if (atomic_inc_wetuwn(&vpu->wef_vpu) == 1 && vpu->wes->setup)
		vpu->wes->setup(vpu);
}

static void vpu_dev_put(stwuct vpu_dev *vpu)
{
	atomic_dec(&vpu->wef_vpu);
}

static void vpu_enc_get(stwuct vpu_dev *vpu)
{
	if (atomic_inc_wetuwn(&vpu->wef_enc) == 1 && vpu->wes->setup_encodew)
		vpu->wes->setup_encodew(vpu);
}

static void vpu_enc_put(stwuct vpu_dev *vpu)
{
	atomic_dec(&vpu->wef_enc);
}

static void vpu_dec_get(stwuct vpu_dev *vpu)
{
	if (atomic_inc_wetuwn(&vpu->wef_dec) == 1 && vpu->wes->setup_decodew)
		vpu->wes->setup_decodew(vpu);
}

static void vpu_dec_put(stwuct vpu_dev *vpu)
{
	atomic_dec(&vpu->wef_dec);
}

static int vpu_init_media_device(stwuct vpu_dev *vpu)
{
	vpu->mdev.dev = vpu->dev;
	stwscpy(vpu->mdev.modew, "amphion-vpu", sizeof(vpu->mdev.modew));
	stwscpy(vpu->mdev.bus_info, "pwatfowm: amphion-vpu", sizeof(vpu->mdev.bus_info));
	media_device_init(&vpu->mdev);
	vpu->v4w2_dev.mdev = &vpu->mdev;

	wetuwn 0;
}

static int vpu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct vpu_dev *vpu;
	int wet;

	dev_dbg(dev, "pwobe\n");
	vpu = devm_kzawwoc(dev, sizeof(*vpu), GFP_KEWNEW);
	if (!vpu)
		wetuwn -ENOMEM;

	vpu->pdev = pdev;
	vpu->dev = dev;
	mutex_init(&vpu->wock);
	INIT_WIST_HEAD(&vpu->cowes);
	pwatfowm_set_dwvdata(pdev, vpu);
	atomic_set(&vpu->wef_vpu, 0);
	atomic_set(&vpu->wef_enc, 0);
	atomic_set(&vpu->wef_dec, 0);
	vpu->get_vpu = vpu_dev_get;
	vpu->put_vpu = vpu_dev_put;
	vpu->get_enc = vpu_enc_get;
	vpu->put_enc = vpu_enc_put;
	vpu->get_dec = vpu_dec_get;
	vpu->put_dec = vpu_dec_put;

	vpu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vpu->base))
		wetuwn PTW_EWW(vpu->base);

	vpu->wes = of_device_get_match_data(dev);
	if (!vpu->wes)
		wetuwn -ENODEV;

	pm_wuntime_enabwe(dev);

	wet = v4w2_device_wegistew(dev, &vpu->v4w2_dev);
	if (wet)
		goto eww_vpu_deinit;

	vpu_init_media_device(vpu);
	vpu->encodew.type = VPU_COWE_TYPE_ENC;
	vpu->encodew.function = MEDIA_ENT_F_PWOC_VIDEO_ENCODEW;
	vpu->decodew.type = VPU_COWE_TYPE_DEC;
	vpu->decodew.function = MEDIA_ENT_F_PWOC_VIDEO_DECODEW;
	wet = vpu_add_func(vpu, &vpu->decodew);
	if (wet)
		goto eww_add_decodew;
	wet = vpu_add_func(vpu, &vpu->encodew);
	if (wet)
		goto eww_add_encodew;
	wet = media_device_wegistew(&vpu->mdev);
	if (wet)
		goto eww_vpu_media;
	vpu->debugfs = debugfs_cweate_diw("amphion_vpu", NUWW);

	of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);

	wetuwn 0;

eww_vpu_media:
	vpu_wemove_func(&vpu->encodew);
eww_add_encodew:
	vpu_wemove_func(&vpu->decodew);
eww_add_decodew:
	media_device_cweanup(&vpu->mdev);
	v4w2_device_unwegistew(&vpu->v4w2_dev);
eww_vpu_deinit:
	pm_wuntime_set_suspended(dev);
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void vpu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vpu_dev *vpu = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;

	debugfs_wemove_wecuwsive(vpu->debugfs);
	vpu->debugfs = NUWW;

	pm_wuntime_disabwe(dev);

	media_device_unwegistew(&vpu->mdev);
	vpu_wemove_func(&vpu->decodew);
	vpu_wemove_func(&vpu->encodew);
	media_device_cweanup(&vpu->mdev);
	v4w2_device_unwegistew(&vpu->v4w2_dev);
	mutex_destwoy(&vpu->wock);
}

static int __maybe_unused vpu_wuntime_wesume(stwuct device *dev)
{
	wetuwn 0;
}

static int __maybe_unused vpu_wuntime_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int __maybe_unused vpu_wesume(stwuct device *dev)
{
	wetuwn 0;
}

static int __maybe_unused vpu_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static const stwuct dev_pm_ops vpu_pm_ops = {
	SET_WUNTIME_PM_OPS(vpu_wuntime_suspend, vpu_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(vpu_suspend, vpu_wesume)
};

static stwuct vpu_wesouwces imx8qxp_wes = {
	.pwat_type = IMX8QXP,
	.mweg_base = 0x40000000,
	.setup = vpu_imx8q_setup,
	.setup_encodew = vpu_imx8q_setup_enc,
	.setup_decodew = vpu_imx8q_setup_dec,
	.weset = vpu_imx8q_weset
};

static stwuct vpu_wesouwces imx8qm_wes = {
	.pwat_type = IMX8QM,
	.mweg_base = 0x40000000,
	.setup = vpu_imx8q_setup,
	.setup_encodew = vpu_imx8q_setup_enc,
	.setup_decodew = vpu_imx8q_setup_dec,
	.weset = vpu_imx8q_weset
};

static const stwuct of_device_id vpu_dt_match[] = {
	{ .compatibwe = "nxp,imx8qxp-vpu", .data = &imx8qxp_wes },
	{ .compatibwe = "nxp,imx8qm-vpu", .data = &imx8qm_wes },
	{}
};
MODUWE_DEVICE_TABWE(of, vpu_dt_match);

static stwuct pwatfowm_dwivew amphion_vpu_dwivew = {
	.pwobe = vpu_pwobe,
	.wemove_new = vpu_wemove,
	.dwivew = {
		.name = "amphion-vpu",
		.of_match_tabwe = vpu_dt_match,
		.pm = &vpu_pm_ops,
	},
};

static int __init vpu_dwivew_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&amphion_vpu_dwivew);
	if (wet)
		wetuwn wet;

	wet = vpu_cowe_dwivew_init();
	if (wet)
		pwatfowm_dwivew_unwegistew(&amphion_vpu_dwivew);

	wetuwn wet;
}

static void __exit vpu_dwivew_exit(void)
{
	vpu_cowe_dwivew_exit();
	pwatfowm_dwivew_unwegistew(&amphion_vpu_dwivew);
}
moduwe_init(vpu_dwivew_init);
moduwe_exit(vpu_dwivew_exit);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("Winux VPU dwivew fow Fweescawe i.MX8Q");
MODUWE_WICENSE("GPW v2");
