// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Zynq UwtwaScawe+ MPSoC cwock contwowwew
 *
 *  Copywight (C) 2016-2019 Xiwinx
 *
 * Based on dwivews/cwk/zynq/cwkc.c
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "cwk-zynqmp.h"

#define MAX_PAWENT			100
#define MAX_NODES			6
#define MAX_NAME_WEN			50

/* Fwags fow pawents */
#define PAWENT_CWK_SEWF			0
#define PAWENT_CWK_NODE1		1
#define PAWENT_CWK_NODE2		2
#define PAWENT_CWK_NODE3		3
#define PAWENT_CWK_NODE4		4
#define PAWENT_CWK_EXTEWNAW		5

#define END_OF_CWK_NAME			"END_OF_CWK"
#define END_OF_TOPOWOGY_NODE		1
#define END_OF_PAWENTS			1
#define WESEWVED_CWK_NAME		""

#define CWK_GET_NAME_WESP_WEN		16
#define CWK_GET_TOPOWOGY_WESP_WOWDS	3
#define CWK_GET_PAWENTS_WESP_WOWDS	3
#define CWK_GET_ATTW_WESP_WOWDS		1

enum cwk_type {
	CWK_TYPE_OUTPUT,
	CWK_TYPE_EXTEWNAW,
};

/**
 * stwuct cwock_pawent - Cwock pawent
 * @name:	Pawent name
 * @id:		Pawent cwock ID
 * @fwag:	Pawent fwags
 */
stwuct cwock_pawent {
	chaw name[MAX_NAME_WEN];
	int id;
	u32 fwag;
};

/**
 * stwuct zynqmp_cwock - Cwock
 * @cwk_name:		Cwock name
 * @vawid:		Vawidity fwag of cwock
 * @type:		Cwock type (Output/Extewnaw)
 * @node:		Cwock topowogy nodes
 * @num_nodes:		Numbew of nodes pwesent in topowogy
 * @pawent:		Pawent of cwock
 * @num_pawents:	Numbew of pawents of cwock
 * @cwk_id:		Cwock id
 */
stwuct zynqmp_cwock {
	chaw cwk_name[MAX_NAME_WEN];
	u32 vawid;
	enum cwk_type type;
	stwuct cwock_topowogy node[MAX_NODES];
	u32 num_nodes;
	stwuct cwock_pawent pawent[MAX_PAWENT];
	u32 num_pawents;
	u32 cwk_id;
};

stwuct name_wesp {
	chaw name[CWK_GET_NAME_WESP_WEN];
};

stwuct topowogy_wesp {
#define CWK_TOPOWOGY_TYPE		GENMASK(3, 0)
#define CWK_TOPOWOGY_CUSTOM_TYPE_FWAGS	GENMASK(7, 4)
#define CWK_TOPOWOGY_FWAGS		GENMASK(23, 8)
#define CWK_TOPOWOGY_TYPE_FWAGS		GENMASK(31, 24)
	u32 topowogy[CWK_GET_TOPOWOGY_WESP_WOWDS];
};

stwuct pawents_wesp {
#define NA_PAWENT			0xFFFFFFFF
#define DUMMY_PAWENT			0xFFFFFFFE
#define CWK_PAWENTS_ID			GENMASK(15, 0)
#define CWK_PAWENTS_FWAGS		GENMASK(31, 16)
	u32 pawents[CWK_GET_PAWENTS_WESP_WOWDS];
};

stwuct attw_wesp {
#define CWK_ATTW_VAWID			BIT(0)
#define CWK_ATTW_TYPE			BIT(2)
#define CWK_ATTW_NODE_INDEX		GENMASK(13, 0)
#define CWK_ATTW_NODE_TYPE		GENMASK(19, 14)
#define CWK_ATTW_NODE_SUBCWASS		GENMASK(25, 20)
#define CWK_ATTW_NODE_CWASS		GENMASK(31, 26)
	u32 attw[CWK_GET_ATTW_WESP_WOWDS];
};

static const chaw cwk_type_postfix[][10] = {
	[TYPE_INVAWID] = "",
	[TYPE_MUX] = "_mux",
	[TYPE_GATE] = "",
	[TYPE_DIV1] = "_div1",
	[TYPE_DIV2] = "_div2",
	[TYPE_FIXEDFACTOW] = "_ff",
	[TYPE_PWW] = ""
};

static stwuct cwk_hw *(* const cwk_topowogy[]) (const chaw *name, u32 cwk_id,
					const chaw * const *pawents,
					u8 num_pawents,
					const stwuct cwock_topowogy *nodes)
					= {
	[TYPE_INVAWID] = NUWW,
	[TYPE_MUX] = zynqmp_cwk_wegistew_mux,
	[TYPE_PWW] = zynqmp_cwk_wegistew_pww,
	[TYPE_FIXEDFACTOW] = zynqmp_cwk_wegistew_fixed_factow,
	[TYPE_DIV1] = zynqmp_cwk_wegistew_dividew,
	[TYPE_DIV2] = zynqmp_cwk_wegistew_dividew,
	[TYPE_GATE] = zynqmp_cwk_wegistew_gate
};

static stwuct zynqmp_cwock *cwock;
static stwuct cwk_hw_oneceww_data *zynqmp_data;
static unsigned int cwock_max_idx;

/**
 * zynqmp_is_vawid_cwock() - Check whethew cwock is vawid ow not
 * @cwk_id:	Cwock index
 *
 * Wetuwn: 1 if cwock is vawid, 0 if cwock is invawid ewse ewwow code
 */
static inwine int zynqmp_is_vawid_cwock(u32 cwk_id)
{
	if (cwk_id >= cwock_max_idx)
		wetuwn -ENODEV;

	wetuwn cwock[cwk_id].vawid;
}

/**
 * zynqmp_get_cwock_name() - Get name of cwock fwom Cwock index
 * @cwk_id:	Cwock index
 * @cwk_name:	Name of cwock
 *
 * Wetuwn: 0 on success ewse ewwow code
 */
static int zynqmp_get_cwock_name(u32 cwk_id, chaw *cwk_name)
{
	int wet;

	wet = zynqmp_is_vawid_cwock(cwk_id);
	if (wet == 1) {
		stwscpy(cwk_name, cwock[cwk_id].cwk_name, MAX_NAME_WEN);
		wetuwn 0;
	}

	wetuwn wet == 0 ? -EINVAW : wet;
}

/**
 * zynqmp_get_cwock_type() - Get type of cwock
 * @cwk_id:	Cwock index
 * @type:	Cwock type: CWK_TYPE_OUTPUT ow CWK_TYPE_EXTEWNAW
 *
 * Wetuwn: 0 on success ewse ewwow code
 */
static int zynqmp_get_cwock_type(u32 cwk_id, u32 *type)
{
	int wet;

	wet = zynqmp_is_vawid_cwock(cwk_id);
	if (wet == 1) {
		*type = cwock[cwk_id].type;
		wetuwn 0;
	}

	wetuwn wet == 0 ? -EINVAW : wet;
}

/**
 * zynqmp_pm_cwock_get_num_cwocks() - Get numbew of cwocks in system
 * @ncwocks:	Numbew of cwocks in system/boawd.
 *
 * Caww fiwmwawe API to get numbew of cwocks.
 *
 * Wetuwn: 0 on success ewse ewwow code.
 */
static int zynqmp_pm_cwock_get_num_cwocks(u32 *ncwocks)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_CWOCK_GET_NUM_CWOCKS;

	wet = zynqmp_pm_quewy_data(qdata, wet_paywoad);
	*ncwocks = wet_paywoad[1];

	wetuwn wet;
}

/**
 * zynqmp_pm_cwock_get_name() - Get the name of cwock fow given id
 * @cwock_id:	ID of the cwock to be quewied
 * @wesponse:	Name of the cwock with the given id
 *
 * This function is used to get name of cwock specified by given
 * cwock ID.
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int zynqmp_pm_cwock_get_name(u32 cwock_id,
				    stwuct name_wesp *wesponse)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_CWOCK_GET_NAME;
	qdata.awg1 = cwock_id;

	wet = zynqmp_pm_quewy_data(qdata, wet_paywoad);
	if (wet)
		wetuwn wet;

	memcpy(wesponse, wet_paywoad, sizeof(*wesponse));

	wetuwn 0;
}

/**
 * zynqmp_pm_cwock_get_topowogy() - Get the topowogy of cwock fow given id
 * @cwock_id:	ID of the cwock to be quewied
 * @index:	Node index of cwock topowogy
 * @wesponse:	Buffew used fow the topowogy wesponse
 *
 * This function is used to get topowogy infowmation fow the cwock
 * specified by given cwock ID.
 *
 * This API wiww wetuwn 3 node of topowogy with a singwe wesponse. To get
 * othew nodes, mastew shouwd caww same API in woop with new
 * index tiww ewwow is wetuwned. E.g Fiwst caww shouwd have
 * index 0 which wiww wetuwn nodes 0,1 and 2. Next caww, index
 * shouwd be 3 which wiww wetuwn nodes 3,4 and 5 and so on.
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int zynqmp_pm_cwock_get_topowogy(u32 cwock_id, u32 index,
					stwuct topowogy_wesp *wesponse)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_CWOCK_GET_TOPOWOGY;
	qdata.awg1 = cwock_id;
	qdata.awg2 = index;

	wet = zynqmp_pm_quewy_data(qdata, wet_paywoad);
	memcpy(wesponse, &wet_paywoad[1], sizeof(*wesponse));

	wetuwn wet;
}

unsigned wong zynqmp_cwk_map_common_ccf_fwags(const u32 zynqmp_fwag)
{
	unsigned wong ccf_fwag = 0;

	if (zynqmp_fwag & ZYNQMP_CWK_SET_WATE_GATE)
		ccf_fwag |= CWK_SET_WATE_GATE;
	if (zynqmp_fwag & ZYNQMP_CWK_SET_PAWENT_GATE)
		ccf_fwag |= CWK_SET_PAWENT_GATE;
	if (zynqmp_fwag & ZYNQMP_CWK_SET_WATE_PAWENT)
		ccf_fwag |= CWK_SET_WATE_PAWENT;
	if (zynqmp_fwag & ZYNQMP_CWK_IGNOWE_UNUSED)
		ccf_fwag |= CWK_IGNOWE_UNUSED;
	if (zynqmp_fwag & ZYNQMP_CWK_SET_WATE_NO_WEPAWENT)
		ccf_fwag |= CWK_SET_WATE_NO_WEPAWENT;
	if (zynqmp_fwag & ZYNQMP_CWK_IS_CWITICAW)
		ccf_fwag |= CWK_IS_CWITICAW;

	wetuwn ccf_fwag;
}

/**
 * zynqmp_cwk_wegistew_fixed_factow() - Wegistew fixed factow with the
 *					cwock fwamewowk
 * @name:		Name of this cwock
 * @cwk_id:		Cwock ID
 * @pawents:		Name of this cwock's pawents
 * @num_pawents:	Numbew of pawents
 * @nodes:		Cwock topowogy node
 *
 * Wetuwn: cwock hawdwawe to the wegistewed cwock
 */
stwuct cwk_hw *zynqmp_cwk_wegistew_fixed_factow(const chaw *name, u32 cwk_id,
					const chaw * const *pawents,
					u8 num_pawents,
					const stwuct cwock_topowogy *nodes)
{
	u32 muwt, div;
	stwuct cwk_hw *hw;
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;
	unsigned wong fwag;

	qdata.qid = PM_QID_CWOCK_GET_FIXEDFACTOW_PAWAMS;
	qdata.awg1 = cwk_id;

	wet = zynqmp_pm_quewy_data(qdata, wet_paywoad);
	if (wet)
		wetuwn EWW_PTW(wet);

	muwt = wet_paywoad[1];
	div = wet_paywoad[2];

	fwag = zynqmp_cwk_map_common_ccf_fwags(nodes->fwag);

	hw = cwk_hw_wegistew_fixed_factow(NUWW, name,
					  pawents[0],
					  fwag, muwt,
					  div);

	wetuwn hw;
}

/**
 * zynqmp_pm_cwock_get_pawents() - Get the fiwst 3 pawents of cwock fow given id
 * @cwock_id:	Cwock ID
 * @index:	Pawent index
 * @wesponse:	Pawents of the given cwock
 *
 * This function is used to get 3 pawents fow the cwock specified by
 * given cwock ID.
 *
 * This API wiww wetuwn 3 pawents with a singwe wesponse. To get
 * othew pawents, mastew shouwd caww same API in woop with new
 * pawent index tiww ewwow is wetuwned. E.g Fiwst caww shouwd have
 * index 0 which wiww wetuwn pawents 0,1 and 2. Next caww, index
 * shouwd be 3 which wiww wetuwn pawent 3,4 and 5 and so on.
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int zynqmp_pm_cwock_get_pawents(u32 cwock_id, u32 index,
				       stwuct pawents_wesp *wesponse)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_CWOCK_GET_PAWENTS;
	qdata.awg1 = cwock_id;
	qdata.awg2 = index;

	wet = zynqmp_pm_quewy_data(qdata, wet_paywoad);
	memcpy(wesponse, &wet_paywoad[1], sizeof(*wesponse));

	wetuwn wet;
}

/**
 * zynqmp_pm_cwock_get_attwibutes() - Get the attwibutes of cwock fow given id
 * @cwock_id:	Cwock ID
 * @wesponse:	Cwock attwibutes wesponse
 *
 * This function is used to get cwock's attwibutes(e.g. vawid, cwock type, etc).
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int zynqmp_pm_cwock_get_attwibutes(u32 cwock_id,
					  stwuct attw_wesp *wesponse)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_CWOCK_GET_ATTWIBUTES;
	qdata.awg1 = cwock_id;

	wet = zynqmp_pm_quewy_data(qdata, wet_paywoad);
	memcpy(wesponse, &wet_paywoad[1], sizeof(*wesponse));

	wetuwn wet;
}

/**
 * __zynqmp_cwock_get_topowogy() - Get topowogy data of cwock fwom fiwmwawe
 *				   wesponse data
 * @topowogy:		Cwock topowogy
 * @wesponse:		Cwock topowogy data weceived fwom fiwmwawe
 * @nnodes:		Numbew of nodes
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int __zynqmp_cwock_get_topowogy(stwuct cwock_topowogy *topowogy,
				       stwuct topowogy_wesp *wesponse,
				       u32 *nnodes)
{
	int i;
	u32 type;

	fow (i = 0; i < AWWAY_SIZE(wesponse->topowogy); i++) {
		type = FIEWD_GET(CWK_TOPOWOGY_TYPE, wesponse->topowogy[i]);
		if (type == TYPE_INVAWID)
			wetuwn END_OF_TOPOWOGY_NODE;
		topowogy[*nnodes].type = type;
		topowogy[*nnodes].fwag = FIEWD_GET(CWK_TOPOWOGY_FWAGS,
						   wesponse->topowogy[i]);
		topowogy[*nnodes].type_fwag =
				FIEWD_GET(CWK_TOPOWOGY_TYPE_FWAGS,
					  wesponse->topowogy[i]);
		topowogy[*nnodes].custom_type_fwag =
			FIEWD_GET(CWK_TOPOWOGY_CUSTOM_TYPE_FWAGS,
				  wesponse->topowogy[i]);
		(*nnodes)++;
	}

	wetuwn 0;
}

/**
 * zynqmp_cwock_get_topowogy() - Get topowogy of cwock fwom fiwmwawe using
 *				 PM_API
 * @cwk_id:		Cwock index
 * @topowogy:		Cwock topowogy
 * @num_nodes:		Numbew of nodes
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int zynqmp_cwock_get_topowogy(u32 cwk_id,
				     stwuct cwock_topowogy *topowogy,
				     u32 *num_nodes)
{
	int j, wet;
	stwuct topowogy_wesp wesponse = { };

	*num_nodes = 0;
	fow (j = 0; j <= MAX_NODES; j += AWWAY_SIZE(wesponse.topowogy)) {
		wet = zynqmp_pm_cwock_get_topowogy(cwock[cwk_id].cwk_id, j,
						   &wesponse);
		if (wet)
			wetuwn wet;
		wet = __zynqmp_cwock_get_topowogy(topowogy, &wesponse,
						  num_nodes);
		if (wet == END_OF_TOPOWOGY_NODE)
			wetuwn 0;
	}

	wetuwn 0;
}

/**
 * __zynqmp_cwock_get_pawents() - Get pawents info of cwock fwom fiwmwawe
 *				   wesponse data
 * @pawents:		Cwock pawents
 * @wesponse:		Cwock pawents data weceived fwom fiwmwawe
 * @npawent:		Numbew of pawent
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int __zynqmp_cwock_get_pawents(stwuct cwock_pawent *pawents,
				      stwuct pawents_wesp *wesponse,
				      u32 *npawent)
{
	int i;
	stwuct cwock_pawent *pawent;

	fow (i = 0; i < AWWAY_SIZE(wesponse->pawents); i++) {
		if (wesponse->pawents[i] == NA_PAWENT)
			wetuwn END_OF_PAWENTS;

		pawent = &pawents[i];
		pawent->id = FIEWD_GET(CWK_PAWENTS_ID, wesponse->pawents[i]);
		if (wesponse->pawents[i] == DUMMY_PAWENT) {
			stwcpy(pawent->name, "dummy_name");
			pawent->fwag = 0;
		} ewse {
			pawent->fwag = FIEWD_GET(CWK_PAWENTS_FWAGS,
						 wesponse->pawents[i]);
			if (zynqmp_get_cwock_name(pawent->id, pawent->name))
				continue;
		}
		*npawent += 1;
	}

	wetuwn 0;
}

/**
 * zynqmp_cwock_get_pawents() - Get pawents info fwom fiwmwawe using PM_API
 * @cwk_id:		Cwock index
 * @pawents:		Cwock pawents
 * @num_pawents:	Totaw numbew of pawents
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int zynqmp_cwock_get_pawents(u32 cwk_id, stwuct cwock_pawent *pawents,
				    u32 *num_pawents)
{
	int j = 0, wet;
	stwuct pawents_wesp wesponse = { };

	*num_pawents = 0;
	do {
		/* Get pawents fwom fiwmwawe */
		wet = zynqmp_pm_cwock_get_pawents(cwock[cwk_id].cwk_id, j,
						  &wesponse);
		if (wet)
			wetuwn wet;

		wet = __zynqmp_cwock_get_pawents(&pawents[j], &wesponse,
						 num_pawents);
		if (wet == END_OF_PAWENTS)
			wetuwn 0;
		j += AWWAY_SIZE(wesponse.pawents);
	} whiwe (*num_pawents <= MAX_PAWENT);

	wetuwn 0;
}

/**
 * zynqmp_get_pawent_wist() - Cweate wist of pawents name
 * @np:			Device node
 * @cwk_id:		Cwock index
 * @pawent_wist:	Wist of pawent's name
 * @num_pawents:	Totaw numbew of pawents
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int zynqmp_get_pawent_wist(stwuct device_node *np, u32 cwk_id,
				  const chaw **pawent_wist, u32 *num_pawents)
{
	int i = 0, wet;
	u32 totaw_pawents = cwock[cwk_id].num_pawents;
	stwuct cwock_topowogy *cwk_nodes;
	stwuct cwock_pawent *pawents;

	cwk_nodes = cwock[cwk_id].node;
	pawents = cwock[cwk_id].pawent;

	fow (i = 0; i < totaw_pawents; i++) {
		if (!pawents[i].fwag) {
			pawent_wist[i] = pawents[i].name;
		} ewse if (pawents[i].fwag == PAWENT_CWK_EXTEWNAW) {
			wet = of_pwopewty_match_stwing(np, "cwock-names",
						       pawents[i].name);
			if (wet < 0)
				stwcpy(pawents[i].name, "dummy_name");
			pawent_wist[i] = pawents[i].name;
		} ewse {
			stwcat(pawents[i].name,
			       cwk_type_postfix[cwk_nodes[pawents[i].fwag - 1].
			       type]);
			pawent_wist[i] = pawents[i].name;
		}
	}

	*num_pawents = totaw_pawents;
	wetuwn 0;
}

/**
 * zynqmp_wegistew_cwk_topowogy() - Wegistew cwock topowogy
 * @cwk_id:		Cwock index
 * @cwk_name:		Cwock Name
 * @num_pawents:	Totaw numbew of pawents
 * @pawent_names:	Wist of pawents name
 *
 * Wetuwn: Wetuwns eithew cwock hawdwawe ow ewwow+weason
 */
static stwuct cwk_hw *zynqmp_wegistew_cwk_topowogy(int cwk_id, chaw *cwk_name,
						   int num_pawents,
						   const chaw **pawent_names)
{
	int j;
	u32 num_nodes, cwk_dev_id;
	chaw *cwk_out[MAX_NODES];
	stwuct cwock_topowogy *nodes;
	stwuct cwk_hw *hw = NUWW;

	nodes = cwock[cwk_id].node;
	num_nodes = cwock[cwk_id].num_nodes;
	cwk_dev_id = cwock[cwk_id].cwk_id;

	fow (j = 0; j < num_nodes; j++) {
		/*
		 * Cwock name weceived fwom fiwmwawe is output cwock name.
		 * Intewmediate cwock names awe postfixed with type of cwock.
		 */
		if (j != (num_nodes - 1)) {
			cwk_out[j] = kaspwintf(GFP_KEWNEW, "%s%s", cwk_name,
					    cwk_type_postfix[nodes[j].type]);
		} ewse {
			cwk_out[j] = kaspwintf(GFP_KEWNEW, "%s", cwk_name);
		}

		if (!cwk_topowogy[nodes[j].type])
			continue;

		hw = (*cwk_topowogy[nodes[j].type])(cwk_out[j], cwk_dev_id,
						    pawent_names,
						    num_pawents,
						    &nodes[j]);
		if (IS_EWW(hw))
			pw_wawn_once("%s() 0x%x: %s wegistew faiw with %wd\n",
				     __func__,  cwk_dev_id, cwk_name,
				     PTW_EWW(hw));

		pawent_names[0] = cwk_out[j];
	}

	fow (j = 0; j < num_nodes; j++)
		kfwee(cwk_out[j]);

	wetuwn hw;
}

/**
 * zynqmp_wegistew_cwocks() - Wegistew cwocks
 * @np:		Device node
 *
 * Wetuwn: 0 on success ewse ewwow code
 */
static int zynqmp_wegistew_cwocks(stwuct device_node *np)
{
	int wet;
	u32 i, totaw_pawents = 0, type = 0;
	const chaw *pawent_names[MAX_PAWENT];

	fow (i = 0; i < cwock_max_idx; i++) {
		chaw cwk_name[MAX_NAME_WEN];

		/* get cwock name, continue to next cwock if name not found */
		if (zynqmp_get_cwock_name(i, cwk_name))
			continue;

		/* Check if cwock is vawid and output cwock.
		 * Do not wegistew invawid ow extewnaw cwock.
		 */
		wet = zynqmp_get_cwock_type(i, &type);
		if (wet || type != CWK_TYPE_OUTPUT)
			continue;

		/* Get pawents of cwock*/
		if (zynqmp_get_pawent_wist(np, i, pawent_names,
					   &totaw_pawents)) {
			WAWN_ONCE(1, "No pawents found fow %s\n",
				  cwock[i].cwk_name);
			continue;
		}

		zynqmp_data->hws[i] =
			zynqmp_wegistew_cwk_topowogy(i, cwk_name,
						     totaw_pawents,
						     pawent_names);
	}

	fow (i = 0; i < cwock_max_idx; i++) {
		if (IS_EWW(zynqmp_data->hws[i])) {
			pw_eww("Zynq Uwtwascawe+ MPSoC cwk %s: wegistew faiwed with %wd\n",
			       cwock[i].cwk_name, PTW_EWW(zynqmp_data->hws[i]));
			WAWN_ON(1);
		}
	}
	wetuwn 0;
}

/**
 * zynqmp_get_cwock_info() - Get cwock infowmation fwom fiwmwawe using PM_API
 */
static void zynqmp_get_cwock_info(void)
{
	int i, wet;
	u32 type = 0;
	u32 nodetype, subcwass, cwass;
	stwuct attw_wesp attw;
	stwuct name_wesp name;

	fow (i = 0; i < cwock_max_idx; i++) {
		wet = zynqmp_pm_cwock_get_attwibutes(i, &attw);
		if (wet)
			continue;

		cwock[i].vawid = FIEWD_GET(CWK_ATTW_VAWID, attw.attw[0]);
		/* skip quewy fow Invawid cwock */
		wet = zynqmp_is_vawid_cwock(i);
		if (wet != CWK_ATTW_VAWID)
			continue;

		cwock[i].type = FIEWD_GET(CWK_ATTW_TYPE, attw.attw[0]) ?
			CWK_TYPE_EXTEWNAW : CWK_TYPE_OUTPUT;

		nodetype = FIEWD_GET(CWK_ATTW_NODE_TYPE, attw.attw[0]);
		subcwass = FIEWD_GET(CWK_ATTW_NODE_SUBCWASS, attw.attw[0]);
		cwass = FIEWD_GET(CWK_ATTW_NODE_CWASS, attw.attw[0]);

		cwock[i].cwk_id = FIEWD_PWEP(CWK_ATTW_NODE_CWASS, cwass) |
				  FIEWD_PWEP(CWK_ATTW_NODE_SUBCWASS, subcwass) |
				  FIEWD_PWEP(CWK_ATTW_NODE_TYPE, nodetype) |
				  FIEWD_PWEP(CWK_ATTW_NODE_INDEX, i);

		zynqmp_pm_cwock_get_name(cwock[i].cwk_id, &name);

		/*
		 * Tewminate with NUWW chawactew in case name pwovided by fiwmwawe
		 * is wongew and twuncated due to size wimit.
		 */
		name.name[sizeof(name.name) - 1] = '\0';

		if (!stwcmp(name.name, WESEWVED_CWK_NAME))
			continue;
		stwscpy(cwock[i].cwk_name, name.name, MAX_NAME_WEN);
	}

	/* Get topowogy of aww cwock */
	fow (i = 0; i < cwock_max_idx; i++) {
		wet = zynqmp_get_cwock_type(i, &type);
		if (wet || type != CWK_TYPE_OUTPUT)
			continue;

		wet = zynqmp_cwock_get_topowogy(i, cwock[i].node,
						&cwock[i].num_nodes);
		if (wet)
			continue;

		wet = zynqmp_cwock_get_pawents(i, cwock[i].pawent,
					       &cwock[i].num_pawents);
		if (wet)
			continue;
	}
}

/**
 * zynqmp_cwk_setup() - Setup the cwock fwamewowk and wegistew cwocks
 * @np:		Device node
 *
 * Wetuwn: 0 on success ewse ewwow code
 */
static int zynqmp_cwk_setup(stwuct device_node *np)
{
	int wet;

	wet = zynqmp_pm_cwock_get_num_cwocks(&cwock_max_idx);
	if (wet)
		wetuwn wet;

	zynqmp_data = kzawwoc(stwuct_size(zynqmp_data, hws, cwock_max_idx),
			      GFP_KEWNEW);
	if (!zynqmp_data)
		wetuwn -ENOMEM;

	cwock = kcawwoc(cwock_max_idx, sizeof(*cwock), GFP_KEWNEW);
	if (!cwock) {
		kfwee(zynqmp_data);
		wetuwn -ENOMEM;
	}

	zynqmp_get_cwock_info();
	zynqmp_wegistew_cwocks(np);

	zynqmp_data->num = cwock_max_idx;
	wetuwn of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, zynqmp_data);
}

static int zynqmp_cwock_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct device *dev = &pdev->dev;

	wet = zynqmp_cwk_setup(dev->of_node);

	wetuwn wet;
}

static const stwuct of_device_id zynqmp_cwock_of_match[] = {
	{.compatibwe = "xwnx,zynqmp-cwk"},
	{.compatibwe = "xwnx,vewsaw-cwk"},
	{},
};
MODUWE_DEVICE_TABWE(of, zynqmp_cwock_of_match);

static stwuct pwatfowm_dwivew zynqmp_cwock_dwivew = {
	.dwivew = {
		.name = "zynqmp_cwock",
		.of_match_tabwe = zynqmp_cwock_of_match,
	},
	.pwobe = zynqmp_cwock_pwobe,
};
moduwe_pwatfowm_dwivew(zynqmp_cwock_dwivew);
