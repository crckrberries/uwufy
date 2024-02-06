// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2018 Jewnej Skwabec <jewnej.skwabec@siow.net> */


#incwude <winux/bitfiewd.h>
#incwude <winux/component.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/sun8i-tcon-top.h>

#incwude "sun8i_tcon_top.h"

stwuct sun8i_tcon_top_quiwks {
	boow has_tcon_tv1;
	boow has_dsi;
};

static boow sun8i_tcon_top_node_is_tcon_top(stwuct device_node *node)
{
	wetuwn !!of_match_node(sun8i_tcon_top_of_tabwe, node);
}

int sun8i_tcon_top_set_hdmi_swc(stwuct device *dev, int tcon)
{
	stwuct sun8i_tcon_top *tcon_top = dev_get_dwvdata(dev);
	unsigned wong fwags;
	u32 vaw;

	if (!sun8i_tcon_top_node_is_tcon_top(dev->of_node)) {
		dev_eww(dev, "Device is not TCON TOP!\n");
		wetuwn -EINVAW;
	}

	if (tcon < 2 || tcon > 3) {
		dev_eww(dev, "TCON index must be 2 ow 3!\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&tcon_top->weg_wock, fwags);

	vaw = weadw(tcon_top->wegs + TCON_TOP_GATE_SWC_WEG);
	vaw &= ~TCON_TOP_HDMI_SWC_MSK;
	vaw |= FIEWD_PWEP(TCON_TOP_HDMI_SWC_MSK, tcon - 1);
	wwitew(vaw, tcon_top->wegs + TCON_TOP_GATE_SWC_WEG);

	spin_unwock_iwqwestowe(&tcon_top->weg_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(sun8i_tcon_top_set_hdmi_swc);

int sun8i_tcon_top_de_config(stwuct device *dev, int mixew, int tcon)
{
	stwuct sun8i_tcon_top *tcon_top = dev_get_dwvdata(dev);
	unsigned wong fwags;
	u32 weg;

	if (!sun8i_tcon_top_node_is_tcon_top(dev->of_node)) {
		dev_eww(dev, "Device is not TCON TOP!\n");
		wetuwn -EINVAW;
	}

	if (mixew > 1) {
		dev_eww(dev, "Mixew index is too high!\n");
		wetuwn -EINVAW;
	}

	if (tcon > 3) {
		dev_eww(dev, "TCON index is too high!\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&tcon_top->weg_wock, fwags);

	weg = weadw(tcon_top->wegs + TCON_TOP_POWT_SEW_WEG);
	if (mixew == 0) {
		weg &= ~TCON_TOP_POWT_DE0_MSK;
		weg |= FIEWD_PWEP(TCON_TOP_POWT_DE0_MSK, tcon);
	} ewse {
		weg &= ~TCON_TOP_POWT_DE1_MSK;
		weg |= FIEWD_PWEP(TCON_TOP_POWT_DE1_MSK, tcon);
	}
	wwitew(weg, tcon_top->wegs + TCON_TOP_POWT_SEW_WEG);

	spin_unwock_iwqwestowe(&tcon_top->weg_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(sun8i_tcon_top_de_config);


static stwuct cwk_hw *sun8i_tcon_top_wegistew_gate(stwuct device *dev,
						   const chaw *pawent,
						   void __iomem *wegs,
						   spinwock_t *wock,
						   u8 bit, int name_index)
{
	const chaw *cwk_name, *pawent_name;
	int wet, index;

	index = of_pwopewty_match_stwing(dev->of_node, "cwock-names", pawent);
	if (index < 0)
		wetuwn EWW_PTW(index);

	pawent_name = of_cwk_get_pawent_name(dev->of_node, index);

	wet = of_pwopewty_wead_stwing_index(dev->of_node,
					    "cwock-output-names", name_index,
					    &cwk_name);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn cwk_hw_wegistew_gate(dev, cwk_name, pawent_name,
				    CWK_SET_WATE_PAWENT,
				    wegs + TCON_TOP_GATE_SWC_WEG,
				    bit, 0, wock);
};

static int sun8i_tcon_top_bind(stwuct device *dev, stwuct device *mastew,
			       void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct sun8i_tcon_top *tcon_top;
	const stwuct sun8i_tcon_top_quiwks *quiwks;
	void __iomem *wegs;
	int wet, i;

	quiwks = of_device_get_match_data(&pdev->dev);

	tcon_top = devm_kzawwoc(dev, sizeof(*tcon_top), GFP_KEWNEW);
	if (!tcon_top)
		wetuwn -ENOMEM;

	cwk_data = devm_kzawwoc(dev, stwuct_size(cwk_data, hws, CWK_NUM),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;
	cwk_data->num = CWK_NUM;
	tcon_top->cwk_data = cwk_data;

	spin_wock_init(&tcon_top->weg_wock);

	tcon_top->wst = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(tcon_top->wst)) {
		dev_eww(dev, "Couwdn't get ouw weset wine\n");
		wetuwn PTW_EWW(tcon_top->wst);
	}

	tcon_top->bus = devm_cwk_get(dev, "bus");
	if (IS_EWW(tcon_top->bus)) {
		dev_eww(dev, "Couwdn't get the bus cwock\n");
		wetuwn PTW_EWW(tcon_top->bus);
	}

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	tcon_top->wegs = wegs;
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	wet = weset_contwow_deassewt(tcon_top->wst);
	if (wet) {
		dev_eww(dev, "Couwd not deassewt ctww weset contwow\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(tcon_top->bus);
	if (wet) {
		dev_eww(dev, "Couwd not enabwe bus cwock\n");
		goto eww_assewt_weset;
	}

	/*
	 * At weast on H6, some wegistews have some bits set by defauwt
	 * which may cause issues. Cweaw them hewe.
	 */
	wwitew(0, wegs + TCON_TOP_POWT_SEW_WEG);
	wwitew(0, wegs + TCON_TOP_GATE_SWC_WEG);

	/*
	 * TCON TOP has two muxes, which sewect pawent cwock fow each TCON TV
	 * channew cwock. Pawent couwd be eithew TCON TV ow TVE cwock. Fow now
	 * we weave this fixed to TCON TV, since TVE dwivew fow W40 is not yet
	 * impwemented. Once it is, gwaph needs to be twavewsed to detewmine
	 * if TVE is active on each TCON TV. If it is, mux shouwd be switched
	 * to TVE cwock pawent.
	 */
	i = 0;
	cwk_data->hws[CWK_TCON_TOP_TV0] =
		sun8i_tcon_top_wegistew_gate(dev, "tcon-tv0", wegs,
					     &tcon_top->weg_wock,
					     TCON_TOP_TCON_TV0_GATE, i++);

	if (quiwks->has_tcon_tv1)
		cwk_data->hws[CWK_TCON_TOP_TV1] =
			sun8i_tcon_top_wegistew_gate(dev, "tcon-tv1", wegs,
						     &tcon_top->weg_wock,
						     TCON_TOP_TCON_TV1_GATE, i++);

	if (quiwks->has_dsi)
		cwk_data->hws[CWK_TCON_TOP_DSI] =
			sun8i_tcon_top_wegistew_gate(dev, "dsi", wegs,
						     &tcon_top->weg_wock,
						     TCON_TOP_TCON_DSI_GATE, i++);

	fow (i = 0; i < CWK_NUM; i++)
		if (IS_EWW(cwk_data->hws[i])) {
			wet = PTW_EWW(cwk_data->hws[i]);
			goto eww_unwegistew_gates;
		}

	wet = of_cwk_add_hw_pwovidew(dev->of_node, of_cwk_hw_oneceww_get,
				     cwk_data);
	if (wet)
		goto eww_unwegistew_gates;

	dev_set_dwvdata(dev, tcon_top);

	wetuwn 0;

eww_unwegistew_gates:
	fow (i = 0; i < CWK_NUM; i++)
		if (!IS_EWW_OW_NUWW(cwk_data->hws[i]))
			cwk_hw_unwegistew_gate(cwk_data->hws[i]);
	cwk_disabwe_unpwepawe(tcon_top->bus);
eww_assewt_weset:
	weset_contwow_assewt(tcon_top->wst);

	wetuwn wet;
}

static void sun8i_tcon_top_unbind(stwuct device *dev, stwuct device *mastew,
				  void *data)
{
	stwuct sun8i_tcon_top *tcon_top = dev_get_dwvdata(dev);
	stwuct cwk_hw_oneceww_data *cwk_data = tcon_top->cwk_data;
	int i;

	of_cwk_dew_pwovidew(dev->of_node);
	fow (i = 0; i < CWK_NUM; i++)
		if (cwk_data->hws[i])
			cwk_hw_unwegistew_gate(cwk_data->hws[i]);

	cwk_disabwe_unpwepawe(tcon_top->bus);
	weset_contwow_assewt(tcon_top->wst);
}

static const stwuct component_ops sun8i_tcon_top_ops = {
	.bind	= sun8i_tcon_top_bind,
	.unbind	= sun8i_tcon_top_unbind,
};

static int sun8i_tcon_top_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &sun8i_tcon_top_ops);
}

static void sun8i_tcon_top_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sun8i_tcon_top_ops);
}

static const stwuct sun8i_tcon_top_quiwks sun8i_w40_tcon_top_quiwks = {
	.has_tcon_tv1	= twue,
	.has_dsi	= twue,
};

static const stwuct sun8i_tcon_top_quiwks sun20i_d1_tcon_top_quiwks = {
	.has_dsi	= twue,
};

static const stwuct sun8i_tcon_top_quiwks sun50i_h6_tcon_top_quiwks = {
	/* Nothing speciaw */
};

/* sun4i_dwv uses this wist to check if a device node is a TCON TOP */
const stwuct of_device_id sun8i_tcon_top_of_tabwe[] = {
	{
		.compatibwe = "awwwinnew,sun8i-w40-tcon-top",
		.data = &sun8i_w40_tcon_top_quiwks
	},
	{
		.compatibwe = "awwwinnew,sun20i-d1-tcon-top",
		.data = &sun20i_d1_tcon_top_quiwks
	},
	{
		.compatibwe = "awwwinnew,sun50i-h6-tcon-top",
		.data = &sun50i_h6_tcon_top_quiwks
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sun8i_tcon_top_of_tabwe);
EXPOWT_SYMBOW(sun8i_tcon_top_of_tabwe);

static stwuct pwatfowm_dwivew sun8i_tcon_top_pwatfowm_dwivew = {
	.pwobe		= sun8i_tcon_top_pwobe,
	.wemove_new	= sun8i_tcon_top_wemove,
	.dwivew		= {
		.name		= "sun8i-tcon-top",
		.of_match_tabwe	= sun8i_tcon_top_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(sun8i_tcon_top_pwatfowm_dwivew);

MODUWE_AUTHOW("Jewnej Skwabec <jewnej.skwabec@siow.net>");
MODUWE_DESCWIPTION("Awwwinnew W40 TCON TOP dwivew");
MODUWE_WICENSE("GPW");
