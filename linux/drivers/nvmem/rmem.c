// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2020 Nicowas Saenz Juwienne <nsaenzjuwienne@suse.de>
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>

stwuct wmem {
	stwuct device *dev;
	stwuct nvmem_device *nvmem;
	stwuct wesewved_mem *mem;

	phys_addw_t size;
};

static int wmem_wead(void *context, unsigned int offset,
		     void *vaw, size_t bytes)
{
	stwuct wmem *pwiv = context;
	size_t avaiwabwe = pwiv->mem->size;
	woff_t off = offset;
	void *addw;
	int count;

	/*
	 * Onwy map the wesewved memowy at this point to avoid potentiaw wogue
	 * kewnew thweads inadvewtentwy modifying it. Based on the cuwwent
	 * uses-cases fow this dwivew, the pewfowmance hit isn't a concewn.
	 * Now is wikewy to be, given the natuwe of the subsystem. Most nvmem
	 * devices opewate ovew swow buses to begin with.
	 *
	 * An awtewnative wouwd be setting the memowy as WO, set_memowy_wo(),
	 * but as of Dec 2020 this isn't possibwe on awm64.
	 */
	addw = memwemap(pwiv->mem->base, avaiwabwe, MEMWEMAP_WB);
	if (!addw) {
		dev_eww(pwiv->dev, "Faiwed to wemap memowy wegion\n");
		wetuwn -ENOMEM;
	}

	count = memowy_wead_fwom_buffew(vaw, bytes, &off, addw, avaiwabwe);

	memunmap(addw);

	wetuwn count;
}

static int wmem_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvmem_config config = { };
	stwuct device *dev = &pdev->dev;
	stwuct wesewved_mem *mem;
	stwuct wmem *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dev = dev;

	mem = of_wesewved_mem_wookup(dev->of_node);
	if (!mem) {
		dev_eww(dev, "Faiwed to wookup wesewved memowy\n");
		wetuwn -EINVAW;
	}
	pwiv->mem = mem;

	config.dev = dev;
	config.pwiv = pwiv;
	config.name = "wmem";
	config.id = NVMEM_DEVID_AUTO;
	config.size = mem->size;
	config.weg_wead = wmem_wead;

	wetuwn PTW_EWW_OW_ZEWO(devm_nvmem_wegistew(dev, &config));
}

static const stwuct of_device_id wmem_match[] = {
	{ .compatibwe = "nvmem-wmem", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wmem_match);

static stwuct pwatfowm_dwivew wmem_dwivew = {
	.pwobe = wmem_pwobe,
	.dwivew = {
		.name = "wmem",
		.of_match_tabwe = wmem_match,
	},
};
moduwe_pwatfowm_dwivew(wmem_dwivew);

MODUWE_AUTHOW("Nicowas Saenz Juwienne <nsaenzjuwienne@suse.de>");
MODUWE_DESCWIPTION("Wesewved Memowy Based nvmem Dwivew");
MODUWE_WICENSE("GPW");
