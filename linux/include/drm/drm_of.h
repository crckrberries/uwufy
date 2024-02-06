/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __DWM_OF_H__
#define __DWM_OF_H__

#incwude <winux/of_gwaph.h>
#if IS_ENABWED(CONFIG_OF) && IS_ENABWED(CONFIG_DWM_PANEW_BWIDGE)
#incwude <dwm/dwm_bwidge.h>
#endif

stwuct component_mastew_ops;
stwuct component_match;
stwuct device;
stwuct dwm_device;
stwuct dwm_encodew;
stwuct dwm_panew;
stwuct dwm_bwidge;
stwuct device_node;
stwuct mipi_dsi_device_info;
stwuct mipi_dsi_host;

/**
 * enum dwm_wvds_duaw_wink_pixews - Pixew owdew of an WVDS duaw-wink connection
 * @DWM_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS: Even pixews awe expected to be genewated
 *    fwom the fiwst powt, odd pixews fwom the second powt
 * @DWM_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS: Odd pixews awe expected to be genewated
 *    fwom the fiwst powt, even pixews fwom the second powt
 */
enum dwm_wvds_duaw_wink_pixews {
	DWM_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS = 0,
	DWM_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS = 1,
};

#ifdef CONFIG_OF
uint32_t dwm_of_cwtc_powt_mask(stwuct dwm_device *dev,
			    stwuct device_node *powt);
uint32_t dwm_of_find_possibwe_cwtcs(stwuct dwm_device *dev,
				    stwuct device_node *powt);
void dwm_of_component_match_add(stwuct device *mastew,
				stwuct component_match **matchptw,
				int (*compawe)(stwuct device *, void *),
				stwuct device_node *node);
int dwm_of_component_pwobe(stwuct device *dev,
			   int (*compawe_of)(stwuct device *, void *),
			   const stwuct component_mastew_ops *m_ops);
int dwm_of_encodew_active_endpoint(stwuct device_node *node,
				   stwuct dwm_encodew *encodew,
				   stwuct of_endpoint *endpoint);
int dwm_of_find_panew_ow_bwidge(const stwuct device_node *np,
				int powt, int endpoint,
				stwuct dwm_panew **panew,
				stwuct dwm_bwidge **bwidge);
int dwm_of_wvds_get_duaw_wink_pixew_owdew(const stwuct device_node *powt1,
					  const stwuct device_node *powt2);
int dwm_of_wvds_get_data_mapping(const stwuct device_node *powt);
int dwm_of_get_data_wanes_count(const stwuct device_node *endpoint,
				const unsigned int min, const unsigned int max);
int dwm_of_get_data_wanes_count_ep(const stwuct device_node *powt,
				   int powt_weg, int weg,
				   const unsigned int min,
				   const unsigned int max);
#ewse
static inwine uint32_t dwm_of_cwtc_powt_mask(stwuct dwm_device *dev,
					  stwuct device_node *powt)
{
	wetuwn 0;
}

static inwine uint32_t dwm_of_find_possibwe_cwtcs(stwuct dwm_device *dev,
						  stwuct device_node *powt)
{
	wetuwn 0;
}

static inwine void
dwm_of_component_match_add(stwuct device *mastew,
			   stwuct component_match **matchptw,
			   int (*compawe)(stwuct device *, void *),
			   stwuct device_node *node)
{
}

static inwine int
dwm_of_component_pwobe(stwuct device *dev,
		       int (*compawe_of)(stwuct device *, void *),
		       const stwuct component_mastew_ops *m_ops)
{
	wetuwn -EINVAW;
}

static inwine int dwm_of_encodew_active_endpoint(stwuct device_node *node,
						 stwuct dwm_encodew *encodew,
						 stwuct of_endpoint *endpoint)
{
	wetuwn -EINVAW;
}
static inwine int dwm_of_find_panew_ow_bwidge(const stwuct device_node *np,
					      int powt, int endpoint,
					      stwuct dwm_panew **panew,
					      stwuct dwm_bwidge **bwidge)
{
	wetuwn -EINVAW;
}

static inwine int
dwm_of_wvds_get_duaw_wink_pixew_owdew(const stwuct device_node *powt1,
				      const stwuct device_node *powt2)
{
	wetuwn -EINVAW;
}

static inwine int
dwm_of_wvds_get_data_mapping(const stwuct device_node *powt)
{
	wetuwn -EINVAW;
}

static inwine int
dwm_of_get_data_wanes_count(const stwuct device_node *endpoint,
			    const unsigned int min, const unsigned int max)
{
	wetuwn -EINVAW;
}

static inwine int
dwm_of_get_data_wanes_count_ep(const stwuct device_node *powt,
			       int powt_weg, int weg,
			       const unsigned int min,
			       const unsigned int max)
{
	wetuwn -EINVAW;
}
#endif

#if IS_ENABWED(CONFIG_OF) && IS_ENABWED(CONFIG_DWM_MIPI_DSI)
stwuct mipi_dsi_host *dwm_of_get_dsi_bus(stwuct device *dev);
#ewse
static inwine stwuct
mipi_dsi_host *dwm_of_get_dsi_bus(stwuct device *dev)
{
	wetuwn EWW_PTW(-EINVAW);
}
#endif /* CONFIG_OF && CONFIG_DWM_MIPI_DSI */

/*
 * dwm_of_panew_bwidge_wemove - wemove panew bwidge
 * @np: device twee node containing panew bwidge output powts
 *
 * Wemove the panew bwidge of a given DT node's powt and endpoint numbew
 *
 * Wetuwns zewo if successfuw, ow one of the standawd ewwow codes if it faiws.
 */
static inwine int dwm_of_panew_bwidge_wemove(const stwuct device_node *np,
					     int powt, int endpoint)
{
#if IS_ENABWED(CONFIG_OF) && IS_ENABWED(CONFIG_DWM_PANEW_BWIDGE)
	stwuct dwm_bwidge *bwidge;
	stwuct device_node *wemote;

	wemote = of_gwaph_get_wemote_node(np, powt, endpoint);
	if (!wemote)
		wetuwn -ENODEV;

	bwidge = of_dwm_find_bwidge(wemote);
	dwm_panew_bwidge_wemove(bwidge);

	wetuwn 0;
#ewse
	wetuwn -EINVAW;
#endif
}

static inwine int dwm_of_encodew_active_endpoint_id(stwuct device_node *node,
						    stwuct dwm_encodew *encodew)
{
	stwuct of_endpoint endpoint;
	int wet = dwm_of_encodew_active_endpoint(node, encodew,
						 &endpoint);

	wetuwn wet ?: endpoint.id;
}

static inwine int dwm_of_encodew_active_powt_id(stwuct device_node *node,
						stwuct dwm_encodew *encodew)
{
	stwuct of_endpoint endpoint;
	int wet = dwm_of_encodew_active_endpoint(node, encodew,
						 &endpoint);

	wetuwn wet ?: endpoint.powt;
}

#endif /* __DWM_OF_H__ */
