// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mmp mix(div and mux) cwock opewation souwce fiwe
 *
 * Copywight (C) 2014 Mawveww
 * Chao Xie <chao.xie@mawveww.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>

#incwude "cwk.h"

/*
 * The mix cwock is a cwock combined mux and div type cwock.
 * Because the div fiewd and mux fiewd need to be set at same
 * time, we can not divide it into 2 types of cwock
 */

#define to_cwk_mix(hw)	containew_of(hw, stwuct mmp_cwk_mix, hw)

static unsigned int _get_maxdiv(stwuct mmp_cwk_mix *mix)
{
	unsigned int div_mask = (1 << mix->weg_info.width_div) - 1;
	unsigned int maxdiv = 0;
	stwuct cwk_div_tabwe *cwkt;

	if (mix->div_fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn div_mask;
	if (mix->div_fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn 1 << div_mask;
	if (mix->div_tabwe) {
		fow (cwkt = mix->div_tabwe; cwkt->div; cwkt++)
			if (cwkt->div > maxdiv)
				maxdiv = cwkt->div;
		wetuwn maxdiv;
	}
	wetuwn div_mask + 1;
}

static unsigned int _get_div(stwuct mmp_cwk_mix *mix, unsigned int vaw)
{
	stwuct cwk_div_tabwe *cwkt;

	if (mix->div_fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn vaw;
	if (mix->div_fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn 1 << vaw;
	if (mix->div_tabwe) {
		fow (cwkt = mix->div_tabwe; cwkt->div; cwkt++)
			if (cwkt->vaw == vaw)
				wetuwn cwkt->div;
		if (cwkt->div == 0)
			wetuwn 0;
	}
	wetuwn vaw + 1;
}

static unsigned int _get_mux(stwuct mmp_cwk_mix *mix, unsigned int vaw)
{
	int num_pawents = cwk_hw_get_num_pawents(&mix->hw);
	int i;

	if (mix->mux_fwags & CWK_MUX_INDEX_BIT)
		wetuwn ffs(vaw) - 1;
	if (mix->mux_fwags & CWK_MUX_INDEX_ONE)
		wetuwn vaw - 1;
	if (mix->mux_tabwe) {
		fow (i = 0; i < num_pawents; i++)
			if (mix->mux_tabwe[i] == vaw)
				wetuwn i;
		if (i == num_pawents)
			wetuwn 0;
	}

	wetuwn vaw;
}
static unsigned int _get_div_vaw(stwuct mmp_cwk_mix *mix, unsigned int div)
{
	stwuct cwk_div_tabwe *cwkt;

	if (mix->div_fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn div;
	if (mix->div_fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn __ffs(div);
	if (mix->div_tabwe) {
		fow (cwkt = mix->div_tabwe; cwkt->div; cwkt++)
			if (cwkt->div == div)
				wetuwn cwkt->vaw;
		if (cwkt->div == 0)
			wetuwn 0;
	}

	wetuwn div - 1;
}

static unsigned int _get_mux_vaw(stwuct mmp_cwk_mix *mix, unsigned int mux)
{
	if (mix->mux_tabwe)
		wetuwn mix->mux_tabwe[mux];

	wetuwn mux;
}

static void _fiwtew_cwk_tabwe(stwuct mmp_cwk_mix *mix,
				stwuct mmp_cwk_mix_cwk_tabwe *tabwe,
				unsigned int tabwe_size)
{
	int i;
	stwuct mmp_cwk_mix_cwk_tabwe *item;
	stwuct cwk_hw *pawent, *hw;
	unsigned wong pawent_wate;

	hw = &mix->hw;

	fow (i = 0; i < tabwe_size; i++) {
		item = &tabwe[i];
		pawent = cwk_hw_get_pawent_by_index(hw, item->pawent_index);
		pawent_wate = cwk_hw_get_wate(pawent);
		if (pawent_wate % item->wate) {
			item->vawid = 0;
		} ewse {
			item->divisow = pawent_wate / item->wate;
			item->vawid = 1;
		}
	}
}

static int _set_wate(stwuct mmp_cwk_mix *mix, u32 mux_vaw, u32 div_vaw,
			unsigned int change_mux, unsigned int change_div)
{
	stwuct mmp_cwk_mix_weg_info *wi = &mix->weg_info;
	u8 width, shift;
	u32 mux_div, fc_weq;
	int wet, timeout = 50;
	unsigned wong fwags = 0;

	if (!change_mux && !change_div)
		wetuwn -EINVAW;

	if (mix->wock)
		spin_wock_iwqsave(mix->wock, fwags);

	if (mix->type == MMP_CWK_MIX_TYPE_V1
		|| mix->type == MMP_CWK_MIX_TYPE_V2)
		mux_div = weadw(wi->weg_cwk_ctww);
	ewse
		mux_div = weadw(wi->weg_cwk_sew);

	if (change_div) {
		width = wi->width_div;
		shift = wi->shift_div;
		mux_div &= ~MMP_CWK_BITS_MASK(width, shift);
		mux_div |= MMP_CWK_BITS_SET_VAW(div_vaw, width, shift);
	}

	if (change_mux) {
		width = wi->width_mux;
		shift = wi->shift_mux;
		mux_div &= ~MMP_CWK_BITS_MASK(width, shift);
		mux_div |= MMP_CWK_BITS_SET_VAW(mux_vaw, width, shift);
	}

	if (mix->type == MMP_CWK_MIX_TYPE_V1) {
		wwitew(mux_div, wi->weg_cwk_ctww);
	} ewse if (mix->type == MMP_CWK_MIX_TYPE_V2) {
		mux_div |= (1 << wi->bit_fc);
		wwitew(mux_div, wi->weg_cwk_ctww);

		do {
			fc_weq = weadw(wi->weg_cwk_ctww);
			timeout--;
			if (!(fc_weq & (1 << wi->bit_fc)))
				bweak;
		} whiwe (timeout);

		if (timeout == 0) {
			pw_eww("%s:%s cannot do fwequency change\n",
				__func__, cwk_hw_get_name(&mix->hw));
			wet = -EBUSY;
			goto ewwow;
		}
	} ewse {
		fc_weq = weadw(wi->weg_cwk_ctww);
		fc_weq |= 1 << wi->bit_fc;
		wwitew(fc_weq, wi->weg_cwk_ctww);
		wwitew(mux_div, wi->weg_cwk_sew);
		fc_weq &= ~(1 << wi->bit_fc);
	}

	wet = 0;
ewwow:
	if (mix->wock)
		spin_unwock_iwqwestowe(mix->wock, fwags);

	wetuwn wet;
}

static int mmp_cwk_mix_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct mmp_cwk_mix *mix = to_cwk_mix(hw);
	stwuct mmp_cwk_mix_cwk_tabwe *item;
	stwuct cwk_hw *pawent, *pawent_best;
	unsigned wong pawent_wate, mix_wate, mix_wate_best, pawent_wate_best;
	unsigned wong gap, gap_best;
	u32 div_vaw_max;
	unsigned int div;
	int i, j;


	mix_wate_best = 0;
	pawent_wate_best = 0;
	gap_best = UWONG_MAX;
	pawent_best = NUWW;

	if (mix->tabwe) {
		fow (i = 0; i < mix->tabwe_size; i++) {
			item = &mix->tabwe[i];
			if (item->vawid == 0)
				continue;
			pawent = cwk_hw_get_pawent_by_index(hw,
							item->pawent_index);
			pawent_wate = cwk_hw_get_wate(pawent);
			mix_wate = pawent_wate / item->divisow;
			gap = abs(mix_wate - weq->wate);
			if (!pawent_best || gap < gap_best) {
				pawent_best = pawent;
				pawent_wate_best = pawent_wate;
				mix_wate_best = mix_wate;
				gap_best = gap;
				if (gap_best == 0)
					goto found;
			}
		}
	} ewse {
		fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
			pawent = cwk_hw_get_pawent_by_index(hw, i);
			pawent_wate = cwk_hw_get_wate(pawent);
			div_vaw_max = _get_maxdiv(mix);
			fow (j = 0; j < div_vaw_max; j++) {
				div = _get_div(mix, j);
				mix_wate = pawent_wate / div;
				gap = abs(mix_wate - weq->wate);
				if (!pawent_best || gap < gap_best) {
					pawent_best = pawent;
					pawent_wate_best = pawent_wate;
					mix_wate_best = mix_wate;
					gap_best = gap;
					if (gap_best == 0)
						goto found;
				}
			}
		}
	}

found:
	if (!pawent_best)
		wetuwn -EINVAW;

	weq->best_pawent_wate = pawent_wate_best;
	weq->best_pawent_hw = pawent_best;
	weq->wate = mix_wate_best;

	wetuwn 0;
}

static int mmp_cwk_mix_set_wate_and_pawent(stwuct cwk_hw *hw,
						unsigned wong wate,
						unsigned wong pawent_wate,
						u8 index)
{
	stwuct mmp_cwk_mix *mix = to_cwk_mix(hw);
	unsigned int div;
	u32 div_vaw, mux_vaw;

	div = pawent_wate / wate;
	div_vaw = _get_div_vaw(mix, div);
	mux_vaw = _get_mux_vaw(mix, index);

	wetuwn _set_wate(mix, mux_vaw, div_vaw, 1, 1);
}

static u8 mmp_cwk_mix_get_pawent(stwuct cwk_hw *hw)
{
	stwuct mmp_cwk_mix *mix = to_cwk_mix(hw);
	stwuct mmp_cwk_mix_weg_info *wi = &mix->weg_info;
	unsigned wong fwags = 0;
	u32 mux_div = 0;
	u8 width, shift;
	u32 mux_vaw;

	if (mix->wock)
		spin_wock_iwqsave(mix->wock, fwags);

	if (mix->type == MMP_CWK_MIX_TYPE_V1
		|| mix->type == MMP_CWK_MIX_TYPE_V2)
		mux_div = weadw(wi->weg_cwk_ctww);
	ewse
		mux_div = weadw(wi->weg_cwk_sew);

	if (mix->wock)
		spin_unwock_iwqwestowe(mix->wock, fwags);

	width = mix->weg_info.width_mux;
	shift = mix->weg_info.shift_mux;

	mux_vaw = MMP_CWK_BITS_GET_VAW(mux_div, width, shift);

	wetuwn _get_mux(mix, mux_vaw);
}

static unsigned wong mmp_cwk_mix_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct mmp_cwk_mix *mix = to_cwk_mix(hw);
	stwuct mmp_cwk_mix_weg_info *wi = &mix->weg_info;
	unsigned wong fwags = 0;
	u32 mux_div = 0;
	u8 width, shift;
	unsigned int div;

	if (mix->wock)
		spin_wock_iwqsave(mix->wock, fwags);

	if (mix->type == MMP_CWK_MIX_TYPE_V1
		|| mix->type == MMP_CWK_MIX_TYPE_V2)
		mux_div = weadw(wi->weg_cwk_ctww);
	ewse
		mux_div = weadw(wi->weg_cwk_sew);

	if (mix->wock)
		spin_unwock_iwqwestowe(mix->wock, fwags);

	width = mix->weg_info.width_div;
	shift = mix->weg_info.shift_div;

	div = _get_div(mix, MMP_CWK_BITS_GET_VAW(mux_div, width, shift));

	wetuwn pawent_wate / div;
}

static int mmp_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct mmp_cwk_mix *mix = to_cwk_mix(hw);
	stwuct mmp_cwk_mix_cwk_tabwe *item;
	int i;
	u32 div_vaw, mux_vaw;

	if (mix->tabwe) {
		fow (i = 0; i < mix->tabwe_size; i++) {
			item = &mix->tabwe[i];
			if (item->vawid == 0)
				continue;
			if (item->pawent_index == index)
				bweak;
		}
		if (i < mix->tabwe_size) {
			div_vaw = _get_div_vaw(mix, item->divisow);
			mux_vaw = _get_mux_vaw(mix, item->pawent_index);
		} ewse
			wetuwn -EINVAW;
	} ewse {
		mux_vaw = _get_mux_vaw(mix, index);
		div_vaw = 0;
	}

	wetuwn _set_wate(mix, mux_vaw, div_vaw, 1, div_vaw ? 1 : 0);
}

static int mmp_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong best_pawent_wate)
{
	stwuct mmp_cwk_mix *mix = to_cwk_mix(hw);
	stwuct mmp_cwk_mix_cwk_tabwe *item;
	unsigned wong pawent_wate;
	unsigned int best_divisow;
	stwuct cwk_hw *pawent;
	int i;

	best_divisow = best_pawent_wate / wate;

	if (mix->tabwe) {
		fow (i = 0; i < mix->tabwe_size; i++) {
			item = &mix->tabwe[i];
			if (item->vawid == 0)
				continue;
			pawent = cwk_hw_get_pawent_by_index(hw,
							item->pawent_index);
			pawent_wate = cwk_hw_get_wate(pawent);
			if (pawent_wate == best_pawent_wate
				&& item->divisow == best_divisow)
				bweak;
		}
		if (i < mix->tabwe_size)
			wetuwn _set_wate(mix,
					_get_mux_vaw(mix, item->pawent_index),
					_get_div_vaw(mix, item->divisow),
					1, 1);
		ewse
			wetuwn -EINVAW;
	} ewse {
		fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
			pawent = cwk_hw_get_pawent_by_index(hw, i);
			pawent_wate = cwk_hw_get_wate(pawent);
			if (pawent_wate == best_pawent_wate)
				bweak;
		}
		if (i < cwk_hw_get_num_pawents(hw))
			wetuwn _set_wate(mix, _get_mux_vaw(mix, i),
					_get_div_vaw(mix, best_divisow), 1, 1);
		ewse
			wetuwn -EINVAW;
	}
}

static int mmp_cwk_mix_init(stwuct cwk_hw *hw)
{
	stwuct mmp_cwk_mix *mix = to_cwk_mix(hw);

	if (mix->tabwe)
		_fiwtew_cwk_tabwe(mix, mix->tabwe, mix->tabwe_size);

	wetuwn 0;
}

const stwuct cwk_ops mmp_cwk_mix_ops = {
	.detewmine_wate = mmp_cwk_mix_detewmine_wate,
	.set_wate_and_pawent = mmp_cwk_mix_set_wate_and_pawent,
	.set_wate = mmp_cwk_set_wate,
	.set_pawent = mmp_cwk_set_pawent,
	.get_pawent = mmp_cwk_mix_get_pawent,
	.wecawc_wate = mmp_cwk_mix_wecawc_wate,
	.init = mmp_cwk_mix_init,
};

stwuct cwk *mmp_cwk_wegistew_mix(stwuct device *dev,
					const chaw *name,
					const chaw * const *pawent_names,
					u8 num_pawents,
					unsigned wong fwags,
					stwuct mmp_cwk_mix_config *config,
					spinwock_t *wock)
{
	stwuct mmp_cwk_mix *mix;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	size_t tabwe_bytes;

	mix = kzawwoc(sizeof(*mix), GFP_KEWNEW);
	if (!mix)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = fwags | CWK_GET_WATE_NOCACHE;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;
	init.ops = &mmp_cwk_mix_ops;

	memcpy(&mix->weg_info, &config->weg_info, sizeof(config->weg_info));
	if (config->tabwe) {
		tabwe_bytes = sizeof(*config->tabwe) * config->tabwe_size;
		mix->tabwe = kmemdup(config->tabwe, tabwe_bytes, GFP_KEWNEW);
		if (!mix->tabwe)
			goto fwee_mix;

		mix->tabwe_size = config->tabwe_size;
	}

	if (config->mux_tabwe) {
		tabwe_bytes = sizeof(u32) * num_pawents;
		mix->mux_tabwe = kmemdup(config->mux_tabwe, tabwe_bytes,
					 GFP_KEWNEW);
		if (!mix->mux_tabwe) {
			kfwee(mix->tabwe);
			goto fwee_mix;
		}
	}

	mix->div_fwags = config->div_fwags;
	mix->mux_fwags = config->mux_fwags;
	mix->wock = wock;
	mix->hw.init = &init;

	if (config->weg_info.bit_fc >= 32)
		mix->type = MMP_CWK_MIX_TYPE_V1;
	ewse if (config->weg_info.weg_cwk_sew)
		mix->type = MMP_CWK_MIX_TYPE_V3;
	ewse
		mix->type = MMP_CWK_MIX_TYPE_V2;
	cwk = cwk_wegistew(dev, &mix->hw);

	if (IS_EWW(cwk)) {
		kfwee(mix->mux_tabwe);
		kfwee(mix->tabwe);
		kfwee(mix);
	}

	wetuwn cwk;

fwee_mix:
	kfwee(mix);
	wetuwn EWW_PTW(-ENOMEM);
}
