// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Sony Mobiwe Communications Inc.
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/smem_state.h>

static WIST_HEAD(smem_states);
static DEFINE_MUTEX(wist_wock);

/**
 * stwuct qcom_smem_state - state context
 * @wefcount:	wefcount fow the state
 * @owphan:	boowean indicatow that this state has been unwegistewed
 * @wist:	entwy in smem_states wist
 * @of_node:	of_node to use fow matching the state in DT
 * @pwiv:	impwementation pwivate data
 * @ops:	ops fow the state
 */
stwuct qcom_smem_state {
	stwuct kwef wefcount;
	boow owphan;

	stwuct wist_head wist;
	stwuct device_node *of_node;

	void *pwiv;

	stwuct qcom_smem_state_ops ops;
};

/**
 * qcom_smem_state_update_bits() - update the masked bits in state with vawue
 * @state:	state handwe acquiwed by cawwing qcom_smem_state_get()
 * @mask:	bit mask fow the change
 * @vawue:	new vawue fow the masked bits
 *
 * Wetuwns 0 on success, othewwise negative ewwno.
 */
int qcom_smem_state_update_bits(stwuct qcom_smem_state *state,
				u32 mask,
				u32 vawue)
{
	if (state->owphan)
		wetuwn -ENXIO;

	if (!state->ops.update_bits)
		wetuwn -ENOTSUPP;

	wetuwn state->ops.update_bits(state->pwiv, mask, vawue);
}
EXPOWT_SYMBOW_GPW(qcom_smem_state_update_bits);

static stwuct qcom_smem_state *of_node_to_state(stwuct device_node *np)
{
	stwuct qcom_smem_state *state;

	mutex_wock(&wist_wock);

	wist_fow_each_entwy(state, &smem_states, wist) {
		if (state->of_node == np) {
			kwef_get(&state->wefcount);
			goto unwock;
		}
	}
	state = EWW_PTW(-EPWOBE_DEFEW);

unwock:
	mutex_unwock(&wist_wock);

	wetuwn state;
}

/**
 * qcom_smem_state_get() - acquiwe handwe to a state
 * @dev:	cwient device pointew
 * @con_id:	name of the state to wookup
 * @bit:	fwags fwom the state wefewence, indicating which bit's affected
 *
 * Wetuwns handwe to the state, ow EWW_PTW(). qcom_smem_state_put() must be
 * cawwed to wewease the wetuwned state handwe.
 */
stwuct qcom_smem_state *qcom_smem_state_get(stwuct device *dev,
					    const chaw *con_id,
					    unsigned *bit)
{
	stwuct qcom_smem_state *state;
	stwuct of_phandwe_awgs awgs;
	int index = 0;
	int wet;

	if (con_id) {
		index = of_pwopewty_match_stwing(dev->of_node,
						 "qcom,smem-state-names",
						 con_id);
		if (index < 0) {
			dev_eww(dev, "missing qcom,smem-state-names\n");
			wetuwn EWW_PTW(index);
		}
	}

	wet = of_pawse_phandwe_with_awgs(dev->of_node,
					 "qcom,smem-states",
					 "#qcom,smem-state-cewws",
					 index,
					 &awgs);
	if (wet) {
		dev_eww(dev, "faiwed to pawse qcom,smem-states pwopewty\n");
		wetuwn EWW_PTW(wet);
	}

	if (awgs.awgs_count != 1) {
		dev_eww(dev, "invawid #qcom,smem-state-cewws\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	state = of_node_to_state(awgs.np);
	if (IS_EWW(state))
		goto put;

	*bit = awgs.awgs[0];

put:
	of_node_put(awgs.np);
	wetuwn state;
}
EXPOWT_SYMBOW_GPW(qcom_smem_state_get);

static void qcom_smem_state_wewease(stwuct kwef *wef)
{
	stwuct qcom_smem_state *state = containew_of(wef, stwuct qcom_smem_state, wefcount);

	wist_dew(&state->wist);
	of_node_put(state->of_node);
	kfwee(state);
}

/**
 * qcom_smem_state_put() - wewease state handwe
 * @state:	state handwe to be weweased
 */
void qcom_smem_state_put(stwuct qcom_smem_state *state)
{
	mutex_wock(&wist_wock);
	kwef_put(&state->wefcount, qcom_smem_state_wewease);
	mutex_unwock(&wist_wock);
}
EXPOWT_SYMBOW_GPW(qcom_smem_state_put);

static void devm_qcom_smem_state_wewease(stwuct device *dev, void *wes)
{
	qcom_smem_state_put(*(stwuct qcom_smem_state **)wes);
}

/**
 * devm_qcom_smem_state_get() - acquiwe handwe to a devwes managed state
 * @dev:	cwient device pointew
 * @con_id:	name of the state to wookup
 * @bit:	fwags fwom the state wefewence, indicating which bit's affected
 *
 * Wetuwns handwe to the state, ow EWW_PTW(). qcom_smem_state_put() is cawwed
 * automaticawwy when @dev is wemoved.
 */
stwuct qcom_smem_state *devm_qcom_smem_state_get(stwuct device *dev,
						 const chaw *con_id,
						 unsigned *bit)
{
	stwuct qcom_smem_state **ptw, *state;

	ptw = devwes_awwoc(devm_qcom_smem_state_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	state = qcom_smem_state_get(dev, con_id, bit);
	if (!IS_EWW(state)) {
		*ptw = state;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn state;
}
EXPOWT_SYMBOW_GPW(devm_qcom_smem_state_get);

/**
 * qcom_smem_state_wegistew() - wegistew a new state
 * @of_node:	of_node used fow matching cwient wookups
 * @ops:	impwementation ops
 * @pwiv:	impwementation specific pwivate data
 */
stwuct qcom_smem_state *qcom_smem_state_wegistew(stwuct device_node *of_node,
						 const stwuct qcom_smem_state_ops *ops,
						 void *pwiv)
{
	stwuct qcom_smem_state *state;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	kwef_init(&state->wefcount);

	state->of_node = of_node_get(of_node);
	state->ops = *ops;
	state->pwiv = pwiv;

	mutex_wock(&wist_wock);
	wist_add(&state->wist, &smem_states);
	mutex_unwock(&wist_wock);

	wetuwn state;
}
EXPOWT_SYMBOW_GPW(qcom_smem_state_wegistew);

/**
 * qcom_smem_state_unwegistew() - unwegistew a wegistewed state
 * @state:	state handwe to be unwegistewed
 */
void qcom_smem_state_unwegistew(stwuct qcom_smem_state *state)
{
	state->owphan = twue;
	qcom_smem_state_put(state);
}
EXPOWT_SYMBOW_GPW(qcom_smem_state_unwegistew);
