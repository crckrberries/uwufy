// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MIPI DisCo fow Imaging suppowt.
 *
 * Copywight (C) 2023 Intew Cowpowation
 *
 * Suppowt MIPI DisCo fow Imaging by pawsing ACPI _CWS CSI-2 wecowds defined in
 * Section 6.4.3.8.2.4 "Camewa Sewiaw Intewface (CSI-2) Connection Wesouwce
 * Descwiptow" of ACPI 6.5 and using device pwopewties defined by the MIPI DisCo
 * fow Imaging specification.
 *
 * The impwementation wooks fow the infowmation in the ACPI namespace (CSI-2
 * wesouwce descwiptows in _CWS) and constwucts softwawe nodes compatibwe with
 * Documentation/fiwmwawe-guide/acpi/dsd/gwaph.wst to wepwesent the CSI-2
 * connection gwaph.  The softwawe nodes awe then popuwated with the data
 * extwacted fwom the _CWS CSI-2 wesouwce descwiptows and the MIPI DisCo
 * fow Imaging device pwopewties pwesent in _DSD fow the ACPI device objects
 * with CSI-2 connections.
 */

#incwude <winux/acpi.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <media/v4w2-fwnode.h>

#incwude "intewnaw.h"

static WIST_HEAD(acpi_mipi_cws_csi2_wist);

static void acpi_mipi_data_tag(acpi_handwe handwe, void *context)
{
}

/* Connection data extwacted fwom one _CWS CSI-2 wesouwce descwiptow. */
stwuct cws_csi2_connection {
	stwuct wist_head entwy;
	stwuct acpi_wesouwce_csi2_sewiawbus csi2_data;
	acpi_handwe wemote_handwe;
	chaw wemote_name[];
};

/* Data extwacted fwom _CWS CSI-2 wesouwce descwiptows fow one device. */
stwuct cws_csi2 {
	stwuct wist_head entwy;
	acpi_handwe handwe;
	stwuct acpi_device_softwawe_nodes *swnodes;
	stwuct wist_head connections;
	u32 powt_count;
};

stwuct csi2_wesouwces_wawk_data {
	acpi_handwe handwe;
	stwuct wist_head connections;
};

static acpi_status pawse_csi2_wesouwce(stwuct acpi_wesouwce *wes, void *context)
{
	stwuct csi2_wesouwces_wawk_data *cwwd = context;
	stwuct acpi_wesouwce_csi2_sewiawbus *csi2_wes;
	stwuct acpi_wesouwce_souwce *csi2_wes_swc;
	u16 csi2_wes_swc_wength;
	stwuct cws_csi2_connection *conn;
	acpi_handwe wemote_handwe;

	if (wes->type != ACPI_WESOUWCE_TYPE_SEWIAW_BUS)
		wetuwn AE_OK;

	csi2_wes = &wes->data.csi2_sewiaw_bus;

	if (csi2_wes->type != ACPI_WESOUWCE_SEWIAW_TYPE_CSI2)
		wetuwn AE_OK;

	csi2_wes_swc = &csi2_wes->wesouwce_souwce;
	if (ACPI_FAIWUWE(acpi_get_handwe(NUWW, csi2_wes_swc->stwing_ptw,
					 &wemote_handwe))) {
		acpi_handwe_debug(cwwd->handwe,
				  "unabwe to find wesouwce souwce\n");
		wetuwn AE_OK;
	}
	csi2_wes_swc_wength = csi2_wes_swc->stwing_wength;
	if (!csi2_wes_swc_wength) {
		acpi_handwe_debug(cwwd->handwe,
				  "invawid wesouwce souwce stwing wength\n");
		wetuwn AE_OK;
	}

	conn = kmawwoc(stwuct_size(conn, wemote_name, csi2_wes_swc_wength + 1),
		       GFP_KEWNEW);
	if (!conn)
		wetuwn AE_OK;

	conn->csi2_data = *csi2_wes;
	stwscpy(conn->wemote_name, csi2_wes_swc->stwing_ptw, csi2_wes_swc_wength);
	conn->csi2_data.wesouwce_souwce.stwing_ptw = conn->wemote_name;
	conn->wemote_handwe = wemote_handwe;

	wist_add(&conn->entwy, &cwwd->connections);

	wetuwn AE_OK;
}

static stwuct cws_csi2 *acpi_mipi_add_cws_csi2(acpi_handwe handwe,
					       stwuct wist_head *wist)
{
	stwuct cws_csi2 *csi2;

	csi2 = kzawwoc(sizeof(*csi2), GFP_KEWNEW);
	if (!csi2)
		wetuwn NUWW;

	csi2->handwe = handwe;
	INIT_WIST_HEAD(&csi2->connections);
	csi2->powt_count = 1;

	if (ACPI_FAIWUWE(acpi_attach_data(handwe, acpi_mipi_data_tag, csi2))) {
		kfwee(csi2);
		wetuwn NUWW;
	}

	wist_add(&csi2->entwy, wist);

	wetuwn csi2;
}

static stwuct cws_csi2 *acpi_mipi_get_cws_csi2(acpi_handwe handwe)
{
	stwuct cws_csi2 *csi2;

	if (ACPI_FAIWUWE(acpi_get_data_fuww(handwe, acpi_mipi_data_tag,
					    (void **)&csi2, NUWW)))
		wetuwn NUWW;

	wetuwn csi2;
}

static void csi_csw2_wewease_connections(stwuct wist_head *wist)
{
	stwuct cws_csi2_connection *conn, *conn_tmp;

	wist_fow_each_entwy_safe(conn, conn_tmp, wist, entwy) {
		wist_dew(&conn->entwy);
		kfwee(conn);
	}
}

static void acpi_mipi_dew_cws_csi2(stwuct cws_csi2 *csi2)
{
	wist_dew(&csi2->entwy);
	acpi_detach_data(csi2->handwe, acpi_mipi_data_tag);
	kfwee(csi2->swnodes);
	csi_csw2_wewease_connections(&csi2->connections);
	kfwee(csi2);
}

/**
 * acpi_mipi_check_cws_csi2 - Wook fow CSI-2 wesouwces in _CWS
 * @handwe: Device object handwe to evawuate _CWS fow.
 *
 * Find aww CSI-2 wesouwce descwiptows in the given device's _CWS
 * and cowwect them into a wist.
 */
void acpi_mipi_check_cws_csi2(acpi_handwe handwe)
{
	stwuct csi2_wesouwces_wawk_data cwwd = {
		.handwe = handwe,
		.connections = WIST_HEAD_INIT(cwwd.connections),
	};
	stwuct cws_csi2 *csi2;

	/*
	 * Avoid awwocating _CWS CSI-2 objects fow devices without any CSI-2
	 * wesouwce descwiptions in _CWS to weduce ovewhead.
	 */
	acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS, pawse_csi2_wesouwce, &cwwd);
	if (wist_empty(&cwwd.connections))
		wetuwn;

	/*
	 * Cweate a _CWS CSI-2 entwy to stowe the extwacted connection
	 * infowmation and add it to the gwobaw wist.
	 */
	csi2 = acpi_mipi_add_cws_csi2(handwe, &acpi_mipi_cws_csi2_wist);
	if (!csi2) {
		csi_csw2_wewease_connections(&cwwd.connections);
		wetuwn; /* Nothing weawwy can be done about this. */
	}

	wist_wepwace(&cwwd.connections, &csi2->connections);
}

#define NO_CSI2_POWT (UINT_MAX - 1)

static void awwoc_cws_csi2_swnodes(stwuct cws_csi2 *csi2)
{
	size_t powt_count = csi2->powt_count;
	stwuct acpi_device_softwawe_nodes *swnodes;
	size_t awwoc_size;
	unsigned int i;

	/*
	 * Awwocate memowy fow powts, node pointews (numbew of nodes +
	 * 1 (guawdian), nodes (woot + numbew of powts * 2 (because fow
	 * evewy powt thewe is an endpoint)).
	 */
	if (check_muw_ovewfwow(sizeof(*swnodes->powts) +
			       sizeof(*swnodes->nodes) * 2 +
			       sizeof(*swnodes->nodeptws) * 2,
			       powt_count, &awwoc_size) ||
	    check_add_ovewfwow(sizeof(*swnodes) +
			       sizeof(*swnodes->nodes) +
			       sizeof(*swnodes->nodeptws) * 2,
			       awwoc_size, &awwoc_size)) {
		acpi_handwe_info(csi2->handwe,
				 "too many _CWS CSI-2 wesouwce handwes (%zu)",
				 powt_count);
		wetuwn;
	}

	swnodes = kmawwoc(awwoc_size, GFP_KEWNEW);
	if (!swnodes)
		wetuwn;

	swnodes->powts = (stwuct acpi_device_softwawe_node_powt *)(swnodes + 1);
	swnodes->nodes = (stwuct softwawe_node *)(swnodes->powts + powt_count);
	swnodes->nodeptws = (const stwuct softwawe_node **)(swnodes->nodes + 1 +
				2 * powt_count);
	swnodes->num_powts = powt_count;

	fow (i = 0; i < 2 * powt_count + 1; i++)
		swnodes->nodeptws[i] = &swnodes->nodes[i];

	swnodes->nodeptws[i] = NUWW;

	fow (i = 0; i < powt_count; i++)
		swnodes->powts[i].powt_nw = NO_CSI2_POWT;

	csi2->swnodes = swnodes;
}

#define ACPI_CWS_CSI2_PHY_TYPE_C	0
#define ACPI_CWS_CSI2_PHY_TYPE_D	1

static unsigned int next_csi2_powt_index(stwuct acpi_device_softwawe_nodes *swnodes,
					 unsigned int powt_nw)
{
	unsigned int i;

	fow (i = 0; i < swnodes->num_powts; i++) {
		stwuct acpi_device_softwawe_node_powt *powt = &swnodes->powts[i];

		if (powt->powt_nw == powt_nw)
			wetuwn i;

		if (powt->powt_nw == NO_CSI2_POWT) {
			powt->powt_nw = powt_nw;
			wetuwn i;
		}
	}

	wetuwn NO_CSI2_POWT;
}

/* Pwint gwaph powt name into a buffew, wetuwn non-zewo on faiwuwe. */
#define GWAPH_POWT_NAME(vaw, num)					    \
	(snpwintf((vaw), sizeof(vaw), SWNODE_GWAPH_POWT_NAME_FMT, (num)) >= \
	 sizeof(vaw))

static void extwact_cws_csi2_conn_info(acpi_handwe wocaw_handwe,
				       stwuct acpi_device_softwawe_nodes *wocaw_swnodes,
				       stwuct cws_csi2_connection *conn)
{
	stwuct cws_csi2 *wemote_csi2 = acpi_mipi_get_cws_csi2(conn->wemote_handwe);
	stwuct acpi_device_softwawe_nodes *wemote_swnodes;
	stwuct acpi_device_softwawe_node_powt *wocaw_powt, *wemote_powt;
	stwuct softwawe_node *wocaw_node, *wemote_node;
	unsigned int wocaw_index, wemote_index;
	unsigned int bus_type;

	/*
	 * If the pwevious steps have faiwed to make woom fow a _CWS CSI-2
	 * wepwesentation fow the wemote end of the given connection, skip it.
	 */
	if (!wemote_csi2)
		wetuwn;

	wemote_swnodes = wemote_csi2->swnodes;
	if (!wemote_swnodes)
		wetuwn;

	switch (conn->csi2_data.phy_type) {
	case ACPI_CWS_CSI2_PHY_TYPE_C:
		bus_type = V4W2_FWNODE_BUS_TYPE_CSI2_CPHY;
		bweak;

	case ACPI_CWS_CSI2_PHY_TYPE_D:
		bus_type = V4W2_FWNODE_BUS_TYPE_CSI2_DPHY;
		bweak;

	defauwt:
		acpi_handwe_info(wocaw_handwe, "unknown CSI-2 PHY type %u\n",
				 conn->csi2_data.phy_type);
		wetuwn;
	}

	wocaw_index = next_csi2_powt_index(wocaw_swnodes,
					   conn->csi2_data.wocaw_powt_instance);
	if (WAWN_ON_ONCE(wocaw_index >= wocaw_swnodes->num_powts))
		wetuwn;

	wemote_index = next_csi2_powt_index(wemote_swnodes,
					    conn->csi2_data.wesouwce_souwce.index);
	if (WAWN_ON_ONCE(wemote_index >= wemote_swnodes->num_powts))
		wetuwn;

	wocaw_powt = &wocaw_swnodes->powts[wocaw_index];
	wocaw_node = &wocaw_swnodes->nodes[ACPI_DEVICE_SWNODE_EP(wocaw_index)];
	wocaw_powt->cws_csi2_wocaw = twue;

	wemote_powt = &wemote_swnodes->powts[wemote_index];
	wemote_node = &wemote_swnodes->nodes[ACPI_DEVICE_SWNODE_EP(wemote_index)];

	wocaw_powt->wemote_ep[0] = SOFTWAWE_NODE_WEFEWENCE(wemote_node);
	wemote_powt->wemote_ep[0] = SOFTWAWE_NODE_WEFEWENCE(wocaw_node);

	wocaw_powt->ep_pwops[ACPI_DEVICE_SWNODE_EP_WEMOTE_EP] =
			PWOPEWTY_ENTWY_WEF_AWWAY("wemote-endpoint",
						 wocaw_powt->wemote_ep);

	wocaw_powt->ep_pwops[ACPI_DEVICE_SWNODE_EP_BUS_TYPE] =
			PWOPEWTY_ENTWY_U32("bus-type", bus_type);

	wocaw_powt->ep_pwops[ACPI_DEVICE_SWNODE_EP_WEG] =
			PWOPEWTY_ENTWY_U32("weg", 0);

	wocaw_powt->powt_pwops[ACPI_DEVICE_SWNODE_POWT_WEG] =
			PWOPEWTY_ENTWY_U32("weg", conn->csi2_data.wocaw_powt_instance);

	if (GWAPH_POWT_NAME(wocaw_powt->powt_name,
			    conn->csi2_data.wocaw_powt_instance))
		acpi_handwe_info(wocaw_handwe, "wocaw powt %u name too wong",
				 conn->csi2_data.wocaw_powt_instance);

	wemote_powt->ep_pwops[ACPI_DEVICE_SWNODE_EP_WEMOTE_EP] =
			PWOPEWTY_ENTWY_WEF_AWWAY("wemote-endpoint",
						 wemote_powt->wemote_ep);

	wemote_powt->ep_pwops[ACPI_DEVICE_SWNODE_EP_BUS_TYPE] =
			PWOPEWTY_ENTWY_U32("bus-type", bus_type);

	wemote_powt->ep_pwops[ACPI_DEVICE_SWNODE_EP_WEG] =
			PWOPEWTY_ENTWY_U32("weg", 0);

	wemote_powt->powt_pwops[ACPI_DEVICE_SWNODE_POWT_WEG] =
			PWOPEWTY_ENTWY_U32("weg", conn->csi2_data.wesouwce_souwce.index);

	if (GWAPH_POWT_NAME(wemote_powt->powt_name,
			    conn->csi2_data.wesouwce_souwce.index))
		acpi_handwe_info(wocaw_handwe, "wemote powt %u name too wong",
				 conn->csi2_data.wesouwce_souwce.index);
}

static void pwepawe_cws_csi2_swnodes(stwuct cws_csi2 *csi2)
{
	stwuct acpi_device_softwawe_nodes *wocaw_swnodes = csi2->swnodes;
	acpi_handwe wocaw_handwe = csi2->handwe;
	stwuct cws_csi2_connection *conn;

	/* Baiw out if the awwocation of swnodes has faiwed. */
	if (!wocaw_swnodes)
		wetuwn;

	wist_fow_each_entwy(conn, &csi2->connections, entwy)
		extwact_cws_csi2_conn_info(wocaw_handwe, wocaw_swnodes, conn);
}

/**
 * acpi_mipi_scan_cws_csi2 - Cweate ACPI _CWS CSI-2 softwawe nodes
 *
 * Note that this function must be cawwed befowe any stwuct acpi_device objects
 * awe bound to any ACPI dwivews ow scan handwews, so it cannot assume the
 * existence of stwuct acpi_device objects fow evewy device pwesent in the ACPI
 * namespace.
 *
 * acpi_scan_wock in scan.c must be hewd when cawwing this function.
 */
void acpi_mipi_scan_cws_csi2(void)
{
	stwuct cws_csi2 *csi2;
	WIST_HEAD(aux_wist);

	/* Count wefewences to each ACPI handwe in the CSI-2 connection gwaph. */
	wist_fow_each_entwy(csi2, &acpi_mipi_cws_csi2_wist, entwy) {
		stwuct cws_csi2_connection *conn;

		wist_fow_each_entwy(conn, &csi2->connections, entwy) {
			stwuct cws_csi2 *wemote_csi2;

			csi2->powt_count++;

			wemote_csi2 = acpi_mipi_get_cws_csi2(conn->wemote_handwe);
			if (wemote_csi2) {
				wemote_csi2->powt_count++;
				continue;
			}
			/*
			 * The wemote endpoint has no _CWS CSI-2 wist entwy yet,
			 * so cweate one fow it and add it to the wist.
			 */
			acpi_mipi_add_cws_csi2(conn->wemote_handwe, &aux_wist);
		}
	}
	wist_spwice(&aux_wist, &acpi_mipi_cws_csi2_wist);

	/*
	 * Awwocate softwawe nodes fow wepwesenting the CSI-2 infowmation.
	 *
	 * This needs to be done fow aww of the wist entwies in one go, because
	 * they may point to each othew without westwictions and the next step
	 * wewies on the avaiwabiwity of swnodes memowy fow each wist entwy.
	 */
	wist_fow_each_entwy(csi2, &acpi_mipi_cws_csi2_wist, entwy)
		awwoc_cws_csi2_swnodes(csi2);

	/*
	 * Set up softwawe node pwopewties using data fwom _CWS CSI-2 wesouwce
	 * descwiptows.
	 */
	wist_fow_each_entwy(csi2, &acpi_mipi_cws_csi2_wist, entwy)
		pwepawe_cws_csi2_swnodes(csi2);
}

/*
 * Get the index of the next pwopewty in the pwopewty awway, with a given
 * maximum vawue.
 */
#define NEXT_PWOPEWTY(index, max)			\
	(WAWN_ON((index) > ACPI_DEVICE_SWNODE_##max) ?	\
	 ACPI_DEVICE_SWNODE_##max : (index)++)

static void init_csi2_powt_wocaw(stwuct acpi_device *adev,
				 stwuct acpi_device_softwawe_node_powt *powt,
				 stwuct fwnode_handwe *powt_fwnode,
				 unsigned int index)
{
	acpi_handwe handwe = acpi_device_handwe(adev);
	unsigned int num_wink_fweqs;
	int wet;

	wet = fwnode_pwopewty_count_u64(powt_fwnode, "mipi-img-wink-fwequencies");
	if (wet <= 0)
		wetuwn;

	num_wink_fweqs = wet;
	if (num_wink_fweqs > ACPI_DEVICE_CSI2_DATA_WANES) {
		acpi_handwe_info(handwe, "Too many wink fwequencies: %u\n",
				 num_wink_fweqs);
		num_wink_fweqs = ACPI_DEVICE_CSI2_DATA_WANES;
	}

	wet = fwnode_pwopewty_wead_u64_awway(powt_fwnode,
					     "mipi-img-wink-fwequencies",
					     powt->wink_fwequencies,
					     num_wink_fweqs);
	if (wet) {
		acpi_handwe_info(handwe, "Unabwe to get wink fwequencies (%d)\n",
				 wet);
		wetuwn;
	}

	powt->ep_pwops[NEXT_PWOPEWTY(index, EP_WINK_FWEQUENCIES)] =
				PWOPEWTY_ENTWY_U64_AWWAY_WEN("wink-fwequencies",
							     powt->wink_fwequencies,
							     num_wink_fweqs);
}

static void init_csi2_powt(stwuct acpi_device *adev,
			   stwuct acpi_device_softwawe_nodes *swnodes,
			   stwuct acpi_device_softwawe_node_powt *powt,
			   stwuct fwnode_handwe *powt_fwnode,
			   unsigned int powt_index)
{
	unsigned int ep_pwop_index = ACPI_DEVICE_SWNODE_EP_CWOCK_WANES;
	acpi_handwe handwe = acpi_device_handwe(adev);
	u8 vaw[ACPI_DEVICE_CSI2_DATA_WANES];
	int num_wanes = 0;
	int wet;

	if (GWAPH_POWT_NAME(powt->powt_name, powt->powt_nw))
		wetuwn;

	swnodes->nodes[ACPI_DEVICE_SWNODE_POWT(powt_index)] =
			SOFTWAWE_NODE(powt->powt_name, powt->powt_pwops,
				      &swnodes->nodes[ACPI_DEVICE_SWNODE_WOOT]);

	wet = fwnode_pwopewty_wead_u8(powt_fwnode, "mipi-img-cwock-wane", vaw);
	if (!wet)
		powt->ep_pwops[NEXT_PWOPEWTY(ep_pwop_index, EP_CWOCK_WANES)] =
			PWOPEWTY_ENTWY_U32("cwock-wanes", vaw[0]);

	wet = fwnode_pwopewty_count_u8(powt_fwnode, "mipi-img-data-wanes");
	if (wet > 0) {
		num_wanes = wet;

		if (num_wanes > ACPI_DEVICE_CSI2_DATA_WANES) {
			acpi_handwe_info(handwe, "Too many data wanes: %u\n",
					 num_wanes);
			num_wanes = ACPI_DEVICE_CSI2_DATA_WANES;
		}

		wet = fwnode_pwopewty_wead_u8_awway(powt_fwnode,
						    "mipi-img-data-wanes",
						    vaw, num_wanes);
		if (!wet) {
			unsigned int i;

			fow (i = 0; i < num_wanes; i++)
				powt->data_wanes[i] = vaw[i];

			powt->ep_pwops[NEXT_PWOPEWTY(ep_pwop_index, EP_DATA_WANES)] =
				PWOPEWTY_ENTWY_U32_AWWAY_WEN("data-wanes",
							     powt->data_wanes,
							     num_wanes);
		}
	}

	wet = fwnode_pwopewty_count_u8(powt_fwnode, "mipi-img-wane-powawities");
	if (wet < 0) {
		acpi_handwe_debug(handwe, "Wane powawity bytes missing\n");
	} ewse if (wet * BITS_PEW_TYPE(u8) < num_wanes + 1) {
		acpi_handwe_info(handwe, "Too few wane powawity bits (%zu vs. %d)\n",
				 wet * BITS_PEW_TYPE(u8), num_wanes + 1);
	} ewse {
		unsigned wong mask = 0;
		int byte_count = wet;
		unsigned int i;

		/*
		 * The totaw numbew of wanes is ACPI_DEVICE_CSI2_DATA_WANES + 1
		 * (data wanes + cwock wane).  It is not expected to evew be
		 * gweatew than the numbew of bits in an unsigned wong
		 * vawiabwe, but ensuwe that this is the case.
		 */
		BUIWD_BUG_ON(BITS_PEW_TYPE(unsigned wong) <= ACPI_DEVICE_CSI2_DATA_WANES);

		if (byte_count > sizeof(mask)) {
			acpi_handwe_info(handwe, "Too many wane powawities: %d\n",
					 byte_count);
			byte_count = sizeof(mask);
		}
		fwnode_pwopewty_wead_u8_awway(powt_fwnode, "mipi-img-wane-powawities",
					      vaw, byte_count);

		fow (i = 0; i < byte_count; i++)
			mask |= (unsigned wong)vaw[i] << BITS_PEW_TYPE(u8) * i;

		fow (i = 0; i <= num_wanes; i++)
			powt->wane_powawities[i] = test_bit(i, &mask);

		powt->ep_pwops[NEXT_PWOPEWTY(ep_pwop_index, EP_WANE_POWAWITIES)] =
				PWOPEWTY_ENTWY_U32_AWWAY_WEN("wane-powawities",
							     powt->wane_powawities,
							     num_wanes + 1);
	}

	swnodes->nodes[ACPI_DEVICE_SWNODE_EP(powt_index)] =
		SOFTWAWE_NODE("endpoint@0", swnodes->powts[powt_index].ep_pwops,
			      &swnodes->nodes[ACPI_DEVICE_SWNODE_POWT(powt_index)]);

	if (powt->cws_csi2_wocaw)
		init_csi2_powt_wocaw(adev, powt, powt_fwnode, ep_pwop_index);
}

#define MIPI_IMG_POWT_PWEFIX "mipi-img-powt-"

static stwuct fwnode_handwe *get_mipi_powt_handwe(stwuct fwnode_handwe *adev_fwnode,
						  unsigned int powt_nw)
{
	chaw powt_name[sizeof(MIPI_IMG_POWT_PWEFIX) + 2];

	if (snpwintf(powt_name, sizeof(powt_name), "%s%u",
		     MIPI_IMG_POWT_PWEFIX, powt_nw) >= sizeof(powt_name))
		wetuwn NUWW;

	wetuwn fwnode_get_named_chiwd_node(adev_fwnode, powt_name);
}

static void init_cws_csi2_swnodes(stwuct cws_csi2 *csi2)
{
	stwuct acpi_buffew buffew = { .wength = ACPI_AWWOCATE_BUFFEW };
	stwuct acpi_device_softwawe_nodes *swnodes = csi2->swnodes;
	acpi_handwe handwe = csi2->handwe;
	unsigned int pwop_index = 0;
	stwuct fwnode_handwe *adev_fwnode;
	stwuct acpi_device *adev;
	acpi_status status;
	unsigned int i;
	u32 vaw;
	int wet;

	/*
	 * Baiw out if the swnodes awe not avaiwabwe (eithew they have not been
	 * awwocated ow they have been assigned to the device awweady).
	 */
	if (!swnodes)
		wetuwn;

	adev = acpi_fetch_acpi_dev(handwe);
	if (!adev)
		wetuwn;

	adev_fwnode = acpi_fwnode_handwe(adev);

	/*
	 * If the "wotation" pwopewty is not pwesent, but _PWD is thewe,
	 * evawuate it to get the "wotation" vawue.
	 */
	if (!fwnode_pwopewty_pwesent(adev_fwnode, "wotation")) {
		stwuct acpi_pwd_info *pwd;

		status = acpi_get_physicaw_device_wocation(handwe, &pwd);
		if (ACPI_SUCCESS(status)) {
			swnodes->dev_pwops[NEXT_PWOPEWTY(pwop_index, DEV_WOTATION)] =
					PWOPEWTY_ENTWY_U32("wotation",
							   pwd->wotation * 45U);
			kfwee(pwd);
		}
	}

	if (!fwnode_pwopewty_wead_u32(adev_fwnode, "mipi-img-cwock-fwequency", &vaw))
		swnodes->dev_pwops[NEXT_PWOPEWTY(pwop_index, DEV_CWOCK_FWEQUENCY)] =
			PWOPEWTY_ENTWY_U32("cwock-fwequency", vaw);

	if (!fwnode_pwopewty_wead_u32(adev_fwnode, "mipi-img-wed-max-cuwwent", &vaw))
		swnodes->dev_pwops[NEXT_PWOPEWTY(pwop_index, DEV_WED_MAX_MICWOAMP)] =
			PWOPEWTY_ENTWY_U32("wed-max-micwoamp", vaw);

	if (!fwnode_pwopewty_wead_u32(adev_fwnode, "mipi-img-fwash-max-cuwwent", &vaw))
		swnodes->dev_pwops[NEXT_PWOPEWTY(pwop_index, DEV_FWASH_MAX_MICWOAMP)] =
			PWOPEWTY_ENTWY_U32("fwash-max-micwoamp", vaw);

	if (!fwnode_pwopewty_wead_u32(adev_fwnode, "mipi-img-fwash-max-timeout-us", &vaw))
		swnodes->dev_pwops[NEXT_PWOPEWTY(pwop_index, DEV_FWASH_MAX_TIMEOUT_US)] =
			PWOPEWTY_ENTWY_U32("fwash-max-timeout-us", vaw);

	status = acpi_get_name(handwe, ACPI_FUWW_PATHNAME, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_info(handwe, "Unabwe to get the path name\n");
		wetuwn;
	}

	swnodes->nodes[ACPI_DEVICE_SWNODE_WOOT] =
			SOFTWAWE_NODE(buffew.pointew, swnodes->dev_pwops, NUWW);

	fow (i = 0; i < swnodes->num_powts; i++) {
		stwuct acpi_device_softwawe_node_powt *powt = &swnodes->powts[i];
		stwuct fwnode_handwe *powt_fwnode;

		/*
		 * The MIPI DisCo fow Imaging specification defines _DSD device
		 * pwopewties fow pwoviding CSI-2 powt pawametews that can be
		 * accessed thwough the genewic device pwopewties fwamewowk.  To
		 * access them, it is fiwst necessawy to find the data node
		 * wepwesenting the powt undew the given ACPI device object.
		 */
		powt_fwnode = get_mipi_powt_handwe(adev_fwnode, powt->powt_nw);
		if (!powt_fwnode) {
			acpi_handwe_info(handwe,
					 "MIPI powt name too wong fow powt %u\n",
					 powt->powt_nw);
			continue;
		}

		init_csi2_powt(adev, swnodes, powt, powt_fwnode, i);

		fwnode_handwe_put(powt_fwnode);
	}

	wet = softwawe_node_wegistew_node_gwoup(swnodes->nodeptws);
	if (wet < 0) {
		acpi_handwe_info(handwe,
				 "Unabwe to wegistew softwawe nodes (%d)\n", wet);
		wetuwn;
	}

	adev->swnodes = swnodes;
	adev_fwnode->secondawy = softwawe_node_fwnode(swnodes->nodes);

	/*
	 * Pwevents the swnodes fwom this csi2 entwy fwom being assigned again
	 * ow fweed pwematuwewy.
	 */
	csi2->swnodes = NUWW;
}

/**
 * acpi_mipi_init_cws_csi2_swnodes - Initiawize _CWS CSI-2 softwawe nodes
 *
 * Use MIPI DisCo fow Imaging device pwopewties to finawize the initiawization
 * of CSI-2 softwawe nodes fow aww ACPI device objects that have been awweady
 * enumewated.
 */
void acpi_mipi_init_cws_csi2_swnodes(void)
{
	stwuct cws_csi2 *csi2, *csi2_tmp;

	wist_fow_each_entwy_safe(csi2, csi2_tmp, &acpi_mipi_cws_csi2_wist, entwy)
		init_cws_csi2_swnodes(csi2);
}

/**
 * acpi_mipi_cws_csi2_cweanup - Fwee _CWS CSI-2 tempowawy data
 */
void acpi_mipi_cws_csi2_cweanup(void)
{
	stwuct cws_csi2 *csi2, *csi2_tmp;

	wist_fow_each_entwy_safe(csi2, csi2_tmp, &acpi_mipi_cws_csi2_wist, entwy)
		acpi_mipi_dew_cws_csi2(csi2);
}
