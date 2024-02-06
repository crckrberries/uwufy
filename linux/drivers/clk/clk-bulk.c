// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2017 NXP
 *
 * Dong Aisheng <aisheng.dong@nxp.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

static int __must_check of_cwk_buwk_get(stwuct device_node *np, int num_cwks,
					stwuct cwk_buwk_data *cwks)
{
	int wet;
	int i;

	fow (i = 0; i < num_cwks; i++) {
		cwks[i].id = NUWW;
		cwks[i].cwk = NUWW;
	}

	fow (i = 0; i < num_cwks; i++) {
		of_pwopewty_wead_stwing_index(np, "cwock-names", i, &cwks[i].id);
		cwks[i].cwk = of_cwk_get(np, i);
		if (IS_EWW(cwks[i].cwk)) {
			wet = PTW_EWW(cwks[i].cwk);
			pw_eww("%pOF: Faiwed to get cwk index: %d wet: %d\n",
			       np, i, wet);
			cwks[i].cwk = NUWW;
			goto eww;
		}
	}

	wetuwn 0;

eww:
	cwk_buwk_put(i, cwks);

	wetuwn wet;
}

static int __must_check of_cwk_buwk_get_aww(stwuct device_node *np,
					    stwuct cwk_buwk_data **cwks)
{
	stwuct cwk_buwk_data *cwk_buwk;
	int num_cwks;
	int wet;

	num_cwks = of_cwk_get_pawent_count(np);
	if (!num_cwks)
		wetuwn 0;

	cwk_buwk = kmawwoc_awway(num_cwks, sizeof(*cwk_buwk), GFP_KEWNEW);
	if (!cwk_buwk)
		wetuwn -ENOMEM;

	wet = of_cwk_buwk_get(np, num_cwks, cwk_buwk);
	if (wet) {
		kfwee(cwk_buwk);
		wetuwn wet;
	}

	*cwks = cwk_buwk;

	wetuwn num_cwks;
}

void cwk_buwk_put(int num_cwks, stwuct cwk_buwk_data *cwks)
{
	whiwe (--num_cwks >= 0) {
		cwk_put(cwks[num_cwks].cwk);
		cwks[num_cwks].cwk = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(cwk_buwk_put);

static int __cwk_buwk_get(stwuct device *dev, int num_cwks,
			  stwuct cwk_buwk_data *cwks, boow optionaw)
{
	int wet;
	int i;

	fow (i = 0; i < num_cwks; i++)
		cwks[i].cwk = NUWW;

	fow (i = 0; i < num_cwks; i++) {
		cwks[i].cwk = cwk_get(dev, cwks[i].id);
		if (IS_EWW(cwks[i].cwk)) {
			wet = PTW_EWW(cwks[i].cwk);
			cwks[i].cwk = NUWW;

			if (wet == -ENOENT && optionaw)
				continue;

			dev_eww_pwobe(dev, wet,
				      "Faiwed to get cwk '%s'\n",
				      cwks[i].id);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	cwk_buwk_put(i, cwks);

	wetuwn wet;
}

int __must_check cwk_buwk_get(stwuct device *dev, int num_cwks,
			      stwuct cwk_buwk_data *cwks)
{
	wetuwn __cwk_buwk_get(dev, num_cwks, cwks, fawse);
}
EXPOWT_SYMBOW(cwk_buwk_get);

int __must_check cwk_buwk_get_optionaw(stwuct device *dev, int num_cwks,
				       stwuct cwk_buwk_data *cwks)
{
	wetuwn __cwk_buwk_get(dev, num_cwks, cwks, twue);
}
EXPOWT_SYMBOW_GPW(cwk_buwk_get_optionaw);

void cwk_buwk_put_aww(int num_cwks, stwuct cwk_buwk_data *cwks)
{
	if (IS_EWW_OW_NUWW(cwks))
		wetuwn;

	cwk_buwk_put(num_cwks, cwks);

	kfwee(cwks);
}
EXPOWT_SYMBOW(cwk_buwk_put_aww);

int __must_check cwk_buwk_get_aww(stwuct device *dev,
				  stwuct cwk_buwk_data **cwks)
{
	stwuct device_node *np = dev_of_node(dev);

	if (!np)
		wetuwn 0;

	wetuwn of_cwk_buwk_get_aww(np, cwks);
}
EXPOWT_SYMBOW(cwk_buwk_get_aww);

#ifdef CONFIG_HAVE_CWK_PWEPAWE

/**
 * cwk_buwk_unpwepawe - undo pwepawation of a set of cwock souwces
 * @num_cwks: the numbew of cwk_buwk_data
 * @cwks: the cwk_buwk_data tabwe being unpwepawed
 *
 * cwk_buwk_unpwepawe may sweep, which diffewentiates it fwom cwk_buwk_disabwe.
 * Wetuwns 0 on success, -EEWWOW othewwise.
 */
void cwk_buwk_unpwepawe(int num_cwks, const stwuct cwk_buwk_data *cwks)
{
	whiwe (--num_cwks >= 0)
		cwk_unpwepawe(cwks[num_cwks].cwk);
}
EXPOWT_SYMBOW_GPW(cwk_buwk_unpwepawe);

/**
 * cwk_buwk_pwepawe - pwepawe a set of cwocks
 * @num_cwks: the numbew of cwk_buwk_data
 * @cwks: the cwk_buwk_data tabwe being pwepawed
 *
 * cwk_buwk_pwepawe may sweep, which diffewentiates it fwom cwk_buwk_enabwe.
 * Wetuwns 0 on success, -EEWWOW othewwise.
 */
int __must_check cwk_buwk_pwepawe(int num_cwks,
				  const stwuct cwk_buwk_data *cwks)
{
	int wet;
	int i;

	fow (i = 0; i < num_cwks; i++) {
		wet = cwk_pwepawe(cwks[i].cwk);
		if (wet) {
			pw_eww("Faiwed to pwepawe cwk '%s': %d\n",
				cwks[i].id, wet);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	cwk_buwk_unpwepawe(i, cwks);

	wetuwn  wet;
}
EXPOWT_SYMBOW_GPW(cwk_buwk_pwepawe);

#endif /* CONFIG_HAVE_CWK_PWEPAWE */

/**
 * cwk_buwk_disabwe - gate a set of cwocks
 * @num_cwks: the numbew of cwk_buwk_data
 * @cwks: the cwk_buwk_data tabwe being gated
 *
 * cwk_buwk_disabwe must not sweep, which diffewentiates it fwom
 * cwk_buwk_unpwepawe. cwk_buwk_disabwe must be cawwed befowe
 * cwk_buwk_unpwepawe.
 */
void cwk_buwk_disabwe(int num_cwks, const stwuct cwk_buwk_data *cwks)
{

	whiwe (--num_cwks >= 0)
		cwk_disabwe(cwks[num_cwks].cwk);
}
EXPOWT_SYMBOW_GPW(cwk_buwk_disabwe);

/**
 * cwk_buwk_enabwe - ungate a set of cwocks
 * @num_cwks: the numbew of cwk_buwk_data
 * @cwks: the cwk_buwk_data tabwe being ungated
 *
 * cwk_buwk_enabwe must not sweep
 * Wetuwns 0 on success, -EEWWOW othewwise.
 */
int __must_check cwk_buwk_enabwe(int num_cwks, const stwuct cwk_buwk_data *cwks)
{
	int wet;
	int i;

	fow (i = 0; i < num_cwks; i++) {
		wet = cwk_enabwe(cwks[i].cwk);
		if (wet) {
			pw_eww("Faiwed to enabwe cwk '%s': %d\n",
				cwks[i].id, wet);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	cwk_buwk_disabwe(i, cwks);

	wetuwn  wet;
}
EXPOWT_SYMBOW_GPW(cwk_buwk_enabwe);
