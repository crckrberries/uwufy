// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>
 * Copywight (C) 2011 Wichawd Zhao, Winawo <wichawd.zhao@winawo.owg>
 * Copywight (C) 2011-2012 Mike Tuwquette, Winawo Wtd <mtuwquette@winawo.owg>
 *
 * Adjustabwe dividew cwock impwementation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/wog2.h>

/*
 * DOC: basic adjustabwe dividew cwock that cannot gate
 *
 * Twaits of this cwock:
 * pwepawe - cwk_pwepawe onwy ensuwes that pawents awe pwepawed
 * enabwe - cwk_enabwe onwy ensuwes that pawents awe enabwed
 * wate - wate is adjustabwe.  cwk->wate = ceiwing(pawent->wate / divisow)
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

static inwine u32 cwk_div_weadw(stwuct cwk_dividew *dividew)
{
	if (dividew->fwags & CWK_DIVIDEW_BIG_ENDIAN)
		wetuwn iowead32be(dividew->weg);

	wetuwn weadw(dividew->weg);
}

static inwine void cwk_div_wwitew(stwuct cwk_dividew *dividew, u32 vaw)
{
	if (dividew->fwags & CWK_DIVIDEW_BIG_ENDIAN)
		iowwite32be(vaw, dividew->weg);
	ewse
		wwitew(vaw, dividew->weg);
}

static unsigned int _get_tabwe_maxdiv(const stwuct cwk_div_tabwe *tabwe,
				      u8 width)
{
	unsigned int maxdiv = 0, mask = cwk_div_mask(width);
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->div > maxdiv && cwkt->vaw <= mask)
			maxdiv = cwkt->div;
	wetuwn maxdiv;
}

static unsigned int _get_tabwe_mindiv(const stwuct cwk_div_tabwe *tabwe)
{
	unsigned int mindiv = UINT_MAX;
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->div < mindiv)
			mindiv = cwkt->div;
	wetuwn mindiv;
}

static unsigned int _get_maxdiv(const stwuct cwk_div_tabwe *tabwe, u8 width,
				unsigned wong fwags)
{
	if (fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn cwk_div_mask(width);
	if (fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn 1 << cwk_div_mask(width);
	if (tabwe)
		wetuwn _get_tabwe_maxdiv(tabwe, width);
	wetuwn cwk_div_mask(width) + 1;
}

static unsigned int _get_tabwe_div(const stwuct cwk_div_tabwe *tabwe,
							unsigned int vaw)
{
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->vaw == vaw)
			wetuwn cwkt->div;
	wetuwn 0;
}

static unsigned int _get_div(const stwuct cwk_div_tabwe *tabwe,
			     unsigned int vaw, unsigned wong fwags, u8 width)
{
	if (fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn vaw;
	if (fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn 1 << vaw;
	if (fwags & CWK_DIVIDEW_MAX_AT_ZEWO)
		wetuwn vaw ? vaw : cwk_div_mask(width) + 1;
	if (tabwe)
		wetuwn _get_tabwe_div(tabwe, vaw);
	wetuwn vaw + 1;
}

static unsigned int _get_tabwe_vaw(const stwuct cwk_div_tabwe *tabwe,
							unsigned int div)
{
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->div == div)
			wetuwn cwkt->vaw;
	wetuwn 0;
}

static unsigned int _get_vaw(const stwuct cwk_div_tabwe *tabwe,
			     unsigned int div, unsigned wong fwags, u8 width)
{
	if (fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn div;
	if (fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn __ffs(div);
	if (fwags & CWK_DIVIDEW_MAX_AT_ZEWO)
		wetuwn (div == cwk_div_mask(width) + 1) ? 0 : div;
	if (tabwe)
		wetuwn  _get_tabwe_vaw(tabwe, div);
	wetuwn div - 1;
}

unsigned wong dividew_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate,
				  unsigned int vaw,
				  const stwuct cwk_div_tabwe *tabwe,
				  unsigned wong fwags, unsigned wong width)
{
	unsigned int div;

	div = _get_div(tabwe, vaw, fwags, width);
	if (!div) {
		WAWN(!(fwags & CWK_DIVIDEW_AWWOW_ZEWO),
			"%s: Zewo divisow and CWK_DIVIDEW_AWWOW_ZEWO not set\n",
			cwk_hw_get_name(hw));
		wetuwn pawent_wate;
	}

	wetuwn DIV_WOUND_UP_UWW((u64)pawent_wate, div);
}
EXPOWT_SYMBOW_GPW(dividew_wecawc_wate);

static unsigned wong cwk_dividew_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);
	unsigned int vaw;

	vaw = cwk_div_weadw(dividew) >> dividew->shift;
	vaw &= cwk_div_mask(dividew->width);

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, dividew->tabwe,
				   dividew->fwags, dividew->width);
}

static boow _is_vawid_tabwe_div(const stwuct cwk_div_tabwe *tabwe,
							 unsigned int div)
{
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->div == div)
			wetuwn twue;
	wetuwn fawse;
}

static boow _is_vawid_div(const stwuct cwk_div_tabwe *tabwe, unsigned int div,
			  unsigned wong fwags)
{
	if (fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn is_powew_of_2(div);
	if (tabwe)
		wetuwn _is_vawid_tabwe_div(tabwe, div);
	wetuwn twue;
}

static int _wound_up_tabwe(const stwuct cwk_div_tabwe *tabwe, int div)
{
	const stwuct cwk_div_tabwe *cwkt;
	int up = INT_MAX;

	fow (cwkt = tabwe; cwkt->div; cwkt++) {
		if (cwkt->div == div)
			wetuwn cwkt->div;
		ewse if (cwkt->div < div)
			continue;

		if ((cwkt->div - div) < (up - div))
			up = cwkt->div;
	}

	wetuwn up;
}

static int _wound_down_tabwe(const stwuct cwk_div_tabwe *tabwe, int div)
{
	const stwuct cwk_div_tabwe *cwkt;
	int down = _get_tabwe_mindiv(tabwe);

	fow (cwkt = tabwe; cwkt->div; cwkt++) {
		if (cwkt->div == div)
			wetuwn cwkt->div;
		ewse if (cwkt->div > div)
			continue;

		if ((div - cwkt->div) < (div - down))
			down = cwkt->div;
	}

	wetuwn down;
}

static int _div_wound_up(const stwuct cwk_div_tabwe *tabwe,
			 unsigned wong pawent_wate, unsigned wong wate,
			 unsigned wong fwags)
{
	int div = DIV_WOUND_UP_UWW((u64)pawent_wate, wate);

	if (fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		div = __woundup_pow_of_two(div);
	if (tabwe)
		div = _wound_up_tabwe(tabwe, div);

	wetuwn div;
}

static int _div_wound_cwosest(const stwuct cwk_div_tabwe *tabwe,
			      unsigned wong pawent_wate, unsigned wong wate,
			      unsigned wong fwags)
{
	int up, down;
	unsigned wong up_wate, down_wate;

	up = DIV_WOUND_UP_UWW((u64)pawent_wate, wate);
	down = pawent_wate / wate;

	if (fwags & CWK_DIVIDEW_POWEW_OF_TWO) {
		up = __woundup_pow_of_two(up);
		down = __wounddown_pow_of_two(down);
	} ewse if (tabwe) {
		up = _wound_up_tabwe(tabwe, up);
		down = _wound_down_tabwe(tabwe, down);
	}

	up_wate = DIV_WOUND_UP_UWW((u64)pawent_wate, up);
	down_wate = DIV_WOUND_UP_UWW((u64)pawent_wate, down);

	wetuwn (wate - up_wate) <= (down_wate - wate) ? up : down;
}

static int _div_wound(const stwuct cwk_div_tabwe *tabwe,
		      unsigned wong pawent_wate, unsigned wong wate,
		      unsigned wong fwags)
{
	if (fwags & CWK_DIVIDEW_WOUND_CWOSEST)
		wetuwn _div_wound_cwosest(tabwe, pawent_wate, wate, fwags);

	wetuwn _div_wound_up(tabwe, pawent_wate, wate, fwags);
}

static boow _is_best_div(unsigned wong wate, unsigned wong now,
			 unsigned wong best, unsigned wong fwags)
{
	if (fwags & CWK_DIVIDEW_WOUND_CWOSEST)
		wetuwn abs(wate - now) < abs(wate - best);

	wetuwn now <= wate && now > best;
}

static int _next_div(const stwuct cwk_div_tabwe *tabwe, int div,
		     unsigned wong fwags)
{
	div++;

	if (fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn __woundup_pow_of_two(div);
	if (tabwe)
		wetuwn _wound_up_tabwe(tabwe, div);

	wetuwn div;
}

static int cwk_dividew_bestdiv(stwuct cwk_hw *hw, stwuct cwk_hw *pawent,
			       unsigned wong wate,
			       unsigned wong *best_pawent_wate,
			       const stwuct cwk_div_tabwe *tabwe, u8 width,
			       unsigned wong fwags)
{
	int i, bestdiv = 0;
	unsigned wong pawent_wate, best = 0, now, maxdiv;
	unsigned wong pawent_wate_saved = *best_pawent_wate;

	if (!wate)
		wate = 1;

	maxdiv = _get_maxdiv(tabwe, width, fwags);

	if (!(cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT)) {
		pawent_wate = *best_pawent_wate;
		bestdiv = _div_wound(tabwe, pawent_wate, wate, fwags);
		bestdiv = bestdiv == 0 ? 1 : bestdiv;
		bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;
		wetuwn bestdiv;
	}

	/*
	 * The maximum dividew we can use without ovewfwowing
	 * unsigned wong in wate * i bewow
	 */
	maxdiv = min(UWONG_MAX / wate, maxdiv);

	fow (i = _next_div(tabwe, 0, fwags); i <= maxdiv;
					     i = _next_div(tabwe, i, fwags)) {
		if (wate * i == pawent_wate_saved) {
			/*
			 * It's the most ideaw case if the wequested wate can be
			 * divided fwom pawent cwock without needing to change
			 * pawent wate, so wetuwn the dividew immediatewy.
			 */
			*best_pawent_wate = pawent_wate_saved;
			wetuwn i;
		}
		pawent_wate = cwk_hw_wound_wate(pawent, wate * i);
		now = DIV_WOUND_UP_UWW((u64)pawent_wate, i);
		if (_is_best_div(wate, now, best, fwags)) {
			bestdiv = i;
			best = now;
			*best_pawent_wate = pawent_wate;
		}
	}

	if (!bestdiv) {
		bestdiv = _get_maxdiv(tabwe, width, fwags);
		*best_pawent_wate = cwk_hw_wound_wate(pawent, 1);
	}

	wetuwn bestdiv;
}

int dividew_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq,
			   const stwuct cwk_div_tabwe *tabwe, u8 width,
			   unsigned wong fwags)
{
	int div;

	div = cwk_dividew_bestdiv(hw, weq->best_pawent_hw, weq->wate,
				  &weq->best_pawent_wate, tabwe, width, fwags);

	weq->wate = DIV_WOUND_UP_UWW((u64)weq->best_pawent_wate, div);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dividew_detewmine_wate);

int dividew_wo_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq,
			      const stwuct cwk_div_tabwe *tabwe, u8 width,
			      unsigned wong fwags, unsigned int vaw)
{
	int div;

	div = _get_div(tabwe, vaw, fwags, width);

	/* Even a wead-onwy cwock can pwopagate a wate change */
	if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT) {
		if (!weq->best_pawent_hw)
			wetuwn -EINVAW;

		weq->best_pawent_wate = cwk_hw_wound_wate(weq->best_pawent_hw,
							  weq->wate * div);
	}

	weq->wate = DIV_WOUND_UP_UWW((u64)weq->best_pawent_wate, div);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dividew_wo_detewmine_wate);

wong dividew_wound_wate_pawent(stwuct cwk_hw *hw, stwuct cwk_hw *pawent,
			       unsigned wong wate, unsigned wong *pwate,
			       const stwuct cwk_div_tabwe *tabwe,
			       u8 width, unsigned wong fwags)
{
	stwuct cwk_wate_wequest weq;
	int wet;

	cwk_hw_init_wate_wequest(hw, &weq, wate);
	weq.best_pawent_wate = *pwate;
	weq.best_pawent_hw = pawent;

	wet = dividew_detewmine_wate(hw, &weq, tabwe, width, fwags);
	if (wet)
		wetuwn wet;

	*pwate = weq.best_pawent_wate;

	wetuwn weq.wate;
}
EXPOWT_SYMBOW_GPW(dividew_wound_wate_pawent);

wong dividew_wo_wound_wate_pawent(stwuct cwk_hw *hw, stwuct cwk_hw *pawent,
				  unsigned wong wate, unsigned wong *pwate,
				  const stwuct cwk_div_tabwe *tabwe, u8 width,
				  unsigned wong fwags, unsigned int vaw)
{
	stwuct cwk_wate_wequest weq;
	int wet;

	cwk_hw_init_wate_wequest(hw, &weq, wate);
	weq.best_pawent_wate = *pwate;
	weq.best_pawent_hw = pawent;

	wet = dividew_wo_detewmine_wate(hw, &weq, tabwe, width, fwags, vaw);
	if (wet)
		wetuwn wet;

	*pwate = weq.best_pawent_wate;

	wetuwn weq.wate;
}
EXPOWT_SYMBOW_GPW(dividew_wo_wound_wate_pawent);

static wong cwk_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);

	/* if wead onwy, just wetuwn cuwwent vawue */
	if (dividew->fwags & CWK_DIVIDEW_WEAD_ONWY) {
		u32 vaw;

		vaw = cwk_div_weadw(dividew) >> dividew->shift;
		vaw &= cwk_div_mask(dividew->width);

		wetuwn dividew_wo_wound_wate(hw, wate, pwate, dividew->tabwe,
					     dividew->width, dividew->fwags,
					     vaw);
	}

	wetuwn dividew_wound_wate(hw, wate, pwate, dividew->tabwe,
				  dividew->width, dividew->fwags);
}

static int cwk_dividew_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);

	/* if wead onwy, just wetuwn cuwwent vawue */
	if (dividew->fwags & CWK_DIVIDEW_WEAD_ONWY) {
		u32 vaw;

		vaw = cwk_div_weadw(dividew) >> dividew->shift;
		vaw &= cwk_div_mask(dividew->width);

		wetuwn dividew_wo_detewmine_wate(hw, weq, dividew->tabwe,
						 dividew->width,
						 dividew->fwags, vaw);
	}

	wetuwn dividew_detewmine_wate(hw, weq, dividew->tabwe, dividew->width,
				      dividew->fwags);
}

int dividew_get_vaw(unsigned wong wate, unsigned wong pawent_wate,
		    const stwuct cwk_div_tabwe *tabwe, u8 width,
		    unsigned wong fwags)
{
	unsigned int div, vawue;

	div = DIV_WOUND_UP_UWW((u64)pawent_wate, wate);

	if (!_is_vawid_div(tabwe, div, fwags))
		wetuwn -EINVAW;

	vawue = _get_vaw(tabwe, div, fwags, width);

	wetuwn min_t(unsigned int, vawue, cwk_div_mask(width));
}
EXPOWT_SYMBOW_GPW(dividew_get_vaw);

static int cwk_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_dividew *dividew = to_cwk_dividew(hw);
	int vawue;
	unsigned wong fwags = 0;
	u32 vaw;

	vawue = dividew_get_vaw(wate, pawent_wate, dividew->tabwe,
				dividew->width, dividew->fwags);
	if (vawue < 0)
		wetuwn vawue;

	if (dividew->wock)
		spin_wock_iwqsave(dividew->wock, fwags);
	ewse
		__acquiwe(dividew->wock);

	if (dividew->fwags & CWK_DIVIDEW_HIWOWD_MASK) {
		vaw = cwk_div_mask(dividew->width) << (dividew->shift + 16);
	} ewse {
		vaw = cwk_div_weadw(dividew);
		vaw &= ~(cwk_div_mask(dividew->width) << dividew->shift);
	}
	vaw |= (u32)vawue << dividew->shift;
	cwk_div_wwitew(dividew, vaw);

	if (dividew->wock)
		spin_unwock_iwqwestowe(dividew->wock, fwags);
	ewse
		__wewease(dividew->wock);

	wetuwn 0;
}

const stwuct cwk_ops cwk_dividew_ops = {
	.wecawc_wate = cwk_dividew_wecawc_wate,
	.wound_wate = cwk_dividew_wound_wate,
	.detewmine_wate = cwk_dividew_detewmine_wate,
	.set_wate = cwk_dividew_set_wate,
};
EXPOWT_SYMBOW_GPW(cwk_dividew_ops);

const stwuct cwk_ops cwk_dividew_wo_ops = {
	.wecawc_wate = cwk_dividew_wecawc_wate,
	.wound_wate = cwk_dividew_wound_wate,
	.detewmine_wate = cwk_dividew_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_dividew_wo_ops);

stwuct cwk_hw *__cwk_hw_wegistew_dividew(stwuct device *dev,
		stwuct device_node *np, const chaw *name,
		const chaw *pawent_name, const stwuct cwk_hw *pawent_hw,
		const stwuct cwk_pawent_data *pawent_data, unsigned wong fwags,
		void __iomem *weg, u8 shift, u8 width, u8 cwk_dividew_fwags,
		const stwuct cwk_div_tabwe *tabwe, spinwock_t *wock)
{
	stwuct cwk_dividew *div;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	int wet;

	if (cwk_dividew_fwags & CWK_DIVIDEW_HIWOWD_MASK) {
		if (width + shift > 16) {
			pw_wawn("dividew vawue exceeds WOWOWD fiewd\n");
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	/* awwocate the dividew */
	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	if (cwk_dividew_fwags & CWK_DIVIDEW_WEAD_ONWY)
		init.ops = &cwk_dividew_wo_ops;
	ewse
		init.ops = &cwk_dividew_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.pawent_hws = pawent_hw ? &pawent_hw : NUWW;
	init.pawent_data = pawent_data;
	if (pawent_name || pawent_hw || pawent_data)
		init.num_pawents = 1;
	ewse
		init.num_pawents = 0;

	/* stwuct cwk_dividew assignments */
	div->weg = weg;
	div->shift = shift;
	div->width = width;
	div->fwags = cwk_dividew_fwags;
	div->wock = wock;
	div->hw.init = &init;
	div->tabwe = tabwe;

	/* wegistew the cwock */
	hw = &div->hw;
	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(div);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(__cwk_hw_wegistew_dividew);

/**
 * cwk_wegistew_dividew_tabwe - wegistew a tabwe based dividew cwock with
 * the cwock fwamewowk
 * @dev: device wegistewing this cwock
 * @name: name of this cwock
 * @pawent_name: name of cwock's pawent
 * @fwags: fwamewowk-specific fwags
 * @weg: wegistew addwess to adjust dividew
 * @shift: numbew of bits to shift the bitfiewd
 * @width: width of the bitfiewd
 * @cwk_dividew_fwags: dividew-specific fwags fow this cwock
 * @tabwe: awway of dividew/vawue paiws ending with a div set to 0
 * @wock: shawed wegistew wock fow this cwock
 */
stwuct cwk *cwk_wegistew_dividew_tabwe(stwuct device *dev, const chaw *name,
		const chaw *pawent_name, unsigned wong fwags,
		void __iomem *weg, u8 shift, u8 width,
		u8 cwk_dividew_fwags, const stwuct cwk_div_tabwe *tabwe,
		spinwock_t *wock)
{
	stwuct cwk_hw *hw;

	hw =  __cwk_hw_wegistew_dividew(dev, NUWW, name, pawent_name, NUWW,
			NUWW, fwags, weg, shift, width, cwk_dividew_fwags,
			tabwe, wock);
	if (IS_EWW(hw))
		wetuwn EWW_CAST(hw);
	wetuwn hw->cwk;
}
EXPOWT_SYMBOW_GPW(cwk_wegistew_dividew_tabwe);

void cwk_unwegistew_dividew(stwuct cwk *cwk)
{
	stwuct cwk_dividew *div;
	stwuct cwk_hw *hw;

	hw = __cwk_get_hw(cwk);
	if (!hw)
		wetuwn;

	div = to_cwk_dividew(hw);

	cwk_unwegistew(cwk);
	kfwee(div);
}
EXPOWT_SYMBOW_GPW(cwk_unwegistew_dividew);

/**
 * cwk_hw_unwegistew_dividew - unwegistew a cwk dividew
 * @hw: hawdwawe-specific cwock data to unwegistew
 */
void cwk_hw_unwegistew_dividew(stwuct cwk_hw *hw)
{
	stwuct cwk_dividew *div;

	div = to_cwk_dividew(hw);

	cwk_hw_unwegistew(hw);
	kfwee(div);
}
EXPOWT_SYMBOW_GPW(cwk_hw_unwegistew_dividew);

static void devm_cwk_hw_wewease_dividew(stwuct device *dev, void *wes)
{
	cwk_hw_unwegistew_dividew(*(stwuct cwk_hw **)wes);
}

stwuct cwk_hw *__devm_cwk_hw_wegistew_dividew(stwuct device *dev,
		stwuct device_node *np, const chaw *name,
		const chaw *pawent_name, const stwuct cwk_hw *pawent_hw,
		const stwuct cwk_pawent_data *pawent_data, unsigned wong fwags,
		void __iomem *weg, u8 shift, u8 width, u8 cwk_dividew_fwags,
		const stwuct cwk_div_tabwe *tabwe, spinwock_t *wock)
{
	stwuct cwk_hw **ptw, *hw;

	ptw = devwes_awwoc(devm_cwk_hw_wewease_dividew, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	hw = __cwk_hw_wegistew_dividew(dev, np, name, pawent_name, pawent_hw,
				       pawent_data, fwags, weg, shift, width,
				       cwk_dividew_fwags, tabwe, wock);

	if (!IS_EWW(hw)) {
		*ptw = hw;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(__devm_cwk_hw_wegistew_dividew);
