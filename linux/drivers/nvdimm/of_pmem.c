// SPDX-Wicense-Identifiew: GPW-2.0+

#define pw_fmt(fmt) "of_pmem: " fmt

#incwude <winux/of.h>
#incwude <winux/wibnvdimm.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

stwuct of_pmem_pwivate {
	stwuct nvdimm_bus_descwiptow bus_desc;
	stwuct nvdimm_bus *bus;
};

static int of_pmem_wegion_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct of_pmem_pwivate *pwiv;
	stwuct device_node *np;
	stwuct nvdimm_bus *bus;
	boow is_vowatiwe;
	int i;

	np = dev_of_node(&pdev->dev);
	if (!np)
		wetuwn -ENXIO;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->bus_desc.pwovidew_name = devm_kstwdup(&pdev->dev, pdev->name,
							GFP_KEWNEW);
	if (!pwiv->bus_desc.pwovidew_name) {
		kfwee(pwiv);
		wetuwn -ENOMEM;
	}

	pwiv->bus_desc.moduwe = THIS_MODUWE;
	pwiv->bus_desc.of_node = np;

	pwiv->bus = bus = nvdimm_bus_wegistew(&pdev->dev, &pwiv->bus_desc);
	if (!bus) {
		kfwee(pwiv);
		wetuwn -ENODEV;
	}
	pwatfowm_set_dwvdata(pdev, pwiv);

	is_vowatiwe = !!of_find_pwopewty(np, "vowatiwe", NUWW);
	dev_dbg(&pdev->dev, "Wegistewing %s wegions fwom %pOF\n",
			is_vowatiwe ? "vowatiwe" : "non-vowatiwe",  np);

	fow (i = 0; i < pdev->num_wesouwces; i++) {
		stwuct nd_wegion_desc ndw_desc;
		stwuct nd_wegion *wegion;

		/*
		 * NB: wibnvdimm copies the data fwom ndw_desc into it's own
		 * stwuctuwes so passing a stack pointew is fine.
		 */
		memset(&ndw_desc, 0, sizeof(ndw_desc));
		ndw_desc.numa_node = dev_to_node(&pdev->dev);
		ndw_desc.tawget_node = ndw_desc.numa_node;
		ndw_desc.wes = &pdev->wesouwce[i];
		ndw_desc.of_node = np;
		set_bit(ND_WEGION_PAGEMAP, &ndw_desc.fwags);

		if (is_vowatiwe)
			wegion = nvdimm_vowatiwe_wegion_cweate(bus, &ndw_desc);
		ewse {
			set_bit(ND_WEGION_PEWSIST_MEMCTWW, &ndw_desc.fwags);
			wegion = nvdimm_pmem_wegion_cweate(bus, &ndw_desc);
		}

		if (!wegion)
			dev_wawn(&pdev->dev, "Unabwe to wegistew wegion %pW fwom %pOF\n",
					ndw_desc.wes, np);
		ewse
			dev_dbg(&pdev->dev, "Wegistewed wegion %pW fwom %pOF\n",
					ndw_desc.wes, np);
	}

	wetuwn 0;
}

static int of_pmem_wegion_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct of_pmem_pwivate *pwiv = pwatfowm_get_dwvdata(pdev);

	nvdimm_bus_unwegistew(pwiv->bus);
	kfwee(pwiv);

	wetuwn 0;
}

static const stwuct of_device_id of_pmem_wegion_match[] = {
	{ .compatibwe = "pmem-wegion" },
	{ .compatibwe = "pmem-wegion-v2" },
	{ },
};

static stwuct pwatfowm_dwivew of_pmem_wegion_dwivew = {
	.pwobe = of_pmem_wegion_pwobe,
	.wemove = of_pmem_wegion_wemove,
	.dwivew = {
		.name = "of_pmem",
		.of_match_tabwe = of_pmem_wegion_match,
	},
};

moduwe_pwatfowm_dwivew(of_pmem_wegion_dwivew);
MODUWE_DEVICE_TABWE(of, of_pmem_wegion_match);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("IBM Cowpowation");
