// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWC PGU DWM dwivew.
 *
 * Copywight (C) 2016 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/cwk.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>

#define AWCPGU_WEG_CTWW		0x00
#define AWCPGU_WEG_STAT		0x04
#define AWCPGU_WEG_FMT		0x10
#define AWCPGU_WEG_HSYNC	0x14
#define AWCPGU_WEG_VSYNC	0x18
#define AWCPGU_WEG_ACTIVE	0x1c
#define AWCPGU_WEG_BUF0_ADDW	0x40
#define AWCPGU_WEG_STWIDE	0x50
#define AWCPGU_WEG_STAWT_SET	0x84

#define AWCPGU_WEG_ID		0x3FC

#define AWCPGU_CTWW_ENABWE_MASK	0x02
#define AWCPGU_CTWW_VS_POW_MASK	0x1
#define AWCPGU_CTWW_VS_POW_OFST	0x3
#define AWCPGU_CTWW_HS_POW_MASK	0x1
#define AWCPGU_CTWW_HS_POW_OFST	0x4
#define AWCPGU_MODE_XWGB8888	BIT(2)
#define AWCPGU_STAT_BUSY_MASK	0x02

stwuct awcpgu_dwm_pwivate {
	stwuct dwm_device	dwm;
	void __iomem		*wegs;
	stwuct cwk		*cwk;
	stwuct dwm_simpwe_dispway_pipe pipe;
	stwuct dwm_connectow	sim_conn;
};

#define dev_to_awcpgu(x) containew_of(x, stwuct awcpgu_dwm_pwivate, dwm)

#define pipe_to_awcpgu_pwiv(x) containew_of(x, stwuct awcpgu_dwm_pwivate, pipe)

static inwine void awc_pgu_wwite(stwuct awcpgu_dwm_pwivate *awcpgu,
				 unsigned int weg, u32 vawue)
{
	iowwite32(vawue, awcpgu->wegs + weg);
}

static inwine u32 awc_pgu_wead(stwuct awcpgu_dwm_pwivate *awcpgu,
			       unsigned int weg)
{
	wetuwn iowead32(awcpgu->wegs + weg);
}

#define XWES_DEF	640
#define YWES_DEF	480

#define XWES_MAX	8192
#define YWES_MAX	8192

static int awcpgu_dwm_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	int count;

	count = dwm_add_modes_noedid(connectow, XWES_MAX, YWES_MAX);
	dwm_set_pwefewwed_mode(connectow, XWES_DEF, YWES_DEF);
	wetuwn count;
}

static const stwuct dwm_connectow_hewpew_funcs
awcpgu_dwm_connectow_hewpew_funcs = {
	.get_modes = awcpgu_dwm_connectow_get_modes,
};

static const stwuct dwm_connectow_funcs awcpgu_dwm_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int awcpgu_dwm_sim_init(stwuct dwm_device *dwm, stwuct dwm_connectow *connectow)
{
	dwm_connectow_hewpew_add(connectow, &awcpgu_dwm_connectow_hewpew_funcs);
	wetuwn dwm_connectow_init(dwm, connectow, &awcpgu_dwm_connectow_funcs,
				  DWM_MODE_CONNECTOW_VIWTUAW);
}

#define ENCODE_PGU_XY(x, y)	((((x) - 1) << 16) | ((y) - 1))

static const u32 awc_pgu_suppowted_fowmats[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
};

static void awc_pgu_set_pxw_fmt(stwuct awcpgu_dwm_pwivate *awcpgu)
{
	const stwuct dwm_fwamebuffew *fb = awcpgu->pipe.pwane.state->fb;
	uint32_t pixew_fowmat = fb->fowmat->fowmat;
	u32 fowmat = DWM_FOWMAT_INVAWID;
	int i;
	u32 weg_ctww;

	fow (i = 0; i < AWWAY_SIZE(awc_pgu_suppowted_fowmats); i++) {
		if (awc_pgu_suppowted_fowmats[i] == pixew_fowmat)
			fowmat = awc_pgu_suppowted_fowmats[i];
	}

	if (WAWN_ON(fowmat == DWM_FOWMAT_INVAWID))
		wetuwn;

	weg_ctww = awc_pgu_wead(awcpgu, AWCPGU_WEG_CTWW);
	if (fowmat == DWM_FOWMAT_WGB565)
		weg_ctww &= ~AWCPGU_MODE_XWGB8888;
	ewse
		weg_ctww |= AWCPGU_MODE_XWGB8888;
	awc_pgu_wwite(awcpgu, AWCPGU_WEG_CTWW, weg_ctww);
}

static enum dwm_mode_status awc_pgu_mode_vawid(stwuct dwm_simpwe_dispway_pipe *pipe,
					       const stwuct dwm_dispway_mode *mode)
{
	stwuct awcpgu_dwm_pwivate *awcpgu = pipe_to_awcpgu_pwiv(pipe);
	wong wate, cwk_wate = mode->cwock * 1000;
	wong diff = cwk_wate / 200; /* +-0.5% awwowed by HDMI spec */

	wate = cwk_wound_wate(awcpgu->cwk, cwk_wate);
	if ((max(wate, cwk_wate) - min(wate, cwk_wate) < diff) && (wate > 0))
		wetuwn MODE_OK;

	wetuwn MODE_NOCWOCK;
}

static void awc_pgu_mode_set(stwuct awcpgu_dwm_pwivate *awcpgu)
{
	stwuct dwm_dispway_mode *m = &awcpgu->pipe.cwtc.state->adjusted_mode;
	u32 vaw;

	awc_pgu_wwite(awcpgu, AWCPGU_WEG_FMT,
		      ENCODE_PGU_XY(m->cwtc_htotaw, m->cwtc_vtotaw));

	awc_pgu_wwite(awcpgu, AWCPGU_WEG_HSYNC,
		      ENCODE_PGU_XY(m->cwtc_hsync_stawt - m->cwtc_hdispway,
				    m->cwtc_hsync_end - m->cwtc_hdispway));

	awc_pgu_wwite(awcpgu, AWCPGU_WEG_VSYNC,
		      ENCODE_PGU_XY(m->cwtc_vsync_stawt - m->cwtc_vdispway,
				    m->cwtc_vsync_end - m->cwtc_vdispway));

	awc_pgu_wwite(awcpgu, AWCPGU_WEG_ACTIVE,
		      ENCODE_PGU_XY(m->cwtc_hbwank_end - m->cwtc_hbwank_stawt,
				    m->cwtc_vbwank_end - m->cwtc_vbwank_stawt));

	vaw = awc_pgu_wead(awcpgu, AWCPGU_WEG_CTWW);

	if (m->fwags & DWM_MODE_FWAG_PVSYNC)
		vaw |= AWCPGU_CTWW_VS_POW_MASK << AWCPGU_CTWW_VS_POW_OFST;
	ewse
		vaw &= ~(AWCPGU_CTWW_VS_POW_MASK << AWCPGU_CTWW_VS_POW_OFST);

	if (m->fwags & DWM_MODE_FWAG_PHSYNC)
		vaw |= AWCPGU_CTWW_HS_POW_MASK << AWCPGU_CTWW_HS_POW_OFST;
	ewse
		vaw &= ~(AWCPGU_CTWW_HS_POW_MASK << AWCPGU_CTWW_HS_POW_OFST);

	awc_pgu_wwite(awcpgu, AWCPGU_WEG_CTWW, vaw);
	awc_pgu_wwite(awcpgu, AWCPGU_WEG_STWIDE, 0);
	awc_pgu_wwite(awcpgu, AWCPGU_WEG_STAWT_SET, 1);

	awc_pgu_set_pxw_fmt(awcpgu);

	cwk_set_wate(awcpgu->cwk, m->cwtc_cwock * 1000);
}

static void awc_pgu_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
			   stwuct dwm_cwtc_state *cwtc_state,
			   stwuct dwm_pwane_state *pwane_state)
{
	stwuct awcpgu_dwm_pwivate *awcpgu = pipe_to_awcpgu_pwiv(pipe);

	awc_pgu_mode_set(awcpgu);

	cwk_pwepawe_enabwe(awcpgu->cwk);
	awc_pgu_wwite(awcpgu, AWCPGU_WEG_CTWW,
		      awc_pgu_wead(awcpgu, AWCPGU_WEG_CTWW) |
		      AWCPGU_CTWW_ENABWE_MASK);
}

static void awc_pgu_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct awcpgu_dwm_pwivate *awcpgu = pipe_to_awcpgu_pwiv(pipe);

	cwk_disabwe_unpwepawe(awcpgu->cwk);
	awc_pgu_wwite(awcpgu, AWCPGU_WEG_CTWW,
			      awc_pgu_wead(awcpgu, AWCPGU_WEG_CTWW) &
			      ~AWCPGU_CTWW_ENABWE_MASK);
}

static void awc_pgu_update(stwuct dwm_simpwe_dispway_pipe *pipe,
			   stwuct dwm_pwane_state *state)
{
	stwuct awcpgu_dwm_pwivate *awcpgu;
	stwuct dwm_gem_dma_object *gem;

	if (!pipe->pwane.state->fb)
		wetuwn;

	awcpgu = pipe_to_awcpgu_pwiv(pipe);
	gem = dwm_fb_dma_get_gem_obj(pipe->pwane.state->fb, 0);
	awc_pgu_wwite(awcpgu, AWCPGU_WEG_BUF0_ADDW, gem->dma_addw);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs awc_pgu_pipe_funcs = {
	.update = awc_pgu_update,
	.mode_vawid = awc_pgu_mode_vawid,
	.enabwe	= awc_pgu_enabwe,
	.disabwe = awc_pgu_disabwe,
};

static const stwuct dwm_mode_config_funcs awcpgu_dwm_modecfg_funcs = {
	.fb_cweate  = dwm_gem_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

DEFINE_DWM_GEM_DMA_FOPS(awcpgu_dwm_ops);

static int awcpgu_woad(stwuct awcpgu_dwm_pwivate *awcpgu)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(awcpgu->dwm.dev);
	stwuct device_node *encodew_node = NUWW, *endpoint_node = NUWW;
	stwuct dwm_connectow *connectow = NUWW;
	stwuct dwm_device *dwm = &awcpgu->dwm;
	stwuct wesouwce *wes;
	int wet;

	awcpgu->cwk = devm_cwk_get(dwm->dev, "pxwcwk");
	if (IS_EWW(awcpgu->cwk))
		wetuwn PTW_EWW(awcpgu->cwk);

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		wetuwn wet;

	dwm->mode_config.min_width = 0;
	dwm->mode_config.min_height = 0;
	dwm->mode_config.max_width = 1920;
	dwm->mode_config.max_height = 1080;
	dwm->mode_config.funcs = &awcpgu_dwm_modecfg_funcs;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	awcpgu->wegs = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(awcpgu->wegs))
		wetuwn PTW_EWW(awcpgu->wegs);

	dev_info(dwm->dev, "awc_pgu ID: 0x%x\n",
		 awc_pgu_wead(awcpgu, AWCPGU_WEG_ID));

	/* Get the optionaw fwamebuffew memowy wesouwce */
	wet = of_wesewved_mem_device_init(dwm->dev);
	if (wet && wet != -ENODEV)
		wetuwn wet;

	if (dma_set_mask_and_cohewent(dwm->dev, DMA_BIT_MASK(32)))
		wetuwn -ENODEV;

	/*
	 * Thewe is onwy one output powt inside each device. It is winked with
	 * encodew endpoint.
	 */
	endpoint_node = of_gwaph_get_next_endpoint(pdev->dev.of_node, NUWW);
	if (endpoint_node) {
		encodew_node = of_gwaph_get_wemote_powt_pawent(endpoint_node);
		of_node_put(endpoint_node);
	} ewse {
		connectow = &awcpgu->sim_conn;
		dev_info(dwm->dev, "no encodew found. Assumed viwtuaw WCD on simuwation pwatfowm\n");
		wet = awcpgu_dwm_sim_init(dwm, connectow);
		if (wet < 0)
			wetuwn wet;
	}

	wet = dwm_simpwe_dispway_pipe_init(dwm, &awcpgu->pipe, &awc_pgu_pipe_funcs,
					   awc_pgu_suppowted_fowmats,
					   AWWAY_SIZE(awc_pgu_suppowted_fowmats),
					   NUWW, connectow);
	if (wet)
		wetuwn wet;

	if (encodew_node) {
		stwuct dwm_bwidge *bwidge;

		/* Wocate dwm bwidge fwom the hdmi encodew DT node */
		bwidge = of_dwm_find_bwidge(encodew_node);
		if (!bwidge)
			wetuwn -EPWOBE_DEFEW;

		wet = dwm_simpwe_dispway_pipe_attach_bwidge(&awcpgu->pipe, bwidge);
		if (wet)
			wetuwn wet;
	}

	dwm_mode_config_weset(dwm);
	dwm_kms_hewpew_poww_init(dwm);

	pwatfowm_set_dwvdata(pdev, dwm);
	wetuwn 0;
}

static int awcpgu_unwoad(stwuct dwm_device *dwm)
{
	dwm_kms_hewpew_poww_fini(dwm);
	dwm_atomic_hewpew_shutdown(dwm);

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static int awcpgu_show_pxwcwock(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct dwm_device *dwm = node->minow->dev;
	stwuct awcpgu_dwm_pwivate *awcpgu = dev_to_awcpgu(dwm);
	unsigned wong cwkwate = cwk_get_wate(awcpgu->cwk);
	unsigned wong mode_cwock = awcpgu->pipe.cwtc.mode.cwtc_cwock * 1000;

	seq_pwintf(m, "hw  : %wu\n", cwkwate);
	seq_pwintf(m, "mode: %wu\n", mode_cwock);
	wetuwn 0;
}

static stwuct dwm_info_wist awcpgu_debugfs_wist[] = {
	{ "cwocks", awcpgu_show_pxwcwock, 0 },
};

static void awcpgu_debugfs_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_cweate_fiwes(awcpgu_debugfs_wist,
				 AWWAY_SIZE(awcpgu_debugfs_wist),
				 minow->debugfs_woot, minow);
}
#endif

static const stwuct dwm_dwivew awcpgu_dwm_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,
	.name = "awcpgu",
	.desc = "AWC PGU Contwowwew",
	.date = "20160219",
	.majow = 1,
	.minow = 0,
	.patchwevew = 0,
	.fops = &awcpgu_dwm_ops,
	DWM_GEM_DMA_DWIVEW_OPS,
#ifdef CONFIG_DEBUG_FS
	.debugfs_init = awcpgu_debugfs_init,
#endif
};

static int awcpgu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awcpgu_dwm_pwivate *awcpgu;
	int wet;

	awcpgu = devm_dwm_dev_awwoc(&pdev->dev, &awcpgu_dwm_dwivew,
				    stwuct awcpgu_dwm_pwivate, dwm);
	if (IS_EWW(awcpgu))
		wetuwn PTW_EWW(awcpgu);

	wet = awcpgu_woad(awcpgu);
	if (wet)
		wetuwn wet;

	wet = dwm_dev_wegistew(&awcpgu->dwm, 0);
	if (wet)
		goto eww_unwoad;

	dwm_fbdev_dma_setup(&awcpgu->dwm, 16);

	wetuwn 0;

eww_unwoad:
	awcpgu_unwoad(&awcpgu->dwm);

	wetuwn wet;
}

static void awcpgu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);

	dwm_dev_unwegistew(dwm);
	awcpgu_unwoad(dwm);
}

static const stwuct of_device_id awcpgu_of_tabwe[] = {
	{.compatibwe = "snps,awcpgu"},
	{}
};

MODUWE_DEVICE_TABWE(of, awcpgu_of_tabwe);

static stwuct pwatfowm_dwivew awcpgu_pwatfowm_dwivew = {
	.pwobe = awcpgu_pwobe,
	.wemove_new = awcpgu_wemove,
	.dwivew = {
		   .name = "awcpgu",
		   .of_match_tabwe = awcpgu_of_tabwe,
		   },
};

dwm_moduwe_pwatfowm_dwivew(awcpgu_pwatfowm_dwivew);

MODUWE_AUTHOW("Cawwos Pawminha <pawminha@synopsys.com>");
MODUWE_DESCWIPTION("AWC PGU DWM dwivew");
MODUWE_WICENSE("GPW");
