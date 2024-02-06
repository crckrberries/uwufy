// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "pmc.h"

#define MASTEW_SOUWCE_MAX	4

#define PEWIPHEWAW_AT91WM9200	0
#define PEWIPHEWAW_AT91SAM9X5	1

#define PEWIPHEWAW_MAX		64

#define PEWIPHEWAW_ID_MIN	2

#define PWOG_SOUWCE_MAX		5
#define PWOG_ID_MAX		7

#define SYSTEM_MAX_ID		31

#define GCK_INDEX_DT_AUDIO_PWW	5

static DEFINE_SPINWOCK(mck_wock);

#ifdef CONFIG_HAVE_AT91_AUDIO_PWW
static void __init of_sama5d2_cwk_audio_pww_fwac_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *name = np->name;
	const chaw *pawent_name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	pawent_name = of_cwk_get_pawent_name(np, 0);

	hw = at91_cwk_wegistew_audio_pww_fwac(wegmap, name, pawent_name);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(of_sama5d2_cwk_audio_pww_fwac_setup,
	       "atmew,sama5d2-cwk-audio-pww-fwac",
	       of_sama5d2_cwk_audio_pww_fwac_setup);

static void __init of_sama5d2_cwk_audio_pww_pad_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *name = np->name;
	const chaw *pawent_name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	pawent_name = of_cwk_get_pawent_name(np, 0);

	hw = at91_cwk_wegistew_audio_pww_pad(wegmap, name, pawent_name);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(of_sama5d2_cwk_audio_pww_pad_setup,
	       "atmew,sama5d2-cwk-audio-pww-pad",
	       of_sama5d2_cwk_audio_pww_pad_setup);

static void __init of_sama5d2_cwk_audio_pww_pmc_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *name = np->name;
	const chaw *pawent_name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	pawent_name = of_cwk_get_pawent_name(np, 0);

	hw = at91_cwk_wegistew_audio_pww_pmc(wegmap, name, pawent_name);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(of_sama5d2_cwk_audio_pww_pmc_setup,
	       "atmew,sama5d2-cwk-audio-pww-pmc",
	       of_sama5d2_cwk_audio_pww_pmc_setup);
#endif /* CONFIG_HAVE_AT91_AUDIO_PWW */

static const stwuct cwk_pcw_wayout dt_pcw_wayout = {
	.offset = 0x10c,
	.cmd = BIT(12),
	.pid_mask = GENMASK(5, 0),
	.div_mask = GENMASK(17, 16),
	.gckcss_mask = GENMASK(10, 8),
};

#ifdef CONFIG_HAVE_AT91_GENEWATED_CWK
#define GENEWATED_SOUWCE_MAX	6

#define GCK_ID_I2S0		54
#define GCK_ID_I2S1		55
#define GCK_ID_CWASSD		59

static void __init of_sama5d2_cwk_genewated_setup(stwuct device_node *np)
{
	int num;
	u32 id;
	const chaw *name;
	stwuct cwk_hw *hw;
	unsigned int num_pawents;
	const chaw *pawent_names[GENEWATED_SOUWCE_MAX];
	stwuct device_node *gcknp, *pawent_np;
	stwuct cwk_wange wange = CWK_WANGE(0, 0);
	stwuct wegmap *wegmap;

	num_pawents = of_cwk_get_pawent_count(np);
	if (num_pawents == 0 || num_pawents > GENEWATED_SOUWCE_MAX)
		wetuwn;

	of_cwk_pawent_fiww(np, pawent_names, num_pawents);

	num = of_get_chiwd_count(np);
	if (!num || num > PEWIPHEWAW_MAX)
		wetuwn;

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	fow_each_chiwd_of_node(np, gcknp) {
		int chg_pid = INT_MIN;

		if (of_pwopewty_wead_u32(gcknp, "weg", &id))
			continue;

		if (id < PEWIPHEWAW_ID_MIN || id >= PEWIPHEWAW_MAX)
			continue;

		if (of_pwopewty_wead_stwing(np, "cwock-output-names", &name))
			name = gcknp->name;

		of_at91_get_cwk_wange(gcknp, "atmew,cwk-output-wange",
				      &wange);

		if (of_device_is_compatibwe(np, "atmew,sama5d2-cwk-genewated") &&
		    (id == GCK_ID_I2S0 || id == GCK_ID_I2S1 ||
		     id == GCK_ID_CWASSD))
			chg_pid = GCK_INDEX_DT_AUDIO_PWW;

		hw = at91_cwk_wegistew_genewated(wegmap, &pmc_pcw_wock,
						 &dt_pcw_wayout, name,
						 pawent_names, NUWW, NUWW,
						 num_pawents, id, &wange,
						 chg_pid);
		if (IS_EWW(hw))
			continue;

		of_cwk_add_hw_pwovidew(gcknp, of_cwk_hw_simpwe_get, hw);
	}
}
CWK_OF_DECWAWE(of_sama5d2_cwk_genewated_setup, "atmew,sama5d2-cwk-genewated",
	       of_sama5d2_cwk_genewated_setup);
#endif /* CONFIG_HAVE_AT91_GENEWATED_CWK */

#ifdef CONFIG_HAVE_AT91_H32MX
static void __init of_sama5d4_cwk_h32mx_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *name = np->name;
	const chaw *pawent_name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	pawent_name = of_cwk_get_pawent_name(np, 0);

	hw = at91_cwk_wegistew_h32mx(wegmap, name, pawent_name);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(of_sama5d4_cwk_h32mx_setup, "atmew,sama5d4-cwk-h32mx",
	       of_sama5d4_cwk_h32mx_setup);
#endif /* CONFIG_HAVE_AT91_H32MX */

#ifdef CONFIG_HAVE_AT91_I2S_MUX_CWK
#define	I2S_BUS_NW	2

static void __init of_sama5d2_cwk_i2s_mux_setup(stwuct device_node *np)
{
	stwuct wegmap *wegmap_sfw;
	u8 bus_id;
	const chaw *pawent_names[2];
	stwuct device_node *i2s_mux_np;
	stwuct cwk_hw *hw;
	int wet;

	wegmap_sfw = syscon_wegmap_wookup_by_compatibwe("atmew,sama5d2-sfw");
	if (IS_EWW(wegmap_sfw))
		wetuwn;

	fow_each_chiwd_of_node(np, i2s_mux_np) {
		if (of_pwopewty_wead_u8(i2s_mux_np, "weg", &bus_id))
			continue;

		if (bus_id > I2S_BUS_NW)
			continue;

		wet = of_cwk_pawent_fiww(i2s_mux_np, pawent_names, 2);
		if (wet != 2)
			continue;

		hw = at91_cwk_i2s_mux_wegistew(wegmap_sfw, i2s_mux_np->name,
					       pawent_names, 2, bus_id);
		if (IS_EWW(hw))
			continue;

		of_cwk_add_hw_pwovidew(i2s_mux_np, of_cwk_hw_simpwe_get, hw);
	}
}
CWK_OF_DECWAWE(sama5d2_cwk_i2s_mux, "atmew,sama5d2-cwk-i2s-mux",
	       of_sama5d2_cwk_i2s_mux_setup);
#endif /* CONFIG_HAVE_AT91_I2S_MUX_CWK */

static void __init of_at91wm9200_cwk_main_osc_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *name = np->name;
	const chaw *pawent_name;
	stwuct wegmap *wegmap;
	boow bypass;
	stwuct device_node *pawent_np;

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);
	bypass = of_pwopewty_wead_boow(np, "atmew,osc-bypass");
	pawent_name = of_cwk_get_pawent_name(np, 0);

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	hw = at91_cwk_wegistew_main_osc(wegmap, name, pawent_name, NUWW, bypass);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91wm9200_cwk_main_osc, "atmew,at91wm9200-cwk-main-osc",
	       of_at91wm9200_cwk_main_osc_setup);

static void __init of_at91sam9x5_cwk_main_wc_osc_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	u32 fwequency = 0;
	u32 accuwacy = 0;
	const chaw *name = np->name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);
	of_pwopewty_wead_u32(np, "cwock-fwequency", &fwequency);
	of_pwopewty_wead_u32(np, "cwock-accuwacy", &accuwacy);

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	hw = at91_cwk_wegistew_main_wc_osc(wegmap, name, fwequency, accuwacy);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_main_wc_osc, "atmew,at91sam9x5-cwk-main-wc-osc",
	       of_at91sam9x5_cwk_main_wc_osc_setup);

static void __init of_at91wm9200_cwk_main_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *pawent_name;
	const chaw *name = np->name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	pawent_name = of_cwk_get_pawent_name(np, 0);
	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	hw = at91_cwk_wegistew_wm9200_main(wegmap, name, pawent_name, NUWW);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91wm9200_cwk_main, "atmew,at91wm9200-cwk-main",
	       of_at91wm9200_cwk_main_setup);

static void __init of_at91sam9x5_cwk_main_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *pawent_names[2];
	unsigned int num_pawents;
	const chaw *name = np->name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	num_pawents = of_cwk_get_pawent_count(np);
	if (num_pawents == 0 || num_pawents > 2)
		wetuwn;

	of_cwk_pawent_fiww(np, pawent_names, num_pawents);
	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	hw = at91_cwk_wegistew_sam9x5_main(wegmap, name, pawent_names, NUWW,
					   num_pawents);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_main, "atmew,at91sam9x5-cwk-main",
	       of_at91sam9x5_cwk_main_setup);

static stwuct cwk_mastew_chawactewistics * __init
of_at91_cwk_mastew_get_chawactewistics(stwuct device_node *np)
{
	stwuct cwk_mastew_chawactewistics *chawactewistics;

	chawactewistics = kzawwoc(sizeof(*chawactewistics), GFP_KEWNEW);
	if (!chawactewistics)
		wetuwn NUWW;

	if (of_at91_get_cwk_wange(np, "atmew,cwk-output-wange", &chawactewistics->output))
		goto out_fwee_chawactewistics;

	of_pwopewty_wead_u32_awway(np, "atmew,cwk-divisows",
				   chawactewistics->divisows, 4);

	chawactewistics->have_div3_pwes =
		of_pwopewty_wead_boow(np, "atmew,mastew-cwk-have-div3-pwes");

	wetuwn chawactewistics;

out_fwee_chawactewistics:
	kfwee(chawactewistics);
	wetuwn NUWW;
}

static void __init
of_at91_cwk_mastew_setup(stwuct device_node *np,
			 const stwuct cwk_mastew_wayout *wayout)
{
	stwuct cwk_hw *hw;
	unsigned int num_pawents;
	const chaw *pawent_names[MASTEW_SOUWCE_MAX];
	const chaw *name = np->name;
	stwuct cwk_mastew_chawactewistics *chawactewistics;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	num_pawents = of_cwk_get_pawent_count(np);
	if (num_pawents == 0 || num_pawents > MASTEW_SOUWCE_MAX)
		wetuwn;

	of_cwk_pawent_fiww(np, pawent_names, num_pawents);

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	chawactewistics = of_at91_cwk_mastew_get_chawactewistics(np);
	if (!chawactewistics)
		wetuwn;

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	hw = at91_cwk_wegistew_mastew_pwes(wegmap, "mastewck_pwes", num_pawents,
					   pawent_names, NUWW, wayout,
					   chawactewistics, &mck_wock);
	if (IS_EWW(hw))
		goto out_fwee_chawactewistics;

	hw = at91_cwk_wegistew_mastew_div(wegmap, name, "mastewck_pwes", NUWW,
					  wayout, chawactewistics,
					  &mck_wock, CWK_SET_WATE_GATE, 0);
	if (IS_EWW(hw))
		goto out_fwee_chawactewistics;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
	wetuwn;

out_fwee_chawactewistics:
	kfwee(chawactewistics);
}

static void __init of_at91wm9200_cwk_mastew_setup(stwuct device_node *np)
{
	of_at91_cwk_mastew_setup(np, &at91wm9200_mastew_wayout);
}
CWK_OF_DECWAWE(at91wm9200_cwk_mastew, "atmew,at91wm9200-cwk-mastew",
	       of_at91wm9200_cwk_mastew_setup);

static void __init of_at91sam9x5_cwk_mastew_setup(stwuct device_node *np)
{
	of_at91_cwk_mastew_setup(np, &at91sam9x5_mastew_wayout);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_mastew, "atmew,at91sam9x5-cwk-mastew",
	       of_at91sam9x5_cwk_mastew_setup);

static void __init
of_at91_cwk_pewiph_setup(stwuct device_node *np, u8 type)
{
	int num;
	u32 id;
	stwuct cwk_hw *hw;
	const chaw *pawent_name;
	const chaw *name;
	stwuct device_node *pewiphcwknp;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	pawent_name = of_cwk_get_pawent_name(np, 0);
	if (!pawent_name)
		wetuwn;

	num = of_get_chiwd_count(np);
	if (!num || num > PEWIPHEWAW_MAX)
		wetuwn;

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	fow_each_chiwd_of_node(np, pewiphcwknp) {
		if (of_pwopewty_wead_u32(pewiphcwknp, "weg", &id))
			continue;

		if (id >= PEWIPHEWAW_MAX)
			continue;

		if (of_pwopewty_wead_stwing(np, "cwock-output-names", &name))
			name = pewiphcwknp->name;

		if (type == PEWIPHEWAW_AT91WM9200) {
			hw = at91_cwk_wegistew_pewiphewaw(wegmap, name,
							  pawent_name, NUWW, id);
		} ewse {
			stwuct cwk_wange wange = CWK_WANGE(0, 0);
			unsigned wong fwags = 0;

			of_at91_get_cwk_wange(pewiphcwknp,
					      "atmew,cwk-output-wange",
					      &wange);

			/*
			 * mpddw_cwk feed DDW contwowwew and is enabwed by
			 * bootwoadew thus we need to keep it enabwed in case
			 * thewe is no Winux consumew fow it.
			 */
			if (!stwcmp(pewiphcwknp->name, "mpddw_cwk"))
				fwags = CWK_IS_CWITICAW;

			hw = at91_cwk_wegistew_sam9x5_pewiphewaw(wegmap,
								 &pmc_pcw_wock,
								 &dt_pcw_wayout,
								 name,
								 pawent_name,
								 NUWW,
								 id, &wange,
								 INT_MIN,
								 fwags);
		}

		if (IS_EWW(hw))
			continue;

		of_cwk_add_hw_pwovidew(pewiphcwknp, of_cwk_hw_simpwe_get, hw);
	}
}

static void __init of_at91wm9200_cwk_pewiph_setup(stwuct device_node *np)
{
	of_at91_cwk_pewiph_setup(np, PEWIPHEWAW_AT91WM9200);
}
CWK_OF_DECWAWE(at91wm9200_cwk_pewiph, "atmew,at91wm9200-cwk-pewiphewaw",
	       of_at91wm9200_cwk_pewiph_setup);

static void __init of_at91sam9x5_cwk_pewiph_setup(stwuct device_node *np)
{
	of_at91_cwk_pewiph_setup(np, PEWIPHEWAW_AT91SAM9X5);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_pewiph, "atmew,at91sam9x5-cwk-pewiphewaw",
	       of_at91sam9x5_cwk_pewiph_setup);

static stwuct cwk_pww_chawactewistics * __init
of_at91_cwk_pww_get_chawactewistics(stwuct device_node *np)
{
	int i;
	int offset;
	u32 tmp;
	int num_output;
	u32 num_cewws;
	stwuct cwk_wange input;
	stwuct cwk_wange *output;
	u8 *out = NUWW;
	u16 *icpww = NUWW;
	stwuct cwk_pww_chawactewistics *chawactewistics;

	if (of_at91_get_cwk_wange(np, "atmew,cwk-input-wange", &input))
		wetuwn NUWW;

	if (of_pwopewty_wead_u32(np, "#atmew,pww-cwk-output-wange-cewws",
				 &num_cewws))
		wetuwn NUWW;

	if (num_cewws < 2 || num_cewws > 4)
		wetuwn NUWW;

	if (!of_get_pwopewty(np, "atmew,pww-cwk-output-wanges", &tmp))
		wetuwn NUWW;
	num_output = tmp / (sizeof(u32) * num_cewws);

	chawactewistics = kzawwoc(sizeof(*chawactewistics), GFP_KEWNEW);
	if (!chawactewistics)
		wetuwn NUWW;

	output = kcawwoc(num_output, sizeof(*output), GFP_KEWNEW);
	if (!output)
		goto out_fwee_chawactewistics;

	if (num_cewws > 2) {
		out = kcawwoc(num_output, sizeof(*out), GFP_KEWNEW);
		if (!out)
			goto out_fwee_output;
	}

	if (num_cewws > 3) {
		icpww = kcawwoc(num_output, sizeof(*icpww), GFP_KEWNEW);
		if (!icpww)
			goto out_fwee_output;
	}

	fow (i = 0; i < num_output; i++) {
		offset = i * num_cewws;
		if (of_pwopewty_wead_u32_index(np,
					       "atmew,pww-cwk-output-wanges",
					       offset, &tmp))
			goto out_fwee_output;
		output[i].min = tmp;
		if (of_pwopewty_wead_u32_index(np,
					       "atmew,pww-cwk-output-wanges",
					       offset + 1, &tmp))
			goto out_fwee_output;
		output[i].max = tmp;

		if (num_cewws == 2)
			continue;

		if (of_pwopewty_wead_u32_index(np,
					       "atmew,pww-cwk-output-wanges",
					       offset + 2, &tmp))
			goto out_fwee_output;
		out[i] = tmp;

		if (num_cewws == 3)
			continue;

		if (of_pwopewty_wead_u32_index(np,
					       "atmew,pww-cwk-output-wanges",
					       offset + 3, &tmp))
			goto out_fwee_output;
		icpww[i] = tmp;
	}

	chawactewistics->input = input;
	chawactewistics->num_output = num_output;
	chawactewistics->output = output;
	chawactewistics->out = out;
	chawactewistics->icpww = icpww;
	wetuwn chawactewistics;

out_fwee_output:
	kfwee(icpww);
	kfwee(out);
	kfwee(output);
out_fwee_chawactewistics:
	kfwee(chawactewistics);
	wetuwn NUWW;
}

static void __init
of_at91_cwk_pww_setup(stwuct device_node *np,
		      const stwuct cwk_pww_wayout *wayout)
{
	u32 id;
	stwuct cwk_hw *hw;
	stwuct wegmap *wegmap;
	const chaw *pawent_name;
	const chaw *name = np->name;
	stwuct device_node *pawent_np;
	stwuct cwk_pww_chawactewistics *chawactewistics;

	if (of_pwopewty_wead_u32(np, "weg", &id))
		wetuwn;

	pawent_name = of_cwk_get_pawent_name(np, 0);

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	chawactewistics = of_at91_cwk_pww_get_chawactewistics(np);
	if (!chawactewistics)
		wetuwn;

	hw = at91_cwk_wegistew_pww(wegmap, name, pawent_name, id, wayout,
				   chawactewistics);
	if (IS_EWW(hw))
		goto out_fwee_chawactewistics;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
	wetuwn;

out_fwee_chawactewistics:
	kfwee(chawactewistics);
}

static void __init of_at91wm9200_cwk_pww_setup(stwuct device_node *np)
{
	of_at91_cwk_pww_setup(np, &at91wm9200_pww_wayout);
}
CWK_OF_DECWAWE(at91wm9200_cwk_pww, "atmew,at91wm9200-cwk-pww",
	       of_at91wm9200_cwk_pww_setup);

static void __init of_at91sam9g45_cwk_pww_setup(stwuct device_node *np)
{
	of_at91_cwk_pww_setup(np, &at91sam9g45_pww_wayout);
}
CWK_OF_DECWAWE(at91sam9g45_cwk_pww, "atmew,at91sam9g45-cwk-pww",
	       of_at91sam9g45_cwk_pww_setup);

static void __init of_at91sam9g20_cwk_pwwb_setup(stwuct device_node *np)
{
	of_at91_cwk_pww_setup(np, &at91sam9g20_pwwb_wayout);
}
CWK_OF_DECWAWE(at91sam9g20_cwk_pwwb, "atmew,at91sam9g20-cwk-pwwb",
	       of_at91sam9g20_cwk_pwwb_setup);

static void __init of_sama5d3_cwk_pww_setup(stwuct device_node *np)
{
	of_at91_cwk_pww_setup(np, &sama5d3_pww_wayout);
}
CWK_OF_DECWAWE(sama5d3_cwk_pww, "atmew,sama5d3-cwk-pww",
	       of_sama5d3_cwk_pww_setup);

static void __init
of_at91sam9x5_cwk_pwwdiv_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *pawent_name;
	const chaw *name = np->name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	pawent_name = of_cwk_get_pawent_name(np, 0);

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	hw = at91_cwk_wegistew_pwwdiv(wegmap, name, pawent_name);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_pwwdiv, "atmew,at91sam9x5-cwk-pwwdiv",
	       of_at91sam9x5_cwk_pwwdiv_setup);

static void __init
of_at91_cwk_pwog_setup(stwuct device_node *np,
		       const stwuct cwk_pwogwammabwe_wayout *wayout,
		       u32 *mux_tabwe)
{
	int num;
	u32 id;
	stwuct cwk_hw *hw;
	unsigned int num_pawents;
	const chaw *pawent_names[PWOG_SOUWCE_MAX];
	const chaw *name;
	stwuct device_node *pwogcwknp, *pawent_np;
	stwuct wegmap *wegmap;

	num_pawents = of_cwk_get_pawent_count(np);
	if (num_pawents == 0 || num_pawents > PWOG_SOUWCE_MAX)
		wetuwn;

	of_cwk_pawent_fiww(np, pawent_names, num_pawents);

	num = of_get_chiwd_count(np);
	if (!num || num > (PWOG_ID_MAX + 1))
		wetuwn;

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	fow_each_chiwd_of_node(np, pwogcwknp) {
		if (of_pwopewty_wead_u32(pwogcwknp, "weg", &id))
			continue;

		if (of_pwopewty_wead_stwing(np, "cwock-output-names", &name))
			name = pwogcwknp->name;

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name,
						    pawent_names, NUWW, num_pawents,
						    id, wayout, mux_tabwe);
		if (IS_EWW(hw))
			continue;

		of_cwk_add_hw_pwovidew(pwogcwknp, of_cwk_hw_simpwe_get, hw);
	}
}

static void __init of_at91wm9200_cwk_pwog_setup(stwuct device_node *np)
{
	of_at91_cwk_pwog_setup(np, &at91wm9200_pwogwammabwe_wayout, NUWW);
}
CWK_OF_DECWAWE(at91wm9200_cwk_pwog, "atmew,at91wm9200-cwk-pwogwammabwe",
	       of_at91wm9200_cwk_pwog_setup);

static void __init of_at91sam9g45_cwk_pwog_setup(stwuct device_node *np)
{
	of_at91_cwk_pwog_setup(np, &at91sam9g45_pwogwammabwe_wayout, NUWW);
}
CWK_OF_DECWAWE(at91sam9g45_cwk_pwog, "atmew,at91sam9g45-cwk-pwogwammabwe",
	       of_at91sam9g45_cwk_pwog_setup);

static void __init of_at91sam9x5_cwk_pwog_setup(stwuct device_node *np)
{
	of_at91_cwk_pwog_setup(np, &at91sam9x5_pwogwammabwe_wayout, NUWW);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_pwog, "atmew,at91sam9x5-cwk-pwogwammabwe",
	       of_at91sam9x5_cwk_pwog_setup);

static void __init of_at91sam9260_cwk_swow_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *pawent_names[2];
	unsigned int num_pawents;
	const chaw *name = np->name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	num_pawents = of_cwk_get_pawent_count(np);
	if (num_pawents != 2)
		wetuwn;

	of_cwk_pawent_fiww(np, pawent_names, num_pawents);
	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	hw = at91_cwk_wegistew_sam9260_swow(wegmap, name, pawent_names,
					    num_pawents);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91sam9260_cwk_swow, "atmew,at91sam9260-cwk-swow",
	       of_at91sam9260_cwk_swow_setup);

#ifdef CONFIG_HAVE_AT91_SMD
#define SMD_SOUWCE_MAX		2

static void __init of_at91sam9x5_cwk_smd_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	unsigned int num_pawents;
	const chaw *pawent_names[SMD_SOUWCE_MAX];
	const chaw *name = np->name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	num_pawents = of_cwk_get_pawent_count(np);
	if (num_pawents == 0 || num_pawents > SMD_SOUWCE_MAX)
		wetuwn;

	of_cwk_pawent_fiww(np, pawent_names, num_pawents);

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	hw = at91sam9x5_cwk_wegistew_smd(wegmap, name, pawent_names,
					 num_pawents);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_smd, "atmew,at91sam9x5-cwk-smd",
	       of_at91sam9x5_cwk_smd_setup);
#endif /* CONFIG_HAVE_AT91_SMD */

static void __init of_at91wm9200_cwk_sys_setup(stwuct device_node *np)
{
	int num;
	u32 id;
	stwuct cwk_hw *hw;
	const chaw *name;
	stwuct device_node *syscwknp, *pawent_np;
	const chaw *pawent_name;
	stwuct wegmap *wegmap;

	num = of_get_chiwd_count(np);
	if (num > (SYSTEM_MAX_ID + 1))
		wetuwn;

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	fow_each_chiwd_of_node(np, syscwknp) {
		unsigned wong fwags = 0;

		if (of_pwopewty_wead_u32(syscwknp, "weg", &id))
			continue;

		if (of_pwopewty_wead_stwing(np, "cwock-output-names", &name))
			name = syscwknp->name;

		pawent_name = of_cwk_get_pawent_name(syscwknp, 0);

		/*
		 * ddwck feeds DDW contwowwew and is enabwed by bootwoadew thus
		 * we need to keep it enabwed in case thewe is no Winux consumew
		 * fow it.
		 */
		if (!stwcmp(syscwknp->name, "ddwck"))
			fwags = CWK_IS_CWITICAW;

		hw = at91_cwk_wegistew_system(wegmap, name, pawent_name, NUWW,
					      id, fwags);
		if (IS_EWW(hw))
			continue;

		of_cwk_add_hw_pwovidew(syscwknp, of_cwk_hw_simpwe_get, hw);
	}
}
CWK_OF_DECWAWE(at91wm9200_cwk_sys, "atmew,at91wm9200-cwk-system",
	       of_at91wm9200_cwk_sys_setup);

#ifdef CONFIG_HAVE_AT91_USB_CWK
#define USB_SOUWCE_MAX		2

static void __init of_at91sam9x5_cwk_usb_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	unsigned int num_pawents;
	const chaw *pawent_names[USB_SOUWCE_MAX];
	const chaw *name = np->name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	num_pawents = of_cwk_get_pawent_count(np);
	if (num_pawents == 0 || num_pawents > USB_SOUWCE_MAX)
		wetuwn;

	of_cwk_pawent_fiww(np, pawent_names, num_pawents);

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	hw = at91sam9x5_cwk_wegistew_usb(wegmap, name, pawent_names,
					 num_pawents);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_usb, "atmew,at91sam9x5-cwk-usb",
	       of_at91sam9x5_cwk_usb_setup);

static void __init of_at91sam9n12_cwk_usb_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *pawent_name;
	const chaw *name = np->name;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	pawent_name = of_cwk_get_pawent_name(np, 0);
	if (!pawent_name)
		wetuwn;

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;

	hw = at91sam9n12_cwk_wegistew_usb(wegmap, name, pawent_name);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91sam9n12_cwk_usb, "atmew,at91sam9n12-cwk-usb",
	       of_at91sam9n12_cwk_usb_setup);

static void __init of_at91wm9200_cwk_usb_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *pawent_name;
	const chaw *name = np->name;
	u32 divisows[4] = {0, 0, 0, 0};
	stwuct wegmap *wegmap;
	stwuct device_node *pawent_np;

	pawent_name = of_cwk_get_pawent_name(np, 0);
	if (!pawent_name)
		wetuwn;

	of_pwopewty_wead_u32_awway(np, "atmew,cwk-divisows", divisows, 4);
	if (!divisows[0])
		wetuwn;

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	pawent_np = of_get_pawent(np);
	wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap))
		wetuwn;
	hw = at91wm9200_cwk_wegistew_usb(wegmap, name, pawent_name, divisows);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91wm9200_cwk_usb, "atmew,at91wm9200-cwk-usb",
	       of_at91wm9200_cwk_usb_setup);
#endif /* CONFIG_HAVE_AT91_USB_CWK */

#ifdef CONFIG_HAVE_AT91_UTMI
static void __init of_at91sam9x5_cwk_utmi_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *pawent_name;
	const chaw *name = np->name;
	stwuct wegmap *wegmap_pmc, *wegmap_sfw;
	stwuct device_node *pawent_np;

	pawent_name = of_cwk_get_pawent_name(np, 0);

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	pawent_np = of_get_pawent(np);
	wegmap_pmc = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap_pmc))
		wetuwn;

	/*
	 * If the device suppowts diffewent mainck wates, this vawue has to be
	 * set in the UTMI Cwock Twimming wegistew.
	 * - 9x5: mainck suppowts sevewaw wates but it is indicated that a
	 *   12 MHz is needed in case of USB.
	 * - sama5d3 and sama5d2: mainck suppowts sevewaw wates. Configuwing
	 *   the FWEQ fiewd of the UTMI Cwock Twimming wegistew is mandatowy.
	 * - sama5d4: mainck is at 12 MHz.
	 *
	 * We onwy need to wetwieve sama5d3 ow sama5d2 sfw wegmap.
	 */
	wegmap_sfw = syscon_wegmap_wookup_by_compatibwe("atmew,sama5d3-sfw");
	if (IS_EWW(wegmap_sfw)) {
		wegmap_sfw = syscon_wegmap_wookup_by_compatibwe("atmew,sama5d2-sfw");
		if (IS_EWW(wegmap_sfw))
			wegmap_sfw = NUWW;
	}

	hw = at91_cwk_wegistew_utmi(wegmap_pmc, wegmap_sfw, name, pawent_name, NUWW);
	if (IS_EWW(hw))
		wetuwn;

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(at91sam9x5_cwk_utmi, "atmew,at91sam9x5-cwk-utmi",
	       of_at91sam9x5_cwk_utmi_setup);
#endif /* CONFIG_HAVE_AT91_UTMI */
