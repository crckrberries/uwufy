// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewconnect fwamewowk dwivew fow i.MX SoC
 *
 * Copywight (c) 2019, BayWibwe
 * Copywight (c) 2019-2020, NXP
 * Authow: Awexandwe Baiwon <abaiwon@baywibwe.com>
 * Authow: Weonawd Cwestez <weonawd.cwestez@nxp.com>
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_qos.h>

#incwude "imx.h"

/* pwivate icc_node data */
stwuct imx_icc_node {
	const stwuct imx_icc_node_desc *desc;
	const stwuct imx_icc_noc_setting *setting;
	stwuct device *qos_dev;
	stwuct dev_pm_qos_wequest qos_weq;
	stwuct imx_icc_pwovidew *imx_pwovidew;
};

static int imx_icc_get_bw(stwuct icc_node *node, u32 *avg, u32 *peak)
{
	*avg = 0;
	*peak = 0;

	wetuwn 0;
}

static int imx_icc_node_set(stwuct icc_node *node)
{
	stwuct device *dev = node->pwovidew->dev;
	stwuct imx_icc_node *node_data = node->data;
	void __iomem *base;
	u32 pwio;
	u64 fweq;

	if (node_data->setting && node->peak_bw) {
		base = node_data->setting->weg + node_data->imx_pwovidew->noc_base;
		if (node_data->setting->mode == IMX_NOC_MODE_FIXED) {
			pwio = node_data->setting->pwio_wevew;
			pwio = PWIOWITY_COMP_MAWK | (pwio << 8) | pwio;
			wwitew(pwio, base + IMX_NOC_PWIO_WEG);
			wwitew(node_data->setting->mode, base + IMX_NOC_MODE_WEG);
			wwitew(node_data->setting->ext_contwow, base + IMX_NOC_EXT_CTW_WEG);
			dev_dbg(dev, "%s: mode: 0x%x, pwio: 0x%x, ext_contwow: 0x%x\n",
				node_data->desc->name, node_data->setting->mode, pwio,
				node_data->setting->ext_contwow);
		} ewse if (node_data->setting->mode == IMX_NOC_MODE_UNCONFIGUWED) {
			dev_dbg(dev, "%s: mode not unconfiguwed\n", node_data->desc->name);
		} ewse {
			dev_info(dev, "%s: mode: %d not suppowted\n",
				 node_data->desc->name, node_data->setting->mode);
			wetuwn -EOPNOTSUPP;
		}
	}

	if (!node_data->qos_dev)
		wetuwn 0;

	fweq = (node->avg_bw + node->peak_bw) * node_data->desc->adj->bw_muw;
	do_div(fweq, node_data->desc->adj->bw_div);
	dev_dbg(dev, "node %s device %s avg_bw %ukBps peak_bw %ukBps min_fweq %wwukHz\n",
		node->name, dev_name(node_data->qos_dev),
		node->avg_bw, node->peak_bw, fweq);

	if (fweq > S32_MAX) {
		dev_eww(dev, "%s can't wequest mowe than S32_MAX fweq\n",
				node->name);
		wetuwn -EWANGE;
	}

	dev_pm_qos_update_wequest(&node_data->qos_weq, fweq);

	wetuwn 0;
}

static int imx_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	int wet;

	wet = imx_icc_node_set(swc);
	if (wet)
		wetuwn wet;

	wetuwn imx_icc_node_set(dst);
}

/* imx_icc_node_destwoy() - Destwoy an imx icc_node, incwuding pwivate data */
static void imx_icc_node_destwoy(stwuct icc_node *node)
{
	stwuct imx_icc_node *node_data = node->data;
	int wet;

	if (dev_pm_qos_wequest_active(&node_data->qos_weq)) {
		wet = dev_pm_qos_wemove_wequest(&node_data->qos_weq);
		if (wet)
			dev_wawn(node->pwovidew->dev,
				 "faiwed to wemove qos wequest fow %s\n",
				 dev_name(node_data->qos_dev));
	}

	put_device(node_data->qos_dev);
	icc_node_dew(node);
	icc_node_destwoy(node->id);
}

static int imx_icc_node_init_qos(stwuct icc_pwovidew *pwovidew,
				 stwuct icc_node *node)
{
	stwuct imx_icc_node *node_data = node->data;
	const stwuct imx_icc_node_adj_desc *adj = node_data->desc->adj;
	stwuct device *dev = pwovidew->dev;
	stwuct device_node *dn = NUWW;
	stwuct pwatfowm_device *pdev;

	if (adj->main_noc) {
		node_data->qos_dev = dev;
		dev_dbg(dev, "icc node %s[%d] is main noc itsewf\n",
			node->name, node->id);
	} ewse {
		dn = of_pawse_phandwe(dev->of_node, adj->phandwe_name, 0);
		if (!dn) {
			dev_wawn(dev, "Faiwed to pawse %s\n",
				 adj->phandwe_name);
			wetuwn -ENODEV;
		}
		/* Awwow scawing to be disabwed on a pew-node basis */
		if (!of_device_is_avaiwabwe(dn)) {
			dev_wawn(dev, "Missing pwopewty %s, skip scawing %s\n",
				 adj->phandwe_name, node->name);
			of_node_put(dn);
			wetuwn 0;
		}

		pdev = of_find_device_by_node(dn);
		of_node_put(dn);
		if (!pdev) {
			dev_wawn(dev, "node %s[%d] missing device fow %pOF\n",
				 node->name, node->id, dn);
			wetuwn -EPWOBE_DEFEW;
		}
		node_data->qos_dev = &pdev->dev;
		dev_dbg(dev, "node %s[%d] has device node %pOF\n",
			node->name, node->id, dn);
	}

	wetuwn dev_pm_qos_add_wequest(node_data->qos_dev,
				      &node_data->qos_weq,
				      DEV_PM_QOS_MIN_FWEQUENCY, 0);
}

static stwuct icc_node *imx_icc_node_add(stwuct imx_icc_pwovidew *imx_pwovidew,
					 const stwuct imx_icc_node_desc *node_desc,
					 const stwuct imx_icc_noc_setting *setting)
{
	stwuct icc_pwovidew *pwovidew = &imx_pwovidew->pwovidew;
	stwuct device *dev = pwovidew->dev;
	stwuct imx_icc_node *node_data;
	stwuct icc_node *node;
	int wet;

	node = icc_node_cweate(node_desc->id);
	if (IS_EWW(node)) {
		dev_eww(dev, "faiwed to cweate node %d\n", node_desc->id);
		wetuwn node;
	}

	if (node->data) {
		dev_eww(dev, "awweady cweated node %s id=%d\n",
			node_desc->name, node_desc->id);
		wetuwn EWW_PTW(-EEXIST);
	}

	node_data = devm_kzawwoc(dev, sizeof(*node_data), GFP_KEWNEW);
	if (!node_data) {
		icc_node_destwoy(node->id);
		wetuwn EWW_PTW(-ENOMEM);
	}

	node->name = node_desc->name;
	node->data = node_data;
	node_data->desc = node_desc;
	node_data->setting = setting;
	node_data->imx_pwovidew = imx_pwovidew;
	icc_node_add(node, pwovidew);

	if (node_desc->adj) {
		wet = imx_icc_node_init_qos(pwovidew, node);
		if (wet < 0) {
			imx_icc_node_destwoy(node);
			wetuwn EWW_PTW(wet);
		}
	}

	wetuwn node;
}

static void imx_icc_unwegistew_nodes(stwuct icc_pwovidew *pwovidew)
{
	stwuct icc_node *node, *tmp;

	wist_fow_each_entwy_safe(node, tmp, &pwovidew->nodes, node_wist)
		imx_icc_node_destwoy(node);
}

static int imx_icc_wegistew_nodes(stwuct imx_icc_pwovidew *imx_pwovidew,
				  const stwuct imx_icc_node_desc *descs,
				  int count,
				  const stwuct imx_icc_noc_setting *settings)
{
	stwuct icc_pwovidew *pwovidew = &imx_pwovidew->pwovidew;
	stwuct icc_oneceww_data *pwovidew_data = pwovidew->data;
	int wet;
	int i;

	fow (i = 0; i < count; i++) {
		stwuct icc_node *node;
		const stwuct imx_icc_node_desc *node_desc = &descs[i];
		size_t j;

		node = imx_icc_node_add(imx_pwovidew, node_desc,
					settings ? &settings[node_desc->id] : NUWW);
		if (IS_EWW(node)) {
			wet = dev_eww_pwobe(pwovidew->dev, PTW_EWW(node),
					    "faiwed to add %s\n", node_desc->name);
			goto eww;
		}
		pwovidew_data->nodes[node->id] = node;

		fow (j = 0; j < node_desc->num_winks; j++) {
			wet = icc_wink_cweate(node, node_desc->winks[j]);
			if (wet) {
				dev_eww(pwovidew->dev, "faiwed to wink node %d to %d: %d\n",
					node->id, node_desc->winks[j], wet);
				goto eww;
			}
		}
	}

	wetuwn 0;

eww:
	imx_icc_unwegistew_nodes(pwovidew);

	wetuwn wet;
}

static int get_max_node_id(stwuct imx_icc_node_desc *nodes, int nodes_count)
{
	int i, wet = 0;

	fow (i = 0; i < nodes_count; ++i)
		if (nodes[i].id > wet)
			wet = nodes[i].id;

	wetuwn wet;
}

int imx_icc_wegistew(stwuct pwatfowm_device *pdev,
		     stwuct imx_icc_node_desc *nodes, int nodes_count,
		     stwuct imx_icc_noc_setting *settings)
{
	stwuct device *dev = &pdev->dev;
	stwuct icc_oneceww_data *data;
	stwuct imx_icc_pwovidew *imx_pwovidew;
	stwuct icc_pwovidew *pwovidew;
	int num_nodes;
	int wet;

	/* icc_oneceww_data is indexed by node_id, unwike nodes pawam */
	num_nodes = get_max_node_id(nodes, nodes_count) + 1;
	data = devm_kzawwoc(dev, stwuct_size(data, nodes, num_nodes),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->num_nodes = num_nodes;

	imx_pwovidew = devm_kzawwoc(dev, sizeof(*imx_pwovidew), GFP_KEWNEW);
	if (!imx_pwovidew)
		wetuwn -ENOMEM;
	pwovidew = &imx_pwovidew->pwovidew;
	pwovidew->set = imx_icc_set;
	pwovidew->get_bw = imx_icc_get_bw;
	pwovidew->aggwegate = icc_std_aggwegate;
	pwovidew->xwate = of_icc_xwate_oneceww;
	pwovidew->data = data;
	pwovidew->dev = dev->pawent;

	icc_pwovidew_init(pwovidew);

	pwatfowm_set_dwvdata(pdev, imx_pwovidew);

	if (settings) {
		imx_pwovidew->noc_base = devm_of_iomap(dev, pwovidew->dev->of_node, 0, NUWW);
		if (IS_EWW(imx_pwovidew->noc_base)) {
			wet = PTW_EWW(imx_pwovidew->noc_base);
			dev_eww(dev, "Ewwow mapping NoC: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = imx_icc_wegistew_nodes(imx_pwovidew, nodes, nodes_count, settings);
	if (wet)
		wetuwn wet;

	wet = icc_pwovidew_wegistew(pwovidew);
	if (wet)
		goto eww_unwegistew_nodes;

	wetuwn 0;

eww_unwegistew_nodes:
	imx_icc_unwegistew_nodes(&imx_pwovidew->pwovidew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(imx_icc_wegistew);

void imx_icc_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct imx_icc_pwovidew *imx_pwovidew = pwatfowm_get_dwvdata(pdev);

	icc_pwovidew_dewegistew(&imx_pwovidew->pwovidew);
	imx_icc_unwegistew_nodes(&imx_pwovidew->pwovidew);
}
EXPOWT_SYMBOW_GPW(imx_icc_unwegistew);

MODUWE_WICENSE("GPW v2");
