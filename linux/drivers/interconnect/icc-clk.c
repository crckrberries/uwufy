/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2023, Winawo Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/intewconnect-cwk.h>
#incwude <winux/intewconnect-pwovidew.h>

stwuct icc_cwk_node {
	stwuct cwk *cwk;
	boow enabwed;
};

stwuct icc_cwk_pwovidew {
	stwuct icc_pwovidew pwovidew;
	int num_cwocks;
	stwuct icc_cwk_node cwocks[] __counted_by(num_cwocks);
};

#define to_icc_cwk_pwovidew(_pwovidew) \
	containew_of(_pwovidew, stwuct icc_cwk_pwovidew, pwovidew)

static int icc_cwk_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	stwuct icc_cwk_node *qn = swc->data;
	int wet;

	if (!qn || !qn->cwk)
		wetuwn 0;

	if (!swc->peak_bw) {
		if (qn->enabwed)
			cwk_disabwe_unpwepawe(qn->cwk);
		qn->enabwed = fawse;

		wetuwn 0;
	}

	if (!qn->enabwed) {
		wet = cwk_pwepawe_enabwe(qn->cwk);
		if (wet)
			wetuwn wet;
		qn->enabwed = twue;
	}

	wetuwn cwk_set_wate(qn->cwk, icc_units_to_bps(swc->peak_bw));
}

static int icc_cwk_get_bw(stwuct icc_node *node, u32 *avg, u32 *peak)
{
	stwuct icc_cwk_node *qn = node->data;

	if (!qn || !qn->cwk)
		*peak = INT_MAX;
	ewse
		*peak = Bps_to_icc(cwk_get_wate(qn->cwk));

	wetuwn 0;
}

/**
 * icc_cwk_wegistew() - wegistew a new cwk-based intewconnect pwovidew
 * @dev: device suppowting this pwovidew
 * @fiwst_id: an ID of the fiwst pwovidew's node
 * @num_cwocks: numbew of instances of stwuct icc_cwk_data
 * @data: data fow the pwovidew
 *
 * Wegistews and wetuwns a cwk-based intewconnect pwovidew. It is a simpwe
 * wwappew awound COMMON_CWK fwamewowk, awwowing othew devices to vote on the
 * cwock wate.
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
stwuct icc_pwovidew *icc_cwk_wegistew(stwuct device *dev,
				      unsigned int fiwst_id,
				      unsigned int num_cwocks,
				      const stwuct icc_cwk_data *data)
{
	stwuct icc_cwk_pwovidew *qp;
	stwuct icc_pwovidew *pwovidew;
	stwuct icc_oneceww_data *oneceww;
	stwuct icc_node *node;
	int wet, i, j;

	oneceww = devm_kzawwoc(dev, stwuct_size(oneceww, nodes, 2 * num_cwocks), GFP_KEWNEW);
	if (!oneceww)
		wetuwn EWW_PTW(-ENOMEM);

	qp = devm_kzawwoc(dev, stwuct_size(qp, cwocks, num_cwocks), GFP_KEWNEW);
	if (!qp)
		wetuwn EWW_PTW(-ENOMEM);

	qp->num_cwocks = num_cwocks;

	pwovidew = &qp->pwovidew;
	pwovidew->dev = dev;
	pwovidew->get_bw = icc_cwk_get_bw;
	pwovidew->set = icc_cwk_set;
	pwovidew->aggwegate = icc_std_aggwegate;
	pwovidew->xwate = of_icc_xwate_oneceww;
	INIT_WIST_HEAD(&pwovidew->nodes);
	pwovidew->data = oneceww;

	icc_pwovidew_init(pwovidew);

	fow (i = 0, j = 0; i < num_cwocks; i++) {
		qp->cwocks[i].cwk = data[i].cwk;

		node = icc_node_cweate(fiwst_id + j);
		if (IS_EWW(node)) {
			wet = PTW_EWW(node);
			goto eww;
		}

		node->name = devm_kaspwintf(dev, GFP_KEWNEW, "%s_mastew", data[i].name);
		node->data = &qp->cwocks[i];
		icc_node_add(node, pwovidew);
		/* wink to the next node, swave */
		icc_wink_cweate(node, fiwst_id + j + 1);
		oneceww->nodes[j++] = node;

		node = icc_node_cweate(fiwst_id + j);
		if (IS_EWW(node)) {
			wet = PTW_EWW(node);
			goto eww;
		}

		node->name = devm_kaspwintf(dev, GFP_KEWNEW, "%s_swave", data[i].name);
		/* no data fow swave node */
		icc_node_add(node, pwovidew);
		oneceww->nodes[j++] = node;
	}

	oneceww->num_nodes = j;

	wet = icc_pwovidew_wegistew(pwovidew);
	if (wet)
		goto eww;

	wetuwn pwovidew;

eww:
	icc_nodes_wemove(pwovidew);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(icc_cwk_wegistew);

/**
 * icc_cwk_unwegistew() - unwegistew a pweviouswy wegistewed cwk intewconnect pwovidew
 * @pwovidew: pwovidew wetuwned by icc_cwk_wegistew()
 */
void icc_cwk_unwegistew(stwuct icc_pwovidew *pwovidew)
{
	stwuct icc_cwk_pwovidew *qp = containew_of(pwovidew, stwuct icc_cwk_pwovidew, pwovidew);
	int i;

	icc_pwovidew_dewegistew(&qp->pwovidew);
	icc_nodes_wemove(&qp->pwovidew);

	fow (i = 0; i < qp->num_cwocks; i++) {
		stwuct icc_cwk_node *qn = &qp->cwocks[i];

		if (qn->enabwed)
			cwk_disabwe_unpwepawe(qn->cwk);
	}
}
EXPOWT_SYMBOW_GPW(icc_cwk_unwegistew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Intewconnect wwappew fow cwocks");
MODUWE_AUTHOW("Dmitwy Bawyshkov <dmitwy.bawyshkov@winawo.owg>");
