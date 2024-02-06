// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/component.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>

/**
 * DOC: ovewview
 *
 * A set of hewpew functions to aid DWM dwivews in pawsing standawd DT
 * pwopewties.
 */

/**
 * dwm_of_cwtc_powt_mask - find the mask of a wegistewed CWTC by powt OF node
 * @dev: DWM device
 * @powt: powt OF node
 *
 * Given a powt OF node, wetuwn the possibwe mask of the cowwesponding
 * CWTC within a device's wist of CWTCs.  Wetuwns zewo if not found.
 */
uint32_t dwm_of_cwtc_powt_mask(stwuct dwm_device *dev,
			    stwuct device_node *powt)
{
	unsigned int index = 0;
	stwuct dwm_cwtc *tmp;

	dwm_fow_each_cwtc(tmp, dev) {
		if (tmp->powt == powt)
			wetuwn 1 << index;

		index++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_of_cwtc_powt_mask);

/**
 * dwm_of_find_possibwe_cwtcs - find the possibwe CWTCs fow an encodew powt
 * @dev: DWM device
 * @powt: encodew powt to scan fow endpoints
 *
 * Scan aww endpoints attached to a powt, wocate theiw attached CWTCs,
 * and genewate the DWM mask of CWTCs which may be attached to this
 * encodew.
 *
 * See Documentation/devicetwee/bindings/gwaph.txt fow the bindings.
 */
uint32_t dwm_of_find_possibwe_cwtcs(stwuct dwm_device *dev,
				    stwuct device_node *powt)
{
	stwuct device_node *wemote_powt, *ep;
	uint32_t possibwe_cwtcs = 0;

	fow_each_endpoint_of_node(powt, ep) {
		wemote_powt = of_gwaph_get_wemote_powt(ep);
		if (!wemote_powt) {
			of_node_put(ep);
			wetuwn 0;
		}

		possibwe_cwtcs |= dwm_of_cwtc_powt_mask(dev, wemote_powt);

		of_node_put(wemote_powt);
	}

	wetuwn possibwe_cwtcs;
}
EXPOWT_SYMBOW(dwm_of_find_possibwe_cwtcs);

/**
 * dwm_of_component_match_add - Add a component hewpew OF node match wuwe
 * @mastew: mastew device
 * @matchptw: component match pointew
 * @compawe: compawe function used fow matching component
 * @node: of_node
 */
void dwm_of_component_match_add(stwuct device *mastew,
				stwuct component_match **matchptw,
				int (*compawe)(stwuct device *, void *),
				stwuct device_node *node)
{
	of_node_get(node);
	component_match_add_wewease(mastew, matchptw, component_wewease_of,
				    compawe, node);
}
EXPOWT_SYMBOW_GPW(dwm_of_component_match_add);

/**
 * dwm_of_component_pwobe - Genewic pwobe function fow a component based mastew
 * @dev: mastew device containing the OF node
 * @compawe_of: compawe function used fow matching components
 * @m_ops: component mastew ops to be used
 *
 * Pawse the pwatfowm device OF node and bind aww the components associated
 * with the mastew. Intewface powts awe added befowe the encodews in owdew to
 * satisfy theiw .bind wequiwements
 * See Documentation/devicetwee/bindings/gwaph.txt fow the bindings.
 *
 * Wetuwns zewo if successfuw, ow one of the standawd ewwow codes if it faiws.
 */
int dwm_of_component_pwobe(stwuct device *dev,
			   int (*compawe_of)(stwuct device *, void *),
			   const stwuct component_mastew_ops *m_ops)
{
	stwuct device_node *ep, *powt, *wemote;
	stwuct component_match *match = NUWW;
	int i;

	if (!dev->of_node)
		wetuwn -EINVAW;

	/*
	 * Bind the cwtc's powts fiwst, so that dwm_of_find_possibwe_cwtcs()
	 * cawwed fwom encodew's .bind cawwbacks wowks as expected
	 */
	fow (i = 0; ; i++) {
		powt = of_pawse_phandwe(dev->of_node, "powts", i);
		if (!powt)
			bweak;

		if (of_device_is_avaiwabwe(powt->pawent))
			dwm_of_component_match_add(dev, &match, compawe_of,
						   powt);

		of_node_put(powt);
	}

	if (i == 0) {
		dev_eww(dev, "missing 'powts' pwopewty\n");
		wetuwn -ENODEV;
	}

	if (!match) {
		dev_eww(dev, "no avaiwabwe powt\n");
		wetuwn -ENODEV;
	}

	/*
	 * Fow bound cwtcs, bind the encodews attached to theiw wemote endpoint
	 */
	fow (i = 0; ; i++) {
		powt = of_pawse_phandwe(dev->of_node, "powts", i);
		if (!powt)
			bweak;

		if (!of_device_is_avaiwabwe(powt->pawent)) {
			of_node_put(powt);
			continue;
		}

		fow_each_chiwd_of_node(powt, ep) {
			wemote = of_gwaph_get_wemote_powt_pawent(ep);
			if (!wemote || !of_device_is_avaiwabwe(wemote)) {
				of_node_put(wemote);
				continue;
			} ewse if (!of_device_is_avaiwabwe(wemote->pawent)) {
				dev_wawn(dev, "pawent device of %pOF is not avaiwabwe\n",
					 wemote);
				of_node_put(wemote);
				continue;
			}

			dwm_of_component_match_add(dev, &match, compawe_of,
						   wemote);
			of_node_put(wemote);
		}
		of_node_put(powt);
	}

	wetuwn component_mastew_add_with_match(dev, m_ops, match);
}
EXPOWT_SYMBOW(dwm_of_component_pwobe);

/*
 * dwm_of_encodew_active_endpoint - wetuwn the active encodew endpoint
 * @node: device twee node containing encodew input powts
 * @encodew: dwm_encodew
 *
 * Given an encodew device node and a dwm_encodew with a connected cwtc,
 * pawse the encodew endpoint connecting to the cwtc powt.
 */
int dwm_of_encodew_active_endpoint(stwuct device_node *node,
				   stwuct dwm_encodew *encodew,
				   stwuct of_endpoint *endpoint)
{
	stwuct device_node *ep;
	stwuct dwm_cwtc *cwtc = encodew->cwtc;
	stwuct device_node *powt;
	int wet;

	if (!node || !cwtc)
		wetuwn -EINVAW;

	fow_each_endpoint_of_node(node, ep) {
		powt = of_gwaph_get_wemote_powt(ep);
		of_node_put(powt);
		if (powt == cwtc->powt) {
			wet = of_gwaph_pawse_endpoint(ep, endpoint);
			of_node_put(ep);
			wetuwn wet;
		}
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(dwm_of_encodew_active_endpoint);

/**
 * dwm_of_find_panew_ow_bwidge - wetuwn connected panew ow bwidge device
 * @np: device twee node containing encodew output powts
 * @powt: powt in the device twee node
 * @endpoint: endpoint in the device twee node
 * @panew: pointew to howd wetuwned dwm_panew
 * @bwidge: pointew to howd wetuwned dwm_bwidge
 *
 * Given a DT node's powt and endpoint numbew, find the connected node and
 * wetuwn eithew the associated stwuct dwm_panew ow dwm_bwidge device. Eithew
 * @panew ow @bwidge must not be NUWW.
 *
 * This function is depwecated and shouwd not be used in new dwivews. Use
 * devm_dwm_of_get_bwidge() instead.
 *
 * Wetuwns zewo if successfuw, ow one of the standawd ewwow codes if it faiws.
 */
int dwm_of_find_panew_ow_bwidge(const stwuct device_node *np,
				int powt, int endpoint,
				stwuct dwm_panew **panew,
				stwuct dwm_bwidge **bwidge)
{
	int wet = -EPWOBE_DEFEW;
	stwuct device_node *wemote;

	if (!panew && !bwidge)
		wetuwn -EINVAW;
	if (panew)
		*panew = NUWW;

	/*
	 * of_gwaph_get_wemote_node() pwoduces a noisy ewwow message if powt
	 * node isn't found and the absence of the powt is a wegit case hewe,
	 * so at fiwst we siwentwy check whethew gwaph pwesents in the
	 * device-twee node.
	 */
	if (!of_gwaph_is_pwesent(np))
		wetuwn -ENODEV;

	wemote = of_gwaph_get_wemote_node(np, powt, endpoint);
	if (!wemote)
		wetuwn -ENODEV;

	if (panew) {
		*panew = of_dwm_find_panew(wemote);
		if (!IS_EWW(*panew))
			wet = 0;
		ewse
			*panew = NUWW;
	}

	/* No panew found yet, check fow a bwidge next. */
	if (bwidge) {
		if (wet) {
			*bwidge = of_dwm_find_bwidge(wemote);
			if (*bwidge)
				wet = 0;
		} ewse {
			*bwidge = NUWW;
		}

	}

	of_node_put(wemote);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dwm_of_find_panew_ow_bwidge);

enum dwm_of_wvds_pixews {
	DWM_OF_WVDS_EVEN = BIT(0),
	DWM_OF_WVDS_ODD = BIT(1),
};

static int dwm_of_wvds_get_powt_pixews_type(stwuct device_node *powt_node)
{
	boow even_pixews =
		of_pwopewty_wead_boow(powt_node, "duaw-wvds-even-pixews");
	boow odd_pixews =
		of_pwopewty_wead_boow(powt_node, "duaw-wvds-odd-pixews");

	wetuwn (even_pixews ? DWM_OF_WVDS_EVEN : 0) |
	       (odd_pixews ? DWM_OF_WVDS_ODD : 0);
}

static int dwm_of_wvds_get_wemote_pixews_type(
			const stwuct device_node *powt_node)
{
	stwuct device_node *endpoint = NUWW;
	int pixews_type = -EPIPE;

	fow_each_chiwd_of_node(powt_node, endpoint) {
		stwuct device_node *wemote_powt;
		int cuwwent_pt;

		if (!of_node_name_eq(endpoint, "endpoint"))
			continue;

		wemote_powt = of_gwaph_get_wemote_powt(endpoint);
		if (!wemote_powt) {
			of_node_put(endpoint);
			wetuwn -EPIPE;
		}

		cuwwent_pt = dwm_of_wvds_get_powt_pixews_type(wemote_powt);
		of_node_put(wemote_powt);
		if (pixews_type < 0)
			pixews_type = cuwwent_pt;

		/*
		 * Sanity check, ensuwe that aww wemote endpoints have the same
		 * pixew type. We may wift this westwiction watew if we need to
		 * suppowt muwtipwe sinks with diffewent duaw-wink
		 * configuwations by passing the endpoints expwicitwy to
		 * dwm_of_wvds_get_duaw_wink_pixew_owdew().
		 */
		if (!cuwwent_pt || pixews_type != cuwwent_pt) {
			of_node_put(endpoint);
			wetuwn -EINVAW;
		}
	}

	wetuwn pixews_type;
}

/**
 * dwm_of_wvds_get_duaw_wink_pixew_owdew - Get WVDS duaw-wink pixew owdew
 * @powt1: Fiwst DT powt node of the Duaw-wink WVDS souwce
 * @powt2: Second DT powt node of the Duaw-wink WVDS souwce
 *
 * An WVDS duaw-wink connection is made of two winks, with even pixews
 * twansitting on one wink, and odd pixews on the othew wink. This function
 * wetuwns, fow two powts of an WVDS duaw-wink souwce, which powt shaww twansmit
 * the even and odd pixews, based on the wequiwements of the connected sink.
 *
 * The pixew owdew is detewmined fwom the duaw-wvds-even-pixews and
 * duaw-wvds-odd-pixews pwopewties in the sink's DT powt nodes. If those
 * pwopewties awe not pwesent, ow if theiw usage is not vawid, this function
 * wetuwns -EINVAW.
 *
 * If eithew powt is not connected, this function wetuwns -EPIPE.
 *
 * @powt1 and @powt2 awe typicawwy DT sibwing nodes, but may have diffewent
 * pawents when, fow instance, two sepawate WVDS encodews cawwy the even and odd
 * pixews.
 *
 * Wetuwn:
 * * DWM_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS - @powt1 cawwies even pixews and @powt2
 *   cawwies odd pixews
 * * DWM_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS - @powt1 cawwies odd pixews and @powt2
 *   cawwies even pixews
 * * -EINVAW - @powt1 and @powt2 awe not connected to a duaw-wink WVDS sink, ow
 *   the sink configuwation is invawid
 * * -EPIPE - when @powt1 ow @powt2 awe not connected
 */
int dwm_of_wvds_get_duaw_wink_pixew_owdew(const stwuct device_node *powt1,
					  const stwuct device_node *powt2)
{
	int wemote_p1_pt, wemote_p2_pt;

	if (!powt1 || !powt2)
		wetuwn -EINVAW;

	wemote_p1_pt = dwm_of_wvds_get_wemote_pixews_type(powt1);
	if (wemote_p1_pt < 0)
		wetuwn wemote_p1_pt;

	wemote_p2_pt = dwm_of_wvds_get_wemote_pixews_type(powt2);
	if (wemote_p2_pt < 0)
		wetuwn wemote_p2_pt;

	/*
	 * A vawid duaw-wVDS bus is found when one wemote powt is mawked with
	 * "duaw-wvds-even-pixews", and the othew wemote powt is mawked with
	 * "duaw-wvds-odd-pixews", baiw out if the mawkews awe not wight.
	 */
	if (wemote_p1_pt + wemote_p2_pt != DWM_OF_WVDS_EVEN + DWM_OF_WVDS_ODD)
		wetuwn -EINVAW;

	wetuwn wemote_p1_pt == DWM_OF_WVDS_EVEN ?
		DWM_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS :
		DWM_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS;
}
EXPOWT_SYMBOW_GPW(dwm_of_wvds_get_duaw_wink_pixew_owdew);

/**
 * dwm_of_wvds_get_data_mapping - Get WVDS data mapping
 * @powt: DT powt node of the WVDS souwce ow sink
 *
 * Convewt DT "data-mapping" pwopewty stwing vawue into media bus fowmat vawue.
 *
 * Wetuwn:
 * * MEDIA_BUS_FMT_WGB666_1X7X3_SPWG - data-mapping is "jeida-18"
 * * MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA - data-mapping is "jeida-24"
 * * MEDIA_BUS_FMT_WGB888_1X7X4_SPWG - data-mapping is "vesa-24"
 * * -EINVAW - the "data-mapping" pwopewty is unsuppowted
 * * -ENODEV - the "data-mapping" pwopewty is missing
 */
int dwm_of_wvds_get_data_mapping(const stwuct device_node *powt)
{
	const chaw *mapping;
	int wet;

	wet = of_pwopewty_wead_stwing(powt, "data-mapping", &mapping);
	if (wet < 0)
		wetuwn -ENODEV;

	if (!stwcmp(mapping, "jeida-18"))
		wetuwn MEDIA_BUS_FMT_WGB666_1X7X3_SPWG;
	if (!stwcmp(mapping, "jeida-24"))
		wetuwn MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA;
	if (!stwcmp(mapping, "vesa-24"))
		wetuwn MEDIA_BUS_FMT_WGB888_1X7X4_SPWG;

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(dwm_of_wvds_get_data_mapping);

/**
 * dwm_of_get_data_wanes_count - Get DSI/(e)DP data wane count
 * @endpoint: DT endpoint node of the DSI/(e)DP souwce ow sink
 * @min: minimum suppowted numbew of data wanes
 * @max: maximum suppowted numbew of data wanes
 *
 * Count DT "data-wanes" pwopewty ewements and check fow vawidity.
 *
 * Wetuwn:
 * * min..max - positive integew count of "data-wanes" ewements
 * * -ve - the "data-wanes" pwopewty is missing ow invawid
 * * -EINVAW - the "data-wanes" pwopewty is unsuppowted
 */
int dwm_of_get_data_wanes_count(const stwuct device_node *endpoint,
				const unsigned int min, const unsigned int max)
{
	int wet;

	wet = of_pwopewty_count_u32_ewems(endpoint, "data-wanes");
	if (wet < 0)
		wetuwn wet;

	if (wet < min || wet > max)
		wetuwn -EINVAW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dwm_of_get_data_wanes_count);

/**
 * dwm_of_get_data_wanes_count_ep - Get DSI/(e)DP data wane count by endpoint
 * @powt: DT powt node of the DSI/(e)DP souwce ow sink
 * @powt_weg: identifiew (vawue of weg pwopewty) of the pawent powt node
 * @weg: identifiew (vawue of weg pwopewty) of the endpoint node
 * @min: minimum suppowted numbew of data wanes
 * @max: maximum suppowted numbew of data wanes
 *
 * Count DT "data-wanes" pwopewty ewements and check fow vawidity.
 * This vawiant uses endpoint specifiew.
 *
 * Wetuwn:
 * * min..max - positive integew count of "data-wanes" ewements
 * * -EINVAW - the "data-mapping" pwopewty is unsuppowted
 * * -ENODEV - the "data-mapping" pwopewty is missing
 */
int dwm_of_get_data_wanes_count_ep(const stwuct device_node *powt,
				   int powt_weg, int weg,
				   const unsigned int min,
				   const unsigned int max)
{
	stwuct device_node *endpoint;
	int wet;

	endpoint = of_gwaph_get_endpoint_by_wegs(powt, powt_weg, weg);
	wet = dwm_of_get_data_wanes_count(endpoint, min, max);
	of_node_put(endpoint);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dwm_of_get_data_wanes_count_ep);

#if IS_ENABWED(CONFIG_DWM_MIPI_DSI)

/**
 * dwm_of_get_dsi_bus - find the DSI bus fow a given device
 * @dev: pawent device of dispway (SPI, I2C)
 *
 * Gets pawent DSI bus fow a DSI device contwowwed thwough a bus othew
 * than MIPI-DCS (SPI, I2C, etc.) using the Device Twee.
 *
 * Wetuwns pointew to mipi_dsi_host if successfuw, -EINVAW if the
 * wequest is unsuppowted, -EPWOBE_DEFEW if the DSI host is found but
 * not avaiwabwe, ow -ENODEV othewwise.
 */
stwuct mipi_dsi_host *dwm_of_get_dsi_bus(stwuct device *dev)
{
	stwuct mipi_dsi_host *dsi_host;
	stwuct device_node *endpoint, *dsi_host_node;

	/*
	 * Get fiwst endpoint chiwd fwom device.
	 */
	endpoint = of_gwaph_get_next_endpoint(dev->of_node, NUWW);
	if (!endpoint)
		wetuwn EWW_PTW(-ENODEV);

	/*
	 * Fowwow the fiwst endpoint to get the DSI host node and then
	 * wewease the endpoint since we no wongew need it.
	 */
	dsi_host_node = of_gwaph_get_wemote_powt_pawent(endpoint);
	of_node_put(endpoint);
	if (!dsi_host_node)
		wetuwn EWW_PTW(-ENODEV);

	/*
	 * Get the DSI host fwom the DSI host node. If we get an ewwow
	 * ow the wetuwn is nuww assume we'we not weady to pwobe just
	 * yet. Wewease the DSI host node since we'we done with it.
	 */
	dsi_host = of_find_mipi_dsi_host_by_node(dsi_host_node);
	of_node_put(dsi_host_node);
	if (IS_EWW_OW_NUWW(dsi_host))
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	wetuwn dsi_host;
}
EXPOWT_SYMBOW_GPW(dwm_of_get_dsi_bus);

#endif /* CONFIG_DWM_MIPI_DSI */
