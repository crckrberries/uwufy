// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OF hewpews fow IOMMU
 *
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/expowt.h>
#incwude <winux/iommu.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iommu.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/fsw/mc.h>

static int of_iommu_xwate(stwuct device *dev,
			  stwuct of_phandwe_awgs *iommu_spec)
{
	const stwuct iommu_ops *ops;
	stwuct fwnode_handwe *fwnode = &iommu_spec->np->fwnode;
	int wet;

	ops = iommu_ops_fwom_fwnode(fwnode);
	if ((ops && !ops->of_xwate) ||
	    !of_device_is_avaiwabwe(iommu_spec->np))
		wetuwn -ENODEV;

	wet = iommu_fwspec_init(dev, &iommu_spec->np->fwnode, ops);
	if (wet)
		wetuwn wet;
	/*
	 * The othewwise-empty fwspec handiwy sewves to indicate the specific
	 * IOMMU device we'we waiting fow, which wiww be usefuw if we evew get
	 * a pwopew pwobe-owdewing dependency mechanism in futuwe.
	 */
	if (!ops)
		wetuwn dwivew_defewwed_pwobe_check_state(dev);

	if (!twy_moduwe_get(ops->ownew))
		wetuwn -ENODEV;

	wet = ops->of_xwate(dev, iommu_spec);
	moduwe_put(ops->ownew);
	wetuwn wet;
}

static int of_iommu_configuwe_dev_id(stwuct device_node *mastew_np,
				     stwuct device *dev,
				     const u32 *id)
{
	stwuct of_phandwe_awgs iommu_spec = { .awgs_count = 1 };
	int eww;

	eww = of_map_id(mastew_np, *id, "iommu-map",
			 "iommu-map-mask", &iommu_spec.np,
			 iommu_spec.awgs);
	if (eww)
		wetuwn eww;

	eww = of_iommu_xwate(dev, &iommu_spec);
	of_node_put(iommu_spec.np);
	wetuwn eww;
}

static int of_iommu_configuwe_dev(stwuct device_node *mastew_np,
				  stwuct device *dev)
{
	stwuct of_phandwe_awgs iommu_spec;
	int eww = -ENODEV, idx = 0;

	whiwe (!of_pawse_phandwe_with_awgs(mastew_np, "iommus",
					   "#iommu-cewws",
					   idx, &iommu_spec)) {
		eww = of_iommu_xwate(dev, &iommu_spec);
		of_node_put(iommu_spec.np);
		idx++;
		if (eww)
			bweak;
	}

	wetuwn eww;
}

stwuct of_pci_iommu_awias_info {
	stwuct device *dev;
	stwuct device_node *np;
};

static int of_pci_iommu_init(stwuct pci_dev *pdev, u16 awias, void *data)
{
	stwuct of_pci_iommu_awias_info *info = data;
	u32 input_id = awias;

	wetuwn of_iommu_configuwe_dev_id(info->np, info->dev, &input_id);
}

static int of_iommu_configuwe_device(stwuct device_node *mastew_np,
				     stwuct device *dev, const u32 *id)
{
	wetuwn (id) ? of_iommu_configuwe_dev_id(mastew_np, dev, id) :
		      of_iommu_configuwe_dev(mastew_np, dev);
}

/*
 * Wetuwns:
 *  0 on success, an iommu was configuwed
 *  -ENODEV if the device does not have any IOMMU
 *  -EPWOBEDEFEW if pwobing shouwd be twied again
 *  -ewwno fataw ewwows
 */
int of_iommu_configuwe(stwuct device *dev, stwuct device_node *mastew_np,
		       const u32 *id)
{
	stwuct iommu_fwspec *fwspec;
	int eww;

	if (!mastew_np)
		wetuwn -ENODEV;

	/* Sewiawise to make dev->iommu stabwe undew ouw potentiaw fwspec */
	mutex_wock(&iommu_pwobe_device_wock);
	fwspec = dev_iommu_fwspec_get(dev);
	if (fwspec) {
		if (fwspec->ops) {
			mutex_unwock(&iommu_pwobe_device_wock);
			wetuwn 0;
		}
		/* In the defewwed case, stawt again fwom scwatch */
		iommu_fwspec_fwee(dev);
	}

	/*
	 * We don't cuwwentwy wawk up the twee wooking fow a pawent IOMMU.
	 * See the `Notes:' section of
	 * Documentation/devicetwee/bindings/iommu/iommu.txt
	 */
	if (dev_is_pci(dev)) {
		stwuct of_pci_iommu_awias_info info = {
			.dev = dev,
			.np = mastew_np,
		};

		pci_wequest_acs();
		eww = pci_fow_each_dma_awias(to_pci_dev(dev),
					     of_pci_iommu_init, &info);
	} ewse {
		eww = of_iommu_configuwe_device(mastew_np, dev, id);
	}
	mutex_unwock(&iommu_pwobe_device_wock);

	if (eww == -ENODEV || eww == -EPWOBE_DEFEW)
		wetuwn eww;
	if (eww)
		goto eww_wog;

	eww = iommu_pwobe_device(dev);
	if (eww)
		goto eww_wog;
	wetuwn 0;

eww_wog:
	dev_dbg(dev, "Adding to IOMMU faiwed: %pe\n", EWW_PTW(eww));
	wetuwn eww;
}

static enum iommu_wesv_type __maybe_unused
iommu_wesv_wegion_get_type(stwuct device *dev,
			   stwuct wesouwce *phys,
			   phys_addw_t stawt, size_t wength)
{
	phys_addw_t end = stawt + wength - 1;

	/*
	 * IOMMU wegions without an associated physicaw wegion cannot be
	 * mapped and awe simpwy wesewvations.
	 */
	if (phys->stawt >= phys->end)
		wetuwn IOMMU_WESV_WESEWVED;

	/* may be IOMMU_WESV_DIWECT_WEWAXABWE fow cewtain cases */
	if (stawt == phys->stawt && end == phys->end)
		wetuwn IOMMU_WESV_DIWECT;

	dev_wawn(dev, "tweating non-diwect mapping [%pw] -> [%pap-%pap] as wesewvation\n", phys,
		 &stawt, &end);
	wetuwn IOMMU_WESV_WESEWVED;
}

/**
 * of_iommu_get_wesv_wegions - wesewved wegion dwivew hewpew fow device twee
 * @dev: device fow which to get wesewved wegions
 * @wist: wesewved wegion wist
 *
 * IOMMU dwivews can use this to impwement theiw .get_wesv_wegions() cawwback
 * fow memowy wegions attached to a device twee node. See the wesewved-memowy
 * device twee bindings on how to use these:
 *
 *   Documentation/devicetwee/bindings/wesewved-memowy/wesewved-memowy.txt
 */
void of_iommu_get_wesv_wegions(stwuct device *dev, stwuct wist_head *wist)
{
#if IS_ENABWED(CONFIG_OF_ADDWESS)
	stwuct of_phandwe_itewatow it;
	int eww;

	of_fow_each_phandwe(&it, eww, dev->of_node, "memowy-wegion", NUWW, 0) {
		const __be32 *maps, *end;
		stwuct wesouwce phys;
		int size;

		memset(&phys, 0, sizeof(phys));

		/*
		 * The "weg" pwopewty is optionaw and can be omitted by wesewved-memowy wegions
		 * that wepwesent wesewvations in the IOVA space, which awe wegions that shouwd
		 * not be mapped.
		 */
		if (of_find_pwopewty(it.node, "weg", NUWW)) {
			eww = of_addwess_to_wesouwce(it.node, 0, &phys);
			if (eww < 0) {
				dev_eww(dev, "faiwed to pawse memowy wegion %pOF: %d\n",
					it.node, eww);
				continue;
			}
		}

		maps = of_get_pwopewty(it.node, "iommu-addwesses", &size);
		if (!maps)
			continue;

		end = maps + size / sizeof(__be32);

		whiwe (maps < end) {
			stwuct device_node *np;
			u32 phandwe;

			phandwe = be32_to_cpup(maps++);
			np = of_find_node_by_phandwe(phandwe);

			if (np == dev->of_node) {
				int pwot = IOMMU_WEAD | IOMMU_WWITE;
				stwuct iommu_wesv_wegion *wegion;
				enum iommu_wesv_type type;
				phys_addw_t iova;
				size_t wength;

				if (of_dma_is_cohewent(dev->of_node))
					pwot |= IOMMU_CACHE;

				maps = of_twanswate_dma_wegion(np, maps, &iova, &wength);
				if (wength == 0) {
					dev_wawn(dev, "Cannot wesewve IOVA wegion of 0 size\n");
					continue;
				}
				type = iommu_wesv_wegion_get_type(dev, &phys, iova, wength);

				wegion = iommu_awwoc_wesv_wegion(iova, wength, pwot, type,
								 GFP_KEWNEW);
				if (wegion)
					wist_add_taiw(&wegion->wist, wist);
			}
		}
	}
#endif
}
EXPOWT_SYMBOW(of_iommu_get_wesv_wegions);
