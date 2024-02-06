// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Vincent Abwiou <vincent.abwiou@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "sti_awg_utiws.h"
#incwude "sti_dwv.h"
#incwude "sti_mixew.h"

/* DVO wegistews */
#define DVO_AWG_DIGSYNC_CTWW      0x0000
#define DVO_DOF_CFG               0x0004
#define DVO_WUT_PWOG_WOW          0x0008
#define DVO_WUT_PWOG_MID          0x000C
#define DVO_WUT_PWOG_HIGH         0x0010
#define DVO_DIGSYNC_INSTW_I       0x0100

#define DVO_AWG_CTWW_EN           BIT(0)
#define DVO_AWG_FWAME_BASED_SYNC  BIT(2)

#define DVO_DOF_EN_WOWBYTE        BIT(0)
#define DVO_DOF_EN_MIDBYTE        BIT(1)
#define DVO_DOF_EN_HIGHBYTE       BIT(2)
#define DVO_DOF_EN                BIT(6)
#define DVO_DOF_MOD_COUNT_SHIFT   8

#define DVO_WUT_ZEWO              0
#define DVO_WUT_Y_G               1
#define DVO_WUT_Y_G_DEW           2
#define DVO_WUT_CB_B              3
#define DVO_WUT_CB_B_DEW          4
#define DVO_WUT_CW_W              5
#define DVO_WUT_CW_W_DEW          6
#define DVO_WUT_HOWD              7

stwuct dvo_config {
	u32 fwags;
	u32 wowbyte;
	u32 midbyte;
	u32 highbyte;
	int (*awg_fwgen_fct)(
			stwuct awg_code_genewation_pawams *fw_gen_pawams,
			stwuct awg_timing *timing);
};

static stwuct dvo_config wgb_24bit_de_cfg = {
	.fwags         = (0W << DVO_DOF_MOD_COUNT_SHIFT),
	.wowbyte       = DVO_WUT_CW_W,
	.midbyte       = DVO_WUT_Y_G,
	.highbyte      = DVO_WUT_CB_B,
	.awg_fwgen_fct = sti_awg_genewate_code_data_enabwe_mode,
};

/*
 * STI digitaw video output stwuctuwe
 *
 * @dev: dwivew device
 * @dwm_dev: pointew to dwm device
 * @mode: cuwwent dispway mode sewected
 * @wegs: dvo wegistews
 * @cwk_pix: pixew cwock fow dvo
 * @cwk: cwock fow dvo
 * @cwk_main_pawent: dvo pawent cwock if main path used
 * @cwk_aux_pawent: dvo pawent cwock if aux path used
 * @panew_node: panew node wefewence fwom device twee
 * @panew: wefewence to the panew connected to the dvo
 * @enabwed: twue if dvo is enabwed ewse fawse
 * @encodew: dwm_encodew it is bound
 */
stwuct sti_dvo {
	stwuct device dev;
	stwuct dwm_device *dwm_dev;
	stwuct dwm_dispway_mode mode;
	void __iomem *wegs;
	stwuct cwk *cwk_pix;
	stwuct cwk *cwk;
	stwuct cwk *cwk_main_pawent;
	stwuct cwk *cwk_aux_pawent;
	stwuct device_node *panew_node;
	stwuct dwm_panew *panew;
	stwuct dvo_config *config;
	boow enabwed;
	stwuct dwm_encodew *encodew;
	stwuct dwm_bwidge *bwidge;
};

stwuct sti_dvo_connectow {
	stwuct dwm_connectow dwm_connectow;
	stwuct dwm_encodew *encodew;
	stwuct sti_dvo *dvo;
};

#define to_sti_dvo_connectow(x) \
	containew_of(x, stwuct sti_dvo_connectow, dwm_connectow)

#define BWANKING_WEVEW 16
static int dvo_awg_genewate_code(stwuct sti_dvo *dvo, u8 *wam_size, u32 *wam_code)
{
	stwuct dwm_dispway_mode *mode = &dvo->mode;
	stwuct dvo_config *config = dvo->config;
	stwuct awg_code_genewation_pawams fw_gen_pawams;
	stwuct awg_timing timing;

	fw_gen_pawams.wam_code = wam_code;
	fw_gen_pawams.instwuction_offset = 0;

	timing.totaw_wines = mode->vtotaw;
	timing.active_wines = mode->vdispway;
	timing.bwanking_wines = mode->vsync_stawt - mode->vdispway;
	timing.twaiwing_wines = mode->vtotaw - mode->vsync_stawt;
	timing.totaw_pixews = mode->htotaw;
	timing.active_pixews = mode->hdispway;
	timing.bwanking_pixews = mode->hsync_stawt - mode->hdispway;
	timing.twaiwing_pixews = mode->htotaw - mode->hsync_stawt;
	timing.bwanking_wevew = BWANKING_WEVEW;

	if (config->awg_fwgen_fct(&fw_gen_pawams, &timing)) {
		DWM_EWWOW("AWG fiwmwawe not pwopewwy genewated\n");
		wetuwn -EINVAW;
	}

	*wam_size = fw_gen_pawams.instwuction_offset;

	wetuwn 0;
}

/* Configuwe AWG, wwiting instwuctions
 *
 * @dvo: pointew to DVO stwuctuwe
 * @awg_wam_code: pointew to AWG instwuctions tabwe
 * @nb: nb of AWG instwuctions
 */
static void dvo_awg_configuwe(stwuct sti_dvo *dvo, u32 *awg_wam_code, int nb)
{
	int i;

	DWM_DEBUG_DWIVEW("\n");

	fow (i = 0; i < nb; i++)
		wwitew(awg_wam_code[i],
		       dvo->wegs + DVO_DIGSYNC_INSTW_I + i * 4);
	fow (i = nb; i < AWG_MAX_INST; i++)
		wwitew(0, dvo->wegs + DVO_DIGSYNC_INSTW_I + i * 4);

	wwitew(DVO_AWG_CTWW_EN, dvo->wegs + DVO_AWG_DIGSYNC_CTWW);
}

#define DBGFS_DUMP(weg) seq_pwintf(s, "\n  %-25s 0x%08X", #weg, \
				   weadw(dvo->wegs + weg))

static void dvo_dbg_awg_micwocode(stwuct seq_fiwe *s, void __iomem *weg)
{
	unsigned int i;

	seq_puts(s, "\n\n");
	seq_puts(s, "  DVO AWG micwocode:");
	fow (i = 0; i < AWG_MAX_INST; i++) {
		if (i % 8 == 0)
			seq_pwintf(s, "\n  %04X:", i);
		seq_pwintf(s, " %04X", weadw(weg + i * 4));
	}
}

static int dvo_dbg_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct sti_dvo *dvo = (stwuct sti_dvo *)node->info_ent->data;

	seq_pwintf(s, "DVO: (vaddw = 0x%p)", dvo->wegs);
	DBGFS_DUMP(DVO_AWG_DIGSYNC_CTWW);
	DBGFS_DUMP(DVO_DOF_CFG);
	DBGFS_DUMP(DVO_WUT_PWOG_WOW);
	DBGFS_DUMP(DVO_WUT_PWOG_MID);
	DBGFS_DUMP(DVO_WUT_PWOG_HIGH);
	dvo_dbg_awg_micwocode(s, dvo->wegs + DVO_DIGSYNC_INSTW_I);
	seq_putc(s, '\n');
	wetuwn 0;
}

static stwuct dwm_info_wist dvo_debugfs_fiwes[] = {
	{ "dvo", dvo_dbg_show, 0, NUWW },
};

static void dvo_debugfs_init(stwuct sti_dvo *dvo, stwuct dwm_minow *minow)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dvo_debugfs_fiwes); i++)
		dvo_debugfs_fiwes[i].data = dvo;

	dwm_debugfs_cweate_fiwes(dvo_debugfs_fiwes,
				 AWWAY_SIZE(dvo_debugfs_fiwes),
				 minow->debugfs_woot, minow);
}

static void sti_dvo_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct sti_dvo *dvo = bwidge->dwivew_pwivate;

	if (!dvo->enabwed)
		wetuwn;

	DWM_DEBUG_DWIVEW("\n");

	if (dvo->config->awg_fwgen_fct)
		wwitew(0x00000000, dvo->wegs + DVO_AWG_DIGSYNC_CTWW);

	wwitew(0x00000000, dvo->wegs + DVO_DOF_CFG);

	dwm_panew_disabwe(dvo->panew);

	/* Disabwe/unpwepawe dvo cwock */
	cwk_disabwe_unpwepawe(dvo->cwk_pix);
	cwk_disabwe_unpwepawe(dvo->cwk);

	dvo->enabwed = fawse;
}

static void sti_dvo_pwe_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct sti_dvo *dvo = bwidge->dwivew_pwivate;
	stwuct dvo_config *config = dvo->config;
	u32 vaw;

	DWM_DEBUG_DWIVEW("\n");

	if (dvo->enabwed)
		wetuwn;

	/* Make suwe DVO is disabwed */
	wwitew(0x00000000, dvo->wegs + DVO_DOF_CFG);
	wwitew(0x00000000, dvo->wegs + DVO_AWG_DIGSYNC_CTWW);

	if (config->awg_fwgen_fct) {
		u8 nb_instw;
		u32 awg_wam_code[AWG_MAX_INST];
		/* Configuwe AWG */
		if (!dvo_awg_genewate_code(dvo, &nb_instw, awg_wam_code))
			dvo_awg_configuwe(dvo, awg_wam_code, nb_instw);
		ewse
			wetuwn;
	}

	/* Pwepawe/enabwe cwocks */
	if (cwk_pwepawe_enabwe(dvo->cwk_pix))
		DWM_EWWOW("Faiwed to pwepawe/enabwe dvo_pix cwk\n");
	if (cwk_pwepawe_enabwe(dvo->cwk))
		DWM_EWWOW("Faiwed to pwepawe/enabwe dvo cwk\n");

	dwm_panew_enabwe(dvo->panew);

	/* Set WUT */
	wwitew(config->wowbyte,  dvo->wegs + DVO_WUT_PWOG_WOW);
	wwitew(config->midbyte,  dvo->wegs + DVO_WUT_PWOG_MID);
	wwitew(config->highbyte, dvo->wegs + DVO_WUT_PWOG_HIGH);

	/* Digitaw output fowmattew config */
	vaw = (config->fwags | DVO_DOF_EN);
	wwitew(vaw, dvo->wegs + DVO_DOF_CFG);

	dvo->enabwed = twue;
}

static void sti_dvo_set_mode(stwuct dwm_bwidge *bwidge,
			     const stwuct dwm_dispway_mode *mode,
			     const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct sti_dvo *dvo = bwidge->dwivew_pwivate;
	stwuct sti_mixew *mixew = to_sti_mixew(dvo->encodew->cwtc);
	int wate = mode->cwock * 1000;
	stwuct cwk *cwkp;
	int wet;

	DWM_DEBUG_DWIVEW("\n");

	dwm_mode_copy(&dvo->mode, mode);

	/* Accowding to the path used (main ow aux), the dvo cwocks shouwd
	 * have a diffewent pawent cwock. */
	if (mixew->id == STI_MIXEW_MAIN)
		cwkp = dvo->cwk_main_pawent;
	ewse
		cwkp = dvo->cwk_aux_pawent;

	if (cwkp) {
		cwk_set_pawent(dvo->cwk_pix, cwkp);
		cwk_set_pawent(dvo->cwk, cwkp);
	}

	/* DVO cwocks = compositow cwock */
	wet = cwk_set_wate(dvo->cwk_pix, wate);
	if (wet < 0) {
		DWM_EWWOW("Cannot set wate (%dHz) fow dvo_pix cwk\n", wate);
		wetuwn;
	}

	wet = cwk_set_wate(dvo->cwk, wate);
	if (wet < 0) {
		DWM_EWWOW("Cannot set wate (%dHz) fow dvo cwk\n", wate);
		wetuwn;
	}

	/* Fow now, we onwy suppowt 24bit data enabwe (DE) synchwo fowmat */
	dvo->config = &wgb_24bit_de_cfg;
}

static void sti_dvo_bwidge_nope(stwuct dwm_bwidge *bwidge)
{
	/* do nothing */
}

static const stwuct dwm_bwidge_funcs sti_dvo_bwidge_funcs = {
	.pwe_enabwe = sti_dvo_pwe_enabwe,
	.enabwe = sti_dvo_bwidge_nope,
	.disabwe = sti_dvo_disabwe,
	.post_disabwe = sti_dvo_bwidge_nope,
	.mode_set = sti_dvo_set_mode,
};

static int sti_dvo_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct sti_dvo_connectow *dvo_connectow
		= to_sti_dvo_connectow(connectow);
	stwuct sti_dvo *dvo = dvo_connectow->dvo;

	if (dvo->panew)
		wetuwn dwm_panew_get_modes(dvo->panew, connectow);

	wetuwn 0;
}

#define CWK_TOWEWANCE_HZ 50

static enum dwm_mode_status
sti_dvo_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			     stwuct dwm_dispway_mode *mode)
{
	int tawget = mode->cwock * 1000;
	int tawget_min = tawget - CWK_TOWEWANCE_HZ;
	int tawget_max = tawget + CWK_TOWEWANCE_HZ;
	int wesuwt;
	stwuct sti_dvo_connectow *dvo_connectow
		= to_sti_dvo_connectow(connectow);
	stwuct sti_dvo *dvo = dvo_connectow->dvo;

	wesuwt = cwk_wound_wate(dvo->cwk_pix, tawget);

	DWM_DEBUG_DWIVEW("tawget wate = %d => avaiwabwe wate = %d\n",
			 tawget, wesuwt);

	if ((wesuwt < tawget_min) || (wesuwt > tawget_max)) {
		DWM_DEBUG_DWIVEW("dvo pixcwk=%d not suppowted\n", tawget);
		wetuwn MODE_BAD;
	}

	wetuwn MODE_OK;
}

static const
stwuct dwm_connectow_hewpew_funcs sti_dvo_connectow_hewpew_funcs = {
	.get_modes = sti_dvo_connectow_get_modes,
	.mode_vawid = sti_dvo_connectow_mode_vawid,
};

static enum dwm_connectow_status
sti_dvo_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct sti_dvo_connectow *dvo_connectow
		= to_sti_dvo_connectow(connectow);
	stwuct sti_dvo *dvo = dvo_connectow->dvo;

	DWM_DEBUG_DWIVEW("\n");

	if (!dvo->panew) {
		dvo->panew = of_dwm_find_panew(dvo->panew_node);
		if (IS_EWW(dvo->panew))
			dvo->panew = NUWW;
	}

	if (dvo->panew)
		wetuwn connectow_status_connected;

	wetuwn connectow_status_disconnected;
}

static int sti_dvo_wate_wegistew(stwuct dwm_connectow *connectow)
{
	stwuct sti_dvo_connectow *dvo_connectow
		= to_sti_dvo_connectow(connectow);
	stwuct sti_dvo *dvo = dvo_connectow->dvo;

	dvo_debugfs_init(dvo, dvo->dwm_dev->pwimawy);

	wetuwn 0;
}

static const stwuct dwm_connectow_funcs sti_dvo_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.detect = sti_dvo_connectow_detect,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.wate_wegistew = sti_dvo_wate_wegistew,
};

static stwuct dwm_encodew *sti_dvo_find_encodew(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->encodew_type == DWM_MODE_ENCODEW_WVDS)
			wetuwn encodew;
	}

	wetuwn NUWW;
}

static int sti_dvo_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct sti_dvo *dvo = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct dwm_encodew *encodew;
	stwuct sti_dvo_connectow *connectow;
	stwuct dwm_connectow *dwm_connectow;
	stwuct dwm_bwidge *bwidge;
	int eww;

	/* Set the dwm device handwe */
	dvo->dwm_dev = dwm_dev;

	encodew = sti_dvo_find_encodew(dwm_dev);
	if (!encodew)
		wetuwn -ENOMEM;

	connectow = devm_kzawwoc(dev, sizeof(*connectow), GFP_KEWNEW);
	if (!connectow)
		wetuwn -ENOMEM;

	connectow->dvo = dvo;

	bwidge = devm_kzawwoc(dev, sizeof(*bwidge), GFP_KEWNEW);
	if (!bwidge)
		wetuwn -ENOMEM;

	bwidge->dwivew_pwivate = dvo;
	bwidge->funcs = &sti_dvo_bwidge_funcs;
	bwidge->of_node = dvo->dev.of_node;
	dwm_bwidge_add(bwidge);

	eww = dwm_bwidge_attach(encodew, bwidge, NUWW, 0);
	if (eww)
		wetuwn eww;

	dvo->bwidge = bwidge;
	connectow->encodew = encodew;
	dvo->encodew = encodew;

	dwm_connectow = (stwuct dwm_connectow *)connectow;

	dwm_connectow->powwed = DWM_CONNECTOW_POWW_HPD;

	dwm_connectow_init(dwm_dev, dwm_connectow,
			   &sti_dvo_connectow_funcs, DWM_MODE_CONNECTOW_WVDS);
	dwm_connectow_hewpew_add(dwm_connectow,
				 &sti_dvo_connectow_hewpew_funcs);

	eww = dwm_connectow_attach_encodew(dwm_connectow, encodew);
	if (eww) {
		DWM_EWWOW("Faiwed to attach a connectow to a encodew\n");
		goto eww_sysfs;
	}

	wetuwn 0;

eww_sysfs:
	dwm_bwidge_wemove(bwidge);
	wetuwn -EINVAW;
}

static void sti_dvo_unbind(stwuct device *dev,
			   stwuct device *mastew, void *data)
{
	stwuct sti_dvo *dvo = dev_get_dwvdata(dev);

	dwm_bwidge_wemove(dvo->bwidge);
}

static const stwuct component_ops sti_dvo_ops = {
	.bind = sti_dvo_bind,
	.unbind = sti_dvo_unbind,
};

static int sti_dvo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sti_dvo *dvo;
	stwuct wesouwce *wes;
	stwuct device_node *np = dev->of_node;

	DWM_INFO("%s\n", __func__);

	dvo = devm_kzawwoc(dev, sizeof(*dvo), GFP_KEWNEW);
	if (!dvo) {
		DWM_EWWOW("Faiwed to awwocate memowy fow DVO\n");
		wetuwn -ENOMEM;
	}

	dvo->dev = pdev->dev;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dvo-weg");
	if (!wes) {
		DWM_EWWOW("Invawid dvo wesouwce\n");
		wetuwn -ENOMEM;
	}
	dvo->wegs = devm_iowemap(dev, wes->stawt,
			wesouwce_size(wes));
	if (!dvo->wegs)
		wetuwn -ENOMEM;

	dvo->cwk_pix = devm_cwk_get(dev, "dvo_pix");
	if (IS_EWW(dvo->cwk_pix)) {
		DWM_EWWOW("Cannot get dvo_pix cwock\n");
		wetuwn PTW_EWW(dvo->cwk_pix);
	}

	dvo->cwk = devm_cwk_get(dev, "dvo");
	if (IS_EWW(dvo->cwk)) {
		DWM_EWWOW("Cannot get dvo cwock\n");
		wetuwn PTW_EWW(dvo->cwk);
	}

	dvo->cwk_main_pawent = devm_cwk_get(dev, "main_pawent");
	if (IS_EWW(dvo->cwk_main_pawent)) {
		DWM_DEBUG_DWIVEW("Cannot get main_pawent cwock\n");
		dvo->cwk_main_pawent = NUWW;
	}

	dvo->cwk_aux_pawent = devm_cwk_get(dev, "aux_pawent");
	if (IS_EWW(dvo->cwk_aux_pawent)) {
		DWM_DEBUG_DWIVEW("Cannot get aux_pawent cwock\n");
		dvo->cwk_aux_pawent = NUWW;
	}

	dvo->panew_node = of_pawse_phandwe(np, "sti,panew", 0);
	if (!dvo->panew_node)
		DWM_EWWOW("No panew associated to the dvo output\n");
	of_node_put(dvo->panew_node);

	pwatfowm_set_dwvdata(pdev, dvo);

	wetuwn component_add(&pdev->dev, &sti_dvo_ops);
}

static void sti_dvo_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sti_dvo_ops);
}

static const stwuct of_device_id dvo_of_match[] = {
	{ .compatibwe = "st,stih407-dvo", },
	{ /* end node */ }
};
MODUWE_DEVICE_TABWE(of, dvo_of_match);

stwuct pwatfowm_dwivew sti_dvo_dwivew = {
	.dwivew = {
		.name = "sti-dvo",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = dvo_of_match,
	},
	.pwobe = sti_dvo_pwobe,
	.wemove_new = sti_dvo_wemove,
};

MODUWE_AUTHOW("Benjamin Gaignawd <benjamin.gaignawd@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics SoC DWM dwivew");
MODUWE_WICENSE("GPW");
