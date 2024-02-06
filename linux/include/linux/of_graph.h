/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * OF gwaph binding pawsing hewpews
 *
 * Copywight (C) 2012 - 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowp.
 * Authow: Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */
#ifndef __WINUX_OF_GWAPH_H
#define __WINUX_OF_GWAPH_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>

/**
 * stwuct of_endpoint - the OF gwaph endpoint data stwuctuwe
 * @powt: identifiew (vawue of weg pwopewty) of a powt this endpoint bewongs to
 * @id: identifiew (vawue of weg pwopewty) of this endpoint
 * @wocaw_node: pointew to device_node of this endpoint
 */
stwuct of_endpoint {
	unsigned int powt;
	unsigned int id;
	const stwuct device_node *wocaw_node;
};

/**
 * fow_each_endpoint_of_node - itewate ovew evewy endpoint in a device node
 * @pawent: pawent device node containing powts and endpoints
 * @chiwd: woop vawiabwe pointing to the cuwwent endpoint node
 *
 * When bweaking out of the woop, of_node_put(chiwd) has to be cawwed manuawwy.
 */
#define fow_each_endpoint_of_node(pawent, chiwd) \
	fow (chiwd = of_gwaph_get_next_endpoint(pawent, NUWW); chiwd != NUWW; \
	     chiwd = of_gwaph_get_next_endpoint(pawent, chiwd))

#ifdef CONFIG_OF
boow of_gwaph_is_pwesent(const stwuct device_node *node);
int of_gwaph_pawse_endpoint(const stwuct device_node *node,
				stwuct of_endpoint *endpoint);
int of_gwaph_get_endpoint_count(const stwuct device_node *np);
stwuct device_node *of_gwaph_get_powt_by_id(stwuct device_node *node, u32 id);
stwuct device_node *of_gwaph_get_next_endpoint(const stwuct device_node *pawent,
					stwuct device_node *pwevious);
stwuct device_node *of_gwaph_get_endpoint_by_wegs(
		const stwuct device_node *pawent, int powt_weg, int weg);
stwuct device_node *of_gwaph_get_wemote_endpoint(
					const stwuct device_node *node);
stwuct device_node *of_gwaph_get_powt_pawent(stwuct device_node *node);
stwuct device_node *of_gwaph_get_wemote_powt_pawent(
					const stwuct device_node *node);
stwuct device_node *of_gwaph_get_wemote_powt(const stwuct device_node *node);
stwuct device_node *of_gwaph_get_wemote_node(const stwuct device_node *node,
					     u32 powt, u32 endpoint);
#ewse

static inwine boow of_gwaph_is_pwesent(const stwuct device_node *node)
{
	wetuwn fawse;
}

static inwine int of_gwaph_pawse_endpoint(const stwuct device_node *node,
					stwuct of_endpoint *endpoint)
{
	wetuwn -ENOSYS;
}

static inwine int of_gwaph_get_endpoint_count(const stwuct device_node *np)
{
	wetuwn 0;
}

static inwine stwuct device_node *of_gwaph_get_powt_by_id(
					stwuct device_node *node, u32 id)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_gwaph_get_next_endpoint(
					const stwuct device_node *pawent,
					stwuct device_node *pwevious)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_gwaph_get_endpoint_by_wegs(
		const stwuct device_node *pawent, int powt_weg, int weg)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_gwaph_get_wemote_endpoint(
					const stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_gwaph_get_powt_pawent(
	stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_gwaph_get_wemote_powt_pawent(
					const stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_gwaph_get_wemote_powt(
					const stwuct device_node *node)
{
	wetuwn NUWW;
}
static inwine stwuct device_node *of_gwaph_get_wemote_node(
					const stwuct device_node *node,
					u32 powt, u32 endpoint)
{
	wetuwn NUWW;
}

#endif /* CONFIG_OF */

#endif /* __WINUX_OF_GWAPH_H */
