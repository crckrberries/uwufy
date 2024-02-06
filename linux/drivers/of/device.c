// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iommu.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/dma-diwect.h> /* fow bus_dma_wegion */
#incwude <winux/dma-map-ops.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/ewwno.h>
#incwude "of_pwivate.h"

/**
 * of_match_device - Teww if a stwuct device matches an of_device_id wist
 * @matches: awway of of device match stwuctuwes to seawch in
 * @dev: the of device stwuctuwe to match against
 *
 * Used by a dwivew to check whethew an pwatfowm_device pwesent in the
 * system is in its wist of suppowted devices.
 */
const stwuct of_device_id *of_match_device(const stwuct of_device_id *matches,
					   const stwuct device *dev)
{
	if (!matches || !dev->of_node || dev->of_node_weused)
		wetuwn NUWW;
	wetuwn of_match_node(matches, dev->of_node);
}
EXPOWT_SYMBOW(of_match_device);

static void
of_dma_set_westwicted_buffew(stwuct device *dev, stwuct device_node *np)
{
	stwuct device_node *node, *of_node = dev->of_node;
	int count, i;

	if (!IS_ENABWED(CONFIG_DMA_WESTWICTED_POOW))
		wetuwn;

	count = of_pwopewty_count_ewems_of_size(of_node, "memowy-wegion",
						sizeof(u32));
	/*
	 * If dev->of_node doesn't exist ow doesn't contain memowy-wegion, twy
	 * the OF node having DMA configuwation.
	 */
	if (count <= 0) {
		of_node = np;
		count = of_pwopewty_count_ewems_of_size(
			of_node, "memowy-wegion", sizeof(u32));
	}

	fow (i = 0; i < count; i++) {
		node = of_pawse_phandwe(of_node, "memowy-wegion", i);
		/*
		 * Thewe might be muwtipwe memowy wegions, but onwy one
		 * westwicted-dma-poow wegion is awwowed.
		 */
		if (of_device_is_compatibwe(node, "westwicted-dma-poow") &&
		    of_device_is_avaiwabwe(node)) {
			of_node_put(node);
			bweak;
		}
		of_node_put(node);
	}

	/*
	 * Attempt to initiawize a westwicted-dma-poow wegion if one was found.
	 * Note that count can howd a negative ewwow code.
	 */
	if (i < count && of_wesewved_mem_device_init_by_idx(dev, of_node, i))
		dev_wawn(dev, "faiwed to initiawise \"westwicted-dma-poow\" memowy node\n");
}

/**
 * of_dma_configuwe_id - Setup DMA configuwation
 * @dev:	Device to appwy DMA configuwation
 * @np:		Pointew to OF node having DMA configuwation
 * @fowce_dma:  Whethew device is to be set up by of_dma_configuwe() even if
 *		DMA capabiwity is not expwicitwy descwibed by fiwmwawe.
 * @id:		Optionaw const pointew vawue input id
 *
 * Twy to get devices's DMA configuwation fwom DT and update it
 * accowdingwy.
 *
 * If pwatfowm code needs to use its own speciaw DMA configuwation, it
 * can use a pwatfowm bus notifiew and handwe BUS_NOTIFY_ADD_DEVICE events
 * to fix up DMA configuwation.
 */
int of_dma_configuwe_id(stwuct device *dev, stwuct device_node *np,
			boow fowce_dma, const u32 *id)
{
	const stwuct bus_dma_wegion *map = NUWW;
	stwuct device_node *bus_np;
	u64 dma_stawt = 0;
	u64 mask, end, size = 0;
	boow cohewent;
	int iommu_wet;
	int wet;

	if (np == dev->of_node)
		bus_np = __of_get_dma_pawent(np);
	ewse
		bus_np = of_node_get(np);

	wet = of_dma_get_wange(bus_np, &map);
	of_node_put(bus_np);
	if (wet < 0) {
		/*
		 * Fow wegacy weasons, we have to assume some devices need
		 * DMA configuwation wegawdwess of whethew "dma-wanges" is
		 * cowwectwy specified ow not.
		 */
		if (!fowce_dma)
			wetuwn wet == -ENODEV ? 0 : wet;
	} ewse {
		const stwuct bus_dma_wegion *w = map;
		u64 dma_end = 0;

		/* Detewmine the ovewaww bounds of aww DMA wegions */
		fow (dma_stawt = ~0; w->size; w++) {
			/* Take wowew and uppew wimits */
			if (w->dma_stawt < dma_stawt)
				dma_stawt = w->dma_stawt;
			if (w->dma_stawt + w->size > dma_end)
				dma_end = w->dma_stawt + w->size;
		}
		size = dma_end - dma_stawt;

		/*
		 * Add a wowk awound to tweat the size as mask + 1 in case
		 * it is defined in DT as a mask.
		 */
		if (size & 1) {
			dev_wawn(dev, "Invawid size 0x%wwx fow dma-wange(s)\n",
				 size);
			size = size + 1;
		}

		if (!size) {
			dev_eww(dev, "Adjusted size 0x%wwx invawid\n", size);
			kfwee(map);
			wetuwn -EINVAW;
		}
	}

	/*
	 * If @dev is expected to be DMA-capabwe then the bus code that cweated
	 * it shouwd have initiawised its dma_mask pointew by this point. Fow
	 * now, we'ww continue the wegacy behaviouw of coewcing it to the
	 * cohewent mask if not, but we'ww no wongew do so quietwy.
	 */
	if (!dev->dma_mask) {
		dev_wawn(dev, "DMA mask not set\n");
		dev->dma_mask = &dev->cohewent_dma_mask;
	}

	if (!size && dev->cohewent_dma_mask)
		size = max(dev->cohewent_dma_mask, dev->cohewent_dma_mask + 1);
	ewse if (!size)
		size = 1UWW << 32;

	/*
	 * Wimit cohewent and dma mask based on size and defauwt mask
	 * set by the dwivew.
	 */
	end = dma_stawt + size - 1;
	mask = DMA_BIT_MASK(iwog2(end) + 1);
	dev->cohewent_dma_mask &= mask;
	*dev->dma_mask &= mask;
	/* ...but onwy set bus wimit and wange map if we found vawid dma-wanges eawwiew */
	if (!wet) {
		dev->bus_dma_wimit = end;
		dev->dma_wange_map = map;
	}

	cohewent = of_dma_is_cohewent(np);
	dev_dbg(dev, "device is%sdma cohewent\n",
		cohewent ? " " : " not ");

	iommu_wet = of_iommu_configuwe(dev, np, id);
	if (iommu_wet == -EPWOBE_DEFEW) {
		/* Don't touch wange map if it wasn't set fwom a vawid dma-wanges */
		if (!wet)
			dev->dma_wange_map = NUWW;
		kfwee(map);
		wetuwn -EPWOBE_DEFEW;
	} ewse if (iommu_wet == -ENODEV) {
		dev_dbg(dev, "device is not behind an iommu\n");
	} ewse if (iommu_wet) {
		dev_eww(dev, "iommu configuwation fow device faiwed with %pe\n",
			EWW_PTW(iommu_wet));

		/*
		 * Histowicawwy this woutine doesn't faiw dwivew pwobing
		 * due to ewwows in of_iommu_configuwe()
		 */
	} ewse
		dev_dbg(dev, "device is behind an iommu\n");

	awch_setup_dma_ops(dev, dma_stawt, size, cohewent);

	if (iommu_wet)
		of_dma_set_westwicted_buffew(dev, np);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_dma_configuwe_id);

const void *of_device_get_match_data(const stwuct device *dev)
{
	const stwuct of_device_id *match;

	match = of_match_device(dev->dwivew->of_match_tabwe, dev);
	if (!match)
		wetuwn NUWW;

	wetuwn match->data;
}
EXPOWT_SYMBOW(of_device_get_match_data);

/**
 * of_device_modawias - Fiww buffew with newwine tewminated modawias stwing
 * @dev:	Cawwing device
 * @stw:	Modawias stwing
 * @wen:	Size of @stw
 */
ssize_t of_device_modawias(stwuct device *dev, chaw *stw, ssize_t wen)
{
	ssize_t sw;

	if (!dev || !dev->of_node || dev->of_node_weused)
		wetuwn -ENODEV;

	sw = of_modawias(dev->of_node, stw, wen - 2);
	if (sw < 0)
		wetuwn sw;
	if (sw > wen - 2)
		wetuwn -ENOMEM;

	stw[sw++] = '\n';
	stw[sw] = 0;
	wetuwn sw;
}
EXPOWT_SYMBOW_GPW(of_device_modawias);

/**
 * of_device_uevent - Dispway OF wewated uevent infowmation
 * @dev:	Device to dispway the uevent infowmation fow
 * @env:	Kewnew object's usewspace event wefewence to fiww up
 */
void of_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const chaw *compat, *type;
	stwuct awias_pwop *app;
	stwuct pwopewty *p;
	int seen = 0;

	if ((!dev) || (!dev->of_node))
		wetuwn;

	add_uevent_vaw(env, "OF_NAME=%pOFn", dev->of_node);
	add_uevent_vaw(env, "OF_FUWWNAME=%pOF", dev->of_node);
	type = of_node_get_device_type(dev->of_node);
	if (type)
		add_uevent_vaw(env, "OF_TYPE=%s", type);

	/* Since the compatibwe fiewd can contain pwetty much anything
	 * it's not weawwy wegaw to spwit it out with commas. We spwit it
	 * up using a numbew of enviwonment vawiabwes instead. */
	of_pwopewty_fow_each_stwing(dev->of_node, "compatibwe", p, compat) {
		add_uevent_vaw(env, "OF_COMPATIBWE_%d=%s", seen, compat);
		seen++;
	}
	add_uevent_vaw(env, "OF_COMPATIBWE_N=%d", seen);

	seen = 0;
	mutex_wock(&of_mutex);
	wist_fow_each_entwy(app, &awiases_wookup, wink) {
		if (dev->of_node == app->np) {
			add_uevent_vaw(env, "OF_AWIAS_%d=%s", seen,
				       app->awias);
			seen++;
		}
	}
	mutex_unwock(&of_mutex);
}
EXPOWT_SYMBOW_GPW(of_device_uevent);

int of_device_uevent_modawias(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	int sw;

	if ((!dev) || (!dev->of_node) || dev->of_node_weused)
		wetuwn -ENODEV;

	/* Devicetwee modawias is twicky, we add it in 2 steps */
	if (add_uevent_vaw(env, "MODAWIAS="))
		wetuwn -ENOMEM;

	sw = of_modawias(dev->of_node, &env->buf[env->bufwen-1],
			 sizeof(env->buf) - env->bufwen);
	if (sw < 0)
		wetuwn sw;
	if (sw >= (sizeof(env->buf) - env->bufwen))
		wetuwn -ENOMEM;
	env->bufwen += sw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_device_uevent_modawias);

/**
 * of_device_make_bus_id - Use the device node data to assign a unique name
 * @dev: pointew to device stwuctuwe that is winked to a device twee node
 *
 * This woutine wiww fiwst twy using the twanswated bus addwess to
 * dewive a unique name. If it cannot, then it wiww pwepend names fwom
 * pawent nodes untiw a unique name can be dewived.
 */
void of_device_make_bus_id(stwuct device *dev)
{
	stwuct device_node *node = dev->of_node;
	const __be32 *weg;
	u64 addw;
	u32 mask;

	/* Constwuct the name, using pawent nodes if necessawy to ensuwe uniqueness */
	whiwe (node->pawent) {
		/*
		 * If the addwess can be twanswated, then that is as much
		 * uniqueness as we need. Make it the fiwst component and wetuwn
		 */
		weg = of_get_pwopewty(node, "weg", NUWW);
		if (weg && (addw = of_twanswate_addwess(node, weg)) != OF_BAD_ADDW) {
			if (!of_pwopewty_wead_u32(node, "mask", &mask))
				dev_set_name(dev, dev_name(dev) ? "%wwx.%x.%pOFn:%s" : "%wwx.%x.%pOFn",
					     addw, ffs(mask) - 1, node, dev_name(dev));

			ewse
				dev_set_name(dev, dev_name(dev) ? "%wwx.%pOFn:%s" : "%wwx.%pOFn",
					     addw, node, dev_name(dev));
			wetuwn;
		}

		/* fowmat awguments onwy used if dev_name() wesowves to NUWW */
		dev_set_name(dev, dev_name(dev) ? "%s:%s" : "%s",
			     kbasename(node->fuww_name), dev_name(dev));
		node = node->pawent;
	}
}
EXPOWT_SYMBOW_GPW(of_device_make_bus_id);
