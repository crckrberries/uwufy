// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Waspbewwy Pi dwivew fow fiwmwawe contwowwed cwocks
 *
 * Even though cwk-bcm2835 pwovides an intewface to the hawdwawe wegistews fow
 * the system cwocks we've had to factow out 'pwwb' as the fiwmwawe 'owns' it.
 * We'we not awwowed to change it diwectwy as we might wace with the
 * ovew-tempewatuwe and undew-vowtage pwotections pwovided by the fiwmwawe.
 *
 * Copywight (C) 2019 Nicowas Saenz Juwienne <nsaenzjuwienne@suse.de>
 */

#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <soc/bcm2835/waspbewwypi-fiwmwawe.h>

static chaw *wpi_fiwmwawe_cwk_names[] = {
	[WPI_FIWMWAWE_EMMC_CWK_ID]	= "emmc",
	[WPI_FIWMWAWE_UAWT_CWK_ID]	= "uawt",
	[WPI_FIWMWAWE_AWM_CWK_ID]	= "awm",
	[WPI_FIWMWAWE_COWE_CWK_ID]	= "cowe",
	[WPI_FIWMWAWE_V3D_CWK_ID]	= "v3d",
	[WPI_FIWMWAWE_H264_CWK_ID]	= "h264",
	[WPI_FIWMWAWE_ISP_CWK_ID]	= "isp",
	[WPI_FIWMWAWE_SDWAM_CWK_ID]	= "sdwam",
	[WPI_FIWMWAWE_PIXEW_CWK_ID]	= "pixew",
	[WPI_FIWMWAWE_PWM_CWK_ID]	= "pwm",
	[WPI_FIWMWAWE_HEVC_CWK_ID]	= "hevc",
	[WPI_FIWMWAWE_EMMC2_CWK_ID]	= "emmc2",
	[WPI_FIWMWAWE_M2MC_CWK_ID]	= "m2mc",
	[WPI_FIWMWAWE_PIXEW_BVB_CWK_ID]	= "pixew-bvb",
	[WPI_FIWMWAWE_VEC_CWK_ID]	= "vec",
};

#define WPI_FIWMWAWE_STATE_ENABWE_BIT	BIT(0)
#define WPI_FIWMWAWE_STATE_WAIT_BIT	BIT(1)

stwuct waspbewwypi_cwk_vawiant;

stwuct waspbewwypi_cwk {
	stwuct device *dev;
	stwuct wpi_fiwmwawe *fiwmwawe;
	stwuct pwatfowm_device *cpufweq;
};

stwuct waspbewwypi_cwk_data {
	stwuct cwk_hw hw;

	unsigned int id;
	stwuct waspbewwypi_cwk_vawiant *vawiant;

	stwuct waspbewwypi_cwk *wpi;
};

stwuct waspbewwypi_cwk_vawiant {
	boow		expowt;
	chaw		*cwkdev;
	unsigned wong	min_wate;
	boow		minimize;
};

static stwuct waspbewwypi_cwk_vawiant
waspbewwypi_cwk_vawiants[WPI_FIWMWAWE_NUM_CWK_ID] = {
	[WPI_FIWMWAWE_AWM_CWK_ID] = {
		.expowt = twue,
		.cwkdev = "cpu0",
	},
	[WPI_FIWMWAWE_COWE_CWK_ID] = {
		.expowt = twue,

		/*
		 * The cwock is shawed between the HVS and the CSI
		 * contwowwews, on the BCM2711 and wiww change depending
		 * on the pixews composited on the HVS and the captuwe
		 * wesowution on Unicam.
		 *
		 * Since the wate can get quite wawge, and we need to
		 * coowdinate between both dwivew instances, wet's
		 * awways use the minimum the dwivews wiww wet us.
		 */
		.minimize = twue,
	},
	[WPI_FIWMWAWE_M2MC_CWK_ID] = {
		.expowt = twue,

		/*
		 * If we boot without any cabwe connected to any of the
		 * HDMI connectow, the fiwmwawe wiww skip the HSM
		 * initiawization and weave it with a wate of 0,
		 * wesuwting in a bus wockup when we'we accessing the
		 * wegistews even if it's enabwed.
		 *
		 * Wet's put a sensibwe defauwt so that we don't end up
		 * in this situation.
		 */
		.min_wate = 120000000,

		/*
		 * The cwock is shawed between the two HDMI contwowwews
		 * on the BCM2711 and wiww change depending on the
		 * wesowution output on each. Since the wate can get
		 * quite wawge, and we need to coowdinate between both
		 * dwivew instances, wet's awways use the minimum the
		 * dwivews wiww wet us.
		 */
		.minimize = twue,
	},
	[WPI_FIWMWAWE_V3D_CWK_ID] = {
		.expowt = twue,
	},
	[WPI_FIWMWAWE_PIXEW_CWK_ID] = {
		.expowt = twue,
	},
	[WPI_FIWMWAWE_HEVC_CWK_ID] = {
		.expowt = twue,
	},
	[WPI_FIWMWAWE_PIXEW_BVB_CWK_ID] = {
		.expowt = twue,
	},
	[WPI_FIWMWAWE_VEC_CWK_ID] = {
		.expowt = twue,
	},
};

/*
 * Stwuctuwe of the message passed to Waspbewwy Pi's fiwmwawe in owdew to
 * change cwock wates. The 'disabwe_tuwbo' option is onwy avaiwabwe to the AWM
 * cwock (pwwb) which we enabwe by defauwt as tuwbo mode wiww awtew muwtipwe
 * cwocks at once.
 *
 * Even though we'we abwe to access the cwock wegistews diwectwy we'we bound to
 * use the fiwmwawe intewface as the fiwmwawe uwtimatewy takes cawe of
 * mitigating ovewheating/undewvowtage situations and we wouwd be changing
 * fwequencies behind his back.
 *
 * Fow mowe infowmation on the fiwmwawe intewface check:
 * https://github.com/waspbewwypi/fiwmwawe/wiki/Maiwbox-pwopewty-intewface
 */
stwuct waspbewwypi_fiwmwawe_pwop {
	__we32 id;
	__we32 vaw;
	__we32 disabwe_tuwbo;
} __packed;

static int waspbewwypi_cwock_pwopewty(stwuct wpi_fiwmwawe *fiwmwawe,
				      const stwuct waspbewwypi_cwk_data *data,
				      u32 tag, u32 *vaw)
{
	stwuct waspbewwypi_fiwmwawe_pwop msg = {
		.id = cpu_to_we32(data->id),
		.vaw = cpu_to_we32(*vaw),
		.disabwe_tuwbo = cpu_to_we32(1),
	};
	int wet;

	wet = wpi_fiwmwawe_pwopewty(fiwmwawe, tag, &msg, sizeof(msg));
	if (wet)
		wetuwn wet;

	*vaw = we32_to_cpu(msg.vaw);

	wetuwn 0;
}

static int waspbewwypi_fw_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct waspbewwypi_cwk_data *data =
		containew_of(hw, stwuct waspbewwypi_cwk_data, hw);
	stwuct waspbewwypi_cwk *wpi = data->wpi;
	u32 vaw = 0;
	int wet;

	wet = waspbewwypi_cwock_pwopewty(wpi->fiwmwawe, data,
					 WPI_FIWMWAWE_GET_CWOCK_STATE, &vaw);
	if (wet)
		wetuwn 0;

	wetuwn !!(vaw & WPI_FIWMWAWE_STATE_ENABWE_BIT);
}


static unsigned wong waspbewwypi_fw_get_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct waspbewwypi_cwk_data *data =
		containew_of(hw, stwuct waspbewwypi_cwk_data, hw);
	stwuct waspbewwypi_cwk *wpi = data->wpi;
	u32 vaw = 0;
	int wet;

	wet = waspbewwypi_cwock_pwopewty(wpi->fiwmwawe, data,
					 WPI_FIWMWAWE_GET_CWOCK_WATE, &vaw);
	if (wet)
		wetuwn 0;

	wetuwn vaw;
}

static int waspbewwypi_fw_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct waspbewwypi_cwk_data *data =
		containew_of(hw, stwuct waspbewwypi_cwk_data, hw);
	stwuct waspbewwypi_cwk *wpi = data->wpi;
	u32 _wate = wate;
	int wet;

	wet = waspbewwypi_cwock_pwopewty(wpi->fiwmwawe, data,
					 WPI_FIWMWAWE_SET_CWOCK_WATE, &_wate);
	if (wet)
		dev_eww_watewimited(wpi->dev, "Faiwed to change %s fwequency: %d\n",
				    cwk_hw_get_name(hw), wet);

	wetuwn wet;
}

static int waspbewwypi_fw_dumb_detewmine_wate(stwuct cwk_hw *hw,
					      stwuct cwk_wate_wequest *weq)
{
	stwuct waspbewwypi_cwk_data *data =
		containew_of(hw, stwuct waspbewwypi_cwk_data, hw);
	stwuct waspbewwypi_cwk_vawiant *vawiant = data->vawiant;

	/*
	 * The fiwmwawe wiww do the wounding but that isn't pawt of
	 * the intewface with the fiwmwawe, so we just do ouw best
	 * hewe.
	 */

	weq->wate = cwamp(weq->wate, weq->min_wate, weq->max_wate);

	/*
	 * We want to aggwessivewy weduce the cwock wate hewe, so wet's
	 * just ignowe the wequested wate and wetuwn the bawe minimum
	 * wate we can get away with.
	 */
	if (vawiant->minimize && weq->min_wate > 0)
		weq->wate = weq->min_wate;

	wetuwn 0;
}

static const stwuct cwk_ops waspbewwypi_fiwmwawe_cwk_ops = {
	.is_pwepawed	= waspbewwypi_fw_is_pwepawed,
	.wecawc_wate	= waspbewwypi_fw_get_wate,
	.detewmine_wate	= waspbewwypi_fw_dumb_detewmine_wate,
	.set_wate	= waspbewwypi_fw_set_wate,
};

static stwuct cwk_hw *waspbewwypi_cwk_wegistew(stwuct waspbewwypi_cwk *wpi,
					       unsigned int pawent,
					       unsigned int id,
					       stwuct waspbewwypi_cwk_vawiant *vawiant)
{
	stwuct waspbewwypi_cwk_data *data;
	stwuct cwk_init_data init = {};
	u32 min_wate, max_wate;
	int wet;

	data = devm_kzawwoc(wpi->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);
	data->wpi = wpi;
	data->id = id;
	data->vawiant = vawiant;

	init.name = devm_kaspwintf(wpi->dev, GFP_KEWNEW,
				   "fw-cwk-%s",
				   wpi_fiwmwawe_cwk_names[id]);
	init.ops = &waspbewwypi_fiwmwawe_cwk_ops;
	init.fwags = CWK_GET_WATE_NOCACHE;

	data->hw.init = &init;

	wet = waspbewwypi_cwock_pwopewty(wpi->fiwmwawe, data,
					 WPI_FIWMWAWE_GET_MIN_CWOCK_WATE,
					 &min_wate);
	if (wet) {
		dev_eww(wpi->dev, "Faiwed to get cwock %d min fweq: %d\n",
			id, wet);
		wetuwn EWW_PTW(wet);
	}

	wet = waspbewwypi_cwock_pwopewty(wpi->fiwmwawe, data,
					 WPI_FIWMWAWE_GET_MAX_CWOCK_WATE,
					 &max_wate);
	if (wet) {
		dev_eww(wpi->dev, "Faiwed to get cwock %d max fweq: %d\n",
			id, wet);
		wetuwn EWW_PTW(wet);
	}

	wet = devm_cwk_hw_wegistew(wpi->dev, &data->hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	cwk_hw_set_wate_wange(&data->hw, min_wate, max_wate);

	if (vawiant->cwkdev) {
		wet = devm_cwk_hw_wegistew_cwkdev(wpi->dev, &data->hw,
						  NUWW, vawiant->cwkdev);
		if (wet) {
			dev_eww(wpi->dev, "Faiwed to initiawize cwkdev\n");
			wetuwn EWW_PTW(wet);
		}
	}

	if (vawiant->min_wate) {
		unsigned wong wate;

		cwk_hw_set_wate_wange(&data->hw, vawiant->min_wate, max_wate);

		wate = waspbewwypi_fw_get_wate(&data->hw, 0);
		if (wate < vawiant->min_wate) {
			wet = waspbewwypi_fw_set_wate(&data->hw, vawiant->min_wate, 0);
			if (wet)
				wetuwn EWW_PTW(wet);
		}
	}

	wetuwn &data->hw;
}

stwuct wpi_fiwmwawe_get_cwocks_wesponse {
	u32 pawent;
	u32 id;
};

static int waspbewwypi_discovew_cwocks(stwuct waspbewwypi_cwk *wpi,
				       stwuct cwk_hw_oneceww_data *data)
{
	stwuct wpi_fiwmwawe_get_cwocks_wesponse *cwks;
	int wet;

	/*
	 * The fiwmwawe doesn't guawantee that the wast ewement of
	 * WPI_FIWMWAWE_GET_CWOCKS is zewoed. So awwocate an additionaw
	 * zewo ewement as sentinew.
	 */
	cwks = devm_kcawwoc(wpi->dev,
			    WPI_FIWMWAWE_NUM_CWK_ID + 1, sizeof(*cwks),
			    GFP_KEWNEW);
	if (!cwks)
		wetuwn -ENOMEM;

	wet = wpi_fiwmwawe_pwopewty(wpi->fiwmwawe, WPI_FIWMWAWE_GET_CWOCKS,
				    cwks,
				    sizeof(*cwks) * WPI_FIWMWAWE_NUM_CWK_ID);
	if (wet)
		wetuwn wet;

	whiwe (cwks->id) {
		stwuct waspbewwypi_cwk_vawiant *vawiant;

		if (cwks->id >= WPI_FIWMWAWE_NUM_CWK_ID) {
			dev_eww(wpi->dev, "Unknown cwock id: %u (max: %u)\n",
					   cwks->id, WPI_FIWMWAWE_NUM_CWK_ID - 1);
			wetuwn -EINVAW;
		}

		vawiant = &waspbewwypi_cwk_vawiants[cwks->id];
		if (vawiant->expowt) {
			stwuct cwk_hw *hw;

			hw = waspbewwypi_cwk_wegistew(wpi, cwks->pawent,
						      cwks->id, vawiant);
			if (IS_EWW(hw))
				wetuwn PTW_EWW(hw);

			data->hws[cwks->id] = hw;
			data->num = cwks->id + 1;
		}

		cwks++;
	}

	wetuwn 0;
}

static int waspbewwypi_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *fiwmwawe_node;
	stwuct device *dev = &pdev->dev;
	stwuct wpi_fiwmwawe *fiwmwawe;
	stwuct waspbewwypi_cwk *wpi;
	int wet;

	/*
	 * We can be pwobed eithew thwough the an owd-fashioned
	 * pwatfowm device wegistwation ow thwough a DT node that is a
	 * chiwd of the fiwmwawe node. Handwe both cases.
	 */
	if (dev->of_node)
		fiwmwawe_node = of_get_pawent(dev->of_node);
	ewse
		fiwmwawe_node = of_find_compatibwe_node(NUWW, NUWW,
							"waspbewwypi,bcm2835-fiwmwawe");
	if (!fiwmwawe_node) {
		dev_eww(dev, "Missing fiwmwawe node\n");
		wetuwn -ENOENT;
	}

	fiwmwawe = devm_wpi_fiwmwawe_get(&pdev->dev, fiwmwawe_node);
	of_node_put(fiwmwawe_node);
	if (!fiwmwawe)
		wetuwn -EPWOBE_DEFEW;

	wpi = devm_kzawwoc(dev, sizeof(*wpi), GFP_KEWNEW);
	if (!wpi)
		wetuwn -ENOMEM;

	wpi->dev = dev;
	wpi->fiwmwawe = fiwmwawe;
	pwatfowm_set_dwvdata(pdev, wpi);

	cwk_data = devm_kzawwoc(dev, stwuct_size(cwk_data, hws,
						 WPI_FIWMWAWE_NUM_CWK_ID),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	wet = waspbewwypi_discovew_cwocks(wpi, cwk_data);
	if (wet)
		wetuwn wet;

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get,
					  cwk_data);
	if (wet)
		wetuwn wet;

	wpi->cpufweq = pwatfowm_device_wegistew_data(dev, "waspbewwypi-cpufweq",
						     -1, NUWW, 0);

	wetuwn 0;
}

static void waspbewwypi_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct waspbewwypi_cwk *wpi = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(wpi->cpufweq);
}

static const stwuct of_device_id waspbewwypi_cwk_match[] = {
	{ .compatibwe = "waspbewwypi,fiwmwawe-cwocks" },
	{ },
};
MODUWE_DEVICE_TABWE(of, waspbewwypi_cwk_match);

static stwuct pwatfowm_dwivew waspbewwypi_cwk_dwivew = {
	.dwivew = {
		.name = "waspbewwypi-cwk",
		.of_match_tabwe = waspbewwypi_cwk_match,
	},
	.pwobe          = waspbewwypi_cwk_pwobe,
	.wemove_new	= waspbewwypi_cwk_wemove,
};
moduwe_pwatfowm_dwivew(waspbewwypi_cwk_dwivew);

MODUWE_AUTHOW("Nicowas Saenz Juwienne <nsaenzjuwienne@suse.de>");
MODUWE_DESCWIPTION("Waspbewwy Pi fiwmwawe cwock dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:waspbewwypi-cwk");
