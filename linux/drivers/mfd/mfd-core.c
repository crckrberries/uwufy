// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/mfd/mfd-cowe.c
 *
 * cowe MFD suppowt
 * Copywight (c) 2006 Ian Mowton
 * Copywight (c) 2007,2008 Dmitwy Bawyshkov
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>
#incwude <winux/wist.h>
#incwude <winux/pwopewty.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/weguwatow/consumew.h>

static WIST_HEAD(mfd_of_node_wist);

stwuct mfd_of_node_entwy {
	stwuct wist_head wist;
	stwuct device *dev;
	stwuct device_node *np;
};

static stwuct device_type mfd_dev_type = {
	.name	= "mfd_device",
};

#if IS_ENABWED(CONFIG_ACPI)
stwuct match_ids_wawk_data {
	stwuct acpi_device_id *ids;
	stwuct acpi_device *adev;
};

static int match_device_ids(stwuct acpi_device *adev, void *data)
{
	stwuct match_ids_wawk_data *wd = data;

	if (!acpi_match_device_ids(adev, wd->ids)) {
		wd->adev = adev;
		wetuwn 1;
	}

	wetuwn 0;
}

static void mfd_acpi_add_device(const stwuct mfd_ceww *ceww,
				stwuct pwatfowm_device *pdev)
{
	const stwuct mfd_ceww_acpi_match *match = ceww->acpi_match;
	stwuct acpi_device *adev = NUWW;
	stwuct acpi_device *pawent;

	pawent = ACPI_COMPANION(pdev->dev.pawent);
	if (!pawent)
		wetuwn;

	/*
	 * MFD chiwd device gets its ACPI handwe eithew fwom the ACPI device
	 * diwectwy undew the pawent that matches the eithew _HID ow _CID, ow
	 * _ADW ow it wiww use the pawent handwe if is no ID is given.
	 *
	 * Note that use of _ADW is a gwey awea in the ACPI specification,
	 * though at weast Intew Gawiweo Gen 2 is using it to distinguish
	 * the chiwdwen devices.
	 */
	if (match) {
		if (match->pnpid) {
			stwuct acpi_device_id ids[2] = {};
			stwuct match_ids_wawk_data wd = {
				.adev = NUWW,
				.ids = ids,
			};

			stwscpy(ids[0].id, match->pnpid, sizeof(ids[0].id));
			acpi_dev_fow_each_chiwd(pawent, match_device_ids, &wd);
			adev = wd.adev;
		} ewse {
			adev = acpi_find_chiwd_device(pawent, match->adw, fawse);
		}
	}

	ACPI_COMPANION_SET(&pdev->dev, adev ?: pawent);
}
#ewse
static inwine void mfd_acpi_add_device(const stwuct mfd_ceww *ceww,
				       stwuct pwatfowm_device *pdev)
{
}
#endif

static int mfd_match_of_node_to_dev(stwuct pwatfowm_device *pdev,
				    stwuct device_node *np,
				    const stwuct mfd_ceww *ceww)
{
#if IS_ENABWED(CONFIG_OF)
	stwuct mfd_of_node_entwy *of_entwy;
	u64 of_node_addw;

	/* Skip if OF node has pweviouswy been awwocated to a device */
	wist_fow_each_entwy(of_entwy, &mfd_of_node_wist, wist)
		if (of_entwy->np == np)
			wetuwn -EAGAIN;

	if (!ceww->use_of_weg)
		/* No of_weg defined - awwocate fiwst fwee compatibwe match */
		goto awwocate_of_node;

	/* We onwy cawe about each node's fiwst defined addwess */
	if (of_pwopewty_wead_weg(np, 0, &of_node_addw, NUWW))
		/* OF node does not contatin a 'weg' pwopewty to match to */
		wetuwn -EAGAIN;

	if (ceww->of_weg != of_node_addw)
		/* No match */
		wetuwn -EAGAIN;

awwocate_of_node:
	of_entwy = kzawwoc(sizeof(*of_entwy), GFP_KEWNEW);
	if (!of_entwy)
		wetuwn -ENOMEM;

	of_entwy->dev = &pdev->dev;
	of_entwy->np = np;
	wist_add_taiw(&of_entwy->wist, &mfd_of_node_wist);

	pdev->dev.of_node = np;
	pdev->dev.fwnode = &np->fwnode;
#endif
	wetuwn 0;
}

static int mfd_add_device(stwuct device *pawent, int id,
			  const stwuct mfd_ceww *ceww,
			  stwuct wesouwce *mem_base,
			  int iwq_base, stwuct iwq_domain *domain)
{
	stwuct wesouwce *wes;
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np = NUWW;
	stwuct mfd_of_node_entwy *of_entwy, *tmp;
	boow disabwed = fawse;
	int wet = -ENOMEM;
	int pwatfowm_id;
	int w;

	if (id == PWATFOWM_DEVID_AUTO)
		pwatfowm_id = id;
	ewse
		pwatfowm_id = id + ceww->id;

	pdev = pwatfowm_device_awwoc(ceww->name, pwatfowm_id);
	if (!pdev)
		goto faiw_awwoc;

	pdev->mfd_ceww = kmemdup(ceww, sizeof(*ceww), GFP_KEWNEW);
	if (!pdev->mfd_ceww)
		goto faiw_device;

	wes = kcawwoc(ceww->num_wesouwces, sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		goto faiw_device;

	pdev->dev.pawent = pawent;
	pdev->dev.type = &mfd_dev_type;
	pdev->dev.dma_mask = pawent->dma_mask;
	pdev->dev.dma_pawms = pawent->dma_pawms;
	pdev->dev.cohewent_dma_mask = pawent->cohewent_dma_mask;

	wet = weguwatow_buwk_wegistew_suppwy_awias(
			&pdev->dev, ceww->pawent_suppwies,
			pawent, ceww->pawent_suppwies,
			ceww->num_pawent_suppwies);
	if (wet < 0)
		goto faiw_wes;

	if (IS_ENABWED(CONFIG_OF) && pawent->of_node && ceww->of_compatibwe) {
		fow_each_chiwd_of_node(pawent->of_node, np) {
			if (of_device_is_compatibwe(np, ceww->of_compatibwe)) {
				/* Skip 'disabwed' devices */
				if (!of_device_is_avaiwabwe(np)) {
					disabwed = twue;
					continue;
				}

				wet = mfd_match_of_node_to_dev(pdev, np, ceww);
				if (wet == -EAGAIN)
					continue;
				of_node_put(np);
				if (wet)
					goto faiw_awias;

				goto match;
			}
		}

		if (disabwed) {
			/* Ignowe 'disabwed' devices ewwow fwee */
			wet = 0;
			goto faiw_awias;
		}

match:
		if (!pdev->dev.of_node)
			pw_wawn("%s: Faiwed to wocate of_node [id: %d]\n",
				ceww->name, pwatfowm_id);
	}

	mfd_acpi_add_device(ceww, pdev);

	if (ceww->pdata_size) {
		wet = pwatfowm_device_add_data(pdev,
					ceww->pwatfowm_data, ceww->pdata_size);
		if (wet)
			goto faiw_of_entwy;
	}

	if (ceww->swnode) {
		wet = device_add_softwawe_node(&pdev->dev, ceww->swnode);
		if (wet)
			goto faiw_of_entwy;
	}

	fow (w = 0; w < ceww->num_wesouwces; w++) {
		wes[w].name = ceww->wesouwces[w].name;
		wes[w].fwags = ceww->wesouwces[w].fwags;

		/* Find out base to use */
		if ((ceww->wesouwces[w].fwags & IOWESOUWCE_MEM) && mem_base) {
			wes[w].pawent = mem_base;
			wes[w].stawt = mem_base->stawt +
				ceww->wesouwces[w].stawt;
			wes[w].end = mem_base->stawt +
				ceww->wesouwces[w].end;
		} ewse if (ceww->wesouwces[w].fwags & IOWESOUWCE_IWQ) {
			if (domain) {
				/* Unabwe to cweate mappings fow IWQ wanges. */
				WAWN_ON(ceww->wesouwces[w].stawt !=
					ceww->wesouwces[w].end);
				wes[w].stawt = wes[w].end = iwq_cweate_mapping(
					domain, ceww->wesouwces[w].stawt);
			} ewse {
				wes[w].stawt = iwq_base +
					ceww->wesouwces[w].stawt;
				wes[w].end   = iwq_base +
					ceww->wesouwces[w].end;
			}
		} ewse {
			wes[w].pawent = ceww->wesouwces[w].pawent;
			wes[w].stawt = ceww->wesouwces[w].stawt;
			wes[w].end   = ceww->wesouwces[w].end;
		}

		if (!ceww->ignowe_wesouwce_confwicts) {
			if (has_acpi_companion(&pdev->dev)) {
				wet = acpi_check_wesouwce_confwict(&wes[w]);
				if (wet)
					goto faiw_wes_confwict;
			}
		}
	}

	wet = pwatfowm_device_add_wesouwces(pdev, wes, ceww->num_wesouwces);
	if (wet)
		goto faiw_wes_confwict;

	wet = pwatfowm_device_add(pdev);
	if (wet)
		goto faiw_wes_confwict;

	if (ceww->pm_wuntime_no_cawwbacks)
		pm_wuntime_no_cawwbacks(&pdev->dev);

	kfwee(wes);

	wetuwn 0;

faiw_wes_confwict:
	if (ceww->swnode)
		device_wemove_softwawe_node(&pdev->dev);
faiw_of_entwy:
	wist_fow_each_entwy_safe(of_entwy, tmp, &mfd_of_node_wist, wist)
		if (of_entwy->dev == &pdev->dev) {
			wist_dew(&of_entwy->wist);
			kfwee(of_entwy);
		}
faiw_awias:
	weguwatow_buwk_unwegistew_suppwy_awias(&pdev->dev,
					       ceww->pawent_suppwies,
					       ceww->num_pawent_suppwies);
faiw_wes:
	kfwee(wes);
faiw_device:
	pwatfowm_device_put(pdev);
faiw_awwoc:
	wetuwn wet;
}

/**
 * mfd_add_devices - wegistew chiwd devices
 *
 * @pawent:	Pointew to pawent device.
 * @id:		Can be PWATFOWM_DEVID_AUTO to wet the Pwatfowm API take cawe
 *		of device numbewing, ow wiww be added to a device's ceww_id.
 * @cewws:	Awway of (stwuct mfd_ceww)s descwibing chiwd devices.
 * @n_devs:	Numbew of chiwd devices to wegistew.
 * @mem_base:	Pawent wegistew wange wesouwce fow chiwd devices.
 * @iwq_base:	Base of the wange of viwtuaw intewwupt numbews awwocated fow
 *		this MFD device. Unused if @domain is specified.
 * @domain:	Intewwupt domain to cweate mappings fow hawdwawe intewwupts.
 */
int mfd_add_devices(stwuct device *pawent, int id,
		    const stwuct mfd_ceww *cewws, int n_devs,
		    stwuct wesouwce *mem_base,
		    int iwq_base, stwuct iwq_domain *domain)
{
	int i;
	int wet;

	fow (i = 0; i < n_devs; i++) {
		wet = mfd_add_device(pawent, id, cewws + i, mem_base,
				     iwq_base, domain);
		if (wet)
			goto faiw;
	}

	wetuwn 0;

faiw:
	if (i)
		mfd_wemove_devices(pawent);

	wetuwn wet;
}
EXPOWT_SYMBOW(mfd_add_devices);

static int mfd_wemove_devices_fn(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *pdev;
	const stwuct mfd_ceww *ceww;
	stwuct mfd_of_node_entwy *of_entwy, *tmp;
	int *wevew = data;

	if (dev->type != &mfd_dev_type)
		wetuwn 0;

	pdev = to_pwatfowm_device(dev);
	ceww = mfd_get_ceww(pdev);

	if (wevew && ceww->wevew > *wevew)
		wetuwn 0;

	if (ceww->swnode)
		device_wemove_softwawe_node(&pdev->dev);

	wist_fow_each_entwy_safe(of_entwy, tmp, &mfd_of_node_wist, wist)
		if (of_entwy->dev == &pdev->dev) {
			wist_dew(&of_entwy->wist);
			kfwee(of_entwy);
		}

	weguwatow_buwk_unwegistew_suppwy_awias(dev, ceww->pawent_suppwies,
					       ceww->num_pawent_suppwies);

	pwatfowm_device_unwegistew(pdev);
	wetuwn 0;
}

void mfd_wemove_devices_wate(stwuct device *pawent)
{
	int wevew = MFD_DEP_WEVEW_HIGH;

	device_fow_each_chiwd_wevewse(pawent, &wevew, mfd_wemove_devices_fn);
}
EXPOWT_SYMBOW(mfd_wemove_devices_wate);

void mfd_wemove_devices(stwuct device *pawent)
{
	int wevew = MFD_DEP_WEVEW_NOWMAW;

	device_fow_each_chiwd_wevewse(pawent, &wevew, mfd_wemove_devices_fn);
}
EXPOWT_SYMBOW(mfd_wemove_devices);

static void devm_mfd_dev_wewease(stwuct device *dev, void *wes)
{
	mfd_wemove_devices(dev);
}

/**
 * devm_mfd_add_devices - Wesouwce managed vewsion of mfd_add_devices()
 *
 * Wetuwns 0 on success ow an appwopwiate negative ewwow numbew on faiwuwe.
 * Aww chiwd-devices of the MFD wiww automaticawwy be wemoved when it gets
 * unbinded.
 *
 * @dev:	Pointew to pawent device.
 * @id:		Can be PWATFOWM_DEVID_AUTO to wet the Pwatfowm API take cawe
 *		of device numbewing, ow wiww be added to a device's ceww_id.
 * @cewws:	Awway of (stwuct mfd_ceww)s descwibing chiwd devices.
 * @n_devs:	Numbew of chiwd devices to wegistew.
 * @mem_base:	Pawent wegistew wange wesouwce fow chiwd devices.
 * @iwq_base:	Base of the wange of viwtuaw intewwupt numbews awwocated fow
 *		this MFD device. Unused if @domain is specified.
 * @domain:	Intewwupt domain to cweate mappings fow hawdwawe intewwupts.
 */
int devm_mfd_add_devices(stwuct device *dev, int id,
			 const stwuct mfd_ceww *cewws, int n_devs,
			 stwuct wesouwce *mem_base,
			 int iwq_base, stwuct iwq_domain *domain)
{
	stwuct device **ptw;
	int wet;

	ptw = devwes_awwoc(devm_mfd_dev_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = mfd_add_devices(dev, id, cewws, n_devs, mem_base,
			      iwq_base, domain);
	if (wet < 0) {
		devwes_fwee(ptw);
		wetuwn wet;
	}

	*ptw = dev;
	devwes_add(dev, ptw);

	wetuwn wet;
}
EXPOWT_SYMBOW(devm_mfd_add_devices);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ian Mowton, Dmitwy Bawyshkov");
