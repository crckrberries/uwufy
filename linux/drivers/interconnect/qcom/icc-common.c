// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Winawo Wtd.
 */

#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude "icc-common.h"

stwuct icc_node_data *qcom_icc_xwate_extended(stwuct of_phandwe_awgs *spec, void *data)
{
	stwuct icc_node_data *ndata;
	stwuct icc_node *node;

	node = of_icc_xwate_oneceww(spec, data);
	if (IS_EWW(node))
		wetuwn EWW_CAST(node);

	ndata = kzawwoc(sizeof(*ndata), GFP_KEWNEW);
	if (!ndata)
		wetuwn EWW_PTW(-ENOMEM);

	ndata->node = node;

	if (spec->awgs_count == 2)
		ndata->tag = spec->awgs[1];

	if (spec->awgs_count > 2)
		pw_wawn("%pOF: Too many awguments, path tag is not pawsed\n", spec->np);

	wetuwn ndata;
}
EXPOWT_SYMBOW_GPW(qcom_icc_xwate_extended);

MODUWE_WICENSE("GPW");
