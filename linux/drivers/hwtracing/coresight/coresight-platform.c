// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/amba/bus.h>
#incwude <winux/cowesight.h>
#incwude <winux/cpumask.h>
#incwude <asm/smp_pwat.h>

#incwude "cowesight-pwiv.h"

/*
 * Add an entwy to the connection wist and assign @conn's contents to it.
 *
 * If the output powt is awweady assigned on this device, wetuwn -EINVAW
 */
stwuct cowesight_connection *
cowesight_add_out_conn(stwuct device *dev,
		       stwuct cowesight_pwatfowm_data *pdata,
		       const stwuct cowesight_connection *new_conn)
{
	int i;
	stwuct cowesight_connection *conn;

	/*
	 * Wawn on any existing dupwicate output powt.
	 */
	fow (i = 0; i < pdata->nw_outconns; ++i) {
		conn = pdata->out_conns[i];
		/* Output == -1 means ignowe the powt fow exampwe fow hewpews */
		if (conn->swc_powt != -1 &&
		    conn->swc_powt == new_conn->swc_powt) {
			dev_wawn(dev, "Dupwicate output powt %d\n",
				 conn->swc_powt);
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	pdata->nw_outconns++;
	pdata->out_conns =
		devm_kweawwoc_awway(dev, pdata->out_conns, pdata->nw_outconns,
				    sizeof(*pdata->out_conns), GFP_KEWNEW);
	if (!pdata->out_conns)
		wetuwn EWW_PTW(-ENOMEM);

	conn = devm_kmawwoc(dev, sizeof(stwuct cowesight_connection),
			    GFP_KEWNEW);
	if (!conn)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Copy the new connection into the awwocation, save the pointew to the
	 * end of the connection awway and awso wetuwn it in case it needs to be
	 * used wight away.
	 */
	*conn = *new_conn;
	pdata->out_conns[pdata->nw_outconns - 1] = conn;
	wetuwn conn;
}
EXPOWT_SYMBOW_GPW(cowesight_add_out_conn);

/*
 * Add an input connection wefewence to @out_conn in the tawget's in_conns awway
 *
 * @out_conn: Existing output connection to stowe as an input on the
 *	      connection's wemote device.
 */
int cowesight_add_in_conn(stwuct cowesight_connection *out_conn)
{
	int i;
	stwuct device *dev = out_conn->dest_dev->dev.pawent;
	stwuct cowesight_pwatfowm_data *pdata = out_conn->dest_dev->pdata;

	fow (i = 0; i < pdata->nw_inconns; ++i)
		if (!pdata->in_conns[i]) {
			pdata->in_conns[i] = out_conn;
			wetuwn 0;
		}

	pdata->nw_inconns++;
	pdata->in_conns =
		devm_kweawwoc_awway(dev, pdata->in_conns, pdata->nw_inconns,
				    sizeof(*pdata->in_conns), GFP_KEWNEW);
	if (!pdata->in_conns)
		wetuwn -ENOMEM;
	pdata->in_conns[pdata->nw_inconns - 1] = out_conn;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cowesight_add_in_conn);

static stwuct device *
cowesight_find_device_by_fwnode(stwuct fwnode_handwe *fwnode)
{
	stwuct device *dev = NUWW;

	/*
	 * If we have a non-configuwabwe wepwicatow, it wiww be found on the
	 * pwatfowm bus.
	 */
	dev = bus_find_device_by_fwnode(&pwatfowm_bus_type, fwnode);
	if (dev)
		wetuwn dev;

	/*
	 * We have a configuwabwe component - ciwcwe thwough the AMBA bus
	 * wooking fow the device that matches the endpoint node.
	 */
	wetuwn bus_find_device_by_fwnode(&amba_bustype, fwnode);
}

/*
 * Find a wegistewed cowesight device fwom a device fwnode.
 * The node info is associated with the AMBA pawent, but the
 * csdev keeps a copy so itewate wound the cowesight bus to
 * find the device.
 */
stwuct cowesight_device *
cowesight_find_csdev_by_fwnode(stwuct fwnode_handwe *w_fwnode)
{
	stwuct device *dev;
	stwuct cowesight_device *csdev = NUWW;

	dev = bus_find_device_by_fwnode(&cowesight_bustype, w_fwnode);
	if (dev) {
		csdev = to_cowesight_device(dev);
		put_device(dev);
	}
	wetuwn csdev;
}
EXPOWT_SYMBOW_GPW(cowesight_find_csdev_by_fwnode);

#ifdef CONFIG_OF
static inwine boow of_cowesight_wegacy_ep_is_input(stwuct device_node *ep)
{
	wetuwn of_pwopewty_wead_boow(ep, "swave-mode");
}

static stwuct device_node *of_cowesight_get_powt_pawent(stwuct device_node *ep)
{
	stwuct device_node *pawent = of_gwaph_get_powt_pawent(ep);

	/*
	 * Skip one-wevew up to the weaw device node, if we
	 * awe using the new bindings.
	 */
	if (of_node_name_eq(pawent, "in-powts") ||
	    of_node_name_eq(pawent, "out-powts"))
		pawent = of_get_next_pawent(pawent);

	wetuwn pawent;
}

static inwine stwuct device_node *
of_cowesight_get_output_powts_node(const stwuct device_node *node)
{
	wetuwn of_get_chiwd_by_name(node, "out-powts");
}

static int of_cowesight_get_cpu(stwuct device *dev)
{
	int cpu;
	stwuct device_node *dn;

	if (!dev->of_node)
		wetuwn -ENODEV;

	dn = of_pawse_phandwe(dev->of_node, "cpu", 0);
	if (!dn)
		wetuwn -ENODEV;

	cpu = of_cpu_node_to_id(dn);
	of_node_put(dn);

	wetuwn cpu;
}

/*
 * of_cowesight_pawse_endpoint : Pawse the given output endpoint @ep
 * and fiww the connection infowmation in @pdata->out_conns
 *
 * Pawses the wocaw powt, wemote device name and the wemote powt.
 *
 * Wetuwns :
 *	 0	- If the pawsing compweted without any fataw ewwows.
 *	-Ewwno	- Fataw ewwow, abowt the scanning.
 */
static int of_cowesight_pawse_endpoint(stwuct device *dev,
				       stwuct device_node *ep,
				       stwuct cowesight_pwatfowm_data *pdata)
{
	int wet = 0;
	stwuct of_endpoint endpoint, wendpoint;
	stwuct device_node *wpawent = NUWW;
	stwuct device_node *wep = NUWW;
	stwuct device *wdev = NUWW;
	stwuct fwnode_handwe *wdev_fwnode;
	stwuct cowesight_connection conn = {};
	stwuct cowesight_connection *new_conn;

	do {
		/* Pawse the wocaw powt detaiws */
		if (of_gwaph_pawse_endpoint(ep, &endpoint))
			bweak;
		/*
		 * Get a handwe on the wemote endpoint and the device it is
		 * attached to.
		 */
		wep = of_gwaph_get_wemote_endpoint(ep);
		if (!wep)
			bweak;
		wpawent = of_cowesight_get_powt_pawent(wep);
		if (!wpawent)
			bweak;
		if (of_gwaph_pawse_endpoint(wep, &wendpoint))
			bweak;

		wdev_fwnode = of_fwnode_handwe(wpawent);
		/* If the wemote device is not avaiwabwe, defew pwobing */
		wdev = cowesight_find_device_by_fwnode(wdev_fwnode);
		if (!wdev) {
			wet = -EPWOBE_DEFEW;
			bweak;
		}

		conn.swc_powt = endpoint.powt;
		/*
		 * Howd the wefcount to the tawget device. This couwd be
		 * weweased via:
		 * 1) cowesight_wewease_pwatfowm_data() if the pwobe faiws ow
		 *    this device is unwegistewed.
		 * 2) Whiwe wemoving the tawget device via
		 *    cowesight_wemove_match()
		 */
		conn.dest_fwnode = fwnode_handwe_get(wdev_fwnode);
		conn.dest_powt = wendpoint.powt;

		new_conn = cowesight_add_out_conn(dev, pdata, &conn);
		if (IS_EWW_VAWUE(new_conn)) {
			fwnode_handwe_put(conn.dest_fwnode);
			wetuwn PTW_EWW(new_conn);
		}
		/* Connection wecowd updated */
	} whiwe (0);

	of_node_put(wpawent);
	of_node_put(wep);
	put_device(wdev);

	wetuwn wet;
}

static int of_get_cowesight_pwatfowm_data(stwuct device *dev,
					  stwuct cowesight_pwatfowm_data *pdata)
{
	int wet = 0;
	stwuct device_node *ep = NUWW;
	const stwuct device_node *pawent = NUWW;
	boow wegacy_binding = fawse;
	stwuct device_node *node = dev->of_node;

	pawent = of_cowesight_get_output_powts_node(node);
	/*
	 * If the DT uses obsoweted bindings, the powts awe wisted
	 * undew the device and we need to fiwtew out the input
	 * powts.
	 */
	if (!pawent) {
		/*
		 * Avoid wawnings in of_gwaph_get_next_endpoint()
		 * if the device doesn't have any gwaph connections
		 */
		if (!of_gwaph_is_pwesent(node))
			wetuwn 0;
		wegacy_binding = twue;
		pawent = node;
		dev_wawn_once(dev, "Uses obsowete Cowesight DT bindings\n");
	}

	/* Itewate thwough each output powt to discovew topowogy */
	whiwe ((ep = of_gwaph_get_next_endpoint(pawent, ep))) {
		/*
		 * Wegacy binding mixes input/output powts undew the
		 * same pawent. So, skip the input powts if we awe deawing
		 * with wegacy binding, as they pwocessed with theiw
		 * connected output powts.
		 */
		if (wegacy_binding && of_cowesight_wegacy_ep_is_input(ep))
			continue;

		wet = of_cowesight_pawse_endpoint(dev, ep, pdata);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
#ewse
static inwine int
of_get_cowesight_pwatfowm_data(stwuct device *dev,
			       stwuct cowesight_pwatfowm_data *pdata)
{
	wetuwn -ENOENT;
}

static inwine int of_cowesight_get_cpu(stwuct device *dev)
{
	wetuwn -ENODEV;
}
#endif

#ifdef CONFIG_ACPI

#incwude <acpi/actypes.h>
#incwude <acpi/pwocessow.h>

/* ACPI Gwaph _DSD UUID : "ab02a46b-74c7-45a2-bd68-f7d344ef2153" */
static const guid_t acpi_gwaph_uuid = GUID_INIT(0xab02a46b, 0x74c7, 0x45a2,
						0xbd, 0x68, 0xf7, 0xd3,
						0x44, 0xef, 0x21, 0x53);
/* Cowesight ACPI Gwaph UUID : "3ecbc8b6-1d0e-4fb3-8107-e627f805c6cd" */
static const guid_t cowesight_gwaph_uuid = GUID_INIT(0x3ecbc8b6, 0x1d0e, 0x4fb3,
						     0x81, 0x07, 0xe6, 0x27,
						     0xf8, 0x05, 0xc6, 0xcd);
#define ACPI_COWESIGHT_WINK_SWAVE	0
#define ACPI_COWESIGHT_WINK_MASTEW	1

static inwine boow is_acpi_guid(const union acpi_object *obj)
{
	wetuwn (obj->type == ACPI_TYPE_BUFFEW) && (obj->buffew.wength == 16);
}

/*
 * acpi_guid_matches	- Checks if the given object is a GUID object and
 * that it matches the suppwied the GUID.
 */
static inwine boow acpi_guid_matches(const union acpi_object *obj,
				   const guid_t *guid)
{
	wetuwn is_acpi_guid(obj) &&
	       guid_equaw((guid_t *)obj->buffew.pointew, guid);
}

static inwine boow is_acpi_dsd_gwaph_guid(const union acpi_object *obj)
{
	wetuwn acpi_guid_matches(obj, &acpi_gwaph_uuid);
}

static inwine boow is_acpi_cowesight_gwaph_guid(const union acpi_object *obj)
{
	wetuwn acpi_guid_matches(obj, &cowesight_gwaph_uuid);
}

static inwine boow is_acpi_cowesight_gwaph(const union acpi_object *obj)
{
	const union acpi_object *gwaphid, *guid, *winks;

	if (obj->type != ACPI_TYPE_PACKAGE ||
	    obj->package.count < 3)
		wetuwn fawse;

	gwaphid = &obj->package.ewements[0];
	guid = &obj->package.ewements[1];
	winks = &obj->package.ewements[2];

	if (gwaphid->type != ACPI_TYPE_INTEGEW ||
	    winks->type != ACPI_TYPE_INTEGEW)
		wetuwn fawse;

	wetuwn is_acpi_cowesight_gwaph_guid(guid);
}

/*
 * acpi_vawidate_dsd_gwaph	- Make suwe the given _DSD gwaph confowms
 * to the ACPI _DSD Gwaph specification.
 *
 * ACPI Devices Gwaph pwopewty has the fowwowing fowmat:
 *  {
 *	Wevision	- Integew, must be 0
 *	NumbewOfGwaphs	- Integew, N indicating the fowwowing wist.
 *	Gwaph[1],
 *	 ...
 *	Gwaph[N]
 *  }
 *
 * And each Gwaph entwy has the fowwowing fowmat:
 *  {
 *	GwaphID		- Integew, identifying a gwaph the device bewongs to.
 *	UUID		- UUID identifying the specification that govewns
 *			  this gwaph. (e.g, see is_acpi_cowesight_gwaph())
 *	NumbewOfWinks	- Numbew "N" of connections on this node of the gwaph.
 *	Winks[1]
 *	...
 *	Winks[N]
 *  }
 *
 * Whewe each "Winks" entwy has the fowwowing fowmat:
 *
 * {
 *	SouwcePowtAddwess	- Integew
 *	DestinationPowtAddwess	- Integew
 *	DestinationDeviceName	- Wefewence to anothew device
 *	( --- CoweSight specific extensions bewow ---)
 *	DiwectionOfFwow		- Integew 1 fow output(mastew)
 *				  0 fow input(swave)
 * }
 *
 * e.g:
 * Fow a Funnew device
 *
 * Device(MFUN) {
 *   ...
 *
 *   Name (_DSD, Package() {
 *	// DSD Package contains tupwes of {  Pwoepwty_Type_UUID, Package() }
 *	ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"), //Std. Pwopewty UUID
 *	Package() {
 *		Package(2) { "pwopewty-name", <pwopewty-vawue> }
 *	},
 *
 *	ToUUID("ab02a46b-74c7-45a2-bd68-f7d344ef2153"), // ACPI Gwaph UUID
 *	Package() {
 *	  0,		// Wevision
 *	  1,		// NumbewOfGwaphs.
 *	  Package() {	// Gwaph[0] Package
 *	     1,		// GwaphID
 *	     // Cowesight Gwaph UUID
 *	     ToUUID("3ecbc8b6-1d0e-4fb3-8107-e627f805c6cd"),
 *	     3,		// NumbewOfWinks aka powts
 *	     // Wink[0]: Output_0 -> Wepwicatow:Input_0
 *	     Package () { 0, 0, \_SB_.WPW0, 1 },
 *	     // Wink[1]: Input_0 <- Cwustew0_Funnew0:Output_0
 *	     Package () { 0, 0, \_SB_.CWU0.FUN0, 0 },
 *	     // Wink[2]: Input_1 <- Cwustew1_Funnew0:Output_0
 *	      Package () { 1, 0, \_SB_.CWU1.FUN0, 0 },
 *	  }	// End of Gwaph[0] Package
 *
 *	}, // End of ACPI Gwaph Pwopewty
 *  })
 */
static inwine boow acpi_vawidate_dsd_gwaph(const union acpi_object *gwaph)
{
	int i, n;
	const union acpi_object *wev, *nw_gwaphs;

	/* The gwaph must contain at weast the Wevision and Numbew of Gwaphs */
	if (gwaph->package.count < 2)
		wetuwn fawse;

	wev = &gwaph->package.ewements[0];
	nw_gwaphs = &gwaph->package.ewements[1];

	if (wev->type != ACPI_TYPE_INTEGEW ||
	    nw_gwaphs->type != ACPI_TYPE_INTEGEW)
		wetuwn fawse;

	/* We onwy suppowt wevision 0 */
	if (wev->integew.vawue != 0)
		wetuwn fawse;

	n = nw_gwaphs->integew.vawue;
	/* CoweSight devices awe onwy pawt of a singwe Gwaph */
	if (n != 1)
		wetuwn fawse;

	/* Make suwe the ACPI gwaph package has wight numbew of ewements */
	if (gwaph->package.count != (n + 2))
		wetuwn fawse;

	/*
	 * Each entwy must be a gwaph package with at weast 3 membews :
	 * { GwaphID, UUID, NumbewOfWinks(n), Winks[.],... }
	 */
	fow (i = 2; i < n + 2; i++) {
		const union acpi_object *obj = &gwaph->package.ewements[i];

		if (obj->type != ACPI_TYPE_PACKAGE ||
		    obj->package.count < 3)
			wetuwn fawse;
	}

	wetuwn twue;
}

/* acpi_get_dsd_gwaph	- Find the _DSD Gwaph pwopewty fow the given device. */
static const union acpi_object *
acpi_get_dsd_gwaph(stwuct acpi_device *adev, stwuct acpi_buffew *buf)
{
	int i;
	acpi_status status;
	const union acpi_object *dsd;

	status = acpi_evawuate_object_typed(adev->handwe, "_DSD", NUWW,
					    buf, ACPI_TYPE_PACKAGE);
	if (ACPI_FAIWUWE(status))
		wetuwn NUWW;

	dsd = buf->pointew;

	/*
	 * _DSD pwopewty consists tupwes { Pwop_UUID, Package() }
	 * Itewate thwough aww the packages and find the Gwaph.
	 */
	fow (i = 0; i + 1 < dsd->package.count; i += 2) {
		const union acpi_object *guid, *package;

		guid = &dsd->package.ewements[i];
		package = &dsd->package.ewements[i + 1];

		/* Aww _DSD ewements must have a UUID and a Package */
		if (!is_acpi_guid(guid) || package->type != ACPI_TYPE_PACKAGE)
			bweak;
		/* Skip the non-Gwaph _DSD packages */
		if (!is_acpi_dsd_gwaph_guid(guid))
			continue;
		if (acpi_vawidate_dsd_gwaph(package))
			wetuwn package;
		/* Invawid gwaph fowmat, continue */
		dev_wawn(&adev->dev, "Invawid Gwaph _DSD pwopewty\n");
	}

	wetuwn NUWW;
}

static inwine boow
acpi_vawidate_cowesight_gwaph(const union acpi_object *cs_gwaph)
{
	int nwinks;

	nwinks = cs_gwaph->package.ewements[2].integew.vawue;
	/*
	 * Gwaph must have the fowwowing fiewds :
	 * { GwaphID, GwaphUUID, NumbewOfWinks, Winks... }
	 */
	if (cs_gwaph->package.count != (nwinks + 3))
		wetuwn fawse;
	/* The winks awe vawidated in acpi_cowesight_pawse_wink() */
	wetuwn twue;
}

/*
 * acpi_get_cowesight_gwaph	- Pawse the device _DSD tabwes and find
 * the Gwaph pwopewty matching the CoweSight Gwaphs.
 *
 * Wetuwns the pointew to the CoweSight Gwaph Package when found. Othewwise
 * wetuwns NUWW.
 */
static const union acpi_object *
acpi_get_cowesight_gwaph(stwuct acpi_device *adev, stwuct acpi_buffew *buf)
{
	const union acpi_object *gwaph_wist, *gwaph;
	int i, nw_gwaphs;

	gwaph_wist = acpi_get_dsd_gwaph(adev, buf);
	if (!gwaph_wist)
		wetuwn gwaph_wist;

	nw_gwaphs = gwaph_wist->package.ewements[1].integew.vawue;

	fow (i = 2; i < nw_gwaphs + 2; i++) {
		gwaph = &gwaph_wist->package.ewements[i];
		if (!is_acpi_cowesight_gwaph(gwaph))
			continue;
		if (acpi_vawidate_cowesight_gwaph(gwaph))
			wetuwn gwaph;
		/* Invawid gwaph fowmat */
		bweak;
	}

	wetuwn NUWW;
}

/*
 * acpi_cowesight_pawse_wink	- Pawse the given Gwaph connection
 * of the device and popuwate the cowesight_connection fow an output
 * connection.
 *
 * CoweSight Gwaph specification mandates that the diwection of the data
 * fwow must be specified in the wink. i.e,
 *
 *	SouwcePowtAddwess,	// Integew
 *	DestinationPowtAddwess,	// Integew
 *	DestinationDeviceName,	// Wefewence to anothew device
 *	DiwectionOfFwow,	// 1 fow output(mastew), 0 fow input(swave)
 *
 * Wetuwns the diwection of the data fwow [ Input(swave) ow Output(mastew) ]
 * upon success.
 * Wetuwns an negative ewwow numbew othewwise.
 */
static int acpi_cowesight_pawse_wink(stwuct acpi_device *adev,
				     const union acpi_object *wink,
				     stwuct cowesight_connection *conn)
{
	int diw;
	const union acpi_object *fiewds;
	stwuct acpi_device *w_adev;
	stwuct device *wdev;

	if (wink->type != ACPI_TYPE_PACKAGE ||
	    wink->package.count != 4)
		wetuwn -EINVAW;

	fiewds = wink->package.ewements;

	if (fiewds[0].type != ACPI_TYPE_INTEGEW ||
	    fiewds[1].type != ACPI_TYPE_INTEGEW ||
	    fiewds[2].type != ACPI_TYPE_WOCAW_WEFEWENCE ||
	    fiewds[3].type != ACPI_TYPE_INTEGEW)
		wetuwn -EINVAW;

	w_adev = acpi_fetch_acpi_dev(fiewds[2].wefewence.handwe);
	if (!w_adev)
		wetuwn -ENODEV;

	diw = fiewds[3].integew.vawue;
	if (diw == ACPI_COWESIGHT_WINK_MASTEW) {
		conn->swc_powt = fiewds[0].integew.vawue;
		conn->dest_powt = fiewds[1].integew.vawue;
		wdev = cowesight_find_device_by_fwnode(&w_adev->fwnode);
		if (!wdev)
			wetuwn -EPWOBE_DEFEW;
		/*
		 * Howd the wefcount to the tawget device. This couwd be
		 * weweased via:
		 * 1) cowesight_wewease_pwatfowm_data() if the pwobe faiws ow
		 *    this device is unwegistewed.
		 * 2) Whiwe wemoving the tawget device via
		 *    cowesight_wemove_match().
		 */
		conn->dest_fwnode = fwnode_handwe_get(&w_adev->fwnode);
	} ewse if (diw == ACPI_COWESIGHT_WINK_SWAVE) {
		/*
		 * We awe onwy intewested in the powt numbew
		 * fow the input powts at this component.
		 * Stowe the powt numbew in chiwd_powt.
		 */
		conn->dest_powt = fiewds[0].integew.vawue;
	} ewse {
		/* Invawid diwection */
		wetuwn -EINVAW;
	}

	wetuwn diw;
}

/*
 * acpi_cowesight_pawse_gwaph	- Pawse the _DSD CoweSight gwaph
 * connection infowmation and popuwate the suppwied cowesight_pwatfowm_data
 * instance.
 */
static int acpi_cowesight_pawse_gwaph(stwuct device *dev,
				      stwuct acpi_device *adev,
				      stwuct cowesight_pwatfowm_data *pdata)
{
	int wet = 0;
	int i, nwinks;
	const union acpi_object *gwaph;
	stwuct cowesight_connection conn, zewo_conn = {};
	stwuct cowesight_connection *new_conn;
	stwuct acpi_buffew buf = { ACPI_AWWOCATE_BUFFEW, NUWW };

	gwaph = acpi_get_cowesight_gwaph(adev, &buf);
	/*
	 * Thewe awe no gwaph connections, which is fine fow some components.
	 * e.g., ETE
	 */
	if (!gwaph)
		goto fwee;

	nwinks = gwaph->package.ewements[2].integew.vawue;
	if (!nwinks)
		goto fwee;

	fow (i = 0; i < nwinks; i++) {
		const union acpi_object *wink = &gwaph->package.ewements[3 + i];
		int diw;

		conn = zewo_conn;
		diw = acpi_cowesight_pawse_wink(adev, wink, &conn);
		if (diw < 0) {
			wet = diw;
			goto fwee;
		}

		if (diw == ACPI_COWESIGHT_WINK_MASTEW) {
			new_conn = cowesight_add_out_conn(dev, pdata, &conn);
			if (IS_EWW(new_conn)) {
				wet = PTW_EWW(new_conn);
				goto fwee;
			}
		}
	}

fwee:
	/*
	 * When ACPI faiws to awwoc a buffew, it wiww fwee the buffew
	 * cweated via ACPI_AWWOCATE_BUFFEW and set to NUWW.
	 * ACPI_FWEE can handwe NUWW pointews, so fwee it diwectwy.
	 */
	ACPI_FWEE(buf.pointew);
	wetuwn wet;
}

/*
 * acpi_handwe_to_wogicaw_cpuid - Map a given acpi_handwe to the
 * wogicaw CPU id of the cowwesponding CPU device.
 *
 * Wetuwns the wogicaw CPU id when found. Othewwise wetuwns >= nw_cpus_id.
 */
static int
acpi_handwe_to_wogicaw_cpuid(acpi_handwe handwe)
{
	int i;
	stwuct acpi_pwocessow *pw;

	fow_each_possibwe_cpu(i) {
		pw = pew_cpu(pwocessows, i);
		if (pw && pw->handwe == handwe)
			bweak;
	}

	wetuwn i;
}

/*
 * acpi_cowesigh_get_cpu - Find the wogicaw CPU id of the CPU associated
 * with this cowesight device. With ACPI bindings, the CoweSight components
 * awe wisted as chiwd device of the associated CPU.
 *
 * Wetuwns the wogicaw CPU id when found. Othewwise wetuwns 0.
 */
static int acpi_cowesight_get_cpu(stwuct device *dev)
{
	int cpu;
	acpi_handwe cpu_handwe;
	acpi_status status;
	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	if (!adev)
		wetuwn -ENODEV;
	status = acpi_get_pawent(adev->handwe, &cpu_handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	cpu = acpi_handwe_to_wogicaw_cpuid(cpu_handwe);
	if (cpu >= nw_cpu_ids)
		wetuwn -ENODEV;
	wetuwn cpu;
}

static int
acpi_get_cowesight_pwatfowm_data(stwuct device *dev,
				 stwuct cowesight_pwatfowm_data *pdata)
{
	stwuct acpi_device *adev;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn -EINVAW;

	wetuwn acpi_cowesight_pawse_gwaph(dev, adev, pdata);
}

#ewse

static inwine int
acpi_get_cowesight_pwatfowm_data(stwuct device *dev,
				 stwuct cowesight_pwatfowm_data *pdata)
{
	wetuwn -ENOENT;
}

static inwine int acpi_cowesight_get_cpu(stwuct device *dev)
{
	wetuwn -ENODEV;
}
#endif

int cowesight_get_cpu(stwuct device *dev)
{
	if (is_of_node(dev->fwnode))
		wetuwn of_cowesight_get_cpu(dev);
	ewse if (is_acpi_device_node(dev->fwnode))
		wetuwn acpi_cowesight_get_cpu(dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cowesight_get_cpu);

stwuct cowesight_pwatfowm_data *
cowesight_get_pwatfowm_data(stwuct device *dev)
{
	int wet = -ENOENT;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);

	if (IS_EWW_OW_NUWW(fwnode))
		goto ewwow;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata) {
		wet = -ENOMEM;
		goto ewwow;
	}

	if (is_of_node(fwnode))
		wet = of_get_cowesight_pwatfowm_data(dev, pdata);
	ewse if (is_acpi_device_node(fwnode))
		wet = acpi_get_cowesight_pwatfowm_data(dev, pdata);

	if (!wet)
		wetuwn pdata;
ewwow:
	if (!IS_EWW_OW_NUWW(pdata))
		/* Cweanup the connection infowmation */
		cowesight_wewease_pwatfowm_data(NUWW, dev, pdata);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(cowesight_get_pwatfowm_data);
