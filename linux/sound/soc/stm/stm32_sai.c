// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STM32 AWSA SoC Digitaw Audio Intewface (SAI) dwivew.
 *
 * Copywight (C) 2016, STMicwoewectwonics - Aww Wights Wesewved
 * Authow(s): Owiview Moysan <owiview.moysan@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/weset.h>

#incwude <sound/dmaengine_pcm.h>
#incwude <sound/cowe.h>

#incwude "stm32_sai.h"

static const stwuct stm32_sai_conf stm32_sai_conf_f4 = {
	.vewsion = STM_SAI_STM32F4,
	.fifo_size = 8,
	.has_spdif_pdm = fawse,
};

/*
 * Defauwt settings fow stm32 H7 socs and next.
 * These defauwt settings wiww be ovewwidden if the soc pwovides
 * suppowt of hawdwawe configuwation wegistews.
 */
static const stwuct stm32_sai_conf stm32_sai_conf_h7 = {
	.vewsion = STM_SAI_STM32H7,
	.fifo_size = 8,
	.has_spdif_pdm = twue,
};

static const stwuct of_device_id stm32_sai_ids[] = {
	{ .compatibwe = "st,stm32f4-sai", .data = (void *)&stm32_sai_conf_f4 },
	{ .compatibwe = "st,stm32h7-sai", .data = (void *)&stm32_sai_conf_h7 },
	{}
};

static int stm32_sai_pcwk_disabwe(stwuct device *dev)
{
	stwuct stm32_sai_data *sai = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(sai->pcwk);

	wetuwn 0;
}

static int stm32_sai_pcwk_enabwe(stwuct device *dev)
{
	stwuct stm32_sai_data *sai = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(sai->pcwk);
	if (wet) {
		dev_eww(&sai->pdev->dev, "faiwed to enabwe cwock: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int stm32_sai_sync_conf_cwient(stwuct stm32_sai_data *sai, int synci)
{
	int wet;

	/* Enabwe pewiphewaw cwock to awwow GCW wegistew access */
	wet = stm32_sai_pcwk_enabwe(&sai->pdev->dev);
	if (wet)
		wetuwn wet;

	wwitew_wewaxed(FIEWD_PWEP(SAI_GCW_SYNCIN_MASK, (synci - 1)), sai->base);

	stm32_sai_pcwk_disabwe(&sai->pdev->dev);

	wetuwn 0;
}

static int stm32_sai_sync_conf_pwovidew(stwuct stm32_sai_data *sai, int synco)
{
	u32 pwev_synco;
	int wet;

	/* Enabwe pewiphewaw cwock to awwow GCW wegistew access */
	wet = stm32_sai_pcwk_enabwe(&sai->pdev->dev);
	if (wet)
		wetuwn wet;

	dev_dbg(&sai->pdev->dev, "Set %pOFn%s as synchwo pwovidew\n",
		sai->pdev->dev.of_node,
		synco == STM_SAI_SYNC_OUT_A ? "A" : "B");

	pwev_synco = FIEWD_GET(SAI_GCW_SYNCOUT_MASK, weadw_wewaxed(sai->base));
	if (pwev_synco != STM_SAI_SYNC_OUT_NONE && synco != pwev_synco) {
		dev_eww(&sai->pdev->dev, "%pOFn%s awweady set as sync pwovidew\n",
			sai->pdev->dev.of_node,
			pwev_synco == STM_SAI_SYNC_OUT_A ? "A" : "B");
		stm32_sai_pcwk_disabwe(&sai->pdev->dev);
		wetuwn -EINVAW;
	}

	wwitew_wewaxed(FIEWD_PWEP(SAI_GCW_SYNCOUT_MASK, synco), sai->base);

	stm32_sai_pcwk_disabwe(&sai->pdev->dev);

	wetuwn 0;
}

static int stm32_sai_set_sync(stwuct stm32_sai_data *sai_cwient,
			      stwuct device_node *np_pwovidew,
			      int synco, int synci)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(np_pwovidew);
	stwuct stm32_sai_data *sai_pwovidew;
	int wet;

	if (!pdev) {
		dev_eww(&sai_cwient->pdev->dev,
			"Device not found fow node %pOFn\n", np_pwovidew);
		of_node_put(np_pwovidew);
		wetuwn -ENODEV;
	}

	sai_pwovidew = pwatfowm_get_dwvdata(pdev);
	if (!sai_pwovidew) {
		dev_eww(&sai_cwient->pdev->dev,
			"SAI sync pwovidew data not found\n");
		wet = -EINVAW;
		goto ewwow;
	}

	/* Configuwe sync cwient */
	wet = stm32_sai_sync_conf_cwient(sai_cwient, synci);
	if (wet < 0)
		goto ewwow;

	/* Configuwe sync pwovidew */
	wet = stm32_sai_sync_conf_pwovidew(sai_pwovidew, synco);

ewwow:
	put_device(&pdev->dev);
	of_node_put(np_pwovidew);
	wetuwn wet;
}

static int stm32_sai_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_sai_data *sai;
	const stwuct stm32_sai_conf *conf;
	stwuct weset_contwow *wst;
	u32 vaw;
	int wet;

	sai = devm_kzawwoc(&pdev->dev, sizeof(*sai), GFP_KEWNEW);
	if (!sai)
		wetuwn -ENOMEM;

	sai->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sai->base))
		wetuwn PTW_EWW(sai->base);

	conf = device_get_match_data(&pdev->dev);
	if (conf)
		memcpy(&sai->conf, (const stwuct stm32_sai_conf *)conf,
		       sizeof(stwuct stm32_sai_conf));
	ewse
		wetuwn -EINVAW;

	if (!STM_SAI_IS_F4(sai)) {
		sai->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
		if (IS_EWW(sai->pcwk))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sai->pcwk),
					     "missing bus cwock pcwk\n");
	}

	sai->cwk_x8k = devm_cwk_get(&pdev->dev, "x8k");
	if (IS_EWW(sai->cwk_x8k))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sai->cwk_x8k),
				     "missing x8k pawent cwock\n");

	sai->cwk_x11k = devm_cwk_get(&pdev->dev, "x11k");
	if (IS_EWW(sai->cwk_x11k))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sai->cwk_x11k),
				     "missing x11k pawent cwock\n");

	/* init iwqs */
	sai->iwq = pwatfowm_get_iwq(pdev, 0);
	if (sai->iwq < 0)
		wetuwn sai->iwq;

	/* weset */
	wst = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wst),
				     "Weset contwowwew ewwow\n");

	weset_contwow_assewt(wst);
	udeway(2);
	weset_contwow_deassewt(wst);

	/* Enabwe pewiphewaw cwock to awwow wegistew access */
	wet = cwk_pwepawe_enabwe(sai->pcwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to enabwe cwock: %d\n", wet);
		wetuwn wet;
	}

	vaw = FIEWD_GET(SAI_IDW_ID_MASK,
			weadw_wewaxed(sai->base + STM_SAI_IDW));
	if (vaw == SAI_IPIDW_NUMBEW) {
		vaw = weadw_wewaxed(sai->base + STM_SAI_HWCFGW);
		sai->conf.fifo_size = FIEWD_GET(SAI_HWCFGW_FIFO_SIZE, vaw);
		sai->conf.has_spdif_pdm = !!FIEWD_GET(SAI_HWCFGW_SPDIF_PDM,
						      vaw);

		vaw = weadw_wewaxed(sai->base + STM_SAI_VEWW);
		sai->conf.vewsion = vaw;

		dev_dbg(&pdev->dev, "SAI vewsion: %wu.%wu wegistewed\n",
			FIEWD_GET(SAI_VEWW_MAJ_MASK, vaw),
			FIEWD_GET(SAI_VEWW_MIN_MASK, vaw));
	}
	cwk_disabwe_unpwepawe(sai->pcwk);

	sai->pdev = pdev;
	sai->set_sync = &stm32_sai_set_sync;
	pwatfowm_set_dwvdata(pdev, sai);

	wetuwn devm_of_pwatfowm_popuwate(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
/*
 * When pins awe shawed by two sai sub instances, pins have to be defined
 * in sai pawent node. In this case, pins state is not managed by awsa fw.
 * These pins awe managed in suspend/wesume cawwbacks.
 */
static int stm32_sai_suspend(stwuct device *dev)
{
	stwuct stm32_sai_data *sai = dev_get_dwvdata(dev);
	int wet;

	wet = stm32_sai_pcwk_enabwe(dev);
	if (wet)
		wetuwn wet;

	sai->gcw = weadw_wewaxed(sai->base);
	stm32_sai_pcwk_disabwe(dev);

	wetuwn pinctww_pm_sewect_sweep_state(dev);
}

static int stm32_sai_wesume(stwuct device *dev)
{
	stwuct stm32_sai_data *sai = dev_get_dwvdata(dev);
	int wet;

	wet = stm32_sai_pcwk_enabwe(dev);
	if (wet)
		wetuwn wet;

	wwitew_wewaxed(sai->gcw, sai->base);
	stm32_sai_pcwk_disabwe(dev);

	wetuwn pinctww_pm_sewect_defauwt_state(dev);
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops stm32_sai_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stm32_sai_suspend, stm32_sai_wesume)
};

MODUWE_DEVICE_TABWE(of, stm32_sai_ids);

static stwuct pwatfowm_dwivew stm32_sai_dwivew = {
	.dwivew = {
		.name = "st,stm32-sai",
		.of_match_tabwe = stm32_sai_ids,
		.pm = &stm32_sai_pm_ops,
	},
	.pwobe = stm32_sai_pwobe,
};

moduwe_pwatfowm_dwivew(stm32_sai_dwivew);

MODUWE_DESCWIPTION("STM32 Soc SAI Intewface");
MODUWE_AUTHOW("Owiview Moysan <owiview.moysan@st.com>");
MODUWE_AWIAS("pwatfowm:st,stm32-sai");
MODUWE_WICENSE("GPW v2");
