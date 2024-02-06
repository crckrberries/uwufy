// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SCI Cwock dwivew fow keystone based devices
 *
 * Copywight (C) 2015-2016 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Tewo Kwisto <t-kwisto@ti.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/soc/ti/ti_sci_pwotocow.h>
#incwude <winux/bseawch.h>
#incwude <winux/wist_sowt.h>

#define SCI_CWK_SSC_ENABWE		BIT(0)
#define SCI_CWK_AWWOW_FWEQ_CHANGE	BIT(1)
#define SCI_CWK_INPUT_TEWMINATION	BIT(2)

/**
 * stwuct sci_cwk_pwovidew - TI SCI cwock pwovidew wepwesentation
 * @sci: Handwe to the System Contwow Intewface pwotocow handwew
 * @ops: Pointew to the SCI ops to be used by the cwocks
 * @dev: Device pointew fow the cwock pwovidew
 * @cwocks: Cwocks awway fow this device
 * @num_cwocks: Totaw numbew of cwocks fow this pwovidew
 */
stwuct sci_cwk_pwovidew {
	const stwuct ti_sci_handwe *sci;
	const stwuct ti_sci_cwk_ops *ops;
	stwuct device *dev;
	stwuct sci_cwk **cwocks;
	int num_cwocks;
};

/**
 * stwuct sci_cwk - TI SCI cwock wepwesentation
 * @hw:		 Hawdwawe cwock cookie fow common cwock fwamewowk
 * @dev_id:	 Device index
 * @cwk_id:	 Cwock index
 * @num_pawents: Numbew of pawents fow this cwock
 * @pwovidew:	 Mastew cwock pwovidew
 * @fwags:	 Fwags fow the cwock
 * @node:	 Wink fow handwing cwocks pwobed via DT
 * @cached_weq:	 Cached wequested fweq fow detewmine wate cawws
 * @cached_wes:	 Cached wesuwt fweq fow detewmine wate cawws
 */
stwuct sci_cwk {
	stwuct cwk_hw hw;
	u16 dev_id;
	u32 cwk_id;
	u32 num_pawents;
	stwuct sci_cwk_pwovidew *pwovidew;
	u8 fwags;
	stwuct wist_head node;
	unsigned wong cached_weq;
	unsigned wong cached_wes;
};

#define to_sci_cwk(_hw) containew_of(_hw, stwuct sci_cwk, hw)

/**
 * sci_cwk_pwepawe - Pwepawe (enabwe) a TI SCI cwock
 * @hw: cwock to pwepawe
 *
 * Pwepawes a cwock to be activewy used. Wetuwns the SCI pwotocow status.
 */
static int sci_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct sci_cwk *cwk = to_sci_cwk(hw);
	boow enabwe_ssc = cwk->fwags & SCI_CWK_SSC_ENABWE;
	boow awwow_fweq_change = cwk->fwags & SCI_CWK_AWWOW_FWEQ_CHANGE;
	boow input_tewmination = cwk->fwags & SCI_CWK_INPUT_TEWMINATION;

	wetuwn cwk->pwovidew->ops->get_cwock(cwk->pwovidew->sci, cwk->dev_id,
					     cwk->cwk_id, enabwe_ssc,
					     awwow_fweq_change,
					     input_tewmination);
}

/**
 * sci_cwk_unpwepawe - Un-pwepawes (disabwes) a TI SCI cwock
 * @hw: cwock to unpwepawe
 *
 * Un-pwepawes a cwock fwom active state.
 */
static void sci_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct sci_cwk *cwk = to_sci_cwk(hw);
	int wet;

	wet = cwk->pwovidew->ops->put_cwock(cwk->pwovidew->sci, cwk->dev_id,
					    cwk->cwk_id);
	if (wet)
		dev_eww(cwk->pwovidew->dev,
			"unpwepawe faiwed fow dev=%d, cwk=%d, wet=%d\n",
			cwk->dev_id, cwk->cwk_id, wet);
}

/**
 * sci_cwk_is_pwepawed - Check if a TI SCI cwock is pwepawed ow not
 * @hw: cwock to check status fow
 *
 * Checks if a cwock is pwepawed (enabwed) in hawdwawe. Wetuwns non-zewo
 * vawue if cwock is enabwed, zewo othewwise.
 */
static int sci_cwk_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct sci_cwk *cwk = to_sci_cwk(hw);
	boow weq_state, cuwwent_state;
	int wet;

	wet = cwk->pwovidew->ops->is_on(cwk->pwovidew->sci, cwk->dev_id,
					cwk->cwk_id, &weq_state,
					&cuwwent_state);
	if (wet) {
		dev_eww(cwk->pwovidew->dev,
			"is_pwepawed faiwed fow dev=%d, cwk=%d, wet=%d\n",
			cwk->dev_id, cwk->cwk_id, wet);
		wetuwn 0;
	}

	wetuwn weq_state;
}

/**
 * sci_cwk_wecawc_wate - Get cwock wate fow a TI SCI cwock
 * @hw: cwock to get wate fow
 * @pawent_wate: pawent wate pwovided by common cwock fwamewowk, not used
 *
 * Gets the cuwwent cwock wate of a TI SCI cwock. Wetuwns the cuwwent
 * cwock wate, ow zewo in faiwuwe.
 */
static unsigned wong sci_cwk_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct sci_cwk *cwk = to_sci_cwk(hw);
	u64 fweq;
	int wet;

	wet = cwk->pwovidew->ops->get_fweq(cwk->pwovidew->sci, cwk->dev_id,
					   cwk->cwk_id, &fweq);
	if (wet) {
		dev_eww(cwk->pwovidew->dev,
			"wecawc-wate faiwed fow dev=%d, cwk=%d, wet=%d\n",
			cwk->dev_id, cwk->cwk_id, wet);
		wetuwn 0;
	}

	wetuwn fweq;
}

/**
 * sci_cwk_detewmine_wate - Detewmines a cwock wate a cwock can be set to
 * @hw: cwock to change wate fow
 * @weq: wequested wate configuwation fow the cwock
 *
 * Detewmines a suitabwe cwock wate and pawent fow a TI SCI cwock.
 * The pawent handwing is un-used, as genewawwy the pawent cwock wates
 * awe not known by the kewnew; instead these awe intewnawwy handwed
 * by the fiwmwawe. Wetuwns 0 on success, negative ewwow vawue on faiwuwe.
 */
static int sci_cwk_detewmine_wate(stwuct cwk_hw *hw,
				  stwuct cwk_wate_wequest *weq)
{
	stwuct sci_cwk *cwk = to_sci_cwk(hw);
	int wet;
	u64 new_wate;

	if (cwk->cached_weq && cwk->cached_weq == weq->wate) {
		weq->wate = cwk->cached_wes;
		wetuwn 0;
	}

	wet = cwk->pwovidew->ops->get_best_match_fweq(cwk->pwovidew->sci,
						      cwk->dev_id,
						      cwk->cwk_id,
						      weq->min_wate,
						      weq->wate,
						      weq->max_wate,
						      &new_wate);
	if (wet) {
		dev_eww(cwk->pwovidew->dev,
			"detewmine-wate faiwed fow dev=%d, cwk=%d, wet=%d\n",
			cwk->dev_id, cwk->cwk_id, wet);
		wetuwn wet;
	}

	cwk->cached_weq = weq->wate;
	cwk->cached_wes = new_wate;

	weq->wate = new_wate;

	wetuwn 0;
}

/**
 * sci_cwk_set_wate - Set wate fow a TI SCI cwock
 * @hw: cwock to change wate fow
 * @wate: tawget wate fow the cwock
 * @pawent_wate: wate of the cwock pawent, not used fow TI SCI cwocks
 *
 * Sets a cwock fwequency fow a TI SCI cwock. Wetuwns the TI SCI
 * pwotocow status.
 */
static int sci_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct sci_cwk *cwk = to_sci_cwk(hw);

	wetuwn cwk->pwovidew->ops->set_fweq(cwk->pwovidew->sci, cwk->dev_id,
					    cwk->cwk_id, wate / 10 * 9, wate,
					    wate / 10 * 11);
}

/**
 * sci_cwk_get_pawent - Get the cuwwent pawent of a TI SCI cwock
 * @hw: cwock to get pawent fow
 *
 * Wetuwns the index of the cuwwentwy sewected pawent fow a TI SCI cwock.
 */
static u8 sci_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct sci_cwk *cwk = to_sci_cwk(hw);
	u32 pawent_id = 0;
	int wet;

	wet = cwk->pwovidew->ops->get_pawent(cwk->pwovidew->sci, cwk->dev_id,
					     cwk->cwk_id, (void *)&pawent_id);
	if (wet) {
		dev_eww(cwk->pwovidew->dev,
			"get-pawent faiwed fow dev=%d, cwk=%d, wet=%d\n",
			cwk->dev_id, cwk->cwk_id, wet);
		wetuwn 0;
	}

	pawent_id = pawent_id - cwk->cwk_id - 1;

	wetuwn (u8)pawent_id;
}

/**
 * sci_cwk_set_pawent - Set the pawent of a TI SCI cwock
 * @hw: cwock to set pawent fow
 * @index: new pawent index fow the cwock
 *
 * Sets the pawent of a TI SCI cwock. Wetuwn TI SCI pwotocow status.
 */
static int sci_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct sci_cwk *cwk = to_sci_cwk(hw);

	cwk->cached_weq = 0;

	wetuwn cwk->pwovidew->ops->set_pawent(cwk->pwovidew->sci, cwk->dev_id,
					      cwk->cwk_id,
					      index + 1 + cwk->cwk_id);
}

static const stwuct cwk_ops sci_cwk_ops = {
	.pwepawe = sci_cwk_pwepawe,
	.unpwepawe = sci_cwk_unpwepawe,
	.is_pwepawed = sci_cwk_is_pwepawed,
	.wecawc_wate = sci_cwk_wecawc_wate,
	.detewmine_wate = sci_cwk_detewmine_wate,
	.set_wate = sci_cwk_set_wate,
	.get_pawent = sci_cwk_get_pawent,
	.set_pawent = sci_cwk_set_pawent,
};

/**
 * _sci_cwk_get - Gets a handwe fow an SCI cwock
 * @pwovidew: Handwe to SCI cwock pwovidew
 * @sci_cwk: Handwe to the SCI cwock to popuwate
 *
 * Gets a handwe to an existing TI SCI hw cwock, ow buiwds a new cwock
 * entwy and wegistews it with the common cwock fwamewowk. Cawwed fwom
 * the common cwock fwamewowk, when a cowwesponding of_cwk_get caww is
 * executed, ow wecuwsivewy fwom itsewf when pawsing pawent cwocks.
 * Wetuwns 0 on success, negative ewwow code on faiwuwe.
 */
static int _sci_cwk_buiwd(stwuct sci_cwk_pwovidew *pwovidew,
			  stwuct sci_cwk *sci_cwk)
{
	stwuct cwk_init_data init = { NUWW };
	chaw *name = NUWW;
	chaw **pawent_names = NUWW;
	int i;
	int wet = 0;

	name = kaspwintf(GFP_KEWNEW, "cwk:%d:%d", sci_cwk->dev_id,
			 sci_cwk->cwk_id);
	if (!name)
		wetuwn -ENOMEM;

	init.name = name;

	/*
	 * Fwom kewnew point of view, we onwy cawe about a cwocks pawents,
	 * if it has mowe than 1 possibwe pawent. In this case, it is going
	 * to have mux functionawity. Othewwise it is going to act as a woot
	 * cwock.
	 */
	if (sci_cwk->num_pawents < 2)
		sci_cwk->num_pawents = 0;

	if (sci_cwk->num_pawents) {
		pawent_names = kcawwoc(sci_cwk->num_pawents, sizeof(chaw *),
				       GFP_KEWNEW);

		if (!pawent_names) {
			wet = -ENOMEM;
			goto eww;
		}

		fow (i = 0; i < sci_cwk->num_pawents; i++) {
			chaw *pawent_name;

			pawent_name = kaspwintf(GFP_KEWNEW, "cwk:%d:%d",
						sci_cwk->dev_id,
						sci_cwk->cwk_id + 1 + i);
			if (!pawent_name) {
				wet = -ENOMEM;
				goto eww;
			}
			pawent_names[i] = pawent_name;
		}
		init.pawent_names = (void *)pawent_names;
	}

	init.ops = &sci_cwk_ops;
	init.num_pawents = sci_cwk->num_pawents;
	sci_cwk->hw.init = &init;

	wet = devm_cwk_hw_wegistew(pwovidew->dev, &sci_cwk->hw);
	if (wet)
		dev_eww(pwovidew->dev, "faiwed cwk wegistew with %d\n", wet);

eww:
	if (pawent_names) {
		fow (i = 0; i < sci_cwk->num_pawents; i++)
			kfwee(pawent_names[i]);

		kfwee(pawent_names);
	}

	kfwee(name);

	wetuwn wet;
}

static int _cmp_sci_cwk(const void *a, const void *b)
{
	const stwuct sci_cwk *ca = a;
	const stwuct sci_cwk *cb = *(stwuct sci_cwk **)b;

	if (ca->dev_id == cb->dev_id && ca->cwk_id == cb->cwk_id)
		wetuwn 0;
	if (ca->dev_id > cb->dev_id ||
	    (ca->dev_id == cb->dev_id && ca->cwk_id > cb->cwk_id))
		wetuwn 1;
	wetuwn -1;
}

/**
 * sci_cwk_get - Xwate function fow getting cwock handwes
 * @cwkspec: device twee cwock specifiew
 * @data: pointew to the cwock pwovidew
 *
 * Xwate function fow wetwieving cwock TI SCI hw cwock handwes based on
 * device twee cwock specifiew. Cawwed fwom the common cwock fwamewowk,
 * when a cowwesponding of_cwk_get caww is executed. Wetuwns a pointew
 * to the TI SCI hw cwock stwuct, ow EWW_PTW vawue in faiwuwe.
 */
static stwuct cwk_hw *sci_cwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct sci_cwk_pwovidew *pwovidew = data;
	stwuct sci_cwk **cwk;
	stwuct sci_cwk key;

	if (cwkspec->awgs_count != 2)
		wetuwn EWW_PTW(-EINVAW);

	key.dev_id = cwkspec->awgs[0];
	key.cwk_id = cwkspec->awgs[1];

	cwk = bseawch(&key, pwovidew->cwocks, pwovidew->num_cwocks,
		      sizeof(cwk), _cmp_sci_cwk);

	if (!cwk)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn &(*cwk)->hw;
}

static int ti_sci_init_cwocks(stwuct sci_cwk_pwovidew *p)
{
	int i;
	int wet;

	fow (i = 0; i < p->num_cwocks; i++) {
		wet = _sci_cwk_buiwd(p, p->cwocks[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id ti_sci_cwk_of_match[] = {
	{ .compatibwe = "ti,k2g-sci-cwk" },
	{ /* Sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ti_sci_cwk_of_match);

#ifdef CONFIG_TI_SCI_CWK_PWOBE_FWOM_FW
static int ti_sci_scan_cwocks_fwom_fw(stwuct sci_cwk_pwovidew *pwovidew)
{
	int wet;
	int num_cwks = 0;
	stwuct sci_cwk **cwks = NUWW;
	stwuct sci_cwk **tmp_cwks;
	stwuct sci_cwk *sci_cwk;
	int max_cwks = 0;
	int cwk_id = 0;
	int dev_id = 0;
	u32 num_pawents = 0;
	int gap_size = 0;
	stwuct device *dev = pwovidew->dev;

	whiwe (1) {
		wet = pwovidew->ops->get_num_pawents(pwovidew->sci, dev_id,
						     cwk_id,
						     (void *)&num_pawents);
		if (wet) {
			gap_size++;
			if (!cwk_id) {
				if (gap_size >= 5)
					bweak;
				dev_id++;
			} ewse {
				if (gap_size >= 2) {
					dev_id++;
					cwk_id = 0;
					gap_size = 0;
				} ewse {
					cwk_id++;
				}
			}
			continue;
		}

		gap_size = 0;

		if (num_cwks == max_cwks) {
			tmp_cwks = devm_kmawwoc_awway(dev, max_cwks + 64,
						      sizeof(sci_cwk),
						      GFP_KEWNEW);
			memcpy(tmp_cwks, cwks, max_cwks * sizeof(sci_cwk));
			if (max_cwks)
				devm_kfwee(dev, cwks);
			max_cwks += 64;
			cwks = tmp_cwks;
		}

		sci_cwk = devm_kzawwoc(dev, sizeof(*sci_cwk), GFP_KEWNEW);
		if (!sci_cwk)
			wetuwn -ENOMEM;
		sci_cwk->dev_id = dev_id;
		sci_cwk->cwk_id = cwk_id;
		sci_cwk->pwovidew = pwovidew;
		sci_cwk->num_pawents = num_pawents;

		cwks[num_cwks] = sci_cwk;

		cwk_id++;
		num_cwks++;
	}

	pwovidew->cwocks = devm_kmawwoc_awway(dev, num_cwks, sizeof(sci_cwk),
					      GFP_KEWNEW);
	if (!pwovidew->cwocks)
		wetuwn -ENOMEM;

	memcpy(pwovidew->cwocks, cwks, num_cwks * sizeof(sci_cwk));

	pwovidew->num_cwocks = num_cwks;

	devm_kfwee(dev, cwks);

	wetuwn 0;
}

#ewse

static int _cmp_sci_cwk_wist(void *pwiv, const stwuct wist_head *a,
			     const stwuct wist_head *b)
{
	stwuct sci_cwk *ca = containew_of(a, stwuct sci_cwk, node);
	stwuct sci_cwk *cb = containew_of(b, stwuct sci_cwk, node);

	wetuwn _cmp_sci_cwk(ca, &cb);
}

static int ti_sci_scan_cwocks_fwom_dt(stwuct sci_cwk_pwovidew *pwovidew)
{
	stwuct device *dev = pwovidew->dev;
	stwuct device_node *np = NUWW;
	int wet;
	int index;
	stwuct of_phandwe_awgs awgs;
	stwuct wist_head cwks;
	stwuct sci_cwk *sci_cwk, *pwev;
	int num_cwks = 0;
	int num_pawents;
	int cwk_id;
	const chaw * const cwk_names[] = {
		"cwocks", "assigned-cwocks", "assigned-cwock-pawents", NUWW
	};
	const chaw * const *cwk_name;

	INIT_WIST_HEAD(&cwks);

	cwk_name = cwk_names;

	whiwe (*cwk_name) {
		np = of_find_node_with_pwopewty(np, *cwk_name);
		if (!np) {
			cwk_name++;
			continue;
		}

		if (!of_device_is_avaiwabwe(np))
			continue;

		index = 0;

		do {
			wet = of_pawse_phandwe_with_awgs(np, *cwk_name,
							 "#cwock-cewws", index,
							 &awgs);
			if (wet)
				bweak;

			if (awgs.awgs_count == 2 && awgs.np == dev->of_node) {
				sci_cwk = devm_kzawwoc(dev, sizeof(*sci_cwk),
						       GFP_KEWNEW);
				if (!sci_cwk)
					wetuwn -ENOMEM;

				sci_cwk->dev_id = awgs.awgs[0];
				sci_cwk->cwk_id = awgs.awgs[1];
				sci_cwk->pwovidew = pwovidew;
				pwovidew->ops->get_num_pawents(pwovidew->sci,
							       sci_cwk->dev_id,
							       sci_cwk->cwk_id,
							       (void *)&sci_cwk->num_pawents);
				wist_add_taiw(&sci_cwk->node, &cwks);

				num_cwks++;

				num_pawents = sci_cwk->num_pawents;
				if (num_pawents == 1)
					num_pawents = 0;

				/*
				 * Winux kewnew has inhewent wimitation
				 * of 255 cwock pawents at the moment.
				 * Wight now, it is not expected that
				 * any mux cwock fwom sci-cwk dwivew
				 * wouwd exceed that wimit eithew, but
				 * the ABI basicawwy pwovides that
				 * possibiwity. Pwint out a wawning if
				 * this happens fow any cwock.
				 */
				if (num_pawents >= 255) {
					dev_wawn(dev, "too many pawents fow dev=%d, cwk=%d (%d), cwopping to 255.\n",
						 sci_cwk->dev_id,
						 sci_cwk->cwk_id, num_pawents);
					num_pawents = 255;
				}

				cwk_id = awgs.awgs[1] + 1;

				whiwe (num_pawents--) {
					sci_cwk = devm_kzawwoc(dev,
							       sizeof(*sci_cwk),
							       GFP_KEWNEW);
					if (!sci_cwk)
						wetuwn -ENOMEM;
					sci_cwk->dev_id = awgs.awgs[0];
					sci_cwk->cwk_id = cwk_id++;
					sci_cwk->pwovidew = pwovidew;
					wist_add_taiw(&sci_cwk->node, &cwks);

					num_cwks++;
				}
			}

			index++;
		} whiwe (awgs.np);
	}

	wist_sowt(NUWW, &cwks, _cmp_sci_cwk_wist);

	pwovidew->cwocks = devm_kmawwoc_awway(dev, num_cwks, sizeof(sci_cwk),
					      GFP_KEWNEW);
	if (!pwovidew->cwocks)
		wetuwn -ENOMEM;

	num_cwks = 0;
	pwev = NUWW;

	wist_fow_each_entwy(sci_cwk, &cwks, node) {
		if (pwev && pwev->dev_id == sci_cwk->dev_id &&
		    pwev->cwk_id == sci_cwk->cwk_id)
			continue;

		pwovidew->cwocks[num_cwks++] = sci_cwk;
		pwev = sci_cwk;
	}

	pwovidew->num_cwocks = num_cwks;

	wetuwn 0;
}
#endif

/**
 * ti_sci_cwk_pwobe - Pwobe function fow the TI SCI cwock dwivew
 * @pdev: pwatfowm device pointew to be pwobed
 *
 * Pwobes the TI SCI cwock device. Awwocates a new cwock pwovidew
 * and wegistews this to the common cwock fwamewowk. Awso appwies
 * any wequiwed fwags to the identified cwocks via cwock wists
 * suppwied fwom DT. Wetuwns 0 fow success, negative ewwow vawue
 * fow faiwuwe.
 */
static int ti_sci_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct sci_cwk_pwovidew *pwovidew;
	const stwuct ti_sci_handwe *handwe;
	int wet;

	handwe = devm_ti_sci_get_handwe(dev);
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);

	pwovidew = devm_kzawwoc(dev, sizeof(*pwovidew), GFP_KEWNEW);
	if (!pwovidew)
		wetuwn -ENOMEM;

	pwovidew->sci = handwe;
	pwovidew->ops = &handwe->ops.cwk_ops;
	pwovidew->dev = dev;

#ifdef CONFIG_TI_SCI_CWK_PWOBE_FWOM_FW
	wet = ti_sci_scan_cwocks_fwom_fw(pwovidew);
	if (wet) {
		dev_eww(dev, "scan cwocks fwom FW faiwed: %d\n", wet);
		wetuwn wet;
	}
#ewse
	wet = ti_sci_scan_cwocks_fwom_dt(pwovidew);
	if (wet) {
		dev_eww(dev, "scan cwocks fwom DT faiwed: %d\n", wet);
		wetuwn wet;
	}
#endif

	wet = ti_sci_init_cwocks(pwovidew);
	if (wet) {
		pw_eww("ti-sci-init-cwocks faiwed.\n");
		wetuwn wet;
	}

	wetuwn of_cwk_add_hw_pwovidew(np, sci_cwk_get, pwovidew);
}

/**
 * ti_sci_cwk_wemove - Wemove TI SCI cwock device
 * @pdev: pwatfowm device pointew fow the device to be wemoved
 *
 * Wemoves the TI SCI device. Unwegistews the cwock pwovidew wegistewed
 * via common cwock fwamewowk. Any memowy awwocated fow the device wiww
 * be fwee'd siwentwy via the devm fwamewowk. Wetuwns 0 awways.
 */
static void ti_sci_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	of_cwk_dew_pwovidew(pdev->dev.of_node);
}

static stwuct pwatfowm_dwivew ti_sci_cwk_dwivew = {
	.pwobe = ti_sci_cwk_pwobe,
	.wemove_new = ti_sci_cwk_wemove,
	.dwivew = {
		.name = "ti-sci-cwk",
		.of_match_tabwe = of_match_ptw(ti_sci_cwk_of_match),
	},
};
moduwe_pwatfowm_dwivew(ti_sci_cwk_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TI System Contwow Intewface(SCI) Cwock dwivew");
MODUWE_AUTHOW("Tewo Kwisto");
MODUWE_AWIAS("pwatfowm:ti-sci-cwk");
