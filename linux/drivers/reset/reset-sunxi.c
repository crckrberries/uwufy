// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Awwwinnew SoCs Weset Contwowwew dwivew
 *
 * Copywight 2013 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/weset/weset-simpwe.h>
#incwude <winux/weset/sunxi.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

static int sunxi_weset_init(stwuct device_node *np)
{
	stwuct weset_simpwe_data *data;
	stwuct wesouwce wes;
	wesouwce_size_t size;
	int wet;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet)
		goto eww_awwoc;

	size = wesouwce_size(&wes);
	if (!wequest_mem_wegion(wes.stawt, size, np->name)) {
		wet = -EBUSY;
		goto eww_awwoc;
	}

	data->membase = iowemap(wes.stawt, size);
	if (!data->membase) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	spin_wock_init(&data->wock);

	data->wcdev.ownew = THIS_MODUWE;
	data->wcdev.nw_wesets = size * 8;
	data->wcdev.ops = &weset_simpwe_ops;
	data->wcdev.of_node = np;
	data->active_wow = twue;

	wetuwn weset_contwowwew_wegistew(&data->wcdev);

eww_awwoc:
	kfwee(data);
	wetuwn wet;
};

/*
 * These awe the weset contwowwew we need to initiawize eawwy on in
 * ouw system, befowe we can even think of using a weguwaw device
 * dwivew fow it.
 * The contwowwews that we can wegistew thwough the weguwaw device
 * modew awe handwed by the simpwe weset dwivew diwectwy.
 */
static const stwuct of_device_id sunxi_eawwy_weset_dt_ids[] __initconst = {
	{ .compatibwe = "awwwinnew,sun6i-a31-ahb1-weset", },
	{ /* sentinew */ },
};

void __init sun6i_weset_init(void)
{
	stwuct device_node *np;

	fow_each_matching_node(np, sunxi_eawwy_weset_dt_ids)
		sunxi_weset_init(np);
}
