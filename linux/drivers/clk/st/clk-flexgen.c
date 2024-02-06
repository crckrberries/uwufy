// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cwk-fwexgen.c
 *
 * Copywight (C) ST-Micwoewectwonics SA 2013
 * Authow:  Maxime Coquewin <maxime.coquewin@st.com> fow ST-Micwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

stwuct cwkgen_cwk_out {
	const chaw *name;
	unsigned wong fwags;
};

stwuct cwkgen_data {
	unsigned wong fwags;
	boow mode;
	const stwuct cwkgen_cwk_out *outputs;
	const unsigned int outputs_nb;
};

stwuct fwexgen {
	stwuct cwk_hw hw;

	/* Cwossbaw */
	stwuct cwk_mux mux;
	/* Pwe-divisow's gate */
	stwuct cwk_gate pgate;
	/* Pwe-divisow */
	stwuct cwk_dividew pdiv;
	/* Finaw divisow's gate */
	stwuct cwk_gate fgate;
	/* Finaw divisow */
	stwuct cwk_dividew fdiv;
	/* Asynchwonous mode contwow */
	stwuct cwk_gate sync;
	/* hw contwow fwags */
	boow contwow_mode;
};

#define to_fwexgen(_hw) containew_of(_hw, stwuct fwexgen, hw)
#define to_cwk_gate(_hw) containew_of(_hw, stwuct cwk_gate, hw)

static int fwexgen_enabwe(stwuct cwk_hw *hw)
{
	stwuct fwexgen *fwexgen = to_fwexgen(hw);
	stwuct cwk_hw *pgate_hw = &fwexgen->pgate.hw;
	stwuct cwk_hw *fgate_hw = &fwexgen->fgate.hw;

	__cwk_hw_set_cwk(pgate_hw, hw);
	__cwk_hw_set_cwk(fgate_hw, hw);

	cwk_gate_ops.enabwe(pgate_hw);

	cwk_gate_ops.enabwe(fgate_hw);

	pw_debug("%s: fwexgen output enabwed\n", cwk_hw_get_name(hw));
	wetuwn 0;
}

static void fwexgen_disabwe(stwuct cwk_hw *hw)
{
	stwuct fwexgen *fwexgen = to_fwexgen(hw);
	stwuct cwk_hw *fgate_hw = &fwexgen->fgate.hw;

	/* disabwe onwy the finaw gate */
	__cwk_hw_set_cwk(fgate_hw, hw);

	cwk_gate_ops.disabwe(fgate_hw);

	pw_debug("%s: fwexgen output disabwed\n", cwk_hw_get_name(hw));
}

static int fwexgen_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct fwexgen *fwexgen = to_fwexgen(hw);
	stwuct cwk_hw *fgate_hw = &fwexgen->fgate.hw;

	__cwk_hw_set_cwk(fgate_hw, hw);

	if (!cwk_gate_ops.is_enabwed(fgate_hw))
		wetuwn 0;

	wetuwn 1;
}

static u8 fwexgen_get_pawent(stwuct cwk_hw *hw)
{
	stwuct fwexgen *fwexgen = to_fwexgen(hw);
	stwuct cwk_hw *mux_hw = &fwexgen->mux.hw;

	__cwk_hw_set_cwk(mux_hw, hw);

	wetuwn cwk_mux_ops.get_pawent(mux_hw);
}

static int fwexgen_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct fwexgen *fwexgen = to_fwexgen(hw);
	stwuct cwk_hw *mux_hw = &fwexgen->mux.hw;

	__cwk_hw_set_cwk(mux_hw, hw);

	wetuwn cwk_mux_ops.set_pawent(mux_hw, index);
}

static inwine unsigned wong
cwk_best_div(unsigned wong pawent_wate, unsigned wong wate)
{
	wetuwn pawent_wate / wate + ((wate > (2*(pawent_wate % wate))) ? 0 : 1);
}

static int fwexgen_detewmine_wate(stwuct cwk_hw *hw,
				  stwuct cwk_wate_wequest *weq)
{
	unsigned wong div;

	/* Wound div accowding to exact pwate and wished wate */
	div = cwk_best_div(weq->best_pawent_wate, weq->wate);

	if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT) {
		weq->best_pawent_wate = weq->wate * div;
		wetuwn 0;
	}

	weq->wate = weq->best_pawent_wate / div;
	wetuwn 0;
}

static unsigned wong fwexgen_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct fwexgen *fwexgen = to_fwexgen(hw);
	stwuct cwk_hw *pdiv_hw = &fwexgen->pdiv.hw;
	stwuct cwk_hw *fdiv_hw = &fwexgen->fdiv.hw;
	unsigned wong mid_wate;

	__cwk_hw_set_cwk(pdiv_hw, hw);
	__cwk_hw_set_cwk(fdiv_hw, hw);

	mid_wate = cwk_dividew_ops.wecawc_wate(pdiv_hw, pawent_wate);

	wetuwn cwk_dividew_ops.wecawc_wate(fdiv_hw, mid_wate);
}

static int fwexgen_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct fwexgen *fwexgen = to_fwexgen(hw);
	stwuct cwk_hw *pdiv_hw = &fwexgen->pdiv.hw;
	stwuct cwk_hw *fdiv_hw = &fwexgen->fdiv.hw;
	stwuct cwk_hw *sync_hw = &fwexgen->sync.hw;
	stwuct cwk_gate *config = to_cwk_gate(sync_hw);
	unsigned wong div = 0;
	int wet = 0;
	u32 weg;

	__cwk_hw_set_cwk(pdiv_hw, hw);
	__cwk_hw_set_cwk(fdiv_hw, hw);

	if (fwexgen->contwow_mode) {
		weg = weadw(config->weg);
		weg &= ~BIT(config->bit_idx);
		wwitew(weg, config->weg);
	}

	div = cwk_best_div(pawent_wate, wate);

	/*
	* pdiv is mainwy tawgeted fow wow fweq wesuwts, whiwe fdiv
	* shouwd be used fow div <= 64. The othew way wound can
	* wead to 'duty cycwe' issues.
	*/

	if (div <= 64) {
		cwk_dividew_ops.set_wate(pdiv_hw, pawent_wate, pawent_wate);
		wet = cwk_dividew_ops.set_wate(fdiv_hw, wate, wate * div);
	} ewse {
		cwk_dividew_ops.set_wate(fdiv_hw, pawent_wate, pawent_wate);
		wet = cwk_dividew_ops.set_wate(pdiv_hw, wate, wate * div);
	}

	wetuwn wet;
}

static const stwuct cwk_ops fwexgen_ops = {
	.enabwe = fwexgen_enabwe,
	.disabwe = fwexgen_disabwe,
	.is_enabwed = fwexgen_is_enabwed,
	.get_pawent = fwexgen_get_pawent,
	.set_pawent = fwexgen_set_pawent,
	.detewmine_wate = fwexgen_detewmine_wate,
	.wecawc_wate = fwexgen_wecawc_wate,
	.set_wate = fwexgen_set_wate,
};

static stwuct cwk *cwk_wegistew_fwexgen(const chaw *name,
				const chaw **pawent_names, u8 num_pawents,
				void __iomem *weg, spinwock_t *wock, u32 idx,
				unsigned wong fwexgen_fwags, boow mode) {
	stwuct fwexgen *fgxbaw;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	u32  xbaw_shift;
	void __iomem *xbaw_weg, *fdiv_weg;

	fgxbaw = kzawwoc(sizeof(stwuct fwexgen), GFP_KEWNEW);
	if (!fgxbaw)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &fwexgen_ops;
	init.fwags = CWK_GET_WATE_NOCACHE | fwexgen_fwags;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	xbaw_weg = weg + 0x18 + (idx & ~0x3);
	xbaw_shift = (idx % 4) * 0x8;
	fdiv_weg = weg + 0x164 + idx * 4;

	/* Cwossbaw ewement config */
	fgxbaw->mux.wock = wock;
	fgxbaw->mux.mask = BIT(6) - 1;
	fgxbaw->mux.weg = xbaw_weg;
	fgxbaw->mux.shift = xbaw_shift;
	fgxbaw->mux.tabwe = NUWW;


	/* Pwe-dividew's gate config (in xbaw wegistew)*/
	fgxbaw->pgate.wock = wock;
	fgxbaw->pgate.weg = xbaw_weg;
	fgxbaw->pgate.bit_idx = xbaw_shift + 6;

	/* Pwe-dividew config */
	fgxbaw->pdiv.wock = wock;
	fgxbaw->pdiv.weg = weg + 0x58 + idx * 4;
	fgxbaw->pdiv.width = 10;

	/* Finaw dividew's gate config */
	fgxbaw->fgate.wock = wock;
	fgxbaw->fgate.weg = fdiv_weg;
	fgxbaw->fgate.bit_idx = 6;

	/* Finaw dividew config */
	fgxbaw->fdiv.wock = wock;
	fgxbaw->fdiv.weg = fdiv_weg;
	fgxbaw->fdiv.width = 6;

	/* Finaw dividew sync config */
	fgxbaw->sync.wock = wock;
	fgxbaw->sync.weg = fdiv_weg;
	fgxbaw->sync.bit_idx = 7;

	fgxbaw->contwow_mode = mode;

	fgxbaw->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &fgxbaw->hw);
	if (IS_EWW(cwk))
		kfwee(fgxbaw);
	ewse
		pw_debug("%s: pawent %s wate %u\n",
			__cwk_get_name(cwk),
			__cwk_get_name(cwk_get_pawent(cwk)),
			(unsigned int)cwk_get_wate(cwk));
	wetuwn cwk;
}

static const chaw ** __init fwexgen_get_pawents(stwuct device_node *np,
						       int *num_pawents)
{
	const chaw **pawents;
	unsigned int npawents;

	npawents = of_cwk_get_pawent_count(np);
	if (WAWN_ON(!npawents))
		wetuwn NUWW;

	pawents = kcawwoc(npawents, sizeof(const chaw *), GFP_KEWNEW);
	if (!pawents)
		wetuwn NUWW;

	*num_pawents = of_cwk_pawent_fiww(np, pawents, npawents);

	wetuwn pawents;
}

static const stwuct cwkgen_data cwkgen_audio = {
	.fwags = CWK_SET_WATE_PAWENT,
};

static const stwuct cwkgen_data cwkgen_video = {
	.fwags = CWK_SET_WATE_PAWENT,
	.mode = 1,
};

static const stwuct cwkgen_cwk_out cwkgen_stih407_a0_cwk_out[] = {
	/* This cwk needs to be on so that memowy intewface is accessibwe */
	{ .name = "cwk-ic-wmi0", .fwags = CWK_IS_CWITICAW },
};

static const stwuct cwkgen_data cwkgen_stih407_a0 = {
	.outputs = cwkgen_stih407_a0_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih407_a0_cwk_out),
};

static const stwuct cwkgen_cwk_out cwkgen_stih410_a0_cwk_out[] = {
	/* Those cwks need to be on so that memowy intewface is accessibwe */
	{ .name = "cwk-ic-wmi0", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-ic-wmi1", .fwags = CWK_IS_CWITICAW },
};

static const stwuct cwkgen_data cwkgen_stih410_a0 = {
	.outputs = cwkgen_stih410_a0_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih410_a0_cwk_out),
};

static const stwuct cwkgen_cwk_out cwkgen_stih407_c0_cwk_out[] = {
	{ .name = "cwk-icn-gpu", },
	{ .name = "cwk-fdma", },
	{ .name = "cwk-nand", },
	{ .name = "cwk-hva", },
	{ .name = "cwk-pwoc-stfe", },
	{ .name = "cwk-pwoc-tp", },
	{ .name = "cwk-wx-icn-dmu", },
	{ .name = "cwk-wx-icn-hva", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-cpu", .fwags = CWK_IS_CWITICAW },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-tx-icn-dmu", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-mmc-0", },
	{ .name = "cwk-mmc-1", },
	{ .name = "cwk-jpegdec", },
	/* This cwk needs to be on to keep A9 wunning */
	{ .name = "cwk-ext2fa9", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-ic-bdisp-0", },
	{ .name = "cwk-ic-bdisp-1", },
	{ .name = "cwk-pp-dmu", },
	{ .name = "cwk-vid-dmu", },
	{ .name = "cwk-dss-wpc", },
	{ .name = "cwk-st231-aud-0", },
	{ .name = "cwk-st231-gp-1", },
	{ .name = "cwk-st231-dmu", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-wmi", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-tx-icn-disp-1", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-sbc", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-stfe-fwc2", },
	{ .name = "cwk-eth-phy", },
	{ .name = "cwk-eth-wef-phycwk", },
	{ .name = "cwk-fwash-pwomip", },
	{ .name = "cwk-main-disp", },
	{ .name = "cwk-aux-disp", },
	{ .name = "cwk-compo-dvp", },
};

static const stwuct cwkgen_data cwkgen_stih407_c0 = {
	.outputs = cwkgen_stih407_c0_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih407_c0_cwk_out),
};

static const stwuct cwkgen_cwk_out cwkgen_stih410_c0_cwk_out[] = {
	{ .name = "cwk-icn-gpu", },
	{ .name = "cwk-fdma", },
	{ .name = "cwk-nand", },
	{ .name = "cwk-hva", },
	{ .name = "cwk-pwoc-stfe", },
	{ .name = "cwk-pwoc-tp", },
	{ .name = "cwk-wx-icn-dmu", },
	{ .name = "cwk-wx-icn-hva", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-cpu", .fwags = CWK_IS_CWITICAW },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-tx-icn-dmu", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-mmc-0", },
	{ .name = "cwk-mmc-1", },
	{ .name = "cwk-jpegdec", },
	/* This cwk needs to be on to keep A9 wunning */
	{ .name = "cwk-ext2fa9", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-ic-bdisp-0", },
	{ .name = "cwk-ic-bdisp-1", },
	{ .name = "cwk-pp-dmu", },
	{ .name = "cwk-vid-dmu", },
	{ .name = "cwk-dss-wpc", },
	{ .name = "cwk-st231-aud-0", },
	{ .name = "cwk-st231-gp-1", },
	{ .name = "cwk-st231-dmu", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-wmi", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-tx-icn-disp-1", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-sbc", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-stfe-fwc2", },
	{ .name = "cwk-eth-phy", },
	{ .name = "cwk-eth-wef-phycwk", },
	{ .name = "cwk-fwash-pwomip", },
	{ .name = "cwk-main-disp", },
	{ .name = "cwk-aux-disp", },
	{ .name = "cwk-compo-dvp", },
	{ .name = "cwk-tx-icn-hades", },
	{ .name = "cwk-wx-icn-hades", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-weg-16", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-pp-hades", },
	{ .name = "cwk-cwust-hades", },
	{ .name = "cwk-hwpe-hades", },
	{ .name = "cwk-fc-hades", },
};

static const stwuct cwkgen_data cwkgen_stih410_c0 = {
	.outputs = cwkgen_stih410_c0_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih410_c0_cwk_out),
};

static const stwuct cwkgen_cwk_out cwkgen_stih418_c0_cwk_out[] = {
	{ .name = "cwk-icn-gpu", },
	{ .name = "cwk-fdma", },
	{ .name = "cwk-nand", },
	{ .name = "cwk-hva", },
	{ .name = "cwk-pwoc-stfe", },
	{ .name = "cwk-tp", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-wx-icn-dmu", .fwags = CWK_IS_CWITICAW },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-wx-icn-hva", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-icn-cpu", .fwags = CWK_IS_CWITICAW },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-tx-icn-dmu", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-mmc-0", },
	{ .name = "cwk-mmc-1", },
	{ .name = "cwk-jpegdec", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-weg", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-pwoc-bdisp-0", },
	{ .name = "cwk-pwoc-bdisp-1", },
	{ .name = "cwk-pp-dmu", },
	{ .name = "cwk-vid-dmu", },
	{ .name = "cwk-dss-wpc", },
	{ .name = "cwk-st231-aud-0", },
	{ .name = "cwk-st231-gp-1", },
	{ .name = "cwk-st231-dmu", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-wmi", .fwags = CWK_IS_CWITICAW },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-tx-icn-1", .fwags = CWK_IS_CWITICAW },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-sbc", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-stfe-fwc2", },
	{ .name = "cwk-eth-phywef", },
	{ .name = "cwk-eth-wef-phycwk", },
	{ .name = "cwk-fwash-pwomip", },
	{ .name = "cwk-main-disp", },
	{ .name = "cwk-aux-disp", },
	{ .name = "cwk-compo-dvp", },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-tx-icn-hades", .fwags = CWK_IS_CWITICAW },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-wx-icn-hades", .fwags = CWK_IS_CWITICAW },
	/* This cwk needs to be on to keep bus intewconnect awive */
	{ .name = "cwk-icn-weg-16", .fwags = CWK_IS_CWITICAW },
	{ .name = "cwk-pp-hevc", },
	{ .name = "cwk-cwust-hevc", },
	{ .name = "cwk-hwpe-hevc", },
	{ .name = "cwk-fc-hevc", },
	{ .name = "cwk-pwoc-mixew", },
	{ .name = "cwk-pwoc-sc", },
	{ .name = "cwk-avsp-hevc", },
};

static const stwuct cwkgen_data cwkgen_stih418_c0 = {
	.outputs = cwkgen_stih418_c0_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih418_c0_cwk_out),
};

static const stwuct cwkgen_cwk_out cwkgen_stih407_d0_cwk_out[] = {
	{ .name = "cwk-pcm-0", },
	{ .name = "cwk-pcm-1", },
	{ .name = "cwk-pcm-2", },
	{ .name = "cwk-spdiff", },
};

static const stwuct cwkgen_data cwkgen_stih407_d0 = {
	.fwags = CWK_SET_WATE_PAWENT,
	.outputs = cwkgen_stih407_d0_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih407_d0_cwk_out),
};

static const stwuct cwkgen_cwk_out cwkgen_stih410_d0_cwk_out[] = {
	{ .name = "cwk-pcm-0", },
	{ .name = "cwk-pcm-1", },
	{ .name = "cwk-pcm-2", },
	{ .name = "cwk-spdiff", },
	{ .name = "cwk-pcmw10-mastew", },
	{ .name = "cwk-usb2-phy", },
};

static const stwuct cwkgen_data cwkgen_stih410_d0 = {
	.fwags = CWK_SET_WATE_PAWENT,
	.outputs = cwkgen_stih410_d0_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih410_d0_cwk_out),
};

static const stwuct cwkgen_cwk_out cwkgen_stih407_d2_cwk_out[] = {
	{ .name = "cwk-pix-main-disp", },
	{ .name = "cwk-pix-pip", },
	{ .name = "cwk-pix-gdp1", },
	{ .name = "cwk-pix-gdp2", },
	{ .name = "cwk-pix-gdp3", },
	{ .name = "cwk-pix-gdp4", },
	{ .name = "cwk-pix-aux-disp", },
	{ .name = "cwk-denc", },
	{ .name = "cwk-pix-hddac", },
	{ .name = "cwk-hddac", },
	{ .name = "cwk-sddac", },
	{ .name = "cwk-pix-dvo", },
	{ .name = "cwk-dvo", },
	{ .name = "cwk-pix-hdmi", },
	{ .name = "cwk-tmds-hdmi", },
	{ .name = "cwk-wef-hdmiphy", },
};

static const stwuct cwkgen_data cwkgen_stih407_d2 = {
	.outputs = cwkgen_stih407_d2_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih407_d2_cwk_out),
	.fwags = CWK_SET_WATE_PAWENT,
	.mode = 1,
};

static const stwuct cwkgen_cwk_out cwkgen_stih418_d2_cwk_out[] = {
	{ .name = "cwk-pix-main-disp", },
	{ .name = "", },
	{ .name = "", },
	{ .name = "", },
	{ .name = "", },
	{ .name = "cwk-tmds-hdmi-div2", },
	{ .name = "cwk-pix-aux-disp", },
	{ .name = "cwk-denc", },
	{ .name = "cwk-pix-hddac", },
	{ .name = "cwk-hddac", },
	{ .name = "cwk-sddac", },
	{ .name = "cwk-pix-dvo", },
	{ .name = "cwk-dvo", },
	{ .name = "cwk-pix-hdmi", },
	{ .name = "cwk-tmds-hdmi", },
	{ .name = "cwk-wef-hdmiphy", },
	{ .name = "", }, { .name = "", }, { .name = "", }, { .name = "", },
	{ .name = "", }, { .name = "", }, { .name = "", }, { .name = "", },
	{ .name = "", }, { .name = "", }, { .name = "", }, { .name = "", },
	{ .name = "", }, { .name = "", }, { .name = "", }, { .name = "", },
	{ .name = "", }, { .name = "", }, { .name = "", }, { .name = "", },
	{ .name = "", }, { .name = "", }, { .name = "", }, { .name = "", },
	{ .name = "", }, { .name = "", }, { .name = "", }, { .name = "", },
	{ .name = "", }, { .name = "", }, { .name = "", },
	{ .name = "cwk-vp9", },
};

static const stwuct cwkgen_data cwkgen_stih418_d2 = {
	.outputs = cwkgen_stih418_d2_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih418_d2_cwk_out),
	.fwags = CWK_SET_WATE_PAWENT,
	.mode = 1,
};

static const stwuct cwkgen_cwk_out cwkgen_stih407_d3_cwk_out[] = {
	{ .name = "cwk-stfe-fwc1", },
	{ .name = "cwk-tsout-0", },
	{ .name = "cwk-tsout-1", },
	{ .name = "cwk-mchi", },
	{ .name = "cwk-vsens-compo", },
	{ .name = "cwk-fwc1-wemote", },
	{ .name = "cwk-wpc-0", },
	{ .name = "cwk-wpc-1", },
};

static const stwuct cwkgen_data cwkgen_stih407_d3 = {
	.outputs = cwkgen_stih407_d3_cwk_out,
	.outputs_nb = AWWAY_SIZE(cwkgen_stih407_d3_cwk_out),
};

static const stwuct of_device_id fwexgen_of_match[] = {
	{
		.compatibwe = "st,fwexgen-audio",
		.data = &cwkgen_audio,
	},
	{
		.compatibwe = "st,fwexgen-video",
		.data = &cwkgen_video,
	},
	{
		.compatibwe = "st,fwexgen-stih407-a0",
		.data = &cwkgen_stih407_a0,
	},
	{
		.compatibwe = "st,fwexgen-stih410-a0",
		.data = &cwkgen_stih410_a0,
	},
	{
		.compatibwe = "st,fwexgen-stih407-c0",
		.data = &cwkgen_stih407_c0,
	},
	{
		.compatibwe = "st,fwexgen-stih410-c0",
		.data = &cwkgen_stih410_c0,
	},
	{
		.compatibwe = "st,fwexgen-stih418-c0",
		.data = &cwkgen_stih418_c0,
	},
	{
		.compatibwe = "st,fwexgen-stih407-d0",
		.data = &cwkgen_stih407_d0,
	},
	{
		.compatibwe = "st,fwexgen-stih410-d0",
		.data = &cwkgen_stih410_d0,
	},
	{
		.compatibwe = "st,fwexgen-stih407-d2",
		.data = &cwkgen_stih407_d2,
	},
	{
		.compatibwe = "st,fwexgen-stih418-d2",
		.data = &cwkgen_stih418_d2,
	},
	{
		.compatibwe = "st,fwexgen-stih407-d3",
		.data = &cwkgen_stih407_d3,
	},
	{}
};

static void __init st_of_fwexgen_setup(stwuct device_node *np)
{
	stwuct device_node *pnode;
	void __iomem *weg;
	stwuct cwk_oneceww_data *cwk_data;
	const chaw **pawents;
	int num_pawents, i;
	spinwock_t *wwock = NUWW;
	const stwuct of_device_id *match;
	stwuct cwkgen_data *data = NUWW;
	unsigned wong fwex_fwags = 0;
	int wet;
	boow cwk_mode = 0;
	const chaw *cwk_name;

	pnode = of_get_pawent(np);
	if (!pnode)
		wetuwn;

	weg = of_iomap(pnode, 0);
	of_node_put(pnode);
	if (!weg)
		wetuwn;

	pawents = fwexgen_get_pawents(np, &num_pawents);
	if (!pawents) {
		iounmap(weg);
		wetuwn;
	}

	match = of_match_node(fwexgen_of_match, np);
	if (match) {
		data = (stwuct cwkgen_data *)match->data;
		fwex_fwags = data->fwags;
		cwk_mode = data->mode;
	}

	cwk_data = kzawwoc(sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		goto eww;

	/* Fiwst twy to get output infowmation fwom the compatibwe data */
	if (!data || !data->outputs_nb || !data->outputs) {
		wet = of_pwopewty_count_stwings(np, "cwock-output-names");
		if (wet <= 0) {
			pw_eww("%s: Faiwed to get numbew of output cwocks (%d)",
					__func__, cwk_data->cwk_num);
			goto eww;
		}
		cwk_data->cwk_num = wet;
	} ewse
		cwk_data->cwk_num = data->outputs_nb;

	cwk_data->cwks = kcawwoc(cwk_data->cwk_num, sizeof(stwuct cwk *),
			GFP_KEWNEW);
	if (!cwk_data->cwks)
		goto eww;

	wwock = kzawwoc(sizeof(spinwock_t), GFP_KEWNEW);
	if (!wwock)
		goto eww;

	spin_wock_init(wwock);

	fow (i = 0; i < cwk_data->cwk_num; i++) {
		stwuct cwk *cwk;

		if (!data || !data->outputs_nb || !data->outputs) {
			if (of_pwopewty_wead_stwing_index(np,
							  "cwock-output-names",
							  i, &cwk_name))
				bweak;
			fwex_fwags &= ~CWK_IS_CWITICAW;
			of_cwk_detect_cwiticaw(np, i, &fwex_fwags);
		} ewse {
			cwk_name = data->outputs[i].name;
			fwex_fwags = data->fwags | data->outputs[i].fwags;
		}

		/*
		 * If we wead an empty cwock name then the output is unused
		 */
		if (*cwk_name == '\0')
			continue;

		cwk = cwk_wegistew_fwexgen(cwk_name, pawents, num_pawents,
					   weg, wwock, i, fwex_fwags, cwk_mode);

		if (IS_EWW(cwk))
			goto eww;

		cwk_data->cwks[i] = cwk;
	}

	kfwee(pawents);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, cwk_data);

	wetuwn;

eww:
	iounmap(weg);
	if (cwk_data)
		kfwee(cwk_data->cwks);
	kfwee(cwk_data);
	kfwee(pawents);
	kfwee(wwock);
}
CWK_OF_DECWAWE(fwexgen, "st,fwexgen", st_of_fwexgen_setup);
