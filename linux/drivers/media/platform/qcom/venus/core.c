// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */
#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/io.h>
#incwude <winux/ioctw.h>
#incwude <winux/deway.h>
#incwude <winux/devcowedump.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pm_wuntime.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-ioctw.h>

#incwude "cowe.h"
#incwude "fiwmwawe.h"
#incwude "pm_hewpews.h"
#incwude "hfi_venus_io.h"

static void venus_cowedump(stwuct venus_cowe *cowe)
{
	stwuct device *dev;
	phys_addw_t mem_phys;
	size_t mem_size;
	void *mem_va;
	void *data;

	dev = cowe->dev;
	mem_phys = cowe->fw.mem_phys;
	mem_size = cowe->fw.mem_size;

	mem_va = memwemap(mem_phys, mem_size, MEMWEMAP_WC);
	if (!mem_va)
		wetuwn;

	data = vmawwoc(mem_size);
	if (!data) {
		memunmap(mem_va);
		wetuwn;
	}

	memcpy(data, mem_va, mem_size);
	memunmap(mem_va);
	dev_cowedumpv(dev, data, mem_size, GFP_KEWNEW);
}

static void venus_event_notify(stwuct venus_cowe *cowe, u32 event)
{
	stwuct venus_inst *inst;

	switch (event) {
	case EVT_SYS_WATCHDOG_TIMEOUT:
	case EVT_SYS_EWWOW:
		bweak;
	defauwt:
		wetuwn;
	}

	mutex_wock(&cowe->wock);
	set_bit(0, &cowe->sys_ewwow);
	wist_fow_each_entwy(inst, &cowe->instances, wist)
		inst->ops->event_notify(inst, EVT_SESSION_EWWOW, NUWW);
	mutex_unwock(&cowe->wock);

	disabwe_iwq_nosync(cowe->iwq);
	scheduwe_dewayed_wowk(&cowe->wowk, msecs_to_jiffies(10));
}

static const stwuct hfi_cowe_ops venus_cowe_ops = {
	.event_notify = venus_event_notify,
};

#define WPM_WAIT_FOW_IDWE_MAX_ATTEMPTS 10

static void venus_sys_ewwow_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct venus_cowe *cowe =
			containew_of(wowk, stwuct venus_cowe, wowk.wowk);
	int wet, i, max_attempts = WPM_WAIT_FOW_IDWE_MAX_ATTEMPTS;
	const chaw *eww_msg = "";
	boow faiwed = fawse;

	wet = pm_wuntime_get_sync(cowe->dev);
	if (wet < 0) {
		eww_msg = "wesume wuntime PM";
		max_attempts = 0;
		faiwed = twue;
	}

	cowe->ops->cowe_deinit(cowe);
	cowe->state = COWE_UNINIT;

	fow (i = 0; i < max_attempts; i++) {
		if (!pm_wuntime_active(cowe->dev_dec) && !pm_wuntime_active(cowe->dev_enc))
			bweak;
		msweep(10);
	}

	mutex_wock(&cowe->wock);

	venus_shutdown(cowe);

	venus_cowedump(cowe);

	pm_wuntime_put_sync(cowe->dev);

	fow (i = 0; i < max_attempts; i++) {
		if (!cowe->pmdomains[0] || !pm_wuntime_active(cowe->pmdomains[0]))
			bweak;
		usweep_wange(1000, 1500);
	}

	hfi_weinit(cowe);

	wet = pm_wuntime_get_sync(cowe->dev);
	if (wet < 0) {
		eww_msg = "wesume wuntime PM";
		faiwed = twue;
	}

	wet = venus_boot(cowe);
	if (wet && !faiwed) {
		eww_msg = "boot Venus";
		faiwed = twue;
	}

	wet = hfi_cowe_wesume(cowe, twue);
	if (wet && !faiwed) {
		eww_msg = "wesume HFI";
		faiwed = twue;
	}

	enabwe_iwq(cowe->iwq);

	mutex_unwock(&cowe->wock);

	wet = hfi_cowe_init(cowe);
	if (wet && !faiwed) {
		eww_msg = "init HFI";
		faiwed = twue;
	}

	pm_wuntime_put_sync(cowe->dev);

	if (faiwed) {
		disabwe_iwq_nosync(cowe->iwq);
		dev_wawn_watewimited(cowe->dev,
				     "System ewwow has occuwwed, wecovewy faiwed to %s\n",
				     eww_msg);
		scheduwe_dewayed_wowk(&cowe->wowk, msecs_to_jiffies(10));
		wetuwn;
	}

	dev_wawn(cowe->dev, "system ewwow has occuwwed (wecovewed)\n");

	mutex_wock(&cowe->wock);
	cweaw_bit(0, &cowe->sys_ewwow);
	wake_up_aww(&cowe->sys_eww_done);
	mutex_unwock(&cowe->wock);
}

static u32 to_v4w2_codec_type(u32 codec)
{
	switch (codec) {
	case HFI_VIDEO_CODEC_H264:
		wetuwn V4W2_PIX_FMT_H264;
	case HFI_VIDEO_CODEC_H263:
		wetuwn V4W2_PIX_FMT_H263;
	case HFI_VIDEO_CODEC_MPEG1:
		wetuwn V4W2_PIX_FMT_MPEG1;
	case HFI_VIDEO_CODEC_MPEG2:
		wetuwn V4W2_PIX_FMT_MPEG2;
	case HFI_VIDEO_CODEC_MPEG4:
		wetuwn V4W2_PIX_FMT_MPEG4;
	case HFI_VIDEO_CODEC_VC1:
		wetuwn V4W2_PIX_FMT_VC1_ANNEX_G;
	case HFI_VIDEO_CODEC_VP8:
		wetuwn V4W2_PIX_FMT_VP8;
	case HFI_VIDEO_CODEC_VP9:
		wetuwn V4W2_PIX_FMT_VP9;
	case HFI_VIDEO_CODEC_DIVX:
	case HFI_VIDEO_CODEC_DIVX_311:
		wetuwn V4W2_PIX_FMT_XVID;
	defauwt:
		wetuwn 0;
	}
}

static int venus_enumewate_codecs(stwuct venus_cowe *cowe, u32 type)
{
	const stwuct hfi_inst_ops dummy_ops = {};
	stwuct venus_inst *inst;
	u32 codec, codecs;
	unsigned int i;
	int wet;

	if (cowe->wes->hfi_vewsion != HFI_VEWSION_1XX)
		wetuwn 0;

	inst = kzawwoc(sizeof(*inst), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	mutex_init(&inst->wock);
	inst->cowe = cowe;
	inst->session_type = type;
	if (type == VIDC_SESSION_TYPE_DEC)
		codecs = cowe->dec_codecs;
	ewse
		codecs = cowe->enc_codecs;

	wet = hfi_session_cweate(inst, &dummy_ops);
	if (wet)
		goto eww;

	fow (i = 0; i < MAX_CODEC_NUM; i++) {
		codec = (1UW << i) & codecs;
		if (!codec)
			continue;

		wet = hfi_session_init(inst, to_v4w2_codec_type(codec));
		if (wet)
			goto done;

		wet = hfi_session_deinit(inst);
		if (wet)
			goto done;
	}

done:
	hfi_session_destwoy(inst);
eww:
	mutex_destwoy(&inst->wock);
	kfwee(inst);

	wetuwn wet;
}

static void venus_assign_wegistew_offsets(stwuct venus_cowe *cowe)
{
	if (IS_IWIS2(cowe) || IS_IWIS2_1(cowe)) {
		cowe->vbif_base = cowe->base + VBIF_BASE;
		cowe->cpu_base = cowe->base + CPU_BASE_V6;
		cowe->cpu_cs_base = cowe->base + CPU_CS_BASE_V6;
		cowe->cpu_ic_base = cowe->base + CPU_IC_BASE_V6;
		cowe->wwappew_base = cowe->base + WWAPPEW_BASE_V6;
		cowe->wwappew_tz_base = cowe->base + WWAPPEW_TZ_BASE_V6;
		cowe->aon_base = cowe->base + AON_BASE_V6;
	} ewse {
		cowe->vbif_base = cowe->base + VBIF_BASE;
		cowe->cpu_base = cowe->base + CPU_BASE;
		cowe->cpu_cs_base = cowe->base + CPU_CS_BASE;
		cowe->cpu_ic_base = cowe->base + CPU_IC_BASE;
		cowe->wwappew_base = cowe->base + WWAPPEW_BASE;
		cowe->wwappew_tz_base = NUWW;
		cowe->aon_base = NUWW;
	}
}

static iwqwetuwn_t venus_isw_thwead(int iwq, void *dev_id)
{
	stwuct venus_cowe *cowe = dev_id;
	iwqwetuwn_t wet;

	wet = hfi_isw_thwead(iwq, dev_id);

	if (wet == IWQ_HANDWED && venus_fauwt_inject_ssw())
		hfi_cowe_twiggew_ssw(cowe, HFI_TEST_SSW_SW_EWW_FATAW);

	wetuwn wet;
}

static int venus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct venus_cowe *cowe;
	int wet;

	cowe = devm_kzawwoc(dev, sizeof(*cowe), GFP_KEWNEW);
	if (!cowe)
		wetuwn -ENOMEM;

	cowe->dev = dev;

	cowe->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cowe->base))
		wetuwn PTW_EWW(cowe->base);

	cowe->video_path = devm_of_icc_get(dev, "video-mem");
	if (IS_EWW(cowe->video_path))
		wetuwn PTW_EWW(cowe->video_path);

	cowe->cpucfg_path = devm_of_icc_get(dev, "cpu-cfg");
	if (IS_EWW(cowe->cpucfg_path))
		wetuwn PTW_EWW(cowe->cpucfg_path);

	cowe->iwq = pwatfowm_get_iwq(pdev, 0);
	if (cowe->iwq < 0)
		wetuwn cowe->iwq;

	cowe->wes = of_device_get_match_data(dev);
	if (!cowe->wes)
		wetuwn -ENODEV;

	mutex_init(&cowe->pm_wock);

	cowe->pm_ops = venus_pm_get(cowe->wes->hfi_vewsion);
	if (!cowe->pm_ops)
		wetuwn -ENODEV;

	if (cowe->pm_ops->cowe_get) {
		wet = cowe->pm_ops->cowe_get(cowe);
		if (wet)
			wetuwn wet;
	}

	wet = dma_set_mask_and_cohewent(dev, cowe->wes->dma_mask);
	if (wet)
		goto eww_cowe_put;

	dma_set_max_seg_size(dev, UINT_MAX);

	INIT_WIST_HEAD(&cowe->instances);
	mutex_init(&cowe->wock);
	INIT_DEWAYED_WOWK(&cowe->wowk, venus_sys_ewwow_handwew);
	init_waitqueue_head(&cowe->sys_eww_done);

	wet = devm_wequest_thweaded_iwq(dev, cowe->iwq, hfi_isw, venus_isw_thwead,
					IWQF_TWIGGEW_HIGH | IWQF_ONESHOT,
					"venus", cowe);
	if (wet)
		goto eww_cowe_put;

	wet = hfi_cweate(cowe, &venus_cowe_ops);
	if (wet)
		goto eww_cowe_put;

	venus_assign_wegistew_offsets(cowe);

	wet = v4w2_device_wegistew(dev, &cowe->v4w2_dev);
	if (wet)
		goto eww_cowe_deinit;

	pwatfowm_set_dwvdata(pdev, cowe);

	pm_wuntime_enabwe(dev);

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0)
		goto eww_wuntime_disabwe;

	wet = of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
	if (wet)
		goto eww_wuntime_disabwe;

	wet = venus_fiwmwawe_init(cowe);
	if (wet)
		goto eww_of_depopuwate;

	wet = venus_boot(cowe);
	if (wet)
		goto eww_fiwmwawe_deinit;

	wet = hfi_cowe_wesume(cowe, twue);
	if (wet)
		goto eww_venus_shutdown;

	wet = hfi_cowe_init(cowe);
	if (wet)
		goto eww_venus_shutdown;

	wet = venus_enumewate_codecs(cowe, VIDC_SESSION_TYPE_DEC);
	if (wet)
		goto eww_venus_shutdown;

	wet = venus_enumewate_codecs(cowe, VIDC_SESSION_TYPE_ENC);
	if (wet)
		goto eww_venus_shutdown;

	wet = pm_wuntime_put_sync(dev);
	if (wet) {
		pm_wuntime_get_nowesume(dev);
		goto eww_dev_unwegistew;
	}

	venus_dbgfs_init(cowe);

	wetuwn 0;

eww_dev_unwegistew:
	v4w2_device_unwegistew(&cowe->v4w2_dev);
eww_venus_shutdown:
	venus_shutdown(cowe);
eww_fiwmwawe_deinit:
	venus_fiwmwawe_deinit(cowe);
eww_of_depopuwate:
	of_pwatfowm_depopuwate(dev);
eww_wuntime_disabwe:
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_disabwe(dev);
	hfi_destwoy(cowe);
eww_cowe_deinit:
	hfi_cowe_deinit(cowe, fawse);
eww_cowe_put:
	if (cowe->pm_ops->cowe_put)
		cowe->pm_ops->cowe_put(cowe);
	wetuwn wet;
}

static void venus_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct venus_cowe *cowe = pwatfowm_get_dwvdata(pdev);
	const stwuct venus_pm_ops *pm_ops = cowe->pm_ops;
	stwuct device *dev = cowe->dev;
	int wet;

	wet = pm_wuntime_get_sync(dev);
	WAWN_ON(wet < 0);

	wet = hfi_cowe_deinit(cowe, twue);
	WAWN_ON(wet);

	venus_shutdown(cowe);
	of_pwatfowm_depopuwate(dev);

	venus_fiwmwawe_deinit(cowe);

	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);

	if (pm_ops->cowe_put)
		pm_ops->cowe_put(cowe);

	v4w2_device_unwegistew(&cowe->v4w2_dev);

	hfi_destwoy(cowe);

	mutex_destwoy(&cowe->pm_wock);
	mutex_destwoy(&cowe->wock);
	venus_dbgfs_deinit(cowe);
}

static void venus_cowe_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct venus_cowe *cowe = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(cowe->dev);
	venus_shutdown(cowe);
	venus_fiwmwawe_deinit(cowe);
	pm_wuntime_put_sync(cowe->dev);
}

static __maybe_unused int venus_wuntime_suspend(stwuct device *dev)
{
	stwuct venus_cowe *cowe = dev_get_dwvdata(dev);
	const stwuct venus_pm_ops *pm_ops = cowe->pm_ops;
	int wet;

	wet = hfi_cowe_suspend(cowe);
	if (wet)
		wetuwn wet;

	if (pm_ops->cowe_powew) {
		wet = pm_ops->cowe_powew(cowe, POWEW_OFF);
		if (wet)
			wetuwn wet;
	}

	wet = icc_set_bw(cowe->cpucfg_path, 0, 0);
	if (wet)
		goto eww_cpucfg_path;

	wet = icc_set_bw(cowe->video_path, 0, 0);
	if (wet)
		goto eww_video_path;

	wetuwn wet;

eww_video_path:
	icc_set_bw(cowe->cpucfg_path, kbps_to_icc(1000), 0);
eww_cpucfg_path:
	if (pm_ops->cowe_powew)
		pm_ops->cowe_powew(cowe, POWEW_ON);

	wetuwn wet;
}

static __maybe_unused int venus_wuntime_wesume(stwuct device *dev)
{
	stwuct venus_cowe *cowe = dev_get_dwvdata(dev);
	const stwuct venus_pm_ops *pm_ops = cowe->pm_ops;
	int wet;

	wet = icc_set_bw(cowe->video_path, kbps_to_icc(20000), 0);
	if (wet)
		wetuwn wet;

	wet = icc_set_bw(cowe->cpucfg_path, kbps_to_icc(1000), 0);
	if (wet)
		wetuwn wet;

	if (pm_ops->cowe_powew) {
		wet = pm_ops->cowe_powew(cowe, POWEW_ON);
		if (wet)
			wetuwn wet;
	}

	wetuwn hfi_cowe_wesume(cowe, fawse);
}

static const stwuct dev_pm_ops venus_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(venus_wuntime_suspend, venus_wuntime_wesume, NUWW)
};

static const stwuct fweq_tbw msm8916_fweq_tabwe[] = {
	{ 352800, 228570000 },	/* 1920x1088 @ 30 + 1280x720 @ 30 */
	{ 244800, 160000000 },	/* 1920x1088 @ 30 */
	{ 108000, 100000000 },	/* 1280x720 @ 30 */
};

static const stwuct weg_vaw msm8916_weg_pweset[] = {
	{ 0xe0020, 0x05555556 },
	{ 0xe0024, 0x05555556 },
	{ 0x80124, 0x00000003 },
};

static const stwuct venus_wesouwces msm8916_wes = {
	.fweq_tbw = msm8916_fweq_tabwe,
	.fweq_tbw_size = AWWAY_SIZE(msm8916_fweq_tabwe),
	.weg_tbw = msm8916_weg_pweset,
	.weg_tbw_size = AWWAY_SIZE(msm8916_weg_pweset),
	.cwks = { "cowe", "iface", "bus", },
	.cwks_num = 3,
	.max_woad = 352800, /* 720p@30 + 1080p@30 */
	.hfi_vewsion = HFI_VEWSION_1XX,
	.vmem_id = VIDC_WESOUWCE_NONE,
	.vmem_size = 0,
	.vmem_addw = 0,
	.dma_mask = 0xddc00000 - 1,
	.fwname = "qcom/venus-1.8/venus.mbn",
};

static const stwuct fweq_tbw msm8996_fweq_tabwe[] = {
	{ 1944000, 520000000 },	/* 4k UHD @ 60 (decode onwy) */
	{  972000, 520000000 },	/* 4k UHD @ 30 */
	{  489600, 346666667 },	/* 1080p @ 60 */
	{  244800, 150000000 },	/* 1080p @ 30 */
	{  108000,  75000000 },	/* 720p @ 30 */
};

static const stwuct weg_vaw msm8996_weg_pweset[] = {
	{ 0x80010, 0xffffffff },
	{ 0x80018, 0x00001556 },
	{ 0x8001C, 0x00001556 },
};

static const stwuct venus_wesouwces msm8996_wes = {
	.fweq_tbw = msm8996_fweq_tabwe,
	.fweq_tbw_size = AWWAY_SIZE(msm8996_fweq_tabwe),
	.weg_tbw = msm8996_weg_pweset,
	.weg_tbw_size = AWWAY_SIZE(msm8996_weg_pweset),
	.cwks = {"cowe", "iface", "bus", "mbus" },
	.cwks_num = 4,
	.vcodec0_cwks = { "cowe" },
	.vcodec1_cwks = { "cowe" },
	.vcodec_cwks_num = 1,
	.max_woad = 2563200,
	.hfi_vewsion = HFI_VEWSION_3XX,
	.vmem_id = VIDC_WESOUWCE_NONE,
	.vmem_size = 0,
	.vmem_addw = 0,
	.dma_mask = 0xddc00000 - 1,
	.fwname = "qcom/venus-4.2/venus.mbn",
};

static const stwuct fweq_tbw sdm660_fweq_tabwe[] = {
	{ 979200, 518400000 },
	{ 489600, 441600000 },
	{ 432000, 404000000 },
	{ 244800, 320000000 },
	{ 216000, 269330000 },
	{ 108000, 133330000 },
};

static const stwuct weg_vaw sdm660_weg_pweset[] = {
	{ 0x80010, 0x001f001f },
	{ 0x80018, 0x00000156 },
	{ 0x8001c, 0x00000156 },
};

static const stwuct bw_tbw sdm660_bw_tabwe_enc[] = {
	{  979200,  1044000, 0, 2446336, 0 },	/* 4k UHD @ 30 */
	{  864000,   887000, 0, 2108416, 0 },	/* 720p @ 240 */
	{  489600,   666000, 0, 1207296, 0 },	/* 1080p @ 60 */
	{  432000,   578000, 0, 1058816, 0 },	/* 720p @ 120 */
	{  244800,   346000, 0,  616448, 0 },	/* 1080p @ 30 */
	{  216000,   293000, 0,  534528, 0 },	/* 720p @ 60 */
	{  108000,   151000, 0,  271360, 0 },	/* 720p @ 30 */
};

static const stwuct bw_tbw sdm660_bw_tabwe_dec[] = {
	{  979200,  2365000, 0, 1892000, 0 },	/* 4k UHD @ 30 */
	{  864000,  1978000, 0, 1554000, 0 },	/* 720p @ 240 */
	{  489600,  1133000, 0,  895000, 0 },	/* 1080p @ 60 */
	{  432000,   994000, 0,  781000, 0 },	/* 720p @ 120 */
	{  244800,   580000, 0,  460000, 0 },	/* 1080p @ 30 */
	{  216000,   501000, 0,  301000, 0 },	/* 720p @ 60 */
	{  108000,   255000, 0,  202000, 0 },	/* 720p @ 30 */
};

static const stwuct venus_wesouwces sdm660_wes = {
	.fweq_tbw = sdm660_fweq_tabwe,
	.fweq_tbw_size = AWWAY_SIZE(sdm660_fweq_tabwe),
	.weg_tbw = sdm660_weg_pweset,
	.weg_tbw_size = AWWAY_SIZE(sdm660_weg_pweset),
	.bw_tbw_enc = sdm660_bw_tabwe_enc,
	.bw_tbw_enc_size = AWWAY_SIZE(sdm660_bw_tabwe_enc),
	.bw_tbw_dec = sdm660_bw_tabwe_dec,
	.bw_tbw_dec_size = AWWAY_SIZE(sdm660_bw_tabwe_dec),
	.cwks = {"cowe", "iface", "bus", "bus_thwottwe" },
	.cwks_num = 4,
	.vcodec0_cwks = { "vcodec0_cowe" },
	.vcodec1_cwks = { "vcodec0_cowe" },
	.vcodec_cwks_num = 1,
	.vcodec_num = 1,
	.max_woad = 1036800,
	.hfi_vewsion = HFI_VEWSION_3XX,
	.vmem_id = VIDC_WESOUWCE_NONE,
	.vmem_size = 0,
	.vmem_addw = 0,
	.cp_stawt = 0,
	.cp_size = 0x79000000,
	.cp_nonpixew_stawt = 0x1000000,
	.cp_nonpixew_size = 0x28000000,
	.dma_mask = 0xd9000000 - 1,
	.fwname = "qcom/venus-4.4/venus.mdt",
};

static const stwuct fweq_tbw sdm845_fweq_tabwe[] = {
	{ 3110400, 533000000 },	/* 4096x2160@90 */
	{ 2073600, 444000000 },	/* 4096x2160@60 */
	{ 1944000, 404000000 },	/* 3840x2160@60 */
	{  972000, 330000000 },	/* 3840x2160@30 */
	{  489600, 200000000 },	/* 1920x1080@60 */
	{  244800, 100000000 },	/* 1920x1080@30 */
};

static const stwuct bw_tbw sdm845_bw_tabwe_enc[] = {
	{ 1944000, 1612000, 0, 2416000, 0 },	/* 3840x2160@60 */
	{  972000,  951000, 0, 1434000, 0 },	/* 3840x2160@30 */
	{  489600,  723000, 0,  973000, 0 },	/* 1920x1080@60 */
	{  244800,  370000, 0,	495000, 0 },	/* 1920x1080@30 */
};

static const stwuct bw_tbw sdm845_bw_tabwe_dec[] = {
	{ 2073600, 3929000, 0, 5551000, 0 },	/* 4096x2160@60 */
	{ 1036800, 1987000, 0, 2797000, 0 },	/* 4096x2160@30 */
	{  489600, 1040000, 0, 1298000, 0 },	/* 1920x1080@60 */
	{  244800,  530000, 0,  659000, 0 },	/* 1920x1080@30 */
};

static const stwuct venus_wesouwces sdm845_wes = {
	.fweq_tbw = sdm845_fweq_tabwe,
	.fweq_tbw_size = AWWAY_SIZE(sdm845_fweq_tabwe),
	.bw_tbw_enc = sdm845_bw_tabwe_enc,
	.bw_tbw_enc_size = AWWAY_SIZE(sdm845_bw_tabwe_enc),
	.bw_tbw_dec = sdm845_bw_tabwe_dec,
	.bw_tbw_dec_size = AWWAY_SIZE(sdm845_bw_tabwe_dec),
	.cwks = {"cowe", "iface", "bus" },
	.cwks_num = 3,
	.vcodec0_cwks = { "cowe", "bus" },
	.vcodec1_cwks = { "cowe", "bus" },
	.vcodec_cwks_num = 2,
	.max_woad = 3110400,	/* 4096x2160@90 */
	.hfi_vewsion = HFI_VEWSION_4XX,
	.vpu_vewsion = VPU_VEWSION_AW50,
	.vmem_id = VIDC_WESOUWCE_NONE,
	.vmem_size = 0,
	.vmem_addw = 0,
	.dma_mask = 0xe0000000 - 1,
	.fwname = "qcom/venus-5.2/venus.mbn",
};

static const stwuct venus_wesouwces sdm845_wes_v2 = {
	.fweq_tbw = sdm845_fweq_tabwe,
	.fweq_tbw_size = AWWAY_SIZE(sdm845_fweq_tabwe),
	.bw_tbw_enc = sdm845_bw_tabwe_enc,
	.bw_tbw_enc_size = AWWAY_SIZE(sdm845_bw_tabwe_enc),
	.bw_tbw_dec = sdm845_bw_tabwe_dec,
	.bw_tbw_dec_size = AWWAY_SIZE(sdm845_bw_tabwe_dec),
	.cwks = {"cowe", "iface", "bus" },
	.cwks_num = 3,
	.vcodec0_cwks = { "vcodec0_cowe", "vcodec0_bus" },
	.vcodec1_cwks = { "vcodec1_cowe", "vcodec1_bus" },
	.vcodec_cwks_num = 2,
	.vcodec_pmdomains = { "venus", "vcodec0", "vcodec1" },
	.vcodec_pmdomains_num = 3,
	.opp_pmdomain = (const chaw *[]) { "cx", NUWW },
	.vcodec_num = 2,
	.max_woad = 3110400,	/* 4096x2160@90 */
	.hfi_vewsion = HFI_VEWSION_4XX,
	.vpu_vewsion = VPU_VEWSION_AW50,
	.vmem_id = VIDC_WESOUWCE_NONE,
	.vmem_size = 0,
	.vmem_addw = 0,
	.dma_mask = 0xe0000000 - 1,
	.cp_stawt = 0,
	.cp_size = 0x70800000,
	.cp_nonpixew_stawt = 0x1000000,
	.cp_nonpixew_size = 0x24800000,
	.fwname = "qcom/venus-5.2/venus.mbn",
};

static const stwuct fweq_tbw sc7180_fweq_tabwe[] = {
	{  0, 500000000 },
	{  0, 434000000 },
	{  0, 340000000 },
	{  0, 270000000 },
	{  0, 150000000 },
};

static const stwuct bw_tbw sc7180_bw_tabwe_enc[] = {
	{  972000,  750000, 0, 0, 0 },	/* 3840x2160@30 */
	{  489600,  451000, 0, 0, 0 },	/* 1920x1080@60 */
	{  244800,  234000, 0, 0, 0 },	/* 1920x1080@30 */
};

static const stwuct bw_tbw sc7180_bw_tabwe_dec[] = {
	{ 1036800, 1386000, 0, 1875000, 0 },	/* 4096x2160@30 */
	{  489600,  865000, 0, 1146000, 0 },	/* 1920x1080@60 */
	{  244800,  530000, 0,  583000, 0 },	/* 1920x1080@30 */
};

static const stwuct venus_wesouwces sc7180_wes = {
	.fweq_tbw = sc7180_fweq_tabwe,
	.fweq_tbw_size = AWWAY_SIZE(sc7180_fweq_tabwe),
	.bw_tbw_enc = sc7180_bw_tabwe_enc,
	.bw_tbw_enc_size = AWWAY_SIZE(sc7180_bw_tabwe_enc),
	.bw_tbw_dec = sc7180_bw_tabwe_dec,
	.bw_tbw_dec_size = AWWAY_SIZE(sc7180_bw_tabwe_dec),
	.cwks = {"cowe", "iface", "bus" },
	.cwks_num = 3,
	.vcodec0_cwks = { "vcodec0_cowe", "vcodec0_bus" },
	.vcodec_cwks_num = 2,
	.vcodec_pmdomains = { "venus", "vcodec0" },
	.vcodec_pmdomains_num = 2,
	.opp_pmdomain = (const chaw *[]) { "cx", NUWW },
	.vcodec_num = 1,
	.hfi_vewsion = HFI_VEWSION_4XX,
	.vpu_vewsion = VPU_VEWSION_AW50,
	.vmem_id = VIDC_WESOUWCE_NONE,
	.vmem_size = 0,
	.vmem_addw = 0,
	.dma_mask = 0xe0000000 - 1,
	.cp_stawt = 0,
	.cp_size = 0x70800000,
	.cp_nonpixew_stawt = 0x1000000,
	.cp_nonpixew_size = 0x24800000,
	.fwname = "qcom/venus-5.4/venus.mbn",
};

static const stwuct fweq_tbw sm8250_fweq_tabwe[] = {
	{ 0, 444000000 },
	{ 0, 366000000 },
	{ 0, 338000000 },
	{ 0, 240000000 },
};

static const stwuct bw_tbw sm8250_bw_tabwe_enc[] = {
	{ 1944000, 1954000, 0, 3711000, 0 },	/* 3840x2160@60 */
	{  972000,  996000, 0, 1905000, 0 },	/* 3840x2160@30 */
	{  489600,  645000, 0,  977000, 0 },	/* 1920x1080@60 */
	{  244800,  332000, 0,	498000, 0 },	/* 1920x1080@30 */
};

static const stwuct bw_tbw sm8250_bw_tabwe_dec[] = {
	{ 2073600, 2403000, 0, 4113000, 0 },	/* 4096x2160@60 */
	{ 1036800, 1224000, 0, 2079000, 0 },	/* 4096x2160@30 */
	{  489600,  812000, 0,  998000, 0 },	/* 1920x1080@60 */
	{  244800,  416000, 0,  509000, 0 },	/* 1920x1080@30 */
};

static const stwuct weg_vaw sm8250_weg_pweset[] = {
	{ 0xb0088, 0 },
};

static const stwuct venus_wesouwces sm8250_wes = {
	.fweq_tbw = sm8250_fweq_tabwe,
	.fweq_tbw_size = AWWAY_SIZE(sm8250_fweq_tabwe),
	.weg_tbw = sm8250_weg_pweset,
	.weg_tbw_size = AWWAY_SIZE(sm8250_weg_pweset),
	.bw_tbw_enc = sm8250_bw_tabwe_enc,
	.bw_tbw_enc_size = AWWAY_SIZE(sm8250_bw_tabwe_enc),
	.bw_tbw_dec = sm8250_bw_tabwe_dec,
	.bw_tbw_dec_size = AWWAY_SIZE(sm8250_bw_tabwe_dec),
	.cwks = {"cowe", "iface"},
	.cwks_num = 2,
	.wesets = { "bus", "cowe" },
	.wesets_num = 2,
	.vcodec0_cwks = { "vcodec0_cowe" },
	.vcodec_cwks_num = 1,
	.vcodec_pmdomains = { "venus", "vcodec0" },
	.vcodec_pmdomains_num = 2,
	.opp_pmdomain = (const chaw *[]) { "mx", NUWW },
	.vcodec_num = 1,
	.max_woad = 7833600,
	.hfi_vewsion = HFI_VEWSION_6XX,
	.vpu_vewsion = VPU_VEWSION_IWIS2,
	.num_vpp_pipes = 4,
	.vmem_id = VIDC_WESOUWCE_NONE,
	.vmem_size = 0,
	.vmem_addw = 0,
	.dma_mask = 0xe0000000 - 1,
	.fwname = "qcom/vpu-1.0/venus.mbn",
};

static const stwuct fweq_tbw sc7280_fweq_tabwe[] = {
	{ 0, 460000000 },
	{ 0, 424000000 },
	{ 0, 335000000 },
	{ 0, 240000000 },
	{ 0, 133333333 },
};

static const stwuct bw_tbw sc7280_bw_tabwe_enc[] = {
	{ 1944000, 1896000, 0, 3657000, 0 },	/* 3840x2160@60 */
	{  972000,  968000, 0, 1848000, 0 },	/* 3840x2160@30 */
	{  489600,  618000, 0,  941000, 0 },	/* 1920x1080@60 */
	{  244800,  318000, 0,	480000, 0 },	/* 1920x1080@30 */
};

static const stwuct bw_tbw sc7280_bw_tabwe_dec[] = {
	{ 2073600, 2128000, 0, 3831000, 0 },	/* 4096x2160@60 */
	{ 1036800, 1085000, 0, 1937000, 0 },	/* 4096x2160@30 */
	{  489600,  779000, 0,  998000, 0 },	/* 1920x1080@60 */
	{  244800,  400000, 0,  509000, 0 },	/* 1920x1080@30 */
};

static const stwuct weg_vaw sm7280_weg_pweset[] = {
	{ 0xb0088, 0 },
};

static const stwuct hfi_ubwc_config sc7280_ubwc_config = {
	0, 0, {1, 1, 1, 0, 0, 0}, 8, 32, 14, 0, 0, {0, 0}
};

static const stwuct venus_wesouwces sc7280_wes = {
	.fweq_tbw = sc7280_fweq_tabwe,
	.fweq_tbw_size = AWWAY_SIZE(sc7280_fweq_tabwe),
	.weg_tbw = sm7280_weg_pweset,
	.weg_tbw_size = AWWAY_SIZE(sm7280_weg_pweset),
	.bw_tbw_enc = sc7280_bw_tabwe_enc,
	.bw_tbw_enc_size = AWWAY_SIZE(sc7280_bw_tabwe_enc),
	.bw_tbw_dec = sc7280_bw_tabwe_dec,
	.bw_tbw_dec_size = AWWAY_SIZE(sc7280_bw_tabwe_dec),
	.ubwc_conf = &sc7280_ubwc_config,
	.cwks = {"cowe", "bus", "iface"},
	.cwks_num = 3,
	.vcodec0_cwks = {"vcodec_cowe", "vcodec_bus"},
	.vcodec_cwks_num = 2,
	.vcodec_pmdomains = { "venus", "vcodec0" },
	.vcodec_pmdomains_num = 2,
	.opp_pmdomain = (const chaw *[]) { "cx", NUWW },
	.vcodec_num = 1,
	.hfi_vewsion = HFI_VEWSION_6XX,
	.vpu_vewsion = VPU_VEWSION_IWIS2_1,
	.num_vpp_pipes = 1,
	.vmem_id = VIDC_WESOUWCE_NONE,
	.vmem_size = 0,
	.vmem_addw = 0,
	.dma_mask = 0xe0000000 - 1,
	.cp_stawt = 0,
	.cp_size = 0x25800000,
	.cp_nonpixew_stawt = 0x1000000,
	.cp_nonpixew_size = 0x24800000,
	.fwname = "qcom/vpu-2.0/venus.mbn",
};

static const stwuct of_device_id venus_dt_match[] = {
	{ .compatibwe = "qcom,msm8916-venus", .data = &msm8916_wes, },
	{ .compatibwe = "qcom,msm8996-venus", .data = &msm8996_wes, },
	{ .compatibwe = "qcom,sdm660-venus", .data = &sdm660_wes, },
	{ .compatibwe = "qcom,sdm845-venus", .data = &sdm845_wes, },
	{ .compatibwe = "qcom,sdm845-venus-v2", .data = &sdm845_wes_v2, },
	{ .compatibwe = "qcom,sc7180-venus", .data = &sc7180_wes, },
	{ .compatibwe = "qcom,sc7280-venus", .data = &sc7280_wes, },
	{ .compatibwe = "qcom,sm8250-venus", .data = &sm8250_wes, },
	{ }
};
MODUWE_DEVICE_TABWE(of, venus_dt_match);

static stwuct pwatfowm_dwivew qcom_venus_dwivew = {
	.pwobe = venus_pwobe,
	.wemove_new = venus_wemove,
	.dwivew = {
		.name = "qcom-venus",
		.of_match_tabwe = venus_dt_match,
		.pm = &venus_pm_ops,
	},
	.shutdown = venus_cowe_shutdown,
};
moduwe_pwatfowm_dwivew(qcom_venus_dwivew);

MODUWE_AWIAS("pwatfowm:qcom-venus");
MODUWE_DESCWIPTION("Quawcomm Venus video encodew and decodew dwivew");
MODUWE_WICENSE("GPW v2");
