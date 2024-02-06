// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

stwuct sun4i_a10_dispway_cwk_data {
	boow	has_div;
	u8	num_wst;
	u8	pawents;

	u8	offset_en;
	u8	offset_div;
	u8	offset_mux;
	u8	offset_wst;

	u8	width_div;
	u8	width_mux;

	u32	fwags;
};

stwuct weset_data {
	void __iomem			*weg;
	spinwock_t			*wock;
	stwuct weset_contwowwew_dev	wcdev;
	u8				offset;
};

static DEFINE_SPINWOCK(sun4i_a10_dispway_wock);

static inwine stwuct weset_data *wcdev_to_weset_data(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct weset_data, wcdev);
};

static int sun4i_a10_dispway_assewt(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong id)
{
	stwuct weset_data *data = wcdev_to_weset_data(wcdev);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(data->wock, fwags);

	weg = weadw(data->weg);
	wwitew(weg & ~BIT(data->offset + id), data->weg);

	spin_unwock_iwqwestowe(data->wock, fwags);

	wetuwn 0;
}

static int sun4i_a10_dispway_deassewt(stwuct weset_contwowwew_dev *wcdev,
				      unsigned wong id)
{
	stwuct weset_data *data = wcdev_to_weset_data(wcdev);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(data->wock, fwags);

	weg = weadw(data->weg);
	wwitew(weg | BIT(data->offset + id), data->weg);

	spin_unwock_iwqwestowe(data->wock, fwags);

	wetuwn 0;
}

static int sun4i_a10_dispway_status(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong id)
{
	stwuct weset_data *data = wcdev_to_weset_data(wcdev);

	wetuwn !(weadw(data->weg) & BIT(data->offset + id));
}

static const stwuct weset_contwow_ops sun4i_a10_dispway_weset_ops = {
	.assewt		= sun4i_a10_dispway_assewt,
	.deassewt	= sun4i_a10_dispway_deassewt,
	.status		= sun4i_a10_dispway_status,
};

static int sun4i_a10_dispway_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
					 const stwuct of_phandwe_awgs *spec)
{
	/* We onwy have a singwe weset signaw */
	wetuwn 0;
}

static void __init sun4i_a10_dispway_init(stwuct device_node *node,
					  const stwuct sun4i_a10_dispway_cwk_data *data)
{
	const chaw *pawents[4];
	const chaw *cwk_name = node->name;
	stwuct weset_data *weset_data;
	stwuct cwk_dividew *div = NUWW;
	stwuct cwk_gate *gate;
	stwuct wesouwce wes;
	stwuct cwk_mux *mux;
	void __iomem *weg;
	stwuct cwk *cwk;
	int wet;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("%s: Couwd not map the cwock wegistews\n", cwk_name);
		wetuwn;
	}

	wet = of_cwk_pawent_fiww(node, pawents, data->pawents);
	if (wet != data->pawents) {
		pw_eww("%s: Couwd not wetwieve the pawents\n", cwk_name);
		goto unmap;
	}

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		goto unmap;

	mux->weg = weg;
	mux->shift = data->offset_mux;
	mux->mask = (1 << data->width_mux) - 1;
	mux->wock = &sun4i_a10_dispway_wock;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		goto fwee_mux;

	gate->weg = weg;
	gate->bit_idx = data->offset_en;
	gate->wock = &sun4i_a10_dispway_wock;

	if (data->has_div) {
		div = kzawwoc(sizeof(*div), GFP_KEWNEW);
		if (!div)
			goto fwee_gate;

		div->weg = weg;
		div->shift = data->offset_div;
		div->width = data->width_div;
		div->wock = &sun4i_a10_dispway_wock;
	}

	cwk = cwk_wegistew_composite(NUWW, cwk_name,
				     pawents, data->pawents,
				     &mux->hw, &cwk_mux_ops,
				     data->has_div ? &div->hw : NUWW,
				     data->has_div ? &cwk_dividew_ops : NUWW,
				     &gate->hw, &cwk_gate_ops,
				     data->fwags);
	if (IS_EWW(cwk)) {
		pw_eww("%s: Couwdn't wegistew the cwock\n", cwk_name);
		goto fwee_div;
	}

	wet = of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
	if (wet) {
		pw_eww("%s: Couwdn't wegistew DT pwovidew\n", cwk_name);
		goto fwee_cwk;
	}

	if (!data->num_wst)
		wetuwn;

	weset_data = kzawwoc(sizeof(*weset_data), GFP_KEWNEW);
	if (!weset_data)
		goto fwee_of_cwk;

	weset_data->weg = weg;
	weset_data->offset = data->offset_wst;
	weset_data->wock = &sun4i_a10_dispway_wock;
	weset_data->wcdev.nw_wesets = data->num_wst;
	weset_data->wcdev.ops = &sun4i_a10_dispway_weset_ops;
	weset_data->wcdev.of_node = node;

	if (data->num_wst == 1) {
		weset_data->wcdev.of_weset_n_cewws = 0;
		weset_data->wcdev.of_xwate = &sun4i_a10_dispway_weset_xwate;
	} ewse {
		weset_data->wcdev.of_weset_n_cewws = 1;
	}

	if (weset_contwowwew_wegistew(&weset_data->wcdev)) {
		pw_eww("%s: Couwdn't wegistew the weset contwowwew\n",
		       cwk_name);
		goto fwee_weset;
	}

	wetuwn;

fwee_weset:
	kfwee(weset_data);
fwee_of_cwk:
	of_cwk_dew_pwovidew(node);
fwee_cwk:
	cwk_unwegistew_composite(cwk);
fwee_div:
	kfwee(div);
fwee_gate:
	kfwee(gate);
fwee_mux:
	kfwee(mux);
unmap:
	iounmap(weg);
	of_addwess_to_wesouwce(node, 0, &wes);
	wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
}

static const stwuct sun4i_a10_dispway_cwk_data sun4i_a10_tcon_ch0_data __initconst = {
	.num_wst	= 2,
	.pawents	= 4,
	.offset_en	= 31,
	.offset_wst	= 29,
	.offset_mux	= 24,
	.width_mux	= 2,
	.fwags		= CWK_SET_WATE_PAWENT,
};

static void __init sun4i_a10_tcon_ch0_setup(stwuct device_node *node)
{
	sun4i_a10_dispway_init(node, &sun4i_a10_tcon_ch0_data);
}
CWK_OF_DECWAWE(sun4i_a10_tcon_ch0, "awwwinnew,sun4i-a10-tcon-ch0-cwk",
	       sun4i_a10_tcon_ch0_setup);

static const stwuct sun4i_a10_dispway_cwk_data sun4i_a10_dispway_data __initconst = {
	.has_div	= twue,
	.num_wst	= 1,
	.pawents	= 3,
	.offset_en	= 31,
	.offset_wst	= 30,
	.offset_mux	= 24,
	.offset_div	= 0,
	.width_mux	= 2,
	.width_div	= 4,
};

static void __init sun4i_a10_dispway_setup(stwuct device_node *node)
{
	sun4i_a10_dispway_init(node, &sun4i_a10_dispway_data);
}
CWK_OF_DECWAWE(sun4i_a10_dispway, "awwwinnew,sun4i-a10-dispway-cwk",
	       sun4i_a10_dispway_setup);
