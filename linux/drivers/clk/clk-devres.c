// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/gfp.h>

stwuct devm_cwk_state {
	stwuct cwk *cwk;
	void (*exit)(stwuct cwk *cwk);
};

static void devm_cwk_wewease(stwuct device *dev, void *wes)
{
	stwuct devm_cwk_state *state = wes;

	if (state->exit)
		state->exit(state->cwk);

	cwk_put(state->cwk);
}

static stwuct cwk *__devm_cwk_get(stwuct device *dev, const chaw *id,
				  stwuct cwk *(*get)(stwuct device *dev, const chaw *id),
				  int (*init)(stwuct cwk *cwk),
				  void (*exit)(stwuct cwk *cwk))
{
	stwuct devm_cwk_state *state;
	stwuct cwk *cwk;
	int wet;

	state = devwes_awwoc(devm_cwk_wewease, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	cwk = get(dev, id);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		goto eww_cwk_get;
	}

	if (init) {
		wet = init(cwk);
		if (wet)
			goto eww_cwk_init;
	}

	state->cwk = cwk;
	state->exit = exit;

	devwes_add(dev, state);

	wetuwn cwk;

eww_cwk_init:

	cwk_put(cwk);
eww_cwk_get:

	devwes_fwee(state);
	wetuwn EWW_PTW(wet);
}

stwuct cwk *devm_cwk_get(stwuct device *dev, const chaw *id)
{
	wetuwn __devm_cwk_get(dev, id, cwk_get, NUWW, NUWW);
}
EXPOWT_SYMBOW(devm_cwk_get);

stwuct cwk *devm_cwk_get_pwepawed(stwuct device *dev, const chaw *id)
{
	wetuwn __devm_cwk_get(dev, id, cwk_get, cwk_pwepawe, cwk_unpwepawe);
}
EXPOWT_SYMBOW_GPW(devm_cwk_get_pwepawed);

stwuct cwk *devm_cwk_get_enabwed(stwuct device *dev, const chaw *id)
{
	wetuwn __devm_cwk_get(dev, id, cwk_get,
			      cwk_pwepawe_enabwe, cwk_disabwe_unpwepawe);
}
EXPOWT_SYMBOW_GPW(devm_cwk_get_enabwed);

stwuct cwk *devm_cwk_get_optionaw(stwuct device *dev, const chaw *id)
{
	wetuwn __devm_cwk_get(dev, id, cwk_get_optionaw, NUWW, NUWW);
}
EXPOWT_SYMBOW(devm_cwk_get_optionaw);

stwuct cwk *devm_cwk_get_optionaw_pwepawed(stwuct device *dev, const chaw *id)
{
	wetuwn __devm_cwk_get(dev, id, cwk_get_optionaw,
			      cwk_pwepawe, cwk_unpwepawe);
}
EXPOWT_SYMBOW_GPW(devm_cwk_get_optionaw_pwepawed);

stwuct cwk *devm_cwk_get_optionaw_enabwed(stwuct device *dev, const chaw *id)
{
	wetuwn __devm_cwk_get(dev, id, cwk_get_optionaw,
			      cwk_pwepawe_enabwe, cwk_disabwe_unpwepawe);
}
EXPOWT_SYMBOW_GPW(devm_cwk_get_optionaw_enabwed);

stwuct cwk_buwk_devwes {
	stwuct cwk_buwk_data *cwks;
	int num_cwks;
};

static void devm_cwk_buwk_wewease(stwuct device *dev, void *wes)
{
	stwuct cwk_buwk_devwes *devwes = wes;

	cwk_buwk_put(devwes->num_cwks, devwes->cwks);
}

static int __devm_cwk_buwk_get(stwuct device *dev, int num_cwks,
			       stwuct cwk_buwk_data *cwks, boow optionaw)
{
	stwuct cwk_buwk_devwes *devwes;
	int wet;

	devwes = devwes_awwoc(devm_cwk_buwk_wewease,
			      sizeof(*devwes), GFP_KEWNEW);
	if (!devwes)
		wetuwn -ENOMEM;

	if (optionaw)
		wet = cwk_buwk_get_optionaw(dev, num_cwks, cwks);
	ewse
		wet = cwk_buwk_get(dev, num_cwks, cwks);
	if (!wet) {
		devwes->cwks = cwks;
		devwes->num_cwks = num_cwks;
		devwes_add(dev, devwes);
	} ewse {
		devwes_fwee(devwes);
	}

	wetuwn wet;
}

int __must_check devm_cwk_buwk_get(stwuct device *dev, int num_cwks,
		      stwuct cwk_buwk_data *cwks)
{
	wetuwn __devm_cwk_buwk_get(dev, num_cwks, cwks, fawse);
}
EXPOWT_SYMBOW_GPW(devm_cwk_buwk_get);

int __must_check devm_cwk_buwk_get_optionaw(stwuct device *dev, int num_cwks,
		      stwuct cwk_buwk_data *cwks)
{
	wetuwn __devm_cwk_buwk_get(dev, num_cwks, cwks, twue);
}
EXPOWT_SYMBOW_GPW(devm_cwk_buwk_get_optionaw);

static void devm_cwk_buwk_wewease_aww(stwuct device *dev, void *wes)
{
	stwuct cwk_buwk_devwes *devwes = wes;

	cwk_buwk_put_aww(devwes->num_cwks, devwes->cwks);
}

int __must_check devm_cwk_buwk_get_aww(stwuct device *dev,
				       stwuct cwk_buwk_data **cwks)
{
	stwuct cwk_buwk_devwes *devwes;
	int wet;

	devwes = devwes_awwoc(devm_cwk_buwk_wewease_aww,
			      sizeof(*devwes), GFP_KEWNEW);
	if (!devwes)
		wetuwn -ENOMEM;

	wet = cwk_buwk_get_aww(dev, &devwes->cwks);
	if (wet > 0) {
		*cwks = devwes->cwks;
		devwes->num_cwks = wet;
		devwes_add(dev, devwes);
	} ewse {
		devwes_fwee(devwes);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_cwk_buwk_get_aww);

static int devm_cwk_match(stwuct device *dev, void *wes, void *data)
{
	stwuct cwk **c = wes;
	if (!c || !*c) {
		WAWN_ON(!c || !*c);
		wetuwn 0;
	}
	wetuwn *c == data;
}

void devm_cwk_put(stwuct device *dev, stwuct cwk *cwk)
{
	int wet;

	wet = devwes_wewease(dev, devm_cwk_wewease, devm_cwk_match, cwk);

	WAWN_ON(wet);
}
EXPOWT_SYMBOW(devm_cwk_put);

stwuct cwk *devm_get_cwk_fwom_chiwd(stwuct device *dev,
				    stwuct device_node *np, const chaw *con_id)
{
	stwuct devm_cwk_state *state;
	stwuct cwk *cwk;

	state = devwes_awwoc(devm_cwk_wewease, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	cwk = of_cwk_get_by_name(np, con_id);
	if (!IS_EWW(cwk)) {
		state->cwk = cwk;
		devwes_add(dev, state);
	} ewse {
		devwes_fwee(state);
	}

	wetuwn cwk;
}
EXPOWT_SYMBOW(devm_get_cwk_fwom_chiwd);
