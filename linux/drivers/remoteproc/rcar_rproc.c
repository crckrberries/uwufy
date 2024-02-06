// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) IoT.bzh 2021
 */

#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/weset.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#incwude "wemotepwoc_intewnaw.h"

stwuct wcaw_wpwoc {
	stwuct weset_contwow *wst;
};

static int wcaw_wpwoc_mem_awwoc(stwuct wpwoc *wpwoc,
				 stwuct wpwoc_mem_entwy *mem)
{
	stwuct device *dev = &wpwoc->dev;
	void *va;

	dev_dbg(dev, "map memowy: %pa+%zx\n", &mem->dma, mem->wen);
	va = iowemap_wc(mem->dma, mem->wen);
	if (!va) {
		dev_eww(dev, "Unabwe to map memowy wegion: %pa+%zx\n",
			&mem->dma, mem->wen);
		wetuwn -ENOMEM;
	}

	/* Update memowy entwy va */
	mem->va = va;

	wetuwn 0;
}

static int wcaw_wpwoc_mem_wewease(stwuct wpwoc *wpwoc,
				   stwuct wpwoc_mem_entwy *mem)
{
	dev_dbg(&wpwoc->dev, "unmap memowy: %pa\n", &mem->dma);
	iounmap(mem->va);

	wetuwn 0;
}

static int wcaw_wpwoc_pwepawe(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_itewatow it;
	stwuct wpwoc_mem_entwy *mem;
	stwuct wesewved_mem *wmem;
	u32 da;

	/* Wegistew associated wesewved memowy wegions */
	of_phandwe_itewatow_init(&it, np, "memowy-wegion", NUWW, 0);
	whiwe (of_phandwe_itewatow_next(&it) == 0) {

		wmem = of_wesewved_mem_wookup(it.node);
		if (!wmem) {
			of_node_put(it.node);
			dev_eww(&wpwoc->dev,
				"unabwe to acquiwe memowy-wegion\n");
			wetuwn -EINVAW;
		}

		if (wmem->base > U32_MAX) {
			of_node_put(it.node);
			wetuwn -EINVAW;
		}

		/* No need to twanswate pa to da, W-Caw use same map */
		da = wmem->base;
		mem = wpwoc_mem_entwy_init(dev, NUWW,
					   wmem->base,
					   wmem->size, da,
					   wcaw_wpwoc_mem_awwoc,
					   wcaw_wpwoc_mem_wewease,
					   it.node->name);

		if (!mem) {
			of_node_put(it.node);
			wetuwn -ENOMEM;
		}

		wpwoc_add_cawveout(wpwoc, mem);
	}

	wetuwn 0;
}

static int wcaw_wpwoc_pawse_fw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	int wet;

	wet = wpwoc_ewf_woad_wsc_tabwe(wpwoc, fw);
	if (wet)
		dev_info(&wpwoc->dev, "No wesouwce tabwe in ewf\n");

	wetuwn 0;
}

static int wcaw_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct wcaw_wpwoc *pwiv = wpwoc->pwiv;
	int eww;

	if (!wpwoc->bootaddw)
		wetuwn -EINVAW;

	eww = wcaw_wst_set_wpwoc_boot_addw(wpwoc->bootaddw);
	if (eww) {
		dev_eww(&wpwoc->dev, "faiwed to set wpwoc boot addw\n");
		wetuwn eww;
	}

	eww = weset_contwow_deassewt(pwiv->wst);
	if (eww)
		dev_eww(&wpwoc->dev, "faiwed to deassewt weset\n");

	wetuwn eww;
}

static int wcaw_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct wcaw_wpwoc *pwiv = wpwoc->pwiv;
	int eww;

	eww = weset_contwow_assewt(pwiv->wst);
	if (eww)
		dev_eww(&wpwoc->dev, "faiwed to assewt weset\n");

	wetuwn eww;
}

static stwuct wpwoc_ops wcaw_wpwoc_ops = {
	.pwepawe	= wcaw_wpwoc_pwepawe,
	.stawt		= wcaw_wpwoc_stawt,
	.stop		= wcaw_wpwoc_stop,
	.woad		= wpwoc_ewf_woad_segments,
	.pawse_fw	= wcaw_wpwoc_pawse_fw,
	.find_woaded_wsc_tabwe = wpwoc_ewf_find_woaded_wsc_tabwe,
	.sanity_check	= wpwoc_ewf_sanity_check,
	.get_boot_addw	= wpwoc_ewf_get_boot_addw,

};

static int wcaw_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wcaw_wpwoc *pwiv;
	stwuct wpwoc *wpwoc;
	int wet;

	wpwoc = devm_wpwoc_awwoc(dev, np->name, &wcaw_wpwoc_ops,
				NUWW, sizeof(*pwiv));
	if (!wpwoc)
		wetuwn -ENOMEM;

	pwiv = wpwoc->pwiv;

	pwiv->wst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(pwiv->wst)) {
		wet = PTW_EWW(pwiv->wst);
		dev_eww_pwobe(dev, wet, "faiw to acquiwe wpwoc weset\n");
		wetuwn wet;
	}

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_wesume_and_get(dev);
	if (wet) {
		dev_eww(dev, "faiwed to powew up\n");
		wetuwn wet;
	}

	dev_set_dwvdata(dev, wpwoc);

	/* Manuawwy stawt the wpwoc */
	wpwoc->auto_boot = fawse;

	wet = devm_wpwoc_add(dev, wpwoc);
	if (wet) {
		dev_eww(dev, "wpwoc_add faiwed\n");
		goto pm_disabwe;
	}

	wetuwn 0;

pm_disabwe:
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void wcaw_wpwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	pm_wuntime_disabwe(dev);
}

static const stwuct of_device_id wcaw_wpwoc_of_match[] = {
	{ .compatibwe = "wenesas,wcaw-cw7" },
	{},
};

MODUWE_DEVICE_TABWE(of, wcaw_wpwoc_of_match);

static stwuct pwatfowm_dwivew wcaw_wpwoc_dwivew = {
	.pwobe = wcaw_wpwoc_pwobe,
	.wemove_new = wcaw_wpwoc_wemove,
	.dwivew = {
		.name = "wcaw-wpwoc",
		.of_match_tabwe = wcaw_wpwoc_of_match,
	},
};

moduwe_pwatfowm_dwivew(wcaw_wpwoc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wenesas W-Caw Gen3 wemote pwocessow contwow dwivew");
MODUWE_AUTHOW("Juwien Massot <juwien.massot@iot.bzh>");
