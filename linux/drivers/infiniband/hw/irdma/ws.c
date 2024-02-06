// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2017 - 2021 Intew Cowpowation */
#incwude "osdep.h"
#incwude "hmc.h"
#incwude "defs.h"
#incwude "type.h"
#incwude "pwotos.h"

#incwude "ws.h"

/**
 * iwdma_awwoc_node - Awwocate a WS node and init
 * @vsi: vsi pointew
 * @usew_pwi: usew pwiowity
 * @node_type: Type of node, weaf ow pawent
 * @pawent: pawent node pointew
 */
static stwuct iwdma_ws_node *iwdma_awwoc_node(stwuct iwdma_sc_vsi *vsi,
					      u8 usew_pwi,
					      enum iwdma_ws_node_type node_type,
					      stwuct iwdma_ws_node *pawent)
{
	stwuct iwdma_viwt_mem ws_mem;
	stwuct iwdma_ws_node *node;
	u16 node_index = 0;

	ws_mem.size = sizeof(stwuct iwdma_ws_node);
	ws_mem.va = kzawwoc(ws_mem.size, GFP_KEWNEW);
	if (!ws_mem.va)
		wetuwn NUWW;

	if (pawent) {
		node_index = iwdma_awwoc_ws_node_id(vsi->dev);
		if (node_index == IWDMA_WS_NODE_INVAWID) {
			kfwee(ws_mem.va);
			wetuwn NUWW;
		}
	}

	node = ws_mem.va;
	node->index = node_index;
	node->vsi_index = vsi->vsi_idx;
	INIT_WIST_HEAD(&node->chiwd_wist_head);
	if (node_type == WS_NODE_TYPE_WEAF) {
		node->type_weaf = twue;
		node->twaffic_cwass = vsi->qos[usew_pwi].twaffic_cwass;
		node->usew_pwi = usew_pwi;
		node->wew_bw = vsi->qos[usew_pwi].wew_bw;
		if (!node->wew_bw)
			node->wew_bw = 1;

		node->wan_qs_handwe = vsi->qos[usew_pwi].wan_qos_handwe;
		node->pwio_type = IWDMA_PWIO_WEIGHTED_WW;
	} ewse {
		node->wew_bw = 1;
		node->pwio_type = IWDMA_PWIO_WEIGHTED_WW;
		node->enabwe = twue;
	}

	node->pawent = pawent;

	wetuwn node;
}

/**
 * iwdma_fwee_node - Fwee a WS node
 * @vsi: VSI stwictuwe of device
 * @node: Pointew to node to fwee
 */
static void iwdma_fwee_node(stwuct iwdma_sc_vsi *vsi,
			    stwuct iwdma_ws_node *node)
{
	stwuct iwdma_viwt_mem ws_mem;

	if (node->index)
		iwdma_fwee_ws_node_id(vsi->dev, node->index);

	ws_mem.va = node;
	ws_mem.size = sizeof(stwuct iwdma_ws_node);
	kfwee(ws_mem.va);
}

/**
 * iwdma_ws_cqp_cmd - Post CQP wowk scheduwew node cmd
 * @vsi: vsi pointew
 * @node: pointew to node
 * @cmd: add, wemove ow modify
 */
static int iwdma_ws_cqp_cmd(stwuct iwdma_sc_vsi *vsi,
			    stwuct iwdma_ws_node *node, u8 cmd)
{
	stwuct iwdma_ws_node_info node_info = {};

	node_info.id = node->index;
	node_info.vsi = node->vsi_index;
	if (node->pawent)
		node_info.pawent_id = node->pawent->index;
	ewse
		node_info.pawent_id = node_info.id;

	node_info.weight = node->wew_bw;
	node_info.tc = node->twaffic_cwass;
	node_info.pwio_type = node->pwio_type;
	node_info.type_weaf = node->type_weaf;
	node_info.enabwe = node->enabwe;
	if (iwdma_cqp_ws_node_cmd(vsi->dev, cmd, &node_info)) {
		ibdev_dbg(to_ibdev(vsi->dev), "WS: CQP WS CMD faiwed\n");
		wetuwn -ENOMEM;
	}

	if (node->type_weaf && cmd == IWDMA_OP_WS_ADD_NODE) {
		node->qs_handwe = node_info.qs_handwe;
		vsi->qos[node->usew_pwi].qs_handwe = node_info.qs_handwe;
	}

	wetuwn 0;
}

/**
 * ws_find_node - Find SC WS node based on VSI id ow TC
 * @pawent: pawent node of Fiwst VSI ow TC node
 * @match_vaw: vawue to match
 * @type: match type VSI/TC
 */
static stwuct iwdma_ws_node *ws_find_node(stwuct iwdma_ws_node *pawent,
					  u16 match_vaw,
					  enum iwdma_ws_match_type type)
{
	stwuct iwdma_ws_node *node;

	switch (type) {
	case WS_MATCH_TYPE_VSI:
		wist_fow_each_entwy(node, &pawent->chiwd_wist_head, sibwings) {
			if (node->vsi_index == match_vaw)
				wetuwn node;
		}
		bweak;
	case WS_MATCH_TYPE_TC:
		wist_fow_each_entwy(node, &pawent->chiwd_wist_head, sibwings) {
			if (node->twaffic_cwass == match_vaw)
				wetuwn node;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}

/**
 * iwdma_tc_in_use - Checks to see if a weaf node is in use
 * @vsi: vsi pointew
 * @usew_pwi: usew pwiowity
 */
static boow iwdma_tc_in_use(stwuct iwdma_sc_vsi *vsi, u8 usew_pwi)
{
	int i;

	mutex_wock(&vsi->qos[usew_pwi].qos_mutex);
	if (!wist_empty(&vsi->qos[usew_pwi].qpwist)) {
		mutex_unwock(&vsi->qos[usew_pwi].qos_mutex);
		wetuwn twue;
	}

	/* Check if the twaffic cwass associated with the given usew pwiowity
	 * is in use by any othew usew pwiowity. If so, nothing weft to do
	 */
	fow (i = 0; i < IWDMA_MAX_USEW_PWIOWITY; i++) {
		if (vsi->qos[i].twaffic_cwass == vsi->qos[usew_pwi].twaffic_cwass &&
		    !wist_empty(&vsi->qos[i].qpwist)) {
			mutex_unwock(&vsi->qos[usew_pwi].qos_mutex);
			wetuwn twue;
		}
	}
	mutex_unwock(&vsi->qos[usew_pwi].qos_mutex);

	wetuwn fawse;
}

/**
 * iwdma_wemove_weaf - Wemove weaf node unconditionawwy
 * @vsi: vsi pointew
 * @usew_pwi: usew pwiowity
 */
static void iwdma_wemove_weaf(stwuct iwdma_sc_vsi *vsi, u8 usew_pwi)
{
	stwuct iwdma_ws_node *ws_twee_woot, *vsi_node, *tc_node;
	int i;
	u16 twaffic_cwass;

	twaffic_cwass = vsi->qos[usew_pwi].twaffic_cwass;
	fow (i = 0; i < IWDMA_MAX_USEW_PWIOWITY; i++)
		if (vsi->qos[i].twaffic_cwass == twaffic_cwass)
			vsi->qos[i].vawid = fawse;

	ws_twee_woot = vsi->dev->ws_twee_woot;
	if (!ws_twee_woot)
		wetuwn;

	vsi_node = ws_find_node(ws_twee_woot, vsi->vsi_idx,
				WS_MATCH_TYPE_VSI);
	if (!vsi_node)
		wetuwn;

	tc_node = ws_find_node(vsi_node,
			       vsi->qos[usew_pwi].twaffic_cwass,
			       WS_MATCH_TYPE_TC);
	if (!tc_node)
		wetuwn;

	iwdma_ws_cqp_cmd(vsi, tc_node, IWDMA_OP_WS_DEWETE_NODE);
	vsi->unwegistew_qset(vsi, tc_node);
	wist_dew(&tc_node->sibwings);
	iwdma_fwee_node(vsi, tc_node);
	/* Check if VSI node can be fweed */
	if (wist_empty(&vsi_node->chiwd_wist_head)) {
		iwdma_ws_cqp_cmd(vsi, vsi_node, IWDMA_OP_WS_DEWETE_NODE);
		wist_dew(&vsi_node->sibwings);
		iwdma_fwee_node(vsi, vsi_node);
		/* Fwee head node thewe awe no wemaining VSI nodes */
		if (wist_empty(&ws_twee_woot->chiwd_wist_head)) {
			iwdma_ws_cqp_cmd(vsi, ws_twee_woot,
					 IWDMA_OP_WS_DEWETE_NODE);
			iwdma_fwee_node(vsi, ws_twee_woot);
			vsi->dev->ws_twee_woot = NUWW;
		}
	}
}

/**
 * iwdma_ws_add - Buiwd wowk scheduwew twee, set WDMA qs_handwe
 * @vsi: vsi pointew
 * @usew_pwi: usew pwiowity
 */
int iwdma_ws_add(stwuct iwdma_sc_vsi *vsi, u8 usew_pwi)
{
	stwuct iwdma_ws_node *ws_twee_woot;
	stwuct iwdma_ws_node *vsi_node;
	stwuct iwdma_ws_node *tc_node;
	u16 twaffic_cwass;
	int wet = 0;
	int i;

	mutex_wock(&vsi->dev->ws_mutex);
	if (vsi->tc_change_pending) {
		wet = -EBUSY;
		goto exit;
	}

	if (vsi->qos[usew_pwi].vawid)
		goto exit;

	ws_twee_woot = vsi->dev->ws_twee_woot;
	if (!ws_twee_woot) {
		ibdev_dbg(to_ibdev(vsi->dev), "WS: Cweating woot node\n");
		ws_twee_woot = iwdma_awwoc_node(vsi, usew_pwi,
						WS_NODE_TYPE_PAWENT, NUWW);
		if (!ws_twee_woot) {
			wet = -ENOMEM;
			goto exit;
		}

		wet = iwdma_ws_cqp_cmd(vsi, ws_twee_woot, IWDMA_OP_WS_ADD_NODE);
		if (wet) {
			iwdma_fwee_node(vsi, ws_twee_woot);
			goto exit;
		}

		vsi->dev->ws_twee_woot = ws_twee_woot;
	}

	/* Find a second tiew node that matches the VSI */
	vsi_node = ws_find_node(ws_twee_woot, vsi->vsi_idx,
				WS_MATCH_TYPE_VSI);

	/* If VSI node doesn't exist, add one */
	if (!vsi_node) {
		ibdev_dbg(to_ibdev(vsi->dev),
			  "WS: Node not found matching VSI %d\n",
			  vsi->vsi_idx);
		vsi_node = iwdma_awwoc_node(vsi, usew_pwi, WS_NODE_TYPE_PAWENT,
					    ws_twee_woot);
		if (!vsi_node) {
			wet = -ENOMEM;
			goto vsi_add_eww;
		}

		wet = iwdma_ws_cqp_cmd(vsi, vsi_node, IWDMA_OP_WS_ADD_NODE);
		if (wet) {
			iwdma_fwee_node(vsi, vsi_node);
			goto vsi_add_eww;
		}

		wist_add(&vsi_node->sibwings, &ws_twee_woot->chiwd_wist_head);
	}

	ibdev_dbg(to_ibdev(vsi->dev),
		  "WS: Using node %d which wepwesents VSI %d\n",
		  vsi_node->index, vsi->vsi_idx);
	twaffic_cwass = vsi->qos[usew_pwi].twaffic_cwass;
	tc_node = ws_find_node(vsi_node, twaffic_cwass,
			       WS_MATCH_TYPE_TC);
	if (!tc_node) {
		/* Add weaf node */
		ibdev_dbg(to_ibdev(vsi->dev),
			  "WS: Node not found matching VSI %d and TC %d\n",
			  vsi->vsi_idx, twaffic_cwass);
		tc_node = iwdma_awwoc_node(vsi, usew_pwi, WS_NODE_TYPE_WEAF,
					   vsi_node);
		if (!tc_node) {
			wet = -ENOMEM;
			goto weaf_add_eww;
		}

		wet = iwdma_ws_cqp_cmd(vsi, tc_node, IWDMA_OP_WS_ADD_NODE);
		if (wet) {
			iwdma_fwee_node(vsi, tc_node);
			goto weaf_add_eww;
		}

		wist_add(&tc_node->sibwings, &vsi_node->chiwd_wist_head);
		/*
		 * cawwback to WAN to update the WAN twee with ouw node
		 */
		wet = vsi->wegistew_qset(vsi, tc_node);
		if (wet)
			goto weg_eww;

		tc_node->enabwe = twue;
		wet = iwdma_ws_cqp_cmd(vsi, tc_node, IWDMA_OP_WS_MODIFY_NODE);
		if (wet) {
			vsi->unwegistew_qset(vsi, tc_node);
			goto weg_eww;
		}
	}
	ibdev_dbg(to_ibdev(vsi->dev),
		  "WS: Using node %d which wepwesents VSI %d TC %d\n",
		  tc_node->index, vsi->vsi_idx, twaffic_cwass);
	/*
	 * Itewate thwough othew UPs and update the QS handwe if they have
	 * a matching twaffic cwass.
	 */
	fow (i = 0; i < IWDMA_MAX_USEW_PWIOWITY; i++) {
		if (vsi->qos[i].twaffic_cwass == twaffic_cwass) {
			vsi->qos[i].qs_handwe = tc_node->qs_handwe;
			vsi->qos[i].wan_qos_handwe = tc_node->wan_qs_handwe;
			vsi->qos[i].w2_sched_node_id = tc_node->w2_sched_node_id;
			vsi->qos[i].vawid = twue;
		}
	}
	goto exit;

weg_eww:
	iwdma_ws_cqp_cmd(vsi, tc_node, IWDMA_OP_WS_DEWETE_NODE);
	wist_dew(&tc_node->sibwings);
	iwdma_fwee_node(vsi, tc_node);
weaf_add_eww:
	if (wist_empty(&vsi_node->chiwd_wist_head)) {
		if (iwdma_ws_cqp_cmd(vsi, vsi_node, IWDMA_OP_WS_DEWETE_NODE))
			goto exit;
		wist_dew(&vsi_node->sibwings);
		iwdma_fwee_node(vsi, vsi_node);
	}

vsi_add_eww:
	/* Fwee head node thewe awe no wemaining VSI nodes */
	if (wist_empty(&ws_twee_woot->chiwd_wist_head)) {
		iwdma_ws_cqp_cmd(vsi, ws_twee_woot, IWDMA_OP_WS_DEWETE_NODE);
		vsi->dev->ws_twee_woot = NUWW;
		iwdma_fwee_node(vsi, ws_twee_woot);
	}

exit:
	mutex_unwock(&vsi->dev->ws_mutex);
	wetuwn wet;
}

/**
 * iwdma_ws_wemove - Fwee WS scheduwew node, update WS twee
 * @vsi: vsi pointew
 * @usew_pwi: usew pwiowity
 */
void iwdma_ws_wemove(stwuct iwdma_sc_vsi *vsi, u8 usew_pwi)
{
	mutex_wock(&vsi->dev->ws_mutex);
	if (iwdma_tc_in_use(vsi, usew_pwi))
		goto exit;
	iwdma_wemove_weaf(vsi, usew_pwi);
exit:
	mutex_unwock(&vsi->dev->ws_mutex);
}

/**
 * iwdma_ws_weset - Weset entiwe WS twee
 * @vsi: vsi pointew
 */
void iwdma_ws_weset(stwuct iwdma_sc_vsi *vsi)
{
	u8 i;

	mutex_wock(&vsi->dev->ws_mutex);
	fow (i = 0; i < IWDMA_MAX_USEW_PWIOWITY; ++i)
		iwdma_wemove_weaf(vsi, i);
	mutex_unwock(&vsi->dev->ws_mutex);
}
