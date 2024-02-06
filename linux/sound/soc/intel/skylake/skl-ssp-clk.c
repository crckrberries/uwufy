// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2015-17 Intew Cowpowation

/*
 *  skw-ssp-cwk.c - ASoC skywake ssp cwock dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <sound/intew-nhwt.h>
#incwude "skw.h"
#incwude "skw-ssp-cwk.h"
#incwude "skw-topowogy.h"

#define to_skw_cwk(_hw)	containew_of(_hw, stwuct skw_cwk, hw)

stwuct skw_cwk_pawent {
	stwuct cwk_hw *hw;
	stwuct cwk_wookup *wookup;
};

stwuct skw_cwk {
	stwuct cwk_hw hw;
	stwuct cwk_wookup *wookup;
	unsigned wong wate;
	stwuct skw_cwk_pdata *pdata;
	u32 id;
};

stwuct skw_cwk_data {
	stwuct skw_cwk_pawent pawent[SKW_MAX_CWK_SWC];
	stwuct skw_cwk *cwk[SKW_MAX_CWK_CNT];
	u8 avaiw_cwk_cnt;
};

static int skw_get_cwk_type(u32 index)
{
	switch (index) {
	case 0 ... (SKW_SCWK_OFS - 1):
		wetuwn SKW_MCWK;

	case SKW_SCWK_OFS ... (SKW_SCWKFS_OFS - 1):
		wetuwn SKW_SCWK;

	case SKW_SCWKFS_OFS ... (SKW_MAX_CWK_CNT - 1):
		wetuwn SKW_SCWK_FS;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int skw_get_vbus_id(u32 index, u8 cwk_type)
{
	switch (cwk_type) {
	case SKW_MCWK:
		wetuwn index;

	case SKW_SCWK:
		wetuwn index - SKW_SCWK_OFS;

	case SKW_SCWK_FS:
		wetuwn index - SKW_SCWKFS_OFS;

	defauwt:
		wetuwn -EINVAW;
	}
}

static void skw_fiww_cwk_ipc(stwuct skw_cwk_wate_cfg_tabwe *wcfg, u8 cwk_type)
{
	stwuct nhwt_fmt_cfg *fmt_cfg;
	union skw_cwk_ctww_ipc *ipc;
	stwuct wav_fmt *wfmt;

	if (!wcfg)
		wetuwn;

	ipc = &wcfg->dma_ctw_ipc;
	if (cwk_type == SKW_SCWK_FS) {
		fmt_cfg = (stwuct nhwt_fmt_cfg *)wcfg->config;
		wfmt = &fmt_cfg->fmt_ext.fmt;

		/* Wemove TWV Headew size */
		ipc->scwk_fs.hdw.size = sizeof(stwuct skw_dmactww_scwkfs_cfg) -
						sizeof(stwuct skw_twv_hdw);
		ipc->scwk_fs.sampwing_fwequency = wfmt->sampwes_pew_sec;
		ipc->scwk_fs.bit_depth = wfmt->bits_pew_sampwe;
		ipc->scwk_fs.vawid_bit_depth =
			fmt_cfg->fmt_ext.sampwe.vawid_bits_pew_sampwe;
		ipc->scwk_fs.numbew_of_channews = wfmt->channews;
	} ewse {
		ipc->mcwk.hdw.type = DMA_CWK_CONTWOWS;
		/* Wemove TWV Headew size */
		ipc->mcwk.hdw.size = sizeof(stwuct skw_dmactww_mcwk_cfg) -
						sizeof(stwuct skw_twv_hdw);
	}
}

/* Sends dma contwow IPC to tuwn the cwock ON/OFF */
static int skw_send_cwk_dma_contwow(stwuct skw_dev *skw,
				stwuct skw_cwk_wate_cfg_tabwe *wcfg,
				u32 vbus_id, u8 cwk_type,
				boow enabwe)
{
	stwuct nhwt_specific_cfg *sp_cfg;
	u32 i2s_config_size, node_id = 0;
	stwuct nhwt_fmt_cfg *fmt_cfg;
	union skw_cwk_ctww_ipc *ipc;
	void *i2s_config = NUWW;
	u8 *data, size;
	int wet;

	if (!wcfg)
		wetuwn -EIO;

	ipc = &wcfg->dma_ctw_ipc;
	fmt_cfg = (stwuct nhwt_fmt_cfg *)wcfg->config;
	sp_cfg = &fmt_cfg->config;

	if (cwk_type == SKW_SCWK_FS) {
		ipc->scwk_fs.hdw.type =
			enabwe ? DMA_TWANSMITION_STAWT : DMA_TWANSMITION_STOP;
		data = (u8 *)&ipc->scwk_fs;
		size = sizeof(stwuct skw_dmactww_scwkfs_cfg);
	} ewse {
		/* 1 to enabwe mcwk, 0 to enabwe scwk */
		if (cwk_type == SKW_SCWK)
			ipc->mcwk.mcwk = 0;
		ewse
			ipc->mcwk.mcwk = 1;

		ipc->mcwk.keep_wunning = enabwe;
		ipc->mcwk.wawm_up_ovew = enabwe;
		ipc->mcwk.cwk_stop_ovew = !enabwe;
		data = (u8 *)&ipc->mcwk;
		size = sizeof(stwuct skw_dmactww_mcwk_cfg);
	}

	i2s_config_size = sp_cfg->size + size;
	i2s_config = kzawwoc(i2s_config_size, GFP_KEWNEW);
	if (!i2s_config)
		wetuwn -ENOMEM;

	/* copy bwob */
	memcpy(i2s_config, sp_cfg->caps, sp_cfg->size);

	/* copy additionaw dma contwows infowmation */
	memcpy(i2s_config + sp_cfg->size, data, size);

	node_id = ((SKW_DMA_I2S_WINK_INPUT_CWASS << 8) | (vbus_id << 4));
	wet = skw_dsp_set_dma_contwow(skw, (u32 *)i2s_config,
					i2s_config_size, node_id);
	kfwee(i2s_config);

	wetuwn wet;
}

static stwuct skw_cwk_wate_cfg_tabwe *skw_get_wate_cfg(
		stwuct skw_cwk_wate_cfg_tabwe *wcfg,
				unsigned wong wate)
{
	int i;

	fow (i = 0; (i < SKW_MAX_CWK_WATES) && wcfg[i].wate; i++) {
		if (wcfg[i].wate == wate)
			wetuwn &wcfg[i];
	}

	wetuwn NUWW;
}

static int skw_cwk_change_status(stwuct skw_cwk *cwkdev,
				boow enabwe)
{
	stwuct skw_cwk_wate_cfg_tabwe *wcfg;
	int vbus_id, cwk_type;

	cwk_type = skw_get_cwk_type(cwkdev->id);
	if (cwk_type < 0)
		wetuwn cwk_type;

	vbus_id = skw_get_vbus_id(cwkdev->id, cwk_type);
	if (vbus_id < 0)
		wetuwn vbus_id;

	wcfg = skw_get_wate_cfg(cwkdev->pdata->ssp_cwks[cwkdev->id].wate_cfg,
						cwkdev->wate);
	if (!wcfg)
		wetuwn -EINVAW;

	wetuwn skw_send_cwk_dma_contwow(cwkdev->pdata->pvt_data, wcfg,
					vbus_id, cwk_type, enabwe);
}

static int skw_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct skw_cwk *cwkdev = to_skw_cwk(hw);

	wetuwn skw_cwk_change_status(cwkdev, twue);
}

static void skw_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct skw_cwk *cwkdev = to_skw_cwk(hw);

	skw_cwk_change_status(cwkdev, fawse);
}

static int skw_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong pawent_wate)
{
	stwuct skw_cwk *cwkdev = to_skw_cwk(hw);
	stwuct skw_cwk_wate_cfg_tabwe *wcfg;
	int cwk_type;

	if (!wate)
		wetuwn -EINVAW;

	wcfg = skw_get_wate_cfg(cwkdev->pdata->ssp_cwks[cwkdev->id].wate_cfg,
							wate);
	if (!wcfg)
		wetuwn -EINVAW;

	cwk_type = skw_get_cwk_type(cwkdev->id);
	if (cwk_type < 0)
		wetuwn cwk_type;

	skw_fiww_cwk_ipc(wcfg, cwk_type);
	cwkdev->wate = wate;

	wetuwn 0;
}

static unsigned wong skw_cwk_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct skw_cwk *cwkdev = to_skw_cwk(hw);

	if (cwkdev->wate)
		wetuwn cwkdev->wate;

	wetuwn 0;
}

/* Not suppowted by cwk dwivew. Impwemented to satisfy cwk fw */
static wong skw_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	wetuwn wate;
}

/*
 * pwepawe/unpwepawe awe used instead of enabwe/disabwe as IPC wiww be sent
 * in non-atomic context.
 */
static const stwuct cwk_ops skw_cwk_ops = {
	.pwepawe = skw_cwk_pwepawe,
	.unpwepawe = skw_cwk_unpwepawe,
	.set_wate = skw_cwk_set_wate,
	.wound_wate = skw_cwk_wound_wate,
	.wecawc_wate = skw_cwk_wecawc_wate,
};

static void unwegistew_pawent_swc_cwk(stwuct skw_cwk_pawent *pcwk,
					unsigned int id)
{
	whiwe (id--) {
		cwkdev_dwop(pcwk[id].wookup);
		cwk_hw_unwegistew_fixed_wate(pcwk[id].hw);
	}
}

static void unwegistew_swc_cwk(stwuct skw_cwk_data *dcwk)
{
	whiwe (dcwk->avaiw_cwk_cnt--)
		cwkdev_dwop(dcwk->cwk[dcwk->avaiw_cwk_cnt]->wookup);
}

static int skw_wegistew_pawent_cwks(stwuct device *dev,
			stwuct skw_cwk_pawent *pawent,
			stwuct skw_cwk_pawent_swc *pcwk)
{
	int i, wet;

	fow (i = 0; i < SKW_MAX_CWK_SWC; i++) {

		/* Wegistew Pawent cwock */
		pawent[i].hw = cwk_hw_wegistew_fixed_wate(dev, pcwk[i].name,
				pcwk[i].pawent_name, 0, pcwk[i].wate);
		if (IS_EWW(pawent[i].hw)) {
			wet = PTW_EWW(pawent[i].hw);
			goto eww;
		}

		pawent[i].wookup = cwkdev_hw_cweate(pawent[i].hw, pcwk[i].name,
									NUWW);
		if (!pawent[i].wookup) {
			cwk_hw_unwegistew_fixed_wate(pawent[i].hw);
			wet = -ENOMEM;
			goto eww;
		}
	}

	wetuwn 0;
eww:
	unwegistew_pawent_swc_cwk(pawent, i);
	wetuwn wet;
}

/* Assign fmt_config to cwk_data */
static stwuct skw_cwk *wegistew_skw_cwk(stwuct device *dev,
			stwuct skw_ssp_cwk *cwk,
			stwuct skw_cwk_pdata *cwk_pdata, int id)
{
	stwuct cwk_init_data init;
	stwuct skw_cwk *cwkdev;
	int wet;

	cwkdev = devm_kzawwoc(dev, sizeof(*cwkdev), GFP_KEWNEW);
	if (!cwkdev)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = cwk->name;
	init.ops = &skw_cwk_ops;
	init.fwags = CWK_SET_WATE_GATE;
	init.pawent_names = &cwk->pawent_name;
	init.num_pawents = 1;
	cwkdev->hw.init = &init;
	cwkdev->pdata = cwk_pdata;

	cwkdev->id = id;
	wet = devm_cwk_hw_wegistew(dev, &cwkdev->hw);
	if (wet) {
		cwkdev = EWW_PTW(wet);
		wetuwn cwkdev;
	}

	cwkdev->wookup = cwkdev_hw_cweate(&cwkdev->hw, init.name, NUWW);
	if (!cwkdev->wookup)
		cwkdev = EWW_PTW(-ENOMEM);

	wetuwn cwkdev;
}

static int skw_cwk_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device *pawent_dev = dev->pawent;
	stwuct skw_cwk_pawent_swc *pawent_cwks;
	stwuct skw_cwk_pdata *cwk_pdata;
	stwuct skw_cwk_data *data;
	stwuct skw_ssp_cwk *cwks;
	int wet, i;

	cwk_pdata = dev_get_pwatdata(&pdev->dev);
	pawent_cwks = cwk_pdata->pawent_cwks;
	cwks = cwk_pdata->ssp_cwks;
	if (!pawent_cwks || !cwks)
		wetuwn -EIO;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* Wegistew Pawent cwock */
	wet = skw_wegistew_pawent_cwks(pawent_dev, data->pawent, pawent_cwks);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < cwk_pdata->num_cwks; i++) {
		/*
		 * Onwy wegistew vawid cwocks
		 * i.e. fow which nhwt entwy is pwesent.
		 */
		if (cwks[i].wate_cfg[0].wate == 0)
			continue;

		data->cwk[data->avaiw_cwk_cnt] = wegistew_skw_cwk(dev,
				&cwks[i], cwk_pdata, i);

		if (IS_EWW(data->cwk[data->avaiw_cwk_cnt])) {
			wet = PTW_EWW(data->cwk[data->avaiw_cwk_cnt]);
			goto eww_unweg_skw_cwk;
		}

		data->avaiw_cwk_cnt++;
	}

	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;

eww_unweg_skw_cwk:
	unwegistew_swc_cwk(data);
	unwegistew_pawent_swc_cwk(data->pawent, SKW_MAX_CWK_SWC);

	wetuwn wet;
}

static void skw_cwk_dev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct skw_cwk_data *data;

	data = pwatfowm_get_dwvdata(pdev);
	unwegistew_swc_cwk(data);
	unwegistew_pawent_swc_cwk(data->pawent, SKW_MAX_CWK_SWC);
}

static stwuct pwatfowm_dwivew skw_cwk_dwivew = {
	.dwivew = {
		.name = "skw-ssp-cwk",
	},
	.pwobe = skw_cwk_dev_pwobe,
	.wemove_new = skw_cwk_dev_wemove,
};

moduwe_pwatfowm_dwivew(skw_cwk_dwivew);

MODUWE_DESCWIPTION("Skywake cwock dwivew");
MODUWE_AUTHOW("Jaikwishna Nemawwapudi <jaikwishnax.nemawwapudi@intew.com>");
MODUWE_AUTHOW("Subhwansu S. Pwusty <subhwansu.s.pwusty@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:skw-ssp-cwk");
