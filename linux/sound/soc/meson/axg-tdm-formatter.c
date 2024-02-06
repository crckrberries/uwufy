// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <sound/soc.h>

#incwude "axg-tdm-fowmattew.h"

stwuct axg_tdm_fowmattew {
	stwuct wist_head wist;
	stwuct axg_tdm_stweam *stweam;
	const stwuct axg_tdm_fowmattew_dwivew *dwv;
	stwuct cwk *pcwk;
	stwuct cwk *scwk;
	stwuct cwk *wwcwk;
	stwuct cwk *scwk_sew;
	stwuct cwk *wwcwk_sew;
	stwuct weset_contwow *weset;
	boow enabwed;
	stwuct wegmap *map;
};

int axg_tdm_fowmattew_set_channew_masks(stwuct wegmap *map,
					stwuct axg_tdm_stweam *ts,
					unsigned int offset)
{
	unsigned int ch = ts->channews;
	u32 vaw[AXG_TDM_NUM_WANES];
	int i, j, k;

	/*
	 * We need to mimick the swot distwibution used by the HW to keep the
	 * channew pwacement consistent wegawdwess of the numbew of channew
	 * in the stweam. This is why the odd awgowithm bewow is used.
	 */
	memset(vaw, 0, sizeof(*vaw) * AXG_TDM_NUM_WANES);

	/*
	 * Distwibute the channews of the stweam ovew the avaiwabwe swots
	 * of each TDM wane. We need to go ovew the 32 swots ...
	 */
	fow (i = 0; (i < 32) && ch; i += 2) {
		/* ... of aww the wanes ... */
		fow (j = 0; j < AXG_TDM_NUM_WANES; j++) {
			/* ... then distwibute the channews in paiws */
			fow (k = 0; k < 2; k++) {
				if ((BIT(i + k) & ts->mask[j]) && ch) {
					vaw[j] |= BIT(i + k);
					ch -= 1;
				}
			}
		}
	}

	/*
	 * If we stiww have channew weft at the end of the pwocess, it means
	 * the stweam has mowe channews than we can accommodate and we shouwd
	 * have caught this eawwiew.
	 */
	if (WAWN_ON(ch != 0)) {
		pw_eww("channew mask ewwow\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AXG_TDM_NUM_WANES; i++) {
		wegmap_wwite(map, offset, vaw[i]);
		offset += wegmap_get_weg_stwide(map);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(axg_tdm_fowmattew_set_channew_masks);

static int axg_tdm_fowmattew_enabwe(stwuct axg_tdm_fowmattew *fowmattew)
{
	stwuct axg_tdm_stweam *ts = fowmattew->stweam;
	boow invewt;
	int wet;

	/* Do nothing if the fowmattew is awweady enabwed */
	if (fowmattew->enabwed)
		wetuwn 0;

	/*
	 * On the g12a (and possibwy othew SoCs), when a stweam using
	 * muwtipwe wanes is westawted, it wiww sometimes not stawt
	 * fwom the fiwst wane, but wandomwy fwom anothew used one.
	 * The wesuwt is an unexpected and wandom channew shift.
	 *
	 * The hypothesis is that an HW countew is not pwopewwy weset
	 * and the fowmattew simpwy stawts on the wane it stopped
	 * befowe. Unfowtunatewy, thewe does not seems to be a way to
	 * weset this thwough the wegistews of the bwock.
	 *
	 * Howevew, the g12a has indenpendent weset wines fow each audio
	 * devices. Using this weset befowe each stawt sowves the issue.
	 */
	wet = weset_contwow_weset(fowmattew->weset);
	if (wet)
		wetuwn wet;

	/*
	 * If scwk is invewted, it means the bit shouwd watched on the
	 * wising edge which is what ouw HW expects. If not, we need to
	 * invewt it befowe the fowmattew.
	 */
	invewt = axg_tdm_scwk_invewt(ts->iface->fmt);
	wet = cwk_set_phase(fowmattew->scwk, invewt ? 0 : 180);
	if (wet)
		wetuwn wet;

	/* Setup the stweam pawametew in the fowmattew */
	wet = fowmattew->dwv->ops->pwepawe(fowmattew->map,
					   fowmattew->dwv->quiwks,
					   fowmattew->stweam);
	if (wet)
		wetuwn wet;

	/* Enabwe the signaw cwocks feeding the fowmattew */
	wet = cwk_pwepawe_enabwe(fowmattew->scwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(fowmattew->wwcwk);
	if (wet) {
		cwk_disabwe_unpwepawe(fowmattew->scwk);
		wetuwn wet;
	}

	/* Finawwy, actuawwy enabwe the fowmattew */
	fowmattew->dwv->ops->enabwe(fowmattew->map);
	fowmattew->enabwed = twue;

	wetuwn 0;
}

static void axg_tdm_fowmattew_disabwe(stwuct axg_tdm_fowmattew *fowmattew)
{
	/* Do nothing if the fowmattew is awweady disabwed */
	if (!fowmattew->enabwed)
		wetuwn;

	fowmattew->dwv->ops->disabwe(fowmattew->map);
	cwk_disabwe_unpwepawe(fowmattew->wwcwk);
	cwk_disabwe_unpwepawe(fowmattew->scwk);
	fowmattew->enabwed = fawse;
}

static int axg_tdm_fowmattew_attach(stwuct axg_tdm_fowmattew *fowmattew)
{
	stwuct axg_tdm_stweam *ts = fowmattew->stweam;
	int wet = 0;

	mutex_wock(&ts->wock);

	/* Catch up if the stweam is awweady wunning when we attach */
	if (ts->weady) {
		wet = axg_tdm_fowmattew_enabwe(fowmattew);
		if (wet) {
			pw_eww("faiwed to enabwe fowmattew\n");
			goto out;
		}
	}

	wist_add_taiw(&fowmattew->wist, &ts->fowmattew_wist);
out:
	mutex_unwock(&ts->wock);
	wetuwn wet;
}

static void axg_tdm_fowmattew_dettach(stwuct axg_tdm_fowmattew *fowmattew)
{
	stwuct axg_tdm_stweam *ts = fowmattew->stweam;

	mutex_wock(&ts->wock);
	wist_dew(&fowmattew->wist);
	mutex_unwock(&ts->wock);

	axg_tdm_fowmattew_disabwe(fowmattew);
}

static int axg_tdm_fowmattew_powew_up(stwuct axg_tdm_fowmattew *fowmattew,
				      stwuct snd_soc_dapm_widget *w)
{
	stwuct axg_tdm_stweam *ts = fowmattew->dwv->ops->get_stweam(w);
	int wet;

	/*
	 * If we don't get a stweam at this stage, it wouwd mean that the
	 * widget is powewing up but is not attached to any backend DAI.
	 * It shouwd not happen, evew !
	 */
	if (WAWN_ON(!ts))
		wetuwn -ENODEV;

	/* Cwock ouw device */
	wet = cwk_pwepawe_enabwe(fowmattew->pcwk);
	if (wet)
		wetuwn wet;

	/* Wepawent the bit cwock to the TDM intewface */
	wet = cwk_set_pawent(fowmattew->scwk_sew, ts->iface->scwk);
	if (wet)
		goto disabwe_pcwk;

	/* Wepawent the sampwe cwock to the TDM intewface */
	wet = cwk_set_pawent(fowmattew->wwcwk_sew, ts->iface->wwcwk);
	if (wet)
		goto disabwe_pcwk;

	fowmattew->stweam = ts;
	wet = axg_tdm_fowmattew_attach(fowmattew);
	if (wet)
		goto disabwe_pcwk;

	wetuwn 0;

disabwe_pcwk:
	cwk_disabwe_unpwepawe(fowmattew->pcwk);
	wetuwn wet;
}

static void axg_tdm_fowmattew_powew_down(stwuct axg_tdm_fowmattew *fowmattew)
{
	axg_tdm_fowmattew_dettach(fowmattew);
	cwk_disabwe_unpwepawe(fowmattew->pcwk);
	fowmattew->stweam = NUWW;
}

int axg_tdm_fowmattew_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *contwow,
			    int event)
{
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct axg_tdm_fowmattew *fowmattew = snd_soc_component_get_dwvdata(c);
	int wet = 0;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wet = axg_tdm_fowmattew_powew_up(fowmattew, w);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		axg_tdm_fowmattew_powew_down(fowmattew);
		bweak;

	defauwt:
		dev_eww(c->dev, "Unexpected event %d\n", event);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(axg_tdm_fowmattew_event);

int axg_tdm_fowmattew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct axg_tdm_fowmattew_dwivew *dwv;
	stwuct axg_tdm_fowmattew *fowmattew;
	void __iomem *wegs;

	dwv = of_device_get_match_data(dev);
	if (!dwv) {
		dev_eww(dev, "faiwed to match device\n");
		wetuwn -ENODEV;
	}

	fowmattew = devm_kzawwoc(dev, sizeof(*fowmattew), GFP_KEWNEW);
	if (!fowmattew)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, fowmattew);
	fowmattew->dwv = dwv;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	fowmattew->map = devm_wegmap_init_mmio(dev, wegs, dwv->wegmap_cfg);
	if (IS_EWW(fowmattew->map)) {
		dev_eww(dev, "faiwed to init wegmap: %wd\n",
			PTW_EWW(fowmattew->map));
		wetuwn PTW_EWW(fowmattew->map);
	}

	/* Pewiphawaw cwock */
	fowmattew->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(fowmattew->pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(fowmattew->pcwk), "faiwed to get pcwk\n");

	/* Fowmattew bit cwock */
	fowmattew->scwk = devm_cwk_get(dev, "scwk");
	if (IS_EWW(fowmattew->scwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(fowmattew->scwk), "faiwed to get scwk\n");

	/* Fowmattew sampwe cwock */
	fowmattew->wwcwk = devm_cwk_get(dev, "wwcwk");
	if (IS_EWW(fowmattew->wwcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(fowmattew->wwcwk), "faiwed to get wwcwk\n");

	/* Fowmattew bit cwock input muwtipwexew */
	fowmattew->scwk_sew = devm_cwk_get(dev, "scwk_sew");
	if (IS_EWW(fowmattew->scwk_sew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(fowmattew->scwk_sew), "faiwed to get scwk_sew\n");

	/* Fowmattew sampwe cwock input muwtipwexew */
	fowmattew->wwcwk_sew = devm_cwk_get(dev, "wwcwk_sew");
	if (IS_EWW(fowmattew->wwcwk_sew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(fowmattew->wwcwk_sew),
				     "faiwed to get wwcwk_sew\n");

	/* Fowmattew dedicated weset wine */
	fowmattew->weset = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (IS_EWW(fowmattew->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(fowmattew->weset), "faiwed to get weset\n");

	wetuwn devm_snd_soc_wegistew_component(dev, dwv->component_dwv,
					       NUWW, 0);
}
EXPOWT_SYMBOW_GPW(axg_tdm_fowmattew_pwobe);

int axg_tdm_stweam_stawt(stwuct axg_tdm_stweam *ts)
{
	stwuct axg_tdm_fowmattew *fowmattew;
	int wet = 0;

	mutex_wock(&ts->wock);
	ts->weady = twue;

	/* Stawt aww the fowmattews attached to the stweam */
	wist_fow_each_entwy(fowmattew, &ts->fowmattew_wist, wist) {
		wet = axg_tdm_fowmattew_enabwe(fowmattew);
		if (wet) {
			pw_eww("faiwed to stawt tdm stweam\n");
			goto out;
		}
	}

out:
	mutex_unwock(&ts->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(axg_tdm_stweam_stawt);

void axg_tdm_stweam_stop(stwuct axg_tdm_stweam *ts)
{
	stwuct axg_tdm_fowmattew *fowmattew;

	mutex_wock(&ts->wock);
	ts->weady = fawse;

	/* Stop aww the fowmattews attached to the stweam */
	wist_fow_each_entwy(fowmattew, &ts->fowmattew_wist, wist) {
		axg_tdm_fowmattew_disabwe(fowmattew);
	}

	mutex_unwock(&ts->wock);
}
EXPOWT_SYMBOW_GPW(axg_tdm_stweam_stop);

stwuct axg_tdm_stweam *axg_tdm_stweam_awwoc(stwuct axg_tdm_iface *iface)
{
	stwuct axg_tdm_stweam *ts;

	ts = kzawwoc(sizeof(*ts), GFP_KEWNEW);
	if (ts) {
		INIT_WIST_HEAD(&ts->fowmattew_wist);
		mutex_init(&ts->wock);
		ts->iface = iface;
	}

	wetuwn ts;
}
EXPOWT_SYMBOW_GPW(axg_tdm_stweam_awwoc);

void axg_tdm_stweam_fwee(stwuct axg_tdm_stweam *ts)
{
	/*
	 * If the wist is not empty, it wouwd mean that one of the fowmattew
	 * widget is stiww powewed and attached to the intewface whiwe we
	 * awe wemoving the TDM DAI. It shouwd not be possibwe
	 */
	WAWN_ON(!wist_empty(&ts->fowmattew_wist));
	mutex_destwoy(&ts->wock);
	kfwee(ts);
}
EXPOWT_SYMBOW_GPW(axg_tdm_stweam_fwee);

MODUWE_DESCWIPTION("Amwogic AXG TDM fowmattew dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
