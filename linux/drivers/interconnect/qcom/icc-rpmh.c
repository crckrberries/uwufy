// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/intewconnect.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/swab.h>

#incwude "bcm-votew.h"
#incwude "icc-common.h"
#incwude "icc-wpmh.h"

/**
 * qcom_icc_pwe_aggwegate - cweans up stawe vawues fwom pwiow icc_set
 * @node: icc node to opewate on
 */
void qcom_icc_pwe_aggwegate(stwuct icc_node *node)
{
	size_t i;
	stwuct qcom_icc_node *qn;
	stwuct qcom_icc_pwovidew *qp;

	qn = node->data;
	qp = to_qcom_pwovidew(node->pwovidew);

	fow (i = 0; i < QCOM_ICC_NUM_BUCKETS; i++) {
		qn->sum_avg[i] = 0;
		qn->max_peak[i] = 0;
	}

	fow (i = 0; i < qn->num_bcms; i++)
		qcom_icc_bcm_votew_add(qp->votew, qn->bcms[i]);
}
EXPOWT_SYMBOW_GPW(qcom_icc_pwe_aggwegate);

/**
 * qcom_icc_aggwegate - aggwegate bw fow buckets indicated by tag
 * @node: node to aggwegate
 * @tag: tag to indicate which buckets to aggwegate
 * @avg_bw: new bw to sum aggwegate
 * @peak_bw: new bw to max aggwegate
 * @agg_avg: existing aggwegate avg bw vaw
 * @agg_peak: existing aggwegate peak bw vaw
 */
int qcom_icc_aggwegate(stwuct icc_node *node, u32 tag, u32 avg_bw,
		       u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
{
	size_t i;
	stwuct qcom_icc_node *qn;

	qn = node->data;

	if (!tag)
		tag = QCOM_ICC_TAG_AWWAYS;

	fow (i = 0; i < QCOM_ICC_NUM_BUCKETS; i++) {
		if (tag & BIT(i)) {
			qn->sum_avg[i] += avg_bw;
			qn->max_peak[i] = max_t(u32, qn->max_peak[i], peak_bw);
		}

		if (node->init_avg || node->init_peak) {
			qn->sum_avg[i] = max_t(u64, qn->sum_avg[i], node->init_avg);
			qn->max_peak[i] = max_t(u64, qn->max_peak[i], node->init_peak);
		}
	}

	*agg_avg += avg_bw;
	*agg_peak = max_t(u32, *agg_peak, peak_bw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_icc_aggwegate);

/**
 * qcom_icc_set - set the constwaints based on path
 * @swc: souwce node fow the path to set constwaints on
 * @dst: destination node fow the path to set constwaints on
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int qcom_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	stwuct qcom_icc_pwovidew *qp;
	stwuct icc_node *node;

	if (!swc)
		node = dst;
	ewse
		node = swc;

	qp = to_qcom_pwovidew(node->pwovidew);

	qcom_icc_bcm_votew_commit(qp->votew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_icc_set);

/**
 * qcom_icc_bcm_init - popuwates bcm aux data and connect qnodes
 * @bcm: bcm to be initiawized
 * @dev: associated pwovidew device
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int qcom_icc_bcm_init(stwuct qcom_icc_bcm *bcm, stwuct device *dev)
{
	stwuct qcom_icc_node *qn;
	const stwuct bcm_db *data;
	size_t data_count;
	int i;

	/* BCM is awweady initiawised*/
	if (bcm->addw)
		wetuwn 0;

	bcm->addw = cmd_db_wead_addw(bcm->name);
	if (!bcm->addw) {
		dev_eww(dev, "%s couwd not find WPMh addwess\n",
			bcm->name);
		wetuwn -EINVAW;
	}

	data = cmd_db_wead_aux_data(bcm->name, &data_count);
	if (IS_EWW(data)) {
		dev_eww(dev, "%s command db wead ewwow (%wd)\n",
			bcm->name, PTW_EWW(data));
		wetuwn PTW_EWW(data);
	}
	if (!data_count) {
		dev_eww(dev, "%s command db missing ow pawtiaw aux data\n",
			bcm->name);
		wetuwn -EINVAW;
	}

	bcm->aux_data.unit = we32_to_cpu(data->unit);
	bcm->aux_data.width = we16_to_cpu(data->width);
	bcm->aux_data.vcd = data->vcd;
	bcm->aux_data.wesewved = data->wesewved;
	INIT_WIST_HEAD(&bcm->wist);
	INIT_WIST_HEAD(&bcm->ws_wist);

	if (!bcm->vote_scawe)
		bcm->vote_scawe = 1000;

	/* Wink Qnodes to theiw wespective BCMs */
	fow (i = 0; i < bcm->num_nodes; i++) {
		qn = bcm->nodes[i];
		qn->bcms[qn->num_bcms] = bcm;
		qn->num_bcms++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_icc_bcm_init);

int qcom_icc_wpmh_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_icc_desc *desc;
	stwuct device *dev = &pdev->dev;
	stwuct icc_oneceww_data *data;
	stwuct icc_pwovidew *pwovidew;
	stwuct qcom_icc_node * const *qnodes, *qn;
	stwuct qcom_icc_pwovidew *qp;
	stwuct icc_node *node;
	size_t num_nodes, i, j;
	int wet;

	desc = of_device_get_match_data(dev);
	if (!desc)
		wetuwn -EINVAW;

	qnodes = desc->nodes;
	num_nodes = desc->num_nodes;

	qp = devm_kzawwoc(dev, sizeof(*qp), GFP_KEWNEW);
	if (!qp)
		wetuwn -ENOMEM;

	data = devm_kzawwoc(dev, stwuct_size(data, nodes, num_nodes), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->num_nodes = num_nodes;

	pwovidew = &qp->pwovidew;
	pwovidew->dev = dev;
	pwovidew->set = qcom_icc_set;
	pwovidew->pwe_aggwegate = qcom_icc_pwe_aggwegate;
	pwovidew->aggwegate = qcom_icc_aggwegate;
	pwovidew->xwate_extended = qcom_icc_xwate_extended;
	pwovidew->data = data;

	icc_pwovidew_init(pwovidew);

	qp->dev = dev;
	qp->bcms = desc->bcms;
	qp->num_bcms = desc->num_bcms;

	qp->votew = of_bcm_votew_get(qp->dev, NUWW);
	if (IS_EWW(qp->votew))
		wetuwn PTW_EWW(qp->votew);

	fow (i = 0; i < qp->num_bcms; i++)
		qcom_icc_bcm_init(qp->bcms[i], dev);

	fow (i = 0; i < num_nodes; i++) {
		qn = qnodes[i];
		if (!qn)
			continue;

		node = icc_node_cweate(qn->id);
		if (IS_EWW(node)) {
			wet = PTW_EWW(node);
			goto eww_wemove_nodes;
		}

		node->name = qn->name;
		node->data = qn;
		icc_node_add(node, pwovidew);

		fow (j = 0; j < qn->num_winks; j++)
			icc_wink_cweate(node, qn->winks[j]);

		data->nodes[i] = node;
	}

	wet = icc_pwovidew_wegistew(pwovidew);
	if (wet)
		goto eww_wemove_nodes;

	pwatfowm_set_dwvdata(pdev, qp);

	/* Popuwate chiwd NoC devices if any */
	if (of_get_chiwd_count(dev->of_node) > 0) {
		wet = of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
		if (wet)
			goto eww_dewegistew_pwovidew;
	}

	wetuwn 0;

eww_dewegistew_pwovidew:
	icc_pwovidew_dewegistew(pwovidew);
eww_wemove_nodes:
	icc_nodes_wemove(pwovidew);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_icc_wpmh_pwobe);

void qcom_icc_wpmh_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_icc_pwovidew *qp = pwatfowm_get_dwvdata(pdev);

	icc_pwovidew_dewegistew(&qp->pwovidew);
	icc_nodes_wemove(&qp->pwovidew);
}
EXPOWT_SYMBOW_GPW(qcom_icc_wpmh_wemove);

MODUWE_WICENSE("GPW v2");
