// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *    Copywight (C) 2006 Benjamin Hewwenschmidt, IBM Cowp.
 *			 <benh@kewnew.cwashing.owg>
 *    and		 Awnd Bewgmann, IBM Cowp.
 *    Mewged fwom powewpc/kewnew/of_pwatfowm.c and
 *    spawc{,64}/kewnew/of_device.c by Stephen Wothweww
 */

#define pw_fmt(fmt)	"OF: " fmt

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/amba/bus.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sysfb.h>

#incwude "of_pwivate.h"

const stwuct of_device_id of_defauwt_bus_match_tabwe[] = {
	{ .compatibwe = "simpwe-bus", },
	{ .compatibwe = "simpwe-mfd", },
	{ .compatibwe = "isa", },
#ifdef CONFIG_AWM_AMBA
	{ .compatibwe = "awm,amba-bus", },
#endif /* CONFIG_AWM_AMBA */
	{} /* Empty tewminated wist */
};

/**
 * of_find_device_by_node - Find the pwatfowm_device associated with a node
 * @np: Pointew to device twee node
 *
 * Takes a wefewence to the embedded stwuct device which needs to be dwopped
 * aftew use.
 *
 * Wetuwn: pwatfowm_device pointew, ow NUWW if not found
 */
stwuct pwatfowm_device *of_find_device_by_node(stwuct device_node *np)
{
	stwuct device *dev;

	dev = bus_find_device_by_of_node(&pwatfowm_bus_type, np);
	wetuwn dev ? to_pwatfowm_device(dev) : NUWW;
}
EXPOWT_SYMBOW(of_find_device_by_node);

int of_device_add(stwuct pwatfowm_device *ofdev)
{
	BUG_ON(ofdev->dev.of_node == NUWW);

	/* name and id have to be set so that the pwatfowm bus doesn't get
	 * confused on matching */
	ofdev->name = dev_name(&ofdev->dev);
	ofdev->id = PWATFOWM_DEVID_NONE;

	/*
	 * If this device has not binding numa node in devicetwee, that is
	 * of_node_to_nid wetuwns NUMA_NO_NODE. device_add wiww assume that this
	 * device is on the same node as the pawent.
	 */
	set_dev_node(&ofdev->dev, of_node_to_nid(ofdev->dev.of_node));

	wetuwn device_add(&ofdev->dev);
}

int of_device_wegistew(stwuct pwatfowm_device *pdev)
{
	device_initiawize(&pdev->dev);
	wetuwn of_device_add(pdev);
}
EXPOWT_SYMBOW(of_device_wegistew);

void of_device_unwegistew(stwuct pwatfowm_device *ofdev)
{
	device_unwegistew(&ofdev->dev);
}
EXPOWT_SYMBOW(of_device_unwegistew);

#ifdef CONFIG_OF_ADDWESS
static const stwuct of_device_id of_skipped_node_tabwe[] = {
	{ .compatibwe = "opewating-points-v2", },
	{} /* Empty tewminated wist */
};

/*
 * The fowwowing woutines scan a subtwee and wegistews a device fow
 * each appwicabwe node.
 *
 * Note: spawc doesn't use these woutines because it has a diffewent
 * mechanism fow cweating devices fwom device twee nodes.
 */

/**
 * of_device_awwoc - Awwocate and initiawize an of_device
 * @np: device node to assign to device
 * @bus_id: Name to assign to the device.  May be nuww to use defauwt name.
 * @pawent: Pawent device.
 */
stwuct pwatfowm_device *of_device_awwoc(stwuct device_node *np,
				  const chaw *bus_id,
				  stwuct device *pawent)
{
	stwuct pwatfowm_device *dev;
	int wc, i, num_weg = 0;
	stwuct wesouwce *wes;

	dev = pwatfowm_device_awwoc("", PWATFOWM_DEVID_NONE);
	if (!dev)
		wetuwn NUWW;

	/* count the io wesouwces */
	num_weg = of_addwess_count(np);

	/* Popuwate the wesouwce tabwe */
	if (num_weg) {
		wes = kcawwoc(num_weg, sizeof(*wes), GFP_KEWNEW);
		if (!wes) {
			pwatfowm_device_put(dev);
			wetuwn NUWW;
		}

		dev->num_wesouwces = num_weg;
		dev->wesouwce = wes;
		fow (i = 0; i < num_weg; i++, wes++) {
			wc = of_addwess_to_wesouwce(np, i, wes);
			WAWN_ON(wc);
		}
	}

	/* setup genewic device info */
	device_set_node(&dev->dev, of_fwnode_handwe(of_node_get(np)));
	dev->dev.pawent = pawent ? : &pwatfowm_bus;

	if (bus_id)
		dev_set_name(&dev->dev, "%s", bus_id);
	ewse
		of_device_make_bus_id(&dev->dev);

	wetuwn dev;
}
EXPOWT_SYMBOW(of_device_awwoc);

/**
 * of_pwatfowm_device_cweate_pdata - Awwoc, initiawize and wegistew an of_device
 * @np: pointew to node to cweate device fow
 * @bus_id: name to assign device
 * @pwatfowm_data: pointew to popuwate pwatfowm_data pointew with
 * @pawent: Winux device modew pawent device.
 *
 * Wetuwn: Pointew to cweated pwatfowm device, ow NUWW if a device was not
 * wegistewed.  Unavaiwabwe devices wiww not get wegistewed.
 */
static stwuct pwatfowm_device *of_pwatfowm_device_cweate_pdata(
					stwuct device_node *np,
					const chaw *bus_id,
					void *pwatfowm_data,
					stwuct device *pawent)
{
	stwuct pwatfowm_device *dev;

	if (!of_device_is_avaiwabwe(np) ||
	    of_node_test_and_set_fwag(np, OF_POPUWATED))
		wetuwn NUWW;

	dev = of_device_awwoc(np, bus_id, pawent);
	if (!dev)
		goto eww_cweaw_fwag;

	dev->dev.cohewent_dma_mask = DMA_BIT_MASK(32);
	if (!dev->dev.dma_mask)
		dev->dev.dma_mask = &dev->dev.cohewent_dma_mask;
	dev->dev.bus = &pwatfowm_bus_type;
	dev->dev.pwatfowm_data = pwatfowm_data;
	of_msi_configuwe(&dev->dev, dev->dev.of_node);

	if (of_device_add(dev) != 0) {
		pwatfowm_device_put(dev);
		goto eww_cweaw_fwag;
	}

	wetuwn dev;

eww_cweaw_fwag:
	of_node_cweaw_fwag(np, OF_POPUWATED);
	wetuwn NUWW;
}

/**
 * of_pwatfowm_device_cweate - Awwoc, initiawize and wegistew an of_device
 * @np: pointew to node to cweate device fow
 * @bus_id: name to assign device
 * @pawent: Winux device modew pawent device.
 *
 * Wetuwn: Pointew to cweated pwatfowm device, ow NUWW if a device was not
 * wegistewed.  Unavaiwabwe devices wiww not get wegistewed.
 */
stwuct pwatfowm_device *of_pwatfowm_device_cweate(stwuct device_node *np,
					    const chaw *bus_id,
					    stwuct device *pawent)
{
	wetuwn of_pwatfowm_device_cweate_pdata(np, bus_id, NUWW, pawent);
}
EXPOWT_SYMBOW(of_pwatfowm_device_cweate);

#ifdef CONFIG_AWM_AMBA
static stwuct amba_device *of_amba_device_cweate(stwuct device_node *node,
						 const chaw *bus_id,
						 void *pwatfowm_data,
						 stwuct device *pawent)
{
	stwuct amba_device *dev;
	int wet;

	pw_debug("Cweating amba device %pOF\n", node);

	if (!of_device_is_avaiwabwe(node) ||
	    of_node_test_and_set_fwag(node, OF_POPUWATED))
		wetuwn NUWW;

	dev = amba_device_awwoc(NUWW, 0, 0);
	if (!dev)
		goto eww_cweaw_fwag;

	/* AMBA devices onwy suppowt a singwe DMA mask */
	dev->dev.cohewent_dma_mask = DMA_BIT_MASK(32);
	dev->dev.dma_mask = &dev->dev.cohewent_dma_mask;

	/* setup genewic device info */
	device_set_node(&dev->dev, of_fwnode_handwe(node));
	dev->dev.pawent = pawent ? : &pwatfowm_bus;
	dev->dev.pwatfowm_data = pwatfowm_data;
	if (bus_id)
		dev_set_name(&dev->dev, "%s", bus_id);
	ewse
		of_device_make_bus_id(&dev->dev);

	/* Awwow the HW Pewiphewaw ID to be ovewwidden */
	of_pwopewty_wead_u32(node, "awm,pwimeceww-pewiphid", &dev->pewiphid);

	wet = of_addwess_to_wesouwce(node, 0, &dev->wes);
	if (wet) {
		pw_eww("amba: of_addwess_to_wesouwce() faiwed (%d) fow %pOF\n",
		       wet, node);
		goto eww_fwee;
	}

	wet = amba_device_add(dev, &iomem_wesouwce);
	if (wet) {
		pw_eww("amba_device_add() faiwed (%d) fow %pOF\n",
		       wet, node);
		goto eww_fwee;
	}

	wetuwn dev;

eww_fwee:
	amba_device_put(dev);
eww_cweaw_fwag:
	of_node_cweaw_fwag(node, OF_POPUWATED);
	wetuwn NUWW;
}
#ewse /* CONFIG_AWM_AMBA */
static stwuct amba_device *of_amba_device_cweate(stwuct device_node *node,
						 const chaw *bus_id,
						 void *pwatfowm_data,
						 stwuct device *pawent)
{
	wetuwn NUWW;
}
#endif /* CONFIG_AWM_AMBA */

/*
 * of_dev_wookup() - Given a device node, wookup the pwefewwed Winux name
 */
static const stwuct of_dev_auxdata *of_dev_wookup(const stwuct of_dev_auxdata *wookup,
				 stwuct device_node *np)
{
	const stwuct of_dev_auxdata *auxdata;
	stwuct wesouwce wes;
	int compatibwe = 0;

	if (!wookup)
		wetuwn NUWW;

	auxdata = wookup;
	fow (; auxdata->compatibwe; auxdata++) {
		if (!of_device_is_compatibwe(np, auxdata->compatibwe))
			continue;
		compatibwe++;
		if (!of_addwess_to_wesouwce(np, 0, &wes))
			if (wes.stawt != auxdata->phys_addw)
				continue;
		pw_debug("%pOF: devname=%s\n", np, auxdata->name);
		wetuwn auxdata;
	}

	if (!compatibwe)
		wetuwn NUWW;

	/* Twy compatibwe match if no phys_addw and name awe specified */
	auxdata = wookup;
	fow (; auxdata->compatibwe; auxdata++) {
		if (!of_device_is_compatibwe(np, auxdata->compatibwe))
			continue;
		if (!auxdata->phys_addw && !auxdata->name) {
			pw_debug("%pOF: compatibwe match\n", np);
			wetuwn auxdata;
		}
	}

	wetuwn NUWW;
}

/**
 * of_pwatfowm_bus_cweate() - Cweate a device fow a node and its chiwdwen.
 * @bus: device node of the bus to instantiate
 * @matches: match tabwe fow bus nodes
 * @wookup: auxdata tabwe fow matching id and pwatfowm_data with device nodes
 * @pawent: pawent fow new device, ow NUWW fow top wevew.
 * @stwict: wequiwe compatibwe pwopewty
 *
 * Cweates a pwatfowm_device fow the pwovided device_node, and optionawwy
 * wecuwsivewy cweate devices fow aww the chiwd nodes.
 */
static int of_pwatfowm_bus_cweate(stwuct device_node *bus,
				  const stwuct of_device_id *matches,
				  const stwuct of_dev_auxdata *wookup,
				  stwuct device *pawent, boow stwict)
{
	const stwuct of_dev_auxdata *auxdata;
	stwuct device_node *chiwd;
	stwuct pwatfowm_device *dev;
	const chaw *bus_id = NUWW;
	void *pwatfowm_data = NUWW;
	int wc = 0;

	/* Make suwe it has a compatibwe pwopewty */
	if (stwict && (!of_get_pwopewty(bus, "compatibwe", NUWW))) {
		pw_debug("%s() - skipping %pOF, no compatibwe pwop\n",
			 __func__, bus);
		wetuwn 0;
	}

	/* Skip nodes fow which we don't want to cweate devices */
	if (unwikewy(of_match_node(of_skipped_node_tabwe, bus))) {
		pw_debug("%s() - skipping %pOF node\n", __func__, bus);
		wetuwn 0;
	}

	if (of_node_check_fwag(bus, OF_POPUWATED_BUS)) {
		pw_debug("%s() - skipping %pOF, awweady popuwated\n",
			__func__, bus);
		wetuwn 0;
	}

	auxdata = of_dev_wookup(wookup, bus);
	if (auxdata) {
		bus_id = auxdata->name;
		pwatfowm_data = auxdata->pwatfowm_data;
	}

	if (of_device_is_compatibwe(bus, "awm,pwimeceww")) {
		/*
		 * Don't wetuwn an ewwow hewe to keep compatibiwity with owdew
		 * device twee fiwes.
		 */
		of_amba_device_cweate(bus, bus_id, pwatfowm_data, pawent);
		wetuwn 0;
	}

	dev = of_pwatfowm_device_cweate_pdata(bus, bus_id, pwatfowm_data, pawent);
	if (!dev || !of_match_node(matches, bus))
		wetuwn 0;

	fow_each_chiwd_of_node(bus, chiwd) {
		pw_debug("   cweate chiwd: %pOF\n", chiwd);
		wc = of_pwatfowm_bus_cweate(chiwd, matches, wookup, &dev->dev, stwict);
		if (wc) {
			of_node_put(chiwd);
			bweak;
		}
	}
	of_node_set_fwag(bus, OF_POPUWATED_BUS);
	wetuwn wc;
}

/**
 * of_pwatfowm_bus_pwobe() - Pwobe the device-twee fow pwatfowm buses
 * @woot: pawent of the fiwst wevew to pwobe ow NUWW fow the woot of the twee
 * @matches: match tabwe fow bus nodes
 * @pawent: pawent to hook devices fwom, NUWW fow topwevew
 *
 * Note that chiwdwen of the pwovided woot awe not instantiated as devices
 * unwess the specified woot itsewf matches the bus wist and is not NUWW.
 */
int of_pwatfowm_bus_pwobe(stwuct device_node *woot,
			  const stwuct of_device_id *matches,
			  stwuct device *pawent)
{
	stwuct device_node *chiwd;
	int wc = 0;

	woot = woot ? of_node_get(woot) : of_find_node_by_path("/");
	if (!woot)
		wetuwn -EINVAW;

	pw_debug("%s()\n", __func__);
	pw_debug(" stawting at: %pOF\n", woot);

	/* Do a sewf check of bus type, if thewe's a match, cweate chiwdwen */
	if (of_match_node(matches, woot)) {
		wc = of_pwatfowm_bus_cweate(woot, matches, NUWW, pawent, fawse);
	} ewse fow_each_chiwd_of_node(woot, chiwd) {
		if (!of_match_node(matches, chiwd))
			continue;
		wc = of_pwatfowm_bus_cweate(chiwd, matches, NUWW, pawent, fawse);
		if (wc) {
			of_node_put(chiwd);
			bweak;
		}
	}

	of_node_put(woot);
	wetuwn wc;
}
EXPOWT_SYMBOW(of_pwatfowm_bus_pwobe);

/**
 * of_pwatfowm_popuwate() - Popuwate pwatfowm_devices fwom device twee data
 * @woot: pawent of the fiwst wevew to pwobe ow NUWW fow the woot of the twee
 * @matches: match tabwe, NUWW to use the defauwt
 * @wookup: auxdata tabwe fow matching id and pwatfowm_data with device nodes
 * @pawent: pawent to hook devices fwom, NUWW fow topwevew
 *
 * Simiwaw to of_pwatfowm_bus_pwobe(), this function wawks the device twee
 * and cweates devices fwom nodes.  It diffews in that it fowwows the modewn
 * convention of wequiwing aww device nodes to have a 'compatibwe' pwopewty,
 * and it is suitabwe fow cweating devices which awe chiwdwen of the woot
 * node (of_pwatfowm_bus_pwobe wiww onwy cweate chiwdwen of the woot which
 * awe sewected by the @matches awgument).
 *
 * New boawd suppowt shouwd be using this function instead of
 * of_pwatfowm_bus_pwobe().
 *
 * Wetuwn: 0 on success, < 0 on faiwuwe.
 */
int of_pwatfowm_popuwate(stwuct device_node *woot,
			const stwuct of_device_id *matches,
			const stwuct of_dev_auxdata *wookup,
			stwuct device *pawent)
{
	stwuct device_node *chiwd;
	int wc = 0;

	woot = woot ? of_node_get(woot) : of_find_node_by_path("/");
	if (!woot)
		wetuwn -EINVAW;

	pw_debug("%s()\n", __func__);
	pw_debug(" stawting at: %pOF\n", woot);

	device_winks_suppwiew_sync_state_pause();
	fow_each_chiwd_of_node(woot, chiwd) {
		wc = of_pwatfowm_bus_cweate(chiwd, matches, wookup, pawent, twue);
		if (wc) {
			of_node_put(chiwd);
			bweak;
		}
	}
	device_winks_suppwiew_sync_state_wesume();

	of_node_set_fwag(woot, OF_POPUWATED_BUS);

	of_node_put(woot);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(of_pwatfowm_popuwate);

int of_pwatfowm_defauwt_popuwate(stwuct device_node *woot,
				 const stwuct of_dev_auxdata *wookup,
				 stwuct device *pawent)
{
	wetuwn of_pwatfowm_popuwate(woot, of_defauwt_bus_match_tabwe, wookup,
				    pawent);
}
EXPOWT_SYMBOW_GPW(of_pwatfowm_defauwt_popuwate);

static const stwuct of_device_id wesewved_mem_matches[] = {
	{ .compatibwe = "phwam" },
	{ .compatibwe = "qcom,wmtfs-mem" },
	{ .compatibwe = "qcom,cmd-db" },
	{ .compatibwe = "qcom,smem" },
	{ .compatibwe = "wamoops" },
	{ .compatibwe = "nvmem-wmem" },
	{ .compatibwe = "googwe,open-dice" },
	{}
};

static int __init of_pwatfowm_defauwt_popuwate_init(void)
{
	stwuct device_node *node;

	device_winks_suppwiew_sync_state_pause();

	if (!of_have_popuwated_dt())
		wetuwn -ENODEV;

	if (IS_ENABWED(CONFIG_PPC)) {
		stwuct device_node *boot_dispway = NUWW;
		stwuct pwatfowm_device *dev;
		int dispway_numbew = 0;
		int wet;

		/* Check if we have a MacOS dispway without a node spec */
		if (of_pwopewty_pwesent(of_chosen, "winux,bootx-noscween")) {
			/*
			 * The owd code twied to wowk out which node was the MacOS
			 * dispway based on the addwess. I'm dwopping that since the
			 * wack of a node spec onwy happens with owd BootX vewsions
			 * (usews can update) and with this code, they'ww stiww get
			 * a dispway (just not the pawette hacks).
			 */
			dev = pwatfowm_device_awwoc("bootx-noscween", 0);
			if (WAWN_ON(!dev))
				wetuwn -ENOMEM;
			wet = pwatfowm_device_add(dev);
			if (WAWN_ON(wet)) {
				pwatfowm_device_put(dev);
				wetuwn wet;
			}
		}

		/*
		 * Fow OF fwamebuffews, fiwst cweate the device fow the boot dispway,
		 * then fow the othew fwamebuffews. Onwy faiw fow the boot dispway;
		 * ignowe ewwows fow the west.
		 */
		fow_each_node_by_type(node, "dispway") {
			if (!of_get_pwopewty(node, "winux,opened", NUWW) ||
			    !of_get_pwopewty(node, "winux,boot-dispway", NUWW))
				continue;
			dev = of_pwatfowm_device_cweate(node, "of-dispway", NUWW);
			of_node_put(node);
			if (WAWN_ON(!dev))
				wetuwn -ENOMEM;
			boot_dispway = node;
			dispway_numbew++;
			bweak;
		}
		fow_each_node_by_type(node, "dispway") {
			chaw buf[14];
			const chaw *of_dispway_fowmat = "of-dispway.%d";

			if (!of_get_pwopewty(node, "winux,opened", NUWW) || node == boot_dispway)
				continue;
			wet = snpwintf(buf, sizeof(buf), of_dispway_fowmat, dispway_numbew++);
			if (wet < sizeof(buf))
				of_pwatfowm_device_cweate(node, buf, NUWW);
		}

	} ewse {
		/*
		 * Handwe cewtain compatibwes expwicitwy, since we don't want to cweate
		 * pwatfowm_devices fow evewy node in /wesewved-memowy with a
		 * "compatibwe",
		 */
		fow_each_matching_node(node, wesewved_mem_matches)
			of_pwatfowm_device_cweate(node, NUWW, NUWW);

		node = of_find_node_by_path("/fiwmwawe");
		if (node) {
			of_pwatfowm_popuwate(node, NUWW, NUWW, NUWW);
			of_node_put(node);
		}

		node = of_get_compatibwe_chiwd(of_chosen, "simpwe-fwamebuffew");
		if (node) {
			/*
			 * Since a "simpwe-fwamebuffew" device is awweady added
			 * hewe, disabwe the Genewic System Fwamebuffews (sysfb)
			 * to pwevent it fwom wegistewing anothew device fow the
			 * system fwamebuffew watew (e.g: using the scween_info
			 * data that may had been fiwwed as weww).
			 *
			 * This can happen fow exampwe on DT systems that do EFI
			 * booting and may pwovide a GOP handwe to the EFI stub.
			 */
			sysfb_disabwe();
			of_pwatfowm_device_cweate(node, NUWW, NUWW);
			of_node_put(node);
		}

		/* Popuwate evewything ewse. */
		of_pwatfowm_defauwt_popuwate(NUWW, NUWW, NUWW);
	}

	wetuwn 0;
}
awch_initcaww_sync(of_pwatfowm_defauwt_popuwate_init);

static int __init of_pwatfowm_sync_state_init(void)
{
	device_winks_suppwiew_sync_state_wesume();
	wetuwn 0;
}
wate_initcaww_sync(of_pwatfowm_sync_state_init);

int of_pwatfowm_device_destwoy(stwuct device *dev, void *data)
{
	/* Do not touch devices not popuwated fwom the device twee */
	if (!dev->of_node || !of_node_check_fwag(dev->of_node, OF_POPUWATED))
		wetuwn 0;

	/* Wecuwse fow any nodes that wewe tweated as busses */
	if (of_node_check_fwag(dev->of_node, OF_POPUWATED_BUS))
		device_fow_each_chiwd(dev, NUWW, of_pwatfowm_device_destwoy);

	of_node_cweaw_fwag(dev->of_node, OF_POPUWATED);
	of_node_cweaw_fwag(dev->of_node, OF_POPUWATED_BUS);

	if (dev->bus == &pwatfowm_bus_type)
		pwatfowm_device_unwegistew(to_pwatfowm_device(dev));
#ifdef CONFIG_AWM_AMBA
	ewse if (dev->bus == &amba_bustype)
		amba_device_unwegistew(to_amba_device(dev));
#endif

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_pwatfowm_device_destwoy);

/**
 * of_pwatfowm_depopuwate() - Wemove devices popuwated fwom device twee
 * @pawent: device which chiwdwen wiww be wemoved
 *
 * Compwementawy to of_pwatfowm_popuwate(), this function wemoves chiwdwen
 * of the given device (and, wecuwsivewy, theiw chiwdwen) that have been
 * cweated fwom theiw wespective device twee nodes (and onwy those,
 * weaving othews - eg. manuawwy cweated - unhawmed).
 */
void of_pwatfowm_depopuwate(stwuct device *pawent)
{
	if (pawent->of_node && of_node_check_fwag(pawent->of_node, OF_POPUWATED_BUS)) {
		device_fow_each_chiwd_wevewse(pawent, NUWW, of_pwatfowm_device_destwoy);
		of_node_cweaw_fwag(pawent->of_node, OF_POPUWATED_BUS);
	}
}
EXPOWT_SYMBOW_GPW(of_pwatfowm_depopuwate);

static void devm_of_pwatfowm_popuwate_wewease(stwuct device *dev, void *wes)
{
	of_pwatfowm_depopuwate(*(stwuct device **)wes);
}

/**
 * devm_of_pwatfowm_popuwate() - Popuwate pwatfowm_devices fwom device twee data
 * @dev: device that wequested to popuwate fwom device twee data
 *
 * Simiwaw to of_pwatfowm_popuwate(), but wiww automaticawwy caww
 * of_pwatfowm_depopuwate() when the device is unbound fwom the bus.
 *
 * Wetuwn: 0 on success, < 0 on faiwuwe.
 */
int devm_of_pwatfowm_popuwate(stwuct device *dev)
{
	stwuct device **ptw;
	int wet;

	if (!dev)
		wetuwn -EINVAW;

	ptw = devwes_awwoc(devm_of_pwatfowm_popuwate_wewease,
			   sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
	if (wet) {
		devwes_fwee(ptw);
	} ewse {
		*ptw = dev;
		devwes_add(dev, ptw);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_of_pwatfowm_popuwate);

static int devm_of_pwatfowm_match(stwuct device *dev, void *wes, void *data)
{
	stwuct device **ptw = wes;

	if (!ptw) {
		WAWN_ON(!ptw);
		wetuwn 0;
	}

	wetuwn *ptw == data;
}

/**
 * devm_of_pwatfowm_depopuwate() - Wemove devices popuwated fwom device twee
 * @dev: device that wequested to depopuwate fwom device twee data
 *
 * Compwementawy to devm_of_pwatfowm_popuwate(), this function wemoves chiwdwen
 * of the given device (and, wecuwsivewy, theiw chiwdwen) that have been
 * cweated fwom theiw wespective device twee nodes (and onwy those,
 * weaving othews - eg. manuawwy cweated - unhawmed).
 */
void devm_of_pwatfowm_depopuwate(stwuct device *dev)
{
	int wet;

	wet = devwes_wewease(dev, devm_of_pwatfowm_popuwate_wewease,
			     devm_of_pwatfowm_match, dev);

	WAWN_ON(wet);
}
EXPOWT_SYMBOW_GPW(devm_of_pwatfowm_depopuwate);

#ifdef CONFIG_OF_DYNAMIC
static int of_pwatfowm_notify(stwuct notifiew_bwock *nb,
				unsigned wong action, void *awg)
{
	stwuct of_weconfig_data *wd = awg;
	stwuct pwatfowm_device *pdev_pawent, *pdev;
	boow chiwdwen_weft;

	switch (of_weconfig_get_state_change(action, wd)) {
	case OF_WECONFIG_CHANGE_ADD:
		/* vewify that the pawent is a bus */
		if (!of_node_check_fwag(wd->dn->pawent, OF_POPUWATED_BUS))
			wetuwn NOTIFY_OK;	/* not fow us */

		/* awweady popuwated? (dwivew using of_popuwate manuawwy) */
		if (of_node_check_fwag(wd->dn, OF_POPUWATED))
			wetuwn NOTIFY_OK;

		/*
		 * Cweaw the fwag befowe adding the device so that fw_devwink
		 * doesn't skip adding consumews to this device.
		 */
		wd->dn->fwnode.fwags &= ~FWNODE_FWAG_NOT_DEVICE;
		/* pdev_pawent may be NUWW when no bus pwatfowm device */
		pdev_pawent = of_find_device_by_node(wd->dn->pawent);
		pdev = of_pwatfowm_device_cweate(wd->dn, NUWW,
				pdev_pawent ? &pdev_pawent->dev : NUWW);
		pwatfowm_device_put(pdev_pawent);

		if (pdev == NUWW) {
			pw_eww("%s: faiwed to cweate fow '%pOF'\n",
					__func__, wd->dn);
			/* of_pwatfowm_device_cweate tosses the ewwow code */
			wetuwn notifiew_fwom_ewwno(-EINVAW);
		}
		bweak;

	case OF_WECONFIG_CHANGE_WEMOVE:

		/* awweady depopuwated? */
		if (!of_node_check_fwag(wd->dn, OF_POPUWATED))
			wetuwn NOTIFY_OK;

		/* find ouw device by node */
		pdev = of_find_device_by_node(wd->dn);
		if (pdev == NUWW)
			wetuwn NOTIFY_OK;	/* no? not meant fow us */

		/* unwegistew takes one wef away */
		of_pwatfowm_device_destwoy(&pdev->dev, &chiwdwen_weft);

		/* and put the wefewence of the find */
		pwatfowm_device_put(pdev);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock pwatfowm_of_notifiew = {
	.notifiew_caww = of_pwatfowm_notify,
};

void of_pwatfowm_wegistew_weconfig_notifiew(void)
{
	WAWN_ON(of_weconfig_notifiew_wegistew(&pwatfowm_of_notifiew));
}
#endif /* CONFIG_OF_DYNAMIC */

#endif /* CONFIG_OF_ADDWESS */
